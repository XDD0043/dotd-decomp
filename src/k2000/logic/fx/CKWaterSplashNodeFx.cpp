// Reconstructed original translation unit: 0x56f2a0-0x56ff60 (GAME_TOC2, main_toc2), 15 functions, 15 live.
// Primary class: CKWaterSplashNodeFx  key 0x3c4c  category Logic  size ?  vtable 0xb2daf8
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x56f2a0  CKWaterSplashNodeFx_Delete  (DOTD_DECLARE_FACTORIES)
//   [x] 0x56f2f0  CKWaterSplashNodeFx_Destroy  (empty)
//   [x] 0x56f2f8  CKWaterSplashNodeFx_RecursiveRegistration
//   [ ] 0x56f3c8  RegisterCKWaterSplashNodeFxClass
//   [ ] 0x56f440  _GLOBAL__I_56f440
//   [x] 0x56f450  CKWaterSplashNodeFx_PostLoad
//   [ ] 0x56f4d0  CKWaterSplashNodeFx_Save
//   [x] 0x56f4f8  CKWaterSplashNodeFx_DeleteArray  (DOTD_DECLARE_FACTORIES)
//   [x] 0x56f5a0  CKWaterSplashNodeFx_Create  (DOTD_DECLARE_FACTORIES)
//   [x] 0x56f5f8  CKWaterSplashNodeFx_Stop
//   [x] 0x56f6b8  CKWaterSplashNodeFx_Start
//   [x] 0x56f6e8  CKWaterSplashNodeFx_CreateArray  (DOTD_DECLARE_FACTORIES)
//   [x] 0x56f7a0  CKWaterSplashNodeFx_TriggerAt_maybe
//   [x] 0x56f9a8  CKWaterSplashNodeFx_Update
//   [x] 0x56fd98  CKWaterSplashNodeFx_Load
//
//   [x] 0x9ca8e8  CKWaterSplashNodeFx_IsKindOfClass  [inline]
//   [x] 0x9ca920  CKWaterSplashNodeFx_GetClassType  [inline]
//   [x] 0x9ca928  CKWaterSplashNodeFx_GetClassID  [inline]
//   [x] 0x9ca930  CKWaterSplashNodeFx_GetFxData  [inline]
//   [x] 0x9ca938  CKWaterSplashNodeFx_SetFxData  [inline]
//   [ ] 0x9ca940  CKWaterSplashNodeFx_DeletingDestruct  [inline]
//   [ ] 0x9ca988  CKWaterSplashNodeFx_Destruct  [inline]
#include "k2000/logic/fx/CKWaterSplashNodeFx.h"

#include "Renderware/rwcore/RwCamera.h"
#include "crt/ppc_ops.h"
#include "k2000/components/CKParticlesCpnt.h"
#include "k2000/geometry/CGeometry.h"
#include "k2000/io/IKFile.h"
#include "k2000/logic/CKSavingManager.h"
#include "k2000/logic/fx/CKSrvFxParticlesAccessor.h"
#include "k2000/logic/fx/CKWaterSplashFxData.h"
#include "k2000/logic/render/CMaterial.h"
#include "k2000/misc/Engine.h"
#include "k2000/scenegraph/CNode.h"
#include "k2000/scenegraph/CSGMovable.h"
#include "k2000/system/IKTime.h"

// 0x0056f2f8 CKWaterSplashNodeFx_RecursiveRegistration: registered with the saving manager (vt+0x24, no owner); for type 0
// the two particle accessors' registrations (+0x1c first; their vt+0x24, no null test).
void CKWaterSplashNodeFx::RecursiveRegistration(int32_t type) {
    g_pEngine->m_pSavingManager->RegisterSerializableObject(this, nullptr);  // vt+0x24
    if (type != 0) return;
    m_pParticles2->RecursiveRegistration(0);
    m_pParticles1->RecursiveRegistration(0);
}

// 0x0056fd98 CKWaterSplashNodeFx_Load: IKNodeFx's; level files then hold the second mesh, the FX flag byte (+0x0c, read
// raw) and the two accessors.
int32_t CKWaterSplashNodeFx::Load(IKFile* file, int32_t type) {
    IKNodeFx::Load(file, type);
    if (type != K_LEVEL_PLATEFORMS) return 1;
    IKFile_ReadRef(file, &m_pMesh2);
    ReadRaw(file, &m_baFxData, 1);
    IKFile_ReadRef(file, &m_pParticles1);
    IKFile_ReadRef(file, &m_pParticles2);
    return 1;
}

// 0x0056f450 CKWaterSplashNodeFx_PostLoad: IKNodeFx's, the node hidden (vt+0x60) and the second mesh too (its flags bit 2).
int32_t CKWaterSplashNodeFx::PostLoad(int32_t type) {
    IKNodeFx::PostLoad(type);
    Vf60();
    if (m_pMesh2 != nullptr) m_pMesh2->m_sgProperties = (m_pMesh2->m_sgProperties & 0xfffffffbu) | 4u;
    return 1;
}

// 0x0056f6b8 CKWaterSplashNodeFx_Start: not stopped, the time 0, not running yet (bit 2: TriggerAt sets it).
void CKWaterSplashNodeFx::Vf64() {
    m_baFxData = static_cast<uint8_t>(m_baFxData & 0xfe);
    m_fTime = 0.0f;
    m_baFxData = static_cast<uint8_t>(m_baFxData & 0xfb);
}

// 0x0056f5f8 CKWaterSplashNodeFx_Stop: stopped, both meshes hidden (the second one, then the node, then vt+0x60 again),
// not running. No null tests.
void CKWaterSplashNodeFx::Stop() {
    m_baFxData = static_cast<uint8_t>((m_baFxData & 0xfe) | 1);
    m_pMesh2->m_sgProperties = (m_pMesh2->m_sgProperties & 0xfffffffbu) | 4u;
    m_pNode->m_sgProperties = (m_pNode->m_sgProperties & 0xfffffffbu) | 4u;
    Vf60();
    m_baFxData = static_cast<uint8_t>(m_baFxData & 0xfb);
}

IKFxData* CKWaterSplashNodeFx::GetFxData() { return reinterpret_cast<IKFxData*>(m_pData); }                 // 0x009ca930
void CKWaterSplashNodeFx::SetFxData(IKFxData* data) { m_pData = static_cast<CKWaterSplashFxData*>(data); }  // 0x009ca938

namespace {
// A movable node's frame moved to `position` (the modelling matrix's position, its flag 0x20000 cleared, the frame
// marked dirty: RwFrame_MarkDirty 0x10698).
void PlaceNode(CNode* node, const CVector3* position) {
    RwFrame* frame = static_cast<CSGMovable*>(static_cast<IKSerializable*>(node))->m_pRwFrame;
    frame->modelling.pos.z = position->z;
    frame->modelling.pos.x = position->x;
    frame->modelling.pos.y = position->y;
    frame->modelling.flags &= 0xfffdffffu;
    RwFrame_MarkDirty(frame);
}

CKParticlesCpnt* ParticlesOf(IKSerializable* accessor) {
    return static_cast<CKParticlesCpnt*>(static_cast<CKSrvFxParticlesAccessor*>(accessor)->m_pParticles);
}

// The alpha store of one geometry (inlined twice in Update; the same as CKElectricArcNodeFx's): `alpha` with blending
// (render flag 11), or opaque without it for a material of modes 1..6 with render flag 12 (or when `alpha` is 0xff).
void SetSplashGeometryAlpha(CGeometry* geometry, uint8_t alpha) {
    uint32_t blended = 0;
    if (alpha != 0xff) {
        blended = 1;
        if ((geometry->m_BitProperties & 0x1000u) != 0) {
            const uint32_t mode = (static_cast<CMaterial*>(geometry->m_pMaterial)->m_baProperties >> 3) & 0xfu;
            if (mode > 0 && mode <= 6) {
                alpha = 0xff;
                blended = 0;
            }
        }
    }
    geometry->m_cGeometryColor[3] = alpha;
    const uint32_t flags = geometry->m_BitProperties;
    if (((flags >> 11) & 1u) != blended) {
        geometry->m_BitProperties = (flags & 0xfffff7ffu) | (blended << 11);
        geometry->UpdateProperties();  // vt+0x60
    }
}

void SetNodeAlpha(CNode* node, uint8_t alpha) {
    for (CGeometry* g = static_cast<CGeometry*>(node->m_lGeometryList); g != nullptr; g = g->m_pNext)
        SetSplashGeometryAlpha(g, alpha);
}
}  // namespace

// 0x0056f7a0 CKWaterSplashNodeFx_TriggerAt_maybe. BUG(original): the second burst is tested with the first accessor's
// component (+0x18's +0x04) but emitted from the second's.
void CKWaterSplashNodeFx::TriggerAt(const CVector3* position, const IKSerializable* owner) {
    if ((m_baFxData & 2) == 0 || m_pOwner != owner) return;
    Vf64();  // vt+0x64 Start
    Vf5C();  // vt+0x5c ShowSceneNode
    m_pMesh2->m_sgProperties &= 0xfffffffbu;
    PlaceNode(m_pNode, position);
    PlaceNode(m_pMesh2, position);
    if (ParticlesOf(m_pParticles1) != nullptr) ParticlesOf(m_pParticles1)->QueueEmission(position, nullptr, nullptr);
    if (ParticlesOf(m_pParticles1) != nullptr) ParticlesOf(m_pParticles2)->QueueEmission(position, nullptr, nullptr);
    m_baFxData = static_cast<uint8_t>(m_baFxData | 4);
}

// 0x0056f9a8 CKWaterSplashNodeFx_Update: while running (bit 2) the time advances by the scaled game time (IKTime +0x1c);
// at the data's duration (+0x08; ble: an unordered duration stops) Stop (vt+0x6c), else both meshes are scaled (width,
// mesh height, width: CSGMovable_SetScaleXYZ_maybe) and every geometry of both takes the curve's alpha.
void CKWaterSplashNodeFx::Update(IKTime* frameClock) {
    if ((m_baFxData & 4) == 0) return;
    const float t = m_fTime + frameClock->m_afDeltaTime[IKTime::SCALABLE_GAME_TIME];
    m_fTime = t;
    if (!(m_pData->m_unk08 > t)) {
        Stop();  // vt+0x6c
        return;
    }
    const float width = m_pData->EvalWidthScale(t);
    const float height1 = m_pData->EvalMesh1HeightScale(m_fTime);
    const float height2 = m_pData->EvalMesh2HeightScale(m_fTime);
    static_cast<CSGMovable*>(static_cast<IKSerializable*>(m_pNode))->SetScaleXYZ(width, height1, width);
    static_cast<CSGMovable*>(static_cast<IKSerializable*>(m_pMesh2))->SetScaleXYZ(width, height2, width);
    const uint8_t alpha = static_cast<uint8_t>(ppc::fctiwz(m_pData->EvalAlpha(m_fTime)));
    SetNodeAlpha(m_pNode, alpha);
    SetNodeAlpha(m_pMesh2, alpha);
}
