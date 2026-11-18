// CKS08EnemyElement.h - (key 0x7a0c, vtable 0xb21a80, size 0x64). Original unit: CKS08EnemyElement.cpp
// (0x26b348-0x26c918). No XXL2 class of this name. Its Load reads two scene-node references; the rest of
// the object is runtime state (never set by Create, which only stores the vtable).
#pragma once
#include <cstdint>

#include "k2000/core/IKSerializable.h"
#include "k2000/core/Layout.h"
#include "k2000/math/CMatrix34.h"

class CKS08Damage;
class IKTime;

class CKS08EnemyElement : public IKSerializable {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x1e8)
    int32_t IsKindOfClass(uint32_t key) override { return key == 0x7a0c || key == 0xc; }  // vt+0x08 0x9bbd00
    DOTD_DECLARE_FACTORIES(CKS08EnemyElement)

    CKS08EnemyElement() {}  // inlined in 0x0026b7d8 CKS08EnemyElement_Create: the vtable only
    ~CKS08EnemyElement() override {}
    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x0026c7b8 CKS08EnemyElement_Load
    int32_t PostLoad(int32_t type) override;            // vt+0x30 0x0026c2f0 CKS08EnemyElement_PostLoad

    // 0x0026b8b8 CKS08Accessory_AttachToOwner_maybe: the element taken by `pool` (its owner, +0x58): +0x44 the pool's
    // +0x18, the motion vector +0x10 zeroed, the glow node (+0x5c, shown) moved under the element's node.
    void AttachToOwner(IKSerializable* pool);
    // 0x0026bb58 CKS08Accessory_UpdateMotion_maybe: a launched accessory's flight (the accessory manager's list).
    void UpdateMotion(IKTime* clock);
    // 0x0026c408 CKS08Accessory_LaunchFromHit_maybe: the flight's start at the node's world position: pushed away from
    // `hitPoint` (horizontally, turned by the damage's +0x1c / +0x18, at the damage's or the config's speed), the spin,
    // the time on the ground and the break FX `breakFx` (+0x50) set.
    void LaunchFromHit(const CKS08Damage* damage, const CVector3* hitPoint, IKSerializable* breakFx);
    // 0x0026b398 CKS08EnemyElement_BreakOff_maybe: the end of the flight: the node back under the enemy group's first
    // +0x40 node and hidden, the element free (+0x54), the break FX (+0x50) set off at the position.
    void BreakOff();
    // vt+0x50 0x0026c158 CKS08EnemyElement_vf50 (non-virtual here: only the accessory manager's ClearAccessories calls
    // it, on its flying list): BreakOff without the FX and the camera: the node back under the enemy group's first +0x40
    // node and hidden, the element free (+0x54), the glow node (+0x5c) hidden too.
    void ReturnToGroup();

    CVector3 m_v04;            // +0x04 LaunchFromHit: the node's world position; the flight's position (UpdateMotion)
    CVector3 m_v10;            // +0x10 the velocity (AttachToOwner, LaunchFromHit: the zero vector)
    CVector3 m_v1c;            // +0x1c LaunchFromHit: the push, spent over +0x28 (UpdateMotion)
    float m_unk28;             // +0x28 the push time left
    float m_unk2c;             // +0x2c LaunchFromHit: the push time (the damage's +0x14, at least the config's +0x2c)
    float m_afSpin30[3];       // +0x30 the turn rates about the right / up / at axes (the config's +0x0c / +0x10 / +0x14)
    uint32_t m_unk3c;          // +0x3c the bounces so far (UpdateMotion; at most the config's +0x1c)
    float m_unk40;             // +0x40 landed: the time before the break (the config's +0x20; 0 against a wall)
    float m_unk44;             // +0x44 AttachToOwner: the owner pool's +0x18
    uint8_t m_unk48;           // +0x48 landed (on the ground for good, or against a wall)
    uint8_t m_pad49[3];
    IKSerializable* m_pNode;   // +0x4c a scene node (file: key 0xcb references; live: CNode)
    IKSerializable* m_pBreakFx50;  // +0x50 LaunchFromHit: the break FX data (BreakOff)
    uint8_t m_inUse54;         // +0x54 taken by an enemy (AttachRandomAccessories sets 1)
    uint8_t m_pad55[3];
    IKSerializable* m_pPool58; // +0x58 the CKS08EnemyElementPool that gave it (AttachToOwner)
    IKSerializable* m_pGlow;   // +0x5c _maybe a CGlowNodeFx (live), mostly null
    float m_unk60;             // +0x60 LaunchFromHit: the enemy group's +0x268 (the camera follow's time_maybe)
};
DOTD_ASSERT_SIZE(CKS08EnemyElement, 0x64);
DOTD_ASSERT_OFFSET(CKS08EnemyElement, m_pNode, 0x4c);
DOTD_ASSERT_OFFSET(CKS08EnemyElement, m_pGlow, 0x5c);
DOTD_ASSERT_OFFSET(CKS08EnemyElement, m_v10, 0x10);
DOTD_ASSERT_OFFSET(CKS08EnemyElement, m_v04, 0x04);
DOTD_ASSERT_OFFSET(CKS08EnemyElement, m_v1c, 0x1c);
DOTD_ASSERT_OFFSET(CKS08EnemyElement, m_afSpin30, 0x30);
DOTD_ASSERT_OFFSET(CKS08EnemyElement, m_unk40, 0x40);
DOTD_ASSERT_OFFSET(CKS08EnemyElement, m_unk44, 0x44);
DOTD_ASSERT_OFFSET(CKS08EnemyElement, m_unk48, 0x48);
DOTD_ASSERT_OFFSET(CKS08EnemyElement, m_pBreakFx50, 0x50);
DOTD_ASSERT_OFFSET(CKS08EnemyElement, m_unk60, 0x60);
DOTD_ASSERT_OFFSET(CKS08EnemyElement, m_inUse54, 0x54);
DOTD_ASSERT_OFFSET(CKS08EnemyElement, m_pPool58, 0x58);
