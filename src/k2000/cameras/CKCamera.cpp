// CKCamera.cpp - reconstructed original translation unit 0x13d8c8-0x13e2b8 (GAME_TOC1, main_toc1), 16 functions, 16 live.
// Primary class: CKCamera  key 0x47  category Camera  size 0x88  vtable 0xb1a2b8
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x13d8c8  CKCamera_Delete
//   [x] 0x13d918  CKCamera_vf54  (empty: IKCamera::Pause)
//   [x] 0x13d920  CKCamera_vf5C  (empty: IKCamera::Resume)
//   [ ] 0x13d928  RegisterCKCameraClass
//   [ ] 0x13d9a0  _GLOBAL__I_13d9a0
//   [x] 0x13d9b0  CKCamera_RecursiveRegistration  (inherited: IKCamera_LevelReset 0x144108, a tail call)
//   [x] 0x13d9d8  CKCamera_Activate_maybe
//   [x] 0x13da10  CKCamera_Destroy  (inherited: CKCameraTrack_ClearReferences_BaseNop_maybe)
//   [x] 0x13da38  CKCamera_DeleteArray
//   [x] 0x13dae0  CKCamera_Create
//   [x] 0x13db38  CKCamera_ResetTrack_maybe
//   [x] 0x13db90  CKCamera_Deactivate_maybe
//   [x] 0x13dc60  CKCamera_Update
//   [x] 0x13dea0  CKCamera_CreateArray
//   [x] 0x13df58  CKCamera_Load
//   [ ] 0x13e100  CKCamera_Save
//
//   [ ] 0x9a75e8  CKCamera_IsKindOfClass  [inline]
//   [ ] 0x9a7610  CKCamera_GetClassType  [inline]
//   [ ] 0x9a7618  CKCamera_GetClassID  [inline]
//   [ ] 0x9a7620  CKCamera_vf84  [inline]
//   [ ] 0x9a7628  CKCamera_vfB0  [inline]
//   [ ] 0x9a7638  CKCamera_vf88  [inline]
//   [ ] 0x9a7670  CKCamera_DeletingDestructor  [inline]
//   [ ] 0x9a76b8  CKCamera_Destructor  [inline]
//   [ ] 0x9a76e8  CKCamera_vfB8  [inline]
#include "k2000/cameras/CKCamera.h"

#include <cmath>

#include "crt/ppc_ops.h"
#include "k2000/core/Stub.h"
#include "k2000/io/IKFile.h"

namespace {

// 0x00010690 Math_Sqrtf (fsqrts).
inline float Sqrtf(float x) { return std::sqrt(x); }

// 0x00c50d40: the shared Y axis (zero in the EBOOT's BSS, filled by a static initialiser).
const CVector3 kAxisY = {0.0f, 1.0f, 0.0f};

}  // namespace

// 0x0013d9d8 CKCamera_Activate_maybe. CKCamera_StartAttachedFx_maybe (0x1441e8): with an attached fx (+0x50; none of
// the game's cameras has one) +0x54 is taken from it and CKSrvFx_StartCameraFx_maybe (0x1afaf8) starts it.
void CKCamera::Start(const CVector3* /*startPosition*/) {
    StartAttachedFx();  // 0x001441e8
    m_fMoveElapsed = 0.0f;  // (a word store of 0)
}

// 0x0013db90 CKCamera_Deactivate_maybe. CKCamera_StopAttachedFx_maybe (0x144238) is CKSrvFx_StopCameraFx_maybe
// 0x1affd8 on the attached fx. The reset only runs for a camera with a move duration and a move offset other than the
// null vector (0x00c50d64).
void CKCamera::Stop() {
    StopAttachedFx();  // 0x00144238
    if (m_fMoveDuration != 0.0f && (m_v3MoveOffset.x != 0.0f || m_v3MoveOffset.y != 0.0f || m_v3MoveOffset.z != 0.0f)) {
        m_WorldPosition.x = m_unk5c.x;
        m_WorldPosition.z = m_unk5c.z;
        m_WorldPosition.y = m_unk5c.y;
        m_WorldTarget.x = m_unk68.x;
        m_WorldTarget.z = m_unk68.z;
        m_WorldTarget.y = m_unk68.y;
    }
}

// 0x0013df58 CKCamera_Load
int32_t CKCamera::Load(IKFile* file, int32_t type) {
    BaseLoad(file, type);
    if (type == K_LEVEL_PLATEFORMS) {
        ReadU32LE(file, &m_unk58);
        ReadF32LE(file, &m_fMoveDuration);
        ReadU32LEWords(file, reinterpret_cast<uint32_t*>(&m_v3MoveOffset), 3);  // one 0xc read, swapped
    }
    m_unk5c.x = m_WorldPosition.x;
    m_unk5c.z = m_WorldPosition.z;
    m_unk5c.y = m_WorldPosition.y;
    m_unk68.x = m_WorldTarget.x;
    m_unk68.z = m_WorldTarget.z;
    m_unk68.y = m_WorldTarget.y;
    return 1;
}

// 0x0013db38 CKCamera_ResetTrack_maybe
void CKCamera::ResetTrack() {
    m_WorldPosition.x = m_unk5c.x;
    m_WorldPosition.z = m_unk5c.z;
    m_WorldPosition.y = m_unk5c.y;
    m_WorldTarget.x = m_unk68.x;
    m_WorldTarget.z = m_unk68.z;
    m_WorldTarget.y = m_unk68.y;
    m_unk18 = m_fFov;
    m_unk58 = m_unk44;
}

// 0x0013dc60 CKCamera_Update (vt+0x60). The move offset is (right, up, along the view): the right axis is the
// world up (0x00c50d40) crossed with the view direction, the up axis the right one crossed with the view direction
// again (neither normalised).
void CKCamera::Update(float frameTime) {
    UpdateTrackBase();
    const float zero = 0.0f;  // TOC -0x3e28
    if (m_fMoveDuration == zero || !(m_fMoveDuration > m_fMoveElapsed)) return;
    m_fMoveElapsed = frameTime + m_fMoveElapsed;
    float dx = m_WorldTarget.x - m_WorldPosition.x;
    float dy = m_WorldTarget.y - m_WorldPosition.y;
    float dz = m_WorldTarget.z - m_WorldPosition.z;
    const float length = Sqrtf(ppc::fmadds(dz, dz, ppc::fmadds(dx, dx, dy * dy)));
    if (length != zero) {
        const float inverse = 1.0f / length;
        dz = dz * inverse;
        dx = dx * inverse;
        dy = dy * inverse;
    }
    const float right = m_v3MoveOffset.x;
    const float along = m_v3MoveOffset.z;
    float oz = ppc::fmadds(along, dz, zero);
    float ox = ppc::fmadds(along, dx, zero);
    float oy = ppc::fmadds(along, dy, zero);
    const float up = m_v3MoveOffset.y;
    if (right != zero || up != zero) {
        const float t9 = kAxisY.x * dz;
        const float t11 = kAxisY.y * dx;
        const float t10 = kAxisY.z * dy;
        const float ry = ppc::fmsubs(kAxisY.z, dx, t9);
        const float rz = ppc::fmsubs(kAxisY.x, dy, t11);
        const float rx = ppc::fmsubs(kAxisY.y, dz, t10);
        const float u8 = ry * dz;
        const float u10 = rz * dx;
        const float u9 = rx * dy;
        oz = ppc::fmadds(right, rz, oz);
        const float rightX = ppc::fmadds(right, rx, ox);
        const float rightY = ppc::fmadds(right, ry, oy);
        const float ux = ppc::fmsubs(rz, dy, u8);
        const float uy = ppc::fmsubs(rx, dz, u10);
        const float uz = ppc::fmsubs(ry, dx, u9);
        ox = ppc::fmadds(ux, up, rightX);
        oy = ppc::fmadds(uy, up, rightY);
        oz = ppc::fmadds(uz, up, oz);
    }
    if (!(m_fMoveElapsed >= m_fMoveDuration)) {
        const float fraction = m_fMoveElapsed / m_fMoveDuration;
        oz = oz * fraction;
        ox = ox * fraction;
        oy = oy * fraction;
    }
    m_WorldPosition.x = m_unk5c.x + ox;
    m_WorldPosition.z = m_unk5c.z + oz;
    m_WorldPosition.y = m_unk5c.y + oy;
    m_WorldTarget.x = m_unk68.x + ox;
    m_WorldTarget.z = m_unk68.z + oz;
    m_WorldTarget.y = m_unk68.y + oy;
}
