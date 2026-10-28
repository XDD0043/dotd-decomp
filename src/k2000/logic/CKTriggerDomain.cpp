// CKTriggerDomain.cpp - reconstructed original translation unit 0x2364c8-0x239b10 (GAME_TOC1, main_toc1), 17 functions, 17 live.
// Primary class: CKTriggerDomain  key 0x28cc  category Logic  size 0x24  vtable 0xb20b18
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x2364c8  CKTriggerDomain_Delete
//   [ ] 0x236518  CKTriggerDomain_RecursiveRegistration
//   [ ] 0x236520  RegisterCKTriggerDomainClass
//   [ ] 0x236598  _GLOBAL__I_236598
//   [x] 0x2365a8  CKTriggerDomain_EvaluateTriggers
//   [x] 0x2367e8  CKTriggerDomain_DeleteArray
//   [x] 0x236890  CKTriggerDomain_Create
//   [x] 0x2368f0  CKTriggerDomain_CreateArray
//   [ ] 0x2369b8  CKTriggerDomain_GetInfo
//   [ ] 0x236a10  CKTriggerDomain_Save
//   [ ] 0x236a18  CKTriggerDomain_PostLoad
//   [ ] 0x236a20  CKTriggerDomain_Destroy
//   [x] 0x236a28  CKTriggerDomain_Load
//   [ ] 0x236db0  CKTriggerDomain_ClearConditionEventsRecursive_maybe
//   [x] 0x237470  CKTriggerDomain_MessageProc
//   [x] 0x237850  CKTriggerDomain_RestoreInitialEnableState_maybe
//   [x] 0x2388f8  CKTriggerDomain_ResetTriggersAndEnableState_maybe
//
//   [ ] 0x9b8998  CKTriggerDomain_GetClassType  [inline]
//   [ ] 0x9b89a0  CKTriggerDomain_GetClassID  [inline]
//   [ ] 0x9b89a8  CKTriggerDomain_vf50  [inline]
//   [ ] 0x9b89b0  CKTriggerDomain_GetIsEnabled  [inline]
//   [ ] 0x9b89c0  CKTriggerDomain_IsKindOfClass  [inline]
//   [ ] 0x9b89e0  CKTriggerDomain_Destructor  [inline]
//   [ ] 0x9b8a78  CKTriggerDomain_DeletingDestructor  [inline]
//   [x] 0x9b8b28  CKTriggerDomain_EnableRecursive  [inline]
//   [x] 0x9b9280  CKTriggerDomain_DisableRecursive  [inline]
#include "k2000/logic/CKTriggerDomain.h"

#include "k2000/io/IKFile.h"
#include "k2000/logic/CKTrigger.h"
#include "k2000/logic/CKTriggerSynchro.h"
#include "k2000/misc/IKEvaluator.h"
#include "k2000/memory/Mem.h"
#include "k2000/services/CKSrvTrigger.h"

namespace {

// The vector read CKTriggerDomain_Load inlines twice: sized to the count (1 when 0), then the references.
template <class T>
void LoadRefVector(IKFile* file, TVector<T*, 8>& vector, uint32_t count) {
    if (count == 0) {
        vector.m_ui32NbElt = 1;
        vector.m_pBlock = static_cast<T**>(Mem_AllocAligned16(static_cast<uint32_t>(sizeof(T*))));
        return;
    }
    vector.m_ui32NbElt = count;
    vector.m_pBlock = static_cast<T**>(Mem_AllocAligned16(count * static_cast<uint32_t>(sizeof(T*))));
    if (vector.m_ui32NbElt < count) {  // as in the original: cannot happen right after the assignment
        uint32_t capacity = (count & ~7u) + 8;
        if (capacity == 0) capacity = 8;
        vector.m_pBlock = static_cast<T**>(
            Mem_ReallocAligned16(vector.m_pBlock, capacity * static_cast<uint32_t>(sizeof(T*))));
        vector.m_ui32NbElt = capacity;
    }
    vector.m_ui32NbUsedElt = count;
    IKFile_ReadObjectRefArray(file, reinterpret_cast<IKSerializable**>(vector.m_pBlock), count);
}

}  // namespace

// Inlined in 0x00236890 CKTriggerDomain_Create: both vectors empty with a capacity of 8.
CKTriggerDomain::CKTriggerDomain() {
    m_vTriggers.m_pBlock = nullptr;
    m_vTriggers.m_ui32NbElt = 8;
    m_vTriggers.m_ui32NbUsedElt = 0;
    m_vSubDomains.m_ui32NbElt = 8;
    m_vSubDomains.m_ui32NbUsedElt = 0;
    m_vSubDomains.m_pBlock = nullptr;
}

// 0x00236a28 CKTriggerDomain_Load
int32_t CKTriggerDomain::Load(IKFile* file, int32_t type) {
    if (type != K_LEVEL_PLATEFORMS) return 1;
    ReadU32LE(file, &m_ba32Flags);
    uint32_t subDomainCount = 0;
    ReadU32LE(file, &subDomainCount);
    uint32_t triggerCount = 0;
    ReadU32LE(file, &triggerCount);
    LoadRefVector(file, m_vSubDomains, subDomainCount);
    LoadRefVector(file, m_vTriggers, triggerCount);
    IKFile_ReadRef(file, &m_pTriggerSynchro);
    return 1;
}

// 0x009b8b28 CKTriggerDomain_EnableRecursive
void CKTriggerDomain::EnableRecursive() {
    for (uint32_t i = m_vSubDomains.m_ui32NbUsedElt; i != 0; --i) m_vSubDomains.m_pBlock[i - 1]->EnableRecursive();
    for (uint32_t i = m_vTriggers.m_ui32NbUsedElt; i != 0; --i) {
        static_cast<CKTrigger*>(m_vTriggers.m_pBlock[i - 1])->m_pRootEvaluator->Asleep();
    }
}

// 0x009b9280 CKTriggerDomain_DisableRecursive
void CKTriggerDomain::DisableRecursive() {
    for (uint32_t i = m_vSubDomains.m_ui32NbUsedElt; i != 0; --i) m_vSubDomains.m_pBlock[i - 1]->DisableRecursive();
    for (uint32_t i = m_vTriggers.m_ui32NbUsedElt; i != 0; --i) {
        static_cast<CKTrigger*>(m_vTriggers.m_pBlock[i - 1])->m_pRootEvaluator->Vf68();
    }
}

// 0x002388f8 CKTriggerDomain_ResetTriggersAndEnableState_maybe: the original unrolls the recursion over the
// sub-domains seven levels deep; the order of the calls is the plain recursion's.
void CKTriggerDomain::ResetTriggersAndEnableState() {
    for (uint32_t i = 0; i < m_vSubDomains.m_ui32NbUsedElt; ++i) m_vSubDomains.m_pBlock[i]->ResetTriggersAndEnableState();
    for (uint32_t i = 0; i < m_vTriggers.m_ui32NbUsedElt; ++i) {
        static_cast<CKTrigger*>(m_vTriggers.m_pBlock[i])->m_pRootEvaluator->Vf60();
    }
    const uint32_t initiallyEnabled = (m_ba32Flags >> 1) & 1;
    m_ba32Flags = (m_ba32Flags & 0xfffffffeu) | initiallyEnabled;
    if (initiallyEnabled == 0) {
        DisableRecursive();
    } else {
        EnableRecursive();
    }
}

// 0x00237850 CKTriggerDomain_RestoreInitialEnableState_maybe
void CKTriggerDomain::RestoreInitialEnableState() {
    if (m_pTriggerSynchro == nullptr) {
        const uint32_t initiallyEnabled = (m_ba32Flags >> 1) & 1;
        m_ba32Flags = (m_ba32Flags & 0xfffffffeu) | initiallyEnabled;
        if (initiallyEnabled == 0) {
            for (uint32_t i = m_vSubDomains.m_ui32NbUsedElt; i != 0; --i) m_vSubDomains.m_pBlock[i - 1]->DisableRecursive();
            for (uint32_t i = m_vTriggers.m_ui32NbUsedElt; i != 0; --i) {
                static_cast<CKTrigger*>(m_vTriggers.m_pBlock[i - 1])->m_pRootEvaluator->Vf68();
            }
        } else {
            for (uint32_t i = m_vSubDomains.m_ui32NbUsedElt; i != 0; --i) m_vSubDomains.m_pBlock[i - 1]->EnableRecursive();
            for (uint32_t i = m_vTriggers.m_ui32NbUsedElt; i != 0; --i) {
                static_cast<CKTrigger*>(m_vTriggers.m_pBlock[i - 1])->m_pRootEvaluator->Asleep();
            }
        }
    }
    for (uint32_t i = 0; i < m_vSubDomains.m_ui32NbUsedElt; ++i) m_vSubDomains.m_pBlock[i]->RestoreInitialEnableState();
    for (uint32_t i = 0; i < m_vTriggers.m_ui32NbUsedElt; ++i) {
        static_cast<CKTrigger*>(m_vTriggers.m_pBlock[i])->m_pRootEvaluator->Start();
    }
}

// 0x002365a8 CKTriggerDomain_EvaluateTriggers (the count is read again after every sub-domain and every fire)
void CKTriggerDomain::EvaluateTriggers() {
    for (uint32_t i = 0; i < m_vSubDomains.m_ui32NbUsedElt; ++i) {
        CKTriggerDomain* subDomain = m_vSubDomains.m_pBlock[i];
        if ((subDomain->m_ba32Flags & 1) != 0) subDomain->EvaluateTriggers();
    }
    for (uint32_t i = 0; i < m_vTriggers.m_ui32NbUsedElt; ++i) {
        CKTrigger* trigger = static_cast<CKTrigger*>(m_vTriggers.m_pBlock[i]);
        if (trigger->m_unk18 == 0 && trigger->m_unk19 == 0) continue;
        trigger->m_unk19 = 0;
        if (trigger->m_pRootEvaluator->Vf54()) {
            QueueTriggerSignals(&trigger->m_tsStarter);
            for (uint32_t j = 0; j < trigger->m_ui32NbActions; ++j) {
                CTriggerAction* action = &trigger->m_aActions[j];
                if (action->m_pObject != nullptr) action->m_pObject->MessageProc(action->m_mMsg, action);
            }
            trigger->m_pRootEvaluator->Vf50();
            if ((m_ba32Flags & 4) != 0) return;
        }
    }
}

// 0x00237470 CKTriggerDomain_MessageProc
int32_t CKTriggerDomain::MessageProc(uint16_t message, void* /*data*/) {
    if (message == 0x2201) {
        if ((m_ba32Flags & 1) != 0) {
            m_ba32Flags &= 0xfffffffeu;
            DisableRecursive();
        }
    } else if (message == 0x2202) {
        const uint32_t wasEnabled = m_ba32Flags & 1;
        m_ba32Flags = (m_ba32Flags & 0xfffffffeu) | (wasEnabled ^ 1);
        if (wasEnabled == 0) {
            EnableRecursive();
        } else {
            DisableRecursive();
        }
    } else if (message == 0x2200) {
        if ((m_ba32Flags & 1) == 0) {
            m_ba32Flags = (m_ba32Flags & 0xfffffffeu) | 1;
            EnableRecursive();
        }
    } else {
        return 1;
    }
    return 0;
}
