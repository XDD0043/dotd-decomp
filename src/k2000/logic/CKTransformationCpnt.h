// CKTransformationCpnt.h - a list of curve-driven transformation entries (key 0xa80c, vtable 0xb210b0,
// size 0x14). Original unit: CKTransformationCpnt.cpp (0x251628-0x2520c0). No XXL2 class of this name.
#pragma once
#include <cstdint>

#include "k2000/components/IKComponent.h"
#include "k2000/core/Layout.h"
#include "k2000/util/TVector.h"

class CKTransformationCpntUpdater;

// The output of CKTransformationCpnt_Evaluate_maybe (0x2d bytes used, 0x30 with the padding: the first part of a gauge sample): nine
// channels (entry bits 0..8: 0-2 scaled by the entry's +0x08, 3-5 by +0x0c, 6-8 by +0x10) and a "set" byte per channel.
// The 2D use (GaugeSample_ApplyToElement2d_maybe): 0 x, 1 y, 5 rotation, 6 / 7 the constant scale (2-4, 8 unused).
struct TransformSample {
    float m_af[9];        // +0x00
    uint8_t m_abSet[9];   // +0x24
};

class CKTransformationCpnt : public IKComponent {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x2a0)
    int32_t IsKindOfClass(uint32_t key) override {  // vt+0x08 0x9ba528
        return key == 0xa80c || key == 0x6 || key == 0xc;
    }
    DOTD_DECLARE_FACTORIES(CKTransformationCpnt)

    // 0x18 bytes on the PS3: a curve reference, then five words, all byte-swapped. The types of the
    // words are from the data (LVL000: 0x40, then 0.5, pi/2, 3.09, 0.0; _maybe).
    struct Entry {
        IKComponent* m_pCurve;  // +0x00 a curve (CKCurve2DCpnt in LVL000)
        uint32_t m_unk04;       // +0x04
        float m_unk08;          // +0x08
        float m_unk0c;          // +0x0c
        float m_unk10;          // +0x10
        float m_unk14;          // +0x14
    };

    CKTransformationCpnt();  // 0x00251c00 CKTransformationCpnt_Create (the constructor is inlined there)

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x00251d38 CKTransformationCpnt_Load
    // vt+0x30 PostLoad 0x251d20 returns 1.

    // 0x00251678 CKTransformationCpnt_StartUpdater_maybe: `updater` running (+0x08 = 1, +0x09 = 0), its time 0.
    void StartUpdater(CKTransformationCpntUpdater* updater) const;
    // 0x00251758 CKTransformationCpnt_Evaluate_maybe: `out` cleared, then (while `updater` runs) every entry whose start
    // time (+0x14) the updater's time `t` has reached adds its curve at (t - start) times its scale to the channels of its
    // bits. Returns 1 when `t` passes the duration (+0x04) in this call (the previous time below it).
    uint8_t Evaluate(float t, TransformSample* out, CKTransformationCpntUpdater* updater) const;

    float m_unk04;                  // +0x04 the duration
    TVector<Entry, 1> m_entries;    // +0x08 the constructor: null, 1, 0
};
DOTD_ASSERT_SIZE(CKTransformationCpnt::Entry, 0x18);
DOTD_ASSERT_SIZE(CKTransformationCpnt, 0x14);
DOTD_ASSERT_OFFSET(CKTransformationCpnt, m_unk04, 0x04);
DOTD_ASSERT_OFFSET(CKTransformationCpnt, m_entries, 0x08);
