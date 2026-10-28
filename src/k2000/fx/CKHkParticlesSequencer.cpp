// CKHkParticlesSequencer.cpp - reconstructed original translation unit 0x5a8910-0x5a9588 (GAME_TOC2, main_toc2), 34 functions, 31 live.
// Primary owner: CKHkParticlesSequencer (not a registered class)
// Other owners: RegisterCKHkParticlesSequencerClass (1), CKSrvBonus (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x5a8910  CKHkParticlesSequencer_Destroy
//   [x] 0x5a8960  CKHkParticlesSequencer_Construct  [dead]
//   [ ] 0x5a89a8  CKHkParticlesSequencer_Construct_2  [dead]
//   [ ] 0x5a89f0  CKHkParticlesSequencer_ClearReferences
//   [ ] 0x5a89f8  CKHkParticlesSequencer_vf50
//   [ ] 0x5a8a00  CKHkParticlesSequencer_vf70
//   [ ] 0x5a8a08  CKHkParticlesSequencer_vf78
//   [ ] 0x5a8a10  CKHkParticlesSequencer_OnSectorActivate
//   [ ] 0x5a8a38  CKHkParticlesSequencer_OnSectorDeactivate
//   [ ] 0x5a8aa0  RegisterCKHkParticlesSequencerClass
//   [ ] 0x5a8b18  _GLOBAL__I_5a8b18
//   [ ] 0x5a8b28  CKHkParticlesSequencer_ReinitRuntime
//   [ ] 0x5a8bb0  CKHkParticlesSequencer_PostLoad
//   [x] 0x5a8c18  CKHkParticlesSequencer_Load
//   [ ] 0x5a8d30  CKHkParticlesSequencer_Save
//   [ ] 0x5a8d58  CKHkParticlesSequencer_LevelReset
//   [x] 0x5a8d80  CKHkParticlesSequencer_DestroyArray
//   [ ] 0x5a8e28  CKHkParticlesSequencer_Update
//   [ ] 0x5a8ed8  CKHkParticlesSequencer_OnLevelExit_maybe
//   [ ] 0x5a8f40  CKHkParticlesSequencer_HandleMessage
//   [ ] 0x5a9110  CKHkParticlesSequencer_vf38
//   [ ] 0x5a9120  CKHkParticlesSequencer_vf3C
//   [ ] 0x5a9148  CKHkParticlesSequencer_OnActivate
//   [ ] 0x5a91c0  CKHkParticlesSequencer_OnDeactivate
//   [x] 0x5a9200  CKHkParticlesSequencer_Create
//   [x] 0x5a9268  CKHkParticlesSequencer_CreateArray
//   [ ] 0x5a9338  CKHkParticlesSequencer_Destructor
//   [ ] 0x5a9358  CKHkParticlesSequencer_Destructor_2  [dead]
//   [ ] 0x5a9378  CKHkParticlesSequencer_DeletingDestructor
//   [ ] 0x5a93c0  CKHkParticlesSequencer_IsStopped_maybe
//   [ ] 0x5a93e0  CKHkParticlesSequencer_IsAtStep_maybe
//   [ ] 0x5a9410  CKHkParticlesSequencer_ResolveTriggerProperty
//   [ ] 0x5a94f8  CKHkParticlesSequencer_HasStoppedAtStep_maybe
//   [ ] 0x5a9538  CKSrvBonus_Destroy
//
//   [ ] 0x9cbd80  CKHkParticlesSequencer_IsKindOf  [inline]
//   [ ] 0x9cbdc8  CKHkParticlesSequencer_GetClassGroup  [inline]
//   [ ] 0x9cbdd0  CKHkParticlesSequencer_GetClassId  [inline]
#include "k2000/fx/CKHkParticlesSequencer.h"

#include "k2000/io/IKFile.h"

// 0x005a8c18 CKHkParticlesSequencer_Load
int32_t CKHkParticlesSequencer::Load(IKFile* file, int32_t type) {
    IKHook::Load(file, type);  // through TocBridge_CKHook_Load
    if (type != K_LEVEL_PLATEFORMS) return 1;
    IKFile_ReadRef(file, &m_pSequencerPartCpnt);
    m_tsSequenceEnded.Load(file, 0);
    ReadS32LE(file, &m_i32DefaultStartSequence);
    return 1;
}
