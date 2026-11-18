// CKS08CarrierEnemy.h - an enemy that carries the hero_maybe (key 0x958c, vtable 0xb297e0, size 0xa8).
// Original unit: CKS08CarrierEnemy.cpp (0x4c7730-0x4c98d8). Base: KBase910C (CKS08CarrierBase_maybe). No XXL2 class of this
// name. +0x38..+0x8b: runtime (heap pointers set at Init).
#pragma once
#include "k2000/math/CMatrix34.h"
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/logic/KBase910C.h"

class IKTime;

class CKS08CarrierEnemy : public KBase910C {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x256)
    int32_t IsKindOfClass(uint32_t key) override {  // vt+0x08 0x9c5a00
        return key == 0x958c || key == 0xc || key == 0x910c;
    }
    DOTD_DECLARE_FACTORIES(CKS08CarrierEnemy)

    // 0x004c8048 CKS08CarrierEnemy_Construct: the base, the vtable, then +0x8d and +0x8c = 0xff.
    CKS08CarrierEnemy() {
        m_unk8d = 0xff;
        m_unk8c = 0xff;
    }
    ~CKS08CarrierEnemy() override {}  // 0x004c85a0 CKS08CarrierEnemy_Destructor: the vtable, then the base's
    // vt+0x10 0x004c7f60 CKS08CarrierEnemy_Destroy: the base's (KStub_Nop_4ac390), the word array +0x1c deleted.
    void Destroy() override {
        if (m_aui32Unk1c != nullptr) delete[] m_aui32Unk1c;
    }
    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x004c90f0 CKS08CarrierEnemy_Load

    // The state machine (+0x88 the rows, +0x8c the state, +0x8d the count; rows +0x90: State0_Carry,
    // IsTransportableInReach, State2_PickUp): PS3 descriptors mapped through k2000/core/Ps3MemberFn.h.
    using StateFn = uint8_t (CKS08CarrierEnemy::*)(IKTime* clock, int32_t phase, uint8_t other);
    uint8_t CallState(const uint32_t pair[2], IKTime* clock, int32_t phase, uint8_t other);
    // The KBase910C slots the enemy calls (declared here, not virtual: the enemy's +0x734 is always a CKS08CarrierEnemy).
    void Reset();                           // vt+0x68 0x004c9720 CKS08CarrierEnemy_Reset_maybe
    void UpdateStateMachine(IKTime* clock); // vt+0x74 0x004c93e8 CKS08CarrierEnemy_UpdateStateMachine_maybe
    void ResetStateMachine();               // 0x004c95e8 CKS08CarrierEnemy_ResetStateMachine_maybe
    // State 1 (row +0x98): 0x004c8c30 CKS08CarrierEnemy_IsTransportableInReach_maybe
    uint8_t IsTransportableInReach(IKTime* clock, int32_t phase, uint8_t other);
    uint8_t State0Carry(IKTime* clock, int32_t phase, uint8_t other);   // 0x004c78b8 (state 0)
    uint8_t State2PickUp(IKTime* clock, int32_t phase, uint8_t other);  // 0x004c7a00 (state 2)
    // 0x004c7c58 CKS08CarrierEnemy_ClaimTransportableInReach_maybe
    IKSerializable* ClaimTransportableInReach(uint32_t key);
    // vt+0x58 0x004c7780 CKS08CarrierEnemy_vf58: nothing carried, a class it carries (vt+0x78) and the object not carried.
    uint8_t CanPickUp(IKSerializable* object) override;
    // vt+0x6c 0x004c82d0 CKS08CarrierEnemy_DropCarriedObject_maybe
    void DropCarriedObject() override;
    // vt+0x78 0x004c79d0 CKS08CarrierEnemy_vf78: the class ids it carries.
    uint8_t Vf78(const uint32_t* classId) const;
    // 0x004c7c48 CKS08CarrierEnemy_IsCarrying_maybe: in state 0.
    uint8_t IsCarrying() const { return m_unk8c == 0 ? 1 : 0; }
    uint8_t Vf5C(IKSerializable* object) override;            // vt+0x5c 0x004c7878
    IKSerializable* Vf64() const { return m_pEnemy; }          // vt+0x64 0x004c78b0
    uint8_t StartCarrying(IKSerializable* object) override;   // vt+0x50 0x004c8450
    uint8_t StopCarrying(IKSerializable* object) override;    // vt+0x54 0x004c89f0
    void CaptureCarryPose();                                   // 0x004c80a0 CKS08CarrierEnemy_CaptureCarryPose_maybe
    // 0x004c8ed8 CKS08CarrierEnemy_IsInGrabRangeAndAngle_maybe
    uint8_t IsInGrabRangeAndAngle(const CVector3* pos, const CVector3* dir, IKSerializable* object) const;

    uint32_t m_unk04;           // +0x04 runtime
    IKSerializable* m_pTransportGroup;  // +0x08 Reset: the last child group of class id 0x35 of the game manager's +0x0c
    IKSerializable* m_unk0c;    // +0x0c Reset: 0; the transportable claimed (0x4c7c58)
    IKSerializable* m_unk10;    // +0x10 Reset: 0; the carried transportable
    uint32_t m_unk14[2];        // +0x14..+0x1b runtime
    uint32_t* m_aui32Unk1c;     // +0x1c OperatorNewArray(count * 4) (file: 194)
    uint32_t m_ui32NbUnk1c;     // +0x20 the count
    IKSerializable* m_pEnemy;   // +0x24 (live: CKHkS08Enemy)
    float m_unk28;              // +0x28
    float m_unk2c;              // +0x2c
    IKSerializable* m_pHotSpot; // +0x30 (live: CSGHotSpot)
    float m_unk34;              // +0x34
    float m_fCarryTime;         // +0x38 runtime: the lerp time (CaptureCarryPose: 0)
    uint32_t m_unk3c[7];        // +0x3c..+0x57 runtime
    float m_aQuatHotSpot[4];    // +0x58 runtime: the hot spot's world orientation (CaptureCarryPose)
    float m_aQuatStart[4];      // +0x68 runtime: the carried node's orientation (CaptureCarryPose)
    CVector3 m_vStartPos;       // +0x78 runtime: the carried node's modelling position (CaptureCarryPose)
    uint8_t m_unk84;            // +0x84 Reset: 0
    uint8_t m_pad85[3];
    uint32_t* m_pStates;        // +0x88 &m_aStates (Reset)
    uint8_t m_unk8c;            // +0x8c the state (constructor 0xff, Reset 1)
    uint8_t m_unk8d;            // +0x8d the state count (constructor 0xff, Reset 3)
    uint8_t m_pad8e[2];
    uint32_t m_aStates[3][2];   // +0x90 descriptor / adjust pairs
};
DOTD_ASSERT_SIZE(CKS08CarrierEnemy, 0xa8);
DOTD_ASSERT_OFFSET(CKS08CarrierEnemy, m_aui32Unk1c, 0x1c);
DOTD_ASSERT_OFFSET(CKS08CarrierEnemy, m_ui32NbUnk1c, 0x20);
DOTD_ASSERT_OFFSET(CKS08CarrierEnemy, m_pEnemy, 0x24);
DOTD_ASSERT_OFFSET(CKS08CarrierEnemy, m_unk28, 0x28);
DOTD_ASSERT_OFFSET(CKS08CarrierEnemy, m_pHotSpot, 0x30);
DOTD_ASSERT_OFFSET(CKS08CarrierEnemy, m_unk34, 0x34);
DOTD_ASSERT_OFFSET(CKS08CarrierEnemy, m_unk8c, 0x8c);
DOTD_ASSERT_OFFSET(CKS08CarrierEnemy, m_unk8d, 0x8d);
DOTD_ASSERT_OFFSET(CKS08CarrierEnemy, m_pTransportGroup, 0x08);
DOTD_ASSERT_OFFSET(CKS08CarrierEnemy, m_unk84, 0x84);
DOTD_ASSERT_OFFSET(CKS08CarrierEnemy, m_fCarryTime, 0x38);
DOTD_ASSERT_OFFSET(CKS08CarrierEnemy, m_aQuatHotSpot, 0x58);
DOTD_ASSERT_OFFSET(CKS08CarrierEnemy, m_vStartPos, 0x78);
DOTD_ASSERT_OFFSET(CKS08CarrierEnemy, m_pStates, 0x88);
DOTD_ASSERT_OFFSET(CKS08CarrierEnemy, m_aStates, 0x90);
