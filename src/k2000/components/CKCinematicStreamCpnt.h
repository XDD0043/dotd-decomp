// CKCinematicStreamCpnt.h - a streamed cinematic: its channels (one animated actor, or the camera, each), keys and
// events (key 0x13c6, vtable 0xb168b8, size 0x100). Original unit: CKCinematicStreamCpnt.cpp; the channel, key
// and event helpers sit in CKAnimationMarkContainer.cpp, CinematicStream.cpp, CinematicStreamFile.cpp and
// CinematicCameraTrack.cpp by address. No XXL2 class of this name; the names are ours (_maybe where inferred).
//
// The KCS run time (C2.2 pre-C2.7, package E3). A stream file LVLnnn/STREAMS/PS3<n>.KCS (n = +0xc4) is a sequence of
// chunks: an 8-byte big-endian header {body size, has data} and the body. The chunks come in segments of one chunk per
// channel (+0xc8 segments, each +0xd4 seconds long); the component keeps +0xdc segments in memory (its chunk tables,
// AllocChunkTables), reads them ahead through the one stream file (g_cinematicStreamFile, RtFS reads) and gives each
// chunk to its channel's type when it is read (DispatchChunk: the type's slot +0x00) and every frame the stream time
// (StepSegmentStateMachine: slot +0x20): type 0 an animated actor (the chunk is an RtAnimAnimation for its node), type 1
// the stream camera (a camera key track), type 2 an actor hanging from a second one. A stream started with media
// (+0xfc bit 11, CKStreamAnimCinematicBeginBloc) is synchronised with its sekens (+0xf0, the speech) and its music
// play list (+0xec); while the next segment is not read the game waits on the job queue (job 0xcb, the loading
// message) until StreamReadyJobCallback has the stream ready again.
#pragma once
#include <cstdint>

#include "k2000/components/IKComponent.h"
#include "k2000/core/Layout.h"
#include "k2000/math/CMatrix34.h"
#include "k2000/memory/Mem.h"
#include "k2000/services/CTriggerStarter.h"
#include "k2000/util/TVector.h"

class IKFile;
class IKTime;
struct RtFSFile;
struct SCinematicStreamTrackType;

class CKCinematicStreamCpnt : public IKComponent {
public:
    DOTD_CLASS_KEY(kCategoryComponent, 0x4f)
    int32_t IsKindOfClass(uint32_t key) override {  // vt+0x08 0x99b5a0
        return key == 0x13c6 || key == 0x6 || key == 0xc;
    }
    DOTD_DECLARE_FACTORIES(CKCinematicStreamCpnt)

    // A stream event (0xc bytes): its id and the triggers it starts.
    struct SEvent {
        // 0x0007dda8 CinematicStreamEvent_Construct_maybe
        void Construct() { m_id = -1; }
        // 0x0007dff8 CinematicStreamEvent_Load_maybe: the triggers (any type), then the id for
        // K_LEVEL_PLATEFORMS; returns the triggers' result.
        int32_t Load(IKFile* file, int32_t type);

        int32_t m_id;                  // +0x00
        CTriggerStarter m_tsTriggers;  // +0x04 queued when the stream time reaches the key's time (Update)
    };
    // A stream key (0xc bytes): the event with the same id, linked at the end of the Load.
    struct SKey {
        // 0x0007ddd8 CinematicStreamKey_Construct_maybe
        void Construct() {
            m_pEvent = nullptr;
            m_fTime = 0.0f;
            m_id = -1;
        }
        // 0x0007de18 CinematicStreamKey_Load_maybe: +0x04 then the id, for K_LEVEL_PLATEFORMS; returns 1.
        int32_t Load(IKFile* file, int32_t type);

        int32_t m_id;      // +0x00
        float m_fTime;     // +0x04 the stream time (seconds) its event's triggers are queued at (Update)
        SEvent* m_pEvent;  // +0x08
    };
    // A channel (0x38 bytes): one streamed actor (or the camera). Its buffer holds the channel type's data.
    struct SChannel {
        // 0x0007df20 CKCinematicStreamCpnt_FreeEntryBuffers_maybe
        void FreeBuffers();
        // 0x0007e0a0 CKCinematicStreamCpnt_AllocStreamBuffer_maybe: frees the buffer and the two matrices,
        // then a new zeroed buffer of size bytes (none for 0) and two new matrices.
        void AllocBuffer(uint32_t size);

        uint32_t m_type;             // +0x00 the channel type (index into g_cinematicStreamFile.m_aTypes)
        IKSerializable* m_pUnk04;    // +0x04 reference, read second: the actor's scene node (a CSGLeaf; type 1: the camera)
        IKSerializable* m_pUnk08;    // +0x08 reference, read first: the actor's hook (its blend slots: vt+0xbc), or 0
        IKSerializable* m_pUnk0c;    // +0x0c the node's parent kept by RestoreActor, given back by AttachActor
        CMatrix34* m_pMatrix10;      // +0x10 RwMatrixCreate: the node's modelling matrix kept at the start
        uint32_t m_unk14;            // +0x14 bit 0: the kept matrices are put back at the end (AttachActor)
        IKSerializable* m_pUnk18;    // +0x18 reference: type 2's second node (hangs from the first one's bone 0)
        IKSerializable* m_pUnk1c;    // +0x1c reference: type 2's second hook, or 0
        IKSerializable* m_pUnk20;    // +0x20 the second node's parent kept by RestoreSecondActor
        CMatrix34* m_pMatrix24;      // +0x24 RwMatrixCreate: the second node's modelling matrix
        CVector3 m_v28;              // +0x28 (one 12-byte read, each word swapped): the node's position during the stream
        void* m_pBuffer;             // +0x34 OperatorNewArray(type's size), zeroed: types 0 and 2 an AnimFloatBlock9
    };
    // A chunk table entry (0x14 bytes; 0x0007dd88 CinematicStreamChunk_Construct_maybe clears it). The first two words
    // are read from the file (the chunk header).
    struct SChunk {
        void Construct() {
            m_unk10 = 0;
            m_ui32Size = 0;
            m_ui32HasData = 0;
            m_ui32State = 0;
            m_pData = nullptr;
        }
        uint32_t m_ui32Size;     // +0x00 the body's size (header word 0)
        uint32_t m_ui32HasData;  // +0x04 header word 1: 0 = the channel has nothing in this segment
        uint32_t m_ui32State;    // +0x08 0 free, 1 played, 2 played out, 3 reading, 4 read, 5 dispatched
        void* m_pData;           // +0x0c the body (m_vChunkData) while dispatched, else 0
        uint32_t m_unk10;        // +0x10 cleared by the constructor only
    };

    // 0x00085378 CKCinematicStreamCpnt_Create (the same stores as 0x85238 CKCinematicStreamCpnt_Construct),
    // then the shared part.
    CKCinematicStreamCpnt() {
        m_vChunkBuffers = {nullptr, 1, 0};
        m_vChunkData = {nullptr, 1, 0};
        m_vSegmentStates = {nullptr, 1, 0};
        m_vChunks = {nullptr, 1, 0};
        m_vKeys = {nullptr, 1, 0};
        m_vEvents = {nullptr, 1, 0};
        m_vChannels = {nullptr, 1, 0};
        m_unkfc = 0;
        ConstructBase();
    }
    // 0x0099b840 CKCinematicStreamCpnt_Destructor (inline): the channel, event, key and chunk blocks freed (Destroy has
    // freed all but the channels' at a level exit), the segment states, the chunk data and the chunk body tables freed
    // and emptied, then the component base (vtable only).
    ~CKCinematicStreamCpnt() override {
        if (m_vChannels.m_pBlock != nullptr) Mem_FreeAligned16(m_vChannels.m_pBlock);
        if (m_vEvents.m_pBlock != nullptr) Mem_FreeAligned16(m_vEvents.m_pBlock);
        if (m_vKeys.m_pBlock != nullptr) Mem_FreeAligned16(m_vKeys.m_pBlock);
        if (m_vChunks.m_pBlock != nullptr) Mem_FreeAligned16(m_vChunks.m_pBlock);
        if (m_vSegmentStates.m_pBlock != nullptr) Mem_FreeAligned16(m_vSegmentStates.m_pBlock);
        m_vSegmentStates.m_ui32NbUsedElt = 0;
        m_vSegmentStates.m_pBlock = nullptr;
        if (m_vChunkData.m_pBlock != nullptr) Mem_FreeAligned16(m_vChunkData.m_pBlock);
        m_vChunkData.m_pBlock = nullptr;
        m_vChunkData.m_ui32NbUsedElt = 0;
        if (m_vChunkBuffers.m_pBlock != nullptr) Mem_FreeAligned16(m_vChunkBuffers.m_pBlock);
        m_vChunkBuffers.m_ui32NbUsedElt = 0;
        m_vChunkBuffers.m_pBlock = nullptr;
    }

    // vt+0x10 0x00084a58 CKCinematicStreamCpnt_Destroy: FreeChunkTables (a tail jump).
    void Destroy() override { FreeChunkTables(); }
    // vt+0x24 0x00081ed8 CKCinematicStreamCpnt_RecursiveRegistration: registered with the saving manager (vt+0x24, no
    // owner) unless the type is 4..7.
    void RecursiveRegistration(int32_t type) override;
    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x000855c0 CKCinematicStreamCpnt_Load
    // vt+0x30 0x00081a38 CKCinematicStreamCpnt_PostLoad: every channel's type state cleared and pointed at it, then the
    // type's slot +0x2c (the actor's class check); 1.
    int32_t PostLoad(int32_t type) override;

    // 0x00084ef8 CKCinematicStreamCpnt_ConstructBase_maybe: the defaults, the time step, and the channel-type
    // slots of g_cinematicStreamFile (filled again by every construction).
    void ConstructBase();
    // vt+0x50 0x00080b38 CKCinematicStreamCpnt_vf50: empty (the component's only slot after +0x4c; nothing calls it).
    virtual void Vf50() {}
    // 0x0099baa0 CKCinematicStreamCpnt_ChannelArray_Resize_maybe [inline]: m_vChannels to count channels,
    // the new ones constructed.
    void ResizeChannels(uint32_t count);
    // 0x0099bd40 CKCinematicStreamCpnt_SetTimeQuantizedToFrames_maybe [inline]: in the 60 fps mode
    // (m_unkcc == 1) m_fTime becomes a whole number of 1/60 s frames (m_ui32NbFrames counts them, plus
    // one), at least the engine's minimum step; otherwise at least that step.
    void SetTimeQuantizedToFrames(float time);
    // 0x00081db8 CKCinematicStreamCpnt_ResetChannels_maybe: for every channel (in order) its type's run-time
    // state is cleared and points at the channel, then the type's reset handler (slot +0x08: empty for all
    // three types) runs.
    void ResetChannels();
    // 0x00081ca0 CKCinematicStreamCpnt_InitChannels_maybe: the same with the types' init handler (slot +0x0c, empty).
    void InitChannels();

    // 0x00084ca8 CKCinematicStreamCpnt_StartStream_maybe: when no stream runs, the run time cleared, the start time
    // taken, the file opened; with `withMedia` (+0xfc bit 11) the sekens and the music play list are asked to start
    // paused. 1 when the file was opened.
    uint8_t StartStream(uint8_t withMedia);
    // 0x00084a60 CKCinematicStreamCpnt_OpenStreamFile_maybe: the chunk tables for the stream, the file (re)opened,
    // every channel's type slot +0x10 (keep the actor's matrices); the stream camera's far plane. 1 when opened.
    uint8_t OpenStreamFile();
    // 0x00081980 CKCinematicStreamCpnt_BuildStreamPath_maybe: "<data root>LVL%03d/STREAMS/PS3%d.KCS" (the current
    // level, the stream number +0xc4), backslashes converted. (OpenStreamFile inlines it.)
    void BuildStreamPath(char* path);
    // 0x00081400 CKCinematicStreamCpnt_CloseStream_maybe: the file closed unless it is (state 3), the ready bit cleared.
    void CloseStream();
    // 0x000829d0 CKCinematicStreamCpnt_ReopenStream_maybe: CloseStream, then the file at `path` opened (state 1).
    uint8_t ReopenStream(const char* path);
    // 0x000843c0 CKCinematicStreamCpnt_AllocChunkTables_maybe: the segment time and count, the segment states, the
    // chunk table (channels x segments entries), the chunk buffers freed and the two buffer tables emptied.
    void AllocChunkTables(float segmentTime, uint32_t channelCount, uint32_t segmentCount);
    // 0x00084860 CKCinematicStreamCpnt_FreeChunkTables_maybe (Destroy): the tables, the keys, the events and the
    // channels' buffers freed.
    void FreeChunkTables();
    // 0x00083f18 CKCinematicStreamCpnt_UpdateStream_maybe: the file read ahead (header, body, dispatch of the chunks)
    // until nothing can go on or 0.5 ms have passed on `clock` (vt+0x08), then the media synchronisation. 0 when the
    // stream is not running, timed out (+0xfc bit 5) or has ended; 1 while it goes on.
    uint8_t UpdateStream(IKTime* clock);
    // 0x00082290 CKCinematicStreamCpnt_ReadNextChunk_maybe: the chunk's body buffer (size + 0x40, aligned 0x40) and
    // its read requested (state 6). 1.
    uint8_t ReadNextChunk();
    // 0x00082ec0 CKCinematicStreamCpnt_DispatchChunk_maybe: the chunk given to its channel's type (slot +0x00), the
    // next chunk, and after a whole segment the next segment. 1.
    uint8_t DispatchChunk();
    // 0x000826d8 CKCinematicStreamCpnt_UpdateSyncedMedia_maybe: whether the sekens' voice and the music track are
    // ready; 15 s after the start whatever is not ready is stopped. Once synchronised (bit 9) 0 when the stream ended
    // (bit 14); 0 on a time-out (bit 5); else 1.
    uint8_t UpdateSyncedMedia();
    // 0x00083820 CKCinematicStreamCpnt_Update_maybe: the stream time advanced (by the frame time, or following the
    // sekens' speech), the segments stepped, the keys reached queued; 0 at the end.
    uint8_t Update(IKTime* time);
    // 0x00083268 CKCinematicStreamCpnt_StepSegmentStateMachine_maybe: the current segment's state: its chunks get the
    // time (slot +0x20) while it plays; when it is over the next one; a segment not read yet makes the game wait on
    // the job queue (job 0xcb). 1 while a segment plays.
    uint8_t StepSegmentStateMachine(float dt);
    // 0x00084308 CKCinematicStreamCpnt_StreamReadyJobCallback_maybe: the job queue's callback while waiting (the
    // stream read on); 2 s after the first segment is ready the stream goes on (+0xfc bits 10 and 16). 1 when ready.
    static uint8_t StreamReadyJobCallback(void* stream, int32_t id, void* data);
    // 0x00082a88 CKCinematicStreamCpnt_Finish_maybe: every channel's type slot +0x14 (the actor given back), the file
    // closed, the sekens and the play list stopped and the volume restored when the stream had media.
    void Finish();
    // 0x00082008 CKCinematicStreamCpnt_Stop_maybe: every channel's type slot +0x18, the chunk tables freed, the flags
    // cleared and the stream no longer running.
    void Stop();
    // 0x00081130 CKCinematicStreamCpnt_GetChannelMarkList_maybe: channel `index`'s buffer +0x20 (the AnimFloatBlock9's
    // reference), 0 out of range.
    IKSerializable* GetChannelMarkList(int32_t index);

    TVector<uint8_t*, 1> m_vChunkBuffers;   // +0x04 the chunk bodies (OperatorNewArray, size + 0x40); not loaded
    TVector<uint8_t*, 1> m_vChunkData;      // +0x10 the same, aligned to 0x40 (the dispatched chunks' data); not loaded
    int32_t m_unk1c;                        // +0x1c the read state: 0 done, 1 opening, 2 next chunk, 3 closed, 4 header
                                            //       read, 5 body to read, 6 body read, 7 to dispatch (constructor 3)
    double m_d20;                           // +0x20 the system time the job wait started (StepSegmentStateMachine)
    double m_d28;                           // +0x28 the time in the current segment
    double m_d30;                           // +0x30 the stream time
    double m_d38;                           // +0x38 +0x28 of the last Update
    double m_d40;                           // +0x40 +0x30 of the last Update
    double m_d48;                           // +0x48 the time since the stream began to play
    double m_d50;                           // +0x50 the clock's fixed time at StartStream
    double m_d58;                           // +0x58 the time since StartStream (UpdateSyncedMedia)
    uint32_t m_ui32FrameInSegment;          // +0x60 the 1/60 s frames played in the current segment (60 fps mode)
    uint32_t m_ui32Frame;                   // +0x64 the 1/60 s frames played
    uint32_t m_ui32ChunkWrite;              // +0x68 the next chunk to read (mod +0xe8)
    uint32_t m_ui32SegmentWrite;            // +0x6c the next segment to read (mod +0xdc)
    uint32_t m_ui32SegmentRead;             // +0x70 the segment playing (mod +0xdc)
    uint32_t m_ui32NextKey;                 // +0x74 the first key not reached
    uint32_t m_ui32SegmentsRead;            // +0x78 the segments read
    uint32_t m_ui32SegmentsPlayed;          // +0x7c the segments played
    TVector<uint32_t, 1> m_vSegmentStates;  // +0x80 per segment slot: 0 free, 1 playing, 2 played, 3 reading, 5 read
    TVector<SChunk, 1> m_vChunks;           // +0x8c channels x segments
    TVector<SKey, 1> m_vKeys;               // +0x98
    TVector<SEvent, 1> m_vEvents;           // +0xa4
    TVector<SChannel, 1> m_vChannels;       // +0xb0
    uint32_t m_unkbc;                       // +0xbc the size of the read in flight (the constructor sets 0)
    uint32_t m_unkc0;                       // +0xc0
    int32_t m_unkc4;                        // +0xc4 the stream file number (PS3<n>.KCS); the constructor sets -1
    int32_t m_unkc8;                        // +0xc8 the segment count of the file
    int32_t m_unkcc;                        // +0xcc 1: the time is a whole number of 1/60 s frames _maybe
    float m_unkd0;                          // +0xd0 the stream's length in seconds
    float m_fTime;                          // +0xd4 _maybe: a segment's length, quantised by the Load (SetTimeQuantizedToFrames)
    uint32_t m_ui32NbFrames;                // +0xd8 _maybe: the frame count + 1 in the 60 fps mode
    int32_t m_unkdc;                        // +0xdc the segments kept in memory (the constructor sets 2)
    uint32_t m_unke0;                       // +0xe0
    uint32_t m_unke4;                       // +0xe4
    uint32_t m_unke8;                       // +0xe8 the chunk table's size (channels x +0xdc); not loaded
    IKSerializable* m_pUnkec;               // +0xec reference: the music play list (a CKMusicPlayList)
    IKSerializable* m_pUnkf0;               // +0xf0 reference: the sekens (a CKSekens, its speech stream)
    float m_fCameraFar;                     // +0xf4 _maybe: copied into the stream camera's m_fFar (constructor 70.0)
    uint8_t m_unkf8;                        // +0xf8 read raw: given to the types' slot +0x1c (the actors taken over)
    uint8_t m_padf9[3];
    // +0xfc the run-time flags: 0 the sekens' voice ready, 1 the sekens timed out, 2 the music ready, 3 the music timed
    // out, 4 a segment read, 5 timed out (the scene is skipped), 6 started, 7 running, 8 the first segment to begin,
    // 9 synchronised, 10 ready (the job wait ends), 11 with media, 12 the speech started, 13 the music started,
    // 14 ended, 15 the speech position is not followed, 16 resynchronise after the job wait.
    uint32_t m_unkfc;
};
static_assert(CKCinematicStreamCpnt::kClassKey == 0x13c6, "key");
DOTD_ASSERT_SIZE(CKCinematicStreamCpnt::SEvent, 0xc);
DOTD_ASSERT_SIZE(CKCinematicStreamCpnt::SKey, 0xc);
DOTD_ASSERT_SIZE(CKCinematicStreamCpnt::SChannel, 0x38);
DOTD_ASSERT_SIZE(CKCinematicStreamCpnt::SChunk, 0x14);
DOTD_ASSERT_OFFSET(CKCinematicStreamCpnt::SChannel, m_pMatrix24, 0x24);
DOTD_ASSERT_OFFSET(CKCinematicStreamCpnt::SChannel, m_pBuffer, 0x34);
DOTD_ASSERT_SIZE(CKCinematicStreamCpnt, 0x100);
DOTD_ASSERT_OFFSET(CKCinematicStreamCpnt, m_unk1c, 0x1c);
DOTD_ASSERT_OFFSET(CKCinematicStreamCpnt, m_d20, 0x20);
DOTD_ASSERT_OFFSET(CKCinematicStreamCpnt, m_d58, 0x58);
DOTD_ASSERT_OFFSET(CKCinematicStreamCpnt, m_ui32FrameInSegment, 0x60);
DOTD_ASSERT_OFFSET(CKCinematicStreamCpnt, m_ui32SegmentsPlayed, 0x7c);
DOTD_ASSERT_OFFSET(CKCinematicStreamCpnt, m_vSegmentStates, 0x80);
DOTD_ASSERT_OFFSET(CKCinematicStreamCpnt, m_vChunks, 0x8c);
DOTD_ASSERT_OFFSET(CKCinematicStreamCpnt, m_vKeys, 0x98);
DOTD_ASSERT_OFFSET(CKCinematicStreamCpnt, m_vEvents, 0xa4);
DOTD_ASSERT_OFFSET(CKCinematicStreamCpnt, m_vChannels, 0xb0);
DOTD_ASSERT_OFFSET(CKCinematicStreamCpnt, m_unkc4, 0xc4);
DOTD_ASSERT_OFFSET(CKCinematicStreamCpnt, m_fTime, 0xd4);
DOTD_ASSERT_OFFSET(CKCinematicStreamCpnt, m_unke4, 0xe4);
DOTD_ASSERT_OFFSET(CKCinematicStreamCpnt, m_unke8, 0xe8);
DOTD_ASSERT_OFFSET(CKCinematicStreamCpnt, m_pUnkec, 0xec);
DOTD_ASSERT_OFFSET(CKCinematicStreamCpnt, m_fCameraFar, 0xf4);
DOTD_ASSERT_OFFSET(CKCinematicStreamCpnt, m_unkf8, 0xf8);
DOTD_ASSERT_OFFSET(CKCinematicStreamCpnt, m_unkfc, 0xfc);

// A channel type (0x70 bytes; three in g_cinematicStreamFile from +0x30, 0x00c5c708 + 0x70 * type). Its first 0x3c
// bytes are the handler slots (every constructor stores them, ConstructBase); from +0x3c the state the component sets
// before each call: the chunk, the channel and the time. Type 0 an animated actor, 1 the stream camera, 2 an actor
// hanging from a second one. The slots no code calls are kept for the record (+0x04, +0x30, +0x34, +0x38).
struct SCinematicStreamTrackType {
    uint8_t (*m_pfnBeginChunk)(SCinematicStreamTrackType* type, void* data);              // +0x00 DispatchChunk
    void (*m_pfnEndChunk)(SCinematicStreamTrackType* type);                               // +0x04 not called
    void (*m_pfnReset)(SCinematicStreamTrackType* type);                                  // +0x08 ResetChannels (empty)
    void (*m_pfnInit)(SCinematicStreamTrackType* type);                                   // +0x0c InitChannels (empty)
    uint8_t (*m_pfnKeepActor)(SCinematicStreamTrackType* type, uint32_t withMedia);       // +0x10 OpenStreamFile, Update
    void (*m_pfnGiveBackActor)(SCinematicStreamTrackType* type, uint32_t withMedia);      // +0x14 Finish
    void (*m_pfnStop)(SCinematicStreamTrackType* type, TVector<uint8_t*, 1>* chunkData,
                      uint32_t withMedia);                                                // +0x18 Stop
    void (*m_pfnTakeActor)(SCinematicStreamTrackType* type, uint32_t takeOver);           // +0x1c Update (the start)
    uint8_t (*m_pfnApplyTime)(SCinematicStreamTrackType* type);                           // +0x20 StepSegmentStateMachine
    uint32_t (*m_pfnGetBufferSize)();                                                     // +0x24 Load
    int32_t (*m_pfnLoadBuffer)(void* buffer, IKFile* file, int32_t type);                 // +0x28 Load
    void (*m_pfnPostLoad)(SCinematicStreamTrackType* type);                               // +0x2c PostLoad
    int32_t (*m_pfnSaveBuffer)(void* buffer, IKFile* file);                               // +0x30 not called
    IKSerializable* (*m_pfnResolve)(IKSerializable* object);                              // +0x34 not called
    IKSerializable* (*m_pfnResolve2)(IKSerializable* object);                             // +0x38 not called

    // The state (ResetState clears it, the caller then sets what the slot reads).
    CKCinematicStreamCpnt::SChunk* m_pChunk;      // +0x3c the chunk (DispatchChunk, StepSegmentStateMachine)
    CKCinematicStreamCpnt::SChannel* m_pChannel;  // +0x40 the channel
    float m_fSegmentTime;                         // +0x44 the component's segment length (+0xd4)
    uint32_t m_unk48;                             // +0x48 not touched
    float m_fDt;                                  // +0x4c the frame time
    double m_dStreamTime;                         // +0x50 the stream time (+0x30)
    double m_dSegmentTime;                        // +0x58 the time in the segment (+0x28)
    uint32_t m_ui32Frame;                         // +0x60 the frames played (+0x64)
    uint32_t m_ui32FrameInSegment;                // +0x64 the frames in the segment (+0x60)
    uint32_t m_ui32FrameRate;                     // +0x68 60 in the 60 fps mode, else 0 (the times are then frames)
    uint8_t m_bFirst;                             // +0x6c the segment's first frame
    uint8_t m_bPlaying;                           // +0x6d 1 while a segment plays
    uint8_t m_bStopped;                           // +0x6e not set by the component (0)
    uint8_t m_pad6f;

    // The state's clear every caller inlines (the double TOC -0x6998 is 0.0).
    void ResetState() {
        m_pChannel = nullptr;
        m_fSegmentTime = 0.0f;
        m_fDt = 0.0f;
        m_dStreamTime = 0.0;
        m_dSegmentTime = 0.0;
        m_ui32Frame = 0;
        m_ui32FrameInSegment = 0;
        m_ui32FrameRate = 0;
        m_bFirst = 0;
        m_bPlaying = 0;
        m_bStopped = 0;
        m_pChunk = nullptr;
    }
};
DOTD_ASSERT_OFFSET(SCinematicStreamTrackType, m_pfnGetBufferSize, 0x24);
DOTD_ASSERT_OFFSET(SCinematicStreamTrackType, m_pfnResolve2, 0x38);
DOTD_ASSERT_OFFSET(SCinematicStreamTrackType, m_pChunk, 0x3c);
DOTD_ASSERT_OFFSET(SCinematicStreamTrackType, m_fDt, 0x4c);
DOTD_ASSERT_OFFSET(SCinematicStreamTrackType, m_dStreamTime, 0x50);
DOTD_ASSERT_OFFSET(SCinematicStreamTrackType, m_ui32FrameRate, 0x68);
DOTD_ASSERT_OFFSET(SCinematicStreamTrackType, m_bStopped, 0x6e);
DOTD_ASSERT_SIZE(SCinematicStreamTrackType, 0x70);

// The stream file (0x30 bytes at 0x00c5c6d8, CinematicStreamFile.cpp): one for all the streams. Its reads are RtFS
// reads of 0x20000 bytes into its own buffer, copied out to the requested destination.
struct SCinematicStreamFile {
    uint8_t* m_pBuffer;      // +0x00 the read buffer (aligned 0x40)
    uint8_t* m_pBufferRaw;   // +0x04 OperatorNewArray(0x20040)
    uint32_t m_unk08;        // +0x08
    uint32_t m_unk0c;        // +0x0c
    uint8_t m_bBusy;         // +0x10 a request is being served
    uint8_t m_bDone;         // +0x11 the request is complete
    uint8_t m_bOpened;       // +0x12 the file is open (the RtFS open callback)
    uint8_t m_pad13;
    CKCinematicStreamCpnt* m_pOwner;  // +0x14 the stream the request is for
    uint8_t* m_pDestination;          // +0x18 where the request copies to
    uint32_t m_ui32Requested;         // +0x1c the request's size
    uint32_t m_ui32Copied;            // +0x20 copied so far
    uint32_t m_ui32Available;         // +0x24 bytes left in the buffer
    uint32_t m_ui32BufferOffset;      // +0x28 the next byte of the buffer
    RtFSFile* m_pFile;                // +0x2c the RtFS file, or 0
};

// 0x00c5c6d8: the stream file, then the three channel types (+0x30), the run flag and the camera (the original's
// one block of statics; RegisterCKCinematicStreamCpntClass clears the types' state and inits the file).
struct SCinematicStreamGlobals {
    SCinematicStreamFile m_file;             // +0x000
    SCinematicStreamTrackType m_aTypes[3];   // +0x030 0x00c5c708
    uint8_t m_unk180;                        // +0x180 0x00c5c858 RegisterClass's word
    uint8_t m_bRunning;                      // +0x181 0x00c5c859 a stream runs (StartStream .. Stop)
    uint8_t m_pad182[2];
    IKSerializable* m_pCamera;               // +0x184 0x00c5c85c the camera every stream's Load reads (a CKCamera)
    uint32_t m_ui32CameraCount;              // +0x188 0x00c5c860 how many non-null reads there were
};
extern SCinematicStreamGlobals g_cinematicStreamFile;

// CinematicStreamFile.cpp: the file's calls (the stream passes itself as the owner).
// 0x0007ea98 CinematicStreamFile_Init_maybe
void CinematicStreamFile_Init(SCinematicStreamFile* file);
// Platform (not in the original): the RtFS callbacks the PS3's request thread would have run by now (the open a frame,
// a read two frames after it was asked for); CKCinematicStreamCpnt::UpdateStream polls them first.
void CinematicStreamFile_PumpAsync();
// 0x0007e9b0 CinematicStreamFile_Close_maybe: the RtFS file cancelled and closed, the buffer freed, the state cleared.
void CinematicStreamFile_Close(SCinematicStreamFile* file, CKCinematicStreamCpnt* owner);
// 0x0007ead0 CinematicStreamFile_Open_maybe: closed first; when the file exists it is opened (the open completes
// through the RtFS callback) and the 0x20000-byte buffer made. 1 when RtFS gave a file.
uint8_t CinematicStreamFile_Open(SCinematicStreamFile* file, const char* path, CKCinematicStreamCpnt* owner);
// 0x0007f088 CinematicStreamFile_RequestRead_maybe: `size` bytes to `destination`: what the buffer holds is copied,
// the rest read (busy until done). 1.
uint8_t CinematicStreamFile_RequestRead(SCinematicStreamFile* file, void* destination, uint32_t size,
                                        CKCinematicStreamCpnt* owner);

// The channel types' slots (CinematicStreamFile.cpp, CinematicStream.cpp, CKAnimationMarkContainer.cpp,
// CinematicCameraTrack.cpp).
// 0x0007fcb8 CinematicStream_LoadFloatBlock9_maybe: AnimFloatBlock9_LoadByteSwapped, then 1.
int32_t CinematicStream_LoadFloatBlock9(void* buffer, IKFile* file, int32_t type);
// 0x0007f680 KStub_Return36_7f680 (CinematicStreamFile.cpp): the block's size, 36 on the PS3 (native: its
// sizeof, a reference inside).
uint32_t CinematicStream_GetFloatBlock9Size();
// 0x0099b6b8 CinematicStream_LoadFloatBlock9_Thunk [inline]
inline int32_t CinematicStream_LoadFloatBlock9_Thunk(void* buffer, IKFile* file, int32_t type) {
    return CinematicStream_LoadFloatBlock9(buffer, file, type);
}
// 0x0099b708 CinematicStream_GetFloatBlock9Size_Thunk_maybe [inline]
inline uint32_t CinematicStream_GetFloatBlock9Size_Thunk() { return CinematicStream_GetFloatBlock9Size(); }
// 0x0007e258 KStub_Return1_7e258: channel type 1's Load (no data).
int32_t CinematicStream_LoadNothing(void* buffer, IKFile* file, int32_t type);
// 0x0007e290 KStub_Return0_7e290: channel type 1's buffer size.
uint32_t CinematicStream_GetNoBufferSize();
// 0x0007e260 KStub_Return1_7e260: channel type 1's save slot (+0x30).
int32_t CinematicStream_SaveNothing(void* buffer, IKFile* file);

// Type 0 (an animated actor).
uint8_t CinematicStream_CreateAnimTrackAnimation(SCinematicStreamTrackType* type, void* data);   // 0x0007fb30 (+0x00)
void CinematicStream_DestroyAnimTrackAnimation(SCinematicStreamTrackType* type);                 // 0x0007fae0 (+0x04)
uint8_t CinematicStream_SaveActorMatrix(SCinematicStreamTrackType* type, uint32_t withMedia);    // 0x0007f540 (+0x10)
void CinematicStream_AttachActor(SCinematicStreamTrackType* type, uint32_t withMedia);           // 0x000804b0 (+0x14)
void CinematicStream_RestartActorAnimIfInList(SCinematicStreamTrackType* type, TVector<uint8_t*, 1>* chunkData,
                                              uint32_t withMedia);                               // 0x0007f860 (+0x18)
void CinematicStream_RestoreActor(SCinematicStreamTrackType* type, uint32_t takeOver);           // 0x0007f698 (+0x1c)
uint8_t CinematicStream_ApplyAnimTrackTime(SCinematicStreamTrackType* type);                     // 0x00080050 (+0x20)
void CinematicStream_IsActorSceneLeaf(SCinematicStreamTrackType* type);                          // 0x0007f4d8 (+0x2c)
IKSerializable* CinematicStream_ResolveAnimatedNode(IKSerializable* object);                     // 0x0007f3e8 (+0x34)
// Type 1 (the stream camera). Its chunk is a camera key track (PS3: 0x14-byte header, then 0x28-byte keys).
struct SCinematicCameraKey {
    float m_af[10];  // +0x00 position (3), fov, target (3), roll (IKCamera vt+0x88), the key's time, unused
};
DOTD_ASSERT_SIZE(SCinematicCameraKey, 0x28);
struct SCinematicCameraTrack {
    uint32_t m_unk00;                 // +0x00 (3 in the files)
    uint32_t m_ui32NbKeys;            // +0x04
    uint32_t m_ui32NbFrames;          // +0x08 the keys per segment the time is scaled by (lroundf)
    float m_fDuration;                // +0x0c
    SCinematicCameraKey* m_pKeys;     // +0x10 ResetTrackBufferPtr: the keys right behind the header
};
DOTD_ASSERT_SIZE(SCinematicCameraTrack, 0x14);
uint8_t CinematicStream_ResetTrackBufferPtr(SCinematicStreamTrackType* type, void* data);        // 0x0007e268 (+0x00)
void CinematicStream_FreeTrackBuffer(SCinematicStreamTrackType* type);                           // 0x0007e298 (+0x04)
void CinematicCameraTrack_Release(SCinematicStreamTrackType* type, uint32_t withMedia);          // 0x0007e878 (+0x14)
uint8_t CinematicCameraTrack_Update(SCinematicStreamTrackType* type);                            // 0x0007e318 (+0x20)
IKSerializable* CinematicStream_ResolveCamera(IKSerializable* object);                           // 0x0007e1d8 (+0x34)
// Type 2 (an actor hanging from a second one).
uint8_t CinematicStream_SaveActorMatrices(SCinematicStreamTrackType* type, uint32_t withMedia);  // 0x000807b0 (+0x10)
void CinematicStream_AttachSecondActor(SCinematicStreamTrackType* type, uint32_t withMedia);     // 0x00080608 (+0x14)
void CinematicStream_RestartActorAnimAndClearNodeFlag2000(SCinematicStreamTrackType* type,
                                                          TVector<uint8_t*, 1>* chunkData,
                                                          uint32_t withMedia);                   // 0x0007ff90 (+0x18)
void CinematicStream_RestoreSecondActor(SCinematicStreamTrackType* type, uint32_t takeOver);     // 0x0007fdf0 (+0x1c)
void CinematicStream_IsActorSceneLeaf_WithSecond(SCinematicStreamTrackType* type);              // 0x00080408 (+0x2c)
IKSerializable* CinematicStream_ResolveSceneLeaf(IKSerializable* object);                        // 0x0007fd20 (+0x38)

// DOTD (platform, not in the original): a chunk body is a PS3 memory image (big-endian, 32-bit pointer slots) that the
// PS3 uses where it was read. CinematicStream_ConvertChunkBody builds the native image of channel type `type`'s body
// (an RtAnimAnimation with its key frames and custom data for types 0 and 2, the camera key track for type 1) in a new
// OperatorNewArray block of the same shape as the original's (*nativeRaw: the block, aligned 0x40 at the result), the
// pointer slots still holding the file's indices for the type's slot +0x00 to fix up as on the PS3.
uint8_t* CinematicStream_ConvertChunkBody(uint32_t type, const uint8_t* image, uint32_t size, uint8_t** nativeRaw);
// DOTD (platform): a big-endian word of the stream file as it lies in memory, as the PS3 reads it.
inline uint32_t CinematicStream_FromBigEndian(uint32_t word) {
    const uint8_t* b = reinterpret_cast<const uint8_t*>(&word);
    return (static_cast<uint32_t>(b[0]) << 24) | (static_cast<uint32_t>(b[1]) << 16) | (static_cast<uint32_t>(b[2]) << 8) |
           static_cast<uint32_t>(b[3]);
}
