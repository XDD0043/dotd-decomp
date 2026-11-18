// CKDistortionNodeFx.h - the screen distortion effect node (key 0x38cc, vtable 0xb1c6a8, size 0x2c).
// Original unit: CKDistortionNodeFx.cpp. Its data is CKDistortionFxData (0x394c). Not in XXL2; names ours.
// Load reads only the IKNodeFx part.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/fx/IKNodeFx.h"
#include "k2000/math/CMatrix34.h"

class CKDistortionNodeFx : public IKNodeFx {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0xe3)
    int32_t IsKindOfClass(uint32_t key) override {  // vt+0x08 0x9ab528
        return key == 0x38cc || key == 0x148c || key == 0x154c || key == 0xc;
    }
    DOTD_DECLARE_FACTORIES(CKDistortionNodeFx)

    CKDistortionNodeFx() {}  // inlined in 0x001af338 CKDistortionNodeFx_Create: the IKNodeFx part only
    ~CKDistortionNodeFx() override {}

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x001af248 CKDistortionNodeFx_Load
    void Destroy() override {}  // vt+0x10 0x001af0b0 CKDistortionNodeFx_Destroy: empty (the node is kept)
    // vt+0x24 0x001af0b8 CKDistortionNodeFx_RecursiveRegistration: registered with the saving manager whatever the type.
    void RecursiveRegistration(int32_t type) override;
    // vt+0x30 0x001af110 CKDistortionNodeFx_PostLoad: returns 1 (as IKNodeFx's).
    // vt+0x64 0x001af390 CKDistortionNodeFx_Start: running; the screen distortion (key 0xc4d) shows the data's
    // distortion data (+0x08).
    void Vf64() override;
    // vt+0x6c 0x001af558 CKDistortionNodeFx_Stop: stopped; the screen distortion reset when it shows this effect's data;
    // the node hidden (vt+0x60).
    void Stop() override;
    // vt+0x78 0x001af118 CKDistortionNodeFx_Update: stopped (vt+0x6c) once the screen distortion shows other data.
    void Update(IKTime* frameClock) override;
    IKFxData* GetFxData() override { return reinterpret_cast<IKFxData*>(m_pFxData); }  // vt+0x80 0x009ab570
    void SetFxData(IKFxData* data) override { m_pFxData = reinterpret_cast<IKSerializable*>(data); }  // vt+0x84 0x009ab578

    // 0x001af410 CKDistortionNodeFx_SetCenterForOwner_maybe: when `owner` holds the reservation, the centre (+0x20) and
    // the screen distortion's centre pointer (its +0x20) at it.
    void SetCenterForOwner(const CVector3* center, const IKSerializable* owner);

    uint32_t m_unk14;            // +0x14
    IKSerializable* m_pFxData;   // +0x18 the inline GetFxData (0x9ab570) returns it
    uint32_t m_unk1c;            // +0x1c run-time state
    CVector3 m_vCenter;          // +0x20 SetCenterForOwner (the screen distortion points at it)
};
static_assert(CKDistortionNodeFx::kClassKey == 0x38cc, "key");
DOTD_ASSERT_SIZE(CKDistortionNodeFx, 0x2c);
DOTD_ASSERT_OFFSET(CKDistortionNodeFx, m_pFxData, 0x18);
