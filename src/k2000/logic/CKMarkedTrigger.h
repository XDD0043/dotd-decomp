// CKMarkedTrigger.h - trigger starters keyed by marks (key 0xb08c, vtable 0xb30238, size 0x1c). Original
// unit: CKMarkedTrigger.cpp. DotD only; the names are ours.
#pragma once
#include <cstdint>

#include "k2000/core/IKSerializable.h"
#include "k2000/core/Layout.h"
#include "k2000/services/CTriggerStarter.h"
#include "k2000/util/TVector.h"

class CKMarkedTrigger : public IKSerializable {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x2c2)
    DOTD_DECLARE_FACTORIES(CKMarkedTrigger)

    // One mark (OperatorNew(0x10)): a starter and two words (a mark id and a value _maybe).
    struct Mark {
        CTriggerStarter m_tsStarter;  // +0x00 loaded last
        uint32_t m_unk08;             // +0x08 loaded first
        uint32_t m_unk0c;             // +0x0c
    };

    CKMarkedTrigger();  // 0x005d1798 CKMarkedTrigger_Construct
    ~CKMarkedTrigger() override {}

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x005d1c10 CKMarkedTrigger_Load

    TVector<Mark*, 1> m_vMarks;  // +0x04
    IKSerializable* m_unk10;     // +0x10 a reference
    IKSerializable* m_unk14;     // +0x14 a reference
    uint32_t m_unk18;            // +0x18
};
DOTD_ASSERT_SIZE(CKMarkedTrigger::Mark, 0x10);
DOTD_ASSERT_SIZE(CKMarkedTrigger, 0x1c);
DOTD_ASSERT_OFFSET(CKMarkedTrigger, m_vMarks, 0x04);
DOTD_ASSERT_OFFSET(CKMarkedTrigger, m_unk10, 0x10);
DOTD_ASSERT_OFFSET(CKMarkedTrigger, m_unk14, 0x14);
DOTD_ASSERT_OFFSET(CKMarkedTrigger, m_unk18, 0x18);
