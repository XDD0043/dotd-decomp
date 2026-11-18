// KHostFS.cpp - the host file system service (RtFS on cellFs).
//
// Reconstructed original translation unit: 0x4f628-0x51bf0 (GAME_TOC1, main_toc1), 39 functions, 38 live.
// Primary owner: KHostFS (not a registered class)
// Other owners: Vt (2), KFileLoader (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [ ] 0x4f628  KHostFS_GetRootPath  [platform] by design: RtFS / cellFs host file system; the stand-in is KHostFS.h (stubs/BootStubs.cpp, KFileStreamHost.cpp)
//   [ ] 0x4f678  KHostFS_PreopenFilesRecursive  [platform] by design: RtFS / cellFs host file system; the stand-in is KHostFS.h (stubs/BootStubs.cpp, KFileStreamHost.cpp)
//   [ ] 0x4fb88  KHostFS_RegisterRtFS  [platform] by design: RtFS / cellFs host file system; the stand-in is KHostFS.h (stubs/BootStubs.cpp, KFileStreamHost.cpp)
//   [ ] 0x4fc48  KHostFS_PollReadRequest_maybe  [platform] by design: RtFS / cellFs host file system; the stand-in is KHostFS.h (stubs/BootStubs.cpp, KFileStreamHost.cpp)
//   [ ] 0x4fcb0  KHostFS_vf24  [platform] by design: RtFS / cellFs host file system; the stand-in is KHostFS.h (stubs/BootStubs.cpp, KFileStreamHost.cpp)
//   [x] 0x4fd18  KFileLoader_IsReadComplete_maybe
//   [ ] 0x4fd80  KHostFS_PollDevice_maybe  [platform] by design: RtFS / cellFs host file system; the stand-in is KHostFS.h (stubs/BootStubs.cpp, KFileStreamHost.cpp)
//   [ ] 0x4fdd8  KHostFS_Init  [platform] by design: RtFS / cellFs host file system; the stand-in is KHostFS.h (stubs/BootStubs.cpp, KFileStreamHost.cpp)
//   [ ] 0x4fe00  KHostFS_Construct_2  [platform] by design: RtFS / cellFs host file system; the stand-in is KHostFS.h (stubs/BootStubs.cpp, KFileStreamHost.cpp)
//   [ ] 0x4fec8  KHostFS_FileWait  [platform] by design: RtFS / cellFs host file system; the stand-in is KHostFS.h (stubs/BootStubs.cpp, KFileStreamHost.cpp)
//   [ ] 0x4ff20  KHostFS_FileRead  [platform] by design: RtFS / cellFs host file system; the stand-in is KHostFS.h (stubs/BootStubs.cpp, KFileStreamHost.cpp)
//   [ ] 0x500b8  KHostFS_FileSeek  [platform] by design: RtFS / cellFs host file system; the stand-in is KHostFS.h (stubs/BootStubs.cpp, KFileStreamHost.cpp)
//   [ ] 0x50248  KHostFS_Construct  [platform] by design: RtFS / cellFs host file system; the stand-in is KHostFS.h (stubs/BootStubs.cpp, KFileStreamHost.cpp)
//   [ ] 0x50310  KHostFS_IsCachedFd  [platform] by design: RtFS / cellFs host file system; the stand-in is KHostFS.h (stubs/BootStubs.cpp, KFileStreamHost.cpp)
//   [ ] 0x504d8  KHostFS_BuildPath  [platform] by design: RtFS / cellFs host file system; the stand-in is KHostFS.h (stubs/BootStubs.cpp, KFileStreamHost.cpp)
//   [ ] 0x50730  KHostFS_FileOpen  [platform] by design: RtFS / cellFs host file system; the stand-in is KHostFS.h (stubs/BootStubs.cpp, KFileStreamHost.cpp)
//   [ ] 0x50ac8  KHostFS_FileSync  [platform] by design: RtFS / cellFs host file system; the stand-in is KHostFS.h (stubs/BootStubs.cpp, KFileStreamHost.cpp)
//   [ ] 0x50e20  KHostFS_FileClose  [platform] by design: RtFS / cellFs host file system; the stand-in is KHostFS.h (stubs/BootStubs.cpp, KFileStreamHost.cpp)
//   [ ] 0x51020  KHostFS_CloseCachedFiles  [platform] by design: RtFS / cellFs host file system; the stand-in is KHostFS.h (stubs/BootStubs.cpp, KFileStreamHost.cpp)
//   [ ] 0x51278  KHostFS_PreopenRwsFiles  [platform] by design: RtFS / cellFs host file system; the stand-in is KHostFS.h (stubs/BootStubs.cpp, KFileStreamHost.cpp)
//   [ ] 0x513e8  KHostFS_DeletingDestructor  [platform] by design: RtFS / cellFs host file system; the stand-in is KHostFS.h (stubs/BootStubs.cpp, KFileStreamHost.cpp)
//   [ ] 0x515c0  KHostFS_Destructor  [platform] by design: RtFS / cellFs host file system; the stand-in is KHostFS.h (stubs/BootStubs.cpp, KFileStreamHost.cpp)
//   [ ] 0x51788  KHostFS_Destructor_2  [platform] by design: RtFS / cellFs host file system; the stand-in is KHostFS.h (stubs/BootStubs.cpp, KFileStreamHost.cpp)
//   [ ] 0x51950  KHostFS_ConstructBase_maybe  [platform] by design: RtFS / cellFs host file system; the stand-in is KHostFS.h (stubs/BootStubs.cpp, KFileStreamHost.cpp)
//   [ ] 0x51970  KHostFS_ConstructBase_2_maybe  [dead]
//   [x] 0x51990  KHostFS_GetInstance  (k2000/stubs/BootStubs.cpp)
//   [ ] 0x519a0  KStub_Nop_519a0  [platform] by design: RtFS / cellFs host file system; the stand-in is KHostFS.h (stubs/BootStubs.cpp, KFileStreamHost.cpp)
//   [ ] 0x519a8  KStub_Return1_519a8  [platform] by design: RtFS / cellFs host file system; the stand-in is KHostFS.h (stubs/BootStubs.cpp, KFileStreamHost.cpp)
//   [ ] 0x519b0  KStub_Return1_519b0  [platform] by design: RtFS / cellFs host file system; the stand-in is KHostFS.h (stubs/BootStubs.cpp, KFileStreamHost.cpp)
//   [ ] 0x519b8  KStub_Return1_519b8  [platform] by design: RtFS / cellFs host file system; the stand-in is KHostFS.h (stubs/BootStubs.cpp, KFileStreamHost.cpp)
//   [ ] 0x519c0  KStub_Return2_519c0  [platform] by design: RtFS / cellFs host file system; the stand-in is KHostFS.h (stubs/BootStubs.cpp, KFileStreamHost.cpp)
//   [x] 0x519c8  KHostFS_GetDeviceState_maybe  (KHostFS.h: the stand-in has no RtFS)
//   [ ] 0x51a08  KHostFS_CloseRtFSManager_maybe  [platform] by design: RtFS / cellFs host file system; the stand-in is KHostFS.h (stubs/BootStubs.cpp, KFileStreamHost.cpp)
//   [ ] 0x51a48  KHostFS_PumpAsyncRequests_maybe  [platform] by design: RtFS / cellFs host file system; the stand-in is KHostFS.h (stubs/BootStubs.cpp, KFileStreamHost.cpp)
//   [ ] 0x51a70  KHostFS_InitFileSystems  [platform] by design: RtFS / cellFs host file system; the stand-in is KHostFS.h (stubs/BootStubs.cpp, KFileStreamHost.cpp)
//   [ ] 0x51b50  KHostFS_Create  [platform] by design: RtFS / cellFs host file system; the stand-in is KHostFS.h (stubs/BootStubs.cpp, KFileStreamHost.cpp)
//   [ ] 0x51ba0  Vt_b15398_DeletingDestructor_maybe  [platform] by design: RtFS / cellFs host file system; the stand-in is KHostFS.h (stubs/BootStubs.cpp, KFileStreamHost.cpp)
//   [ ] 0x51bd0  Vt_b15398_Destructor_maybe  [platform] by design: RtFS / cellFs host file system; the stand-in is KHostFS.h (stubs/BootStubs.cpp, KFileStreamHost.cpp)
//   [ ] 0x51be0  KHostFS_BaseDestructor  [platform] by design: RtFS / cellFs host file system; the stand-in is KHostFS.h (stubs/BootStubs.cpp, KFileStreamHost.cpp)
//
//   [ ] 0x995a88  KHostFS_GetName  [inline]
//   [ ] 0x995a90  KHostFS_GetShortName  [inline]
//   [ ] 0x995a98  KHostFS_vf30  [inline]
//   [ ] 0x995c60  HashTableStr_DeletingDestructor  [inline]
//   [ ] 0x995df8  HashTableU32_DeletingDestructor_3  [inline]
//   [ ] 0x995f18  HashTableU32_Destructor_3  [inline]
//   [ ] 0x996038  HashTableStr_Destructor  [inline]
