// CDOFData.h - depth-of-field parameters (key 0x10cd, vtable 0xb17808, size 0x14). Original unit:
// CDOFData.cpp (0xb5c70-0xb6bd8, with CHDRData and CBlurData). XXL2's CDOFData has another layout (no
// members), so the names are ours.
#pragma once
#include <cstdint>

#include "k2000/components/IKComponent.h"
#include "k2000/core/Layout.h"

class CDOFData : public IKComponent {
public:
    DOTD_CLASS_KEY(kCategoryGraphical, 0x43)
    int32_t IsKindOfClass(uint32_t key) override {  // vt+0x08 0x9a0d30
        return key == 0x10cd || key == 0x6 || key == 0xc;
    }
    DOTD_DECLARE_FACTORIES(CDOFData)

    CDOFData() {}  // 0x000b6398 CDOFData_Create: the vtable only

    void Destroy() override {}                           // vt+0x10 0x000b5d58 CDOFData_Destroy (blr)
    void RecursiveRegistration(int32_t type) override;  // vt+0x24 0x000b6270 CDOFData_RecursiveRegistration
    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x000b64d8 CDOFData_Load

    // +0x04..+0x10 four byte-swapped words (all 0 in LVL000).
    float m_fFocusDistance;  // +0x04 IKCamera_UpdateTrackBase_maybe: the camera's position-target distance
    float m_fFocusClamp;     // +0x08 the same clamped to the camera's +0x54 (which CKCamera_StartAttachedFx takes from here)
    uint32_t m_unk0c;
    uint32_t m_unk10;
};
DOTD_ASSERT_SIZE(CDOFData, 0x14);
DOTD_ASSERT_OFFSET(CDOFData, m_fFocusDistance, 0x04);
DOTD_ASSERT_OFFSET(CDOFData, m_fFocusClamp, 0x08);
DOTD_ASSERT_OFFSET(CDOFData, m_unk10, 0x10);

// 0x000b5db8 CDOFData_IsInactive_maybe: +0x10 is 0, or +0x04, +0x08 and +0x0c are all 0 (fcmpu: a NaN is not 0).
bool CDOFData_IsInactive(const IKSerializable* data);
// 0x000b6338 CDOFData_SetParams_maybe: the four words +0x04..+0x10 copied from `from` (lfs / stfs).
void CDOFData_SetParams(IKSerializable* data, const IKSerializable* from);
