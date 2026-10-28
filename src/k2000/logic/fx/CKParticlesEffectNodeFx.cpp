// CKParticlesEffectNodeFx.cpp - reconstructed original translation unit 0x1cd4a0-0x1cf310 (GAME_TOC1, main_toc1), 23 functions, 17 live.
// Primary class: CKParticlesEffectNodeFx  key 0x1fcc  category Logic  size 0x30  vtable 0xb1d4d8
// Other owners: SetOwnedParticleEffectTransform (2), SetOwnedParticleEffectPosition (1), StopOwnedParticleEffect (1), UpdateParticleEffectLifetime (1), StartParticleEffect (1), StopParticleEffect (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [ ] 0x1cd4a0  FUN_001cd4a0  [dead]
//   [ ] 0x1cd598  FUN_001cd598  [dead]
//   [ ] 0x1cd5b8  RegisterCKParticlesEffectNodeFxClass
//   [ ] 0x1cd630  _GLOBAL__I_1cd630
//   [ ] 0x1cd640  CKParticlesEffectNodeFx_AttachNodesToHotSpot_maybe
//   [ ] 0x1cd718  CKParticlesEffectNodeFx_PostLoad
//   [x] 0x1cd758  CKParticlesEffectNodeFx_Load
//   [ ] 0x1cd910  CKParticlesEffectNodeFx_Save
//   [x] 0x1cd938  CKParticlesEffectNodeFx_DeleteArray
//   [x] 0x1cd9e0  CKParticlesEffectNodeFx_Create
//   [ ] 0x1cda50  CKParticlesEffectNodeFx_RecursiveRegistration
//   [ ] 0x1cdb30  SetOwnedParticleEffectTransform_2  [dead]
//   [ ] 0x1cdc08  SetOwnedParticleEffectTransform
//   [ ] 0x1cdce0  SetOwnedParticleEffectPosition
//   [ ] 0x1cdde8  StopOwnedParticleEffect
//   [ ] 0x1cde58  FUN_001cde58  [dead]
//   [ ] 0x1cdf58  FUN_001cdf58  [dead]
//   [ ] 0x1ce000  FUN_001ce000  [dead]
//   [ ] 0x1ce0a8  UpdateParticleEffectLifetime
//   [x] 0x1ce1e8  CKParticlesEffectNodeFx_StopIfLinkedTo
//   [x] 0x1ce2b8  CKParticlesEffectNodeFx_CreateArray
//   [ ] 0x1ce3a0  StartParticleEffect
//   [ ] 0x1cf0d0  StopParticleEffect
//
//   [ ] 0x9acce0  CKParticlesEffectNodeFx_IsKindOfClass  [inline]
//   [x] 0x9acd18  CKParticlesEffectNodeFx_GetClassType  [inline]
//   [x] 0x9acd20  CKParticlesEffectNodeFx_GetClassID  [inline]
//   [x] 0x9acd28  CKParticlesEffectNodeFx_GetFxData  [inline]
//   [x] 0x9acd30  CKParticlesEffectNodeFx_SetFxData  [inline]
//   [ ] 0x9acd38  CKParticlesEffectNodeFx_Destruct  [inline]
//   [ ] 0x9acdb8  CKParticlesEffectNodeFx_DeletingDestruct  [inline]
#include "k2000/logic/fx/CKParticlesEffectNodeFx.h"

#include "k2000/core/Stub.h"
#include "k2000/io/IKFile.h"
#include "k2000/logic/CKParticlesEffectFxData.h"
#include "k2000/memory/Mem.h"
#include "k2000/scenegraph/CParticlesNodeFx.h"

// Inlined in 0x001cd9e0 CKParticlesEffectNodeFx_Create.
CKParticlesEffectNodeFx::CKParticlesEffectNodeFx() {
    m_ppParticleNodes = nullptr;
    m_ui32NodeCapacity = 1;
    m_ui32NodeCount = 0;
}

// 0x001cd758 CKParticlesEffectNodeFx_Load: the particle-node references only in level files.
int32_t CKParticlesEffectNodeFx::Load(IKFile* file, int32_t type) {
    IKNodeFx::Load(file, type);
    if (type != K_LEVEL_PLATEFORMS) return 1;
    uint32_t count = 0;
    ReadU32LE(file, &count);
    if (count == 0) {
        m_ui32NodeCapacity = 1;
        m_ppParticleNodes =
            static_cast<CParticlesNodeFx**>(Mem_AllocAligned16(static_cast<uint32_t>(sizeof(CParticlesNodeFx*))));
    } else {
        m_ui32NodeCapacity = count;
        m_ppParticleNodes = static_cast<CParticlesNodeFx**>(
            Mem_AllocAligned16(count * static_cast<uint32_t>(sizeof(CParticlesNodeFx*))));
    }
    if (m_ui32NodeCapacity < count) {  // as in the original: cannot happen right after the assignment
        uint32_t capacity = count + 1;
        if (capacity == 0) capacity = 1;
        m_ppParticleNodes = static_cast<CParticlesNodeFx**>(
            Mem_ReallocAligned16(m_ppParticleNodes, capacity * static_cast<uint32_t>(sizeof(CParticlesNodeFx*))));
        m_ui32NodeCapacity = capacity;
    }
    m_ui32NodeCount = count;
    for (uint32_t i = 0; i < count; ++i) IKFile_ReadRef(file, &m_ppParticleNodes[i]);  // one reference at a time
    return 1;
}

// 0x001ce1e8 CKParticlesEffectNodeFx_StopIfLinkedTo
void CKParticlesEffectNodeFx::StopIfLinkedTo(int32_t sector) {
    if ((m_baFxData & 1) != 0 || sector == 0) return;
    if ((m_pEffectData->m_unk08 & 0x10) == 0) return;
    CSGLeaf* owner = m_pEffectData->m_pAttachOwner;
    if (owner == nullptr) return;
    if (sector == static_cast<int32_t>(owner->GetSectorIndex())) Stop();
}

// 0x001cf0d0 StopParticleEffect (vt+0x6c). STUB(C2.2): the effect's nodes taken off the dynamic scene root
// and reset (CParticlesNodeFx, CSGMovable_SetIdentity) belong to the effect runtime (StartParticleEffect
// 0x1ce3a0 is not ported either, so no effect runs and none can be linked to a sector).
void CKParticlesEffectNodeFx::Stop() {
    DOTD_STUB_ONCE("CKParticlesEffectNodeFx_Stop 0x1cf0d0 StopParticleEffect (C2.2)");
    IKNodeFx::Stop();
}

// 0x009acd28 / 0x009acd30 CKParticlesEffectNodeFx_GetFxData / SetFxData
IKFxData* CKParticlesEffectNodeFx::GetFxData() { return m_pEffectData; }
void CKParticlesEffectNodeFx::SetFxData(IKFxData* data) { m_pEffectData = static_cast<CKParticlesEffectFxData*>(data); }
