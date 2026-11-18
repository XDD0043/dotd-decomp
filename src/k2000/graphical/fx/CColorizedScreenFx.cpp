// CColorizedScreenFx.cpp - reconstructed original translation unit 0xb01f0-0xb1580 (GAME_TOC1, main_toc1), 31 functions, 30 live.
// Primary class: CColorizedScreenFx  key 0xccd  category Graphical  size 0x4c  vtable 0xb17528
// Other owners: CColorizedScreenData (8), CDistortionScreenFx (3), RegisterCColorizedScreenDataAndFxClasses (1), ScreenFade (1), CDistortionScreenData (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0xb01f0  CColorizedScreenFx_Delete
//   [x] 0xb0240  CColorizedScreenFx_RecursiveRegistration
//   [x] 0xb02a0  CColorizedScreenFx_vf78  (Clear, CColorizedScreenFx.h)
//   [x] 0xb02a8  CColorizedScreenData_Destroy  (CColorizedScreenData.h)
//   [ ] 0xb02b0  RegisterCColorizedScreenDataAndFxClasses
//   [ ] 0xb0368  _GLOBAL__I_b0368
//   [x] 0xb0378  CColorizedScreenFx_StartColorFade_maybe
//   [ ] 0xb0570  CColorizedScreenFx_DrawQuad_maybe  [dead]
//   [x] 0xb05e8  CColorizedScreenFx_Load
//   [ ] 0xb0610  CColorizedScreenFx_Save
//   [x] 0xb0638  CColorizedScreenFx_Destroy  (inherited: IRendableObject_Destroy)
//   [x] 0xb0660  CColorizedScreenFx_DeleteArray
//   [x] 0xb0700  CColorizedScreenData_DeleteArray
//   [x] 0xb07a8  CColorizedScreenFx_Create
//   [x] 0xb0800  CColorizedScreenData_Create
//   [x] 0xb0838  CColorizedScreenData_PostLoad  (CColorizedScreenData.h)
//   [x] 0xb0840  CColorizedScreenFx_PostLoad
//   [x] 0xb0870  ScreenFade_Start_maybe
//   [x] 0xb0a68  CColorizedScreenData_CreateArray
//   [x] 0xb0b00  CColorizedScreenFx_ApplyData_maybe
//   [x] 0xb0bd0  CColorizedScreenFx_CreateArray
//   [x] 0xb0c80  CColorizedScreenFx_vf74
//   [x] 0xb0ce0  CColorizedScreenData_RecursiveRegistration
//   [x] 0xb0d40  CColorizedScreenData_Load
//   [ ] 0xb0f18  CColorizedScreenData_Save
//   [x] 0xb10e8  CColorizedScreenFx_Draw (Render)
//   [x] 0xb1170  CColorizedScreenFx_UpdateAndEnqueue
//   [x] 0xb14d0  CDistortionScreenFx_Delete  (DOTD_DECLARE_FACTORIES(CDistortionScreenFx))
//   [x] 0xb1520  CDistortionScreenData_Delete  (DOTD_DECLARE_FACTORIES(CDistortionScreenData))
//   [x] 0xb1570  CDistortionScreenFx_vf58  (CDistortionScreenFx::UpdateAndExtract, CDistortionScreenFx.h)
//   [x] 0xb1578  CDistortionScreenFx_vf78  (CDistortionScreenFx::Clear, CDistortionScreenFx.h)
//
//   [x] 0x9a07e0  CColorizedScreenFx_IsKindOfClass  [inline]
//   [x] 0x9a0808  CColorizedScreenFx_GetClassType  [inline]
//   [x] 0x9a0810  CColorizedScreenFx_GetClassID  [inline]
//   [x] 0x9a0818  CColorizedScreenFx_vf70  [inline]
//   [ ] 0x9a0850  CColorizedScreenData_IsKindOfClass  [inline]
//   [x] 0x9a0878  CColorizedScreenData_GetClassType  [inline]
//   [x] 0x9a0880  CColorizedScreenData_GetClassID  [inline]
//   [ ] 0x9a0888  CColorizedScreenData_Destructor  [inline]
//   [ ] 0x9a08b8  CColorizedScreenData_DeletingDestructor  [inline]
//   [x] 0x9a0900  CColorizedScreenFx_DeletingDestructor  [inline]
//   [x] 0x9a0948  CColorizedScreenFx_Destructor  [inline]
#include "k2000/graphical/fx/CColorizedScreenFx.h"

#include <cmath>
#include <cstring>

#include "Renderware/rwcore/RwMatrix.h"
#include "crt/ppc_ops.h"
#include "k2000/graphical/fx/CColorizedScreenData.h"
#include "k2000/managers/CKGraphic.h"
#include "k2000/cameras/CameraContext.h"
#include "k2000/misc/Engine.h"
#include "k2000/render/CRenderer.h"
#include "k2000/system/CTimeManager.h"
#include "k2000/system/IKTime.h"

// 0x000b07a8 CColorizedScreenFx_Create: the inlined IRendableObject part, in the original's store order;
// the class's own fields are left as they are.
CColorizedScreenFx::CColorizedScreenFx() {
    m_pLightSet = nullptr;
    m_pNextAccumulatedObject = nullptr;
    m_BitProperties = 0;
    m_pPriorityParent = 0;
}

// 0x000b05e8 CColorizedScreenFx_Load
int32_t CColorizedScreenFx::Load(IKFile* file, int32_t type) {
    IRendableObject::Load(file, type);
    return 1;
}

// 0x000b10e8 CColorizedScreenFx_Render: the current colour (+0x24, the smoothed colour's value) over the
// screen with the blend table's entry +0x3c; the centre colour is the shared white (0x00c50dfc).
void CColorizedScreenFx::Render(IKTime* /*frameClock*/) {
    if ((m_BitProperties & 0x100u) == 0) return;
    static const uint8_t kWhite[4] = {0xff, 0xff, 0xff, 0xff};
    DrawScreenColorQuad(0.0f, 0.0f, 0, kBlendTableSrc[m_eBlendMod], kBlendTableDest[m_eBlendMod], m_scColor.m_cCurrent, kWhite,
                        nullptr);
}

// ---- CColorizedScreenData (graphical/fx/CColorizedScreenData.h) ----
#include "k2000/graphical/fx/CColorizedScreenData.h"

#include "k2000/io/IKFile.h"
#include "k2000/logic/CKSavingManager.h"

// 0x000b0d40 CColorizedScreenData_Load
int32_t CColorizedScreenData::Load(IKFile* file, int32_t type) {
    if (type != K_LEVEL_PLATEFORMS) return 1;
    ReadRaw(file, m_cPrimary, 4);
    ReadRaw(file, m_cSecondary, 4);
    ReadF32LE(file, &m_fBlendPrimary);
    ReadF32LE(file, &m_fBlendSecondary);
    ReadU8(file, &m_ui8BlendMode);
    ReadU8(file, &m_ui8ColorMode);
    ReadU8(file, &m_baInfos);
    return 1;
}

namespace {
inline bool SameColor(const uint8_t* a, const uint8_t* b) { return std::memcmp(a, b, 4) == 0; }
// An unsigned byte to float (fcfid + frsp in the original).
inline float ByteToFloat(uint8_t v) { return static_cast<float>(v); }
// The difference of two bytes to float (subf, extsw, fcfid, frsp).
inline float ByteDiff(uint8_t to, uint8_t from) { return static_cast<float>(static_cast<int32_t>(to) - static_cast<int32_t>(from)); }
const float kColorUnit = 255.0f;  // TOC1 -0x5e44 (0x437f0000)
}  // namespace

// 0x000b0378 CColorizedScreenFx_StartColorFade_maybe. 0x000b0870 ScreenFade_Start_maybe is the same code with
// the same arguments (the game manager and the fades start through that copy).
void CColorizedScreenFx::StartColorFade(float blendPrimary, float blendSecondary, const uint8_t* primary,
                                        uint32_t blendMode, uint32_t sortMode, uint32_t colorMode,
                                        const uint8_t* secondary) {
    m_pCSData = nullptr;
    m_BitProperties = (m_BitProperties & ~(3u << kColorModeShift)) | (colorMode << kColorModeShift);
    std::memcpy(m_cPrimaryColor, primary, 4);
    std::memcpy(m_cSecondaryColor, secondary, 4);
    m_eBlendMod = blendMode;
    std::memcpy(m_scColor.m_cCurrent, m_cPrimaryColor, 4);
    for (int i = 0; i < 4; ++i) m_scColor.m_afCurrent[i] = ByteToFloat(m_scColor.m_cCurrent[i]);
    std::memcpy(m_scColor.m_cTarget, m_cSecondaryColor, 4);
    if (colorMode == 0) std::memcpy(m_scColor.m_cTarget, m_cPrimaryColor, 4);
    m_BitProperties = (m_BitProperties & ~(3u << kSortModeShift)) | (sortMode << kSortModeShift);
    // The distance between the two colours: g*g, then r, b, a added with fmadds.
    const float g = ByteDiff(m_cSecondaryColor[1], m_cPrimaryColor[1]);
    const float r = ByteDiff(m_cSecondaryColor[0], m_cPrimaryColor[0]);
    const float b = ByteDiff(m_cSecondaryColor[2], m_cPrimaryColor[2]);
    const float a = ByteDiff(m_cSecondaryColor[3], m_cPrimaryColor[3]);
    float sum = g * g;
    sum = ppc::fmadds(r, r, sum);
    sum = ppc::fmadds(b, b, sum);
    sum = ppc::fmadds(a, a, sum);
    const float distance = std::sqrt(sum);  // 0x00010690 Math_Sqrtf (fsqrts)
    m_fBackBlendSpeed = (distance / blendSecondary) / kColorUnit;
    m_scColor.m_fSpeed = (distance / blendPrimary) / kColorUnit;
    m_BitProperties &= ~kHold;
}

// 0x000b0b00 CColorizedScreenFx_ApplyData_maybe: the data's bits: 0 and 1 give the sort mode (bit 0
// set: bit 1; clear: 3 - (bit 1 ^ 1)), bit 2 kUnscaledTime, bit 3 kHold.
void CColorizedScreenFx::ApplyData(CColorizedScreenData* data) {
    m_pCSData = data;
    const uint32_t infos = data->m_baInfos;
    uint32_t sortMode = (infos >> 1) & 1;
    if ((infos & 1) == 0) sortMode = 3 - (sortMode ^ 1);
    StartColorFade(data->m_fBlendPrimary, data->m_fBlendSecondary, data->m_cPrimary, data->m_ui8BlendMode, sortMode,
                   data->m_ui8ColorMode, data->m_cSecondary);
    m_BitProperties = (m_BitProperties & ~kUnscaledTime) | (((infos >> 2) & 1) << 14);
    m_BitProperties = (m_BitProperties & ~kHold) | (((infos >> 3) & 1) << 9);
}

// 0x000b0840 CColorizedScreenFx_PostLoad
int32_t CColorizedScreenFx::PostLoad(int32_t type) {
    if (type == 0) m_BitProperties &= ~kActive;
    m_pCSData = nullptr;
    return 1;
}

// 0x009a0818 CColorizedScreenFx_CanBeUpdated: sort modes 2 and 3 only while the renderer's bit 2 is clear.
int32_t CColorizedScreenFx::CanBeUpdated() {
    if (((m_BitProperties >> kSortModeShift) & 3) > 1)
        return static_cast<int32_t>(((g_pEngine->m_graphic->m_renderer->m_bitProperties ^ 4) >> 2) & 1);
    return 1;
}

// 0x000b0c80 CColorizedScreenFx_vf74 (XXL2 ComputeSortingCoef(ESortingOrder)): 10000.0 for sort modes 0/2
// with order 1 and 1/3 with order 2, else 0.
void CColorizedScreenFx::ComputeSortingCoef(int32_t sortingOrder) {
    const uint32_t mode = (m_BitProperties >> kSortModeShift) & 3;
    if (mode == 1 || mode == 3) {
        if (sortingOrder == 2) { m_fSortingCoef = 10000.0f; return; }  // 0x461c4000
    } else if (sortingOrder == 1) {
        m_fSortingCoef = 10000.0f;
        return;
    }
    m_fSortingCoef = 0.0f;
}

// 0x000b1170 CColorizedScreenFx_UpdateAndEnqueue
void CColorizedScreenFx::UpdateAndExtract(float /*maxDistanceSquared*/, RenderQueue** /*stages*/, IKTime* /*frameClock*/, RwCamera* /*camera*/, int32_t /*distanceCull*/) {
    const uint32_t flags = m_BitProperties;
    if ((flags & kActive) == 0) return;
    IKTime* frameClock = g_pEngine->m_timeManager->m_pTime;  // the PS3's third argument
    float dt = 0.0f;
    if ((flags & kUnscaledTime) != 0 || frameClock->m_eCurrentState == IKTime::RUNNING)
        dt = frameClock->m_afDeltaTime[IKTime::SCALABLE_GAME_TIME];
    const uint32_t colorMode = (flags >> kColorModeShift) & 3;
    bool step = false;
    if (colorMode == 1) {
        if (SameColor(m_scColor.m_cTarget, m_scColor.m_cCurrent) && (flags & kHold) == 0) m_BitProperties &= ~kActive;
        step = true;
    } else if (colorMode == 2) {
        if (SameColor(m_scColor.m_cCurrent, m_scColor.m_cTarget)) {
            if (!SameColor(m_cSecondaryColor, m_scColor.m_cTarget)) {
                // Back at the primary colour: done, unless held.
                if ((flags & kHold) == 0) m_BitProperties &= ~kActive;
            } else {
                // At the secondary colour: head back to the primary one at the back speed.
                std::memcpy(m_scColor.m_cTarget, m_cPrimaryColor, 4);
                m_scColor.m_fSpeed = m_fBackBlendSpeed;
            }
        }
        step = true;
    }
    if (step && !SameColor(m_scColor.m_cCurrent, m_scColor.m_cTarget)) {
        const float g = ByteToFloat(m_scColor.m_cTarget[1]) - m_scColor.m_afCurrent[1];
        const float r = ByteToFloat(m_scColor.m_cTarget[0]) - m_scColor.m_afCurrent[0];
        const float b = ByteToFloat(m_scColor.m_cTarget[2]) - m_scColor.m_afCurrent[2];
        const float a = ByteToFloat(m_scColor.m_cTarget[3]) - m_scColor.m_afCurrent[3];
        float dist2 = g * g;
        dist2 = ppc::fmadds(r, r, dist2);
        const float stepLength = (dt * m_scColor.m_fSpeed) * kColorUnit;
        dist2 = ppc::fmadds(b, b, dist2);
        dist2 = ppc::fmadds(a, a, dist2);
        if (stepLength * stepLength > dist2) {
            std::memcpy(m_scColor.m_cCurrent, m_scColor.m_cTarget, 4);  // reached (the floats are left)
        } else {
            const float scale = stepLength * rwInvSqrt(dist2);  // 0x000114d8 Math_InvSqrtf
            m_scColor.m_afCurrent[0] = ppc::fmadds(r, scale, m_scColor.m_afCurrent[0]);
            m_scColor.m_afCurrent[3] = ppc::fmadds(a, scale, m_scColor.m_afCurrent[3]);
            m_scColor.m_afCurrent[1] = ppc::fmadds(g, scale, m_scColor.m_afCurrent[1]);
            m_scColor.m_afCurrent[2] = ppc::fmadds(b, scale, m_scColor.m_afCurrent[2]);
            for (int i = 0; i < 4; ++i) m_scColor.m_cCurrent[i] = static_cast<uint8_t>(ppc::fctiwz(m_scColor.m_afCurrent[i]));
        }
    }
    // The enqueue: with kExplicitQueue into render stage (flags & 0x1f), else by sort mode (0/1: stage 16,
    // 2: 17, 3: 21; the accumulators +0x40 / +0x44 / +0x54).
    CRenderer* renderer = g_pEngine->m_graphic->m_renderer;
    const uint32_t properties = m_BitProperties;
    if ((properties & kExplicitQueue) != 0) {
        renderer->GetStage(properties & kQueueIndexMask)->Add(this);
        return;
    }
    const uint32_t sortMode = (properties >> kSortModeShift) & 3;
    if (sortMode == 2) renderer->GetStage(17)->Add(this);
    else if (sortMode < 3) renderer->GetStage(16)->Add(this);
    else renderer->GetStage(21)->Add(this);
}

// C2.8 port-all P08.

// 0x000b0240 CColorizedScreenFx_RecursiveRegistration
void CColorizedScreenFx::RecursiveRegistration(int32_t type) {
    if (type == 0) g_pEngine->m_pSavingManager->RegisterSerializableObject(this, nullptr);  // vt+0x24
}

// 0x000b0ce0 CColorizedScreenData_RecursiveRegistration
void CColorizedScreenData::RecursiveRegistration(int32_t type) {
    if (type == 0) g_pEngine->m_pSavingManager->RegisterSerializableObject(this, nullptr);  // vt+0x24
}
