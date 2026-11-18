// CKCameraPathTrack.cpp - reconstructed original translation unit 0x13add0-0x13c110 (GAME_TOC1, main_toc1), 20 functions, 19 live.
// Primary class: CKCameraPathTrack  key 0x107  category Camera  size 0x84  vtable 0xb1a078
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x13add0  CKCameraPathTrack_Delete
//   [x] 0x13ae20  CKCameraPathTrack_vf54
//   [x] 0x13ae28  CKCameraPathTrack_vf5C
//   [x] 0x13ae30  CKCameraPathTrack_GetRollAtTime_maybe
//   [ ] 0x13af58  CKCameraPathTrack_IsAtPathEnd_2_maybe  [dead]
//   [ ] 0x13afe8  RegisterCKCameraPathTrackClass
//   [ ] 0x13b060  _GLOBAL__I_13b060
//   [x] 0x13b070  CKCameraPathTrack_PostLoad
//   [x] 0x13b098  CKCameraPathTrack_RecursiveRegistration  (CKCameraPathTrack::RecursiveRegistration)
//   [x] 0x13b110  CKCameraPathTrack_Deactivate_maybe
//   [x] 0x13b138  CKCameraPathTrack_Activate_maybe
//   [x] 0x13b1b0  CKCameraPathTrack_Destroy  (CKCameraPathTrack::Destroy)
//   [x] 0x13b208  CKCameraPathTrack_DeleteArray
//   [x] 0x13b2b0  CKCameraPathTrack_Construct
//   [x] 0x13b2f0  CKCameraPathTrack_Construct_2  [dead: no pointer to its descriptor 0xb5bd18, no call]  (the constructor: the same stores as 0x13b2b0 CKCameraPathTrack_Construct)
//   [x] 0x13b330  CKCameraPathTrack_Update_maybe
//   [x] 0x13b990  CKCameraPathTrack_CreateArray
//   [x] 0x13ba58  CKCameraPathTrack_Create
//   [x] 0x13bab8  CKCameraPathTrack_Load
//   [ ] 0x13bdd0  CKCameraPathTrack_Save
//
//   [ ] 0x9a7320  CKCameraPathTrack_IsKindOfClass  [inline]
//   [ ] 0x9a7348  CKCameraPathTrack_GetClassType  [inline]
//   [ ] 0x9a7350  CKCameraPathTrack_GetClassID  [inline]
//   [x] 0x9a7358  CKCameraPathTrack_ResetTrack_maybe  [inline]
//   [ ] 0x9a7368  CKCameraPathTrack_Destructor  [inline]
//   [ ] 0x9a7398  CKCameraPathTrack_DeletingDestructor  [inline]
//   [x] 0x9a73e0  CKCameraPathTrack_IsAtPathEnd_maybe  [inline]
#include "k2000/cameras/CKCameraPathTrack.h"

#include "crt/ppc_ops.h"
#include "k2000/cameras/CKSrvCamera.h"
#include "k2000/core/Stub.h"
#include "k2000/io/IKFile.h"
#include "k2000/logic/math/IKPath.h"
#include "k2000/misc/Engine.h"
#include "k2000/misc/Mat4.h"

// 0x0013ba58 CKCameraPathTrack_Create
CKCameraPathTrack::CKCameraPathTrack() { m_av2RollAlongTime = nullptr; }

// 0x0013b098 CKCameraPathTrack_RecursiveRegistration
void CKCameraPathTrack::RecursiveRegistration(int32_t type) {
    IKCamera::RecursiveRegistration(type);  // 0x00144108
    if (m_pPath != nullptr) m_pPath->RecursiveRegistration(type);
}

// 0x0013b1b0 CKCameraPathTrack_Destroy
void CKCameraPathTrack::Destroy() {
    IKCamera::Destroy();  // CKCameraTrack_ClearReferences_BaseNop_maybe 0x144578 (empty)
    if (m_av2RollAlongTime != nullptr) {
        delete[] m_av2RollAlongTime;  // OperatorDeleteArray (the count cookie)
        m_ui32NbRollPoint = 0;
        m_av2RollAlongTime = nullptr;
    }
}

// 0x0013bab8 CKCameraPathTrack_Load
int32_t CKCameraPathTrack::Load(IKFile* file, int32_t type) {
    BaseLoad(file, type);
    if (type == K_LEVEL_PLATEFORMS) {
        IKFile_ReadRef(file, &m_pPath);
        ReadF32LE(file, &m_fPosOnPath);
        ReadF32LE(file, &m_fCameraSpeed);
        ReadF32LE(file, &m_fTargetOffset);
        ReadU32LE(file, &m_ui32NbRollPoint);
        if (m_ui32NbRollPoint == 0) {
            m_av2RollAlongTime = nullptr;
        } else {
            // OperatorNewArray(count * 8 + 4): the count cookie, then the points (new CVector2[count]).
            m_av2RollAlongTime = new CVector2[m_ui32NbRollPoint];
            // One read of count * 8 bytes, then each word swapped.
            ReadU32LEWords(file, reinterpret_cast<uint32_t*>(m_av2RollAlongTime), m_ui32NbRollPoint * 2);
        }
        ReadU32LEWords(file, reinterpret_cast<uint32_t*>(&m_v3StartTargetRef), 3);  // one 0xc read, swapped
        ReadU8(file, &m_ba8PathTrackInfos);
    }
    return 1;
}

namespace {
IKPath* PathOf(const CKCameraPathTrack* track) { return static_cast<IKPath*>(track->m_pPath); }

// The loop bit's wrap of the Update: below 0 the length is added until it is not; from the length on it is subtracted
// until it is below (fcmpu + cror: NaN stays).
float WrapDistance(float distance, float length) {
    if (!(distance >= 0.0f)) {  // bge: NaN adds the length once
        do distance = distance + length;
        while (distance < 0.0f);
    }
    if (distance >= length) {
        do distance = distance - length;
        while (length <= distance);
    }
    return distance;
}
}  // namespace

// 0x0013b138 CKCameraPathTrack_Activate_maybe
void CKCameraPathTrack::Start(const CVector3* /*startPosition*/) {
    StartAttachedFx();  // 0x001441e8 CKCamera_StartAttachedFx_maybe
    if (m_pPath == nullptr) return;
    m_fPosOnPath = 0.0f;
    m_fTimeSinceStart = 0.0f;
    Update(0.0f);  // vt+0x60
}

// 0x0013b110 CKCameraPathTrack_Deactivate_maybe
void CKCameraPathTrack::Stop() {
    StopAttachedFx();  // 0x00144238 CKCamera_StopAttachedFx_maybe
}

// 0x0013b330 CKCameraPathTrack_Update_maybe
void CKCameraPathTrack::Update(float frameTime) {
    UpdateTrackBase();  // 0x00144398
    if (m_pPath == nullptr) return;
    m_fTimeSinceStart = frameTime + m_fTimeSinceStart;
    const uint32_t mode = m_ba8PathTrackInfos & 3u;
    const bool loop = ((m_ba8PathTrackInfos >> 2) & 1u) != 0;
    IKPath* path = PathOf(this);
    if (mode == 0 || mode == 1) {
        if (mode == 0) {
            m_WorldTarget = static_cast<CKSrvCamera*>(g_pEngine->m_srvCamera)->m_v3FocusPos;
        } else {
            m_WorldTarget = m_v3StartTargetRef;
        }
        const float y = m_WorldTarget.y + m_fTargetOffset;
        float distance = ppc::fmadds(frameTime, m_fCameraSpeed, m_fPosOnPath);
        m_WorldTarget.y = y;
        m_fPosOnPath = distance;
        const float length = path->GetLength();  // vt+0x5c
        if (loop) {
            distance = WrapDistance(distance, length);
        } else if (!(distance < length)) {
            distance = length;
        }
        m_fPosOnPath = distance;
        path->GetPointAtDistance(distance, &m_WorldPosition, nullptr);  // vt+0x54
        return;
    }
    float distance = ppc::fmadds(frameTime, m_fCameraSpeed, m_fPosOnPath);
    m_fPosOnPath = distance;
    const float length = path->GetLength();
    if (loop) {
        distance = WrapDistance(distance, length);
    } else if (!(distance < length)) {
        distance = length;
    }
    m_fPosOnPath = distance;
    if (mode == 2) {
        path->GetPointAtDistance(distance, &m_WorldPosition, nullptr);
        const CVector3 p = m_WorldPosition;
        m_WorldTarget.x = p.x + m_v3StartTargetRef.x;
        m_WorldTarget.z = p.z + m_v3StartTargetRef.z;
        m_WorldTarget.y = p.y + m_v3StartTargetRef.y;
        return;
    }
    // mode 3
    CVector3 direction;
    path->GetPointAtDistance(distance, &m_WorldPosition, &direction);
    static const CVector3 kAxisY = {0.0f, 1.0f, 0.0f};  // 0x00c50d40
    CMatrix34 frame;
    frame.m_right = {1.0f, 0.0f, 0.0f};
    frame.m_ui32Flags = 0x20003;
    frame.m_up = {0.0f, 1.0f, 0.0f};
    frame.m_at = {0.0f, 0.0f, 1.0f};
    frame.m_pos = {0.0f, 0.0f, 0.0f};
    frame.m_ui32pad1 = frame.m_ui32pad2 = frame.m_ui32pad3 = 0;  // stack garbage in the original (never read)
    Mat4_SetBasisFromRightUp(&frame, &direction, &kAxisY);
    const CVector3 p = m_WorldPosition;
    float x = ppc::fmadds(m_v3StartTargetRef.x, frame.m_right.x, p.x);
    float z = ppc::fmadds(m_v3StartTargetRef.x, frame.m_right.z, p.z);
    float y = ppc::fmadds(m_v3StartTargetRef.x, frame.m_right.y, p.y);
    x = ppc::fmadds(m_v3StartTargetRef.y, frame.m_up.x, x);
    z = ppc::fmadds(m_v3StartTargetRef.y, frame.m_up.z, z);
    y = ppc::fmadds(m_v3StartTargetRef.y, frame.m_up.y, y);
    m_WorldTarget.x = ppc::fmadds(m_v3StartTargetRef.z, frame.m_at.x, x);
    m_WorldTarget.z = ppc::fmadds(m_v3StartTargetRef.z, frame.m_at.z, z);
    m_WorldTarget.y = ppc::fmadds(m_v3StartTargetRef.z, frame.m_at.y, y);
}

// 0x009a73e0 CKCameraPathTrack_IsAtPathEnd_maybe
uint8_t CKCameraPathTrack::IsFinished() {
    if (((m_ba8PathTrackInfos >> 2) & 1u) != 0 || m_pPath == nullptr) return 0;
    return PathOf(this)->GetLength() == m_fPosOnPath ? 1 : 0;
}

// 0x0013ae30 CKCameraPathTrack_GetRollAtTime_maybe
float CKCameraPathTrack::Vf84() const {
    const int32_t count = static_cast<int32_t>(m_ui32NbRollPoint);
    if (count <= 0) return 0.0f;
    const CVector2* points = m_av2RollAlongTime;
    const float t = m_fTimeSinceStart;
    int32_t lo = -1;
    int32_t hi = -1;
    for (int32_t i = 0; i < count; ++i) {
        if (points[i].m_fX >= t) {  // fcmpu + cror gt|eq
            hi = i;
            break;
        }
        lo = i;
    }
    if (lo == -1) return hi == -1 ? 0.0f : points[hi].m_fY;
    if (hi == -1) return points[lo].m_fY;
    const float dy = points[hi].m_fY - points[lo].m_fY;
    if (dy == 0.0f) return points[lo].m_fY;
    const float dx = points[hi].m_fX - points[lo].m_fX;
    if (dx == 0.0f) return points[lo].m_fY;
    const float slope = dy / dx;
    const float line = ppc::fmadds(slope, t, points[lo].m_fY);
    return line - points[lo].m_fX * slope;
}
