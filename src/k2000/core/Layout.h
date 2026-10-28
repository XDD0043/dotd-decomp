// Layout.h - compile-time checks that a class keeps its PS3 layout.
// Active only in 32-bit builds (DOTD_PS3_LAYOUT=1: Win32 parity preset, wasm32), where pointers are
// 4 bytes like on the PS3. In 64-bit builds pointer-holding classes are larger and the checks are off.
#pragma once
#include <cstddef>

#ifndef DOTD_PS3_LAYOUT
#define DOTD_PS3_LAYOUT 0
#endif

#if DOTD_PS3_LAYOUT
#define DOTD_ASSERT_SIZE(T, size) static_assert(sizeof(T) == (size), #T " must be " #size " bytes (PS3 layout)")
#define DOTD_ASSERT_OFFSET(T, member, off) \
    static_assert(offsetof(T, member) == (off), #T "::" #member " must be at " #off " (PS3 layout)")
#else
#define DOTD_ASSERT_SIZE(T, size) static_assert(true, "")
#define DOTD_ASSERT_OFFSET(T, member, off) static_assert(true, "")
#endif
