// Vt_3.cpp - the default save device's slots (KSaveDevice in k2000/io/KFileSystem.h).
//
// Reconstructed original translation unit: 0x4c1f0-0x4cc08 (GAME_TOC1, main_toc1), 52 functions, 38 live.
// Primary owner: Vt (not a registered class)
// Other owners: KFileSystem (4), KFileDevice (2)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [ ] 0x4c1f0  Vt_b14fe0_DeletingDestructor_maybe  [platform]  (the PS3 save / file device stack (the default save device, vtable 0xb150d8, and its buffered save file 0xb15060 / 0xb14fe0; KSaveDevice in io/KFileSystem.h models only the slot KFileSystem calls): the remake's save data is platform/cell/savedata)
//   [ ] 0x4c238  Vt_b14fe0_Destructor_maybe  [platform]  (the PS3 save / file device stack (the default save device, vtable 0xb150d8, and its buffered save file 0xb15060 / 0xb14fe0; KSaveDevice in io/KFileSystem.h models only the slot KFileSystem calls): the remake's save data is platform/cell/savedata)
//   [ ] 0x4c268  Vt_b14fe0_Destructor_2_maybe  [dead]
//   [ ] 0x4c298  Vt_b14fe0_Construct_maybe  [dead]
//   [ ] 0x4c2e0  Vt_b14fe0_Construct_2_maybe  [dead]
//   [ ] 0x4c328  KStub_Return1_4c328  [platform]  (the PS3 save / file device stack (the default save device, vtable 0xb150d8, and its buffered save file 0xb15060 / 0xb14fe0; KSaveDevice in io/KFileSystem.h models only the slot KFileSystem calls): the remake's save data is platform/cell/savedata)
//   [ ] 0x4c330  KStub_Return0_4c330  [platform]  (the PS3 save / file device stack (the default save device, vtable 0xb150d8, and its buffered save file 0xb15060 / 0xb14fe0; KSaveDevice in io/KFileSystem.h models only the slot KFileSystem calls): the remake's save data is platform/cell/savedata)
//   [ ] 0x4c338  Vt_b15060_Close_maybe  [platform]  (the PS3 save / file device stack (the default save device, vtable 0xb150d8, and its buffered save file 0xb15060 / 0xb14fe0; KSaveDevice in io/KFileSystem.h models only the slot KFileSystem calls): the remake's save data is platform/cell/savedata)
//   [ ] 0x4c450  Vt_b15060_AllocBuffer_maybe  [platform]  (the PS3 save / file device stack (the default save device, vtable 0xb150d8, and its buffered save file 0xb15060 / 0xb14fe0; KSaveDevice in io/KFileSystem.h models only the slot KFileSystem calls): the remake's save data is platform/cell/savedata)
//   [ ] 0x4c4e8  Vt_b15060_DeletingDestructor_maybe  [platform]  (the PS3 save / file device stack (the default save device, vtable 0xb150d8, and its buffered save file 0xb15060 / 0xb14fe0; KSaveDevice in io/KFileSystem.h models only the slot KFileSystem calls): the remake's save data is platform/cell/savedata)
//   [ ] 0x4c530  Vt_b15060_Destructor_maybe  [platform]  (the PS3 save / file device stack (the default save device, vtable 0xb150d8, and its buffered save file 0xb15060 / 0xb14fe0; KSaveDevice in io/KFileSystem.h models only the slot KFileSystem calls): the remake's save data is platform/cell/savedata)
//   [ ] 0x4c560  Vt_b15060_Destructor_2_maybe  [dead]
//   [ ] 0x4c590  Vt_b15060_Construct_maybe  [platform]  (the PS3 save / file device stack (the default save device, vtable 0xb150d8, and its buffered save file 0xb15060 / 0xb14fe0; KSaveDevice in io/KFileSystem.h models only the slot KFileSystem calls): the remake's save data is platform/cell/savedata)
//   [ ] 0x4c5e8  Vt_b15060_Construct_2_maybe  [dead]
//   [x] 0x4c640  KFileSystem_ConstructBase_maybe
//   [ ] 0x4c650  KStub_Return1_4c650  [platform]  (the PS3 save / file device stack (the default save device, vtable 0xb150d8, and its buffered save file 0xb15060 / 0xb14fe0; KSaveDevice in io/KFileSystem.h models only the slot KFileSystem calls): the remake's save data is platform/cell/savedata)
//   [x] 0x4c658  KStub_Return1_4c658
//   [ ] 0x4c660  KStub_ReturnM1_4c660  [platform]  (the PS3 save / file device stack (the default save device, vtable 0xb150d8, and its buffered save file 0xb15060 / 0xb14fe0; KSaveDevice in io/KFileSystem.h models only the slot KFileSystem calls): the remake's save data is platform/cell/savedata)
//   [ ] 0x4c668  Vt_b150d8_InitRootFromGlobals_maybe  [platform]  (the PS3 save / file device stack (the default save device, vtable 0xb150d8, and its buffered save file 0xb15060 / 0xb14fe0; KSaveDevice in io/KFileSystem.h models only the slot KFileSystem calls): the remake's save data is platform/cell/savedata)
//   [ ] 0x4c6c0  KStub_Return0_4c6c0  [platform]  (the PS3 save / file device stack (the default save device, vtable 0xb150d8, and its buffered save file 0xb15060 / 0xb14fe0; KSaveDevice in io/KFileSystem.h models only the slot KFileSystem calls): the remake's save data is platform/cell/savedata)
//   [ ] 0x4c6c8  KStub_Return1_4c6c8  [platform]  (the PS3 save / file device stack (the default save device, vtable 0xb150d8, and its buffered save file 0xb15060 / 0xb14fe0; KSaveDevice in io/KFileSystem.h models only the slot KFileSystem calls): the remake's save data is platform/cell/savedata)
//   [ ] 0x4c6d0  KStub_Return1_4c6d0  [platform]  (the PS3 save / file device stack (the default save device, vtable 0xb150d8, and its buffered save file 0xb15060 / 0xb14fe0; KSaveDevice in io/KFileSystem.h models only the slot KFileSystem calls): the remake's save data is platform/cell/savedata)
//   [ ] 0x4c6d8  KStub_Return0_4c6d8  [platform]  (the PS3 save / file device stack (the default save device, vtable 0xb150d8, and its buffered save file 0xb15060 / 0xb14fe0; KSaveDevice in io/KFileSystem.h models only the slot KFileSystem calls): the remake's save data is platform/cell/savedata)
//   [ ] 0x4c6e0  KStub_Return0_4c6e0  [platform]  (the PS3 save / file device stack (the default save device, vtable 0xb150d8, and its buffered save file 0xb15060 / 0xb14fe0; KSaveDevice in io/KFileSystem.h models only the slot KFileSystem calls): the remake's save data is platform/cell/savedata)
//   [ ] 0x4c6e8  KStub_Return0_4c6e8  [platform]  (the PS3 save / file device stack (the default save device, vtable 0xb150d8, and its buffered save file 0xb15060 / 0xb14fe0; KSaveDevice in io/KFileSystem.h models only the slot KFileSystem calls): the remake's save data is platform/cell/savedata)
//   [ ] 0x4c6f0  KStub_Return1_4c6f0  [platform]  (the PS3 save / file device stack (the default save device, vtable 0xb150d8, and its buffered save file 0xb15060 / 0xb14fe0; KSaveDevice in io/KFileSystem.h models only the slot KFileSystem calls): the remake's save data is platform/cell/savedata)
//   [ ] 0x4c6f8  KStub_Return1_4c6f8  [platform]  (the PS3 save / file device stack (the default save device, vtable 0xb150d8, and its buffered save file 0xb15060 / 0xb14fe0; KSaveDevice in io/KFileSystem.h models only the slot KFileSystem calls): the remake's save data is platform/cell/savedata)
//   [ ] 0x4c700  Vt_b150d8_HasEnoughSpace_maybe  [platform]  (the PS3 save / file device stack (the default save device, vtable 0xb150d8, and its buffered save file 0xb15060 / 0xb14fe0; KSaveDevice in io/KFileSystem.h models only the slot KFileSystem calls): the remake's save data is platform/cell/savedata)
//   [ ] 0x4c760  KStub_Return0_4c760  [platform]  (the PS3 save / file device stack (the default save device, vtable 0xb150d8, and its buffered save file 0xb15060 / 0xb14fe0; KSaveDevice in io/KFileSystem.h models only the slot KFileSystem calls): the remake's save data is platform/cell/savedata)
//   [ ] 0x4c768  KStub_Return1_4c768  [platform]  (the PS3 save / file device stack (the default save device, vtable 0xb150d8, and its buffered save file 0xb15060 / 0xb14fe0; KSaveDevice in io/KFileSystem.h models only the slot KFileSystem calls): the remake's save data is platform/cell/savedata)
//   [ ] 0x4c770  KStub_Return1_4c770  [platform]  (the PS3 save / file device stack (the default save device, vtable 0xb150d8, and its buffered save file 0xb15060 / 0xb14fe0; KSaveDevice in io/KFileSystem.h models only the slot KFileSystem calls): the remake's save data is platform/cell/savedata)
//   [ ] 0x4c778  KStub_Return1_4c778  [platform]  (the PS3 save / file device stack (the default save device, vtable 0xb150d8, and its buffered save file 0xb15060 / 0xb14fe0; KSaveDevice in io/KFileSystem.h models only the slot KFileSystem calls): the remake's save data is platform/cell/savedata)
//   [ ] 0x4c780  KStub_Return0_4c780  [platform]  (the PS3 save / file device stack (the default save device, vtable 0xb150d8, and its buffered save file 0xb15060 / 0xb14fe0; KSaveDevice in io/KFileSystem.h models only the slot KFileSystem calls): the remake's save data is platform/cell/savedata)
//   [ ] 0x4c788  KStub_Return0_4c788  [platform]  (the PS3 save / file device stack (the default save device, vtable 0xb150d8, and its buffered save file 0xb15060 / 0xb14fe0; KSaveDevice in io/KFileSystem.h models only the slot KFileSystem calls): the remake's save data is platform/cell/savedata)
//   [ ] 0x4c790  KStub_Return0_4c790  [platform]  (the PS3 save / file device stack (the default save device, vtable 0xb150d8, and its buffered save file 0xb15060 / 0xb14fe0; KSaveDevice in io/KFileSystem.h models only the slot KFileSystem calls): the remake's save data is platform/cell/savedata)
//   [ ] 0x4c798  Vt_b150d8_OpenFile_maybe  [platform]  (the PS3 save / file device stack (the default save device, vtable 0xb150d8, and its buffered save file 0xb15060 / 0xb14fe0; KSaveDevice in io/KFileSystem.h models only the slot KFileSystem calls): the remake's save data is platform/cell/savedata)
//   [ ] 0x4c860  Vt_b150d8_SetRootPath_maybe  [platform]  (the PS3 save / file device stack (the default save device, vtable 0xb150d8, and its buffered save file 0xb15060 / 0xb14fe0; KSaveDevice in io/KFileSystem.h models only the slot KFileSystem calls): the remake's save data is platform/cell/savedata)
//   [ ] 0x4c890  Vt_b150d8_Destructor_2_maybe  [dead]
//   [ ] 0x4c8a0  Vt_b150d8_Construct_maybe  [dead]
//   [x] 0x4c8b0  Vt_b150d8_DeletingDestructor_maybe
//   [x] 0x4c8e0  Vt_b150d8_Destructor_maybe
//   [ ] 0x4c8f0  KFileSystem_SaveDevice_CallInitRootFromGlobals_maybe  [platform]  (the PS3 save / file device stack (the default save device, vtable 0xb150d8, and its buffered save file 0xb15060 / 0xb14fe0; KSaveDevice in io/KFileSystem.h models only the slot KFileSystem calls): the remake's save data is platform/cell/savedata)
//   [ ] 0x4c938  KFileSystem_SaveDevice_CallVf58_maybe  [platform]  (the PS3 save / file device stack (the default save device, vtable 0xb150d8, and its buffered save file 0xb15060 / 0xb14fe0; KSaveDevice in io/KFileSystem.h models only the slot KFileSystem calls): the remake's save data is platform/cell/savedata)
//   [x] 0x4c980  KFileSystem_SaveDevice_CallVf5C_maybe
//   [ ] 0x4c9c8  KFileDevice_CloseFile_maybe  [platform]  (the PS3 save / file device stack (the default save device, vtable 0xb150d8, and its buffered save file 0xb15060 / 0xb14fe0; KSaveDevice in io/KFileSystem.h models only the slot KFileSystem calls): the remake's save data is platform/cell/savedata)
//   [ ] 0x4ca10  FUN_0004ca10  [dead]
//   [ ] 0x4ca58  FUN_0004ca58  [dead]
//   [ ] 0x4caa0  FUN_0004caa0  [dead]
//   [ ] 0x4cae8  FUN_0004cae8  [dead]
//   [ ] 0x4cb30  KFileDevice_HasEnoughSpace_maybe  [dead]
//   [ ] 0x4cb78  FUN_0004cb78  [dead]
//   [ ] 0x4cbc0  FUN_0004cbc0  [dead]
//
//   [ ] 0x993188  Vt_b13d90_Destructor_maybe  [inline]
//   [ ] 0x993198  Vt_b13d90_DeletingDestructor_maybe  [inline]
//   [ ] 0x9931c8  Vt_b13d90_IsEqual_maybe  [inline]
//   [ ] 0x995a08  Vt_b15178_DeletingDestructor_maybe  [inline]
//   [ ] 0x995a38  Vt_b15178_Destructor_maybe  [inline]
//   [ ] 0x996208  Vt_b154c0_Destructor_maybe  [inline]
//   [ ] 0x996218  Vt_b154c0_DeletingDestructor_maybe  [inline]
//   [ ] 0x996248  KStub_Nop_996248  [inline]
//   [ ] 0x996250  keCThreadPool_vfC_Thunk  [inline]
//   [ ] 0x996258  keCThreadPool_vfC  [inline]
//   [ ] 0x996260  Vt_b15548_Destructor_maybe  [inline]
//   [ ] 0x996270  keCThreadPool_vf8_Thunk  [inline]
//   [ ] 0x996278  keCThreadPool_vf8  [inline]
//   [ ] 0x9962a8  Vt_b15548_DeletingDestructor_maybe  [inline]
//   [ ] 0x9962d8  keCThreadPool_DeletingDestructor_Thunk  [inline]
//   [ ] 0x9962e0  keCThreadPool_Destructor_Thunk  [inline]
//   [ ] 0x996f40  Vt_b15640_DeletingDestructor_maybe  [inline]
//   [ ] 0x9970e8  Vt_b15640_Destructor_maybe  [inline]
//   [ ] 0x998318  Vt_b15e00_DeletingDestructor_maybe  [inline]
//   [ ] 0x998348  Vt_b15e00_Destructor_maybe  [inline]
//   [ ] 0x9996a0  Vt_b16530_Destructor_maybe  [inline]
//   [ ] 0x9996b0  Vt_b16530_DeletingDestructor_maybe  [inline]
//   [ ] 0x99c460  Vt_b16b58_DeletingDestructor_maybe  [inline]
//   [ ] 0x99c490  Vt_b16b58_Destructor_maybe  [inline]
//   [ ] 0x99c4a0  IKKinematicsChain_IsKindOf  [inline]
//   [ ] 0x9a1178  Vt_b17b48_DeletingDestructor_maybe  [inline]
//   [ ] 0x9a11a8  Vt_b17b48_Destructor_maybe  [inline]
//   [ ] 0x9a6298  Vt_b19390_DeletingDestructor_maybe  [inline]
//   [ ] 0x9a62c8  Vt_b19390_Destructor_maybe  [inline]
//   [ ] 0x9a62d8  Vt_b193b0_DeletingDestructor_maybe  [inline]
//   [ ] 0x9a6308  Vt_b193b0_Destructor_maybe  [inline]
//   [ ] 0x9a6328  Vt_b193e8_DeletingDestructor_maybe  [inline]
//   [ ] 0x9a6358  Vt_b193e8_Destructor_maybe  [inline]
//   [ ] 0x9a6410  Vt_b195b0_DeletingDestructor_maybe  [inline]
//   [ ] 0x9a6440  Vt_b195b0_Destructor_maybe  [inline]
//   [ ] 0x9a6710  Vt_b19600_DeletingDestructor_maybe  [inline]
//   [ ] 0x9a6740  Vt_b19600_Destructor_maybe  [inline]
//   [ ] 0x9a6750  KStub_Nop_9a6750  [inline]
//   [ ] 0x9a6758  KStub_ReturnM1_9a6758  [inline]
//   [ ] 0x9a6768  KStub_ReturnM1_9a6768  [inline]
//   [ ] 0x9a6778  Vt_b19648_DeletingDestructor_maybe  [inline]
//   [ ] 0x9a67a8  Vt_b19648_Destructor_maybe  [inline]
//   [ ] 0x9a68f8  Vt_b197a8_DeletingDestructor_maybe  [inline]
//   [ ] 0x9a6928  Vt_b197a8_Destructor_maybe  [inline]
//   [ ] 0x9aba68  Vt_b1c9f0_DeletingDestructor_maybe  [inline]
//   [ ] 0x9aba98  Vt_b1c9f0_Destructor_maybe  [inline]
//   [ ] 0x9abaa8  Vt_b1ca20_DeletingDestructor_maybe  [inline]
//   [ ] 0x9abb50  Vt_b1ca08_Destructor_maybe  [inline]
//   [ ] 0x9abb60  Vt_b1ca20_Destructor_maybe  [inline]
//   [ ] 0x9abb70  Vt_b1ca08_DeletingDestructor_maybe  [inline]
//   [ ] 0x9b2118  Vt_b1fca8_DeletingDestructor_maybe  [inline]
//   [ ] 0x9b2148  Vt_b1fca8_Destructor_maybe  [inline]
//   [ ] 0x9b21a0  Vt_b1fdb0_DeletingDestructor_maybe  [inline]
//   [ ] 0x9b21d0  Vt_b1fdb0_Destructor_maybe  [inline]
//   [ ] 0x9b21e0  Vt_b1fd90_Destructor_maybe  [inline]
//   [ ] 0x9b2230  Vt_b1fda0_DeletingDestructor_maybe  [inline]
//   [ ] 0x9b2288  Vt_b1fda0_Destructor_maybe  [inline]
//   [ ] 0x9b22d0  Vt_b1fd70_DeletingDestructor_maybe  [inline]
//   [ ] 0x9b2328  Vt_b1fd70_Destructor_maybe  [inline]
//   [ ] 0x9b2370  Vt_b1fd80_DeletingDestructor_maybe  [inline]
//   [ ] 0x9b23d0  Vt_b1fd80_Destructor_maybe  [inline]
//   [ ] 0x9b2420  Vt_b1fd90_DeletingDestructor_maybe  [inline]
//   [ ] 0x9b3ac0  Vt_b1ff08_Destructor_maybe  [inline]
//   [ ] 0x9b3e78  Vt_b1ff08_DeletingDestructor_maybe  [inline]
//   [ ] 0x9bb1f8  Vt_b21458_Destructor_maybe  [inline]
//   [ ] 0x9bb208  Vt_b21458_DeletingDestructor_maybe  [inline]
//   [ ] 0x9bc7f8  Vt_b22068_DeletingDestructor_maybe  [inline]
//   [ ] 0x9bc840  Vt_b22068_Destructor_maybe  [inline]
//   [ ] 0x9cd768  Vt_b30290_DeletingDestructor_maybe  [inline]
//   [ ] 0x9cd808  Vt_b30290_Destructor_maybe  [inline]
//   [ ] 0x9cd838  Vt_b302c0_DeletingDestructor_maybe  [inline]
//   [ ] 0x9cd868  Vt_b302c0_Destructor_maybe  [inline]
//   [ ] 0x9cd878  Vt_b302b0_Destructor_maybe  [inline]
//   [ ] 0x9cd888  Vt_b302b0_DeletingDestructor_maybe  [inline]
//   [ ] 0x9cd8b8  Vt_b302f8_DeletingDestructor_maybe  [inline]
//   [ ] 0x9cd8e8  Vt_b302f8_Destructor_maybe  [inline]
//   [ ] 0x9cd8f8  KStub_Return1_9cd8f8  [inline]
//   [ ] 0x9cd900  KStub_Return1_9cd900  [inline]
//   [ ] 0x9cd908  KStub_Return1_9cd908  [inline]
//   [ ] 0x9cd910  std_ctype_char_do_tolower_maybe  [inline]
//   [ ] 0x9cd930  std_ctype_char_do_toupper_maybe  [inline]
//   [ ] 0x9cd950  std_ctype_char_do_widen_maybe  [inline]
//   [ ] 0x9cd958  std_ctype_char_do_narrow_maybe  [inline]
//   [ ] 0x9cdae8  Vt_b30488_DeletingDestructor_maybe  [inline]
//   [ ] 0x9cdb18  Vt_b30488_Destructor_maybe  [inline]
//   [ ] 0x9cdb28  Vt_b304a8_DeletingDestructor_maybe  [inline]
//   [ ] 0x9cdb58  Vt_b304a8_Destructor_maybe  [inline]
//   [ ] 0x9cdb68  Vt_b304d8_DeletingDestructor_maybe  [inline]
//   [ ] 0x9cdb98  Vt_b304d8_Destructor_maybe  [inline]
//   [ ] 0x9cdba8  Vt_b30500_DeletingDestructor_maybe  [inline]
//   [ ] 0x9cdbd8  Vt_b30500_Destructor_maybe  [inline]
//   [ ] 0x9cdbe8  Vt_b30520_DeletingDestructor_maybe  [inline]
//   [ ] 0x9cdc18  Vt_b30520_Destructor_maybe  [inline]
//   [ ] 0x9cdc28  Vt_b30548_DeletingDestructor_maybe  [inline]
//   [ ] 0x9cdc58  Vt_b30548_Destructor_maybe  [inline]
//   [ ] 0x9cdc68  Vt_b30778_DeletingDestructor_maybe  [inline]
//   [ ] 0x9cdc98  Vt_b30778_Destructor_maybe  [inline]
//   [ ] 0x9cdca8  Vt_b306e0_DeletingDestructor_maybe  [inline]
//   [ ] 0x9cdcd8  Vt_b306e0_Destructor_maybe  [inline]
//   [ ] 0x9cdce8  Vt_b30768_Destructor_maybe  [inline]
//   [ ] 0x9cdcf8  std_ctype_char_do_narrow_range_maybe  [inline]
//   [ ] 0x9cdd40  std_ctype_char_do_widen_range_maybe  [inline]
//   [ ] 0x9ce678  Vt_b30768_DeletingDestructor_maybe  [inline]
//   [ ] 0x9ce6a8  std_vector_PushBack_e4_Cg_maybe_4  [inline]
//   [ ] 0x9ce920  std_vector_Resize_e4_Cg_maybe  [inline]
