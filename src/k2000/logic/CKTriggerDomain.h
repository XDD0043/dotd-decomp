// CKTriggerDomain.h - a group of triggers and sub-domains (key 0x28cc, vtable 0xb20b18, size 0x24).
// Original unit: CKTriggerDomain.cpp. XXL2: K/KServices/KServiceTrigger/CKTriggerDomain.h (m_vTriggers,
// m_vSubDomains, m_ba32Flags; DotD has a CKTriggerSynchro reference where XXL2 has
// m_pSubDomainActiveOnStart and m_iSectorIndex).
#pragma once
#include <cstdint>

#include "k2000/core/IKSerializable.h"
#include "k2000/core/Layout.h"
#include "k2000/util/TVector.h"

class CKTriggerSynchro;

class CKTriggerDomain : public IKSerializable {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0xa3)
    int32_t IsKindOfClass(uint32_t key) override { return key == 0x28cc || key == 0xc; }  // vt+0x08 0x9b89c0
    DOTD_DECLARE_FACTORIES(CKTriggerDomain)
    // vt+0x40 0x002369b8 CKTriggerDomain_GetInfo: the trigger values 1 (the domain enabled).
    int32_t GetInfo(IKInfo* info, int32_t request) override;

    CKTriggerDomain();  // inlined in 0x00236890 CKTriggerDomain_Create
    ~CKTriggerDomain() override {}

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x00236a28 CKTriggerDomain_Load

    // 0x009b8b28 CKTriggerDomain_EnableRecursive / 0x009b9280 CKTriggerDomain_DisableRecursive (out-of-line
    // copies of a recursive inline; the original unrolls several levels): every sub-domain (last to first)
    // enabled or disabled the same way, then this domain's triggers (last to first) through their evaluator's
    // vt+0x64 / vt+0x68. The domain's own enabled bit is not touched.
    void EnableRecursive();
    void DisableRecursive();
    // 0x002388f8 CKTriggerDomain_ResetTriggersAndEnableState_maybe (CKSrvTrigger_Stop): every sub-domain (first
    // to last) the same way, then this domain's triggers reset through their evaluator's vt+0x60, then the
    // enabled bit (bit 1 of the flags, the state at load) copied to bit 0 and applied as in SetEnabled.
    void ResetTriggersAndEnableState();
    // 0x00237850 CKTriggerDomain_RestoreInitialEnableState_maybe (CKSrvTrigger_Start; the original unrolls the
    // recursion several levels): a domain without a synchro copies its initial enabled bit (flags bit 1) to bit 0
    // and applies it (sub-domains, then triggers' evaluators, both last to first); then every sub-domain the same
    // way (first to last), then this domain's evaluators are started (vt+0x58, first to last).
    void RestoreInitialEnableState();
    // vt+0x1c 0x00237470 CKTriggerDomain_MessageProc: the trigger actions' domain messages: 0x2200 enables the domain
    // (when disabled), 0x2201 disables it (when enabled), 0x2202 toggles it; the sub-domains and the triggers' evaluators
    // follow as in ResetTriggersAndEnableState. 0 when handled, 1 for any other message.
    int32_t MessageProc(uint16_t message, void* data) override;
    // 0x002365a8 CKTriggerDomain_EvaluateTriggers: the enabled sub-domains first, then every trigger that is polled
    // (+0x18) or was signalled (+0x19): when its evaluator holds, its starters are queued, its actions sent and
    // the evaluator told (vt+0x50); a domain with flags bit 2 stops after the first trigger that fired.
    void EvaluateTriggers();
    // 0x00236db0 CKTriggerDomain_ClearConditionEventsRecursive_maybe: every sub-domain (first to last) the same way,
    // then this domain's triggers' evaluators told (vt+0x5c, first to last).
    void ClearConditionEventsRecursive();

    TVector<IKSerializable*, 8> m_vTriggers;       // +0x04 CKTrigger*; the file's second count
    TVector<CKTriggerDomain*, 8> m_vSubDomains;    // +0x10 the file's first count
    CKTriggerSynchro* m_pTriggerSynchro;           // +0x1c (the files reference CKTriggerSynchro objects)
    uint32_t m_ba32Flags;                          // +0x20 XXL2 CBitArray m_ba32Flags; not set by the constructor
};
DOTD_ASSERT_SIZE(CKTriggerDomain, 0x24);
DOTD_ASSERT_OFFSET(CKTriggerDomain, m_vTriggers, 0x04);
DOTD_ASSERT_OFFSET(CKTriggerDomain, m_vSubDomains, 0x10);
DOTD_ASSERT_OFFSET(CKTriggerDomain, m_pTriggerSynchro, 0x1c);
DOTD_ASSERT_OFFSET(CKTriggerDomain, m_ba32Flags, 0x20);
