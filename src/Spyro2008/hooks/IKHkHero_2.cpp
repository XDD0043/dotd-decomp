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
//   [x] 0x354a80  CKHkS08Hero_ApplyHazardHitAndLeaveAttach_maybe
//   [ ] 0x354c30  IKHkHero_RememberDynamicGround_maybe  [dead]
//   [x] 0x354cf0  CKHkS08Hero_SetCameraDirectionLock_maybe
//   [ ] 0x354da0  FUN_00354da0  [dead]
//   [ ] 0x354ef8  IKHkHero_ProbeGroundWorldPoint_maybe  [dead]
//   [ ] 0x355098  IKHkHero_vf174  [dead: only in the abstract IKHkHero vtable 0xb22f10 (vt+0x174), which only IKHkHero's destructors 0x9be9a8 / 0x9bea98 install; CKHkS08Hero, the only hero, has 0x2f8678 CKHkS08Hero_vf174 in that slot of its vtable 0xb22c98 (C2.8 port-final F07)]
//   [ ] 0x3550c0  IKHkHero_InitStationaryMoveRequest_maybe  [dead]
//   [ ] 0x355130  IKHkHero_StateThreePhaseTimedMove_Condition_maybe  [dead]
//   [ ] 0x355190  IKHkHero_StateClimbOntoObject_Condition_maybe  [dead]
//   [ ] 0x355240  FUN_00355240  [dead]
//   [ ] 0x3552d8  FUN_003552d8  [dead]
//   [x] 0x355328  CKHkS08Hero_UpdateHazardAndSavedPositionRespawn_maybe
//   [ ] 0x3557e8  IKHkHero_vf180  [dead: only in the abstract IKHkHero vtable 0xb22f10 (vt+0x180), which only IKHkHero's destructors 0x9be9a8 / 0x9bea98 install; CKHkS08Hero, the only hero, has 0x2f8518 CKHkS08Hero_vf180 in that slot of its vtable 0xb22c98 (C2.8 port-final F07)]
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
//   [x] 0x359388  CKHkS08Hero_UpdateModelOffsetAndBank_maybe
//   [x] 0x359988  IKHkHero_SetPositionAndDirection_maybe
//   [ ] 0x359b30  Vec3_ProjectOnPlaneNormalizeScale_maybe  [dead]
//   [x] 0x359c60  CKHkS08Hero_UpdateSignedSlopePitchClass_maybe
//   [ ] 0x359e90  IKHkHero_StateImpulseSlide_maybe  [dead: no pointer to its descriptor 0xba15d0, no call]
//   [ ] 0x35a4c8  IKHkHero_StateSteeredVelocityMove_maybe  [dead]
//   [x] 0x35b058  IKHkHero_PlaceAtHotspotOrPosition_maybe
//   [x] 0x35b278  CKHkS08Hero_ResolveWallMovement_maybe
//   [ ] 0x35b710  FUN_0035b710  [dead]
//   [ ] 0x35e010  IKHkHero_StartJumpWithSpeed_maybe  [dead]
//   [ ] 0x35e288  IKHkHero_ClearAirborneState_maybe  [dead]
//   [x] 0x35e3e8  IKHkHero_StartJumpOrFall_maybe  (CKHkS08Hero::StartJumpOrFall)
//   [x] 0x35ea70  CKHkS08Hero_ResolveGroundContactAndPosition_maybe
//   [x] 0x35f6f8  SetPositions
//   [ ] 0x35fbb0  IKHkHero_StateClimbOntoObject_maybe  [dead]
//   [ ] 0x360110  IKHkHero_StateFollowBezier_maybe  [dead: no pointer to its descriptor 0xba1630, no call]
//   [x] 0x360648  CKHkS08Hero_UpdateDynamicGroundAttachment_maybe
//   [x] 0x360c50  CKHkS08Hero_UpdateLocomotionAndResolvePosition_maybe
//   [x] 0x361960  CKHkS08Hero_GetDragonIndex
//   [x] 0x361968  CKHkS08Hero_GetPositionPtr
//   [ ] 0x361a10  IKHkHero_GetVec3Ptr558_maybe  [dead]
//   [ ] 0x361a20  IKHkHero_GetVec3Ptr474_maybe  [dead]
//   [x] 0x361a30  IKHkHero_GetPtr3E0_maybe  (IKHkHero::GetPFCharacter)
//   [x] 0x361a40  IKHkHero_GetVec3Ptr430_maybe  (IKHkHero::GetPFDestination)
//   [x] 0x361a50  CKHkS08Hero_GetForwardDirPtr_maybe  (inlined at the callers: &m_unk540)
//   [x] 0x361a60  IKHkHero_GetVec3Ptr3B8_maybe  (IKHkHero::GetUnk3B8Ptr; inlined in CKS08GameManager_GetFocusedHeroMoveVector_maybe)
//   [ ] 0x361a70  IKHkHero_SetFlag360Bit19_maybe  [dead]
//   [x] 0x361a90  IKHkHero_GetFlag354Bit0_Word_maybe  (IKHkHero::GetFlag354Bit0)
//   [ ] 0x361aa0  IKHkHero_GetFlag354Bit1_maybe  [dead]
//   [x] 0x361ab0  IKHkHero_GetFlag35CBit8_maybe  (IKHkHero::GetFlag35CBit8)
//   [ ] 0x361ac0  CKHkS08Hero_CtlState2_ScriptedMoveTo_Condition_2  [dead]
//   [ ] 0x361b00  IKHkHero_GetByte354Bit0_maybe  [dead]
//   [x] 0x361b10  IKHkHero_IsInvulnerable_maybe  (IKHkHero::IsInvulnerable; inlined in CKS08GameManager_GetHeroesInvulnerableMask_maybe)
//   [x] 0x361b20  IKHkHero_SetInvulnerable_maybe
//   [ ] 0x361b40  IKHkHero_GetFlag354Bit21_maybe  [dead]
//   [x] 0x361b50  IKHkHero_GetFlag358Bit8_maybe  (IKHkHero::GetFlag358Bit8)
//   [x] 0x361b60  IKHkHero_GetFloat26C_maybe  (IKHkHero::GetUnk26C)
//   [x] 0x361b68  CKHkS08Hero_GetGroundInfo_maybe
//   [x] 0x361b70  CKHkS08Hero_GetHotSpot
//   [x] 0x361c00  CKHkS08Hero_GetFloat510_maybe  (IKHkHero::GetUnk510; inlined in CKHkS08Hero_LocoState4_Ground)
//   [ ] 0x361c08  IKHkHero_GetFloat278_maybe  [dead]
//   [x] 0x361c10  IKHkHero_GetFloat530_maybe  (IKHkHero::GetUnk530; inlined in CKHkS08Sparx_SteerTowardTarget_maybe)
//   [ ] 0x361c18  IKHkHero_GetVerticalSpeed_maybe  [dead]
//   [ ] 0x361c20  IKHkHero_GetMoveEntryIndex_maybe  [dead]
//   [ ] 0x361c28  FUN_00361c28  [dead]
//   [ ] 0x361c78  IKHkHero_GetMoveEntryFloat0C_maybe  [dead]
//   [x] 0x361c98  IKHkHero_GetFloat218_maybe
//   [x] 0x361ca0  IKHkHero_GetVec3Ptr4A8_maybe  (IKHkHero::GetGroundContactIn)
//   [ ] 0x361cb0  IKHkHero_GetFlag354Bit9_maybe  [dead]
//   [x] 0x361cc0  IKHkHero_SetFlag354Bit9_maybe  (IKHkHero::SetFlag354Bit9)
//   [ ] 0x361cf8  IKHkHero_SetFloat594_maybe  [dead]
//   [ ] 0x361d00  IKHkHero_SetFloat598_maybe  [dead]
//   [x] 0x361d08  CKHkS08Hero_CanAttachTo_Thunk  (thunk: CanAttachTo, vt+0xe0, called directly)
//   [x] 0x361d50  CKHkS08Hero_GetAttachedObject_maybe
//   [ ] 0x361d58  KStub_Nop_361d58  [dead]
//   [ ] 0x361d60  IKHkHero_GetFlag354Bit18_maybe  [dead]
//   [ ] 0x361d70  IKHkHero_GetFlag35CBit16_maybe  [dead]
//   [ ] 0x361d80  IKHkHero_GetFlag354Bit19_maybe  [dead]
//   [ ] 0x361d90  IKHkHero_GetPartnerHero_maybe  [dead]
//   [x] 0x361d98  IKHkHero_SetFlag364Bit5_maybe  (IKHkHero::SetFlag364Bit5)
//   [ ] 0x361db0  IKHkHero_SetFlag364Bit7_maybe  [dead]
//   [ ] 0x361dd0  IKHkHero_SetFlag364Bit8_maybe  [dead]
//   [x] 0x361de8  IKHkHero_GetFlag354Bit30_maybe  (CKHkS08Hero.h)
//   [x] 0x361df8  IKHkHero_CallVf140_maybe  (CKHkS08Hero::CallVf140)
//   [ ] 0x361e40  IKHkHero_GetFlag364Bit16_maybe  [dead]
//   [ ] 0x361e50  IKHkHero_GetFlag364Bit17_maybe  [dead]
//   [ ] 0x361e60  IKHkHero_GetPtr120_maybe  [dead]
//   [ ] 0x361e68  IKHkHero_SetFlag368Bit0_maybe  [dead]
//   [ ] 0x361e80  CKHkS08Hero_GetCurrentAnimTime_2  [dead]
//   [x] 0x361ee0  IKHkHero_GetCurrentAnim_maybe  (CKHkS08Hero::GetCurrentAnim)
//   [x] 0x361f40  CKHkS08Hero_GetCurrentAnimResource
//   [x] 0x361fa0  IKHkHero_IsAnimBlendCrossfading_maybe
//   [x] 0x362000  IKHkHero_IsObjectControllingAnim_maybe  (IKHkHero::IsObjectControllingAnim)
//   [x] 0x362010  IKHkHero_SetObjectControlsAnim_maybe
//   [x] 0x362040  IKHkHero_IsLockedToObject_maybe
//   [x] 0x362050  IKHkHero_SetAttachedMovementEnabled_maybe
//   [ ] 0x3620c8  IKHkHero_GetFlag364Bit26_maybe  [dead]
//   [ ] 0x3620d8  IKHkHero_SetFlag364Bit26_IfAttached_maybe  [dead]
//   [ ] 0x362108  IKHkHero_GetFlag35CBit3_maybe  [dead]
//   [x] 0x362118  CKHkS08Hero_TeleportTo_Thunk  (CKHkS08Hero::TeleportToThunk)
//   [x] 0x362150  IKHkHero_SetCollisionDisabledWhileAttached_maybe
//   [x] 0x3622a8  IKHkHero_SetLockedToObject_maybe
//   [x] 0x362360  CKHkS08Hero_AttachToObject_maybe
//   [x] 0x362450  CKHkS08Hero_GetCurrentAnimDuration
//   [ ] 0x3624b8  CKHkS08Hero_WillAnimEndThisFrame_maybe  [dead: no pointer to its descriptor 0xba1b40, no call]
//   [ ] 0x3625c8  CKHkS08Hero_SetHidden_maybe  [dead: no pointer to its descriptor 0xba1b48, no call]
//   [ ] 0x362618  FUN_00362618  [dead]
//   [x] 0x362670  IKHkHero_SetAttachedMoveSpeed_maybe  (CKHkS08Hero.h)
//   [x] 0x362688  IKHkHero_SetFloat534_IfAttachedMovementEnabled_maybe
//   [x] 0x3626a0  IKHkHero_SetFloat530_IfAttachedMovementEnabled_maybe
//   [ ] 0x3626b8  IKHkHero_SetFlag358Bit6_IfAttachedMovementEnabled_maybe  [dead]
//   [x] 0x3626e8  IKHkHero_IsAttachedMovementEnabled_maybe  (CKHkS08Hero.h)
//   [x] 0x3626f8  CKHkS08Hero_GetPlayerInputFloat38C  (CKHkS08Hero::GetPlayerInputFloat38C)
//   [ ] 0x362760  IKHkHero_GetFlag360Bit8_IfAttached_maybe  [dead]
//   [ ] 0x362788  IKHkHero_GetFlag360Bit15_IfAttached_maybe  [dead]
//   [ ] 0x3627b0  IKHkHero_GetFlag360Bit14_IfAttached_maybe  [dead]
//   [ ] 0x3627d8  IKHkHero_GetFlag360Bit16_IfAttached_maybe  [dead]
//   [ ] 0x362800  IKHkHero_GetFlag35CBit28_IfAttached_maybe  [dead]
//   [ ] 0x362828  IKHkHero_GetFlag364Bit12_IfAttached_maybe  [dead]
//   [ ] 0x362850  IKHkHero_GetFlag35CBit21_IfAttached_maybe  [dead]
//   [x] 0x362878  IKHkHero_GetFlag35CBit0_IfAttached_maybe  (IKHkHero::GetFlag35CBit0IfAttached)
//   [ ] 0x3628a0  IKHkHero_GetFlag35CBit1_IfAttached_maybe  [dead]
//   [ ] 0x3628c8  IKHkHero_SetFloat794_IfAttached_maybe  [dead]
//   [x] 0x3628e0  IKHkHero_ClearFlag358Bit21_IfAttached_maybe  (IKHkHero::ClearFlag358Bit21IfAttached)
//   [ ] 0x362908  IKHkHero_GetFlag360Bit7_IfAttached_maybe  [dead]
//   [ ] 0x362930  IKHkHero_GetFlag358Bit22_IfAttached_maybe  [dead]
//   [ ] 0x362950  CKHkS08Hero_GetPlayerInputFloat388  [dead: no pointer to its descriptor 0xba1bf0, no call]
//   [ ] 0x3629b8  CKHkS08Hero_GetPlayerMoveInputPtr  [dead: no pointer to its descriptor 0xba1bf8, no call]
//   [x] 0x362a40  CKHkS08Hero_GetPlayerMoveVectorPtr
//   [x] 0x362ac8  CKHkS08Hero_GetPlayerIndexIfControlled_maybe  (inlined at the callers: m_ui8Leader when m_ui8Hero == m_ui8TrackedLeader, else 0xff)
//   [x] 0x362af0  CKHkS08Hero_IsPlayerControlled
//   [ ] 0x362b10  FUN_00362b10  [dead]
//   [ ] 0x362b70  FUN_00362b70  [dead]
//   [ ] 0x362bb8  CKHkS08Hero_GetPlayerInputFlag360b17  [dead: no pointer to its descriptor 0xba1c28, no call]
//   [ ] 0x362c28  CKHkS08Hero_GetPlayerInputFlag360b29  [dead: no pointer to its descriptor 0xba1c30, no call]
//   [x] 0x362c98  CKHkS08Hero_GetPlayerInputFlag358b21  (CKHkS08Hero::GetPlayerInputFlag358b21)
//   [ ] 0x362d00  CKHkS08Hero_GetPlayerInputFlag358b20  [dead: no pointer to its descriptor 0xba1c40, no call]
//   [ ] 0x362d68  CKHkS08Hero_GetPlayerInputByte395  [dead: no pointer to its descriptor 0xba1c48, no call]
//   [x] 0x362dd0  CKHkS08Hero_GetPlayerInputByte394
//   [ ] 0x362e38  FUN_00362e38  [dead]
//   [ ] 0x362ef0  CKHkS08Hero_GetPlayerInputWord392  [dead: no pointer to its descriptor 0xba1c60, no call]
//   [ ] 0x362f60  CKHkS08Hero_GetPlayerInputWord390  [dead: no pointer to its descriptor 0xba1c68, no call]
//   [x] 0x362fd0  IKHkHero_SetPendingSourceAndVec3_Flag35CBit4_maybe  (IKHkHero::SetPendingSource)
//   [ ] 0x363060  IKHkHero_GetObjectDrivenBezierProgress_maybe  [dead]
//   [ ] 0x363090  CKHkS08Hero_UpdateObjectDrivenMove_maybe  [dead: no pointer to its descriptor 0xba1c88, no call]
//   [ ] 0x363110  IKHkHero_GetModelNode_maybe  [dead]
//   [ ] 0x363118  IKHkHero_PlayAnimResource_maybe  [dead: only in the abstract IKHkHero vtable 0xb22f10 (vt+0xc0), which only IKHkHero's destructors 0x9be9a8 / 0x9bea98 install; CKHkS08Hero, the only hero, has 0x32ad80 CKHkS08Hero_PlayAnimResource_maybe in that slot of its vtable 0xb22c98 (C2.8 port-final F07)]
//   [ ] 0x363218  IKHkHero_SetObjectDrivenBezierMove_maybe  [dead]
//   [ ] 0x363318  IKHkHero_SetObjectDrivenMoveTarget_maybe  [dead]
//   [x] 0x363378  IKHkHero_SetObjectAnimTime_maybe
//   [x] 0x363410  IKHkHero_AdvanceObjectAnimTime_maybe
//   [ ] 0x3634b0  IKHkHero_SetAnimPairAndWeight_maybe  [dead: only in the abstract IKHkHero vtable 0xb22f10 (vt+0xc8), which only IKHkHero's destructors 0x9be9a8 / 0x9bea98 install; CKHkS08Hero, the only hero, has 0x32aec8 CKHkS08Hero_SetAnimPairAndWeight_maybe in that slot of its vtable 0xb22c98 (C2.8 port-final F07)]
//   [ ] 0x363578  IKHkHero_CrossfadeAnimResource_maybe  [dead: only in the abstract IKHkHero vtable 0xb22f10 (vt+0xc4), which only IKHkHero's destructors 0x9be9a8 / 0x9bea98 install; CKHkS08Hero, the only hero, has 0x32ac88 CKHkS08Hero_CrossfadeAnimResource_maybe in that slot of its vtable 0xb22c98 (C2.8 port-final F07)]
//   [ ] 0x363640  IKHkHero_SetDesiredMoveDirectionFlat_maybe  [dead]
//   [ ] 0x3636f8  IKHkHero_SetFlag364Bit18_IfFlag364Bit26_maybe  [dead]
//   [ ] 0x363728  IKHkHero_SetFlag364Bit27_IfFlag364Bit26_maybe  [dead]
//   [ ] 0x363758  IKHkHero_SetPtr120_IfFlag364Bit26_maybe  [dead]
//   [x] 0x363770  IKHkHero_GetLedgeGroundContact_maybe  (IKHkHero::GetLedgeGroundContact)
//   [ ] 0x363790  FUN_00363790  [dead]
//   [x] 0x3638a0  IKHkHero_GetCurrentAnimTime_maybe  (CKHkS08Hero::GetCurrentAnimTime)
//   [x] 0x363900  IKHkHero_UpdateMoveTo_maybe
//   [x] 0x363c40  CKHkS08Hero_GetGroundObject_maybe  (CKHkS08Hero.h)
//   [x] 0x363c78  IKHkHero_GetTargetingPositionPtr_maybe  (IKHkHero::GetTargetingPositionPtr; inlined in its ported callers)
//   [x] 0x363ca0  IKHkHero_GetFlag360Bit12_maybe  (IKHkHero::GetFlag360Bit12; inlined in CKGrpS08Hero_RequestDragonSelection_maybe)
//   [ ] 0x363cb0  IKHkHero_UpdateWaypointSteer_maybe  [dead]
//   [x] 0x363dc8  IKHkHero_SetFlag360Bit14_IfAttached_maybe
//   [x] 0x363df8  IKHkHero_SetFlag360Bit15_IfAttached_maybe
//   [ ] 0x363e28  IKHkHero_SetFlag358Bit22_IfAttached_maybe  [dead]
//   [x] 0x363e58  IKHkHero_SetFlag364Bit12_IfAttached_maybe  (CKHkS08Hero.h)
//   [x] 0x363e88  IKHkHero_SetFlag35CBit0_IfAttached_maybe  (CKHkS08Hero.h)
//   [ ] 0x363eb8  IKHkHero_SetFlag35CBit1_IfAttached_maybe  [dead]
//   [x] 0x363ee8  IKHkHero_SetFlag35CBit3_IfAttached_maybe
//   [ ] 0x363f18  IKHkHero_SetFlag360Bit20_maybe  [dead]
//   [ ] 0x363f38  IKHkHero_SetFlag35CBit28_IfAttached_maybe  [dead]
//   [ ] 0x363f68  IKHkHero_SetFlag360Bit7_IfAttached_maybe  [dead]
//   [x] 0x363f98  IKHkHero_SetFlag360Bit8_IfAttached_maybe
//   [x] 0x363fc8  IKHkHero_SetFlag35CBit21_IfAttached_maybe
//   [x] 0x363ff8  IKHkHero_IsFlag35CBit6_AndFlag3B0Bit6Clear_maybe  (CKHkS08Hero.h)
//   [x] 0x364020  CKHkS08Hero_WillAnimEndWithin_maybe
//   [x] 0x364100  CKHkS08Hero_GetAnimMarkWindow
//   [x] 0x364268  IKHkHero_PassesTrackerAssignFlagChecks_maybe  (CKHkS08Hero.h)
//   [ ] 0x3642d8  IKHkHero_SetWaypointSteerTarget_maybe  [dead]
//   [x] 0x364470  IKHkHero_SetMoveDestination_maybe
//   [x] 0x364608  CKHkS08Hero_DetachFromObject_maybe
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
#include "Spyro2008/groups/CKGrpS08Hero.h"
#include "k2000/animation/AnimBlendSlot.h"
#include "k2000/graphical/CKAnmKeyFrameController.h"
#include "k2000/graphical/animation/CKBlenderController.h"
#include "k2000/logic/CSGHotSpot.h"
#include "k2000/math/CMatrix34.h"
#include "k2000/misc/FloatApproach.h"
#include "k2000/ai/CKSrvPathFinding.h"
#include "Renderware/rwcore/RwMatrix.h"

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

namespace {
float ModelWordAsFloat(uint32_t word) {
    float value;
    std::memcpy(&value, &word, sizeof value);
    return value;
}
uint32_t ModelFloatAsWord(float value) {
    uint32_t word;
    std::memcpy(&word, &value, sizeof word);
    return word;
}
}  // namespace

// 0x00359388 CKHkS08Hero_UpdateModelOffsetAndBank_maybe (UpdateMovement of a hero out of its locomotion or locked to
// an object): nothing while +0x358 bit 2 or +0x35c bit 11 is set. The model node (+0x1c) back to the identity at the
// position (+0x54c), plus while +0x358 bit 19 (without bit 30) the offset +0x468, which shrinks by +0x28c a second (bit
// 19 cleared with it at 0). Then either (+0x360 bit 9 clear) the pitch +0x594 approaches +-+0x343 (by the move's
// direction +0x58c, when the speed mode +0x588 turns the animation and +0x35c bit 20 is clear) at +0x336 a second and
// turns the node about x, the bank +0x598 approaches the turn rate's share of +0x344 at +0x338 a second and turns it
// about z, and the heading (+0x538) turns it about y; or the node's up axis (the one before the identity) turns toward
// +0x798 by +0x230 degrees a second and the basis is built from it and the direction +0x540.
void CKHkS08Hero::UpdateModelOffsetAndBank(IKTime* clock) {
    if ((m_ui32HeroFlags358 & 4u) != 0 || (m_ui32HeroFlags35C & 0x800u) != 0) return;
    CSGMovable* node = static_cast<CSGMovable*>(m_pKGLObject);
    const float upX = node->m_pRwFrame->modelling.up.x;
    const float upY = node->m_pRwFrame->modelling.up.y;
    const float upZ = node->m_pRwFrame->modelling.up.z;
    node->SetIdentity();  // 0x000d08f0
    if ((m_ui32HeroFlags358 & 0x80000u) == 0 || (m_ui32HeroFlags358 & 0x40000000u) != 0) {
        RwFrame* frame = node->m_pRwFrame;
        frame->modelling.pos.z = m_unk554;
        frame->modelling.pos.x = m_unk54c;
        frame->modelling.pos.y = m_unk550;
        frame->modelling.flags &= 0xfffdffffu;
        c22spyro::RwFrameMarkDirty(node->m_pRwFrame);  // 0x00010698
        m_ui32HeroFlags358 &= 0xfff7ffffu;
    } else {
        const float length =
            std::sqrt(ppc::fmadds(m_unk470, m_unk470, ppc::fmadds(m_unk468, m_unk468, m_unk46c * m_unk46c)));  // 0x10690
        const float step = m_unk28c * clock->m_afDeltaTime[0];
        if (length > step) {
            const float scale = (1.0f / length) * (length - step);  // TOC1 +0x2c3c
            m_unk470 = scale * m_unk470;
            m_unk468 = scale * m_unk468;
            m_unk46c = scale * m_unk46c;
        } else {
            m_unk468 = kHeroZeroVector.x;  // 0x00c50d64 (TOC1 +0x2c44)
            m_unk46c = kHeroZeroVector.y;
            m_unk470 = kHeroZeroVector.z;
            m_ui32HeroFlags358 &= 0xfff7ffffu;
        }
        RwFrame* frame = node->m_pRwFrame;
        frame->modelling.pos.x = m_unk54c + m_unk468;
        frame->modelling.pos.y = m_unk550 + m_unk46c;
        frame->modelling.pos.z = m_unk554 + m_unk470;
        frame->modelling.flags &= 0xfffdffffu;
        c22spyro::RwFrameMarkDirty(node->m_pRwFrame);
    }
    const float dt = clock->m_afDeltaTime[0];
    if ((m_ui32HeroFlags360 & 0x200u) == 0) {
        static const float kAxisX[3] = {1.0f, 0.0f, 0.0f};  // 0x00c50d34 (TOC1 +0x2cd0; a static initialiser's)
        static const float kAxisY[3] = {0.0f, 1.0f, 0.0f};  // 0x00c50d40 (TOC1 +0x2c48)
        static const float kAxisZ[3] = {0.0f, 0.0f, 1.0f};  // 0x00c50d4c (TOC1 +0x2cd8)
        const float kHalfPi = 1.5707964f;                   // TOC1 +0x2c64
        float pitchTarget = 0.0f;                           // TOC1 +0x2c24
        if ((m_ui32HeroFlags35C & 0x100000u) == 0 &&
            m_asSpeedModes[m_unk588].m_abAnimMustBeTurned[static_cast<int32_t>(m_unk58c)] != 0) {
            pitchTarget = m_unk58c == 1 ? static_cast<float>(m_unk343) : -static_cast<float>(m_unk343);
        }
        float pitch = ModelWordAsFloat(m_unk594);
        if (pitch != pitchTarget) {
            float approach[3] = {pitchTarget, static_cast<float>(m_unk336), pitch};
            FloatApproach_Step(dt, approach);  // 0x002436e8
            pitch = approach[2];
            m_unk594 = ModelFloatAsWord(pitch);
        }
        if (pitch != 0.0f) node->RotateInPlace(kAxisX, pitch);  // 0x000d11b0
        float bankTarget = 0.0f;
        if (m_aui8Unk1a4[8] != 0 && (m_ui32HeroFlags360 & 0x10000000u) == 0 && m_fCurHSpeed != 0.0f && (m_ui32HeroFlags354 & 1u) == 0 &&
            (m_ui32HeroFlags358 & 0x400u) == 0) {
            const CVector3 facing = {m_unk3b8, m_unk3bc, m_unk3c0};
            const float turn = Math_WrapAngleToPi(m_unk538 - Vec3_GetYawAngleFromX(&facing));  // 0x00244638, 0x00582c18
            float rate = std::fabs(turn) / (dt * kHalfPi);
            if (!(rate <= 1.0f)) rate = 1.0f;  // ble (TOC1 +0x2c3c)
            float speed = m_fCurHSpeed;
            if (!(m_unk21c >= m_fCurHSpeed)) speed = m_unk21c;  // bge
            float sign = 1.0f;
            if (!(turn < 0.0f)) sign = -1.0f;  // blt (TOC1 +0x2cd4)
            bankTarget = rate * (speed / m_unk21c) * (sign * static_cast<float>(m_unk344));
        }
        float bank = ModelWordAsFloat(m_unk598);
        if (bank != bankTarget) {
            float approach[3] = {bankTarget, static_cast<float>(m_unk338), bank};
            FloatApproach_Step(dt, approach);
            bank = approach[2];
            m_unk598 = ModelFloatAsWord(bank);
        }
        if (bank != 0.0f) node->RotateInPlace(kAxisZ, bank);
        node->RotateInPlace(kAxisY, (kHalfPi - m_unk538) * 57.29578f);  // TOC1 +0x2cdc
        return;
    }
    const float targetX = m_unk798;
    const float targetY = m_unk79c;
    const float targetZ = m_unk7a0;
    CVector3 up = {upX, upY, upZ};
    if (!(upX == targetX && upY == targetY && upZ == targetZ)) {
        const float dy = targetY - upY;
        const float dx = targetX - upX;
        const float dz = targetZ - upZ;
        const float stepLength = dt * (m_unk230 * ModelWordAsFloat(0x3c8efa34u));  // TOC1 +0x2cc4: degrees to radians, one ulp low
        const float distance2 = ppc::fmadds(dz, dz, ppc::fmadds(dx, dx, dy * dy));
        if (stepLength * stepLength <= distance2) {
            const float k = stepLength * rwInvSqrt(distance2);  // 0x000114d8 Math_InvSqrtf
            up.z = ppc::fmadds(dz, k, upZ);
            up.x = ppc::fmadds(dx, k, upX);
            up.y = ppc::fmadds(dy, k, upY);
        } else {
            up = {targetX, targetY, targetZ};
        }
    }
    const float length = std::sqrt(ppc::fmadds(up.z, up.z, ppc::fmadds(up.x, up.x, up.y * up.y)));  // 0x10690
    if (length != 0.0f) {
        const float inverse = 1.0f / length;
        up.z = up.z * inverse;
        up.x = up.x * inverse;
        up.y = up.y * inverse;
    }
    const CVector3 forward = {m_unk540, m_unk544, m_unk548};
    node->SetBasisFromUpAndForward(&up, &forward);  // 0x000d0a30
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
    if ((m_ui32HeroFlags358 & 0x2000000u) != 0 && (m_ui32HeroFlags354 & 1u) == 0) {
        m_unk6d4 = m_unk564;
        m_unk6dc = m_unk56c;
        m_unk6d8 = m_unk568;
        const float value = ground->m_fPropertieValue;  // +0x40
        m_unk6dc = value * m_unk6dc;
        m_unk6d4 = value * m_unk6d4;
        m_unk6d8 = value * m_unk6d8;
        m_ui32HeroFlags358 = (m_ui32HeroFlags358 & ~0x10000000u) | 0x10000000u;
    }
    CKS08GameManager* manager = static_cast<CKS08GameManager*>(g_pEngine->m_gameManager);
    const uint8_t points = manager->Vf270(m_ui8Hero);  // vt+0x270
    const bool dead = points == 0;                     // (points - 1) < 0
    if ((m_ui32HeroFlags358 & 0x4000000u) != 0 && (m_ui32HeroFlags354 & 1u) == 0 && (m_ui32HeroFlags360 & 0x4000u) == 0 && !dead) {
        if (TeleportToSavedPosition()) {
            m_ui32HeroFlags358 &= ~0x4000000u;
        } else {
            ApplyHazardHitAndLeaveAttach(manager->Vf274(m_ui8Hero), 1);  // vt+0x274
            RequestOwnDragonSelectionIfMultiHero();
        }
    }
    if ((m_ui32HeroFlags360 & 0x2000u) != 0 && (m_ui32HeroFlags354 & 1u) == 0 && (m_ui32HeroFlags360 & 0x8000u) == 0 && !dead) {
        if (TeleportToSavedPosition()) m_ui32HeroFlags360 &= ~0x2000u;
    }
    if ((m_ui32HeroFlags358 & 0x8000000u) != 0 && (m_ui32HeroFlags354 & 1u) == 0 && (m_ui32HeroFlags354 & 0x4000000u) == 0 && (m_ui32HeroFlags35C & 4u) == 0 &&
        !dead) {
        uint8_t damage = manager->Vf270(m_ui8Hero);
        uint8_t kind = 1;
        bool hurt = false;
        if ((m_ui32HeroFlags364 & 0x80u) == 0) {
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
                m_ui32HeroFlags358 &= ~0x8000000u;
            } else {
                ApplyHazardHitAndLeaveAttach(damage, kind);
                RequestOwnDragonSelectionIfMultiHero();
            }
        }
    }
    const uint32_t onGround = (m_ui32HeroFlags364 & 0x80u) != 0 ? ((m_ui32HeroFlags354 & 1u) << 7) : 0u;
    m_ui32HeroFlags364 = (m_ui32HeroFlags364 & ~0x80u) | onGround;
    if (m_ui8TrackedLeader == m_ui8Hero && (m_ui32HeroFlags354 & 4u) != 0 && m_unk300 != 0.0f && (m_ui32HeroFlags360 & 0x2000u) == 0 &&
        (m_ui32HeroFlags358 & 0x4000000u) == 0 && (m_ui32HeroFlags358 & 4u) == 0 && m_unk478 - m_unk550 > m_unk300) {
        // A fall from too high.
        ApplyHazardHitAndLeaveAttach(manager->Vf274(m_ui8Hero), 1);
        m_ui32HeroFlags364 = (m_ui32HeroFlags364 & ~0x2000u) | 0x2000u;
    }
    UpdateGroundSurfaceFlags(clock);  // vt+0x14c 0x002dc660
}

// 0x00354a80 CKHkS08Hero_ApplyHazardHitAndLeaveAttach_maybe: the hit of a hazard ground (or a fall): the attached object
// left (0x344e88), the hero pushed away from the mirror of its saved position +0x474 (mode 0, the position not kept) with
// the push speeds +0x1c8 / +0x1cc / +0x1d0, the two speeds scaled by 1 + (kind - 1) x +0x1ec for a kind above 1; the game
// manager told (vt+0x268 with `damage`, the dragon, 1: empty in CKS08GameManager), +0xf4 and +0xf8 cleared, +0x354 bit 30.
void CKHkS08Hero::ApplyHazardHitAndLeaveAttach(uint8_t damage, uint8_t kind) {
    LeaveAttachedObject();  // 0x00344e88
    float speeds[3] = {m_unk1c8, m_unk1cc, m_unk1d0};
    const float dx = m_unk54c - m_unk474;
    const float dy = m_unk550 - m_unk478;
    const float dz = m_unk554 - m_unk47c;
    const CVector3 source = {dx + m_unk54c, dy + m_unk550, dz + m_unk554};
    if (kind > 1) {
        const int64_t steps = static_cast<int32_t>(kind - 1);  // extsw, fcfid
        const float scale = ppc::fmadds(static_cast<float>(static_cast<double>(steps)), m_unk1ec, 1.0f);  // TOC +0x2c3c
        speeds[1] = speeds[1] * scale;
        speeds[0] = speeds[0] * scale;
    }
    InitMoveRequestFromSourcePoint(speeds, &source, 0, 0);  // 0x0036bbf8
    static_cast<CKS08GameManager*>(g_pEngine->m_gameManager)->Vf268(damage, m_ui8Hero, 1);  // TOC +0x2c40, vt+0x268
    const CVector3& zero = kHeroZeroVector;  // TOC +0x2c44
    m_unkf4 = 0;
    m_unkf8 = zero.x;
    m_unk100 = zero.z;
    m_unkfc = zero.y;
    m_ui32HeroFlags354 = (m_ui32HeroFlags354 & ~0x40000000u) | 0x40000000u;
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
    const uint32_t old354 = m_ui32HeroFlags354;
    const uint32_t step1 = (old354 & 0xfffffff7u) | ((old354 & 1u) << 3);
    m_ui32HeroFlags354 = step1;
    const uint32_t wasOnMovingGround = (step1 >> 2) & 1u;
    m_ui32HeroFlags354 = step1 & 0xfffffffbu;
    const uint32_t* handlers = reinterpret_cast<const uint32_t*>(m_unk528);
    if ((m_ui32HeroFlags358 & 4u) != 0 || (m_ui32HeroFlags35C & 0x800u) != 0) {
        if (m_ui8DynamicCurrentState != 0xff) SwitchState(handlers, m_ui8DynamicCurrentState, 0xff, clock);
        // The position and the flat facing from the attach hot spot's world matrix (group vt+0x16c with 0), the
        // previous position kept (+0x558), the move (+0x5b4) and the speeds (+0x530 flat, +0x534 vertical) from it,
        // then SetPositions, the path-finding position and the move entry.
        CMatrix34 matrix;
        static_cast<CSGHotSpot*>(
            m_apHotSpots[static_cast<int8_t>(static_cast<CKGrpS08Hero*>(m_pGrpHero)->GetHotSpotIndex(m_ui8Hero, 0))])
            ->GetWorldMatrix(&matrix);  // 0x000ce970
        const float kZeroF = 0.0f;  // TOC +0x2c24
        m_unk558 = m_unk54c;
        m_unk55c = m_unk550;
        m_unk54c = matrix.m_pos.x;
        m_unk550 = matrix.m_pos.y;
        m_unk540 = matrix.m_at.x;
        m_unk544 = matrix.m_at.y;
        m_unk544 = kZeroF;
        m_unk560 = m_unk554;
        m_unk554 = matrix.m_pos.z;
        m_unk548 = matrix.m_at.z;
        const float facing = static_cast<float>(
            c22spyro::MathSqrtf(ppc::fmadds(m_unk548, m_unk548, ppc::fmadds(m_unk540, m_unk540, m_unk544 * m_unk544))));
        if (facing != kZeroF) {
            const float inverse = 1.0f / facing;  // TOC +0x2c3c
            m_unk548 = inverse * m_unk548;
            m_unk540 = inverse * m_unk540;
            m_unk544 = inverse * m_unk544;
        }
        const float dx = m_unk54c - m_unk558;
        const float dz = m_unk554 - m_unk560;
        const float dy = m_unk550 - m_unk55c;
        m_unk5b4 = dx;
        m_unk5bc = dz;
        m_unk5b8 = dy;
        const float dt = clock->m_afDeltaTime[0];
        const float flat = static_cast<float>(c22spyro::MathSqrtf(ppc::fmadds(dz, dz, ppc::fmadds(dx, dx, kZeroF))));
        m_fCurVSpeed = m_unk5b8 / dt;
        float height = m_unk1f0;
        const float step = m_unk510;
        m_fCurHSpeed = flat / dt;
        CVector3 target = {m_unk54c, m_unk550, m_unk554};
        if ((m_ui32HeroFlags354 & 1u) == 0 && !(m_unk204 >= kZeroF)) {
            height = ppc::fmadds(height, (kZeroF - m_unk204) / m_unk204, height);  // a negative +0x204 only (bge), as the original
        }
        m_gcDatasIn.m_fDeltaMax = height;    // +0x4a8
        m_gcDatasIn.m_fObjectHeight = step;  // +0x4ac
        SetPositions(clock, &target);        // 0x0035f6f8
        m_PFCpnt.SetDestination(reinterpret_cast<const CVector3*>(&m_unk54c));  // 0x001e3a40
        m_unk588 = SelectMoveEntryIndexForSpeed(m_fCurHSpeed);  // 0x00369ac8
        return;
    }
    UpdateDynamicGroundAttachment(clock, wasOnMovingGround);  // 0x00360648
    // The slope test (+0x1ad): a ground steeper than +0x349 degrees (or the slide flag +0x1ae with +0x358 bit 24)
    // starts the slide timer (+0x608, +0x354 bit 23).
    bool steep = false;
    if ((m_ui32HeroFlags358 & 0x1000000u) != 0) steep = m_aui8Unk1a4[0x1ae - 0x1a4] != 0;  // +0x1ae
    if (m_aui8Unk1a4[0x1ad - 0x1a4] != 0 && !steep) {  // +0x1ad
        const float cosine = ppc::fmadds(m_unk56c, kHeroAxisY.z, ppc::fmadds(m_unk564, kHeroAxisY.x, m_unk568 * kHeroAxisY.y));  // TOC +0x2c48
        float angle = 0.0f;                                     // TOC +0x2c24
        if (!(cosine >= 1.0f)) angle = crt::Acosf(cosine) * 0x1.ca5dc2p+5f;  // 0x0098e1a0; TOC +0x2cdc (57.29578)
        steep = angle >= static_cast<float>(static_cast<double>(m_unk349));  // cror gt|eq
    }
    if (!steep) {
        m_ui32HeroFlags354 &= 0xff7fffffu;
    } else if ((m_ui32HeroFlags354 & 0x800000u) == 0) {
        m_unk608 = clock->m_afCurrentTime[0];
        m_ui32HeroFlags354 = (m_ui32HeroFlags354 & 0xff7fffffu) | 0x800000u;
    }
    const uint8_t count = static_cast<IKGrpHero*>(m_pGrpHero)->GetNbHeroStatesC();  // vt+0x12c
    uint8_t found = count;
    for (uint32_t row = 0; row < count; ++row) {
        if (CallStateCondition(m_unk520[row].m_aPtmf1, clock, static_cast<uint8_t>(row)) != 0) {
            found = static_cast<uint8_t>(row);
            break;
        }
    }
    if (found != m_ui8DynamicCurrentState) SwitchState(handlers, m_ui8DynamicCurrentState, found, clock);
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
    const float speedBefore = m_fCurHSpeed;
    if ((m_ui32HeroFlags35C & 0x1000u) == 0) RunState(handlers, m_ui8DynamicCurrentState, clock);
    uint32_t started = 0;
    if (speedBefore == 0.0f && m_fCurHSpeed != 0.0f) started = 0x2000u;  // TOC +0x2c24
    m_ui32HeroFlags358 = (m_ui32HeroFlags358 & 0xffffdfffu) | started;
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
    if ((m_ui32HeroFlags35C & 0x80u) != 0) {
        // Moved without collision: the position is the target, the path follows.
        m_unk558 = m_unk54c;
        m_unk560 = m_unk554;
        m_unk55c = m_unk550;
        m_unk554 = target.z;
        m_unk54c = target.x;
        m_unk550 = target.y;
        m_PFCpnt.SetDestination(reinterpret_cast<const CVector3*>(&m_unk54c));  // 0x001e3a40
    } else {
        if (m_aui8Unk1a4[0x1aa - 0x1a4] != 0 && (m_ui32HeroFlags360 & 0x8000000u) == 0 && (m_ui32HeroFlags35C & 0x10000000u) == 0) {
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
        if ((m_ui32HeroFlags354 & 1u) == 0 && m_fCurHSpeed > m_unk204) {
            height = ppc::fmadds(m_unk1f0, (m_fCurHSpeed - m_unk204) / m_unk204, height);
        }
        m_gcDatasIn.m_fDeltaMax = height;      // +0x4a8
        m_gcDatasIn.m_fObjectHeight = step;    // +0x4ac
        SetPositions(clock, &target);          // 0x0035f6f8
    }
    if (m_aui8Unk1a4[0x1b3 - 0x1a4] != 0 && (m_ui32HeroFlags358 & 0x40000000u) == 0 && (m_ui32HeroFlags358 & 0x80000u) == 0 && (m_ui32HeroFlags358 & 0x8000u) == 0) {
        const bool moved = (m_ui32HeroFlags354 & 0x40000u) != 0 || (m_ui32HeroFlags358 & 0x80u) != 0 || m_unk5f0 != zero.x ||
                           m_unk5f4 != zero.y || m_unk5f8 != zero.z || m_unk5fc != zero.x || m_unk600 != zero.y ||
                           m_unk604 != zero.z;
        if (moved) {
            // The node's world position against the target (the model offset, y kept 0), +0x358 bit 19.
            const RwFrame* frame = static_cast<CSGMovable*>(m_pKGLObject)->m_pRwFrame;
            m_unk468 = FrameLtm(frame)->pos.x - target.x;
            m_unk46c = FrameLtm(frame)->pos.y - target.y;
            m_unk46c = 0.0f;
            m_unk470 = FrameLtm(frame)->pos.z - target.z;
            m_ui32HeroFlags358 = (m_ui32HeroFlags358 & 0xfff7ffffu) | 0x80000u;
        }
    }
    m_unk588 = SelectMoveEntryIndexForSpeed(m_fCurHSpeed);  // 0x00369ac8
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
            uint32_t flags = m_ui32HeroFlags354;
            if ((flags & 1u) != 0 && point.y >= m_unk550 + m_gcDatasIn.m_fDeltaMax && ((ground->m_ba16EngineFlags >> 3) & 1) == 0) {
                // An airborne hero the ground came up to: landed.
                if (m_ui8Hero == m_ui8TrackedLeader && (m_ui32HeroFlags35C & 0x400000u) == 0 && (m_ui32HeroFlags358 & 4u) == 0) {
                    static_cast<CKSrvCamera*>(g_pEngine->m_srvCamera)->m_baTemporaryFlags &= ~1u;
                }
                m_ui32HeroFlags354 &= 0xfffffdfeu;
                m_ui32HeroFlags364 &= ~0x400u;
                m_ui32HeroFlags354 &= ~2u;
                m_unk590 = 0xff;
                m_ui32HeroFlags354 = (m_ui32HeroFlags354 & ~6u) | 4u;
                SetDirectionLock(0);  // 0x009bdb48
                flags = m_ui32HeroFlags354;
            }
            if ((flags & 1u) != 0 || (m_ui32HeroFlags35C & 0x100u) != 0) {
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
    m_ui32HeroFlags354 &= 0xfffbffffu;
    m_ui32HeroFlags35C &= 0xfffeffffu;
    const int32_t result = static_cast<int32_t>(m_unk60c);
    // The speed scaled by 1 + 0.01 * (u8)+0x347 * k (k = -1 when blocked or by several walls).
    auto scaleSpeed = [&](float k) {
        const float factor = static_cast<float>(static_cast<double>(m_unk347));  // fcfid + frsp
        m_fCurHSpeed = m_fCurHSpeed * ppc::fmadds(k * factor, -0.00999999978f, 1.0f);  // TOC +0x2c70 / +0x2c3c
    };
    if (result == 1) {
        target->x = m_unk54c;
        target->z = m_unk554;
        move->x = 0.0f;
        move->z = 0.0f;
        const float factor = static_cast<float>(static_cast<double>(m_unk347));
        m_fCurHSpeed = m_fCurHSpeed * ppc::fmadds(factor, -0.00999999978f, 1.0f);
        m_ui32HeroFlags354 |= 0x40000u;
        return;
    }
    if (result < 1 || result > 3) return;
    float lift2 = 0.0f;  // TOC +0x2c24
    const CVector3& bounce = m_wallSlide.m_v3BouncingVector;
    if ((m_ui32HeroFlags354 & 1u) == 0 && (m_ui32HeroFlags358 & 0x400u) == 0) {
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
        m_ui32HeroFlags35C = (m_ui32HeroFlags35C & 0xfffeffffu) | (dot <= 0.0f ? 0x10000u : 0u);
    } else {
        const float factor = static_cast<float>(static_cast<double>(m_unk347));
        m_fCurHSpeed = m_fCurHSpeed * ppc::fmadds(factor, -0.00999999978f, 1.0f);
        m_ui32HeroFlags35C |= 0x10000u;
    }
    m_ui32HeroFlags354 |= 0x40000u;
}

// 0x0035f6f8 SetPositions
void CKHkS08Hero::SetPositions(IKTime* clock, CVector3* target) {
    m_ui32HeroFlags35C &= ~0x40000u;
    m_ui32HeroFlags364 &= ~0x8000u;
    m_ui32HeroFlags360 &= 0xfffffbfdu;
    CopyGroundContact(m_gcOldDatasInOut, m_gcCurDatasInOut);
    CVector3* const position = reinterpret_cast<CVector3*>(&m_unk54c);
    ICollisionMesh* deactivated = nullptr;
    if (!ResolveGroundContactAndPosition(clock, target, position, 0, &deactivated)) {
        const uint32_t firstStatus = m_gcCurDatasInOut.m_eContactStatus;
        if (!ResolveGroundContactAndPosition(clock, target, position, 1, nullptr)) {
            uint32_t falling = 0;  // +0x364 bit 15
            if (firstStatus == 3) {
                m_ui32HeroFlags35C = (m_ui32HeroFlags35C & ~0x40000u) | (m_gcCurDatasInOut.m_eContactStatus == 3 ? 0x40000u : 0u);
            } else {
                m_ui32HeroFlags35C &= ~0x40000u;
                if (firstStatus == 2 && m_gcCurDatasInOut.m_eContactStatus == 2) falling = 0x8000;
            }
            m_ui32HeroFlags364 = (m_ui32HeroFlags364 & ~0x8000u) | falling;
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
    if ((m_ui32HeroFlags354 & 1u) == 0 && (m_ui32HeroFlags35C & 0x400u) == 0) {
        *groundPoint = *position;
        return;
    }
    GroundContact_GetWorldPointOr(&m_gcCurDatasInOut, position, groundPoint);
}

// 0x00354cf0 CKHkS08Hero_SetCameraDirectionLock_maybe
void CKHkS08Hero::SetCameraDirectionLock(uint8_t airborne) {
    if (m_ui8Hero != m_ui8TrackedLeader || (m_ui32HeroFlags35C & 0x400000u) != 0 || (m_ui32HeroFlags358 & 4u) != 0) return;
    CKSrvCamera* camera = static_cast<CKSrvCamera*>(g_pEngine->m_srvCamera);
    if (airborne == 0) {
        if ((m_ui32HeroFlags354 & 1u) != 0) camera->m_baTemporaryFlags &= ~1u;
        return;
    }
    if ((m_ui32HeroFlags354 & 1u) != 0) return;
    static const CVector3 kAxisY = {0.0f, 1.0f, 0.0f};  // 0x00c50d40 (filled by a static initialiser)
    camera->EnableDirectionLock(&kAxisY);  // 0x0012bc98 CKSrvCamera_EnableDirectionLock_maybe
}

namespace {
// The camera's bit 0 of +0x46c cleared when the player's hero is in the air (+0x354 bit 0; the inlined
// CKHkS08Hero_SetCameraDirectionLock_maybe 0x354cf0 with 0, before the bit is cleared).
void ClearCameraLockIfOnGround(CKHkS08Hero* hero) {
    if (hero->m_ui8Hero == hero->m_ui8TrackedLeader && (hero->m_ui32HeroFlags35C & 0x400000u) == 0 && (hero->m_ui32HeroFlags358 & 4u) == 0 &&
        (hero->m_ui32HeroFlags354 & 1u) != 0) {
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
            float speed = m_fCurVSpeed;
            if (speed > 0.0f) speed = 0.0f;
            m_fCurVSpeed = speed;
            if ((m_ui32HeroFlags354 & 1u) == 0) return 0;
            m_ui32HeroFlags354 = (m_ui32HeroFlags354 & ~0x200u) | 0x200u;
            return 0;
        }
        if ((ground->m_ba16EngineFlags & 8) != 0) return 0;
        CVector3 point;
        GroundContact_GetWorldPointOr(&contact, target, &point);
        const float above = point.y - m_unk574;
        const float reach = Vf160() * m_unk278;  // vt+0x160
        target->y = !(reach < above) ? point.y : m_unk574;
        ClearCameraLockIfOnGround(this);
        uint32_t flags = m_ui32HeroFlags354 & 0xfffffdfeu;
        m_ui32HeroFlags354 = flags;
        m_ui32HeroFlags364 &= ~0x400u;
        m_ui32HeroFlags354 &= ~2u;
        m_unk590 = 0xff;
        flags = (m_ui32HeroFlags354 & ~6u) | 4u;
        m_ui32HeroFlags354 = flags;
        if (m_ui8Hero == m_ui8TrackedLeader && (m_ui32HeroFlags35C & 0x400000u) == 0 && (m_ui32HeroFlags358 & 4u) == 0 && (m_ui32HeroFlags354 & 1u) != 0) {
            static_cast<CKSrvCamera*>(g_pEngine->m_srvCamera)->m_baTemporaryFlags &= ~1u;
            flags = m_ui32HeroFlags354;
        }
        m_ui32HeroFlags354 = flags & 0xfffffdfeu;
        m_ui32HeroFlags364 &= ~0x400u;
        m_ui32HeroFlags354 &= ~2u;
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
    if ((m_ui32HeroFlags354 & 0x400u) != 0 && m_gcOldDatasInOut.m_pGround != nullptr && contact.m_pGround != m_gcOldDatasInOut.m_pGround) {
        target->z = previous->z;
        target->x = previous->x;
        return 0;
    }
    if (status == 1) {
        // A ground under the target within m_fDeltaMax: the hero is put on it.
        if ((m_ui32HeroFlags354 & 1u) != 0) {
            if ((Vf150() & ground->m_ui16PropertiesFlags) != 0) {  // vt+0x150
                if (deactivated == nullptr) return 0;
                ground->SetActive(0);
                *deactivated = ground;
                return 0;
            }
            if (((ground->m_ba16EngineFlags >> 3) & 1) != 0) {
                m_fCurVSpeed = 0.0f;
                if ((m_ui32HeroFlags354 & 1u) == 0) return 1;
                m_ui32HeroFlags354 = (m_ui32HeroFlags354 & ~0x200u) | 0x200u;
                return 1;
            }
            if ((m_ui32HeroFlags35C & 0x400u) == 0) {
                SetDirectionLock(0);  // 0x009bdb48
                m_ui32HeroFlags354 = (m_ui32HeroFlags354 & ~6u) | 4u;
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
    if ((m_ui32HeroFlags35C & 0x400u) != 0) return 1;
    if ((m_ui32HeroFlags354 & 1u) != 0) return 1;
    if (contact.m_fdH < m_gcDatasIn.m_fDeltaMax) {
        GroundContact_GetWorldPointOr(&contact, previous, target);
        return 1;
    }
    if (m_aui8Unk1a4[0x1a6 - 0x1a4] == 0 || (m_ui32HeroFlags354 & 0x100u) != 0) {
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
            if (m_aui8Unk1a4[0x1b8 - 0x1a4] != 0 && static_cast<int32_t>(m_ui32HeroFlags35C) >= 0 && (m_ui32HeroFlags354 & 0x800000u) == 0) {
                slide = ((m_ui32HeroFlags354 >> 24) & 1u) ^ 1u;
            }
            uint32_t push = 0;
            if (contact.m_fdH > m_unk2ec || (ground->m_ui16PropertiesFlags & 0x94u) != 0) push = slide;
            const bool place = (m_aui8Unk1a4[0x1b4 - 0x1a4] != 0 && (m_ui32HeroFlags354 & 0x1000000u) == 0) || (push & 0xffu) != 0;
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
                if ((push & 0xffu) != 0) m_ui32HeroFlags360 = (m_ui32HeroFlags360 & ~2u) | 2u;
                m_ui32HeroFlags360 = (m_ui32HeroFlags360 & ~0x400u) | 0x400u;
                return 0;
            }
        }
    }
    Vf178(clock, 0);  // vt+0x178 0x002f8708
    const uint32_t keep = ((m_ui32HeroFlags360 & 0x4000000u) != 0 || (m_ui32HeroFlags35C & 0x10000u) != 0) ? 0x4000000u : 0u;
    m_ui32HeroFlags360 = (m_ui32HeroFlags360 & ~0x4000000u) | keep;
    return 1;
}

// 0x00359c60 CKHkS08Hero_UpdateSignedSlopePitchClass_maybe: the slope under the move (+0x7a4, degrees: the angle between
// the move +0x540 and its projection along the ground normal +0x564, negative going down) and its class (+0x58c: 1 up,
// 2 down) once it reaches +0x348 degrees; 0 / 0 without +0x1a8, in the air (+0x354 bit 0) or bit 22, or standing.
void CKHkS08Hero::UpdateSignedSlopePitchClass() {
    m_unk58c = 0;
    if (m_aui8Unk1a4[0x1a8 - 0x1a4] == 0 || (m_ui32HeroFlags354 & 0x400000u) != 0 || (m_ui32HeroFlags354 & 1u) != 0 || m_fCurHSpeed == 0.0f) {
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
uint8_t CKHkS08Hero::IsLockedToObject() { return static_cast<uint8_t>((m_ui32HeroFlags358 >> 2) & 1u); }

// 0x00361b20 IKHkHero_SetInvulnerable_maybe: +0x35c bit 2.
void CKHkS08Hero::SetInvulnerable(uint8_t invulnerable) {
    m_ui32HeroFlags35C = (m_ui32HeroFlags35C & 0xfffffffbu) | (static_cast<uint32_t>(invulnerable) << 2);
}

// ---- pre-C2.7 gamemgr: the attachment calls of the game manager's hero death state ----

// 0x00362360 CKHkS08Hero_AttachToObject_maybe
uint8_t CKHkS08Hero::AttachToObject(IKSerializable* object, int32_t mode) {
    if (CanAttachTo(object, mode) == 0) return 0;  // vt+0xe0
    LeaveAttachedObject();                         // 0x344e88
    m_unk90 = object;
    m_unk94 = static_cast<uint32_t>(mode);
    m_ui32HeroFlags358 = (m_ui32HeroFlags358 & ~1u) | 1u;
    m_ui32HeroFlags35C &= ~0x20000u;
    OnAttachToObject();  // vt+0x120
    return 1;
}

// 0x0035b058 IKHkHero_PlaceAtHotspotOrPosition_maybe
void CKHkS08Hero::PlaceAtHotspotOrPosition(const float* position, const float* direction) {
    // The hot spot of body part 0 (the group's vt+0x16c, a signed byte index).
    CSGHotSpot* hotSpot = static_cast<CSGHotSpot*>(
        m_apHotSpots[static_cast<int8_t>(static_cast<CKGrpS08Hero*>(m_pGrpHero)->GetHotSpotIndex(m_ui8Hero, 0))]);
    CMatrix34 matrix;  // the 16-byte aligned stack buffer; read only where the original fills it
    float p[3];
    float d[3];
    if (position == nullptr || direction == nullptr) hotSpot->GetWorldMatrix(&matrix);  // 0xce970
    if (position == nullptr) {
        p[0] = matrix.m_pos.x;
        p[1] = matrix.m_pos.y;
        p[2] = matrix.m_pos.z;
    } else {
        p[0] = position[0];
        p[1] = position[1];
        p[2] = position[2];
    }
    if (direction == nullptr) {
        d[0] = matrix.m_at.x;
        d[1] = matrix.m_at.y;
        d[2] = matrix.m_at.z;
    } else {
        d[0] = direction[0];
        d[1] = direction[1];
        d[2] = direction[2];
    }
    m_unk558 = p[0];
    m_unk54c = p[0];
    m_unk550 = p[1];
    m_unk55c = p[1];
    m_unk544 = d[1];
    m_unk544 = 0.0f;
    m_unk554 = p[2];
    m_unk540 = d[0];
    m_unk560 = p[2];
    m_unk548 = d[2];
    const float length = static_cast<float>(
        c22spyro::MathSqrtf(ppc::fmadds(m_unk548, m_unk548, ppc::fmadds(m_unk540, m_unk540, m_unk544 * m_unk544))));
    if (length != 0.0f) {  // TOC +0x2c24; a NaN divides
        const float scale = 1.0f / length;
        m_unk548 = scale * m_unk548;
        m_unk540 = scale * m_unk540;
        m_unk544 = scale * m_unk544;
    }
    const CVector3 facing = {m_unk540, m_unk544, m_unk548};
    m_unk538 = Vec3_GetYawAngleFromX(&facing);  // 0x244638
    m_unk3b8 = m_unk540;
    m_unk3bc = m_unk544;
    m_unk5e4 = 0.0f;  // the zero vector 0x00c50d64
    m_unk3c0 = m_unk548;
    m_unk5e8 = 0.0f;
    m_unk5ec = 0.0f;
    m_unk478 = m_unk550;
}

// 0x003622a8 IKHkHero_SetLockedToObject_maybe
void CKHkS08Hero::SetLockedToObject(uint8_t locked, const float* position, const float* direction) {
    if ((m_ui32HeroFlags358 & 1u) == 0) return;
    if ((m_ui32HeroFlags358 & 4u) != 0 && locked == 0) {
        PlaceAtHotspotOrPosition(position, direction);  // 0x35b058
    } else if (locked != 0) {
        SetCameraDirectionLock(0);  // 0x354cf0
    }
    m_ui32HeroFlags358 = (m_ui32HeroFlags358 & ~4u) | (static_cast<uint32_t>(locked) << 2);
}

// 0x00362010 IKHkHero_SetObjectControlsAnim_maybe
void CKHkS08Hero::SetObjectControlsAnim(uint8_t value) {
    if ((m_ui32HeroFlags358 & 1u) == 0) return;
    m_ui32HeroFlags358 = (m_ui32HeroFlags358 & ~2u) | (static_cast<uint32_t>(value) << 1);
}

// 0x00362050 IKHkHero_SetAttachedMovementEnabled_maybe
void CKHkS08Hero::SetAttachedMovementEnabled(uint8_t enabled) {
    if ((m_ui32HeroFlags358 & 1u) == 0) return;
    if ((m_ui32HeroFlags358 & 8u) != 0 && enabled == 0) m_ui32HeroFlags35C &= ~0xc0u;
    m_ui32HeroFlags358 = (m_ui32HeroFlags358 & ~8u) | (static_cast<uint32_t>(enabled) << 3);
}

// 0x00362150 IKHkHero_SetCollisionDisabledWhileAttached_maybe: the volume count is the hero group's vt+0x100.
void CKHkS08Hero::SetCollisionDisabledWhileAttached(uint8_t disabled) {
    if ((m_ui32HeroFlags358 & 1u) == 0) return;
    if (disabled == 0) {
        RestoreDefaultVolumes();  // 0x352bf8 IKHkHero_CallRestoreDefaultVolumes: vt+0x130
    } else {
        CKSrvCollision* collision = static_cast<CKSrvCollision*>(g_pEngine->m_srvCollision);
        const uint8_t count = static_cast<CKGrpS08Hero*>(m_pGrpHero)->GetNbBoundingVolumes(m_ui8Hero);  // vt+0x100
        for (uint32_t i = 0; i < count; ++i) collision->DisableVolume(static_cast<IKBoundingVolume*>(m_apBoundings[i]));  // 0x1920e8
    }
    m_ui32HeroFlags360 = (m_ui32HeroFlags360 & ~0x10000u) | (static_cast<uint32_t>(disabled) << 16);
}

// 0x00363dc8 IKHkHero_SetFlag360Bit14_IfAttached_maybe
void CKHkS08Hero::SetFlag360Bit14IfAttached(uint8_t value) {
    if ((m_ui32HeroFlags358 & 1u) == 0) return;
    m_ui32HeroFlags360 = (m_ui32HeroFlags360 & ~0x4000u) | (static_cast<uint32_t>(value) << 14);
}

// 0x00363df8 IKHkHero_SetFlag360Bit15_IfAttached_maybe
void CKHkS08Hero::SetFlag360Bit15IfAttached(uint8_t value) {
    if ((m_ui32HeroFlags358 & 1u) == 0) return;
    m_ui32HeroFlags360 = (m_ui32HeroFlags360 & ~0x8000u) | (static_cast<uint32_t>(value) << 15);
}

// 0x00363f98 IKHkHero_SetFlag360Bit8_IfAttached_maybe
void CKHkS08Hero::SetFlag360Bit8IfAttached(uint8_t value) {
    if ((m_ui32HeroFlags358 & 1u) == 0) return;
    m_ui32HeroFlags360 = (m_ui32HeroFlags360 & ~0x100u) | (static_cast<uint32_t>(value) << 8);
}

// 0x00363ee8 IKHkHero_SetFlag35CBit3_IfAttached_maybe
void CKHkS08Hero::SetFlag35CBit3IfAttached(uint8_t value) {
    if ((m_ui32HeroFlags358 & 1u) == 0) return;
    m_ui32HeroFlags35C = (m_ui32HeroFlags35C & ~8u) | (static_cast<uint32_t>(value) << 3);
}

// 0x00363fc8 IKHkHero_SetFlag35CBit21_IfAttached_maybe
void CKHkS08Hero::SetFlag35CBit21IfAttached(uint8_t value) {
    if ((m_ui32HeroFlags358 & 1u) == 0) return;
    m_ui32HeroFlags35C = (m_ui32HeroFlags35C & ~0x200000u) | (static_cast<uint32_t>(value) << 21);
}

// 0x00364020 CKHkS08Hero_WillAnimEndWithin_maybe (C2.8 sequence): the active controller of the animation slot (vt+0x194)
// has an animation and its time wrapped into the duration plus `dt` reaches the duration (Anim_GetDuration's test).
uint8_t CKHkS08Hero::WillAnimEndWithin(float dt) {
    AnimBlendSlot* slot = GetAnimBlendSlot();  // vt+0x194
    const CKAnmKeyFrameController* controller = static_cast<CKAnmKeyFrameController*>(
        static_cast<CKBlenderController*>(slot->m_pController)->m_apControllers[slot->m_unk10]);
    return controller->HasEnded(dt) ? 1 : 0;
}

// 0x00363410 IKHkHero_AdvanceObjectAnimTime_maybe
void CKHkS08Hero::AdvanceObjectAnimTime(float dt) {
    if ((m_ui32HeroFlags358 & 2u) == 0) return;
    m_ui32HeroFlags360 = (m_ui32HeroFlags360 & ~0x800u) | 0x800u;
    AnimBlendSlot* slot = GetAnimBlendSlot();  // vt+0x194
    CKAnmKeyFrameController* controller = static_cast<CKAnmKeyFrameController*>(
        static_cast<CKBlenderController*>(slot->m_pController)->m_apControllers[slot->m_unk10]);
    controller->m_unk50 = dt + controller->m_unk50;  // fadds
}

// 0x003626a0 IKHkHero_SetFloat530_IfAttachedMovementEnabled_maybe: +0x530 while +0x358 bit 3 is set.
void CKHkS08Hero::SetUnk530IfAttachedMovement(float value) {
    if ((m_ui32HeroFlags358 & 8u) == 0) return;
    m_fCurHSpeed = value;
}

// 0x00362688 IKHkHero_SetFloat534_IfAttachedMovementEnabled_maybe: +0x534 while +0x358 bit 3 is set.
void CKHkS08Hero::SetUnk534IfAttachedMovement(float value) {
    if ((m_ui32HeroFlags358 & 8u) == 0) return;
    m_fCurVSpeed = value;
}

// 0x00364608 CKHkS08Hero_DetachFromObject_maybe: an attached hero (+0x358 bit 0) leaves its object: the object's animation
// control (bit 1) dropped, the lock (bit 2) released at the hot spot (IKHkHero_PlaceAtHotspotOrPosition_maybe), the
// attached movement (bit 3, with +0x35c bits 6-7) and +0x364 bit 26 cleared, the attachment bits of +0x358..+0x364
// cleared, the default volumes back (vt+0x130 through IKHkHero_CallRestoreDefaultVolumes 0x352bf8, +0x360 bit 16),
// +0x794 = +0x218, vt+0x124 (OnDetachFromObject), +0x90 / +0x94 cleared and bit 0 last.
void CKHkS08Hero::DetachFromObject() {
    if ((m_ui32HeroFlags358 & 1u) == 0) return;
    m_ui32HeroFlags358 &= 0xfffffffdu;
    if ((m_ui32HeroFlags358 & 1u) != 0) {
        if ((m_ui32HeroFlags358 & 4u) != 0) PlaceAtHotspotOrPosition(nullptr, nullptr);  // 0x0035b058
        m_ui32HeroFlags358 &= 0xfffffffbu;
    }
    if ((m_ui32HeroFlags358 & 1u) != 0) {
        if ((m_ui32HeroFlags358 & 8u) != 0) m_ui32HeroFlags35C &= 0xffffff3fu;
        m_ui32HeroFlags358 &= 0xfffffff7u;
    }
    if ((m_ui32HeroFlags358 & 1u) != 0) m_ui32HeroFlags364 &= 0xfbffffffu;
    m_ui32HeroFlags35C &= 0xffdffff4u;
    m_ui32HeroFlags358 &= 0xdfbfffffu;
    m_ui32HeroFlags35C &= 0xffff7fffu;
    m_ui32HeroFlags360 &= 0xffef3e7fu;
    m_ui32HeroFlags35C &= 0xefffffffu;
    m_ui32HeroFlags364 &= 0xffffefffu;
    if ((m_ui32HeroFlags358 & 1u) != 0) {
        RestoreDefaultVolumes();  // 0x00352bf8 -> vt+0x130
        m_ui32HeroFlags360 &= 0xfffeffffu;
    }
    m_ui32HeroFlags35C &= 0xffffffbfu;
    m_unk794 = m_unk218;
    OnDetachFromObject();  // vt+0x124
    m_unk94 = 0;
    m_unk90 = nullptr;
    m_ui32HeroFlags358 &= 0xfffffffeu;
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
    const uint32_t flags354 = m_ui32HeroFlags354;
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
        const uint32_t flags358 = m_ui32HeroFlags358;
        m_unk790 = clock->m_afCurrentTime[0];
        if ((flags358 & 0x400u) == 0) m_fCurVSpeed = 0.0f;
        m_unk590 = static_cast<uint8_t>(stage);
        SetCameraDirectionLock(1);  // the inlined 0x00354cf0 (airborne is still clear: the camera is told)
        m_ui32HeroFlags354 = (m_ui32HeroFlags354 | 1u) & ~4u;
        return;
    }
    if (airborne || flag != 0) {
        if ((flags354 & 0x800u) != 0 || (m_ui32HeroFlags35C & 2u) != 0 || (flags354 & 0x200u) != 0) return;
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
        if ((m_ui32HeroFlags354 & 1u) == 0) storeStart();
        m_fCurVSpeed = m_asJumps[stage].m_fImpulse;
        m_unk590 = static_cast<uint8_t>(stage);
        if ((m_unk368 & 0x100u) == 0) m_unk790 = -1000.0f;  // TOC1 +0x2c58
        SetCameraDirectionLock(1);
        m_ui32HeroFlags354 = ((m_ui32HeroFlags354 | 1u) & ~6u) | 2u;
        return;
    }
}

// 0x00361c98 IKHkHero_GetFloat218_maybe (step 4 AI): +0x218 (the hero's radius, as AIUpdatePathToTarget adds it).
float CKHkS08Hero::GetFloat218() const { return m_unk218; }

// 0x00361968 CKHkS08Hero_GetPositionPtr
const float* CKHkS08Hero::GetPositionPtr() const {
    if ((m_bitArray & 2u) == 0 || ((m_ui32StatusFlagsED4 >> 4) & 1u) != 0) return &m_unk54c;
    return &FrameLtm(static_cast<const CSGMovable*>(m_pKGLObject)->m_pRwFrame)->pos.x;  // RwFrame +0x80
}

namespace {
// The controller the hero's marks are read on: the active blend slot (vt+0x194) and its active controller (the blender
// +0x04, its +0x50[slot +0x10]).
CKAnmKeyFrameController* MarkWindowController(CKHkS08Hero* hero) {
    AnimBlendSlot* slot = hero->GetAnimBlendSlot();
    return static_cast<CKAnmKeyFrameController*>(
        static_cast<CKBlenderController*>(slot->m_pController)->m_apControllers[slot->m_unk10]);
}
}  // namespace

// 0x00361f40 CKHkS08Hero_GetCurrentAnimResource
RtAnimAnimation* CKHkS08Hero::GetCurrentAnimResource() { return MarkWindowController(this)->m_unk58; }

// 0x00364100 CKHkS08Hero_GetAnimMarkWindow: the time (+0x50) brought into [0, duration) (TOC +0x2d1c 0.0; bge / ble with
// cror: a NaN time stays), then the evaluated time (+0x54). The slot is asked again for each read (vt+0x194).
void CKHkS08Hero::GetAnimMarkWindow(float* from, float* to) {
    float t = MarkWindowController(this)->m_unk50;
    const float duration = MarkWindowController(this)->GetDuration();  // 0x0007ab60 Anim_GetDuration
    while (t < 0.0f) t = t + duration;
    const float end = duration + 0.0f;
    while (end <= t) t = t - duration;
    *to = t;
    *from = MarkWindowController(this)->m_unk54;
}

// ---- C2.8 meca-hero: the object-driven moves and animations ----

// 0x00364470 IKHkHero_SetMoveDestination_maybe
void CKHkS08Hero::SetMoveDestinationBase(float timeout, const CVector3* position, const CVector3* direction,
                                         uint32_t flag4, uint32_t flag31) {
    if ((m_ui32HeroFlags358 & 8u) == 0 || (m_ui32HeroFlags358 & 4u) != 0) return;
    m_unk398 = position->x;
    m_unk39c = position->y;
    m_unk3a0 = position->z;
    m_unk3a4 = direction->x;
    m_unk3ac = direction->z;
    m_unk3a8 = 0.0f;  // TOC +0x2d1c
    const float length = static_cast<float>(
        c22spyro::MathSqrtf(ppc::fmadds(m_unk3ac, m_unk3ac, ppc::fmadds(m_unk3a4, m_unk3a4, 0.0f))));  // 0x00010690
    if (length != 0.0f) {
        const float inverse = 1.0f / length;  // TOC +0x2d28
        m_unk3ac = inverse * m_unk3ac;
        m_unk3a4 = inverse * m_unk3a4;
        m_unk3a8 = inverse * m_unk3a8;
    }
    m_ui32HeroFlags358 = (m_ui32HeroFlags358 & 0xffffffefu) | ((flag4 & 0xffu) << 4);
    m_ui32HeroFlags360 = (m_ui32HeroFlags360 & 0x7fffffffu) | ((flag31 & 1u) << 31);
    m_unk484 = -1000.0f;  // TOC +0x2d30
    m_unk480 = timeout;
    m_ui32HeroFlags358 = (m_ui32HeroFlags358 & 0xdfffffffu) | 0x20000000u;
    m_ui32HeroFlags35C &= 0xffff7fffu;
}

// 0x00363900 IKHkHero_UpdateMoveTo_maybe: the walk to the destination (AIMoveToTarget, the lost check without a timeout),
// +0x35c bit 6 = arrived (+0x3b0 bit 1 on the ground, within 0.1 of the move with +0x358 bit 19), a timeout teleports
// the hero there when the path finding has a route, `out` = blocked (no route with +0x3b0 bit 9, else +0x3b0 bit 0 when
// standing still).
uint8_t CKHkS08Hero::UpdateMoveToBase(IKTime* clock, uint8_t* out) {
    if ((m_ui32HeroFlags358 & 8u) == 0 || (m_ui32HeroFlags358 & 4u) != 0) return 0;
    CVector3* target = reinterpret_cast<CVector3*>(&m_unk398);
    const CVector3* facing = reinterpret_cast<const CVector3*>(&m_unk3a4);
    const uint8_t lostCheck = m_unk480 == 0.0f ? 1 : 0;
    const uint8_t moved = AIMoveToTarget(clock, target, facing, static_cast<uint8_t>((m_ui32HeroFlags358 >> 4) & 1u),
                                         static_cast<uint8_t>(m_ui32HeroFlags360 >> 31), lostCheck);  // 0x0036dd08
    uint8_t arrived = 0;   // r24
    uint8_t result = 0;    // r27
    uint32_t bit6 = 0;
    if (moved != 0 && (m_unk3b0 & 2u) != 0 && (m_ui32HeroFlags354 & 1u) == 0) {
        arrived = 1;
        result = 1;
        bit6 = 0x40;
        if ((m_ui32HeroFlags358 & 0x80000u) != 0) {
            const float length = static_cast<float>(c22spyro::MathSqrtf(
                ppc::fmadds(m_unk470, m_unk470, ppc::fmadds(m_unk468, m_unk468, m_unk46c * m_unk46c))));
            arrived = length < 0.1f ? 1 : 0;  // TOC +0x2d34
            result = arrived;
            bit6 = static_cast<uint32_t>(result) << 6;
        }
    }
    m_ui32HeroFlags35C = (m_ui32HeroFlags35C & 0xffffffbfu) | bit6;
    CKSrvPathFinding* pathFinding = static_cast<CKSrvPathFinding*>(g_pEngine->m_srvPathFinding);
    if (m_unk480 != 0.0f) {
        float start = m_unk484;
        if (start == -1000.0f) {
            start = clock->m_afCurrentTime[0];
            m_unk484 = start;
        }
        if (start + m_unk480 < clock->m_afCurrentTime[0] &&
            pathFinding->HasSectorRoute(&m_PFCpnt.m_Destination, &m_PFCpnt.m_ptTargetPosition, &m_PFCharacter, nullptr) != 0) {
            TeleportTo(target, facing, 0, 0, 0xffff, 0);  // 0x0036a578
            return 1;
        }
    }
    if (out == nullptr) return result;
    if ((m_unk3b0 & 0x200u) != 0) {
        *out = static_cast<uint8_t>(pathFinding->HasSectorRoute(&m_PFCpnt.m_Destination, &m_PFCpnt.m_ptTargetPosition,
                                                                &m_PFCharacter, nullptr) ^ 1u);  // 0x001e9198
        return result;
    }
    if (arrived == 0 && m_fCurHSpeed == 0.0f && m_fCurVSpeed == 0.0f) {
        *out = static_cast<uint8_t>(m_unk3b0 & 1u);
    } else {
        *out = 0;
    }
    return result;
}

// 0x00362450 CKHkS08Hero_GetCurrentAnimDuration
float CKHkS08Hero::GetCurrentAnimDuration() {
    AnimBlendSlot* slot = GetAnimBlendSlot();  // vt+0x194
    return static_cast<CKAnmKeyFrameController*>(
               static_cast<CKBlenderController*>(slot->m_pController)->m_apControllers[slot->m_unk10])
        ->GetDuration();  // 0x0007ab60
}

// 0x00363378 IKHkHero_SetObjectAnimTime_maybe
void CKHkS08Hero::SetObjectAnimTime(float time) {
    if ((m_ui32HeroFlags358 & 2u) == 0) return;
    m_ui32HeroFlags360 = (m_ui32HeroFlags360 & 0xfffff7ffu) | 0x800u;
    AnimBlendSlot* slot = GetAnimBlendSlot();  // vt+0x194
    static_cast<CKAnmKeyFrameController*>(
        static_cast<CKBlenderController*>(slot->m_pController)->m_apControllers[slot->m_unk10])
        ->m_unk50 = time;
}

// 0x00361fa0 IKHkHero_IsAnimBlendCrossfading_maybe
uint8_t CKHkS08Hero::IsAnimBlendCrossfading() { return GetAnimBlendSlot()->m_unk14 != 0 ? 1 : 0; }

// 0x00362a40 CKHkS08Hero_GetPlayerMoveVectorPtr
const float* CKHkS08Hero::GetPlayerMoveVectorPtr() {
    static const float kNull[3] = {0.0f, 0.0f, 0.0f};  // 0x00c50d64 (TOC +0x2d20)
    if (m_ui8Hero != m_ui8TrackedLeader) return kNull;
    if ((m_ui32HeroFlags358 & 8u) != 0) ReadHeroPlayerInput();  // 0x00369670
    return &m_unk37c;
}

// 0x00362dd0 CKHkS08Hero_GetPlayerInputByte394
uint8_t CKHkS08Hero::GetPlayerInputByte394() {
    if (m_ui8Hero != m_ui8TrackedLeader) return 0;
    if ((m_ui32HeroFlags358 & 8u) != 0) ReadHeroPlayerInput();  // 0x00369670
    return m_unk394;
}

// ---- C2.8 port-all P16: the accessors (IKHkHero.h / CKHkS08Hero.h) ----

// 0x00361a30 IKHkHero_GetPtr3E0_maybe
CPFCharacter* IKHkHero::GetPFCharacter() { return &m_PFCharacter; }
// 0x00361a40 IKHkHero_GetVec3Ptr430_maybe: the path-finding component's destination point (+0x3f0 +0x40).
void* IKHkHero::GetPFDestination() { return &m_PFCpnt.m_Destination; }
// 0x00361a60 IKHkHero_GetVec3Ptr3B8_maybe
float* IKHkHero::GetUnk3B8Ptr() { return &m_unk3b8; }
// 0x00361a90 IKHkHero_GetFlag354Bit0_Word_maybe
uint32_t IKHkHero::GetFlag354Bit0() const { return m_ui32HeroFlags354 & 1u; }
// 0x00361ab0 IKHkHero_GetFlag35CBit8_maybe
uint32_t IKHkHero::GetFlag35CBit8() const { return (m_ui32HeroFlags35C >> 8) & 1u; }
// 0x00361b10 IKHkHero_IsInvulnerable_maybe
uint32_t IKHkHero::IsInvulnerable() const { return (m_ui32HeroFlags35C >> 2) & 1u; }
// 0x00361b50 IKHkHero_GetFlag358Bit8_maybe
uint32_t IKHkHero::GetFlag358Bit8() const { return (m_ui32HeroFlags358 >> 8) & 1u; }
// 0x00361b60 IKHkHero_GetFloat26C_maybe
float IKHkHero::GetUnk26C() const { return m_unk26c; }
// 0x00361c00 CKHkS08Hero_GetFloat510_maybe
float IKHkHero::GetUnk510() const { return m_unk510; }
// 0x00361c10 IKHkHero_GetFloat530_maybe
float IKHkHero::GetUnk530() const { return m_fCurHSpeed; }
// 0x00361ca0 IKHkHero_GetVec3Ptr4A8_maybe
CGroundContactDatasIn* IKHkHero::GetGroundContactIn() { return &m_gcDatasIn; }

// 0x00361cc0 IKHkHero_SetFlag354Bit9_maybe: setting it needs +0x354 bit 0; clearing always.
void IKHkHero::SetFlag354Bit9(uint8_t on) {
    if (on != 0 && (m_ui32HeroFlags354 & 1u) == 0) return;
    m_ui32HeroFlags354 = (m_ui32HeroFlags354 & 0xfffffdffu) | (static_cast<uint32_t>(on) << 9);
}

// 0x00361d98 IKHkHero_SetFlag364Bit5_maybe
void IKHkHero::SetFlag364Bit5() { m_ui32HeroFlags364 = (m_ui32HeroFlags364 & 0xffffffdfu) | 0x20u; }
// 0x00362000 IKHkHero_IsObjectControllingAnim_maybe
uint32_t IKHkHero::IsObjectControllingAnim() const { return (m_ui32HeroFlags358 >> 1) & 1u; }

// 0x00362878 IKHkHero_GetFlag35CBit0_IfAttached_maybe
uint32_t IKHkHero::GetFlag35CBit0IfAttached() const {
    if ((m_ui32HeroFlags358 & 1u) == 0) return 0;
    return m_ui32HeroFlags35C & 1u;
}

// 0x003628e0 IKHkHero_ClearFlag358Bit21_IfAttached_maybe
void IKHkHero::ClearFlag358Bit21IfAttached() {
    if ((m_ui32HeroFlags358 & 1u) == 0) return;
    m_ui32HeroFlags358 &= 0xffdfffffu;
}

// 0x00362fd0 IKHkHero_SetPendingSourceAndVec3_Flag35CBit4_maybe
void IKHkHero::SetPendingSource(IKSerializable* source, const float* point) {
    if (source == nullptr) return;
    m_unkd4 = source;
    if (point != nullptr) {
        m_unkd8 = point[0];
        m_unke0 = point[2];
        m_unkdc = point[1];
    } else {
        m_unkd8 = 0.0f;  // the zero vector 0x00c50d64 (TOC +0x2d20)
        m_unke0 = 0.0f;
        m_unkdc = 0.0f;
    }
    m_ui32HeroFlags35C = (m_ui32HeroFlags35C & 0xffffffefu) | 0x10u;
}

// 0x00363770 IKHkHero_GetLedgeGroundContact_maybe
IKSerializable* IKHkHero::GetLedgeGroundContact() const {
    if ((m_ui32HeroFlags35C & 0x400000u) == 0) return nullptr;
    return m_gcOldDatasInOut2_maybe.m_pGround;  // +0x81c
}

// 0x00363c78 IKHkHero_GetTargetingPositionPtr_maybe
const float* IKHkHero::GetTargetingPositionPtr() {
    if ((m_bitArray & 2u) == 0) return &m_unk570;
    return &FrameLtm(static_cast<CSGMovable*>(m_pKGLObject)->m_pRwFrame)->pos.x;  // frame +0x80
}

// 0x00363ca0 IKHkHero_GetFlag360Bit12_maybe
uint32_t IKHkHero::GetFlag360Bit12() const { return (m_ui32HeroFlags360 >> 12) & 1u; }

// 0x003626f8 CKHkS08Hero_GetPlayerInputFloat38C (TOC +0x2d1c 0.0 for another hero)
float CKHkS08Hero::GetPlayerInputFloat38C() {
    if (m_ui8Hero != m_ui8TrackedLeader) return 0.0f;
    if ((m_ui32HeroFlags358 & 8u) != 0) ReadHeroPlayerInput();  // 0x00369670
    return m_unk38c;
}

// 0x00362c98 CKHkS08Hero_GetPlayerInputFlag358b21
uint32_t CKHkS08Hero::GetPlayerInputFlag358b21() {
    if (m_ui8Hero != m_ui8TrackedLeader) return 0;
    if ((m_ui32HeroFlags358 & 8u) != 0) ReadHeroPlayerInput();
    return (m_ui32HeroFlags358 >> 21) & 1u;
}

// 0x00361ee0 IKHkHero_GetCurrentAnim_maybe: the dictionary word of the active controller's evaluated animation (+0x5c).
uint32_t CKHkS08Hero::GetCurrentAnim() { return MarkWindowController(this)->GetEvaluatedAnimWord(); }
// 0x003638a0 IKHkHero_GetCurrentAnimTime_maybe: the active controller's evaluated time (+0x54).
float CKHkS08Hero::GetCurrentAnimTime() { return MarkWindowController(this)->m_unk54; }

// 0x00362118 CKHkS08Hero_TeleportTo_Thunk
void CKHkS08Hero::TeleportToThunk(const CVector3* position, const CVector3* facing) {
    TeleportTo(position, facing, 0, 0, 0xffff, 0);  // 0x0036a578
}
