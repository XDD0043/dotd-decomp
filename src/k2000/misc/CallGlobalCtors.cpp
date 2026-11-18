// Reconstructed original translation unit: 0x10200-0x10558 (GAME_TOC1, main_toc1), 10 functions, 8 live.
// Primary owner: CallGlobalCtors (not a registered class)
// Other owners: Exitspawn (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [ ] 0x10200  _init_maybe  [platform]  (the C runtime's _init (the static constructors): the host C++ runtime runs them)
//   [ ] 0x1022c  CallGlobalCtors_maybe  [platform]  (the C runtime's static constructor walk: the host C++ runtime)
//   [ ] 0x10240  _start  [platform]  (the PS3 process entry (_start: TOC, argv, mainw): the host entry point is dotd's main)
//   [ ] 0x10268  FUN_00010268  [dead]
//   [ ] 0x10278  FUN_00010278  [dead]
//   [ ] 0x10288  Exitspawn_maybe  [platform]  (the PS3 exit path (sys_process_exit): the host C runtime)
//   [ ] 0x102b0  _ExitCleanup_maybe  [platform]  (the C runtime's exit cleanup (atexit handlers, static destructors): the host C runtime)
//   [ ] 0x10300  exit_maybe  [platform]  (the C runtime's exit: the host C runtime)
//   [ ] 0x10338  _Exit_maybe  [platform]  (the C runtime's _Exit: the host C runtime)
//   [ ] 0x10370  mainw  [platform]  (the PS3 main wrapper (argument block to main): dotd's main)
