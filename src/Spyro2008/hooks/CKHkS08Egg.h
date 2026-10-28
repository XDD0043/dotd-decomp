// CKHkS08Egg.h - an enemy egg hook (key 0x2ac2, size 0x70). Original unit: CKHkS08Egg.cpp. No XXL2 class.
// The fields are named by offset until their use is known.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/math/CMatrix34.h"
#include "k2000/misc/CKHkActorBase.h"
#include "k2000/services/CTriggerStarter.h"
#include "k2000/util/TVector.h"

class CKHkS08Egg : public CKHkActorBase {
public:
    DOTD_CLASS_KEY(kCategoryHook, 0xab)
    DOTD_DECLARE_FACTORIES(CKHkS08Egg)

    // 0x00473160 CKHkS08Egg_Create (inlined constructor): the +0x20 vector empty (block 0, capacity 1,
    // length 0).
    CKHkS08Egg() {
        m_vUnk20.m_pBlock = nullptr;
        m_vUnk20.m_ui32NbElt = 1;
        m_vUnk20.m_ui32NbUsedElt = 0;
    }
    ~CKHkS08Egg() override {}

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x00473828 CKHkS08Egg_Load
    void SetDefaultState(int32_t flag) override;        // vt+0x38 0x00472e58 CKHkS08Egg_SetDefaultState (C2.2)
    void Start() override;                              // vt+0x50 0x00473fc8 CKHkS08Egg_Start (C2.2)

    // +0x20 positions (3 floats each; spawn points_maybe: the samples hold 5 or 8 points near each
    // other). Grows one element at a time; +0x54 is the count in the file.
    TVector<CVector3, 1> m_vUnk20;
    IKSerializable* m_pUnk2C;  // +0x2c
    uint32_t m_unk30;
    uint32_t m_unk34;          // +0x34
    float m_fUnk38;            // +0x38
    float m_fUnk3C;            // +0x3c
    uint32_t m_unk40;          // +0x40 (0, 3, 1 in the LVL010 samples)
    IKSerializable* m_pUnk44;  // +0x44
    float m_fUnk48;            // +0x48
    uint32_t m_unk4C;
    uint8_t m_unk50;           // +0x50
    uint8_t m_unk51[3];
    uint32_t m_unk54;          // +0x54 the number of +0x20 elements in the file
    uint32_t m_unk58;
    float m_fUnk5C;            // +0x5c
    uint32_t m_unk60;
    uint8_t m_unk64;           // +0x64
    uint8_t m_unk65[3];
    CTriggerStarter m_unk68;   // +0x68
};
DOTD_ASSERT_SIZE(CKHkS08Egg, 0x70);
DOTD_ASSERT_OFFSET(CKHkS08Egg, m_vUnk20, 0x20);
DOTD_ASSERT_OFFSET(CKHkS08Egg, m_pUnk2C, 0x2c);
DOTD_ASSERT_OFFSET(CKHkS08Egg, m_unk34, 0x34);
DOTD_ASSERT_OFFSET(CKHkS08Egg, m_fUnk38, 0x38);
DOTD_ASSERT_OFFSET(CKHkS08Egg, m_fUnk3C, 0x3c);
DOTD_ASSERT_OFFSET(CKHkS08Egg, m_unk40, 0x40);
DOTD_ASSERT_OFFSET(CKHkS08Egg, m_pUnk44, 0x44);
DOTD_ASSERT_OFFSET(CKHkS08Egg, m_fUnk48, 0x48);
DOTD_ASSERT_OFFSET(CKHkS08Egg, m_unk50, 0x50);
DOTD_ASSERT_OFFSET(CKHkS08Egg, m_unk54, 0x54);
DOTD_ASSERT_OFFSET(CKHkS08Egg, m_fUnk5C, 0x5c);
DOTD_ASSERT_OFFSET(CKHkS08Egg, m_unk64, 0x64);
DOTD_ASSERT_OFFSET(CKHkS08Egg, m_unk68, 0x68);
