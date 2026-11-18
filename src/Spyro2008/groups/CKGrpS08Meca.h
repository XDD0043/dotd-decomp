// CKGrpS08Meca.h - Spyro's mechanism group (key 0xbc4, vtable 0xb25170, size 0x50; base CKGrpMeca).
// Original unit: CKGrpS08Meca.cpp. No XXL2 class of this name.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/misc/CKGrpMeca.h"

class CKGrpS08Meca : public CKGrpMeca {
public:
    DOTD_CLASS_KEY(kCategoryGroup, 0x2f)
    int32_t IsKindOfClass(uint32_t key) override {  // vt+0x08 0x9c0e40
        return key == 0xbc4 || key == 0x2c4 || key == 0x17e || key == 0x4 || key == 0x2fe || key == 0x3fe || key == 0xc;
    }
    DOTD_DECLARE_FACTORIES(CKGrpS08Meca)

    CKGrpS08Meca() {}  // 0x003f9618 CKGrpS08Meca_Create: the base, the vtable

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x003f9670 CKGrpS08Meca_Load
    int32_t PostLoad(int32_t type) override;  // vt+0x30 0x003f92f0 CKGrpS08Meca_PostLoad
    void Start() override;  // vt+0x50 0x003f92b8 CKGrpS08Meca_Start (C2.2)
    // vt+0x68 0x003f9280 CKGrpS08Meca_Stop: CKGrpMeca's, then the byte at +0x4c cleared.
    void Stop() override {
        CKGrpMeca::Stop();
        m_unk4c = m_unk4c & 0x00ffffffu;  // the byte at +0x4c
    }
    // vt+0x54 0x003f9550 CKGrpS08Meca_Restart: the byte at +0x4c cleared (CKGrpMeca's Restart not called).
    void Restart() override { m_unk4c = m_unk4c & 0x00ffffffu; }
    // vt+0x24 0x003f9340 CKGrpS08Meca_RecursiveRegistration: CKGrpMeca's (0x3f8988, IKGroup's), inherited. vt+0xb8
    // 0x003f9178 CKGrpS08Meca_vfB8 returns 1: IKBaseGroup models no slot there and no ported code calls it.
    // 0x003f9390 _DeletingDestructor / 0x003f9408 _DestructBody: the implicit destructor (CKGrpMeca's base destructor).
    // vt+0x7c 0x003f9208 CKGrpS08Meca_Update: CKGrpMeca_UpdateMembers_maybe only.
    void Update(IKTime* clock) override { UpdateMembers(clock); }

    IKSerializable* m_pUnk40;  // +0x40 reference (LVL010: the CKGrpS08Clamp)
    IKSerializable* m_pUnk44;  // +0x44 reference
    IKSerializable* m_pUnk48;  // +0x48 reference (LVL010: the CKGrpTransportableObject)
    uint32_t m_unk4c;          // +0x4c not set
};
DOTD_ASSERT_SIZE(CKGrpS08Meca, 0x50);
DOTD_ASSERT_OFFSET(CKGrpS08Meca, m_pUnk40, 0x40);
DOTD_ASSERT_OFFSET(CKGrpS08Meca, m_pUnk48, 0x48);
