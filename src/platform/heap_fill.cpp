// heap_fill.cpp - see heap_fill.h.
#include "platform/heap_fill.h"

#include <cstdlib>
#include <cstring>
#include <new>

namespace dotd {

namespace {
int ReadFillByte() {
    const char* env = std::getenv("DOTD_HEAP_FILL");
    if (env == nullptr || *env == 0) return 0;  // the default: zeroed blocks in every build
    if (std::strcmp(env, "off") == 0) return -1;
    char* end = nullptr;
    const long value = std::strtol(env, &end, 16);
    if (end == env || *end != 0 || value < 0 || value > 0xff) return -1;
    return static_cast<int>(value);
}
}  // namespace

int HeapFillByte() {
    static const int byte = ReadFillByte();
    return byte;
}

void HeapFill(void* block, size_t size) {
    const int byte = HeapFillByte();
    if (byte >= 0 && block != nullptr) std::memset(block, byte, size);
}

}  // namespace dotd

// The global operator new / new[] (the replaceable forms; delete stays the CRT's, which frees malloc'd blocks).
// Engine objects are created with plain new, so their unported fields hold the fill.
void* operator new(size_t size) {
    void* block = std::malloc(size == 0 ? 1 : size);
    if (block == nullptr) throw std::bad_alloc();
    dotd::HeapFill(block, size);
    return block;
}

void* operator new[](size_t size) { return ::operator new(size); }

void* operator new(size_t size, const std::nothrow_t&) noexcept {
    void* block = std::malloc(size == 0 ? 1 : size);
    dotd::HeapFill(block, size);
    return block;
}

void* operator new[](size_t size, const std::nothrow_t& tag) noexcept { return ::operator new(size, tag); }
