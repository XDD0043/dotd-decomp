// CKHkSequenceMgr.h - a hook that plays sequences of steps (key 0x18c2, vtable 0xb27310, size 0x140).
// Original unit: CKHkSequenceMgr.cpp. No XXL2 class. The nested record names follow the Ghidra helper
// names (LoadSequenceEntry_maybe, LoadObjectRefRecord_maybe, LoadStepParamsRecord_maybe); every field
// name is a placeholder (C2.1 ports the constructor and Load only).
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/misc/CKHkActorBase.h"
#include "k2000/services/CTriggerStarter.h"
#include "k2000/util/TVector.h"

class CKHkSequenceMgr : public CKHkActorBase {
public:
    DOTD_CLASS_KEY(kCategoryHook, 0x63)
    DOTD_DECLARE_FACTORIES(CKHkSequenceMgr)

    // 0x1c bytes; read by 0x004665b8 CKHkSequenceMgr_LoadObjectRefRecord_maybe.
    struct ObjectRefRecord {
        uint8_t m_unk0;            // +0x00 read last
        uint8_t m_pad1[3];
        IKSerializable* m_pRef;    // +0x04 reference
        uint32_t m_unk8;           // +0x08
        uint8_t m_unkC;            // +0x0c
        uint8_t m_padD[3];
        uint32_t m_unk10;          // +0x10
        uint32_t m_unk14;          // +0x14
        uint32_t m_unk18;          // +0x18 never set by the Load path
        int32_t Load(IKFile* file, int32_t type);
    };

    // 0x28 bytes; read by 0x00465ad0 CKHkSequenceMgr_LoadStepParamsRecord_maybe.
    struct StepParams {
        uint8_t m_unk0;            // +0x00
        uint8_t m_pad1[3];
        uint32_t m_unk4;           // +0x04
        uint32_t m_unk8;           // +0x08
        uint32_t m_unkC;           // +0x0c
        uint32_t m_unk10;          // +0x10
        uint8_t m_unk14;           // +0x14
        uint8_t m_pad15[3];
        uint32_t m_unk18;          // +0x18
        uint8_t m_unk1c;           // +0x1c
        uint8_t m_pad1d[3];
        uint32_t m_unk20;          // +0x20
        float m_unk24;             // +0x24
        int32_t Load(IKFile* file, int32_t type);
    };

    // 0x18 bytes, the elements of SequenceEntry +0x60.
    struct EntryItem {
        IKSerializable* m_pRef;    // +0x00 reference
        uint8_t m_unk4;            // +0x04
        uint8_t m_pad5[3];
        uint32_t m_unk8;           // +0x08
        uint32_t m_unkC;           // +0x0c pushed as 1.0f (the TOC float at +0x56fc), then read
        uint32_t m_unk10;          // +0x10 never set by the Load path
        uint32_t m_unk14;          // +0x14
    };

    // 0xb4 bytes, the elements of +0x24 (stored inline in the vector's block).
    struct SequenceEntry {
        float m_unk0;                          // +0x00
        float m_unk4;                          // +0x04
        ObjectRefRecord m_recA;                // +0x08
        ObjectRefRecord m_recB;                // +0x24
        ObjectRefRecord m_recC;                // +0x40
        TVector<ObjectRefRecord, 1>* m_pvRecords;  // +0x5c Mem_CallocAligned16(1, 0xc)
        TVector<EntryItem, 1>* m_pvItems;      // +0x60 Mem_CallocAligned16(1, 0xc)
        uint32_t m_unk64;                      // +0x64
        uint32_t m_unk68;                      // +0x68
        StepParams m_stepParams;               // +0x6c
        uint32_t m_unk94;                      // +0x94 never set by the Load path
        uint8_t m_unk98;                       // +0x98
        uint8_t m_pad99[3];
        uint32_t m_unk9c;                      // +0x9c
        float m_unkA0;                         // +0xa0
        uint32_t m_unkA4;                      // +0xa4 never set by the Load path
        uint32_t m_unkA8;                      // +0xa8
        CKHkSequenceMgr* m_pOwner;             // +0xac
        uint8_t m_unkB0;                       // +0xb0
        uint8_t m_unkB1;                       // +0xb1
        uint8_t m_padB2[2];
        // 0x00462f60 CKHkSequenceMgr_InitSequenceEntry_maybe
        void Init(CKHkSequenceMgr* owner);
        // 0x004667a0 CKHkSequenceMgr_LoadSequenceEntry_maybe
        int32_t Load(IKFile* file, int32_t type);
    };

    // 0x18 bytes, the elements of +0x30 (only +0x00..+0x0b are written by the Load).
    struct MgrItem {
        IKSerializable* m_pRef;    // +0x00 reference
        uint8_t m_unk4;            // +0x04
        uint8_t m_pad5[3];
        uint32_t m_unk8;           // +0x08
        uint32_t m_unkC[3];        // +0x0c uninitialised (Mem_AllocAligned16 / Mem_ReallocAligned16)
    };

    // 0x14 bytes (OperatorNew): two references and one reference per +0x30 item.
    struct RefGroup {
        IKSerializable* m_pRef0;           // +0x00
        IKSerializable* m_pRef4;           // +0x04 read first
        TVector<IKSerializable*, 1> m_vRefs;  // +0x08
    };

    // 0x00463600 CKHkSequenceMgr_Create (inlined constructor, the same as 0x462600
    // CKHkSequenceMgr_Construct): the three vectors empty with capacity 1.
    CKHkSequenceMgr() {
        m_vEntries.m_pBlock = nullptr;
        m_vEntries.m_ui32NbElt = 1;
        m_vEntries.m_ui32NbUsedElt = 0;
        m_vItems.m_ui32NbElt = 1;
        m_vItems.m_pBlock = nullptr;
        m_vItems.m_ui32NbUsedElt = 0;
        m_vGroups.m_ui32NbElt = 1;
        m_vGroups.m_ui32NbUsedElt = 0;
        m_vGroups.m_pBlock = nullptr;
    }
    ~CKHkSequenceMgr() override {}

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x00466e38 CKHkSequenceMgr_Load
    void Start() override;  // vt+0x50 0x00465da0 CKHkSequenceMgr_Start
    void DetachHeroes();    // 0x004621e0 CKHkSequenceMgr_DetachHeroes_maybe

    IKSerializable* m_unk20;                // +0x20 reference
    TVector<SequenceEntry, 1> m_vEntries;   // +0x24
    TVector<MgrItem, 1> m_vItems;           // +0x30
    TVector<RefGroup*, 1> m_vGroups;        // +0x3c one per entry
    RefGroup* m_pGroup48;                   // +0x48
    IKSerializable* m_unk4c;                // +0x4c reference
    CTriggerStarter m_unk50;                // +0x50
    CTriggerStarter m_unk58;                // +0x58
    CTriggerStarter m_unk60;                // +0x60
    CTriggerStarter m_unk68;                // +0x68
    CTriggerStarter m_unk70;                // +0x70
    CTriggerStarter m_unk78;                // +0x78
    CTriggerStarter m_unk80;                // +0x80
    float m_unk88;                          // +0x88 every Load: 1.0f (type 0 then reads it)
    float m_unk8c;                          // +0x8c every Load: 1.0f
    float m_unk90;                          // +0x90 every Load: 0.1f
    float m_unk94;                          // +0x94 every Load: 0.1f
    float m_unk98[3];                       // +0x98 every Load: 0.5f, 0.2f, 0 (type 0: one 12-byte read)
    IKSerializable* m_unkA4;                // +0xa4 reference
    IKSerializable* m_unkA8;                // +0xa8 reference
    IKSerializable* m_unkAC;                // +0xac reference
    IKSerializable* m_unkB0;                // +0xb0 reference
    IKSerializable* m_unkB4;                // +0xb4 reference
    uint32_t m_unkB8[2];                    // +0xb8
    IKSerializable* m_apUnkC0[5];           // +0xc0 one contiguous read of 5 references
    uint8_t m_unkD4;                        // +0xd4 runtime (Start keeps its high nibble)
    uint8_t m_padD5[3];
    uint32_t m_unkD8;                       // +0xd8 runtime
    uint32_t m_unkDC;                       // +0xdc runtime
    uint8_t m_unkE0;                        // +0xe0 runtime
    uint8_t m_unkE1;                        // +0xe1 runtime
    uint8_t m_padE2[2];
    uint32_t m_unkE4;                       // +0xe4 runtime
    int32_t m_unkE8;                        // +0xe8 runtime: the running sequence's index, -1 none
    uint32_t m_unkEC;                       // +0xec runtime
    uint32_t m_unkF0;                       // +0xf0 runtime
    uint32_t m_unkF4;                       // +0xf4 runtime
    uint32_t m_unkF8;                       // +0xf8 runtime
    uint32_t m_unkFC[7];                    // +0xfc..+0x117 runtime
    uint8_t m_unk118;                       // +0x118 runtime
    uint8_t m_pad119[3];
    uint32_t m_unk11c;                      // +0x11c runtime (PostLoad 0x462548 clears it)
    uint32_t m_unk120[4];                   // +0x120 runtime
    uint8_t m_unk130;                       // +0x130 runtime
    uint8_t m_unk131;                       // +0x131 runtime (Start: 1)
    uint8_t m_pad132[2];
    uint32_t m_unk134;                      // +0x134 runtime (Start: 0)
    uint32_t m_unk138;                      // +0x138 runtime (Start: 0)
    uint8_t m_unk13c[4];                    // +0x13c runtime (PostLoad clears the four bytes)
};
DOTD_ASSERT_SIZE(CKHkSequenceMgr, 0x140);
DOTD_ASSERT_SIZE(CKHkSequenceMgr::ObjectRefRecord, 0x1c);
DOTD_ASSERT_SIZE(CKHkSequenceMgr::StepParams, 0x28);
DOTD_ASSERT_SIZE(CKHkSequenceMgr::EntryItem, 0x18);
DOTD_ASSERT_SIZE(CKHkSequenceMgr::SequenceEntry, 0xb4);
DOTD_ASSERT_SIZE(CKHkSequenceMgr::MgrItem, 0x18);
DOTD_ASSERT_SIZE(CKHkSequenceMgr::RefGroup, 0x14);
DOTD_ASSERT_OFFSET(CKHkSequenceMgr::SequenceEntry, m_recB, 0x24);
DOTD_ASSERT_OFFSET(CKHkSequenceMgr::SequenceEntry, m_pvRecords, 0x5c);
DOTD_ASSERT_OFFSET(CKHkSequenceMgr::SequenceEntry, m_stepParams, 0x6c);
DOTD_ASSERT_OFFSET(CKHkSequenceMgr::SequenceEntry, m_unk98, 0x98);
DOTD_ASSERT_OFFSET(CKHkSequenceMgr::SequenceEntry, m_unkA8, 0xa8);
DOTD_ASSERT_OFFSET(CKHkSequenceMgr::SequenceEntry, m_unkB1, 0xb1);
DOTD_ASSERT_OFFSET(CKHkSequenceMgr, m_unk20, 0x20);
DOTD_ASSERT_OFFSET(CKHkSequenceMgr, m_vEntries, 0x24);
DOTD_ASSERT_OFFSET(CKHkSequenceMgr, m_vItems, 0x30);
DOTD_ASSERT_OFFSET(CKHkSequenceMgr, m_vGroups, 0x3c);
DOTD_ASSERT_OFFSET(CKHkSequenceMgr, m_pGroup48, 0x48);
DOTD_ASSERT_OFFSET(CKHkSequenceMgr, m_unk4c, 0x4c);
DOTD_ASSERT_OFFSET(CKHkSequenceMgr, m_unk50, 0x50);
DOTD_ASSERT_OFFSET(CKHkSequenceMgr, m_unk80, 0x80);
DOTD_ASSERT_OFFSET(CKHkSequenceMgr, m_unk88, 0x88);
DOTD_ASSERT_OFFSET(CKHkSequenceMgr, m_unk98, 0x98);
DOTD_ASSERT_OFFSET(CKHkSequenceMgr, m_unkA4, 0xa4);
DOTD_ASSERT_OFFSET(CKHkSequenceMgr, m_unkB4, 0xb4);
DOTD_ASSERT_OFFSET(CKHkSequenceMgr, m_apUnkC0, 0xc0);
DOTD_ASSERT_OFFSET(CKHkSequenceMgr, m_unk11c, 0x11c);
