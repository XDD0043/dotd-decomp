// CKWindBeam.h - the wind beam grab (key 0xa50c, vtable 0xb24920, size 0x318). Original unit: CKWindBeam.cpp
// (0x3e0248-0x3e6f80). Derives from CKGrabElement (its constructor and Load run first). No XXL2 class of this name.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/logic/CKGrabElement.h"

class CKWindBeam : public CKGrabElement {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x294)
    DOTD_DECLARE_FACTORIES(CKWindBeam)

    CKWindBeam() {}  // 0x003e04a0 CKWindBeam_Construct: CKGrabElement's constructor, then the vtable only
    ~CKWindBeam() override {}
    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x003e4a18 CKWindBeam_Load

    uint32_t m_unk140[3];         // +0x140 (file and live: 0; type unknown)
    int32_t m_unk14c[3];          // +0x14c (live: integers)
    int32_t m_unk158[3];          // +0x158 (live: integers)
    uint32_t m_unk164[3];         // +0x164 (live: 0; type unknown)
    float m_unk170[3];            // +0x170
    float m_unk17c[3][3];         // +0x17c three vectors, each one 12-byte read
    float m_unk1a0;               // +0x1a0
    IKSerializable* m_unk1a4;     // +0x1a4 reference (live: CNode; PostLoad shows it in a layer)
    int32_t m_unk1a8[3];          // +0x1a8 (live: integers)
    uint32_t m_unk1b4[3];         // +0x1b4 (live: 0; type unknown)
    uint32_t m_unk1c0[3];         // +0x1c0 (idem)
    float m_unk1cc[3][3];         // +0x1cc three vectors, each one 12-byte read
    uint32_t m_unk1f0;            // +0x1f0 (live: 0; type unknown)
    uint32_t m_unk1f4;            // +0x1f4 (idem)
    IKSerializable* m_unk1f8;     // +0x1f8 reference (live: CNode; PostLoad shows it in a layer)
    IKSerializable* m_unk1fc[3];  // +0x1fc references (live: heap objects)
    uint32_t m_unk208;            // +0x208 (not loaded)
    IKSerializable* m_unk20c[3];  // +0x20c references (live: heap objects)
    uint32_t m_unk218;            // +0x218 (not loaded)
    IKSerializable* m_unk21c[3];  // +0x21c references (live: CParticlesNodeFx)
    IKSerializable* m_unk228[3];  // +0x228 references (live: CParticlesNodeFx)
    int32_t m_unk234;             // +0x234
    float m_unk238[21];           // +0x238..+0x288 (index = (offset - 0x238) / 4)
    IKSerializable* m_unk28c;     // +0x28c reference (live: CKSoundDictionaryID)
    IKSerializable* m_unk290[3];  // +0x290 references (live: CKS08StunDamage)
    uint8_t m_pad29c[0x7c];       // +0x29c runtime state (not loaded)
};
DOTD_ASSERT_SIZE(CKWindBeam, 0x318);
DOTD_ASSERT_OFFSET(CKWindBeam, m_unk140, 0x140);
DOTD_ASSERT_OFFSET(CKWindBeam, m_unk14c, 0x14c);
DOTD_ASSERT_OFFSET(CKWindBeam, m_unk158, 0x158);
DOTD_ASSERT_OFFSET(CKWindBeam, m_unk164, 0x164);
DOTD_ASSERT_OFFSET(CKWindBeam, m_unk170, 0x170);
DOTD_ASSERT_OFFSET(CKWindBeam, m_unk17c, 0x17c);
DOTD_ASSERT_OFFSET(CKWindBeam, m_unk1a0, 0x1a0);
DOTD_ASSERT_OFFSET(CKWindBeam, m_unk1a4, 0x1a4);
DOTD_ASSERT_OFFSET(CKWindBeam, m_unk1a8, 0x1a8);
DOTD_ASSERT_OFFSET(CKWindBeam, m_unk1b4, 0x1b4);
DOTD_ASSERT_OFFSET(CKWindBeam, m_unk1c0, 0x1c0);
DOTD_ASSERT_OFFSET(CKWindBeam, m_unk1cc, 0x1cc);
DOTD_ASSERT_OFFSET(CKWindBeam, m_unk1f0, 0x1f0);
DOTD_ASSERT_OFFSET(CKWindBeam, m_unk1f4, 0x1f4);
DOTD_ASSERT_OFFSET(CKWindBeam, m_unk1f8, 0x1f8);
DOTD_ASSERT_OFFSET(CKWindBeam, m_unk1fc, 0x1fc);
DOTD_ASSERT_OFFSET(CKWindBeam, m_unk20c, 0x20c);
DOTD_ASSERT_OFFSET(CKWindBeam, m_unk21c, 0x21c);
DOTD_ASSERT_OFFSET(CKWindBeam, m_unk228, 0x228);
DOTD_ASSERT_OFFSET(CKWindBeam, m_unk234, 0x234);
DOTD_ASSERT_OFFSET(CKWindBeam, m_unk238, 0x238);
DOTD_ASSERT_OFFSET(CKWindBeam, m_unk28c, 0x28c);
DOTD_ASSERT_OFFSET(CKWindBeam, m_unk290, 0x290);
