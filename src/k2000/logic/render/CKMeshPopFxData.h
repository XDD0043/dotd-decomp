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
    int32_t IsKindOfClass(uint32_t key) override {  // vt+0x08 0x9acae8
        return key == 0xa28c || key == 0x304c || key == 0x6 || key == 0xc;
    }
    DOTD_DECLARE_FACTORIES(CKMeshPopFxData)

    CKMeshPopFxData() {}  // inlined in 0x001ae388 CKMeshPopFxData_Create: the vtables only

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x001c8170 CKMeshPopFxData_Load
    // vt+0x30 0x001c8070 CKMeshPopFxData_PostLoad: the reserved node (+0x60) and the placement (+0x08, +0x0c) cleared.
    int32_t PostLoad(int32_t type) override;
    // vt+0x24 0x001c80b8 CKMeshPopFxData_RecursiveRegistration: the FX data base's (nothing), then (type 0) the move
    // component (+0x10) and the alpha curve (+0x14).
    void RecursiveRegistration(int32_t type) override;
    // vt+0x1c 0x001c8700 CKMeshPopFxData_MessageProc: 0x1b01 releases the reserved node; 0x1b00 (a marker: its
    // orientation and position) / 0x1b02 (a hook: its node becomes the placement) start a node (a repeating data
    // reserves one, once) and switch it on. vt+0x40 GetInfo 0x1c8160 returns 1, vt+0x10 Destroy 0x1c8168 is empty.
    int32_t MessageProc(uint16_t message, void* data) override;
    uint32_t GetAssociatedFxClassIdentifier() override { return 0xa24c; }  // vt+0x54 0x1c8060

    // The run-time placement (not read; the users set them before acquiring a node: the enemies clear both,
    // CKHkS08Enemy_SetMeshPopFxActive_maybe). CKMeshPopNodeFx_PlaceAtTarget_maybe: with +0x19 the node goes under the
    // dynamic root at +0x08's world matrix (its frame's LTM) or +0x0c's; without, it hangs under +0x08 or +0x0c.
    class CSGBranch* m_unk08;    // +0x08
    class CSGHotSpot* m_unk0c;   // +0x0c
    IKSerializable* m_unk10;     // +0x10 the CKMoveCpnt each pop plays (CKMeshPopNodeFx_TriggerPop_maybe)
    IKSerializable* m_unk14;     // +0x14 the CKCurve2DCpnt of the alpha over the life (read for every type)
    uint8_t m_unk18;             // +0x18 repeating: the pops go on while active (CKMeshPopNodeFx_SetActive_maybe)
    uint8_t m_unk19;             // +0x19 placed in the world (the dynamic root) rather than under +0x08 / +0x0c
    uint8_t m_pad1a[2];
    float m_unk1c;               // +0x1c the repeat interval's base (the draw is base + range x (1 - 2u))
    float m_unk20;               // +0x20 the repeat interval's range
    float m_unk24;               // +0x24 the scatter distance's base
    float m_unk28;               // +0x28 the scatter distance's range (read for every type)
    float m_unk2c;               // +0x2c the life's base (also the alpha curve's x span)
    float m_unk30;               // +0x30 the life's range
    float m_unk34;               // +0x34 the random tilt's largest angle (degrees)
    int32_t m_unk38;             // +0x38 the pop count's base
    int32_t m_unk3c;             // +0x3c the pop count's range
    float m_unk40;               // +0x40 the scale's range in percent
    uint8_t m_unk44;             // +0x44 facing away from the scatter direction (read for every type)
    uint8_t m_pad45[3];
    float m_unk48;               // +0x48 the random yaw's range (degrees; read for every type)
    uint8_t m_unk4c;             // +0x4c the pops on a ring (each child at its share of a turn; read for every type)
    uint8_t m_pad4d[3];
    float m_unk50;               // +0x50 the ring's spread (degrees; read for every type)
    float m_unk54[3];            // +0x54 the offset added after the scatter (one 12-byte read, for every type)
    class IKFx* m_pReservedFx;   // +0x60 not read: the node a repeating data reserved (MessageProc 0x1b00 / 0x1b02)
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
