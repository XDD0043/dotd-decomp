// Reconstructed original translation unit: 0x42ffb0-0x43ef98 (GAME_TOC1, main_toc1), 90 functions, 76 live.
// Primary class: CKHkPushObstacle  key 0x842  category Hook  size 0x1e8  vtable 0xb263e8
// Other owners: CKHkRollingBarrel (2), IsDragon2AttachedToObject (1), IsDragon1AttachedToObject (1), IsDragon0AttachedToObject (1), GetHeroModelNodeByDragonIndex (1), Contact (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x42ffb0  CKHkPushObstacle_Delete  (DOTD_DECLARE_FACTORIES(CKHkPushObstacle))
//   [ ] 0x430000  CKHkPushObstacle_ResetRuntimeState_maybe  [dead]
//   [ ] 0x430090  CKHkPushObstacle_IsSlotNotExcluded_maybe  [dead]
//   [ ] 0x430100  CKHkPushObstacle_CountNonNullEntriesOnCurrentSide_maybe  [dead]
//   [ ] 0x430188  CKHkPushObstacle_ComputeLocalBox_maybe  [dead]
//   [ ] 0x430228  CKHkPushObstacle_IsCurrentSideEnabled_maybe  [dead]
//   [ ] 0x430258  RegisterCKHkPushObstacleClass
//   [ ] 0x4302d0  _GLOBAL__I_4302d0
//   [ ] 0x4302e0  CKHkPushObstacle_GetFacingAxisVectors_maybe  [dead]
//   [x] 0x4304a8  CKHkPushObstacle_SnapToGroundAndBlockNav_maybe
//   [x] 0x430c78  CKHkPushObstacle_AttachSounds  (KGLObjectAttached, vt+0xb4)
//   [ ] 0x430d30  CKHkPushObstacle_FindNearestHotSpot_maybe  [dead]
//   [x] 0x430f20  CKHkPushObstacle_PlayPushAnimsOnMove_maybe
//   [x] 0x431028  CKHkPushObstacle_AreAllPushersReady_maybe
//   [x] 0x431180  CKHkPushObstacle_FreeBuffers_maybe  (VfC0, vt+0xc0)
//   [x] 0x4311e8  CKHkPushObstacle_SetDefaultState
//   [x] 0x431240  CKHkPushObstacle_Resume  (the actor base's KStub_Nop_3f6e60: inherited)
//   [x] 0x431268  CKHkPushObstacle_Pause  (the actor base's KStub_Nop_3f6e58: inherited)
//   [x] 0x431290  CKHkPushObstacle_Stop  (the actor base's 0x3f6e50: inherited)
//   [x] 0x4312b8  CKHkPushObstacle_Start
//   [x] 0x431318  CKHkPushObstacle_PostLoad
//   [ ] 0x431358  CKHkPushObstacle_Save
//   [x] 0x431380  CKHkPushObstacle_RecursiveRegistration  (the actor base's 0x3f6ee8: inherited)
//   [ ] 0x4313a8  CKHkPushObstacle_Construct  [dead]
//   [x] 0x431440  CKHkPushObstacle_DeleteArray  (DOTD_DECLARE_FACTORIES)
//   [x] 0x4314e0  IsDragon2AttachedToObject  (the GetInfo accessor of 0xaa, IsDragonAttachedToObject in the .cpp)
//   [x] 0x431560  IsDragon1AttachedToObject  (the GetInfo accessor of 0xa9)
//   [x] 0x4315e0  IsDragon0AttachedToObject  (the GetInfo accessor of 0xa8)
//   [ ] 0x431660  GetHeroModelNodeByDragonIndex  [dead: no caller; its OPD 0xbb8e40 is referenced nowhere in the EBOOT (port-last Z2)]
//   [x] 0x4316a0  CKHkPushObstacle_Destroy  (the actor base's 0x3f6e08: inherited)
//   [x] 0x4316c8  CKHkPushObstacle_PlayIdleAnims_maybe
//   [x] 0x4317b0  CKHkPushObstacle_PlayFinalAnims_maybe
//   [x] 0x4318c8  CKHkPushObstacle_SetAnimTimeAll_maybe
//   [x] 0x431950  CKHkPushObstacle_AdvanceAnimTime_maybe
//   [x] 0x4319d8  CKHkPushObstacle_PlayPushAnimsForReadyPushers_maybe
//   [x] 0x431ad8  CKHkPushObstacle_ApplyStatePreset_maybe  (ApplyStatePreset, vt+0xc8)
//   [ ] 0x431cb8  CKHkPushObstacle_SetFlag158Bit4_maybe  [dead]
//   [ ] 0x431cd8  CKHkPushObstacle_SetFlag158Bit5_maybe  [dead]
//   [x] 0x431cf8  CKHkPushObstacle_Destructor  (the header's destructor)
//   [x] 0x431d70  CKHkPushObstacle_UpdatePusherHandFxPoints_maybe
//   [x] 0x431f78  CKHkPushObstacle_PlayImpactFx_maybe
//   [ ] 0x432678  CKHkPushObstacle_Destructor_2  [dead]
//   [x] 0x4326f0  CKHkPushObstacle_DeletingDestructor  (the header's destructor)
//   [ ] 0x432778  CKHkPushObstacle_Construct_2  [dead]
//   [x] 0x432810  CKHkPushObstacle_GetInfo
//   [ ] 0x432a78  CKHkPushObstacle_FindNearestHotSpotOnSide_maybe  [dead]
//   [x] 0x432bf0  CKHkPushObstacle_SetNavBoxBlocked_maybe
//   [x] 0x432d30  CKHkPushObstacle_ResetPushState_maybe
//   [x] 0x432e20  CKHkPushObstacle_StopMoveFeedbackFx_maybe
//   [x] 0x432f18  CKHkPushObstacle_StartMoveFeedback_maybe
//   [x] 0x4335b0  CKHkPushObstacle_CreateArray  (DOTD_DECLARE_FACTORIES)
//   [x] 0x4336f8  CKHkPushObstacle_Create  (DOTD_DECLARE_FACTORIES: the header's constructor)
//   [x] 0x4337a0  CKHkPushObstacle_StartPushFxAndSound_maybe  (the push effects and loop: state 3)
//   [x] 0x434008  CKHkPushObstacle_SnapPushersToGrabPoints_maybe  (state 2)
//   [x] 0x4341b8  CKHkPushObstacle_StopMoveFeedbackAndCollision_maybe  (state 2)
//   [x] 0x4342c0  CKHkPushObstacle_CheckGrabPointsForHero_maybe  (MessageProc 0x93f)
//   [x] 0x434728  CKHkPushObstacle_AttachHeroesToGrabPoints_maybe  (MessageProc 0x93f, UpdateHeroPush)
//   [x] 0x4351a8  CKHkPushObstacle_IsHeroInGrabArea_maybe  (SelectNextState, MessageProc 0x300)
//   [x] 0x4358b8  CKHkPushObstacle_UnblockGrabPointCells_maybe  (state 4)
//   [x] 0x435a80  CKHkPushObstacle_SetPusherCellsBlocked_maybe  (no caller: Update inlines it twice; Update calls this port)
//   [x] 0x435b98  CKHkPushObstacle_ShowInputIcon_maybe
//   [x] 0x435e70  CKHkPushObstacle_StepGridCoordAndFireSignals_maybe  (BeginMove)
//   [x] 0x436150  CKHkPushObstacle_UpdateHeroInteraction_maybe  (states 1, 2, 3)
//   [x] 0x436630  CKHkPushObstacle_ComputeFootprintCorner_maybe  (CellPosition with the cells +0x196 / +0x197)
//   [x] 0x436ba8  CKHkPushObstacle_IsHeroOnMoveTrajectory_maybe  (MessageProc 0x300)
//   [x] 0x4371b0  CKHkPushObstacle_UpdateMoveStep_maybe  (state 2)
//   [x] 0x4373d8  CKHkPushObstacle_ComputeRestPosition_maybe  (CellPosition with the cells +0x194 / +0x195)
//   [x] 0x437950  CKHkPushObstacle_CanPushInDirection_maybe  (ChoosePushState)
//   [x] 0x4381e0  CKHkPushObstacle_ProbeMoveTarget_maybe  (SelectNextState)
//   [x] 0x438550  CKHkPushObstacle_BeginMove_maybe  (state 2)
//   [x] 0x4387b0  CKHkPushObstacle_Update  (Update, vt+0x7c)
//   [x] 0x439060  CKHkPushObstacle_Load  (Load, vt+0x2c)
//   [x] 0x43a258  CKHkPushObstacle_DetachPushingHeroes_maybe
//   [x] 0x43a640  CKHkPushObstacle_CountActivePushers_maybe  (ChoosePushState, SelectNextState)
//   [x] 0x43acd0  CKHkPushObstacle_ChoosePushState_maybe  (states 1, 2)
//   [x] 0x43aff8  CKHkPushObstacle_SelectNextState_maybe  (states 1, 2)
//   [x] 0x43b290  CKHkPushObstacle_UpdateHeroPush_maybe  (states 1, 2, 3)
//   [x] 0x43bc88  CKHkPushObstacle_OnDeactivate  (OnDeactivate, VfA4)
//   [x] 0x43bf88  CKHkPushObstacle_MessageProc  (MessageProc, vt+0x1c)
//   [x] 0x43cbc8  CKHkPushObstacle_OnActivate  (OnActivate, VfA0)
//   [x] 0x43d1a8  CKHkPushObstacle_Restart  (Restart, vt+0x54)
//   [x] 0x43d7e8  CKHkPushObstacle_InitStateTable_maybe
//   [x] 0x43d848  CKHkPushObstacle_State0_PlayAnimWithImpact_maybe  (State0, vt+0xf0)
//   [x] 0x43db10  CKHkPushObstacle_State4_FinalAnimAndLock_maybe  (State4, vt+0x100)
//   [x] 0x43dfd0  CKHkPushObstacle_State3_WaitForPush_maybe  (State3, vt+0xfc)
//   [x] 0x43e3c0  CKHkPushObstacle_State1_Idle_maybe  (State1, vt+0xf4)
//   [x] 0x43e760  CKHkPushObstacle_State2_Moving_maybe  (State2, vt+0xf8)
//   [x] 0x43ee68  CKHkRollingBarrel_Delete  (CKHkRollingBarrel's factory delete: DOTD_DECLARE_FACTORIES, CKHkRollingBarrel.h)
//   [x] 0x43eeb8  CKHkRollingBarrel_vfB4  (an empty blr: IKHook's KGLObjectAttached, inherited by CKHkRollingBarrel)
//   [ ] 0x43eec0  Contact_GetOtherVolume_2  [dead]
//
//   [ ] 0x9c3328  CKHkPushObstacle_IsKindOfClass  [inline]
//   [ ] 0x9c3380  CKHkPushObstacle_GetClassType  [inline]
//   [ ] 0x9c3388  CKHkPushObstacle_GetClassID  [inline]
//   [ ] 0x9c3390  CKHkPushObstacle_GetTriggerPropA5  [inline]
//   [ ] 0x9c33a0  CKHkPushObstacle_GetTriggerPropA2  [inline]
//   [ ] 0x9c33b0  CKHkPushObstacle_GetTriggerPropA3  [inline]
//   [ ] 0x9c33c0  CKHkPushObstacle_GetTriggerPropA4  [inline]
//   [ ] 0x9c33d8  CKHkPushObstacle_GetTriggerPropA6  [inline]
//   [ ] 0x9c3400  CKHkPushObstacle_GetTriggerPropA7  [inline]
//
// C2.8 port-all P18: left (no game file holds class 0x842 CKHkPushObstacle).
// C2.8 port-final F02: the class is written (CKHkPushObstacle.h) with its Load, slots and helpers.
// C2.8 port-last Z2: the hero grab / push logic, the moves, the five states, MessageProc / Update / OnActivate /
// Restart. Nothing replays the class.
#include "k2000/hooks/CKHkPushObstacle.h"

#include <cmath>

#include "Renderware/rpprtstd/RpPrtStd.h"
#include "Renderware/rwcore/RwCamera.h"
#include "Renderware/rwcore/RwMatrix.h"
#include "Spyro2008/groups/CKGrpS08Hero.h"
#include "Spyro2008/groups/IKGrpHero.h"
#include "Spyro2008/hooks/CKHkS08Hero.h"
#include "crt/ppc_ops.h"
#include "crt/xlround.h"
#include "k2000/ai/CKSrvPathFinding.h"
#include "Renderware/rpprtstd/RpPrtStdRuntime.h"
#include "Renderware/rtanim/RtAnim.h"
#include "Spyro2008/logic/CKS08GameManager.h"
#include "k2000/components/CKLocTextAccessor.h"
#include "k2000/components/CKQuakeCameraLauncher.h"
#include "k2000/components/CKSekensLauncherCpnt.h"
#include "k2000/graphical/animation/CAnimationManager.h"
#include "k2000/logic/physics/CDynamicGround.h"
#include "k2000/math/CBBox.h"
#include "k2000/misc/IKGrpEnemy.h"
#include "k2000/scenegraph/IKBoundingBox.h"
#include "k2000/core/IKInfo.h"
#include "k2000/dictionaries/CAnimationDictionary.h"
#include "k2000/dictionaries/CKSoundDictionaryID.h"
#include "k2000/fx/IKFx.h"
#include "k2000/io/IKFile.h"
#include "k2000/logic/CDefaultGameManager.h"
#include "k2000/logic/CKPFGraphNode.h"
#include "k2000/logic/CSGHotSpot.h"
#include "k2000/logic/fx/CKInputIconNodeFx.h"
#include "k2000/scenegraph/IKBoundingVolume.h"
#include "k2000/logic/IKFxData.h"
#include "k2000/logic/fx/CKExplosionNodeFx.h"
#include "k2000/logic/sound/CKSound.h"
#include "k2000/managers/CKInput.h"
#include "k2000/managers/CKVibrationData.h"
#include "k2000/memory/Mem.h"
#include "k2000/misc/ClassRegistry.h"
#include "k2000/misc/Engine.h"
#include "k2000/misc/Mat4.h"
#include "k2000/scenegraph/CAnimatedNode.h"
#include "k2000/scenegraph/CParticlesNodeFx.h"
#include "k2000/scenegraph/CSGBranch.h"
#include "k2000/scenegraph/CSGLeaf.h"
#include "k2000/scenegraph/CSGMovable.h"
#include "k2000/services/CKSrvCollision.h"
#include "k2000/services/CKSrvFx.h"
#include "k2000/services/ICollisionMesh.h"
#include "k2000/system/IKTime.h"

namespace {
using Pusher = CKHkPushObstacle::Pusher;

CKSrvCollision* Collision() { return static_cast<CKSrvCollision*>(g_pEngine->m_srvCollision); }        // engine +0x58
CKSrvPathFinding* PathFinding() { return static_cast<CKSrvPathFinding*>(g_pEngine->m_srvPathFinding); }  // engine +0x6c
IKGrpHero* HeroGroup() { return static_cast<IKGrpHero*>(g_pEngine->m_gameManager->m_unk04[1]); }  // engine +0x8c -> +0x08
CKSoundDictionaryID* Sounds(const CKHkPushObstacle* o) { return static_cast<CKSoundDictionaryID*>(o->m_pSoundDictionary); }
CAnimatedNode* NodeOf(const CKHkPushObstacle* o) { return static_cast<CAnimatedNode*>(o->m_pKGLObject); }
CParticlesNodeFx* Fx(IKSerializable* node) { return static_cast<CParticlesNodeFx*>(node); }
ICollisionMesh* Mesh(IKSerializable* ground) { return static_cast<ICollisionMesh*>(ground); }
// The animation word `index` of a dictionary (CAnimationDictionary +0x04).
uint32_t AnimWord(IKSerializable* dictionary, uint32_t index) {
    return static_cast<uint32_t>(static_cast<CAnimationDictionary*>(dictionary)->m_apAnimations[index]);
}
// The pusher's dragon's animation dictionary (+0x58[dragon index], the index's low byte).
uint32_t HeroAnimWord(const CKHkPushObstacle* o, CKHkS08Hero* hero, uint32_t index) {
    return AnimWord(o->m_apHeroAnimDictionaries[hero->GetDragonIndex() & 0xffu], index);  // 0x00361960
}

// The shared axes (zero in the EBOOT's BSS, filled by StaticInitAndDestruction_11578).
const CVector3 kAxisX = {1.0f, 0.0f, 0.0f};     // 0x00c50d34 (TOC1 +0x4f68)
const CVector3 kAxisY = {0.0f, 1.0f, 0.0f};     // 0x00c50d40 (TOC1 +0x4f84)
const CVector3 kAxisZ = {0.0f, 0.0f, 1.0f};     // 0x00c50d4c (TOC1 +0x4f78)
const CVector3 kAxisNegX = {-1.0f, 0.0f, 0.0f};  // 0x00c50d70 (TOC1 +0x4f74)
const CVector3 kAxisNegZ = {0.0f, 0.0f, -1.0f};  // 0x00c50d88 (TOC1 +0x4f6c)
const float kZero = 0.0f;       // TOC1 +0x4f94
const float kHalf = 0.5f;       // TOC1 +0x4f3c
const float kOne = 1.0f;        // TOC1 +0x4f80
const float kTenth = 0.1f;      // TOC1 +0x4f88 (0x3dcccccd)
const float kBlendPush = 0.2f;  // TOC1 +0x4f90 (0x3e4ccccd)
const float kBlendIdle = 0.4f;  // TOC1 +0x4fa0 (0x3ecccccd)
const float kRandMax = 65535.0f;  // TOC1 +0x4fe4
const float kMinusTwo = -2.0f;  // TOC1 +0x4fe8
const float kMinusHalf = -0.5f;  // TOC1 +0x4fec
const float kBlendRest = 0.3f;   // TOC1 +0x5024 (0x3e99999a)

// The node's facing: its LTM's at axis (frame +0x70) equal to Z, X, -Z or -X (tested in that order, exactly): 0..3;
// 4 for none.
int32_t ExactFacing(const CKHkPushObstacle* o, CVector3* at) {
    const RwV3d& a = FrameLtm(NodeOf(o)->m_pRwFrame)->at;
    *at = {a.x, a.y, a.z};
    const CVector3* axes[4] = {&kAxisZ, &kAxisX, &kAxisNegZ, &kAxisNegX};
    for (int32_t i = 0; i < 4; ++i) {
        if (axes[i]->x == at->x && axes[i]->y == at->y && axes[i]->z == at->z) return i;
    }
    return 4;
}
// Whether the node's modelling at axis (frame +0x30) is within 0.1 of `axis` in every component (cror: a NaN fails).
bool NearAxis(const RwV3d& at, const CVector3& axis) {
    return at.x - kTenth <= axis.x && at.x + kTenth >= axis.x && at.y - kTenth <= axis.y && at.y + kTenth >= axis.y &&
           at.z - kTenth <= axis.z && at.z + kTenth >= axis.z;
}
// The footprint's centre offset (grid units times the cell size) for a facing (the four inlined copies).
void CentreOffset(const CKHkPushObstacle* o, int32_t facing, float* x, float* z) {
    const float s = g_pfGridScale.m_cellSize;  // 0x00c4025c
    const float c = static_cast<float>(o->m_i8CentreA);
    const float d = static_cast<float>(o->m_i8CentreB);
    switch (facing) {
    case 0: *x = s * c; *z = s * d; break;
    case 1: *x = s * static_cast<float>(-o->m_i8CentreB); *z = s * c; break;
    case 2: *x = s * static_cast<float>(-o->m_i8CentreA); *z = s * static_cast<float>(-o->m_i8CentreB); break;
    case 3: *x = s * d; *z = s * static_cast<float>(-o->m_i8CentreA); break;
    default: break;  // BUG(original): off the axes the offsets are stack garbage (kept as the caller's values here)
    }
}
// The footprint matrix: the identity axes (flags 3) at +0x188, its basis from `at` and the Y axis.
void FootprintMatrix(const CKHkPushObstacle* o, const CVector3* at, CMatrix34* m) {
    *m = CMatrix34{};
    m->m_right.x = kOne;
    m->m_up.y = kOne;
    m->m_at.z = kOne;
    m->m_ui32Flags = 0x20003u;
    m->m_pos = o->m_unk188;
    m->m_ui32Flags &= 0xfffdffffu;
    Mat4_SetBasisFromAtUp(m, at, &kAxisY);  // 0x0023fd30
}
// The emitting start of a particle node (CParticlesNodeFx_MessageProc's 0x1a00 inlined): 0x400 set, 0x80000 cleared, no
// speed adjustment, the emitter active and emitting (0xa).
void StartEmitting(CParticlesNodeFx* fx) {
    fx->m_sgProperties = (fx->m_sgProperties | 0x400u) & ~0x80000u;
    fx->m_fEmissionSpeedAdjustment = 0.0f;
    fx->m_pRpPrtStdEmitter->flag |= 0xau;
}
// Its stop: 0x400 and 0x80000 cleared, the emitter's emit bit (8) cleared.
void StopEmitting(CParticlesNodeFx* fx) {
    fx->m_sgProperties &= 0xfff7fbffu;
    fx->m_pRpPrtStdEmitter->flag &= 0xfffffff7u;
}
// Three emit points (the node's emit count 3, flag 0x2000 when it changes).
void SetThreeEmitPoints(CParticlesNodeFx* fx, const CVector3 p[3]) {
    if (fx->m_ui8NbActivePoints != 3) {
        fx->m_ui8NbActivePoints = 3;
        fx->m_sgProperties = (fx->m_sgProperties & 0xffffdfffu) | 0x2000u;
    }
    for (int32_t i = 0; i < 3; ++i) {
        RwV3d& out = fx->m_pAdvEmtPointList->pointList[i];
        out.z = p[i].z;
        out.x = p[i].x;
        out.y = p[i].y;
    }
}

// The GetInfo accessors (the inline 0x9c33a0.. and the dragon tests 0x4315e0 / 0x431560 / 0x4314e0).
uint32_t InfoCellA(IKSerializable* self, uint32_t) {  // 0x009c33a0 GetTriggerPropA2
    return static_cast<uint32_t>(static_cast<int32_t>(static_cast<CKHkPushObstacle*>(self)->m_i8CellA));
}
uint32_t InfoCellB(IKSerializable* self, uint32_t) {  // 0x009c33b0 GetTriggerPropA3
    return static_cast<uint32_t>(static_cast<int32_t>(static_cast<CKHkPushObstacle*>(self)->m_i8CellB));
}
uint32_t InfoInState1(IKSerializable* self, uint32_t) {  // 0x009c33c0 GetTriggerPropA4
    return static_cast<CKHkPushObstacle*>(self)->m_ui8State == 1 ? 1u : 0u;
}
uint32_t InfoUnk184(IKSerializable* self, uint32_t) {  // 0x009c3390 GetTriggerPropA5
    return static_cast<CKHkPushObstacle*>(self)->m_ui8Unk184 != 0 ? 1u : 0u;
}
uint32_t InfoNoneOrState4(IKSerializable* self, uint32_t) {  // 0x009c33d8 GetTriggerPropA6
    const uint8_t state = static_cast<CKHkPushObstacle*>(self)->m_ui8State;
    return (state == 0xff || state == 4) ? 1u : 0u;
}
uint32_t InfoHasPushers(IKSerializable* self, uint32_t) {  // 0x009c3400 GetTriggerPropA7
    return static_cast<CKHkPushObstacle*>(self)->m_pPushers != nullptr ? 1u : 0u;
}
// 0x004315e0 / 0x00431560 / 0x004314e0 IsDragon0 / 1 / 2AttachedToObject: the dragon is attached to `object` (no
// dragon: 0).
uint32_t IsDragonAttachedToObject(uint8_t dragon, const IKSerializable* object) {
    CKHkS08Hero* hero = static_cast<CKHkS08Hero*>(HeroGroup()->m_apHeros[dragon]);  // 0x002ca080
    if (hero == nullptr) return 0;
    return hero->GetAttachedObject() == object ? 1u : 0u;  // 0x00361d50
}
uint32_t InfoDragon0(IKSerializable* self, uint32_t) { return IsDragonAttachedToObject(0, self); }
uint32_t InfoDragon1(IKSerializable* self, uint32_t) { return IsDragonAttachedToObject(1, self); }
uint32_t InfoDragon2(IKSerializable* self, uint32_t) { return IsDragonAttachedToObject(2, self); }
}  // namespace

CKHkPushObstacle::CKHkPushObstacle() {
    m_ui8NbStates = 0xff;
    m_ui8State = 0xff;
    m_i16NavNode = -1;
    m_pPushers = nullptr;
    // m_GrdContDatasIn / m_GrdContDatasInOut: their constructors (masks 1, 8; ground 0, face -1, status 3, sector 0).
}

CKHkPushObstacle::~CKHkPushObstacle() {
    for (Pusher* p = m_pPushers; p != nullptr;) {
        Pusher* next = p->m_pNext;
        delete p;  // the FreeListPool 0x00ceaa90 in the original
        p = next;
    }
    m_pPushers = nullptr;
}

// 0x004304a8 CKHkPushObstacle_SnapToGroundAndBlockNav_maybe
void CKHkPushObstacle::SnapToGroundAndBlockNav() {
    CKSrvPathFinding* pf = PathFinding();
    CVector3 at;
    const int32_t facing = ExactFacing(this, &at);
    const float a = static_cast<float>(m_ui8HalfA);
    const float b = static_cast<float>(m_ui8HalfB);
    const float na = static_cast<float>(-static_cast<int32_t>(m_ui8HalfA));
    const float nb = static_cast<float>(-static_cast<int32_t>(m_ui8HalfB));
    // The footprint box (min +0x94, max +0xa0 on the stack) and the centre (+0x88): off the axes the centre stays
    // (+0x188.x, height / 2, +0x188.z). BUG(original): the box's x / z are then stack garbage (0 here).
    CVector3 lo = {0.0f, 0.0f, 0.0f};
    CVector3 hi = {0.0f, 0.0f, 0.0f};
    CVector3 centre = {m_unk188.x, m_fHeight * kHalf, m_unk188.z};
    switch (facing) {
    case 0: lo.x = a * kHalf; lo.z = b * kHalf; hi.x = na * kHalf; hi.z = nb * kHalf; break;
    case 1: lo.x = nb * kHalf; lo.z = a * kHalf; hi.x = b * kHalf; hi.z = na * kHalf; break;
    case 2: lo.x = na * kHalf; lo.z = nb * kHalf; hi.x = a * kHalf; hi.z = b * kHalf; break;
    case 3: lo.x = b * kHalf; lo.z = na * kHalf; hi.x = nb * kHalf; hi.z = a * kHalf; break;
    default: break;
    }
    CentreOffset(this, facing, &centre.x, &centre.z);
    lo.x = lo.x + centre.x;
    hi.x = hi.x + centre.x;
    lo.y = lo.y + centre.y;
    lo.z = lo.z + centre.z;
    hi.y = hi.y + centre.y;
    hi.z = hi.z + centre.z;
    CMatrix34 m;
    FootprintMatrix(this, &at, &m);
    CVector3 in = centre;
    Mat4_TransformPoints(&m, &centre, &in, 1);  // 0x0023f7e8
    in = hi;
    Mat4_TransformPoints(&m, &hi, &in, 1);
    in = lo;
    Mat4_TransformPoints(&m, &lo, &in, 1);
    // The obstacle's own grounds off while the centre is dropped on the ground.
    const uint16_t f0 = Mesh(m_apGrounds[0])->m_ba16EngineFlags;
    const uint16_t f1 = Mesh(m_apGrounds[1])->m_ba16EngineFlags;
    const uint16_t f2 = Mesh(m_apGrounds[2])->m_ba16EngineFlags;
    Mesh(m_apGrounds[0])->SetActive(0);  // 0x001a6b70
    Mesh(m_apGrounds[1])->SetActive(0);
    Mesh(m_apGrounds[2])->SetActive(0);
    Collision()->GroundProbePoints(&m_GrdContDatasIn, &m_GrdContDatasInOut, &centre.x, 1);  // 0x00196540
    if (m_GrdContDatasInOut.m_eContactStatus != 3) {
        GroundContact_GetWorldPoint(&m_GrdContDatasInOut, &centre);  // 0x001a70e0
        lo.y = centre.y;
        hi.y = centre.y;
    }
    Mesh(m_apGrounds[0])->SetActive(static_cast<uint16_t>(f0 & 1u));
    Mesh(m_apGrounds[1])->SetActive(static_cast<uint16_t>(f1 & 1u));
    Mesh(m_apGrounds[2])->SetActive(static_cast<uint16_t>(f2 & 1u));
    CPFPoint point;
    point.m_position = centre;
    point.m_i16GraphNodeIndex = 0xffff;
    if (static_cast<uint8_t>(pf->FindSectorForPoint(&point)) == 0) return;  // 0x001e5ca0
    // The box shrunk by 0.1 on x / z, whichever way round its corners are (the stack's +0xa0 corner is the minimum).
    CVector3 boxMin = hi;
    CVector3 boxMax = lo;
    if (!(hi.x <= lo.x)) {
        boxMin.x = lo.x + kTenth;
        boxMax.x = hi.x - kTenth;
    } else {
        boxMin.x = hi.x + kTenth;
        boxMax.x = lo.x - kTenth;
    }
    if (!(hi.z <= lo.z)) {
        boxMin.z = lo.z + kTenth;
        boxMax.z = hi.z - kTenth;
    } else {
        boxMin.z = hi.z + kTenth;
        boxMax.z = lo.z - kTenth;
    }
    pf->SetBoxBlocked(point.m_i16GraphNodeIndex, &boxMin, &boxMax, 1);  // 0x001e5f60
}

// 0x00430c78 CKHkPushObstacle_AttachSounds
void CKHkPushObstacle::KGLObjectAttached(IKSerializable* node) {
    for (uint32_t i = 0; i < 4; ++i) Sounds(this)->GetSound(i)->SetAttachObject(node);  // 0x00112bc0, 0x00111350
}

// 0x00430f20 CKHkPushObstacle_PlayPushAnimsOnMove_maybe
void CKHkPushObstacle::PlayPushAnimsOnMove() {
    for (Pusher* p = m_pPushers; p != nullptr; p = p->m_pNext) {
        const uint32_t word = HeroAnimWord(this, p->m_pHero, 1);
        if (word != p->m_pHero->GetCurrentAnim()) {  // 0x00361ee0
            p->m_pHero->CrossfadeAnimResource(kBlendPush, kZero, word, 1);  // vt+0xc4
        }
        p->m_bPushing = 0;
        p->m_unk18 = 1;
    }
    NodeOf(this)->PlayAnim(static_cast<double>(kZero), AnimWord(m_pAnimDictionary, 0), 0);  // 0x000c98b8
}

// 0x00431028 CKHkPushObstacle_AreAllPushersReady_maybe
uint8_t CKHkPushObstacle::AreAllPushersReady() {
    if (m_i8Side < 0) return 0;
    uint32_t i = HeroGroup()->GetHeroCount();  // 0x002ca038
    IKSerializable** points = m_apGrabPoints[m_i8Side];
    uint32_t points_used = 0;
    for (;;) {
        i = (i - 1) & 0xffu;
        if (i == 0xff) break;
        if (points[i] != nullptr) ++points_used;
    }
    uint32_t count = 0;
    for (Pusher* p = m_pPushers; p != nullptr; p = p->m_pNext) ++count;
    if ((points_used & 0xffu) != count) return 0;
    uint32_t all = m_pPushers != nullptr ? 1u : 0u;
    for (Pusher* p = m_pPushers; p != nullptr; p = p->m_pNext) {
        if (p->m_bReady == 0) all = 0;
    }
    return static_cast<uint8_t>(all);
}

// 0x00431180 CKHkPushObstacle_FreeBuffers_maybe
void CKHkPushObstacle::VfC0() {
    Mem_FreeAligned16(m_apHeroAnimDictionaries);  // 0x00052fb8
    Mem_FreeAligned16(m_apGrabPoints[3]);
    Mem_FreeAligned16(m_apGrabPoints[2]);
    Mem_FreeAligned16(m_apGrabPoints[1]);
    Mem_FreeAligned16(m_apGrabPoints[0]);
}

// 0x004311e8 CKHkPushObstacle_SetDefaultState
void CKHkPushObstacle::SetDefaultState(int32_t flag) {
    CKHkActorBase::SetDefaultState(flag);  // 0x003f72a0 (empty)
    ApplyStatePreset(0);                   // vt+0xc8
}

// 0x004312b8 CKHkPushObstacle_Start
void CKHkPushObstacle::Start() {
    CKHkActorBase::Start();  // 0x003f6e48 (empty)
    Restart();               // vt+0x54 0x0043d1a8
    m_pInputIconFx = nullptr;
}

// 0x00431318 CKHkPushObstacle_PostLoad
int32_t CKHkPushObstacle::PostLoad(int32_t type) {
    CKHkActorBase::PostLoad(type);  // 0x003f6e70
    InitStateTable();
    return 1;
}

// 0x004316c8 CKHkPushObstacle_PlayIdleAnims_maybe
void CKHkPushObstacle::PlayIdleAnims() {
    NodeOf(this)->PlayAnim(static_cast<double>(kZero), AnimWord(m_pAnimDictionary, 0), 0);  // 0x000c98b8
    for (Pusher* p = m_pPushers; p != nullptr; p = p->m_pNext) {
        if (p->m_bReady == 0) continue;
        p->m_pHero->CrossfadeAnimResource(kBlendIdle, kZero, HeroAnimWord(this, p->m_pHero, 0), 1);  // vt+0xc4
    }
}

// 0x004317b0 CKHkPushObstacle_PlayFinalAnims_maybe: a player's dragon plays its final animation (vt+0xc0), another
// gives the animation back (SetObjectControlsAnim 0).
void CKHkPushObstacle::PlayFinalAnims() {
    for (Pusher* p = m_pPushers; p != nullptr; p = p->m_pNext) {
        if (static_cast<uint8_t>(p->m_pHero->IsPlayerControlled()) != 0) {  // 0x00362af0
            p->m_pHero->PlayAnimResource(kZero, HeroAnimWord(this, p->m_pHero, 2));  // vt+0xc0
        } else {
            p->m_pHero->SetObjectControlsAnim(0);  // 0x00362010
        }
    }
    NodeOf(this)->PlayAnim(static_cast<double>(kZero), AnimWord(m_pAnimDictionary, 2), 0);  // 0x000c98b8
}

// 0x004318c8 CKHkPushObstacle_SetAnimTimeAll_maybe
void CKHkPushObstacle::SetAnimTimeAll(float time) {
    NodeOf(this)->SetCurrentAnimTime(time);  // 0x000c9690
    for (Pusher* p = m_pPushers; p != nullptr; p = p->m_pNext) {
        if (p->m_bReady == 0) continue;
        p->m_pHero->SetObjectAnimTime(time);  // 0x00363378
    }
}

// 0x00431950 CKHkPushObstacle_AdvanceAnimTime_maybe
void CKHkPushObstacle::AdvanceAnimTime(float nodeDt, float heroDt) {
    NodeOf(this)->AddAnimTime(static_cast<double>(nodeDt));  // 0x000c9638
    for (Pusher* p = m_pPushers; p != nullptr; p = p->m_pNext) {
        if (p->m_bReady == 0) continue;
        p->m_pHero->AdvanceObjectAnimTime(heroDt);  // 0x00363410
    }
}

// 0x004319d8 CKHkPushObstacle_PlayPushAnimsForReadyPushers_maybe
void CKHkPushObstacle::PlayPushAnimsForReadyPushers() {
    for (Pusher* p = m_pPushers; p != nullptr; p = p->m_pNext) {
        if (p->m_bReady == 0) continue;
        p->m_pHero->CrossfadeAnimResource(kBlendPush, kZero, HeroAnimWord(this, p->m_pHero, 1), 1);  // vt+0xc4
        p->m_bPushing = 1;
    }
    NodeOf(this)->PlayAnim(static_cast<double>(kZero), AnimWord(m_pAnimDictionary, 0), 0);  // 0x000c98b8
}

// 0x00431ad8 CKHkPushObstacle_ApplyStatePreset_maybe
void CKHkPushObstacle::ApplyStatePreset(int32_t state) {
    m_i8CellB = 0;
    m_i8CellA = 0;
    uint8_t flags;
    if (state == 0) {
        flags = m_aPresetFlags[0];
    } else {
        flags = m_aPresetFlags[1];
        m_i8CellA = m_aPresetCell[0];
        m_i8CellB = m_aPresetCell[1];
    }
    const bool needsNode = (flags & 2u) != 0 && m_unk70 != nullptr;
    m_ui8SideBits = static_cast<uint8_t>((m_ui8SideBits & 0xf0u) | ((flags >> 2) & 0xfu));
    if ((flags & 1u) != 0) {
        m_ui8StartMove = 0;
    } else if (needsNode) {
        m_ui8StartMove = 0xff;
    } else {
        m_ui8StartMove = 1;
    }
    m_i8StartCellB = m_i8CellB;
    m_i8StartCellA = m_i8CellA;
}

// 0x00431d70 CKHkPushObstacle_UpdatePusherHandFxPoints_maybe. BUG(original): no bound on the emit point list.
void CKHkPushObstacle::UpdatePusherHandFxPoints() {
    if (((m_ui8Flags >> 4) & 1u) != 0) return;
    CParticlesNodeFx* fx = Fx(m_pHandFx);
    if (fx->m_pAdvEmtPointList == nullptr) return;
    IKGrpHero* group = HeroGroup();
    uint32_t k = 0;
    for (Pusher* p = m_pPushers; p != nullptr; p = p->m_pNext) {
        if (p->m_bPushing == 0 || p->m_bHandFx == 0) continue;
        const uint8_t dragon = p->m_pHero->GetDragonIndex();  // 0x00361960
        CVector3 left;
        CVector3 right;
        static_cast<CSGHotSpot*>(p->m_pHero->GetHotSpot(static_cast<uint8_t>(group->GetHotSpotIndex(dragon, 2))))
            ->GetWorldPosition(&left);  // 0x002ca298, 0x00361b70, 0x000ce790
        static_cast<CSGHotSpot*>(p->m_pHero->GetHotSpot(static_cast<uint8_t>(group->GetHotSpotIndex(dragon, 3))))
            ->GetWorldPosition(&right);
        RwV3d* points = Fx(m_pHandFx)->m_pAdvEmtPointList->pointList;
        points[k].z = left.z;
        points[k].y = left.y;
        points[k].x = left.x;
        points[k + 1].z = right.z;
        points[k + 1].x = right.x;
        points[k + 1].y = right.y;
        k += 2;
    }
}

// 0x00431f78 CKHkPushObstacle_PlayImpactFx_maybe
void CKHkPushObstacle::PlayImpactFx() {
    IKFx* fx = static_cast<CKSrvFx*>(g_pEngine->m_srvFx)->AcquireFx(static_cast<IKFxData*>(m_pImpactFxData), this);
    if (fx != nullptr) {
        CKExplosionNodeFx* explosion = static_cast<CKExplosionNodeFx*>(fx);
        CVector3 at;
        const int32_t facing = ExactFacing(this, &at);
        // BUG(original): off the axes the offsets are stack garbage (0 here).
        CVector3 local = {0.0f, m_fHeight * kHalf, 0.0f};
        CentreOffset(this, facing, &local.x, &local.z);
        CMatrix34 m;
        FootprintMatrix(this, &at, &m);
        CVector3 point;
        Mat4_TransformPoints(&m, &point, &local, 1);  // 0x0023f7e8
        Collision()->GroundProbePoints(&m_GrdContDatasIn, &m_GrdContDatasInOut, &point.x, 1);  // 0x00196540
        if (m_GrdContDatasInOut.m_eContactStatus != 3) GroundContact_GetWorldPoint(&m_GrdContDatasInOut, &point);
        point.y = point.y + m_fImpactRaise;
        explosion->SetTranslation(&point, this);  // 0x001b66e8
        explosion->Trigger(this, nullptr);        // 0x001b82a8 (r5 / r6 0)
        explosion->ReleaseReservation(this);      // vt+0x54
    }
    if (((m_ui8Flags >> 2) & 1u) != 0) static_cast<CKQuakeCameraLauncher*>(m_pQuake)->Trigger();  // 0x001533c0
    if ((m_ui8Flags & 8u) == 0) {
        CKSound* sound = Sounds(this)->GetSound(2);
        sound->SetAttachObject(m_unk70 != nullptr ? m_unk70 : m_pNode);  // 0x00111350
        Sounds(this)->GetSound(2)->Play(kZero);                         // 0x00111230
    }
    CKVibrationData* vibration = static_cast<CKVibrationData*>(m_pVibration);
    vibration->m_pOwner = this;
    vibration->m_bUseTime = 1;
    if (!(vibration->m_fTime >= kZero)) vibration->m_fTime = kZero;  // bge
    g_pEngine->m_input->PlayVibration(vibration);  // 0x00107d38
}

// 0x00432810 CKHkPushObstacle_GetInfo (the jump table 0x4328e4 on the ids 0xa2..0xaa)
int32_t CKHkPushObstacle::GetInfo(IKInfo* info, int32_t request) {
    const int32_t base = CKHkActorBase::GetInfo(info, request);  // KStub_Return1 0x3f7140
    int32_t own = 1;
    if (request == kGetInfoValueAccessor && info->m_ui32Id - 0xa2u <= 8u) {
        switch (info->m_ui32Id) {
        case 0xa2: own = AnswerInfo(info, InfoCellA, 1); break;
        case 0xa3: own = AnswerInfo(info, InfoCellB, 1); break;
        case 0xa4: own = AnswerInfo(info, InfoInState1, 0); break;
        case 0xa5: own = AnswerInfo(info, InfoUnk184, 0); break;
        case 0xa6: own = AnswerInfo(info, InfoNoneOrState4, 0); break;
        case 0xa7: own = AnswerInfo(info, InfoHasPushers, 0); break;
        case 0xa8: own = AnswerInfo(info, InfoDragon0, 0); break;
        case 0xa9: own = AnswerInfo(info, InfoDragon1, 0); break;
        default: own = AnswerInfo(info, InfoDragon2, 0); break;
        }
    }
    if (base == 2) return 2;
    if (own == 0) return 0;
    return base == 0 ? 0 : 1;
}

// 0x00432bf0 CKHkPushObstacle_SetNavBoxBlocked_maybe
void CKHkPushObstacle::SetNavBoxBlocked(uint8_t blocked) {
    const float half = g_pfGridScale.m_cellSize * kHalf;  // 0x00c4025c
    const float a = static_cast<float>(m_ui8CellsA);
    const float na = static_cast<float>(-static_cast<int32_t>(m_ui8CellsA));
    const float b = static_cast<float>(m_ui8CellsB);
    const float nb = static_cast<float>(-static_cast<int32_t>(m_ui8CellsB));
    CVector3 boxMin = {ppc::fmadds(na, kHalf, half) + m_vRestPos.x, m_vRestPos.y + kZero,
                       ppc::fmadds(nb, kHalf, half) + m_vRestPos.z};
    CVector3 boxMax = {ppc::fmsubs(a, kHalf, half) + m_vRestPos.x, m_vRestPos.y + kZero,
                       ppc::fmsubs(b, kHalf, half) + m_vRestPos.z};
    if (m_i16NavNode < 0) return;
    PathFinding()->SetBoxBlocked(static_cast<uint16_t>(m_i16NavNode), &boxMin, &boxMax, blocked);  // 0x001e5f60
}

// 0x00432d30 CKHkPushObstacle_ResetPushState_maybe
void CKHkPushObstacle::ResetPushState() {
    if (m_pPushFx != nullptr) StopEmitting(Fx(m_pPushFx));
    if (m_pHandFx != nullptr) StopEmitting(Fx(m_pHandFx));
    Sound_Stop(Sounds(this)->GetSound(3), 0);  // 0x001111b0
    for (Pusher* p = m_pPushers; p != nullptr; p = p->m_pNext) p->m_bHandFx = 0;
}

// 0x00432e20 CKHkPushObstacle_StopMoveFeedbackFx_maybe
void CKHkPushObstacle::StopMoveFeedbackFx() {
    if ((m_ui8Flags & 0x20u) != 0) return;
    CParticlesNodeFx* fx = Fx(m_pMoveFx);
    CSGBranch* node = static_cast<CSGBranch*>(m_pNode);
    if (node == fx->m_pParent) {
        node->RemoveChild(fx);                                                // vt+0x78
        static_cast<CSGBranch*>(static_cast<CSGBranch*>(m_pNode)->m_pParent)->AddChild(Fx(m_pMoveFx));  // vt+0x70
        fx = Fx(m_pMoveFx);
    }
    StopEmitting(fx);
}

// 0x00432f18 CKHkPushObstacle_StartMoveFeedback_maybe. The move loop (sound 1) starts, or its pitch is drawn again
// (one rand draw) while it plays; then (unless +0x158 bit 5) three emit points along the pushed side: the two ends and
// a random point between them (one rand draw). BUG(original): with no side (or one above 3) the points are the
// caller's floating-point registers (0 here).
void CKHkPushObstacle::StartMoveFeedback() {
    CKSound* sound = Sounds(this)->GetSound(1);  // 0x00112bc0
    sound->SetLoop(1);                           // 0x00110fd0
    if (sound->CountInstances() == 0) {
        sound->Play(kZero);  // 0x00111230
    } else {
        const float base = sound->m_fRandomPitch + kOne;
        const uint32_t r = static_cast<uint32_t>(Rand_Int()) & 0xffffu;  // 0x00011500
        sound->SetSpeed(ppc::fmadds((static_cast<float>(r) / kRandMax) * kMinusTwo, sound->m_fRandomPitch, base));
    }
    if (((m_ui8Flags >> 5) & 1u) != 0) return;
    CParticlesNodeFx* fx = Fx(m_pMoveFx);
    fx->SetIdentity();                                            // 0x000d08f0
    static_cast<CSGBranch*>(fx->m_pParent)->RemoveChild(fx);      // vt+0x78
    static_cast<CSGBranch*>(m_pNode)->AddChild(Fx(m_pMoveFx));   // vt+0x70
    // The cells along / across the pushed side: (+0xd8, +0xd9) when the node faces Z or -Z (within 0.1), else swapped.
    const RwV3d& at = NodeOf(this)->m_pRwFrame->modelling.at;  // frame +0x30
    uint32_t p = m_ui8CellsA;
    uint32_t q = m_ui8CellsB;
    if (!NearAxis(at, kAxisZ) && !NearAxis(at, kAxisNegZ)) {
        p = m_ui8CellsB;
        q = m_ui8CellsA;
    }
    CVector3 pts[3] = {};
    const float h = m_fFxHeight * kHalf;
    const float pf = static_cast<float>(p);
    const float qf = static_cast<float>(q);
    const float np = static_cast<float>(-static_cast<int32_t>(p));
    const float nq = static_cast<float>(-static_cast<int32_t>(q));
    const float d8 = static_cast<float>(m_ui8CellsA);  // cases 1 / 3 read +0xd8 again (not the swapped p)
    switch (m_i8Side) {
    case 0: {
        pts[0] = {pf * kHalf, h, nq * kHalf};
        const uint32_t r = static_cast<uint32_t>(Rand_Int()) & 0xffffu;  // 0x00011500
        float t = static_cast<float>(r) / kRandMax;
        t = t + t;
        pts[2] = {pf * kHalf, m_fFxHeight * kHalf, qf * kHalf};
        pts[1] = {pf * kHalf, h, ppc::fmadds(qf * t, kMinusHalf, qf * kHalf + kZero)};
        break;
    }
    case 2: {
        pts[0] = {np * kHalf, h, nq * kHalf};
        const uint32_t r = static_cast<uint32_t>(Rand_Int()) & 0xffffu;
        float t = static_cast<float>(r) / kRandMax;
        t = t + t;
        pts[2] = {np * kHalf, m_fFxHeight * kHalf, qf * kHalf};
        pts[1] = {np * kHalf, h, ppc::fmadds(qf * t, kMinusHalf, qf * kHalf + kZero)};
        break;
    }
    case 1:
    case 3: {
        const float z = (m_i8Side == 1 ? qf : nq) * kHalf;
        pts[0] = {np * kHalf, h, z};
        const uint32_t r = static_cast<uint32_t>(Rand_Int()) & 0xffffu;
        float t = static_cast<float>(r) / kRandMax;
        t = t + t;
        const float h2 = m_fFxHeight * kHalf;
        pts[1] = {ppc::fmadds(t * d8, kMinusHalf, ppc::fmadds(d8, kHalf, kZero)), h2, z};
        pts[2] = {pf * kHalf, h2, z};
        break;
    }
    default:
        break;
    }
    fx = Fx(m_pMoveFx);
    if (fx->m_pAdvEmtPointList != nullptr) SetThreeEmitPoints(fx, pts);
    StartEmitting(Fx(m_pMoveFx));
}

// 0x0043a258 CKHkPushObstacle_DetachPushingHeroes_maybe. The list is read again after each release (the hero's detach
// may reach the obstacle); the kept pusher before is the one relinked.
void CKHkPushObstacle::DetachPushingHeroes(uint8_t all) {
    Pusher* p = m_pPushers;
    static_cast<CKGrpS08Hero*>(HeroGroup())->SetDragonSwitchLocked(0);  // 0x002ca1b8
    Collision()->RemoveVolume(static_cast<IKBoundingVolume*>(m_unkac));  // 0x00192bc0
    Pusher* prev = nullptr;
    while (p != nullptr) {
        if (static_cast<int16_t>(p->m_point.m_i16GraphNodeIndex) >= 0) {
            CKSrvPathFinding* pf = PathFinding();
            if (static_cast<uint8_t>(pf->FindSectorForPoint(&p->m_point)) != 0) {  // 0x001e5ca0
                CKPFGraphNode* node = static_cast<CKPFGraphNode*>(pf->m_Graph.m_apGraphNodes[p->m_point.m_i16GraphNodeIndex]);
                uint8_t cell[2];
                node->m_Sector.WorldToCell(&p->m_point.m_position, cell);  // 0x001ea3e0
                node->m_Sector.m_grid.SetCellBlocked(cell, 0);             // 0x001f12d8
            }
        }
        CKHkS08Hero* hero = p->m_pHero;
        if (all == 0 && hero->IsPlayerControlled() != 0 && hero->GetPlayerInputFloat38C() != kZero &&  // 0x003626f8
            m_ui8State != 4) {
            prev = p;
            p = p->m_pNext;
            continue;
        }
        if (hero->IsPlayerControlled() != 0) QueueTriggerSignals(&m_aStarters[9]);  // +0x148, 0x00236338
        hero->ClearFlag358Bit21IfAttached();  // 0x003628e0
        hero->DetachFromObject();             // 0x00364608
        Pusher* next = p->m_pNext;
        if (m_pPushers == p) {
            m_pPushers = next;
            prev = nullptr;
        } else {
            prev->m_pNext = next;
        }
        delete p;  // back to the FreeListPool 0x00ceaa90 in the original
        p = next;
    }
    if (m_pPushers != nullptr) return;
    QueueTriggerSignals(&m_aStarters[8]);  // +0x140
    if (m_ui8State != 2) m_i8Side = -1;
    m_ui8Unk184 = 0;
    m_ui16Flags1e4 = static_cast<uint16_t>(m_ui16Flags1e4 & 0xfffbu);
    if (m_ui8State == 3) {
        (this->*m_pStateTable[3])(nullptr, 2, 1);
        m_ui8State = 1;
        (this->*m_pStateTable[1])(nullptr, 1, 3);
    }
}

// 0x00435b98 CKHkPushObstacle_ShowInputIcon_maybe
void CKHkPushObstacle::ShowInputIcon(int32_t show) {
    if (show == 0) {
        if (m_pInputIconFx == nullptr) return;
        static_cast<IKFx*>(m_pInputIconFx)->StopAndRelease(this);  // vt+0x58
        m_pInputIconFx = nullptr;
        return;
    }
    if (m_pInputIconFx != nullptr) return;
    m_pInputIconFx = static_cast<CKSrvFx*>(g_pEngine->m_srvFx)->AcquireFx(static_cast<IKFxData*>(m_unk15c), this);
    if (m_pInputIconFx == nullptr) return;
    static_cast<CKInputIconNodeFx*>(m_pInputIconFx)
        ->UpdateWorldPosition(reinterpret_cast<const CMatrix34*>(FrameLtm(NodeOf(this)->m_pRwFrame)));  // 0x001c4bd8
}

// 0x0043bc88 CKHkPushObstacle_OnDeactivate (the footprint's release is SetNavBoxBlocked's code, inlined)
void CKHkPushObstacle::VfA4() {
    CKHkActorBase::VfA4();  // 0x003f7370
    SetNavBoxBlocked(0);
    DetachPushingHeroes(0);
    RwFrame* frame = NodeOf(this)->m_pRwFrame;
    frame->modelling.pos.z = m_unk188.z;
    frame->modelling.pos.x = m_unk188.x;
    frame->modelling.pos.y = m_unk188.y;
    frame->modelling.flags &= 0xfffdffffu;
    RwFrame_MarkDirty(NodeOf(this)->m_pRwFrame);  // 0x00010698
    if (m_pMoveFx != nullptr) StopEmitting(Fx(m_pMoveFx));
    ResetPushState();
    if (m_unk70 != nullptr) {
        CSGLeaf* leaf = static_cast<CSGLeaf*>(m_unk70);
        leaf->m_sgProperties = (leaf->m_sgProperties & 0xfffffffbu) | 4u;  // hidden
    }
    static_cast<CSGLeaf*>(m_pNode)->m_sgProperties &= 0xfffffffbu;  // shown
    IKSerializable* volumes[2] = {m_unk80, m_unkac};
    for (IKSerializable* v : volumes) {
        Collision()->RemoveVolume(static_cast<IKBoundingVolume*>(v));  // 0x00192bc0
        CSGBranch* parent = static_cast<CSGLeaf*>(v)->m_pParent;
        if (parent != nullptr) parent->RemoveChild(static_cast<CSGLeaf*>(v));  // vt+0x78
    }
    ShowInputIcon(0);
}

// C2.8 port-last Z2: the moves, the grid and the push decisions.
namespace {
float SqrtF(float x) { return static_cast<float>(std::sqrt(static_cast<double>(x))); }  // 0x00010690 Math_Sqrtf
// The squared length as the original sums it (y * y, then x * x and z * z fused on).
float LengthSq(float x, float y, float z) { return ppc::fmadds(z, z, ppc::fmadds(x, x, y * y)); }
bool SameAxis(const RwV3d& v, const CVector3& axis) { return axis.x == v.x && axis.y == v.y && axis.z == v.z; }
bool SameAxis(const CVector3& v, const CVector3& axis) { return axis.x == v.x && axis.y == v.y && axis.z == v.z; }
void Negate(CVector3* v) {
    v->x = -v->x;
    v->y = -v->y;
    v->z = -v->z;
}
const float kNearAxis = 0.9f;       // TOC1 +0x4f64 (0x3f666666)
const float kNearNegAxis = -0.9f;   // TOC1 +0x4f70 (0xbf666666)
const float kProbeRaise = 0.05f;    // TOC1 +0x5020 (0x3d4ccccd)
const float kWalkRadius = 0.45f;    // TOC1 +0x5018 (0x3ee66666)
const float kPi = 3.14159274f;      // TOC1 +0x5014 (0x40490fdb)
const float kSqrt2 = 1.41421354f;   // TOC1 +0x501c (0x3fb504f3)
// The pushed side's axis (the inlined test of a grab point's world matrix): its at axis' x not less than 0.9: X (0),
// not greater than -0.9: -X (1), else its z: Z (2) / -Z (3); 4 for none (a NaN fails each test).
int32_t SideAxis(const CMatrix34& m) {
    const float x = m.m_at.x;  // +0x20
    const float z = m.m_at.z;  // +0x28
    if (x >= kNearAxis) return 0;
    if (x <= kNearNegAxis) return 1;
    if (z >= kNearAxis) return 2;
    if (z <= kNearNegAxis) return 3;
    return 4;
}
// Its vector. BUG(original): for none the callers keep their caller's floating-point registers (0 here).
CVector3 SideVector(int32_t axis) {
    switch (axis) {
    case 0: return kAxisX;
    case 1: return kAxisNegX;
    case 2: return kAxisZ;
    case 3: return kAxisNegZ;
    default: return CVector3{0.0f, 0.0f, 0.0f};
    }
}
// A frame's modelling position (the flag 0x20000 cleared, the frame updated: the inlined CSGMovable store).
void SetFramePosition(RwFrame* frame, const CVector3& p) {
    frame->modelling.pos.z = p.z;
    frame->modelling.pos.x = p.x;
    frame->modelling.pos.y = p.y;
    frame->modelling.flags &= 0xfffdffffu;
    RwFrame_MarkDirty(frame);  // 0x00010698
}
RwFrame* FrameOf(IKSerializable* node) { return static_cast<CSGMovable*>(node)->m_pRwFrame; }
// The cell of a point found in a nav node (its node m_unk0c) blocked or freed (the inlined grid write).
void SetPointCellBlocked(CKSrvPathFinding* pf, CPFPoint* point, uint8_t blocked) {
    CKPFGraphNode* node = static_cast<CKPFGraphNode*>(pf->m_Graph.m_apGraphNodes[point->m_i16GraphNodeIndex]);
    uint8_t cell[2];
    node->m_Sector.WorldToCell(&point->m_position, cell);  // 0x001ea3e0
    node->m_Sector.m_grid.SetCellBlocked(cell, blocked);   // 0x001f12d8
}
CSGHotSpot* GrabPoint(const CKHkPushObstacle* o, int8_t side, int32_t index) {
    return static_cast<CSGHotSpot*>(o->m_apGrabPoints[side][index]);
}
}  // namespace

// 0x004373d8 CKHkPushObstacle_ComputeRestPosition_maybe / 0x00436630 _ComputeFootprintCorner_maybe: the same code on
// the cells (+0x194, +0x195) and (+0x196, +0x197). The node's LTM at axis (frame +0x70) and right axis (+0x50), each
// scaled to |cell| x the grid's cell size: when the at axis is Z or -Z (exactly) the at axis takes cell B and the
// right axis cell A, their signs from the at axis; when the right axis is Z or -Z the at axis takes cell A and the
// right axis cell B, their signs from the right axis; else both stay unit. Their sum plus +0x188.
void CKHkPushObstacle::CellPosition(int8_t cellA, int8_t cellB, CVector3* out) {
    const RwFrame* frame = NodeOf(this)->m_pRwFrame;
    const RwV3d& at = frame->ltm.at;
    const RwV3d& right = frame->ltm.right;
    const float s = g_pfGridScale.m_cellSize;  // 0x00c4025c
    CVector3 a = {at.x, at.y, at.z};
    CVector3 r = {right.x, right.y, right.z};
    const auto scale = [s](CVector3* v, int8_t cell) {
        const float c = std::fabs(static_cast<float>(cell));
        const float len = SqrtF(LengthSq(v->x, v->y, v->z));
        if (len != kZero) {
            const float f = (s * c) / len;
            v->z = v->z * f;
            v->x = v->x * f;
            v->y = v->y * f;
        }
    };
    if (SameAxis(at, kAxisZ) || SameAxis(at, kAxisNegZ)) {
        scale(&a, cellB);
        scale(&r, cellA);
        if (cellB > 0 ? SameAxis(at, kAxisNegZ) : (cellB != 0 && SameAxis(at, kAxisZ))) Negate(&a);
        if (cellA > 0 ? SameAxis(at, kAxisNegZ) : (cellA != 0 && SameAxis(at, kAxisZ))) Negate(&r);
    } else if (SameAxis(right, kAxisZ) || SameAxis(right, kAxisNegZ)) {
        scale(&a, cellA);
        scale(&r, cellB);
        if (cellB > 0 ? SameAxis(right, kAxisNegZ) : (cellB != 0 && SameAxis(right, kAxisZ))) Negate(&r);
        if (cellA < 0 ? SameAxis(right, kAxisNegZ) : (cellA != 0 && SameAxis(right, kAxisZ))) Negate(&a);
    }
    out->x = (a.x + r.x) + m_unk188.x;
    out->y = (a.y + r.y) + m_unk188.y;
    out->z = (a.z + r.z) + m_unk188.z;
}
void CKHkPushObstacle::ComputeRestPosition(CVector3* out) { CellPosition(m_i8CellA, m_i8CellB, out); }
void CKHkPushObstacle::ComputeFootprintCorner(CVector3* out) { CellPosition(m_i8StartCellA, m_i8StartCellB, out); }

// 0x00435e70 CKHkPushObstacle_StepGridCoordAndFireSignals_maybe: the cell offsets step one cell along the pushed
// side's axis (-X: A - 1, starter 1; -Z: B - 1, starter 3; X: A + 1, starter 2; Z: B + 1, starter 4); the rest
// position is recomputed by the next Update (+0x1e4 bit 0).
void CKHkPushObstacle::StepGridCoordAndFireSignals() {
    if (m_i8Side >= 0) m_i8LastSide = m_i8Side;
    CMatrix34 m;
    GrabPoint(this, m_i8LastSide, 0)->GetWorldMatrix(&m);  // 0x000ce970
    const CVector3 d = SideVector(SideAxis(m));
    if (SameAxis(d, kAxisNegX)) {
        m_i8CellA = static_cast<int8_t>(m_i8CellA - 1);
        QueueTriggerSignals(&m_aStarters[1]);  // +0x108, 0x00236338
    } else if (SameAxis(d, kAxisNegZ)) {
        m_i8CellB = static_cast<int8_t>(m_i8CellB - 1);
        QueueTriggerSignals(&m_aStarters[3]);  // +0x118
    } else if (SameAxis(d, kAxisX)) {
        m_i8CellA = static_cast<int8_t>(m_i8CellA + 1);
        QueueTriggerSignals(&m_aStarters[2]);  // +0x110
    } else if (SameAxis(d, kAxisZ)) {
        m_i8CellB = static_cast<int8_t>(m_i8CellB + 1);
        QueueTriggerSignals(&m_aStarters[4]);  // +0x120
    }
    m_ui16Flags1e4 = static_cast<uint16_t>(m_ui16Flags1e4 | 1u);
}

// 0x004371b0 CKHkPushObstacle_UpdateMoveStep_maybe: the move distance runs on at a cell per push animation (the first
// pusher's; none: 1 a second), and the node sits that far from the start corner along the pushed side's axis.
void CKHkPushObstacle::UpdateMoveStep(float dt) {
    float speed = kOne;
    if (m_pPushers != nullptr) speed = g_pfGridScale.m_cellSize / m_pPushers->m_pHero->GetCurrentAnimDuration();  // 0x00362450
    CVector3 corner;
    ComputeFootprintCorner(&corner);
    if (m_i8Side >= 0) m_i8LastSide = m_i8Side;
    CMatrix34 m;
    GrabPoint(this, m_i8LastSide, 0)->GetWorldMatrix(&m);  // 0x000ce970
    CVector3 d = SideVector(SideAxis(m));
    m_fMoveDist = ppc::fmadds(speed, dt, m_fMoveDist);
    const float len = SqrtF(LengthSq(d.x, d.y, d.z));
    if (len != kZero) {
        const float f = m_fMoveDist / len;
        d.z = d.z * f;
        d.x = d.x * f;
        d.y = d.y * f;
    }
    corner.x = d.x + corner.x;
    corner.y = corner.y + d.y;
    corner.z = corner.z + d.z;
    SetFramePosition(NodeOf(this)->m_pRwFrame, corner);
}

// 0x00438550 CKHkPushObstacle_BeginMove_maybe: the footprint freed (SetNavBoxBlocked(0)'s code, inlined), the push
// animations, the cell step and its signals, the move feedback; the move distance 0, +0x1e4 bit 1 (moving). With
// +0x158 bit 1 the volume +0x80 joins the collision; else the node +0x7c drops 0.05 under the rest position and the
// third ground is switched on.
void CKHkPushObstacle::BeginMove() {
    SetNavBoxBlocked(0);
    PlayPushAnimsOnMove();
    StepGridCoordAndFireSignals();
    StartMoveFeedback();
    m_fMoveDist = kZero;
    m_ui16Flags1e4 = static_cast<uint16_t>(m_ui16Flags1e4 | 2u);
    if (((m_ui8Flags >> 1) & 1u) != 0) {
        Collision()->AddVolume(static_cast<IKBoundingVolume*>(m_unk80));  // 0x00192b80
        return;
    }
    CVector3 p;
    ComputeRestPosition(&p);
    p.y = p.y - kProbeRaise;
    SetFramePosition(FrameOf(m_unk7c), p);
    Mesh(m_apGrounds[2])->SetActive(1);  // 0x001a6b70
}

// 0x004381e0 CKHkPushObstacle_ProbeMoveTarget_maybe: with a side, half a cell past the rest position along the side's
// axis must be ground at once (status 0, more than 0.5 under the point), the obstacle's first two grounds off
// meanwhile; +0x158 bit 3 or +0x1e4 bit 6 skip the test (1); no side: 0.
uint8_t CKHkPushObstacle::ProbeMoveTarget() {
    if (m_i8Side < 0) return 0;
    if (((m_ui8Flags >> 3) & 1u) != 0 || ((m_ui16Flags1e4 >> 6) & 1u) != 0) return 1;
    if (m_apGrounds[1] != nullptr) Mesh(m_apGrounds[1])->SetActive(0);
    Mesh(m_apGrounds[0])->SetActive(0);
    CVector3 p;
    ComputeRestPosition(&p);
    if (m_i8Side >= 0) m_i8LastSide = m_i8Side;
    CMatrix34 m;
    GrabPoint(this, m_i8LastSide, 0)->GetWorldMatrix(&m);  // 0x000ce970
    CVector3 d = SideVector(SideAxis(m));
    const float s = g_pfGridScale.m_cellSize;
    const float len = SqrtF(LengthSq(d.x, d.y, d.z));
    if (len != kZero) {
        const float f = (s * kHalf) / len;
        d.z = d.z * f;
        d.x = d.x * f;
        d.y = d.y * f;
    }
    p.x = p.x + d.x;
    p.y = p.y + d.y;
    p.z = p.z + d.z;
    Collision()->GroundProbePoints(&m_GrdContDatasIn, &m_GrdContDatasInOut, &p.x, 1);  // 0x00196540
    const bool ground = m_GrdContDatasInOut.m_eContactStatus == 0 && !(m_GrdContDatasInOut.m_fdH <= kHalf);  // ble
    // BUG(original): the second ground is switched off again (not back on).
    if (m_apGrounds[1] != nullptr) Mesh(m_apGrounds[1])->SetActive(0);
    Mesh(m_apGrounds[0])->SetActive(1);
    return ground ? 1 : 0;
}

// 0x00437950 CKHkPushObstacle_CanPushInDirection_maybe: the cells the footprint moves into, one grid cell at a time
// along the pushed side's axis from the rest position (as many as the footprint's depth over the cell size): each one
// in a nav node must be inside the node's box and walkable for a 0x45-radius character, and on ground (status 0 / 1,
// within 0.5 unless +0x70 is set); without +0x158 bit 1 no other dragon may stand in the snapped cell (it gets +0x364
// bit 5), and with enemies (+0xbc above 0) none may be ahead in the half-circle within a diagonal. Outside a nav node
// only the ground test.
uint8_t CKHkPushObstacle::CanPushInDirection() {
    CKSrvPathFinding* pf = PathFinding();
    const float s = g_pfGridScale.m_cellSize;  // 0x00c4025c
    CPFPoint point;
    point.m_i16GraphNodeIndex = 0xffff;
    CVector3 p;
    ComputeRestPosition(&p);
    if (m_i8Side >= 0) m_i8LastSide = m_i8Side;
    CMatrix34 m;
    GrabPoint(this, m_i8LastSide, 0)->GetWorldMatrix(&m);  // 0x000ce970
    // The back axis, the side's axis and the footprint's (along, across) cells per side. BUG(original): off the axes
    // they are stack garbage and the caller's registers (0 here).
    CVector3 back = {0.0f, 0.0f, 0.0f};
    CVector3 along = {0.0f, 0.0f, 0.0f};
    uint32_t cellsAlong = 0;
    uint32_t cellsAcross = 0;
    switch (SideAxis(m)) {
    case 0: back = kAxisNegZ; along = kAxisX; cellsAlong = m_ui8CellsA; cellsAcross = m_ui8CellsB; break;
    case 1: back = kAxisZ; along = kAxisNegX; cellsAlong = m_ui8CellsA; cellsAcross = m_ui8CellsB; break;
    case 2: back = kAxisX; along = kAxisZ; cellsAlong = m_ui8CellsB; cellsAcross = m_ui8CellsA; break;
    case 3: back = kAxisNegX; along = kAxisNegZ; cellsAlong = m_ui8CellsB; cellsAcross = m_ui8CellsA; break;
    default: break;
    }
    CVector3 ahead = {-back.x, -back.y, -back.z};
    Mat4_TransformVectors(reinterpret_cast<const CMatrix34*>(&NodeOf(this)->m_pRwFrame->modelling), &ahead, &ahead, 1);
    const float half = s * kHalf;
    const float alongDist = ppc::fmadds(static_cast<float>(cellsAlong), kHalf, half);
    const float fAcross = static_cast<float>(cellsAcross);
    const float acrossDist = ppc::fmadds(fAcross, kHalf, s * kMinusHalf);
    CVector3 w = {-(back.x * acrossDist), -(back.y * acrossDist), -(back.z * acrossDist)};
    p.z = p.z + ppc::fmadds(alongDist, along.z, w.z);
    p.x = p.x + ppc::fmadds(alongDist, along.x, w.x);
    p.y = p.y + ppc::fmadds(alongDist, along.y, w.y);
    float len = SqrtF(LengthSq(w.x, w.y, w.z));
    if (len != kZero) {
        const float f = kOne / len;
        w.y = w.y * f;
        w.z = w.z * f;
        w.x = w.x * f;
    }
    CVector3 step = {-w.x, -w.y, -w.z};
    len = SqrtF(LengthSq(step.x, step.y, step.z));
    if (len != kZero) {
        const float f = s / len;
        step.z = step.z * f;
        step.x = step.x * f;
        step.y = step.y * f;
    }
    CPFCharacter character;
    character.m_bits = 0xc01;
    character.m_fRadius = kWalkRadius;
    character.m_fMaxStepHeight = kBlendPush;  // 0.2
    character.m_fMaxStepRise = kOne;
    const int32_t count = static_cast<int32_t>(static_cast<int64_t>(fAcross / s));  // fctidz
    for (int32_t i = 0; i != count;) {
        point.m_position = p;
        if (static_cast<uint8_t>(pf->FindSectorForPoint(&point)) == 0) {  // 0x001e5ca0
            Collision()->GroundProbePoints(&m_GrdContDatasIn, &m_GrdContDatasInOut, &p.x, 1);  // 0x00196540
            const uint32_t status = m_GrdContDatasInOut.m_eContactStatus;
            if (status != 0 && status != 1) return 0;
            if (!(m_GrdContDatasInOut.m_fdH <= kHalf) && m_unk70 == nullptr) return 0;
        } else {
            const int16_t index = static_cast<int16_t>(point.m_i16GraphNodeIndex);
            if (index < 0) return 0;
            if (static_cast<uint32_t>(static_cast<int32_t>(index)) >= pf->m_Graph.m_ui32GraphNodesSize) return 0;
            const CBBox& box = static_cast<CKPFGraphNode*>(pf->m_Graph.m_apGraphNodes[point.m_i16GraphNodeIndex])->m_Sector.m_box;
            if (!(box.m_inf.x <= point.m_position.x) || !(box.m_sup.x >= point.m_position.x)) return 0;
            if (!(box.m_inf.z <= point.m_position.z) || !(box.m_sup.z >= point.m_position.z)) return 0;
            if (!(box.m_inf.y <= point.m_position.y) || !(box.m_sup.y >= point.m_position.y)) return 0;
            if (static_cast<uint8_t>(pf->IsPointWalkable(&point, &character)) == 0) return 0;  // 0x001e42d0
            Collision()->GroundProbePoints(&m_GrdContDatasIn, &m_GrdContDatasInOut, &p.x, 1);
            const uint32_t status = m_GrdContDatasInOut.m_eContactStatus;
            if (status != 0 && status != 1) return 0;
            if (!(m_GrdContDatasInOut.m_fdH <= kHalf) && m_unk70 == nullptr) return 0;
            IKGrpHero* group = HeroGroup();
            if ((m_ui8Flags & 2u) == 0) {
                // The point snapped to its cell's centre (x and z), then no other dragon in that cell.
                const float cs = g_pfGridScale.m_cellSize;
                const float ch = cs * kHalf;
                const int32_t xi = crt::lroundf((ch + p.x) / cs);  // 0x0098d3a0
                const float zArg = (ch + p.z) / cs;
                p.x = ppc::fmsubs(cs, static_cast<float>(xi), ch);
                const int32_t zi = crt::lroundf(zArg);
                p.z = ppc::fmsubs(cs, static_cast<float>(zi), ch);
                for (uint32_t k = group->GetHeroCount();;) {  // 0x002ca038
                    k = (k - 1) & 0xffu;
                    if (k == 0xff) break;
                    if (static_cast<CKHkS08Hero*>(HeroGroup()->m_apHeros[k])->GetAttachedObject() == this) continue;
                    CKHkS08Hero* hero = static_cast<CKHkS08Hero*>(HeroGroup()->m_apHeros[k]);  // 0x002ca080
                    const float* pos = hero->GetPositionPtr();  // 0x00361968
                    const float hs = g_pfGridScale.m_cellSize;
                    const float hh = hs * kHalf;
                    const float hx = ppc::fmsubs(hs, static_cast<float>(crt::lroundf((hh + pos[0]) / hs)), hh);
                    const int32_t hzi = crt::lroundf((pos[2] + hh) / hs);
                    float hy = pos[1];
                    if (p.y + m_fHeight >= hy) hy = p.y;
                    if (!(hx - kTenth <= p.x) || !(hx + kTenth >= p.x)) continue;
                    if (!(hy - kTenth <= p.y) || !(hy + kTenth >= p.y)) continue;
                    const float hz = ppc::fmsubs(hs, static_cast<float>(hzi), hh);
                    if (!(hz - kTenth <= p.z) || !(hz + kTenth >= p.z)) continue;
                    hero->SetFlag364Bit5();  // 0x00361d98
                    return 0;
                }
            }
            IKGrpEnemy* enemies = static_cast<IKGrpEnemy*>(g_pEngine->m_gameManager->m_unk04[0]);  // engine +0x8c -> +0x04
            if (enemies != nullptr && !(m_fEnemyConeCheck <= kZero)) {  // ble
                CVector3 d = {-ahead.x, -ahead.y, -ahead.z};
                const float dl = SqrtF(LengthSq(d.x, d.y, d.z));
                if (dl != kZero) {
                    const float f = half / dl;
                    d.z = d.z * f;
                    d.x = d.x * f;
                    d.y = d.y * f;
                }
                const CVector3 centre = {d.x + p.x, d.y + p.y, d.z + p.z};
                const CVector3 direction = ahead;
                if (enemies->IsAnyEnemyInCone(kPi, s * kSqrt2, &centre, &direction) != 0) return 0;  // 0x002665a0
            }
        }
        p.x = p.x + step.x;
        p.y = p.y + step.y;
        p.z = p.z + step.z;
        ++i;
    }
    return 1;
}

// 0x0043a640 CKHkPushObstacle_CountActivePushers_maybe: the pushers' players counted; a player's dragon that stopped
// pushing (no input +0x38c, unless `keep`, +0x1e4 bit 4 / 6 or +0x158 bit 3) is let go (its cell freed, detached,
// +0x180); a ready one pushing into the obstacle (input +0x394 above +0xde, its move vector along its model's at axis)
// counts. The player count change fires starter 9 when it drops to 0. With every grab point of the side taken by
// ready pushers and +0x1e4 bit 1 the count is the controlled dragons'; else, without a player (with +0x158 bit 0 and
// no +0x1e4 bit 6) or without +0x158 bit 0, starters 8 and 9 and every pusher let go. Answers the count.
int8_t CKHkPushObstacle::CountActivePushers(uint8_t keep) {
    IKGrpHero* group = HeroGroup();
    uint8_t pushing = 0;
    uint8_t players = 0;
    Pusher* prev = nullptr;
    Pusher* p = m_pPushers;
    while (p != nullptr) {
        CKHkS08Hero* hero = p->m_pHero;
        if (static_cast<uint8_t>(hero->IsPlayerControlled()) != 0) ++players;  // 0x00362af0
        if (static_cast<uint8_t>(p->m_pHero->IsPlayerControlled()) != 0) {
            if ((m_ui16Flags1e4 & 0x10u) == 0 && keep == 0 && p->m_pHero->GetPlayerInputFloat38C() == kZero &&  // 0x003626f8
                (m_ui8Flags & 8u) == 0 && (m_ui16Flags1e4 & 0x40u) == 0) {
                p->m_pHero->ClearFlag358Bit21IfAttached();  // 0x003628e0
                if (static_cast<int16_t>(p->m_point.m_i16GraphNodeIndex) >= 0) {
                    CKSrvPathFinding* pf = PathFinding();
                    if (static_cast<uint8_t>(pf->FindSectorForPoint(&p->m_point)) != 0) SetPointCellBlocked(pf, &p->m_point, 0);
                }
                p->m_pHero->DetachFromObject();  // 0x00364608
                m_pReleasedHero = p->m_pHero;
                Pusher* next = p->m_pNext;
                if (m_pPushers == p) {
                    m_pPushers = next;
                } else {
                    prev->m_pNext = next;
                }
                delete p;  // back to the FreeListPool 0x00ceaa20's free list +0x74 in the original
                if (m_pPushers == nullptr) {
                    static_cast<CKGrpS08Hero*>(group)->SetDragonSwitchLocked(0);  // 0x002ca1b8
                    m_i8Side = -1;
                }
                if (next == nullptr) break;
                // BUG(original): the pusher after a released one is skipped.
                prev = next;
                p = next->m_pNext;
                continue;
            }
            if (p->m_bReady != 0 && m_unkde < static_cast<uint8_t>(p->m_pHero->GetPlayerInputByte394())) {  // 0x00362dd0
                const float* move = p->m_pHero->GetPlayerMoveVectorPtr();  // 0x00362a40
                const RwV3d& at = FrameOf(p->m_pHero->m_pKGLObject)->ltm.at;
                const float dot = ppc::fmadds(move[2], at.z, ppc::fmadds(move[0], at.x, move[1] * at.y));
                if (!(dot <= kZero)) ++pushing;  // ble
            }
        }
        prev = p;
        p = p->m_pNext;
    }
    const int8_t n = static_cast<int8_t>(players);
    if (static_cast<int32_t>(n) != static_cast<int32_t>(m_ui8Unk184)) {
        if (n == 0) QueueTriggerSignals(&m_aStarters[9]);  // +0x148
        m_ui8Unk184 = players;
    }
    if (((n == 0 && (m_ui8Flags & 1u) != 0) || ((m_ui16Flags1e4 >> 6) & 1u) != 0) && m_i8Side >= 0 &&
        AreAllPushersReady() != 0 && (m_ui16Flags1e4 & 2u) != 0) {
        pushing = group->m_ui8ControlledHeroCount;  // 0x002ca288
    }
    if (m_pPushers != nullptr) {
        const bool release = n == 0 && (m_ui8Flags & 1u) == 0 && (m_ui16Flags1e4 & 0x40u) == 0;
        if (!release) {
            if (AreAllPushersReady() != 0) return static_cast<int8_t>(pushing);
            if ((m_ui8Flags & 1u) == 0 || n != 0) return static_cast<int8_t>(pushing);
        }
        QueueTriggerSignals(&m_aStarters[8]);  // +0x140
        QueueTriggerSignals(&m_aStarters[9]);  // +0x148
        DetachPushingHeroes(0);
    }
    return static_cast<int8_t>(pushing);
}

// 0x0043acd0 CKHkPushObstacle_ChoosePushState_maybe: no pusher pushing: -1; fewer than needed (the side's grab points,
// at most the controlled dragons; all of them while a dragon switch is pending in state 2): 1; enough with the side
// allowed (+0x1a1), all its grab points ready and the way free: 2; else 3.
int8_t CKHkPushObstacle::ChoosePushState() {
    int8_t n = CountActivePushers(0);
    IKGrpHero* group = HeroGroup();
    if (static_cast<uint8_t>(static_cast<CKGrpS08Hero*>(group)->IsDragonSwitchPending()) != 0 && m_ui8State == 2) {  // 0x002ca188
        n = static_cast<int8_t>(HeroGroup()->m_ui8ControlledHeroCount);  // 0x002ca288
    }
    const uint8_t controlled = HeroGroup()->m_ui8ControlledHeroCount;
    const int8_t side = m_i8Side;
    const auto countPoints = [this, side]() {
        uint32_t used = 0;
        if (side == -1) return used;
        for (uint32_t i = m_ui8NbDragons;;) {
            i = (i - 1) & 0xffu;
            if (i == 0xff) break;
            if (m_apGrabPoints[side][i] != nullptr) ++used;
        }
        return used;
    };
    uint8_t needed;
    if (controlled > static_cast<uint8_t>(countPoints())) {
        needed = static_cast<uint8_t>(countPoints());
    } else {
        needed = HeroGroup()->m_ui8ControlledHeroCount;
    }
    if (n <= 0) return -1;
    if (n < static_cast<int8_t>(needed)) return 1;
    if (m_i8Side >= 0 && ((m_ui8SideBits >> static_cast<uint8_t>(m_i8Side)) & 1u) != 0 && AreAllPushersReady() != 0 &&
        CanPushInDirection() != 0) {
        return 2;
    }
    return 3;
}

// 0x0043aff8 CKHkPushObstacle_SelectNextState_maybe: with +0x70 and ground ahead (ProbeMoveTarget): the final state 4
// once every grab point is taken by ready pushers (pushed by a player, +0x1e4 bit 6, or +0x158 bit 3 without one),
// unless (without +0x158 bit 1) another dragon stands in the grab area (3); pushers not all ready: 3; else -1.
int8_t CKHkPushObstacle::SelectNextState() {
    if (m_unk70 == nullptr || ProbeMoveTarget() == 0) return -1;
    const int8_t n = CountActivePushers(0);
    const uint8_t ready = AreAllPushersReady();
    IKGrpHero* group = HeroGroup();
    if (n <= 0 && ((m_ui16Flags1e4 >> 6) & 1u) == 0) {
        if ((m_ui8Flags & 8u) == 0 || ready == 0) return -1;
    } else if (ready == 0) {
        return 3;
    }
    if ((m_ui8Flags & 2u) != 0) return 4;
    int8_t result = 4;
    for (uint32_t i = group->GetHeroCount();;) {  // 0x002ca038
        i = (i - 1) & 0xffu;
        if (i == 0xff) break;
        CKHkS08Hero* hero = static_cast<CKHkS08Hero*>(group->m_apHeros[i]);  // 0x002ca080
        if (hero->GetAttachedObject() == this) continue;
        if (IsHeroInGrabArea(hero) == 0) continue;
        result = 3;
    }
    return result;
}

// 0x004358b8 CKHkPushObstacle_UnblockGrabPointCells_maybe: every grab point's cell (the four sides, the dragons) freed
// in the nav grid. The point's node hint is kept from one grab point to the next.
void CKHkPushObstacle::UnblockGrabPointCells() {
    CKSrvPathFinding* pf = PathFinding();
    CPFPoint point;
    point.m_i16GraphNodeIndex = 0xffff;
    for (uint32_t side = 3; side != 0xff; side = (side - 1) & 0xffu) {
        for (uint32_t i = HeroGroup()->GetHeroCount();;) {  // 0x002ca038
            i = (i - 1) & 0xffu;
            if (i == 0xff) break;
            CSGHotSpot* hs = static_cast<CSGHotSpot*>(m_apGrabPoints[side][i]);
            if (hs == nullptr) continue;
            CVector3 pos;
            hs->GetWorldPosition(&pos);  // 0x000ce790
            point.m_position = pos;
            if (static_cast<uint8_t>(pf->FindSectorForPoint(&point)) == 0) continue;
            if (static_cast<uint8_t>(pf->FindSectorForPoint(&point)) == 0) continue;
            SetPointCellBlocked(pf, &point, 0);
        }
    }
}

// 0x00435a80 CKHkPushObstacle_SetPusherCellsBlocked_maybe (no caller: Update inlines it): every pusher's cell (found
// in a nav node) blocked or freed.
void CKHkPushObstacle::SetPusherCellsBlocked(uint8_t blocked) {
    CKSrvPathFinding* pf = PathFinding();
    for (Pusher* p = m_pPushers; p != nullptr; p = p->m_pNext) {
        if (static_cast<int16_t>(p->m_point.m_i16GraphNodeIndex) < 0) continue;
        if (static_cast<uint8_t>(pf->FindSectorForPoint(&p->m_point)) == 0) continue;  // 0x001e5ca0
        SetPointCellBlocked(pf, &p->m_point, blocked);
    }
}

// 0x00434008 CKHkPushObstacle_SnapPushersToGrabPoints_maybe: every pusher's model at its grab point dropped on the
// ground (the hero's ground test, the third ground off meanwhile).
void CKHkPushObstacle::SnapPushersToGrabPoints() {
    for (Pusher* p = m_pPushers; p != nullptr; p = p->m_pNext) {
        CVector3 pos;
        GrabPoint(this, m_i8Side, p->m_i8GrabPoint)->GetWorldPosition(&pos);  // 0x000ce790
        ICollisionMesh* ground = Mesh(m_apGrounds[2]);
        const uint16_t flags = ground->m_ba16EngineFlags;
        ground->SetActive(0);
        Collision()->GroundProbePoints(p->m_pHero->GetGroundContactIn(), &m_GrdContDatasInOut, &pos.x, 1);  // 0x00361ca0
        if (m_GrdContDatasInOut.m_eContactStatus != 3) GroundContact_GetWorldPoint(&m_GrdContDatasInOut, &pos);
        Mesh(m_apGrounds[2])->SetActive(static_cast<uint16_t>(flags & 1u));
        SetFramePosition(FrameOf(p->m_pHero->m_pKGLObject), pos);
    }
}

// 0x004341b8 CKHkPushObstacle_StopMoveFeedbackAndCollision_maybe: the third ground off, then StopMoveFeedbackFx's code.
void CKHkPushObstacle::StopMoveFeedbackAndCollision() {
    Mesh(m_apGrounds[2])->SetActive(0);
    StopMoveFeedbackFx();
}

namespace {
const float kFltMax = 0x1.fffffep+127f;  // the word at 0x00c4acb8 + 0x28 (FLT_MAX), read through TOC1 +0x4f8c
// The nearest grab point of the allowed sides (+0x1a1) to a point on the ground plane (x / z), within 1 unit in y
// (the inlined search of UpdateHeroInteraction / UpdateHeroPush; the node must have been drawn, +0x16). The
// distance (FLT_MAX for none), the side and the index (-1 for none) of the last nearer one.
float NearestGrabPoint(const CKHkPushObstacle* o, const float* pos, int8_t* side, int8_t* index) {
    float best = kFltMax;
    if (static_cast<CSGLeaf*>(o->m_pKGLObject)->m_ui16LastRenderedFrame == 0) return best;
    for (uint32_t s = 3; s != 0xff; s = (s - 1) & 0xffu) {
        if (((o->m_ui8SideBits >> s) & 1u) == 0) continue;
        IKSerializable** points = o->m_apGrabPoints[s];
        for (uint32_t i = o->m_ui8NbDragons;;) {
            i = (i - 1) & 0xffu;
            if (i == 0xff) break;
            CSGHotSpot* hs = static_cast<CSGHotSpot*>(points[i]);
            if (hs == nullptr) continue;
            CVector3 w;
            hs->GetWorldPosition(&w);  // 0x000ce790
            const float dz = w.z - pos[2];
            const float dx = w.x - pos[0];
            const float d = SqrtF(ppc::fmadds(dx, dx, dz * dz));
            const float dy = std::fabs(pos[1] - w.y);
            if (!(dy <= kOne)) continue;
            if (best <= d) continue;  // ble: a NaN distance is taken
            best = d;
            *side = static_cast<int8_t>(s);
            *index = static_cast<int8_t>(i);
        }
    }
    return best;
}
}  // namespace

// 0x00436150 CKHkPushObstacle_UpdateHeroInteraction_maybe: each controlled dragon not attached to the obstacle, near
// it (within the larger of its footprint cells and +0xe4 of the node +0x78) and within +0xe4 of a grab point (no
// enemy in front of that grab point when +0xbc is above 0), becomes the game manager's interaction target (unless
// +0x354 bit 0), and the input icon shows while one does.
void CKHkPushObstacle::UpdateHeroInteraction() {
    uint8_t show = 0;
    IKSerializable** heroes = HeroGroup()->m_apControlledHeroes;  // 0x002ca0e0
    for (; *heroes != nullptr; ++heroes) {
        CKHkS08Hero* hero = static_cast<CKHkS08Hero*>(*heroes);
        if (hero->GetAttachedObject() == this) continue;  // 0x00361d50
        const float* pos = hero->GetPositionPtr();        // 0x00361968
        const uint8_t cells = m_ui8CellsA > m_ui8CellsB ? m_ui8CellsA : m_ui8CellsB;
        const float fc = static_cast<float>(cells);
        float reach = m_fGrabRadius;
        if (!(fc < reach)) reach = fc;
        reach = reach * reach;
        const RwV3d& centre = FrameOf(m_unk78)->modelling.pos;  // frame +0x40
        const float dy = centre.y - pos[1];
        const float dx = centre.x - pos[0];
        const float dz = centre.z - pos[2];
        if (!(reach > ppc::fmadds(dz, dz, ppc::fmadds(dx, dx, dy * dy)))) continue;  // bgt
        int8_t side = -1;
        int8_t index = -1;
        const float best = NearestGrabPoint(this, hero->GetPositionPtr(), &side, &index);
        if (m_fGrabRadius <= best) continue;  // ble
        IKGrpEnemy* enemies = static_cast<IKGrpEnemy*>(g_pEngine->m_gameManager->m_unk04[0]);  // engine +0x8c -> +0x04
        if (enemies != nullptr && m_fEnemyConeCheck > kZero) {
            CMatrix34 m;
            GrabPoint(this, side, index)->GetWorldMatrix(&m);  // 0x000ce970
            const float s = g_pfGridScale.m_cellSize;
            CVector3 d = {-m.m_at.x, -m.m_at.y, -m.m_at.z};
            const float len = SqrtF(LengthSq(d.x, d.y, d.z));
            if (len != kZero) {
                const float f = (s * kHalf) / len;
                d.z = d.z * f;
                d.x = d.x * f;
                d.y = d.y * f;
            }
            const CVector3 at = {d.x + m.m_pos.x, d.y + m.m_pos.y, d.z + m.m_pos.z};
            if (enemies->IsAnyEnemyInCone(kPi, m_fEnemyConeCheck, &at, &d) != 0) continue;  // 0x002665a0
        }
        if (static_cast<uint8_t>(hero->GetFlag354Bit0()) != 0) continue;  // 0x00361a90
        show = 1;
        // 0x00362ac8 CKHkS08Hero_GetPlayerIndexIfControlled_maybe: the leader index of a player's dragon, else -1.
        const uint8_t player = hero->m_ui8Hero == hero->m_ui8TrackedLeader ? hero->m_ui8Leader : 0xff;
        static_cast<CKS08GameManager*>(g_pEngine->m_gameManager)->SetHeroInteractionTarget(this, 1, player);  // 0x004ee770
    }
    ShowInputIcon(show & 1);
}

// 0x0043b290 CKHkPushObstacle_UpdateHeroPush_maybe. A dragon switch (+0x1e4 bit 3): the new player's dragon near a
// grab point (within +0xe4) takes over: the pushers let go, starter 8, the pending side +0x187 becomes the side and
// the dragons attach again. Then each pusher not ready walks to its grab point (UpdateMoveTo); on arrival it is locked
// there facing the grab point (on the ground), the object drives its animation (a crossfade of a random 0.1..0.3 to
// its rest animation) and state 1 waits 0.4 (+0x1e4 bit 7, +0x19c). A player's dragon without input lets go of the
// obstacle (unless a switch is pending, bits 6 / 7 or +0x158 bit 3): starters 8 and 9. All arrived this frame:
// starter 7, +0x1e4 bit 2, the pushers' cells from their models, and with two pushers the grab volume +0xac on the
// pushed side, joined to the collision.
void CKHkPushObstacle::UpdateHeroPush(IKTime* clock) {
    if (((m_ui16Flags1e4 >> 3) & 1u) != 0) {
        m_ui16Flags1e4 = static_cast<uint16_t>(m_ui16Flags1e4 & 0xfff7u);
        CKHkS08Hero* hero = static_cast<CKHkS08Hero*>(HeroGroup()->m_apControlledHeroes[0]);  // 0x002ca0e0
        if (hero->GetPlayerInputFloat38C() != kZero && hero->GetAttachedObject() != this) {  // 0x003626f8
            const RwV3d& hp = FrameOf(hero->m_pKGLObject)->ltm.pos;  // frame +0x80
            const float pos[3] = {hp.x, hp.y, hp.z};
            int8_t side = -1;
            int8_t index = -1;
            const float best = NearestGrabPoint(this, pos, &side, &index);
            if (!(m_fGrabRadius <= best)) {  // ble
                DetachPushingHeroes(0);
                QueueTriggerSignals(&m_aStarters[8]);  // +0x140
                m_i8Side = m_i8PendingSide;
                m_i8PendingSide = -1;
                AttachHeroesToGrabPoints();
                if (m_pPushers == nullptr) m_i8Side = -1;
                return;
            }
        }
    }
    uint32_t waiting = 0;
    for (Pusher* p = m_pPushers; p != nullptr; p = p->m_pNext) ++waiting;
    uint8_t arrived = 0;
    for (Pusher* p = m_pPushers; p != nullptr; p = p->m_pNext) {
        if (p->m_bReady != 0) {
            --waiting;
        } else {
            const uint8_t ready = p->m_pHero->UpdateMoveTo(clock, nullptr);  // vt+0xd0
            p->m_bReady = ready;
            if (m_pPushers == nullptr) return;
            if (ready != 0) {
                CKHkS08Hero* hero = p->m_pHero;
                hero->SetLockedToObject(1, nullptr, nullptr);  // 0x003622a8
                p->m_pHero->SetObjectControlsAnim(1);           // 0x00362010
                CMatrix34 m;
                GrabPoint(this, m_i8Side, p->m_i8GrabPoint)->GetWorldMatrix(&m);  // 0x000ce970
                CVector3 pos = m.m_pos;
                Collision()->GroundProbePoints(p->m_pHero->GetGroundContactIn(), &m_GrdContDatasInOut, &pos.x, 1);
                if (m_GrdContDatasInOut.m_eContactStatus != 3) GroundContact_GetWorldPoint(&m_GrdContDatasInOut, &pos);
                --waiting;
                arrived = 1;
                CSGMovable* model = static_cast<CSGMovable*>(p->m_pHero->m_pKGLObject);
                SetFramePosition(model->m_pRwFrame, pos);
                model->SetOrientationFromAtUp(&m.m_at, &kAxisY);  // 0x000d0918
                const uint32_t word = HeroAnimWord(this, p->m_pHero, 0);
                const uint32_t r = static_cast<uint32_t>(Rand_Int()) & 0xffffu;  // 0x00011500
                float t = static_cast<float>(r) / kRandMax;
                t = t + t;
                t = t * kBlendPush;
                p->m_pHero->CrossfadeAnimResource(ppc::fmadds(t, kMinusHalf, kBlendRest), kZero, word, 1);  // vt+0xc4
                m_ui16Flags1e4 = static_cast<uint16_t>(m_ui16Flags1e4 | 0x80u);
                m_fIdleTimer = kBlendIdle;  // 0.4
            }
        }
        if (static_cast<uint8_t>(p->m_pHero->IsPlayerControlled()) == 0) continue;  // 0x00362af0
        if (static_cast<uint8_t>(static_cast<CKGrpS08Hero*>(HeroGroup())->IsDragonSwitchPending()) != 0) continue;
        if ((m_ui16Flags1e4 & 0x80u) != 0 || (m_ui16Flags1e4 & 0x40u) != 0 || (m_ui8Flags & 8u) != 0) continue;
        if (p->m_pHero->GetPlayerInputFloat38C() != kZero) continue;
        DetachPushingHeroes(0);
        QueueTriggerSignals(&m_aStarters[8]);  // +0x140
        QueueTriggerSignals(&m_aStarters[9]);  // +0x148
        return;
    }
    if (m_i8Side < 0 || (waiting & 0xffu) != 0 || arrived == 0) return;
    QueueTriggerSignals(&m_aStarters[7]);  // +0x138
    m_ui16Flags1e4 = static_cast<uint16_t>(m_ui16Flags1e4 | 4u);
    uint32_t count = 0;
    for (Pusher* p = m_pPushers; p != nullptr; p = p->m_pNext) {
        p->m_pHero->SetFlag35CBit21IfAttached(0);  // 0x00363fc8
        const RwV3d& hp = FrameOf(p->m_pHero->m_pKGLObject)->ltm.pos;  // frame +0x80
        p->m_point.m_position.z = hp.z;
        p->m_point.m_position.x = hp.x;
        p->m_point.m_position.y = hp.y;
    }
    for (Pusher* p = m_pPushers; p != nullptr; p = p->m_pNext) ++count;
    if (count != 2) return;
    // The cells along / across the pushed side (+0xd8, +0xd9 when the node faces Z or -Z within 0.1, else swapped).
    const RwV3d& at = NodeOf(this)->m_pRwFrame->modelling.at;  // frame +0x30
    uint32_t a = m_ui8CellsA;
    uint32_t b = m_ui8CellsB;
    if (!NearAxis(at, kAxisZ) && !NearAxis(at, kAxisNegZ)) {
        a = m_ui8CellsB;
        b = m_ui8CellsA;
    }
    // BUG(original): with a side above 3 the position is the caller's floating-point registers (0 here).
    CVector3 pos = {0.0f, 0.0f, 0.0f};
    switch (m_i8Side) {
    case 0: pos = {static_cast<float>(a) * kHalf, m_fVolumeHeight * kHalf, kZero}; break;
    case 1: pos = {kZero, m_fVolumeHeight * kHalf, static_cast<float>(b) * kHalf}; break;
    case 2: pos = {static_cast<float>(-static_cast<int32_t>(a)) * kHalf, m_fVolumeHeight * kHalf, kZero}; break;
    case 3: pos = {kZero, m_fVolumeHeight * kHalf, static_cast<float>(-static_cast<int32_t>(b)) * kHalf}; break;
    default: break;
    }
    SetFramePosition(FrameOf(m_unkac), pos);
    Collision()->AddVolume(static_cast<IKBoundingVolume*>(m_unkac));  // 0x00192b80
}

namespace {
// The point's node (just found) holds it: a valid node index whose sector box contains the point (the inlined test of
// CanPushInDirection, CheckGrabPointsForHero, AttachHeroesToGrabPoints and IsHeroOnMoveTrajectory; unordered fails).
bool NodeBoxHolds(const CKSrvPathFinding* pf, const CPFPoint& point) {
    const int16_t index = static_cast<int16_t>(point.m_i16GraphNodeIndex);
    if (index < 0) return false;
    if (static_cast<uint32_t>(static_cast<int32_t>(index)) >= pf->m_Graph.m_ui32GraphNodesSize) return false;
    const CBBox& box = static_cast<const CKPFGraphNode*>(pf->m_Graph.m_apGraphNodes[point.m_i16GraphNodeIndex])->m_Sector.m_box;
    const CVector3& p = point.m_position;
    if (!(box.m_inf.x <= p.x) || !(box.m_sup.x >= p.x)) return false;
    if (!(box.m_inf.z <= p.z) || !(box.m_sup.z >= p.z)) return false;
    return box.m_inf.y <= p.y && box.m_sup.y >= p.y;
}
// The distance on the ground plane from a hero's model (its LTM position) to a point (dz squared, then dx fused on).
float FlatDistance(CKHkS08Hero* hero, const CVector3& p) {
    const RwV3d& hp = FrameOf(hero->m_pKGLObject)->ltm.pos;  // frame +0x80
    const float dz = hp.z - p.z;
    const float dx = hp.x - p.x;
    return SqrtF(ppc::fmadds(dx, dx, dz * dz));
}
// The point's cell centre (x or z) for the inlined snaps (lroundf of the half-cell-shifted coordinate).
float SnapToCell(float v, float s, float h) { return ppc::fmsubs(s, static_cast<float>(crt::lroundf((h + v) / s)), h); }
CKSekensLauncherCpnt* Sekens(const CKHkPushObstacle* o) { return static_cast<CKSekensLauncherCpnt*>(o->m_unka4); }
}  // namespace

// 0x004351a8 CKHkPushObstacle_IsHeroInGrabArea_maybe: the hero's model, snapped to its cell's centre, is strictly
// inside the footprint (x / z, the footprint matrix of the facing, dropped on the ground); a NaN passes the first
// three bounds and fails the last.
uint8_t CKHkPushObstacle::IsHeroInGrabArea(CKHkS08Hero* hero) {
    CVector3 at;
    const int32_t facing = ExactFacing(this, &at);
    const float a = static_cast<float>(m_ui8HalfA);
    const float b = static_cast<float>(m_ui8HalfB);
    const float na = static_cast<float>(-static_cast<int32_t>(m_ui8HalfA));
    const float nb = static_cast<float>(-static_cast<int32_t>(m_ui8HalfB));
    // BUG(original): off the axes the box's x / z are stack garbage (0 here).
    CVector3 lo = {0.0f, 0.0f, 0.0f};
    CVector3 hi = {0.0f, 0.0f, 0.0f};
    CVector3 centre = {m_unk188.x, m_fHeight * kHalf, m_unk188.z};
    switch (facing) {
    case 0: lo.x = na * kHalf; lo.z = nb * kHalf; hi.x = a * kHalf; hi.z = b * kHalf; break;
    case 1: lo.x = b * kHalf; lo.z = na * kHalf; hi.x = nb * kHalf; hi.z = a * kHalf; break;
    case 2: lo.x = a * kHalf; lo.z = b * kHalf; hi.x = na * kHalf; hi.z = nb * kHalf; break;
    case 3: lo.x = nb * kHalf; lo.z = a * kHalf; hi.x = b * kHalf; hi.z = na * kHalf; break;
    default: break;
    }
    CentreOffset(this, facing, &centre.x, &centre.z);
    hi.x = hi.x + centre.x;
    lo.x = lo.x + centre.x;
    hi.y = hi.y + centre.y;
    hi.z = hi.z + centre.z;
    lo.y = lo.y + centre.y;
    lo.z = lo.z + centre.z;
    CMatrix34 m;
    FootprintMatrix(this, &at, &m);
    CVector3 in = centre;
    Mat4_TransformPoints(&m, &centre, &in, 1);  // 0x0023f7e8
    in = lo;
    Mat4_TransformPoints(&m, &lo, &in, 1);
    in = hi;
    Mat4_TransformPoints(&m, &hi, &in, 1);
    const RwV3d& hp = FrameOf(hero->m_pKGLObject)->ltm.pos;  // frame +0x80
    const float s = g_pfGridScale.m_cellSize;
    const float h = s * kHalf;
    const float hx = SnapToCell(hp.x, s, h);
    const int32_t zi = crt::lroundf((hp.z + h) / s);  // 0x0098d3a0
    Collision()->GroundProbePoints(&m_GrdContDatasIn, &m_GrdContDatasInOut, &centre.x, 1);  // 0x00196540
    if (m_GrdContDatasInOut.m_eContactStatus != 3) {
        GroundContact_GetWorldPoint(&m_GrdContDatasInOut, &centre);  // 0x001a70e0
        hi.y = centre.y;
        lo.y = centre.y;
    }
    if (lo.x >= hx) return 0;  // bge
    if (hi.x <= hx) return 0;  // ble
    const float hz = ppc::fmsubs(s, static_cast<float>(zi), h);
    if (lo.z >= hz) return 0;
    return hz < hi.z ? 1 : 0;
}

namespace {
// A hero takes the grab point `index` (the inlined pusher creation of CheckGrabPointsForHero and
// AttachHeroesToGrabPoints): a new pusher at the head of the list (no cell), attached, walking to the grab point.
void AddPusher(CKHkPushObstacle* o, CKHkS08Hero* hero, int8_t index, const CMatrix34& m) {
    Pusher* p = new Pusher();  // the FreeListPool 0x00ceaa20's free list +0x74 (grown by 0x00244908) in the original
    p->m_point.m_i16GraphNodeIndex = 0xffff;
    p->m_pNext = o->m_pPushers;
    o->m_pPushers = p;
    p->m_i8GrabPoint = index;
    p->m_pHero = hero;
    p->m_unk18 = 0;
    p->m_bPushing = 0;
    p->m_bReady = 0;
    p->m_bHandFx = 0;
    p->m_pHero->AttachToObject(o, 1);             // 0x00362360
    p->m_pHero->SetAttachedMovementEnabled(1);    // 0x00362050
    p->m_pHero->SetFlag35CBit21IfAttached(1);     // 0x00363fc8
    p->m_pHero->SetMoveDestination(o->m_fMoveToTimeout, &m.m_pos, &m.m_at, 0, 0, 1);  // vt+0xcc
}
bool GrabPointTaken(const CKHkPushObstacle* o, int8_t index) {
    for (const Pusher* p = o->m_pPushers; p != nullptr; p = p->m_pNext) {
        if (p->m_i8GrabPoint == index) return true;
    }
    return false;
}
}  // namespace

// 0x004342c0 CKHkPushObstacle_CheckGrabPointsForHero_maybe: the candidate (+0x17c) takes the nearest free grab point of
// the side that is in a nav node, inside its box and walkable for the candidate (when it may attach); the dragon
// switch is locked unless +0x158 bit 0 or 3.
void CKHkPushObstacle::CheckGrabPointsForHero() {
    CKSrvPathFinding* pf = PathFinding();
    if ((m_ui8Flags & 1u) == 0 && ((m_ui8Flags >> 3) & 1u) == 0) {
        static_cast<CKGrpS08Hero*>(HeroGroup())->SetDragonSwitchLocked(1);  // 0x002ca1b8
    }
    float best = kFltMax;
    int8_t chosen = -1;
    for (uint32_t i = m_ui8NbDragons;;) {
        i = (i - 1) & 0xffu;
        if (i == 0xff) break;
        CSGHotSpot* hs = GrabPoint(this, m_i8Side, static_cast<int32_t>(i));
        if (hs == nullptr) continue;
        if (GrabPointTaken(this, static_cast<int8_t>(i))) continue;
        CMatrix34 m;
        hs->GetWorldMatrix(&m);  // 0x000ce970
        CPFPoint point;
        point.m_i16GraphNodeIndex = 0xffff;
        point.m_position = m.m_pos;
        if (m_pCandidateHero->GetAttachedObject() == this) continue;  // 0x00361d50
        const float d = FlatDistance(m_pCandidateHero, m.m_pos);
        if (best <= d) continue;  // ble
        if (static_cast<uint8_t>(pf->FindSectorForPoint(&point)) == 0) continue;  // 0x001e5ca0
        const CPFCharacter* character = m_pCandidateHero->GetPFCharacter();  // 0x00361a30
        if (!NodeBoxHolds(pf, point)) continue;
        if (static_cast<uint8_t>(pf->IsPointWalkable(&point, character)) == 0) continue;  // 0x001e42d0
        best = d;
        chosen = static_cast<int8_t>(i);
    }
    if (chosen == -1) return;
    if (m_pCandidateHero->CanAttachTo(this, 1) == 0) return;  // vt+0xe0 (0x00361d08)
    Pusher* p = new Pusher();  // the FreeListPool 0x00ceaa20 in the original
    p->m_point.m_i16GraphNodeIndex = 0xffff;
    p->m_pNext = m_pPushers;
    m_pPushers = p;
    p->m_bHandFx = 0;
    p->m_unk18 = 0;
    p->m_bPushing = 0;
    p->m_bReady = 0;
    p->m_i8GrabPoint = chosen;
    p->m_pHero = m_pCandidateHero;
    CMatrix34 m;
    GrabPoint(this, m_i8Side, chosen)->GetWorldMatrix(&m);
    p->m_pHero->AttachToObject(this, 1);
    p->m_pHero->SetAttachedMovementEnabled(1);
    p->m_pHero->SetFlag35CBit21IfAttached(1);
    p->m_pHero->SetMoveDestination(m_fMoveToTimeout, &m.m_pos, &m.m_at, 0, 0, 1);  // vt+0xcc
}

// 0x00434728 CKHkPushObstacle_AttachHeroesToGrabPoints_maybe: every free grab point of the side gets the nearest
// dragon that may take it (not attached; a companion, a non-player, or the candidate +0x17c; the point in a nav node,
// inside its box, walkable for the dragon), else the nearest that may attach of the others (no player but the
// candidate). One that may not attach yields to the runner-up; else (unless sekens 0..2 runs) the dragon's sekens
// plays and the game manager's vt+0x2b8 hint (empty) is asked for both. With every grab point taken, one of the
// sekens bits 9 / 10 / 11 is drawn (about half each; bit 9 plays sekens 3 + the player's dragon at once).
void CKHkPushObstacle::AttachHeroesToGrabPoints() {
    CKSrvPathFinding* pf = PathFinding();
    if ((m_ui8Flags & 1u) == 0 && ((m_ui8Flags >> 3) & 1u) == 0) {
        static_cast<CKGrpS08Hero*>(HeroGroup())->SetDragonSwitchLocked(1);  // 0x002ca1b8
    }
    uint8_t allTaken = 1;
    for (uint32_t i = m_ui8NbDragons;;) {
        i = (i - 1) & 0xffu;
        if (i == 0xff) break;
        CSGHotSpot* hs = GrabPoint(this, m_i8Side, static_cast<int32_t>(i));
        if (hs == nullptr) continue;
        if (GrabPointTaken(this, static_cast<int8_t>(i))) continue;
        CMatrix34 m;
        hs->GetWorldMatrix(&m);  // 0x000ce970
        CPFPoint point;
        point.m_i16GraphNodeIndex = 0xffff;
        point.m_position = m.m_pos;
        int8_t chosen = -1;
        int8_t runnerUp = -1;
        float best = kFltMax;
        uint32_t n = m_ui8NbDragons;
        if (n != 0) {
            for (uint32_t d = 0;;) {
                CKHkS08Hero* hero = static_cast<CKHkS08Hero*>(HeroGroup()->m_apHeros[d & 0xffu]);  // 0x002ca080
                if (hero->GetAttachedObject() != this &&
                    (hero->PassesTrackerAssignFlagChecks() != 0 || static_cast<uint8_t>(hero->IsPlayerControlled()) == 0 ||
                     m_pCandidateHero == hero)) {
                    const float dist = FlatDistance(hero, m.m_pos);
                    if (!(best <= dist) && static_cast<uint8_t>(pf->FindSectorForPoint(&point)) != 0) {
                        const CPFCharacter* character = hero->GetPFCharacter();  // 0x00361a30
                        if (NodeBoxHolds(pf, point) && static_cast<uint8_t>(pf->IsPointWalkable(&point, character)) != 0) {
                            best = dist;
                            runnerUp = chosen;
                            chosen = static_cast<int8_t>(d);
                        }
                    }
                }
                ++d;
                n = m_ui8NbDragons;
                if (!(n > (d & 0xffu))) break;
            }
        }
        if (chosen < 0) {
            best = kFltMax;
            for (uint32_t d = n;;) {
                d = (d - 1) & 0xffu;
                if (d == 0xff) break;
                CKHkS08Hero* hero = static_cast<CKHkS08Hero*>(HeroGroup()->m_apHeros[d]);
                if (hero->GetAttachedObject() == this) continue;
                if (static_cast<uint8_t>(hero->IsPlayerControlled()) != 0 && m_pCandidateHero != hero) continue;
                if (hero->CanAttachTo(this, 1) == 0) continue;  // vt+0xe0
                const float dist = FlatDistance(hero, m.m_pos);
                if (best <= dist) continue;  // ble
                if (static_cast<uint8_t>(pf->FindSectorForPoint(&point)) == 0) continue;
                const CPFCharacter* character = hero->GetPFCharacter();
                if (!NodeBoxHolds(pf, point)) continue;
                if (static_cast<uint8_t>(pf->IsPointWalkable(&point, character)) == 0) continue;
                best = dist;
                chosen = static_cast<int8_t>(d);
            }
            if (chosen < 0) continue;
        }
        CKHkS08Hero* hero = static_cast<CKHkS08Hero*>(HeroGroup()->m_apHeros[static_cast<uint8_t>(chosen)]);
        if (hero->CanAttachTo(this, 1) != 0) {
            AddPusher(this, hero, static_cast<int8_t>(i), m);
            continue;
        }
        if (runnerUp != -1) {
            CKHkS08Hero* other = static_cast<CKHkS08Hero*>(HeroGroup()->m_apHeros[static_cast<uint8_t>(runnerUp)]);
            if (other != nullptr && other->CanAttachTo(this, 1) != 0) {
                AddPusher(this, other, static_cast<int8_t>(i), m);
                continue;
            }
        }
        if (Sekens(this)->IsSekensCurrent(0) != 0 || Sekens(this)->IsSekensCurrent(1) != 0 ||  // 0x001f7b98
            Sekens(this)->IsSekensCurrent(2) != 0) {
            continue;
        }
        if (static_cast<CKHkS08Hero*>(HeroGroup()->m_apHeros[static_cast<uint8_t>(chosen)])->CallVf140() != 0) {  // 0x00361df8
            Sekens(this)->PlaySekens(static_cast<uint32_t>(static_cast<int32_t>(chosen)));  // 0x001f7730
        }
        // The game manager's vt+0x2b8 (0x009c69c0 CKS08GameManager_vf2B8, empty) for the dragon and the runner-up,
        // with 10.0 (TOC1 +0x4ff8): nothing to do here.
        allTaken = 0;
    }
    m_ui16Flags1e4 = static_cast<uint16_t>(m_ui16Flags1e4 & 0xf1ffu);
    if (allTaken == 0) return;
    // Sekens bits: a draw of r * 100 above 0x32ffff for bit 9, else one for bit 10, else bit 11.
    uint32_t r = static_cast<uint32_t>(Rand_Int()) & 0xffffu;  // 0x00011500
    m_ui16Flags1e4 = static_cast<uint16_t>((m_ui16Flags1e4 & 0xfdffu) | (r * 100u > 0x32ffffu ? 0x200u : 0u));
    if ((m_ui16Flags1e4 & 0x200u) == 0) {
        r = static_cast<uint32_t>(Rand_Int()) & 0xffffu;
        m_ui16Flags1e4 = static_cast<uint16_t>((m_ui16Flags1e4 & 0xfbffu) | (r * 100u > 0x32ffffu ? 0x400u : 0u));
        if ((m_ui16Flags1e4 & 0x400u) == 0) m_ui16Flags1e4 = static_cast<uint16_t>(m_ui16Flags1e4 | 0x800u);
    }
    if (((m_ui16Flags1e4 >> 9) & 1u) != 0) {
        CKHkS08Hero* player = static_cast<CKHkS08Hero*>(HeroGroup()->m_apControlledHeroes[0]);  // 0x002ca0e0
        Sekens(this)->PlaySekens(static_cast<uint32_t>((player->GetDragonIndex() & 0xffu) + 3));  // 0x00361960
    }
}

// 0x00436ba8 CKHkPushObstacle_IsHeroOnMoveTrajectory_maybe: the hero's model, snapped to its cell, is one of the cells
// the footprint sweeps from the start corner along the pushed side (as many as the footprint's depth), within 0.1;
// then 1 unless the cell a step further along the side is walkable for the hero in its nav node (0 when no cell
// matches).
uint8_t CKHkPushObstacle::IsHeroOnMoveTrajectory(CKHkS08Hero* hero) {
    const float s = g_pfGridScale.m_cellSize;  // 0x00c4025c
    const float h = s * kHalf;
    const RwV3d& hp = FrameOf(hero->m_pKGLObject)->ltm.pos;  // frame +0x80
    const float hy = hp.y;
    const float hx = SnapToCell(hp.x, s, h);
    const int32_t zi = crt::lroundf((hp.z + h) / s);  // 0x0098d3a0
    const float cs = g_pfGridScale.m_cellSize;
    const float hz = ppc::fmsubs(s, static_cast<float>(zi), h);
    CKSrvPathFinding* pf = PathFinding();
    CVector3 c;
    ComputeFootprintCorner(&c);
    if (m_i8Side >= 0) m_i8LastSide = m_i8Side;
    CMatrix34 m;
    GrabPoint(this, m_i8LastSide, 0)->GetWorldMatrix(&m);  // 0x000ce970
    // The side's axis, the back axis and the footprint's (along, across) cells. BUG(original): off the axes they are
    // the caller's registers (0 here).
    CVector3 d1 = {0.0f, 0.0f, 0.0f};
    CVector3 d2 = {0.0f, 0.0f, 0.0f};
    uint32_t cellsAlong = 0;
    uint32_t cellsAcross = 0;
    switch (SideAxis(m)) {
    case 0: d1 = kAxisX; d2 = kAxisNegZ; cellsAlong = m_ui8CellsA; cellsAcross = m_ui8CellsB; break;
    case 1: d1 = kAxisNegX; d2 = kAxisZ; cellsAlong = m_ui8CellsA; cellsAcross = m_ui8CellsB; break;
    case 2: d1 = kAxisZ; d2 = kAxisX; cellsAlong = m_ui8CellsB; cellsAcross = m_ui8CellsA; break;
    case 3: d1 = kAxisNegZ; d2 = kAxisNegX; cellsAlong = m_ui8CellsB; cellsAcross = m_ui8CellsA; break;
    default: break;
    }
    const uint32_t count = cellsAcross & 0xffu;
    const float alongK = ppc::fmadds(cs, kHalf, (static_cast<float>(cellsAlong) * kHalf) / cs);
    const float acrossK = ppc::fmadds(cs, kMinusHalf, (static_cast<float>(static_cast<int32_t>(count)) * kHalf) / cs);
    CVector3 v1 = {alongK * d1.x, d1.y * alongK, d1.z * alongK};
    CVector3 w = {-(acrossK * d2.x), -(d2.y * acrossK), -(d2.z * acrossK)};
    c.y = c.y + (v1.y + w.y);
    c.x = c.x + (v1.x + w.x);
    c.z = c.z + (v1.z + w.z);
    float len = SqrtF(LengthSq(w.x, w.y, w.z));
    if (len != kZero) {
        const float f = kOne / len;
        w.z = w.z * f;
        w.x = w.x * f;
        w.y = w.y * f;
    }
    CVector3 step = {-w.x, -w.y, -w.z};
    len = SqrtF(LengthSq(step.x, step.y, step.z));
    if (len != kZero) {
        const float f = cs / len;
        step.z = step.z * f;
        step.y = step.y * f;
        step.x = step.x * f;
    }
    len = SqrtF(LengthSq(v1.x, v1.y, v1.z));
    if (len != kZero) {
        const float f = cs / len;
        v1.z = v1.z * f;
        v1.x = v1.x * f;
        v1.y = v1.y * f;
    }
    for (uint32_t i = 0; i != count; ++i) {
        const float s2 = g_pfGridScale.m_cellSize;
        const float h2 = s2 * kHalf;
        const int32_t xi = crt::lroundf((h2 + c.x) / s2);
        const float zArg = (h2 + c.z) / s2;
        c.x = ppc::fmsubs(s2, static_cast<float>(xi), h2);
        c.z = ppc::fmsubs(s2, static_cast<float>(crt::lroundf(zArg)), h2);
        if (c.x - kTenth <= hx && c.x + kTenth >= hx && c.y - kTenth <= hy && c.y + kTenth >= hy &&
            c.z - kTenth <= hz && c.z + kTenth >= hz) {
            CPFPoint point;
            point.m_position = {v1.x + c.x, c.y + v1.y, c.z + v1.z};
            point.m_i16GraphNodeIndex = 0xffff;
            if (static_cast<uint8_t>(pf->FindSectorForPoint(&point)) == 0) return 1;  // 0x001e5ca0
            const CPFCharacter* character = hero->GetPFCharacter();  // 0x00361a30
            if (!NodeBoxHolds(pf, point)) return 1;
            return static_cast<uint8_t>(static_cast<uint8_t>(pf->IsPointWalkable(&point, character)) ^ 1u);  // 0x001e42d0
        }
        c.x = c.x + step.x;
        c.y = c.y + step.y;
        c.z = c.z + step.z;
    }
    return 0;
}

// 0x004337a0 CKHkPushObstacle_StartPushFxAndSound_maybe (unless +0x158 bit 4): the push effect (+0x94) reset under its
// node with three emit points along the pushed side at half the effect height (+0xec), or without a point list its
// emitter box and position, then emitting; the hand effect (+0x90) restarted with the pushing heroes' two hand points
// each (at most 64; their +0x17 set), emitting; the push loop (sound 3) plays.
void CKHkPushObstacle::StartPushFxAndSound() {
    if (((m_ui8Flags >> 4) & 1u) != 0) return;
    CParticlesNodeFx* fx = Fx(m_pPushFx);
    fx->SetIdentity();  // 0x000d08f0
    // The cells along / across the pushed side (+0xd8, +0xd9 when the node faces Z or -Z within 0.1, else swapped).
    const RwV3d& nodeAt = NodeOf(this)->m_pRwFrame->modelling.at;  // frame +0x30
    uint32_t p = m_ui8CellsA;
    uint32_t q = m_ui8CellsB;
    if (!NearAxis(nodeAt, kAxisZ) && !NearAxis(nodeAt, kAxisNegZ)) {
        p = m_ui8CellsB;
        q = m_ui8CellsA;
    }
    const float h = m_fFxHeight * kHalf;
    const float pp = static_cast<float>(p) * kHalf;
    const float np = static_cast<float>(-static_cast<int32_t>(p)) * kHalf;
    const float pq = static_cast<float>(q) * kHalf;
    const float nq = static_cast<float>(-static_cast<int32_t>(q)) * kHalf;
    // The three points, the emitter box and the node position per side. BUG(original): with no side they are the
    // caller's registers (0 here).
    CVector3 pts[3] = {};
    CVector3 size = {0.0f, 0.0f, 0.0f};
    CVector3 pos = {0.0f, 0.0f, 0.0f};
    switch (m_i8Side) {
    case 0:
        pts[0] = {np, h, nq}; pts[1] = {np, h, 0.0f}; pts[2] = {np, h, pq};
        size = {kTenth, m_fFxHeight, pq}; pos = {np, h, 0.0f};
        break;
    case 1:
        pts[0] = {np, h, nq}; pts[1] = {0.0f, h, nq}; pts[2] = {pp, h, nq};
        size = {pp, m_fFxHeight, kTenth}; pos = {0.0f, h, nq};
        break;
    case 2:
        pts[0] = {pp, h, nq}; pts[1] = {pp, h, 0.0f}; pts[2] = {pp, h, pq};
        size = {kTenth, m_fFxHeight, pq}; pos = {pp, h, 0.0f};
        break;
    case 3:
        pts[0] = {np, h, pq}; pts[1] = {0.0f, h, pq}; pts[2] = {pp, h, pq};
        size = {pp, m_fFxHeight, kTenth}; pos = {0.0f, h, pq};
        break;
    default:
        break;
    }
    if (fx->m_pAdvEmtPointList != nullptr) {
        SetThreeEmitPoints(fx, pts);
    } else {
        RpPrtStdEmitter* emitter = fx->m_pRpPrtStdEmitter;
        RpPrtStdEmitterStandard* standard = reinterpret_cast<RpPrtStdEmitterStandard*>(
            reinterpret_cast<uint8_t*>(emitter) + emitter->emtClass->propTab->propOffset[1]);
        standard->emtSize.x = size.x;
        standard->emtSize.y = size.y;
        standard->emtSize.z = size.z;
        SetFramePosition(Fx(m_pPushFx)->m_pRwFrame, pos);
    }
    // +0x158 bit 4 is clear here: the effect starts emitting.
    StartEmitting(Fx(m_pPushFx));
    CParticlesNodeFx* hands = Fx(m_pHandFx);
    if (hands->m_pAdvEmtPointList != nullptr) {
        if (hands->m_ui8NbActivePoints != 0) {
            hands->m_ui8NbActivePoints = 0;
            hands->m_sgProperties = (hands->m_sgProperties & 0xffffdfffu) | 0x2000u;
        }
        IKGrpHero* group = HeroGroup();
        for (Pusher* p2 = m_pPushers; p2 != nullptr; p2 = p2->m_pNext) {
            if (p2->m_bPushing == 0) continue;
            CVector3 left;
            CVector3 right;
            static_cast<CSGHotSpot*>(p2->m_pHero->GetHotSpot(group->GetHotSpotIndex(p2->m_pHero->GetDragonIndex(), 2)))
                ->GetWorldPosition(&left);  // 0x002ca298, 0x00361b70, 0x000ce790
            static_cast<CSGHotSpot*>(p2->m_pHero->GetHotSpot(group->GetHotSpotIndex(p2->m_pHero->GetDragonIndex(), 3)))
                ->GetWorldPosition(&right);
            const CVector3 both[2] = {left, right};
            for (const CVector3& point : both) {
                CParticlesNodeFx* hfx = Fx(m_pHandFx);
                if (hfx->m_ui8NbActivePoints > 0x3f) continue;
                RwV3d& out = hfx->m_pAdvEmtPointList->pointList[hfx->m_ui8NbActivePoints];
                out.z = point.z;
                out.x = point.x;
                out.y = point.y;
                hfx->m_sgProperties = (hfx->m_sgProperties & 0xffffdfffu) | 0x2000u;
                hfx->m_ui8NbActivePoints = static_cast<uint8_t>(hfx->m_ui8NbActivePoints + 1);
            }
            p2->m_bHandFx = 1;
        }
    }
    StartEmitting(Fx(m_pHandFx));
    CKSound* sound = Sounds(this)->GetSound(3);  // 0x00112bc0
    sound->SetLoop(1);                           // 0x00110fd0
    Sounds(this)->GetSound(3)->Play(kZero);      // 0x00111230
}

namespace {
void Hide(IKSerializable* node) {
    CSGLeaf* leaf = static_cast<CSGLeaf*>(node);
    leaf->m_sgProperties = (leaf->m_sgProperties & 0xfffffffbu) | 4u;
}
void Show(IKSerializable* node) { static_cast<CSGLeaf*>(node)->m_sgProperties &= 0xfffffffbu; }
// The node +0x78 placed at a node's LTM position (frame +0x80).
void FollowNode(const CKHkPushObstacle* o, IKSerializable* node) {
    const RwV3d& p = FrameOf(node)->ltm.pos;
    SetFramePosition(FrameOf(o->m_unk78), CVector3{p.x, p.y, p.z});
}
// A dynamic ground's inlined refresh (once per frame: flag 0x20; while active its parent's matrix, the inverse and
// the world box).
void RefreshDynamicGround(IKSerializable* g) {
    CDynamicGround* ground = static_cast<CDynamicGround*>(g);
    if ((ground->m_ba16EngineFlags & 0x20u) != 0) return;
    ground->m_ba16EngineFlags = static_cast<uint16_t>(ground->m_ba16EngineFlags | 0x20u);
    if ((ground->m_ba16EngineFlags & 1u) == 0) return;
    static_cast<CSGMovable*>(ground->m_pParent)->ForceWorldMatrixUpdate();  // vt+0x50
    const CMatrix34* ltm = reinterpret_cast<const CMatrix34*>(&FrameOf(ground->m_pParent)->ltm);
    Mat4_Invert(ground->m_pInvertedWorldMatrix, ltm);  // 0x0023f878
    const CMatrix34* ltm2 = reinterpret_cast<const CMatrix34*>(&FrameOf(ground->m_pParent)->ltm);
    BBox_TransformByMatrix(reinterpret_cast<CBBox*>(ground->m_AABB), reinterpret_cast<const CBBox*>(ground->m_OBB), ltm2);
}
// A volume moved under the obstacle's node (out of its parent first).
void Reparent(CKHkPushObstacle* o, IKSerializable* volume) {
    CSGLeaf* leaf = static_cast<CSGLeaf*>(volume);
    if (leaf->m_pParent != nullptr) leaf->m_pParent->RemoveChild(leaf);  // vt+0x78
    static_cast<CSGBranch*>(o->m_pNode)->AddChild(leaf);                // vt+0x70
}
const float kMoveMinRate = 0.1f;   // TOC1 +0x504c (0x3dcccccd)
const float kMoveEaseIn = 0.4f;    // TOC1 +0x5050 (0x3ecccccd)
const float kMoveEaseOut = 0.2f;   // TOC1 +0x5058 (0x3e4ccccd)
}  // namespace

// 0x0043d848 CKHkPushObstacle_State0_PlayAnimWithImpact_maybe: the start animation (word 1) of a locked obstacle; the
// impact once its time reaches +0xb8 (or it ends): sound 0, the pad vibration, starter 0. State 1 when it ends.
uint8_t CKHkPushObstacle::State0(IKTime* clock, int32_t phase, uint8_t) {
    if (phase == 1) {
        NodeOf(this)->PlayAnim(static_cast<double>(kZero), AnimWord(m_pAnimDictionary, 1), 0);  // 0x000c98b8
        if (m_unk70 != nullptr) {
            Hide(m_unk70);
            Mesh(m_apGrounds[1])->SetActive(0);
        }
        Show(m_pNode);
        Mesh(m_apGrounds[0])->SetActive(0);
        Collision()->RemoveVolume(static_cast<IKBoundingVolume*>(m_unk80));  // 0x00192bc0
        m_ui16Flags1e4 = static_cast<uint16_t>(m_ui16Flags1e4 & 0xfeffu);
        return 0;
    }
    if (phase == 2) {
        m_ui8StartMove = 1;
        return 0;
    }
    if (phase != 0) return 0;
    const float dt = clock->m_afDeltaTime[0];
    if (((m_ui16Flags1e4 >> 8) & 1u) == 0 &&
        (m_fImpactTime0 <= NodeOf(this)->GetCurrentAnimTime() || NodeOf(this)->IsAnimEndReached(static_cast<double>(dt)))) {
        m_ui16Flags1e4 = static_cast<uint16_t>(m_ui16Flags1e4 | 0x100u);
        Sounds(this)->GetSound(0)->Play(kZero);  // 0x00111230
        CKVibrationData* vibration = static_cast<CKVibrationData*>(m_pVibration);
        vibration->m_pOwner = this;
        vibration->m_bUseTime = 1;
        if (vibration->m_fTime < kZero) vibration->m_fTime = kZero;  // blt
        g_pEngine->m_input->PlayVibration(vibration);  // 0x00107d38
        QueueTriggerSignals(&m_aStarters[0]);  // +0x100
    }
    const bool end = NodeOf(this)->IsAnimEndReached(static_cast<double>(dt));  // 0x000ca368
    NodeOf(this)->AddAnimTime(static_cast<double>(dt));                       // 0x000c9638
    return end ? 1 : 0;
}

// 0x0043e3c0 CKHkPushObstacle_State1_Idle_maybe: at rest; the heroes come and grab; the next state from the push
// decisions (with ground ahead the final state, else a push, a wait or 1).
uint8_t CKHkPushObstacle::State1(IKTime* clock, int32_t phase, uint8_t) {
    if (phase == 1) {
        PlayIdleAnims();
        if (m_unk70 != nullptr) {
            Mesh(m_apGrounds[1])->SetActive(0);
            Hide(m_unk70);
        }
        Mesh(m_apGrounds[0])->SetActive(1);
        Show(m_pNode);
        Collision()->RemoveVolume(static_cast<IKBoundingVolume*>(m_unk80));
        CVector3 p;
        ComputeRestPosition(&p);
        SetFramePosition(NodeOf(this)->m_pRwFrame, p);
        FollowNode(this, m_pNode);
        return 1;
    }
    if (phase == 2) {
        m_ui16Flags1e4 = static_cast<uint16_t>(m_ui16Flags1e4 & 0xfffdu);
        return 1;
    }
    if (phase != 0) return 1;
    if (((m_ui16Flags1e4 >> 7) & 1u) == 0) {
        UpdateHeroInteraction();
    } else {
        m_fIdleTimer = m_fIdleTimer - clock->m_afDeltaTime[0];
        if (m_fIdleTimer <= kZero) m_ui16Flags1e4 = static_cast<uint16_t>(m_ui16Flags1e4 & 0xff7fu);
    }
    UpdateHeroPush(clock);
    Mesh(m_apGrounds[0])->SetActive(0);
    int8_t next = SelectNextState();
    if (next == -1) {
        next = ChoosePushState();
        if (next == -1) next = 1;
    }
    Mesh(m_apGrounds[0])->SetActive(1);
    AdvanceAnimTime(clock->m_afDeltaTime[0], clock->m_afDeltaTime[0]);
    FollowNode(this, m_pNode);
    return static_cast<uint8_t>(next);
}

// 0x0043e760 CKHkPushObstacle_State2_Moving_maybe: one cell per push animation, eased in over the first 0.4 and out over
// the last 0.2 of the cell (unless the push goes on), at least a tenth of the frame; at the cell's end the next
// decision (another push carries the rest of the distance on, +0x1e4 bit 12; none rests the obstacle: state 1).
uint8_t CKHkPushObstacle::State2(IKTime* clock, int32_t phase, uint8_t) {
    if (phase == 1) {
        BeginMove();
        CKHkS08Hero* player = static_cast<CKHkS08Hero*>(HeroGroup()->m_apControlledHeroes[0]);  // 0x002ca0e0
        if (player->GetAttachedObject() == this && (m_ui16Flags1e4 & 0x400u) != 0) {
            Sekens(this)->PlaySekens(static_cast<uint32_t>((player->GetDragonIndex() & 0xffu) + 6));  // 0x001f7730
        }
        return 2;
    }
    if (phase == 2) {
        StopMoveFeedbackAndCollision();
        if (m_pPushers == nullptr) m_i8Side = -1;
        m_ui16Flags1e4 = static_cast<uint16_t>(m_ui16Flags1e4 & 0xeffdu);
        Sounds(this)->GetSound(1)->Stop(0);  // 0x001111b0
        return 2;
    }
    if (phase != 0) return 2;
    float step = clock->m_afDeltaTime[0];
    if (m_pPushers != nullptr) UpdateHeroInteraction();
    Mesh(m_apGrounds[0])->SetActive(0);
    const float minStep = step * kMoveMinRate;
    bool eased = false;
    if (((m_ui16Flags1e4 >> 12) & 1u) == 0 && !(m_fMoveDist >= kMoveEaseIn)) {  // bge
        step = (step * m_fMoveDist) / kMoveEaseIn;
        eased = true;
    }
    if (!eased && !(m_fMoveDist <= g_pfGridScale.m_cellSize - kMoveEaseOut)) {  // ble
        const uint8_t choice = static_cast<uint8_t>(ChoosePushState());
        if (choice != 2 && choice != 4) step = (step * (g_pfGridScale.m_cellSize - m_fMoveDist)) / kMoveEaseOut;
    }
    if (!(step >= minStep)) step = minStep;  // bge
    uint8_t result = 2;
    AdvanceAnimTime(step, clock->m_afDeltaTime[0]);
    UpdateMoveStep(step);
    if (m_fMoveDist >= g_pfGridScale.m_cellSize) {
        m_ui16Flags1e4 = static_cast<uint16_t>(m_ui16Flags1e4 & 0xffdfu);
        m_i8StartCellA = m_i8CellA;
        m_i8StartCellB = m_i8CellB;
        StopMoveFeedbackAndCollision();
        if (m_pPushers != nullptr) UpdateHeroPush(clock);
        result = static_cast<uint8_t>(SelectNextState());
        if (result == 0xff) result = static_cast<uint8_t>(ChoosePushState());
        if (result == 2) {
            const float rest = m_fMoveDist - g_pfGridScale.m_cellSize;
            BeginMove();
            m_fMoveDist = rest;
            m_ui16Flags1e4 = static_cast<uint16_t>(m_ui16Flags1e4 | 0x1000u);
        } else if (result == 0xff) {
            CVector3 p;
            ComputeRestPosition(&p);
            SetFramePosition(NodeOf(this)->m_pRwFrame, p);
            Mesh(m_apGrounds[0])->SetActive(1);
            FollowNode(this, m_pNode);
            m_ui16Flags1e4 = static_cast<uint16_t>(m_ui16Flags1e4 & 0xefffu);
            return 1;
        }
    }
    if (m_pPushers != nullptr) SnapPushersToGrabPoints();
    Mesh(m_apGrounds[0])->SetActive(1);
    RefreshDynamicGround(m_apGrounds[0]);
    if (m_apGrounds[2] != nullptr) RefreshDynamicGround(m_apGrounds[2]);
    FollowNode(this, m_pNode);
    if (m_pPushers != nullptr) {
        const uint8_t ends = m_pPushers->m_pHero->WillAnimEndWithin(step);  // 0x00364020
        m_ui16Flags1e4 = static_cast<uint16_t>((m_ui16Flags1e4 & 0xffdfu) | ((static_cast<uint32_t>(ends) << 5) & 0x1fe0u));
    }
    return result;
}

// 0x0043dfd0 CKHkPushObstacle_State3_WaitForPush_maybe: the heroes at their grab points pushing (+0x1e4 bit 1); with
// every grab point ready starter 10, the push effects and sound (and sekens 9 + the player's dragon with bit 11). It
// goes back to state 1 once a pushing hero's animation passes +0xf8 (or its duration).
uint8_t CKHkPushObstacle::State3(IKTime* clock, int32_t phase, uint8_t) {
    if (phase == 1) {
        PlayPushAnimsForReadyPushers();
        m_ui16Flags1e4 = static_cast<uint16_t>(m_ui16Flags1e4 | 2u);
        if (AreAllPushersReady() != 0) {
            QueueTriggerSignals(&m_aStarters[10]);  // +0x150
            StartPushFxAndSound();
            CKHkS08Hero* player = static_cast<CKHkS08Hero*>(HeroGroup()->m_apControlledHeroes[0]);  // 0x002ca0e0
            if (player->GetAttachedObject() == this && (m_ui16Flags1e4 & 0x800u) != 0) {
                Sekens(this)->PlaySekens(static_cast<uint32_t>((player->GetDragonIndex() & 0xffu) + 9));
            }
        }
        Collision()->RemoveVolume(static_cast<IKBoundingVolume*>(m_unk80));
        return 3;
    }
    if (phase == 2) {
        ResetPushState();
        m_ui16Flags1e4 = static_cast<uint16_t>(m_ui16Flags1e4 & 0xfffdu);
        return 3;
    }
    if (phase != 0) return 3;
    if (((m_ui16Flags1e4 >> 3) & 1u) != 0 || m_pPushers == nullptr) return 1;
    uint8_t result = 3;
    for (Pusher* p = m_pPushers; p != nullptr; p = p->m_pNext) {
        if (static_cast<uint8_t>(p->m_pHero->IsObjectControllingAnim()) == 0) continue;  // 0x00362000
        float limit = m_fPushAnimTime;
        const float duration = CAnimationManager_GetAnimation(p->m_pHero->GetCurrentAnim())->duration;  // 0x00361ee0
        if (duration < limit) {
            limit = CAnimationManager_GetAnimation(p->m_pHero->GetCurrentAnim())->duration;
        } else {
            limit = m_fPushAnimTime;
        }
        if (p->m_bPushing == 0) continue;
        if (!(limit <= p->m_pHero->GetCurrentAnimTime())) continue;  // 0x003638a0
        result = 1;
        break;
    }
    UpdatePusherHandFxPoints();
    AdvanceAnimTime(clock->m_afDeltaTime[0], clock->m_afDeltaTime[0]);
    UpdateHeroInteraction();
    UpdateHeroPush(clock);
    FollowNode(this, m_pNode);
    return result;
}

// 0x0043db10 CKHkPushObstacle_State4_FinalAnimAndLock_maybe: the final animation (starter 5, the footprint freed, the
// volume +0x80 or the second ground, the impact sound with +0x158 bit 3); the impact as it passes +0xc0; at its end the
// obstacle rests for good (starter 6, the heroes let go, +0x70 shown and blocking when set), no state.
uint8_t CKHkPushObstacle::State4(IKTime* clock, int32_t phase, uint8_t) {
    if (phase == 1) {
        PlayFinalAnims();
        QueueTriggerSignals(&m_aStarters[5]);  // +0x128
        SetNavBoxBlocked(0);
        if (((m_ui8Flags >> 1) & 1u) != 0) {
            Collision()->AddVolume(static_cast<IKBoundingVolume*>(m_unk80));  // 0x00192b80
        } else {
            Mesh(m_apGrounds[1])->SetActive(1);
        }
        if (((m_ui8Flags >> 3) & 1u) != 0) {
            Sounds(this)->GetSound(2)->SetAttachObject(m_pNode);  // 0x00111350
            Sounds(this)->GetSound(2)->Play(kZero);
        }
        return 4;
    }
    if (phase == 2) {
        Collision()->RemoveVolume(static_cast<IKBoundingVolume*>(m_unk80));
        return 4;
    }
    if (phase != 0) return 4;
    const float dt = clock->m_afDeltaTime[0];
    for (Pusher* p = m_pPushers; p != nullptr; p = p->m_pNext) {
        if (static_cast<uint8_t>(p->m_pHero->IsObjectControllingAnim()) == 0) continue;
        if (p->m_pHero->WillAnimEndWithin(dt) != 0) {  // 0x00364020
            DetachPushingHeroes(0);
            break;
        }
        p->m_pHero->AdvanceObjectAnimTime(dt);  // 0x00363410
    }
    const float t = NodeOf(this)->GetCurrentAnimTime();  // 0x000c95a8
    if (t < m_fImpactTime4 && dt + t >= m_fImpactTime4) PlayImpactFx();
    uint8_t result;
    if (!NodeOf(this)->IsAnimEndReached(static_cast<double>(dt))) {
        result = 4;
        NodeOf(this)->AddAnimTime(static_cast<double>(dt));
    } else {
        CVector3 p;
        ComputeRestPosition(&p);
        SetFramePosition(NodeOf(this)->m_pRwFrame, p);
        Mesh(m_apGrounds[2])->SetActive(0);
        Mesh(m_apGrounds[0])->SetActive(0);
        Mesh(m_apGrounds[1])->SetActive(0);
        StopMoveFeedbackFx();
        Hide(m_pNode);
        if (m_unk70 != nullptr) {
            Mesh(m_apGrounds[1])->SetActive(1);
            Show(m_unk70);
            SnapToGroundAndBlockNav();
        }
        QueueTriggerSignals(&m_aStarters[6]);  // +0x130
        result = 0xff;
        DetachPushingHeroes(0);
        UnblockGrabPointCells();
        CAnimatedNode* node = NodeOf(this);
        node->SetCurrentAnimTime(node->GetCurrentAnimDuration());  // 0x000c9768, 0x000c9690
        m_ui8StartMove = 0xff;
    }
    FollowNode(this, m_pKGLObject);
    return result;
}

// 0x004387b0 CKHkPushObstacle_Update (unless +0x1e4 bit 13): without a state the optional node +0x70 plays its
// animation (+0x54 word 0); the pushers' cells freed, a player's push remembered for a second (+0x158 bit 0, bit 4),
// the state machine, the footprint blocked again after a cell step (bit 0), and the pushers' cells taken from their
// grab points (blocked while there is a state).
void CKHkPushObstacle::Update(IKTime* clock) {
    CKHkActorBase::Update(clock);  // 0x003f6e68 (empty)
    if (((m_ui16Flags1e4 >> 13) & 1u) != 0) return;
    const float now = clock->m_afCurrentTime[0];
    CKSrvPathFinding* pf = PathFinding();
    if (m_ui8State == 0xff && m_unk54 != nullptr) {
        // BUG(original): without a CAnimatedNode at +0x70 the node calls get null (never with level data; skipped).
        const auto animated = [this]() -> CAnimatedNode* {
            return (m_unk70 != nullptr && m_unk70->IsKindOfClass(0x54b) != 0) ? static_cast<CAnimatedNode*>(m_unk70) : nullptr;
        };
        CAnimatedNode* node = animated();
        if (node != nullptr) {
            if (AnimWord(m_unk54, 0) != node->GetActiveAnim()) {  // 0x000c9720
                CAnimatedNode* target = animated();
                if (target != nullptr) target->PlayAnim(static_cast<double>(kZero), AnimWord(m_unk54, 0), 0);
            }
            CAnimatedNode* target = animated();
            if (target != nullptr) target->AddAnimTime(static_cast<double>(clock->m_afDeltaTime[0]));
        }
    }
    SetPusherCellsBlocked(0);
    m_pReleasedHero = nullptr;
    if ((m_ui8Flags & 1u) != 0 && m_ui8Unk184 == 0 && (m_ui16Flags1e4 & 0x10u) == 0) {
        for (Pusher* p = m_pPushers; p != nullptr; p = p->m_pNext) {
            if (static_cast<uint8_t>(p->m_pHero->IsPlayerControlled()) == 0) continue;
            m_ui16Flags1e4 = static_cast<uint16_t>(m_ui16Flags1e4 | 0x10u);
            m_fPlayerPushTime = now;
        }
    }
    if ((m_ui16Flags1e4 & 0x10u) != 0 && !(now - m_fPlayerPushTime <= kOne)) {  // ble
        m_ui16Flags1e4 = static_cast<uint16_t>(m_ui16Flags1e4 & 0xffefu);
    }
    const uint8_t state = m_ui8State;
    if (state != 0xff) {
        const uint8_t next = (this->*m_pStateTable[state])(clock, 0, state);
        const uint8_t current = m_ui8State;
        if (next != current) {
            if (current != 0xff) (this->*m_pStateTable[current])(clock, 2, next);
            m_ui8State = next;
            if (next != 0xff) (this->*m_pStateTable[next])(clock, 1, current);
        }
    }
    if ((m_ui16Flags1e4 & 1u) != 0) {
        CVector3 rest;
        ComputeRestPosition(&rest);
        m_vRestPos = rest;
        // +0x164 / +0x170 are a CPFPoint (the position, then its node).
        if (static_cast<uint8_t>(pf->FindSectorForPoint(RestPoint())) == 0) m_i16NavNode = -1;  // 0x001e5ca0
        SetNavBoxBlocked(1);
        m_ui16Flags1e4 = static_cast<uint16_t>(m_ui16Flags1e4 & 0xfffeu);
    }
    if (m_pPushers == nullptr) return;
    for (Pusher* p = m_pPushers; p != nullptr; p = p->m_pNext) {
        CVector3 pos;
        GrabPoint(this, m_i8Side, p->m_i8GrabPoint)->GetWorldPosition(&pos);  // 0x000ce790
        p->m_point.m_position = pos;
        if ((m_ui16Flags1e4 & 4u) == 0 || p->m_bReady == 0 || static_cast<uint8_t>(pf->FindSectorForPoint(&p->m_point)) == 0) {
            p->m_point.m_i16GraphNodeIndex = 0xffff;
        }
    }
    SetPusherCellsBlocked(m_ui8State != 0xff ? 1 : 0);
}

// 0x0043bf88 CKHkPushObstacle_MessageProc: the actor messages (0x3f7148), then: 0x93f a hero grabs (the side of its
// nearest grab point; another side than the one pushed waits for the switch, +0x187 / bit 3), 0x940 every pusher let
// go, 0x300 a hero hit on the move trajectory (state 2) or in the grab area (state 4) dies (the game manager's death
// sequence), 0x996 a fresh obstacle starts (state 0), 0x997..0x99a the side bits 0..3 (answer 1), 0x99b / 0x99c the
// presets 0 / 1 applied at once, 0x99d / 0x99e +0x1e4 bit 6 (only while pushed in state 2), 0x99f / 0x9a0 the node
// hidden / shown with bit 13, 0x2666 the text of +0x160. The answers merged.
int32_t CKHkPushObstacle::MessageProc(uint16_t message, void* data) {
    const int32_t base = CKHkActorBase::MessageProc(message, data);  // 0x003f7148
    int32_t own = 1;
    const auto preset = [this](int32_t which) {
        ApplyStatePreset(which);  // vt+0xc8
        DetachPushingHeroes(0);
        CVector3 p;
        ComputeRestPosition(&p);
        SetFramePosition(NodeOf(this)->m_pRwFrame, p);
        ApplyStartMove(1);
    };
    switch (message) {
    case 0x99a:
        own = 1;
        m_ui8SideBits = static_cast<uint8_t>((m_ui8SideBits & 0xf7u) | (static_cast<uint32_t>(*static_cast<const uint8_t*>(data)) << 3));
        break;
    case 0x999:
        own = 1;
        m_ui8SideBits = static_cast<uint8_t>((m_ui8SideBits & 0xfdu) | (static_cast<uint32_t>(*static_cast<const uint8_t*>(data)) << 1));
        break;
    case 0x998:
        own = 1;
        m_ui8SideBits = static_cast<uint8_t>((m_ui8SideBits & 0xfbu) | (static_cast<uint32_t>(*static_cast<const uint8_t*>(data)) << 2));
        break;
    case 0x997:
        own = 1;
        m_ui8SideBits = static_cast<uint8_t>((m_ui8SideBits & 0xfeu) | *static_cast<const uint8_t*>(data));
        break;
    case 0x99e:
        own = 0;
        m_ui16Flags1e4 = static_cast<uint16_t>(m_ui16Flags1e4 & 0xffbfu);
        break;
    case 0x9a0:
        own = 0;
        Show(m_pNode);
        Mesh(m_apGrounds[0])->SetActive(1);
        m_ui16Flags1e4 = static_cast<uint16_t>(m_ui16Flags1e4 & 0xdfffu);
        break;
    case 0x99f:
        own = 0;
        Hide(m_pNode);
        Mesh(m_apGrounds[0])->SetActive(0);
        m_ui16Flags1e4 = static_cast<uint16_t>(m_ui16Flags1e4 | 0x2000u);
        break;
    case 0x2666: {
        // The text of the CKLocTextAccessor +0x160: its first text with a text block (+0x04), else its +0x10.
        CKLocTextAccessor* accessor = static_cast<CKLocTextAccessor*>(m_unk160);
        own = 0;
        *static_cast<IKSerializable**>(data) =
            accessor->m_texts.m_pBlock != nullptr ? accessor->m_texts.m_pBlock[0] : accessor->m_pText;
        break;
    }
    case 0x99b:
    case 0x99c:
        own = 0;
        preset(message == 0x99c ? 1 : 0);
        break;
    case 0x99d:
        own = 0;
        if (m_pPushers != nullptr && m_ui8State == 2) m_ui16Flags1e4 = static_cast<uint16_t>(m_ui16Flags1e4 | 0x40u);
        break;
    case 0x996:
        own = 0;
        if (m_ui8State == 0xff) {
            m_ui8State = 0;
            (this->*m_pStateTable[0])(nullptr, 1, 0xff);
        }
        break;
    case 0x940:
        own = 0;
        DetachPushingHeroes(1);
        break;
    case 0x300: {
        own = 0;
        ICollision* collision = static_cast<ICollision*>(data);
        IKSerializable* volume = static_cast<IKBoundingVolume*>(collision->GetBoundingVolume1())->m_pOwner == this
                                     ? collision->GetBoundingVolume2()   // vt+0x04
                                     : collision->GetBoundingVolume1();  // vt+0x00
        CKHkS08Hero* hero = static_cast<CKHkS08Hero*>(static_cast<IKBoundingVolume*>(volume)->m_pOwner);
        if (hero->GetAttachedObject() == this) break;
        bool kill = false;
        if (m_ui8State == 2) {
            kill = IsHeroOnMoveTrajectory(hero) != 0;
        } else if (m_ui8State == 4) {
            kill = IsHeroInGrabArea(hero) != 0;
        }
        if (kill) static_cast<CKS08GameManager*>(g_pEngine->m_gameManager)->StartDeathSequence(0, 0);  // vt+0x25c
        break;
    }
    case 0x93f: {
        CKHkS08Hero* hero = static_cast<CKHkS08Hero*>(data);
        m_pCandidateHero = hero;
        if (m_pReleasedHero == hero) break;
        const RwV3d& hp = FrameOf(hero->m_pKGLObject)->ltm.pos;  // frame +0x80
        const float pos[3] = {hp.x, hp.y, hp.z};
        int8_t side = -1;
        int8_t index = -1;
        NearestGrabPoint(this, pos, &side, &index);
        if (m_i8Side == -1 || side == m_i8Side) {
            m_i8Side = side;
            CheckGrabPointsForHero();
            AttachHeroesToGrabPoints();
            if (m_pPushers == nullptr) m_i8Side = -1;
            m_ui16Flags1e4 = static_cast<uint16_t>(m_ui16Flags1e4 & 0xfff7u);
            ShowInputIcon(0);
            own = 0;
            break;
        }
        if (hero->GetAttachedObject() == this) break;
        m_i8PendingSide = side;
        m_ui16Flags1e4 = static_cast<uint16_t>(m_ui16Flags1e4 | 8u);
        own = 1;
        break;
    }
    default:
        break;
    }
    if (base == 3 || own == 3) return 3;
    if (base == 2 || own == 2) return 2;
    return base == 0 ? 0 : own;
}

// The start move (+0x1a0) applied at once (the inlined block of MessageProc's presets, OnActivate and Restart): 0 the
// rest pose (word 1, +0x70 hidden), 0xff the final pose (word 2 at its end, +0x70 shown, the node hidden; from
// OnActivate / Restart also dropped on the ground and blocking, +0x1e4 bit 0 cleared), 1 state 1. From MessageProc
// the current state is left afterwards (0 / 0xff) or before (1); OnActivate / Restart left it already.
void CKHkPushObstacle::ApplyStartMove(uint8_t fromMessage) {
    const uint8_t move = m_ui8StartMove;
    if (move == 0) {
        NodeOf(this)->PlayAnim(static_cast<double>(kZero), AnimWord(m_pAnimDictionary, 1), 0);  // 0x000c98b8
        if (m_unk70 != nullptr) {
            Hide(m_unk70);
            Mesh(m_apGrounds[1])->SetActive(0);
        }
        Show(m_pNode);
        Mesh(m_apGrounds[0])->SetActive(0);
    } else if (move == 0xff) {
        const uint32_t word = AnimWord(m_pAnimDictionary, 2);
        NodeOf(this)->PlayAnim(static_cast<double>(CAnimationManager_GetAnimation(word)->duration), word, 0);  // +0x10
        if (m_unk70 != nullptr) {
            Show(m_unk70);
            Mesh(m_apGrounds[1])->SetActive(1);
        }
        Hide(m_pNode);
        Mesh(m_apGrounds[0])->SetActive(0);
        if (fromMessage == 0) {
            SnapToGroundAndBlockNav();
            m_ui16Flags1e4 = static_cast<uint16_t>(m_ui16Flags1e4 & 0xfffeu);
        }
    } else if (move == 1) {
        const uint8_t old = m_ui8State;
        if (fromMessage != 0 && old != 0xff) (this->*m_pStateTable[old])(nullptr, 2, 1);
        m_ui8State = 1;
        (this->*m_pStateTable[1])(nullptr, 1, fromMessage != 0 ? old : static_cast<uint8_t>(0xff));
        return;
    } else {
        return;
    }
    if (fromMessage != 0) {
        if (m_ui8State != 0xff) (this->*m_pStateTable[m_ui8State])(nullptr, 2, 0xff);
        m_ui8State = 0xff;
    }
}

// The run-time reset shared by OnActivate and Restart: no side, no player, +0x1e4 = bit 0 (the rest position to block),
// the ground probe of the obstacle (masks 1 / 0, delta +0xf0, height +0xe8; no contact).
void CKHkPushObstacle::ResetRuntime() {
    m_i8PendingSide = -1;
    m_i8Side = -1;
    m_ui8Unk184 = 0;
    m_ui16Flags1e4 = 0;
    m_ui16Flags1e4 = static_cast<uint16_t>((m_ui16Flags1e4 & 0xfffeu) | 1u);
    m_ui16Flags1e4 = static_cast<uint16_t>(m_ui16Flags1e4 & 0xcfffu);
    m_fPlayerPushTime = 0.0f;
    m_GrdContDatasIn.m_MasksOfGrdForTest[0] = 1;
    m_GrdContDatasIn.m_MasksOfGrdForTest[1] = 0;
    m_GrdContDatasIn.m_fDeltaMax = m_fGroundDeltaMax;
    m_GrdContDatasIn.m_fObjectHeight = m_fHeight;
    m_GrdContDatasInOut.m_ui8SectorNumber = 0;
    m_GrdContDatasInOut.m_i32FaceIndex = -1;
    m_GrdContDatasInOut.m_eContactStatus = 3;
    m_GrdContDatasInOut.m_pGround = nullptr;
}

// vt+0xa0 0x0043cbc8 CKHkPushObstacle_OnActivate: the actor base's, the run-time reset, the nodes +0x78 / +0x7c on the
// node's modelling matrix, the third ground off, +0x188 the node's LTM position and the node at the rest position, the
// effects and the state reset, the start move, the volume +0x80 under the node (its extents +0x84, its radius, at half
// the height) and the grab volume +0xac under the node, out of the collision.
void CKHkPushObstacle::VfA0() {
    CKHkActorBase::VfA0();  // 0x003f7338
    ResetRuntime();
    const RwMatrix* modelling = &NodeOf(this)->m_pRwFrame->modelling;  // frame +0x10
    static_cast<CSGMovable*>(m_unk78)->SetLocalMatrix(modelling);       // 0x000d0be8
    static_cast<CSGMovable*>(m_unk7c)->SetLocalMatrix(&NodeOf(this)->m_pRwFrame->modelling);
    Mesh(m_apGrounds[2])->SetActive(0);
    const RwV3d& ltmPos = NodeOf(this)->m_pRwFrame->ltm.pos;  // frame +0x80
    m_unk188.x = ltmPos.x;
    m_unk188.z = ltmPos.z;
    m_unk188.y = ltmPos.y;
    CVector3 p;
    ComputeRestPosition(&p);
    SetFramePosition(NodeOf(this)->m_pRwFrame, p);
    if (m_pMoveFx != nullptr) StopEmitting(Fx(m_pMoveFx));
    ResetPushState();
    if (m_ui8State != 0xff) (this->*m_pStateTable[m_ui8State])(nullptr, 2, 0xff);
    m_ui8State = 0xff;
    ApplyStartMove(0);
    Reparent(this, m_unk80);
    IKBoundingBox* box = static_cast<IKBoundingBox*>(m_unk80);
    box->m_Extent.z = m_unk84.z;
    box->m_Extent.x = m_unk84.x;
    box->m_Extent.y = m_unk84.y;
    box->m_fRadius = SqrtF(LengthSq(m_unk84.x, m_unk84.y, m_unk84.z));  // 0x00010690
    RwFrame* frame = FrameOf(m_unk80);
    frame->modelling.pos.y = m_fHeight * kHalf;
    frame->modelling.flags &= 0xfffdffffu;
    RwFrame_MarkDirty(FrameOf(m_unk80));
    Reparent(this, m_unkac);
    Collision()->RemoveVolume(static_cast<IKBoundingVolume*>(m_unkac));  // 0x00192bc0
}

// vt+0x54 0x0043d1a8 CKHkPushObstacle_Restart: the run-time reset; unless the life is off (+0x0c bit 2) the footprint
// freed, the node at the rest position, the effects off, the pushers let go, no state, the start move, both volumes
// under the node and the grab volume out of the collision.
void CKHkPushObstacle::Restart() {
    ResetRuntime();
    if ((m_bitArray & 4u) != 0) return;
    SetNavBoxBlocked(0);
    CVector3 p;
    ComputeRestPosition(&p);
    SetFramePosition(NodeOf(this)->m_pRwFrame, p);
    if (m_pMoveFx != nullptr) StopEmitting(Fx(m_pMoveFx));
    ResetPushState();
    DetachPushingHeroes(0);
    if (m_ui8State != 0xff) (this->*m_pStateTable[m_ui8State])(nullptr, 2, 0xff);
    m_ui8State = 0xff;
    ApplyStartMove(0);
    Reparent(this, m_unk80);
    Reparent(this, m_unkac);
    Collision()->RemoveVolume(static_cast<IKBoundingVolume*>(m_unkac));
}

// 0x00439060 CKHkPushObstacle_Load: level data only. The per-dragon arrays are Mem_CallocAligned16(count, pointer size)
// (4 on the PS3) read through the resolver (vt+0x28) at once.
int32_t CKHkPushObstacle::Load(IKFile* file, int32_t type) {
    CKHkActorBase::Load(file, type);  // 0x003f6e98
    if (type != K_LEVEL_PLATEFORMS) return 1;
    static const int kStarterOrder[11] = {0, 1, 2, 3, 4, 6, 5, 7, 8, 9, 10};
    for (int i = 0; i < 11; ++i) m_aStarters[kStarterOrder[i]].Load(file, 0);  // 0x002361c0
    IKFile_ReadRef(file, &m_apGrounds[1]);
    IKFile_ReadRef(file, &m_apGrounds[0]);
    IKFile_ReadRef(file, &m_apGrounds[2]);
    IKFile_ReadRef(file, &m_unk80);
    IKFile_ReadRef(file, &m_unkac);
    ReadF32LE(file, &m_fVolumeHeight);
    ReadRaw(file, &m_ui8NbDragons, 1);
    const auto readArray = [&](IKSerializable*** out) {
        *out = static_cast<IKSerializable**>(Mem_CallocAligned16(sizeof(IKSerializable*), m_ui8NbDragons));  // 0x000531f8
        IKFile_ReadObjectRefArray(file, *out, m_ui8NbDragons);
    };
    readArray(&m_apHeroAnimDictionaries);
    IKFile_ReadRef(file, &m_pAnimDictionary);
    IKFile_ReadRef(file, &m_unk54);
    IKFile_ReadRef(file, &m_pSoundDictionary);
    IKFile_ReadRef(file, &m_pNode);
    IKFile_ReadRef(file, &m_unk70);
    IKFile_ReadRef(file, &m_unk74);
    IKFile_ReadRef(file, &m_unk78);
    IKFile_ReadRef(file, &m_unk7c);
    for (int i = 0; i < 4; ++i) readArray(&m_apGrabPoints[i]);
    IKFile_ReadRef(file, &m_pMoveFx);
    IKFile_ReadRef(file, &m_pPushFx);
    IKFile_ReadRef(file, &m_pHandFx);
    IKFile_ReadRef(file, &m_pImpactFxData);
    IKFile_ReadRef(file, &m_pQuake);
    ReadF32LE(file, &m_fFxHeight);
    ReadRaw(file, &m_ui8CellsA, 1);
    ReadRaw(file, &m_ui8CellsB, 1);
    ReadU32LE(file, &m_unke0);
    ReadF32LE(file, &m_fGrabRadius);
    ReadF32LE(file, &m_fHeight);
    ReadF32LE(file, &m_fGroundDeltaMax);
    ReadF32LE(file, &m_fMoveToTimeout);
    ReadU32LEWords(file, reinterpret_cast<uint32_t*>(&m_unk84), 3);  // one 12-byte read, each word swapped
    ReadRaw(file, &m_ui8HalfA, 1);
    ReadRaw(file, &m_ui8HalfB, 1);
    ReadRaw(file, &m_i8CentreA, 1);
    ReadRaw(file, &m_i8CentreB, 1);
    ReadRaw(file, &m_unkde, 1);
    ReadF32LE(file, &m_fPushAnimTime);
    ReadF32LE(file, &m_fImpactRaise);
    ReadF32LE(file, &m_fImpactTime0);
    ReadF32LE(file, &m_fEnemyConeCheck);
    ReadF32LE(file, &m_fImpactTime4);
    ReadRaw(file, &m_aPresetFlags[0], 1);
    ReadRaw(file, &m_aPresetFlags[1], 1);
    ReadRaw(file, &m_aPresetCell[0], 1);
    ReadRaw(file, &m_aPresetCell[1], 1);
    ReadRaw(file, &m_ui8Flags, 1);
    IKFile_ReadRef(file, &m_unka4);
    IKFile_ReadRef(file, &m_pVibration);
    IKFile_ReadRef(file, &m_unk15c);
    IKFile_ReadRef(file, &m_unk160);
    return 1;
}

// 0x0043d7e8 CKHkPushObstacle_InitStateTable_maybe
void CKHkPushObstacle::InitStateTable() {
    m_aStates[0] = &CKHkPushObstacle::State0;  // {0xf1, 0}: vt+0xf0
    m_aStates[1] = &CKHkPushObstacle::State1;  // {0xf5, 0}
    m_aStates[2] = &CKHkPushObstacle::State2;  // {0xf9, 0}
    m_aStates[3] = &CKHkPushObstacle::State3;  // {0xfd, 0}
    m_aStates[4] = &CKHkPushObstacle::State4;  // {0x101, 0}
    m_pStateTable = m_aStates;
    m_ui8State = 0xff;
    m_ui8NbStates = kStateCount;
}

