// CKHDRNodeFx.cpp - reconstructed original translation unit 0x1bef50-0x1c06d0 (GAME_TOC1, main_toc1), 19 functions, 19 live.
// Primary class: CKHDRNodeFx  key 0xf8c  category Logic  size 0x50  vtable 0xb1ce78
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x1bef50  CKHDRNodeFx_Delete
//   [ ] 0x1befa0  CKHDRNodeFx_Destroy
//   [ ] 0x1befa8  CKHDRNodeFx_RecursiveRegistration
//   [x] 0x1bf088  CKHDRNodeFx_PostLoad
//   [x] 0x1bf0b0  CKHDRNodeFx_Start
//   [x] 0x1bf0c0  CKHDRNodeFx_Interrupt_maybe  (header)
//   [ ] 0x1bf100  RegisterCKHDRNodeFxClass
//   [ ] 0x1bf178  _GLOBAL__I_1bf178
//   [x] 0x1bf188  CKHDRNodeFx_StepColorTowardTarget_maybe
//   [ ] 0x1bf3f8  CKHDRNodeFx_Save
//   [x] 0x1bf420  CKHDRNodeFx_DeleteArray
//   [x] 0x1bf4c8  CKHDRNodeFx_Create
//   [x] 0x1bf528  CKHDRNodeFx_Stop
//   [ ] 0x1bf650  CKHDRNodeFx_StopWithFadeTime_maybe  (STUB(C2.7): CKHDRFxData's messages)
//   [x] 0x1bf700  CKHDRNodeFx_Update
//   [x] 0x1bf9e8  CKHDRNodeFx_CreateArray
//   [x] 0x1bfab0  CKHDRNodeFx_Load
//   [x] 0x1bfc00  CKHDRNodeFx_SetDataAndOwner
//   [ ] 0x1c0200  CKHDRNodeFx_StartBlendToSetting_maybe  (STUB(C2.7): the fury and CKHDRFxData's messages)
//
//   [ ] 0x9ac420  CKHDRNodeFx_IsKindOfClass  [inline]
//   [x] 0x9ac458  CKHDRNodeFx_GetClassType  [inline]
//   [x] 0x9ac460  CKHDRNodeFx_GetClassID  [inline]
//   [ ] 0x9ac468  CKHDRNodeFx_IsGlobalEffect_maybe  [inline]
//   [x] 0x9ac470  CKHDRNodeFx_GetFxData  [inline]
//   [x] 0x9ac478  CKHDRNodeFx_SetFxData  [inline]
//   [ ] 0x9ac480  CKHDRNodeFx_Destruct  [inline]
//   [ ] 0x9ac4e0  CKHDRNodeFx_DeletingDestruct  [inline]
#include "k2000/logic/fx/CKHDRNodeFx.h"

#include <cmath>
#include <cstring>

#include "Renderware/rwcore/RwMatrix.h"
#include "crt/ppc_ops.h"
#include "k2000/graphical/CHDRData.h"
#include "k2000/graphical/render/CPostRenderingFx.h"
#include "k2000/io/IKFile.h"
#include "k2000/logic/CKCoreManager.h"
#include "k2000/logic/fx/CKHDRFxData.h"
#include "k2000/misc/Engine.h"
#include "k2000/system/IKTime.h"

namespace {
const uint8_t kColorWhite[4] = {0xff, 0xff, 0xff, 0xff};  // 0x00c50dfc
// 0x00010690 Math_Sqrtf: fsqrt of the double, rounded to float (correctly rounded on both machines).
float MathSqrtf(float x) { return static_cast<float>(std::sqrt(static_cast<double>(x))); }
uint32_t ColorWord(const uint8_t c[4]) {
    return static_cast<uint32_t>(c[0]) << 24 | static_cast<uint32_t>(c[1]) << 16 | static_cast<uint32_t>(c[2]) << 8 | c[3];
}
// The distance of two colours in byte units (the channel differences as ints, converted to float).
float ColorDistance(const uint8_t to[4], const uint8_t from[4]) {
    const float dg = static_cast<float>(static_cast<int32_t>(to[1]) - static_cast<int32_t>(from[1]));
    const float dr = static_cast<float>(static_cast<int32_t>(to[0]) - static_cast<int32_t>(from[0]));
    const float db = static_cast<float>(static_cast<int32_t>(to[2]) - static_cast<int32_t>(from[2]));
    const float da = static_cast<float>(static_cast<int32_t>(to[3]) - static_cast<int32_t>(from[3]));
    float sum = dg * dg;
    sum = ppc::fmadds(dr, dr, sum);
    sum = ppc::fmadds(db, db, sum);
    sum = ppc::fmadds(da, da, sum);
    return MathSqrtf(sum);
}
// The smoothed colour starts from `color` (its bytes as floats).
void StartSmoothedColor(CKHDRNodeFx::SSmoothedColor* smoothed, const uint8_t color[4]) {
    std::memcpy(smoothed->m_CurrentColor, color, 4);
    smoothed->m_fdRed = static_cast<float>(smoothed->m_CurrentColor[0]);
    smoothed->m_fdGreen = static_cast<float>(smoothed->m_CurrentColor[1]);
    smoothed->m_fdBlue = static_cast<float>(smoothed->m_CurrentColor[2]);
    smoothed->m_fdAlpha = static_cast<float>(smoothed->m_CurrentColor[3]);
}
CPostRenderingFx* PostRenderingFx() {
    return static_cast<CPostRenderingFx*>(g_pEngine->m_coreManager->GetObjectByClassKey(0x38d));
}
}  // namespace

// Inlined in 0x001bf4c8 CKHDRNodeFx_Create.
CKHDRNodeFx::CKHDRNodeFx() { m_lDataList = nullptr; }

// 0x001bf088 CKHDRNodeFx_PostLoad
int32_t CKHDRNodeFx::PostLoad(int32_t) {
    m_fCurColorSpeed = 0.0f;
    m_pData = nullptr;
    m_fDefaultIntensitySpeed = 0.0f;
    m_fDefaultColorSpeed = 0.0f;
    m_fCurIntensitySpeed = 0.0f;
    return 1;
}

// 0x001bf0b0 CKHDRNodeFx_Start: running (the stopped bit cleared).
void CKHDRNodeFx::Vf64() { m_baFxData = static_cast<uint8_t>(m_baFxData & 0xfe); }

// 0x001bf528 CKHDRNodeFx_Stop: stopped, the post object's HDR off, the scene node hidden (vt+0x60), the data list back to
// the pool, the speeds and the default data's intensity 0.
void CKHDRNodeFx::Stop() {
    m_baFxData = static_cast<uint8_t>((m_baFxData & 0xfe) | 1);
    CPostRenderingFx* postFx = PostRenderingFx();
    if ((postFx->m_BitProperties & 0x200) != 0) postFx->m_BitProperties &= 0xfffffdffu;
    Vf60();
    for (SDataNode* node = m_lDataList; node != nullptr;) {
        SDataNode* next = node->m_pNext;
        delete node;  // back to the free list 0x00ceaa40
        node = next;
    }
    m_lDataList = nullptr;
    m_pData = nullptr;
    m_fDefaultIntensitySpeed = 0.0f;
    m_fDefaultColorSpeed = 0.0f;
    m_fCurIntensitySpeed = 0.0f;
    m_fCurColorSpeed = 0.0f;
    m_pHDRDefaultData->m_fHDRIntensity = 0.0f;
}

// 0x001bf188 CKHDRNodeFx_StepColorTowardTarget_maybe
bool CKHDRNodeFx::StepColorTowardTarget(float intensitySpeed, float colorSpeed, float dt, CHDRData* target, const CHDRData* source,
                                        SSmoothedColor* color) {
    const float step = intensitySpeed * dt;
    uint8_t goal[4];
    std::memcpy(goal, kColorWhite, 4);
    float goalIntensity = 0.0f;  // TOC -0x1f60
    const float current = target->m_fHDRIntensity;
    if (source != nullptr) {
        std::memcpy(goal, source->m_cHDRColor, 4);
        goalIntensity = source->m_fHDRIntensity;
    }
    color->m_fCurrentSpeed = colorSpeed;
    std::memcpy(color->m_TargetedColor, goal, 4);
    if (ColorWord(color->m_CurrentColor) != ColorWord(goal)) {
        const float length = (dt * colorSpeed) * 255.0f;  // TOC -0x1f64
        const float dg = static_cast<float>(color->m_TargetedColor[1]) - color->m_fdGreen;
        const float dr = static_cast<float>(color->m_TargetedColor[0]) - color->m_fdRed;
        const float db = static_cast<float>(color->m_TargetedColor[2]) - color->m_fdBlue;
        const float da = static_cast<float>(color->m_TargetedColor[3]) - color->m_fdAlpha;
        float distance = dg * dg;
        distance = ppc::fmadds(dr, dr, distance);
        distance = ppc::fmadds(db, db, distance);
        distance = ppc::fmadds(da, da, distance);
        if (length * length > distance) {
            std::memcpy(color->m_CurrentColor, goal, 4);
        } else {
            const float k = length * rwInvSqrt(distance);  // Math_InvSqrtf 0x114d8 (_rwInvSqrt)
            color->m_fdRed = ppc::fmadds(dr, k, color->m_fdRed);
            color->m_fdGreen = ppc::fmadds(dg, k, color->m_fdGreen);
            color->m_fdBlue = ppc::fmadds(db, k, color->m_fdBlue);
            color->m_fdAlpha = ppc::fmadds(da, k, color->m_fdAlpha);
            color->m_CurrentColor[0] = static_cast<uint8_t>(ppc::fctiwz(color->m_fdRed));
            color->m_CurrentColor[3] = static_cast<uint8_t>(ppc::fctiwz(color->m_fdAlpha));
            color->m_CurrentColor[1] = static_cast<uint8_t>(ppc::fctiwz(color->m_fdGreen));
            color->m_CurrentColor[2] = static_cast<uint8_t>(ppc::fctiwz(color->m_fdBlue));
        }
    }
    std::memcpy(target->m_cHDRColor, color->m_CurrentColor, 4);
    float intensity;
    if (goalIntensity >= current) {
        intensity = (goalIntensity - current < step) ? goalIntensity : step + current;
    } else {
        intensity = (current - goalIntensity >= step) ? current - step : goalIntensity;
    }
    target->m_fHDRIntensity = intensity;
    return ColorWord(goal) != ColorWord(color->m_CurrentColor) || goalIntensity != intensity;
}

// 0x001bf700 CKHDRNodeFx_Update (vt+0x78): the current data (with a data list) and the default data moved towards their
// data; while either moves, and in the steady state, the post object's HDR on (0x200) with the current data (a list) or the
// default data as its HDR data. The default data arriving with neither a list nor data stops the effect (vt+0x6c).
void CKHDRNodeFx::Update(IKTime* frameClock) {
    CPostRenderingFx* postFx = PostRenderingFx();
    const float dt = frameClock->m_afDeltaTime[0];
    const bool hasList = m_lDataList != nullptr;
    const float zero = 0.0f;  // TOC -0x1f60
    if (hasList && (m_fCurColorSpeed != zero || m_fCurIntensitySpeed != zero)) {
        const CKHDRFxData* data = static_cast<const CKHDRFxData*>(m_lDataList->m_pData);
        const CHDRData* hdr = static_cast<const CHDRData*>(data->m_pHDRData);
        if (!StepColorTowardTarget(m_fCurIntensitySpeed, m_fCurColorSpeed, dt, m_pHDRCurData, hdr, &m_scCurColor)) {
            m_fCurIntensitySpeed = zero;
            m_fCurColorSpeed = zero;
            std::memcpy(m_pHDRCurData->m_cHDRColor, hdr->m_cHDRColor, 4);
            m_pHDRCurData->m_fHDRIntensity = hdr->m_fHDRIntensity;
        }
    }
    if (m_fDefaultIntensitySpeed != zero || m_fDefaultColorSpeed != zero) {
        const CKHDRFxData* data = static_cast<const CKHDRFxData*>(m_pData);
        if (data != nullptr) {
            const CHDRData* hdr = static_cast<const CHDRData*>(data->m_pHDRData);
            if (!StepColorTowardTarget(m_fDefaultIntensitySpeed, m_fDefaultColorSpeed, dt, m_pHDRDefaultData, hdr, &m_scCurColor)) {
                m_fDefaultColorSpeed = zero;
                m_fDefaultIntensitySpeed = zero;
                const CHDRData* arrived = static_cast<const CHDRData*>(static_cast<const CKHDRFxData*>(m_pData)->m_pHDRData);
                std::memcpy(m_pHDRDefaultData->m_cHDRColor, arrived->m_cHDRColor, 4);
                m_pHDRDefaultData->m_fHDRIntensity = arrived->m_fHDRIntensity;
            }
        } else if (!StepColorTowardTarget(m_fDefaultIntensitySpeed, m_fDefaultColorSpeed, dt, m_pHDRDefaultData, nullptr, &m_scCurColor)) {
            m_fDefaultColorSpeed = zero;
            m_fDefaultIntensitySpeed = zero;
            if (!hasList) {
                Stop();  // vt+0x6c
                return;
            }
        }
    }
    postFx->m_BitProperties = (postFx->m_BitProperties & 0xfffffdffu) | 0x200u;
    // KStub_Nop_106d8(0xc, "HDR ...", intensity): a debug print.
    postFx->m_pHDRData = m_lDataList != nullptr ? m_pHDRCurData : m_pHDRDefaultData;
}

// 0x001bfc00 CKHDRNodeFx_SetDataAndOwner (vt+0x8c). A data without the list bit (CKHDRFxData +0x14 bit 1) becomes the
// default data's target: the speeds that reach it in the data's fade time (+0x10; none for 0), the smoothed colour from the
// default data's colour, its blend mode and luminance flag taken at once, and with no speed its colour and intensity too.
// With the list bit the data is pushed on the list and the current data blends to it the same way (from the default
// data for the first entry, from the current data after).
void CKHDRNodeFx::SetDataAndOwner(IKFxData* fxData, const IKSerializable* owner) {
    CKHDRFxData* data = reinterpret_cast<CKHDRFxData*>(fxData);
    const CHDRData* hdr = static_cast<const CHDRData*>(data->m_pHDRData);
    const float zero = 0.0f;  // TOC -0x1f60
    const float scale = 255.0f;  // TOC -0x1f64
    if ((static_cast<uint32_t>(data->m_unk14) & 2) == 0) {
        m_pData = data;
        m_pOwner = owner;
        const float fade = data->m_unk10;
        if (fade != zero) {
            m_fDefaultColorSpeed = (ColorDistance(hdr->m_cHDRColor, m_pHDRDefaultData->m_cHDRColor) / fade) / scale;
            const float speed = (m_pHDRDefaultData->m_fHDRIntensity - hdr->m_fHDRIntensity) / data->m_unk10;
            m_fDefaultIntensitySpeed = speed;
            m_fDefaultIntensitySpeed = speed < zero ? -speed : speed;
        } else {
            m_fDefaultIntensitySpeed = zero;
            m_fDefaultColorSpeed = zero;
        }
        StartSmoothedColor(&m_scCurColor, m_pHDRDefaultData->m_cHDRColor);
        m_pHDRDefaultData->m_eBlendMode = hdr->m_eBlendMode;
        m_pHDRDefaultData->m_bExtractLuminance = hdr->m_bExtractLuminance;
        if (m_fDefaultColorSpeed <= zero && m_fDefaultIntensitySpeed <= zero) {
            std::memcpy(m_pHDRDefaultData->m_cHDRColor, hdr->m_cHDRColor, 4);
            m_pHDRDefaultData->m_fHDRIntensity = hdr->m_fHDRIntensity;
        }
        return;
    }
    // The list: BUG(original): an entry with the same data and owner already in the list makes the search loop forever (it
    // tests the found entry again and again).
    SDataNode* first = m_lDataList;
    for (SDataNode* node = first; node != nullptr; node = node->m_pNext) {
        while (node->m_pData == data && node->m_pOwner == owner) {
#if DOTD_FIX_BUGS
            break;
#endif
        }
#if DOTD_FIX_BUGS
        if (node->m_pData == data && node->m_pOwner == owner) break;
#endif
    }
    SDataNode* entry = new SDataNode();  // FreeListPool 0x00ceaa20 (grown by FreeListPool_Grow 0x244908)
    entry->m_pNext = m_lDataList;
    m_lDataList = entry;
    entry->m_pOwner = owner;
    entry->m_pData = data;
    const float fade = data->m_unk10;
    if (fade <= zero) {
        m_fDefaultIntensitySpeed = zero;  // BUG(original)-like: the default speeds, not the current ones, are cleared
        m_fDefaultColorSpeed = zero;
    } else {
        const CHDRData* from = first == nullptr ? m_pHDRDefaultData : m_pHDRCurData;
        m_fCurColorSpeed = (ColorDistance(hdr->m_cHDRColor, from->m_cHDRColor) / fade) / scale;
        const float speed = (from->m_fHDRIntensity - hdr->m_fHDRIntensity) / data->m_unk10;
        m_fCurIntensitySpeed = speed;
        if (first == nullptr) {
            // BUG(original): for the first entry the current intensity speed becomes |the default intensity speed|.
            const float other = m_fDefaultIntensitySpeed;
            m_fCurIntensitySpeed = other < zero ? -other : other;
        } else {
            m_fCurIntensitySpeed = speed < zero ? -speed : speed;
        }
        StartSmoothedColor(&m_scCurColor, from->m_cHDRColor);
    }
    m_pHDRCurData->m_eBlendMode = hdr->m_eBlendMode;
    m_pHDRCurData->m_bExtractLuminance = hdr->m_bExtractLuminance;
    if (m_fCurColorSpeed <= zero && m_fCurIntensitySpeed <= zero) {
        std::memcpy(m_pHDRCurData->m_cHDRColor, hdr->m_cHDRColor, 4);
        m_pHDRCurData->m_fHDRIntensity = hdr->m_fHDRIntensity;
    }
}

// 0x001bfab0 CKHDRNodeFx_Load: the two data references only in level files, the current one first.
int32_t CKHDRNodeFx::Load(IKFile* file, int32_t type) {
    IKNodeFx::Load(file, type);
    if (type != K_LEVEL_PLATEFORMS) return 1;
    IKFile_ReadRef(file, &m_pHDRCurData);
    IKFile_ReadRef(file, &m_pHDRDefaultData);
    return 1;
}
