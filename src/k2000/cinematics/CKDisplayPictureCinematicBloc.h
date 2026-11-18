// CKDisplayPictureCinematicBloc.h - shows a 2D picture (key 0x588, vtable 0xb1b1d0, size 0x98). Original unit: CKDisplayPictureCinematicBloc.cpp.
// XXL2: the same members in the same load order.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/misc/IKCinematicBloc.h"
#include "k2000/math/CVector2.h"

class IKFile;
class IKTime;

class CKDisplayPictureCinematicBloc : public IKCinematicBloc {
public:
    DOTD_CLASS_KEY(kCategoryCinematic, 0x16)
    DOTD_DECLARE_FACTORIES(CKDisplayPictureCinematicBloc)
    DOTD_BLOC_IS_KIND_OF()

    // 0x00177168 CKDisplayPictureCinematicBloc_Create: IKCinematicBloc_Construct, then the vtable.
    CKDisplayPictureCinematicBloc() {}
    ~CKDisplayPictureCinematicBloc() override {}

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x001771c0 CKDisplayPictureCinematicBloc_Load
    // vt+0x24 0x00176e50 CKDisplayPictureCinematicBloc_RecursiveRegistration: registered (unless 4..7), the base's, then the
    // picture's.
    void RecursiveRegistration(int32_t type) override;
    // vt+0x30 0x001778e8 CKDisplayPictureCinematicBloc_PostLoad (any type): IKCinematicBloc_PostLoad 0x18eac0 (returns
    // 1), then the picture taken off the 2D manager's scene +0xa68 (CContainer2d_RemoveChild_maybe 0x650d8); returns 1.
    int32_t PostLoad(int32_t type) override;
    // 0x00177078 CKDisplayPictureCinematicBloc_SetVideoPlayingState_maybe: while a video of the scene plays the picture
    // (when it has one) keeps its colour with alpha 0; when the video stops it takes the default colour (+0x3c) again.
    // The playing flag (+0x7b) follows.
    void SetVideoPlayingState(uint8_t playing);

    // vt+0x5c 0x001773e0 CKDisplayPictureCinematicBloc_Start: the blocs' start (StartCommon), then the picture sized,
    // coloured (the default colour at the start alpha, fading to the middle alpha), placed at the initial position with
    // its move speed, and shown (the 2D manager's scene +0xa68). Flags: bit 7 (fading out) and bit 8 (holding) cleared.
    void Start() override;
    void Complete() override;            // vt+0x64 0x00176c50 CKDisplayPictureCinematicBloc_Complete (CompleteBloc)
    // vt+0x68 0x00177938 CKDisplayPictureCinematicBloc_Update: the fade; with flag bit 9 the picture moves to the final
    // position first; once the fade ends the picture is hidden (flag bit 10) and the bloc completed.
    void Update(IKTime* time) override;
    // vt+0x6c 0x00177ae8 CKDisplayPictureCinematicBloc_Stop (no Ghidra function): CompleteBloc, the picture hidden with
    // flag bit 10, Complete (vt+0x64).
    void Stop() override;
    void Abort() override;  // vt+0x70 0x001778a0 CKDisplayPictureCinematicBloc_Abort: not running, the picture hidden
    // 0x001768a8 CKDisplayPictureCinematicBloc_UpdateColorFade_maybe: fade in to the middle alpha, hold (+0x4c seconds),
    // fade out to the end alpha; 0 once the fade out ended.
    uint8_t UpdateColorFade(IKTime* time);
    // The out-of-line helpers nothing calls (dead in the original; Update / Start / Stop inline the same code):
    uint8_t UpdateMove(IKTime* time);  // 0x001767c8 CKDisplayPictureCinematicBloc_UpdateMove_maybe
    void HidePicture();                // 0x00176be0 CKDisplayPictureCinematicBloc_HidePicture_maybe
    void ShowPicture();                // 0x00176c18 CKDisplayPictureCinematicBloc_ShowPicture_maybe

    IKSerializable* m_pPicture;  // +0x38 CBillboard2d
    uint32_t m_DefaultColor;     // +0x3c CColor, read raw (the file's bytes)
    float m_fPictureHeight;      // +0x40
    float m_fPictureWidth;       // +0x44
    float m_fFadeTime;           // +0x48
    float m_fTimeAfterFadeIn;    // +0x4c
    float m_fTimeForMoving;      // +0x50
    float m_fCurWaitTime;        // +0x54 runtime
    CVector2 m_v2InitialPos;     // +0x58
    CVector2 m_v2FinalPos;       // +0x60
    CVector2 m_v2CurPos;         // +0x68 runtime
    CVector2 m_v2MoveSpeed;      // +0x70 runtime
    uint8_t m_ui8AlphaStart;     // +0x78 the three alphas: one 3-byte read
    uint8_t m_ui8Alpha;          // +0x79
    uint8_t m_ui8AlphaEnd;       // +0x7a
    uint8_t m_bVideoPlaying;     // +0x7b DotD runtime: SetVideoPlayingState; while set the fade leaves the picture's colour
    // XXL2 CSmoothedCColorLinear (0x1c bytes; member names ours, as CColorizedScreenFx::SmoothedColor): runtime.
    uint8_t m_aTargetColor[4];   // +0x7c
    uint8_t m_aCurColor[4];      // +0x80
    float m_fColorSpeed;         // +0x84 in units of 255 per second
    float m_afCurColor[4];       // +0x88
};
DOTD_ASSERT_SIZE(CKDisplayPictureCinematicBloc, 0x98);
DOTD_ASSERT_OFFSET(CKDisplayPictureCinematicBloc, m_pPicture, +0x38);
DOTD_ASSERT_OFFSET(CKDisplayPictureCinematicBloc, m_DefaultColor, +0x3c);
DOTD_ASSERT_OFFSET(CKDisplayPictureCinematicBloc, m_fPictureHeight, +0x40);
DOTD_ASSERT_OFFSET(CKDisplayPictureCinematicBloc, m_fPictureWidth, +0x44);
DOTD_ASSERT_OFFSET(CKDisplayPictureCinematicBloc, m_fFadeTime, +0x48);
DOTD_ASSERT_OFFSET(CKDisplayPictureCinematicBloc, m_fTimeAfterFadeIn, +0x4c);
DOTD_ASSERT_OFFSET(CKDisplayPictureCinematicBloc, m_fTimeForMoving, +0x50);
DOTD_ASSERT_OFFSET(CKDisplayPictureCinematicBloc, m_fCurWaitTime, +0x54);
DOTD_ASSERT_OFFSET(CKDisplayPictureCinematicBloc, m_v2InitialPos, +0x58);
DOTD_ASSERT_OFFSET(CKDisplayPictureCinematicBloc, m_v2FinalPos, +0x60);
DOTD_ASSERT_OFFSET(CKDisplayPictureCinematicBloc, m_v2CurPos, +0x68);
DOTD_ASSERT_OFFSET(CKDisplayPictureCinematicBloc, m_v2MoveSpeed, +0x70);
DOTD_ASSERT_OFFSET(CKDisplayPictureCinematicBloc, m_ui8AlphaStart, +0x78);
DOTD_ASSERT_OFFSET(CKDisplayPictureCinematicBloc, m_ui8Alpha, +0x79);
DOTD_ASSERT_OFFSET(CKDisplayPictureCinematicBloc, m_ui8AlphaEnd, +0x7a);
DOTD_ASSERT_OFFSET(CKDisplayPictureCinematicBloc, m_aTargetColor, +0x7c);
DOTD_ASSERT_OFFSET(CKDisplayPictureCinematicBloc, m_afCurColor, +0x88);
