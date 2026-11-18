// CKPlayVideoCinematicBloc.cpp - reconstructed original translation unit 0x1871b8-0x189578 (GAME_TOC1, main_toc1), 25 functions, 22 live.
// Primary class: CKPlayVideoCinematicBloc  key 0x888  category CinematicNode  size 0x170  vtable 0xb1b908
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x1871b8  CKPlayVideoCinematicBloc_Delete
//   [x] 0x187208  CKPlayVideoCinematicBloc_IsCurrentVideoSkippable_maybe
//   [ ] 0x187238  RegisterCKPlayVideoCinematicBlocClass
//   [ ] 0x1872b0  _GLOBAL__I_1872b0
//   [x] 0x1872c0  CKPlayVideoCinematicBloc_UpdateSubtitleVisibility_maybe  [dead: no pointer to its descriptor 0xb66cc0, no call]  (CKPlayVideoCinematicBloc::UpdateSubtitleVisibility)
//   [x] 0x187398  CKPlayVideoCinematicBloc_PostLoad  (= the inherited slot)
//   [x] 0x1873c0  CKPlayVideoCinematicBloc_RecursiveRegistration
//   [x] 0x1874e8  CKPlayVideoCinematicBloc_StartFade_maybe
//   [ ] 0x187580  FUN_00187580  [dead]
//   [x] 0x187620  CKPlayVideoCinematicBloc_DeleteArray
//   [x] 0x1876c0  CKPlayVideoCinematicBloc_Create
//   [ ] 0x187760  CKPlayVideoCinematicBloc_Save
//   [x] 0x1879f8  CKPlayVideoCinematicBloc_Load
//   [x] 0x187e10  CKPlayVideoCinematicBloc_Destroy
//   [x] 0x187ec8  CKPlayVideoCinematicBloc_Start
//   [x] 0x188190  CKPlayVideoCinematicBloc_CreateArray
//   [x] 0x1882a8  CKPlayVideoCinematicBloc_UpdateSubtitles_maybe
//   [ ] 0x188428  CKPlayVideoCinematicBloc_StopSubtitles_maybe  [dead]
//   [ ] 0x1884c8  CKPlayVideoCinematicBloc_StartSubtitles_maybe  [dead]
//   [x] 0x188628  CKPlayVideoCinematicBloc_Abort
//   [x] 0x1887b0  CKPlayVideoCinematicBloc_Stop
//   [x] 0x188b40  CKPlayVideoCinematicBloc_FinishVideo_maybe
//   [x] 0x188d38  CKPlayVideoCinematicBloc_Complete
//   [x] 0x188f88  CKPlayVideoCinematicBloc_PlayNextVideo_maybe
//   [x] 0x1894b0  CKPlayVideoCinematicBloc_Update
//
//   [ ] 0x9a9ec8  CKPlayVideoCinematicBloc_IsKindOfClass  [inline]
//   [ ] 0x9a9f00  CKPlayVideoCinematicBloc_GetClassType  [inline]
//   [ ] 0x9a9f08  CKPlayVideoCinematicBloc_GetClassID  [inline]
//   [x] 0x9a9f10  CKPlayVideoCinematicBloc_PreActivate  [inline]
//   [ ] 0x9a9f18  CKPlayVideoCinematicBloc_Destructor  [inline]
//   [ ] 0x9a9fe8  CKPlayVideoCinematicBloc_DeletingDestructor  [inline]
#include "k2000/cinematics/CKPlayVideoCinematicBloc.h"
#include "k2000/logic/CKSavingManager.h"

#include <cmath>
#include <cstring>

#include "Renderware/rwcore/RwCamera.h"
#include "crt/ppc_ops.h"
#include "k2000/cinematics/CKDisplayPictureCinematicBloc.h"
#include "k2000/core/Stub.h"
#include "k2000/graphical/fx/CColorizedScreenFx.h"
#include "k2000/graphical/system/IKVideo.h"
#include "k2000/graphical/ui/CText2d.h"
#include "k2000/hooks/IKHook.h"
#include "k2000/io/IKFile.h"
#include "k2000/logic/CKCinematicScene.h"
#include "k2000/logic/CKCinematicSceneData.h"
#include "k2000/logic/CKSekens.h"
#include "k2000/memory/Mem.h"
#include "k2000/misc/Engine.h"
#include "k2000/scenegraph/CSGMovable.h"
#include "k2000/services/CKSrvCinematic.h"
#include "k2000/services/CKSrvSekensor.h"

// 0x001876c0 CKPlayVideoCinematicBloc_Create (the constructor inlined)
CKPlayVideoCinematicBloc::CKPlayVideoCinematicBloc() {
    m_vpVideo = nullptr;
    m_vpVideoCapacity = 1;
    m_vpVideoCount = 0;
    m_vi32SekIndexCapacity = 1;
    m_vi32SekIndex = nullptr;
    m_vi32SekIndexCount = 0;
    m_vbSkipVideoCapacity = 1;
    m_vbSkipVideo = nullptr;
    m_vbSkipVideoCount = 0;
    m_baInternalData = 0;
    m_szVideoPath[0] = 0;
}

// 0x001879f8 CKPlayVideoCinematicBloc_Load. The vectors' inlined reserve (TVector: grow to count + 1
// with Mem_ReallocAligned16 when the capacity is short) never grows here: each capacity was just set
// to the count.
int32_t CKPlayVideoCinematicBloc::Load(IKFile* file, int32_t type) {
    BasicLoadCinematicElement(file, type);
    if (type != K_LEVEL_PLATEFORMS) {
        m_pSubtitleText = nullptr;
        return 1;
    }
    uint32_t count;
    ReadU32LE(file, &count);
    if (count != 0) {
        m_vpVideoCapacity = count;
        m_vpVideo = static_cast<IKSerializable**>(Mem_AllocAligned16(count * static_cast<uint32_t>(sizeof(IKSerializable*))));
        if (m_vpVideoCapacity < count) {
            uint32_t grown = count + 1;
            m_vpVideo = static_cast<IKSerializable**>(
                Mem_ReallocAligned16(m_vpVideo, grown * static_cast<uint32_t>(sizeof(IKSerializable*))));
            m_vpVideoCapacity = grown;
        }
        m_vpVideoCount = count;
        IKFile_ReadObjectRefArray(file, m_vpVideo, count);

        m_vi32SekIndexCapacity = count;
        m_vi32SekIndex = static_cast<int32_t*>(Mem_AllocAligned16(count * static_cast<uint32_t>(sizeof(int32_t))));
        if (m_vi32SekIndexCapacity < count) {
            uint32_t grown = count + 1;
            m_vi32SekIndex = static_cast<int32_t*>(Mem_ReallocAligned16(m_vi32SekIndex, grown * static_cast<uint32_t>(sizeof(int32_t))));
            m_vi32SekIndexCapacity = grown;
        }
        m_vi32SekIndexCount = count;
        // One read of count words, each swapped.
        ReadU32LEWords(file, reinterpret_cast<uint32_t*>(m_vi32SekIndex), count);

        m_vbSkipVideoCapacity = count;
        m_vbSkipVideo = static_cast<uint8_t*>(Mem_AllocAligned16(count));
        if (m_vbSkipVideoCapacity < count) {
            uint32_t grown = count + 1;
            m_vbSkipVideo = static_cast<uint8_t*>(Mem_ReallocAligned16(m_vbSkipVideo, grown));
            m_vbSkipVideoCapacity = grown;
        }
        m_vbSkipVideoCount = count;
        ReadRaw(file, m_vbSkipVideo, count);
    }
    ReadF32LE(file, &m_fFirstBlocFadeTime);
    IKFile_ReadRef(file, &m_pColorizedScreenFx);
    m_pSubtitleText = nullptr;
    return 1;
}

namespace {

CKSrvSekensor* Sekensor() { return static_cast<CKSrvSekensor*>(g_pEngine->m_srvSekensor); }
CKSrvCinematic* Cinematic() { return static_cast<CKSrvCinematic*>(g_pEngine->m_srvCinematic); }

// The length of a matrix row, Math_Sqrtf(x*x + y*y + z*z) with the sum fused as in the original
// (fmuls, fmadds, fmadds; Math_Sqrtf is the double square root rounded to float).
float RowLength(const float* v) {
    float sum = v[1] * v[1];
    sum = ppc::fmadds(v[0], v[0], sum);
    sum = ppc::fmadds(v[2], v[2], sum);
    return static_cast<float>(std::sqrt(static_cast<double>(sum)));
}

// 0x001874e8 CKPlayVideoCinematicBloc_StartFade_maybe: a fade time other than 0 shows the bloc's screen fx and starts the fade
// from opaque black to transparent black over that time (ScreenFade_Start_maybe 0xb0870 = StartColorFade: blend mode 1, sort
// mode 3, colour mode 1; the back blend takes 1 second).
void StartFade(CKPlayVideoCinematicBloc* bloc, float fadeTime) {
    if (fadeTime == 0.0f) return;
    CColorizedScreenFx* fade = static_cast<CColorizedScreenFx*>(bloc->m_pColorizedScreenFx);
    fade->m_BitProperties = (fade->m_BitProperties & ~CColorizedScreenFx::kActive) | CColorizedScreenFx::kActive;
    const uint8_t primary[4] = {0, 0, 0, 0xff};
    const uint8_t secondary[4] = {0, 0, 0, 0};
    fade->StartColorFade(fadeTime, 1.0f, primary, 1, 3, 1, secondary);
}

// The scene's CKDisplayPictureCinematicBloc elements (key 0x588), told whether a video plays.
void TellPictures(CKPlayVideoCinematicBloc* bloc, uint8_t playing) {
    for (IKCinematicElement* node = bloc->m_pRelatedScene->m_pActiveNodes; node != nullptr; node = node->m_pNext) {
        if (node->IsKindOfClass(0x588) != 0) static_cast<CKDisplayPictureCinematicBloc*>(node)->SetVideoPlayingState(playing);
    }
}

IKVideo* VideoAt(CKPlayVideoCinematicBloc* bloc, uint32_t index) { return static_cast<IKVideo*>(bloc->m_vpVideo[index]); }

}  // namespace

// 0x00187208 CKPlayVideoCinematicBloc_IsCurrentVideoSkippable_maybe
uint8_t CKPlayVideoCinematicBloc::IsCurrentVideoSkippable() const {
    if (m_ui32CurVideo == 0xffffffffu) return 0;
    return m_vbSkipVideo[m_ui32CurVideo] != 0 ? 1 : 0;
}

// 0x00187ec8 CKPlayVideoCinematicBloc_Start
void CKPlayVideoCinematicBloc::Start() {
    CKCinematicSceneData* data = static_cast<CKCinematicSceneData*>(m_pElementData);
    IKHook* hook = data != nullptr ? static_cast<IKHook*>(data->m_pHook) : nullptr;
    CSGMovable* node = hook != nullptr ? static_cast<CSGMovable*>(hook->m_pKGLObject) : nullptr;
    if (node == nullptr) {
        m_unk2c[0] = 1.0f;  // the shared vector 0x00c50d58
        m_unk2c[1] = 1.0f;
        m_unk2c[2] = 1.0f;
    } else {
        const RwFrame* frame = node->m_pRwFrame;
        m_unk2c[0] = RowLength(&frame->modelling.at.x);
        m_unk2c[1] = RowLength(&frame->modelling.right.x);
        m_unk2c[2] = RowLength(&frame->modelling.up.x);
    }
    if (UsesActor() != 0 && hook != nullptr) {  // vt+0x80
        IKLife* object = hook->m_pHookLife != nullptr ? static_cast<IKLife*>(hook->m_pHookLife) : hook;
        if (((object->m_bitArray >> 1) & 1) == 0) Complete();  // vt+0x64
    }
    if (((m_DataFlags & 0x20) == 0 || (m_DataFlags & 4) == 0) && InterruptConflictingBlocs() != 0) {
        m_pRelatedScene->AddActiveNode(this);
        m_DataFlags = (m_DataFlags & 0xfffffff8u) | (m_DataFlags & 2) | 1;
        m_bSekensReached = 0;
    } else {
        Complete();
    }
    m_ui32CurVideo = 0xffffffffu;
    m_pSubtitleText = nullptr;
    m_pad162 = static_cast<uint16_t>(m_pad162 | 0x200);  // the byte at +0x162, bit 1
}

// 0x00188f88 CKPlayVideoCinematicBloc_PlayNextVideo_maybe
void CKPlayVideoCinematicBloc::PlayNextVideo() {
    CKSrvSekensor* sekensor = Sekensor();
    sekensor->MessageProc(0xf08, nullptr);
    if (m_pSubtitleText != nullptr) m_pSubtitleText->Disable();  // vt+0x68
    m_pSubtitleText = nullptr;
    const uint32_t current = m_ui32CurVideo;
    if (m_vpVideoCount <= current + 1u) {
        Cinematic()->m_pCurrentVideoBloc = nullptr;
        StartFade(this, m_fFirstBlocFadeTime);
        Complete();  // vt+0x64
        return;
    }
    if (current != 0xffffffffu) {
        VideoAt(this, current)->Stop();  // vt+0x78
        TellPictures(this, 0);
    }
    StartFade(this, m_fFirstBlocFadeTime);
    ++m_ui32CurVideo;
    IKVideo* video = VideoAt(this, m_ui32CurVideo);
    video->m_baData = (video->m_baData & 0xffefffffu) | 0x100000;  // a cutscene
    video->Start(nullptr);  // vt+0x60
    Cinematic()->m_pCurrentVideoBloc = this;
    TellPictures(this, 1);
    CKSekens* sekens = nullptr;
    const uint32_t index = static_cast<uint32_t>(m_vi32SekIndex[m_ui32CurVideo]);
    if (index != 0xffffffffu) {
        sekens = sekensor->GetSekens(index);
        if (sekens != nullptr) {
            sekens->SetFlag14Bit3(1);
            sekensor->RequestSekens(sekens);
            m_pSubtitleText = sekens->m_pText;
        }
    }
    CText2d* text = m_pSubtitleText;
    if (text == nullptr) return;
    if (sekens != nullptr && sekensor->IsSekensDone(sekens) == 0 && sekens->GetCurrentLineIndex() != -1 &&
        (sekensor->m_unk2c & 1) != 0) {
        text->Enable();  // vt+0x64
    } else {
        text->Disable();  // vt+0x68
    }
}

// 0x001894b0 CKPlayVideoCinematicBloc_Update
void CKPlayVideoCinematicBloc::Update(IKTime* /*time*/) {
    if (CheckSekensStop() == 0) return;
    if (m_ui32CurVideo == 0xffffffffu || VideoAt(this, m_ui32CurVideo)->m_state == 0) {
        PlayNextVideo();
        if (m_ui32CurVideo == 0xffffffffu) return;
        if (VideoAt(this, m_ui32CurVideo)->m_state == 0) return;
    }
    UpdateSubtitles();
}

// 0x001882a8 CKPlayVideoCinematicBloc_UpdateSubtitles_maybe
void CKPlayVideoCinematicBloc::UpdateSubtitles() {
    const uint32_t index = static_cast<uint32_t>(m_vi32SekIndex[m_ui32CurVideo]);
    if (index == 0xffffffffu) return;
    CKSrvSekensor* sekensor = Sekensor();
    CKSekens* sekens = sekensor->GetSekens(index);
    if (sekens != nullptr && sekensor->IsSekensDone(sekens) == 0) {
        sekens->UpdateVideoSubtitles(VideoAt(this, m_ui32CurVideo)->GetElapsedSeconds(), 0);
    }
    CText2d* text = m_pSubtitleText;
    if (text == nullptr) return;
    if (sekens != nullptr && sekensor->IsSekensDone(sekens) == 0 && sekens->GetCurrentLineIndex() != -1 &&
        (sekensor->m_unk2c & 1) != 0) {
        text->Enable();
    } else {
        text->Disable();
    }
}

// 0x00188d38 CKPlayVideoCinematicBloc_Complete
void CKPlayVideoCinematicBloc::Complete() {
    Sekensor()->MessageProc(0xf08, nullptr);
    if (m_pSubtitleText != nullptr) m_pSubtitleText->Disable();  // vt+0x68
    m_pSubtitleText = nullptr;
    CompleteBloc();
}

// 0x00188b40 CKPlayVideoCinematicBloc_FinishVideo_maybe
void CKPlayVideoCinematicBloc::FinishVideo() {
    Sekensor()->MessageProc(0xf08, nullptr);
    if (m_pSubtitleText != nullptr) m_pSubtitleText->Disable();
    m_pSubtitleText = nullptr;
    Cinematic()->m_pCurrentVideoBloc = nullptr;
    if (m_ui32CurVideo < m_vpVideoCount) {
        VideoAt(this, m_ui32CurVideo)->Stop();  // vt+0x78
        TellPictures(this, 0);
    }
    StartFade(this, m_fFirstBlocFadeTime);
}

// 0x001887b0 CKPlayVideoCinematicBloc_Stop: FinishVideo's work, the outputs activated, then Complete.
void CKPlayVideoCinematicBloc::Stop() {
    FinishVideo();
    CompleteBloc();
    Complete();  // vt+0x64
}

// 0x00188628 CKPlayVideoCinematicBloc_Abort
void CKPlayVideoCinematicBloc::Abort() {
    Cinematic()->m_pCurrentVideoBloc = nullptr;
    m_DataFlags &= 0xfffffffeu;
    if (m_ui32CurVideo < m_vpVideoCount) {
        VideoAt(this, m_ui32CurVideo)->Stop();
        TellPictures(this, 0);
    }
    Sekensor()->MessageProc(0xf08, nullptr);
    if (m_pSubtitleText != nullptr) m_pSubtitleText->Disable();
    m_pSubtitleText = nullptr;
}

// 0x00187e10 CKPlayVideoCinematicBloc_Destroy
void CKPlayVideoCinematicBloc::Destroy() {
    if (m_vpVideo != nullptr) {
        Mem_FreeAligned16(m_vpVideo);
        m_vpVideo = nullptr;
    }
    m_vpVideoCount = 0;
    m_vpVideo = nullptr;
    if (m_vi32SekIndex != nullptr) {
        Mem_FreeAligned16(m_vi32SekIndex);
        m_vi32SekIndex = nullptr;
    }
    m_vi32SekIndexCount = 0;
    m_vi32SekIndex = nullptr;
    if (m_vbSkipVideo != nullptr) {
        Mem_FreeAligned16(m_vbSkipVideo);
        m_vbSkipVideo = nullptr;
    }
    m_vbSkipVideoCount = 0;
    m_vbSkipVideo = nullptr;
}

// 0x001873c0 CKPlayVideoCinematicBloc_RecursiveRegistration
void CKPlayVideoCinematicBloc::RecursiveRegistration(int32_t type) {
    g_pEngine->m_pSavingManager->RegisterSerializableObject(this, nullptr);  // no type test here
    IKCinematicBloc::RecursiveRegistration(type);  // 0x0018e8d8
    for (uint32_t i = 0; i < m_vpVideoCount; ++i) m_vpVideo[i]->RecursiveRegistration(type);  // vt+0x24
    m_pColorizedScreenFx->RecursiveRegistration(type);
}

// 0x001872c0 CKPlayVideoCinematicBloc_UpdateSubtitleVisibility_maybe: the out-of-line copy of PlayNextVideo's end: with a
// subtitle text, shown (vt+0x64) while `sekens` runs (not done), has a current line and the sekensor's +0x2c bit 0 is
// set; hidden (vt+0x68) otherwise (and without a sekens). Dead in the original (no pointer to its descriptor 0xb66cc0, no
// call).
void CKPlayVideoCinematicBloc::UpdateSubtitleVisibility(CKSekens* sekens) {
    if (m_pSubtitleText == nullptr) return;
    CKSrvSekensor* sekensor = Sekensor();
    if (sekens != nullptr && sekensor->IsSekensDone(sekens) == 0 && sekens->GetCurrentLineIndex() != -1 &&
        (Sekensor()->m_unk2c & 1) != 0) {
        m_pSubtitleText->Enable();  // vt+0x64
        return;
    }
    m_pSubtitleText->Disable();  // vt+0x68
}
