// Layout.h - compile-time checks that a class keeps its PS3 layout.
// Active only with DOTD_PS3_LAYOUT=1 (the Win32 parity preset), where pointers are 4 bytes like on the PS3.
// In 64-bit builds pointer-holding classes are larger and the checks are off; the web build (wasm32) leaves
// them off too (CMakeLists.txt).
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
