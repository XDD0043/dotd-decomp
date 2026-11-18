// CKDetectorBase.cpp - reconstructed original translation unit 0x1a8608-0x1a9890 (GAME_TOC1, main_toc1), 17 functions, 17 live.
// Primary class: CKDetectorBase  key 0x270c  category Logic  size 0x14  vtable 0xb1c3a8
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x1a8608  CKDetectorBase_Delete
//   [x] 0x1a8658  CKDetectorBase_SetGameState
//   [ ] 0x1a86f8  RegisterCKDetectorBaseClass
//   [ ] 0x1a8770  _GLOBAL__I_1a8770
//   [x] 0x1a8780  CKDetectorBase_DeleteArray
//   [x] 0x1a8828  CKDetectorBase_CreateArray
//   [x] 0x1a88c0  CKDetectorBase_Create
//   [x] 0x1a88f8  CKDetectorBase_SetDefaultState
//   [x] 0x1a8948  CKDetectorBase_SetEnabled_maybe
//   [x] 0x1a8978  CKDetectorBase_GetInfo
//   [x] 0x1a89d0  CKDetectorBase_Save  (returns 1: the default)
//   [x] 0x1a89d8  CKDetectorBase_MessageProc
//   [x] 0x1a8a68  CKDetectorBase_RecursiveRegistration  (returns 1: the default)
//   [x] 0x1a8a70  CKDetectorBase_PostLoad  (returns 1: the default)
//   [x] 0x1a8a78  CKDetectorBase_Destroy
//   [x] 0x1a8a88  CKDetectorBase_Load
//   [x] 0x1a8c70  CKDetectorBase_CheckDetection_maybe
//
//   [ ] 0x9aaf38  CKDetectorBase_GetClassType  [inline]
//   [ ] 0x9aaf40  CKDetectorBase_GetClassID  [inline]
//   [ ] 0x9aaf48  CKDetectorBase_GetTriggerProp2  [inline]
//   [ ] 0x9aaf58  CKDetectorBase_vf5C  [inline]
//   [ ] 0x9aaf60  CKDetectorBase_Destructor  [inline]
//   [ ] 0x9aaf78  CKDetectorBase_vf54  [inline]
//   [ ] 0x9aafa8  CKDetectorBase_IsKindOfClass  [inline]
//   [ ] 0x9aafc8  CKDetectorBase_DeletingDestructor  [inline]
#include "k2000/logic/ai/CKDetectorBase.h"

#include "k2000/core/IKInfo.h"
#include "k2000/io/IKFile.h"
#include "k2000/logic/CKLevel.h"
#include "k2000/logic/CMultiGeometryBasic.h"
#include "k2000/logic/ai/CKDetectedMovable.h"
#include "k2000/math/Vec3.h"
#include "k2000/misc/Engine.h"
#include "k2000/scenegraph/CSGMovable.h"
#include "k2000/system/CTimeManager.h"
#include "k2000/system/IKTime.h"
#include "Renderware/rwcore/RwCamera.h"

// 0x001a8948 CKDetectorBase_SetEnabled_maybe: bit 4 = enabled (the argument shifted in, as the original's
// rlwinm/or); disabling also clears bits 1-3.
void CKDetectorBase::SetEnabled(uint32_t enabled) {
    m_baData = (m_baData & ~0x10u) | ((enabled << 4) & 0xfffffff0u);
    if (enabled != 0) return;
    m_baData &= ~0xeu;
}

namespace {

// The movable's world position: its frame's LTM position (frame +0x80), as stored.
const RwV3d& MovablePosition(const CKDetectedMovable::Entry* entry) {
    return FrameLtm(static_cast<const CSGMovable*>(entry->m_pMovable)->m_pRwFrame)->pos;
}

// Shape type 0 (+0x04 max x, y, z, min x, y, z) or 1 (+0x04 centre, +0x10 extent, +0x14 squared radius) holds `pos`;
// other types hold nothing. Inlined in Detect.
uint8_t ShapeHolds(const CMultiGeometryBasic* shape, const RwV3d& pos) {
    const float* s = shape->m_afShape;
    switch (shape->m_baData & 3) {
    case 0:
        return s[3] <= pos.x && s[0] >= pos.x && s[5] <= pos.z && s[2] >= pos.z && s[4] <= pos.y && pos.y <= s[1] ? 1 : 0;
    case 1: {
        const float point[3] = {pos.x, pos.y, pos.z};
        return static_cast<uint8_t>(Vec3_IsWithinRadius(s[3], s[4], s, point));  // 0x2441e8
    }
    default:
        return 0;
    }
}

// Shape type 2, inlined twice in Detect (two jump tables of six cases): the move from `from` to `to` crosses the
// rectangle of the shape (+0x04 its centre, +0x10 / +0x14 its half extents along the two other axes in x, y, z order)
// on the plane of axis byte / 2 (+0x18: 0, 1 x, 2, 3 y, 4, 5 z), from above to at or below it for an even byte, from
// below to at or above it for an odd one. A byte past 5 crosses nothing.
uint8_t MoveCrossesRectangle(const CMultiGeometryBasic* shape, const float* from, const float* to) {
    const uint8_t mode = shape->m_ui8ShapeByte;
    if (mode > 5) return 0;
    const float* s = shape->m_afShape;
    const int32_t a = mode >> 1;
    const int32_t b = a == 0 ? 1 : 0;
    const int32_t c = a == 2 ? 1 : 2;
    const float d[3] = {to[0] - from[0], to[1] - from[1], to[2] - from[2]};
    const float plane = s[a];
    if ((mode & 1) == 0) {
        if (!(from[a] > plane && to[a] <= plane)) return 0;
    } else {
        if (!(from[a] < plane && to[a] >= plane)) return 0;
    }
    if (d[a] == 0.0f) return 0;
    const float lo1 = s[b] - s[3];
    const float hi1 = s[b] + s[3];
    if (!((from[b] > lo1 && to[b] < hi1) || (from[b] < hi1 && to[b] > lo1))) return 0;
    const float lo2 = s[c] - s[4];
    const float hi2 = s[c] + s[4];
    if (!((from[c] > lo2 && to[c] < hi2) || (from[c] < hi2 && to[c] > lo2))) return 0;
    const float t = (plane - from[a]) / d[a];
    const float vb = ppc::fmadds(d[b], t, from[b]);
    if (!(lo1 < vb)) return 0;
    if (!(hi1 > vb)) return 0;
    const float vc = ppc::fmadds(d[c], t, from[c]);
    if (!(lo2 < vc)) return 0;
    return hi2 > vc ? 1 : 0;
}

}  // namespace

// 0x001a8c70 CKDetectorBase_CheckDetection_maybe
int32_t CKDetectorBase::Detect() {
    if ((m_baData & 0x10) == 0) return 0;
    if (m_ui32NumSector != 0 && g_pEngine->m_level->m_currentSector != static_cast<int32_t>(m_ui32NumSector) &&
        g_pEngine->m_timeManager->m_pTime->m_eCurrentState == 0) {
        m_baData &= 0xfffffff1u;
        return 0;
    }
    const CMultiGeometryBasic* shape = static_cast<const CMultiGeometryBasic*>(m_pGeometry);
    if ((shape->m_baData & 3) == 2) {
        // Each movable's move this frame (from its old position): forward crossings set bit 1, backward ones bit 3.
        uint8_t forward = 0;
        uint8_t backward = 0;
        for (const CKDetectedMovable::Entry* entry = m_pDetectedMovable->m_lMovables; entry != nullptr;
             entry = entry->m_pNext) {
            if (entry->m_bIsLoaded == 0 || entry->m_unk15 == 0) continue;
            const RwV3d& pos = MovablePosition(entry);
            const float now[3] = {pos.x, pos.y, pos.z};
            const float old[3] = {entry->m_v3OldPos.x, entry->m_v3OldPos.y, entry->m_v3OldPos.z};
            if (forward == 0) forward = MoveCrossesRectangle(shape, old, now);
            if (backward == 0) backward = MoveCrossesRectangle(shape, now, old);
        }
        m_baData = (m_baData & ~0xeu) | (static_cast<uint32_t>(forward) << 1) | (static_cast<uint32_t>(backward) << 3);
        return 1;
    }
    uint8_t inside = 0;
    if ((m_baData & 0x400) == 0) {
        // Any movable inside.
        for (const CKDetectedMovable::Entry* entry = m_pDetectedMovable->m_lMovables; entry != nullptr;
             entry = entry->m_pNext) {
            if (entry->m_bIsLoaded == 0 || entry->m_unk15 == 0) continue;
            if (ShapeHolds(shape, MovablePosition(entry)) != 0) {
                inside = 1;
                break;
            }
        }
    } else {
        // Every movable inside, and at least one.
        bool none = true;
        uint8_t outside = 0;
        for (const CKDetectedMovable::Entry* entry = m_pDetectedMovable->m_lMovables; entry != nullptr;
             entry = entry->m_pNext) {
            outside = 0;
            if (entry->m_bIsLoaded != 0 && entry->m_unk15 != 0) {
                outside = static_cast<uint8_t>(ShapeHolds(shape, MovablePosition(entry)) ^ 1);
                none = false;
            }
            if (outside != 0) break;
        }
        inside = outside == 0 && !none ? 1 : 0;
    }
    const uint8_t was = static_cast<uint8_t>(GetDetectionType(1));  // vt+0x54: bit 2 of the last call
    const uint32_t entered = inside != 0 && was == 0 ? 2u : 0u;
    const uint32_t left = inside == 0 && was != 0 ? 8u : 0u;
    m_baData = (m_baData & ~0xeu) | entered | (static_cast<uint32_t>(inside) << 2) | left;
    return 1;
}

// 0x001a8a78 CKDetectorBase_Destroy
void CKDetectorBase::Destroy() {
    m_pDetectedMovable = nullptr;
    m_pGeometry = nullptr;
}

// 0x001a89d8 CKDetectorBase_MessageProc
int32_t CKDetectorBase::MessageProc(uint16_t message, void* /*data*/) {
    uint32_t enabled = 1;
    if (message != 0x1100) {
        if (message != 0x1101) return 1;
        enabled = 0;
    }
    SetEnabled(enabled);  // vt+0x58
    return 0;
}

// 0x001a88f8 CKDetectorBase_SetDefaultState
void CKDetectorBase::SetDefaultState(int32_t flag) {
    if (flag != 0) return;
    SetEnabled((m_baData >> 5) & 1);  // vt+0x58
}

// 0x001a8658 CKDetectorBase_SetGameState: the state's byte +0x07 (the low byte of the big-endian state id word).
int32_t CKDetectorBase::SetGameState(const SApplyGameState* state) {
    if (state->m_ui32InfoId != 50000) return 0;
    const uint8_t value = static_cast<uint8_t>(state->m_ui32GameStateId & 0xff);
    if (value == 0) {
        SetEnabled(1);  // vt+0x58
        return 1;
    }
    if (value != 1) return 0;
    SetEnabled(0);
    return 1;
}

// 0x001a8978 CKDetectorBase_GetInfo
int32_t CKDetectorBase::GetInfo(IKInfo* info, int32_t request) {
    if (request != kGetInfoValueAccessor || info->m_ui32Id != 2) return 1;
    // 0x009aaf48 CKDetectorBase_GetTriggerProp2: bit 4 (enabled). The type word is the request (0: a byte).
    return AnswerInfo(info, [](IKSerializable* o, uint32_t) { return (static_cast<CKDetectorBase*>(o)->m_baData >> 4) & 1u; }, 0);
}

// 0x001a8a88 CKDetectorBase_Load
int32_t CKDetectorBase::Load(IKFile* file, int32_t type) {
    if (type != K_LEVEL_PLATEFORMS) return 1;
    ReadU32LE(file, &m_baData);
    IKFile_ReadRef(file, &m_pGeometry);
    IKFile_ReadRef(file, &m_pDetectedMovable);
    ReadU32LE(file, &m_ui32NumSector);
    SetEnabled((m_baData >> 5) & 1);  // a virtual call (vt+0x58)
    return 1;
}
