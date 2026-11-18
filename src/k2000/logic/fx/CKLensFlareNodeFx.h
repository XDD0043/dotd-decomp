// CKLensFlareNodeFx.h - the lens flare effect (key 0x370c, vtable 0xb1d1a8, size 0x18). Original unit:
// CKLensFlareNodeFx.cpp (0x1c6758-0x1c7128, with CKLightningObjectFxData's methods at its end). It shows its data's
// CLensFlareData on the level's CLensFlareFx (the core manager's 0x1b4d). Not in XXL2; names ours. No game file holds
// the class (C2.8 port-rest R06).
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/fx/IKNodeFx.h"

class CKLensFlareFxData;

class CKLensFlareNodeFx : public IKNodeFx {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0xdc)
    int32_t IsKindOfClass(uint32_t key) override {  // vt+0x08 0x9ac888
        return key == 0x370c || key == 0x148c || key == 0x154c || key == 0xc;
    }
    DOTD_DECLARE_FACTORIES(CKLensFlareNodeFx)

    CKLensFlareNodeFx() {}            // inlined in 0x001c6c90 CKLensFlareNodeFx_Create: the IKNodeFx part, the vtable
    ~CKLensFlareNodeFx() override {}  // 0x009ac8e0 / 0x009ac900: the vtables only

    void Destroy() override {}  // vt+0x10 0x001c67a8 CKLensFlareNodeFx_Destroy (empty: the node kept)
    // vt+0x24 0x001c67b0 CKLensFlareNodeFx_RecursiveRegistration: the saving manager's registration only.
    void RecursiveRegistration(int32_t type) override;
    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x001c6940 CKLensFlareNodeFx_Load
    int32_t PostLoad(int32_t /*type*/) override { return 1; }  // vt+0x30 0x001c6808
    void Vf64() override;                               // vt+0x64 0x001c6af0 CKLensFlareNodeFx_Start
    void Stop() override;                               // vt+0x6c 0x001c6b88 CKLensFlareNodeFx_Stop
    void Update(IKTime* frameClock) override;           // vt+0x78 0x001c6810 CKLensFlareNodeFx_Update
    IKFxData* GetFxData() override;                     // vt+0x80 0x009ac8d0 (+0x14)
    void SetFxData(IKFxData* data) override;            // vt+0x84 0x009ac8d8 (+0x14)

    CKLensFlareFxData* m_pData;  // +0x14 not set by the constructor or Load
};
static_assert(CKLensFlareNodeFx::kClassKey == 0x370c, "key");
DOTD_ASSERT_SIZE(CKLensFlareNodeFx, 0x18);
DOTD_ASSERT_OFFSET(CKLensFlareNodeFx, m_pData, 0x14);
