// CKS08CarrierEnemy.h - an enemy that carries the hero_maybe (key 0x958c, vtable 0xb297e0, size 0xa8).
// Original unit: CKS08CarrierEnemy.cpp (0x4c7730-0x4c98d8). Base: KBase910C (CKS08CarrierBase_maybe). No XXL2 class of this
// name. +0x38..+0x8b: runtime (heap pointers set at Init).
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/logic/KBase910C.h"

class CKS08CarrierEnemy : public KBase910C {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x256)
    DOTD_DECLARE_FACTORIES(CKS08CarrierEnemy)

    // 0x004c8048 CKS08CarrierEnemy_Construct: the base, the vtable, then +0x8d and +0x8c = 0xff.
    CKS08CarrierEnemy() {
        m_unk8d = 0xff;
        m_unk8c = 0xff;
    }
    ~CKS08CarrierEnemy() override {}
    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x004c90f0 CKS08CarrierEnemy_Load

    uint32_t m_unk04[6];        // +0x04..+0x1b runtime
    uint32_t* m_aui32Unk1c;     // +0x1c OperatorNewArray(count * 4) (file: 194)
    uint32_t m_ui32NbUnk1c;     // +0x20 the count
    IKSerializable* m_pEnemy;   // +0x24 (live: CKHkS08Enemy)
    float m_unk28;              // +0x28
    float m_unk2c;              // +0x2c
    IKSerializable* m_pHotSpot; // +0x30 (live: CSGHotSpot)
    float m_unk34;              // +0x34
    uint32_t m_unk38[21];       // +0x38..+0x8b runtime
    uint8_t m_unk8c;            // +0x8c
    uint8_t m_unk8d;            // +0x8d
    uint8_t m_unk8e[0x1a];      // +0x8e..+0xa7 runtime
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
