// CKShockWaveFxData.h - the data of a shockwave effect (key 0x310c, vtable 0xb1d7a0, size 0x44). Original
// unit: k2000/fx/CKShockWaveFxData.cpp (0x1d12b0-0x1d1f20); Create (0x1ae340) sits in another unit. Its node
// is CKShockWaveNodeFx (0x30cc). Not in XXL2; names ours.
//
// Three key lists of (float, float) pairs, each a count then a new[] array (EvalRadiusScale, EvalHeightScale
// and EvalAlpha 0x1d12b8/0x1d1388/0x1d1458 _maybe evaluate them). LVL010: (0, 2) (1, 0); (0, 4) (1, 0);
// (0, 100) (1.5, 0).
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/logic/IKFxData.h"

class CKShockWaveFxData : public IKFxData {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0xc4)
    DOTD_DECLARE_FACTORIES(CKShockWaveFxData)

    // Two byte-swapped words. The PS3 allocates the arrays with operator new[] and a 4-byte count cookie.
    struct Key {
        float m_unk00;
        float m_unk04;
    };

    CKShockWaveFxData();  // 0x001d15c8 CKShockWaveFxData_ConstructBase_maybe (called by Create 0x1ae340)

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x001d1a68 CKShockWaveFxData_Load
    // vt+0x30 PostLoad 0x1d1500 (stays the default in C2.1).
    uint32_t GetAssociatedFxClassIdentifier() override { return 0x30cc; }  // vt+0x54 0x1d12b0

    float m_unk08;          // +0x08
    float m_unk0c;          // +0x0c
    uint32_t m_unk10;       // +0x10 the number of keys in +0x14 (read second)
    Key* m_unk14;           // +0x14 the constructor sets 0
    uint32_t m_unk18;       // +0x18 the number of keys in +0x1c (read first)
    Key* m_unk1c;           // +0x1c the constructor sets 0
    uint32_t m_unk20;       // +0x20 the number of keys in +0x24 (read third)
    Key* m_unk24;           // +0x24 the constructor sets 0
    uint32_t m_unk28;       // +0x28 not read
    float m_unk2c;          // +0x2c not read
    uint8_t m_unk30;        // +0x30
    uint8_t m_pad31[3];
    float m_unk34;          // +0x34
    float m_unk38;          // +0x38
    uint32_t m_unk3c;       // +0x3c the constructor sets 0
    uint8_t m_unk40[4];     // +0x40 read without a swap: the file's bytes (a colour, _maybe)
};
static_assert(CKShockWaveFxData::kClassKey == 0x310c, "key");
DOTD_ASSERT_SIZE(CKShockWaveFxData::Key, 0x8);
DOTD_ASSERT_SIZE(CKShockWaveFxData, 0x44);
DOTD_ASSERT_OFFSET(CKShockWaveFxData, m_unk08, 0x08);
DOTD_ASSERT_OFFSET(CKShockWaveFxData, m_unk10, 0x10);
DOTD_ASSERT_OFFSET(CKShockWaveFxData, m_unk14, 0x14);
DOTD_ASSERT_OFFSET(CKShockWaveFxData, m_unk18, 0x18);
DOTD_ASSERT_OFFSET(CKShockWaveFxData, m_unk1c, 0x1c);
DOTD_ASSERT_OFFSET(CKShockWaveFxData, m_unk20, 0x20);
DOTD_ASSERT_OFFSET(CKShockWaveFxData, m_unk24, 0x24);
DOTD_ASSERT_OFFSET(CKShockWaveFxData, m_unk30, 0x30);
DOTD_ASSERT_OFFSET(CKShockWaveFxData, m_unk34, 0x34);
DOTD_ASSERT_OFFSET(CKShockWaveFxData, m_unk38, 0x38);
DOTD_ASSERT_OFFSET(CKShockWaveFxData, m_unk3c, 0x3c);
DOTD_ASSERT_OFFSET(CKShockWaveFxData, m_unk40, 0x40);
