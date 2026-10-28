// CKDisplayPictureCinematicBloc.cpp - reconstructed original translation unit 0x1766f0-0x177cf0 (GAME_TOC1, main_toc1), 21 functions, 21 live.
// Primary class: CKDisplayPictureCinematicBloc  key 0x588  category CinematicNode  size 0x98  vtable 0xb1b1d0
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x1766f0  CKDisplayPictureCinematicBloc_Delete
//   [ ] 0x176740  RegisterCKDisplayPictureCinematicBlocClass
//   [ ] 0x1767b8  _GLOBAL__I_1767b8
//   [ ] 0x1767c8  CKDisplayPictureCinematicBloc_UpdateMove_maybe
//   [ ] 0x1768a8  CKDisplayPictureCinematicBloc_UpdateColorFade_maybe
//   [ ] 0x176be0  CKDisplayPictureCinematicBloc_HidePicture_maybe
//   [ ] 0x176c18  CKDisplayPictureCinematicBloc_ShowPicture_maybe
//   [ ] 0x176c50  CKDisplayPictureCinematicBloc_Complete
//   [ ] 0x176e28  CKDisplayPictureCinematicBloc_Save
//   [ ] 0x176e50  CKDisplayPictureCinematicBloc_RecursiveRegistration
//   [x] 0x176f28  CKDisplayPictureCinematicBloc_DeleteArray
//   [x] 0x176fc8  CKDisplayPictureCinematicBloc_CreateArray
//   [x] 0x177078  CKDisplayPictureCinematicBloc_SetVideoPlayingState_maybe
//   [ ] 0x177160  CKDisplayPictureCinematicBloc_Destroy
//   [x] 0x177168  CKDisplayPictureCinematicBloc_Create
//   [x] 0x1771c0  CKDisplayPictureCinematicBloc_Load
//   [ ] 0x1773e0  CKDisplayPictureCinematicBloc_Start
//   [ ] 0x1778a0  CKDisplayPictureCinematicBloc_Abort
//   [ ] 0x1778e8  CKDisplayPictureCinematicBloc_PostLoad
//   [ ] 0x177938  CKDisplayPictureCinematicBloc_Update
//   [ ] 0x177ae8  CKDisplayPictureCinematicBloc_Stop
//
//   [ ] 0x9a9528  CKDisplayPictureCinematicBloc_IsKindOfClass  [inline]
//   [ ] 0x9a9560  CKDisplayPictureCinematicBloc_GetClassType  [inline]
//   [ ] 0x9a9568  CKDisplayPictureCinematicBloc_GetClassID  [inline]
//   [ ] 0x9a9570  CKDisplayPictureCinematicBloc_PreActivate  [inline]
//   [ ] 0x9a9578  CKDisplayPictureCinematicBloc_Destructor  [inline]
//   [ ] 0x9a9598  CKDisplayPictureCinematicBloc_DeletingDestructor  [inline]
#include "k2000/cinematics/CKDisplayPictureCinematicBloc.h"

#include "k2000/graphical/fx/CBillboard2d.h"

#include <cstring>

#include "k2000/io/IKFile.h"

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

// 0x00177078 CKDisplayPictureCinematicBloc_SetVideoPlayingState_maybe
// BUG(original): the colour handed to IKBillboard2d::SetColor is an uninitialised local of the PS3 frame (the same in
// both branches); zeros here.
void CKDisplayPictureCinematicBloc::SetVideoPlayingState(uint8_t playing) {
    CBillboard2d* picture = static_cast<CBillboard2d*>(m_pPicture);
    if (picture == nullptr) return;
    const uint8_t uninitialisedColor[4] = {0, 0, 0, 0};
    picture->SetColor(uninitialisedColor);
    m_pad7b = playing != 0 ? 1 : 0;
}
