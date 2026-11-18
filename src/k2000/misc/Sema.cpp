// Reconstructed original translation unit: 0x58ea8-0x591b0 (GAME_TOC1, main_toc1), 7 functions, 7 live.
// Primary owner: Sema (not a registered class)
// Other owners: KThread (1), PpuThread (1), SpinWaitForNonZero (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [ ] 0x58ea8  Sema_Create_2  [platform]  (a PS3 semaphore (sys_semaphore_create): host primitives by design)
//   [ ] 0x58f38  KThread_AttachCurrent_maybe  [platform]  (the KThread record of the current PPU thread: platform/cell/sys_thread)
//   [ ] 0x58fc0  PpuThread_SetPriorityLevel_maybe  [platform]  (sys_ppu_thread_set_priority from a KThread level: platform/cell/sys_thread)
//   [ ] 0x59058  KStub_Nop_59058  [platform]  (a stub of the PS3 thread layer (the particle scheduler's): host threads by design)
//   [ ] 0x59060  Sema_Create  [platform]  (a PS3 semaphore (sys_semaphore_create; the CondVar layer's): host primitives by design)
//   [ ] 0x590f0  SpinWaitForNonZero_maybe  [platform]  (a spin wait on sys_ppu_thread_yield (the CondVar layer's timed wait): host primitives by design)
//   [ ] 0x59190  Sema_Destroy_maybe  [platform]  (a PS3 semaphore (sys_semaphore_destroy): host primitives by design)
