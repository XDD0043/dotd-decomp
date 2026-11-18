// CKAnimatedFxCollection.h - a group of animated effects (key 0xa08c, vtable 0xb30128, size 0x40). Original
// unit: CKAnimatedFxCollection.cpp (0x5cc298-0x5cdb00). Derived straight from IKSerializable. Not in XXL2;
// names ours. The three lists are the engine's TVector growing by one element.
#pragma once
#include <cstdint>

#include "k2000/core/IKSerializable.h"
#include "k2000/core/Layout.h"
#include "k2000/memory/Mem.h"
#include "k2000/util/TVector.h"
#include "k2000/logic/fx/CKAnimatedFx.h"

class CKAnimatedFxCollection : public IKSerializable {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x282)
    int32_t IsKindOfClass(uint32_t key) override { return key == 0xa08c || key == 0xc; }  // vt+0x08 0x9cd658
    DOTD_DECLARE_FACTORIES(CKAnimatedFxCollection)

    // Four object references read one after the other (16 bytes on the PS3).
    struct Entry {
        IKSerializable* m_unk00;
        IKSerializable* m_unk04;
        IKSerializable* m_unk08;
        IKSerializable* m_unk0c;
    };

    CKAnimatedFxCollection();  // inlined in 0x005ccb68 CKAnimatedFxCollection_Create (also 0x5cc2e8)
    // 0x005cd2d0 CKAnimatedFxCollection_Destructor: the three blocks freed (the active bytes, the entries, the references).
    ~CKAnimatedFxCollection() override {
        if (m_abActive.m_pBlock != nullptr) Mem_FreeAligned16(m_abActive.m_pBlock);
        m_abActive.m_ui32NbUsedElt = 0;
        m_abActive.m_pBlock = nullptr;
        if (m_unk18.m_pBlock != nullptr) Mem_FreeAligned16(m_unk18.m_pBlock);
        m_unk18.m_ui32NbUsedElt = 0;
        m_unk18.m_pBlock = nullptr;
        if (m_unk0c.m_pBlock != nullptr) Mem_FreeAligned16(m_unk0c.m_pBlock);
        m_unk0c.m_ui32NbUsedElt = 0;
        m_unk0c.m_pBlock = nullptr;
    }

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x005cd510 CKAnimatedFxCollection_Load
    // vt+0x30 0x005ccf58 CKAnimatedFxCollection_PostLoad: the active bytes (one per effect, 0), not playing, no owner,
    // the own rigs' nodes hidden.
    int32_t PostLoad(int32_t type) override;

    // 0x005cc528 CKAnimatedFxCollection_Play: every effect not playing plays on its rig (the own rigs with +0x24, else
    // `rigs`); 1 when one plays. Not while the collection plays.
    int32_t Play(CSGLeaf* owner, SAnimatedFxRig* rigs, CSGHotSpot* attach);
    // 0x005cd0a8 CKAnimatedFxCollection_PlayWithOwnRigs_maybe: Play on the own rigs (+0x24 only).
    int32_t PlayWithOwnRigs(CSGLeaf* owner, CSGHotSpot* attach);
    // 0x005cc990 CKAnimatedFxCollection_Stop
    void Stop();
    // 0x005cc7f0 CKAnimatedFxCollection_SetOrientation_maybe: while playing, every active effect oriented along `at` /
    // `up` (CKAnimatedFx_SetOrientation_maybe).
    void SetOrientation(const CVector3* at, const CVector3* up);
    // 0x005cc8c8 CKAnimatedFxCollection_SetPosition: while playing, every active effect placed at `position`
    // (CKAnimatedFx_SetPosition).
    void SetPosition(const CVector3* position);
    // 0x005cccb0 CKAnimatedFxCollection_Update_maybe: the playing effects advance (CKAnimatedFx::Update); when none plays
    // any more and +0x04 is set, every effect plays again. 1 while playing.
    uint8_t Update(float dt);
    // The rig of effect `i` (inlined in Play / PlayWithOwnRigs / Update).
    SAnimatedFxRig* RigOf(uint32_t i);

    uint8_t m_unk04;                    // +0x04
    uint8_t m_pad05[3];
    uint32_t m_unk08;                   // +0x08 the number of entries in +0x18 (when +0x24 is set)
    TVector<IKSerializable*, 1> m_unk0c;  // +0x0c object references (LVL010: CKAnimatedFx)
    TVector<Entry, 1> m_unk18;          // +0x18
    uint8_t m_unk24;                    // +0x24 non-zero: the +0x18 entries follow in the file (the own rigs)
    uint8_t m_unk25;
    uint8_t m_bPlaying;                 // +0x26 not read: PostLoad 0; one of the effects plays
    uint8_t m_unk27;
    SAnimatedFxRig* m_pRigs;            // +0x28 Load (type 0) sets 0; the rigs Play got (one per effect)
    TVector<uint8_t, 1> m_abActive;     // +0x2c not read by Load: PostLoad, one byte per effect (it plays)
    CSGLeaf* m_pOwner;                  // +0x38 not set: PostLoad 0; the node the rigs hang under (Play)
    CSGHotSpot* m_pAttach;              // +0x3c not set: Play's hot spot
};
static_assert(CKAnimatedFxCollection::kClassKey == 0xa08c, "key");
DOTD_ASSERT_SIZE(CKAnimatedFxCollection::Entry, 0x10);
DOTD_ASSERT_SIZE(CKAnimatedFxCollection, 0x40);
DOTD_ASSERT_OFFSET(CKAnimatedFxCollection, m_unk04, 0x04);
DOTD_ASSERT_OFFSET(CKAnimatedFxCollection, m_unk08, 0x08);
DOTD_ASSERT_OFFSET(CKAnimatedFxCollection, m_unk0c, 0x0c);
DOTD_ASSERT_OFFSET(CKAnimatedFxCollection, m_unk18, 0x18);
DOTD_ASSERT_OFFSET(CKAnimatedFxCollection, m_unk24, 0x24);
DOTD_ASSERT_OFFSET(CKAnimatedFxCollection, m_pRigs, 0x28);
DOTD_ASSERT_OFFSET(CKAnimatedFxCollection, m_bPlaying, 0x26);
DOTD_ASSERT_OFFSET(CKAnimatedFxCollection, m_pOwner, 0x38);
DOTD_ASSERT_OFFSET(CKAnimatedFxCollection, m_abActive, 0x2c);
