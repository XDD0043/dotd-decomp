// CKDisplayPictureCinematicBloc.cpp - reconstructed original translation unit 0x1766f0-0x177cf0 (GAME_TOC1, main_toc1), 21 functions, 21 live.
// Primary class: CKDisplayPictureCinematicBloc  key 0x588  category CinematicNode  size 0x98  vtable 0xb1b1d0
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x1766f0  CKDisplayPictureCinematicBloc_Delete
//   [ ] 0x176740  RegisterCKDisplayPictureCinematicBlocClass
//   [ ] 0x1767b8  _GLOBAL__I_1767b8
//   [x] 0x1767c8  CKDisplayPictureCinematicBloc_UpdateMove_maybe  [dead: no pointer to its descriptor 0xb63bd8, no call]  (CKDisplayPictureCinematicBloc::UpdateMove)
//   [x] 0x1768a8  CKDisplayPictureCinematicBloc_UpdateColorFade_maybe
//   [x] 0x176be0  CKDisplayPictureCinematicBloc_HidePicture_maybe  [dead: no pointer to its descriptor 0xb63be8, no call]  (CKDisplayPictureCinematicBloc::HidePicture)
//   [x] 0x176c18  CKDisplayPictureCinematicBloc_ShowPicture_maybe  [dead: no pointer to its descriptor 0xb63bf0, no call]  (CKDisplayPictureCinematicBloc::ShowPicture)
//   [x] 0x176c50  CKDisplayPictureCinematicBloc_Complete
//   [ ] 0x176e28  CKDisplayPictureCinematicBloc_Save
//   [x] 0x176e50  CKDisplayPictureCinematicBloc_RecursiveRegistration
//   [x] 0x176f28  CKDisplayPictureCinematicBloc_DeleteArray
//   [x] 0x176fc8  CKDisplayPictureCinematicBloc_CreateArray
//   [x] 0x177078  CKDisplayPictureCinematicBloc_SetVideoPlayingState_maybe
//   [x] 0x177160  CKDisplayPictureCinematicBloc_Destroy  (empty: the default)
//   [x] 0x177168  CKDisplayPictureCinematicBloc_Create
//   [x] 0x1771c0  CKDisplayPictureCinematicBloc_Load
//   [x] 0x1773e0  CKDisplayPictureCinematicBloc_Start
//   [x] 0x1778a0  CKDisplayPictureCinematicBloc_Abort
//   [x] 0x1778e8  CKDisplayPictureCinematicBloc_PostLoad
//   [x] 0x177938  CKDisplayPictureCinematicBloc_Update
//   [x] 0x177ae8  CKDisplayPictureCinematicBloc_Stop
//
//   [ ] 0x9a9528  CKDisplayPictureCinematicBloc_IsKindOfClass  [inline]
//   [ ] 0x9a9560  CKDisplayPictureCinematicBloc_GetClassType  [inline]
//   [ ] 0x9a9568  CKDisplayPictureCinematicBloc_GetClassID  [inline]
//   [ ] 0x9a9570  CKDisplayPictureCinematicBloc_PreActivate  [inline]
//   [ ] 0x9a9578  CKDisplayPictureCinematicBloc_Destructor  [inline]
//   [ ] 0x9a9598  CKDisplayPictureCinematicBloc_DeletingDestructor  [inline]
#include "k2000/cinematics/CKDisplayPictureCinematicBloc.h"
#include "k2000/logic/CKSavingManager.h"

#include "k2000/graphical/fx/CBillboard2d.h"

#include <cmath>
#include <cstring>

#include "k2000/graphical/ui/CManager2d.h"
#include "k2000/graphical/ui/CScene2d.h"
#include "k2000/io/IKFile.h"
#include "k2000/misc/Engine.h"
#include "k2000/system/IKTime.h"
#include "crt/ppc_ops.h"
#include "Renderware/rwcore/RwMatrix.h"

// 0x001778e8 CKDisplayPictureCinematicBloc_PostLoad
int32_t CKDisplayPictureCinematicBloc::PostLoad(int32_t type) {
    IKCinematicBloc::PostLoad(type);  // 0x18eac0 IKCinematicBloc_PostLoad (KStub_Return1_18fc18)
    static_cast<CScene2d*>(g_pEngine->m_manager2d->m_unkA68)->RemoveChild(static_cast<CBillboard2d*>(m_pPicture));  // 0x650d8
    return 1;
}

// 0x001771c0 CKDisplayPictureCinematicBloc_Load
int32_t CKDisplayPictureCinematicBloc::Load(IKFile* file, int32_t type) {
    BasicLoadCinematicElement(file, type);
    if (type == K_LEVEL_PLATEFORMS) {
        IKFile_ReadRef(file, &m_pPicture);
        ReadRaw(file, &m_DefaultColor, 4);
        // One 0x14-byte read of the five floats, each word swapped.
        uint32_t w[5];
        ReadU32LEWords(file, w, 5);
        std::memcpy(&m_fPictureHeight, &w[0], 4);
        std::memcpy(&m_fPictureWidth, &w[1], 4);
        std::memcpy(&m_fFadeTime, &w[2], 4);
        std::memcpy(&m_fTimeAfterFadeIn, &w[3], 4);
        std::memcpy(&m_fTimeForMoving, &w[4], 4);
        // One 0x10-byte read of the two positions, each word swapped.
        uint32_t p[4];
        ReadU32LEWords(file, p, 4);
        std::memcpy(&m_v2InitialPos, &p[0], 8);
        std::memcpy(&m_v2FinalPos, &p[2], 8);
        uint8_t alphas[3];
        ReadRaw(file, alphas, 3);
        m_ui8AlphaStart = alphas[0];
        m_ui8Alpha = alphas[1];
        m_ui8AlphaEnd = alphas[2];
    }
    return 1;
}

// 0x00177078 CKDisplayPictureCinematicBloc_SetVideoPlayingState_maybe. Both branches build the colour they hand to
// IKBillboard2d::SetColor (vt+0x28 of the picture's billboard part, +0x28): while a video plays, the picture's own colour
// word (+0x34 = the billboard's m_Color, 0x177108) with its alpha byte cleared (stb 0 at +3, 0x177114); when it stops, the
// bloc's default colour (+0x3c, 0x1770c4). The flag +0x7b follows (1 / the argument). The port passed zeros in both
// branches (the old note called the colour uninitialised), so a picture stayed invisible after a video.
void CKDisplayPictureCinematicBloc::SetVideoPlayingState(uint8_t playing) {
    CBillboard2d* picture = static_cast<CBillboard2d*>(m_pPicture);
    if (picture == nullptr) return;
    uint8_t color[4];
    if (playing != 0) {
        std::memcpy(color, &static_cast<IKBillboard2d*>(picture)->m_Color, 4);
        color[3] = 0;
        picture->SetColor(color);
        m_bVideoPlaying = 1;
    } else {
        std::memcpy(color, &m_DefaultColor, 4);
        picture->SetColor(color);
        m_bVideoPlaying = playing;
    }
}

namespace {
CScene2d* PictureScene() { return static_cast<CScene2d*>(g_pEngine->m_manager2d->m_unkA68); }
float ByteToFloat(uint8_t value) { return static_cast<float>(static_cast<double>(value)); }
}  // namespace

// 0x001773e0 CKDisplayPictureCinematicBloc_Start
void CKDisplayPictureCinematicBloc::Start() {
    StartCommon();
    m_DataFlags &= 0xffffff7fu;
    CBillboard2d* picture = static_cast<CBillboard2d*>(m_pPicture);
    IKBillboard2d* billboard = static_cast<IKBillboard2d*>(picture);
    billboard->m_vBillboardSize.m_fX = m_fPictureWidth;
    billboard->m_vBillboardSize.m_fY = m_fPictureHeight;
    billboard->m_bUseAlpha = 1;
    uint8_t* defaultColor = reinterpret_cast<uint8_t*>(&m_DefaultColor);
    defaultColor[3] = m_ui8AlphaStart;
    m_fCurWaitTime = 0.0f;
    const int32_t span = (static_cast<int32_t>(m_ui8Alpha) - static_cast<int32_t>(m_ui8AlphaStart)) +
                         (static_cast<int32_t>(m_ui8Alpha) - static_cast<int32_t>(m_ui8AlphaEnd));
    const float speed = (static_cast<float>(static_cast<double>(span)) / m_fFadeTime) / 255.0f;  // TOC -0x3268
    m_fColorSpeed = std::fabs(speed);
    std::memcpy(m_aCurColor, defaultColor, 4);
    for (int i = 0; i < 4; ++i) m_afCurColor[i] = ByteToFloat(m_aCurColor[i]);
    m_aCurColor[3] = m_ui8AlphaStart;
    m_afCurColor[3] = ByteToFloat(m_ui8AlphaStart);
    std::memcpy(m_aTargetColor, defaultColor, 4);
    m_aTargetColor[3] = m_ui8Alpha;
    uint8_t color[4];
    std::memcpy(color, defaultColor, 4);
    billboard->SetColor(color);  // vt+0x28
    m_v2CurPos = m_v2InitialPos;
    m_v2MoveSpeed.m_fX = (m_v2FinalPos.m_fX - m_v2InitialPos.m_fX) / m_fTimeForMoving;
    m_v2MoveSpeed.m_fY = (m_v2FinalPos.m_fY - m_v2InitialPos.m_fY) / m_fTimeForMoving;
    picture->SetPos(m_v2CurPos);  // vt+0x74
    PictureScene()->AddChild(picture);  // 0x00065468 CScene2d_AddChild_Thunk
    m_DataFlags &= 0xfffffeffu;
    m_bVideoPlaying = 0;
}

// 0x001768a8 CKDisplayPictureCinematicBloc_UpdateColorFade_maybe
uint8_t CKDisplayPictureCinematicBloc::UpdateColorFade(IKTime* time) {
    IKBillboard2d* billboard = static_cast<IKBillboard2d*>(static_cast<CBillboard2d*>(m_pPicture));
    uint8_t* defaultColor = reinterpret_cast<uint8_t*>(&m_DefaultColor);
    const float dt = time->m_afDeltaTime[IKTime::SCALABLE_GAME_TIME];  // +0x1c
    if ((m_DataFlags & 0x100) != 0) {
        // Holding: the wait after the fade in, then the fade out (bit 7) starts.
        bool fadeOut = m_fTimeAfterFadeIn == 0.0f;
        if (!fadeOut) {
            m_fCurWaitTime = m_fCurWaitTime + dt;
            fadeOut = m_fTimeAfterFadeIn < m_fCurWaitTime;
        }
        if (fadeOut) m_DataFlags = (m_DataFlags & 0xfffffe7fu) | 0x80;
    } else {
        if (std::memcmp(m_aCurColor, m_aTargetColor, 4) != 0) {
            const float d1 = ByteToFloat(m_aTargetColor[1]) - m_afCurColor[1];
            const float d0 = ByteToFloat(m_aTargetColor[0]) - m_afCurColor[0];
            const float d2 = ByteToFloat(m_aTargetColor[2]) - m_afCurColor[2];
            const float d3 = ByteToFloat(m_aTargetColor[3]) - m_afCurColor[3];
            const float step = (dt * m_fColorSpeed) * 255.0f;
            const float length2 = ppc::fmadds(d3, d3, ppc::fmadds(d2, d2, ppc::fmadds(d0, d0, d1 * d1)));
            if (step * step > length2) {  // ble: NaN interpolates
                std::memcpy(m_aCurColor, m_aTargetColor, 4);
            } else {
                const float scale = step * rwInvSqrt(length2);  // Math_InvSqrtf 0x114d8
                m_afCurColor[0] = ppc::fmadds(d0, scale, m_afCurColor[0]);
                m_afCurColor[1] = ppc::fmadds(d1, scale, m_afCurColor[1]);
                m_afCurColor[2] = ppc::fmadds(d2, scale, m_afCurColor[2]);
                m_afCurColor[3] = ppc::fmadds(d3, scale, m_afCurColor[3]);
                for (int i = 0; i < 4; ++i) m_aCurColor[i] = static_cast<uint8_t>(ppc::fctiwz(m_afCurColor[i]));
            }
        }
        if ((m_DataFlags & 0x80) != 0) {
            if (m_aCurColor[3] == m_aTargetColor[3]) {
                // The fade out ended.
                defaultColor[3] = m_aCurColor[3];
                if (m_bVideoPlaying == 0) {
                    uint8_t color[4];
                    std::memcpy(color, defaultColor, 4);
                    billboard->SetColor(color);  // vt+0x28
                }
                return 0;
            }
        } else if (m_aCurColor[3] == m_aTargetColor[3]) {
            // The fade in ended: hold, then fade to the end alpha.
            m_DataFlags = (m_DataFlags & 0xfffffeffu) | 0x100;
            m_aTargetColor[3] = m_ui8AlphaEnd;
        }
    }
    defaultColor[3] = m_aCurColor[3];
    if (m_bVideoPlaying == 0) {
        uint8_t color[4];
        std::memcpy(color, defaultColor, 4);
        billboard->SetColor(color);  // vt+0x28
    }
    return 1;
}

// 0x00177938 CKDisplayPictureCinematicBloc_Update (0x001767c8 _UpdateMove_maybe inlined)
void CKDisplayPictureCinematicBloc::Update(IKTime* time) {
    if (CheckSekensStop() == 0) return;
    const uint8_t fading = UpdateColorFade(time);
    if ((m_DataFlags & 0x200) != 0) {
        const float dx = m_v2CurPos.m_fX - m_v2FinalPos.m_fX;
        const float dy = m_v2CurPos.m_fY - m_v2FinalPos.m_fY;
        const float distance = static_cast<float>(std::sqrt(static_cast<double>(ppc::fmadds(dx, dx, dy * dy))));  // 0x10690
        if (!(distance < 0.01f)) {  // TOC -0x326c
            const float dt = time->m_afDeltaTime[IKTime::SCALABLE_GAME_TIME];
            m_v2CurPos.m_fX = ppc::fmadds(m_v2MoveSpeed.m_fX, dt, m_v2CurPos.m_fX);
            m_v2CurPos.m_fY = ppc::fmadds(m_v2MoveSpeed.m_fY, dt, m_v2CurPos.m_fY);
            static_cast<CBillboard2d*>(m_pPicture)->SetPos(m_v2CurPos);  // vt+0x74
            return;
        }
    }
    if (fading != 0) return;
    if ((m_DataFlags & 0x400) != 0) PictureScene()->RemoveChild(static_cast<CBillboard2d*>(m_pPicture));  // 0x000650d8
    Complete();  // vt+0x64
}

// 0x00176c50 CKDisplayPictureCinematicBloc_Complete
void CKDisplayPictureCinematicBloc::Complete() { CompleteBloc(); }

// 0x00177ae8 CKDisplayPictureCinematicBloc_Stop
void CKDisplayPictureCinematicBloc::Stop() {
    CompleteBloc();
    if ((m_DataFlags & 0x400) != 0) PictureScene()->RemoveChild(static_cast<CBillboard2d*>(m_pPicture));  // 0x000650d8
    Complete();  // vt+0x64
}

// 0x001778a0 CKDisplayPictureCinematicBloc_Abort
void CKDisplayPictureCinematicBloc::Abort() {
    m_DataFlags &= 0xfffffffeu;
    PictureScene()->RemoveChild(static_cast<CBillboard2d*>(m_pPicture));  // 0x000650d8
}

// 0x00176e50 CKDisplayPictureCinematicBloc_RecursiveRegistration
void CKDisplayPictureCinematicBloc::RecursiveRegistration(int32_t type) {
    if (static_cast<uint32_t>(type - 4) > 3u) g_pEngine->m_pSavingManager->RegisterSerializableObject(this, nullptr);
    IKCinematicBloc::RecursiveRegistration(type);  // 0x0018e8d8
    if (m_pPicture != nullptr) m_pPicture->RecursiveRegistration(type);  // vt+0x24
}

// 0x001767c8 CKDisplayPictureCinematicBloc_UpdateMove_maybe: the out-of-line copy of the move Update inlines: 0 once the
// picture is within 0.01 of its final position (blt: a NaN distance moves on), else one step of the move speed (by the
// time's scalable dt +0x1c, fused), the picture placed (vt+0x74), 1. Dead in the original (no pointer to its descriptor
// 0xb63bd8, no call).
uint8_t CKDisplayPictureCinematicBloc::UpdateMove(IKTime* time) {
    const float dy = m_v2CurPos.m_fY - m_v2FinalPos.m_fY;
    const float dx = m_v2CurPos.m_fX - m_v2FinalPos.m_fX;
    const float distance = static_cast<float>(std::sqrt(static_cast<double>(ppc::fmadds(dx, dx, dy * dy))));  // 0x10690
    if (distance < 0.01f) return 0;  // TOC -0x326c
    m_v2CurPos.m_fX = ppc::fmadds(m_v2MoveSpeed.m_fX, time->m_afDeltaTime[IKTime::SCALABLE_GAME_TIME], m_v2CurPos.m_fX);
    m_v2CurPos.m_fY = ppc::fmadds(m_v2MoveSpeed.m_fY, time->m_afDeltaTime[IKTime::SCALABLE_GAME_TIME], m_v2CurPos.m_fY);
    static_cast<CBillboard2d*>(m_pPicture)->SetPos(m_v2CurPos);  // vt+0x74
    return 1;
}

// 0x00176be0 CKDisplayPictureCinematicBloc_HidePicture_maybe: the picture taken off the 2D manager's scene +0xa68
// (CContainer2d_RemoveChild_maybe 0x650d8). Dead in the original (no pointer to its descriptor 0xb63be8, no call).
void CKDisplayPictureCinematicBloc::HidePicture() {
    PictureScene()->RemoveChild(static_cast<CBillboard2d*>(m_pPicture));
}

// 0x00176c18 CKDisplayPictureCinematicBloc_ShowPicture_maybe: the picture put on that scene (CScene2d_AddChild_Thunk
// 0x65468). Dead in the original (no pointer to its descriptor 0xb63bf0, no call).
void CKDisplayPictureCinematicBloc::ShowPicture() {
    PictureScene()->AddChild(static_cast<CBillboard2d*>(m_pPicture));
}
