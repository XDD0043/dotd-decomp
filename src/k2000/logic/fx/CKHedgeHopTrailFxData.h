// CKHedgeHopTrailFxData.h - the data of a hedge-hop trail effect (key 0x2d4c, vtable 0xb1cf20, size 0x3c). Original unit:
// CKHedgeHopTrailFxData.cpp (0x1c06d0-0x1c0f90, with two CKHedgeHopTrailNodeFx slots); Create / CreateArray (0x1adf08 /
// 0x1ae8a0) in CKMeshPopFxData.cpp, the DeleteArray (0x1ad7e0) in CKFlashFxData.cpp. Its node is CKHedgeHopTrailNodeFx
// (0x2c4c). Not in XXL2; the names say what the node does with each value. No game file holds the class (C2.8
// port-rest R06).
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/logic/IKFxData.h"

class CKHedgeHopTrailFxData : public IKFxData {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0xb5)
    int32_t IsKindOfClass(uint32_t key) override {  // vt+0x08 0x9ac568
        return key == 0x2d4c || key == 0x304c || key == 0x6 || key == 0xc;
    }
    DOTD_DECLARE_FACTORIES(CKHedgeHopTrailFxData)

    CKHedgeHopTrailFxData() {}            // inlined in 0x001adf08 CKHedgeHopTrailFxData_Create: the vtables only
    ~CKHedgeHopTrailFxData() override {}  // 0x009ac5b0 / 0x009ac5f0: the vtables only

    void Destroy() override {}  // vt+0x10 0x001c0760 CKHedgeHopTrailFxData_Destroy (empty)
    // vt+0x24 0x001c0738 CKHedgeHopTrailFxData_RecursiveRegistration: IKFxData's (KStub_Return1_1d8340): the default.
    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x001c0768 CKHedgeHopTrailFxData_Load
    uint32_t GetAssociatedFxClassIdentifier() override { return 0x2c4c; }  // vt+0x54 0x001c06d0

    uint8_t m_unk08[4];         // +0x08 read raw (the file's bytes, the first read)
    float m_fExtendSpeed;       // +0x0c a ribbon point's distance grows by this per second
    float m_fSpreadSpeed;       // +0x10 the two sides move apart by half of this per second
    float m_unk14;              // +0x14 not read by the node
    float m_fFadeSpeed;         // +0x18 vertex alpha lost per second while fading
    float m_fLength;            // +0x1c the trail's length (the point spacing is length / (points - 1))
    float m_fMinSpread;         // +0x20 the sides' spacing threshold at the head
    float m_fSpreadGrowth;      // +0x24 percent: the threshold grows by it point by point
    float m_fMaxSpread;         // +0x28 the threshold's cap
    float m_fMaxSegment;        // +0x2c a point's distance cap at the head
    float m_fMinSegment;        // +0x30 the cap's floor
    float m_unk34;              // +0x34 not read by the node
    float m_fSegmentDecay;      // +0x38 percent: the distance cap shrinks by it point by point
};
static_assert(CKHedgeHopTrailFxData::kClassKey == 0x2d4c, "key");
DOTD_ASSERT_SIZE(CKHedgeHopTrailFxData, 0x3c);
DOTD_ASSERT_OFFSET(CKHedgeHopTrailFxData, m_fExtendSpeed, 0x0c);
DOTD_ASSERT_OFFSET(CKHedgeHopTrailFxData, m_fFadeSpeed, 0x18);
DOTD_ASSERT_OFFSET(CKHedgeHopTrailFxData, m_fMaxSpread, 0x28);
DOTD_ASSERT_OFFSET(CKHedgeHopTrailFxData, m_fSegmentDecay, 0x38);
