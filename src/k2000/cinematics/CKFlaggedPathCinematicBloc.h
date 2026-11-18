// CKFlaggedPathCinematicBloc.h - moves an actor along a flagged path (key 0x148, vtable 0xb1b268, size 0x100). Original unit: CKFlaggedPathCinematicBloc.cpp.
// XXL2: the same members (m_v3CurrentPos, m_sv3LookAt, m_sfSpeed, the speeds, the ground contact,
// m_pFlaggedPath, m_fDist, m_AnimStateEngine, m_pTime, m_bPutOnGround and the three arrays) at DotD's
// offsets. The ground-contact blocks are CKSrvCamera's XXL2 types.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/misc/IKCinematicBloc.h"
#include "k2000/cameras/CKSrvCamera.h"
#include "k2000/math/CMatrix34.h"

class IKFile;
class IKTime;

class CKFlaggedPathCinematicBloc : public IKCinematicBloc {
public:
    DOTD_CLASS_KEY(kCategoryCinematic, 0x5)
    DOTD_DECLARE_FACTORIES(CKFlaggedPathCinematicBloc)
    DOTD_BLOC_IS_KIND_OF()

    CKFlaggedPathCinematicBloc();  // 0x001784d0 CKFlaggedPathCinematicBloc_Create (the constructor inlined)
    ~CKFlaggedPathCinematicBloc() override {}

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x00179320 CKFlaggedPathCinematicBloc_Load
    // vt+0x24 0x00178230 CKFlaggedPathCinematicBloc_RecursiveRegistration: registered (unless 4..7), the base's, then the
    // flagged path's.
    void RecursiveRegistration(int32_t type) override;
    // vt+0x10 0x00178828 CKFlaggedPathCinematicBloc_Destroy: the state engine's owner cleared, its table freed
    // (Mem_FreeAligned16) and cleared, its state 0 and +0xcd 0xff.
    void Destroy() override;

    void Start() override;               // vt+0x5c 0x0017a260 CKFlaggedPathCinematicBloc_Start
    void Complete() override;            // vt+0x64 0x00179bf0 CKFlaggedPathCinematicBloc_Complete (CompleteBloc inlined)
    void Update(IKTime* time) override;  // vt+0x68 0x00178ff0 CKFlaggedPathCinematicBloc_Update
    void Stop() override;                // vt+0x6c 0x00178050 CKFlaggedPathCinematicBloc_Stop
    // vt+0x70 0x009a9628 CKFlaggedPathCinematicBloc_Abort [inline]: not running (bit 0 cleared).
    void Abort() override { m_DataFlags &= 0xfffffffeu; }
    uint8_t UsesActor() override { return 1; }            // vt+0x80 0x009a9638
    uint8_t IsExclusiveOnActor() override { return 1; }   // vt+0x84 0x009a9640
    uint8_t GetAnimCount() override { return 3; }         // vt+0x88 0x009a9648
    // vt+0x8c 0x009a9650 CKFlaggedPathCinematicBloc_GetAnimIndex_maybe [inline]: m_i32Tab[index] (the base declares the
    // slot without the index; nothing calls it).
    int32_t GetAnimIndexAt(int32_t index) const { return m_i32Tab[index]; }
    // vt+0x1c 0x00179ff0 CKFlaggedPathCinematicBloc_MessageProc: IKCinematicElement's, then 0x503 the speed's target from
    // m_fSpeedArray[*data], 0x504 its rate from m_fAccelerateArray[*data], 0x502 the state *data (0 handled).
    int32_t MessageProc(uint16_t message, void* data) override;

    // 0x00179dc8 CKFlaggedPathCinematicBloc_RunStateMachine_maybe: the state engine's frame (the current state's handler with
    // mode 0 gives the next state; a change runs the old one's exit (2) and the new one's entry (1)), then the actor's
    // animation advanced. Update inlines it.
    void RunStateMachine();
    // The state engine's handler call: the handler table's word pair at `state` (the PS3 member-function descriptors
    // 0xb640a8 / 0xb64098 / 0xb64090 the Load copied) dispatched to the native handlers.
    uint8_t CallStateHandler(uint8_t state, int32_t mode, uint8_t other);
    // 0x00178740 / 0x00178660 / 0x00178580 CKFlaggedPathCinematicBloc_PathState0/1/2_maybe: the states standing (until
    // m_fTimeForStatique has passed since m_fStatiqueStartTime), walking and running; entry (mode 1) plays the state's
    // animation (m_i32Tab) and sets the speed (0, walk, run); mode 0 returns the state to go on with, mode 2 (exit) 0.
    uint8_t PathState0(int32_t mode, uint8_t other);
    uint8_t PathState1(int32_t mode, uint8_t other);
    uint8_t PathState2(int32_t mode, uint8_t other);
    // 0x00178c80 CKFlaggedPathCinematicBloc_MoveActorAlongPath: the speed approached, the distance advanced (not while
    // standing), the actor placed on the path (on the ground with m_bPutOnGround) and oriented along it (with bit 7 of the
    // flags turned smoothly, StepActorTowards), turned by m_fAngleRotate (bit 8) and scaled back.
    void MoveActorAlongPath();
    // 0x00177e60 CKFlaggedPathCinematicBloc_StepActorTowards_maybe: the look-at vector (+0x44, a CSmoothedCVector3Linear
    // with the rotation speed) stepped towards `direction`, which gets it back normalised.
    void StepActorTowards(CVector3* direction);
    // 0x001789d0 CKFlaggedPathCinematicBloc_UpdateActorGroundContact_maybe: the actor's shadow on the ground under it (or
    // flat at 0.2 under the position without a ground).
    void UpdateActorGroundContact();
    // 0x00177dc8 CKFlaggedPathCinematicBloc_SnapTargetToGround_maybe: the current position put on the ground under it.
    void SnapTargetToGround();

    CVector3 m_v3CurrentPos;                             // +0x38 runtime
    uint32_t m_sv3LookAt[7];                             // +0x44 XXL2 CSmoothedCVector3Linear; runtime
    float m_sfSpeed[3];                                  // +0x60 XXL2 CSmoothedFloat32Linear; 0 in the constructor
    float m_fWalkSpeed;                                  // +0x6c
    float m_fRunSpeed;                                   // +0x70 read first
    float m_fTimeForStatique;                            // +0x74
    float m_fStatiqueStartTime;                          // +0x78 the Load sets -1
    float m_fRotationSpeed;                              // +0x7c
    CKSrvCamera::CGroundContactDatasIn m_DatasIn;        // +0x80 the Load sets 0.5, 1.2, 1, 8
    CKSrvCamera::CGroundContactDatasInOut m_DatasInOut;  // +0x90
    IKSerializable* m_pFlaggedPath;                      // +0xbc CKFlaggedPath
    float m_fDist;                                       // +0xc0 the Load sets 0
    CKFlaggedPathCinematicBloc* m_AnimStateEngineOwner;  // +0xc4 XXL2 CStateEngine m_AnimStateEngine: the owner (the Load sets this)
    uint32_t* m_AnimStateEngineTable;                    // +0xc8 Mem_AllocAligned16(0x18): the state handlers (see the Load)
    uint8_t m_AnimStateEngineState;                      // +0xcc the Load sets 3
    uint8_t m_AnimStateEngineUnkCd;                      // +0xcd 0xff in the constructor
    uint8_t m_padce[2];
    IKSerializable* m_pTime;                             // +0xd0 XXL2 IKTime*; the Load sets 0
    uint8_t m_bPutOnGround;                              // +0xd4
    uint8_t m_padd5[3];
    int32_t m_i32Tab[3];                                 // +0xd8
    float m_fSpeedArray[3];                              // +0xe4
    float m_fAccelerateArray[3];                         // +0xf0
    float m_fAngleRotate;                                // +0xfc
};
DOTD_ASSERT_SIZE(CKFlaggedPathCinematicBloc, 0x100);
DOTD_ASSERT_OFFSET(CKFlaggedPathCinematicBloc, m_v3CurrentPos, +0x38);
DOTD_ASSERT_OFFSET(CKFlaggedPathCinematicBloc, m_sv3LookAt, +0x44);
DOTD_ASSERT_OFFSET(CKFlaggedPathCinematicBloc, m_sfSpeed, +0x60);
DOTD_ASSERT_OFFSET(CKFlaggedPathCinematicBloc, m_fWalkSpeed, +0x6c);
DOTD_ASSERT_OFFSET(CKFlaggedPathCinematicBloc, m_fRunSpeed, +0x70);
DOTD_ASSERT_OFFSET(CKFlaggedPathCinematicBloc, m_fTimeForStatique, +0x74);
DOTD_ASSERT_OFFSET(CKFlaggedPathCinematicBloc, m_fStatiqueStartTime, +0x78);
DOTD_ASSERT_OFFSET(CKFlaggedPathCinematicBloc, m_fRotationSpeed, +0x7c);
DOTD_ASSERT_OFFSET(CKFlaggedPathCinematicBloc, m_DatasIn, +0x80);
DOTD_ASSERT_OFFSET(CKFlaggedPathCinematicBloc, m_DatasInOut, +0x90);
DOTD_ASSERT_OFFSET(CKFlaggedPathCinematicBloc, m_pFlaggedPath, +0xbc);
DOTD_ASSERT_OFFSET(CKFlaggedPathCinematicBloc, m_fDist, +0xc0);
DOTD_ASSERT_OFFSET(CKFlaggedPathCinematicBloc, m_AnimStateEngineOwner, +0xc4);
DOTD_ASSERT_OFFSET(CKFlaggedPathCinematicBloc, m_AnimStateEngineTable, +0xc8);
DOTD_ASSERT_OFFSET(CKFlaggedPathCinematicBloc, m_AnimStateEngineState, +0xcc);
DOTD_ASSERT_OFFSET(CKFlaggedPathCinematicBloc, m_AnimStateEngineUnkCd, +0xcd);
DOTD_ASSERT_OFFSET(CKFlaggedPathCinematicBloc, m_pTime, +0xd0);
DOTD_ASSERT_OFFSET(CKFlaggedPathCinematicBloc, m_bPutOnGround, +0xd4);
DOTD_ASSERT_OFFSET(CKFlaggedPathCinematicBloc, m_i32Tab, +0xd8);
DOTD_ASSERT_OFFSET(CKFlaggedPathCinematicBloc, m_fSpeedArray, +0xe4);
DOTD_ASSERT_OFFSET(CKFlaggedPathCinematicBloc, m_fAccelerateArray, +0xf0);
DOTD_ASSERT_OFFSET(CKFlaggedPathCinematicBloc, m_fAngleRotate, +0xfc);
