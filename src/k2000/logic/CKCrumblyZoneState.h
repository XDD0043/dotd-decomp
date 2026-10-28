// CKCrumblyZoneState.h - one state of a crumbly zone (key 0xa40c, vtable 0xb25758, size 0x4c). Original
// unit: CKCrumblyZoneState.cpp. DotD only (no XXL2 class); the names are ours, the reference types from
// the files (struct draft).
#pragma once
#include <cstdint>

#include "k2000/core/IKSerializable.h"
#include "k2000/core/Layout.h"
#include "k2000/util/TVector.h"

class CKCrumblyZoneState : public IKSerializable {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x290)
    DOTD_DECLARE_FACTORIES(CKCrumblyZoneState)

    // One entry (0x14 bytes on the PS3): three bytes, a word and three words (a vector _maybe).
    struct Entry {
        uint8_t m_unk00;      // +0x00
        uint8_t m_unk01;      // +0x01
        uint8_t m_unk02;      // +0x02
        uint8_t m_pad03;
        uint32_t m_unk04;     // +0x04
        uint32_t m_unk08[3];  // +0x08 read as 12 bytes, then each word swapped
    };

    CKCrumblyZoneState();  // 0x00403770 CKCrumblyZoneState_Construct (inlined in Create)
    ~CKCrumblyZoneState() override {}

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x00404d98 CKCrumblyZoneState_Load
    // 0x004038f0 CKCrumblyZoneState_SetVolumesDamage_maybe (not virtual; the damage is its caller's second
    // argument): the bounding component's volumes all take `damage`.
    void SetVolumesDamage(IKSerializable* damage);

    IKSerializable* m_pZone;         // +0x04 CKHkS08CrumblyZoneMultiState in the files
    float m_unk08;                   // +0x08 not loaded; PostLoad sets 0
    float m_unk0c;                   // +0x0c
    TVector<Entry, 1> m_vEntries;    // +0x10 the constructor: null, capacity 1, 0 used
    IKSerializable* m_pGroundCpnt;   // +0x1c CKGroundCpnt in the files
    IKSerializable* m_pBoundingCpnt; // +0x20 CKBoundingCpnt in the files
    uint32_t m_unk24;                // +0x24 not loaded; the constructor sets 0
    IKSerializable* m_pSound;        // +0x28 CKSoundDictionaryID in the files
    float m_unk2c;                   // +0x2c
    float m_unk30;                   // +0x30
    IKSerializable* m_pBonusData;    // +0x34 CKBonusData in the files
    uint32_t m_unk38;                // +0x38 read before +0x34
    void* m_unk3c;                   // +0x3c not loaded
    float m_unk40;                   // +0x40
    int32_t m_unk44;                 // +0x44
    int32_t m_unk48;                 // +0x48
};
DOTD_ASSERT_SIZE(CKCrumblyZoneState::Entry, 0x14);
DOTD_ASSERT_SIZE(CKCrumblyZoneState, 0x4c);
DOTD_ASSERT_OFFSET(CKCrumblyZoneState, m_pZone, 0x04);
DOTD_ASSERT_OFFSET(CKCrumblyZoneState, m_unk0c, 0x0c);
DOTD_ASSERT_OFFSET(CKCrumblyZoneState, m_vEntries, 0x10);
DOTD_ASSERT_OFFSET(CKCrumblyZoneState, m_pGroundCpnt, 0x1c);
DOTD_ASSERT_OFFSET(CKCrumblyZoneState, m_pBoundingCpnt, 0x20);
DOTD_ASSERT_OFFSET(CKCrumblyZoneState, m_unk24, 0x24);
DOTD_ASSERT_OFFSET(CKCrumblyZoneState, m_pSound, 0x28);
DOTD_ASSERT_OFFSET(CKCrumblyZoneState, m_pBonusData, 0x34);
DOTD_ASSERT_OFFSET(CKCrumblyZoneState, m_unk38, 0x38);
DOTD_ASSERT_OFFSET(CKCrumblyZoneState, m_unk40, 0x40);
DOTD_ASSERT_OFFSET(CKCrumblyZoneState, m_unk48, 0x48);
