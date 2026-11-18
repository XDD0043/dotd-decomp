// CKLightningObjectNodeFx.cpp - reconstructed original translation unit 0x1c7128-0x1c8060 (GAME_TOC1, main_toc1),
// 14 functions, 14 live.
// Primary class: CKLightningObjectNodeFx  key 0x194c  category Logic  size 0x40  vtable 0xb1d2b8
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x1c7128  CKLightningObjectNodeFx_Delete  (DOTD_DECLARE_FACTORIES)
//   [ ] 0x1c7178  RegisterCKLightningObjectNodeFxClass
//   [ ] 0x1c71f0  _GLOBAL__I_1c71f0
//   [x] 0x1c7200  CKLightningObjectNodeFx_RecursiveRegistration
//   [x] 0x1c72c0  CKLightningObjectNodeFx_Destroy
//   [x] 0x1c7318  CKLightningObjectNodeFx_DeleteArray  (DOTD_DECLARE_FACTORIES)
//   [x] 0x1c73b8  CKLightningObjectNodeFx_CreateArray  (DOTD_DECLARE_FACTORIES; the constructor)
//   [x] 0x1c7468  CKLightningObjectNodeFx_Start
//   [x] 0x1c77a0  CKLightningObjectNodeFx_PostLoad
//   [x] 0x1c7878  CKLightningObjectNodeFx_Update
//   [x] 0x1c7d20  CKLightningObjectNodeFx_Create  (DOTD_DECLARE_FACTORIES; the constructor)
//   [x] 0x1c7d78  CKLightningObjectNodeFx_Stop
//   [x] 0x1c7ee0  CKLightningObjectNodeFx_Load
//   [ ] 0x1c7fa0  CKLightningObjectNodeFx_Save
//
//   [x] 0x9aca28  CKLightningObjectNodeFx_IsKindOfClass  [inline]  (CKLightningObjectNodeFx.h)
//   [x] 0x9aca60  CKLightningObjectNodeFx_GetClassType  [inline]  (DOTD_CLASS_KEY)
//   [x] 0x9aca68  CKLightningObjectNodeFx_GetClassID  [inline]  (DOTD_CLASS_KEY)
//   [x] 0x9aca70  CKLightningObjectNodeFx_GetFxData  [inline]
//   [x] 0x9aca78  CKLightningObjectNodeFx_SetFxData  [inline]
//   [x] 0x9aca80  CKLightningObjectNodeFx_Destruct  [inline]  (CKLightningObjectNodeFx.h)
//   [x] 0x9acaa0  CKLightningObjectNodeFx_DeletingDestruct  [inline]  (CKLightningObjectNodeFx.h)
#include "k2000/logic/render/CKLightningObjectNodeFx.h"

#include <cmath>
#include <cstring>

#include "Renderware/rpworld/RpAtomic.h"
#include "Renderware/rpworld/RpGeometry.h"
#include "Renderware/rwcore/RwCamera.h"
#include "crt/ppc_ops.h"
#include "k2000/cameras/CKSrvCamera.h"
#include "k2000/dictionaries/CAnimationDictionary.h"
#include "k2000/geometry/CGeometry.h"
#include "k2000/io/IKFile.h"
#include "k2000/logic/CKSavingManager.h"
#include "k2000/logic/fx/CKLightningObjectFxData.h"
#include "k2000/misc/ClassRegistry.h"
#include "k2000/misc/Engine.h"
#include "k2000/scenegraph/CAnimatedNode.h"
#include "k2000/system/IKTime.h"

namespace {

CGeometry* FirstGeometry(CNode* node) { return static_cast<CGeometry*>(node->m_lGeometryList); }

// The data's words at +0x08 (the animation speed) and +0x10 (the x scale) are read as floats (lfs) here; the data's
// header keeps them as the Load's words (port-rest R06), so their bits are reinterpreted.
float WordAsFloat(uint32_t word) {
    float value;
    std::memcpy(&value, &word, sizeof(value));
    return value;
}

CVector3& DataStart(CKLightningObjectFxData* data) { return *reinterpret_cast<CVector3*>(&data->m_afUnk18[0]); }  // +0x18
CVector3& DataEnd(CKLightningObjectFxData* data) { return *reinterpret_cast<CVector3*>(&data->m_afUnk18[3]); }    // +0x24
CVector3& DataDir(CKLightningObjectFxData* data) { return *reinterpret_cast<CVector3*>(&data->m_afUnk18[6]); }    // +0x30

// u / 65535 for one Rand_Int draw (fcfid of the low 16 bits, frsp, fdivs by TOC -0x1d0c 0x477fff00).
float RandUnit() { return static_cast<float>(static_cast<uint16_t>(Rand_Int())) / 65535.0f; }

// p = base + t * dir per component (fmadds).
void OffsetAlong(CVector3* out, float t, const CVector3& dir, const CVector3& base) {
    out->x = ppc::fmadds(t, dir.x, base.x);
    out->z = ppc::fmadds(t, dir.z, base.z);
    out->y = ppc::fmadds(t, dir.y, base.y);
}

}  // namespace

CKLightningObjectNodeFx::CKLightningObjectNodeFx() {}
CKLightningObjectNodeFx::~CKLightningObjectNodeFx() {}

IKFxData* CKLightningObjectNodeFx::GetFxData() { return m_pData; }  // 0x009aca70
void CKLightningObjectNodeFx::SetFxData(IKFxData* data) {  // 0x009aca78
    m_pData = static_cast<CKLightningObjectFxData*>(data);
}

// 0x001c72c0 CKLightningObjectNodeFx_Destroy: no node; the dictionary's Destroy (vt+0x10; no null test).
void CKLightningObjectNodeFx::Destroy() {
    IKNodeFx::Destroy();
    m_pDictionary->Destroy();
}

// 0x001c7200 CKLightningObjectNodeFx_RecursiveRegistration
void CKLightningObjectNodeFx::RecursiveRegistration(int32_t type) {
    g_pEngine->m_pSavingManager->RegisterSerializableObject(this, nullptr);  // vt+0x24
    IKNodeFx::RecursiveRegistration(type);
    if (m_pDictionary != nullptr) m_pDictionary->RecursiveRegistration(type);
}

// 0x001c7ee0 CKLightningObjectNodeFx_Load: IKNodeFx's; level files: the dictionary reference.
int32_t CKLightningObjectNodeFx::Load(IKFile* file, int32_t type) {
    IKNodeFx::Load(file, type);
    if (type == K_LEVEL_PLATEFORMS) IKFile_ReadRef(file, &m_pDictionary);
    return 1;
}

// 0x001c77a0 CKLightningObjectNodeFx_PostLoad: with a node, its geometry's blend mode 2 and the dictionary's first
// animation played from 0; without one, the dictionary destroyed (vt+0x10, then the registry) and cleared.
int32_t CKLightningObjectNodeFx::PostLoad(int32_t /*type*/) {
    if (m_pNode != nullptr) {
        FirstGeometry(m_pNode)->SetBlendMode(2);
        static_cast<CAnimatedNode*>(m_pNode)->PlayAnim(0.0, static_cast<uint32_t>(m_pDictionary->m_apAnimations[0]), 0);
        return 1;
    }
    if (m_pDictionary != nullptr) {
        m_pDictionary->Destroy();
        ClassRegistry_DestroyObject(m_pDictionary);
        m_pDictionary = nullptr;
    }
    return 1;
}

// 0x001c7468 CKLightningObjectNodeFx_Start: with a node: running, the time 0; the dictionary's first animation played
// from 0 (data bit 0: from a random start, one Rand_Int draw); data bit 3: every prelit colour of the geometry set to
// the data's colour; the end points the data's (bit 2: each moved a random distance, data +0x40 x u, along the data's
// direction; one draw each, Start first); then shown (vt+0x5c).
void CKLightningObjectNodeFx::Vf64() {
    if (m_pNode == nullptr) return;
    m_baFxData = static_cast<uint8_t>(m_baFxData & 0xfe);
    m_fTime = 0.0f;
    CAnimatedNode* node = static_cast<CAnimatedNode*>(m_pNode);
    if ((m_pData->m_baFlags44 & 1u) == 0) {
        node->PlayAnim(0.0, static_cast<uint32_t>(m_pDictionary->m_apAnimations[0]), 0);  // 0x000c98b8
    } else {
        const float start = RandUnit();
        node->PlayAnim(start, static_cast<uint32_t>(m_pDictionary->m_apAnimations[0]), 0);
    }
    if (((m_pData->m_baFlags44 >> 3) & 1u) != 0) {
        CGeometry* geometry = FirstGeometry(m_pNode);
        RpGeometryLock(geometry->m_pRpAtomic->geometry, 8);
        RpGeometry* rp = geometry->m_pRpAtomic->geometry;
        RwRGBA* prelit = rp->preLitLum;
        for (uint32_t i = 0; static_cast<uint32_t>(geometry->m_pRpAtomic->geometry->numVertices) > i; ++i) {
            std::memcpy(&prelit[i], m_pData->m_Color, 4);  // lwz / stw: the colour word
        }
        geometry->UnlockGeometry();
    }
    if (((m_pData->m_baFlags44 >> 2) & 1u) == 0) {
        m_v3Start = DataStart(m_pData);
        m_v3End = DataEnd(m_pData);
    } else {
        float range = m_pData->m_unk40;
        float t = range * RandUnit();  // fmuls
        m_fStartOffset = t;
        OffsetAlong(&m_v3Start, t, DataDir(m_pData), DataStart(m_pData));
        range = m_pData->m_unk40;
        t = range * RandUnit();
        m_fEndOffset = t;
        OffsetAlong(&m_v3End, t, DataDir(m_pData), DataEnd(m_pData));
    }
    Vf5C();
}

// 0x001c7d78 CKLightningObjectNodeFx_Stop: stopped; with data: bit 3 set: the geometry's prelit colours white again and
// bit 3 cleared; bits 2 and 1 cleared; then hidden (vt+0x60).
void CKLightningObjectNodeFx::Stop() {
    m_baFxData = static_cast<uint8_t>((m_baFxData & 0xfe) | 1);
    if (m_pData != nullptr) {
        if (((m_pData->m_baFlags44 >> 3) & 1u) != 0) {
            CGeometry* geometry = FirstGeometry(m_pNode);
            RpGeometryLock(geometry->m_pRpAtomic->geometry, 8);
            RwRGBA* prelit = geometry->m_pRpAtomic->geometry->preLitLum;
            for (uint32_t i = 0; static_cast<uint32_t>(geometry->m_pRpAtomic->geometry->numVertices) > i; ++i) {
                prelit[i].alpha = 0xff;
                prelit[i].red = 0xff;
                prelit[i].green = 0xff;
                prelit[i].blue = 0xff;
            }
            geometry->UnlockGeometry();
            m_pData->m_baFlags44 = static_cast<uint8_t>(m_pData->m_baFlags44 & ~8u);
        }
        m_pData->m_baFlags44 = static_cast<uint8_t>(m_pData->m_baFlags44 & ~4u);
        m_pData->m_baFlags44 = static_cast<uint8_t>(m_pData->m_baFlags44 & ~2u);
    }
    Vf60();
}

// 0x001c7878 CKLightningObjectNodeFx_Update: stops (vt+0x6c) once the time is not below the data's duration (+0x0c;
// NaN stops too) or without a node. Else the animation advanced by dt x the data's speed (+0x08); the end points:
// data bit 1 clear: End = Start - the data's length (+0x14) x the camera's real Y axis; set: (bit 2: Start / End along
// the data's direction by their offsets - BUG(original): both overwritten right after) Start / End the data's and
// the data's length set to their distance. The node's frame: position the middle, at axis the unit direction Start ->
// End (unnormalised when 0 long), right = at x the camera's real Z axis, up = right x at; scaled by (data +0x10, 1,
// data +0x14); the time advanced by dt.
void CKLightningObjectNodeFx::Update(IKTime* frameClock) {
    if (!(m_fTime < m_pData->m_unk0c) || m_pNode == nullptr) {  // fcmpu / bge
        Stop();
        return;
    }
    const float dt = frameClock->m_afDeltaTime[0];
    CKSrvCamera* camera = static_cast<CKSrvCamera*>(g_pEngine->m_srvCamera);
    CAnimatedNode* node = static_cast<CAnimatedNode*>(m_pNode);
    node->AddAnimTime(dt * WordAsFloat(m_pData->m_unk08));  // 0x000c9638
    if ((m_pData->m_baFlags44 & 2u) == 0) {
        m_v3End = m_v3Start;
        const float length = -m_pData->m_unk14;
        m_v3End.z = ppc::fmadds(length, camera->m_v3RealAxisY.z, m_v3Start.z);
        m_v3End.x = ppc::fmadds(length, camera->m_v3RealAxisY.x, m_v3Start.x);
        m_v3End.y = ppc::fmadds(length, camera->m_v3RealAxisY.y, m_v3Start.y);
    } else {
        if (((m_pData->m_baFlags44 >> 2) & 1u) != 0) {
            OffsetAlong(&m_v3Start, m_fStartOffset, DataDir(m_pData), DataStart(m_pData));
            OffsetAlong(&m_v3End, m_fEndOffset, DataDir(m_pData), DataEnd(m_pData));
        }
        m_v3Start = DataStart(m_pData);
        m_v3End = DataEnd(m_pData);
        CKLightningObjectFxData* data = m_pData;
        const float dy = DataStart(data).y - DataEnd(data).y;
        const float dx = DataStart(data).x - DataEnd(data).x;
        const float dz = DataStart(data).z - DataEnd(data).z;
        data->m_unk14 = std::sqrt(ppc::fmadds(dz, dz, ppc::fmadds(dx, dx, dy * dy)));  // Math_Sqrtf 0x10690
    }
    RwFrame* frame = node->m_pRwFrame;
    frame->modelling.pos.x = (m_v3Start.x + m_v3End.x) * 0.5f;  // TOC -0x1d04
    frame->modelling.pos.y = (m_v3Start.y + m_v3End.y) * 0.5f;
    frame->modelling.pos.z = (m_v3Start.z + m_v3End.z) * 0.5f;
    frame->modelling.flags &= 0xfffdffffu;
    RwFrame_MarkDirty(frame);
    float dy = m_v3End.y - m_v3Start.y;
    float dx = m_v3End.x - m_v3Start.x;
    float dz = m_v3End.z - m_v3Start.z;
    const float length = std::sqrt(ppc::fmadds(dz, dz, ppc::fmadds(dx, dx, dy * dy)));  // Math_Sqrtf 0x10690
    if (length != 0.0f) {
        const float inverse = 1.0f / length;
        dz *= inverse;
        dx *= inverse;
        dy *= inverse;
    }
    frame = node->m_pRwFrame;
    frame->modelling.at.x = dx;
    frame->modelling.at.y = dy;
    frame->modelling.at.z = dz;
    frame->modelling.flags &= 0xfffdfffcu;
    RwFrame_MarkDirty(frame);
    const float cx = camera->m_v3RealAxisZ.x;
    const float cz = camera->m_v3RealAxisZ.z;
    const float cy = camera->m_v3RealAxisZ.y;
    const float rz = ppc::fmsubs(cy, dx, cx * dy);
    const float ry = ppc::fmsubs(cx, dz, cz * dx);
    const float rx = ppc::fmsubs(cz, dy, cy * dz);
    frame = node->m_pRwFrame;
    frame->modelling.flags &= 0xfffdfffcu;
    frame->modelling.right.z = rz;
    frame->modelling.right.y = ry;
    frame->modelling.right.x = rx;
    RwFrame_MarkDirty(frame);
    const float uz = ppc::fmsubs(rx, dy, ry * dx);
    const float uy = ppc::fmsubs(rz, dx, rx * dz);
    const float ux = ppc::fmsubs(ry, dz, rz * dy);
    frame = node->m_pRwFrame;
    frame->modelling.flags &= 0xfffdfffcu;
    frame->modelling.up.z = uz;
    frame->modelling.up.y = uy;
    frame->modelling.up.x = ux;
    RwFrame_MarkDirty(frame);
    node->ScaleXYZ(WordAsFloat(m_pData->m_unk10), 1.0f, m_pData->m_unk14);  // 0x000d0d28
    m_fTime = dt + m_fTime;
}
