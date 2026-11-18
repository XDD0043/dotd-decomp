// CKHkScriptedNPC.h - a scripted NPC hook (key 0x32c2, vtable 0xb2ff48, size 0x84; library-TOC code).
// Original unit: k2000/ui/CKHkScriptedNPC_2.cpp. No XXL2 class. Derives from CKHkActorBase (0xd82): its
// constructor and Load call CKHkActorBase_d82_maybe_Construct/_Load through TocBridge stubs.
//
// The NPC runs behaviour blocks (+0x34, KBase9C8C: CKBhvBlockAnimation in LVL010) one after the other for its user
// (+0x2c, a CKNPCBehaviourBlockUser): the next block (+0x64) is prepared (vt+0xf8), entered when it and the current
// one (+0x60) allow it (vt+0xf4), updated each frame while active (+0x4c), and when it reports its end the NPC queues
// its signals (+0x78) and chains the block the table +0x40 names. Scripts move it with the messages 0x996..0x999 and
// switch it on / off, show / hide it through the actor messages 0x908..0x90f.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/math/CMatrix34.h"
#include "k2000/memory/Mem.h"
#include "k2000/misc/CKHkActorBase.h"
#include "k2000/services/CTriggerStarter.h"
#include "k2000/util/TVector.h"

class KBase9C8C;

class CKHkScriptedNPC : public CKHkActorBase {
public:
    DOTD_CLASS_KEY(kCategoryHook, 0xcb)
    DOTD_DECLARE_FACTORIES(CKHkScriptedNPC)
    // vt+0x40 0x005c8b58 CKHkScriptedNPC_GetInfo (Ghidra: _ResolveTriggerProperty): the trigger values 0x99 (+0x60) and
    // 0x9b (+0x58), integers.
    int32_t GetInfo(IKInfo* info, int32_t request) override;

    // An element of the +0x40 vector (OperatorNew(8), no constructor): per block, what follows it.
    struct Entry {
        uint8_t m_unk0;    // +0x00 the next block starts on its own when this one ends (QueueSignalsAndChainNextBlock)
        uint8_t m_pad1[3];
        uint32_t m_unk4;   // +0x04 the block prepared when this one is entered (-2: the following one)
    };

    // 0x005c9338 CKHkScriptedNPC_Create (inlined constructor, = 0x005c81d0 CKHkScriptedNPC_Construct):
    // CKHkActorBase's, then the two vectors {block 0, capacity 1, length 0}.
    CKHkScriptedNPC() {
        m_vpUnk34.m_pBlock = nullptr;
        m_vpUnk34.m_ui32NbElt = 1;
        m_vpUnk34.m_ui32NbUsedElt = 0;
        m_vpUnk40.m_ui32NbElt = 1;
        m_vpUnk40.m_ui32NbUsedElt = 0;
        m_vpUnk40.m_pBlock = nullptr;
    }
    // 0x005c91a0 CKHkScriptedNPC_Destructor (0x5c9050 the base one, 0x5c90f0 deleting): the two vectors' blocks freed
    // (Mem_FreeAligned16), their lengths and blocks cleared; then CKHkActorBase's.
    ~CKHkScriptedNPC() override {
        if (m_vpUnk40.m_pBlock != nullptr) Mem_FreeAligned16(m_vpUnk40.m_pBlock);
        m_vpUnk40.m_ui32NbUsedElt = 0;
        m_vpUnk40.m_pBlock = nullptr;
        if (m_vpUnk34.m_pBlock != nullptr) Mem_FreeAligned16(m_vpUnk34.m_pBlock);
        m_vpUnk34.m_ui32NbUsedElt = 0;
        m_vpUnk34.m_pBlock = nullptr;
    }
    // vt+0x10 0x005c82e8 CKHkScriptedNPC_Destroy (Ghidra: _ClearReferences): CKHkActorBase_d82_maybe_Destroy 0x3f6e08 (its
    // vt+0xc0, KStub_Nop_9c0bc8 here), then the +0x40 entries deleted, counted by the blocks' length (+0x3c).
    void Destroy() override;

    // vt+0x1c 0x005c7f30 CKHkScriptedNPC_MessageProc (Ghidra: _HandleMessage).
    int32_t MessageProc(uint16_t message, void* data) override;
    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x005c9560 CKHkScriptedNPC_Load
    int32_t PostLoad(int32_t type) override;      // vt+0x30 0x005c7e48 CKHkScriptedNPC_PostLoad
    void SetDefaultState(int32_t flag) override;  // vt+0x38 0x005c7e08 CKHkScriptedNPC_SetDefaultState
    void Start() override;                        // vt+0x50 0x005c7da8 CKHkScriptedNPC_ResetRuntime
    void Restart() override;                      // vt+0x54 0x005c8d30 CKHkScriptedNPC_ReinitRuntime
    void Stop() override;                         // vt+0x68 0x005c7cd0 CKHkScriptedNPC_OnLevelExit_maybe
    void Pause() override {}                      // vt+0x70 0x005c7ca8 CKHkScriptedNPC_Pause (KStub_Nop_3f6e58)
    void Resume() override {}                     // vt+0x78 0x005c7c80 CKHkScriptedNPC_Resume (KStub_Nop_3f6e60)
    void Update(IKTime* clock) override;          // vt+0x7c 0x005c93b8 CKHkScriptedNPC_Update
    void VfA0() override;                         // vt+0xa0 0x005c85d8 CKHkScriptedNPC_OnActivate
    void VfA4() override;                         // vt+0xa4 0x005c84a8 CKHkScriptedNPC_OnDeactivate
    void ApplyStatePreset(int32_t state) override;  // vt+0xc8 0x005c7a50 CKHkScriptedNPC_vfC8
    void SetEnabled(int32_t enabled) override;    // vt+0xcc 0x005c8a08 CKHkScriptedNPC_vfCC
    // vt+0xd0 0x009c0c18 CKHkActorBase_d82_maybe_SetVisible: the actor base's (not overridden).
    // vt+0xd4 0x005c8ab0 CKHkScriptedNPC_vfD4: as vt+0xcc (the second argument is not used).
    void VfD4(int32_t enabled, int32_t unused) override;
    // vt+0xf0 0x005c7a88 CKHkScriptedNPC_vfF0: the cinematic stream the current block plays (+0x28).
    void SetStream(IKSerializable* stream) { m_pUnk28 = stream; }
    // vt+0xf4 0x005c8780 CKHkScriptedNPC_TrySwitchBlock_maybe (the argument, a clock or 0, is not used).
    uint8_t TrySwitchBlock();
    // vt+0xf8 0x005c83c8 CKHkScriptedNPC_vfF8: block `index` prepared as the next one.
    void PrepareBlock(uint32_t index);
    // vt+0xfc 0x005c8360 CKHkScriptedNPC_vfFC: block `index`'s preparation undone.
    void UnprepareBlock(uint32_t index);
    // vt+0x100 0x005c7b68 CKHkScriptedNPC_vf100: the prepared block's preparation undone unless it is the current one.
    void UnprepareNext();
    // 0x005c8f28 CKHkScriptedNPC_QueueSignalsAndChainNextBlock_maybe: the current block reached its end.
    void QueueSignalsAndChainNextBlock();
    // 0x005c8c88 CKHkScriptedNPC_GetAnchorPosition_maybe: the hot spot's (+0x30) world position, else the node's
    // frame position. The sound marks' position callback (the index is not used).
    static CVector3* GetAnchorPosition(CVector3* out, IKSerializable* npc, uint32_t index);

    IKSerializable* m_pUnk20;                   // +0x20 reference: a CKMarkedFX
    IKSerializable* m_pUnk24;                   // +0x24 reference
    IKSerializable* m_pUnk28;                   // +0x28 runtime (not set by Create or Load): the stream (vt+0xf0)
    IKSerializable* m_pUnk2C;                   // +0x2c reference: the blocks' user (a CKNPCBehaviourBlockUser)
    IKSerializable* m_pUnk30;                   // +0x30 reference: a CSGHotSpot
    TVector<KBase9C8C*, 1> m_vpUnk34;           // +0x34 the behaviour blocks (Load)
    TVector<Entry*, 1> m_vpUnk40;               // +0x40 (Load) one per block
    uint8_t m_unk4C;                            // +0x4c runtime: active (the blocks run)
    uint8_t m_unk4D;                            // +0x4d
    uint8_t m_unk4E;                            // +0x4e
    uint8_t m_unk4F;                            // +0x4f
    uint8_t m_unk50;                            // +0x50 runtime: shown (the node's hidden bit is its negation)
    uint8_t m_unk51;                            // +0x51
    uint8_t m_unk52;                            // +0x52
    uint8_t m_unk53;                            // +0x53
    uint8_t m_unk54;                            // +0x54 runtime (ResetRuntime, ReinitRuntime: 0)
    uint8_t m_pad55[3];
    uint32_t m_unk58;                           // +0x58 runtime (ResetRuntime: -1): the block that queued its signals
    uint32_t m_unk5C;                           // +0x5c runtime: the prepared block (-1 none)
    uint32_t m_unk60;                           // +0x60 runtime: the current block (-1 none)
    uint32_t m_unk64;                           // +0x64 runtime: the next block (-1 none)
    uint8_t m_unk68;                            // +0x68 runtime: the current block ended (no more updates)
    uint8_t m_pad69[3];
    CVector3 m_unk6C;                           // +0x6c runtime: the node's position at OnActivate
    CTriggerStarter m_tsUnk78;                  // +0x78
    uint8_t m_unk80;                            // +0x80 runtime (ResetRuntime: 0): message 0x999 set the next block
    uint8_t m_pad81[3];
};
DOTD_ASSERT_SIZE(CKHkScriptedNPC, 0x84);
DOTD_ASSERT_OFFSET(CKHkScriptedNPC, m_pUnk20, 0x20);
DOTD_ASSERT_OFFSET(CKHkScriptedNPC, m_pUnk24, 0x24);
DOTD_ASSERT_OFFSET(CKHkScriptedNPC, m_pUnk28, 0x28);
DOTD_ASSERT_OFFSET(CKHkScriptedNPC, m_pUnk2C, 0x2c);
DOTD_ASSERT_OFFSET(CKHkScriptedNPC, m_pUnk30, 0x30);
DOTD_ASSERT_OFFSET(CKHkScriptedNPC, m_vpUnk34, 0x34);
DOTD_ASSERT_OFFSET(CKHkScriptedNPC, m_vpUnk40, 0x40);
DOTD_ASSERT_OFFSET(CKHkScriptedNPC, m_unk4D, 0x4d);
DOTD_ASSERT_OFFSET(CKHkScriptedNPC, m_unk4E, 0x4e);
DOTD_ASSERT_OFFSET(CKHkScriptedNPC, m_unk51, 0x51);
DOTD_ASSERT_OFFSET(CKHkScriptedNPC, m_unk58, 0x58);
DOTD_ASSERT_OFFSET(CKHkScriptedNPC, m_unk60, 0x60);
DOTD_ASSERT_OFFSET(CKHkScriptedNPC, m_unk68, 0x68);
DOTD_ASSERT_OFFSET(CKHkScriptedNPC, m_unk6C, 0x6c);
DOTD_ASSERT_OFFSET(CKHkScriptedNPC, m_tsUnk78, 0x78);
