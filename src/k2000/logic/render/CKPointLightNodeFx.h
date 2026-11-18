// CKPointLightNodeFx.h - the point-light effect node (key 0xaa4c, vtable 0xb1d5e8, size 0x2c). Original
// unit: CKPointLightNodeFx.cpp. Its data is CKPointLightFxData (0xaa8c). Not in XXL2; names ours.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/fx/IKNodeFx.h"
#include "k2000/math/CMatrix34.h"

class CKPointLightNodeFx : public IKNodeFx {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x2a9)
    int32_t IsKindOfClass(uint32_t key) override {  // vt+0x08 0x9acf70
        return key == 0xaa4c || key == 0x148c || key == 0x154c || key == 0xc;
    }
    DOTD_DECLARE_FACTORIES(CKPointLightNodeFx)

    CKPointLightNodeFx() {}  // inlined in 0x001cfe48 CKPointLightNodeFx_Create: the IKNodeFx part only
    ~CKPointLightNodeFx() override {}

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x001cfc98 CKPointLightNodeFx_Load
    // vt+0x30 0x1cfc38 CKPointLightNodeFx_PostLoad: IKNodeFx's, then (level type) the light's +0x18 byte = 0.
    int32_t PostLoad(int32_t type) override;
    // vt+0x24 0x001cfb58 CKPointLightNodeFx_RecursiveRegistration: registered with the saving manager (every type; the
    // node base's is not called).
    void RecursiveRegistration(int32_t type) override;
    // vt+0x64 0x001cfea0 CKPointLightNodeFx_Start: running and reserved; the time 0; the light takes the data's colour,
    // radius and intensity at 0 and the data's position, then hangs under the data's node (vt+0x70) or hot spot (the
    // offset then the light's position) and is switched on and shown.
    void Vf64() override;
    // vt+0x6c 0x001d0130 CKPointLightNodeFx_Stop: stopped; the light back under the dynamic scene root, off and hidden.
    void Stop() override;
    // vt+0x78 0x001d02c8 CKPointLightNodeFx_Update: the time advances, the light follows the data's curves and the offset
    // plus the data's position; a data life (+0x20) not below 0 stops the effect (vt+0x6c) once the time reaches it.
    void Update(IKTime* frameClock) override;
    IKFxData* GetFxData() override { return reinterpret_cast<IKFxData*>(m_pFxData); }  // vt+0x80 0x009acfc0
    void SetFxData(IKFxData* data) override { m_pFxData = reinterpret_cast<IKSerializable*>(data); }  // vt+0x84 0x009acfc8

    // +0x14 the light (Ghidra draft: CSGPointLight*; LVL010 references class 0x94b).
    IKSerializable* m_pPointLight;
    float m_fTime;               // +0x18 the time since the start (Start: the word 0)
    IKSerializable* m_pFxData;   // +0x1c the inline GetFxData/SetFxData (0x9acfc0/0x9acfc8) use it
    CVector3 m_vOffset;          // +0x20 the light's offset: the zero vector, or its position on the hot spot (Start)
};
static_assert(CKPointLightNodeFx::kClassKey == 0xaa4c, "key");
DOTD_ASSERT_SIZE(CKPointLightNodeFx, 0x2c);
DOTD_ASSERT_OFFSET(CKPointLightNodeFx, m_pPointLight, 0x14);
DOTD_ASSERT_OFFSET(CKPointLightNodeFx, m_pFxData, 0x1c);
