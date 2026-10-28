// cell_errors.h - PS3 return codes the shims use. Game code branches on these exact values.
// Values from the PS3 SDK headers as documented by RPCS3 (Emu/Cell/ErrorCodes.h, module headers).
#pragma once
#include <cstdint>

enum : int32_t {
    CELL_OK = 0,
};

// LV2 / sys_fs errors
enum : uint32_t {
    CELL_EAGAIN = 0x80010001u,
    CELL_EINVAL = 0x80010002u,
    CELL_ENOMEM = 0x80010004u,
    CELL_ESRCH = 0x80010005u,
    CELL_ENOENT = 0x80010006u,
    CELL_EDEADLK = 0x80010008u,
    CELL_EPERM = 0x80010009u,
    CELL_EBUSY = 0x8001000Au,
    CELL_ETIMEDOUT = 0x8001000Bu,
    CELL_EFAULT = 0x8001000Du,
    CELL_EISDIR = 0x80010012u,
    CELL_EEXIST = 0x80010014u,
    CELL_EACCES = 0x80010029u,
    CELL_EBADF = 0x8001002Au,
    CELL_EIO = 0x8001002Bu,
    CELL_EMFILE = 0x8001002Cu,
    CELL_ENOTDIR = 0x8001002Eu,
};

// cellPad
enum : uint32_t {
    CELL_PAD_ERROR_FATAL = 0x80121101u,
    CELL_PAD_ERROR_INVALID_PARAMETER = 0x80121102u,
    CELL_PAD_ERROR_ALREADY_INITIALIZED = 0x80121103u,
    CELL_PAD_ERROR_UNINITIALIZED = 0x80121104u,
    CELL_PAD_ERROR_NO_DEVICE = 0x80121107u,
};

// cellSysutil
enum : uint32_t {
    CELL_SYSUTIL_ERROR_TYPE = 0x8002b101u,
    CELL_SYSUTIL_ERROR_VALUE = 0x8002b102u,
    CELL_SYSUTIL_ERROR_STATUS = 0x8002b106u,
};

// The PS3 functions return these as int; keep the bit pattern.
inline int32_t CellError(uint32_t code) { return static_cast<int32_t>(code); }
