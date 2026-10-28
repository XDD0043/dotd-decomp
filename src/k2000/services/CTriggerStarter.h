// CTriggerStarter.h - a list of trigger starter datas, embedded in many classes (XXL2:
// K/KServices/KServiceTrigger/CTriggerStarter.h). Its Load takes its slots from the trigger service's
// starter-data pool, which CKSrvTrigger_Load sized for the whole level.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"

class IKFile;
class IKSerializable;

// Plain data: the owners' constructors set (or leave) the fields, as in the original.
struct CTriggerStarter {
    // 0x002361c0 CTriggerStarter_Load (was EventNode_Load; the same code as XXL2's
    // CTriggerStarter::Load). Reads only for K_LEVEL_PLATEFORMS; returns 1.
    int32_t Load(IKFile* file, int32_t type);
    // 0x00236330 TriggerEventList_PostLoad_maybe (CTriggerStarter::PostLoad): returns 1.
    int32_t PostLoad(int32_t /*type*/) { return 1; }

    IKSerializable** m_apDatas;  // +0x00 CKComparedData* slots in CKSrvTrigger::m_apAllocatedStarterDatas
    uint32_t m_ui32NbDatas;      // +0x04
};
DOTD_ASSERT_SIZE(CTriggerStarter, 0x8);

// C2.2 gm: a node of the trigger service's pending list (CKSrvTrigger +0x10), 8 bytes from the FreeListPool in the
// original; whoever empties the list (CKSrvTrigger Start / Update) frees them.
class CKComparedData;
struct QueuedSignal {
    CKComparedData* m_pData;   // +0x00
    QueuedSignal* m_pNext;     // +0x04
};
// 0x00236338 QueueTriggerSignals (k2000/system/EventNode.cpp): flags the starter datas and queues them.
void QueueTriggerSignals(CTriggerStarter* starter);
