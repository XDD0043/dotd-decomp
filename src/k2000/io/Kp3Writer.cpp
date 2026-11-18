// Kp3Writer.cpp - the KP3 writer (an export path: Kp3Writer_WriteCategory has no caller in the binary).
//
// Reconstructed original translation unit: 0x26648-0x27e68 (GAME_TOC1, main_toc1), 12 functions, 6 live.
// Primary owner: Kp3Writer (not a registered class)
// Other owners: CKLoadingManager (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [ ] 0x26648  Kp3Writer_BeginCategory  [dead: only Kp3Writer_WriteCategory 0x26e70 calls it]
//   [ ] 0x267c8  Kp3Writer_PushOffsetPlaceholder  [dead: no pointer to its descriptor 0xb38af8, no call (raw ELF scan)]
//   [ ] 0x26898  Kp3Writer_WriteObject  [dead: only Kp3Writer_WriteClassBlock 0x26a98 calls it]
//   [ ] 0x26a98  Kp3Writer_WriteClassBlock  [dead: only Kp3Writer_WriteCategory 0x26e70 calls it]
//   [ ] 0x26e70  Kp3Writer_WriteCategory  [dead: no pointer to its descriptor 0xb38b10, no call (raw ELF scan; Ghidra's two DATA refs from Cgc_* are constants)]
//   [ ] 0x270f8  FUN_000270f8  [dead]
//   [ ] 0x276b8  FUN_000276b8  [dead]
//   [ ] 0x27c78  FUN_00027c78  [dead]
//   [ ] 0x27cf8  FUN_00027cf8  [dead]
//   [x] 0x27d78  CKLoadingManager_Delete  (the registry factory Delete: DOTD_DECLARE_FACTORIES(CKLoadingManager))
//   [ ] 0x27dc8  KStub_Return0_27dc8  [dead]
//   [ ] 0x27dd0  FUN_00027dd0  [dead]
//
//   [ ] 0x9938a0  HashTableU32_Destructor  [inline]
//   [ ] 0x9939c0  HashTableU32_DeletingDestructor  [inline]
//   [ ] 0x993ae0  IKLoadingInterfaces_IsKindOf  [inline]
