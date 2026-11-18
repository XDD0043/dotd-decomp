// Reconstructed original translation unit: 0x1d0978-0x1d1288 (GAME_TOC1, main_toc1), 14 functions, 14 live.
// Primary class: CKQuadNodeFx  key 0x178c  category Logic  size 0x1c  vtable 0xb1d6f8
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x1d0978  CKQuadNodeFx_Delete  (DOTD_DECLARE_FACTORIES)
//   [x] 0x1d09c8  CKQuadNodeFx_Destroy  (empty)
//   [x] 0x1d09d0  CKQuadNodeFx_RecursiveRegistration
//   [x] 0x1d0a28  CKQuadNodeFx_Stop
//   [ ] 0x1d0a80  RegisterCKQuadNodeFxClass
//   [ ] 0x1d0af8  _GLOBAL__I_1d0af8
//   [x] 0x1d0b08  CKQuadNodeFx_Load  (IKNodeFx's Load: inherited)
//   [ ] 0x1d0b30  CKQuadNodeFx_Save
//   [x] 0x1d0b58  CKQuadNodeFx_DeleteArray  (DOTD_DECLARE_FACTORIES)
//   [x] 0x1d0c00  CKQuadNodeFx_CreateArray  (DOTD_DECLARE_FACTORIES)
//   [x] 0x1d0cb8  CKQuadNodeFx_PostLoad
//   [x] 0x1d0e30  CKQuadNodeFx_Start
//   [x] 0x1d0fd8  CKQuadNodeFx_Update
//   [x] 0x1d1230  CKQuadNodeFx_Create  (DOTD_DECLARE_FACTORIES)
//
//   [x] 0x9ad118  CKQuadNodeFx_IsKindOfClass  [inline]
//   [x] 0x9ad150  CKQuadNodeFx_GetClassType  [inline]
//   [x] 0x9ad158  CKQuadNodeFx_GetClassID  [inline]
//   [x] 0x9ad160  CKQuadNodeFx_GetFxData  [inline]
//   [x] 0x9ad168  CKQuadNodeFx_SetFxData  [inline]
//   [ ] 0x9ad170  CKQuadNodeFx_Destruct  [inline]
//   [ ] 0x9ad190  CKQuadNodeFx_DeletingDestruct  [inline]
#include "k2000/logic/fx/CKQuadNodeFx.h"

#include <cfloat>
#include <cstring>

#include "Renderware/rpworld/RpAtomic.h"
#include "Renderware/rpworld/RpGeometry.h"
#include "crt/ppc_ops.h"
#include "k2000/misc/ClassRegistry.h"
#include "k2000/geometry/CGeometry.h"
#include "k2000/logic/CKSavingManager.h"
#include "k2000/logic/fx/CKQuadFxData.h"
#include "k2000/logic/render/CMaterial.h"
#include "k2000/misc/Engine.h"
#include "k2000/scenegraph/CNode.h"
#include "k2000/system/IKTime.h"

namespace {
CParticleGeometry* QuadGeometry(const CKQuadNodeFx* fx) {
    return static_cast<CParticleGeometry*>(static_cast<CNode*>(fx->m_pNode)->m_lGeometryList);
}
void SetFloatWord(uint32_t* word, float value) { std::memcpy(word, &value, 4); }
}  // namespace

// 0x001d09d0 CKQuadNodeFx_RecursiveRegistration
void CKQuadNodeFx::RecursiveRegistration(int32_t /*type*/) {
    g_pEngine->m_pSavingManager->RegisterSerializableObject(this, nullptr);  // vt+0x24
}

// 0x001d0a28 CKQuadNodeFx_Stop: stopped, the node hidden (vt+0x60).
void CKQuadNodeFx::Stop() {
    m_baFxData = static_cast<uint8_t>((m_baFxData & 0xfe) | 1);
    Vf60();
}

// 0x001d0cb8 CKQuadNodeFx_PostLoad (IKNodeFx's not called): the PTank atomic's bounding sphere made infinite (the null
// vector 0x00c50d64, radius FLT_MAX; synchronised first when dirty; then its dirty bit 1 cleared and its world bound
// marked dirty), the constant colour 0 (0x00c50dfc) copied to the PTank material, the constant vertex colours flag, the
// geometry's blend mode 2.
int32_t CKQuadNodeFx::PostLoad(int32_t /*type*/) {
    CParticleGeometry* geometry = QuadGeometry(this);
    RpAtomic* atomic = geometry->m_pRpAtomic;
    if ((atomic->flags & 2u) != 0) _rpAtomicResyncInterpolatedSphere(atomic);  // 0x0098e090 -> 0x69bbe0
    atomic = geometry->m_pRpAtomic;
    atomic->boundingSphere[0] = 0.0f;
    atomic->boundingSphere[1] = 0.0f;
    atomic->boundingSphere[2] = 0.0f;
    atomic->boundingSphere[3] = FLT_MAX;  // 0x00c4ace0
    atomic->flags &= ~2u;
    atomic->privateFlags |= 1;
    RpPTankData* ptank = atomic->ptank;
    std::memset(ptank->colorCC, 0, 4);
    RpPTankAtomicCopyConstantColorToMaterial(atomic);  // the PTank material's colour when it has one
    ptank->flags40 |= 0x2000;
    geometry->SetBlendMode(2);  // 0x00088028
    return 1;
}

// 0x001d0e30 CKQuadNodeFx_Start: running; the material's texture from the data; the PTank's two constant tex coords
// (0, 0, 1, 1: TOC -0x1acc) with their flag; unlocked (vt+0x8c); the count flag and one particle; the node shown (vt+0x5c).
void CKQuadNodeFx::Vf64() {
    m_baFxData = static_cast<uint8_t>(m_baFxData & 0xfe);
    CParticleGeometry* geometry = QuadGeometry(this);
    static_cast<CMaterial*>(geometry->m_pMaterial)->SetTexture(static_cast<RwTexture*>(m_pData->m_pTexture));
    RpPTankData* ptank = geometry->m_pRpAtomic->ptank;
    ptank->texCoordsE0[0] = 0;
    ptank->texCoordsE0[1] = 0;
    SetFloatWord(&ptank->texCoordsE0[3], 1.0f);
    SetFloatWord(&ptank->texCoordsE0[2], 1.0f);
    // (the original then copies the four words onto themselves: the same PTank read twice)
    ptank->flags40 |= 0x80000;
    geometry->UnlockPTank();  // vt+0x8c
    ptank = geometry->m_pRpAtomic->ptank;
    ptank->flags40 |= 0x800000;
    ptank->numPrt = 1;
    Vf5C();  // vt+0x5c
}

// 0x001d0fd8 CKQuadNodeFx_Update: the four PTank arrays locked for writing (position, size, 2D rotation, colour; a missing
// one is written through null as in the original); the angle advances by sign (+0x25) x dt (IKTime +0x1c) x speed (fused);
// the position from the data's position pointer; the size, with the jitter flag, scaled by 1 + (2r/65535 - 1) x jitter
// (one rand), else as stored; the rotation; the colour word; unlocked (vt+0x8c), the count flag and one particle.
void CKQuadNodeFx::Update(IKTime* frameClock) {
    CParticleGeometry* geometry = QuadGeometry(this);
    RpAtomic* atomic = geometry->m_pRpAtomic;
    RpPTankLockStruct lock = {nullptr, 0};
    float* positions = RpPTankAtomicLock(atomic, &lock, 1, 0x40000000) != 0 ? reinterpret_cast<float*>(lock.data) : nullptr;
    float* sizes = RpPTankAtomicLock(atomic, &lock, 4, 0x40000000) != 0 ? reinterpret_cast<float*>(lock.data) : nullptr;
    float* rotations = RpPTankAtomicLock(atomic, &lock, 0x20, 0x40000000) != 0 ? reinterpret_cast<float*>(lock.data) : nullptr;
    uint8_t* colours = RpPTankAtomicLock(atomic, &lock, 2, 0x40000000) != 0 ? lock.data : nullptr;
    const CKQuadFxData* data = m_pData;
    const float sign = static_cast<float>(static_cast<double>(data->m_i8RotationSign));
    m_fAngle = ppc::fmadds(sign * frameClock->m_afDeltaTime[IKTime::SCALABLE_GAME_TIME], data->m_fRotationSpeed, m_fAngle);
    const CVector3* position = data->m_pPosition;
    positions[2] = position->z;
    positions[0] = position->x;
    positions[1] = position->y;
    data = m_pData;
    if (data->m_bJitterSize == 0) {
        sizes[1] = data->m_afSize[1];
        sizes[0] = data->m_afSize[0];
    } else {
        const uint32_t r = static_cast<uint32_t>(Rand_Int()) & 0xffffu;  // 0x00011500
        data = m_pData;
        float f = static_cast<float>(static_cast<double>(r)) / 65535.0f;  // TOC -0x1ac8
        f = f + f;
        f = ppc::fmsubs(f, data->m_fSizeJitter, data->m_fSizeJitter);
        sizes[1] = ppc::fmadds(f, data->m_afSize[1], data->m_afSize[1]);
        sizes[0] = ppc::fmadds(f, data->m_afSize[0], data->m_afSize[0]);
    }
    rotations[0] = m_fAngle;
    std::memcpy(colours, &m_pData->m_color, 4);
    geometry->UnlockPTank();  // vt+0x8c
    RpPTankData* ptank = geometry->m_pRpAtomic->ptank;
    ptank->flags40 |= 0x800000;
    ptank->numPrt = 1;
}

IKFxData* CKQuadNodeFx::GetFxData() { return m_pData; }                                  // 0x009ad160
void CKQuadNodeFx::SetFxData(IKFxData* data) { m_pData = static_cast<CKQuadFxData*>(data); }  // 0x009ad168
