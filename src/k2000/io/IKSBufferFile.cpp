// IKSBufferFile.cpp - the PS3 block-buffered file under KFileStream. Platform-only: replaced by design.
//
// Reconstructed original translation unit: 0x4d7d8-0x4ed98 (GAME_TOC1, main_toc1), 18 functions, 17 live.
// Primary owner: IKSBufferFile (not a registered class)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [ ] 0x4d7d8  IKSBufferFile_Tell  [platform] by design: the PS3 1 MB block-buffered file (async cellFs reads); KFileStream.h is the platform equivalent
//   [ ] 0x4d7e8  IKSBufferFile_UpdateAsyncRead  [platform] by design: the PS3 1 MB block-buffered file (async cellFs reads); KFileStream.h is the platform equivalent
//   [ ] 0x4db48  IKSBufferFile_Read  [platform] by design: the PS3 1 MB block-buffered file (async cellFs reads); KFileStream.h is the platform equivalent
//   [ ] 0x4ddf0  IKSBufferFile_Destructor  [platform] by design: the PS3 1 MB block-buffered file (async cellFs reads); KFileStream.h is the platform equivalent
//   [ ] 0x4de00  IKSBufferFile_Construct_2  [dead]
//   [ ] 0x4ded8  IKSBufferFile_Construct  [platform] by design: the PS3 1 MB block-buffered file (async cellFs reads); KFileStream.h is the platform equivalent
//   [ ] 0x4dfb0  IKSBufferFile_ReadStreaming  [platform] by design: the PS3 1 MB block-buffered file (async cellFs reads); KFileStream.h is the platform equivalent
//   [ ] 0x4e378  IKSBufferFile_GetFileLength  [platform] by design: the PS3 1 MB block-buffered file (async cellFs reads); KFileStream.h is the platform equivalent
//   [ ] 0x4e388  IKSBufferFile_FlushAsync  [platform] by design: the PS3 1 MB block-buffered file (async cellFs reads); KFileStream.h is the platform equivalent
//   [ ] 0x4e4d8  IKSBufferFile_Eof  [platform] by design: the PS3 1 MB block-buffered file (async cellFs reads); KFileStream.h is the platform equivalent
//   [ ] 0x4e4f8  IKSBufferFile_Flush  [platform] by design: the PS3 1 MB block-buffered file (async cellFs reads); KFileStream.h is the platform equivalent
//   [ ] 0x4e5c8  IKSBufferFile_Seek  [platform] by design: the PS3 1 MB block-buffered file (async cellFs reads); KFileStream.h is the platform equivalent
//   [ ] 0x4e790  IKSBufferFile_BeginAsyncWrite  [platform] by design: the PS3 1 MB block-buffered file (async cellFs reads); KFileStream.h is the platform equivalent
//   [ ] 0x4e7b0  IKSBufferFile_Write  [platform] by design: the PS3 1 MB block-buffered file (async cellFs reads); KFileStream.h is the platform equivalent
//   [ ] 0x4e9e0  IKSBufferFile_BeginAsyncRead  [platform] by design: the PS3 1 MB block-buffered file (async cellFs reads); KFileStream.h is the platform equivalent
//   [ ] 0x4ea30  IKSBufferFile_UpdateAsyncWrite  [platform] by design: the PS3 1 MB block-buffered file (async cellFs reads); KFileStream.h is the platform equivalent
//   [ ] 0x4ed58  IKSBufferFile_Destructor_2  [platform] by design: the PS3 1 MB block-buffered file (async cellFs reads); KFileStream.h is the platform equivalent
//   [ ] 0x4ed68  IKSBufferFile_DeletingDestructor  [platform] by design: the PS3 1 MB block-buffered file (async cellFs reads); KFileStream.h is the platform equivalent
