// CKPathFindingCinematicBloc.h - moves an actor with the path finding (key 0x108, vtable 0xb1b6a8, size
// 0x1b0). Original unit: CKPathFindingCinematicBloc.cpp. XXL2:
// K/KServices/KServiceCinematic/CinematicElement/CinematicBloc/CKPathFindingCinematicBloc.h; the members
// below follow XXL2's order where the PS3 code matches it (names with _maybe where only the order does).
// DotD embeds a CKPathFindingCpnt at +0xfc. The ground-contact blocks are CKSrvCamera's XXL2 types.
#pragma once
#include <cstdint>

#include "k2000/cameras/CKSrvCamera.h"
#include "k2000/components/CKPathFindingCpnt.h"
#include "k2000/core/Layout.h"
#include "k2000/math/CMatrix34.h"
#include "k2000/misc/IKCinematicBloc.h"

class IKFile;

class CKPathFindingCinematicBloc : public IKCinematicBloc {
public:
    DOTD_CLASS_KEY(kCategoryCinematic, 0x4)
    DOTD_DECLARE_FACTORIES(CKPathFindingCinematicBloc)
    DOTD_BLOC_IS_KIND_OF()

    CKPathFindingCinematicBloc();  // 0x00181db8 CKPathFindingCinematicBloc_Create (the constructor inlined)
    ~CKPathFindingCinematicBloc() override {}

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x00181f20 CKPathFindingCinematicBloc_Load
    // vt+0x24 0x00181c78 CKPathFindingCinematicBloc_RecursiveRegistration: registered with the saving manager (vt+0x24) unless the type is 4..7, then
    // IKCinematicBloc_LevelReset 0x18e8d8 (which registers it once more).
    void RecursiveRegistration(int32_t type) override;

    void ResetRuntime();  // 0x00181520 CKPathFindingCinematicBloc_ResetRuntime_maybe (the Load calls it)

    void Start() override;                 // vt+0x5c 0x00183240 CKPathFindingCinematicBloc_Start
    void Complete() override;              // vt+0x64 0x00182580 CKPathFindingCinematicBloc_Complete
    void Update(IKTime* time) override;    // vt+0x68 0x00183f58 CKPathFindingCinematicBloc_Update
    void Stop() override;                  // vt+0x6c 0x00181a70 CKPathFindingCinematicBloc_Stop
    void Abort() override;                 // vt+0x70 0x00181818 CKPathFindingCinematicBloc_Abort
    uint8_t UsesActor() override { return 1; }              // vt+0x80 0x009a9b80
    uint8_t IsExclusiveOnActor() override { return 1; }     // vt+0x84 0x009a9b88
    uint8_t GetAnimCount() override { return 1; }           // vt+0x88 0x009a9b90
    int32_t GetAnimIndex() override { return static_cast<int32_t>(m_ui32AnimChosen); }  // vt+0x8c 0x009a9b98
    // 0x00182e40 CKPathFindingCinematicBloc_ComputeTargetHeading_maybe: the yaw (+0x70) the actor ends with, from the yaw
    // byte of the final beacon.
    void ComputeTargetHeading();
    // 0x00183940 CKPathFindingCinematicBloc_MoveActorAlongPath_maybe: one frame of the walk: the actor turns towards the
    // next waypoint and steps (at most speed * dt) along its heading; once within the final distance it is "arrived"
    // (bit 2) and, with bit 1, turns to the final yaw before the bloc completes.
    void MoveActorAlongPath(IKTime* time);
    // 0x001823c8 CKPathFindingCinematicBloc_TurnActorToTargetYaw_maybe: one frame of the turn to the final yaw; 1 once there.
    bool TurnActorToTargetYaw(IKTime* time);
    // The out-of-line copies of code Update / MoveActorAlongPath inline (dead in the original):
    void AdvanceActorAnimBy(IKTime* time);  // 0x00181948 CKPathFindingCinematicBloc_AdvanceActorAnim_maybe
    void SnapActorToGround();               // 0x00181970 CKPathFindingCinematicBloc_SnapActorToGround_maybe

    CVector3 m_v3StartPos;              // +0x38 ResetRuntime: (0, 0, 0)
    CVector3 m_v3CurrentPos;            // +0x44 ResetRuntime: (0, 0, 0)
    CVector3 m_v3CurrentUp;             // +0x50 _maybe
    uint32_t m_unk5c;                   // +0x5c
    uint16_t m_baFinalPos[4];           // +0x60 XXL2 CKBeaconAccessor; 0xffff each in the constructor; read
    float m_fFinalDist;                 // +0x68 _maybe (XXL2 order)
    uint32_t m_ui32AnimChosen;          // +0x6c _maybe (XXL2 order)
    uint32_t m_aUnk70[4];               // +0x70 runtime (XXL2 m_fFinalAngle, m_FinalAngle)
    uint32_t m_aUnk80[3];               // +0x80 ResetRuntime: 0 (XXL2 m_Angle _maybe)
    float m_fRotSpeed;                  // +0x8c _maybe (XXL2 order)
    CVector3 m_v3Speed;                 // +0x90 ResetRuntime: (0, 0, 0)
    float m_fSpeed;                     // +0x9c _maybe; read first
    float m_fStartAngle;                // +0xa0 _maybe
    float m_fTimeBeforeTeleportation;   // +0xa4 _maybe
    float m_fStartTime;                 // +0xa8 ResetRuntime: -1
    uint8_t m_ui8CurFramesWait;         // +0xac
    uint8_t m_bitarray;                 // +0xad read; ResetRuntime sets bit 3
    int8_t m_i8SlotNumber;              // +0xae
    uint8_t m_padaf;
    CPFCharacter m_SrvPFCharacter;      // +0xb0
    CPFPoint m_StartPos;                // +0xc0
    CPFPoint m_Target;                  // +0xd0
    CVector3 m_v3CurrentPath;           // +0xe0 ResetRuntime: (0, 0, 0)
    CVector3 m_v3OldPath;               // +0xec
    uint32_t m_CurrentPFState;          // +0xf8
    CKPathFindingCpnt m_PathFindingCpnt;  // +0xfc DotD (vtable 0xb1e4f0)
    CKSrvCamera::CGroundContactDatasIn m_DatasIn;       // +0x174
    CKSrvCamera::CGroundContactDatasInOut m_DatasInOut;  // +0x184
};
DOTD_ASSERT_SIZE(CKPathFindingCinematicBloc, 0x1b0);
DOTD_ASSERT_OFFSET(CKPathFindingCinematicBloc, m_v3StartPos, 0x38);
DOTD_ASSERT_OFFSET(CKPathFindingCinematicBloc, m_baFinalPos, 0x60);
DOTD_ASSERT_OFFSET(CKPathFindingCinematicBloc, m_fFinalDist, 0x68);
DOTD_ASSERT_OFFSET(CKPathFindingCinematicBloc, m_ui32AnimChosen, 0x6c);
DOTD_ASSERT_OFFSET(CKPathFindingCinematicBloc, m_aUnk80, 0x80);
DOTD_ASSERT_OFFSET(CKPathFindingCinematicBloc, m_fRotSpeed, 0x8c);
DOTD_ASSERT_OFFSET(CKPathFindingCinematicBloc, m_v3Speed, 0x90);
DOTD_ASSERT_OFFSET(CKPathFindingCinematicBloc, m_fSpeed, 0x9c);
DOTD_ASSERT_OFFSET(CKPathFindingCinematicBloc, m_fTimeBeforeTeleportation, 0xa4);
DOTD_ASSERT_OFFSET(CKPathFindingCinematicBloc, m_fStartTime, 0xa8);
DOTD_ASSERT_OFFSET(CKPathFindingCinematicBloc, m_bitarray, 0xad);
DOTD_ASSERT_OFFSET(CKPathFindingCinematicBloc, m_SrvPFCharacter, 0xb0);
DOTD_ASSERT_OFFSET(CKPathFindingCinematicBloc, m_StartPos, 0xc0);
DOTD_ASSERT_OFFSET(CKPathFindingCinematicBloc, m_Target, 0xd0);
DOTD_ASSERT_OFFSET(CKPathFindingCinematicBloc, m_v3CurrentPath, 0xe0);
DOTD_ASSERT_OFFSET(CKPathFindingCinematicBloc, m_PathFindingCpnt, 0xfc);
DOTD_ASSERT_OFFSET(CKPathFindingCinematicBloc, m_DatasIn, 0x174);
DOTD_ASSERT_OFFSET(CKPathFindingCinematicBloc, m_DatasInOut, 0x184);

// 0x00181858 DirectionToYawAngle_maybe (dead in the original): the heading of the direction (atan(-z / x) in [0, 2 pi]).
float DirectionToYawAngle(const CVector3* direction);
