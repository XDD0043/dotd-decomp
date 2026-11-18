// CKNPCBehaviourBlockUser.cpp - reconstructed original translation unit 0x5c9bc0-0x5ca148 (GAME_TOC2, main_toc2), 21 functions, 21 live.
// Primary class: CKNPCBehaviourBlockUser  key 0x9ecc  category Logic  size ?  vtable 0xb30058
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x5c9bc0  CKNPCBehaviourBlockUser_Delete
//   [x] 0x5c9c10  CKNPCBehaviourBlockUser_vf50
//   [x] 0x5c9c18  CKNPCBehaviourBlockUser_vf54
//   [x] 0x5c9c28  CKNPCBehaviourBlockUser_vf5C
//   [x] 0x5c9c70  CKNPCBehaviourBlockUser_vf60
//   [ ] 0x5c9c80  RegisterCKNPCBehaviourBlockUserClass
//   [ ] 0x5c9cf8  _GLOBAL__I_5c9cf8
//   [x] 0x5c9d08  CKNPCBehaviourBlockUser_vf64
//   [x] 0x5c9d40  CKNPCBehaviourBlockUser_Load
//   [ ] 0x5c9e00  CKNPCBehaviourBlockUser_Save
//   [x] 0x5c9e28  CKNPCBehaviourBlockUser_RecursiveRegistration  (inherited: KBase9CCC_vf24)
//   [x] 0x5c9e50  CKNPCBehaviourBlockUser_Destroy  (inherited: KStub_Nop_5c5888)
//   [x] 0x5c9e78  CKNPCBehaviourBlockUser_DeletingDestructor  (C++ destructor chain: vtable stores only)
//   [x] 0x5c9ec0  CKNPCBehaviourBlockUser_Destructor  (C++ destructor chain: vtable stores only)
//   [x] 0x5c9ef0  CKNPCBehaviourBlockUser_Destructor_2  (C++ destructor chain: vtable stores only)
//   [x] 0x5c9f20  CKNPCBehaviourBlockUser_Construct_2  (the same as 0x5c9f58 CKNPCBehaviourBlockUser_Construct)
//   [x] 0x5c9f58  CKNPCBehaviourBlockUser_Construct
//   [x] 0x5c9f90  CKNPCBehaviourBlockUser_DeleteArray
//   [x] 0x5ca030  CKNPCBehaviourBlockUser_vf58
//   [x] 0x5ca040  CKNPCBehaviourBlockUser_Create
//   [x] 0x5ca098  CKNPCBehaviourBlockUser_CreateArray
//
//   [ ] 0x9cd5c8  CKNPCBehaviourBlockUser_IsKindOfClass  [inline]
//   [ ] 0x9cd600  CKNPCBehaviourBlockUser_GetClassType  [inline]
//   [ ] 0x9cd608  CKNPCBehaviourBlockUser_GetClassID  [inline]
#include "k2000/logic/CKNPCBehaviourBlockUser.h"

#include "k2000/io/IKFile.h"
#include "k2000/ui/CKHkScriptedNPC.h"

// 0x005c9d40 CKNPCBehaviourBlockUser_Load: the base's Load, then (level data only) one reference.
int32_t CKNPCBehaviourBlockUser::Load(IKFile* file, int32_t type) {
    KBase9CCC::Load(file, type);
    if (type == K_LEVEL_PLATEFORMS) IKFile_ReadRef(file, &m_unk04);
    return 1;
}

// 0x005c9c18 CKNPCBehaviourBlockUser_vf54: the NPC's node (+0x1c).
IKSerializable* CKNPCBehaviourBlockUser::GetAnimatedNode() { return static_cast<CKHkScriptedNPC*>(m_unk04)->m_pKGLObject; }

// 0x005ca030 CKNPCBehaviourBlockUser_vf58: the same node.
IKSerializable* CKNPCBehaviourBlockUser::GetMovable() { return static_cast<CKHkScriptedNPC*>(m_unk04)->m_pKGLObject; }

// 0x005c9c28 CKNPCBehaviourBlockUser_vf5C: the NPC's vt+0xf0 (CKHkScriptedNPC_vfF0).
void CKNPCBehaviourBlockUser::SetStream(IKSerializable* stream) { static_cast<CKHkScriptedNPC*>(m_unk04)->SetStream(stream); }

// 0x005c9c70 CKNPCBehaviourBlockUser_vf60: the NPC's hot spot (+0x30).
IKSerializable* CKNPCBehaviourBlockUser::GetHotSpot() { return static_cast<CKHkScriptedNPC*>(m_unk04)->m_pUnk30; }

// 0x005c9d08 CKNPCBehaviourBlockUser_vf64: the NPC (when there is one) chains its next block
// (CKHkScriptedNPC_QueueSignalsAndChainNextBlock_maybe 0x5c8f28; the block is passed along and not used).
void CKNPCBehaviourBlockUser::OnBlockDone(KBase9C8C* /*block*/) {
    if (m_unk04 != nullptr) static_cast<CKHkScriptedNPC*>(m_unk04)->QueueSignalsAndChainNextBlock();
}
