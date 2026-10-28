// EventNode.cpp - reconstructed original translation unit 0x2361c0-0x2364c8 (GAME_TOC1, main_toc1), 4 functions, 3 live.
// Primary owner: EventNode (not a registered class)
// Other owners: TriggerEventList (1), QueueTriggerSignals (1), TriggerSignals (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x2361c0  CTriggerStarter_Load
//   [x] 0x236330  TriggerEventList_PostLoad_maybe
//   [x] 0x236338  QueueTriggerSignals
//   [ ] 0x236470  TriggerSignals_ClearQueuedFlag_maybe  [dead]
#include "k2000/services/CTriggerStarter.h"

#include "k2000/io/IKFile.h"
#include "k2000/logic/CKComparedData.h"
#include "k2000/logic/CKTrigger.h"
#include "k2000/misc/Engine.h"
#include "k2000/services/CKSrvTrigger.h"

// 0x002361c0 CTriggerStarter_Load
int32_t CTriggerStarter::Load(IKFile* file, int32_t type) {
    if (type != K_LEVEL_PLATEFORMS) return 1;
    ReadU32LE(file, &m_ui32NbDatas);
    if (m_ui32NbDatas == 0) {
        m_apDatas = nullptr;
        return 1;
    }
    CKSrvTrigger* trigger = static_cast<CKSrvTrigger*>(g_pEngine->m_srvTrigger);
    m_apDatas = trigger->m_apAllocatedStarterDatas + trigger->m_ui32NbRequestedStarterDatas;
    trigger->m_ui32NbRequestedStarterDatas += m_ui32NbDatas;
    IKFile_ReadObjectRefArray(file, m_apDatas, m_ui32NbDatas);
    return 1;
}

// 0x00236338 QueueTriggerSignals: each starter data (a mode-2 CKComparedData: a flag byte at +0x08 and
// the signalled CKTrigger at +0x04), from the last down: flag bit 0 set, the trigger's pending byte
// (+0x19) set, and, unless it is already queued (flag bit 1), a node {data, next} pushed on the trigger
// service's pending list (+0x10; the node comes from the FreeListPool in the original). The flag byte is
// bits 24-31 of the word at +0x08 here (the PS3 is big-endian).
void QueueTriggerSignals(CTriggerStarter* starter) {
    CKSrvTrigger* service = static_cast<CKSrvTrigger*>(g_pEngine->m_srvTrigger);
    for (uint32_t i = starter->m_ui32NbDatas; i != 0; --i) {
        CKComparedData* data = static_cast<CKComparedData*>(starter->m_apDatas[i - 1]);
        data->m_unk08 = (data->m_unk08 & 0xfeffffffu) | 0x01000000u;
        static_cast<CKTrigger*>(data->m_pObject)->m_unk19 = 1;
        if ((data->m_unk08 & 0x02000000u) != 0) continue;
        SPendingStarterData* node = new SPendingStarterData();
        node->m_pData = data;
        node->m_pNext = service->m_unk10;
        service->m_unk10 = node;
    }
}
