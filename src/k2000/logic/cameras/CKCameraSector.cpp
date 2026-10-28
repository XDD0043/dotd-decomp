// CKCameraSector.cpp - reconstructed original translation unit 0x128e18-0x12a888 (GAME_TOC1, main_toc1), 21 functions, 21 live.
// Primary class: CKCameraSector  key 0x20c  category Logic  size 0x58  vtable 0xb130f8
// Other owners: CKCamera (2)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x128e18  CKCameraSector_Delete
//   [ ] 0x128e68  CKCameraSector_SetDefaultState
//   [x] 0x128e90  CKCameraSector_TestCandidateByMode_maybe
//   [ ] 0x1290b8  RegisterCKCameraSectorClass
//   [ ] 0x129130  _GLOBAL__I_129130
//   [x] 0x129140  CKCameraSector_QueueActivateSignals_maybe
//   [ ] 0x129178  CKCameraSector_RecursiveRegistration
//   [x] 0x129268  CKCameraSector_DeleteArray
//   [x] 0x129308  CKCameraSector_Create
//   [x] 0x129358  CKCameraSector_FlushTriggerSignals_maybe
//   [ ] 0x1293d8  CKCameraSector_SetGameState
//   [x] 0x129438  CKCameraSector_IsEnabledForFocusedHero_maybe
//   [x] 0x1294a0  CKCameraSector_CreateArray
//   [x] 0x129550  CKCameraSector_ContainsPoint_maybe
//   [ ] 0x129670  CKCameraSector_MessageProc
//   [ ] 0x1296e8  CKCameraSector_PostLoad
//   [ ] 0x129748  CKCameraSector_Destroy
//   [x] 0x1297e8  CKCameraSector_ScoreCandidateAlignment_maybe
//   [x] 0x129aa8  CKCameraSector_FindValidCamera_maybe
//   [x] 0x129da8  CKCameraSector_Load
//   [ ] 0x12a2c8  CKCameraSector_Save
//
//   [ ] 0x9915b8  CKCameraSector_GetClassType  [inline]
//   [ ] 0x9915c0  CKCameraSector_GetClassID  [inline]
//   [ ] 0x9917e0  CKCameraSector_IsKindOfClass  [inline]
//   [ ] 0x992010  CKCameraSector_DeletingDestructor  [inline]
//   [ ] 0x992090  CKCameraSector_Destructor  [inline]
#include "k2000/logic/cameras/CKCameraSector.h"

#include <cfloat>
#include <cmath>
#include <cstring>

#include "crt/ppc_ops.h"
#include "k2000/cameras/CKSrvCamera.h"
#include "k2000/cameras/IKCamera.h"
#include "k2000/io/IKFile.h"
#include "k2000/logic/CDefaultGameManager.h"
#include "k2000/logic/CKLevel.h"
#include "k2000/memory/Mem.h"
#include "k2000/misc/CKGameLoop.h"
#include "k2000/misc/Engine.h"

namespace {

// 0x00010690 Math_Sqrtf (fsqrts).
inline float Sqrtf(float x) { return std::sqrt(x); }

}  // namespace

// 0x00129438 CKCameraSector_IsEnabledForFocusedHero_maybe
bool CKCameraSector::IsEnabledForFocusedHero() const {
    if ((m_unk2d & 2u) == 0) return false;
    uint32_t sector;
    std::memcpy(&sector, &m_unk40, sizeof(sector));
    if (sector == 0) return true;
    return static_cast<uint32_t>(g_pEngine->m_gameManager->m_level->m_currentSector) == sector;
}

// 0x00129550 CKCameraSector_ContainsPoint_maybe (the same test as the constraint zones', 0x1540d8)
bool CKCameraSector::ContainsPoint(const float* point) const {
    const float x = point[0];
    const float minX = m_AABB[3];
    if (!(minX <= x)) return false;
    const float maxX = m_AABB[0];
    if (!(x <= maxX)) return false;
    const float minZ = m_AABB[5];
    const float z = point[2];
    if (!(minZ <= z)) return false;
    const float maxZ = m_AABB[2];
    if (!(z <= maxZ)) return false;
    const float y = point[1];
    const float minY = m_AABB[4];
    if (!(minY <= y)) return false;
    const float maxY = m_AABB[1];
    if (!(y <= maxY)) return false;
    const uint32_t shape = (m_unk2d >> 5) & 3u;
    if (shape == 1) {  // a cylinder
        const float sumZ = minZ + maxZ;
        const float sumX = minX + maxX;
        const float extent = maxX - minX;
        float dz = ppc::fmsubs(sumZ, 0.5f, z);
        float dx = ppc::fmsubs(sumX, 0.5f, x);
        float radius = extent * 0.5f;
        dz = dz * dz;
        radius = radius * radius;
        dx = ppc::fmadds(dx, dx, dz);
        return dx <= radius;
    }
    if (shape == 0) return true;
    if (shape != 2) return false;
    const float sumY = minY + maxY;  // a sphere
    const float sumX = minX + maxX;
    const float sumZ = minZ + maxZ;
    const float extent = maxX - minX;
    float dy = ppc::fmsubs(sumY, 0.5f, y);
    float dx = ppc::fmsubs(sumX, 0.5f, x);
    float dz = ppc::fmsubs(sumZ, 0.5f, z);
    float radius = extent * 0.5f;
    dy = dy * dy;
    radius = radius * radius;
    dx = ppc::fmadds(dx, dx, dy);
    dz = ppc::fmadds(dz, dz, dx);
    return dz <= radius;
}

// 0x00128e90 CKCameraSector_TestCandidateByMode_maybe
bool CKCameraSector::TestCandidateByMode(const IKCamera* camera, const float* focusPos, const float* cameraPos,
                                         float* best) const {
    if (m_unk2f > 4) return false;
    if (m_unk2f == 0) return true;
    const bool threeD = ((m_unk2d >> 2) & 1u) != 0;
    const float* point = (m_unk2f <= 2) ? focusPos : cameraPos;  // modes 1 / 2 and 3 / 4
    float distance;
    if (threeD) {
        const float dx = point[0] - camera->m_WorldPosition.x;
        const float dy = point[1] - camera->m_WorldPosition.y;
        const float dz = point[2] - camera->m_WorldPosition.z;
        distance = ppc::fmadds(dx, dx, dy * dy);
        distance = ppc::fmadds(dz, dz, distance);
    } else {
        const float dx = point[0] - camera->m_WorldPosition.x;
        const float dz = point[2] - camera->m_WorldPosition.z;
        distance = ppc::fmadds(dx, dx, dz * dz);
    }
    const bool nearest = (m_unk2f == 1 || m_unk2f == 3);
    if (nearest) {
        // accepted when nothing is stored yet (-1) or the distance is smaller
        if (*best == -1.0f || distance < *best) {
            *best = distance;
            return true;
        }
        return false;
    }
    // modes 2 and 4: the farthest wins
    if (*best == -1.0f || distance > *best) {
        *best = distance;
        return true;
    }
    return false;
}

// 0x001297e8 CKCameraSector_ScoreCandidateAlignment_maybe. The thresholds are the TOC floats: cos 80, 70, ... 10 degrees.
bool CKCameraSector::ScoreCandidateAlignment(const IKCamera* camera, const float* direction3d, const float* direction2d,
                                             float* best) const {
    if (m_unk2e == 0) return true;
    float threshold = 0.0f;
    switch (m_unk2e) {
        case 1: threshold = -2.0f; break;
        case 2: threshold = 0.0f; break;
        case 3: threshold = 0.1736481785774231f; break;
        case 4: threshold = 0.3420201539993286f; break;
        case 5: threshold = 0.5f; break;
        case 6: threshold = 0.6427876353263855f; break;
        case 7: threshold = 0.7660444378852844f; break;
        case 8: threshold = 0.8660253882408142f; break;
        case 9: threshold = 0.9396926164627075f; break;
        case 10: threshold = 0.9848077297210693f; break;
        default: break;  // the original leaves the register as it was (modes above 10 are not used)
    }
    float dot;
    if (((m_unk2d >> 2) & 1u) == 0) {
        float dz = camera->m_WorldTarget.z - camera->m_WorldPosition.z;
        float dx = camera->m_WorldTarget.x - camera->m_WorldPosition.x;
        const float length = Sqrtf(ppc::fmadds(dx, dx, dz * dz));
        if (length != 0.0f) {
            const float inverse = 1.0f / length;
            dz = dz * inverse;
            dx = dx * inverse;
        }
        dot = ppc::fmadds(dx, direction2d[0], dz * direction2d[1]);
    } else {
        float dx = camera->m_WorldTarget.x - camera->m_WorldPosition.x;
        float dy = camera->m_WorldTarget.y - camera->m_WorldPosition.y;
        float dz = camera->m_WorldTarget.z - camera->m_WorldPosition.z;
        float sum = ppc::fmadds(dx, dx, dy * dy);
        const float length = Sqrtf(ppc::fmadds(dz, dz, sum));
        if (length != 0.0f) {
            const float inverse = 1.0f / length;
            dz = dz * inverse;
            dx = dx * inverse;
            dy = dy * inverse;
        }
        dot = ppc::fmadds(dz, direction3d[2], ppc::fmadds(dx, direction3d[0], dy * direction3d[1]));
    }
    if (static_cast<CKGameLoop*>(g_pEngine->m_gameLoop)->m_pendingSubsystemReset == 0) {
        if (threshold >= dot) return false;
    } else {
        // At the level start the first candidate (nothing stored yet: -FLT_MAX) is taken whatever its alignment.
        if (-FLT_MAX == *best) {
            *best = dot;
            return true;
        }
        if (!(threshold < dot)) return false;
    }
    if (*best >= dot) return false;
    *best = dot;
    return true;
}

// 0x00129aa8 CKCameraSector_FindValidCamera_maybe
IKCamera* CKCameraSector::FindValidCamera() {
    const uint32_t count = m_vpCameraCount;
    if (count == 0) return nullptr;
    CKSrvCamera* service = static_cast<CKSrvCamera*>(g_pEngine->m_srvCamera);
    const float focusPos[3] = {service->m_v3FocusPosCopy.x, service->m_v3FocusPosCopy.y, service->m_v3FocusPosCopy.z};
    IKCamera* const current = service->m_pCurrentCamera;
    const float realPos[3] = {service->m_v3RealPos.x, service->m_v3RealPos.y, service->m_v3RealPos.z};
    const float direction3d[3] = {service->m_v3RealAxisZ.x, service->m_v3RealAxisZ.y, service->m_v3RealAxisZ.z};
    float direction2d[2] = {direction3d[0], direction3d[2]};  // the real view direction over x/z, normalised
    const CVector3* startPosition = nullptr;
    if ((service->m_baTemporaryFlags & 0x40u) != 0) startPosition = &service->m_v3ScriptedStart;
    const float length = Sqrtf(ppc::fmadds(direction2d[0], direction2d[0], direction2d[1] * direction2d[1]));
    if (length != 0.0f) {
        const float inverse = 1.0f / length;
        direction2d[1] = direction2d[1] * inverse;
        direction2d[0] = direction2d[0] * inverse;
    }
    float bestDistance = -1.0f;
    float bestScore = -FLT_MAX;
    IKCamera* result = nullptr;
    for (uint32_t i = 0; i < count; ++i) {
        IKCamera* camera = static_cast<IKCamera*>(m_vpCamera[i]);
        if (current != camera) camera->Start(startPosition);
        float distance = bestDistance;
        float score = bestScore;
        if (m_unk2f == 0) {
            if (ScoreCandidateAlignment(camera, direction3d, direction2d, &score)) {
                bestScore = score;
                result = camera;
            }
        } else if (TestCandidateByMode(camera, focusPos, realPos, &distance)) {
            bestDistance = distance;
            result = ScoreCandidateAlignment(camera, direction3d, direction2d, &score) ? camera : nullptr;
        }
    }
    return result;
}

// 0x00129308 CKCameraSector_Create (the constructor inlined)
CKCameraSector::CKCameraSector() {
    m_vpCamera = nullptr;
    m_vpCameraCapacity = 5;
    m_vpCameraCount = 0;
}

// 0x00129da8 CKCameraSector_Load
int32_t CKCameraSector::Load(IKFile* file, int32_t type) {
    if (type != K_LEVEL_PLATEFORMS) return 1;
    ReadU8(file, &m_unk2d);
    ReadU32LEWords(file, reinterpret_cast<uint32_t*>(m_AABB), 6);  // one 0x18 read, swapped
    uint32_t count;
    ReadU32LE(file, &count);
    if (count != 0) {
        m_vpCameraCapacity = count;
        m_vpCamera = static_cast<IKSerializable**>(Mem_AllocAligned16(count * static_cast<uint32_t>(sizeof(IKSerializable*))));
        if (m_vpCameraCapacity < count) {  // the inlined reserve (grows by 5); never true here
            uint32_t grown = (count / 5) * 5 + 5;
            m_vpCamera = static_cast<IKSerializable**>(
                Mem_ReallocAligned16(m_vpCamera, grown * static_cast<uint32_t>(sizeof(IKSerializable*))));
            m_vpCameraCapacity = grown;
        }
        m_vpCameraCount = count;
        IKFile_ReadObjectRefArray(file, m_vpCamera, count);
    }
    ReadF32LE(file, &m_fTransitionTime);
    ReadU32LE(file, &m_unk34);
    ReadU32LE(file, &m_unk3c);
    IKFile_ReadRef(file, &m_unk28);
    ReadU8(file, &m_unk2c);
    ReadU8(file, &m_unk2f);
    ReadU8(file, &m_unk2e);
    ReadU8(file, &m_unk38);
    ReadF32LE(file, &m_unk40);
    m_tsUnk44.Load(file, K_LEVEL_PLATEFORMS);
    m_tsUnk4c.Load(file, K_LEVEL_PLATEFORMS);
    ReadF32LE(file, &m_unk54);
    return 1;
}

// 0x00129358 CKCameraSector_FlushTriggerSignals_maybe
void CKCameraSector::FlushTriggerSignals() {
    if (((m_unk2d >> 4) & 1) != 0 || 0.0f < m_unk54) {
        QueueTriggerSignals(&m_tsUnk44);
        m_unk2d = static_cast<uint8_t>((m_unk2d & 0xfc) | (m_unk2d & 1));
    }
}

// 0x00129140 CKCameraSector_QueueActivateSignals_maybe
void CKCameraSector::QueueActivateSignals() { QueueTriggerSignals(&m_tsUnk4c); }
