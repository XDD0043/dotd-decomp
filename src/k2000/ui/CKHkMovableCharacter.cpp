// CKHkMovableCharacter.cpp - reconstructed original translation unit 0x59cb80-0x5a7d20 (GAME_TOC2, main_toc2), 66 functions, 64 live.
// Primary owner: CKHkMovableCharacter (not a registered class)
// Other owners: RegisterCKHkMovableCharacterClass (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [ ] 0x59cb80  CKHkMovableCharacter_Destroy
//   [ ] 0x59cbd0  CKHkMovableCharacter_vfB4
//   [x] 0x59cbd8  CKHkMovableCharacter_ResetRuntime
//   [ ] 0x59cc50  CKHkMovableCharacter_vf70
//   [ ] 0x59cc58  CKHkMovableCharacter_vf78
//   [ ] 0x59cc60  CKHkMovableCharacter_PushTargetInsideBounds_maybe
//   [ ] 0x59d008  FUN_0059d008  [dead]
//   [ ] 0x59d030  RegisterCKHkMovableCharacterClass
//   [ ] 0x59d0a8  _GLOBAL__I_59d0a8
//   [ ] 0x59d0b8  CKHkMovableCharacter_UpdateShadowFade_maybe
//   [ ] 0x59d270  CKHkMovableCharacter_ApplySpin_maybe
//   [ ] 0x59d328  CKHkMovableCharacter_UpdateMoveSound_maybe
//   [ ] 0x59d490  CKHkMovableCharacter_UpdateLocomotionAnim_maybe
//   [ ] 0x59d738  CKHkMovableCharacter_SnapToGround_maybe
//   [ ] 0x59d870  CKHkMovableCharacter_ProcessHitContacts_maybe
//   [ ] 0x59dd60  CKHkMovableCharacter_OnLevelExit_maybe
//   [ ] 0x59dd90  CKHkMovableCharacter_Save
//   [ ] 0x59ddb8  CKHkMovableCharacter_LevelReset
//   [ ] 0x59dde0  CKHkMovableCharacter_DirectionToYaw_maybe
//   [ ] 0x59de98  CKHkMovableCharacter_DestroyArray
//   [ ] 0x59df38  CKHkMovableCharacter_GetComponentByKey_maybe
//   [ ] 0x59dfe8  CKHkMovableCharacter_ClearReferences
//   [ ] 0x59dff8  CKHkMovableCharacter_vf40
//   [ ] 0x59e050  CKHkMovableCharacter_vf38
//   [ ] 0x59e060  CKHkMovableCharacter_vf3C
//   [x] 0x59e080  CKHkMovableCharacter_Create
//   [ ] 0x59e1e0  CKHkMovableCharacter_InitMovementFields_maybe
//   [ ] 0x59e488  CKHkMovableCharacter_PostLoadInitMovement_maybe  [dead]
//   [ ] 0x59e4d8  CKHkMovableCharacter_PostLoad
//   [x] 0x59e5a0  CKHkMovableCharacter_CreateArray
//   [ ] 0x59e7a8  CKHkMovableCharacter_HandleMessage
//   [ ] 0x59ed48  CKHkMovableCharacter_UpdateFade_maybe
//   [ ] 0x59efa8  CKHkMovableCharacter_UpdateGroundContact_maybe
//   [ ] 0x59f160  CKHkMovableCharacter_ProbeGround_maybe
//   [ ] 0x59f338  CKHkMovableCharacter_SetUniformScale_maybe
//   [ ] 0x59f5c8  CKHkMovableCharacter_UpdateLookAtNearbyEntity_maybe
//   [ ] 0x59f840  CKHkMovableCharacter_UpdateInputIcon_maybe
//   [ ] 0x59fb18  CKHkMovableCharacter_UpdateHeroProximity_maybe
//   [ ] 0x59fc60  CKHkMovableCharacter_OnDeactivate
//   [ ] 0x59fe48  CKHkMovableCharacter_ApplyPoseToNode_maybe
//   [ ] 0x5a02d0  CKHkMovableCharacter_GetHeadingDirection_maybe
//   [ ] 0x5a0498  CKHkMovableCharacter_ResetTargetIfOutOfBounds_maybe
//   [ ] 0x5a0590  CKHkMovableCharacter_ClampToMoveBounds_maybe
//   [ ] 0x5a0698  CKHkMovableCharacter_CheckNavCellBlocked_maybe
//   [ ] 0x5a08c0  CKHkMovableCharacter_CheckBlockingCollision_maybe
//   [ ] 0x5a0ab0  CKHkMovableCharacter_ProbeGroundAtTarget_maybe
//   [ ] 0x5a0e50  CKHkMovableCharacter_PickRandomWanderTarget_maybe
//   [ ] 0x5a12c0  CKHkMovableCharacter_InitRuntimeState_maybe
//   [ ] 0x5a1860  CKHkMovableCharacter_ReinitRuntime
//   [ ] 0x5a1998  CKHkMovableCharacter_OnActivate
//   [ ] 0x5a1b28  CKHkMovableCharacter_TurnTowardDirectionFlat_maybe
//   [ ] 0x5a1f18  CKHkMovableCharacter_TurnTowardDirectionAligned_maybe
//   [ ] 0x5a23c0  CKHkMovableCharacter_Update
//   [x] 0x5a30f0  CKHkMovableCharacter_Load
//   [ ] 0x5a44e8  CKHkMovableCharacter_UpdateRandomActionTimer_maybe
//   [ ] 0x5a4668  CKHkMovableCharacter_State3
//   [ ] 0x5a4800  CKHkMovableCharacter_ChooseState_maybe
//   [ ] 0x5a4998  CKHkMovableCharacter_MoveAlongPath_maybe
//   [ ] 0x5a4ef8  CKHkMovableCharacter_State1
//   [ ] 0x5a5010  CKHkMovableCharacter_State5
//   [ ] 0x5a5698  CKHkMovableCharacter_State4
//   [ ] 0x5a5f00  CKHkMovableCharacter_State2
//   [ ] 0x5a64e8  CKHkMovableCharacter_State0
//   [ ] 0x5a6ce8  CKHkMovableCharacter_MoveToWithPathfinding_maybe
//   [ ] 0x5a7080  CKHkMovableCharacter_TurnTowardPoint_maybe
//   [ ] 0x5a7458  CKHkMovableCharacter_State6
//
//   [ ] 0x9cba10  CKHkMovableCharacter_IsKindOf  [inline]
//   [ ] 0x9cba58  CKHkMovableCharacter_GetClassGroup  [inline]
//   [ ] 0x9cba60  CKHkMovableCharacter_GetClassId  [inline]
//   [ ] 0x9cba68  CKHkMovableCharacter_IsVisible_maybe  [inline]
//   [ ] 0x9cba80  CKHkMovableCharacter_DeletingDestructor  [inline]
//   [ ] 0x9cbb20  CKHkMovableCharacter_Destructor  [inline]
#include "k2000/ui/CKHkMovableCharacter.h"

#include "k2000/io/IKFile.h"
#include "k2000/memory/Mem.h"
#include "k2000/core/Stub.h"

// Inlined in 0x0059e080 CKHkMovableCharacter_Create: the ground-contact defaults, +0x7c = 0 (TOC2 -0x6abc,
// 0.0f), the embedded CKPathFindingCpnt's constructor, an empty reference vector of capacity 1 and the two
// bytes +0x2c4/+0x2c5 = 0xff.
CKHkMovableCharacter::CKHkMovableCharacter() {
    m_unk7c.x = 0.0f;
    m_unk7c.z = 0.0f;
    m_unk7c.y = 0.0f;
    m_unkF0 = 0;
    m_vUnk294.m_ui32NbElt = 1;
    m_vUnk294.m_ui32NbUsedElt = 0;
    m_vUnk294.m_pBlock = nullptr;
    m_unk2c5 = 0xff;
    m_unk2c4 = 0xff;
}

// 0x005a30f0 CKHkMovableCharacter_Load: no serialization-type branch of its own.
int32_t CKHkMovableCharacter::Load(IKFile* file, int32_t type) {
    IKHook::Load(file, type);
    ReadU8(file, &m_unk148);
    ReadU32LE(file, &m_unk140);
    ReadU32LEWords(file, reinterpret_cast<uint32_t*>(&m_unk14c), 3);  // one Read(0xc), then three swaps
    ReadU32LEWords(file, reinterpret_cast<uint32_t*>(&m_unk158), 3);
    ReadU32LEWords(file, reinterpret_cast<uint32_t*>(&m_unk164), 3);
    ReadU32LE(file, &m_unk170);
    ReadU8(file, &m_unk174);
    for (uint32_t i = 0; i < 0x1e; ++i) ReadU32LE(file, &m_unk178[i]);
    for (uint32_t i = 0; i < 4; ++i) ReadU32LE(file, &m_unk268[i]);
    ReadU32LE(file, &m_unk2ac);
    ReadU32LE(file, &m_unk2bc);
    IKFile_ReadRef(file, &m_unk138);
    IKFile_ReadRef(file, &m_unk13c);
    IKFile_ReadRef(file, &m_unk144);
    IKFile_ReadRef(file, &m_unk290);
    ReadU32LEWords(file, reinterpret_cast<uint32_t*>(&m_unk278), 3);
    ReadU32LEWords(file, reinterpret_cast<uint32_t*>(&m_unk284), 3);
    uint16_t count = 0;
    ReadU16LE(file, &count);
    if (count == 0) {
        m_vUnk294.m_ui32NbElt = 1;
        m_vUnk294.m_pBlock =
            static_cast<IKSerializable**>(Mem_AllocAligned16(static_cast<uint32_t>(sizeof(IKSerializable*))));
    } else {
        m_vUnk294.m_ui32NbElt = count;
        m_vUnk294.m_pBlock = static_cast<IKSerializable**>(
            Mem_AllocAligned16(count * static_cast<uint32_t>(sizeof(IKSerializable*))));
        if (m_vUnk294.m_ui32NbElt < count) {  // as in the original: cannot happen
            uint32_t capacity = count + 1u;
            if (capacity == 0) capacity = 1;
            m_vUnk294.m_pBlock = static_cast<IKSerializable**>(
                Mem_ReallocAligned16(m_vUnk294.m_pBlock, capacity * static_cast<uint32_t>(sizeof(IKSerializable*))));
            m_vUnk294.m_ui32NbElt = capacity;
        }
        m_vUnk294.m_ui32NbUsedElt = count;
        for (uint32_t i = 0; i < count; ++i) IKFile_ReadObjectRef(file, &m_vUnk294.m_pBlock[i]);
    }
    IKFile_ReadRef(file, &m_unk2a0[0]);
    IKFile_ReadRef(file, &m_unk2a0[1]);
    IKFile_ReadRef(file, &m_unk2a0[2]);
    m_unk300.Load(file, type);
    m_unk308.Load(file, type);
    m_unk310.Load(file, type);
    m_PFCpnt.CKPathFindingCpnt::Load(file, type);
    IKFile_ReadRef(file, &m_unk2b0[0]);
    IKFile_ReadRef(file, &m_unk2b0[1]);
    IKFile_ReadRef(file, &m_unk2b0[2]);
    return 1;
}

// 0x0059cbd8 CKHkMovableCharacter_ResetRuntime: bit 9 of the +0x68 word cleared, the seven-state handler table
// at +0x2c8 refilled (pairs: the state's function descriptor and a zero adjustment, the PS3 pointer-to-member
// layout; State6 is stored first at +0x2f8). STUB(C2.2): native state handlers replace the descriptor words.
void CKHkMovableCharacter::Start() {
    m_unk64[1] &= 0xfffffdffu;
    m_unk2c8[12] = 0x00bed388u;  // State6 (+0x2f8)
    m_unk2c8[13] = 0;
    m_unk2c8[0] = 0x00bed370u;   // State0 (+0x2c8)
    m_unk2c8[2] = 0x00bed2c0u;   // State1 (+0x2d0)
    m_unk2c8[4] = 0x00bed368u;   // State2 (+0x2d8)
    m_unk2c8[6] = 0x00bed228u;   // State3 (+0x2e0)
    m_unk2c8[8] = 0x00bed360u;   // State4 (+0x2e8)
    m_unk2c8[10] = 0x00bed358u;  // State5 (+0x2f0)
    m_unk2c8[1] = 0;
    m_unk2c8[3] = 0;
    m_unk2c8[5] = 0;
    m_unk2c8[7] = 0;
    m_unk2c8[9] = 0;
    m_unk2c8[11] = 0;
}
