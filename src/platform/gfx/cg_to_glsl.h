// cg_to_glsl.h - the game's Cg uber-shader as GLSL 3.30 (new platform code, not a port).
//
// The PS3 build ships the shader as Cg text inside the EBOOT (the vertex program in one block, the pixel
// program in another; each is shaderdefine + commonshadertools + the main function, switched by `extern*`
// defines) and `Shader/ps3/shfct.bin` holds the NV40 binaries compiled from it, which a PC cannot use. This
// module reads the text from EBOOT.elf at run time (it is game data and never copied into the repository),
// runs the C preprocessor with a variant's define list (cg_preproc.h) and translates the Cg subset the shader
// uses into GLSL.
//
// Conventions (decided once, tested in tests/c15/cg_translate_test.cpp with a known matrix):
//  * Matrices. The shader has `#pragma pack_matrix (row_major)`: a floatRxC uniform occupies R constant
//    registers that hold its rows. A Cg floatRxC matrix M is a GLSL matRxC holding the TRANSPOSE (column i of
//    the GLSL matrix is row i of M), so the register data of a uniform is uploaded verbatim
//    (glUniformMatrix4fv(..., GL_FALSE, registers)) and M[i] is the GLSL column [i], M._mRC is [R][C],
//    float3x3(a, b, c) is mat3(a, b, c), (float3x3)M is mat3(S). mul(M, v) is emitted `v * S`, mul(v, M) is
//    `S * v`, mul(M1, M2) is `S2 * S1`. Every matrix in the program follows this, locals and parameters too.
//  * Vertex inputs are `in` attributes at the fixed NV40 slots by semantic (POSITION 0, BLENDWEIGHT 1, NORMAL 2,
//    COLOR0 3, COLOR1 4, FOG 5, PSIZE 6, BLENDINDICES 7, TEXCOORD0..7 8..15, TANGENT = TEXCOORD6, BINORMAL =
//    TEXCOORD7), named `a_<member>`; the vertex outputs are `v_<member>` varyings (POSITION -> gl_Position),
//    the pixel outputs `o_<member>` (COLOR0 / COLOR1 at their locations, DEPTH -> gl_FragDepth).
//  * Samplers are plain `uniform sampler2D`; the register s<N> is the texture unit the host sets after link.
//  * Cg's leaky `for (int i ...)` scope (the loop variable stays visible after the loop; the shader relies on
//    it) is kept: the variable is declared in the enclosing block.
#pragma once
#include <string>
#include <vector>

#include "platform/gfx/cg_preproc.h"

namespace dotd::gfx::cg {

enum class Stage { kVertex, kPixel };

// A `uniform` of the Cg source with its constant register ('c' float registers, 'b' bool registers).
struct UniformInfo {
    std::string name;
    std::string cgType;    // "float4x4", "float4", "bool", ...
    std::string glslType;  // "mat4", "vec4", "bool", "mat3x4", ...
    int arraySize = 0;     // 0: not an array
    char registerClass = 'c';
    int registerIndex = 0;
    int registerCount = 0;  // registers the uniform occupies (rows of a matrix, times the array size)
};
struct SamplerInfo {
    std::string name;
    int unit = 0;  // register(s<N>)
};
struct AttributeInfo {
    std::string name;      // the GLSL attribute name (a_<member>)
    std::string semantic;  // POSITION, TEXCOORD0, ...
    std::string glslType;
    int location = 0;
};
struct VaryingInfo {
    std::string name;  // v_<member>
    std::string semantic;
    std::string glslType;
    int arraySize = 0;
};
struct Translation {
    std::string glsl;
    std::vector<UniformInfo> uniforms;
    std::vector<SamplerInfo> samplers;
    std::vector<AttributeInfo> attributes;  // vertex stage
    std::vector<VaryingInfo> varyings;      // vertex outputs / pixel inputs
    std::vector<std::string> colorOutputs;  // pixel stage: the o_ names, index = colour attachment
};

// Translates preprocessed Cg text (Preprocess output); `entry` is the entry function
// ("VertexShaderMain" / "PixelShaderMain"). False with `error` ("line N: ...") on an unsupported or wrong
// construct.
bool Translate(const std::string& preprocessed, Stage stage, const char* entry, Translation* out, std::string* error);

// The two Cg texts of the game's uber-shader.
struct Sources {
    std::string vertex;  // shaderdefine + commonshadertools + VertexShaderMain (EBOOT.elf file offset 0xc26750)
    std::string pixel;   // the same with PixelShaderMain (file offset 0xc19848)
};
// Reads EBOOT.elf (or the disc's EBOOT.BIN, decrypted in memory first: platform/self_decrypt.h) and takes the
// blocks at their ELF file offsets after verifying each block's first line and that it contains its entry function
// (the offsets were measured on the US EBOOT, BLUS30205). The text is NUL terminated in the file. False with `error`
// when the file or a block does not match.
bool LoadGameSources(const char* ebootPath, Sources* out, std::string* error);

// Preprocess + Translate for one stage of a variant.
bool BuildStage(const Sources& sources, Stage stage, const std::vector<Define>& defines, Translation* out,
                std::string* error);

}  // namespace dotd::gfx::cg
