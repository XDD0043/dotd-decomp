// CKTrailShockWaveNodeFx.h - a shock wave that runs along the ground (key 0x444c, vtable 0xb2de90, size 0x9c): three
// particle nodes moved from the start towards a target point (accelerating, clamped), kept on the ground, their
// emitters' size / standard properties interpolated along the run, a damage sphere under the first. Original unit:
// CKTrailShockWaveNodeFx.cpp (0x572e48-0x5748c0). Its data is CKTrailShockWaveFxData (0x448c). No game file holds one
// (outputs/remake/kp3-class-usage.json). Not in XXL2; names ours (C2.8 port-rest R07).
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/fx/IKNodeFx.h"
#include "k2000/hooks/GroundContact.h"
#include "k2000/math/CMatrix34.h"

class CKDynamicBoundingSphere;
class CParticlesNodeFx;

class CKTrailShockWaveNodeFx : public IKNodeFx {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x111)
    int32_t IsKindOfClass(uint32_t key) override {  // vt+0x08 0x9cae10
        return key == 0x444c || key == 0x148c || key == 0x154c || key == 0xc;
    }
    DOTD_DECLARE_FACTORIES(CKTrailShockWaveNodeFx)

    // 0x00573280 CKTrailShockWaveNodeFx_Construct (= 0x573168 Construct_2; inlined in 0x573b48 Create): IKNodeFx's,
    // then the ground contact's defaults (masks 1, 8; no ground, face -1, status 3, sector 0). The rest is set by
    // TriggerAt / PostLoad.
    CKTrailShockWaveNodeFx();
    // 0x00573bd8 CKTrailShockWaveNodeFx_Destruct (the vtables only) / 0x573e28 DeletingDestruct (+ delete).
    ~CKTrailShockWaveNodeFx() override {}

    void Destroy() override {}  // vt+0x10 0x00572e98 (empty: the node is kept)
    // vt+0x2c 0x005732f8 CKTrailShockWaveNodeFx_Load: IKNodeFx's, then (level data only) the three particle nodes
    // (references) and the damage radius (a word).
    int32_t Load(IKFile* file, int32_t type) override;
    // vt+0x30 0x00573100 CKTrailShockWaveNodeFx_PostLoad: IKNodeFx's (1), no damage sphere.
    int32_t PostLoad(int32_t type) override;
    // vt+0x24 0x00573140 CKTrailShockWaveNodeFx_RecursiveRegistration: IKNodeFx's (the node).
    IKFxData* GetFxData() override { return reinterpret_cast<IKFxData*>(m_pFxData); }                   // vt+0x80 0x9cae58
    void SetFxData(IKFxData* data) override { m_pFxData = reinterpret_cast<IKSerializable*>(data); }  // vt+0x84 0x9cae60
    void Vf64() override { m_baFxData = static_cast<uint8_t>(m_baFxData & 0xfe); }  // vt+0x64 0x00572ea0 Start
    // vt+0x6c 0x00573e70 CKTrailShockWaveNodeFx_Stop: stopped (bit 0), HideAndReleaseCollision, the three emitters stop
    // emitting (ParticleFxNode_StopEmitting_maybe).
    void Stop() override;
    // vt+0x78 0x00573fd0 CKTrailShockWaveNodeFx_Update: running, the position moves towards the target (the speed
    // accelerates by +0x44, clamped at +0x3c), the ground under it is probed: on it, the three nodes there with their
    // emitters' properties at the run's progress (the distance from the start over the data's spacing), at the target
    // all stop; off it, all stop at once. Stopped (+0x98): once the three emitters have no live particle, Stop (vt+0x6c).
    void Update(IKTime* frameClock) override;

    // 0x005734f8 CKTrailShockWaveNodeFx_TriggerAt_maybe (no reference to its descriptor 0xbe5b60 in the EBOOT): when
    // reserved by `owner`, the run from `start` towards start + spacing x the normalised `direction`; the nodes shown
    // there and emitting; the damage sphere (taken from the collision service) under the first node; the ground
    // contact's heights (0.5, the radius / 2) and defaults.
    void TriggerAt(const IKSerializable* owner, const CVector3* start, const CVector3* direction);
    // 0x00572fd8 CKTrailShockWaveNodeFx_HideAndReleaseCollision_maybe (no reference to its descriptor 0xbe5ad0; inlined
    // in Stop and Update): the three nodes stop emitting (0x400 / 0x80000 cleared, the emitters' emit flag off), the
    // damage sphere released, done (+0x98).
    void HideAndReleaseCollision();

    IKSerializable* m_pFxData;             // +0x14 a CKTrailShockWaveFxData
    CParticlesNodeFx* m_apParticles[3];    // +0x18 references (Load)
    CVector3 m_v3Target;                   // +0x24 TriggerAt: start + direction x spacing
    CVector3 m_v3Pos;                      // +0x30 the current position
    float m_fMaxSpeed;                     // +0x3c data +0x100
    float m_fSpeed;                        // +0x40 data +0xfc, then accelerated
    float m_fAccel;                        // +0x44 data +0x104
    CVector3 m_v3Start;                    // +0x48
    float m_fRadius;                       // +0x54 read as a word (Load): the damage sphere's radius
    CKDynamicBoundingSphere* m_pSphere;    // +0x58 PostLoad 0
    CGroundContactDatasIn m_GrdIn;         // +0x5c TriggerAt: 0.5, radius / 2; constructor masks 1, 8
    CGroundContactDatasInOut m_GrdInOut;   // +0x6c
    uint8_t m_bDone;                       // +0x98 stopped (TriggerAt 0)
    uint8_t m_pad99[3];
};
static_assert(CKTrailShockWaveNodeFx::kClassKey == 0x444c, "key");
DOTD_ASSERT_SIZE(CKTrailShockWaveNodeFx, 0x9c);
DOTD_ASSERT_OFFSET(CKTrailShockWaveNodeFx, m_pFxData, 0x14);
DOTD_ASSERT_OFFSET(CKTrailShockWaveNodeFx, m_apParticles, 0x18);
DOTD_ASSERT_OFFSET(CKTrailShockWaveNodeFx, m_fMaxSpeed, 0x3c);
DOTD_ASSERT_OFFSET(CKTrailShockWaveNodeFx, m_fRadius, 0x54);
DOTD_ASSERT_OFFSET(CKTrailShockWaveNodeFx, m_GrdIn, 0x5c);
DOTD_ASSERT_OFFSET(CKTrailShockWaveNodeFx, m_GrdInOut, 0x6c);
DOTD_ASSERT_OFFSET(CKTrailShockWaveNodeFx, m_bDone, 0x98);
