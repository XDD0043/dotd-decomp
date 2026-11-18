// bink.cpp - see bink.h. The Bink 1 container is read here (header, audio track table, frame index);
// each frame's video packet goes to FFmpeg's bink decoder, the audio packets of the opened tracks to
// FFmpeg's binkaudio decoder and from there to a platform mixer stream (platform/audio/mixer.h).
//
// A "DVP9" file (the web pack's re-encoded video, dotd/web/pack_video.py) is read here too: the same layout with
// the picture as VP9 (FFmpeg's vp9 decoder) and only the first audio track in the frames; each other track is a
// file of its own next to it ("<video>.Ann"), opened when the game plays that track.
// A DVP9 video is decoded ahead on a thread of its own (see Ahead): it is the web build's format, read over the
// network and decoded in software on whatever the browser runs on, and the game's frame must wait for neither.
// BinkWait answers "not yet" while the next frame is not decoded; BinkDoFrame then only copies it.
#include "platform/video/bink.h"

#include <algorithm>
#include <chrono>
#include <condition_variable>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <deque>
#include <memory>
#include <mutex>
#include <string>
#include <thread>
#include <vector>

#include "platform/audio/mixer.h"
#include "platform/cell/fs.h"
#include "platform/cell/sys_time.h"
#include "platform/hostfs.h"
#include "platform/log.h"
#ifdef __EMSCRIPTEN__
#include "platform/web/web.h"
#endif

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
    std::FILE* side = nullptr;         // DVP9: the track's own file (see OpenSideTrack)
    std::vector<uint32_t> sideIndex;   // DVP9: Frames + 1 offsets into it
};
#endif

// DVP9: one frame decoded ahead of its time.
struct AheadFrame {
    uint32_t number = 0;
    std::vector<uint8_t> y, cb, cr;         // the planes, width (or half width) bytes per row
    std::vector<std::vector<float>> sound;  // per opened track: the frame's samples, interleaved (empty: none)
};

// DVP9: the frames a thread decodes ahead (AheadThread). The thread owns the file, the decoders and BinkImpl's
// decoding state; the game's thread owns the BINK, the timing fields and the mixer streams; this is all they share.
struct Ahead {
    std::mutex mutex;
    std::condition_variable changed;
    std::deque<std::unique_ptr<AheadFrame>> ready;  // decoded, in the order BinkDoFrame takes them
    std::vector<std::unique_ptr<AheadFrame>> spare;
    std::unique_ptr<AheadFrame> shown;              // the frame BinkDoFrame took last (the game's thread only)
    uint32_t next = 1;      // the frame decoded next
    uint32_t expected = 1;  // the frame BinkDoFrame takes next: ready's first when there is one
    uint32_t jumps = 0;     // counts AheadJump: a frame decoded for an earlier count is dropped
    bool quit = false;      // BinkClose: the thread frees everything and ends
    bool failed = false;    // a read or decode error: BinkDoFrame reports it
};

struct BinkImpl {
    std::FILE* file = nullptr;
    uint32_t signature = 0;            // 'BIKi' etc. (the codec tag)
    uint32_t fileSize = 0;             // header +4 plus 8
    uint32_t videoFlags = 0;           // header +0x24 (the decoder's extradata)
    std::vector<uint32_t> index;       // Frames + 1 offsets; bit 0 = keyframe
    std::vector<uint8_t> packet;
    std::vector<uint8_t> sidePacket;
    uint32_t decodedFrame = 0;         // the frame the decoder holds (0 = none)
    // Timing (BinkWait): the PS3 Bink keeps these at +0x2b4 (frames shown), +0x2c0 (timer start, ms),
    // +0x2c4 (frames shown at the timer start, minus 1).
    uint32_t framesShown = 0;
    uint32_t timerStartMs = 0;
    uint32_t timerBase = 0;
    BINKFRAMEBUFFERS* buffers = nullptr;
    uint32_t audioSignature = 0;       // the Bink signature the audio decoders read their revision from
    uint32_t inlineTracks = 0;         // the audio tracks whose packets are in the frames (Bink: all of them)
    bool vp9 = false;                  // a DVP9 file
    uint32_t frames = 0;               // BINK::Frames
    std::string host;                  // the file's host path
    Ahead* ahead = nullptr;            // DVP9: the frames decoded ahead
    AheadFrame* capture = nullptr;     // DVP9: the frame whose sound DecodeOne is collecting
    bool starved = false;              // DVP9: a frame was due before it was decoded
    double decodeMs = 0.0, decodeMaxMs = 0.0;  // DVP9: time spent in DecodeOne (logged when the video closes)
    uint32_t decoded = 0;
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

dotd::video::BinkReplayEndSource g_binkReplayEnd = nullptr;  // DEBUG (DOTD_REPLAY)
int32_t BinkReplayEnd() { return g_binkReplayEnd != nullptr ? g_binkReplayEnd() : 0; }

// Bink's timer: milliseconds of the platform system clock (the PS3 library reads the time base the same way).
uint32_t TimeMs() { return static_cast<uint32_t>(sys_time_get_system_time() / 1000); }

// Bit 0 of a frame's index entry marks a keyframe; the first frame always is one.
bool IsKey(const BinkImpl* impl, uint32_t frame) {  // frame 1-based
    return frame == 1 || (impl->index[frame - 1] & 1u) != 0;
}

#if DOTD_HAVE_FFMPEG_BINK
// One audio packet of a track (its first word is the decoded size in bytes, which the decoder skips).
// sink: where the samples go instead of the mixer stream (DVP9: they are queued with their frame).
void DecodeAudio(BinkAudioTrack* track, const uint8_t* data, uint32_t size, AVPacket* pkt, std::vector<float>* sink) {
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
        if (sink != nullptr) {
            sink->insert(sink->end(), track->interleaved.begin(), track->interleaved.end());
        } else {
            dotd::audio::StreamPush(track->stream, track->interleaved.data(), n);
        }
        av_frame_unref(f);
    }
    av_frame_free(&f);
}

// A DVP9 video's track that is not in the frames: "<video>.Ann" = 'DVPA', the frame count, Frames + 1 offsets,
// then the track's packets (dotd/web/pack_video.py). Without the file the track stays silent.
void OpenSideTrack(BinkImpl* impl, BinkAudioTrack* track) {
    char suffix[8];
    std::snprintf(suffix, sizeof(suffix), ".A%02u", track->index);
    std::FILE* file = dotd::platform::hostfs::OpenStdio(impl->host + suffix);
    uint8_t head[8];
    std::vector<uint8_t> raw(4 * static_cast<size_t>(impl->frames + 1));
    if (file == nullptr || std::fread(head, 1, sizeof(head), file) != sizeof(head) || std::memcmp(head, "DVPA", 4) != 0 ||
        ReadLE32(head + 4) != impl->frames || std::fread(raw.data(), 1, raw.size(), file) != raw.size()) {
        DOTD_LOG("bink: %s%s: missing, or not this video's track", impl->host.c_str(), suffix);
        if (file != nullptr) std::fclose(file);
        return;
    }
    track->sideIndex.resize(impl->frames + 1);
    for (uint32_t i = 0; i <= impl->frames; ++i) track->sideIndex[i] = ReadLE32(raw.data() + 4 * i);
    track->side = file;
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
                std::memcpy(track.codec->extradata, &impl->audioSignature, 4);  // the decoder reads the revision byte
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
            impl->audio.push_back(std::move(track));  // (DVP9: AheadThread opens a track's own file)
            break;
        }
    }
}

// streams: the mixer streams too (not for a DVP9 video's thread: BinkClose destroyed them).
void CloseAudioTracks(BinkImpl* impl, bool streams) {
    for (BinkAudioTrack& track : impl->audio) {
        if (streams) dotd::audio::StreamDestroy(track.stream);
        avcodec_free_context(&track.codec);
        if (track.side != nullptr) std::fclose(track.side);
    }
    impl->audio.clear();
}

// Reads frame `frame` (1-based) and decodes its video part. Returns false on a read or decode error.
bool DecodeOne(BinkImpl* impl, uint32_t frame) {
    const uint32_t begin = impl->index[frame - 1] & ~1u;
    uint32_t end = impl->index[frame] & ~1u;
    if (frame == impl->frames && (end <= begin || end > impl->fileSize)) end = impl->fileSize;
    if (end <= begin) return false;
    impl->packet.resize(end - begin);
    if (std::fseek(impl->file, static_cast<long>(begin), SEEK_SET) != 0 ||
        std::fread(impl->packet.data(), 1, end - begin, impl->file) != end - begin) {
        return false;
    }
    // The audio packets come first: per track a u32 size, then the data. Only the frame after the last
    // one whose audio was queued feeds the mixer (re-decodes after a seek stay silent); the first frame follows
    // the last one (a looping video's sound goes on when BinkNextFrame wraps).
    const bool feedAudio = frame == impl->audioFrame + 1 || (frame == 1 && impl->audioFrame == impl->frames);
    uint32_t pos = 0;
    for (uint32_t t = 0; t < impl->inlineTracks; ++t) {
        if (pos + 4 > impl->packet.size()) return false;
        const uint32_t size = ReadLE32(impl->packet.data() + pos);
        if (pos + 4 + size > impl->packet.size()) return false;
        if (feedAudio && size >= 4) {
            for (BinkAudioTrack& track : impl->audio) {
                if (track.index != t) continue;
                DecodeAudio(&track, impl->packet.data() + pos + 4, size, impl->avPacket,
                            impl->capture != nullptr ? &impl->capture->sound[&track - impl->audio.data()] : nullptr);
            }
        }
        pos += 4 + size;
    }
    if (feedAudio) {
        for (BinkAudioTrack& track : impl->audio) {  // DVP9: the tracks in files of their own
            if (track.side == nullptr) continue;
            const uint32_t from = track.sideIndex[frame - 1], to = track.sideIndex[frame];
            if (to < from + 4) continue;
            impl->sidePacket.resize(to - from);
            if ((std::ftell(track.side) != static_cast<long>(from) &&
                 std::fseek(track.side, static_cast<long>(from), SEEK_SET) != 0) ||
                std::fread(impl->sidePacket.data(), 1, to - from, track.side) != to - from) {
                continue;
            }
            DecodeAudio(&track, impl->sidePacket.data(), to - from, impl->avPacket,
                        impl->capture != nullptr ? &impl->capture->sound[&track - impl->audio.data()] : nullptr);
        }
        impl->audioFrame = frame;
    }
    if (pos > impl->packet.size()) return false;
    uint32_t size = static_cast<uint32_t>(impl->packet.size()) - pos;
    if (impl->vp9) {  // DVP9: the picture's size comes first (the frame may end in a padding byte)
        if (size < 4 || ReadLE32(impl->packet.data() + pos) > size - 4) return false;
        size = ReadLE32(impl->packet.data() + pos);
        pos += 4;
    }
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
bool DecodeTo(BinkImpl* impl, uint32_t frame) {
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
        if (!impl->vp9) {
            if (!DecodeOne(impl, f)) return false;
            continue;
        }
        const auto t0 = std::chrono::steady_clock::now();
        if (!DecodeOne(impl, f)) return false;
        const double ms = std::chrono::duration<double, std::milli>(std::chrono::steady_clock::now() - t0).count();
        impl->decodeMs += ms;
        impl->decodeMaxMs = std::max(impl->decodeMaxMs, ms);
        ++impl->decoded;
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

// ---- DVP9: decoding ahead ---------------------------------------------------------------------------------------
// Frames kept decoded ahead of the one shown (1280x720: 1.4 MB each).
constexpr size_t kAheadFrames = 12;

// Makes `frame` the next one the thread delivers; what was decoded for the old order is dropped (mutex held).
void AheadJump(Ahead* a, uint32_t frame) {
    for (std::unique_ptr<AheadFrame>& f : a->ready) a->spare.push_back(std::move(f));
    a->ready.clear();
    a->next = frame;
    a->expected = frame;
    ++a->jumps;
    a->changed.notify_all();
}

// True when BinkDoFrame has bink->FrameNum at hand (or an error to report).
bool AheadReady(BINK* bink) {
    Ahead* a = bink->impl->ahead;
    std::lock_guard<std::mutex> lock(a->mutex);
    if (a->failed) return true;
    if (a->expected != bink->FrameNum) AheadJump(a, bink->FrameNum);
    return !a->ready.empty();
}

// The thread of one open DVP9 video: decodes the frames in playing order (after the last comes the first, as
// BinkNextFrame goes) up to kAheadFrames ahead, and starts again from the target after a jump (BinkGoto). The
// reads of the file (over HTTP in the web build) happen here too. It ends, and frees the decoders and impl,
// when BinkClose sets quit; BinkClose does not wait for it (it may be in a read).
void AheadThread(BinkImpl* impl) {
    Ahead* a = impl->ahead;
    for (BinkAudioTrack& track : impl->audio) {
        if (track.index >= impl->inlineTracks) OpenSideTrack(impl, &track);
    }
    const int w = impl->codec->width, h = impl->codec->height;
    const int cw = (w + 1) / 2, ch = (h + 1) / 2;
    uint32_t jumps = 0;
    std::unique_lock<std::mutex> lock(a->mutex);
    while (!a->quit) {
        if (a->failed || a->ready.size() >= kAheadFrames) {
            a->changed.wait(lock);
            continue;
        }
        const uint32_t target = a->next;
        const bool jumped = a->jumps != jumps;
        jumps = a->jumps;
        std::unique_ptr<AheadFrame> out;
        if (!a->spare.empty()) {
            out = std::move(a->spare.back());
            a->spare.pop_back();
        } else {
            out = std::make_unique<AheadFrame>();
        }
        lock.unlock();

        if (jumped) {  // as BinkGoto: the sound starts again with the target frame
            for (BinkAudioTrack& track : impl->audio) {
                if (track.codec != nullptr) avcodec_flush_buffers(track.codec);
            }
            impl->audioFrame = target - 1;
            // The target is decoded again when the decoder already holds it (the game rewinds a video it has just
            // opened, and frame 1 was decoded meanwhile): DecodeTo would return at once, the frame's sound would
            // never be read, and no later frame would follow "the last one with sound": a silent video.
            if (impl->decodedFrame == target) impl->decodedFrame = 0;
        }
        out->number = target;
        out->sound.resize(impl->audio.size());
        for (std::vector<float>& s : out->sound) s.clear();
        impl->capture = out.get();
        const bool ok = DecodeTo(impl, target);
        impl->capture = nullptr;
        if (ok) {
            const AVFrame* f = impl->frame;
            out->y.resize(static_cast<size_t>(w) * h);
            out->cb.resize(static_cast<size_t>(cw) * ch);
            out->cr.resize(static_cast<size_t>(cw) * ch);
            for (int row = 0; row < h; ++row) {
                std::memcpy(out->y.data() + static_cast<size_t>(row) * w, f->data[0] + static_cast<size_t>(row) * f->linesize[0],
                            static_cast<size_t>(w));
            }
            for (int row = 0; row < ch; ++row) {  // FFmpeg: [1] = Cb (U), [2] = Cr (V)
                std::memcpy(out->cb.data() + static_cast<size_t>(row) * cw, f->data[1] + static_cast<size_t>(row) * f->linesize[1],
                            static_cast<size_t>(cw));
                std::memcpy(out->cr.data() + static_cast<size_t>(row) * cw, f->data[2] + static_cast<size_t>(row) * f->linesize[2],
                            static_cast<size_t>(cw));
            }
        }

        lock.lock();
        if (!ok) {
            a->failed = true;
        } else if (a->jumps == jumps) {
            a->ready.push_back(std::move(out));
            a->next = target >= impl->frames ? 1 : target + 1;
        }
        if (out != nullptr) a->spare.push_back(std::move(out));
        a->changed.notify_all();
    }
    lock.unlock();
    if (impl->decoded != 0) {
        DOTD_LOG("bink: re-encoded video closed: %u frames decoded on its thread, %.1f ms each (longest %.1f ms)",
                 impl->decoded, impl->decodeMs / impl->decoded, impl->decodeMaxMs);
    }
    CloseAudioTracks(impl, false);
    av_packet_free(&impl->avPacket);
    av_frame_free(&impl->frame);
    avcodec_free_context(&impl->codec);
    if (impl->file != nullptr) std::fclose(impl->file);
    delete a;
    delete impl;
}
#endif

// Bink's own timing: 0 once the next frame's time has come (BinkWait).
int32_t WaitForClock(BINK* bink);

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
    std::FILE* file = dotd::platform::hostfs::OpenStdio(host);
    if (file == nullptr) {
        DOTD_LOG("bink: cannot open %s", host.c_str());
        return nullptr;
    }
#ifdef __EMSCRIPTEN__
    // The web build: the header, the track table and the frame index (what this function reads, on the game's
    // thread) come in one small request of their own instead of with the file's first megabyte.
    std::vector<uint8_t> head;
    dotd::platform::web::ReadHead(host, 65536, &head);
    size_t headAt = 0;
#endif
    const auto readNext = [&](void* dst, size_t n) {
#ifdef __EMSCRIPTEN__
        if (headAt + n <= head.size()) {
            std::memcpy(dst, head.data() + headAt, n);
            headAt += n;
            return true;
        }
        if (std::fseek(file, static_cast<long>(headAt), SEEK_SET) != 0) return false;  // (a longer index: from the file)
        headAt += n;
#endif
        return std::fread(dst, 1, n, file) == n;
    };
    uint8_t header[44];
    const bool read = readNext(header, sizeof(header));
    const bool vp9 = read && std::memcmp(header, "DVP9", 4) == 0;  // the web pack's re-encoded video
    if (!read || (!vp9 && (std::memcmp(header, "BIK", 3) != 0 || header[3] < 'b' || header[3] > 'i'))) {
        DOTD_LOG("bink: %s is not a Bink 1 file", host.c_str());
        std::fclose(file);
        return nullptr;
    }
    BINK* bink = new BINK();
    BinkImpl* impl = new BinkImpl();
    bink->impl = impl;
    impl->file = file;
    impl->host = host;
    impl->vp9 = vp9;
    impl->signature = ReadLE32(header);
    impl->audioSignature = vp9 ? ReadLE32(header + 16) : impl->signature;
    impl->fileSize = ReadLE32(header + 4) + 8;
    bink->Frames = ReadLE32(header + 8);
    impl->frames = bink->Frames;
    bink->Width = ReadLE32(header + 20);
    bink->Height = ReadLE32(header + 24);
    bink->FrameRate = ReadLE32(header + 28);
    bink->FrameRateDiv = ReadLE32(header + 32);
    impl->videoFlags = ReadLE32(header + 36);
    bink->NumTracks = ReadLE32(header + 40);
    impl->inlineTracks = vp9 ? std::min(ReadLE32(header + 12), bink->NumTracks) : bink->NumTracks;
    bink->OpenFlags = flags;
    bool ok = bink->Frames > 0 && bink->Frames < 1000000 && bink->NumTracks < 256 && bink->FrameRate != 0 &&
              bink->FrameRateDiv != 0;
    // Audio track table: max decoded sizes, (sample rate, flags), track ids: 12 bytes per track.
    std::vector<uint8_t> trackTable(12 * static_cast<size_t>(ok ? bink->NumTracks : 0));
    if (ok && !trackTable.empty()) ok = readNext(trackTable.data(), trackTable.size());
    if (ok) {
        impl->index.resize(bink->Frames + 1);
        std::vector<uint8_t> raw(4 * static_cast<size_t>(bink->Frames + 1));
        ok = readNext(raw.data(), raw.size());
        for (uint32_t i = 0; ok && i <= bink->Frames; ++i) impl->index[i] = ReadLE32(raw.data() + 4 * i);
    }
    if (ok) {
        const AVCodec* codec = avcodec_find_decoder(vp9 ? AV_CODEC_ID_VP9 : AV_CODEC_ID_BINKVIDEO);
        impl->codec = codec != nullptr ? avcodec_alloc_context3(codec) : nullptr;
        ok = impl->codec != nullptr;
        if (ok) {
            impl->codec->width = static_cast<int>(bink->Width);
            impl->codec->height = static_cast<int>(bink->Height);
            if (!vp9) {
                impl->codec->codec_tag = impl->signature;
                impl->codec->extradata = static_cast<uint8_t*>(av_mallocz(4 + AV_INPUT_BUFFER_PADDING_SIZE));
                std::memcpy(impl->codec->extradata, header + 36, 4);
                impl->codec->extradata_size = 4;
            }
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
    if (vp9) {  // from here on the file and the decoders are the thread's
        impl->ahead = new Ahead();
        std::thread(AheadThread, impl).detach();
    }
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
        if (impl->ahead != nullptr) {  // DVP9: the thread frees the rest (see AheadThread)
            for (BinkAudioTrack& track : impl->audio) dotd::audio::StreamDestroy(track.stream);
            {
                std::lock_guard<std::mutex> lock(impl->ahead->mutex);
                impl->ahead->quit = true;
                impl->ahead->changed.notify_all();
            }
            delete bink;
            return;
        }
        CloseAudioTracks(impl, true);
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
    if (impl->ahead != nullptr) {
        // DVP9: the frame was decoded ahead. (BinkWait keeps the game from asking before it is there; the wait
        // here is for a caller that did not ask BinkWait.)
        Ahead* a = impl->ahead;
        std::unique_lock<std::mutex> lock(a->mutex);
        if (a->expected != bink->FrameNum) AheadJump(a, bink->FrameNum);
        a->changed.wait(lock, [a] { return a->failed || !a->ready.empty(); });
        if (a->failed) {
            bink->ReadError = 1;
            return 0;
        }
        if (a->shown != nullptr) a->spare.push_back(std::move(a->shown));
        a->shown = std::move(a->ready.front());
        a->ready.pop_front();
        a->expected = bink->FrameNum >= bink->Frames ? 1 : bink->FrameNum + 1;
        a->changed.notify_all();
        lock.unlock();
        const AheadFrame* f = a->shown.get();
        for (size_t i = 0; i < f->sound.size(); ++i) {
            const BinkAudioTrack& track = impl->audio[i];
            if (!f->sound[i].empty()) {
                dotd::audio::StreamPush(track.stream, f->sound[i].data(),
                                        static_cast<uint32_t>(f->sound[i].size() / track.channels));
            }
        }
        BINKFRAMEBUFFERS* fb = impl->buffers;
        if (fb != nullptr && fb->TotalFrames > 0) {
            fb->FrameNum = (fb->FrameNum + 1) % static_cast<uint32_t>(fb->TotalFrames);
            BINKFRAMEPLANESET& set = fb->Frames[fb->FrameNum];
            const int w = static_cast<int>(bink->Width), h = static_cast<int>(bink->Height);
            const int cw = (w + 1) / 2, ch = (h + 1) / 2;
            CopyPlane(f->y.data(), w, &set.YPlane, w, h);
            CopyPlane(f->cr.data(), cw, &set.cRPlane, cw, ch);
            CopyPlane(f->cb.data(), cw, &set.cBPlane, cw, ch);
            fb->Textures[fb->FrameNum].dirty = 1;
        }
        return 1;
    }
#ifdef __EMSCRIPTEN__
    const uint32_t before = TimeMs();
#endif
    if (!DecodeTo(impl, bink->FrameNum)) {
        bink->ReadError = 1;
        return 0;
    }
#ifdef __EMSCRIPTEN__
    // The web build reads the video over the network. After a wait for data the timer starts again from this
    // frame (as after a pause): otherwise the picture would run ahead of the sound to catch the clock up.
    if (TimeMs() - before > 250u) impl->timerStartMs = 0;
#endif
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
    const int32_t wait = WaitForClock(bink);
#if DOTD_HAVE_FFMPEG_BINK
    // DVP9: the frame is decoded ahead on a thread. While it is not there the game keeps the last one on the
    // screen; the timer then starts again from the late frame, so the picture does not run to catch the clock up.
    if (wait == 0 && bink != nullptr && bink->impl->ahead != nullptr) {
        if (!AheadReady(bink)) {
            bink->impl->starved = true;
            return 1;
        }
        if (bink->impl->starved) {
            bink->impl->starved = false;
            bink->impl->timerStartMs = 0;
        }
    }
#endif
    return wait;
}

namespace {
int32_t WaitForClock(BINK* bink) {
    if (bink == nullptr) return 0;
    // DEBUG (DOTD_REPLAY): the original's video ended in this frame (decode now), or not yet (hold the last frame)
    const int32_t replayEnd = BinkReplayEnd();
    if (replayEnd > 0) return 0;
    if (replayEnd < 0 && bink->FrameNum >= bink->Frames) return 1;
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
}  // namespace

// 0x009f3e70 in the PS3 library (Ghidra BinkWait): skipping only happens to stay in sync with an audio
// track. Audio is not played yet, so playback never skips.
int32_t BinkShouldSkip(BINK* bink) {
    (void)bink;
    return BinkReplayEnd() > 0 ? 1 : 0;  // DEBUG (DOTD_REPLAY): the original's video ended in this frame
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
    if (bink->impl->ahead != nullptr) {  // DVP9: the thread decodes from the target (and flushes its decoders)
        for (BinkAudioTrack& track : bink->impl->audio) dotd::audio::StreamClear(track.stream);
        std::lock_guard<std::mutex> lock(bink->impl->ahead->mutex);
        AheadJump(bink->impl->ahead, frame);
        return;
    }
    for (BinkAudioTrack& track : bink->impl->audio) {
        dotd::audio::StreamClear(track.stream);
        if (track.codec != nullptr) avcodec_flush_buffers(track.codec);
    }
    bink->impl->audioFrame = frame - 1;
    // (the frame the decoder holds is decoded again, or its sound and all the sound after it would be skipped)
    if (!bink->impl->audio.empty() && bink->impl->decodedFrame == frame) bink->impl->decodedFrame = 0;
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
    if (bink != nullptr && bink->impl->ahead != nullptr) {  // DVP9: the frame BinkDoFrame took last
        const AheadFrame* shown = bink->impl->ahead->shown.get();
        if (shown == nullptr) return false;
        out->y = shown->y.data();
        out->cb = shown->cb.data();
        out->cr = shown->cr.data();
        out->a = nullptr;
        out->width = static_cast<int>(bink->Width);
        out->height = static_cast<int>(bink->Height);
        out->yPitch = out->width;
        out->cPitch = (out->width + 1) / 2;
        out->aPitch = 0;
        out->frame = shown->number;
        return true;
    }
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

void SetBinkReplayEndSource(BinkReplayEndSource source) { g_binkReplayEnd = source; }

uint32_t CountKeyFrames(BINK* bink) {
    if (bink == nullptr) return 0;
    uint32_t n = 0;
    for (uint32_t f = 1; f <= bink->Frames; ++f) n += IsKey(bink->impl, f) ? 1u : 0u;
    return n;
}

}  // namespace dotd::video
