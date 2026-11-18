// CKS08CarrierHero.h - (key 0x91cc, vtable 0xb28d98, size 0xbc). Original unit: CKS08CarrierHero.cpp
// (0x4b08d8-0x4b4750). Base: KBase910C
// (CKS08CarrierBase_maybe). No XXL2 class of this name. +0x44..+0xa7: runtime (heap pointers set at Init).
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/logic/KBase910C.h"
#include "k2000/math/CMatrix34.h"

class IKTime;

class CKS08CarrierHero : public KBase910C {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x247)
    int32_t IsKindOfClass(uint32_t key) override {  // vt+0x08 0x9c5468
        return key == 0x91cc || key == 0xc || key == 0x910c;
    }
    DOTD_DECLARE_FACTORIES(CKS08CarrierHero)

    // 0x004b0e00 CKS08CarrierHero_Construct: the base, the vtable, then +0xa9 and +0xa8 = 0xff.
    CKS08CarrierHero() {
        m_unka9 = 0xff;
        m_unka8 = 0xff;
    }
    ~CKS08CarrierHero() override {}
    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x004b2288 CKS08CarrierHero_Load
    void Reset();  // vt+0x68 0x004b4118 CKS08CarrierHero_Reset_maybe (C2.2)
    void DropCarriedObjectAndReset();  // vt+0x70 0x004b3e40 CKS08CarrierHero_DropCarriedObjectAndReset_maybe
    // vt+0x74 0x004b4518 CKS08CarrierHero_UpdateStateMachine (CKS08CarrierHero.cpp).
    void UpdateStateMachine(IKTime* clock);
    // DOTD: a state handler of the table (k2000/core/Ps3MemberFn.h); none is ported (C2.8).
    uint8_t CallState(const uint32_t pair[2], IKTime* clock, int32_t phase, uint8_t other);
    // vt+0x80 0x009c54c8 CKS08CarrierHero_vf80: the carried object.
    IKSerializable* GetCarriedObject() const { return m_pCarriedObject; }
    void CaptureCarryPose();  // 0x004b0a48 CKS08CarrierHero_CaptureCarryPose_maybe
    // 0x004b1bc8 CKS08CarrierHero_IsInGrabRangeAndAngle_maybe
    uint8_t IsInGrabRangeAndAngle(const CVector3* pos, const CVector3* dir, IKSerializable* object) const;

    // vt+0x10 0x004b0d18 CKS08CarrierHero_Destroy: the base's (KStub_Nop_4ac390), the word array +0x24 deleted.
    void Destroy() override;
    uint8_t StartCarrying(IKSerializable* object) override;  // vt+0x50 0x004b4300 CKS08CarrierHero_StartCarrying_maybe
    uint8_t StopCarrying(IKSerializable* object) override;   // vt+0x54 0x004b14e0 CKS08CarrierHero_StopCarrying_maybe
    uint8_t CanPickUp(IKSerializable* object) override;      // vt+0x58 0x004b0bd0 CKS08CarrierHero_CanPickUp_maybe
    void DropCarriedObject() override;  // vt+0x6c 0x004b0f30 CKS08CarrierHero_DropCarriedObject_maybe
    // vt+0x78 0x004b0928 CKS08CarrierHero_vf78: the class ids it carries (0xc2, 0xc3, 0xc5).
    uint8_t Vf78(const uint32_t* classId) const {
        const uint32_t id = *classId;
        if (id - 0xc2u <= 1u) return 1;
        return id == 0xc5u ? 1 : 0;
    }
    IKSerializable* Vf64() const { return m_pHero; }     // vt+0x64 0x9c54b0
    IKSerializable* Vf7C() const { return m_pHotSpot; }  // vt+0x7c 0x9c54c0 (vt+0x84 0x9c54b8 the same)
    // 0x004b0960 CKS08CarrierHero_IsCarriedObjectAttachedToCarrierHotSpot_maybe: the carried object's node hangs under the
    // hot spot's node and bone, or under the carry branch +0x3c.
    uint8_t IsCarriedObjectAttachedToCarrierHotSpot() const;
    // 0x004b0a00 CKS08CarrierHero_SetNearbyReceiver_maybe / 0x004b0a38 _HasNearbyReceiver_maybe
    void SetNearbyReceiver(uint8_t set, IKSerializable* receiver);
    uint8_t HasNearbyReceiver() const { return m_bNearbyReceiver; }
    // 0x004b1de0 CKS08CarrierHero_FindPickupInRange_maybe: the first live transportable of class id `key` near the hero
    // (height within 1.5, within +0x30, inside the cone +0x34 ahead) that can be picked up (vt+0xf4) and is in a state.
    IKSerializable* FindPickupInRange(uint32_t key);
    // State 1 (the table's second row): 0x004b30f8 CKS08CarrierHero_State1_LookForPickup_maybe
    uint8_t State1LookForPickup(IKTime* clock, int32_t phase, uint8_t other);
    // State 0 (the table's first row): 0x004b26c0 CKS08CarrierHero_CarryState_maybe
    uint8_t CarryState(IKTime* clock, int32_t phase, uint8_t other);
    // 0x004b1628 CKS08CarrierHero_LerpCarriedObjectToHotSpot_maybe
    void LerpCarriedObjectToHotSpot(IKTime* clock);
    // The pickup animation's end (CarryState and MessageProc 0x940 inline it): without +0x90 the carried node's start
    // pose kept (+0x84 position, +0x64 the hot spot's orientation, +0x74 its own) and the lerp time cleared; with it the
    // node hung under the carry branch (a grip) or the hot spot at once.
    void CaptureOrAttachCarried();
    // The carried node hung under the carry branch at the identity (it has a grip, vt+0x118) or under the hot spot.
    void AttachCarriedNode();
    int32_t MessageProc(uint16_t message, void* data) override;  // vt+0x1c 0x004b3958 CKS08CarrierHero_MessageProc
    uint8_t Vf5C(IKSerializable* object) override;                // vt+0x5c 0x004b1370 CKS08CarrierHero_vf5C

    uint32_t m_unk04;              // +0x04 runtime
    IKSerializable* m_pSoundDico;  // +0x08 (live: CKSoundDictionaryID)
    float m_unk0c;                 // +0x0c
    IKSerializable* m_pUnk10;      // +0x10 Reset: the last child group of class id 0x35 of the game manager's group +0x0c
    IKSerializable* m_unk14;       // +0x14 runtime: the pickup chosen (State1_LookForPickup)
    IKSerializable* m_pCarriedObject;  // +0x18 the object carried (vt+0x80); runtime
    IKSerializable* m_pAnimDico;   // +0x1c (live: CAnimationDictionary)
    uint8_t m_unk20;               // +0x20 runtime (MessageProc 0x940)
    uint8_t m_pad21[3];
    uint32_t* m_aui32Unk24;        // +0x24 OperatorNewArray(count * 4)
    uint32_t m_ui32NbUnk24;        // +0x28 the count
    IKSerializable* m_pHero;       // +0x2c (live: CKHkS08Hero)
    float m_unk30;                 // +0x30
    float m_unk34;                 // +0x34
    IKSerializable* m_pHotSpot;    // +0x38 (live: CSGHotSpot)
    IKSerializable* m_pBranch;     // +0x3c (live: CSGBranch)
    float m_unk40;                 // +0x40
    float m_fCarryTime;            // +0x44 runtime: the time the carried object has been lerped towards the hot spot
    uint32_t m_unk48[7];           // +0x48..+0x63 runtime
    float m_aQuatHotSpot[4];       // +0x64 runtime: the hot spot's world orientation (the lerp's target)
    float m_aQuatStart[4];         // +0x74 runtime: the carried node's orientation at the pickup's end
    CVector3 m_vStartPos;          // +0x84 runtime: the carried node's modelling position at the pickup's end
    uint8_t m_bUnk90;              // +0x90 runtime (Reset: 0)
    uint8_t m_pad91[3];
    IKSerializable* m_pUnk94;      // +0x94 runtime: an effect (Reset clears it; DropCarriedObjectAndReset releases it, vt+0x58)
    IKSerializable* m_pLastCandidate;  // +0x98 runtime: the pickup found last frame (State1_LookForPickup)
    uint8_t m_bNearbyReceiver;     // +0x9c runtime (0x4b0a00 / 0x4b0a38)
    uint8_t m_pad9D[3];
    IKSerializable* m_pReceiver;   // +0xa0 runtime: the nearby receiver (0x4b0a00)
    uint32_t* m_pStateTable;       // +0xa4 Reset: the state handlers (PS3 pointers to member, 8 bytes each)
    uint8_t m_unka8;               // +0xa8 the current state (0xff none)
    uint8_t m_unka9;               // +0xa9 the number of states
    uint8_t m_unkaa[2];            // +0xaa
    uint32_t m_aStateTable[4];     // +0xac Reset: CarryState 0x4b26c0, State1_LookForPickup 0x4b30f8 (descriptors, adjust 0)
};
DOTD_ASSERT_SIZE(CKS08CarrierHero, 0xbc);
DOTD_ASSERT_OFFSET(CKS08CarrierHero, m_pSoundDico, 0x08);
DOTD_ASSERT_OFFSET(CKS08CarrierHero, m_unk0c, 0x0c);
DOTD_ASSERT_OFFSET(CKS08CarrierHero, m_pAnimDico, 0x1c);
DOTD_ASSERT_OFFSET(CKS08CarrierHero, m_aui32Unk24, 0x24);
DOTD_ASSERT_OFFSET(CKS08CarrierHero, m_ui32NbUnk24, 0x28);
DOTD_ASSERT_OFFSET(CKS08CarrierHero, m_pHero, 0x2c);
DOTD_ASSERT_OFFSET(CKS08CarrierHero, m_unk34, 0x34);
DOTD_ASSERT_OFFSET(CKS08CarrierHero, m_pBranch, 0x3c);
DOTD_ASSERT_OFFSET(CKS08CarrierHero, m_unk40, 0x40);
DOTD_ASSERT_OFFSET(CKS08CarrierHero, m_unka8, 0xa8);
DOTD_ASSERT_OFFSET(CKS08CarrierHero, m_unka9, 0xa9);
DOTD_ASSERT_OFFSET(CKS08CarrierHero, m_pStateTable, 0xa4);
DOTD_ASSERT_OFFSET(CKS08CarrierHero, m_aStateTable, 0xac);
DOTD_ASSERT_OFFSET(CKS08CarrierHero, m_pCarriedObject, 0x18);
DOTD_ASSERT_OFFSET(CKS08CarrierHero, m_fCarryTime, 0x44);
DOTD_ASSERT_OFFSET(CKS08CarrierHero, m_aQuatHotSpot, 0x64);
DOTD_ASSERT_OFFSET(CKS08CarrierHero, m_aQuatStart, 0x74);
DOTD_ASSERT_OFFSET(CKS08CarrierHero, m_vStartPos, 0x84);
