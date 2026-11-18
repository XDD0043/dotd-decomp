// web.h - the web build's (Emscripten: wasm32 + WebGL2) own entry points. Only compiled into that build;
// include it under #ifdef __EMSCRIPTEN__. How the page is built, served and run: dotd/web/README.md.
#pragma once
#include <cstddef>
#include <cstdint>
#include <string>
#include <vector>

namespace dotd::platform::web {

// Main thread, before anything reads a file: takes the listing of the served USRDIR the page fetched and
// starts the I/O thread (web/hostfs_web.cpp). `root` is Config::usrdir, the path prefix the files appear under.
// False when the listing is empty (the server has no game folder).
bool InitHostFs(const std::string& root);
void LogHostFsStats();
// What the browser's main thread waited for file reads since the last call (a read not in the block cache is a
// request the I/O thread makes for it): the time in ms and the number of reads that waited. For the long-frame
// line of DOTD_GFX_STATS (platform/frame_loop.cpp).
void TakeMainThreadReadWait(double* ms, int* reads, double* megabytes);
// The first `bytes` of a served file (fewer when it is shorter) in one request of exactly that size, not through
// the cache of 1 MB blocks: for a caller on the main thread that only needs a file's header and must not wait
// for a megabyte on a slow connection (a video's header, platform/video/bink.cpp). False: not a served file, or
// the request failed.
bool ReadHead(const std::string& path, size_t bytes, std::vector<uint8_t>* out);

}  // namespace dotd::platform::web
