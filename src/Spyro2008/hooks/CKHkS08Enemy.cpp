// CKHkS08Enemy.cpp - reconstructed original translation unit 0x276f58-0x285340 (GAME_TOC1, main_toc1), 96 functions, 89 live.
// Primary class: CKHkS08Enemy  key 0x26c2  category Hook  size 0x8f8  vtable 0xb22078
// Other owners: IKHkEnemy (8), Vec3 (3), GetEnemyGroup (1), GetHeroGroup (1), Contact (1), Volume (1), CKHkS08EnemyParent (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x276f58  GetEnemyGroup  (the same body as GetEnemyGroup_3 0x26e0e8: GetEnemyGroup(), k2000/groups/CKGrpFightZone.cpp)
//   [x] 0x276f70  GetHeroGroup  (enemy::HeroGroup(), CKHkS08EnemyShared.h)
//   [x] 0x276f88  CKHkS08Enemy_ClearVolumeGroupFlags
//   [x] 0x277008  CKHkS08Enemy_SetVolumeGroupFlags
//   [x] 0x277088  Contact_GetOtherVolume
//   [ ] 0x277160  Volume_DetachFromOwner_maybe  [dead]
//   [x] 0x2771c0  CKHkS08Enemy_GetSectorIndex_maybe
//   [x] 0x277240  CKHkS08Enemy_AllocAnimLayerSlots_maybe
//   [x] 0x2773e0  CKHkS08Enemy_UnregisterShadowCaster_maybe  (CKHkS08Enemy_xforkB.cpp)
//   [ ] 0x277448  CKHkS08Enemy_RegisterShadowCaster_maybe  [dead]
//   [x] 0x277528  IKHkEnemy_PostLoad
//   [ ] 0x277600  CKHkS08EnemyParent_1402_Save
//   [x] 0x277628  IKHkEnemy_LevelReset  (IKHkEnemy's RecursiveRegistration: inherited IKHook's)
//   [x] 0x277650  IKHkEnemy_Update
//   [x] 0x277670  CKHkS08Enemy_DisableVolumeGroup
//   [x] 0x277738  CKHkS08Enemy_EnableVolumeGroup
//   [x] 0x277800  CKHkS08Enemy_DisableVolume
//   [x] 0x277850  CKHkS08Enemy_EnableVolume
//   [x] 0x2778a0  CKHkS08Enemy_FreeBuffers_maybe
//   [x] 0x277c90  IKHkEnemy_TeleportTo_maybe
//   [x] 0x277d08  CKHkS08Enemy_ReleaseDynSphere_maybe
//   [x] 0x277dc8  CKHkS08Enemy_SetDynSphereFlags
//   [x] 0x277df8  IKHkEnemy_ResetMovementState_maybe
//   [x] 0x277f50  CKHkS08Enemy_ClearDynSphereFlags
//   [x] 0x277f80  CKHkS08Enemy_SetTrailRibbonEndpoints_maybe
//   [x] 0x278008  IKHkEnemy_vf124  (IKHkEnemy::ForceState16, IKHkEnemy.h)
//   [x] 0x278020  IKHkEnemy_HandleMessage  (IKHkEnemy's MessageProc: 1, inherited IKBaseClass's)
//   [x] 0x278028  CKHkS08Enemy_EmitParticleAt
//   [ ] 0x2781a0  CKHkS08Enemy_ConstructBase_2_maybe  [dead]
//   [x] 0x278330  IKHkEnemy_ConstrainToGroundAndNavMesh_maybe
//   [x] 0x2790d8  CKHkS08Enemy_ConstructBase_maybe
//   [x] 0x279268  CKHkS08Enemy_DetachSectorNode_maybe
//   [x] 0x279400  CKHkS08Enemy_StopAllSounds_maybe
//   [x] 0x2794f0  CKHkS08Enemy_StopSound
//   [x] 0x2795c0  CKHkS08Enemy_PlaySound
//   [x] 0x2796e8  CKHkS08Enemy_UpdateShadowCaster
//   [x] 0x279998  CKHkS08Enemy_EnableCollisionSphere_maybe
//   [x] 0x27a1b0  CKHkS08Enemy_DetachSectorNodesFromBones_maybe
//   [x] 0x27a748  CKHkS08Enemy_UnregisterActive
//   [x] 0x27aac0  CKHkS08Enemy_BindAttachmentToNode_maybe  (the attachment is a CDynamicGround)
//   [x] 0x27ad40  CKHkS08Enemy_AttachSectorNode_maybe
//   [x] 0x27b048  CKHkS08Enemy_AttachSectorNodesToBones_maybe
//   [x] 0x27b590  CKHkS08Enemy_RegisterActive
//   [x] 0x27b908  IKHkEnemy_Load
//   [x] 0x27c700  CKHkS08Enemy_StopTrailRibbon_maybe
//   [x] 0x27c7b0  CKHkS08Enemy_StartTrailRibbon_maybe
//   [x] 0x27cd58  CKHkS08Enemy_Delete
//   [x] 0x27cda8  EvalRampHoldRampDown_maybe
//   [x] 0x27ce18  CKHkS08Enemy_ResetAttackCooldowns_maybe
//   [x] 0x27ce50  IsEnemyInDeathStates_maybe
//   [x] 0x27ce90  CKHkS08Enemy_AddBurnGauge
//   [x] 0x27ceb8  CKHkS08Enemy_AddPoisonGauge
//   [x] 0x27cee0  CKHkS08Enemy_AddStunGauge
//   [x] 0x27cf08  CKHkS08Enemy_AddWindGauge_maybe
//   [x] 0x27cf30  CKHkS08Enemy_SetPartsFlagForCategory_maybe  (CKHkS08Enemy_xforkB.cpp)
//   [x] 0x27d018  CKHkS08Enemy_ClearPartsFlagForCategory_maybe  (CKHkS08Enemy_xforkB.cpp)
//   [x] 0x27d100  CKHkS08Enemy_GetAttackSlotCategory_maybe
//   [x] 0x27d138  CKHkS08Enemy_vf148
//   [x] 0x27d1b8  CKHkS08Enemy_SpawnBonusDrop_maybe
//   [x] 0x27d208  CKHkS08Enemy_PickSpotAlongTargetAim_maybe
//   [x] 0x27d460  Vec3_ForwardFromYaw_maybe
//   [x] 0x27d548  CKHkS08Enemy_Construct
//   [x] 0x27d650  CKHkS08Enemy_DeleteArray
//   [ ] 0x27d6f0  CKHkS08Enemy_IsState13_maybe  [dead]
//   [x] 0x27d708  CKHkS08Enemy_EnableAttackVolumes_maybe
//   [ ] 0x27d8a0  RegisterCKHkS08EnemyClass
//   [ ] 0x27d928  _GLOBAL__D_27d928
//   [ ] 0x27d938  _GLOBAL__I_27d938
//   [x] 0x27d948  CKHkS08Enemy_GetGroundSurfaceType_maybe
//   [x] 0x27d9b8  CKHkS08Enemy_UpdateAttackerHitCooldowns_maybe
//   [ ] 0x27db68  CKHkS08Enemy_Construct_2  [dead: no pointer to its descriptor 0xb8b3a0, no call]
//   [x] 0x27dc70  CKHkS08Enemy_IsWithinHeroRangeOfCameraFocus_maybe
//   [ ] 0x27de70  CKHkS08Enemy_ResolveSweptCylinderWalls_maybe  [dead]
//   [x] 0x27df10  GetActiveEnemyCentroid
//   [ ] 0x27e040  CKHkS08Enemy_AdvanceSpeedProfileMove_maybe  [dead]
//   [x] 0x27e148  CKHkS08Enemy_DeletingDestructor  (~CKHkS08Enemy, CKHkS08Enemy.h)
//   [x] 0x27e258  CKHkS08Enemy_CreateArray
//   [x] 0x27e408  CKHkS08Enemy_Create
//   [x] 0x27e520  CKHkS08Enemy_PickAttackSpotNearHeroAnyAngle_maybe
//   [x] 0x27ea88  CKHkS08Enemy_Destructor  (CKHkS08Enemy.h)
//   [x] 0x27eb88  Vec3_AngleBetween_maybe
//   [x] 0x27ed08  CKHkS08Enemy_BreakArmourPart
//   [x] 0x27efc0  Vec3_SignedAngleBetween_maybe
//   [ ] 0x27f1d8  CKHkS08Enemy_BaseDestructor  [dead: no pointer to its descriptor 0xb8b588, no call]
//   [x] 0x27f2d8  CKHkS08Enemy_ClampToNavSectors_maybe
//   [x] 0x27f8c0  CKHkS08Enemy_IsReachablePoint_maybe
//   [x] 0x27fce8  CKHkS08Enemy_PickRandomReachablePoint_maybe
//   [x] 0x280190  CKHkS08Enemy_PickAttackSpotNearHero_maybe
//   [x] 0x2808e8  CKHkS08Enemy_ChooseMoveTarget_maybe
//   [x] 0x280ca0  CKHkS08Enemy_UpdateOffNavFlag_maybe
//   [x] 0x280e30  CKHkS08Enemy_ComputeAttackApproachPoint_maybe
//   [x] 0x2820e8  CKHkS08Enemy_ForceState16_maybe
//   [x] 0x282228  CKHkS08Enemy_ForceAlerted_maybe
//   [ ] 0x282398  CKHkS08Enemy_ForceAwarenessState0_maybe  [dead]
//   [x] 0x2824d0  CKHkS08Enemy_ProcessContacts
//   [x] 0x283b08  CKHkS08Enemy_ResolveGroundAndApplyTransform_maybe
//
//   [ ] 0x9bc778  IKHkEnemy_IsKindOf  [inline]
//   [ ] 0x9bc7c0  IKHkEnemy_GetClassGroup  [inline]
//   [ ] 0x9bc7c8  IKHkEnemy_GetClassId  [inline]
//   [ ] 0x9bc7d0  IKHkEnemy_vf70  [inline]
//   [ ] 0x9bc7d8  IKHkEnemy_vf78  [inline]
//   [ ] 0x9bc7e0  IKHkEnemy_vfD4  [inline]
//   [ ] 0x9bc7e8  IKHkEnemy_vfD8  [inline]
//   [ ] 0x9bc7f0  CKHkS08Enemy_vfE8  [inline]
//   [ ] 0x9bc860  IKHkEnemy_Destructor  [inline]
//   [ ] 0x9bc8c0  IKHkEnemy_DeletingDestructor  [inline]
//   [ ] 0x9bc930  CKHkS08Enemy_IsKindOfClass  [inline]
//   [ ] 0x9bc988  CKHkS08Enemy_GetClassType  [inline]
//   [ ] 0x9bc990  CKHkS08Enemy_GetClassID  [inline]
//   [ ] 0x9bc998  CKHkS08Enemy_vfEC  [inline]
#include "Spyro2008/hooks/CKHkS08Enemy.h"
#include "Spyro2008/groups/IKGrpHero.h"
#include "k2000/cameras/CKSrvCamera.h"
#include "Spyro2008/logic/CKS08AccessoryManager.h"
#include "k2000/scenegraph/CKDynamicBoundingSphere.h"

#include "k2000/core/Stub.h"
#include <cstring>

#include "Renderware/rwcore/RwCamera.h"
#include "Renderware/rwcore/RwMatrix.h"
#include "Spyro2008/groups/CKGrpS08Enemy.h"
#include "Spyro2008/components/CKS08EnemyCpnt.h"
#include "Spyro2008/hooks/CKHkS08EnemyShared.h"
#include "k2000/services/KBase201.h"
#include "k2000/components/CKBonusData.h"
#include "Spyro2008/logic/CKS08GameManager.h"
#include "Spyro2008/logic/CKS08GolemDamage.h"
#include "Spyro2008/logic/memory/CKS08EnemyElementPool.h"
#include "Spyro2008/logic/CKS08EnemyElement.h"
#include "crt/ppc_ops.h"
#include "crt/xatan.h"
#include "k2000/ai/CKSrvPathFinding.h"
#include "k2000/logic/CKPFGraphNode.h"
#include "k2000/logic/CKPFGraphTransition.h"
#include "k2000/misc/Mat4.h"
#include "k2000/logic/physics/CDynamicGround.h"
#include "k2000/services/CollisionDatas.h"

#include "k2000/components/CKEnemySectorCpnt.h"
#include "k2000/dictionaries/CKSoundDictionaryID.h"
#include "k2000/graphical/animation/CKBlenderController.h"
#include "k2000/hooks/GroundContact.h"
#include "k2000/io/IKFile.h"
#include "k2000/logic/CDefaultGameManager.h"
#include "k2000/logic/CSGHotSpot.h"
#include "Renderware/rpprtstd/RpPrtStd.h"
#include "k2000/scenegraph/CParticlesNodeFx.h"
#include "k2000/logic/sound/CKSound.h"
#include "k2000/memory/Mem.h"
#include "k2000/misc/ClassRegistry.h"
#include "k2000/misc/Engine.h"
#include "k2000/misc/IKGrpEnemy.h"
#include "k2000/scenegraph/CAnimatedNode.h"
#include "k2000/scenegraph/CSGBranch.h"
#include "k2000/scenegraph/CTrailNodeFx.h"
#include "k2000/scenegraph/IKBoundingVolume.h"
#include "k2000/services/CKSrvAvoidance.h"
#include "k2000/services/CKSrvCollision.h"
#include "k2000/services/CKSrvShadow.h"
#include "k2000/services/ICollisionMesh.h"
#include "k2000/system/IKTime.h"
#include "Spyro2008/components/CKS08FightZoneCpnt.h"
#include "k2000/groups/CKGrpSquad.h"
#include "k2000/groups/CKGrpFightZone.h"
#include "k2000/ai/CKHkDetectorGroup.h"
#include "Spyro2008/hooks/CKHkS08Hero.h"
#include "Spyro2008/logic/CKS08ElementDamage.h"
#include "Spyro2008/logic/CKS08Damage.h"
#include "Spyro2008/logic/CKS08EnemyAttack.h"

using namespace enemy;

// 0x002790d8 CKHkS08Enemy_ConstructBase_maybe: IKHkEnemy's constructor. The bases, the ground-contact
// pair and the path-finding component set their own defaults; then the array pointers (not +0x3c) and
// +0x164/+0x1ac are cleared.
IKHkEnemy::IKHkEnemy() {
    m_apAnimLayerSlots = nullptr;
    m_unk1AC = 0;
    m_apBV = nullptr;
    m_aui8BoundingNumberByType = nullptr;
    m_aui8BoundingIndexByType = nullptr;
    m_unk20 = nullptr;
    m_unk24 = nullptr;
    m_unk28 = nullptr;
    m_unk40 = nullptr;
    m_unk58 = nullptr;
    m_unk68 = nullptr;
    m_apBVProj = nullptr;
    m_asProjPropeties = nullptr;
    m_afBVProjRadius = nullptr;
    m_av3BVProjPos = nullptr;
    m_apParticleNodeFx = nullptr;
    m_apTrailNodeFx = nullptr;
    m_unk60 = nullptr;
    m_apFogBoxNodeFx = nullptr;
}

// 0x00277df8 IKHkEnemy_ResetMovementState_maybe
void IKHkEnemy::ResetMovementState() {
    m_GrdContDatasIn.m_fDeltaMax = 0.2f;      // TOC1 +0xa8c: 0x3e4ccccd
    m_GrdContDatasIn.m_fObjectHeight = 2.0f;  // TOC1 +0xa90
    m_GrdContDatasIn.m_MasksOfGrdForTest[0] = 1;
    m_GrdContDatasIn.m_MasksOfGrdForTest[1] = 8;
    m_GrdContDatasInOut.m_pGround = nullptr;
    m_GrdContDatasInOut.m_eContactStatus = 3;
    m_GrdContDatasInOut.m_ui8SectorNumber = 0;
    m_GrdContDatasInOut.m_i32FaceIndex = -1;
    m_unkac = 0;
    m_unkb0 = 0.5f;  // TOC1 +0xa94
    m_unk14c = 0;
    m_unkb4 = 0;
    m_unk1ad = 0;
    // the zero vector 0x00c50d64 (TOC1 +0xa98)
    m_unk140 = 0.0f;
    m_unk148 = 0.0f;
    m_unk144 = 0.0f;
    m_v3Speed = CVector3{0.0f, 0.0f, 0.0f};
    m_avoidance.m_pNode = m_pKGLObject;
    if (m_unk60 != nullptr) {
        // the trail bytes of the kind's trail nodes go back to 0xff (the group is asked again every time)
        IKGrpEnemy* group = static_cast<IKGrpEnemy*>(g_pEngine->m_gameManager->m_unk04[0]);
        for (uint32_t i = 0; group->GetNbTrailNodes(m_ui8EnemyClassType) > i; ++i) m_unk60[i] = 0xff;  // vt+0x128
    }
}

// 0x00277240 CKHkS08Enemy_AllocAnimLayerSlots_maybe: one block of slots per animation layer of the enemy's kind.
void IKHkEnemy::AllocAnimLayerSlots() {
    IKGrpEnemy* group = static_cast<IKGrpEnemy*>(g_pEngine->m_gameManager->m_unk04[0]);
    const uint32_t layers = group->GetNbAnimLayers(m_ui8EnemyClassType);  // vt+0x108
    if (layers == 0) {
        m_apAnimLayerSlots = nullptr;
        return;
    }
    m_apAnimLayerSlots = new SEnemyAnimLayerSlot*[layers];  // OperatorNewArray(layers << 2)
    for (uint32_t layer = 0; layer < layers; ++layer) {
        const uint32_t count = group->GetNbAnimLayerSlots(m_ui8EnemyClassType, static_cast<uint8_t>(layer));  // vt+0x130
        if (count == 0) {
            m_apAnimLayerSlots[layer] = nullptr;
        } else {
            // OperatorNewArray(count * 0x2c + 4): the count cookie, then the slots: the layer object's vtable word
            // (0xb22068), the embedded AnimBlendSlot's vtable (0xb16530: the native one here) and no controller yet.
            SEnemyAnimLayerSlot* slots = new SEnemyAnimLayerSlot[count];
            for (uint32_t i = 0; i < count; ++i) {
                slots[i].m_unk00 = 0x00b22068u;
                slots[i].m_blendSlot.m_pController = nullptr;
            }
            m_apAnimLayerSlots[layer] = slots;
        }
    }
}

// 0x00277528 IKHkEnemy_PostLoad: IKLife_PostLoad, and for the level data the runtime reset (vt+0xc4), a matrix
// (the identity) and the animation-layer slots.
int32_t IKHkEnemy::PostLoad(int32_t type) {
    PostLoadLife(type);
    if (type == K_LEVEL_PLATEFORMS) {
        ResetRuntimeState();
        m_pDynGroundInvMatrix = reinterpret_cast<CMatrix34*>(RwMatrixCreate());  // RwMatrixCreate_Thunk 0x0023fa68
        m_pDynGroundInvMatrix->m_ui32Flags = 0x20003u;
        m_pDynGroundInvMatrix->m_right = CVector3{1.0f, 0.0f, 0.0f};
        m_pDynGroundInvMatrix->m_pos = CVector3{0.0f, 0.0f, 0.0f};
        m_pDynGroundInvMatrix->m_at = CVector3{0.0f, 0.0f, 1.0f};
        m_pDynGroundInvMatrix->m_up = CVector3{0.0f, 1.0f, 0.0f};
        AllocAnimLayerSlots();
    }
    return 1;
}

namespace {
// A count byte, then count raw u16s in a zeroed block (Mem_CallocAligned16(2, count)): the block is
// allocated only when the count is not 0.
void ReadRawU16Array(IKFile* file, uint16_t** array) {
    uint8_t count = 0;
    ReadU8(file, &count);
    if (count == 0) return;
    *array = static_cast<uint16_t*>(Mem_CallocAligned16(2, count));
    ReadRaw(file, *array, count * 2u);
}
}  // namespace

// 0x0027b908 IKHkEnemy_Load
int32_t IKHkEnemy::Load(IKFile* file, int32_t type) {
    IKHook::Load(file, type);
    if (type != K_LEVEL_PLATEFORMS) return 1;
    uint8_t count = 0;
    ReadU8(file, &count);
    if (count != 0) {
        m_apEnemySectorCpnt = static_cast<CKEnemySectorCpnt**>(
            Mem_CallocAligned16(static_cast<uint32_t>(sizeof(IKSerializable*)), count));
        IKFile_ReadObjectRefArray(file, reinterpret_cast<IKSerializable**>(m_apEnemySectorCpnt), count);
    }
    ReadRawU16Array(file, &m_unk20);
    ReadRawU16Array(file, &m_unk24);
    ReadRawU16Array(file, &m_unk28);
    ReadU8(file, &count);
    if (count != 0) {
        m_apBV = static_cast<IKSerializable**>(Mem_AllocAligned16(count * static_cast<uint32_t>(sizeof(IKSerializable*))));
        IKFile_ReadObjectRefArray(file, m_apBV, count);
    }
    ReadU8(file, &m_ui8NumberOfBoundingTypes);
    m_aui8BoundingNumberByType = static_cast<uint8_t*>(Mem_AllocAligned16(m_ui8NumberOfBoundingTypes));
    m_aui8BoundingIndexByType = static_cast<uint8_t*>(Mem_AllocAligned16(m_ui8NumberOfBoundingTypes));
    ReadRaw(file, m_aui8BoundingNumberByType, m_ui8NumberOfBoundingTypes);
    ReadRaw(file, m_aui8BoundingIndexByType, m_ui8NumberOfBoundingTypes);
    // One raw u16 per +0x2c reference (the count byte read above), allocated even for 0.
    m_unk40 = static_cast<uint16_t*>(Mem_CallocAligned16(2, count));
    ReadRaw(file, m_unk40, count * 2u);
    ReadU8(file, &count);
    if (count != 0) {
        m_apBVProj = static_cast<IKSerializable**>(
            Mem_CallocAligned16(static_cast<uint32_t>(sizeof(IKSerializable*)), count));
        m_asProjPropeties = static_cast<SEnemyProjectileBoundingProperties*>(
            Mem_AllocAligned16(count * static_cast<uint32_t>(sizeof(SEnemyProjectileBoundingProperties))));
        m_afBVProjRadius = static_cast<float*>(Mem_AllocAligned16(count * 4u));
        m_av3BVProjPos = static_cast<CVector3*>(Mem_AllocAligned16(count * static_cast<uint32_t>(sizeof(CVector3))));
        for (uint8_t i = 0; i < count; ++i) {
            SEnemyProjectileBoundingProperties& properties = m_asProjPropeties[i];
            ReadU16LE(file, &properties.m_ui16Properties);
            uint8_t owner = 0;
            ReadU8(file, &owner);
            properties.m_eOwnerType = owner;
            ReadRaw(file, &properties.m_i8ParentIndex, 1);
            ReadRaw(file, &properties.m_i8AttachHotSpotIndex, 1);
        }
        ReadU32LEWords(file, reinterpret_cast<uint32_t*>(m_afBVProjRadius), count);
        ReadU32LEWords(file, reinterpret_cast<uint32_t*>(m_av3BVProjPos), count * 3u);
    }
    ReadU8(file, &count);
    if (count != 0) {
        m_apParticleNodeFx = static_cast<IKSerializable**>(
            Mem_AllocAligned16(count * static_cast<uint32_t>(sizeof(IKSerializable*))));
        IKFile_ReadObjectRefArray(file, m_apParticleNodeFx, count);
        m_unk58 = static_cast<uint16_t*>(Mem_CallocAligned16(2, count));
        ReadRaw(file, m_unk58, count * 2u);
    }
    ReadU8(file, &count);
    if (count != 0) {
        m_apTrailNodeFx = static_cast<IKSerializable**>(
            Mem_AllocAligned16(count * static_cast<uint32_t>(sizeof(IKSerializable*))));
        IKFile_ReadObjectRefArray(file, m_apTrailNodeFx, count);
        m_unk60 = nullptr;
        m_unk60 = static_cast<uint8_t*>(Mem_AllocAligned16(count));
        for (uint8_t i = 0; i < count; ++i) m_unk60[i] = 0xff;
    }
    ReadU8(file, &count);
    if (count != 0) {
        m_apFogBoxNodeFx = static_cast<IKSerializable**>(
            Mem_AllocAligned16(count * static_cast<uint32_t>(sizeof(IKSerializable*))));
        IKFile_ReadObjectRefArray(file, m_apFogBoxNodeFx, count);
        m_unk68 = static_cast<uint16_t*>(Mem_CallocAligned16(2, count));
        ReadRaw(file, m_unk68, count * 2u);
    }
    ReadU8(file, &m_ui8EnemyClassType);
    IKFile_ReadRef(file, &m_pGroupSquad);
    IKFile_ReadRef(file, &m_unkB8);
    uint32_t position[3];
    ReadU32LEWords(file, position, 3);
    std::memcpy(&m_v3Position, position, sizeof(position));
    m_v3Speed = CVector3{0.0f, 0.0f, 0.0f};  // the zero vector 0xc50d64
    m_PFCpnt.Load(file, K_LEVEL_PLATEFORMS);
    ReadF32LE(file, &m_avoidance.m_fRadius);
    ReadF32LE(file, &m_avoidance.m_unk04);
    m_avoidance.m_pNode = nullptr;
    IKFile_ReadRef(file, reinterpret_cast<IKSerializable**>(&m_pEnemyCpnt));
    IKFile_ReadRef(file, &m_pShadowCpnt);
    ReadU8(file, &count);
    if (count != 0) {
        m_unk3C = static_cast<CVector3*>(Mem_AllocAligned16(count * static_cast<uint32_t>(sizeof(CVector3))));
        ReadU32LEWords(file, reinterpret_cast<uint32_t*>(m_unk3C), count * 3u);
    }
    return 1;
}

// 0x0027d548 CKHkS08Enemy_Construct (the same body inlined in CKHkS08Enemy_Create 0x27e408).
CKHkS08Enemy::CKHkS08Enemy() {
    m_pSecondVtable1C0 = nullptr;  // the original stores the second base's vtable 0xb21458
    m_mainStateCount = 0xff;
    m_mainState = 0xff;
    m_unk4E4.m_pBlock = nullptr;
    m_unk4E4.m_ui32NbUsedElt = 0;
    m_unk4E4.m_ui32NbElt = 1;
    m_unk4F0.m_pBlock = nullptr;
    m_unk4F0.m_ui32NbUsedElt = 0;
    m_unk4F0.m_ui32NbElt = 1;
    m_unk4FC.m_pBlock = nullptr;
    m_unk4FC.m_ui32NbUsedElt = 0;
    m_unk4FC.m_ui32NbElt = 1;
    m_unk508.m_pBlock = nullptr;
    m_unk508.m_ui32NbUsedElt = 0;
    m_unk508.m_ui32NbElt = 1;
    m_unk514.m_ui32NbUsedElt = 0;
    m_unk514.m_pBlock = nullptr;
    m_unk514.m_ui32NbElt = 1;
    m_awareStateCount = 0xff;
    m_awareState = 0xff;
    m_reactStateCount = 0xff;
    m_reactState = 0xff;
    m_auxStateCount = 0xff;
    m_auxState = 0xff;
    // m_damage8BC: CKS08Damage_Construct(this + 0x8bc) 0x4ebc70, the last call of the original (member constructor).
}

namespace {
template <class T>
void FreeAndClear(T*& block) {
    if (block == nullptr) return;
    Mem_FreeAligned16(block);  // 0x00052fb8
    block = nullptr;
}
}  // namespace

// 0x002778a0 CKHkS08Enemy_FreeBuffers_maybe (the enemies' vt+0xc0; Destroy): the Load's / PostLoad's arrays freed and
// cleared in the original's order, the animation-layer slots deleted per layer (the group's vt+0x108 count; the slots'
// destructors are vtable-only), their table deleted, the sector components' table freed and the matrix destroyed.
void IKHkEnemy::FreeBuffers() {
    FreeAndClear(m_apBV);
    FreeAndClear(m_aui8BoundingNumberByType);
    FreeAndClear(m_aui8BoundingIndexByType);
    FreeAndClear(m_unk20);
    FreeAndClear(m_unk24);
    FreeAndClear(m_unk28);
    FreeAndClear(m_unk40);
    FreeAndClear(m_unk58);
    FreeAndClear(m_unk68);
    FreeAndClear(m_apBVProj);
    FreeAndClear(m_asProjPropeties);
    FreeAndClear(m_afBVProjRadius);
    FreeAndClear(m_av3BVProjPos);
    FreeAndClear(m_unk3C);
    FreeAndClear(m_apParticleNodeFx);
    FreeAndClear(m_apTrailNodeFx);
    FreeAndClear(m_unk60);
    FreeAndClear(m_apFogBoxNodeFx);
    IKGrpEnemy* group = static_cast<IKGrpEnemy*>(g_pEngine->m_gameManager->m_unk04[0]);
    const uint8_t layers = group->GetNbAnimLayers(m_ui8EnemyClassType);  // vt+0x108
    for (uint32_t layer = 0; layer != layers; ++layer) {
        if (m_apAnimLayerSlots[layer] == nullptr) continue;
        delete[] m_apAnimLayerSlots[layer];  // the slots' vt+0 last first, then OperatorDeleteArray
        m_apAnimLayerSlots[layer] = nullptr;
    }
    if (m_apAnimLayerSlots != nullptr) {
        delete[] m_apAnimLayerSlots;  // TocBridge_OperatorDeleteArray
        m_apAnimLayerSlots = nullptr;
    }
    FreeAndClear(m_apEnemySectorCpnt);
    RwMatrixDestroy_Thunk(m_pDynGroundInvMatrix);  // 0x0023f968
    m_pDynGroundInvMatrix = nullptr;
}

// 0x0027b590 CKHkS08Enemy_RegisterActive (IKHkEnemy's vt+0xcc): the sector nodes attached, the enemy listed by its group,
// the runtime state reset (vt+0xc4), the avoidance agent listed, the life flags 0x80 / 0x38 cleared, the path-finding
// radius and validation distance from the component's radius, the shadow caster registered at the enemy's position,
// the avoidance radius, and every animation layer slot given its controller.
void IKHkEnemy::Activate() {
    CKHkS08Enemy* self = static_cast<CKHkS08Enemy*>(this);
    self->AttachSectorNodesToBones();  // 0x0027b048
    IKGrpEnemy* group = EnemyGroup();
    AddActiveEncounterEnemy(group, this);  // 0x00265a50
    ResetRuntimeState();  // vt+0xc4
    static_cast<CKSrvAvoidance*>(g_pEngine->m_srvAvoidance)->AddAgent(&m_avoidance);  // 0x00122b60
    m_bitArray = m_bitArray & 0xffffff47u;  // rlwinm 24/8 clear 0x80, rlwinm 26/6 clear 0x38
    const float half = g_pfGridScale.m_halfCellSize;  // 0x00c40260 (TOC1 +0xab4)
    const float margin = 0.05f;                      // TOC1 +0xac0 0x3d4ccccd
    float radius = m_pEnemyCpnt->m_MoveCpnt.m_afParams[0];
    const float cap = half - margin;
    if (!(radius < cap)) radius = cap;
    m_PFCpnt.m_CharacterType.m_fRadius = radius;
    const float half2 = g_pfGridScale.m_halfCellSize;
    const float cap2 = half2 - margin;
    float distance = m_pEnemyCpnt->m_MoveCpnt.m_afParams[0];
    if (!(distance < cap2)) distance = cap2;
    if (!(distance < half2)) distance = half2;
    m_PFCpnt.m_fPointValidationDistanceSquared = distance * distance;
    m_unk1ad = 0;
    if (m_pShadowCpnt != nullptr) {
        static_cast<CKSrvShadow*>(g_pEngine->m_srvShadow)
            ->RegisterCaster(m_pShadowCpnt, m_pKGLObject, reinterpret_cast<CKShadowGround*>(&m_v3ShadowGroundPosition), 0, nullptr, 0);  // 0x001fb6f8
        m_v3ShadowGroundPosition.x = m_v3Position.x;
        m_v3ShadowGroundPosition.z = m_v3Position.z;
        m_v3ShadowGroundPosition.y = m_v3Position.y;
        m_v3ShadowGroundNormal = kAxisY;  // 0x00c50d40 (TOC1 +0xa84)
        m_unk1a8 = 0.0f;
    }
    m_avoidance.m_fRadius = m_pEnemyCpnt->m_MoveCpnt.m_afParams[1];
    const uint32_t variant = GroupKindFlag104(m_ui8EnemyClassType) == 0 ? SquadFightZoneIndex(m_pGroupSquad) : 0u;
    CKEnemySectorCpnt* sector = m_apEnemySectorCpnt[variant];
    for (uint32_t layer = 0; layer < GroupNbAnimLayers(m_ui8EnemyClassType); ++layer) {
        SEnemyAnimLayerSlot* slots = m_apAnimLayerSlots[layer];
        for (uint32_t slot = 0; slot < GroupNbAnimLayerSlots(m_ui8EnemyClassType, static_cast<uint8_t>(layer)); ++slot) {
            self->InitAnimLayerSlot(&slots[slot], sector->GetChainedEntry(layer, slot));  // 0x002b3140, then 0x00079ff0
        }
    }
}

// 0x0027a748 CKHkS08Enemy_UnregisterActive (IKHkEnemy's vt+0xd0): the sector nodes detached, the sounds of the sector's
// dictionary stopped (from the last), the enemy unlisted by its group and the avoidance service, the shadow caster
// unregistered, the path request cancelled, and the enemy taken out of its fog boxes' lists.
void IKHkEnemy::Deactivate() {
    CKHkS08Enemy* self = static_cast<CKHkS08Enemy*>(this);
    self->DetachSectorNodesFromBones();  // 0x0027a1b0
    const uint32_t variant = GroupKindFlag104(m_ui8EnemyClassType) == 0 ? SquadFightZoneIndex(m_pGroupSquad) : 0u;
    CKSoundDictionaryID* sounds = static_cast<CKSoundDictionaryID*>(m_apEnemySectorCpnt[variant]->m_pUnk1c);
    for (uint32_t i = sounds->m_ui32NbKSound; i != 0;) {
        --i;
        CKSound* sound = sounds->GetSound(i);  // 0x00112bc0
        if (sound != nullptr) Sound_Stop(sound, 0);  // 0x001111b0
    }
    RemoveActiveEncounterEnemy(EnemyGroup(), this);  // 0x00265a78
    static_cast<CKSrvAvoidance*>(g_pEngine->m_srvAvoidance)->RemoveAgent(&m_avoidance);  // 0x00122bb0
    if (m_pShadowCpnt != nullptr && m_unk1ad != 0) {
        static_cast<CKSrvShadow*>(g_pEngine->m_srvShadow)
            ->UnregisterCaster(reinterpret_cast<CKShadowGround*>(&m_v3ShadowGroundPosition), m_pShadowCpnt);  // 0x001fd6f0
    }
    m_PFCpnt.CancelPathRequest();  // 0x001e2820
    for (uint32_t i = 0; i < GroupNbFogBoxes(m_ui8EnemyClassType); ++i) {
        // STUB(C2.9: unreachable in every level): the enemy's entry (+0x04 == this) taken out of the fog box's list (+0x3c
        // entries of 0x10 bytes, +0x40 count; the last entry's 0x40-byte block copied over it). CKGrpS08Enemy vt+0x12c
        // (0x00a6fec8 +0x90) gives 0 fog boxes for all nine enemy kinds, so this never runs.
        DOTD_STUB_ONCE("CKHkS08Enemy_UnregisterActive 0x27a748: the fog box lists (none in DotD)");
    }
}

// 0x00277c90 IKHkEnemy_TeleportTo_maybe (vt+0xdc): the position, the path finding's current position, the node turned to
// `direction` with the Y axis up.
void IKHkEnemy::SpawnAtPosition(const CVector3* position, const CVector3* direction, uint32_t /*flags*/) {
    m_v3Position.x = position->x;
    m_v3Position.y = position->y;
    m_v3Position.z = position->z;
    m_PFCpnt.SetDestination(&m_v3Position);  // 0x001e3a40 CKPathFindingCpnt_ResetCurrentPosition
    static_cast<CSGMovable*>(m_pKGLObject)->SetOrientationFromAtUp(direction, &kAxisY);  // 0x000d0918, TOC1 +0xa84
}

// 0x00278330 IKHkEnemy_ConstrainToGroundAndNavMesh_maybe (vt+0xe0): the move of the frame (from +0x140 to the position)
// checked. On a moving ground (CDynamicGround, class id 0x13) the position first follows it (through the matrix kept at
// +0x150). Unless the enemy stays in place, the nav mesh is asked (the path finding's node hint follows the new point;
// a node change needs a transition the character may take; an unwalkable point falls back to the previous one, the
// path-finding radius shrinking to 0 or back to the component's), then the ground is probed (higher test box when
// rising) and the position put on it, slid along walls in the air (status 3) or off a moving ground (status 2), or
// left (life flag 0x40) when it is above the ground's +0xb0 step. Returns 0 when the position went back to +0x140.
uint32_t IKHkEnemy::ConstrainToGroundAndNavMesh() {
    CVector3& pos = m_v3Position;
    const CVector3 prevVec = {m_unk140, m_unk144, m_unk148};
    const bool prevZero = m_unk140 == 0.0f && m_unk144 == 0.0f && m_unk148 == 0.0f;  // the zero vector 0x00c50d64
    m_bitArray = m_bitArray & 0xffffffbfu;  // rlwinm 25 / 7
    CGroundContactDatasInOut& contact = m_GrdContDatasInOut;
    CKSrvCollision* collision = nullptr;
    CKSrvPathFinding* pathFinding = nullptr;
    CPFPoint point;
    CSlideGroundEdgeDatasOut slide;
    CLine line;
    int32_t oldHint = 0;
    uint16_t newHint = 0;
    uint8_t result = 0;

    // The moving-ground part (0x2785a0) runs while +0x14c says the enemy stood on one.
    bool onDynamic = false;
    if (contact.m_pGround == nullptr) {
        onDynamic = true;
    } else if (static_cast<ICollisionMesh*>(contact.m_pGround)->GetClassID() == 0x13) {  // vt+0x18
        onDynamic = true;
    } else {
        m_unk14c = 0;
    }
    if (onDynamic && m_unk14c != 0) {
        if (contact.m_pGround == nullptr) goto checkMoved;  // 0x00278914 -> 0x0027843c
        {
            CVector3 local;
            CVector3 world;
            Mat4_TransformPoints(m_pDynGroundInvMatrix, &local, &pos, 1);  // 0x0023f7e8
            Mat4_TransformPoints(static_cast<ICollisionMesh*>(contact.m_pGround)->GetWorldMatrix(), &world, &local, 1);  // vt+0x50
            pos.x = world.x;
            pos.z = world.z;
            pos.y = world.y + 0.1f;  // TOC1 +0xac4 0x3dcccccd
            CopyMatrix(m_pDynGroundInvMatrix, static_cast<ICollisionMesh*>(contact.m_pGround)->GetInvertedWorldMatrix());  // vt+0x54
        }
        if (m_unk14c == 0) goto checkMoved;
        if ((m_PFCpnt.m_eState & 0x40) != 0) goto checkActions;
        goto navMesh;
    }
    // 0x0027842c: no move, nothing to do.
    if (pos.x == prevVec.x && pos.y == prevVec.y && pos.z == prevVec.z) return 1;
checkMoved:  // 0x0027843c
    if ((m_PFCpnt.m_eState & 0x40) == 0) goto navMesh;
checkActions:  // 0x00278450
    if ((m_PFCpnt.m_bits70 & 0x400) != 0) goto navMesh;
ground:  // 0x00278460
    {
        collision = static_cast<CKSrvCollision*>(g_pEngine->m_srvCollision);
        const float rise = m_unk144 - pos.y;
        if (!(rise <= 0.0f) && !prevZero) {  // TOC1 +0xac8
            m_GrdContDatasIn.m_fDeltaMax = rise + 0.2f;      // TOC1 +0xa8c
            m_GrdContDatasIn.m_fObjectHeight = rise + 2.0f;  // TOC1 +0xa90
        } else {
            m_GrdContDatasIn.m_fDeltaMax = 0.2f;
            m_GrdContDatasIn.m_fObjectHeight = 2.0f;
        }
        collision->GroundProbePoints(&m_GrdContDatasIn, &contact, &pos.x, 1);  // 0x00196540
        if (contact.m_pGround != nullptr && static_cast<ICollisionMesh*>(contact.m_pGround)->GetClassID() == 0x13) {
            CopyMatrix(m_pDynGroundInvMatrix, static_cast<ICollisionMesh*>(contact.m_pGround)->GetInvertedWorldMatrix());  // vt+0x54
            m_unk14c = 1;
        } else {
            m_unk14c = 0;
        }
        const int32_t status = static_cast<int32_t>(contact.m_eContactStatus);
        if (status == 1) {
            GroundContact_GetWorldPoint(&contact, &pos);  // 0x001a70e0
            return 1;
        }
        if (status < 1) {
            if (status != 0) return 1;
            if (static_cast<ICollisionMesh*>(contact.m_pGround)->GetClassID() == 0x13) {
                GroundContact_GetWorldPoint(&contact, &pos);
                return 1;
            }
            // 0x00278dd0: below the step height the position is put on the ground; above it, too, with flag 0x40.
            if (pos.y - contact.m_ProjectionOnGround.y < m_unkb0) goto onGround;
            pos.z = contact.m_ProjectionOnGround.z;
            pos.x = contact.m_ProjectionOnGround.x;
            pos.y = contact.m_ProjectionOnGround.y;
            m_bitArray = (m_bitArray & 0xffffffbfu) | 0x40u;
            return 1;
        }
        if (status == 2) {
            if (static_cast<ICollisionMesh*>(contact.m_pGround)->GetClassID() == 0x13) goto offDynamic;
            if (prevZero) goto onGround;
            result = SweepFromPrevious(collision, &line, &slide);  // 0x00278e60
            if (result == 1) goto backToPrevious;
            if (result > 1) goto slid;
            if (result == 0) goto onGround;
            return 1;
        }
        if (status == 3) {
            if (prevZero) return 1;
            result = SweepFromPrevious(collision, &line, &slide);  // 0x0027891c
            if (result == 1) goto backToPrevious;
            if (result == 0) goto backToPrevious;
            goto slid;
        }
        return 1;
    }
slid:  // 0x002789a8 (results 2 and 3: the slide added, the height kept)
    if (result > 3) return 1;
    {
        const float y = slide.m_v3BouncingVector.y + pos.y;
        const float z = slide.m_v3BouncingVector.z + pos.z;
        const float x = slide.m_v3BouncingVector.x + pos.x;
        pos.y = y;
        pos.y = m_unk144;
        pos.z = z;
        pos.x = x;
    }
    return 1;
onGround:  // 0x00278a84
    pos.z = contact.m_ProjectionOnGround.z;
    pos.x = contact.m_ProjectionOnGround.x;
    pos.y = contact.m_ProjectionOnGround.y;
    return 1;
backToPrevious:  // 0x00278a28
    pos.z = prevVec.z;
    pos.x = prevVec.x;
    pos.y = prevVec.y;
    return 0;
offDynamic:  // 0x00278eec: the line starts on the moving ground's rim (its box's xz circle) towards the position
    {
        const ICollisionMesh* mesh = static_cast<const ICollisionMesh*>(contact.m_pGround);
        const float* box = mesh->m_AABB;  // +0x18, read as +0x00 / +0x0c (x) and +0x08 / +0x14 (z)
        const float zero = 0.0f;
        float hx = (box[0] - box[3]) * 0.5f;  // TOC1 +0xa94
        const float cx = (box[0] + box[3]) * 0.5f;
        float hz = (box[2] - box[5]) * 0.5f;
        const float cz = (box[2] + box[5]) * 0.5f;

        hx = ppc::fmadds(hx, hx, zero);
        const float radius = static_cast<float>(enemy::MathSqrtf(ppc::fmadds(hz, hz, hx)));  // 0x00010690
        float dx = pos.x - cx;
        float dz = pos.z - cz;
        const float length = static_cast<float>(enemy::MathSqrtf(ppc::fmadds(dz, dz, ppc::fmadds(dx, dx, zero))));
        if (length != zero) {
            const float inv = 1.0f / length;  // TOC1 +0xa88
            dz = dz * inv;
            dx = dx * inv;
        }
        const float sz = ppc::fmadds(dz, radius, cz);
        const float sx = ppc::fmadds(radius, dx, cx);
        line.m_start.y = m_unk144;
        line.m_start.z = sz;
        line.m_start.x = sx;
        line.m_VectDir.y = pos.y - m_unk144;
        line.m_VectDir.x = pos.x - sx;
        line.m_VectDir.z = pos.z - sz;
        result = collision->ResolveSweptCylinderWalls(&line, m_pEnemyCpnt->m_MoveCpnt.m_afParams[0], ComponentHeight(),
                                                       &slide, nullptr, nullptr, 1);  // 0x0019aa68
        if (result == 1) {
            pos.z = prevVec.z;
            pos.x = prevVec.x;
            pos.y = prevVec.y;
        } else if (result < 1) {
            if (result != 0) return 1;
            Mat4_TransformPoints(mesh->GetWorldMatrix(), &pos, &contact.m_ProjectionOnGround, 1);  // vt+0x50
            return 1;
        } else {
            if (result > 3) return 1;
            const float y = slide.m_v3BouncingVector.y + pos.y;
            const float x = slide.m_v3BouncingVector.x + pos.x;
            const float z = slide.m_v3BouncingVector.z + pos.z;
            pos.y = y;
            pos.y = m_unk144;
            pos.x = x;
            pos.z = z;
        }
        // 0x00279038: the contact cleared.
        contact.m_ui8SectorNumber = 0;
        contact.m_i32FaceIndex = -1;
        contact.m_eContactStatus = 3;
        contact.m_pGround = nullptr;
        return 1;
    }
navMesh:  // 0x00278748
    pathFinding = static_cast<CKSrvPathFinding*>(g_pEngine->m_srvPathFinding);
    oldHint = static_cast<int16_t>(m_PFCpnt.m_Destination.m_i16GraphNodeIndex);
    point.m_position = pos;
    point.m_i16GraphNodeIndex = static_cast<uint16_t>(oldHint);
    if ((pathFinding->FindSectorForPoint(&point) & 0xffu) == 0) {  // 0x001e5ca0
        point.m_position = prevVec;
        if ((pathFinding->FindSectorForPoint(&point) & 0xffu) != 0) goto backToPrevious;
        m_bitArray = (m_bitArray & 0xffffffefu) | 0x10u;
        return 0;
    }
    newHint = point.m_i16GraphNodeIndex;
    if (static_cast<int16_t>(newHint) != static_cast<int16_t>(oldHint) && (m_PFCpnt.m_eState & 0x40) == 0) {
        CKPFGraphTransition* transition =
            pathFinding->GetTransitionBetween(newHint, static_cast<uint16_t>(oldHint));  // 0x001e3e28
        if (transition == nullptr) goto backToPrevious;
        if ((transition->m_baFlags & 1u) != 0) goto backToPrevious;
        if ((transition->AllowsCharacter(&m_PFCpnt.m_CharacterType) & 0xffu) == 0) goto backToPrevious;  // 0x001f0648
        if ((transition->m_baFlags & 4u) == 0) goto backToPrevious;
    }
    if ((m_bitArray & 0x80u) == 0 &&
        (pathFinding->IsPointWalkable(&point, &m_PFCpnt.m_CharacterType) & 0xffu) == 0) {  // 0x001e42d0
        // 0x00278ad4: the previous point in its own node still walkable: back there.
        point.m_position = prevVec;
        point.m_i16GraphNodeIndex = static_cast<uint16_t>(oldHint);
        if (PointInNodeBox(pathFinding, &point) &&
            (pathFinding->IsPointWalkable(&point, &m_PFCpnt.m_CharacterType) & 0xffu) != 0) {
            goto backToPrevious;
        }
        point.m_position = pos;
        point.m_i16GraphNodeIndex = newHint;
        m_PFCpnt.m_CharacterType.m_fRadius = 0.0f;
        if (!PointInNodeBox(pathFinding, &point) ||
            (pathFinding->IsPointWalkable(&point, &m_PFCpnt.m_CharacterType) & 0xffu) == 0) {
            pos.x = prevVec.x;
            pos.y = prevVec.y;
            pos.z = prevVec.z;
        }
        const float cap = g_pfGridScale.m_halfCellSize - 0.05f;  // TOC1 +0xab4 / +0xac0
        const float radius = m_pEnemyCpnt->m_MoveCpnt.m_afParams[0];
        m_PFCpnt.m_CharacterType.m_fRadius = radius >= cap ? cap : radius;
    }
    if ((m_PFCpnt.m_eState & 0x40) == 0) m_PFCpnt.m_Destination.m_i16GraphNodeIndex = point.m_i16GraphNodeIndex;
    goto ground;
}


// 0x002796e8 CKHkS08Enemy_UpdateShadowCaster (vt+0xe4): the ground under the enemy probed; on a ground that is not a
// surface for shadows (the game manager's vt+0x138) or without one, the caster is unregistered; else it is registered
// once (at the enemy's position, normal Y), then follows the contact's point, normal and height, and bit 4 of +0x1ac
// mirrors the ground's engine flag 6.
void IKHkEnemy::UpdateShadowCaster() {
    CKSrvCollision* collision = static_cast<CKSrvCollision*>(g_pEngine->m_srvCollision);
    collision->GroundProbePoints(&m_GrdContDatasIn, &m_GrdContDatasInOut, &m_v3Position.x, 1);  // 0x00196540
    CKShadowGround* caster = reinterpret_cast<CKShadowGround*>(&m_v3ShadowGroundPosition);
    bool keep = m_GrdContDatasInOut.m_pGround != nullptr;
    if (keep) {
        const CKS08GameManager* manager = static_cast<const CKS08GameManager*>(g_pEngine->m_gameManager);
        keep = (manager->GetGroundSurfaceBit(m_GrdContDatasInOut.m_pGround) & 0xffu) == 0;  // vt+0x138 0x004f88f8
    }
    if (!keep) {
        if (m_pShadowCpnt != nullptr && m_unk1ad != 0) {
            static_cast<CKSrvShadow*>(g_pEngine->m_srvShadow)->UnregisterCaster(caster, m_pShadowCpnt);  // 0x001fd6f0
        }
        return;
    }
    if (m_pShadowCpnt != nullptr && m_unk1ad == 0) {
        static_cast<CKSrvShadow*>(g_pEngine->m_srvShadow)
            ->RegisterCaster(m_pShadowCpnt, m_pKGLObject, caster, 0, nullptr, 0);  // 0x001fb6f8
        m_v3ShadowGroundPosition.x = m_v3Position.x;
        m_v3ShadowGroundPosition.z = m_v3Position.z;
        m_v3ShadowGroundPosition.y = m_v3Position.y;
        m_v3ShadowGroundNormal = kAxisY;  // TOC1 +0xa84
        m_unk1a8 = 0.0f;
    }
    if (m_GrdContDatasInOut.m_eContactStatus == 3) return;
    GroundContact_GetWorldPoint(&m_GrdContDatasInOut, &m_v3ShadowGroundPosition);   // 0x001a70e0
    GroundContact_GetWorldNormal(&m_GrdContDatasInOut, &m_v3ShadowGroundNormal);  // 0x001a71d8
    m_unk1a8 = m_GrdContDatasInOut.m_fdH;
    const ICollisionMesh* ground = static_cast<const ICollisionMesh*>(m_GrdContDatasInOut.m_pGround);
    if (((ground->m_ba16EngineFlags >> 6) & 1u) != 0) {
        m_unk1AC = static_cast<uint8_t>(m_unk1AC | 0x10u);
    } else if ((m_unk1AC & 0x10u) != 0) {
        m_unk1AC = static_cast<uint8_t>(m_unk1AC ^ 0x10u);
    }
}

// 0x00277850 CKHkS08Enemy_EnableVolume (vt+0xf0): volume `index` of +0x2c switched on in the collision service.
void IKHkEnemy::EnableVolume(int32_t index) {
    IKSerializable* volume = m_apBV[index];
    if (volume == nullptr) return;
    static_cast<CKSrvCollision*>(g_pEngine->m_srvCollision)->EnableVolume(static_cast<IKBoundingVolume*>(volume));  // 0x00192090
}

// 0x00277800 CKHkS08Enemy_DisableVolume (vt+0xf4)
void IKHkEnemy::DisableVolume(int32_t index) {
    IKSerializable* volume = m_apBV[index];
    if (volume == nullptr) return;
    static_cast<CKSrvCollision*>(g_pEngine->m_srvCollision)->DisableVolume(static_cast<IKBoundingVolume*>(volume));  // 0x001920e8
}

// 0x00277738 CKHkS08Enemy_EnableVolumeGroup (vt+0xf8): the m_aui8BoundingNumberByType[group] volumes from
// m_aui8BoundingIndexByType[group] switched on (the count is read again after each volume).
void IKHkEnemy::EnableVolumeGroup(int32_t group) {
    for (uint32_t i = 0; m_aui8BoundingNumberByType[group] > i; ++i) {
        IKSerializable* volume = m_apBV[m_aui8BoundingIndexByType[group] + i];
        if (volume == nullptr) continue;
        static_cast<CKSrvCollision*>(g_pEngine->m_srvCollision)->EnableVolume(static_cast<IKBoundingVolume*>(volume));  // 0x00192090
    }
}

// 0x00277670 CKHkS08Enemy_DisableVolumeGroup (vt+0xfc)
void IKHkEnemy::DisableVolumeGroup(int32_t group) {
    for (uint32_t i = 0; m_aui8BoundingNumberByType[group] > i; ++i) {
        IKSerializable* volume = m_apBV[m_aui8BoundingIndexByType[group] + i];
        if (volume == nullptr) continue;
        static_cast<CKSrvCollision*>(g_pEngine->m_srvCollision)->DisableVolume(static_cast<IKBoundingVolume*>(volume));  // 0x001920e8
    }
}

// 0x00276f88 CKHkS08Enemy_ClearVolumeGroupFlags (vt+0x100): `flags` cleared in the properties of the group's volumes.
void IKHkEnemy::ClearVolumeGroupFlags(int32_t group, uint16_t flags) {
    for (uint32_t i = 0; m_aui8BoundingNumberByType[group] > i; ++i) {
        IKBoundingVolume* volume = static_cast<IKBoundingVolume*>(m_apBV[m_aui8BoundingIndexByType[group] + i]);
        if (volume == nullptr) continue;
        volume->m_ui16PropertiesFlags = static_cast<uint16_t>(~flags & volume->m_ui16PropertiesFlags);
    }
}

// 0x00277008 CKHkS08Enemy_SetVolumeGroupFlags (vt+0x104)
void IKHkEnemy::SetVolumeGroupFlags(int32_t group, uint16_t flags) {
    for (uint32_t i = 0; m_aui8BoundingNumberByType[group] > i; ++i) {
        IKBoundingVolume* volume = static_cast<IKBoundingVolume*>(m_apBV[m_aui8BoundingIndexByType[group] + i]);
        if (volume == nullptr) continue;
        volume->m_ui16PropertiesFlags = static_cast<uint16_t>(flags | volume->m_ui16PropertiesFlags);
    }
}

// 0x00279998 CKHkS08Enemy_EnableCollisionSphere_maybe (vt+0x108): projectile volume `index` (taken from the collision
// service when missing) off its parent and hung by its properties' parent kind: 0 the dynamic scene root, 1 the enemy's
// node, 2 / 3 the variant's animated node / collision volume (the hot spot index), 4 the variant's hot spot; then placed
// at its local position (m_av3BVProjPos), given its radius (0.001 when not positive), owned by the enemy, its moves
// reset to the parent's world position, its owner type and property flags from the properties, and switched on.
void IKHkEnemy::EnableCollisionSphere(uint32_t index) {
    IKSerializable** slot = &m_apBVProj[index];
    if (*slot == nullptr) {
        *slot = static_cast<CKSrvCollision*>(g_pEngine->m_srvCollision)->AcquireDynSphere();  // 0x00192a70
        if (*slot == nullptr) return;
    }
    CKDynamicBoundingSphere* sphere = static_cast<CKDynamicBoundingSphere*>(m_apBVProj[index]);
    if (sphere->m_pParent != nullptr) sphere->m_pParent->RemoveChild(sphere);  // vt+0x78
    const SEnemyProjectileBoundingProperties& props = m_asProjPropeties[index];
    // The original reads the variant (GetSectorIndex's logic, inlined) before the attach and again before the position.
    auto sector = [this]() -> CKEnemySectorCpnt* {
        const uint32_t i = enemy::GroupKindFlag104(m_ui8EnemyClassType) != 0 ? 0u : enemy::SquadFightZoneIndex(m_pGroupSquad);
        return m_apEnemySectorCpnt[i];
    };
    CVector3 base{0.0f, 0.0f, 0.0f};  // DOTD: a parent kind above 4 leaves the original's stack copy uninitialised
    switch (static_cast<uint8_t>(props.m_i8ParentIndex)) {
        case 0:
            static_cast<CSGBranch*>(g_pEngine->m_dynamicSceneRoot)->AddChild(sphere);  // vt+0x70
            break;
        case 1: {
            CSGBranch* node = static_cast<CSGBranch*>(m_pKGLObject);
            node->AddChild(sphere);
            const RwV3d& at = node->m_pRwFrame->ltm.pos;
            base = CVector3{at.x, at.y, at.z};
            break;
        }
        case 2: {
            static_cast<CSGBranch*>(sector()->GetAnimatedNode(static_cast<uint8_t>(props.m_i8AttachHotSpotIndex)))->AddChild(sphere);
            const RwV3d& at = static_cast<CSGLeaf*>(sector()->GetAnimatedNode(static_cast<uint8_t>(props.m_i8AttachHotSpotIndex)))
                                  ->m_pRwFrame->ltm.pos;
            base = CVector3{at.x, at.y, at.z};
            break;
        }
        case 3: {
            static_cast<CSGBranch*>(sector()->GetCollisionVolume(static_cast<uint8_t>(props.m_i8AttachHotSpotIndex)))->AddChild(sphere);
            const RwV3d& at = static_cast<CSGLeaf*>(sector()->GetCollisionVolume(static_cast<uint8_t>(props.m_i8AttachHotSpotIndex)))
                                  ->m_pRwFrame->ltm.pos;
            base = CVector3{at.x, at.y, at.z};
            break;
        }
        case 4:
            static_cast<CSGHotSpot*>(sector()->GetHotSpot(static_cast<uint8_t>(props.m_i8AttachHotSpotIndex)))->AttachVolume(sphere);  // 0x000ce2b8
            static_cast<CSGHotSpot*>(sector()->GetHotSpot(static_cast<uint8_t>(props.m_i8AttachHotSpotIndex)))->GetWorldPosition(&base);  // 0x000ce790
            break;
        default:
            break;
    }
    RwFrame* frame = sphere->m_pRwFrame;
    const CVector3& local = m_av3BVProjPos[index];
    frame->modelling.pos.x = local.x;
    frame->modelling.pos.y = local.y;
    frame->modelling.pos.z = local.z;
    frame->modelling.flags &= 0xfffdffffu;
    RwFrame_MarkDirty(sphere->m_pRwFrame);  // 0x00010698
    const float radius = m_afBVProjRadius[index];
    sphere->m_fRadius = radius > 0.0f ? radius : 0.001f;
    sphere->m_ba8Infos = static_cast<uint8_t>(sphere->m_ba8Infos | 0x08u);
    sphere->m_ba8Infos = static_cast<uint8_t>(sphere->m_ba8Infos | 0x20u);
    sphere->m_ba8Infos = static_cast<uint8_t>(sphere->m_ba8Infos | 0x04u);
    sphere->m_pOwner = this;
    sphere->m_v3WorldMove = CVector3{0.0f, 0.0f, 0.0f};  // g_nullVector
    sphere->m_v3OldPos = base;
    sphere->m_v3LastWorldPos = base;
    sphere->m_ui16PropertiesFlags = 0;
    sphere->m_ui8OwnerType = 0;
    sphere->m_ui8OwnerType = static_cast<uint8_t>(props.m_eOwnerType);
    sphere->m_ui16PropertiesFlags = static_cast<uint16_t>(props.m_ui16Properties | sphere->m_ui16PropertiesFlags);
    sphere->m_ba8Infos = static_cast<uint8_t>((sphere->m_ba8Infos & 0x7fu) | 0x80u);
}

// 0x00277d08 CKHkS08Enemy_ReleaseDynSphere_maybe (vt+0x10c): projectile volume `index` taken off its parent node, given
// back to the collision service and forgotten.
void IKHkEnemy::ReleaseDynSphere(int32_t index) {
    IKBoundingVolume* volume = static_cast<IKBoundingVolume*>(m_apBVProj[index]);
    if (volume == nullptr) return;
    CSGBranch* parent = volume->m_pParent;
    if (parent != nullptr) parent->RemoveChild(volume);  // vt+0x78
    static_cast<CKSrvCollision*>(g_pEngine->m_srvCollision)->ReleaseDynSphere(static_cast<IKBoundingVolume*>(m_apBVProj[index]));  // 0x00191a38
    m_apBVProj[index] = nullptr;
}

// 0x00277f50 CKHkS08Enemy_ClearDynSphereFlags (vt+0x110)
void IKHkEnemy::ClearDynSphereFlags(int32_t index, uint16_t flags) {
    IKBoundingVolume* volume = static_cast<IKBoundingVolume*>(m_apBVProj[index]);
    if (volume == nullptr) return;
    volume->m_ui16PropertiesFlags = static_cast<uint16_t>(volume->m_ui16PropertiesFlags & ~flags);
}

// 0x00277dc8 CKHkS08Enemy_SetDynSphereFlags (vt+0x114)
void IKHkEnemy::SetDynSphereFlags(int32_t index, uint16_t flags) {
    IKBoundingVolume* volume = static_cast<IKBoundingVolume*>(m_apBVProj[index]);
    if (volume == nullptr) return;
    volume->m_ui16PropertiesFlags = static_cast<uint16_t>(flags | volume->m_ui16PropertiesFlags);
}

// 0x0027c7b0 CKHkS08Enemy_StartTrailRibbon_maybe (vt+0x118): trail node `index` (none running: +0x60 byte 0xff) gets its
// first ribbon not on (bit 0 of its properties) with the two given extremes, switched on with its geometry rebuilt (the
// inlined CTrailNodeFx_SetRibbonActive_maybe 0x9bdfb8), and the ribbon's number kept; no free ribbon: 0xff.
void IKHkEnemy::StartTrailRibbon(int32_t index, const void* a, const void* b) {
    if (m_unk60[index] != 0xff) return;
    CTrailNodeFx* trail = static_cast<CTrailNodeFx*>(m_apTrailNodeFx[index]);
    if (trail == nullptr) return;
    uint8_t ribbon = 0xff;
    for (uint32_t i = 0; i < trail->m_ui32NbTrail; ++i) {
        if ((trail->m_apTrailData[i]->m_ba8Properties & 1u) == 0) {
            ribbon = static_cast<uint8_t>(i);
            break;
        }
    }
    if (ribbon == 0xff) {
        m_unk60[index] = 0xff;
        return;
    }
    STrailNodeData* data = trail->m_apTrailData[ribbon];
    data->m_v3Extrem1 = *static_cast<const CVector3*>(a);
    data->m_v3Extrem2 = *static_cast<const CVector3*>(b);
    trail->SetRibbonActive(ribbon, 1, 1);  // 0x009bdfb8 (inlined in the original)
    m_unk60[index] = ribbon;
}

// 0x0027c700 CKHkS08Enemy_StopTrailRibbon_maybe (vt+0x11c): the running ribbon of trail node `index` switched off (its
// visible count set to its control points, no geometry change), and the node free again.
void IKHkEnemy::StopTrailRibbon(int32_t index) {
    const uint8_t ribbon = m_unk60[index];
    if (ribbon == 0xff) return;
    CTrailNodeFx* trail = static_cast<CTrailNodeFx*>(m_apTrailNodeFx[index]);
    if (trail == nullptr) return;
    STrailNodeData* data = trail->m_apTrailData[ribbon];
    if ((data->m_ba8Properties & 1u) != 0) {
        data->m_ba8Properties = static_cast<uint8_t>(data->m_ba8Properties & 0xfeu);
        data->m_ui8Visible = static_cast<uint8_t>(data->m_ui32NbCtrPoints);
    }
    m_unk60[index] = 0xff;
}

// 0x00277f80 CKHkS08Enemy_SetTrailRibbonEndpoints_maybe (vt+0x120): the running ribbon's two extremes.
void IKHkEnemy::SetTrailRibbonEndpoints(int32_t index, const void* a, const void* b) {
    const int8_t ribbon = static_cast<int8_t>(m_unk60[index]);
    if (ribbon == -1) return;
    STrailNodeData* data = static_cast<CTrailNodeFx*>(m_apTrailNodeFx[index])->m_apTrailData[static_cast<uint8_t>(ribbon)];
    data->m_v3Extrem1 = *static_cast<const CVector3*>(a);
    data->m_v3Extrem2 = *static_cast<const CVector3*>(b);
}

// 0x002820e8 CKHkS08Enemy_ForceState16_maybe (vt+0x124): the main state machine to state 0x16 (clock null): the old state
// left, then 0x16 entered.
void CKHkS08Enemy::ForceState16() {
    const uint8_t old = m_mainState;
    if (old != 0xff) CallMainState(old, nullptr, 2, 0x16);
    m_mainState = 0x16;
    CallMainState(0x16, nullptr, 1, old);
}

namespace {
// 0x00277088 Contact_GetOtherVolume: the contact's volume that is not `own` (the second when the first is `own`).
IKBoundingVolume* OtherVolume(IKBoundingVolume* own, ICollision* contact) {
    if (contact->GetBoundingVolume1() == own) return static_cast<IKBoundingVolume*>(contact->GetBoundingVolume2());
    return static_cast<IKBoundingVolume*>(contact->GetBoundingVolume1());
}

// The angle between two directions, each normalised when not null (the 1 / length step, TOC +0xb44), their dot
// product clamped to [-1, 1] (TOC +0xb28 / +0xb44) before TocBridge_Math_Acosf 0x98e1a0. `dotAB` picks the product's
// order (the two inlined copies differ).
float ClampedAngle(float ax, float ay, float az, float bx, float by, float bz, bool bFirst) {
    float length = std::sqrt(ppc::fmadds(az, az, ppc::fmadds(ax, ax, ay * ay)));  // 0x00010690
    if (length != 0.0f) {
        const float inverse = 1.0f / length;
        az = az * inverse;
        ax = ax * inverse;
        ay = ay * inverse;
    }
    length = std::sqrt(ppc::fmadds(bz, bz, ppc::fmadds(bx, bx, by * by)));
    if (length != 0.0f) {
        const float inverse = 1.0f / length;
        bz = bz * inverse;
        bx = bx * inverse;
        by = by * inverse;
    }
    float dot;
    if (bFirst) {
        dot = ppc::fmadds(az, bz, ppc::fmadds(ax, bx, by * ay));
    } else {
        dot = ppc::fmadds(bz, az, ppc::fmadds(ax, bx, ay * by));
    }
    if (dot <= -1.0f) {
        dot = -1.0f;
    } else if (dot >= 1.0f) {
        dot = 1.0f;
    }
    return crt::Acosf(dot);
}
}  // namespace

// 0x002824d0 CKHkS08Enemy_ProcessContacts (vt+0x134): the collision service's contacts of the enemy's volumes, by
// bounding type (+0x30 types, +0x34 counts, +0x38 first indices into +0x2c), each contact with a contact set (vt+0x08):
// type 1 (the body) is pushed out of a hero's body volume (owner type 3, properties 0x10; not a 0x2000 volume against
// a plain one) by the interpenetration (vt+0x18) x +0x254 along the normal (vt+0x1c); type 2 (the hurt volumes) takes
// the hits (ProcessDamageContact); type 3 marks +0x23a and keeps the contact point. Then the projectile spheres' contacts
// (+0x44, the kind's count) are walked (nothing kept).
void CKHkS08Enemy::ProcessContacts(IKTime* /*clock*/) {
    uint8_t canBeHit = 1;  // cleared by a hit whose damage is not held (+0x0c)
    for (uint32_t type = 0; type < m_ui8NumberOfBoundingTypes; ++type) {
        for (uint32_t index = m_aui8BoundingIndexByType[type];
             index < static_cast<uint32_t>(m_aui8BoundingIndexByType[type]) + m_aui8BoundingNumberByType[type]; ++index) {
            IKBoundingVolume* own = static_cast<IKBoundingVolume*>(m_apBV[index]);
            if (own == nullptr) continue;
            for (ICollision* contact = static_cast<ICollision*>(own->m_CollisionResList); contact != nullptr;
                 contact = contact->m_pNext) {
                if (contact->HasContactSet() == 0) continue;  // vt+0x08
                IKBoundingVolume* other = OtherVolume(own, contact);  // 0x00277088
                if (type == 2) {
                    ProcessDamageContact(contact, other, &canBeHit);
                } else if (type == 3) {
                    m_unk23a = 1;
                    const CVector3* point = contact->GetWorldContactPoint();  // vt+0x20
                    m_vLastHitPos[0] = point->x;
                    m_vLastHitPos[2] = point->z;
                    m_vLastHitPos[1] = point->y;
                } else if (type == 1) {
                    if (other->m_ui8OwnerType != 3 || (other->m_ui16PropertiesFlags & 0x10u) == 0) continue;
                    if ((other->m_ui16PropertiesFlags & 0x2000u) == 0 && (own->m_ui16PropertiesFlags & 0x2000u) != 0) continue;
                    const CVector3 zero = {0.0f, 0.0f, 0.0f};  // the zero vector 0x00c50d64 (TOC +0xb7c)
                    const CVector3* normal = contact->GetNormale12();                  // vt+0x1c
                    const float depth = contact->GetdInterpenetration() * m_unk254;   // vt+0x18
                    const float x = ppc::fmadds(depth, normal->x, zero.x);
                    const float y = ppc::fmadds(depth, normal->y, zero.y);
                    const float z = ppc::fmadds(depth, normal->z, zero.z);
                    m_v3Position.x = x + m_v3Position.x;
                    m_v3Position.y = y + m_v3Position.y;
                    m_v3Position.z = z + m_v3Position.z;
                }
            }
        }
    }
    // The projectile spheres' contacts: Contact_GetOtherVolume for each, the result dropped.
    const uint8_t spheres = GroupNbDynSpheres(static_cast<uint8_t>(m_pActiveEnemyCpnt->m_unkb8));  // vt+0x11c, the kind +0xbb
    for (uint32_t i = 0; i < spheres; ++i) {
        IKBoundingVolume* sphere = static_cast<IKBoundingVolume*>(m_apBVProj[i]);
        if (sphere == nullptr) continue;
        for (ICollision* contact = static_cast<ICollision*>(sphere->m_CollisionResList); contact != nullptr;
             contact = contact->m_pNext) {
            if (contact->HasContactSet() != 0) (void)OtherVolume(sphere, contact);
        }
    }
}

// DOTD: ProcessContacts' hurt-volume contact (0x002828f4). While the hit window is open (+0x7cd), the enemy can still be
// hit this frame and the path finding is not in a scripted mode (+0x3c bit 0x40 without +0x70 bit 0x400): a damaging
// volume (properties 0x20) of another owner. Its damage (+0x1c): a CKS08Damage as it is, any other copied into +0x8bc
// (time, kind, held byte; +0x8e2 set); "has damage" is its byte +0x0c. In state 0x1d an element damage of type 7 sets
// +0x899. With fewer than four attackers listed: an attacker already listed is skipped (unless a held damage +0x26 comes
// from a new volume, +0x8a0 / +0x8a4, or the hit has damage) - an element damage of type 7 without the held byte lets it
// through; the others' "touching" bytes follow (cleared for element damages of types 0, 10, 14). A new hook attacker is
// listed (+0x694, +0x208.., cooldown by the element type: the enemy group's +0x258 / +0x25c / +0x260, else 0.2), the
// contact point kept (+0x23c), the damage pending (+0x27c). An enemy that can block (kind +0xe8, not a type 2 damage,
// +0x354 clear, +0x718 past the kind's +0xf4, state 1, walking or a move anim 5..7) and faces the hit (the angle
// between +0x388 and its node's LTM at within +0x564) blocks with a shield (+0x524: kinds 2 / 5) or a weapon (+0x520,
// kinds 4 / 5, not an element damage): state 5 (the block count +0x72c below the kind's +0x33c, or no damage), 0x22
// (not an element damage), or a move target and state 0x17 (+0x7dd); else the hit is pending (+0x239). A hero in a
// combo seen from the front (+0x1f8 / +0x1f9, +0x6b0 past +0x220, the hero's aim against the node's at within +0x200)
// with a hit sphere within +0x204 (squared, flat) makes the enemy dodge (state 6, no pending hit). A pending hit with
// armour parts goes to them (STUB). Then a hero attacker is told the hit landed (SetHitConfirmed); a damage without the
// held byte ends the hits of this frame.
void CKHkS08Enemy::ProcessDamageContact(ICollision* contact, IKBoundingVolume* other, uint8_t* canBeHit) {
    if (m_unk7cd == 0 || *canBeHit == 0) return;
    if ((m_PFCpnt.m_eState & 0x40) != 0 && (m_PFCpnt.m_bits70 & 0x400u) == 0) return;
    if ((other->m_ui16PropertiesFlags & 0x20u) == 0) return;
    if (other->m_pOwner == this) return;
    CKS08Damage* damage = nullptr;
    uint8_t hasDamage = 0;
    if (other->m_unk1c != nullptr) {
        if (other->m_unk1c->IsKindOfClass(0x970c) != 0) {  // vt+0x08
            damage = static_cast<CKS08Damage*>(other->m_unk1c);
        } else {
            const CKDamage* source = static_cast<const CKDamage*>(other->m_unk1c);
            const CKS08Damage fresh;  // 0x004ebc70; CKS08Damage_Assign 0x4eba18, the destructor 0x4ebb00
            m_damage8BC.m_bContinuous = fresh.m_bContinuous;
            m_damage8BC.m_fAmount = fresh.m_fAmount;
            m_damage8BC.m_i32DamageKind = fresh.m_i32DamageKind;
            m_damage8BC.m_unk26 = fresh.m_unk26;
            m_damage8BC.m_fKnockbackForce = fresh.m_fKnockbackForce;
            m_damage8BC.m_fKnockbackTime = fresh.m_fKnockbackTime;
            m_damage8BC.m_unk18 = fresh.m_unk18;
            m_damage8BC.m_unk1c = fresh.m_unk1c;
            m_damage8BC.m_ui32DamageType = fresh.m_ui32DamageType;
            m_damage8BC.m_unk24 = fresh.m_unk24;
            m_damage8BC.m_unk25 = fresh.m_unk25;
            m_damage8BC.m_i32DamageKind = source->m_i32DamageKind;
            m_damage8BC.m_fAmount = source->m_fAmount;
            m_damage8BC.m_bContinuous = source->m_bContinuous;
            m_damage8BC.m_unk26 = 1;  // +0x8e2
            damage = &m_damage8BC;
        }
        if (damage != nullptr && damage->m_bContinuous != 0) hasDamage = 1;
    }
    auto element = [](CKS08Damage* d) -> CKS08ElementDamage* {
        return d != nullptr && d->IsKindOfClass(0x99cc) != 0 ? static_cast<CKS08ElementDamage*>(d) : nullptr;
    };
    if (m_mainState == 0x1d && element(damage) != nullptr && damage->m_ui32DamageType == 7) m_unk899 = 1;
    const uint8_t listed = m_ui8HitByCount;
    if (listed > 3) return;
    if (listed != 0) {
        uint8_t skip = 0;
        for (uint32_t i = 0; i < m_ui8HitByCount; ++i) {
            SEnemyHitAttacker& entry = m_aRecentAttackers[i];
            if (entry.m_pAttacker == other->m_pOwner) {
                if (m_pPendingDamage != nullptr && m_pPendingDamage->m_unk26 != 0) {
                    if (m_unk8a0 == other) {
                        skip = 1;
                    } else {
                        m_unk8a0 = other;
                        m_unk8a4 = 0.5f;  // TOC +0xb68
                    }
                } else if (hasDamage == 0) {
                    skip = 1;
                }
                if (element(damage) != nullptr && damage->m_ui32DamageType == 7 && damage->m_bContinuous == 0) skip = 0;
            }
            if (entry.m_pAttacker == nullptr) continue;
            const CKS08ElementDamage* elemental = element(damage);
            if (elemental != nullptr &&
                (elemental->m_i32AbilityId == 0 || elemental->m_i32AbilityId == 10 || elemental->m_i32AbilityId == 14)) {
                entry.m_bTouching = 0;
            } else {
                entry.m_bTouching = 1;
            }
        }
        if (skip != 0) return;
    }
    // 0x00282b30: a new attacker.
    IKSerializable* attacker = other->m_pOwner;
    if (attacker->IsKindOfClass(2) == 0) return;  // a hook
    // (the distance to the volume's LTM position is computed twice, Math_Sqrtf, and dropped)
    const uint32_t moveAnim = m_pActiveEnemyCpnt->m_MoveCpnt.m_eMvtAnim;  // +0x84
    m_pLastAttacker = attacker;
    SEnemyHitAttacker& added = m_aRecentAttackers[m_ui8HitByCount];
    added.m_pAttacker = attacker;
    added.m_bTouching = 1;
    if (damage != nullptr) {
        const CKS08ElementDamage* elemental = element(damage);
        CKGrpS08Enemy* group = static_cast<CKGrpS08Enemy*>(EnemyGroup());  // 0x00276f58
        if (elemental != nullptr && elemental->m_i32AbilityId == 0) {
            added.m_fCooldown = group->m_unk238[8];   // +0x258
        } else if (elemental != nullptr && elemental->m_i32AbilityId == 10) {
            added.m_fCooldown = group->m_unk238[9];   // +0x25c
        } else if (elemental != nullptr && elemental->m_i32AbilityId == 14) {
            added.m_fCooldown = group->m_unk238[10];  // +0x260
        } else {
            added.m_fCooldown = 0.2f;  // TOC +0xbb8
        }
    }
    m_ui8HitByCount = static_cast<uint8_t>(m_ui8HitByCount + 1);
    const CVector3* point = contact->GetWorldContactPoint();  // vt+0x20
    m_vLastHitPos[0] = point->x;
    m_vLastHitPos[1] = point->y;
    m_vLastHitPos[2] = point->z;
    m_pPendingDamage = damage;
    const CKS08EnemyCpnt* cfg = m_pActiveEnemyCpnt;
    bool pending = true;
    bool blockChecked = false;
    if (cfg->m_unke8 != 0 && damage != nullptr && damage->m_i32DamageKind != 2 && m_unk354 == 0 && m_unk718 >= cfg->m_unkf4 &&
        m_mainState == 1 && (moveAnim <= 2 || moveAnim == 5 || moveAnim == 6 || moveAnim == 7)) {
        const RwFrame* frame = static_cast<CSGMovable*>(m_pKGLObject)->m_pRwFrame;
        const float angle = ClampedAngle(m_unk388, m_unk38c, m_unk390, frame->ltm.at.x, frame->ltm.at.y,
                                         frame->ltm.at.z, true);
        if (cfg->m_unk564 >= angle) {
            const uint8_t kind = m_ui8EnemyClassType;
            bool block = false;
            if (kind == 2) {
                block = m_pHeldShield != nullptr;
            } else if (kind == 5 && m_pHeldShield != nullptr) {
                block = true;
            } else if (kind == 4 || kind == 5) {
                block = m_pHeldWeapon != nullptr && m_pPendingDamage != nullptr && element(m_pPendingDamage) == nullptr;
            }
            if (block && m_mainState != 0x22 && m_mainState != 5) {
                blockChecked = true;
                pending = false;
                if (m_unk72c + 1u < static_cast<uint32_t>(m_pActiveEnemyCpnt->m_unk33c) || m_pPendingDamage == nullptr) {
                    SwitchMainState(5, nullptr);
                } else if (element(m_pPendingDamage) == nullptr) {
                    SwitchMainState(0x22, nullptr);
                } else {
                    m_unk7dd = 1;
                    const CVector3 target = ChooseMoveTarget();  // 0x002808e8
                    m_unk85c = target.x;
                    m_unk864 = target.z;
                    m_unk860 = target.y;
                    if (!(target.x == 0.0f && target.y == 0.0f && target.z == 0.0f)) SwitchMainState(0x17, nullptr);
                }
            }
        }
    }
    (void)blockChecked;
    if (pending) m_bPendingHit = 1;
    // 0x002830f0: the dodge.
    cfg = m_pActiveEnemyCpnt;
    IKSerializable* hitter = static_cast<IKSerializable*>(m_pLastAttacker);
    if ((cfg->m_unk1f8 != 0 || cfg->m_unk1f9 != 0) && m_unk6b0 >= cfg->m_unk220 && hitter != nullptr &&
        hitter->IsKindOfClass(0x25c2) != 0) {
        CKHkS08Hero* hero = static_cast<CKHkS08Hero*>(hitter);
        if (hero->IsInCombo() != 0) {  // 0x0032a698
            const CVector3 aim = hero->GetAimDirection();  // 0x0032a708
            const RwFrame* frame = static_cast<CSGMovable*>(m_pKGLObject)->m_pRwFrame;
            const float angle = ClampedAngle(aim.x, aim.y, aim.z, frame->modelling.at.x, frame->modelling.at.y,
                                             frame->modelling.at.z, false);
            if (cfg->m_unk200 >= angle && m_mainState == 1) {
                uint32_t count = hero->m_ui32ActiveHitSphereCount;  // CKHkS08Hero_GetActiveHitSpheres 0x329de0
                if (count > 4) count = 4;
                for (uint32_t i = 0; i < count; ++i) {
                    const RwFrame* sphere = static_cast<CSGMovable*>(hero->m_apActiveHitSpheres[i])->m_pRwFrame;
                    const float dz = sphere->ltm.pos.z - m_v3Position.z;
                    const float dx = sphere->ltm.pos.x - m_v3Position.x;
                    if (ppc::fmadds(dx, dx, dz * dz) <= m_pActiveEnemyCpnt->m_unk204) {
                        SwitchMainState(6, nullptr);
                        m_bPendingHit = 0;
                    }
                }
            }
        }
    }
    // 0x00283158
    if (m_bPendingHit != 0) {
        if (m_pPendingDamage == nullptr) {
            m_bPendingHit = 0;
            return;
        }
        if (m_pLastAttacker == nullptr) return;
        ApplyHitToArmourParts(other);

    }
    // 0x00283440
    if (m_pPendingDamage == nullptr) {
        m_bPendingHit = 0;
        return;
    }
    if (hitter == nullptr || hitter->IsKindOfClass(0x25c2) == 0) return;
    static_cast<CKHkS08Hero*>(hitter)->SetHitConfirmed(1);  // 0x00329f00
    if (m_pPendingDamage->m_bContinuous == 0) *canBeHit = 0;
}

namespace {
// The pool (CKS08EnemyElementPool) an armour part came from, null when it has none.
CKS08EnemyElementPool* PartPool(const CKS08EnemyElement* part) { return static_cast<CKS08EnemyElementPool*>(part->m_pPool58); }
// An armour part type that takes element damages (0..7; 8 and the negative ones take everything plainly).
bool ElementalPart(int32_t type) { return !(type < 0) && type != 8; }

// 0x0026b9a8 EnemyArmorPart_ApplyDamage: the part's health (+0x44) loses the damage (+0x04; times `dt` for a lasting
// damage, +0x0c), scaled by the pool's resistance (+0x1c) unless the part is plain or the damage is an element damage of
// the part's type.
void ApplyArmourPartDamage(float dt, CKS08EnemyElement* part, const CKS08Damage* damage) {
    const CKS08EnemyElementPool* pool = PartPool(part);
    if (pool == nullptr) return;
    bool scaled = ElementalPart(pool->m_unk14);
    if (scaled && const_cast<CKS08Damage*>(damage)->IsKindOfClass(0x99cc) != 0 &&  // vt+0x08
        pool->m_unk14 == static_cast<int32_t>(damage->m_ui32DamageType)) {
        scaled = false;
    }
    if (!scaled) {
        part->m_unk44 = damage->m_bContinuous != 0 ? part->m_unk44 - dt * damage->m_fAmount : part->m_unk44 - damage->m_fAmount;
        return;
    }
    if (damage->m_bContinuous != 0) {
        part->m_unk44 = part->m_unk44 - dt * (damage->m_fAmount * pool->m_unk1c);
    } else {
        part->m_unk44 = part->m_unk44 - damage->m_fAmount * pool->m_unk1c;
    }
}
}  // namespace

// DOTD: ProcessContacts' armour (0x0028317c). The hit point: a golem damage's +0x28 (+0x89c the volume when it has
// none: the volume's position), else the attacker's node. The part that takes the damage: the first active part of an
// element type (0..7), else the nearest active one to the contact point +0x23c. That first elemental part ends the
// pending hit (+0x239) unless the damage is an element damage of its type; a damage without the lasting byte, or with
// the explosion cooldown +0x8b8 over, also sets off the armour explosion (STUB) and restarts the cooldown (the group's
// +0x278). Then the part takes the damage (ApplyArmourPartDamage) and every active part without health breaks
// (BreakArmourPart) and leaves +0x514.
void CKHkS08Enemy::ApplyHitToArmourParts(IKBoundingVolume* other) {
    const uint32_t count = m_unk514.m_ui32NbUsedElt;
    CVector3 point;
    if (m_pPendingDamage->IsKindOfClass(0xad4c) != 0) {  // CKS08GolemDamage
        const auto* golem = static_cast<const CKS08GolemDamage*>(m_pPendingDamage);
        const CVector3* at;
        if (golem->m_unk28 == nullptr) {
            m_unk89c = other;
            at = reinterpret_cast<const CVector3*>(&other->m_pRwFrame->ltm.pos);  // +0x80
        } else {
            at = reinterpret_cast<const CVector3*>(reinterpret_cast<const uint8_t*>(golem->m_unk28) + 4);
        }
        point = *at;
    } else {
        point = *reinterpret_cast<const CVector3*>(
            &static_cast<CSGMovable*>(static_cast<IKHook*>(m_pLastAttacker)->m_pKGLObject)->m_pRwFrame->ltm.pos);
    }
    if (count == 0) return;
    auto* parts = reinterpret_cast<CKS08EnemyElement**>(m_unk514.m_pBlock);
    float best = 3.4028235e+38f;  // 0x00c4acb8 +0x28 (FLT_MAX)
    int32_t target = -1;
    for (uint32_t i = 0; i < count; ++i) {
        const CKS08EnemyElement* part = parts[i];
        if (part == nullptr || PartPool(part) == nullptr || PartPool(part)->m_unk10 == 0) continue;
        const RwV3d& at = static_cast<CSGMovable*>(part->m_pNode)->m_pRwFrame->ltm.pos;
        const float dy = at.y - m_vLastHitPos[1];
        const float dx = at.x - m_vLastHitPos[0];
        const float dz = at.z - m_vLastHitPos[2];
        const float distance = ppc::fmadds(dz, dz, ppc::fmadds(dx, dx, dy * dy));
        if (!(distance >= best)) {  // bge
            best = distance;
            target = static_cast<int32_t>(i);
        }
    }
    for (uint32_t i = 0; i < count; ++i) {
        const CKS08EnemyElement* part = parts[i];
        if (part == nullptr || PartPool(part) == nullptr) continue;
        const int32_t type = PartPool(part)->m_unk14;
        if (!ElementalPart(type)) continue;
        const bool matching = m_pPendingDamage->IsKindOfClass(0x99cc) != 0 && static_cast<int32_t>(m_pPendingDamage->m_ui32DamageType) == type;
        if (!matching) {
            if (m_pPendingDamage->m_bContinuous == 0 || m_unk8b8 <= 0.0f) {  // cror lt / eq
                // STUB(C2.8: armour): CKS08GameManager_SpawnExplosionFx 0x4fbd70 (this, 0, the contact point).
                DOTD_STUB_ONCE("CKHkS08Enemy_ProcessContacts: the armour explosion (C2.8)");
                m_unk8b8 = static_cast<CKGrpS08Enemy*>(enemy::EnemyGroup())->m_unk268[4];  // +0x278
            }
            m_bPendingHit = 0;
        }
        target = static_cast<int32_t>(i);
        break;
    }
    if (target >= 0) ApplyArmourPartDamage(m_fScaledDt, parts[target], m_pPendingDamage);  // 0x0026b9a8
    for (uint32_t i = 0; i < count; ++i) {
        CKS08EnemyElement* part = parts[i];
        if (part == nullptr || PartPool(part) == nullptr) continue;
        if (!(part->m_unk44 <= 0.0f) || PartPool(part)->m_unk10 == 0) continue;  // cror lt / eq
        BreakArmourPart(part, i, &point);  // 0x0027ed08
        parts[i] = nullptr;
    }
}

// 0x0028a6e0 CKHkS08Enemy_ReceiveDamage: a hit from `source` (+0x694) with `damage` pending (+0x27c, +0x239); the hit
// position (+0x23c) is the sector's hot spot 0. The hit point: a golem damage's +0x28 object (+0x04), else the source's
// node. The first active part of an element type (0..7) takes the damage (ApplyArmourPartDamage), after the armour
// explosion (STUB) and its cooldown restart (+0x8b8, the group's +0x278) for a damage not of its element that has no
// lasting byte or meets an expired cooldown; then every active part without health that breaks (pool +0x10;
// BreakArmourPart) leaves +0x514.
void CKHkS08Enemy::ReceiveDamage(IKSerializable* damage, IKSerializable* source) {
    m_pLastAttacker = source;
    m_bPendingHit = 1;
    m_pPendingDamage = static_cast<CKS08Damage*>(damage);
    CVector3 hit;
    static_cast<CSGHotSpot*>(m_apEnemySectorCpnt[GetSectorIndex()]->GetHotSpot(0))->GetWorldPosition(&hit);  // 0x002b31e0, 0x000ce790
    m_vLastHitPos[0] = hit.x;
    m_vLastHitPos[1] = hit.y;
    m_vLastHitPos[2] = hit.z;
    CVector3 point;
    const CKS08GolemDamage* golem =
        m_pPendingDamage->IsKindOfClass(0xad4c) != 0 ? static_cast<const CKS08GolemDamage*>(static_cast<CKDamage*>(m_pPendingDamage)) : nullptr;
    if (golem != nullptr && golem->m_unk28 != nullptr) {
        point = *reinterpret_cast<const CVector3*>(reinterpret_cast<const uint8_t*>(golem->m_unk28) + 4);
    } else {
        point = *reinterpret_cast<const CVector3*>(
            &static_cast<CSGMovable*>(static_cast<IKHook*>(source)->m_pKGLObject)->m_pRwFrame->ltm.pos);
    }
    const uint32_t count = m_unk514.m_ui32NbUsedElt;
    if (count == 0) return;
    auto* parts = reinterpret_cast<CKS08EnemyElement**>(m_unk514.m_pBlock);
    for (uint32_t i = 0; i < count; ++i) {
        const CKS08EnemyElement* part = parts[i];
        if (part == nullptr || PartPool(part) == nullptr) continue;
        const int32_t type = PartPool(part)->m_unk14;
        if (!ElementalPart(type)) continue;
        const bool matching = m_pPendingDamage->IsKindOfClass(0x99cc) != 0 && m_pPendingDamage->IsKindOfClass(0x99cc) != 0 &&
                              static_cast<int32_t>(m_pPendingDamage->m_ui32DamageType) == type;  // the original tests the class twice
        if (!matching && (m_pPendingDamage->m_bContinuous == 0 || m_unk8b8 <= 0.0f)) {  // cror lt / eq
            static_cast<CKS08GameManager*>(g_pEngine->m_gameManager)
                ->SpawnExplosionFx(this, 0, reinterpret_cast<const CVector3*>(m_vLastHitPos));  // 0x004fbd70, the hit position
            m_unk8b8 = static_cast<CKGrpS08Enemy*>(enemy::EnemyGroup())->m_unk268[4];  // +0x278
        }
        ApplyArmourPartDamage(m_fScaledDt, parts[i], m_pPendingDamage);  // 0x0026b9a8
        break;
    }
    for (uint32_t i = 0; i < count; ++i) {
        CKS08EnemyElement* part = parts[i];
        if (part == nullptr || PartPool(part) == nullptr) continue;
        if (!(part->m_unk44 <= 0.0f) || PartPool(part)->m_unk10 == 0) continue;  // cror lt / eq
        BreakArmourPart(part, i, &point);  // 0x0027ed08
        parts[i] = nullptr;
    }
}

// 0x0027ed08 CKHkS08Enemy_BreakArmourPart. An element part (pool type 0..7) under a current camera first turns the
// group's scripted camera (+0x264) to it (STUB(C2.8: camera): ScriptedCameraHandle_TryActivate_maybe 0x165eb8 with the
// camera's position, the direction to the node, 1.0 and the group's +0x270).
void CKHkS08Enemy::BreakArmourPart(CKS08EnemyElement* part, uint32_t /*index*/, const CVector3* hitPoint) {
    if (part == nullptr) return;
    CSGLeaf* node = static_cast<CSGLeaf*>(part->m_pNode);
    if (node->m_pParent != nullptr) {
        node->SetLocalMatrix(&node->m_pRwFrame->ltm);  // 0x000d0be8
        node->m_pParent->RemoveChild(node);            // vt+0x78
        static_cast<CSGBranch*>(g_pEngine->m_dynamicSceneRoot)->AddChild(node);  // vt+0x70
        part->LaunchFromHit(m_pPendingDamage, hitPoint, m_pActiveEnemyCpnt->m_vUnk128.m_pBlock[0x1b]);  // 0x0026c408
    }
    static_cast<CKS08AccessoryManager*>(static_cast<CKGrpS08Enemy*>(enemy::EnemyGroup())->m_pAccessoryManager)
        ->AddActiveItem(part);  // 0x002c75f0
    const int32_t type = PartPool(part)->m_unk14;
    const auto at = [part]() {
        return reinterpret_cast<const CVector3*>(&static_cast<CSGMovable*>(part->m_pNode)->m_pRwFrame->ltm.pos);
    };
    if (type < 0 || type == 8) {
        SpawnHitFxAt(0x1c, at());  // 0x0028c590
        return;
    }
    if (static_cast<CKSrvCamera*>(g_pEngine->m_srvCamera)->m_pCurrentCamera != nullptr) {
        DOTD_STUB_ONCE("CKHkS08Enemy_BreakArmourPart: ScriptedCameraHandle_TryActivate 0x165eb8 (C2.8)");
    }
    SpawnHitFxAt(0x22, at());
}

// 0x0027d9b8 CKHkS08Enemy_UpdateAttackerHitCooldowns_maybe (vt+0x138): from the newest attacker down, a cooldown above 0
// counts down while no held damage is pending (the pending damage's +0x0c); an expired one (or any while the damage is
// held) clears its "touching" byte, and an attacker no longer touching is taken out of the list.
void CKHkS08Enemy::UpdateAttackerHitCooldowns(IKTime* clock) {
    uint8_t i = static_cast<uint8_t>(m_ui8HitByCount - 1);
    while (i != 0xff) {
        SEnemyHitAttacker& entry = m_aRecentAttackers[i];
        const float cooldown = entry.m_fCooldown;
        if (!(cooldown <= 0.0f) && (m_pPendingDamage == nullptr || m_pPendingDamage->m_bContinuous == 0)) {
            entry.m_fCooldown = cooldown - clock->m_afDeltaTime[0];
        } else if (entry.m_bTouching != 0 && (m_pPendingDamage == nullptr || m_pPendingDamage->m_bContinuous == 0)) {
            entry.m_bTouching = 0;
        } else {
            const uint8_t count = m_ui8HitByCount;
            for (uint32_t j = static_cast<uint32_t>(i) + 1; j < count; ++j) {
                m_aRecentAttackers[j - 1].m_pAttacker = m_aRecentAttackers[j].m_pAttacker;
                m_aRecentAttackers[j - 1].m_bTouching = m_aRecentAttackers[j].m_bTouching;
                m_aRecentAttackers[j - 1].m_fCooldown = m_aRecentAttackers[j].m_fCooldown;
            }
            m_ui8HitByCount = static_cast<uint8_t>(count - 1);
        }
        i = static_cast<uint8_t>(i - 1);
    }
}

namespace {
// 0x0025ab50 CKGrpSquad_GetFightZone: the squad's parent group (+0x1c).
CKGrpFightZone* SquadZone(IKSerializable* squad) {
    return static_cast<CKGrpFightZone*>(static_cast<CKGrpSquad*>(squad)->m_pParent);
}
}  // namespace

// DOTD: the inlined test of ResolveGroundAndApplyTransform: a hero holds the enemy with the wind beam (+0x294 a hero,
// CKHkS08Hero_IsUsingWindBeam 0x32a7a8, its grab target this one).
bool CKHkS08Enemy::IsHeldByWindBeam() {
    IKSerializable* holder = m_pGrabbingHero;
    if (holder == nullptr || holder->IsKindOfClass(0x25c2) == 0) return false;  // vt+0x08
    CKHkS08Hero* hero = static_cast<CKHkS08Hero*>(holder);
    if (hero->IsUsingWindBeam() == 0) return false;
    return hero->GetGrabTarget() == this;  // 0x00329df8
}

// DOTD: the inlined code of ResolveGroundAndApplyTransform that keeps the last safe point (+0x8e4): the point's ground
// (probed into the enemy's contact pair) neither a slide (0x200) nor flag 1 and out of reach (status 0 or above 3), the
// fight zone's detector group (squad +0x1c -> +0x30, vt+0xc4) holding it, the point in its graph node's box and walkable
// there, and the path finding not in mode 0x40 (+0x3c).
void CKHkS08Enemy::RememberSafePoint(const CVector3& point) {
    CKSrvCollision* collision = static_cast<CKSrvCollision*>(g_pEngine->m_srvCollision);
    collision->GroundProbePoints(&m_GrdContDatasIn, &m_GrdContDatasInOut, &point.x, 1);  // 0x00196540
    const bool inReach = m_GrdContDatasInOut.m_eContactStatus - 1u <= 2u;
    const ICollisionMesh* ground = static_cast<const ICollisionMesh*>(m_GrdContDatasInOut.m_pGround);
    if (ground == nullptr || (ground->m_ui16PropertiesFlags & 0x200u) != 0 || (ground->m_ui16PropertiesFlags & 1u) != 0) {
        return;
    }
    if (inReach) return;
    const CKHkDetectorGroup* detectors = static_cast<const CKHkDetectorGroup*>(SquadZone(m_pGroupSquad)->m_pUnk30);
    if (detectors->IsTriggered(&point.x) == 0) return;  // vt+0xc4
    CKSrvPathFinding* pathFinding = static_cast<CKSrvPathFinding*>(g_pEngine->m_srvPathFinding);
    CPFPoint at;
    at.m_position = point;
    at.m_i16GraphNodeIndex = m_PFCpnt.m_Destination.m_i16GraphNodeIndex;
    pathFinding->FindSectorForPoint(&at);  // 0x001e5ca0 (the result is not used)
    if (!PointInNodeBox(pathFinding, &at)) return;
    if ((pathFinding->IsPointWalkable(&at, &m_PFCpnt.m_CharacterType) & 0xffu) == 0) return;  // 0x001e42d0
    if ((m_PFCpnt.m_eState & 0x40) != 0) return;
    m_unk8e4 = point.x;
    m_unk8ec = point.z;
    m_unk8e8 = point.y;
}

// 0x00280190 CKHkS08Enemy_PickAttackSpotNearHero_maybe: an enemy outside its fight zone's detectors keeps +0x1c4; one
// without a current attack (+0x32c past the kind's +0x11c list) gets the null vector. Else the camera's flat view
// (the real z axis, +0x5c8) turned about y by a random angle (one draw for the side: below half the angle is negative,
// one draw for the size, up to the kind's +0x1c4 degrees) at the attack's distance (+0x0c) plus the kind's +0x1bc from a
// random hero (a third draw). The spot must be inside the detectors, on a reachable ground that is neither out of reach
// (status 2 / 3) nor flag 0x400, in its graph node's box and walkable; when no sector route joins it to the enemy, the
// enemy's own point must not be inside its node and walkable; the enemy's ground must not slide (0x200) and no active
// enemy (this one too) may stand within the two radii (x / z). Any failure: the null vector.
CVector3 CKHkS08Enemy::PickAttackSpotNearHero() {
    const CVector3 kNull = {0.0f, 0.0f, 0.0f};  // 0x00c50d64 (TOC +0xb7c)
    const CKHkDetectorGroup* detectors = static_cast<const CKHkDetectorGroup*>(SquadZone(m_pGroupSquad)->m_pUnk30);
    const CKSrvCamera* camera = static_cast<const CKSrvCamera*>(g_pEngine->m_srvCamera);
    float viewZ = camera->m_v3RealAxisZ.z;
    float viewX = camera->m_v3RealAxisZ.x;
    if (detectors->IsTriggered(&m_v3Position.x) == 0) return CVector3{m_unk1c4, m_unk1c8, m_unk1cc};  // vt+0xc4
    const CKS08EnemyCpnt* kind = m_pActiveEnemyCpnt;
    if (!(kind->m_vUnk11c.m_ui32NbUsedElt > m_unk32c)) return kNull;
    const float zero = 0.0f;  // TOC +0xaf4
    const float reach = kind->m_unk1bc;
    const float distance = static_cast<const CKS08EnemyAttack*>(kind->m_vUnk11c.m_pBlock[m_unk32c])->m_unk0c;
    float viewY = zero;
    const float length = static_cast<float>(enemy::MathSqrtf(ppc::fmadds(viewZ, viewZ, ppc::fmadds(viewX, viewX, zero))));
    if (length != zero) {
        const float inverse = 1.0f / length;  // TOC +0xb44
        viewZ = viewZ * inverse;
        viewX = viewX * inverse;
        viewY = inverse * zero;
    }
    float angle;
    const float side = static_cast<float>(static_cast<uint32_t>(Rand_Int()) & 0xffffu) / 65535.0f;  // 0x00011500, TOC +0xb64
    if (side <= 0.5f) {  // TOC +0xb68
        angle = static_cast<float>(static_cast<uint32_t>(Rand_Int()) & 0xffffu) / -65535.0f * m_pActiveEnemyCpnt->m_unk1c4;  // +0xb70
    } else {
        angle = static_cast<float>(static_cast<uint32_t>(Rand_Int()) & 0xffffu) / 65535.0f * m_pActiveEnemyCpnt->m_unk1c4;
    }
    CMatrix34 turn;
    std::memset(&turn, 0, sizeof(turn));
    turn.m_at = CVector3{viewX, viewY, viewZ};
    Mat4_RotateInPlace(&turn, &kAxisY, angle * 0.017453291f * 57.29578f);  // 0x00240498, TOC +0xb78 / +0xb14 / +0xb10
    const CVector3 direction = turn.m_at;
    IKGrpHero* heroes = static_cast<IKGrpHero*>(enemy::HeroGroup());  // 0x00276f70
    const uint32_t count = heroes->GetHeroCount();                      // 0x002ca038 (vt+0xf4)
    if ((count & 0xffu) == 0) return kNull;
    const float away = distance + reach;
    const uint32_t pick = static_cast<uint32_t>(Rand_Int()) & 0xffffu;
    CKHkS08Hero* hero = static_cast<CKHkS08Hero*>(
        static_cast<IKGrpHero*>(enemy::HeroGroup())->m_apHeros[((count & 0xffu) * pick >> 16) & 0xffu]);  // 0x002ca080
    const float* at = hero->GetPositionPtr();  // 0x00361968
    CVector3 spot;
    spot.x = ppc::fmadds(away, direction.x, at[0]);
    spot.z = ppc::fmadds(away, direction.z, at[2]);
    spot.y = ppc::fmadds(away, direction.y, at[1]);
    if (static_cast<const CKHkDetectorGroup*>(SquadZone(m_pGroupSquad)->m_pUnk30)->IsTriggered(&spot.x) == 0) return kNull;
    CKSrvCollision* collision = static_cast<CKSrvCollision*>(g_pEngine->m_srvCollision);
    collision->GroundProbePoints(&m_GrdContDatasIn, &m_GrdContDatasInOut, &spot.x, 1);  // 0x00196540
    if (m_GrdContDatasInOut.m_eContactStatus - 2u <= 1u) return kNull;
    if ((static_cast<const ICollisionMesh*>(m_GrdContDatasInOut.m_pGround)->m_ui16PropertiesFlags & 0x400u) != 0) return kNull;
    CKSrvPathFinding* pathFinding = static_cast<CKSrvPathFinding*>(g_pEngine->m_srvPathFinding);
    CPFPoint own;
    own.m_i16GraphNodeIndex = 0xffff;
    own.m_position = m_v3Position;
    own.m_i16GraphNodeIndex = m_PFCpnt.m_Destination.m_i16GraphNodeIndex;
    pathFinding->FindSectorForPoint(&own);  // 0x001e5ca0
    CPFPoint target;
    target.m_i16GraphNodeIndex = 0xffff;
    target.m_position = spot;
    target.m_i16GraphNodeIndex = m_PFCpnt.m_Destination.m_i16GraphNodeIndex;
    pathFinding->FindSectorForPoint(&target);
    if (!PointInNodeBox(pathFinding, &target)) return kNull;
    if ((pathFinding->IsPointWalkable(&target, &m_PFCpnt.m_CharacterType) & 0xffu) == 0) return kNull;  // 0x001e42d0
    if (pathFinding->HasSectorRoute(&own, &target, &m_PFCpnt.m_CharacterType, nullptr) == 0 &&  // 0x001e9198
        PointInNodeBox(pathFinding, &own) &&
        (pathFinding->IsPointWalkable(&own, &m_PFCpnt.m_CharacterType) & 0xffu) != 0) {
        return kNull;
    }
    const ICollisionMesh* ground = static_cast<const ICollisionMesh*>(m_GrdContDatasInOut.m_pGround);
    if (ground != nullptr && (ground->m_ui16PropertiesFlags & 0x200u) != 0) return kNull;
    const IKGrpEnemy* group = static_cast<const IKGrpEnemy*>(enemy::EnemyGroup());  // 0x00276f58
    const uint32_t active = group->m_ui32NbActiveEnemies;
    const float radius = m_pActiveEnemyCpnt->m_MoveCpnt.m_afParams[0];  // +0x0c
    for (uint32_t i = 0; i < active; ++i) {
        const CKHkS08Enemy* other = static_cast<const CKHkS08Enemy*>(group->m_apActiveEnemies[i]);
        const float dx = spot.x - other->m_v3Position.x;
        const float dz = spot.z - other->m_v3Position.z;
        const float both = radius + other->m_pEnemyCpnt->m_MoveCpnt.m_afParams[0];
        const float limit = both * both;
        if (i == 0) {
            if (limit > ppc::fmadds(dz, dz, dx * dx)) return kNull;  // bgt
        } else if (!(ppc::fmadds(dx, dx, dz * dz) >= limit)) {     // bge
            return kNull;
        }
    }
    return spot;
}

// 0x002808e8 CKHkS08Enemy_ChooseMoveTarget_maybe: where to go (the null vector: nowhere). A path walking with its waypoint
// classified (+0x3c 0x40) and neither flag +0x70 0x400 nor the portal action bit 0: the waypoint. +0x7f9 (a weapon to
// fetch): a spot near a hero, else at any angle, else the spawn point +0x1c4. +0x7dd: a spot along the target's aim,
// else near a hero at any angle. +0x86f: a spot near a hero, else the spawn point. Else a spot near a hero, unless it is
// within the kind's +0x54c (squared, flat) of the enemy while the enemy is inside its zone's detectors.
CVector3 CKHkS08Enemy::ChooseMoveTarget() {
    const CVector3 kNull = {0.0f, 0.0f, 0.0f};  // 0x00c50d64 (TOC +0xb7c)
    auto isNull = [&](const CVector3& v) { return v.x == kNull.x && v.y == kNull.y && v.z == kNull.z; };
    const CVector3 spawn = {m_unk1c4, m_unk1c8, m_unk1cc};
    if ((m_PFCpnt.m_eState & 0x40) != 0 && (m_PFCpnt.m_bits70 & 0x400u) == 0 && (m_PFCpnt.m_ui32Action & 1u) == 0) {
        return m_PFCpnt.m_vCurrentTarget;
    }
    if (m_unk7f9 != 0) {
        CVector3 spot = PickAttackSpotNearHero();  // 0x00280190
        if (isNull(spot)) spot = PickAttackSpotNearHeroAnyAngle();  // 0x0027e520
        return isNull(spot) ? spawn : spot;
    }
    if (m_unk7dd != 0) {
        const CVector3 spot = PickSpotAlongTargetAim();  // 0x0027d208
        return isNull(spot) ? PickAttackSpotNearHeroAnyAngle() : spot;
    }
    if (m_unk86f != 0) {
        const CVector3 spot = PickAttackSpotNearHero();
        return isNull(spot) ? spawn : spot;
    }
    const CVector3 spot = PickAttackSpotNearHero();
    const float dz = spot.z - m_v3Position.z;
    const float dx = spot.x - m_v3Position.x;
    if (ppc::fmadds(dx, dx, dz * dz) <= m_pActiveEnemyCpnt->m_unk54c &&
        static_cast<const CKHkDetectorGroup*>(SquadZone(m_pGroupSquad)->m_pUnk30)->IsTriggered(&m_v3Position.x) != 0) {  // vt+0xc4
        return kNull;
    }
    return spot;
}

// 0x0027d208 CKHkS08Enemy_PickSpotAlongTargetAim_maybe: with a hero target (+0x330, class 0x25c2), the point along its
// aim direction from its position: back by the current attack's distance (+0x73c +0x0c), or 5 ahead without an attack
// (TOC +0xb0c, -5.0f); the enemy's own position (+0x134) when there is no hero target or no sector route joins the two.
CVector3 CKHkS08Enemy::PickSpotAlongTargetAim() {
    if (m_pTarget == nullptr || m_pTarget->IsKindOfClass(0x25c2) == 0) return m_v3Position;  // vt+0x08
    const CKHkS08Hero* hero = static_cast<const CKHkS08Hero*>(m_pTarget);
    const float* at = hero->GetPositionPtr();  // 0x00361968
    CVector3 spot;
    if (m_pCurrentAttack == nullptr) {
        const CVector3 aim = hero->GetAimDirection();  // 0x0032a708
        const float k = -5.0f;                          // TOC +0xb0c
        spot.x = ppc::fmadds(aim.x, k, at[0]);
        spot.z = ppc::fmadds(aim.z, k, at[2]);
        spot.y = ppc::fmadds(aim.y, k, at[1]);
    } else {
        const CVector3 aim = hero->GetAimDirection();
        const float k = -m_pCurrentAttack->m_unk0c;
        spot.z = ppc::fmadds(k, aim.z, at[2]);
        spot.x = ppc::fmadds(k, aim.x, at[0]);
        spot.y = ppc::fmadds(k, aim.y, at[1]);
    }
    CKSrvPathFinding* pathFinding = static_cast<CKSrvPathFinding*>(g_pEngine->m_srvPathFinding);  // TOC +0xb08 -> +0x6c
    CPFPoint own;
    own.m_i16GraphNodeIndex = 0xffff;
    own.m_position = m_v3Position;
    own.m_i16GraphNodeIndex = m_PFCpnt.m_Destination.m_i16GraphNodeIndex;
    pathFinding->FindSectorForPoint(&own);  // 0x001e5ca0
    CPFPoint target;
    target.m_position = spot;
    target.m_i16GraphNodeIndex = 0xffff;
    target.m_i16GraphNodeIndex = m_PFCpnt.m_Destination.m_i16GraphNodeIndex;
    pathFinding->FindSectorForPoint(&target);
    if (pathFinding->HasSectorRoute(&own, &target, &m_PFCpnt.m_CharacterType, nullptr) == 0) return m_v3Position;  // 0x001e9198
    return spot;
}

// 0x0027e520 CKHkS08Enemy_PickAttackSpotNearHeroAnyAngle_maybe: as PickAttackSpotNearHero, but the direction is the x
// axis (0x00c50d34) turned about y by a random angle of up to 360 degrees either way (two draws), and the spot only needs
// the detectors, a ground in reach without flag 0x400, a sector route from the enemy, a ground that does not slide and
// no active enemy within the two radii. An enemy outside its zone's detectors keeps +0x1c4.
CVector3 CKHkS08Enemy::PickAttackSpotNearHeroAnyAngle() {
    const CVector3 kNull = {0.0f, 0.0f, 0.0f};  // 0x00c50d64 (TOC +0xb7c)
    const CVector3 kAxisX = {1.0f, 0.0f, 0.0f};  // 0x00c50d34 (TOC +0xb74; filled by a static initialiser)
    if (static_cast<const CKHkDetectorGroup*>(SquadZone(m_pGroupSquad)->m_pUnk30)->IsTriggered(&m_v3Position.x) == 0) {  // vt+0xc4
        return CVector3{m_unk1c4, m_unk1c8, m_unk1cc};
    }
    const CKS08EnemyCpnt* kind = m_pActiveEnemyCpnt;
    if (!(kind->m_vUnk11c.m_ui32NbUsedElt > m_unk32c)) return kNull;
    const float reach = kind->m_unk1bc;
    const float distance = static_cast<const CKS08EnemyAttack*>(kind->m_vUnk11c.m_pBlock[m_unk32c])->m_unk0c;
    float angle;
    const float side = static_cast<float>(static_cast<uint32_t>(Rand_Int()) & 0xffffu) / 65535.0f;  // 0x00011500, TOC +0xb64
    if (side <= 0.5f) {  // TOC +0xb68
        angle = static_cast<float>(static_cast<uint32_t>(Rand_Int()) & 0xffffu) / -65535.0f * 360.0f;  // TOC +0xb70 / +0xb6c
    } else {
        angle = static_cast<float>(static_cast<uint32_t>(Rand_Int()) & 0xffffu) / 65535.0f * 360.0f;
    }
    CMatrix34 turn;
    std::memset(&turn, 0, sizeof(turn));  // the original masks its stack's flag word (0xfffdfffc) and leaves the pads
    turn.m_at = kAxisX;
    Mat4_RotateInPlace(&turn, &kAxisY, angle * 0.017453291f * 57.29578f);  // 0x00240498, TOC +0xb78 / +0xb14 / +0xb10
    const CVector3 direction = turn.m_at;
    const uint32_t count = static_cast<IKGrpHero*>(enemy::HeroGroup())->GetHeroCount();  // 0x00276f70, 0x002ca038
    if ((count & 0xffu) == 0) return kNull;
    const float away = distance + reach;
    IKGrpHero* heroes = static_cast<IKGrpHero*>(enemy::HeroGroup());
    const uint32_t pick = static_cast<uint32_t>(Rand_Int()) & 0xffffu;
    const CKHkS08Hero* hero = static_cast<const CKHkS08Hero*>(heroes->m_apHeros[((count & 0xffu) * pick >> 16) & 0xffu]);  // 0x002ca080
    const float* at = hero->GetPositionPtr();  // 0x00361968
    CVector3 spot;
    spot.x = ppc::fmadds(away, direction.x, at[0]);
    spot.z = ppc::fmadds(away, direction.z, at[2]);
    spot.y = ppc::fmadds(away, direction.y, at[1]);
    if (static_cast<const CKHkDetectorGroup*>(SquadZone(m_pGroupSquad)->m_pUnk30)->IsTriggered(&spot.x) == 0) return kNull;
    CKSrvCollision* collision = static_cast<CKSrvCollision*>(g_pEngine->m_srvCollision);
    collision->GroundProbePoints(&m_GrdContDatasIn, &m_GrdContDatasInOut, &spot.x, 1);  // 0x00196540
    if (m_GrdContDatasInOut.m_eContactStatus - 2u <= 1u) return kNull;
    if ((static_cast<const ICollisionMesh*>(m_GrdContDatasInOut.m_pGround)->m_ui16PropertiesFlags & 0x400u) != 0) return kNull;
    CKSrvPathFinding* pathFinding = static_cast<CKSrvPathFinding*>(g_pEngine->m_srvPathFinding);
    CPFPoint own;
    own.m_i16GraphNodeIndex = 0xffff;
    own.m_position = m_v3Position;
    own.m_i16GraphNodeIndex = m_PFCpnt.m_Destination.m_i16GraphNodeIndex;
    pathFinding->FindSectorForPoint(&own);  // 0x001e5ca0
    CPFPoint target;
    target.m_i16GraphNodeIndex = 0xffff;
    target.m_position = spot;
    target.m_i16GraphNodeIndex = m_PFCpnt.m_Destination.m_i16GraphNodeIndex;
    pathFinding->FindSectorForPoint(&target);
    if (pathFinding->HasSectorRoute(&own, &target, &m_PFCpnt.m_CharacterType, nullptr) == 0) return kNull;  // 0x001e9198
    const ICollisionMesh* ground = static_cast<const ICollisionMesh*>(m_GrdContDatasInOut.m_pGround);
    if (ground == nullptr || (ground->m_ui16PropertiesFlags & 0x200u) != 0) return kNull;
    const IKGrpEnemy* group = static_cast<const IKGrpEnemy*>(enemy::EnemyGroup());  // 0x00276f58
    const uint32_t active = group->m_ui32NbActiveEnemies;
    const float radius = m_pActiveEnemyCpnt->m_MoveCpnt.m_afParams[0];  // +0x0c
    for (uint32_t i = 0; i < active; ++i) {
        const CKHkS08Enemy* other = static_cast<const CKHkS08Enemy*>(group->m_apActiveEnemies[i]);
        const float dx = spot.x - other->m_v3Position.x;
        const float dz = spot.z - other->m_v3Position.z;
        const float both = radius + other->m_pEnemyCpnt->m_MoveCpnt.m_afParams[0];
        const float limit = both * both;
        if (i == 0) {
            if (limit > ppc::fmadds(dz, dz, dx * dx)) return kNull;  // bgt
        } else if (!(ppc::fmadds(dx, dx, dz * dz) >= limit)) {     // bge
            return kNull;
        }
    }
    return spot;
}

// 0x0027f2d8 CKHkS08Enemy_ClampToNavSectors_maybe: unless the path finding is in mode 0x40 (+0x3c) without +0x70 bit
// 0x400, the position is kept on the nav mesh: no graph node for it sends it back to +0x140 (none for that either: the
// life flag 0x10, 0); a new node needs an open, allowed, two-way transition from the old one (mode 0x40 skips that);
// outside the off-nav flag (0x80) a position outside its node or not walkable goes back to +0x140 when that point is
// walkable in the old node (0), else it is tried with a zero-radius character (back to +0x140 if not walkable either),
// and the character's radius becomes the move radius capped at the half cell less 0.05. The node hint is kept (not in
// mode 0x40). Then the ground probe's reach: the height fallen since +0x144 (if above 0) plus 0.2 down and 2 up; 1.
uint8_t CKHkS08Enemy::ClampToNavSectors() {
    CKPathFindingCpnt& pf = m_PFCpnt;
    const bool quick = (pf.m_eState & 0x40) != 0 && (pf.m_bits70 & 0x400u) == 0;
    if (!quick) {
        CKSrvPathFinding* pathFinding = static_cast<CKSrvPathFinding*>(g_pEngine->m_srvPathFinding);
        const int16_t oldHint = static_cast<int16_t>(pf.m_Destination.m_i16GraphNodeIndex);
        const CVector3 previous = {m_unk140, m_unk144, m_unk148};
        CPFPoint point;
        point.m_position = m_v3Position;
        point.m_i16GraphNodeIndex = static_cast<uint16_t>(oldHint);
        if ((pathFinding->FindSectorForPoint(&point) & 0xffu) == 0) {  // 0x001e5ca0
            point.m_position = previous;
            if ((pathFinding->FindSectorForPoint(&point) & 0xffu) == 0) {
                m_bitArray = (m_bitArray & 0xffffffefu) | 0x10u;
                return 0;
            }
            m_v3Position = previous;
            return 0;
        }
        const uint16_t newHint = point.m_i16GraphNodeIndex;
        if (static_cast<int16_t>(newHint) != oldHint && (pf.m_eState & 0x40) == 0) {
            CKPFGraphTransition* transition =
                pathFinding->GetTransitionBetween(newHint, static_cast<uint16_t>(oldHint));  // 0x001e3e28
            if (transition == nullptr || (transition->m_baFlags & 1u) != 0 ||
                (transition->AllowsCharacter(&pf.m_CharacterType) & 0xffu) == 0 ||  // 0x001f0648
                (transition->m_baFlags & 4u) == 0) {
                m_v3Position = previous;
                return 0;
            }
        }
        if ((m_bitArray & 0x80u) == 0 &&
            !(PointInNodeBox(pathFinding, &point) &&
              (pathFinding->IsPointWalkable(&point, &pf.m_CharacterType) & 0xffu) != 0)) {  // 0x001e42d0
            point.m_position = previous;
            point.m_i16GraphNodeIndex = static_cast<uint16_t>(oldHint);
            if (PointInNodeBox(pathFinding, &point) &&
                (pathFinding->IsPointWalkable(&point, &pf.m_CharacterType) & 0xffu) != 0) {
                m_v3Position = previous;
                return 0;
            }
            point.m_position = m_v3Position;
            point.m_i16GraphNodeIndex = newHint;
            pf.m_CharacterType.m_fRadius = 0.0f;
            if (!PointInNodeBox(pathFinding, &point) ||
                (pathFinding->IsPointWalkable(&point, &pf.m_CharacterType) & 0xffu) == 0) {
                m_v3Position = previous;
            }
            const float cap = g_pfGridScale.m_halfCellSize - 0.05f;  // TOC +0xbb0 / +0xbb4
            const float radius = m_pEnemyCpnt->m_MoveCpnt.m_afParams[0];
            pf.m_CharacterType.m_fRadius = radius < cap ? radius : cap;
        }
        if ((pf.m_eState & 0x40) == 0) {
            pf.m_Destination.m_i16GraphNodeIndex = point.m_i16GraphNodeIndex;
            const float fallen = m_unk144 - m_v3Position.y;
            if (fallen > 0.0f) {
                m_GrdContDatasIn.m_fDeltaMax = fallen + 0.2f;      // TOC +0xbb8
                m_GrdContDatasIn.m_fObjectHeight = fallen + 2.0f;  // TOC +0xbbc
            } else {
                m_GrdContDatasIn.m_fDeltaMax = 0.2f;
                m_GrdContDatasIn.m_fObjectHeight = 2.0f;
            }
            return 1;
        }
    }
    const float fallen = m_unk144 - m_v3Position.y;
    if (fallen <= 0.0f) {
        m_GrdContDatasIn.m_fDeltaMax = 0.2f;
        m_GrdContDatasIn.m_fObjectHeight = 2.0f;
    } else {
        m_GrdContDatasIn.m_fDeltaMax = fallen + 0.2f;
        m_GrdContDatasIn.m_fObjectHeight = fallen + 2.0f;
    }
    return 1;
}

// 0x0027f8c0 CKHkS08Enemy_IsReachablePoint_maybe (ported from the instructions: Ghidra's decompile mixes up the three
// path points). `point` must be inside the fight zone's detectors (EvaluateConditions 0x5bda08 through its TocBridge,
// no enable test). When the last position (+0x140) lies in its graph node's box and is walkable, the enemy's position
// (+0x134) and `point` get their nodes (the hint +0xbc +0x4c each) and, unless the position is itself in its box and
// walkable, a sector route must join the two (none: not reachable). Then, outside the state 0x18, the walls swept from
// the position to `point` (the kind's radius +0x0c, the tuning component's height) must not block, slide or push
// (results 1..3: not reachable).
bool CKHkS08Enemy::IsReachablePoint(const CVector3* point) {
    const CKHkDetectorGroup* detectors = static_cast<const CKHkDetectorGroup*>(SquadZone(m_pGroupSquad)->m_pUnk30);
    if ((detectors->EvaluateConditions(&point->x, 0) & 0xff) == 0) return false;  // TocBridge 0x0098f2f0
    CKSrvPathFinding* pathFinding = static_cast<CKSrvPathFinding*>(g_pEngine->m_srvPathFinding);  // TOC +0xb08 -> +0x6c
    CPFPoint last;
    last.m_i16GraphNodeIndex = 0xffff;
    last.m_position = CVector3{m_unk140, m_unk144, m_unk148};
    last.m_i16GraphNodeIndex = m_PFCpnt.m_Destination.m_i16GraphNodeIndex;
    pathFinding->FindSectorForPoint(&last);  // 0x001e5ca0 (the result is not used)
    if (PointInNodeBox(pathFinding, &last) &&
        (pathFinding->IsPointWalkable(&last, &m_PFCpnt.m_CharacterType) & 0xffu) != 0) {  // 0x001e42d0
        CPFPoint own;
        own.m_i16GraphNodeIndex = 0xffff;
        CPFPoint target;
        target.m_i16GraphNodeIndex = 0xffff;
        own.m_position = m_v3Position;
        own.m_i16GraphNodeIndex = m_PFCpnt.m_Destination.m_i16GraphNodeIndex;
        pathFinding->FindSectorForPoint(&own);
        target.m_position = *point;
        target.m_i16GraphNodeIndex = m_PFCpnt.m_Destination.m_i16GraphNodeIndex;
        pathFinding->FindSectorForPoint(&target);
        if (!(PointInNodeBox(pathFinding, &own) &&
              (pathFinding->IsPointWalkable(&own, &m_PFCpnt.m_CharacterType) & 0xffu) != 0) &&
            (pathFinding->HasSectorRoute(&own, &target, &m_PFCpnt.m_CharacterType, nullptr) & 0xffu) == 0) {  // 0x001e9198
            return false;
        }
    }
    if (m_mainState == 0x18) return true;
    CKSrvCollision* collision = static_cast<CKSrvCollision*>(g_pEngine->m_srvCollision);  // +0x58
    CLine line;
    line.m_start = m_v3Position;
    line.m_VectDir = CVector3{point->x - m_v3Position.x, point->y - m_v3Position.y, point->z - m_v3Position.z};
    CSlideGroundEdgeDatasOut slide;
    const uint8_t result = collision->ResolveSweptCylinderWalls(&line, m_pActiveEnemyCpnt->m_MoveCpnt.m_afParams[0],
                                                                ComponentHeight(), &slide, nullptr, nullptr, 1);  // 0x0019aa68
    return !(static_cast<uint32_t>(result) - 1u <= 2u);
}

// 0x0027fce8 CKHkS08Enemy_PickRandomReachablePoint_maybe: a point the enemy can walk to (IsReachablePoint), the null
// vector when none is found. First along the yaw turned by a random angle within the kind's +0x308 degrees either way
// (one draw): at the kind's +0x304, else 5 ahead, the distance shrinking by (+0x304 - +0x300) / +0x30c each of the
// +0x30c tries; then (a second draw) from a random distance between +0x300 and +0x304, each try along the z axis turned
// about y by a new random angle up to 360 degrees (one draw per try), at that distance, else 5 ahead, shrinking alike.
CVector3 CKHkS08Enemy::PickRandomReachablePoint() {
    const CVector3 kNull = {0.0f, 0.0f, 0.0f};   // 0x00c50d64 (TOC +0xb7c)
    const CVector3 kAxisY = {0.0f, 1.0f, 0.0f};  // 0x00c50d40 (TOC +0xb10)
    const CVector3 kAxisZ = {0.0f, 0.0f, 1.0f};  // 0x00c50d4c (TOC +0xbc4)
    const float kAhead = 5.0f;                   // TOC +0xbc8
    auto direction = [&](float degrees) {
        CMatrix34 turn;
        std::memset(&turn, 0, sizeof(turn));  // the original masks its stack's flag word (0xfffdfffc) and leaves the pads
        turn.m_at = kAxisZ;
        Mat4_RotateInPlace(&turn, &kAxisY, degrees);  // 0x00240498
        return turn.m_at;
    };
    auto shrink = [&](float distance) {
        const CKS08EnemyCpnt* kind = m_pActiveEnemyCpnt;
        const uint32_t tries = static_cast<uint32_t>(kind->m_unk30c);
        return distance - (kind->m_unk304 - kind->m_unk300) / static_cast<float>(static_cast<double>(tries));
    };
    CVector3 spot;
    float distance = m_pActiveEnemyCpnt->m_unk304;
    const float r0 = static_cast<float>(static_cast<double>(static_cast<uint32_t>(Rand_Int()) & 0xffffu));  // 0x00011500
    const float range = m_pActiveEnemyCpnt->m_unk308;
    const float half = r0 / 65535.0f;  // TOC +0xb64
    const float offset = ppc::fmadds(half + half, range * 0.017453290f, range * -0.017453290f);  // TOC +0xb78 / +0xbc0
    uint32_t i = 0;
    if (m_pActiveEnemyCpnt->m_unk30c != 0) {
        for (;;) {
            const float degrees = (offset + m_fYaw) * 57.29578f;  // TOC +0xb14
            ++i;
            const CVector3 at = direction(degrees);
            spot = CVector3{ppc::fmadds(distance, at.x, m_v3Position.x), ppc::fmadds(distance, at.y, m_v3Position.y),
                            ppc::fmadds(distance, at.z, m_v3Position.z)};
            if (IsReachablePoint(&spot)) return spot;
            spot = CVector3{ppc::fmadds(at.x, kAhead, m_v3Position.x), ppc::fmadds(at.y, kAhead, m_v3Position.y),
                            ppc::fmadds(at.z, kAhead, m_v3Position.z)};
            if (IsReachablePoint(&spot)) return spot;
            if (!(static_cast<uint32_t>(m_pActiveEnemyCpnt->m_unk30c) > i)) break;
            distance = shrink(distance);
        }
    }
    // 0x0027ffa0
    const uint32_t r1 = static_cast<uint32_t>(Rand_Int()) & 0xffffu;
    if (m_pActiveEnemyCpnt->m_unk30c == 0) return kNull;
    {
        const CKS08EnemyCpnt* kind = m_pActiveEnemyCpnt;
        distance = ppc::fmadds(static_cast<float>(static_cast<double>(r1)) / 65535.0f, kind->m_unk304 - kind->m_unk300,
                               kind->m_unk300);
    }
    i = 0;
    for (;;) {
        const float r = static_cast<float>(static_cast<double>(static_cast<uint32_t>(Rand_Int()) & 0xffffu));
        ++i;
        const float degrees = r / 65535.0f * 360.0f * 0.017453290f * 57.29578f;  // TOC +0xb6c
        const CVector3 at = direction(degrees);
        spot = CVector3{ppc::fmadds(distance, at.x, m_v3Position.x), ppc::fmadds(distance, at.y, m_v3Position.y),
                        ppc::fmadds(distance, at.z, m_v3Position.z)};
        if (IsReachablePoint(&spot)) return spot;
        spot = CVector3{ppc::fmadds(at.x, kAhead, m_v3Position.x), ppc::fmadds(at.y, kAhead, m_v3Position.y),
                        ppc::fmadds(at.z, kAhead, m_v3Position.z)};
        if (IsReachablePoint(&spot)) return spot;
        if (!(static_cast<uint32_t>(m_pActiveEnemyCpnt->m_unk30c) > i)) return kNull;
        distance = shrink(distance);
    }
}

// 0x00283b08 CKHkS08Enemy_ResolveGroundAndApplyTransform_maybe (vt+0x13c). While another holds the enemy (+0x294, not a
// wind-beam grab) only the nav check at the end runs. Else: outside the states 0x17 / 0x18 the walls swept from +0x140
// (the move radius + 0.1; blocked: back on x / z, the speed's x / z zeroed; slid or pushed: moved). A wind-beam grab only
// keeps the last safe point (fight zone state 4). Then the ground: the attack states 0xd..0xf and 6 on the ground (not
// +0x7b4) go back on x / z without a ground (or on a slide at status 0), or when the position fits the wide character
// (0x404) but not the narrow one (0x402). The falling / in-air states (2 with reaction 8 / 2 / 6, +0x7b4 — state 1
// clamps to the nav mesh first —, 0x1d, 0x27) probe the ground (the attack states back on x / z when off the nav):
// within reach (1 / 2) up by the distance, +0x7b4 cleared on a ground that is not a slide (kind 8 keeps it); in the air
// (3) the walls swept from +0x140 (blocked: back and state 0x15; free: back on x / z, y too unless still in the air, the
// speed's x / z zeroed; slid / pushed: moved, the speed's x / z zeroed); else SnapToGround. The others: the off-nav flag
// (0x80) set in the states 2 (reactions 2 / 6 / 7 / 8 / 10 / 11), 0x15, 0x17, 0x18, 7 and 10, the nav and ground
// constraint (vt+0xe0) outside 0xd..0xf, the flag cleared, SnapToGround. A position the fight zone's detector group
// refuses goes back on x / z. The flying kinds 1 / 8 in state 1 get their height. The node placed at the position and
// turned by the yaw (+0x154; not in an attack state whose attack +0x64 is 3), the last safe point kept (state 4); then
// the nav check: state 1 off the nav (or mode 0x40 while on the ground and the path idle) picks a move target (+0x85c,
// +0x86f) and goes to state 0x17; the life flag 0x10 (outside reaction 0xf) sends the enemy to state 0x15.
void CKHkS08Enemy::ResolveGroundAndApplyTransform(IKTime* /*clock*/) {
    CKSrvPathFinding* pathFinding = static_cast<CKSrvPathFinding*>(g_pEngine->m_srvPathFinding);
    CKSrvCollision* collision = static_cast<CKSrvCollision*>(g_pEngine->m_srvCollision);
    CVector3& pos = m_v3Position;
    if (m_pGrabbingHero == nullptr || IsHeldByWindBeam()) {
        // 0x00284028
        if (m_mainState != 0x17 && m_mainState != 0x18) {
            CLine line;
            line.m_start = CVector3{m_unk140, m_unk144, m_unk148};
            line.m_VectDir = CVector3{pos.x - m_unk140, pos.y - m_unk144, pos.z - m_unk148};
            CSlideGroundEdgeDatasOut slide;
            const uint8_t result = collision->ResolveSweptCylinderWalls(
                &line, m_pActiveEnemyCpnt->m_MoveCpnt.m_afParams[0] + 0.1f, ComponentHeight(), &slide, nullptr, nullptr,
                1);  // 0x0019aa68, TOC +0xbe8
            if (result == 1) {
                pos.x = m_unk140;
                pos.z = m_unk148;
                m_v3Speed.z = 0.0f;
                m_v3Speed.x = 0.0f;
            } else if (result >= 2 && result <= 3) {
                pos.x = slide.m_v3BouncingVector.x + pos.x;
                pos.y = slide.m_v3BouncingVector.y + pos.y;
                pos.z = slide.m_v3BouncingVector.z + pos.z;
            }
        }
        // 0x002840e8
        if (m_pGrabbingHero != nullptr && IsHeldByWindBeam()) {
            if (SquadZone(m_pGroupSquad)->m_pFightZoneCpnt->m_unk04 != 4) return;
            RememberSafePoint(CVector3{pos.x, pos.y, pos.z});
            return;
        }
        // 0x0028412c
        CPFPoint point;
        point.m_position = pos;
        point.m_i16GraphNodeIndex = m_PFCpnt.m_Destination.m_i16GraphNodeIndex;
        pathFinding->FindSectorForPoint(&point);  // 0x001e5ca0 (the result is not used)
        const float radius = g_pfGridScale.m_halfCellSize * 0.2f;  // TOC +0xbb0 / +0xbb8
        const CPFCharacter wide = {0x404u, radius, 0.2f, 1.0f};
        const CPFCharacter narrow = {0x402u, radius, 0.2f, 1.0f};
        collision->GroundProbePoints(&m_GrdContDatasIn, &m_GrdContDatasInOut, &pos.x, 1);  // 0x00196540
        if (m_unk7b4 == 0) {
            const uint8_t state = m_mainState;
            if (state == 0xd || state == 0xe || state == 0xf || state == 6) {
                const ICollisionMesh* ground = static_cast<const ICollisionMesh*>(m_GrdContDatasInOut.m_pGround);
                bool back = ground == nullptr ||
                            ((ground->m_ui16PropertiesFlags & 0x200u) != 0 && m_GrdContDatasInOut.m_eContactStatus == 0);
                if (!back && PointInNodeBox(pathFinding, &point) &&
                    (pathFinding->IsPointWalkable(&point, &wide) & 0xffu) != 0) {  // 0x001e42d0
                    back = !(PointInNodeBox(pathFinding, &point) &&
                             (pathFinding->IsPointWalkable(&point, &narrow) & 0xffu) != 0);
                }
                if (back) {  // 0x00284868
                    pos.x = m_unk140;
                    pos.z = m_unk148;
                }
            }
        }
        // 0x002843f8
        const uint8_t state = m_mainState;
        const uint8_t react = m_reactState;
        bool falling = false;
        if (state == 2 && (react == 8 || react == 2 || react == 6)) {
            falling = true;
        } else if (m_unk7b4 != 0) {
            if (state == 1 && (m_PFCpnt.m_eState & 0x40) == 0) ClampToNavSectors();  // 0x0027f2d8
            falling = true;
        } else if (state == 0x1d || state == 0x27) {
            falling = true;
        }
        if (falling) {
            // 0x0028441c
            if (m_mainState == 0xd || m_mainState == 0xe || m_mainState == 0xf) {
                CPFPoint at;
                at.m_position = pos;
                at.m_i16GraphNodeIndex = m_PFCpnt.m_Destination.m_i16GraphNodeIndex;
                pathFinding->FindSectorForPoint(&at);
                if (!(PointInNodeBox(pathFinding, &at) &&
                      (pathFinding->IsPointWalkable(&at, &m_PFCpnt.m_CharacterType) & 0xffu) != 0)) {
                    pos.x = m_unk140;
                    pos.z = m_unk148;
                }
            }
            // 0x00284438
            collision->GroundProbePoints(&m_GrdContDatasIn, &m_GrdContDatasInOut, &pos.x, 1);
            const int32_t status = static_cast<int32_t>(m_GrdContDatasInOut.m_eContactStatus);
            if (status >= 1 && status <= 2) {
                // 0x00284ac8
                pos.y = pos.y + m_GrdContDatasInOut.m_fdH;
                if (m_ui8EnemyClassType != 8) {
                    bool checkGround = true;
                    if (m_unk7b4 == 0 && !(m_mainState == 2 && m_reactState == 2)) {
                        m_unk7b4 = 0;
                        checkGround = false;
                    }
                    if (checkGround) {
                        const ICollisionMesh* ground = static_cast<const ICollisionMesh*>(m_GrdContDatasInOut.m_pGround);
                        if (ground != nullptr && (ground->m_ui16PropertiesFlags & 0x200u) == 0) m_unk7b4 = 0;
                    }
                }
            } else if (status == 3) {
                // 0x00284e74
                CLine line;
                line.m_start = CVector3{m_unk140, m_unk144, m_unk148};
                line.m_VectDir = CVector3{pos.x - m_unk140, pos.y - m_unk144, pos.z - m_unk148};
                CSlideGroundEdgeDatasOut slide;
                const uint8_t result = collision->ResolveSweptCylinderWalls(
                    &line, m_pActiveEnemyCpnt->m_MoveCpnt.m_afParams[0], ComponentHeight(), &slide, nullptr, nullptr, 1);
                if (result == 1) {
                    pos = CVector3{m_unk140, m_unk144, m_unk148};
                    SwitchMainState(0x15, nullptr);
                } else if (result == 0) {
                    const CVector3 previous = {m_unk140, m_unk144, m_unk148};
                    collision->GroundProbePoints(&m_GrdContDatasIn, &m_GrdContDatasInOut, &previous.x, 1);
                    if (m_GrdContDatasInOut.m_eContactStatus != 3) pos.y = m_unk144;
                    pos.x = m_unk140;
                    pos.z = m_unk148;
                    m_v3Speed.z = 0.0f;
                    m_v3Speed.x = 0.0f;
                } else if (result <= 3) {
                    pos.x = slide.m_v3BouncingVector.x + pos.x;
                    m_v3Speed.x = 0.0f;
                    pos.z = slide.m_v3BouncingVector.z + pos.z;
                    pos.y = slide.m_v3BouncingVector.y + pos.y;
                    m_v3Speed.z = 0.0f;
                }
            } else {
                SnapToGround();  // 0x00286ee0
            }
        } else {
            // 0x002847a0
            bool offNav = false;
            if (state == 2) {
                offNav = react == 2 || react == 6 || react == 7 || react == 8 || react == 0xa || react == 0xb;
            } else {
                offNav = state == 0x15 || state == 0x17 || state == 0x18 || state == 7 || state == 0xa;
            }
            if (offNav) m_bitArray = (m_bitArray & 0xffffff7fu) | 0x80u;
            if (m_mainState != 0xd && m_mainState != 0xe && m_mainState != 0xf) {
                ConstrainToGroundAndNavMesh();  // vt+0xe0 (the result is not used)
            }
            m_bitArray = m_bitArray & 0xffffff7fu;
            SnapToGround();
        }
        // 0x00284484
        const CKHkDetectorGroup* detectors = static_cast<const CKHkDetectorGroup*>(SquadZone(m_pGroupSquad)->m_pUnk30);
        if (detectors->EvaluateConditions(&pos.x, 0) == 0) {  // 0x005bda08
            pos.x = m_unk140;
            pos.z = m_unk148;
        }
        if ((m_ui8EnemyClassType == 1 || m_ui8EnemyClassType == 8) && m_mainState == 1) UpdateFlyingHeight();
        // 0x002844d0
        RwFrame* frame = static_cast<CSGMovable*>(m_pKGLObject)->m_pRwFrame;
        frame->modelling.pos.z = pos.z;
        frame->modelling.pos.x = pos.x;
        frame->modelling.pos.y = pos.y;
        frame->modelling.flags &= 0xfffdffffu;
        RwFrame_MarkDirty(frame);  // 0x00010698
        const uint8_t now = m_mainState;
        if (!(now == 0xd || now == 0xe || now == 0xf) || m_pCurrentAttack == nullptr || m_pCurrentAttack->m_unk64 != 3) {
            RwFrame* turned = static_cast<CSGMovable*>(m_pKGLObject)->m_pRwFrame;
            Mat4_SetRotationAboutAxis(m_fYaw, reinterpret_cast<CMatrix34*>(&turned->modelling), 1);  // 0x00241688
            RwFrame_MarkDirty(turned);
        }
        if (SquadZone(m_pGroupSquad)->m_pFightZoneCpnt->m_unk04 == 4) RememberSafePoint(CVector3{pos.x, pos.y, pos.z});
    }
    // 0x00283bac: the nav check.
    CPFPoint point;
    point.m_position = pos;
    point.m_i16GraphNodeIndex = m_PFCpnt.m_Destination.m_i16GraphNodeIndex;
    pathFinding->FindSectorForPoint(&point);  // 0x001e5ca0 (the result is not used)
    bool chooseTarget = false;
    if (m_mainState == 1 && !(PointInNodeBox(pathFinding, &point) &&
                              (pathFinding->IsPointWalkable(&point, &m_PFCpnt.m_CharacterType) & 0xffu) != 0)) {
        chooseTarget = (m_PFCpnt.m_eState & 0x40) == 0;
    }
    if (!chooseTarget && (m_PFCpnt.m_eState & 0x40) != 0 && m_mainState == 1 && m_unk7b4 == 0 &&
        (m_PFCpnt.m_bits70 & 0x400u) == 0 && (m_PFCpnt.m_ui32Action & 1u) == 0) {
        chooseTarget = true;
    }
    if (chooseTarget) {
        // 0x00283dc0
        m_unk86f = 1;
        const CVector3 target = ChooseMoveTarget();  // 0x002808e8
        m_unk85c = target.x;
        m_unk864 = target.z;
        m_unk860 = target.y;
        if (target.x == 0.0f && target.y == 0.0f && target.z == 0.0f) {  // the zero vector 0xc50d64 (TOC +0xb7c)
            m_unk86f = 0;
        } else {
            SwitchMainState(0x17, nullptr);
        }
    }
    // 0x00283c0c
    if ((m_bitArray & 0x10u) == 0 || m_reactState == 0xf) return;
    if (m_mainState == 0x15 || m_mainState == 0xff) return;
    SwitchMainState(0x15, nullptr);
    m_bitArray = m_bitArray & 0xfffffff7u;
}

// DOTD: the inlined height of the flying kinds (1 / 8) in state 1 (ResolveGroundAndApplyTransform 0x002848a0). With
// +0x6c8 above 0 in the air (+0x7b4): down by 2 x the frame dt from +0x144, onto a ground within reach. Else the height
// of the ground under +0x37c (+0x380 less / plus the distance; the position's height without a ground) and the ground
// under the position: in the air higher than the kind's +0x494 over it, only without a ground below: the previous
// height, or down by 2 x dt when 0.1 more stays within the limit. Else, with a hero target (+0x330) at least 0.2 above
// its ground, the target height +0x78c from the distance +0x344 (beyond +0x490: the ground height; within +0x48c:
// +0x380; between: interpolated): above it, the position drops by 2 x dt from +0x144 while both heights are below +0x144
// in the air (onto a ground within reach, +0x7b4 cleared but for kind 8), else stays at +0x144 when the ground height
// is not above it.
void CKHkS08Enemy::UpdateFlyingHeight() {
    CKSrvCollision* collision = static_cast<CKSrvCollision*>(g_pEngine->m_srvCollision);
    CVector3& pos = m_v3Position;
    if (!(m_fIceGauge <= 0.0f) && m_unk7b4 != 0) {  // ble
        // 0x00285088
        pos.y = ppc::fmadds(m_fScaledDt, -2.0f, m_unk144);  // TOC +0xbec
        collision->GroundProbePoints(&m_GrdContDatasIn, &m_GrdContDatasInOut, &pos.x, 1);
        if (m_GrdContDatasInOut.m_eContactStatus - 1u <= 1u) pos.y = pos.y + m_GrdContDatasInOut.m_fdH;
        return;
    }
    // 0x002848c8
    collision->GroundProbePoints(&m_GrdContDatasIn, &m_GrdContDatasInOut, &m_unk37c, 1);
    const int32_t status = static_cast<int32_t>(m_GrdContDatasInOut.m_eContactStatus);
    float groundHeight = pos.y;
    if (status == 0) {
        groundHeight = m_unk380 - m_GrdContDatasInOut.m_fdH;
    } else if (status >= 0 && status <= 2) {
        groundHeight = m_unk380 + m_GrdContDatasInOut.m_fdH;
    }
    collision->GroundProbePoints(&m_GrdContDatasIn, &m_GrdContDatasInOut, &pos.x, 1);
    const float over = m_GrdContDatasInOut.m_fdH;
    const float limit = m_pActiveEnemyCpnt->m_unk494;
    if (!(over <= limit) && m_unk7b4 != 0) {
        if (m_GrdContDatasInOut.m_eContactStatus != 0) return;
        if (over + 0.1f <= limit) {  // TOC +0xbe8
            pos.y = ppc::fmadds(m_fScaledDt, -2.0f, m_unk144);
        } else {
            pos.y = m_unk144;
        }
        return;
    }
    // 0x00284f48
    IKHook* target = m_pTarget;
    if (target == nullptr || target->IsKindOfClass(0x25c2) == 0) return;  // vt+0x08
    const RwV3d& at = static_cast<CSGMovable*>(target->m_pKGLObject)->m_pRwFrame->modelling.pos;
    collision->GroundProbePoints(&m_GrdContDatasIn, &m_GrdContDatasInOut, &at.x, 1);
    if (m_GrdContDatasInOut.m_eContactStatus != 0) return;
    if (!(m_GrdContDatasInOut.m_fdH >= 0.2f)) return;  // TOC +0xbb8
    const CKS08EnemyCpnt* config = m_pActiveEnemyCpnt;
    float height;
    if (config->m_unk490 <= m_unk344) {
        height = groundHeight;
    } else if (config->m_unk48c >= m_unk344) {
        height = m_unk380;
    } else {
        collision->GroundProbePoints(&m_GrdContDatasIn, &m_GrdContDatasInOut, &m_unk37c, 1);  // (the result is not used)
        const float span = (m_unk380 - groundHeight) * (config->m_unk490 - m_unk344);
        height = groundHeight + span / (config->m_unk490 - config->m_unk48c);
    }
    m_unk78c = height;
    if (pos.y <= height) return;
    const float previous = m_unk144;
    if (height < previous && groundHeight < previous && m_unk7b4 != 0) {
        // 0x002852d8
        pos.y = ppc::fmadds(m_fScaledDt, -2.0f, previous);
        collision->GroundProbePoints(&m_GrdContDatasIn, &m_GrdContDatasInOut, &pos.x, 1);
        if (m_GrdContDatasInOut.m_eContactStatus - 1u <= 1u) {
            pos.y = pos.y + m_GrdContDatasInOut.m_fdH;
            if (m_ui8EnemyClassType != 8) m_unk7b4 = 0;
        }
        return;
    }
    if (groundHeight <= previous) pos.y = previous;
}

// 0x0027d138 CKHkS08Enemy_vf148 (vt+0x148): the timer +0x2ac and the first n timers of +0x2b0 (n: the used count of the
// component's +0x11c vector; from the last down) count down by +0x1fc while not below 0.
void CKHkS08Enemy::TickAttackCooldowns() {
    if (m_unk2ac >= 0.0f) m_unk2ac = m_unk2ac - m_fScaledDt;  // TOC1 +0xaf4 0.0
    const uint32_t count = m_pActiveEnemyCpnt->m_vUnk11c.m_ui32NbUsedElt;  // +0x124
    for (uint32_t i = count; i != 0; --i) {
        float& timer = m_afAttackCooldowns[i - 1];
        if (timer >= 0.0f) timer = timer - m_fScaledDt;
    }
}

// 0x00277650 IKHkEnemy_Update: the position copied to +0x140 (the previous frame's position for the next one).
void IKHkEnemy::Update(IKTime* /*clock*/) {
    m_unk140 = m_v3Position.x;
    m_unk148 = m_v3Position.z;
    m_unk144 = m_v3Position.y;
}

// 0x002771c0 CKHkS08Enemy_GetSectorIndex_maybe
int32_t CKHkS08Enemy::GetSectorIndex() {
    if (GroupKindFlag104(m_ui8EnemyClassType) != 0) return 0;  // vt+0x104
    return static_cast<int32_t>(SquadFightZoneIndex(m_pGroupSquad));

}

// DOTD: the sector component of the enemy's variant (the original inlines GetSectorIndex and the index each time).
CKEnemySectorCpnt* CKHkS08Enemy::GetSectorCpnt() {
    return m_apEnemySectorCpnt[GetSectorIndex()];
}

// 0x00279268 CKHkS08Enemy_DetachSectorNode_maybe: the node leaves its parent and goes back under the sector root of the
// enemy's variant (the group's +0x40 roots; the first one for clones, keys 0x30b / 0x58b).
void CKHkS08Enemy::DetachSectorNode(IKSerializable* node) {
    if (node == nullptr) return;
    CSGLeaf* leaf = static_cast<CSGLeaf*>(node);
    if (leaf->m_pParent != nullptr) leaf->m_pParent->RemoveChild(leaf);  // vt+0x78
    IKGrpEnemy* group = EnemyGroup();
    IKSerializable* root;
    if (node->IsKindOfClass(0x30b) != 0 || node->IsKindOfClass(0x58b) != 0) {  // vt+0x08: CClone, CAnimatedClone
        root = group->m_vUnk40.m_pBlock[0];
    } else {
        const uint32_t variant = GroupKindFlag104(m_ui8EnemyClassType) == 0 ? SquadFightZoneIndex(m_pGroupSquad) : 0u;
        root = group->m_vUnk40.m_pBlock[variant];
    }
    static_cast<CSGBranch*>(root)->AddChild(leaf);  // vt+0x70
}

// 0x0027ad40 CKHkS08Enemy_AttachSectorNode_maybe
void CKHkS08Enemy::AttachSectorNode(IKSerializable* node, uint8_t mode, uint8_t index) {
    if (node == nullptr) return;
    CSGLeaf* leaf = static_cast<CSGLeaf*>(node);
    if (leaf->m_pParent != nullptr) leaf->m_pParent->RemoveChild(leaf);  // vt+0x78
    if (mode > 4) return;
    switch (mode) {  // the jump table at 0x0027ae04 (TOC1 +0xad4)
    case 0:
        static_cast<CSGBranch*>(g_pEngine->m_dynamicSceneRoot)->AddChild(leaf);  // vt+0x70
        break;
    case 1:
        static_cast<CSGMovable*>(node)->SetIdentity();  // 0x000d08f0
        static_cast<CSGBranch*>(m_pKGLObject)->AddChild(leaf);
        break;
    case 2:
        static_cast<CSGMovable*>(node)->SetIdentity();
        static_cast<CSGBranch*>(GetSectorCpnt()->GetAnimatedNode(index))->AddChild(leaf);  // 0x002b3110
        break;
    case 3:
        static_cast<CSGMovable*>(node)->SetIdentity();
        static_cast<CSGBranch*>(GetSectorCpnt()->GetCollisionVolume(index))->AddChild(leaf);  // 0x002b31b0
        break;
    default:
        static_cast<CSGHotSpot*>(GetSectorCpnt()->GetHotSpot(index))->AttachVolume(leaf);  // 0x002b31e0, 0x000ce2b8
        break;
    }
}

// 0x0027aac0 CKHkS08Enemy_BindAttachmentToNode_maybe (C2.8 port-last Z5): the sector component's +0x18 entries are moving
// grounds (CDynamicGround: m_pParent +0x50, m_pInvertedWorldMatrix +0x54; XXL2's IKHkEnemy keeps m_apDynamicGround in
// the same place). Mode 0: no parent and the identity; 1: the enemy's node; 2: an animated node, 3: a collision volume of
// the sector component (index); each with the inverse of its world matrix (frame +0x50), or the identity without one.
// Other modes leave the ground as it is. Only AttachSectorNodesToBones calls it, for the group's vt+0x120 count of the
// kind (0 for every DotD enemy kind, so no level reaches it).
void CKHkS08Enemy::BindAttachmentToNode(IKSerializable* attachment, uint8_t mode, uint8_t index) {
    if (attachment == nullptr) return;
    CDynamicGround* ground = static_cast<CDynamicGround*>(attachment);
    IKSerializable* parent;
    if (mode == 1) {
        parent = m_pKGLObject;
    } else if (mode == 0) {
        ground->m_pParent = nullptr;
        parent = nullptr;
    } else if (mode == 2) {
        parent = GetSectorCpnt()->GetAnimatedNode(index);  // vt+0x104 / the squad's fight zone inlined; 0x002b3110
    } else if (mode == 3) {
        parent = GetSectorCpnt()->GetCollisionVolume(index);  // 0x002b31b0
    } else {
        return;
    }
    if (mode != 0) {
        ground->m_pParent = parent;
        if (parent != nullptr) {
            Mat4_Invert(ground->m_pInvertedWorldMatrix,
                        reinterpret_cast<const CMatrix34*>(&static_cast<CSGMovable*>(parent)->m_pRwFrame->ltm));  // 0x0023f878
            return;
        }
    }
    // The identity written word by word (flags 0x20003 first; the pad words are left).
    CMatrix34* m = ground->m_pInvertedWorldMatrix;
    m->m_ui32Flags = 0x20003u;
    m->m_right.x = 1.0f;  // TOC1 +0xa88
    m->m_pos.x = 0.0f;
    m->m_at.z = 1.0f;
    m->m_up.y = 1.0f;
    m->m_up.x = 0.0f;
    m->m_right.z = 0.0f;
    m->m_right.y = 0.0f;
    m->m_at.y = 0.0f;
    m->m_at.x = 0.0f;
    m->m_up.z = 0.0f;
    m->m_pos.z = 0.0f;
    m->m_pos.y = 0.0f;
}

// 0x0027b048 CKHkS08Enemy_AttachSectorNodesToBones_maybe: the sector component's animated nodes, collision volumes and
// attachments, then the enemy's own volumes (each moved by its offset +0x3c), particle nodes (those with a mode) and fog
// boxes, each hung where its mode / index pair says (the raw u16 arrays +0x20 / +0x24 / +0x28 / +0x40 / +0x58 / +0x68:
// mode byte first). The counts come from the group (vt+0x108 / +0x10c / +0x120 / +0x118 / +0x124 / +0x12c).
void CKHkS08Enemy::AttachSectorNodesToBones() {
    const uint8_t kind = m_ui8EnemyClassType;
    const uint32_t variant = GroupKindFlag104(kind) == 0 ? SquadFightZoneIndex(m_pGroupSquad) : 0u;
    const uint8_t* modes20 = reinterpret_cast<const uint8_t*>(m_unk20);
    const uint8_t* modes24 = reinterpret_cast<const uint8_t*>(m_unk24);
    const uint8_t* modes28 = reinterpret_cast<const uint8_t*>(m_unk28);
    const uint8_t* modes40 = reinterpret_cast<const uint8_t*>(m_unk40);
    const uint8_t* modes58 = reinterpret_cast<const uint8_t*>(m_unk58);
    const uint8_t* modes68 = reinterpret_cast<const uint8_t*>(m_unk68);
    uint32_t count = GroupNbAnimLayers(kind);  // vt+0x108
    for (uint32_t i = 0; i != count; ++i) {
        AttachSectorNode(m_apEnemySectorCpnt[variant]->GetAnimatedNode(i), modes20[i * 2], modes20[i * 2 + 1]);
    }
    count = GroupNbSectorVolumes(kind);  // vt+0x10c
    for (uint32_t i = 0; i != count; ++i) {
        AttachSectorNode(m_apEnemySectorCpnt[variant]->GetCollisionVolume(i), modes24[i * 2], modes24[i * 2 + 1]);
    }
    count = GroupNbAttachments(kind);  // vt+0x120
    for (uint32_t i = 0; i != count; ++i) {
        BindAttachmentToNode(m_apEnemySectorCpnt[variant]->GetArray18Entry(i), modes28[i * 2], modes28[i * 2 + 1]);
    }
    count = GroupNbVolumes(kind);  // vt+0x118
    for (uint32_t i = 0; i != count; ++i) {
        IKSerializable* volume = m_apBV[i];
        if (volume == nullptr) continue;
        AttachSectorNode(volume, modes40[i * 2], modes40[i * 2 + 1]);
        RwFrame* frame = static_cast<CSGMovable*>(m_apBV[i])->m_pRwFrame;
        const CVector3& offset = m_unk3C[i];
        frame->modelling.pos.x = frame->modelling.pos.x + offset.x;
        frame->modelling.pos.y = frame->modelling.pos.y + offset.y;
        frame->modelling.pos.z = frame->modelling.pos.z + offset.z;
        frame->modelling.flags = frame->modelling.flags & 0xfffdffffu;
        RwFrame_MarkDirty(frame);  // 0x00010698
    }
    count = GroupNbParticles(kind);  // vt+0x124
    for (uint32_t i = 0; i != count; ++i) {
        // BUG(original): the group's count (0x16) is used, not the file's: the particle arrays are read as long as the
        // file's count says (equal for LVL010's enemies).
        if (modes58[i * 2] == 0) continue;
        AttachSectorNode(m_apParticleNodeFx[i], modes58[i * 2], modes58[i * 2 + 1]);
    }
    count = GroupNbFogBoxes(kind);  // vt+0x12c
    for (uint32_t i = 0; i != count; ++i) {
        AttachSectorNode(m_apFogBoxNodeFx[i], modes68[i * 2], modes68[i * 2 + 1]);
    }
}

// 0x0027a1b0 CKHkS08Enemy_DetachSectorNodesFromBones_maybe: the animated nodes go back to the sector roots (their
// controller reset), the collision volumes too, the attachments get the identity (none in DotD), and the enemy's volumes,
// projectile volumes, particle nodes (those with a mode) and fog boxes leave their parents.
void CKHkS08Enemy::DetachSectorNodesFromBones() {
    const uint8_t kind = m_ui8EnemyClassType;
    const uint32_t variant = GroupKindFlag104(kind) == 0 ? SquadFightZoneIndex(m_pGroupSquad) : 0u;
    uint32_t count = GroupNbAnimLayers(kind);  // vt+0x108
    for (uint32_t i = 0; i != count; ++i) {
        DetachSectorNode(m_apEnemySectorCpnt[variant]->GetAnimatedNode(i));  // 0x00279268
        if (m_apEnemySectorCpnt[variant]->GetAnimatedNode(i) != nullptr) {
            CAnimatedNode* node = static_cast<CAnimatedNode*>(m_apEnemySectorCpnt[variant]->GetAnimatedNode(i));
            static_cast<KBase98D*>(node->m_pController)->Reset();  // vt+0x60
        }
    }
    count = GroupNbSectorVolumes(kind);  // vt+0x10c
    for (uint32_t i = 0; i != count; ++i) DetachSectorNode(m_apEnemySectorCpnt[variant]->GetCollisionVolume(i));
    count = GroupNbAttachments(kind);  // vt+0x120
    for (uint32_t i = 0; i != count; ++i) {
        // STUB(C2.9: unreachable, 0 attachments for every kind): the attachment's target cleared and its matrix the identity (0 attachments in DotD).
        DOTD_STUB_ONCE("CKHkS08Enemy_DetachSectorNodesFromBones_maybe 0x27a1b0: attachments (none in DotD)");
    }
    const auto leave = [](IKSerializable* node) {
        if (node == nullptr) return;
        CSGLeaf* leaf = static_cast<CSGLeaf*>(node);
        if (leaf->m_pParent != nullptr) leaf->m_pParent->RemoveChild(leaf);  // vt+0x78
    };
    count = GroupNbVolumes(kind);  // vt+0x118
    for (uint32_t i = 0; i != count; ++i) leave(m_apBV[i]);
    count = GroupNbDynSpheres(kind);  // vt+0x11c
    for (uint32_t i = 0; i != count; ++i) leave(m_apBVProj[i]);
    count = GroupNbParticles(kind);  // vt+0x124
    const uint8_t* modes58 = reinterpret_cast<const uint8_t*>(m_unk58);
    for (uint32_t i = 0; i != count; ++i) {
        if (modes58[i * 2] != 0) leave(m_apParticleNodeFx[i]);
    }
    count = GroupNbFogBoxes(kind);  // vt+0x12c
    for (uint32_t i = 0; i != count; ++i) leave(m_apFogBoxNodeFx[i]);
}

// 0x00279400 CKHkS08Enemy_StopAllSounds_maybe: every sound of the sector's dictionary stopped, from the last.
void CKHkS08Enemy::StopAllSounds() {
    CKSoundDictionaryID* sounds = static_cast<CKSoundDictionaryID*>(GetSectorCpnt()->m_pUnk1c);
    for (uint32_t i = sounds->m_ui32NbKSound; i != 0;) {
        --i;
        CKSound* sound = sounds->GetSound(i);  // 0x00112bc0
        if (sound != nullptr) Sound_Stop(sound, 0);  // 0x001111b0
    }
}

// 0x002794f0 CKHkS08Enemy_StopSound
void CKHkS08Enemy::StopSound(uint8_t sound) {
    CKSound* instance = static_cast<CKSoundDictionaryID*>(GetSectorCpnt()->m_pUnk1c)->GetSound(sound);  // 0x00112bc0
    if (instance != nullptr) Sound_Stop(instance, 0);  // 0x001111b0
}

// 0x002795c0 CKHkS08Enemy_PlaySound
void CKHkS08Enemy::PlaySound(uint8_t sound, uint8_t loop, IKSerializable* node) {
    CKSound* instance = static_cast<CKSoundDictionaryID*>(GetSectorCpnt()->m_pUnk1c)->GetSound(sound);  // 0x00112bc0
    if (instance == nullptr) return;
    instance->SetAttachObject(node != nullptr ? node : m_pKGLObject);  // 0x00111350
    instance->SetLoop(loop);                                           // 0x00110fd0
    instance->Play(0.0f);                                              // 0x00111230, TOC1 +0xac8
}

// 0x0027ce18 CKHkS08Enemy_ResetAttackCooldowns_maybe: +0x2ac and the thirty timers of +0x2b0 cleared.
void CKHkS08Enemy::ResetAttackCooldowns() {
    m_unk2ac = 0.0f;
    for (uint32_t i = 0; i < 30; ++i) m_afAttackCooldowns[i] = 0.0f;
}

// 0x0027ce50 IsEnemyInDeathStates_maybe
uint8_t CKHkS08Enemy::IsInDeathStates() const {
    return (m_mainState == 0xd || m_mainState == 0xe || m_mainState == 0xf) ? 1 : 0;
}

// 0x0027ce90 CKHkS08Enemy_AddBurnGauge: the burn gauge +0x6b8 grows by amount * the component's +0x264, up to its +0x244.
void CKHkS08Enemy::AddBurnGauge(float amount) {
    const float value = ppc::fmadds(amount, m_pActiveEnemyCpnt->m_unk264, m_fFireGauge);
    m_fFireGauge = value;
    if (!(value <= m_pActiveEnemyCpnt->m_unk244)) m_fFireGauge = m_pActiveEnemyCpnt->m_unk244;
}

// 0x0027ceb8 CKHkS08Enemy_AddPoisonGauge: +0x6c0 by the component's +0x290, up to its +0x24c.
void CKHkS08Enemy::AddPoisonGauge(float amount) {
    const float value = ppc::fmadds(amount, m_pActiveEnemyCpnt->m_unk290, m_fPoisonGauge);
    m_fPoisonGauge = value;
    if (!(value <= m_pActiveEnemyCpnt->m_unk24c)) m_fPoisonGauge = m_pActiveEnemyCpnt->m_unk24c;
}

// 0x0027cee0 CKHkS08Enemy_AddStunGauge: +0x6d4 by the component's +0x320, up to its +0x260.
void CKHkS08Enemy::AddStunGauge(float amount) {
    const float value = ppc::fmadds(amount, m_pActiveEnemyCpnt->m_unk320, m_fElectricGauge);
    m_fElectricGauge = value;
    if (!(value <= m_pActiveEnemyCpnt->m_unk260)) m_fElectricGauge = m_pActiveEnemyCpnt->m_unk260;
}

// 0x0027cf08 CKHkS08Enemy_AddWindGauge_maybe: +0x6d0 by the component's +0x2e4, up to its +0x25c.
void CKHkS08Enemy::AddWindGauge(float amount) {
    const float value = ppc::fmadds(amount, m_pActiveEnemyCpnt->m_unk2e4, m_fWindGauge);
    m_fWindGauge = value;
    if (!(value <= m_pActiveEnemyCpnt->m_unk25c)) m_fWindGauge = m_pActiveEnemyCpnt->m_unk25c;
}

// 0x0027d100 CKHkS08Enemy_GetAttackSlotCategory_maybe
int32_t CKHkS08Enemy::GetAttackSlotCategory(int32_t kind) {
    if (kind == 1) return 1;
    return kind == 2 ? 2 : 0;
}

// 0x00282228 CKHkS08Enemy_ForceAlerted_maybe: the group's alert byte (+0x1bc) set and the awareness machine to state 2.
void CKHkS08Enemy::ForceAlerted(IKTime* clock) {
    static_cast<CKGrpS08Enemy*>(EnemyGroup())->m_bAlerted = 1;
    const uint8_t old = m_awareState;
    if (old != 0xff) CallAwareState(old, clock, 2, 2);
    m_awareState = 2;
    CallAwareState(2, clock, 1, old);
}

// DOTD: the wall sweep from the previous position to the current one (inlined twice in ConstrainToGroundAndNavMesh,
// at 0x00278928 and 0x00278e60): radius the component's m_afParams[0], height its +0xb4.
uint8_t IKHkEnemy::SweepFromPrevious(CKSrvCollision* collision, CLine* line, CSlideGroundEdgeDatasOut* slide) {
    line->m_start.x = m_unk140;
    line->m_start.y = m_unk144;
    line->m_start.z = m_unk148;
    line->m_VectDir.x = m_v3Position.x - m_unk140;
    line->m_VectDir.y = m_v3Position.y - m_unk144;
    line->m_VectDir.z = m_v3Position.z - m_unk148;
    return collision->ResolveSweptCylinderWalls(line, m_pEnemyCpnt->m_MoveCpnt.m_afParams[0], ComponentHeight(), slide, nullptr,
                                                nullptr, 1);  // 0x0019aa68
}

// DOTD: the component's +0xb4 read as a float (lfs), the wall sweep's height.
float IKHkEnemy::ComponentHeight() const {
    float height;
    std::memcpy(&height, &m_pEnemyCpnt->m_unkb4, sizeof(height));
    return height;
}

// DOTD: the inlined test of ConstrainToGroundAndNavMesh: the point's hint names a graph node whose box holds it.
bool IKHkEnemy::PointInNodeBox(CKSrvPathFinding* pathFinding, const CPFPoint* point) {
    const int32_t hint = static_cast<int16_t>(point->m_i16GraphNodeIndex);
    if (hint < 0 || static_cast<uint32_t>(hint) >= pathFinding->m_Graph.m_ui32GraphNodesSize) return false;
    const CBBox& box = static_cast<CKPFGraphNode*>(pathFinding->m_Graph.m_apGraphNodes[hint])->m_Sector.m_box;
    const CVector3& p = point->m_position;
    return box.m_inf.x <= p.x && box.m_sup.x >= p.x && box.m_inf.z <= p.z && box.m_sup.z >= p.z && box.m_inf.y <= p.y &&
           box.m_sup.y >= p.y;
}

// DOTD: the 64-byte matrix copy the original writes out word by word (+0x150 from the ground's vt+0x54).
void IKHkEnemy::CopyMatrix(CMatrix34* to, const CMatrix34* from) {
    to->m_right = from->m_right;
    to->m_ui32Flags = from->m_ui32Flags;
    to->m_up = from->m_up;
    to->m_ui32pad1 = from->m_ui32pad1;
    to->m_at = from->m_at;
    to->m_ui32pad2 = from->m_ui32pad2;
    to->m_pos = from->m_pos;
    to->m_ui32pad3 = from->m_ui32pad3;
}

// 0x00280ca0 CKHkS08Enemy_UpdateOffNavFlag_maybe: while the life flag 0x80 (off the nav mesh) is set, it is cleared once
// the position is back in a graph node's box and walkable there.
void CKHkS08Enemy::UpdateOffNavFlag() {
    if ((m_bitArray & 0x80u) == 0) return;
    CKSrvPathFinding* pathFinding = static_cast<CKSrvPathFinding*>(g_pEngine->m_srvPathFinding);
    CPFPoint point;
    point.m_position = m_v3Position;
    point.m_i16GraphNodeIndex = m_PFCpnt.m_Destination.m_i16GraphNodeIndex;
    if ((pathFinding->FindSectorForPoint(&point) & 0xffu) == 0) return;  // 0x001e5ca0
    if (!PointInNodeBox(pathFinding, &point)) return;
    if ((pathFinding->IsPointWalkable(&point, &m_PFCpnt.m_CharacterType) & 0xffu) == 0) return;  // 0x001e42d0
    m_bitArray = m_bitArray & 0xffffff7fu;  // rlwinm 24 / 8
}

// 0x0027d948 CKHkS08Enemy_GetGroundSurfaceType_maybe: 0 without a ground; 3 for a ground of engine flag 2; else by its
// properties: 0x800 -> 0, 0x1000 -> 1, 0x2000 -> 2, none -> 0.
uint32_t CKHkS08Enemy::GetGroundSurfaceType() const {
    const ICollisionMesh* ground = static_cast<const ICollisionMesh*>(m_GrdContDatasInOut.m_pGround);
    if (ground == nullptr) return 0;
    if (((ground->m_ba16EngineFlags >> 1) & 1u) != 0) return 3;
    const uint16_t properties = ground->m_ui16PropertiesFlags;
    if ((properties & 0x800u) != 0) return 0;
    if ((properties & 0x1000u) != 0) return 1;
    if ((properties & 0x2000u) != 0) return 2;
    return 0;
}

// 0x0027cda8 EvalRampHoldRampDown_maybe: a value that ramps up (base + t * slope) until `rampEnd`, holds for `hold`, then
// ramps down by `downSlope` per second over `rampDown`; 0 (nothing written) after that.
uint8_t EvalRampHoldRampDown(float t, float rampEnd, float hold, float rampDown, float base, float slope, float downSlope,
                             float* out) {
    if (!(t >= rampEnd)) {
        *out = ppc::fmadds(t, slope, base);
        return 1;
    }
    const float holdEnd = rampEnd + hold;
    if (t < holdEnd) {
        *out = ppc::fmadds(rampEnd, slope, base);
        return 1;
    }
    if (holdEnd + rampDown <= t) return 0;
    const float over = t - holdEnd;
    const float top = ppc::fmadds(rampEnd, slope, base);
    *out = top - over * downSlope;
    return 1;
}

namespace {
// The normalisation the angle helpers inline: the length (Math_Sqrtf of x^2 + y^2 + z^2, fused), and the vector scaled by
// its inverse when not 0.
void NormalizeInPlace(CVector3* v) {
    const float length = static_cast<float>(MathSqrtf(ppc::fmadds(v->z, v->z, ppc::fmadds(v->x, v->x, v->y * v->y))));
    if (length == 0.0f) return;
    const float inv = 1.0f / length;
    const float z = inv * v->z;
    const float x = inv * v->x;
    const float y = inv * v->y;
    v->z = z;
    v->x = x;
    v->y = y;
}
}  // namespace

// 0x0027eb88 Vec3_AngleBetween_maybe: both vectors normalised in place, then the arc cosine of their dot product clamped
// to [-1, 1].
float enemy::Vec3_AngleBetween(CVector3* a, CVector3* b) {
    NormalizeInPlace(a);
    NormalizeInPlace(b);
    float dot = ppc::fmadds(b->z, a->z, ppc::fmadds(b->x, a->x, b->y * a->y));
    if (dot <= -1.0f) {  // TOC1 +0xb28
        dot = -1.0f;
    } else if (dot >= 1.0f) {  // TOC1 +0xb44
        dot = 1.0f;
    }
    return crt::Acosf(dot);  // 0x0098e1a0 -> 0x00780c90
}

// 0x0027efc0 Vec3_SignedAngleBetween_maybe: the three vectors normalised in place; the angle between a and b, taken as
// 2 pi minus it when a points away from `side` (their dot product below 0).
float enemy::Vec3_SignedAngleBetween(CVector3* a, CVector3* b, CVector3* side) {
    NormalizeInPlace(a);
    NormalizeInPlace(b);
    NormalizeInPlace(side);
    float dot = ppc::fmadds(a->z, b->z, ppc::fmadds(a->x, b->x, a->y * b->y));
    if (dot <= -1.0f) {
        dot = -1.0f;
    } else if (dot >= 1.0f) {
        dot = 1.0f;
    }
    float angle = crt::Acosf(dot);  // 0x0098e1a0
    const float facing = ppc::fmadds(a->z, side->z, ppc::fmadds(a->x, side->x, a->y * side->y));
    if (!(facing >= 0.0f)) angle = 6.28318548f - angle;  // TOC1 +0xbac 0x40c90fdb
    return angle;
}

// 0x0027df10 GetActiveEnemyCentroid: the mean position of the enemy group's active enemies (0 when none).
CVector3 GetActiveEnemyCentroid() {
    CVector3 centre = {0.0f, 0.0f, 0.0f};
    const uint32_t count = EnemyGroup()->m_ui32NbActiveEnemies;  // +0x120
    if (count == 0) return centre;
    for (uint32_t i = 0; i < count; ++i) {
        const IKHkEnemy* enemy = static_cast<const IKHkEnemy*>(EnemyGroup()->m_apActiveEnemies[i]);  // +0x58
        centre.z = centre.z + enemy->m_v3Position.z;
        centre.x = centre.x + enemy->m_v3Position.x;
        centre.y = centre.y + enemy->m_v3Position.y;
    }
    const float inv = 1.0f / static_cast<float>(static_cast<double>(count));  // fcfid, frsp
    centre.z = inv * centre.z;
    centre.x = inv * centre.x;
    centre.y = inv * centre.y;
    return centre;
}

// 0x0027d1b8 CKHkS08Enemy_SpawnBonusDrop_maybe
void CKHkS08Enemy::SpawnBonusDrop(const CVector3* pos, const CVector3* dir, int32_t onlyMode1) {
    static_cast<KBase201*>(g_pEngine->m_srvBonus)
        ->SpawnBonuses(static_cast<CKBonusData*>(m_pActiveEnemyCpnt->m_pUnk4b4), pos, dir, pos, onlyMode1);  // 0x00126278
}

// 0x00278028 CKHkS08Enemy_EmitParticleAt: particle node `fx` (+0x54; none: nothing) gets an emission point (at most 64:
// the advanced emitter's point list, and its direction list when `direction` is given) and is lit: properties | 0x2000
// for a new point, then | 0x400 (| 0x200 too with `local`) and without 0x80000, its emission speed adjustment 0 and
// its emitter's flags | 0xa.
void CKHkS08Enemy::EmitParticleAt(uint32_t fx, const CVector3* position, const CVector3* direction, uint32_t local) {
    CParticlesNodeFx* node = static_cast<CParticlesNodeFx*>(m_apParticleNodeFx[fx]);
    if (node == nullptr) return;
    if (node->m_ui8NbActivePoints <= 0x3f) {
        RwV3d& point = node->m_pAdvEmtPointList->pointList[node->m_ui8NbActivePoints];
        point.x = position->x;
        point.y = position->y;
        point.z = position->z;
        if (direction != nullptr) {
            RwV3d& dir = node->m_pAdvEmtPointList->directionList[node->m_ui8NbActivePoints];
            dir.x = direction->x;
            dir.y = direction->y;
            dir.z = direction->z;
        }
        node->m_sgProperties |= 0x2000u;
        node->m_ui8NbActivePoints = static_cast<uint8_t>(node->m_ui8NbActivePoints + 1);
    }
    CParticlesNodeFx* lit = static_cast<CParticlesNodeFx*>(m_apParticleNodeFx[fx]);
    if (local != 0) {
        lit->m_sgProperties = (lit->m_sgProperties | 0x600u) & ~0x80000u;
    } else {
        lit->m_sgProperties = (lit->m_sgProperties | 0x400u) & ~0x80000u;
    }
    lit->m_fEmissionSpeedAdjustment = 0.0f;
    lit->m_pRpPrtStdEmitter->flag |= 0xau;
}

// 0x0027d460 Vec3_ForwardFromYaw_maybe (see CKHkS08EnemyShared.h). The original's matrix sits on the stack: its flags
// word keeps the stack's bits but the type bits 0..1 and 0x20000 (DOTD: the other bits 0; RwMatrixRotate reads only
// those).
CVector3 enemy::Vec3_RotateAboutY(float angle, const CVector3* v) {
    CMatrix34 m{};
    m.m_at = *v;
    m.m_ui32Flags = 0;
    Mat4_RotateInPlace(&m, &enemy::kAxisY, angle * 57.2957802f);  // TOC +0xb14 (0x42652ee1), 0x00240498
    return m.m_at;
}
