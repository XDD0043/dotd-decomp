// KFileReadRequest.cpp - the PS3 asynchronous read requests of KHostFS.
//
// Reconstructed original translation unit: 0x4ed98-0x4f3c0 (GAME_TOC1, main_toc1), 15 functions, 15 live.
// Primary owner: KFileReadRequest (not a registered class)
// Other owners: CKFileSystemRequestQueue (2)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [ ] 0x4ed98  KFileReadRequest_IsPendingFor  [platform] by design: the PS3 asynchronous cellFs read request (KHostFS +0x100); the platform reads are synchronous (KFileStream.h)
//   [ ] 0x4edd0  KFileReadRequest_Execute  [platform] by design: the PS3 asynchronous cellFs read request (KHostFS +0x100); the platform reads are synchronous (KFileStream.h)
//   [ ] 0x4ee88  KFileReadRequest_Reset  [platform] by design: the PS3 asynchronous cellFs read request (KHostFS +0x100); the platform reads are synchronous (KFileStream.h)
//   [ ] 0x4eed8  KFileReadRequest_TakeResult  [platform] by design: the PS3 asynchronous cellFs read request (KHostFS +0x100); the platform reads are synchronous (KFileStream.h)
//   [ ] 0x4ef78  KFileReadRequest_Poll  [platform] by design: the PS3 asynchronous cellFs read request (KHostFS +0x100); the platform reads are synchronous (KFileStream.h)
//   [ ] 0x4f050  KFileReadRequest_Post  [platform] by design: the PS3 asynchronous cellFs read request (KHostFS +0x100); the platform reads are synchronous (KFileStream.h)
//   [ ] 0x4f0f8  KFileReadRequest_DeletingDestructor  [platform] by design: the PS3 asynchronous cellFs read request (KHostFS +0x100); the platform reads are synchronous (KFileStream.h)
//   [ ] 0x4f140  KFileReadRequest_Destructor  [platform] by design: the PS3 asynchronous cellFs read request (KHostFS +0x100); the platform reads are synchronous (KFileStream.h)
//   [ ] 0x4f170  KFileReadRequest_Destructor_2  [platform] by design: the PS3 asynchronous cellFs read request (KHostFS +0x100); the platform reads are synchronous (KFileStream.h)
//   [ ] 0x4f1a0  KFileReadRequest_Construct  [platform] by design: the PS3 asynchronous cellFs read request (KHostFS +0x100); the platform reads are synchronous (KFileStream.h)
//   [ ] 0x4f220  KFileReadRequest_Construct_2  [platform] by design: the PS3 asynchronous cellFs read request (KHostFS +0x100); the platform reads are synchronous (KFileStream.h)
//   [ ] 0x4f2a0  KFileReadRequest_Cancel_maybe  [platform] by design: the PS3 asynchronous cellFs read request (KHostFS +0x100); the platform reads are synchronous (KFileStream.h)
//   [x] 0x4f320  CKFileSystemRequestQueue_JoinThreads  (CKFileSystemRequestQueue.cpp)
//   [x] 0x4f360  CKFileSystemRequestQueue_Abort  (CKFileSystemRequestQueue.cpp)
//   [ ] 0x4f398  keCThreadPoolBase_CancelRequest_Thunk_maybe  [platform] by design: the PS3 asynchronous cellFs read request (KHostFS +0x100); the platform reads are synchronous (KFileStream.h)
