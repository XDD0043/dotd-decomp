// CKFlaggedPath.cpp - reconstructed original translation unit 0xc4048-0xc5140 (GAME_TOC1, main_toc1), 20 functions, 17 live.
// Primary class: CKFlaggedPath  key 0x5cc  category Logic  size 0x28  vtable 0xb17bd8
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0xc4048  CKFlaggedPath_Delete
//   [x] 0xc4098  CKFlaggedPath_RecursiveRegistration  (returns 1: the default slot)
//   [ ] 0xc40a0  CKFlaggedPath_Construct  [dead]
//   [ ] 0xc40c0  CKFlaggedPath_InterpolateAtDistance_maybe  [dead]
//   [ ] 0xc4200  CKFlaggedPath_Construct_2  [dead]
//   [ ] 0xc4220  RegisterCKFlaggedPathClass
//   [ ] 0xc4298  _GLOBAL__I_c4298
//   [x] 0xc42a8  CKFlaggedPath_DeleteArray
//   [x] 0xc4350  CKFlaggedPath_GetSegmentValueAt_maybe  (its caller CKHkRollingBarrel_UpdateBarrels_maybe is not ported (hooks))
//   [x] 0xc43f8  CKFlaggedPath_CreateArray
//   [x] 0xc44b0  CKFlaggedPath_Create
//   [x] 0xc4500  CKFlaggedPath_GetInfo  (returns 1: the default slot)
//   [x] 0xc4508  CKFlaggedPath_MessageProc  (returns 1: the default slot)
//   [ ] 0xc4510  CKFlaggedPath_Save
//   [x] 0xc4518  CKFlaggedPath_PostLoad  (returns 1: the default slot)
//   [x] 0xc4520  CKFlaggedPath_Destroy
//   [x] 0xc4568  CKFlaggedPath_Load
//   [x] 0xc4908  CKFlaggedPath_ComputeRollUpVector_maybe
//   [x] 0xc4d88  CKFlaggedPath_SetDistanceAndGetPositionUp_maybe
//   [x] 0xc4eb8  CKFlaggedPath_SetDistanceAndGetPosition
//
//   [ ] 0x9a1c60  CKFlaggedPath_GetClassType  [inline]
//   [ ] 0x9a1c68  CKFlaggedPath_GetClassID  [inline]
//   [ ] 0x9a1c70  CKFlaggedPath_IsKindOfClass  [inline]
//   [ ] 0x9a1c90  CKFlaggedPath_DeletingDestructor  [inline]
//   [ ] 0x9a1d10  CKFlaggedPath_Destructor  [inline]
//   [ ] 0x9a1d78  IKPath_IsKindOf  [inline]
#include "k2000/logic/ai/CKFlaggedPath.h"

#include <cmath>
#include <cstring>

#include "crt/ppc_ops.h"
#include "crt/xsinf.h"
#include "k2000/io/IKFile.h"
#include "k2000/logic/math/IKPath.h"
#include "k2000/memory/Mem.h"

namespace {

// 0x00c50d4c: the shared z axis (zero in the EBOOT's BSS; a static initialiser fills it).
const CVector3 kAxisZ = {0.0f, 0.0f, 1.0f};

// 0x00010690 Math_Sqrtf (fsqrts).
inline float Sqrtf(float x) { return std::sqrt(x); }

inline float PairValue(const CKFlaggedPath::Pair& pair) {
    float value;
    std::memcpy(&value, &pair.m_unk4, 4);
    return value;
}

}  // namespace

// 0x000c4908 CKFlaggedPath_ComputeRollUpVector_maybe. The angle's sine and cosine are the inlined polynomials for a
// non-negative angle, the library's cosf / sinf (with the sign) for a negative one.
void CKFlaggedPath::ComputeRollUpVector(float distance, const CVector3* direction, CVector3* up) {
    if (std::fabs(direction->y) > 0.95f) {
        *up = kAxisZ;
        return;
    }
    float angle = 0.0f;
    const uint32_t count = m_vPairs.m_ui32NbUsedElt;
    if (count != 0) {
        if (distance == 0.0f) {
            const Pair& first = m_vPairs.m_pBlock[0];
            if (m_aBeaconList[first.m_unk0] == 0.0f) angle = PairValue(first) * 0.01745329052209854f;  // TOC -0x5748 (0x3c8efa34)
        } else {
            float lowDistance = 0.0f;
            float lowValue = 0.0f;
            float highDistance = 0.0f;
            float highValue = 0.0f;
            bool found = false;
            for (uint32_t k = 0; k < count; ++k) {
                const Pair& pair = m_vPairs.m_pBlock[k];
                const float d = m_aBeaconList[pair.m_unk0];
                if (!(distance > d)) {
                    highDistance = d;
                    highValue = PairValue(pair);
                    found = true;
                    break;
                }
                lowValue = PairValue(pair);
                lowDistance = d;
            }
            if (!found) {
                highDistance = static_cast<IKPath*>(m_pPath)->GetLength();  // vt+0x5c
                highValue = lowValue;
            }
            const float t = (distance - lowDistance) / (highDistance - lowDistance);
            angle = ppc::fmadds(t, highValue - lowValue, lowValue) * 0.01745329052209854f;  // TOC -0x5748 (0x3c8efa34)
        }
    }
    const float dz = direction->z;
    const float dx = direction->x;
    const float dy = direction->y;
    const float negZ = -dz;
    int32_t bits;
    std::memcpy(&bits, &angle, 4);
    const float cosine = bits < 0 ? crt::LibCosf(-angle) : crt::InlineCosf(angle);
    const float sine = bits < 0 ? -crt::LibSinf(-angle) : crt::InlineSinf(angle);
    const float zero = 0.0f;
    const float horizontal = ppc::fmsubs(dx, dx, dz * negZ);
    const float crossX = ppc::fmsubs(dz, zero, dx * dy);
    const float crossZ = ppc::fmsubs(negZ, dy, dx * zero);
    const float y = ppc::fmadds(cosine, horizontal, sine * zero);
    const float x = ppc::fmadds(cosine, crossX, sine * negZ);
    const float z = ppc::fmadds(cosine, crossZ, sine * dx);
    up->y = y;
    up->x = x;
    up->z = z;
    const float length = Sqrtf(ppc::fmadds(z, z, ppc::fmadds(x, x, y * y)));
    if (length == 0.0f) return;
    const float inverse = 1.0f / length;
    up->z = inverse * up->z;
    up->x = inverse * up->x;
    up->y = inverse * up->y;
}

// 0x000c4d88 CKFlaggedPath_SetDistanceAndGetPositionUp_maybe
void CKFlaggedPath::SetDistanceAndGetPositionUp(float distance, CVector3* point, CVector3* direction, CVector3* up) {
    m_fCursorPos = distance;
    IKPath* path = static_cast<IKPath*>(m_pPath);
    if (up == nullptr) {
        path->GetPointAtDistance(distance, point, direction);  // vt+0x54
        return;
    }
    CVector3 along;
    if (direction == nullptr) {
        path->GetPointAtDistance(distance, point, &along);
    } else {
        path->GetPointAtDistance(distance, point, direction);
        along = *direction;
    }
    ComputeRollUpVector(distance, &along, up);
}

// 0x000c4eb8 CKFlaggedPath_SetDistanceAndGetPosition
void CKFlaggedPath::SetDistanceAndGetPosition(float distance, CVector3* point, CVector3* direction, CVector3* up) {
    int32_t passedBefore = -1;
    int32_t passedAfter = -1;
    const float cursor = m_fCursorPos;
    if (static_cast<int32_t>(m_ui32NbOfBeacon) > 0) {
        for (uint32_t i = 0; i < m_ui32NbOfBeacon; ++i) {
            const float beacon = m_aBeaconList[i];
            if (!(cursor <= beacon)) passedBefore = static_cast<int32_t>(i);
            if (!(distance <= beacon)) passedAfter = static_cast<int32_t>(i);
        }
    }
    if (!(cursor >= distance)) {
        for (int32_t k = passedBefore + 1; k <= passedAfter; ++k) QueueTriggerSignals(&m_aTriggerToCallList[k]);  // 0x00236338
    } else {
        for (int32_t k = passedAfter + 1; k <= passedBefore; ++k) QueueTriggerSignals(&m_aTriggerToCallList[k]);
    }
    SetDistanceAndGetPositionUp(distance, point, direction, up);  // the same tail (the cursor stored, the point)
}

// Inlined in 0x000c44b0 CKFlaggedPath_Create.
CKFlaggedPath::CKFlaggedPath() {
    m_vPairs.m_pBlock = nullptr;
    m_vPairs.m_ui32NbElt = 1;
    m_vPairs.m_ui32NbUsedElt = 0;
}

// 0x000c4568 CKFlaggedPath_Load
int32_t CKFlaggedPath::Load(IKFile* file, int32_t type) {
    if (type != K_LEVEL_PLATEFORMS) return 1;
    IKFile_ReadRef(file, &m_pPath);
    ReadU32LE(file, &m_ui32NbOfBeacon);
    ReadF32LE(file, &m_fCursorPos);
    uint32_t n = m_ui32NbOfBeacon;
    if (n == 0) {
        m_aTriggerToCallList = nullptr;
        m_aBeaconList = nullptr;
    } else {
        // One block: the positions (a float each), then the starters.
        void* block = Mem_AllocAligned16(n * static_cast<uint32_t>(sizeof(float) + sizeof(CTriggerStarter)));
        n = m_ui32NbOfBeacon;
        m_aBeaconList = static_cast<float*>(block);
        m_aTriggerToCallList = reinterpret_cast<CTriggerStarter*>(m_aBeaconList + n);
        ReadU32LEWords(file, reinterpret_cast<uint32_t*>(m_aBeaconList), n);
        for (uint32_t i = 0; i < m_ui32NbOfBeacon; ++i) m_aTriggerToCallList[i].Load(file, K_LEVEL_PLATEFORMS);
    }
    uint32_t count = 0;
    ReadU32LE(file, &count);
    if (count == 0) {
        // BUG(original): the used count is not set here (it keeps the constructor's 0).
        m_vPairs.m_ui32NbElt = 1;
        m_vPairs.m_pBlock = static_cast<Pair*>(Mem_AllocAligned16(static_cast<uint32_t>(sizeof(Pair))));
    } else {
        m_vPairs.m_ui32NbElt = count;
        m_vPairs.m_pBlock = static_cast<Pair*>(Mem_AllocAligned16(count * static_cast<uint32_t>(sizeof(Pair))));
        if (m_vPairs.m_ui32NbElt < count) {  // as in the original: cannot happen
            uint32_t capacity = count + 1;
            if (capacity == 0) capacity = 1;
            m_vPairs.m_pBlock = static_cast<Pair*>(
                Mem_ReallocAligned16(m_vPairs.m_pBlock, capacity * static_cast<uint32_t>(sizeof(Pair))));
            m_vPairs.m_ui32NbElt = capacity;
        }
        m_vPairs.m_ui32NbUsedElt = count;
    }
    for (uint32_t i = 0; i < count; ++i) {
        ReadU32LE(file, &m_vPairs.m_pBlock[i].m_unk0);
        ReadU32LE(file, &m_vPairs.m_pBlock[i].m_unk4);
    }
    return 1;
}

// 0x000c4520 CKFlaggedPath_Destroy
void CKFlaggedPath::Destroy() {
    if (m_aBeaconList != nullptr) {
        Mem_FreeAligned16(m_aBeaconList);
        m_aBeaconList = nullptr;
    }
}

// 0x000c4350 CKFlaggedPath_GetSegmentValueAt_maybe
float CKFlaggedPath::GetSegmentValueAt(float distance) const {
    float value = 0.0f;  // TOC -0x57a4
    const uint32_t count = m_vPairs.m_ui32NbUsedElt;
    if (count == 0) return value;
    if (distance == value) {
        const Pair& first = m_vPairs.m_pBlock[0];
        if (m_aBeaconList[first.m_unk0] != value) return value;
        return PairValue(first);
    }
    for (uint32_t i = 0; i < count; ++i) {
        const Pair& pair = m_vPairs.m_pBlock[i];
        if (!(m_aBeaconList[pair.m_unk0] < distance)) return value;  // bge: NaN takes it
        value = PairValue(pair);
    }
    return value;
}
