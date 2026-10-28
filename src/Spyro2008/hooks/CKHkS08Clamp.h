// CKHkS08Clamp.h - a clamp hook (key 0x2c82, size 0x130). Original unit:
// CKHkS08Clamp.cpp. No XXL2 class.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/math/CMatrix34.h"
#include "k2000/misc/CKHkActorBase.h"

class CKHkS08Clamp : public CKHkActorBase {
public:
    DOTD_CLASS_KEY(kCategoryHook, 0xb2)
    DOTD_DECLARE_FACTORIES(CKHkS08Clamp)

    // 0x0048d2b8 CKHkS08Clamp_Construct (inlined in 0x0048e240 CKHkS08Clamp_Create): +0x30 = 0, +0xd8 = 0,
    // +0xc4 = 3, +0xb0 = 0, +0xb4 = -1, +0x10d/+0x10c = 0xff. (The +0xb0/+0xb4/+0xc4/+0xd8 defaults are those
    // of CGroundContactDatasInOut, but the live LVL010 objects hold projectile pointers at +0xb8..+0xd0, so
    // the block is not taken for one.)
    CKHkS08Clamp() {
        m_unk30 = 0;
        m_unkD8 = 0;
        m_unkC4 = 3;
        m_unkB0 = 0;
        m_unkB4 = 0xffffffffu;
        m_unk10D = 0xff;
        m_unk10C = 0xff;
    }
    ~CKHkS08Clamp() override {}

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x0048ee18 CKHkS08Clamp_Load
    int32_t PostLoad(int32_t type) override;            // vt+0x30 0x0048dbc0 CKHkS08Clamp_PostLoad

    uint32_t m_unk20;          // +0x20 runtime (PostLoad clears the byte at +0x20)
    IKSerializable* m_pUnk24;  // +0x24 runtime (PostLoad: the clamp group, CKGrpS08Meca +0x40)
    uint32_t m_unk28;          // +0x28 runtime
    IKSerializable* m_pUnk2C;  // +0x2c
    uint32_t m_unk30;          // +0x30 constructor 0
    uint32_t m_unk34;
    float m_fUnk38;            // +0x38 (0.7 in the LVL010 samples)
    CMatrix34* m_pUnk3C;       // +0x3c PostLoad: RwMatrixCreate (the second)
    CMatrix34* m_pUnk40;       // +0x40 PostLoad: RwMatrixCreate (the first)
    float m_fUnk44;            // +0x44
    uint32_t m_unk48[11];
    float m_fUnk74;            // +0x74
    float m_fUnk78;            // +0x78
    float m_fUnk7C;            // +0x7c
    uint32_t m_unk80[3];
    float m_fUnk8C;            // +0x8c
    float m_fUnk90;            // +0x90
    float m_fUnk94;            // +0x94
    uint32_t m_unk98[2];
    uint32_t m_unkA0[4];
    uint32_t m_unkB0;          // +0xb0 constructor 0
    uint32_t m_unkB4;          // +0xb4 constructor -1
    uint32_t m_unkB8[3];       // +0xb8 runtime (projectile pointers in the live dump)
    uint32_t m_unkC4;          // +0xc4 constructor 3
    uint32_t m_unkC8[4];
    uint8_t m_unkD8;           // +0xd8 constructor 0
    uint8_t m_unkD9[3];
    float m_fUnkDC;            // +0xdc
    float m_fUnkE0;            // +0xe0
    float m_fUnkE4;            // +0xe4
    uint32_t m_unkE8;
    IKSerializable* m_pUnkEC;  // +0xec
    uint32_t m_unkF0[2];
    IKSerializable* m_pUnkF8;  // +0xf8
    float m_fUnkFC;            // +0xfc
    uint32_t m_unk100;         // +0x100
    uint8_t m_unk104;          // +0x104
    uint8_t m_unk105[7];
    uint8_t m_unk10C;          // +0x10c constructor 0xff
    uint8_t m_unk10D;          // +0x10d constructor 0xff
    uint8_t m_unk10E[0x22];
};
DOTD_ASSERT_SIZE(CKHkS08Clamp, 0x130);
DOTD_ASSERT_OFFSET(CKHkS08Clamp, m_unk20, 0x20);
DOTD_ASSERT_OFFSET(CKHkS08Clamp, m_pUnk24, 0x24);
DOTD_ASSERT_OFFSET(CKHkS08Clamp, m_pUnk2C, 0x2c);
DOTD_ASSERT_OFFSET(CKHkS08Clamp, m_pUnk3C, 0x3c);
DOTD_ASSERT_OFFSET(CKHkS08Clamp, m_pUnk40, 0x40);
DOTD_ASSERT_OFFSET(CKHkS08Clamp, m_unk30, 0x30);
DOTD_ASSERT_OFFSET(CKHkS08Clamp, m_fUnk38, 0x38);
DOTD_ASSERT_OFFSET(CKHkS08Clamp, m_fUnk44, 0x44);
DOTD_ASSERT_OFFSET(CKHkS08Clamp, m_fUnk74, 0x74);
DOTD_ASSERT_OFFSET(CKHkS08Clamp, m_fUnk78, 0x78);
DOTD_ASSERT_OFFSET(CKHkS08Clamp, m_fUnk7C, 0x7c);
DOTD_ASSERT_OFFSET(CKHkS08Clamp, m_fUnk8C, 0x8c);
DOTD_ASSERT_OFFSET(CKHkS08Clamp, m_fUnk90, 0x90);
DOTD_ASSERT_OFFSET(CKHkS08Clamp, m_fUnk94, 0x94);
DOTD_ASSERT_OFFSET(CKHkS08Clamp, m_unkB0, 0xb0);
DOTD_ASSERT_OFFSET(CKHkS08Clamp, m_unkC4, 0xc4);
DOTD_ASSERT_OFFSET(CKHkS08Clamp, m_unkD8, 0xd8);
DOTD_ASSERT_OFFSET(CKHkS08Clamp, m_fUnkDC, 0xdc);
DOTD_ASSERT_OFFSET(CKHkS08Clamp, m_fUnkE0, 0xe0);
DOTD_ASSERT_OFFSET(CKHkS08Clamp, m_fUnkE4, 0xe4);
DOTD_ASSERT_OFFSET(CKHkS08Clamp, m_pUnkEC, 0xec);
DOTD_ASSERT_OFFSET(CKHkS08Clamp, m_pUnkF8, 0xf8);
DOTD_ASSERT_OFFSET(CKHkS08Clamp, m_fUnkFC, 0xfc);
DOTD_ASSERT_OFFSET(CKHkS08Clamp, m_unk100, 0x100);
DOTD_ASSERT_OFFSET(CKHkS08Clamp, m_unk104, 0x104);
DOTD_ASSERT_OFFSET(CKHkS08Clamp, m_unk10C, 0x10c);
