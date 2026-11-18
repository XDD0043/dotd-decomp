// rwa_stream.h - RWA's stream player (RwaStreamPlayer, 0x6bf000-0x6c1000, reached through the TocBridge_RwaStreamPlayer_*
// stubs at 0x98f020-0x98f0c0), re-implemented on the platform mixer. Platform code, not a port: on the PS3 the player's
// requests go to RWA's "RWA" thread (RwaStreamPlayerRequest_*), which opens the .RWS file, fills the buffers and feeds
// MultiStream on the SPUs, all in real time. What the K code sees is kept: the calls and records below, the states it
// polls (GetState: +0xd6c) and the playback position (GetCurrentItem).
//
// The player here: a request (source, command, item, volume) is taken by the next Advance (the host's frame hook,
// CKSoundManager::PostUpdate, standing for the RWA thread), and the states move by the frame time:
//   SetSource(path)  -> OPENING, STOPPED kOpenSeconds later (the file's items known);
//   SetSource(null)  -> NOMEDIA;
//   command play     -> PLAYING; the output (GetCurrentItem's position) starts kPrerollSeconds later and the item
//                       plays its whole blocks (the zero padding of the last one included); STOPPED kEndSeconds after
//                       the last block (looping: the item starts again);
//   command pause    -> PAUSING, PAUSED at the next frame (the output kept);
//   command stop     -> STOPPING, STOPPED at the next frame.
// The three times are fitted to RPCS3's captures of LVL010 (work/scratch-c27/rec/fight*: the SoundStream's states and
// the sekens' position flag per frame; speech items 1, 34 and 40 of 0_PS30.RWS, 7, 3 and 2 blocks): the opening ends
// in the 9th frame after SetSource, the position is above 0 five or six frames after the play command, STOPPED is
// first seen 236, 103 and 70 frames after it. Music items are not checked against a capture (the music service is
// not ported).
//
// The item plays on a mixer voice once the output starts: speech is ATRAC3 (decoded with platform/audio/rws.h), music
// 16-bit PCM; gain = the player's volume (SetVolume) x the item volume (SetItemVolume).
#pragma once
#include <cstdint>

struct RwaOutput;
struct RwaStreamPlayer;

// RwaStreamPlayer_GetState: the names of the game's debug table 0x00b00f20 (0 and 1 have none).
enum : uint32_t {
    kRwaStreamOpening = 2,
    kRwaStreamStopped = 3,
    kRwaStreamPausing = 4,
    kRwaStreamPaused = 5,
    kRwaStreamPlaying = 6,
    kRwaStreamStarved = 7,
    kRwaStreamStopping = 8,
    kRwaStreamNoMedia = 9,
};
// RwaStreamPlayer_SetCommand: the commands the K code sends (SoundStream_StateMediaStopped / Playing / Paused entries).
enum : uint32_t { kRwaStreamCommandStop = 1, kRwaStreamCommandPlay = 2, kRwaStreamCommandPause = 3 };

// The source record SoundStream_StateOpenSource_maybe 0x11c708 builds on its stack (0x28 bytes on the PS3).
struct RwaStreamSource {
    const char* path;  // +0x00 CKStreamWave_BuildFilePath_maybe: the data root and the wave's path
    uint32_t unk04;    // +0x04 1
    uint32_t unk08;    // +0x08 0
    uint32_t unk0c;    // +0x0c 0
    uint32_t unk10;    // +0x10 0
    uint32_t unk14;    // +0x14 0
    uint32_t unk18;    // +0x18 8
    uint32_t unk1c;    // +0x1c 2
    uint32_t unk20;    // +0x20 1
    uint32_t unk24;    // +0x24 1 for a music stream (CKStreamWave +0x218 clear), 0 for speech
};
// A place in the source (RwaStreamPlayer_SelectItem's target, GetCurrentItem's answer): `by` 3 = the item by index (1 by
// name, 2 by GUID), `unit` 1 = the offset in seconds (2 in samples).
struct RwaStreamPosition {
    uint32_t item;
    uint32_t by;
    float offset;
    uint32_t unit;
};
struct RwaStreamSelect {
    const RwaStreamPosition* position;
    uint32_t unk04;  // 1
};
// RwaStreamPlayer_SetItemVolume's record: the K code passes -1 three times (every item _maybe), then the volume.
struct RwaStreamItemVolume {
    int32_t unk00;
    int32_t unk04;
    int32_t unk08;
    float volume;
};

// 0x006c0600 RwaStreamPlayer_Create_maybe (output's driver, 0, 0, 0, 0): NOMEDIA.
RwaStreamPlayer* RwaStreamPlayer_Create(RwaOutput* output);
// RwaObject_Destroy_maybe(player, 0, 0) (bridge 0x98eeb0).
void RwaStreamPlayer_Destroy(RwaStreamPlayer* player);
// 0x006bf290 RwaStreamPlayer_GetState_maybe
uint32_t RwaStreamPlayer_GetState(const RwaStreamPlayer* player);
// 0x006bf988 RwaStreamPlayer_SetCommand_maybe
void RwaStreamPlayer_SetCommand(RwaStreamPlayer* player, uint32_t command);
// 0x006bfa38 RwaStreamPlayer_SetSource_maybe (bridge 0x98f070): null closes the source.
void RwaStreamPlayer_SetSource(RwaStreamPlayer* player, const RwaStreamSource* source);
// 0x006bf538 RwaStreamPlayer_GetItemCount_maybe: the source's items (segments); 0 before the source is open.
uint32_t RwaStreamPlayer_GetItemCount(const RwaStreamPlayer* player);
// 0x006bff28 RwaStreamPlayer_SelectItem_maybe
void RwaStreamPlayer_SelectItem(RwaStreamPlayer* player, const RwaStreamSelect* select);
// 0x006bfcd0 RwaStreamPlayer_GetCurrentItem_maybe: the item and the offset played in it (by `by` / `unit`); item 0 and
// offset 0 while nothing is output.
void RwaStreamPlayer_GetCurrentItem(const RwaStreamPlayer* player, RwaStreamPosition* position);
// 0x006bf2b8 RwaStreamPlayer_GetVolume_maybe (+0x120) / 0x006bf810 RwaStreamPlayer_SetVolume_maybe
float RwaStreamPlayer_GetVolume(const RwaStreamPlayer* player);
void RwaStreamPlayer_SetVolume(float volume, RwaStreamPlayer* player);
// 0x006bf8b8 RwaStreamPlayer_SetItemVolume_maybe
void RwaStreamPlayer_SetItemVolume(RwaStreamPlayer* player, const RwaStreamItemVolume* volume);
// 0x006bfc20 RwaStreamPlayer_SetLoop_maybe (bridge 0x98f090)
void RwaStreamPlayer_SetLoop(RwaStreamPlayer* player, uint8_t loop);

namespace dotd::audio {

// The RWA thread's time: every player takes its requests and moves on by `seconds` (host hook, once per frame).
void RwaStreamPlayers_Advance(float seconds);

// Replays (debug, off by default): the PS3's stream players run in real time, so the frame a state is reached in is an
// input of a recording. A source that answers (returns true) for a player overrides what GetState returns (state, when
// not -1) and whether GetCurrentItem has an output (`output`; the position is then the player's own, at least 1e-3, or
// `position` when it is not negative: the original's seconds, which follow the PS3's audio clock, not the frame time).
struct RwaStreamReplayAnswer {
    int32_t state;
    bool output;
    float position;
    bool positionQuery;  // in: GetCurrentItem asks (GetState: false)
    float ownPosition;   // in (GetCurrentItem): the player's own position, at least 1e-3
    bool ownOutput;      // in (GetCurrentItem): whether the player itself has an output
};
using RwaStreamReplaySource = bool (*)(const RwaStreamPlayer* player, RwaStreamReplayAnswer* answer);
void RwaStreamPlayer_SetReplaySource(RwaStreamReplaySource source);  // nullptr = off

}  // namespace dotd::audio
