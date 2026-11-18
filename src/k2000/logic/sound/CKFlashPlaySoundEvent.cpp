// Reconstructed original translation unit: 0x77e48-0x78280 (GAME_TOC1, main_toc1), 11 functions, 11 live.
// Primary class: CKFlashPlaySoundEvent  key 0x2e4c  category Logic  size 0xc  vtable 0xb16410
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x77e48  CKFlashPlaySoundEvent_Delete  (DOTD_DECLARE_FACTORIES Delete)
//   [x] 0x77e98  CKFlashPlaySoundEvent_PostLoad  (IKSerializable's default (1))
//   [ ] 0x77ea0  RegisterCKFlashPlaySoundEventClass
//   [ ] 0x77f18  _GLOBAL__I_77f18
//   [x] 0x77f28  CKFlashPlaySoundEvent_Load
//   [ ] 0x77fd0  CKFlashPlaySoundEvent_Save
//   [x] 0x77ff8  CKFlashPlaySoundEvent_RecursiveRegistration
//   [x] 0x78080  CKFlashPlaySoundEvent_Execute
//   [x] 0x78108  CKFlashPlaySoundEvent_DeleteArray  (DOTD_DECLARE_FACTORIES DeleteArray)
//   [x] 0x781b0  CKFlashPlaySoundEvent_CreateArray  (DOTD_DECLARE_FACTORIES CreateArray)
//   [x] 0x78248  CKFlashPlaySoundEvent_Create  (DOTD_DECLARE_FACTORIES Create)
//
//   [ ] 0x9994b8  CKFlashPlaySoundEvent_IsKindOfClass  [inline]
//   [ ] 0x9994e0  CKFlashPlaySoundEvent_Destroy  [inline]
//   [ ] 0x9994e8  CKFlashPlaySoundEvent_GetClassType  [inline]
//   [ ] 0x9994f0  CKFlashPlaySoundEvent_GetClassID  [inline]
//   [ ] 0x9994f8  CKFlashPlaySoundEvent_Destructor  [inline]
//   [ ] 0x999518  CKFlashPlaySoundEvent_DeletingDestructor  [inline]
#include "k2000/logic/sound/CKFlashPlaySoundEvent.h"

#include "k2000/dictionaries/CKSoundDictionaryID.h"
#include "k2000/graphical/ui/CKFlashUI.h"
#include "k2000/logic/CKSavingManager.h"
#include "k2000/logic/sound/CKSound.h"
#include "k2000/misc/Engine.h"
#include "k2000/ui/IKFlashObject.h"

// 0x00077f28 CKFlashPlaySoundEvent_Load
int32_t CKFlashPlaySoundEvent::Load(IKFile* file, int32_t type) {
    IKFlashGenericEvent::Load(file, type);  // 0x00078650
    if (type == K_LEVEL_PLATEFORMS) ReadS32LE(file, &m_soundIndex);
    return 1;
}

// 0x00077ff8 CKFlashPlaySoundEvent_RecursiveRegistration (the base's 0x786e8 returns 1)
void CKFlashPlaySoundEvent::RecursiveRegistration(int32_t type) {
    if (type != 0) return;
    g_pEngine->m_pSavingManager->RegisterSerializableObject(this, nullptr);  // vt+0x24
}

// 0x00078080 CKFlashPlaySoundEvent_Execute (TOC1 -0x6bb4 0.0)
void CKFlashPlaySoundEvent::Vf50() {
    if (m_soundIndex == -1) return;
    CKFlashUI* ui = static_cast<CKFlashUI*>(m_pOwner->m_pFlashUI);
    CKSound* sound = static_cast<CKSoundDictionaryID*>(ui->m_pSoundDico)->GetSound(static_cast<uint32_t>(m_soundIndex));  // 0x00112bc0
    sound->m_SoundFlags = (sound->m_SoundFlags & ~CKSound::kFlagMultiInstance) | CKSound::kFlagMultiInstance;
    sound->ResetPan(1);  // 0x00111b70
    sound->Play(0.0f);   // 0x00111230
}
