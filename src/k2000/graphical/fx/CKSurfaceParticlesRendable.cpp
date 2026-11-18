// CKSurfaceParticlesRendable.cpp - reconstructed original translation unit 0xc2bf8-0xc4048 (GAME_TOC1, main_toc1), 27 functions, 20 live.
// Primary class: CKSurfaceParticlesRendable  key 0xe0d  category Graphical  size 0x24  vtable 0xb17b58
// Other owners: CMaterialEffectData (2), DrawSurfaceParticleGeometry (1), SurfaceParticles (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0xc2bf8  CKSurfaceParticlesRendable_Delete
//   [x] 0xc2c48  CKSurfaceParticlesRendable_vf58  (UpdateAndExtract)
//   [ ] 0xc2ca0  RegisterCKSurfaceParticlesRendableClass
//   [ ] 0xc2d18  _GLOBAL__I_c2d18
//   [x] 0xc2d28  CKSurfaceParticlesRendable_RecursiveRegistration  (CKSurfaceParticlesRendable.h)
//   [x] 0xc2d50  CKSurfaceParticlesRendable_Destroy  (CKSurfaceParticlesRendable.h)
//   [x] 0xc2d78  CKSurfaceParticlesRendable_DeleteArray
//   [x] 0xc2e20  CKSurfaceParticlesRendable_Create
//   [x] 0xc2e78  DrawSurfaceParticleGeometry
//   [x] 0xc3398  CKSurfaceParticlesRendable_CreateArray
//   [x] 0xc3450  CKSurfaceParticlesRendable_PostLoad
//   [x] 0xc3478  CKSurfaceParticlesRendable_Load
//   [ ] 0xc3570  CKSurfaceParticlesRendable_Save
//   [x] 0xc3678  KStub_Nop_c3678  (CMaterialEffectData_Release, CKSurfaceParticlesRendable.h)
//   [x] 0xc3680  CMaterialEffectData_LevelReset_maybe  (CMaterialEffectData_RecursiveRegistration)
//   [x] 0xc3728  KStub_Nop_c3728  (CMaterialEffectData_PostLoad, CKSurfaceParticlesRendable.h)
//   [x] 0xc3730  CKSurfaceParticlesRendable_GetFadeInAlpha_maybe
//   [x] 0xc3788  CKSurfaceParticlesRendable_GetFadeOutAlpha_maybe
//   [x] 0xc37e0  SurfaceParticles_ComputeDistanceFade_maybe
//   [ ] 0xc3878  KStub_Nop_c3878  [dead]
//   [ ] 0xc3880  CKSurfaceParticlesRendable_SetFadeStart_maybe  [dead]
//   [ ] 0xc38a8  CKSurfaceParticlesRendable_SetFadeEnd_maybe  [dead]
//   [ ] 0xc38d0  FUN_000c38d0  [dead]
//   [ ] 0xc3a70  FUN_000c3a70  [dead]
//   [x] 0xc3b28  CMaterialEffectData_Load_maybe  (logic/render/CMaterial.cpp CMaterialEffectData_Load)
//   [ ] 0xc3d70  FUN_000c3d70  [dead]
//   [ ] 0xc3e38  FUN_000c3e38  [dead]
//
//   [ ] 0x9a1bc0  CKSurfaceParticlesRendable_GetClassType  [inline]
//   [ ] 0x9a1bc8  CKSurfaceParticlesRendable_GetClassID  [inline]
//   [ ] 0x9a1bd0  CKSurfaceParticlesRendable_IsKindOfClass  [inline]
//   [ ] 0x9a1bf8  CKSurfaceParticlesRendable_DeletingDestructor  [inline]
//   [ ] 0x9a1c40  CKSurfaceParticlesRendable_Destructor  [inline]
#include "k2000/graphical/fx/CKSurfaceParticlesRendable.h"

#include <cstring>

#include "Renderware/rpworld/RpAtomic.h"
#include "Renderware/rpworld/RpGeometry.h"
#include "Renderware/rwcore/RwCamera.h"
#include "Renderware/rwcore/RwIm3D.h"
#include "crt/ppc_ops.h"
#include "k2000/cameras/CameraContext.h"
#include "k2000/geometry/CGeometry.h"
#include "k2000/io/IKFile.h"
#include "k2000/logic/render/CMaterial.h"
#include "k2000/managers/CKGraphic.h"
#include "k2000/math/CMatrix34.h"
#include "k2000/math/ConvertRwMatrixToHomogeneous4x4.h"
#include "k2000/misc/Engine.h"
#include "k2000/misc/Mat4.h"
#include "k2000/render/CRenderer.h"
#include "k2000/render/CShaderManagerPSGL.h"
#include "k2000/render/MeshShaderPassState.h"
#include "k2000/render/ShaderMatrixCache.h"

namespace {

float WordF(uint32_t w) {
    float f;
    std::memcpy(&f, &w, 4);
    return f;
}

// 0x000c3730 CKSurfaceParticlesRendable_GetFadeInAlpha_maybe(data, distance): 0 up to the start (+0x10, start >= d),
// 255 from the end (+0x14, d >= end), between them (d - start) / (end - start) x 255.0f (TOC -0x57d4), fctiwz, low byte.
uint32_t GetFadeInAlpha(const CMaterialEffectData* data, float distance) {
    const float start = WordF(data->m_unk10);
    if (start >= distance) return 0;
    const float end = WordF(data->m_unk14);
    if (distance >= end) return 0xff;
    return static_cast<uint32_t>(ppc::fctiwz(((distance - start) / (end - start)) * 255.0f)) & 0xff;
}

// 0x000c3788 CKSurfaceParticlesRendable_GetFadeOutAlpha_maybe: 255 up to the start, 0 from the end, between them
// (end - d) / (end - start) x 255.0f.
uint32_t GetFadeOutAlpha(const CMaterialEffectData* data, float distance) {
    const float start = WordF(data->m_unk10);
    if (start >= distance) return 0xff;
    const float end = WordF(data->m_unk14);
    if (distance >= end) return 0;
    return static_cast<uint32_t>(ppc::fctiwz(((end - distance) / (end - start)) * 255.0f)) & 0xff;
}

// 0x000c37e0 SurfaceParticles_ComputeDistanceFade_maybe: the PTank's constant tex coords (u0, v0, u1, v1): (0, 0, 1, 1)
// up to the start, (0.5, 0.5, 0.5, 0.5) from the end, between them the square 0.5 -+ 0.5 / ((end - d) / (end - start)
// + 0.0001) (TOC -0x57cc 0x38d1b717) around the centre.
void ComputeDistanceFade(const CMaterialEffectData* data, float distance, float out[4]) {
    const float start = WordF(data->m_unk10);
    if (start >= distance) {
        out[0] = 0.0f;
        out[1] = 0.0f;
        out[2] = 1.0f;
        out[3] = 1.0f;
        return;
    }
    const float end = WordF(data->m_unk14);
    if (!(distance < end)) {
        out[0] = 0.5f;
        out[1] = 0.5f;
        out[2] = 0.5f;
        out[3] = 0.5f;
        return;
    }
    const float half = 0.5f / ((end - distance) / (end - start) + 9.99999975e-05f);
    const float high = half + 0.5f;
    const float low = 0.5f - half;
    out[0] = low;
    out[2] = high;
    out[1] = low;
    out[3] = high;
}

}  // namespace

// 0x000c2e78 DrawSurfaceParticleGeometry. The distance of the owner atomic's world sphere centre along the main camera's
// at axis (fmuls + 2 fmadds) beyond the data's +0x14: nothing. Else the particle geometry (+0x08 of the data) gets the
// owner's world sphere as its atomic's sphere (resynced first when dirty; dirty bit cleared, world bound marked), with
// the shader pipelines the owner's frame LTM as the mesh passes' world matrix (0x00c68314) and the cache's world
// cleared; the main camera's right and up axes are put into the owner frame's space for the draw (the PTank billboards
// read them) and restored after it; the PTank's constant colour is the rendable's four bytes (+0x20); then by the fade
// mode (+0x0c): 2 the alpha times the fade-out alpha / 255, 3 the constant tex coords by the distance fade (changed
// flag 0x80000), 1 under pushed render states an alpha test (function 5, greater) with the fade-in alpha as reference
// (PS3 state 0x20); the geometry drawn (vt+0x5c). With the shader pipelines the owner's matrix becomes the cache's world
// and the override is cleared at the end.
void CKSurfaceParticlesRendable::Render(IKTime* frameClock) {
    CameraContext* context = g_pEngine->m_graphic->m_renderer->m_cameraContext;
    RwMatrix* camera = RwFrameGetLTM(RwCameraGetFrame(context->m_pMainCamera));  // 0x00c5c9cc, BridgeRwGetFrameLocalToWorldMatrix
    RpAtomic* owner = static_cast<CGeometry*>(m_pOwner)->m_pRpAtomic;
    const float* sphere = owner->worldSphere;  // +0x2c
    const float dy = sphere[1] - camera->pos.y;
    const float dx = sphere[0] - camera->pos.x;
    const float dz = sphere[2] - camera->pos.z;
    const float radius = sphere[3];
    const float distance = ppc::fmadds(dz, camera->at.z, ppc::fmadds(dx, camera->at.x, dy * camera->at.y));
    const CMaterialEffectData* data = m_unk18;
    if (!(WordF(data->m_unk14) >= distance)) return;  // bge

    CGeometry* geometry = static_cast<CGeometry*>(data->m_pRef8);
    RwMatrix* ownerLtm = RwFrameGetLTM(owner->frame);
    RpAtomic* atomic = geometry->m_pRpAtomic;
    RpPTankData* ptank = atomic->ptank;
    if ((atomic->flags & 2) != 0) {
        _rpAtomicResyncInterpolatedSphere(atomic);  // BridgeRwUpdateAtomicMorphBoundingSphere
        atomic = geometry->m_pRpAtomic;
    }
    atomic->boundingSphere[0] = sphere[0];
    atomic->boundingSphere[1] = sphere[1];
    atomic->boundingSphere[2] = sphere[2];
    atomic->boundingSphere[3] = radius;
    geometry->m_pRpAtomic->flags &= 0xfffffffdu;
    geometry->m_pRpAtomic->privateFlags |= 1;
    Homogeneous4x4 world;  // sp+0xe0
    Homogeneous4x4_Construct(&world);
    const bool shaders = g_pShaderManager->m_bShadersEnabled != 0;  // +0x44
    if (shaders) {
        MeshShaderPass_SetWorldMatrixOverride(ownerLtm);
        ConvertRwMatrixToHomogeneous4x4(&world, ownerLtm);
        ShaderMatrixCache_SetWorld4x4(nullptr);  // +0x60
    }
    const RwV3d savedRight = camera->right;  // sp+0x7c
    const RwV3d savedUp = camera->up;        // sp+0x70
    CMatrix34 inverse;  // sp+0xa0
    Mat4_Invert(&inverse, reinterpret_cast<const CMatrix34*>(ownerLtm));
    Mat4_TransformVectors(&inverse, reinterpret_cast<CVector3*>(&camera->right),
                          reinterpret_cast<const CVector3*>(&savedRight), 1);
    Mat4_TransformVectors(&inverse, reinterpret_cast<CVector3*>(&camera->up), reinterpret_cast<const CVector3*>(&savedUp),
                          1);
    std::memcpy(ptank->colorCC, m_unk20, 4);
    const uint32_t mode = m_unk18->m_unkC;
    if (mode == 2) {
        const uint32_t alpha = GetFadeOutAlpha(m_unk18, distance);
        ptank->colorCC[3] = static_cast<uint8_t>(((alpha & 0xff) * m_unk20[3] & 0xffff) / 0xff);  // the 0x80808081 multiply
        geometry->Render(frameClock);  // vt+0x5c
    } else if (mode == 3) {
        float uv[4];
        ComputeDistanceFade(m_unk18, distance, uv);
        RpPTankData* tank = geometry->m_pRpAtomic->ptank;
        std::memcpy(tank->texCoordsE0, uv, sizeof uv);
        geometry->m_pRpAtomic->ptank->flags40 |= 0x80000;
        geometry->Render(frameClock);
    } else if (mode == 1) {
        const uint32_t alpha = GetFadeInAlpha(m_unk18, distance);
        PushRenderStates(g_pRenderStateRenderer);
        RwRenderStateSet(rwRENDERSTATEALPHATESTFUNCTION, reinterpret_cast<void*>(static_cast<intptr_t>(5)));
        RwRenderStateSet(rwRENDERSTATEALPHATESTFUNCTIONREF, reinterpret_cast<void*>(static_cast<intptr_t>(alpha & 0xff)));
        geometry->Render(frameClock);
        PopRenderStates(g_pRenderStateRenderer);
    } else {
        geometry->Render(frameClock);
    }
    camera->right = savedRight;
    camera->up = savedUp;
    if (g_pShaderManager->m_bShadersEnabled != 0) {
        ShaderMatrixCache_SetWorld4x4(&world);
        MeshShaderPass_SetWorldMatrixOverride(nullptr);
    }
    // KStub_Nop_2471d0: the 4x4's destructor.
}

// 0x000c3478 CKSurfaceParticlesRendable_Load
int32_t CKSurfaceParticlesRendable::Load(IKFile* file, int32_t type) {
    IRendableObject::Load(file, type);  // 0xa7258
    if (type == K_LEVEL_PLATEFORMS) {
        IKFile_ReadRef(file, &m_pOwner);
        ReadRaw(file, m_unk20, 4);  // not swapped
    }
    return 1;
}

// 0x000c3450 CKSurfaceParticlesRendable_PostLoad
int32_t CKSurfaceParticlesRendable::PostLoad(int32_t type) {
    if (type != K_LEVEL_PLATEFORMS) return 1;
    const CGeometry* geometry = static_cast<const CGeometry*>(m_pOwner);
    m_unk18 = static_cast<const CMaterial*>(geometry->m_pMaterial)->m_pEffectData;
    return 1;
}

// C2.8 port-all P08.

// 0x000c2c48 CKSurfaceParticlesRendable_UpdateAndExtract
void CKSurfaceParticlesRendable::UpdateAndExtract(float /*maxDistanceSquared*/, RenderQueue** stages, IKTime* /*frameClock*/,
                                                  RwCamera* /*camera*/, int32_t /*distanceCull*/) {
    stages[m_BitProperties & 0x1f]->Add(this);  // vt+0x00
}

// 0x000c3680 CMaterialEffectData_LevelReset_maybe
void CMaterialEffectData_RecursiveRegistration(CMaterialEffectData* data, int32_t type) {
    if (data->m_pRef4 != nullptr) data->m_pRef4->RecursiveRegistration(type);  // vt+0x24
    if (data->m_pRef8 != nullptr) data->m_pRef8->RecursiveRegistration(type);
}
