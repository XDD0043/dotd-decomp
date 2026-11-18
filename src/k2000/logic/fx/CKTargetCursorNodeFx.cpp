// CKTargetCursorNodeFx.cpp - reconstructed original translation unit 0x1d57b8-0x1d7298 (GAME_TOC1, main_toc1), 23 functions, 18 live.
// Primary class: CKTargetCursorNodeFx  key 0x460c  category Logic  size 0x38  vtable 0xb1da88
// Other owners: StopOwnedEffectWithFadeOut (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x1d57b8  CKTargetCursorNodeFx_Delete
//   [x] 0x1d5808  CKTargetCursorNodeFx_RecursiveRegistration
//   [ ] 0x1d5860  FUN_001d5860  [dead]
//   [ ] 0x1d58e0  FUN_001d58e0  [dead]
//   [x] 0x1d5988  CKTargetCursorNodeFx_StopForOwner_maybe
//   [ ] 0x1d5a50  CKTargetCursorNodeFx_SetAlpha_maybe  [dead]
//   [ ] 0x1d5bc0  RegisterCKTargetCursorNodeFxClass
//   [ ] 0x1d5c38  _GLOBAL__I_1d5c38
//   [x] 0x1d5c48  CKTargetCursorNodeFx_PostLoad
//   [x] 0x1d5ca0  CKTargetCursorNodeFx_Load
//   [ ] 0x1d5d60  CKTargetCursorNodeFx_Save
//   [x] 0x1d5d88  CKTargetCursorNodeFx_Destroy
//   [x] 0x1d5dc8  CKTargetCursorNodeFx_DeleteArray
//   [x] 0x1d5e70  CKTargetCursorNodeFx_Create
//   [x] 0x1d5ec8  CKTargetCursorNodeFx_SetPositionForOwner_maybe
//   [x] 0x1d5fa0  CKTargetCursorNodeFx_Stop
//   [ ] 0x1d5fe0  FUN_001d5fe0  [dead]
//   [ ] 0x1d6020  FUN_001d6020  [dead]
//   [x] 0x1d60f0  CKTargetCursorNodeFx_CreateArray
//   [x] 0x1d61a8  CKTargetCursorNodeFx_SetupCursorStateForOwner_maybe
//   [x] 0x1d63d8  CKTargetCursorNodeFx_Start
//   [x] 0x1d6640  CKTargetCursorNodeFx_Update
//   [x] 0x1d7190  StopOwnedEffectWithFadeOut_maybe
//
//   [ ] 0x9ad590  CKTargetCursorNodeFx_IsKindOfClass  [inline]
//   [x] 0x9ad5c8  CKTargetCursorNodeFx_GetClassType  [inline]
//   [x] 0x9ad5d0  CKTargetCursorNodeFx_GetClassID  [inline]
//   [x] 0x9ad5d8  CKTargetCursorNodeFx_GetFxData  [inline]
//   [x] 0x9ad5e0  CKTargetCursorNodeFx_SetFxData  [inline]
//   [ ] 0x9ad5e8  CKTargetCursorNodeFx_Destruct  [inline]
//   [ ] 0x9ad608  CKTargetCursorNodeFx_DeletingDestruct  [inline]
#include "k2000/logic/fx/CKTargetCursorNodeFx.h"
#include "k2000/logic/CKSavingManager.h"

#include <cmath>
#include <cstring>

#include "Renderware/rwcore/RwCamera.h"
#include "crt/ppc_ops.h"
#include "k2000/cameras/CKSrvCamera.h"
#include "k2000/cameras/CameraContext.h"
#include "k2000/geometry/CGeometry.h"
#include "k2000/io/IKFile.h"
#include "k2000/logic/fx/CKTargetCursorFxData.h"
#include "k2000/logic/render/CMaterial.h"
#include "k2000/managers/CKGraphic.h"
#include "k2000/misc/Engine.h"
#include "k2000/misc/Mat4.h"
#include "k2000/render/CRenderer.h"
#include "k2000/scenegraph/CNode.h"
#include "k2000/system/IKTime.h"
#include "platform/fps.h"

namespace {

// 0x00c50d40: the shared +y axis (zero in the EBOOT's BSS; a static initialiser fills it).
const CVector3 kAxisY = {0.0f, 1.0f, 0.0f};

// 0x00010690 Math_Sqrtf (fsqrts).
inline float Sqrtf(float x) { return std::sqrt(x); }

CKTargetCursorFxData* DataOf(const CKTargetCursorNodeFx* fx) { return static_cast<CKTargetCursorFxData*>(fx->m_pFxData); }

// The cursor geometries' alpha (inlined in SetupCursorStateForOwner and Update): 0xff opaque for all; another alpha with
// blending (render flag 11), opaque without it for a material of modes 1..6 with render flag 12.
void ApplyCursorAlpha(CNode* node, uint8_t alpha) {
    for (CGeometry* geometry = static_cast<CGeometry*>(node->m_lGeometryList); geometry != nullptr;
         geometry = geometry->m_pNext) {
        uint32_t blended = 0;
        uint8_t value = alpha;
        if (alpha != 0xff) {
            blended = 1;
            if ((geometry->m_BitProperties & 0x1000u) != 0) {
                const uint32_t mode = (static_cast<CMaterial*>(geometry->m_pMaterial)->m_baProperties >> 3) & 0xfu;
                if (mode > 0 && mode <= 6) {
                    blended = 0;
                    value = 0xff;
                }
            }
        }
        geometry->m_cGeometryColor[3] = value;
        const uint32_t flags = geometry->m_BitProperties;
        if (((flags >> 11) & 1u) != blended) {
            geometry->m_BitProperties = (flags & 0xfffff7ffu) | (blended << 11);
            geometry->UpdateProperties();  // vt+0x60
        }
    }
}

}  // namespace

// 0x009ad5d8 CKTargetCursorNodeFx_GetFxData / 0x009ad5e0 CKTargetCursorNodeFx_SetFxData
IKFxData* CKTargetCursorNodeFx::GetFxData() { return reinterpret_cast<IKFxData*>(m_pFxData); }
void CKTargetCursorNodeFx::SetFxData(IKFxData* data) { m_pFxData = reinterpret_cast<IKSerializable*>(data); }

// 0x001d5fa0 CKTargetCursorNodeFx_Stop
void CKTargetCursorNodeFx::Stop() {
    m_baFxData = static_cast<uint8_t>((m_baFxData & 0xfe) | 1);
    if (m_pCursorNode == nullptr) return;
    m_pCursorNode->m_sgProperties = (m_pCursorNode->m_sgProperties & 0xfffffffbu) | 4u;
}

// 0x001d61a8 CKTargetCursorNodeFx_SetupCursorStateForOwner_maybe
void CKTargetCursorNodeFx::SetupCursorStateForOwner(const IKSerializable* owner) {
    if ((m_baFxData & 2) == 0 || m_pOwner != owner || m_pCursorNode == nullptr) return;
    m_baFxData = static_cast<uint8_t>(m_baFxData & 0xf7);
    m_fAngle = 0.0f;
    const CKTargetCursorFxData* data = DataOf(this);
    m_fPhaseTime = data->m_unk08;
    if (m_fPhaseTime == 0.0f) {
        m_baFxData = static_cast<uint8_t>(m_baFxData & 0xfb);
        data = DataOf(this);
        m_ui8Alpha = data->m_unk34;
        m_fScale = data->m_unk28;
        m_baFxData = static_cast<uint8_t>((m_baFxData & 0xdf) | 0x20);
        m_baFxData = static_cast<uint8_t>((m_baFxData & 0xef) | 0x10);
    } else {
        m_baFxData = static_cast<uint8_t>((m_baFxData & 0xfb) | 4);
        data = DataOf(this);
        m_ui8Alpha = data->m_unk10[0];
        m_fScale = data->m_unk14;
    }
    ApplyCursorAlpha(m_pCursorNode, m_ui8Alpha);
}

// 0x001d63d8 CKTargetCursorNodeFx_Start. Reserved and running (Start keeps bit 1 set), the cursor shown and set up for
// the owner, the placement matrix the identity, bit 6 cleared; then the cursor's render stages as the input icon's
// (on the screen with data +0x5c / +0x5f, world stage 0xf).
void CKTargetCursorNodeFx::Vf64() {
    m_baFxData = static_cast<uint8_t>(((m_baFxData & 0xfd) | 2) & 0xfe);
    if (m_pCursorNode != nullptr) {
        m_pCursorNode->m_sgProperties &= 0xfffffffbu;
        SetupCursorStateForOwner(m_pOwner);
    }
    CMatrix34* m = m_pMatrix1c;
    m->m_pos.x = 0.0f;  // stw 0 (the eleven zero words)
    m->m_up.x = 0.0f;
    m->m_right.z = 0.0f;
    m->m_right.y = 0.0f;
    m->m_at.y = 0.0f;
    m->m_at.x = 0.0f;
    m->m_up.z = 0.0f;
    m->m_pos.z = 0.0f;
    m->m_pos.y = 0.0f;
    m->m_ui32Flags = 0x20003;
    m->m_right.x = 1.0f;
    m->m_at.z = 1.0f;
    m->m_up.y = 1.0f;
    m_baFxData = static_cast<uint8_t>(m_baFxData & 0xbf);
    uint32_t onScreen = 0;
    uint32_t stage32 = 0;
    uint32_t stage31 = 0;
    const CKTargetCursorFxData* data = DataOf(this);
    if (data != nullptr) {
        onScreen = 1;
        if (data->m_unk5c == 0) onScreen = data->m_unk5f != 0 ? 1u : 0u;
        stage32 = data->m_unk5e != 0 ? 1u : 0u;
        stage31 = data->m_unk5d != 0 ? 1u : 0u;
    }
    CNode* node = m_pCursorNode;
    if (node == nullptr) return;
    for (CGeometry* geometry = static_cast<CGeometry*>(node->m_lGeometryList); geometry != nullptr;
         geometry = geometry->m_pNext) {
        uint32_t flags = geometry->m_BitProperties;
        if (((flags >> 17) & 1u) != onScreen) {
            geometry->m_BitProperties = (flags & 0xfffdffffu) | (onScreen << 17);
            geometry->UpdateProperties();  // vt+0x60
            flags = geometry->m_BitProperties;
        }
        if (onScreen == 0) {
            geometry->m_BitProperties = (flags & 0xffffffe0u) | 0xfu;
        } else if (stage32 != 0) {
            geometry->m_BitProperties = (flags & 0xffffffe0u) | 0x12u;
        } else if (stage31 != 0) {
            geometry->m_BitProperties = (flags & 0xffffffe0u) | 0x14u;
        } else {
            geometry->m_BitProperties = (flags & 0xffffffe0u) | 0x11u;
        }
        geometry->m_BitProperties = (geometry->m_BitProperties & 0xffffffdfu) | 0x20u;
    }
    node->SetFlag10Bit5ResetField20To1(onScreen);  // 0x000cc808
}

// 0x001d6640 CKTargetCursorNodeFx_Update. The phase: appearing (alpha and scale from the data's start values, +0x10 /
// +0x14, to its idle ones over data +0x08 seconds; at its end the directions chosen), disappearing (from the stop values
// to the data's end values +0x12 / +0x1c over data +0x0c seconds, then stopped) or idle (alpha between data +0x34 and
// +0x35 at data +0x38 per second, scale between +0x28 and +0x2c at +0x30 per second, back and forth); the roll turns at
// the phase's rate (+0x20 / +0x24 / +0x3c). The cursor's matrix: the placement matrix (facing the camera unless bit 6
// or data +0x5f), rolled, scaled (times the distance factor data +0x50..+0x58 between distances +0x4c and +0x54), then
// turned toward the camera and offset by data +0x40; the alpha applied when it changed; data +0x5f puts it on the
// screen at the projected point.
void CKTargetCursorNodeFx::Update(IKTime* frameClock) {
    const float dt = frameClock->m_afDeltaTime[0];
    if (m_pCursorNode == nullptr) return;
    const uint8_t oldAlpha = m_ui8Alpha;
    CKTargetCursorFxData* data;
    if ((m_baFxData & 4) != 0) {
        float t = m_fPhaseTime - dt;
        m_fPhaseTime = t;
        if (t < 0.0f || t == 0.0f) {
            data = DataOf(this);
            if (data->m_unk28 > m_fScale || data->m_unk28 == m_fScale) {
                m_baFxData = static_cast<uint8_t>((m_baFxData & 0xef) | 0x10);
            } else if (data->m_unk2c < m_fScale || data->m_unk2c == m_fScale) {
                m_baFxData = static_cast<uint8_t>(m_baFxData & 0xef);
            } else {
                const uint32_t grows = (data->m_unk14 < data->m_unk18 || data->m_unk14 == data->m_unk18) ? 1u : 0u;
                m_baFxData = static_cast<uint8_t>((m_baFxData & 0xef) | (grows << 4));
            }
            // BUG(original): the alpha's direction is written to bit 4 (the scale's) as well, not bit 5.
            data = DataOf(this);
            const uint8_t alpha = m_ui8Alpha;
            if (!(data->m_unk34 < alpha)) {
                m_baFxData = static_cast<uint8_t>((m_baFxData & 0xef) | 0x10);
            } else if (!(data->m_unk35 > alpha)) {
                m_baFxData = static_cast<uint8_t>(m_baFxData & 0xef);
            } else {
                const uint32_t grows = data->m_unk10[0] <= data->m_unk10[1] ? 1u : 0u;
                m_baFxData = static_cast<uint8_t>((m_baFxData & 0xef) | (grows << 4));
            }
            m_fPhaseTime = 0.0f;
            m_baFxData = static_cast<uint8_t>(m_baFxData & 0xfb);
            t = m_fPhaseTime;
        }
        data = DataOf(this);
        const float angle = m_fAngle;
        const float k = t / data->m_unk08;
        const float rest = 1.0f - k;
        m_ui8Alpha = static_cast<uint8_t>(ppc::fctiwz(
            ppc::fmadds(k, static_cast<float>(data->m_unk10[0]), rest * static_cast<float>(data->m_unk10[1]))));
        m_fScale = ppc::fmadds(k, data->m_unk14, rest * data->m_unk18);
        m_fAngle = ppc::fmadds(dt, data->m_unk20, angle);
    } else if ((m_baFxData & 8) != 0) {
        float t = m_fPhaseTime - dt;
        m_fPhaseTime = t;
        if (t < 0.0f || t == 0.0f) {
            m_fPhaseTime = 0.0f;
            m_baFxData = static_cast<uint8_t>(m_baFxData & 0xf7);
            Stop();  // vt+0x6c
            t = m_fPhaseTime;
        }
        data = DataOf(this);
        const float stopScale = m_fStopScale;
        const float angle = m_fAngle;
        const float k = t / data->m_unk0c;
        const float rest = 1.0f - k;
        m_ui8Alpha = static_cast<uint8_t>(ppc::fctiwz(
            ppc::fmadds(k, static_cast<float>(m_ui8StopAlpha), rest * static_cast<float>(data->m_unk10[2]))));
        m_fScale = ppc::fmadds(k, stopScale, rest * data->m_unk1c);
        m_fAngle = ppc::fmadds(dt, data->m_unk24, angle);
    } else {
        data = DataOf(this);
        const float alphaStep = dt * data->m_unk38;
        int32_t wholeStep = ppc::fctiwz(alphaStep);
        // --fps N (not in the original): the whole steps of this frame's 60 Hz frames, so the pulse keeps its speed.
        if (dotd::fps::Unlocked()) wholeStep = static_cast<int32_t>(dotd::fps::TruncSteps(data->m_unk38, dt));
        const uint8_t low = data->m_unk34;
        const uint8_t high = data->m_unk35;
        if ((m_baFxData & 0x20) != 0) {
            const uint8_t alpha = static_cast<uint8_t>(wholeStep + oldAlpha);
            m_ui8Alpha = alpha;
            if (!(high > alpha)) {
                m_ui8Alpha = high;
                m_baFxData = static_cast<uint8_t>(m_baFxData & 0xdf);
            }
        } else {
            const uint8_t alpha = static_cast<uint8_t>(oldAlpha - wholeStep);
            m_ui8Alpha = alpha;
            if (!(low < alpha)) {
                m_ui8Alpha = low;
                m_baFxData = static_cast<uint8_t>((m_baFxData & 0xdf) | 0x20);
            }
        }
        data = DataOf(this);
        const float scaleStep = dt * data->m_unk30;
        const float smallest = data->m_unk28;
        const float largest = data->m_unk2c;
        if ((m_baFxData & 0x10) != 0) {
            m_fScale = scaleStep + m_fScale;
            if (largest < m_fScale || largest == m_fScale) {
                m_fScale = largest;
                m_baFxData = static_cast<uint8_t>(m_baFxData & 0xef);
            }
        } else {
            m_fScale = m_fScale - scaleStep;
            if (smallest > m_fScale || smallest == m_fScale) {
                m_fScale = smallest;
                m_baFxData = static_cast<uint8_t>((m_baFxData & 0xef) | 0x10);
            }
        }
        data = DataOf(this);
        m_fAngle = ppc::fmadds(dt, data->m_unk3c, m_fAngle);
    }
    data = DataOf(this);
    float distanceScale = data->m_unk50;
    CKSrvCamera* cameraService = static_cast<CKSrvCamera*>(g_pEngine->m_srvCamera);
    if (data->m_unk58 != data->m_unk50) {
        const CVector3& camera = cameraService->m_v3RealPos;
        const CVector3& placed = m_pMatrix1c->m_pos;
        const float ey = placed.y - camera.y;
        const float ex = placed.x - camera.x;
        const float ez = placed.z - camera.z;
        const float distance = Sqrtf(ppc::fmadds(ez, ez, ppc::fmadds(ex, ex, ey * ey)));
        data = DataOf(this);
        if (distance < data->m_unk4c || distance == data->m_unk4c) {
            distanceScale = data->m_unk50;
        } else if (distance > data->m_unk54 || distance == data->m_unk54) {
            distanceScale = data->m_unk58;
        } else {
            distanceScale = data->m_unk50 + ((data->m_unk58 - data->m_unk50) * (distance - data->m_unk4c)) /
                                                (data->m_unk54 - data->m_unk4c);
        }
    }
    CMatrix34 m = *m_pMatrix1c;
    data = DataOf(this);
    if ((m_baFxData & 0x40) == 0 && (data == nullptr || data->m_unk5f == 0)) {
        const CVector3& axisZ = cameraService->m_v3RealAxisZ;
        const CVector3 at = {axisZ.x, axisZ.y, axisZ.z};
        CVector3 right = {axisZ.z, 0.0f, -axisZ.x};
        const float length = Sqrtf(ppc::fmadds(right.z, right.z, ppc::fmadds(axisZ.z, axisZ.z, 0.0f)));
        if (length == 0.0f) {
            right.x = at.y;
            right.z = 0.0f;
            right.y = -at.x;
        } else {
            const float inverse = 1.0f / length;
            right.z = right.z * inverse;
            right.x = right.x * inverse;
            right.y = right.y * inverse;
        }
        Mat4_SetBasisFromAtRight(&m, &at, &right);  // 0x0023fe58
    }
    Mat4_RotateLocalZDeg(m_fAngle, &m);  // 0x002419c0
    const float size = distanceScale * m_fScale;
    m.m_right.x = size * m.m_right.x;
    m.m_right.y = size * m.m_right.y;
    m.m_right.z = size * m.m_right.z;
    m.m_up.x = size * m.m_up.x;
    m.m_up.y = size * m.m_up.y;
    m.m_up.z = size * m.m_up.z;
    m.m_at.x = size * m.m_at.x;
    m.m_at.z = size * m.m_at.z;
    m.m_at.y = size * m.m_at.y;
    m.m_ui32Flags &= 0xfffdfffeu;
    m_pCursorNode->SetLocalMatrix(reinterpret_cast<const RwMatrix*>(&m));  // 0x000d0be8
    m_pCursorNode->ForceWorldMatrixUpdate();  // vt+0x50
    const RwV3d& position = m_pCursorNode->m_pRwFrame->modelling.pos;
    const float pz = position.z;
    const float px = position.x;
    const float py = position.y;
    const CVector3& camera = static_cast<CKSrvCamera*>(g_pEngine->m_srvCamera)->m_v3RealPos;
    CVector3 toward;
    toward.y = py - camera.y;
    toward.x = px - camera.x;
    toward.z = pz - camera.z;
    const float length = Sqrtf(ppc::fmadds(toward.z, toward.z, ppc::fmadds(toward.x, toward.x, toward.y * toward.y)));
    if (length != 0.0f) {
        const float inverse = 1.0f / length;
        toward.z = toward.z * inverse;
        toward.x = toward.x * inverse;
        toward.y = toward.y * inverse;
    }
    Mat4_SetBasisFromAtUp(&m, &toward, &kAxisY);  // 0x0023fd30
    CVector3 offset = DataOf(this)->m_unk40;
    Mat4_TransformVectors(&m, &offset, &offset, 1);  // 0x0023f7b0
    RwFrame* frame = m_pCursorNode->m_pRwFrame;
    frame->modelling.pos.z = pz + offset.z;
    frame->modelling.pos.x = px + offset.x;
    frame->modelling.pos.y = py + offset.y;
    frame->modelling.flags &= 0xfffdffffu;
    RwFrame_MarkDirty(m_pCursorNode->m_pRwFrame);
    if (m_ui8Alpha != oldAlpha && m_pCursorNode->m_lGeometryList != nullptr) ApplyCursorAlpha(m_pCursorNode, m_ui8Alpha);
    data = DataOf(this);
    if (data == nullptr || data->m_unk5f == 0) return;
    CNode* node = m_pCursorNode;
    float screen[2] = {0.0f, 0.0f};  // BUG(original): uninitialised without the rasters
    ProjectWorldPointToScreen(g_pEngine->m_graphic->m_renderer->m_cameraContext, &node->m_pRwFrame->modelling.pos,
                              screen, 0);  // 0x000a30c0
    frame = node->m_pRwFrame;
    frame->modelling.pos.z = 0.0f;  // stw 0
    frame->modelling.pos.y = 1.0f - screen[1];
    frame->modelling.pos.x = 1.0f - screen[0];
    frame->modelling.flags &= 0xfffdffffu;
    RwFrame_MarkDirty(node->m_pRwFrame);
}

// 0x001d5ca0 CKTargetCursorNodeFx_Load
int32_t CKTargetCursorNodeFx::Load(IKFile* file, int32_t type) {
    IKNodeFx::Load(file, type);
    if (type == K_LEVEL_PLATEFORMS) IKFile_ReadRef(file, &m_pCursorNode);
    return 1;
}

// 0x001d5c48 CKTargetCursorNodeFx_PostLoad: IKNodeFx_PostLoad, then for the level type a matrix (RwMatrixCreate_Thunk).
int32_t CKTargetCursorNodeFx::PostLoad(int32_t type) {
    IKNodeFx::PostLoad(type);
    if (type == K_LEVEL_PLATEFORMS) m_pMatrix1c = RwMatrixCreate_Thunk();
    return 1;
}

// 0x001d7190 StopOwnedEffectWithFadeOut_maybe (from the assembly). Reserved by `owner`: the disappear time (data +0x0c)
// becomes the phase time; unless it is <= 0 (fcmpu / ble against 0.0f: an unordered time fades) or `immediate`, the
// disappear phase starts (bit 3) from the current alpha and scale, else the cursor stops (vt+0x6c). Then, in every case,
// the reservation is released for `owner` (vt+0x54).
void CKTargetCursorNodeFx::StopForOwnerWithFadeOut(const IKSerializable* owner, int32_t immediate) {
    if ((m_baFxData & 2) != 0 && m_pOwner == owner) {
        const float time = DataOf(this)->m_unk0c;
        m_fPhaseTime = time;
        if (time <= 0.0f || immediate != 0) {
            Stop();  // vt+0x6c
        } else {
            m_baFxData = static_cast<uint8_t>(m_baFxData | 8);  // rlwinm pair (bit 3 cleared) then ori 8
            m_ui8StopAlpha = m_ui8Alpha;
            m_fStopScale = m_fScale;
        }
    }
    ReleaseReservation(owner);  // vt+0x54
}

// 0x001d5ec8 CKTargetCursorNodeFx_SetPositionForOwner_maybe
void CKTargetCursorNodeFx::SetPositionForOwner(const IKSerializable* owner, const CVector3* position) {
    if ((m_baFxData & 2u) == 0 || m_pOwner != owner || m_pCursorNode == nullptr) return;
    m_pMatrix1c->m_pos = *position;
    uint32_t flags;
    std::memcpy(&flags, reinterpret_cast<const uint8_t*>(m_pMatrix1c) + 0xc, 4);
    flags &= 0xfffdffffu;
    std::memcpy(reinterpret_cast<uint8_t*>(m_pMatrix1c) + 0xc, &flags, 4);
    RwFrame* frame = m_pCursorNode->m_pRwFrame;
    frame->modelling.pos.z = position->z;
    frame->modelling.pos.x = position->x;
    frame->modelling.pos.y = position->y;
    frame->modelling.flags &= 0xfffdffffu;
    RwFrame_MarkDirty(frame);  // 0x00010698
}

// 0x001d5808 CKTargetCursorNodeFx_RecursiveRegistration: registered with the saving manager (vt+0x24, no owner) only.
void CKTargetCursorNodeFx::RecursiveRegistration(int32_t /*type*/) {
    g_pEngine->m_pSavingManager->RegisterSerializableObject(this, nullptr);  // vt+0x24
}

// 0x001d5d88 CKTargetCursorNodeFx_Destroy: IKNodeFx's (no node), then the placement matrix destroyed (the pointer kept).
void CKTargetCursorNodeFx::Destroy() {
    IKNodeFx::Destroy();
    RwMatrixDestroy_Thunk(m_pMatrix1c);  // 0x0023f968
}

// 0x001d5988 CKTargetCursorNodeFx_StopForOwner_maybe: for the reserving `owner`, the phase time from the data's disappear
// time (+0x0c); when it is not above 0 (ble: an unordered time stops too) or `immediate`, stopped (vt+0x6c), else the
// disappear phase (bit 3) from the current alpha and scale. Unlike 0x1d7190 the reservation is kept.
void CKTargetCursorNodeFx::StopForOwner(const IKSerializable* owner, int32_t immediate) {
    if ((m_baFxData & 2u) == 0 || m_pOwner != owner) return;
    const float time = static_cast<const CKTargetCursorFxData*>(m_pFxData)->m_unk0c;
    m_fPhaseTime = time;
    if (!(time > 0.0f) || immediate != 0) {
        Stop();  // vt+0x6c
        return;
    }
    m_baFxData = static_cast<uint8_t>(m_baFxData | 8);
    m_ui8StopAlpha = m_ui8Alpha;
    m_fStopScale = m_fScale;
}
