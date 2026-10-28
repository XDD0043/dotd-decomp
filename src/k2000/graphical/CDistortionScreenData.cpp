// CDistortionScreenData.cpp - reconstructed original translation unit 0xb1580-0xb3170 (GAME_TOC1, main_toc1), 32 functions, 29 live.
// Primary class: CDistortionScreenData  key 0xc8d  category Graphical  size 0x30  vtable 0xb175b0
// Other owners: CDistortionScreenFx (10), RegisterCDistortionScreenFxAndDataClasses (1), EvaluateDistortionVertex (1), RenderDistortionGridWarp (1), CLensFlareFx (1), CLensFlareData (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [ ] 0xb1580  CDistortionScreenData_GetMaxAbsCurveValue_maybe  [dead]
//   [ ] 0xb1628  CDistortionScreenData_EvaluateCurve_maybe  [dead]
//   [ ] 0xb16c0  CDistortionScreenData_Save
//   [ ] 0xb16c8  CDistortionScreenData_PostLoad
//   [ ] 0xb16d0  CDistortionScreenData_vf58
//   [ ] 0xb16d8  CDistortionScreenData_RecursiveRegistration
//   [ ] 0xb1738  RegisterCDistortionScreenFxAndDataClasses
//   [ ] 0xb17f0  _GLOBAL__I_b17f0
//   [ ] 0xb1800  CDistortionScreenData_Destroy
//   [x] 0xb1850  CDistortionScreenData_DeleteArray
//   [x] 0xb18f8  CDistortionScreenFx_DeleteArray
//   [ ] 0xb19a0  CDistortionScreenData_InitDefaults_maybe  [dead]
//   [ ] 0xb1a68  EvaluateDistortionVertex_maybe
//   [ ] 0xb1d20  CDistortionScreenFx_BuildGrid_maybe
//   [x] 0xb1f78  CDistortionScreenData_Create
//   [x] 0xb1fb0  CDistortionScreenFx_Create
//   [ ] 0xb2008  CDistortionScreenData_Reset_maybe
//   [ ] 0xb2038  CDistortionScreenData_SetSource_maybe
//   [ ] 0xb2080  CDistortionScreenData_vf54
//   [x] 0xb20d0  CDistortionScreenData_CreateArray
//   [x] 0xb2168  CDistortionScreenFx_CreateArray
//   [ ] 0xb2220  CDistortionScreenFx_RecursiveRegistration
//   [ ] 0xb2280  CDistortionScreenFx_PostLoad
//   [ ] 0xb22e0  CDistortionScreenFx_Destroy
//   [ ] 0xb2350  CDistortionScreenFx_Save
//   [x] 0xb2378  CDistortionScreenFx_Load
//   [ ] 0xb2428  RenderDistortionGridWarp
//   [ ] 0xb2c88  CDistortionScreenFx_Draw
//   [x] 0xb2d28  CDistortionScreenData_Load
//   [ ] 0xb3008  CDistortionScreenData_vf50
//   [ ] 0xb30d0  CLensFlareFx_Delete
//   [ ] 0xb3120  CLensFlareData_Delete
//
//   [x] 0x9a0968  CDistortionScreenData_GetClassType  [inline]
//   [x] 0x9a0970  CDistortionScreenData_GetClassID  [inline]
//   [x] 0x9a0978  CDistortionScreenFx_GetClassType  [inline]
//   [x] 0x9a0980  CDistortionScreenFx_GetClassID  [inline]
//   [x] 0x9a0988  CDistortionScreenFx_GetSerializationFlags  [inline]
//   [x] 0x9a0990  CDistortionScreenData_IsKindOfClass  [inline]
//   [x] 0x9a09b0  CDistortionScreenFx_IsKindOfClass  [inline]
//   [ ] 0x9a09e8  CDistortionScreenFx_DeletingDestructor  [inline]
//   [ ] 0x9a0a30  CDistortionScreenData_DeletingDestructor  [inline]
//   [ ] 0x9a0a70  CDistortionScreenData_Destructor  [inline]
//   [ ] 0x9a0a88  CDistortionScreenFx_Destructor  [inline]
#include "k2000/graphical/CDistortionScreenData.h"

#include <cstring>

#include "k2000/graphical/CDistortionScreenFx.h"
#include "k2000/io/IKFile.h"

namespace {
// count little-endian words read in one block, then each byte-swapped (lwbrx on the PS3).
void SwapWordsLE(const uint8_t* bytes, void* dst, uint32_t count) {
    uint8_t* out = static_cast<uint8_t*>(dst);
    for (uint32_t i = 0; i < count; ++i) {
        const uint8_t* b = bytes + 4 * i;
        const uint32_t bits = static_cast<uint32_t>(b[0]) | (static_cast<uint32_t>(b[1]) << 8) |
                              (static_cast<uint32_t>(b[2]) << 16) | (static_cast<uint32_t>(b[3]) << 24);
        std::memcpy(out + 4 * i, &bits, 4);
    }
}
}  // namespace

// 0x000b1fb0 CDistortionScreenFx_Create: the inlined IRendableObject part, in the original's store order.
CDistortionScreenFx::CDistortionScreenFx() {
    m_pLightSet = nullptr;
    m_pNextAccumulatedObject = nullptr;
    m_BitProperties = 0;
    m_pPriorityParent = 0;
}

// 0x000b2378 CDistortionScreenFx_Load
int32_t CDistortionScreenFx::Load(IKFile* file, int32_t type) {
    IScreenFx::Load(file, type);  // the original calls IRendableObject_Load (IScreenFx_Load inlined)
    if (type == K_LEVEL_PLATEFORMS) {
        m_unk28 = 0;
        m_unk30 = nullptr;
        m_unk34 = nullptr;
        ReadU8(file, &m_ui8Resol);
    }
    return 1;
}

// 0x000b2d28 CDistortionScreenData_Load
int32_t CDistortionScreenData::Load(IKFile* file, int32_t type) {
    if (type != K_LEVEL_PLATEFORMS) return 1;
    m_pv2Amplitude = nullptr;
    ReadF32LE(file, &m_fDuration);
    ReadF32LE(file, &m_fDampCoeff);
    ReadF32LE(file, &m_fAmpThreshold);
    ReadRaw(file, m_cColor, 4);  // not swapped by the original
    ReadU32LE(file, &m_ui32NbAmplitudePoints);
    m_pv2Amplitude = new CVector2[m_ui32NbAmplitudePoints];  // OperatorNewArray(count * 8 + 4), count cookie
    const uint32_t bytes = m_ui32NbAmplitudePoints * 8;
    uint8_t* raw = new uint8_t[bytes != 0 ? bytes : 1];
    file->Read(raw, bytes);  // one read, then 2 * count words swapped
    SwapWordsLE(raw, m_pv2Amplitude, m_ui32NbAmplitudePoints * 2);
    delete[] raw;
    uint8_t offset[0xc];
    file->Read(offset, 0xc);
    SwapWordsLE(offset, &m_v3OffsetPos, 3);
    return 1;
}
