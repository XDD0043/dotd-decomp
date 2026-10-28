// CKLightningBoltFxData.h - the data of a lightning-bolt effect (key 0xa64c, vtable 0xb2e048, size 0xa8).
// Original unit: CKLightningBoltFxData_2.cpp (0x5774e8-0x579b00); Create (0x56eec8) is in
// CKLightningBoltFxData.cpp. Its node is CKLightningBoltNodeFx (0xa60c). Not in XXL2; names ours.
//
// The segments (+0x60) are 60-byte records of fifteen byte-swapped words (CopyEntry60 0x577868 copies them).
// The decompiler shows three of them unswapped; the assembly swaps all fifteen (lwbrx).
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/logic/IKFxData.h"
#include "k2000/util/TVector.h"

class CKLightningBoltFxData : public IKFxData {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x299)
    DOTD_DECLARE_FACTORIES(CKLightningBoltFxData)

    struct Segment {
        float m_values[15];  // +0x00 (LVL010: floats, 100.0, 1.0, 0.2, ...)
    };

    CKLightningBoltFxData();  // inlined in 0x0056eec8 CKLightningBoltFxData_Create

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x00578158 CKLightningBoltFxData_Load
    // vt+0x30 PostLoad 0x5774f8 (stays the default in C2.1).
    uint32_t GetAssociatedFxClassIdentifier() override { return 0xa60c; }  // vt+0x54 0x5774e8

    uint32_t m_unk08[4];       // +0x08 not read
    uint16_t m_unk18;          // +0x18 (lhbrx)
    uint8_t m_pad1a[2];
    float m_unk1c;             // +0x1c
    uint32_t m_unk20[3];       // +0x20 not read
    uint8_t m_unk2c[4];        // +0x2c read without a swap: the file's bytes (colours, _maybe)
    uint8_t m_unk30[4];        // +0x30 read without a swap
    uint8_t m_unk34[4];        // +0x34 read without a swap
    uint8_t m_unk38[4];        // +0x38 read without a swap
    float m_unk3c;             // +0x3c
    IKSerializable* m_unk40;   // +0x40 object references
    IKSerializable* m_unk44;   // +0x44
    IKSerializable* m_unk48;   // +0x48
    IKSerializable* m_unk4c;   // +0x4c
    float m_unk50;             // +0x50 RandomInterval50 (0x577630) _maybe reads +0x50/+0x54
    float m_unk54;             // +0x54
    float m_unk58;             // +0x58 RandomInterval58 (0x5775b8) _maybe reads +0x58/+0x5c
    float m_unk5c;             // +0x5c
    TVector<Segment, 1> m_segments;  // +0x60 the constructor: null, 1, 0
    float m_unk6c;             // +0x6c RandomValue6C (0x577548) _maybe reads +0x6c/+0x70
    float m_unk70;             // +0x70
    uint32_t m_unk74[5];       // +0x74 not read
    float m_unk88;             // +0x88 read last
    IKSerializable* m_unk8c;   // +0x8c an object reference
    float m_unk90;             // +0x90
    float m_unk94;             // +0x94
    float m_unk98;             // +0x98
    float m_unk9c;             // +0x9c
    float m_unka0;             // +0xa0
    float m_unka4;             // +0xa4
};
static_assert(CKLightningBoltFxData::kClassKey == 0xa64c, "key");
DOTD_ASSERT_SIZE(CKLightningBoltFxData::Segment, 0x3c);
DOTD_ASSERT_SIZE(CKLightningBoltFxData, 0xa8);
DOTD_ASSERT_OFFSET(CKLightningBoltFxData, m_unk18, 0x18);
DOTD_ASSERT_OFFSET(CKLightningBoltFxData, m_unk1c, 0x1c);
DOTD_ASSERT_OFFSET(CKLightningBoltFxData, m_unk2c, 0x2c);
DOTD_ASSERT_OFFSET(CKLightningBoltFxData, m_unk3c, 0x3c);
DOTD_ASSERT_OFFSET(CKLightningBoltFxData, m_unk40, 0x40);
DOTD_ASSERT_OFFSET(CKLightningBoltFxData, m_unk4c, 0x4c);
DOTD_ASSERT_OFFSET(CKLightningBoltFxData, m_unk50, 0x50);
DOTD_ASSERT_OFFSET(CKLightningBoltFxData, m_segments, 0x60);
DOTD_ASSERT_OFFSET(CKLightningBoltFxData, m_unk6c, 0x6c);
DOTD_ASSERT_OFFSET(CKLightningBoltFxData, m_unk88, 0x88);
DOTD_ASSERT_OFFSET(CKLightningBoltFxData, m_unk8c, 0x8c);
DOTD_ASSERT_OFFSET(CKLightningBoltFxData, m_unka4, 0xa4);
