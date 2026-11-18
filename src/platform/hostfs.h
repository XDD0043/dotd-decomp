// hostfs.h - read-only access to the game's files where the host keeps them.
// Native builds (hostfs.cpp): the files are on the local disk, read through SDL and the C library.
// The web build (web/hostfs_web.cpp): the files stay on the user's disk too, unconverted; web/serve.py serves
// the USRDIR folder next to the page and the paths under Config::usrdir are read from it with HTTP range
// requests (a listing fetched once at start-up answers Stat and List). Any other path goes to the C library
// (Emscripten's in-memory file system).
#pragma once
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <string>
#include <vector>

namespace dotd::platform::hostfs {

struct Info {
    bool isDir = false;
    uint64_t size = 0;                        // 0 for a directory
    int64_t atime = 0, mtime = 0, ctime = 0;  // seconds
};

// False when the path does not exist.
bool Stat(const std::string& path, Info* info);
// The names in a directory (no "." / "..", any order). False when it cannot be listed.
bool List(const std::string& dir, std::vector<std::string>* names);

// A file open for reading, with its own position.
struct File;
File* Open(const std::string& path);  // nullptr when it cannot be opened
size_t Read(File* file, void* buffer, size_t bytes);
bool Seek(File* file, uint64_t position);
void Close(File* file);

// The same file as a C stream ("rb"), for the code that reads with fread / fseek (Bink, RWS).
std::FILE* OpenStdio(const std::string& path);

}  // namespace dotd::platform::hostfs
