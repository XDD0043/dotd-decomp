// CKHkScrapShower.h - a hook that drops scrap pieces around a point (key 0x1242, vtable 0xb285c8, size
// 0x12c). Original unit: CKHkScrapShower.cpp (0x4a40d0-0x4a66d0). No XXL2 class. Field names are
// placeholders: only the Load and the constructor are ported (C2.1); the purposes are _maybe from the
// LVL060 data (two objects).
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/hooks/GroundContact.h"
#include "k2000/math/CMatrix34.h"
#include "k2000/misc/CKHkActorBase.h"
#include "k2000/services/CTriggerStarter.h"

class CKHkScrapShower : public CKHkActorBase {
public:
    DOTD_CLASS_KEY(kCategoryHook, 0x49)
    DOTD_DECLARE_FACTORIES(CKHkScrapShower)

    // 0x004a5ce0 CKHkScrapShower_Create (inlined constructor, the same as the dead 0x4a4b50
    // CKHkScrapShower_Construct): +0x50 = 0 and the ground-contact defaults (+0xe8 / +0xf8).
    CKHkScrapShower() { m_unk50 = 0; }
    ~CKHkScrapShower() override {}

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x004a5d78 CKHkScrapShower_Load

    CVector3 m_unk20;                          // +0x20 a position_maybe (LVL060: near the hook's leaf)
    float m_unk2c;                             // +0x2c (LVL060: 50.0)
    IKSerializable* m_unk30;                   // +0x30 reference (LVL060: a CKScrapShowerCpnt)
    uint32_t m_unk34[7];                       // +0x34..+0x4f runtime (not set by Create or Load)
    uint8_t m_unk50;                           // +0x50 constructor 0
    uint8_t m_unk51;                           // +0x51 runtime (PostLoad 0x4a49c0 clears it)
    uint8_t m_pad52[2];
    uint8_t m_ui8NbUnk58;                      // +0x54 the element count of +0x58 / +0x5c
    uint8_t m_pad55[3];
    uint32_t* m_unk58;                         // +0x58 OperatorNewArray(count * 4), words (LVL060: 100.0f)
    uint32_t* m_unk5c;                         // +0x5c OperatorNewArray(count * 4), words (LVL060: 0)
    float m_unk60[9];                          // +0x60..+0x83 nine separate 4-byte reads
    IKSerializable* m_unk84;                   // +0x84 reference (LVL060: a CKDetectorBase-derived object)
    CVector3 m_unk88;                          // +0x88 one 12-byte read
    float m_unk94[2];                          // +0x94 one 8-byte read
    IKSerializable* m_unk9c;                   // +0x9c reference (LVL060: null)
    uint8_t m_unkA0;                           // +0xa0 (LVL060: 100)
    uint8_t m_padA1[3];
    float m_unkA4[3];                          // +0xa4..+0xaf
    float m_unkB0[3];                          // +0xb0..+0xbb (read last)
    uint8_t m_unkBC;                           // +0xbc (LVL060: 50)
    uint8_t m_padBD[3];
    float m_unkC0;                             // +0xc0 (LVL060: 7.0)
    CTriggerStarter m_unkC4;                   // +0xc4
    CTriggerStarter m_unkCC;                   // +0xcc
    IKSerializable* m_unkD4;                   // +0xd4 reference (LVL060: a CKSoundDictionaryID_maybe)
    uint8_t m_unkD8;                           // +0xd8
    uint8_t m_unkD9;                           // +0xd9
    uint8_t m_padDA[2];
    uint32_t m_unkDC[3];                       // +0xdc runtime
    CGroundContactDatasIn m_GContactIn;        // +0xe8
    CGroundContactDatasInOut m_GContactInOut;  // +0xf8
    uint32_t m_unk124[2];                      // +0x124 runtime
};
DOTD_ASSERT_SIZE(CKHkScrapShower, 0x12c);
DOTD_ASSERT_OFFSET(CKHkScrapShower, m_unk20, 0x20);
DOTD_ASSERT_OFFSET(CKHkScrapShower, m_unk2c, 0x2c);
DOTD_ASSERT_OFFSET(CKHkScrapShower, m_unk30, 0x30);
DOTD_ASSERT_OFFSET(CKHkScrapShower, m_unk50, 0x50);
DOTD_ASSERT_OFFSET(CKHkScrapShower, m_ui8NbUnk58, 0x54);
DOTD_ASSERT_OFFSET(CKHkScrapShower, m_unk58, 0x58);
DOTD_ASSERT_OFFSET(CKHkScrapShower, m_unk5c, 0x5c);
DOTD_ASSERT_OFFSET(CKHkScrapShower, m_unk60, 0x60);
DOTD_ASSERT_OFFSET(CKHkScrapShower, m_unk84, 0x84);
DOTD_ASSERT_OFFSET(CKHkScrapShower, m_unk88, 0x88);
DOTD_ASSERT_OFFSET(CKHkScrapShower, m_unk94, 0x94);
DOTD_ASSERT_OFFSET(CKHkScrapShower, m_unk9c, 0x9c);
DOTD_ASSERT_OFFSET(CKHkScrapShower, m_unkA0, 0xa0);
DOTD_ASSERT_OFFSET(CKHkScrapShower, m_unkA4, 0xa4);
DOTD_ASSERT_OFFSET(CKHkScrapShower, m_unkB0, 0xb0);
DOTD_ASSERT_OFFSET(CKHkScrapShower, m_unkBC, 0xbc);
DOTD_ASSERT_OFFSET(CKHkScrapShower, m_unkC0, 0xc0);
DOTD_ASSERT_OFFSET(CKHkScrapShower, m_unkC4, 0xc4);
DOTD_ASSERT_OFFSET(CKHkScrapShower, m_unkCC, 0xcc);
DOTD_ASSERT_OFFSET(CKHkScrapShower, m_unkD4, 0xd4);
DOTD_ASSERT_OFFSET(CKHkScrapShower, m_unkD8, 0xd8);
DOTD_ASSERT_OFFSET(CKHkScrapShower, m_unkD9, 0xd9);
DOTD_ASSERT_OFFSET(CKHkScrapShower, m_GContactIn, 0xe8);
DOTD_ASSERT_OFFSET(CKHkScrapShower, m_GContactInOut, 0xf8);
