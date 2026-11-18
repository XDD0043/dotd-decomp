// Reconstructed original translation unit: 0x3f7430-0x3f7950 (GAME_TOC1, main_toc1), 19 functions, 16 live.
// Primary owner: KBase3CC2 (not a registered class)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [ ] 0x3f7430  KBase3CC2_HasOtherHookWithSameId20_maybe  [dead]
//   [ ] 0x3f7558  KBase3CC2_vfA4  [dead: no object is built: the constructors' descriptors 0xbb19a0 / 0xbb19a8 are unreferenced (raw ELF scan), the vtable 0xb24da8 is only stored by them]
//   [ ] 0x3f7580  KBase3CC2_vfA0  [dead: no object is built: the constructors' descriptors 0xbb19a0 / 0xbb19a8 are unreferenced (raw ELF scan), the vtable 0xb24da8 is only stored by them]
//   [ ] 0x3f75d8  KBase3CC2_Update  [dead: no object is built: the constructors' descriptors 0xbb19a0 / 0xbb19a8 are unreferenced (raw ELF scan), the vtable 0xb24da8 is only stored by them]
//   [ ] 0x3f7600  KBase3CC2_vf78  [dead: no object is built: the constructors' descriptors 0xbb19a0 / 0xbb19a8 are unreferenced (raw ELF scan), the vtable 0xb24da8 is only stored by them]
//   [ ] 0x3f7628  KBase3CC2_vf70  [dead: no object is built: the constructors' descriptors 0xbb19a0 / 0xbb19a8 are unreferenced (raw ELF scan), the vtable 0xb24da8 is only stored by them]
//   [ ] 0x3f7650  KBase3CC2_vf68  [dead: no object is built: the constructors' descriptors 0xbb19a0 / 0xbb19a8 are unreferenced (raw ELF scan), the vtable 0xb24da8 is only stored by them]
//   [ ] 0x3f7678  KBase3CC2_vf50  [dead: no object is built: the constructors' descriptors 0xbb19a0 / 0xbb19a8 are unreferenced (raw ELF scan), the vtable 0xb24da8 is only stored by them]
//   [ ] 0x3f76a0  KBase3CC2_PostLoad  [dead: no object is built: the constructors' descriptors 0xbb19a0 / 0xbb19a8 are unreferenced (raw ELF scan), the vtable 0xb24da8 is only stored by them]
//   [ ] 0x3f76c8  KBase3CC2_Load  [dead: no object is built: the constructors' descriptors 0xbb19a0 / 0xbb19a8 are unreferenced (raw ELF scan), the vtable 0xb24da8 is only stored by them]
//   [ ] 0x3f7788  KBase3CC2_Save
//   [ ] 0x3f77b0  KBase3CC2_LevelReset  [dead: no object is built: the constructors' descriptors 0xbb19a0 / 0xbb19a8 are unreferenced (raw ELF scan), the vtable 0xb24da8 is only stored by them]
//   [ ] 0x3f77d8  KBase3CC2_ClearReferences  [dead: no object is built: the constructors' descriptors 0xbb19a0 / 0xbb19a8 are unreferenced (raw ELF scan), the vtable 0xb24da8 is only stored by them]
//   [ ] 0x3f7800  KBase3CC2_DeletingDestructor  [dead: no object is built: the constructors' descriptors 0xbb19a0 / 0xbb19a8 are unreferenced (raw ELF scan), the vtable 0xb24da8 is only stored by them]
//   [ ] 0x3f7848  KBase3CC2_Destructor  [dead: no object is built: the constructors' descriptors 0xbb19a0 / 0xbb19a8 are unreferenced (raw ELF scan), the vtable 0xb24da8 is only stored by them]
//   [ ] 0x3f7878  KBase3CC2_BaseDestructor  [dead: no object is built: the constructors' descriptors 0xbb19a0 / 0xbb19a8 are unreferenced (raw ELF scan), the vtable 0xb24da8 is only stored by them]
//   [ ] 0x3f78a8  KBase3CC2_Construct  [dead]
//   [ ] 0x3f78e0  KBase3CC2_Construct_2  [dead]
//   [ ] 0x3f7918  KBase3CC2_vf54  [dead: no object is built: the constructors' descriptors 0xbb19a0 / 0xbb19a8 are unreferenced (raw ELF scan), the vtable 0xb24da8 is only stored by them]
//
//   [ ] 0x9c0c50  KBase3CC2_IsKindOf  [inline]
//   [ ] 0x9c0ca8  KBase3CC2_GetClassGroup  [inline]
//   [ ] 0x9c0cb0  KBase3CC2_GetClassId  [inline]
//
// C2.8 port-all P18: no object of KBase3CC2 is ever built. Its constructors 0x3f78a8 / 0x3f78e0 have descriptors
// 0xbb19a0 / 0xbb19a8 that nothing points to and no branch reaches (raw ELF scan), and its vtable 0xb24da8 is only
// stored by those constructors and its own destructors (TOC slot 0xc19fb0: five loads, all in this unit). The other
// slots are reachable only through that vtable, so the whole class is dead.
