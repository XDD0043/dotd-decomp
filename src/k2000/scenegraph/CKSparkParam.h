// CKSparkParam.h - the parameters of a spark effect (key 0x110b, vtable 0xb18ac0, size 0x9c). Original
// unit: CKSparkParam.cpp. No XXL2 class; the fields keep their offsets until named (the Ghidra struct's
// flUnkXX / dwUnkXX). LVL010 holds 576.
#pragma once
#include <cstdint>

#include "k2000/core/IKSerializable.h"
#include "k2000/core/Layout.h"

class CKSparkParam : public IKSerializable {
public:
    DOTD_CLASS_KEY(kCategoryNode, 0x44)
    DOTD_DECLARE_FACTORIES(CKSparkParam)

    CKSparkParam() {}  // 0x000e5280 CKSparkParam_Create: only the vtable
    ~CKSparkParam() override {}

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x000e5388 CKSparkParam_Load

    // +0x04..+0x74: 29 words read in groups (3, 3, 3, 3, 3, 2, 2, 2, 2, then 1 each), each byte-swapped.
    // The words at +0x10, +0x28, +0x30..+0x3c are 0 in every LVL010 sample (the decompiler types them
    // as integers; read as floats here like their neighbours).
    float m_afUnk04[29];
    // +0x78..+0x84: four words read without a byte swap (file bytes kept; 0xffffffff in the samples,
    // _maybe colours, RwRGBA).
    uint8_t m_aColor78[4][4];
    float m_unk88;  // +0x88
    float m_unk8c;  // +0x8c
    float m_unk90;  // +0x90
    void* m_pTexture94;  // +0x94 IKFile_ReadTextureRef (resolve 1)
    uint8_t m_aUnk98[3];  // +0x98..+0x9a three bytes, one read each
    uint8_t m_unk9b;      // +0x9b not read
};
static_assert(CKSparkParam::kClassKey == 0x110b, "key");
DOTD_ASSERT_SIZE(CKSparkParam, 0x9c);
DOTD_ASSERT_OFFSET(CKSparkParam, m_afUnk04, 0x04);
DOTD_ASSERT_OFFSET(CKSparkParam, m_aColor78, 0x78);
DOTD_ASSERT_OFFSET(CKSparkParam, m_unk88, 0x88);
DOTD_ASSERT_OFFSET(CKSparkParam, m_pTexture94, 0x94);
DOTD_ASSERT_OFFSET(CKSparkParam, m_aUnk98, 0x98);
