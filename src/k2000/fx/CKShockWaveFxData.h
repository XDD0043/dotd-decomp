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

    // vt+0x10 0x001d1950 CKShockWaveFxData_ClearReferences (Destroy): the three key arrays (+0x1c, +0x14, +0x24, in
    // that order) delete[]d and cleared; the counts kept.
    void Destroy() override;
    // vt+0x1c 0x001d15f8 CKShockWaveFxData_HandleMessage (MessageProc): 0x1b00 with an object (null: 0) acquires an
    // effect of this data (CKSrvFx::AcquireFx inlined: reserved, owned by this data, started) and fires it from the
    // object: turned to the at row of its quaternion's matrix (+0x10), placed at its position (+0x04), triggered and
    // released (vt+0x54); returns 0. Other messages return 1.
    int32_t MessageProc(uint16_t message, void* data) override;
    // vt+0x24 0x001d1548 RecursiveRegistration: IKFxData's (KStub_Return1_1d8340): nothing. vt+0x40 0x001d15f0 GetInfo: 1
    // (the defaults). 0x001d19e8 / 0x001d1a28 destructors and 0x001d1570 the deleting one: the C++ chain.

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x001d1a68 CKShockWaveFxData_Load
    // vt+0x30 0x001d1500 CKShockWaveFxData_PostLoad (any type): IKFxData's (KStub_Return1_1d8338), then the radius factor
    // back to 1.0 (TOC -0x1ab0 = 0x3f800000) and no damage; returns 1.
    int32_t PostLoad(int32_t type) override;
    uint32_t GetAssociatedFxClassIdentifier() override { return 0x30cc; }  // vt+0x54 0x1d12b0

    // 0x001d12b8 CKShockWaveFxData_EvalRadiusScale_maybe / 0x001d1388 _EvalHeightScale_maybe / 0x001d1458 _EvalAlpha_maybe:
    // the key list +0x1c / +0x14 / +0x24 at `time` / the duration (+0x08), linear between keys (a time from one key up to
    // the next), the last key's value outside; the radius times +0x2c with +0x30 bit 1, the height times +0x28 with bit 0.
    float EvalRadiusScale(float time) const;
    float EvalHeightScale(float time) const;
    float EvalAlpha(float time) const;

    float m_unk08;          // +0x08 the duration
    float m_unk0c;          // +0x0c
    uint32_t m_unk10;       // +0x10 the number of keys in +0x14 (read second)
    Key* m_unk14;           // +0x14 the constructor sets 0
    uint32_t m_unk18;       // +0x18 the number of keys in +0x1c (read first)
    Key* m_unk1c;           // +0x1c the constructor sets 0
    uint32_t m_unk20;       // +0x20 the number of keys in +0x24 (read third)
    Key* m_unk24;           // +0x24 the constructor sets 0
    uint32_t m_unk28;       // +0x28 not read
    float m_unk2c;          // +0x2c the radius factor (EvalRadiusScale with +0x30 bit 1); PostLoad sets 1.0
    uint8_t m_unk30;        // +0x30
    uint8_t m_pad31[3];
    float m_unk34;          // +0x34
    float m_unk38;          // +0x38
    IKSerializable* m_pDamage3c;  // +0x3c the damage of the shock wave sphere (Trigger); the constructor and PostLoad set 0
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
DOTD_ASSERT_OFFSET(CKShockWaveFxData, m_pDamage3c, 0x3c);
DOTD_ASSERT_OFFSET(CKShockWaveFxData, m_unk40, 0x40);
