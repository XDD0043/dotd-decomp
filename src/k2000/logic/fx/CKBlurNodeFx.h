// CKBlurNodeFx.h - the blur effect node (key 0x30c, vtable 0xb2dd80, size 0x20). Original unit:
// CKBlurNodeFx.cpp. Its data is CKBlurFxData (0x28c). Not in XXL2; names ours. Load reads only the IKNodeFx
// part.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/fx/IKNodeFx.h"

class CKBlurNodeFx : public IKNodeFx {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0xc)
    int32_t IsKindOfClass(uint32_t key) override {  // vt+0x08 0x9cad08
        return key == 0x30c || key == 0x148c || key == 0x154c || key == 0xc;
    }
    DOTD_DECLARE_FACTORIES(CKBlurNodeFx)

    CKBlurNodeFx() {}  // inlined in 0x00572188 CKBlurNodeFx_Create: the IKNodeFx part only
    ~CKBlurNodeFx() override {}

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x00571dc0 CKBlurNodeFx_Load
    void Destroy() override {}  // vt+0x10 0x00571c30 CKBlurNodeFx_Destroy: empty (the node is kept)
    // vt+0x24 0x00571c38 CKBlurNodeFx_RecursiveRegistration: registered with the saving manager whatever the type.
    void RecursiveRegistration(int32_t type) override;
    // vt+0x30 0x00571c90 CKBlurNodeFx_PostLoad: returns 1 (IKNodeFx's answer; IKNodeFx_PostLoad is not called).
    // vt+0x64 0x00571c98 CKBlurNodeFx_Start: running; the post-rendering object's blur on (0x100) with the data's blur
    // data (+0x08) as its own (+0x20); the time 0.
    void Vf64() override;
    // vt+0x6c 0x00572080 CKBlurNodeFx_Stop: stopped; the post object's blur off when its blur data is this effect's; then
    // the node hidden (vt+0x60).
    void Stop() override;
    // vt+0x78 0x00571f60 CKBlurNodeFx_Update: while the post object blurs with this effect's data and the data is timed
    // (+0x0c bit 0), the time advances and the blur intensity (CBlurData +0x1c) follows the data's curve until the
    // data's duration (+0x10); then (or when another blur took over) stopped (vt+0x6c).
    void Update(IKTime* frameClock) override;
    IKFxData* GetFxData() override { return reinterpret_cast<IKFxData*>(m_pFxData); }  // vt+0x80 0x009cad50
    void SetFxData(IKFxData* data) override { m_pFxData = reinterpret_cast<IKSerializable*>(data); }  // vt+0x84 0x009cad58

    float m_fTime;               // +0x14 the time since the start (Start: 0)
    IKSerializable* m_pFxData;   // +0x18 the inline GetFxData (0x9cad50) returns it
    uint32_t m_unk1c;            // +0x1c
};
static_assert(CKBlurNodeFx::kClassKey == 0x30c, "key");
DOTD_ASSERT_SIZE(CKBlurNodeFx, 0x20);
DOTD_ASSERT_OFFSET(CKBlurNodeFx, m_pFxData, 0x18);
