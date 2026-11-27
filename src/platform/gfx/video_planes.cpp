// video_planes.cpp - see video_planes.h. The shaders are GLSL translations of the Cg sources the PS3 build
// compiles at run time (text at 0xa6f5c8 vertex, +0x300 opaque "NPA" pixel program, +0x558 alpha pixel
// program); the constants are copied from them.
#include "platform/gfx/video_planes.h"

#include "platform/gfx/device.h"
#include "platform/gfx/gl.h"
#include "platform/gfx/mesh.h"
#include "platform/log.h"

using namespace dotd::gfx::gl;

namespace dotd::gfx {

namespace {
constexpr GLenum kGlRed = 0x1903;            // GL_RED
constexpr GLenum kGlR8 = 0x8229;             // GL_R8
constexpr GLenum kGlUnpackRowLength = 0x0CF2;  // GL_UNPACK_ROW_LENGTH

// Vertex program (0xa6f5c8): In.Pos.xy *= Adjust.zw; In.Pos.xy += Adjust.xy. The unit quad of the PS3's VBO
// (0xc29788: positions (0,0,0) (1,0,0) (0,-1,0) (1,-1,0), UVs (0,0) (1,0) (0,1) (1,1)) comes from gl_VertexID.
const char* kVideoVS =
    "#version 330 core\n"
    "uniform vec4 Adjust;\n"
    "out vec2 vUV;\n"
    "void main() {\n"
    "  vec2 c = vec2(float(gl_VertexID & 1), float((gl_VertexID >> 1) & 1));\n"
    "  vUV = c;\n"
    "  vec2 pos = vec2(c.x, -c.y);\n"
    "  pos.x *= Adjust.z;\n"
    "  pos.y *= Adjust.w;\n"
    "  pos.x += Adjust.x;\n"
    "  pos.y += Adjust.y;\n"
    "  gl_Position = vec4(pos, 0.0, 1.0);\n"
    "}\n";
// Pixel programs (0xa6f8c8 "NPA" and 0xa6fb20): p = y * 1.164123535 + crc * cr + crb * cb + adj; p.w = 1 or
// the A plane; p *= Alpha.
const char* kVideoFS =
    "#version 330 core\n"
    "uniform sampler2D Yplane;\n"
    "uniform sampler2D cRplane;\n"
    "uniform sampler2D cBplane;\n"
    "uniform sampler2D Aplane;\n"
    "uniform vec4 Alpha;\n"
    "uniform int HasAplane;\n"
    "in vec2 vUV;\n"
    "out vec4 oColor;\n"
    "void main() {\n"
    "  const vec4 crc = vec4(1.595794678, -0.813476563, 0.0, 0.0);\n"
    "  const vec4 crb = vec4(0.0, -0.391448975, 2.017822266, 0.0);\n"
    "  const vec4 adj = vec4(-0.87065506, 0.529705048, -1.081668854, 0.0);\n"
    "  float y = texture(Yplane, vUV).x;\n"
    "  float cr = texture(cRplane, vUV).x;\n"
    "  float cb = texture(cBplane, vUV).x;\n"
    "  vec4 p = vec4(y * 1.164123535);\n"
    "  p += crc * cr;\n"
    "  p += crb * cb;\n"
    "  p += adj;\n"
    "  p.w = HasAplane != 0 ? texture(Aplane, vUV).x : 1.0;\n"
    "  p *= Alpha;\n"
    "  oColor = p;\n"
    "}\n";

GLuint g_program = 0;
GLuint g_vao = 0;
GLint g_adjust = -1, g_alpha = -1, g_hasA = -1;
bool g_failed = false;

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
        DOTD_LOG("gfx: video shader compile failed: %s", log);
    }
    return s;
}

bool EnsureProgram() {
    if (g_program != 0) return true;
    if (g_failed || !IsReady()) return false;
    GLuint p = glCreateProgram();
    GLuint v = Compile(GL_VERTEX_SHADER, kVideoVS);
    GLuint f = Compile(GL_FRAGMENT_SHADER, kVideoFS);
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
        DOTD_LOG("gfx: video program link failed: %s", log);
        glDeleteProgram(p);
        g_failed = true;
        return false;
    }
    g_program = p;
    g_adjust = glGetUniformLocation(p, "Adjust");
    g_alpha = glGetUniformLocation(p, "Alpha");
    g_hasA = glGetUniformLocation(p, "HasAplane");
    GlUseProgram(p);
    glUniform1i(glGetUniformLocation(p, "Yplane"), 0);
    glUniform1i(glGetUniformLocation(p, "cRplane"), 1);
    glUniform1i(glGetUniformLocation(p, "cBplane"), 2);
    glUniform1i(glGetUniformLocation(p, "Aplane"), 3);
    glGenVertexArrays(1, &g_vao);
    return true;
}
}  // namespace

uint32_t CreateTextureR8(int width, int height) {
    if (!IsReady()) return 0;
    GLuint t = 0;
    glGenTextures(1, &t);
    GlBindTexture2D(t);
    GlFlushActiveTexture();
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glTexImage2D(GL_TEXTURE_2D, 0, static_cast<GLint>(kGlR8), width, height, 0, kGlRed, GL_UNSIGNED_BYTE, nullptr);
    GlTexParameter2D(GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    GlTexParameter2D(GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    GlTexParameter2D(GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    GlTexParameter2D(GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    return t;
}

void UpdateTextureR8(uint32_t texture, int width, int height, const void* pixels, int pitch) {
    if (texture == 0 || !IsReady()) return;
    GlBindTexture2D(texture);
    GlFlushActiveTexture();
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glPixelStorei(kGlUnpackRowLength, pitch);
    glTexImage2D(GL_TEXTURE_2D, 0, static_cast<GLint>(kGlR8), width, height, 0, kGlRed, GL_UNSIGNED_BYTE, pixels);
    glPixelStorei(kGlUnpackRowLength, 0);
}

void DrawVideoPlanes(uint32_t y, uint32_t cr, uint32_t cb, uint32_t a, const float adjust[4], const float mult[4],
                     bool alpha) {
    if (!EnsureProgram() || y == 0 || cr == 0 || cb == 0) return;
    BindTarget();  // (the current render target: bound by what draws, device.cpp BindCurrent)
    GlCap(GL_DEPTH_TEST, false);
    GlCap(GL_CULL_FACE, false);
    if (alpha) {
        GlCap(GL_BLEND, true);
        GlBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    } else {
        GlCap(GL_BLEND, false);
    }
    GlUseProgram(g_program);
    glUniform4f(g_adjust, adjust[0], adjust[1], adjust[2], adjust[3]);
    glUniform4f(g_alpha, mult[0], mult[1], mult[2], mult[3]);
    glUniform1i(g_hasA, a != 0 ? 1 : 0);
    const GLuint textures[4] = {y, cr, cb, a};
    for (int i = 0; i < 4; ++i) {
        GlActiveTexture(i);
        GlBindTexture2D(textures[i]);
    }
    GlActiveTexture(0);
    GlBindVertexArray(g_vao);
    ApplyAlphaCoverage();  // (off: platform/gfx/mesh.h)
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
}

}  // namespace dotd::gfx
