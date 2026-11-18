// CKDOFFxData.h - the data of a depth-of-field effect (key 0x7f8c, vtable 0xb1c750, size 0x10). Original unit:
// CKDOFFxData.cpp (0x1af710-0x1b06d8, with the camera FX start / stop of CKSrvFx). Its node is the unique CKDOFNodeFx
// (0x7fcc). Not in XXL2; names ours. No game file holds one: a camera's attached fx (IKCamera +0x50) would be one.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/logic/IKFxData.h"

class CKDOFFxData : public IKFxData {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x1fe)
    int32_t IsKindOfClass(uint32_t key) override {  // vt+0x08 0x9ab6c8
        return key == 0x7f8c || key == 0x304c || key == 0x6 || key == 0xc;
    }
    DOTD_DECLARE_FACTORIES(CKDOFFxData)

    CKDOFFxData() {}  // 0x001aff80 CKDOFFxData_Create: the vtables only

    // vt+0x1c 0x001b0148 CKDOFFxData_MessageProc: 0x1b00 starts the effect (CKSrvFx::StartEffect, the data as owner) and
    // gives the unique DOF node the blend time *data; 0x1b01 fades it out over *data. Returns 0 for 0x1b00, else 1.
    int32_t MessageProc(uint16_t message, void* data) override;
    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x001af818 CKDOFFxData_Load
    // vt+0x30 0x001af7f0 CKDOFFxData_PostLoad: KStub_Return1_1d8338 (IKFxData's), 1.
    int32_t Vf50() override { return 1; }                                  // vt+0x50 0x9ab710: a unique effect
    uint32_t GetAssociatedFxClassIdentifier() override { return 0x7fcc; }  // vt+0x54 0x1af760
    // vt+0x24 0x001af940 CKDOFFxData_RecursiveRegistration: IKFxData's, then with type 0 the reference +0x08's.
    void RecursiveRegistration(int32_t type) override;

    IKSerializable* m_pDOFData;  // +0x08 the CDOFData (its +0x04 / +0x08: the camera's focus distance and its clamp)
    float m_fFadeTime;           // +0x0c the fade-out time when a camera stops it with a negative time
};
static_assert(CKDOFFxData::kClassKey == 0x7f8c, "key");
DOTD_ASSERT_SIZE(CKDOFFxData, 0x10);
DOTD_ASSERT_OFFSET(CKDOFFxData, m_pDOFData, 0x08);
DOTD_ASSERT_OFFSET(CKDOFFxData, m_fFadeTime, 0x0c);
