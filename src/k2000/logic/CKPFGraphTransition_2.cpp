// CKPFGraphTransition_2.cpp - reconstructed original translation unit 0x1f0380-0x1f0f10 (GAME_TOC1, main_toc1), 21 functions, 20 live.
// Primary class: CKPFGraphTransition  key 0x8c  category Logic  size 0x24  vtable 0xb1e670
// Other owners: CKSrvPathFinding (3), NavSectorFlags (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x1f0380  CKPFGraphTransition_Delete
//   [ ] 0x1f03d0  CKPFGraphTransition_RecursiveRegistration
//   [ ] 0x1f0438  RegisterCKPFGraphTransitionClass
//   [ ] 0x1f04b0  _GLOBAL__I_1f04b0
//   [x] 0x1f04c0  CKPFGraphTransition_DeleteArray
//   [x] 0x1f0568  CKPFGraphTransition_Create
//   [ ] 0x1f0600  CKPFGraphTransition_ResetEnabledToDefault_maybe
//   [x] 0x1f0648  NavSectorFlags_AllowsAgent_maybe
//   [ ] 0x1f06d8  CKPFGraphTransition_Save
//   [ ] 0x1f06e0  CKPFGraphTransition_GetInfo
//   [ ] 0x1f06e8  CKPFGraphTransition_MessageProc
//   [ ] 0x1f0760  CKPFGraphTransition_PostLoad
//   [ ] 0x1f0768  CKPFGraphTransition_SetGameState
//   [ ] 0x1f07d0  CKPFGraphTransition_Destroy
//   [x] 0x1f0860  CKPFGraphTransition_Load
//   [x] 0x1f0ad0  CKPFGraphTransition_CreateArray
//   [ ] 0x1f0bb8  FUN_001f0bb8  [dead]
//   [ ] 0x1f0bc8  KStub_Return1_1f0bc8
//   [ ] 0x1f0bd0  CKSrvPathFinding_ClearGraph_maybe
//   [x] 0x1f0c38  CKSrvPathFinding_LoadGraph_maybe
//   [ ] 0x1f0de8  CKSrvPathFinding_SaveGraph_maybe
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
