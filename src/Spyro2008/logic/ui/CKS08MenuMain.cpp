// CKS08MenuMain.cpp - reconstructed original translation unit 0x5572b8-0x5582b8 (GAME_TOC2, main_toc2), 20 functions, 18 live.
// Primary class: CKS08MenuMain  key 0x818c  category Logic  size ?  vtable 0xb2c970
// Other owners: CKS08Menu (2)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x5572b8  CKS08MenuMain_Delete
//   [ ] 0x557308  CKS08MenuMain_Construct  [dead]
//   [x] 0x5573b0  CKS08Menu_PlayLoopSounds_maybe
//   [x] 0x5574a8  CKS08Menu_PlayEnterSounds_maybe
//   [x] 0x557528  CKS08MenuMain_RecursiveRegistration
//   [x] 0x557598  CKS08MenuMain_Destroy  (inherited: CKMenuBase114c::Destroy)
//   [x] 0x5575c0  CKS08MenuMain_DeleteArray
//   [ ] 0x557660  RegisterCKS08MenuMainClass
//   [ ] 0x5576e8  _GLOBAL__D_5576e8
//   [ ] 0x5576f8  _GLOBAL__I_5576f8
//   [x] 0x557708  CKS08MenuMain_vfE8
//   [ ] 0x5578b0  CKS08MenuMain_Construct_2  [dead]
//   [x] 0x557958  CKS08MenuMain_CreateArray
//   [x] 0x557a98  CKS08MenuMain_Create
//   [x] 0x557b80  CKS08MenuMain_Load
//   [ ] 0x557c60  CKS08MenuMain_Save
//   [x] 0x557d40  CKS08MenuMain_OnMenuState_maybe
//   [x] 0x557f10  CKS08MenuMain_Destructor  (implicit destructor: CKMenuBase114c's inlined)
//   [x] 0x558048  CKS08MenuMain_Destructor_2  (implicit destructor: CKMenuBase114c's inlined)
//   [x] 0x558180  CKS08MenuMain_DeletingDestructor  (implicit destructor: CKMenuBase114c's inlined)
//
//   [x] 0x9c9c40  CKS08MenuMain_IsKindOfClass  [inline]
//   [x] 0x9c9c80  CKS08MenuMain_GetClassType  [inline]
//   [x] 0x9c9c88  CKS08MenuMain_GetClassID  [inline]
//   [x] 0x9c9c90  CKS08MenuMain_vfB8  [inline]
//   [x] 0x9c9c98  CKS08MenuMain_vfE0  [inline]
//   [x] 0x9c9ca0  CKS08MenuMain_vfC4  [inline]
//   [x] 0x9c9ca8  CKS08MenuMain_vfC8  [inline]
//   [x] 0x9c9cb8  CKS08MenuMain_vfCC  [inline]
//   [x] 0x9c9cc8  CKS08MenuMain_vfBC  [inline]
//   [x] 0x9c9cd0  CKS08MenuMain_vfC0  [inline]
//   [x] 0x9c9ce0  CKS08MenuMain_GetWidgetSlotCount  [inline]
//   [x] 0x9c9ce8  CKS08MenuMain_GetWidgetSlots  [inline]
//   [x] 0x9c9cf8  CKS08MenuMain_vfE4  [inline]
#include "Spyro2008/logic/ui/CKS08MenuMain.h"
#include "k2000/logic/sound/CKSound.h"
#include "k2000/dictionaries/CKSoundDictionaryID.h"
#include "k2000/logic/IKPlayer.h"

#include "k2000/core/Stub.h"

#include "Spyro2008/logic/CKS08GameManager.h"
#include "k2000/components/CKLocTextAccessor.h"
#include "k2000/graphical/fx/CColorizedScreenData.h"
#include "k2000/graphical/fx/CColorizedScreenFx.h"
#include "k2000/graphical/system/IKVideo.h"
#include "k2000/graphical/system/CKVideoSegment.h"
#include "k2000/graphical/system/CVideoManager.h"
#include "k2000/graphical/system/PS3_CKVideo.h"
#include "k2000/graphical/ui/CKFlashText.h"
#include "k2000/managers/CKInput.h"
#include "k2000/misc/Engine.h"
#include "k2000/system/CTimeManager.h"
#include "k2000/system/IKTime.h"
#include "k2000/ui/IKNode2d.h"

#include "k2000/io/IKFile.h"

// 0x00557b80 CKS08MenuMain_Load: no type test of its own, so its fields are read whatever the type.
int32_t CKS08MenuMain::Load(IKFile* file, int32_t type) {
    CKMenuBase114c::Load(file, type);
    IKFile_ReadRef(file, &m_pSound);
    return 1;
}

namespace {

// The sound calls (0x00112bd8 CKSoundDictionaryID_GetSound_2, 0x00111568 CKSound_IsPlaying_maybe,
// 0x00110fd0 CKSound_SetLoop_maybe, 0x00111230 CKSound_Play; the menus pass f1 = TOC2 -0x7f74 = 0.0).
CKSound* SoundDictionaryGetSound(IKSerializable* dictionary, uint32_t index) {
    return CKSoundDictionaryID_GetSound_2(static_cast<CKSoundDictionaryID*>(dictionary), index);
}
uint8_t SoundIsPlaying(CKSound* sound) { return static_cast<uint8_t>(sound->IsPlaying()); }
void SoundSetLoop(CKSound* sound, uint8_t loop) { sound->SetLoop(loop); }
void SoundPlay(float offset, CKSound* sound) { sound->Play(offset); }

}  // namespace

// 0x005573b0 CKS08Menu_PlayLoopSounds_maybe
void CKS08MenuMain::PlayLoopSounds() {
    CKSound* sound = SoundDictionaryGetSound(m_pSound, 0);
    if (sound != nullptr && SoundIsPlaying(sound) == 0) {
        SoundSetLoop(sound, 1);
        SoundPlay(0.0f, sound);
    }
    sound = SoundDictionaryGetSound(m_pSound, 1);
    if (sound != nullptr && SoundIsPlaying(sound) == 0) {
        SoundSetLoop(sound, 1);
        SoundPlay(0.0f, sound);
    }
}

// 0x005574a8 CKS08Menu_PlayEnterSounds_maybe
void CKS08MenuMain::PlayEnterSounds() {
    CKSound* sound = SoundDictionaryGetSound(m_pSound, 2);
    if (sound != nullptr) SoundPlay(0.0f, sound);
    sound = SoundDictionaryGetSound(m_pSound, 3);
    if (sound != nullptr) SoundPlay(0.0f, sound);
}

// 0x00557708 CKS08MenuMain_vfE8
void CKS08MenuMain::OnItemState(uint8_t item, uint8_t state, uint8_t phase) {
    CKS08GameManager* manager = static_cast<CKS08GameManager*>(m_pGameManager);
    if (state != 4 || phase != 1) return;
    if (item == 1) {
        manager->m_unkAFC &= ~0x20u;
        manager->m_unkAFC = (manager->m_unkAFC & ~2u) | 2u;
        manager->m_unkAFC = (manager->m_unkAFC & ~8u) | 8u;
        manager->SetFlag64Bit2();
    } else if (item == 0) {
        manager->m_unkAFC &= ~0x20u;
        manager->m_unkAFC = (manager->m_unkAFC & ~4u) | 4u;
        static_cast<IKPlayer*>(manager->m_players[0])->InitializeNewGame();  // +0x44 vt+0x54
        manager->NewGame();                        // vt+0xb8
    } else if (item == 2) {
        manager->ExitGame();                       // vt+0xb4
    }
}

// 0x00557d40 CKS08MenuMain_OnMenuState_maybe: on enter, the interface video's segment from its start, the
// loop and enter sounds (the latter inlined), one player.
uint8_t CKS08MenuMain::OnMenuState(int32_t phase, uint8_t /*other*/) {
    if (phase == 1) {
        PlayScreenVideo(3, 1);
        PlayLoopSounds();
        CKSound* sound = SoundDictionaryGetSound(m_pSound, 2);
        if (sound != nullptr) SoundPlay(0.0f, sound);  // TOC2 -0x7f74 = 0.0
        sound = SoundDictionaryGetSound(m_pSound, 3);
        if (sound != nullptr) SoundPlay(0.0f, sound);
        CKS08GameManager* manager = static_cast<CKS08GameManager*>(m_pGameManager);
        manager->SetPlayerCount(1);         // vt+0x158
        manager->SetPlayerActive(0, 1);     // vt+0x184
        manager->SetPlayerActive(1, 0);
        manager->m_unkAFC &= ~4u;
        manager->m_unkAFC &= ~8u;
        manager->m_unkAFC &= ~0x10u;
        manager->m_unk2FC = 1;
    }
    return static_cast<uint8_t>(GetMenuId());
}

// 0x00557528 CKS08MenuMain_RecursiveRegistration: the referenced objects' registration, then the base.
void CKS08MenuMain::RecursiveRegistration(int32_t type) {
    m_pSound->RecursiveRegistration(type);
    CKMenuBase114c::RecursiveRegistration(type);
}
