// texture_transcode.cpp - DXT for a GPU without S3TC: decoded to RGBA8, or rewritten as ASTC 4x4 (texture_transcode.h).
#include "platform/gfx/texture_transcode.h"

#include <algorithm>
#include <chrono>
#include <condition_variable>
#include <cstring>
#include <functional>
#include <mutex>
#include <thread>

#if DOTD_HAVE_ASTCENC
#include "astcenc_internal.h"
#endif

namespace dotd::gfx {

namespace {

// (Rgb565, DecodeColorBlock and DecodeS3tc were device.cpp's.)
void Rgb565(uint16_t c, uint8_t out[3]) {
    out[0] = static_cast<uint8_t>(((c >> 11) & 0x1f) * 255 / 31);
    out[1] = static_cast<uint8_t>(((c >> 5) & 0x3f) * 255 / 63);
    out[2] = static_cast<uint8_t>((c & 0x1f) * 255 / 31);
}

void DecodeColorBlock(const uint8_t* b, bool dxt1, uint8_t out[16][4]) {
    const uint16_t c0 = static_cast<uint16_t>(b[0] | (b[1] << 8));
    const uint16_t c1 = static_cast<uint16_t>(b[2] | (b[3] << 8));
    uint8_t pal[4][4];
    Rgb565(c0, pal[0]);
    Rgb565(c1, pal[1]);
    pal[0][3] = pal[1][3] = 255;
    if (!dxt1 || c0 > c1) {
        for (int k = 0; k < 3; ++k) {
            pal[2][k] = static_cast<uint8_t>((2 * pal[0][k] + pal[1][k]) / 3);
            pal[3][k] = static_cast<uint8_t>((pal[0][k] + 2 * pal[1][k]) / 3);
        }
        pal[2][3] = pal[3][3] = 255;
    } else {
        for (int k = 0; k < 3; ++k) pal[2][k] = static_cast<uint8_t>((pal[0][k] + pal[1][k]) / 2);
        pal[2][3] = 255;
        pal[3][0] = pal[3][1] = pal[3][2] = pal[3][3] = 0;
    }
    const uint32_t bits = static_cast<uint32_t>(b[4]) | (static_cast<uint32_t>(b[5]) << 8) |
                          (static_cast<uint32_t>(b[6]) << 16) | (static_cast<uint32_t>(b[7]) << 24);
    for (int i = 0; i < 16; ++i) std::memcpy(out[i], pal[(bits >> (2 * i)) & 3], 4);
}

}  // namespace

std::vector<uint8_t> DecodeS3tc(TextureFormat format, int width, int height, const uint8_t* data) {
    std::vector<uint8_t> rgba(static_cast<size_t>(width) * height * 4, 0);
    const int bw = (width + 3) / 4, bh = (height + 3) / 4;
    const int blockBytes = format == TextureFormat::kBC1 ? 8 : 16;
    for (int by = 0; by < bh; ++by) {
        for (int bx = 0; bx < bw; ++bx) {
            const uint8_t* b = data + (static_cast<size_t>(by) * bw + bx) * blockBytes;
            uint8_t px[16][4];
            DecodeColorBlock(format == TextureFormat::kBC1 ? b : b + 8, format == TextureFormat::kBC1, px);
            if (format == TextureFormat::kBC2) {
                for (int i = 0; i < 16; ++i) {
                    const uint8_t nib = static_cast<uint8_t>((b[i / 2] >> ((i & 1) * 4)) & 0xf);
                    px[i][3] = static_cast<uint8_t>(nib * 17);
                }
            } else if (format == TextureFormat::kBC3) {
                const uint8_t a0 = b[0], a1 = b[1];
                uint8_t pal[8];
                pal[0] = a0;
                pal[1] = a1;
                if (a0 > a1) {
                    for (int k = 1; k < 7; ++k) pal[k + 1] = static_cast<uint8_t>(((7 - k) * a0 + k * a1) / 7);
                } else {
                    for (int k = 1; k < 5; ++k) pal[k + 1] = static_cast<uint8_t>(((5 - k) * a0 + k * a1) / 5);
                    pal[6] = 0;
                    pal[7] = 255;
                }
                uint64_t bits = 0;
                for (int k = 0; k < 6; ++k) bits |= static_cast<uint64_t>(b[2 + k]) << (8 * k);
                for (int i = 0; i < 16; ++i) px[i][3] = pal[(bits >> (3 * i)) & 7];
            }
            for (int i = 0; i < 16; ++i) {
                const int x = bx * 4 + (i & 3), y = by * 4 + (i >> 2);
                if (x < width && y < height) std::memcpy(&rgba[(static_cast<size_t>(y) * width + x) * 4], px[i], 4);
            }
        }
    }
    return rgba;
}

// ---- DXT to ASTC 4x4 -------------------------------------------------------------------------------------------
#if DOTD_HAVE_ASTCENC
namespace {

// The block kinds (AstcStats::blocks) and the ASTC block mode each is written with: all a 4x4 weight grid (one
// weight per texel, as DXT has one index per texel) and one partition.
enum Kind { kFour, kThree, kThreeAlpha, kOneAlpha, kVaryingAlpha, kKinds };
struct ModeInfo {
    uint16_t mode = 0;          // the 11-bit ASTC block mode
    quant_method colorQuant{};  // the endpoints' quantisation the decoder derives from the bits left
    bool dual = false;          // a second weight plane (the alpha)
    int format = 0;             // FMT_RGB (6 endpoint values) or FMT_RGBA (8)
    bool fast = false;          // 4 weight levels (plain 2-bit weights): PackFast; else symbolic_to_physical
    uint8_t header[16] = {};    // the block with every endpoint value and weight 0: mode, CEM, plane selector
};
block_size_descriptor* g_bsd = nullptr;
ModeInfo g_modes[kKinds];
int g_ready = -1;                 // -1: not set up yet
bool g_referencePacking = false;  // the test: every block through symbolic_to_physical

// astc-encoder's own packing of a block (symbolic_to_physical): the endpoint values as quantised (0..255), the
// weights 0..64, the alpha plane's in w1.
void PackReference(const ModeInfo& m, const uint8_t values[8], const uint8_t w0[16], const uint8_t* w1, uint8_t out[16]) {
    symbolic_compressed_block scb;
    std::memset(&scb, 0, sizeof(scb));
    scb.block_type = SYM_BTYPE_NONCONST;
    scb.partition_count = 1;
    scb.color_formats_matched = 1;
    scb.plane2_component = static_cast<int8_t>(m.dual ? 3 : -1);
    scb.block_mode = m.mode;
    scb.color_formats[0] = static_cast<uint8_t>(m.format);
    scb.quant_mode = m.colorQuant;
    std::memcpy(scb.color_values[0], values, m.format == FMT_RGBA ? 8 : 6);
    for (int i = 0; i < 16; ++i) {
        scb.weights[i] = w0[i];
        if (m.dual) scb.weights[WEIGHTS_PLANE2_OFFSET + i] = w1[i];
    }
    symbolic_to_physical(*g_bsd, scb, out);
}

// The same block as PackReference writes, faster (the test compares them on every block of a level): the mode's
// header, the endpoint values by the integer sequence encoding at bit 17, then the weights, two bits each, texel by
// texel (the alpha plane's after each texel's colour weight), as one bit string reversed from bit 127 down.
void PackFast(const ModeInfo& m, const uint8_t values[8], const uint8_t w0[16], const uint8_t* w1, uint8_t out[16]) {
    std::memcpy(out, m.header, 16);
    const int count = m.format == FMT_RGBA ? 8 : 6;
    uint8_t scrambled[8];
    const uint8_t* table = color_uquant_to_scrambled_pquant_tables[m.colorQuant - QUANT_6];
    for (int i = 0; i < count; ++i) scrambled[i] = table[values[i]];
    encode_ise(m.colorQuant, static_cast<unsigned>(count), scrambled, out, 17);
    uint64_t stream = 0;
    for (int i = 0, k = 0; i < 16; ++i) {
        stream |= static_cast<uint64_t>((w0[i] * 3 + 32) >> 6) << (2 * k++);  // 0, 21, 43, 64 -> 0..3
        if (m.dual) stream |= static_cast<uint64_t>((w1[i] * 3 + 32) >> 6) << (2 * k++);
    }
    // Bit j of the string to bit 127 - j of the block: byte b of the string, its bits reversed, to byte 15 - b.
    static const auto kReversed = [] {
        struct Table { uint8_t v[256]; } t{};
        for (int i = 0; i < 256; ++i) {
            int r = 0;
            for (int j = 0; j < 8; ++j) r |= ((i >> j) & 1) << (7 - j);
            t.v[i] = static_cast<uint8_t>(r);
        }
        return t;
    }();
    for (int b = 0; b < 8; ++b) out[15 - b] |= kReversed.v[(stream >> (8 * b)) & 0xff];
}

// 4x4 grid block modes (ASTC 2D block mode layout: bits 0-1 and 4 the weight range R, bits 5-6 A = 2 (4 rows),
// bits 7-8 B = 0 (4 columns), bit 10 dual plane): R = 4 is 4 weight levels, R = 3 three.
constexpr uint16_t kMode4Levels = 2 | (2 << 5);
constexpr uint16_t kMode3Levels = 1 | (1 << 4) | (2 << 5);
constexpr uint16_t kDualPlane = 1 << 10;

bool SetupMode(ModeInfo& m, uint16_t mode, int format, quant_method weightQuant, bool dual) {
    if (g_bsd->block_mode_packed_index[mode] == BLOCK_BAD_BLOCK_MODE) return false;
    const block_mode& bm = g_bsd->get_block_mode(mode);
    const decimation_info& di = g_bsd->get_decimation_info(bm.decimation_mode);
    if (di.weight_count != 16 || (bm.is_dual_plane != 0) != dual || bm.get_weight_quant_mode() != weightQuant) return false;
    // As physical_to_symbolic: 111 bits after the 17 of the header for one partition, less the weights and the
    // dual plane's component selector; the decoder takes the finest quantisation that fits.
    const int weightBits = static_cast<int>(get_ise_sequence_bitcount(dual ? 32 : 16, weightQuant));
    const int colorBits = 111 - weightBits - (dual ? 2 : 0);
    const int values = format == FMT_RGBA ? 8 : 6;
    if (colorBits < 0 || colorBits >= 128) return false;
    const int quant = quant_mode_table[values >> 1][colorBits];
    if (quant < QUANT_6) return false;
    m.mode = mode;
    m.colorQuant = static_cast<quant_method>(quant);
    m.dual = dual;
    m.format = format;
    m.fast = weightQuant == QUANT_4;
    // The header: the block with zero endpoint values and weights (both encode as zero bits).
    const uint8_t zeros[16] = {};
    PackReference(m, zeros, zeros, zeros, m.header);
    return true;
}

// The value the endpoint quantisation keeps of v (0..255): the nearest one it can represent.
inline int QuantColor(quant_method quant, int v) {
    return color_unquant_to_uquant_tables[quant - QUANT_6][std::min(255, std::max(0, v)) * 2 + 1];
}

// One ASTC block from two endpoints (8-bit RGBA; alpha unused for FMT_RGB) and the weights (0..64) of the texels,
// with a second plane for the alpha when the mode has one. The decoder swaps the endpoints (and contracts blue) when
// the second's RGB sum is the smaller: then they go in the other order with the weights reversed instead.
void Pack(Kind kind, const int e0[4], const int e1[4], const uint8_t w0[16], const uint8_t* w1, uint8_t out[16]) {
    const ModeInfo& m = g_modes[kind];
    const int comps = m.format == FMT_RGBA ? 4 : 3;
    int q0[4], q1[4];
    for (int c = 0; c < comps; ++c) {
        q0[c] = QuantColor(m.colorQuant, e0[c]);
        q1[c] = QuantColor(m.colorQuant, e1[c]);
    }
    const bool swap = q1[0] + q1[1] + q1[2] < q0[0] + q0[1] + q0[2];
    uint8_t values[8], sw0[16], sw1[16];
    for (int c = 0; c < comps; ++c) {
        values[2 * c] = static_cast<uint8_t>(swap ? q1[c] : q0[c]);
        values[2 * c + 1] = static_cast<uint8_t>(swap ? q0[c] : q1[c]);
    }
    for (int i = 0; i < 16; ++i) {
        sw0[i] = static_cast<uint8_t>(swap ? 64 - w0[i] : w0[i]);
        sw1[i] = static_cast<uint8_t>(m.dual ? (swap ? 64 - w1[i] : w1[i]) : 0);
    }
    if (m.fast && !g_referencePacking) {
        PackFast(m, values, sw0, sw1, out);
    } else {
        PackReference(m, values, sw0, sw1, out);
    }
}

// The alpha plane of a block with varying alpha: 4 levels (0, 21, 43, 64 / 64) between two endpoints, which start
// at the block's lowest and highest alpha and are fitted once more by least squares to the levels chosen; the pair
// with the smaller error is kept. `quant` is the endpoints' quantisation. Integer work but the fit's one division.
void FitAlpha(const uint8_t a[16], quant_method quant, int* outA0, int* outA1, uint8_t w[16]) {
    static const int kLevels[4] = {0, 21, 43, 64};
    int lo = 255, hi = 0;
    for (int i = 0; i < 16; ++i) {
        lo = std::min(lo, static_cast<int>(a[i]));
        hi = std::max(hi, static_cast<int>(a[i]));
    }
    int bestErr = -1;
    int c0 = lo, c1 = hi;
    for (int round = 0; round < 2; ++round) {
        const int q0 = QuantColor(quant, c0), q1 = QuantColor(quant, c1);
        int level[4];
        for (int k = 0; k < 4; ++k) level[k] = (q0 * (64 - kLevels[k]) + q1 * kLevels[k] + 32) >> 6;
        // The levels are in order (rising when q0 <= q1): a texel takes the nearest by the half-way points.
        const bool rising = q0 <= q1;
        const int t1 = level[0] + level[1], t2 = level[1] + level[2], t3 = level[2] + level[3];
        uint8_t wt[16];
        int err = 0, sw = 0, sww = 0, sa = 0, swa = 0;
        for (int i = 0; i < 16; ++i) {
            const int twice = 2 * a[i];
            const int k = rising ? (twice > t1) + (twice > t2) + (twice > t3) : (twice < t1) + (twice < t2) + (twice < t3);
            const int d = a[i] - level[k];
            err += d * d;
            wt[i] = static_cast<uint8_t>(kLevels[k]);
            sw += kLevels[k];
            sww += kLevels[k] * kLevels[k];
            sa += a[i];
            swa += kLevels[k] * a[i];
        }
        if (bestErr < 0 || err < bestErr) {
            bestErr = err;
            *outA0 = q0;
            *outA1 = q1;
            std::memcpy(w, wt, 16);
        }
        if (err == 0 || round == 1) break;
        // Least squares for a = c0 + (c1 - c0) w / 64 over the texels' weights w.
        const long long det = 16LL * sww - static_cast<long long>(sw) * sw;
        if (det <= 0) break;
        const long long slope64 = (16LL * swa - static_cast<long long>(sw) * sa) * 64;  // (c1 - c0) * det
        const double slope = static_cast<double>(slope64) / static_cast<double>(det);
        const double base = (sa - slope * sw / 64.0) / 16.0;
        c0 = static_cast<int>(base + 0.5);
        c1 = static_cast<int>(base + slope + 0.5);
    }
}

// The four colours' weights of a DXT colour block: index 0 = the first endpoint, 1 = the second, 2 = one third of
// the way, 3 = two thirds; three colours: 2 = half way (3 = transparent black, weight 0 here).
const uint8_t kFourWeights[4] = {0, 64, 21, 43};
const uint8_t kThreeWeights[4] = {0, 64, 32, 0};

void TranscodeBlock(TextureFormat format, const uint8_t* b, uint8_t out[16], AstcStats* stats) {
    const uint8_t* color = format == TextureFormat::kBC1 ? b : b + 8;
    const uint16_t c0 = static_cast<uint16_t>(color[0] | (color[1] << 8));
    const uint16_t c1 = static_cast<uint16_t>(color[2] | (color[3] << 8));
    uint8_t p0[3], p1[3];
    Rgb565(c0, p0);
    Rgb565(c1, p1);
    int e0[4] = {p0[0], p0[1], p0[2], 255}, e1[4] = {p1[0], p1[1], p1[2], 255};
    const uint32_t bits = static_cast<uint32_t>(color[4]) | (static_cast<uint32_t>(color[5]) << 8) |
                          (static_cast<uint32_t>(color[6]) << 16) | (static_cast<uint32_t>(color[7]) << 24);
    uint8_t w0[16], w1[16];
    if (format == TextureFormat::kBC1) {
        if (c0 > c1) {
            for (int i = 0; i < 16; ++i) w0[i] = kFourWeights[(bits >> (2 * i)) & 3];
            Pack(kFour, e0, e1, w0, nullptr, out);
            ++stats->blocks[kFour];
            return;
        }
        bool transparent = false;
        for (int i = 0; i < 16; ++i) {
            const uint32_t index = (bits >> (2 * i)) & 3;
            w0[i] = kThreeWeights[index];
            w1[i] = index == 3 ? 64 : 0;
            transparent |= index == 3;
        }
        if (!transparent) {
            Pack(kThree, e0, e1, w0, nullptr, out);
            ++stats->blocks[kThree];
            return;
        }
        e0[3] = 255;  // alpha plane: weight 0 opaque, 64 transparent
        e1[3] = 0;
        Pack(kThreeAlpha, e0, e1, w0, w1, out);
        ++stats->blocks[kThreeAlpha];
        return;
    }
    // DXT3 / DXT5: the colour block always has four colours; the alpha is its own.
    for (int i = 0; i < 16; ++i) w0[i] = kFourWeights[(bits >> (2 * i)) & 3];
    uint8_t alpha[16];
    if (format == TextureFormat::kBC2) {
        for (int i = 0; i < 16; ++i) alpha[i] = static_cast<uint8_t>(((b[i / 2] >> ((i & 1) * 4)) & 0xf) * 17);
    } else {
        const uint8_t a0 = b[0], a1 = b[1];
        uint8_t pal[8];
        pal[0] = a0;
        pal[1] = a1;
        if (a0 > a1) {
            for (int k = 1; k < 7; ++k) pal[k + 1] = static_cast<uint8_t>(((7 - k) * a0 + k * a1) / 7);
        } else {
            for (int k = 1; k < 5; ++k) pal[k + 1] = static_cast<uint8_t>(((5 - k) * a0 + k * a1) / 5);
            pal[6] = 0;
            pal[7] = 255;
        }
        uint64_t abits = 0;
        for (int k = 0; k < 6; ++k) abits |= static_cast<uint64_t>(b[2 + k]) << (8 * k);
        for (int i = 0; i < 16; ++i) alpha[i] = pal[(abits >> (3 * i)) & 7];
    }
    bool constant = true;
    for (int i = 1; i < 16; ++i) constant &= alpha[i] == alpha[0];
    if (constant) {
        e0[3] = e1[3] = alpha[0];
        Pack(kOneAlpha, e0, e1, w0, nullptr, out);
        ++stats->blocks[kOneAlpha];
        return;
    }
    FitAlpha(alpha, g_modes[kVaryingAlpha].colorQuant, &e0[3], &e1[3], w1);
    Pack(kVaryingAlpha, e0, e1, w0, w1, out);
    ++stats->blocks[kVaryingAlpha];
}

}  // namespace

void SetAstcReferencePacking(bool on) { g_referencePacking = on; }

bool AstcTranscodeReady() {
    if (g_ready < 0) {
        g_ready = 0;
        g_bsd = new block_size_descriptor();
        init_block_size_descriptor(4, 4, 1, false, 4, 1.0f, *g_bsd);
        g_ready = SetupMode(g_modes[kFour], kMode4Levels, FMT_RGB, QUANT_4, false) &&
                  SetupMode(g_modes[kThree], kMode3Levels, FMT_RGB, QUANT_3, false) &&
                  SetupMode(g_modes[kThreeAlpha], kMode3Levels | kDualPlane, FMT_RGBA, QUANT_3, true) &&
                  SetupMode(g_modes[kOneAlpha], kMode4Levels, FMT_RGBA, QUANT_4, false) &&
                  SetupMode(g_modes[kVaryingAlpha], kMode4Levels | kDualPlane, FMT_RGBA, QUANT_4, true);
    }
    return g_ready == 1;
}

namespace {

// Helper threads for the large levels (TranscodeS3tcToAstc4x4): the caller (the level loader's thread) does one share
// of the blocks itself and waits for the others. Made at the first large level; up to 3 (a phone has 8 cores, the
// game's own threads need some, and the web build's thread pool is 12).
constexpr size_t kSplitBlocks = 4096;  // a level of fewer blocks is done by the caller alone
class HelperPool {
public:
    static HelperPool& Get() {
        static HelperPool pool;
        return pool;
    }
    size_t Count() const { return m_threads.size(); }
    void Run(std::function<void()> job) {
        {
            std::lock_guard<std::mutex> lock(m_mutex);
            m_jobs.push_back(std::move(job));
        }
        m_wake.notify_one();
    }

private:
    HelperPool() {
        const unsigned cores = std::thread::hardware_concurrency();
        const unsigned count = cores >= 4 ? std::min(3u, cores - 2) : 0u;
        for (unsigned i = 0; i < count; ++i) {
            m_threads.emplace_back([this] {
                for (;;) {
                    std::function<void()> job;
                    {
                        std::unique_lock<std::mutex> lock(m_mutex);
                        m_wake.wait(lock, [this] { return !m_jobs.empty(); });
                        job = std::move(m_jobs.front());
                        m_jobs.erase(m_jobs.begin());
                    }
                    job();
                }
            });
            m_threads.back().detach();
        }
    }
    std::vector<std::thread> m_threads;
    std::mutex m_mutex;
    std::condition_variable m_wake;
    std::vector<std::function<void()>> m_jobs;
};

void TranscodeRange(TextureFormat format, const uint8_t* data, size_t blockBytes, size_t from, size_t to, uint8_t* out,
                    AstcStats* stats) {
    for (size_t i = from; i < to; ++i) TranscodeBlock(format, data + i * blockBytes, out + i * 16, stats);
}

}  // namespace

std::vector<uint8_t> TranscodeS3tcToAstc4x4(TextureFormat format, int width, int height, const uint8_t* data,
                                            AstcStats* stats) {
    const auto start = std::chrono::steady_clock::now();
    const int bw = (width + 3) / 4, bh = (height + 3) / 4;
    const size_t blockBytes = format == TextureFormat::kBC1 ? 8 : 16;
    const size_t n = static_cast<size_t>(bw) * bh;
    std::vector<uint8_t> out(n * 16);
    AstcStats local;
    AstcStats* s = stats != nullptr ? stats : &local;
    HelperPool* pool = n >= kSplitBlocks ? &HelperPool::Get() : nullptr;
    if (pool == nullptr || pool->Count() == 0) {
        TranscodeRange(format, data, blockBytes, 0, n, out.data(), s);
    } else {
        // Shares of the blocks: the helpers take all but the first, the caller the first; then it waits for them.
        const size_t shares = pool->Count() + 1;
        std::vector<AstcStats> partial(shares);
        std::mutex doneMutex;
        std::condition_variable doneWake;
        size_t done = 0;
        for (size_t k = 1; k < shares; ++k) {
            pool->Run([&, k] {
                TranscodeRange(format, data, blockBytes, n * k / shares, n * (k + 1) / shares, out.data(), &partial[k]);
                std::lock_guard<std::mutex> lock(doneMutex);
                ++done;
                doneWake.notify_one();
            });
        }
        TranscodeRange(format, data, blockBytes, 0, n / shares, out.data(), &partial[0]);
        {
            std::unique_lock<std::mutex> lock(doneMutex);
            doneWake.wait(lock, [&] { return done == shares - 1; });
        }
        for (const AstcStats& p : partial) {
            for (int k = 0; k < 5; ++k) s->blocks[k] += p.blocks[k];
        }
    }
    s->ms += std::chrono::duration<double, std::milli>(std::chrono::steady_clock::now() - start).count();
    return out;
}

#else  // no astc-encoder in this build: the RGBA8 fallback only

void SetAstcReferencePacking(bool) {}

bool AstcTranscodeReady() { return false; }

std::vector<uint8_t> TranscodeS3tcToAstc4x4(TextureFormat, int, int, const uint8_t*, AstcStats*) { return {}; }

#endif

}  // namespace dotd::gfx
