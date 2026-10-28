// CKS08CarrierHero.h - (key 0x91cc, vtable 0xb28d98, size 0xbc). Original unit: CKS08CarrierHero.cpp
// (0x4b08d8-0x4b4750). Base: KBase910C
// (CKS08CarrierBase_maybe). No XXL2 class of this name. +0x44..+0xa7: runtime (heap pointers set at Init).
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/logic/KBase910C.h"

class IKTime;

class CKS08CarrierHero : public KBase910C {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x247)
    DOTD_DECLARE_FACTORIES(CKS08CarrierHero)

    // 0x004b0e00 CKS08CarrierHero_Construct: the base, the vtable, then +0xa9 and +0xa8 = 0xff.
    CKS08CarrierHero() {
        m_unka9 = 0xff;
        m_unka8 = 0xff;
    }
    ~CKS08CarrierHero() override {}
    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x004b2288 CKS08CarrierHero_Load
    void Reset();  // vt+0x68 0x004b4118 CKS08CarrierHero_Reset_maybe (C2.2)
    // vt+0x74 0x004b4518 CKS08CarrierHero_UpdateStateMachine (CKS08CarrierHero.cpp).
    void UpdateStateMachine(IKTime* clock);
    // DOTD: a state handler of the table (k2000/core/Ps3MemberFn.h); none is ported (C2.8).
    uint8_t CallState(const uint32_t pair[2], IKTime* clock, int32_t phase, uint8_t other);
    // vt+0x80 0x009c54c8 CKS08CarrierHero_vf80: the carried object.
    IKSerializable* GetCarriedObject() const { return m_pCarriedObject; }

    uint32_t m_unk04;              // +0x04 runtime
    IKSerializable* m_pSoundDico;  // +0x08 (live: CKSoundDictionaryID)
    float m_unk0c;                 // +0x0c
    IKSerializable* m_pUnk10;      // +0x10 Reset: the last child group of class id 0x35 of the game manager's group +0x0c
    uint32_t m_unk14;              // +0x14 runtime
    IKSerializable* m_pCarriedObject;  // +0x18 the object carried (vt+0x80); runtime
    IKSerializable* m_pAnimDico;   // +0x1c (live: CAnimationDictionary)
    uint32_t m_unk20;              // +0x20 runtime
    uint32_t* m_aui32Unk24;        // +0x24 OperatorNewArray(count * 4)
    uint32_t m_ui32NbUnk24;        // +0x28 the count
    IKSerializable* m_pHero;       // +0x2c (live: CKHkS08Hero)
    float m_unk30;                 // +0x30
    float m_unk34;                 // +0x34
    IKSerializable* m_pHotSpot;    // +0x38 (live: CSGHotSpot)
    IKSerializable* m_pBranch;     // +0x3c (live: CSGBranch)
    float m_unk40;                 // +0x40
    uint32_t m_unk44[24];          // +0x44..+0xa3 runtime
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
