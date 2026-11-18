// debug_symbols.cpp - see debug_symbols.h.
#include "platform/debug_symbols.h"

#include <cstdio>
#include <map>
#include <string>

#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <windows.h>
#include <dbghelp.h>
#pragma comment(lib, "dbghelp.lib")
#endif

namespace dotd::platform::debugsym {

int CaptureCallers(int skip, void** out, int max) {
#ifdef _WIN32
    return static_cast<int>(CaptureStackBackTrace(static_cast<DWORD>(skip + 1), static_cast<DWORD>(max), out, nullptr));
#else
    (void)skip, (void)out, (void)max;
    return 0;
#endif
}

const char* FunctionName(void* address) {
    static std::map<void*, std::string> cache;
    auto it = cache.find(address);
    if (it != cache.end()) return it->second.c_str();
    std::string name = "?";
#ifdef _WIN32
    static bool ready = false;
    HANDLE process = GetCurrentProcess();
    if (!ready) {
        SymSetOptions(SYMOPT_UNDNAME | SYMOPT_DEFERRED_LOADS);
        ready = SymInitialize(process, nullptr, TRUE) != FALSE;
    }
    alignas(SYMBOL_INFO) char buffer[sizeof(SYMBOL_INFO) + 512];
    SYMBOL_INFO* symbol = reinterpret_cast<SYMBOL_INFO*>(buffer);
    symbol->SizeOfStruct = sizeof(SYMBOL_INFO);
    symbol->MaxNameLen = 511;
    DWORD64 displacement = 0;
    if (ready && SymFromAddr(process, reinterpret_cast<DWORD64>(address), &displacement, symbol)) name = symbol->Name;
#endif
    return cache.emplace(address, name).first->second.c_str();
}

#ifdef _WIN32
namespace {
LONG WINAPI ReportCrash(EXCEPTION_POINTERS* info) {
    const EXCEPTION_RECORD* record = info->ExceptionRecord;
    std::fprintf(stderr, "crash: exception 0x%08lx at %p (%s), thread %lu\n", record->ExceptionCode,
                 record->ExceptionAddress, FunctionName(record->ExceptionAddress), GetCurrentThreadId());
    if (record->ExceptionCode == EXCEPTION_ACCESS_VIOLATION && record->NumberParameters >= 2) {
        std::fprintf(stderr, "crash: %s of %p\n", record->ExceptionInformation[0] == 0 ? "read" : "write",
                     reinterpret_cast<void*>(record->ExceptionInformation[1]));
    }
    // The faulting thread's stack from its context (StackWalk64), not the filter's.
    CONTEXT context = *info->ContextRecord;
    STACKFRAME64 frame = {};
    DWORD machine;
#if defined(_M_X64)
    machine = IMAGE_FILE_MACHINE_AMD64;
    frame.AddrPC.Offset = context.Rip;
    frame.AddrFrame.Offset = context.Rbp;
    frame.AddrStack.Offset = context.Rsp;
#else
    machine = IMAGE_FILE_MACHINE_I386;
    frame.AddrPC.Offset = context.Eip;
    frame.AddrFrame.Offset = context.Ebp;
    frame.AddrStack.Offset = context.Esp;
#endif
    frame.AddrPC.Mode = frame.AddrFrame.Mode = frame.AddrStack.Mode = AddrModeFlat;
    FunctionName(record->ExceptionAddress);  // SymInitialize
    for (int i = 0; i < 48; ++i) {
        if (!StackWalk64(machine, GetCurrentProcess(), GetCurrentThread(), &frame, &context, nullptr,
                         SymFunctionTableAccess64, SymGetModuleBase64, nullptr) || frame.AddrPC.Offset == 0) {
            break;
        }
        void* pc = reinterpret_cast<void*>(static_cast<uintptr_t>(frame.AddrPC.Offset));
        std::fprintf(stderr, "crash:   %2d %p %s\n", i, pc, FunctionName(pc));
    }
    std::fflush(stderr);
    return EXCEPTION_CONTINUE_SEARCH;
}
}  // namespace
#endif

void InstallCrashReport() {
#ifdef _WIN32
    SetUnhandledExceptionFilter(&ReportCrash);
#endif
}

}  // namespace dotd::platform::debugsym
