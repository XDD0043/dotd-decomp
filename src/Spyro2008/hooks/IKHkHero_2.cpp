// Reconstructed original translation unit: 0x354538-0x364a68 (GAME_TOC1, main_toc1), 207 functions, 105 live.
// Primary owner: IKHkHero (not a registered class)
// Other owners: CKHkS08Hero (46), Vec3 (1), SetPositions (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [ ] 0x354538  FUN_00354538  [dead]
//   [ ] 0x354678  FUN_00354678  [dead]
//   [ ] 0x354818  IKHkHero_InitStationaryMoveRequestAtPosition_maybe  [dead]
//   [ ] 0x354928  IKHkHero_SetGroundProbeWindowFromSpeed_maybe  [dead]
//   [x] 0x354990  IKHkHero_FindNextEnabledJump
//   [~] 0x354a80  CKHkS08Hero_ApplyHazardHitAndLeaveAttach_maybe
//   [ ] 0x354c30  IKHkHero_RememberDynamicGround_maybe  [dead]
//   [x] 0x354cf0  CKHkS08Hero_SetCameraDirectionLock_maybe
//   [ ] 0x354da0  FUN_00354da0  [dead]
//   [ ] 0x354ef8  IKHkHero_ProbeGroundWorldPoint_maybe  [dead]
//   [ ] 0x355098  IKHkHero_vf174
//   [ ] 0x3550c0  IKHkHero_InitStationaryMoveRequest_maybe  [dead]
//   [ ] 0x355130  IKHkHero_StateThreePhaseTimedMove_Condition_maybe  [dead]
//   [ ] 0x355190  IKHkHero_StateClimbOntoObject_Condition_maybe  [dead]
//   [ ] 0x355240  FUN_00355240  [dead]
//   [ ] 0x3552d8  FUN_003552d8  [dead]
//   [x] 0x355328  CKHkS08Hero_UpdateHazardAndSavedPositionRespawn_maybe
//   [ ] 0x3557e8  IKHkHero_vf180
//   [x] 0x355c00  IKHkHero_ApplyPositionToFrame_maybe
//   [ ] 0x355cc0  IKHkHero_FillLocomotionParams_maybe  [dead]
//   [ ] 0x355f78  IKHkHero_CommitContactPointAndHeading_maybe  [dead]
//   [ ] 0x356108  IKHkHero_ShiftContactPointAndCommit_maybe  [dead]
//   [ ] 0x356260  IKHkHero_ProbeWallAhead_maybe  [dead]
//   [ ] 0x3563e8  FUN_003563e8  [dead]
//   [ ] 0x3566b8  IKHkHero_ProbeWallAhead_2_maybe  [dead]
//   [ ] 0x356868  IKHkHero_DeriveSpeedAndHeadingFromDisplacement_maybe  [dead]
//   [ ] 0x356bb8  IKHkHero_IntegrateLocomotionStep_maybe  [dead]
//   [ ] 0x357140  FUN_00357140  [dead]
//   [ ] 0x3575a8  IKHkHero_StateThreePhaseTimedMove_maybe  [dead]
//   [ ] 0x357878  FUN_00357878  [dead]
//   [ ] 0x357ae0  FUN_00357ae0  [dead]
//   [ ] 0x357c40  IKHkHero_ResolveWallsAndProbeGround_maybe  [dead]
//   [ ] 0x357f00  FUN_00357f00  [dead]
//   [ ] 0x358228  FUN_00358228  [dead]
//   [ ] 0x358528  IKHkHero_ProbeGroundAndCommitContact_maybe  [dead]
//   [ ] 0x3585f0  FUN_003585f0  [dead]
//   [ ] 0x3587e0  FUN_003587e0  [dead]
//   [ ] 0x358da0  FUN_00358da0  [dead]
//   [ ] 0x358f98  FUN_00358f98  [dead]
//   [ ] 0x359388  CKHkS08Hero_UpdateModelOffsetAndBank_maybe
//   [x] 0x359988  IKHkHero_SetPositionAndDirection_maybe
//   [ ] 0x359b30  Vec3_ProjectOnPlaneNormalizeScale_maybe  [dead]
//   [x] 0x359c60  CKHkS08Hero_UpdateSignedSlopePitchClass_maybe
//   [ ] 0x359e90  IKHkHero_StateImpulseSlide_maybe
//   [ ] 0x35a4c8  IKHkHero_StateSteeredVelocityMove_maybe  [dead]
//   [ ] 0x35b058  IKHkHero_PlaceAtHotspotOrPosition_maybe
//   [x] 0x35b278  CKHkS08Hero_ResolveWallMovement_maybe
//   [ ] 0x35b710  FUN_0035b710  [dead]
//   [ ] 0x35e010  IKHkHero_StartJumpWithSpeed_maybe  [dead]
//   [ ] 0x35e288  IKHkHero_ClearAirborneState_maybe  [dead]
//   [x] 0x35e3e8  IKHkHero_StartJumpOrFall_maybe  (CKHkS08Hero::StartJumpOrFall)
//   [x] 0x35ea70  CKHkS08Hero_ResolveGroundContactAndPosition_maybe
//   [x] 0x35f6f8  SetPositions
//   [ ] 0x35fbb0  IKHkHero_StateClimbOntoObject_maybe  [dead]
//   [ ] 0x360110  IKHkHero_StateFollowBezier_maybe
//   [x] 0x360648  CKHkS08Hero_UpdateDynamicGroundAttachment_maybe
//   [x] 0x360c50  CKHkS08Hero_UpdateLocomotionAndResolvePosition_maybe
//   [ ] 0x361960  CKHkS08Hero_GetDragonIndex
//   [ ] 0x361968  CKHkS08Hero_GetPositionPtr
//   [ ] 0x361a10  IKHkHero_GetVec3Ptr558_maybe  [dead]
//   [ ] 0x361a20  IKHkHero_GetVec3Ptr474_maybe  [dead]
//   [ ] 0x361a30  IKHkHero_GetPtr3E0_maybe
//   [ ] 0x361a40  IKHkHero_GetVec3Ptr430_maybe
//   [ ] 0x361a50  CKHkS08Hero_GetForwardDirPtr_maybe
//   [ ] 0x361a60  IKHkHero_GetVec3Ptr3B8_maybe
//   [ ] 0x361a70  IKHkHero_SetFlag360Bit19_maybe  [dead]
//   [ ] 0x361a90  IKHkHero_GetFlag354Bit0_Word_maybe
//   [ ] 0x361aa0  IKHkHero_GetFlag354Bit1_maybe  [dead]
//   [ ] 0x361ab0  IKHkHero_GetFlag35CBit8_maybe
//   [ ] 0x361ac0  CKHkS08Hero_CtlState2_ScriptedMoveTo_Condition_2  [dead]
//   [ ] 0x361b00  IKHkHero_GetByte354Bit0_maybe  [dead]
//   [ ] 0x361b10  IKHkHero_IsInvulnerable_maybe
//   [x] 0x361b20  IKHkHero_SetInvulnerable_maybe
//   [ ] 0x361b40  IKHkHero_GetFlag354Bit21_maybe  [dead]
//   [ ] 0x361b50  IKHkHero_GetFlag358Bit8_maybe
//   [ ] 0x361b60  IKHkHero_GetFloat26C_maybe
//   [x] 0x361b68  CKHkS08Hero_GetGroundInfo_maybe
//   [x] 0x361b70  CKHkS08Hero_GetHotSpot
//   [ ] 0x361c00  CKHkS08Hero_GetFloat510_maybe
//   [ ] 0x361c08  IKHkHero_GetFloat278_maybe  [dead]
//   [ ] 0x361c10  IKHkHero_GetFloat530_maybe
//   [ ] 0x361c18  IKHkHero_GetVerticalSpeed_maybe  [dead]
//   [ ] 0x361c20  IKHkHero_GetMoveEntryIndex_maybe  [dead]
//   [ ] 0x361c28  FUN_00361c28  [dead]
//   [ ] 0x361c78  IKHkHero_GetMoveEntryFloat0C_maybe  [dead]
//   [x] 0x361c98  IKHkHero_GetFloat218_maybe
//   [ ] 0x361ca0  IKHkHero_GetVec3Ptr4A8_maybe
//   [ ] 0x361cb0  IKHkHero_GetFlag354Bit9_maybe  [dead]
//   [ ] 0x361cc0  IKHkHero_SetFlag354Bit9_maybe
//   [ ] 0x361cf8  IKHkHero_SetFloat594_maybe  [dead]
//   [ ] 0x361d00  IKHkHero_SetFloat598_maybe  [dead]
//   [ ] 0x361d08  CKHkS08Hero_CanAttachTo_Thunk
//   [x] 0x361d50  CKHkS08Hero_GetAttachedObject_maybe
//   [ ] 0x361d58  KStub_Nop_361d58  [dead]
//   [ ] 0x361d60  IKHkHero_GetFlag354Bit18_maybe  [dead]
//   [ ] 0x361d70  IKHkHero_GetFlag35CBit16_maybe  [dead]
//   [ ] 0x361d80  IKHkHero_GetFlag354Bit19_maybe  [dead]
//   [ ] 0x361d90  IKHkHero_GetPartnerHero_maybe  [dead]
//   [ ] 0x361d98  IKHkHero_SetFlag364Bit5_maybe
//   [ ] 0x361db0  IKHkHero_SetFlag364Bit7_maybe  [dead]
//   [ ] 0x361dd0  IKHkHero_SetFlag364Bit8_maybe  [dead]
//   [ ] 0x361de8  IKHkHero_GetFlag354Bit30_maybe
//   [ ] 0x361df8  IKHkHero_CallVf140_maybe
//   [ ] 0x361e40  IKHkHero_GetFlag364Bit16_maybe  [dead]
//   [ ] 0x361e50  IKHkHero_GetFlag364Bit17_maybe  [dead]
//   [ ] 0x361e60  IKHkHero_GetPtr120_maybe  [dead]
//   [ ] 0x361e68  IKHkHero_SetFlag368Bit0_maybe  [dead]
//   [ ] 0x361e80  CKHkS08Hero_GetCurrentAnimTime_2  [dead]
//   [ ] 0x361ee0  IKHkHero_GetCurrentAnim_maybe
//   [ ] 0x361f40  CKHkS08Hero_GetCurrentAnimResource
//   [ ] 0x361fa0  IKHkHero_IsAnimBlendCrossfading_maybe
//   [ ] 0x362000  IKHkHero_IsObjectControllingAnim_maybe
//   [ ] 0x362010  IKHkHero_SetObjectControlsAnim_maybe
//   [x] 0x362040  IKHkHero_IsLockedToObject_maybe
//   [ ] 0x362050  IKHkHero_SetAttachedMovementEnabled_maybe
//   [ ] 0x3620c8  IKHkHero_GetFlag364Bit26_maybe  [dead]
//   [ ] 0x3620d8  IKHkHero_SetFlag364Bit26_IfAttached_maybe  [dead]
//   [ ] 0x362108  IKHkHero_GetFlag35CBit3_maybe  [dead]
//   [ ] 0x362118  CKHkS08Hero_TeleportTo_Thunk
//   [ ] 0x362150  IKHkHero_SetCollisionDisabledWhileAttached_maybe
//   [ ] 0x3622a8  IKHkHero_SetLockedToObject_maybe
//   [ ] 0x362360  CKHkS08Hero_AttachToObject_maybe
//   [ ] 0x362450  CKHkS08Hero_GetCurrentAnimDuration
//   [ ] 0x3624b8  CKHkS08Hero_WillAnimEndThisFrame_maybe
//   [ ] 0x3625c8  CKHkS08Hero_SetHidden_maybe
//   [ ] 0x362618  FUN_00362618  [dead]
//   [ ] 0x362670  IKHkHero_SetAttachedMoveSpeed_maybe
//   [x] 0x362688  IKHkHero_SetFloat534_IfAttachedMovementEnabled_maybe
//   [x] 0x3626a0  IKHkHero_SetFloat530_IfAttachedMovementEnabled_maybe
//   [ ] 0x3626b8  IKHkHero_SetFlag358Bit6_IfAttachedMovementEnabled_maybe  [dead]
//   [ ] 0x3626e8  IKHkHero_IsAttachedMovementEnabled_maybe
//   [ ] 0x3626f8  CKHkS08Hero_GetPlayerInputFloat38C
//   [ ] 0x362760  IKHkHero_GetFlag360Bit8_IfAttached_maybe  [dead]
//   [ ] 0x362788  IKHkHero_GetFlag360Bit15_IfAttached_maybe  [dead]
//   [ ] 0x3627b0  IKHkHero_GetFlag360Bit14_IfAttached_maybe  [dead]
//   [ ] 0x3627d8  IKHkHero_GetFlag360Bit16_IfAttached_maybe  [dead]
//   [ ] 0x362800  IKHkHero_GetFlag35CBit28_IfAttached_maybe  [dead]
//   [ ] 0x362828  IKHkHero_GetFlag364Bit12_IfAttached_maybe  [dead]
//   [ ] 0x362850  IKHkHero_GetFlag35CBit21_IfAttached_maybe  [dead]
//   [ ] 0x362878  IKHkHero_GetFlag35CBit0_IfAttached_maybe
//   [ ] 0x3628a0  IKHkHero_GetFlag35CBit1_IfAttached_maybe  [dead]
//   [ ] 0x3628c8  IKHkHero_SetFloat794_IfAttached_maybe  [dead]
//   [ ] 0x3628e0  IKHkHero_ClearFlag358Bit21_IfAttached_maybe
//   [ ] 0x362908  IKHkHero_GetFlag360Bit7_IfAttached_maybe  [dead]
//   [ ] 0x362930  IKHkHero_GetFlag358Bit22_IfAttached_maybe  [dead]
//   [ ] 0x362950  CKHkS08Hero_GetPlayerInputFloat388
//   [ ] 0x3629b8  CKHkS08Hero_GetPlayerMoveInputPtr
//   [ ] 0x362a40  CKHkS08Hero_GetPlayerMoveVectorPtr
//   [ ] 0x362ac8  CKHkS08Hero_GetPlayerIndexIfControlled_maybe
//   [ ] 0x362af0  CKHkS08Hero_IsPlayerControlled
//   [ ] 0x362b10  FUN_00362b10  [dead]
//   [ ] 0x362b70  FUN_00362b70  [dead]
//   [ ] 0x362bb8  CKHkS08Hero_GetPlayerInputFlag360b17
//   [ ] 0x362c28  CKHkS08Hero_GetPlayerInputFlag360b29
//   [ ] 0x362c98  CKHkS08Hero_GetPlayerInputFlag358b21
//   [ ] 0x362d00  CKHkS08Hero_GetPlayerInputFlag358b20
//   [ ] 0x362d68  CKHkS08Hero_GetPlayerInputByte395
//   [ ] 0x362dd0  CKHkS08Hero_GetPlayerInputByte394
//   [ ] 0x362e38  FUN_00362e38  [dead]
//   [ ] 0x362ef0  CKHkS08Hero_GetPlayerInputWord392
//   [ ] 0x362f60  CKHkS08Hero_GetPlayerInputWord390
//   [ ] 0x362fd0  IKHkHero_SetPendingSourceAndVec3_Flag35CBit4_maybe
//   [ ] 0x363060  IKHkHero_GetObjectDrivenBezierProgress_maybe  [dead]
//   [ ] 0x363090  CKHkS08Hero_UpdateObjectDrivenMove_maybe
//   [ ] 0x363110  IKHkHero_GetModelNode_maybe  [dead]
//   [ ] 0x363118  IKHkHero_PlayAnimResource_maybe
//   [ ] 0x363218  IKHkHero_SetObjectDrivenBezierMove_maybe  [dead]
//   [ ] 0x363318  IKHkHero_SetObjectDrivenMoveTarget_maybe  [dead]
//   [ ] 0x363378  IKHkHero_SetObjectAnimTime_maybe
//   [ ] 0x363410  IKHkHero_AdvanceObjectAnimTime_maybe
//   [ ] 0x3634b0  IKHkHero_SetAnimPairAndWeight_maybe
//   [ ] 0x363578  IKHkHero_CrossfadeAnimResource_maybe
//   [ ] 0x363640  IKHkHero_SetDesiredMoveDirectionFlat_maybe  [dead]
//   [ ] 0x3636f8  IKHkHero_SetFlag364Bit18_IfFlag364Bit26_maybe  [dead]
//   [ ] 0x363728  IKHkHero_SetFlag364Bit27_IfFlag364Bit26_maybe  [dead]
//   [ ] 0x363758  IKHkHero_SetPtr120_IfFlag364Bit26_maybe  [dead]
//   [ ] 0x363770  IKHkHero_GetLedgeGroundContact_maybe
//   [ ] 0x363790  FUN_00363790  [dead]
//   [ ] 0x3638a0  IKHkHero_GetCurrentAnimTime_maybe
//   [ ] 0x363900  IKHkHero_UpdateMoveTo_maybe
//   [x] 0x363c40  CKHkS08Hero_GetGroundObject_maybe  (CKHkS08Hero.h)
//   [ ] 0x363c78  IKHkHero_GetTargetingPositionPtr_maybe
//   [ ] 0x363ca0  IKHkHero_GetFlag360Bit12_maybe
//   [ ] 0x363cb0  IKHkHero_UpdateWaypointSteer_maybe  [dead]
//   [ ] 0x363dc8  IKHkHero_SetFlag360Bit14_IfAttached_maybe
//   [ ] 0x363df8  IKHkHero_SetFlag360Bit15_IfAttached_maybe
//   [ ] 0x363e28  IKHkHero_SetFlag358Bit22_IfAttached_maybe  [dead]
//   [ ] 0x363e58  IKHkHero_SetFlag364Bit12_IfAttached_maybe
//   [ ] 0x363e88  IKHkHero_SetFlag35CBit0_IfAttached_maybe
//   [ ] 0x363eb8  IKHkHero_SetFlag35CBit1_IfAttached_maybe  [dead]
//   [ ] 0x363ee8  IKHkHero_SetFlag35CBit3_IfAttached_maybe
//   [ ] 0x363f18  IKHkHero_SetFlag360Bit20_maybe  [dead]
//   [ ] 0x363f38  IKHkHero_SetFlag35CBit28_IfAttached_maybe  [dead]
//   [ ] 0x363f68  IKHkHero_SetFlag360Bit7_IfAttached_maybe  [dead]
//   [ ] 0x363f98  IKHkHero_SetFlag360Bit8_IfAttached_maybe
//   [ ] 0x363fc8  IKHkHero_SetFlag35CBit21_IfAttached_maybe
//   [ ] 0x363ff8  IKHkHero_IsFlag35CBit6_AndFlag3B0Bit6Clear_maybe
//   [ ] 0x364020  CKHkS08Hero_WillAnimEndWithin_maybe
//   [ ] 0x364100  CKHkS08Hero_GetAnimMarkWindow
//   [ ] 0x364268  IKHkHero_PassesTrackerAssignFlagChecks_maybe
//   [ ] 0x3642d8  IKHkHero_SetWaypointSteerTarget_maybe  [dead]
//   [ ] 0x364470  IKHkHero_SetMoveDestination_maybe
//   [ ] 0x364608  CKHkS08Hero_DetachFromObject_maybe
//   [ ] 0x364858  FUN_00364858  [dead]
//   [ ] 0x364960  FUN_00364960  [dead]
//   [x] 0x364a28  CKHkS08Hero_ActState12_FreeMovement_Condition
//   [x] 0x364a30  CKHkS08Hero_ActState12_FreeMovement
//
//   [ ] 0x9be848  IKHkHero_vf8  [inline]
//   [ ] 0x9be890  IKHkHero_vf14  [inline]
//   [ ] 0x9be898  IKHkHero_vf18  [inline]
//   [ ] 0x9be8a0  IKHkHero_vfF8  [inline]
//   [ ] 0x9be8a8  IKHkHero_vfFC  [inline]
//   [ ] 0x9be8b0  IKHkHero_vf104  [inline]
//   [ ] 0x9be8b8  IKHkHero_vf108  [inline]
//   [ ] 0x9be8c0  IKHkHero_vf138  [inline]
//   [ ] 0x9be8c8  IKHkHero_vf14C  [inline]
//   [ ] 0x9be8d0  IKHkHero_vf158  [inline]
//   [ ] 0x9be8d8  IKHkHero_vf15C  [inline]
//   [ ] 0x9be8e0  IKHkHero_vf160  [inline]
//   [ ] 0x9be8e8  IKHkHero_vf164  [inline]
//   [ ] 0x9be8f0  IKHkHero_vf168  [inline]
//   [ ] 0x9be8f8  IKHkHero_CompareEntriesByByte10Desc_maybe  [inline]
//   [ ] 0x9be920  IKHkHero_CompareEntriesByByte10Desc_2_maybe  [inline]
//   [ ] 0x9be948  IKHkHero_CompareEntriesByByte12Desc_maybe  [inline]
//   [ ] 0x9be970  IKHkHero_CompareEntriesByByte10Desc_3_maybe  [inline]
//   [ ] 0x9be998  IKHkHero_vf194  [inline]
//   [ ] 0x9be9a0  IKHkHero_Destructor  [inline]
//   [ ] 0x9bea90  IKHkHero_DeletingDestructor  [inline]
#include <cmath>
#include <cstring>

#include "Spyro2008/hooks/IKHkHero.h"
#include "Spyro2008/hooks/CKHkS08Hero.h"
#include "k2000/system/IKTime.h"
#include "k2000/core/Stub.h"
#include "crt/xatan.h"
#include "Renderware/rwcore/RwCamera.h"
#include "Spyro2008/groups/IKGrpHero.h"
#include "Spyro2008/groups/C22SpyroShims.h"
#include "k2000/misc/Mat4.h"
#include "k2000/math/Vec3.h"
#include "crt/ppc_ops.h"
#include "k2000/math/Math.h"
#include "crt/xsinf.h"
#include "k2000/scenegraph/CSGMovable.h"
#include "k2000/services/CKSrvCollision.h"
#include "Spyro2008/logic/CKS08GameManager.h"
#include "k2000/cameras/CKSrvCamera.h"
#include "k2000/hooks/GroundContact.h"
#include "k2000/logic/CKLevel.h"
#include "k2000/logic/CKSector.h"
#include "k2000/logic/physics/CGround.h"
#include "k2000/logic/physics/CDynamicGround.h"
#include "k2000/render/CRenderer.h"
#include "k2000/scenegraph/CSGLeaf.h"
#include "k2000/misc/Engine.h"
#include "k2000/services/CollisionDatas.h"
#include "k2000/services/ICollisionMesh.h"

namespace {
// The scene node's RenderWare frame (CSGMovable +0x04): the hero's node (+0x1c).
RwFrame* NodeFrame(IKSerializable* node) { return static_cast<CSGMovable*>(node)->m_pRwFrame; }
}  // namespace

// 0x00355c00 IKHkHero_ApplyPositionToFrame_maybe: the node's frame takes the hero's heading (a rotation about
// the y axis from the direction at +0x540) and position (+0x54c).
void IKHkHero::ApplyPositionToFrame() {
    RwFrame* frame = NodeFrame(m_pKGLObject);
    const CVector3 direction = {m_unk540, m_unk544, m_unk548};
    const float yaw = Vec3_GetYawAngleFromX(&direction);  // 0x00244638
    const float angle = 1.5707964f /* TOC 0x2c64, pi / 2 */ - yaw;
    Mat4_SetRotationAboutAxis(angle, reinterpret_cast<CMatrix34*>(&frame->modelling), 1);  // 0x00241688
    c22spyro::RwFrameMarkDirty(frame);
    c22spyro::RwFrameSetPosition(frame, m_unk54c, m_unk550, m_unk554);
    c22spyro::RwFrameMarkDirty(frame);
}

// 0x00359988 IKHkHero_SetPositionAndDirection_maybe: the position (+0x54c, copied to +0x558) and the direction
// (+0x540, flattened to the horizontal plane and normalised) with their yaw (+0x538); a null argument takes the
// node frame's own position / direction.
void IKHkHero::SetPositionAndDirection(const CVector3* position, const CVector3* direction) {
    const RwFrame* frame = NodeFrame(m_pKGLObject);
    const float* source = position != nullptr ? &position->x : &frame->modelling.pos.x;
    const float px = source[0];
    const float py = source[1];
    const float pz = source[2];
    m_unk54c = px;
    m_unk550 = py;
    m_unk554 = pz;
    m_unk558 = m_unk54c;
    m_unk55c = m_unk550;
    m_unk560 = pz;
    source = direction != nullptr ? &direction->x : &frame->modelling.at.x;
    const float dx = source[0];
    const float dz = source[2];
    m_unk540 = dx;
    m_unk544 = source[1];
    m_unk548 = dz;
    m_unk544 = 0.0f;  // TOC 0x2c24: the direction is flattened
    const float horizontalLength = static_cast<float>(
        c22spyro::MathSqrtf(ppc::fmadds(dz, dz, ppc::fmadds(dx, dx, m_unk544 * m_unk544))));
    if (horizontalLength != 0.0f) {
        const float inverse = 1.0f / horizontalLength;  // TOC 0x2c3c is 1.0f; fdivs
        const float z = inverse * m_unk548;
        const float x = inverse * m_unk540;
        const float y = inverse * m_unk544;
        m_unk548 = z;
        m_unk540 = x;
        m_unk544 = y;
    }
    const CVector3 flat = {m_unk540, m_unk544, m_unk548};
    m_unk538 = Vec3_GetYawAngleFromX(&flat);  // 0x00244638
}

// 0x00355328 CKHkS08Hero_UpdateHazardAndSavedPositionRespawn_maybe: only with a ground contact (+0x4b8): the grounds
// with the surface flags of UpdateHeroMovementAndContacts (+0x358 bit 25: the push +0x6d4 = the normal times the ground's
// value +0x40 on the ground, bit 28; bit 26 / +0x360 bit 13 / +0x358 bit 27: the hazard falls back to the saved
// position or hurt), the fall from higher than +0x300 above the ground (+0x478) for the player's hero, then the ground
// surface flags (vt+0x14c). The game manager's hit points (vt+0x270 / +0x274) are 0xff in DotD.
void CKHkS08Hero::UpdateHazardAndSavedPositionRespawn(IKTime* clock) {
    const CGround* ground = static_cast<const CGround*>(m_gcCurDatasInOut.m_pGround);
    if (ground == nullptr) return;
    if ((m_unk358 & 0x2000000u) != 0 && (m_unk354 & 1u) == 0) {
        m_unk6d4 = m_unk564;
        m_unk6dc = m_unk56c;
        m_unk6d8 = m_unk568;
        const float value = ground->m_fPropertieValue;  // +0x40
        m_unk6dc = value * m_unk6dc;
        m_unk6d4 = value * m_unk6d4;
        m_unk6d8 = value * m_unk6d8;
        m_unk358 = (m_unk358 & ~0x10000000u) | 0x10000000u;
    }
    CKS08GameManager* manager = static_cast<CKS08GameManager*>(g_pEngine->m_gameManager);
    const uint8_t points = manager->Vf270(m_ui8Hero);  // vt+0x270
    const bool dead = points == 0;                     // (points - 1) < 0
    if ((m_unk358 & 0x4000000u) != 0 && (m_unk354 & 1u) == 0 && (m_unk360 & 0x4000u) == 0 && !dead) {
        if (TeleportToSavedPosition()) {
            m_unk358 &= ~0x4000000u;
        } else {
            ApplyHazardHitAndLeaveAttach(manager->Vf274(m_ui8Hero), 1);  // vt+0x274
            RequestOwnDragonSelectionIfMultiHero();
        }
    }
    if ((m_unk360 & 0x2000u) != 0 && (m_unk354 & 1u) == 0 && (m_unk360 & 0x8000u) == 0 && !dead) {
        if (TeleportToSavedPosition()) m_unk360 &= ~0x2000u;
    }
    if ((m_unk358 & 0x8000000u) != 0 && (m_unk354 & 1u) == 0 && (m_unk354 & 0x4000000u) == 0 && (m_unk35c & 4u) == 0 &&
        !dead) {
        uint8_t damage = manager->Vf270(m_ui8Hero);
        uint8_t kind = 1;
        bool hurt = false;
        if ((m_unk364 & 0x80u) == 0) {
            const int32_t value = ppc::fctiwz(ground->m_fPropertieValue);
            if (damage > static_cast<uint8_t>(value)) {
                ApplyHazardHitAndLeaveAttach(static_cast<uint8_t>(value), static_cast<uint8_t>(value));
                hurt = true;
            } else {
                kind = static_cast<uint8_t>(value);
                damage = static_cast<uint8_t>(value);
            }
        }
        if (!hurt) {
            if (TeleportToSavedPosition()) {
                m_unk358 &= ~0x8000000u;
            } else {
                ApplyHazardHitAndLeaveAttach(damage, kind);
                RequestOwnDragonSelectionIfMultiHero();
            }
        }
    }
    const uint32_t onGround = (m_unk364 & 0x80u) != 0 ? ((m_unk354 & 1u) << 7) : 0u;
    m_unk364 = (m_unk364 & ~0x80u) | onGround;
    if (m_ui8TrackedLeader == m_ui8Hero && (m_unk354 & 4u) != 0 && m_unk300 != 0.0f && (m_unk360 & 0x2000u) == 0 &&
        (m_unk358 & 0x4000000u) == 0 && (m_unk358 & 4u) == 0 && m_unk478 - m_unk550 > m_unk300) {
        // A fall from too high.
        ApplyHazardHitAndLeaveAttach(manager->Vf274(m_ui8Hero), 1);
        m_unk364 = (m_unk364 & ~0x2000u) | 0x2000u;
    }
    UpdateGroundSurfaceFlags(clock);  // vt+0x14c 0x002dc660
}

// 0x00354a80 CKHkS08Hero_ApplyHazardHitAndLeaveAttach_maybe. STUB(C2.7: health and hazards): the hit of a hazard ground.
void CKHkS08Hero::ApplyHazardHitAndLeaveAttach(uint8_t, uint8_t) {
    DOTD_STUB_ONCE("CKHkS08Hero_ApplyHazardHitAndLeaveAttach_maybe 0x354a80 (C2.7)");
}

// 0x00361b68 CKHkS08Hero_GetGroundInfo_maybe: the ground of the current contact (+0x4b8).
IKSerializable* CKHkS08Hero::GetGroundInfo() { return m_gcCurDatasInOut.m_pGround; }

// 0x00361b70 CKHkS08Hero_GetHotSpot: the hero's hot spot `index` (+0x4c), null when the index is not below the
// group's hot spot count of this hero (vt+0xf8).
IKSerializable* CKHkS08Hero::GetHotSpot(uint8_t index) {
    // CKGrpS08Hero_vfF8 0x002ce320 (the only IKGrpHero in DotD; not declared on IKGrpHero yet): the byte table at
    // 0x00a70448 by hero, 0x21 hot spots for Spyro, 0x1d for Cynder.
    static const uint8_t kHotSpotCounts[2] = {0x21, 0x1d};
    const uint8_t count = kHotSpotCounts[m_ui8Hero];
    if (count <= index) return nullptr;
    return m_apHotSpots[index];
}

// 0x00364a28 CKHkS08Hero_ActState12_FreeMovement_Condition: always (the last row).
uint8_t CKHkS08Hero::ActFreeMovementCondition(IKTime*, uint8_t) { return 1; }

// 0x00364a30 CKHkS08Hero_ActState12_FreeMovement: entering clears +0xd0.
uint8_t CKHkS08Hero::ActFreeMovement(IKTime*, int32_t phase, uint8_t other) {
    if (phase == 0) return other;
    if (phase == 1) m_unkd0 = 0;
    return 0;
}

// 0x00360c50 CKHkS08Hero_UpdateLocomotionAndResolvePosition_maybe: the locomotion machine (rows +0x520, handlers
// +0x528, current row +0x52c) and the frame's movement: the displacement (+0x5b4) gathered from the position
// adjustment (vt+0x174), the root motion (+0x5a8), the pushes (+0x5e4 / +0x5f0 / +0x5fc), checked against the walls and
// the navigation, and the new position resolved on the ground (SetPositions). A hero attached to an object (+0x358
// bit 2) or held (+0x35c bit 11) leaves its locomotion state and follows the object's hot spot instead.
void CKHkS08Hero::UpdateLocomotionAndResolvePosition(IKTime* clock) {
    // Bit 3 takes bit 0 (the ground flag of the frame before); bit 2 is cleared (its old value goes to the moving
    // ground attachment).
    const uint32_t old354 = m_unk354;
    const uint32_t step1 = (old354 & 0xfffffff7u) | ((old354 & 1u) << 3);
    m_unk354 = step1;
    const uint32_t wasOnMovingGround = (step1 >> 2) & 1u;
    m_unk354 = step1 & 0xfffffffbu;
    const uint32_t* handlers = reinterpret_cast<const uint32_t*>(m_unk528);
    if ((m_unk358 & 4u) != 0 || (m_unk35c & 0x800u) != 0) {
        if (m_unk52c != 0xff) SwitchState(handlers, m_unk52c, 0xff, clock);
        // STUB(C2.8: attachments): the position and direction from the attach hot spot's world matrix
        // (CSGHotSpot_GetWorldMatrix 0xce970), the speeds from the move, SetPositions and the path destination.
        DOTD_STUB_ONCE("CKHkS08Hero_UpdateLocomotionAndResolvePosition_maybe: attached hero (C2.8)");
        return;
    }
    UpdateDynamicGroundAttachment(clock, wasOnMovingGround);  // 0x00360648
    // The slope test (+0x1ad): a ground steeper than +0x349 degrees (or the slide flag +0x1ae with +0x358 bit 24)
    // starts the slide timer (+0x608, +0x354 bit 23).
    bool steep = false;
    if ((m_unk358 & 0x1000000u) != 0) steep = m_aui8Unk1a4[0x1ae - 0x1a4] != 0;  // +0x1ae
    if (m_aui8Unk1a4[0x1ad - 0x1a4] != 0 && !steep) {  // +0x1ad
        const float cosine = ppc::fmadds(m_unk56c, kHeroAxisY.z, ppc::fmadds(m_unk564, kHeroAxisY.x, m_unk568 * kHeroAxisY.y));  // TOC +0x2c48
        float angle = 0.0f;                                     // TOC +0x2c24
        if (!(cosine >= 1.0f)) angle = crt::Acosf(cosine) * 0x1.ca5dc2p+5f;  // 0x0098e1a0; TOC +0x2cdc (57.29578)
        steep = angle >= static_cast<float>(static_cast<double>(m_unk349));  // cror gt|eq
    }
    if (!steep) {
        m_unk354 &= 0xff7fffffu;
    } else if ((m_unk354 & 0x800000u) == 0) {
        m_unk608 = clock->m_afCurrentTime[0];
        m_unk354 = (m_unk354 & 0xff7fffffu) | 0x800000u;
    }
    const uint8_t count = static_cast<IKGrpHero*>(m_pGrpHero)->GetNbHeroStatesC();  // vt+0x12c
    uint8_t found = count;
    for (uint32_t row = 0; row < count; ++row) {
        if (CallStateCondition(m_unk520[row].m_aPtmf1, clock, static_cast<uint8_t>(row)) != 0) {
            found = static_cast<uint8_t>(row);
            break;
        }
    }
    if (found != m_unk52c) SwitchState(handlers, m_unk52c, found, clock);
    const CVector3& zero = kHeroZeroVector;  // TOC +0x2c44
    m_unk5b4 = zero.x;
    m_unk5b8 = zero.y;
    m_unk5bc = zero.z;
    Vf174();  // vt+0x174
    m_unk5cc = zero.x;
    m_unk5d0 = zero.y;
    m_unk5d4 = zero.z;
    m_unk5c0 = m_unk5c0 + m_unk5a8;
    m_unk5c4 = m_unk5c4 + m_unk5ac;
    m_unk5c8 = m_unk5c8 + m_unk5b0;
    m_unk5cc = m_unk5cc + m_unk5e4;
    m_unk5d0 = m_unk5d0 + m_unk5e8;
    m_unk5d4 = m_unk5d4 + m_unk5ec;
    m_unk5cc = m_unk5cc + m_unk5f0;
    m_unk5d0 = m_unk5d0 + m_unk5f4;
    m_unk5d4 = m_unk5d4 + m_unk5f8;
    m_unk5cc = m_unk5cc + m_unk5fc;
    m_unk5d0 = m_unk5d0 + m_unk600;
    m_unk5d4 = m_unk5d4 + m_unk604;
    const float speedBefore = m_unk530;
    if ((m_unk35c & 0x1000u) == 0) RunState(handlers, m_unk52c, clock);
    uint32_t started = 0;
    if (speedBefore == 0.0f && m_unk530 != 0.0f) started = 0x2000u;  // TOC +0x2c24
    m_unk358 = (m_unk358 & 0xffffdfffu) | started;
    Vf180();  // vt+0x180 (empty)
    const float dx = m_unk5c0 + m_unk5cc;
    const float dy = m_unk5c4 + m_unk5d0;
    const float dz = m_unk5c8 + m_unk5d4;
    m_unk5b4 = dx;
    m_unk5bc = dz;
    m_unk5b8 = dy;
    CVector3 target{m_unk54c + dx, m_unk550 + dy, m_unk554 + dz};
    m_unk5d8 = m_unk5b4;
    m_unk5dc = m_unk5b8;
    m_unk5e0 = m_unk5bc;
    if ((m_unk35c & 0x80u) != 0) {
        // Moved without collision: the position is the target, the path follows.
        m_unk558 = m_unk54c;
        m_unk560 = m_unk554;
        m_unk55c = m_unk550;
        m_unk554 = target.z;
        m_unk54c = target.x;
        m_unk550 = target.y;
        m_PFCpnt.SetDestination(reinterpret_cast<const CVector3*>(&m_unk54c));  // 0x001e3a40
    } else {
        if (m_aui8Unk1a4[0x1aa - 0x1a4] != 0 && (m_unk360 & 0x8000000u) == 0 && (m_unk35c & 0x10000000u) == 0) {
            const uint32_t noRootMotion = (m_unk5a8 == zero.x && m_unk5ac == zero.y && m_unk5b0 == zero.z) ? 1u : 0u;
            ResolveWallMovement(reinterpret_cast<CVector3*>(&m_unk5b4), &target,
                                reinterpret_cast<const CVector3*>(&m_unk5a8), noRootMotion);  // 0x0035b278
        }
        ConstrainMovementToNavigation(clock, reinterpret_cast<CVector3*>(&m_unk5b4), &target);  // 0x0036b1a0
        float height = m_unk1f0;
        float step = m_unk510;
        if (m_unk5b8 < 0.0f) {
            step = step - m_unk5b8;
            height = m_unk1f0 - m_unk5b8;
        }
        if ((m_unk354 & 1u) == 0 && m_unk530 > m_unk204) {
            height = ppc::fmadds(m_unk1f0, (m_unk530 - m_unk204) / m_unk204, height);
        }
        m_gcDatasIn.m_fDeltaMax = height;      // +0x4a8
        m_gcDatasIn.m_fObjectHeight = step;    // +0x4ac
        SetPositions(clock, &target);          // 0x0035f6f8
    }
    if (m_aui8Unk1a4[0x1b3 - 0x1a4] != 0 && (m_unk358 & 0x40000000u) == 0 && (m_unk358 & 0x80000u) == 0 && (m_unk358 & 0x8000u) == 0) {
        const bool moved = (m_unk354 & 0x40000u) != 0 || (m_unk358 & 0x80u) != 0 || m_unk5f0 != zero.x ||
                           m_unk5f4 != zero.y || m_unk5f8 != zero.z || m_unk5fc != zero.x || m_unk600 != zero.y ||
                           m_unk604 != zero.z;
        if (moved) {
            // The node's world position against the target (the model offset, y kept 0), +0x358 bit 19.
            const RwFrame* frame = static_cast<CSGMovable*>(m_pKGLObject)->m_pRwFrame;
            m_unk468 = frame->ltm.pos.x - target.x;
            m_unk46c = frame->ltm.pos.y - target.y;
            m_unk46c = 0.0f;
            m_unk470 = frame->ltm.pos.z - target.z;
            m_unk358 = (m_unk358 & 0xfff7ffffu) | 0x80000u;
        }
    }
    m_unk588 = SelectMoveEntryIndexForSpeed(m_unk530);  // 0x00369ac8
    UpdateSignedSlopePitchClass();                     // 0x00359c60
}

// 0x00360648 CKHkS08Hero_UpdateDynamicGroundAttachment_maybe: a hero on a moving ground (+0x1ab; the contact's ground a
// CDynamicGround whose sector is active) is carried by it: the ground point in the world, the move to it (+0x5a8; none
// and vt+0x178 when the hero is a ground's reach above it) and the ground's turn (+0x5a4, added to the yaw +0x538, the
// heading +0x540 and the direction +0x3b8 turned with it). An airborne hero (+0x354 bit 0) the ground reaches lands
// on it; a ground moving faster than 150 per second, a hero still in the air or with +0x35c bit 8 is not carried.
// `wasOnMovingGround` restarts the turn.
void CKHkS08Hero::UpdateDynamicGroundAttachment(IKTime* clock, uint32_t wasOnMovingGround) {
    ICollisionMesh* ground = static_cast<ICollisionMesh*>(m_gcCurDatasInOut.m_pGround);
    IKSerializable* carriedBy = nullptr;
    bool carry = false;
    CVector3 point;
    if (m_aui8Unk1a4[0x1ab - 0x1a4] != 0 && m_gcCurDatasInOut.m_eContactStatus <= 2 && ground->GetClassID() == 0x13) {
        const CKSector* sector =
            static_cast<const CKSector*>(g_pEngine->m_level->m_vpSectors.m_pBlock[ground->GetSectorNumber()]);
        if ((sector->m_ba16Properties & 1) != 0) {
            Mat4_TransformPoints(ground->GetWorldMatrix(), &point, &m_gcCurDatasInOut.m_ProjectionOnGround, 1);
            uint32_t flags = m_unk354;
            if ((flags & 1u) != 0 && point.y >= m_unk550 + m_gcDatasIn.m_fDeltaMax && ((ground->m_ba16EngineFlags >> 3) & 1) == 0) {
                // An airborne hero the ground came up to: landed.
                if (m_ui8Hero == m_ui8TrackedLeader && (m_unk35c & 0x400000u) == 0 && (m_unk358 & 4u) == 0) {
                    static_cast<CKSrvCamera*>(g_pEngine->m_srvCamera)->m_baTemporaryFlags &= ~1u;
                }
                m_unk354 &= 0xfffffdfeu;
                m_unk364 &= ~0x400u;
                m_unk354 &= ~2u;
                m_unk590 = 0xff;
                m_unk354 = (m_unk354 & ~6u) | 4u;
                SetDirectionLock(0);  // 0x009bdb48
                flags = m_unk354;
            }
            if ((flags & 1u) != 0 || (m_unk35c & 0x100u) != 0) {
                carriedBy = ground;
            } else {
                const float dx = point.x - m_unk54c;
                const float dy = point.y - m_unk550;
                const float dz = point.z - m_unk554;
                const float distance = std::sqrt(ppc::fmadds(dz, dz, ppc::fmadds(dx, dx, dy * dy)));  // Math_Sqrtf
                carry = !(distance / clock->m_afDeltaTime[0] > 150.0f);  // TOC +0x2d04
            }
        }
    }
    if (!carry) {
        m_unk59c = carriedBy;
        m_unk5a8 = kHeroZeroVector.x;  // TOC +0x2c44
        m_unk5b0 = kHeroZeroVector.z;
        m_unk5ac = kHeroZeroVector.y;
        m_unk5a4 = 0.0f;
        return;
    }
    if (m_unk550 - point.y >= m_gcDatasIn.m_fDeltaMax) {
        Vf178(clock, 0);  // vt+0x178 0x002f8708
        m_unk5a8 = kHeroZeroVector.x;
        m_unk5b0 = kHeroZeroVector.z;
        m_unk5ac = kHeroZeroVector.y;
        m_unk5a4 = 0.0f;
    } else {
        m_unk5a8 = point.x - m_unk54c;
        m_unk5ac = point.y - m_unk550;
        m_unk5b0 = point.z - m_unk554;
    }
    // The ground's yaw: its world matrix's right row (vt+0x50 read as a vector).
    const float yaw = Vec3_GetYawAngleFromX(&ground->GetWorldMatrix()->m_right);  // 0x00244638
    if (m_unk59c != ground || wasOnMovingGround != 0) m_unk5a0 = yaw;
    const float turn = yaw - m_unk5a0;
    const float heading = turn + m_unk538;
    m_unk5a4 = turn;
    m_unk538 = heading;
    int32_t headingBits;
    std::memcpy(&headingBits, &heading, 4);
    float c;
    float s;
    if (headingBits >= 0) {
        c = crt::InlineCosf(heading);
        s = crt::InlineSinf(heading);
    } else {
        c = crt::LibCosf(-heading);
        s = -crt::LibSinf(-heading);
    }
    m_unk540 = c;
    m_unk548 = s;
    m_unk544 = 0.0f;
    Vec3_RotateYawFlatNormalized(m_unk5a4, reinterpret_cast<CVector3*>(&m_unk3b8));  // 0x00584e40
    m_unk59c = ground;
    m_unk5a0 = yaw;
}

// 0x0035b278 CKHkS08Hero_ResolveWallMovement_maybe: the hero's cylinder (radius +0x794, from its feet at +0x214 - +0x7dc
// above the position, the height +0x510 - +0x214 + +0x7dc) swept from the position (moved by the root motion first, unless
// `noRootMotion`) by the rest of the move (CKSrvCollision_ResolveSweptCylinderWalls 0x19aa68, edges gathered; result
// +0x60c, data +0x610 / +0x638). Blocked (1): the target keeps the position in x / z, the move stops, the speed +0x530 is
// scaled by 1 - 0.01 * +0x347. Slid or pushed (2, 3): the target takes the bouncing vector (in the air without +0x358 bit
// 10, the vertical part of its length along the ground's plane +0x564), the move follows; a lone wall scales the speed by
// how much the velocity +0x540 runs into it (+0x35c bit 16: into it), several walls as when blocked (bit 16 set).
// +0x354 bit 18: a wall was met. (The original returns 1; the caller ignores it.)
void CKHkS08Hero::ResolveWallMovement(CVector3* move, CVector3* target, const CVector3* rootMotion,
                                      uint32_t noRootMotion) {
    float feetOffset;  // +0x7dc, read as a float
    std::memcpy(&feetOffset, &m_unk7dc, 4);
    const float lift = m_unk214;
    CLine line;
    if (noRootMotion != 0) {
        line.m_start.x = m_unk54c;
        line.m_start.z = m_unk554;
        line.m_VectDir.x = move->x;
        line.m_VectDir.z = move->z;
        line.m_start.y = (m_unk550 + lift) - feetOffset;
        line.m_VectDir.y = move->y;
    } else {
        line.m_VectDir.y = move->y - rootMotion->y;
        line.m_VectDir.z = move->z - rootMotion->z;
        line.m_start.x = m_unk54c + rootMotion->x;
        line.m_start.z = rootMotion->z + m_unk554;
        line.m_VectDir.x = move->x - rootMotion->x;
        line.m_start.y = ((rootMotion->y + m_unk550) + lift) - feetOffset;
    }
    const float height = (m_unk510 - lift) + feetOffset;
    CKSrvCollision* collision = static_cast<CKSrvCollision*>(g_pEngine->m_srvCollision);
    m_unk60c = collision->ResolveSweptCylinderWalls(&line, m_unk794, height, &m_wallSlide, &m_wallSlidePrev, nullptr, 1);
    m_unk354 &= 0xfffbffffu;
    m_unk35c &= 0xfffeffffu;
    const int32_t result = static_cast<int32_t>(m_unk60c);
    // The speed scaled by 1 + 0.01 * (u8)+0x347 * k (k = -1 when blocked or by several walls).
    auto scaleSpeed = [&](float k) {
        const float factor = static_cast<float>(static_cast<double>(m_unk347));  // fcfid + frsp
        m_unk530 = m_unk530 * ppc::fmadds(k * factor, -0.00999999978f, 1.0f);  // TOC +0x2c70 / +0x2c3c
    };
    if (result == 1) {
        target->x = m_unk54c;
        target->z = m_unk554;
        move->x = 0.0f;
        move->z = 0.0f;
        const float factor = static_cast<float>(static_cast<double>(m_unk347));
        m_unk530 = m_unk530 * ppc::fmadds(factor, -0.00999999978f, 1.0f);
        m_unk354 |= 0x40000u;
        return;
    }
    if (result < 1 || result > 3) return;
    float lift2 = 0.0f;  // TOC +0x2c24
    const CVector3& bounce = m_wallSlide.m_v3BouncingVector;
    if ((m_unk354 & 1u) == 0 && (m_unk358 & 0x400u) == 0) {
        // In the air: the bounce's length, the vertical part of its direction along the ground's plane.
        float by = bounce.y, bx = bounce.x, bz = bounce.z;
        float length = static_cast<float>(c22spyro::MathSqrtf(ppc::fmadds(bz, bz, ppc::fmadds(bx, bx, by * by))));
        if (length != 0.0f) {
            const float inverse = 1.0f / length;
            bz = bz * inverse;
            bx = bx * inverse;
            by = by * inverse;
        } else {
            length = 0.0f;
        }
        const float nx = m_unk564, ny = m_unk568, nz = m_unk56c;
        const float negDot = ppc::fnmadds(nz, bz, ppc::fmadds(nx, bx, ny * by));
        const float py = ppc::fmadds(ny, negDot, by);
        const float px = ppc::fmadds(nx, negDot, bx);
        const float pz = ppc::fmadds(nz, negDot, bz);
        const float projected = static_cast<float>(c22spyro::MathSqrtf(ppc::fmadds(pz, pz, ppc::fmadds(px, px, py * py))));
        float unitY = py;
        if (projected != 0.0f) unitY = py * (1.0f / projected);
        lift2 = length * unitY;
    }
    target->x = target->x + bounce.x;
    target->y = target->y + lift2;
    target->z = target->z + bounce.z;
    move->z = target->z - m_unk554;
    move->x = target->x - m_unk54c;
    move->y = target->y - m_unk550;
    if (((m_wallSlide.m_ba8Infos >> 1) & 1u) == 0) {
        // A lone wall: the velocity against its normal in x / z.
        float wx = m_wallSlide.m_v3Normal.x, wz = m_wallSlide.m_v3Normal.z;
        float wy = 0.0f;
        const float length = static_cast<float>(c22spyro::MathSqrtf(ppc::fmadds(wz, wz, ppc::fmadds(wx, wx, 0.0f))));
        if (length != 0.0f) {
            const float inverse = 1.0f / length;
            wz = wz * inverse;
            wx = wx * inverse;
            wy = inverse * wy;
        }
        const float dot = ppc::fmadds(wz, m_unk548, ppc::fmadds(wx, m_unk540, wy * m_unk544));
        if (dot < 0.0f) scaleSpeed(-dot);
        m_unk35c = (m_unk35c & 0xfffeffffu) | (dot <= 0.0f ? 0x10000u : 0u);
    } else {
        const float factor = static_cast<float>(static_cast<double>(m_unk347));
        m_unk530 = m_unk530 * ppc::fmadds(factor, -0.00999999978f, 1.0f);
        m_unk35c |= 0x10000u;
    }
    m_unk354 |= 0x40000u;
}

// 0x0035f6f8 SetPositions
void CKHkS08Hero::SetPositions(IKTime* clock, CVector3* target) {
    m_unk35c &= ~0x40000u;
    m_unk364 &= ~0x8000u;
    m_unk360 &= 0xfffffbfdu;
    CopyGroundContact(m_gcOldDatasInOut, m_gcCurDatasInOut);
    CVector3* const position = reinterpret_cast<CVector3*>(&m_unk54c);
    ICollisionMesh* deactivated = nullptr;
    if (!ResolveGroundContactAndPosition(clock, target, position, 0, &deactivated)) {
        const uint32_t firstStatus = m_gcCurDatasInOut.m_eContactStatus;
        if (!ResolveGroundContactAndPosition(clock, target, position, 1, nullptr)) {
            uint32_t falling = 0;  // +0x364 bit 15
            if (firstStatus == 3) {
                m_unk35c = (m_unk35c & ~0x40000u) | (m_gcCurDatasInOut.m_eContactStatus == 3 ? 0x40000u : 0u);
            } else {
                m_unk35c &= ~0x40000u;
                if (firstStatus == 2 && m_gcCurDatasInOut.m_eContactStatus == 2) falling = 0x8000;
            }
            m_unk364 = (m_unk364 & ~0x8000u) | falling;
            CopyGroundContact(m_gcCurDatasInOut, m_gcOldDatasInOut);
        }
        if (deactivated != nullptr) deactivated->SetActive(1);
    }
    m_unk558 = m_unk54c;
    m_unk55c = m_unk550;
    m_unk560 = m_unk554;
    m_unk54c = target->x;
    m_unk550 = target->y;
    m_unk554 = target->z;
    ICollisionMesh* ground = static_cast<ICollisionMesh*>(m_gcCurDatasInOut.m_pGround);
    if (ground == nullptr || m_gcCurDatasInOut.m_eContactStatus > 2) {
        m_unk564 = kHeroAxisY.x;  // TOC +0x2c48
        m_unk568 = kHeroAxisY.y;
        m_unk56c = kHeroAxisY.z;
    } else if (ground->GetClassID() != 0x13) {  // vt+0x18
        m_unk564 = m_gcCurDatasInOut.m_Normal.x;
        m_unk568 = m_gcCurDatasInOut.m_Normal.y;
        m_unk56c = m_gcCurDatasInOut.m_Normal.z;
    } else {
        // A moving ground's normal turned into the world, while its sector is active (else the last one stays).
        const CKSector* sector =
            static_cast<const CKSector*>(g_pEngine->m_level->m_vpSectors.m_pBlock[ground->GetSectorNumber()]);
        if ((sector->m_ba16Properties & 1) != 0) {
            Mat4_TransformVectors(ground->GetWorldMatrix(), reinterpret_cast<CVector3*>(&m_unk564),
                                  &m_gcCurDatasInOut.m_Normal, 1);
        }
    }
    m_unk57c = m_unk570;
    m_unk580 = m_unk574;
    m_unk584 = m_unk578;
    CVector3* const groundPoint = reinterpret_cast<CVector3*>(&m_unk570);
    if ((m_unk354 & 1u) == 0 && (m_unk35c & 0x400u) == 0) {
        *groundPoint = *position;
        return;
    }
    GroundContact_GetWorldPointOr(&m_gcCurDatasInOut, position, groundPoint);
}

// 0x00354cf0 CKHkS08Hero_SetCameraDirectionLock_maybe
void CKHkS08Hero::SetCameraDirectionLock(uint8_t airborne) {
    if (m_ui8Hero != m_ui8TrackedLeader || (m_unk35c & 0x400000u) != 0 || (m_unk358 & 4u) != 0) return;
    CKSrvCamera* camera = static_cast<CKSrvCamera*>(g_pEngine->m_srvCamera);
    if (airborne == 0) {
        if ((m_unk354 & 1u) != 0) camera->m_baTemporaryFlags &= ~1u;
        return;
    }
    if ((m_unk354 & 1u) != 0) return;
    static const CVector3 kAxisY = {0.0f, 1.0f, 0.0f};  // 0x00c50d40 (filled by a static initialiser)
    camera->EnableDirectionLock(&kAxisY);  // 0x0012bc98 CKSrvCamera_EnableDirectionLock_maybe
}

namespace {
// The camera's bit 0 of +0x46c cleared when the player's hero is in the air (+0x354 bit 0; the inlined
// CKHkS08Hero_SetCameraDirectionLock_maybe 0x354cf0 with 0, before the bit is cleared).
void ClearCameraLockIfOnGround(CKHkS08Hero* hero) {
    if (hero->m_ui8Hero == hero->m_ui8TrackedLeader && (hero->m_unk35c & 0x400000u) == 0 && (hero->m_unk358 & 4u) == 0 &&
        (hero->m_unk354 & 1u) != 0) {
        static_cast<CKSrvCamera*>(g_pEngine->m_srvCamera)->m_baTemporaryFlags &= ~1u;
    }
}
}  // namespace

// 0x0035ea70 CKHkS08Hero_ResolveGroundContactAndPosition_maybe
uint8_t CKHkS08Hero::ResolveGroundContactAndPosition(IKTime* clock, CVector3* target, const CVector3* previous,
                                                     uint32_t keepPrevious, ICollisionMesh** deactivated) {
    CKSrvCollision* collision = static_cast<CKSrvCollision*>(g_pEngine->m_srvCollision);
    CGroundContactDatasInOut& contact = m_gcCurDatasInOut;
    m_unk368 &= ~0x80u;
    m_unk514 = kHeroZeroVector.x;  // the push-off direction (+0x514): none
    m_unk518 = kHeroZeroVector.y;
    m_unk51c = kHeroZeroVector.z;
    collision->GroundProbePoints(&m_gcDatasIn, &contact, &target->x, 1);
    const float dx = target->x - previous->x;
    const float dy = target->y - previous->y;
    const float dz = target->z - previous->z;
    // The move against the grounds with engine flag 8 (faces the hero slides off, _maybe): crossing one that faces the
    // move puts the hero back on the line and pushes it off along the way back.
    {
        CLine line;
        line.m_start = *previous;
        line.m_VectDir = {dx, dy, dz};
        CLineCollisionDatas hit;
        hit.m_ftOnLine = 0x1.fffffep+127f;  // the word at 0x00c4acb8 + 0x28 (FLT_MAX)
        hit.m_pCollisionMesh = nullptr;
        hit.m_i32FaceIndex = -1;
        hit.m_ui8SectorNumber = 0;
        const CMasksOfGrdTypeForTests masks = {8, 0};
        if (collision->RaycastMeshes(&line, &hit, 1, 0, &masks) && hit.m_pCollisionMesh != nullptr &&
            (hit.m_pCollisionMesh->m_ba16EngineFlags & 8) != 0) {
            float by = -dy, bx = -dx, bz = -dz;  // the way back, normalised
            float sum = by * by;
            sum = ppc::fmadds(bx, bx, sum);
            sum = ppc::fmadds(bz, bz, sum);
            const float length = std::sqrt(sum)  /* Math_Sqrtf 0x10690 */;
            if (length != 0.0f) {
                const float inverse = 1.0f / length;
                bz = bz * inverse;
                bx = bx * inverse;
                by = by * inverse;
            }
            const ICollisionMesh* mesh = hit.m_pCollisionMesh;
            // BUG(original): a hit without a valid face reads the indices at address 0 (the raycast always sets one).
            const uint16_t* face = hit.m_i32FaceIndex != -1 && hit.m_i32FaceIndex < static_cast<int32_t>(mesh->m_ui16NbTriangle)
                                       ? mesh->m_aTriangle[hit.m_i32FaceIndex].m_aui16Index
                                       : nullptr;
            const CVector3 normal =
                ground_test::FaceNormal(mesh->m_aVertex[face[0]], mesh->m_aVertex[face[1]], mesh->m_aVertex[face[2]]);
            const float facing = ppc::fmadds(bz, -normal.z, ppc::fmsubs(by, -normal.y, normal.x * bx));
            if (facing > 0.0f) {
                m_unk518 = by;
                m_unk51c = bz;
                m_unk514 = bx;
                target->y = ppc::fmadds(dy, hit.m_ftOnLine, previous->y) - m_unk510;
                m_unk368 = (m_unk368 & ~0x80u) | 0x80u;
                return 1;
            }
        }
    }
    const uint32_t status = contact.m_eContactStatus;
    ICollisionMesh* ground = static_cast<ICollisionMesh*>(contact.m_pGround);
    if (status == 2) {
        // A ground above the target within m_fObjectHeight: the hero stays at its x / z unless the ground slides it.
        if (ground == nullptr || (ground->m_ba16EngineFlags & 8) == 0) {
            target->z = previous->z;
            target->x = previous->x;
        }
        if (keepPrevious == 0) return 0;
        m_unk368 = (m_unk368 & ~0x80u) | 0x80u;
        m_unk514 = -contact.m_Normal.x;
        m_unk518 = -contact.m_Normal.y;
        m_unk51c = -contact.m_Normal.z;
        const float lift = (m_gcDatasIn.m_fObjectHeight + 0.01f) - contact.m_fdH;  // TOC +0x2c74
        if (ground->GetClassID() == 0x13) {  // vt+0x18
            const CMatrix34* world = ground->GetWorldMatrix();  // vt+0x50
            const float down = -lift;
            target->z = ppc::fmadds(down, world->m_up.z, target->z);
            target->x = ppc::fmadds(down, world->m_up.x, target->x);
            target->y = ppc::fmadds(down, world->m_up.y, target->y);
        } else {
            target->y = target->y - lift;
        }
        if (!(target->y < m_unk574 + m_unk1f0)) {
            float speed = m_unk534;
            if (speed > 0.0f) speed = 0.0f;
            m_unk534 = speed;
            if ((m_unk354 & 1u) == 0) return 0;
            m_unk354 = (m_unk354 & ~0x200u) | 0x200u;
            return 0;
        }
        if ((ground->m_ba16EngineFlags & 8) != 0) return 0;
        CVector3 point;
        GroundContact_GetWorldPointOr(&contact, target, &point);
        const float above = point.y - m_unk574;
        const float reach = Vf160() * m_unk278;  // vt+0x160
        target->y = !(reach < above) ? point.y : m_unk574;
        ClearCameraLockIfOnGround(this);
        uint32_t flags = m_unk354 & 0xfffffdfeu;
        m_unk354 = flags;
        m_unk364 &= ~0x400u;
        m_unk354 &= ~2u;
        m_unk590 = 0xff;
        flags = (m_unk354 & ~6u) | 4u;
        m_unk354 = flags;
        if (m_ui8Hero == m_ui8TrackedLeader && (m_unk35c & 0x400000u) == 0 && (m_unk358 & 4u) == 0 && (m_unk354 & 1u) != 0) {
            static_cast<CKSrvCamera*>(g_pEngine->m_srvCamera)->m_baTemporaryFlags &= ~1u;
            flags = m_unk354;
        }
        m_unk354 = flags & 0xfffffdfeu;
        m_unk364 &= ~0x400u;
        m_unk354 &= ~2u;
        m_unk590 = 0xff;
        return 0;
    }
    if (status == 3) {
        // No ground under the target.
        if (keepPrevious == 0) {
            target->z = previous->z;
            target->x = previous->x;
            return 0;
        }
        *target = *previous;
        return 0;
    }
    if ((m_unk354 & 0x400u) != 0 && m_gcOldDatasInOut.m_pGround != nullptr && contact.m_pGround != m_gcOldDatasInOut.m_pGround) {
        target->z = previous->z;
        target->x = previous->x;
        return 0;
    }
    if (status == 1) {
        // A ground under the target within m_fDeltaMax: the hero is put on it.
        if ((m_unk354 & 1u) != 0) {
            if ((Vf150() & ground->m_ui16PropertiesFlags) != 0) {  // vt+0x150
                if (deactivated == nullptr) return 0;
                ground->SetActive(0);
                *deactivated = ground;
                return 0;
            }
            if (((ground->m_ba16EngineFlags >> 3) & 1) != 0) {
                m_unk534 = 0.0f;
                if ((m_unk354 & 1u) == 0) return 1;
                m_unk354 = (m_unk354 & ~0x200u) | 0x200u;
                return 1;
            }
            if ((m_unk35c & 0x400u) == 0) {
                SetDirectionLock(0);  // 0x009bdb48
                m_unk354 = (m_unk354 & ~6u) | 4u;
                SetDirectionLock(0);
            }
        }
        if (contact.m_pGround == nullptr || (ground->m_ba16EngineFlags & 8) == 0) {
            GroundContact_GetWorldPointOr(&contact, previous, target);
        }
        return 1;
    }
    if (status != 0) return 1;
    // The target under a ground (status 0).
    if ((m_unk35c & 0x400u) != 0) return 1;
    if ((m_unk354 & 1u) != 0) return 1;
    if (contact.m_fdH < m_gcDatasIn.m_fDeltaMax) {
        GroundContact_GetWorldPointOr(&contact, previous, target);
        return 1;
    }
    if (m_aui8Unk1a4[0x1a6 - 0x1a4] == 0 || (m_unk354 & 0x100u) != 0) {
        if (keepPrevious == 0) {
            target->z = previous->z;
            target->x = previous->x;
            return 0;
        }
        *target = *previous;
        return 0;
    }
    if (m_ui8Hero == m_ui8TrackedLeader && clock->m_afCurrentTime[0] - m_unk6f0 > 0.1f) {  // TOC +0x2c4c
        // The player's hero deep under a ground: put back where the way it came (the root motion included) crosses a
        // wall, 0.01 past it.
        CLine line;
        line.m_start = {target->x, target->y - m_unk1f0, target->z};
        const float wx = (previous->x + m_unk5a8) - target->x;
        const float wy = (previous->y + m_unk5ac) - target->y;
        const float wz = (previous->z + m_unk5b0) - target->z;
        line.m_VectDir = {wx, wy, wz};
        CGroundEdgeDatasOut edge;
        if (collision->RaycastWalls(&line, m_unk1f0, &edge, 0, nullptr, 1)) {
            uint32_t slide = 0;
            if (m_aui8Unk1a4[0x1b8 - 0x1a4] != 0 && static_cast<int32_t>(m_unk35c) >= 0 && (m_unk354 & 0x800000u) == 0) {
                slide = ((m_unk354 >> 24) & 1u) ^ 1u;
            }
            uint32_t push = 0;
            if (contact.m_fdH > m_unk2ec || (ground->m_ui16PropertiesFlags & 0x94u) != 0) push = slide;
            const bool place = (m_aui8Unk1a4[0x1b4 - 0x1a4] != 0 && (m_unk354 & 0x1000000u) == 0) || (push & 0xffu) != 0;
            if (place) {
                float ux = wx, uy = wy, uz = wz;
                const float t = edge.m_ftLine;
                float sum = uy * uy;
                target->x = ppc::fmadds(ux, t, target->x);
                target->y = ppc::fmadds(uy, t, target->y);
                target->z = ppc::fmadds(uz, t, target->z);
                sum = ppc::fmadds(ux, ux, sum);
                sum = ppc::fmadds(uz, uz, sum);
                const float length = std::sqrt(sum)  /* Math_Sqrtf 0x10690 */;
                if (length != 0.0f) {
                    const float inverse = 1.0f / length;
                    uz = uz * inverse;
                    ux = ux * inverse;
                    uy = uy * inverse;
                }
                target->x = ppc::fmadds(ux, 0.01f, target->x);  // TOC +0x2c74
                target->y = ppc::fmadds(uy, 0.01f, target->y);
                target->z = ppc::fmadds(uz, 0.01f, target->z);
                // The wall's normal, flattened (+0x6e0).
                m_unk6e0 = edge.m_EdgeNormal.x;
                m_unk6e4 = edge.m_EdgeNormal.y;
                m_unk6e4 = 0.0f;
                m_unk6e8 = edge.m_EdgeNormal.z;
                float normalSum = m_unk6e4 * m_unk6e4;
                normalSum = ppc::fmadds(m_unk6e0, m_unk6e0, normalSum);
                normalSum = ppc::fmadds(m_unk6e8, m_unk6e8, normalSum);
                const float normalLength = std::sqrt(normalSum)  /* Math_Sqrtf 0x10690 */;
                if (normalLength != 0.0f) {
                    const float inverse = 1.0f / normalLength;
                    m_unk6e8 = inverse * m_unk6e8;
                    m_unk6e0 = inverse * m_unk6e0;
                    m_unk6e4 = inverse * m_unk6e4;
                }
                if ((push & 0xffu) != 0) m_unk360 = (m_unk360 & ~2u) | 2u;
                m_unk360 = (m_unk360 & ~0x400u) | 0x400u;
                return 0;
            }
        }
    }
    Vf178(clock, 0);  // vt+0x178 0x002f8708
    const uint32_t keep = ((m_unk360 & 0x4000000u) != 0 || (m_unk35c & 0x10000u) != 0) ? 0x4000000u : 0u;
    m_unk360 = (m_unk360 & ~0x4000000u) | keep;
    return 1;
}

// 0x00359c60 CKHkS08Hero_UpdateSignedSlopePitchClass_maybe: the slope under the move (+0x7a4, degrees: the angle between
// the move +0x540 and its projection along the ground normal +0x564, negative going down) and its class (+0x58c: 1 up,
// 2 down) once it reaches +0x348 degrees; 0 / 0 without +0x1a8, in the air (+0x354 bit 0) or bit 22, or standing.
void CKHkS08Hero::UpdateSignedSlopePitchClass() {
    m_unk58c = 0;
    if (m_aui8Unk1a4[0x1a8 - 0x1a4] == 0 || (m_unk354 & 0x400000u) != 0 || (m_unk354 & 1u) != 0 || m_unk530 == 0.0f) {
        m_unk7a4 = 0.0f;
        return;
    }
    const float vx = m_unk540, vy = m_unk544, vz = m_unk548;
    const float nx = m_unk564, ny = m_unk568, nz = m_unk56c;
    const float ax = ppc::fmsubs(ny, vz, nz * vy);
    const float ay = ppc::fmsubs(nz, vx, vz * nx);
    const float az = ppc::fmsubs(vy, nx, ny * vx);
    float by = ppc::fmsubs(nx, az, nz * ax);
    float bz = ppc::fmsubs(ny, ax, nx * ay);
    float bx = ppc::fmsubs(nz, ay, ny * az);
    const float length = std::sqrt(ppc::fmadds(bz, bz, ppc::fmadds(bx, bx, by * by)));  // Math_Sqrtf 0x10690
    if (length != 0.0f) {
        const float inverse = 1.0f / length;  // TOC +0x2c3c
        bz = bz * inverse;
        bx = bx * inverse;
        by = by * inverse;
    }
    const float along = ppc::fmadds(bz, vz, ppc::fmadds(bx, vx, by * vy));
    m_unk7a4 = along >= 1.0f ? 0.0f : crt::Acosf(along) * 57.2957801818847656f;  // TOC +0x2cdc
    if (ppc::fmadds(nz, vz, ppc::fmadds(nx, vx, ny * vy)) < 0.0f) m_unk7a4 = -m_unk7a4;
    if (static_cast<float>(static_cast<double>(m_unk348)) <= std::fabs(m_unk7a4)) {
        m_unk58c = m_unk7a4 >= 0.0f ? 1u : 2u;
    }
}

// 0x00362040 IKHkHero_IsLockedToObject_maybe: +0x358 bit 2.
uint8_t CKHkS08Hero::IsLockedToObject() { return static_cast<uint8_t>((m_unk358 >> 2) & 1u); }

// 0x00361b20 IKHkHero_SetInvulnerable_maybe: +0x35c bit 2.
void CKHkS08Hero::SetInvulnerable(uint8_t invulnerable) {
    m_unk35c = (m_unk35c & 0xfffffffbu) | (static_cast<uint32_t>(invulnerable) << 2);
}

// 0x003626a0 IKHkHero_SetFloat530_IfAttachedMovementEnabled_maybe: +0x530 while +0x358 bit 3 is set.
void CKHkS08Hero::SetUnk530IfAttachedMovement(float value) {
    if ((m_unk358 & 8u) == 0) return;
    m_unk530 = value;
}

// 0x00362688 IKHkHero_SetFloat534_IfAttachedMovementEnabled_maybe: +0x534 while +0x358 bit 3 is set.
void CKHkS08Hero::SetUnk534IfAttachedMovement(float value) {
    if ((m_unk358 & 8u) == 0) return;
    m_unk534 = value;
}

// 0x00364608 CKHkS08Hero_DetachFromObject_maybe. STUB(C2.8: attachments): an attached hero (+0x358 bit 0) leaves its
// object: placed at its hot spot (IKHkHero_PlaceAtHotspotOrPosition_maybe) when locked, the attachment bits of
// +0x358..+0x364 cleared, the default volumes back, +0x794 = +0x218, vt+0x124, +0x90..+0xa4 cleared. Nothing is
// attached before C2.8 (+0x358 bit 0 clear: nothing to do).
void CKHkS08Hero::DetachFromObject() {
    if ((m_unk358 & 1u) == 0) return;
    DOTD_STUB_ONCE("CKHkS08Hero_DetachFromObject_maybe 0x364608 (C2.8)");
}

namespace {
// 0x002ce3b8 CKGrpS08Hero_vf124 (vt+0x124): the jumps per hero, table 0x00a70490 (a copy of IKHkHero.cpp's).
const uint8_t kNbJumpsOfHero[16] = {2, 2, 0, 0, 0, 0, 0, 0, 2, 2, 0, 0, 0, 0, 0, 0};
}  // namespace

// 0x00354990 IKHkHero_FindNextEnabledJump (step 4 AI): the first jump after `index` (group vt+0x124
// of them, +0x1c0) that is enabled (its byte +5), or -1.
int8_t CKHkS08Hero::FindNextEnabledJump(int8_t index) {
    const uint8_t count = kNbJumpsOfHero[m_ui8Hero & 15];  // vt+0x124
    for (int32_t i = static_cast<int8_t>(index + 1); i < count; ++i) {
        if (m_asJumps[i].m_bEnable != 0) return static_cast<int8_t>(i);
    }
    return -1;
}

// 0x0035e3e8 IKHkHero_StartJumpOrFall_maybe (the base of vt+0x178): the next jump stage of the hero (+0x1c0, +0x590 the current one, 0xff
// none): `flag` 1 is the jump command (the ground jump, the double jump / flap in the air), 0 the ground is gone (the
// hero walked off an edge or the ground probe found it too far below: ResolveGroundContactAndPosition). A hero in the air
// (+0x354 bit 0) takes the next enabled stage once +0x20c seconds have passed since +0x790 (else the current stage again),
// a hero on the ground the next one after the current stage; no stage left: nothing. The stage gives the vertical speed
// (+0x534 = its impulse; a fall, flag 0, starts at 0 unless +0x358 bit 10), +0x790 the time of the stage, the position
// +0x558.. goes to +0x474.., +0x368 bit 1 takes whether the hero's node was drawn this frame, the player's hero locks the
// camera's direction, and the hero is in the air: +0x354 bit 0 set, bit 2 cleared (a jump command also sets bit 1).
// With the hero attached (+0x368 bit 11) or without the jump table flag (+0x1a6) it does nothing.
void CKHkS08Hero::StartJumpOrFall(IKTime* clock, uint8_t flag) {
    if ((m_unk368 & 0x800u) != 0) return;
    if (m_aui8Unk1a4[0x1a6 - 0x1a4] == 0) return;
    const uint32_t flags354 = m_unk354;
    const bool airborne = (flags354 & 1u) != 0;
    // The position and the drawn bit that every stage start stores.
    auto storeStart = [this]() {
        m_unk474 = m_unk558;
        m_unk47c = m_unk560;
        m_unk478 = m_unk55c;
        const uint32_t drawn = static_cast<CSGLeaf*>(m_pKGLObject)->m_ui16LastRenderedFrame == g_ui16RenderFrameCounter ? 2u : 0u;
        m_unk368 = (m_unk368 & 0xfffffffdu) | drawn;
    };
    if (!airborne && flag == 0) {
        // The ground is gone: the fall takes the next enabled stage after the current one.
        const int8_t stage = FindNextEnabledJump(static_cast<int8_t>(m_unk590));
        if (stage == -1) return;
        storeStart();
        const uint32_t flags358 = m_unk358;
        m_unk790 = clock->m_afCurrentTime[0];
        if ((flags358 & 0x400u) == 0) m_unk534 = 0.0f;
        m_unk590 = static_cast<uint8_t>(stage);
        SetCameraDirectionLock(1);  // the inlined 0x00354cf0 (airborne is still clear: the camera is told)
        m_unk354 = (m_unk354 | 1u) & ~4u;
        return;
    }
    if (airborne || flag != 0) {
        if ((flags354 & 0x800u) != 0 || (m_unk35c & 2u) != 0 || (flags354 & 0x200u) != 0) return;
        if (m_ui8Hero == m_ui8TrackedLeader && !airborne) {
            // A jump from the ground: the ground must still be the one under the hero (not a moving ground: those are
            // trusted), probed from the position raised by +0x208 with the object height 0.1.
            IKSerializable* ground = m_gcCurDatasInOut.m_pGround;
            if (ground != nullptr) {
                if (ground->IsKindOfClass(CDynamicGround::kClassKey) == 0) {  // vt+0x08
                    CGroundContactDatasIn in;
                    in.m_fDeltaMax = m_unk1f0;
                    in.m_fObjectHeight = 0.1f;  // TOC1 +0x2c4c
                    in.m_MasksOfGrdForTest[0] = 1;
                    in.m_MasksOfGrdForTest[1] = 0;
                    CGroundContactDatasInOut contact;
                    CopyGroundContact(contact, m_gcCurDatasInOut);
                    const float point[3] = {m_unk54c, m_unk550 + m_unk208, m_unk554};
                    static_cast<CKSrvCollision*>(g_pEngine->m_srvCollision)->GroundProbePoints(&in, &contact, point, 1);  // 0x00196540
                    if (contact.m_pGround != ground) return;
                }
            }
        }
        int8_t stage;
        if (airborne && !((clock->m_afCurrentTime[0] - m_unk790) >= m_unk20c)) {
            stage = static_cast<int8_t>(m_unk590);  // the same stage again
        } else {
            stage = FindNextEnabledJump(static_cast<int8_t>(m_unk590));
        }
        if (stage == -1) return;
        if ((m_unk354 & 1u) == 0) storeStart();
        m_unk534 = m_asJumps[stage].m_fImpulse;
        m_unk590 = static_cast<uint8_t>(stage);
        if ((m_unk368 & 0x100u) == 0) m_unk790 = -1000.0f;  // TOC1 +0x2c58
        SetCameraDirectionLock(1);
        m_unk354 = ((m_unk354 | 1u) & ~6u) | 2u;
        return;
    }
}

// 0x00361c98 IKHkHero_GetFloat218_maybe (step 4 AI): +0x218 (the hero's radius, as AIUpdatePathToTarget adds it).
float CKHkS08Hero::GetFloat218() const { return m_unk218; }
