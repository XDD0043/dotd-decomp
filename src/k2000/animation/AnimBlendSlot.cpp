//
// Reconstructed original translation unit: 0x78d18-0x7a018 (GAME_TOC1, main_toc1), 19 functions, 11 live.
// Primary owner: AnimBlendSlot (not a registered class)
// Other owners: Anim (7), AnimFloatBlock9 (2), CSectorAnimation (2)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [ ] 0x78d18  Anim_GetMarkValueAt_Const1Keys2_maybe  [dead]
//   [ ] 0x78e98  Anim_GetMarkValueAt_Const0Keys34_maybe  [dead]
//   [ ] 0x79008  Anim_GetMarkById_Keys2  [dead]
//   [ ] 0x790d8  Anim_GetMarkById_Keys3  [dead]
//   [ ] 0x791a8  Anim_GetMarkById_Keys4  [dead]
//   [ ] 0x79278  Anim_GetMarkById_Const1  [dead]
//   [ ] 0x79348  Anim_GetMarkById_Const0  [dead]
//   [x] 0x79418  AnimFloatBlock9_LoadByteSwapped_maybe
//   [ ] 0x795d8  AnimFloatBlock9_SaveByteSwapped_maybe
//   [x] 0x79898  CSectorAnimation_LoadEntry_maybe
//   [ ] 0x79a88  CSectorAnimation_SaveEntry_maybe  [dead]
//   [ ] 0x79d70  AnimBlendSlot_PostLoadThunk_maybe
//   [x] 0x79d98  AnimBlendSlot_LoadThunk
//   [ ] 0x79dc0  AnimBlendSlot_SaveThunk
//   [ ] 0x79de8  AnimBlendSlot_vf14_ThunkReturn1_maybe
//   [x] 0x79e10  AnimBlendSlot_SetAnimPairAndWeight_maybe
//   [x] 0x79ea0  AnimBlendSlot_CrossfadeToAnim
//   [x] 0x79f30  AnimBlendSlot_AdvanceInactiveTrack_maybe
//   [ ] 0x79ff0  AnimBlendSlot_InitThunk
//
//   [ ] 0x9996e0  AnimBlendSlot_DeletingDestructor  [inline]
//   [ ] 0x999710  AnimBlendSlot_Destructor  [inline]
#include "Renderware/rtanim/RtAnim.h"
#include "k2000/graphical/animation/CSectorAnimation.h"
#include "k2000/io/IKFile.h"

// 0x00079898 CSectorAnimation_LoadEntry_maybe: three swapped reads of 4, 12 and 16 bytes, then a handle.
void CSectorAnimation_LoadEntry_maybe(RtAnimAnimation* animation, IKFile* file) {
    RtAnimSectorEntryData& data = *RtAnimSectorEntry(animation);  // customData + customDataSize - 0x24
    ReadU32LEWords(file, &data.word10, 1);
    ReadU32LEWords(file, data.words14, 3);
    ReadU32LEWords(file, data.words00, 4);
    IKFile_ReadRef(file, &data.ref20);
}
#include "k2000/animation/AnimBlendSlot.h"

// 0x00079d98 AnimBlendSlot_LoadThunk
int32_t AnimBlendSlot_LoadThunk(AnimBlendSlot* slot, IKFile* file, int32_t type) {
    slot->Load(file, type);  // 0x7a730
    return 1;
}

// 0x00079418 AnimFloatBlock9_LoadByteSwapped_maybe
void AnimFloatBlock9_LoadByteSwapped(AnimFloatBlock9* block, IKFile* file) {
    ReadF32LE(file, &block->m_unk10);
    ReadU32LEWords(file, reinterpret_cast<uint32_t*>(block->m_av14), 3);
    ReadU32LEWords(file, block->m_aui32Unk00, 4);
    IKFile_ReadRef(file, &block->m_pUnk20);
}
