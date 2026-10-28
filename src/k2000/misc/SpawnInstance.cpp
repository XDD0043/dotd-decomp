// SpawnInstance.cpp - reconstructed original translation unit 0xd4b30-0xd62b0 (GAME_TOC1, main_toc1), 9 functions, 7 live.
// Primary owner: SpawnInstance (not a registered class)
// Other owners: SpawnNodeData (3), SpawnNodeInfo (2)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [ ] 0xd4b30  SpawnNodeData_ResetInstanceState_maybe  [dead]
//   [ ] 0xd4ba8  SpawnNodeData_ClearReferences_maybe
//   [ ] 0xd4bf0  SpawnInstance_EnqueueGeometries_maybe
//   [ ] 0xd4df0  SpawnInstance_FindActorInBoundsAndStartShake_maybe
//   [x] 0xd5198  SpawnNodeInfo_Load
//   [x] 0xd5488  SpawnNodeData_PostLoad_maybe
//   [ ] 0xd55e8  SpawnNodeInfo_Save  [dead]
//   [ ] 0xd5a78  SpawnInstance_ApplyTransform_maybe
//   [ ] 0xd5e20  SpawnInstance_CullAndUpdate_maybe
#include "k2000/misc/ISpawnNode.h"

#include <cstring>

#include "Renderware/rwcore/RwCamera.h"
#include "Renderware/rwcore/RwMatrix.h"
#include "k2000/core/IKSerializable.h"
#include "k2000/io/IKFile.h"
#include "k2000/scenegraph/CSGMovable.h"

namespace {
// 0x00c50d34 (TOC1 -0x528c): the shared unit X vector the static initialiser 0x11578 builds (1, 0, 0).
const uint32_t kVectorUnitX[3] = {0x3f800000u, 0u, 0u};
}  // namespace

// 0x000d5198 SpawnNodeInfo_Load (XXL2 ISpawnNode::Load)
void ISpawnNode::Load(IKFile* file, int32_t type) {
    if (type != K_LEVEL_PLATEFORMS) return;
    m_pOriginalMatrix = nullptr;
    IKFile_ReadRef(file, &m_pSpawnPool);
    ReadU32LE(file, &m_ui32SectorNum);
    uint32_t words[6];
    ReadU32LEWords(file, words, 3);
    std::memcpy(m_rwBSphereCenter, words, 0xc);
    ReadF32LE(file, &m_rwBSphereRadius);
    ReadU32LEWords(file, words, 3);
    std::memcpy(m_unk04, words, 0xc);
    ReadF32LE(file, &m_unk10);
    ReadU32LEWords(file, m_aUnk38, 6);
}

// 0x000d5488 SpawnNodeData_PostLoad_maybe (called by CSpawnNode_PostLoad with the node's ISpawnNode part and
// the node as its CSGMovable): level data only. A copy of the node's frame matrix becomes the original matrix
// (all 16 words, flags and pads included) and the frame is given it again; the spawn state is reset.
void ISpawnNode::PostLoad(int32_t type, CSGMovable* node) {
    if (type != 0) return;
    RwMatrix* original = RwMatrixCreate();  // RwMatrixCreate_Thunk 0x23fa68
    m_pOriginalMatrix = original;
    std::memcpy(original, &node->m_pRwFrame->modelling, sizeof(RwMatrix));
    m_unk28 = 0xffffffffu;
    node->SetLocalMatrix(static_cast<const RwMatrix*>(m_pOriginalMatrix));  // 0x000d0be8
    m_unk34 = m_unk34 & 0x00ffffffu;  // the byte at +0x34 (type, 0)
    m_unk30 = static_cast<uint32_t>(type);
    std::memcpy(m_aUnk50, kVectorUnitX, 0xc);
}
