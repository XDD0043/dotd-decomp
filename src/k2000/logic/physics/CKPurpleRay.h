// CKPurpleRay.h - the purple ray breath (key 0x930c, vtable 0xb23f08, size 0x228). Original unit:
// CKPurpleRay.cpp (0x3c5af0-0x3c9a68). Derives from CKBreathElement (its constructor and Load run first). No XXL2
// class of this name. Same layout and Load as CKFearEyes.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/logic/CKBreathElement.h"

class CKPurpleRay : public CKBreathElement {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x24c)
    DOTD_DECLARE_FACTORIES(CKPurpleRay)

    CKPurpleRay() {}  // 0x003c6098 CKPurpleRay_Construct: CKBreathElement's constructor, then the vtable only
    ~CKPurpleRay() override {}
    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x003c6538 CKPurpleRay_Load

    int32_t m_unk178[3];         // +0x178 (live: integers)
    uint32_t m_unk184[3];        // +0x184 (live: 0; type unknown)
    uint32_t m_unk190[3];        // +0x190 (idem)
    float m_unk19c[3];           // +0x19c
    float m_unk1a8[3];           // +0x1a8
    float m_unk1b4;              // +0x1b4
    float m_unk1b8;              // +0x1b8
    float m_unk1bc;              // +0x1bc
    float m_unk1c0;              // +0x1c0
    float m_unk1c4;              // +0x1c4
    IKSerializable* m_unk1c8[3]; // +0x1c8 references (live: heap objects)
    IKSerializable* m_unk1d4[3]; // +0x1d4 references (live: heap objects)
    uint32_t m_unk1e0;           // +0x1e0 (not loaded)
    uint32_t m_unk1e4;           // +0x1e4 (not loaded)
    IKSerializable* m_unk1e8[3]; // +0x1e8 references (live: CNode)
    IKSerializable* m_unk1f4[3]; // +0x1f4 references (live: CKPointLightFxData)
    uint32_t m_unk200;           // +0x200 (not loaded)
    IKSerializable* m_unk204;    // +0x204 reference (live: CKAimCamembert)
    IKSerializable* m_unk208;    // +0x208 reference (live: CKSoundDictionaryID)
    uint8_t m_pad20c[0x1c];      // +0x20c runtime state (not loaded)
};
DOTD_ASSERT_SIZE(CKPurpleRay, 0x228);
DOTD_ASSERT_OFFSET(CKPurpleRay, m_unk178, 0x178);
DOTD_ASSERT_OFFSET(CKPurpleRay, m_unk184, 0x184);
DOTD_ASSERT_OFFSET(CKPurpleRay, m_unk190, 0x190);
DOTD_ASSERT_OFFSET(CKPurpleRay, m_unk19c, 0x19c);
DOTD_ASSERT_OFFSET(CKPurpleRay, m_unk1a8, 0x1a8);
DOTD_ASSERT_OFFSET(CKPurpleRay, m_unk1b4, 0x1b4);
DOTD_ASSERT_OFFSET(CKPurpleRay, m_unk1c4, 0x1c4);
DOTD_ASSERT_OFFSET(CKPurpleRay, m_unk1c8, 0x1c8);
DOTD_ASSERT_OFFSET(CKPurpleRay, m_unk1d4, 0x1d4);
DOTD_ASSERT_OFFSET(CKPurpleRay, m_unk1e8, 0x1e8);
DOTD_ASSERT_OFFSET(CKPurpleRay, m_unk1f4, 0x1f4);
DOTD_ASSERT_OFFSET(CKPurpleRay, m_unk204, 0x204);
DOTD_ASSERT_OFFSET(CKPurpleRay, m_unk208, 0x208);
