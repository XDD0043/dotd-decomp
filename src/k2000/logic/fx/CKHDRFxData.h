// CKHDRFxData.h - the data of an HDR effect (key 0xf0c, vtable 0xb1ce10, size 0x18). Original unit:
// CKHDRFxData.cpp (0x1be2a0-0x1be7c0). Its node is CKHDRNodeFx (0xf8c). Not in XXL2; names ours.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/logic/IKFxData.h"

class CKHDRFxData : public IKFxData {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x3c)
    int32_t IsKindOfClass(uint32_t key) override {  // vt+0x08 0x9ac338
        return key == 0xf0c || key == 0x304c || key == 0x6 || key == 0xc;
    }
    DOTD_DECLARE_FACTORIES(CKHDRFxData)

    CKHDRFxData() {}  // inlined in 0x001be608 CKHDRFxData_Create: the vtables only

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x001be3c0 CKHDRFxData_Load
    // vt+0x30 0x001be380 CKHDRFxData_PostLoad: IKFxData's (KStub_Return1_1d8338), then +0x10 = +0x0c.
    int32_t PostLoad(int32_t /*type*/) override {
        m_unk10 = m_unk0c;
        return 1;
    }
    int32_t Vf50() override { return 1; }                                  // vt+0x50 0x9ac380
    uint32_t GetAssociatedFxClassIdentifier() override { return 0xf8c; }  // vt+0x54 0x1be2f0
    void Destroy() override {}                          // vt+0x10 0x001be700 CKHDRFxData_Destroy (empty)
    void RecursiveRegistration(int32_t type) override;  // vt+0x24 0x001be4e8
    int32_t MessageProc(uint16_t message, void* data) override;  // vt+0x1c 0x001be708
    // vt+0x40 0x001be6f8 CKHDRFxData_GetInfo: returns 1 (the default).

    IKSerializable* m_pHDRData;  // +0x08 (Ghidra draft: CHDRData*; LVL010 references class 0x54d)
    float m_unk0c;               // +0x0c
    float m_unk10;               // +0x10 the messages 0x1b00..0x1b04 store their data word (0x1b01: the fade time)
    int32_t m_unk14;             // +0x14 bit 1: set by 0x1b03, cleared by 0x1b00
};
static_assert(CKHDRFxData::kClassKey == 0xf0c, "key");
DOTD_ASSERT_SIZE(CKHDRFxData, 0x18);
DOTD_ASSERT_OFFSET(CKHDRFxData, m_pHDRData, 0x08);
DOTD_ASSERT_OFFSET(CKHDRFxData, m_unk0c, 0x0c);
