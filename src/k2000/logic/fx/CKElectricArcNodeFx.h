// CKElectricArcNodeFx.h - the electric-arc effect node (key 0x164c, vtable 0xb1c8c8, size 0x50). Original
// unit: CKElectricArcNodeFx.cpp. Its data is CKElectricArcFxData (0x174c). Not in XXL2; names ours.
//
// Load reads three single bytes into the first byte of the words +0x18, +0x44 and +0x48: on the PS3 a word
// load of them sees the byte in bits 24..31.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/fx/IKNodeFx.h"

class CKElectricArcNodeFx : public IKNodeFx {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x59)
    DOTD_DECLARE_FACTORIES(CKElectricArcNodeFx)

    CKElectricArcNodeFx() {}  // inlined in 0x001b20c0 CKElectricArcNodeFx_Create: the IKNodeFx part only
    ~CKElectricArcNodeFx() override {}

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x001b2118 CKElectricArcNodeFx_Load
    int32_t PostLoad(int32_t type) override;            // vt+0x30 0x001b2018 CKElectricArcNodeFx_PostLoad

    IKSerializable* m_pFxData;  // +0x14 the inline GetFxData/SetFxData (0x9ab9a0/0x9ab9a8) use it
    uint8_t m_unk18;            // +0x18 one byte (LVL010: 5)
    uint8_t m_pad19[3];
    uint32_t m_unk1c[10];       // +0x1c run-time state
    uint8_t m_unk44;            // +0x44 one byte (LVL010: 0)
    uint8_t m_pad45[3];
    uint8_t m_unk48;            // +0x48 one byte (LVL010: 4)
    uint8_t m_pad49[3];
    int32_t m_unk4c;            // +0x4c
};
static_assert(CKElectricArcNodeFx::kClassKey == 0x164c, "key");
DOTD_ASSERT_SIZE(CKElectricArcNodeFx, 0x50);
DOTD_ASSERT_OFFSET(CKElectricArcNodeFx, m_pFxData, 0x14);
DOTD_ASSERT_OFFSET(CKElectricArcNodeFx, m_unk18, 0x18);
DOTD_ASSERT_OFFSET(CKElectricArcNodeFx, m_unk44, 0x44);
DOTD_ASSERT_OFFSET(CKElectricArcNodeFx, m_unk48, 0x48);
