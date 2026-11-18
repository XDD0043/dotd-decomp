// CParticleGeometry_2.cpp - reconstructed original translation unit 0x89a70-0x8b218 (GAME_TOC1, main_toc1), 12 functions, 12 live.
// Primary class: CParticleGeometry  key 0x4a  category Geometry  size 0x34  vtable 0xb169d0
// Other owners: ParticlePTank (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x89a70  CParticleGeometry_Destroy  (CGeometry::Destroy inherited; the render mutex is not needed natively)
//   [ ] 0x89ad0  ParticlePTank_UpdateBoundingSphere_maybe  [dead: no pointer to its descriptor 0xb461e0]
//   [x] 0x89d60  CParticleGeometry_vf84
//   [x] 0x89f20  CParticleGeometry_DeleteArray  (DOTD_DECLARE_FACTORIES)
//   [x] 0x89fc0  CParticleGeometry_Create
//   [x] 0x8a028  CParticleGeometry_GetMaterialRenderInfo
//   [x] 0x8a050  CParticleGeometry_PostLoad
//   [x] 0x8a0e8  CParticleGeometry_ComputeRenderStage
//   [x] 0x8a290  CParticleGeometry_UpdateAtomicBoundingSphere_maybe
//   [x] 0x8a460  CParticleGeometry_CreateArray  (DOTD_DECLARE_FACTORIES: the constructors' zeroed fields)
//   [x] 0x8a520  CParticleGeometry_HasParticlesToDraw_maybe
//   [x] 0x8a590  CParticleGeometry_Load
//
//   [ ] 0x99c300  CParticleGeometry_GetClassType  [inline]
//   [ ] 0x99c308  CParticleGeometry_GetClassID  [inline]
//   [ ] 0x99c310  CParticleGeometry_IsKindOfClass  [inline]
//   [ ] 0x99c348  CParticleGeometry_DeletingDestructor  [inline]
//   [ ] 0x99c390  CParticleGeometry_Destructor  [inline]
#include "k2000/geometry/CGeometry.h"

#include <cmath>
#include <cstring>

#include "crt/vmx_ops.h"

#include "Renderware/rpprtstd/RpPrtStd.h"
#include "Renderware/rpprtstd/RpPrtStdRuntime.h"
#include "Renderware/rpworld/RpAtomic.h"
#include "Renderware/rpworld/RpGeometry.h"
#include "Renderware/rwcore/RwCamera.h"
#include "Renderware/rwcore/RwTexture.h"
#include "k2000/io/IKFile.h"
#include "k2000/math/CMatrix34.h"

namespace {
// 0xc297ec / 0xc297fc (TOC -0x6680 / -0x667c): source and destination blend per property bits 8-9.
constexpr uint32_t kSrcBlend[4] = {2, 5, 5, 1};
constexpr uint32_t kDestBlend[4] = {1, 6, 2, 4};

uint32_t LoadLE32(const uint8_t* b) {
    return static_cast<uint32_t>(b[0]) | (static_cast<uint32_t>(b[1]) << 8) | (static_cast<uint32_t>(b[2]) << 16) |
           (static_cast<uint32_t>(b[3]) << 24);
}

// Read(n * 4 * words) into the array, then lwbrx every word in place (on the PS3; native here).
void ReadSwapped(IKFile* file, void* dst, uint32_t words) {
    uint8_t* bytes = static_cast<uint8_t*>(dst);
    file->Read(bytes, words * 4);
    for (uint32_t i = 0; i < words; ++i) {
        const uint32_t v = LoadLE32(bytes + 4 * i);
        std::memcpy(bytes + 4 * i, &v, 4);
    }
}
}  // namespace

// 0x0008a590 CParticleGeometry_Load
int32_t CParticleGeometry::Load(IKFile* file, int32_t type) {
    RenderLock_Lock();
    CGeometry::Load(file, type);
    RenderLock_Unlock();
    if (type != K_LEVEL_PLATEFORMS) return 1;
    ReadU32LE(file, &m_baParticleGeometry);
    if ((m_BitProperties & 0x4000) == 0) {
        // A streamed (RpPrtStd) atomic: under the render lock vt+0x84 (FindRpGeometry), which makes its
        // emitters' PTanks now.
        RenderLock_Lock();
        FindRpGeometry();
        RenderLock_Unlock();
        return 1;
    }
    uint32_t header[3];
    ReadSwapped(file, header, 3);  // data flags, the PTank's +4 word, the particle count
    m_pRpAtomic = RpPTankAtomicCreate(header[2], header[0], 0);
    RpPTankData* ptank = m_pRpAtomic->ptank;
    ptank->flags40 |= 0x800000;
    ptank->numPrt = header[1];
    ReadSwapped(file, m_pRpAtomic->boundingSphere, 4);
    std::memcpy(m_pRpAtomic->worldSphere, m_pRpAtomic->boundingSphere, sizeof(m_pRpAtomic->worldSphere));
    m_pRpAtomic->flags &= ~2u;
    m_pRpAtomic->privateFlags &= 0xfe;
    const uint32_t flags = m_baParticleGeometry;
    if ((flags & 0x1ffff) != 0) {
        const uint32_t n = ptank->maxParticles;
        if ((flags & 0x1) != 0) {  // positions: 12 bytes each, 16 apart
            uint8_t* p = RwShim_PTankArray(m_pRpAtomic, 0x1);
            for (uint32_t i = 0; i < n; ++i) ReadSwapped(file, p + 16 * i, 3);
        }
        if ((flags & 0x2) != 0) ReadRaw(file, RwShim_PTankArray(m_pRpAtomic, 0x2), n * 4);  // colours, raw
        if ((flags & 0x4) != 0) ReadSwapped(file, RwShim_PTankArray(m_pRpAtomic, 0x4), n * 2);  // sizes
        if ((flags & 0x8) != 0) {  // matrices
            uint8_t* p = RwShim_PTankArray(m_pRpAtomic, 0x8);
            for (uint32_t i = 0; i < n; ++i) CMatrix34_LoadMatrix(reinterpret_cast<CMatrix34*>(p + 64 * i), file);
        }
        if ((flags & 0x10) != 0) {  // normals: 12 bytes each, 12 apart
            uint8_t* p = RwShim_PTankArray(m_pRpAtomic, 0x10);
            for (uint32_t i = 0; i < n; ++i) ReadSwapped(file, p + 12 * i, 3);
        }
        if ((flags & 0x20) != 0) ReadSwapped(file, RwShim_PTankArray(m_pRpAtomic, 0x20), n);  // 2D rotations
        if ((flags & 0x40) != 0) ReadRaw(file, RwShim_PTankArray(m_pRpAtomic, 0x40), n * 16);  // vertex colours, raw
        if ((flags & 0x80) != 0) ReadSwapped(file, RwShim_PTankArray(m_pRpAtomic, 0x80), n * 4);  // 2 tex coords
        if ((flags & 0x100) != 0) ReadSwapped(file, RwShim_PTankArray(m_pRpAtomic, 0x100), n * 8);  // 4 tex coords
        if ((flags & 0x200) != 0) ReadSwapped(file, ptank->renderC0, 2);
        if ((flags & 0x400) != 0) ReadRaw(file, ptank->colorCC, 4);
        if ((flags & 0x800) != 0) CMatrix34_LoadMatrix(reinterpret_cast<CMatrix34*>(ptank->matrix100), file);
        if ((flags & 0x1000) != 0) ReadSwapped(file, &ptank->renderC8, 1);
        if ((flags & 0x2000) != 0) ReadRaw(file, ptank->vtxColorD0, 16);
        if ((flags & 0x4000) != 0) ReadSwapped(file, ptank->texCoordsE0, 4);
        if ((flags & 0x8000) != 0) ReadSwapped(file, ptank->texCoordsE0, 8);
        // After any locked array: vt+0x80 (CParticleGeometry_vf80, unlocks the PTank). Nothing to do here.
    }
    if (RpAtomicIsPTank(m_pRpAtomic) != 0) {
        void* texture = nullptr;
        IKFile_ReadTextureRef(file, &texture, 0);
        RpMaterialSetTexture(m_pRpAtomic->geometry->matList.materials[0], static_cast<RwTexture*>(texture));
    }
    const uint32_t mode = (m_BitProperties >> 8) & 3;
    ptank->renderB4 = mode != 0 ? 1 : 0;  // -(mode) >> 31: vertex alpha
    ptank->renderAC = kSrcBlend[mode];
    ptank->renderB0 = kDestBlend[mode];
    ptank->flags40 |= 0x10000000;
    return 1;
}

// 0x00089d60 CParticleGeometry_FindRpGeometry (vt+0x84): a PTank atomic's own geometry; for an RpPrtStd atomic the
// geometry of its (last) emitter's PTank, the PTank made first when there is none: the atomic updated and emitting
// once (RW_UpdateParticleAtomic_2, time 0) with the emitter's flags reduced to active (the update, particle update,
// render and emit flags 0x78 off; put back afterwards), on a temporary frame when the atomic has none. Null without
// an atomic, an emitter or a PTank property. A PTank's geometry is its quad geometry (one material, RpAtomic.cpp).
void* CParticleGeometry::FindRpGeometry() {
    RpAtomic* atomic = m_pRpAtomic;
    if (atomic == nullptr) return nullptr;
    if (RpAtomicIsPTank(atomic) != 0) return m_pRpAtomic->geometry;
    RpPrtStdEmitter* emitter = RpPrtStdAtomicGetEmitter(m_pRpAtomic);
    if (emitter == nullptr) return nullptr;
    const int32_t offset = RpPrtStdPropTabGetPropOffset(emitter->emtClass->propTab, rpPRTSTDPROPERTYCODEEMITTERPTANK);
    if (offset == -1) return nullptr;
    RpPrtStdEmitterPTank* ptank = reinterpret_cast<RpPrtStdEmitterPTank*>(reinterpret_cast<uint8_t*>(emitter) + offset);
    if (ptank->pTank == nullptr) {
        if (m_pRpAtomic->frame != nullptr) {
            const uint32_t flags = emitter->flag;
            emitter->flag = (flags | 2u) & ~0x78u;
            float time = 0.0f;  // stw 0
            RpPrtStdAtomicUpdateAndEmit(m_pRpAtomic, &time);
            emitter->flag = flags;
        } else {
            RwFrame* frame = RwFrameCreate();
            RpAtomicSetFrame(m_pRpAtomic, frame);
            const uint32_t flags = emitter->flag;
            emitter->flag = (flags | 2u) & ~0x78u;
            float time = 0.0f;
            RpPrtStdAtomicUpdateAndEmit(m_pRpAtomic, &time);
            emitter->flag = flags;
            if (frame != nullptr) {
                RpAtomicSetFrame(m_pRpAtomic, nullptr);
                RwFrameDestroy(frame);
            }
        }
    }
    return ptank->pTank->geometry;
}

// 0x0008a520 CParticleGeometry_HasParticlesToDraw_maybe: a PTank atomic only with particles (+4 > 0); any
// other atomic (the RpPrtStd emitters') always.
int32_t CParticleGeometry::HasParticlesToDraw() {
    if (RpAtomicIsPTank(m_pRpAtomic) == 0) return 1;
    const int32_t count = static_cast<int32_t>(m_pRpAtomic->ptank->numPrt);
    return count > 0 ? 1 : 0;
}

// 0x0008a050 CParticleGeometry_PostLoad (the original's r4 is the type CGeometry_PostLoad received: stale in the
// decompile, the caller's argument).
int32_t CParticleGeometry::PostLoad(int32_t type) {
    CGeometry::PostLoad(type);
    if (((m_BitProperties >> 8) & 3) == 2) m_BitProperties &= 0xfdffffffu;
    Vf80(1);
    return 1;
}

// 0x0008a028 CParticleGeometry_GetRenderingProperties
void CParticleGeometry::GetRenderingProperties(uint8_t* first, uint8_t* second, uint8_t* third, uint32_t* blendMode) {
    *first = 1;
    *second = 0xff;
    *third = 0;
    *blendMode = (m_BitProperties >> 8) & 3;
}

// 0x0008a0e8 CParticleGeometry_UpdateProperties: the particle geometry's own vt+0x60 (CGeometry's ran in its place, so a
// blend mode set after the Load (CGeometry_SetBlendMode: the fog boxes, the sparks) left the PTank's blend states).
void CParticleGeometry::UpdateProperties() {
    // g_RenderStageLookupTable 0x00c296b8 (TOC -0x6684), the same as CGeometry's.
    static const uint32_t kStages[32] = {5, 6, 7, 8, 9, 12, 13, 14, 19, 20, 20, 20, 21, 21, 21, 21,
                                         1, 2, 3, 3, 4, 4, 4, 4, 1, 0, 2, 3, 4, 1, 0, 3};
    const uint32_t cur = m_BitProperties;
    const uint32_t mode = (cur >> 8) & 3;
    if ((cur & 0x20) == 0) {
        const uint32_t layer = (cur >> 17) & 3;
        m_BitProperties = kStages[layer * 8 + (mode == 2 ? 7u : 6u)] | (m_BitProperties & 0xffffffe0u);
    }
    const uint32_t src = kSrcBlend[mode];
    const uint32_t dst = kDestBlend[mode];
    RpAtomic* tankAtomic = nullptr;
    if (m_pRpAtomic == nullptr) return;  // (as below: the original would fault)
    RpPrtStdEmitter* emitter = RpPrtStdAtomicGetEmitter(m_pRpAtomic);  // 0x0098e110 (TocBridge)
    if (emitter == nullptr) {
        tankAtomic = m_pRpAtomic;
        if (tankAtomic->ptank == nullptr) return;
        tankAtomic->ptank->renderB4 = mode != 0 ? 1u : 0u;  // -(mode) >> 31: vertex alpha
        m_BitProperties = (m_BitProperties & 0xffdfffffu) | 0x200000u;
    } else {
        m_BitProperties &= 0xffdfffffu;
        const int32_t offset = RpPrtStdPropTabGetPropOffset(emitter->emtClass->propTab, rpPRTSTDPROPERTYCODEEMITTERPTANK);
        // BUG(original): without the PTank property the PTank pointer stays null and the stores below go through it.
        if (offset != -1) {
            RpPrtStdEmitterPTank* property =
                reinterpret_cast<RpPrtStdEmitterPTank*>(reinterpret_cast<uint8_t*>(emitter) + offset);
            tankAtomic = property->pTank;
            property->strDstBlend = dst;
            property->strSrcBlend = src;
        }
    }
    // (The original dereferences the PTank unconditionally; a null one would fault there.)
    if (tankAtomic == nullptr || tankAtomic->ptank == nullptr) return;
    RpPTankData* tank = tankAtomic->ptank;
    tank->renderAC = src;
    tank->renderB0 = dst;
    tank->flags40 |= 0x10000000u;
}

// 0x0008a290 CParticleGeometry_UpdateAtomicBoundingSphere_maybe: without particles the zero sphere; else the
// box around the particles' positions (AltiVec min / max), its centre ((max + min) * 0.5) and the radius
// ((|half extent| + 1) * 1.1, or 1.1); the PTank unlocked, the atomic's sphere-dirty flag (2) cleared.
void CParticleGeometry::UpdateAtomicBoundingSphere() {
    RpAtomic* atomic = m_pRpAtomic;
    const RpPTankData* ptank = atomic->ptank;
    const uint32_t count = ptank->numPrt;
    if (count == 0) {
        atomic->boundingSphere[0] = 0.0f;  // 0x00c50d64
        atomic->boundingSphere[1] = 0.0f;
        atomic->boundingSphere[2] = 0.0f;
        atomic->boundingSphere[3] = 0.0f;
        return;
    }
    RpPTankLockStruct lock = {nullptr, 0};
    RpPTankAtomicLock(atomic, &lock, 1, 0x80000000u);  // rpPTANKLFLAGREAD
    const float* p = reinterpret_cast<const float*>(lock.data);
    float maxV[3] = {p[0], p[1], p[2]};
    float minV[3] = {p[0], p[1], p[2]};
    for (uint32_t i = 1; i < count; ++i) {
        p += 4;
        for (int32_t k = 0; k < 3; ++k) {
            if (p[k] >= maxV[k]) maxV[k] = p[k];  // vcmpgefp / vsel
            if (!(p[k] >= minV[k])) minV[k] = p[k];
        }
    }
    // vaddfp / vsubfp, then vmaddfp by the 0.5 splat (+0); the squared half extent fused lane by lane (z, y, x) and its
    // length d * vrsqrtefp(d) (crt/vmx_ops.h: RPCS3's exact estimate, results with a zero exponent flushed).
    float half[3];
    for (int32_t k = 0; k < 3; ++k) {
        atomic->boundingSphere[k] = vmx::Madd(vmx::Add(maxV[k], minV[k]), 0.5f, 0.0f);
        half[k] = vmx::Madd(vmx::Sub(maxV[k], minV[k]), 0.5f, 0.0f);
    }
    const float lengthSquared = vmx::Madd(half[0], half[0], vmx::Madd(half[1], half[1], vmx::Madd(half[2], half[2], 0.0f)));
    const float length = vmx::Madd(lengthSquared, vmx::Rsqrtefp(lengthSquared), 0.0f);
    atomic->boundingSphere[3] = length > 0.0f ? (length + 1.0f) * 1.10000002f : 1.10000002f;
    RpPTankAtomicUnlock(atomic);
    atomic->flags &= 0xfffffffdu;
}
