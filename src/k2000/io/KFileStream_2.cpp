// KFileStream_2.cpp - the PS3 KFileStream (block I/O, open, its IKFile slots).
//
// Reconstructed original translation unit: 0x4b7b8-0x4c1f0 (GAME_TOC1, main_toc1), 15 functions, 14 live.
// Primary owner: KFileStream (not a registered class)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [ ] 0x4b7b8  KFileStream_Destructor_2  [platform] by design: the PS3 KFileStream over RtFS / cellFs; KFileStream.h / KFileStreamHost.cpp are the platform equivalent
//   [ ] 0x4b828  KFileStream_Construct_2  [platform] by design: the PS3 KFileStream over RtFS / cellFs; KFileStream.h / KFileStreamHost.cpp are the platform equivalent
//   [ ] 0x4b8c8  KFileStream_BeginBlockIO  [platform] by design: the PS3 KFileStream over RtFS / cellFs; KFileStream.h / KFileStreamHost.cpp are the platform equivalent
//   [ ] 0x4b930  KFileStream_DeletingDestructor  [platform] by design: the PS3 KFileStream over RtFS / cellFs; KFileStream.h / KFileStreamHost.cpp are the platform equivalent
//   [ ] 0x4b9a8  KFileStream_Destructor  [platform] by design: the PS3 KFileStream over RtFS / cellFs; KFileStream.h / KFileStreamHost.cpp are the platform equivalent
//   [ ] 0x4ba18  KFileStream_Construct  [platform] by design: the PS3 KFileStream over RtFS / cellFs; KFileStream.h / KFileStreamHost.cpp are the platform equivalent
//   [ ] 0x4bab8  KFileStream_UpdateBlockIO  [platform] by design: the PS3 KFileStream over RtFS / cellFs; KFileStream.h / KFileStreamHost.cpp are the platform equivalent
//   [ ] 0x4bc78  KFileStream_ReadWriteBlock  [platform] by design: the PS3 KFileStream over RtFS / cellFs; KFileStream.h / KFileStreamHost.cpp are the platform equivalent
//   [ ] 0x4bea0  KFileStream_Open  [platform] by design: the PS3 KFileStream over RtFS / cellFs; KFileStream.h / KFileStreamHost.cpp are the platform equivalent
//   [ ] 0x4c1c0  KStub_Nop_4c1c0  [dead]
//   [ ] 0x4c1c8  KStub_Return0_4c1c8  [platform] by design: the PS3 KFileStream over RtFS / cellFs; KFileStream.h / KFileStreamHost.cpp are the platform equivalent
//   [ ] 0x4c1d0  KStub_Return1_4c1d0  [platform] by design: the PS3 KFileStream over RtFS / cellFs; KFileStream.h / KFileStreamHost.cpp are the platform equivalent
//   [ ] 0x4c1d8  KStub_ReturnM1_4c1d8  [platform] by design: the PS3 KFileStream over RtFS / cellFs; KFileStream.h / KFileStreamHost.cpp are the platform equivalent
//   [ ] 0x4c1e0  KStub_ReturnArg4_4c1e0  [platform] by design: the PS3 KFileStream over RtFS / cellFs; KFileStream.h / KFileStreamHost.cpp are the platform equivalent
//   [ ] 0x4c1e8  KStub_ReturnM1_4c1e8  [platform] by design: the PS3 KFileStream over RtFS / cellFs; KFileStream.h / KFileStreamHost.cpp are the platform equivalent
