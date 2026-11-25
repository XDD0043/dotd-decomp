// The disc SELF decrypted into its ELF (self_decrypt.h).
#include "platform/self_decrypt.h"

#include <algorithm>
#include <cstdio>
#include <cstring>

namespace dotd::platform {
namespace {

// ---- AES (FIPS-197): the block cipher with 128- and 256-bit keys, both directions --------------------------------
struct AesTables {
    uint8_t sbox[256];
    uint8_t inv[256];
    AesTables() {
        // The S-box from the multiplicative inverse in GF(2^8) and the affine map: p walks the field by powers of 3,
        // q by powers of 3's inverse, so q = 1/p at every step.
        uint8_t p = 1, q = 1;
        do {
            p = static_cast<uint8_t>(p ^ (p << 1) ^ ((p & 0x80) != 0 ? 0x1b : 0));
            q = static_cast<uint8_t>(q ^ (q << 1));
            q = static_cast<uint8_t>(q ^ (q << 2));
            q = static_cast<uint8_t>(q ^ (q << 4));
            if ((q & 0x80) != 0) q ^= 0x09;
            const auto rotl = [](uint8_t x, int n) { return static_cast<uint8_t>((x << n) | (x >> (8 - n))); };
            sbox[p] = static_cast<uint8_t>(q ^ rotl(q, 1) ^ rotl(q, 2) ^ rotl(q, 3) ^ rotl(q, 4) ^ 0x63);
        } while (p != 1);
        sbox[0] = 0x63;
        for (int i = 0; i < 256; ++i) inv[sbox[i]] = static_cast<uint8_t>(i);
    }
};

const AesTables& Tables() {
    static const AesTables tables;
    return tables;
}

uint8_t XTime(uint8_t x) { return static_cast<uint8_t>((x << 1) ^ ((x & 0x80) != 0 ? 0x1b : 0)); }

uint8_t Mul(uint8_t a, uint8_t b) {
    uint8_t r = 0;
    while (b != 0) {
        if ((b & 1) != 0) r ^= a;
        a = XTime(a);
        b >>= 1;
    }
    return r;
}

class Aes {
public:
    // `bits` 128 or 256.
    Aes(const uint8_t* key, int bits) {
        const int nk = bits / 32;
        rounds_ = nk + 6;
        const AesTables& t = Tables();
        std::memcpy(rk_, key, static_cast<size_t>(nk) * 4);
        uint8_t rcon = 1;
        for (int i = nk; i < 4 * (rounds_ + 1); ++i) {
            uint8_t w[4];
            std::memcpy(w, rk_ + (i - 1) * 4, 4);
            if (i % nk == 0) {
                const uint8_t first = w[0];
                w[0] = static_cast<uint8_t>(t.sbox[w[1]] ^ rcon);
                w[1] = t.sbox[w[2]];
                w[2] = t.sbox[w[3]];
                w[3] = t.sbox[first];
                rcon = XTime(rcon);
            } else if (nk > 6 && i % nk == 4) {
                for (uint8_t& b : w) b = t.sbox[b];
            }
            for (int j = 0; j < 4; ++j) rk_[i * 4 + j] = static_cast<uint8_t>(rk_[(i - nk) * 4 + j] ^ w[j]);
        }
    }

    void EncryptBlock(const uint8_t in[16], uint8_t out[16]) const {
        const AesTables& t = Tables();
        uint8_t s[16];
        for (int i = 0; i < 16; ++i) s[i] = static_cast<uint8_t>(in[i] ^ rk_[i]);
        for (int round = 1; round <= rounds_; ++round) {
            uint8_t m[16];
            for (int c = 0; c < 4; ++c) {  // SubBytes + ShiftRows
                for (int r = 0; r < 4; ++r) m[c * 4 + r] = t.sbox[s[((c + r) & 3) * 4 + r]];
            }
            if (round != rounds_) {  // MixColumns
                for (int c = 0; c < 4; ++c) {
                    const uint8_t a0 = m[c * 4], a1 = m[c * 4 + 1], a2 = m[c * 4 + 2], a3 = m[c * 4 + 3];
                    const uint8_t all = static_cast<uint8_t>(a0 ^ a1 ^ a2 ^ a3);
                    m[c * 4] = static_cast<uint8_t>(a0 ^ all ^ XTime(static_cast<uint8_t>(a0 ^ a1)));
                    m[c * 4 + 1] = static_cast<uint8_t>(a1 ^ all ^ XTime(static_cast<uint8_t>(a1 ^ a2)));
                    m[c * 4 + 2] = static_cast<uint8_t>(a2 ^ all ^ XTime(static_cast<uint8_t>(a2 ^ a3)));
                    m[c * 4 + 3] = static_cast<uint8_t>(a3 ^ all ^ XTime(static_cast<uint8_t>(a3 ^ a0)));
                }
            }
            for (int i = 0; i < 16; ++i) s[i] = static_cast<uint8_t>(m[i] ^ rk_[round * 16 + i]);
        }
        std::memcpy(out, s, 16);
    }

    void DecryptBlock(const uint8_t in[16], uint8_t out[16]) const {
        const AesTables& t = Tables();
        uint8_t s[16];
        for (int i = 0; i < 16; ++i) s[i] = static_cast<uint8_t>(in[i] ^ rk_[rounds_ * 16 + i]);
        for (int round = rounds_ - 1; round >= 0; --round) {
            uint8_t m[16];
            for (int c = 0; c < 4; ++c) {  // InvShiftRows + InvSubBytes
                for (int r = 0; r < 4; ++r) m[((c + r) & 3) * 4 + r] = t.inv[s[c * 4 + r]];
            }
            for (int i = 0; i < 16; ++i) m[i] ^= rk_[round * 16 + i];
            if (round != 0) {  // InvMixColumns
                for (int c = 0; c < 4; ++c) {
                    const uint8_t a0 = m[c * 4], a1 = m[c * 4 + 1], a2 = m[c * 4 + 2], a3 = m[c * 4 + 3];
                    m[c * 4] = static_cast<uint8_t>(Mul(a0, 14) ^ Mul(a1, 11) ^ Mul(a2, 13) ^ Mul(a3, 9));
                    m[c * 4 + 1] = static_cast<uint8_t>(Mul(a0, 9) ^ Mul(a1, 14) ^ Mul(a2, 11) ^ Mul(a3, 13));
                    m[c * 4 + 2] = static_cast<uint8_t>(Mul(a0, 13) ^ Mul(a1, 9) ^ Mul(a2, 14) ^ Mul(a3, 11));
                    m[c * 4 + 3] = static_cast<uint8_t>(Mul(a0, 11) ^ Mul(a1, 13) ^ Mul(a2, 9) ^ Mul(a3, 14));
                }
            }
            std::memcpy(s, m, 16);
        }
        std::memcpy(out, s, 16);
    }

private:
    uint8_t rk_[16 * 15];
    int rounds_;
};

// CBC decryption in place (`size` a multiple of 16).
void CbcDecrypt(const Aes& aes, const uint8_t iv[16], uint8_t* data, size_t size) {
    uint8_t chain[16];
    std::memcpy(chain, iv, 16);
    for (size_t at = 0; at + 16 <= size; at += 16) {
        uint8_t cipher[16], plain[16];
        std::memcpy(cipher, data + at, 16);
        aes.DecryptBlock(cipher, plain);
        for (int i = 0; i < 16; ++i) data[at + i] = static_cast<uint8_t>(plain[i] ^ chain[i]);
        std::memcpy(chain, cipher, 16);
    }
}

// CTR in place: the counter is the whole 16-byte IV, big-endian, incremented once per block.
void CtrCrypt(const Aes& aes, const uint8_t iv[16], uint8_t* data, size_t size) {
    uint8_t counter[16], stream[16];
    std::memcpy(counter, iv, 16);
    for (size_t at = 0; at < size; at += 16) {
        aes.EncryptBlock(counter, stream);
        const size_t n = std::min<size_t>(16, size - at);
        for (size_t i = 0; i < n; ++i) data[at + i] ^= stream[i];
        for (int i = 15; i >= 0; --i) {
            if (++counter[i] != 0) break;
        }
    }
}

// ---- the SELF ---------------------------------------------------------------------------------------------------
uint16_t Be16(const uint8_t* p) { return static_cast<uint16_t>(p[0] << 8 | p[1]); }
uint32_t Be32(const uint8_t* p) { return static_cast<uint32_t>(p[0]) << 24 | static_cast<uint32_t>(p[1]) << 16 | static_cast<uint32_t>(p[2]) << 8 | p[3]; }
uint64_t Be64(const uint8_t* p) { return static_cast<uint64_t>(Be32(p)) << 32 | Be32(p + 4); }

void FromHex(const char* hex, uint8_t* out, size_t n) {
    const auto nibble = [](char c) { return c <= '9' ? c - '0' : (c | 0x20) - 'a' + 10; };
    for (size_t i = 0; i < n; ++i) out[i] = static_cast<uint8_t>(nibble(hex[2 * i]) << 4 | nibble(hex[2 * i + 1]));
}

// The retail application keys by key revision (the SCE header's flags): erk (AES-256 key) and riv (IV) of the
// metadata info. Revision 0x0001 is BLUS30205's (firmware 3.30-era application keys; RPCS3 key_vault.cpp, KEY_APP).
struct AppKey {
    uint16_t revision;
    const char* erk;
    const char* riv;
};
const AppKey kAppKeys[] = {
    {0x0001, "79481839C406A632BDB4AC093D73D99AE1587F24CE7E69192C1CD0010274A8AB", "6F0F25E1C8C4B7AE70DF968B04521DDA"},
};

constexpr uint32_t kSceMagic = 0x53434500;   // "SCE\0"
constexpr uint16_t kSceTypeSelf = 1;
constexpr uint32_t kProgramTypeApp = 4;
constexpr uint16_t kFlagDebug = 0x8000;
constexpr uint32_t kSectionPhdr = 2;         // metadata section type: an ELF segment (program header)
constexpr uint32_t kEncryptedAesCtr = 3;
constexpr uint32_t kCompressedZlib = 2;

bool Fail(std::string* error, const std::string& message) {
    if (error != nullptr) *error = message;
    return false;
}

std::string Hex(uint64_t v) {
    char text[24];
    std::snprintf(text, sizeof text, "0x%llx", static_cast<unsigned long long>(v));
    return text;
}

}  // namespace

bool IsSelf(const uint8_t* data, size_t size) { return size >= 4 && Be32(data) == kSceMagic; }

bool DecryptSelf(const std::vector<uint8_t>& self, std::vector<uint8_t>* elf, std::string* error) {
    const uint8_t* f = self.data();
    const uint64_t size = self.size();
    const auto inside = [size](uint64_t offset, uint64_t length) { return offset <= size && length <= size - offset; };
    if (!inside(0, 0x70) || !IsSelf(f, self.size())) return Fail(error, "not a SELF file (no SCE header)");
    // SCE header: magic, version, flags (the key revision), type, metadata offset, header size, data size.
    const uint16_t revision = Be16(f + 0x08);
    const uint16_t sceType = Be16(f + 0x0a);
    const uint64_t metaOffset = 0x20 + static_cast<uint64_t>(Be32(f + 0x0c));
    const uint64_t headerSize = Be64(f + 0x10);
    if (sceType != kSceTypeSelf) return Fail(error, "the SCE file is not a SELF (type " + std::to_string(sceType) + ")");
    if ((revision & kFlagDebug) != 0) return Fail(error, "debug SELFs are not handled");
    // Extended header: the offsets of the program info, ELF header, program headers, section headers, segment info.
    const uint64_t appInfo = Be64(f + 0x28), ehdrAt = Be64(f + 0x30), phdrAt = Be64(f + 0x38), shdrAt = Be64(f + 0x40);
    if (!inside(appInfo, 0x20) || !inside(ehdrAt, 0x40)) return Fail(error, "the SELF headers are truncated");
    const uint32_t programType = Be32(f + appInfo + 0x0c);
    if (programType != kProgramTypeApp) {
        return Fail(error, "the SELF is not a disc application (program type " + std::to_string(programType) +
                               "; PSN/NPDRM executables are not handled)");
    }
    const uint8_t* ehdr = f + ehdrAt;
    if (std::memcmp(ehdr, "\x7f" "ELF", 4) != 0 || ehdr[4] != 2) return Fail(error, "the SELF does not hold a 64-bit ELF");
    const uint64_t phoff = Be64(ehdr + 0x20), shoff = Be64(ehdr + 0x28);
    const uint16_t phentsize = Be16(ehdr + 0x36), phnum = Be16(ehdr + 0x38);
    const uint16_t shentsize = Be16(ehdr + 0x3a), shnum = Be16(ehdr + 0x3c);
    if (phentsize != 0x38 || !inside(phdrAt, static_cast<uint64_t>(phnum) * 0x38)) {
        return Fail(error, "the SELF's program headers are truncated");
    }

    const AppKey* key = nullptr;
    for (const AppKey& k : kAppKeys) {
        if (k.revision == revision) key = &k;
    }
    if (key == nullptr) return Fail(error, "no application key for key revision " + Hex(revision));

    // Metadata info (64 bytes, AES-256-CBC with the revision's key): the key and IV of the metadata headers.
    if (!inside(metaOffset, 0x40) || headerSize < metaOffset + 0x40 || !inside(metaOffset + 0x40, headerSize - metaOffset - 0x40)) {
        return Fail(error, "the SELF metadata is truncated");
    }
    uint8_t info[0x40];
    std::memcpy(info, f + metaOffset, sizeof info);
    {
        uint8_t erk[32], riv[16];
        FromHex(key->erk, erk, sizeof erk);
        FromHex(key->riv, riv, sizeof riv);
        CbcDecrypt(Aes(erk, 256), riv, info, sizeof info);
    }
    if (info[0x10] != 0 || info[0x30] != 0) return Fail(error, "the SELF metadata did not decrypt (wrong key)");

    // Metadata header, section headers and the data keys (AES-128-CTR with the metadata info's key and IV).
    std::vector<uint8_t> meta(f + metaOffset + 0x40, f + headerSize);
    CtrCrypt(Aes(info, 128), info + 0x20, meta.data(), meta.size());
    if (meta.size() < 0x20) return Fail(error, "the SELF metadata header is truncated");
    const uint32_t sectionCount = Be32(meta.data() + 0x0c);
    const uint32_t keyCount = Be32(meta.data() + 0x10);
    const uint64_t keysAt = 0x20 + static_cast<uint64_t>(sectionCount) * 0x30;
    if (keysAt + static_cast<uint64_t>(keyCount) * 0x10 > meta.size()) return Fail(error, "the SELF section table is truncated");

    // The ELF: header, program headers, every segment at its file offset, section headers.
    uint64_t elfSize = std::max<uint64_t>(0x40, phoff + static_cast<uint64_t>(phnum) * 0x38);
    for (uint32_t i = 0; i < phnum; ++i) {
        const uint8_t* ph = f + phdrAt + i * 0x38;
        elfSize = std::max(elfSize, Be64(ph + 0x08) + Be64(ph + 0x20));  // p_offset + p_filesz
    }
    if (shdrAt != 0 && shnum != 0) {
        if (!inside(shdrAt, static_cast<uint64_t>(shnum) * shentsize)) return Fail(error, "the SELF's section headers are truncated");
        elfSize = std::max(elfSize, shoff + static_cast<uint64_t>(shnum) * shentsize);
    }
    if (elfSize > (1ull << 31)) return Fail(error, "the ELF would be larger than 2 GB");
    elf->assign(static_cast<size_t>(elfSize), 0);
    std::memcpy(elf->data(), ehdr, 0x40);
    std::memcpy(elf->data() + phoff, f + phdrAt, static_cast<size_t>(phnum) * 0x38);

    for (uint32_t i = 0; i < sectionCount; ++i) {
        const uint8_t* s = meta.data() + 0x20 + i * 0x30;
        const uint64_t dataOffset = Be64(s), dataSize = Be64(s + 0x08);
        const uint32_t type = Be32(s + 0x10), programIndex = Be32(s + 0x14);
        const uint32_t encrypted = Be32(s + 0x20), keyIndex = Be32(s + 0x24), ivIndex = Be32(s + 0x28);
        const uint32_t compressed = Be32(s + 0x2c);
        if (type != kSectionPhdr) continue;  // (the SHDR and SCE-version sections: the ELF takes them elsewhere)
        if (programIndex >= phnum || !inside(dataOffset, dataSize)) return Fail(error, "SELF section " + std::to_string(i) + " is out of range");
        if (compressed == kCompressedZlib) return Fail(error, "compressed SELF segments are not handled");
        const uint64_t target = Be64(f + phdrAt + programIndex * 0x38 + 0x08);
        if (target + dataSize > elf->size()) return Fail(error, "SELF section " + std::to_string(i) + " does not fit its segment");
        uint8_t* out = elf->data() + target;
        std::memcpy(out, f + dataOffset, static_cast<size_t>(dataSize));
        if (encrypted == kEncryptedAesCtr) {
            if (keyIndex >= keyCount || ivIndex >= keyCount) return Fail(error, "SELF section " + std::to_string(i) + " names a missing key");
            CtrCrypt(Aes(meta.data() + keysAt + keyIndex * 0x10, 128), meta.data() + keysAt + ivIndex * 0x10, out,
                     static_cast<size_t>(dataSize));
        }
    }
    if (shdrAt != 0 && shnum != 0) std::memcpy(elf->data() + shoff, f + shdrAt, static_cast<size_t>(shnum) * shentsize);
    return true;
}

}  // namespace dotd::platform
