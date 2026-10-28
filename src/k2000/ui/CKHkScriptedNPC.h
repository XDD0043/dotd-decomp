// CKHkScriptedNPC.h - a scripted NPC hook (key 0x32c2, vtable 0xb2ff48, size 0x84; library-TOC code).
// Original unit: k2000/ui/CKHkScriptedNPC_2.cpp. No XXL2 class. Derives from CKHkActorBase (0xd82): its
// constructor and Load call CKHkActorBase_d82_maybe_Construct/_Load through TocBridge stubs.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/misc/CKHkActorBase.h"
#include "k2000/services/CTriggerStarter.h"
#include "k2000/util/TVector.h"

class CKHkScriptedNPC : public CKHkActorBase {
public:
    DOTD_CLASS_KEY(kCategoryHook, 0xcb)
    DOTD_DECLARE_FACTORIES(CKHkScriptedNPC)

    // An element of the +0x40 vector (OperatorNew(8), no constructor).
    struct Entry {
        uint8_t m_unk0;    // +0x00
        uint8_t m_pad1[3];
        uint32_t m_unk4;   // +0x04
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
    ~CKHkScriptedNPC() override {}

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x005c9560 CKHkScriptedNPC_Load
    void SetDefaultState(int32_t flag) override;  // vt+0x38 0x005c7e08 CKHkScriptedNPC_SetDefaultState
    void Start() override;                        // vt+0x50 0x005c7da8 CKHkScriptedNPC_ResetRuntime

    IKSerializable* m_pUnk20;                   // +0x20 reference
    IKSerializable* m_pUnk24;                   // +0x24 reference
    uint32_t m_unk28;                           // +0x28 runtime (not set by Create or Load)
    IKSerializable* m_pUnk2C;                   // +0x2c reference
    IKSerializable* m_pUnk30;                   // +0x30 reference
    TVector<IKSerializable*, 1> m_vpUnk34;      // +0x34 references (Load)
    TVector<Entry*, 1> m_vpUnk40;               // +0x40 (Load)
    uint8_t m_unk4C;                            // +0x4c runtime
    uint8_t m_unk4D;                            // +0x4d
    uint8_t m_unk4E;                            // +0x4e
    uint8_t m_unk4F;                            // +0x4f
    uint8_t m_unk50;                            // +0x50 runtime
    uint8_t m_unk51;                            // +0x51
    uint8_t m_unk52;                            // +0x52
    uint8_t m_unk53;                            // +0x53
    uint8_t m_unk54;                            // +0x54 runtime (ResetRuntime: 0)
    uint8_t m_pad55[3];
    uint32_t m_unk58;                           // +0x58 runtime (ResetRuntime: -1)
    uint32_t m_unk5C[7];                        // +0x5c..+0x77 runtime
    CTriggerStarter m_tsUnk78;                  // +0x78
    uint8_t m_unk80;                            // +0x80 runtime (ResetRuntime: 0)
    uint8_t m_pad81[3];
};
DOTD_ASSERT_SIZE(CKHkScriptedNPC, 0x84);
DOTD_ASSERT_OFFSET(CKHkScriptedNPC, m_pUnk20, 0x20);
DOTD_ASSERT_OFFSET(CKHkScriptedNPC, m_pUnk24, 0x24);
DOTD_ASSERT_OFFSET(CKHkScriptedNPC, m_pUnk2C, 0x2c);
DOTD_ASSERT_OFFSET(CKHkScriptedNPC, m_pUnk30, 0x30);
DOTD_ASSERT_OFFSET(CKHkScriptedNPC, m_vpUnk34, 0x34);
DOTD_ASSERT_OFFSET(CKHkScriptedNPC, m_vpUnk40, 0x40);
DOTD_ASSERT_OFFSET(CKHkScriptedNPC, m_unk4D, 0x4d);
DOTD_ASSERT_OFFSET(CKHkScriptedNPC, m_unk4E, 0x4e);
DOTD_ASSERT_OFFSET(CKHkScriptedNPC, m_unk51, 0x51);
DOTD_ASSERT_OFFSET(CKHkScriptedNPC, m_tsUnk78, 0x78);
