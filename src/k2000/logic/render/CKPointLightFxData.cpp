// CKPointLightFxData.cpp - reconstructed original translation unit 0x1cf310-0x1cfb08 (GAME_TOC1, main_toc1), 17 functions, 17 live.
// Primary class: CKPointLightFxData  key 0xaa8c  category Logic  size 0x38  vtable 0xb1d580
// Other owners: CKPointLightNodeFx (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x1cf310  CKPointLightFxData_Delete
//   [x] 0x1cf360  CKPointLightFxData_GetNodeClassKey
//   [x] 0x1cf370  CKPointLightFxData_PostLoad
//   [ ] 0x1cf3a8  RegisterCKPointLightFxDataClass
//   [ ] 0x1cf420  _GLOBAL__I_1cf420
//   [x] 0x1cf430  CKPointLightNodeFx_EvaluateColorLooped_maybe
//   [ ] 0x1cf4d0  CKPointLightFxData_Save
//   [x] 0x1cf4f8  CKPointLightFxData_RecursiveRegistration
//   [x] 0x1cf5a0  CKPointLightFxData_DeleteArray
//   [x] 0x1cf648  CKPointLightFxData_CreateArray
//   [x] 0x1cf750  CKPointLightFxData_GetInfo  (IKSerializable's: returns 1)
//   [x] 0x1cf758  CKPointLightFxData_MessageProc  (header)
//   [x] 0x1cf788  CKPointLightFxData_Destroy  (empty: IKSerializable's)
//   [x] 0x1cf790  CKPointLightFxData_Create
//   [x] 0x1cf810  CKPointLightFxData_EvaluateIntensityLooped_maybe
//   [x] 0x1cf898  CKPointLightFxData_EvaluateRadiusLooped
//   [x] 0x1cf920  CKPointLightFxData_Load
//
//   [ ] 0x9ace40  CKPointLightFxData_IsKindOfClass  [inline]
//   [x] 0x9ace80  CKPointLightFxData_GetClassType  [inline]
//   [x] 0x9ace88  CKPointLightFxData_GetClassID  [inline]
//   [ ] 0x9ace90  CKPointLightFxData_DeletingDestructor  [inline]
//   [ ] 0x9acf08  CKPointLightFxData_Destructor  [inline]
#include "k2000/logic/render/CKPointLightFxData.h"

#include <cmath>
#include <cstring>

#include "crt/ppc_ops.h"
#include "k2000/components/CKCurve2DCpnt.h"

#include "k2000/io/IKFile.h"
#include "k2000/memory/Mem.h"

// 0x001cf790 CKPointLightFxData_Create, the inlined constructor, in its store order.
CKPointLightFxData::CKPointLightFxData() {
    m_colorKeys.m_pBlock = nullptr;
    m_colorKeys.m_ui32NbElt = 20;
    m_colorKeys.m_ui32NbUsedElt = 0;
    m_colorKeys.m_pBlock = static_cast<CurveKey*>(Mem_AllocAligned16(20 * static_cast<uint32_t>(sizeof(CurveKey))));
}

// 0x001cf920 CKPointLightFxData_Load
int32_t CKPointLightFxData::Load(IKFile* file, int32_t type) {
    IKFxData::Load(file, type);
    if (type != K_LEVEL_PLATEFORMS) return 1;
    IKFile_ReadRef(file, &m_pRadiusCurve);
    IKFile_ReadRef(file, &m_pIntensityCurve);
    CurveKeys_Load(&m_colorKeys, file);
    ReadF32LE(file, &m_fLoopPeriod);
    ReadF32LE(file, &m_unk20);
    return 1;
}

// 0x001cf370 CKPointLightFxData_PostLoad
int32_t CKPointLightFxData::PostLoad(int32_t type) {
    if (type != K_LEVEL_PLATEFORMS) return 1;
    m_pAttachHotSpot = nullptr;
    m_pAttachNode = nullptr;
    m_vPosition = {0.0f, 0.0f, 0.0f};  // the vector at 0x00c50d64
    return 1;
}

namespace {
// The time wrapped into the period (the three evaluators' common start): x = t / |period| (fdivs), its integer part taken
// off with the exponent mask (a truncation; |x| < 1 gives +0), times |period| (fmuls), divided by the period (fdivs).
float WrapIntoPeriod(float t, float period) {
    const float magnitude = std::fabs(period);
    const float x = t / magnitude;
    uint32_t bits;
    std::memcpy(&bits, &x, 4);
    const int32_t shift = 0x7f - static_cast<int32_t>((bits >> 23) & 0xffu);
    const uint32_t below = (shift - 1) < 0 ? 0u : 0xffffffffu;  // ~((shift - 1) >> 31): all ones when |x| < 1
    uint32_t fraction = 0;
    if (shift > -0x1f) fraction = static_cast<uint32_t>(ppc::sraw(0x7fffff, static_cast<uint32_t>(-shift)));
    const uint32_t truncatedBits = bits & ~(fraction | below);
    float truncated;
    std::memcpy(&truncated, &truncatedBits, 4);
    return (magnitude * (x - truncated)) / period;
}
}  // namespace

// 0x001cf430 CKPointLightNodeFx_EvaluateColorLooped_maybe
void CKPointLightFxData::EvaluateColorLooped(float t, uint8_t out[4]) const {
    ColorCurve_Evaluate(WrapIntoPeriod(t, m_fLoopPeriod), out, &m_colorKeys);  // 0x00246408
}

// 0x001cf810 CKPointLightFxData_EvaluateIntensityLooped_maybe
float CKPointLightFxData::EvaluateIntensityLooped(float t) const {
    return static_cast<CKCurve2DCpnt*>(m_pIntensityCurve)->Evaluate(WrapIntoPeriod(t, m_fLoopPeriod));  // 0x00249ea8
}

// 0x001cf898 CKPointLightFxData_EvaluateRadiusLooped
float CKPointLightFxData::EvaluateRadiusLooped(float t) const {
    return static_cast<CKCurve2DCpnt*>(m_pRadiusCurve)->Evaluate(WrapIntoPeriod(t, m_fLoopPeriod));  // 0x00249ea8
}

// 0x001cf4f8 CKPointLightFxData_RecursiveRegistration (KStub_Return1_1d8340 first: nothing)
void CKPointLightFxData::RecursiveRegistration(int32_t type) {
    if (type != 0) return;
    m_pRadiusCurve->RecursiveRegistration(0);  // vt+0x24
    m_pIntensityCurve->RecursiveRegistration(0);
}
