// CinematicStreamFile.cpp - reconstructed original translation unit 0x7e978-0x7f698 (GAME_TOC1, main_toc1), 17 functions, 15 live.
// Primary owner: CinematicStreamFile (not a registered class)
// Other owners: CinematicStream (3)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [ ] 0x7e978  CinematicStreamFile_Init_2_maybe  [dead]
//   [ ] 0x7e9b0  CinematicStreamFile_Close_maybe
//   [ ] 0x7ea60  CinematicStreamFile_Init_3_maybe  [dead]
//   [ ] 0x7ea98  CinematicStreamFile_Init_maybe
//   [ ] 0x7ead0  CinematicStreamFile_Open_maybe
//   [ ] 0x7ec58  CinematicStreamFile_ContinueRead_maybe
//   [ ] 0x7f088  CinematicStreamFile_RequestRead_maybe
//   [ ] 0x7f208  CinematicStreamFile_RtFSCallback_maybe
//   [ ] 0x7f3e0  KStub_Nop_7f3e0
//   [ ] 0x7f3e8  CinematicStream_ResolveAnimatedNode_maybe
//   [ ] 0x7f4d8  CinematicStream_IsActorSceneLeaf_maybe
//   [ ] 0x7f530  KStub_Nop_7f530
//   [ ] 0x7f538  KStub_Nop_7f538
//   [ ] 0x7f540  CinematicStream_SaveActorMatrix_maybe
//   [x] 0x7f680  KStub_Return36_7f680
//   [ ] 0x7f688  KStub_Nop_7f688
//   [ ] 0x7f690  KStub_Nop_7f690
#include "k2000/animation/AnimBlendSlot.h"
#include "k2000/components/CKCinematicStreamCpnt.h"

// 0x0007f680 KStub_Return36_7f680: 36 = the PS3 size of AnimFloatBlock9 (native: sizeof, as STYLE.md asks).
uint32_t CinematicStream_GetFloatBlock9Size() { return static_cast<uint32_t>(sizeof(AnimFloatBlock9)); }
