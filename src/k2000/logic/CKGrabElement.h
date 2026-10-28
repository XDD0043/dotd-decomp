// CKGrabElement.h - the grab-attack element base (key 0x9fcc, vtable 0xb23ae0, size 0x140). Original unit:
// CKGrabElement.cpp (0x3a5e60-0x3a9c50). No XXL2 class of this name: the members keep placeholder names.
// Base of CKElectricalGrapple and CKWindBeam (their Loads call this one first).
#pragma once
#include <cstdint>

#include "k2000/core/IKSerializable.h"
#include "k2000/core/Layout.h"

class CKGrabElement : public IKSerializable {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x27f)
    DOTD_DECLARE_FACTORIES(CKGrabElement)

    CKGrabElement() {}  // 0x003a5eb0 CKGrabElement_Construct: stores the vtable only
    ~CKGrabElement() override {}
    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x003a83c0 CKGrabElement_Load

    uint32_t m_unk04;          // +0x04 (not loaded)
    int32_t m_unk08[3];        // +0x08 (file: 40/60/120)
    float m_unk14[3];          // +0x14
    float m_unk20;             // +0x20
    float m_unk24;             // +0x24
    float m_unk28;             // +0x28
    int32_t m_unk2c[3];        // +0x2c (file: 10/12/16)
    float m_unk38[3];          // +0x38
    float m_unk44[3];          // +0x44
    float m_unk50[3];          // +0x50
    uint32_t m_unk5c[3];       // +0x5c (file and live: 0; type unknown)
    uint32_t m_unk68[3];       // +0x68 (idem)
    uint32_t m_unk74[3];       // +0x74 (idem)
    uint32_t m_unk80[3];       // +0x80 (idem)
    uint32_t m_unk8c[3];       // +0x8c (idem)
    uint32_t m_unk98[3];       // +0x98 (idem)
    uint32_t m_unkA4[3];       // +0xa4 (idem)
    float m_unkB0[3];          // +0xb0
    uint32_t m_unkBc[3];       // +0xbc (file and live: 0; type unknown)
    uint8_t m_unkC8[3];        // +0xc8
    uint8_t m_unkCb[3];        // +0xcb
    uint8_t m_padCe[2];        // +0xce
    IKSerializable* m_unkD0;   // +0xd0 reference (live: CKAimCamembert)
    uint32_t m_unkD4;          // +0xd4 (not loaded)
    uint8_t m_unkD8;           // +0xd8
    uint8_t m_unkD9;           // +0xd9
    uint8_t m_unkDa;           // +0xda
    uint8_t m_padDb;           // +0xdb
    float m_unkDc;             // +0xdc
    float m_unkE0;             // +0xe0
    uint8_t m_unkE4;           // +0xe4
    uint8_t m_unkE5;           // +0xe5
    uint8_t m_unkE6;           // +0xe6
    uint8_t m_padE7;           // +0xe7
    float m_unkE8;             // +0xe8
    float m_unkEc;             // +0xec
    float m_unkF0;             // +0xf0
    float m_unkF4;             // +0xf4
    uint8_t m_unkF8;           // +0xf8
    uint8_t m_unkF9;           // +0xf9
    uint8_t m_padFa[2];        // +0xfa (not loaded)
    float m_unkFc;             // +0xfc
    float m_unk100;            // +0x100
    uint8_t m_unk104;          // +0x104
    uint8_t m_unk105;          // +0x105
    uint8_t m_unk106;          // +0x106
    uint8_t m_pad107;          // +0x107
    float m_unk108;            // +0x108
    float m_unk10c;            // +0x10c
    float m_unk110;            // +0x110
    uint8_t m_unk114;          // +0x114
    uint8_t m_pad115[3];       // +0x115 (not loaded)
    float m_unk118;            // +0x118
    IKSerializable* m_unk11c;  // +0x11c reference (live: CKExplosionFxData)
    uint8_t m_pad120[0x18];    // +0x120 runtime state (not loaded)
    IKSerializable* m_unk138;  // +0x138 reference (live: CKS08ElementDamage)
    uint32_t m_unk13c;         // +0x13c (not loaded)
};
DOTD_ASSERT_SIZE(CKGrabElement, 0x140);
DOTD_ASSERT_OFFSET(CKGrabElement, m_unk08, 0x08);
DOTD_ASSERT_OFFSET(CKGrabElement, m_unk14, 0x14);
DOTD_ASSERT_OFFSET(CKGrabElement, m_unk20, 0x20);
DOTD_ASSERT_OFFSET(CKGrabElement, m_unk24, 0x24);
DOTD_ASSERT_OFFSET(CKGrabElement, m_unk28, 0x28);
DOTD_ASSERT_OFFSET(CKGrabElement, m_unk2c, 0x2c);
DOTD_ASSERT_OFFSET(CKGrabElement, m_unk38, 0x38);
DOTD_ASSERT_OFFSET(CKGrabElement, m_unk44, 0x44);
DOTD_ASSERT_OFFSET(CKGrabElement, m_unk50, 0x50);
DOTD_ASSERT_OFFSET(CKGrabElement, m_unk5c, 0x5c);
DOTD_ASSERT_OFFSET(CKGrabElement, m_unk68, 0x68);
DOTD_ASSERT_OFFSET(CKGrabElement, m_unk74, 0x74);
DOTD_ASSERT_OFFSET(CKGrabElement, m_unk80, 0x80);
DOTD_ASSERT_OFFSET(CKGrabElement, m_unk8c, 0x8c);
DOTD_ASSERT_OFFSET(CKGrabElement, m_unk98, 0x98);
DOTD_ASSERT_OFFSET(CKGrabElement, m_unkA4, 0xa4);
DOTD_ASSERT_OFFSET(CKGrabElement, m_unkB0, 0xb0);
DOTD_ASSERT_OFFSET(CKGrabElement, m_unkBc, 0xbc);
DOTD_ASSERT_OFFSET(CKGrabElement, m_unkC8, 0xc8);
DOTD_ASSERT_OFFSET(CKGrabElement, m_unkCb, 0xcb);
DOTD_ASSERT_OFFSET(CKGrabElement, m_unkD0, 0xd0);
DOTD_ASSERT_OFFSET(CKGrabElement, m_unkD8, 0xd8);
DOTD_ASSERT_OFFSET(CKGrabElement, m_unkD9, 0xd9);
DOTD_ASSERT_OFFSET(CKGrabElement, m_unkDa, 0xda);
DOTD_ASSERT_OFFSET(CKGrabElement, m_unkDc, 0xdc);
DOTD_ASSERT_OFFSET(CKGrabElement, m_unkE0, 0xe0);
DOTD_ASSERT_OFFSET(CKGrabElement, m_unkE4, 0xe4);
DOTD_ASSERT_OFFSET(CKGrabElement, m_unkE5, 0xe5);
DOTD_ASSERT_OFFSET(CKGrabElement, m_unkE6, 0xe6);
DOTD_ASSERT_OFFSET(CKGrabElement, m_unkE8, 0xe8);
DOTD_ASSERT_OFFSET(CKGrabElement, m_unkEc, 0xec);
DOTD_ASSERT_OFFSET(CKGrabElement, m_unkF0, 0xf0);
DOTD_ASSERT_OFFSET(CKGrabElement, m_unkF4, 0xf4);
DOTD_ASSERT_OFFSET(CKGrabElement, m_unkF8, 0xf8);
DOTD_ASSERT_OFFSET(CKGrabElement, m_unkF9, 0xf9);
DOTD_ASSERT_OFFSET(CKGrabElement, m_unkFc, 0xfc);
DOTD_ASSERT_OFFSET(CKGrabElement, m_unk100, 0x100);
DOTD_ASSERT_OFFSET(CKGrabElement, m_unk104, 0x104);
DOTD_ASSERT_OFFSET(CKGrabElement, m_unk105, 0x105);
DOTD_ASSERT_OFFSET(CKGrabElement, m_unk106, 0x106);
DOTD_ASSERT_OFFSET(CKGrabElement, m_unk108, 0x108);
DOTD_ASSERT_OFFSET(CKGrabElement, m_unk10c, 0x10c);
DOTD_ASSERT_OFFSET(CKGrabElement, m_unk110, 0x110);
DOTD_ASSERT_OFFSET(CKGrabElement, m_unk114, 0x114);
DOTD_ASSERT_OFFSET(CKGrabElement, m_unk118, 0x118);
DOTD_ASSERT_OFFSET(CKGrabElement, m_unk11c, 0x11c);
DOTD_ASSERT_OFFSET(CKGrabElement, m_unk138, 0x138);
