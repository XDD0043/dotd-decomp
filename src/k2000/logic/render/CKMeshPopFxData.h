// CKMeshPopFxData.h - the data of a mesh-pop effect (key 0xa28c, vtable 0xb1d360, size 0x64). Original
// unit: CKMeshPopFxData_2.cpp (0x1c8060-0x1c8800); Create (0x1ae388) sits in another unit. Its node is
// CKMeshPopNodeFx (0xa24c). Not in XXL2; names ours.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/logic/IKFxData.h"

class CKMeshPopFxData : public IKFxData {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x28a)
    DOTD_DECLARE_FACTORIES(CKMeshPopFxData)

    CKMeshPopFxData() {}  // inlined in 0x001ae388 CKMeshPopFxData_Create: the vtables only

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x001c8170 CKMeshPopFxData_Load
    // vt+0x30 PostLoad 0x1c8070 (stays the default in C2.1).
    uint32_t GetAssociatedFxClassIdentifier() override { return 0xa24c; }  // vt+0x54 0x1c8060

    uint32_t m_unk08;            // +0x08 not read
    uint32_t m_unk0c;            // +0x0c not read
    IKSerializable* m_unk10;     // +0x10 an object reference (Ghidra draft: CKMoveCpnt*)
    IKSerializable* m_unk14;     // +0x14 an object reference (Ghidra draft: CKCurve2DCpnt*), read for every type
    uint8_t m_unk18;             // +0x18
    uint8_t m_unk19;             // +0x19
    uint8_t m_pad1a[2];
    float m_unk1c;               // +0x1c
    float m_unk20;               // +0x20
    float m_unk24;               // +0x24
    float m_unk28;               // +0x28 read for every type
    float m_unk2c;               // +0x2c
    float m_unk30;               // +0x30
    float m_unk34;               // +0x34
    int32_t m_unk38;             // +0x38
    int32_t m_unk3c;             // +0x3c
    float m_unk40;               // +0x40
    uint8_t m_unk44;             // +0x44 read for every type
    uint8_t m_pad45[3];
    float m_unk48;               // +0x48 read for every type
    uint8_t m_unk4c;             // +0x4c read for every type
    uint8_t m_pad4d[3];
    float m_unk50;               // +0x50 read for every type
    uint32_t m_unk54[3];         // +0x54 three byte-swapped words read in one block, for every type
    uint32_t m_unk60;            // +0x60 not read
};
static_assert(CKMeshPopFxData::kClassKey == 0xa28c, "key");
DOTD_ASSERT_SIZE(CKMeshPopFxData, 0x64);
DOTD_ASSERT_OFFSET(CKMeshPopFxData, m_unk10, 0x10);
DOTD_ASSERT_OFFSET(CKMeshPopFxData, m_unk14, 0x14);
DOTD_ASSERT_OFFSET(CKMeshPopFxData, m_unk18, 0x18);
DOTD_ASSERT_OFFSET(CKMeshPopFxData, m_unk19, 0x19);
DOTD_ASSERT_OFFSET(CKMeshPopFxData, m_unk1c, 0x1c);
DOTD_ASSERT_OFFSET(CKMeshPopFxData, m_unk28, 0x28);
DOTD_ASSERT_OFFSET(CKMeshPopFxData, m_unk38, 0x38);
DOTD_ASSERT_OFFSET(CKMeshPopFxData, m_unk40, 0x40);
DOTD_ASSERT_OFFSET(CKMeshPopFxData, m_unk44, 0x44);
DOTD_ASSERT_OFFSET(CKMeshPopFxData, m_unk48, 0x48);
DOTD_ASSERT_OFFSET(CKMeshPopFxData, m_unk4c, 0x4c);
DOTD_ASSERT_OFFSET(CKMeshPopFxData, m_unk50, 0x50);
DOTD_ASSERT_OFFSET(CKMeshPopFxData, m_unk54, 0x54);
