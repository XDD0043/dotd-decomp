// newgame_ltmwatch.inc - DOTD_DBG_LTMWATCH=F (C2.7 diagnostics, Windows x86 only): from recorded frame F - 1 to F + 1 a
// hardware write watchpoint (debug register 0, by a helper thread that suspends this one) on the x of the camera service's
// first stack target's LTM translation; every write prints the replay frame, the writing function and its callers. Which
// code brings that LTM up to date before CKSrvCamera::UpdateFrame reads it (the original reads last frame's).
#if defined(_WIN32) && defined(_M_IX86)
#include <windows.h>
#include "platform/debug_symbols.h"

namespace {
volatile void* g_ltmWatchAddress = nullptr;
HANDLE g_ltmWatchThread = nullptr;

// The hits are only buffered here (the handler must not touch the watched address, nor take locks): printed when the
// watch is disarmed.
struct LtmWatchHit {
    int32_t frame;
    void* at;
    void* callers[20];
    int count;
};
LtmWatchHit g_ltmWatchHits[4096];
volatile LONG g_ltmWatchCount = 0;

LONG CALLBACK LtmWatchHandler(EXCEPTION_POINTERS* info) {
    if (info->ExceptionRecord->ExceptionCode != EXCEPTION_SINGLE_STEP) return EXCEPTION_CONTINUE_SEARCH;
    if ((info->ContextRecord->Dr6 & 1u) == 0) return EXCEPTION_CONTINUE_SEARCH;
    info->ContextRecord->Dr6 = 0;
    const LONG i = g_ltmWatchCount;
    if (i < 4096) {
        LtmWatchHit& hit = g_ltmWatchHits[i];
        hit.frame = g_replayCurrent;
        hit.at = info->ExceptionRecord->ExceptionAddress;
        hit.count = static_cast<int>(RtlCaptureStackBackTrace(5, 20, hit.callers, nullptr));
        g_ltmWatchCount = i + 1;
    }
    return EXCEPTION_CONTINUE_EXECUTION;
}

void LtmWatchPrint() {
    for (LONG i = 0; i < g_ltmWatchCount; ++i) {
        const LtmWatchHit& hit = g_ltmWatchHits[i];
        if (hit.at == nullptr) {
            std::fprintf(stderr, "ltmwatch ---- frame +%d begins\n", hit.frame);
            continue;
        }
        std::fprintf(stderr, "ltmwatch +%d at %s", hit.frame, dotd::platform::debugsym::FunctionName(hit.at));
        for (int k = 0; k < hit.count; ++k) std::fprintf(stderr, " < %s", dotd::platform::debugsym::FunctionName(hit.callers[k]));
        std::fputc('\n', stderr);
    }
    g_ltmWatchCount = 0;
}

struct LtmWatchRequest {
    HANDLE target;
    void* address;
};

DWORD WINAPI LtmWatchSetter(void* parameter) {
    LtmWatchRequest* request = static_cast<LtmWatchRequest*>(parameter);
    SuspendThread(request->target);
    CONTEXT context = {};
    context.ContextFlags = CONTEXT_DEBUG_REGISTERS;
    GetThreadContext(request->target, &context);
    if (request->address != nullptr) {
        context.Dr0 = reinterpret_cast<DWORD>(request->address);
        context.Dr7 = (context.Dr7 & ~0x000f0003u) | 0x1u | (0x3u << 16) | (0x3u << 18);  // local 0, read/write, 4 bytes
    } else {
        context.Dr0 = 0;
        context.Dr7 &= ~0x000f0003u;
    }
    SetThreadContext(request->target, &context);
    ResumeThread(request->target);
    return 0;
}

void LtmWatchSet(void* address) {
    static bool installed = false;
    if (!installed) {
        AddVectoredExceptionHandler(1, LtmWatchHandler);
        installed = true;
    }
    HANDLE self = nullptr;
    DuplicateHandle(GetCurrentProcess(), GetCurrentThread(), GetCurrentProcess(), &self, 0, FALSE, DUPLICATE_SAME_ACCESS);
    LtmWatchRequest request = {self, address};
    HANDLE thread = CreateThread(nullptr, 0, LtmWatchSetter, &request, 0, nullptr);
    WaitForSingleObject(thread, INFINITE);
    CloseHandle(thread);
    CloseHandle(self);
    g_ltmWatchAddress = address;
}
}  // namespace

// Before each loop frame: arm the watch over [F - 1, F + 1], disarm after.
void LtmWatchBeforeFrame() {
    static const char* env = std::getenv("DOTD_DBG_LTMWATCH");
    if (env == nullptr) return;
    const int32_t at = std::atoi(env);
    static bool armed = false;
    const bool want = g_replayCurrent >= at - 1 && g_replayCurrent <= at + 1;
    if (want && !armed) {
        CKSrvCamera* service = static_cast<CKSrvCamera*>(g_pEngine->m_srvCamera);
        if (service == nullptr || service->m_ui32NbStacked == 0 || service->m_aStack[0].m_pTarget == nullptr) return;
        CSGLeaf* leaf = static_cast<CSGLeaf*>(service->m_aStack[0].m_pTarget);
        LtmWatchSet(&leaf->m_pRwFrame->ltm.pos.x);
        std::fprintf(stderr, "ltmwatch armed at +%d (modelling x %.7g, ltm x %.7g)\n", g_replayCurrent,
                     leaf->m_pRwFrame->modelling.pos.x, leaf->m_pRwFrame->ltm.pos.x);
        armed = true;
    } else if (!want && armed) {
        LtmWatchSet(nullptr);
        armed = false;
        LtmWatchPrint();
    }
    if (armed) {  // a frame marker among the hits
        const LONG i = g_ltmWatchCount;
        if (i < 4096) {
            g_ltmWatchHits[i] = LtmWatchHit{g_replayCurrent, nullptr, {}, 0};
            g_ltmWatchCount = i + 1;
        }
    }
}
#else
void LtmWatchBeforeFrame() {}
#endif
