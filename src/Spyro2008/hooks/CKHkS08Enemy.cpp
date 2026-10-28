// CKHkS08Enemy.cpp - reconstructed original translation unit 0x276f58-0x285340 (GAME_TOC1, main_toc1), 96 functions, 89 live.
// Primary class: CKHkS08Enemy  key 0x26c2  category Hook  size 0x8f8  vtable 0xb22078
// Other owners: IKHkEnemy (8), Vec3 (3), GetEnemyGroup (1), GetHeroGroup (1), Contact (1), Volume (1), CKHkS08EnemyParent (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [ ] 0x276f58  GetEnemyGroup
//   [ ] 0x276f70  GetHeroGroup
//   [ ] 0x276f88  CKHkS08Enemy_ClearVolumeGroupFlags
//   [ ] 0x277008  CKHkS08Enemy_SetVolumeGroupFlags
//   [ ] 0x277088  Contact_GetOtherVolume
//   [ ] 0x277160  Volume_DetachFromOwner_maybe  [dead]
//   [ ] 0x2771c0  CKHkS08Enemy_GetSectorIndex_maybe
//   [x] 0x277240  CKHkS08Enemy_AllocAnimLayerSlots_maybe
//   [ ] 0x2773e0  CKHkS08Enemy_UnregisterShadowCaster_maybe
//   [ ] 0x277448  CKHkS08Enemy_RegisterShadowCaster_maybe  [dead]
//   [x] 0x277528  IKHkEnemy_PostLoad
//   [ ] 0x277600  CKHkS08EnemyParent_1402_Save
//   [ ] 0x277628  IKHkEnemy_LevelReset
//   [ ] 0x277650  IKHkEnemy_Update
//   [ ] 0x277670  CKHkS08Enemy_DisableVolumeGroup
//   [ ] 0x277738  CKHkS08Enemy_EnableVolumeGroup
//   [ ] 0x277800  CKHkS08Enemy_DisableVolume
//   [ ] 0x277850  CKHkS08Enemy_EnableVolume
//   [ ] 0x2778a0  CKHkS08Enemy_FreeBuffers_maybe
//   [ ] 0x277c90  IKHkEnemy_TeleportTo_maybe
//   [ ] 0x277d08  CKHkS08Enemy_ReleaseDynSphere_maybe
//   [ ] 0x277dc8  CKHkS08Enemy_SetDynSphereFlags
//   [x] 0x277df8  IKHkEnemy_ResetMovementState_maybe
//   [ ] 0x277f50  CKHkS08Enemy_ClearDynSphereFlags
//   [ ] 0x277f80  CKHkS08Enemy_SetTrailRibbonEndpoints_maybe
//   [ ] 0x278008  IKHkEnemy_vf124
//   [ ] 0x278020  IKHkEnemy_HandleMessage
//   [ ] 0x278028  CKHkS08Enemy_EmitParticleAt
//   [ ] 0x2781a0  CKHkS08Enemy_ConstructBase_2_maybe  [dead]
//   [ ] 0x278330  IKHkEnemy_ConstrainToGroundAndNavMesh_maybe
//   [x] 0x2790d8  CKHkS08Enemy_ConstructBase_maybe
//   [ ] 0x279268  CKHkS08Enemy_DetachSectorNode_maybe
//   [ ] 0x279400  CKHkS08Enemy_StopAllSounds_maybe
//   [ ] 0x2794f0  CKHkS08Enemy_StopSound
//   [ ] 0x2795c0  CKHkS08Enemy_PlaySound
//   [ ] 0x2796e8  CKHkS08Enemy_UpdateShadowCaster
//   [ ] 0x279998  CKHkS08Enemy_EnableCollisionSphere_maybe
//   [ ] 0x27a1b0  CKHkS08Enemy_DetachSectorNodesFromBones_maybe
//   [ ] 0x27a748  CKHkS08Enemy_UnregisterActive
//   [ ] 0x27aac0  CKHkS08Enemy_BindAttachmentToNode_maybe
//   [ ] 0x27ad40  CKHkS08Enemy_AttachSectorNode_maybe
//   [ ] 0x27b048  CKHkS08Enemy_AttachSectorNodesToBones_maybe
//   [ ] 0x27b590  CKHkS08Enemy_RegisterActive
//   [x] 0x27b908  IKHkEnemy_Load
//   [ ] 0x27c700  CKHkS08Enemy_StopTrailRibbon_maybe
//   [ ] 0x27c7b0  CKHkS08Enemy_StartTrailRibbon_maybe
//   [x] 0x27cd58  CKHkS08Enemy_Delete
//   [ ] 0x27cda8  EvalRampHoldRampDown_maybe
//   [ ] 0x27ce18  CKHkS08Enemy_ResetAttackCooldowns_maybe
//   [ ] 0x27ce50  IsEnemyInDeathStates_maybe
//   [ ] 0x27ce90  CKHkS08Enemy_AddBurnGauge
//   [ ] 0x27ceb8  CKHkS08Enemy_AddPoisonGauge
//   [ ] 0x27cee0  CKHkS08Enemy_AddStunGauge
//   [ ] 0x27cf08  CKHkS08Enemy_AddWindGauge_maybe
//   [ ] 0x27cf30  CKHkS08Enemy_SetPartsFlagForCategory_maybe
//   [ ] 0x27d018  CKHkS08Enemy_ClearPartsFlagForCategory_maybe
//   [ ] 0x27d100  CKHkS08Enemy_GetAttackSlotCategory_maybe
//   [ ] 0x27d138  CKHkS08Enemy_vf148
//   [ ] 0x27d1b8  CKHkS08Enemy_SpawnBonusDrop_maybe
//   [ ] 0x27d208  CKHkS08Enemy_PickSpotAlongTargetAim_maybe
//   [ ] 0x27d460  Vec3_ForwardFromYaw_maybe
//   [x] 0x27d548  CKHkS08Enemy_Construct
//   [x] 0x27d650  CKHkS08Enemy_DeleteArray
//   [ ] 0x27d6f0  CKHkS08Enemy_IsState13_maybe  [dead]
//   [ ] 0x27d708  CKHkS08Enemy_EnableAttackVolumes_maybe
//   [ ] 0x27d8a0  RegisterCKHkS08EnemyClass
//   [ ] 0x27d928  _GLOBAL__D_27d928
//   [ ] 0x27d938  _GLOBAL__I_27d938
//   [ ] 0x27d948  CKHkS08Enemy_GetGroundSurfaceType_maybe
//   [ ] 0x27d9b8  CKHkS08Enemy_UpdateAttackerHitCooldowns_maybe
//   [ ] 0x27db68  CKHkS08Enemy_Construct_2
//   [ ] 0x27dc70  CKHkS08Enemy_IsWithinHeroRangeOfCameraFocus_maybe
//   [ ] 0x27de70  CKHkS08Enemy_ResolveSweptCylinderWalls_maybe  [dead]
//   [ ] 0x27df10  GetActiveEnemyCentroid
//   [ ] 0x27e040  CKHkS08Enemy_AdvanceSpeedProfileMove_maybe  [dead]
//   [ ] 0x27e148  CKHkS08Enemy_DeletingDestructor
//   [x] 0x27e258  CKHkS08Enemy_CreateArray
//   [x] 0x27e408  CKHkS08Enemy_Create
//   [ ] 0x27e520  CKHkS08Enemy_PickAttackSpotNearHeroAnyAngle_maybe
//   [ ] 0x27ea88  CKHkS08Enemy_Destructor
//   [ ] 0x27eb88  Vec3_AngleBetween_maybe
//   [ ] 0x27ed08  CKHkS08Enemy_BreakArmourPart
//   [ ] 0x27efc0  Vec3_SignedAngleBetween_maybe
//   [ ] 0x27f1d8  CKHkS08Enemy_BaseDestructor
//   [ ] 0x27f2d8  CKHkS08Enemy_ClampToNavSectors_maybe
//   [ ] 0x27f8c0  CKHkS08Enemy_IsReachablePoint_maybe
//   [ ] 0x27fce8  CKHkS08Enemy_PickRandomReachablePoint_maybe
//   [ ] 0x280190  CKHkS08Enemy_PickAttackSpotNearHero_maybe
//   [ ] 0x2808e8  CKHkS08Enemy_ChooseMoveTarget_maybe
//   [ ] 0x280ca0  CKHkS08Enemy_UpdateOffNavFlag_maybe
//   [ ] 0x280e30  CKHkS08Enemy_ComputeAttackApproachPoint_maybe
//   [ ] 0x2820e8  CKHkS08Enemy_ForceState16_maybe
//   [ ] 0x282228  CKHkS08Enemy_ForceAlerted_maybe
//   [ ] 0x282398  CKHkS08Enemy_ForceAwarenessState0_maybe  [dead]
//   [ ] 0x2824d0  CKHkS08Enemy_ProcessContacts
//   [ ] 0x283b08  CKHkS08Enemy_ResolveGroundAndApplyTransform_maybe
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

#include <cstring>

#include "Renderware/rwcore/RwMatrix.h"
#include "k2000/io/IKFile.h"
#include "k2000/logic/CDefaultGameManager.h"
#include "k2000/memory/Mem.h"
#include "k2000/misc/Engine.h"
#include "k2000/misc/IKGrpEnemy.h"

// 0x002790d8 CKHkS08Enemy_ConstructBase_maybe: IKHkEnemy's constructor. The bases, the ground-contact
// pair and the path-finding component set their own defaults; then the array pointers (not +0x3c) and
// +0x164/+0x1ac are cleared.
IKHkEnemy::IKHkEnemy() {
    m_unk164 = nullptr;
    m_unk1AC = 0;
    m_unk2C = nullptr;
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
    m_unk158 = CVector3{0.0f, 0.0f, 0.0f};
    m_unk174 = m_pKGLObject;
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
        m_unk164 = nullptr;
        return;
    }
    m_unk164 = new SEnemyAnimLayerSlot*[layers];  // OperatorNewArray(layers << 2)
    for (uint32_t layer = 0; layer < layers; ++layer) {
        const uint32_t count = group->GetNbAnimLayerSlots(m_ui8EnemyClassType, static_cast<uint8_t>(layer));  // vt+0x130
        if (count == 0) {
            m_unk164[layer] = nullptr;
        } else {
            // OperatorNewArray(count * 0x2c + 4): the count cookie, then the slots. The first two words are the PS3
            // vtables of the layer object (0xb22068) and of the AnimBlendSlot embedded at +0x04 (0xb16530). STUB(C2.7):
            // kept as words; the layers are only driven by the enemy's animation update (CKHkS08Enemy_AdvanceAnimLayer_maybe
            // 0x286220, _AdvanceAnimation_maybe 0x2866d0: the first fight).
            SEnemyAnimLayerSlot* slots = new SEnemyAnimLayerSlot[count];
            for (uint32_t i = 0; i < count; ++i) {
                slots[i].m_unk00 = 0x00b22068u;
                slots[i].m_unk04 = 0x00b16530u;
                slots[i].m_unk08 = 0;
            }
            m_unk164[layer] = slots;
        }
    }
}

// 0x00277528 IKHkEnemy_PostLoad: IKLife_PostLoad, and for the level data the runtime reset (vt+0xc4), a matrix
// (the identity) and the animation-layer slots.
int32_t IKHkEnemy::PostLoad(int32_t type) {
    PostLoadLife(type);
    if (type == K_LEVEL_PLATEFORMS) {
        ResetRuntimeState();
        m_unk150 = reinterpret_cast<CMatrix34*>(RwMatrixCreate());  // RwMatrixCreate_Thunk 0x0023fa68
        m_unk150->m_ui32Flags = 0x20003u;
        m_unk150->m_right = CVector3{1.0f, 0.0f, 0.0f};
        m_unk150->m_pos = CVector3{0.0f, 0.0f, 0.0f};
        m_unk150->m_at = CVector3{0.0f, 0.0f, 1.0f};
        m_unk150->m_up = CVector3{0.0f, 1.0f, 0.0f};
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
        m_unk18C = static_cast<IKSerializable**>(
            Mem_CallocAligned16(static_cast<uint32_t>(sizeof(IKSerializable*)), count));
        IKFile_ReadObjectRefArray(file, m_unk18C, count);
    }
    ReadRawU16Array(file, &m_unk20);
    ReadRawU16Array(file, &m_unk24);
    ReadRawU16Array(file, &m_unk28);
    ReadU8(file, &count);
    if (count != 0) {
        m_unk2C = static_cast<IKSerializable**>(Mem_AllocAligned16(count * static_cast<uint32_t>(sizeof(IKSerializable*))));
        IKFile_ReadObjectRefArray(file, m_unk2C, count);
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
    m_unk158 = CVector3{0.0f, 0.0f, 0.0f};  // the zero vector 0xc50d64
    m_PFCpnt.Load(file, K_LEVEL_PLATEFORMS);
    ReadF32LE(file, &m_unk16C);
    ReadU32LE(file, &m_unk170);
    m_unk174 = nullptr;
    IKFile_ReadRef(file, &m_unk188);
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
    m_unk3A1 = 0xff;
    m_unk3A0 = 0xff;
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
    m_unk539 = 0xff;
    m_unk538 = 0xff;
    m_unk559 = 0xff;
    m_unk558 = 0xff;
    m_unk5E9 = 0xff;
    m_unk5E8 = 0xff;
    // m_damage8BC: CKS08Damage_Construct(this + 0x8bc) 0x4ebc70, the last call of the original (member constructor).
}
