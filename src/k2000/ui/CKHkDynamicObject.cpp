// CKHkDynamicObject.cpp - reconstructed original translation unit 0x5a9bc8-0x5acb48 (GAME_TOC2, main_toc2), 32 functions, 26 live.
// Primary owner: CKHkDynamicObject (not a registered class)
// Other owners: RegisterCKHkDynamicObjectClass (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x5a9bc8  CKHkDynamicObject_Destroy
//   [x] 0x5a9c18  CKHkDynamicObject_Construct  [dead]
//   [ ] 0x5a9c60  CKHkDynamicObject_vf68
//   [ ] 0x5a9c68  CKHkDynamicObject_vf70
//   [ ] 0x5a9c70  CKHkDynamicObject_vf78
//   [ ] 0x5a9c78  RegisterCKHkDynamicObjectClass
//   [ ] 0x5a9cf0  _GLOBAL__I_5a9cf0
//   [ ] 0x5a9d00  CKHkDynamicObject_OnCycleComplete_maybe  [dead]
//   [ ] 0x5a9da8  CKHkDynamicObject_GetAxisFromFlagBits9to11_maybe  [dead]
//   [ ] 0x5a9ee8  CKHkDynamicObject_GetAxisFromFlagBits6to8_maybe  [dead]
//   [ ] 0x5a9ff0  CKHkDynamicObject_Save
//   [ ] 0x5aa018  CKHkDynamicObject_LevelReset
//   [ ] 0x5aa040  CKHkDynamicObject_ClearReferences
//   [x] 0x5aa0c8  CKHkDynamicObject_DestroyArray
//   [ ] 0x5aa170  CKHkDynamicObject_SetActive_maybe
//   [ ] 0x5aa1c8  CKHkDynamicObject_OnDeactivate
//   [ ] 0x5aa248  CKHkDynamicObject_OnActivate
//   [ ] 0x5aa2a8  CKHkDynamicObject_Construct_2  [dead]
//   [ ] 0x5aa2f0  CKHkDynamicObject_vf40
//   [x] 0x5aa348  CKHkDynamicObject_CreateArray
//   [x] 0x5aa418  CKHkDynamicObject_Create
//   [ ] 0x5aa480  CKHkDynamicObject_HandleMessage
//   [ ] 0x5aab98  CKHkDynamicObject_Update
//   [ ] 0x5ab788  CKHkDynamicObject_Destructor
//   [x] 0x5ab7a8  CKHkDynamicObject_Load
//   [ ] 0x5abfd8  CKHkDynamicObject_Destructor_2  [dead]
//   [ ] 0x5abff8  CKHkDynamicObject_PostLoad
//   [ ] 0x5ac2a0  CKHkDynamicObject_vf3C
//   [ ] 0x5ac608  CKHkDynamicObject_ResetToInitialState_maybe
//   [ ] 0x5ac818  CKHkDynamicObject_ReinitRuntime
//   [ ] 0x5ac9a0  CKHkDynamicObject_ResetRuntime
//   [ ] 0x5acb00  CKHkDynamicObject_DeletingDestructor
//
//   [ ] 0x9cbe30  CKHkDynamicObject_IsKindOf  [inline]
//   [ ] 0x9cbe78  CKHkDynamicObject_GetClassGroup  [inline]
//   [ ] 0x9cbe80  CKHkDynamicObject_GetClassId  [inline]
//   [ ] 0x9cbe88  CKHkDynamicObject_GetTriggerProp10  [inline]
#include "k2000/ui/CKHkDynamicObject.h"

#include "k2000/io/IKFile.h"
#include "k2000/misc/Mat4.h"

// 0x005ab7a8 CKHkDynamicObject_Load
int32_t CKHkDynamicObject::Load(IKFile* file, int32_t type) {
    IKHook::Load(file, type);  // through TocBridge_CKHook_Load
    if (type != K_LEVEL_PLATEFORMS) return 1;
    ReadF32LE(file, &m_unk70);
    ReadF32LE(file, &m_unk6C);
    ReadF32LE(file, &m_unk74);
    // Read into a local, +0x28 = 0, then +0x28 = the swapped word.
    uint32_t value = 0;
    ReadU32LE(file, &value);
    m_unk28 = 0;
    m_unk28 = value;
    IKFile_ReadRef(file, &m_pUnk44);
    ReadU32LEWords(file, reinterpret_cast<uint32_t*>(m_aUnk2C), 3);
    ReadF32LE(file, &m_unk38);
    ReadF32LE(file, &m_unk3C);
    ReadF32LE(file, &m_unk40);
    IKFile_ReadRef(file, &m_pUnk80);
    ReadF32LE(file, &m_unk78);
    ReadF32LE(file, &m_unk7C);
    IKFile_ReadRef(file, &m_pUnk68);
    ReadU32LEWords(file, reinterpret_cast<uint32_t*>(m_aUnk48), 3);
    ReadU32LEWords(file, reinterpret_cast<uint32_t*>(m_aUnk54), 3);
    ReadF32LE(file, &m_unk64);
    ReadF32LE(file, &m_unk60);
    IKFile_ReadRef(file, &m_pUnk84);
    ReadF32LE(file, &m_unk88);
    ReadF32LE(file, &m_unk8C);
    IKFile_ReadRef(file, &m_pUnk94);
    ReadF32LE(file, &m_unk90);
    m_pMatrix20 = RwMatrixCreate_Thunk();
    m_pMatrix24 = RwMatrixCreate_Thunk();
    CMatrix34_LoadMatrix(m_pMatrix20, file);
    CMatrix34_LoadMatrix(m_pMatrix24, file);
    IKFile_ReadRef(file, &m_pUnkF0);
    m_tsUnk98.Load(file, 0);
    m_tsUnkA0.Load(file, 0);
    ReadU8(file, &m_unkA8);
    ReadU8(file, &m_unkA9);
    return 1;
}
