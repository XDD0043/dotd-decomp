// CKComparedData.h - one operand of a trigger comparison (key 0x234c, vtable 0xb207f0, size 0x18).
// Original unit: CKComparedData.cpp. XXL2: K/KServices/KServiceTrigger/CKComparedData.h (bases
// IKSerializable and SUData_CKComparedData: m_ba32Flags and an unnamed data union). The flags' bits 2-3
// choose what the union holds: 0 an object's value (reference + two words), 2 a byte and a reference,
// 1/3 a typed constant (byte, word, float or reference).
#pragma once
#include <cstdint>

#include "k2000/core/IKInfo.h"
#include "k2000/core/IKSerializable.h"
#include "k2000/core/Layout.h"

class CKComparedData : public IKSerializable {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x8d)
    int32_t IsKindOfClass(uint32_t key) override { return key == 0x234c || key == 0xc; }  // vt+0x08 0x9b7380
    DOTD_DECLARE_FACTORIES(CKComparedData)

    CKComparedData() {}  // inlined in 0x00233118 CKComparedData_Create: only the vtable is set
    ~CKComparedData() override {}

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x002332d0 CKComparedData_Load
    int32_t PostLoad(int32_t type) override;            // vt+0x30 0x002331f0 CKComparedData_PostLoad
    // vt+0x24 0x00232f88 CKComparedData_RecursiveRegistration: for type 0 registered with the saving manager (vt+0x24,
    // no owner). (vt+0x10 0x00232f80 CKComparedData_Destroy is empty.)
    void RecursiveRegistration(int32_t type) override;

    // +0x04 the data (XXL2's unnamed SUData_CKComparedData member): an object reference (mode 0 and 2,
    // constant type 3) or a 32-bit constant (constant types 0-2).
    union {
        IKSerializable* m_pObject;
        uint32_t m_ui32Value;
    };
    uint32_t m_unk08;      // +0x08 mode 0: a word (a message or value id _maybe); mode 2: a byte in bits 24-31
    // +0x0c mode 0: the value id the file names; PostLoad replaces it with the object's accessor for it (GetInfo).
    union {
        uint32_t m_unk0c;
        InfoAccessor m_pfnAccessor;
    };
    uint32_t m_unk10;      // +0x10 not loaded; PostLoad (mode 0): the accessor's this-adjustment (0)
    uint32_t m_ba32Flags;  // +0x14 XXL2 SUData_CKComparedData::m_ba32Flags (bits 2-3: the mode)
};
DOTD_ASSERT_SIZE(CKComparedData, 0x18);
DOTD_ASSERT_OFFSET(CKComparedData, m_pObject, 0x04);
DOTD_ASSERT_OFFSET(CKComparedData, m_unk08, 0x08);
DOTD_ASSERT_OFFSET(CKComparedData, m_unk0c, 0x0c);
DOTD_ASSERT_OFFSET(CKComparedData, m_ba32Flags, 0x14);
