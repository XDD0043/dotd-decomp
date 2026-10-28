// bink.h - the RAD Bink 1.x library calls the game makes (the PS3 build links Bink at 0x9eb000-0xa0c000
// and reaches it through TocBridge_Bink* stubs), re-implemented on FFmpeg's Bink decoder (thirdparty/
// ffmpeg-bink). Platform code: new code, not a port. The game code calls these exactly where the original
// calls Bink, with the same meaning:
//   BinkOpen / BinkClose, BinkDoFrame (decode the current frame into the registered frame buffers),
//   BinkNextFrame (advance; wraps to frame 1 after the last), BinkWait (1 = not yet time for the next
//   frame), BinkShouldSkip (1 = behind, skip showing this frame), BinkGoto, BinkGetKeyFrame, BinkPause,
//   BinkGetFrameBuffersInfo / BinkRegisterFrameBuffers, BinkSetVolume / BinkSetSoundTrack.
// Timing follows Bink's: real time from sys_time_get_system_time() (the platform's system clock, which
// tests and the Console timing mode script), frame rate from the file header.
// Audio: the opened tracks (BinkSetSoundTrack + BINKSNDTRACK, else the first) are decoded with FFmpeg's
// binkaudio and queued on platform mixer streams; BinkSetVolume sets their gain, BinkPause pauses them.
//
// Note on the Ghidra names: TocBridge_BinkShouldSkip_maybe (0x98e650 -> 0x9f0010) is BinkWait (it returns 0
// once the frame time has elapsed) and TocBridge_BinkWait (0x98e620 -> 0x9f3e70) is BinkShouldSkip (it
// returns 1 only when playback is behind by more than a threshold, up to 3 frames in a row).
#pragma once
#include <cstdint>

struct BinkImpl;

// The BINK handle. Only the fields the game reads are kept; the comments give the PS3 offsets.
struct BINK {
    uint32_t Width;         // +0x00
    uint32_t Height;        // +0x04
    uint32_t Frames;        // +0x08 frame count
    uint32_t FrameNum;      // +0x0c the current frame (1-based): the one BinkDoFrame decodes
    uint32_t LastFrameNum;  // +0x10
    uint32_t FrameRate;     // +0x14 frames per FrameRateDiv seconds
    uint32_t FrameRateDiv;  // +0x18
    uint32_t ReadError;     // +0x1c non-zero after a read error (the game then reopens the stream)
    uint32_t OpenFlags;     // +0x20
    uint32_t NumTracks;     // +0xe0 _maybe: the audio tracks opened (PS3_CKVideo_Play: >1 disables the XMB music)
    uint32_t Paused;        // +0xec
    BinkImpl* impl;         // host decoder state
};

// One plane of a frame-buffer set (Bink's BINKPLANE).
struct BINKPLANE {
    int32_t Allocate;       // the plane exists in this video
    void* Buffer;           // host memory, BufferPitch bytes per row
    uint32_t BufferPitch;
};
// One set of planes (Bink's BINKFRAMEPLANESET).
struct BINKFRAMEPLANESET {
    BINKPLANE YPlane;
    BINKPLANE cRPlane;
    BINKPLANE cBPlane;
    BINKPLANE APlane;
};
// The R8 textures of one set (0 = none). PS3: the GL texture names and the set's fence.
struct BINKPLANETEXTURES {
    uint32_t y, cR, cB, a;
    uint32_t dirty;  // host: planes written since the last upload
};
// The frame-buffer record (Bink's BINKFRAMEBUFFERS plus the PS3 build's textures): PS3_CKVideo +0x194,
// 0xa8 bytes on the PS3 (sets at +0x18, stride 0x30; textures and fences at +0x78, stride 0x14; the PBO
// at +0xa0, the per-set size at +0xa4).
struct BINKFRAMEBUFFERS {
    int32_t TotalFrames;          // +0x00 number of sets (2)
    uint32_t YABufferWidth;       // +0x04
    uint32_t YABufferHeight;      // +0x08
    uint32_t cRcBBufferWidth;     // +0x0c
    uint32_t cRcBBufferHeight;    // +0x10
    uint32_t FrameNum;            // +0x14 the set the last BinkDoFrame wrote
    BINKFRAMEPLANESET Frames[2];  // +0x18
    BINKPLANETEXTURES Textures[2];  // +0x78
    void* PlaneMemory;            // +0xa0 host: the planes' memory (PS3: a PBO)
    uint32_t SetSize;             // +0xa4 bytes per set
};

enum : uint32_t {
    BINKGETKEYPREVIOUS = 0,
    BINKGETKEYNEXT = 1,
    BINKGETKEYCLOSEST = 2,
    BINKGETKEYNOTEQUAL = 128,
};

// path: the game's path (relative paths are under /dev_bdvd/PS3_GAME/USRDIR, like the PS3's current
// directory; '\' already converted). Returns null when the file is missing or not a Bink 1 file.
BINK* BinkOpen(const char* path, uint32_t flags);
void BinkClose(BINK* bink);
int32_t BinkDoFrame(BINK* bink);
void BinkNextFrame(BINK* bink);
int32_t BinkWait(BINK* bink);
int32_t BinkShouldSkip(BINK* bink);
void BinkGoto(BINK* bink, uint32_t frame, int32_t flags);
uint32_t BinkGetKeyFrame(BINK* bink, uint32_t frame, int32_t flags);
int32_t BinkPause(BINK* bink, int32_t pause);
void BinkGetFrameBuffersInfo(BINK* bink, BINKFRAMEBUFFERS* buffers);
void BinkRegisterFrameBuffers(BINK* bink, BINKFRAMEBUFFERS* buffers);
void BinkSetVolume(BINK* bink, uint32_t trackId, int32_t volume);
void BinkSetSoundTrack(uint32_t totalTracks, const uint32_t* trackIds);

namespace dotd::video {
// False when the build has no Bink decoder (the FFmpeg clone was missing at configure time).
bool HasBinkDecoder();
// Host-side helpers (no PS3 counterpart): the planes of the last decoded frame, for tests and tools.
struct DecodedPlanes {
    const uint8_t* y;
    const uint8_t* cr;
    const uint8_t* cb;
    const uint8_t* a;  // null without alpha
    int width, height, yPitch, cPitch, aPitch;
    uint32_t frame;    // the frame number they belong to (0 = none decoded yet)
};
bool GetDecodedPlanes(BINK* bink, DecodedPlanes* out);
// Number of keyframes in the index (tests).
uint32_t CountKeyFrames(BINK* bink);
}  // namespace dotd::video
