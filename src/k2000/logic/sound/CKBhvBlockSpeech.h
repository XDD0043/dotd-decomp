// CKBhvBlockSpeech.h - a behaviour block that plays a speech (DotD) (key 0xa54c, vtable 0xb2fcf0, size 0x18). Original unit: CKBhvBlockSpeech.cpp.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/logic/KBase9C8C.h"

class IKFile;

class CKBhvBlockSpeech : public KBase9C8C {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x295)
    DOTD_DECLARE_FACTORIES(CKBhvBlockSpeech)

    // 0x005c5410 CKBhvBlockSpeech_Create: CKBhvBlockBase_maybe_Construct, then the vtable (CKBhvBlockSpeech_Construct 0x5c5330).
    CKBhvBlockSpeech() {}
    ~CKBhvBlockSpeech() override {}

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x005c5520 CKBhvBlockSpeech_Load

    IKSerializable* m_unk04;  // +0x04
    IKSerializable* m_unk08;  // +0x08
    IKSerializable* m_unk0c;  // +0x0c
    uint8_t m_unk10;          // +0x10
    uint8_t m_unk11;          // +0x11
    uint8_t m_pad12[2];
    uint32_t m_unk14;         // +0x14
};
DOTD_ASSERT_SIZE(CKBhvBlockSpeech, 0x18);
DOTD_ASSERT_OFFSET(CKBhvBlockSpeech, m_unk04, +0x04);
DOTD_ASSERT_OFFSET(CKBhvBlockSpeech, m_unk08, +0x08);
DOTD_ASSERT_OFFSET(CKBhvBlockSpeech, m_unk0c, +0x0c);
DOTD_ASSERT_OFFSET(CKBhvBlockSpeech, m_unk10, +0x10);
DOTD_ASSERT_OFFSET(CKBhvBlockSpeech, m_unk11, +0x11);
DOTD_ASSERT_OFFSET(CKBhvBlockSpeech, m_unk14, +0x14);
