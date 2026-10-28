// CKSrvTrigger.h - the trigger service (key 0x481, vtable 0xb20a68, size 0x38). Original unit:
// CKSrvTrigger.cpp (0x235188-0x2361c0). XXL2: K/KServices/KServiceTrigger/CKSrvTrigger.h, the same
// members in the same order, plus DotD's +0x10 and the named-reference array (+0x2c..+0x34).
//
// Its Load sizes one block for the level's trigger actions and starter datas; every CTriggerStarter
// the level's objects load then takes its slots from it (CTriggerStarter::Load).
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/services/IKService.h"

// XXL2 CMultiData: an action's parameter word. The parameter type decides what it holds (CKTrigger_LoadAction:
// a byte in all four bytes, an integer or float word, or an object reference); the reference is a pointer,
// so the union is wider than the PS3's word on 64-bit hosts.
union CMultiData {
    uint32_t m_ui32Value;         // types 0, 1, 2
    IKSerializable* m_pObject;    // type 3
};

// One trigger action (XXL2 CTriggerAction: CMultiData m_mdParam, IKSerializable* m_pObject, UInt16 m_mMsg).
// 0xc bytes on the PS3.
struct CTriggerAction {
    CMultiData m_mdParam;         // +0x00 (XXL2 CMultiData)
    IKSerializable* m_pObject;    // +0x04
    uint16_t m_mMsg;              // +0x08
    uint16_t m_pad0a;
};
DOTD_ASSERT_SIZE(CTriggerAction, 0xc);

// A pending starter-data node (8 bytes on the PS3; FreeListPool at TOC -0x3a0 in the original; here
// new/delete): the data and the next node. QueueTriggerSignals (0x236338) pushes them on m_unk10.
struct SPendingStarterData {
    IKSerializable* m_pData;         // +0x00 CKComparedData
    SPendingStarterData* m_pNext;    // +0x04
};

class CKSrvTrigger : public IKService {
public:
    DOTD_CLASS_KEY(kCategoryService, 0x12)
    DOTD_DECLARE_FACTORIES(CKSrvTrigger)

    // DotD only (not in XXL2): 0x104-byte records of an object reference and a name. Name ours.
    struct NamedRef {
        IKSerializable* m_object;  // +0x00
        char m_name[0x100];        // +0x04 length-prefixed string, read without a length limit
    };

    CKSrvTrigger();  // 0x00235368 CKSrvTrigger_Construct
    ~CKSrvTrigger() override {}

    void Destroy() override;  // vt+0x10 0x00235540 CKSrvTrigger_Destroy
    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x002359d8 CKSrvTrigger_Load
    void Start() override;                              // vt+0x50 0x2352d0 CKSrvTrigger_Start
    void Stop() override;                               // vt+0x68 0x235768 CKSrvTrigger_Stop
    void Pause() override {}                            // vt+0x70 0x2351e8  STUB(C1.6)
    void Resume() override {}                           // vt+0x78 0x2351f0  STUB(C1.6)
    void Update(IKTime* frameClock) override;           // vt+0x7c 0x235848 UpdateCKSrvTrigger
    int32_t InitializeService() override { return 1; }  // vt+0x94 0x235240
    void DestroyService() override {}                   // vt+0x98 0x235928  STUB(C1.6)

    IKSerializable* m_pRootDomain;              // +0x0c CKTriggerDomain; not set by the constructor
    SPendingStarterData* m_unk10;               // +0x10 the pending list (Start and Stop return its nodes to the pool); 0
    uint32_t m_ui32NbAllocatedActions;          // +0x14
    uint32_t m_ui32NbRequestedActions;          // +0x18
    uint32_t m_ui32NbAllocatedStarterDatas;     // +0x1c
    uint32_t m_ui32NbRequestedStarterDatas;     // +0x20
    CTriggerAction* m_aAllocatedActions;        // +0x24 the block (Mem_AllocAligned16); not set by the constructor
    IKSerializable** m_apAllocatedStarterDatas; // +0x28 CKComparedData* slots, after the actions in the block
    NamedRef** m_apNamedRefs;                   // +0x2c (Mem_AllocAligned16)
    uint32_t m_namedRefCapacity;                // +0x30 the constructor sets 1
    uint32_t m_namedRefCount;                   // +0x34
};
DOTD_ASSERT_SIZE(CKSrvTrigger, 0x38);
DOTD_ASSERT_OFFSET(CKSrvTrigger, m_ui32Priority, 0x08);
DOTD_ASSERT_OFFSET(CKSrvTrigger, m_pRootDomain, 0x0c);
DOTD_ASSERT_OFFSET(CKSrvTrigger, m_ui32NbAllocatedActions, 0x14);
DOTD_ASSERT_OFFSET(CKSrvTrigger, m_ui32NbRequestedStarterDatas, 0x20);
DOTD_ASSERT_OFFSET(CKSrvTrigger, m_apAllocatedStarterDatas, 0x28);
DOTD_ASSERT_OFFSET(CKSrvTrigger, m_namedRefCount, 0x34);
