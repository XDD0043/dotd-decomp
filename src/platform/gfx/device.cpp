// device.cpp - the OpenGL 3.3 core backend (see device.h). New platform code.
#include "platform/gfx/device.h"

#include <algorithm>
#include <atomic>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <unordered_map>
#include <vector>

#include "platform/cell/videoout.h"
#include "platform/gfx/cg_program.h"
#include "platform/gfx/gl.h"
#include "platform/gfx/gpuprof.h"
#include "platform/gfx/mesh.h"
#include "platform/gfx/perf.h"
#include "platform/gfx/png.h"
#include "platform/gfx/texture_transcode.h"
#include "platform/log.h"
#include "platform/sdl/app.h"

using namespace dotd::gfx::gl;

namespace dotd::gfx {

namespace {
// The internal target: g_baseWidth x g_baseHeight is the size the game knows (InternalWidth / InternalHeight, the
// PS3's 1280x720), g_width x g_height its pixels, smaller under a resolution scale (SetResolutionScale).
int g_width = 0;
int g_height = 0;
int g_baseWidth = 0;
int g_baseHeight = 0;
float g_scale = 1.0f;
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
std::atomic<bool> g_transcodeAstc{false};
std::atomic<bool> g_astcBench{false};  // TranscodeDxtToAstc (device.h): set by Init, read by the loader thread
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
    int width = 0;   // pixels
    int height = 0;
    bool screenSized = false;  // asked for at the internal target's size: follows the resolution scale
};
std::vector<RenderTarget> g_targets;
uint32_t g_currentTarget = 0;
bool g_frontCW = false;

// The frame buffer binding and the viewport as the backend last set them (perf, like the texture state shadow below:
// every glBindFramebuffer / glViewport / glDeleteFramebuffers of the backend goes through these three).
bool g_fboKnown = false;
GLuint g_boundFbo = 0;
bool g_viewportKnown = false;
GLint g_viewport[4] = {};

void GlBindFramebuffer(GLuint fbo) {
    if (g_fboKnown && g_boundFbo == fbo) return;
    glBindFramebuffer(GL_FRAMEBUFFER, fbo);
    perf::Add(perf::kTargetBinds);
    g_boundFbo = fbo;
    g_fboKnown = true;
}

void GlViewport(GLint x, GLint y, GLsizei w, GLsizei h) {
    if (g_viewportKnown && g_viewport[0] == x && g_viewport[1] == y && g_viewport[2] == w && g_viewport[3] == h) return;
    glViewport(x, y, w, h);
    g_viewport[0] = x;
    g_viewport[1] = y;
    g_viewport[2] = w;
    g_viewport[3] = h;
    g_viewportKnown = true;
}

void GlDeleteFramebuffer(GLuint fbo) {
    glDeleteFramebuffers(1, &fbo);
    if (g_fboKnown && g_boundFbo == fbo) g_boundFbo = 0;  // GL: deleting the bound frame buffer binds 0
}

// The GL state shadow (perf; mesh.h "GL state shadow"): the active unit, the GL_TEXTURE_2D binding of the units
// 0..kShadowUnits-1, the min / mag filter and S / T wrap of the textures, and the blend / depth / cull states, as the
// backend last set them. Every call of the backend that sets one of them goes through the Gl* functions below (mesh.h),
// so a call that would set what GL already has is skipped and ActiveTextureUnit needs no glGetIntegerv. Unknown (before
// Init, a unit above the shadowed ones, a texture name above kShadowTextureNames) means: call GL.
constexpr int kShadowUnits = 32;
// The active texture unit is set lazily (perf): g_activeUnit is the unit the backend asked for (what ActiveTextureUnit
// answers), g_glActiveUnit the one GL has. glActiveTexture is only called when a call that depends on the unit follows
// (FlushActiveUnit: before glBindTexture, glTexParameter and, through GlFlushActiveTexture, the texture image calls), so
// selecting a unit whose texture and sampler state are already what the draw wants costs no GL call.
int g_activeUnit = -1;    // -1: unknown
int g_glActiveUnit = -1;  // -1: unknown
GLuint g_unitTexture[kShadowUnits] = {};
uint32_t g_unitKnown = 0;  // bit u: g_unitTexture[u] is what unit u has
struct TextureParams {
    GLint value[4] = {};  // min filter, mag filter, wrap S, wrap T
    uint8_t known = 0;    // bit i: value[i] is the texture's
    // perf: the sampler state BindTextureUnit last applied in full (SamplerKey; 0: none, or changed since by another
    // call): the same key again needs no parameter call at all.
    uint32_t samplerKey = 0;
};
constexpr GLuint kShadowTextureNames = 1u << 20;
std::vector<TextureParams> g_textureParams;  // by texture name
struct FixedState {
    int8_t blend = -1, depthTest = -1, cullFace = -1, depthMask = -1;  // -1: unknown
    GLenum blendSrc = 0, blendDst = 0, depthFunc = 0, frontFace = 0, cullMode = 0;
    bool blendFuncKnown = false, depthFuncKnown = false, frontFaceKnown = false, cullModeKnown = false;
};
FixedState g_fixed;

// The program and vertex array object bindings as the backend last set them (perf; mesh.h GlUseProgram /
// GlBindVertexArray). They are never set back to 0 between draws: every draw path binds its own program and vertex
// array first, so an unbind followed by the next draw's bind is two calls for nothing.
bool g_programKnown = false;
GLuint g_program = 0;
bool g_vaoKnown = false;
GLuint g_boundVao = 0;

// The alpha test uniforms of the uber-shader programs (mesh.h SetAlphaTest), by GL program.
struct AlphaTestUniforms {
    GLint funcLocation = -1;
    GLint refLocation = -1;
    int func = 0;
    float ref = 0.0f;
    bool funcKnown = false;
    bool refKnown = false;
};
std::unordered_map<GLuint, AlphaTestUniforms> g_alphaTest;  // (node-based: entries never move)
GLuint g_alphaTestLastProgram = 0;
AlphaTestUniforms* g_alphaTestLast = nullptr;

// The device's immediate-geometry program's uniforms as last uploaded (perf: DrawPrimitive uploads only what changed;
// nothing else writes them).
struct ImUniforms {
    float viewProj[16];
    float model[16];
    float colorScale[4];
    float alphaTest[2];
    int useTex = -1;
    bool known = false;
};
ImUniforms g_imUniforms;

void ForgetGlState() {
    g_fboKnown = false;
    g_viewportKnown = false;
    g_activeUnit = -1;
    g_glActiveUnit = -1;
    g_unitKnown = 0;
    g_textureParams.clear();
    g_fixed = FixedState();
    g_programKnown = false;
    g_program = 0;
    g_vaoKnown = false;
    g_boundVao = 0;
    g_alphaTest.clear();
    g_alphaTestLast = nullptr;
    g_alphaTestLastProgram = 0;
    g_imUniforms = ImUniforms();
}

// glActiveTexture, when GL's unit is not the one the backend selected (see g_activeUnit).
void FlushActiveUnit() {
    if (g_activeUnit < 0 || g_glActiveUnit == g_activeUnit) return;
    glActiveTexture(GL_TEXTURE0 + static_cast<GLenum>(g_activeUnit));
    g_glActiveUnit = g_activeUnit;
}

// Binds the frame buffer of the current target with its viewport. PERF: the binding is made by what draws or clears
// (DrawPrimitive, BindTarget, ClearTarget, DrawQuad, the video planes), not when the target is chosen: a camera's end
// selects the internal target again and the next camera's begin often another one at once, and a frame buffer bound
// without a draw into it is a switch for nothing (costly on tile-based GPUs).
void BindCurrent() {
    if (g_currentTarget != 0 && g_currentTarget <= g_targets.size() && g_targets[g_currentTarget - 1].fbo != 0) {
        const RenderTarget& t = g_targets[g_currentTarget - 1];
        GlBindFramebuffer(t.fbo);
        GlViewport(0, 0, t.width, t.height);
        return;
    }
    GlBindFramebuffer(g_fbo);
    GlViewport(0, 0, g_width, g_height);
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
    const std::string text = gl::ShaderSourceForContext(src);
    src = text.c_str();
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
void SetDefaultSampler(GLint filter) {
    GlTexParameter2D(GL_TEXTURE_MIN_FILTER, filter);
    GlTexParameter2D(GL_TEXTURE_MAG_FILTER, filter);
    GlTexParameter2D(GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    GlTexParameter2D(GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
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

void ApplySamplerState(uint32_t texture, const DrawState& state);  // below

bool Init(int internalWidth, int internalHeight) {
    if (!gl::Load(platform::sdl::GetGLProcAddress)) return false;
    DOTD_LOG("gfx: %s / %s", reinterpret_cast<const char*>(glGetString(GL_RENDERER)),
             reinterpret_cast<const char*>(glGetString(GL_VERSION)));
    g_baseWidth = g_width = internalWidth;
    g_baseHeight = g_height = internalHeight;
    g_scale = 1.0f;
    if (const char* scale = std::getenv("DOTD_RES_SCALE")) {  // the resolution scale from the start (device.h)
        g_scale = std::min(1.0f, std::max(0.25f, static_cast<float>(std::atof(scale))));
        g_width = std::max(1, static_cast<int>(g_baseWidth * g_scale + 0.5f));
        g_height = std::max(1, static_cast<int>(g_baseHeight * g_scale + 0.5f));
    }
    gpuprof::Init();
    // (WebGL2 names the same formats WEBGL_compressed_texture_s3tc.)
    g_s3tc = HasExtension("GL_EXT_texture_compression_s3tc") || HasExtension("GL_WEBGL_compressed_texture_s3tc");
#ifdef __EMSCRIPTEN__
    {
        // No S3TC (a phone): the DXT textures as ASTC 4x4 where the browser has it (texture_transcode.h).
        const char* astc = std::getenv("DOTD_ASTC");
        const bool wanted = astc == nullptr || std::strcmp(astc, "0") != 0;
        const bool astcThere = HasExtension("GL_WEBGL_compressed_texture_astc") || HasExtension("GL_KHR_texture_compression_astc_ldr");
        g_transcodeAstc = !g_s3tc && wanted && astcThere && AstcTranscodeReady();
        g_astcBench = g_s3tc && astc != nullptr && std::strcmp(astc, "bench") == 0 && AstcTranscodeReady();
        if (g_astcBench) {
            g_transcodeAstc = true;
            DOTD_LOG("gfx: DOTD_ASTC=bench: the DXT textures are transcoded to ASTC and timed, the DXT kept");
        }
        if (!g_s3tc) {
            DOTD_LOG("gfx: no S3TC: the DXT textures go to the GPU %s",
                     g_transcodeAstc ? "as ASTC 4x4, transcoded on the loader thread"
                                     : !astcThere ? "as RGBA8 (no ASTC either)" : !wanted ? "as RGBA8 (DOTD_ASTC=0)"
                                                                                           : "as RGBA8 (no transcoder in this build)");
        }
    }
#endif
    ForgetGlState();
    ForgetVertexAttribDefaults(~0u);
    perf::Init(platform::sdl::GetGLProcAddress);
    {
        GLint unit = GL_TEXTURE0;
        glGetIntegerv(GL_ACTIVE_TEXTURE, &unit);
        g_activeUnit = static_cast<int>(unit - GL_TEXTURE0);
        g_glActiveUnit = g_activeUnit;
    }

    glGenTextures(1, &g_colorTex);
    GlBindTexture2D(g_colorTex);
    GlFlushActiveTexture();
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, g_width, g_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
    SetDefaultSampler(GL_LINEAR);
    glGenRenderbuffers(1, &g_depthRb);
    glBindRenderbuffer(GL_RENDERBUFFER, g_depthRb);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, g_width, g_height);
    glGenFramebuffers(1, &g_fbo);
    GlBindFramebuffer(g_fbo);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, g_colorTex, 0);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, g_depthRb);
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
        DOTD_LOG("gfx: internal target incomplete");
        return false;
    }
    GlBindFramebuffer(0);

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
    GlBindVertexArray(g_imVao);
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
    GlUseProgram(g_imProgram);
    glUniform1i(g_imTex, 0);  // the sampler's unit: set once

    DOTD_LOG("gfx: internal target %dx%d (%dx%d pixels), S3TC %s", g_baseWidth, g_baseHeight, g_width, g_height,
             g_s3tc ? "native" : TranscodeDxtToAstc() ? "absent (ASTC 4x4 instead)" : "decoded on the CPU");
    g_ready = glGetError() == GL_NO_ERROR;
    return g_ready;
}

bool IsReady() { return g_ready; }
bool TranscodeDxtToAstc() { return g_transcodeAstc.load(std::memory_order_acquire); }
bool AstcBenchOnly() { return g_astcBench.load(std::memory_order_acquire); }

int InternalWidth() { return g_baseWidth; }
int InternalHeight() { return g_baseHeight; }

float ResolutionScale() { return g_scale; }

void SetColorWrite(bool on) {
    if (g_ready) glColorMask(on ? 1 : 0, on ? 1 : 0, on ? 1 : 0, on ? 1 : 0);
}

void SetResolutionScale(float scale) {
    if (!g_ready) return;
    scale = std::min(1.0f, std::max(0.25f, scale));
    const int width = std::max(1, static_cast<int>(g_baseWidth * scale + 0.5f));
    const int height = std::max(1, static_cast<int>(g_baseHeight * scale + 0.5f));
    g_scale = scale;
    if (width == g_width && height == g_height) return;
    g_width = width;
    g_height = height;
    // The storage of the internal target, its depth buffer and every screen-sized target made again at the new size
    // (the ids, textures and frame buffers stay: the game does not notice; the contents are lost for one frame).
    auto resize = [&](GLuint texture, GLuint fbo) {
        GlBindTexture2D(texture);
        GlFlushActiveTexture();
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
        GlBindFramebuffer(fbo);
        GlViewport(0, 0, width, height);
        glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT);
    };
    glBindRenderbuffer(GL_RENDERBUFFER, g_depthRb);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
    resize(g_colorTex, g_fbo);
    for (RenderTarget& t : g_targets) {
        if (t.fbo == 0 || !t.screenSized) continue;
        t.width = width;
        t.height = height;
        resize(t.texture, t.fbo);
    }
    BindCurrent();
    DOTD_LOG("gfx: resolution scale %.2f: %dx%d pixels", scale, width, height);
}

void Shutdown() {
    if (!g_ready) return;
    perf::Shutdown();
    ReleaseStreamMeshes();  // mesh.h: while the context and IsReady() are still there
    g_ready = false;
    if (g_vao) GlDeleteVertexArray(g_vao);
    if (g_imVao) GlDeleteVertexArray(g_imVao);
    if (g_imVbo) glDeleteBuffers(1, &g_imVbo);
    if (g_imIbo) glDeleteBuffers(1, &g_imIbo);
    if (g_quadProgram) glDeleteProgram(g_quadProgram);
    if (g_blitProgram) glDeleteProgram(g_blitProgram);
    if (g_imProgram) glDeleteProgram(g_imProgram);
    if (g_whiteTex) GlDeleteTexture(g_whiteTex);
    if (g_colorTex) GlDeleteTexture(g_colorTex);
    if (g_depthRb) glDeleteRenderbuffers(1, &g_depthRb);
    if (g_fbo) GlDeleteFramebuffer(g_fbo);
    for (RenderTarget& t : g_targets) {
        if (t.fbo) GlDeleteFramebuffer(t.fbo);
        if (t.texture) GlDeleteTexture(t.texture);
    }
    g_targets.clear();
    ForgetGlState();
    ForgetVertexAttribDefaults(~0u);
    g_currentTarget = 0;
    g_vao = g_imVao = g_imVbo = g_imIbo = 0;
    g_quadProgram = g_blitProgram = g_imProgram = g_whiteTex = g_colorTex = g_depthRb = g_fbo = 0;
}

void BeginFrame() {
    if (!g_ready) return;
    GlCap(GL_DEPTH_TEST, false);
    GlCap(GL_CULL_FACE, false);
}

void Clear(float r, float g, float b, float a) { ClearTarget(true, true, r, g, b, a); }

uint32_t CreateRenderTarget(int width, int height) {
    if (!g_ready || width <= 0 || height <= 0) return 0;
    RenderTarget t;
    t.screenSized = width == g_baseWidth && height == g_baseHeight;
    if (t.screenSized) {  // (the resolution scale)
        width = g_width;
        height = g_height;
    }
    t.width = width;
    t.height = height;
    glGenTextures(1, &t.texture);
    GlBindTexture2D(t.texture);
    GlFlushActiveTexture();
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, 0);
    SetDefaultSampler(GL_LINEAR);
    glGenFramebuffers(1, &t.fbo);
    GlBindFramebuffer(t.fbo);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, t.texture, 0);
    if (t.screenSized)
        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, g_depthRb);
    const bool complete = glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE;
    if (complete) {
        // A new camera texture starts black (the PS3's video memory is not cleared either; black keeps the first
        // frames deterministic).
        GlViewport(0, 0, width, height);
        glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT);
    }
    if (!complete) {
        DOTD_LOG("gfx: render target %dx%d incomplete", width, height);
        GlDeleteFramebuffer(t.fbo);
        GlDeleteTexture(t.texture);
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
    if (t.fbo != 0) GlDeleteFramebuffer(t.fbo);
    if (t.texture != 0) GlDeleteTexture(t.texture);
    t = RenderTarget();
    if (g_currentTarget == target) g_currentTarget = 0;
}

uint32_t RenderTargetTexture(uint32_t target) {
    if (target == 0) return g_colorTex;
    if (target > g_targets.size()) return 0;
    return g_targets[target - 1].texture;
}

void SetRenderTarget(uint32_t target) {
    if (target > g_targets.size() || (target != 0 && g_targets[target - 1].fbo == 0)) target = 0;
    g_currentTarget = target;  // (bound by the next draw or clear: BindCurrent)
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
        GlDepthMask(true);
        mask |= GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT;
    }
    if (mask != 0) glClear(mask);
}

uint32_t CreateTexture(TextureFormat format, int width, int height, int levelCount, const TextureLevel* levels) {
    if (!g_ready || width <= 0 || height <= 0 || levelCount <= 0) return 0;
    GLuint t = 0;
    glGenTextures(1, &t);
    GlBindTexture2D(t);
    GlFlushActiveTexture();
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    int w = width, h = height;
#ifdef __EMSCRIPTEN__
    // WebGL takes a compressed image only when its top level's sides are multiples of 4; the others are decoded.
    const bool s3tc = g_s3tc && (width & 3) == 0 && (height & 3) == 0;
#else
    const bool s3tc = g_s3tc;
#endif
    for (int level = 0; level < levelCount; ++level) {
        const auto* data = static_cast<const uint8_t*>(levels[level].data);
        switch (format) {
            case TextureFormat::kRGBA8:
                glTexImage2D(GL_TEXTURE_2D, level, GL_RGBA8, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
                break;
            case TextureFormat::kR8:
                glTexImage2D(GL_TEXTURE_2D, level, GL_R8, w, h, 0, GL_RED, GL_UNSIGNED_BYTE, data);
                break;
            case TextureFormat::kASTC4x4:  // (GL_COMPRESSED_RGBA_ASTC_4x4_KHR)
                glCompressedTexImage2D(GL_TEXTURE_2D, level, 0x93B0, w, h, 0, static_cast<GLsizei>(levels[level].size), data);
                break;
            case TextureFormat::kBC1:
            case TextureFormat::kBC2:
            case TextureFormat::kBC3:
                if (s3tc) {
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
#ifndef __EMSCRIPTEN__
    // (WebGL 2 has no LOD bias parameter: there the translated pixel shaders' lookups carry it, cg_to_glsl.cpp.)
    if (levelCount > 1) glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_LOD_BIAS, kPsglLodBias);
#endif
    SetDefaultSampler(GL_LINEAR);
    return t;
}

uint32_t CreateTextureRGBA8(int width, int height, const void* pixels, bool linearFilter) {
    GLuint t = 0;
    glGenTextures(1, &t);
    GlBindTexture2D(t);
    GlFlushActiveTexture();
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, 0);
    SetDefaultSampler(linearFilter ? GL_LINEAR : GL_NEAREST);
    return t;
}

void SetTextureMaxLod(uint32_t texture, float lod) {
    if (!g_ready || texture == 0) return;
    GlBindTexture2D(texture);
    GlFlushActiveTexture();
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_LOD, lod);
}

void DestroyTexture(uint32_t texture) {
    GLuint t = texture;
    if (t && g_ready) GlDeleteTexture(t);
}

// The bound texture's min / mag filters for a state (see DrawState::filterMode).
void SetTextureFilter(const DrawState& state) {
    static const GLint kMin[7] = {0, GL_NEAREST, GL_LINEAR, GL_NEAREST_MIPMAP_NEAREST, GL_LINEAR_MIPMAP_NEAREST,
                                  GL_NEAREST_MIPMAP_LINEAR, GL_LINEAR_MIPMAP_LINEAR};
    static const GLint kMag[7] = {0, GL_NEAREST, GL_LINEAR, GL_NEAREST, GL_LINEAR, GL_NEAREST, GL_LINEAR};
    if (state.filterMode >= 1 && state.filterMode <= 6) {
        GlTexParameter2D(GL_TEXTURE_MIN_FILTER, kMin[state.filterMode]);
        GlTexParameter2D(GL_TEXTURE_MAG_FILTER, kMag[state.filterMode]);
        return;
    }
    GLint minFilter = state.linear ? GL_LINEAR : GL_NEAREST;
    if (state.mipmaps) minFilter = state.linear ? GL_LINEAR_MIPMAP_LINEAR : GL_NEAREST_MIPMAP_NEAREST;
    GlTexParameter2D(GL_TEXTURE_MIN_FILTER, minFilter);
    GlTexParameter2D(GL_TEXTURE_MAG_FILTER, state.linear ? GL_LINEAR : GL_NEAREST);
}

// The sampler part of a state (filter, mips, addressing) as one word, never 0.
uint32_t SamplerKey(const DrawState& state) {
    return 0x80000000u | static_cast<uint32_t>(state.filterMode) | (state.linear ? 0x100u : 0u) |
           (state.mipmaps ? 0x200u : 0u) | (static_cast<uint32_t>(state.addressU) << 12) |
           (static_cast<uint32_t>(state.addressV) << 16);
}

// The sampler state of `state` on `texture`, bound on the active unit: the filters and the addressing (GlTexParameter2D
// skips what the texture already has); nothing at all when the texture's last full sampler state was this one.
void ApplySamplerState(uint32_t texture, const DrawState& state) {
    const uint32_t key = SamplerKey(state);
    const bool shadowed = texture < kShadowTextureNames;
    if (shadowed && texture < g_textureParams.size() && g_textureParams[texture].samplerKey == key) return;
    SetTextureFilter(state);
    GlTexParameter2D(GL_TEXTURE_WRAP_S, GlAddress(state.addressU));
    GlTexParameter2D(GL_TEXTURE_WRAP_T, GlAddress(state.addressV));
    // (GlTexParameter2D made the entry when the unit's binding is known; a change clears the key, so it is set last)
    if (shadowed && texture < g_textureParams.size() && g_activeUnit >= 0 && g_activeUnit < kShadowUnits &&
        (g_unitKnown & (1u << g_activeUnit)) != 0 && g_unitTexture[g_activeUnit] == texture &&
        g_textureParams[texture].known == 0xf) {
        g_textureParams[texture].samplerKey = key;
    }
}

void ApplyState(const DrawState& state) {
    if (!g_ready) return;
    if (state.blend) {
        GlCap(GL_BLEND, true);
        GlBlendFunc(GlBlend(state.srcBlend), GlBlend(state.dstBlend));
    } else {
        GlCap(GL_BLEND, false);
    }
    if (state.depthTest) {
        GlCap(GL_DEPTH_TEST, true);
        GlDepthFunc(GL_LEQUAL);
    } else {
        GlCap(GL_DEPTH_TEST, false);
    }
    GlDepthMask(state.depthWrite);
    if (state.cull == 0) {
        GlCap(GL_CULL_FACE, false);
    } else {
        GlCap(GL_CULL_FACE, true);
        GlFrontFace(g_frontCW ? GL_CW : GL_CCW);
        GlCullFace(state.cull == 1 ? GL_BACK : GL_FRONT);
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
    GlActiveTexture(unit);
    GlBindTexture2D(texture != 0 ? texture : g_whiteTex);
    if (texture != 0) ApplySamplerState(texture, state);
}

int ActiveTextureUnit() {
    if (!g_ready) return 0;
    if (g_activeUnit >= 0) return g_activeUnit;  // the shadow (GlActiveTexture)
    GLint unit = GL_TEXTURE0;
    glGetIntegerv(GL_ACTIVE_TEXTURE, &unit);
    g_activeUnit = static_cast<int>(unit - GL_TEXTURE0);
    g_glActiveUnit = g_activeUnit;
    return g_activeUnit;
}

void SetActiveTextureUnit(int unit) {
    if (!g_ready) return;
    GlActiveTexture(unit);
}

void GlActiveTexture(int unit) { g_activeUnit = unit; }  // lazily: FlushActiveUnit

void GlFlushActiveTexture() { FlushActiveUnit(); }

void GlUseProgram(uint32_t program) {
    if (g_programKnown && g_program == program) return;
    glUseProgram(program);
    perf::Add(perf::kPrograms);
    g_program = program;
    g_programKnown = true;
}

void GlBindVertexArray(uint32_t vao) {
    if (g_vaoKnown && g_boundVao == vao) return;
    glBindVertexArray(vao);
    perf::Add(perf::kVaoBinds);
    g_boundVao = vao;
    g_vaoKnown = true;
}

void GlDeleteVertexArray(uint32_t vao) {
    GLuint name = vao;
    glDeleteVertexArrays(1, &name);
    if (g_vaoKnown && g_boundVao == vao) g_boundVao = 0;  // GL: deleting the bound vertex array object binds 0
}

void ForgetPrograms() {
    if (!g_ready) return;
    // The programs are being deleted: their names may be given out again. GL keeps a deleted program that is current
    // alive until another one is bound, so the binding is given up here.
    glUseProgram(0);
    g_program = 0;
    g_programKnown = true;
    g_alphaTest.clear();
    g_alphaTestLast = nullptr;
    g_alphaTestLastProgram = 0;
}

void SetAlphaTest(uint32_t program, int func, float ref) {
    if (!g_ready || program == 0) return;
    AlphaTestUniforms* u = g_alphaTestLast;
    if (u == nullptr || g_alphaTestLastProgram != program) {
        auto found = g_alphaTest.find(program);
        if (found == g_alphaTest.end()) {
            AlphaTestUniforms entry;
            entry.funcLocation = glGetUniformLocation(program, "dotd_alphaFunc");
            entry.refLocation = glGetUniformLocation(program, "dotd_alphaRef");
            found = g_alphaTest.emplace(program, entry).first;
        }
        u = &found->second;
        g_alphaTestLast = u;
        g_alphaTestLastProgram = program;
    }
    if (u->funcLocation >= 0 && !(u->funcKnown && u->func == func)) {
        GlUseProgram(program);
        glUniform1i(u->funcLocation, func);
        perf::Add(perf::kUniforms);
        u->func = func;
        u->funcKnown = true;
    }
    if (u->refLocation >= 0 && !(u->refKnown && std::memcmp(&u->ref, &ref, sizeof ref) == 0)) {
        GlUseProgram(program);
        glUniform1f(u->refLocation, ref);
        perf::Add(perf::kUniforms);
        u->ref = ref;
        u->refKnown = true;
    }
}

void GlBindTexture2D(uint32_t texture) {
    const int unit = g_activeUnit;
    if (unit < 0 || unit >= kShadowUnits) {
        FlushActiveUnit();
        glBindTexture(GL_TEXTURE_2D, texture);
        perf::Add(perf::kTextureBinds);
        if (unit < 0) g_unitKnown = 0;  // an unknown unit: any of them may have changed
        return;
    }
    const uint32_t bit = 1u << unit;
    if ((g_unitKnown & bit) != 0 && g_unitTexture[unit] == texture) return;
    FlushActiveUnit();
    glBindTexture(GL_TEXTURE_2D, texture);
    perf::Add(perf::kTextureBinds);
    g_unitTexture[unit] = texture;
    g_unitKnown |= bit;
}

void GlTexParameter2D(uint32_t pname, int value) {
    int index = -1;
    switch (pname) {
        case GL_TEXTURE_MIN_FILTER: index = 0; break;
        case GL_TEXTURE_MAG_FILTER: index = 1; break;
        case GL_TEXTURE_WRAP_S: index = 2; break;
        case GL_TEXTURE_WRAP_T: index = 3; break;
        default: break;
    }
    const int unit = g_activeUnit;
    const bool bound = unit >= 0 && unit < kShadowUnits && (g_unitKnown & (1u << unit)) != 0;
    if (index < 0 || !bound) {
        FlushActiveUnit();
        glTexParameteri(GL_TEXTURE_2D, pname, value);
        if (index >= 0) g_textureParams.clear();  // a texture the shadow cannot name changed
        return;
    }
    const GLuint texture = g_unitTexture[unit];
    if (texture >= kShadowTextureNames) {
        FlushActiveUnit();
        glTexParameteri(GL_TEXTURE_2D, pname, value);
        return;
    }
    if (texture >= g_textureParams.size()) g_textureParams.resize(texture + 1);
    TextureParams& params = g_textureParams[texture];
    const uint8_t bit = static_cast<uint8_t>(1u << index);
    if ((params.known & bit) != 0 && params.value[index] == value) return;
    FlushActiveUnit();
    glTexParameteri(GL_TEXTURE_2D, pname, value);
    perf::Add(perf::kSamplerParams);
    params.value[index] = value;
    params.known |= bit;
    params.samplerKey = 0;  // (ApplySamplerState sets it again after a full state)
}

void GlDeleteTexture(uint32_t texture) {
    GLuint name = texture;
    glDeleteTextures(1, &name);
    // GL: a deleted texture bound to a unit of the context leaves that unit bound to 0.
    for (int unit = 0; unit < kShadowUnits; ++unit) {
        if ((g_unitKnown & (1u << unit)) != 0 && g_unitTexture[unit] == texture) g_unitTexture[unit] = 0;
    }
    if (texture < g_textureParams.size()) g_textureParams[texture] = TextureParams();
}

void GlCap(uint32_t cap, bool on) {
    int8_t* known = cap == GL_BLEND ? &g_fixed.blend : cap == GL_DEPTH_TEST ? &g_fixed.depthTest : cap == GL_CULL_FACE ? &g_fixed.cullFace : nullptr;
    if (known != nullptr && *known == (on ? 1 : 0)) return;
    if (on) glEnable(cap);
    else glDisable(cap);
    if (known != nullptr) *known = on ? 1 : 0;
}

void GlBlendFunc(uint32_t src, uint32_t dst) {
    if (g_fixed.blendFuncKnown && g_fixed.blendSrc == src && g_fixed.blendDst == dst) return;
    glBlendFunc(src, dst);
    g_fixed.blendSrc = src;
    g_fixed.blendDst = dst;
    g_fixed.blendFuncKnown = true;
}

void GlDepthFunc(uint32_t func) {
    if (g_fixed.depthFuncKnown && g_fixed.depthFunc == func) return;
    glDepthFunc(func);
    g_fixed.depthFunc = func;
    g_fixed.depthFuncKnown = true;
}

void GlDepthMask(bool write) {
    if (g_fixed.depthMask == (write ? 1 : 0)) return;
    glDepthMask(write ? 1 : 0);
    g_fixed.depthMask = write ? 1 : 0;
}

void GlFrontFace(uint32_t mode) {
    if (g_fixed.frontFaceKnown && g_fixed.frontFace == mode) return;
    glFrontFace(mode);
    g_fixed.frontFace = mode;
    g_fixed.frontFaceKnown = true;
}

void GlCullFace(uint32_t mode) {
    if (g_fixed.cullModeKnown && g_fixed.cullMode == mode) return;
    glCullFace(mode);
    g_fixed.cullMode = mode;
    g_fixed.cullModeKnown = true;
}

void DrawPrimitive(Primitive primitive, const Vertex* vertices, int count, const uint16_t* indices, int indexCount,
                   const float* model, const float* colorScale, const DrawState& state) {
    if (!g_ready || count <= 0) return;
    if (indices != nullptr && indexCount <= 0) return;
    static const float kIdentity[16] = {1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1};
    static const float kOne[4] = {1, 1, 1, 1};
    BindCurrent();
    GlUseProgram(g_imProgram);
    // The uniforms: only what differs from the last upload (g_imUniforms; the sampler's unit was set at Init).
    ImUniforms& u = g_imUniforms;
    const float* modelMatrix = model != nullptr ? model : kIdentity;
    const float* scale = colorScale != nullptr ? colorScale : kOne;
    const float alphaTest[2] = {state.alphaTest ? static_cast<float>(state.alphaFunc) : 7.0f, state.alphaRef};
    const int useTex = state.texture != 0 ? 1 : 0;
    if (!u.known || std::memcmp(u.viewProj, g_viewProj, sizeof u.viewProj) != 0) {
        glUniformMatrix4fv(g_imViewProj, 1, 0, g_viewProj);
        std::memcpy(u.viewProj, g_viewProj, sizeof u.viewProj);
        perf::Add(perf::kUniforms);
    }
    if (!u.known || std::memcmp(u.model, modelMatrix, sizeof u.model) != 0) {
        glUniformMatrix4fv(g_imModel, 1, 0, modelMatrix);
        std::memcpy(u.model, modelMatrix, sizeof u.model);
        perf::Add(perf::kUniforms);
    }
    if (!u.known || std::memcmp(u.colorScale, scale, sizeof u.colorScale) != 0) {
        glUniform4fv(g_imColorScale, 1, scale);
        std::memcpy(u.colorScale, scale, sizeof u.colorScale);
        perf::Add(perf::kUniforms);
    }
    if (!u.known || u.useTex != useTex) {
        glUniform1i(g_imUseTex, useTex);
        u.useTex = useTex;
        perf::Add(perf::kUniforms);
    }
    if (!u.known || std::memcmp(u.alphaTest, alphaTest, sizeof u.alphaTest) != 0) {
        glUniform4f(g_imAlphaTest, alphaTest[0], alphaTest[1], 0, 0);
        std::memcpy(u.alphaTest, alphaTest, sizeof u.alphaTest);
        perf::Add(perf::kUniforms);
    }
    u.known = true;
    GlActiveTexture(0);
    GlBindTexture2D(state.texture != 0 ? state.texture : g_whiteTex);
    if (state.texture != 0) ApplySamplerState(state.texture, state);
    ApplyState(state);
    GlBindVertexArray(g_imVao);
    glBindBuffer(GL_ARRAY_BUFFER, g_imVbo);
    glBufferData(GL_ARRAY_BUFFER, static_cast<GLsizeiptr>(count) * sizeof(Vertex), vertices, GL_STREAM_DRAW);
    perf::Add(perf::kDraws);
    perf::Add(perf::kBufferUploads, indices != nullptr ? 2 : 1);
    perf::Add(perf::kBufferBytes,
              static_cast<uint64_t>(count) * sizeof(Vertex) + (indices != nullptr ? static_cast<uint64_t>(indexCount) * 2 : 0));
    if (indices != nullptr) {
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, static_cast<GLsizeiptr>(indexCount) * sizeof(uint16_t), indices,
                     GL_STREAM_DRAW);
        glDrawElements(GlPrimitive(primitive), indexCount, GL_UNSIGNED_SHORT, nullptr);
    } else {
        glDrawArrays(GlPrimitive(primitive), 0, count);
    }
    ForgetVertexAttribDefaults(0x7u);  // g_imVao's arrays (slots 0..2): see DrawMesh
    GlDepthMask(true);
}

void DrawQuad(uint32_t texture, float x0, float y0, float x1, float y1, uint32_t rgba) {
    if (!g_ready) return;
    float nx0, ny0, nx1, ny1;
    ToNdc(x0, y1, &nx0, &ny0);  // bottom-left
    ToNdc(x1, y0, &nx1, &ny1);  // top-right
    BindCurrent();
    GlCap(GL_BLEND, true);
    GlBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    GlUseProgram(g_quadProgram);
    perf::Add(perf::kUniforms, 3);
    perf::Add(perf::kDraws);
    glUniform4f(g_quadRect, nx0, ny0, nx1, ny1);
    glUniform4f(g_quadColor, ((rgba >> 24) & 0xff) / 255.0f, ((rgba >> 16) & 0xff) / 255.0f,
                ((rgba >> 8) & 0xff) / 255.0f, (rgba & 0xff) / 255.0f);
    glUniform1i(g_quadTex, 0);
    GlActiveTexture(0);
    GlBindTexture2D(texture ? texture : g_whiteTex);
    GlBindVertexArray(g_vao);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
}

bool ReadTarget(uint8_t* rgba) {
    if (!g_ready) return false;
    std::vector<uint8_t> rows(static_cast<size_t>(g_width) * g_height * 4);
    GlBindFramebuffer(g_fbo);
    glPixelStorei(GL_PACK_ALIGNMENT, 1);
    glReadPixels(0, 0, g_width, g_height, GL_RGBA, GL_UNSIGNED_BYTE, rows.data());
    const size_t stride = static_cast<size_t>(g_width) * 4;
    if (g_width == g_baseWidth && g_height == g_baseHeight) {
        for (int y = 0; y < g_height; ++y)  // GL's row 0 is the bottom
            std::memcpy(rgba + static_cast<size_t>(y) * stride, rows.data() + static_cast<size_t>(g_height - 1 - y) * stride, stride);
        return true;
    }
    for (int y = 0; y < g_baseHeight; ++y) {  // under a resolution scale: the nearest pixel, at the size the game knows
        const int sy = g_height - 1 - y * g_height / g_baseHeight;
        for (int x = 0; x < g_baseWidth; ++x) {
            const int sx = x * g_width / g_baseWidth;
            std::memcpy(rgba + (static_cast<size_t>(y) * g_baseWidth + x) * 4, rows.data() + sy * stride + sx * 4, 4);
        }
    }
    return true;
}

bool SaveScreenshot(const char* path) {
    if (!g_ready) return false;
    const size_t n = static_cast<size_t>(g_baseWidth) * g_baseHeight;
    std::vector<uint8_t> rgba(n * 4);
    if (!ReadTarget(rgba.data())) return false;
    perf::CaptureNextFrame();  // DOTD_RDOC_ON_SHOT (perf.h)
    std::vector<uint8_t> rgb(n * 3);
    for (size_t i = 0; i < n; ++i) std::memcpy(&rgb[i * 3], &rgba[i * 4], 3);
    return WritePngRgb(path, g_baseWidth, g_baseHeight, rgb.data());
}

uint32_t FrameCount() { return g_frames; }

void EndFrame() {
    if (!g_ready) return;
    cg::PollBuilds();  // (the web build: the shader programs the browser finished building; nothing natively)
    ++g_frames;
    MaybeScreenshot();
    int ww = 0, wh = 0;
    platform::sdl::GetDrawableSize(&ww, &wh);
    GlBindFramebuffer(0);
    GlViewport(0, 0, ww, wh);
    GlCap(GL_BLEND, false);
    GlCap(GL_DEPTH_TEST, false);
    GlCap(GL_CULL_FACE, false);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    // letterbox: keep the internal aspect ratio
    int vw = ww, vh = ww * g_baseHeight / g_baseWidth;
    if (vh > wh) {
        vh = wh;
        vw = wh * g_baseWidth / g_baseHeight;
    }
    GlViewport((ww - vw) / 2, (wh - vh) / 2, vw, vh);
    GlUseProgram(g_blitProgram);
    glUniform1f(g_blitGamma, platform::GetVideoOutGamma());
    glUniform1i(g_blitTex, 0);
    GlActiveTexture(0);
    GlBindTexture2D(g_colorTex);
    GlBindVertexArray(g_vao);
    perf::Add(perf::kUniforms, 2);
    perf::Add(perf::kDraws);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    gpuprof::FrameEnd();
    perf::BeforePresent();
    platform::sdl::SwapWindow();
    perf::AfterPresent();
}

}  // namespace dotd::gfx
