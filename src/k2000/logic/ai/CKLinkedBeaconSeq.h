// CKLinkedBeaconSeq.h - (key 0x4a0c, vtable 0xb26e68, size 0x1c). Original unit: CKLinkedBeaconSeq.cpp.
// DotD only; the names are ours, the reference types from the files (struct draft).
#pragma once
#include <cstdint>

#include "k2000/core/IKSerializable.h"
#include "k2000/core/Layout.h"

class CKLinkedBeaconSeq : public IKSerializable {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x128)
    int32_t IsKindOfClass(uint32_t key) override { return key == 0x4a0c || key == 0xc; }  // vt+0x08 0x9c3d20
    DOTD_DECLARE_FACTORIES(CKLinkedBeaconSeq)

    // An animation step of the sequence (8 bytes, OperatorNewArray, no constructor; the animation itself is word
    // `step` of the dictionary +0x04). CKHkLinkedBeacon_UpdateCurrentStage_maybe moves on when the step's animation
    // ends (m_unk0 0) or after m_fDuration seconds (m_unk0 nonzero, a positive duration).
    struct Entry {
        uint8_t m_unk0;       // +0x00 timed step (0: until the animation ends)
        uint8_t m_pad1[3];
        float m_fDuration;    // +0x04 seconds (lfs)
    };

    CKLinkedBeaconSeq() {}  // 0x00450e40 CKLinkedBeaconSeq_Construct: only the vtable
    ~CKLinkedBeaconSeq() override {}

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x00451188 CKLinkedBeaconSeq_Load
    // vt+0x24 0x00451070 CKLinkedBeaconSeq_RecursiveRegistration: the dictionary's (when set) and the launcher's (not
    // tested) RecursiveRegistration.
    void RecursiveRegistration(int32_t type) override;
    // vt+0x10 0x00451110 CKLinkedBeaconSeq_Destroy: the dictionary destroyed (vt+0x10, when set) and the entries deleted
    // (the pointer kept, as in the original).
    void Destroy() override;

    IKSerializable* m_pAnimDictionary;  // +0x04 CAnimationDictionary in the files
    IKSerializable* m_pLauncherCpnt;    // +0x08 CKSekensLauncherCpnt in the files
    int32_t m_nbEntries;                // +0x0c
    Entry* m_aEntries;                  // +0x10 new[] (m_nbEntries)
    uint8_t m_unk14;                    // +0x14 the stage loops (its steps and sekens restart; the time-out applies)
    uint8_t m_unk15;                    // +0x15 the steps follow the sekens' current line
    uint8_t m_unk16;                    // +0x16 the steps start without waiting for the sekens to be current
    uint8_t m_pad17;
    float m_fTimeOut;                   // +0x18 a looping stage ends after it (seconds; 0 none)
};
DOTD_ASSERT_SIZE(CKLinkedBeaconSeq, 0x1c);
DOTD_ASSERT_OFFSET(CKLinkedBeaconSeq, m_pAnimDictionary, 0x04);
DOTD_ASSERT_OFFSET(CKLinkedBeaconSeq, m_pLauncherCpnt, 0x08);
DOTD_ASSERT_OFFSET(CKLinkedBeaconSeq, m_nbEntries, 0x0c);
DOTD_ASSERT_OFFSET(CKLinkedBeaconSeq, m_aEntries, 0x10);
DOTD_ASSERT_OFFSET(CKLinkedBeaconSeq, m_unk14, 0x14);
DOTD_ASSERT_OFFSET(CKLinkedBeaconSeq, m_unk16, 0x16);
DOTD_ASSERT_OFFSET(CKLinkedBeaconSeq, m_fTimeOut, 0x18);
