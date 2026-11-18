// CKWaterSplashNodeFx.h - the water-splash effect (key 0x3c4c, vtable 0xb2daf8, size 0x28): two meshes (the node and a
// second movable) scaled and faded along CKWaterSplashFxData's curves, plus two particle bursts at the trigger. Original
// unit: CKWaterSplashNodeFx.cpp (0x56f2a0-0x56ff60). Not in XXL2; names ours.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/fx/IKNodeFx.h"
#include "k2000/math/CMatrix34.h"

class CKWaterSplashFxData;
class CNode;

class CKWaterSplashNodeFx : public IKNodeFx {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0xf1)
    int32_t IsKindOfClass(uint32_t key) override {  // vt+0x08 0x9ca8e8
        return key == 0x3c4c || key == 0x148c || key == 0x154c || key == 0xc;
    }
    DOTD_DECLARE_FACTORIES(CKWaterSplashNodeFx)

    // Inlined in 0x0056f5a0 CKWaterSplashNodeFx_Create: the IKNodeFx part only (the fresh heap leaves the rest 0).
    CKWaterSplashNodeFx() : m_pMesh2(nullptr), m_pParticles1(nullptr), m_pParticles2(nullptr), m_pData(nullptr), m_fTime(0.0f) {}
    ~CKWaterSplashNodeFx() override {}

    void Destroy() override {}                          // vt+0x10 0x0056f2f0 (empty: the nodes kept)
    void RecursiveRegistration(int32_t type) override;  // vt+0x24 0x0056f2f8
    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x0056fd98
    int32_t PostLoad(int32_t type) override;            // vt+0x30 0x0056f450
    void Vf64() override;                               // vt+0x64 0x0056f6b8 CKWaterSplashNodeFx_Start
    void Stop() override;                               // vt+0x6c 0x0056f5f8
    void Update(IKTime* frameClock) override;           // vt+0x78 0x0056f9a8
    IKFxData* GetFxData() override;                     // vt+0x80 0x009ca930 (+0x20)
    void SetFxData(IKFxData* data) override;            // vt+0x84 0x009ca938

    // 0x0056f7a0 CKWaterSplashNodeFx_TriggerAt_maybe: for the reserving `owner`, started and shown, both meshes moved to
    // `position` (the second one shown), the two particle bursts there; running (bit 2).
    void TriggerAt(const CVector3* position, const IKSerializable* owner);

    CNode* m_pMesh2;               // +0x14 a reference: the second mesh (a CSGMovable)
    IKSerializable* m_pParticles1; // +0x18 a reference: a CKSrvFxParticlesAccessor
    IKSerializable* m_pParticles2; // +0x1c a reference: a CKSrvFxParticlesAccessor
    CKWaterSplashFxData* m_pData;  // +0x20 GetFxData / SetFxData
    float m_fTime;                 // +0x24 the time since the trigger (Start: 0)
};
static_assert(CKWaterSplashNodeFx::kClassKey == 0x3c4c, "key");
DOTD_ASSERT_SIZE(CKWaterSplashNodeFx, 0x28);
DOTD_ASSERT_OFFSET(CKWaterSplashNodeFx, m_pMesh2, 0x14);
DOTD_ASSERT_OFFSET(CKWaterSplashNodeFx, m_pData, 0x20);
DOTD_ASSERT_OFFSET(CKWaterSplashNodeFx, m_fTime, 0x24);
