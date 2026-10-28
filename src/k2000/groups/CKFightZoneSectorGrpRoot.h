// CKFightZoneSectorGrpRoot.h - the root of a sector's fight-zone groups (key 0x1904, vtable 0xb21c38,
// size 0x2c). Original unit: CKFightZoneSectorGrpRoot.cpp. XXL2: K/KSquad/CKFightZoneSectorGrpRoot.h
// (its Load is GroupBasicLoad, as here).
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/groups/IKBaseGroup.h"

class CKFightZoneSectorGrpRoot : public IKGroup<IKHook> {
public:
    DOTD_CLASS_KEY(kCategoryGroup, 0x64)
    DOTD_DECLARE_FACTORIES(CKFightZoneSectorGrpRoot)

    // 0x0026dd70 CKFightZoneSectorGrpRoot_Create (inlined constructor): the bases, then the priority word
    // 0x80000015.
    CKFightZoneSectorGrpRoot() { m_ui32Priority = 0x80000015u; }

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x0026de48 CKFightZoneSectorGrpRoot_Load
};
DOTD_ASSERT_SIZE(CKFightZoneSectorGrpRoot, 0x2c);
