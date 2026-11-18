// CKLightningBoltNodeFx.cpp - reconstructed original translation unit 0x57a7c8-0x582a48 (GAME_TOC2, main_toc2), 53 functions, 50 live.
// Primary class: CKLightningBoltNodeFx  key 0xa60c  category Logic  size ?  vtable 0xb2e0b0
// Other owners: Vec3 (2)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x57a7c8  CKLightningBoltNodeFx_Delete
//   [ ] 0x57a818  CKLightningBoltNodeFx_InterpolateParam_maybe  [dead]
//   [x] 0x57a890  CKLightningBoltNodeFx_SetStartSmoothParams_maybe
//   [x] 0x57a8d0  CKLightningBoltNodeFx_SetEndSmoothParams_maybe
//   [ ] 0x57a910  CKLightningBoltNodeFx_StopAndReleaseChildNodes_maybe  [dead]
//   [x] 0x57a9d0  CKLightningBoltNodeFx_SetTargetPoint_maybe
//   [x] 0x57aa10  CKLightningBoltNodeFx_SetField1E0_maybe
//   [x] 0x57aa38  CKLightningBoltNodeFx_SetField1E8_maybe
//   [x] 0x57aa60  CKLightningBoltNodeFx_SetField1E4_maybe
//   [x] 0x57aa88  CKLightningBoltNodeFx_SetField1E6_maybe
//   [x] 0x57aab0  CKLightningBoltNodeFx_SetField1D8_maybe
//   [x] 0x57aad8  CKLightningBoltNodeFx_SetStartIntensity_maybe
//   [x] 0x57ab48  CKLightningBoltNodeFx_Destroy
//   [ ] 0x57aba0  RegisterCKLightningBoltNodeFxClass
//   [ ] 0x57ac18  _GLOBAL__I_57ac18
//   [x] 0x57ac28  CKLightningBoltNodeFx_ResetImpactSlots_maybe
//   [x] 0x57ae68  CKLightningBoltNodeFx_UpdateEndpoints_maybe
//   [x] 0x57b0c0  CKLightningBoltNodeFx_UpdateFades_maybe
//   [x] 0x57b230  CKLightningBoltNodeFx_UpdateVertexColors_maybe
//   [x] 0x57b3d0  CKLightningBoltNodeFx_AllocSegments_maybe
//   [x] 0x57b5f0  CKLightningBoltNodeFx_RecursiveRegistration
//   [x] 0x57b670  CKLightningBoltNodeFx_DeleteArray
//   [x] 0x57b710  CKLightningBoltNodeFx_Create
//   [x] 0x57b780  CKLightningBoltNodeFx_StopIfLinkedTo
//   [x] 0x57b968  CKLightningBoltNodeFx_SetField20C_maybe
//   [x] 0x57b990  CKLightningBoltNodeFx_SetEndIntensity_maybe
//   [x] 0x57ba00  CKLightningBoltNodeFx_CreateArray
//   [x] 0x57bae0  CKLightningBoltNodeFx_Load
//   [ ] 0x57bc10  CKLightningBoltNodeFx_Save
//   [x] 0x57bd30  CKLightningBoltNodeFx_RemoveBranchRecursive_maybe
//   [x] 0x57bfd8  CKLightningBoltNodeFx_ResetBolt_maybe
//   [x] 0x57c320  CKLightningBoltNodeFx_Start
//   [x] 0x57c3c8  CKLightningBoltNodeFx_PostLoad
//   [x] 0x57c430  CKLightningBoltNodeFx_SetNodePositionIfOwner_maybe
//   [x] 0x57c4c8  CKLightningBoltNodeFx_SyncNodeToTarget_maybe
//   [x] 0x57c650  CKLightningBoltNodeFx_PlaceNodeAtSource_maybe
//   [x] 0x57c818  CKLightningBoltNodeFx_ComputeBranchPoint_maybe
//   [x] 0x57cc20  CKLightningBoltNodeFx_GenerateBranch_maybe
//   [x] 0x57d678  CKLightningBoltNodeFx_UpdateBranchesRecursive_maybe
//   [ ] 0x57d920  Vec3_RotateTowardByAngle_2_maybe  [dead]
//   [x] 0x57db68  Vec3_AngleBetweenNormalizing_maybe  (no caller found in the EBOOT: a file-local function here)
//   [x] 0x57dce8  CKLightningBoltNodeFx_IsLinkedTo_maybe
//   [x] 0x57e348  CKLightningBoltNodeFx_CollectTargetsInRange_maybe
//   [x] 0x57ec40  CKLightningBoltNodeFx_BuildBranchVertices_maybe
//   [x] 0x580030  CKLightningBoltNodeFx_RebuildGeometry_maybe
//   [x] 0x5806c8  CKLightningBoltNodeFx_UpdateImpactExplosions_maybe
//   [x] 0x580c58  CKLightningBoltNodeFx_SetEndParticlesActive_maybe
//   [x] 0x581178  CKLightningBoltNodeFx_Stop
//   [x] 0x581380  CKLightningBoltNodeFx_SetActiveForOwner_maybe
//   [x] 0x581c38  CKLightningBoltNodeFx_UpdateImpactSlots_maybe
//   [x] 0x5823f0  CKLightningBoltNodeFx_UpdateImpacts_maybe
//   [x] 0x582470  CKLightningBoltNodeFx_Update
//   [x] 0x5829a0  CKLightningBoltNodeFx_RestartForOwner_maybe
//
//   [ ] 0x9cb068  CKLightningBoltNodeFx_IsKindOfClass  [inline]
//   [x] 0x9cb0a8  CKLightningBoltNodeFx_GetClassType  [inline]
//   [x] 0x9cb0b0  CKLightningBoltNodeFx_GetClassID  [inline]
//   [x] 0x9cb0b8  CKLightningBoltNodeFx_GetFxData  [inline]
//   [x] 0x9cb0c0  CKLightningBoltNodeFx_SetFxData  [inline]
//   [ ] 0x9cb0c8  CKLightningBoltNodeFx_Destruct  [inline]
//   [ ] 0x9cb148  CKLightningBoltNodeFx_DeletingDestruct  [inline]
//   [ ] 0x9cb1d0  KBaseA58C_vf8  [inline]
//   [ ] 0x9cb200  KBaseA58C_vf14  [inline]
//   [ ] 0x9cb208  KBaseA58C_vf18  [inline]
#include "k2000/logic/render/CKLightningBoltNodeFx.h"

#include <cmath>

#include "Renderware/rwcore/RwCamera.h"
#include "crt/ppc_ops.h"
#include "crt/xatan.h"
#include "crt/xpowfast.h"
#include "crt/xsinf.h"
#include "crt/xtanf.h"
#include "k2000/logic/render/CMaterial.h"
#include "k2000/io/IKFile.h"
#include "k2000/logic/CKSavingManager.h"
#include "k2000/fx/IKFx.h"
#include "k2000/geometry/CGeometry.h"
#include "Renderware/rpworld/RpGeometry.h"
#include "Renderware/rwcore/RwRaster.h"
#include "Renderware/rwcore/RwTexture.h"
#include <cstring>
#include "k2000/logic/CKParticlesEffectFxData.h"
#include "k2000/logic/CSGHotSpot.h"
#include "k2000/logic/fx/CKExplosionNodeFx.h"
#include "k2000/logic/fx/CKParticlesEffectNodeFx.h"
#include "k2000/logic/render/CKLightningBoltFxData.h"
#include "k2000/scenegraph/CKDynamicBoundingSphere.h"
#include "k2000/scenegraph/CSGBranch.h"
#include "k2000/services/CKSrvCollision.h"
#include "k2000/services/CKSrvFx.h"
#include "k2000/core/Stub.h"
#include "k2000/misc/Engine.h"
#include "k2000/memory/Mem.h"
#include "k2000/misc/ClassRegistry.h"
#include "k2000/misc/FloatApproach.h"
#include "k2000/misc/Mat4.h"
#include "k2000/scenegraph/CNode.h"
#include "k2000/scenegraph/CSGMovable.h"
#include "k2000/system/IKTime.h"
#include "Spyro2008/groups/CKGrpS08Hero.h"
#include "k2000/hooks/IKHook.h"
#include "k2000/logic/CDefaultGameManager.h"
#include "k2000/misc/CKGrpMeca.h"
#include "k2000/misc/IKGrpEnemy.h"

// 0x0057b710 CKLightningBoltNodeFx_Create, the inlined constructor, in its store order.
CKLightningBoltNodeFx::CKLightningBoltNodeFx() {
    m_segments.m_pBlock = nullptr;
    m_segments.m_ui32NbElt = 1;
    m_segments.m_ui32NbUsedElt = 0;
}

// 0x0057bae0 CKLightningBoltNodeFx_Load
int32_t CKLightningBoltNodeFx::Load(IKFile* file, int32_t type) {
    IKNodeFx::Load(file, type);  // through TocBridge_IKNodeFx_Load
    if (type == K_LEVEL_PLATEFORMS) {
        ReadU8(file, &m_unk18);
        ReadU32LE(file, &m_ui32MaxLevels);
        ReadU32LE(file, &m_ui32NbVertices);
    }
    return 1;
}

namespace {
const float kZero = 0.0f;          // TOC2 -0x7440
const float kOne = 1.0f;           // TOC2 -0x7448
const float kMinIntensity = 0.01f;  // TOC2 -0x7444
const float kHalf = 0.5f;          // TOC2 -0x7390
const float k65535 = 65535.0f;     // TOC2 -0x7410
const float kMinusTwo = -2.0f;     // TOC2 -0x740c
const float kMinusOne = -1.0f;     // TOC2 -0x7404
const float kFadeRate = 10.0f;     // TOC2 -0x7400
const CVector3 kNullVector = {0.0f, 0.0f, 0.0f};  // g_nullVector 0x00c50d64 (TOC2 -0x7408)
const CVector3 kAxisY = {0.0f, 1.0f, 0.0f};       // 0x00c50d40 (TOC2 -0x7394)
const CVector3 kAxisZ = {0.0f, 0.0f, 1.0f};       // 0x00c50d4c (TOC2 -0x7360)

CKLightningBoltFxData* DataOf(const CKLightningBoltNodeFx* node) {
    return static_cast<CKLightningBoltFxData*>(node->m_pFxData);
}
// (rand & 0xffff) / 65535 (fcfid, frsp, fdivs).
float RandUnit16() { return static_cast<float>(static_cast<double>(static_cast<uint32_t>(Rand_Int()) & 0xffffu)) / k65535; }
// A centre and a range: fmadds(rand / 65535 x -2, range, centre + range), in [centre - range, centre + range].
float RandAround(float centre, float range) {
    const float base = centre + range;
    return ppc::fmadds(RandUnit16() * kMinusTwo, range, base);
}
void SetPoint(float* out, const CVector3& v) {
    out[0] = v.x;
    out[1] = v.y;
    out[2] = v.z;
}
// The fade between the two intensities at `t` of the bolt (the start one, or a blend toward the end one), at least 0.01.
float IntensityAt(const CKLightningBoltNodeFx* node, float t) {
    float intensity = node->m_afStartFade[3];
    if (intensity != node->m_afEndFade[3]) intensity = ppc::fmadds(t, node->m_afEndFade[3] - intensity, intensity);
    if (intensity < kMinIntensity) intensity = kMinIntensity;
    return intensity;
}
// [0, 1].
float Clamp01(float t) {
    if (t < kZero) return kZero;
    if (t > kOne) return kOne;
    return t;
}
}  // namespace

// 0x0057c3c8 CKLightningBoltNodeFx_PostLoad
int32_t CKLightningBoltNodeFx::PostLoad(int32_t type) {
    IKNodeFx::PostLoad(type);  // TocBridge_IKNodeFx_PostLoad
    AllocSegments();
    m_baFxData = static_cast<uint8_t>(m_baFxData & 0xf7);
    ResetBolt();
    return 1;
}

// 0x0057ab48 CKLightningBoltNodeFx_Destroy
void CKLightningBoltNodeFx::Destroy() {
    if (m_segments.m_pBlock != nullptr) {
        Mem_FreeAligned16(m_segments.m_pBlock);
        m_segments.m_pBlock = nullptr;
    }
    m_segments.m_ui32NbUsedElt = 0;
    m_segments.m_pBlock = nullptr;
}

// 0x0057c320 CKLightningBoltNodeFx_Start
void CKLightningBoltNodeFx::Vf64() {
    m_baFxData = static_cast<uint8_t>((m_baFxData & 0xfc) | 2);
    ResetBolt();
    if (m_pFxData == nullptr) {
        Stop();  // vt+0x6c
        return;
    }
    m_baFxData = static_cast<uint8_t>((m_baFxData & 0xf0) | (m_baFxData & 3));
}

// 0x0057aad8 CKLightningBoltNodeFx_SetStartIntensity_maybe
void CKLightningBoltNodeFx::SetStartIntensity(uint8_t intensity, const IKSerializable* owner) {
    if ((m_baFxData & 2u) == 0 || m_pOwner != owner) return;
    float value = static_cast<float>(static_cast<double>(intensity)) / 255.0f;  // TOC2 -0x743c
    if (value <= kZero) {
        value = kZero;
    } else if (kOne <= value) {
        value = kOne;
    }
    m_fStartIntensity = value;
}

// 0x0057b968 CKLightningBoltNodeFx_SetField20C_maybe
void CKLightningBoltNodeFx::SetField20C(float value, const IKSerializable* owner) {
    if ((m_baFxData & 2u) == 0 || m_pOwner != owner) return;
    m_unk20c = value;
}

// 0x0057b990 CKLightningBoltNodeFx_SetEndIntensity_maybe
void CKLightningBoltNodeFx::SetEndIntensity(uint8_t intensity, const IKSerializable* owner) {
    if ((m_baFxData & 2u) == 0 || m_pOwner != owner) return;
    float value = static_cast<float>(static_cast<double>(intensity)) / 255.0f;
    if (value <= kZero) {
        value = kZero;
    } else if (kOne <= value) {
        value = kOne;
    }
    m_fEndIntensity = value;
}

// 0x0057b3d0 CKLightningBoltNodeFx_AllocSegments_maybe
void CKLightningBoltNodeFx::AllocSegments() {
    const uint32_t budget = static_cast<uint32_t>(static_cast<float>(static_cast<double>(m_ui32NbVertices)));
    m_ui32MaxSegments = budget;
    if (m_segments.m_pBlock == nullptr) {
        if (budget == 0) {
            m_segments.m_ui32NbElt = 1;
            m_segments.m_pBlock = static_cast<SSegment*>(Mem_AllocAligned16(sizeof(SSegment)));
        } else {
            m_segments.m_ui32NbElt = budget;
            m_segments.m_pBlock = static_cast<SSegment*>(Mem_AllocAligned16(budget * static_cast<uint32_t>(sizeof(SSegment))));
        }
    }
    if (m_ui32MaxSegments < m_segments.m_ui32NbUsedElt) {
        m_segments.m_ui32NbUsedElt = m_ui32MaxSegments;
        return;
    }
    while (m_segments.m_ui32NbUsedElt < m_ui32MaxSegments) {
        const uint32_t used = m_segments.m_ui32NbUsedElt;
        if (m_segments.m_ui32NbElt == used) {
            uint32_t capacity = used + 1;
            uint32_t bytes = capacity * static_cast<uint32_t>(sizeof(SSegment));
            if (capacity == 0) {
                capacity = 1;
                bytes = sizeof(SSegment);
            }
            m_segments.m_pBlock = static_cast<SSegment*>(Mem_ReallocAligned16(m_segments.m_pBlock, bytes));
            m_segments.m_ui32NbElt = capacity;
        }
        SSegment& s = m_segments.m_pBlock[m_segments.m_ui32NbUsedElt];
        s.m_ui32Level = 0;
        SetPoint(s.m_afStart, kNullVector);
        SetPoint(s.m_afEnd, kNullVector);
        s.m_fSpeed = 0.0f;
        s.m_fAccel = 0.0f;
        s.m_fAmplitude = 0.0f;
        s.m_ui32Parent = 0;
        s.m_ui32FirstChild = 0;
        s.m_ui32NbChildren = 0;
        s.m_bLeaf = 0;
        s.m_bPointsCached = 0;
        s.m_fWidth = 0.2f;  // TOC2 -0x73fc
        s.m_vPoint = kNullVector;
        s.m_vDirection = kNullVector;
        s.m_vUp = kNullVector;
        s.m_fExpiry = 0.0f;
        m_segments.m_ui32NbUsedElt = m_segments.m_ui32NbUsedElt + 1;
    }
}

// 0x0057bfd8 CKLightningBoltNodeFx_ResetBolt_maybe
void CKLightningBoltNodeFx::ResetBolt() {
    RwFrame* frame = static_cast<CSGMovable*>(m_pNode)->m_pRwFrame;
    frame->modelling.pos = {kNullVector.x, kNullVector.y, kNullVector.z};
    frame->modelling.flags &= 0xfffdffffu;
    RwFrame_MarkDirty(frame);  // 0x00010698
    m_vSourceOffset = kNullVector;
    m_vStart = kNullVector;
    m_vEnd = kNullVector;
    m_vDirection = kNullVector;
    m_vRight = kNullVector;
    m_vUp = kNullVector;
    m_fTime = 0.0f;
    m_fLifetime = 0.0f;
    m_ui32NbStripVertices = 0;
    m_ui32NbSegments = 0;
    m_unk8c = 1.0f;
    m_ui32MaxSegments = static_cast<uint32_t>(static_cast<float>(static_cast<double>(m_ui32NbVertices)));
    m_ui32NbImpacts = 0;
    m_pDamage = nullptr;
    m_pSphere = nullptr;
    m_pDamageOwner = nullptr;
    m_unk1e8 = 0;
    m_ui8DamageCategory = 0;
    m_ui16DamageFlags = 0;
    for (SLevel& level : m_aLevels) {
        level.m_fBranchChance = 0.0f;
        level.m_unk04 = 0.3f;  // 0x3e99999a
        level.m_unk08 = 1.0f;
        level.m_unk0c = 0.2f;  // 0x3e4ccccd
        level.m_fDensity = 1.0f;
        level.m_fWidth = 0.2f;
        level.m_fWidthRange = 0.0f;
        level.m_fLifetime = 5.0f;  // 0x40a00000
        level.m_fLifetimeRange = 1.0f;
        level.m_fSpread = 0.25f;  // 0x3e800000
        level.m_fJitter = 0.0f;
        level.m_fSpeed = 0.0f;
        level.m_fSpeedRange = 0.0f;
        level.m_fAccel = 0.0f;
        level.m_fAccelRange = 0.0f;
    }
    m_fStartIntensity = 1.0f;
    m_fEndIntensity = 1.0f;
    m_unk20c = 1.0f;
    m_unk1f8 = 0;
    m_pStartParticles = nullptr;
    m_pEndParticles = nullptr;
    m_unk1f4 = 0;
    m_fSourceExplosionTimer = 0.0f;
    m_fEndExplosionTimer = 0.0f;
    const float startFade[7] = {kFadeRate, kFadeRate, kFadeRate, 1.0f, 0.0f, 1.0f, 0.0f};
    for (int i = 0; i < 7; ++i) m_afStartFade[i] = startFade[i];
    for (int i = 0; i < 7; ++i) m_afEndFade[i] = startFade[i];
    m_fEndFadeTimer = -1.0f;
    m_fStartFadeTimer = -1.0f;
    m_fRollAngle = RandUnit16() * 360.0f;  // TOC2 -0x73dc
}

// 0x0057b0c0 CKLightningBoltNodeFx_UpdateFades_maybe
void CKLightningBoltNodeFx::UpdateFades(IKTime* frameClock) {
    const float dt = frameClock->m_afDeltaTime[0];
    const float startBefore = m_afStartFade[3];
    if (startBefore == Math_ApproachWithAccelDecel(dt, m_afStartFade) && m_fStartFadeTimer != kMinusOne) {  // 0x00243a10
        m_fStartFadeTimer = m_fStartFadeTimer - dt;
        if (m_fStartFadeTimer < kZero && (m_baFxData & 2u) != 0) {
            m_afStartFade[4] = 0.0f;
            m_afStartFade[5] = kOne;
            m_afStartFade[1] = kFadeRate;
            m_afStartFade[2] = kFadeRate;
            m_afStartFade[0] = kFadeRate;
            m_fStartFadeTimer = kMinusOne;
        }
    }
    const float endBefore = m_afEndFade[3];
    if (endBefore == Math_ApproachWithAccelDecel(dt, m_afEndFade) && m_fEndFadeTimer != kMinusOne) {
        m_fEndFadeTimer = m_fEndFadeTimer - dt;
        if (m_fEndFadeTimer < kZero && (m_baFxData & 2u) != 0) {
            m_afEndFade[5] = kOne;
            m_afEndFade[4] = 0.0f;
            m_afEndFade[1] = kFadeRate;
            m_afEndFade[2] = kFadeRate;
            m_afEndFade[0] = kFadeRate;
            m_fEndFadeTimer = kMinusOne;
        }
    }
}

// 0x0057c818 CKLightningBoltNodeFx_ComputeBranchPoint_maybe
void CKLightningBoltNodeFx::ComputeBranchPoint(uint32_t index, CVector3* point, CVector3* direction, CVector3* up) {
    SSegment& s = m_segments.m_pBlock[index];
    if (s.m_bPointsCached == 0) {
        CVector3 at;
        if (index == s.m_ui32Parent) {
            s.m_vPoint = {s.m_afStart[0], s.m_afStart[1], s.m_afStart[2]};
            const float dy = s.m_afEnd[1] - s.m_afStart[1];
            const float dx = s.m_afEnd[0] - s.m_afStart[0];
            const float dz = s.m_afEnd[2] - s.m_afStart[2];
            s.m_vDirection = {dx, dy, dz};
            at = {dx, dy, dz};
        } else {
            CVector3 p, d, u;
            ComputeBranchPoint(s.m_ui32Parent, &p, &d, &u);
            const float t0 = s.m_afStart[0];
            CVector3 a = {ppc::fmadds(t0, d.x, p.x), ppc::fmadds(t0, d.y, p.y), ppc::fmadds(t0, d.z, p.z)};
            const float o0 = s.m_afStart[1];
            a = {ppc::fmadds(o0, u.x, a.x), ppc::fmadds(o0, u.y, a.y), ppc::fmadds(o0, u.z, a.z)};
            s.m_vPoint = a;
            const float t1 = s.m_afEnd[0];
            const float o1 = s.m_afEnd[1];
            const float bx = ppc::fmadds(o1, u.x, ppc::fmadds(t1, d.x, p.x));
            const float by = ppc::fmadds(o1, u.y, ppc::fmadds(t1, d.y, p.y));
            const float bz = ppc::fmadds(o1, u.z, ppc::fmadds(t1, d.z, p.z));
            at = {bx - a.x, by - a.y, bz - a.z};
            s.m_vDirection = at;
        }
        const float length = std::sqrt(ppc::fmadds(at.z, at.z, ppc::fmadds(at.x, at.x, at.y * at.y)));  // Math_Sqrtf
        if (length != kZero) {
            const float k = kOne / length;
            at = {at.x * k, at.y * k, at.z * k};
        }
        CMatrix34 basis;
        if (Mat4_SetBasisFromAtRight(&basis, &at, &m_vRight) != 0) {  // 0x0023fe58
            s.m_vUp = basis.m_up;
        } else {
            s.m_vUp = kAxisY;
        }
        s.m_bPointsCached = 1;
    }
    *point = s.m_vPoint;
    *direction = s.m_vDirection;
    *up = s.m_vUp;
}

// 0x0057cc20 CKLightningBoltNodeFx_GenerateBranch_maybe
void CKLightningBoltNodeFx::GenerateBranch(float t0, float t1, uint32_t index) {
    SSegment* seg = &m_segments.m_pBlock[index];
    const uint32_t level = seg->m_ui32Level;
    const float intensity = IntensityAt(this, Clamp01((t1 + t0) * kHalf));
    const float previousExpiry = seg->m_fExpiry;
    SLevel& lv = m_aLevels[level];
    // The segment's lifetime: a random rate; below 0.001 per second it lives on (999.99994 s).
    float rate = std::fabs(RandAround(lv.m_fLifetime, lv.m_fLifetimeRange));
    float life;
    if (intensity * rate >= 0.001f) {  // TOC2 -0x738c
        rate = std::fabs(RandAround(lv.m_fLifetime, lv.m_fLifetimeRange));
        life = kOne / (intensity * rate);
    } else {
        life = 999.99994f;  // TOC2 -0x7388 (0x4479ffff)
    }
    seg->m_fExpiry = life + previousExpiry;
    if (index == 0) {
        // The root's width: a draw below 0.01 keeps 0.01, else a second draw is the width.
        float width = kMinIntensity;
        if (RandAround(lv.m_fWidth, lv.m_fWidthRange) >= kMinIntensity) width = RandAround(lv.m_fWidth, lv.m_fWidthRange);
        seg->m_fWidth = width;
    }
    if (!(level < m_ui32MaxLevels) || !(RandUnit16() * 100.0f < lv.m_fBranchChance)) {  // TOC2 -0x7384
        seg->m_bLeaf = 1;
        return;
    }
    CVector3 point, direction, up;
    ComputeBranchPoint(index, &point, &direction, &up);
    const float length = std::sqrt(ppc::fmadds(direction.z, direction.z, ppc::fmadds(direction.x, direction.x, direction.y * direction.y)));
    const float length2 = std::sqrt(ppc::fmadds(direction.z, direction.z, ppc::fmadds(direction.x, direction.x, direction.y * direction.y)));
    if (length2 != kZero) {
        const float k = kOne / length2;
        direction = {direction.x * k, direction.y * k, direction.z * k};
    }
    const float rootIntensity = std::sqrt(intensity);
    const float scaled = rootIntensity * DataOf(this)->GetBranchLevelScale(length, level);  // f17
    const int64_t children = ppc::fctidz((rootIntensity * lv.m_fDensity) / (scaled / length));
    const uint32_t count = static_cast<uint32_t>(children) + 1;
    if (count + m_ui32NbSegments > m_ui32MaxSegments) {
        seg->m_bLeaf = 1;
        return;
    }
    seg->m_ui32NbChildren = count;
    const float step = length / static_cast<float>(static_cast<double>(static_cast<uint32_t>(children) * 2u));
    seg->m_ui32FirstChild = m_ui32NbSegments;
    const float jitter = step * lv.m_fJitter;
    float sign = kOne;
    if (ppc::fmadds(RandUnit16(), kMinusTwo, kOne) < kZero) sign = kMinusOne;
    const float spread = scaled * lv.m_fSpread;
    CVector3 start = kNullVector;
    const float span = t1 - t0;
    const uint32_t childLevel = level + 1;
    SLevel& cl = m_aLevels[childLevel];
    for (uint32_t i = 0; count != 0; ++i) {
        SSegment* child = &m_segments.m_pBlock[m_ui32NbSegments];
        const bool last = static_cast<int32_t>(children) == static_cast<int32_t>(i);
        child->m_ui32Level = 0;
        SetPoint(child->m_afStart, kNullVector);
        SetPoint(child->m_afEnd, kNullVector);
        child->m_fSpeed = kZero;
        child->m_fAccel = kZero;
        child->m_fAmplitude = kZero;
        child->m_ui32Parent = 0;
        child->m_ui32FirstChild = 0;
        child->m_ui32NbChildren = 0;
        child->m_bLeaf = 0;
        child->m_fExpiry = kZero;
        child->m_bPointsCached = 0;
        child->m_vPoint = kNullVector;
        child->m_vDirection = kNullVector;
        child->m_vUp = kNullVector;
        child->m_fWidth = 0.2f;  // TOC2 -0x73fc
        if (!last) {
            const float r = static_cast<float>(static_cast<double>(static_cast<uint32_t>(Rand_Int()) & 0xffffu));
            const float odd = static_cast<float>(static_cast<double>(i * 2u + 1u));
            child->m_afStart[2] = start.z;
            child->m_afStart[1] = start.y;
            const float along = ppc::fmadds(step, odd, jitter);
            child->m_afEnd[0] = ppc::fmadds(jitter, (r / k65535) * kMinusTwo, along) / length;
            child->m_afStart[0] = start.x;
        } else {
            child->m_afEnd[0] = kOne;
            child->m_afStart[0] = start.x;
            child->m_afStart[2] = start.z;
            child->m_afStart[1] = start.y;
        }
        const float a = ppc::fmadds(span, child->m_afStart[0], t0);
        const float b = ppc::fmadds(span, child->m_afEnd[0], t0);
        const float local = IntensityAt(this, Clamp01((a + b) * kHalf));
        if (!last) {
            const float r = static_cast<float>(static_cast<double>(static_cast<uint32_t>(Rand_Int()) & 0xffffu));
            const float ratio = local / intensity;
            child->m_afEnd[1] = ppc::fmadds(spread, r / -65535.0f, scaled) * sign * ratio;  // TOC2 -0x7380
        } else {
            child->m_afEnd[1] = kZero;
        }
        const CVector3 next = {child->m_afEnd[0], child->m_afEnd[1], child->m_afEnd[2]};
        child->m_ui32Level = childLevel;
        child->m_ui32Parent = index;
        child->m_fExpiry = m_fTime;
        // The width: a draw below 0.1 keeps 0.1, else a second draw.
        float width = 0.1f;  // TOC2 -0x737c
        if (RandAround(cl.m_fWidth, cl.m_fWidthRange) >= 0.1f) width = RandAround(cl.m_fWidth, cl.m_fWidthRange);
        child->m_fWidth = width;
        const float side = start.y < kZero ? kMinusOne : kOne;
        const SLevel& own = m_aLevels[child->m_ui32Level];
        child->m_fSpeed = (side * local) * RandAround(own.m_fSpeed, own.m_fSpeedRange);
        child->m_fAccel = local * RandAround(own.m_fAccel, own.m_fAccelRange);
        child->m_fAmplitude = std::fabs(start.y);
        m_ui32NbSegments = m_ui32NbSegments + 1;
        if (last) break;
        sign = -sign;
        start = next;
    }
    for (uint32_t k = 0; k < seg->m_ui32NbChildren; ++k) {
        const uint32_t c = seg->m_ui32FirstChild + k;
        const SSegment& child = m_segments.m_pBlock[c];
        GenerateBranch(ppc::fmadds(span, child.m_afStart[0], t0), ppc::fmadds(span, child.m_afEnd[0], t0), c);
    }
}

// 0x0057d678 CKLightningBoltNodeFx_UpdateBranchesRecursive_maybe
void CKLightningBoltNodeFx::UpdateBranchesRecursive(float t0, float t1, IKTime* frameClock, uint32_t index) {
    const float dt = frameClock->m_afDeltaTime[0];
    SSegment* seg = &m_segments.m_pBlock[index];
    float a = kZero;
    float b = kOne;
    if (index != 0) {
        const float span = t1 - t0;
        b = ppc::fmadds(span, seg->m_afEnd[0], t0);
        a = ppc::fmadds(seg->m_afStart[0], span, t0);
    }
    if (seg->m_fExpiry <= m_fTime) {
        RemoveBranchRecursive(index);
        GenerateBranch(a, b, index);
        seg = &m_segments.m_pBlock[index];
    } else {
        // The wiggle. BUG(original): with a negative speed the step is 255 x the acceleration and the sign test compares
        // 0xff with -1, so the acceleration flips every frame then.
        int32_t was;
        float scale;
        if (seg->m_fSpeed < kZero) {
            was = 0xff;
            scale = 255.0f;  // TOC2 -0x743c
        } else {
            was = 1;
            scale = kOne;
        }
        const float accel = seg->m_fAccel;
        const float speed = ppc::fmadds(dt, scale * accel, seg->m_fSpeed);
        seg->m_fSpeed = speed;
        const int32_t now = speed >= kZero ? 1 : -1;
        float v = speed;
        if (was != now) {
            seg->m_fAccel = -accel;
            v = seg->m_fSpeed;
        }
        const float offset = ppc::fmadds(dt, v, seg->m_afStart[1]);
        seg->m_afStart[1] = offset;
        const float amplitude = seg->m_fAmplitude;
        if (std::fabs(offset) > amplitude) {
            float folded;
            if (offset < kZero) {
                folded = ppc::fmsubs(amplitude, kMinusTwo, offset);
                if (amplitude >= folded) {
                    seg->m_afStart[1] = folded;
                } else {
                    seg->m_afStart[1] = amplitude;
                }
            } else {
                folded = (amplitude + amplitude) - offset;
                if (amplitude >= folded) folded = amplitude;
                seg->m_afStart[1] = folded;
            }
            seg->m_fSpeed = -seg->m_fSpeed;
        }
    }
    seg->m_bPointsCached = 0;
    if (seg->m_ui32NbChildren == 0) return;
    for (uint32_t k = 0; k < seg->m_ui32NbChildren; ++k) {
        UpdateBranchesRecursive(a, b, frameClock, seg->m_ui32FirstChild + k);
        seg = &m_segments.m_pBlock[index];
    }
    for (uint32_t k = 1; k < seg->m_ui32NbChildren; ++k) {
        SSegment& c = m_segments.m_pBlock[seg->m_ui32FirstChild + k];
        SSegment& p = m_segments.m_pBlock[seg->m_ui32FirstChild + k - 1];
        p.m_afEnd[2] = c.m_afStart[2];
        p.m_afEnd[0] = c.m_afStart[0];
        p.m_afEnd[1] = c.m_afStart[1];
    }
}

// 0x0057bd30 CKLightningBoltNodeFx_RemoveBranchRecursive_maybe
void CKLightningBoltNodeFx::RemoveBranchRecursive(uint32_t index) {
    SSegment* seg = &m_segments.m_pBlock[index];
    const uint32_t count = seg->m_ui32NbChildren;
    if (count != 0) {
        for (uint32_t k = 0; k < count; ++k) RemoveBranchRecursive(seg->m_ui32FirstChild + k);
        seg = &m_segments.m_pBlock[index];
        uint32_t used = m_ui32NbSegments;
        const uint32_t end = count + seg->m_ui32FirstChild;
        for (uint32_t i = end; i < used; ++i) {
            m_segments.m_pBlock[i - count] = m_segments.m_pBlock[i];
            used = m_ui32NbSegments;
        }
        m_ui32NbSegments = used - count;
        for (uint32_t i = 0; i < m_ui32NbSegments; ++i) {
            SSegment& s = m_segments.m_pBlock[i];
            if (end <= s.m_ui32FirstChild) s.m_ui32FirstChild = s.m_ui32FirstChild - count;
            if (end <= s.m_ui32Parent) s.m_ui32Parent = s.m_ui32Parent - count;
        }
    }
    seg->m_ui32FirstChild = 0;
    seg->m_ui32NbChildren = 0;
}

// 0x00580c58 CKLightningBoltNodeFx_SetEndParticlesActive_maybe
void CKLightningBoltNodeFx::SetEndParticlesActive(int32_t active) {
    if (active == 0) {
        if (m_pStartParticles != nullptr) {
            StopOwnedParticleEffect(static_cast<IKFx*>(m_pStartParticles), this);  // 0x001cdde8
            static_cast<IKFx*>(m_pStartParticles)->ReleaseReservation(this);       // vt+0x54
            m_pStartParticles = nullptr;
        }
        if (m_pEndParticles != nullptr) {
            StopOwnedParticleEffect(static_cast<IKFx*>(m_pEndParticles), this);
            static_cast<IKFx*>(m_pEndParticles)->ReleaseReservation(this);
            m_pEndParticles = nullptr;
        }
        return;
    }
    CKLightningBoltFxData* data = DataOf(this);
    CKParticlesEffectFxData* first = static_cast<CKParticlesEffectFxData*>(data->m_unk40);
    first->m_pAttachHotSpot = nullptr;
    first->m_pAttachOwner = reinterpret_cast<CSGLeaf*>(m_pNode);
    CKParticlesEffectFxData* second = static_cast<CKParticlesEffectFxData*>(data->m_unk44);
    second->m_pAttachHotSpot = nullptr;
    second->m_pAttachOwner = reinterpret_cast<CSGLeaf*>(m_pNode);
    CKSrvFx* service = static_cast<CKSrvFx*>(g_pEngine->m_srvFx);
    m_pStartParticles = service->AcquireFx(static_cast<IKFxData*>(data->m_unk40), this);  // the inlined CKSrvFx_AcquireFx
    m_pEndParticles = service->AcquireFx(static_cast<IKFxData*>(data->m_unk44), this);
}

// 0x0057c650 CKLightningBoltNodeFx_PlaceNodeAtSource_maybe: the node moved under the dynamic scene root, at the
// source (the data's source node, else its source hot spot) when `owner` owns the bolt.
void CKLightningBoltNodeFx::PlaceNodeAtSource(const IKSerializable* owner) {
    CSGLeaf* node = reinterpret_cast<CSGLeaf*>(m_pNode);
    if (node->m_pParent != nullptr) node->m_pParent->RemoveChild(node);   // vt+0x78
    static_cast<CSGBranch*>(g_pEngine->m_dynamicSceneRoot)->AddChild(node);  // vt+0x70
    CKLightningBoltFxData* data = DataOf(this);
    CVector3 position;
    if (data->m_pSourceNode != nullptr) {
        const RwV3d& p = FrameLtm(static_cast<CSGMovable*>(data->m_pSourceNode)->m_pRwFrame)->pos;  // RwFrame +0x80
        position = {p.x, p.y, p.z};
    } else {
        CSGHotSpot* hotSpot = static_cast<CSGHotSpot*>(data->m_pSourceHotSpot);
        if (hotSpot == nullptr) return;
        hotSpot->GetWorldPosition(&position);  // 0x000ce790
    }
    if ((m_baFxData & 2u) == 0 || m_pOwner != owner) return;
    RwFrame* frame = static_cast<CSGMovable*>(m_pNode)->m_pRwFrame;
    frame->modelling.pos = {position.x, position.y, position.z};
    frame->modelling.flags &= 0xfffdffffu;
    RwFrame_MarkDirty(frame);  // 0x00010698
}

// 0x0057c4c8 CKLightningBoltNodeFx_SyncNodeToTarget_maybe: with the data's flag bit 2, the node follows the source
// (the source node, updated first (vt+0x50); else the source hot spot; a hot spot without a node stops the bolt).
void CKLightningBoltNodeFx::SyncNodeToTarget() {
    CKLightningBoltFxData* data = DataOf(this);
    if (((data->m_unk18 >> 2) & 1u) == 0) return;
    RwFrame* frame = static_cast<CSGMovable*>(m_pNode)->m_pRwFrame;
    if (data->m_pSourceNode != nullptr) {
        CSGMovable* source = static_cast<CSGMovable*>(data->m_pSourceNode);
        source->ForceWorldMatrixUpdate();  // vt+0x50
        const RwV3d& p = FrameLtm(static_cast<CSGMovable*>(DataOf(this)->m_pSourceNode)->m_pRwFrame)->pos;
        frame->modelling.pos = p;
        frame->modelling.flags &= 0xfffdffffu;
        RwFrame_MarkDirty(frame);
        return;
    }
    CSGHotSpot* hotSpot = static_cast<CSGHotSpot*>(data->m_pSourceHotSpot);
    if (hotSpot == nullptr) return;
    if (hotSpot->m_pParent == nullptr) {
        Stop();  // vt+0x6c
        return;
    }
    CVector3 position;
    hotSpot->GetWorldPosition(&position);
    frame->modelling.pos = {position.x, position.y, position.z};
    frame->modelling.flags &= 0xfffdffffu;
    RwFrame_MarkDirty(frame);
}

// 0x0057ae68 CKLightningBoltNodeFx_UpdateEndpoints_maybe: the end point in the world (+0x3c: the target node, or the
// target hot spot plus the offset), and the start point (+0x30) the same in the node's space.
void CKLightningBoltNodeFx::UpdateEndpoints() {
    CKLightningBoltFxData* data = DataOf(this);
    if ((data->m_unk18 & 4u) == 0) {
        if (m_vStart.x == kNullVector.x && m_vStart.y == kNullVector.y && m_vStart.z == kNullVector.z) {
            if (data->m_pTargetNode != nullptr) {
                const RwV3d& p = FrameLtm(static_cast<CSGMovable*>(data->m_pTargetNode)->m_pRwFrame)->pos;
                m_vEnd = {p.x, p.y, p.z};
            } else if (data->m_pTargetHotSpot != nullptr) {
                static_cast<CSGHotSpot*>(data->m_pSourceHotSpot)->GetWorldPosition(&m_vSourceOffset);
            }
        }
        m_vStart = m_vSourceOffset;
    } else {
        m_vStart = kNullVector;
        if (data->m_pTargetNode != nullptr) {
            const RwV3d& p = FrameLtm(static_cast<CSGMovable*>(data->m_pTargetNode)->m_pRwFrame)->pos;
            m_vStart = {p.x, p.y, p.z};
        } else {
            CSGHotSpot* hotSpot = static_cast<CSGHotSpot*>(data->m_pTargetHotSpot);
            if (hotSpot != nullptr) {
                if (hotSpot->m_pParent == nullptr) {
                    Stop();  // vt+0x6c
                    return;
                }
                hotSpot->GetWorldPosition(&m_vStart);
            }
        }
    }
    CMatrix34 inverse;
    Mat4_Invert(&inverse, reinterpret_cast<const CMatrix34*>(&static_cast<CSGMovable*>(m_pNode)->m_pRwFrame->modelling));  // 0x0023f878
    const float x = m_vStart.x;
    const float y = m_vStart.y;
    const float z = m_vStart.z;
    m_vStart.x = x + m_vSourceOffset.x;
    m_vEnd.x = x + m_vSourceOffset.x;
    m_vStart.y = y + m_vSourceOffset.y;
    m_vStart.z = z + m_vSourceOffset.z;
    m_vEnd.y = y + m_vSourceOffset.y;
    m_vEnd.z = z + m_vSourceOffset.z;
    Mat4_TransformPoints(&inverse, &m_vStart, &m_vEnd, 1);  // 0x0023f7e8
}

// 0x0057ac28 CKLightningBoltNodeFx_ResetImpactSlots_maybe: a random impact count between the data's +0x90 and +0x94
// (one draw); each slot cleared with a random interval (one draw each); the impacts' bolt data (+0x8c) told the
// source and target.
void CKLightningBoltNodeFx::ResetImpactSlots() {
    const uint32_t r = static_cast<uint32_t>(Rand_Int());
    CKLightningBoltFxData* data = DataOf(this);
    const int32_t lo = data->m_i32ImpactsMin;
    const uint32_t spread = static_cast<uint32_t>(
        (static_cast<int64_t>(static_cast<int32_t>(r & 0xffffu)) * static_cast<int64_t>(data->m_i32ImpactsMax - lo)) >> 16);
    const int32_t count = lo + static_cast<int32_t>(spread & 0xffffu);
    m_ui32NbImpacts = static_cast<uint32_t>(count);
    const uint16_t flags = data->m_unk18;
    if (((flags >> 6) & 1u) == 0 && ((flags >> 8) & 1u) == 0 && ((flags >> 7) & 1u) == 0) {
        m_ui32NbImpacts = (flags >> 7) & 1u;  // 0
        return;
    }
    if (count == 0) return;
    for (uint32_t i = 0; i < m_ui32NbImpacts; ++i) {
        SImpactSlot& slot = m_aImpacts[i];
        slot.m_bActive = 0;
        slot.m_pTarget = nullptr;
        slot.m_pFx = nullptr;
        slot.m_fTimer = 0.0f;
        const float centre = DataOf(this)->m_unka0;
        const float range = DataOf(this)->m_unka4;
        slot.m_fTimer = ppc::fmadds(RandUnit16() * kMinusTwo, range, centre + range);
    }
    data = DataOf(this);
    CKLightningBoltFxData* impacts = static_cast<CKLightningBoltFxData*>(data->m_unk8c);
    if (((data->m_unk18 >> 2) & 1u) == 0) {
        impacts->m_pTargetNode = nullptr;
        impacts->m_pTargetHotSpot = nullptr;
        impacts->m_pSourceNode = nullptr;
        impacts->m_pSourceHotSpot = nullptr;
        return;
    }
    if (data->m_pSourceNode != nullptr) {
        impacts->m_pSourceHotSpot = nullptr;
        impacts->m_pSourceNode = data->m_pTargetNode;
    } else if (data->m_pSourceHotSpot != nullptr) {
        if (static_cast<CSGHotSpot*>(data->m_pSourceHotSpot)->m_pParent != nullptr) {
            impacts->m_pSourceNode = nullptr;
            impacts->m_pSourceHotSpot = data->m_pTargetHotSpot;
        }
    } else {
        impacts->m_pTargetNode = nullptr;
        impacts->m_pTargetHotSpot = nullptr;
        impacts->m_pSourceNode = nullptr;
        impacts->m_pSourceHotSpot = nullptr;
    }
}

// 0x00581178 CKLightningBoltNodeFx_Stop
void CKLightningBoltNodeFx::Stop() {
    SetEndParticlesActive(0);
    for (uint32_t i = 0; i < m_ui32NbImpacts; ++i) {
        IKFx* fx = static_cast<IKFx*>(m_aImpacts[i].m_pFx);
        if (fx != nullptr && ((fx->m_baFxData & 1u) == 0 || (fx->m_baFxData & 2u) != 0)) fx->StopAndRelease(this);  // vt+0x58
    }
    if (m_pSphere != nullptr) {
        CSGBranch* parent = reinterpret_cast<CSGLeaf*>(m_pSphere)->m_pParent;
        if (parent != nullptr) parent->RemoveChild(reinterpret_cast<CSGLeaf*>(m_pSphere));  // vt+0x78
        static_cast<CKSrvCollision*>(g_pEngine->m_srvCollision)->ReleaseDynSphere(reinterpret_cast<IKBoundingVolume*>(m_pSphere));
        m_pSphere = nullptr;
    }
    m_baFxData = static_cast<uint8_t>((m_baFxData & 0xfc) | 1);
    CSGLeaf* node = reinterpret_cast<CSGLeaf*>(m_pNode);
    if (node->m_pParent != nullptr) node->m_pParent->RemoveChild(node);
    static_cast<CSGBranch*>(g_pEngine->m_dynamicSceneRoot)->AddChild(node);
    node->m_sgProperties = (node->m_sgProperties & 0xfffffffbu) | 4u;  // hidden
    m_baFxData = static_cast<uint8_t>((m_baFxData & 0xf0) | (m_baFxData & 7));
}

// 0x00581380 CKLightningBoltNodeFx_SetActiveForOwner_maybe: for `owner` (the bolt reserved by it), on: a stopped
// or inactive bolt starts at the source (the points and the root reset, the basis from the direction, the levels from
// the data, the end particles, the impacts, the data's lifetime flag, the collision sphere of a damaging bolt); off:
// the end particles, the impacts and the sphere released, the node hidden, inactive.
void CKLightningBoltNodeFx::SetActiveForOwner(const IKSerializable* owner, int32_t active) {
    if ((m_baFxData & 2u) == 0 || m_pOwner != owner) return;
    if (active == 0) {
        if (((m_baFxData >> 3) & 1u) == 0) return;
        SetEndParticlesActive(0);
        for (uint32_t i = 0; i < m_ui32NbImpacts; ++i) {
            IKFx* fx = static_cast<IKFx*>(m_aImpacts[i].m_pFx);
            if (fx == nullptr) continue;
            if ((fx->m_baFxData & 1u) == 0 || (fx->m_baFxData & 2u) != 0) fx->StopAndRelease(this);  // vt+0x58
        }
        if (m_pSphere != nullptr) {
            CSGBranch* parent = reinterpret_cast<CSGLeaf*>(m_pSphere)->m_pParent;
            if (parent != nullptr) parent->RemoveChild(reinterpret_cast<CSGLeaf*>(m_pSphere));
            static_cast<CKSrvCollision*>(g_pEngine->m_srvCollision)->ReleaseDynSphere(reinterpret_cast<IKBoundingVolume*>(m_pSphere));
        }
        m_pSphere = nullptr;
        CSGLeaf* node = reinterpret_cast<CSGLeaf*>(m_pNode);
        if (node->m_pParent != nullptr) node->m_pParent->RemoveChild(node);
        static_cast<CSGBranch*>(g_pEngine->m_dynamicSceneRoot)->AddChild(node);
        node->m_sgProperties = (node->m_sgProperties & 0xfffffffbu) | 4u;
        m_baFxData = static_cast<uint8_t>(m_baFxData & 0xf7);
        return;
    }
    if (((m_baFxData >> 3) & 1u) != 0 || ((m_baFxData >> 2) & 1u) != 0) return;
    m_fTime = kZero;
    m_fLifetime = kZero;
    m_vStart = kNullVector;
    m_vEnd = kNullVector;
    PlaceNodeAtSource(owner);
    UpdateEndpoints();
    SSegment& root = m_segments.m_pBlock[0];
    root.m_ui32Level = 0;
    SetPoint(root.m_afStart, kNullVector);
    SetPoint(root.m_afEnd, kNullVector);
    root.m_bPointsCached = 0;
    root.m_ui32Parent = 0;
    root.m_ui32FirstChild = 0;
    root.m_ui32NbChildren = 0;
    root.m_bLeaf = 0;
    root.m_fSpeed = kZero;
    root.m_fAccel = kZero;
    root.m_fAmplitude = kZero;
    root.m_fExpiry = kZero;
    root.m_vPoint = kNullVector;
    root.m_vDirection = kNullVector;
    root.m_vUp = kNullVector;
    root.m_fWidth = 0.2f;  // TOC2 -0x73fc
    m_ui32NbSegments = 1;
    float dy = m_vStart.y - kNullVector.y;
    float dx = m_vStart.x - kNullVector.x;
    float dz = m_vStart.z - kNullVector.z;
    m_vDirection = {dx, dy, dz};
    const float length = std::sqrt(ppc::fmadds(dz, dz, ppc::fmadds(dx, dx, dy * dy)));
    if (length != kZero) {
        const float k = kOne / length;
        m_vDirection = {k * m_vDirection.x, k * m_vDirection.y, k * m_vDirection.z};
        if (length < kZero) m_vDirection = {0.0f, 0.0f, 1.0f};  // TOC2 -0x7360 (0x00c50d4c); never taken
    }
    CMatrix34 basis;
    if (Mat4_SetBasisFromAtUp(&basis, &m_vDirection, &kAxisY) == 0) {  // 0x0023fd30
        const CVector3 kAxisX = {1.0f, 0.0f, 0.0f};  // 0x00c50d34 (TOC2 -0x735c)
        Mat4_SetBasisFromAtUp(&basis, &m_vDirection, &kAxisX);
    }
    m_vRight = basis.m_right;
    m_vUp = basis.m_up;
    m_baFxData = static_cast<uint8_t>((m_baFxData & 0xf7) | 8);
    CSGLeaf* node = reinterpret_cast<CSGLeaf*>(m_pNode);
    node->m_sgProperties &= 0xfffffffbu;  // shown
    if (m_ui32MaxLevels != 0xffffffffu) {
        for (uint32_t i = 0; m_ui32MaxLevels + 1 > i; ++i) DataOf(this)->CopyEntry60(&m_aLevels[i], i);  // 0x00577868
    }
    m_fSourceExplosionTimer = 0.0f;
    m_fEndExplosionTimer = 0.0f;
    SetEndParticlesActive(1);
    ResetImpactSlots();
    if (((DataOf(this)->m_unk18 >> 1) & 1u) != 0) {
        m_fLifetime = 0.2f;  // f30 (TOC2 -0x73fc) still
        m_baFxData = static_cast<uint8_t>((m_baFxData & 0xfb) | 4);
    }
    if (m_pDamageOwner == nullptr) return;
    CKSrvCollision* collision = static_cast<CKSrvCollision*>(g_pEngine->m_srvCollision);
    if (m_pSphere == nullptr) {
        m_pSphere = static_cast<CKDynamicBoundingSphere*>(collision->AcquireDynSphere());  // 0x00192a70
        if (m_pSphere == nullptr) return;
    }
    CKDynamicBoundingSphere* sphere = m_pSphere;
    const float radius = DataOf(this)->m_unk88;
    sphere->m_fRadius = radius <= kZero ? 0.001f : radius;  // TOC2 -0x738c
    sphere->m_ba8Infos = static_cast<uint8_t>(sphere->m_ba8Infos | 0x08);
    sphere->m_ba8Infos = static_cast<uint8_t>(sphere->m_ba8Infos | 0x20);
    sphere->m_ba8Infos = static_cast<uint8_t>(sphere->m_ba8Infos | 0x04);
    sphere->m_v3WorldMove = kNullVector;
    sphere->m_v3OldPos = m_vEnd;
    sphere->m_v3LastWorldPos = m_vEnd;
    sphere->m_ui8OwnerType = 0;
    sphere->m_ui16PropertiesFlags = 0;
    sphere->m_pOwner = m_pDamageOwner;
    sphere->m_ui8OwnerType = m_ui8DamageCategory;
    sphere->m_ui16PropertiesFlags = static_cast<uint16_t>(sphere->m_ui16PropertiesFlags | m_ui16DamageFlags);
    sphere->m_unk1c = m_pDamage;
    RwFrame* frame = sphere->m_pRwFrame;
    frame->modelling.pos = {m_vEnd.x, m_vEnd.y, m_vEnd.z};
    frame->modelling.flags &= 0xfffdffffu;
    RwFrame_MarkDirty(frame);
    CSGBranch* root2 = static_cast<CSGBranch*>(g_pEngine->m_dynamicSceneRoot);
    CSGBranch* parent = sphere->m_pParent;
    if (parent == root2) return;
    if (parent != nullptr) parent->RemoveChild(sphere);
    root2->AddChild(sphere);
}

// 0x005806c8 CKLightningBoltNodeFx_UpdateImpactExplosions_maybe. The timer gets its next interval whether or not the
// pool had a free explosion.
void CKLightningBoltNodeFx::UpdateImpactExplosions(IKTime* frameClock) {
    CKSrvFx* srvFx = static_cast<CKSrvFx*>(g_pEngine->m_srvFx);
    m_fSourceExplosionTimer = m_fSourceExplosionTimer - frameClock->m_afDeltaTime[0];
    m_fEndExplosionTimer = m_fEndExplosionTimer - frameClock->m_afDeltaTime[0];
    if (m_fSourceExplosionTimer < kZero) {
        IKFx* fx = srvFx->AcquireFx(reinterpret_cast<IKFxData*>(DataOf(this)->m_pSourceExplosion), this);
        if (fx != nullptr) {
            CKExplosionNodeFx* explosion = static_cast<CKExplosionNodeFx*>(fx);
            const RwV3d& p = static_cast<CSGMovable*>(m_pNode)->m_pRwFrame->modelling.pos;  // RwFrame +0x40
            const CVector3 position = {p.x, p.y, p.z};
            explosion->SetTranslation(&position, this);  // 0x001b66e8
            explosion->Trigger(this, 0);                  // 0x001b82a8
            explosion->ReleaseReservation(this);          // vt+0x54
        }
        m_fSourceExplosionTimer = m_fSourceExplosionTimer + DataOf(this)->RandomInterval50();  // 0x00577630
    }
    if (m_fEndExplosionTimer < kZero) {
        IKFx* fx = srvFx->AcquireFx(reinterpret_cast<IKFxData*>(DataOf(this)->m_pEndExplosion), this);
        if (fx != nullptr) {
            CKExplosionNodeFx* explosion = static_cast<CKExplosionNodeFx*>(fx);
            explosion->SetTranslation(&m_vEnd, this);
            explosion->Trigger(this, 0);
            explosion->ReleaseReservation(this);
        }
        m_fEndExplosionTimer = m_fEndExplosionTimer + DataOf(this)->RandomInterval58();  // 0x005775b8
    }
}

namespace {
// 0x004ec5b8 CKS08GameManager_vf13C (local copy; the bolt calls it through the game manager's vtable, which dotd does not
// declare that far): the target answers message 0x402 (MessageProc vt+0x1c) with a non-zero word and returns 0 (handled).
uint8_t GameManagerAcceptsTarget(IKSerializable* target) {
    if (target == nullptr) return 0;
    int32_t answer = 0;
    if (target->MessageProc(0x402, &answer) != 0) return 0;
    return answer != 0 ? 1 : 0;
}
// The message 0x400 record (sp+0x70 in 0x4ee988): a byte, the aim point (in: the target's node LTM position), a word and
// the game manager.
struct SAimPointMessage {
    uint8_t m_unk00;             // +0x00 0
    uint8_t m_pad01[3];
    CVector3 m_v3Point;          // +0x04
    uint32_t m_unk10;            // +0x10 0
    IKSerializable* m_pManager;  // +0x14
};
// 0x004ee988 CKS08GameManager_vf140 (local copy, as vf13C): the target's aim point: its node's LTM position offered with
// message 0x400; the answer when the target handled it (MessageProc 0), else the null vector.
CVector3 GameManagerTargetPoint(IKSerializable* manager, IKSerializable* target) {
    CVector3 out = {0.0f, 0.0f, 0.0f};  // 0x00c50d64
    SAimPointMessage message;
    const RwV3d& p = static_cast<CSGMovable*>(static_cast<IKHook*>(target)->m_pKGLObject)->m_pRwFrame->ltm.pos;  // +0x80
    message.m_v3Point = {p.x, p.y, p.z};
    message.m_pManager = manager;
    message.m_unk00 = 0;
    message.m_unk10 = 0;
    if (target->MessageProc(0x400, &message) == 0) out = message.m_v3Point;
    return out;
}
}  // namespace

// 0x0057dce8 CKLightningBoltNodeFx_IsLinkedTo_maybe
uint8_t CKLightningBoltNodeFx::IsLinkedTo(const IKSerializable* target, const CKLightningBoltNodeFx* from) {
    for (uint32_t i = 0; i < m_ui32NbImpacts; ++i) {
        if (m_aImpacts[i].m_pTarget == target) return 1;
        CKLightningBoltNodeFx* bolt = static_cast<CKLightningBoltNodeFx*>(m_aImpacts[i].m_pFx);
        if (bolt != nullptr && (bolt->m_baFxData & 8u) != 0 && bolt != from && bolt->IsLinkedTo(target, this) != 0) return 1;
        IKSerializable* owner = const_cast<IKSerializable*>(m_pOwner);
        if (owner != nullptr && owner->IsKindOfClass(0xa60c) != 0 && owner != from) {  // vt+0x08: a lightning bolt
            return static_cast<CKLightningBoltNodeFx*>(owner)->IsLinkedTo(target, this);
        }
        if (m_unk1e8 == target) return 1;
    }
    return 0;
}

// 0x0057e348 CKLightningBoltNodeFx_CollectTargetsInRange_maybe
IKSerializable* CKLightningBoltNodeFx::CollectTargetsInRange(CVector3* position) {
    const uint16_t flags = DataOf(this)->m_unk18;
    if (((flags >> 6) & 1u) == 0 && ((flags >> 8) & 1u) == 0 && ((flags >> 7) & 1u) == 0) return nullptr;
    const float high = DataOf(this)->m_unk98 + DataOf(this)->m_unk9c;
    const float low = DataOf(this)->m_unk98 - DataOf(this)->m_unk9c;
    float best = 3.40282347e+38f;  // 0x00c4acb8 +0x28 (TOC2 -0x7374): FLT_MAX
    CDefaultGameManager* manager = g_pEngine->m_gameManager;  // engine +0x8c
    IKSerializable* found = nullptr;
    // One candidate: it has a node, is not linked to this bolt, the game manager accepts it and its aim point lies in
    // the range, nearer than the best so far (a Manhattan distance from the end point).
    auto consider = [&](IKSerializable* candidate) {
        if (candidate == nullptr || static_cast<IKHook*>(candidate)->m_pKGLObject == nullptr) return;
        if (m_ui32NbImpacts != 0 && IsLinkedTo(candidate, this) != 0) return;
        if (GameManagerAcceptsTarget(candidate) == 0) return;  // vt+0x13c
        const CVector3 point = GameManagerTargetPoint(manager, candidate);  // vt+0x140
        const float distance =
            std::fabs(point.x - m_vEnd.x) + std::fabs(point.y - m_vEnd.y) + std::fabs(point.z - m_vEnd.z);
        if (!(low < distance || low == distance)) return;    // cror lt / eq
        if (!(high > distance || high == distance)) return;  // cror gt / eq
        if (!(distance < best)) return;
        best = distance;
        found = candidate;
        *position = point;
    };
    if (((flags >> 6) & 1u) != 0) {
        CKGrpS08Hero* heroes = static_cast<CKGrpS08Hero*>(manager->m_unk04[1]);  // +0x08
        if (heroes != nullptr) {
            IKSerializable** list = heroes->m_apHeroesCopy;           // 0x002ca0f0 CKGrpS08Hero_GetHeroList
            uint32_t count = heroes->CKGrpS08Hero::GetHeroCount();  // 0x002ce318 (called directly)
            while (count != 0) {
                --count;
                consider(*list);
                ++list;
            }
        }
    }
    if (((DataOf(this)->m_unk18 >> 7) & 1u) != 0) {
        IKGrpEnemy* enemies = static_cast<IKGrpEnemy*>(manager->m_unk04[0]);  // +0x04
        if (enemies != nullptr) {
            const uint32_t count = enemies->m_ui32NbActiveEnemies;
            for (uint32_t i = 0; i != count; ++i) consider(enemies->m_apActiveEnemies[i]);
        }
    }
    if (((DataOf(this)->m_unk18 >> 8) & 1u) != 0) {
        CKGrpMeca* mecas = static_cast<CKGrpMeca*>(manager->m_unk04[2]);  // +0x0c
        if (mecas != nullptr) {
            uint32_t count = mecas->m_unk30;
            IKHook** list = mecas->m_pUnk2c;
            while (count != 0) {
                --count;
                consider(*list);
                ++list;
            }
        }
    }
    return found;
}

// 0x00581c38 CKLightningBoltNodeFx_UpdateImpactSlots_maybe: per impact slot. A slot on a target keeps its sub-bolt on
// it (at the end point when the sub-bolt data has no source, aimed at the target's aim point) while the target is
// still accepted and the sub-bolt runs; otherwise the sub-bolt is stopped and let go (vt+0x58) and the slot waits a new
// random interval (1 rand draw). A waiting slot counts its timer down by the frame's delta; at 0 (and only one new
// sub-bolt per frame) it looks for a target (CollectTargetsInRange) and takes a sub-bolt from the FX pool (the data's
// +0x8c: placed at the end point, aimed at the target, the damage fields and the target copied, switched on); without
// a target or a free sub-bolt it waits a new random interval (1 rand draw).
void CKLightningBoltNodeFx::UpdateImpactSlots(IKTime* frameClock) {
    if (m_ui32NbImpacts == 0) return;
    uint8_t started = 0;
    // A sub-bolt reserved by this bolt, with a source-less data, placed at the end point.
    auto placeAtEnd = [this](CKLightningBoltNodeFx* bolt) {
        const CKLightningBoltFxData* sub = static_cast<const CKLightningBoltFxData*>(DataOf(this)->m_unk8c);
        if (sub->m_pSourceNode != nullptr || sub->m_pSourceHotSpot != nullptr) return;
        if ((bolt->m_baFxData & 2u) == 0 || bolt->m_pOwner != this) return;
        RwFrame* frame = static_cast<CSGMovable*>(bolt->m_pNode)->m_pRwFrame;
        frame->modelling.pos.z = m_vEnd.z;
        frame->modelling.pos.x = m_vEnd.x;
        frame->modelling.pos.y = m_vEnd.y;
        frame->modelling.flags &= 0xfffdffffu;
        RwFrame_MarkDirty(frame);  // 0x00010698 (through its TocBridge)
    };
    auto newInterval = [this](SImpactSlot& slot) {
        const float base = DataOf(this)->m_unka0 + DataOf(this)->m_unka4;
        slot.m_fTimer = ppc::fmadds(RandUnit16() * kMinusTwo, DataOf(this)->m_unka4, base);  // TOC2 -0x7410 / -0x740c
    };
    for (uint32_t i = 0; i < m_ui32NbImpacts; ++i) {
        SImpactSlot& slot = m_aImpacts[i];
        if (slot.m_bActive != 0) {
            CKLightningBoltNodeFx* bolt = static_cast<CKLightningBoltNodeFx*>(slot.m_pFx);
            // BUG(original): an active slot without a sub-bolt calls vt+0x58 on null (an active slot always has one).
            if (bolt != nullptr && slot.m_pTarget != nullptr && GameManagerAcceptsTarget(slot.m_pTarget) != 0 &&
                (bolt->m_baFxData & 1u) == 0) {
                placeAtEnd(bolt);
                const CVector3 point = GameManagerTargetPoint(g_pEngine->m_gameManager, slot.m_pTarget);  // vt+0x140
                bolt->SetTargetPoint(&point, this);  // inlined
                continue;
            }
            bolt->StopAndRelease(this);  // vt+0x58
            slot.m_bActive = 0;
            slot.m_fTimer = 0.0f;
            slot.m_pTarget = nullptr;
            slot.m_pFx = nullptr;
            newInterval(slot);
            continue;
        }
        slot.m_fTimer = slot.m_fTimer - frameClock->m_afDeltaTime[0];  // +0x1c
        if (!(slot.m_fTimer < kZero || slot.m_fTimer == kZero)) continue;  // cror lt / eq
        if (started != 0) continue;
        CVector3 point = {0.0f, 0.0f, 0.0f};  // 0x00c50d64 (TOC2 -0x7408)
        slot.m_pTarget = CollectTargetsInRange(&point);  // 0x0057e348
        if (slot.m_pTarget != nullptr) {
            IKFxData* sub = static_cast<IKFxData*>(DataOf(this)->m_unk8c);
            CKLightningBoltNodeFx* bolt =
                static_cast<CKLightningBoltNodeFx*>(static_cast<CKSrvFx*>(g_pEngine->m_srvFx)->AcquireFx(sub, this));
            if (bolt != nullptr) {
                placeAtEnd(bolt);
                bolt->SetTargetPoint(&point, this);                  // the inlined setters, each for this owner
                bolt->SetDamageOwner(m_pDamageOwner, this);          // +0x1e0
                bolt->SetDamageCategory(m_ui8DamageCategory, this);  // +0x1e4
                bolt->SetDamageFlags(m_ui16DamageFlags, this);       // +0x1e6
                bolt->SetDamage(m_pDamage, this);                    // +0x1d8
                bolt->SetUnk1e8(slot.m_pTarget, this);               // +0x1e8
                started = 1;
                bolt->SetActiveForOwner(this, 1);  // 0x00581380
                slot.m_bActive = 1;
                slot.m_pFx = bolt;
                continue;
            }
        }
        if (slot.m_bActive == 0) newInterval(slot);
    }
}

namespace {

const float kHalfPi = 1.57079637f;     // TOC2 -0x7370
const float kTwo = 2.0f;               // TOC2 -0x7368
const float kMinusHalf = -0.5f;        // TOC2 -0x736c
const float kSharpSine = 0.2f;         // TOC2 -0x73fc
const float kSameWidth = 0.1f;         // TOC2 -0x737c
const float kCapRadius = 1000.0f;      // TOC2 -0x7364

bool SignBitSet(float x) {
    int32_t bits;
    std::memcpy(&bits, &x, 4);
    return bits < 0;
}
// The inlined sinf / cosf with the library call (TocBridge_sinf 0x98fdd0 / TocBridge_cosf 0x98fde0) for a negative
// argument (its sign bit tested through memory).
float GameSin(float x) { return SignBitSet(x) ? -crt::LibSinf(-x) : crt::InlineSinf(x); }
float GameCos(float x) { return SignBitSet(x) ? crt::LibCosf(-x) : crt::InlineCosf(x); }
// Math_Sqrtf (TocBridge 0x98fc10).
float Sqrtf(float x) { return std::sqrt(x); }
// The arc cosine of a dot product clamped to [-1, 1] (`cror lt|eq` / `cror gt|eq`; NaN passes through).
float AcosClamped(float dot) {
    if (dot < kMinusOne || dot == kMinusOne) return crt::Acosf(kMinusOne);
    if (dot > kOne || dot == kOne) dot = kOne;
    return crt::Acosf(dot);  // 0x00780c90
}
// sqrt(fmadds(z, z, fmadds(x, x, y * y))).
float Length(float x, float y, float z) { return Sqrtf(ppc::fmadds(z, z, ppc::fmadds(x, x, y * y))); }

}  // namespace

// 0x00580030 CKLightningBoltNodeFx_RebuildGeometry_maybe. The leaf walk's ComputeBranchPoint calls also leave the points
// of every visited segment (and of their parents) cached, and a branch that regrows in the next frame's
// UpdateBranchesRecursive (before the flags are cleared) grows from those: the root's length of the frame before (fight
// capture 3, +56: a child's end t one ulp off; capture 2, +880: a regrown branch's child count).
void CKLightningBoltNodeFx::RebuildGeometry() {
    CGeometry* geometry = static_cast<CGeometry*>(m_pNode->m_lGeometryList);
    m_unk8c = kOne;
    // GetMaterialTexture_maybe 0xbb398 (through its TocBridge): the material's RpMaterial texture unless its property
    // bit 0x1000 is set; the ratio is the raster's height over its width (unsigned words, fcfid).
    auto materialTexture = [](CGeometry* g) -> RwTexture* {
        const CMaterial* material = static_cast<const CMaterial*>(g->m_pMaterial);
        if ((material->m_baProperties & 0x1000u) != 0) return nullptr;
        return material->m_pRpMaterial->texture;
    };
    if (materialTexture(geometry) != nullptr) {
        float height = kZero;
        const RwRaster* raster = materialTexture(geometry)->raster;
        if (raster != nullptr) height = static_cast<float>(static_cast<double>(static_cast<uint32_t>(raster->height)));
        raster = materialTexture(geometry)->raster;
        float width = kZero;
        if (raster != nullptr) width = static_cast<float>(static_cast<double>(static_cast<uint32_t>(raster->width)));
        m_unk8c = height / width;
    }
    RpGeometry* rpGeometry = geometry->m_pRpAtomic->geometry;
    RpGeometryLock(rpGeometry, 0x12);  // 0x006a0e28: the vertices and the texture coordinates
    CVector3* left = reinterpret_cast<CVector3*>(rpGeometry->morphTarget[0].verts);
    CVector3* right = left + m_ui32NbVertices;
    float* uvs = reinterpret_cast<float*>(rpGeometry->texCoords[0]);
    m_ui32NbStripVertices = 0;
    float texLeft = kZero;   // sp+0x78
    float texRight = kZero;  // sp+0x74
    const uint32_t last = BuildBranchVertices(0, 0, &texLeft, &texRight, &left, &right, &uvs);  // 0x0057ec40
    // The end cap at the start point (+0x30), across the world up, widened by the last leaf's angle to the bolt.
    const SSegment& leaf = m_segments.m_pBlock[last];
    float dx = m_vDirection.x;
    float dz = m_vDirection.z;
    float dy = m_vDirection.y;
    float lx = leaf.m_vDirection.x;
    float ly = leaf.m_vDirection.y;
    float lz = leaf.m_vDirection.z;
    float length = Length(lx, ly, lz);
    if (length != kZero) {
        const float k = kOne / length;
        lz = lz * k;
        lx = lx * k;
        ly = ly * k;
    }
    length = Length(dx, dy, dz);
    if (length != kZero) {
        const float k = kOne / length;
        dz = dz * k;
        dx = dx * k;
        dy = dy * k;
    }
    const float dot = ppc::fmadds(lz, dz, ppc::fmadds(lx, dx, dy * ly));
    const float angle = kHalfPi - AcosClamped(dot);
    const float width = m_unk20c * leaf.m_fWidth;
    const float sine = std::fabs(GameSin(angle));
    const float span = !(sine > kHalf) ? width + width : width / sine;
    const float up = span * kHalf;
    const float down = span * kMinusHalf;
    const float leftY = ppc::fmadds(up, kAxisY.y, m_vStart.y);
    const float leftX = ppc::fmadds(up, kAxisY.x, m_vStart.x);
    const float leftZ = ppc::fmadds(up, kAxisY.z, m_vStart.z);
    const float rightZ = ppc::fmadds(kAxisY.z, down, m_vStart.z);
    const float rightX = ppc::fmadds(kAxisY.x, down, m_vStart.x);
    const float rightY = ppc::fmadds(kAxisY.y, down, m_vStart.y);
    {
        const CVector3& p = left[-1];
        const float ey = p.y - leftY;
        const float ex = p.x - leftX;
        const float ez = p.z - leftZ;
        texLeft = texLeft + Sqrtf(ppc::fmadds(ez, ez, ppc::fmadds(ex, ex, ey * ey))) / (width / m_unk8c);
    }
    {
        const CVector3& p = right[-1];
        const float ey = p.y - rightY;
        const float ex = p.x - rightX;
        const float ez = p.z - rightZ;
        texRight = texRight + Sqrtf(ppc::fmadds(ez, ez, ppc::fmadds(ex, ex, ey * ey))) / (width / m_unk8c);
    }
    // The cap fills the rest of the strip.
    for (uint32_t v = m_ui32NbStripVertices; v < m_ui32NbVertices; ++v) {
        left->z = leftZ;
        left->x = leftX;
        left->y = leftY;
        ++left;
        right->z = rightZ;
        right->x = rightX;
        right->y = rightY;
        ++right;
    }
    uvs[m_ui32NbStripVertices * 2] = texLeft;
    uvs[m_ui32NbStripVertices * 2 + 1] = kOne;
    uvs[(m_ui32NbStripVertices + m_ui32NbVertices) * 2] = texRight;
    uvs[(m_ui32NbStripVertices + m_ui32NbVertices) * 2 + 1] = kZero;
    m_ui32NbStripVertices = m_ui32NbStripVertices + 1;
    // The atomic's sphere: the middle of the node (its stored LTM) and the end point, radius 1000.
    RpAtomic* atomic = geometry->m_pRpAtomic;
    const RwV3d& node = FrameLtm(static_cast<CSGMovable*>(m_pNode)->m_pRwFrame)->pos;  // RwFrame +0x80
    const float ex = m_vEnd.x;
    const float ez = m_vEnd.z;
    const float ey = m_vEnd.y;
    if ((atomic->flags & 2u) != 0) {
        _rpAtomicResyncInterpolatedSphere(atomic);  // 0x0069bbe0 RW_UpdateAtomicMorphBoundingSphere
        atomic = geometry->m_pRpAtomic;
    }
    atomic->boundingSphere[0] = (ex + node.x) * kHalf;
    atomic->boundingSphere[1] = (ey + node.y) * kHalf;
    atomic->boundingSphere[2] = (ez + node.z) * kHalf;
    atomic->boundingSphere[3] = kCapRadius;
    atomic->flags &= 0xfffffffdu;
    atomic->privateFlags |= 1;
    geometry->UnlockGeometry();  // 0x0098fd70 TocBridge_CGeometry_UnlockGeometry_maybe
}

// 0x0057ec40 CKLightningBoltNodeFx_BuildBranchVertices_maybe
uint32_t CKLightningBoltNodeFx::BuildBranchVertices(uint32_t index, uint32_t previous, float* texLeft, float* texRight,
                                                    CVector3** left, CVector3** right, float** uvs) {
    const SSegment* seg = &m_segments.m_pBlock[index];
    if (seg->m_ui32NbChildren != 0) {
        for (uint32_t k = 0; k < m_segments.m_pBlock[index].m_ui32NbChildren; ++k) {
            previous = BuildBranchVertices(m_segments.m_pBlock[index].m_ui32FirstChild + k, previous, texLeft, texRight,
                                           left, right, uvs);
        }
        return previous;
    }
    const bool doubled = ((DataOf(this)->m_unk18 >> 5) & 1u) != 0;
    float* const uv = *uvs;
    const uint32_t other = m_ui32NbVertices;
    if (m_ui32NbStripVertices == 0) {
        // The first leaf: a pair across its own start, widened by its angle to the bolt.
        CVector3 p, d, u;  // sp+0xa4, +0x80, +0x8c
        ComputeBranchPoint(index, &p, &d, &u);
        float dx = d.x, dy = d.y, dz = d.z;
        float bx = m_vDirection.x, by = m_vDirection.y, bz = m_vDirection.z;
        float length = Length(dx, dy, dz);
        if (length != kZero) {
            const float k = kOne / length;
            dz = dz * k;
            dx = dx * k;
            dy = dy * k;
        }
        length = Length(bx, by, bz);
        if (length != kZero) {
            const float k = kOne / length;
            bz = bz * k;
            bx = bx * k;
            by = by * k;
        }
        const float dot = ppc::fmadds(dz, bz, ppc::fmadds(bx, dx, dy * by));
        const float a = AcosClamped(dot);
        const float width = m_unk20c * seg->m_fWidth;
        const float sine = std::fabs(GameSin(kHalfPi - a));
        const float span = !(sine > kHalf) ? width + width : width / sine;
        const float up = span * kHalf;
        const float down = span * kMinusHalf;
        CVector3* l = *left;
        l->z = ppc::fmadds(up, kAxisY.z, p.z);
        l->x = ppc::fmadds(up, kAxisY.x, p.x);
        l->y = ppc::fmadds(up, kAxisY.y, p.y);
        *left = l + 1;
        CVector3* r = *right;
        r->z = ppc::fmadds(kAxisY.z, down, p.z);
        r->x = ppc::fmadds(kAxisY.x, down, p.x);
        r->y = ppc::fmadds(kAxisY.y, down, p.y);
        *right = r + 1;
        if (doubled) {
            // The texture start on the outer side of the bend (the node's up against the leaf's direction).
            const float stretch = std::fabs(GameSin(a) * span);
            const float unit = width / m_unk8c;
            const float side = ppc::fmadds(d.z, m_vUp.z, ppc::fmadds(d.x, m_vUp.x, d.y * m_vUp.y));
            const float start = stretch / unit;
            if (side < kZero) {
                *texLeft = kZero;
                *texRight = start;
            } else {
                *texLeft = start;
                *texRight = kZero;
            }
        }
        uv[0] = *texLeft;
        uv[1] = kOne;
        uv[other * 2] = *texRight;
        uv[other * 2 + 1] = kZero;
        m_ui32NbStripVertices = m_ui32NbStripVertices + 1;
        return index;
    }
    if (m_ui32NbVertices - 1u <= m_ui32NbStripVertices) return previous;
    // A joint: the previous leaf's end against this leaf's start.
    CVector3 pp, pd, pu;  // sp+0x98, +0xa4, +0xb0
    CVector3 p, d, u;     // sp+0x80, +0x8c, +0x74
    ComputeBranchPoint(previous, &pp, &pd, &pu);
    ComputeBranchPoint(index, &p, &d, &u);
    float ny = -pd.y;
    float nx = -pd.x;
    float nz = -pd.z;
    float wCur = m_unk20c * seg->m_fWidth;                                // f23
    float dx = d.x, dy = d.y, dz = d.z;
    float wPrev = m_unk20c * m_segments.m_pBlock[previous].m_fWidth;     // f25
    float length = Length(nx, ny, nz);
    if (length != kZero) {
        const float k = kOne / length;
        nz = nz * k;
        nx = nx * k;
        ny = ny * k;
    }
    length = Length(dx, dy, dz);
    if (length != kZero) {
        const float k = kOne / length;
        dz = dz * k;
        dx = dx * k;
        dy = dy * k;
    }
    const float a = AcosClamped(ppc::fmadds(dz, nz, ppc::fmadds(nx, dx, dy * ny)));  // f14
    const float h = a * kHalf;                                                       // f30
    const float sinH = GameSin(h);                                                    // f31
    const float tanH = crt::Tanf(h);                                                  // f29, 0x00780a90
    // The joint's half widths: the average (bends, or widths alike) or the miter of the two widths.
    float numPrev;    // f25: the previous leaf's offset scale
    float numCur;     // f23
    float spanSum;    // f29
    float miterA;     // f30
    float miterB;     // f28
    auto average = [&](bool withSine) {
        const float avg = (wPrev + wCur) * kHalf;
        spanSum = avg + avg;
        miterB = kZero;
        numCur = avg;
        numPrev = avg;
        miterA = withSine ? avg / GameSin(h) : spanSum;
    };
    bool done = false;
    if (!doubled) {
        average(true);
        done = true;
    } else if (!(std::fabs(GameSin(a)) >= kSharpSine)) {
        // A sharp bend: the average unless the two widths differ by less than 10%.
        float num = wPrev;
        float den = wCur;
        if (wPrev > wCur) {
            num = wCur;
            den = wPrev;
        }
        if (!(std::fabs(kOne - num / den) <= kSameWidth)) {
            average(true);
            done = true;
        }
    }
    if (!done) {
        if (std::fabs(sinH) < kHalf || std::fabs(tanH) < kHalf) {
            average(false);
        } else {
            float num = wPrev;
            float den = wCur;
            if (!(wPrev <= wCur)) {
                num = wCur;
                den = wPrev;
            }
            if (std::fabs(kOne - num / den) < kSameWidth) {
                average(true);
            } else {
                spanSum = wPrev + wCur;
                const float sine1 = GameSin(h);
                const float sine2 = GameSin(h);
                miterA = spanSum / (sine1 + sine1);
                miterB = (wCur - wPrev) / ((sine2 + sine2) * crt::Tanf(h));
                numPrev = wPrev;
                numCur = wCur;
            }
        }
    }
    // 0x0057f094: the joint's span, at most the two widths' sum.
    const float miter = Sqrtf(crt::PowFast(miterA, kTwo) + crt::PowFast(miterB, kTwo));  // TocBridge_Math_PowFast_maybe
    float span = (spanSum + spanSum) * kHalf;
    if (!(miter > span)) span = miter;
    // The joint's axis: this leaf's direction scaled by numPrev / |d| less the previous one's by numCur / |pd|.
    const float kd = numPrev / Length(d.x, d.y, d.z);
    float bz = ppc::fmadds(kd, d.z, kNullVector.z);
    float bx = ppc::fmadds(kd, d.x, kNullVector.x);
    float by = ppc::fmadds(kd, d.y, kNullVector.y);
    const float kp = -numCur / Length(pd.x, pd.y, pd.z);
    by = ppc::fmadds(kp, pd.y, by);
    bx = ppc::fmadds(kp, pd.x, bx);
    bz = ppc::fmadds(kp, pd.z, bz);
    length = Length(bx, by, bz);
    if (length != kZero) {
        const float k = kOne / length;
        bz = bz * k;
        bx = bx * k;
        by = by * k;
    }
    if (bx == kNullVector.x && by == kNullVector.y && bz == kNullVector.z) {
        bx = pu.x;
        by = pu.y;
        bz = pu.z;
    }
    const float side = ppc::fmadds(bz, m_vUp.z, ppc::fmadds(bx, m_vUp.x, by * m_vUp.y));  // f15
    float leftScale;
    float rightSign;
    if (side < kZero) {
        leftScale = -span * kHalf;
        rightSign = kMinusOne;
    } else {
        leftScale = span * kHalf;
        rightSign = kOne;
    }
    const float lz = ppc::fmadds(leftScale, bz, p.z);
    const float lx = ppc::fmadds(leftScale, bx, p.x);
    const float ly = ppc::fmadds(leftScale, by, p.y);
    const float rightScale = (rightSign * -span) * kHalf;
    float texL = *texLeft;
    const CVector3& lp = (*left)[-1];
    const float rz = ppc::fmadds(rightScale, bz, p.z);
    const float rx = ppc::fmadds(rightScale, bx, p.x);
    const float ry = ppc::fmadds(rightScale, by, p.y);
    {
        const float ey = lp.y - ly;
        const float ex = lp.x - lx;
        const float ez = lp.z - lz;
        texL = texL + Sqrtf(ppc::fmadds(ez, ez, ppc::fmadds(ex, ex, ey * ey))) / (numPrev / m_unk8c);
        *texLeft = texL;
    }
    {
        float texR = *texRight;
        const CVector3& rp = (*right)[-1];
        const float ey = rp.y - ry;
        const float ex = rp.x - rx;
        const float ez = rp.z - rz;
        texR = texR + Sqrtf(ppc::fmadds(ez, ez, ppc::fmadds(ex, ex, ey * ey))) / (numPrev / m_unk8c);
        *texRight = texR;
    }
    auto pushPair = [&]() {
        CVector3* l = *left;
        l->x = lx;
        l->z = lz;
        l->y = ly;
        *left = l + 1;
        CVector3* r = *right;
        r->x = rx;
        r->z = rz;
        r->y = ry;
        *right = r + 1;
        const uint32_t n = m_ui32NbStripVertices;
        uv[n * 2] = *texLeft;
        uv[n * 2 + 1] = kOne;
        uv[(n + m_ui32NbVertices) * 2] = *texRight;
        uv[(n + m_ui32NbVertices) * 2 + 1] = kZero;
    };
    pushPair();
    if (doubled) {
        // 0x0057fb4c: the second pair of the joint at the same place, the texture moved on by the outer side's arc.
        float my = -pd.y;
        float mx = -pd.x;
        float mz = -pd.z;
        length = Length(mx, my, mz);
        if (length != kZero) {  // (compared with the integer 0 stored as a float)
            const float k = kOne / length;
            mz = mz * k;
            mx = mx * k;
            my = my * k;
        }
        length = Length(bx, by, bz);
        if (length != kZero) {
            const float k = kOne / length;
            bz = bz * k;
            bx = bx * k;
            by = by * k;
        }
        const float a2 = AcosClamped(ppc::fmadds(mz, bz, ppc::fmadds(bx, mx, by * my)));
        const float cos2 = GameCos(a2);
        const float ratio = m_unk8c;
        const float cos1 = GameCos(a - a2);
        const float unitCur = wCur / ratio;
        const float arc = (cos2 * span) / (numPrev / ratio) + (cos1 * span) / unitCur;
        if (side < kZero) {
            *texRight = arc + *texRight;
        } else {
            *texLeft = arc + *texLeft;
        }
        m_ui32NbStripVertices = m_ui32NbStripVertices + 1;
        pushPair();
    }
    m_ui32NbStripVertices = m_ui32NbStripVertices + 1;
    return index;
}

// 0x0057b230 CKLightningBoltNodeFx_UpdateVertexColors_maybe: the strip's two sides (vertex i and i + +0x20) get the
// data's colour at their place along the strip, the alpha scaled from the start to the end intensity unless both are 1.
void CKLightningBoltNodeFx::UpdateVertexColors() {
    CGeometry* geometry = static_cast<CGeometry*>(m_pNode->m_lGeometryList);
    RpGeometryLock(geometry->m_pRpAtomic->geometry, 8);  // 0x006a0e28 (prelit colours)
    const float one = 1.0f;  // TOC2 -0x7448
    RwRGBA* colors = geometry->m_pRpAtomic->geometry->preLitLum;
    const uint32_t count = m_ui32NbStripVertices;
    const float step = one / static_cast<float>(static_cast<double>(static_cast<uint32_t>(count - 1u)));
    for (uint32_t i = 0; i < count; ++i) {
        const float t = step * static_cast<float>(static_cast<double>(i));
        uint8_t c[4];
        DataOf(this)->EvaluateColor(m_fTime, t, c);  // 0x00577bd0
        const float start = m_fStartIntensity;
        if (start != one || m_fEndIntensity != one) {
            const float f = ppc::fmadds(t, m_fEndIntensity - start, start);
            c[3] = static_cast<uint8_t>(ppc::fctiwz(f * static_cast<float>(c[3])));
        }
        std::memcpy(&colors[i], c, 4);
        std::memcpy(&colors[i + m_ui32NbVertices], c, 4);
    }
    geometry->UnlockGeometry();  // 0x0098fd70 TocBridge_CGeometry_UnlockGeometry_maybe
}

// 0x00582470 CKLightningBoltNodeFx_Update
void CKLightningBoltNodeFx::Update(IKTime* frameClock) {
    const uint8_t flags = m_baFxData;
    bool checkLifetime = true;
    if (((flags >> 3) & 1u) != 0) {
        checkLifetime = (flags & 4u) != 0;
    } else if (((flags >> 2) & 1u) == 0) {
        return;
    }
    if (checkLifetime && m_fTime > m_fLifetime) {
        Stop();  // vt+0x6c
        return;
    }
    CKLightningBoltFxData* data = DataOf(this);
    if ((data->m_unk18 & 1u) != 0 && m_fTime >= data->m_unk1c) {
        Stop();
        return;
    }
    m_fTime = m_fTime + frameClock->m_afDeltaTime[0];
    SyncNodeToTarget();
    UpdateEndpoints();
    CSGMovable* node = static_cast<CSGMovable*>(m_pNode);
    {
        const RwV3d& p = FrameLtm(node->m_pRwFrame)->pos;  // RwFrame +0x80
        float dy = m_vEnd.y - p.y;
        float dx = m_vEnd.x - p.x;
        float dz = m_vEnd.z - p.z;
        const float length = std::sqrt(ppc::fmadds(dz, dz, ppc::fmadds(dx, dx, dy * dy)));
        if (length != kZero) {
            const float k = kOne / length;
            dz = dz * k;
            dx = dx * k;
            dy = dy * k;
            if (length > kZero) {
                const CVector3 at = {dx, dy, dz};
                if (node->SetOrientationFromAtUp(&at, &kAxisY) == 0) node->SetOrientationFromAtUp(&at, &kAxisZ);  // 0x000d0918
                const float dt = frameClock->m_afDeltaTime[0];
                const float roll = m_fRollAngle;
                const float speed = DataOf(this)->RandomValue6C();  // 0x00577548
                m_fRollAngle = roll + dt * speed / IntensityAt(this, kHalf);
                node->RotateInPlace(&node->m_pRwFrame->modelling.at.x, m_fRollAngle);  // 0x000d11b0
                UpdateEndpoints();
            }
        }
    }
    SSegment& root = m_segments.m_pBlock[0];
    SetPoint(root.m_afStart, kNullVector);
    SetPoint(root.m_afEnd, m_vStart);
    float dy = m_vStart.y - kNullVector.y;
    float dx = m_vStart.x - kNullVector.x;
    float dz = m_vStart.z - kNullVector.z;
    m_vDirection = {dx, dy, dz};
    const float length = std::sqrt(ppc::fmadds(dz, dz, ppc::fmadds(dx, dx, dy * dy)));
    if (length != kZero) {
        const float k = kOne / length;
        m_vDirection = {k * m_vDirection.x, k * m_vDirection.y, k * m_vDirection.z};
        if (length < kZero) m_vDirection = kAxisZ;  // never taken
    }
    CMatrix34 basis;
    if (Mat4_SetBasisFromAtUp(&basis, &m_vDirection, &m_vUp) == 0) {  // 0x0023fd30
        Mat4_SetBasisFromAtRight(&basis, &m_vDirection, &m_vRight);   // 0x0023fe58
    }
    m_vRight = basis.m_right;
    m_vUp = basis.m_up;
    UpdateFades(frameClock);
    UpdateBranchesRecursive(kZero, kOne, frameClock, 0);
    RebuildGeometry();
    UpdateVertexColors();
    UpdateImpactExplosions(frameClock);
    UpdateImpactSlots(frameClock);
    if (m_pEndParticles != nullptr) {
        SetOwnedParticleEffectPosition(static_cast<CKParticlesEffectNodeFx*>(m_pEndParticles), &m_vStart, this);  // 0x001cdce0
    }
    if (m_pSphere == nullptr) return;
    RwFrame* frame = m_pSphere->m_pRwFrame;
    frame->modelling.pos = {m_vEnd.x, m_vEnd.y, m_vEnd.z};
    frame->modelling.flags &= 0xfffdffffu;
    RwFrame_MarkDirty(frame);  // 0x00010698
}

// 0x0057a890 CKLightningBoltNodeFx_SetStartSmoothParams_maybe
void CKLightningBoltNodeFx::SetStartSmoothParams(float target, float timer, float rate0, float rate1, float speed,
                                                 float rate2, const IKSerializable* owner) {
    if ((m_baFxData & 2u) == 0 || m_pOwner != owner) return;
    m_afStartFade[5] = target;
    m_afStartFade[4] = speed;
    m_afStartFade[2] = rate2;
    m_afStartFade[0] = rate0;
    m_afStartFade[1] = rate1;
    m_fStartFadeTimer = timer;
}

// 0x0057a8d0 CKLightningBoltNodeFx_SetEndSmoothParams_maybe
void CKLightningBoltNodeFx::SetEndSmoothParams(float target, float timer, float rate0, float rate1, float speed,
                                               float rate2, const IKSerializable* owner) {
    if ((m_baFxData & 2u) == 0 || m_pOwner != owner) return;
    m_afEndFade[5] = target;
    m_afEndFade[4] = speed;
    m_afEndFade[2] = rate2;
    m_afEndFade[0] = rate0;
    m_afEndFade[1] = rate1;
    m_fEndFadeTimer = timer;
}

// 0x0057a9d0 CKLightningBoltNodeFx_SetTargetPoint_maybe
void CKLightningBoltNodeFx::SetTargetPoint(const CVector3* point, const IKSerializable* owner) {
    if ((m_baFxData & 2u) == 0 || m_pOwner != owner) return;
    m_vSourceOffset = {point->x, point->y, point->z};
}

// 0x0057aab0 CKLightningBoltNodeFx_SetField1D8_maybe
void CKLightningBoltNodeFx::SetDamage(IKSerializable* damage, const IKSerializable* owner) {
    if ((m_baFxData & 2u) == 0 || m_pOwner != owner) return;
    m_pDamage = damage;
}

// 0x0057aa10 CKLightningBoltNodeFx_SetField1E0_maybe
void CKLightningBoltNodeFx::SetDamageOwner(IKSerializable* damageOwner, const IKSerializable* owner) {
    if ((m_baFxData & 2u) == 0 || m_pOwner != owner) return;
    m_pDamageOwner = damageOwner;
}

// 0x0057aa60 CKLightningBoltNodeFx_SetField1E4_maybe
void CKLightningBoltNodeFx::SetDamageCategory(uint8_t category, const IKSerializable* owner) {
    if ((m_baFxData & 2u) == 0 || m_pOwner != owner) return;
    m_ui8DamageCategory = category;
}

// 0x0057aa88 CKLightningBoltNodeFx_SetField1E6_maybe
void CKLightningBoltNodeFx::SetDamageFlags(uint16_t flags, const IKSerializable* owner) {
    if ((m_baFxData & 2u) == 0 || m_pOwner != owner) return;
    m_ui16DamageFlags = flags;
}

// 0x0057aa38 CKLightningBoltNodeFx_SetField1E8_maybe
void CKLightningBoltNodeFx::SetUnk1e8(IKSerializable* value, const IKSerializable* owner) {
    if ((m_baFxData & 2u) == 0 || m_pOwner != owner) return;
    m_unk1e8 = value;
}

// 0x005829a0 CKLightningBoltNodeFx_RestartForOwner_maybe
void CKLightningBoltNodeFx::RestartForOwner(float lifetime, const IKSerializable* owner) {
    if ((m_baFxData & 2u) == 0 || m_pOwner != owner) return;
    SetActiveForOwner(m_pOwner, 1);  // 0x00581380
    m_fLifetime = lifetime;
    m_baFxData = static_cast<uint8_t>((m_baFxData & 0xf8u) | (m_baFxData & 3u) | 4u);
}

// 0x0057c430 CKLightningBoltNodeFx_SetNodePositionIfOwner_maybe
void CKLightningBoltNodeFx::SetNodePosition(const CVector3* point, const IKSerializable* owner) {
    if ((m_baFxData & 2u) == 0 || m_pOwner != owner) return;
    RwFrame* frame = m_pNode->m_pRwFrame;
    frame->modelling.pos.z = point->z;
    frame->modelling.pos.x = point->x;
    frame->modelling.pos.y = point->y;
    frame->modelling.flags &= 0xfffdffffu;
    RwFrame_MarkDirty(frame);
}

// 0x0057b5f0 CKLightningBoltNodeFx_RecursiveRegistration
void CKLightningBoltNodeFx::RecursiveRegistration(int32_t type) {
    g_pEngine->m_pSavingManager->RegisterSerializableObject(this, nullptr);  // vt+0x24
    IKNodeFx::RecursiveRegistration(type);  // 0x001d88c0 (through its TOC bridge)
}

// 0x0057b780 CKLightningBoltNodeFx_StopIfLinkedTo. The nodes' GetSectorIndex is their vt+0x6c.
void CKLightningBoltNodeFx::StopIfLinkedTo(int32_t sector) {
    if ((m_baFxData & 1) != 0 || sector == 0) return;
    const CKLightningBoltFxData* data = reinterpret_cast<const CKLightningBoltFxData*>(m_pFxData);
    if (data == nullptr || (data->m_unk18 & 4) == 0) return;
    auto in = [sector](IKSerializable* node) {
        return node != nullptr && sector == static_cast<int32_t>(static_cast<CSGLeaf*>(node)->GetSectorIndex());
    };
    auto hotSpotNode = [](IKSerializable* hotSpot) -> IKSerializable* {
        return hotSpot != nullptr ? static_cast<CSGHotSpot*>(hotSpot)->m_pParent : nullptr;
    };
    if (in(data->m_pSourceNode) || in(hotSpotNode(data->m_pSourceHotSpot)) || in(data->m_pTargetNode) ||
        in(hotSpotNode(data->m_pTargetHotSpot))) {
        Stop();  // vt+0x6c
    }
}

// 0x005823f0 CKLightningBoltNodeFx_UpdateImpacts_maybe
void CKLightningBoltNodeFx::UpdateImpacts(IKTime* frameClock) {
    UpdateImpactExplosions(frameClock);
    UpdateImpactSlots(frameClock);
    if (m_pEndParticles != nullptr) {
        SetOwnedParticleEffectPosition(static_cast<CKParticlesEffectNodeFx*>(m_pEndParticles), &m_vStart, this);  // 0x001cdce0
    }
}

namespace {

// 0x0057db68 Vec3_AngleBetweenNormalizing_maybe: both vectors normalised in place (unless 0 long; Math_Sqrtf of
// y^2 + x^2 + z^2), then Math_Acosf of their dot product kept in [-1, 1] (a NaN passes through). No caller found.
[[maybe_unused]] float Vec3_AngleBetweenNormalizing(CVector3* a, CVector3* b) {
    auto normalise = [](CVector3* v) {
        const float length = std::sqrt(ppc::fmadds(v->z, v->z, ppc::fmadds(v->x, v->x, v->y * v->y)));
        if (length == 0.0f) return;
        const float inverse = 1.0f / length;
        const float z = inverse * v->z;
        const float x = inverse * v->x;
        const float y = inverse * v->y;
        v->z = z;
        v->x = x;
        v->y = y;
    };
    normalise(a);
    normalise(b);
    float dot = ppc::fmadds(b->z, a->z, ppc::fmadds(b->x, a->x, b->y * a->y));
    if (dot <= -1.0f) return crt::Acosf(-1.0f);  // cror lt|eq
    if (dot >= 1.0f) dot = 1.0f;                 // cror gt|eq
    return crt::Acosf(dot);
}

}  // namespace
