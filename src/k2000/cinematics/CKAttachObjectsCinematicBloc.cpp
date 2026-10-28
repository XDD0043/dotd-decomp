// CKAttachObjectsCinematicBloc.cpp - reconstructed original translation unit 0x172ba8-0x174a58 (GAME_TOC1, main_toc1), 19 functions, 18 live.
// Primary class: CKAttachObjectsCinematicBloc  key 0x248  category CinematicNode  size 0x84  vtable 0xb1b008
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x172ba8  CKAttachObjectsCinematicBloc_Delete
//   [ ] 0x172bf8  RegisterCKAttachObjectsCinematicBlocClass
//   [ ] 0x172c70  _GLOBAL__I_172c70
//   [ ] 0x172c80  CKAttachObjectsCinematicBloc_Update
//   [ ] 0x172ca8  CKAttachObjectsCinematicBloc_CreateMatrix_maybe  [dead]
//   [ ] 0x172d20  CKAttachObjectsCinematicBloc_RecursiveRegistration
//   [x] 0x172e40  CKAttachObjectsCinematicBloc_DeleteArray
//   [x] 0x172ee8  CKAttachObjectsCinematicBloc_Create
//   [ ] 0x172f40  CKAttachObjectsCinematicBloc_Destroy
//   [x] 0x172f80  CKAttachObjectsCinematicBloc_CreateArray
//   [ ] 0x173038  CKAttachObjectsCinematicBloc_AttachToParent_maybe
//   [ ] 0x1731f8  CKAttachObjectsCinematicBloc_ApplyAttachment_maybe
//   [ ] 0x173488  CKAttachObjectsCinematicBloc_RestoreObject_maybe
//   [ ] 0x173720  CKAttachObjectsCinematicBloc_Abort
//   [ ] 0x1737e8  CKAttachObjectsCinematicBloc_Stop
//   [ ] 0x173a80  CKAttachObjectsCinematicBloc_Start
//   [x] 0x173f38  CKAttachObjectsCinematicBloc_Load
//   [ ] 0x1743a8  CKAttachObjectsCinematicBloc_Save
//   [ ] 0x174880  CKAttachObjectsCinematicBloc_Complete
//
//   [ ] 0x9a9308  CKAttachObjectsCinematicBloc_IsKindOfClass  [inline]
//   [ ] 0x9a9340  CKAttachObjectsCinematicBloc_GetClassType  [inline]
//   [ ] 0x9a9348  CKAttachObjectsCinematicBloc_GetClassID  [inline]
//   [ ] 0x9a9350  CKAttachObjectsCinematicBloc_Destructor  [inline]
//   [ ] 0x9a9370  CKAttachObjectsCinematicBloc_DeletingDestructor  [inline]
#include "k2000/cinematics/CKAttachObjectsCinematicBloc.h"

#include <cstring>

#include "k2000/io/IKFile.h"
#include "k2000/misc/Mat4.h"

// 0x00173f38 CKAttachObjectsCinematicBloc_Load
int32_t CKAttachObjectsCinematicBloc::Load(IKFile* file, int32_t type) {
    BasicLoadCinematicElement(file, type);
    if (type == K_LEVEL_PLATEFORMS) {
        IKFile_ReadRef(file, &m_pLeaf);
        IKFile_ReadRef(file, &m_pLeafParent);
        IKFile_ReadRef(file, &m_pAttachLeaf);
        ReadU8(file, &m_bAttachToBone);
        ReadU32LE(file, &m_ui32BoneIndex);
        // Two 0xc-byte reads, each word swapped.
        uint32_t w[3];
        ReadU32LEWords(file, w, 3);
        std::memcpy(&m_v3Pos, w, 0xc);
        ReadU32LEWords(file, w, 3);
        std::memcpy(&m_v3OldPos, w, 0xc);
        ReadU8(file, &m_bRestorePos);
        ReadU8(file, &m_bAttachToHotSpot);
        CMatrix34* matrix = RwMatrixCreate_Thunk();
        m_pMatrixToApply = matrix;
        CMatrix34_LoadMatrix(matrix, file);
        IKFile_ReadRef(file, &m_pHotSpot);
        ReadU8(file, &m_unk78);
    }
    // 0x17426c: a fresh identity matrix, whatever the type.
    CMatrix34* old = RwMatrixCreate_Thunk();
    m_pOldMatrix = old;
    old->m_ui32Flags = 0x20003u;
    old->m_right.x = 1.0f;  // TOC 0xc12654
    old->m_pos.x = 0.0f;
    old->m_at.z = 1.0f;
    old->m_up.y = 1.0f;
    old->m_up.x = 0.0f;
    old->m_right.z = 0.0f;
    old->m_right.y = 0.0f;
    old->m_at.y = 0.0f;
    old->m_at.x = 0.0f;
    old->m_up.z = 0.0f;
    old->m_pos.z = 0.0f;
    old->m_pos.y = 0.0f;
    return 1;
}
