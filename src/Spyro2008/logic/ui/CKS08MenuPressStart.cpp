// CKS08MenuPressStart.cpp - reconstructed original translation unit 0x560f38-0x5625a0 (GAME_TOC2, main_toc2), 17 functions, 15 live.
// Primary class: CKS08MenuPressStart  key 0x814c  category Logic  size ?  vtable 0xb2d1b0
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x560f38  CKS08MenuPressStart_Delete
//   [ ] 0x560f88  CKS08MenuPressStart_Construct  [dead]
//   [ ] 0x561030  CKS08MenuPressStart_Save
//   [x] 0x561058  CKS08MenuPressStart_RecursiveRegistration
//   [x] 0x561198  CKS08MenuPressStart_Destroy  (inherited: CKMenuBase114c::Destroy)
//   [x] 0x5611c0  CKS08MenuPressStart_DeleteArray
//   [ ] 0x561268  RegisterCKS08MenuPressStartClass
//   [ ] 0x5612f0  _GLOBAL__D_5612f0
//   [ ] 0x561300  _GLOBAL__I_561300
//   [ ] 0x561310  CKS08MenuPressStart_Construct_2  [dead]
//   [x] 0x5613b8  CKS08MenuPressStart_OnMenuState_maybe
//   [x] 0x561cc8  CKS08MenuPressStart_CreateArray
//   [x] 0x561e10  CKS08MenuPressStart_Create
//   [x] 0x561ef8  CKS08MenuPressStart_Load
//   [x] 0x5621f8  CKS08MenuPressStart_Destructor  (implicit destructor: CKMenuBase114c's inlined)
//   [x] 0x562330  CKS08MenuPressStart_Destructor_2  (implicit destructor: CKMenuBase114c's inlined)
//   [x] 0x562468  CKS08MenuPressStart_DeletingDestructor  (implicit destructor: CKMenuBase114c's inlined)
//
//   [x] 0x9ca220  CKS08MenuPressStart_IsKindOfClass  [inline]
//   [x] 0x9ca260  CKS08MenuPressStart_GetClassType  [inline]
//   [x] 0x9ca268  CKS08MenuPressStart_GetClassID  [inline]
//   [x] 0x9ca270  CKS08MenuPressStart_vfB8  [inline]
//   [x] 0x9ca278  CKS08MenuPressStart_vfE0  [inline]
//   [x] 0x9ca280  CKS08MenuPressStart_vfBC  [inline]
//   [x] 0x9ca288  CKS08MenuPressStart_vfC0  [inline]
//   [x] 0x9ca298  CKS08MenuPressStart_GetWidgetSlotCount  [inline]
//   [x] 0x9ca2a0  CKS08MenuPressStart_GetWidgetSlots  [inline]
//   [x] 0x9ca2b0  CKS08MenuPressStart_vfC4  [inline]
//   [x] 0x9ca2b8  CKS08MenuPressStart_vfC8  [inline]
//   [x] 0x9ca2c8  CKS08MenuPressStart_vfCC  [inline]
#include "Spyro2008/logic/ui/CKS08MenuPressStart.h"

#include "Spyro2008/logic/CKS08GameManager.h"
#include "k2000/components/CKLocTextAccessor.h"
#include "k2000/graphical/fx/CColorizedScreenData.h"
#include "k2000/graphical/fx/CColorizedScreenFx.h"
#include "k2000/graphical/system/IKVideo.h"
#include "k2000/graphical/system/CKVideoSegment.h"
#include "k2000/graphical/system/CVideoManager.h"
#include "k2000/graphical/system/PS3_CKVideo.h"
#include "k2000/graphical/ui/CKFlashText.h"
#include "k2000/graphical/ui/CText2d.h"
#include "k2000/dictionaries/CKSoundDictionaryID.h"
#include "k2000/logic/sound/CKSound.h"
#include "k2000/managers/CKInput.h"
#include "k2000/misc/Engine.h"
#include "k2000/system/CTimeManager.h"
#include "k2000/system/IKTime.h"
#include "k2000/ui/IKNode2d.h"
#include "k2000/core/Stub.h"
#include "k2000/misc/CoreSingletons.h"

#include "k2000/io/IKFile.h"

// 0x00561ef8 CKS08MenuPressStart_Load
int32_t CKS08MenuPressStart::Load(IKFile* file, int32_t type) {
    CKMenuBase114c::Load(file, type);
    if (type == K_LEVEL_PLATEFORMS) {
        IKFile_ReadRef(file, &m_pUnke0);
        IKFile_ReadRef(file, &m_pColorizedFx);
        IKFile_ReadRef(file, &m_pColorizedData0);
        IKFile_ReadRef(file, &m_pColorizedData1);
        ReadF32LE(file, &m_fUnkf0);
        IKFile_ReadRef(file, &m_pText);
    }
    IKFile_ReadRef(file, &m_pSound);  // outside the type test, as in the original
    return 1;
}

namespace {
// TOC2 constants (0x00c25974 - 0x7b98 .. - 0x7b80).
const float kIdleDelay = 30.0f;           // -0x7b98
const float kIdleDelayAfterDemo = 10.0f;  // -0x7b84
const float kTextDelay = 184.0f;          // -0x7b8c
const float kTextDelayAlt = 173.0f;       // -0x7b90 (AppConfig +0x15 set)

// The text of a CKLocTextAccessor: its first text, else its default one.
IKSerializable* AccessorText(IKSerializable* accessor) {
    CKLocTextAccessor* texts = static_cast<CKLocTextAccessor*>(accessor);
    return texts->m_texts.m_pBlock != nullptr ? texts->m_texts.m_pBlock[0] : texts->m_pText;
}
}  // namespace

// 0x005613b8 CKS08MenuPressStart_OnMenuState_maybe
uint8_t CKS08MenuPressStart::OnMenuState(int32_t phase, uint8_t /*other*/) {
    CKS08GameManager* manager = static_cast<CKS08GameManager*>(m_pGameManager);
    CColorizedScreenFx* fx = static_cast<CColorizedScreenFx*>(m_pColorizedFx);
    IKVideo* video = static_cast<IKVideo*>(m_pUnke0);
    IKTime* frameClock = g_pEngine->m_timeManager->m_pTime;
    if (phase == 1) {
        m_fIdleTimer = kIdleDelay;
        if (video != nullptr) {
            video->m_baData &= ~0x10u;
            video->m_baData = (video->m_baData & ~0x20u) | 0x20;
            video->m_baData &= ~0x40000u;
            video->Start(nullptr);
            fx->ApplyData(static_cast<CColorizedScreenData*>(m_pColorizedData0));
            fx->m_BitProperties = (fx->m_BitProperties & ~CColorizedScreenFx::kActive) | CColorizedScreenFx::kActive;
        }
        if (VfC0()[2] != nullptr) static_cast<CKFlashText*>(VfC0()[2])->SetTextId(AccessorText(m_pText));
        m_bStarted = 0;
        manager->SetPlayerActive(0, 0);
        static_cast<IKNode2d*>(manager->m_unk2A8[0])->Disable();
    } else if (phase == 2) {
        manager->SetPlayerActive(0, 1);
        fx->m_BitProperties &= ~CColorizedScreenFx::kActive;
    } else if (phase == 0) {
        if (m_fIdleTimer > 0.0f) {
            if (m_bStarted == 0) {
                const float timer = m_fIdleTimer;
                m_fIdleTimer = timer - frameClock->m_afDeltaTime[IKTime::SCALABLE_GAME_TIME];
                if (video != nullptr) {
                    if ((video->m_baData & 1) == 0) {
                        video->Start(nullptr);
                        return static_cast<uint8_t>(GetMenuId());
                    }
                    if (video->GetPlaybackPosition() == video->GetFrameCount()) {
                        video->Stop();
                        video->Start(nullptr);
                        return static_cast<uint8_t>(GetMenuId());
                    }
                }
                if (m_fIdleTimer < 0.0f) {
                    // Idle: the demo video (game manager +0x2e0) replaces the press-start one.
                    if (video != nullptr) {
                        video->m_baData &= ~0x10u;
                        video->m_baData = (video->m_baData & ~0x20u) | 0x20;
                        video->Stop();
                    }
                    if (VfC0()[2] != nullptr) static_cast<CKFlashText*>(VfC0()[2])->SetTextId(manager->Vf214());
                    manager->PlayDemoVideo();  // 0x4f6838 CKS08GameManager_CallMember2E0Vf60Arg0_maybe
                    Pause(1);                  // vt+0x54
                    m_fTextTimer = g_pEngine->m_appConfig->parametersHandled != 0 ? kTextDelayAlt : kTextDelay;
                } else {
                    g_pEngine->m_input->FindMappingIndexByName("Flash Manager");  // the result is not used
                    if (m_fOpenInputDelay <= 0.0f && (VfCC()[3] != 0 || g_pEngine->m_input->IsMenuStartPressed())) {
                        // The START sound: the dictionary's sound 0 (if any), its pan reset, played from 0.0 (f31).
                        if (CKSound* sound = CKSoundDictionaryID_GetSound_2(static_cast<CKSoundDictionaryID*>(m_pSound), 0)) {
                            CKSound_ResetPan(sound, 1);
                            CKSound_Play(0.0f, sound);
                        }
                        fx->ApplyData(static_cast<CColorizedScreenData*>(m_pColorizedData1));
                        fx->m_BitProperties = (fx->m_BitProperties & ~CColorizedScreenFx::kActive) | CColorizedScreenFx::kActive;
                        m_bStarted = 1;
                    }
                }
            } else {
                if (video != nullptr) {
                    if ((fx->m_BitProperties & CColorizedScreenFx::kActive) != 0 && fx->m_scColor.m_cCurrent[3] <= 0xf5)
                        return static_cast<uint8_t>(GetMenuId());
                    if ((video->m_baData & 1) != 0) video->Stop();
                }
                manager->m_unkAFC = (manager->m_unkAFC & ~1u) | 1;
            }
        } else {
            // The demo plays: skip or its end brings the press-start screen back.
            g_pEngine->m_input->FindMappingIndexByName("Flash Manager");
            IKVideo* demo = manager->GetDemoVideo();  // vt+0xe0
            if (g_pEngine->m_input->IsMenuSkipPressed() || demo == nullptr || (demo->m_baData & 1) == 0) {
                manager->StopDemoVideo();  // 0x4f6890 CKS08GameManager_CallMember2E0Vf78_maybe
                Resume();                  // vt+0x58
                if (video != nullptr) {
                    video->Start(nullptr);
                    fx->ApplyData(static_cast<CColorizedScreenData*>(m_pColorizedData0));
                    fx->m_BitProperties = (fx->m_BitProperties & ~CColorizedScreenFx::kActive) | CColorizedScreenFx::kActive;
                }
                if (VfC0()[2] != nullptr) static_cast<CKFlashText*>(VfC0()[2])->SetTextId(AccessorText(m_pText));
                m_fIdleTimer = kIdleDelayAfterDemo;
            }
            const float zero = 0.0f;
            if (zero < m_fTextTimer) {
                const float left = m_fTextTimer - frameClock->m_afDeltaTime[IKTime::SCALABLE_GAME_TIME];
                m_fTextTimer = left;
                if (left <= zero && m_aWidgetSlots[0].m_pElement != nullptr) {
                    // The text slot (a CText2d) takes the game manager's press-start text (vt+0x214) through its
                    // vt+0x88 (0x00066440 CText2d_SetTextById).
                    CText2d* text = static_cast<CText2d*>(m_aWidgetSlots[0].m_pElement);
                    text->SetTextById(manager->Vf214());
                }
            }
        }
    }
    return static_cast<uint8_t>(GetMenuId());
}

// 0x00561058 CKS08MenuPressStart_RecursiveRegistration: the referenced objects' registration (the colorized screen data and FX only with the flash UI loaded), then the base.
void CKS08MenuPressStart::RecursiveRegistration(int32_t type) {
    if (m_pFlashUI != nullptr) {
        m_pColorizedData0->RecursiveRegistration(type);
        m_pColorizedData1->RecursiveRegistration(type);
        m_pColorizedFx->RecursiveRegistration(type);
    }
    m_pText->RecursiveRegistration(type);
    m_pSound->RecursiveRegistration(type);
    CKMenuBase114c::RecursiveRegistration(type);
}
