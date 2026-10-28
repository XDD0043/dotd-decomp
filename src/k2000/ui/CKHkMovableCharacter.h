// CKHkMovableCharacter.h - a hook that walks with the path finder (key 0x3402, vtable 0xb2e760, size 0x318).
// Original unit: CKHkMovableCharacter.cpp (0x59cb80-0x5a7d20, library-TOC code). No XXL2 class. Derives from
// IKHook directly (CKHkMovableCharacter_Create 0x59e080 stores vtable_CKHook, then its own). Fields are ours
// (m_unkXX) except the embedded XXL2 structs.
#pragma once
#include <cstdint>

#include "k2000/components/CKPathFindingCpnt.h"
#include "k2000/core/Layout.h"
#include "k2000/hooks/GroundContact.h"
#include "k2000/hooks/IKHook.h"
#include "k2000/math/CMatrix34.h"
#include "k2000/services/CTriggerStarter.h"
#include "k2000/util/TVector.h"

class CKHkMovableCharacter : public IKHook {
public:
    DOTD_CLASS_KEY(kCategoryHook, 0xd0)
    DOTD_DECLARE_FACTORIES(CKHkMovableCharacter)

    CKHkMovableCharacter();  // inlined in 0x0059e080 CKHkMovableCharacter_Create
    ~CKHkMovableCharacter() override {}

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x005a30f0 CKHkMovableCharacter_Load
    // vt+0x50 0x0059cbd8 CKHkMovableCharacter_ResetRuntime (the Start).
    void Start() override;

    uint32_t m_unk20[2];                        // +0x20
    CGroundContactDatasIn m_GContactIn;         // +0x28
    CGroundContactDatasInOut m_GContactInOut;   // +0x38
    uint32_t m_unk64[6];                        // +0x64
    CVector3 m_unk7c;                           // +0x7c constructor 0
    uint32_t m_unk88[0x1a];                     // +0x88
    uint8_t m_unkF0;                            // +0xf0 constructor 0
    uint8_t m_padF1[3];
    uint32_t m_unkF4[0x11];                     // +0xf4
    IKSerializable* m_unk138;                   // +0x138
    IKSerializable* m_unk13c;                   // +0x13c
    uint32_t m_unk140;                          // +0x140
    IKSerializable* m_unk144;                   // +0x144
    uint8_t m_unk148;                           // +0x148 (read before +0x140)
    uint8_t m_pad149[3];
    CVector3 m_unk14c;                          // +0x14c
    CVector3 m_unk158;                          // +0x158
    CVector3 m_unk164;                          // +0x164
    uint32_t m_unk170;                          // +0x170
    uint8_t m_unk174;                           // +0x174
    uint8_t m_pad175[3];
    uint32_t m_unk178[0x1e];                    // +0x178..+0x1ef 30 words, each read and swapped
    CKPathFindingCpnt m_PFCpnt;                 // +0x1f0 (vtables 0xb12ce8 then 0xb1e4f0 in Create)
    uint32_t m_unk268[4];                       // +0x268
    CVector3 m_unk278;                          // +0x278
    CVector3 m_unk284;                          // +0x284
    IKSerializable* m_unk290;                   // +0x290
    TVector<IKSerializable*, 1> m_vUnk294;      // +0x294 u16-counted references
    IKSerializable* m_unk2a0[3];                // +0x2a0 three single references
    uint32_t m_unk2ac;                          // +0x2ac
    IKSerializable* m_unk2b0[3];                // +0x2b0 three single references (after the path-finding Load)
    uint32_t m_unk2bc;                          // +0x2bc
    uint32_t m_unk2c0;                          // +0x2c0
    uint8_t m_unk2c4;                           // +0x2c4 constructor 0xff
    uint8_t m_unk2c5;                           // +0x2c5 constructor 0xff
    uint8_t m_pad2c6[2];
    uint32_t m_unk2c8[0xe];                     // +0x2c8
    CTriggerStarter m_unk300;                   // +0x300
    CTriggerStarter m_unk308;                   // +0x308
    CTriggerStarter m_unk310;                   // +0x310
};
DOTD_ASSERT_SIZE(CKHkMovableCharacter, 0x318);
DOTD_ASSERT_OFFSET(CKHkMovableCharacter, m_GContactIn, 0x28);
DOTD_ASSERT_OFFSET(CKHkMovableCharacter, m_GContactInOut, 0x38);
DOTD_ASSERT_OFFSET(CKHkMovableCharacter, m_unk7c, 0x7c);
DOTD_ASSERT_OFFSET(CKHkMovableCharacter, m_unkF0, 0xf0);
DOTD_ASSERT_OFFSET(CKHkMovableCharacter, m_unk138, 0x138);
DOTD_ASSERT_OFFSET(CKHkMovableCharacter, m_unk140, 0x140);
DOTD_ASSERT_OFFSET(CKHkMovableCharacter, m_unk148, 0x148);
DOTD_ASSERT_OFFSET(CKHkMovableCharacter, m_unk14c, 0x14c);
DOTD_ASSERT_OFFSET(CKHkMovableCharacter, m_unk170, 0x170);
DOTD_ASSERT_OFFSET(CKHkMovableCharacter, m_unk178, 0x178);
DOTD_ASSERT_OFFSET(CKHkMovableCharacter, m_PFCpnt, 0x1f0);
DOTD_ASSERT_OFFSET(CKHkMovableCharacter, m_unk268, 0x268);
DOTD_ASSERT_OFFSET(CKHkMovableCharacter, m_unk278, 0x278);
DOTD_ASSERT_OFFSET(CKHkMovableCharacter, m_unk290, 0x290);
DOTD_ASSERT_OFFSET(CKHkMovableCharacter, m_vUnk294, 0x294);
DOTD_ASSERT_OFFSET(CKHkMovableCharacter, m_unk2a0, 0x2a0);
DOTD_ASSERT_OFFSET(CKHkMovableCharacter, m_unk2ac, 0x2ac);
DOTD_ASSERT_OFFSET(CKHkMovableCharacter, m_unk2b0, 0x2b0);
DOTD_ASSERT_OFFSET(CKHkMovableCharacter, m_unk2bc, 0x2bc);
DOTD_ASSERT_OFFSET(CKHkMovableCharacter, m_unk2c4, 0x2c4);
DOTD_ASSERT_OFFSET(CKHkMovableCharacter, m_unk300, 0x300);
