#pragma once
// The disc's EBOOT.BIN (a SELF: the executable, encrypted and signed) turned back into the plain ELF that RPCS3's
// "Utilities > Decrypt PS3 Binaries" writes as EBOOT.elf. The renderer reads the game's Cg shader sources from that
// ELF (platform/gfx/cg_to_glsl.cpp), so a player only needs the disc's files: no RPCS3 and no decrypted copy.
//
// Only what the disc's application SELF uses is handled: SCE header type 1 (SELF), program type 4 (application), a
// retail key revision from the application key table, segments encrypted with AES-128-CTR and stored uncompressed.
// NPDRM (PSN) executables, debug SELFs and compressed segments are refused with a message. The signature is not
// checked: the ELF's SHA-256 is compared by the caller where it matters (setup.ps1, tests/self_decrypt_test.cpp).
//
// Written from the format (SCE header, extended header, metadata info / header / section headers) and checked
// byte for byte against RPCS3's output for BLUS30205; the key values are public data (RPCS3's Crypto/key_vault.cpp).
#include <cstdint>
#include <string>
#include <vector>

namespace dotd::platform {

// True when `data` starts with the SCE magic ("SCE\0").
bool IsSelf(const uint8_t* data, size_t size);

// `self` decrypted into the ELF file `elf` (program headers, segments, section headers at their ELF offsets). False
// with `error` set when the file is not a SELF this handles.
bool DecryptSelf(const std::vector<uint8_t>& self, std::vector<uint8_t>* elf, std::string* error);

}  // namespace dotd::platform
