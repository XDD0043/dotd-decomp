// CTrailNodeFx.cpp - reconstructed original translation unit 0xea630-0xec920 (GAME_TOC1, main_toc1), 17 functions, 16 live.
// Primary class: CTrailNodeFx  key 0x6cb  category SceneNode  size 0x38  vtable 0xb18c38
// Other owners: TrailStrip (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [ ] 0xea630  RegisterCTrailNodeFxClass
//   [ ] 0xea6a8  _GLOBAL__I_ea6a8
//   [ ] 0xea6b8  CTrailNodeFx_AllocPointBuffers_maybe  [dead]
//   [ ] 0xea8c0  CTrailNodeFx_RecursiveRegistration
//   [x] 0xea8e8  CTrailNodeFx_DeleteArray
//   [x] 0xea990  CTrailNodeFx_Create
//   [ ] 0xea9f0  CTrailNodeFx_Destroy
//   [x] 0xeaad8  CTrailNodeFx_CreateArray
//   [ ] 0xeabb0  TrailStrip_ResetPointsBetweenAnchors_maybe
//   [ ] 0xeae78  CTrailNodeFx_UpdateAnchorPoints_maybe
//   [x] 0xeb2d8  CTrailNodeFx_LoadPart
//   [x] 0xeb5f0  CTrailNodeFx_Load
//   [ ] 0xeb7b0  CTrailNodeFx_UpdateTrailGeometry_maybe
//   [ ] 0xec240  CTrailNodeFx_Enqueue
//   [ ] 0xec320  CTrailNodeFx_SaveSegment_maybe
//   [ ] 0xec610  CTrailNodeFx_Save
//   [ ] 0xec708  CTrailNodeFx_PostLoad
//
//   [ ] 0x9a5628  CTrailNodeFx_IsKindOfClass  [inline]
//   [ ] 0x9a5688  CTrailNodeFx_GetClassType  [inline]
//   [ ] 0x9a5690  CTrailNodeFx_GetClassID  [inline]
//   [ ] 0x9a5698  CTrailNodeFx_DeletingDestructor  [inline]
//   [ ] 0x9a56f0  CTrailNodeFx_Destructor  [inline]
//   [x] 0x9bdfb8  CTrailNodeFx_SetRibbonActive_maybe  [inline]
//   [ ] 0x9be780  KStub_Return12_9be780  [inline]
//   [ ] 0x9be788  KStub_Return674_9be788  [inline]
#include "k2000/scenegraph/CTrailNodeFx.h"

#include "k2000/core/Stub.h"

#include "k2000/io/IKFile.h"
#include "k2000/logic/CSGHotSpot.h"
#include "k2000/memory/Mem.h"

// 0x000eb2d8 CTrailNodeFx_LoadPart
void CTrailNodeFx::LoadTrail(uint32_t /*index*/, STrailNodeData* trail, IKFile* file, int32_t type) {
    if (type == K_LEVEL_PLATEFORMS) {
        ReadRaw(file, &trail->m_ui8Extrem1, 1);
        ReadRaw(file, &trail->m_ui8Extrem2, 1);
        ReadRaw(file, trail->m_cColor, 4);  // not swapped
        IKFile_ReadRef(file, &trail->m_pHotSpot1);
        IKFile_ReadRef(file, &trail->m_pHotSpot2);
        ReadU32LE(file, &trail->m_ui32NbCtrPoints);
        ReadU32LE(file, &trail->m_ui32NbLineVertex);
        ReadU32LE(file, &trail->m_unk44);
        ReadU32LE(file, &trail->m_unk38);
        ReadU32LE(file, &trail->m_unk34);
    }
    trail->m_ui8Visible = 0;
    trail->m_pCtrlPoints = nullptr;
    trail->m_ba8Properties = 0;
}

// 0x000eb5f0 CTrailNodeFx_Load
int32_t CTrailNodeFx::Load(IKFile* file, int32_t type) {
    INodeFx::Load(file, type);  // 0xeccd8
    if (type != K_LEVEL_PLATEFORMS) return 1;
    m_pTrailCtrlPoints = nullptr;
    ReadU32LE(file, &m_ui32NbTrail);
    if (m_ui32NbTrail == 0) {
        m_apTrailData = nullptr;
        return 1;
    }
    m_apTrailData = static_cast<STrailNodeData**>(Mem_AllocAligned16(m_ui32NbTrail * sizeof(STrailNodeData*)));
    // The loop counter is a byte (rlwinm 0xff): more than 255 trails would never end. Each trail block is
    // Mem_AllocAligned16(m_ui32NbTrail * 100), sized by the trail count rather than the 0x48-byte struct
    // (as the original; the native struct fits in 100 bytes on both builds).
    uint32_t index = 0;
    do {
        STrailNodeData* trail = static_cast<STrailNodeData*>(Mem_AllocAligned16(m_ui32NbTrail * 100));
        m_apTrailData[index] = trail;
        LoadTrail(index, trail, file, K_LEVEL_PLATEFORMS);
        index = (index + 1) & 0xff;
    } while (index < m_ui32NbTrail);
    return 1;
}

// 0x009bdfb8 CTrailNodeFx_SetRibbonActive_maybe
void CTrailNodeFx::SetRibbonActive(uint32_t ribbon, uint32_t active, int32_t resetGeometry) {
    STrailNodeData* trail = m_apTrailData[ribbon];
    if (active == (trail->m_ba8Properties & 1u)) return;
    trail->m_ba8Properties = static_cast<uint8_t>((trail->m_ba8Properties & 0xfeu) | active);
    trail->m_ui8Visible = static_cast<uint8_t>(trail->m_ui32NbCtrPoints);
    if (active != 0 || resetGeometry != 0) {
        // STUB(C2.7, the FX service: trail drawing): the control points between the two anchors (bone matrices, hot spots or the stored extremes,
        // by the node's scene flags bits 9-10) are laid out in a line; draw state.
        DOTD_STUB_ONCE("CTrailNodeFx::SetRibbonActive: ribbon geometry");
    }
}
