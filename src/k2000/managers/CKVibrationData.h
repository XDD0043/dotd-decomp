// CKVibrationData.h - a pad vibration (key 0xccc, vtable 0xb19498, size 0x14). Its functions are in
// CKInput.cpp (0x103810-0x10dcb0); CKVibrationData_Delete (0x1037c0) is in CKILError.cpp. XXL2:
// K/KModules/KIL/CKInput.h, the same members in the same order; DotD does not read m_ui8NumPad (it sets
// 0xff) and stores m_bUseTime in a byte at +0x0c.
#pragma once
#include <cstdint>

#include "k2000/components/IKComponent.h"
#include "k2000/core/Layout.h"

class CKVibrationData : public IKComponent {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x33)
    DOTD_DECLARE_FACTORIES(CKVibrationData)

    CKVibrationData() {}  // 0x00107940 CKVibrationData_Create: the vtable only

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x00108768 CKVibrationData_Load

    IKSerializable* m_pOwner;  // +0x04 Load sets null
    uint8_t m_ui8OwnerIndex;   // +0x08 Load sets 0
    uint8_t m_ui8NumPad;       // +0x09 Load sets 0xff (XXL2 reads it)
    uint8_t m_ui8NumMotor;     // +0x0a
    uint8_t m_ui8Value;        // +0x0b
    uint8_t m_bUseTime;        // +0x0c (XXL2 Bool)
    uint8_t m_pad0d[3];
    float m_fTime;             // +0x10
};
DOTD_ASSERT_SIZE(CKVibrationData, 0x14);
DOTD_ASSERT_OFFSET(CKVibrationData, m_pOwner, 0x04);
DOTD_ASSERT_OFFSET(CKVibrationData, m_ui8OwnerIndex, 0x08);
DOTD_ASSERT_OFFSET(CKVibrationData, m_ui8NumPad, 0x09);
DOTD_ASSERT_OFFSET(CKVibrationData, m_ui8NumMotor, 0x0a);
DOTD_ASSERT_OFFSET(CKVibrationData, m_ui8Value, 0x0b);
DOTD_ASSERT_OFFSET(CKVibrationData, m_bUseTime, 0x0c);
DOTD_ASSERT_OFFSET(CKVibrationData, m_fTime, 0x10);
