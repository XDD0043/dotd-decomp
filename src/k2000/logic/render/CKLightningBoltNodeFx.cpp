// CKLightningBoltNodeFx.cpp - reconstructed original translation unit 0x57a7c8-0x582a48 (GAME_TOC2, main_toc2), 53 functions, 50 live.
// Primary class: CKLightningBoltNodeFx  key 0xa60c  category Logic  size ?  vtable 0xb2e0b0
// Other owners: Vec3 (2)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x57a7c8  CKLightningBoltNodeFx_Delete
//   [ ] 0x57a818  CKLightningBoltNodeFx_InterpolateParam_maybe  [dead]
//   [ ] 0x57a890  CKLightningBoltNodeFx_SetStartSmoothParams_maybe
//   [ ] 0x57a8d0  CKLightningBoltNodeFx_SetEndSmoothParams_maybe
//   [ ] 0x57a910  CKLightningBoltNodeFx_StopAndReleaseChildNodes_maybe  [dead]
//   [ ] 0x57a9d0  CKLightningBoltNodeFx_SetTargetPoint_maybe
//   [ ] 0x57aa10  CKLightningBoltNodeFx_SetField1E0_maybe
//   [ ] 0x57aa38  CKLightningBoltNodeFx_SetField1E8_maybe
//   [ ] 0x57aa60  CKLightningBoltNodeFx_SetField1E4_maybe
//   [ ] 0x57aa88  CKLightningBoltNodeFx_SetField1E6_maybe
//   [ ] 0x57aab0  CKLightningBoltNodeFx_SetField1D8_maybe
//   [ ] 0x57aad8  CKLightningBoltNodeFx_SetStartIntensity_maybe
//   [ ] 0x57ab48  CKLightningBoltNodeFx_Destroy
//   [ ] 0x57aba0  RegisterCKLightningBoltNodeFxClass
//   [ ] 0x57ac18  _GLOBAL__I_57ac18
//   [ ] 0x57ac28  CKLightningBoltNodeFx_ResetImpactSlots_maybe
//   [ ] 0x57ae68  CKLightningBoltNodeFx_UpdateEndpoints_maybe
//   [ ] 0x57b0c0  CKLightningBoltNodeFx_UpdateFades_maybe
//   [ ] 0x57b230  CKLightningBoltNodeFx_UpdateVertexColors_maybe
//   [ ] 0x57b3d0  CKLightningBoltNodeFx_AllocSegments_maybe
//   [ ] 0x57b5f0  CKLightningBoltNodeFx_RecursiveRegistration
//   [x] 0x57b670  CKLightningBoltNodeFx_DeleteArray
//   [x] 0x57b710  CKLightningBoltNodeFx_Create
//   [ ] 0x57b780  CKLightningBoltNodeFx_StopIfLinkedTo
//   [ ] 0x57b968  CKLightningBoltNodeFx_SetField20C_maybe
//   [ ] 0x57b990  CKLightningBoltNodeFx_SetEndIntensity_maybe
//   [x] 0x57ba00  CKLightningBoltNodeFx_CreateArray
//   [x] 0x57bae0  CKLightningBoltNodeFx_Load
//   [ ] 0x57bc10  CKLightningBoltNodeFx_Save
//   [ ] 0x57bd30  CKLightningBoltNodeFx_RemoveBranchRecursive_maybe
//   [ ] 0x57bfd8  CKLightningBoltNodeFx_ResetBolt_maybe
//   [ ] 0x57c320  CKLightningBoltNodeFx_Start
//   [ ] 0x57c3c8  CKLightningBoltNodeFx_PostLoad
//   [ ] 0x57c430  CKLightningBoltNodeFx_SetNodePositionIfOwner_maybe
//   [ ] 0x57c4c8  CKLightningBoltNodeFx_SyncNodeToTarget_maybe
//   [ ] 0x57c650  CKLightningBoltNodeFx_PlaceNodeAtSource_maybe
//   [ ] 0x57c818  CKLightningBoltNodeFx_ComputeBranchPoint_maybe
//   [ ] 0x57cc20  CKLightningBoltNodeFx_GenerateBranch_maybe
//   [ ] 0x57d678  CKLightningBoltNodeFx_UpdateBranchesRecursive_maybe
//   [ ] 0x57d920  Vec3_RotateTowardByAngle_2_maybe  [dead]
//   [ ] 0x57db68  Vec3_AngleBetweenNormalizing_maybe
//   [ ] 0x57dce8  CKLightningBoltNodeFx_IsLinkedTo_maybe
//   [ ] 0x57e348  CKLightningBoltNodeFx_CollectTargetsInRange_maybe
//   [ ] 0x57ec40  CKLightningBoltNodeFx_BuildBranchVertices_maybe
//   [ ] 0x580030  CKLightningBoltNodeFx_RebuildGeometry_maybe
//   [ ] 0x5806c8  CKLightningBoltNodeFx_UpdateImpactExplosions_maybe
//   [ ] 0x580c58  CKLightningBoltNodeFx_SetEndParticlesActive_maybe
//   [ ] 0x581178  CKLightningBoltNodeFx_Stop
//   [ ] 0x581380  CKLightningBoltNodeFx_SetActiveForOwner_maybe
//   [ ] 0x581c38  CKLightningBoltNodeFx_UpdateImpactSlots_maybe
//   [ ] 0x5823f0  CKLightningBoltNodeFx_UpdateImpacts_maybe
//   [ ] 0x582470  CKLightningBoltNodeFx_Update
//   [ ] 0x5829a0  CKLightningBoltNodeFx_RestartForOwner_maybe
//
//   [ ] 0x9cb068  CKLightningBoltNodeFx_IsKindOfClass  [inline]
//   [x] 0x9cb0a8  CKLightningBoltNodeFx_GetClassType  [inline]
//   [x] 0x9cb0b0  CKLightningBoltNodeFx_GetClassID  [inline]
//   [ ] 0x9cb0b8  CKLightningBoltNodeFx_GetFxData  [inline]
//   [ ] 0x9cb0c0  CKLightningBoltNodeFx_SetFxData  [inline]
//   [ ] 0x9cb0c8  CKLightningBoltNodeFx_Destruct  [inline]
//   [ ] 0x9cb148  CKLightningBoltNodeFx_DeletingDestruct  [inline]
//   [ ] 0x9cb1d0  KBaseA58C_vf8  [inline]
//   [ ] 0x9cb200  KBaseA58C_vf14  [inline]
//   [ ] 0x9cb208  KBaseA58C_vf18  [inline]
#include "k2000/logic/render/CKLightningBoltNodeFx.h"

#include "k2000/io/IKFile.h"

// 0x0057b710 CKLightningBoltNodeFx_Create, the inlined constructor, in its store order.
CKLightningBoltNodeFx::CKLightningBoltNodeFx() {
    m_unk54.m_pBlock = nullptr;
    m_unk54.m_ui32NbElt = 1;
    m_unk54.m_ui32NbUsedElt = 0;
}

// 0x0057bae0 CKLightningBoltNodeFx_Load
int32_t CKLightningBoltNodeFx::Load(IKFile* file, int32_t type) {
    IKNodeFx::Load(file, type);  // through TocBridge_IKNodeFx_Load
    if (type == K_LEVEL_PLATEFORMS) {
        ReadU8(file, &m_unk18);
        ReadU32LE(file, &m_unk1c);
        ReadU32LE(file, &m_unk20);
    }
    return 1;
}
