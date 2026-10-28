// CKEnemyCpnt.h - an enemy's component: option flags and movement parameters (key 0x186, vtable 0xb224d0,
// size 0xb8). Original unit: CKEnemyCpnt.cpp. XXL2: Commun/K/KEnemy/CKEnemyCpnt.h (m_baOptionFlags,
// CKHkMoveCpnt m_MoveCpnt; the same Load). DotD adds a word at +0xb4 that is read for every type.
#pragma once
#include <cstdint>

#include "k2000/components/IKComponent.h"
#include "k2000/core/Layout.h"
#include "k2000/logic/CKHkMoveCpnt.h"

class CKEnemyCpnt : public IKComponent {
public:
    DOTD_CLASS_KEY(kCategoryComponent, 0x6)
    DOTD_DECLARE_FACTORIES(CKEnemyCpnt)

    CKEnemyCpnt() {}  // 0x002b2e90 CKEnemyCpnt_Create: the vtables and m_MoveCpnt's constructor (inlined)
    ~CKEnemyCpnt() override {}

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x002b2fb0 CKEnemyCpnt_Load

    uint32_t m_baOptionFlags;   // +0x04 XXL2 CBitArray m_baOptionFlags
    CKHkMoveCpnt m_MoveCpnt;    // +0x08 XXL2 m_MoveCpnt
    uint32_t m_unkb4;           // +0xb4 read for every type (not in XXL2)
};
static_assert(CKEnemyCpnt::kClassKey == 0x186, "key");
DOTD_ASSERT_SIZE(CKEnemyCpnt, 0xb8);
DOTD_ASSERT_OFFSET(CKEnemyCpnt, m_baOptionFlags, 0x04);
DOTD_ASSERT_OFFSET(CKEnemyCpnt, m_MoveCpnt, 0x08);
DOTD_ASSERT_OFFSET(CKEnemyCpnt, m_unkb4, 0xb4);
