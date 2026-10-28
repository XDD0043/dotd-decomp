// CKHkLinkedBeacon.h - a beacon of a linked-beacon path (key 0x1002, vtable 0xb26cb8, size 0xf4). Original
// unit: CKHkLinkedBeacon.cpp. No XXL2 class. Field types from the Ghidra struct draft (live samples).
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/math/CMatrix34.h"
#include "k2000/misc/CKHkActorBase.h"
#include "k2000/services/CTriggerStarter.h"

class CKHkLinkedBeacon : public CKHkActorBase {
public:
    DOTD_CLASS_KEY(kCategoryHook, 0x40)
    DOTD_DECLARE_FACTORIES(CKHkLinkedBeacon)

    // A link record (0xc bytes, OperatorNew'd and zeroed one by one by Load, then read by LoadLinkRecord).
    struct LinkRecord {
        IKSerializable* m_pTarget;  // +0x00 a reference_maybe
        uint8_t m_unk4;             // +0x04 read first
        uint8_t m_unk5;             // +0x05 read third
        uint8_t m_unk6;             // +0x06 read second
        uint8_t m_unk7;             // +0x07 read fourth
        uint8_t m_unk8;             // +0x08 read last
        uint8_t m_unk9;             // +0x09 run-time (Restart clears it)
        uint8_t m_padA[2];
    };

    CKHkLinkedBeacon() {}  // 0x0044bbd8 CKHkLinkedBeacon_Create: the CKHkActorBase defaults only
    ~CKHkLinkedBeacon() override {}

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x0044c240 CKHkLinkedBeacon_Load
    void SetDefaultState(int32_t flag) override;  // vt+0x38 0x0044bb58 CKHkLinkedBeacon_SetDefaultState
    void Start() override;                        // vt+0x50 0x0044b788 CKHkLinkedBeacon_Start
    void Restart() override;                      // vt+0x54 0x0044bf20 CKHkLinkedBeacon_Restart
    // 0x0044af18 CKHkLinkedBeacon_ShowInputIcon_maybe (not virtual). STUB(C2.2): as for the hero activator,
    // the input-icon effect cannot be acquired yet (services), so m_pInputIconFx is always null.
    void ShowInputIcon(int32_t on);
    // 0x0044c0b8 CKHkLinkedBeacon_LoadLinkRecord_maybe (this unused; the last argument is 0 at the call).
    void LoadLinkRecord(IKFile* file, LinkRecord* record, int32_t unused);

    CVector3 m_unk20;                 // +0x20 a position_maybe (one 12-byte read, each word swapped)
    CVector3 m_unk2C;                 // +0x2c a direction_maybe (one 12-byte read)
    uint32_t m_unk38;                 // +0x38
    float m_unk3C;                    // +0x3c
    uint32_t m_unk40;                 // +0x40
    uint32_t m_unk44;                 // +0x44
    float m_unk48;                    // +0x48 (LVL010: 360)
    float m_unk4C;                    // +0x4c (LVL010: 100)
    uint8_t m_unk50;                  // +0x50
    uint8_t m_pad51[3];
    IKSerializable* m_unk54;          // +0x54 CKHkLinkedBeacon* (struct draft)
    IKSerializable* m_unk58;          // +0x58 CKHkLinkedBeacon* (struct draft)
    int32_t m_unk5C;                  // +0x5c the count of +0x60
    IKSerializable** m_apUnk60;       // +0x60 OperatorNewArray'd references
    IKSerializable* m_unk64;          // +0x64 CKLinkedBeaconSeq* (struct draft); 0 without bit 0x10 of m_bitArray
    uint8_t m_unk68;                  // +0x68 0 without bit 0x10
    uint8_t m_pad69[3];
    float m_unk6C;                    // +0x6c 0.8f without bit 0x10
    float m_unk70;                    // +0x70
    uint8_t m_unk74;                  // +0x74
    uint8_t m_pad75[3];
    CVector3 m_unk78;                 // +0x78 a position_maybe (one 12-byte read)
    uint32_t m_unk84;                 // +0x84
    CTriggerStarter m_unk88;          // +0x88
    CTriggerStarter m_unk90;          // +0x90
    CTriggerStarter m_unk98;          // +0x98
    CTriggerStarter m_unkA0;          // +0xa0
    CTriggerStarter m_unkA8;          // +0xa8
    IKSerializable* m_unkB0;          // +0xb0
    int32_t m_unkB4;                  // +0xb4 the count of +0xb8
    LinkRecord** m_apLinks;           // +0xb8 OperatorNewArray'd record pointers
    uint8_t m_unkBC;                  // +0xbc
    uint8_t m_padBD[3];
    IKSerializable* m_unkC0;          // +0xc0
    IKSerializable* m_unkC4;          // +0xc4
    IKSerializable* m_unkC8;          // +0xc8 CKKLBCharacterSparx* (struct draft)
    uint32_t m_unkCC[7];              // +0xcc..+0xe7 runtime (not set by Create or Load)
    IKSerializable* m_pSekens;        // +0xe8 runtime: a CKSekensLauncherCpnt* (Restart stops its sekens)
    uint8_t m_unkEC;                  // +0xec runtime (Restart: 0xff)
    uint8_t m_padED[3];
    IKSerializable* m_pInputIconFx;   // +0xf0 runtime: the input-icon effect (CKInputIconNodeFx*), or null
};
DOTD_ASSERT_SIZE(CKHkLinkedBeacon::LinkRecord, 0xc);
DOTD_ASSERT_SIZE(CKHkLinkedBeacon, 0xf4);
DOTD_ASSERT_OFFSET(CKHkLinkedBeacon, m_unk20, 0x20);
DOTD_ASSERT_OFFSET(CKHkLinkedBeacon, m_unk2C, 0x2c);
DOTD_ASSERT_OFFSET(CKHkLinkedBeacon, m_unk38, 0x38);
DOTD_ASSERT_OFFSET(CKHkLinkedBeacon, m_unk3C, 0x3c);
DOTD_ASSERT_OFFSET(CKHkLinkedBeacon, m_unk48, 0x48);
DOTD_ASSERT_OFFSET(CKHkLinkedBeacon, m_unk50, 0x50);
DOTD_ASSERT_OFFSET(CKHkLinkedBeacon, m_unk54, 0x54);
DOTD_ASSERT_OFFSET(CKHkLinkedBeacon, m_unk5C, 0x5c);
DOTD_ASSERT_OFFSET(CKHkLinkedBeacon, m_apUnk60, 0x60);
DOTD_ASSERT_OFFSET(CKHkLinkedBeacon, m_unk64, 0x64);
DOTD_ASSERT_OFFSET(CKHkLinkedBeacon, m_unk68, 0x68);
DOTD_ASSERT_OFFSET(CKHkLinkedBeacon, m_unk6C, 0x6c);
DOTD_ASSERT_OFFSET(CKHkLinkedBeacon, m_unk70, 0x70);
DOTD_ASSERT_OFFSET(CKHkLinkedBeacon, m_unk74, 0x74);
DOTD_ASSERT_OFFSET(CKHkLinkedBeacon, m_unk78, 0x78);
DOTD_ASSERT_OFFSET(CKHkLinkedBeacon, m_unk84, 0x84);
DOTD_ASSERT_OFFSET(CKHkLinkedBeacon, m_unk88, 0x88);
DOTD_ASSERT_OFFSET(CKHkLinkedBeacon, m_unkA8, 0xa8);
DOTD_ASSERT_OFFSET(CKHkLinkedBeacon, m_unkB0, 0xb0);
DOTD_ASSERT_OFFSET(CKHkLinkedBeacon, m_unkB4, 0xb4);
DOTD_ASSERT_OFFSET(CKHkLinkedBeacon, m_apLinks, 0xb8);
DOTD_ASSERT_OFFSET(CKHkLinkedBeacon, m_unkBC, 0xbc);
DOTD_ASSERT_OFFSET(CKHkLinkedBeacon, m_unkC0, 0xc0);
DOTD_ASSERT_OFFSET(CKHkLinkedBeacon, m_unkC8, 0xc8);
