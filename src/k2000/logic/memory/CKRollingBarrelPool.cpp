// CKRollingBarrelPool.cpp - reconstructed original translation unit 0x441f60-0x443bb8 (GAME_TOC1, main_toc1), 25 functions, 18 live.
// Primary class: CKRollingBarrelPool  key 0x118c  category Logic  size 0x9c  vtable 0xb26668
// Other owners: CKHkRollingBarrel (2), RollingBarrelFx (2), NormalizedCurve (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x441f60  CKRollingBarrelPool_Delete  (the registry factory: DOTD_DECLARE_FACTORIES)
//   [ ] 0x441fb0  CKRollingBarrelPool_Construct  [dead]
//   [ ] 0x441ff8  FUN_00441ff8  [dead]
//   [x] 0x442000  CKHkRollingBarrel_PoolTakeNext_maybe  (CKRollingBarrelPool::TakeNext)
//   [x] 0x442040  CKHkRollingBarrel_PoolRelease_maybe  (CKRollingBarrelPool::Release)
//   [ ] 0x4420d8  RegisterCKRollingBarrelPoolClass
//   [ ] 0x442150  _GLOBAL__I_442150
//   [x] 0x442160  CKRollingBarrelPool_DeleteArray  (the registry factory: DOTD_DECLARE_FACTORIES)
//   [x] 0x442200  NormalizedCurve_Evaluate_maybe  (CKRollingBarrelPool::EvaluateCurve)
//   [ ] 0x4422c8  CKRollingBarrelPool_Construct_2  [dead]
//   [ ] 0x442310  CKRollingBarrelPool_Save
//   [x] 0x442318  CKRollingBarrelPool_RecursiveRegistration  (IKSerializable's: returns 1)
//   [x] 0x442320  CKRollingBarrelPool_PostLoad
//   [x] 0x442360  CKRollingBarrelPool_Destroy
//   [ ] 0x4423e0  CKRollingBarrelPool_ApplyDimensionsToBarrels_maybe  [dead]
//   [ ] 0x442590  CKRollingBarrelPool_SetHeight_maybe  [dead]
//   [ ] 0x4425a8  CKRollingBarrelPool_SetRadius_maybe  [dead]
//   [x] 0x4425b8  CKRollingBarrelPool_CreateArray  (the registry factory: DOTD_DECLARE_FACTORIES)
//   [x] 0x442690  CKRollingBarrelPool_Create  (the registry factory: DOTD_DECLARE_FACTORIES (the constructor))
//   [x] 0x442700  RollingBarrelFx_AddImpactPoint_maybe  (CKRollingBarrelPool::AddImpactPoint; port-rest R07 (its caller CKHkRollingBarrel 0x441168 waits in R05's left rows))
//   [x] 0x442810  RollingBarrelFx_EmitTrailPoints_maybe  (CKRollingBarrelPool::EmitTrailPoints; port-rest R07 (its caller CKHkRollingBarrel 0x4410c4 waits in R05's left rows))
//   [x] 0x442c80  CKRollingBarrelPool_DeletingDestructor  (the destructor; delete)
//   [x] 0x442d38  CKRollingBarrelPool_Destructor
//   [ ] 0x442dd8  CKRollingBarrelPool_Destructor_2  [dead]
//   [x] 0x442e78  CKRollingBarrelPool_Load
//
//   [ ] 0x9c3510  CKRollingBarrelPool_GetClassType  [inline]
//   [ ] 0x9c3518  CKRollingBarrelPool_GetClassID  [inline]
//   [ ] 0x9c3520  CKRollingBarrelPool_IsKindOfClass  [inline]
#include "k2000/logic/memory/CKRollingBarrelPool.h"

#include <cstring>

#include "crt/ppc_ops.h"
#include "k2000/io/IKFile.h"
#include "k2000/memory/Mem.h"
#include "Renderware/rpprtstd/RpPrtStd.h"
#include "k2000/misc/Mat4.h"
#include "k2000/scenegraph/CParticlesNodeFx.h"
#include "k2000/scenegraph/CSGLeaf.h"

CKRollingBarrelPool::CKRollingBarrelPool() {
    m_vPoints.m_pBlock = nullptr;
    m_vPoints.m_ui32NbElt = 1;
    m_vPoints.m_ui32NbUsedElt = 0;
    m_vWorldPoints.m_pBlock = nullptr;
    m_vWorldPoints.m_ui32NbElt = 1;
    m_vWorldPoints.m_ui32NbUsedElt = 0;
    m_unk5c = 1;
    m_unk60 = 8;
}

// 0x00442d38 CKRollingBarrelPool_Destructor (the TVectors' destructors)
CKRollingBarrelPool::~CKRollingBarrelPool() {
    if (m_vWorldPoints.m_pBlock != nullptr) Mem_FreeAligned16(m_vWorldPoints.m_pBlock);
    m_vWorldPoints.m_pBlock = nullptr;
    m_vWorldPoints.m_ui32NbUsedElt = 0;
    if (m_vPoints.m_pBlock != nullptr) Mem_FreeAligned16(m_vPoints.m_pBlock);
    m_vPoints.m_ui32NbUsedElt = 0;
    m_vPoints.m_pBlock = nullptr;
}

// 0x00442e78 CKRollingBarrelPool_Load. The references go through the file's resolver (IKFile_ReadRef).
int32_t CKRollingBarrelPool::Load(IKFile* file, int32_t type) {
    const bool level = type == K_LEVEL_PLATEFORMS;
    if (level) ReadRaw(file, &m_ui8NbBarrel, 1);
    ReadF32LE(file, &m_unk48);
    ReadF32LE(file, &m_unk4c);
    if (level) {
        // x4 on the PS3 (pointer size; port-rest R07: sizeof the pointer, so x64 holds them)
        m_apBarrels = static_cast<Barrel**>(Mem_AllocAligned16(static_cast<uint32_t>(m_ui8NbBarrel) * sizeof(Barrel*)));
        m_aBarrels = static_cast<Barrel*>(Mem_AllocAligned16(static_cast<uint32_t>(m_ui8NbBarrel) * sizeof(Barrel)));  // 0x90
        static const CVector3 kAxisZ = {0.0f, 0.0f, 1.0f};  // TOC +0x51ac -> 0x00c50d4c
        for (uint32_t i = 0; i < m_ui8NbBarrel; i = (i + 1) & 0xffu) {
            m_apBarrels[i] = &m_aBarrels[i];
            IKSerializable* a = nullptr;
            IKSerializable* node = nullptr;
            IKSerializable* c = nullptr;
            IKSerializable* d = nullptr;
            IKFile_ReadRef(file, &a);
            IKFile_ReadRef(file, &node);
            IKFile_ReadRef(file, &c);
            IKFile_ReadRef(file, &d);
            Barrel* barrel = m_apBarrels[i];
            barrel->m_pUnk00 = a;
            barrel->m_pNode = node;
            CSGLeaf* leaf = static_cast<CSGLeaf*>(barrel->m_pNode);
            leaf->m_sgProperties = (leaf->m_sgProperties & 0xfffffffbu) | 4u;
            barrel->m_pUnk38 = c;
            barrel->m_pUnk8c = d;
            barrel->m_unk08 = 0;
            barrel->m_unk0c = kAxisZ;
            barrel->m_unk18 = 0;
            barrel->m_unk3c = 0;
        }
        IKFile_ReadRef(file, &m_pUnk50);
    }
    ReadF32LE(file, &m_fCurveSpan);
    ReadU32LE(file, &m_ui32NbCurveKey);
    if (level) {
        if (m_ui32NbCurveKey == 0) {
            m_aCurveKeys = nullptr;
        } else {
            m_aCurveKeys = new CurveKey[m_ui32NbCurveKey];  // OperatorNewArray(count x 8 + 4) with the count first
            ReadU32LEWords(file, reinterpret_cast<uint32_t*>(m_aCurveKeys), m_ui32NbCurveKey * 2);
        }
    }
    for (int32_t i = 0; i < 6; ++i) ReadRaw(file, &m_unk6c[i], 1);
    IKFile_ReadRef(file, &m_pUnk1c);
    IKFile_ReadRef(file, &m_pTrail[0]);
    IKFile_ReadRef(file, &m_pTrail[1]);
    IKFile_ReadRef(file, &m_pTrail[2]);
    IKFile_ReadRef(file, &m_pUnk2c);
    ReadF32LE(file, &m_unk64);
    ReadF32LE(file, &m_unk68);
    ReadRaw(file, &m_unk6c[6], 1);
    ReadRaw(file, &m_unk98, 1);
    ReadF32LE(file, &m_unk7c);
    ReadF32LE(file, &m_unk80);
    ReadF32LE(file, &m_unk84);
    uint32_t count = 0;
    ReadU32LE(file, &count);
    // Both point vectors sized to the count (1 when 0, the used counts then left as they were); the original's
    // never-taken grow steps are kept.
    if (count == 0) {
        m_vPoints.m_ui32NbElt = 1;
        m_vPoints.m_pBlock = static_cast<CVector3*>(Mem_AllocAligned16(0xc));
        m_vWorldPoints.m_ui32NbElt = 1;
        m_vWorldPoints.m_pBlock = static_cast<CVector3*>(Mem_AllocAligned16(0xc));
        return 1;
    }
    m_vPoints.m_ui32NbElt = count;
    m_vPoints.m_pBlock = static_cast<CVector3*>(Mem_AllocAligned16(count * 0xc));
    m_vWorldPoints.m_ui32NbElt = count;
    m_vWorldPoints.m_pBlock = static_cast<CVector3*>(Mem_AllocAligned16(count * 0xc));
    if (m_vPoints.m_ui32NbElt < count) {
        const uint32_t capacity = count + 1;
        m_vPoints.m_pBlock = static_cast<CVector3*>(Mem_ReallocAligned16(m_vPoints.m_pBlock, capacity * 0xc));
        m_vPoints.m_ui32NbElt = capacity;
    }
    m_vPoints.m_ui32NbUsedElt = count;
    if (m_vWorldPoints.m_ui32NbElt < count) {
        const uint32_t capacity = count + 1;
        m_vWorldPoints.m_pBlock = static_cast<CVector3*>(Mem_ReallocAligned16(m_vWorldPoints.m_pBlock, capacity * 0xc));
        m_vWorldPoints.m_ui32NbElt = capacity;
    }
    m_vWorldPoints.m_ui32NbUsedElt = count;
    for (uint32_t i = 0; i < count; ++i) {
        uint32_t words[3];
        ReadU32LEWords(file, words, 3);  // one 0xc-byte read, each word swapped
        float* p = reinterpret_cast<float*>(&m_vPoints.m_pBlock[i]);
        std::memcpy(p, words, sizeof words);
    }
    return 1;
}

// 0x00442320 CKRollingBarrelPool_PostLoad (every type)
int32_t CKRollingBarrelPool::PostLoad(int32_t /*type*/) {
    m_ui8NbUsed = 0;
    m_unk54 = m_unk48;
    m_unk58 = m_unk48 + m_unk48;
    m_unk5c = 1;
    m_unk60 = 8;
    return 1;
}

// 0x00442360 CKRollingBarrelPool_Destroy (TocBridge_OperatorDeleteArray for the keys)
void CKRollingBarrelPool::Destroy() {
    if (m_apBarrels != nullptr) Mem_FreeAligned16(m_apBarrels);
    if (m_aBarrels != nullptr) Mem_FreeAligned16(m_aBarrels);
    if (m_aCurveKeys != nullptr) {
        delete[] m_aCurveKeys;
        m_aCurveKeys = nullptr;
    }
}

// 0x00442000 CKHkRollingBarrel_PoolTakeNext_maybe
CKRollingBarrelPool::Barrel* CKRollingBarrelPool::TakeNext() {
    if (!(m_ui8NbUsed < m_ui8NbBarrel)) return nullptr;
    m_ui8NbUsed = static_cast<uint8_t>(m_ui8NbUsed + 1);
    return m_apBarrels[(static_cast<uint32_t>(m_ui8NbUsed) * 4 & 0x3fcu) / 4 - 1];
}

// 0x00442040 CKHkRollingBarrel_PoolRelease_maybe: the walk goes on down to slot 0 after a match.
void CKRollingBarrelPool::Release(Barrel* barrel) {
    uint32_t i = m_ui8NbUsed;
    for (;;) {
        i = (i - 1) & 0xffu;
        if (i == 0xff) break;
        if (m_apBarrels[i] != barrel) continue;
        m_ui8NbUsed = static_cast<uint8_t>(m_ui8NbUsed - 1);
        if (i < m_ui8NbUsed) {
            m_apBarrels[i] = m_apBarrels[m_ui8NbUsed];
            m_apBarrels[m_ui8NbUsed] = barrel;
        }
    }
}

// 0x00442200 NormalizedCurve_Evaluate_maybe
float CKRollingBarrelPool::EvaluateCurve(float t) const {
    const float span = m_fCurveSpan;
    if (m_ui32NbCurveKey == 0 || span < t) return 1.0f;  // TOC +0x5180 (blt: a NaN goes on)
    if (m_ui32NbCurveKey == 1) return m_aCurveKeys[0].m_fY;
    for (uint32_t i = 0; i + 1 < m_ui32NbCurveKey; ++i) {  // CTR count - 1
        const float a = span * m_aCurveKeys[i].m_fX;
        if (!(t >= a)) continue;  // cror gt|eq
        const float b = span * m_aCurveKeys[i + 1].m_fX;
        if (t < b) {
            const float y0 = m_aCurveKeys[i].m_fY;
            return ppc::fmadds((t - a) / (b - a), m_aCurveKeys[i + 1].m_fY - y0, y0);
        }
    }
    return 0.0f;  // TOC +0x5184
}

// ---- C2.8 port-rest R07: the trail effects (CParticlesNodeFx, their emit point lists; CKHkRollingBarrel's callers) --
namespace {
// One emit point appended while the list has room (at most 64; cmplwi 0x3f / bgt), the node's 0x2000 set.
void AppendEmitPoint(CParticlesNodeFx* fx, const CVector3& point) {
    const uint8_t n = fx->m_ui8NbActivePoints;
    if (n > 0x3f) return;
    RwV3d& out = fx->m_pAdvEmtPointList->pointList[n];
    out.z = point.z;
    out.x = point.x;
    out.y = point.y;
    fx->m_sgProperties |= 0x2000u;  // the CBitArray rlwinm pair: bit 13 cleared, then or-ed in
    fx->m_ui8NbActivePoints = static_cast<uint8_t>(n + 1);
}
// The emitting start (CParticlesNodeFx_MessageProc's 0x1a00 with 1 / 0x1a01 inlined): 0x400 (and with `show` 0x200)
// set, 0x80000 cleared, no speed adjustment, the emitter active and emitting (0xa).
void StartEmitting(CParticlesNodeFx* fx, bool show) {
    uint32_t p = fx->m_sgProperties;
    if (show) p |= 0x200u;
    p |= 0x400u;
    p &= ~0x80000u;
    fx->m_sgProperties = p;
    fx->m_fEmissionSpeedAdjustment = 0.0f;
    fx->m_pRpPrtStdEmitter->flag |= 0xau;
}
}  // namespace

// 0x00442700 RollingBarrelFx_AddImpactPoint_maybe: `point` appended to the impact effect (+0x20), which starts emitting
// (shown too with `show`).
void CKRollingBarrelPool::AddImpactPoint(const CVector3* point, int32_t show) {
    CParticlesNodeFx* fx = static_cast<CParticlesNodeFx*>(m_pTrail[0]);
    AppendEmitPoint(fx, *point);
    StartEmitting(static_cast<CParticlesNodeFx*>(m_pTrail[0]), show != 0);
}

// 0x00442810 RollingBarrelFx_EmitTrailPoints_maybe: without trail points the matrix's position, else the trail points
// through `matrix` (Mat4_TransformPoints into +0x3c), each appended to the effect +0x24 and, when set, +0x28 / +0x2c;
// then the three start emitting.
void CKRollingBarrelPool::EmitTrailPoints(const CMatrix34* matrix) {
    CParticlesNodeFx* const a = static_cast<CParticlesNodeFx*>(m_pTrail[1]);  // +0x24
    if (m_vPoints.m_ui32NbUsedElt == 0) {
        const CVector3& pos = matrix->m_pos;  // +0x30
        AppendEmitPoint(a, pos);
        if (m_pTrail[2] != nullptr) AppendEmitPoint(static_cast<CParticlesNodeFx*>(m_pTrail[2]), pos);
        if (m_pUnk2c != nullptr) AppendEmitPoint(static_cast<CParticlesNodeFx*>(m_pUnk2c), pos);
    } else {
        Mat4_TransformPoints(matrix, m_vWorldPoints.m_pBlock, m_vPoints.m_pBlock,
                             static_cast<int32_t>(m_vPoints.m_ui32NbUsedElt));  // 0x0023f7e8
        for (uint32_t i = 0; i < m_vWorldPoints.m_ui32NbUsedElt; ++i) {  // cmplw / bgt after the first
            AppendEmitPoint(static_cast<CParticlesNodeFx*>(m_pTrail[1]), m_vWorldPoints.m_pBlock[i]);
            if (m_pTrail[2] != nullptr) AppendEmitPoint(static_cast<CParticlesNodeFx*>(m_pTrail[2]), m_vWorldPoints.m_pBlock[i]);
            if (m_pUnk2c != nullptr) AppendEmitPoint(static_cast<CParticlesNodeFx*>(m_pUnk2c), m_vWorldPoints.m_pBlock[i]);
        }
    }
    StartEmitting(static_cast<CParticlesNodeFx*>(m_pTrail[1]), false);
    if (m_pTrail[2] != nullptr) StartEmitting(static_cast<CParticlesNodeFx*>(m_pTrail[2]), false);
    if (m_pUnk2c != nullptr) StartEmitting(static_cast<CParticlesNodeFx*>(m_pUnk2c), false);
}
