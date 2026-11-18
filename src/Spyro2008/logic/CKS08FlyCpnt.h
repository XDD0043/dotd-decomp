// CKS08FlyCpnt.h - a flying component's settings (key 0x9a8c, vtable 0xb225d8, size 0x84). Original unit:
// CKS08FlyCpnt.cpp (0x2b85e8-0x2bc640). No XXL2 class of this name. Derives straight from IKSerializable (the
// destructor 0x2b8f00 writes the CKObjectRoot vtable 0xb12ab8 back). Eighteen words read by the Load; the defaults
// are the constructor's (inlined in Create 0x2b8e48 / CreateArray 0x2b8d20).
#pragma once
#include <cstdint>

#include "k2000/core/IKSerializable.h"
#include "k2000/core/Layout.h"

class CKS08FlyCpnt : public IKSerializable {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x26a)
    int32_t IsKindOfClass(uint32_t key) override { return key == 0x9a8c || key == 0xc; }  // vt+0x08 0x9bcfa0
    DOTD_DECLARE_FACTORIES(CKS08FlyCpnt)

    // The constructor inlined in 0x002b8e48 CKS08FlyCpnt_Create / 0x002b8d20 CKS08FlyCpnt_CreateArray: the defaults
    // below; +0x04..+0x0c and +0x5c..+0x74 are left as the heap gives them.
    CKS08FlyCpnt() {
        m_unk50 = 0;
        m_unk24 = 200.0f;            // 0x43480000
        m_unk2c = 1.39626324f;       // 0x3fb2b8c1 (80 degrees, one ulp below)
        m_unk38 = 1.0f;
        m_unk3c = 2.0f;
        m_unk40 = 8.0f;
        m_unk44 = 120.0f;
        m_unk48 = 5.0f;
        m_unk4c = 0.5f;
        m_unk10 = 1.0f;
        m_unk14 = 1.0f;
        m_unk18 = 1.0f;
        m_unk1c = 1.0f;
        m_unk20 = 1.0f;
        m_unk28 = 0.5f;
        m_unk30 = 0.5f;
        m_unk34 = 0.5f;
        m_unk58 = 0;
        m_unk54 = 0;
        m_unk78 = 10.0f;             // 0x41200000
        m_unk7c = 10;
    }
    // 0x002b8f00 CKS08FlyCpnt_Destructor (0x002b8f30 the deleting one + operator delete): the vtables only.
    ~CKS08FlyCpnt() override {}
    // vt+0x2c 0x002b8f70 CKS08FlyCpnt_Load: type 0 only, eighteen 4-byte little-endian words.
    int32_t Load(IKFile* file, int32_t type) override;
    // vt+0x30 0x002b8d08 PostLoad (1), vt+0x24 0x002b8d10 RecursiveRegistration (1), vt+0x10 0x002b8d18 Destroy
    // (empty): the IKSerializable defaults.

    float m_unk04[3];   // +0x04 (a vector: the dead 0x2b8788 adds to it, 0x2b8ce8 zeroes it)
    float m_unk10;      // +0x10 (1.0)
    float m_unk14;      // +0x14 (1.0)
    float m_unk18;      // +0x18 (1.0)
    float m_unk1c;      // +0x1c (1.0)
    float m_unk20;      // +0x20 (1.0)
    float m_unk24;      // +0x24 (200)
    float m_unk28;      // +0x28 (0.5)
    float m_unk2c;      // +0x2c (80 degrees in radians)
    float m_unk30;      // +0x30 (0.5)
    float m_unk34;      // +0x34 (0.5)
    float m_unk38;      // +0x38 (1.0)
    float m_unk3c;      // +0x3c (2.0)
    float m_unk40;      // +0x40 (8.0)
    float m_unk44;      // +0x44 (120)
    float m_unk48;      // +0x48 (5.0)
    float m_unk4c;      // +0x4c (0.5)
    uint32_t m_unk50;   // +0x50 (0)
    uint32_t m_unk54;   // +0x54 (0)
    uint32_t m_unk58;   // +0x58 (0)
    uint32_t m_unk5c[7];  // +0x5c (not set by the constructor nor the Load)
    float m_unk78;      // +0x78 (10.0)
    int32_t m_unk7c;    // +0x7c (10)
};
DOTD_ASSERT_SIZE(CKS08FlyCpnt, 0x84);
DOTD_ASSERT_OFFSET(CKS08FlyCpnt, m_unk04, 0x04);
DOTD_ASSERT_OFFSET(CKS08FlyCpnt, m_unk10, 0x10);
DOTD_ASSERT_OFFSET(CKS08FlyCpnt, m_unk4c, 0x4c);
DOTD_ASSERT_OFFSET(CKS08FlyCpnt, m_unk58, 0x58);
DOTD_ASSERT_OFFSET(CKS08FlyCpnt, m_unk78, 0x78);
DOTD_ASSERT_OFFSET(CKS08FlyCpnt, m_unk7c, 0x7c);
