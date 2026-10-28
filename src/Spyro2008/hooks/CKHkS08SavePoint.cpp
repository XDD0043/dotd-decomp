// CKHkS08SavePoint.cpp - reconstructed original translation unit 0x4c98d8-0x4cc920 (GAME_TOC1, main_toc1), 31 functions, 28 live.
// Primary class: CKHkS08SavePoint  key 0x2e02  category Hook  size 0x84  vtable 0xb29870
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x4c98d8  CKHkS08SavePoint_Delete
//   [ ] 0x4c9928  CKHkS08SavePoint_Restart
//   [ ] 0x4c9930  CKHkS08SavePoint_GetInfo
//   [ ] 0x4c9980  CKHkS08SavePoint_SetModelYaw_maybe
//   [ ] 0x4c9a60  CKHkS08SavePoint_ApplyNodeAlphas_maybe  [dead]
//   [ ] 0x4c9d18  CKHkS08SavePoint_Resume
//   [ ] 0x4c9d40  CKHkS08SavePoint_Pause
//   [ ] 0x4c9d68  CKHkS08SavePoint_Stop
//   [x] 0x4c9d90  CKHkS08SavePoint_Start
//   [ ] 0x4c9de8  CKHkS08SavePoint_PostLoad
//   [ ] 0x4c9e10  CKHkS08SavePoint_Save
//   [ ] 0x4c9e38  CKHkS08SavePoint_RecursiveRegistration
//   [ ] 0x4c9e60  CKHkS08SavePoint_Destroy
//   [x] 0x4c9e88  CKHkS08SavePoint_Construct  [dead]
//   [x] 0x4c9ec0  CKHkS08SavePoint_DeleteArray
//   [ ] 0x4c9f68  RegisterCKHkS08SavePointClass
//   [ ] 0x4c9ff0  _GLOBAL__D_4c9ff0
//   [ ] 0x4ca000  _GLOBAL__I_4ca000
//   [ ] 0x4ca010  CKHkS08SavePoint_DeletingDestructor
//   [ ] 0x4ca058  CKHkS08SavePoint_Destructor
//   [ ] 0x4ca088  CKHkS08SavePoint_BaseDestructor
//   [ ] 0x4ca0b8  CKHkS08SavePoint_SetEnabled
//   [ ] 0x4ca178  CKHkS08SavePoint_Construct_2  [dead]
//   [x] 0x4ca1b0  CKHkS08SavePoint_Create
//   [x] 0x4ca208  CKHkS08SavePoint_CreateArray
//   [ ] 0x4ca2c0  CKHkS08SavePoint_SetVisible
//   [ ] 0x4ca7e8  CKHkS08SavePoint_OnDeactivate
//   [ ] 0x4ca9c8  CKHkS08SavePoint_MessageProc
//   [ ] 0x4cb030  CKHkS08SavePoint_Update
//   [ ] 0x4cbbf0  CKHkS08SavePoint_OnActivate
//   [x] 0x4cc318  CKHkS08SavePoint_Load
//
//   [ ] 0x9c5a50  CKHkS08SavePoint_IsKindOfClass  [inline]
//   [ ] 0x9c5aa8  CKHkS08SavePoint_GetClassType  [inline]
//   [ ] 0x9c5ab0  CKHkS08SavePoint_GetClassID  [inline]
#include "Spyro2008/hooks/CKHkS08SavePoint.h"

#include "k2000/io/IKFile.h"

// 0x004cc318 CKHkS08SavePoint_Load: the actor base, then the level data (type 0 only). The trigger
// starters are loaded with type 0.
int32_t CKHkS08SavePoint::Load(IKFile* file, int32_t type) {
    CKHkActorBase::Load(file, type);
    if (type == K_LEVEL_PLATEFORMS) {
        IKFile_ReadRef(file, &m_pUnk20);
        IKFile_ReadRef(file, &m_pUnk64);
        IKFile_ReadRef(file, &m_pUnk34);
        IKFile_ReadRef(file, &m_pUnk38);
        IKFile_ReadRef(file, &m_pUnk3C);
        IKFile_ReadRef(file, &m_pUnk40);
        m_unk24.Load(file, K_LEVEL_PLATEFORMS);
        m_unk2C.Load(file, K_LEVEL_PLATEFORMS);
        ReadRaw(file, m_unk44, 3);
        ReadRaw(file, m_unk47, 3);
        ReadRaw(file, m_unk4A, 3);
        ReadU8(file, &m_unk4D);
        ReadU8(file, &m_unk4E);
        ReadU8(file, &m_unk4F);
        ReadF32LE(file, &m_fUnk50);
        ReadF32LE(file, &m_fUnk54);
        ReadF32LE(file, &m_fUnk58);
        ReadU32LE(file, &m_unk5C);
        ReadU32LE(file, &m_unk60);
    }
    return 1;
}

// 0x004c9d90 CKHkS08SavePoint_Start (the actor base's empty ResetRuntime 0x3f6e48, then vt+0x54)
void CKHkS08SavePoint::Start() {
    Restart();
}
