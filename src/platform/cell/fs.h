// fs.h - cellFs (sys_fs) as the game uses it.
// /dev_bdvd/PS3_GAME/USRDIR/... and /app_home/... map to the configured local USRDIR, read-only.
// Handles open the host file lazily on first read/seek: the boot pre-opens ~550 RWS files.
#pragma once
#include <cstdint>
#include <string>

enum : int32_t {
    CELL_FS_O_RDONLY = 000000,
    CELL_FS_O_WRONLY = 000001,
    CELL_FS_O_RDWR = 000002,
    CELL_FS_O_ACCMODE = 000003,
    CELL_FS_O_CREAT = 000100,
    CELL_FS_O_TRUNC = 001000,
};
enum : int32_t { CELL_FS_SEEK_SET = 0, CELL_FS_SEEK_CUR = 1, CELL_FS_SEEK_END = 2 };
enum : int32_t { CELL_FS_S_IFDIR = 0040000, CELL_FS_S_IFREG = 0100000 };
enum : uint8_t { CELL_FS_TYPE_UNKNOWN = 0, CELL_FS_TYPE_DIRECTORY = 1, CELL_FS_TYPE_REGULAR = 2 };

typedef int32_t CellFsErrno;

#pragma pack(push, 4)
struct CellFsStat {
    int32_t mode;
    int32_t uid;
    int32_t gid;
    int64_t atime;
    int64_t mtime;
    int64_t ctime;
    uint64_t size;
    uint64_t blksize;
};
#pragma pack(pop)
static_assert(sizeof(CellFsStat) == 52, "PS3 layout (4-byte aligned 64-bit fields)");

struct CellFsDirent {
    uint8_t d_type;
    uint8_t d_namlen;
    char d_name[256];
};

#pragma pack(push, 4)
struct CellFsDirectoryEntry {
    CellFsStat attribute;
    CellFsDirent entry_name;
};
#pragma pack(pop)

CellFsErrno cellFsOpen(const char* path, int32_t flags, int32_t* fd, const void* arg, uint64_t size);
CellFsErrno cellFsRead(int32_t fd, void* buf, uint64_t nbytes, uint64_t* nread);
CellFsErrno cellFsWrite(int32_t fd, const void* buf, uint64_t nbytes, uint64_t* nwrite);
CellFsErrno cellFsLseek(int32_t fd, int64_t offset, int32_t whence, uint64_t* pos);
CellFsErrno cellFsClose(int32_t fd);
CellFsErrno cellFsStat(const char* path, CellFsStat* sb);
CellFsErrno cellFsOpendir(const char* path, int32_t* fd);
CellFsErrno cellFsGetDirectoryEntries(int32_t fd, CellFsDirectoryEntry* entries, uint32_t entries_size, uint32_t* data_count);
CellFsErrno cellFsClosedir(int32_t fd);

namespace dotd::platform {
// PS3 path -> host path. False when the path is outside the mapped devices.
bool MapPs3Path(const char* ps3Path, std::string* hostPath, bool* writable);
}
