// CKFlaggedPathCinematicBloc.cpp - reconstructed original translation unit 0x177cf0-0x17a760 (GAME_TOC1, main_toc1), 24 functions, 23 live.
// Primary class: CKFlaggedPathCinematicBloc  key 0x148  category CinematicNode  size 0x100  vtable 0xb1b268
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x177cf0  CKFlaggedPathCinematicBloc_Delete
//   [ ] 0x177d40  RegisterCKFlaggedPathCinematicBlocClass
//   [ ] 0x177db8  _GLOBAL__I_177db8
//   [ ] 0x177dc8  CKFlaggedPathCinematicBloc_SnapTargetToGround_maybe
//   [ ] 0x177e60  CKFlaggedPathCinematicBloc_StepActorTowards_maybe
//   [ ] 0x178050  CKFlaggedPathCinematicBloc_Stop
//   [ ] 0x178230  CKFlaggedPathCinematicBloc_RecursiveRegistration
//   [ ] 0x178308  CKFlaggedPathCinematicBloc_InitGroundProbe_maybe  [dead]
//   [x] 0x178430  CKFlaggedPathCinematicBloc_DeleteArray
//   [x] 0x1784d0  CKFlaggedPathCinematicBloc_Create
//   [ ] 0x178580  CKFlaggedPathCinematicBloc_PathState2_maybe
//   [ ] 0x178660  CKFlaggedPathCinematicBloc_PathState1_maybe
//   [ ] 0x178740  CKFlaggedPathCinematicBloc_PathState0_maybe
//   [ ] 0x178828  CKFlaggedPathCinematicBloc_Destroy
//   [x] 0x178880  CKFlaggedPathCinematicBloc_CreateArray
//   [ ] 0x1789d0  CKFlaggedPathCinematicBloc_UpdateActorGroundContact_maybe
//   [ ] 0x178c80  CKFlaggedPathCinematicBloc_MoveActorAlongPath
//   [ ] 0x178ff0  CKFlaggedPathCinematicBloc_Update
//   [x] 0x179320  CKFlaggedPathCinematicBloc_Load
//   [ ] 0x179778  CKFlaggedPathCinematicBloc_Save
//   [ ] 0x179bf0  CKFlaggedPathCinematicBloc_Complete
//   [ ] 0x179dc8  CKFlaggedPathCinematicBloc_RunStateMachine_maybe
//   [ ] 0x179ff0  CKFlaggedPathCinematicBloc_MessageProc
//   [ ] 0x17a260  CKFlaggedPathCinematicBloc_Start
//
//   [ ] 0x9a95e0  CKFlaggedPathCinematicBloc_IsKindOfClass  [inline]
//   [ ] 0x9a9618  CKFlaggedPathCinematicBloc_GetClassType  [inline]
//   [ ] 0x9a9620  CKFlaggedPathCinematicBloc_GetClassID  [inline]
//   [ ] 0x9a9628  CKFlaggedPathCinematicBloc_Abort  [inline]
//   [ ] 0x9a9638  CKFlaggedPathCinematicBloc_UsesActor_maybe  [inline]
//   [ ] 0x9a9640  CKFlaggedPathCinematicBloc_IsExclusiveOnActor_maybe  [inline]
//   [ ] 0x9a9648  CKFlaggedPathCinematicBloc_GetAnimCount_maybe  [inline]
//   [ ] 0x9a9650  CKFlaggedPathCinematicBloc_GetAnimIndex_maybe  [inline]
//   [ ] 0x9a9670  CKFlaggedPathCinematicBloc_Destructor  [inline]
//   [ ] 0x9a9690  CKFlaggedPathCinematicBloc_DeletingDestructor  [inline]
#include "k2000/cinematics/CKFlaggedPathCinematicBloc.h"

#include "k2000/io/IKFile.h"
#include "k2000/memory/Mem.h"

// 0x001784d0 CKFlaggedPathCinematicBloc_Create (the constructor inlined)
CKFlaggedPathCinematicBloc::CKFlaggedPathCinematicBloc() {
    m_sfSpeed[0] = 0.0f;  // TOC 0xc127d4
    m_sfSpeed[2] = 0.0f;
    m_sfSpeed[1] = 0.0f;
    m_DatasIn.m_MasksOfGrdForTest[0] = 1;
    m_DatasIn.m_MasksOfGrdForTest[1] = 8;
    m_DatasInOut.m_eContactStatus = 3;
    m_DatasInOut.m_ui8SectorNumber = 0;
    m_DatasInOut.m_pGround = nullptr;
    m_DatasInOut.m_i32FaceIndex = -1;
    m_AnimStateEngineUnkCd = 0xff;
    m_AnimStateEngineState = 0;
    m_AnimStateEngineOwner = nullptr;
    m_AnimStateEngineTable = nullptr;
}

namespace {
// 0x00b1b2f8: the state engine's handler table the Load copies (three PS3 pointer-to-member pairs: the
// function descriptors 0xb640a8, 0xb64098, 0xb64090, each with a 0 adjustment).
// STUB(C2.2): native handlers replace these words when the state engine is ported.
constexpr uint32_t kFlaggedPathStateTable[6] = {0x00b640a8u, 0u, 0x00b64098u, 0u, 0x00b64090u, 0u};
}  // namespace

// 0x00179320 CKFlaggedPathCinematicBloc_Load
int32_t CKFlaggedPathCinematicBloc::Load(IKFile* file, int32_t type) {
    BasicLoadCinematicElement(file, type);
    if (type == K_LEVEL_PLATEFORMS) {
        ReadF32LE(file, &m_fRunSpeed);
        ReadF32LE(file, &m_fWalkSpeed);
        ReadF32LE(file, &m_fTimeForStatique);
        ReadF32LE(file, &m_fRotationSpeed);
        IKFile_ReadRef(file, &m_pFlaggedPath);
        ReadU32LEWords(file, reinterpret_cast<uint32_t*>(m_i32Tab), 3);  // one 0xc read, swapped
        ReadU8(file, &m_bPutOnGround);
        ReadU32LEWords(file, reinterpret_cast<uint32_t*>(m_fSpeedArray), 3);
        ReadU32LEWords(file, reinterpret_cast<uint32_t*>(m_fAccelerateArray), 3);
        ReadF32LE(file, &m_fAngleRotate);
        m_DatasInOut.m_pGround = nullptr;
        m_DatasInOut.m_i32FaceIndex = -1;
        m_DatasInOut.m_ui8SectorNumber = 0;
        m_DatasInOut.m_eContactStatus = 3;
        m_AnimStateEngineOwner = this;
        uint32_t* table = static_cast<uint32_t*>(Mem_AllocAligned16(0x18));
        m_AnimStateEngineTable = table;
        for (int i = 0; i < 6; ++i) table[i] = kFlaggedPathStateTable[i];
        m_AnimStateEngineState = 3;
        m_fDist = 0.0f;  // the word 0
        m_DatasIn.m_fDeltaMax = 0.5f;      // TOC 0xc127e0
        m_DatasIn.m_fObjectHeight = 1.2f;  // TOC 0xc127dc (0x3f99999a)
        m_DatasIn.m_MasksOfGrdForTest[0] = 1;
        m_DatasIn.m_MasksOfGrdForTest[1] = 8;
        m_pTime = nullptr;
        m_fStatiqueStartTime = -1.0f;      // TOC 0xc127e4
    }
    return 1;
}
