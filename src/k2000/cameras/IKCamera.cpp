// IKCamera.cpp - reconstructed original translation unit 0x144108-0x146de8 (GAME_TOC1, main_toc1), 21 functions, 20 live.
// Primary owner: IKCamera (not a registered class)
// Other owners: CKCamera (2), CameraTrack (2), CKCameraBase (2), CKCameraTrack (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x144108  IKCamera_LevelReset  (IKCamera::RecursiveRegistration)
//   [x] 0x1441e8  CKCamera_StartAttachedFx_maybe
//   [x] 0x144238  CKCamera_StopAttachedFx_maybe
//   [x] 0x144278  IKCamera_GetHalfExtentsAtDistance_maybe
//   [x] 0x144300  IKCamera_IsCurrentCameraPredicate_maybe  (IsCurrentCamera, IKCamera::GetInfo's accessor)
//   [x] 0x144330  IKCamera_GetEffectiveProfileIndex_maybe
//   [x] 0x144378  IKCamera_GetFreezeYSpringStiffnessAndFriction_maybe
//   [x] 0x144398  IKCamera_UpdateTrackBase_maybe
//   [ ] 0x144460  IKCamera_ConstructBase_2  [dead]
//   [x] 0x1444a8  IKCamera_ConstructBase
//   [x] 0x1444f0  IKCamera_GetInfo  (IKCamera::GetInfo)
//   [x] 0x144570  KStub_Return1_144570  (PostLoad: 1, IKSerializable's default)
//   [x] 0x144578  CKCameraTrack_ClearReferences_BaseNop_maybe  (empty)
//   [x] 0x144580  CKCameraBase_Load
//   [ ] 0x144ab0  CKCameraBase_Save
//   [x] 0x145088  IKCamera_FindAndRepairOcclusion_maybe
//   [x] 0x145ee0  CameraTrack_OrientMatrixToTarget_maybe  (IKCamera::OrientMatrixToTarget (static))
//   [x] 0x1461a0  IKCamera_FindGroundContact_maybe
//   [x] 0x146d78  IKCamera_DeletingDestructor  (~IKCamera (vtable stores only), delete)
//   [x] 0x146db8  IKCamera_Destructor  (~IKCamera (vtable stores only))
//   [x] 0x146dd0  IKCamera_BaseDestructor  (C++ destructor chain: vtable stores only)
//
//   [ ] 0x9a7178  IKCamera_vf68  [inline]
//   [ ] 0x9a7180  KStub_Nop_9a7180  [inline]
//   [ ] 0x9a7188  IKCamera_vf84  [inline]
//   [ ] 0x9a7190  IKCamera_vf88  [inline]
//   [ ] 0x9a7198  IKCamera_vf8C  [inline]
//   [ ] 0x9a71a0  IKCamera_vf90  [inline]
//   [ ] 0x9a71a8  KStub_Return0_9a71a8  [inline]
//   [ ] 0x9a71b0  IKCamera_vfA0  [inline]
//   [ ] 0x9a71c0  IKCamera_vfAC  [inline]
//   [ ] 0x9a71e0  KStub_Return1_9a71e0  [inline]
//   [ ] 0x9a71e8  IKCamera_vf70  [inline]
//   [ ] 0x9a72b8  IKCamera_vf98  [inline]
//   [ ] 0x9a72c8  IKCamera_vfA8  [inline]
//   [ ] 0x9a72d8  IKCamera_vfA4  [inline]
//   [ ] 0x9a72f8  IKCamera_vf9C  [inline]
//   [ ] 0x9a7310  IKCamera_vf80  [inline]
//   [ ] 0x9a7318  KStub_Return0_9a7318  [inline]
//   [ ] 0x9a78d0  IKCamera_GetClassGroup  [inline]
//   [ ] 0x9a78d8  IKCamera_GetClassId  [inline]
//   [ ] 0x9a78e0  IKCamera_IsKindOf  [inline]
#include "k2000/cameras/IKCamera.h"

#include <cmath>
#include <cstring>

#include "crt/ppc_ops.h"
#include "crt/xtanf.h"
#include "k2000/cameras/CKSrvCamera.h"
#include "k2000/cameras/CameraContext.h"
#include "k2000/core/Stub.h"
#include "k2000/graphical/CDOFData.h"
#include "k2000/logic/fx/CKDOFFxData.h"
#include "k2000/logic/CKSavingManager.h"
#include "k2000/misc/Engine.h"
#include "k2000/services/CKSrvFx.h"
#include "k2000/graphical/CDOFData.h"
#include "k2000/logic/fx/CKDOFFxData.h"
#include "k2000/services/CKSrvFx.h"
#include "k2000/hooks/GroundContact.h"
#include "k2000/hooks/CKCameraBeacon.h"
#include "k2000/io/IKFile.h"
#include "k2000/core/IKInfo.h"
#include "k2000/logic/CKSavingManager.h"
#include "k2000/logic/physics/CGround.h"
#include "k2000/managers/CKGraphic.h"
#include "k2000/misc/Engine.h"
#include "k2000/render/CRenderer.h"
#include "k2000/scenegraph/IKBoundingVolume.h"
#include "k2000/services/CKSrvCollision.h"
#include "k2000/services/CollisionDatas.h"
#include "k2000/services/ICollisionMesh.h"

// The collision / constraint helpers (COLL family).
namespace {

constexpr float kDegToRad = 0x1.1df468p-6f;   // TOC -0x3c48 0x3c8efa34
constexpr float kFarDistance = 20.0f;          // TOC -0x3c28 0x41a00000
constexpr float kMaxSpringValue = 10000.0f;    // TOC -0x3c24 0x461c4000
constexpr float kSettleDistance = 0x1.99999ap-3f;  // TOC -0x3c20 0x3e4ccccd (0.2)
constexpr float kSettleSquare = 0x1.47ae16p-5f;    // TOC -0x3c1c 0x3d23d70b (0.04, one ulp above 0.04f)
constexpr float kWallTopMargin = 0x1.47ae14p-6f;   // TOC -0x3c14 0x3ca3d70a (0.02)

// The shared y axis (0x00c50d40; filled by a static initialiser in the original).
const CVector3 kAxisY = {0.0f, 1.0f, 0.0f};

CKSrvCamera* SrvCamera() { return static_cast<CKSrvCamera*>(g_pEngine->m_srvCamera); }

CKSrvCollision* SrvCollision() { return static_cast<CKSrvCollision*>(g_pEngine->m_srvCollision); }

// 0x00010690 Math_Sqrtf (fsqrts).
inline float Sqrtf(float x) { return std::sqrt(x); }

// The sign bit cleared (rlwinm r0,r0,0,1,31 on the stored word).
inline float ClearSignBit(float x) {
    uint32_t bits;
    std::memcpy(&bits, &x, 4);
    bits &= 0x7fffffffu;
    std::memcpy(&x, &bits, 4);
    return x;
}

// The renderer's camera context's height / width (engine +0x04 -> +0x04 -> +0x28 -> +0x48).
float ScreenHeightOverWidth() { return g_pEngine->m_graphic->m_renderer->m_cameraContext->m_fHeightOverWidth; }

float Word(uint32_t word) { return IKCamera::AsFloat(word); }

uint32_t Word(float value) { return IKCamera::AsWord(value); }

constexpr float kFloatMax = 3.40282347e+38f;  // the word at 0x00c4acb8 + 0x28 (FLT_MAX), read through a TOC pointer

// The camera service's contact copies are the XXL2 types' twins (same layout): the contact helpers take the XXL2 ones.
const ::CGroundContactDatasInOut* AsContact(const CKSrvCamera::CGroundContactDatasInOut* contact) {
    return reinterpret_cast<const ::CGroundContactDatasInOut*>(contact);
}

// The ground's engine flags (ICollisionMesh +0x36): bit 1 (0x2) the floor height m_fPropertieValue applies, bit 3 (0x8)
// _maybe a ceiling (the camera is put under it).
uint32_t GroundFlags(const IKSerializable* ground) { return static_cast<const ICollisionMesh*>(ground)->m_ba16EngineFlags; }

float GroundProperty(const IKSerializable* ground) { return static_cast<const CGround*>(ground)->m_fPropertieValue; }

// The camera pushed out of a hit face along its normal by `radius` (inlined twice in 0x1461a0): the face is the hit's
// (the mesh's triangle m_i32FaceIndex), its normal (v1 - v0) x (v2 - v0) in the mesh's space, normalised unless 0.
void PushAlongHitFaceNormal(const CLineCollisionDatas& hit, float radius, CVector3* position) {
    const ICollisionMesh* mesh = hit.m_pCollisionMesh;
    const uint16_t* triangle = nullptr;
    if (hit.m_i32FaceIndex != -1 && mesh != nullptr &&
        static_cast<int32_t>(mesh->m_ui16NbTriangle) > hit.m_i32FaceIndex) {
        triangle = mesh->m_aTriangle[hit.m_i32FaceIndex].m_aui16Index;
    }
    if (triangle == nullptr) {
        // BUG(original): without a face (or a mesh) the original reads the vertex indices at address 0 (and the vertices
        // of a null mesh), a fault on the PS3. A hit always has both, so this is never reached.
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
        const float inverse = 1.0f / length;
        nz = nz * inverse;
        nx = nx * inverse;
        ny = ny * inverse;
    }
    position->x = ppc::fmadds(radius, nx, position->x);
    position->y = ppc::fmadds(radius, ny, position->y);
    position->z = ppc::fmadds(radius, nz, position->z);
}

// The ground's floor height (flag bit 1): the y is raised to radius + m_fPropertieValue (inlined three times in 0x1461a0).
void ClampAboveGroundProperty(const IKSerializable* ground, float radius, CVector3* position) {
    if (((GroundFlags(ground) >> 1) & 1u) == 0) return;
    const float floor = radius + GroundProperty(ground);
    float y = position->y;
    if (!(y > floor)) y = floor;
    position->y = y;
}

}  // namespace

// 0x00144278 IKCamera_GetHalfExtentsAtDistance_maybe: the half extents of the view at `distance` from the camera:
// tan(fov / 2) * distance (the fov m_unk18 in degrees) and that times the screen's height / width (r4 is not used: the
// float argument takes its slot).
void IKCamera::GetHalfExtentsAtDistance(float distance, float* halfWidth, float* halfHeight) const {
    const float halfFov = (m_unk18 * kDegToRad) * 0.5f;  // TOC -0x3c44 0.5
    const float width = crt::Tanf(halfFov) * distance;  // TocBridge_tanf
    *halfWidth = width;
    *halfHeight = width * ScreenHeightOverWidth();
}

// 0x00144108 IKCamera_LevelReset (IKCamera's RecursiveRegistration; the tracks' call it first): type 0 registers
// the camera; then the reference +0x38 (not tested for null: it is always set) and, when set, the attached fx +0x50.
void IKCamera::RecursiveRegistration(int32_t type) {
    if (type == 0) g_pEngine->m_pSavingManager->RegisterSerializableObject(this, nullptr);  // vt+0x24
    m_unk38->RecursiveRegistration(type);
    if (m_unk50 != nullptr) m_unk50->RecursiveRegistration(type);
}

// 0x00144300 IKCamera_IsCurrentCameraPredicate_maybe: 1 when the camera is the service's current one (+0x474):
// ((|this ^ current| - 1) >> 31).
static uint32_t IsCurrentCamera(IKSerializable* self, uint32_t /*arg*/) {
    return self == SrvCamera()->m_pCurrentCamera ? 1u : 0u;
}

// 0x001444f0 IKCamera_GetInfo: request 0 with the value id 0: the current-camera predicate (a byte).
int32_t IKCamera::GetInfo(IKInfo* info, int32_t request) {
    if (request != kGetInfoValueAccessor || info->m_ui32Id != 0) return 1;
    return AnswerInfo(info, IsCurrentCamera, 0);  // TriggerPropertyRequest_SetGetter_maybe 0x38cd8, descriptor TOC -0x3c3c
}

// 0x001444a8 IKCamera_ConstructBase
IKCamera::IKCamera() {
    m_unk04 = nullptr;
    m_unk4c = 0;
    m_unk44 = 0;
    m_unk48 = 0;
    // rlwinm/ori sequence on the word: bit 0 set, bit 1 set, bit 2 cleared (the other bits as allocated).
    uint32_t bits = m_unk0c;
    bits = (bits & ~1u) | 1u;
    bits = (bits & ~2u) | 2u;
    bits = bits & ~4u;
    m_unk0c = bits;
}

// 0x00144378 IKCamera_GetFreezeYSpringStiffnessAndFriction_maybe: the camera service's (engine +0x70 -> CKSrvCamera) +0x8dc / +0x8e0.
void IKCamera::GetFrameMargins(float* a, float* b) const {
    const CKSrvCamera* service = static_cast<const CKSrvCamera*>(g_pEngine->m_srvCamera);
    *a = AsFloat(service->m_unk8dc);
    *b = AsFloat(service->m_unk8e0);
}

// 0x001441e8 CKCamera_StartAttachedFx_maybe
void IKCamera::StartAttachedFx() {
    CKDOFFxData* fx = static_cast<CKDOFFxData*>(m_unk50);
    if (fx == nullptr) return;
    m_unk54 = static_cast<CDOFData*>(fx->m_pDOFData)->m_fFocusClamp;  // +0x08
    CKSrvFx::StartCameraFx(-1.0f, fx);  // 0x001afaf8, TOC -0x3c4c
}

// 0x00144238 CKCamera_StopAttachedFx_maybe
void IKCamera::StopAttachedFx() {
    if (m_unk50 != nullptr) CKSrvFx::StopCameraFx(-1.0f, static_cast<IKFxData*>(m_unk50));  // 0x001affd8
}

// 0x00144398 IKCamera_UpdateTrackBase_maybe: the tracks' Updates call it first. Only with an attached fx (+0x50, a
// depth-of-field effect): the position-target distance (fsubs, fmuls / fmadds / fmadds, Math_Sqrtf) goes to the fx
// data's CDOFData +0x04 and, clamped to +0x54 (`bge`: a NaN distance takes +0x54), +0x08; then
// CKSrvFx_StartCameraFx_maybe 0x1afaf8 (time -1.0).
void IKCamera::UpdateTrackBase() {
    if (m_unk50 == nullptr) return;
    const float dx = m_WorldTarget.x - m_WorldPosition.x;
    const float dy = m_WorldTarget.y - m_WorldPosition.y;
    const float dz = m_WorldTarget.z - m_WorldPosition.z;
    const float distance = std::sqrt(ppc::fmadds(dz, dz, ppc::fmadds(dx, dx, dy * dy)));  // 0x00010690 Math_Sqrtf
    CKDOFFxData* fx = static_cast<CKDOFFxData*>(m_unk50);
    CDOFData* dof = static_cast<CDOFData*>(fx->m_pDOFData);
    dof->m_fFocusDistance = distance;
    dof->m_fFocusClamp = !(distance < m_unk54) ? m_unk54 : distance;
    CKSrvFx::StartCameraFx(-1.0f, fx);
}

// 0x00144580 CKCameraBase_Load
int32_t IKCamera::BaseLoad(IKFile* file, int32_t type) {
    if (type == K_LEVEL_PLATEFORMS) {
        ReadU32LE(file, &m_Flags);
        ReadU8(file, &m_CameraSmoothMode);
        ReadU8(file, &m_TargetSmoothMode);
        ReadU8(file, &m_TargetSafeMode);
        ReadF32LE(file, &m_fFar);
        ReadF32LE(file, &m_fFov);
        ReadU32LEWords(file, reinterpret_cast<uint32_t*>(&m_WorldPosition), 3);  // one 0xc read, swapped
        ReadU32LEWords(file, reinterpret_cast<uint32_t*>(&m_WorldTarget), 3);
        IKFile_ReadRef(file, &m_unk04);
        ReadU8(file, &m_ui8CameraAvoidingSystemIndex);
        IKFile_ReadRef(file, &m_unk38);
        ReadU8(file, &m_unk3e);
        ReadU32LE(file, &m_unk40);
        ReadU32LE(file, &m_unk44);
        ReadU32LE(file, &m_unk48);
        ReadU32LE(file, &m_unk4c);
        ReadU8(file, &m_unk3d);
        IKFile_ReadRef(file, &m_unk50);
    }
    m_unk18 = m_fFov;
    return 1;
}

// 0x00145088 IKCamera_FindAndRepairOcclusion_maybe (vt+0x74): the cameras' own obstruction handling (CKCameraClassicTrack3 overrides it), run
// with m_Flags 0x2000 (otherwise the service's flags 0x200 / 0x400 and probe bits 0..2 are cleared). The camera
// service's probe state (m_ui8ProbeFlags, +0x88c..+0x8a8):
// - a pending ground contact (m_baTemporaryFlags 0x1000, contact status 2) puts the camera back at the last frame's
//   position (m_v3SavedPos), probe bit 0 (the view crossed a ground) keeps its height;
// - the push sphere's contact (m_baTemporaryFlags 0x200) removes the move against the push and pushes it out;
// - probe bit 1 (a wall pushed the camera): the x / z position follows a critically damped spring of stiffness
//   avoiding datas [0] along the line from +0x894 (the current point) to +0x88c (the wall-free point); the distance
//   left is +0x8a0 (target) / +0x8a4 (value) / +0x8a8 (speed);
// - near the focus (20 units), a moving camera slides along the walls from the last position (probe bit 2);
// - without m_Flags 0x10000, a ground between the focus and the camera (two RaycastWalls, lifted by the screen's
//   tan(fov / 2) * height / width) lifts the camera over it or brings it in front (probe bit 0 when it could not);
// - the cylinder from the focus to the camera is slid along the walls; a wall sets probe bit 1 and the spring's
//   wall-free point +0x88c (the camera at +0x89c from the focus, slid once more).
void IKCamera::ResolveViewObstructions(float dt, const CVector3* focus, CVector3* position) {
    CKSrvCamera* camera = SrvCamera();
    if ((m_Flags & 0x2000u) == 0) {
        camera->m_baTemporaryFlags &= ~0x200u;
        camera->m_ui8ProbeFlags = static_cast<uint8_t>(camera->m_ui8ProbeFlags & 0xf8u);
        camera->m_baTemporaryFlags &= ~0x400u;
        return;
    }
    const float focusX = focus->x;
    const float savedZ = camera->m_v3SavedPos.z;
    const float savedX = camera->m_v3SavedPos.x;
    const float savedY = camera->m_v3SavedPos.y;
    const CKSrvCamera::SCameraAvoidingDatas& avoid = camera->m_asAvoidingDatas[m_ui8CameraAvoidingSystemIndex];
    CMasksOfGrdTypeForTests moveMasks;    // the slide from the last position (stack +0x74)
    moveMasks.m_ui32GrdToTest = 1;
    moveMasks.m_ui32GrdToAvoid = 0x80;
    CMasksOfGrdTypeForTests groundMasks;  // the grounds between the focus and the camera (+0x7c)
    groundMasks.m_ui32GrdToTest = 8;
    groundMasks.m_ui32GrdToAvoid = 0x80;
    CMasksOfGrdTypeForTests wallMasks;    // the slide from the focus (+0x84)
    wallMasks.m_ui32GrdToTest = 1;
    wallMasks.m_ui32GrdToAvoid = 0x188;
    const float startY = focus->y + avoid.m_afValues[2];
    const float focusZ = focus->z;
    if ((camera->m_ui32NbStacked & 0xffu) > 1) wallMasks.m_ui32GrdToAvoid = 0x288;

    if ((camera->m_baTemporaryFlags & 0x1000u) != 0 && camera->m_GContactInOut.m_eContactStatus == 2) {
        position->x = savedX;
        position->y = savedY;
        position->z = savedZ;
    }
    if ((camera->m_ui8ProbeFlags & 1u) != 0) position->y = savedY;
    if ((camera->m_baTemporaryFlags & 0x200u) != 0) {
        // The push sphere touches something: the move from the last position loses its part against the push (the
        // service's +0x770, its length the depth), then the camera is pushed out by the depth less half the radius.
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
            const float inverse = 1.0f / depth;
            pushZ = pushZ * inverse;
            pushX = pushX * inverse;
            pushY = pushY * inverse;
        }
        const float along = ppc::fmadds(pushZ, moveZ, ppc::fmadds(pushX, moveX, pushY * moveY));
        if (along < 0.0f) {
            const float back = -along;
            moveZ = ppc::fmadds(pushZ, back, moveZ);
            moveX = ppc::fmadds(pushX, back, moveX);
            moveY = ppc::fmadds(pushY, back, moveY);
        }
        const float x = savedX + moveX;
        const float y = savedY + moveY;
        const float z = savedZ + moveZ;
        position->x = x;
        position->y = y;
        position->z = z;
        const IKBoundingVolume* pushSphere = static_cast<const IKBoundingVolume*>(camera->m_pDodgeBSPushCam);
        const float out = ppc::fmadds(pushSphere->m_fRadius, -0.5f, depth);
        if (out > 0.0f) {
            position->x = ppc::fmadds(pushX, out, x);
            position->z = ppc::fmadds(pushZ, out, z);
            position->y = ppc::fmadds(pushY, out, y);
        }
    }
    // Far from the focus: the camera's own position more than 20 from it in x / z.
    bool far;
    {
        const float x = m_WorldPosition.x - focusX;
        const float z = m_WorldPosition.z - focusZ;
        far = Sqrtf(ppc::fmadds(x, x, z * z)) > kFarDistance;
    }

    bool moving = true;  // the spring has not settled (or did not run)
    if ((camera->m_ui8ProbeFlags & 2u) != 0 &&
        !((m_Flags & 0x10000u) != 0 && !far && !(m_WorldPosition.y - startY > kFarDistance))) {
        // The spring towards the wall-free point (+0x88c) from the current point (+0x894), in x / z.
        const float targetX = Word(camera->m_unk88c[0]);
        const float targetZ = Word(camera->m_unk88c[1]);
        float directionZ = targetZ - Word(camera->m_unk88c[3]);
        float directionX = targetX - Word(camera->m_unk88c[2]);
        float length = Sqrtf(ppc::fmadds(directionX, directionX, directionZ * directionZ));
        if (length == 0.0f) {
            length = 0.0f;
        } else {
            const float inverse = 1.0f / length;
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
            const float speed = ppc::fmadds(accel, dt, camera->m_unk8a0[2]);
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
        const float currentX = ppc::fmadds(directionX, step, Word(camera->m_unk88c[2]));
        const float currentZ = ppc::fmadds(directionZ, step, Word(camera->m_unk88c[3]));
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
        position->x = Word(camera->m_unk88c[2]);
        position->z = Word(camera->m_unk88c[3]);
    }

    const float tanHalfFov = crt::Tanf(m_unk18 * kDegToRad * 0.5f);
    const float heightOverWidth = ScreenHeightOverWidth();
    // (The original also takes the focus-camera distance in x / z and in 3D here, with Math_Sqrtf, and never uses them.)
    CKSrvCollision* collision = SrvCollision();
    const float radius = avoid.m_afValues[1];
    const float height = avoid.m_afValues[3];

    if (moving && !far) {
        // Near the focus: the camera slides along the walls from the last position.
        CLine line;
        line.m_start.x = savedX;
        line.m_start.y = savedY;
        line.m_start.z = savedZ;
        line.m_VectDir.x = position->x - savedX;
        line.m_VectDir.y = position->y - savedY;
        line.m_VectDir.z = position->z - savedZ;
        CSlideGroundEdgeDatasOut out;  // the callee fills it when it answers 2 / 3
        const uint8_t result = collision->ResolveSweptCylinderWalls(&line, radius, height, &out, nullptr, &moveMasks, 1);
        if (result == 1) {
            position->x = savedX;
            position->z = savedZ;
            camera->m_ui8ProbeFlags = static_cast<uint8_t>(camera->m_ui8ProbeFlags | 4u);
        } else if (result == 0) {
            camera->m_ui8ProbeFlags = static_cast<uint8_t>(camera->m_ui8ProbeFlags & ~4u);
        } else if (result == 2 || result == 3) {
            position->x = position->x + out.m_v3BouncingVector.x;
            position->y = position->y + out.m_v3BouncingVector.y;
            position->z = position->z + out.m_v3BouncingVector.z;
            camera->m_ui8ProbeFlags = static_cast<uint8_t>(camera->m_ui8ProbeFlags | 4u);
        }
    }

    camera->m_ui8ProbeFlags = static_cast<uint8_t>(camera->m_ui8ProbeFlags & ~1u);
    if ((m_Flags & 0x10000u) == 0) {
        // A ground between the focus and the camera: the lines are lifted by the view's half height at distance 1.
        const float lift = tanHalfFov * heightOverWidth;
        const float liftX = kAxisY.x * lift;
        const float liftY = kAxisY.y * lift;
        const float liftZ = kAxisY.z * lift;
        CLine down;  // focus (lifted) -> camera
        down.m_VectDir.x = position->x - focusX;
        down.m_VectDir.y = position->y - startY;
        down.m_VectDir.z = position->z - focusZ;
        down.m_start.x = focusX + liftX;
        down.m_start.y = startY + liftY;
        down.m_start.z = focusZ + liftZ;
        CGroundEdgeDatasOut downHit;
        if (collision->RaycastWalls(&down, 0.0f, &downHit, 0, &groundMasks, 1) != 0) {
            const float t = downHit.m_ftLine;
            const float hitY = ppc::fmadds(t, down.m_VectDir.y, down.m_start.y);
            const float under = downHit.m_fHeightUnder - kWallTopMargin;
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
                const float inverse = 1.0f / length;
                directionZ = directionZ * inverse;
                directionX = directionX * inverse;
                directionY = directionY * inverse;
                squareZ = directionZ * directionZ;
                squareX = directionX * directionX;
            }
            const float toFocusZ = focusZ - cameraZ;
            const float toFocusX = focusX - cameraX;
            const float horizontal = squareZ + squareX;
            const float distanceSquare = ppc::fmadds(toFocusX, toFocusX, toFocusZ * toFocusZ);
            // The point over the top at the camera's x / z distance (+0x1a0 / +0x1a4 on the stack).
            float overX;
            float overZ;
            if (horizontal != 0.0f) {
                overY = overY - lift;
                const float scale = Sqrtf(distanceSquare / horizontal);
                const float y = ppc::fmadds(directionY, scale, startY);
                if (!(y < overY)) overY = y;
                overZ = ppc::fmadds(directionZ, scale, focusZ);
                overX = ppc::fmadds(directionX, scale, focusX);
            } else {
                overY = overY - lift;
                overZ = cameraZ;
                overX = cameraX;
            }
            const float currentY = position->y;
            if (!(currentY > overY)) overY = currentY;
            if ((downHit.m_ba8Infos & 1u) != 0 && !(focus->y < overY)) {
                overY = currentY;
                overX = position->x;
                overZ = position->z;
            } else {
                camera->m_ui8ProbeFlags = static_cast<uint8_t>(camera->m_ui8ProbeFlags | 1u);
            }
            // camera (lifted) -> focus
            CLine up;
            up.m_start.x = position->x + liftX;
            up.m_start.y = position->y + liftY;
            up.m_start.z = position->z + liftZ;
            up.m_VectDir.x = focusX - position->x;
            up.m_VectDir.y = startY - position->y;
            up.m_VectDir.z = focusZ - position->z;
            CGroundEdgeDatasOut upHit;
            float frontX = cameraX;
            float frontY = cameraY;
            float frontZ = cameraZ;
            if (collision->RaycastWalls(&up, 0.0f, &upHit, 0, &groundMasks, 1) != 0) {
                const float u = upHit.m_ftLine;
                const float endX = up.m_start.x + up.m_VectDir.x;
                const float upHitX = ppc::fmadds(u, up.m_VectDir.x, up.m_start.x);
                const float upHitY = ppc::fmadds(u, up.m_VectDir.y, up.m_start.y);
                const float upUnder = upHit.m_fHeightUnder - kWallTopMargin;
                const float endY = up.m_start.y + up.m_VectDir.y;
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
                    const float inverse = 1.0f / upLength;
                    upDirectionZ = upDirectionZ * inverse;
                    upDirectionX = upDirectionX * inverse;
                    upDirectionY = upDirectionY * inverse;
                    upSquareZ = upDirectionZ * upDirectionZ;
                    upSquareX = upDirectionX * upDirectionX;
                }
                const float upHorizontal = upSquareX + upSquareZ;
                if (upHorizontal != 0.0f) {
                    frontY = upTop - lift;
                    const float scale = Sqrtf(distanceSquare / upHorizontal);
                    const float y = ppc::fmadds(upDirectionY, scale, startY);
                    if (!(y < frontY)) frontY = y;
                    frontZ = ppc::fmadds(upDirectionZ, scale, focusZ);
                    frontX = ppc::fmadds(upDirectionX, scale, focusX);
                } else {
                    frontY = upTop - lift;
                    frontZ = cameraZ;
                    frontX = cameraX;
                }
                const float upCurrentY = position->y;
                if (!(upCurrentY > frontY)) frontY = upCurrentY;
                if ((upHit.m_ba8Infos & 1u) != 0 && !(focus->y < frontY)) {
                    frontY = upCurrentY;
                    frontX = position->x;
                    frontZ = position->z;
                } else {
                    camera->m_ui8ProbeFlags = static_cast<uint8_t>(camera->m_ui8ProbeFlags | 1u);
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

    // The cylinder from the focus to the camera along the walls.
    CLine line;
    line.m_start.x = focusX;
    line.m_start.y = startY;
    line.m_start.z = focusZ;
    line.m_VectDir.z = position->z - focusZ;
    line.m_VectDir.x = position->x - focusX;
    line.m_VectDir.y = position->y - startY;
    CSlideGroundEdgeDatasOut out;
    // BUG(original): `prev` is an uninitialised stack record; the second slide below reads its bouncing vector after a
    // result 2, which the callee does not copy there (only 3 does). Zeroed here.
    CSlideGroundEdgeDatasOut prev = {};
    const uint8_t result = collision->ResolveSweptCylinderWalls(&line, radius, height, &out, &prev, &wallMasks, 1);
    if (result <= 1) {
        camera->m_ui8ProbeFlags = static_cast<uint8_t>(camera->m_ui8ProbeFlags & ~2u);
        return;
    }
    if (result > 3) return;
    if (!far && !((camera->m_ui8ProbeFlags & 2u) != 0 && (m_Flags & 0x10000u) == 0)) {
        // A new wall contact: the spring starts at the camera, the wall-free point at the camera's own distance.
        camera->m_unk88c[2] = Word(position->x);
        camera->m_unk88c[3] = Word(position->z);
        const float z = m_WorldPosition.z - m_WorldTarget.z;
        const float x = m_WorldPosition.x - m_WorldTarget.x;
        camera->m_fUnk89c = Sqrtf(ppc::fmadds(x, x, z * z));
        camera->m_unk8a0[1] = 0.0f;
        camera->m_unk8a0[2] = 0.0f;
    }
    // The wall-free point: the slid camera at +0x89c from the focus in x / z, slid once more.
    const float slidX = position->x + out.m_v3BouncingVector.x;
    const float slidZ = position->z + out.m_v3BouncingVector.z;
    float directionX = slidX - focusX;
    float directionZ = slidZ - focusZ;
    camera->m_unk88c[0] = Word(slidX);
    camera->m_unk88c[1] = Word(slidZ);
    const float keep = camera->m_fUnk89c;
    const float length = Sqrtf(ppc::fmadds(directionZ, directionZ, ppc::fmadds(directionX, directionX, 0.0f)));
    if (length != 0.0f) {
        const float scale = keep / length;
        directionZ = directionZ * scale;
        directionX = directionX * scale;
    }
    const float pointX = focusX + directionX;
    const float pointZ = focusZ + directionZ;
    CLine toPoint;
    toPoint.m_start.x = focusX;
    toPoint.m_start.y = startY;
    toPoint.m_start.z = focusZ;
    toPoint.m_VectDir.y = position->y - startY;
    toPoint.m_VectDir.x = pointX - focusX;
    toPoint.m_VectDir.z = pointZ - focusZ;
    const uint8_t slid = collision->ResolveSweptCylinderWalls(&toPoint, radius, height, &out, &prev, &wallMasks, 1);
    if (slid == 0) {
        camera->m_unk88c[1] = Word(pointZ);
        camera->m_unk88c[0] = Word(pointX);
    } else if (slid == 2 || slid == 3) {
        camera->m_unk88c[0] = Word(pointX + prev.m_v3BouncingVector.x);
        camera->m_unk88c[1] = Word(pointZ + prev.m_v3BouncingVector.z);
    }
    camera->m_ui8ProbeFlags = static_cast<uint8_t>(camera->m_ui8ProbeFlags | 2u);
}

// 0x001461a0 IKCamera_FindGroundContact_maybe (vt+0x78): with m_Flags bit 12 (0x1000) the camera position is kept
// out of the grounds. The camera service's ground probe (+0x6c8 / +0x6d8) looks for the ground under the camera within
// the view's half height at distance 1 (h = tan(fov / 2) * height / width); the camera's radius is Vf80 (at least 0.01).
// - No ground: the line from the focus (+0x484, 0.1 higher) to the camera, else the wall edges and then the grounds on
//   the line from the camera's last position (m_WorldPosition): the camera goes to the first hit, pushed out by the
//   radius along the face normal (0.1 along the wall's normal).
// - A ground with flag 8 (_maybe a ceiling): status 0 only when its distance m_fdH is below |position.y - target.y|,
//   other statuses always: the camera goes h + 0.01 under it.
// - Status 0 / 1 (on / just above the ground): the camera is kept the radius above it (and its floor height, flag 2).
// - Status 2 (within the object height): the radius above it unless the target is under the ground or the service's
//   bit 0 is set; then a second probe under that ground: a ceiling there the target sees (no mesh between) holds the
//   camera h + 0.01 under it and becomes the service's contact.
// The service's m_baTemporaryFlags bits 11 (0x800) / 12 (0x1000) tell what was done (_maybe: 0x800 pushed by a ground,
// 0x1000 kept above a ground); SetPlayerCanMoveCamera follows the camera's m_Flags bit 13 (0x2000) after a line hit.
void IKCamera::ResolveCameraCollision(const CVector3* target, CVector3* position) {
    if ((m_Flags & 0x1000u) == 0) return;
    const float halfFov = (m_unk18 * kDegToRad) * 0.5f;
    CKSrvCamera* camera = SrvCamera();
    CKSrvCollision* collision = static_cast<CKSrvCollision*>(g_pEngine->m_srvCollision);
    CKSrvCamera::CGroundContactDatasIn* in = &camera->m_GContactIn;
    CKSrvCamera::CGroundContactDatasInOut* contact = &camera->m_GContactInOut;
    const float tangent = crt::Tanf(halfFov);  // TocBridge_tanf
    CVector3 probe;
    probe.x = position->x;
    probe.y = position->y;
    probe.z = position->z;
    const float halfHeight = tangent * ScreenHeightOverWidth();  // f31
    float radius = Vf80();                                       // vt+0x80
    const float kMargin = 0.01f;                                 // TOC -0x3c0c 0x3c23d70a
    if (radius < kMargin) radius = kMargin;
    const float dy = probe.y - m_WorldPosition.y;
    if (dy < -0.01f) {  // TOC -0x3c08 0xbc23d70a
        // The camera is below its last position: the probe from where it is, the object height to above the last one.
        float above = halfHeight + dy;
        in->m_fObjectHeight = halfHeight - dy;
        if (above < 0.0f) above = 0.0f;
        in->m_fDeltaMax = above;
    } else {
        probe.y = m_WorldPosition.y;
        in->m_fDeltaMax = 0.0f;  // stw 0
        in->m_fObjectHeight = halfHeight + dy;
    }
    collision->GroundProbePoints(in, contact, &probe.x, 1);  // 0x00196540
    const uint32_t status = contact->m_eContactStatus;
    if (status == 3) {
        // No ground under the camera: the lines to the camera.
        const float kLift = 0.1f;  // TOC -0x3c04 0x3dcccccd
        CLineCollisionDatas hit;
        hit.m_i32FaceIndex = -1;
        hit.m_ui8SectorNumber = 0;
        hit.m_ftOnLine = kFloatMax;
        hit.m_pCollisionMesh = nullptr;
        CMasksOfGrdTypeForTests masks;
        masks.m_ui32GrdToTest = 1;
        masks.m_ui32GrdToAvoid = 0x80;
        CLine fromLast;  // sp+0xbc: from the last position to the camera
        fromLast.m_start.x = m_WorldPosition.x;
        fromLast.m_start.y = m_WorldPosition.y;
        fromLast.m_start.z = m_WorldPosition.z;
        fromLast.m_VectDir.x = position->x - m_WorldPosition.x;
        fromLast.m_VectDir.y = position->y - m_WorldPosition.y;
        fromLast.m_VectDir.z = position->z - m_WorldPosition.z;
        CLine fromFocus;  // sp+0xa4: from the focus (the service's +0x484), 0.1 higher
        const CVector3& focus = SrvCamera()->m_v3FocusPos;
        fromFocus.m_start.x = focus.x;
        fromFocus.m_start.y = focus.y + kLift;
        fromFocus.m_start.z = focus.z;
        fromFocus.m_VectDir.x = position->x - focus.x;
        fromFocus.m_VectDir.z = position->z - focus.z;
        fromFocus.m_VectDir.y = position->y - fromFocus.m_start.y;
        if (collision->RaycastMeshes(&fromFocus, &hit, 1, 1, &masks)) {  // 0x00197af8
            const float t = hit.m_ftOnLine;
            position->x = ppc::fmadds(t, fromFocus.m_VectDir.x, fromFocus.m_start.x);
            position->z = ppc::fmadds(t, fromFocus.m_VectDir.z, fromFocus.m_start.z);
            position->y = ppc::fmadds(t, fromFocus.m_VectDir.y, fromFocus.m_start.y);
            PushAlongHitFaceNormal(hit, radius, position);
        } else {
            CGroundEdgeDatasOut edge;  // sp+0xd4
            if (collision->RaycastWalls(&fromLast, 0.0f, &edge, 1, &masks, 1)) {  // 0x00198438
                const float t = edge.m_ftLine;
                const float x = ppc::fmadds(t, fromLast.m_VectDir.x, fromLast.m_start.x);
                const float z = ppc::fmadds(t, fromLast.m_VectDir.z, fromLast.m_start.z);
                const float y = ppc::fmadds(t, fromLast.m_VectDir.y, fromLast.m_start.y);
                position->x = ppc::fmadds(edge.m_EdgeNormal.x, kLift, x);
                position->z = ppc::fmadds(edge.m_EdgeNormal.z, kLift, z);
                position->y = ppc::fmadds(edge.m_EdgeNormal.y, kLift, y);
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
            camera->SetPlayerCanMoveCamera(false);
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
        CVector3 world;
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
        if (!dynamic) {
            position->y = radius + world.y;
        } else {
            const CMatrix34* matrix = static_cast<ICollisionMesh*>(ground)->GetWorldMatrix();  // vt+0x50
            position->x = ppc::fmadds(radius, matrix->m_up.x, world.x);
            position->y = ppc::fmadds(radius, matrix->m_up.y, world.y);
            position->z = ppc::fmadds(radius, matrix->m_up.z, world.z);
        }
        ClampAboveGroundProperty(ground, radius, position);
        camera->m_baTemporaryFlags = (camera->m_baTemporaryFlags & ~0x800u) | 0x800u;
        camera->m_baTemporaryFlags = (camera->m_baTemporaryFlags & ~0x1000u) | 0x1000u;
        return;
    }
    // The target is under the ground (or the service's bit 0): a second probe h + 0.01 under the ground's point.
    CKSrvCamera::CGroundContactDatasInOut below;  // sp+0xd4 (only these four members are set)
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
    in->m_fDeltaMax = halfHeight * 0.1f;  // TOC -0x3c04 0.1
    collision->GroundProbePoints(in, &below, &probe.x, 1);
    if (below.m_eContactStatus != 3 && (GroundFlags(below.m_pGround) & 0x8u) != 0) {
        CVector3 ceiling;  // sp+0x7c
        GroundContact_GetWorldPoint(AsContact(&below), &ceiling);
        ceiling.y = ceiling.y - (halfHeight + kMargin);
        const float targetY = target->y;
        if (below.m_eContactStatus != 0 || !(targetY > ceiling.y)) {
            // The target must see the point under the ceiling.
            CLineCollisionDatas hit;  // sp+0xbc
            hit.m_i32FaceIndex = -1;
            hit.m_ftOnLine = kFloatMax;
            hit.m_ui8SectorNumber = 0;
            hit.m_pCollisionMesh = nullptr;
            CMasksOfGrdTypeForTests masks;  // sp+0x74
            masks.m_ui32GrdToTest = 1;
            masks.m_ui32GrdToAvoid = 0x80;
            CLine line;  // sp+0xa4
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
    if (!dynamic) {
        position->y = radius + world.y;
    } else {
        const CMatrix34* matrix = static_cast<ICollisionMesh*>(ground)->GetWorldMatrix();  // vt+0x50
        position->x = ppc::fmadds(radius, matrix->m_up.x, world.x);
        position->y = ppc::fmadds(radius, matrix->m_up.y, world.y);
        position->z = ppc::fmadds(radius, matrix->m_up.z, world.z);
    }
    ClampAboveGroundProperty(ground, radius, position);
    camera->m_baTemporaryFlags = (camera->m_baTemporaryFlags & ~0x1000u) | 0x1000u;
    camera->m_baTemporaryFlags = (camera->m_baTemporaryFlags & ~0x800u) | 0x800u;
}

// 0x00144330 IKCamera_GetEffectiveProfileIndex_maybe. The original returns the byte sign-extended (extsw); the callers
// take its low byte.
uint8_t IKCamera::GetEffectiveProfileIndex() const {
    const CKSrvCamera* service = static_cast<const CKSrvCamera*>(g_pEngine->m_srvCamera);
    if (service->m_bUnk915 != 0 && service->m_pUnk920 != nullptr) {
        return static_cast<const CKCameraBeacon*>(service->m_pUnk920)->m_unk23;
    }
    return m_TargetSafeMode;
}

// 0x00145ee0 CameraTrack_OrientMatrixToTarget_maybe (r3 is not read). TOC -0x3c68 (0), -0x3c30 (1), -0x3c10 (cos 1 deg
// 0x3f7ff605). Only `up`'s y is read: the up candidate is (0, up.y, 0) normalised.
void IKCamera::OrientMatrixToTarget(const CVector3* target, const CVector3* up, CMatrix34* m) {
    const float dy = target->y - m->m_pos.y;
    const float dx = target->x - m->m_pos.x;
    const float dz = target->z - m->m_pos.z;
    const float length = std::sqrt(ppc::fmadds(dz, dz, ppc::fmadds(dx, dx, dy * dy)));  // Math_Sqrtf 0x10690
    if (length == 0.0f) return;
    const float inverse = 1.0f / length;
    m->m_ui32Flags &= 0xfffdfffcu;
    const float ay = dy * inverse;
    const float az = dz * inverse;
    const float ax = dx * inverse;
    m->m_at.y = ay;
    const float upY = up->y;
    float upLength = ppc::fmadds(upY, upY, 0.0f);
    m->m_at.x = ax;
    m->m_at.z = az;
    upLength = std::sqrt(upLength + 0.0f);
    if (!(upLength == 0.0f)) {
        const float upInverse = 1.0f / upLength;
        const float n0 = upInverse * 0.0f;  // the x and z of the normalised (0, up.y, 0)
        const float n1 = upY * upInverse;
        const float n0ax = n0 * ax;
        const float n0az = n0 * az;
        const float dot = ppc::fmadds(n1, ay, n0ax) + n0az;
        if (std::fabs(dot) < 0.9998477101325989f) {
            // The right axis n x at, the up axis at x right.
            const float n0ay = n0 * ay;
            float ry = n0ax - n0az;
            const float n1ax = n1 * ax;
            float rx = ppc::fmsubs(n1, az, n0ay);
            float rz = n0ay - n1ax;
            const float rightLength = std::sqrt(ppc::fmadds(rz, rz, ppc::fmadds(rx, rx, ry * ry)));
            if (!(rightLength == 0.0f)) {
                const float rightInverse = 1.0f / rightLength;
                rz = rz * rightInverse;
                rx = rx * rightInverse;
                ry = ry * rightInverse;
            }
            const float rxay = rx * ay;
            const float rzax = rz * ax;
            const float ryaz = ry * az;
            m->m_right.x = rx;
            m->m_right.y = ry;
            m->m_right.z = rz;
            m->m_ui32Flags &= 0xfffdfffcu;
            m->m_up.z = ppc::fmsubs(ry, ax, rxay);
            m->m_up.y = ppc::fmsubs(rx, az, rzax);
            m->m_up.x = ppc::fmsubs(rz, ay, ryaz);
            return;
        }
    }
    // Near the up axis (or no up): the up axis at x the matrix's current right, the right axis up x at.
    const float rz = m->m_right.z;
    const float rzax = rz * ax;
    const float ry = m->m_right.y;
    const float rx = m->m_right.x;
    const float ryaz = ry * az;
    const float rxay = rx * ay;
    float uy = ppc::fmsubs(rx, az, rzax);
    float ux = ppc::fmsubs(rz, ay, ryaz);
    float uz = ppc::fmsubs(ry, ax, rxay);
    const float upNewLength = std::sqrt(ppc::fmadds(uz, uz, ppc::fmadds(ux, ux, uy * uy)));
    if (!(upNewLength == 0.0f)) {
        const float upInverse = 1.0f / upNewLength;
        uz = uz * upInverse;
        ux = ux * upInverse;
        uy = uy * upInverse;
    }
    const float uyax = uy * ax;
    const float uxaz = ux * az;
    const float uzay = uz * ay;
    m->m_up.x = ux;
    m->m_up.y = uy;
    m->m_up.z = uz;
    m->m_ui32Flags &= 0xfffdfffcu;
    m->m_right.z = ppc::fmsubs(ux, ay, uyax);
    m->m_right.y = ppc::fmsubs(uz, ax, uxaz);
    m->m_right.x = ppc::fmsubs(uy, az, uzay);
}
