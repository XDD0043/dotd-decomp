// astc_transcode_test - the DXT to ASTC 4x4 transcoder (platform/gfx/texture_transcode.h) on a level's textures: every
// block of every mip level of every DDS texture in the level file, transcoded, then decoded by astc-encoder's own
// decoder (physical_to_symbolic + decompress_symbolic_block, the LDR profile) and compared with the RGBA8 the web build
// made of it until now (DecodeS3tc). Prints, per block kind, the largest and the mean difference per channel, and
// the transcoding speed. Fails when a block of the near-exact kinds differs by more than kExactTolerance in a channel,
// or a varying-alpha block's colour does.
//
//   astc_transcode_test [LEVEL.KP3 ...]   default: DOTD_USRDIR/LVL010/LVL010.KP3 (skipped, 77, without it)
// The game file is only read.
#include <algorithm>
#include <chrono>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <vector>

#include "astcenc_internal.h"
#include "platform/gfx/texture_transcode.h"

using dotd::gfx::AstcStats;
using dotd::gfx::TextureFormat;

namespace {

constexpr int kExactTolerance = 3;   // 8-bit steps: ASTC's interpolation rounds differently from DXT's thirds
constexpr int kFittedTolerance = 5;  // the colour of a varying-alpha block (endpoints at 48 levels)

struct KindStats {
    uint64_t blocks = 0;
    int maxDiff[4] = {};
    double sumDiff[4] = {};
    uint64_t texels = 0;
};

const char* const kKindNames[5] = {"DXT1 four colours", "DXT1 three colours", "DXT1 with transparent texels",
                                   "DXT3/5 one alpha", "DXT3/5 varying alpha"};

bool ReadFile(const std::string& path, std::vector<uint8_t>* out) {
    FILE* f = std::fopen(path.c_str(), "rb");
    if (f == nullptr) return false;
    std::fseek(f, 0, SEEK_END);
    out->resize(static_cast<size_t>(std::ftell(f)));
    std::fseek(f, 0, SEEK_SET);
    const bool ok = std::fread(out->data(), 1, out->size(), f) == out->size();
    std::fclose(f);
    return ok;
}

uint32_t U32(const uint8_t* p) { return p[0] | (p[1] << 8) | (p[2] << 16) | (static_cast<uint32_t>(p[3]) << 24); }

}  // namespace

int main(int argc, char** argv) {
    std::vector<std::string> files;
    for (int i = 1; i < argc; ++i) files.push_back(argv[i]);
    if (files.empty()) {
        const char* usrdir = std::getenv("DOTD_USRDIR");
        if (usrdir == nullptr) {
            std::printf("astc_transcode_test: no DOTD_USRDIR and no file given: skipped\n");
            return 77;
        }
        files.push_back(std::string(usrdir) + "/LVL010/LVL010.KP3");
    }
    if (!dotd::gfx::AstcTranscodeReady()) {
        std::printf("astc_transcode_test: the transcoder's block modes are not set up\n");
        return 1;
    }
    block_size_descriptor* bsd = new block_size_descriptor();
    init_block_size_descriptor(4, 4, 1, false, 4, 1.0f, *bsd);

    KindStats kinds[5];
    AstcStats total;
    uint64_t textures = 0, levels = 0;
    double transcodeMs = 0.0, referenceMs = 0.0;
    uint64_t alphaOver[3] = {}, alphaTexels = 0;  // varying-alpha texels off by more than 8, 16, 32
    bool failed = false;
    for (const std::string& path : files) {
        std::vector<uint8_t> file;
        if (!ReadFile(path, &file)) {
            std::printf("astc_transcode_test: %s not readable: skipped\n", path.c_str());
            return 77;
        }
        for (size_t at = 0; at + 128 <= file.size(); ++at) {
            if (std::memcmp(&file[at], "DDS |\0\0\0", 8) != 0) continue;
            const uint8_t* h = &file[at];
            const int height = static_cast<int>(U32(h + 12)), width = static_cast<int>(U32(h + 16));
            const int mips = std::max(1, static_cast<int>(U32(h + 28)));
            const uint32_t fourcc = U32(h + 84);
            TextureFormat format;
            if (fourcc == U32(reinterpret_cast<const uint8_t*>("DXT1"))) format = TextureFormat::kBC1;
            else if (fourcc == U32(reinterpret_cast<const uint8_t*>("DXT3"))) format = TextureFormat::kBC2;
            else if (fourcc == U32(reinterpret_cast<const uint8_t*>("DXT5"))) format = TextureFormat::kBC3;
            else continue;
            if (width <= 0 || height <= 0 || width > 4096 || height > 4096) continue;
            const size_t blockBytes = format == TextureFormat::kBC1 ? 8 : 16;
            size_t offset = at + 128;
            int w = width, hgt = height;
            ++textures;
            for (int level = 0; level < mips; ++level) {
                const size_t bw = (w + 3) / 4, bh = (hgt + 3) / 4, size = bw * bh * blockBytes;
                if (offset + size > file.size()) break;
                const uint8_t* data = &file[offset];
                AstcStats stats;
                const std::vector<uint8_t> astc = dotd::gfx::TranscodeS3tcToAstc4x4(format, w, hgt, data, &stats);
                transcodeMs += stats.ms;
                AstcStats refStats;
                dotd::gfx::SetAstcReferencePacking(true);
                const std::vector<uint8_t> reference = dotd::gfx::TranscodeS3tcToAstc4x4(format, w, hgt, data, &refStats);
                dotd::gfx::SetAstcReferencePacking(false);
                referenceMs += refStats.ms;
                if (reference != astc) {
                    for (size_t i = 0; i < astc.size(); i += 16) {
                        if (std::memcmp(&astc[i], &reference[i], 16) != 0) {
                            std::printf("FAIL: the fast packing differs from symbolic_to_physical: block %zu, level %d %dx%d\n",
                                        i / 16, level, w, hgt);
                            break;
                        }
                    }
                    failed = true;
                }
                const std::vector<uint8_t> rgba = dotd::gfx::DecodeS3tc(format, w, hgt, data);
                ++levels;
                // Which kind each block was: the transcoder counts; recover the kind per block by transcoding alone.
                for (size_t i = 0; i < bw * bh; ++i) {
                    AstcStats one;
                    const std::vector<uint8_t> single = dotd::gfx::TranscodeS3tcToAstc4x4(format, 4, 4, data + i * blockBytes, &one);
                    int kind = 0;
                    for (int k = 0; k < 5; ++k) {
                        if (one.blocks[k] != 0) kind = k;
                    }
                    if (std::memcmp(single.data(), &astc[i * 16], 16) != 0) {
                        std::printf("FAIL: block %zu of %s level %d not deterministic\n", i, path.c_str(), level);
                        failed = true;
                    }
                    symbolic_compressed_block scb;
                    physical_to_symbolic(*bsd, &astc[i * 16], scb);
                    if (scb.block_type == SYM_BTYPE_ERROR) {
                        std::printf("FAIL: block %zu (kind %d) does not decode\n", i, kind);
                        failed = true;
                        continue;
                    }
                    image_block blk;
                    std::memset(&blk, 0, sizeof(blk));
                    blk.texel_count = 16;
                    blk.decode_unorm8 = true;
                    decompress_symbolic_block(ASTCENC_PRF_LDR, *bsd, 0, 0, 0, scb, blk);
                    KindStats& ks = kinds[kind];
                    ++ks.blocks;
                    const int x0 = static_cast<int>(i % bw) * 4, y0 = static_cast<int>(i / bw) * 4;
                    for (int t = 0; t < 16; ++t) {
                        const int x = x0 + (t & 3), y = y0 + (t >> 2);
                        if (x >= w || y >= hgt) continue;
                        const uint8_t* ref = &rgba[(static_cast<size_t>(y) * w + x) * 4];
                        const float got[4] = {blk.data_r[t], blk.data_g[t], blk.data_b[t], blk.data_a[t]};
                        ++ks.texels;
                        for (int c = 0; c < 4; ++c) {
                            const int v = static_cast<int>(std::lround(got[c] * 255.0f));  // (the decoder gives 0..1)
                            const int d = std::abs(v - ref[c]);
                            // Transparent DXT1 texels: only the alpha counts (their colour is never seen).
                            if (kind == 2 && ref[3] == 0 && c < 3) continue;
                            ks.maxDiff[c] = std::max(ks.maxDiff[c], d);
                            ks.sumDiff[c] += d;
                            const bool alphaFitted = kind == 4 && c == 3;
                            if (alphaFitted) {
                                ++alphaTexels;
                                alphaOver[0] += d > 8;
                                alphaOver[1] += d > 16;
                                alphaOver[2] += d > 32;
                            }
                            const int tolerance = kind == 4 ? kFittedTolerance : kExactTolerance;
                            if (!alphaFitted && d > tolerance && !failed) {
                                std::printf("FAIL: %s, block %zu texel %d channel %d: %d, DXT %d (level %d %dx%d)\n",
                                            kKindNames[kind], i, t, c, v, ref[c], level, w, hgt);
                                failed = true;
                            }
                        }
                    }
                }
                for (int k = 0; k < 5; ++k) total.blocks[k] += stats.blocks[k];
                offset += size;
                w = w > 1 ? w / 2 : 1;
                hgt = hgt > 1 ? hgt / 2 : 1;
            }
        }
    }
    uint64_t blocks = 0;
    for (uint64_t b : total.blocks) blocks += b;
    std::printf("%llu textures, %llu levels, %llu blocks; transcoding %.1f ms (%.0f ns a block; symbolic_to_physical "
                "%.1f ms)\n",
                static_cast<unsigned long long>(textures), static_cast<unsigned long long>(levels),
                static_cast<unsigned long long>(blocks), transcodeMs, blocks ? transcodeMs * 1e6 / blocks : 0.0, referenceMs);
    if (alphaTexels != 0) {
        std::printf("  varying alpha: texels off by more than 8 / 16 / 32: %.2f%% / %.2f%% / %.3f%%\n",
                    100.0 * alphaOver[0] / alphaTexels, 100.0 * alphaOver[1] / alphaTexels, 100.0 * alphaOver[2] / alphaTexels);
    }
    for (int k = 0; k < 5; ++k) {
        const KindStats& ks = kinds[k];
        if (ks.blocks == 0) continue;
        std::printf("  %-30s %9llu blocks; difference max R %d G %d B %d A %d, mean %.2f %.2f %.2f %.2f\n", kKindNames[k],
                    static_cast<unsigned long long>(ks.blocks), ks.maxDiff[0], ks.maxDiff[1], ks.maxDiff[2], ks.maxDiff[3],
                    ks.sumDiff[0] / ks.texels, ks.sumDiff[1] / ks.texels, ks.sumDiff[2] / ks.texels, ks.sumDiff[3] / ks.texels);
    }
    if (blocks == 0) {
        std::printf("FAIL: no DXT texture found\n");
        return 1;
    }
    std::printf(failed ? "FAILED\n" : "ok\n");
    return failed ? 1 : 0;
}
