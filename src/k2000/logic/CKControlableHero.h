// CKControlableHero.h - (key 0xa88c, vtable 0xb22e40, size 0xc). Original unit: CKControlableHero.cpp
// (0x344758-0x344ef0). Derived straight from IKSerializable. No XXL2 class. The character-control cinematic bloc
// (CKCharacterControlBloc) drives a hero through it: vt+0x50 bind (the hero of dragon +0x04 attached to this object and
// sent to a point), vt+0x54 the move-to each frame, vt+0x58 detach.
#pragma once
#include <cstdint>

#include "k2000/core/IKSerializable.h"
#include "k2000/core/Layout.h"
#include "k2000/math/CMatrix34.h"

class CKHkS08Hero;
class IKTime;

class CKControlableHero : public IKSerializable {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x2a2)
    int32_t IsKindOfClass(uint32_t key) override { return key == 0xa88c || key == 0xc; }  // vt+0x08 0x9be7c8
    DOTD_DECLARE_FACTORIES(CKControlableHero)

    // 0x00344bd0 CKControlableHero_Create: +0x8 = 0, then the vtable.
    CKControlableHero() { m_pHero = nullptr; }
    // 0x00344ca8 CKControlableHero_Destructor / 0x00344cc8 DeletingDestructor: vtable stores only (and operator delete).
    ~CKControlableHero() override {}
    void Destroy() override { m_pHero = nullptr; }  // vt+0x10 0x00344c98 CKControlableHero_Destroy

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x00344c10 CKControlableHero_Load

    // vt+0x50 0x00344948 CKControlableHero_BindAndAttachHero_maybe (C2.8 sequence): with a hero group, the hero of dragon
    // +0x04 (+0x08; 0 without a group) is attached to this object (mode 3) and, when it took, gets the attached movement
    // and the move to `position` facing `direction` (vt+0xcc: timeout 10, flag 4 set, flag 31 clear).
    void BindAndAttachHero(const CVector3* position, const CVector3* direction);
    // vt+0x54 0x003447e0 CKControlableHero_UpdateMoveTo: the hero's move-to (vt+0xd0, no out byte): 1 when arrived; 1 without
    // a hero.
    uint8_t UpdateMoveTo(IKTime* clock);
    // vt+0x58 0x003448d0 CKControlableHero_DetachHero: the hero leaves this object when attached to it.
    void DetachHero();

    uint8_t m_unk04;  // +0x04 one byte from the file (LVL010: 0 or 1): the dragon
    uint8_t m_pad05[3];
    CKHkS08Hero* m_pHero;  // +0x08 0 (constructor and Load); the bound hero (BindAndAttachHero)
};
DOTD_ASSERT_SIZE(CKControlableHero, 0xc);
DOTD_ASSERT_OFFSET(CKControlableHero, m_unk04, 0x04);
DOTD_ASSERT_OFFSET(CKControlableHero, m_pHero, 0x08);
