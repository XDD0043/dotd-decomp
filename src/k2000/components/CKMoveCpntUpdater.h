// CKMoveCpntUpdater.h - drives a CKMoveCpnt on a node (key 0x12c6, vtable 0xb20ea0, size 0x10). Original
// unit: CKMoveCpntUpdater.cpp (0x24d2a8-0x24df50). No XXL2 class of this name.
#pragma once
#include <cstdint>

#include "k2000/components/IKComponent.h"
#include "k2000/core/Layout.h"

class CKMoveCpnt;
class CSGMovable;
struct CMatrix34;

class CKMoveCpntUpdater : public IKComponent {
public:
    DOTD_CLASS_KEY(kCategoryComponent, 0x4b)
    int32_t IsKindOfClass(uint32_t key) override {  // vt+0x08 0x9ba0f8
        return key == 0x12c6 || key == 0x6 || key == 0xc;
    }
    DOTD_DECLARE_FACTORIES(CKMoveCpntUpdater)

    CKMoveCpntUpdater() {}  // 0x0024dd70 CKMoveCpntUpdater_Create: the vtable only

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x0024de48 CKMoveCpntUpdater_Load
    // vt+0x30 0x0024ded8 CKMoveCpntUpdater_PostLoad: for type 0 the running byte and the time cleared. Returns 1.
    int32_t PostLoad(int32_t type) override {
        if (type == K_LEVEL_PLATEFORMS) {
            m_bRunning = 0;
            m_fTime = 0.0f;  // stw 0
        }
        return 1;
    }
    // vt+0x10 0x24df00 Destroy (empty) and vt+0x24 0x24def8 RecursiveRegistration (returns 1): the defaults.
    CKMoveCpnt* GetMoveCpnt() const { return m_pMoveCpnt; }  // 0x0024d2a8 CKMoveCpntUpdater_GetMoveCpnt

    // 0x0024d9c0 CKMoveCpntUpdater_ApplyToNode: the node's modelling matrix moved by the sample
    // (ApplySampleToMatrix), then set back (CSGMovable_SetLocalMatrix_maybe 0xd0be8).
    void ApplyToNode(const float* sample, CSGMovable* node) const;
    // 0x0024d338 CKMoveCpnt_ApplySampleToMatrix_maybe: `matrix` moved by the sample: the path placement first (a path
    // +0x0c or a flagged path +0x10 at channel 6's distance: the position moved by the point less +0x1c, or the
    // matrix +0x18 times the path's frame post-concatenated; by +0x14 / +0x15 / +0x16), then the translation along the matrix's own axes
    // (channels 0-2), the rotations about them (3-5, Mat4_RotateInPlace on an identity), post-concatenated, the axes
    // scaled by 1 + channels 7-9 (at least 0.01; all 1 when the three are 0) and the translated position put back.
    void ApplySampleToMatrix(const float* sample, CMatrix34* matrix) const;
    // 0x0024db60 CKMoveCpntUpdater_Evaluate: CKMoveCpnt_Advance with this updater; without a movement the ten channels
    // zeroed and 0.
    uint8_t Evaluate(float dt, float* out);
    // 0x0024dad0 CKHkMovingObject_SampleMoveCpnt_maybe (unit CKMoveCpntUpdater.cpp): the movement sampled at `time`
    // (CKMoveCpnt_Sample with this updater); without a movement the ten channels zeroed and 0.
    uint8_t SampleMoveCpnt(float time, float* out);
    void Resume();       // 0x0024dbf0 CKMoveCpntUpdater_Resume (with a movement)
    void Pause();        // 0x0024dc28 CKMoveCpntUpdater_Pause
    void Stop();         // 0x0024dc60 CKMoveCpntUpdater_Stop: CKMoveCpnt_ResetUpdater
    void Start();        // 0x0024dc98 CKMoveCpntUpdater_Start: CKMoveCpnt_StartUpdater
    void SetMoveCpnt(CKMoveCpnt* cpnt) { m_pMoveCpnt = cpnt; }  // 0x0024dda8

    CKMoveCpnt* m_pMoveCpnt;  // +0x04 (CKMoveCpntUpdater_GetMoveCpnt 0x24d2a8; LVL010 refs of key 0x968c)
    uint8_t m_bRunning;       // +0x08 runtime (CKMoveCpnt_StartUpdater 1, ResetUpdater 0); not set by the constructor
    uint8_t m_bPaused;        // +0x09 runtime (Pause/Resume)
    uint8_t m_pad0a[2];
    float m_fTime;            // +0x0c runtime: the movement's time (CKMoveCpnt_Sample)
};
DOTD_ASSERT_SIZE(CKMoveCpntUpdater, 0x10);
DOTD_ASSERT_OFFSET(CKMoveCpntUpdater, m_pMoveCpnt, 0x04);
DOTD_ASSERT_OFFSET(CKMoveCpntUpdater, m_bRunning, 0x08);
DOTD_ASSERT_OFFSET(CKMoveCpntUpdater, m_bPaused, 0x09);
DOTD_ASSERT_OFFSET(CKMoveCpntUpdater, m_fTime, 0x0c);
