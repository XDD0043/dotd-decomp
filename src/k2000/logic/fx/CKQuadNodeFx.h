// CKQuadNodeFx.h - a textured quad (one PTank particle) at its data's position (key 0x178c, vtable 0xb1d6f8, size 0x1c).
// Original unit: CKQuadNodeFx.cpp (0x1d0978-0x1d1288). Not in XXL2; names ours.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/fx/IKNodeFx.h"

class CKQuadFxData;

class CKQuadNodeFx : public IKNodeFx {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x5e)
    int32_t IsKindOfClass(uint32_t key) override {  // vt+0x08 0x9ad118
        return key == 0x178c || key == 0x148c || key == 0x154c || key == 0xc;
    }
    DOTD_DECLARE_FACTORIES(CKQuadNodeFx)

    CKQuadNodeFx() : m_pData(nullptr), m_fAngle(0.0f) {}  // inlined in 0x001d1230 Create (the heap leaves the rest 0)
    ~CKQuadNodeFx() override {}

    void Destroy() override {}                          // vt+0x10 0x001d09c8 (empty: the node kept)
    void RecursiveRegistration(int32_t type) override;  // vt+0x24 0x001d09d0: the saving manager's registration only
    // vt+0x2c 0x001d0b08 CKQuadNodeFx_Load: IKNodeFx's.
    int32_t PostLoad(int32_t type) override;            // vt+0x30 0x001d0cb8
    void Vf64() override;                               // vt+0x64 0x001d0e30 CKQuadNodeFx_Start
    void Stop() override;                               // vt+0x6c 0x001d0a28
    void Update(IKTime* frameClock) override;           // vt+0x78 0x001d0fd8
    IKFxData* GetFxData() override;                     // vt+0x80 0x009ad160 (+0x14)
    void SetFxData(IKFxData* data) override;            // vt+0x84 0x009ad168

    CKQuadFxData* m_pData;  // +0x14
    float m_fAngle;         // +0x18 the quad's rotation (degrees), advanced by the data's speed
};
static_assert(CKQuadNodeFx::kClassKey == 0x178c, "key");
DOTD_ASSERT_SIZE(CKQuadNodeFx, 0x1c);
DOTD_ASSERT_OFFSET(CKQuadNodeFx, m_pData, 0x14);
DOTD_ASSERT_OFFSET(CKQuadNodeFx, m_fAngle, 0x18);
