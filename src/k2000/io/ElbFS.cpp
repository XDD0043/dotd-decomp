// Reconstructed original translation unit: 0x5ac10-0x5af70 (GAME_TOC1, main_toc1), 6 functions, 6 live.
// Primary owner: ElbFS (not a registered class)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [ ] 0x5ac10  ElbFS_GetFileRecord  [platform]  (replaced by design: RwStream reads its IKFile directly, see RwStream.h)
//   [ ] 0x5ac40  ElbFS_Create  [platform]  (replaced by design: RwStream reads its IKFile directly, see RwStream.h)
//   [ ] 0x5ae00  ElbFS_Destroy  [platform]  (replaced by design: RwStream reads its IKFile directly, see RwStream.h)
//   [ ] 0x5ae28  ElbFS_FileExists  [platform]  (replaced by design: RwStream reads its IKFile directly, see RwStream.h)
//   [ ] 0x5ae68  ElbFS_FileSeek  [platform]  (replaced by design: RwStream reads its IKFile directly, see RwStream.h)
//   [ ] 0x5af30  ElbFS_FileOpen  [platform]  (replaced by design: RwStream reads its IKFile directly, see RwStream.h)
//
// Platform: ElbFS is the RtFS "ELB:" device the PS3 build reads RenderWare streams through (the IKFile parked at
// KFileSystem +0x308). The remake's RwStream holds the IKFile itself (Renderware/rwcore/RwStream.h), so no device.
