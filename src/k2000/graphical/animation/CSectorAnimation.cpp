//
// Reconstructed original translation unit: 0x786f0-0x78d18 (GAME_TOC1, main_toc1), 7 functions, 1 live.
// Primary class: CSectorAnimation  key 0xdcd  category Graphical  size 0xc  vtable 0xb17198
// Other owners: Anim (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [ ] 0x786f0  FUN_000786f0  [dead]
//   [ ] 0x787b0  FUN_000787b0  [dead]
//   [ ] 0x787d8  FUN_000787d8  [dead]
//   [x] 0x78830  Anim_GetMarkById
//   [ ] 0x788a8  CSectorAnimation_EntryKeyEquals_maybe  [dead]
//   [ ] 0x78960  CSectorAnimation_LoadEntryStruct_maybe  [dead]
//   [ ] 0x78ac0  CSectorAnimation_SaveEntryStruct_maybe  [dead]
#include "Renderware/rtanim/RtAnim.h"
#include "k2000/logic/animation/CKAnimationMarkContainer.h"

// 0x00078830 Anim_GetMarkById
AnimMark* Anim_GetMarkById(RtAnimAnimation* animation, uint32_t id) {
    const CKAnimationMarkContainer* container =
        static_cast<const CKAnimationMarkContainer*>(RtAnimSectorEntry(animation)->ref20);
    if (container == nullptr) return nullptr;
    for (uint32_t i = container->m_count; i != 0; --i) {
        AnimMark* mark = container->m_ppMarks[i - 1];
        if (mark->m_channel == id) return mark;
    }
    return nullptr;
}
