// Reconstructed original translation unit: 0x543d8-0x54ef0 (GAME_TOC1, main_toc1), 14 functions, 9 live.
// Primary owner: CondVar (not a registered class)
// Other owners: KThreadState (1), KThreadSet (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [ ] 0x543d8  CondVar_WaitBegin  [platform]  (the engine's semaphore-based condition variable: the remake uses host condition variables (KRequest.cpp, JobQueue.cpp))
//   [ ] 0x54428  CondVar_WaitEndTimeout_maybe  [platform]  (the engine's semaphore-based condition variable (timed wait): host condition variables by design)
//   [ ] 0x54688  CondVar_WaitEnd  [platform]  (the engine's semaphore-based condition variable: host condition variables by design)
//   [ ] 0x54860  CondVar_Broadcast  [platform]  (the engine's semaphore-based condition variable: host condition variables by design)
//   [ ] 0x549d0  CondVar_Signal  [platform]  (the engine's semaphore-based condition variable: host condition variables by design)
//   [ ] 0x54b20  CondVar_Destroy  [platform]  (the engine's semaphore-based condition variable: host condition variables by design)
//   [ ] 0x54b78  CondVar_Destroy_2  [platform]  (the engine's semaphore-based condition variable: host condition variables by design)
//   [ ] 0x54bd0  CondVar_Init  [platform]  (the engine's semaphore-based condition variable: host condition variables by design)
//   [ ] 0x54c50  CondVar_Init_2  [dead]
//   [ ] 0x54cd0  KStub_Return2_54cd0  [platform]  (a stub of the engine's thread layer (returns 2; ParticleUpdateScheduler's SPU threads): host threads by design)
//   [ ] 0x54cd8  KThreadState_InitForSpawn_2_maybe  [dead]
//   [ ] 0x54d60  KThreadSet_SetPriorityLevel_maybe  [dead]
//   [ ] 0x54df0  FUN_00054df0  [dead]
//   [ ] 0x54e70  FUN_00054e70  [dead]
