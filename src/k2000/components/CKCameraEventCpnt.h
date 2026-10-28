// CKCameraEventCpnt.h - a camera to switch to, with a value (key 0x1246, vtable 0xb1ab10, size 0x18).
// Original unit: CKCameraEventCpnt.cpp. No XXL2 class of this name.
#pragma once
#include <cstdint>

#include "k2000/components/IKComponent.h"
#include "k2000/core/Layout.h"

class CKCameraEventCpnt : public IKComponent {
public:
    DOTD_CLASS_KEY(kCategoryComponent, 0x49)
    DOTD_DECLARE_FACTORIES(CKCameraEventCpnt)

    CKCameraEventCpnt() {}  // 0x00166020 CKCameraEventCpnt_Create: the vtable only

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x00166240 CKCameraEventCpnt_Load

    IKSerializable* m_pCamera;  // +0x04 CKCamera (Ghidra type; LVL010 refs of key 0x47, category camera)
    float m_unk08;              // +0x08 (LVL010: 3, 1) _maybe a duration
    uint32_t m_unk0c;           // +0x0c..+0x17 not set by the constructor or the Load
    uint32_t m_unk10;
    uint32_t m_unk14;
};
DOTD_ASSERT_SIZE(CKCameraEventCpnt, 0x18);
DOTD_ASSERT_OFFSET(CKCameraEventCpnt, m_pCamera, 0x04);
DOTD_ASSERT_OFFSET(CKCameraEventCpnt, m_unk08, 0x08);
