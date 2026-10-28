// CKTransformElement.cpp - reconstructed original translation unit 0x3dc3d8-0x3e0248 (GAME_TOC1, main_toc1), 32 functions, 30 live.
// Primary class: CKTransformElement  key 0x954c  category Logic  size 0x154  vtable 0xb24888
// Other owners: CKWindBeam (2)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x3dc3d8  CKTransformElement_Delete
//   [x] 0x3dc428  CKTransformElement_Construct
//   [ ] 0x3dc438  CKTransformElement_Construct_2  [dead]
//   [x] 0x3dc448  CKTransformElement_GetAbilityId
//   [ ] 0x3dc450  CKTransformElement_GetFamilyId
//   [ ] 0x3dc458  CKTransformElement_Start
//   [ ] 0x3dc690  CKTransformElement_Stop
//   [ ] 0x3dc720  CKTransformElement_End
//   [ ] 0x3dc800  CKTransformElement_ApplyHeroControl
//   [x] 0x3dcea0  CKTransformElement_ResetRuntime
//   [ ] 0x3dcee8  CKTransformElement_StopFx
//   [ ] 0x3dcf40  CKTransformElement_SwitchLoopAnim_maybe
//   [x] 0x3dcfc8  CKTransformElement_DeleteArray
//   [ ] 0x3dd068  CKTransformElement_StartEmitterFx
//   [ ] 0x3dd330  RegisterCKTransformElementClass
//   [ ] 0x3dd3b8  _GLOBAL__D_3dd3b8
//   [ ] 0x3dd3c8  _GLOBAL__I_3dd3c8
//   [ ] 0x3dd3d8  CKTransformElement_ApplyDamageParams
//   [ ] 0x3dd958  CKTransformElement_Update
//   [x] 0x3de3b8  CKTransformElement_CreateArray
//   [x] 0x3de448  CKTransformElement_Create
//   [ ] 0x3de480  CKTransformElement_RecursiveRegistration
//   [x] 0x3de488  CKTransformElement_PostLoad
//   [ ] 0x3de4d0  CKTransformElement_Destroy
//   [ ] 0x3de4d8  CKTransformElement_BaseDestructor
//   [x] 0x3de4f8  CKTransformElement_Load
//   [ ] 0x3df3a0  CKTransformElement_DeletingDestructor
//   [ ] 0x3df3e8  CKTransformElement_Destructor
//   [ ] 0x3df408  CKTransformElement_Save
//   [ ] 0x3e01e8  CKWindBeam_Delete
//   [ ] 0x3e0238  CKWindBeam_GetAbilityId
//   [ ] 0x3e0240  KStub_Nop_3e0240  [dead]
//
//   [ ] 0x9c08d0  CKTransformElement_GetClassType  [inline]
//   [ ] 0x9c08d8  CKTransformElement_GetClassID  [inline]
//   [ ] 0x9c08e0  CKTransformElement_SetFxActive  [inline]
//   [ ] 0x9c08e8  CKTransformElement_vf74  [inline]
//   [ ] 0x9c08f0  CKTransformElement_UpdateAttack_maybe  [inline]
//   [ ] 0x9c08f8  CKTransformElement_IsKindOfClass  [inline]
#include "k2000/logic/CKTransformElement.h"

#include "k2000/io/IKFile.h"

// 0x003de488 CKTransformElement_PostLoad: vt+0x6c (ResetRuntime) for every type.
int32_t CKTransformElement::PostLoad(int32_t /*type*/) {
    ResetRuntime();
    return 1;
}

// 0x003dcea0 CKTransformElement_ResetRuntime. Not written: +0x134.
void CKTransformElement::ResetRuntime() {
    m_unk140 = -1.0f;  // TOC +0x41ac (0xbf800000)
    m_unk144 = 0;
    m_unk148 = 1;
    m_unk13c = 0xff;
    m_unk13d = 0;
    m_unk12c = 0;
    m_levelIndex = 0;
    m_unk130[0] = 0;
    m_unk130[1] = 0;
    m_unk130[2] = 0;
    m_unk130[3] = 0;
    m_unk138 = 0;
}

// 0x003de4f8 CKTransformElement_Load: level data only (type K_LEVEL_PLATEFORMS). Three per-level records
// (twelve words and two flag bytes each), then the movement/turn settings, the damage and emitter references.
// 286 bytes.
int32_t CKTransformElement::Load(IKFile* file, int32_t type) {
    if (type == 0) {
        for (int32_t i = 0; i < 3; ++i) {
            ReadS32LE(file, &m_damage[i]);
            ReadF32LE(file, &m_cooldown[i]);
            ReadS32LE(file, &m_manaPerSecond[i]);
            ReadF32LE(file, &m_dmgParam2C[i]);
            ReadF32LE(file, &m_dmgParam28[i]);
            ReadF32LE(file, &m_dmgEffect0[i]);
            ReadF32LE(file, &m_dmgEffect1[i]);
            ReadF32LE(file, &m_dmgEffect2[i]);
            ReadF32LE(file, &m_dmgEffect4[i]);
            ReadF32LE(file, &m_dmgEffect6[i]);
            ReadF32LE(file, &m_dmgEffect5[i]);
            ReadF32LE(file, &m_dmgEffect7[i]);
            ReadU8(file, &m_dmgFlag34[i]);
            ReadU8(file, &m_dmgFlag35[i]);
        }
        ReadU8(file, &m_airPerm1Perm0TurnEnable[0]);
        ReadU8(file, &m_airPerm1Perm0TurnEnable[1]);
        ReadU8(file, &m_airPerm1Perm0TurnEnable[2]);
        ReadF32LE(file, &m_airTurnAB[0]);
        ReadF32LE(file, &m_airTurnAB[1]);
        ReadF32LE(file, &m_airMoveSpeed);
        ReadU8(file, &m_mode1Perm1Perm0TurnEnable[0]);
        ReadU8(file, &m_mode1Perm1Perm0TurnEnable[1]);
        ReadU8(file, &m_mode1Perm1Perm0TurnEnable[2]);
        ReadF32LE(file, &m_mode1TurnAB[0]);
        ReadF32LE(file, &m_mode1TurnAB[1]);
        ReadF32LE(file, &m_mode1MoveSpeed);
        ReadU8(file, &m_airMode1P11f8Enable[0]);
        ReadU8(file, &m_airMode1P11f8Enable[1]);
        ReadF32LE(file, &m_airMode1P11f8[0]);
        ReadF32LE(file, &m_airMode1P11f8[1]);
        ReadF32LE(file, &m_dmgEffect3[0]);
        ReadF32LE(file, &m_dmgEffect3[1]);
        ReadF32LE(file, &m_dmgEffect3[2]);
        IKFile_ReadRef(file, &m_elementDamage);
        ReadU8(file, &m_groundPerm1Perm0TurnEnable[0]);
        ReadU8(file, &m_groundPerm1Perm0TurnEnable[1]);
        ReadU8(file, &m_groundPerm1Perm0TurnEnable[2]);
        ReadF32LE(file, &m_groundTurnAB[0]);
        ReadF32LE(file, &m_groundTurnAB[1]);
        ReadF32LE(file, &m_groundMoveSpeed);
        ReadU8(file, &m_groundP11f8Enable);
        ReadF32LE(file, &m_groundP11f8);
        ReadF32LE(file, &m_groundFxIntervalBase);
        ReadF32LE(file, &m_groundFxIntervalRange);
        ReadF32LE(file, &m_unkE0);
        ReadF32LE(file, &m_cooldownForced[0]);
        ReadF32LE(file, &m_cooldownForced[1]);
        ReadF32LE(file, &m_cooldownForced[2]);
        IKFile_ReadRef(file, &m_emitterFxData);
        ReadF32LE(file, &m_damageParam10[0]);
        ReadF32LE(file, &m_damageParam10[1]);
        ReadF32LE(file, &m_damageParam10[2]);
        ReadF32LE(file, &m_dmgRandBase);
        ReadF32LE(file, &m_dmgRandRange);
        ReadS32LE(file, &m_manaRequired[0]);
        ReadS32LE(file, &m_manaRequired[1]);
        ReadS32LE(file, &m_manaRequired[2]);
    }
    return 1;
}
