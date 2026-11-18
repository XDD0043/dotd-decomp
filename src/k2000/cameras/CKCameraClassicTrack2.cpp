// Reconstructed original translation unit: 0x146de8-0x14f888 (GAME_TOC1, main_toc1), 47 functions, 37 live.
// Primary class: CKCameraClassicTrack2  key 0x307  category Camera  size 0x130  vtable 0xb1a618
// Other owners: CameraTrack (2), CKSrvCamera (1)
//
// No level file holds the class, so nothing replays it: C2.8 port-last Z1 ported it from the disassembly (the earlier
// analysis: work/c28-report-port-R01.json / F01.json).
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x146de8  CKCameraClassicTrack2_Delete  (DOTD_DECLARE_FACTORIES)
//   [x] 0x146e38  CKCameraClassicTrack2_vf54  (Pause, empty)
//   [x] 0x146e40  CKCameraClassicTrack2_vf5C  (Resume, empty)
//   [ ] 0x146e48  CKSrvCamera_GetFirstTrackedHero_maybe  [dead]
//   [ ] 0x146e78  FUN_00146e78  [dead]
//   [ ] 0x146f08  RegisterCKCameraClassicTrack2Class
//   [ ] 0x146f80  _GLOBAL__I_146f80
//   [ ] 0x146f90  CameraTrack_IsSegmentBlocked_maybe  [dead: no pointer to its descriptor 0xb5e170, no call]
//   [x] 0x1470a8  CameraTrack_ClampPositionByCollision_maybe  (CKCameraClassicTrack2::ClampPositionByCollision)
//   [x] 0x147350  CKCameraClassicTrack2_Deactivate_maybe  (Stop, CKCameraClassicTrack2.h)
//   [x] 0x147378  CKCameraClassicTrack2_PostLoad
//   [x] 0x1473f8  CKCameraClassicTrack2_RecursiveRegistration
//   [x] 0x147420  CKCameraClassicTrack2_Destroy
//   [ ] 0x147468  CKCameraClassicTrack2_Construct  [dead: no pointer to its descriptor 0xb5e1a0, no call]
//   [x] 0x1474d8  CKCameraClassicTrack2_DeleteArray  (DOTD_DECLARE_FACTORIES)
//   [ ] 0x147578  CKCameraClassicTrack2_BaseDestructor  [dead: no pointer to its descriptor 0xb5e1b8, no call]
//   [ ] 0x1475a8  CKCameraClassicTrack2_Construct_2  [dead: no pointer to its descriptor 0xb5e1c0, no call]
//   [x] 0x147618  CKCameraClassicTrack2_DeletingDestructor  (the header's destructor + delete)
//   [x] 0x147660  CKCameraClassicTrack2_Destructor  (the header's destructor)
//   [x] 0x147690  CKCameraClassicTrack2_CreateArray  (DOTD_DECLARE_FACTORIES; the constructor)
//   [x] 0x147790  CKCameraClassicTrack2_Create  (DOTD_DECLARE_FACTORIES; the constructor)
//   [x] 0x147818  CKCameraClassicTrack2_Update
//   [x] 0x147a38  CKCameraClassicTrack2_Load
//   [ ] 0x148078  CKCameraClassicTrack2_Save
//   [x] 0x148958  CKCameraClassicTrack2_ComputeFollowPose_maybe
//   [ ] 0x148ca0  FUN_00148ca0  [dead]
//   [x] 0x148f50  CKCameraClassicTrack2_UpdateAxisController_maybe  (AdaptTargetAndCameraCurrentOffset)
//   [x] 0x149470  CKCameraClassicTrack2_ApplyStickRotation_maybe
//   [x] 0x149a00  CKCameraClassicTrack2_UpdateModeSpeedAndAxis_maybe  (UpdateWantedPosition)
//   [x] 0x149c30  CKCameraClassicTrack2_ApplyCoopTargetOffset_maybe
//   [ ] 0x149e18  CKCameraClassicTrack2_GetHeroPosition_maybe  [dead]
//   [ ] 0x149e60  CKCameraClassicTrack2_GetHeroPosition_2_maybe  [dead]
//   [ ] 0x149ea8  CKCameraClassicTrack2_SetClampedDistanceFromPoint_maybe  [dead]
//   [x] 0x14a018  CKCameraClassicTrack2_vf74  (ResolveViewObstructions)
//   [ ] 0x14b2d0  CKCameraClassicTrack2_SetClampedHeightFromPoint_maybe  [dead]
//   [x] 0x14b3f8  CKCameraClassicTrack2_PlaceBehindTarget_maybe
//   [x] 0x14b670  CKCameraClassicTrack2_UpdateAutoRecenter_maybe
//   [ ] 0x14bab8  CKCameraClassicTrack2_SetHeightOffsetFromPoint_maybe  [dead]
//   [ ] 0x14bb40  CKCameraClassicTrack2_GetTargetPosition_maybe  [dead]
//   [x] 0x14bbd8  CKCameraClassicTrack2_InitDistanceAndHeight_maybe  (ForceCurrentOffsetsFromPosition)
//   [x] 0x14be30  CKCameraClassicTrack2_UpdateFollow_maybe
//   [x] 0x14c440  CKCameraClassicTrack2_StateFollow_maybe
//   [x] 0x14c4f8  CKCameraClassicTrack2_ResolveCameraCollision_maybe
//   [ ] 0x14d210  CKCameraClassicTrack2_SearchUnobstructedAngleAlt_maybe  [dead]
//   [x] 0x14ddc8  CKCameraClassicTrack2_SearchUnobstructedAngle_maybe
//   [x] 0x14f030  CKCameraClassicTrack2_ResolveWallCollision_maybe
//   [x] 0x14f278  CKCameraClassicTrack2_Activate_maybe  (Start)
//
//   [x] 0x9a7900  CKCameraClassicTrack2_IsKindOfClass  [inline]  (CKCameraClassicTrack2.h)
//   [x] 0x9a7928  CKCameraClassicTrack2_GetClassType  [inline]  (DOTD_CLASS_KEY)
//   [x] 0x9a7930  CKCameraClassicTrack2_GetClassID  [inline]  (DOTD_CLASS_KEY)
//   [x] 0x9a7938  CKCameraClassicTrack2_vf80  [inline]  (CKCameraClassicTrack2.h)
//   [x] 0x9a7940  CKCameraClassicTrack2_vfB0  [inline]  (CKCameraClassicTrack2.h)
//   [x] 0x9a7948  CKCameraClassicTrack2_vfB4  [inline]  (CKCameraClassicTrack2.h)
#include "k2000/cameras/CKCameraClassicTrack2.h"

#include <cfloat>
#include <cmath>
#include <cstring>

#include "Renderware/rwcore/RwCamera.h"
#include "Renderware/rwcore/RwMatrix.h"
#include "Spyro2008/logic/CKS08GameManager.h"
#include "crt/ppc_ops.h"
#include "crt/xsinf.h"
#include "k2000/cameras/CKSrvCamera.h"
#include "k2000/io/IKFile.h"
#include "k2000/logic/CDefaultGameManager.h"
#include "k2000/hooks/GroundContact.h"
#include "k2000/logic/physics/CGround.h"
#include "k2000/misc/Engine.h"
#include "k2000/misc/FloatApproach.h"
#include "k2000/misc/Mat4.h"
#include "k2000/scenegraph/CSGMovable.h"
#include "k2000/scenegraph/IKBoundingVolume.h"
#include "k2000/services/CKSrvCollision.h"
#include "k2000/services/CollisionDatas.h"
#include "k2000/services/ICollisionMesh.h"

namespace {

// The TOC floats of the unit (TOC1; compared by their bits).
constexpr float kOne = 1.0f;                       // -0x3b7c 0x3f800000
constexpr float kHalf = 0.5f;                      // -0x3be0 0x3f000000
constexpr float kTwo = 2.0f;                       // -0x3b60 0x40000000
constexpr float kMinusTwo = -2.0f;                 // -0x3b64 0xc0000000
constexpr float kMinusOne = -1.0f;                 // -0x3b38 0xbf800000
constexpr float kStartPoseDt = 1000.0f;            // -0x3b34 0x447a0000
constexpr float kPrevNudge = 0x1.4f8b58p-17f;      // -0x3aec 0x3727c5ac (1e-5)
constexpr float kNearFraction = 0x1.2p-1f;         // -0x3af8 0x3f100000 (0.5625 = 0.75^2)
constexpr float kSearchMargin = 0x1.19999ap+0f;    // -0x3af4 0x3f8ccccd (1.1)
constexpr float kTenth = 0x1.99999ap-4f;           // -0x3ba4 0x3dcccccd (0.1)
constexpr float kGroundClearance = 0x1.666666p+1f; // -0x3be4 0x40333333 (2.8)
constexpr float kThousandth = 0x1.0624dep-10f;     // -0x3bdc 0x3a83126f (0.001)
constexpr float kMinusThousandth = -0x1.0624dep-10f;  // -0x3b40 0xba83126f
constexpr float kCoopProjectionScale = 10.0f;      // -0x3b44 0x41200000
constexpr float kStickScale = 255.0f;              // -0x3b70 0x437f0000
constexpr float kFullTurn = 360.0f;                // -0x3b6c 0x43b40000
constexpr float kQuarterPi = 0x1.921fb6p-1f;       // -0x3b18 0x3f490fdb
constexpr float kHalfPi = 0x1.921fb6p+0f;          // -0x3af0 0x3fc90fdb
constexpr float kPi = 0x1.921fb6p+1f;              // -0x3b00 0x40490fdb
// The word at 0x00c4acb8 + 0x28 (FLT_MAX), read through a TOC pointer.
constexpr float kFloatMax = FLT_MAX;

// The shared axes (0x00c50d40 / 0x00c50d4c; filled by static initialisers in the original).
const CVector3 kAxisY = {0.0f, 1.0f, 0.0f};
const CVector3 kAxisZ = {0.0f, 0.0f, 1.0f};
const CVector3 kNullVector = {0.0f, 0.0f, 0.0f};  // 0x00c50d64

// The state table (XXL2 CKCameraClassicTrack2::m_sapUpdateFunc, TOC -0x3ba0 -> 0x00c4b1bc).
const CKCameraClassicTrack2::StateHandler kUpdateStates[1] = {&CKCameraClassicTrack2::StateFollow};

CKSrvCamera* SrvCamera() { return static_cast<CKSrvCamera*>(g_pEngine->m_srvCamera); }           // engine +0x70
CKSrvCollision* SrvCollision() { return static_cast<CKSrvCollision*>(g_pEngine->m_srvCollision); }  // engine +0x58

// 0x00010690 Math_Sqrtf (fsqrts).
inline float Sqrtf(float x) { return std::sqrt(x); }

// The stacked targets' count: the low byte of +0xdf8 (lbz +0xdfb).
uint32_t StackCount(const CKSrvCamera* camera) { return camera->m_ui32NbStacked & 0xffu; }
// The first stacked target (the whole word +0xdf8 tested), else null.
IKSerializable* FirstTarget(const CKSrvCamera* camera) {
    return camera->m_ui32NbStacked != 0 ? camera->m_aStack[0].m_pTarget : nullptr;
}
// The camera's avoiding datas (+0x3cc + 16 * m_ui8CameraAvoidingSystemIndex): [1] the cylinder radius, [2] the probes'
// height above the focus, [3] the cylinder height.
const CKSrvCamera::SCameraAvoidingDatas& AvoidingDatas(const CKSrvCamera* camera, const IKCamera* track) {
    return camera->m_asAvoidingDatas[track->m_ui8CameraAvoidingSystemIndex];
}

// The sign bit cleared (stfs, lwz, rlwinm r0,r0,0,1,31, stw, lfs).
inline float ClearSignBit(float x) {
    uint32_t bits;
    std::memcpy(&bits, &x, 4);
    bits &= 0x7fffffffu;
    std::memcpy(&x, &bits, 4);
    return x;
}

inline bool SignBitSet(float x) {
    int32_t bits;
    std::memcpy(&bits, &x, 4);
    return bits < 0;
}
// The inlined cosf / sinf: the single-precision polynomials for a non-negative argument (by its sign bit), the
// library's cosf 0x009a11d8 / sinf 0x009a1390 of the magnitude otherwise (the sine negated).
inline float GameCosf(float x) { return SignBitSet(x) ? crt::LibCosf(-x) : crt::InlineCosf(x); }
inline float GameSinf(float x) { return SignBitSet(x) ? -crt::LibSinf(-x) : crt::InlineSinf(x); }

// The right stick's axis from the game manager's direction states (vt+0x188 GetDirectionActionState: 0 / 1 the y axis,
// 2 / 3 the x axis), (positive - negative) / 255.
float StickAxis(CKS08GameManager* manager, uint8_t positive, uint8_t negative) {
    const uint8_t a = manager->GetDirectionActionState(positive);
    const uint8_t b = manager->GetDirectionActionState(negative);
    return static_cast<float>(static_cast<double>(static_cast<int32_t>(a) - static_cast<int32_t>(b))) / kStickScale;
}

// 0x0023fba8 Mat4_RotateAboutPoint_maybe (local copy, as CKMeshPopNodeFx.cpp / CKHkS08TuningFork.cpp keep theirs): `m`
// turned by `angle` degrees about `axis` through `point` (the position moved to the point, the identity flag cleared,
// RwMatrixRotate post-concatenated, the position moved back).
void RotateAboutPoint(float angle, CMatrix34* m, const CVector3* point, const CVector3* axis) {
    m->m_pos.x = m->m_pos.x - point->x;
    m->m_pos.y = m->m_pos.y - point->y;
    m->m_pos.z = m->m_pos.z - point->z;
    m->m_ui32Flags = m->m_ui32Flags & 0xfffdffffu;
    RwMatrixRotate(reinterpret_cast<RwMatrix*>(m), reinterpret_cast<const RwV3d*>(axis), angle, rwCOMBINEPOSTCONCAT);
    m->m_pos.x = m->m_pos.x + point->x;
    m->m_pos.y = m->m_pos.y + point->y;
    m->m_pos.z = m->m_pos.z + point->z;
}

// The focus point (the camera service's +0x484), moved toward the second hero in co-op.
CVector3 CoopFocus(CKCameraClassicTrack2* track) {
    CVector3 focus = SrvCamera()->m_v3FocusPos;
    if (StackCount(SrvCamera()) > 1) track->ApplyCoopTargetOffset(&focus);
    return focus;
}

// The camera height's clamp (ForceCurrentOffsetsFromPosition and PlaceBehindTarget inline it): at least the near
// height (position 0), at most the larger of the near / far heights (co-op: positions 4 / 5).
float ClampCameraHeight(const CKCameraClassicTrack2* track, const CKSrvCamera* camera, float height) {
    const float low = track->m_av2CameraOffset[0].m_fY;  // +0x84
    float high;
    if (StackCount(camera) > 1) {
        high = track->m_av2CameraOffset[5].m_fY > track->m_av2CameraOffset[4].m_fY ? track->m_av2CameraOffset[5].m_fY
                                                                                  : track->m_av2CameraOffset[4].m_fY;
    } else {
        high = track->m_av2CameraOffset[2].m_fY > track->m_av2CameraOffset[1].m_fY ? track->m_av2CameraOffset[2].m_fY
                                                                                  : track->m_av2CameraOffset[1].m_fY;
    }
    if (low >= height) return low;
    if (high <= height) return high;
    return height;
}

// The farthest camera distance (the larger of positions 1 / 2, co-op 4 / 5).
float FarDistance(const CKCameraClassicTrack2* track, const CKSrvCamera* camera) {
    if (StackCount(camera) > 1) {
        return track->m_av2CameraOffset[5].m_fX > track->m_av2CameraOffset[4].m_fX ? track->m_av2CameraOffset[5].m_fX
                                                                                   : track->m_av2CameraOffset[4].m_fX;
    }
    return track->m_av2CameraOffset[2].m_fX > track->m_av2CameraOffset[1].m_fX ? track->m_av2CameraOffset[2].m_fX
                                                                               : track->m_av2CameraOffset[1].m_fX;
}

// The height kept over the focus' ground reference near the focus (the end of AdaptTargetAndCameraCurrentOffset and
// of UpdateFollow's move): nearer than the near distance (+0x80) and lower than the focus copy's height over the focus
// (+0x494 - +0x488) + 2.8 (on the line from (0.5, that) to the near offset beyond 0.5): raised to it + 0.001. True
// when raised.
bool RaiseOverGroundReference(CKCameraClassicTrack2* track) {
    const CKSrvCamera* camera = SrvCamera();
    const float distance = track->m_v2CurrentCameraOffset.m_fX;
    const float nearDistance = track->m_av2CameraOffset[0].m_fX;
    if (!(distance < nearDistance)) return false;
    float height = (camera->m_v3FocusPosCopy.y - camera->m_v3FocusPos.y) + kGroundClearance;
    const float current = track->m_v2CurrentCameraOffset.m_fY;
    if (!(height > current)) return false;
    if (!(distance <= kHalf)) {
        const float nearHeight = track->m_av2CameraOffset[0].m_fY;
        const float slope = (height - nearHeight) / (kHalf - nearDistance);
        height = ppc::fmadds(distance, slope, nearHeight - nearDistance * slope);
        if (!(current < height)) return false;
    }
    track->m_v2CurrentCameraOffset.m_fY = height + kThousandth;
    return true;
}

}  // namespace

// 0x00147790 CKCameraClassicTrack2_Create (the constructor inlined)
CKCameraClassicTrack2::CKCameraClassicTrack2() {
    m_ui8NbStates = 0xff;
    m_ui8State = 0xff;
    m_afRecenterApproach[0] = 0.0f;  // TOC -0x3ba8
    m_afRecenterApproach[2] = 0.0f;
    m_afRecenterApproach[1] = 0.0f;
    m_pMatrix = nullptr;
    // The fresh heap's zeroes.
    m_fPlayerCtrl_UpDown_MaxSpeed = 0.0f;
    m_fPlayerCtrl_UpDown_Acceleration = 0.0f;
    m_fPlayerCtrl_Rotation_MaxSpeed = 0.0f;
    m_fPlayerCtrl_Rotation_Acceleration = 0.0f;
    for (float& value : m_afTargetOffsetY) value = 0.0f;
    for (CVector2& value : m_av2CameraOffset) value = CVector2{0.0f, 0.0f};
    m_fTargetOffsetLR = 0.0f;
    m_fTargetOffsetLRSpeed = 0.0f;
    m_fCameraMaxSpeed = 0.0f;
    m_fHeightAboveGround = 0.0f;
    m_fIdleTimeAfterPlayerInput = 0.0f;
    m_fRecenterDelay = 0.0f;
    m_unkC8 = 0.0f;
    m_fCoopDistanceRange = 0.0f;
    m_fCoopMaxOffset = 0.0f;
    m_fCoopBlendDownSpeed = 0.0f;
    m_fCoopBlendUpSpeed = 0.0f;
    m_pStateTable = nullptr;
    m_padE6[0] = 0;
    m_padE6[1] = 0;
    m_fCurrentRotationSpeed = 0.0f;
    m_fCurrentTargetOffsetY = 0.0f;
    m_v2CurrentCameraOffset = CVector2{0.0f, 0.0f};
    m_fCurrentOffsetSpeed = 0.0f;
    m_fCurrentTargetOffsetLR = 0.0f;
    m_v3PreviousTargetedPositionRefForTarget = CVector3{0.0f, 0.0f, 0.0f};
    m_fCurrentIdleTimeLeft = 0.0f;
    m_fRecenterTimer = 0.0f;
    m_fTargetOffsetLRHold = 0.0f;
    m_eCurrentWantedPosition = 0;
    m_fTimeToGoToWantedPosition = 0.0f;
    m_fCoopBlend = 0.0f;
}

// 0x00147a38 CKCameraClassicTrack2_Load
int32_t CKCameraClassicTrack2::Load(IKFile* file, int32_t type) {
    BaseLoad(file, type);  // 0x00144580
    if (type != 0) return 1;
    ReadF32LE(file, &m_fPlayerCtrl_UpDown_MaxSpeed);
    ReadF32LE(file, &m_fPlayerCtrl_UpDown_Acceleration);
    ReadF32LE(file, &m_fPlayerCtrl_Rotation_MaxSpeed);
    ReadF32LE(file, &m_fPlayerCtrl_Rotation_Acceleration);
    ReadU32LEWords(file, reinterpret_cast<uint32_t*>(m_afTargetOffsetY), 6);    // one 0x18 read, swapped
    ReadU32LEWords(file, reinterpret_cast<uint32_t*>(m_av2CameraOffset), 12);   // one 0x30 read, swapped
    ReadF32LE(file, &m_fTargetOffsetLR);
    ReadF32LE(file, &m_fTargetOffsetLRSpeed);
    ReadF32LE(file, &m_fCameraMaxSpeed);
    ReadF32LE(file, &m_fHeightAboveGround);
    ReadF32LE(file, &m_fIdleTimeAfterPlayerInput);
    ReadF32LE(file, &m_fRecenterDelay);
    ReadF32LE(file, &m_unkC8);
    ReadF32LE(file, &m_fCoopDistanceRange);
    ReadF32LE(file, &m_fCoopMaxOffset);
    ReadF32LE(file, &m_fCoopBlendDownSpeed);
    ReadF32LE(file, &m_fCoopBlendUpSpeed);
    return 1;
}

// 0x00147378 CKCameraClassicTrack2_PostLoad
int32_t CKCameraClassicTrack2::PostLoad(int32_t type) {
    IKCamera::PostLoad(type);  // KStub_Return1_144570
    if (type == 0) {
        m_pMatrix = RwMatrixCreate_Thunk();  // 0x0023fa68
        m_pStateTable = kUpdateStates;
        m_ui8State = 0xff;
        m_ui8NbStates = 1;
    }
    return 1;
}

// 0x001473f8 CKCameraClassicTrack2_RecursiveRegistration
void CKCameraClassicTrack2::RecursiveRegistration(int32_t type) {
    IKCamera::RecursiveRegistration(type);  // 0x00144108
}

// 0x00147420 CKCameraClassicTrack2_Destroy
void CKCameraClassicTrack2::Destroy() {
    IKCamera::Destroy();                // 0x00144578 CKCameraTrack_ClearReferences_BaseNop_maybe (empty)
    RwMatrixDestroy_Thunk(m_pMatrix);   // 0x0023f968
    m_pMatrix = nullptr;
}

// 0x00147818 CKCameraClassicTrack2_Update: the state engine (XXL2 TStateEngine<float>::Update) with the frame time.
void CKCameraClassicTrack2::Update(float frameTime) {
    UpdateTrackBase();  // 0x00144398
    float dt = frameTime;  // sp+0xe8: its address is the handlers' argument
    const uint8_t state = m_ui8State;
    if (state == 0xff) return;
    const uint8_t next = (this->*m_pStateTable[state])(&dt, 0, state);
    const uint8_t current = m_ui8State;
    if (next == current) return;
    if (current != 0xff) (this->*m_pStateTable[current])(&dt, 2, next);
    m_ui8State = next;
    if (next != 0xff) (this->*m_pStateTable[next])(&dt, 1, current);
}

// 0x0014c440 CKCameraClassicTrack2_StateFollow_maybe
uint8_t CKCameraClassicTrack2::StateFollow(float* dt, int32_t phase, uint8_t other) {
    if (phase == 1) {
        ComputeFollowPose(kStartPoseDt, m_pMatrix, &m_WorldTarget);  // 0x00148958
        return other;
    }
    if (phase == 2) return other;
    if (phase != 0) return other;
    UpdateFollow(*dt);  // 0x0014be30
    return 0;
}

// 0x00149c30 CKCameraClassicTrack2_ApplyCoopTargetOffset_maybe
void CKCameraClassicTrack2::ApplyCoopTargetOffset(CVector3* point) {
    const float* second = SrvCamera()->m_aStack[1].m_unk24;  // +0xd5c
    float dy = second[1] - point->y;
    float dx = second[0] - point->x;
    float dz = second[2] - point->z;
    float square = ppc::fmadds(dz, dz, ppc::fmadds(dx, dx, dy * dy));
    const float length = Sqrtf(square);
    float half = 0.0f;
    if (length != 0.0f) {
        const float inverse = kOne / length;
        dy = dy * inverse;
        dx = dx * inverse;
        dz = dz * inverse;
        half = length * kHalf;
        square = ppc::fmadds(dz, dz, ppc::fmadds(dx, dx, dy * dy));
    }
    // The matrix's at axis, flat and normalised.
    float atX = m_pMatrix->m_at.x;
    float atZ = m_pMatrix->m_at.z;
    float atY = 0.0f;
    const float flat = Sqrtf(ppc::fmadds(atZ, atZ, ppc::fmadds(atX, atX, 0.0f)));
    if (flat != 0.0f) {
        const float inverse = kOne / flat;
        atZ = atZ * inverse;
        atX = atX * inverse;
        atY = inverse * 0.0f;
    }
    // The direction scaled to half the distance.
    const float again = Sqrtf(square);
    if (again != 0.0f) {
        const float scale = half / again;
        dz = dz * scale;
        dx = dx * scale;
        dy = dy * scale;
    }
    const float along = ppc::fmadds(atZ, dz, ppc::fmadds(atX, dx, atY * dy));
    const float limit = m_fCoopMaxOffset;
    if (along > limit) {
        const float scale = limit / along;
        dz = dz * scale;
        dx = dx * scale;
        dy = dy * scale;
    } else if (-limit > along) {
        // BUG(original): limit / along + 2 (the part along the view becomes limit + 2 * along, not -limit). Kept.
        const float scale = limit / along + kTwo;
        dz = dz * scale;
        dx = dx * scale;
        dy = dy * scale;
    }
    point->x = dx + point->x;
    point->y = dy + point->y;
    point->z = dz + point->z;
}

// 0x00148958 CKCameraClassicTrack2_ComputeFollowPose_maybe
void CKCameraClassicTrack2::ComputeFollowPose(float dt, CMatrix34* m, CVector3* target) {
    CKSrvCamera* camera = SrvCamera();
    IKSerializable* followed = FirstTarget(camera);
    const float dx = target->x - m->m_pos.x;
    const float dy = target->y - m->m_pos.y;
    const float dz = target->z - m->m_pos.z;
    const float distance = Sqrtf(ppc::fmadds(dz, dz, ppc::fmadds(dx, dx, dy * dy)));
    const float keep = m_fCurrentTargetOffsetLR;  // the goal while the lead is held
    CDefaultGameManager* manager = g_pEngine->m_gameManager;  // engine +0x8c
    float goal;
    if ((camera->m_baTemporaryFlags & 0x40000u) == 0 && followed != nullptr &&
        manager->GetFocusedHeroCamera() == followed &&                                   // vt+0x120
        m_v2CurrentCameraOffset.m_fX >= m_av2CameraOffset[0].m_fX - kTenth && (m_Flags & 0x10000u) == 0) {
        // The focused hero is followed from about the near distance: the lead follows its sideways move.
        float hold = m_fTargetOffsetLRHold;
        if (hold > 0.0f) {
            hold = hold - dt;
            m_fTargetOffsetLRHold = hold;
        }
        if (!(hold <= 0.0f)) {
            goal = keep;
        } else if (StackCount(camera) > 1) {
            goal = 0.0f;
        } else {
            const float* move = manager->GetFocusedHeroMoveVector();  // vt+0x130
            float moveX = move[0];
            float moveZ = move[2];
            float moveY = 0.0f;
            const float length = Sqrtf(ppc::fmadds(moveZ, moveZ, ppc::fmadds(moveX, moveX, 0.0f)));
            if (length != 0.0f) {
                const float inverse = kOne / length;
                moveZ = moveZ * inverse;
                moveX = moveX * inverse;
                moveY = inverse * 0.0f;
            }
            const float side =
                ppc::fmadds(moveZ, m->m_right.z, ppc::fmadds(moveX, m->m_right.x, moveY * m->m_right.y));
            float power = side * side;
            power = power * power;
            goal = side < 0.0f ? -m_fTargetOffsetLR * power : power * m_fTargetOffsetLR;
        }
    } else {
        m_fTargetOffsetLRHold = m_fRecenterDelay;
        goal = 0.0f;
    }
    const float current = m_fCurrentTargetOffsetLR;
    if (goal < current) {
        const float next = current - dt * m_fTargetOffsetLRSpeed;
        m_fCurrentTargetOffsetLR = goal > next ? goal : next;
    } else if (goal > current) {
        const float next = ppc::fmadds(dt, m_fTargetOffsetLRSpeed, current);
        m_fCurrentTargetOffsetLR = goal < next ? goal : next;
    }
    float halfWidth;
    float halfHeight;
    GetHalfExtentsAtDistance(distance, &halfWidth, &halfHeight);  // 0x00144278
    const float shift = (m_fCurrentTargetOffsetLR + m_fCurrentTargetOffsetLR) * halfWidth;
    target->z = ppc::fmadds(shift, m->m_right.z, target->z);
    target->x = ppc::fmadds(shift, m->m_right.x, target->x);
    target->y = ppc::fmadds(shift, m->m_right.y, target->y);
}

// 0x00148f50 CKCameraClassicTrack2_UpdateAxisController_maybe
uint8_t CKCameraClassicTrack2::AdaptTargetAndCameraCurrentOffset(float dt, int32_t position, float step,
                                                                  uint32_t flags) {
    const float speed = ClearSignBit(step);
    CKSrvCamera* camera = SrvCamera();
    // BUG(original): in co-op a position outside 0..3 leaves the three registers unset (the callers pass 0..3); 0 here.
    float cameraX = 0.0f;
    float cameraY = 0.0f;
    float targetY = 0.0f;
    if (StackCount(camera) <= 1) {
        cameraX = m_av2CameraOffset[position].m_fX;
        cameraY = m_av2CameraOffset[position].m_fY;
        targetY = m_afTargetOffsetY[position];
    } else {
        IKSerializable* followed = FirstTarget(camera);
        if (position == 1) {
            m_fCoopBlend = 0.0f;
            cameraY = m_av2CameraOffset[5].m_fY;
            cameraX = m_av2CameraOffset[5].m_fX;
            targetY = m_afTargetOffsetY[5];
        } else if (position == 0) {
            cameraY = m_av2CameraOffset[0].m_fY;
            cameraX = m_av2CameraOffset[0].m_fX;
            targetY = m_afTargetOffsetY[0];
            m_fCoopBlend = 0.0f;
        } else if (position == 2 || position == 3) {
            // The co-op blend follows the heroes' distance (the followed node's position to the second target).
            const RwV3d& node = static_cast<CSGMovable*>(followed)->m_pRwFrame->ltm.pos;  // frame +0x80
            const float* second = camera->m_aStack[1].m_unk24;
            const float dy = second[1] - node.y;
            const float dx = second[0] - node.x;
            const float dz = second[2] - node.z;
            const float distance = Sqrtf(ppc::fmadds(dz, dz, ppc::fmadds(dx, dx, dy * dy)));
            float t = (distance == 0.0f ? 0.0f : distance) / m_fCoopDistanceRange;
            if (t <= 0.0f) {
                t = 0.0f;
            } else if (t >= kOne) {
                t = kOne;
            }
            const float blend = m_fCoopBlend;
            if (t > blend) {
                const float next = ppc::fmadds(dt, m_fCoopBlendUpSpeed, blend);
                m_fCoopBlend = next;
                if (t < next) m_fCoopBlend = t;
            } else {
                const float next = blend - dt * m_fCoopBlendDownSpeed;
                m_fCoopBlend = next;
                if (!(t <= next)) m_fCoopBlend = t;
            }
            const float w = m_fCoopBlend;
            const float v = kOne - w;
            cameraX = ppc::fmadds(v, m_av2CameraOffset[4].m_fX, w * m_av2CameraOffset[5].m_fX);
            targetY = ppc::fmadds(v, m_afTargetOffsetY[4], w * m_afTargetOffsetY[5]);
            cameraY = ppc::fmadds(v, m_av2CameraOffset[4].m_fY, w * m_av2CameraOffset[5].m_fY);
        }
    }
    float deltaX = 0.0f;
    if ((flags & 2u) != 0) deltaX = ClearSignBit(m_v2CurrentCameraOffset.m_fX - cameraX);
    float deltaY = 0.0f;
    if (position != 3 && (flags & 4u) != 0) deltaY = ClearSignBit(m_v2CurrentCameraOffset.m_fY - cameraY);
    float deltaT = 0.0f;
    if ((flags & 1u) != 0) deltaT = ClearSignBit(m_fCurrentTargetOffsetY - targetY);
    float largest = deltaY > deltaT ? deltaY : deltaT;
    if (largest < deltaX) largest = deltaX;
    if (largest == 0.0f) return 0;
    const float scale = speed / largest;
    const float stepT = deltaT * scale;
    const float stepX = deltaX * scale;
    const float stepY = deltaY * scale;
    // The camera distance.
    const float x = m_v2CurrentCameraOffset.m_fX;
    if (x > cameraX) {
        const float next = x - stepX;
        if (!(next < cameraX)) cameraX = next;
    } else {
        const float next = stepX + x;
        if (!(next > cameraX)) cameraX = next;
    }
    m_v2CurrentCameraOffset.m_fX = cameraX;
    // The camera height.
    const float y = m_v2CurrentCameraOffset.m_fY;
    if (y > cameraY) {
        const float next = y - stepY;
        if (!(next < cameraY)) cameraY = next;
    } else {
        const float next = stepY + y;
        if (!(next > cameraY)) cameraY = next;
    }
    m_v2CurrentCameraOffset.m_fY = cameraY;
    // The target height.
    const float t = m_fCurrentTargetOffsetY;
    if (!(targetY < t)) {
        const float next = stepT + t;
        if (!(targetY < next)) targetY = next;
    } else {
        const float next = t - stepT;
        if (!(targetY > next)) targetY = next;
    }
    m_fCurrentTargetOffsetY = targetY;
    return RaiseOverGroundReference(this) ? 1 : 0;
}

// 0x00149470 CKCameraClassicTrack2_ApplyStickRotation_maybe
uint32_t CKCameraClassicTrack2::ApplyStickRotation(float dt, CMatrix34* m) {
    CKS08GameManager* manager = static_cast<CKS08GameManager*>(g_pEngine->m_gameManager);
    uint32_t result = 0;
    uint32_t movedFlag = 0;  // m_Flags bit 16
    const uint32_t flags = SrvCamera()->m_baTemporaryFlags;
    if ((flags & 4u) != 0) {
        m_Flags = (m_Flags & ~0x10000u) | movedFlag;
        return result;
    }
    bool turned = false;
    if ((flags & 0x200000u) != 0) {
        // The stick x turns the matrix about the target.
        const float axis = StickAxis(manager, 3, 2);
        if (axis != 0.0f) {
            uint32_t& serviceFlags = SrvCamera()->m_baTemporaryFlags;
            serviceFlags = (serviceFlags & ~0x100000u) | 0x100000u;
            float input = axis < 0.0f ? -axis * axis : axis * axis;
            if (manager->Vf1B8() != 0) input = -input;  // vt+0x1b8
            if ((input < 0.0f && m_fCurrentRotationSpeed > 0.0f) || (input > 0.0f && m_fCurrentRotationSpeed < 0.0f)) {
                m_fCurrentRotationSpeed = 0.0f;
            }
            const float limit = ClearSignBit(input * m_fPlayerCtrl_Rotation_MaxSpeed);
            const float next = ppc::fmadds(dt, input * m_fPlayerCtrl_Rotation_Acceleration, m_fCurrentRotationSpeed);
            float speed;
            if (-limit >= next) {
                speed = -limit;
            } else if (limit <= next) {
                speed = limit;
            } else {
                speed = next;
            }
            m_fCurrentRotationSpeed = speed;
            float angle = speed * dt;
            if (angle < 0.0f) {
                do {
                    angle = angle + kFullTurn;
                } while (angle < 0.0f);
            }
            while (angle >= kFullTurn) angle = angle - kFullTurn;
            result = 1;
            if (angle != 0.0f) RotateAboutPoint(angle, m, &m_WorldTarget, &kAxisY);  // 0x0023fba8
            turned = true;
        }
    }
    if (!turned) {
        m_fCurrentRotationSpeed = 0.0f;
        result = 0;
    }
    movedFlag = result != 0 ? 0x10000u : 0u;
    if ((SrvCamera()->m_baTemporaryFlags & 0x200000u) == 0) {
        m_Flags = (m_Flags & ~0x10000u) | movedFlag;
        return result;
    }
    // The stick y moves between the near and far offsets.
    const float axis = StickAxis(manager, 0, 1);
    if (axis == 0.0f) {
        m_Flags = (m_Flags & ~0x10000u) | movedFlag;
        return result;
    }
    uint32_t& serviceFlags = SrvCamera()->m_baTemporaryFlags;
    serviceFlags = (serviceFlags & ~0x100000u) | 0x100000u;
    float signedAxis = axis;
    if (manager->Vf1B0() != 0) signedAxis = -signedAxis;  // vt+0x1b0
    const float input = signedAxis < 0.0f ? signedAxis * -signedAxis : signedAxis * signedAxis;
    const bool towardNear = input < 0.0f;
    if ((towardNear && m_fCurrentOffsetSpeed > 0.0f) || (input > 0.0f && m_fCurrentOffsetSpeed < 0.0f)) {
        m_fCurrentOffsetSpeed = 0.0f;
    }
    const float limit = ClearSignBit(input * m_fPlayerCtrl_UpDown_MaxSpeed);
    const float next = ppc::fmadds(input * m_fPlayerCtrl_UpDown_Acceleration, dt, m_fCurrentOffsetSpeed);
    float speed;
    if (-limit >= next) {
        speed = -limit;
    } else if (limit <= next) {
        speed = limit;
    } else {
        speed = next;
    }
    m_fCurrentOffsetSpeed = speed;
    const float stepSize = ClearSignBit(speed * dt);
    if (towardNear) {
        AdaptTargetAndCameraCurrentOffset(dt, 0, stepSize, 7);
        result |= 8u;
    } else if (input > 0.0f) {
        const uint32_t which = FarDistance(this, SrvCamera()) >= m_v2CurrentCameraOffset.m_fX ? 7u : 5u;
        AdaptTargetAndCameraCurrentOffset(dt, 1, stepSize, which);
        result |= 4u;
    }
    result |= 2u;
    m_Flags = (m_Flags & ~0x10000u) | 0x10000u;
    return result;
}

// 0x00149a00 CKCameraClassicTrack2_UpdateModeSpeedAndAxis_maybe
uint8_t CKCameraClassicTrack2::UpdateWantedPosition(float dt) {
    const int32_t wanted = m_eCurrentWantedPosition;
    if (wanted == 2) {
        // Far: the speed up to twice the stick's.
        const float next = ppc::fmadds(dt, m_fPlayerCtrl_UpDown_Acceleration + m_fPlayerCtrl_UpDown_Acceleration,
                                       m_fCurrentOffsetSpeed);
        float speed = 0.0f;
        if (!(next <= 0.0f)) {
            const float top = m_fPlayerCtrl_UpDown_MaxSpeed + m_fPlayerCtrl_UpDown_MaxSpeed;
            speed = next >= top ? top : next;
        }
        m_fCurrentOffsetSpeed = speed;
        AdaptTargetAndCameraCurrentOffset(dt, 1, speed * dt, 7);
    } else if (wanted == 3) {
        // Normal: inward when farther than the normal distance, else outward.
        float speed;
        if (m_v2CurrentCameraOffset.m_fX > m_av2CameraOffset[2].m_fX) {
            const float next = ppc::fmadds(dt, m_fPlayerCtrl_UpDown_Acceleration * kMinusTwo, m_fCurrentOffsetSpeed);
            const float low = m_fPlayerCtrl_UpDown_MaxSpeed * kMinusTwo;
            if (low >= next) {
                speed = low;
            } else {
                speed = next >= 0.0f ? 0.0f : next;
            }
        } else {
            const float next = ppc::fmadds(dt, m_fPlayerCtrl_UpDown_Acceleration + m_fPlayerCtrl_UpDown_Acceleration,
                                           m_fCurrentOffsetSpeed);
            speed = 0.0f;
            if (!(next <= 0.0f)) {
                const float top = m_fPlayerCtrl_UpDown_MaxSpeed + m_fPlayerCtrl_UpDown_MaxSpeed;
                speed = next >= top ? top : next;
            }
        }
        m_fCurrentOffsetSpeed = speed;
        AdaptTargetAndCameraCurrentOffset(dt, 2, dt * speed, 7);
    } else if (wanted == 1) {
        // Near: the speed down to twice the stick's.
        const float next = ppc::fmadds(dt, m_fPlayerCtrl_UpDown_Acceleration * kMinusTwo, m_fCurrentOffsetSpeed);
        const float low = m_fPlayerCtrl_UpDown_MaxSpeed * kMinusTwo;
        float speed;
        if (low >= next) {
            speed = low;
        } else {
            speed = next >= 0.0f ? 0.0f : next;
        }
        m_fCurrentOffsetSpeed = speed;
        AdaptTargetAndCameraCurrentOffset(dt, 0, speed * dt, 7);
    } else {
        return 0;
    }
    const float left = m_fTimeToGoToWantedPosition - dt;
    m_fTimeToGoToWantedPosition = left;
    if (left <= 0.0f) {
        m_fTimeToGoToWantedPosition = kTwo;
        m_eCurrentWantedPosition = 0;
    }
    return 1;
}

// 0x0014b3f8 CKCameraClassicTrack2_PlaceBehindTarget_maybe
void CKCameraClassicTrack2::PlaceBehindTarget(const CVector3* target, CMatrix34* m) {
    CKSrvCamera* camera = SrvCamera();
    const CVector3 focus = CoopFocus(this);
    float atX = m->m_at.x;
    float atZ = m->m_at.z;
    float atY = 0.0f;
    const float length = Sqrtf(ppc::fmadds(atZ, atZ, ppc::fmadds(atX, atX, 0.0f)));
    if (length != 0.0f) {
        const float inverse = kOne / length;
        atZ = atZ * inverse;
        atX = atX * inverse;
        atY = inverse * 0.0f;
    }
    const float back = -m_v2CurrentCameraOffset.m_fX;
    if ((camera->m_baTemporaryFlags & 1u) != 0 && camera->m_v3GroundRefA.y > focus.y) {
        // The focus is under the ground reference (+0x8b0): the height from the camera's own position.
        const CVector3 again = CoopFocus(this);
        m_v2CurrentCameraOffset.m_fY = ClampCameraHeight(this, SrvCamera(), m_WorldPosition.y - again.y);
    }
    const float y = ppc::fmadds(back, atY, focus.y);
    const float height = m_v2CurrentCameraOffset.m_fY;
    const float x = ppc::fmadds(back, atX, focus.x);
    const float z = ppc::fmadds(back, atZ, focus.z);
    m->m_pos.x = x;
    m->m_pos.z = z;
    m->m_pos.y = y + height;
    m->m_ui32Flags = m->m_ui32Flags & 0xfffdffffu;
    IKCamera::OrientMatrixToTarget(target, &m->m_up, m);  // 0x00145ee0
}

// 0x0014b670 CKCameraClassicTrack2_UpdateAutoRecenter_maybe
uint8_t CKCameraClassicTrack2::UpdateAutoRecenter(float dt, CMatrix34* m) {
    if ((m_Flags & 0x10000u) != 0) {
        m_fRecenterTimer = m_fRecenterDelay;
        return 0;
    }
    const CVector3 focus = CoopFocus(this);
    float atX = m->m_at.x;
    float atZ = m->m_at.z;
    const float moveX = focus.x - m_v3PreviousTargetedPositionRefForTarget.x;
    const float moveY = focus.y - m_v3PreviousTargetedPositionRefForTarget.y;
    const float moveZ = focus.z - m_v3PreviousTargetedPositionRefForTarget.z;
    const float length = Sqrtf(ppc::fmadds(atZ, atZ, ppc::fmadds(atX, atX, 0.0f)));
    float atY = 0.0f;
    if (length != 0.0f) {
        const float inverse = kOne / length;
        atZ = atZ * inverse;
        atX = atX * inverse;
        atY = inverse * 0.0f;
    }
    float along = ppc::fmadds(moveZ, atZ, ppc::fmadds(moveX, atX, moveY * atY));
    const uint32_t count = StackCount(SrvCamera());
    if (count > 1) along = along * kCoopProjectionScale;
    const float idle = m_fCurrentIdleTimeLeft;
    if (idle > 0.0f && along > kThousandth && m_v2CurrentCameraOffset.m_fX < m_av2CameraOffset[0].m_fX) {
        // Still idle: a move away from the camera brings it in to the near distance.
        AdaptTargetAndCameraCurrentOffset(dt, 0, along, 7);
        m_fRecenterTimer = m_fRecenterDelay;
        return 1;
    }
    if (idle <= 0.0f) {
        if (along > kThousandth) {
            AdaptTargetAndCameraCurrentOffset(dt, 2, along, 7);
            m_fRecenterTimer = m_fRecenterDelay;
            return 1;
        }
        if (along < kMinusThousandth && m_v2CurrentCameraOffset.m_fX <= m_av2CameraOffset[2].m_fX) {
            const float limit = dt * m_fPlayerCtrl_UpDown_MaxSpeed;
            AdaptTargetAndCameraCurrentOffset(dt, 3, along > limit ? limit : along, 7);
            m_fRecenterTimer = m_fRecenterDelay;
            return 1;
        }
    }
    const bool still = kNullVector.x == moveX && kNullVector.y == moveY && kNullVector.z == moveZ;
    if (!still && count > 1) {
        const float limit = dt * m_fPlayerCtrl_UpDown_MaxSpeed;
        AdaptTargetAndCameraCurrentOffset(dt, 3, along > limit ? limit : along, 7);
        m_fRecenterTimer = m_fRecenterDelay;
        return 1;
    }
    if (along != 0.0f) {
        m_fRecenterTimer = m_fRecenterDelay;
        return 0;
    }
    // The focus did not move: after the delay the offsets come back to the normal position.
    float timer = m_fRecenterTimer;
    if (kFloatMax == timer) return 0;
    if (timer >= 0.0f) {
        m_fRecenterTimer = timer - dt;
        m_afRecenterApproach[2] = 0.0f;
        m_afRecenterApproach[0] = m_fPlayerCtrl_UpDown_MaxSpeed * kHalf;
        m_afRecenterApproach[1] = m_fPlayerCtrl_UpDown_Acceleration * kHalf;
        timer = m_fRecenterTimer;
    }
    if (!(timer <= 0.0f)) return 0;
    const CKSrvCamera* camera = SrvCamera();
    const uint32_t flags = camera->m_baTemporaryFlags;
    const uint8_t probe = camera->m_ui8ProbeFlags;
    if ((flags & 4u) != 0 || ((probe >> 2) & 1u) != 0 || (flags & 0x200u) != 0 || ((probe >> 1) & 1u) != 0 ||
        (probe & 1u) != 0 || (flags & 0x800u) != 0 || (flags & 0x1000u) != 0 ||
        camera->m_GContactInOut.m_eContactStatus == 2) {
        m_fRecenterTimer = kFloatMax;
        return 0;
    }
    FloatApproach_Step(dt, m_afRecenterApproach);  // 0x002436e8
    AdaptTargetAndCameraCurrentOffset(dt, 2, dt * m_afRecenterApproach[2], 7);
    return 1;
}

// 0x0014bbd8 CKCameraClassicTrack2_InitDistanceAndHeight_maybe
void CKCameraClassicTrack2::ForceCurrentOffsetsFromPosition(const CVector3* target, const CVector3* cameraPos) {
    CVector3 focus = CoopFocus(this);
    m_v2CurrentCameraOffset.m_fY = ClampCameraHeight(this, SrvCamera(), cameraPos->y - focus.y);
    focus = CoopFocus(this);
    const float dz = cameraPos->z - focus.z;
    const float dx = cameraPos->x - focus.x;
    const float distance = Sqrtf(ppc::fmadds(dx, dx, dz * dz));
    const float high = FarDistance(this, SrvCamera());
    float value;
    if (distance <= 0.0f) {
        value = 0.0f;
    } else {
        value = high <= distance ? high : distance;
    }
    m_v2CurrentCameraOffset.m_fX = value;
    focus = CoopFocus(this);
    m_fCurrentTargetOffsetY = target->y - focus.y;
}

// 0x0014be30 CKCameraClassicTrack2_UpdateFollow_maybe
void CKCameraClassicTrack2::UpdateFollow(float dt) {
    CKSrvCamera* camera = SrvCamera();
    CVector3 target = camera->m_v3FocusPos;  // sp+0x8c: the focus, then the target
    if (StackCount(camera) > 1) ApplyCoopTargetOffset(&target);
    uint32_t replace;
    if (target.x == m_v3PreviousTargetedPositionRefForTarget.x && target.y == m_v3PreviousTargetedPositionRefForTarget.y &&
        target.z == m_v3PreviousTargetedPositionRefForTarget.z) {
        replace = 0;
    } else {
        IKCamera::OrientMatrixToTarget(&target, &m_pMatrix->m_up, m_pMatrix);  // 0x00145ee0
        replace = 1;
    }
    bool clearSpeed = false;
    bool handled = false;
    const uint32_t stick = ApplyStickRotation(dt, m_pMatrix);
    if (stick != 0) {
        m_fRecenterTimer = m_fRecenterDelay;
        replace = 1;
        if ((stick & 2u) != 0) {
            m_fTimeToGoToWantedPosition = kTwo;
            m_eCurrentWantedPosition = 0;
            m_fCurrentIdleTimeLeft = m_fIdleTimeAfterPlayerInput;
            handled = true;
        }
    }
    if (!handled) {
        if (UpdateWantedPosition(dt) != 0) {
            replace = 1;
            m_fCurrentIdleTimeLeft = m_fIdleTimeAfterPlayerInput;
            m_fRecenterTimer = m_fRecenterDelay;
        } else {
            if (m_fCurrentIdleTimeLeft > 0.0f) m_fCurrentIdleTimeLeft = m_fCurrentIdleTimeLeft - dt;
            clearSpeed = true;
            const uint8_t recentered = UpdateAutoRecenter(dt, m_pMatrix);
            replace = ((replace & 0xffu) | recentered) != 0 ? 1u : 0u;
        }
    }
    // The target at the current target height over the focus; the camera placed again when its height is not the
    // current one or something moved it.
    const float heightOffset = m_v2CurrentCameraOffset.m_fY;
    const float focusY = target.y;
    const float matrixY = m_pMatrix->m_pos.y;
    const CVector3 focus = CoopFocus(this);
    const float wantedY = focusY + heightOffset;
    target.y = focus.y + m_fCurrentTargetOffsetY;
    target.z = focus.z;
    target.x = focus.x;
    if (matrixY != wantedY || replace != 0) PlaceBehindTarget(&target, m_pMatrix);  // 0x0014b3f8
    CVector3 position = m_pMatrix->m_pos;  // sp+0x80
    ResolveViewObstructions(dt, &camera->m_v3FocusPosCopy, &position);  // vt+0x74
    ResolveCameraCollision(&camera->m_v3FocusPosCopy, &position);       // vt+0x78
    const uint32_t serviceFlags = camera->m_baTemporaryFlags;
    if ((serviceFlags & 0x4000u) == 0 && (serviceFlags & 0x800u) == 0) {
        // The vertical move limited to m_fCameraMaxSpeed a second.
        const float y0 = m_WorldPosition.y;
        const float dy = position.y - y0;
        const float sign = dy < 0.0f ? kMinusOne : kOne;
        const float limit = dt * m_fCameraMaxSpeed;
        const float amount = ClearSignBit(dy);
        const float stepSize = limit < amount ? limit : amount;
        position.y = ppc::fmadds(stepSize, sign, y0);
    }
    CMatrix34* m = m_pMatrix;
    if (m->m_pos.x != position.x || m->m_pos.y != position.y || m->m_pos.z != position.z) {
        const float rise = position.y - m->m_pos.y;
        m->m_pos.z = position.z;
        m->m_pos.x = position.x;
        m->m_pos.y = position.y;
        m->m_ui32Flags = m->m_ui32Flags & 0xfffdffffu;
        if (rise < 0.0f && target.y - m_WorldTarget.y < kMinusThousandth) {
            // Down with a target going down: the offsets from the height before the move.
            CVector3 kept;  // sp+0x74
            kept.x = position.x;
            kept.z = position.z;
            kept.y = position.y - rise;
            ForceCurrentOffsetsFromPosition(&target, &kept);
        } else {
            ForceCurrentOffsetsFromPosition(&target, &m_pMatrix->m_pos);
        }
        if (RaiseOverGroundReference(this)) m_fCurrentOffsetSpeed = 0.0f;  // stw
        IKCamera::OrientMatrixToTarget(&target, &m_pMatrix->m_up, m_pMatrix);
    }
    ComputeFollowPose(dt, m_pMatrix, &target);  // 0x00148958
    m_WorldPosition.x = m_pMatrix->m_pos.x;
    m_WorldPosition.z = m_pMatrix->m_pos.z;
    m_WorldPosition.y = m_pMatrix->m_pos.y;
    m_WorldTarget.x = target.x;
    m_WorldTarget.z = target.z;
    m_WorldTarget.y = target.y;
    if (clearSpeed) m_fCurrentOffsetSpeed = 0.0f;  // stw
    m_v3PreviousTargetedPositionRefForTarget = SrvCamera()->m_v3FocusPos;
    if (StackCount(SrvCamera()) > 1) ApplyCoopTargetOffset(&m_v3PreviousTargetedPositionRefForTarget);
}

// 0x001470a8 CameraTrack_ClampPositionByCollision_maybe
float CKCameraClassicTrack2::ClampPositionByCollision(IKCamera* camera, float best, const CVector3* from,
                                                      const CVector3* to, CVector3* out) {
    CMasksOfGrdTypeForTests masks;  // sp+0x70
    masks.m_ui32GrdToTest = 1;
    masks.m_ui32GrdToAvoid = 0x80;
    CLine line;  // sp+0x88
    line.m_start.x = from->x;
    line.m_start.y = from->y;
    line.m_start.z = from->z;
    line.m_VectDir.x = to->x - from->x;
    line.m_VectDir.y = to->y - from->y;
    line.m_VectDir.z = to->z - from->z;
    const CKSrvCamera::SCameraAvoidingDatas& avoid = AvoidingDatas(SrvCamera(), camera);
    CGroundEdgeDatasOut wall;  // sp+0xa0
    if (SrvCollision()->SweepCylinderAgainstWalls(&line, avoid.m_afValues[1], avoid.m_afValues[3], &wall, 0, &masks,
                                                  1) != 0) {  // 0x00198ed0
        const float t = wall.m_ftLine;
        const float y = t * line.m_VectDir.y;
        const float x = t * line.m_VectDir.x;
        const float z = t * line.m_VectDir.z;
        const float square = ppc::fmadds(z, z, ppc::fmadds(x, x, y * y));
        if (best < square) {
            best = square;
            out->z = z + from->z;
            out->x = x + from->x;
            out->y = y + from->y;
        }
        return best;
    }
    CLineCollisionDatas hit;  // sp+0x78
    hit.m_ui8SectorNumber = 0;
    hit.m_i32FaceIndex = -1;
    hit.m_pCollisionMesh = nullptr;
    hit.m_ftOnLine = kFloatMax;
    if (SrvCollision()->RaycastMeshes(&line, &hit, 1, 0, &masks) != 0) {  // 0x00197af8
        const float t = hit.m_ftOnLine + kTenth;
        const float y = line.m_VectDir.y * t;
        const float x = line.m_VectDir.x * t;
        const float z = line.m_VectDir.z * t;
        const float square = ppc::fmadds(z, z, ppc::fmadds(x, x, y * y));
        if (square > best) {
            best = square;
            out->z = z + from->z;
            out->x = x + from->x;
            out->y = y + from->y;
        }
        return best;
    }
    out->z = to->z;
    out->x = to->x;
    out->y = to->y;
    return kFloatMax;
}

// 0x0014ddc8 CKCameraClassicTrack2_SearchUnobstructedAngle_maybe
uint8_t CKCameraClassicTrack2::SearchUnobstructedAngle(float distanceSquare, const CVector3* from, CVector3* position) {
    CKSrvCamera* camera = SrvCamera();
    const CKSrvCamera::SCameraAvoidingDatas& avoid = AvoidingDatas(camera, this);
    const float baseY = from->y + avoid.m_afValues[2];
    // The offset behind the followed node: its at axis (frame ltm +0x70) times -distance, flat (z axis when null).
    IKSerializable* followed = FirstTarget(camera);
    const RwV3d& at = static_cast<CSGMovable*>(followed)->m_pRwFrame->ltm.at;
    const float back = -m_v2CurrentCameraOffset.m_fX;
    float offsetX = at.x * back;
    float offsetZ = at.z * back;
    if (offsetX == 0.0f && offsetZ == 0.0f) {
        offsetZ = kAxisZ.z;
        offsetX = kAxisZ.x;
    }
    float limit = (m_v2CurrentCameraOffset.m_fX * m_v2CurrentCameraOffset.m_fX) * kNearFraction;
    const float margin = distanceSquare * kSearchMargin;
    if (!(limit > margin)) limit = margin;
    CVector3 candidate;  // sp+0xa0
    candidate.y = from->y + m_v2CurrentCameraOffset.m_fY;
    float best = distanceSquare;
    if (!(limit > distanceSquare)) return 0;
    // One candidate: the offset turned by `angle` about y around `from`.
    auto tryAngle = [&](float angle) {
        const float c = GameCosf(angle);
        const float s = GameSinf(angle);
        candidate.x = ppc::fmadds(offsetZ, s, ppc::fmadds(offsetX, c, from->x));
        candidate.z = ppc::fmadds(offsetZ, c, from->z) - s * offsetX;
        CVector3 start;  // the cylinder's start: the focus at the probes' height
        start.x = from->x;
        start.y = baseY;
        start.z = from->z;
        best = ClampPositionByCollision(this, best, &start, &candidate, position);  // 0x001470a8
    };
    float angle = 0.0f;
    for (;;) {
        tryAngle(angle);
        if (limit > best && angle != 0.0f) tryAngle(-angle);
        if (!(best < limit)) return best > distanceSquare ? 1 : 0;
        if (angle == kHalfPi) return distanceSquare < best ? 1 : 0;
        tryAngle(kPi - angle);
        if (limit > best && angle != 0.0f) tryAngle(angle + kPi);
        if (!(best < limit)) return best > distanceSquare ? 1 : 0;
        angle = angle + kQuarterPi;
        if (!(angle <= kHalfPi)) return distanceSquare < best ? 1 : 0;
    }
}

// 0x0014f030 CKCameraClassicTrack2_ResolveWallCollision_maybe
void CKCameraClassicTrack2::ResolveWallCollision(const CVector3* from, CVector3* position) {
    if ((m_Flags & 0x2000u) == 0) return;
    CKSrvCamera* camera = SrvCamera();
    CMasksOfGrdTypeForTests masks;  // sp+0x70
    masks.m_ui32GrdToTest = 1;
    masks.m_ui32GrdToAvoid = 0x80;
    const CKSrvCamera::SCameraAvoidingDatas& avoid = AvoidingDatas(camera, this);
    CLine line;  // sp+0x84
    line.m_start.x = from->x;
    line.m_start.y = from->y + avoid.m_afValues[2];
    line.m_start.z = from->z;
    line.m_VectDir.x = position->x - from->x;
    line.m_VectDir.z = position->z - from->z;
    line.m_VectDir.y = position->y - line.m_start.y;
    CSlideGroundEdgeDatasOut out;  // sp+0x9c; the callee fills it when it answers 2 / 3
    const uint8_t result = SrvCollision()->ResolveSweptCylinderWalls(&line, avoid.m_afValues[1], avoid.m_afValues[3],
                                                                     &out, nullptr, &masks, 1);  // 0x0019aa68
    if (result != 2 && result != 3) return;
    const float x = position->x + out.m_v3BouncingVector.x;
    const float y = position->y + out.m_v3BouncingVector.y;
    const float z = position->z + out.m_v3BouncingVector.z;
    bool store = true;
    if (!(camera->m_fBlendDuration > 0.0f)) {
        // Outside a camera transition: a slide that brings the camera nearer than 0.75 of the distance looks for
        // another angle around the focus.
        const float dy = y - from->y;
        const float dx = x - from->x;
        const float dz = z - from->z;
        const float near = (m_v2CurrentCameraOffset.m_fX * m_v2CurrentCameraOffset.m_fX) * kNearFraction;
        const float square = ppc::fmadds(dz, dz, ppc::fmadds(dx, dx, dy * dy));
        if (!(near <= square)) {
            const CVector3 start = *from;  // sp+0x78
            store = SearchUnobstructedAngle(square, &start, position) == 0;
        }
    }
    if (store) {
        position->z = z;
        position->x = x;
        position->y = y;
    }
}

// 0x0014f278 CKCameraClassicTrack2_Activate_maybe
void CKCameraClassicTrack2::Start(const CVector3* startPosition) {
    StartAttachedFx();  // 0x001441e8
    CKSrvCamera* camera = SrvCamera();
    if (StackCount(camera) > 1) {
        // Co-op: the offsets between the co-op near / far ones by the heroes' distance.
        const float* second = camera->m_aStack[1].m_unk24;
        const CVector3& focus = camera->m_v3FocusPos;
        const float dy = second[1] - focus.y;
        const float dx = second[0] - focus.x;
        const float dz = second[2] - focus.z;
        const float distance = Sqrtf(ppc::fmadds(dz, dz, ppc::fmadds(dx, dx, dy * dy)));
        const float t = (distance == 0.0f ? 0.0f : distance) / m_fCoopDistanceRange;
        float w;
        float v;
        if (t <= 0.0f) {
            w = 0.0f;
            v = kOne;
        } else if (t >= kOne) {
            w = kOne;
            v = 0.0f;
        } else {
            v = kOne - t;
            w = t;
        }
        m_v2CurrentCameraOffset.m_fX = ppc::fmadds(v, m_av2CameraOffset[4].m_fX, w * m_av2CameraOffset[5].m_fX);
        m_v2CurrentCameraOffset.m_fY = ppc::fmadds(v, m_av2CameraOffset[4].m_fY, w * m_av2CameraOffset[5].m_fY);
        m_fCurrentTargetOffsetY = ppc::fmadds(v, m_afTargetOffsetY[4], w * m_afTargetOffsetY[5]);
    } else {
        m_v2CurrentCameraOffset.m_fX = m_av2CameraOffset[2].m_fX;
        m_v2CurrentCameraOffset.m_fY = m_av2CameraOffset[2].m_fY;
        m_fCurrentTargetOffsetY = m_afTargetOffsetY[2];
    }
    m_fCurrentTargetOffsetLR = 0.0f;
    m_fCurrentOffsetSpeed = 0.0f;
    m_fCurrentRotationSpeed = 0.0f;
    m_fCurrentIdleTimeLeft = 0.0f;
    m_fRecenterTimer = kFloatMax;
    m_eCurrentWantedPosition = 0;
    m_fTimeToGoToWantedPosition = kTwo;
    m_fTargetOffsetLRHold = 0.0f;
    m_fCoopBlend = 0.0f;
    m_v3PreviousTargetedPositionRefForTarget = SrvCamera()->m_v3FocusPos;
    if (StackCount(SrvCamera()) > 1) ApplyCoopTargetOffset(&m_v3PreviousTargetedPositionRefForTarget);
    m_WorldTarget = m_v3PreviousTargetedPositionRefForTarget;
    m_WorldTarget.y = m_WorldTarget.y + m_fCurrentTargetOffsetY;
    // The direction from the camera to the target, flat: from the start position, else the real camera's at axis.
    float dirX;
    float dirZ;
    if (startPosition == nullptr) {
        const CVector3& at = SrvCamera()->m_v3RealAxisZ;  // +0x5c8
        dirX = at.x;
        dirZ = at.z;
    } else {
        m_WorldPosition.x = startPosition->x;
        m_WorldPosition.z = startPosition->z;
        dirX = m_WorldTarget.x - startPosition->x;
        dirZ = m_WorldTarget.z - startPosition->z;
        m_WorldPosition.y = startPosition->y;
    }
    float dirY = 0.0f;
    const float length = Sqrtf(ppc::fmadds(dirZ, dirZ, ppc::fmadds(dirX, dirX, 0.0f)));
    if (length != 0.0f) {
        const float inverse = kOne / length;
        dirZ = dirZ * inverse;
        dirX = dirX * inverse;
        dirY = inverse * 0.0f;
    }
    m_WorldPosition = SrvCamera()->m_v3FocusPos;
    if (StackCount(SrvCamera()) > 1) ApplyCoopTargetOffset(&m_WorldPosition);
    const float back = -m_v2CurrentCameraOffset.m_fX;
    m_WorldPosition.z = ppc::fmadds(dirZ, back, m_WorldPosition.z);
    m_WorldPosition.x = ppc::fmadds(dirX, back, m_WorldPosition.x);
    m_WorldPosition.y = ppc::fmadds(dirY, back, m_WorldPosition.y);
    m_WorldPosition.y = m_WorldPosition.y + m_v2CurrentCameraOffset.m_fY;
    const CVector3 from = camera->m_v3FocusPosCopy;  // sp+0x74
    ResolveWallCollision(&from, &m_WorldPosition);                       // 0x0014f030
    ResolveCameraCollision(&camera->m_v3FocusPosCopy, &m_WorldPosition);  // vt+0x78
    // The matrix: the real camera's axes at the position, turned to the target.
    CMatrix34* m = m_pMatrix;
    m->m_right = camera->m_v3RealAxisX;
    m->m_up = camera->m_v3RealAxisY;
    const uint32_t matrixFlags = m->m_ui32Flags & 0xfffdfffcu;
    m->m_at = camera->m_v3RealAxisZ;
    m->m_pos = m_WorldPosition;
    m->m_ui32Flags = matrixFlags;
    IKCamera::OrientMatrixToTarget(&m_WorldTarget, &kAxisY, m_pMatrix);  // 0x00145ee0
    ForceCurrentOffsetsFromPosition(&m_WorldTarget, &m_pMatrix->m_pos);  // 0x0014bbd8
    // The last focus nudged so that the first update sees a move.
    m_v3PreviousTargetedPositionRefForTarget.y = m_v3PreviousTargetedPositionRefForTarget.y - kPrevNudge;
    // State 0 entered (the frame time 0).
    float dt = 0.0f;  // sp+0x70
    const uint8_t old = m_ui8State;
    if (old != 0xff) (this->*m_pStateTable[old])(&dt, 2, 0);
    m_ui8State = 0;
    (this->*m_pStateTable[0])(&dt, 1, old);
}

namespace {

constexpr float kMargin = 0x1.47ae14p-7f;        // -0x3b30 0x3c23d70a (0.01)
constexpr float kMinusMargin = -0x1.47ae14p-7f;  // -0x3b2c 0xbc23d70a
constexpr float kMinusHalf = -0.5f;              // -0x3b5c 0xbf000000

// The camera service's contact copies are the XXL2 types' twins (same layout): the contact helpers take the XXL2 ones.
const ::CGroundContactDatasInOut* AsContact(const CKSrvCamera::CGroundContactDatasInOut* contact) {
    return reinterpret_cast<const ::CGroundContactDatasInOut*>(contact);
}
// The ground's engine flags (ICollisionMesh +0x36): bit 1 (0x2) the floor height m_fPropertieValue applies, bit 3 (0x8)
// _maybe a ceiling (the camera is put under it).
uint32_t GroundFlags(const IKSerializable* ground) { return static_cast<const ICollisionMesh*>(ground)->m_ba16EngineFlags; }
float GroundProperty(const IKSerializable* ground) { return static_cast<const CGround*>(ground)->m_fPropertieValue; }

// The camera pushed out of a hit face along its normal by `radius` (the same code as IKCamera.cpp's helper for
// 0x1461a0): the face is the hit's (the mesh's triangle m_i32FaceIndex), its normal (v1 - v0) x (v2 - v0), normalised
// unless 0.
void PushAlongHitFaceNormal(const CLineCollisionDatas& hit, float radius, CVector3* position) {
    const ICollisionMesh* mesh = hit.m_pCollisionMesh;
    const uint16_t* triangle = nullptr;
    if (hit.m_i32FaceIndex != -1 && mesh != nullptr &&
        static_cast<int32_t>(mesh->m_ui16NbTriangle) > hit.m_i32FaceIndex) {
        triangle = mesh->m_aTriangle[hit.m_i32FaceIndex].m_aui16Index;
    }
    if (triangle == nullptr) {
        // BUG(original): without a face (or a mesh) the original reads the vertex indices at address 0, a fault on the
        // PS3. A hit always has both, so this is never reached.
        return;
    }
    const CVector3& v1 = mesh->m_aVertex[triangle[1]];
    const CVector3& v0 = mesh->m_aVertex[triangle[0]];
    const CVector3& v2 = mesh->m_aVertex[triangle[2]];
    const float e1x = v1.x - v0.x;
    const float e2z = v2.z - v0.z;
    const float e1z = v1.z - v0.z;
    const float e2x = v2.x - v0.x;
    const float e2y = v2.y - v0.y;
    const float e1y = v1.y - v0.y;
    const float xz = e1x * e2z;
    const float zy = e1z * e2y;
    float ny = ppc::fmsubs(e1z, e2x, xz);
    const float yx = e1y * e2x;
    float nx = ppc::fmsubs(e1y, e2z, zy);
    float nz = ppc::fmsubs(e1x, e2y, yx);
    const float length = Sqrtf(ppc::fmadds(nz, nz, ppc::fmadds(nx, nx, ny * ny)));
    if (length != 0.0f) {
        const float inverse = kOne / length;
        nz = nz * inverse;
        nx = nx * inverse;
        ny = ny * inverse;
    }
    position->x = ppc::fmadds(radius, nx, position->x);
    position->y = ppc::fmadds(radius, ny, position->y);
    position->z = ppc::fmadds(radius, nz, position->z);
}

// The ground's floor height (flag bit 1): the y raised to radius + m_fPropertieValue.
void ClampAboveGroundProperty(const IKSerializable* ground, float radius, CVector3* position) {
    if (((GroundFlags(ground) >> 1) & 1u) == 0) return;
    const float floor = radius + GroundProperty(ground);
    float y = position->y;
    if (!(y > floor)) y = floor;
    position->y = y;
}

// The camera `radius` above the ground point `world` (along a moving ground's up axis).
void PlaceAboveGround(IKSerializable* ground, bool dynamic, float radius, const CVector3& world, CVector3* position) {
    if (!dynamic) {
        position->y = radius + world.y;
        return;
    }
    const CMatrix34* matrix = static_cast<ICollisionMesh*>(ground)->GetWorldMatrix();  // vt+0x50
    position->x = ppc::fmadds(radius, matrix->m_up.x, world.x);
    position->y = ppc::fmadds(radius, matrix->m_up.y, world.y);
    position->z = ppc::fmadds(radius, matrix->m_up.z, world.z);
}

}  // namespace

// 0x0014c4f8 CKCameraClassicTrack2_ResolveCameraCollision_maybe (vt+0x78): IKCamera's FindGroundContact (0x1461a0,
// IKCamera.cpp) with three differences: the radius is the larger of the view's half height at distance 1 and Vf80 +
// 0.01; without a ground the line starts at the (co-op) focus at the target height (m_fCurrentTargetOffsetY) and a wall
// on the line from the last position is tested on that line too; on a ground more than 0.5 above the target the camera
// is kept at least half way down the target's plane along the ground normal (the comeback timer stopped).
void CKCameraClassicTrack2::ResolveCameraCollision(const CVector3* target, CVector3* position) {
    if ((m_Flags & 0x1000u) == 0) return;
    CKSrvCamera* camera = SrvCamera();
    CKSrvCollision* collision = SrvCollision();
    float halfWidth;   // sp+0x70
    float halfHeight;  // sp+0x74
    GetHalfExtentsAtDistance(kOne, &halfWidth, &halfHeight);  // 0x00144278
    CKSrvCamera::CGroundContactDatasIn* in = &camera->m_GContactIn;
    CKSrvCamera::CGroundContactDatasInOut* contact = &camera->m_GContactInOut;
    CVector3 probe = *position;  // sp+0x90
    float radius = halfHeight;
    const float minimum = Vf80() + kMargin;  // vt+0x80
    if (!(radius > minimum)) radius = minimum;
    const float dy = probe.y - m_WorldPosition.y;
    if (dy < kMinusMargin) {
        in->m_fObjectHeight = halfHeight - dy;
        float above = dy + halfHeight;
        if (above < 0.0f) above = 0.0f;
        in->m_fDeltaMax = above;
    } else {
        probe.y = m_WorldPosition.y;
        in->m_fDeltaMax = 0.0f;  // stw 0
        in->m_fObjectHeight = dy + halfHeight;
    }
    collision->GroundProbePoints(in, contact, &probe.x, 1);  // 0x00196540
    const uint32_t status = contact->m_eContactStatus;
    if (status == 3) {
        // No ground under the camera: the lines to the camera.
        CLineCollisionDatas hit;  // sp+0x9c
        hit.m_i32FaceIndex = -1;
        hit.m_ui8SectorNumber = 0;
        hit.m_ftOnLine = kFloatMax;
        hit.m_pCollisionMesh = nullptr;
        CMasksOfGrdTypeForTests masks;  // sp+0x7c
        masks.m_ui32GrdToTest = 1;
        masks.m_ui32GrdToAvoid = 0x80;
        CLine fromLast;  // sp+0xc4: from the last position to the camera
        fromLast.m_start.x = m_WorldPosition.x;
        fromLast.m_start.z = m_WorldPosition.z;
        fromLast.m_start.y = m_WorldPosition.y;
        fromLast.m_VectDir.x = position->x - m_WorldPosition.x;
        fromLast.m_VectDir.y = position->y - m_WorldPosition.y;
        fromLast.m_VectDir.z = position->z - m_WorldPosition.z;
        const CVector3 focus = CoopFocus(this);  // sp+0x84
        CLine fromFocus;  // sp+0xac: from the focus at the target height
        fromFocus.m_start.x = focus.x;
        fromFocus.m_start.z = focus.z;
        fromFocus.m_start.y = focus.y + m_fCurrentTargetOffsetY;
        fromFocus.m_VectDir.z = position->z - focus.z;
        fromFocus.m_VectDir.x = position->x - focus.x;
        fromFocus.m_VectDir.y = position->y - fromFocus.m_start.y;
        if (collision->RaycastMeshes(&fromFocus, &hit, 1, 1, &masks)) {  // 0x00197af8
            const float t = hit.m_ftOnLine;
            position->x = ppc::fmadds(t, fromFocus.m_VectDir.x, fromFocus.m_start.x);
            position->z = ppc::fmadds(t, fromFocus.m_VectDir.z, fromFocus.m_start.z);
            position->y = ppc::fmadds(t, fromFocus.m_VectDir.y, fromFocus.m_start.y);
            PushAlongHitFaceNormal(hit, radius, position);
        } else {
            CGroundEdgeDatasOut edge;  // sp+0xdc (both wall tests write it)
            if (collision->RaycastWalls(&fromLast, 0.0f, &edge, 1, &masks, 1)) {  // 0x00198438
                if (collision->RaycastWalls(&fromFocus, 0.0f, &edge, 1, &masks, 1)) {
                    const float t = edge.m_ftLine;
                    position->x = ppc::fmadds(t, fromFocus.m_VectDir.x, fromFocus.m_start.x);
                    position->z = ppc::fmadds(t, fromFocus.m_VectDir.z, fromFocus.m_start.z);
                    position->y = ppc::fmadds(t, fromFocus.m_VectDir.y, fromFocus.m_start.y);
                } else {
                    // The record as the second (missed) test left it: the original reads it after the miss.
                    const float t = edge.m_ftLine;
                    const float x = ppc::fmadds(t, fromLast.m_VectDir.x, fromLast.m_start.x);
                    const float z = ppc::fmadds(t, fromLast.m_VectDir.z, fromLast.m_start.z);
                    const float y = ppc::fmadds(t, fromLast.m_VectDir.y, fromLast.m_start.y);
                    position->x = ppc::fmadds(edge.m_EdgeNormal.x, kTenth, x);
                    position->z = ppc::fmadds(edge.m_EdgeNormal.z, kTenth, z);
                    position->y = ppc::fmadds(edge.m_EdgeNormal.y, kTenth, y);
                }
            } else if (collision->RaycastMeshes(&fromLast, &hit, 1, 1, &masks)) {
                const float t = hit.m_ftOnLine;
                position->x = ppc::fmadds(t, fromLast.m_VectDir.x, fromLast.m_start.x);
                position->z = ppc::fmadds(t, fromLast.m_VectDir.z, fromLast.m_start.z);
                position->y = ppc::fmadds(t, fromLast.m_VectDir.y, fromLast.m_start.y);
                PushAlongHitFaceNormal(hit, radius, position);
            }
        }
        camera->m_baTemporaryFlags = (camera->m_baTemporaryFlags & ~0x800u) | 0x800u;
        camera->m_baTemporaryFlags = (camera->m_baTemporaryFlags & ~0x1000u) | 0x1000u;
        if ((m_Flags & 0x2000u) != 0) {
            camera->SetPlayerCanMoveCamera(false);  // 0x0012ac08
        } else {
            camera->SetPlayerCanMoveCamera(true);
        }
        return;
    }
    camera->SetPlayerCanMoveCamera(true);
    IKSerializable* ground = contact->m_pGround;
    if (((GroundFlags(ground) >> 3) & 1u) != 0) {
        // A ceiling (_maybe): the camera h + 0.01 under it.
        if (status == 0) {
            const float distance = ClearSignBit(position->y - target->y);
            if (!(contact->m_fdH < distance)) {
                camera->m_baTemporaryFlags &= ~0x800u;
                camera->m_baTemporaryFlags &= ~0x1000u;
                return;
            }
        }
        CVector3 world;  // sp+0xac
        GroundContact_GetWorldPoint(AsContact(contact), &world);  // 0x001a70e0
        position->y = (world.y - halfHeight) - kMargin;
        camera->m_baTemporaryFlags = (camera->m_baTemporaryFlags & ~0x800u) | 0x800u;
        camera->m_baTemporaryFlags &= ~0x1000u;
        return;
    }
    if (status <= 1) {
        // On the ground or just above it: the radius above it.
        CVector3 world;
        GroundContact_GetWorldPoint(AsContact(contact), &world);
        if ((camera->m_ui8ProbeFlags & 1u) != 0) radius = kMargin;
        float y = radius + world.y;
        const float below = target->y - world.y;
        if (below < kMinusHalf) {
            // The target below the ground: the camera at least half way down the target's plane along the normal.
            const CVector3& normal = contact->m_Normal;
            const float along = ppc::fmadds(target->z - world.z, normal.z,
                                            ppc::fmadds(target->x - world.x, normal.x, below * normal.y));
            const float plane = ppc::fmadds(along, kMinusHalf, world.y);
            if (y < plane) {
                y = plane;
                m_fRecenterTimer = kFloatMax;
            }
        }
        if (((GroundFlags(ground) >> 1) & 1u) != 0) {
            const float floor = radius + GroundProperty(ground);
            if (!(y > floor)) y = floor;
        }
        if (!(position->y <= y)) {
            camera->m_baTemporaryFlags &= ~0x1800u;
            return;
        }
        position->y = y;
        camera->m_baTemporaryFlags = (camera->m_baTemporaryFlags & ~0x800u) | 0x800u;
        camera->m_baTemporaryFlags = (camera->m_baTemporaryFlags & ~0x1000u) | 0x1000u;
        return;
    }
    if (status != 2) return;
    // Within the object height of the ground.
    const bool dynamic = static_cast<ICollisionMesh*>(ground)->GetClassID() == 0x13;  // vt+0x18: CDynamicGround
    CVector3 world;
    GroundContact_GetWorldPoint(AsContact(contact), &world);
    if ((camera->m_baTemporaryFlags & 1u) == 0 && target->y >= world.y) {
        PlaceAboveGround(ground, dynamic, radius, world, position);
        ClampAboveGroundProperty(ground, radius, position);
        camera->m_baTemporaryFlags = (camera->m_baTemporaryFlags & ~0x800u) | 0x800u;
        camera->m_baTemporaryFlags = (camera->m_baTemporaryFlags & ~0x1000u) | 0x1000u;
        return;
    }
    // The target is under the ground (or the service's bit 0): a second probe h + 0.01 under the ground's point.
    CKSrvCamera::CGroundContactDatasInOut below;  // sp+0xdc (only these four members are set)
    below.m_i32FaceIndex = -1;
    below.m_eContactStatus = 3;
    below.m_ui8SectorNumber = 0;
    below.m_pGround = nullptr;
    if (!dynamic) {
        probe.y = world.y - (halfHeight + kMargin);
    } else {
        const CMatrix34* matrix = static_cast<ICollisionMesh*>(ground)->GetWorldMatrix();  // vt+0x50
        const float back = -(halfHeight + kMargin);
        probe.z = ppc::fmadds(back, matrix->m_up.z, world.z);
        probe.x = ppc::fmadds(back, matrix->m_up.x, world.x);
        probe.y = ppc::fmadds(back, matrix->m_up.y, world.y);
    }
    in->m_fObjectHeight = halfHeight;
    in->m_fDeltaMax = halfHeight * kTenth;
    collision->GroundProbePoints(in, &below, &probe.x, 1);
    if (below.m_eContactStatus != 3 && (GroundFlags(below.m_pGround) & 0x8u) != 0) {
        CVector3 ceiling;  // sp+0x84
        GroundContact_GetWorldPoint(AsContact(&below), &ceiling);
        ceiling.y = ceiling.y - (halfHeight + kMargin);
        const float targetY = target->y;
        if (below.m_eContactStatus != 0 || !(targetY > ceiling.y)) {
            // The target must see the point under the ceiling.
            CLineCollisionDatas hit;  // sp+0x9c
            hit.m_i32FaceIndex = -1;
            hit.m_ftOnLine = kFloatMax;
            hit.m_ui8SectorNumber = 0;
            hit.m_pCollisionMesh = nullptr;
            CMasksOfGrdTypeForTests masks;  // sp+0x7c
            masks.m_ui32GrdToTest = 1;
            masks.m_ui32GrdToAvoid = 0x80;
            CLine line;  // sp+0xc4
            line.m_start.x = target->x;
            line.m_start.y = targetY;
            line.m_start.z = target->z;
            line.m_VectDir.y = ceiling.y - targetY;
            line.m_VectDir.x = ceiling.x - target->x;
            line.m_VectDir.z = ceiling.z - target->z;
            if (!collision->RaycastMeshes(&line, &hit, 1, 1, &masks)) {
                position->z = ceiling.z;
                position->x = ceiling.x;
                position->y = ceiling.y;
                CopyGroundContact(*reinterpret_cast<::CGroundContactDatasInOut*>(contact), *AsContact(&below));
                camera->m_baTemporaryFlags &= ~0x1000u;
                camera->m_baTemporaryFlags = (camera->m_baTemporaryFlags & ~0x800u) | 0x800u;
                return;
            }
        }
    }
    PlaceAboveGround(ground, dynamic, radius, world, position);
    ClampAboveGroundProperty(ground, radius, position);
    camera->m_baTemporaryFlags = (camera->m_baTemporaryFlags & ~0x1000u) | 0x1000u;
    camera->m_baTemporaryFlags = (camera->m_baTemporaryFlags & ~0x800u) | 0x800u;
}

namespace {

constexpr float kFarFactor = 0x1.333334p+0f;       // -0x3b58 0x3f99999a (1.2)
constexpr float kMaxSpringValue = 10000.0f;        // -0x3b54 0x461c4000
constexpr float kSettleDistance = 0x1.99999ap-3f;  // -0x3b50 0x3e4ccccd (0.2)
constexpr float kSettleSquare = 0x1.47ae16p-5f;    // -0x3b4c 0x3d23d70b (0.04, one ulp above 0.04f)
constexpr float kWallTopMargin = 0x1.47ae14p-6f;   // -0x3b48 0x3ca3d70a (0.02)

float Word(uint32_t word) { return IKCamera::AsFloat(word); }
uint32_t Word(float value) { return IKCamera::AsWord(value); }

}  // namespace

// 0x0014a018 CKCameraClassicTrack2_vf74 (vt+0x74, XXL2 FindAndRepairOcclusion): IKCamera's FindAndRepairOcclusion
// (0x145088, IKCamera.cpp) for this track. The differences: the focus point of the distance tests is the co-op focus
// (`focus` still starts the lines); the push sphere's correction moves at most 2 dt; "far" is beyond 1.2 times the
// farthest camera distance; the wall spring runs whenever a wall pushed the camera (with m_Flags 0x10000 only when far),
// its speed limited to m_fCameraMaxSpeed when near, and it keeps the player from moving the camera; the masks avoid the
// ground types 0x180 (0x280 in co-op); the walls of the slide from the focus are also tested with the ground masks
// (ignored when their intersection is above the ground under the camera); a new wall contact keeps the camera at most at
// the current distance; and without a wall contact (and m_Flags 0x10000) a ground between the focus' mid height and
// the camera brings the camera onto it (the comeback timer stopped).
void CKCameraClassicTrack2::ResolveViewObstructions(float dt, const CVector3* focus, CVector3* position) {
    CKSrvCamera* camera = SrvCamera();
    if ((m_Flags & 0x2000u) == 0) {
        camera->m_baTemporaryFlags &= ~0x200u;
        camera->m_ui8ProbeFlags = static_cast<uint8_t>(camera->m_ui8ProbeFlags & 0xf8u);
        camera->m_baTemporaryFlags &= ~0x400u;
        return;
    }
    const float startX = focus->x;
    const float startZ = focus->z;
    const float startY = focus->y + AvoidingDatas(camera, this).m_afValues[2];
    // The focus of the distance tests (sp+0x94): the co-op focus at the probes' height, else the lines' start.
    CVector3 center;
    if (StackCount(camera) > 1) {
        center = CoopFocus(this);
        center.y = center.y + AvoidingDatas(camera, this).m_afValues[2];
    } else {
        center.x = startX;
        center.y = startY;
        center.z = startZ;
    }
    const float savedX = camera->m_v3SavedPos.x;
    const float savedY = camera->m_v3SavedPos.y;
    const float savedZ = camera->m_v3SavedPos.z;
    CKSrvCollision* collision = SrvCollision();
    const CKSrvCamera::SCameraAvoidingDatas& avoid = AvoidingDatas(camera, this);
    CMasksOfGrdTypeForTests wallMasks;    // sp+0x7c: the slide from the focus
    wallMasks.m_ui32GrdToTest = 1;
    wallMasks.m_ui32GrdToAvoid = 0x180;
    CMasksOfGrdTypeForTests moveMasks;    // sp+0x84: the slide from the last position
    moveMasks.m_ui32GrdToTest = 1;
    moveMasks.m_ui32GrdToAvoid = 0x80;
    CMasksOfGrdTypeForTests groundMasks;  // sp+0x8c: the grounds between the focus and the camera
    groundMasks.m_ui32GrdToTest = 8;
    groundMasks.m_ui32GrdToAvoid = 0x180;
    if (StackCount(camera) > 1) {
        groundMasks.m_ui32GrdToAvoid = 0x280;
        wallMasks.m_ui32GrdToAvoid = 0x280;
    }
    if ((camera->m_baTemporaryFlags & 0x1000u) != 0 && camera->m_GContactInOut.m_eContactStatus == 2) {
        position->x = savedX;
        position->y = savedY;
        position->z = savedZ;
    }
    if ((camera->m_ui8ProbeFlags & 1u) != 0) position->y = savedY;
    if ((camera->m_baTemporaryFlags & 0x200u) != 0) {
        // The push sphere touches something: the move from the last position loses its part against the push (at most
        // 2 dt of it), then the camera is pushed out by the depth less half the radius.
        float moveY = position->y - savedY;
        float moveX = position->x - savedX;
        float moveZ = position->z - savedZ;
        float pushY = Word(camera->m_unk770[1]);
        float pushX = Word(camera->m_unk770[0]);
        float pushZ = Word(camera->m_unk770[2]);
        float depth = Sqrtf(ppc::fmadds(pushZ, pushZ, ppc::fmadds(pushX, pushX, pushY * pushY)));
        if (depth == 0.0f) {
            depth = 0.0f;
        } else {
            const float inverse = kOne / depth;
            pushZ = pushZ * inverse;
            pushX = pushX * inverse;
            pushY = pushY * inverse;
        }
        const float along = ppc::fmadds(pushZ, moveZ, ppc::fmadds(pushX, moveX, pushY * moveY));
        if (along < 0.0f) {
            const float back = -along;
            float backY = pushY * back;
            float backX = pushX * back;
            float backZ = pushZ * back;
            float length = Sqrtf(ppc::fmadds(backZ, backZ, ppc::fmadds(backX, backX, backY * backY)));
            if (length != 0.0f) {
                const float inverse = kOne / length;
                backZ = backZ * inverse;
                backX = backX * inverse;
                backY = backY * inverse;
            } else {
                length = 0.0f;
            }
            float amount = dt + dt;
            if (!(length > amount)) amount = length;
            moveZ = ppc::fmadds(amount, backZ, moveZ);
            moveX = ppc::fmadds(amount, backX, moveX);
            moveY = ppc::fmadds(amount, backY, moveY);
        }
        const float x = savedX + moveX;
        const float y = savedY + moveY;
        const float z = savedZ + moveZ;
        position->x = x;
        position->y = y;
        position->z = z;
        const IKBoundingVolume* pushSphere = static_cast<const IKBoundingVolume*>(camera->m_pDodgeBSPushCam);
        const float out = ppc::fmadds(pushSphere->m_fRadius, kMinusHalf, depth);
        if (out > 0.0f) {
            position->z = ppc::fmadds(pushZ, out, z);
            position->x = ppc::fmadds(pushX, out, x);
            position->y = ppc::fmadds(pushY, out, y);
        }
    }
    // Far: the camera's own position beyond 1.2 times the farthest distance from the focus in x / z.
    bool farAway;
    {
        const float x = m_WorldPosition.x - center.x;
        const float z = m_WorldPosition.z - center.z;
        const float distance = Sqrtf(ppc::fmadds(x, x, z * z));
        farAway = distance > FarDistance(this, camera) * kFarFactor;
    }

    bool moving = true;  // the spring has not settled (or did not run)
    if ((camera->m_ui8ProbeFlags & 2u) != 0 && ((m_Flags & 0x10000u) == 0 || farAway)) {
        // The spring towards the wall-free point (+0x88c) from the current point (+0x894), in x / z.
        const float targetX = Word(camera->m_unk88c[0]);
        const float targetZ = Word(camera->m_unk88c[1]);
        float directionZ = targetZ - Word(camera->m_unk88c[3]);
        float directionX = targetX - Word(camera->m_unk88c[2]);
        float length = Sqrtf(ppc::fmadds(directionX, directionX, directionZ * directionZ));
        if (length == 0.0f) {
            length = 0.0f;
        } else {
            const float inverse = kOne / length;
            directionZ = directionZ * inverse;
            directionX = directionX * inverse;
        }
        camera->m_unk8a0[1] = length;
        const float stiffness = avoid.m_afValues[0];
        float damping = Sqrtf(stiffness);
        damping = damping + damping;
        float value = camera->m_unk8a0[1];
        const float offset = camera->m_unk8a0[0] - value;
        bool integrate = true;
        float accel = 0.0f;
        if (offset != 0.0f) {
            accel = ppc::fmsubs(stiffness, offset, damping * camera->m_unk8a0[2]);
        } else if (camera->m_unk8a0[2] == 0.0f) {
            integrate = false;  // at rest on the target
        } else {
            accel = camera->m_unk8a0[2] * -damping;
        }
        if (integrate) {
            float speed = ppc::fmadds(accel, dt, camera->m_unk8a0[2]);
            if (!farAway) {
                // (The original tests the member's address against null first: always true.)
                const float limit = m_fCameraMaxSpeed;
                if (speed <= -limit) {
                    speed = -limit;
                } else if (speed >= limit) {
                    speed = limit;
                }
            }
            value = ppc::fmadds(dt, speed, value);
            if (value <= 0.0f) {
                value = 0.0f;
            } else if (value >= kMaxSpringValue) {
                value = kMaxSpringValue;
            }
            if (ClearSignBit(speed) <= 0.0f && ClearSignBit(value - camera->m_unk8a0[0]) <= 0.0f) {
                value = camera->m_unk8a0[0];
                camera->m_unk8a0[2] = 0.0f;
                camera->m_unk8a0[1] = value;
            } else {
                camera->m_unk8a0[2] = speed;
                camera->m_unk8a0[1] = value;
            }
        }
        const float step = length - value;
        const float currentX = ppc::fmadds(step, directionX, Word(camera->m_unk88c[2]));
        const float currentZ = ppc::fmadds(step, directionZ, Word(camera->m_unk88c[3]));
        camera->m_unk88c[2] = Word(currentX);
        camera->m_unk88c[3] = Word(currentZ);
        const float gapX = ClearSignBit(currentX - Word(camera->m_unk88c[0]));
        if (!(gapX > kSettleDistance)) {
            const float gapZ = ClearSignBit(Word(camera->m_unk88c[3]) - Word(camera->m_unk88c[1]));
            if (!(gapZ > kSettleDistance) && ppc::fmadds(gapX, gapX, gapZ * gapZ) <= kSettleSquare) {
                camera->m_unk88c[2] = camera->m_unk88c[0];
                moving = false;
                camera->m_unk88c[3] = camera->m_unk88c[1];
            }
        }
        camera->SetPlayerCanMoveCamera(false);  // 0x0012ac08
        position->x = Word(camera->m_unk88c[2]);
        position->z = Word(camera->m_unk88c[3]);
    }

    float halfWidth;   // sp+0x74
    float halfHeight;  // sp+0x70
    GetHalfExtentsAtDistance(kOne, &halfWidth, &halfHeight);  // 0x00144278
    // (The original also takes the center-camera distance in x / z and in 3D here, with Math_Sqrtf, and never uses them.)
    const float radius = avoid.m_afValues[1];
    const float height = avoid.m_afValues[3];

    if (moving && !farAway) {
        // Near the focus: the camera slides along the walls from the last position.
        CLine line;  // sp+0xb8
        line.m_start.x = savedX;
        line.m_start.y = savedY;
        line.m_start.z = savedZ;
        line.m_VectDir.x = position->x - savedX;
        line.m_VectDir.y = position->y - savedY;
        line.m_VectDir.z = position->z - savedZ;
        CSlideGroundEdgeDatasOut out;  // sp+0xe8; the callee fills it when it answers 2 / 3
        const uint8_t result = collision->ResolveSweptCylinderWalls(&line, radius, height, &out, nullptr, &moveMasks, 1);
        if (result == 1) {
            position->x = savedX;
            position->z = savedZ;
            camera->m_ui8ProbeFlags = static_cast<uint8_t>((camera->m_ui8ProbeFlags & ~4u) | 4u);
        } else if (result == 0) {
            camera->m_ui8ProbeFlags = static_cast<uint8_t>(camera->m_ui8ProbeFlags & ~4u);
        } else if (result == 2 || result == 3) {
            position->x = position->x + out.m_v3BouncingVector.x;
            position->y = position->y + out.m_v3BouncingVector.y;
            position->z = position->z + out.m_v3BouncingVector.z;
            camera->m_ui8ProbeFlags = static_cast<uint8_t>((camera->m_ui8ProbeFlags & ~4u) | 4u);
        }
    }

    camera->m_ui8ProbeFlags = static_cast<uint8_t>(camera->m_ui8ProbeFlags & ~1u);
    if ((m_Flags & 0x10000u) == 0) {
        // A ground between the focus and the camera: the lines are lifted by the view's half height at distance 1.
        const float liftX = kAxisY.x * halfHeight;
        const float liftY = kAxisY.y * halfHeight;
        const float liftZ = kAxisY.z * halfHeight;
        CLine down;  // sp+0xa0: focus (lifted) -> camera
        down.m_VectDir.x = position->x - startX;
        down.m_VectDir.y = position->y - startY;
        down.m_VectDir.z = position->z - startZ;
        down.m_start.x = startX + liftX;
        down.m_start.y = startY + liftY;
        down.m_start.z = startZ + liftZ;
        CGroundEdgeDatasOut downHit;  // sp+0x138
        if (collision->RaycastWalls(&down, 0.0f, &downHit, 0, &groundMasks, 1) != 0) {  // 0x00198438
            const float t = downHit.m_ftLine;
            const float under = downHit.m_fHeightUnder - kWallTopMargin;
            const float hitY = ppc::fmadds(t, down.m_VectDir.y, down.m_start.y);
            const float hitX = ppc::fmadds(t, down.m_VectDir.x, down.m_start.x);
            const float hitZ = ppc::fmadds(t, down.m_VectDir.z, down.m_start.z);
            const float cameraX = position->x;
            const float cameraZ = position->z;
            const float cameraY = position->y;
            float overY = hitY - under;  // the wall's top
            float directionX = hitX - down.m_start.x;
            float directionZ = hitZ - down.m_start.z;
            float directionY = overY - down.m_start.y;
            float squareX = directionX * directionX;
            float squareZ = directionZ * directionZ;
            const float length = Sqrtf(ppc::fmadds(directionY, directionY, squareX) + squareZ);
            if (length != 0.0f) {
                const float inverse = kOne / length;
                directionZ = directionZ * inverse;
                directionX = directionX * inverse;
                directionY = directionY * inverse;
                squareZ = directionZ * directionZ;
                squareX = directionX * directionX;
            }
            const float horizontal = squareX + squareZ;
            // The point over the top at the camera's x / z distance from the center (sp+0x1b0 / +0x1b4).
            float overX;
            float overZ;
            if (horizontal != 0.0f) {
                const float toCenterZ = center.z - cameraZ;
                const float toCenterX = center.x - cameraX;
                overY = overY - halfHeight;
                const float scale = Sqrtf(ppc::fmadds(toCenterX, toCenterX, toCenterZ * toCenterZ) / horizontal);
                const float y = ppc::fmadds(directionY, scale, center.y);
                if (!(y < overY)) overY = y;
                overZ = ppc::fmadds(directionZ, scale, center.z);
                overX = ppc::fmadds(directionX, scale, center.x);
            } else {
                overY = overY - halfHeight;
                overZ = cameraZ;
                overX = cameraX;
            }
            const float currentY = position->y;
            if (!(overY < currentY)) overY = currentY;
            if ((downHit.m_ba8Infos & 1u) != 0 && !(focus->y < overY)) {
                overY = currentY;
                overX = position->x;
                overZ = position->z;
            } else {
                camera->m_ui8ProbeFlags = static_cast<uint8_t>((camera->m_ui8ProbeFlags & ~1u) | 1u);
            }
            // camera (lifted) -> focus
            CLine up;  // sp+0xd0
            up.m_start.x = position->x + liftX;
            up.m_start.y = position->y + liftY;
            up.m_start.z = position->z + liftZ;
            up.m_VectDir.x = startX - position->x;
            up.m_VectDir.y = startY - position->y;
            up.m_VectDir.z = startZ - position->z;
            CGroundEdgeDatasOut upHit;  // sp+0x170
            float frontX = cameraX;
            float frontY = cameraY;
            float frontZ = cameraZ;
            if (collision->RaycastWalls(&up, 0.0f, &upHit, 0, &groundMasks, 0) != 0) {
                const float u = upHit.m_ftLine;
                const float endX = up.m_start.x + up.m_VectDir.x;
                const float upHitX = ppc::fmadds(u, up.m_VectDir.x, up.m_start.x);
                const float upHitY = ppc::fmadds(u, up.m_VectDir.y, up.m_start.y);
                const float endY = up.m_start.y + up.m_VectDir.y;
                const float upUnder = upHit.m_fHeightUnder - kWallTopMargin;
                const float endZ = up.m_start.z + up.m_VectDir.z;
                const float upHitZ = ppc::fmadds(u, up.m_VectDir.z, up.m_start.z);
                float upDirectionX = upHitX - endX;
                const float upTop = upHitY - upUnder;
                float upDirectionZ = upHitZ - endZ;
                float upSquareX = upDirectionX * upDirectionX;
                float upDirectionY = upTop - endY;
                float upSquareZ = upDirectionZ * upDirectionZ;
                const float upLength = Sqrtf(ppc::fmadds(upDirectionY, upDirectionY, upSquareX) + upSquareZ);
                if (upLength != 0.0f) {
                    const float inverse = kOne / upLength;
                    upDirectionZ = upDirectionZ * inverse;
                    upDirectionX = upDirectionX * inverse;
                    upDirectionY = upDirectionY * inverse;
                    upSquareZ = upDirectionZ * upDirectionZ;
                    upSquareX = upDirectionX * upDirectionX;
                }
                const float upHorizontal = upSquareX + upSquareZ;
                if (upHorizontal != 0.0f) {
                    const float toCenterZ = center.z - cameraZ;
                    const float toCenterX = center.x - cameraX;
                    frontY = upTop - halfHeight;
                    const float scale = Sqrtf(ppc::fmadds(toCenterX, toCenterX, toCenterZ * toCenterZ) / upHorizontal);
                    const float y = ppc::fmadds(upDirectionY, scale, center.y);
                    if (!(y < frontY)) frontY = y;
                    frontZ = ppc::fmadds(upDirectionZ, scale, center.z);
                    frontX = ppc::fmadds(upDirectionX, scale, center.x);
                } else {
                    frontY = upTop - halfHeight;
                    frontZ = cameraZ;
                    frontX = cameraX;
                }
                const float upCurrentY = position->y;
                if (!(frontY < upCurrentY)) frontY = upCurrentY;
                if ((upHit.m_ba8Infos & 1u) != 0 && !(focus->y < frontY)) {
                    frontY = upCurrentY;
                    frontX = position->x;
                    frontZ = position->z;
                } else {
                    camera->m_ui8ProbeFlags = static_cast<uint8_t>((camera->m_ui8ProbeFlags & ~1u) | 1u);
                }
            }
            if (!(overY > frontY)) {
                position->x = overX;
                position->y = overY;
                position->z = overZ;
            } else {
                position->x = frontX;
                position->y = frontY;
                position->z = frontZ;
            }
        }
    }

    // The cylinder from the focus to the camera along the walls (then along the grounds' edges).
    CLine line;  // sp+0xb8
    line.m_start.x = startX;
    line.m_start.y = startY;
    line.m_start.z = startZ;
    line.m_VectDir.x = position->x - startX;
    line.m_VectDir.y = position->y - startY;
    line.m_VectDir.z = position->z - startZ;
    CSlideGroundEdgeDatasOut out;  // sp+0xe8
    // BUG(original): `prev` (sp+0x110) is an uninitialised stack record; the second slide below reads its bouncing
    // vector after a result 2, which the callee does not copy there (only 3 does). Zeroed here.
    CSlideGroundEdgeDatasOut prev = {};
    uint8_t result = collision->ResolveSweptCylinderWalls(&line, radius, height, &out, &prev, &wallMasks, 1);
    bool clearContact = false;
    if (result != 2 && result != 3) {
        result = collision->ResolveSweptCylinderWalls(&line, radius, height, &out, &prev, &groundMasks, 1);
        if (result == 2 || result == 3) {
            // A ground edge: ignored when its intersection is above the ground under the camera.
            const float intersection = out.m_fYOfIntersection;  // sp+0x108
            if ((camera->m_baTemporaryFlags & 0x800u) == 0 && camera->m_GContactInOut.m_eContactStatus != 3) {
                CVector3 world;  // sp+0x138
                GroundContact_GetWorldPoint(AsContact(&camera->m_GContactInOut), &world);  // 0x001a70e0
                if ((m_Flags & 0x1000u) != 0 && world.y < intersection) clearContact = true;
            }
        }
    }
    if (clearContact || result <= 1) {
        camera->m_ui8ProbeFlags = static_cast<uint8_t>(camera->m_ui8ProbeFlags & ~2u);
    } else if (result <= 3) {
        if (!farAway && !((camera->m_ui8ProbeFlags & 2u) != 0 && (m_Flags & 0x10000u) == 0)) {
            // A new wall contact: the spring starts at the camera, the wall-free point at most at the current distance.
            camera->m_unk88c[3] = Word(position->z);
            camera->m_unk88c[2] = Word(position->x);
            const float current = m_v2CurrentCameraOffset.m_fX;
            const float farthest = FarDistance(this, SrvCamera());
            camera->m_fUnk89c = farthest > current ? current : farthest;
            camera->m_unk8a0[1] = 0.0f;  // stw
            camera->m_unk8a0[2] = 0.0f;  // stw
        }
        // The wall-free point: the slid camera at +0x89c from the center in x / z, slid once more.
        const float slidZ = position->z + out.m_v3BouncingVector.z;
        const float slidX = position->x + out.m_v3BouncingVector.x;
        camera->m_unk88c[1] = Word(slidZ);
        camera->m_unk88c[0] = Word(slidX);
        float directionX = slidX - center.x;
        float directionZ = slidZ - center.z;
        const float keep = camera->m_fUnk89c;
        const float length = Sqrtf(ppc::fmadds(directionZ, directionZ, ppc::fmadds(directionX, directionX, 0.0f)));
        if (length != 0.0f) {
            const float scale = keep / length;
            directionZ = directionZ * scale;
            directionX = directionX * scale;
        }
        const float pointX = directionX + center.x;
        const float pointZ = directionZ + center.z;
        CLine toPoint;  // sp+0xb8
        toPoint.m_start.x = startX;
        toPoint.m_start.y = startY;
        toPoint.m_start.z = startZ;
        toPoint.m_VectDir.y = position->y - startY;
        toPoint.m_VectDir.x = pointX - startX;
        toPoint.m_VectDir.z = pointZ - startZ;
        const uint8_t slid = collision->ResolveSweptCylinderWalls(&toPoint, radius, height, &out, &prev, &wallMasks, 1);
        if (slid == 0) {
            camera->m_unk88c[1] = Word(pointZ);
            camera->m_unk88c[0] = Word(pointX);
        } else if (slid == 2 || slid == 3) {
            camera->m_unk88c[0] = Word(pointX + prev.m_v3BouncingVector.x);
            camera->m_unk88c[1] = Word(pointZ + prev.m_v3BouncingVector.z);
        }
        camera->m_ui8ProbeFlags = static_cast<uint8_t>((camera->m_ui8ProbeFlags & ~2u) | 2u);
    }

    // 0x14a788: without a wall contact, a ground between the focus' mid height and the camera takes the camera.
    if (((camera->m_ui8ProbeFlags >> 1) & 1u) != 0 || (m_Flags & 0x10000u) != 0) return;
    const float copyY = camera->m_v3FocusPosCopy.y;
    const float middleY = (startY + copyY) * kHalf;
    CLineCollisionDatas hit;  // sp+0xa0
    hit.m_i32FaceIndex = -1;
    hit.m_ui8SectorNumber = 0;
    hit.m_ftOnLine = kFloatMax;
    hit.m_pCollisionMesh = nullptr;
    CMasksOfGrdTypeForTests meshMasks;  // sp+0x138
    meshMasks.m_ui32GrdToTest = 1;
    meshMasks.m_ui32GrdToAvoid = 0x180;
    CLine toCamera;  // sp+0xb8
    toCamera.m_start.x = startX;
    toCamera.m_start.y = middleY;
    toCamera.m_start.z = startZ;
    toCamera.m_VectDir.z = position->z - startZ;
    toCamera.m_VectDir.x = position->x - startX;
    toCamera.m_VectDir.y = position->y - middleY;
    if (StackCount(camera) > 1) meshMasks.m_ui32GrdToAvoid = 0x280;
    if (!SrvCollision()->RaycastMeshes(&toCamera, &hit, 1, 0, &meshMasks)) return;  // 0x00197af8
    const float t = hit.m_ftOnLine;
    const float hitY = ppc::fmadds(t, toCamera.m_VectDir.y, toCamera.m_start.y);
    const uint32_t status = camera->m_GContactInOut.m_eContactStatus;
    float groundY;
    if (status == 0 || status == 2) {
        CVector3 world;  // sp+0xd0
        GroundContact_GetWorldPoint(AsContact(&camera->m_GContactInOut), &world);
        groundY = world.y;
    } else {
        groundY = position->y;
    }
    const ICollisionMesh* mesh = hit.m_pCollisionMesh;
    if ((mesh->m_ba16EngineFlags & 8u) == 0) {
        if (!(position->y <= hitY) && !(startY <= hitY)) return;
    } else {
        if (groundY < hitY && !(copyY >= hitY)) return;
        if (camera->m_GContactInOut.m_pGround == static_cast<const IKSerializable*>(mesh)) return;
    }
    const float z = ppc::fmadds(t, toCamera.m_VectDir.z, toCamera.m_start.z);
    const float x = ppc::fmadds(t, toCamera.m_VectDir.x, toCamera.m_start.x);
    camera->m_baTemporaryFlags = (camera->m_baTemporaryFlags & ~0x4000u) | 0x4000u;
    camera->m_baTemporaryFlags = (camera->m_baTemporaryFlags & ~0x800u) | 0x800u;
    m_fRecenterTimer = kFloatMax;
    position->z = z;
    position->x = x;
    position->y = hitY;
}
