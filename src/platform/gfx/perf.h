// perf.h - measuring aids of the graphics backend (new platform code, debug / profiling only).
//
// DOTD_GFX_STATS=<frames> (0 or absent: off): every <frames> presented frames one log line with the averages per frame
// of that window: the wall time between two presents, the time inside the present (SwapWindow), the GPU time of the
// frame's GL commands (a GL_TIME_ELAPSED query when the driver has timer queries; desktop GL 3.3 has them, GLES 3 /
// WebGL2 only as an extension, so the entry points are optional and loaded here, not in gl.h), and the counters below.
// At Shutdown a total line. Nothing is counted or queried when it is off.
//
// DOTD_RDOC_ON_SHOT=1: when the process runs under RenderDoc (renderdoc.dll injected, e.g. `renderdoccmd capture`),
// every SaveScreenshot asks RenderDoc to capture the next frame (its in-application API, TriggerCapture).
#pragma once
#include <cstdint>

namespace dotd::gfx::perf {

enum Counter : int {
    kDraws,           // glDraw* calls
    kInstances,       // instances drawn by the instanced draws (0 for the others)
    kPrograms,        // glUseProgram calls that changed the program
    kUniforms,        // glUniform* calls
    kUniformBlocks,   // uniform buffer uploads
    kTextureBinds,    // glBindTexture calls that reached GL
    kSamplerParams,   // glTexParameter / glSamplerParameter / glBindSampler calls that reached GL
    kBufferUploads,   // glBufferData / glBufferSubData calls
    kBufferBytes,     // their bytes
    kTargetBinds,     // glBindFramebuffer calls that reached GL
    kVaoBinds,        // glBindVertexArray calls
    kCounterCount,
};

extern bool g_enabled;
extern uint64_t g_counters[kCounterCount];

inline void Add(Counter counter, uint64_t n = 1) {
    if (g_enabled) g_counters[counter] += n;
}

void Init(void* (*getProc)(const char* name));  // gfx::Init, with the context current
void Shutdown();                                // gfx::Shutdown, before the context goes: the total line
void BeforePresent();                           // EndFrame, after the last GL command of the frame
void AfterPresent();                            // EndFrame, after SwapWindow
void CaptureNextFrame();                        // RenderDoc: capture the frame that starts at the next present

// What a long frame spent in the backend's first-use work: with the statistics on, a frame longer than 8.33 ms logs
// "gfxstats hitch" with the time and count of each kind inside it (Scope objects around that work); Shutdown logs the
// run's totals ("gfxstats work").
enum Work : int {
    kWorkShader,           // a shader variant translated, compiled and linked (cg::GetProgram's first use)
    kWorkTexture,          // a device texture created and filled
    kWorkMesh,             // a device mesh created (vertex array object and buffers)
    kWorkShaderTranslate,  // parts of kWorkShader (the totals line only): Cg to GLSL,
    kWorkShaderCompile,    // glCompileShader of the new GLSL texts,
    kWorkShaderLink,       // glLinkProgram of a new pair
    kWorkCount,
};
class Scope {
public:
    explicit Scope(Work work);
    ~Scope();
    Scope(const Scope&) = delete;
    Scope& operator=(const Scope&) = delete;

private:
    Work m_work;
    long long m_start = 0;  // steady_clock ticks; 0 when the statistics are off
};

}  // namespace dotd::gfx::perf
