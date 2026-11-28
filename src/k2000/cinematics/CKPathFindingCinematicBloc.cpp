// CKPathFindingCinematicBloc.cpp - reconstructed original translation unit 0x1814d0-0x1840f8 (GAME_TOC1, main_toc1), 24 functions, 22 live.
// Primary class: CKPathFindingCinematicBloc  key 0x108  category CinematicNode  size 0x1b0  vtable 0xb1b6a8
// Other owners: DirectionToYawAngle (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x1814d0  CKPathFindingCinematicBloc_Delete
//   [x] 0x181520  CKPathFindingCinematicBloc_ResetRuntime_maybe
//   [ ] 0x1816b8  FUN_001816b8  [dead]
//   [ ] 0x181790  RegisterCKPathFindingCinematicBlocClass
//   [ ] 0x181808  _GLOBAL__I_181808
//   [x] 0x181818  CKPathFindingCinematicBloc_Abort
//   [x] 0x181858  DirectionToYawAngle_maybe  [dead: no pointer to its descriptor 0xb65c88, no call]  (DirectionToYawAngle: YawOf out of line)
//   [x] 0x181948  CKPathFindingCinematicBloc_AdvanceActorAnim_maybe  [dead: no pointer to its descriptor 0xb65c90, no call]  (CKPathFindingCinematicBloc::AdvanceActorAnimBy)
//   [x] 0x181970  CKPathFindingCinematicBloc_SnapActorToGround_maybe  [dead: no pointer to its descriptor 0xb65c98, no call]  (CKPathFindingCinematicBloc::SnapActorToGround)
//   [x] 0x181a70  CKPathFindingCinematicBloc_Stop
//   [ ] 0x181c50  CKPathFindingCinematicBloc_Save
//   [x] 0x181c78  CKPathFindingCinematicBloc_RecursiveRegistration
//   [x] 0x181d08  CKPathFindingCinematicBloc_DeleteArray
//   [x] 0x181db0  CKPathFindingCinematicBloc_Destroy  (empty: the default)
//   [x] 0x181db8  CKPathFindingCinematicBloc_Create
//   [x] 0x181f20  CKPathFindingCinematicBloc_Load
//   [x] 0x1821c0  CKPathFindingCinematicBloc_CreateArray
//   [x] 0x1823c8  CKPathFindingCinematicBloc_TurnActorToTargetYaw_maybe
//   [x] 0x182580  CKPathFindingCinematicBloc_Complete
//   [ ] 0x182778  CKPathFindingCinematicBloc_ApplyPathSample_maybe  [dead]
//   [x] 0x182e40  CKPathFindingCinematicBloc_ComputeTargetHeading_maybe
//   [x] 0x183240  CKPathFindingCinematicBloc_Start
//   [x] 0x183940  CKPathFindingCinematicBloc_MoveActorAlongPath_maybe
//   [x] 0x183f58  CKPathFindingCinematicBloc_Update
//
//   [ ] 0x9a9b38  CKPathFindingCinematicBloc_IsKindOfClass  [inline]
//   [ ] 0x9a9b70  CKPathFindingCinematicBloc_GetClassType  [inline]
//   [ ] 0x9a9b78  CKPathFindingCinematicBloc_GetClassID  [inline]
//   [x] 0x9a9b80  CKPathFindingCinematicBloc_UsesActor_maybe  [inline]
//   [x] 0x9a9b88  CKPathFindingCinematicBloc_IsExclusiveOnActor_maybe  [inline]
//   [x] 0x9a9b90  CKPathFindingCinematicBloc_GetAnimCount_maybe  [inline]
//   [x] 0x9a9b98  CKPathFindingCinematicBloc_GetAnimIndex_maybe  [inline]
//   [ ] 0x9a9ba8  CKPathFindingCinematicBloc_DeletingDestructor  [inline]
//   [ ] 0x9a9c18  CKPathFindingCinematicBloc_Destructor  [inline]
#include "k2000/cinematics/CKPathFindingCinematicBloc.h"
#include "k2000/logic/CKSavingManager.h"

#include "k2000/io/IKFile.h"

#include <cmath>
#include <cstring>

#include "Renderware/rwcore/RwCamera.h"
#include "crt/ppc_ops.h"
#include "crt/xatanf.h"
#include "crt/xsinf.h"
#include "k2000/core/Stub.h"
#include "k2000/hooks/IKHook.h"
#include "k2000/logic/CKCinematicScene.h"
#include "k2000/logic/CKCinematicSceneData.h"
#include "k2000/misc/Engine.h"
#include "k2000/misc/FloatApproach.h"
#include "k2000/scenegraph/CSGMovable.h"
#include "k2000/services/CKSrvBeacon.h"
#include "k2000/services/CKSrvCollision.h"
#include "k2000/hooks/GroundContact.h"
#include "k2000/system/IKTime.h"

namespace {
const CVector3 kVectorZero = {0.0f, 0.0f, 0.0f};  // 0x00c50d64
}  // namespace

// 0x00181db8 CKPathFindingCinematicBloc_Create (the constructor inlined; m_PathFindingCpnt's constructor
// writes the same words as the inlined copy)
CKPathFindingCinematicBloc::CKPathFindingCinematicBloc() {
    m_baFinalPos[0] = 0xffff;
    m_baFinalPos[3] = 0xffff;
    m_baFinalPos[1] = 0xffff;
    m_baFinalPos[2] = 0xffff;
    m_SrvPFCharacter.m_bits = 0;
    m_SrvPFCharacter.m_bits = (((m_SrvPFCharacter.m_bits & ~7u) | 7u) & ~0x7f8u) | 0x400u;  // 0x407
    m_SrvPFCharacter.m_fMaxStepRise = 1.0f;
    m_SrvPFCharacter.m_fMaxStepHeight = 0x1.99999ap-3f;  // 0.2 (TOC 0xc12a3c)
    m_SrvPFCharacter.m_fRadius = g_pfGridScale.m_halfCellSize * 0x1.99999ap-3f;
    m_StartPos.m_i16GraphNodeIndex = 0xffff;
    m_Target.m_i16GraphNodeIndex = 0xffff;
    m_DatasIn.m_MasksOfGrdForTest[0] = 1;
    m_DatasIn.m_MasksOfGrdForTest[1] = 8;
    m_DatasInOut.m_ui8SectorNumber = 0;
    m_DatasInOut.m_i32FaceIndex = -1;
    m_DatasInOut.m_eContactStatus = 3;
    m_DatasInOut.m_pGround = nullptr;
}

// 0x00181520 CKPathFindingCinematicBloc_ResetRuntime_maybe
void CKPathFindingCinematicBloc::ResetRuntime() {
    m_DatasInOut.m_pGround = nullptr;
    m_DatasInOut.m_ui8SectorNumber = 0;
    m_DatasInOut.m_i32FaceIndex = -1;
    m_DatasInOut.m_eContactStatus = 3;
    m_v3StartPos.x = kVectorZero.x;
    m_v3StartPos.z = kVectorZero.z;
    m_v3StartPos.y = kVectorZero.y;
    m_v3CurrentPos.x = kVectorZero.x;
    m_v3CurrentPos.z = kVectorZero.z;
    m_v3CurrentPos.y = kVectorZero.y;
    m_v3Speed.x = kVectorZero.x;
    m_v3Speed.z = kVectorZero.z;
    m_v3Speed.y = kVectorZero.y;
    m_SrvPFCharacter.m_fRadius = 0x1.99999ap-4f;  // 0.1 (TOC 0xc12a20)
    m_SrvPFCharacter.m_bits = (((m_SrvPFCharacter.m_bits & ~7u) | 1u) & ~0x7f8u) | 8u;
    m_StartPos.m_position.x = kVectorZero.x;
    m_StartPos.m_position.z = kVectorZero.z;
    m_StartPos.m_position.y = kVectorZero.y;
    m_v3CurrentPath.x = kVectorZero.x;
    m_v3CurrentPath.z = kVectorZero.z;
    m_v3CurrentPath.y = kVectorZero.y;
    m_bitarray = static_cast<uint8_t>(m_bitarray | 8u);  // bit 3 cleared, then set
    uint32_t bits = m_PathFindingCpnt.m_CharacterType.m_bits;
    bits = (bits & ~7u) | 1u;
    bits = (bits & ~0x7f8u) | ((bits & 0x7f8u) | 8u);
    bits = (bits & ~0x800u) | 0x800u;
    m_PathFindingCpnt.m_CharacterType.m_bits = bits;
    const float half = g_pfGridScale.m_halfCellSize;  // 0x00c40260
    // fcmpu half > 0.1: the squared distance capped at 0.01.
    const float squared = half > 0x1.99999ap-4f ? 0x1.47ae16p-7f /* 0x3c23d70b */ : half * half;
    m_PathFindingCpnt.m_CharacterType.m_fRadius = 0x1.99999ap-4f;  // 0.1 (+0x108)
    m_PathFindingCpnt.m_fPointValidationDistanceSquared = squared;
    m_aUnk80[0] = 0;
    m_aUnk80[1] = 0;
    m_aUnk80[2] = 0;
    m_DatasIn.m_fObjectHeight = 1.2f;  // TOC 0xc12a2c (0x3f99999a)
    m_DatasIn.m_fDeltaMax = 0.5f;      // TOC 0xc12a30
    m_DatasIn.m_MasksOfGrdForTest[0] = 1;
    m_DatasIn.m_MasksOfGrdForTest[1] = 8;
    m_fStartTime = -1.0f;              // TOC 0xc12a34
}

// 0x00181f20 CKPathFindingCinematicBloc_Load
int32_t CKPathFindingCinematicBloc::Load(IKFile* file, int32_t type) {
    BasicLoadCinematicElement(file, type);
    if (type == K_LEVEL_PLATEFORMS) {
        ReadF32LE(file, &m_fSpeed);
        ReadF32LE(file, &m_fRotSpeed);
        ReadF32LE(file, &m_fFinalDist);
        ReadF32LE(file, &m_fTimeBeforeTeleportation);
        ReadU32LE(file, &m_ui32AnimChosen);
        ReadU8(file, &m_bitarray);
        // One 8-byte read, then each half-word swapped (lhbrx).
        uint8_t raw[8];
        ReadRaw(file, raw, 8);
        for (int i = 0; i < 4; ++i) m_baFinalPos[i] = static_cast<uint16_t>(raw[2 * i] | (raw[2 * i + 1] << 8));
        m_PathFindingCpnt.Load(file, K_LEVEL_PLATEFORMS);  // CKPathFindingCpnt_Load, called directly
        ResetRuntime();
    }
    return 1;
}

namespace {

constexpr float kHalfPi = 1.5707963705062866f;    // 0x3fc90fdb
constexpr float kThreeHalfPi = 4.71238899230957f;
constexpr float kPi = 3.1415927410125732f;
constexpr float kTwoPi = 6.2831854820251465f;
constexpr float kDegrees = 57.295780181884766f;   // 180 / pi
const float kAxisY[3] = {0.0f, 1.0f, 0.0f};       // 0x00c50d40
const float kZeroVector[3] = {0.0f, 0.0f, 0.0f};  // 0x00c50d64

// The heading the code makes from a horizontal direction (x, z) in four places (Start, ComputeTargetHeading, MoveActorAlongPath,
// TurnActorToTargetYaw): atan(-z / x), plus pi for a negative x, brought into [0, 2 pi]; a null x gives a quarter turn.
float YawOf(float x, float z) {
    if (x == 0.0f) return z < 0.0f ? kHalfPi : kThreeHalfPi;
    float angle = crt::Atanf(-z / x);
    if (x < 0.0f) angle = angle + kPi;
    if (angle < 0.0f) {
        do {
            angle = angle + kTwoPi;
        } while (angle < 0.0f);
    }
    while (kTwoPi < angle) angle = angle - kTwoPi;
    return angle;
}

CSGMovable* NodeOf(const IKCinematicElement* bloc) {
    return static_cast<CSGMovable*>(static_cast<IKHook*>(static_cast<CKCinematicSceneData*>(bloc->m_pElementData)->m_pHook)->m_pKGLObject);
}

void MarkFrame(RwFrame* frame, uint32_t keepMask) {
    frame->modelling.flags &= keepMask;
    RwFrame_MarkDirty(frame);
}

}  // namespace

// 0x00183240 CKPathFindingCinematicBloc_Start
void CKPathFindingCinematicBloc::Start() {
    StartCommon();
    m_DatasInOut.m_pGround = nullptr;
    m_DatasInOut.m_ui8SectorNumber = 0;
    m_DatasInOut.m_i32FaceIndex = -1;
    m_DatasInOut.m_eContactStatus = 3;
    CKCinematicSceneData* data = static_cast<CKCinematicSceneData*>(m_pElementData);
    if (data != nullptr && data->m_pHook != nullptr && static_cast<IKHook*>(data->m_pHook)->m_pKGLObject != nullptr) {
        CSGMovable* node = NodeOf(this);
        RwFrame* frame = node->m_pRwFrame;
        const RwV3d position = frame->modelling.pos;
        m_v3StartPos.x = position.x;
        m_v3StartPos.z = position.z;
        m_v3StartPos.y = position.y;
        m_v3CurrentPos.x = position.x;
        m_v3CurrentPos.z = position.z;
        m_v3CurrentPos.y = position.y;
        m_v3CurrentPath.x = position.x;
        m_v3CurrentPath.z = position.z;
        m_v3CurrentPath.y = position.y;
        // The final beacon's position (tenths); a sector without klusters is read from the low addresses: zeros here.
        const uint8_t* beacon = static_cast<CKSrvBeacon*>(g_pEngine->m_srvBeacon)->GetBeaconData(m_baFinalPos);
        const int16_t* values = reinterpret_cast<const int16_t*>(beacon);
        m_Target.m_position.x = static_cast<float>(values != nullptr ? values[0] : 0) * 0.1f;
        m_Target.m_position.y = static_cast<float>(values != nullptr ? values[1] : 0) * 0.1f;
        m_Target.m_position.z = static_cast<float>(values != nullptr ? values[2] : 0) * 0.1f;
        m_bitarray = static_cast<uint8_t>(m_bitarray | 8);
        m_StartPos.m_position.x = position.x;
        m_StartPos.m_position.z = position.z;
        m_StartPos.m_position.y = position.y;
        m_aUnk80[1] = 0;
        std::memcpy(&m_aUnk80[1], &m_fRotSpeed, 4);
        const float yaw = YawOf(frame->modelling.at.x, frame->modelling.at.z);
        m_fStartAngle = yaw;
        std::memcpy(&m_aUnk80[2], &yaw, 4);
        std::memcpy(&m_aUnk80[0], &yaw, 4);
        if (m_fBlendingValue == 0.0f) {
            PlayActorAnim(0.0, static_cast<int32_t>(m_ui32AnimChosen));
        } else {
            CrossfadeActorAnim(static_cast<double>(m_fBlendingValue), 0.0, static_cast<int32_t>(m_ui32AnimChosen), 1);
        }
        if (((m_bitarray >> 1) & 1) != 0) {
            ComputeTargetHeading();
            m_bitarray = static_cast<uint8_t>(m_bitarray & 0xfe);
        }
        m_bitarray = static_cast<uint8_t>((m_bitarray & 0xf8) | (m_bitarray & 3));
        // The actor's up vector, normalised.
        const RwV3d up = frame->modelling.up;
        float length = ppc::fmadds(up.z, up.z, ppc::fmadds(up.x, up.x, up.y * up.y));
        length = static_cast<float>(std::sqrt(static_cast<double>(length)));
        m_v3CurrentUp.x = up.x;
        m_v3CurrentUp.y = up.y;
        m_v3CurrentUp.z = up.z;
        if (length != 0.0f) {
            const float inverse = 1.0f / length;
            m_v3CurrentUp.z = inverse * up.z;
            m_v3CurrentUp.x = inverse * up.x;
            m_v3CurrentUp.y = inverse * up.y;
        }
        m_PathFindingCpnt.SetDestination(&m_v3CurrentPos);   // 0x001e3a40
        m_PathFindingCpnt.RequestPathTo(&m_Target.m_position, -1);  // 0x001e1520
        return;
    }
    Complete();  // vt+0x64
}

// 0x00182e40 CKPathFindingCinematicBloc_ComputeTargetHeading_maybe
void CKPathFindingCinematicBloc::ComputeTargetHeading() {
    const uint8_t* beacon = static_cast<CKSrvBeacon*>(g_pEngine->m_srvBeacon)->GetBeaconData(m_baFinalPos);
    const int8_t yawByte = beacon != nullptr ? static_cast<int8_t>(beacon[6]) : static_cast<int8_t>(0);  // BUG(original): low memory without klusters
    const float angle = (static_cast<float>(yawByte) * kPi) * 0.0078125f;
    int32_t angleBits;
    std::memcpy(&angleBits, &angle, 4);
    float sine;
    float cosine;
    if (angleBits < 0) {
        sine = -crt::LibSinf(-angle);
        cosine = crt::LibCosf(-angle);
    } else {
        sine = crt::InlineSinf(angle);
        cosine = crt::InlineCosf(angle);
    }
    const float length = static_cast<float>(std::sqrt(static_cast<double>(ppc::fmadds(cosine, cosine, ppc::fmadds(sine, sine, 0.0f)))));
    if (length != 0.0f) {
        const float inverse = 1.0f / length;
        cosine = cosine * inverse;
        sine = sine * inverse;
    }
    const float yaw = YawOf(sine, cosine);
    std::memcpy(&m_aUnk70[0], &yaw, 4);
}

// 0x001823c8 CKPathFindingCinematicBloc_TurnActorToTargetYaw_maybe. The turn's FloatApproach is +0x74 (target, speed, current).
bool CKPathFindingCinematicBloc::TurnActorToTargetYaw(IKTime* time) {
    float* approach = reinterpret_cast<float*>(&m_aUnk70[1]);
    float* finalYaw = reinterpret_cast<float*>(&m_aUnk70[0]);
    if ((m_bitarray & 1) == 0) {
        std::memcpy(&m_aUnk70[2], &m_fRotSpeed, 4);
        RwFrame* frame = NodeOf(this)->m_pRwFrame;
        const float yaw = YawOf(frame->modelling.at.x, frame->modelling.at.z);
        m_fStartAngle = yaw;
        approach[2] = yaw;
        approach[0] = *finalYaw;
        m_bitarray = static_cast<uint8_t>((m_bitarray & 0xfe) | 1);
    }
    FloatApproach_StepAngle(time->m_afDeltaTime[0], approach);
    if (*finalYaw == approach[2]) return true;
    CSGMovable* node = NodeOf(this);
    node->RotateKeepPosition(kAxisY, (approach[2] + kHalfPi) * kDegrees);
    node->Scale(m_unk2c);
    return false;
}

// 0x00183940 CKPathFindingCinematicBloc_MoveActorAlongPath_maybe
void CKPathFindingCinematicBloc::MoveActorAlongPath(IKTime* time) {
    const float dt = time->m_afDeltaTime[0];
    if ((m_bitarray & 4) == 0) {
        m_PathFindingCpnt.Update(&m_v3CurrentPos);  // 0x001e2b28
        m_CurrentPFState = static_cast<uint32_t>(m_PathFindingCpnt.m_eState);
        if ((m_CurrentPFState & 2) == 0) return;
        CSGMovable* node = NodeOf(this);
        RwFrame* frame = node->m_pRwFrame;
        float waypointX;
        float waypointZ;
        std::memcpy(&waypointX, &m_PathFindingCpnt.m_vCurrentTarget.x, 4);
        std::memcpy(&waypointZ, &m_PathFindingCpnt.m_vCurrentTarget.z, 4);
        m_v3CurrentPath.x = waypointX;
        m_v3CurrentPath.y = m_v3CurrentPos.y;
        m_v3CurrentPath.z = waypointZ;
        float dy = m_v3CurrentPath.y - m_v3CurrentPos.y;
        float dx = waypointX - m_v3CurrentPos.x;
        float dz = waypointZ - m_v3CurrentPos.z;
        float distance = ppc::fmadds(dz, dz, ppc::fmadds(dx, dx, dy * dy));
        distance = static_cast<float>(std::sqrt(static_cast<double>(distance)));
        if (distance != 0.0f) {
            const float inverse = 1.0f / distance;
            dz = dz * inverse;
            dx = dx * inverse;
            dy = dy * inverse;
        }
        if ((m_CurrentPFState & 0x80) == 0 || m_fFinalDist <= distance) {
            // The target yaw to the waypoint, the current one stepped towards it.
            const float heading = YawOf(dx, dz);
            std::memcpy(&m_aUnk80[0], &heading, 4);
            float* approach = reinterpret_cast<float*>(&m_aUnk80[0]);
            FloatApproach_StepAngle(dt, approach);
            const RwV3d at = frame->modelling.at;
            float alignment = ppc::fmadds(dz, at.z, ppc::fmadds(dx, at.x, dy * at.y));
            if (alignment <= 0.0f) alignment = 0.0f;
            m_v3Speed.x = at.x;
            m_v3Speed.y = at.y;
            m_v3Speed.z = at.z;
            const float step = m_fSpeed * dt;
            if (distance >= step) distance = step;
            m_v3Speed.z = alignment * (distance * at.z);
            m_v3Speed.x = alignment * (distance * at.x);
            m_v3Speed.y = alignment * (distance * at.y);
            node->RotateKeepPosition(kAxisY, (approach[2] + kHalfPi) * kDegrees);
            m_v3CurrentPos.x = m_v3CurrentPos.x + m_v3Speed.x;
            m_v3CurrentPos.y = m_v3CurrentPos.y + m_v3Speed.y;
            m_v3CurrentPos.z = m_v3CurrentPos.z + m_v3Speed.z;
            frame->modelling.pos.x = m_v3CurrentPos.x;
            frame->modelling.pos.y = m_v3CurrentPos.y;
            frame->modelling.pos.z = m_v3CurrentPos.z;
            MarkFrame(frame, 0xfffdffffu);
            static_cast<CKSrvCollision*>(g_pEngine->m_srvCollision)->GroundProbePoints(&m_DatasIn, &m_DatasInOut, &m_v3CurrentPos.x, 1);
            if (m_DatasInOut.m_eContactStatus != 3 && m_DatasInOut.m_pGround != nullptr) {
                // The actor stands on the ground found under it.
                GroundContact_GetWorldPoint(reinterpret_cast<const CGroundContactDatasInOut*>(&m_DatasInOut),
                                            &m_v3CurrentPos);
                frame->modelling.pos.x = m_v3CurrentPos.x;
                frame->modelling.pos.y = m_v3CurrentPos.y;
                frame->modelling.pos.z = m_v3CurrentPos.z;
                MarkFrame(frame, 0xfffdffffu);
            }
            frame->modelling.up.x = m_v3CurrentUp.x;
            frame->modelling.up.y = m_v3CurrentUp.y;
            frame->modelling.up.z = m_v3CurrentUp.z;
            MarkFrame(frame, 0xfffdfffcu);
            // The heading made orthogonal to the up vector and normalised.
            const RwV3d heading3 = frame->modelling.at;
            const float along = ppc::fmadds(heading3.z, m_v3CurrentUp.z, ppc::fmadds(heading3.x, m_v3CurrentUp.x, heading3.y * m_v3CurrentUp.y));
            const float removedY = ppc::fmadds(m_v3CurrentUp.y, along, kZeroVector[1]);
            const float removedX = ppc::fmadds(m_v3CurrentUp.x, along, kZeroVector[0]);
            const float removedZ = ppc::fmadds(m_v3CurrentUp.z, along, kZeroVector[2]);
            float oy = heading3.y - removedY;
            float ox = heading3.x - removedX;
            float oz = heading3.z - removedZ;
            float length = ppc::fmadds(oz, oz, ppc::fmadds(ox, ox, oy * oy));
            length = static_cast<float>(std::sqrt(static_cast<double>(length)));
            if (length != 0.0f) {
                const float inverse = 1.0f / length;
                oz = oz * inverse;
                ox = ox * inverse;
                oy = oy * inverse;
            }
            frame->modelling.at.x = ox;
            frame->modelling.at.y = oy;
            frame->modelling.at.z = oz;
            MarkFrame(frame, 0xfffdfffcu);
            node->Scale(m_unk2c);
            return;
        }
        m_bitarray = static_cast<uint8_t>((m_bitarray & 0xfb) | 4);  // arrived
    }
    if (((m_bitarray >> 1) & 1) == 0 || TurnActorToTargetYaw(time)) Complete();  // vt+0x64
}

// 0x00183f58 CKPathFindingCinematicBloc_Update
void CKPathFindingCinematicBloc::Update(IKTime* time) {
    if (CheckSekensStop() == 0) return;
    MoveActorAlongPath(time);
    AdvanceActorAnim(static_cast<double>(time->m_afDeltaTime[0]));
    CKCinematicSceneData* data = static_cast<CKCinematicSceneData*>(m_pElementData);
    float* shadow = reinterpret_cast<float*>(data->m_pShadowData);
    if (shadow == nullptr) return;
    if (((m_bitarray >> 5) & 1) != 0 && m_DatasInOut.m_pGround != nullptr && m_DatasInOut.m_eContactStatus != 3) {
        shadow[3] = m_DatasInOut.m_Normal.x;
        shadow[5] = m_DatasInOut.m_Normal.z;
        shadow[4] = m_DatasInOut.m_Normal.y;
        shadow[0] = m_v3CurrentPos.x;
        shadow[1] = m_v3CurrentPos.y;
        shadow[2] = m_v3CurrentPos.z;
        shadow[6] = m_DatasInOut.m_fdH;
        return;
    }
    shadow[3] = kAxisY[0];
    shadow[5] = kAxisY[2];
    shadow[4] = kAxisY[1];
    shadow[0] = m_v3CurrentPos.x;
    shadow[6] = 0.2f;  // 0x3e4ccccd
    shadow[1] = m_v3CurrentPos.y;
    shadow[2] = m_v3CurrentPos.z;
}

// 0x00182580 CKPathFindingCinematicBloc_Complete: the path request cancelled, then the completion inlined.
void CKPathFindingCinematicBloc::Complete() {
    m_PathFindingCpnt.CancelPathRequest();
    if (((m_bitarray >> 4) & 1) != 0) m_fStartTime = -1.0f;
    CompleteBloc();
}

// 0x00181a70 CKPathFindingCinematicBloc_Stop
void CKPathFindingCinematicBloc::Stop() {
    CompleteBloc();
    Complete();  // vt+0x64
}

// 0x00181818 CKPathFindingCinematicBloc_Abort
void CKPathFindingCinematicBloc::Abort() {
    m_DataFlags &= 0xfffffffeu;
    m_PathFindingCpnt.CancelPathRequest();
}

// 0x00181c78 CKPathFindingCinematicBloc_RecursiveRegistration
void CKPathFindingCinematicBloc::RecursiveRegistration(int32_t type) {
    if (static_cast<uint32_t>(type - 4) > 3u) g_pEngine->m_pSavingManager->RegisterSerializableObject(this, nullptr);
    IKCinematicBloc::RecursiveRegistration(type);  // 0x0018e8d8
}

// 0x00181858 DirectionToYawAngle_maybe: the out-of-line copy of YawOf above for a vector (r3 is not read). Dead in the
// original (no pointer to its descriptor 0xb65c88, no call).
float DirectionToYawAngle(const CVector3* direction) { return YawOf(direction->x, direction->z); }

// 0x00181948 CKPathFindingCinematicBloc_AdvanceActorAnim_maybe: CKCinematicBloc_AdvanceActorAnim 0x18f450 by the time's
// scalable dt (+0x1c), as Update does inline. Dead in the original (no pointer to its descriptor 0xb65c90, no call).
void CKPathFindingCinematicBloc::AdvanceActorAnimBy(IKTime* time) {
    AdvanceActorAnim(static_cast<double>(time->m_afDeltaTime[IKTime::SCALABLE_GAME_TIME]));
}

// 0x00181970 CKPathFindingCinematicBloc_SnapActorToGround_maybe: the ground probe under the actor's position (one point,
// GroundProbePoints_maybe 0x196540); unless the contact's status is 3 or it found no ground, the position becomes the
// ground point (GroundContact_GetWorldPoint) and the actor's frame takes it (the identity bit 17 cleared, marked dirty),
// as MoveActorAlongPath does inline. Dead in the original (no pointer to its descriptor 0xb65c98, no call).
void CKPathFindingCinematicBloc::SnapActorToGround() {
    static_cast<CKSrvCollision*>(g_pEngine->m_srvCollision)->GroundProbePoints(&m_DatasIn, &m_DatasInOut, &m_v3CurrentPos.x, 1);
    if (m_DatasInOut.m_eContactStatus == 3) return;
    if (m_DatasInOut.m_pGround == nullptr) return;
    GroundContact_GetWorldPoint(reinterpret_cast<const CGroundContactDatasInOut*>(&m_DatasInOut), &m_v3CurrentPos);
    RwFrame* frame = NodeOf(this)->m_pRwFrame;
    frame->modelling.pos.z = m_v3CurrentPos.z;
    frame->modelling.pos.x = m_v3CurrentPos.x;
    frame->modelling.pos.y = m_v3CurrentPos.y;
    MarkFrame(frame, 0xfffdffffu);
}
