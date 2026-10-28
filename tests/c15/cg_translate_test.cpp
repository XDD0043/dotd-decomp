// cg_translate_test - checkpoint C2.4 step 2: the Cg preprocessor and the Cg -> GLSL translator.
//
// 1. The preprocessor on small inputs: object and function-like macros, ## pasting (the DeclareUniform form of the
//    game's shader), #if / #elif / defined, #undef, #error.
// 2. The matrix convention (platform/gfx/cg_to_glsl.h) with a known matrix: a tiny Cg program, translated, compiled
//    with GL (hidden window), run into a 4x4 target and read back; mul(M, v), mul(v, M), a float3x4 array element,
//    M._m30_..., M[i], (float3x3)M, float3x3(a, b, c) and mul(M, M) give what the maths says, with the uniform data
//    uploaded verbatim as constant registers (the rows). Skipped (reported) without a GL device.
// 3. The game's own shader (EBOOT.elf in DOTD_USRDIR): the blocks are found at their offsets, and a handful of
//    variants translate (and compile when a device exists). The full LVL010 set is shader_variants_test.
#include <cmath>
#include <cstdio>
#include <cstring>
#include <string>
#include <vector>

#include "boot_helper.h"
#include "platform/config.h"
#include "platform/gfx/cg_preproc.h"
#include "platform/gfx/cg_program.h"
#include "platform/gfx/cg_to_glsl.h"
#include "platform/gfx/device.h"
#include "platform/gfx/gl.h"
#include "platform/sdl/app.h"

using namespace dotd::gfx;
using namespace dotd::gfx::cg;

namespace {

std::string Pre(const std::string& source, const std::vector<Define>& defines, bool* ok = nullptr) {
    std::string out, error;
    const bool good = Preprocess(source, defines, &out, &error);
    if (ok != nullptr) *ok = good;
    if (!good) return "ERROR " + error;
    // squeeze: drop blank lines and surrounding spaces for easy comparison
    std::string squeezed;
    std::string line;
    for (char c : out + "\n") {
        if (c == '\n') {
            size_t a = line.find_first_not_of(' ');
            if (a != std::string::npos) squeezed += line.substr(a, line.find_last_not_of(' ') - a + 1) + "|";
            line.clear();
        } else {
            line += c;
        }
    }
    return squeezed;
}

void CheckPreprocessor() {
    C15_CHECK(Pre("#define A 3\nint x = A + A;\n", {}) == "int x = 3 + 3;|");
    C15_CHECK(Pre("#define DU(t, n, r) uniform t n : register(c##r);\nDU(float4, u_a, 7)\n", {}) ==
              "uniform float4 u_a : register(c7);|");
    C15_CHECK(Pre("#define ARR(t, n, s, r) DU(t, n[s], r)\n#define DU(t, n, r) uniform t n : register(c##r);\nARR(float4, u_b, 4, 11)\n", {}) ==
              "uniform float4 u_b[4] : register(c11);|");
    C15_CHECK(Pre("#if externFog>1 && defined(externX)\nA\n#elif externFog==1\nB\n#else\nC\n#endif\n", {{"externFog", "1"}}) == "B|");
    C15_CHECK(Pre("#if externFog>1 && defined(externX)\nA\n#elif externFog==1\nB\n#else\nC\n#endif\n", {{"externFog", "2"}, {"externX", "0"}}) == "A|");
    C15_CHECK(Pre("#if externFog>1 && defined(externX)\nA\n#elif externFog==1\nB\n#else\nC\n#endif\n", {{"externFog", "0"}}) == "C|");
    C15_CHECK(Pre("#define internLightNb (internPoint+internDir)\n#define internPoint 1\n#define internDir 2\n#if internLightNb>2\nyes\n#endif\n", {}) == "yes|");
    C15_CHECK(Pre("#define X 1\n#undef X\n#ifdef X\nA\n#else\nB\n#endif\n", {}) == "B|");
    C15_CHECK(Pre("#define MAXV(a,b) ((a)>(b)?(a):(b))\nint v = MAXV(1, 2+3);\n", {}) == "int v = ((1)>(2+3)?(1):(2+3));|");
    bool ok = true;
    const std::string error = Pre("#ifndef externX\n#error \"externX undefined\"\n#endif\n", {}, &ok);
    C15_CHECK(!ok && error.find("externX undefined") != std::string::npos && error.find("line 2") != std::string::npos);
    C15_CHECK(Pre("#ifndef externX\n#error \"externX undefined\"\n#endif\nok\n", {{"externX", ""}}) == "ok|");
    C15_CHECK(Pre("/* a\ncomment */ x // y\nz\n", {}) == "x|z|");
}

// ---- GL helpers for the matrix test
GLuint g_fbo = 0, g_texture = 0, g_vao = 0, g_vbo = 0;

bool MakeTarget() {
    g_texture = CreateTextureRGBA8(4, 4, nullptr, false);
    if (g_texture == 0) return false;
    gl::glGenFramebuffers(1, &g_fbo);
    gl::glBindFramebuffer(GL_FRAMEBUFFER, g_fbo);
    gl::glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, g_texture, 0);
    if (gl::glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) return false;
    gl::glGenVertexArrays(1, &g_vao);
    gl::glBindVertexArray(g_vao);
    const float triangle[6] = {-1.0f, -1.0f, 3.0f, -1.0f, -1.0f, 3.0f};
    gl::glGenBuffers(1, &g_vbo);
    gl::glBindBuffer(GL_ARRAY_BUFFER, g_vbo);
    gl::glBufferData(GL_ARRAY_BUFFER, sizeof triangle, triangle, GL_DYNAMIC_DRAW);
    gl::glVertexAttribPointer(0, 2, GL_FLOAT, 0, 8, nullptr);
    gl::glEnableVertexAttribArray(0);
    return true;
}

GLuint Shader(GLenum type, const std::string& text) {
    GLuint s = gl::glCreateShader(type);
    const char* src = text.c_str();
    gl::glShaderSource(s, 1, &src, nullptr);
    gl::glCompileShader(s);
    GLint ok = 0;
    gl::glGetShaderiv(s, GL_COMPILE_STATUS, &ok);
    if (!ok) {
        char log[2048];
        gl::glGetShaderInfoLog(s, sizeof log, nullptr, log);
        std::printf("cg_translate: GLSL compile error: %s\n--- source ---\n%s\n", log, text.c_str());
        return 0;
    }
    return s;
}

const char* const kTiny =
    "#pragma pack_matrix (row_major)\n"
    "uniform float4x4 u_M : register(c0);\n"
    "uniform float4x4 u_S : register(c4);\n"
    "uniform float3x4 u_B[2] : register(c8);\n"
    "struct VIn { float4 p : POSITION; };\n"
    "struct VOut { float4 pos : POSITION0; float2 t : TEXCOORD0; };\n"
    "VOut VertexShaderMain(VIn v) { VOut o; o.pos = v.p; o.t = v.p.xy; return o; }\n"
    "struct POut { float4 c : COLOR0; };\n"
    "POut PixelShaderMain(VOut i)\n"
    "{\n"
    "  POut o;\n"
    "  float4 v = float4(1, 2, 3, 4);\n"
    "  float4 r = float4(0, 0, 0, 0);\n"
    "#if CASE==0\n  r = mul(u_M, v);\n"
    "#elif CASE==1\n  r = mul(v, u_M);\n"
    "#elif CASE==2\n  r.xyz = mul(u_B[1], v);\n"
    "#elif CASE==3\n  r = float4(u_M._m30_m31_m32_m33);\n"
    "#elif CASE==4\n  r.xyz = u_M[2].xyz;\n"
    "#elif CASE==5\n  r.xyz = mul((float3x3)u_M, float3(1, 2, 3));\n"
    "#elif CASE==6\n  r.xyz = mul(float3(1, 2, 3), (float3x3)u_M);\n"
    "#elif CASE==7\n  float3x3 m = float3x3(float3(1, 2, 3), float3(4, 5, 6), float3(7, 8, 10));\n"
    "  r.xyz = mul(m, float3(1, 1, 1));\n  r.w = m._m21;\n"
    "#elif CASE==8\n  r = mul(u_S, u_S)[1] * 50.0;\n"
    "#elif CASE==9\n  float4 q = u_M[1];\n  r = float4(q.x, u_M._12, u_M._m13, (float)(3 > 2 ? 7 : 1));\n"
    "#endif\n"
    "  o.c = r / 255.0;\n"
    "  return o;\n"
    "}\n";

// Row-major register data, as the PS3 constant registers hold them.
const float kM[16] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};
const float kS[16] = {1, 1, 0, 0, 0, 1, 1, 0, 0, 0, 1, 1, 1, 0, 0, 1};
const float kB[24] = {1, 0, 0, 0, 0, 2, 0, 0, 0, 0, 3, 1,  // B[0]: 3 rows of 4
                      1, 0, 0, 0, 0, 2, 0, 0, 0, 0, 3, 1};

void ExpectedFor(int c, float out[4]) {
    const float v[4] = {1, 2, 3, 4};
    out[0] = out[1] = out[2] = out[3] = 0;
    auto row = [](const float* m, int r, int col) { return m[r * 4 + col]; };
    switch (c) {
    case 0:
        for (int r = 0; r < 4; ++r) for (int k = 0; k < 4; ++k) out[r] += row(kM, r, k) * v[k];
        break;
    case 1:
        for (int k = 0; k < 4; ++k) for (int r = 0; r < 4; ++r) out[k] += v[r] * row(kM, r, k);
        break;
    case 2:
        for (int r = 0; r < 3; ++r) for (int k = 0; k < 4; ++k) out[r] += kB[12 + r * 4 + k] * v[k];
        break;
    case 3:
        for (int k = 0; k < 4; ++k) out[k] = row(kM, 3, k);
        break;
    case 4:
        for (int k = 0; k < 3; ++k) out[k] = row(kM, 2, k);
        break;
    case 5: {
        const float w[3] = {1, 2, 3};
        for (int r = 0; r < 3; ++r) for (int k = 0; k < 3; ++k) out[r] += row(kM, r, k) * w[k];
        break;
    }
    case 6: {
        const float w[3] = {1, 2, 3};
        for (int k = 0; k < 3; ++k) for (int r = 0; r < 3; ++r) out[k] += w[r] * row(kM, r, k);
        break;
    }
    case 7:
        out[0] = 6; out[1] = 15; out[2] = 25; out[3] = 8;
        break;
    case 8:
        for (int k = 0; k < 4; ++k) for (int j = 0; j < 4; ++j) out[k] += row(kS, 1, j) * row(kS, j, k);
        for (int k = 0; k < 4; ++k) out[k] *= 50.0f;
        break;
    case 9:
        out[0] = row(kM, 1, 0); out[1] = row(kM, 0, 1); out[2] = row(kM, 1, 3); out[3] = 7;  // M[1].x, _12 (row 0, column 1), _m13 (row 1, column 3)
        break;
    }
}

void CheckMatrixConvention() {
    if (!IsReady()) {
        std::printf("cg_translate: no GL device: the matrix test is skipped\n");
        return;
    }
    if (!MakeTarget()) {
        std::printf("FAIL cg_translate: no render target\n");
        ++c15::g_failures;
        return;
    }
    for (int c = 0; c <= 9; ++c) {
        Sources sources;
        sources.vertex = kTiny;
        sources.pixel = kTiny;
        std::vector<Define> defines = {{"CASE", std::to_string(c)}};
        Translation vs, ps;
        std::string error;
        // BuildStage uses the fixed entry names, which the tiny source defines
        const bool vsOk = BuildStage(sources, Stage::kVertex, defines, &vs, &error);
        const bool psOk = vsOk && BuildStage(sources, Stage::kPixel, defines, &ps, &error);
        if (!vsOk || !psOk) {
            std::printf("FAIL cg_translate: case %d: %s\n", c, error.c_str());
            ++c15::g_failures;
            continue;
        }
        GLuint v = Shader(GL_VERTEX_SHADER, vs.glsl);
        GLuint f = Shader(GL_FRAGMENT_SHADER, ps.glsl);
        if (v == 0 || f == 0) {
            ++c15::g_failures;
            continue;
        }
        GLuint p = gl::glCreateProgram();
        gl::glAttachShader(p, v);
        gl::glAttachShader(p, f);
        gl::glLinkProgram(p);
        GLint linked = 0;
        gl::glGetProgramiv(p, GL_LINK_STATUS, &linked);
        if (!linked) {
            char log[2048];
            gl::glGetProgramInfoLog(p, sizeof log, nullptr, log);
            std::printf("FAIL cg_translate: case %d link: %s\n", c, log);
            ++c15::g_failures;
            continue;
        }
        gl::glUseProgram(p);
        // The registers verbatim: no transpose.
        const GLint m = gl::glGetUniformLocation(p, "u_M");
        const GLint s = gl::glGetUniformLocation(p, "u_S");
        const GLint b = gl::glGetUniformLocation(p, "u_B");
        if (m >= 0) gl::glUniformMatrix4fv(m, 1, 0, kM);
        if (s >= 0) gl::glUniformMatrix4fv(s, 1, 0, kS);
        if (b >= 0) gl::glUniformMatrix3x4fv(b, 2, 0, kB);
        gl::glBindFramebuffer(GL_FRAMEBUFFER, g_fbo);
        gl::glViewport(0, 0, 4, 4);
        gl::glDisable(GL_BLEND);
        gl::glDisable(GL_DEPTH_TEST);
        gl::glDisable(GL_CULL_FACE);
        gl::glClearColor(0, 0, 0, 0);
        gl::glClear(GL_COLOR_BUFFER_BIT);
        gl::glBindVertexArray(g_vao);
        gl::glDrawArrays(GL_TRIANGLES, 0, 3);
        unsigned char px[4] = {};
        gl::glReadPixels(1, 1, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, px);
        float want[4];
        ExpectedFor(c, want);
        bool good = true;
        for (int k = 0; k < 4; ++k) {
            const float w = want[k] > 255.0f ? 255.0f : want[k];
            if (std::fabs(static_cast<float>(px[k]) - w) > 1.01f) good = false;
        }
        std::printf("cg_translate: matrix case %d: got %u %u %u %u, expected %.0f %.0f %.0f %.0f%s\n", c, px[0], px[1], px[2],
                    px[3], want[0], want[1], want[2], want[3], good ? "" : "  MISMATCH");
        if (!good) ++c15::g_failures;
        gl::glUseProgram(0);
        gl::glDeleteProgram(p);
        gl::glDeleteShader(v);
        gl::glDeleteShader(f);
    }
}

void CheckGameShader() {
    const char* usrdir = dotd::platform::GetConfig().usrdir.c_str();
    if (*usrdir == 0) {
        std::printf("cg_translate: no game data configured: the game shader part is skipped\n");
        return;
    }
    std::string path = std::string(usrdir) + "/EBOOT.elf";
    std::string error;
    if (!InitSources(path.c_str(), &error)) {
        std::printf("FAIL cg_translate: %s\n", error.c_str());
        ++c15::g_failures;
        return;
    }
    const Sources& src = GameSources();
    std::printf("cg_translate: Cg blocks: vertex %zu bytes, pixel %zu bytes\n", src.vertex.size(), src.pixel.size());
    C15_CHECK(src.vertex.size() == 39678 && src.pixel.size() == 52999);
    // The missing-define guard of the shader itself.
    {
        Translation t;
        std::string e;
        C15_CHECK(!BuildStage(src, Stage::kVertex, {}, &t, &e) && e.find("externTransform undefined") != std::string::npos);
    }
    const std::vector<Define> base = {{"externTransform", "0"}, {"externFogType", "0"},   {"externDirLight", "0"},
                                      {"externPointLight", "0"}, {"externSpotLight", "0"}, {"externVertexColor", "0"},
                                      {"externWeightNb", "0"},   {"externTexCoordNb", "1"}, {"externFirstPass", "1"},
                                      {"externMATERIALFX_NONE", "0"}, {"externSpecialLight", "0"}, {"externPS3", "0"}};
    const Program* program = GetProgram(base);
    C15_CHECK(program != nullptr && program->error.empty());
    if (program != nullptr) {
        std::printf("cg_translate: base variant: %zu vertex uniforms, %zu attributes, %zu varyings, %zu pixel samplers%s\n",
                    program->vertex.uniforms.size(), program->vertex.attributes.size(), program->vertex.varyings.size(),
                    program->pixel.samplers.size(), IsReady() ? (program->glProgram != 0 ? ", linked" : ", NOT LINKED") : "");
        C15_CHECK(!IsReady() || program->glProgram != 0);
    }
}

}  // namespace

int main() {
    std::setvbuf(stdout, nullptr, _IONBF, 0);
    CheckPreprocessor();
    dotd::platform::Config& config = dotd::platform::MutableConfig();
    dotd::platform::LoadConfig(0, nullptr, config);
    config.hiddenWindow = true;
    config.vsync = false;
    config.frameRate = 0;
    const bool device = dotd::platform::sdl::Init(config) && dotd::gfx::Init(1280, 720);
    if (!device) std::printf("cg_translate: no OpenGL 3.3 device: GL checks are skipped\n");
    CheckMatrixConvention();
    CheckGameShader();
    std::fflush(stdout);
    if (c15::g_failures == 0) std::printf("cg_translate: all tests passed\n");
    std::fflush(stdout);
    return c15::g_failures == 0 ? 0 : 1;
}
