// CKPFGraphTransition_2.cpp - reconstructed original translation unit 0x1f0380-0x1f0f10 (GAME_TOC1, main_toc1), 21 functions, 20 live.
// Primary class: CKPFGraphTransition  key 0x8c  category Logic  size 0x24  vtable 0xb1e670
// Other owners: CKSrvPathFinding (3), NavSectorFlags (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x1f0380  CKPFGraphTransition_Delete
//   [x] 0x1f03d0  CKPFGraphTransition_RecursiveRegistration
//   [ ] 0x1f0438  RegisterCKPFGraphTransitionClass
//   [ ] 0x1f04b0  _GLOBAL__I_1f04b0
//   [x] 0x1f04c0  CKPFGraphTransition_DeleteArray
//   [x] 0x1f0568  CKPFGraphTransition_Create
//   [x] 0x1f0600  CKPFGraphTransition_ResetEnabledToDefault_maybe  (inline in the header)
//   [x] 0x1f0648  NavSectorFlags_AllowsAgent_maybe
//   [x] 0x1f06d8  CKPFGraphTransition_Save  (the base class default)
//   [x] 0x1f06e0  CKPFGraphTransition_GetInfo  (the base class default)
//   [x] 0x1f06e8  CKPFGraphTransition_MessageProc
//   [x] 0x1f0760  CKPFGraphTransition_PostLoad  (the base class default)
//   [x] 0x1f0768  CKPFGraphTransition_SetGameState
//   [x] 0x1f07d0  CKPFGraphTransition_Destroy
//   [x] 0x1f0860  CKPFGraphTransition_Load
//   [x] 0x1f0ad0  CKPFGraphTransition_CreateArray
//   [ ] 0x1f0bb8  FUN_001f0bb8  [dead]
//   [x] 0x1f0bc8  KStub_Return1_1f0bc8  (1: CKSrvPathFinding_RecursiveRegistration's call does nothing)
//   [x] 0x1f0bd0  CKSrvPathFinding_ClearGraph_maybe
//   [x] 0x1f0c38  CKSrvPathFinding_LoadGraph_maybe
//   [x] 0x1f0de8  CKSrvPathFinding_SaveGraph_maybe
//
//   [ ] 0x9b05d8  CKPFGraphTransition_GetClassType  [inline]
//   [ ] 0x9b05e0  CKPFGraphTransition_GetClassID  [inline]
//   [ ] 0x9b05e8  CKPFGraphTransition_DeletingDestructor  [inline]
//   [ ] 0x9b0628  CKPFGraphTransition_IsKindOfClass  [inline]
//   [ ] 0x9b0648  CKPFGraphTransition_Destructor  [inline]
//   [ ] 0x9b0660  KBase16CC_vf8  [inline]
//   [ ] 0x9b0680  KBase16CC_vf14  [inline]
//   [ ] 0x9b0688  KBase16CC_vf18  [inline]
#include "k2000/ai/CKSrvPathFinding.h"
#include "k2000/logic/CKPFGraphNode.h"
#include "k2000/io/IKFile.h"
#include "k2000/memory/Mem.h"

// 0x001f0c38 CKSrvPathFinding_LoadGraph_maybe (XXL2 CPFGraph::Load). Called with type 0 by
// CKSrvPathFinding_Load; reads the node references whatever the type.
int32_t CPFGraph::Load(IKFile* file, int32_t type) {
    ReadU32LE(file, &m_ui32GraphNodesSize);
    m_apGraphNodes = nullptr;
    if (m_ui32GraphNodesSize != 0) {
        m_apGraphNodes = static_cast<IKSerializable**>(
            Mem_AllocAligned16(m_ui32GraphNodesSize * static_cast<uint32_t>(sizeof(IKSerializable*))));
        if (m_ui32GraphNodesSize != 0) IKFile_ReadObjectRefArray(file, m_apGraphNodes, m_ui32GraphNodesSize);
    }
    if (type == K_LEVEL_PLATEFORMS) m_quadTree.Load(file, K_LEVEL_PLATEFORMS);
    // The nodes numbered (the index is taken as 16 bits: rlwinm 2,14,29).
    for (uint32_t i = 0; i < m_ui32GraphNodesSize; ++i) {
        static_cast<CKPFGraphNode*>(m_apGraphNodes[i & 0xffffu])->m_ui16Node = static_cast<uint16_t>(i);
    }
    return 1;
}
#include "k2000/logic/CKPFGraphTransition.h"

#include "k2000/io/IKFile.h"

// Inlined in 0x001f0568 CKPFGraphTransition_Create: the allowed character's defaults (flags 0x407, the
// radius from the grid scale's half cell size times 0.2 (fmuls), 0.2, 1.0) and a null node.
CKPFGraphTransition::CKPFGraphTransition() {
    m_AllowedChar.m_bits = 0;
    m_AllowedChar.m_bits = (m_AllowedChar.m_bits & 0xfffff800u) | 0x400u | 0x7u;  // the two bitfield stores
    m_AllowedChar.m_unk0c = 1.0f;
    m_AllowedChar.m_unk08 = 0x1.99999ap-3f;  // 0.2f
    m_AllowedChar.m_unk04 = g_pfGridScale.m_halfCellSize * 0x1.99999ap-3f;
    m_pNode = nullptr;
    m_AllowedChar.m_bits = (m_AllowedChar.m_bits & 0xfffffff8u) | 0x7u;
}

// 0x001f06e8 CKPFGraphTransition_MessageProc
int32_t CKPFGraphTransition::MessageProc(uint16_t message, void* /*data*/) {
    if (message == 0xa00) {
        m_baFlags = (m_baFlags & ~4u) | 4u;
        return 0;
    }
    if (message == 0xa01) {
        m_baFlags &= ~4u;
        return 0;
    }
    return 1;
}

// 0x001f0768 CKPFGraphTransition_SetGameState
int32_t CKPFGraphTransition::SetGameState(const SApplyGameState* state) {
    if (state->m_ui32GameStateId == 0) {
        m_baFlags = (m_baFlags & ~4u) | 4u;
        return 1;
    }
    if (state->m_ui32GameStateId == 1) {
        m_baFlags &= ~4u;
        return 1;
    }
    return 0;
}

// 0x001f0860 CKPFGraphTransition_Load
int32_t CKPFGraphTransition::Load(IKFile* file, int32_t type) {
    if (type != K_LEVEL_PLATEFORMS) return 1;
    ReadU32LE(file, &m_baFlags);
    IKFile_ReadRef(file, &m_pNode);
    m_AllowedChar.Load(file, K_LEVEL_PLATEFORMS);
    ReadU32LE(file, &m_ui32NbPortals);
    if (m_ui32NbPortals == 0) {
        m_aPortals = nullptr;
        return 1;
    }
    m_aPortals = new CPFPortal[m_ui32NbPortals];  // OperatorNewArray, each built by Door_Init
    for (uint32_t i = 0; i < m_ui32NbPortals; ++i) m_aPortals[i].Load(file, K_LEVEL_PLATEFORMS);
    return 1;
}

// 0x001f0648 NavSectorFlags_AllowsAgent_maybe
uint8_t CKPFGraphTransition::AllowsCharacter(const CPFCharacter* character) const {
    const uint32_t allowed = m_AllowedChar.m_bits;
    const uint32_t types = (allowed >> 3) & 0xffu;
    const uint32_t bits = character->m_bits;
    if (types != 0x80u && ((bits >> 3) & types) == 0) return 0;
    if ((allowed & bits & 7u) == 0) return 0;
    return m_AllowedChar.m_unk04 >= character->m_unk04 ? 1 : 0;
}

#include "k2000/ai/CKSrvPathFinding.h"
#include "k2000/logic/CKSavingManager.h"
#include "k2000/memory/Mem.h"
#include "k2000/misc/Engine.h"

// 0x001f07d0 CKPFGraphTransition_Destroy (the portals' destructors only store their vtable; OperatorDeleteArray)
void CKPFGraphTransition::Destroy() {
    if (m_aPortals != nullptr) delete[] m_aPortals;
    m_pNode = nullptr;
    m_aPortals = nullptr;
}

// 0x001f03d0 CKPFGraphTransition_RecursiveRegistration
void CKPFGraphTransition::RecursiveRegistration(int32_t type) {
    if (static_cast<uint32_t>(type - 4) > 3) g_pEngine->m_pSavingManager->RegisterSerializableObject(this, nullptr);
}

// 0x001f0bd0 CKSrvPathFinding_ClearGraph_maybe (CKSrvPathFinding_Destroy's; XXL2 CPFGraph::Destroy): the node block freed,
// then the quadtree's Destroy (CKQuadTreeRoot_Destroy 0x1f21f8, called directly; here its vt+0x10).
void CPFGraph::Clear() {
    if (m_apGraphNodes != nullptr) {
        Mem_FreeAligned16(m_apGraphNodes);
        m_apGraphNodes = nullptr;
    }
    m_quadTree.Destroy();
}

// 0x001f0de8 CKSrvPathFinding_SaveGraph_maybe
int32_t CPFGraph::Save(IKFile* file, int32_t /*type*/) {
    const uint32_t count = m_ui32GraphNodesSize;
    WriteU32LE(file, count);
    if (count == 0) return 1;
    if (file->m_pSavingInterfaces != nullptr) {
        file->m_pSavingInterfaces->WriteAsContiguousHandles(file, m_apGraphNodes, count);  // vt+0x4c
        return 1;
    }
    for (uint32_t i = 0; i < count; ++i) {  // the block's words as they are in memory (big-endian pointers)
        const uint32_t raw = static_cast<uint32_t>(reinterpret_cast<uintptr_t>(m_apGraphNodes[i]));
        const uint8_t b[4] = {static_cast<uint8_t>(raw >> 24), static_cast<uint8_t>(raw >> 16),
                              static_cast<uint8_t>(raw >> 8), static_cast<uint8_t>(raw)};
        file->Write(b, 4);
    }
    return 1;
}
