// CKGrpS08SpawnableMushroom.h - the spawnable mushrooms group (key 0xd84, vtable 0xb2a050, size 0x84; base
// KBase1944). Original unit: CKGrpS08SpawnableMushroom.cpp. No XXL2 class of this name.
#pragma once
#include <cstdint>

#include "Spyro2008/groups/KBase1944.h"
#include "k2000/core/Layout.h"
#include "k2000/math/CMatrix34.h"

class CKGrpS08SpawnableMushroom : public KBase1944 {
public:
    DOTD_CLASS_KEY(kCategoryGroup, 0x36)
    int32_t IsKindOfClass(uint32_t key) override {  // vt+0x08 0x9c5fa8
        return key == 0xd84 || key == 0x1944 || key == 0x17e || key == 0x4 || key == 0x2fe || key == 0x3fe || key == 0xc;
    }
    DOTD_DECLARE_FACTORIES(CKGrpS08SpawnableMushroom)

    CKGrpS08SpawnableMushroom() {}  // 0x004d7ce8 CKGrpS08SpawnableMushroom_Create: the base, the vtable

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x004d7d40 CKGrpS08SpawnableMushroom_Load
    // vt+0x1c 0x004d7a40 CKGrpS08SpawnableMushroom_MessageProc: KBase1944's, its result kept when 2 or 3,
    // else 1 for any non-zero result and 0 for 0.
    int32_t MessageProc(uint16_t message, void* data) override;
    void Start() override;  // vt+0x50 0x004d7a18 CKGrpS08SpawnableMushroom_Start (C2.2)
    // vt+0x54 0x004d79a0 CKGrpS08SpawnableMushroom_Restart: KBase1944_ReinitRuntime only.
    void Restart() override { KBase1944::Restart(); }
    // vt+0x68 0x004d79f0 CKGrpS08SpawnableMushroom_Stop: KBase1944_DeactivateAllSpawned_maybe 0x444a00 (the same code as
    // 0x444740: every spawned member put to sleep, its slot key cleared, given back).
    void Stop() override { DeactivateAllSpawned(); }
    // vt+0x88 0x004d7958 CKGrpS08SpawnableMushroom_SectorLoaded: IKLife's, then the sector's beacons made ready
    // (SpawnFromSectorBeacons).
    void SectorLoaded(int32_t sector) override;
    // 0x004d73b8 CKGrpS08SpawnableMushroom_SpawnFromSectorBeacons_maybe: every beacon of the group's type in `sector` gets
    // its persistent bit 0 (picked) cleared and its next 8 bits the variant +0x74.
    void SpawnFromSectorBeacons(int32_t sector);
    // vt+0xec 0x009c6070: the beacon type of kind `kind` (0x00a70c4c +0x28: 0x60, 0x67, 0x68, 0x69, 0x6a).
    uint8_t VfEC(uint32_t kind) override;
    void VfFC(const uint16_t* /*slot*/, const uint8_t* /*beacon*/) override {}  // vt+0xfc 0x004d7328 (empty)
    // vt+0x100 0x004d7268 CKGrpS08SpawnableMushroom_vf100: the beacon's persistent bit 0 (picked) is clear.
    uint8_t Vf100(const uint16_t* slot) override;
    uint8_t Vf104(uint32_t /*kind*/) override { return 1; }  // vt+0x104 0x009c6038
    float Vf108(uint32_t kind) override;  // vt+0x108 0x009c6040: 0x00a70c4c[kind] (10 for every kind)
    float Vf10C(uint32_t kind) override;  // vt+0x10c 0x009c6058: 0x00a70c4c[kind + 5] (2 for every kind)

    // (+0x5c and +0x5d are KBase1944's m_unk5c / m_unk5d.)

    CVector3 m_unk60;           // +0x60 one 0xc-byte read, three swaps (LVL010: 1, 1.5, 1.5)
    IKSerializable* m_pUnk6c;   // +0x6c reference (read after +0x70)
    IKSerializable* m_pUnk70;   // +0x70 reference
    uint8_t m_unk74;            // +0x74
    uint8_t m_pad75[3];
    uint32_t m_unk78;           // +0x78 (LVL010: 25)
    IKSerializable* m_pUnk7c;   // +0x7c reference
    float m_unk80;              // +0x80 (LVL010: 0.5)
};
DOTD_ASSERT_SIZE(CKGrpS08SpawnableMushroom, 0x84);
DOTD_ASSERT_OFFSET(CKGrpS08SpawnableMushroom, m_unk5d, 0x5d);
DOTD_ASSERT_OFFSET(CKGrpS08SpawnableMushroom, m_unk60, 0x60);
DOTD_ASSERT_OFFSET(CKGrpS08SpawnableMushroom, m_pUnk6c, 0x6c);
DOTD_ASSERT_OFFSET(CKGrpS08SpawnableMushroom, m_unk74, 0x74);
DOTD_ASSERT_OFFSET(CKGrpS08SpawnableMushroom, m_unk78, 0x78);
DOTD_ASSERT_OFFSET(CKGrpS08SpawnableMushroom, m_unk80, 0x80);
