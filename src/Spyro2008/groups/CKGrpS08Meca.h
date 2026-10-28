// CKGrpS08Meca.h - Spyro's mechanism group (key 0xbc4, vtable 0xb25170, size 0x50; base CKGrpMeca).
// Original unit: CKGrpS08Meca.cpp. No XXL2 class of this name.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/misc/CKGrpMeca.h"

class CKGrpS08Meca : public CKGrpMeca {
public:
    DOTD_CLASS_KEY(kCategoryGroup, 0x2f)
    DOTD_DECLARE_FACTORIES(CKGrpS08Meca)

    CKGrpS08Meca() {}  // 0x003f9618 CKGrpS08Meca_Create: the base, the vtable

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x003f9670 CKGrpS08Meca_Load
    int32_t PostLoad(int32_t type) override;  // vt+0x30 0x003f92f0 CKGrpS08Meca_PostLoad
    void Start() override;  // vt+0x50 0x003f92b8 CKGrpS08Meca_Start (C2.2)

    IKSerializable* m_pUnk40;  // +0x40 reference (LVL010: the CKGrpS08Clamp)
    IKSerializable* m_pUnk44;  // +0x44 reference
    IKSerializable* m_pUnk48;  // +0x48 reference (LVL010: the CKGrpTransportableObject)
    uint32_t m_unk4c;          // +0x4c not set
};
DOTD_ASSERT_SIZE(CKGrpS08Meca, 0x50);
DOTD_ASSERT_OFFSET(CKGrpS08Meca, m_pUnk40, 0x40);
DOTD_ASSERT_OFFSET(CKGrpS08Meca, m_pUnk48, 0x48);
