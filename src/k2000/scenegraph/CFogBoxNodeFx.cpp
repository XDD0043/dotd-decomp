// CFogBoxNodeFx.cpp - reconstructed original translation unit 0xda260-0xe3538 (GAME_TOC1, main_toc1), 29 functions, 21 live.
// Primary class: CFogBoxNodeFx  key 0x68b  category SceneNode  size 0x838  vtable 0xb189a0
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [ ] 0xda260  RegisterCFogBoxNodeFxClass
//   [ ] 0xda2d8  _GLOBAL__I_da2d8
//   [x] 0xda2e8  CFogBoxNodeFx_DeleteArray
//   [x] 0xda388  CFogBoxNodeFx_GetInfo  (INodeFx's 1 mapped to 1: the default)
//   [ ] 0xda3d8  CFogBoxNodeFx_InitParticlePhaseTables_maybe  [dead]
//   [ ] 0xda4d8  CFogBoxNodeFx_AdvanceFlipbookFrame_maybe  [dead]
//   [x] 0xda598  CFogBoxNodeFx_RecursiveRegistration  (INodeFx's (returns 1, registers nothing): CSGLeaf's)
//   [x] 0xda5c0  CFogBoxNodeFx_Destroy
//   [ ] 0xda7c0  CFogBoxNodeFx_Construct  [dead]
//   [x] 0xda968  CFogBoxNodeFx_RandomizeEmitterParticles_maybe
//   [x] 0xdab30  CFogBoxNodeFx_MessageProc
//   [ ] 0xdaba0  CFogBoxNodeFx_Construct_2  [dead]
//   [ ] 0xdad48  CFogBoxNodeFx_SortParticlesByDistance_maybe  [dead]
//   [x] 0xdae70  CFogBoxNodeFx_InitParticleRandomValues_maybe
//   [ ] 0xdb018  CFogBoxNodeFx_InitAtomicRenderState_maybe  [dead]
//   [x] 0xdb1a0  CFogBoxNodeFx_InitParticleColors_maybe
//   [ ] 0xdbac8  CFogBoxNodeFx_ResetFlipbookAndColors_maybe  [dead]
//   [x] 0xdbae0  CFogBoxNodeFx_InitParticlesRandomInBox_maybe
//   [x] 0xdbfa0  CFogBoxNodeFx_AllocParticleArrays_maybe
//   [ ] 0xdc1f8  CFogBoxNodeFx_InitParticlePositions_maybe  [dead: no pointer to its descriptor 0xb51fd8]
//   [ ] 0xdc548  CFogBoxNodeFx_UploadParticlePositions_maybe  [dead]
//   [x] 0xdc618  CFogBoxNodeFx_RandomizeParticlePositions_maybe
//   [x] 0xdc8b0  CFogBoxNodeFx_InitParticles_maybe
//   [x] 0xdcb20  CFogBoxNodeFx_PostLoad
//   [x] 0xdcde0  CFogBoxNodeFx_Create
//   [x] 0xdcfa0  CFogBoxNodeFx_CreateArray
//   [x] 0xdd1f8  CFogBoxNodeFx_Load
//   [ ] 0xde0b0  CFogBoxNodeFx_Save
//   [x] 0xdef38  CFogBoxNodeFx_UpdateParticles_maybe
//
//   [ ] 0x9a4da8  CFogBoxNodeFx_IsKindOfClass  [inline]
//   [ ] 0x9a4e08  CFogBoxNodeFx_GetClassType  [inline]
//   [ ] 0x9a4e10  CFogBoxNodeFx_GetClassID  [inline]
//   [ ] 0x9a4e18  CFogBoxNodeFx_Destructor  [inline]
//   [ ] 0x9a4e58  SortParticlesByKey_maybe  [inline]
//   [ ] 0x9a5320  CFogBoxNodeFx_DeletingDestructor  [inline]
#include "k2000/scenegraph/CFogBoxNodeFx.h"

#include <cmath>
#include <cstring>

#include "Renderware/rpworld/RpAtomic.h"
#include "Renderware/rwcore/RwCamera.h"
#include "Renderware/rwcore/RwMatrix.h"
#include "crt/ppc_ops.h"
#include "crt/xpowfast.h"
#include "crt/vmx_ops.h"
#include "crt/xsinf.h"
#include "k2000/cameras/CameraContext.h"
#include "k2000/core/Stub.h"
#include "k2000/geometry/CGeometry.h"
#include "k2000/io/IKFile.h"
#include "k2000/memory/Mem.h"
#include "k2000/misc/ClassRegistry.h"
#include "k2000/misc/FloatApproach.h"
#include "k2000/misc/Mat4.h"
#include "k2000/render/CRenderer.h"
#include "k2000/scenegraph/CSGMovable.h"
#include "k2000/system/IKTime.h"


namespace {

// Rand_Int's low 16 bits as a float (rldicl 48, fcfid, frsp). Macros, so that the rand log names the fog box.
#define FogRandU16() static_cast<float>(static_cast<uint16_t>(Rand_Int()))
// fmadds(u, TOC -0x5038 (0xb8000080), TOC -0x5034 (1.0f)): (-1, 1].
#define FogRandSigned() ppc::fmadds(FogRandU16(), kRandScale, 1.0f)

const float kRandScale = [] {
    const uint32_t bits = 0xb8000080u;
    float f;
    std::memcpy(&f, &bits, 4);
    return f;
}();
const float kDegToRad = 0x1.1df468p-6f;  // TOC -0x4fac (0x3c8efa34)
const float kHidden = 9999.0f;           // TOC -0x4f9c: a particle out of sight
const uint8_t kColorWhite[4] = {0xff, 0xff, 0xff, 0xff};  // 0x00c50dfc

void SetFloatBits(uint32_t* dst, float value) { std::memcpy(dst, &value, 4); }
RpPTankData* PTank(CParticleGeometry* geometry) { return geometry->m_pRpAtomic->ptank; }
uint8_t* LockArray(CParticleGeometry* geometry, uint32_t flag, int32_t* stride = nullptr) {
    RpPTankLockStruct lock = {nullptr, 0};
    if (RpPTankAtomicLock(geometry->m_pRpAtomic, &lock, flag, 0x40000000) == 0) return nullptr;
    if (stride != nullptr) *stride = lock.stride;
    return lock.data;
}

// 0x002403e0 Mat4_TransformVec4Array_VMX_maybe: `count` 16-byte points through `m` (in place allowed), the AltiVec
// way (crt/vmx_ops.h, RPCS3's semantics: fused, results with a zero exponent flushed): x * right (vmaddfp with +0),
// then fused with y * up and z * at, then plus the position (vaddfp), all four lanes stored (stvx): the w lane comes
// from the rows' fourth words (the flags and pad words of the CMatrix34, as floats).
void TransformVec4Array(const CMatrix34* m, float* out, const float* in, int32_t count) {
    float rows[4][4];
    std::memcpy(rows, m, sizeof rows);  // right + flags, up + pad, at + pad, pos + pad
    for (int32_t i = 0; i < count; ++i, in += 4, out += 4) {
        const float x = in[0], y = in[1], z = in[2];
        float r[4];
        for (int32_t lane = 0; lane < 4; ++lane) {
            const float a = vmx::Madd(x, rows[0][lane], 0.0f);
            const float b = vmx::Madd(rows[1][lane], y, a);
            const float c = vmx::Madd(rows[2][lane], z, b);
            r[lane] = vmx::Add(c, rows[3][lane]);
        }
        std::memcpy(out, r, 16);
    }
}

// The fades' powers (the jump tables at 0xdf4ac / 0xdf994: exponents 0..7 as products; above,
// TocBridge_Math_PowFast_maybe 0x98ec60, crt/xpowfast.h).
float FadePower(float x, uint8_t exponent) {
    switch (exponent) {
        case 0: return 1.0f;
        case 1: return x;
        case 2: return x * x;
        case 3: { const float a = x * x; return x * a; }
        case 4: { const float a = x * x; return a * a; }
        case 5: { const float a = x * x; const float b = x * a; return a * b; }
        case 6: { const float a = x * x; const float b = x * a; return b * b; }
        case 7: { const float a = x * x; const float b = x * a; const float c = x * b; return b * c; }
        default:
            // 0x000df7b0 / 0x000df9b8: the exponent as a float (clrldi, fcfid, frsp), TocBridge_Math_PowFast_maybe 0x98ec60.
            return crt::PowFast(x, static_cast<float>(static_cast<double>(exponent)));
    }
}

// The game's inlined cosf / sinf with the library call for a negative argument.
bool SignBit(float x) {
    int32_t bits;
    std::memcpy(&bits, &x, 4);
    return bits < 0;
}
float GameCos(float x) { return SignBit(x) ? crt::LibCosf(-x) : crt::InlineCosf(x); }
float GameSin(float x) { return SignBit(x) ? -crt::LibSinf(-x) : crt::InlineSinf(x); }

// A colour key's colour: per channel fctiwz(fmadds(t, high - low, low)).
void LerpKeyColor(const CFogBoxNodeFx::SEntry728& entry, float t, uint8_t* out) {
    for (int32_t c = 0; c < 4; ++c) {
        const float low = static_cast<float>(entry.m_raw08[c]);
        out[c] = static_cast<uint8_t>(ppc::fctiwz(ppc::fmadds(t, static_cast<float>(entry.m_raw0c[c]) - low, low)));
    }
}
// The distance between two colours (fmuls, fmadds x3 in the order d1, d0, d2, d3; Math_Sqrtf).
float ColorDistance(const uint8_t* a, const uint8_t* b) {
    float d[4];
    for (int32_t c = 0; c < 4; ++c) d[c] = static_cast<float>(static_cast<int32_t>(b[c]) - static_cast<int32_t>(a[c]));
    return std::sqrt(ppc::fmadds(d[3], d[3], ppc::fmadds(d[2], d[2], ppc::fmadds(d[0], d[0], d[1] * d[1]))));
}

// A particle's move toward its target (inlined in modes 0 and 3): on it when the step reaches it, else by the step
// along the difference (rwInvSqrt).
void StepToTarget(CFogBoxNodeFx::SParticle* p, float dt) {
    float* pos = p->m_position;
    const float* t = p->m_target;
    if (pos[0] == t[0] && pos[1] == t[1] && pos[2] == t[2]) return;
    const float step = dt * p->m_fSpeed;
    const float d0 = t[0] - pos[0];
    const float d1 = t[1] - pos[1];
    const float d2 = t[2] - pos[2];
    const float lengthSquared = ppc::fmadds(d2, d2, ppc::fmadds(d0, d0, d1 * d1));
    if (step * step > lengthSquared) {
        pos[0] = t[0];
        pos[1] = t[1];
        pos[2] = t[2];
        return;
    }
    const float k = step * rwInvSqrt(lengthSquared);  // 0x114d8 Math_InvSqrtf
    pos[2] = ppc::fmadds(d2, k, pos[2]);
    pos[0] = ppc::fmadds(d0, k, pos[0]);
    pos[1] = ppc::fmadds(d1, k, pos[1]);
}

bool AtTarget(const CFogBoxNodeFx::SParticle* p) {
    return p->m_position[0] == p->m_target[0] && p->m_position[1] == p->m_target[1] && p->m_position[2] == p->m_target[2];
}

}  // namespace

// 0x000dcde0 CFogBoxNodeFx_Create: the constructor's stores, in their order.
CFogBoxNodeFx::CFogBoxNodeFx() {
    for (SEntry728& entry : m_aEntries728) {
        entry.m_af[0] = 1.0f;  // TOC -0x5034
        entry.m_af[1] = 0.0f;
        std::memcpy(entry.m_raw08, kColorWhite, 4);  // 0x00c50dfc
        std::memcpy(entry.m_raw0c, kColorWhite, 4);
    }
    m_unk808 = 0.0f;
    m_unk810 = 0.0f;
    m_unk80c = 0.0f;
    m_pTexture = nullptr;
    m_pGeometry = nullptr;
    m_aColors = nullptr;
    m_pUnk7ac = nullptr;
    m_pRandomValues = nullptr;
    m_pUnk7ec = nullptr;
    m_pUnk7f0 = nullptr;
    m_pSwirlRadius = nullptr;
    m_pSwirlSpeed = nullptr;
    m_fTime = 0.0f;
    m_pUnk7fc = nullptr;
    m_pUnk834 = nullptr;
    m_aBoxes = nullptr;
    m_apVisibleBoxes = nullptr;
    m_pSortKeys = nullptr;
    m_aParticleRefs = nullptr;
}

// 0x000da5c0 CFogBoxNodeFx_Destroy
void CFogBoxNodeFx::Destroy() {
    CNode::Destroy();  // 0xcbe10
    auto release = [](auto*& block) {
        if (block != nullptr) {
            Mem_FreeAligned16(block);
            block = nullptr;
        }
    };
    release(m_aColors);
    release(m_pUnk7ac);
    release(m_pRandomValues);
    release(m_pUnk7ec);
    release(m_pUnk7f0);
    release(m_pSwirlRadius);
    release(m_pSwirlSpeed);
    release(m_pUnk7fc);
    release(m_pSortKeys);
    if (m_aParticleRefs != nullptr) {
        delete[] m_aParticleRefs;  // OperatorDeleteArray
        m_aParticleRefs = nullptr;
    }
    release(m_pUnk834);
    if (m_aBoxes != nullptr) {
        for (uint32_t i = 0; i < m_ui32NbBoxes; ++i) RwMatrixDestroy_Thunk(m_aBoxes[i].m_pMatrix);
        Mem_FreeAligned16(m_aBoxes);  // with m_apVisibleBoxes (the same buffer)
        m_aBoxes = nullptr;
    }
}

// 0x000dab30 CFogBoxNodeFx_MessageProc
int32_t CFogBoxNodeFx::MessageProc(uint16_t message, void* /*data*/) {
    if (message == 0x1a00) {
        m_unk80c = 1.0f;
        m_unk808 = m_unk804;
        return 0;
    }
    if (message != 0x1a01) return 1;
    m_unk808 = 0.0f;
    m_unk80c = 1.0f;
    return 0;
}

// 0x000dcb20 CFogBoxNodeFx_PostLoad
int32_t CFogBoxNodeFx::PostLoad(int32_t type) {
    INodeFx::PostLoad(type);  // 0xeca78 CNodeFx_PostLoadBase_maybe
    m_pGeometry = static_cast<CParticleGeometry*>(m_lGeometryList);
    const float length3 = std::sqrt(ppc::fmadds(m_unk5c[2], m_unk5c[2], ppc::fmadds(m_unk5c[0], m_unk5c[0], m_unk5c[1] * m_unk5c[1])));
    const float length2 = std::sqrt(ppc::fmadds(m_unk68[0], m_unk68[0], m_unk68[1] * m_unk68[1]));
    m_unk7d4 = 1.0f / m_unk7d0;                    // TOC -0x5034 = 1.0f
    m_unk30 = ppc::fmadds(length2, 0.5f, length3);  // TOC -0x5014 = 0.5f
    m_unk7e4 = 1.0f / m_unk7e0;
    AllocParticleArrays();
    // The atomic's sphere (the morph sphere update when its flag 2 is set: never for the shim's PTank atomics).
    RpAtomic* atomic = m_pGeometry->m_pRpAtomic;
    atomic->boundingSphere[0] = 0.0f;  // 0x00c50d64
    atomic->boundingSphere[1] = 0.0f;
    atomic->boundingSphere[2] = 0.0f;
    atomic->boundingSphere[3] = 100000.0f;  // TOC -0x5018
    atomic->flags &= 0xfffffffdu;
    atomic->privateFlags |= 1;
    RpPTankData* ptank = PTank(m_pGeometry);
    SetFloatBits(&ptank->renderC0[0], m_unk68[0]);
    SetFloatBits(&ptank->renderC0[1], m_unk68[1]);
    ptank->flags40 |= 0x4000;
    ptank->texCoordsE0[0] = 0;
    ptank->texCoordsE0[1] = 0;
    SetFloatBits(&ptank->texCoordsE0[2], 1.0f);
    SetFloatBits(&ptank->texCoordsE0[3], 1.0f);
    ptank->flags40 |= 0x80000;
    m_pGeometry->SetBlendMode(m_aUnk720[0]);  // 0x88028 CGeometry_SetBlendMode
    InitParticles();
    m_unk70 = -1.0f;  // TOC -0x5004
    m_unk71c = 0;
    InitParticleColors();
    if (type == 0) {
        for (uint32_t i = 0; i < m_ui32NbBoxes; ++i) m_aBoxes[i].m_unk04 = 0;
        if ((m_sgProperties & 0x800) != 0) m_unk40 = 0;
    }
    return 1;
}

// 0x000dbfa0 CFogBoxNodeFx_AllocParticleArrays_maybe
void CFogBoxNodeFx::AllocParticleArrays() {
    if (m_pSortKeys != nullptr) {
        Mem_FreeAligned16(m_pSortKeys);
        m_pSortKeys = nullptr;
    }
    if (m_aParticleRefs != nullptr) {
        delete[] m_aParticleRefs;  // OperatorDeleteArray
        m_aParticleRefs = nullptr;
    }
    m_pSortKeys = static_cast<float*>(Mem_AllocAligned16(m_unk54 << 2));
    m_aParticleRefs = new SParticleRef[m_unk54];  // OperatorNewArray(m_unk54 << 4)
    uint8_t* positions = LockArray(m_pGeometry, 1);    // rpPTANKDFLAGPOSITION
    uint8_t* colors = LockArray(m_pGeometry, 2);       // rpPTANKDFLAGCOLOR
    uint8_t* rotations = LockArray(m_pGeometry, 0x20);  // rpPTANKDFLAG2DROTATE
    for (uint32_t box = 0; box < m_ui32NbBoxes; ++box) {
        for (uint32_t i = 0; i < m_unk50; ++i) {
            SParticleRef& ref = m_aParticleRefs[box * m_unk50 + i];
            ref.m_ui16Index = static_cast<uint16_t>(box * m_unk50 + i);
            ref.m_pPosition = reinterpret_cast<float*>(positions);
            positions += 0x10;
            ref.m_pColor = colors;
            colors += 4;
            ref.m_pRotation = nullptr;
            if ((m_sgProperties & 0x2000) != 0) ref.m_pRotation = reinterpret_cast<float*>(rotations);
            rotations += 4;
        }
    }
    m_pGeometry->UnlockPTank();  // vt+0x8c
}

// 0x000dae70 CFogBoxNodeFx_InitParticleRandomValues_maybe
void CFogBoxNodeFx::InitParticleRandomValues() {
    float* values = m_pRandomValues;
    if (values == nullptr) {
        values = static_cast<float*>(Mem_AllocAligned16(m_unk50 << 3));
        m_pRandomValues = values;
    }
    uint8_t* rotations = LockArray(m_pGeometry, 0x20);
    for (uint32_t i = 0; i < m_unk50; ++i, values += 2) {
        const float base = m_unk7bc[2];  // +0x7c4
        const float r = FogRandSigned();
        const float speedBase = m_unk7bc[0];  // +0x7bc
        const float rotation = ppc::fmadds(r, m_unk7bc[3], base);  // +0x7c8
        const float s = FogRandSigned();
        values[0] = rotation;
        values[1] = ppc::fmadds(s, m_unk7bc[1], speedBase);  // +0x7c0
    }
    for (uint32_t box = 0; box < m_ui32NbBoxes; ++box) {
        for (uint32_t i = 0; i < m_unk50; ++i) {
            std::memcpy(rotations, &m_pRandomValues[i * 2], 4);
            rotations += 4;
        }
    }
}

// 0x000dbae0 CFogBoxNodeFx_InitParticlesRandomInBox_maybe. STUB(C2.9 fx: the emitter path with flag 0x20000 in mode 0
// (per box, through the box matrices) is not ported; no fog box of any level uses it: the 189 CFogBoxNodeFx of LVL010..LVL120 and their sectors are modes 0 / 1 / 3 without flag 0x20000).
void CFogBoxNodeFx::InitParticlesRandomInBox() {
    if ((m_sgProperties & 0x20000) != 0 && m_unk71f == 0) {
        DOTD_STUB_ONCE("CFogBoxNodeFx_InitParticlesRandomInBox_maybe: flag 0x20000 (C2.9 fx)");
        return;
    }
    RandomizeParticlePositions();  // the same code (without RandomizeParticlePositions' allocations)
}

// 0x000dc618 CFogBoxNodeFx_RandomizeParticlePositions_maybe (InitParticlesRandomInBox's first path is the same code)
void CFogBoxNodeFx::RandomizeParticlePositions() {
    if (m_unk71f == 3 && m_pSwirlRadius == nullptr && m_pSwirlSpeed == nullptr) {
        m_pSwirlRadius = static_cast<float*>(Mem_AllocAligned16(m_unk50 << 2));
        m_pSwirlSpeed = static_cast<float*>(Mem_AllocAligned16(m_unk50 << 2));
    }
    uint8_t* positions = LockArray(m_pGeometry, 1);
    SParticle* p = m_pUnk7ac;
    for (uint32_t i = 0; i < m_unk50; ++i, ++p) {
        const float x = FogRandSigned() * m_unk5c[0];
        const float y = FogRandSigned() * m_unk5c[1];
        const float base = m_unk7b0;
        const float z = FogRandSigned() * m_unk5c[2];
        float speed = ppc::fmadds(FogRandSigned(), m_unk7b4, base);
        if (!(speed >= 0.0f)) speed = 0.0f;
        p->m_fSpeed = speed;
        p->m_position[0] = x;
        p->m_position[2] = z;
        p->m_position[1] = y;
        p->m_target[0] = x;
        p->m_target[2] = z;
        p->m_target[1] = y;
    }
    for (uint32_t box = 0; box < m_ui32NbBoxes; ++box) {
        for (uint32_t i = 0; i < m_unk50; ++i) {
            std::memcpy(positions, m_pUnk7ac[i].m_position, 0xc);
            positions += 0x10;
        }
    }
}

// 0x000dc8b0 CFogBoxNodeFx_InitParticles_maybe (the jump table at 0xdc920)
void CFogBoxNodeFx::InitParticles() {
    if ((m_sgProperties & 0x2000) != 0) InitParticleRandomValues();
    switch (m_unk71f) {
        case 0:
            InitParticlesRandomInBox();
            break;
        case 1: {
            // The ring: the start angles evenly spread, the angular speeds at random (1 rand draw each).
            const float step = 6.28318548f / static_cast<float>(m_unk50);  // TOC -0x503c
            float angle = 0.0f;
            for (uint32_t i = 0; i < m_unk50; ++i) {
                m_pUnk7ec[i] = angle;
                angle = angle + step;
                const float base = m_unk7b0;
                m_pUnk7f0[i] = ppc::fmadds(FogRandSigned(), m_unk7b4, base);
            }
            break;
        }
        case 2:
            // STUB(C2.9 fx: CFogBoxNodeFx_InitParticlePositions_maybe 0xdc1f8, mode 2: no fog box of any level uses it: the 189 CFogBoxNodeFx of LVL010..LVL120 and their sectors are modes 0 / 1 / 3 without flag 0x20000).
            DOTD_STUB_ONCE("CFogBoxNodeFx_InitParticles: mode 2 (0xdc1f8, C2.9)");
            break;
        case 3:
            RandomizeParticlePositions();
            break;
        case 4: {
            uint8_t* positions = LockArray(m_pGeometry, 1);
            for (uint32_t box = 0; box < m_ui32NbBoxes; ++box) {
                for (uint32_t i = 0; i < m_unk50; ++i) {
                    std::memcpy(positions, m_pUnk7ac[i].m_position, 0xc);
                    positions += 0x10;
                }
            }
            break;
        }
        default:
            break;
    }
    m_unk70 = -1.0f;
    m_unk71c = 0;
    InitParticleColors();
    m_pGeometry->UnlockPTank();  // vt+0x8c
}

// 0x000db1a0 CFogBoxNodeFx_InitParticleColors_maybe. STUB(C2.9 fx: mode 4's colours by height (no rand draw) are not
// ported; no fog box of any level uses it: the 189 CFogBoxNodeFx of LVL010..LVL120 and their sectors are modes 0 / 1 / 3 without flag 0x20000).
void CFogBoxNodeFx::InitParticleColors() {
    if (m_aColors == nullptr) m_aColors = static_cast<SParticleColor*>(Mem_AllocAligned16(m_unk50 << 5));
    if (m_unk71f == 4) {
        DOTD_STUB_ONCE("CFogBoxNodeFx_InitParticleColors_maybe: mode 4 (C2.9 fx)");
        m_pGeometry->UnlockPTank();
        return;
    }
    for (uint32_t i = 0; i < m_unk50; ++i) {
        SParticleColor* c = &m_aColors[i];
        const uint32_t inBox = i - ppc::divwu(i, m_unk50) * m_unk50;
        c->m_ui32Key = inBox - ppc::divwu(inBox, m_unk724) * m_unk724;
        std::memcpy(c->m_current, kColorWhite, 4);
        c->m_colorF[0] = 255.0f;
        std::memcpy(c->m_target, kColorWhite, 4);
        c->m_fSpeed = 0.0f;
        c->m_colorF[3] = 255.0f;
        c->m_colorF[2] = 255.0f;
        c->m_colorF[1] = 255.0f;
        const uint32_t key = c->m_ui32Key;
        uint32_t next = key + 1;
        if (!(m_unk724 > next)) next = 0;
        uint8_t a[4];
        uint8_t b[4];
        LerpKeyColor(m_aEntries728[key], FogRandU16() / 65535.0f, a);
        LerpKeyColor(m_aEntries728[next], FogRandU16() / 65535.0f, b);
        const float distance = ColorDistance(a, b);
        const float range = m_aEntries728[key].m_af[1];
        float f = ppc::fmadds(range, FogRandSigned(), 1.0f);
        if (f == 0.0f) f = 9.99999997e-07f;  // TOC -0x5008
        f = std::fabs(f);
        c->m_fSpeed = distance / ((f * m_aEntries728[key].m_af[0]) * 255.0f);
        std::memcpy(c->m_current, a, 4);
        for (int32_t k = 0; k < 4; ++k) c->m_colorF[k] = static_cast<float>(c->m_current[k]);
        std::memcpy(c->m_target, b, 4);
        // The original then clears the speed and puts the target back on the current colour.
        m_aColors[i].m_fSpeed = 0.0f;
        std::memcpy(m_aColors[i].m_target, m_aColors[i].m_current, 4);
    }
    uint8_t* colors = LockArray(m_pGeometry, 2);
    for (uint32_t box = 0; box < m_ui32NbBoxes; ++box) {
        for (uint32_t i = 0; i < m_unk50; ++i) {
            const uint32_t index = m_aParticleRefs[box * m_unk50 + i].m_ui16Index;
            std::memcpy(colors, m_aColors[index - ppc::divwu(index, m_unk50) * m_unk50].m_current, 4);
            colors += 4;
        }
    }
    m_pGeometry->UnlockPTank();  // vt+0x8c
}

// 0x000da968 CFogBoxNodeFx_RandomizeEmitterParticles_maybe
void CFogBoxNodeFx::RandomizeEmitterParticles(int32_t enable, uint32_t boxIndex) {
    if (m_unk71f != 0 || (m_sgProperties & 0x20000) == 0 || enable == 0) return;
    const SBox* box = &m_aBoxes[boxIndex];
    SParticle* p = m_pUnk7ac;
    for (uint32_t i = 0; i < m_unk50; ++i, ++p) {
        CVector3 v;
        v.x = FogRandSigned() * m_unk5c[0];
        v.y = FogRandSigned() * m_unk5c[1];
        v.z = (FogRandSigned() * m_unk5c[2]) * box->m_unk08;
        Mat4_TransformPoints(box->m_pMatrix, &v, &v, 1);
        p->m_position[2] = v.z;
        p->m_position[0] = v.x;
        p->m_position[1] = v.y;
        p->m_target[0] = v.x;
        p->m_target[2] = v.z;
        p->m_target[1] = v.y;
    }
}

// The colour key step (inlined in modes 0 / 1 / 3 at 0xdfdc4 / 0xe0b40 / 0xe1138).
void CFogBoxNodeFx::StepParticleColor(SParticleColor* c, float dt) {
    if (std::memcmp(c->m_current, c->m_target, 4) != 0) {
        const float d1 = static_cast<float>(c->m_target[1]) - c->m_colorF[1];
        const float d0 = static_cast<float>(c->m_target[0]) - c->m_colorF[0];
        const float d2 = static_cast<float>(c->m_target[2]) - c->m_colorF[2];
        const float d3 = static_cast<float>(c->m_target[3]) - c->m_colorF[3];
        const float step = (dt * c->m_fSpeed) * 255.0f;
        const float sum = ppc::fmadds(d3, d3, ppc::fmadds(d2, d2, ppc::fmadds(d0, d0, d1 * d1)));
        if (step * step > sum) {
            std::memcpy(c->m_current, c->m_target, 4);
        } else {
            const float k = step * rwInvSqrt(sum);  // 0x114d8 Math_InvSqrtf
            c->m_colorF[0] = ppc::fmadds(d0, k, c->m_colorF[0]);
            c->m_colorF[3] = ppc::fmadds(d3, k, c->m_colorF[3]);
            c->m_colorF[1] = ppc::fmadds(d1, k, c->m_colorF[1]);
            c->m_colorF[2] = ppc::fmadds(d2, k, c->m_colorF[2]);
            for (int32_t i = 0; i < 4; ++i) c->m_current[i] = static_cast<uint8_t>(ppc::fctiwz(c->m_colorF[i]));
        }
    }
    if (std::memcmp(c->m_current, c->m_target, 4) != 0) return;
    // On the target: the next key, its colour and the next one's (2 rand draws), the time to it (1 rand draw).
    uint32_t key = c->m_ui32Key + 1;
    c->m_ui32Key = key;
    if (!(m_unk724 > key)) {
        key = 0;
        c->m_ui32Key = 0;
    }
    uint32_t next = key + 1;
    if (!(m_unk724 > next)) next = 0;
    uint8_t a[4];
    uint8_t b[4];
    LerpKeyColor(m_aEntries728[key], FogRandU16() / 65535.0f, a);
    LerpKeyColor(m_aEntries728[next], FogRandU16() / 65535.0f, b);
    const float distance = ColorDistance(a, b);
    const float range = m_aEntries728[key].m_af[1];
    float f = ppc::fmadds(range, FogRandSigned(), 1.0f);
    if (f == 0.0f) f = 9.99999997e-07f;
    f = std::fabs(f);
    c->m_fSpeed = distance / ((f * m_aEntries728[key].m_af[0]) * 255.0f);
    std::memcpy(c->m_target, b, 4);
}

// 0x000def38 CFogBoxNodeFx_UpdateParticles_maybe
void CFogBoxNodeFx::UpdateAndExtract(float /*maxDistanceSquared*/, RenderQueue** stages, IKTime* frameClock, RwCamera* camera,
                                     int32_t /*distanceCull*/) {
    if ((m_sgProperties & 4) != 0) return;
    if (frameClock->m_eCurrentState == 0 || (m_sgProperties & 0x4000) != 0) {
        m_fDeltaTime = frameClock->m_afDeltaTime[0];
    } else {
        m_fDeltaTime = 0.0f;
    }
    // engine +0x08 +0x2c +0x04 +0x80: the camera's position (the stored LTM; natively RwFrameGetLTM makes it current).
    const RwV3d cam = RwFrameGetLTM(static_cast<CSGMovable*>(Engine_GetCameraContext()->m_pCamera)->m_pRwFrame)->pos;
    uint8_t* colorBase = LockArray(m_pGeometry, 2);
    uint8_t* positionBase = LockArray(m_pGeometry, 1);
    uint8_t* rotations = nullptr;
    if ((m_sgProperties & 0x2000) != 0) rotations = LockArray(m_pGeometry, 0x20);
    SBox* box = m_aBoxes;
    float turn = 0.0f;
    if (m_unk71f == 3) {
        turn = m_fDeltaTime * m_unk800;
        FloatApproach_Step(m_fDeltaTime, &m_unk808);
    }
    const float dt = m_fDeltaTime;
    const float time = m_fTime + m_fDeltaTime;
    m_unk58 = 0;
    m_ui32NbVisibleBoxes = 0;
    const float radius = m_unk30;
    m_fTime = time;
    uint8_t* colors = colorBase;
    uint8_t* positions = positionBase;
    const uint32_t n = m_unk50;
    const CMatrix34* ltm = reinterpret_cast<const CMatrix34*>(FrameLtm(m_pRwFrame));  // the stored LTM (+0x50, no sync)
    for (uint32_t left = m_unk40; left != 0; --left, ++box) {
        const uint32_t remaining = left - 1;  // r24: the boxes after this one
        CVector3 center = box->m_pMatrix->m_pos;
        if ((m_sgProperties & 0x400) != 0) Mat4_TransformPoints(ltm, &center, &center, 1);
        const float sphere[4] = {center.x, center.y, center.z, radius};
        if (RwCameraFrustumTestSphere(camera, sphere) == 0) continue;  // BridgeRwCameraFrustumTestSphere_maybe
        const float dy = cam.y - center.y;
        const float dx = cam.x - center.x;
        const float dz = cam.z - center.z;
        box->m_fDistance = std::sqrt(ppc::fmadds(dz, dz, ppc::fmadds(dx, dx, dy * dy))) - m_unk30;  // Math_Sqrtf
        if (m_ui32NbVisibleBoxes == 0) {
            // The first visible box simulates the particles.
            const SParticleRef* refs = &m_aParticleRefs[remaining * n];
            switch (m_unk71f) {
                case 0:
                case 3: {
                    if (m_unk71f == 0 && (m_sgProperties & 0x20000) != 0) {
                        // STUB(C2.9 fx: mode 0 with flag 0x20000 (0xe22b8, the emitter particles): no fog box of any level uses it: the 189 CFogBoxNodeFx of LVL010..LVL120 and their sectors are modes 0 / 1 / 3 without flag 0x20000).
                        DOTD_STUB_ONCE("CFogBoxNodeFx_UpdateParticles: mode 0 with flag 0x20000 (C2.9 fx)");
                        break;
                    }
                    if (m_unk71f == 3) Mat4_RotateLocalZDeg(turn, box->m_pMatrix);  // the first visible box turns
                    uint8_t* color = colors;
                    float* position = reinterpret_cast<float*>(positions);
                    for (uint32_t j = 0; j < n; ++j, color += 4, position += 4) {
                        const uint32_t index = refs[j].m_ui16Index;
                        const uint32_t i = index - ppc::divwu(index, n) * n;
                        SParticleColor* c = &m_aColors[i];
                        SParticle* p = &m_pUnk7ac[i];
                        if (m_unk724 > 1) StepParticleColor(c, dt);
                        if (m_unk71f == 0) {
                            std::memcpy(color, c->m_current, 4);
                            StepToTarget(p, dt);
                            if (AtTarget(p)) {
                                // A new target in the box (3 rand draws).
                                const float x = FogRandSigned() * m_unk5c[0];
                                const float y = FogRandSigned() * m_unk5c[1];
                                p->m_target[0] = x;
                                p->m_target[1] = y;
                                p->m_target[2] = FogRandSigned() * m_unk5c[2];
                            }
                            position[2] = p->m_position[2];
                            position[0] = p->m_position[0];
                            position[1] = p->m_position[1];
                        } else {
                            // Mode 3: the particles rise from the bottom to the top of the box, faded by their height
                            // and by +0x810, swirling around their column.
                            color[0] = c->m_current[0];
                            color[1] = c->m_current[1];
                            color[2] = c->m_current[2];
                            const float height = std::fabs(p->m_position[2] / (m_unk5c[2] * box->m_unk08));
                            if (height < 1.0f) {
                                color[3] = static_cast<uint8_t>(ppc::fctiwz((m_unk810 * 255.0f) * (1.0f - height)));
                            } else {
                                color[3] = 0;
                            }
                            StepToTarget(p, dt);
                            float* swirlRadius = &m_pSwirlRadius[i];
                            float* swirlSpeed = &m_pSwirlSpeed[i];
                            if (AtTarget(p)) {
                                float top = m_unk5c[2];
                                if (p->m_position[2] == m_unk5c[2]) {
                                    // At the top: back to the bottom at random (3 rand draws and the speed).
                                    const float x = FogRandSigned() * m_unk5c[0];
                                    const float y = FogRandSigned() * m_unk5c[1];
                                    const float bottom = -m_unk5c[2];
                                    const float base = m_unk7b0;
                                    float speed = ppc::fmadds(FogRandSigned(), m_unk7b4, base);
                                    if (speed < 0.0f) speed = 0.0f;
                                    p->m_fSpeed = speed;
                                    p->m_position[2] = bottom;
                                    p->m_position[0] = x;
                                    p->m_position[1] = y;
                                    top = m_unk5c[2];
                                }
                                const float x = p->m_position[0];
                                const float y = p->m_position[1];
                                p->m_target[1] = y;
                                p->m_target[0] = x;
                                p->m_target[2] = top;
                                if (m_unk814 != 0.0f || m_unk818 != 0.0f) {
                                    // A swirl radius and speed (2 rand draws), the radius kept inside the box.
                                    *swirlRadius = ppc::fmadds(FogRandSigned(), m_unk818, m_unk814);
                                    *swirlSpeed = ppc::fmadds(FogRandSigned(), m_unk820, m_unk81c);
                                    const float ax = std::fabs(x);
                                    const float ay = std::fabs(y);
                                    const float ar = std::fabs(*swirlRadius);
                                    if (ax + ar > m_unk5c[0]) *swirlRadius = m_unk5c[0] - ax;
                                    if (ay + ar > m_unk5c[1]) *swirlRadius = m_unk5c[1] - ay;
                                } else {
                                    *swirlRadius = 0.0f;
                                    *swirlSpeed = 0.0f;
                                }
                            }
                            const float px = p->m_position[0];
                            const float py = p->m_position[1];
                            const float pz = p->m_position[2];
                            position[1] = py;
                            position[0] = px;
                            position[2] = pz;
                            const float r = *swirlRadius;
                            if (r != 0.0f) {
                                const float a = *swirlSpeed * m_fTime;
                                const float cosA = GameCos(a);
                                const float sinA = GameSin(a);
                                position[2] = pz;
                                position[1] = ppc::fmadds(sinA, r, py);
                                position[0] = ppc::fmadds(cosA, r, px);
                            }
                        }
                        if ((m_sgProperties & 0x2000) != 0) {
                            float* value = &m_pRandomValues[i * 2];
                            if (m_ui32NbVisibleBoxes == 0) value[0] = ppc::fmadds(value[1], m_fDeltaTime, value[0]);
                            const float rotation = value[0] * kDegToRad;
                            std::memcpy(rotations, &rotation, 4);
                            rotations += 4;
                        }
                    }
                    break;
                }
                case 1: {
                    // 0x000dfc1c mode 1, the ring (the air currents' boxes): every particle on the ellipse of the box's
                    // x / z half extents at its start angle (+0x7ec) plus its angular speed (+0x7f0) times the time.
                    uint8_t* color = colors;
                    float* position = reinterpret_cast<float*>(positions);
                    for (uint32_t j = 0; j < n; ++j, color += 4, position += 4) {
                        const uint32_t index = refs[j].m_ui16Index;
                        const uint32_t i = index - ppc::divwu(index, n) * n;
                        SParticleColor* c = &m_aColors[i];
                        if (m_unk724 > 1) StepParticleColor(c, dt);
                        std::memcpy(color, c->m_current, 4);
                        const float angle = ppc::fmadds(m_pUnk7f0[i], m_fTime, m_pUnk7ec[i]);
                        const float rx = m_unk5c[0];
                        const float cosA = GameCos(angle);
                        const float rz = m_unk5c[2];
                        const float sinA = GameSin(angle);
                        position[1] = 0.0f;
                        position[0] = cosA * rx;
                        position[2] = sinA * rz;
                        if ((m_sgProperties & 0x2000) != 0) {
                            float* value = &m_pRandomValues[i * 2];
                            if (m_ui32NbVisibleBoxes == 0) value[0] = ppc::fmadds(value[1], m_fDeltaTime, value[0]);
                            const float rotation = value[0] * kDegToRad;
                            std::memcpy(rotations, &rotation, 4);
                            rotations += 4;
                        }
                    }
                    break;
                }
                default:
                    // STUB(C2.9 fx: modes 2 (0xe0374) and 4 (0xe1a80): no fog box of any level uses it: the 189 CFogBoxNodeFx of LVL010..LVL120 and their sectors are modes 0 / 1 / 3 without flag 0x20000).
                    DOTD_STUB_ONCE("CFogBoxNodeFx_UpdateParticles: mode 2 / 4 (C2.9)");
                    break;
            }
            positions += n * 0x10;
            colors += n * 4;
        } else {
            // The other visible boxes copy the first one's particles.
            if ((m_sgProperties & 0x2000) != 0) std::memmove(rotations, rotations - n * 4, n * 4);
            std::memmove(positions, positions - n * 0x10, n * 0x10);
            std::memmove(colors, colors - n * 4, n * 4);
            positions += n * 0x10;
            colors += n * 4;
            rotations += n * 4;
        }
        m_apVisibleBoxes[m_ui32NbVisibleBoxes] = box;
        ++m_ui32NbVisibleBoxes;
        m_unk58 += n;
    }
    RpPTankData* ptank = PTank(m_pGeometry);
    if (m_ui32NbVisibleBoxes == 0) {
        m_pGeometry->UnlockPTank();  // vt+0x8c
        ptank->flags40 |= 0x800000;
        ptank->numPrt = 0;
        RpAtomic* atomic = m_pGeometry->m_pRpAtomic;  // (the morph sphere update with flag 2: never here)
        atomic->boundingSphere[0] = kHidden;
        atomic->boundingSphere[1] = kHidden;
        atomic->boundingSphere[2] = kHidden;
        atomic->boundingSphere[3] = 0.0f;
        atomic->flags &= 0xfffffffdu;
        atomic->privateFlags |= 1;
    } else {
        if ((m_sgProperties & 0x200) != 0 && m_unk70 < m_fTime) {
            // The flipbook's next frame.
            m_unk70 = m_unk74 + m_fTime;
            uint8_t frame = static_cast<uint8_t>(m_unk71c + 1);
            m_unk71c = frame;
            if (!(static_cast<int32_t>(frame) < static_cast<int32_t>(m_unk71d) * static_cast<int32_t>(m_unk71e))) {
                frame = 0;
                m_unk71c = 0;
            }
            const uint32_t* uv = &m_aPairs78[m_aBytes6b8[frame]][0];
            std::memcpy(ptank->texCoordsE0, uv, 16);
            ptank->flags40 |= 0x80000;
        }
        if ((m_sgProperties & 0x400) != 0) {
            TransformVec4Array(ltm, reinterpret_cast<float*>(positionBase), reinterpret_cast<const float*>(positionBase),
                               static_cast<int32_t>(m_unk58));
        }
        ptank->flags40 |= 0x800000;
        ptank->numPrt = m_unk58;
        const float nearEnd = m_unk7cc + m_unk7d0;
        for (uint32_t v = m_ui32NbVisibleBoxes; v != 0; --v) {
            const uint32_t slot = v - 1;
            const SBox* visible = m_apVisibleBoxes[slot];
            float* first = reinterpret_cast<float*>(positionBase + slot * n * 0x10);
            if ((m_sgProperties & 0x20000) == 0 || m_unk71f != 0) {
                TransformVec4Array(visible->m_pMatrix, first, first, static_cast<int32_t>(n));
            }
            if ((m_sgProperties & 0x8000) != 0 && visible->m_fDistance < nearEnd) {
                // The near fade: hidden up to +0x7cc, faded over +0x7d0.
                for (uint32_t j = 0; j < n; ++j) {
                    float* p = first + j * 4;
                    uint8_t* alpha = &colorBase[(slot * n + j) * 4 + 3];
                    const float dy = cam.y - p[1];
                    const float dx = cam.x - p[0];
                    const float dz = cam.z - p[2];
                    const float d = std::sqrt(ppc::fmadds(dz, dz, ppc::fmadds(dx, dx, dy * dy))) - m_unk7cc;
                    if (d <= 0.0f) {
                        *alpha = 0;
                    } else {
                        if (!(m_unk7d0 <= d)) {
                            const float f = FadePower(d * m_unk7d4, m_unk7d8);
                            *alpha = static_cast<uint8_t>(ppc::fctiwz(f * static_cast<float>(*alpha)));
                        }
                        if (*alpha > 9) continue;
                    }
                    p[2] = kHidden;
                    p[0] = kHidden;
                    p[1] = kHidden;
                }
            }
            if ((m_sgProperties & 0x10000) != 0) {
                // The far fade: hidden from +0x7dc, faded over the +0x7e0 before.
                for (uint32_t j = 0; j < n; ++j) {
                    float* p = first + j * 4;
                    uint8_t* alpha = &colorBase[(slot * n + j) * 4 + 3];
                    const float dy = cam.y - p[1];
                    const float dx = cam.x - p[0];
                    const float dz = cam.z - p[2];
                    const float d = std::sqrt(ppc::fmadds(dz, dz, ppc::fmadds(dx, dx, dy * dy)));
                    if (d >= m_unk7dc) {
                        *alpha = 0;
                    } else {
                        if (!(m_unk7dc - m_unk7e0 >= d)) {
                            const float f = FadePower(std::fabs(d - m_unk7dc) * m_unk7e4, m_unk7e8);
                            *alpha = static_cast<uint8_t>(ppc::fctiwz(f * static_cast<float>(*alpha)));
                        }
                        if (*alpha > 9) continue;
                    }
                    p[2] = kHidden;
                    p[0] = kHidden;
                    p[1] = kHidden;
                }
            }
        }
        if (m_unk71f == 4) DOTD_STUB_ONCE("CFogBoxNodeFx_UpdateParticles: mode 4's depth sort (SortParticlesByKey_maybe, C2.9)");
        m_pGeometry->UpdateAtomicBoundingSphere();  // 0x8a290
        CullAndEnqueueGeometry(stages, frameClock, camera);  // vt+0x84
        m_ui16LastRenderedFrame = g_ui16RenderFrameCounter;
    }
    for (CSGLeaf* child = m_lChildList; child != nullptr; child = child->m_pNext) {
        child->UpdateAndExtract(0.0f, stages, frameClock, camera, 0);  // vt+0x58
    }
}

// 0x000dd1f8 CFogBoxNodeFx_Load
int32_t CFogBoxNodeFx::Load(IKFile* file, int32_t type) {
    INodeFx::Load(file, type);  // 0xeccd8
    if (type != K_LEVEL_PLATEFORMS) return 1;
    ReadU32LE(file, &m_unk40);
    ReadU32LE(file, &m_ui32NbBoxes);
    // One buffer: the boxes, then m_ui32NbBoxes words (PS3: n * 0x14 bytes).
    // One buffer: the boxes, then m_ui32NbBoxes pointers (PS3: n * 0x14 bytes).
    uint8_t* buffer = static_cast<uint8_t*>(Mem_AllocAligned16(m_ui32NbBoxes * static_cast<uint32_t>(sizeof(SBox) + sizeof(SBox*))));
    m_aBoxes = reinterpret_cast<SBox*>(buffer);
    m_apVisibleBoxes = reinterpret_cast<SBox**>(buffer + m_ui32NbBoxes * sizeof(SBox));
    for (uint32_t i = 0; i < m_ui32NbBoxes; ++i) {
        SBox* box = &m_aBoxes[i];
        box->m_pMatrix = RwMatrixCreate_Thunk();
        box->m_unk08 = 1.0f;
        box->m_unk04 = 0;
        CMatrix34_LoadMatrix(box->m_pMatrix, file);
    }
    IKFile_ReadTextureRef(file, &m_pTexture, 0);
    ReadRaw(file, &m_unk71f, 1);
    for (int32_t i = 0; i < 4; ++i) ReadRaw(file, &m_aUnk720[i], 1);
    ReadU32LE(file, &m_unk50);
    ReadU32LE(file, &m_unk54);
    ReadU32LE(file, &m_unk58);
    {
        uint32_t words[3];
        ReadU32LEWords(file, words, 3);
        std::memcpy(m_unk5c, words, 0xc);
    }
    ReadF32LE(file, &m_unk74);
    uint32_t count = 0;
    ReadU32LE(file, &count);
    ReadU32LEWords(file, &m_aPairs78[0][0], count * 2);  // count * 8 bytes
    ReadRaw(file, m_aBytes6b8, count >> 1);
    ReadRaw(file, &m_unk71d, 1);
    ReadRaw(file, &m_unk71e, 1);
    ReadU32LE(file, &m_unk724);
    uint32_t entries = 0;
    ReadU32LE(file, &entries);
    for (uint32_t i = 0; i < entries; ++i) {
        SEntry728* entry = &m_aEntries728[i];
        ReadF32LE(file, &entry->m_af[0]);
        ReadF32LE(file, &entry->m_af[1]);
        ReadRaw(file, entry->m_raw08, 4);
        ReadRaw(file, entry->m_raw0c, 4);
    }
    if (m_unk71f != 1) {
        m_pUnk7ac = static_cast<SParticle*>(Mem_AllocAligned16(m_unk50 * 0x1c));
        ReadU32LEWords(file, reinterpret_cast<uint32_t*>(m_pUnk7ac), m_unk50 * 7);
    }
    ReadF32LE(file, &m_unk7b0);
    ReadF32LE(file, &m_unk7b4);
    for (int32_t i = 0; i < 4; ++i) ReadF32LE(file, &m_unk7bc[i]);
    if (m_unk71f == 1) {
        m_pUnk7ec = static_cast<float*>(Mem_AllocAligned16(m_unk50 * 4));
        m_pUnk7f0 = static_cast<float*>(Mem_AllocAligned16(m_unk50 * 4));
        ReadU32LEWords(file, reinterpret_cast<uint32_t*>(m_pUnk7ec), m_unk50);
        ReadU32LEWords(file, reinterpret_cast<uint32_t*>(m_pUnk7f0), m_unk50);
    }
    ReadF32LE(file, &m_unk7f4);
    ReadF32LE(file, &m_unk7f8);
    ReadF32LE(file, &m_unk800);
    ReadF32LE(file, &m_unk804);
    {
        uint32_t words[3];
        ReadU32LEWords(file, words, 3);
        std::memcpy(&m_unk808, &words[0], 4);
        std::memcpy(&m_unk80c, &words[1], 4);
        std::memcpy(&m_unk810, &words[2], 4);
    }
    ReadF32LE(file, &m_unk814);
    ReadF32LE(file, &m_unk818);
    ReadF32LE(file, &m_unk81c);
    ReadF32LE(file, &m_unk820);
    {
        uint32_t words[2];
        ReadU32LEWords(file, words, 2);
        std::memcpy(m_unk68, words, 8);
    }
    ReadF32LE(file, &m_unk30);
    ReadF32LE(file, &m_unk7cc);
    ReadF32LE(file, &m_unk7d0);
    ReadRaw(file, &m_unk7d8, 1);
    ReadF32LE(file, &m_unk7dc);
    ReadF32LE(file, &m_unk7e0);
    ReadRaw(file, &m_unk7e8, 1);
    m_pUnk834 = static_cast<uint8_t*>(Mem_AllocAligned16(m_unk54 * 4));
    ReadRaw(file, m_pUnk834, m_unk54 * 4);  // not swapped
    return 1;
}
