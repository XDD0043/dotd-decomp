// CKTargetCursorFxData.h - the data of a target-cursor effect (key 0x464c, vtable 0xb1da20, size 0x60).
// Original unit: CKTargetCursorFxData.cpp (0x1d4890-0x1d5200). Its node is CKTargetCursorNodeFx (0x460c). Not
// in XXL2; names ours.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/logic/IKFxData.h"

class CKTargetCursorFxData : public IKFxData {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x119)
    DOTD_DECLARE_FACTORIES(CKTargetCursorFxData)

    CKTargetCursorFxData() {}  // inlined in 0x001d4af0 CKTargetCursorFxData_Create: the vtables only

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x001d4b78 CKTargetCursorFxData_Load
    // vt+0x30 PostLoad 0x1d48e8 (stays the default in C2.1).
    uint32_t GetAssociatedFxClassIdentifier() override { return 0x460c; }  // vt+0x54 0x1d48e0

    float m_unk08;        // +0x08
    float m_unk0c;        // +0x0c
    uint8_t m_unk10[3];   // +0x10 three single bytes (LVL010: 0, 0xff, 0), _maybe a colour
    uint8_t m_pad13;
    float m_unk14;        // +0x14
    float m_unk18;        // +0x18
    float m_unk1c;        // +0x1c
    float m_unk20;        // +0x20
    float m_unk24;        // +0x24
    float m_unk28;        // +0x28
    float m_unk2c;        // +0x2c
    uint32_t m_unk30;     // +0x30
    uint8_t m_unk34;      // +0x34
    uint8_t m_unk35;      // +0x35
    uint8_t m_pad36[2];
    float m_unk38;        // +0x38
    float m_unk3c;        // +0x3c
    uint32_t m_unk40;     // +0x40 read with +0x44/+0x48 as one 12-byte block
    float m_unk44;        // +0x44
    uint32_t m_unk48;     // +0x48
    float m_unk4c;        // +0x4c
    float m_unk50;        // +0x50
    float m_unk54;        // +0x54
    float m_unk58;        // +0x58
    uint32_t m_unk5c;     // +0x5c not read
};
static_assert(CKTargetCursorFxData::kClassKey == 0x464c, "key");
DOTD_ASSERT_SIZE(CKTargetCursorFxData, 0x60);
DOTD_ASSERT_OFFSET(CKTargetCursorFxData, m_unk08, 0x08);
DOTD_ASSERT_OFFSET(CKTargetCursorFxData, m_unk10, 0x10);
DOTD_ASSERT_OFFSET(CKTargetCursorFxData, m_unk14, 0x14);
DOTD_ASSERT_OFFSET(CKTargetCursorFxData, m_unk30, 0x30);
DOTD_ASSERT_OFFSET(CKTargetCursorFxData, m_unk34, 0x34);
DOTD_ASSERT_OFFSET(CKTargetCursorFxData, m_unk38, 0x38);
DOTD_ASSERT_OFFSET(CKTargetCursorFxData, m_unk40, 0x40);
DOTD_ASSERT_OFFSET(CKTargetCursorFxData, m_unk4c, 0x4c);
DOTD_ASSERT_OFFSET(CKTargetCursorFxData, m_unk58, 0x58);
