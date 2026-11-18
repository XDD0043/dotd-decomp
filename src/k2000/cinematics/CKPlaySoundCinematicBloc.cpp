// CKPlaySoundCinematicBloc.cpp - reconstructed original translation unit 0x186430-0x1871b8 (GAME_TOC1, main_toc1), 14 functions, 14 live.
// Primary class: CKPlaySoundCinematicBloc  key 0x708  category CinematicNode  size 0x44  vtable 0xb1b870
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x186430  CKPlaySoundCinematicBloc_Delete
//   [ ] 0x186480  RegisterCKPlaySoundCinematicBlocClass
//   [ ] 0x1864f8  _GLOBAL__I_1864f8
//   [x] 0x186508  CKPlaySoundCinematicBloc_Stop
//   [x] 0x1866e8  CKPlaySoundCinematicBloc_Update
//   [x] 0x1867c0  CKPlaySoundCinematicBloc_RecursiveRegistration
//   [x] 0x186840  CKPlaySoundCinematicBloc_DeleteArray
//   [x] 0x1868e8  CKPlaySoundCinematicBloc_Create
//   [x] 0x186940  CKPlaySoundCinematicBloc_Destroy  (empty: the default)
//   [x] 0x186948  CKPlaySoundCinematicBloc_CreateArray
//   [x] 0x186a00  CKPlaySoundCinematicBloc_Load
//   [ ] 0x186b40  CKPlaySoundCinematicBloc_Save
//   [x] 0x186c68  CKPlaySoundCinematicBloc_Start
//   [x] 0x186fd0  CKPlaySoundCinematicBloc_Complete
//
//   [ ] 0x9a9e00  CKPlaySoundCinematicBloc_IsKindOfClass  [inline]
//   [ ] 0x9a9e38  CKPlaySoundCinematicBloc_GetClassType  [inline]
//   [ ] 0x9a9e40  CKPlaySoundCinematicBloc_GetClassID  [inline]
//   [ ] 0x9a9e48  CKPlaySoundCinematicBloc_PreActivate  [inline]
//   [x] 0x9a9e50  CKPlaySoundCinematicBloc_Abort  [inline]
//   [ ] 0x9a9e60  CKPlaySoundCinematicBloc_Destructor  [inline]
//   [ ] 0x9a9e80  CKPlaySoundCinematicBloc_DeletingDestructor  [inline]
#include "k2000/cinematics/CKPlaySoundCinematicBloc.h"

#include "k2000/io/IKFile.h"
#include "k2000/dictionaries/CKSoundDictionaryID.h"
#include "k2000/hooks/IKHook.h"
#include "k2000/logic/CKCinematicScene.h"
#include "k2000/logic/CKCinematicSceneData.h"
#include "k2000/logic/CKSavingManager.h"
#include "k2000/logic/sound/CKSound.h"
#include "k2000/misc/Engine.h"

// 0x00186a00 CKPlaySoundCinematicBloc_Load
int32_t CKPlaySoundCinematicBloc::Load(IKFile* file, int32_t type) {
    BasicLoadCinematicElement(file, type);
    if (type == K_LEVEL_PLATEFORMS) {
        ReadS32LE(file, &m_i32SoundIndex);
        ReadF32LE(file, &m_fVolume);
        ReadF32LE(file, &m_fPitch);
    }
    return 1;
}

namespace {
CKSound* BlocSound(CKPlaySoundCinematicBloc* bloc, int32_t index) {
    return static_cast<CKSoundDictionaryID*>(bloc->m_pRelatedScene->m_pSoundDico)->GetSound(static_cast<uint32_t>(index));
}
}  // namespace

// 0x001867c0 CKPlaySoundCinematicBloc_RecursiveRegistration
void CKPlaySoundCinematicBloc::RecursiveRegistration(int32_t type) {
    g_pEngine->m_pSavingManager->RegisterSerializableObject(this, nullptr);  // no type test here
    IKCinematicBloc::RecursiveRegistration(type);  // 0x0018e8d8
}

// 0x00186c68 CKPlaySoundCinematicBloc_Start
void CKPlaySoundCinematicBloc::Start() {
    StartCommon();
    int32_t index = m_i32SoundIndex;
    if (index == -1) return;
    CKCinematicSceneData* data = static_cast<CKCinematicSceneData*>(m_pElementData);
    if (data != nullptr && data->m_pHook != nullptr) {
        IKSerializable* node = static_cast<IKHook*>(data->m_pHook)->m_pKGLObject;  // hook +0x1c
        BlocSound(this, index)->SetAttachObject(node);  // 0x00111350
        index = m_i32SoundIndex;
    }
    const float volume = m_fVolume;
    const float pitch = m_fPitch;
    const int32_t loop = static_cast<int32_t>((m_DataFlags >> 7) & 1);
    CKSound* sound = BlocSound(this, index);
    sound->SetBaseVolume(volume);  // 0x00110ee8
    sound->SetSpeed(pitch);        // 0x00110e98
    sound->SetLoop(loop);          // 0x00110fd0
    sound->Play(0.0f);             // 0x00111230, TOC -0x2e14
}

// 0x00186fd0 CKPlaySoundCinematicBloc_Complete
void CKPlaySoundCinematicBloc::Complete() {
    CompleteBloc();
    if (m_i32SoundIndex != -1) Sound_Stop(BlocSound(this, m_i32SoundIndex), 0);  // 0x001111b0
}

// 0x001866e8 CKPlaySoundCinematicBloc_Update (the index is not tested for -1 here)
void CKPlaySoundCinematicBloc::Update(IKTime*) {
    if (CheckSekensStop() == 0 || (m_DataFlags & 0x80u) != 0) return;
    if (BlocSound(this, m_i32SoundIndex)->CountInstances() != 0) return;
    Complete();  // vt+0x64
}

// 0x00186508 CKPlaySoundCinematicBloc_Stop
void CKPlaySoundCinematicBloc::Stop() {
    CompleteBloc();
    Complete();  // vt+0x64
}
