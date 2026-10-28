// SpeechStreamModel.h - the speech stream of a sekens as a clock, until the audio engine has a decoder.
//
// PORT: the original plays a sekens' speech through a SoundStream (RWA stream player): CKStreamObject_Play assigns a
// stream of the "Speech" type, which prepares and plays one item of LVLnnn/SPEECH/<voice>_PS30.RWS; the sekens' line
// logic (CKSekens::UpdateCurrentLine) asks the stream for the item and the playback position and whether it has
// finished. Here the clock the stream would run decides the line logic (so the lines end when they do on the PS3),
// and the item, decoded from ATRAC3 (platform/audio/rws.h), plays on a mixer voice from the clock's first sample.
// Speech volume and 3D placement are not applied (gain 1).
//
// Position = the game's fixed time since the stream started, which is kStartSeconds after Play; the stream has
// finished kFinishSeconds after the item's length. The item's length is read from the .RWS header (the usable bytes
// of the item's segment, 152-byte frames of 1024 samples at 48 kHz). The two constants stand for what the RWA player
// takes to prepare and to report the end; they are fitted to the RPCS3 capture of the opening cutscene (see the .cpp).
#pragma once
#include <cstdint>

class CKStreamObject;

namespace speech_model {

// CKStreamObject_Play on a speech stream: the stream gets its player (the original's stream +0x0c) at once.
void Play(const CKStreamObject* stream);
// CKStreamObject_Stop on it: the player is given back.
void Stop(const CKStreamObject* stream);
// The original's "stream +0x0c is not null".
bool HasPlayer(const CKStreamObject* stream);
// SoundStream_GetPlaybackItemAndPosition_maybe through CKStreamObject_GetPlaybackPosition_maybe: item 0xffffffff and
// position 0 without a player, item 0xff while it prepares, then the item (stream +0x1c) and the seconds played.
void GetPlayback(const CKStreamObject* stream, int32_t* item, float* position);
// FUN_0011a538: 1 without a player, else whether the item has been played to its end.
bool IsFinished(const CKStreamObject* stream);

// The length in seconds of an item of the speech file of the level and voice language in use (0 when unknown).
float ItemSeconds(int32_t item);

// Replays (debug, off by default; step 1): the stream player's answers as the original's were in a recorded frame
// (its third real-time input after the clock and the pad). A source that answers (returns true) for a stream decides
// HasPlayer and IsFinished; GetPlayback gives no item and position 0 while `positionStarted` is false, then the model's.
struct ReplayAnswer {
    bool hasPlayer;
    bool finished;
    bool positionStarted;
};
using ReplaySource = bool (*)(const CKStreamObject* stream, ReplayAnswer* answer);
void SetReplaySource(ReplaySource source);  // nullptr = off

}  // namespace speech_model
