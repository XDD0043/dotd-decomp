// Reconstructed original translation unit: 0x264e18-0x264fa8 (GAME_TOC1, main_toc1), 5 functions, 5 live.
// Primary class: CKChoreoKey  key 0x3cc  category Logic  size 0x18  vtable 0xb21400
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x264e18  CKChoreoKey_Delete  (registry factory: DOTD_DECLARE_FACTORIES)
//   [x] 0x264e68  CKChoreoKey_RecursiveRegistration
//   [ ] 0x264ed0  CKChoreoKey_Save
//   [x] 0x264ed8  CKChoreoKey_Destroy  (Spyro2008/groups/CKChoreoKey.h)
//   [ ] 0x264f30  RegisterCKChoreoKeyClass
//
//   [ ] 0x9bb0e0  CKChoreoKey_GetClassType  [inline]
//   [ ] 0x9bb0e8  CKChoreoKey_GetClassID  [inline]
//   [ ] 0x9bb0f0  CKChoreoKey_Destructor  [inline]
//   [ ] 0x9bb158  CKChoreoKey_IsKindOfClass  [inline]
//   [ ] 0x9bb178  CKChoreoKey_DeletingDestructor  [inline]
#include "Spyro2008/groups/CKChoreoKey.h"

#include "k2000/logic/CKSavingManager.h"
#include "k2000/misc/Engine.h"

// 0x00264e68 CKChoreoKey_RecursiveRegistration (returns 1)
void CKChoreoKey::RecursiveRegistration(int32_t type) {
    if (static_cast<uint32_t>(type) - 4u > 3u) g_pEngine->m_pSavingManager->RegisterSerializableObject(this, nullptr);
}
