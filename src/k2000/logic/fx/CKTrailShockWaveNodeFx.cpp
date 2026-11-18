// CKTrailShockWaveNodeFx.cpp - reconstructed original translation unit: 0x572e48-0x5748c0 (GAME_TOC2, main_toc2), 22 functions, 20 live.
// Primary class: CKTrailShockWaveNodeFx  key 0x444c  category Logic  size ?  vtable 0xb2de90
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x572e48  CKTrailShockWaveNodeFx_Delete  (the Delete factory: DOTD_DECLARE_FACTORIES; port-rest R07)
//   [x] 0x572e98  CKTrailShockWaveNodeFx_Destroy  (Destroy (header, empty); port-rest R07)
//   [x] 0x572ea0  CKTrailShockWaveNodeFx_Start  (Vf64 (header); port-rest R07)
//   [ ] 0x572eb0  CKTrailShockWaveNodeFx_StopWhenAllParticleNodesEmpty_maybe  [dead]
//   [ ] 0x572f50  RegisterCKTrailShockWaveNodeFxClass
//   [ ] 0x572fc8  _GLOBAL__I_572fc8
//   [x] 0x572fd8  CKTrailShockWaveNodeFx_HideAndReleaseCollision_maybe  (HideAndReleaseCollision (no reference to its descriptor; inlined in Stop / Update); port-rest R07)
//   [x] 0x573100  CKTrailShockWaveNodeFx_PostLoad  (PostLoad; port-rest R07)
//   [x] 0x573140  CKTrailShockWaveNodeFx_RecursiveRegistration  (IKNodeFx::RecursiveRegistration (inherited); port-rest R07)
//   [x] 0x573168  CKTrailShockWaveNodeFx_Construct_2  (the same as 0x573280 Construct; port-rest R07)
//   [x] 0x5731e0  CKTrailShockWaveNodeFx_DeleteArray  (the DeleteArray factory: DOTD_DECLARE_FACTORIES; port-rest R07)
//   [x] 0x573280  CKTrailShockWaveNodeFx_Construct  (the constructor; port-rest R07)
//   [x] 0x5732f8  CKTrailShockWaveNodeFx_Load  (Load; port-rest R07)
//   [x] 0x5734f8  CKTrailShockWaveNodeFx_TriggerAt_maybe  (TriggerAt (no reference to its descriptor 0xbe5b60); port-rest R07)
//   [x] 0x573a30  CKTrailShockWaveNodeFx_CreateArray  (the CreateArray factory: DOTD_DECLARE_FACTORIES; port-rest R07)
//   [x] 0x573b48  CKTrailShockWaveNodeFx_Create  (the Create factory: DOTD_DECLARE_FACTORIES (the constructor inlined); port-rest R07)
//   [x] 0x573bd8  CKTrailShockWaveNodeFx_Destruct  (C++ destructor chain: vtable stores only; port-rest R07)
//   [ ] 0x573bf8  CKTrailShockWaveNodeFx_Save
//   [ ] 0x573e08  CKTrailShockWaveNodeFx_Destruct_2  [dead]
//   [x] 0x573e28  CKTrailShockWaveNodeFx_DeletingDestruct  (the destructor; delete; port-rest R07)
//   [x] 0x573e70  CKTrailShockWaveNodeFx_Stop  (Stop; port-rest R07)
//   [x] 0x573fd0  CKTrailShockWaveNodeFx_Update  (Update; port-rest R07)
//
//   [ ] 0x9cae10  CKTrailShockWaveNodeFx_IsKindOfClass  [inline]
//   [ ] 0x9cae48  CKTrailShockWaveNodeFx_GetClassType  [inline]
//   [ ] 0x9cae50  CKTrailShockWaveNodeFx_GetClassID  [inline]
//   [ ] 0x9cae58  CKTrailShockWaveNodeFx_GetFxData  [inline]
//   [ ] 0x9cae60  CKTrailShockWaveNodeFx_SetFxData  [inline]
#include "k2000/logic/fx/CKTrailShockWaveNodeFx.h"

#include "Renderware/rpprtstd/RpPrtStd.h"
#include "Renderware/rpprtstd/RpPrtStdRuntime.h"
#include "Renderware/rwcore/RwCamera.h"
#include "crt/ppc_ops.h"
#include "k2000/fx/UpdateParticleNodeSizeBoundingRadius.h"
#include "k2000/io/IKFile.h"
#include "k2000/logic/fx/CKTrailShockWaveFxData.h"
#include "k2000/misc/Engine.h"
#include <cmath>
#include "k2000/scenegraph/CKDynamicBoundingSphere.h"
#include "k2000/scenegraph/CParticlesNodeFx.h"
#include "k2000/scenegraph/CSGBranch.h"
#include "k2000/services/CKSrvCollision.h"
#include "k2000/system/IKTime.h"

namespace {
const CKTrailShockWaveFxData* Data(const IKSerializable* data) { return static_cast<const CKTrailShockWaveFxData*>(data); }
CKSrvCollision* Collision() { return static_cast<CKSrvCollision*>(g_pEngine->m_srvCollision); }  // engine +0x58
// 0x00010690 Math_Sqrtf (local copy, as CKShockWaveNodeFx.cpp): the double square root rounded to float.
float Math_Sqrtf(float x) { return static_cast<float>(std::sqrt(static_cast<double>(x))); }

// A node's frame placed at `p` (modelling position, flag 0x20000 cleared, RwFrame_MarkDirty 0x10698).
void PlaceNode(CParticlesNodeFx* node, const CVector3& p) {
    RwFrame* frame = node->m_pRwFrame;
    frame->modelling.pos.z = p.z;
    frame->modelling.pos.x = p.x;
    frame->modelling.pos.y = p.y;
    frame->modelling.flags &= 0xfffdffffu;
    RwFrame_MarkDirty(frame);
}

// One float of an emitter property, through its class's property table (the stores of Update).
void SetPropertyFloat(CParticlesNodeFx* node, int32_t offset, uint32_t byteOffset, float value) {
    *reinterpret_cast<float*>(reinterpret_cast<uint8_t*>(node->m_pRpPrtStdEmitter) + offset + byteOffset) = value;
}
}  // namespace

CKTrailShockWaveNodeFx::CKTrailShockWaveNodeFx() {
    m_GrdIn.m_MasksOfGrdForTest[0] = 1;
    m_GrdIn.m_MasksOfGrdForTest[1] = 8;
    m_GrdInOut.m_ui8SectorNumber = 0;
    m_GrdInOut.m_i32FaceIndex = -1;
    m_GrdInOut.m_eContactStatus = 3;
    m_GrdInOut.m_pGround = nullptr;
}

// 0x005732f8 CKTrailShockWaveNodeFx_Load
int32_t CKTrailShockWaveNodeFx::Load(IKFile* file, int32_t type) {
    IKNodeFx::Load(file, type);  // TocBridge_IKNodeFx_Load
    if (type != K_LEVEL_PLATEFORMS) return 1;
    IKFile_ReadRef(file, &m_apParticles[0]);
    IKFile_ReadRef(file, &m_apParticles[1]);
    IKFile_ReadRef(file, &m_apParticles[2]);
    ReadF32LE(file, &m_fRadius);  // one word, swapped
    return 1;
}

// 0x00573100 CKTrailShockWaveNodeFx_PostLoad
int32_t CKTrailShockWaveNodeFx::PostLoad(int32_t type) {
    IKNodeFx::PostLoad(type);  // TocBridge_IKNodeFx_PostLoad
    m_pSphere = nullptr;
    return 1;
}

// 0x00572fd8 CKTrailShockWaveNodeFx_HideAndReleaseCollision_maybe
void CKTrailShockWaveNodeFx::HideAndReleaseCollision() {
    for (CParticlesNodeFx* node : m_apParticles) {
        node->m_sgProperties &= 0xfff7fbffu;
        node->m_pRpPrtStdEmitter->flag &= 0xfffffff7u;  // the CBitArray rlwinm pair: the emit flag off
    }
    if (m_pSphere != nullptr) {
        IKBoundingVolume* sphere = reinterpret_cast<IKBoundingVolume*>(m_pSphere);
        if (sphere->m_pParent != nullptr) sphere->m_pParent->RemoveChild(sphere);  // vt+0x78
        Collision()->ReleaseDynSphere(sphere);  // TocBridge 0x00191a38
        m_pSphere = nullptr;
    }
    m_bDone = 1;
}

// 0x00573e70 CKTrailShockWaveNodeFx_Stop
void CKTrailShockWaveNodeFx::Stop() {
    m_baFxData = static_cast<uint8_t>((m_baFxData & 0xfe) | 1);
    HideAndReleaseCollision();
    m_apParticles[0]->StopEmitting();  // 0x000e6938 ParticleFxNode_StopEmitting_maybe
    m_apParticles[1]->StopEmitting();
    m_apParticles[2]->StopEmitting();
}

// 0x005734f8 CKTrailShockWaveNodeFx_TriggerAt_maybe (TOC2 -0x7578 0.0, -0x7584 1.0, -0x757c 0.5, -0x7580 0.001)
void CKTrailShockWaveNodeFx::TriggerAt(const IKSerializable* owner, const CVector3* start, const CVector3* direction) {
    if ((m_baFxData & 2) == 0 || m_pOwner != owner) return;
    const float zero = 0.0f;
    m_bDone = 0;
    m_v3Pos.x = start->x;
    m_v3Pos.y = start->y;
    m_v3Pos.z = start->z;
    float dy = direction->y;
    float dx = direction->x;
    float dz = direction->z;
    const float sx = start->x;
    const float sy = start->y;
    const float sz = start->z;
    const float len = Math_Sqrtf(ppc::fmadds(dz, dz, ppc::fmadds(dx, dx, dy * dy)));  // TocBridge 0x98fc10
    if (len != zero) {
        const float inv = 1.0f / len;
        dz = dz * inv;
        dx = dx * inv;
        dy = dy * inv;
    }
    const float spacing = Data(m_pFxData)->m_fSpacing;
    m_v3Target.z = ppc::fmadds(dz, spacing, sz);
    m_v3Target.x = ppc::fmadds(spacing, dx, sx);
    m_v3Target.y = ppc::fmadds(spacing, dy, sy);
    m_fSpeed = Data(m_pFxData)->m_unkFC;
    m_fMaxSpeed = Data(m_pFxData)->m_unk100;
    m_fAccel = Data(m_pFxData)->m_unk104;
    m_v3Start.x = start->x;
    m_v3Start.z = start->z;
    m_v3Start.y = start->y;
    for (CParticlesNodeFx* node : m_apParticles) {
        node->m_sgProperties &= 0xfffffffbu;  // shown
        PlaceNode(node, *start);
        node->m_sgProperties = (node->m_sgProperties | 0x400u) & 0xfff7ffffu;  // emitting, 0x80000 off
        node->m_fEmissionSpeedAdjustment = zero;
        node->m_pRpPrtStdEmitter->flag |= rpPRTSTDEMITTERFLAGACTIVE | rpPRTSTDEMITTERFLAGEMIT;  // 0xa
    }
    if (m_pSphere == nullptr) m_pSphere = static_cast<CKDynamicBoundingSphere*>(Collision()->AcquireDynSphere());
    if (m_pSphere != nullptr) {
        CKDynamicBoundingSphere* sphere = m_pSphere;
        sphere->m_fRadius = m_fRadius > zero ? m_fRadius : 0.001f;  // fcmpu / ble: a NaN takes 0.001
        sphere->m_ba8Infos = static_cast<uint8_t>(sphere->m_ba8Infos | 0x20u);
        sphere->m_ba8Infos = static_cast<uint8_t>(sphere->m_ba8Infos | 0x04u);
        sphere->m_ui8OwnerType = 0;
        sphere->m_ui16PropertiesFlags = 0;
        sphere->m_pOwner = Data(m_pFxData)->m_unk108;
        sphere->m_ui8OwnerType = Data(m_pFxData)->m_unk10e;
        sphere->m_ui16PropertiesFlags = static_cast<uint16_t>(Data(m_pFxData)->m_unk10c | sphere->m_ui16PropertiesFlags);
        if (sphere->m_pParent != nullptr) sphere->m_pParent->RemoveChild(sphere);  // vt+0x78
        m_apParticles[0]->AddChild(m_pSphere);  // vt+0x70
    }
    m_GrdIn.m_fDeltaMax = 0.5f;
    m_GrdIn.m_fObjectHeight = m_fRadius * 0.5f;
    m_GrdIn.m_MasksOfGrdForTest[0] = 1;
    m_GrdIn.m_MasksOfGrdForTest[1] = 8;
    m_GrdInOut.m_pGround = nullptr;
    m_GrdInOut.m_ui8SectorNumber = 0;
    m_GrdInOut.m_i32FaceIndex = -1;
    m_GrdInOut.m_eContactStatus = 3;
}

// 0x00573fd0 CKTrailShockWaveNodeFx_Update (TOC2 -0x7578 0.0, -0x7584 1.0)
void CKTrailShockWaveNodeFx::Update(IKTime* frameClock) {
    const float zero = 0.0f;
    if (m_bDone != 0) {
        // 0x005742c0: the emitters' live particle counts all 0 (the srawi / xor / subf zero tests)
        if (m_apParticles[2]->m_pRpPrtStdEmitter->prtActive == 0 && m_apParticles[0]->m_pRpPrtStdEmitter->prtActive == 0 &&
            m_apParticles[1]->m_pRpPrtStdEmitter->prtActive == 0) {
            Stop();  // vt+0x6c
        }
        return;
    }
    const float dt = frameClock->m_afDeltaTime[0];  // +0x1c
    if (!(m_v3Pos.x == m_v3Target.x && m_v3Pos.y == m_v3Target.y && m_v3Pos.z == m_v3Target.z)) {
        float speed = ppc::fmadds(dt, m_fAccel, m_fSpeed);
        m_fSpeed = speed;
        if (m_fAccel > zero) {
            if (speed > m_fMaxSpeed) {  // bgt
                speed = m_fMaxSpeed;
                m_fSpeed = speed;
            }
        } else if (m_fAccel < zero) {
            if (!(speed >= m_fMaxSpeed)) {  // bge: a NaN is clamped
                speed = m_fMaxSpeed;
                m_fSpeed = speed;
            }
        }
        const float step = dt * speed;
        float dy = m_v3Target.y - m_v3Pos.y;
        float dx = m_v3Target.x - m_v3Pos.x;
        float dz = m_v3Target.z - m_v3Pos.z;
        float len = Math_Sqrtf(ppc::fmadds(dz, dz, ppc::fmadds(dx, dx, dy * dy)));  // TocBridge 0x98fc10
        if (len != zero) {
            const float inv = 1.0f / len;
            dz = dz * inv;
            dx = dx * inv;
            dy = dy * inv;
        } else {
            len = zero;
        }
        if (len >= step) {  // bge
            m_v3Pos.x = ppc::fmadds(dx, step, m_v3Pos.x);
            m_v3Pos.y = ppc::fmadds(dy, step, m_v3Pos.y);
            m_v3Pos.z = ppc::fmadds(dz, step, m_v3Pos.z);
        } else {
            m_v3Pos.z = m_v3Target.z;
            m_v3Pos.x = m_v3Target.x;
            m_v3Pos.y = m_v3Target.y;
        }
    }
    CVector3 point = m_v3Pos;  // the probe point (r1 +0x70)
    const float px = point.x - m_v3Start.x;
    const float py = point.y - m_v3Start.y;
    const float pz = point.z - m_v3Start.z;
    const float progress =
        Math_Sqrtf(ppc::fmadds(pz, pz, ppc::fmadds(px, px, py * py))) / Data(m_pFxData)->m_fSpacing;  // fdivs
    Collision()->GroundProbePoints(&m_GrdIn, &m_GrdInOut, &point.x, 1);  // TocBridge 0x98fca0
    if (m_GrdInOut.m_eContactStatus > 1) {  // cmplwi / ble: off the ground
        HideAndReleaseCollision();
        return;
    }
    GroundContact_GetWorldPoint(&m_GrdInOut, &point);  // TocBridge 0x98fcb0
    const CKTrailShockWaveFxData* data = Data(m_pFxData);
    // The size property's eight floats in the original's order, each followed by the node's bounding radius.
    static const uint32_t kSizeOrder[8] = {0, 4, 2, 6, 1, 5, 3, 7};
    for (uint32_t j = 0; j < 3; ++j) {
        CParticlesNodeFx* node = m_apParticles[j];
        PlaceNode(node, point);
        const float* from = data->m_afParticleRanges[j][0];
        const float* to = data->m_afParticleRanges[j][1];
        for (uint32_t k : kSizeOrder) {
            node = m_apParticles[j];
            const float a = from[k];
            const float b = to[k];
            const int32_t offset =
                RpPrtStdPropTabGetPropOffset(node->m_pRpPrtStdEmitter->emtClass->propTab, rpPRTSTDPROPERTYCODEEMITTERPRTSIZE);
            if (offset != -1) SetPropertyFloat(node, offset, k * 4u, ppc::fmadds(progress, b - a, a));
            UpdateParticleNodeSizeBoundingRadius(node);  // TocBridge 0x98fcc0
        }
        // words 8 / 9: the standard property's (index 1) prtInitVel / prtInitVelBias (+0x50 / +0x54)
        node = m_apParticles[j];
        const int32_t standard = node->m_pRpPrtStdEmitter->emtClass->propTab->propOffset[1];
        SetPropertyFloat(node, standard, 0x50, ppc::fmadds(progress, to[8] - from[8], from[8]));
        SetPropertyFloat(node, standard, 0x54, ppc::fmadds(progress, to[9] - from[9], from[9]));
    }
    if (m_v3Pos.x != m_v3Target.x || m_v3Pos.y != m_v3Target.y || m_v3Pos.z != m_v3Target.z) return;
    HideAndReleaseCollision();  // at the target
}
