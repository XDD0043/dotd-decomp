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
    // The web build only (background builds, below): the program is still being built; glProgram is 0 until it
    // is ready, and what would be drawn with it is not drawn meanwhile.
    bool building = false;
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
// Counts the DestroyPrograms calls: a Program* kept outside (ShaderVariant_GetProgram's cache by key) is valid only while
// this has the value it had when the pointer was taken.
uint32_t ProgramsGeneration();

// ---- background builds (the web build; nothing happens natively) -------------------------------------------------------
// WebGL builds a program far more slowly than a desktop driver (about 55 ms for a variant the browser has not seen,
// 5 ms from its cache), and the browser builds in the background as long as nobody asks for the result. So on the web,
// with KHR_parallel_shader_compile, GetProgram does not wait: it starts the build and answers a Program that is
// `building` (glProgram 0: its draws are skipped, like a failed variant's); PollBuilds, once per frame (EndFrame),
// completes the programs the browser has finished and starts the waiting ones (a variant's Cg translation is the
// game's own time, about 3 ms: 8 ms of them per frame). FlushBuilds waits for all of them (PrewarmVariantGroup: a
// loading screen is up).
void PollBuilds();
void FlushBuilds();

// ---- the variant list (perf: no shader build in the middle of play) ---------------------------------------------------
// A variant's first use translates, compiles and links its program: about 7 ms with the GPU driver's own shader cache
// warm and 50 ms with it cold (a new driver, the first run), and a new part of a level brings ten or twenty variants in
// one frame. The variant list is a text file outside the repository (the user's cache folder) that remembers which
// variants (define lists) each group used; a group is a level number. The game calls PrewarmVariantGroup when a level
// has loaded, while its loading screen is still up: the group's listed variants are built there, so from the second
// visit on play finds its programs ready. The list only moves when a program is built: the programs, their uniforms and
// what they draw are the same with and without it.
//
// The file: a first line "dotd-shader-variants 1", then one line per (group, variant): the group number, a tab, the
// variant's define list as "name=value;name=value;...". A line that does not parse is ignored; a variant that no longer
// translates only logs its error, as on a first use.
//
// EnableVariantList(path): turns the list on with that file (null or empty: the default file, shader-variants.txt in
// %LOCALAPPDATA%\dotd\cache or ~/.cache/dotd). The environment variable DOTD_SHADER_LIST wins over the argument: a path,
// or "off" for no list. Without a call and without the variable there is no list (the tests).
void EnableVariantList(const char* path);
// The group the variants built from now on are listed under (-1 at the start: not listed).
void SetVariantGroup(int group);
// Builds the programs of the group's listed variants that are not built yet and calls `built` (when given) with each
// one that linked. Returns how many it built; 0 without a list or a GL device.
int PrewarmVariantGroup(int group, void (*built)(const Program* program));

}  // namespace dotd::gfx::cg
