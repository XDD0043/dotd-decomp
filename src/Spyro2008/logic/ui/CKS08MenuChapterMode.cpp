// CKS08MenuChapterMode.cpp - reconstructed original translation unit 0x548a88-0x549bb0 (GAME_TOC1, main_toc1), 19 functions, 16 live.
// Primary class: CKS08MenuChapterMode  key 0xafcc  category Logic  size 0xf8  vtable 0xb2c340
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x548a88  CKS08MenuChapterMode_Delete
//   [ ] 0x548ad8  CKS08MenuChapterMode_Construct  [dead]
//   [ ] 0x548b80  CKS08MenuChapterMode_Save
//   [x] 0x548ba8  CKS08MenuChapterMode_RecursiveRegistration
//   [x] 0x548cb8  CKS08MenuChapterMode_Destroy  (inherited: CKMenuBase114c::Destroy)
//   [x] 0x548ce0  CKS08MenuChapterMode_DeleteArray
//   [ ] 0x548d88  RegisterCKS08MenuChapterModeClass
//   [ ] 0x548e10  _GLOBAL__D_548e10
//   [ ] 0x548e20  _GLOBAL__I_548e20
//   [ ] 0x548e30  FUN_00548e30  [dead]
//   [x] 0x548ea8  CKS08MenuChapterMode_vfE8
//   [x] 0x548f90  CKS08MenuChapterMode_OnMenuState_maybe
//   [ ] 0x549220  CKS08MenuChapterMode_Construct_2  [dead]
//   [x] 0x5492c8  CKS08MenuChapterMode_CreateArray
//   [x] 0x549410  CKS08MenuChapterMode_Create
//   [x] 0x5494f8  CKS08MenuChapterMode_Load
//   [x] 0x549808  CKS08MenuChapterMode_DeletingDestructor  (implicit destructor: CKMenuBase114c's inlined)
//   [x] 0x549940  CKS08MenuChapterMode_Destructor  (implicit destructor: CKMenuBase114c's inlined)
//   [x] 0x549a78  CKS08MenuChapterMode_Destructor_2  (implicit destructor: CKMenuBase114c's inlined)
//
//   [x] 0x9c97c8  CKS08MenuChapterMode_IsKindOfClass  [inline]
//   [x] 0x9c9808  CKS08MenuChapterMode_GetClassType  [inline]
//   [x] 0x9c9810  CKS08MenuChapterMode_GetClassID  [inline]
//   [x] 0x9c9818  CKS08MenuChapterMode_vfB8  [inline]
//   [x] 0x9c9820  CKS08MenuChapterMode_vfE0  [inline]
//   [x] 0x9c9828  CKS08MenuChapterMode_vfBC  [inline]
//   [x] 0x9c9830  CKS08MenuChapterMode_vfC0  [inline]
//   [x] 0x9c9840  CKS08MenuChapterMode_GetWidgetSlotCount  [inline]
//   [x] 0x9c9848  CKS08MenuChapterMode_GetWidgetSlots  [inline]
//   [x] 0x9c9858  CKS08MenuChapterMode_vfC4  [inline]
//   [x] 0x9c9860  CKS08MenuChapterMode_vfC8  [inline]
//   [x] 0x9c9870  CKS08MenuChapterMode_vfCC  [inline]
//   [x] 0x9c9880  CKS08MenuChapterMode_vfF0  [inline]
//   [x] 0x9c9888  CKS08MenuChapterMode_vfF4  [inline]
#include "Spyro2008/logic/ui/CKS08MenuChapterMode.h"

#include "Spyro2008/logic/CKS08GameManager.h"
#include "Spyro2008/logic/ui/CKS08MenuMain.h"
#include "k2000/graphical/fx/CColorizedScreenData.h"
#include "k2000/graphical/fx/CColorizedScreenFx.h"
#include "k2000/graphical/system/IKVideo.h"
#include "k2000/graphical/system/PS3_CKVideo.h"
#include "k2000/io/IKFile.h"

// 0x005494f8 CKS08MenuChapterMode_Load
int32_t CKS08MenuChapterMode::Load(IKFile* file, int32_t type) {
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

// 0x00548ba8 CKS08MenuChapterMode_RecursiveRegistration: the referenced objects' registration (the colorized screen data and FX only with the flash UI loaded), then the base.
void CKS08MenuChapterMode::RecursiveRegistration(int32_t type) {
    if (m_pFlashUI != nullptr) {
        m_pColorizedData0->RecursiveRegistration(type);
        m_pColorizedData1->RecursiveRegistration(type);
        m_pColorizedFx->RecursiveRegistration(type);
    }
    m_pText->RecursiveRegistration(type);
    CKMenuBase114c::RecursiveRegistration(type);
}

// 0x00548f90 CKS08MenuChapterMode_OnMenuState_maybe
uint8_t CKS08MenuChapterMode::OnMenuState(int32_t phase, uint8_t /*other*/) {
    CColorizedScreenFx* fx = static_cast<CColorizedScreenFx*>(m_pColorizedFx);
    if (phase == 1) {
        CKS08GameManager* manager = static_cast<CKS08GameManager*>(m_pGameManager);
        static_cast<CKS08MenuMain*>(manager->Vf344()[9])->PlayEnterSounds();  // inlined in the original
        m_fTimer = m_fDuration;
        IKVideo* video = static_cast<IKVideo*>(m_pUnkdc);
        if (video != nullptr) {
            video->m_baData &= ~0x10u;
            video->m_baData = (video->m_baData & ~0x20u) | 0x20;
            video->Start(nullptr);  // vt+0x60
            fx->ApplyData(static_cast<CColorizedScreenData*>(m_pColorizedData0));
            fx->m_BitProperties = (fx->m_BitProperties & ~CColorizedScreenFx::kActive) | CColorizedScreenFx::kActive;
        }
        m_unkec = 0;
    } else if (phase == 2) {
        IKVideo* video = static_cast<IKVideo*>(m_pUnkdc);
        if (video != nullptr && (video->m_baData & 1) != 0) video->Stop();  // vt+0x78
        fx->m_BitProperties &= ~CColorizedScreenFx::kActive;
    } else if (phase == 0) {
        IKVideo* video = static_cast<IKVideo*>(m_pUnkdc);
        if (video != nullptr) {
            if ((video->m_baData & 1) == 0) {
                video->Start(nullptr);
            } else if (video->GetPlaybackPosition() == video->GetFrameCount()) {
                video->Stop();
                video->Start(nullptr);
            }
        }
    }
    return static_cast<uint8_t>(GetMenuId());
}

// 0x00548ea8 CKS08MenuChapterMode_vfE8
void CKS08MenuChapterMode::OnItemState(uint8_t item, uint8_t state, uint8_t phase) {
    if (phase != 1 || state != 4) return;
    CKS08GameManager* manager = static_cast<CKS08GameManager*>(m_pGameManager);
    if (item == 0) {
        MenuGm_RequestMenu(manager, 0x23);  // vt+0x304, +0x318 = 1, +0x310 = the id
    } else if (item == 1) {
        MenuGm_RequestMenu(manager, 3);
    }
}
