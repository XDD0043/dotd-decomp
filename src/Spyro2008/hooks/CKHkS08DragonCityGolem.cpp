// CKHkS08DragonCityGolem.cpp - reconstructed original translation unit 0x4d5418-0x4d6cc8 (GAME_TOC1, main_toc1), 30 functions, 28 live.
// Primary class: CKHkS08DragonCityGolem  key 0x31c2  category Hook  size 0xe0  vtable 0xb29df0
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x4d5418  CKHkS08DragonCityGolem_Delete
//   [ ] 0x4d5468  CKHkS08DragonCityGolem_vf100
//   [ ] 0x4d5470  CKHkS08DragonCityGolem_vf104
//   [ ] 0x4d5478  CKHkS08DragonCityGolem_vf108
//   [ ] 0x4d5480  CKHkS08DragonCityGolem_AccumulateDamage_maybe
//   [ ] 0x4d5728  CKHkS08DragonCityGolem_ApplyPendingDamage_maybe
//   [ ] 0x4d5a78  CKHkS08DragonCityGolem_Update
//   [ ] 0x4d5ae8  CKHkS08DragonCityGolem_Resume
//   [ ] 0x4d5b10  CKHkS08DragonCityGolem_Pause
//   [ ] 0x4d5b38  CKHkS08DragonCityGolem_Restart
//   [ ] 0x4d5b90  CKHkS08DragonCityGolem_Stop
//   [x] 0x4d5bb8  CKHkS08DragonCityGolem_Start
//   [x] 0x4d5c10  CKHkS08DragonCityGolem_PostLoad
//   [x] 0x4d5c38  CKHkS08DragonCityGolem_Load
//   [ ] 0x4d5c60  CKHkS08DragonCityGolem_Save
//   [ ] 0x4d5c88  CKHkS08DragonCityGolem_RecursiveRegistration
//   [ ] 0x4d5cb0  CKHkS08DragonCityGolem_Destroy
//   [ ] 0x4d5cd8  CKHkS08DragonCityGolem_Destructor
//   [ ] 0x4d5d50  CKHkS08DragonCityGolem_Construct  [dead]
//   [ ] 0x4d5d90  CKHkS08DragonCityGolem_Construct_2  [dead]
//   [x] 0x4d5dd0  CKHkS08DragonCityGolem_DeleteArray
//   [ ] 0x4d5e78  RegisterCKHkS08DragonCityGolemClass
//   [ ] 0x4d5f00  _GLOBAL__D_4d5f00
//   [ ] 0x4d5f10  _GLOBAL__I_4d5f10
//   [ ] 0x4d5f20  CKHkS08DragonCityGolem_DestructBody
//   [ ] 0x4d5f98  CKHkS08DragonCityGolem_DeletingDestructor
//   [ ] 0x4d6020  CKHkS08DragonCityGolem_GetNearestAimVolume_maybe
//   [x] 0x4d63a0  CKHkS08DragonCityGolem_CreateArray
//   [x] 0x4d6468  CKHkS08DragonCityGolem_Create
//   [ ] 0x4d64c8  CKHkS08DragonCityGolem_ProcessDamageContacts_maybe
//
//   [ ] 0x9c5ec8  CKHkS08DragonCityGolem_IsKindOfClass  [inline]
//   [ ] 0x9c5f28  CKHkS08DragonCityGolem_GetClassType  [inline]
//   [ ] 0x9c5f30  CKHkS08DragonCityGolem_GetClassID  [inline]
#include "Spyro2008/hooks/CKHkS08DragonCityGolem.h"
#include <cstring>
#include "k2000/system/IKTime.h"
#include "k2000/system/CTimeManager.h"
#include "k2000/misc/Engine.h"
#include "Spyro2008/groups/C22SpyroShims.h"

// 0x004d5c38 CKHkS08DragonCityGolem_Load: CKHkGolem's part only.
int32_t CKHkS08DragonCityGolem::Load(IKFile* file, int32_t type) {
    CKHkGolem::Load(file, type);
    return 1;
}

// 0x004d5c10 CKHkS08DragonCityGolem_PostLoad: CKHkGolem's.
int32_t CKHkS08DragonCityGolem::PostLoad(int32_t type) {
    CKHkGolem::PostLoad(type);  // 0x004bf308
    return 1;
}

// 0x004d5bb8 CKHkS08DragonCityGolem_Start
void CKHkS08DragonCityGolem::Start() {
    CKHkGolem::Start();  // 0x004bf970
    m_unkC4[4] = m_unkC4[4] & 0x0000ffffu;  // the bytes at +0xd4 and +0xd5
    m_unkC4[3] = 0;  // +0xd0
    m_unkC4[0] = 0;  // +0xc4
    m_unkC4[5] = 0;  // +0xd8
    m_unkC4[2] = 0;  // +0xcc
    m_unkC4[1] = 0;  // +0xc8
    m_unkC4[6] = 0;  // +0xdc
}
