// CKDistortionFxData.h - the data of a screen distortion effect (key 0x394c, vtable 0xb1c640, size 0xc).
// Original unit: CKDistortionFxData.cpp (0x1ae9a0-0x1af0d8); Create (0x1ade78) sits in another unit. XXL2:
// KCommonServiceFx/Distortion/CKDistortionFxData.h, member m_pDistortionData (its Load reads it the same way).
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/logic/IKFxData.h"

class CKDistortionFxData : public IKFxData {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0xe5)
    DOTD_DECLARE_FACTORIES(CKDistortionFxData)

    CKDistortionFxData() {}  // inlined in 0x001ade78 CKDistortionFxData_Create: the vtables only

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x001aea18 CKDistortionFxData_Load
    // vt+0x30 PostLoad 0x1ae9f0 (stays the default in C2.1).
    uint32_t GetAssociatedFxClassIdentifier() override { return 0x38cc; }  // vt+0x54 0x1ae9a0

    // +0x08 XXL2 m_pDistortionData (CDistortionScreenData; LVL010 references class 0xc8d).
    IKSerializable* m_pDistortionData;
};
static_assert(CKDistortionFxData::kClassKey == 0x394c, "key");
DOTD_ASSERT_SIZE(CKDistortionFxData, 0xc);
DOTD_ASSERT_OFFSET(CKDistortionFxData, m_pDistortionData, 0x08);
