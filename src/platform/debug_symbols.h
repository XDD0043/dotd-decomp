// debug_symbols.h - the calling code's return addresses and their function names (new platform debug code for the replay
// tools, C2.7: the rand log names the dotd function behind each rand draw). Windows: CaptureStackBackTrace and DbgHelp
// with the build's pdb; elsewhere nothing is captured.
#pragma once

namespace dotd::platform::debugsym {

// Up to `max` return addresses of the caller's callers, skipping `skip` frames above the caller. Returns the count.
int CaptureCallers(int skip, void** out, int max);

// The function name at `address` ("?" when unknown); cached, valid until the process ends.
const char* FunctionName(void* address);

// A crash (an unhandled exception) prints its code, the faulting function and the thread's stack to stderr before the
// process ends (the test tools: a crash that only happens outside a debugger). Windows only.
void InstallCrashReport();

}  // namespace dotd::platform::debugsym
