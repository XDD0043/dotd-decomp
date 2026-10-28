// CinematicStream.cpp - reconstructed original translation unit 0x7f698-0x80a90 (GAME_TOC1, main_toc1), 15 functions, 14 live.
// Primary owner: CinematicStream (not a registered class)
// Other owners: CSGMovable (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [ ] 0x7f698  CinematicStream_RestoreActor_maybe
//   [ ] 0x7f860  CinematicStream_RestartActorAnimIfInList_maybe
//   [ ] 0x7fae0  CinematicStream_DestroyAnimTrackAnimation_maybe
//   [ ] 0x7fb30  CinematicStream_CreateAnimTrackAnimation_maybe
//   [ ] 0x7fc90  CinematicStream_SaveFloatBlock9_maybe
//   [x] 0x7fcb8  CinematicStream_LoadFloatBlock9_maybe
//   [ ] 0x7fce0  CSGMovable_SetLocalMatrix_NullChecked_maybe  [dead]
//   [ ] 0x7fd20  CinematicStream_ResolveSceneLeaf_maybe
//   [ ] 0x7fdf0  CinematicStream_RestoreSecondActor_maybe
//   [ ] 0x7ff90  CinematicStream_RestartActorAnimAndClearNodeFlag2000_maybe
//   [ ] 0x80050  CinematicStream_ApplyAnimTrackTime_maybe
//   [ ] 0x80408  CinematicStream_IsActorSceneLeaf_WithSecond_maybe
//   [ ] 0x804b0  CinematicStream_AttachActor_maybe
//   [ ] 0x80608  CinematicStream_AttachSecondActor_maybe
//   [ ] 0x807b0  CinematicStream_SaveActorMatrices_maybe
//
//   [ ] 0x99b618  CinematicStream_CreateAnimTrackAnimation_Thunk  [inline]
//   [ ] 0x99b640  CinematicStream_DestroyAnimTrackAnimation_Thunk  [inline]
//   [ ] 0x99b668  CinematicStream_ApplyAnimTrackTime_Thunk  [inline]
//   [ ] 0x99b690  CinematicStream_SaveFloatBlock9_Thunk  [inline]
//   [x] 0x99b6b8  CinematicStream_LoadFloatBlock9_Thunk  [inline]
//   [ ] 0x99b6e0  CinematicStream_ResolveAnimatedNode_Thunk  [inline]
//   [x] 0x99b708  CinematicStream_GetFloatBlock9Size_Thunk_maybe  [inline]
//   [ ] 0x99b730  U32Array_Reserve_maybe  [inline]
#include "k2000/animation/AnimBlendSlot.h"
#include "k2000/components/CKCinematicStreamCpnt.h"

// 0x0007fcb8 CinematicStream_LoadFloatBlock9_maybe
int32_t CinematicStream_LoadFloatBlock9(void* buffer, IKFile* file, int32_t /*type*/) {
    AnimFloatBlock9_LoadByteSwapped(static_cast<AnimFloatBlock9*>(buffer), file);
    return 1;
}
