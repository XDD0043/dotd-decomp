//
// Reconstructed original translation unit: 0xa54c0-0xa59c0 (GAME_TOC1, main_toc1), 12 functions, 11 live.
// Primary class: CSectorAnimation  key 0xdcd  category Graphical  size 0xc  vtable 0xb17198
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0xa54c0  CSectorAnimation_Delete  (DOTD_DECLARE_FACTORIES)
//   [ ] 0xa5510  RegisterCSectorAnimationClass
//   [ ] 0xa5588  _GLOBAL__I_a5588
//   [ ] 0xa5598  CSectorAnimation_WriteAnimationStream_maybe  [dead]
//   [x] 0xa55c8  CSectorAnimation_DeleteArray  (DOTD_DECLARE_FACTORIES)
//   [x] 0xa5670  CSectorAnimation_Create
//   [x] 0xa56a8  CSectorAnimation_CreateArray
//   [ ] 0xa5740  CSectorAnimation_Save
//   [x] 0xa5748  CSectorAnimation_Load
//   [x] 0xa58c0  CSectorAnimation_PostLoad
//   [x] 0xa58c8  CSectorAnimation_RecursiveRegistration
//   [x] 0xa5928  CSectorAnimation_Destroy
//
//   [x] 0x9a0480  CSectorAnimation_GetClassType  [inline]
//   [x] 0x9a0488  CSectorAnimation_GetClassID  [inline]
//   [x] 0x9a0490  CSectorAnimation_GetSerializationFlags  [inline]
//   [x] 0x9a0498  CSectorAnimation_Destructor  [inline]
//   [x] 0x9a04b0  CSectorAnimation_IsKindOfClass  [inline]
//   [x] 0x9a04d0  CSectorAnimation_DeletingDestructor  [inline]
#include "k2000/graphical/animation/CSectorAnimation.h"

#include "Renderware/rtanim/RtAnim.h"
#include "Renderware/rwcore/RwStream.h"
#include "k2000/io/IKFile.h"
#include "k2000/memory/Mem.h"
#include "k2000/logic/CKSavingManager.h"
#include "k2000/misc/Engine.h"

// 0x000a5928 CSectorAnimation_Destroy. The count is decremented before each animation and once more at the end:
// BUG(original): it is left at 0xffffffff (the next Load sets it again).
void CSectorAnimation::Destroy() {
    RtAnimAnimation** animation = m_apAnimations;
    if (animation == nullptr) return;
    while (--m_ui32NbAnimations != 0xffffffffu) RtAnimAnimationDestroy(*animation++);  // TocBridge, inlined
    Mem_FreeAligned16(m_apAnimations);
    m_apAnimations = nullptr;
}

// 0x000a5748 CSectorAnimation_Load (level type only). 0xa58c0 CSectorAnimation_PostLoad returns 1 (the
// IKSerializable default).
int32_t CSectorAnimation::Load(IKFile* file, int32_t type) {
    if (type != K_LEVEL_PLATEFORMS) return 1;
    ReadU32LE(file, &m_ui32NbAnimations);
    if (m_ui32NbAnimations == 0) {
        m_apAnimations = nullptr;
        return 1;
    }
    RtAnimAnimation** animations =
        static_cast<RtAnimAnimation**>(Mem_AllocAligned16(m_ui32NbAnimations * sizeof(RtAnimAnimation*)));
    const uint32_t count = m_ui32NbAnimations;
    m_apAnimations = animations;
    RwStream* stream = file->m_pRwStream;
    for (uint32_t i = 0; i < count; ++i) {
        RwStreamFindChunk(stream, 0x1b, nullptr, nullptr);  // the original ignores the result
        RtAnimAnimation* animation = RtAnimAnimationStreamRead(stream);  // 0x707d58
        *animations = animation;
        CSectorAnimation_LoadEntry_maybe(animation, file);
        ++animations;
    }
    return 1;
}

// C2.8 port-all P08.
// 0x000a58c8 CSectorAnimation_RecursiveRegistration
void CSectorAnimation::RecursiveRegistration(int32_t type) {
    if (type == 0) g_pEngine->m_pSavingManager->RegisterSerializableObject(this, nullptr);  // vt+0x24
}
