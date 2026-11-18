// CKElectricArcFxData.h - the data of an electric-arc effect (key 0x174c, vtable 0xb1c860, size 0x3c). Its
// Load is in CKElectricArcNodeFx.cpp; Create (0x1ae028) sits in another unit. Its node is CKElectricArcNodeFx
// (0x164c). Not in XXL2; names ours.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/logic/IKFxData.h"

class CKElectricArcFxData : public IKFxData {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x5d)
    int32_t IsKindOfClass(uint32_t key) override {  // vt+0x08 0x9ab878
        return key == 0x174c || key == 0x304c || key == 0x6 || key == 0xc;
    }
    DOTD_DECLARE_FACTORIES(CKElectricArcFxData)

    // Two byte-swapped words. The PS3 allocates the array with operator new[] and a 4-byte count cookie.
    struct Key {
        float m_unk00;
        float m_unk04;
    };

    CKElectricArcFxData() {}  // inlined in 0x001ae028 CKElectricArcFxData_Create: the vtables only

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x001b1478 CKElectricArcFxData_Load
    uint32_t GetAssociatedFxClassIdentifier() override { return 0x164c; }  // vt+0x54 0x1b11b8
    // vt+0x10 0x001b1260 CKElectricArcFxData_Destroy (CKDOFNodeFx.cpp): the keys deleted, none left.
    void Destroy() override {
        if (m_unk0c != nullptr) {
            delete[] m_unk0c;  // TocBridge_OperatorDeleteArray(m_unk0c - 4): the count cookie
            m_unk08 = 0;
            m_unk0c = nullptr;
        }
    }

    uint32_t m_unk08;   // +0x08 the number of keys in +0x0c (0 unless flag bit 2 of +0x39 is set)
    Key* m_unk0c;       // +0x0c new[] of m_unk08 keys, or null
    float m_unk10;      // +0x10 read eighth
    float m_unk14;      // +0x14 read first
    float m_unk18;      // +0x18 read fourth
    float m_unk1c;      // +0x1c
    float m_unk20;      // +0x20
    float m_unk24;      // +0x24
    float m_unk28;      // +0x28
    float m_unk2c;      // +0x2c
    float m_unk30;      // +0x30
    float m_unk34;      // +0x34
    uint8_t m_unk38;    // +0x38
    uint8_t m_flags39;  // +0x39 bit 2: the keys follow
    uint8_t m_pad3a[2];
};
static_assert(CKElectricArcFxData::kClassKey == 0x174c, "key");
DOTD_ASSERT_SIZE(CKElectricArcFxData::Key, 0x8);
DOTD_ASSERT_SIZE(CKElectricArcFxData, 0x3c);
DOTD_ASSERT_OFFSET(CKElectricArcFxData, m_unk08, 0x08);
DOTD_ASSERT_OFFSET(CKElectricArcFxData, m_unk0c, 0x0c);
DOTD_ASSERT_OFFSET(CKElectricArcFxData, m_unk10, 0x10);
DOTD_ASSERT_OFFSET(CKElectricArcFxData, m_unk34, 0x34);
DOTD_ASSERT_OFFSET(CKElectricArcFxData, m_unk38, 0x38);
DOTD_ASSERT_OFFSET(CKElectricArcFxData, m_flags39, 0x39);
