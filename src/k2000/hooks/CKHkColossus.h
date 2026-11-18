// CKHkColossus.h - the colossus boss hook (key 0x2a42, vtable 0xb27460, size 0x58). Original unit: CKHkColossus.cpp
// (0x46bd08-0x46cbe8); its Delete 0x46bc70 sits in CKColossusSequenceManager.cpp. No XXL2 class. No level file holds
// one (work/level-class-keys.json); C2.8 port-rest R03 ported it from the code. Field names are placeholders.
//
// The hook owns the colossus' attack sequencer (+0x20, a CKColossusSequenceManager: PostLoad makes the hook its owner,
// Start resets it, Update runs it, Stop stops its sequence), the attack sequences (+0x24, each told its owner by the
// Load) and the hot spot records (+0x30, 16-byte blocks the Load allocates: the sequences' elements look them up by
// index, GetHotSpotRecordByIndex).
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/math/CMatrix34.h"
#include "k2000/misc/CKHkActorBase.h"
#include "k2000/util/TVector.h"

class CKHkColossus : public CKHkActorBase {
public:
    DOTD_CLASS_KEY(kCategoryHook, 0xa9)
    int32_t IsKindOfClass(uint32_t key) override {  // vt+0x08 0x9c4190
        return key == 0x2a42 || key == 0xd82 || key == 0x2 || key == 0x2fe || key == 0x3fe || key == 0xc;
    }
    DOTD_DECLARE_FACTORIES(CKHkColossus)

    // A hot spot record (0x10 bytes, operator new in the Load, delete in Destroy): read as a word (+0x04, swapped) and
    // then three references (+0x00, +0x08, +0x0c).
    struct HotSpotRecord {
        IKSerializable* m_pUnk0;  // +0x00 reference (read second)
        uint32_t m_ui32Unk4;      // +0x04 read first
        IKSerializable* m_pUnk8;  // +0x08 reference
        IKSerializable* m_pUnkC;  // +0x0c reference
    };

    // 0x0046c528 CKHkColossus_Create (the dead 0x46bf08 / 0x46bf78 _Construct copies): the actor base, both vectors
    // empty with a capacity of 1 (blocks null).
    CKHkColossus();
    // 0x0046c488 CKHkColossus_Destructor (= 0x46c088 _BaseDestructor, 0x46c3d8 _DeletingDestructor): both vector blocks
    // freed (+0x30, then +0x24), then the actor base's.
    ~CKHkColossus() override;

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x0046c698 CKHkColossus_Load
    // vt+0x30 0x0046be78 CKHkColossus_PostLoad: the actor base's, then the hook made the sequencer's owner (its +0x04).
    int32_t PostLoad(int32_t type) override;
    // vt+0x10 0x0046c128 CKHkColossus_Destroy: the actor base's (vt+0xc0, empty), every hot spot record deleted, none left.
    void Destroy() override;
    // vt+0x24 0x0046bee0 CKHkColossus_RecursiveRegistration: the actor base's (IKHook's), inherited.
    // vt+0x70 / +0x78 0x46be10 / 0x46bde8 CKHkColossus_Pause / Resume: the actor base's (0x3f6e58 / 0x3f6e60), inherited.
    // vt+0x50 0x0046c350 CKHkColossus_Start: the actor base's (empty), the sequencer reset, the node's modelling `at`
    // axis kept (+0x3c), +0x48 / +0x4c cleared and +0x54 = +0x50.
    void Start() override;
    // vt+0x68 0x0046be38 CKHkColossus_Stop: the actor base's, then the sequencer's current sequence stopped.
    void Stop() override;
    // vt+0x7c 0x0046bd90 CKHkColossus_Update: the actor base's (empty), then the sequencer's update with the clock.
    void Update(IKTime* clock) override;

    // 0x0046c320 CKHkColossus_GetHotSpotRecordByIndex_maybe: record `index` (unsigned), null past the end.
    HotSpotRecord* GetHotSpotRecordByIndex(uint32_t index) const;

    IKSerializable* m_pUnk20;                     // +0x20 reference: the CKColossusSequenceManager
    TVector<IKSerializable*, 1> m_vUnk24;         // +0x24 the attack sequences (references; the Load sets their owner)
    TVector<HotSpotRecord*, 1> m_vUnk30;          // +0x30 the hot spot records
    CVector3 m_vUnk3C;                            // +0x3c Start: the node's modelling `at` axis
    float m_unk48;                                // +0x48 Start: 0 (a float: KBase7CCC_vf68, the yaw)
    float m_unk4C;                                // +0x4c Start: 0 (a float: KBase7CCC_vf68, the turn speed)
    uint32_t m_unk50;                             // +0x50 read last (swapped)
    uint32_t m_unk54;                             // +0x54 Start: +0x50
};
DOTD_ASSERT_SIZE(CKHkColossus, 0x58);
DOTD_ASSERT_OFFSET(CKHkColossus, m_pUnk20, 0x20);
DOTD_ASSERT_OFFSET(CKHkColossus, m_vUnk24, 0x24);
DOTD_ASSERT_OFFSET(CKHkColossus, m_vUnk30, 0x30);
DOTD_ASSERT_OFFSET(CKHkColossus, m_vUnk3C, 0x3c);
DOTD_ASSERT_OFFSET(CKHkColossus, m_unk48, 0x48);
DOTD_ASSERT_OFFSET(CKHkColossus, m_unk50, 0x50);
DOTD_ASSERT_OFFSET(CKHkColossus, m_unk54, 0x54);
