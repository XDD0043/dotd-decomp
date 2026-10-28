// CKLinkedBeaconSeq.h - (key 0x4a0c, vtable 0xb26e68, size 0x1c). Original unit: CKLinkedBeaconSeq.cpp.
// DotD only; the names are ours, the reference types from the files (struct draft).
#pragma once
#include <cstdint>

#include "k2000/core/IKSerializable.h"
#include "k2000/core/Layout.h"

class CKLinkedBeaconSeq : public IKSerializable {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x128)
    DOTD_DECLARE_FACTORIES(CKLinkedBeaconSeq)

    struct Entry {  // 8 bytes (OperatorNewArray, no constructor)
        uint8_t m_unk0;
        uint8_t m_pad1[3];
        uint32_t m_unk4;
    };

    CKLinkedBeaconSeq() {}  // 0x00450e40 CKLinkedBeaconSeq_Construct: only the vtable
    ~CKLinkedBeaconSeq() override {}

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x00451188 CKLinkedBeaconSeq_Load

    IKSerializable* m_pAnimDictionary;  // +0x04 CAnimationDictionary in the files
    IKSerializable* m_pLauncherCpnt;    // +0x08 CKSekensLauncherCpnt in the files
    int32_t m_nbEntries;                // +0x0c
    Entry* m_aEntries;                  // +0x10 new[] (m_nbEntries)
    uint8_t m_unk14;                    // +0x14
    uint8_t m_unk15;                    // +0x15
    uint8_t m_unk16;                    // +0x16
    uint8_t m_pad17;
    uint32_t m_unk18;                   // +0x18
};
DOTD_ASSERT_SIZE(CKLinkedBeaconSeq, 0x1c);
DOTD_ASSERT_OFFSET(CKLinkedBeaconSeq, m_pAnimDictionary, 0x04);
DOTD_ASSERT_OFFSET(CKLinkedBeaconSeq, m_pLauncherCpnt, 0x08);
DOTD_ASSERT_OFFSET(CKLinkedBeaconSeq, m_nbEntries, 0x0c);
DOTD_ASSERT_OFFSET(CKLinkedBeaconSeq, m_aEntries, 0x10);
DOTD_ASSERT_OFFSET(CKLinkedBeaconSeq, m_unk14, 0x14);
DOTD_ASSERT_OFFSET(CKLinkedBeaconSeq, m_unk16, 0x16);
DOTD_ASSERT_OFFSET(CKLinkedBeaconSeq, m_unk18, 0x18);
