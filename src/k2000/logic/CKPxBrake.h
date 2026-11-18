// CKPxBrake.h - a physics brake (key 0x494c, vtable 0xb20690, size 0x40). Original unit: CKPxBrake.cpp
// (0x22fc48-0x230598). Base: KBase468C (the physics elements). No game file holds one
// (outputs/remake/kp3-class-usage.json). Names ours.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/misc/KBase468C.h"
#include "k2000/util/TVector.h"

class CKPxBrake : public KBase468C {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x125)
    int32_t IsKindOfClass(uint32_t key) override { return key == 0x494c || key == 0x468c || key == 0xc; }
    DOTD_DECLARE_FACTORIES(CKPxBrake)

    // 0x0022fe28 CKPxBrake_Construct (and _2 0x22fe88): the base, the vtable, the reference list (null, 1, 0).
    CKPxBrake() {
        m_unk30.m_pBlock = nullptr;
        m_unk30.m_ui32NbElt = 1;
        m_unk30.m_ui32NbUsedElt = 0;
    }
    // 0x00230000 CKPxBrake_Destructor (DestructBody 0x22fdb8, the deleting one 0x22ff88): the reference list's block
    // freed, its length and block cleared, then the base's.
    ~CKPxBrake() override;
    // vt+0x2c 0x00230070 CKPxBrake_Load: the base's, then (level data only) a byte, a reference, the word array +0x24
    // (a 16-bit count), a word, the reference list +0x30 (a 16-bit count) and a word.
    int32_t Load(IKFile* file, int32_t type) override;
    // vt+0x10 0x0022fd70 CKPxBrake_Destroy: the base's (empty), then the word array freed (the pointer kept).
    void Destroy() override;
    // vt+0x24 0x0022fd48 CKPxBrake_RecursiveRegistration: the base's vf24 0x218068 (returns 1, registers nothing).

    uint8_t m_unk18;                       // +0x18
    uint8_t m_pad19[3];
    IKSerializable* m_unk1c;               // +0x1c a reference
    uint8_t m_unk20;                       // +0x20 the Load sets 0
    uint8_t m_pad21;
    uint16_t m_unk22;                      // +0x22 the count of +0x24
    uint32_t* m_unk24;                     // +0x24 the words (Mem_AllocAligned16; null for none)
    uint16_t m_unk28;                      // +0x28 the Load sets 0
    uint8_t m_pad2a[2];
    uint32_t m_unk2c;                      // +0x2c
    TVector<IKSerializable*, 1> m_unk30;   // +0x30 references
    uint32_t m_unk3c;                      // +0x3c
};
DOTD_ASSERT_SIZE(CKPxBrake, 0x40);
DOTD_ASSERT_OFFSET(CKPxBrake, m_unk1c, 0x1c);
DOTD_ASSERT_OFFSET(CKPxBrake, m_unk22, 0x22);
DOTD_ASSERT_OFFSET(CKPxBrake, m_unk24, 0x24);
DOTD_ASSERT_OFFSET(CKPxBrake, m_unk2c, 0x2c);
DOTD_ASSERT_OFFSET(CKPxBrake, m_unk30, 0x30);
DOTD_ASSERT_OFFSET(CKPxBrake, m_unk3c, 0x3c);
