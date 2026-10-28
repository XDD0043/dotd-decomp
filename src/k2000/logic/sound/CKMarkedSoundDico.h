// CKMarkedSoundDico.h - the sounds of animation marks (DotD; not in XXL2) (key 0xab0c, vtable 0xb30180, size 0x30). Original unit: CKMarkedSoundDico.cpp.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/core/IKSerializable.h"

class IKFile;

class CKMarkedSoundDico : public IKSerializable {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x2ac)
    DOTD_DECLARE_FACTORIES(CKMarkedSoundDico)

    CKMarkedSoundDico();  // 0x005ce5a8 CKMarkedSoundDico_Create (the constructor inlined)
    ~CKMarkedSoundDico() override {}

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x005ce678 CKMarkedSoundDico_Load

    IKSerializable* m_unk04;  // +0x04
    IKSerializable* m_unk08;  // +0x08 read first
    uint32_t** m_apIds;       // +0x0c a vector of one-word blocks (operator new(4) each); 0
    uint32_t m_idsCapacity;   // +0x10 1
    uint32_t m_idsCount;      // +0x14 0
    uint8_t m_unk18;          // +0x18
    uint8_t m_pad19[3];
    IKSerializable* m_unk1c;  // +0x1c
    IKSerializable* m_unk20;  // +0x20
    uint32_t m_aUnk24[2];     // +0x24 not set by the constructor nor the Load
    uint32_t m_idCount;       // +0x2c the number of words the Load reads
};
DOTD_ASSERT_SIZE(CKMarkedSoundDico, 0x30);
DOTD_ASSERT_OFFSET(CKMarkedSoundDico, m_unk04, +0x04);
DOTD_ASSERT_OFFSET(CKMarkedSoundDico, m_unk08, +0x08);
DOTD_ASSERT_OFFSET(CKMarkedSoundDico, m_apIds, +0x0c);
DOTD_ASSERT_OFFSET(CKMarkedSoundDico, m_idsCapacity, +0x10);
DOTD_ASSERT_OFFSET(CKMarkedSoundDico, m_idsCount, +0x14);
DOTD_ASSERT_OFFSET(CKMarkedSoundDico, m_unk18, +0x18);
DOTD_ASSERT_OFFSET(CKMarkedSoundDico, m_unk1c, +0x1c);
DOTD_ASSERT_OFFSET(CKMarkedSoundDico, m_unk20, +0x20);
DOTD_ASSERT_OFFSET(CKMarkedSoundDico, m_aUnk24, +0x24);
DOTD_ASSERT_OFFSET(CKMarkedSoundDico, m_idCount, +0x2c);
