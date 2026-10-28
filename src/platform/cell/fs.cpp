#include "platform/cell/fs.h"

#include <SDL3/SDL.h>

#include <algorithm>
#include <cstring>
#include <mutex>
#include <string>
#include <vector>

#include "platform/cell/cell_errors.h"
#include "platform/config.h"
#include "platform/log.h"

namespace {

struct DirItem {
    std::string name;
    CellFsStat stat;
    uint8_t type;
};

struct Handle {
    bool used = false;
    bool isDir = false;
    std::string host;
    SDL_IOStream* io = nullptr;  // opened on first read/seek
    uint64_t pos = 0;
    uint64_t size = 0;
    std::vector<DirItem> dir;
    size_t dirPos = 0;
};

const int kFirstFd = 3;
const size_t kMaxHandles = 1024;
std::mutex g_mutex;
std::vector<Handle> g_handles;

bool StartsWith(const std::string& s, const char* prefix, size_t* len) {
    const size_t n = std::strlen(prefix);
    if (s.size() < n || s.compare(0, n, prefix) != 0) return false;
    if (s.size() > n && s[n] != '/') return false;
    *len = n;
    return true;
}

bool HostStat(const std::string& host, CellFsStat* sb, uint8_t* type) {
    SDL_PathInfo info;
    if (!SDL_GetPathInfo(host.c_str(), &info) || info.type == SDL_PATHTYPE_NONE) return false;
    std::memset(sb, 0, sizeof(*sb));
    const bool dir = info.type == SDL_PATHTYPE_DIRECTORY;
    sb->mode = dir ? (CELL_FS_S_IFDIR | 0555) : (CELL_FS_S_IFREG | 0444);
    sb->atime = static_cast<int64_t>(info.access_time / SDL_NS_PER_SECOND);
    sb->mtime = static_cast<int64_t>(info.modify_time / SDL_NS_PER_SECOND);
    sb->ctime = static_cast<int64_t>(info.create_time / SDL_NS_PER_SECOND);
    sb->size = dir ? 0 : info.size;
    sb->blksize = 0x10000;
    if (type) *type = dir ? CELL_FS_TYPE_DIRECTORY : CELL_FS_TYPE_REGULAR;
    return true;
}

int32_t AllocHandle() {
    for (size_t i = 0; i < g_handles.size(); ++i) {
        if (!g_handles[i].used) return static_cast<int32_t>(i);
    }
    if (g_handles.size() >= kMaxHandles) return -1;
    g_handles.emplace_back();
    return static_cast<int32_t>(g_handles.size() - 1);
}

Handle* GetHandle(int32_t fd, bool wantDir) {
    const int32_t i = fd - kFirstFd;
    if (i < 0 || static_cast<size_t>(i) >= g_handles.size()) return nullptr;
    Handle& h = g_handles[static_cast<size_t>(i)];
    if (!h.used || h.isDir != wantDir) return nullptr;
    return &h;
}

bool EnsureOpen(Handle& h) {
    if (h.io) return true;
    h.io = SDL_IOFromFile(h.host.c_str(), "rb");
    if (!h.io) {
        DOTD_LOG("fs: cannot open %s: %s", h.host.c_str(), SDL_GetError());
        return false;
    }
    if (h.pos) SDL_SeekIO(h.io, static_cast<Sint64>(h.pos), SDL_IO_SEEK_SET);
    return true;
}

SDL_EnumerationResult CollectName(void* userdata, const char*, const char* fname) {
    static_cast<std::vector<std::string>*>(userdata)->push_back(fname);
    return SDL_ENUM_CONTINUE;
}

}  // namespace

namespace dotd::platform {
bool MapPs3Path(const char* ps3Path, std::string* hostPath, bool* writable) {
    if (!ps3Path) return false;
    std::string p(ps3Path);
    for (char& c : p) {
        if (c == '\\') c = '/';
    }
    const std::string& root = GetConfig().usrdir;
    size_t n = 0;
    if (StartsWith(p, "/dev_bdvd/PS3_GAME/USRDIR", &n) || StartsWith(p, "/app_home", &n)) {
        if (root.empty()) return false;
        *hostPath = root + p.substr(n);
        *writable = false;
        return true;
    }
    return false;  // /dev_hdd0 (saves) comes with the save-data shim
}
}  // namespace dotd::platform

CellFsErrno cellFsOpen(const char* path, int32_t flags, int32_t* fd, const void*, uint64_t) {
    if (!path || !fd) return CellError(CELL_EFAULT);
    std::string host;
    bool writable = false;
    if (!dotd::platform::MapPs3Path(path, &host, &writable)) return CellError(CELL_ENOENT);
    if ((flags & CELL_FS_O_ACCMODE) != CELL_FS_O_RDONLY || (flags & (CELL_FS_O_CREAT | CELL_FS_O_TRUNC))) {
        if (!writable) return CellError(CELL_EACCES);
    }
    CellFsStat sb;
    uint8_t type = 0;
    if (!HostStat(host, &sb, &type)) return CellError(CELL_ENOENT);
    if (type == CELL_FS_TYPE_DIRECTORY) return CellError(CELL_EISDIR);
    std::lock_guard<std::mutex> lock(g_mutex);
    const int32_t i = AllocHandle();
    if (i < 0) return CellError(CELL_EMFILE);
    Handle& h = g_handles[static_cast<size_t>(i)];
    h = Handle();
    h.used = true;
    h.host = host;
    h.size = sb.size;
    *fd = i + kFirstFd;
    return CELL_OK;
}

CellFsErrno cellFsRead(int32_t fd, void* buf, uint64_t nbytes, uint64_t* nread) {
    std::lock_guard<std::mutex> lock(g_mutex);
    Handle* h = GetHandle(fd, false);
    if (!h) return CellError(CELL_EBADF);
    if (!buf && nbytes) return CellError(CELL_EFAULT);
    if (!EnsureOpen(*h)) return CellError(CELL_EIO);
    const size_t got = nbytes ? SDL_ReadIO(h->io, buf, static_cast<size_t>(nbytes)) : 0;
    h->pos += got;
    if (nread) *nread = got;
    return CELL_OK;
}

CellFsErrno cellFsWrite(int32_t fd, const void*, uint64_t, uint64_t* nwrite) {
    std::lock_guard<std::mutex> lock(g_mutex);
    if (nwrite) *nwrite = 0;
    return GetHandle(fd, false) ? CellError(CELL_EACCES) : CellError(CELL_EBADF);  // only read-only devices so far
}

CellFsErrno cellFsLseek(int32_t fd, int64_t offset, int32_t whence, uint64_t* pos) {
    std::lock_guard<std::mutex> lock(g_mutex);
    Handle* h = GetHandle(fd, false);
    if (!h) return CellError(CELL_EBADF);
    int64_t base = 0;
    switch (whence) {
    case CELL_FS_SEEK_SET: base = 0; break;
    case CELL_FS_SEEK_CUR: base = static_cast<int64_t>(h->pos); break;
    case CELL_FS_SEEK_END: base = static_cast<int64_t>(h->size); break;
    default: return CellError(CELL_EINVAL);
    }
    const int64_t target = base + offset;
    if (target < 0) return CellError(CELL_EINVAL);
    h->pos = static_cast<uint64_t>(target);
    if (h->io) SDL_SeekIO(h->io, target, SDL_IO_SEEK_SET);
    if (pos) *pos = h->pos;
    return CELL_OK;
}

CellFsErrno cellFsClose(int32_t fd) {
    std::lock_guard<std::mutex> lock(g_mutex);
    Handle* h = GetHandle(fd, false);
    if (!h) return CellError(CELL_EBADF);
    if (h->io) SDL_CloseIO(h->io);
    *h = Handle();
    return CELL_OK;
}

CellFsErrno cellFsStat(const char* path, CellFsStat* sb) {
    if (!path || !sb) return CellError(CELL_EFAULT);
    std::string host;
    bool writable = false;
    if (!dotd::platform::MapPs3Path(path, &host, &writable)) return CellError(CELL_ENOENT);
    return HostStat(host, sb, nullptr) ? CELL_OK : CellError(CELL_ENOENT);
}

CellFsErrno cellFsOpendir(const char* path, int32_t* fd) {
    if (!path || !fd) return CellError(CELL_EFAULT);
    std::string host;
    bool writable = false;
    if (!dotd::platform::MapPs3Path(path, &host, &writable)) return CellError(CELL_ENOENT);
    CellFsStat sb;
    uint8_t type = 0;
    if (!HostStat(host, &sb, &type)) return CellError(CELL_ENOENT);
    if (type != CELL_FS_TYPE_DIRECTORY) return CellError(CELL_ENOTDIR);
    std::vector<std::string> names;
    SDL_EnumerateDirectory(host.c_str(), CollectName, &names);
    // Entry order: "." and ".." first, then sorted by name. ASSUMPTION: the order the PS3 returns for
    // the disc is not verified; check it if the game ever depends on it (KHostFS_PreopenFilesRecursive
    // 0x4f678 builds its file index from this listing).
    std::sort(names.begin(), names.end());
    std::vector<DirItem> items;
    DirItem dot;
    dot.stat = sb;
    dot.type = CELL_FS_TYPE_DIRECTORY;
    dot.name = ".";
    items.push_back(dot);
    dot.name = "..";
    items.push_back(dot);
    for (const std::string& n : names) {
        DirItem it;
        it.name = n;
        if (!HostStat(host + "/" + n, &it.stat, &it.type)) continue;
        items.push_back(it);
    }
    std::lock_guard<std::mutex> lock(g_mutex);
    const int32_t i = AllocHandle();
    if (i < 0) return CellError(CELL_EMFILE);
    Handle& h = g_handles[static_cast<size_t>(i)];
    h = Handle();
    h.used = true;
    h.isDir = true;
    h.host = host;
    h.dir.swap(items);
    *fd = i + kFirstFd;
    return CELL_OK;
}

CellFsErrno cellFsGetDirectoryEntries(int32_t fd, CellFsDirectoryEntry* entries, uint32_t entries_size, uint32_t* data_count) {
    std::lock_guard<std::mutex> lock(g_mutex);
    Handle* h = GetHandle(fd, true);
    if (!h) return CellError(CELL_EBADF);
    if (!entries || !data_count) return CellError(CELL_EFAULT);
    const uint32_t capacity = entries_size / static_cast<uint32_t>(sizeof(CellFsDirectoryEntry));
    uint32_t n = 0;
    while (n < capacity && h->dirPos < h->dir.size()) {
        const DirItem& it = h->dir[h->dirPos++];
        CellFsDirectoryEntry& e = entries[n++];
        std::memset(&e, 0, sizeof(e));
        e.attribute = it.stat;
        e.entry_name.d_type = it.type;
        const size_t len = it.name.size() > 255 ? 255 : it.name.size();
        e.entry_name.d_namlen = static_cast<uint8_t>(len);
        std::memcpy(e.entry_name.d_name, it.name.data(), len);
    }
    *data_count = n;
    return CELL_OK;
}

CellFsErrno cellFsClosedir(int32_t fd) {
    std::lock_guard<std::mutex> lock(g_mutex);
    Handle* h = GetHandle(fd, true);
    if (!h) return CellError(CELL_EBADF);
    *h = Handle();
    return CELL_OK;
}
