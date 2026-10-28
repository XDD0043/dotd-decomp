// bink.cpp - see bink.h. The Bink 1 container is read here (header, audio track table, frame index);
// each frame's video packet goes to FFmpeg's bink decoder, the audio packets of the opened tracks to
// FFmpeg's binkaudio decoder and from there to a platform mixer stream (platform/audio/mixer.h).
#include "platform/video/bink.h"

#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <vector>

#include "platform/audio/mixer.h"
#include "platform/cell/fs.h"
#include "platform/cell/sys_time.h"
#include "platform/log.h"

#if DOTD_HAVE_FFMPEG_BINK
extern "C" {
#include "libavcodec/avcodec.h"
#include "libavutil/channel_layout.h"
#include "libavutil/frame.h"
#include "libavutil/mem.h"
}
#endif

#if DOTD_HAVE_FFMPEG_BINK
// One opened audio track: its decoder and the mixer stream it feeds.
struct BinkAudioTrack {
    uint32_t index = 0;        // position in the file's track table
    uint32_t id = 0;           // the track ID (BinkSetSoundTrack / BinkSetVolume)
    uint32_t sampleRate = 0;
    uint32_t channels = 0;
    AVCodecContext* codec = nullptr;
    int32_t stream = -1;
    std::vector<float> interleaved;
};
#endif

struct BinkImpl {
    std::FILE* file = nullptr;
    uint32_t signature = 0;            // 'BIKi' etc. (the codec tag)
    uint32_t fileSize = 0;             // header +4 plus 8
    uint32_t videoFlags = 0;           // header +0x24 (the decoder's extradata)
    std::vector<uint32_t> index;       // Frames + 1 offsets; bit 0 = keyframe
    std::vector<uint8_t> packet;
    uint32_t decodedFrame = 0;         // the frame the decoder holds (0 = none)
    // Timing (BinkWait): the PS3 Bink keeps these at +0x2b4 (frames shown), +0x2c0 (timer start, ms),
    // +0x2c4 (frames shown at the timer start, minus 1).
    uint32_t framesShown = 0;
    uint32_t timerStartMs = 0;
    uint32_t timerBase = 0;
    BINKFRAMEBUFFERS* buffers = nullptr;
#if DOTD_HAVE_FFMPEG_BINK
    AVCodecContext* codec = nullptr;
    AVFrame* frame = nullptr;
    AVPacket* avPacket = nullptr;
    std::vector<BinkAudioTrack> audio;  // the opened tracks
    uint32_t audioFrame = 0;            // the last frame whose audio went to the mixer
#endif
};

namespace {

// BinkSetSoundTrack: the tracks the next BinkOpen with BINKSNDTRACK opens (Bink keeps them globally).
uint32_t g_soundTrackCount = 0;
uint32_t g_soundTrackIds[16] = {};
constexpr uint32_t kBinkSndTrack = 0x00004000u;  // BINKSNDTRACK

uint32_t ReadLE32(const uint8_t* p) {
    return static_cast<uint32_t>(p[0]) | (static_cast<uint32_t>(p[1]) << 8) | (static_cast<uint32_t>(p[2]) << 16) |
           (static_cast<uint32_t>(p[3]) << 24);
}

// Bink's timer: milliseconds of the platform system clock (the PS3 library reads the time base the same way).
uint32_t TimeMs() { return static_cast<uint32_t>(sys_time_get_system_time() / 1000); }

// Bit 0 of a frame's index entry marks a keyframe; the first frame always is one.
bool IsKey(const BinkImpl* impl, uint32_t frame) {  // frame 1-based
    return frame == 1 || (impl->index[frame - 1] & 1u) != 0;
}

#if DOTD_HAVE_FFMPEG_BINK
// One audio packet of a track (its first word is the decoded size in bytes, which the decoder skips).
void DecodeAudio(BinkAudioTrack* track, const uint8_t* data, uint32_t size, AVPacket* pkt) {
    if (track->codec == nullptr) return;
    if (av_new_packet(pkt, static_cast<int>(size)) < 0) return;
    std::memcpy(pkt->data, data, size);
    int ret = avcodec_send_packet(track->codec, pkt);
    av_packet_unref(pkt);
    if (ret < 0) return;
    AVFrame* f = av_frame_alloc();
    while (avcodec_receive_frame(track->codec, f) >= 0) {
        const uint32_t n = static_cast<uint32_t>(f->nb_samples);
        const uint32_t ch = track->channels;
        track->interleaved.resize(static_cast<size_t>(n) * ch);
        const bool planar = f->format == AV_SAMPLE_FMT_FLTP;
        for (uint32_t i = 0; i < n; ++i) {
            for (uint32_t c = 0; c < ch; ++c) {
                const float* src = reinterpret_cast<const float*>(f->extended_data[planar ? c : 0]);
                track->interleaved[static_cast<size_t>(i) * ch + c] = planar ? src[i] : src[static_cast<size_t>(i) * ch + c];
            }
        }
        dotd::audio::StreamPush(track->stream, track->interleaved.data(), n);
        av_frame_unref(f);
    }
    av_frame_free(&f);
}

// Opens the decoders of the tracks BinkOpen plays: with BINKSNDTRACK the IDs BinkSetSoundTrack listed
// (Bink's rule), otherwise the first track. table: the header's track table (max sizes, rate/flags, IDs).
void OpenAudioTracks(BINK* bink, const std::vector<uint8_t>& table, uint32_t flags, const char* name) {
    BinkImpl* impl = bink->impl;
    const uint32_t n = bink->NumTracks;
    std::vector<uint32_t> wanted;
    if ((flags & kBinkSndTrack) != 0) {
        wanted.assign(g_soundTrackIds, g_soundTrackIds + g_soundTrackCount);
    } else if (n > 0) {
        wanted.push_back(ReadLE32(table.data() + 8 * n));  // the first track's ID
    }
    for (uint32_t id : wanted) {
        for (uint32_t t = 0; t < n; ++t) {
            if (ReadLE32(table.data() + 8 * n + 4 * t) != id) continue;
            const uint32_t rateFlags = ReadLE32(table.data() + 4 * n + 4 * t);
            BinkAudioTrack track;
            track.index = t;
            track.id = id;
            track.sampleRate = rateFlags & 0xffffu;
            track.channels = (rateFlags & 0x20000000u) != 0 ? 2u : 1u;  // BINK_AUD_STEREO (0x2000 in the high half)
            const bool dct = (rateFlags & 0x10000000u) != 0;             // BINK_AUD_USEDCT (0x1000)
            const AVCodec* codec = avcodec_find_decoder(dct ? AV_CODEC_ID_BINKAUDIO_DCT : AV_CODEC_ID_BINKAUDIO_RDFT);
            track.codec = codec != nullptr ? avcodec_alloc_context3(codec) : nullptr;
            if (track.codec != nullptr) {
                track.codec->sample_rate = static_cast<int>(track.sampleRate);
                av_channel_layout_default(&track.codec->ch_layout, static_cast<int>(track.channels));
                track.codec->extradata = static_cast<uint8_t*>(av_mallocz(4 + AV_INPUT_BUFFER_PADDING_SIZE));
                std::memcpy(track.codec->extradata, &impl->signature, 4);  // the decoder reads the revision byte
                track.codec->extradata_size = 4;
                if (avcodec_open2(track.codec, codec, nullptr) != 0) avcodec_free_context(&track.codec);
            }
            if (track.codec == nullptr) {
                DOTD_LOG("bink: %s: audio track %u: no decoder", name, id);
                break;
            }
            char streamName[96];
            std::snprintf(streamName, sizeof(streamName), "%s#%u", name, id);
            track.stream = dotd::audio::StreamCreate(track.sampleRate, track.channels, streamName);
            impl->audio.push_back(std::move(track));
            break;
        }
    }
}

void CloseAudioTracks(BinkImpl* impl) {
    for (BinkAudioTrack& track : impl->audio) {
        dotd::audio::StreamDestroy(track.stream);
        avcodec_free_context(&track.codec);
    }
    impl->audio.clear();
}

// Reads frame `frame` (1-based) and decodes its video part. Returns false on a read or decode error.
bool DecodeOne(BINK* bink, uint32_t frame) {
    BinkImpl* impl = bink->impl;
    const uint32_t begin = impl->index[frame - 1] & ~1u;
    uint32_t end = impl->index[frame] & ~1u;
    if (frame == bink->Frames && (end <= begin || end > impl->fileSize)) end = impl->fileSize;
    if (end <= begin) return false;
    impl->packet.resize(end - begin);
    if (std::fseek(impl->file, static_cast<long>(begin), SEEK_SET) != 0 ||
        std::fread(impl->packet.data(), 1, end - begin, impl->file) != end - begin) {
        return false;
    }
    // The audio packets come first: per track a u32 size, then the data. Only the frame after the last
    // one whose audio was queued feeds the mixer (re-decodes after a seek stay silent).
    const bool feedAudio = frame == impl->audioFrame + 1;
    uint32_t pos = 0;
    for (uint32_t t = 0; t < bink->NumTracks; ++t) {
        if (pos + 4 > impl->packet.size()) return false;
        const uint32_t size = ReadLE32(impl->packet.data() + pos);
        if (pos + 4 + size > impl->packet.size()) return false;
        if (feedAudio && size >= 4) {
            for (BinkAudioTrack& track : impl->audio) {
                if (track.index == t) DecodeAudio(&track, impl->packet.data() + pos + 4, size, impl->avPacket);
            }
        }
        pos += 4 + size;
    }
    if (feedAudio) impl->audioFrame = frame;
    if (pos > impl->packet.size()) return false;
    const uint32_t size = static_cast<uint32_t>(impl->packet.size()) - pos;
    if (av_new_packet(impl->avPacket, static_cast<int>(size)) < 0) return false;
    std::memcpy(impl->avPacket->data, impl->packet.data() + pos, size);
    if (IsKey(impl, frame)) impl->avPacket->flags |= AV_PKT_FLAG_KEY;
    int ret = avcodec_send_packet(impl->codec, impl->avPacket);
    av_packet_unref(impl->avPacket);
    if (ret < 0) return false;
    ret = avcodec_receive_frame(impl->codec, impl->frame);
    if (ret < 0) return false;
    impl->decodedFrame = frame;
    return true;
}

// Brings the decoder to `frame`: from the previous keyframe when it is not the next one in order.
bool DecodeTo(BINK* bink, uint32_t frame) {
    BinkImpl* impl = bink->impl;
    if (impl->decodedFrame == frame) return true;
    uint32_t first = frame;
    if (impl->decodedFrame + 1 != frame || impl->decodedFrame == 0) {
        while (first > 1 && !IsKey(impl, first)) --first;
        if (impl->decodedFrame != 0 && impl->decodedFrame < frame && impl->decodedFrame >= first) {
            first = impl->decodedFrame + 1;
        } else {
            avcodec_flush_buffers(impl->codec);
        }
    }
    for (uint32_t f = first; f <= frame; ++f) {
        if (!DecodeOne(bink, f)) return false;
    }
    return true;
}

void CopyPlane(const uint8_t* src, int srcPitch, BINKPLANE* dst, int width, int height) {
    if (!dst->Allocate || dst->Buffer == nullptr || src == nullptr) return;
    for (int row = 0; row < height; ++row) {
        std::memcpy(static_cast<uint8_t*>(dst->Buffer) + static_cast<size_t>(row) * dst->BufferPitch,
                    src + static_cast<size_t>(row) * srcPitch, static_cast<size_t>(width));
    }
}
#endif

}  // namespace

BINK* BinkOpen(const char* path, uint32_t flags) {
#if DOTD_HAVE_FFMPEG_BINK
    std::string ps3Path = path;
    if (ps3Path.empty() || ps3Path[0] != '/') ps3Path = "/dev_bdvd/PS3_GAME/USRDIR/" + ps3Path;
    std::string host;
    bool writable = false;
    if (!dotd::platform::MapPs3Path(ps3Path.c_str(), &host, &writable)) {
        DOTD_LOG("bink: no host path for %s", ps3Path.c_str());
        return nullptr;
    }
    std::FILE* file = std::fopen(host.c_str(), "rb");
    if (file == nullptr) {
        DOTD_LOG("bink: cannot open %s", host.c_str());
        return nullptr;
    }
    uint8_t header[44];
    if (std::fread(header, 1, sizeof(header), file) != sizeof(header) || std::memcmp(header, "BIK", 3) != 0 ||
        header[3] < 'b' || header[3] > 'i') {
        DOTD_LOG("bink: %s is not a Bink 1 file", host.c_str());
        std::fclose(file);
        return nullptr;
    }
    BINK* bink = new BINK();
    BinkImpl* impl = new BinkImpl();
    bink->impl = impl;
    impl->file = file;
    impl->signature = ReadLE32(header);
    impl->fileSize = ReadLE32(header + 4) + 8;
    bink->Frames = ReadLE32(header + 8);
    bink->Width = ReadLE32(header + 20);
    bink->Height = ReadLE32(header + 24);
    bink->FrameRate = ReadLE32(header + 28);
    bink->FrameRateDiv = ReadLE32(header + 32);
    impl->videoFlags = ReadLE32(header + 36);
    bink->NumTracks = ReadLE32(header + 40);
    bink->OpenFlags = flags;
    bool ok = bink->Frames > 0 && bink->Frames < 1000000 && bink->NumTracks < 256 && bink->FrameRate != 0 &&
              bink->FrameRateDiv != 0;
    // Audio track table: max decoded sizes, (sample rate, flags), track ids: 12 bytes per track.
    std::vector<uint8_t> trackTable(12 * static_cast<size_t>(ok ? bink->NumTracks : 0));
    if (ok && !trackTable.empty()) ok = std::fread(trackTable.data(), 1, trackTable.size(), file) == trackTable.size();
    if (ok) {
        impl->index.resize(bink->Frames + 1);
        std::vector<uint8_t> raw(4 * static_cast<size_t>(bink->Frames + 1));
        ok = std::fread(raw.data(), 1, raw.size(), file) == raw.size();
        for (uint32_t i = 0; ok && i <= bink->Frames; ++i) impl->index[i] = ReadLE32(raw.data() + 4 * i);
    }
    if (ok) {
        const AVCodec* codec = avcodec_find_decoder(AV_CODEC_ID_BINKVIDEO);
        impl->codec = codec != nullptr ? avcodec_alloc_context3(codec) : nullptr;
        ok = impl->codec != nullptr;
        if (ok) {
            impl->codec->width = static_cast<int>(bink->Width);
            impl->codec->height = static_cast<int>(bink->Height);
            impl->codec->codec_tag = impl->signature;
            impl->codec->extradata = static_cast<uint8_t*>(av_mallocz(4 + AV_INPUT_BUFFER_PADDING_SIZE));
            std::memcpy(impl->codec->extradata, header + 36, 4);
            impl->codec->extradata_size = 4;
            ok = avcodec_open2(impl->codec, codec, nullptr) == 0;
        }
        impl->frame = av_frame_alloc();
        impl->avPacket = av_packet_alloc();
    }
    if (ok) {
        const char* base = std::strrchr(path, '/');
        OpenAudioTracks(bink, trackTable, flags, base != nullptr ? base + 1 : path);
    }
    if (!ok) {
        DOTD_LOG("bink: %s: bad header or decoder", host.c_str());
        BinkClose(bink);
        return nullptr;
    }
    bink->FrameNum = 1;
    bink->LastFrameNum = 0;
    return bink;
#else
    (void)flags;
    DOTD_LOG("bink: no decoder in this build (FFmpeg clone missing), %s not played", path);
    return nullptr;
#endif
}

void BinkClose(BINK* bink) {
    if (bink == nullptr) return;
    BinkImpl* impl = bink->impl;
    if (impl != nullptr) {
#if DOTD_HAVE_FFMPEG_BINK
        CloseAudioTracks(impl);
        av_packet_free(&impl->avPacket);
        av_frame_free(&impl->frame);
        avcodec_free_context(&impl->codec);
#endif
        if (impl->file != nullptr) std::fclose(impl->file);
        delete impl;
    }
    delete bink;
}

int32_t BinkDoFrame(BINK* bink) {
#if DOTD_HAVE_FFMPEG_BINK
    if (bink == nullptr) return 0;
    BinkImpl* impl = bink->impl;
    if (!DecodeTo(bink, bink->FrameNum)) {
        bink->ReadError = 1;
        return 0;
    }
    BINKFRAMEBUFFERS* fb = impl->buffers;
    if (fb != nullptr && fb->TotalFrames > 0) {
        // Bink decodes into the next set (the game waited for its fence in PS3Video_SelectNextFrame).
        fb->FrameNum = (fb->FrameNum + 1) % static_cast<uint32_t>(fb->TotalFrames);
        BINKFRAMEPLANESET& set = fb->Frames[fb->FrameNum];
        const AVFrame* f = impl->frame;
        const int w = static_cast<int>(bink->Width), h = static_cast<int>(bink->Height);
        const int cw = (w + 1) / 2, ch = (h + 1) / 2;
        CopyPlane(f->data[0], f->linesize[0], &set.YPlane, w, h);
        CopyPlane(f->data[2], f->linesize[2], &set.cRPlane, cw, ch);  // FFmpeg: [1] = Cb (U), [2] = Cr (V)
        CopyPlane(f->data[1], f->linesize[1], &set.cBPlane, cw, ch);
        if (f->data[3] != nullptr) CopyPlane(f->data[3], f->linesize[3], &set.APlane, w, h);
        fb->Textures[fb->FrameNum].dirty = 1;
    }
    return 1;
#else
    (void)bink;
    return 0;
#endif
}

void BinkNextFrame(BINK* bink) {
    if (bink == nullptr) return;
    bink->LastFrameNum = bink->FrameNum;
    bink->FrameNum = bink->FrameNum >= bink->Frames ? 1 : bink->FrameNum + 1;
    ++bink->impl->framesShown;
}

// 0x009f0010 in the PS3 library (Ghidra BinkShouldSkip_maybe): 0 once the next frame's time has come.
int32_t BinkWait(BINK* bink) {
    if (bink == nullptr) return 0;
    BinkImpl* impl = bink->impl;
    if (impl->framesShown == 0 && bink->Paused == 0) return 0;
    if (bink->ReadError != 0) return 0;
    uint32_t start = impl->timerStartMs;
    if (start == 0) {
        start = TimeMs();
        if (start == 0) start = 1;
        impl->timerStartMs = start;
        impl->timerBase = impl->framesShown - 1;
    }
    const uint32_t now = TimeMs();
    if (bink->Paused == 0) {
        if (bink->FrameRate == 0) return 0;
        // frames since the timer start x the frame duration in ms (integer, as the library computes it)
        const uint64_t frames = static_cast<uint32_t>(impl->framesShown - impl->timerBase);
        const uint32_t due = static_cast<uint32_t>(frames * bink->FrameRateDiv * 1000u / bink->FrameRate);
        if (static_cast<int32_t>(now - start - due) >= 0) return 0;
    }
    return 1;
}

// 0x009f3e70 in the PS3 library (Ghidra BinkWait): skipping only happens to stay in sync with an audio
// track. Audio is not played yet, so playback never skips.
int32_t BinkShouldSkip(BINK* bink) {
    (void)bink;
    return 0;
}

void BinkGoto(BINK* bink, uint32_t frame, int32_t flags) {
    (void)flags;
    if (bink == nullptr) return;
    if (frame < 1) frame = 1;
    if (frame > bink->Frames) frame = bink->Frames;
    bink->LastFrameNum = bink->FrameNum;
    bink->FrameNum = frame;
    bink->impl->framesShown = 0;  // the next BinkWait shows the frame at once and restarts the timer
    bink->impl->timerStartMs = 0;
#if DOTD_HAVE_FFMPEG_BINK
    // the audio restarts with the target frame
    for (BinkAudioTrack& track : bink->impl->audio) {
        dotd::audio::StreamClear(track.stream);
        if (track.codec != nullptr) avcodec_flush_buffers(track.codec);
    }
    bink->impl->audioFrame = frame - 1;
#endif
}

uint32_t BinkGetKeyFrame(BINK* bink, uint32_t frame, int32_t flags) {
    if (bink == nullptr || bink->Frames == 0) return 0;
    BinkImpl* impl = bink->impl;
    if (frame < 1) frame = 1;
    if (frame > bink->Frames) frame = bink->Frames;
    const bool notEqual = (flags & BINKGETKEYNOTEQUAL) != 0;
    uint32_t prev = 0, next = 0;
    for (uint32_t f = notEqual ? frame - 1 : frame; f >= 1; --f) {
        if (IsKey(impl, f)) {
            prev = f;
            break;
        }
    }
    for (uint32_t f = notEqual ? frame + 1 : frame; f <= bink->Frames; ++f) {
        if (IsKey(impl, f)) {
            next = f;
            break;
        }
    }
    switch (flags & 0x7f) {
    case BINKGETKEYPREVIOUS: return prev;
    case BINKGETKEYNEXT: return next;
    default:
        if (prev == 0) return next;
        if (next == 0) return prev;
        return (frame - prev) <= (next - frame) ? prev : next;
    }
}

int32_t BinkPause(BINK* bink, int32_t pause) {
    if (bink == nullptr) return 0;
    const uint32_t value = pause != 0 ? 1u : 0u;
    if (bink->Paused != value && value == 0) bink->impl->timerStartMs = 0;  // resume: restart the timer
    bink->Paused = value;
#if DOTD_HAVE_FFMPEG_BINK
    for (BinkAudioTrack& track : bink->impl->audio) dotd::audio::StreamSetPaused(track.stream, value != 0);
#endif
    return static_cast<int32_t>(value);
}

void BinkGetFrameBuffersInfo(BINK* bink, BINKFRAMEBUFFERS* buffers) {
    std::memset(buffers, 0, sizeof(*buffers));
    if (bink == nullptr) return;
    buffers->TotalFrames = 2;
    buffers->YABufferWidth = bink->Width;
    buffers->YABufferHeight = bink->Height;
    buffers->cRcBBufferWidth = (bink->Width + 1) / 2;
    buffers->cRcBBufferHeight = (bink->Height + 1) / 2;
    buffers->FrameNum = 0;
    const bool alpha = (bink->impl->videoFlags & 0x00100000u) != 0;  // BINK_FLAG_ALPHA
    for (BINKFRAMEPLANESET& set : buffers->Frames) {
        set.YPlane.Allocate = 1;
        set.cRPlane.Allocate = 1;
        set.cBPlane.Allocate = 1;
        set.APlane.Allocate = alpha ? 1 : 0;
    }
}

void BinkRegisterFrameBuffers(BINK* bink, BINKFRAMEBUFFERS* buffers) {
    if (bink != nullptr) bink->impl->buffers = buffers;
}

// Bink's volume: 32768 = 1.0 (up to 65536), per opened track ID.
void BinkSetVolume(BINK* bink, uint32_t trackId, int32_t volume) {
#if DOTD_HAVE_FFMPEG_BINK
    if (bink == nullptr) return;
    for (BinkAudioTrack& track : bink->impl->audio) {
        if (track.id == trackId) dotd::audio::StreamSetGain(track.stream, static_cast<float>(volume) / 32768.0f);
    }
#else
    (void)bink;
    (void)trackId;
    (void)volume;
#endif
}

void BinkSetSoundTrack(uint32_t totalTracks, const uint32_t* trackIds) {
    g_soundTrackCount = std::min<uint32_t>(totalTracks, 16u);
    for (uint32_t i = 0; i < g_soundTrackCount; ++i) g_soundTrackIds[i] = trackIds[i];
}

namespace dotd::video {

bool HasBinkDecoder() { return DOTD_HAVE_FFMPEG_BINK != 0; }

bool GetDecodedPlanes(BINK* bink, DecodedPlanes* out) {
#if DOTD_HAVE_FFMPEG_BINK
    if (bink == nullptr || bink->impl->decodedFrame == 0) return false;
    const AVFrame* f = bink->impl->frame;
    out->y = f->data[0];
    out->cb = f->data[1];
    out->cr = f->data[2];
    out->a = f->data[3];
    out->width = static_cast<int>(bink->Width);
    out->height = static_cast<int>(bink->Height);
    out->yPitch = f->linesize[0];
    out->cPitch = f->linesize[1];
    out->aPitch = f->linesize[3];
    out->frame = bink->impl->decodedFrame;
    return true;
#else
    (void)bink;
    (void)out;
    return false;
#endif
}

uint32_t CountKeyFrames(BINK* bink) {
    if (bink == nullptr) return 0;
    uint32_t n = 0;
    for (uint32_t f = 1; f <= bink->Frames; ++f) n += IsKey(bink->impl, f) ? 1u : 0u;
    return n;
}

}  // namespace dotd::video
