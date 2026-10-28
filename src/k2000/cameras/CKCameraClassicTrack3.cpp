// CKCameraClassicTrack3.cpp - reconstructed original translation unit 0x1579a0-0x165a08 (GAME_TOC1, main_toc1), 44 functions, 40 live.
// Primary class: CKCameraClassicTrack3  key 0x387  category Camera  size 0x318  vtable 0xb1aa50
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x1579a0  CKCameraClassicTrack3_Delete
//   [x] 0x1579f0  CKCameraClassicTrack3_ResetState_maybe
//   [x] 0x157b48  CKCameraClassicTrack3_Pause  (empty: Pause)
//   [x] 0x157b50  CKCameraClassicTrack3_Resume  (empty: Resume)
//   [ ] 0x157b58  CKCameraClassicTrack3_StepSmoothedPosition_maybe  [dead]
//   [ ] 0x157ca0  RegisterCKCameraClassicTrack3Class
//   [ ] 0x157d18  _GLOBAL__I_157d18
//   [ ] 0x157d28  CKCameraClassicTrack3_ApplyPositionAndTarget_maybe  [dead]
//   [x] 0x157e50  CKCameraClassicTrack3_ResolveWallMovement_maybe
//   [ ] 0x158100  CKCameraClassicTrack3_ProbeCollisionDistance_maybe  [dead]
//   [ ] 0x1582b0  FUN_001582b0  [dead]
//   [x] 0x158428  CKCameraClassicTrack3_Deactivate_maybe
//   [x] 0x158460  CKCameraClassicTrack3_PostLoad
//   [ ] 0x158488  CKCameraClassicTrack3_Save
//   [ ] 0x1584b0  CKCameraClassicTrack3_RecursiveRegistration
//   [ ] 0x1584d8  CKCameraClassicTrack3_Destroy
//   [x] 0x158500  CKCameraClassicTrack3_Construct
//   [x] 0x158568  CKCameraClassicTrack3_DeleteArray
//   [ ] 0x158608  CKCameraClassicTrack3_BaseDestructor
//   [ ] 0x158638  CKCameraClassicTrack3_DeletingDestructor
//   [ ] 0x158680  CKCameraClassicTrack3_Destructor
//   [ ] 0x1586b0  CKCameraClassicTrack3_Construct_2
//   [x] 0x158718  CKCameraClassicTrack3_CreateArray
//   [x] 0x158808  CKCameraClassicTrack3_Create
//   [x] 0x158880  CKCameraClassicTrack3_Load
//   [x] 0x1592e0  CKCameraClassicTrack3_ComputeFocusPoint_maybe
//   [x] 0x159720  CKCameraClassicTrack3_ApplyPushSphereContact_maybe
//   [x] 0x159950  CKCameraClassicTrack3_BuildFrustumPlanes_maybe
//   [x] 0x159ec0  CKCameraClassicTrack3_UpdateFramingAndPlaceCamera_maybe
//   [x] 0x15a690  CKCameraClassicTrack3_IntegrateSplitFollowSpring_maybe
//   [x] 0x15aa10  CKCameraClassicTrack3_IntegrateFollowSpring_maybe
//   [x] 0x15acf0  CKCameraClassicTrack3_UpdateFollowOffsets_maybe
//   [x] 0x15b000  CKCameraClassicTrack3_FindGroundContact_maybe
//   [x] 0x15c0d8  CKCameraClassicTrack3_ConstrainOrbitAnglesToVolume_maybe
//   [x] 0x15c800  CKCameraClassicTrack3_TestCameraObstruction_maybe
//   [x] 0x15ce68  CKCameraClassicTrack3_ApplyRightStick_maybe
//   [x] 0x15ddc0  CKCameraClassicTrack3_ComputeDesiredPose_maybe
//   [x] 0x15f520  CKCameraClassicTrack3_CaptureBlendStart_maybe
//   [x] 0x15fa00  CKCameraClassicTrack3_ConstrainFollowToVolume_maybe
//   [x] 0x1615c8  CKCameraClassicTrack3_UpdateSteady_maybe
//   [x] 0x162910  CKCameraClassicTrack3_FindAndRepairOcclusion_maybe
//   [x] 0x163dc0  CKCameraClassicTrack3_Activate_maybe
//   [x] 0x164448  CKCameraClassicTrack3_UpdateBlending_maybe
//   [x] 0x1653c0  CKCameraClassicTrack3_Update_maybe
//
//   [ ] 0x9a7cb0  CKCameraClassicTrack3_IsKindOfClass  [inline]
//   [ ] 0x9a7cd8  CKCameraClassicTrack3_GetClassType  [inline]
//   [ ] 0x9a7ce0  CKCameraClassicTrack3_GetClassID  [inline]
//   [x] 0x9a7ce8  CKCameraClassicTrack3_vf84  [inline]
//   [x] 0x9a7cf0  CKCameraClassicTrack3_vf8C  [inline]
//   [x] 0x9a7cf8  CKCameraClassicTrack3_vf90  [inline]
//   [x] 0x9a7d00  CKCameraClassicTrack3_vf6C  [inline]
//   [x] 0x9a7d08  CKCameraClassicTrack3_SetFov  [inline]
//   [x] 0x9a7d10  CKCameraClassicTrack3_vf80  [inline]
//   [x] 0x9a7d18  CKCameraClassicTrack3_vf94  [inline]
//   [x] 0x9a7d28  CKCameraClassicTrack3_vfB0  [inline]
//   [x] 0x9a7d30  CKCameraClassicTrack3_vfB4  [inline]
//   [x] 0x9a7d38  CKCameraConstraint_ComputeLookDirection_maybe  [inline]  (mode 0 with an object STUB)
#include "k2000/cameras/CKCameraClassicTrack3.h"

#include <cfloat>
#include <cmath>
#include <cstring>

#include "Spyro2008/logic/CKS08GameManager.h"
#include "crt/ppc_ops.h"
#include "crt/xatan.h"
#include "crt/xsinf.h"
#include "crt/xtanf.h"
#include "k2000/cameras/CKSrvCamera.h"
#include "k2000/cameras/CameraContext.h"
#include "k2000/core/Stub.h"
#include "k2000/hooks/GroundContact.h"
#include "k2000/io/IKFile.h"
#include "k2000/logic/ai/CKFlaggedPath.h"
#include "k2000/logic/ai/CKMarkerBeacon.h"
#include "k2000/logic/math/IKPath.h"
#include "k2000/logic/cameras/CKCameraConstraint.h"
#include "k2000/logic/physics/CGround.h"
#include "k2000/math/Vec3.h"
#include "k2000/misc/Engine.h"
#include "k2000/misc/FloatApproach.h"
#include "k2000/scenegraph/IKBoundingVolume.h"
#include "k2000/services/CKSrvCollision.h"
#include "k2000/services/CollisionDatas.h"
#include "k2000/services/ICollisionMesh.h"
#include "k2000/system/CTimeManager.h"
#include "k2000/system/IKTime.h"

namespace {

// The shared axes and the null vector (0x00c50d40 / 0x00c50d64; filled by static initialisers in the original).
const CVector3 kAxisY = {0.0f, 1.0f, 0.0f};
const CVector3 kNullVector = {0.0f, 0.0f, 0.0f};
// The word at 0x00c4acb8 + 0x28 (FLT_MAX), read through a TOC pointer.
constexpr float kFloatMax = FLT_MAX;
constexpr float kPi = 0x1.921fb6p+1f;      // TOC -0x37b8 0x40490fdb
constexpr float kMinusPi = -0x1.921fb6p+1f;  // TOC -0x37b4 0xc0490fdb
constexpr float kTwoPi = 0x1.921fb6p+2f;   // TOC -0x3888 0x40c90fdb
constexpr float kDegToRad = 0x1.1df468p-6f;  // TOC -0x383c 0x3c8efa34

CKSrvCamera* SrvCamera() { return static_cast<CKSrvCamera*>(g_pEngine->m_srvCamera); }

// 0x00010690 Math_Sqrtf (fsqrts).
inline float Sqrtf(float x) { return std::sqrt(x); }

inline bool SignBitSet(float x) {
    int32_t bits;
    std::memcpy(&bits, &x, 4);
    return bits < 0;
}
// The inlined cosf / sinf: the single-precision polynomials for a non-negative argument (by its sign bit), the
// library's cosf 0x009a11d8 / sinf 0x009a1390 of the magnitude otherwise (the sine negated).
inline float GameCosf(float x) { return SignBitSet(x) ? crt::LibCosf(-x) : crt::InlineCosf(x); }
inline float GameSinf(float x) { return SignBitSet(x) ? -crt::LibSinf(-x) : crt::InlineSinf(x); }

// The camera service's focus targets (the stack entries +0xd08, 0x30 each; their count is the byte +0xdfb) and their
// parameter records (+0xc40, 0x14 each, chosen by the entry's byte +0x04).
uint32_t StackCount(const CKSrvCamera* camera) { return camera->m_ui32NbStacked & 0xffu; }
const CKSrvCamera::StackEntry& StackAt(const CKSrvCamera* camera, uint32_t index) { return camera->m_aStack[index]; }
float StackRecord(const CKSrvCamera* camera, const CKSrvCamera::StackEntry& entry, uint32_t word) {
    return IKCamera::AsFloat(camera->m_unkc40[entry.m_unk04][word]);
}
// The entry's position (+0x24; the service writes the target's position there).
const float* StackPosition(const CKSrvCamera::StackEntry& entry) { return entry.m_unk24; }

// The constraint zone's fields the track reads (CKCameraConstraint, the COLL family's class).
uint32_t ZoneFlags(const CKCameraConstraint* zone) { return IKCamera::AsWord(zone->m_unk20); }        // +0x20
uint32_t ZoneLookMode(const CKCameraConstraint* zone) { return (zone->m_unk1c >> 5) & 3u; }          // +0x1c bits 5-6
float ZoneYawRange(const CKCameraConstraint* zone) { return zone->m_afUnk44[1]; }                    // +0x48
float ZonePitch(const CKCameraConstraint* zone) { return zone->m_afUnk44[2]; }                       // +0x4c
float ZoneFocusPitchScale(const CKCameraConstraint* zone) { return zone->m_afUnk44[3]; }             // +0x50
float ZoneFramingScale(const CKCameraConstraint* zone) { return zone->m_afUnk44[4]; }                // +0x54
float ZoneBlendTimeScale(const CKCameraConstraint* zone) { return zone->m_afUnk44[5]; }               // +0x58
float ZoneBlendTimeScaleAlt(const CKCameraConstraint* zone) { return zone->m_afUnk44[6]; }           // +0x5c
float ZoneSideOffset(const CKCameraConstraint* zone) { return zone->m_afUnk44[11]; }                 // +0x70
float ZoneUpOffset(const CKCameraConstraint* zone) { return IKCamera::AsFloat(zone->m_unk74); }      // +0x74
float ZoneFov(const CKCameraConstraint* zone) { return zone->m_unk78; }                              // +0x78
float ZonePitchUp(const CKCameraConstraint* zone) { return zone->m_afUnk80[1]; }                     // +0x84
float ZonePitchDown(const CKCameraConstraint* zone) { return zone->m_afUnk80[2]; }                   // +0x88
float ZoneUnk44(const CKCameraConstraint* zone) { return zone->m_afUnk80[4]; }                       // +0x90
float ZoneUnk48(const CKCameraConstraint* zone) { return zone->m_afUnk80[5]; }                       // +0x94
float ZoneUnk4c(const CKCameraConstraint* zone) { return zone->m_afUnk80[6]; }                       // +0x98

}  // namespace

// The collision / constraint helpers (COLL family).
namespace {

float ZoneVolumeYawAccel(const CKCameraConstraint* zone) { return zone->m_afUnk44[7]; }        // +0x60

float ZoneVolumeYawMaxSpeed(const CKCameraConstraint* zone) { return zone->m_afUnk44[8]; }     // +0x64

float ZoneVolumeYawDecel(const CKCameraConstraint* zone) { return zone->m_afUnk44[9]; }        // +0x68

float ZoneYawRangeExtra(const CKCameraConstraint* zone) { return zone->m_afUnk80[0]; }         // +0x80

constexpr float kSearchStep = 0x1.921fb6p-3f;  // TOC -0x37ac 0x3e490fdb (pi / 16)
constexpr float kProbeHeight = 0x1.99999ap-5f;  // TOC -0x3840 0x3d4ccccd (0.05)

CKSrvCollision* SrvCollision() { return static_cast<CKSrvCollision*>(g_pEngine->m_srvCollision); }

// The camera's avoiding datas of the track (m_ui8CameraAvoidingSystemIndex): [1] the cylinder radius, [2] the height
// of the obstruction probes above the focus, [3] the cylinder height (the original indexes +0x3c0 + 16 * index).
const CKSrvCamera::SCameraAvoidingDatas& AvoidingDatas(const CKSrvCamera* camera, const IKCamera* track) {
    return camera->m_asAvoidingDatas[track->m_ui8CameraAvoidingSystemIndex];
}

// The obstruction hit as the original resets it before every probe (the word at 0x00c4acb8 + 0x28: FLT_MAX).
void ResetObstructionHit(CLineCollisionDatas* hit) {
    hit->m_ftOnLine = FLT_MAX;
    hit->m_i32FaceIndex = -1;
    hit->m_ui8SectorNumber = 0;
    hit->m_pCollisionMesh = nullptr;
}

// The probe sequence TestCameraObstruction and ResolveViewObstructions repeat inline: the obstruction hit reset, then
// the cylinder swept against the walls (`sweep`: a radius) or the line against them (`walls`: no radius), then the
// line against the grounds (RaycastMeshes bit 0). The first that answers gives the hit time on the line.
bool ProbeObstruction(CKCameraClassicTrack3* track, const CLine* line, float radius, bool sweep, bool walls,
                      const CMasksOfGrdTypeForTests* masks, float* time) {
    CKSrvCollision* collision = SrvCollision();
    ResetObstructionHit(&track->m_obstructionHit);
    if (sweep && collision->SweepCylinderAgainstWalls(line, radius, kProbeHeight, &track->m_wallHit, 0, masks, 1) != 0) {
        *time = track->m_wallHit.m_ftLine;
        return true;
    }
    if (walls && collision->RaycastWalls(line, kProbeHeight, &track->m_wallHit, 0, masks, 1) != 0) {
        *time = track->m_wallHit.m_ftLine;
        return true;
    }
    if (collision->RaycastMeshes(line, &track->m_obstructionHit, 1, 0, masks) != 0) {
        *time = track->m_obstructionHit.m_ftOnLine;
        return true;
    }
    return false;
}

constexpr float kMargin = 0.01f;              // TOC -0x37f0 0x3c23d70a

// The sign bit cleared (rlwinm r0,r0,0,1,31 on the stored word).
inline float ClearSignBit(float x) {
    uint32_t bits;
    std::memcpy(&bits, &x, 4);
    bits &= 0x7fffffffu;
    std::memcpy(&x, &bits, 4);
    return x;
}

// The camera service's contact copies are the XXL2 types' twins (same layout): the contact helpers take the XXL2 ones.
const ::CGroundContactDatasInOut* AsContact(const CKSrvCamera::CGroundContactDatasInOut* contact) {
    return reinterpret_cast<const ::CGroundContactDatasInOut*>(contact);
}

// The ground's engine flags (ICollisionMesh +0x36): bit 3 (0x8) _maybe a ceiling (the camera is put under it).
uint32_t GroundFlags(const IKSerializable* ground) { return static_cast<const ICollisionMesh*>(ground)->m_ba16EngineFlags; }

// The pitch from `to` to the point: asin of the normalised y difference (the length y^2, then x^2, then z^2 fused; not
// normalised when it is 0). Inlined eight times in 0x15b000.
float PitchAngle(float x, float y, float z, const CVector3& to) {
    float dy = y - to.y;
    const float dx = x - to.x;
    const float dz = z - to.z;
    const float length = Sqrtf(ppc::fmadds(dz, dz, ppc::fmadds(dx, dx, dy * dy)));
    if (length != 0.0f) dy = dy * (1.0f / length);
    return crt::Asinf(dy);  // TocBridge_Math_Asinf_maybe
}

// The ground point under the camera (status 2, a static ground or a moving one: along its world matrix's up axis).
void PlaceAlongGroundUp(IKSerializable* ground, bool dynamic, float distance, const CVector3& world, CVector3* out) {
    if (!dynamic) {
        out->y = distance + world.y;
        return;
    }
    const CMatrix34* matrix = static_cast<ICollisionMesh*>(ground)->GetWorldMatrix();  // vt+0x50
    out->x = ppc::fmadds(distance, matrix->m_up.x, world.x);
    out->y = ppc::fmadds(distance, matrix->m_up.y, world.y);
    out->z = ppc::fmadds(distance, matrix->m_up.z, world.z);
}

// The end of 0x15b000 (0x15b270): the pitch limits the probe left open (m_pitchMinA at -FLT_MAX, m_pitchMaxA at FLT_MAX)
// are found with a vertical line from the camera (down for the minimum, up for the maximum); while m_trackFlags bit 20
// (0x100000: the camera is held at a ground, m_groundPoint) stays set, the limits of before the call come back.
void FinishPitchLimits(CKCameraClassicTrack3* track, CKSrvCollision* collision, const CVector3* target, CVector3* position,
                       float savedPitchMin, float savedPitchMax, float clearance, float halfHeight) {
    CLineCollisionDatas hit;  // sp+0xb8
    hit.m_ftOnLine = kFloatMax;
    hit.m_ui8SectorNumber = 0;
    hit.m_pCollisionMesh = nullptr;
    hit.m_i32FaceIndex = -1;
    bool toMinimumLine = false;  // 0x15b540
    if ((track->m_trackFlags & 0x100000u) != 0) {
        // The camera was held at a ground: the hold ends when the ground point is far from the line target -> camera
        // (the squared distance over m_distance above 0.5).
        const float ty = target->y;
        float dy = position->y - ty;
        const float tx = target->x;
        float dx = position->x - tx;
        const float tz = target->z;
        float dz = position->z - tz;
        const CVector3& ground = track->m_groundPoint;
        const float gx = ground.x;
        const float gy = ground.y;
        const float gz = ground.z;
        const float length = Sqrtf(ppc::fmadds(dz, dz, ppc::fmadds(dx, dx, dy * dy)));
        if (length != 0.0f) {
            const float inverse = 1.0f / length;
            dz = dz * inverse;
            dx = dx * inverse;
            dy = dy * inverse;
        }
        const float along = ppc::fmadds(gz - tz, dz, ppc::fmadds(gx - tx, dx, (gy - ty) * dy));
        float cy = ppc::fmadds(along, dy, target->y);
        float cx = ppc::fmadds(along, dx, target->x);
        float cz = ppc::fmadds(along, dz, target->z);
        cy = cy - ground.y;
        cx = cx - ground.x;
        cz = cz - ground.z;
        const float ratio = ppc::fmadds(cz, cz, ppc::fmadds(cx, cx, cy * cy)) / track->m_distance;
        if (ratio > 0.5f) {  // TOC -0x3838
            track->m_trackFlags &= ~0x100000u;
            // (0x15b530: savedPitchMin > m_pitchMinA goes through the bit test just cleared: both reach 0x15b540.)
            toMinimumLine = true;
        }
    }
    float minPitch = track->m_pitchMinA;
    if (!toMinimumLine) {
        if (!(savedPitchMin <= minPitch) && (track->m_trackFlags & 0x100000u) != 0) {
            track->m_pitchMinA = savedPitchMin;
        } else {
            toMinimumLine = true;
        }
    }
    if (toMinimumLine && -kFloatMax == minPitch && !(savedPitchMin == minPitch)) {
        CLine down;  // sp+0xc8
        down.m_start.x = position->x;
        down.m_start.y = position->y;
        down.m_start.z = position->z;
        down.m_VectDir.x = -kAxisY.x;
        down.m_VectDir.y = -kAxisY.y;
        down.m_VectDir.z = -kAxisY.z;
        if (collision->RaycastMeshes(&down, &hit, 1, 0, nullptr)) {  // 0x00197af8
            const float up = clearance - hit.m_ftOnLine;
            const float y = ppc::fmadds(up, kAxisY.y, position->y);
            const float x = ppc::fmadds(up, kAxisY.x, position->x);
            const float z = ppc::fmadds(up, kAxisY.z, position->z);
            track->m_pitchMinA = PitchAngle(x, y, z, track->m_WorldTarget);
        }
    }
    // 0x15b2c0
    const float maxPitch = track->m_pitchMaxA;
    if (!(savedPitchMax >= maxPitch) && (track->m_trackFlags & 0x100000u) != 0) {
        track->m_pitchMaxA = savedPitchMax;
        return;
    }
    if (!(kFloatMax == maxPitch) || savedPitchMax == maxPitch) return;
    CLine upLine;  // sp+0xc8
    upLine.m_start.x = position->x;
    upLine.m_start.y = position->y;
    upLine.m_start.z = position->z;
    upLine.m_VectDir.x = kAxisY.x;
    upLine.m_VectDir.y = kAxisY.y;
    upLine.m_VectDir.z = kAxisY.z;
    if (!collision->RaycastMeshes(&upLine, &hit, 1, 0, nullptr)) return;
    const float up = (hit.m_ftOnLine - halfHeight) - kMargin;
    const float y = ppc::fmadds(up, kAxisY.y, position->y);
    const float x = ppc::fmadds(up, kAxisY.x, position->x);
    const float z = ppc::fmadds(up, kAxisY.z, position->z);
    track->m_pitchMaxA = PitchAngle(x, y, z, track->m_WorldTarget);
}

}  // namespace

// 0x00157e50 CKCameraClassicTrack3_ResolveWallMovement_maybe: the camera's cylinder (the avoiding datas' radius [1] and
// height [3]) moved from -> to against the walls (ResolveSweptCylinderWalls). m_trackFlags bits 2 / 3 (0x4 / 0x8) tell
// on which side of the camera (its real x axis) the wall pushed it: 0x8 the move goes along +x, 0x4 along -x; a free
// move clears both. A slide or push (2, 3) moves `to` by the bouncing vector and, with m_Flags 0x10000 and no stick
// zoom (m_zoomStickMaxSpeed 0), keeps the distance in m_wallDistance; result 1 (not returned by the ported
// ResolveSweptCylinderWalls) leaves the camera at `from`.
void CKCameraClassicTrack3::ResolveWallMovement(const CVector3* from, CVector3* to) {
    CKSrvCamera* camera = SrvCamera();
    CLine line;
    line.m_start.x = from->x;
    line.m_start.y = from->y;
    line.m_start.z = from->z;
    line.m_VectDir.z = to->z - from->z;
    line.m_VectDir.x = to->x - from->x;
    line.m_VectDir.y = to->y - from->y;
    const CKSrvCamera::SCameraAvoidingDatas& avoid = AvoidingDatas(camera, this);
    CSlideGroundEdgeDatasOut out;  // stack; the callee fills it when it answers 2 / 3
    const uint8_t result = SrvCollision()->ResolveSweptCylinderWalls(&line, avoid.m_afValues[1], avoid.m_afValues[3], &out,
                                                                     nullptr, nullptr, 1);
    if (result == 1) {
        const CVector3& axis = camera->m_v3RealAxisX;
        const float side = ppc::fmadds(line.m_VectDir.z, axis.z,
                                       ppc::fmadds(line.m_VectDir.x, axis.x, line.m_VectDir.y * axis.y));
        if (side > 0.0f) {
            m_trackFlags = (m_trackFlags & ~0xcu) | 0x8u;
        } else if (side < 0.0f) {
            m_trackFlags = (m_trackFlags | 0x4u) & ~0x8u;
        }
        to->z = from->z;
        to->x = from->x;
        to->y = from->y;
        return;
    }
    if (result == 0) {
        m_trackFlags &= ~0xcu;
        return;
    }
    if (result > 3) return;
    // 2 slid, 3 pushed out.
    const CVector3& axis = camera->m_v3RealAxisX;
    const float side = ppc::fmadds(line.m_VectDir.z, axis.z,
                                   ppc::fmadds(line.m_VectDir.x, axis.x, line.m_VectDir.y * axis.y));
    if (side > 0.0f) {
        m_trackFlags = (m_trackFlags & ~0xcu) | 0x8u;
    } else if (side < 0.0f) {
        m_trackFlags = (m_trackFlags | 0x4u) & ~0x8u;
    }
    if ((m_Flags & 0x10000u) != 0 && m_zoomStickMaxSpeed == 0.0f) m_wallDistance = m_distance;
    to->x = to->x + out.m_v3BouncingVector.x;
    to->y = to->y + out.m_v3BouncingVector.y;
    to->z = to->z + out.m_v3BouncingVector.z;
}

// 0x00158808 CKCameraClassicTrack3_Create (the constructor inlined)
CKCameraClassicTrack3::CKCameraClassicTrack3() {
    m_obstructionHit.m_ftOnLine = 0x1.fffffep+127f;  // the word at 0x00c4acb8 + 0x28 (FLT_MAX)
    m_obstructionHit.m_ui8SectorNumber = 0;
    m_obstructionHit.m_i32FaceIndex = -1;
    m_obstructionHit.m_pCollisionMesh = nullptr;
}

namespace {
using ParamField = float CKCameraClassicTrack3::*;
// The parameter words in the order the Load reads them.
constexpr ParamField kClassicTrack3LoadOrder[35] = {
    &CKCameraClassicTrack3::m_param5c,           &CKCameraClassicTrack3::m_pitchAccel,          // +0x5c +0x60
    &CKCameraClassicTrack3::m_pitchDecel,        &CKCameraClassicTrack3::m_pullInAccel,         // +0x64 +0x68
    &CKCameraClassicTrack3::m_pullInMaxSpeed,    &CKCameraClassicTrack3::m_minDistance,         // +0x6c +0x88
    &CKCameraClassicTrack3::m_maxDistance,       &CKCameraClassicTrack3::m_leadAtMinDistance,   // +0x8c +0x90
    &CKCameraClassicTrack3::m_leadAtMaxDistance, &CKCameraClassicTrack3::m_defaultDistance,     // +0x94 +0x98
    &CKCameraClassicTrack3::m_followStiffness,   &CKCameraClassicTrack3::m_followDamping,       // +0x70 +0x74
    &CKCameraClassicTrack3::m_followAccelFixed,  &CKCameraClassicTrack3::m_followDampingFixed,  // +0x78 +0x7c
    &CKCameraClassicTrack3::m_followStiffnessUp, &CKCameraClassicTrack3::m_followDampingUp,     // +0x80 +0x84
    &CKCameraClassicTrack3::m_param9c,           &CKCameraClassicTrack3::m_yawStickAccel,       // +0x9c +0xa0
    &CKCameraClassicTrack3::m_yawStickDecel,     &CKCameraClassicTrack3::m_yawStickMaxSpeed,    // +0xa4 +0xa8
    &CKCameraClassicTrack3::m_zoomStickAccel,    &CKCameraClassicTrack3::m_zoomStickDecel,      // +0xac +0xb0
    &CKCameraClassicTrack3::m_zoomStickMaxSpeed, &CKCameraClassicTrack3::m_paramD0,             // +0xb4 +0xd0
    &CKCameraClassicTrack3::m_paramD4,           &CKCameraClassicTrack3::m_paramD8,             // +0xd4 +0xd8
    &CKCameraClassicTrack3::m_stickPitchMin,     &CKCameraClassicTrack3::m_stickPitchMax,       // +0xb8 +0xbc
    &CKCameraClassicTrack3::m_pitchReturnSpeed,  &CKCameraClassicTrack3::m_pitchStickMaxSpeed,  // +0xcc +0xc0
    &CKCameraClassicTrack3::m_pitchStickAccel,   &CKCameraClassicTrack3::m_pitchStickDecel,     // +0xc4 +0xc8
    &CKCameraClassicTrack3::m_paramDC,           &CKCameraClassicTrack3::m_paramE0,             // +0xdc +0xe0
    &CKCameraClassicTrack3::m_paramE4,                                                          // +0xe4
};
}  // namespace

// 0x00158880 CKCameraClassicTrack3_Load: 35 reads of one word each, every word swapped.
int32_t CKCameraClassicTrack3::Load(IKFile* file, int32_t type) {
    BaseLoad(file, type);
    if (type == K_LEVEL_PLATEFORMS) {
        for (ParamField field : kClassicTrack3LoadOrder) ReadF32LE(file, &(this->*field));
    }
    return 1;
}

// 0x00158460 CKCameraClassicTrack3_PostLoad: KStub_Return1_144570 (IKCamera's PostLoad, which returns 1), then 1.
int32_t CKCameraClassicTrack3::PostLoad(int32_t /*type*/) {
    return 1;
}

// 0x00158428 CKCameraClassicTrack3_Deactivate_maybe: CKCamera_StopAttachedFx_maybe (0x144238), then the current field of
// view back to the loaded one.
// STUB(C2.7, the FX service): CKCamera_StopAttachedFx_maybe is CKSrvFx_StopCameraFx_maybe 0x1affd8 on the attached fx (+0x50).
void CKCameraClassicTrack3::Stop() {
    if (m_unk50 != nullptr) DOTD_STUB_ONCE("CKCamera_StopAttachedFx_maybe: CKSrvFx_StopCameraFx_maybe 0x1affd8 (C2.7)");
    m_unk18 = m_fFov;
}

// 0x001579f0 CKCameraClassicTrack3_ResetState_maybe
void CKCameraClassicTrack3::ResetState() {
    m_pullInSpeed = 0.0f;
    m_pitchMinA = -kFloatMax;
    m_pitchMaxA = kFloatMax;
    m_pitchMinB = -kFloatMax;
    m_pitchMaxB = kFloatMax;
    m_pitch.m_accel = m_pitchAccel;
    m_pitch.m_decel = m_pitchDecel;
    m_pitch.m_maxSpeed = kTwoPi;
    m_pitch.m_speedBonus = 0.0f;
    m_followSpeedXZ = 0.0f;
    m_followSpeedY = 0.0f;
    m_pitch.m_speed = 0.0f;
    m_Flags &= ~0x10000u;
    m_trackFlags &= 0xffdabadfu & 0xfff5d52fu;
    m_yawStickSpeed = 0.0f;
    m_zoomStickSpeed = 0.0f;
    m_framingScaleTarget = 1.0f;
    m_stickPitch = m_pitch.m_current;
    m_framingScale = 1.0f;
    m_pitchStickSpeed = 0.0f;
    m_focusHeightOffset = 0.0f;
    m_obstructionOffset = 0.0f;
    m_obstructionPoint = kNullVector;
    m_obstructionTime = 0.0f;
    m_unk1c4 = kNullVector;
    m_zoneOffset = kNullVector;
    m_zoneOffsetTarget = kNullVector;
    m_blendSpeed = 0.0f;
    m_blendDuration = -1.0f;
    m_volumeYawSpeed = 0.0f;
    m_volumeYaw = 0.0f;
    m_volumeYawRange = 0.0f;
    m_wallDistance = -1.0f;
}

// The snap the track makes when the focus jumps (ComputeFocusPoint, UpdateFramingAndPlaceCamera, UpdateSteady, inlined
// in each): the default distance behind the target along the view direction, the track started again there (vt+0x50:
// Start, a full reset) and the camera service's calculation pose and heading lock taken from it.
void CKCameraClassicTrack3::SnapBehindTarget() {
    CKSrvCamera* camera = SrvCamera();
    m_distance = m_defaultDistance;
    const float back = -m_defaultDistance;
    m_WorldPosition.z = ppc::fmadds(back, m_viewDir.z, m_WorldTarget.z);
    m_WorldPosition.x = ppc::fmadds(back, m_viewDir.x, m_WorldTarget.x);
    m_WorldPosition.y = ppc::fmadds(back, m_viewDir.y, m_WorldTarget.y);
    Start(&m_WorldPosition);
    camera->SetCalculationPose(&m_WorldPosition, &m_WorldTarget);
    camera->CaptureHeroHeadingLock();
}

// 0x001592e0 CKCameraClassicTrack3_ComputeFocusPoint_maybe: the weighted mean of the camera service's focus targets
// (x / z weighted by record[2] * entry[1]; y and the pitch only over the entries without the flag +0x0c, y raised by
// record[0] * entry[2], the pitch record[1] * entry[0] scaled by the zone's +0x50 when its flag 8 is set), then the
// zone's side offset (along the service's real x axis without a blend, else along m_right) and up offset, and
// m_focusHeightOffset. With no target x and z are 0 / 0. A jump of more than 15 units while the service's stack
// changed (+0x46c bit 0x800000) snaps the camera.
void CKCameraClassicTrack3::ComputeFocusPoint(CVector3* focus) {
    CKSrvCamera* camera = SrvCamera();
    const uint32_t count = StackCount(camera);
    float pitchScale = 1.0f;
    if (m_pConstraint != nullptr && (ZoneFlags(m_pConstraint) & 0x8u) != 0) pitchScale = ZoneFocusPitchScale(m_pConstraint);
    float z = kNullVector.z;
    float x = kNullVector.x;
    float y = kNullVector.y;
    focus->x = x;
    focus->y = y;
    focus->z = z;
    float pitch;
    if (count != 0) {
        float weightSum = 0.0f;
        float heightWeightSum = 0.0f;
        pitch = 0.0f;
        for (uint32_t i = 0; i < count; ++i) {
            const CKSrvCamera::StackEntry& entry = StackAt(camera, i);
            const float* position = StackPosition(entry);
            const float weight = StackRecord(camera, entry, 2) * entry.m_unk10[1];
            float height = 0.0f;
            z = ppc::fmadds(position[2], weight, z);
            x = ppc::fmadds(position[0], weight, x);
            weightSum = weightSum + weight;
            if (entry.m_unk0c == 0) {
                const float raised = ppc::fmadds(StackRecord(camera, entry, 0), entry.m_unk10[2], position[1]);
                float entryPitch = weight * StackRecord(camera, entry, 1);
                heightWeightSum = heightWeightSum + weight;
                entryPitch = entryPitch * entry.m_unk10[0];
                height = raised * weight;
                pitch = ppc::fmadds(pitchScale, entryPitch, pitch);
            }
            y = height + y;
            focus->x = x;
            focus->z = z;
            focus->y = y;
        }
        z = z / weightSum;
        focus->z = z;
        x = x / weightSum;
        focus->x = x;
        if (heightWeightSum != 0.0f) {
            pitch = pitch / heightWeightSum;
            focus->y = y / heightWeightSum;
        }
    } else {
        pitch = 0.0f;
        focus->z = z / 0.0f;
        focus->x = x / 0.0f;
    }
    if (m_pConstraint != nullptr) {
        float fx = focus->x;
        float fz = focus->z;
        const float side = ZoneSideOffset(m_pConstraint);
        float fy = focus->y + ZoneUpOffset(m_pConstraint);
        if (side != 0.0f) {
            const CVector3& axis = (m_blendDuration == -1.0f) ? camera->m_v3RealAxisX : m_right;
            fz = ppc::fmadds(side, axis.z, fz);
            fx = ppc::fmadds(side, axis.x, fx);
            fy = ppc::fmadds(side, axis.y, fy);
        }
        focus->x = fx;
        focus->y = fy;
        focus->z = fz;
    }
    focus->y = focus->y + m_focusHeightOffset;
    m_desiredPitch = pitch;
    if ((camera->m_baTemporaryFlags & 0x800000u) != 0) {
        const float dy = focus->y - m_WorldTarget.y;
        const float dx = focus->x - m_WorldTarget.x;
        const float dz = focus->z - m_WorldTarget.z;
        const float distanceSq = ppc::fmadds(dz, dz, ppc::fmadds(dx, dx, dy * dy));
        if (distanceSq > 225.0f) {
            m_WorldTarget.x = focus->x;
            m_WorldTarget.z = focus->z;
            m_WorldTarget.y = focus->y;
            m_prevFocus.x = focus->x;
            m_prevFocus.z = focus->z;
            m_prevFocus.y = focus->y;
            SnapBehindTarget();
        }
    }
}

// 0x00159720 CKCameraClassicTrack3_ApplyPushSphereContact_maybe (r4 not read): while the camera service's push
// sphere touches something (m_baTemporaryFlags 0x200; the service's +0x770 is the push vector, its length the depth),
// the move m_WorldPosition -> position loses its part against the push direction (at most 2 dt of it), then the
// position is moved out along the push by its depth less half the push sphere's radius. 1 when it ran.
uint8_t CKCameraClassicTrack3::PushOutOfConstraintPlane(float dt, CVector3* position) {
    CKSrvCamera* camera = SrvCamera();
    if ((camera->m_baTemporaryFlags & 0x200u) == 0) return 0;
    float moveX = position->x - m_WorldPosition.x;
    float moveY = position->y - m_WorldPosition.y;
    float moveZ = position->z - m_WorldPosition.z;
    float pushX = AsFloat(camera->m_unk770[0]);
    float pushY = AsFloat(camera->m_unk770[1]);
    float pushZ = AsFloat(camera->m_unk770[2]);
    float depth = Sqrtf(ppc::fmadds(pushZ, pushZ, ppc::fmadds(pushX, pushX, pushY * pushY)));
    if (depth == 0.0f) {
        depth = 0.0f;
    } else {
        const float inverse = 1.0f / depth;
        pushZ = pushZ * inverse;
        pushX = pushX * inverse;
        pushY = pushY * inverse;
    }
    const float along = ppc::fmadds(moveZ, pushZ, ppc::fmadds(moveX, pushX, moveY * pushY));
    if (along < 0.0f) {
        // The move goes into the push: take back up to 2 dt of it along the push.
        const float back = -along;
        float backY = pushY * back;
        float backX = back * pushX;
        float backZ = pushZ * back;
        float length = Sqrtf(ppc::fmadds(backZ, backZ, ppc::fmadds(backX, backX, backY * backY)));
        if (length == 0.0f) {
            length = 0.0f;
        } else {
            const float inverse = 1.0f / length;
            backZ = backZ * inverse;
            backX = backX * inverse;
            backY = backY * inverse;
        }
        float step = dt + dt;
        if (!(length > step)) step = length;
        moveZ = ppc::fmadds(step, backZ, moveZ);
        moveX = ppc::fmadds(step, backX, moveX);
        moveY = ppc::fmadds(step, backY, moveY);
    }
    const float x = m_WorldPosition.x + moveX;
    const float y = m_WorldPosition.y + moveY;
    const float z = m_WorldPosition.z + moveZ;
    position->x = x;
    position->y = y;
    position->z = z;
    const IKBoundingVolume* pushSphere = static_cast<const IKBoundingVolume*>(camera->m_pDodgeBSPushCam);
    const float out = ppc::fmadds(pushSphere->m_fRadius, -0.5f, depth);
    if (out > 0.0f) {
        position->z = ppc::fmadds(pushZ, out, z);
        position->x = ppc::fmadds(out, pushX, x);
        position->y = ppc::fmadds(pushY, out, y);
    }
    return 1;
}

// 0x00159950 CKCameraClassicTrack3_BuildFrustumPlanes_maybe: m_viewDir normalised, then the six planes of the framing
// frustum at the camera position: 0 the camera plane at m_minDistance (normal -view), 1 the plane at m_maxDistance
// (normal view), 2..5 the sides through the corners of the near rectangle (the half extents tan(fov / 2) * 0.75 and
// tan(fov / 2) / (height / width * 4 / 3), times m_minDistance). u = y x view (z x view looking almost straight up or
// down), w = view x u.
void CKCameraClassicTrack3::BuildFrustumPlanes(const CVector3* position) {
    CKSrvCamera* camera = SrvCamera();
    const float tanHalf = crt::Tanf(m_fov.m_target * kDegToRad * 0.5f);
    const float aspect = camera->m_pCameraContext->m_fHeightOverWidth * 1.3333334f;
    const float nearDistance = m_minDistance;
    const float extentA = tanHalf * 0.75f;
    const float lengthSq = ppc::fmadds(m_viewDir.z, m_viewDir.z, ppc::fmadds(m_viewDir.x, m_viewDir.x, m_viewDir.y * m_viewDir.y));
    const float extentB = tanHalf / aspect;
    const float cornerA = extentA * nearDistance;           // f18
    const float cornerB = extentB * nearDistance;           // f29
    const float cornerMinusA = nearDistance * -extentA;     // f17
    const float cornerMinusB = nearDistance * -extentB;     // f19
    const float length = Sqrtf(lengthSq);
    if (length != 0.0f) {
        const float inverse = 1.0f / length;
        m_viewDir.z = inverse * m_viewDir.z;
        m_viewDir.x = inverse * m_viewDir.x;
        m_viewDir.y = inverse * m_viewDir.y;
    }
    float ux;  // f28
    float uy;  // f26
    float uz;  // f27
    if (std::fabs(m_viewDir.y) >= 0.99939084f) {
        uy = -m_viewDir.x;
        ux = m_viewDir.y;
        const float l = Sqrtf(ppc::fmadds(ux, ux, uy * uy) + 0.0f);
        if (l != 0.0f) {
            const float inverse = 1.0f / l;
            uz = inverse * -0.0f;
            ux = ux * inverse;
            uy = uy * inverse;
        } else {
            uz = -0.0f;
        }
    } else {
        ux = m_viewDir.z;
        uy = 0.0f;
        uz = -m_viewDir.x;
        const float l = Sqrtf(ppc::fmadds(uz, uz, ppc::fmadds(ux, ux, 0.0f)));
        if (l != 0.0f) {
            const float inverse = 1.0f / l;
            uz = uz * inverse;
            ux = ux * inverse;
            uy = inverse * uy;
        }
    }
    const float vx = m_viewDir.x;
    const float vy = m_viewDir.y;
    const float vz = m_viewDir.z;
    const float px = position->x;
    const float py = position->y;
    const float pz = position->z;
    const float nearY = nearDistance * vy;  // f20
    const float nearX = nearDistance * vx;  // f21
    const float nearZ = nearDistance * vz;  // f22
    const float wy = ppc::fmsubs(vz, ux, vx * uz);  // f24
    const float wz = ppc::fmsubs(vx, uy, vy * ux);  // f25
    const float wx = ppc::fmsubs(vy, uz, vz * uy);  // f23
    float* plane = m_frustumPlanes[0];
    // Plane 0: the camera plane at the near distance.
    const float c1x = ppc::fmadds(cornerB, ux, nearX);
    const float c1y = ppc::fmadds(cornerB, uy, nearY);
    const float c1z = ppc::fmadds(cornerB, uz, nearZ);
    plane[1] = -vy;
    plane[0] = -vx;
    plane[2] = -vz;
    float dot = (nearY + py) * plane[1];
    dot = ppc::fmadds(nearX + px, plane[0], dot);
    float nz = ppc::fmsubs(c1y, wx, c1x * wy);  // f29
    float nx = ppc::fmsubs(c1z, wy, c1y * wz);  // f30
    float ny = ppc::fmsubs(c1x, wz, c1z * wx);  // f31
    plane[3] = ppc::fnmadds(nearZ + pz, plane[2], dot);
    float sum = ny * ny;
    // Plane 1: at the farDistance distance.
    plane = m_frustumPlanes[1];
    const float farDistance = m_maxDistance;
    plane[1] = vy;
    float farY = ppc::fmadds(farDistance, vy, py);
    plane[0] = vx;
    sum = ppc::fmadds(nx, nx, sum);
    const float farX = ppc::fmadds(farDistance, vx, px);
    plane[2] = vz;
    const float farZ = ppc::fmadds(farDistance, vz, pz);
    farY = farY * plane[1];
    sum = ppc::fmadds(nz, nz, sum);
    plane[3] = ppc::fnmadds(farZ, plane[2], ppc::fmadds(farX, plane[0], farY));
    float l = Sqrtf(sum);
    if (l != 0.0f) {
        const float inverse = 1.0f / l;
        nz = nz * inverse;
        nx = nx * inverse;
        ny = ny * inverse;
    }
    // Plane 2.
    {
        const float c4 = ppc::fmadds(cornerMinusB, ux, nearX);
        const float c5 = ppc::fmadds(cornerMinusB, uz, nearZ);
        const float c6 = ppc::fmadds(cornerMinusB, uy, nearY);
        plane = m_frustumPlanes[2];
        plane[1] = ny;
        plane[0] = nx;
        plane[2] = nz;
        const float d = ppc::fmadds(plane[0], px, plane[1] * py);
        ny = ppc::fmsubs(c5, wx, c4 * wz);
        nx = ppc::fmsubs(c6, wz, c5 * wy);
        nz = ppc::fmsubs(c4, wy, c6 * wx);
        plane[3] = ppc::fnmadds(plane[2], pz, d);
        sum = ppc::fmadds(nz, nz, ppc::fmadds(nx, nx, ny * ny));
        l = Sqrtf(sum);
        if (l != 0.0f) {
            const float inverse = 1.0f / l;
            nz = nz * inverse;
            nx = nx * inverse;
            ny = ny * inverse;
        }
    }
    // Plane 3.
    {
        const float c4 = ppc::fmadds(cornerA, wx, nearX);
        const float c5 = ppc::fmadds(cornerA, wz, nearZ);
        const float c6 = ppc::fmadds(cornerA, wy, nearY);
        plane = m_frustumPlanes[3];
        plane[1] = ny;
        plane[0] = nx;
        plane[2] = nz;
        const float d = ppc::fmadds(plane[0], px, plane[1] * py);
        ny = ppc::fmsubs(c5, ux, c4 * uz);
        nx = ppc::fmsubs(c6, uz, c5 * uy);
        nz = ppc::fmsubs(c4, uy, c6 * ux);
        plane[3] = ppc::fnmadds(plane[2], pz, d);
        sum = ppc::fmadds(nz, nz, ppc::fmadds(nx, nx, ny * ny));
        l = Sqrtf(sum);
        if (l != 0.0f) {
            const float inverse = 1.0f / l;
            nz = nz * inverse;
            nx = nx * inverse;
            ny = ny * inverse;
        }
    }
    // Plane 4.
    {
        const float c5 = ppc::fmadds(cornerMinusA, wz, nearZ);
        const float c6 = ppc::fmadds(cornerMinusA, wx, nearX);
        const float c4 = ppc::fmadds(cornerMinusA, wy, nearY);
        plane = m_frustumPlanes[4];
        plane[1] = ny;
        plane[0] = nx;
        plane[2] = nz;
        const float d = ppc::fmadds(plane[0], px, plane[1] * py);
        ny = ppc::fmsubs(c6, uz, c5 * ux);
        nz = ppc::fmsubs(c4, ux, c6 * uy);
        nx = ppc::fmsubs(c5, uy, c4 * uz);
        plane[3] = ppc::fnmadds(plane[2], pz, d);
        sum = ppc::fmadds(nz, nz, ppc::fmadds(nx, nx, ny * ny));
        l = Sqrtf(sum);
        if (l != 0.0f) {
            const float inverse = 1.0f / l;
            nz = nz * inverse;
            nx = nx * inverse;
            ny = ny * inverse;
        }
    }
    // Plane 5.
    plane = m_frustumPlanes[5];
    plane[1] = ny;
    plane[0] = nx;
    plane[2] = nz;
    plane[3] = ppc::fnmadds(plane[2], pz, ppc::fmadds(plane[0], px, plane[1] * py));
}

// The framing test of one focus target (the sphere at x, y, z of `radius`) against the planes 5, 4, 3, 2 and 0 (plane 1,
// the far one, is evaluated and skipped): for each plane the sphere crosses (-radius < distance), radius + distance,
// divided by tan(fov / 2) for the side planes; 0 for the planes 4 and 5 without a blend while the camera service's flag
// 0x4000000 is set. The largest one (at least 0).
float CKCameraClassicTrack3::FramingPush(float x, float y, float z, float radius) const {
    float best = 0.0f;
    const float minusRadius = -radius;
    for (int32_t k = 5; k >= 0; --k) {
        const float* plane = m_frustumPlanes[k];
        const float distance = ppc::fmadds(z, plane[2], ppc::fmadds(x, plane[0], y * plane[1])) + plane[3];
        if (minusRadius >= distance) continue;
        if (k == 1) continue;
        float push;
        if (m_blendDuration == -1.0f && (SrvCamera()->m_baTemporaryFlags & 0x4000000u) != 0 &&
            static_cast<uint32_t>(k - 4) <= 1) {
            push = 0.0f;
        } else {
            push = radius + distance;
            if (k != 0) push = push / crt::Tanf(m_fov.m_target * kDegToRad * 0.5f);
        }
        if (!(push < best)) best = push;
    }
    return best;
}

// 0x00159ec0 CKCameraClassicTrack3_UpdateFramingAndPlaceCamera_maybe: the frustum planes at `position`; unless the
// framing is off (m_trackFlags 0x8000), the framing scale approaches its target (0.5 while the stick moves the camera
// and the zoom speed limit is positive, else 1; up by dt / 4, down at once), every framed focus target (entry byte +0x05)
// pushes the camera back as far as its sphere needs (radius: entry +0x08, or record[3] when -1; times entry[3], the
// zone's +0x54 and the scale), the push limited to 20 * dt while the follow spring is fixed (0x200) or 0x800 holds;
// the camera placed at the target - (m_distance + push) * view. A push larger than the distance with flag 0x100000 snaps
// the camera (returns 1). Returns push > 0.5.
uint8_t CKCameraClassicTrack3::UpdateFramingAndPlaceCamera(float dt, CVector3* position) {
    CKSrvCamera* camera = SrvCamera();
    BuildFrustumPlanes(position);
    uint32_t flags = m_trackFlags;
    if ((flags & 0x8000u) != 0) return 0;
    const bool stickActive = (m_Flags & 0x10000u) != 0;
    if (stickActive || (flags & 0x40u) != 0) {
        if (!(m_zoomStickMaxSpeed <= 0.0f)) m_framingScaleTarget = 0.5f;
        const float current = m_framingScale;
        const float target = m_framingScaleTarget;
        if (!(current >= target)) {
            const float next = ppc::fmadds(dt, 0.25f, current);
            m_framingScale = next;
            if (next > target) m_framingScale = target;
        } else {
            m_framingScale = target;
        }
    } else {
        m_framingScaleTarget = 1.0f;
        const float current = m_framingScale;
        const float target = m_framingScaleTarget;
        if (current < target) {
            const float next = ppc::fmadds(dt, 0.25f, current);
            m_framingScale = next;
            if (next > target) m_framingScale = target;
        } else {
            m_framingScale = target;
        }
    }
    float push = 0.0f;
    if (StackCount(camera) != 0) {
        for (uint32_t i = 0; (i & 0xffu) < StackCount(camera); ++i) {
            const CKSrvCamera::StackEntry& entry = StackAt(camera, i & 0xffu);
            if (entry.m_unk05 == 0) continue;
            const float* entryPosition = StackPosition(entry);
            float radius = entry.m_unk08;
            const float y = ppc::fmadds(StackRecord(camera, entry, 4), entry.m_unk10[2], entryPosition[1]);
            const float x = entryPosition[0];
            const float z = entryPosition[2];
            if (radius == -1.0f) radius = StackRecord(camera, entry, 3);
            radius = radius * entry.m_unk10[3];
            float scale;
            CKCameraConstraint* zone = m_pConstraint;
            if (zone == nullptr) {
                scale = m_framingScale;
            } else if ((ZoneFlags(zone) & 0x10u) != 0) {
                if ((m_trackFlags & 0x100u) != 0 && !(ZoneFramingScale(zone) <= 1.0f)) {
                    scale = m_framingScale;
                    const float limit = 1.0f / ZoneFramingScale(zone);
                    m_framingScaleTarget = limit;
                    if (scale > limit) {
                        scale = limit;
                        m_framingScale = limit;
                    }
                } else {
                    scale = m_framingScale;
                }
                radius = radius * ZoneFramingScale(zone);
            } else if ((ZoneFlags(zone) & 0x20000u) != 0) {
                if ((m_trackFlags & 0x100u) != 0 && ZoneFramingScale(zone) > 1.0f) {
                    scale = m_framingScale;
                    const float limit = radius * scale / ZoneFramingScale(zone);
                    m_framingScaleTarget = limit;
                    if (scale > limit) {
                        scale = limit;
                        m_framingScale = limit;
                    }
                } else {
                    scale = m_framingScale;
                }
                radius = ZoneFramingScale(zone);
            } else {
                scale = m_framingScale;
            }
            const float entryPush = FramingPush(x, y, z, radius * scale);
            // The original runs the plane loop a second time (the same values) when the push is the largest so far.
            if (!(entryPush < push)) push = entryPush;
        }
        flags = m_trackFlags;
    }
    if ((flags & 0x800u) != 0 && push == 0.0f) {
        if ((SrvCamera()->m_baTemporaryFlags & 0x4000000u) == 0) m_trackFlags = (m_trackFlags & ~0x1000u) | 0x1000u;
    } else {
        m_trackFlags &= ~0x1000u;
    }
    flags = m_trackFlags;
    if ((flags & 0x200u) != 0 || (flags & 0x800u) != 0) {
        const float limit = dt * 20.0f;
        if (limit < push) push = limit;
    }
    float distance = m_distance;
    if ((flags & 0x100000u) != 0 && distance < push) {
        m_prevFocus.x = m_WorldTarget.x;
        m_prevFocus.y = m_WorldTarget.y;
        m_prevFocus.z = m_WorldTarget.z;
        SnapBehindTarget();
        position->z = m_WorldPosition.z;
        position->x = m_WorldPosition.x;
        position->y = m_WorldPosition.y;
        return 1;
    }
    distance = push + distance;
    const float back = -distance;
    m_distance = distance;
    position->z = ppc::fmadds(back, m_viewDir.z, m_WorldTarget.z);
    position->x = ppc::fmadds(back, m_viewDir.x, m_WorldTarget.x);
    position->y = ppc::fmadds(back, m_viewDir.y, m_WorldTarget.y);
    if (push > 0.0f) {
        if ((m_trackFlags & 0x200u) == 0) m_pullInSpeed = 0.0f;
        if (m_zoomStickSpeed < 0.0f) m_zoomStickSpeed = 0.0f;
    }
    return push > 0.5f ? 1 : 0;
}

// 0x0015b000 CKCameraClassicTrack3_FindGroundContact_maybe (vt+0x78, the override of IKCamera 0x1461a0): the camera
// position kept out of the grounds, and the pitch limits m_pitchMinA / m_pitchMaxA from the grounds above and under it
// (the pitch from the focus m_WorldTarget to the clearance point: asin of the normalised y). The camera service's ground
// probe (+0x6c8 / +0x6d8) looks within the view's half height at distance 1 (GetHalfExtentsAtDistance); the clearance is
// that half height, at least the camera's radius (Vf80 = m_param5c) + 0.01.
// - No ground: farther than 35 from the focus outside a zone with flag 0x200 the camera snaps behind it; else the probe
//   again from the last position (m_WorldPosition): found, the camera goes back there; not found and no zone, it goes
//   back there and moves along the view direction by m_pullInMaxSpeed * dt (the framing scale target 0.5).
// - A ground with flag 8 (_maybe a ceiling): the maximum pitch from it; the camera goes h + 0.01 under it (status 0
//   always, other statuses only when m_fdH is below |position.y - target.y|).
// - Status 0 / 1: the minimum pitch from the clearance point above the ground; the camera is raised to it.
// - Status 2: as IKCamera's (the second probe under the ground, the target's line to the ceiling point), with the pitch.
// A camera put at a ground sets m_trackFlags bit 20 (0x100000) and m_groundPoint. The service's m_baTemporaryFlags bits
// 0x800 / 0x1000 as in IKCamera_FindGroundContact_maybe.
void CKCameraClassicTrack3::ResolveCameraCollision(const CVector3* target, CVector3* position) {
    const float savedPitchMin = m_pitchMinA;  // f21
    m_pitchMinA = -kFloatMax;
    CKSrvCamera* camera = SrvCamera();
    CKSrvCollision* collision = static_cast<CKSrvCollision*>(g_pEngine->m_srvCollision);
    CKSrvCamera::CGroundContactDatasIn* in = &camera->m_GContactIn;
    CKSrvCamera::CGroundContactDatasInOut* contact = &camera->m_GContactInOut;
    const float savedPitchMax = m_pitchMaxA;  // f20
    m_pitchMaxA = kFloatMax;
    float halfWidth;   // sp+0x70 (not used)
    float halfHeight;  // sp+0x78
    GetHalfExtentsAtDistance(1.0f, &halfWidth, &halfHeight);  // 0x00144278
    CVector3 probe;  // sp+0x84
    probe.x = position->x;
    probe.y = position->y;
    probe.z = position->z;
    float clearance = halfHeight;          // f22
    const float radius = Vf80() + kMargin;  // vt+0x80
    if (!(clearance > radius)) clearance = radius;
    const float dy = probe.y - m_WorldPosition.y;
    if (dy < -0.01f) {  // TOC -0x37ec 0xbc23d70a
        in->m_fObjectHeight = halfHeight - dy;
        float above = dy + halfHeight;
        if (above < 0.0f) above = 0.0f;
        in->m_fDeltaMax = above;
    } else {
        const float above = dy + halfHeight;
        probe.y = m_WorldPosition.y;
        in->m_fDeltaMax = 0.0f;  // stw 0
        in->m_fObjectHeight = above;
    }
    collision->GroundProbePoints(in, contact, &probe.x, 1);  // 0x00196540
    const uint32_t status = contact->m_eContactStatus;
    if (status == 3) {
        // No ground under the camera.
        if (m_distance > 35.0f && (m_pConstraint == nullptr || (ZoneFlags(m_pConstraint) & 0x200u) == 0)) {  // TOC -0x37e8
            // Too far from the focus: the snap behind it (as in UpdateSteady).
            m_prevFocus.x = m_WorldTarget.x;
            m_prevFocus.z = m_WorldTarget.z;
            m_prevFocus.y = m_WorldTarget.y;
            SnapBehindTarget();
            position->z = m_WorldPosition.z;
            position->x = m_WorldPosition.x;
            position->y = m_WorldPosition.y;
            return;
        }
        collision->GroundProbePoints(in, contact, &m_WorldPosition.x, 1);
        if (contact->m_eContactStatus != 3) {
            position->z = m_WorldPosition.z;
            position->x = m_WorldPosition.x;
            position->y = m_WorldPosition.y;
        } else if (m_pConstraint == nullptr) {
            position->x = m_WorldPosition.x;
            position->y = m_WorldPosition.y;
            const float vy = m_WorldTarget.y - m_WorldPosition.y;
            const float vx = m_WorldTarget.x - m_WorldPosition.x;
            position->z = m_WorldPosition.z;
            const float vz = m_WorldTarget.z - m_WorldPosition.z;
            m_viewDir.x = vx;
            m_viewDir.y = vy;
            m_viewDir.z = vz;
            const float length = Sqrtf(ppc::fmadds(vz, vz, ppc::fmadds(vx, vx, vy * vy)));
            if (length != 0.0f) {
                const float inverse = 1.0f / length;
                m_viewDir.z = inverse * m_viewDir.z;
                m_viewDir.x = inverse * m_viewDir.x;
                m_viewDir.y = inverse * m_viewDir.y;
            }
            const float dt = g_pEngine->m_timeManager->m_pTime->m_afDeltaTime[IKTime::SCALABLE_GAME_TIME];  // +0x48 -> +0x04 -> +0x1c
            const float step = m_pullInMaxSpeed * dt;
            position->z = ppc::fmadds(step, m_viewDir.z, position->z);
            position->x = ppc::fmadds(step, m_viewDir.x, position->x);
            position->y = ppc::fmadds(step, m_viewDir.y, position->y);
            m_framingScaleTarget = 0.5f;  // TOC -0x3838
        }
        FinishPitchLimits(this, collision, target, position, savedPitchMin, savedPitchMax, clearance, halfHeight);
        return;
    }
    camera->SetPlayerCanMoveCamera(true);  // 0x0012ac08
    IKSerializable* ground = contact->m_pGround;
    CVector3 world;  // sp+0x9c
    if (((GroundFlags(ground) >> 3) & 1u) != 0) {
        // A ceiling (_maybe): the maximum pitch from h + 0.01 under it.
        GroundContact_GetWorldPoint(AsContact(contact), &world);  // 0x001a70e0
        world.y = world.y - (halfHeight + kMargin);
        m_pitchMaxA = PitchAngle(world.x, world.y, world.z, m_WorldTarget);
        bool push = true;
        if (status != 0) {
            const float distance = ClearSignBit(position->y - target->y);
            push = contact->m_fdH < distance;
        }
        if (push) {
            position->y = world.y;
            m_trackFlags = (m_trackFlags & ~0x100000u) | 0x100000u;
            m_groundPoint.x = position->x;
            m_groundPoint.z = position->z;
            m_groundPoint.y = position->y;
            camera->m_baTemporaryFlags = (camera->m_baTemporaryFlags & ~0x800u) | 0x800u;
        } else {
            camera->m_baTemporaryFlags &= ~0x800u;
        }
        camera->m_baTemporaryFlags &= ~0x1000u;
        FinishPitchLimits(this, collision, target, position, savedPitchMin, savedPitchMax, clearance, halfHeight);
        return;
    }
    GroundContact_GetWorldPoint(AsContact(contact), &world);
    world.y = clearance + world.y;
    m_pitchMinA = PitchAngle(world.x, world.y, world.z, m_WorldTarget);
    if (status <= 1) {
        // On the ground or just above it: the camera raised to the clearance point.
        if ((camera->m_ui8ProbeFlags & 1u) != 0) clearance = kMargin;
        if (position->y <= world.y) {
            position->y = world.y;
            m_trackFlags = (m_trackFlags & ~0x100000u) | 0x100000u;
            m_groundPoint.x = position->x;
            m_groundPoint.z = position->z;
            m_groundPoint.y = position->y;
            camera->m_baTemporaryFlags = (camera->m_baTemporaryFlags & ~0x800u) | 0x800u;
            camera->m_baTemporaryFlags = (camera->m_baTemporaryFlags & ~0x1000u) | 0x1000u;
        } else {
            camera->m_baTemporaryFlags &= ~0x1800u;
        }
    } else if (status == 2) {
        // Within the object height of the ground.
        const bool dynamic = static_cast<ICollisionMesh*>(ground)->GetClassID() == 0x13;  // vt+0x18: CDynamicGround
        GroundContact_GetWorldPoint(AsContact(contact), &world);
        if ((camera->m_baTemporaryFlags & 1u) == 0 && target->y >= world.y) {
            PlaceAlongGroundUp(ground, dynamic, clearance, world, position);
            m_trackFlags = (m_trackFlags & ~0x100000u) | 0x100000u;
            m_groundPoint.x = position->x;
            m_groundPoint.z = position->z;
            m_groundPoint.y = position->y;
            camera->m_baTemporaryFlags = (camera->m_baTemporaryFlags & ~0x800u) | 0x800u;
            camera->m_baTemporaryFlags = (camera->m_baTemporaryFlags & ~0x1000u) | 0x1000u;
            m_pitchMinA = PitchAngle(position->x, position->y, position->z, m_WorldTarget);
        } else {
            // The target is under the ground (or the service's bit 0): a second probe h + 0.01 under the ground's point.
            CKSrvCamera::CGroundContactDatasInOut below;  // sp+0xf8 (only these four members are set)
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
            in->m_fDeltaMax = halfHeight * 0.1f;  // TOC -0x37f4 0x3dcccccd
            collision->GroundProbePoints(in, &below, &probe.x, 1);
            if (below.m_eContactStatus != 3 && (GroundFlags(below.m_pGround) & 0x8u) != 0) {
                CVector3 ceiling;  // sp+0x90
                GroundContact_GetWorldPoint(AsContact(&below), &ceiling);
                ceiling.y = ceiling.y - (halfHeight + kMargin);
                const float targetY = target->y;
                if (below.m_eContactStatus != 0 || !(targetY > ceiling.y)) {
                    // The target must see the point under the ceiling.
                    CLineCollisionDatas hit;  // sp+0xa8
                    hit.m_i32FaceIndex = -1;
                    hit.m_ftOnLine = kFloatMax;
                    hit.m_ui8SectorNumber = 0;
                    hit.m_pCollisionMesh = nullptr;
                    CMasksOfGrdTypeForTests masks;  // sp+0x7c
                    masks.m_ui32GrdToTest = 1;
                    masks.m_ui32GrdToAvoid = 0x80;
                    CLine line;  // sp+0xe0
                    line.m_start.x = target->x;
                    line.m_start.y = targetY;
                    line.m_start.z = target->z;
                    line.m_VectDir.y = ceiling.y - targetY;
                    line.m_VectDir.x = ceiling.x - target->x;
                    line.m_VectDir.z = ceiling.z - target->z;
                    if (!collision->RaycastMeshes(&line, &hit, 1, 1, &masks)) {  // 0x00197af8
                        position->z = ceiling.z;
                        position->x = ceiling.x;
                        position->y = ceiling.y;
                        CopyGroundContact(*reinterpret_cast<::CGroundContactDatasInOut*>(contact), *AsContact(&below));
                        m_pitchMaxA = PitchAngle(position->x, position->y, position->z, m_WorldTarget);
                        camera->m_baTemporaryFlags &= ~0x1000u;
                        camera->m_baTemporaryFlags = (camera->m_baTemporaryFlags & ~0x800u) | 0x800u;
                        FinishPitchLimits(this, collision, target, position, savedPitchMin, savedPitchMax, clearance,
                                          halfHeight);
                        return;
                    }
                }
            }
            PlaceAlongGroundUp(ground, dynamic, clearance, world, position);
            m_pitchMinA = PitchAngle(position->x, position->y, position->z, m_WorldTarget);
            camera->m_baTemporaryFlags = (camera->m_baTemporaryFlags & ~0x1000u) | 0x1000u;
            camera->m_baTemporaryFlags = (camera->m_baTemporaryFlags & ~0x800u) | 0x800u;
        }
    }
    FinishPitchLimits(this, collision, target, position, savedPitchMin, savedPitchMax, clearance, halfHeight);
}

// 0x0015c0d8 CKCameraClassicTrack3_ConstrainOrbitAnglesToVolume_maybe: m_blendEnd's angles (ComputeDesiredPose, with
// the zone's flag 0x200) re-derived from the orbit position at distance 5 kept inside the zone's volume: the distance,
// the pitch and the yaw (unwrapped about m_blendStart's yaw) of focus - that position. When the volume moved the point
// and the track's zone (m_pConstraint, not the argument) is not in look mode 2, m_zoneOffsetTarget becomes the move
// along the orbit direction that puts the volume's point level with the focus (the focus' projection on that line,
// minus the focus); otherwise it is cleared. The position buffer (r4) is not used.
void CKCameraClassicTrack3::ConstrainOrbitAnglesToVolume(CVector3* /*position*/, const CVector3* focus,
                                                         CKCameraConstraint* constraint) {
    uint8_t constrained;
    const CVector3 orbit =
        CameraVolume_ComputeConstrainedSphericalPosition(m_blendEnd.m_yaw, m_blendEnd.m_pitch, 5.0f, constraint, focus, &constrained);
    m_zoneOffsetTarget.x = kNullVector.x;
    m_zoneOffsetTarget.y = kNullVector.y;
    m_zoneOffsetTarget.z = kNullVector.z;
    if (constrained != 0 && ZoneLookMode(m_pConstraint) != 2) {
        const float yaw = m_blendEnd.m_yaw;
        const float pitch = m_blendEnd.m_pitch;
        float dirX = GameSinf(yaw);
        dirX = dirX * GameCosf(pitch);
        float dirZ = GameCosf(yaw);
        dirZ = dirZ * GameCosf(pitch);
        const float dirY = -GameSinf(pitch);
        const float dy = focus->y - orbit.y;
        const float dx = focus->x - orbit.x;
        const float dz = focus->z - orbit.z;
        const float along = ppc::fmadds(dirZ, dz, ppc::fmadds(dirX, dx, dirY * dy));
        const float pz = ppc::fmadds(dirZ, along, orbit.z);
        const float px = ppc::fmadds(dirX, along, orbit.x);
        const float py = ppc::fmadds(dirY, along, orbit.y);
        m_zoneOffsetTarget.z = pz - focus->z;
        m_zoneOffsetTarget.x = px - focus->x;
        m_zoneOffsetTarget.y = py - focus->y;
    }
    // The angles from the volume's point (not moved by the offset above, which moves the focus in the later frames).
    CVector3 direction;
    direction.y = focus->y - orbit.y;
    direction.x = focus->x - orbit.x;
    direction.z = focus->z - orbit.z;
    const float length =
        Sqrtf(ppc::fmadds(direction.z, direction.z, ppc::fmadds(direction.x, direction.x, direction.y * direction.y)));
    if (length == 0.0f) {
        m_blendEnd.m_distance = 0.0f;
    } else {
        const float inverse = 1.0f / length;
        direction.y = direction.y * inverse;
        direction.z = direction.z * inverse;
        direction.x = direction.x * inverse;
        m_blendEnd.m_distance = length;
    }
    m_blendEnd.m_pitch = -crt::Asinf(direction.y);
    const float yaw = Vec3_GetYawAngleFromZ(&direction);
    const float startYaw = m_blendStart.m_yaw;
    float difference = yaw - startYaw;
    m_blendEnd.m_yaw = yaw;
    if (difference > kPi) {
        difference = difference - kTwoPi;
    } else if (difference < kMinusPi) {
        difference = difference + kTwoPi;
    }
    m_blendEnd.m_yaw = difference + startYaw;
}

// 0x0015c800 CKCameraClassicTrack3_TestCameraObstruction_maybe: with m_Flags 0x2000 (the track avoids obstructions),
// the line from `from` (raised by the avoiding datas' [2]) to `to` is probed (ProbeObstruction; the masks avoid the
// grounds 0x100 / 0x80, or 0x200 with several focus targets). When something is crossed before `to`, `to` is turned
// about m_WorldTarget by i * pi/16 (i = 1, -1, 2, -2, .. 15, -15) until the line to the turned point is free (or its
// hit is exactly at the end); none free: `to` is kept.
void CKCameraClassicTrack3::TestCameraObstruction(const CVector3* from, CVector3* to) {
    CKSrvCamera* camera = SrvCamera();
    if ((m_Flags & 0x2000u) == 0) return;
    CMasksOfGrdTypeForTests masks;
    masks.m_ui32GrdToTest = 1;
    masks.m_ui32GrdToAvoid = 0x180;
    if (StackCount(camera) > 1) masks.m_ui32GrdToAvoid = 0x280;
    const CKSrvCamera::SCameraAvoidingDatas& avoid = AvoidingDatas(camera, this);
    const float fromZ = from->z;
    const float fromX = from->x;
    const float dz = to->z - fromZ;
    const float dx = to->x - fromX;
    const float startY = from->y + avoid.m_afValues[2];
    const float radius = avoid.m_afValues[1];
    CLine line;
    line.m_start.x = fromX;
    line.m_start.z = fromZ;
    line.m_VectDir.x = dx;
    line.m_VectDir.z = dz;
    line.m_start.y = startY;
    line.m_VectDir.y = to->y - startY;
    const bool sweep = !(radius == 0.0f);
    const bool walls = radius == 0.0f;
    float time;
    if (!ProbeObstruction(this, &line, radius, sweep, walls, &masks, &time)) return;
    if (!(time < 1.0f)) return;
    const float minusDz = -dz;
    int32_t i = 1;
    for (;;) {
        const float angle = static_cast<float>(i) * kSearchStep;
        const float c = GameCosf(angle);
        const float s = GameSinf(angle);
        const float x = ppc::fmadds(s, minusDz, ppc::fmadds(c, dx, m_WorldTarget.x));
        const float z = ppc::fmadds(s, dx, ppc::fmadds(c, dz, m_WorldTarget.z));
        const float y = to->y;
        CLine turned;
        turned.m_start.x = fromX;
        turned.m_start.y = startY;
        turned.m_start.z = fromZ;
        turned.m_VectDir.y = y - startY;
        turned.m_VectDir.x = x - fromX;
        turned.m_VectDir.z = z - fromZ;
        float turnedTime;
        if (!ProbeObstruction(this, &turned, radius, sweep, walls, &masks, &turnedTime) || turnedTime == 1.0f) {
            to->z = z;
            to->x = x;
            to->y = y;
            return;
        }
        i = (i > 0) ? -i : 1 - i;
        if (static_cast<uint32_t>(i + 15) > 30u) return;
    }
}

// 0x0015fa00 CKCameraClassicTrack3_ConstrainFollowToVolume_maybe (UpdateSteady, with a constraint zone): the follow
// track kept inside the zone.
// 1. The heading (not in look mode 2; with IKCamera m_Flags 0x10000 only when the zone's flag 0x100 is set, else
//    m_volumeYawSpeed is cleared and nothing else happens): the zone's look direction (m_lookDirection, or
//    ComputeLookDirection of the previous focus when it is null) gives the target yaw m_volumeYaw; the camera's yaw
//    turns towards it, past the zone's yaw half range m_volumeYawRange (look mode 1: +0x48, plus +0x80 with the zone's
//    flags 2 | 0x100 while m_Flags 0x10000), at the speed m_volumeYawSpeed (accelerating by m_paramDC up to
//    m_paramE0 and braking by m_paramE4: or the zone's +0x60 / +0x64 / +0x68 with its flag 0x800), or snaps to it
//    (m_trackFlags 0x80000, the yaw reached). The track's flags 4 / 8 (the snap requests) beyond 35 units snap the
//    camera behind the target at the zone's yaw instead. The stick speed is limited near the range's edges with the
//    zone's flag 0x100. m_trackFlags 0x80 = a zone heading is active, 0x20000 = the target yaw changed this frame.
// 2. With the zone's flag 0x200 (the volume): the distance is re-measured (to the target plus m_zoneOffset while the
//    zone offset target is set) and the offset target cleared; m_distance shrinks back to m_defaultDistance at
//    m_pullInSpeed (accelerating by m_pullInAccel) while the camera (m_WorldPosition) is inside the volume, slowed
//    down within 3 units of the volume's boundary when the target is outside; then a position outside the volume is
//    either a blend (CaptureBlendStart with the zone's +0x58, when the camera was outside too; m_trackFlags 0x2000),
//    the boundary point (look mode 2) or the orbit position kept inside the volume
//    (CameraVolume_ComputeConstrainedSphericalPosition at the distance m_unk128, the one the volume imposed the frame
//    before, or m_distance), m_zoneOffsetTarget then re-centring the focus on the constrained orbit line.
// The position is r6 in the original (r5 is not used).
void CKCameraClassicTrack3::ConstrainFollowToVolume(float dt, CKCameraConstraint* constraint, CVector3* position) {
    CKSrvCamera* camera = SrvCamera();
    if ((m_Flags & 0x10000u) != 0 && (ZoneFlags(constraint) & 0x100u) == 0) {
        m_volumeYawSpeed = 0.0f;
        return;
    }
    float yaw;  // the camera's yaw this frame (f29)
    if (ZoneLookMode(constraint) == 2) {
        yaw = Vec3_GetYawAngleFromZ(&m_viewDir);
    } else {
        const CVector3 prevFocus = m_prevFocus;
        float accel;     // f27
        float maxSpeed;  // f30
        float decel;     // f26
        if ((ZoneFlags(constraint) & 0x800u) != 0) {
            accel = ZoneVolumeYawAccel(constraint);
            maxSpeed = ZoneVolumeYawMaxSpeed(constraint);
            decel = ZoneVolumeYawDecel(constraint);
        } else {
            accel = m_paramDC;
            maxSpeed = m_paramE0;
            decel = m_paramE4;
        }
        // The yaw of target -> position, turned by pi: the current view yaw.
        const float back = -m_distance;
        CVector3 behind;
        behind.z = m_viewDir.z * back;
        behind.x = m_viewDir.x * back;
        behind.y = m_viewDir.y * back;
        const float viewYaw = Vec3_GetYawAngleFromZ(&behind) + kPi;  // f28
        CVector3 look = m_lookDirection;
        if (look.x == kNullVector.x && look.y == kNullVector.y && look.z == kNullVector.z) {
            look = ComputeLookDirection(constraint, &prevFocus);
        }
        m_volumeYawRange = ZoneLookMode(constraint) == 1 ? ZoneYawRange(constraint) : 0.0f;
        if ((m_Flags & 0x10000u) != 0 && (ZoneFlags(constraint) & 0x2u) != 0 && (ZoneFlags(constraint) & 0x100u) != 0) {
            m_volumeYawRange = m_volumeYawRange + ZoneYawRangeExtra(constraint);
        }
        float targetYaw;  // f31
        if (look.x == 0.0f && look.z == 0.0f) {
            targetYaw = viewYaw;
        } else {
            targetYaw = Vec3_GetYawAngleFromZ(&look);
        }
        if (((m_trackFlags & 0x4u) != 0 || (m_trackFlags & 0x8u) != 0) && m_distance > 35.0f &&
            (ZoneFlags(constraint) & 0x200u) == 0) {
            // Too far with a snap request: the view direction at the zone's yaw and the current pitch, the snap.
            const float pitch = m_pitch.m_current;
            const float sinYaw = GameSinf(targetYaw);
            const float cosPitch = GameCosf(pitch);
            const float cosYaw = GameCosf(targetYaw);
            const float cosPitch2 = GameCosf(pitch);
            const float sinPitch = GameSinf(pitch);
            m_viewDir.y = -sinPitch;
            m_viewDir.x = sinYaw * cosPitch;
            m_viewDir.z = cosYaw * cosPitch2;
            m_prevFocus.z = m_WorldTarget.z;
            m_prevFocus.x = m_WorldTarget.x;
            m_prevFocus.y = m_WorldTarget.y;
            SnapBehindTarget();
            return;
        }
        if (targetYaw == m_volumeYaw) {
            m_trackFlags &= ~0x20000u;
        } else {
            float previousGap = m_volumeYaw - viewYaw;
            if (previousGap > kPi) {
                previousGap = previousGap - kTwoPi;
            } else if (previousGap < kMinusPi) {
                previousGap = previousGap + kTwoPi;
            }
            // A target yaw that barely moved while the view is still away from the old one: 50 times the rates.
            if ((m_trackFlags & 0x80000u) != 0 && (m_trackFlags & 0x10u) != 0 && std::fabs(m_volumeYaw - targetYaw) < 0.02f &&
                std::fabs(previousGap) > 0.02f) {
                decel = decel * 50.0f;
                accel = accel * 50.0f;
                maxSpeed = maxSpeed * 50.0f;
            }
            m_trackFlags = (m_trackFlags & ~0x20000u) | 0x20000u;
            m_volumeYaw = targetYaw;
        }
        float offset = targetYaw - viewYaw;  // f31: the yaw still to turn
        m_trackFlags = (m_trackFlags & ~0x80u) | 0x80u;
        if (offset > kPi) {
            offset = offset - kTwoPi;
        } else if (offset < kMinusPi) {
            offset = offset + kTwoPi;
        }
        const uint32_t flags = m_trackFlags;
        // Which side of the yaw range (0: none, 1: above, -1: below); a dead zone of 0.02 without the flag 0x10 or
        // while the target yaw changed.
        int32_t side;
        if ((flags & 0x10u) == 0 || (flags & 0x20000u) != 0) {
            if (offset < 0.0f) {
                side = offset > -0.02f ? 2 : -1;
            } else if (!(offset < 0.02f)) {
                side = offset > 0.0f ? 1 : 0;
            } else {
                side = 2;
            }
        } else {
            side = offset < 0.0f ? -1 : (offset > 0.0f ? 1 : 0);
        }
        if (side == 2) {
            offset = 0.0f;
        } else if (side == 1) {
            offset = offset - m_volumeYawRange;
            if ((ZoneFlags(constraint) & 0x100u) != 0 && offset > -0.3f && m_yawStickSpeed < 0.0f) {
                // The stick turning away from the range's edge is slowed down near it.
                const float limit = -((offset * -m_yawStickMaxSpeed) / 0.3f);
                if (limit > m_yawStickSpeed) m_yawStickSpeed = limit;
            }
            if (offset < 0.0f) offset = 0.0f;
        } else if (side == -1) {
            offset = offset + m_volumeYawRange;
            if ((ZoneFlags(constraint) & 0x100u) != 0 && offset < 0.3f && m_yawStickSpeed > 0.0f) {
                const float limit = (offset * m_yawStickMaxSpeed) / 0.3f;
                if (limit < m_yawStickSpeed) m_yawStickSpeed = limit;
            }
            if (offset > 0.0f) offset = 0.0f;
        }
        float step;  // f1: the yaw turned this frame
        if ((m_Flags & 0x10000u) == 0 && (flags & 0x80000u) != 0 && (flags & 0x20000u) == 0) {
            // The yaw was reached and the target did not move: follow it directly.
            m_volumeYawSpeed = offset / dt;
            step = offset;
        } else {
            const float remaining = offset < 0.0f ? -offset : offset;
            // The speed limit: the braking distance at full speed (with m_paramE4) beyond the remaining yaw gives
            // sqrt(2 * remaining * m_paramDC) (as the original: the accel, not the decel).
            float limit = maxSpeed;
            if ((1.0f / decel) * (maxSpeed * (maxSpeed * 0.5f)) > remaining) limit = Sqrtf(remaining * (accel + accel));
            if (offset < 0.0f) {
                float speed = m_volumeYawSpeed;
                if (speed > 0.0f) {
                    speed = 0.0f;
                    m_volumeYawSpeed = 0.0f;
                }
                limit = -limit;
                if (speed < limit) {
                    speed = ppc::fmadds(decel, dt, speed);
                    m_volumeYawSpeed = speed;
                    if (limit < speed) m_volumeYawSpeed = limit;
                } else {
                    speed = speed - accel * dt;
                    m_volumeYawSpeed = speed;
                    if (limit > speed) m_volumeYawSpeed = limit;
                }
            } else {
                float speed = m_volumeYawSpeed;
                if (speed < 0.0f) {
                    speed = 0.0f;
                    m_volumeYawSpeed = 0.0f;
                }
                if (limit > speed) {
                    speed = ppc::fmadds(accel, dt, speed);
                    m_volumeYawSpeed = speed;
                    if (limit < speed) m_volumeYawSpeed = limit;
                } else {
                    speed = speed - decel * dt;
                    m_volumeYawSpeed = speed;
                    if (limit > speed) m_volumeYawSpeed = limit;
                }
            }
            step = dt * m_volumeYawSpeed;
        }
        const uint32_t reachedFlag = (m_Flags & 0x10000u) == 0 ? 0x80000u : 0u;
        if (step == 0.0f) {
            yaw = viewYaw;
            if (m_volumeYawRange == 0.0f) yaw = m_volumeYaw;
            m_trackFlags = (m_trackFlags & ~0x80000u) | reachedFlag;
        } else {
            const bool reached = step < 0.0f ? offset >= step : (step > 0.0f && offset <= step);
            if (reached) {
                if (m_volumeYawRange == 0.0f) m_volumeYawSpeed = 0.0f;
                m_trackFlags = (m_trackFlags & ~0x80000u) | reachedFlag;
                step = offset;
            } else {
                m_trackFlags &= ~0x80000u;
            }
            yaw = step + viewYaw;
            // The view direction at the new yaw and the current pitch, the position behind the target.
            const float pitch = m_pitch.m_current;
            const float sinYaw = GameSinf(yaw);
            m_viewDir.x = sinYaw * GameCosf(pitch);
            const float cosYaw = GameCosf(yaw);
            m_viewDir.z = cosYaw * GameCosf(pitch);
            const float sinPitch = GameSinf(pitch);
            const float distanceBack = -m_distance;
            m_viewDir.y = -sinPitch;
            position->z = ppc::fmadds(distanceBack, m_viewDir.z, m_WorldTarget.z);
            position->x = ppc::fmadds(distanceBack, m_viewDir.x, m_WorldTarget.x);
            position->y = ppc::fmadds(distanceBack, m_viewDir.y, m_WorldTarget.y);
        }
    }

    if ((ZoneFlags(constraint) & 0x200u) == 0) return;
    // The volume. The distance to the target (plus the zone offset while a new offset is pending).
    if (m_zoneOffsetTarget.x == kNullVector.x && m_zoneOffsetTarget.y == kNullVector.y && m_zoneOffsetTarget.z == kNullVector.z) {
        const float dx = m_WorldTarget.x - position->x;
        const float dy = m_WorldTarget.y - position->y;
        const float dz = m_WorldTarget.z - position->z;
        m_distance = Sqrtf(ppc::fmadds(dz, dz, ppc::fmadds(dx, dx, dy * dy)));
    } else {
        float dx = m_WorldTarget.x + m_zoneOffset.x;
        float dy = m_WorldTarget.y + m_zoneOffset.y;
        float dz = m_WorldTarget.z + m_zoneOffset.z;
        dx = dx - position->x;
        dy = dy - position->y;
        dz = dz - position->z;
        m_distance = Sqrtf(ppc::fmadds(dz, dz, ppc::fmadds(dx, dx, dy * dy)));
    }
    m_zoneOffsetTarget.x = kNullVector.x;
    m_zoneOffsetTarget.y = kNullVector.y;
    m_zoneOffsetTarget.z = kNullVector.z;
    // The pull-in speed (back to m_defaultDistance): not while m_Flags 0x10000, the stick moves the camera (0x40), the
    // service's flag 0x4000000 or the stick pitch returns (0x20).
    if ((m_Flags & 0x10000u) == 0 && (m_trackFlags & 0x40u) == 0 && (camera->m_baTemporaryFlags & 0x4000000u) == 0 &&
        (m_trackFlags & 0x20u) == 0) {
        if (m_pullInMaxSpeed > m_pullInSpeed) {
            const float speed = ppc::fmadds(dt, m_pullInAccel, m_pullInSpeed);
            m_pullInSpeed = speed;
            if (speed > m_pullInMaxSpeed) m_pullInSpeed = m_pullInMaxSpeed;
        }
    } else {
        m_pullInSpeed = 0.0f;
    }
    const bool cameraInside = CameraVolume_ContainsPoint(constraint, &m_WorldPosition);
    if (!cameraInside) {
        m_pullInSpeed = 0.0f;
    } else {
        m_trackFlags &= ~0x2000u;
        if (!CameraVolume_ContainsPoint(constraint, &m_WorldTarget)) {
            // The target outside: within 3 units (x / z) of the boundary point the pull-in slows down and (with the
            // flag 0x10) the distance grows by the part of the way the position gained on the camera.
            const CVector3 boundary = CameraVolume_ComputeNearestBoundaryPoint(constraint, &m_WorldPosition, &m_WorldTarget);
            float dz = boundary.z - m_WorldPosition.z;
            float dx = boundary.x - m_WorldPosition.x;
            const float cameraToBoundary = Sqrtf(ppc::fmadds(dx, dx, dz * dz));
            dz = boundary.z - position->z;
            dx = boundary.x - position->x;
            const float positionToBoundary = Sqrtf(ppc::fmadds(dx, dx, dz * dz));
            if (cameraToBoundary > positionToBoundary) {
                m_trackFlags &= ~0x1000u;
                if (cameraToBoundary < 3.0f) {
                    if ((m_trackFlags & 0x10u) != 0) {
                        m_distance = m_distance + ((cameraToBoundary - positionToBoundary) * (3.0f - cameraToBoundary)) / 3.0f;
                    }
                    m_pullInSpeed = m_pullInSpeed * (cameraToBoundary / 3.0f);
                }
            }
        }
        float distance = m_distance;
        if (m_defaultDistance < distance && (m_Flags & 0x10000u) == 0 && (m_trackFlags & 0x40u) == 0 &&
            (camera->m_baTemporaryFlags & 0x4000000u) == 0 && m_framingScale >= 1.0f) {
            distance = distance - dt * m_pullInSpeed;
            m_distance = distance;
        } else {
            m_pullInSpeed = 0.0f;
        }
        const float back = -distance;
        position->z = ppc::fmadds(back, m_viewDir.z, m_WorldTarget.z);
        position->x = ppc::fmadds(back, m_viewDir.x, m_WorldTarget.x);
        position->y = ppc::fmadds(back, m_viewDir.y, m_WorldTarget.y);
    }
    // The distance the volume imposed last frame (m_unk128), else m_distance.
    float distance = m_unk128;
    if (!(distance > 0.0f)) distance = m_distance;
    m_unk128 = 0.0f;
    if (CameraVolume_ContainsPoint(constraint, position)) return;
    if (!cameraInside) {
        // Both outside: a blend into the zone (once: m_trackFlags 0x200000 = the zone's +0x20 bit 15 blocks it).
        if ((m_trackFlags & 0x200000u) != 0) return;
        CaptureBlendStart(ZoneBlendTimeScale(constraint), position, &m_WorldTarget);
        m_trackFlags = (m_trackFlags & ~0x2000u) | 0x2000u;
        return;
    }
    if (ZoneLookMode(constraint) == 2) {
        const CVector3 boundary = CameraVolume_ComputeBoundaryPointForShapeBits(constraint, &m_WorldPosition, position);
        position->x = boundary.x;
        position->z = boundary.z;
        position->y = boundary.y;
        return;
    }
    // The orbit position kept inside the volume: at the pitch target when the pitch is within 0.1 of it while
    // m_Flags 0x10000, else at the current pitch.
    const float currentPitch = m_pitch.m_current;
    const float targetPitch = m_pitch.m_target;
    float pitchGap = currentPitch - targetPitch;
    if (pitchGap < 0.0f) pitchGap = -pitchGap;
    if (pitchGap > kPi) pitchGap = kTwoPi - pitchGap;
    uint8_t constrained;
    CVector3 constrainedPosition;
    if (pitchGap < 0.1f && (m_Flags & 0x10000u) != 0) {
        constrainedPosition =
            CameraVolume_ComputeConstrainedSphericalPosition(yaw, targetPitch, distance, constraint, &m_WorldTarget, &constrained);
    } else {
        constrainedPosition =
            CameraVolume_ComputeConstrainedSphericalPosition(yaw, currentPitch, distance, constraint, &m_WorldTarget, &constrained);
    }
    position->x = constrainedPosition.x;
    position->z = constrainedPosition.z;
    position->y = constrainedPosition.y;
    if (constrained == 0) return;
    // The volume moved it: the zone offset target re-centres the focus on the orbit line (yaw, pitch target) through
    // the constrained position, and the distance is kept for the next frame.
    const float pitch = m_pitch.m_target;
    float dirZ = GameCosf(yaw);
    dirZ = dirZ * GameCosf(pitch);
    float dirX = GameSinf(yaw);
    dirX = GameCosf(pitch) * dirX;
    const float dirY = -GameSinf(pitch);
    const float dy = m_WorldTarget.y - position->y;
    const float dx = m_WorldTarget.x - position->x;
    const float dz = m_WorldTarget.z - position->z;
    const float along = ppc::fmadds(dirZ, dz, ppc::fmadds(dirX, dx, dirY * dy));
    const float pz = ppc::fmadds(dirZ, along, position->z);
    const float px = ppc::fmadds(dirX, along, position->x);
    const float py = ppc::fmadds(dirY, along, position->y);
    m_zoneOffsetTarget.z = pz - m_WorldTarget.z;
    m_zoneOffsetTarget.x = px - m_WorldTarget.x;
    m_zoneOffsetTarget.y = py - m_WorldTarget.y;
    m_unk128 = distance;
}

// 0x00162910 CKCameraClassicTrack3_FindAndRepairOcclusion_maybe (IKCamera vt+0x74): keeps the focus target visible.
// The line from the focus (raised by the avoiding datas' [2]) to the camera is probed (the cylinder radius: the first
// focus entry's +0x20, -1: the avoiding datas' [1]). Obstructed: the camera turns about m_WorldTarget towards the free
// side found by a search of i * pi/16 (the direction from m_trackFlags: bits 0 / 1 the side of the last turn, bits
// 2 / 3 the wall side of ResolveWallMovement), at the yaw speed m_obstructionOffset (accelerated by m_paramD0 up to
// m_paramD8 per second); after a second of turning (m_obstructionTime) it snaps to the free point m_obstructionPoint,
// or when no side is free, moves in front of the obstruction or back to the default distance. Free: the yaw speed
// decays by m_paramD4. A wall above the focus (the hit's top below the line) limits the pitch (m_pitchMaxB).
void CKCameraClassicTrack3::ResolveViewObstructions(float dt, const CVector3* focus, CVector3* position) {
    CKSrvCamera* camera = SrvCamera();
    camera->m_baTemporaryFlags &= ~0x4000u;
    const CVector3 savedPosition = {position->x, position->y, position->z};
    const float focusX = focus->x;
    const float focusY = focus->y;
    const float focusZ = focus->z;
    const CKSrvCamera::SCameraAvoidingDatas& avoid = AvoidingDatas(camera, this);
    const float heightOffset = avoid.m_afValues[2];
    CMasksOfGrdTypeForTests masks;
    masks.m_ui32GrdToTest = 1;
    masks.m_ui32GrdToAvoid = 0x180;
    CMasksOfGrdTypeForTests cameraMasks;  // the probes from the camera's own position
    cameraMasks.m_ui32GrdToTest = 1;
    cameraMasks.m_ui32GrdToAvoid = 0x80;
    if (StackCount(camera) > 1) masks.m_ui32GrdToAvoid = 0x280;
    uint8_t pushed = PushOutOfConstraintPlane(dt, position);

    float yawSpeed;
    {
        bool test;
        const CKCameraConstraint* zone = m_pConstraint;
        if (zone != nullptr && (ZoneFlags(zone) & 0x10000u) != 0 && m_blendDuration != -1.0f) {
            test = true;
        } else if ((m_Flags & 0x10000u) != 0) {
            test = false;
        } else if (StackCount(camera) > 1 && focus->y > position->y && m_pitch.m_current > 0.0f) {
            test = false;
        } else {
            test = true;
        }
        if (!test) {
            m_obstructionOffset = 0.0f;
            if ((pushed & 0xffu) != 0) {
                CVector3 from = savedPosition;
                ResolveWallMovement(&from, position);
            }
            return;
        }
    }

    float radius = camera->m_aStack[0].m_unk20;
    if (radius == -1.0f) radius = avoid.m_afValues[1];
    const float startY = focusY + heightOffset;
    const float dx = position->x - focusX;
    const float dz = position->z - focusZ;
    const float dy = position->y - startY;
    const bool sweep = !(radius == 0.0f);
    const bool walls = radius == 0.0f;
    CLine line;
    line.m_start.x = focusX;
    line.m_start.z = focusZ;
    line.m_start.y = startY;
    line.m_VectDir.x = dx;
    line.m_VectDir.z = dz;
    line.m_VectDir.y = dy;
    float firstTime;
    const bool obstructed = ProbeObstruction(this, &line, radius, sweep, walls, &masks, &firstTime) && firstTime < 1.0f;

    if (!obstructed) {
        // Free: the turn speed decays to 0 by m_paramD4 per second.
        m_trackFlags &= ~3u;
        yawSpeed = m_obstructionOffset;
        if (yawSpeed > 0.0f) {
            yawSpeed = yawSpeed - dt * m_paramD4;
            m_obstructionOffset = yawSpeed;
            if (yawSpeed < 0.0f) {
                yawSpeed = 0.0f;
                m_obstructionOffset = 0.0f;
            }
        } else if (yawSpeed < 0.0f) {
            yawSpeed = ppc::fmadds(dt, m_paramD4, yawSpeed);
            m_obstructionOffset = yawSpeed;
            if (yawSpeed > 0.0f) {
                yawSpeed = 0.0f;
                m_obstructionOffset = 0.0f;
            }
        }
        m_obstructionTime = 0.0f;
    } else {
        if ((m_trackFlags & 0x40u) != 0) m_trackFlags &= ~0x40u;
        const CKCameraConstraint* zone = m_pConstraint;
        if (m_blendDuration > 0.0f && zone != nullptr && (ZoneFlags(zone) & 0x10000u) != 0) {
            CaptureBlendStart(0.0f, position, &m_WorldTarget);
            return;
        }
        const float minusDz = -dz;
        bool found = false;
        float foundAngle = 0.0f;
        bool retest;
        if (m_obstructionHit.m_ftOnLine == firstTime) {
            // A ground: one flagged 0x8 (its engine flags) at or above the focus counts as passable.
            const ICollisionMesh* mesh = m_obstructionHit.m_pCollisionMesh;
            retest = !(((mesh->m_ba16EngineFlags >> 3) & 1u) != 0 && ppc::fmadds(firstTime, dy, startY) >= focus->y);
        } else {
            // A wall: when its top is above the probe's start, the pitch is limited to look over it.
            const float top = ppc::fmadds(firstTime, dy, startY) - m_wallHit.m_fHeightUnder;
            if (startY <= top) {
                const float rise = top - startY;
                const float runX = ppc::fmadds(firstTime, dx, focusX) - focusX;
                const float runZ = ppc::fmadds(firstTime, dz, focusZ) - focusZ;
                float sine = rise / Sqrtf(ppc::fmadds(runZ, runZ, ppc::fmadds(runX, runX, rise * rise)));
                if (sine <= 0.0f) {
                    sine = 0.0f;
                } else if (sine >= 1.0f) {
                    sine = 1.0f;
                }
                m_pitchMaxB = crt::Asinf(sine);
                retest = false;
            } else {
                retest = true;
            }
        }
        if (!retest) {
            found = true;  // the angle 0: no turn
        } else if ((m_trackFlags & 3u) != 0) {
            // The last turn's free point: still free, keep turning that way (pi / -pi only gives the side).
            CLine toPoint;
            toPoint.m_start.x = focusX;
            toPoint.m_start.y = startY;
            toPoint.m_start.z = focusZ;
            toPoint.m_VectDir.x = m_obstructionPoint.x - focusX;
            toPoint.m_VectDir.z = m_obstructionPoint.z - focusZ;
            toPoint.m_VectDir.y = m_obstructionPoint.y - startY;
            float pointTime;
            if (!ProbeObstruction(this, &toPoint, radius, sweep, walls, &masks, &pointTime) || pointTime == 1.0f) {
                found = true;
                foundAngle = (m_trackFlags & 2u) != 0 ? kPi : kMinusPi;
            }
        }

        if (!found) {
            // The search: the first direction from the flags, then i * pi/16 by the flags' rule.
            const uint32_t startFlags = m_trackFlags;
            int32_t i;
            if ((startFlags & 8u) != 0 && (startFlags & 2u) == 0) {
                i = -1;
            } else {
                i = (startFlags & 1u) != 0 ? -1 : 1;
            }
            while (i <= 15 && i >= -15) {
                const float angle = static_cast<float>(i) * kSearchStep;
                const float c = GameCosf(angle);
                const float s = GameSinf(angle);
                const float turnedX = ppc::fmadds(s, minusDz, ppc::fmadds(c, dx, m_WorldTarget.x));
                const float turnedZ = ppc::fmadds(s, dx, ppc::fmadds(c, dz, m_WorldTarget.z));
                const float turnedDy = position->y - startY;
                CLine turned;
                turned.m_start.x = focusX;
                turned.m_start.y = startY;
                turned.m_start.z = focusZ;
                turned.m_VectDir.y = turnedDy;
                turned.m_VectDir.x = turnedX - focusX;
                turned.m_VectDir.z = turnedZ - focusZ;
                float time;
                float pointX;
                float pointY;
                float pointZ;
                bool candidate = false;
                if (!ProbeObstruction(this, &turned, radius, sweep, walls, &masks, &time)) {
                    pointX = focusX + turned.m_VectDir.x;
                    pointY = startY + turned.m_VectDir.y;
                    pointZ = focusZ + turned.m_VectDir.z;
                    candidate = true;
                } else if (time > 0.9f && time > firstTime) {
                    // Farther than the first hit: the point of the hit, if the line to it is free.
                    pointX = ppc::fmadds(time, turned.m_VectDir.x, focusX);
                    pointY = ppc::fmadds(time, turned.m_VectDir.y, startY);
                    pointZ = ppc::fmadds(time, turned.m_VectDir.z, focusZ);
                    if (time >= 1.0f) {
                        candidate = true;
                    } else {
                        CLine toHit;
                        toHit.m_start.x = focusX;
                        toHit.m_start.y = startY;
                        toHit.m_start.z = focusZ;
                        toHit.m_VectDir.x = pointX - focusX;
                        toHit.m_VectDir.y = pointY - startY;
                        toHit.m_VectDir.z = pointZ - focusZ;
                        float hitTime;
                        candidate = !ProbeObstruction(this, &toHit, radius, sweep, walls, &masks, &hitTime) ||
                                    hitTime >= 1.0f;
                    }
                }
                if (candidate) {
                    // The camera must reach the point too (the walls, then the grounds, with the camera's masks).
                    CLine fromCamera;
                    fromCamera.m_start.x = position->x;
                    fromCamera.m_start.y = position->y;
                    fromCamera.m_start.z = position->z;
                    fromCamera.m_VectDir.x = pointX - fromCamera.m_start.x;
                    fromCamera.m_VectDir.y = pointY - fromCamera.m_start.y;
                    fromCamera.m_VectDir.z = pointZ - fromCamera.m_start.z;
                    CKSrvCollision* collision = SrvCollision();
                    ResetObstructionHit(&m_obstructionHit);
                    bool reached;
                    if (collision->RaycastWalls(&fromCamera, kProbeHeight, &m_wallHit, 0, &cameraMasks, 1) != 0) {
                        reached = m_wallHit.m_ftLine == 1.0f;
                    } else if (collision->RaycastMeshes(&fromCamera, &m_obstructionHit, 1, 0, &cameraMasks) != 0) {
                        reached = m_obstructionHit.m_ftOnLine == 1.0f;
                    } else {
                        reached = true;
                    }
                    if (reached) {
                        foundAngle = angle;
                        m_obstructionPoint.x = pointX;
                        m_obstructionPoint.z = pointZ;
                        m_obstructionPoint.y = pointY;
                        found = true;
                        break;
                    }
                }
                // The next angle (the flags as they are now).
                const uint32_t flags = m_trackFlags;
                bool alternate = false;  // the 0x163868 rule
                if ((flags & 8u) != 0 && (flags & 2u) == 0) {
                    i = i - 1;
                } else if ((flags & 4u) != 0) {
                    if ((flags & 1u) == 0) {
                        i = i + 1;
                    } else {
                        alternate = true;
                    }
                } else if ((flags & 1u) != 0) {
                    alternate = true;
                } else if ((flags & 2u) == 0) {
                    i = (i > 0) ? -i : 1 - i;
                } else if (i < 0) {
                    i = i - 1;
                } else if (i == 15) {
                    i = -1;
                } else {
                    i = i + 1;
                }
                if (alternate) {
                    // One side to -15, then the other from 1.
                    if (i > 0) {
                        i = i + 1;
                    } else if (i != -15) {
                        i = i - 1;
                    } else {
                        i = 1;
                    }
                }
            }
        }

        if (!found) {
            // No side free: after a second, in front of the obstruction (a hit beyond 3/4 of the way) or back to
            // the default distance behind the target.
            m_trackFlags &= ~3u;
            float time;
            if (StackCount(camera) == 1) {
                time = dt + m_obstructionTime;
                m_obstructionTime = time;
            } else {
                time = m_obstructionTime;
            }
            if (time >= 1.0f) {
                m_obstructionTime = 0.0f;
                if (firstTime > 0.75f || dt + 1.0f < 0.0f) {
                    const float y = position->y - startY;
                    const float z = position->z - focusZ;
                    const float x = position->x - focusX;
                    pushed = 0;
                    position->y = ppc::fmadds(firstTime, y, startY);
                    position->z = ppc::fmadds(firstTime, z, focusZ);
                    position->x = ppc::fmadds(firstTime, x, focusX);
                    camera->SetCalculationPose(position, focus);
                    camera->CaptureHeroHeadingLock();
                } else {
                    m_distance = m_defaultDistance;
                    const float back = -m_defaultDistance;
                    pushed = 0;
                    position->z = ppc::fmadds(back, m_viewDir.z, m_WorldTarget.z);
                    position->x = ppc::fmadds(back, m_viewDir.x, m_WorldTarget.x);
                    position->y = ppc::fmadds(back, m_viewDir.y, m_WorldTarget.y);
                    CVector3 from = {focus->x, focus->y, focus->z};
                    TestCameraObstruction(&from, position);
                    camera->SetCalculationPose(position, focus);
                    camera->CaptureHeroHeadingLock();
                }
            }
            yawSpeed = m_obstructionOffset;
        } else if (m_obstructionTime >= 1.0f) {
            // A second of turning: the snap to the free point.
            m_obstructionOffset = 0.0f;
            pushed = 0;
            position->x = m_obstructionPoint.x;
            position->y = m_obstructionPoint.y;
            position->z = m_obstructionPoint.z;
            m_trackFlags &= ~3u;
            camera->SetCalculationPose(position, focus);
            camera->CaptureHeroHeadingLock();
            yawSpeed = m_obstructionOffset;
        } else if (foundAngle > 0.0f) {
            m_trackFlags = (m_trackFlags | 2u) & ~1u;
            yawSpeed = m_obstructionOffset;
            if (yawSpeed < 0.0f) {
                yawSpeed = 0.0f;
                m_obstructionOffset = 0.0f;
            }
            yawSpeed = ppc::fmadds(dt, m_paramD0, yawSpeed);
            m_obstructionOffset = yawSpeed;
            if (yawSpeed > m_paramD8) {
                yawSpeed = m_paramD8;
                m_obstructionOffset = yawSpeed;
            }
            if ((m_trackFlags & 8u) != 0) m_obstructionTime = dt + m_obstructionTime;
        } else if (foundAngle < 0.0f) {
            m_trackFlags = (m_trackFlags | 1u) & ~2u;
            yawSpeed = m_obstructionOffset;
            if (yawSpeed > 0.0f) {
                yawSpeed = 0.0f;
                m_obstructionOffset = 0.0f;
            }
            const float maxSpeed = -m_paramD8;
            yawSpeed = yawSpeed - dt * m_paramD0;
            m_obstructionOffset = yawSpeed;
            if (yawSpeed < maxSpeed) {
                yawSpeed = maxSpeed;
                m_obstructionOffset = yawSpeed;
            }
            if ((m_trackFlags & 4u) != 0) m_obstructionTime = dt + m_obstructionTime;
        } else {
            yawSpeed = m_obstructionOffset;
        }
    }

    if (yawSpeed == 0.0f) {
        if ((pushed & 0xffu) != 0) {
            CVector3 from = savedPosition;
            ResolveWallMovement(&from, position);
        }
        return;
    }
    // The turn about m_WorldTarget by dt * the yaw speed.
    const float angle = dt * yawSpeed;
    const float offsetY = position->y;
    const float offsetX = position->x - m_WorldTarget.x;
    const float offsetZ = position->z - m_WorldTarget.z;
    const float cosA = GameCosf(angle);
    const float sinA = GameSinf(angle);
    const float sinB = GameSinf(angle);
    const float cosB = GameCosf(angle);
    const float z = ppc::fmadds(sinB, offsetX, cosB * offsetZ);
    const float x = ppc::fmsubs(cosA, offsetX, sinA * offsetZ);
    position->y = (offsetY - m_WorldTarget.y) + m_WorldTarget.y;
    position->z = z + m_WorldTarget.z;
    position->x = m_WorldTarget.x + x;
    CVector3 from = savedPosition;
    ResolveWallMovement(&from, position);
}

// 0x00163dc0 CKCameraClassicTrack3_Activate_maybe (vt+0x50): the track reset, the constraint zone and the focus taken
// from the camera service, the camera placed at the default distance from the focus in the direction of
// `startPosition` (the service's real view direction, negated, without one) at the focus targets' pitch; the fov and
// +0x44 approach states set up, the framing and the obstruction test run once and a blend started when there is a zone.
// CKCamera_StartAttachedFx_maybe (0x1441e8): STUB(C2.7, the FX service), as in CKCamera::Start.
void CKCameraClassicTrack3::Start(const CVector3* startPosition) {
    if (m_unk50 != nullptr) DOTD_STUB_ONCE("CKCamera_StartAttachedFx_maybe: CKSrvFx_StartCameraFx_maybe 0x1afaf8 (C2.7)");
    m_trackFlags = 0;
    ResetState();
    CKSrvCamera* camera = SrvCamera();
    m_distance = m_defaultDistance;
    m_pConstraint = camera->m_pActiveConstraint;
    ComputeFocusPoint(&m_WorldTarget);
    m_prevFocus.x = m_WorldTarget.x;
    m_prevFocus.z = m_WorldTarget.z;
    m_prevFocus.y = m_WorldTarget.y;
    m_pitch.m_current = m_desiredPitch;
    m_pitch.m_target = m_desiredPitch;
    float dx;
    float dz;
    if (startPosition != nullptr) {
        dx = startPosition->x - m_WorldTarget.x;
        dz = startPosition->z - m_WorldTarget.z;
    } else {
        dz = -camera->m_v3RealAxisZ.z;
        dx = -camera->m_v3RealAxisZ.x;
    }
    float lengthSq = ppc::fmadds(dx, dx, 0.0f);
    m_WorldPosition.x = m_WorldTarget.x;
    m_WorldPosition.y = m_WorldTarget.y;
    m_WorldPosition.z = m_WorldTarget.z;
    lengthSq = ppc::fmadds(dz, dz, lengthSq);
    const float length = Sqrtf(lengthSq);
    if (length != 0.0f) {
        const float inverse = 1.0f / length;
        dz = dz * inverse;
        dx = dx * inverse;
    }
    const float pitch = m_pitch.m_current;
    const float horizontalX = GameCosf(pitch) * dx;
    const float horizontalZ = GameCosf(pitch) * dz;
    const float vertical = GameSinf(pitch);
    const float distance = m_distance;
    m_WorldPosition.x = ppc::fmadds(horizontalX, distance, m_WorldPosition.x);
    m_viewDir.x = -horizontalX;
    m_WorldPosition.z = ppc::fmadds(horizontalZ, distance, m_WorldPosition.z);
    m_viewDir.z = -horizontalZ;
    m_WorldPosition.y = ppc::fmadds(vertical, distance, m_WorldPosition.y);
    m_viewDir.y = -vertical;
    UpdateRightVector();
    camera->m_baTemporaryFlags &= ~0x800000u;
    m_fov.m_accel = IKCamera::AsFloat(camera->m_unk2c[3]);     // CKSrvCamera +0x38
    m_fov.m_decel = IKCamera::AsFloat(camera->m_unk2c[5]);     // +0x40
    m_fov.m_maxSpeed = IKCamera::AsFloat(camera->m_unk2c[4]);  // +0x3c
    m_fov.m_target = m_fFov;
    m_unk44Approach.m_accel = 100.0f;
    m_fov.m_current = m_fFov;
    m_fov.m_speedBonus = 0.0f;
    m_fov.m_speed = 0.0f;
    m_unk44Approach.m_maxSpeed = 100.0f;
    m_unk44Approach.m_decel = 100.0f;
    m_unk44Approach.m_target = AsFloat(m_unk44);
    m_unk44Approach.m_current = AsFloat(m_unk44);
    m_unk44Approach.m_speedBonus = 0.0f;
    m_unk44Approach.m_speed = 0.0f;
    m_unk304 = AsFloat(m_unk48);
    m_unk308 = AsFloat(m_unk4c);
    m_trackFlags &= ~0x100000u;
    m_groundPoint = kNullVector;
    UpdateFramingAndPlaceCamera(0.0f, &m_WorldPosition);
    CVector3 focusTarget;
    focusTarget.x = StackPosition(camera->m_aStack[0])[0];
    focusTarget.y = StackPosition(camera->m_aStack[0])[1];
    focusTarget.z = StackPosition(camera->m_aStack[0])[2];
    TestCameraObstruction(&focusTarget, &m_WorldPosition);
    if (m_pConstraint != nullptr) {
        CaptureBlendStart(0.0f, &m_WorldPosition, &m_WorldTarget);
        m_blendDuration = 0.0f;
    }
    m_requestedFov = -1.0f;
}

// 0x001653c0 CKCameraClassicTrack3_Update_maybe (vt+0x60): the attached fx (UpdateTrackBase); a change of the camera
// service's constraint zone (+0xe04) sets up the switch (flags, the zone's +0x90..+0x98 values, a blend from the current
// pose unless the old and new zones have the same offsets and no special flags); the zone offset is taken out of the
// target and the previous focus, the +0x44 approach steps, the steady or blending update runs, the zone offset moves to
// its target by at most 30 * dt per axis and is added back.
void CKCameraClassicTrack3::Update(float dt) {
    CKSrvCamera* camera = SrvCamera();
    UpdateTrackBase();
    CKCameraConstraint* const newZone = camera->m_pActiveConstraint;
    const float noBlend = -1.0f;
    if (m_pConstraint == newZone) {
        m_WorldTarget.x = m_WorldTarget.x - m_zoneOffset.x;
        m_WorldTarget.y = m_WorldTarget.y - m_zoneOffset.y;
        m_WorldTarget.z = m_WorldTarget.z - m_zoneOffset.z;
        m_prevFocus.x = m_prevFocus.x - m_zoneOffset.x;
        m_prevFocus.y = m_prevFocus.y - m_zoneOffset.y;
        m_prevFocus.z = m_prevFocus.z - m_zoneOffset.z;
        m_trackFlags &= ~0x100u;
    } else {
        uint32_t flags = m_trackFlags;
        flags &= 0xffffdeffu;
        flags |= 0x100u;
        flags &= 0xfffdf7ffu;
        flags |= 0x20000u;
        flags &= 0xffd7ffffu;
        m_trackFlags = flags;
        m_unk128 = 0.0f;
        CKCameraConstraint* oldZone = m_pConstraint;
        if (oldZone != nullptr) {
            bool offsetChanged;
            if ((ZoneFlags(oldZone) & 0x200u) != 0) m_pullInSpeed = 0.0f;
            if (ZoneSideOffset(oldZone) != 0.0f || ZoneUpOffset(oldZone) != 0.0f) {
                offsetChanged = true;
            } else {
                offsetChanged = m_zoneOffset.x != kNullVector.x || m_zoneOffset.y != kNullVector.y ||
                                m_zoneOffset.z != kNullVector.z;
            }
            if (offsetChanged) m_trackFlags = (m_trackFlags & ~0x10000u) | 0x10000u;
        }
        if (newZone == nullptr) {
            m_unk44Approach.m_target = AsFloat(m_unk44);
            m_unk304 = AsFloat(m_unk48);
            m_unk308 = AsFloat(m_unk4c);
            m_pConstraint = newZone;
            m_blendDuration = noBlend;
        } else {
            float oldSide;
            float oldUp;
            uint32_t oldKeepsPose;  // the old zone's +0x20 bit 15
            float timeScale;
            oldZone = m_pConstraint;
            if (oldZone == nullptr) {
                oldUp = 0.0f;
                oldKeepsPose = 0;
                oldSide = oldUp;
                timeScale = noBlend;
            } else {
                oldKeepsPose = (ZoneFlags(oldZone) >> 15) & 1u;
                m_trackFlags = (m_trackFlags & ~0x200000u) | ((oldKeepsPose & 0xffu) << 21);
                oldSide = ZoneSideOffset(oldZone);
                oldUp = ZoneUpOffset(oldZone);
                timeScale = (ZoneFlags(m_pConstraint) & 0x4000u) != 0 ? ZoneBlendTimeScaleAlt(m_pConstraint) : noBlend;
            }
            const uint32_t newFlags = ZoneFlags(newZone);
            const bool newNoBlendFlag = (newFlags & 0x20u) != 0;
            uint32_t blend = 1;
            bool sameOffsets = false;
            if (!newNoBlendFlag && oldSide == ZoneSideOffset(newZone) && oldUp == ZoneUpOffset(newZone) &&
                (newFlags & 0x1000u) == 0 && timeScale == noBlend) {
                sameOffsets = true;
            }
            if (sameOffsets) {
                blend = 0;
                timeScale = ZoneBlendTimeScale(newZone);
            } else if (timeScale == noBlend) {
                timeScale = newNoBlendFlag ? 0.0f : ZoneBlendTimeScale(newZone);
            }
            if ((newFlags & 0x80000u) != 0) {
                m_unk44Approach.m_target = ZoneUnk44(newZone);
                m_unk304 = ZoneUnk48(newZone);
                m_unk308 = ZoneUnk4c(newZone);
            }
            if ((ZoneFlags(newZone) & 0x200u) != 0) {
                m_trackFlags = (m_trackFlags & ~0x800u) | 0x800u;
                m_pullInSpeed = 0.0f;
                m_trackFlags = (m_trackFlags & ~0x2000u) | 0x2000u;
            }
            m_pConstraint = newZone;
            if ((blend & 0xffu) != 0 && (oldKeepsPose & 0xffu) == 0) {
                CaptureBlendStart(timeScale, &m_WorldPosition, &m_WorldTarget);
            } else {
                m_blendDuration = noBlend;
            }
        }
        m_WorldTarget.x = m_WorldTarget.x - m_zoneOffset.x;
        m_WorldTarget.y = m_WorldTarget.y - m_zoneOffset.y;
        m_WorldTarget.z = m_WorldTarget.z - m_zoneOffset.z;
        m_prevFocus.x = m_prevFocus.x - m_zoneOffset.x;
        m_prevFocus.y = m_prevFocus.y - m_zoneOffset.y;
        m_prevFocus.z = m_prevFocus.z - m_zoneOffset.z;
        m_zoneOffset = kNullVector;
        m_zoneOffsetTarget = kNullVector;
    }
    Math_ApproachWithAccelDecel(dt, m_unk44Approach.Data());
    if (m_blendDuration <= noBlend) {
        UpdateSteady(dt);
    } else {
        UpdateBlending(dt);
    }
    // The zone offset towards its target, at most 30 * dt per axis.
    const float step = dt * 30.0f;
    {
        const float difference = m_zoneOffsetTarget.x - m_zoneOffset.x;
        float magnitude;
        bool move = true;
        if (difference < 0.0f) {
            magnitude = -difference;
        } else if (difference <= 0.0f) {
            move = false;
            magnitude = 0.0f;
        } else {
            magnitude = difference;
        }
        if (move) {
            if (magnitude > step) {
                m_zoneOffset.x = ppc::fmadds(difference < 0.0f ? noBlend : 1.0f, step, m_zoneOffset.x);
            } else {
                m_zoneOffset.x = m_zoneOffsetTarget.x;
            }
        }
    }
    {
        const float difference = m_zoneOffsetTarget.y - m_zoneOffset.y;
        float magnitude;
        bool move = true;
        if (difference < 0.0f) {
            magnitude = -difference;
        } else if (difference <= 0.0f) {
            move = false;
            magnitude = 0.0f;
        } else {
            magnitude = difference;
        }
        if (move) {
            if (magnitude > step) {
                m_zoneOffset.y = ppc::fmadds(difference < 0.0f ? noBlend : 1.0f, step, m_zoneOffset.y);
            } else {
                m_zoneOffset.y = m_zoneOffsetTarget.y;
            }
        }
    }
    {
        const float difference = m_zoneOffsetTarget.z - m_zoneOffset.z;
        float magnitude;
        bool move = true;
        if (difference < 0.0f) {
            magnitude = -difference;
        } else if (difference <= 0.0f) {
            move = false;
            magnitude = 0.0f;
        } else {
            magnitude = difference;
        }
        if (move) {
            // (The z axis tests the other way round: a NaN difference steps instead of snapping.)
            if (magnitude <= step) {
                m_zoneOffset.z = m_zoneOffsetTarget.z;
            } else {
                m_zoneOffset.z = ppc::fmadds(difference < 0.0f ? noBlend : 1.0f, step, m_zoneOffset.z);
            }
        }
    }
    m_WorldTarget.x = m_WorldTarget.x + m_zoneOffset.x;
    m_WorldTarget.y = m_WorldTarget.y + m_zoneOffset.y;
    m_WorldTarget.z = m_WorldTarget.z + m_zoneOffset.z;
    m_prevFocus.x = m_prevFocus.x + m_zoneOffset.x;
    m_prevFocus.y = m_prevFocus.y + m_zoneOffset.y;
    m_prevFocus.z = m_prevFocus.z + m_zoneOffset.z;
    m_requestedFov = noBlend;
}

// 0x0015a690 CKCameraClassicTrack3_IntegrateSplitFollowSpring_maybe: the follow spring split into a horizontal part (the
// distance in x / z, m_followSpeedXZ) and a vertical one (|delta.y|, m_followSpeedY, the stiffness m_followStiffnessUp
// and damping m_followDampingUp going up while the camera service's flag 0x4000000 is set), integrated in steps of at
// most 0.01 s; with the fixed spring (m_trackFlags 0x200) the horizontal force is m_followAccelFixed and the vertical
// m_followAccelFixed too. The previous focus becomes `focus`, and `focus` the target moved by the integrated distances.
// `delta` (focus - target) is flattened and normalised in place.
void CKCameraClassicTrack3::IntegrateFollowOffset120(float dt, CVector3* focus, CVector3* delta) {
    float vertical = delta->y;
    int32_t sign = 1;
    if (vertical < 0.0f) {
        vertical = -vertical;
        sign = -1;
    }
    float lengthSq = ppc::fmadds(delta->x, delta->x, 0.0f);
    delta->y = 0.0f;
    lengthSq = ppc::fmadds(delta->z, delta->z, lengthSq);
    float horizontal = Sqrtf(lengthSq);
    if (horizontal != 0.0f) {
        const float inverse = 1.0f / horizontal;
        delta->z = inverse * delta->z;
        delta->x = inverse * delta->x;
        delta->y = inverse * delta->y;
    } else {
        horizontal = 0.0f;
    }
    float damping = m_followDamping;
    if ((m_trackFlags & 0x200u) != 0) {
        if (horizontal < 0.1f && !(vertical >= 0.1f)) {
            m_trackFlags &= ~0x200u;
        } else {
            damping = m_followDampingFixed;
        }
    }
    float movedVertical = 0.0f;
    float movedHorizontal = 0.0f;
    if (!(dt <= 0.0f)) {
        float timeLeft = dt;
        const uint32_t flags = m_trackFlags;
        float speedY = m_followSpeedY;
        for (;;) {
            float step;
            if (timeLeft <= 0.01f) {
                step = timeLeft;
                timeLeft = 0.0f;
            } else {
                timeLeft = timeLeft - 0.01f;
                step = 0.01f;
            }
            float limitHorizontal;
            float limitVertical;
            float forceHorizontal;
            float forceVertical;
            bool upward;
            if ((flags & 0x200u) == 0) {
                limitHorizontal = horizontal < 0.1f ? 0.0f : horizontal;
                limitVertical = vertical < 0.1f ? 0.0f : vertical;
                forceHorizontal = m_followStiffness * horizontal;
                upward = (SrvCamera()->m_baTemporaryFlags & 0x4000000u) != 0 && sign > 0;
                forceVertical = upward ? vertical * m_followStiffnessUp : m_followStiffness * vertical;
                upward = (SrvCamera()->m_baTemporaryFlags & 0x4000000u) != 0 && sign > 0;
            } else {
                limitVertical = vertical;
                forceHorizontal = m_followAccelFixed;
                limitHorizontal = horizontal;
                forceVertical = forceHorizontal;
                upward = (SrvCamera()->m_baTemporaryFlags & 0x4000000u) != 0 && sign > 0;
            }
            const float speedXZ = m_followSpeedXZ;
            const float dampingVertical = upward ? -speedY * m_followDampingUp : damping * -speedY;
            const float newSpeedXZ = ppc::fmadds(step, ppc::fmadds(damping, -speedXZ, forceHorizontal), speedXZ);
            const float advanceHorizontal = step * newSpeedXZ;
            m_followSpeedXZ = newSpeedXZ;
            // (The two paths of the original compare the other way round: they differ for a NaN only.)
            const bool horizontalLeft = upward ? !(limitHorizontal <= advanceHorizontal) : limitHorizontal > advanceHorizontal;
            if (horizontalLeft) {
                movedHorizontal = movedHorizontal + advanceHorizontal;
                horizontal = limitHorizontal - advanceHorizontal;
            } else {
                horizontal = 0.0f;
                movedHorizontal = movedHorizontal + limitHorizontal;
            }
            speedY = ppc::fmadds(step, forceVertical + dampingVertical, speedY);
            const float advanceVertical = step * speedY;
            m_followSpeedY = speedY;
            if (horizontalLeft ? !(limitVertical <= advanceVertical) : limitVertical > advanceVertical) {
                movedVertical = movedVertical + advanceVertical;
                vertical = limitVertical - advanceVertical;
            } else {
                vertical = 0.0f;
                movedVertical = movedVertical + limitVertical;
            }
            if (horizontal == 0.0f && vertical == 0.0f) break;
            if (timeLeft <= 0.0f) break;
        }
    }
    m_prevFocus.x = focus->x;
    m_prevFocus.y = focus->y;
    m_prevFocus.z = focus->z;
    const float y = ppc::fmadds(movedHorizontal, delta->y, m_WorldTarget.y);
    focus->z = ppc::fmadds(movedHorizontal, delta->z, m_WorldTarget.z);
    focus->x = ppc::fmadds(movedHorizontal, delta->x, m_WorldTarget.x);
    focus->y = ppc::fmadds(movedVertical, static_cast<float>(sign), y);
}

// 0x0015aa10 CKCameraClassicTrack3_IntegrateFollowSpring_maybe: the follow spring along the 3D direction to the
// focus (m_followSpeedXZ), in steps of at most 0.01 s: speed += step * (distance * m_followStiffness - damping * speed)
// (the distance counted from 0.1 up), or with the fixed spring (0x200) m_followAccelFixed - damping * speed. The
// previous focus becomes `focus`, and `focus` the target moved along `delta` (normalised in place) by the integrated
// distance. A distance below 0.1 ends the fixed spring and the no-framing flag (0x8000) unless the zone offset is null
// and 0x10 is clear.
void CKCameraClassicTrack3::IntegrateFollowOffset11C(float dt, CVector3* focus, CVector3* delta) {
    float remaining = Sqrtf(ppc::fmadds(delta->z, delta->z, ppc::fmadds(delta->x, delta->x, delta->y * delta->y)));
    if (remaining != 0.0f) {
        const float inverse = 1.0f / remaining;
        delta->z = inverse * delta->z;
        delta->x = inverse * delta->x;
        delta->y = inverse * delta->y;
    } else {
        remaining = 0.0f;
    }
    uint32_t flags = m_trackFlags;
    float damping = m_followDamping;
    if ((flags & 0x200u) != 0) {
        if (remaining < 0.1f) {
            m_trackFlags &= ~0x200u;
            flags = m_trackFlags;
        } else {
            damping = m_followDampingFixed;
        }
    }
    if ((flags & 0x8000u) != 0) {
        const bool keep = remaining >= 0.1f && m_zoneOffset.x == kNullVector.x && m_zoneOffset.y == kNullVector.y &&
                          m_zoneOffset.z == kNullVector.z && (flags & 0x10u) == 0;
        if (!keep) m_trackFlags &= ~0x8000u;
    }
    float moved = 0.0f;
    if (!(dt <= 0.0f)) {
        float timeLeft = dt;
        float speed = m_followSpeedXZ;
        const bool fixed = (m_trackFlags & 0x200u) != 0;
        for (;;) {
            float step;
            if (timeLeft > 0.01f) {
                timeLeft = timeLeft - 0.01f;
                step = 0.01f;
            } else {
                step = timeLeft;
                timeLeft = 0.0f;
            }
            float limit;
            if (fixed) {
                limit = remaining;
                speed = ppc::fmadds(step, ppc::fmadds(damping, -speed, m_followAccelFixed), speed);
            } else {
                limit = remaining >= 0.1f ? remaining : 0.0f;
                speed = ppc::fmadds(step, ppc::fmadds(remaining, m_followStiffness, damping * -speed), speed);
            }
            const float advance = step * speed;
            m_followSpeedXZ = speed;
            if (limit <= advance) {
                moved = moved + limit;
                break;
            }
            remaining = limit - advance;
            moved = moved + advance;
            if (remaining == 0.0f) break;
            if (timeLeft <= 0.0f) break;
        }
    }
    m_prevFocus.x = focus->x;
    m_prevFocus.z = focus->z;
    m_prevFocus.y = focus->y;
    focus->x = ppc::fmadds(moved, delta->x, m_WorldTarget.x);
    focus->z = ppc::fmadds(moved, delta->z, m_WorldTarget.z);
    focus->y = ppc::fmadds(moved, delta->y, m_WorldTarget.y);
}

// 0x0015acf0 CKCameraClassicTrack3_UpdateFollowOffsets_maybe: the target follows the focus. A stack change or the
// service's flag 0x1000000 (or the zone's offset change, m_trackFlags 0x10000) starts the fixed spring with the speeds
// at 0; while the fixed spring runs, the part of the focus's own motion that keeps the direction to it is added to the
// target at once. Then the vertical spring (IntegrateFollowOffset120) when the service's flag 0x4000000 is set and the
// focus is above, else the 3D one (IntegrateFollowOffset11C).
void CKCameraClassicTrack3::UpdateFollowOffsets(float dt, CVector3* focus) {
    CVector3 delta;
    delta.x = focus->x - m_WorldTarget.x;
    delta.y = focus->y - m_WorldTarget.y;
    delta.z = focus->z - m_WorldTarget.z;
    CKSrvCamera* camera = SrvCamera();
    uint32_t cameraFlags = camera->m_baTemporaryFlags;
    bool restart = (cameraFlags & 0x800000u) != 0 || (cameraFlags & 0x1000000u) != 0;
    if (!restart) {
        const uint32_t flags = m_trackFlags;
        if ((flags & 0x10000u) != 0) {
            restart = true;
        } else if ((flags & 0x200u) != 0) {
            CVector3 motion;
            motion.x = focus->x - m_prevFocus.x;
            motion.z = focus->z - m_prevFocus.z;
            motion.y = focus->y - m_prevFocus.y;
            if (!(motion.x <= 0.0f)) {
                if (!(delta.x >= 0.0f)) motion.x = 0.0f;
            } else if (!(motion.x >= 0.0f)) {
                if (delta.x > 0.0f) motion.x = 0.0f;
            }
            if (!(motion.y <= 0.0f)) {
                if (!(delta.y >= 0.0f)) motion.y = 0.0f;
            } else if (!(motion.y >= 0.0f)) {
                if (delta.y > 0.0f) motion.y = 0.0f;
            }
            if (!(motion.z <= 0.0f)) {
                if (!(delta.z >= 0.0f)) motion.z = 0.0f;
            } else if (!(motion.z >= 0.0f)) {
                if (delta.z > 0.0f) motion.z = 0.0f;
            }
            delta.y = delta.y - motion.y;
            delta.x = delta.x - motion.x;
            delta.z = delta.z - motion.z;
            m_WorldTarget.x = m_WorldTarget.x + motion.x;
            m_WorldTarget.y = m_WorldTarget.y + motion.y;
            m_WorldTarget.z = m_WorldTarget.z + motion.z;
        }
    }
    if (restart) {
        m_trackFlags = (m_trackFlags & ~0x200u) | 0x200u;
        m_followSpeedY = 0.0f;
        m_followSpeedXZ = 0.0f;
        m_trackFlags &= ~0x10000u;
    }
    cameraFlags = camera->m_baTemporaryFlags;
    if ((cameraFlags & 0x4000000u) != 0) {
        m_trackFlags = (m_trackFlags & ~0x8000u) | 0x8000u;
        cameraFlags = camera->m_baTemporaryFlags;
    }
    CVector3 direction = delta;
    if ((cameraFlags & 0x4000000u) != 0 && delta.y > 0.0f) {
        IntegrateFollowOffset120(dt, focus, &direction);
    } else {
        IntegrateFollowOffset11C(dt, focus, &direction);
    }
}

// m_right = y x view, normalised (the original inlines it in Start, ComputeDesiredPose, UpdateSteady and UpdateBlending).
void CKCameraClassicTrack3::UpdateRightVector() {
    m_right.x = ppc::fmsubs(kAxisY.y, m_viewDir.z, kAxisY.z * m_viewDir.y);
    m_right.y = ppc::fmsubs(kAxisY.z, m_viewDir.x, kAxisY.x * m_viewDir.z);
    m_right.z = ppc::fmsubs(kAxisY.x, m_viewDir.y, kAxisY.y * m_viewDir.x);
    const float length = Sqrtf(ppc::fmadds(m_right.z, m_right.z, ppc::fmadds(m_right.x, m_right.x, m_right.y * m_right.y)));
    if (length != 0.0f) {
        const float inverse = 1.0f / length;
        m_right.z = inverse * m_right.z;
        m_right.x = inverse * m_right.x;
        m_right.y = inverse * m_right.y;
    }
}

// The orbit position (inlined): x and z from the yaw's sine / cosine, scaled by the pitch's cosine, y raised by the
// pitch's sine.
void CKCameraClassicTrack3::OrbitPosition(const CVector3* focus, float yaw, float pitch, float distance, CVector3* out) {
    const float focusY = focus->y;
    const float focusZ = focus->z;
    const float sinYaw = GameSinf(yaw);
    const float cosPitchX = GameCosf(pitch);
    out->x = focus->x - cosPitchX * (sinYaw * distance);
    const float cosYaw = GameCosf(yaw);
    const float cosPitchZ = GameCosf(pitch);
    out->z = focusZ - cosPitchZ * (cosYaw * distance);
    const float sinPitch = GameSinf(pitch);
    out->y = ppc::fmadds(sinPitch, distance, focusY);
}

// 0x009a7d38 CKCameraConstraint_ComputeLookDirection_maybe: the constraint zone's look direction at `point` (its
// mode byte +0x38: 0 / 1 / 2 without an object, 1 a CKMarkerBeacon, 3 two CKFlaggedPaths; the look mode +0x1c bits
// 5-6): look mode 1 without object turns (0, 0, 1) by the zone's angle +0x44 about y (a marker beacon with flag 0x2000
// also tilts it towards the beacon); otherwise the direction to the beacon (negated with flag 0x400); no object: the z
// axis. Mode 2 with an object (an IKPath): the point projected on the path (vt+0x58 squared, then vt+0x54): look mode 1
// turns the path's direction there by the angle, else the direction to the projection. Mode 3 (step 6): the point's
// distance along the first flagged path's path, mapped through the two paths' beacon lists onto the second path; look
// mode 1 the direction from that point to the first path's point, else from `point` to it (negated with flag 0x400
// before the normalisation); flag 0x40000 moves the zone's up offset +0x74 by the first path's height over the point.
// STUB: mode 0 with an object (its +4 frame's at / position vectors +0x70 / +0x80) has no LVL010 zone and an unknown
// object type: the z axis is returned.
CVector3 CKCameraClassicTrack3::ComputeLookDirection(CKCameraConstraint* constraint, const CVector3* point) {
    const uint8_t mode = constraint->m_unk38;
    const CVector3 kAxisZ = {0.0f, 0.0f, 1.0f};  // 0x00c50d4c (TOC -0x37b0)
    CVector3 result;
    if (mode == 2 && constraint->m_unk3c != nullptr) {
        IKPath* path = static_cast<IKPath*>(constraint->m_unk3c);
        CVector3 onPath;
        if (ZoneLookMode(constraint) == 1) {
            CVector3 direction;
            const float distance = path->GetClosestDistanceAlong(point, 1);  // vt+0x58
            path->GetPointAtDistance(distance, &onPath, &direction);       // vt+0x54
            const float angle = constraint->m_afUnk44[0];  // +0x44
            const float c = GameCosf(angle);
            const float s = GameSinf(angle);
            result.x = ppc::fmsubs(c, direction.x, s * direction.z);
            result.y = -direction.y;
            result.z = ppc::fmadds(s, direction.x, c * direction.z);
            return result;
        }
        const float distance = path->GetClosestDistanceAlong(point, 1);
        path->GetPointAtDistance(distance, &onPath, nullptr);
        float y = onPath.y - point->y;
        float x = onPath.x - point->x;
        float z = onPath.z - point->z;
        const float length = Sqrtf(ppc::fmadds(z, z, ppc::fmadds(x, x, y * y)));
        if (length != 0.0f) {  // TOC -0x3874
            const float inverse = 1.0f / length;  // TOC -0x3884
            z = z * inverse;
            x = x * inverse;
            y = y * inverse;
        }
        if ((ZoneFlags(constraint) & 0x400u) != 0) {
            x = -x;
            y = -y;
            z = -z;
        }
        result.x = x;
        result.y = y;
        result.z = z;
        return result;
    }
    if (mode == 3) {
        if (constraint->m_unk3c == nullptr || constraint->m_unk40 == nullptr) return kAxisZ;
        const CKFlaggedPath* first = static_cast<const CKFlaggedPath*>(constraint->m_unk3c);
        const CKFlaggedPath* second = static_cast<const CKFlaggedPath*>(constraint->m_unk40);
        IKPath* firstPath = static_cast<IKPath*>(first->m_pPath);
        IKPath* secondPath = static_cast<IKPath*>(second->m_pPath);
        const float distance = firstPath->GetClosestDistanceAlong(point, 1);  // vt+0x58
        // The first beacon not below the distance closes the interval (the last interval when none).
        const uint32_t count = first->m_ui32NbOfBeacon;
        uint32_t interval = count - 2;
        if (count > 1) {
            for (uint32_t i = 1; i < count; ++i) {
                if (first->m_aBeaconList[i] >= distance) {  // cror gt|eq
                    interval = i - 1;
                    break;
                }
            }
        }
        const float a0 = first->m_aBeaconList[interval];
        const float span = first->m_aBeaconList[interval + 1] - a0;
        const float b0 = second->m_aBeaconList[interval];
        float mapped = second->m_aBeaconList[interval + 1];
        if (span != 0.0f) mapped = b0 + ((mapped - b0) * (distance - a0)) / span;
        CVector3 target;
        secondPath->GetPointAtDistance(mapped, &target, nullptr);  // vt+0x54
        if ((ZoneFlags(constraint) & 0x40000u) != 0) {
            CVector3 onFirst;
            firstPath->GetPointAtDistance(distance, &onFirst, nullptr);
            constraint->m_unk74 = IKCamera::AsWord(ZoneUpOffset(constraint) + (onFirst.y - point->y));
        }
        float x;
        float y;
        float z;
        if (ZoneLookMode(constraint) == 1) {
            CVector3 onFirst;
            firstPath->GetPointAtDistance(distance, &onFirst, nullptr);
            x = onFirst.x - target.x;
            y = onFirst.y - target.y;
            z = onFirst.z - target.z;
        } else {
            x = target.x - point->x;
            y = target.y - point->y;
            z = target.z - point->z;
            if ((ZoneFlags(constraint) & 0x400u) != 0) {
                x = -x;
                y = -y;
                z = -z;
            }
        }
        const float length = Sqrtf(ppc::fmadds(z, z, ppc::fmadds(x, x, y * y)));
        if (length != 0.0f) {
            const float inverse = 1.0f / length;
            z = z * inverse;
            x = x * inverse;
            y = y * inverse;
        }
        result.x = x;
        result.y = y;
        result.z = z;
        return result;
    }
    const uint32_t lookMode = ZoneLookMode(constraint);
    if (lookMode == 1) {
        if (mode == 0 && constraint->m_unk3c != nullptr) {
            DOTD_STUB_ONCE("CKCameraConstraint_ComputeLookDirection_maybe 0x9a7d38: zone mode 0 with an object, look mode 1 (no LVL010 zone; first level with one)");
            return kAxisZ;
        }
        const float angle = constraint->m_afUnk44[0];  // +0x44
        float z = GameCosf(angle);
        float x = -GameSinf(angle);
        float y;
        const CKMarkerBeacon* beacon = static_cast<const CKMarkerBeacon*>(constraint->m_unk3c);
        if (mode == 1 && beacon != nullptr && (ZoneFlags(constraint) & 0x2000u) != 0) {
            float dy = beacon->m_v3Position.y - point->y;
            const float dx = beacon->m_v3Position.x - point->x;
            const float dz = beacon->m_v3Position.z - point->z;
            const float length = Sqrtf(ppc::fmadds(dz, dz, ppc::fmadds(dx, dx, dy * dy)));
            if (length != 0.0f) dy = dy * (1.0f / length);
            const float tilt = GameCosf(crt::Asinf(dy));
            z = z * tilt;
            x = x * tilt;
            y = -dy;
        } else {
            y = 0.0f;
        }
        result.x = x;
        result.y = y;
        result.z = z;
        return result;
    }
    if (constraint->m_unk3c == nullptr) return kAxisZ;
    if (mode != 1) {
        DOTD_STUB_ONCE("CKCameraConstraint_ComputeLookDirection_maybe 0x9a7d38: zone mode 0 with an object (no LVL010 zone; first level with one)");
        return kAxisZ;
    }
    const CKMarkerBeacon* beacon = static_cast<const CKMarkerBeacon*>(constraint->m_unk3c);
    float y = beacon->m_v3Position.y - point->y;
    float x = beacon->m_v3Position.x - point->x;
    float z = beacon->m_v3Position.z - point->z;
    const float length = Sqrtf(ppc::fmadds(z, z, ppc::fmadds(x, x, y * y)));
    if (length != 0.0f) {
        const float inverse = 1.0f / length;
        z = z * inverse;
        x = x * inverse;
        y = y * inverse;
    }
    if ((ZoneFlags(constraint) & 0x400u) != 0) {
        x = -x;
        y = -y;
        z = -z;
    }
    result.x = x;
    result.y = y;
    result.z = z;
    return result;
}

// 0x0015ddc0 CKCameraClassicTrack3_ComputeDesiredPose_maybe: m_blendEnd for the focus and the constraint zone: the pitch
// (the focus targets' or the zone's +0x4c with its flag 1, or the zone's look direction's with flag 0x2000), clamped to
// +-1.45; the yaw: the current one in look mode 2, else the zone's look direction's, kept within the zone's yaw range
// of the current one (look mode 1); the orbit position at the end distance, the view direction and m_right from it, the
// zone's orbit limits (flag 0x200, COLL), the framing push of the focus targets added to the end distance, and the
// obstruction test from the focus to the final position. `position` (the caller's buffer) is not used.
void CKCameraClassicTrack3::ComputeDesiredPose(CVector3* /*position*/, const CVector3* focus, uint32_t keepYaw) {
    CKSrvCamera* camera = SrvCamera();
    float pitch = m_desiredPitch;
    m_blendEnd.m_pitch = pitch;
    m_blendEnd.m_focus.x = focus->x;
    m_blendEnd.m_focus.z = focus->z;
    m_blendEnd.m_focus.y = focus->y;
    CKCameraConstraint* zone = m_pConstraint;
    if ((ZoneFlags(zone) & 1u) != 0) {
        pitch = ZonePitch(zone);
        m_blendEnd.m_pitch = pitch;
    }
    if (ZoneLookMode(zone) == 2) {
        m_blendEnd.m_yaw = Vec3_GetYawAngleFromZ(&m_viewDir);
        m_blendStart.m_yaw = Vec3_GetYawAngleFromZ(&m_viewDir);
    } else {
        m_lookDirection = ComputeLookDirection(zone, focus);
        if (keepYaw == 0) {
            zone = m_pConstraint;
            if (ZoneLookMode(zone) == 1) {
                m_volumeYawRange = ZoneYawRange(zone);
            } else {
                m_volumeYawRange = 0.0f;
            }
        } else {
            m_volumeYawRange = 0.0f;
        }
        float viewYaw;
        float difference;
        const bool zeroLook = m_lookDirection.x == 0.0f && m_lookDirection.z == 0.0f;
        if ((ZoneFlags(m_pConstraint) & 0x2000u) != 0) {
            m_blendEnd.m_pitch = -crt::Asinf(m_lookDirection.y);
            viewYaw = Vec3_GetYawAngleFromZ(&m_viewDir);
            if (zeroLook) {
                difference = viewYaw - viewYaw;
            } else {
                difference = Vec3_GetYawAngleFromZ(&m_lookDirection) - viewYaw;
            }
        } else {
            const float yaw = Vec3_GetYawAngleFromZ(&m_viewDir);
            viewYaw = yaw;
            if (zeroLook) {
                difference = yaw - viewYaw;
            } else {
                difference = Vec3_GetYawAngleFromZ(&m_lookDirection) - viewYaw;
            }
        }
        // The difference wrapped into [-pi, pi], then the yaw range taken off towards 0. (The two paths test the upper
        // bound the other way round: they differ for a NaN only.)
        bool positive;
        if (zeroLook ? !(difference <= kPi) : difference > kPi) {
            difference = difference - kTwoPi;
            positive = !(difference <= 0.0f);
        } else if (difference >= kMinusPi) {
            positive = !(difference <= 0.0f);
        } else {
            difference = difference + kTwoPi;
            positive = difference > 0.0f;
        }
        if (positive) {
            difference = difference - m_volumeYawRange;
            if (difference < 0.0f) difference = 0.0f;
        } else {
            difference = difference + m_volumeYawRange;
            if (!(difference <= 0.0f)) difference = 0.0f;
        }
        m_blendEnd.m_yaw = difference + viewYaw;
    }
    pitch = m_blendEnd.m_pitch;
    if (pitch <= -1.45f) {
        m_blendEnd.m_pitch = -1.45f;
    } else if (pitch >= 1.45f) {
        m_blendEnd.m_pitch = 1.45f;
    } else {
        m_blendEnd.m_pitch = pitch;
    }
    CVector3 orbit;
    OrbitPosition(focus, m_blendEnd.m_yaw, m_blendEnd.m_pitch, m_blendEnd.m_distance, &orbit);
    // The view direction from the orbit position and m_right.
    m_viewDir.x = focus->x - orbit.x;
    m_viewDir.z = focus->z - orbit.z;
    m_viewDir.y = focus->y - orbit.y;
    const float length = Sqrtf(ppc::fmadds(m_viewDir.z, m_viewDir.z, ppc::fmadds(m_viewDir.x, m_viewDir.x, m_viewDir.y * m_viewDir.y)));
    if (length != 0.0f) {
        const float inverse = 1.0f / length;
        m_viewDir.z = inverse * m_viewDir.z;
        m_viewDir.x = inverse * m_viewDir.x;
        m_viewDir.y = inverse * m_viewDir.y;
    }
    UpdateRightVector();
    if ((ZoneFlags(m_pConstraint) & 0x200u) != 0) {
        ConstrainOrbitAnglesToVolume(&orbit, focus, m_pConstraint);
        OrbitPosition(focus, m_blendEnd.m_yaw, m_blendEnd.m_pitch, m_blendEnd.m_distance, &orbit);
    }
    float push = 0.0f;
    BuildFrustumPlanes(&orbit);
    if (StackCount(camera) != 0) {
        for (uint32_t i = 0; (i & 0xffu) < StackCount(camera); ++i) {
            const CKSrvCamera::StackEntry& entry = StackAt(camera, i & 0xffu);
            if (entry.m_unk05 == 0) continue;
            const float* entryPosition = StackPosition(entry);
            float radius = entry.m_unk08;
            const float y = ppc::fmadds(StackRecord(camera, entry, 4), entry.m_unk10[2], entryPosition[1]);
            const float x = entryPosition[0];
            const float z = entryPosition[2];
            if (radius == -1.0f) radius = StackRecord(camera, entry, 3);
            const CKCameraConstraint* entryZone = m_pConstraint;
            radius = radius * entry.m_unk10[3];
            if ((ZoneFlags(entryZone) & 0x10u) != 0) {
                radius = radius * ZoneFramingScale(entryZone);
            } else if ((ZoneFlags(entryZone) & 0x20000u) != 0) {
                radius = ZoneFramingScale(entryZone);
            }
            const float entryPush = FramingPush(x, y, z, radius);
            // (The original runs the plane loop a second time, with the same values, when the push is the largest.)
            if (!(entryPush < push)) push = entryPush;
        }
    }
    m_blendEnd.m_distance = m_blendEnd.m_distance + push;
    OrbitPosition(focus, m_blendEnd.m_yaw, m_blendEnd.m_pitch, m_blendEnd.m_distance, &orbit);
    CVector3 from = *focus;
    TestCameraObstruction(&from, &orbit);
}

namespace {
// The magnitude of an angle difference wrapped into [-pi, pi] (CaptureBlendStart inlines it twice): the wrapped value
// decides the sign, then the difference is wrapped again and negated when it was negative (the original's compares).
float WrappedAngleMagnitude(float d) {
    bool negative;
    if (!(d <= kPi)) {
        negative = (d - kTwoPi) < 0.0f;
    } else if (d >= kMinusPi) {
        negative = d < 0.0f;
    } else {
        negative = !((d + kTwoPi) >= 0.0f);
    }
    if (negative) {
        if (!(d <= kPi)) return -(d - kTwoPi);
        if (d >= kMinusPi) return -d;
        return -(d + kTwoPi);
    }
    if (!(d <= kPi)) return d - kTwoPi;
    if (!(d >= kMinusPi)) return d + kTwoPi;
    return d;
}
}  // namespace

// 0x0015f520 CKCameraClassicTrack3_CaptureBlendStart_maybe: m_blendStart from the current pose (or from the running
// blend's current pose, m_blendSpeed then the smoothstep slope 6t - 6t^2 at its time), m_blendEnd from
// ComputeDesiredPose at the default distance, and the blend's duration: the largest of yaw difference / 1.5, pitch
// difference / 0.75, distance difference * 0.125 and focus distance / 4.5, times `timeScale` unless that is -1; a time
// scale of 0 or a focus jump of more than 15 skips the blend (m_trackFlags 0x40000).
void CKCameraClassicTrack3::CaptureBlendStart(float timeScale, CVector3* position, CVector3* target) {
    if (m_blendDuration <= 0.0f) {
        m_blendStart.m_distance = m_distance;
        m_blendStart.m_pitch = m_pitch.m_current;
        m_blendStart.m_focus.x = target->x;
        m_blendStart.m_focus.y = target->y;
        m_blendStart.m_focus.z = target->z;
        CVector3 view = m_viewDir;
        m_blendStart.m_yaw = Vec3_GetYawAngleFromZ(&view);
    } else {
        const float t = m_blendTime / m_blendDuration;
        m_blendSpeed = ppc::fmadds(t, t * -6.0f, t * 6.0f);
        m_blendStart.m_distance = m_blendCurrent.m_distance;
        m_blendStart.m_pitch = m_blendCurrent.m_pitch;
        m_blendStart.m_yaw = m_blendCurrent.m_yaw;
        m_blendStart.m_focus.x = m_blendCurrent.m_focus.x;
        m_blendStart.m_focus.y = m_blendCurrent.m_focus.y;
        m_blendStart.m_focus.z = m_blendCurrent.m_focus.z;
    }
    m_blendDuration = 0.0f;
    m_blendTime = 0.0f;
    CVector3 focus;
    ComputeFocusPoint(&focus);
    m_prevFocus.x = focus.x;
    m_prevFocus.z = focus.z;
    m_prevFocus.y = focus.y;
    m_blendEnd.m_distance = m_defaultDistance;
    m_blendCurrent.m_yaw = m_blendStart.m_yaw;
    ComputeDesiredPose(position, &focus, (ZoneFlags(m_pConstraint) >> 5) & 1u);
    if (timeScale == 0.0f) {
        m_blendDuration = 0.0f;
        m_unk44Approach.m_current = m_unk44Approach.m_target;
        m_trackFlags = (m_trackFlags & ~0x40000u) | 0x40000u;
        return;
    }
    // The yaw and pitch differences wrapped into [-pi, pi], as magnitudes.
    const float yawDifference = WrappedAngleMagnitude(m_blendEnd.m_yaw - m_blendStart.m_yaw);
    const float pitchDifference = WrappedAngleMagnitude(m_blendEnd.m_pitch - m_blendStart.m_pitch);
    const float dx = m_blendEnd.m_focus.x - m_blendStart.m_focus.x;
    const float dy = m_blendEnd.m_focus.y - m_blendStart.m_focus.y;
    const float dz = m_blendEnd.m_focus.z - m_blendStart.m_focus.z;
    const float distanceDifference = std::fabs(m_blendEnd.m_distance - m_blendStart.m_distance);
    const float focusDistance = Sqrtf(ppc::fmadds(dz, dz, ppc::fmadds(dx, dx, dy * dy)));
    m_blendDuration = 0.0f;
    m_blendTimeScale = timeScale;
    if (focusDistance > 15.0f) {
        m_trackFlags = (m_trackFlags & ~0x40000u) | 0x40000u;
        return;
    }
    float duration = 0.0f;
    const float byYaw = yawDifference / 1.5f;
    if (!(duration > byYaw)) duration = byYaw;
    const float byPitch = pitchDifference / 0.75f;
    if (!(duration > byPitch)) duration = byPitch;
    const float byDistance = distanceDifference * 0.125f;
    if (!(duration > byDistance)) duration = byDistance;
    const float byFocus = focusDistance / 4.5f;
    if (!(duration > byFocus)) duration = byFocus;
    m_blendDuration = duration;
    if (timeScale != -1.0f) m_blendDuration = duration * timeScale;
    m_trackFlags &= ~0x40000u;
}

namespace {

// The right stick's axis from the game manager's direction states (vt+0x188 GetDirectionActionState: 0 / 1 the y axis,
// 2 / 3 the x axis), (positive - negative) / 255.
float StickAxis(CKS08GameManager* manager, uint8_t positive, uint8_t negative) {
    const uint8_t a = manager->GetDirectionActionState(positive);
    const uint8_t b = manager->GetDirectionActionState(negative);
    return static_cast<float>(static_cast<double>(static_cast<int32_t>(a) - static_cast<int32_t>(b))) / 255.0f;
}

// A stick speed towards +-limit (the yaw, zoom and pitch speeds of ApplyStickYaw share the pattern): pushing (axis > 0)
// from a negative speed starts at 0, below the limit accelerates, above it brakes down to it; pulling (axis <= 0) is the
// mirror image; then the speed is clamped to [-limit, limit].
float StickSpeed(float dt, float axis, float limit, float speed, float* stored, float accel, float decel) {
    float result;
    if (!(axis <= 0.0f)) {
        if (speed < 0.0f) {
            *stored = 0.0f;
            speed = 0.0f;
        }
        if (limit >= speed) {
            *stored = ppc::fmadds(dt, accel, speed);
        } else {
            const float braked = speed - dt * decel;
            *stored = braked;
            if (!(limit <= braked)) *stored = limit;
        }
    } else {
        if (speed > 0.0f) {
            speed = 0.0f;
            *stored = 0.0f;
        }
        const float minusLimit = -limit;
        if (speed >= minusLimit) {
            *stored = speed - dt * accel;
        } else {
            const float braked = ppc::fmadds(dt, decel, speed);
            *stored = braked;
            if (!(minusLimit >= braked)) *stored = minusLimit;
        }
    }
    const float value = *stored;
    const float minusLimit = -limit;
    if (minusLimit >= value) {
        result = minusLimit;
    } else if (limit <= value) {
        result = limit;
    } else {
        result = value;
    }
    return result;
}

// A stick speed without input: back to 0 by `decel` per second.
void StickSpeedDecay(float dt, float decel, float* speed) {
    const float value = *speed;
    if (value <= 0.0f) {
        if (value >= 0.0f) return;
        const float next = ppc::fmadds(dt, decel, value);
        *speed = next;
        if (next > 0.0f) *speed = 0.0f;
    } else {
        const float next = value - dt * decel;
        *speed = next;
        if (next < 0.0f) *speed = 0.0f;
    }
}

}  // namespace

// 0x0015ce68 CKCameraClassicTrack3_ApplyRightStick_maybe: the right stick (the game manager's direction states, while the
// camera service's flag 0x200000 allows it and the zone's flag 2 is set; none with the service's flag 4): x turns the
// view direction about y (m_yawStickSpeed), y changes the orbit distance (m_zoomStickSpeed) and the stick pitch
// (m_pitchStickSpeed) within the stick range; without input the speeds decay. The stick pitch returns to the pitch
// limits / the focus pitch when the stick is let go; without a zone a low stick pitch pulls the camera in and down. When
// anything moved, `position` is placed at the target - distance * view.
void CKCameraClassicTrack3::ApplyStickYaw(float dt, CVector3* position) {
    CKSrvCamera* const camera = SrvCamera();
    CKS08GameManager* const manager = static_cast<CKS08GameManager*>(g_pEngine->m_gameManager);
    m_Flags &= ~0x10000u;
    uint32_t zoneAllows = 1;
    if (m_pConstraint != nullptr) zoneAllows = (ZoneFlags(m_pConstraint) >> 1) & 1u;
    float zoomSpeed;
    if ((camera->m_baTemporaryFlags & 0x4u) != 0) {
        zoomSpeed = 0.0f;
        m_zoomStickSpeed = zoomSpeed;
        m_yawStickSpeed = 0.0f;
        m_pitchStickSpeed = zoomSpeed;
    } else {
        // The yaw speed (the stick's x).
        bool yawInput = false;
        if ((SrvCamera()->m_baTemporaryFlags & 0x200000u) != 0 && (zoneAllows & 0xffu) != 0) {
            float axis = StickAxis(manager, 3, 2);
            if (axis != 0.0f) {
                yawInput = true;
                CKSrvCamera* flagged = SrvCamera();
                flagged->m_baTemporaryFlags = (flagged->m_baTemporaryFlags & ~0x100000u) | 0x100000u;
                m_Flags = (m_Flags & ~0x10000u) | 0x10000u;
                if (manager->Vf1B8() != 0) axis = -axis;
                float limit = axis * m_yawStickMaxSpeed;
                if (limit < 0.0f) limit = -limit;
                m_yawStickSpeed = StickSpeed(dt, axis, limit, m_yawStickSpeed, &m_yawStickSpeed, m_yawStickAccel, m_yawStickDecel);
            }
        }
        if (!yawInput) StickSpeedDecay(dt, m_yawStickDecel, &m_yawStickSpeed);
        // The zoom and pitch speeds (the stick's y).
        bool pitchInput = false;
        if ((SrvCamera()->m_baTemporaryFlags & 0x200000u) != 0 && (zoneAllows & 0xffu) != 0) {
            float axis = StickAxis(manager, 0, 1);
            if (axis != 0.0f) {
                pitchInput = true;
                CKSrvCamera* flagged = SrvCamera();
                flagged->m_baTemporaryFlags = (flagged->m_baTemporaryFlags & ~0x100000u) | 0x100000u;
                m_Flags = (m_Flags & ~0x10000u) | 0x10000u;
                if (manager->Vf1B0() != 0) axis = -axis;
                float zoomLimit = axis * m_zoomStickMaxSpeed;
                if (zoomLimit < 0.0f) zoomLimit = -zoomLimit;
                m_zoomStickSpeed = StickSpeed(dt, axis, zoomLimit, m_zoomStickSpeed, &m_zoomStickSpeed, m_zoomStickAccel, m_zoomStickDecel);
                const float pitchLimit = std::fabs(axis * m_pitchStickMaxSpeed);
                const float pitchSpeed = StickSpeed(dt, axis, pitchLimit, m_pitchStickSpeed, &m_pitchStickSpeed, m_pitchStickAccel, m_pitchStickDecel);
                zoomSpeed = m_zoomStickSpeed;
                m_pitchStickSpeed = pitchSpeed;
            }
        }
        if (!pitchInput) {
            StickSpeedDecay(dt, m_zoomStickDecel, &m_zoomStickSpeed);
            zoomSpeed = m_zoomStickSpeed;
            StickSpeedDecay(dt, m_pitchStickDecel, &m_pitchStickSpeed);
        }
    }
    uint32_t moved = 0;
    // The yaw: the view direction turned about y by -dt * speed.
    if (m_yawStickSpeed != 0.0f) {
        const float angle = dt * -m_yawStickSpeed;
        const float x = m_viewDir.x;
        const float z = m_viewDir.z;
        const float cosine = GameCosf(angle);
        const float sine = GameSinf(angle);
        m_viewDir.x = ppc::fmsubs(cosine, x, sine * z);
        const float sine2 = GameSinf(angle);
        const float cosine2 = GameCosf(angle);
        moved = 1;
        m_viewDir.z = ppc::fmadds(sine2, x, cosine2 * z);
    }
    // The zoom: the distance changed by dt * speed (only inwards at the longest distance).
    if (zoomSpeed != 0.0f) {
        m_trackFlags = (m_trackFlags & ~0x40u) | 0x40u;
        const float distance = m_distance;
        m_pullInSpeed = 0.0f;
        if (m_maxDistance <= distance) {
            if (!(m_zoomStickSpeed >= 0.0f)) m_distance = ppc::fmadds(dt, m_zoomStickSpeed, distance);
        } else {
            m_distance = ppc::fmadds(dt, m_zoomStickSpeed, distance);
        }
        m_wallDistance = -1.0f;
        moved = 1;
    }
    CKCameraConstraint* zone;
    bool reposition = false;
    bool checkZone = true;
    if (m_pitchStickSpeed != 0.0f) {
        // The stick pitch: moved by the stick within [m_stickPitchMin, m_stickPitchMax] ([0, max] while the service's
        // byte +0xe28 is set).
        const bool alternate = ((camera->m_unke28 >> 24) & 0xffu) != 0;
        const float maximum = m_stickPitchMax;
        const float minimum = alternate ? 0.0f : m_stickPitchMin;
        const float pullScale = alternate ? 0.35f : 0.5f;
        uint32_t flags = (m_trackFlags & ~0x20u) | 0x20u;
        flags = (flags & ~0x40u) | 0x40u;
        m_trackFlags = flags;
        const float pitch = ppc::fmadds(dt, m_pitchStickSpeed, m_stickPitch);
        m_stickPitch = pitch;
        if (alternate ? !(maximum >= pitch) : maximum < pitch) {
            m_stickPitch = maximum;
            m_pitchStickSpeed = 0.0f;
        } else if (!(minimum <= pitch)) {
            m_pitchStickSpeed = 0.0f;
            m_stickPitch = minimum;
        }
        zone = m_pConstraint;
        moved = 1;
        if (m_zoomStickMaxSpeed == 0.0f) {
            if (zone == nullptr) {
                // Without a zone: a stick pitch at the bottom of every limit pulls the camera in (and the focus down).
                const float stickPitch = m_stickPitch;
                const bool low = minimum >= stickPitch || m_pitchMinA >= stickPitch || stickPitch <= m_pitchMinB;
                if (low && !(m_pitchMaxA <= stickPitch)) {
                    if (!(m_framingScaleTarget >= pullScale) || !(m_framingScale >= pullScale)) {
                        reposition = true;
                        checkZone = false;
                    } else {
                        m_framingScaleTarget = pullScale;
                        if ((m_trackFlags & 0x400u) == 0) m_distance = ppc::fmadds(dt, -3.0f, m_distance);
                        if (((camera->m_unke28 >> 24) & 0xffu) == 0) {
                            const float height = m_focusHeightOffset;
                            if (!(height <= -1.2f)) {
                                const float lowered = ppc::fmadds(dt, -2.0f, height);
                                m_focusHeightOffset = lowered;
                                if (!(lowered >= -1.2f)) m_focusHeightOffset = -1.2f;
                            }
                        }
                        checkZone = true;
                    }
                } else {
                    m_framingScaleTarget = 1.0f;
                }
            } else {
                m_framingScaleTarget = 1.0f;
            }
        }
    } else {
        zone = m_pConstraint;
    }
    if (checkZone && zone != nullptr && (ZoneFlags(zone) & 0x100u) != 0) {
        // The zone's pitch range about the focus pitch.
        const float upper = m_desiredPitch + ZonePitchUp(zone);
        if (m_stickPitch > upper) {
            m_stickPitch = upper;
            m_pitchStickSpeed = 0.0f;
        } else {
            const float lower = m_desiredPitch - ZonePitchDown(zone);
            if (!(m_stickPitch >= lower)) {
                m_stickPitch = lower;
                m_pitchStickSpeed = 0.0f;
            }
        }
    }
    if (reposition || moved != 0) {
        const float back = -m_distance;
        position->z = ppc::fmadds(back, m_viewDir.z, m_WorldTarget.z);
        position->x = ppc::fmadds(back, m_viewDir.x, m_WorldTarget.x);
        position->y = ppc::fmadds(back, m_viewDir.y, m_WorldTarget.y);
        m_wallDistance = -1.0f;
        return;
    }
    // Nothing moved: the stick pitch back to the focus pitch clamped to the pitch limits.
    float lower = m_pitchMinA;
    if (!(lower > m_pitchMinB)) lower = m_pitchMinB;
    float upper = m_pitchMaxB;
    if (!(m_pitchMaxA > upper)) upper = m_pitchMaxA;
    const float desired = m_desiredPitch;
    float target;
    if (lower >= desired) {
        target = lower;
    } else if (!(upper <= desired)) {
        target = desired;
    } else {
        target = upper;
    }
    const uint32_t flags = m_trackFlags;
    if ((flags & 0x40u) == 0) {
        if ((flags & 0x20u) == 0) {
            m_stickPitch = target;
        } else {
            const float current = m_stickPitch;
            if (target >= current) {
                const float next = ppc::fmadds(dt, m_pitchReturnSpeed, current);
                m_stickPitch = next;
                if (!(target >= next)) {
                    m_stickPitch = target;
                    m_trackFlags &= ~0x20u;
                }
            } else {
                const float next = current - dt * m_pitchReturnSpeed;
                m_stickPitch = next;
                if (!(target <= next)) {
                    m_stickPitch = target;
                    m_trackFlags &= ~0x20u;
                }
            }
        }
    } else {
        bool release = (flags & 0x10u) != 0;
        if (!release) {
            if (zone != nullptr && (ZoneFlags(zone) & 0x100u) != 0) release = true;
            else if ((camera->m_baTemporaryFlags & 0x800000u) != 0) release = true;
            else if ((camera->m_baTemporaryFlags & 0x1000000u) != 0) release = true;
        }
        if (release) m_trackFlags &= ~0x40u;
    }
    m_wallDistance = m_distance;
}

namespace {

// An angle difference wrapped into [-pi, pi] by one turn (the original's compares: above pi, else below -pi).
inline float WrapTurn(float d) {
    if (!(d <= kPi)) return d - kTwoPi;
    if (!(d >= kMinusPi)) return d + kTwoPi;
    return d;
}

}  // namespace

// 0x001615c8 CKCameraClassicTrack3_UpdateSteady_maybe: the follow update outside a blend. The orbit distance and the
// pitch from the current pose; the focus point followed by the springs (UpdateFollowOffsets) becomes the target; the
// zone gives the fov (+0x78 when not negative), the focus pitch (+0x4c, or its look direction's) and the heading: towards
// the focus from the target moved along the view by the lead (look mode 2, a yaw range, or flag 0x20000; the yaw range
// keeps it about m_volumeYaw with m_trackFlags 0x80), else the current one. The pitch approaches the stick pitch clamped
// to the limits (the stick's speed while the stick holds it); the distance shrinks back to the default (m_pullInSpeed);
// then the right stick, the framing, the zone's volume (COLL) and the collisions (COLL: walls, the constraint plane or
// the view obstructions, the ground) place the camera.
void CKCameraClassicTrack3::UpdateSteady(float dt) {
    CKSrvCamera* const camera = SrvCamera();
    m_lookDirection = kNullVector;
    m_trackFlags = (m_trackFlags & ~0x10u) | (((camera->m_baTemporaryFlags >> 25) & 1u) << 4);
    {
        const float dx = m_WorldTarget.x - m_WorldPosition.x;
        const float dy = m_WorldTarget.y - m_WorldPosition.y;
        const float dz = m_WorldTarget.z - m_WorldPosition.z;
        m_distance = Sqrtf(ppc::fmadds(dz, dz, ppc::fmadds(dx, dx, dy * dy)));
    }
    // The view direction flattened.
    float viewX = m_WorldTarget.x - m_WorldPosition.x;
    const float viewY = m_WorldTarget.y - m_WorldPosition.y;
    float viewZ = m_WorldTarget.z - m_WorldPosition.z;
    m_viewDir.x = viewX;
    m_viewDir.y = viewY;
    m_viewDir.y = 0.0f;
    m_viewDir.z = viewZ;
    float horizontal = Sqrtf(ppc::fmadds(viewZ, viewZ, ppc::fmadds(viewX, viewX, m_viewDir.y * m_viewDir.y)));
    if (horizontal != 0.0f) {
        const float inverse = 1.0f / horizontal;
        viewZ = inverse * m_viewDir.z;
        viewX = inverse * m_viewDir.x;
        m_viewDir.z = viewZ;
        m_viewDir.x = viewX;
        m_viewDir.y = inverse * m_viewDir.y;
    } else {
        horizontal = 0.0f;
        viewX = m_viewDir.x;
        viewZ = m_viewDir.z;
    }
    // The lead: the target moved along the flat view by a lerp of m_leadAtMinDistance / m_leadAtMaxDistance.
    const float leadSpan = m_leadAtMaxDistance - m_leadAtMinDistance;
    const float rangeSpan = m_maxDistance - m_minDistance;
    const float lead = -(m_leadAtMinDistance + leadSpan * (horizontal - m_minDistance) / rangeSpan);
    float sinePitch = (m_WorldPosition.y - m_WorldTarget.y) / m_distance;
    const float leadZ = ppc::fmadds(lead, viewZ, m_WorldTarget.z);
    const float leadX = ppc::fmadds(lead, viewX, m_WorldTarget.x);
    if (sinePitch <= -1.0f) {
        sinePitch = -1.0f;
    } else if (sinePitch >= 1.0f) {
        sinePitch = 1.0f;
    }
    m_pitch.m_current = crt::Asinf(sinePitch);
    if ((m_trackFlags & 0x40u) == 0) {
        const float height = m_focusHeightOffset;
        if (height != 0.0f) {
            if (height < 0.0f) {
                const float next = dt + height;
                m_focusHeightOffset = next;
                if (next > 0.0f) m_focusHeightOffset = 0.0f;
            } else {
                const float next = height - dt;
                m_focusHeightOffset = next;
                if (!(next >= 0.0f)) m_focusHeightOffset = 0.0f;
            }
        }
    }
    CVector3 focus;
    ComputeFocusPoint(&focus);
    UpdateFollowOffsets(dt, &focus);
    CVector3 position = m_WorldPosition;
    float fov = m_fFov;
    CVector3 direction;  // the heading (y 0), then the view direction
    bool clampYaw = false;
    bool towardsFocus;
    CKCameraConstraint* zone = m_pConstraint;
    if (zone == nullptr) {
        towardsFocus = (camera->m_baTemporaryFlags & 0x8000000u) == 0;
    } else {
        if (ZoneFov(zone) >= 0.0f) fov = ZoneFov(zone);
        if ((ZoneFlags(zone) & 1u) != 0) {
            m_desiredPitch = ZonePitch(zone);
        } else if ((ZoneFlags(zone) & 0x2000u) != 0 && ZoneLookMode(zone) != 2) {
            m_lookDirection = ComputeLookDirection(zone, &m_prevFocus);
            m_desiredPitch = -crt::Asinf(m_lookDirection.y);
        }
        zone = m_pConstraint;
        const uint32_t lookMode = ZoneLookMode(zone);
        const float range = lookMode == 1 ? ZoneYawRange(zone) : 0.0f;
        if (lookMode == 2) {
            towardsFocus = true;
        } else if (range != 0.0f || (m_trackFlags & 0x20000u) != 0) {
            towardsFocus = true;
            clampYaw = true;
        } else {
            towardsFocus = false;
        }
    }
    if (towardsFocus) {
        direction.x = focus.x - leadX;
        direction.y = 0.0f;
        direction.z = focus.z - leadZ;
    } else {
        direction.x = m_WorldTarget.x - m_WorldPosition.x;
        direction.y = 0.0f;
        direction.z = m_WorldTarget.z - m_WorldPosition.z;
    }
    {
        const float length = Sqrtf(ppc::fmadds(direction.z, direction.z, ppc::fmadds(direction.x, direction.x, 0.0f)));
        if (length != 0.0f) {
            const float inverse = 1.0f / length;
            direction.z = direction.z * inverse;
            direction.y = direction.y * inverse;
            direction.x = direction.x * inverse;
        }
    }
    if (clampYaw && (m_trackFlags & 0x80u) != 0) {
        // The heading kept within the zone's yaw range about m_volumeYaw (the edge, or the current yaw, it crosses).
        const float viewYaw = Vec3_GetYawAngleFromZ(&m_viewDir);
        const float yaw = Vec3_GetYawAngleFromZ(&direction);
        const float low = m_volumeYaw - m_volumeYawRange;
        bool clamp = false;
        float clamped = 0.0f;
        if (!(WrapTurn(yaw - low) >= 0.0f) && !(WrapTurn(yaw - viewYaw) >= 0.0f)) {
            clamp = true;
            clamped = WrapTurn(low - viewYaw) < 0.0f ? low : viewYaw;
        } else if (WrapTurn(yaw - low) >= 0.0f || WrapTurn(yaw - viewYaw) >= 0.0f) {
            const float high = m_volumeYaw + m_volumeYawRange;
            if (!(WrapTurn(yaw - high) <= 0.0f) && !(WrapTurn(yaw - viewYaw) <= 0.0f)) {
                clamp = true;
                clamped = WrapTurn(high - viewYaw) > 0.0f ? high : viewYaw;
            }
        }
        if (clamp) {
            direction.x = GameSinf(clamped);
            direction.y = 0.0f;
            direction.z = GameCosf(clamped);
        }
    }
    // The field of view.
    if (m_requestedFov == -1.0f) {
        m_fov.m_target = fov;
        Math_ApproachWithAccelDecel(dt, m_fov.Data());
        m_unk18 = m_fov.m_current;
    } else {
        m_fov.m_target = m_requestedFov;
        m_fov.m_current = m_requestedFov;
        m_unk18 = m_requestedFov;
    }
    // The pitch: towards the stick pitch clamped to the limits.
    float lower = m_pitchMinA;
    if (!(lower > m_pitchMinB)) lower = m_pitchMinB;
    float upper = m_pitchMaxB;
    if (!(m_pitchMaxA > upper)) upper = m_pitchMaxA;
    const float stickPitch = m_stickPitch;
    float targetPitch;
    if (lower >= stickPitch) {
        targetPitch = lower;
    } else if (upper <= stickPitch) {
        targetPitch = upper;
    } else {
        targetPitch = stickPitch;
    }
    m_stickPitch = targetPitch;
    m_pitch.m_target = targetPitch;
    const uint32_t flags = m_trackFlags;
    if ((flags & 0x20u) != 0 && (flags & 0x40u) != 0 && !((targetPitch - m_pitch.m_current) * m_pitchStickSpeed <= 0.0f)) {
        m_pitch.m_speed = m_pitchStickSpeed;
        float limit = m_pitchStickSpeed;
        if (limit < 0.0f) limit = -limit;
        m_pitch.m_maxSpeed = limit;
        m_pitch.m_accel = m_pitchStickAccel;
    } else {
        m_pitch.m_maxSpeed = kTwoPi;
        m_pitch.m_accel = m_pitchAccel;
    }
    if ((camera->m_baTemporaryFlags & 0x800u) == 0 && (m_trackFlags & 0x2000u) == 0) {
        Math_ApproachAngleWithAccelDecel(dt, m_pitch.Data());
    } else {
        m_pitch.m_speed = 0.0f;
    }
    float pitch = m_pitch.m_current;
    if (pitch > kPi) pitch = pitch - kTwoPi;
    if (pitch <= -1.45f) {
        pitch = -1.45f;
    } else if (pitch >= 1.45f) {
        pitch = 1.45f;
    }
    m_pitch.m_current = pitch;
    {
        const float cosine = GameCosf(pitch);
        direction.x = direction.x * cosine;
        direction.z = direction.z * cosine;
        direction.y = direction.y * cosine;
        direction.y = -GameSinf(m_pitch.m_current);
    }
    m_WorldTarget.x = focus.x;
    m_WorldTarget.z = focus.z;
    m_WorldTarget.y = focus.y;
    // The orbit distance: the wall's limit, the pull back in to the default distance, the shortest distance.
    float distance;
    const uint32_t pullFlags = m_trackFlags;
    if ((pullFlags & 0x800u) != 0) {
        distance = m_distance;
    } else if ((m_Flags & 0x10000u) != 0 || (pullFlags & 0x40u) != 0 ||
               (camera->m_baTemporaryFlags & 0x4000000u) != 0 || !(m_framingScale >= 1.0f)) {
        distance = m_distance;
        m_pullInSpeed = 0.0f;
    } else {
        distance = m_distance;
        if (distance <= m_defaultDistance) {
            m_pullInSpeed = 0.0f;
        } else {
            float speed = ppc::fmadds(dt, m_pullInAccel, m_pullInSpeed);
            m_pullInSpeed = speed;
            if (speed > m_pullInMaxSpeed) {
                speed = m_pullInMaxSpeed;
                m_pullInSpeed = speed;
            }
            distance = distance - dt * speed;
            m_distance = distance;
        }
    }
    if ((m_Flags & 0x10000u) != 0 && m_wallDistance > 0.0f && distance > m_wallDistance) {
        distance = m_wallDistance;
        m_distance = distance;
    }
    if (!(distance >= m_minDistance) && !(direction.y <= 0.0f) && (m_Flags & 0x10000u) == 0) {
        // Too close and looking up: the direction tilted to the pitch limit 1.45 (cos 0.1205, sin 0.9927, folded), the
        // shortest distance.
        const float scale = IKCamera::AsFloat(0x3df6ca26u) / GameCosf(m_pitch.m_current);  // TOC -0x375c: cos 1.45
        direction.z = direction.z * scale;
        direction.x = direction.x * scale;
        direction.y = direction.y * scale;
        direction.y = IKCamera::AsFloat(0xbf7e2270u);  // TOC -0x3758: -sin 1.45
        const float length = Sqrtf(ppc::fmadds(direction.z, direction.z, ppc::fmadds(direction.x, direction.x, IKCamera::AsFloat(0x3f7c485bu))));
        if (length != 0.0f) {
            const float inverse = 1.0f / length;
            direction.z = direction.z * inverse;
            direction.x = direction.x * inverse;
            direction.y = direction.y * inverse;
        }
        m_distance = m_minDistance;
    }
    m_viewDir.x = direction.x;
    m_viewDir.y = direction.y;
    m_viewDir.z = direction.z;
    {
        const float back = -m_distance;
        position.z = ppc::fmadds(back, direction.z, m_WorldTarget.z);
        position.x = ppc::fmadds(back, direction.x, m_WorldTarget.x);
        position.y = ppc::fmadds(back, direction.y, m_WorldTarget.y);
    }
    if ((m_trackFlags & 0x2000u) == 0) ApplyStickYaw(dt, &position);
    const uint8_t framed = UpdateFramingAndPlaceCamera(dt, &position);
    m_trackFlags = (m_trackFlags & ~0x400u) | ((static_cast<uint32_t>(framed) & 0xffu) << 10);
    if (m_framingScaleTarget == 0.0f) m_framingScaleTarget = 1.0f;
    if (m_pConstraint != nullptr) {
        ConstrainFollowToVolume(dt, m_pConstraint, &position);
    } else {
        m_volumeYawSpeed = 0.0f;
        m_trackFlags &= ~0x80u;
        const uint32_t noZoneFlags = m_trackFlags;
        if (((noZoneFlags & 0x4u) != 0 || (noZoneFlags & 0x8u) != 0) && m_distance > 35.0f) {
            // Too far from the focus without a zone: the snap behind it.
            m_prevFocus.x = m_WorldTarget.x;
            m_prevFocus.y = m_WorldTarget.y;
            m_prevFocus.z = m_WorldTarget.z;
            SnapBehindTarget();
            return;
        }
    }
    if ((m_Flags & 0x1000u) != 0) {
        if ((m_trackFlags & 0x10u) != 0) {
            m_pitchMinB = -kFloatMax;
            m_pitchMaxB = kFloatMax;
        }
        if (m_pConstraint == nullptr || (ZoneFlags(m_pConstraint) & 0x40u) == 0) {
            CVector3 from = m_WorldPosition;
            ResolveWallMovement(&from, &position);
            if ((m_Flags & 0x2000u) != 0 && (m_trackFlags & 0x400u) == 0 &&
                (m_pConstraint == nullptr || (ZoneFlags(m_pConstraint) & 0x4u) != 0)) {
                CVector3 focusTarget;
                focusTarget.x = StackPosition(camera->m_aStack[0])[0];
                focusTarget.y = StackPosition(camera->m_aStack[0])[1];
                focusTarget.z = StackPosition(camera->m_aStack[0])[2];
                ResolveViewObstructions(dt, &focusTarget, &position);  // vt+0x74
            } else {
                PushOutOfConstraintPlane(dt, &position);
            }
            ResolveCameraCollision(&m_WorldTarget, &position);  // vt+0x78
        } else {
            m_pitchMinA = -kFloatMax;
            m_pitchMaxA = kFloatMax;
            m_trackFlags &= ~0xcu;
        }
    }
    m_WorldPosition.x = position.x;
    m_WorldPosition.z = position.z;
    m_WorldPosition.y = position.y;
}

// 0x00164448 CKCameraClassicTrack3_UpdateBlending_maybe: the blend from m_blendStart to m_blendEnd. The end pose is
// computed again every frame (ComputeDesiredPose at the current focus; with the stick off and no zone offset the focus
// follows the springs and drags the start along); the weights are the smoothstep of time / duration (a Hermite curve
// with the start slope m_blendSpeed when a blend was interrupted); the camera is placed at the blended orbit pose and
// collides (COLL) as in UpdateSteady. While the blend runs its duration is estimated again and only shortened; at the
// end the zone's spherical limits (flag 0x200) may move the target. A blend started at duration 0 also snaps the camera
// service's calculation pose.
void CKCameraClassicTrack3::UpdateBlending(float dt) {
    CKSrvCamera* const camera = SrvCamera();
    const uint32_t snapStart = m_blendDuration == 0.0f ? 1u : 0u;
    CVector3 position = m_WorldPosition;
    m_trackFlags = (m_trackFlags & ~0x10u) | (((camera->m_baTemporaryFlags >> 25) & 1u) << 4);
    CVector3 focus;
    ComputeFocusPoint(&focus);
    const uint32_t flags = m_trackFlags;
    if ((flags & 0x2000u) != 0 && (flags & 0x40000u) == 0) {
        CKCameraConstraint* zone = m_pConstraint;
        if (zone == nullptr || (ZoneSideOffset(zone) == 0.0f && ZoneUpOffset(zone) == 0.0f)) {
            UpdateFollowOffsets(dt, &focus);
            m_blendStart.m_focus.x = focus.x;
            m_blendStart.m_focus.y = focus.y;
            m_blendStart.m_focus.z = focus.z;
        }
    }
    m_blendEnd.m_focus.x = focus.x;
    m_blendEnd.m_focus.y = focus.y;
    m_blendEnd.m_focus.z = focus.z;
    const float time = dt + m_blendTime;
    m_blendTime = time;
    const float t = time / m_blendDuration;
    float weightEnd;
    float weightStart;
    if (t <= 1.0f) {
        const float slope = m_blendSpeed;
        const float t2 = t * t;
        if (slope != 0.0f) {
            const float cubic = t2 * (slope - 2.0f);
            const float square = t2 * ppc::fmadds(slope, -2.0f, 3.0f);
            weightEnd = ppc::fmadds(t, slope, ppc::fmadds(t, cubic, square));
        } else {
            weightEnd = ppc::fmadds(t, t2 * -2.0f, t2 * 3.0f);
        }
        weightStart = 1.0f - weightEnd;
    } else {
        weightEnd = 1.0f;
        m_blendSpeed = 0.0f;
        weightStart = 0.0f;
    }
    ComputeDesiredPose(&position, &m_blendEnd.m_focus, snapStart & 1u);
    // The blended target.
    {
        const float sx = m_blendStart.m_focus.x * weightStart;
        const float sy = m_blendStart.m_focus.y * weightStart;
        const float sz = m_blendStart.m_focus.z * weightStart;
        m_blendCurrent.m_focus.x = sx;
        m_blendCurrent.m_focus.y = sy;
        const float x = ppc::fmadds(weightEnd, m_blendEnd.m_focus.x, sx);
        const float y = ppc::fmadds(weightEnd, m_blendEnd.m_focus.y, sy);
        m_blendCurrent.m_focus.z = sz;
        const float z = ppc::fmadds(weightEnd, m_blendEnd.m_focus.z, sz);
        m_blendCurrent.m_focus.x = x;
        m_WorldTarget.x = x;
        m_blendCurrent.m_focus.y = y;
        m_WorldTarget.y = y;
        m_blendCurrent.m_focus.z = z;
        m_WorldTarget.z = z;
        m_viewDir.x = x - position.x;
        m_viewDir.y = y - position.y;
        m_viewDir.z = z - position.z;
        const float length = Sqrtf(ppc::fmadds(m_viewDir.z, m_viewDir.z, ppc::fmadds(m_viewDir.x, m_viewDir.x, m_viewDir.y * m_viewDir.y)));
        if (length != 0.0f) {
            const float inverse = 1.0f / length;
            m_viewDir.z = inverse * m_viewDir.z;
            m_viewDir.x = inverse * m_viewDir.x;
            m_viewDir.y = inverse * m_viewDir.y;
        }
    }
    // The blended orbit pose.
    float endPitch = m_blendEnd.m_pitch;
    m_blendCurrent.m_distance = ppc::fmadds(weightStart, m_blendStart.m_distance, weightEnd * m_blendEnd.m_distance);
    m_blendCurrent.m_pitch = ppc::fmadds(weightStart, m_blendStart.m_pitch, weightEnd * endPitch);
    m_blendCurrent.m_yaw = ppc::fmadds(weightEnd, WrapTurn(m_blendEnd.m_yaw - m_blendStart.m_yaw), m_blendStart.m_yaw);
    OrbitPosition(&m_WorldTarget, m_blendCurrent.m_yaw, m_blendCurrent.m_pitch, m_blendCurrent.m_distance, &position);
    // The collisions (as in UpdateSteady).
    if ((m_Flags & 0x1000u) != 0) {
        if ((m_trackFlags & 0x10u) != 0) {
            m_pitchMinB = -kFloatMax;
            m_pitchMaxB = kFloatMax;
        }
        CKCameraConstraint* zone = m_pConstraint;
        if (zone != nullptr && (ZoneFlags(zone) & 0x40u) != 0) {
            if ((ZoneFlags(zone) & 0x10000u) != 0) {
                CVector3 focusTarget;
                focusTarget.x = StackPosition(camera->m_aStack[0])[0];
                focusTarget.y = StackPosition(camera->m_aStack[0])[1];
                focusTarget.z = StackPosition(camera->m_aStack[0])[2];
                ResolveViewObstructions(dt, &focusTarget, &position);  // vt+0x74
            }
            m_pitchMinA = -kFloatMax;
            m_pitchMaxA = kFloatMax;
            m_trackFlags &= ~0xcu;
        } else {
            if ((snapStart & 0xffu) != 0) {
                m_trackFlags &= ~0xcu;
            } else {
                CVector3 from = m_WorldPosition;
                ResolveWallMovement(&from, &position);
                zone = m_pConstraint;
                if ((m_Flags & 0x2000u) != 0 &&
                    (zone == nullptr || (ZoneFlags(zone) & 0x4u) != 0 || (ZoneFlags(zone) & 0x10000u) != 0)) {
                    CVector3 focusTarget;
                    focusTarget.x = StackPosition(camera->m_aStack[0])[0];
                    focusTarget.y = StackPosition(camera->m_aStack[0])[1];
                    focusTarget.z = StackPosition(camera->m_aStack[0])[2];
                    ResolveViewObstructions(dt, &focusTarget, &position);  // vt+0x74
                } else {
                    PushOutOfConstraintPlane(dt, &position);
                    m_trackFlags &= ~0xcu;
                }
            }
            ResolveCameraCollision(&m_WorldTarget, &position);  // vt+0x78
        }
        endPitch = m_blendEnd.m_pitch;
    }
    float duration;
    if (weightEnd != 1.0f) {
        // The duration estimated again (as in CaptureBlendStart, from the previous focus): only ever shortened, the
        // elapsed time scaled with it.
        const float yawDifference = WrappedAngleMagnitude(m_blendEnd.m_yaw - m_blendStart.m_yaw);
        const float pitchDifference = WrappedAngleMagnitude(endPitch - m_blendStart.m_pitch);
        const float dx = m_prevFocus.x - m_blendStart.m_focus.x;
        const float dy = m_prevFocus.y - m_blendStart.m_focus.y;
        const float dz = m_prevFocus.z - m_blendStart.m_focus.z;
        const float distanceDifference = std::fabs(m_blendEnd.m_distance - m_blendStart.m_distance);
        const float focusDistance = Sqrtf(ppc::fmadds(dz, dz, ppc::fmadds(dx, dx, dy * dy)));
        float estimate = yawDifference / 1.5f;
        if (estimate < 0.0f) estimate = 0.0f;
        const float byPitch = pitchDifference / 0.75f;
        if (!(estimate > byPitch)) estimate = byPitch;
        const float byDistance = distanceDifference * 0.125f;
        if (!(estimate > byDistance)) estimate = byDistance;
        const float byFocus = focusDistance / 4.5f;
        if (!(estimate > byFocus)) estimate = byFocus;
        if (m_blendTimeScale != -1.0f) estimate = estimate * m_blendTimeScale;
        duration = m_blendDuration;
        if (!(estimate >= duration)) {
            const float ratio = estimate / duration;
            m_blendDuration = estimate;
            m_blendTime = m_blendTime * ratio;
            duration = estimate;
        }
    } else {
        // The blend is over.
        m_blendDuration = -1.0f;
        m_stickPitch = endPitch;
        m_prevFocus.x = m_WorldTarget.x;
        m_prevFocus.z = m_WorldTarget.z;
        m_prevFocus.y = m_WorldTarget.y;
        duration = m_blendDuration;
    }
    if (duration == -1.0f && m_pConstraint != nullptr && (ZoneFlags(m_pConstraint) & 0x200u) != 0) {
        // The zone's spherical limits at the final pose; the target moved onto the view line through the result.
        uint8_t constrained;
        const CVector3 limited = CameraVolume_ComputeConstrainedSphericalPosition(
            m_blendCurrent.m_yaw, m_blendCurrent.m_pitch, m_blendCurrent.m_distance, m_pConstraint, &m_WorldTarget,
            &constrained);
        position = limited;
        if (constrained != 0 && ZoneLookMode(m_pConstraint) != 2) {
            const float dot = ppc::fmadds(m_WorldTarget.z - limited.z, m_viewDir.z,
                                          ppc::fmadds(m_WorldTarget.x - limited.x, m_viewDir.x,
                                                      (m_WorldTarget.y - limited.y) * m_viewDir.y));
            m_WorldTarget.z = ppc::fmadds(dot, m_viewDir.z, limited.z);
            m_WorldTarget.x = ppc::fmadds(m_viewDir.x, dot, limited.x);
            m_WorldTarget.y = ppc::fmadds(dot, m_viewDir.y, limited.y);
        }
    }
    m_WorldPosition.y = position.y;
    m_WorldPosition.x = position.x;
    m_WorldPosition.z = position.z;
    {
        const float y = m_WorldTarget.y - position.y;
        const float x = m_WorldTarget.x - position.x;
        const float z = m_WorldTarget.z - position.z;
        m_viewDir.y = y;
        m_viewDir.x = x;
        m_viewDir.z = z;
        const float length = Sqrtf(ppc::fmadds(z, z, ppc::fmadds(x, x, y * y)));
        if (length != 0.0f) {
            const float inverse = 1.0f / length;
            m_viewDir.z = inverse * m_viewDir.z;
            m_viewDir.x = inverse * m_viewDir.x;
            m_viewDir.y = inverse * m_viewDir.y;
        }
    }
    if ((snapStart & 0xffu) != 0) {
        camera->SetCalculationPose(&m_WorldPosition, &m_WorldTarget);
        camera->CaptureHeroHeadingLock();
    }
}
