// debug_symbols.cpp - see debug_symbols.h.
#include "platform/debug_symbols.h"

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

}  // namespace dotd::platform::debugsym
