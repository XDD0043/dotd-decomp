// CKSekensLauncherCpnt.cpp - reconstructed original translation unit 0x1f7618-0x1f7ff0 (GAME_TOC1, main_toc1), 28 functions, 25 live.
// Primary class: CKSekensLauncherCpnt  key 0xd46  category Component  size 0x10  vtable 0xb1ead8
// Other owners: CKSrvSekensor (1), SekensList (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x1f7618  CKSekensLauncherCpnt_Delete
//   [ ] 0x1f7668  CKSekensLauncherCpnt_Construct  [dead]
//   [ ] 0x1f7688  CKSekensLauncherCpnt_Construct_2  [dead]
//   [ ] 0x1f76a8  RegisterCKSekensLauncherCpntClass
//   [ ] 0x1f7720  _GLOBAL__I_1f7720
//   [x] 0x1f7730  CKSekensLauncherCpnt_PlaySekens_maybe
//   [x] 0x1f77b0  CKSekensLauncherCpnt_Destructor  (~CKSekensLauncherCpnt)
//   [x] 0x1f7808  CKSekensLauncherCpnt_DeleteArray
//   [x] 0x1f78a8  CKSekensLauncherCpnt_HasSekens
//   [x] 0x1f78d8  CKSrvSekensor_IsSekensLineFinished_maybe
//   [ ] 0x1f7928  CKSekensLauncherCpnt_GetSekensLineCount_maybe  [dead]
//   [x] 0x1f7958  CKSekensLauncherCpnt_IsSekensPlaying_maybe  (IsSekensPlaying; CKHkMovableCharacter::Update calls it)
//   [x] 0x1f79b0  SekensList_IsEntryDone_maybe
//   [ ] 0x1f7a00  CKSekensLauncherCpnt_GetSekens  [dead: no pointer to its descriptor 0xb78060]
//   [x] 0x1f7a18  CKSekensLauncherCpnt_StopSekens_maybe
//   [x] 0x1f7aa8  CKSekensLauncherCpnt_GetCurrentLineIndex_maybe
//   [ ] 0x1f7b20  CKSekensLauncherCpnt_IsSekensPending_maybe  [dead: no pointer to its descriptor 0xb78078]
//   [x] 0x1f7b98  CKSekensLauncherCpnt_IsSekensCurrent
//   [x] 0x1f7c10  CKSekensLauncherCpnt_Create
//   [x] 0x1f7c60  CKSekensLauncherCpnt_CreateArray
//   [x] 0x1f7d20  CKSekensLauncherCpnt_Load
//   [x] 0x1f7ec8  CKSekensLauncherCpnt_MessageProc  (returns 1: the default)
//   [ ] 0x1f7ed0  CKSekensLauncherCpnt_Save
//   [x] 0x1f7ed8  CKSekensLauncherCpnt_PostLoad  (returns 1: the default)
//   [x] 0x1f7ee0  CKSekensLauncherCpnt_RecursiveRegistration  (returns 1, registers nothing: the default)
//   [x] 0x1f7ee8  CKSekensLauncherCpnt_Destroy
//   [x] 0x1f7f38  CKSekensLauncherCpnt_Destructor_2  (~CKSekensLauncherCpnt)
//   [x] 0x1f7f90  CKSekensLauncherCpnt_DeletingDestructor  (~CKSekensLauncherCpnt + delete)
//
//   [ ] 0x9b0e88  CKSekensLauncherCpnt_IsKindOfClass  [inline]
//   [x] 0x9b0eb0  CKSekensLauncherCpnt_GetClassType  [inline]
//   [x] 0x9b0eb8  CKSekensLauncherCpnt_GetClassID  [inline]
#include "k2000/components/CKSekensLauncherCpnt.h"

#include "k2000/components/TVectorLoad.h"
#include "k2000/memory/Mem.h"
#include "k2000/logic/CKSekens.h"
#include "k2000/misc/CKSekensElement.h"
#include "k2000/misc/Engine.h"
#include "k2000/services/CKSrvSekensor.h"

// 0x001f7d20 CKSekensLauncherCpnt_Load
int32_t CKSekensLauncherCpnt::Load(IKFile* file, int32_t type) {
    if (type == K_LEVEL_PLATEFORMS) TVector_LoadRefs(m_vSekens, file);
    return 1;
}

namespace {
CKSrvSekensor* Sekensor() { return static_cast<CKSrvSekensor*>(g_pEngine->m_srvSekensor); }

// 0x001f4960 CKSekens_IsCurrentLineFinished_maybe (CKSekens.cpp unit; its one caller is here): not the current sekens:
// 1; the current one: 0 unless it may be interrupted (flags bit 6), then 1 without a line, else the line's element
// answer (vt+0x50: a block's end byte, a marker's 1).
uint8_t IsCurrentLineFinished(const CKSekens* sekens) {
    if (Sekensor()->GetCurrentSekens() != sekens) return 1;
    if ((sekens->m_flags & 0x40u) == 0) return 0;
    if (sekens->m_i32CurrentLine == -1) return 1;
    return static_cast<CKSekensElement*>(sekens->m_vBlocks.m_pBlock[sekens->m_i32CurrentLine])->Vf50();
}
}  // namespace

// 0x001f7730 CKSekensLauncherCpnt_PlaySekens_maybe
uint8_t CKSekensLauncherCpnt::PlaySekens(uint32_t index) {
    CKSekens* sekens = static_cast<CKSekens*>(m_vSekens.m_pBlock[index]);
    if (sekens == nullptr) return 1;
    Sekensor()->RequestSekens(sekens);  // 0x001f89b0
    return static_cast<uint8_t>(Sekensor()->IsSekensDone(sekens) ^ 1u);  // 0x001f4728
}

// 0x001f78d8 CKSrvSekensor_IsSekensLineFinished_maybe
uint8_t CKSekensLauncherCpnt::IsSekensLineFinished(uint32_t index) const {
    const CKSekens* sekens = static_cast<const CKSekens*>(m_vSekens.m_pBlock[index]);
    if (sekens == nullptr) return 1;
    return IsCurrentLineFinished(sekens);
}

// 0x001f79b0 SekensList_IsEntryDone_maybe
uint8_t CKSekensLauncherCpnt::IsEntryDone(uint32_t index) const {
    const CKSekens* sekens = static_cast<const CKSekens*>(m_vSekens.m_pBlock[index]);
    if (sekens == nullptr) return 1;
    return Sekensor()->IsSekensDone(sekens);
}

// 0x001f7aa8 CKSekensLauncherCpnt_GetCurrentLineIndex_maybe
int32_t CKSekensLauncherCpnt::GetCurrentLineIndex(uint32_t index) const {
    const CKSekens* sekens = static_cast<const CKSekens*>(m_vSekens.m_pBlock[index]);
    if (sekens == nullptr || sekens != Sekensor()->GetCurrentSekens()) return -1;
    return sekens->GetCurrentLineIndex();  // 0x001f3eb0
}

// 0x001f7b98 CKSekensLauncherCpnt_IsSekensCurrent
uint8_t CKSekensLauncherCpnt::IsSekensCurrent(uint32_t index) const {
    const CKSekens* sekens = static_cast<const CKSekens*>(m_vSekens.m_pBlock[index]);
    if (sekens == nullptr) return 0;
    return sekens == Sekensor()->GetCurrentSekens() ? 1 : 0;
}

// 0x001f7a18 CKSekensLauncherCpnt_StopSekens_maybe
uint8_t CKSekensLauncherCpnt::StopSekens(uint32_t index, int32_t stop) {
    CKSekens* sekens = static_cast<CKSekens*>(m_vSekens.m_pBlock[index]);
    if (sekens == nullptr) return 1;
    CKSrvSekensor* sekensor = static_cast<CKSrvSekensor*>(g_pEngine->m_srvSekensor);
    if (stop == 0) return sekensor->CancelSekens(sekens);
    return sekensor->StopSekens(sekens);
}

// C2.8 port-all P11.

// 0x001f77b0 CKSekensLauncherCpnt_Destructor (0x1f7f38 / 0x1f7f90 the same)
CKSekensLauncherCpnt::~CKSekensLauncherCpnt() {
    if (m_vSekens.m_pBlock != nullptr) Mem_FreeAligned16(m_vSekens.m_pBlock);
}

// 0x001f7ee8 CKSekensLauncherCpnt_Destroy
void CKSekensLauncherCpnt::Destroy() {
    if (m_vSekens.m_pBlock != nullptr) Mem_FreeAligned16(m_vSekens.m_pBlock);
    m_vSekens.m_ui32NbUsedElt = 0;
    m_vSekens.m_pBlock = nullptr;
}

// 0x001f7958 CKSekensLauncherCpnt_IsSekensPlaying_maybe
uint8_t CKSekensLauncherCpnt::IsSekensPlaying(uint32_t index) const {
    const CKSekens* sekens = static_cast<const CKSekens*>(m_vSekens.m_pBlock[index]);
    if (sekens == nullptr) return 0;
    return static_cast<uint8_t>(Sekensor()->IsSekensDone(sekens) ^ 1u);  // 0x001f4728
}
