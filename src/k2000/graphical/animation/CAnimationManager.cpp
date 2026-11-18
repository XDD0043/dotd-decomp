// CAnimationManager.cpp - reconstructed original translation unit 0x92830-0x92e00 (GAME_TOC1, main_toc1), 13 functions, 11 live.
// Primary class: CAnimationManager  key 0x20d  category Graphical  size 0xc  vtable 0xb15650
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x92830  CAnimationManager_Delete
//   [x] 0x92880  CAnimationManager_RecursiveRegistration
//   [ ] 0x928d8  CAnimationManager_Save
//   [x] 0x928e0  CAnimationManager_PostLoad  (CAnimationManager.h)
//   [ ] 0x928e8  RegisterCAnimationManagerClass
//   [ ] 0x92960  _GLOBAL__I_92960
//   [x] 0x92970  CAnimationManager_Load
//   [x] 0x92b00  CAnimationManager_Destroy
//   [ ] 0x92b48  CAnimationManager_Construct  [dead]
//   [ ] 0x92ba0  CAnimationManager_Construct_2  [dead]
//   [x] 0x92bf8  CAnimationManager_DeleteArray
//   [x] 0x92ca0  CAnimationManager_CreateArray
//   [x] 0x92d80  CAnimationManager_Create
//
//   [x] 0x996770  CAnimationManager_GetClassType  [inline]
//   [x] 0x996778  CAnimationManager_GetClassID  [inline]
//   [x] 0x996780  CAnimationManager_GetSerializationFlags  [inline]
//   [ ] 0x996788  HashTableU32_HashKey_4  [inline]
//   [ ] 0x9967a0  HashTableU32_KeysEqual_4  [inline]
//   [ ] 0x9967c0  KStub_Nop_9967c0  [inline]
//   [ ] 0x9967c8  HashTableU32_InitNode_4  [inline]
//   [ ] 0x996818  HashTableStr_HashKey_2  [inline]
//   [ ] 0x996868  HashTableStr_FreeNodeKey_2  [inline]
//   [ ] 0x9968a0  HashTableStr_InitNode_2  [inline]
//   [ ] 0x996940  HashTableStr_KeysEqual  [inline]
//   [x] 0x996988  CAnimationManager_IsKindOfClass  [inline]
//   [x] 0x997278  CAnimationManager_DeletingDestructor  [inline]
//   [x] 0x9972b8  CAnimationManager_Destructor  [inline]
#include "k2000/graphical/animation/CAnimationManager.h"

#include "Renderware/rtanim/RtAnim.h"
#include "k2000/io/IKFile.h"
#include "k2000/graphical/animation/CSectorAnimation.h"
#include "k2000/memory/Mem.h"
#include "k2000/misc/Engine.h"
#include "k2000/logic/CKSavingManager.h"

// 0x00092d80 CAnimationManager_Create (the constructor inlined)
CAnimationManager::CAnimationManager() {
    RtAnimGetInterpolatorInfo(1)->customDataSize += static_cast<RwInt32>(sizeof(RtAnimSectorEntryData));
    RtAnimGetInterpolatorInfo(2)->customDataSize += static_cast<RwInt32>(sizeof(RtAnimSectorEntryData));
}

// 0x00092b00 CAnimationManager_Destroy: the animation table freed.
void CAnimationManager::Destroy() {
    if (m_apAnimations != nullptr) {
        Mem_FreeAligned16(m_apAnimations);
        m_apAnimations = nullptr;
    }
}

// 0x00092970 CAnimationManager_Load
int32_t CAnimationManager::Load(IKFile* file, int32_t type) {
    if (type != K_LEVEL_PLATEFORMS) return 1;
    ReadU32LE(file, &m_ui32NbAnimations);
    if (m_ui32NbAnimations == 0) {
        m_apAnimations = nullptr;
        return 1;
    }
    // BUG(original)?: 0xc bytes (three pointers) per animation are allocated; only the first
    // m_ui32NbAnimations pointers are filled.
    m_apAnimations = static_cast<IKSerializable**>(
        Mem_AllocAligned16(m_ui32NbAnimations * 3 * static_cast<uint32_t>(sizeof(IKSerializable*))));
    IKFile_ReadObjectRefArray(file, m_apAnimations, m_ui32NbAnimations);
    return 1;
}

// CAnimationDictionary_PostLoad 0x0007a288's resolution of one word.
RtAnimAnimation* CAnimationManager_GetAnimation(uint32_t word) {
    if (word == 0xffffffffu) return nullptr;
    CAnimationManager* manager = g_pEngine->m_animationManager;
    CSectorAnimation* sector = static_cast<CSectorAnimation*>(manager->m_apAnimations[word >> 24]);
    return sector->m_apAnimations[word & 0xffffffu];
}

// DOTD: the reverse lookup (see the header).
uint32_t CAnimationManager_GetAnimationWord(const RtAnimAnimation* animation) {
    if (animation == nullptr) return 0xffffffffu;
    CAnimationManager* manager = g_pEngine->m_animationManager;
    for (uint32_t s = 0; s < manager->m_ui32NbAnimations; ++s) {
        const CSectorAnimation* sector = static_cast<const CSectorAnimation*>(manager->m_apAnimations[s]);
        // A destroyed sector (CSectorAnimation_Destroy 0xa55c8-style loop) keeps the count at -1 with no array.
        if (sector == nullptr || sector->m_apAnimations == nullptr) continue;
        for (uint32_t i = 0; i < sector->m_ui32NbAnimations; ++i) {
            if (sector->m_apAnimations[i] == animation) return (s << 24) | i;
        }
    }
    return 0xffffffffu;
}

// C2.8 port-all P08.
// 0x00092880 CAnimationManager_RecursiveRegistration: no type test.
void CAnimationManager::RecursiveRegistration(int32_t /*type*/) {
    g_pEngine->m_pSavingManager->RegisterSerializableObject(this, nullptr);  // vt+0x24
}
