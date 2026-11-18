// CKTrailShockWaveFxData.h - the data of a trailing shock wave (key 0x448c, vtable 0xb2de28, size 0x110). Original unit:
// CKTrailShockWaveFxData.cpp (0x5721e0-0x572e48). Its node CKTrailShockWaveNodeFx (0x444c) is not ported yet; the
// fields are named from its TriggerAt (0x5734f8) and Update (0x573fd0) reads. Not in XXL2; names ours.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/logic/IKFxData.h"

class CKTrailShockWaveFxData : public IKFxData {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x112)
    int32_t IsKindOfClass(uint32_t key) override {  // vt+0x08 0x9cadc8
        return key == 0x448c || key == 0x304c || key == 0x6 || key == 0xc;
    }
    DOTD_DECLARE_FACTORIES(CKTrailShockWaveFxData)

    // Inlined in 0x00572500 Create / 0x00572458 CreateArray: the vtables only.
    CKTrailShockWaveFxData() : m_unk108(nullptr), m_unk10c(0), m_unk10e(0) {}

    void Destroy() override {}                          // vt+0x10 0x00572260 (empty)
    // vt+0x24 0x00572330 RecursiveRegistration: IKFxData's (nothing). vt+0x30 0x00572308 PostLoad: IKFxData's (1).
    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x005725c8
    uint32_t GetAssociatedFxClassIdentifier() override { return 0x444c; }  // vt+0x54 0x572278

    // Three particle nodes x (start, end) x ten words: the node's emitter properties interpolated from start to end over
    // the trail (Update: words 0..7 four property pairs, 8 / 9 two more).
    float m_afParticleRanges[3][2][10];  // +0x08
    float m_fSpacing;     // +0x0f8 TriggerAt: the start point's distance along the direction; Update's progress divisor
    float m_unkFC;        // +0x0fc TriggerAt -> node +0x40
    float m_unk100;       // +0x100 TriggerAt -> node +0x3c
    float m_unk104;       // +0x104 TriggerAt -> node +0x44
    // +0x108 the damage volume's owner (+0x24; not read by Load; port-rest R07: a pointer, as the node stores it there)
    IKSerializable* m_unk108;
    uint16_t m_unk10c;    // +0x10c the damage volume's property flags (not read by Load)
    uint8_t m_unk10e;     // +0x10e the damage volume's owner type (not read by Load)
    uint8_t m_pad10f;
};
static_assert(CKTrailShockWaveFxData::kClassKey == 0x448c, "key");
DOTD_ASSERT_SIZE(CKTrailShockWaveFxData, 0x110);
DOTD_ASSERT_OFFSET(CKTrailShockWaveFxData, m_afParticleRanges, 0x08);
DOTD_ASSERT_OFFSET(CKTrailShockWaveFxData, m_fSpacing, 0xf8);
DOTD_ASSERT_OFFSET(CKTrailShockWaveFxData, m_unk108, 0x108);
