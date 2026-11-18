// CCloudsNodeFx.cpp - reconstructed original translation unit 0xd8078-0xda260 (GAME_TOC1, main_toc1), 21 functions, 19 live.
// Primary class: CCloudsNodeFx  key 0x84b  category SceneNode  size 0x6678  vtable 0xb18910
// Other owners: CFogBoxNodeFx (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0xd8078  CCloudsNodeFx_Delete
//   [ ] 0xd80c8  CCloudsNodeFx_ReduceCloudCount_maybe  [dead]
//   [ ] 0xd80f0  RegisterCCloudsNodeFxClass
//   [ ] 0xd8168  _GLOBAL__I_d8168
//   [x] 0xd8178  CCloudsNodeFx_InitCloud_maybe  (port-all P19, for CKHkWeatherCenter)
//   [x] 0xd8478  CCloudsNodeFx_PostLoad  (INodeFx's PostLoad, inherited)
//   [ ] 0xd84a0  CCloudsNodeFx_Save
//   [x] 0xd84c8  CCloudsNodeFx_RecursiveRegistration  (INodeFx's (returns 1, registers nothing): CSGLeaf's)
//   [x] 0xd84f0  CCloudsNodeFx_Destroy  (CNode's Destroy, inherited)
//   [x] 0xd8518  CCloudsNodeFx_DeleteArray
//   [x] 0xd85b8  CCloudsNodeFx_CreateArray
//   [x] 0xd8688  CCloudsNodeFx_BeginParamTransition_maybe  (port-final F05; its callers 0x5ad050 / 0x5ad2b8 are dead)
//   [x] 0xd8728  CCloudsNodeFx_SetTargetParams_maybe  (port-all P19, for CKHkWeatherCenter)
//   [x] 0xd8818  CCloudsNodeFx_ApplyPendingParams_maybe  (port-all P19, for CKHkWeatherCenter)
//   [x] 0xd8968  CCloudsNodeFx_Create
//   [x] 0xd89c8  CCloudsNodeFx_Load
//   [x] 0xd8d90  CCloudsNodeFx_WritePTankVertices_maybe  (port-last Z8)
//   [x] 0xd94e0  CCloudsNodeFx_UpdateClouds_maybe  (port-last Z8)
//   [x] 0xda088  CCloudsNodeFx_vf58  (port-last Z8: UpdateAndExtract)
//   [x] 0xda1d0  CFogBoxNodeFx_Delete  (DOTD_DECLARE_FACTORIES(CFogBoxNodeFx))
//   [ ] 0xda220  FUN_000da220  [dead]
//
//   [ ] 0x9a4ca0  CCloudsNodeFx_IsKindOfClass  [inline]
//   [ ] 0x9a4d00  CCloudsNodeFx_GetClassType  [inline]
//   [ ] 0x9a4d08  CCloudsNodeFx_GetClassID  [inline]
//   [ ] 0x9a4d10  CCloudsNodeFx_Destructor  [inline]
//   [ ] 0x9a4d50  CCloudsNodeFx_DeletingDestructor  [inline]
#include "k2000/scenegraph/CCloudsNodeFx.h"

#include <cstring>

#include "Renderware/rpworld/RpAtomic.h"
#include "Renderware/rpworld/RpGeometry.h"
#include "Renderware/rwcore/RwCamera.h"
#include "crt/ppc_ops.h"
#include "crt/xsinf.h"
#include "k2000/cameras/CameraContext.h"
#include "k2000/geometry/CGeometry.h"
#include "k2000/io/IKFile.h"
#include "k2000/misc/ClassRegistry.h"
#include "k2000/scenegraph/CSGMovable.h"
#include "k2000/system/IKTime.h"

// 0x000d89c8 CCloudsNodeFx_Load
int32_t CCloudsNodeFx::Load(IKFile* file, int32_t type) {
    INodeFx::Load(file, type);  // 0xeccd8
    m_ba8Infos = 0;
    m_pCloudTank = nullptr;
    ReadF32LE(file, &m_fFarLimit);
    ReadF32LE(file, &m_fShowSpeed);
    SCloudsWeatherPreset& preset = m_asWeather[1];
    ReadU32LEWords(file, reinterpret_cast<uint32_t*>(&preset.m_fMedHeight), 8);           // one 0x20 read
    ReadU32LEWords(file, &preset.m_ui32ExternNbClusters, 3);                               // one 0xc read
    ReadRaw(file, preset.m_acColor, 8);                                                    // not swapped
    if (type == K_LEVEL_PLATEFORMS) IKFile_ReadRef(file, &m_pCloudTank);
    m_asWeather[0] = preset;  // the original copies word by word, first and last presets interleaved
    m_asWeather[2] = preset;
    m_fSpeedInterpolation = 0.0f;
    m_fStateInterpolation = 1.0f;  // TOC -0x50e4
    return 1;
}

// ==== port-all P19 (for CKHkWeatherCenter): InitCloud, SetTargetParams, ApplyPendingParams ===========================

namespace {
// rand() & 0xffff as a float (fcfid, frsp).
float RandU16() { return static_cast<float>(static_cast<double>(static_cast<uint32_t>(Rand_Int()) & 0xffffu)); }
}  // namespace

// 0x000d8178 CCloudsNodeFx_InitCloud_maybe
void CCloudsNodeFx::InitCloud(uint32_t index, int32_t atFarEdge, int32_t visible) {
    if (index > 99) return;
    SCloudsClusterData& cluster = m_asClusters[index];
    const SCloudsWeatherPreset& weather = m_asWeather[0];
    const uint32_t r = static_cast<uint32_t>(Rand_Int()) & 0xffffu;
    const uint32_t delta = weather.m_ui32DeltaNbCloudsPerCluster;
    const int32_t count =
        static_cast<int32_t>((((r * (delta << 1)) >> 16) & 0xffffu) - delta + weather.m_ui32MedNbCloudsPerCluster);
    uint32_t clouds;
    if (count > 10) {
        clouds = 10;
    } else {
        clouds = count > 0 ? static_cast<uint32_t>(count) : 1u;
    }
    cluster.m_ui32NbClouds = clouds;
    const float one = 1.0f;                 // TOC -0x50e4
    const float scale = -3.05180438e-05f;   // TOC -0x50e0 (0xb8000080, -2 / 65535)
    cluster.m_fUnk0c = visible != 0 ? one : 0.0f;
    if (atFarEdge != 0) {
        cluster.m_afPos[0] = -m_fFarLimit;
    } else {
        cluster.m_afPos[0] = ppc::fmadds(RandU16(), scale, one) * m_fFarLimit;
    }
    cluster.m_afPos[1] = ppc::fmadds(RandU16(), scale, one) * weather.m_fDeltaHeight;
    cluster.m_afPos[2] = ppc::fmadds(RandU16(), scale, one) * m_fFarLimit;
    if (cluster.m_ui32NbClouds == 0) return;
    const float half = 0.5f;  // TOC -0x50dc
    uint32_t i = 0;
    do {
        SCloudData_maybe& cloud = cluster.m_asClouds[i];
        ++i;
        cloud.m_fUnk0c = ppc::fmadds(RandU16(), scale, one);
        cloud.m_afUnk00[0] = ppc::fmadds(RandU16(), scale, one);
        cloud.m_afUnk00[1] = ppc::fmadds(RandU16(), scale, one);
        cloud.m_afUnk00[2] = ppc::fmadds(RandU16(), scale, one);
        cloud.m_fUnk10 = static_cast<float>((static_cast<uint32_t>(Rand_Int()) >> 15) & 1u) * half;
        cloud.m_fUnk14 = static_cast<float>((static_cast<uint32_t>(Rand_Int()) >> 15) & 1u) * half;
    } while (i < cluster.m_ui32NbClouds);
}

// 0x000d8728 CCloudsNodeFx_SetTargetParams_maybe (word copies of the 13 words, the pending preset first)
void CCloudsNodeFx::SetTargetParams(const SCloudsWeatherPreset* preset) {
    m_fStateInterpolation = 1.0f;
    m_asWeather[1] = *preset;
    m_asWeather[0] = *preset;
}

// 0x000d8818 CCloudsNodeFx_ApplyPendingParams_maybe
void CCloudsNodeFx::ApplyPendingParams(uint8_t shown) {
    m_asWeather[0] = m_asWeather[1];
    const uint32_t clusters = m_asWeather[0].m_ui32ExternNbClusters;
    m_fStateInterpolation = 1.0f;
    m_fSpeedInterpolation = 0.0f;
    m_ui32NbClusters = clusters;
    m_ui32NbActiveClusters = clusters;
    for (uint32_t i = 0; i < m_ui32NbActiveClusters; ++i) InitCloud(i, 0, 1);
    m_ba8Infos = static_cast<uint8_t>((m_ba8Infos & 0xfeu) | shown);
    m_sgProperties = (m_sgProperties & 0xfffffffbu) | (static_cast<uint32_t>(shown ^ 1u) << 2);
}

// 0x000d8688 CCloudsNodeFx_BeginParamTransition_maybe (C2.8 port-final F05). Its only callers are CKHkWeatherCenter's
// dead PushPreset_maybe 0x5ad050 / RemovePreset_maybe 0x5ad2b8 (through TocBridge 0x9905bc): the transition toward
// `preset` restarts from where the last one stood (1 - the interpolation, not below 0; blt: an unordered value is kept),
// at 1 / `duration` per second (100 below 0.01 s; bge: an unordered duration takes 1 / duration), and the target preset
// (m_asWeather[2]) takes every field of `preset` but the two sizes (+0x08 / +0x0c are not copied).
void CCloudsNodeFx::BeginParamTransition(const SCloudsWeatherPreset* preset, float duration) {
    float state = 1.0f - m_fStateInterpolation;  // TOC1 -0x50e4
    if (state < 0.0f) state = 0.0f;              // TOC1 -0x50c8
    m_fStateInterpolation = state;
    m_fSpeedInterpolation = !(duration < 0.01f) ? 1.0f / duration : 100.0f;  // TOC1 -0x50d0, -0x50cc
    SCloudsWeatherPreset& target = m_asWeather[2];
    std::memcpy(target.m_acColor, preset->m_acColor, sizeof(target.m_acColor));  // two word copies
    target.m_ui32MedNbCloudsPerCluster = preset->m_ui32MedNbCloudsPerCluster;
    target.m_fClusterLateralSpread = preset->m_fClusterLateralSpread;
    target.m_fClusterVerticalSpread = preset->m_fClusterVerticalSpread;
    target.m_fDeltaHeight = preset->m_fDeltaHeight;
    target.m_fMedHeight = preset->m_fMedHeight;
    target.m_fWindDir = preset->m_fWindDir;
    target.m_fWindSpeed = preset->m_fWindSpeed;
    target.m_ui32DeltaNbCloudsPerCluster = preset->m_ui32DeltaNbCloudsPerCluster;
    target.m_ui32ExternNbClusters = preset->m_ui32ExternNbClusters;
}

// ==== port-last Z8: the cloud update (vf58, UpdateClouds, WritePTankVertices) =======================================

namespace {
const float kPi = 3.14159274f;  // TOC1 -0x5090 (0x40490fdb)
const float kByteMax = 255.0f;  // TOC1 -0x5094

bool SignBit(float x) {
    uint32_t bits;
    std::memcpy(&bits, &x, 4);
    return (bits >> 31) != 0;
}
// The inlined cosf / sinf (TOC1 -0x50bc 4/pi, -0x50b8..-0x50ac / -0x50a8..-0x509c the polynomials: crt/xsinf's
// constants, compared by bits); a negative argument (sign bit, stfs / lwz / cmpwi) goes to the library's 0x9a11d8 cosf
// with -x, or -(0x9a1390 sinf of -x).
float CosOf(float x) { return SignBit(x) ? crt::LibCosf(-x) : crt::InlineCosf(x); }
float SinOf(float x) { return SignBit(x) ? -crt::LibSinf(-x) : crt::InlineSinf(x); }

// A colour channel: below 0 (blt) 0, above 255 (bgt) 0xff, else fctiwz's low byte (an unordered value: 0x80000000's).
uint8_t ClampToByte(float v) {
    if (v < 0.0f) return static_cast<uint8_t>(ppc::fctiwz(0.0f));
    if (v > kByteMax) return 0xff;
    return static_cast<uint8_t>(ppc::fctiwz(v));
}
// A blended preset word: fctidz of the fused blend, its low word stored (stw).
uint32_t BlendWord(float w, float w1, uint32_t current, uint32_t target) {
    const float scaledTarget = w * static_cast<float>(target);
    return static_cast<uint32_t>(ppc::fctidz(ppc::fmadds(w1, static_cast<float>(current), scaledTarget)));
}
}  // namespace

// 0x000da088 CCloudsNodeFx_vf58
void CCloudsNodeFx::UpdateAndExtract(float /*maxDistanceSquared*/, RenderQueue** stages, IKTime* frameClock,
                                     RwCamera* camera, int32_t /*distanceCull*/) {
    if ((m_sgProperties & 4) != 0) return;
    if (frameClock->m_eCurrentState != 0) return;
    if ((m_ba8Infos & 1) == 0) return;
    UpdateClouds(frameClock);
    CParticleGeometry* tank = static_cast<CParticleGeometry*>(m_pCloudTank);
    RpAtomic* atomic = tank->m_pRpAtomic;
    if ((atomic->flags & 2) != 0) {
        _rpAtomicResyncInterpolatedSphere(atomic);  // BridgeRwUpdateAtomicMorphBoundingSphere
        atomic = tank->m_pRpAtomic;
    }
    atomic->boundingSphere[0] = 0.0f;  // the null vector 0x00c50d64 (TOC1 -0x5088)
    atomic->boundingSphere[1] = 0.0f;
    atomic->boundingSphere[2] = 0.0f;
    atomic->boundingSphere[3] = 1e10f;  // TOC1 -0x5084 (0x501502f9)
    tank->m_pRpAtomic->flags &= 0xfffffffdu;
    tank->m_pRpAtomic->privateFlags |= 1;
    CullAndEnqueueGeometry(stages, frameClock, camera);  // vt+0x84 (CNode's 0xcc460); its result is not used
}

// 0x000d94e0 CCloudsNodeFx_UpdateClouds_maybe
void CCloudsNodeFx::UpdateClouds(IKTime* frameClock) {
    SCloudsWeatherPreset& current = m_asWeather[0];
    const SCloudsWeatherPreset& target = m_asWeather[2];
    const float one = 1.0f;  // TOC1 -0x50e4
    const float oldState = m_fStateInterpolation;
    if (oldState < one) {
        // The transition toward the target preset.
        const float state = ppc::fmadds(m_fSpeedInterpolation, frameClock->m_afDeltaTime[0], oldState);
        m_fStateInterpolation = state;
        const float oldMedSize = current.m_fMedSize;
        if (!(state >= one)) {  // cror gt|eq, bne: an unordered state blends
            const float cosNew = CosOf(state * kPi);
            const float cosOld = CosOf(oldState * kPi);
            const float half = 0.5f;  // TOC1 -0x50dc
            const float done = (one - cosOld) * half;
            const float w = ppc::fmsubs(one - cosNew, half, done) / (one - done);
            const float w1 = one - w;
            current.m_fMedHeight = ppc::fmadds(w, target.m_fMedHeight, w1 * current.m_fMedHeight);
            current.m_fDeltaHeight = ppc::fmadds(w, target.m_fDeltaHeight, w1 * current.m_fDeltaHeight);
            current.m_fMedSize = ppc::fmadds(w, target.m_fMedSize, w1 * current.m_fMedSize);
            current.m_fDeltaSize = ppc::fmadds(w, target.m_fDeltaSize, w1 * current.m_fDeltaSize);
            current.m_fWindSpeed = ppc::fmadds(w, target.m_fWindSpeed, w1 * current.m_fWindSpeed);
            current.m_fClusterLateralSpread =
                ppc::fmadds(w, target.m_fClusterLateralSpread, w1 * current.m_fClusterLateralSpread);
            current.m_fClusterVerticalSpread =
                ppc::fmadds(w, target.m_fClusterVerticalSpread, w1 * current.m_fClusterVerticalSpread);
            current.m_fWindDir = ppc::fmadds(w, target.m_fWindDir, w1 * current.m_fWindDir);
            const uint32_t nbClusters =
                BlendWord(w, w1, current.m_ui32ExternNbClusters, target.m_ui32ExternNbClusters);
            const uint32_t medClouds =
                BlendWord(w, w1, current.m_ui32MedNbCloudsPerCluster, target.m_ui32MedNbCloudsPerCluster);
            const uint32_t deltaClouds =
                BlendWord(w, w1, current.m_ui32DeltaNbCloudsPerCluster, target.m_ui32DeltaNbCloudsPerCluster);
            current.m_ui32ExternNbClusters = nbClusters;
            current.m_ui32MedNbCloudsPerCluster = medClouds;
            current.m_ui32DeltaNbCloudsPerCluster = deltaClouds;
            for (int32_t c = 0; c < 2; ++c) {
                for (int32_t k = 0; k < 4; ++k) {
                    const float cur = w1 * static_cast<float>(current.m_acColor[c][k]);
                    current.m_acColor[c][k] =
                        ClampToByte(ppc::fmadds(w, static_cast<float>(target.m_acColor[c][k]), cur));
                }
            }
        } else {
            m_fStateInterpolation = one;
            current = target;  // the 13 words copied
        }
        // Every cluster's clouds (all m_ui32NbClusters) follow the change of the medium size: +0x0c of each cloud, the
        // draw WritePTankVertices scales by the delta size, gets the change added unscaled (as the original does).
        const float sizeChange = current.m_fMedSize - oldMedSize;
        uint32_t clusters = m_ui32NbClusters;
        for (uint32_t i = 0; i < clusters; ++i) {
            SCloudsClusterData& cluster = m_asClusters[i];
            if (cluster.m_ui32NbClouds == 0) continue;
            uint32_t j = 0;
            do {
                SCloudData_maybe& cloud = cluster.m_asClouds[j];
                ++j;
                cloud.m_fUnk0c = sizeChange + cloud.m_fUnk0c;
            } while (cluster.m_ui32NbClouds > j);
            clusters = m_ui32NbClusters;
        }
    }

    // The active cluster count follows the current preset; new clusters are drawn hidden (InitCloud(i, 0, 0)).
    const uint32_t wanted = current.m_ui32ExternNbClusters;
    if (wanted > m_ui32NbActiveClusters) {
        uint32_t i = m_ui32NbClusters;
        if (wanted > i) {
            do {
                InitCloud(i, 0, 0);  // rand draws
                ++i;
            } while (current.m_ui32ExternNbClusters > i);
            const uint32_t now = current.m_ui32ExternNbClusters;
            m_ui32NbActiveClusters = now;
            m_ui32NbClusters = now;
        } else {
            m_ui32NbActiveClusters = wanted;
        }
    } else if (wanted < m_ui32NbActiveClusters) {
        m_ui32NbActiveClusters = wanted;
    }
    const float dt = frameClock->m_afDeltaTime[0];
    const float drift = dt * current.m_fWindSpeed;                             // f29
    const float fade = dt * m_fShowSpeed;                                      // f30
    const float fadeOutX = m_fFarLimit - current.m_fWindSpeed / m_fShowSpeed;  // f28
    uint32_t total = 0;                      // r29: the particles to draw
    uint32_t i = 0;                          // r10
    uint32_t keep = m_ui32NbActiveClusters;  // r8
    if (keep != 0) {
        // The active clusters drift; from fadeOutX on they fade out and come back at the far edge, else they fade in.
        uint32_t n = 0;
        do {
            SCloudsClusterData& cluster = m_asClusters[n];
            const float x = drift + cluster.m_afPos[0];
            cluster.m_afPos[0] = x;
            if (fadeOutX <= x) {
                const float f = cluster.m_fUnk0c - fade;
                bool redraw;
                if (f < 0.0f) {
                    cluster.m_fUnk0c = 0.0f;  // a word 0
                    redraw = true;
                } else {
                    cluster.m_fUnk0c = f;
                    redraw = f == 0.0f;
                }
                if (redraw) {
                    const float past = cluster.m_afPos[0] - m_fFarLimit;
                    InitCloud(n, 1, 0);  // rand draws; x becomes -far
                    cluster.m_afPos[0] = past + cluster.m_afPos[0];
                }
            } else {
                float f = fade + cluster.m_fUnk0c;
                if (!(f < one)) f = one;  // blt: an unordered value becomes 1
                cluster.m_fUnk0c = f;
            }
            ++n;
            keep = m_ui32NbActiveClusters;
            total += cluster.m_ui32NbClouds;
        } while (m_ui32NbActiveClusters > n);
        i = keep;
    }
    // The clusters past the active count drift and fade out; the count shrinks to the last one still visible.
    uint32_t clusters = m_ui32NbClusters;
    while (clusters > i) {
        SCloudsClusterData& cluster = m_asClusters[i];
        const float f = cluster.m_fUnk0c - fade;
        cluster.m_afPos[0] = drift + cluster.m_afPos[0];
        if (!(f < 0.0f)) {  // bge
            cluster.m_fUnk0c = f;
            ++i;
            if (f > 0.0f) keep = i;  // ble: an unordered fade does not keep it
        } else {
            cluster.m_fUnk0c = 0.0f;  // a word 0
            ++i;
        }
        clusters = m_ui32NbClusters;
        total += cluster.m_ui32NbClouds;
    }
    if (clusters > keep) {
        for (uint32_t k = keep; k < clusters; ++k) total -= m_asClusters[k].m_ui32NbClouds;
        m_ui32NbClusters = keep;
    }
    // The atomic's PTank plugin (the offset 0x00cf079c, TOC1 -0x508c).
    RpPTankData* ptank = static_cast<CParticleGeometry*>(m_pCloudTank)->m_pRpAtomic->ptank;
    ptank->flags40 |= 0x800000u;  // the particle count changed
    ptank->numPrt = total;
    WritePTankVertices();
}

// 0x000d8d90 CCloudsNodeFx_WritePTankVertices_maybe. The arrays are written at the PS3 strides (position 16, size 8,
// 2 tex coords 16, colour 4); the lock's stride is not read. (Guards ours: a missing array, or more clouds than the
// tank holds, would make the original write through null / past the arrays; nothing is written there.)
void CCloudsNodeFx::WritePTankVertices() {
    const SCloudsWeatherPreset& weather = m_asWeather[0];
    // engine +0x08 +0x2c +0x04 +0x40: the main camera's frame's modelling position (not the LTM).
    const RwV3d& camera = static_cast<CSGMovable*>(Engine_GetCameraContext()->m_pCamera)->m_pRwFrame->modelling.pos;
    const float windDir = weather.m_fWindDir;
    const float camX = camera.x;
    const float camY = camera.y + weather.m_fMedHeight;
    const float camZ = camera.z;
    const float cosDir = CosOf(windDir);
    const float sinDir = SinOf(windDir);
    CParticleGeometry* tank = static_cast<CParticleGeometry*>(m_pCloudTank);
    const uint32_t capacity = tank->m_pRpAtomic->ptank->maxParticles;
    RpPTankLockStruct lock = {nullptr, 0};

    // Positions: the cluster turned by the wind direction around the camera, the cloud's offset by the spreads.
    uint8_t* out = RpPTankAtomicLock(tank->m_pRpAtomic, &lock, 1, 0x40000000) != 0 ? lock.data : nullptr;  // POSITION
    uint32_t written = 0;
    for (uint32_t i = 0; i < m_ui32NbClusters; ++i) {
        const SCloudsClusterData& cluster = m_asClusters[i];
        const float x = cluster.m_afPos[0];
        const float z = cluster.m_afPos[2];
        const float y = camY + cluster.m_afPos[1];
        const float rz = camZ + ppc::fmsubs(cosDir, x, sinDir * z);
        const float rx = camX + ppc::fmadds(sinDir, x, cosDir * z);
        for (uint32_t j = 0; j < cluster.m_ui32NbClouds; ++j, ++written) {
            if (out == nullptr || written >= capacity) continue;
            const SCloudData_maybe& cloud = cluster.m_asClouds[j];
            float* p = reinterpret_cast<float*>(out + written * 0x10);
            p[0] = ppc::fmadds(cloud.m_afUnk00[0], weather.m_fClusterLateralSpread, rx);
            p[1] = ppc::fmadds(cloud.m_afUnk00[1], weather.m_fClusterVerticalSpread, y);
            p[2] = ppc::fmadds(cloud.m_afUnk00[2], weather.m_fClusterLateralSpread, rz);
        }
    }

    // Sizes: square, the medium size plus the cloud's draw times the delta size.
    out = RpPTankAtomicLock(tank->m_pRpAtomic, &lock, 4, 0x40000000) != 0 ? lock.data : nullptr;  // SIZE
    written = 0;
    for (uint32_t i = 0; i < m_ui32NbClusters; ++i) {
        const SCloudsClusterData& cluster = m_asClusters[i];
        for (uint32_t j = 0; j < cluster.m_ui32NbClouds; ++j, ++written) {
            if (out == nullptr || written >= capacity) continue;
            const float size = ppc::fmadds(cluster.m_asClouds[j].m_fUnk0c, weather.m_fDeltaSize, weather.m_fMedSize);
            float* p = reinterpret_cast<float*>(out + written * 8);
            p[1] = size;
            p[0] = size;
        }
    }

    // Tex coords: one quarter of the texture (the two 0 / 0.5 draws are its corner).
    out = RpPTankAtomicLock(tank->m_pRpAtomic, &lock, 0x80, 0x40000000) != 0 ? lock.data : nullptr;  // VTX2TEXCOORDS
    written = 0;
    const float half = 0.5f;  // TOC1 -0x50dc
    for (uint32_t i = 0; i < m_ui32NbClusters; ++i) {
        const SCloudsClusterData& cluster = m_asClusters[i];
        for (uint32_t j = 0; j < cluster.m_ui32NbClouds; ++j, ++written) {
            if (out == nullptr || written >= capacity) continue;
            const SCloudData_maybe& cloud = cluster.m_asClouds[j];
            float* p = reinterpret_cast<float*>(out + written * 0x10);
            p[0] = cloud.m_fUnk10;
            p[1] = cloud.m_fUnk14;
            p[2] = cloud.m_fUnk10 + half;
            p[3] = cloud.m_fUnk14 + half;
        }
    }

    // Colours: the two preset colours blended by the cluster's x across [-far, far] (colour 0 at +far), the alpha
    // times the cluster's fade; one word for every cloud of the cluster.
    out = RpPTankAtomicLock(tank->m_pRpAtomic, &lock, 2, 0x40000000) != 0 ? lock.data : nullptr;  // COLOR
    written = 0;
    const float one = 1.0f;  // TOC1 -0x50e4
    const float invWidth = one / (m_fFarLimit + m_fFarLimit);
    for (uint32_t i = 0; i < m_ui32NbClusters; ++i) {
        const SCloudsClusterData& cluster = m_asClusters[i];
        const float t = invWidth * (cluster.m_afPos[0] + m_fFarLimit);
        const float t1 = one - t;
        uint8_t color[4];
        for (int32_t k = 0; k < 3; ++k) {
            const float other = t1 * static_cast<float>(weather.m_acColor[1][k]);
            color[k] = ClampToByte(ppc::fmadds(t, static_cast<float>(weather.m_acColor[0][k]), other));
        }
        float alpha = ppc::fmadds(t, static_cast<float>(weather.m_acColor[0][3]),
                                  t1 * static_cast<float>(weather.m_acColor[1][3]));
        if (alpha < 0.0f) {
            alpha = 0.0f;
        } else if (alpha > kByteMax) {  // ble: an unordered alpha is kept
            alpha = kByteMax;
        }
        color[3] = static_cast<uint8_t>(ppc::fctiwz(alpha * cluster.m_fUnk0c));
        for (uint32_t j = 0; j < cluster.m_ui32NbClouds; ++j, ++written) {
            if (out == nullptr || written >= capacity) continue;
            std::memcpy(out + written * 4, color, 4);  // stw of the four bytes
        }
    }
    tank->UnlockPTank();  // vt+0x8c
}
