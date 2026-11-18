// rws.cpp - see rws.h.
#include "platform/audio/rws.h"

#include <algorithm>
#include <cstring>

#include "platform/hostfs.h"
#include "platform/log.h"

#if DOTD_HAVE_FFMPEG_BINK
extern "C" {
#include "libavcodec/avcodec.h"
#include "libavutil/channel_layout.h"
#include "libavutil/frame.h"
#include "libavutil/mem.h"
}
#endif

namespace dotd::audio {
namespace {

const uint8_t kPcmGuid[16] = {0xd0, 0x1b, 0xd2, 0x17, 0x35, 0x87, 0x4e, 0xed,
                              0xb9, 0xd9, 0xb8, 0xe8, 0x6e, 0xa9, 0xb9, 0x95};
const uint8_t kAtrac3Guid[16] = {0x46, 0x36, 0x0b, 0x16, 0x13, 0x22, 0x4f, 0xa2,
                                 0xad, 0xb8, 0xc6, 0x0e, 0x94, 0x6f, 0x3d, 0xe6};

uint32_t LE32(const uint8_t* p) {
    return static_cast<uint32_t>(p[0]) | (static_cast<uint32_t>(p[1]) << 8) | (static_cast<uint32_t>(p[2]) << 16) |
           (static_cast<uint32_t>(p[3]) << 24);
}
uint32_t BE32(const uint8_t* p) {
    return (static_cast<uint32_t>(p[0]) << 24) | (static_cast<uint32_t>(p[1]) << 16) | (static_cast<uint32_t>(p[2]) << 8) |
           static_cast<uint32_t>(p[3]);
}
uint32_t BE16(const uint8_t* p) { return (static_cast<uint32_t>(p[0]) << 8) | p[1]; }
uint64_t LE64(const uint8_t* p) { return static_cast<uint64_t>(LE32(p)) | (static_cast<uint64_t>(LE32(p + 4)) << 32); }

// A NUL-terminated name padded to 16 bytes; false when it runs past the end.
bool ReadName(const std::vector<uint8_t>& b, uint32_t* at, std::string* out) {
    uint32_t end = *at;
    while (end < b.size() && b[end] != 0) ++end;
    if (end >= b.size()) return false;
    out->assign(reinterpret_cast<const char*>(&b[*at]), end - *at);
    *at += ((end + 1 - *at) + 15u) & ~15u;
    return true;
}

}  // namespace

RwsFile::~RwsFile() { Close(); }

void RwsFile::Close() {
    if (file_ != nullptr) std::fclose(file_);
    file_ = nullptr;
}

bool RwsFile::Open(const std::string& hostPath) {
    Close();
    file_ = dotd::platform::hostfs::OpenStdio(hostPath);
    if (file_ == nullptr) return false;
    uint8_t top[0x18];
    if (std::fread(top, 1, sizeof(top), file_) != sizeof(top) || LE32(top) != 0x80d || LE32(top + 0xc) != 0x80e) {
        Close();
        return false;
    }
    const uint32_t headerSize = LE32(top + 0x10);
    std::vector<uint8_t> b(headerSize);
    if (headerSize < 0x60 || std::fread(b.data(), 1, headerSize, file_) != headerSize) {
        Close();
        return false;
    }
    uint8_t dataChunk[12];
    if (std::fread(dataChunk, 1, 12, file_) != 12 || LE32(dataChunk) != 0x80f) {
        Close();
        return false;
    }
    dataOffset_ = 0x24ull + headerSize;
    const uint32_t nseg = BE32(&b[0x20]), nlay = BE32(&b[0x28]);
    if (nseg == 0 || nlay == 0 || nseg > 4096 || nlay > 64) {
        Close();
        return false;
    }
    uint32_t at = 0x50;
    bool ok = ReadName(b, &at, &name);
    segments.assign(nseg, RwsSegment());
    layers.assign(nlay, RwsLayer());
    for (uint32_t s = 0; ok && s < nseg; ++s, at += 0x20) {
        ok = at + 0x20 <= headerSize;
        if (ok) {
            segments[s].bytes = BE32(&b[at + 0x18]);
            segments[s].offset = BE32(&b[at + 0x1c]);
        }
    }
    for (uint32_t s = 0; ok && s < nseg; ++s) {
        for (uint32_t l = 0; ok && l < nlay; ++l, at += 4) {
            ok = at + 4 <= headerSize;
            if (ok) segments[s].usable.push_back(BE32(&b[at]));
        }
    }
    at += 0x10 * nseg;  // segment GUIDs
    for (uint32_t s = 0; ok && s < nseg; ++s) ok = ReadName(b, &at, &segments[s].name);
    for (uint32_t l = 0; ok && l < nlay; ++l, at += 0x28) {
        ok = at + 0x28 <= headerSize;
        if (ok) {
            RwsLayer& y = layers[l];
            y.blockSize = BE32(&b[at + 0x10]);
            y.interleave = BE16(&b[at + 0x18]);
            y.frameSize = BE16(&b[at + 0x1a]);
            y.blockUsable = BE32(&b[at + 0x20]);
            y.start = BE32(&b[at + 0x24]);
        }
    }
    for (uint32_t l = 0; ok && l < nlay; ++l, at += 0x30) {
        ok = at + 0x30 <= headerSize;
        if (ok) {
            RwsLayer& y = layers[l];
            y.sampleRate = BE32(&b[at]);
            y.bits = b[at + 0xc];
            y.channels = b[at + 0xd];
            std::memcpy(y.codec, &b[at + 0x1c], 16);
        }
    }
    if (!ok) {
        DOTD_LOG("rws: %s: malformed header", hostPath.c_str());
        Close();
        return false;
    }
    Select(0, 0);
    return true;
}

bool RwsFile::IsPcm16(uint32_t layer) const {
    return layer < layers.size() && std::memcmp(layers[layer].codec, kPcmGuid, 16) == 0 && layers[layer].bits == 16 &&
           layers[layer].channels != 0;
}

bool RwsFile::Select(uint32_t segment, uint32_t layer) {
    if (segment >= segments.size() || layer >= layers.size()) return false;
    segment_ = segment;
    layer_ = layer;
    consumed_ = 0;
    return IsPcm16(layer);
}

uint64_t RwsFile::TotalFrames() const {
    if (!IsPcm16(layer_) || segment_ >= segments.size()) return 0;
    return segments[segment_].usable[layer_] / (2ull * layers[layer_].channels);
}

uint32_t RwsFile::Read(int16_t* out, uint32_t frames) {
    if (file_ == nullptr || !IsPcm16(layer_)) return 0;
    const RwsLayer& y = layers[layer_];
    const RwsSegment& s = segments[segment_];
    const uint32_t frameBytes = 2u * y.channels;
    uint64_t stride = 0;  // the blocks of all layers, one after the other
    for (const RwsLayer& l : layers) stride += l.blockSize;
    uint32_t done = 0;
    while (done < frames && consumed_ + frameBytes <= s.usable[layer_] && y.blockUsable >= frameBytes) {
        const uint64_t blockIndex = consumed_ / y.blockUsable;
        const uint32_t inBlock = static_cast<uint32_t>(consumed_ % y.blockUsable);
        const uint64_t left = std::min<uint64_t>(y.blockUsable - inBlock, s.usable[layer_] - consumed_);
        const uint32_t n = static_cast<uint32_t>(std::min<uint64_t>(left / frameBytes, frames - done));
        if (n == 0) break;
        const uint64_t pos = dataOffset_ + s.offset + y.start + blockIndex * stride + inBlock;
        block_.resize(static_cast<size_t>(n) * frameBytes);
        if (std::fseek(file_, static_cast<long>(pos), SEEK_SET) != 0 ||
            std::fread(block_.data(), 1, block_.size(), file_) != block_.size()) {
            break;
        }
        for (uint32_t i = 0; i < n * y.channels; ++i) {
            out[static_cast<size_t>(done) * y.channels + i] =
                static_cast<int16_t>(static_cast<uint16_t>((block_[2 * i] << 8) | block_[2 * i + 1]));
        }
        done += n;
        consumed_ += static_cast<uint64_t>(n) * frameBytes;
    }
    return done;
}

bool RwsFile::IsAtrac3(uint32_t layer) const {
    return layer < layers.size() && std::memcmp(layers[layer].codec, kAtrac3Guid, 16) == 0 && layers[layer].channels != 0 &&
           layers[layer].frameSize != 0;
}

bool RwsFile::DecodeAtrac3(uint32_t segment, uint32_t layer, std::vector<int16_t>* out) {
    out->clear();
    if (file_ == nullptr || !IsAtrac3(layer) || segment >= segments.size()) return false;
#if DOTD_HAVE_FFMPEG_BINK
    const RwsLayer& y = layers[layer];
    const RwsSegment& s = segments[segment];
    uint64_t stride = 0;
    for (const RwsLayer& l : layers) stride += l.blockSize;
    // The segment's usable bytes, block by block.
    std::vector<uint8_t> bytes(s.usable[layer]);
    for (uint64_t done = 0, blockIndex = 0; done < bytes.size() && y.blockUsable != 0; ++blockIndex) {
        const size_t n = static_cast<size_t>(std::min<uint64_t>(y.blockUsable, bytes.size() - done));
        const uint64_t pos = dataOffset_ + s.offset + y.start + blockIndex * stride;
        if (std::fseek(file_, static_cast<long>(pos), SEEK_SET) != 0 || std::fread(&bytes[done], 1, n, file_) != n) {
            return false;
        }
        done += n;
    }
    const AVCodec* codec = avcodec_find_decoder(AV_CODEC_ID_ATRAC3);
    AVCodecContext* ctx = codec != nullptr ? avcodec_alloc_context3(codec) : nullptr;
    if (ctx == nullptr) return false;
    av_channel_layout_default(&ctx->ch_layout, static_cast<int>(y.channels));
    ctx->sample_rate = static_cast<int>(y.sampleRate);
    ctx->block_align = static_cast<int>(y.frameSize);
    // The WAV-style extradata (14 bytes): 1, samples per channel, single-channel coding, frame factor 1.
    ctx->extradata = static_cast<uint8_t*>(av_mallocz(14 + AV_INPUT_BUFFER_PADDING_SIZE));
    const uint8_t extradata[14] = {1, 0, 0x00, 0x08, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0};
    std::memcpy(ctx->extradata, extradata, sizeof(extradata));
    ctx->extradata_size = 14;
    bool ok = avcodec_open2(ctx, codec, nullptr) == 0;
    AVPacket* pkt = av_packet_alloc();
    AVFrame* frame = av_frame_alloc();
    std::vector<uint8_t> padded(y.frameSize + AV_INPUT_BUFFER_PADDING_SIZE);
    for (size_t at = 0; ok && at + y.frameSize <= bytes.size(); at += y.frameSize) {
        std::memcpy(padded.data(), &bytes[at], y.frameSize);
        pkt->data = padded.data();
        pkt->size = static_cast<int>(y.frameSize);
        if (avcodec_send_packet(ctx, pkt) < 0) {
            ok = false;
            break;
        }
        while (avcodec_receive_frame(ctx, frame) >= 0) {
            // AV_SAMPLE_FMT_FLTP: one plane per channel.
            for (int i = 0; i < frame->nb_samples; ++i) {
                for (uint32_t c = 0; c < y.channels; ++c) {
                    const float v = reinterpret_cast<const float*>(frame->extended_data[c])[i] * 32768.0f;
                    out->push_back(static_cast<int16_t>(std::max(-32768.0f, std::min(32767.0f, v))));
                }
            }
        }
    }
    av_frame_free(&frame);
    av_packet_free(&pkt);
    avcodec_free_context(&ctx);
    if (!ok) DOTD_LOG("rws: ATRAC3 decode of %s segment %u failed", name.c_str(), segment);
    return ok;
#else
    return false;
#endif
}

// ---- OgvFile ----------------------------------------------------------------------------------------------------
OgvFile::~OgvFile() { Close(); }

void OgvFile::CloseDecoder() {
#if DOTD_HAVE_FFMPEG_BINK
    AVCodecContext* ctx = static_cast<AVCodecContext*>(decoder_);
    AVFrame* frame = static_cast<AVFrame*>(frame_);
    AVPacket* packet = static_cast<AVPacket*>(packet_);
    if (ctx != nullptr) avcodec_free_context(&ctx);
    if (frame != nullptr) av_frame_free(&frame);
    if (packet != nullptr) av_packet_free(&packet);
#endif
    decoder_ = nullptr;
    frame_ = nullptr;
    packet_ = nullptr;
    item_ = 0xffffffffu;
}

void OgvFile::Close() {
    CloseDecoder();
    if (file_ != nullptr) std::fclose(file_);
    file_ = nullptr;
    items_.clear();
}

bool OgvFile::Open(const std::string& hostPath) {
    Close();
    file_ = dotd::platform::hostfs::OpenStdio(hostPath);
    if (file_ == nullptr) return false;
    uint8_t head[12];
    if (std::fread(head, 1, sizeof(head), file_) != sizeof(head) || std::memcmp(head, "DVOR", 4) != 0 || LE32(head + 4) != 1 ||
        LE32(head + 8) == 0 || LE32(head + 8) > 4096) {
        Close();
        return false;
    }
    std::vector<uint8_t> table(32 * static_cast<size_t>(LE32(head + 8)));
    if (std::fread(table.data(), 1, table.size(), file_) != table.size()) {
        Close();
        return false;
    }
    items_.resize(table.size() / 32);
    for (size_t i = 0; i < items_.size(); ++i) {
        const uint8_t* e = &table[32 * i];
        items_[i].rate = LE32(e);
        items_[i].channels = LE32(e + 4);
        items_[i].frames = LE64(e + 8);
        items_[i].setup = LE32(e + 16);
        items_[i].packets = LE32(e + 20);
        items_[i].offset = LE64(e + 24);
    }
    return true;
}

bool OgvFile::Select(uint32_t item) {
#if DOTD_HAVE_FFMPEG_BINK
    if (file_ == nullptr || item >= items_.size()) return false;
    const Item& it = items_[item];
    if (it.frames == 0 || it.packets == 0 || it.channels == 0 || it.channels > 8 || it.setup == 0 || it.setup > (1u << 20)) {
        return false;
    }
    if (item != item_ || decoder_ == nullptr) {
        CloseDecoder();
        std::vector<uint8_t> setup(it.setup), raw(2 * static_cast<size_t>(it.packets));
        if (std::fseek(file_, static_cast<long>(it.offset), SEEK_SET) != 0 ||
            std::fread(setup.data(), 1, setup.size(), file_) != setup.size() ||
            std::fread(raw.data(), 1, raw.size(), file_) != raw.size()) {
            return false;
        }
        sizes_.resize(it.packets);
        for (uint32_t i = 0; i < it.packets; ++i) sizes_[i] = static_cast<uint16_t>(raw[2 * i] | (raw[2 * i + 1] << 8));
        const AVCodec* codec = avcodec_find_decoder(AV_CODEC_ID_VORBIS);
        AVCodecContext* ctx = codec != nullptr ? avcodec_alloc_context3(codec) : nullptr;
        if (ctx == nullptr) return false;
        av_channel_layout_default(&ctx->ch_layout, static_cast<int>(it.channels));
        ctx->sample_rate = static_cast<int>(it.rate);
        ctx->extradata = static_cast<uint8_t*>(av_mallocz(setup.size() + AV_INPUT_BUFFER_PADDING_SIZE));
        std::memcpy(ctx->extradata, setup.data(), setup.size());
        ctx->extradata_size = static_cast<int>(setup.size());
        if (avcodec_open2(ctx, codec, nullptr) != 0) {
            avcodec_free_context(&ctx);
            return false;
        }
        decoder_ = ctx;
        frame_ = av_frame_alloc();
        packet_ = av_packet_alloc();
        item_ = item;
    } else {
        avcodec_flush_buffers(static_cast<AVCodecContext*>(decoder_));
    }
    if (std::fseek(file_, static_cast<long>(it.offset + it.setup + 2ull * it.packets), SEEK_SET) != 0) return false;
    next_ = 0;
    emitted_ = 0;
    pending_.clear();
    pendingAt_ = 0;
    sampleRate = it.rate;
    channels = it.channels;
    return true;
#else
    (void)item;
    return false;
#endif
}

uint32_t OgvFile::Read(float* out, uint32_t frames) {
#if DOTD_HAVE_FFMPEG_BINK
    if (file_ == nullptr || decoder_ == nullptr || item_ >= items_.size()) return 0;
    const Item& it = items_[item_];
    AVCodecContext* ctx = static_cast<AVCodecContext*>(decoder_);
    AVFrame* frame = static_cast<AVFrame*>(frame_);
    AVPacket* packet = static_cast<AVPacket*>(packet_);
    uint32_t done = 0;
    while (done < frames && emitted_ < it.frames) {
        if (pendingAt_ < pending_.size()) {
            const uint64_t have = (pending_.size() - pendingAt_) / it.channels;
            const uint32_t n = static_cast<uint32_t>(std::min<uint64_t>(std::min<uint64_t>(have, frames - done), it.frames - emitted_));
            std::memcpy(out + static_cast<size_t>(done) * it.channels, &pending_[pendingAt_],
                        static_cast<size_t>(n) * it.channels * sizeof(float));
            pendingAt_ += static_cast<size_t>(n) * it.channels;
            done += n;
            emitted_ += n;
            continue;
        }
        if (next_ >= it.packets) break;
        const uint32_t size = sizes_[next_++];
        bytes_.assign(size + AV_INPUT_BUFFER_PADDING_SIZE, 0);
        if (std::fread(bytes_.data(), 1, size, file_) != size) break;
        packet->data = bytes_.data();
        packet->size = static_cast<int>(size);
        pending_.clear();
        pendingAt_ = 0;
        if (avcodec_send_packet(ctx, packet) < 0) continue;  // (a packet the decoder refuses: on with the next)
        while (avcodec_receive_frame(ctx, frame) >= 0) {
            const bool planar = frame->format == AV_SAMPLE_FMT_FLTP;
            for (int i = 0; i < frame->nb_samples; ++i) {
                for (uint32_t c = 0; c < it.channels; ++c) {
                    const float* src = reinterpret_cast<const float*>(frame->extended_data[planar ? c : 0]);
                    pending_.push_back(planar ? src[i] : src[static_cast<size_t>(i) * it.channels + c]);
                }
            }
            av_frame_unref(frame);
        }
    }
    return done;
#else
    (void)out;
    (void)frames;
    return 0;
#endif
}

}  // namespace dotd::audio
