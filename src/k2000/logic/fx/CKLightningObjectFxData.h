// CKLightningObjectFxData.h - the data of a lightning object effect (key 0x198c, vtable 0xb1d250, size 0x48). Its methods
// sit at the end of CKLensFlareNodeFx.cpp (0x1c6ce8-0x1c7128); Create / CreateArray (0x1adf98 / 0x1ae750) in
// CKMeshPopFxData.cpp, the DeleteArray (0x1ad9d8) in CKFlashFxData.cpp. Its node is CKLightningObjectNodeFx (0x194c,
// CKLightningObjectNodeFx.cpp). Not in XXL2; names ours. No game file holds the class (C2.8 port-rest R06: the members
// the node reads as floats are declared as floats; the rest keep the Load's word reads).
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/logic/IKFxData.h"

class CKLightningObjectFxData : public IKFxData {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x66)
    int32_t IsKindOfClass(uint32_t key) override {  // vt+0x08 0x9ac948
        return key == 0x198c || key == 0x304c || key == 0x6 || key == 0xc;
    }
    DOTD_DECLARE_FACTORIES(CKLightningObjectFxData)

    CKLightningObjectFxData() {}            // inlined in 0x001adf98 CKLightningObjectFxData_Create: the vtables only
    ~CKLightningObjectFxData() override {}  // 0x009ac990 / 0x009ac9d0: the vtables only

    void Destroy() override {}  // vt+0x10 0x001c6d40 CKLightningObjectFxData_Destroy (empty)
    // vt+0x24 0x001c6d18 / vt+0x30 0x001c6cf0: IKFxData's RecursiveRegistration / PostLoad (KStub_Return1_1d8340 /
    // 0x1d8338): the defaults.
    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x001c6d48 CKLightningObjectFxData_Load
    uint32_t GetAssociatedFxClassIdentifier() override { return 0x194c; }  // vt+0x54 0x001c6ce8

    uint32_t m_unk08;      // +0x08 (Load: the fifth read)
    float m_unk0c;         // +0x0c the node stops once its time reaches it
    uint32_t m_unk10;      // +0x10
    float m_unk14;         // +0x14
    float m_afUnk18[9];    // +0x18 not read by the Load
    uint8_t m_Color[4];    // +0x3c read raw (the file's bytes)
    float m_unk40;         // +0x40 not read by the Load
    uint8_t m_baFlags44;   // +0x44 bit 0 from the file (the read byte ORed in whole); bits 1, 2 read by the node
    uint8_t m_pad45[3];
};
static_assert(CKLightningObjectFxData::kClassKey == 0x198c, "key");
DOTD_ASSERT_SIZE(CKLightningObjectFxData, 0x48);
DOTD_ASSERT_OFFSET(CKLightningObjectFxData, m_unk08, 0x08);
DOTD_ASSERT_OFFSET(CKLightningObjectFxData, m_unk14, 0x14);
DOTD_ASSERT_OFFSET(CKLightningObjectFxData, m_Color, 0x3c);
DOTD_ASSERT_OFFSET(CKLightningObjectFxData, m_unk40, 0x40);
DOTD_ASSERT_OFFSET(CKLightningObjectFxData, m_baFlags44, 0x44);
