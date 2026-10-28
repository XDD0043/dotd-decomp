// CKCinematicStreamCpnt.h - a streamed cinematic: its channels (one animated actor each), keys and events
// (key 0x13c6, vtable 0xb168b8, size 0x100). Original unit: CKCinematicStreamCpnt.cpp; the channel, key
// and event helpers sit in CKAnimationMarkContainer.cpp, CinematicStream.cpp and CinematicStreamFile.cpp
// by address. No XXL2 class of this name; the names are ours (_maybe where inferred).
#pragma once
#include <cstdint>

#include "k2000/components/IKComponent.h"
#include "k2000/core/Layout.h"
#include "k2000/math/CMatrix34.h"
#include "k2000/services/CTriggerStarter.h"
#include "k2000/util/TVector.h"

class IKFile;

class CKCinematicStreamCpnt : public IKComponent {
public:
    DOTD_CLASS_KEY(kCategoryComponent, 0x4f)
    DOTD_DECLARE_FACTORIES(CKCinematicStreamCpnt)

    // A stream event (0xc bytes): its id and the triggers it starts.
    struct SEvent {
        // 0x0007dda8 CinematicStreamEvent_Construct_maybe
        void Construct() { m_id = -1; }
        // 0x0007dff8 CinematicStreamEvent_Load_maybe: the triggers (any type), then the id for
        // K_LEVEL_PLATEFORMS; returns the triggers' result.
        int32_t Load(IKFile* file, int32_t type);

        int32_t m_id;                  // +0x00
        CTriggerStarter m_tsTriggers;  // +0x04
    };
    // A stream key (0xc bytes): the event with the same id, linked at the end of the Load.
    struct SKey {
        // 0x0007ddd8 CinematicStreamKey_Construct_maybe
        void Construct() {
            m_pEvent = nullptr;
            m_unk4 = 0;
            m_id = -1;
        }
        // 0x0007de18 CinematicStreamKey_Load_maybe: +0x04 then the id, for K_LEVEL_PLATEFORMS; returns 1.
        int32_t Load(IKFile* file, int32_t type);

        int32_t m_id;      // +0x00
        uint32_t m_unk4;   // +0x04 (LVL010: a time or frame _maybe)
        SEvent* m_pEvent;  // +0x08
    };
    // A channel (0x38 bytes): one streamed actor. Its buffer holds the channel type's data.
    struct SChannel {
        // 0x0007df20 CKCinematicStreamCpnt_FreeEntryBuffers_maybe
        void FreeBuffers();
        // 0x0007e0a0 CKCinematicStreamCpnt_AllocStreamBuffer_maybe: frees the buffer and the two matrices,
        // then a new zeroed buffer of size bytes (none for 0) and two new matrices.
        void AllocBuffer(uint32_t size);

        uint32_t m_type;             // +0x00 the channel type (index into g_aCinematicStreamChannelTypes)
        IKSerializable* m_pUnk04;    // +0x04 reference, read second
        IKSerializable* m_pUnk08;    // +0x08 reference, read first
        uint32_t m_unk0c;            // +0x0c
        CMatrix34* m_pMatrix10;      // +0x10 RwMatrixCreate
        uint32_t m_unk14;            // +0x14
        IKSerializable* m_pUnk18;    // +0x18 reference
        IKSerializable* m_pUnk1c;    // +0x1c reference
        uint32_t m_unk20;            // +0x20
        CMatrix34* m_pMatrix24;      // +0x24 RwMatrixCreate
        CVector3 m_v28;              // +0x28 (one 12-byte read, each word swapped)
        void* m_pBuffer;             // +0x34 OperatorNewArray(type's size), zeroed
    };

    // 0x00085378 CKCinematicStreamCpnt_Create (the same stores as 0x85238 CKCinematicStreamCpnt_Construct),
    // then the shared part.
    CKCinematicStreamCpnt() {
        m_vUnk04 = {nullptr, 1, 0};
        m_vUnk10 = {nullptr, 1, 0};
        m_vUnk80 = {nullptr, 1, 0};
        m_vUnk8c = {nullptr, 1, 0};
        m_vKeys = {nullptr, 1, 0};
        m_vEvents = {nullptr, 1, 0};
        m_vChannels = {nullptr, 1, 0};
        m_unkfc = 0;
        ConstructBase();
    }
    ~CKCinematicStreamCpnt() override {}

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x000855c0 CKCinematicStreamCpnt_Load

    // 0x00084ef8 CKCinematicStreamCpnt_ConstructBase_maybe: the defaults, the time step, and the channel-type
    // table g_aCinematicStreamChannelTypes (filled again by every construction).
    void ConstructBase();
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

    TVector<uint32_t, 1> m_vUnk04;     // +0x04 not loaded
    TVector<uint32_t, 1> m_vUnk10;     // +0x10 not loaded
    int32_t m_unk1c;                   // +0x1c the constructor sets 3
    uint32_t m_unk20[24];              // +0x20..+0x7c the constructor clears them (+0x50 a float)
    TVector<uint32_t, 1> m_vUnk80;     // +0x80 not loaded
    TVector<uint32_t, 1> m_vUnk8c;     // +0x8c not loaded
    TVector<SKey, 1> m_vKeys;          // +0x98
    TVector<SEvent, 1> m_vEvents;      // +0xa4
    TVector<SChannel, 1> m_vChannels;  // +0xb0
    uint32_t m_unkbc;                  // +0xbc the constructor sets 0
    uint32_t m_unkc0;                  // +0xc0
    int32_t m_unkc4;                   // +0xc4 the constructor sets -1
    int32_t m_unkc8;                   // +0xc8
    int32_t m_unkcc;                   // +0xcc 1: the time is a whole number of 1/60 s frames _maybe
    float m_unkd0;                     // +0xd0
    float m_fTime;                     // +0xd4 _maybe: quantised by the Load (SetTimeQuantizedToFrames)
    uint32_t m_ui32NbFrames;           // +0xd8 _maybe: the frame count + 1 in the 60 fps mode
    int32_t m_unkdc;                   // +0xdc the constructor sets 2
    uint32_t m_unke0;                  // +0xe0
    uint32_t m_unke4;                  // +0xe4
    int32_t m_unke8;                   // +0xe8 not loaded
    IKSerializable* m_pUnkec;          // +0xec reference
    IKSerializable* m_pUnkf0;          // +0xf0 reference
    float m_fCameraFar;                // +0xf4 _maybe: copied into the stream camera's m_fFar (constructor 70.0)
    uint8_t m_unkf8;                   // +0xf8 read raw
    uint8_t m_padf9[3];
    uint32_t m_unkfc;                  // +0xfc
};
static_assert(CKCinematicStreamCpnt::kClassKey == 0x13c6, "key");
DOTD_ASSERT_SIZE(CKCinematicStreamCpnt::SEvent, 0xc);
DOTD_ASSERT_SIZE(CKCinematicStreamCpnt::SKey, 0xc);
DOTD_ASSERT_SIZE(CKCinematicStreamCpnt::SChannel, 0x38);
DOTD_ASSERT_OFFSET(CKCinematicStreamCpnt::SChannel, m_pMatrix24, 0x24);
DOTD_ASSERT_OFFSET(CKCinematicStreamCpnt::SChannel, m_pBuffer, 0x34);
DOTD_ASSERT_SIZE(CKCinematicStreamCpnt, 0x100);
DOTD_ASSERT_OFFSET(CKCinematicStreamCpnt, m_unk1c, 0x1c);
DOTD_ASSERT_OFFSET(CKCinematicStreamCpnt, m_vKeys, 0x98);
DOTD_ASSERT_OFFSET(CKCinematicStreamCpnt, m_vEvents, 0xa4);
DOTD_ASSERT_OFFSET(CKCinematicStreamCpnt, m_vChannels, 0xb0);
DOTD_ASSERT_OFFSET(CKCinematicStreamCpnt, m_unkc4, 0xc4);
DOTD_ASSERT_OFFSET(CKCinematicStreamCpnt, m_fTime, 0xd4);
DOTD_ASSERT_OFFSET(CKCinematicStreamCpnt, m_unke4, 0xe4);
DOTD_ASSERT_OFFSET(CKCinematicStreamCpnt, m_pUnkec, 0xec);
DOTD_ASSERT_OFFSET(CKCinematicStreamCpnt, m_fCameraFar, 0xf4);
DOTD_ASSERT_OFFSET(CKCinematicStreamCpnt, m_unkf8, 0xf8);

// 0x00c5c85c / 0x00c5c860: the camera every stream's Load reads (a CKCamera in LVL010) and how many
// non-null reads there were. Only CKCinematicStreamCpnt_Load uses them.
extern IKSerializable* g_pCinematicStreamCamera;
extern uint32_t g_ui32CinematicStreamCameraCount;

// The channel types (0x00c5c6d8: 0x70 bytes per type, three types; every constructor stores the function
// pointers). Only the two slots the Load calls are ported: +0x54 the buffer size, +0x58 the buffer's Load.
// STUB(C2.2): the other slots (+0x30.., the animation track handlers) with the stream run time.
struct SCinematicStreamChannelType {
    uint32_t (*m_pfnGetBufferSize)();                             // +0x54
    int32_t (*m_pfnLoadBuffer)(void* buffer, IKFile* file, int32_t type);  // +0x58
};
extern SCinematicStreamChannelType g_aCinematicStreamChannelTypes[3];
// The run-time state each channel type object keeps from its +0x3c on (the three objects stand 0x70 bytes
// apart from 0x00c5c708; their first 0x3c bytes are the handler slots, +0x08 the empty reset handler of all
// three types). ResetChannels clears it and records the channel being reset in +0x40.
struct SCinematicStreamChannelState {
    uint32_t m_unk3c;            // +0x3c
    CKCinematicStreamCpnt::SChannel* m_pChannel;  // +0x40 the channel last reset
    uint32_t m_unk44;            // +0x44
    uint32_t m_unk48;            // +0x48 not touched by ResetChannels
    uint32_t m_unk4c;            // +0x4c
    uint32_t m_unk50[2];         // +0x50 a double, cleared
    uint32_t m_unk58[2];         // +0x58 a double, cleared
    uint32_t m_unk60;            // +0x60
    uint32_t m_unk64;            // +0x64
    uint32_t m_unk68;            // +0x68
    uint8_t m_unk6c;             // +0x6c
    uint8_t m_unk6d;             // +0x6d
    uint8_t m_unk6e;             // +0x6e
    uint8_t m_pad6f;
};
DOTD_ASSERT_SIZE(SCinematicStreamChannelState, 0x34);
extern SCinematicStreamChannelState g_aCinematicStreamChannelState[3];  // 0x00c5c744 + 0x70 * type

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
