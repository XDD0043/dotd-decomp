// CKSrvTrigger.h - the trigger service (key 0x481, vtable 0xb20a68, size 0x38). Original unit:
// CKSrvTrigger.cpp (0x235188-0x2361c0). XXL2: K/KServices/KServiceTrigger/CKSrvTrigger.h, the same
// members in the same order, plus DotD's +0x10 and the named-reference array (+0x2c..+0x34).
//
// Its Load sizes one block for the level's trigger actions and starter datas; every CTriggerStarter
// the level's objects load then takes its slots from it (CTriggerStarter::Load).
#pragma once
#include <cstdint>
#include <cstring>

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

// A receiver's read of the parameter word at a PS3 byte offset (the trigger message's `data` is the action, its
// word at +0, held natively here): the original's lbz 3(r5) / lbz 0(r5) / lhz 2(r5) on the big-endian word are its
// low byte / high byte / low halfword. A byte parameter (type 0, the byte in all four bytes) gives the byte either
// way; a word parameter (type 1) only this way (C2.8 lvl030 waves: `bytes[3]` of the native word read the high byte,
// so LVL030's wave triggers' 0xd00 phase 5 set phase 0 and the second wave never spawned).
inline uint32_t TriggerParamWord(const void* data) {
    uint32_t word = 0;
    std::memcpy(&word, data, 4);
    return word;
}
inline uint8_t TriggerParamByte3(const void* data) { return static_cast<uint8_t>(TriggerParamWord(data)); }
inline uint8_t TriggerParamByte0(const void* data) { return static_cast<uint8_t>(TriggerParamWord(data) >> 24); }
inline uint16_t TriggerParamHalf2(const void* data) { return static_cast<uint16_t>(TriggerParamWord(data)); }

// A pending starter-data node (8 bytes on the PS3; FreeListPool at TOC -0x3a0 in the original; here
// new/delete): the data and the next node. QueueTriggerSignals (0x236338) pushes them on m_unk10.
struct SPendingStarterData {
    IKSerializable* m_pData;         // +0x00 CKComparedData
    SPendingStarterData* m_pNext;    // +0x04
};

class CKSrvTrigger : public IKService {
public:
    DOTD_CLASS_KEY(kCategoryService, 0x12)
    int32_t IsKindOfClass(uint32_t key) override {  // vt+0x08 0x9b8950
        return key == 0x481 || key == 0x1 || key == 0x3fe || key == 0xc;
    }
    DOTD_DECLARE_FACTORIES(CKSrvTrigger)

    // DotD only (not in XXL2): 0x104-byte records of an object reference and a name. Name ours.
    struct NamedRef {
        IKSerializable* m_object;  // +0x00
        char m_name[0x100];        // +0x04 length-prefixed string, read without a length limit
    };

    CKSrvTrigger();  // 0x00235368 CKSrvTrigger_Construct
    ~CKSrvTrigger() override;  // 0x00235d30 CKSrvTrigger_Destructor

    void Destroy() override;  // vt+0x10 0x00235540 CKSrvTrigger_Destroy
    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x002359d8 CKSrvTrigger_Load
    void Start() override;                              // vt+0x50 0x2352d0 CKSrvTrigger_Start
    void Restart() override;                            // vt+0x54 0x2357d8 CKSrvTrigger_Restart
    void Stop() override;                               // vt+0x68 0x235768 CKSrvTrigger_Stop
    void SetDefaultState(int32_t flag) override;        // vt+0x38 0x2351f8: the root domain's
    void Pause() override {}                            // vt+0x70 0x2351e8 CKSrvTrigger_Pause (empty)
    void Resume() override {}                           // vt+0x78 0x2351f0 CKSrvTrigger_Resume (empty)
    void Update(IKTime* frameClock) override;           // vt+0x7c 0x235848 UpdateCKSrvTrigger
    int32_t InitializeService() override { return 1; }  // vt+0x94 0x235240
    // vt+0x98 0x00235928 CKSrvTrigger_DestroyService: the named references deleted (the last first) and their array
    // freed, as Destroy does (the action block stays).
    void DestroyService() override;

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

// 0x00235660 FireTriggerActionsByIndex_maybe: named reference `index`'s CKTrigger fired by hand (no caller in the original).
void FireTriggerActionsByIndex(CKSrvTrigger* service, int32_t index);
