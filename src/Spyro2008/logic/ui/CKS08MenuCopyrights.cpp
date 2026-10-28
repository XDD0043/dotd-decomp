// CKS08MenuCopyrights.cpp - reconstructed original translation unit 0x549bb0-0x54ad98 (GAME_TOC1, main_toc1), 18 functions, 15 live.
// Primary class: CKS08MenuCopyrights  key 0xaacc  category Logic  size 0xf8  vtable 0xb2c448
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x549bb0  CKS08MenuCopyrights_Delete
//   [ ] 0x549c00  CKS08MenuCopyrights_Construct  [dead]
//   [ ] 0x549ca8  CKS08MenuCopyrights_Save
//   [ ] 0x549cd0  CKS08MenuCopyrights_RecursiveRegistration
//   [ ] 0x549de0  CKS08MenuCopyrights_Destroy
//   [x] 0x549e08  CKS08MenuCopyrights_DeleteArray
//   [ ] 0x549eb0  RegisterCKS08MenuCopyrightsClass
//   [ ] 0x549f38  _GLOBAL__D_549f38
//   [ ] 0x549f48  _GLOBAL__I_549f48
//   [ ] 0x549f58  FUN_00549f58  [dead]
//   [x] 0x549fd0  CKS08MenuCopyrights_OnMenuState_maybe
//   [ ] 0x54a408  CKS08MenuCopyrights_Construct_2  [dead]
//   [x] 0x54a4b0  CKS08MenuCopyrights_CreateArray
//   [x] 0x54a5f8  CKS08MenuCopyrights_Create
//   [x] 0x54a6e0  CKS08MenuCopyrights_Load
//   [ ] 0x54a9f0  CKS08MenuCopyrights_Destructor_2
//   [ ] 0x54ab28  CKS08MenuCopyrights_DeletingDestructor
//   [ ] 0x54ac60  CKS08MenuCopyrights_Destructor
//
//   [x] 0x9c9890  CKS08MenuCopyrights_IsKindOfClass  [inline]
//   [x] 0x9c98d0  CKS08MenuCopyrights_GetClassType  [inline]
//   [x] 0x9c98d8  CKS08MenuCopyrights_GetClassID  [inline]
//   [x] 0x9c98e0  CKS08MenuCopyrights_vfB8  [inline]
//   [x] 0x9c98e8  CKS08MenuCopyrights_vfE0  [inline]
//   [x] 0x9c98f0  CKS08MenuCopyrights_vfBC  [inline]
//   [x] 0x9c98f8  CKS08MenuCopyrights_vfC0  [inline]
//   [x] 0x9c9908  CKS08MenuCopyrights_GetWidgetSlotCount  [inline]
//   [x] 0x9c9910  CKS08MenuCopyrights_GetWidgetSlots  [inline]
//   [x] 0x9c9920  CKS08MenuCopyrights_vfC4  [inline]
//   [x] 0x9c9928  CKS08MenuCopyrights_vfC8  [inline]
//   [x] 0x9c9938  CKS08MenuCopyrights_vfCC  [inline]
#include "Spyro2008/logic/ui/CKS08MenuCopyrights.h"

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

// 0x0054a6e0 CKS08MenuCopyrights_Load
int32_t CKS08MenuCopyrights::Load(IKFile* file, int32_t type) {
    CKMenuBase114c::Load(file, type);
    if (type != K_LEVEL_PLATEFORMS) return 1;
    IKFile_ReadRef(file, &m_pUnkdc);
    IKFile_ReadRef(file, &m_pColorizedFx);
    IKFile_ReadRef(file, &m_pColorizedData0);
    IKFile_ReadRef(file, &m_pColorizedData1);
    ReadF32LE(file, &m_fDuration);
    ReadU8(file, &m_unked);
    IKFile_ReadRef(file, &m_pText);
    return 1;
}

// 0x00549fd0 CKS08MenuCopyrights_OnMenuState_maybe. Enter: the timer from m_fDuration, the video played
// from its first frame (flag 0x10 cleared, 0x20 set) with the fade-in (m_pColorizedData0), player 0
// inactive, the game manager's first full-screen billboard hidden. Update: the timer counts down on the
// scaled clock (skip, when allowed, ends it at once), the video restarted at its last frame; at the end the
// fade-out (m_pColorizedData1); once it is (nearly) opaque (alpha 0xf6) or done, the video stopped and the
// game manager's flag bit 0 set (CKS08GameManager_State4_maybe then leaves). Leave: player 0 active, the
// video stopped, the fade inactive.
uint8_t CKS08MenuCopyrights::OnMenuState(int32_t phase, uint8_t /*other*/) {
    CKS08GameManager* manager = static_cast<CKS08GameManager*>(m_pGameManager);
    CColorizedScreenFx* fx = static_cast<CColorizedScreenFx*>(m_pColorizedFx);
    IKVideo* video = static_cast<IKVideo*>(m_pUnkdc);
    if (phase == 1) {
        m_fTimer = m_fDuration;
        if (video != nullptr) {
            video->m_baData &= ~0x10u;
            video->m_baData = (video->m_baData & ~0x20u) | 0x20;
            video->Start(nullptr);
            fx->ApplyData(static_cast<CColorizedScreenData*>(m_pColorizedData0));
            fx->m_BitProperties = (fx->m_BitProperties & ~CColorizedScreenFx::kActive) | CColorizedScreenFx::kActive;
        }
        m_unkec = 0;
        manager->SetPlayerActive(0, 0);                                // vt+0x184
        static_cast<IKNode2d*>(manager->m_unk2A8[0])->Disable();      // vt+0x68
    } else if (phase == 2) {
        manager->SetPlayerActive(0, 1);
        if (video != nullptr && (video->m_baData & 1) != 0) video->Stop();
        fx->m_BitProperties &= ~CColorizedScreenFx::kActive;
    } else if (phase == 0) {
        if (m_unkec == 0) {
            float timer = m_fTimer;
            if (timer <= 0.0f) {
                fx->ApplyData(static_cast<CColorizedScreenData*>(m_pColorizedData1));
                fx->m_BitProperties = (fx->m_BitProperties & ~CColorizedScreenFx::kActive) | CColorizedScreenFx::kActive;
                m_unkec = 1;
            } else {
                if (m_unked != 0) {
                    if (g_pEngine->m_input->IsMenuSkipPressed()) {
                        fx->ApplyData(static_cast<CColorizedScreenData*>(m_pColorizedData1));
                        fx->m_BitProperties = (fx->m_BitProperties & ~CColorizedScreenFx::kActive) | CColorizedScreenFx::kActive;
                        timer = m_fTimer;
                        m_unkec = 1;
                    } else {
                        timer = m_fTimer;
                    }
                }
                m_fTimer = timer - g_pEngine->m_timeManager->m_pTime->m_afDeltaTime[IKTime::SCALABLE_GAME_TIME];
                if (video != nullptr) {
                    if ((video->m_baData & 1) == 0) {
                        video->Start(nullptr);
                    } else if (video->GetPlaybackPosition() == video->GetFrameCount()) {
                        video->Stop();
                        video->Start(nullptr);
                    }
                }
            }
        } else {
            if (video != nullptr) {
                if ((fx->m_BitProperties & CColorizedScreenFx::kActive) != 0 && fx->m_scColor.m_cCurrent[3] < 0xf6)
                    return static_cast<uint8_t>(GetMenuId());
                video->Stop();
            }
            manager->m_unkAFC = (manager->m_unkAFC & ~1u) | 1;
        }
    }
    return static_cast<uint8_t>(GetMenuId());
}
