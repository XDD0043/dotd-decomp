// CKHkS08CristalKey.cpp - reconstructed original translation unit 0x478940-0x47b688 (GAME_TOC1, main_toc1), 35 functions, 31 live.
// Primary class: CKHkS08CristalKey  key 0x2b42  category Hook  size 0x4c  vtable 0xb27a10
// Other owners: CKHkS08CristalOrb (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x478940  CKHkS08CristalKey_Delete
//   [ ] 0x478990  CKHkS08CristalKey_ApplyStatePreset_maybe
//   [ ] 0x478a08  CKHkS08CristalKey_IsCarriedByHero_2_maybe  [dead]
//   [ ] 0x478af8  CKHkS08CristalKey_IsCarriedByEnemy_maybe
//   [ ] 0x478be8  RegisterCKHkS08CristalKeyClass
//   [ ] 0x478c60  _GLOBAL__I_478c60
//   [ ] 0x478c70  CKHkS08CristalKey_Resume
//   [ ] 0x478c98  CKHkS08CristalKey_Pause
//   [ ] 0x478cc0  CKHkS08CristalKey_SetDefaultState
//   [ ] 0x478d30  CKHkS08CristalKey_Stop
//   [ ] 0x478d58  CKHkS08CristalKey_Start
//   [ ] 0x478da8  CKHkS08CristalKey_PostLoad
//   [ ] 0x478dd0  CKHkS08CristalKey_Save
//   [ ] 0x478df8  CKHkS08CristalKey_RecursiveRegistration
//   [ ] 0x478e20  CKHkS08CristalKey_Destroy
//   [ ] 0x478e48  CKHkS08CristalKey_BaseDestructor
//   [x] 0x478e78  CKHkS08CristalKey_Construct  [dead]
//   [ ] 0x478eb0  CKHkS08CristalKey_Construct_2  [dead]
//   [x] 0x478ee8  CKHkS08CristalKey_DeleteArray
//   [ ] 0x478f88  CKHkS08CristalKey_OnDeactivate
//   [ ] 0x4790f0  CKHkS08CristalKey_DeletingDestructor
//   [ ] 0x479138  CKHkS08CristalKey_Destructor
//   [ ] 0x479168  CKHkS08CristalKey_GetInfo
//   [x] 0x4792c0  CKHkS08CristalKey_CreateArray
//   [x] 0x479370  CKHkS08CristalKey_Create
//   [x] 0x4793c8  CKHkS08CristalKey_Load
//   [ ] 0x479610  CKHkS08CristalKey_UpdateCarriedByHeroTrigger_maybe  [dead]
//   [ ] 0x479738  CKHkS08CristalKey_IsCarriedByHero_maybe
//   [ ] 0x479828  CKHkS08CristalKey_IsCarried_maybe
//   [ ] 0x4799b0  CKHkS08CristalKey_Restart
//   [ ] 0x47a390  CKHkS08CristalKey_MessageProc
//   [ ] 0x47a830  CKHkS08CristalKey_Update
//   [ ] 0x47b0c0  CKHkS08CristalKey_OnActivate
//   [ ] 0x47b630  CKHkS08CristalOrb_Delete
//   [ ] 0x47b680  KStub_ReturnArg4_47b680
//
//   [ ] 0x9c4730  CKHkS08CristalKey_IsKindOfClass  [inline]
//   [ ] 0x9c4788  CKHkS08CristalKey_GetClassType  [inline]
//   [ ] 0x9c4790  CKHkS08CristalKey_GetClassID  [inline]
#include "Spyro2008/hooks/CKHkS08CristalKey.h"

#include "k2000/io/IKFile.h"

// 0x004793c8 CKHkS08CristalKey_Load: the actor base, then the level data (type 0 only). The trigger
// starters are loaded with type 0.
int32_t CKHkS08CristalKey::Load(IKFile* file, int32_t type) {
    CKHkActorBase::Load(file, type);
    if (type == K_LEVEL_PLATEFORMS) {
        IKFile_ReadRef(file, &m_pUnk24);
        IKFile_ReadRef(file, &m_pUnk28);
        ReadU8(file, &m_unk34);
        ReadU8(file, &m_unk38);
        ReadU8(file, &m_unk37);
        ReadU8(file, &m_unk36);
        ReadU8(file, &m_unk3A);
        m_unk3C.Load(file, K_LEVEL_PLATEFORMS);
    }
    return 1;
}
