// CKQuakeCpnt.h - a camera quake: a list of curve-driven entries (key 0x364c, vtable 0xb20ef8, size 0x14).
// Original unit: CKQuakeCpnt.cpp (0x24df08-0x24ebb8). XXL2 registers this key as CKCameraQuakeDatas
// (KServiceCamera), but with another layout (two CVector2 arrays and an amplitude scale), so none of its
// member names is used here.
#pragma once
#include <cstdint>

#include "k2000/components/IKComponent.h"
#include "k2000/core/Layout.h"
#include "k2000/util/TVector.h"

class CKQuakeCpntUpdater;

class CKQuakeCpnt : public IKComponent {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0xd9)
    DOTD_DECLARE_FACTORIES(CKQuakeCpnt)

    // 0x1c bytes on the PS3: a curve reference, then six words, all byte-swapped. CKQuakeCpnt_Evaluate_maybe 0x24e310
    // reads them: the channel bits 0..14 say which of the 15 outputs the curve's value goes to, scaled by the
    // amplitude of its group (bits 0-2 +0x08, 3-5 +0x0c, 6-8 +0x10, 9-14 +0x14); the entry starts at +0x18 seconds.
    // In the camera's use (CKSrvCamera_ApplyCameraEffects_maybe) outputs 0-2 move the pose along the view axes and
    // 3-5 turn it about them (degrees).
    struct Entry {
        IKComponent* m_pCurve;       // +0x00 a CKSinCurve2DCpnt
        uint32_t m_ui32Channels;     // +0x04 the output bits
        float m_fAmplitude0;         // +0x08 outputs 0-2
        float m_fAmplitude3;         // +0x0c outputs 3-5
        float m_fAmplitude6;         // +0x10 outputs 6-8
        float m_fAmplitude9;         // +0x14 outputs 9-14
        float m_fStartTime;          // +0x18 seconds after the start
    };

    CKQuakeCpnt();  // 0x0024e130 CKQuakeCpnt_Create (the constructor is inlined there)

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x0024e840 CKQuakeCpnt_Load
    // vt+0x30 PostLoad 0x24e2f8 returns 1.

    // 0x0024e180 CKQuakeCpnt_StartUpdater_maybe / 0x0024dfe0 CKQuakeCpnt_StopUpdater_maybe: `effect` running (1) / stopped (0), its
    // time 0 and every entry's state started / reset.
    void StartEffect(CKQuakeCpntUpdater* effect) const;
    void StopEffect(CKQuakeCpntUpdater* effect) const;
    // 0x0024e310 CKQuakeCpnt_Evaluate_maybe: the 15 outputs of `effect` after dt more seconds (zero when it is not
    // running). Past the duration the effect stops (its states reset, the outputs stay zero).
    void Evaluate(float dt, float out[15], CKQuakeCpntUpdater* effect) const;

    float m_fDuration;              // +0x04 seconds
    TVector<Entry, 1> m_entries;    // +0x08 the constructor: null, 1, 0
};
DOTD_ASSERT_SIZE(CKQuakeCpnt::Entry, 0x1c);
DOTD_ASSERT_SIZE(CKQuakeCpnt, 0x14);
DOTD_ASSERT_OFFSET(CKQuakeCpnt, m_fDuration, 0x04);
DOTD_ASSERT_OFFSET(CKQuakeCpnt, m_entries, 0x08);
