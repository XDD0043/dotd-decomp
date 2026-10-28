// CKDisplayPictureCinematicBloc.h - shows a 2D picture (key 0x588, vtable 0xb1b1d0, size 0x98). Original unit: CKDisplayPictureCinematicBloc.cpp.
// XXL2: the same members in the same load order.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/misc/IKCinematicBloc.h"
#include "k2000/math/CVector2.h"

class IKFile;

class CKDisplayPictureCinematicBloc : public IKCinematicBloc {
public:
    DOTD_CLASS_KEY(kCategoryCinematic, 0x16)
    DOTD_DECLARE_FACTORIES(CKDisplayPictureCinematicBloc)
    DOTD_BLOC_IS_KIND_OF()

    // 0x00177168 CKDisplayPictureCinematicBloc_Create: IKCinematicBloc_Construct, then the vtable.
    CKDisplayPictureCinematicBloc() {}
    ~CKDisplayPictureCinematicBloc() override {}

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x001771c0 CKDisplayPictureCinematicBloc_Load
    // 0x00177078 CKDisplayPictureCinematicBloc_SetVideoPlayingState_maybe: while a video of the scene plays the picture
    // (when it has one) is recoloured and the playing flag (+0x7b) follows.
    void SetVideoPlayingState(uint8_t playing);

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
    uint8_t m_pad7b;
    uint32_t m_scColor[7];       // +0x7c XXL2 CSmoothedCColorLinear; runtime
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
DOTD_ASSERT_OFFSET(CKDisplayPictureCinematicBloc, m_scColor, +0x7c);
