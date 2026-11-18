// CKLightningObjectNodeFx.h - the lightning object effect (key 0x194c, vtable 0xb1d2b8, size 0x40): an animated node
// stretched between two points (its frame placed at their middle, its at axis along them, its right / up axes facing
// the camera), its data CKLightningObjectFxData. Original unit: CKLightningObjectNodeFx.cpp (0x1c7128-0x1c8060). Not in
// XXL2; names ours. No game file holds the class (C2.8 port-final F04).
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/fx/IKNodeFx.h"
#include "k2000/math/CMatrix34.h"

class CAnimationDictionary;
class CKLightningObjectFxData;

class CKLightningObjectNodeFx : public IKNodeFx {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x65)
    int32_t IsKindOfClass(uint32_t key) override {  // vt+0x08 0x9aca28
        return key == 0x194c || key == 0x148c || key == 0x154c || key == 0xc;
    }
    DOTD_DECLARE_FACTORIES(CKLightningObjectNodeFx)

    // 0x001c7d20 CKLightningObjectNodeFx_Create / 0x001c73b8 CreateArray: the IKNodeFx part, the vtable (no member set).
    CKLightningObjectNodeFx();
    ~CKLightningObjectNodeFx() override;  // 0x009aca80 / 0x009acaa0: the vtables only

    // vt+0x10 0x001c72c0 CKLightningObjectNodeFx_Destroy: IKNodeFx's (no node), then the dictionary's Destroy (vt+0x10).
    void Destroy() override;
    // vt+0x24 0x001c7200 CKLightningObjectNodeFx_RecursiveRegistration: the saving manager's, IKNodeFx's (the node),
    // then the dictionary's (vt+0x24) when there is one.
    void RecursiveRegistration(int32_t type) override;
    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x001c7ee0 CKLightningObjectNodeFx_Load
    int32_t PostLoad(int32_t type) override;            // vt+0x30 0x001c77a0 CKLightningObjectNodeFx_PostLoad
    void Vf64() override;                               // vt+0x64 0x001c7468 CKLightningObjectNodeFx_Start
    void Stop() override;                               // vt+0x6c 0x001c7d78 CKLightningObjectNodeFx_Stop
    void Update(IKTime* frameClock) override;           // vt+0x78 0x001c7878 CKLightningObjectNodeFx_Update
    IKFxData* GetFxData() override;                     // vt+0x80 0x009aca70 (+0x18)
    void SetFxData(IKFxData* data) override;            // vt+0x84 0x009aca78 (+0x18)

    float m_fTime;                          // +0x14 the time since Start (Start sets 0)
    CKLightningObjectFxData* m_pData;       // +0x18
    CAnimationDictionary* m_pDictionary;    // +0x1c from the file (type 0); its first animation plays on the node
    CVector3 m_v3Start;                     // +0x20 the first end point
    CVector3 m_v3End;                       // +0x2c the second end point
    float m_fEndOffset;                     // +0x38 data bit 2: a random distance along the data's direction (End)
    float m_fStartOffset;                   // +0x3c data bit 2: a random distance along the data's direction (Start)
};
static_assert(CKLightningObjectNodeFx::kClassKey == 0x194c, "key");
DOTD_ASSERT_SIZE(CKLightningObjectNodeFx, 0x40);
DOTD_ASSERT_OFFSET(CKLightningObjectNodeFx, m_fTime, 0x14);
DOTD_ASSERT_OFFSET(CKLightningObjectNodeFx, m_pData, 0x18);
DOTD_ASSERT_OFFSET(CKLightningObjectNodeFx, m_pDictionary, 0x1c);
DOTD_ASSERT_OFFSET(CKLightningObjectNodeFx, m_v3Start, 0x20);
DOTD_ASSERT_OFFSET(CKLightningObjectNodeFx, m_v3End, 0x2c);
DOTD_ASSERT_OFFSET(CKLightningObjectNodeFx, m_fEndOffset, 0x38);
DOTD_ASSERT_OFFSET(CKLightningObjectNodeFx, m_fStartOffset, 0x3c);
