// CKHkS08Fire.cpp - reconstructed original translation unit 0x4da838-0x4dfc68 (GAME_TOC1, main_toc1), 42 functions, 37 live.
// Primary class: CKHkS08Fire  key 0x3442  category Hook  size 0xd8  vtable 0xb2a268
// Other owners: CKHkMecaSound (3)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [ ] 0x4da838  CKHkS08Fire_ReleaseStageFxRefs_maybe  [dead]
//   [ ] 0x4da930  CKHkS08Fire_ReleaseFlameFxRefByIndex_maybe  [dead]
//   [ ] 0x4da9b0  CKHkS08Fire_ReleaseFlameFxRefs_maybe  [dead]
//   [ ] 0x4daae8  RegisterCKHkS08FireClass
//   [ ] 0x4dab60  _GLOBAL__I_4dab60
//   [ ] 0x4dab70  CKHkS08Fire_StopSounds_maybe
//   [ ] 0x4dac18  CKHkS08Fire_InitCollisionVolume_maybe
//   [ ] 0x4dace8  CKHkS08Fire_ProcessPowerBucketContacts_maybe
//   [ ] 0x4daef8  CKHkS08Fire_GetInfo
//   [ ] 0x4dafd8  CKHkS08Fire_SetDefaultState
//   [ ] 0x4db010  CKHkS08Fire_Resume
//   [ ] 0x4db038  CKHkS08Fire_Pause
//   [ ] 0x4db060  CKHkS08Fire_Stop
//   [ ] 0x4db088  CKHkS08Fire_PostLoad
//   [ ] 0x4db0f0  CKHkS08Fire_RecursiveRegistration
//   [ ] 0x4db118  CKHkS08Fire_Construct_2
//   [x] 0x4db178  CKHkS08Fire_DeleteArray
//   [ ] 0x4db218  CKHkS08Fire_Destructor_2
//   [ ] 0x4db290  CKHkS08Fire_DeletingDestructor
//   [ ] 0x4db318  CKHkS08Fire_Destructor
//   [ ] 0x4db390  CKHkS08Fire_Destroy
//   [x] 0x4db3d0  CKHkS08Fire_Construct
//   [ ] 0x4db430  CKHkS08Fire_Save
//   [x] 0x4db458  CKHkS08Fire_CreateArray
//   [x] 0x4db538  CKHkS08Fire_Create
//   [ ] 0x4db5a8  CKHkS08Fire_OnDeactivate
//   [x] 0x4db7c8  CKHkS08Fire_Load
//   [ ] 0x4dc2c0  CKHkS08Fire_MessageProc
//   [ ] 0x4dc850  CKHkS08Fire_Restart
//   [ ] 0x4dcc78  CKHkS08Fire_Start
//   [ ] 0x4dcdb0  CKHkS08Fire_Update
//   [ ] 0x4dcfc0  CKHkS08Fire_AcquireFlameFxNode_maybe  [dead]
//   [ ] 0x4dd2a0  CKHkS08Fire_StartFlameStage_maybe
//   [ ] 0x4dddd0  CKHkS08Fire_OnActivate
//   [ ] 0x4de0a0  CKHkS08Fire_State3
//   [ ] 0x4de748  CKHkS08Fire_State2
//   [ ] 0x4dee10  CKHkS08Fire_State0
//   [ ] 0x4df490  CKHkS08Fire_State1
//   [ ] 0x4dfb58  CKHkMecaSound_Delete
//   [ ] 0x4dfba8  CKHkMecaSound_Restart
//   [ ] 0x4dfbb0  CKHkMecaSound_vfC8
//   [ ] 0x4dfbc0  FUN_004dfbc0  [dead]
//
//   [ ] 0x9c6250  CKHkS08Fire_IsKindOfClass  [inline]
//   [ ] 0x9c62a8  CKHkS08Fire_GetClassType  [inline]
//   [ ] 0x9c62b0  CKHkS08Fire_GetClassID  [inline]
//   [ ] 0x9c62b8  CKHkS08Fire_GetTriggerProp9A  [inline]
#include "Spyro2008/hooks/CKHkS08Fire.h"

#include <cstring>

#include "k2000/io/IKFile.h"
#include "k2000/misc/Mat4.h"

namespace {
// One 12-byte read, then the three words swapped (the inlined swap of the original).
void ReadVector(IKFile* file, CVector3* dst) {
    uint32_t words[3];
    ReadU32LEWords(file, words, 3);
    std::memcpy(dst, words, sizeof(words));
}
}  // namespace

// 0x004db7c8 CKHkS08Fire_Load: the actor base, then the level data (type 0 only). The trigger starters
// are loaded with type 0.
int32_t CKHkS08Fire::Load(IKFile* file, int32_t type) {
    CKHkActorBase::Load(file, type);
    if (type == K_LEVEL_PLATEFORMS) {
        IKFile_ReadRef(file, &m_pUnk38);
        IKFile_ReadRef(file, &m_pUnk40);
        IKFile_ReadRef(file, &m_pUnk48);
        IKFile_ReadRef(file, &m_pUnk54);
        ReadF32LE(file, &m_fUnk60);
        ReadF32LE(file, &m_fUnk5C);
        ReadU8(file, &m_unk50);
        ReadF32LE(file, &m_fUnk20);
        ReadF32LE(file, &m_fUnk24);
        IKFile_ReadRef(file, &m_pUnk2C);
        // 0x4dbaa0: a new matrix (RwMatrixCreate_Thunk 0x0023fa68), then its pos, at, up and right rows.
        // The first store clears rwMATRIXINTERNALIDENTITY (0x20000), the others also the type bits (3).
        m_pMatrix64 = RwMatrixCreate_Thunk();
        CMatrix34* matrix = m_pMatrix64;
        ReadVector(file, &matrix->m_pos);
        matrix->m_ui32Flags &= 0xfffdffffu;
        ReadVector(file, &m_pMatrix64->m_at);
        m_pMatrix64->m_ui32Flags &= 0xfffdfffcu;
        ReadVector(file, &m_pMatrix64->m_up);
        m_pMatrix64->m_ui32Flags &= 0xfffdfffcu;
        ReadVector(file, &m_pMatrix64->m_right);
        m_pMatrix64->m_ui32Flags &= 0xfffdfffcu;
        m_unk6C.Load(file, K_LEVEL_PLATEFORMS);
        m_unk74.Load(file, K_LEVEL_PLATEFORMS);
        ReadU8(file, &m_unk7C);
        ReadU8(file, &m_unk7D);
        ReadU8(file, &m_unk7E);
        IKFile_ReadRef(file, &m_pUnk30);
        IKFile_ReadRef(file, &m_pUnkA8);
        IKFile_ReadRef(file, &m_pUnkC8);
        IKFile_ReadRef(file, &m_pUnkAC);
        IKFile_ReadRef(file, &m_pUnkCC);
        IKFile_ReadRef(file, &m_pUnkB0);
        IKFile_ReadRef(file, &m_pUnkD0);
        IKFile_ReadRef(file, &m_pUnkB4);
        IKFile_ReadRef(file, &m_pUnkD4);
    }
    return 1;
}
