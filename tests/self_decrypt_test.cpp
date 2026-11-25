// platform/self_decrypt: the disc's EBOOT.BIN decrypted in memory must equal the EBOOT.elf RPCS3's
// "Decrypt PS3 Binaries" writes, byte for byte (SHA-256 c6ca6b1f...2e3455 for BLUS30205, work/quad-game-identity.json).
// Needs DOTD_USRDIR with both files; exit 77 (skipped) without them. Also checks a non-SELF and a truncated file are
// refused instead of crashing.
#include <chrono>
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <iterator>
#include <string>
#include <vector>

#include "platform/self_decrypt.h"

namespace {

bool ReadFile(const std::string& path, std::vector<uint8_t>* out) {
    std::ifstream in(path, std::ios::binary);
    if (!in) return false;
    out->assign(std::istreambuf_iterator<char>(in), std::istreambuf_iterator<char>());
    return true;
}

}  // namespace

int main() {
    int failures = 0;
    std::string error;
    std::vector<uint8_t> elf;
    {
        const std::vector<uint8_t> notSelf = {0x7f, 'E', 'L', 'F', 2, 2, 1, 0};
        if (dotd::platform::DecryptSelf(notSelf, &elf, &error)) {
            std::printf("FAIL: a plain ELF header was accepted as a SELF\n");
            ++failures;
        }
    }
    const char* usrdir = std::getenv("DOTD_USRDIR");
    if (usrdir == nullptr) {
        std::printf("SKIP: DOTD_USRDIR not set\n");
        return failures != 0 ? 1 : 77;
    }
    std::vector<uint8_t> self, expected;
    if (!ReadFile(std::string(usrdir) + "/EBOOT.BIN", &self) || !ReadFile(std::string(usrdir) + "/EBOOT.elf", &expected)) {
        std::printf("SKIP: EBOOT.BIN and EBOOT.elf are not both in %s\n", usrdir);
        return failures != 0 ? 1 : 77;
    }
    {
        const std::vector<uint8_t> truncated(self.begin(), self.begin() + 0x500);
        if (dotd::platform::DecryptSelf(truncated, &elf, &error)) {
            std::printf("FAIL: a truncated SELF was accepted\n");
            ++failures;
        }
    }
    const auto start = std::chrono::steady_clock::now();
    if (!dotd::platform::DecryptSelf(self, &elf, &error)) {
        std::printf("FAIL: DecryptSelf: %s\n", error.c_str());
        return 1;
    }
    const double ms = std::chrono::duration<double, std::milli>(std::chrono::steady_clock::now() - start).count();
    if (elf.size() != expected.size()) {
        std::printf("FAIL: %zu bytes decrypted, EBOOT.elf has %zu\n", elf.size(), expected.size());
        return 1;
    }
    for (size_t i = 0; i < elf.size(); ++i) {
        if (elf[i] != expected[i]) {
            std::printf("FAIL: first difference at file offset 0x%zx\n", i);
            return 1;
        }
    }
    std::printf("ok: EBOOT.BIN decrypted to %zu bytes identical to EBOOT.elf (%.0f ms)\n", elf.size(), ms);
    return failures != 0 ? 1 : 0;
}
