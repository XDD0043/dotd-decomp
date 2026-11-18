// CKQuakeCpntUpdater.cpp - reconstructed original translation unit 0x24ebb8-0x24fba0 (GAME_TOC1, main_toc1), 19 functions, 19 live.
// Primary class: CKQuakeCpntUpdater  key 0x986  category Component  size 0x20  vtable 0xb20f50
// Other owners: ShakeSample (3), ShakeEffect (3)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x24ebb8  CKQuakeCpntUpdater_Delete
//   [x] 0x24ec08  ShakeSample_ApplyToElement2d_maybe
//   [x] 0x24ee00  CKQuakeCpntUpdater_GetQuakeCpnt_maybe  (GetQuakeCpnt, the header; its caller path is not ported)
//   [ ] 0x24ee08  RegisterCKQuakeCpntUpdaterClass
//   [ ] 0x24ee80  _GLOBAL__I_24ee80
//   [x] 0x24ee90  ShakeSample_BuildMatrix_maybe
//   [ ] 0x24f578  ShakeSample_ApplyToNode_maybe  [dead: no pointer to its descriptor 0xb83b48]
//   [x] 0x24f5c8  CKQuakeCpntUpdater_EvaluateScaled
//   [x] 0x24f738  CKQuakeCpntUpdater_Stop
//   [x] 0x24f770  CKQuakeCpntUpdater_Start
//   [x] 0x24f7a8  CKQuakeCpntUpdater_DeleteArray
//   [x] 0x24f848  CKQuakeCpntUpdater_Create
//   [x] 0x24f898  CKQuakeCpntUpdater_CreateArray
//   [x] 0x24f958  CKQuakeCpntUpdater_Load
//   [ ] 0x24f9e8  CKQuakeCpntUpdater_Save
//   [x] 0x24f9f0  CKQuakeCpntUpdater_RecursiveRegistration  (returns 1, registers nothing: the default)
//   [x] 0x24f9f8  CKQuakeCpntUpdater_Destroy  (empty: the default)
//   [x] 0x24fa00  CKQuakeCpntUpdater_AllocCurveStates_maybe
//   [x] 0x24fb60  CKQuakeCpntUpdater_PostLoad
//
//   [ ] 0x9ba298  CKQuakeCpntUpdater_IsKindOfClass  [inline]
//   [x] 0x9ba2c0  CKQuakeCpntUpdater_GetClassType  [inline]
//   [x] 0x9ba2c8  CKQuakeCpntUpdater_GetClassID  [inline]
//   [ ] 0x9ba2d0  CKQuakeCpntUpdater_Destructor  [inline]
//   [ ] 0x9ba328  CKQuakeCpntUpdater_DeletingDestructor  [inline]
#include "k2000/components/CKQuakeCpntUpdater.h"

#include "Spyro2008/logic/KBase730C.h"
#include "k2000/io/IKFile.h"
#include "k2000/ui/IKNode2d.h"
#include "k2000/memory/Mem.h"
#include "k2000/misc/Mat4.h"
#include "crt/ppc_ops.h"

#include <cmath>

// 0x0024f848 CKQuakeCpntUpdater_Create, the inlined constructor: the curve-state list only.
CKQuakeCpntUpdater::CKQuakeCpntUpdater() {
    m_curveStates.m_pBlock = nullptr;
    m_curveStates.m_ui32NbElt = 1;
    m_curveStates.m_ui32NbUsedElt = 0;
}

// 0x0024f958 CKQuakeCpntUpdater_Load
int32_t CKQuakeCpntUpdater::Load(IKFile* file, int32_t type) {
    if (type == K_LEVEL_PLATEFORMS) IKFile_ReadRef(file, &m_pQuake);
    return 1;
}

// 0x0024fb60 CKQuakeCpntUpdater_PostLoad: for type 0 (the level) the effect stopped and its states allocated.
int32_t CKQuakeCpntUpdater::PostLoad(int32_t type) {
    if (type == 0) {
        m_fElapsed = 0.0f;
        m_bRunning = 0;
        AllocCurveStates();
    }
    return 1;
}

// 0x0024fa00 CKQuakeCpntUpdater_AllocCurveStates_maybe
void CKQuakeCpntUpdater::AllocCurveStates() {
    if (m_pQuake != nullptr && m_pQuake->m_entries.m_ui32NbUsedElt != 0) {
        if (m_curveStates.m_pBlock != nullptr) Mem_FreeAligned16(m_curveStates.m_pBlock);
        m_curveStates.m_ui32NbUsedElt = 0;
        m_curveStates.m_pBlock = nullptr;
        const uint32_t count = m_pQuake->m_entries.m_ui32NbUsedElt;
        m_curveStates.m_ui32NbElt = count;
        m_curveStates.m_pBlock =
            static_cast<CurveState*>(Mem_AllocAligned16(count * static_cast<uint32_t>(sizeof(CurveState))));
        if (m_curveStates.m_ui32NbElt < count) {  // as in the original: cannot happen right after the assignment
            const uint32_t capacity = count + 1;
            if (capacity == 0) {
                m_curveStates.m_pBlock = static_cast<CurveState*>(
                    Mem_ReallocAligned16(m_curveStates.m_pBlock, static_cast<uint32_t>(sizeof(CurveState))));
                m_curveStates.m_ui32NbElt = 1;
            } else {
                m_curveStates.m_pBlock = static_cast<CurveState*>(
                    Mem_ReallocAligned16(m_curveStates.m_pBlock, capacity * static_cast<uint32_t>(sizeof(CurveState))));
                m_curveStates.m_ui32NbElt = capacity;
            }
        }
        m_curveStates.m_ui32NbUsedElt = count;
        return;
    }
    if (m_curveStates.m_pBlock != nullptr) Mem_FreeAligned16(m_curveStates.m_pBlock);
    m_curveStates.m_ui32NbElt = 1;
    m_curveStates.m_ui32NbUsedElt = 0;
    m_curveStates.m_pBlock = nullptr;
    m_curveStates.m_pBlock = static_cast<CurveState*>(Mem_AllocAligned16(static_cast<uint32_t>(sizeof(CurveState))));
}

// 0x0024f770 CKQuakeCpntUpdater_Start
void CKQuakeCpntUpdater::Start() {
    if (m_pQuake != nullptr) m_pQuake->StartEffect(this);
}

// 0x0024f738 CKQuakeCpntUpdater_Stop
void CKQuakeCpntUpdater::Stop() {
    if (m_pQuake != nullptr) m_pQuake->StopEffect(this);
}

// 0x0024f5c8 CKQuakeCpntUpdater_EvaluateScaled
void CKQuakeCpntUpdater::EvaluateScaled(float dt, float scale, float out[15]) {
    if (m_pQuake == nullptr) {
        for (int32_t i = 0; i < 15; ++i) out[i] = 0.0f;
        return;
    }
    m_pQuake->Evaluate(dt, out, this);
    for (int32_t i = 0; i < 15; ++i) out[i] = out[i] * scale;
}

// 0x0024ec08 ShakeSample_ApplyToElement2d_maybe. 0.0 is TOC+0x50, the scale floor 0.01 TOC+0x4c.
void ShakeSample_ApplyToElement2d(const float out[15], KBase730C* menu, uint32_t slot) {
    IKNode2d* node = static_cast<IKNode2d*>(menu->GetWidgetSlots()[slot].m_pElement);
    if (out[0] != 0.0f) menu->SetElementX(menu->GetElementX(slot) + out[0], slot);
    if (out[1] != 0.0f) menu->SetElementY(menu->GetElementX(slot) + out[1], slot);  // BUG(original): GetElementX
    if (out[5] != 0.0f) node->m_f32RotateAngle = out[5] + node->m_f32RotateAngle;
    if (out[6] != 0.0f) {
        const float scale = out[6] + node->m_v2ConstantScale.m_fX;
        node->m_v2ConstantScale.m_fX = scale < 0.01f ? 0.01f : scale;
    }
    if (out[7] != 0.0f) {
        const float scale = out[7] + node->m_v2ConstantScale.m_fY;
        node->m_v2ConstantScale.m_fY = scale < 0.01f ? 0.01f : scale;
    }
}

// 0x0024ee90 ShakeSample_BuildMatrix_maybe. TOC +0x78 1.0, +0x50 0.0, +0x4c the scale floor 0.01, +0x7c the null vector
// 0x00c50d64. The updater (r3) is not read. Outputs exactly 0.0 are skipped (a NaN is applied).
void ShakeSample_BuildMatrix(const CKQuakeCpntUpdater* /*updater*/, const float out[15], CMatrix34* result,
                             const CMatrix34* base) {
    CMatrix34 identity;
    if (base == nullptr) {
        identity.m_pos = {0.0f, 0.0f, 0.0f};
        identity.m_ui32Flags = 0x20003u;
        identity.m_at.z = 1.0f;
        identity.m_up.y = 1.0f;
        identity.m_right.x = 1.0f;
        identity.m_up.x = 0.0f;
        identity.m_right.z = 0.0f;
        identity.m_right.y = 0.0f;
        identity.m_at.y = 0.0f;
        identity.m_at.x = 0.0f;
        identity.m_up.z = 0.0f;
        base = &identity;
    }
    // The offset along the base's axes (outputs 0..2).
    float x = 0.0f, y = 0.0f, z = 0.0f;  // the null vector
    const CVector3* axes[3] = {&base->m_right, &base->m_up, &base->m_at};
    for (int32_t i = 0; i < 3; ++i) {
        const float o = out[i];
        if (o == 0.0f) continue;
        z = ppc::fmadds(o, axes[i]->z, z);
        x = ppc::fmadds(o, axes[i]->x, x);
        y = ppc::fmadds(o, axes[i]->y, y);
    }
    // The rotation about the base's axes (outputs 3..5, Mat4_RotateInPlace 0x240498).
    CMatrix34 local;
    local.m_at.z = 1.0f;
    local.m_ui32Flags = 0x20003u;
    local.m_up.y = 1.0f;
    local.m_right.x = 1.0f;
    local.m_up.x = 0.0f;
    local.m_right.z = 0.0f;
    local.m_right.y = 0.0f;
    local.m_at.y = 0.0f;
    local.m_at.x = 0.0f;
    local.m_up.z = 0.0f;
    local.m_pos = {0.0f, 0.0f, 0.0f};
    if (out[3] != 0.0f) Mat4_RotateInPlace(&local, &base->m_right, out[3]);
    if (out[4] != 0.0f) Mat4_RotateInPlace(&local, &base->m_up, out[4]);
    if (out[5] != 0.0f) Mat4_RotateInPlace(&local, &base->m_at, out[5]);
    // The scale (outputs 6..8 plus 1, at least the floor). The branch order makes a NaN scale clamp only after a clamped
    // one (bge) and stay otherwise (blt).
    if (out[6] != 0.0f || out[7] != 0.0f || out[8] != 0.0f) {
        const float floor = 0.01f;
        float sx = out[6] + 1.0f;
        bool clamped = !(sx >= floor);
        if (clamped) sx = floor;
        float sy = out[7] + 1.0f;
        clamped = clamped ? !(sy >= floor) : sy < floor;
        if (clamped) sy = floor;
        float sz = out[8] + 1.0f;
        clamped = clamped ? !(sz >= floor) : sz < floor;
        if (clamped) sz = floor;
        const float x0 = sx * (sx * (base->m_up.x * base->m_up.x));
        const float y0 = sy * (base->m_up.y * base->m_up.y) * sy;
        const float z0 = sz * (base->m_up.z * base->m_up.z) * sz;
        const float x1 = ppc::fmadds(sx, sx * (base->m_right.x * base->m_right.x), x0);
        const float y1 = ppc::fmadds(sy, sy * (base->m_right.y * base->m_right.y), y0);
        const float z1 = ppc::fmadds(sz, sz * (base->m_right.z * base->m_right.z), z0);
        const float lx = std::sqrt(ppc::fmadds(sx, sx * (base->m_at.x * base->m_at.x), x1));  // 0x00010690 Math_Sqrtf
        const float ly = std::sqrt(ppc::fmadds(sy, sy * (base->m_at.y * base->m_at.y), y1));
        const float lz = std::sqrt(ppc::fmadds(sz, sz * (base->m_at.z * base->m_at.z), z1));
        local.m_right = {lx * local.m_right.x, lx * local.m_right.y, lx * local.m_right.z};
        local.m_up = {ly * local.m_up.x, ly * local.m_up.y, ly * local.m_up.z};
        local.m_at = {lz * local.m_at.x, lz * local.m_at.y, lz * local.m_at.z};
        local.m_ui32Flags &= 0xfffdfffeu;
    }
    // The shear (outputs 9..14): each axis moved along the base's other two.
    struct Shear {
        CVector3 CMatrix34::*row;
        CVector3 CMatrix34::*along;
    };
    static const Shear kShears[6] = {{&CMatrix34::m_right, &CMatrix34::m_up}, {&CMatrix34::m_right, &CMatrix34::m_at},
                                     {&CMatrix34::m_up, &CMatrix34::m_right},  {&CMatrix34::m_up, &CMatrix34::m_at},
                                     {&CMatrix34::m_at, &CMatrix34::m_right},  {&CMatrix34::m_at, &CMatrix34::m_up}};
    for (int32_t i = 0; i < 6; ++i) {
        const float o = out[9 + i];
        if (o == 0.0f) continue;
        CVector3& row = local.*(kShears[i].row);
        const CVector3& along = base->*(kShears[i].along);
        local.m_ui32Flags &= 0xfffdfffcu;
        row = {ppc::fmadds(o, along.x, row.x), ppc::fmadds(o, along.y, row.y), ppc::fmadds(o, along.z, row.z)};
    }
    result->m_right = {1.0f, 0.0f, 0.0f};
    result->m_at = {0.0f, 0.0f, 1.0f};
    result->m_up = {0.0f, 1.0f, 0.0f};
    result->m_pos = {0.0f, 0.0f, 0.0f};
    result->m_ui32Flags = 0x20003u;
    Mat4_TransformPostConcat(result, &local);  // 0x0023f760
    result->m_pos = {x, y, z};
    result->m_ui32Flags &= ~0x20000u;
}
