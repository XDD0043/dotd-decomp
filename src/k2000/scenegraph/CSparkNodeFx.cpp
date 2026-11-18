// CSparkNodeFx.cpp - reconstructed original translation unit 0xe79f8-0xea630 (GAME_TOC1, main_toc1), 30 functions, 24 live.
// Primary class: CSparkNodeFx  key 0x70b  category SceneNode  size 0x5c  vtable 0xb18ba8
// Other owners: CTrailNodeFx (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0xe79f8  CSparkNodeFx_Delete
//   [ ] 0xe7a48  RegisterCSparkNodeFxClass
//   [ ] 0xe7ac0  _GLOBAL__I_e7ac0
//   [x] 0xe7ad0  CSparkNodeFx_GetInfo  (INodeFx's 1 mapped to 1: the default)
//   [x] 0xe7b20  CSparkNodeFx_SetParams_maybe
//   [ ] 0xe7b60  CSparkNodeFx_AllocSparkNodes_maybe  [dead]
//   [x] 0xe7c90  CSparkNodeFx_ReleaseAllSparks_maybe
//   [ ] 0xe7df0  CSparkNodeFx_Save
//   [x] 0xe7e18  CSparkNodeFx_RecursiveRegistration  (INodeFx's (returns 1, registers nothing): CSGLeaf's)
//   [x] 0xe7e40  CSparkNodeFx_DeleteArray
//   [x] 0xe7ee0  CSparkNodeFx_BaseDestructor  (C++ destructor chain: vtable stores, then CNode's)
//   [x] 0xe7f20  CSparkNodeFx_Construct  [dead]
//   [x] 0xe7f88  CSparkNodeFx_Destroy
//   [x] 0xe8070  CSparkNodeFx_Load
//   [ ] 0xe8208  CSparkNodeFx_Construct_2  [dead]
//   [x] 0xe8270  CSparkNodeFx_CreateArray
//   [x] 0xe8388  CSparkNodeFx_Create
//   [x] 0xe8408  CSparkNodeFx_DeletingDestructor  (C++ destructor chain + delete)
//   [x] 0xe8460  CSparkNodeFx_Destructor  (C++ destructor chain: vtable stores only)
//   [x] 0xe84a0  CSparkNodeFx_InitSpark_maybe
//   [ ] 0xe9128  CSparkNodeFx_SpawnInitialSparks_maybe  [dead]
//   [x] 0xe9250  CSparkNodeFx_InitSparks_maybe
//   [x] 0xe9410  CSparkNodeFx_PostLoad
//   [x] 0xe96b0  CSparkNodeFx_UpdateSpark_maybe
//   [x] 0xe9c70  CSparkNodeFx_UpdateSparks_maybe
//   [x] 0xea040  CSparkNodeFx_MessageProc
//   [x] 0xea200  CSparkNodeFx_Enqueue
//   [x] 0xea460  CTrailNodeFx_Delete  (DOTD_DECLARE_FACTORIES(CTrailNodeFx))
//   [ ] 0xea4b0  FUN_000ea4b0  [dead]
//   [ ] 0xea590  FUN_000ea590  [dead]
//
//   [ ] 0x9a55b8  CSparkNodeFx_IsKindOfClass  [inline]
//   [ ] 0x9a5618  CSparkNodeFx_GetClassType  [inline]
//   [ ] 0x9a5620  CSparkNodeFx_GetClassID  [inline]
#include "k2000/scenegraph/CSparkNodeFx.h"

#include <cmath>
#include <cstring>

#include "Renderware/rpworld/RpAtomic.h"
#include "Renderware/rwcore/RwCamera.h"
#include "Renderware/rwcore/RwMatrix.h"
#include "crt/ppc_ops.h"
#include "k2000/core/Stub.h"
#include "k2000/cameras/CameraContext.h"
#include "k2000/geometry/CGeometry.h"
#include "k2000/io/IKFile.h"
#include "k2000/logic/render/CMaterial.h"
#include "k2000/misc/ClassRegistry.h"
#include "k2000/misc/Mat4.h"
#include "k2000/scenegraph/CKSparkParam.h"
#include "k2000/scenegraph/CSGMovable.h"
#include "k2000/system/IKTime.h"

namespace {
// TOC -0x4e48 (0xb8000080) and -0x4e44 (1.0f): a rand draw's low 16 bits u map to 1 - u / 32767.75..., in (-1, 1].
const float kRandScale = [] {
    const uint32_t bits = 0xb8000080u;
    float f;
    std::memcpy(&f, &bits, 4);
    return f;
}();

// Rand_Int, its low 16 bits (rldicl 48) as a float (fcfid + frsp: exact). Macros, so that the rand log
// (DOTD_REPLAY_RANDLOG) names the function that draws.
#define RandU16() static_cast<float>(static_cast<uint16_t>(Rand_Int()))
// The signed form: fmadds(u, TOC -0x4e48, 1.0f).
#define RandSigned() ppc::fmadds(RandU16(), kRandScale, 1.0f)

// 0x00c50d34 / 0x00c50d40 / 0x00c50d4c / 0x00c50d64: the shared axes and the null vector.
const CVector3 kAxisX = {1.0f, 0.0f, 0.0f};
const CVector3 kAxisY = {0.0f, 1.0f, 0.0f};
const CVector3 kAxisZ = {0.0f, 0.0f, 1.0f};
const CVector3 kVectorZero = {0.0f, 0.0f, 0.0f};

// A parameter float at its PS3 offset (CKSparkParam keeps the 29 words of +0x04..+0x74 unnamed).
float P(const CKSparkParam* p, uint32_t offset) { return p->m_afUnk04[(offset - 4) / 4]; }

// The PTank data of a particle geometry's atomic (atomic + [0xcf079c] on the PS3).
RpPTankData* PTank(CParticleGeometry* geometry) { return geometry->m_pRpAtomic->ptank; }

// The camera's frame LTM (the original reads the stored one; natively RwFrameGetLTM makes it current): engine +0x08 (camera context) +0x2c (the IKCamera) +0x04 (its frame) +0x50.
const RwMatrix* CameraLtm() {
    return RwFrameGetLTM(static_cast<CSGMovable*>(Engine_GetCameraContext()->m_pCamera)->m_pRwFrame);  // the stored LTM, made current
}

// The original's inlined list removal: `spark` unlinked from the live list (searched from the head), its link cleared.
void UnlinkLive(CSparkNodeFx::SSpark** head, CSparkNodeFx::SSpark* spark) {
    CSparkNodeFx::SSpark* node = *head;
    if (node == nullptr) return;
    if (node == spark) {
        *head = spark->m_pNext;
    } else {
        CSparkNodeFx::SSpark* prev;
        do {
            prev = node;
            node = prev->m_pNext;
            if (node == nullptr) return;
        } while (node != spark);
        prev->m_pNext = spark->m_pNext;
        if (spark->m_pNext != nullptr) spark->m_pNext = nullptr;
    }
    spark->m_pNext = nullptr;
}

// The original's inlined pool take: the free list's head (null when empty: the original then writes through null).
CSparkNodeFx::SSpark* TakeFree(CSparkNodeFx::SSpark** freeHead) {
    CSparkNodeFx::SSpark* spark = *freeHead;
    if (spark == nullptr) return nullptr;
    CSparkNodeFx::SSpark* next = spark->m_pNext;
    if (next != nullptr) {
        spark->m_pNext = nullptr;
        *freeHead = next;
    } else {
        *freeHead = nullptr;
    }
    return spark;
}

// A colour byte from fctidz (the low byte of the 64-bit result).
uint8_t ColorByteD(float x) { return static_cast<uint8_t>(ppc::fctidz(x)); }

// InitSpark's random colour: per channel t = u / 65535, (1 - t) * a + t * b (fmuls, fsubs, fmadds), four draws first.
void RandomColor(const uint8_t* a, const uint8_t* b, uint8_t* out) {
    float t[4];
    t[0] = RandU16();
    t[1] = RandU16();
    t[0] = t[0] / 65535.0f;  // TOC -0x4e2c
    t[2] = RandU16();
    t[1] = t[1] / 65535.0f;
    t[3] = RandU16();
    t[2] = t[2] / 65535.0f;
    t[3] = t[3] / 65535.0f;
    for (int32_t i = 0; i < 4; ++i) {
        const float tb = t[i] * static_cast<float>(b[i]);
        out[i] = ColorByteD(ppc::fmadds(1.0f - t[i], static_cast<float>(a[i]), tb));
    }
}
}  // namespace

// 0x000e7f20 CSparkNodeFx_Construct
CSparkNodeFx::CSparkNodeFx() {
    m_pSparks = nullptr;
    m_pFreeSparks = nullptr;
    m_pLiveSparks = nullptr;
    m_pSparkParam = nullptr;
    m_pGeometry = nullptr;
    m_pMatrix = nullptr;
}

// 0x000e8070 CSparkNodeFx_Load
int32_t CSparkNodeFx::Load(IKFile* file, int32_t type) {
    INodeFx::Load(file, type);  // 0xeccd8
    if (type != K_LEVEL_PLATEFORMS) return 1;
    ReadS32LE(file, &m_i32NbSparks);
    ReadRaw(file, &m_unk40, 1);
    ReadRaw(file, &m_unk4c, 1);
    IKFile_ReadRef(file, &m_pSparkParam);
    return 1;
}

// 0x000e9410 CSparkNodeFx_PostLoad
int32_t CSparkNodeFx::PostLoad(int32_t type) {
    INodeFx::PostLoad(type);  // 0xeca78 CNodeFx_PostLoadBase_maybe
    if (type == 0) {
        m_pMatrix = RwMatrixCreate_Thunk();
        int32_t listed = 0;
        for (SSpark* spark = m_pFreeSparks; spark != nullptr; spark = spark->m_pNext) ++listed;
        const uint32_t count = static_cast<uint32_t>(m_i32NbSparks - listed);
        if ((count & 0xffff) != 0) {
            const int16_t n = static_cast<int16_t>(count);
            if (n > 0) {
                SSpark* sparks = new SSpark[n]();  // OperatorNewArray(n * 0x68 + 4), every link cleared
                m_pSparks = sparks;
                for (int16_t i = static_cast<int16_t>(n - 1); i != -1; --i) {
                    sparks[i].m_pNext = m_pFreeSparks;
                    m_pFreeSparks = &sparks[i];
                }
            }
        }
        CParticleGeometry* geometry = static_cast<CParticleGeometry*>(m_lGeometryList);
        m_pLiveSparks = nullptr;
        m_i32NbLiveSparks = 0;
        m_pGeometry = geometry;
        RpPTankData* ptank = PTank(geometry);
        const float one = 1.0f;  // TOC -0x4e44, stored as its bits
        ptank->texCoordsE0[0] = 0;
        ptank->texCoordsE0[1] = 0;
        std::memcpy(&ptank->texCoordsE0[2], &one, 4);
        std::memcpy(&ptank->texCoordsE0[3], &one, 4);
        ptank->flags40 |= 0x80000;
        if (m_unk40 != 0) InitSparks();
    }
    for (CGeometry* geometry = static_cast<CGeometry*>(m_lGeometryList); geometry != nullptr; geometry = geometry->m_pNext) {
        geometry->Vf80((geometry->m_BitProperties & 0x80000) != 0 ? 0 : 2);
    }
    return 1;
}

// 0x000e7b20 CSparkNodeFx_SetParams_maybe: the parameters copied into this node's own (+0x50), unless they are them.
void CSparkNodeFx::SetParams(CKSparkParam* params) {
    if (m_pSparkParam != params) m_pSparkParam->CopyFrom(params);  // 0x000e5058
}

// 0x000e7c90 CSparkNodeFx_ReleaseAllSparks_maybe (the same code is inlined in MessageProc and Enqueue): off, every live
// spark back to the pool, no texture, no particles drawn.
void CSparkNodeFx::ReleaseAllSparks() {
    m_unk40 = 0;
    SSpark* spark = m_pLiveSparks;
    while (spark != nullptr) {
        SSpark* next = spark->m_pNext;
        UnlinkLive(&m_pLiveSparks, spark);
        spark->m_pNext = m_pFreeSparks;
        m_pFreeSparks = spark;
        --m_i32NbLiveSparks;
        if (next == nullptr) break;
        spark = next;
    }
    static_cast<CMaterial*>(m_pGeometry->m_pMaterial)->SetTexture(nullptr);  // 0xbc238 SetMaterialTexture_maybe
    RpPTankData* ptank = PTank(m_pGeometry);
    ptank->flags40 |= 0x800000;
    ptank->numPrt = 0;
}

// 0x000e84a0 CSparkNodeFx_InitSpark_maybe
void CSparkNodeFx::InitSpark(SSpark* spark) {
    const CKSparkParam* p = m_pSparkParam;
    RwFrame* frame = m_pRwFrame;
    spark->m_bLocal = static_cast<uint8_t>((p->m_aUnk98[2] >> 3) & 1);
    const float speed = ppc::fmadds(RandSigned(), P(p, 0x6c), P(p, 0x68));
    const float r1 = RandU16();
    const float r2 = RandU16();
    const float r3 = RandU16();
    CVector3 dir;
    dir.x = ppc::fmadds(P(p, 0x1c), ppc::fmadds(r1, kRandScale, 1.0f), P(p, 0x10));
    dir.y = ppc::fmadds(P(p, 0x20), ppc::fmadds(r2, kRandScale, 1.0f), P(p, 0x14));
    dir.z = ppc::fmadds(P(p, 0x24), ppc::fmadds(r3, kRandScale, 1.0f), P(p, 0x18));
    float* pos = spark->m_position;
    float* vel = spark->m_velocity;
    // Three draws place the spark in the emitter box: each axis gets (r * 0.5) * the box size, fused into the position.
    // (The draw is made by the caller's argument, so that the rand log names InitSpark.)
    auto offset = [&](const CVector3& axis, float f) {
        const float z = ppc::fmadds(f, axis.z, pos[2]);
        const float x = ppc::fmadds(f, axis.x, pos[0]);
        const float y = ppc::fmadds(f, axis.y, pos[1]);
        pos[2] = z;
        pos[0] = x;
        pos[1] = y;
    };
    if (spark->m_bLocal != 0) {
        pos[0] = kVectorZero.x;
        pos[1] = kVectorZero.y;
        pos[2] = kVectorZero.z;
        offset(kAxisX, (RandSigned() * 0.5f) * P(p, 0x04));
        offset(kAxisY, (RandSigned() * 0.5f) * P(p, 0x08));
        offset(kAxisZ, (RandSigned() * 0.5f) * P(p, 0x0c));
        vel[0] = dir.x;
        vel[1] = dir.y;
        vel[2] = dir.z;
    } else {
        // The stored LTM (+0x50) as it is: a spark started in the update phase (an explosion's sub-effect) must not
        // sync its hierarchy (fight capture 3, +1767: the heroes' LTMs current before the camera service).
        const CMatrix34* ltm = reinterpret_cast<const CMatrix34*>(FrameLtm(frame));
        pos[0] = ltm->m_pos.x;
        pos[1] = ltm->m_pos.y;
        pos[2] = ltm->m_pos.z;
        offset(ltm->m_right, (RandSigned() * 0.5f) * P(p, 0x04));
        offset(ltm->m_up, (RandSigned() * 0.5f) * P(p, 0x08));
        offset(ltm->m_at, (RandSigned() * 0.5f) * P(p, 0x0c));
        Mat4_TransformVectors(ltm, reinterpret_cast<CVector3*>(vel), &dir, 1);
    }
    const float length = std::sqrt(ppc::fmadds(vel[2], vel[2], ppc::fmadds(vel[0], vel[0], vel[1] * vel[1])));  // Math_Sqrtf
    if (length != 0.0f) {
        const float inv = 1.0f / length;
        const float z = inv * vel[2];
        const float x = inv * vel[0];
        const float y = inv * vel[1];
        vel[2] = z;
        vel[0] = x;
        vel[1] = y;
    }
    vel[2] = speed * vel[2];
    vel[0] = speed * vel[0];
    vel[1] = speed * vel[1];
    {
        const float a1 = RandU16();
        const float a2 = RandU16();
        const float a3 = RandU16();
        spark->m_accel[0] = ppc::fmadds(P(p, 0x34), ppc::fmadds(a1, kRandScale, 1.0f), P(p, 0x28));
        spark->m_accel[1] = ppc::fmadds(P(p, 0x38), ppc::fmadds(a2, kRandScale, 1.0f), P(p, 0x2c));
        spark->m_accel[2] = ppc::fmadds(P(p, 0x3c), ppc::fmadds(a3, kRandScale, 1.0f), P(p, 0x30));
    }
    {
        const float s1 = RandU16();
        const float s2 = RandU16();
        spark->m_size[0] = ppc::fmadds(P(p, 0x48), ppc::fmadds(s1, kRandScale, 1.0f), P(p, 0x40));
        spark->m_size[1] = ppc::fmadds(P(p, 0x4c), ppc::fmadds(s2, kRandScale, 1.0f), P(p, 0x44));
    }
    const float e1 = RandU16();
    const float e2 = RandU16();
    spark->m_age = 0.0f;
    const float end0 = ppc::fmadds(P(p, 0x58), ppc::fmadds(e1, kRandScale, 1.0f), P(p, 0x50));
    const float end1 = ppc::fmadds(P(p, 0x5c), ppc::fmadds(e2, kRandScale, 1.0f), P(p, 0x54));
    spark->m_lifetime = ppc::fmadds(RandSigned(), P(p, 0x64), P(p, 0x60));
    const float d0 = end0 - spark->m_size[0];
    const float d1 = end1 - spark->m_size[1];
    const float invLife = 1.0f / spark->m_lifetime;
    spark->m_sizeRate[1] = invLife * d1;
    spark->m_sizeRate[0] = invLife * d0;
    spark->m_unk44 = ppc::fmadds(RandSigned(), P(p, 0x74), P(p, 0x70));
    if (spark->m_unk44 < 0.0f) spark->m_unk44 = 0.0f;
    if ((m_pSparkParam->m_aUnk98[2] & 1) == 0) {
        std::memcpy(spark->m_color, m_pSparkParam->m_aColor78[0], 4);
        for (int32_t i = 0; i < 4; ++i) spark->m_colorF[i] = static_cast<float>(spark->m_color[i]);
        std::memcpy(spark->m_targetColor, m_pSparkParam->m_aColor78[2], 4);
    } else {
        uint8_t start[4];
        uint8_t target[4];
        RandomColor(m_pSparkParam->m_aColor78[0], m_pSparkParam->m_aColor78[1], start);   // +0x78 / +0x7c
        RandomColor(m_pSparkParam->m_aColor78[2], m_pSparkParam->m_aColor78[3], target);  // +0x80 / +0x84
        std::memcpy(spark->m_color, start, 4);
        for (int32_t i = 0; i < 4; ++i) spark->m_colorF[i] = static_cast<float>(spark->m_color[i]);
        std::memcpy(spark->m_targetColor, target, 4);
    }
    const float c1 = static_cast<float>(static_cast<int32_t>(spark->m_targetColor[1]) - spark->m_color[1]);
    const float c0 = static_cast<float>(static_cast<int32_t>(spark->m_targetColor[0]) - spark->m_color[0]);
    const float c2 = static_cast<float>(static_cast<int32_t>(spark->m_targetColor[2]) - spark->m_color[2]);
    const float c3 = static_cast<float>(static_cast<int32_t>(spark->m_targetColor[3]) - spark->m_color[3]);
    float sum = ppc::fmadds(c0, c0, c1 * c1);
    sum = ppc::fmadds(c2, c2, sum);
    sum = ppc::fmadds(c3, c3, sum);
    const float distance = std::sqrt(sum);  // Math_Sqrtf
    spark->m_colorSpeed = (distance / spark->m_lifetime) / 255.0f;  // TOC -0x4e28
}

// 0x000e9250 CSparkNodeFx_InitSparks_maybe
void CSparkNodeFx::InitSparks() {
    CKSparkParam* p = m_pSparkParam;
    m_unk40 = 1;
    m_unk41 = 0;
    static_cast<CMaterial*>(m_pGeometry->m_pMaterial)->SetTexture(static_cast<RwTexture*>(p->m_pTexture94));
    m_pGeometry->SetBlendMode(m_pSparkParam->m_aUnk98[0]);  // 0x88028 CGeometry_SetBlendMode
    uint32_t count = m_pSparkParam->m_aUnk98[1];
    if (static_cast<uint32_t>(m_i32NbSparks) < count) count = static_cast<uint32_t>(m_i32NbSparks);
    for (uint32_t left = count - 1; (left & 0xff) != 0xff; --left) {
        SSpark* spark = TakeFree(&m_pFreeSparks);
        spark->m_pNext = m_pLiveSparks;
        m_pLiveSparks = spark;
        ++m_i32NbLiveSparks;
        InitSpark(spark);
    }
    const float base = m_pSparkParam->m_unk88;
    m_fBurstTimer = ppc::fmadds(RandSigned(), m_pSparkParam->m_unk8c, base);
    m_fEmitTime = m_pSparkParam->m_unk90;
}

// 0x000e96b0 CSparkNodeFx_UpdateSpark_maybe
void CSparkNodeFx::UpdateSpark(float dt, SSpark* spark, CMatrix34* matrix, uint8_t* color) {
    float* pos = spark->m_position;
    float* vel = spark->m_velocity;
    CVector3 a;
    if (spark->m_bLocal == 0) {
        a.x = spark->m_accel[0];
        a.y = spark->m_accel[1];
        a.z = spark->m_accel[2];
    } else {
        Mat4_TransformVectors(m_pMatrix, &a, reinterpret_cast<const CVector3*>(spark->m_accel), 1);
    }
    const float drag = -m_pSparkParam->m_afUnk04[(0x70 - 4) / 4];
    const float half = (dt * dt) * 0.5f;
    a.z = ppc::fmadds(drag, vel[2], a.z);
    a.x = ppc::fmadds(drag, vel[0], a.x);
    a.y = ppc::fmadds(drag, vel[1], a.y);
    pos[0] = ppc::fmadds(half, a.x, pos[0]);
    pos[2] = ppc::fmadds(half, a.z, pos[2]);
    pos[1] = ppc::fmadds(half, a.y, pos[1]);
    pos[0] = ppc::fmadds(dt, vel[0], pos[0]);
    pos[1] = ppc::fmadds(dt, vel[1], pos[1]);
    pos[2] = ppc::fmadds(dt, vel[2], pos[2]);
    vel[0] = ppc::fmadds(dt, a.x, vel[0]);
    vel[1] = ppc::fmadds(dt, a.y, vel[1]);
    vel[2] = ppc::fmadds(dt, a.z, vel[2]);
    spark->m_size[0] = ppc::fmadds(dt, spark->m_sizeRate[0], spark->m_size[0]);
    spark->m_size[1] = ppc::fmadds(dt, spark->m_sizeRate[1], spark->m_size[1]);
    matrix->m_pos.x = pos[0];
    matrix->m_pos.z = pos[2];
    matrix->m_pos.y = pos[1];
    matrix->m_ui32Flags &= 0xfffdffffu;
    // The spark's direction (its velocity, normalised; the camera's right when it does not move) and the up vector
    // across it and the camera's view direction (or the camera's right when they are parallel).
    CVector3 dir = {vel[0], vel[1], vel[2]};
    const float speed = std::sqrt(ppc::fmadds(dir.z, dir.z, ppc::fmadds(dir.x, dir.x, dir.y * dir.y)));  // Math_Sqrtf
    const RwMatrix* camera = CameraLtm();
    if (speed == 0.0f) {
        dir.x = camera->right.x;
        dir.y = camera->right.y;
        dir.z = camera->right.z;
    } else {
        const float inv = 1.0f / speed;
        dir.z = dir.z * inv;
        dir.x = dir.x * inv;
        dir.y = dir.y * inv;
    }
    auto cross = [&dir](const RwV3d& v, CVector3* out) {
        out->x = ppc::fmsubs(dir.y, v.z, dir.z * v.y);
        out->y = ppc::fmsubs(dir.z, v.x, dir.x * v.z);
        out->z = ppc::fmsubs(dir.x, v.y, dir.y * v.x);
        return std::sqrt(ppc::fmadds(out->z, out->z, ppc::fmadds(out->x, out->x, out->y * out->y)));  // Math_Sqrtf
    };
    CVector3 up;
    float length = cross(camera->at, &up);
    if (length == 0.0f) length = cross(camera->right, &up);
    if (length != 0.0f) {
        const float inv = 1.0f / length;
        up.z = up.z * inv;
        up.x = up.x * inv;
        up.y = up.y * inv;
    }
    Mat4_SetBasisFromRightUp(matrix, &dir, &up);
    const float sizeX = spark->m_size[0];
    const float sizeY = spark->m_size[1];
    matrix->m_right.y = sizeX * matrix->m_right.y;
    matrix->m_right.z = sizeX * matrix->m_right.z;
    matrix->m_right.x = sizeX * matrix->m_right.x;
    matrix->m_up.x = sizeY * matrix->m_up.x;
    matrix->m_up.y = sizeY * matrix->m_up.y;
    matrix->m_up.z = sizeY * matrix->m_up.z;
    matrix->m_ui32Flags &= 0xfffdfffeu;
    if (spark->m_bLocal != 0) {
        // 0x0023f760 Mat4_TransformPostConcat: RwMatrixTransform(matrix, the node's LTM, rwCOMBINEPOSTCONCAT).
        RwMatrixTransform(reinterpret_cast<RwMatrix*>(matrix), RwFrameGetLTM(m_pRwFrame), rwCOMBINEPOSTCONCAT);
    }
    if (std::memcmp(spark->m_color, spark->m_targetColor, 4) != 0) {
        const float d1 = static_cast<float>(spark->m_targetColor[1]) - spark->m_colorF[1];
        const float d0 = static_cast<float>(spark->m_targetColor[0]) - spark->m_colorF[0];
        const float d2 = static_cast<float>(spark->m_targetColor[2]) - spark->m_colorF[2];
        const float d3 = static_cast<float>(spark->m_targetColor[3]) - spark->m_colorF[3];
        float sum = ppc::fmadds(d0, d0, d1 * d1);
        sum = ppc::fmadds(d2, d2, sum);
        const float step = (dt * spark->m_colorSpeed) * 255.0f;
        sum = ppc::fmadds(d3, d3, sum);
        if (step * step <= sum) {
            const float k = step * rwInvSqrt(sum);  // 0x114d8 Math_InvSqrtf
            spark->m_colorF[0] = ppc::fmadds(d0, k, spark->m_colorF[0]);
            spark->m_colorF[3] = ppc::fmadds(d3, k, spark->m_colorF[3]);
            spark->m_colorF[1] = ppc::fmadds(d1, k, spark->m_colorF[1]);
            spark->m_colorF[2] = ppc::fmadds(d2, k, spark->m_colorF[2]);
            for (int32_t i = 0; i < 4; ++i) spark->m_color[i] = static_cast<uint8_t>(ppc::fctiwz(spark->m_colorF[i]));
        } else {
            std::memcpy(spark->m_color, spark->m_targetColor, 4);
        }
    }
    std::memcpy(color, spark->m_color, 4);
}

// 0x000e9c70 CSparkNodeFx_UpdateSparks_maybe
void CSparkNodeFx::UpdateSparks(float dt) {
    SSpark* spark = m_pLiveSparks;
    Mat4_Invert(m_pMatrix, reinterpret_cast<const CMatrix34*>(RwFrameGetLTM(m_pRwFrame)));
    RpPTankLockStruct lock;
    uint8_t* matrices = nullptr;
    if (RpPTankAtomicLock(m_pGeometry->m_pRpAtomic, &lock, 8, 0x40000000) != 0) matrices = lock.data;  // rpPTANKDFLAGMATRIX
    uint8_t* colors = nullptr;
    if (RpPTankAtomicLock(m_pGeometry->m_pRpAtomic, &lock, 2, 0x40000000) != 0) colors = lock.data;  // rpPTANKDFLAGCOLOR
    while (spark != nullptr) {
        if (spark->m_age < spark->m_lifetime) {
            UpdateSpark(dt, spark, reinterpret_cast<CMatrix34*>(matrices), colors);
            matrices += 0x40;
            colors += 4;
            const float age = dt + spark->m_age;
            SSpark* next = spark->m_pNext;
            spark->m_age = age;
            spark = next;
        } else {
            SSpark* next = spark->m_pNext;
            UnlinkLive(&m_pLiveSparks, spark);
            spark->m_pNext = m_pFreeSparks;
            m_pFreeSparks = spark;
            --m_i32NbLiveSparks;
            spark = next;
        }
    }
    m_pGeometry->UnlockPTank();  // vt+0x8c
    RpPTankData* ptank = PTank(m_pGeometry);
    ptank->flags40 |= 0x800000;
    ptank->numPrt = static_cast<uint32_t>(m_i32NbLiveSparks);
    const CKSparkParam* p = m_pSparkParam;
    if ((p->m_aUnk98[2] & 2) != 0) return;
    const float timer = m_fBurstTimer - dt;
    m_fBurstTimer = timer;
    if (timer >= 0.0f) return;
    if (m_fEmitTime <= 0.0f && ((p->m_aUnk98[2] >> 2) & 1) == 0) return;
    if (m_unk41 != 0) return;
    uint32_t count = static_cast<uint32_t>(m_i32NbSparks - m_i32NbLiveSparks);
    if ((count & 0xff) > p->m_aUnk98[1]) count = p->m_aUnk98[1];
    for (uint32_t left = count - 1; (left & 0xff) != 0xff; --left) {
        SSpark* fresh = TakeFree(&m_pFreeSparks);
        fresh->m_pNext = m_pLiveSparks;
        m_pLiveSparks = fresh;
        ++m_i32NbLiveSparks;
        InitSpark(fresh);
    }
    const float base = m_pSparkParam->m_unk88;
    m_fBurstTimer = ppc::fmadds(RandSigned(), m_pSparkParam->m_unk8c, base);
}

// 0x000ea040 CSparkNodeFx_MessageProc: 0 when the message was 0x1a64 (whatever it changed), 1 otherwise.
int32_t CSparkNodeFx::MessageProc(uint16_t message, void* data) {
    if (message != 0x1a64) return 1;
    const uint8_t on = *static_cast<const uint8_t*>(data);
    if (m_unk40 == on) return 0;
    if (on == 0) {
        ReleaseAllSparks();  // inlined
        return 0;
    }
    InitSparks();
    return 0;
}

// 0x000ea200 CSparkNodeFx_Enqueue
void CSparkNodeFx::UpdateAndExtract(float /*maxDistanceSquared*/, RenderQueue** stages, IKTime* frameClock, RwCamera* camera,
                                    int32_t /*distanceCull*/) {
    if (m_unk40 != 0 && (m_sgProperties & 1) != 0 && frameClock->m_eCurrentState != 3 &&
        (frameClock->m_eCurrentState == 0 || m_unk4c != 0)) {
        UpdateSparks(frameClock->m_afDeltaTime[0]);
        const float left = m_fEmitTime - frameClock->m_afDeltaTime[0];
        m_fEmitTime = left;
        if (m_i32NbLiveSparks == 0) {
            bool stop = m_unk41 != 0;
            if (!stop) {
                const uint8_t flags = m_pSparkParam->m_aUnk98[2];
                if (((flags >> 2) & 1) == 0 && !(left >= 0.0f)) {
                    stop = true;
                } else {
                    stop = ((flags >> 1) & 1) != 0;
                }
            }
            if (stop) ReleaseAllSparks();  // inlined
        }
    }
    CullAndEnqueueGeometry(stages, frameClock, camera);  // vt+0x84
}

// C2.8 port-all P11.

// 0x000e7f88 CSparkNodeFx_Destroy
void CSparkNodeFx::Destroy() {
    CNode::Destroy();  // 0x000cbe10
    if (m_pMatrix != nullptr) {
        RwMatrixDestroy_Thunk(m_pMatrix);  // 0x0023f968
        m_pMatrix = nullptr;
    }
    for (SSpark* spark = m_pFreeSparks; spark != nullptr;) {
        SSpark* next = spark->m_pNext;
        spark->m_pNext = nullptr;
        spark = next;
    }
    m_pFreeSparks = nullptr;
    for (SSpark* spark = m_pLiveSparks; spark != nullptr;) {
        SSpark* next = spark->m_pNext;
        spark->m_pNext = nullptr;
        spark = next;
    }
    m_pLiveSparks = nullptr;
    delete[] m_pSparks;  // OperatorDeleteArray(p - 4)
    m_pSparks = nullptr;
}
