// CKFearScream.h - the fear scream element attack (key 0x944c, vtable 0xb239b8, size 0x24c). Original unit:
// CKFearScream.cpp. Derives from CKProjectileElement (its Load and constructor are called first).
// No XXL2 class of this name.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/logic/CKProjectileElement.h"

class CKFearScream : public CKProjectileElement {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x251)
    DOTD_DECLARE_FACTORIES(CKFearScream)

    CKFearScream() {}  // 0x003a12c0 CKFearScream_Construct: the base constructor, then the vtable only
    ~CKFearScream() override {}
    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x003a1cb8 CKFearScream_Load

    IKSerializable* m_unk214[7];   // +0x214 CKExplosionFxData (live)
    IKSerializable* m_unk230;      // +0x230 CNode (live)
    float m_unk234[3];             // +0x234 one 12-byte read, three swapped words (live: 0, then floats)
    IKSerializable* m_unk240;      // +0x240 CKSoundDictionaryID (live)
    uint32_t m_unk244;             // +0x244 (not read)
    uint32_t m_unk248;             // +0x248 (not read)
};
DOTD_ASSERT_SIZE(CKFearScream, 0x24c);
DOTD_ASSERT_OFFSET(CKFearScream, m_unk214, 0x214);
DOTD_ASSERT_OFFSET(CKFearScream, m_unk230, 0x230);
DOTD_ASSERT_OFFSET(CKFearScream, m_unk234, 0x234);
DOTD_ASSERT_OFFSET(CKFearScream, m_unk240, 0x240);
