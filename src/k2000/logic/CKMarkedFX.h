// CKMarkedFX.h - effects fired on animation marks (key 0xab4c, vtable 0xb301e0, size 0x2c). Original unit:
// CKMarkedFX.cpp (0x5ceb68-0x5d1700). Derived straight from IKSerializable. Not in XXL2; names ours.
//
// Two lists of heap records, each a TVector growing by one: FX entries (+0x10), each with its mark records,
// and channel tables (+0x1c), each with its channel entries. The record layouts come from their Load
// helpers (0x5d0a20, 0x5d0bb8, 0x5d0da8, 0x5d0f28); no constructors are called for them.
#pragma once
#include <cstdint>

#include "k2000/core/IKSerializable.h"
#include "k2000/core/Layout.h"
#include "k2000/util/TVector.h"

class IKFx;
class IKTime;
struct RtAnimAnimation;

class CKMarkedFX : public IKSerializable {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x2ad)
    int32_t IsKindOfClass(uint32_t key) override { return key == 0xab4c || key == 0xc; }  // vt+0x08 0x9cd6c8
    DOTD_DECLARE_FACTORIES(CKMarkedFX)

    // operator new(0x10), not initialised.
    struct MarkRecord {
        uint32_t m_unk00;          // +0x00
        uint32_t m_unk04;          // +0x04 read last
        IKSerializable* m_unk08;   // +0x08
        IKSerializable* m_unk0c;   // +0x0c
        // 0x005d0a20 CKMarkedFX_LoadFxMarkRecord_maybe (the owner is passed too and not used)
        void Load(IKFile* file, int32_t type);
    };
    // operator new(0x10); the caller sets +0x08 = 1, +0x04 = 0, +0x0c = 0 before Load.
    struct FxEntry {
        IKSerializable* m_unk00;              // +0x00
        TVector<MarkRecord*, 1> m_marks;      // +0x04
        // 0x005d0bb8 CKMarkedFX_LoadFxEntry_maybe
        void Load(IKFile* file, int32_t type, CKMarkedFX* owner);
    };
    // operator new(0x14), not initialised.
    struct ChannelEntry {
        IKFx* m_unk00;             // +0x00 not read: the effect started for the channel's value (PostLoad: 0)
        uint32_t m_unk04;          // +0x04 the mark channel
        uint32_t m_unk08;          // +0x08 read after +0x0c: the mark value
        IKSerializable* m_unk0c;   // +0x0c the hot spot the effect follows (CKParticlesEffectFxData +0x14)
        uint8_t m_unk10;           // +0x10 stopped when the animation changes
        uint8_t m_pad11[3];
        // 0x005d0da8 CKMarkedFX_LoadChannelEntry_maybe (the owner is passed too and not used)
        void Load(IKFile* file, int32_t type);
    };
    // operator new(0x10); the caller sets +0x08 = 1, +0x04 = 0, +0x0c = 0 before Load.
    struct ChannelTable {
        IKSerializable* m_unk00;              // +0x00
        TVector<ChannelEntry*, 1> m_entries;  // +0x04
        // 0x005d0f28 CKMarkedFX_LoadChannelTable_maybe
        void Load(IKFile* file, int32_t type, CKMarkedFX* owner);
    };

    CKMarkedFX();  // inlined in 0x005cf5a8 CKMarkedFX_Create (also 0x5cebb8)
    // 0x005d1618 CKMarkedFX_Destructor (0x005d1568 DeletingDestructor, 0x005d16b0 Destructor_2: the same): the two list
    // blocks freed (the records are Destroy's), their counts cleared.
    ~CKMarkedFX() override;
    // vt+0x10 0x005cf300 CKMarkedFX_Destroy: every FX entry's mark records deleted, its block freed, the entry
    // deleted; the same for the channel tables and their entries (the two lists keep their counts).
    void Destroy() override;

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x005d1118 CKMarkedFX_Load
    // vt+0x30 0x005cf268 CKMarkedFX_PostLoad: for type 0 every channel entry's effect cleared; 1.
    int32_t PostLoad(int32_t type) override;

    // 0x005cf1c0 CKMarkedFX_ResetChannels_maybe: every channel entry's effect forgotten (not stopped), no animation.
    void ResetChannels();
    // 0x005cfb70 CKMarkedFX_StopAllChannelNodes_2_maybe: every started channel effect stopped (vt+0x58, the owner
    // +0x08) and forgotten.
    void StopAllChannelNodes2();
    // 0x005cfcb0 CKMarkedFX_StopAllChannelNodesAndReset_maybe: the same, then no animation (+0x28).
    void StopAllChannelNodesAndReset();
    // 0x005ced80 CKMarkedFX_StopAllChannelNodes_maybe: the same loop as StopAllChannelNodes_2 (its own copy; the sequence
    // manager's end of a sequence calls this one).
    void StopAllChannelNodes();
    // 0x005ceec0 CKMarkedFX_StopFlaggedChannelNodes_maybe: the started channel effects of the entries flagged +0x10 (the
    // ones stopped when the animation changes) stopped (vt+0x58, the owner +0x08) and forgotten.
    void StopFlaggedChannelNodes();
    // 0x005d0178 CKMarkedFX_FireChannel_maybe: every FX entry's mark records of `channel` and `value` with a hot spot
    // fire the entry's explosion (a pooled effect of its data) at the hot spot.
    void FireChannel(uint32_t channel, uint32_t value);
    // 0x005d0558 CKMarkedFX_FireChannelIfMarkCrossed_maybe: with an animation, its mark `channel` crossed between *t0 and
    // *t1 (the mark's vt+0x1c) fires the channel with that value. No caller (UpdateFromAnimMarks inlines it).
    void FireChannelIfMarkCrossed(uint32_t channel, RtAnimAnimation* animation, const float* t0, const float* t1);
    // 0x005cf608 CKMarkedFX_UpdateChannel_maybe: the held channel effects of mark `channel` between the times t0
    // and t1: started while the mark holds a value, stopped when it goes back to 0.
    void UpdateChannel(uint32_t channel, RtAnimAnimation* animation, const float* t0, const float* t1);
    // 0x005d0640 CKMarkedFX_UpdateFromAnimMarks: the animation of the node (+0x04; a hero's +0x0c when the node has no
    // own controller), the channel effects stopped when it changed, then the integer marks ("MarkI_*" of the 37 mark
    // names 0x00b01198) crossed since the last frame fire their channel and update their held effects.
    void UpdateFromAnimMarks(IKTime* clock);

    IKSerializable* m_unk04;                  // +0x04 an object reference (read first): the animated node
    IKSerializable* m_unk08;                  // +0x08 an object reference: the effects' owner
    IKSerializable* m_unk0c;                  // +0x0c an object reference (read last): a hero (key 0x3642) or other
    TVector<FxEntry*, 1> m_fxEntries;         // +0x10
    TVector<ChannelTable*, 1> m_channels;     // +0x1c
    RtAnimAnimation* m_unk28;                 // +0x28 not set by the constructor or Load: the last animation seen
};
static_assert(CKMarkedFX::kClassKey == 0xab4c, "key");

// The integer marks of the 37 animation mark names (0x00b01198 here, the same names at 0x00b012c0 for CKMarkedTrigger):
// the strcmp (0x0095f1a0) of a name's first five characters with "MarkI" the mark loops make.
bool IsIntegerAnimMark(uint32_t id);
DOTD_ASSERT_SIZE(CKMarkedFX::MarkRecord, 0x10);
DOTD_ASSERT_SIZE(CKMarkedFX::FxEntry, 0x10);
DOTD_ASSERT_SIZE(CKMarkedFX::ChannelEntry, 0x14);
DOTD_ASSERT_SIZE(CKMarkedFX::ChannelTable, 0x10);
DOTD_ASSERT_SIZE(CKMarkedFX, 0x2c);
DOTD_ASSERT_OFFSET(CKMarkedFX, m_unk04, 0x04);
DOTD_ASSERT_OFFSET(CKMarkedFX, m_unk0c, 0x0c);
DOTD_ASSERT_OFFSET(CKMarkedFX, m_fxEntries, 0x10);
DOTD_ASSERT_OFFSET(CKMarkedFX, m_channels, 0x1c);
