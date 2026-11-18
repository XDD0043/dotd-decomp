// CGeometry.cpp - reconstructed original translation unit 0x87f78-0x89688 (GAME_TOC1, main_toc1), 25 functions, 23 live.
// Primary class: CGeometry  key 0x8a  category Geometry  size 0x30  vtable 0xb129c8
// Other owners: ParticleDraw (1), GetGeometryWorldBoundingSphere (1), PrepareAndEnqueueGeometry (1), DrawGeometryAtomicWithRenderState (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x87f78  CGeometry_Delete  (DOTD_DECLARE_FACTORIES)
//   [x] 0x87fc8  CGeometry_RecursiveRegistration  (CGeometry.h)
//   [ ] 0x88020  CGeometry_Save
//   [x] 0x88028  CGeometry_SetBlendMode
//   [ ] 0x88098  CGeometry_UpdateRenderStageBits_maybe  [dead]
//   [x] 0x88170  CGeometry_vf84
//   [x] 0x88190  ParticleDraw_SetShaderParticleFlags_maybe
//   [ ] 0x88220  RegisterCGeometryClass
//   [ ] 0x88298  _GLOBAL__I_88298
//   [x] 0x882a8  CGeometry_vf80
//   [x] 0x88340  CGeometry_UpdateBoundingSphere_maybe
//   [x] 0x88398  GetGeometryWorldBoundingSphere
//   [x] 0x88530  CGeometry_UnlockGeometry_maybe
//   [x] 0x88570  CGeometry_Destroy
//   [x] 0x885c8  CGeometry_DeleteArray  (DOTD_DECLARE_FACTORIES)
//   [x] 0x88670  CGeometry_Create
//   [x] 0x886d8  PrepareAndEnqueueGeometry
//   [x] 0x889f8  CGeometry_GetMaterialRenderInfo
//   [ ] 0x88a58  FUN_00088a58  [dead]
//   [x] 0x88b28  CGeometry_ComputeSortKey
//   [x] 0x88bc8  CGeometry_CreateArray
//   [x] 0x88c90  CGeometry_PostLoad
//   [x] 0x88e28  DrawGeometryAtomicWithRenderState
//   [x] 0x89138  CGeometry_ComputeRenderStage
//   [x] 0x892a0  CGeometry_Load
//
//   [ ] 0x990c30  CGeometry_IsKindOfClass  [inline]
//   [ ] 0x990c58  CGeometry_GetClassType  [inline]
//   [ ] 0x990c60  CGeometry_GetClassID  [inline]
//   [ ] 0x990c68  CGeometry_GetSerializationFlags  [inline]
//   [ ] 0x990c70  CGeometry_vf88  [inline]
//   [ ] 0x990c78  KStub_Nop_990c78  [inline]
//   [ ] 0x990c80  KStub_Nop_990c80  [inline]
//   [ ] 0x990c88  KStub_Nop_990c88  [inline]
//   [ ] 0x990c90  KStub_Nop_990c90  [inline]
//   [ ] 0x990c98  KStub_Nop_990c98  [inline]
//   [ ] 0x990ca0  KStub_Nop_990ca0  [inline]
//   [x] 0x990d90  CGeometry_DeletingDestructor  [inline]
//   [x] 0x990df8  CGeometry_Destructor  [inline]
#include "k2000/geometry/CGeometry.h"
#include "k2000/services/CKSrvShadow.h"

#include <mutex>

#include "Renderware/rpworld/RpAtomic.h"
#include "Renderware/rpworld/RpGeometry.h"
#include "Renderware/rwcore/RwStream.h"
#include "k2000/core/Stub.h"
#include "k2000/io/IKFile.h"
#include "k2000/logic/render/CMaterial.h"
#include "Renderware/rwcore/RwCamera.h"
#include "Renderware/rwcore/RwIm3D.h"
#include "k2000/cameras/CameraContext.h"
#include "k2000/misc/Engine.h"
#include "k2000/render/CRenderer.h"
#include "k2000/render/MeshShaderPassState.h"
#include "k2000/scenegraph/CSGMovable.h"
#include "k2000/scenegraph/CNode.h"
#include "k2000/system/LwMutex.h"

namespace {
sys_lwmutex_t g_renderLock;  // 0x00cf9c90
std::once_flag g_renderLockOnce;
}  // namespace

// STUB: the original creates the lock during engine start-up (CKObjectManager); here on first use (once,
// whichever thread gets there first).
void RenderLock_Lock() {
    std::call_once(g_renderLockOnce, [] { LwMutex_Create(&g_renderLock); });
    LwMutex_Lock(&g_renderLock);
}

void RenderLock_Unlock() { LwMutex_Unlock(&g_renderLock); }

// 0x00088670 CGeometry_Create (the constructor is inlined there): +0x0c, +0x20, +0x28 and +0x2c are left
// as they are.
CGeometry::CGeometry() {
    m_pNextAccumulatedObject = nullptr;
    m_BitProperties = 0;
    m_pPriorityParent = 0;
    m_pLightSet = nullptr;
    m_pMaterial = nullptr;
    m_pNext = nullptr;
    m_pRpAtomic = nullptr;
}

// 0x00088530 CGeometry_UnlockGeometry_maybe (RpGeometryUnlock through its TocBridge)
int32_t CGeometry::UnlockGeometry() { return RpGeometryUnlock(m_pRpAtomic->geometry) != nullptr ? 1 : 0; }

// 0x00088170 CGeometry_FindRpGeometry
void* CGeometry::FindRpGeometry() { return m_pRpAtomic != nullptr ? m_pRpAtomic->geometry : nullptr; }

// 0x00088570 CGeometry_Destroy
void CGeometry::Destroy() {
    IRendableObject::Destroy();  // 0xa7248
    if (m_pRpAtomic != nullptr) {
        RpAtomicDestroy(m_pRpAtomic);
        m_pRpAtomic = nullptr;
    }
    m_pMaterial = nullptr;
}

// 0x000892a0 CGeometry_Load
int32_t CGeometry::Load(IKFile* file, int32_t type) {
    if (type != K_LEVEL_PLATEFORMS) return 1;
    IRendableObject::Load(file, K_LEVEL_PLATEFORMS);
    IKFile_ReadRef(file, &m_pNext);
    IKFile_ReadRef(file, &m_pMaterial);
    IKFile_ReadRef(file, &m_unk2c);
    ReadRaw(file, m_cGeometryColor, 4);
    if ((m_BitProperties & 0x4000) == 0) {
        uint8_t streamed = 0;
        ReadRaw(file, &streamed, 1);
        if (streamed == 0) {
            // Another geometry's atomic, cloned (a forward reference still has its constructor's null).
            CGeometry* source = nullptr;
            IKFile_ReadRef(file, &source);
            m_pRpAtomic = RpAtomicClone(source->m_pRpAtomic);
        } else {
            uint32_t length = 0;
            RwStreamFindChunk(file->m_pRwStream, 0x14, &length, nullptr);
            m_pRpAtomic = RpAtomicStreamRead(file->m_pRwStream);  // 0x69ff28
        }
    } else {
        m_pRpAtomic = nullptr;
    }
    // Four bytes into property bits 22, 23, 25, 24 (as in the original, a byte above 1 would also set
    // the bits above).
    uint8_t bit = 0;
    ReadRaw(file, &bit, 1);
    m_BitProperties = (m_BitProperties & 0xffbfffffu) | (static_cast<uint32_t>(bit) << 22);
    ReadRaw(file, &bit, 1);
    m_BitProperties = (m_BitProperties & 0xff7fffffu) | (static_cast<uint32_t>(bit) << 23);
    ReadRaw(file, &bit, 1);
    m_BitProperties = (m_BitProperties & 0xfdffffffu) | (static_cast<uint32_t>(bit) << 25);
    ReadRaw(file, &bit, 1);
    m_BitProperties = (m_BitProperties & 0xfeffffffu) | (static_cast<uint32_t>(bit) << 24);
    return 1;
}

// 0x000882a8 CGeometry_vf80: the shader flag byte (+0x28): 1 for a geometry that receives shadows (render flag 23) when the
// shadow service has the mode enabled (CKSrvShadow_IsShadowModeEnabled_maybe 0x1fb988: 0 world, 1 and 2 as the callers pass)
// and the geometry asks for the sector's shadow texture (render flag 24), else 0.
void CGeometry::Vf80(int32_t mode) {
    const CKSrvShadow* shadow = static_cast<const CKSrvShadow*>(g_pEngine->m_srvShadow);
    if ((m_BitProperties & 0x800000) != 0 && shadow->IsShadowModeEnabled(mode) != 0 && (m_BitProperties & 0x1000000) != 0) {
        SetShaderFlag(1);
        return;
    }
    SetShaderFlag(0);
}

// 0x00088c90 CGeometry_PostLoad. First CGeometry_SetupMaterialShader_maybe 0xbb828 (CMaterial.cpp) with the material's
// shader mode: with the shader manager's atomic pipeline (+0x45, +0x04) TryAssignOverride answers 1 for every atomic, a
// skinned one keeping the skin pipeline its stream chose (Renderware/rpskin/RpSkin.cpp), the others taking the manager's
// pipeline (a tag: RpAtomicPSGL_Render draws every streamed atomic).
int32_t CGeometry::PostLoad(int32_t type) {
    CMaterial* material = static_cast<CMaterial*>(m_pMaterial);
    const uint32_t mode = (material->m_baProperties >> 3) & 0xf;
    CGeometry_SetupMaterialShader(m_pRpAtomic, static_cast<int32_t>(mode));  // 0x000bb828 (the word's bits 3-6)
    if (type == 0 && mode - 10u < 5u && m_pRpAtomic != nullptr && m_pRpAtomic->geometry != nullptr) {  // CMaterial_IsMode10To14_maybe
        m_pRpAtomic->geometry->flags |= 0x200;  // the tangent flag
    }
    if (m_unk2c != nullptr) m_unk2c->PostLoad(type);  // the auxiliary geometry (vt+0x30)
    if (((m_BitProperties >> 8) & 3) == 2) m_BitProperties &= 0xfdffffffu;
    if ((m_BitProperties & 0x80000) != 0) {
        Vf80(0);
        return 1;
    }
    Vf80(2);
    return 1;
}

namespace {
// The stage table 0x00c296b8: 4 layers (render flag bits 17-18) x 8 variants. Layer 0 is the world (5 opaque, 6 cutout,
// 7 / 8 blended with a forced sort, 9 early blend, 12 late blend, 13 / 14 particles), layer 1 the overlay (2D camera),
// layers 2 and 3 the background (far camera).
const uint32_t kStageTable[32] = {5, 6, 7, 8, 9, 12, 13, 14, 19, 20, 20, 20, 21, 21, 21, 21,
                                  1, 2, 3, 3, 4, 4, 4, 4, 1, 0, 2, 3, 4, 1, 0, 3};
}  // namespace

// 0x00089138 CGeometry_UpdateProperties (XXL2 UpdateProperties): the blend mode bits (8-9) and the stage in bits 0-4.
void CGeometry::UpdateProperties() {
    const CMaterial* material = static_cast<CMaterial*>(m_pMaterial);
    const uint32_t before = m_BitProperties;
    uint32_t extra = 0;
    bool direct = false;
    if ((before & 0x1800) != 0 || (material->m_baProperties & 1) != 0) {
        const uint32_t blend = (before >> 8) & 3;
        extra = 0x100;
        if (blend != 0) {
            m_BitProperties = (before & 0xfffffcffu) | (blend << 8);
            direct = true;
        }
    }
    if (!direct) m_BitProperties = (before & 0xfffffcffu) | extra;
    const uint32_t cur = m_BitProperties;
    if ((before & 0x20) != 0) return;
    const uint32_t layer = (cur >> 17) & 3;
    uint32_t variant = 0;
    if (((cur >> 8) & 3) != 0) {
        variant = ((cur & 0x80000) == 0 ? 1u : 0u) + 2;
        if ((cur & 0x2000) == 0) {
            if ((cur & 0x1a00) != 0 || (material->m_baProperties & 2) != 0) {
                m_BitProperties = kStageTable[layer * 8 + ((cur & 0x80000) == 0 ? 1u : 0u) + 4] | (m_BitProperties & 0xffffffe0u);
                return;
            }
            variant = 1;
        }
    }
    m_BitProperties = kStageTable[layer * 8 + variant] | (m_BitProperties & 0xffffffe0u);
}

// 0x00088028 CGeometry_SetBlendMode
void CGeometry::SetBlendMode(uint32_t blendMode) {
    if (blendMode != ((m_BitProperties >> 8) & 3)) {
        m_BitProperties = (m_BitProperties & 0xfffffcffu) | (blendMode << 8);
        UpdateProperties();  // vt+0x60
    }
}

// 0x000889f8 CGeometry_GetMaterialRenderInfo
void CGeometry::GetRenderingProperties(uint8_t* first, uint8_t* second, uint8_t* third, uint32_t* blendMode) {
    const CMaterial* material = static_cast<CMaterial*>(m_pMaterial);
    uint8_t zWrite = 1;
    if ((m_BitProperties & 0x1a00) == 0) zWrite = static_cast<uint8_t>((material->m_baProperties >> 1) & 1);
    *first = zWrite;
    *second = m_cGeometryColor[3];
    *third = (material->m_baProperties & 3) == 1 ? 1 : 0;
    *blendMode = (m_BitProperties >> 8) & 3;
}

// 0x00088b28 CGeometry_ComputeSortingCoef
void CGeometry::ComputeSortingCoef(int32_t /*sortingOrder*/) {
    if ((m_BitProperties & 0x2000) != 0) {
        m_fSortingCoef = static_cast<float>((m_BitProperties >> 26) & 7);
        return;
    }
    const RpAtomic* atomic = m_pRpAtomic;
    const CameraContext* context = static_cast<const CameraContext*>(g_pEngine->m_cameraContext);
    const RwFrame* frame = static_cast<const CSGMovable*>(context->m_pCamera)->m_pRwFrame;
    const float dy = frame->modelling.pos.y - atomic->worldSphere[1];
    const float dx = frame->modelling.pos.x - atomic->worldSphere[0];
    const float dz = frame->modelling.pos.z - atomic->worldSphere[2];
    m_fSortingCoef = (dz * dz + dx * dx + dy * dy) * g_pRenderStateRenderer->m_fInvFarSquared;
}

// 0x00088190 ParticleDraw_SetShaderParticleFlags_maybe: bit 1 from render flag 25 (rldicl 39 / slwi 1 over the cleared
// bit), bit 2 set or cleared by render flag 0x100000, bit 0 cleared and or'ed with the byte +0x28.
void ParticleDraw_SetShaderParticleFlags(const CGeometry* geometry) {
    ShaderSceneInputs& scene = SceneInputs();
    uint32_t flags = scene.managerFlags;
    flags = (flags & ~2u) | (((geometry->m_BitProperties >> 25) & 1u) << 1);
    flags = (geometry->m_BitProperties & 0x100000) != 0 ? (flags | 4u) : (flags & ~4u);
    flags = (flags & ~1u) | geometry->ShaderFlag();
    scene.managerFlags = flags;
}

// 0x00088e28 CGeometry_Render. g_ShaderManagerPSGL +0x8c (SceneInputs().managerFlags): bit 1 point lights = render
// flag 25, bit 2 far texture = render flag 20, bit 0 shadow textures = the shader flag byte. The fog render state (RW
// state 0xe) stays on only for geometries with render flag 22. The geometry's colour goes into the RW material (the
// shader reads it as the material colour). A material with property 0x8000 draws the atomic once per alpha reference of
// its 8 raw bytes (+0x2c, the count at +0x33) with the alpha test on and depth write on, culling off and the render
// states restored afterwards.
void CGeometry::Render(IKTime* /*frameClock*/) {
    ShaderSceneInputs& scene = SceneInputs();
    uint32_t flags = scene.managerFlags;
    flags = (flags & ~2u) | (((m_BitProperties >> 25) & 1u) << 1);
    flags = (m_BitProperties & 0x100000) != 0 ? (flags | 4u) : (flags & ~4u);
    flags = (flags & ~1u) | ShaderFlag();
    scene.managerFlags = flags;
    int32_t fog = 0;
    RwRenderStateGet(rwRENDERSTATEFOGENABLE, &fog);
    int32_t newFog = 0;
    if ((m_BitProperties & 0x400000) != 0) newFog = (fog == 1) ? 1 : 0;
    RwRenderStateSet(rwRENDERSTATEFOGENABLE, reinterpret_cast<void*>(static_cast<intptr_t>(newFog)));
    CMaterial* material = static_cast<CMaterial*>(m_pMaterial);
    RpMaterial* rpMaterial = material->m_pRpMaterial;
    rpMaterial->color.red = m_cGeometryColor[0];
    rpMaterial->color.green = m_cGeometryColor[1];
    rpMaterial->color.blue = m_cGeometryColor[2];
    rpMaterial->color.alpha = m_cGeometryColor[3];
    if ((material->m_baProperties & 0x8000) == 0) {
        m_pRpAtomic->renderCallBack(m_pRpAtomic);
    } else {
        PushRenderStates(g_pRenderStateRenderer);
        RwRenderStateSet(rwRENDERSTATECULLMODE, reinterpret_cast<void*>(1));
        RwRenderStateSet(rwRENDERSTATEZTESTENABLE, reinterpret_cast<void*>(1));
        RwRenderStateSet(rwRENDERSTATEZWRITEENABLE, reinterpret_cast<void*>(1));
        RwRenderStateSet(rwRENDERSTATEALPHATESTFUNCTION, reinterpret_cast<void*>(5));
        const uint8_t count = material->m_FXParameters.m_aui8Raw2c[7];  // +0x33
        for (uint8_t i = 0; i < count; ++i) {
            RwRenderStateSet(rwRENDERSTATEALPHATESTFUNCTIONREF,
                             reinterpret_cast<void*>(static_cast<intptr_t>(material->m_FXParameters.m_aui8Raw2c[i])));
            m_pRpAtomic->renderCallBack(m_pRpAtomic);
        }
        PopRenderStates(g_pRenderStateRenderer);
    }
    RwRenderStateSet(rwRENDERSTATEFOGENABLE, reinterpret_cast<void*>(static_cast<intptr_t>(fog)));
}

// 0x000886d8 PrepareAndEnqueueGeometry (CGeometry_UpdateAndExtract, vt+0x58). The material (+0x24) with
// property 0x100 runs its per-frame update once per frame (+0x10 = the frame counter; the handler of
// 0x00c4b0cc indexed by bits 3-6). With `distanceCull` the geometry is dropped beyond the distance from the
// current camera. Then, when it has something to draw (vt+0x88): the auxiliary geometry (+0x2c) queued
// too, and this one in the stage of its render flags' bits 0-4; materials of type 7 / 8 (bits 3-6) go to
// stage 16 after the object their shared state names (CMaterial's static at 0x00c5d280, its +4 handle: the
// distortion effect) is extracted itself (its vt+0x58 with no distance cull).
void CGeometry::EnqueueVisible(float maxDistanceSquared, RenderQueue** stages, IKTime* frameClock, RwCamera* camera,
                               int32_t distanceCull) {
    CMaterial* material = static_cast<CMaterial*>(m_pMaterial);
    if ((material->m_baProperties & 0x100) != 0 && material->m_ui16UpdateFrameCounter != g_ui16RenderFrameCounter) {
        material->m_ui16UpdateFrameCounter = g_ui16RenderFrameCounter;
        // The table 0x00c4b0cc (8 bytes per shader mode) has an entry for modes 5, 6, 12 and 14 only: all
        // four are MatFXUVAnim_UpdateMaterial_maybe 0xbd228 with this adjustment 0.
        const uint32_t mode = (material->m_baProperties >> 3) & 0xf;
        if (mode == 5 || mode == 6 || mode == 12 || mode == 14) material->UpdateUVAnimation(frameClock);
    }
    if (distanceCull != 0) {
        // The scene camera's position (renderer +0x28 -> the IKCamera's frame) against the atomic's world sphere centre.
        const CameraContext* context = g_pRenderStateRenderer->m_cameraContext;
        const RwMatrix* pose = RwFrameGetLTM(static_cast<const CSGMovable*>(context->m_pCamera)->m_pRwFrame);
        const float dy = pose->pos.y - m_pRpAtomic->worldSphere[1];
        const float dx = pose->pos.x - m_pRpAtomic->worldSphere[0];
        const float dz = pose->pos.z - m_pRpAtomic->worldSphere[2];
        if (maxDistanceSquared < dz * dz + dx * dx + dy * dy) return;
    }
    if (HasParticlesToDraw() == 0) return;
    if (m_unk2c != nullptr) {
        static_cast<CGeometry*>(m_unk2c)->EnqueueVisible(0.0f, stages, frameClock, camera, 0);  // TOC -0x6700: 0.0f
    }
    const uint32_t type = (material->m_baProperties >> 3) & 0xf;
    if (type == 8 || type == 7) {
        // BUG(original): no null check of the handle (every mode 7 / 8 material loads it).
        static_cast<IRendableObject*>(CMaterial::s_sharedState.m_pRef)
            ->UpdateAndExtract(0.0f, stages, frameClock, camera, 0);  // TOC -0x6700: 0.0f
        stages[0x10]->Add(this);
        return;
    }
    stages[m_BitProperties & 0x1f]->Add(this);
}

// 0x00088340 CGeometry_UpdateBoundingSphere_maybe (vt+0x7c; the RW call through the bridge 0x98e090)
void CGeometry::UpdateBoundingSphere() {
    _rpAtomicResyncInterpolatedSphere(m_pRpAtomic);
    m_pRpAtomic->flags &= 0xfffffffdu;
    m_pRpAtomic->privateFlags |= 1;
}

// 0x00088398 GetGeometryWorldBoundingSphere (vt+0x78): the atomic's world sphere. A morphing atomic (flags
// bit 1) first updates its bounding sphere (vt+0x7c). Render flag 0x200000: the bounding sphere is already in
// world space (copied); otherwise it goes through the node's frame (TransformNodeBoundingSphereToWorld). The
// original transforms only when the atomic, the frame's root or the frame is marked dirty and keeps the last
// world sphere otherwise; the port has no dirty list, so it always transforms (the same values once synced).
// The atomic's dirty bit (object private flag 1) is cleared.
float* CGeometry::GetWorldBoundingSphere(CNode* node) {
    RpAtomic* atomic = m_pRpAtomic;
    if ((atomic->flags & 2) != 0) {
        UpdateBoundingSphere();  // vt+0x7c
        atomic = m_pRpAtomic;
    }
    if ((m_BitProperties & 0x200000) == 0) {
        TransformNodeBoundingSphereToWorld(atomic->boundingSphere[3], node, atomic->worldSphere, &atomic->worldSphere[3],
                                           atomic->boundingSphere);
        atomic = m_pRpAtomic;
    } else {
        atomic->worldSphere[0] = atomic->boundingSphere[0];
        atomic->worldSphere[3] = atomic->boundingSphere[3];
        atomic->worldSphere[1] = atomic->boundingSphere[1];
        atomic->worldSphere[2] = atomic->boundingSphere[2];
        atomic = m_pRpAtomic;
    }
    atomic->privateFlags &= static_cast<uint8_t>(~1u);
    return m_pRpAtomic->worldSphere;
}
