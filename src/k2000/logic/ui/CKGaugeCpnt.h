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

class CKGaugeCpnt : public IKComponent {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x2a1)
    DOTD_DECLARE_FACTORIES(CKGaugeCpnt)

    CKGaugeCpnt();  // 0x0024a568 CKGaugeCpnt_Create (the constructor is inlined there)

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x0024ac88 CKGaugeCpnt_Load
    // vt+0x30 PostLoad 0x24a550 returns 1.

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
    uint32_t m_unk34;                               // +0x34
    uint8_t m_unk38;                                // +0x38
    uint8_t m_pad39[3];
    float m_unk3c;                                  // +0x3c
    float m_unk40;                                  // +0x40
    uint8_t m_unk44;                                // +0x44
    uint8_t m_pad45[3];
    IKComponent* m_pCurve48;                        // +0x48 a curve (CKCurve2DCpnt in LVL000)
    float m_unk4c;                                  // +0x4c
    uint8_t m_unk50;                                // +0x50
    uint8_t m_pad51[3];
    float m_unk54;                                  // +0x54
    float m_unk58;                                  // +0x58
    uint8_t m_unk5c;                                // +0x5c
    uint8_t m_pad5d[3];
    IKComponent* m_pCurve60;                        // +0x60 a curve (CKCurve2DCpnt in LVL000)
};
DOTD_ASSERT_SIZE(CKGaugeCpnt, 0x64);
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
