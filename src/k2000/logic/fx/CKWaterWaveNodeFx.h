// CKWaterWaveNodeFx.h - the water-wave effect (key 0x3bcc, vtable 0xb2dba0, size 0x38): while it runs, particles are
// emitted at its position each time the timer passes its data's curve of the position's speed. Original unit:
// CKWaterWaveNodeFx.cpp (0x56ff60-0x5710f0). Not in XXL2; names ours.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/fx/IKNodeFx.h"
#include "k2000/math/CMatrix34.h"

class CKWaterWaveFxData;

class CKWaterWaveNodeFx : public IKNodeFx {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0xef)
    int32_t IsKindOfClass(uint32_t key) override {  // vt+0x08 0x9ca9a8
        return key == 0x3bcc || key == 0x148c || key == 0x154c || key == 0xc;
    }
    DOTD_DECLARE_FACTORIES(CKWaterWaveNodeFx)

    // Inlined in 0x00570310 CKWaterWaveNodeFx_Create: the IKNodeFx part only (the fresh heap leaves the rest 0).
    CKWaterWaveNodeFx()
        : m_pData(nullptr), m_pParticles(nullptr), m_fTimer(0.0f), m_vPosition{0.0f, 0.0f, 0.0f},
          m_vPrevPosition{0.0f, 0.0f, 0.0f} {}
    ~CKWaterWaveNodeFx() override {}

    void Destroy() override {}                          // vt+0x10 0x0056ffb0 (empty: the node kept)
    void RecursiveRegistration(int32_t type) override;  // vt+0x24 0x0056ffb8
    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x00570148
    int32_t PostLoad(int32_t /*type*/) override { return 1; }  // vt+0x30 0x00570060
    void Vf64() override;                               // vt+0x64 0x005704f0 CKWaterWaveNodeFx_Start
    void Stop() override;                               // vt+0x6c 0x005704d0
    void Update(IKTime* frameClock) override;           // vt+0x78 0x00570368
    IKFxData* GetFxData() override;                     // vt+0x80 0x009ca9f0 (+0x14)
    void SetFxData(IKFxData* data) override;            // vt+0x84 0x009ca9f8

    // 0x00570068 CKWaterWaveNodeFx_SetPositionIfOwner_maybe: for the reserving `owner`, the position moves to `position`
    // (the old one kept as the previous position).
    void SetPositionIfOwner(const CVector3* position, const IKSerializable* owner);
    // 0x00570498 CKWaterWaveNodeFx_StopIfLinkedTo_maybe: for the reserving `owner`, the running bit (2) cleared (the next
    // Update stops the effect).
    void StopIfOwnedBy(const IKSerializable* owner);

    CKWaterWaveFxData* m_pData;   // +0x14 GetFxData / SetFxData
    IKSerializable* m_pParticles; // +0x18 a reference (Load): a CKSrvFxParticlesAccessor (its +0x04 the CKParticlesCpnt)
    float m_fTimer;               // +0x1c the time since the last emission
    CVector3 m_vPosition;         // +0x20
    CVector3 m_vPrevPosition;     // +0x2c
};
static_assert(CKWaterWaveNodeFx::kClassKey == 0x3bcc, "key");
DOTD_ASSERT_SIZE(CKWaterWaveNodeFx, 0x38);
DOTD_ASSERT_OFFSET(CKWaterWaveNodeFx, m_pData, 0x14);
DOTD_ASSERT_OFFSET(CKWaterWaveNodeFx, m_fTimer, 0x1c);
DOTD_ASSERT_OFFSET(CKWaterWaveNodeFx, m_vPosition, 0x20);
DOTD_ASSERT_OFFSET(CKWaterWaveNodeFx, m_vPrevPosition, 0x2c);
