// device.cpp - the OpenGL 3.3 core backend (see device.h). New platform code.
#include "platform/gfx/device.h"

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <vector>

#include "platform/cell/videoout.h"
#include "platform/gfx/gl.h"
#include "platform/gfx/mesh.h"
#include "platform/gfx/png.h"
#include "platform/log.h"
#include "platform/sdl/app.h"

using namespace dotd::gfx::gl;

namespace dotd::gfx {

namespace {
int g_width = 0;
int g_height = 0;
GLuint g_fbo = 0;
GLuint g_colorTex = 0;
GLuint g_depthRb = 0;
GLuint g_whiteTex = 0;
GLuint g_quadProgram = 0;
GLint g_quadRect = -1;
GLint g_quadColor = -1;
GLint g_quadTex = -1;
GLuint g_blitProgram = 0;
GLint g_blitGamma = -1;
GLint g_blitTex = -1;
GLuint g_vao = 0;  // attribute-less draws (quads, blit)
bool g_ready = false;
bool g_s3tc = false;
uint32_t g_frames = 0;

// The immediate-geometry program.
GLuint g_imProgram = 0;
GLint g_imViewProj = -1;
GLint g_imModel = -1;
GLint g_imColorScale = -1;
GLint g_imTex = -1;
GLint g_imUseTex = -1;
GLint g_imAlphaTest = -1;  // x: function (Compare, 7 = off), y: reference
GLuint g_imVao = 0;
GLuint g_imVbo = 0;
GLuint g_imIbo = 0;
float g_viewProj[16] = {1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1};

// Render targets (device.h): index + 1 is the id; a destroyed slot has fbo 0.
struct RenderTarget {
    GLuint fbo = 0;
    GLuint texture = 0;
    int width = 0;
    int height = 0;
};
std::vector<RenderTarget> g_targets;
uint32_t g_currentTarget = 0;
bool g_frontCW = false;

// Binds the frame buffer of the current target with its viewport.
void BindCurrent() {
    if (g_currentTarget != 0 && g_currentTarget <= g_targets.size() && g_targets[g_currentTarget - 1].fbo != 0) {
        const RenderTarget& t = g_targets[g_currentTarget - 1];
        glBindFramebuffer(GL_FRAMEBUFFER, t.fbo);
        glViewport(0, 0, t.width, t.height);
        return;
    }
    glBindFramebuffer(GL_FRAMEBUFFER, g_fbo);
    glViewport(0, 0, g_width, g_height);
}

// GLSL 3.30 core; written so it ports to GLSL ES 3.00 by changing the version line.
const char* kQuadVS =
    "#version 330 core\n"
    "uniform vec4 uRect;\n"  // x0, y0, x1, y1 in normalised device coordinates
    "out vec2 vUV;\n"
    "void main() {\n"
    "  vec2 c = vec2(float(gl_VertexID & 1), float((gl_VertexID >> 1) & 1));\n"
    "  vUV = vec2(c.x, c.y);\n"
    "  gl_Position = vec4(mix(uRect.x, uRect.z, c.x), mix(uRect.y, uRect.w, c.y), 0.0, 1.0);\n"
    "}\n";
const char* kQuadFS =
    "#version 330 core\n"
    "uniform sampler2D uTex;\n"
    "uniform vec4 uColor;\n"
    "in vec2 vUV;\n"
    "out vec4 oColor;\n"
    "void main() { oColor = texture(uTex, vUV) * uColor; }\n";
const char* kBlitVS =
    "#version 330 core\n"
    "out vec2 vUV;\n"
    "void main() {\n"
    "  vec2 c = vec2(float(gl_VertexID & 1), float((gl_VertexID >> 1) & 1));\n"
    "  vUV = c;\n"
    "  gl_Position = vec4(c * 2.0 - 1.0, 0.0, 1.0);\n"
    "}\n";
const char* kBlitFS =
    "#version 330 core\n"
    "uniform sampler2D uTex;\n"
    "uniform float uGamma;\n"
    "in vec2 vUV;\n"
    "out vec4 oColor;\n"
    "void main() {\n"
    "  vec4 c = texture(uTex, vUV);\n"
    "  oColor = vec4(pow(c.rgb, vec3(1.0 / uGamma)), 1.0);\n"
    "}\n";

// RenderWare Im3D / atomic geometry: vertex colour x colour scale x texture (RW's modulate).
const char* kImVS =
    "#version 330 core\n"
    "layout(location = 0) in vec3 aPos;\n"
    "layout(location = 1) in vec4 aColor;\n"
    "layout(location = 2) in vec2 aUV;\n"
    "uniform mat4 uViewProj;\n"
    "uniform mat4 uModel;\n"
    "out vec4 vColor;\n"
    "out vec2 vUV;\n"
    "void main() {\n"
    "  vColor = aColor;\n"
    "  vUV = aUV;\n"
    "  gl_Position = uViewProj * (uModel * vec4(aPos, 1.0));\n"
    "}\n";
const char* kImFS =
    "#version 330 core\n"
    "uniform sampler2D uTex;\n"
    "uniform int uUseTex;\n"
    "uniform vec4 uColorScale;\n"
    "uniform vec4 uAlphaTest;\n"
    "in vec4 vColor;\n"
    "in vec2 vUV;\n"
    "out vec4 oColor;\n"
    "void main() {\n"
    "  vec4 c = vColor * uColorScale;\n"
    "  if (uUseTex != 0) c *= texture(uTex, vUV);\n"
    "  int f = int(uAlphaTest.x);\n"
    "  float r = uAlphaTest.y;\n"
    "  bool pass = true;\n"
    "  if (f == 0) pass = false;\n"
    "  else if (f == 1) pass = c.a < r;\n"
    "  else if (f == 2) pass = abs(c.a - r) < (0.5 / 255.0);\n"
    "  else if (f == 3) pass = c.a <= r;\n"
    "  else if (f == 4) pass = c.a > r;\n"
    "  else if (f == 5) pass = abs(c.a - r) >= (0.5 / 255.0);\n"
    "  else if (f == 6) pass = c.a >= r;\n"
    "  if (!pass) discard;\n"
    "  oColor = c;\n"
    "}\n";

GLuint Compile(GLenum type, const char* src) {
    GLuint s = glCreateShader(type);
    glShaderSource(s, 1, &src, nullptr);
    glCompileShader(s);
    GLint ok = 0;
    glGetShaderiv(s, GL_COMPILE_STATUS, &ok);
    if (!ok) {
        char log[1024];
        glGetShaderInfoLog(s, sizeof(log), nullptr, log);
        DOTD_LOG("gfx: shader compile failed: %s", log);
    }
    return s;
}

GLuint Link(const char* vs, const char* fs) {
    GLuint p = glCreateProgram();
    GLuint v = Compile(GL_VERTEX_SHADER, vs);
    GLuint f = Compile(GL_FRAGMENT_SHADER, fs);
    glAttachShader(p, v);
    glAttachShader(p, f);
    glLinkProgram(p);
    glDeleteShader(v);
    glDeleteShader(f);
    GLint ok = 0;
    glGetProgramiv(p, GL_LINK_STATUS, &ok);
    if (!ok) {
        char log[1024];
        glGetProgramInfoLog(p, sizeof(log), nullptr, log);
        DOTD_LOG("gfx: program link failed: %s", log);
    }
    return p;
}

void ToNdc(float x, float y, float* nx, float* ny) {
    *nx = x / static_cast<float>(g_width) * 2.0f - 1.0f;
    *ny = 1.0f - y / static_cast<float>(g_height) * 2.0f;
}

bool HasExtension(const char* name) {
    GLint count = 0;
    glGetIntegerv(GL_NUM_EXTENSIONS, &count);
    for (GLint i = 0; i < count; ++i) {
        const char* ext = reinterpret_cast<const char*>(glGetStringi(GL_EXTENSIONS, static_cast<GLuint>(i)));
        if (ext != nullptr && std::strcmp(ext, name) == 0) return true;
    }
    return false;
}

GLenum GlBlend(Blend b) {
    switch (b) {
        case Blend::kZero: return GL_ZERO;
        case Blend::kOne: return GL_ONE;
        case Blend::kSrcColor: return GL_SRC_COLOR;
        case Blend::kInvSrcColor: return GL_ONE_MINUS_SRC_COLOR;
        case Blend::kSrcAlpha: return GL_SRC_ALPHA;
        case Blend::kInvSrcAlpha: return GL_ONE_MINUS_SRC_ALPHA;
        case Blend::kDestAlpha: return GL_DST_ALPHA;
        case Blend::kInvDestAlpha: return GL_ONE_MINUS_DST_ALPHA;
        case Blend::kDestColor: return GL_DST_COLOR;
        case Blend::kInvDestColor: return GL_ONE_MINUS_DST_COLOR;
        case Blend::kSrcAlphaSat: return GL_SRC_ALPHA_SATURATE;
    }
    return GL_ONE;
}

GLint GlAddress(Address a) {
    switch (a) {
        case Address::kWrap: return GL_REPEAT;
        case Address::kMirror: return GL_MIRRORED_REPEAT;
        case Address::kClamp: return GL_CLAMP_TO_EDGE;
    }
    return GL_REPEAT;
}

GLenum GlPrimitive(Primitive p) {
    switch (p) {
        case Primitive::kLines: return GL_LINES;
        case Primitive::kLineStrip: return GL_LINE_STRIP;
        case Primitive::kTriangles: return GL_TRIANGLES;
        case Primitive::kTriangleStrip: return GL_TRIANGLE_STRIP;
        case Primitive::kTriangleFan: return GL_TRIANGLE_FAN;
    }
    return GL_TRIANGLES;
}

// ---- S3TC decoding (when the driver lacks EXT_texture_compression_s3tc, e.g. GLES/WebGL) ----------
void Rgb565(uint16_t c, uint8_t out[3]) {
    out[0] = static_cast<uint8_t>(((c >> 11) & 0x1f) * 255 / 31);
    out[1] = static_cast<uint8_t>(((c >> 5) & 0x3f) * 255 / 63);
    out[2] = static_cast<uint8_t>((c & 0x1f) * 255 / 31);
}

void DecodeColorBlock(const uint8_t* b, bool dxt1, uint8_t out[16][4]) {
    const uint16_t c0 = static_cast<uint16_t>(b[0] | (b[1] << 8));
    const uint16_t c1 = static_cast<uint16_t>(b[2] | (b[3] << 8));
    uint8_t pal[4][4];
    Rgb565(c0, pal[0]);
    Rgb565(c1, pal[1]);
    pal[0][3] = pal[1][3] = 255;
    if (!dxt1 || c0 > c1) {
        for (int k = 0; k < 3; ++k) {
            pal[2][k] = static_cast<uint8_t>((2 * pal[0][k] + pal[1][k]) / 3);
            pal[3][k] = static_cast<uint8_t>((pal[0][k] + 2 * pal[1][k]) / 3);
        }
        pal[2][3] = pal[3][3] = 255;
    } else {
        for (int k = 0; k < 3; ++k) pal[2][k] = static_cast<uint8_t>((pal[0][k] + pal[1][k]) / 2);
        pal[2][3] = 255;
        pal[3][0] = pal[3][1] = pal[3][2] = pal[3][3] = 0;
    }
    const uint32_t bits = static_cast<uint32_t>(b[4]) | (static_cast<uint32_t>(b[5]) << 8) |
                          (static_cast<uint32_t>(b[6]) << 16) | (static_cast<uint32_t>(b[7]) << 24);
    for (int i = 0; i < 16; ++i) std::memcpy(out[i], pal[(bits >> (2 * i)) & 3], 4);
}

std::vector<uint8_t> DecodeS3tc(TextureFormat format, int width, int height, const uint8_t* data) {
    std::vector<uint8_t> rgba(static_cast<size_t>(width) * height * 4, 0);
    const int bw = (width + 3) / 4, bh = (height + 3) / 4;
    const int blockBytes = format == TextureFormat::kBC1 ? 8 : 16;
    for (int by = 0; by < bh; ++by) {
        for (int bx = 0; bx < bw; ++bx) {
            const uint8_t* b = data + (static_cast<size_t>(by) * bw + bx) * blockBytes;
            uint8_t px[16][4];
            DecodeColorBlock(format == TextureFormat::kBC1 ? b : b + 8, format == TextureFormat::kBC1, px);
            if (format == TextureFormat::kBC2) {
                for (int i = 0; i < 16; ++i) {
                    const uint8_t nib = static_cast<uint8_t>((b[i / 2] >> ((i & 1) * 4)) & 0xf);
                    px[i][3] = static_cast<uint8_t>(nib * 17);
                }
            } else if (format == TextureFormat::kBC3) {
                const uint8_t a0 = b[0], a1 = b[1];
                uint8_t pal[8];
                pal[0] = a0;
                pal[1] = a1;
                if (a0 > a1) {
                    for (int k = 1; k < 7; ++k) pal[k + 1] = static_cast<uint8_t>(((7 - k) * a0 + k * a1) / 7);
                } else {
                    for (int k = 1; k < 5; ++k) pal[k + 1] = static_cast<uint8_t>(((5 - k) * a0 + k * a1) / 5);
                    pal[6] = 0;
                    pal[7] = 255;
                }
                uint64_t bits = 0;
                for (int k = 0; k < 6; ++k) bits |= static_cast<uint64_t>(b[2 + k]) << (8 * k);
                for (int i = 0; i < 16; ++i) px[i][3] = pal[(bits >> (3 * i)) & 7];
            }
            for (int i = 0; i < 16; ++i) {
                const int x = bx * 4 + (i & 3), y = by * 4 + (i >> 2);
                if (x < width && y < height) std::memcpy(&rgba[(static_cast<size_t>(y) * width + x) * 4], px[i], 4);
            }
        }
    }
    return rgba;
}

void SetDefaultSampler(GLint filter) {
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filter);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filter);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
}

// DOTD_SCREENSHOT=path:frame[,frame...]
struct ScreenshotRequest {
    std::string path;
    std::vector<uint32_t> frames;
};
ScreenshotRequest g_shots;
bool g_shotsParsed = false;

void ParseScreenshotRequest() {
    g_shotsParsed = true;
    const char* env = std::getenv("DOTD_SCREENSHOT");
    if (env == nullptr || *env == 0) return;
    std::string spec = env;
    const size_t colon = spec.rfind(':');
    if (colon == std::string::npos || colon == 1) {  // "C:\..." alone has no frame list
        DOTD_LOG("gfx: DOTD_SCREENSHOT=%s: expected path:frame[,frame...]", env);
        return;
    }
    g_shots.path = spec.substr(0, colon);
    const char* p = spec.c_str() + colon + 1;
    while (*p != 0) {
        char* end = nullptr;
        const unsigned long frame = std::strtoul(p, &end, 10);
        if (end == p) break;
        g_shots.frames.push_back(static_cast<uint32_t>(frame));
        p = *end == ',' ? end + 1 : end;
    }
}

void MaybeScreenshot() {
    if (!g_shotsParsed) ParseScreenshotRequest();
    for (uint32_t frame : g_shots.frames) {
        if (frame != g_frames) continue;
        std::string path = g_shots.path;
        const size_t pos = path.find("%d");
        if (pos != std::string::npos) path.replace(pos, 2, std::to_string(frame));
        if (SaveScreenshot(path.c_str())) DOTD_LOG("gfx: frame %u saved to %s", frame, path.c_str());
    }
}

}  // namespace

bool Init(int internalWidth, int internalHeight) {
    if (!gl::Load(platform::sdl::GetGLProcAddress)) return false;
    DOTD_LOG("gfx: %s / %s", reinterpret_cast<const char*>(glGetString(GL_RENDERER)),
             reinterpret_cast<const char*>(glGetString(GL_VERSION)));
    g_width = internalWidth;
    g_height = internalHeight;
    g_s3tc = HasExtension("GL_EXT_texture_compression_s3tc");

    glGenTextures(1, &g_colorTex);
    glBindTexture(GL_TEXTURE_2D, g_colorTex);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, g_width, g_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
    SetDefaultSampler(GL_LINEAR);
    glGenRenderbuffers(1, &g_depthRb);
    glBindRenderbuffer(GL_RENDERBUFFER, g_depthRb);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, g_width, g_height);
    glGenFramebuffers(1, &g_fbo);
    glBindFramebuffer(GL_FRAMEBUFFER, g_fbo);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, g_colorTex, 0);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, g_depthRb);
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
        DOTD_LOG("gfx: internal target incomplete");
        return false;
    }
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    const uint32_t white = 0xffffffffu;
    g_whiteTex = CreateTextureRGBA8(1, 1, &white, false);

    g_quadProgram = Link(kQuadVS, kQuadFS);
    g_quadRect = glGetUniformLocation(g_quadProgram, "uRect");
    g_quadColor = glGetUniformLocation(g_quadProgram, "uColor");
    g_quadTex = glGetUniformLocation(g_quadProgram, "uTex");
    g_blitProgram = Link(kBlitVS, kBlitFS);
    g_blitGamma = glGetUniformLocation(g_blitProgram, "uGamma");
    g_blitTex = glGetUniformLocation(g_blitProgram, "uTex");
    glGenVertexArrays(1, &g_vao);  // core profile needs a bound VAO even without attributes

    g_imProgram = Link(kImVS, kImFS);
    g_imViewProj = glGetUniformLocation(g_imProgram, "uViewProj");
    g_imModel = glGetUniformLocation(g_imProgram, "uModel");
    g_imColorScale = glGetUniformLocation(g_imProgram, "uColorScale");
    g_imTex = glGetUniformLocation(g_imProgram, "uTex");
    g_imUseTex = glGetUniformLocation(g_imProgram, "uUseTex");
    g_imAlphaTest = glGetUniformLocation(g_imProgram, "uAlphaTest");
    glGenVertexArrays(1, &g_imVao);
    glBindVertexArray(g_imVao);
    glGenBuffers(1, &g_imVbo);
    glGenBuffers(1, &g_imIbo);
    glBindBuffer(GL_ARRAY_BUFFER, g_imVbo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, g_imIbo);
    glVertexAttribPointer(0, 3, GL_FLOAT, 0, sizeof(Vertex), reinterpret_cast<const void*>(0));
    glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, 1, sizeof(Vertex), reinterpret_cast<const void*>(12));
    glVertexAttribPointer(2, 2, GL_FLOAT, 0, sizeof(Vertex), reinterpret_cast<const void*>(16));
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);
    glBindVertexArray(0);

    glUseProgram(0);
    DOTD_LOG("gfx: internal target %dx%d, S3TC %s", g_width, g_height, g_s3tc ? "native" : "decoded on the CPU");
    g_ready = glGetError() == GL_NO_ERROR;
    return g_ready;
}

bool IsReady() { return g_ready; }
int InternalWidth() { return g_width; }
int InternalHeight() { return g_height; }

void Shutdown() {
    if (!g_ready) return;
    g_ready = false;
    if (g_vao) glDeleteVertexArrays(1, &g_vao);
    if (g_imVao) glDeleteVertexArrays(1, &g_imVao);
    if (g_imVbo) glDeleteBuffers(1, &g_imVbo);
    if (g_imIbo) glDeleteBuffers(1, &g_imIbo);
    if (g_quadProgram) glDeleteProgram(g_quadProgram);
    if (g_blitProgram) glDeleteProgram(g_blitProgram);
    if (g_imProgram) glDeleteProgram(g_imProgram);
    if (g_whiteTex) glDeleteTextures(1, &g_whiteTex);
    if (g_colorTex) glDeleteTextures(1, &g_colorTex);
    if (g_depthRb) glDeleteRenderbuffers(1, &g_depthRb);
    if (g_fbo) glDeleteFramebuffers(1, &g_fbo);
    for (RenderTarget& t : g_targets) {
        if (t.fbo) glDeleteFramebuffers(1, &t.fbo);
        if (t.texture) glDeleteTextures(1, &t.texture);
    }
    g_targets.clear();
    g_currentTarget = 0;
    g_vao = g_imVao = g_imVbo = g_imIbo = 0;
    g_quadProgram = g_blitProgram = g_imProgram = g_whiteTex = g_colorTex = g_depthRb = g_fbo = 0;
}

void BeginFrame() {
    if (!g_ready) return;
    BindCurrent();
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);
}

void Clear(float r, float g, float b, float a) { ClearTarget(true, true, r, g, b, a); }

uint32_t CreateRenderTarget(int width, int height) {
    if (!g_ready || width <= 0 || height <= 0) return 0;
    RenderTarget t;
    t.width = width;
    t.height = height;
    glGenTextures(1, &t.texture);
    glBindTexture(GL_TEXTURE_2D, t.texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, 0);
    SetDefaultSampler(GL_LINEAR);
    glGenFramebuffers(1, &t.fbo);
    glBindFramebuffer(GL_FRAMEBUFFER, t.fbo);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, t.texture, 0);
    if (width == g_width && height == g_height)
        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, g_depthRb);
    const bool complete = glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE;
    if (complete) {
        // A new camera texture starts black (the PS3's video memory is not cleared either; black keeps the first
        // frames deterministic).
        glViewport(0, 0, width, height);
        glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT);
    }
    BindCurrent();
    if (!complete) {
        DOTD_LOG("gfx: render target %dx%d incomplete", width, height);
        glDeleteFramebuffers(1, &t.fbo);
        glDeleteTextures(1, &t.texture);
        return 0;
    }
    for (size_t i = 0; i < g_targets.size(); ++i) {
        if (g_targets[i].fbo == 0) {
            g_targets[i] = t;
            return static_cast<uint32_t>(i + 1);
        }
    }
    g_targets.push_back(t);
    return static_cast<uint32_t>(g_targets.size());
}

void DestroyRenderTarget(uint32_t target) {
    if (!g_ready || target == 0 || target > g_targets.size()) return;
    RenderTarget& t = g_targets[target - 1];
    if (t.fbo != 0) glDeleteFramebuffers(1, &t.fbo);
    if (t.texture != 0) glDeleteTextures(1, &t.texture);
    t = RenderTarget();
    if (g_currentTarget == target) {
        g_currentTarget = 0;
        BindCurrent();
    }
}

uint32_t RenderTargetTexture(uint32_t target) {
    if (target == 0) return g_colorTex;
    if (target > g_targets.size()) return 0;
    return g_targets[target - 1].texture;
}

void SetRenderTarget(uint32_t target) {
    if (target > g_targets.size() || (target != 0 && g_targets[target - 1].fbo == 0)) target = 0;
    g_currentTarget = target;
    if (g_ready) BindCurrent();
}

uint32_t CurrentRenderTarget() { return g_currentTarget; }

void SetFrontFaceClockwise(bool clockwise) { g_frontCW = clockwise; }

void ClearTarget(bool color, bool depth, float r, float g, float b, float a) {
    if (!g_ready) return;
    BindCurrent();
    GLbitfield mask = 0;
    if (color) {
        glClearColor(r, g, b, a);
        mask |= GL_COLOR_BUFFER_BIT;
    }
    if (depth) {
        glDepthMask(1);
        mask |= GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT;
    }
    if (mask != 0) glClear(mask);
}

uint32_t CreateTexture(TextureFormat format, int width, int height, int levelCount, const TextureLevel* levels) {
    if (!g_ready || width <= 0 || height <= 0 || levelCount <= 0) return 0;
    GLuint t = 0;
    glGenTextures(1, &t);
    glBindTexture(GL_TEXTURE_2D, t);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    int w = width, h = height;
    for (int level = 0; level < levelCount; ++level) {
        const auto* data = static_cast<const uint8_t*>(levels[level].data);
        switch (format) {
            case TextureFormat::kRGBA8:
                glTexImage2D(GL_TEXTURE_2D, level, GL_RGBA8, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
                break;
            case TextureFormat::kR8:
                glTexImage2D(GL_TEXTURE_2D, level, GL_R8, w, h, 0, GL_RED, GL_UNSIGNED_BYTE, data);
                break;
            case TextureFormat::kBC1:
            case TextureFormat::kBC2:
            case TextureFormat::kBC3:
                if (g_s3tc) {
                    const GLenum ifmt = format == TextureFormat::kBC1   ? GL_COMPRESSED_RGBA_S3TC_DXT1_EXT
                                        : format == TextureFormat::kBC2 ? GL_COMPRESSED_RGBA_S3TC_DXT3_EXT
                                                                        : GL_COMPRESSED_RGBA_S3TC_DXT5_EXT;
                    glCompressedTexImage2D(GL_TEXTURE_2D, level, ifmt, w, h, 0, static_cast<GLsizei>(levels[level].size),
                                           data);
                } else {
                    const std::vector<uint8_t> rgba = DecodeS3tc(format, w, h, data);
                    glTexImage2D(GL_TEXTURE_2D, level, GL_RGBA8, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, rgba.data());
                }
                break;
        }
        w = w > 1 ? w / 2 : 1;
        h = h > 1 ? h / 2 : 1;
    }
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_BASE_LEVEL, 0);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, levelCount - 1);
    SetDefaultSampler(GL_LINEAR);
    return t;
}

uint32_t CreateTextureRGBA8(int width, int height, const void* pixels, bool linearFilter) {
    GLuint t = 0;
    glGenTextures(1, &t);
    glBindTexture(GL_TEXTURE_2D, t);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, 0);
    SetDefaultSampler(linearFilter ? GL_LINEAR : GL_NEAREST);
    return t;
}

void SetTextureMaxLod(uint32_t texture, float lod) {
    if (!g_ready || texture == 0) return;
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_LOD, lod);
}

void DestroyTexture(uint32_t texture) {
    GLuint t = texture;
    if (t && g_ready) glDeleteTextures(1, &t);
}

// The bound texture's min / mag filters for a state (see DrawState::filterMode).
void SetTextureFilter(const DrawState& state) {
    static const GLint kMin[7] = {0, GL_NEAREST, GL_LINEAR, GL_NEAREST_MIPMAP_NEAREST, GL_LINEAR_MIPMAP_NEAREST,
                                  GL_NEAREST_MIPMAP_LINEAR, GL_LINEAR_MIPMAP_LINEAR};
    static const GLint kMag[7] = {0, GL_NEAREST, GL_LINEAR, GL_NEAREST, GL_LINEAR, GL_NEAREST, GL_LINEAR};
    if (state.filterMode >= 1 && state.filterMode <= 6) {
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, kMin[state.filterMode]);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, kMag[state.filterMode]);
        return;
    }
    GLint minFilter = state.linear ? GL_LINEAR : GL_NEAREST;
    if (state.mipmaps) minFilter = state.linear ? GL_LINEAR_MIPMAP_LINEAR : GL_NEAREST_MIPMAP_NEAREST;
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minFilter);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, state.linear ? GL_LINEAR : GL_NEAREST);
}

void ApplyState(const DrawState& state) {
    if (!g_ready) return;
    if (state.blend) {
        glEnable(GL_BLEND);
        glBlendFunc(GlBlend(state.srcBlend), GlBlend(state.dstBlend));
    } else {
        glDisable(GL_BLEND);
    }
    if (state.depthTest) {
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LEQUAL);
    } else {
        glDisable(GL_DEPTH_TEST);
    }
    glDepthMask(state.depthWrite ? 1 : 0);
    if (state.cull == 0) {
        glDisable(GL_CULL_FACE);
    } else {
        glEnable(GL_CULL_FACE);
        glFrontFace(g_frontCW ? GL_CW : GL_CCW);
        glCullFace(state.cull == 1 ? GL_BACK : GL_FRONT);
    }
}

void SetViewProjection(const float matrix[16]) { std::memcpy(g_viewProj, matrix, sizeof(g_viewProj)); }

// mesh.h: a draw outside DrawPrimitive goes into the current render target.
void BindTarget() {
    if (g_ready) BindCurrent();
}

// mesh.h: a texture unit's texture and sampler state (the shader's samplers sit on the units of their registers).
void BindTextureUnit(int unit, uint32_t texture, const DrawState& state) {
    if (!g_ready) return;
    glActiveTexture(GL_TEXTURE0 + static_cast<GLenum>(unit));
    glBindTexture(GL_TEXTURE_2D, texture != 0 ? texture : g_whiteTex);
    if (texture != 0) {
        SetTextureFilter(state);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GlAddress(state.addressU));
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GlAddress(state.addressV));
    }
}

void DrawPrimitive(Primitive primitive, const Vertex* vertices, int count, const uint16_t* indices, int indexCount,
                   const float* model, const float* colorScale, const DrawState& state) {
    if (!g_ready || count <= 0) return;
    if (indices != nullptr && indexCount <= 0) return;
    static const float kIdentity[16] = {1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1};
    static const float kOne[4] = {1, 1, 1, 1};
    BindCurrent();
    glUseProgram(g_imProgram);
    glUniformMatrix4fv(g_imViewProj, 1, 0, g_viewProj);
    glUniformMatrix4fv(g_imModel, 1, 0, model != nullptr ? model : kIdentity);
    glUniform4fv(g_imColorScale, 1, colorScale != nullptr ? colorScale : kOne);
    glUniform1i(g_imTex, 0);
    glUniform1i(g_imUseTex, state.texture != 0 ? 1 : 0);
    glUniform4f(g_imAlphaTest, state.alphaTest ? static_cast<float>(state.alphaFunc) : 7.0f, state.alphaRef, 0, 0);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, state.texture != 0 ? state.texture : g_whiteTex);
    if (state.texture != 0) {
        SetTextureFilter(state);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GlAddress(state.addressU));
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GlAddress(state.addressV));
    }
    ApplyState(state);
    glBindVertexArray(g_imVao);
    glBindBuffer(GL_ARRAY_BUFFER, g_imVbo);
    glBufferData(GL_ARRAY_BUFFER, static_cast<GLsizeiptr>(count) * sizeof(Vertex), vertices, GL_STREAM_DRAW);
    if (indices != nullptr) {
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, static_cast<GLsizeiptr>(indexCount) * sizeof(uint16_t), indices,
                     GL_STREAM_DRAW);
        glDrawElements(GlPrimitive(primitive), indexCount, GL_UNSIGNED_SHORT, nullptr);
    } else {
        glDrawArrays(GlPrimitive(primitive), 0, count);
    }
    glBindVertexArray(0);
    glDepthMask(1);
}

void DrawQuad(uint32_t texture, float x0, float y0, float x1, float y1, uint32_t rgba) {
    if (!g_ready) return;
    float nx0, ny0, nx1, ny1;
    ToNdc(x0, y1, &nx0, &ny0);  // bottom-left
    ToNdc(x1, y0, &nx1, &ny1);  // top-right
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glUseProgram(g_quadProgram);
    glUniform4f(g_quadRect, nx0, ny0, nx1, ny1);
    glUniform4f(g_quadColor, ((rgba >> 24) & 0xff) / 255.0f, ((rgba >> 16) & 0xff) / 255.0f,
                ((rgba >> 8) & 0xff) / 255.0f, (rgba & 0xff) / 255.0f);
    glUniform1i(g_quadTex, 0);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture ? texture : g_whiteTex);
    glBindVertexArray(g_vao);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
}

bool ReadTarget(uint8_t* rgba) {
    if (!g_ready) return false;
    std::vector<uint8_t> rows(static_cast<size_t>(g_width) * g_height * 4);
    glBindFramebuffer(GL_FRAMEBUFFER, g_fbo);
    glPixelStorei(GL_PACK_ALIGNMENT, 1);
    glReadPixels(0, 0, g_width, g_height, GL_RGBA, GL_UNSIGNED_BYTE, rows.data());
    const size_t stride = static_cast<size_t>(g_width) * 4;
    for (int y = 0; y < g_height; ++y)  // GL's row 0 is the bottom
        std::memcpy(rgba + static_cast<size_t>(y) * stride, rows.data() + static_cast<size_t>(g_height - 1 - y) * stride, stride);
    return true;
}

bool SaveScreenshot(const char* path) {
    if (!g_ready) return false;
    std::vector<uint8_t> rgba(static_cast<size_t>(g_width) * g_height * 4);
    if (!ReadTarget(rgba.data())) return false;
    std::vector<uint8_t> rgb(static_cast<size_t>(g_width) * g_height * 3);
    for (size_t i = 0, n = static_cast<size_t>(g_width) * g_height; i < n; ++i) std::memcpy(&rgb[i * 3], &rgba[i * 4], 3);
    return WritePngRgb(path, g_width, g_height, rgb.data());
}

uint32_t FrameCount() { return g_frames; }

void EndFrame() {
    if (!g_ready) return;
    ++g_frames;
    MaybeScreenshot();
    int ww = 0, wh = 0;
    platform::sdl::GetDrawableSize(&ww, &wh);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glViewport(0, 0, ww, wh);
    glDisable(GL_BLEND);
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    // letterbox: keep the internal aspect ratio
    int vw = ww, vh = ww * g_height / g_width;
    if (vh > wh) {
        vh = wh;
        vw = wh * g_width / g_height;
    }
    glViewport((ww - vw) / 2, (wh - vh) / 2, vw, vh);
    glUseProgram(g_blitProgram);
    glUniform1f(g_blitGamma, platform::GetVideoOutGamma());
    glUniform1i(g_blitTex, 0);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, g_colorTex);
    glBindVertexArray(g_vao);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    platform::sdl::SwapWindow();
}

}  // namespace dotd::gfx
