// CParticleGeometry_2.cpp - reconstructed original translation unit 0x89a70-0x8b218 (GAME_TOC1, main_toc1), 12 functions, 12 live.
// Primary class: CParticleGeometry  key 0x4a  category Geometry  size 0x34  vtable 0xb169d0
// Other owners: ParticlePTank (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [ ] 0x89a70  CParticleGeometry_Destroy
//   [ ] 0x89ad0  ParticlePTank_UpdateBoundingSphere_maybe
//   [ ] 0x89d60  CParticleGeometry_vf84
//   [ ] 0x89f20  CParticleGeometry_DeleteArray
//   [x] 0x89fc0  CParticleGeometry_Create
//   [ ] 0x8a028  CParticleGeometry_GetMaterialRenderInfo
//   [x] 0x8a050  CParticleGeometry_PostLoad
//   [ ] 0x8a0e8  CParticleGeometry_ComputeRenderStage
//   [ ] 0x8a290  CParticleGeometry_UpdateAtomicBoundingSphere_maybe
//   [ ] 0x8a460  CParticleGeometry_CreateArray
//   [x] 0x8a520  CParticleGeometry_HasParticlesToDraw_maybe
//   [x] 0x8a590  CParticleGeometry_Load
//
//   [ ] 0x99c300  CParticleGeometry_GetClassType  [inline]
//   [ ] 0x99c308  CParticleGeometry_GetClassID  [inline]
//   [ ] 0x99c310  CParticleGeometry_IsKindOfClass  [inline]
//   [ ] 0x99c348  CParticleGeometry_DeletingDestructor  [inline]
//   [ ] 0x99c390  CParticleGeometry_Destructor  [inline]
#include "k2000/geometry/CGeometry.h"

#include <cstring>

#include "Renderware/rpworld/RpAtomic.h"
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
        // Under the render lock: vt EnqueueOwnGeometry (the render queues). STUB(C1.4).
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
    m_pRpAtomic->objectFlags &= 0xfe;
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
        m_pRpAtomic->texture = static_cast<RwTexture*>(texture);  // RpMaterialSetTexture on its material
    }
    const uint32_t mode = (m_BitProperties >> 8) & 3;
    ptank->renderB4 = mode != 0 ? 1 : 0;  // -(mode) >> 31: vertex alpha
    ptank->renderAC = kSrcBlend[mode];
    ptank->renderB0 = kDestBlend[mode];
    ptank->flags40 |= 0x10000000;
    return 1;
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
