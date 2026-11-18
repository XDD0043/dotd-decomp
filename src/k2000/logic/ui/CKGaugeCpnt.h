// CKGaugeCpnt.h - a HUD gauge: two transformation components and two colour key lists (key 0xa84c,
// vtable 0xb20d40, size 0x64). Original unit: CKGaugeCpnt.cpp (0x24a0d0-0x24b248). No XXL2 class of this
// name; the field names are ours (m_unkXX).
//
// Load reads the first block for K_LEVEL_PLATEFORMS only, then +0x34..+0x28 for every type.
#pragma once
#include <cstdint>

#include "k2000/components/CKTransformationCpntUpdater.h"
#include "k2000/components/IKComponent.h"
#include "k2000/core/Layout.h"
#include "k2000/logic/CKTransformationCpnt.h"
#include "k2000/math/CurveKeys.h"
#include "k2000/util/TVector.h"

class CKGaugeCpntUpdater;

// One gauge's sample (0x38 bytes on the PS3): the transformation channels, then the colour (r, g, b, a) and whether it is
// set. CKGaugeCpnt_EvaluateSample_maybe fills it, GaugeSample_ApplyToElement2d_maybe puts it on a 2D element.
struct GaugeSample {
    TransformSample m_transform;  // +0x00
    uint8_t m_aColor[4];          // +0x30 0xffffffff when not set
    uint8_t m_bHasColor;          // +0x34
    uint8_t m_pad35[3];
};

class CKGaugeCpnt : public IKComponent {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x2a1)
    int32_t IsKindOfClass(uint32_t key) override {  // vt+0x08 0x9b9dd8
        return key == 0xa84c || key == 0x6 || key == 0xc;
    }
    DOTD_DECLARE_FACTORIES(CKGaugeCpnt)

    CKGaugeCpnt();  // 0x0024a568 CKGaugeCpnt_Create (the constructor is inlined there)

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x0024ac88 CKGaugeCpnt_Load
    // vt+0x30 PostLoad 0x24a550 returns 1.

    // 0x0024a1a8 CKGaugeCpnt_EvaluateSample_maybe: the sample at transformation time `t` (the transformation updater
    // restarted first); the colour from the key list +0x14 when +0x10, then, while the record flashes (its +0x18 with
    // +0x20), from the key list +0x28 at the flash time over the period (+0x24; 1.0 when the period is not positive).
    void EvaluateSample(float t, GaugeSample* sample, CKGaugeCpntUpdater* record) const;
    // 0x0024a340 CKGaugeCpnt_UpdateDisplayedValue_maybe: the record's displayed value (+0x08) moves to its target (+0x10):
    // rising after the delay +0x34 (mode +0x38: 0 at once, 1 at +0x3c per second), falling after the delay +0x4c (mode
    // +0x50: 0 at once, 1 at +0x54 per second); the flash time advances (clamped to the period, or wrapped with +0x21);
    // then the sample at displayed / maximum x the transformation's duration.
    void UpdateDisplayedValue(float dt, GaugeSample* sample, CKGaugeCpntUpdater* record) const;

    float m_unk04;                                  // +0x04
    CKTransformationCpnt* m_pTransformation;        // +0x08 (Ghidra draft: CKTransformationCpnt*)
    CKTransformationCpntUpdater* m_pTransformationUpdater;  // +0x0c (Ghidra draft)
    uint8_t m_unk10;                                // +0x10
    uint8_t m_pad11[3];
    TVector<CurveKey, 20> m_unk14;                  // +0x14 colour keys (CurveKeys_Load); the constructor
                                                    // allocates 20 keys
    uint8_t m_unk20;                                // +0x20
    uint8_t m_unk21;                                // +0x21
    uint8_t m_pad22[2];
    float m_unk24;                                  // +0x24
    TVector<CurveKey, 20> m_unk28;                  // +0x28 colour keys, like +0x14
    float m_unk34;                                  // +0x34 the rise delay
    uint8_t m_unk38;                                // +0x38 the rise mode
    uint8_t m_pad39[3];
    float m_unk3c;                                  // +0x3c the rise speed
    float m_unk40;                                  // +0x40
    uint8_t m_unk44;                                // +0x44
    uint8_t m_pad45[3];
    IKComponent* m_pCurve48;                        // +0x48 a curve (CKCurve2DCpnt in LVL000)
    float m_unk4c;                                  // +0x4c the fall delay
    uint8_t m_unk50;                                // +0x50 the fall mode
    uint8_t m_pad51[3];
    float m_unk54;                                  // +0x54 the fall speed
    float m_unk58;                                  // +0x58
    uint8_t m_unk5c;                                // +0x5c
    uint8_t m_pad5d[3];
    IKComponent* m_pCurve60;                        // +0x60 a curve (CKCurve2DCpnt in LVL000)
};
DOTD_ASSERT_SIZE(CKGaugeCpnt, 0x64);
static_assert(sizeof(GaugeSample) == 0x38, "GaugeSample");
DOTD_ASSERT_OFFSET(CKGaugeCpnt, m_unk04, 0x04);
DOTD_ASSERT_OFFSET(CKGaugeCpnt, m_pTransformation, 0x08);
DOTD_ASSERT_OFFSET(CKGaugeCpnt, m_pTransformationUpdater, 0x0c);
DOTD_ASSERT_OFFSET(CKGaugeCpnt, m_unk10, 0x10);
DOTD_ASSERT_OFFSET(CKGaugeCpnt, m_unk14, 0x14);
DOTD_ASSERT_OFFSET(CKGaugeCpnt, m_unk20, 0x20);
DOTD_ASSERT_OFFSET(CKGaugeCpnt, m_unk21, 0x21);
DOTD_ASSERT_OFFSET(CKGaugeCpnt, m_unk24, 0x24);
DOTD_ASSERT_OFFSET(CKGaugeCpnt, m_unk28, 0x28);
DOTD_ASSERT_OFFSET(CKGaugeCpnt, m_unk34, 0x34);
DOTD_ASSERT_OFFSET(CKGaugeCpnt, m_unk38, 0x38);
DOTD_ASSERT_OFFSET(CKGaugeCpnt, m_unk3c, 0x3c);
DOTD_ASSERT_OFFSET(CKGaugeCpnt, m_unk40, 0x40);
DOTD_ASSERT_OFFSET(CKGaugeCpnt, m_unk44, 0x44);
DOTD_ASSERT_OFFSET(CKGaugeCpnt, m_pCurve48, 0x48);
DOTD_ASSERT_OFFSET(CKGaugeCpnt, m_unk4c, 0x4c);
DOTD_ASSERT_OFFSET(CKGaugeCpnt, m_unk50, 0x50);
DOTD_ASSERT_OFFSET(CKGaugeCpnt, m_unk54, 0x54);
DOTD_ASSERT_OFFSET(CKGaugeCpnt, m_unk58, 0x58);
DOTD_ASSERT_OFFSET(CKGaugeCpnt, m_unk5c, 0x5c);
DOTD_ASSERT_OFFSET(CKGaugeCpnt, m_pCurve60, 0x60);
