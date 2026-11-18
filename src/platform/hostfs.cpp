// hostfs.cpp - the native host file access (the web build's is web/hostfs_web.cpp).
#include "platform/hostfs.h"

#ifndef __EMSCRIPTEN__

#include <SDL3/SDL.h>

#include "platform/log.h"

namespace dotd::platform::hostfs {

struct File {
    SDL_IOStream* io = nullptr;
};

bool Stat(const std::string& path, Info* info) {
    SDL_PathInfo sdl;
    if (!SDL_GetPathInfo(path.c_str(), &sdl) || sdl.type == SDL_PATHTYPE_NONE) return false;
    info->isDir = sdl.type == SDL_PATHTYPE_DIRECTORY;
    info->size = info->isDir ? 0 : sdl.size;
    info->atime = static_cast<int64_t>(sdl.access_time / SDL_NS_PER_SECOND);
    info->mtime = static_cast<int64_t>(sdl.modify_time / SDL_NS_PER_SECOND);
    info->ctime = static_cast<int64_t>(sdl.create_time / SDL_NS_PER_SECOND);
    return true;
}

namespace {
SDL_EnumerationResult CollectName(void* userdata, const char*, const char* fname) {
    static_cast<std::vector<std::string>*>(userdata)->push_back(fname);
    return SDL_ENUM_CONTINUE;
}
}  // namespace

bool List(const std::string& dir, std::vector<std::string>* names) {
    return SDL_EnumerateDirectory(dir.c_str(), CollectName, names);
}

File* Open(const std::string& path) {
    SDL_IOStream* io = SDL_IOFromFile(path.c_str(), "rb");
    if (!io) {
        DOTD_LOG("fs: cannot open %s: %s", path.c_str(), SDL_GetError());
        return nullptr;
    }
    File* file = new File();
    file->io = io;
    return file;
}

size_t Read(File* file, void* buffer, size_t bytes) { return bytes ? SDL_ReadIO(file->io, buffer, bytes) : 0; }

bool Seek(File* file, uint64_t position) {
    return SDL_SeekIO(file->io, static_cast<Sint64>(position), SDL_IO_SEEK_SET) >= 0;
}

void Close(File* file) {
    if (!file) return;
    SDL_CloseIO(file->io);
    delete file;
}

std::FILE* OpenStdio(const std::string& path) { return std::fopen(path.c_str(), "rb"); }

}  // namespace dotd::platform::hostfs

#endif  // !__EMSCRIPTEN__
