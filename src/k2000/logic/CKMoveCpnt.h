// CKMoveCpnt.h - a node movement built from 2D curves (key 0x968c, category logic, vtable 0xb20e48, size
// 0x34; an IKComponent: IsKindOfClass 0x9ba000 tests 0x968c, 0x6 and 0xc). Original unit: CKMoveCpnt.cpp
// (0x24c378-0x24d2a8). No XXL2 class of this name.
#pragma once
#include <cstdint>

#include "k2000/components/IKComponent.h"
#include "k2000/core/Layout.h"
#include "k2000/math/CMatrix34.h"
#include "k2000/util/TVector.h"

class CKMoveCpntUpdater;

class CKMoveCpnt : public IKComponent {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x25a)
    int32_t IsKindOfClass(uint32_t key) override {  // vt+0x08 0x9ba000
        return key == 0x968c || key == 0x6 || key == 0xc;
    }
    DOTD_DECLARE_FACTORIES(CKMoveCpnt)

    // One track: a curve and four words, all byte-swapped (LVL010: CKCurve2DCpnt refs, 1/2/4, 3.0, pi/2,
    // 0.1, 0) _maybe an axis mask and the curve's scale/range.
    struct Track {
        IKSerializable* m_pCurve;  // +0x00 CKCurve2DCpnt (the files' refs are of key 0x5ac6)
        uint32_t m_unk04;          // +0x04 the sample channels the curve adds to (Sample): bits 0-2 the
                                   // translation, 3-5 the rotations, 6 the path distance, 7-9 the scales
        float m_unk08;             // +0x08 the translations' scale
        float m_unk0c;             // +0x0c the rotations' scale
        float m_unk10;             // +0x10 the scales' scale
        float m_unk14;             // +0x14 the track's start time (Sample skips it before; the curve gets the time since)
    };

    // 0x0024cb48 CKMoveCpnt_Create (inlined constructor): the track vector null, 1, 0; nothing else.
    CKMoveCpnt() {
        m_vTracks.m_pBlock = nullptr;
        m_vTracks.m_ui32NbElt = 1;
        m_vTracks.m_ui32NbUsedElt = 0;
    }

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x0024ccb8 CKMoveCpnt_Load
    // vt+0x10 0x0024cbb0 CKMoveCpnt_Destroy: the matrix (+0x18) destroyed and forgotten. (vt+0x24 0x0024cba0
    // RecursiveRegistration and vt+0x30 0x0024cba8 PostLoad: 1, the inherited defaults.)
    void Destroy() override;

    // The playback state lives in the updater (+0x08 running, +0x09 paused, +0x0c time); these drive it.
    // 0x0024c3c8 CKMoveCpnt_ResetUpdater: stopped, not paused, time 0.
    static void ResetUpdater(CKMoveCpntUpdater* updater);
    // 0x0024c3e0 CKMoveCpnt_PauseUpdater / 0x0024c3f0 CKMoveCpnt_ResumeUpdater: the paused byte 1 / 0.
    static void PauseUpdater(CKMoveCpntUpdater* updater);
    static void ResumeUpdater(CKMoveCpntUpdater* updater);
    // 0x0024c400 CKMoveCpnt_ResetTrackTimeToStart_maybe: the flagged path's (+0x10) cursor (+0x0c) reset (0, or the
    // path's length when that is negative).
    void ResetTrackTime();
    // 0x0024c528 CKMoveCpnt_Sample: the ten channels at `time` into `out` (zeroed first) while the updater runs. At or
    // past the duration (+0x04) a looping movement (+0x08) wraps the time, another clamps it to the duration and, with
    // +0x09, resets the updater after the sample. Every track started by then (its +0x14 at most the time) adds its
    // curve at (time - start) times its scale to its channels. Returns whether the end was crossed this call (the
    // time reached the duration while the updater's previous time was below it).
    uint8_t Sample(float time, float* out, CKMoveCpntUpdater* updater) const;
    // 0x0024c988 CKMoveCpnt_Advance: while the updater runs, its time plus `dt` (unless paused) sampled. 0 otherwise
    // (`out` untouched).
    uint8_t Advance(float dt, float* out, CKMoveCpntUpdater* updater) const;
    // 0x0024cbf8 CKMoveCpnt_StartUpdater: running, not paused, time 0, the path object's distance reset.
    void StartUpdater(CKMoveCpntUpdater* updater);

    float m_unk04;           // +0x04 (LVL010: 10.0) _maybe the duration
    uint8_t m_unk08;         // +0x08
    uint8_t m_unk09;         // +0x09
    uint8_t m_pad0a[2];
    IKSerializable* m_pUnk0c;  // +0x0c reference (null in the LVL010 samples): a path (vt+0x54 position at a distance,
                               // vt+0x5c its length) the channel 6 moves along
    IKSerializable* m_pUnk10;  // +0x10 reference: a CKFlaggedPath (ApplySampleToMatrix calls
                               // CKFlaggedPath_SetDistanceAndGetPosition on it; +0x04 its path, +0x0c the cursor)
    uint8_t m_unk14;         // +0x14
    uint8_t m_unk15;         // +0x15
    uint8_t m_unk16;         // +0x16
    uint8_t m_pad17;
    CMatrix34* m_pMatrix;    // +0x18 RwMatrixCreate + CMatrix34_LoadMatrix when the file's flag byte is set, else 0
    float m_unk1c[3];        // +0x1c..+0x27 three swapped words (_maybe a vector)
    TVector<Track, 1> m_vTracks;  // +0x28
};
DOTD_ASSERT_SIZE(CKMoveCpnt::Track, 0x18);
DOTD_ASSERT_SIZE(CKMoveCpnt, 0x34);
DOTD_ASSERT_OFFSET(CKMoveCpnt, m_unk04, 0x04);
DOTD_ASSERT_OFFSET(CKMoveCpnt, m_unk08, 0x08);
DOTD_ASSERT_OFFSET(CKMoveCpnt, m_pUnk0c, 0x0c);
DOTD_ASSERT_OFFSET(CKMoveCpnt, m_pUnk10, 0x10);
DOTD_ASSERT_OFFSET(CKMoveCpnt, m_unk14, 0x14);
DOTD_ASSERT_OFFSET(CKMoveCpnt, m_pMatrix, 0x18);
DOTD_ASSERT_OFFSET(CKMoveCpnt, m_unk1c, 0x1c);
DOTD_ASSERT_OFFSET(CKMoveCpnt, m_vTracks, 0x28);
