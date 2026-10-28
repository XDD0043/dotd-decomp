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
    DOTD_DECLARE_FACTORIES(CKGrpS08SpawnableMushroom)

    CKGrpS08SpawnableMushroom() {}  // 0x004d7ce8 CKGrpS08SpawnableMushroom_Create: the base, the vtable

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x004d7d40 CKGrpS08SpawnableMushroom_Load
    // vt+0x1c 0x004d7a40 CKGrpS08SpawnableMushroom_MessageProc: KBase1944's, its result kept when 2 or 3,
    // else 1 for any non-zero result and 0 for 0.
    int32_t MessageProc(uint16_t message, void* data) override;
    void Start() override;  // vt+0x50 0x004d7a18 CKGrpS08SpawnableMushroom_Start (C2.2)

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
