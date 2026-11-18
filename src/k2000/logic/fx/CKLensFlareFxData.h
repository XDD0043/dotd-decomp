// CKLensFlareFxData.h - the data of a lens flare effect (key 0x350c, vtable 0xb1d140, size 0x10). Original unit:
// CKLensFlareFxData.cpp (0x1c5f28-0x1c6758); Create / CreateArray (0x1adec0 / 0x1ae4b8) in CKMeshPopFxData.cpp, the
// DeleteArray (0x1ad4a8) in CKFlashFxData.cpp. Its node is CKLensFlareNodeFx (0x370c), which shows the referenced
// CLensFlareData on the level's CLensFlareFx. Not in XXL2; names ours. No game file holds the class (C2.8 port-rest
// R06: ported from the disassembly anyway).
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/logic/IKFxData.h"

class CLensFlareData;
class IKFx;

class CKLensFlareFxData : public IKFxData {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0xd4)
    int32_t IsKindOfClass(uint32_t key) override {  // vt+0x08 0x9ac7a8
        return key == 0x350c || key == 0x304c || key == 0x6 || key == 0xc;
    }
    DOTD_DECLARE_FACTORIES(CKLensFlareFxData)

    CKLensFlareFxData() {}            // inlined in 0x001adec0 CKLensFlareFxData_Create: the vtables only
    ~CKLensFlareFxData() override {}  // 0x009ac7f0 / 0x009ac830: the vtables only

    // vt+0x10 0x001c5f30 CKLensFlareFxData_Destroy: the flare data's Destroy (vt+0x10, not tested).
    void Destroy() override;
    // vt+0x1c 0x001c61b0 CKLensFlareFxData_MessageProc: 0x1b00 releases the held effect (vt+0x58) and acquires a free one
    // (the inlined CKSrvFx::AcquireFx: reserved, owned by the data, started); 0x1b91 does the same after copying the
    // position the message names into the flare data; 0x1b01 releases the held one. 0 for those, else 1.
    int32_t MessageProc(uint16_t message, void* data) override;
    // vt+0x24 0x001c6130 CKLensFlareFxData_RecursiveRegistration: IKFxData's (KStub_Return1_1d8340), then with type 0 the
    // flare data's (type 0).
    void RecursiveRegistration(int32_t type) override;
    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x001c5fa0 CKLensFlareFxData_Load
    // vt+0x30 0x001c5f78 CKLensFlareFxData_PostLoad: IKFxData's (KStub_Return1_1d8338): the default.
    int32_t GetInfo(struct IKInfo* /*info*/, int32_t /*request*/) override { return 1; }  // vt+0x40 0x001c61a8
    uint32_t GetAssociatedFxClassIdentifier() override { return 0x370c; }  // vt+0x54 0x001c5f28

    CLensFlareData* m_pFlareData;  // +0x08 a reference (level files)
    IKFx* m_pHeldFx;               // +0x0c the effect this data holds (MessageProc); the Load sets 0
};
static_assert(CKLensFlareFxData::kClassKey == 0x350c, "key");
DOTD_ASSERT_SIZE(CKLensFlareFxData, 0x10);
DOTD_ASSERT_OFFSET(CKLensFlareFxData, m_pFlareData, 0x08);
DOTD_ASSERT_OFFSET(CKLensFlareFxData, m_pHeldFx, 0x0c);
