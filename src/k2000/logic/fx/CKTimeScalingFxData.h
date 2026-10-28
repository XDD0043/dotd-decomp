// CKTimeScalingFxData.h - a game-time scaling effect (slow motion) with a key list (key 0x264c, vtable
// 0xb1db30, size 0x1c). Original unit: CKTimeScalingFxData.cpp (0x1d7298-0x1d7d50). No XXL2 class of this
// name.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/logic/IKFxData.h"

class CKTimeScalingFxData : public IKFxData {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x99)
    DOTD_DECLARE_FACTORIES(CKTimeScalingFxData)

    // Two byte-swapped words (LVL000: 1.0, 0.075 / 0.21, 0.5, ...: a time and a scale, _maybe).
    struct Key {
        float m_unk00;
        float m_unk04;
    };

    CKTimeScalingFxData() {}  // 0x001d75c8 CKTimeScalingFxData_Create: IKFxData, then the vtable

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x001d7b40 CKTimeScalingFxData_Load
    // vt+0x30 PostLoad 0x1d7400 calls IKFxData's (returns 1).
    int32_t Vf50() override { return 1; }                                  // vt+0x50 0x9ad698
    uint32_t GetAssociatedFxClassIdentifier() override { return 0x27cc; }  // vt+0x54 0x1d72e8
    // vt+0x1c 0x001d7618 CKTimeScalingFxData_MessageProc: 0x1b00 starts the effect (CKSrvFx::StartEffect, the data as owner),
    // 0x1b01 stops the unique CKTimeScalingNodeFx if it runs this data; returns 0 for 0x1b00, 1 otherwise.
    int32_t MessageProc(uint16_t message, void* data) override;
    // 0x001d72f0 CKTimeScalingFxData_EvaluateScaleCurve_maybe: the scale at time t, linear between the two keys around it;
    // 1 (TOC -0x18fc) without keys or outside them.
    float EvaluateScaleCurve(float t) const;

    uint8_t m_unk08;     // +0x08
    uint8_t m_pad09[3];
    float m_unk0c;       // +0x0c
    uint32_t m_unk10;    // +0x10
    Key* m_pKeys;        // +0x14 Mem_AllocAligned16(count * 8)
    uint8_t m_nbKeys;    // +0x18
    uint8_t m_pad19[3];
};
DOTD_ASSERT_SIZE(CKTimeScalingFxData::Key, 0x8);
DOTD_ASSERT_SIZE(CKTimeScalingFxData, 0x1c);
DOTD_ASSERT_OFFSET(CKTimeScalingFxData, m_unk08, 0x08);
DOTD_ASSERT_OFFSET(CKTimeScalingFxData, m_unk0c, 0x0c);
DOTD_ASSERT_OFFSET(CKTimeScalingFxData, m_unk10, 0x10);
DOTD_ASSERT_OFFSET(CKTimeScalingFxData, m_pKeys, 0x14);
DOTD_ASSERT_OFFSET(CKTimeScalingFxData, m_nbKeys, 0x18);
