// CAnimationDictionary.cpp - reconstructed original translation unit 0x7a018-0x7a710 (GAME_TOC1, main_toc1), 17 functions, 15 live.
// Primary class: CAnimationDictionary  key 0x49  category Dictionary  size 0x18  vtable 0xb131a8
// Other owners: AnimBlendSlot (2)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x7a018  CAnimationDictionary_Delete
//   [ ] 0x7a068  CAnimationDictionary_Construct  [dead]
//   [ ] 0x7a088  CAnimationDictionary_Construct_2  [dead]
//   [x] 0x7a0a8  CAnimationDictionary_RecursiveRegistration
//   [ ] 0x7a108  CAnimationDictionary_Save
//   [ ] 0x7a110  RegisterCAnimationDictionaryClass
//   [ ] 0x7a188  _GLOBAL__I_7a188
//   [x] 0x7a198  CAnimationDictionary_Destroy
//   [x] 0x7a1e0  CAnimationDictionary_DeleteArray
//   [x] 0x7a288  CAnimationDictionary_PostLoad  (DOTD: resolved on use)
//   [x] 0x7a338  CAnimationDictionary_Create
//   [x] 0x7a388  CAnimationDictionary_CreateArray
//   [x] 0x7a438  CAnimationDictionary_Load
//   [x] 0x7a660  AnimBlendSlot_ClearReferences_maybe
//   [x] 0x7a670  KStub_Return1_7a670  (AnimBlendSlot::Vf14, AnimBlendSlot.h)
//   [ ] 0x7a678  AnimBlendSlot_Save
//   [x] 0x7a708  KStub_Return1_7a708  (AnimBlendSlot::PostLoad, AnimBlendSlot.h)
//
//   [ ] 0x991588  CAnimationDictionary_GetClassType  [inline]
//   [ ] 0x991590  CAnimationDictionary_GetClassID  [inline]
//   [ ] 0x991598  CAnimationDictionary_GetSerializationFlags  [inline]
//   [ ] 0x991820  CAnimationDictionary_IsKindOfClass  [inline]
//   [ ] 0x992150  CAnimationDictionary_DeletingDestructor  [inline]
//   [ ] 0x992190  CAnimationDictionary_Destructor  [inline]
#include "k2000/dictionaries/CAnimationDictionary.h"

#include "k2000/io/IKFile.h"
#include "k2000/memory/Mem.h"
#include "k2000/logic/CKSavingManager.h"
#include "k2000/misc/Engine.h"

// 0x0007a0a8 CAnimationDictionary_RecursiveRegistration
void CAnimationDictionary::RecursiveRegistration(int32_t type) {
    if (type == 0) g_pEngine->m_pSavingManager->RegisterSerializableObject(this, nullptr);  // vt+0x24
}

// 0x0007a438 CAnimationDictionary_Load
int32_t CAnimationDictionary::Load(IKFile* file, int32_t /*type*/) {
    ReadU32LE(file, &m_ui32NbAnimations);
    ReadU32LE(file, &m_ui32NbColumns);
    if (m_ui32NbAnimations == 0) {
        m_apAnimations = nullptr;
        return 1;
    }
    m_apAnimations = static_cast<int32_t*>(Mem_AllocAligned16(m_ui32NbAnimations * 4 * m_ui32NbColumns));
    const uint32_t count = m_ui32NbAnimations * m_ui32NbColumns;
    ReadU32LEWords(file, reinterpret_cast<uint32_t*>(m_apAnimations), count & 0x3fffffffu);
    ReadU32LE(file, &m_unk10);
    ReadRaw(file, &m_unk14, 1);
    return 1;
}

// 0x0007a198 CAnimationDictionary_Destroy
void CAnimationDictionary::Destroy() {
    if (m_apAnimations != nullptr) {
        Mem_FreeAligned16(m_apAnimations);
        m_apAnimations = nullptr;
    }
}
