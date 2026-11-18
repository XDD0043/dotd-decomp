// CKPxMotor.h - a physics motor (key 0x48cc, vtable 0xb206e8, size 0x80). Original unit: CKPxMotor.cpp
// (0x230598-0x2317a8). Base: KBase468C (the physics elements). No game file holds one
// (outputs/remake/kp3-class-usage.json). Names ours.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/misc/KBase468C.h"
#include "k2000/util/TVector.h"

class CKPxMotor : public KBase468C {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x123)
    int32_t IsKindOfClass(uint32_t key) override { return key == 0x48cc || key == 0x468c || key == 0xc; }
    DOTD_DECLARE_FACTORIES(CKPxMotor)

    // 0x00230b28 CKPxMotor_Construct (and _2 0x230b88): the base, the vtable, the reference list (null, 1, 0).
    CKPxMotor() {
        m_unk70.m_pBlock = nullptr;
        m_unk70.m_ui32NbElt = 1;
        m_unk70.m_ui32NbUsedElt = 0;
    }
    // 0x00230ab8 CKPxMotor_Destructor (DestructBody 0x230c88, the deleting one 0x230cf8): the reference list's block
    // freed, its length and block cleared, then the base's.
    ~CKPxMotor() override;
    // vt+0x2c 0x00230ec0 CKPxMotor_Load: the base's, then (level data only) the motor's bytes, words and word arrays
    // (counts +0x21 / +0x3e / +0x54), the reference list +0x70 (a 16-bit count) and a word.
    int32_t Load(IKFile* file, int32_t type) override;
    // vt+0x10 0x00230a10 CKPxMotor_Destroy: the base's (empty), then the word arrays freed (the pointers kept).
    void Destroy() override;
    // vt+0x24 0x002309e8 CKPxMotor_RecursiveRegistration: the base's vf24 0x218068 (returns 1, registers nothing).

    uint8_t m_unk18;                       // +0x18
    uint8_t m_pad19[3];
    IKSerializable* m_unk1c;               // +0x1c a reference
    uint8_t m_unk20;                       // +0x20
    uint8_t m_unk21;                       // +0x21 the count of +0x24 / +0x30 / +0x34 / +0x38
    uint8_t m_pad22[2];
    uint32_t* m_unk24;                     // +0x24 words (null for none)
    uint8_t m_unk28;                       // +0x28 the Load sets 2
    uint8_t m_pad29[3];
    uint32_t m_unk2c;                      // +0x2c
    uint32_t* m_unk30;                     // +0x30 words (null for none)
    uint32_t* m_unk34;                     // +0x34 words (set with +0x30)
    uint32_t* m_unk38;                     // +0x38 words (set with +0x30)
    uint8_t m_unk3c;                       // +0x3c the Load sets 0
    uint8_t m_pad3d;
    uint16_t m_unk3e;                      // +0x3e the count of +0x40
    uint32_t* m_unk40;                     // +0x40 words (null for none)
    uint16_t m_unk44;                      // +0x44 the Load sets 0
    uint8_t m_pad46[2];
    uint32_t m_unk48;                      // +0x48 the Load sets 0
    uint32_t m_unk4c;                      // +0x4c
    uint32_t m_unk50;                      // +0x50
    uint16_t m_unk54;                      // +0x54 the count of +0x58
    uint8_t m_pad56[2];
    uint32_t* m_unk58;                     // +0x58 words (null for none)
    uint16_t m_unk5c;                      // +0x5c
    uint8_t m_pad5e[2];
    uint32_t m_unk60;                      // +0x60
    uint32_t m_unk64;                      // +0x64
    uint32_t m_unk68;                      // +0x68
    uint32_t m_unk6c;                      // +0x6c
    TVector<IKSerializable*, 1> m_unk70;   // +0x70 references
    uint32_t m_unk7c;                      // +0x7c
};
DOTD_ASSERT_SIZE(CKPxMotor, 0x80);
DOTD_ASSERT_OFFSET(CKPxMotor, m_unk24, 0x24);
DOTD_ASSERT_OFFSET(CKPxMotor, m_unk30, 0x30);
DOTD_ASSERT_OFFSET(CKPxMotor, m_unk3e, 0x3e);
DOTD_ASSERT_OFFSET(CKPxMotor, m_unk54, 0x54);
DOTD_ASSERT_OFFSET(CKPxMotor, m_unk5c, 0x5c);
DOTD_ASSERT_OFFSET(CKPxMotor, m_unk70, 0x70);
DOTD_ASSERT_OFFSET(CKPxMotor, m_unk7c, 0x7c);
