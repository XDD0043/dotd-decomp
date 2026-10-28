// CKS08MenuBonus.cpp - reconstructed original translation unit 0x56d6b8-0x56eb18 (GAME_TOC2, main_toc2), 25 functions, 22 live.
// Primary class: CKS08MenuBonus  key 0x830c  category Logic  size ?  vtable 0xb2d9f0
// Other owners: CKWaterSplashFxData (1), CKWaterWaveFxData (1), CKBlurFxData (1), CKLightningBoltFxData (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x56d6b8  CKS08MenuBonus_Delete
//   [ ] 0x56d708  CKS08MenuBonus_Construct  [dead]
//   [x] 0x56d7b0  CKS08MenuBonus_vfE8
//   [ ] 0x56d7b8  CKS08MenuBonus_UpdateItemEnabledStates_maybe  [dead]
//   [x] 0x56daa8  CKS08MenuBonus_UpdateVideoPlayback_maybe
//   [ ] 0x56dc28  CKS08MenuBonus_LaunchItem_maybe
//   [x] 0x56dd20  CKS08MenuBonus_Load
//   [ ] 0x56dd48  CKS08MenuBonus_Save
//   [ ] 0x56dd70  CKS08MenuBonus_RecursiveRegistration
//   [ ] 0x56dd98  CKS08MenuBonus_Destroy
//   [x] 0x56ddc0  CKS08MenuBonus_DeleteArray
//   [ ] 0x56de60  RegisterCKS08MenuBonusClass
//   [ ] 0x56dee8  _GLOBAL__D_56dee8
//   [ ] 0x56def8  _GLOBAL__I_56def8
//   [ ] 0x56df08  CKS08MenuBonus_Construct_2  [dead]
//   [x] 0x56dfb0  CKS08MenuBonus_CreateArray
//   [x] 0x56e0f0  CKS08MenuBonus_Create
//   [x] 0x56e1d8  CKS08MenuBonus_OnMenuState_maybe
//   [ ] 0x56e630  CKS08MenuBonus_DeletingDestructor
//   [ ] 0x56e768  CKS08MenuBonus_Destructor
//   [ ] 0x56e8a0  CKS08MenuBonus_Destructor_2
//   [ ] 0x56e9d8  CKWaterSplashFxData_Delete
//   [ ] 0x56ea28  CKWaterWaveFxData_Delete
//   [ ] 0x56ea78  CKBlurFxData_Delete
//   [ ] 0x56eac8  CKLightningBoltFxData_Delete
//
//   [x] 0x9ca830  CKS08MenuBonus_IsKindOfClass  [inline]
//   [x] 0x9ca870  CKS08MenuBonus_GetClassType  [inline]
//   [x] 0x9ca878  CKS08MenuBonus_GetClassID  [inline]
//   [x] 0x9ca880  CKS08MenuBonus_vfB8  [inline]
//   [x] 0x9ca888  CKS08MenuBonus_vfE0  [inline]
//   [x] 0x9ca890  CKS08MenuBonus_vfC4  [inline]
//   [x] 0x9ca898  CKS08MenuBonus_vfC8  [inline]
//   [x] 0x9ca8a8  CKS08MenuBonus_vfCC  [inline]
//   [x] 0x9ca8b8  CKS08MenuBonus_vfBC  [inline]
//   [x] 0x9ca8c0  CKS08MenuBonus_vfC0  [inline]
//   [x] 0x9ca8d0  CKS08MenuBonus_GetWidgetSlotCount  [inline]
//   [x] 0x9ca8d8  CKS08MenuBonus_GetWidgetSlots  [inline]
#include "Spyro2008/logic/ui/CKS08MenuBonus.h"
#include "k2000/misc/Engine.h"
#include "k2000/managers/CKInput.h"
#include "k2000/logic/CKInterfaceButton.h"
#include "k2000/graphical/system/IKVideo.h"
#include "Spyro2008/logic/CKS08GameStructure.h"
#include "Spyro2008/logic/CKS08GameManager.h"

// 0x0056dd20 CKS08MenuBonus_Load (through TocBridge_CKMenuBase_114c_maybe_Load 0x98f720)
int32_t CKS08MenuBonus::Load(IKFile* file, int32_t type) {
    CKMenuBase114c::Load(file, type);
    return 1;
}

// 0x0056daa8 CKS08MenuBonus_UpdateVideoPlayback_maybe
void CKS08MenuBonus::UpdateVideoPlayback() {
    CKS08GameManager* manager = static_cast<CKS08GameManager*>(m_pGameManager);
    if (m_bVideoPlaying != 0) {
        if (m_pVideo == nullptr) return;
        if ((m_pVideo->m_baData & 1) == 0) {
            m_pVideo = nullptr;
            m_bVideoPlaying = 0;
        } else if (manager->IsVideoSkipPressed() != 0) {  // vt+0x1e4
            m_pVideo->Stop();  // vt+0x78
            m_bVideoPlaying = 0;
            m_pVideo = nullptr;
        }
        if (m_bVideoPlaying != 0) return;
    }
    if ((m_ui32Flags & 0x10) == 0) return;
    PlayScreenVideo(3, 1);
    m_ui32Flags &= ~0x10u;
    manager->SetPlayerActive(0, 1);
    g_pEngine->m_input->ClearAllStates();
}

// 0x0056e1d8 CKS08MenuBonus_OnMenuState_maybe
uint8_t CKS08MenuBonus::OnMenuState(int32_t phase, uint8_t /*other*/) {
    CKS08GameManager* manager = static_cast<CKS08GameManager*>(m_pGameManager);
    if (phase == 0) {
        if (m_bVideoPlaying == 0) {
            for (uint32_t i = 0; i != 8; ++i) {
                if (i >= m_apButtons.m_ui32NbUsedElt) continue;
                CKInterfaceButton* button = static_cast<CKInterfaceButton*>(m_apButtons.m_pBlock[i]);
                if (button == nullptr || button->m_aStates[4].m_vVideos.m_ui32NbUsedElt == 0) continue;
                IKVideo* video = static_cast<IKVideo*>(button->m_aStates[4].m_vVideos.m_pBlock[0].m_first);
                if (video == nullptr || (video->m_baData & 1) == 0) continue;
                m_pVideo = video;
                m_bVideoPlaying = 1;
                m_ui32Flags = (m_ui32Flags & ~0x10u) | 0x10u;
                manager->SetPlayerActive(0, 0);
                g_pEngine->m_input->ClearAllStates();
            }
        }
        UpdateVideoPlayback();
    } else if (phase == 1) {
        CKS08GameStructure* structure = static_cast<CKS08GameStructure*>(manager->m_gameStructure);
        m_bVideoPlaying = 0;
        m_pVideo = nullptr;
        // The items from the last: 7 and 6 from +0x250 / +0x24f, 5 and 4 always enabled, 3..0 from
        // +0x24e..+0x24b (each byte is "unlocked").
        static const int16_t kUnlock[8] = {0x24b, 0x24c, 0x24d, 0x24e, -1, -1, 0x24f, 0x250};
        for (uint32_t i = 8; i-- != 0;) {
            if (i >= m_apButtons.m_ui32NbUsedElt) continue;
            CKInterfaceButtonBase* button = static_cast<CKInterfaceButtonBase*>(m_apButtons.m_pBlock[i]);
            if (button == nullptr) continue;
            const uint8_t disabled = kUnlock[i] < 0 ? 0 : static_cast<uint8_t>(structure->m_unk1f0[kUnlock[i] - 0x1f0] ^ 1);
            button->SetDisabled(disabled);
        }
    }
    return static_cast<uint8_t>(GetMenuId());
}
