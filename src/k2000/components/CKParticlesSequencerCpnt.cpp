// CKParticlesSequencerCpnt.cpp - reconstructed original translation unit 0x1dab88-0x1dcb28 (GAME_TOC1, main_toc1), 32 functions, 24 live.
// Primary class: CKParticlesSequencerCpnt  key 0xc86  category Component  size 0x28  vtable 0xb1df58
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x1dab88  CKParticlesSequencerCpnt_Delete
//   [ ] 0x1dabd8  CKParticlesSequencerCpnt_Construct  [dead]
//   [ ] 0x1dabe8  CKParticlesSequencerCpnt_Construct_2  [dead]
//   [ ] 0x1dabf8  CKParticlesSequencerCpnt_RecursiveRegistration
//   [ ] 0x1dac00  CKParticlesSequencerCpnt_PostLoad
//   [ ] 0x1dac08  FUN_001dac08  [dead]
//   [ ] 0x1dac20  CKParticlesSequencerCpnt_vf50
//   [ ] 0x1dac28  FUN_001dac28  [dead]
//   [ ] 0x1dac40  KStub_Return1_1dac40  [dead]
//   [ ] 0x1dac48  FUN_001dac48  [dead]
//   [ ] 0x1dad18  RegisterCKParticlesSequencerCpntClass
//   [ ] 0x1dad90  _GLOBAL__I_1dad90
//   [ ] 0x1dada0  FUN_001dada0  [dead]
//   [x] 0x1dae70  CKParticlesSequencerCpnt_DeleteArray
//   [ ] 0x1daf18  CKParticlesSequencerCpnt_BaseDestructor
//   [ ] 0x1daf48  CKParticlesSequencerCpnt_DeletingDestructor
//   [ ] 0x1daf90  CKParticlesSequencerCpnt_Destructor
//   [ ] 0x1dafc0  CKParticlesSequencerCpnt_AttachSequenceFxTo_maybe
//   [x] 0x1db130  CKParticlesSequencerCpnt_CreateArray
//   [x] 0x1db1c8  CKParticlesSequencerCpnt_Create
//   [ ] 0x1db200  CKParticlesSequencerCpnt_Save
//   [ ] 0x1db208  CKParticlesSequencerCpnt_Destroy
//   [ ] 0x1db390  FUN_001db390  [dead]
//   [x] 0x1db508  CKParticlesSequencerCpnt_LoadSequence_maybe
//   [x] 0x1db948  CKParticlesSequencerCpnt_Load
//   [ ] 0x1dbb90  CKParticlesSequencerCpnt_ReleaseSequenceFx_maybe
//   [ ] 0x1dbd60  CKParticlesSequencerCpnt_StartSequence_maybe
//   [ ] 0x1dbf50  CKParticlesSequencerCpnt_StopAll_maybe
//   [ ] 0x1dc0d8  CKParticlesSequencerCpnt_StopSequence_maybe
//   [ ] 0x1dc338  CKParticlesSequencerCpnt_vf54
//   [ ] 0x1dc4c0  CKParticlesSequencerCpnt_PlaySequence_maybe
//   [ ] 0x1dc7d0  CKParticlesSequencerCpnt_Update
//
//   [ ] 0x9adb68  CKParticlesSequencerCpnt_IsKindOfClass  [inline]
//   [x] 0x9adb90  CKParticlesSequencerCpnt_GetClassType  [inline]
//   [x] 0x9adb98  CKParticlesSequencerCpnt_GetClassID  [inline]
#include "k2000/components/CKParticlesSequencerCpnt.h"

#include "Renderware/rwcore/RwMatrix.h"
#include "k2000/io/IKFile.h"

// 0x001db508 CKParticlesSequencerCpnt_LoadSequence_maybe
int32_t CKParticlesSequencerCpnt::CSequence::Load(IKFile* file, int32_t type) {
    if (type != K_LEVEL_PLATEFORMS) return 1;
    ReadU8(file, &m_bLoop);
    ReadF32LE(file, &m_fSeqDuration);
    ReadU16LE(file, &m_ui16KeyTimeNb);
    ReadU16LE(file, &m_ui16PartStateNb);
    m_afKeyTime = new float[m_ui16KeyTimeNb];  // OperatorNewArray(n * 4)
    m_aUnk0c = new uint32_t[m_ui16KeyTimeNb];
    m_aUnk10 = new uint32_t[m_ui16KeyTimeNb];
    m_aParticleState = new CParticleState[m_ui16PartStateNb];  // OperatorNewArray(n * 0xc)
    for (uint32_t i = 0; i < m_ui16KeyTimeNb; ++i) {
        ReadF32LE(file, &m_afKeyTime[i]);
        ReadU32LE(file, &m_aUnk0c[i]);
        ReadU32LE(file, &m_aUnk10[i]);
    }
    for (uint32_t i = 0; i < m_ui16PartStateNb; ++i) {
        CParticleState& state = m_aParticleState[i];
        IKFile_ReadRef(file, &state.m_pParticle);
        state.m_aePartState = new uint32_t[m_ui16KeyTimeNb];
        for (uint32_t k = 0; k < m_ui16KeyTimeNb; ++k) ReadU32LE(file, &state.m_aePartState[k]);
        state.m_pMatrixPart = reinterpret_cast<CMatrix34*>(RwMatrixCreate());  // RwMatrixCreate_Thunk
        CMatrix34_LoadMatrix(state.m_pMatrixPart, file);
    }
    m_pCentralMatrix = reinterpret_cast<CMatrix34*>(RwMatrixCreate());
    CMatrix34_LoadMatrix(m_pCentralMatrix, file);
    return 1;
}

// 0x001db948 CKParticlesSequencerCpnt_Load
int32_t CKParticlesSequencerCpnt::Load(IKFile* file, int32_t type) {
    if (type == K_LEVEL_PLATEFORMS) {
        ReadU16LE(file, &m_ui16PartNb);
        ReadU16LE(file, &m_ui16SeqNb);
        m_apSequencerParticles = new IKSerializable*[m_ui16PartNb];  // OperatorNewArray(n * 4)
        m_aSequences = new CSequence[m_ui16SeqNb];                   // OperatorNewArray(n * 0x20)
        for (uint32_t i = 0; i < m_ui16PartNb; ++i) IKFile_ReadRef(file, &m_apSequencerParticles[i]);
        for (uint32_t i = 0; i < m_ui16SeqNb; ++i) m_aSequences[i].Load(file, K_LEVEL_PLATEFORMS);
    }
    m_baInfos = 0;
    m_i32CurSeq = -1;
    return 1;
}
