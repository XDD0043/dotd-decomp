// KFileDevice.cpp - the PS3 save device file opens. Platform-only: replaced by design.
//
// Reconstructed original translation unit: 0x4cc08-0x4cfe0 (GAME_TOC1, main_toc1), 3 functions, 2 live.
// Primary owner: KFileDevice (not a registered class)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [ ] 0x4cc08  KFileDevice_ReadFileUuid_maybe  [dead]
//   [ ] 0x4cd48  KFileDevice_OpenAndZeroFillAsync_maybe  [platform] by design: the PS3 save device (KSaveDevice slots are stubs); save data goes through platform/cell savedata
//   [ ] 0x4cee8  KFileDevice_OpenAndZeroFill_maybe  [platform] by design: the PS3 save device (KSaveDevice slots are stubs); save data goes through platform/cell savedata
