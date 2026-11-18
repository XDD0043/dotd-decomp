// CKCameraBeacon.cpp - reconstructed original translation unit 0x1512e0-0x152960 (GAME_TOC1, main_toc1), 23 functions, 23 live.
// Primary class: CKCameraBeacon  key 0x582  category Hook  size 0x54  vtable 0xb1a858
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [ ] 0x1512e0  RegisterCKCameraBeaconClass
//   [ ] 0x151358  _GLOBAL__I_151358
//   [x] 0x151368  CKCameraBeacon_QueueEnterLeaveSignals
//   [x] 0x1513b0  CKCameraBeacon_RecursiveRegistration
//   [x] 0x151470  CKCameraBeacon_Destroy
//   [x] 0x1514d0  CKCameraBeacon_Construct
//   [x] 0x151508  CKCameraBeacon_DeleteArray
//   [x] 0x1515a8  CKCameraBeacon_BaseDestructor  (C++ destructor chain)
//   [x] 0x1515d8  CKCameraBeacon_DeletingDestructor  (C++ deleting destructor)
//   [x] 0x151620  CKCameraBeacon_Destructor  (C++ destructor chain: vtable stores only)
//   [x] 0x151650  CKCameraBeacon_Construct_2  (the constructor, CKCameraBeacon.h)
//   [x] 0x151688  CKCameraBeacon_IsActiveBeaconPredicate_maybe  (GetInfo's accessor)
//   [x] 0x1516c8  CKCameraBeacon_GetInfo
//   [x] 0x151740  CKCameraBeacon_vfC0  (no caller of the KBase4C2 vt+0xc0 found, raw vcall scan)
//   [x] 0x151c38  CKCameraBeacon_CreateArray
//   [x] 0x151ce8  CKCameraBeacon_Create
//   [x] 0x151d40  CKCameraBeacon_Load
//   [~] 0x152040  CKCameraBeacon_vfC4  (STUB(C2.8))
//   [ ] 0x1522e8  CKCameraBeacon_Save
//   [x] 0x152628  CKCameraBeacon_MessageProc
//   [x] 0x152800  CKCameraBeacon_SetGameState
//   [x] 0x152858  CKCameraBeacon_PostLoad
//   [x] 0x152920  CKCameraBeacon_SetDefaultState
//
//   [ ] 0x9a7ad0  CKCameraBeacon_IsKindOfClass  [inline]
//   [ ] 0x9a7b28  CKCameraBeacon_GetClassType  [inline]
//   [ ] 0x9a7b30  CKCameraBeacon_GetClassID  [inline]
//   [ ] 0x9a7b38  CKCameraBeacon_IsNodePriority22Greater_maybe  [inline]
#include "k2000/hooks/CKCameraBeacon.h"

#include <cstring>

#include "k2000/core/Stub.h"
#include "k2000/cameras/CKSrvCamera.h"
#include "k2000/core/IKInfo.h"
#include "k2000/io/IKFile.h"
#include "k2000/misc/Engine.h"
#include "Renderware/rwcore/RwCamera.h"
#include "k2000/system/IKTime.h"
#include "k2000/scenegraph/CSGBranch.h"
#include "k2000/misc/Mat4.h"
#include "k2000/math/Vec3.h"
#include "k2000/math/CBBox.h"
#include "k2000/logic/CMultiGeometryBasic.h"

// 0x00151d40 CKCameraBeacon_Load
int32_t CKCameraBeacon::Load(IKFile* file, int32_t type) {
    KBase4C2::Load(file, type);
    if (type != K_LEVEL_PLATEFORMS) return 1;
    ReadU8(file, &m_unk21);
    ReadU8(file, &m_unk22);
    IKFile_ReadRef(file, &m_unk24);
    uint32_t w[3];
    ReadU32LEWords(file, w, 3);  // one 12-byte read, each word swapped
    std::memcpy(&m_unk28, w, sizeof(w));
    ReadF32LE(file, &m_unk34);
    ReadU8(file, &m_unk23);
    ReadF32LE(file, &m_unk3C);
    m_unk44.Load(file, K_LEVEL_PLATEFORMS);
    m_unk4C.Load(file, K_LEVEL_PLATEFORMS);
    ReadF32LE(file, &m_unk38);
    return 1;
}

// 0x00151368 CKCameraBeacon_QueueEnterLeaveSignals (the beacon is passed on as the signals' sender, r4; the native
// QueueTriggerSignals takes the starter only).
void CKCameraBeacon_FireEnterLeaveSignals(CKCameraBeacon* beacon, int32_t enter) {
    QueueTriggerSignals(enter != 0 ? &beacon->m_unk44 : &beacon->m_unk4C);
}

// ---- C2.8 port-all P16 ----

// 0x00151470 CKCameraBeacon_Destroy
void CKCameraBeacon::Destroy() {
    KBase4C2::Destroy();      // 0x001dfb98 (empty)
    m_unk24->Destroy();       // vt+0x10
    m_unk24 = nullptr;
}

// 0x001513b0 CKCameraBeacon_RecursiveRegistration
void CKCameraBeacon::RecursiveRegistration(int32_t type) {
    KBase4C2::RecursiveRegistration(type);  // 0x001dfc30 (IKHook's)
    if (type == 0) m_unk24->RecursiveRegistration(0);
    // 0x002361b0 KStub_Return1 for +0x44 and +0x4c (the trigger starters register nothing).
}

namespace {
// The camera service's held beacon: +0x920 while +0x915 is set, else none.
IKSerializable* HeldBeacon() {
    const CKSrvCamera* camera = static_cast<const CKSrvCamera*>(g_pEngine->m_srvCamera);  // engine +0x70
    return camera->m_bUnk915 != 0 ? camera->m_pUnk920 : nullptr;
}
}  // namespace

// 0x00152628 CKCameraBeacon_MessageProc
int32_t CKCameraBeacon::MessageProc(uint16_t message, void* /*data*/) {
    if (message == 0x700) {
        m_unk20 = static_cast<uint8_t>((m_unk20 & 0xfe) | 1);
        return 0;
    }
    if (message != 0x701) return 1;
    m_unk20 = static_cast<uint8_t>(m_unk20 & 0xf8);
    CKSrvCamera* camera = static_cast<CKSrvCamera*>(g_pEngine->m_srvCamera);
    // BUG(original): without a held beacon the node of a null beacon is read; `this` is never null, so that path
    // returns first.
    if (camera->m_bUnk915 == 0) return 0;
    if (camera->m_pUnk920 != this) return 0;
    const uint32_t count = camera->m_ui32NbStacked;
    if (count == 0) return 0;
    uint32_t index = 0;
    while (camera->m_aStack[index].m_pTarget != m_pKGLObject) {
        index = (index + 1) & 0xff;
        if (count <= index) return 0;
    }
    const uint32_t last = count - 1;
    camera->m_ui32NbStacked = last;
    if (last != index) camera->m_aStack[index] = camera->m_aStack[last];
    camera->m_baTemporaryFlags = (camera->m_baTemporaryFlags & 0xff7fffffu) | 0x800000u;
    return 0;
}

// 0x00152858 CKCameraBeacon_PostLoad: IKLife's, then (type 0) the flag byte from +0x21 bit 0; the starters' PostLoad.
int32_t CKCameraBeacon::PostLoad(int32_t type) {
    PostLoadLife(type);  // 0x00019f68
    if (type == 0) {
        m_unk20 = 0;
        const uint8_t flags = m_unk20;
        const uint8_t on = static_cast<uint8_t>(m_unk21 & 1);
        m_unk20 = static_cast<uint8_t>((flags & 0xfe) | on);
        if (on == 0) m_unk20 = static_cast<uint8_t>(flags & 0xf8);
    }
    m_unk44.PostLoad(type);  // 0x00236330
    m_unk4C.PostLoad(type);
    return 1;
}

// 0x00152920 CKCameraBeacon_SetDefaultState: PostLoad's flag step for a zero flag.
void CKCameraBeacon::SetDefaultState(int32_t flag) {
    if (flag != 0) return;
    m_unk20 = 0;
    const uint8_t flags = m_unk20;
    const uint8_t on = static_cast<uint8_t>(m_unk21 & 1);
    m_unk20 = static_cast<uint8_t>((flags & 0xfe) | on);
    if (on != 0) return;
    m_unk20 = static_cast<uint8_t>(flags & 0xf8);
}

// 0x00152800 CKCameraBeacon_SetGameState
int32_t CKCameraBeacon::SetGameState(const SApplyGameState* state) {
    if (state->m_ui32GameStateId == 0) {
        m_unk20 = static_cast<uint8_t>((m_unk20 & 0xfe) | 1);
        return 1;
    }
    if (state->m_ui32GameStateId != 1) return 1;
    m_unk20 = static_cast<uint8_t>(m_unk20 & 0xf8);
    return 1;
}

// 0x001516c8 CKCameraBeacon_GetInfo, with 0x00151688 CKCameraBeacon_IsActiveBeaconPredicate_maybe
int32_t CKCameraBeacon::GetInfo(IKInfo* info, int32_t request) {
    if (request != kGetInfoValueAccessor || info->m_ui32Id != 1) return 1;
    return AnswerInfo(info, [](IKSerializable* o, uint32_t) { return HeldBeacon() == o ? 1u : 0u; }, 0);
}

// 0x00152040 CKCameraBeacon_vfC4. STUB(C2.8): not ported (see the header); never in view.
uint8_t CKCameraBeacon::IsInView(const void* /*frustum*/) {
    DOTD_STUB_ONCE("CKCameraBeacon_vfC4 0x152040: the camera beacon's view test (C2.8)");
    return 0;
}

// 0x00151740 CKCameraBeacon_vfC0 (the KBase4C2 slot vt+0xc0; no caller of it is known, raw vcall scan): with +0x21 bit 1
// the geometry (+0x24) follows the node's parent (a box: its centre +0x28 through the parent's world matrix, its half
// sizes kept; a sphere: its centre). An enabled beacon (+0x20 bit 0) joins the camera service's beacon list (+0x930,
// highest priority +0x22 first, after the beacons of a higher priority; not twice); bit 1 keeps the last frame's
// "holds the focus" (bit 2), which is then tested again against the focus copy (+0x490). While it holds the focus the
// time +0x40 runs (frame clock running, up to +0x3c); a beacon that starts holding it restarts the time. A disabled
// beacon clears bits 1 and 2.
void CKCameraBeacon::VfC0(IKTime* clock) {
    KBase4C2::VfC0(clock);  // 0x001dfbc8 (empty)
    CKSrvCamera* srv = static_cast<CKSrvCamera*>(g_pEngine->m_srvCamera);  // engine +0x70
    CMultiGeometryBasic* geometry = static_cast<CMultiGeometryBasic*>(m_unk24);
    if (((m_unk21 >> 1) & 1u) != 0) {
        const uint32_t shape = geometry->m_baData & 3u;
        const CMatrix34* parentLtm =
            reinterpret_cast<const CMatrix34*>(FrameLtm(static_cast<CSGLeaf*>(m_pKGLObject)->m_pParent->m_pRwFrame));
        if (shape == 0) {
            CVector3 center;
            Mat4_TransformPoints(parentLtm, &center, &m_unk28, 1);  // 0x0023f7e8
            CBBox* box = reinterpret_cast<CBBox*>(geometry->m_afShape);
            const float half = 0.5f;  // TOC1 -0x39fc
            CVector3 extent;
            extent.x = (box->m_sup.x - box->m_inf.x) * half;
            extent.y = (box->m_sup.y - box->m_inf.y) * half;
            extent.z = (box->m_sup.z - box->m_inf.z) * half;
            BBox_SetFromCenterExtents(box, &center, &extent);  // 0x0023d550
        } else if (shape == 1) {
            CVector3 center;
            Mat4_TransformPoints(parentLtm, &center, &m_unk28, 1);
            geometry->m_afShape[2] = center.z;
            geometry->m_afShape[0] = center.x;
            geometry->m_afShape[1] = center.y;
        }
    }
    if ((m_unk20 & 1u) == 0) {
        m_unk20 = static_cast<uint8_t>(m_unk20 & 0xf8u);  // bits 1 and 2 cleared (bit 0 is clear)
        return;
    }
    // The beacon list, by priority (+0x22, highest first); CKCameraBeacon_IsNodePriority22Greater_maybe 0x9a7b38.
    CKSrvCamera::CameraNode* head = srv->m_pUnk930;
    bool listed = false;
    for (CKSrvCamera::CameraNode* n = head; n != nullptr; n = n->m_pNext) {
        if (n->m_pObject == this) {
            listed = true;
            break;
        }
    }
    if (!listed) {
        auto greater = [this](const CKSrvCamera::CameraNode* n) {
            return static_cast<CKCameraBeacon*>(n->m_pObject)->m_unk22 > m_unk22;  // cmplw / bgt
        };
        CKSrvCamera::CameraNode* node = new CKSrvCamera::CameraNode;  // FreeListPool 0x00ceaa30 (Grow when empty)
        node->m_pObject = this;
        if (head == nullptr || !greater(head)) {
            node->m_pNext = head;  // in front
            srv->m_pUnk930 = node;
        } else {
            CKSrvCamera::CameraNode* after = head;
            while (after->m_pNext != nullptr && greater(after->m_pNext)) after = after->m_pNext;
            node->m_pNext = after->m_pNext;
            after->m_pNext = node;
        }
    }
    // Bit 1 = the previous bit 2, then bit 2 = the focus copy (+0x490) inside the geometry.
    uint8_t flags = m_unk20;
    flags = static_cast<uint8_t>((flags & ~2u) | (((flags >> 2) & 1u) << 1));
    m_unk20 = flags;
    const uint32_t shape = geometry->m_baData & 3u;
    const CVector3& p = srv->m_v3FocusPosCopy;
    uint32_t inside = 0;
    if (shape == 0) {
        const CBBox* box = reinterpret_cast<const CBBox*>(geometry->m_afShape);
        // cror lt|eq / gt|eq: a NaN fails each bound.
        if (box->m_inf.x <= p.x && box->m_sup.x >= p.x && box->m_inf.z <= p.z && box->m_sup.z >= p.z &&
            box->m_inf.y <= p.y) {
            inside = p.y <= box->m_sup.y ? 1u : 0u;
        }
    } else if (shape == 1) {
        inside = static_cast<uint32_t>(Vec3_IsWithinRadius(geometry->m_afShape[3], geometry->m_afShape[4],
                                                           geometry->m_afShape, &p.x)) & 0xffu;  // 0x002441e8
    }
    m_unk20 = static_cast<uint8_t>((m_unk20 & ~4u) | ((inside << 2) & 0xfcu));
    const uint8_t now = m_unk20;
    if (((now >> 1) & 1u) == 0) {
        if ((now & 4u) != 0) m_fUnk40 = 0.0f;  // stw 0: it starts holding the focus
        return;
    }
    if ((now & 4u) == 0) return;
    if (clock->m_eCurrentState != 0) return;
    if (!(m_unk3C > m_fUnk40)) return;  // ble: a NaN stops
    m_fUnk40 = clock->m_afDeltaTime[0] + m_fUnk40;
}
