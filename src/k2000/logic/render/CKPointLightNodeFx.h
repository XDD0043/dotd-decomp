// CKPointLightNodeFx.h - the point-light effect node (key 0xaa4c, vtable 0xb1d5e8, size 0x2c). Original
// unit: CKPointLightNodeFx.cpp. Its data is CKPointLightFxData (0xaa8c). Not in XXL2; names ours.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/fx/IKNodeFx.h"

class CKPointLightNodeFx : public IKNodeFx {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x2a9)
    DOTD_DECLARE_FACTORIES(CKPointLightNodeFx)

    CKPointLightNodeFx() {}  // inlined in 0x001cfe48 CKPointLightNodeFx_Create: the IKNodeFx part only
    ~CKPointLightNodeFx() override {}

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x001cfc98 CKPointLightNodeFx_Load
    // vt+0x30 0x1cfc38 CKPointLightNodeFx_PostLoad: IKNodeFx's, then (level type) the light's +0x18 byte = 0.
    int32_t PostLoad(int32_t type) override;

    // +0x14 the light (Ghidra draft: CSGPointLight*; LVL010 references class 0x94b).
    IKSerializable* m_pPointLight;
    uint32_t m_unk18;            // +0x18
    IKSerializable* m_pFxData;   // +0x1c the inline GetFxData/SetFxData (0x9acfc0/0x9acfc8) use it
    uint32_t m_unk20[3];         // +0x20 run-time state
};
static_assert(CKPointLightNodeFx::kClassKey == 0xaa4c, "key");
DOTD_ASSERT_SIZE(CKPointLightNodeFx, 0x2c);
DOTD_ASSERT_OFFSET(CKPointLightNodeFx, m_pPointLight, 0x14);
DOTD_ASSERT_OFFSET(CKPointLightNodeFx, m_pFxData, 0x1c);
