// cg_program.h - the GL programs of the game's Cg uber-shader, one per variant (new platform code).
//
// A variant is its define list (the game builds it from a ShaderVariantKey, k2000/render/ShaderVariantKey.h).
// GetProgram translates the vertex and pixel stage (cg_to_glsl.h), compiles and links them with the device's
// GL context and keeps the result in memory, keyed by the define list. Identical GLSL texts of two variants
// share their shader objects: the game's key has more bits than the programs it needs (a pixel program does
// not depend on the skinning weights, a vertex program not on the pixel-only flags), see
// ShaderVariantKey_MatchesVertexShader_maybe 0xf1e38 / MatchesPixelShader_maybe 0xf2000.
//
// The cache is process-global and lives until DestroyPrograms (never written to disk). Debug aid: with the
// environment variable DOTD_DUMP_GLSL=<directory> every new variant's generated GLSL and define list are written there
// (variantN.vs.glsl / .fs.glsl / .defines.txt); nothing generated from the game's shader text belongs in the repository.
#pragma once
#include <cstdint>
#include <string>
#include <vector>

#include "platform/gfx/cg_to_glsl.h"

namespace dotd::gfx::cg {

struct Program {
    uint32_t glProgram = 0;  // 0: the variant failed (error says why)
    Translation vertex;      // attribute / varying / uniform interface of the stages
    Translation pixel;
    uint32_t vertexShaderId = 0;  // index of the distinct vertex GLSL text (0-based, for statistics)
    uint32_t pixelShaderId = 0;
    std::string error;
};

// The Cg sources (EBOOT.elf, read once). False with `error` when the file does not match.
bool InitSources(const char* ebootPath, std::string* error);
bool SourcesLoaded();
const Sources& GameSources();

// The program of a define list (compiled on first use). Never null once InitSources succeeded and a GL device
// exists; a failed variant has glProgram 0 and `error` set (also logged once).
const Program* GetProgram(const std::vector<Define>& defines);

struct Statistics {
    uint32_t variants = 0;        // define lists seen
    uint32_t failures = 0;        // variants that did not translate, compile or link
    uint32_t vertexShaders = 0;   // distinct vertex GLSL texts compiled
    uint32_t pixelShaders = 0;    // distinct pixel GLSL texts compiled
    uint32_t linkedPrograms = 0;  // distinct (vertex, pixel) pairs linked
};
Statistics GetStatistics();
void DestroyPrograms();

}  // namespace dotd::gfx::cg
