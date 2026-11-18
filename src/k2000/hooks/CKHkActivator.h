// CKHkActivator.h - a lever / switch mechanism (key 0xd02, vtable 0xb25268, size 0x54). Original unit:
// CKHkActivator.cpp (0x3f9830-0x3fb460). XXL2: K/KMeca/Activator/CKHkActivator.h (an IKHkMeca there; DotD's base is
// the actor base CKHkActorBase). The members are XXL2's, in XXL2's order, with a second trigger starter; the names
// past m_tsActivateStarter follow XXL2 where the code agrees (the +0x40 sphere's contacts switch it: XXL2 m_pHitBS).
// No level file holds one (work/level-class-keys.json); C2.8 port-rest R03 ported it from the code.
//
// The switch: a contact on the hit sphere (+0x40) by a volume with property bit 1 turns it on (+0x0c bit 7; a reusable
// one, bit 6, toggles), plays sound 0 and the meca component's activation FX at the contact point. While on, the
// animation runs forward to its end (sound 1 / 2 looping at the particle node's points, the grounds hurting with bit 4,
// the on signals +0x24 once with bit 9), while off back to 0 (the off signals +0x2c). With bit 5 the heroes in front of
// it within 1.5 make it their interaction target.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/misc/CKHkActorBase.h"
#include "k2000/services/CTriggerStarter.h"

class CKHkActivator : public CKHkActorBase {
public:
    DOTD_CLASS_KEY(kCategoryHook, 0x34)
    int32_t IsKindOfClass(uint32_t key) override {  // vt+0x08 0x9c0eb8
        return key == 0xd02 || key == 0xd82 || key == 0x2 || key == 0x2fe || key == 0x3fe || key == 0xc;
    }
    DOTD_DECLARE_FACTORIES(CKHkActivator)

    // 0x003fafe8 CKHkActivator_Create (the dead 0x3f9d60 / 0x3fa2f0 _Construct copies): the actor base only; the
    // members are what the fresh heap leaves (zero).
    CKHkActivator();
    // 0x003f9f78 CKHkActivator_Destructor (= 0x3f9fa8 _BaseDestructor, 0x3f9fd8 _DeletingDestructor): the actor base's.
    ~CKHkActivator() override {}

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x003fb040 CKHkActivator_Load
    // vt+0x30 0x003f9ca0 CKHkActivator_PostLoad: the actor base's, then the two trigger starters' (return 1).
    int32_t PostLoad(int32_t type) override;
    // vt+0x38 0x003f9880 CKHkActivator_SetDefaultState: the preset 0 (vt+0xc8).
    void SetDefaultState(int32_t flag) override;
    // vt+0x3c 0x3f72a8: the actor base's (KBaseD82_SetGameState), inherited.
    // vt+0x40 0x003f9950 CKHkActivator_GetInfo: the trigger value 0x98 (0x9c0f28 GetTriggerProp98: +0x0c bit 6), folded
    // with the actor base's answer.
    int32_t GetInfo(IKInfo* info, int32_t request) override;
    // vt+0x1c 0x003fa0e0 CKHkActivator_MessageProc: the actor messages, then 0x997 (data: a byte, bit 9 = the byte),
    // 0x2666 (the message index +0x20 into the data's word +4) and 0x996 (bit 7 = the byte).
    int32_t MessageProc(uint16_t message, void* data) override;
    // vt+0x24 0x003f9d38 CKHkActivator_RecursiveRegistration: the actor base's (IKHook's), inherited.
    // vt+0x10 0x003fa2c8 CKHkActivator_Destroy: the actor base's (vt+0xc0, empty), inherited.
    // vt+0x68 / +0x70 / +0x78 0x3f9c78 / 0x3f9c50 / 0x3f9c28 CKHkActivator_Stop / Pause / Resume: the actor base's
    // (0x3f6e50 / 0x3f6e58 / 0x3f6e60), inherited.
    // vt+0x50 0x003fa020 CKHkActivator_Start: the actor base's (empty), bit 9 set, the two spheres out of the collision
    // service.
    void Start() override;
    // vt+0x54 0x003f9ec0 CKHkActivator_Restart: unless bit 2, bit 9 set and, with a ground and bit 4, the grounds' hurt
    // flag (+0x38 bit 3) = bit 7.
    void Restart() override;
    void Update(IKTime* clock) override;  // vt+0x7c 0x003fa618 CKHkActivator_Update
    void VfA0() override;                 // vt+0xa0 0x003fa328 CKHkActivator_OnActivate
    void VfA4() override;                 // vt+0xa4 0x003face0 CKHkActivator_OnDeactivate
    // vt+0xb4 0x003f9e38 CKHkActivator_AttachSounds: sounds 0..2 of +0x38 attached to the node (no null checks).
    void KGLObjectAttached(IKSerializable* leaf) override;
    // vt+0xc8 0x003fa2a0 CKHkActivator_ApplyStatePreset_maybe: bit 7 = the preset (shifted in whole), bit 8 set.
    void ApplyStatePreset(int32_t state) override;
    // vt+0xd8 0x9c0f20 CKHkActivator_vfD8 returns 1 (CKProjectileTypeTargetLock_IsDead keeps a lock on it).
    uint8_t VfD8() override { return 1; }

    // 0x003f9a50 CKHkActivator_CheckContactsAndToggle_maybe (Update): every collision of the hit sphere whose other
    // volume has property bit 1 switches the activator on (or toggles it with bit 6), takes the sphere out of the
    // collision service, plays sound 0 and the meca component's activation FX at the contact point.
    void CheckContactsAndToggle();

    int32_t m_i32MessageIndex;              // +0x20 XXL2 m_i32MessageIndex (message 0x2666 answers it)
    CTriggerStarter m_tsActivateStarter;    // +0x24 XXL2 m_tsActivateStarter: queued at the forward end (bit 9)
    CTriggerStarter m_tsDeactivateStarter;  // +0x2c _maybe: queued at the backward end (DotD only)
    IKSerializable* m_pAnimatedDictionary;  // +0x34 XXL2 (a CAnimationDictionary: word 0 the animation)
    IKSerializable* m_pSoundDictionary;     // +0x38 XXL2 (a CKSoundDictionaryID: sounds 0..2)
    IKSerializable* m_pDodgeBS;             // +0x3c XXL2 CKBoundingSphere* (may be null)
    IKSerializable* m_pHitBS;               // +0x40 XXL2 CKBoundingSphere* (its contacts switch the activator)
    IKSerializable* m_pMecaCpnt;            // +0x44 XXL2 CKMecaCpnt* (the activation FX)
    IKSerializable* m_pGround;              // +0x48 XXL2 CGround (an ICollisionMesh)
    IKSerializable* m_pParticle;            // +0x4c XXL2 CParticlesNodeFx
    IKSerializable* m_pAdvanceGround;       // +0x50 XXL2 CGround (an ICollisionMesh)
};
DOTD_ASSERT_SIZE(CKHkActivator, 0x54);
DOTD_ASSERT_OFFSET(CKHkActivator, m_i32MessageIndex, 0x20);
DOTD_ASSERT_OFFSET(CKHkActivator, m_tsActivateStarter, 0x24);
DOTD_ASSERT_OFFSET(CKHkActivator, m_tsDeactivateStarter, 0x2c);
DOTD_ASSERT_OFFSET(CKHkActivator, m_pAnimatedDictionary, 0x34);
DOTD_ASSERT_OFFSET(CKHkActivator, m_pSoundDictionary, 0x38);
DOTD_ASSERT_OFFSET(CKHkActivator, m_pDodgeBS, 0x3c);
DOTD_ASSERT_OFFSET(CKHkActivator, m_pHitBS, 0x40);
DOTD_ASSERT_OFFSET(CKHkActivator, m_pMecaCpnt, 0x44);
DOTD_ASSERT_OFFSET(CKHkActivator, m_pGround, 0x48);
DOTD_ASSERT_OFFSET(CKHkActivator, m_pParticle, 0x4c);
DOTD_ASSERT_OFFSET(CKHkActivator, m_pAdvanceGround, 0x50);
