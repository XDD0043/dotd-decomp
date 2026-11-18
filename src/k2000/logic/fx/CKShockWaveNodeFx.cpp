// CKShockWaveNodeFx.cpp - reconstructed original translation unit 0x1d22e8-0x1d3568 (GAME_TOC1, main_toc1), 22 functions, 22 live.
// Primary class: CKShockWaveNodeFx  key 0x30cc  category Logic  size 0x58  vtable 0xb1d808
// Other owners: FxAttachment (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x1d22e8  CKShockWaveNodeFx_Delete
//   [x] 0x1d2338  CKShockWaveNodeFx_PostLoad
//   [ ] 0x1d2388  RegisterCKShockWaveNodeFxClass
//   [ ] 0x1d2400  _GLOBAL__I_1d2400
//   [x] 0x1d2410  FxAttachment_SetPositionIfOwner_maybe
//   [x] 0x1d24b0  CKShockWaveNodeFx_Load
//   [ ] 0x1d24d8  CKShockWaveNodeFx_Save
//   [x] 0x1d2500  CKShockWaveNodeFx_RecursiveRegistration
//   [x] 0x1d2580  CKShockWaveNodeFx_Destroy  (inherited: CKNodeFx3d_Destroy)
//   [x] 0x1d25a8  CKShockWaveNodeFx_DeleteArray
//   [x] 0x1d2648  CKShockWaveNodeFx_Create
//   [x] 0x1d26a0  CKShockWaveNodeFx_SetDamageFlags
//   [x] 0x1d26c8  CKShockWaveNodeFx_SetDamageType
//   [x] 0x1d26f0  CKShockWaveNodeFx_SetDamageOwner
//   [x] 0x1d2718  CKShockWaveNodeFx_Start
//   [x] 0x1d2770  CKShockWaveNodeFx_Stop
//   [x] 0x1d2878  CKShockWaveNodeFx_CreateArray
//   [x] 0x1d2928  CKShockWaveNodeFx_Trigger
//   [x] 0x1d2cc8  CKShockWaveNodeFx_Trigger  (b 0x1d2928: the Trigger above)
//   [x] 0x1d2cd0  CKShockWaveNodeFx_SetPosition
//   [x] 0x1d2d70  CKShockWaveNodeFx_Update
//   [x] 0x1d3340  CKShockWaveNodeFx_SetDirection_maybe
//
//   [ ] 0x9ad220  CKShockWaveNodeFx_IsKindOfClass  [inline]
//   [x] 0x9ad258  CKShockWaveNodeFx_GetClassType  [inline]
//   [x] 0x9ad260  CKShockWaveNodeFx_GetClassID  [inline]
//   [x] 0x9ad268  CKShockWaveNodeFx_GetFxData  [inline]
//   [x] 0x9ad270  CKShockWaveNodeFx_SetFxData  [inline]
//   [ ] 0x9ad278  CKShockWaveNodeFx_Destruct  [inline]
//   [ ] 0x9ad298  CKShockWaveNodeFx_DeletingDestruct  [inline]
#include "k2000/logic/fx/CKShockWaveNodeFx.h"
#include "k2000/logic/CKSavingManager.h"
#include "k2000/cameras/CameraContext.h"
#include <cmath>
#include "k2000/system/IKTime.h"
#include "k2000/services/CKSrvCollision.h"
#include "k2000/scenegraph/CSGMovable.h"
#include "k2000/scenegraph/CSGBranch.h"
#include "k2000/scenegraph/CNode.h"
#include "k2000/scenegraph/CKDynamicBoundingSphere.h"
#include "k2000/misc/Engine.h"
#include "k2000/misc/ClassRegistry.h"
#include "k2000/logic/render/CMaterial.h"
#include "k2000/geometry/CGeometry.h"
#include "k2000/fx/CKShockWaveFxData.h"
#include "Renderware/rwcore/RwCamera.h"
#include "crt/ppc_ops.h"
#include <cstring>

#include "k2000/io/IKFile.h"

// 0x001d24b0 CKShockWaveNodeFx_Load
int32_t CKShockWaveNodeFx::Load(IKFile* file, int32_t type) {
    IKNodeFx::Load(file, type);
    return 1;
}

namespace {
bool Reserved(const IKFx* fx, const IKSerializable* owner) { return (fx->m_baFxData & 2u) != 0 && fx->m_pOwner == owner; }
const CVector3 kNull{0.0f, 0.0f, 0.0f};  // 0x00c50d64 (TOC -0x1a60)
// 0x00010690 Math_Sqrtf: the double square root rounded to float.
float Sqrtf(float x) { return static_cast<float>(std::sqrt(static_cast<double>(x))); }
bool IsNull(const CVector3& v) { return v.x == kNull.x && v.y == kNull.y && v.z == kNull.z; }
CGeometry* FirstGeometry(CNode* node) { return static_cast<CGeometry*>(node->m_lGeometryList); }
uint32_t MaterialMode(const CGeometry* geometry) {
    return (static_cast<const CMaterial*>(geometry->m_pMaterial)->m_baProperties >> 3) & 0xfu;
}
}  // namespace

// 0x001d2338 CKShockWaveNodeFx_PostLoad
int32_t CKShockWaveNodeFx::PostLoad(int32_t /*type*/) {
    m_unk54 = -1;  // 0x00c50dfc: ff ff ff ff
    if (m_pNode == nullptr) return 1;
    CGeometry* geometry = FirstGeometry(m_pNode);
    geometry->m_BitProperties = (((geometry->m_BitProperties & ~0x1fu) | 0xfu) & ~0x20u) | 0x20u;
    return 1;
}

// 0x001d2718 CKShockWaveNodeFx_Start
void CKShockWaveNodeFx::Vf64() {
    m_baFxData = static_cast<uint8_t>(m_baFxData & 0xfau);
    m_pDamageSphere = nullptr;
    m_fRadius = 0.01f;  // TOC -0x1a64
    m_pDamageOwner = nullptr;
    std::memcpy(&m_unk54, static_cast<const CKShockWaveFxData*>(m_pFxData)->m_unk40, sizeof m_unk54);
    m_v3Direction = kNull;
}

// 0x001d2770 CKShockWaveNodeFx_Stop
void CKShockWaveNodeFx::Stop() {
    m_baFxData = static_cast<uint8_t>((m_baFxData & 0xfeu) | 1u);
    if (m_pDamageSphere != nullptr) {
        IKBoundingVolume* sphere = m_pDamageSphere;
        if (sphere->m_pParent != nullptr) sphere->m_pParent->RemoveChild(sphere);  // vt+0x78
        static_cast<CKSrvCollision*>(g_pEngine->m_srvCollision)->ReleaseDynSphere(m_pDamageSphere);  // 0x00191a38
        m_pDamageSphere = nullptr;
    }
    m_pDamageOwner = nullptr;
    m_v3Direction = kNull;
    Vf60();  // vt+0x60 the node hidden
}

// 0x001d26a0 CKShockWaveNodeFx_SetDamageFlags
void CKShockWaveNodeFx::SetDamageFlags(uint16_t flags, const IKSerializable* owner) {
    if (Reserved(this, owner)) m_ui16DamageFlags = flags;
}

// 0x001d26c8 CKShockWaveNodeFx_SetDamageType
void CKShockWaveNodeFx::SetDamageType(uint8_t type, const IKSerializable* owner) {
    if (Reserved(this, owner)) m_ui8DamageType = type;
}

// 0x001d26f0 CKShockWaveNodeFx_SetDamageOwner
void CKShockWaveNodeFx::SetDamageOwner(IKSerializable* damageOwner, const IKSerializable* owner) {
    if (Reserved(this, owner)) m_pDamageOwner = damageOwner;
}

// 0x001d2cd0 CKShockWaveNodeFx_SetPosition
void CKShockWaveNodeFx::SetPosition(const CVector3* position, const IKSerializable* owner) {
    if (!Reserved(this, owner) || m_pNode == nullptr) return;
    RwFrame* frame = static_cast<CSGMovable*>(static_cast<IKSerializable*>(m_pNode))->m_pRwFrame;
    frame->modelling.pos.z = position->z;
    frame->modelling.pos.x = position->x;
    frame->modelling.pos.y = position->y;
    frame->modelling.flags &= 0xfffdffffu;
    RwFrame_MarkDirty(frame);  // 0x00010698
}

// 0x001d2928 CKShockWaveNodeFx_Trigger
void CKShockWaveNodeFx::Trigger(const IKSerializable* owner) {
    if (!Reserved(this, owner)) return;
    m_baFxData = static_cast<uint8_t>((m_baFxData & ~4u) | 4u);
    if (m_pNode == nullptr) return;
    m_fElapsed = 0.0f;
    Vf5C();  // vt+0x5c shown
    if (m_pDamageOwner != nullptr) {
        if (m_pDamageSphere == nullptr) {
            m_pDamageSphere = static_cast<CKDynamicBoundingSphere*>(
                static_cast<CKSrvCollision*>(g_pEngine->m_srvCollision)->AcquireDynSphere());  // 0x00192a70
        }
        if (m_pDamageSphere != nullptr) {
            CKDynamicBoundingSphere* sphere = m_pDamageSphere;
            m_fRadius = 0.1f;  // TOC -0x1a5c
            sphere->m_fRadius = 0.1f;
            sphere->m_ba8Infos = static_cast<uint8_t>(sphere->m_ba8Infos | 0x08u);
            sphere->m_ba8Infos = static_cast<uint8_t>(sphere->m_ba8Infos | 0x20u);
            sphere->m_ba8Infos = static_cast<uint8_t>(sphere->m_ba8Infos | 0x04u);
            sphere->m_pOwner = m_pDamageOwner;
            const RwV3d& at = static_cast<CSGMovable*>(static_cast<IKSerializable*>(m_pNode))->m_pRwFrame->modelling.pos;
            sphere->m_v3WorldMove = kNull;
            sphere->m_v3OldPos = CVector3{at.x, at.y, at.z};
            sphere->m_v3LastWorldPos = CVector3{at.x, at.y, at.z};
            sphere->m_ui16PropertiesFlags = 0;
            sphere->m_ui8OwnerType = 0;
            sphere->m_ui8OwnerType = m_ui8DamageType;
            sphere->m_ui16PropertiesFlags = static_cast<uint16_t>(m_ui16DamageFlags | sphere->m_ui16PropertiesFlags);
            RwFrame* frame = sphere->m_pRwFrame;
            frame->modelling.pos = at;
            frame->modelling.flags &= 0xfffdffffu;
            RwFrame_MarkDirty(sphere->m_pRwFrame);
            sphere->m_unk1c = m_pFxData != nullptr ? static_cast<const CKShockWaveFxData*>(m_pFxData)->m_pDamage3c : nullptr;
            CSGBranch* root = static_cast<CSGBranch*>(g_pEngine->m_dynamicSceneRoot);
            if (sphere->m_pParent != root) {
                if (sphere->m_pParent != nullptr) sphere->m_pParent->RemoveChild(sphere);  // vt+0x78
                root->AddChild(m_pDamageSphere);  // vt+0x70
            }
        }
    }
    CMatrix34* uv = static_cast<CMaterial*>(FirstGeometry(m_pNode)->m_pMaterial)->GetUVTransformMatrix();  // 0x000bb9f8
    uv->m_pos = kNull;
    uv->m_ui32Flags &= 0xfffdffffu;
    const uint32_t r = static_cast<uint32_t>(Rand_Int()) & 0xffffu;  // 0x00011500
    m_fRandom = ppc::fmadds(static_cast<float>(static_cast<double>(r)), -3.05180438e-05f, 1.0f);  // TOC -0x1a58 / -0x1a54
}

// 0x001d3340 CKShockWaveNodeFx_SetDirection_maybe
void CKShockWaveNodeFx::SetDirection(const CVector3* direction, const IKSerializable* owner) {
    if (!Reserved(this, owner)) return;
    m_v3Direction = *direction;
    const float length = Sqrtf((ppc::fmadds(m_v3Direction.z, m_v3Direction.z,
                                                                 ppc::fmadds(m_v3Direction.x, m_v3Direction.x,
                                                                             m_v3Direction.y * m_v3Direction.y))));  // 0x00010690
    if (length != 0.0f) {
        const float inverse = 1.0f / length;
        m_v3Direction.z = inverse * m_v3Direction.z;
        m_v3Direction.x = inverse * m_v3Direction.x;
        m_v3Direction.y = inverse * m_v3Direction.y;
    }
    const uint32_t r = static_cast<uint32_t>(Rand_Int()) & 0xffffu;
    m_fRandom = ppc::fmadds(static_cast<float>(static_cast<double>(r)), -3.05180438e-05f, 1.0f);
    if (!(m_v3Direction.y < 1.0f)) {
        m_v3Direction = kNull;
        return;
    }
    const CVector3 axis{0.0f, 1.0f, 0.0f};  // 0x00c50d40 (TOC -0x1a34)
    const CVector3& d = m_v3Direction;
    const float sx = ppc::fmsubs(d.y, axis.z, d.z * axis.y);
    m_v3Side.x = sx;
    const float sy = ppc::fmsubs(d.z, axis.x, d.x * axis.z);
    m_v3Side.y = sy;
    const float sz = ppc::fmsubs(d.x, axis.y, d.y * axis.x);
    m_v3Side.z = sz;
    // The side turned about the direction: (direction x side) x the random + the side.
    const float cz = ppc::fmsubs(sy, d.x, d.y * sx);
    const float cx = ppc::fmsubs(d.y, sz, d.z * sy);
    const float cy = ppc::fmsubs(d.z, sx, d.x * sz);
    m_v3Side.z = ppc::fmadds(cz, m_fRandom, sz);
    m_v3Side.y = ppc::fmadds(cy, m_fRandom, sy);
    m_v3Side.x = ppc::fmadds(cx, m_fRandom, sx);
    const float side = Sqrtf((ppc::fmadds(m_v3Side.z, m_v3Side.z,
                                                               ppc::fmadds(m_v3Side.x, m_v3Side.x, m_v3Side.y * m_v3Side.y))));
    if (side == 0.0f) return;
    const float inverse = 1.0f / side;
    m_v3Side.z = inverse * m_v3Side.z;
    m_v3Side.x = inverse * m_v3Side.x;
    m_v3Side.y = inverse * m_v3Side.y;
}

// 0x001d2d70 CKShockWaveNodeFx_Update
void CKShockWaveNodeFx::Update(IKTime* frameClock) {
    if (((m_baFxData >> 2) & 1u) == 0) return;
    const float dt = frameClock->m_afDeltaTime[0];
    m_fElapsed = dt + m_fElapsed;
    const CKShockWaveFxData* data = static_cast<const CKShockWaveFxData*>(m_pFxData);
    if (!(data->m_unk08 > m_fElapsed)) {
        Stop();  // vt+0x6c
        return;
    }
    CGeometry* geometry = FirstGeometry(m_pNode);
    if (data->m_unk0c > 0.0f) {
        const uint32_t mode = MaterialMode(geometry);
        if (mode - 5u <= 1u || mode == 0xb || mode == 0xd || mode == 0xc || mode == 0xe) {
            CMatrix34* uv = static_cast<CMaterial*>(geometry->m_pMaterial)->GetUVTransformMatrix();
            float u = ppc::fmadds(dt, static_cast<const CKShockWaveFxData*>(m_pFxData)->m_unk0c, uv->m_pos.x);
            if (u < -1.0f) {
                do {
                    u = u + 1.0f;
                } while (u < -1.0f);
            }
            while (u > 1.0f) u = u - 1.0f;
            uv->m_pos.x = u;
            uv->m_ui32Flags &= 0xfffdffffu;
        }
        data = static_cast<const CKShockWaveFxData*>(m_pFxData);
    }
    CSGMovable* node = static_cast<CSGMovable*>(static_cast<IKSerializable*>(m_pNode));
    auto resetRotation = [node]() {
        const RwV3d keep = node->m_pRwFrame->modelling.pos;
        node->SetIdentity();  // 0x000d08f0
        RwFrame* frame = node->m_pRwFrame;
        frame->modelling.pos.z = keep.z;
        frame->modelling.pos.x = keep.x;
        frame->modelling.pos.y = keep.y;
        frame->modelling.flags &= 0xfffdffffu;
        RwFrame_MarkDirty(frame);
    };
    if (((data->m_unk30 >> 2) & 1u) != 0) {
        // Facing the camera: up = -the camera's at, at = its right x +0x50 + its up x (1 - +0x50), normalised.
        const RwFrame* camera = static_cast<const CSGMovable*>(static_cast<const CameraContext*>(g_pEngine->m_cameraContext)->m_pCamera)->m_pRwFrame;
        const float k = m_fRandom;
        const float j = 1.0f - k;
        const CVector3 up{-camera->modelling.at.x, -camera->modelling.at.y, -camera->modelling.at.z};
        const float rx = k * camera->modelling.right.x;
        const float ry = k * camera->modelling.right.y;
        const float rz = k * camera->modelling.right.z;
        CVector3 at{ppc::fmadds(j, camera->modelling.up.x, rx), ppc::fmadds(j, camera->modelling.up.y, ry),
                    ppc::fmadds(j, camera->modelling.up.z, rz)};
        const float length = Sqrtf((ppc::fmadds(at.z, at.z, ppc::fmadds(at.x, at.x, at.y * at.y))));
        if (length != 0.0f) {
            const float inverse = 1.0f / length;
            at.z = at.z * inverse;
            at.x = at.x * inverse;
            at.y = at.y * inverse;
        }
        node->SetOrientationFromUpAt(&up, &at);  // 0x000d0a88
    } else if (IsNull(m_v3Direction) || IsNull(m_v3Side)) {
        resetRotation();
    } else {
        node->SetOrientationFromUpAt(&m_v3Direction, &m_v3Side);
    }
    data = static_cast<const CKShockWaveFxData*>(m_pFxData);
    const float radius = data->EvalRadiusScale(m_fElapsed);  // 0x001d12b8
    const float height = static_cast<const CKShockWaveFxData*>(m_pFxData)->EvalHeightScale(m_fElapsed);  // 0x001d1388
    node->ScaleXYZ(radius, height, radius);  // 0x000d0d28
    if (m_pDamageOwner != nullptr && m_pDamageSphere != nullptr) {
        data = static_cast<const CKShockWaveFxData*>(m_pFxData);
        if (m_fRadius < data->m_unk34) {
            m_fRadius = ppc::fmadds(data->m_unk38 * dt, data->m_unk34 - m_fRadius, m_fRadius);
            if (m_fRadius > data->m_unk34) m_fRadius = data->m_unk34;
        }
        RwFrame* frame = m_pDamageSphere->m_pRwFrame;
        frame->modelling.pos = node->m_pRwFrame->modelling.pos;
        frame->modelling.flags &= 0xfffdffffu;
        RwFrame_MarkDirty(m_pDamageSphere->m_pRwFrame);
        m_pDamageSphere->m_fRadius = m_fRadius > 0.0f ? m_fRadius : 0.001f;  // TOC -0x1a3c
    }
    uint8_t color[4];
    std::memcpy(color, &m_unk54, sizeof color);
    color[3] = static_cast<uint8_t>(ppc::fctiwz(static_cast<const CKShockWaveFxData*>(m_pFxData)->EvalAlpha(m_fElapsed)));  // 0x001d1458
    std::memcpy(geometry->m_cGeometryColor, color, sizeof color);
    if (color[3] != 0xff && (geometry->m_BitProperties & 0x1000u) != 0) {
        const uint32_t mode = MaterialMode(geometry);
        if (mode > 0 && mode <= 6) geometry->m_cGeometryColor[3] = 0xff;
    }
    const uint32_t translucent = geometry->m_cGeometryColor[3] != 0xff ? 1u : 0u;
    if (((geometry->m_BitProperties >> 11) & 1u) != translucent) {
        geometry->m_BitProperties = (geometry->m_BitProperties & ~0x800u) | (translucent << 11);
        geometry->UpdateProperties();  // vt+0x60
    }
}

// 0x001d2500 CKShockWaveNodeFx_RecursiveRegistration: registered with the saving manager (vt+0x24, no owner), then IKNodeFx's (0x1d88c0 CKNodeFx3d_LevelReset):
// the node's registration (its vt+0x24) when there is one.
void CKShockWaveNodeFx::RecursiveRegistration(int32_t type) {
    g_pEngine->m_pSavingManager->RegisterSerializableObject(this, nullptr);  // vt+0x24
    IKNodeFx::RecursiveRegistration(type);
}
