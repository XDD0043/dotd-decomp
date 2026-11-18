// CKTrigger.h - a trigger: a condition, its actions and a starter list (key 0x238c, vtable 0xb208a8,
// size 0x1c). Original unit: CKTrigger.cpp. XXL2: K/KServices/KServiceTrigger/CKTrigger.h
// (m_pRootEvaluator, m_aActions, m_ui32NbActions); DotD adds the CTriggerStarter at +0x04 and the
// bytes at +0x18. The actions are slots of CKSrvTrigger's level-wide action block.
#pragma once
#include <cstdint>

#include "k2000/core/IKSerializable.h"
#include "k2000/core/Layout.h"
#include "k2000/services/CTriggerStarter.h"

class IKEvaluator;
struct CTriggerAction;

class CKTrigger : public IKSerializable {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x8e)
    int32_t IsKindOfClass(uint32_t key) override { return key == 0x238c || key == 0xc; }  // vt+0x08 0x9b74b8
    DOTD_DECLARE_FACTORIES(CKTrigger)

    CKTrigger() {}  // inlined in 0x00233850 CKTrigger_Create: only the vtable is set
    ~CKTrigger() override {}

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x00233928 CKTrigger_Load

    // 0x00233b60 CKTrigger_LoadAction (XXL2 CTriggerAction::Load, inlined there): reads one action.
    static int32_t LoadAction(CTriggerAction* action, IKFile* file, int32_t type);

    CTriggerStarter m_tsStarter;     // +0x04 DotD (name ours); PostLoad calls its PostLoad
    IKEvaluator* m_pRootEvaluator;   // +0x0c XXL2 m_pRootEvaluator (CKComparator / CKCombiner)
    CTriggerAction* m_aActions;      // +0x10 XXL2 m_aActions: slots of CKSrvTrigger::m_aAllocatedActions
    uint32_t m_ui32NbActions;        // +0x14 XXL2 m_ui32NbActions
    uint8_t m_unk18;                 // +0x18 a byte from the file (a flag _maybe)
    uint8_t m_unk19;                 // +0x19 the Load sets 0
    uint8_t m_pad1a[2];
};
DOTD_ASSERT_SIZE(CKTrigger, 0x1c);
DOTD_ASSERT_OFFSET(CKTrigger, m_tsStarter, 0x04);
DOTD_ASSERT_OFFSET(CKTrigger, m_pRootEvaluator, 0x0c);
DOTD_ASSERT_OFFSET(CKTrigger, m_aActions, 0x10);
DOTD_ASSERT_OFFSET(CKTrigger, m_ui32NbActions, 0x14);
DOTD_ASSERT_OFFSET(CKTrigger, m_unk18, 0x18);
DOTD_ASSERT_OFFSET(CKTrigger, m_unk19, 0x19);
