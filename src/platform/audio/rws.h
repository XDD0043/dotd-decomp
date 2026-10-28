// rws.h - RenderWare Audio stream files (.RWS: USRDIR/MUSIC/nn/STRAnnn.RWS, LVLxxx/SPEECH/*.RWS), read
// for the stream players RWA runs on its "RWA" thread. Platform code: the container layout is taken from
// the data (no RWA source), checked on all 253 files of the game.
//
// Layout (RW chunks, little-endian headers): 0x80d { 0x80e header, 0x80f data }. The header body is
// big-endian: +0x20 segment count, +0x28 layer count, +0x50 the stream name (NUL, padded to 16); then per
// segment 0x20 bytes (+0x18 bytes incl. padding, +0x1c offset in the data), per segment and layer the
// usable byte count, per segment a GUID, the segment names; per layer 0x28 bytes (+0x10 block size,
// +0x18 interleave, +0x1a frame size, +0x20 usable bytes per block, +0x24 start in the segment); per layer
// 0x30 bytes of format (+0x00 sample rate, +0x0c bits, +0x0d channels, +0x1c codec GUID). The data is
// cut into blocks of the layers' block sizes, each holding `usable` bytes then zero padding.
//
// Codecs in the game: music {D01BD217-...} PCM 16-bit big-endian, 48 kHz stereo (sample interleaved),
// blocks 0x8800 / 0x801c usable; speech {46360B16-...}, 48 kHz mono, ATRAC3 frames of 152 bytes (1024
// samples; each frame starts with the 0x28 sound-unit header), decoded with FFmpeg's atrac3 (ffbink).
#pragma once
#include <cstdint>
#include <cstdio>
#include <string>
#include <vector>

namespace dotd::audio {

struct RwsLayer {
    uint32_t blockSize = 0, blockUsable = 0, start = 0, interleave = 0, frameSize = 0;
    uint32_t sampleRate = 0, bits = 0, channels = 0;
    uint8_t codec[16] = {};
};
struct RwsSegment {
    uint32_t bytes = 0, offset = 0;
    std::vector<uint32_t> usable;  // per layer
    std::string name;
};

class RwsFile {
public:
    ~RwsFile();
    // hostPath: a host file path. False on a malformed file.
    bool Open(const std::string& hostPath);
    void Close();
    bool IsPcm16(uint32_t layer = 0) const;
    // Selects a segment/layer and rewinds. False when out of range or not PCM.
    bool Select(uint32_t segment, uint32_t layer);
    // Reads up to `frames` frames of the selected layer as native int16 (interleaved); returns the count
    // (0 at the end).
    uint32_t Read(int16_t* out, uint32_t frames);
    uint64_t TotalFrames() const;  // of the selected segment/layer
    bool IsAtrac3(uint32_t layer = 0) const;
    // Decodes a whole segment of an ATRAC3 layer into native int16 (the layer's channels, interleaved). False
    // when the layer is not ATRAC3, the segment is out of range or no decoder is built in.
    bool DecodeAtrac3(uint32_t segment, uint32_t layer, std::vector<int16_t>* out);

    std::string name;
    std::vector<RwsSegment> segments;
    std::vector<RwsLayer> layers;

private:
    std::FILE* file_ = nullptr;
    uint64_t dataOffset_ = 0;
    uint32_t segment_ = 0, layer_ = 0;
    uint64_t consumed_ = 0;  // usable bytes of the selection already read
    std::vector<uint8_t> block_;
};

}  // namespace dotd::audio
