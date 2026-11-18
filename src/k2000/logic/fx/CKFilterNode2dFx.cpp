// CKFilterNode2dFx.cpp - reconstructed original translation unit 0x1b9358-0x1ba218 (GAME_TOC1, main_toc1), 18 functions, 18 live.
// Primary class: CKFilterNode2dFx  key 0x19cc  category Logic  size 0x3c  vtable 0xb1cb48
// Other owners: CKFireBallFxData (6)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [ ] 0x1b9358  RegisterCKFilterNode2dFxClass
//   [ ] 0x1b93d0  _GLOBAL__I_1b93d0
//   [x] 0x1b93e0  CKFilterNode2dFx_Stop
//   [x] 0x1b94a8  CKFilterNode2dFx_Load
//   [ ] 0x1b94d0  CKFilterNode2dFx_Save
//   [x] 0x1b94f8  CKFilterNode2dFx_RecursiveRegistration
//   [x] 0x1b9578  CKFilterNode2dFx_DeleteArray
//   [x] 0x1b9620  CKFilterNode2dFx_Create
//   [x] 0x1b9678  CKFilterNode2dFx_Update
//   [x] 0x1b9a18  CKFilterNode2dFx_BeginFadeOut_maybe  (CKFilterNode2dFx::BeginFadeOut (CKFilterFxData::MessageProc 0x1b1e))
//   [x] 0x1b9ad0  CKFilterNode2dFx_Start
//   [x] 0x1b9d08  CKFilterNode2dFx_CreateArray
//   [x] 0x1b9dc0  CKFireBallFxData_GetNodeClassKey  (CKFireBallFxData::GetAssociatedFxClassIdentifier, CKFireBallFxData.h)
//   [x] 0x1b9dc8  CKFireBallFxData_Destroy  (CKFireBallFxData: empty, the default slot)
//   [x] 0x1b9dd0  CKFireBallFxData_PostLoad  (CKFireBallFxData: IKFxData's (KStub_Return1_1d8338), the default slot)
//   [x] 0x1b9df8  CKFireBallFxData_RecursiveRegistration  (CKFireBallFxData: IKFxData's (KStub_Return1_1d8340), the default slot)
//   [x] 0x1b9e20  CKFireBallFxData_Load  (CKFireBallFxData::Load, here)
//   [ ] 0x1ba040  CKFireBallFxData_Save
//
//   [ ] 0x9abf38  CKFilterNode2dFx_IsKindOfClass  [inline]
//   [x] 0x9abf70  CKFilterNode2dFx_GetClassType  [inline]
//   [x] 0x9abf78  CKFilterNode2dFx_GetClassID  [inline]
//   [x] 0x9abf80  CKFilterNode2dFx_GetFxData  [inline]
//   [x] 0x9abf88  CKFilterNode2dFx_SetFxData  [inline]
//   [ ] 0x9abf90  CKFilterNode2dFx_DeletingDestruct  [inline]
//   [ ] 0x9abfd8  CKFilterNode2dFx_Destruct  [inline]
//   [ ] 0x9abff8  CKFireBallFxData_IsKindOfClass  [inline]
//   [ ] 0x9ac030  CKFireBallFxData_GetClassType  [inline]
//   [ ] 0x9ac038  CKFireBallFxData_GetClassID  [inline]
//   [ ] 0x9ac040  CKFireBallFxData_DeletingDestructor  [inline]
//   [ ] 0x9ac098  CKFireBallFxData_Destructor  [inline]
#include "k2000/logic/fx/CKFilterNode2dFx.h"

#include <cstring>

#include "Renderware/rt2d/Rt2dTypes.h"
#include "Renderware/rwcore/RwMatrix.h"
#include "crt/ppc_ops.h"
#include "k2000/graphical/fx/CBillboard2d.h"
#include "k2000/logic/fx/CKFilterFxData.h"
#include "k2000/io/IKFile.h"
#include "k2000/logic/CKSavingManager.h"
#include "k2000/logic/fx/CKFireBallFxData.h"
#include "k2000/misc/Engine.h"
#include "k2000/system/IKTime.h"
#include "platform/fps.h"

namespace {

CKFilterFxData* DataOf(const CKFilterNode2dFx* fx) { return static_cast<CKFilterFxData*>(fx->m_pFilterData); }
CBillboard2d* BillboardOf(const CKFilterNode2dFx* fx) { return static_cast<CBillboard2d*>(fx->m_pNode); }

// 0x00066c60 BillboardBrush_GetTexture: the brush's texture (Rt2dBrush +0x68).
RwTexture* BillboardBrushGetTexture(const IKBillboard2d* billboard) { return billboard->m_pBrush->texture; }

}  // namespace

// 0x009abf80 CKFilterNode2dFx_GetFxData / 0x009abf88 CKFilterNode2dFx_SetFxData
IKFxData* CKFilterNode2dFx::GetFxData() { return reinterpret_cast<IKFxData*>(m_pFilterData); }
void CKFilterNode2dFx::SetFxData(IKFxData* data) { m_pFilterData = reinterpret_cast<IKSerializable*>(data); }

// 0x001b93e0 CKFilterNode2dFx_Stop: stopped and released (bits 0..1 = 1), the brush's texture taken off
// (BillboardBrush_SetTexture with null), hidden (vt+0x60).
void CKFilterNode2dFx::Stop() {
    m_baFxData = static_cast<uint8_t>((m_baFxData & 0xfc) | 1);
    CBillboard2d* billboard = BillboardOf(this);
    IKBillboard2d* brush = billboard;
    if (BillboardBrushGetTexture(brush) != nullptr) brush->SetTexture(nullptr);  // IKBillboard2d vt+0x3c
    Vf60();  // vt+0x60 HideSceneNode
}

// 0x001b9ad0 CKFilterNode2dFx_Start. Reserved and running; with a texture the billboard's brush takes it, the start
// colour and a new billboard path; the colour moves from the start colour to the final one at the data's speed; the
// billboard centred (0.5, 0.5), sized 1 x 1, stretched to the aspect ratio, in the data's blend mode; no fade-out;
// shown (vt+0x5c).
void CKFilterNode2dFx::Vf64() {
    m_baFxData = static_cast<uint8_t>(((m_baFxData & 0xfd) | 2) & 0xfe);
    CKFilterFxData* data = DataOf(this);
    CBillboard2d* billboard = BillboardOf(this);
    IKBillboard2d* brush = billboard;
    if (data->m_pTexture != nullptr) {
        brush->SetTexture(static_cast<RwTexture*>(data->m_pTexture));  // IKBillboard2d vt+0x3c
        uint8_t color[4];
        std::memcpy(color, DataOf(this)->m_StartColor, 4);
        brush->SetColor(color);       // vt+0x28
        brush->CreateBillboard();     // vt+0x24
        data = DataOf(this);
    }
    std::memcpy(m_sColor.m_TargetedColor, data->m_FinalColor, 4);
    std::memcpy(m_sColor.m_CurrentColor, DataOf(this)->m_StartColor, 4);
    m_sColor.m_fdRed = static_cast<float>(m_sColor.m_CurrentColor[0]);
    m_sColor.m_fdGreen = static_cast<float>(m_sColor.m_CurrentColor[1]);
    m_sColor.m_fdBlue = static_cast<float>(m_sColor.m_CurrentColor[2]);
    m_sColor.m_fdAlpha = static_cast<float>(m_sColor.m_CurrentColor[3]);
    m_sColor.m_fCurrentSpeed = DataOf(this)->m_fColorSpeed;
    billboard->m_vPosition.m_fY = 0.5f;
    billboard->m_vPosition.m_fX = 0.5f;
    brush->m_vBillboardSize.m_fY = 1.0f;
    brush->m_vBillboardSize.m_fX = 1.0f;
    uint8_t color[4];
    std::memcpy(color, DataOf(this)->m_StartColor, 4);
    brush->SetColor(color);  // vt+0x28
    brush->m_bStretchToAspectRatio = 1;
    brush->m_bUseAlpha = DataOf(this)->m_ui8BlendMod;
    m_sColor.m_fFadeOutTime = 0.0f;  // stw 0
    Vf5C();  // vt+0x5c ShowSceneNode
}

// 0x001b9678 CKFilterNode2dFx_Update. CKNode2dFx_Update (0x9ad998, empty) first. The colour moves toward the target by
// dt x speed x 255 (Euclidean, in 0..255 units; it lands on the target when that step reaches it) and goes to the brush;
// with data flag 1 the effect stops once it is there. A fade-out (BeginFadeOut) lowers the alpha by its speed and stops
// the effect when its time is up.
void CKFilterNode2dFx::Update(IKTime* frameClock) {
    CBillboard2d* billboard = BillboardOf(this);
    const float dt = frameClock->m_afDeltaTime[0];
    if (std::memcmp(m_sColor.m_CurrentColor, m_sColor.m_TargetedColor, 4) != 0) {
        const float dg = static_cast<float>(m_sColor.m_TargetedColor[1]) - m_sColor.m_fdGreen;
        const float dr = static_cast<float>(m_sColor.m_TargetedColor[0]) - m_sColor.m_fdRed;
        const float step = (dt * m_sColor.m_fCurrentSpeed) * 255.0f;
        const float db = static_cast<float>(m_sColor.m_TargetedColor[2]) - m_sColor.m_fdBlue;
        float distance2 = ppc::fmadds(dr, dr, dg * dg);
        distance2 = ppc::fmadds(db, db, distance2);
        const float da = static_cast<float>(m_sColor.m_TargetedColor[3]) - m_sColor.m_fdAlpha;
        distance2 = ppc::fmadds(da, da, distance2);
        if (step * step > distance2) {
            std::memcpy(m_sColor.m_CurrentColor, m_sColor.m_TargetedColor, 4);
        } else {
            const float scale = step * rwInvSqrt(distance2);  // 0x000114d8 Math_InvSqrtf
            m_sColor.m_fdRed = ppc::fmadds(dr, scale, m_sColor.m_fdRed);
            const float green = ppc::fmadds(dg, scale, m_sColor.m_fdGreen);
            const float blue = ppc::fmadds(db, scale, m_sColor.m_fdBlue);
            const float alpha = ppc::fmadds(da, scale, m_sColor.m_fdAlpha);
            m_sColor.m_fdGreen = green;
            m_sColor.m_fdBlue = blue;
            m_sColor.m_fdAlpha = alpha;
            m_sColor.m_CurrentColor[0] = static_cast<uint8_t>(ppc::fctiwz(m_sColor.m_fdRed));
            m_sColor.m_CurrentColor[1] = static_cast<uint8_t>(ppc::fctiwz(m_sColor.m_fdGreen));
            m_sColor.m_CurrentColor[2] = static_cast<uint8_t>(ppc::fctiwz(m_sColor.m_fdBlue));
            m_sColor.m_CurrentColor[3] = static_cast<uint8_t>(ppc::fctiwz(m_sColor.m_fdAlpha));
        }
    }
    IKBillboard2d* brush = billboard;
    uint8_t color[4];
    std::memcpy(color, m_sColor.m_CurrentColor, 4);
    brush->SetColor(color);  // vt+0x28
    uint8_t brushColor[4];
    std::memcpy(brushColor, &brush->m_Color, 4);
    const uint8_t brushAlpha = brushColor[3];
    if ((DataOf(this)->m_baFlags & 2) != 0 && std::memcmp(m_sColor.m_CurrentColor, m_sColor.m_TargetedColor, 4) == 0) {
        Stop();  // vt+0x6c
    }
    if (!(m_sColor.m_fFadeOutTime > 0.0f)) return;
    const float fade = dt * m_sColor.m_fFadeOutSpeed;
    m_sColor.m_fFadeOutTime = m_sColor.m_fFadeOutTime - dt;
    float lowered = static_cast<float>(brushAlpha) - fade;
    if (dotd::fps::Unlocked()) {
        // --fps N (not in the original): the 60 Hz frames' steps, each cut to a whole alpha as at 60 fps (cutting once
        // per displayed frame would fade faster at a higher frame rate).
        const float step = dotd::fps::Dt60(dt) * m_sColor.m_fFadeOutSpeed;
        lowered = static_cast<float>(brushAlpha);
        for (int32_t i = 0; i < dotd::fps::Ticks() && lowered > 0.0f; ++i) {
            const float next = lowered - step;
            lowered = next > 0.0f ? static_cast<float>(ppc::fctiwz(next)) : 0.0f;
        }
    }
    uint8_t alpha = 0;
    float alphaValue = 0.0f;
    if (lowered > 0.0f) {
        alpha = static_cast<uint8_t>(ppc::fctiwz(lowered));
        alphaValue = static_cast<float>(alpha);
    }
    m_sColor.m_CurrentColor[3] = alpha;
    m_sColor.m_fdAlpha = alphaValue;
    std::memcpy(color, m_sColor.m_CurrentColor, 4);
    brush->SetColor(color);
    if (m_sColor.m_fFadeOutTime < 0.0f || m_sColor.m_fFadeOutTime == 0.0f) Stop();
}

// 0x001b94a8 CKFilterNode2dFx_Load
int32_t CKFilterNode2dFx::Load(IKFile* file, int32_t type) {
    IKNode2dFx::Load(file, type);
    return 1;
}

// 0x001b94f8 CKFilterNode2dFx_RecursiveRegistration
void CKFilterNode2dFx::RecursiveRegistration(int32_t type) {
    g_pEngine->m_pSavingManager->RegisterSerializableObject(this, nullptr);  // vt+0x24
    IKNode2dFx::RecursiveRegistration(type);  // 0x001d8518 CKNode2dFx_LevelReset: the node's, when set
}

// 0x001b9a18 CKFilterNode2dFx_BeginFadeOut_maybe
void CKFilterNode2dFx::BeginFadeOut(float time, const IKSerializable* owner) {
    if ((m_baFxData & 2u) == 0 || m_pOwner != owner) return;
    if (time > 0.0f) {  // ble: NaN stops
        m_sColor.m_fFadeOutTime = time;
        uint8_t color[4];
        const IKBillboard2d* brush = BillboardOf(this);
        std::memcpy(color, &brush->m_Color, 4);  // the brush colour word (+0x34 of the CBillboard2d)
        m_sColor.m_fFadeOutSpeed = static_cast<float>(color[3]) / time;  // fcfid / frsp, then fdivs
        return;
    }
    Stop();  // vt+0x6c
}

// 0x001b9e20 CKFireBallFxData_Load: six byte-swapped words in level files.
int32_t CKFireBallFxData::Load(IKFile* file, int32_t type) {
    IKFxData::Load(file, type);
    if (type == K_LEVEL_PLATEFORMS) {
        ReadF32LE(file, &m_unk08);
        ReadF32LE(file, &m_unk0c);
        ReadF32LE(file, &m_unk10);
        ReadF32LE(file, &m_unk14);
        ReadF32LE(file, &m_unk18);
        ReadF32LE(file, &m_unk1c);
    }
    return 1;
}
