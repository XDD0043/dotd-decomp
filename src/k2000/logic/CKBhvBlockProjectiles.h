// CKBhvBlockProjectiles.h - an NPC behaviour block that fires projectiles_maybe (key 0xa7cc, vtable 0xb2fc60,
// size 0x68). Original unit: CKBhvBlockProjectiles.cpp (0x5c3088-0x5c4e50). Base: KBase9C8C
// (CKBhvBlockBase_maybe). No XXL2 class of this name and no live struct draft: types from the file data.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/logic/KBase9C8C.h"

class IKTime;

// A turret-like block: entered, the user's node faces the marker (+0x44) or keeps its direction, the aiming sector
// (+0x30) is set from it, the idle animation (the dictionary's first word) plays and the next shot's interval is drawn.
// Each update picks the active enemy (with a squad, awake) the sector scores best, faces it, plays the shooting
// animation (the second word) once the interval ran out, launches a projectile at the target on its activation mark
// (the game manager's vt+0x254 channel) and goes back to the idle animation at its end (a new interval drawn).
class CKBhvBlockProjectiles : public KBase9C8C {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x29f)
    int32_t IsKindOfClass(uint32_t key) override {  // vt+0x08 0x9cd408
        return key == 0xa7cc || key == 0xc || key == 0x9c8c;
    }
    DOTD_DECLARE_FACTORIES(CKBhvBlockProjectiles)

    CKBhvBlockProjectiles() {}  // 0x005c3aa8 CKBhvBlockProjectiles_Construct: the base, then the vtable
    // 0x005c3ca0 CKBhvBlockProjectiles_Destructor (0x5c3c58 deleting, 0x5c3b80 the base one): the vtable, then
    // KBase9C8C_BaseDestructor (the vtable only).
    ~CKBhvBlockProjectiles() override {}
    // vt+0x10 0x005c3a48 CKBhvBlockProjectiles_Destroy: KStub_Nop_5c57c0 (the base's empty Destroy).
    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x005c4850 CKBhvBlockProjectiles_Load
    void Enter(IKSerializable* user) override;   // vt+0x64 0x005c4470 CKBhvBlockProjectiles_vf64
    void Leave(IKSerializable* user) override;   // vt+0x68 0x005c3988 CKBhvBlockProjectiles_vf68
    void Update(IKTime* clock) override;         // vt+0x6c 0x005c3f88 CKBhvBlockProjectiles_Update_maybe

    void FaceTarget();                  // 0x005c3dd8 CKBhvBlockProjectiles_FaceTarget_maybe
    void FireOnAnimMark();              // 0x005c34b0 CKBhvBlockProjectiles_FireOnAnimMark_maybe
    void LaunchAtTarget();              // 0x005c32d8 CKBhvBlockProjectiles_LaunchAtTarget_maybe
    float GetRandomizedInterval();      // 0x005c3928 CKBhvBlockProjectiles_GetRandomizedInterval_maybe

    IKSerializable* m_unk04;  // +0x04 a CKMarkedFX
    IKSerializable* m_unk08;  // +0x08 a CKMarkedSoundDico
    IKSerializable* m_unk0c;  // +0x0c the user (a CKNPCBehaviourBlockUser)
    float m_unk10;            // +0x10 the idle animation's blend time (not above 0: a cut)
    float m_unk14;            // +0x14 the shooting animation's blend time (not above 0: a cut)
    float m_unk18;            // +0x18 runtime: the time since the last shot
    float m_unk1c;            // +0x1c the interval between shots
    float m_unk20;            // +0x20 its random part (+/-)
    float m_unk24;            // +0x24 runtime: the interval drawn for the next shot
    IKSerializable* m_unk28;  // +0x28 the hot spot projectiles start from (CSGHotSpot, key 0x2b4c)
    IKSerializable* m_unk2c;  // +0x2c the animations (CAnimationDictionary: idle, shooting)
    IKSerializable* m_unk30;  // +0x30 the aiming sector (CKAimCamembert)
    IKSerializable* m_unk34;  // +0x34 runtime: the target (an active enemy of the enemy group)
    float m_unk38[3];         // +0x38 one 12-byte read, three swapped words: the direction faced without a target
    IKSerializable* m_unk44;  // +0x44 a CKMarkerBeacon the node is placed at on Enter (or null)
    uint32_t m_unk48[5];      // +0x48..+0x5b
    IKSerializable* m_unk5c;  // +0x5c the projectiles (CKProjectileAccessor)
    float m_unk60;            // +0x60 the projectiles' speed (35.0 in LVL010)
    IKSerializable* m_unk64;  // +0x64 their damage (CKDamage, key 0x96cc)
};
DOTD_ASSERT_SIZE(CKBhvBlockProjectiles, 0x68);
DOTD_ASSERT_OFFSET(CKBhvBlockProjectiles, m_unk04, 0x04);
DOTD_ASSERT_OFFSET(CKBhvBlockProjectiles, m_unk10, 0x10);
DOTD_ASSERT_OFFSET(CKBhvBlockProjectiles, m_unk1c, 0x1c);
DOTD_ASSERT_OFFSET(CKBhvBlockProjectiles, m_unk28, 0x28);
DOTD_ASSERT_OFFSET(CKBhvBlockProjectiles, m_unk38, 0x38);
DOTD_ASSERT_OFFSET(CKBhvBlockProjectiles, m_unk44, 0x44);
DOTD_ASSERT_OFFSET(CKBhvBlockProjectiles, m_unk5c, 0x5c);
DOTD_ASSERT_OFFSET(CKBhvBlockProjectiles, m_unk64, 0x64);
