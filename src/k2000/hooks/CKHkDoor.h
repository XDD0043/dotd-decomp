// CKHkDoor.h - a door mechanism (key 0x1942, vtable 0xb25d10, size 0x80). Original unit: CKHkDoor.cpp
// (0x416710-0x419a18). XXL2 has CKHkDoor (K/KMeca/Door, base IKHkMeca); DotD's derives from CKHkActorBase and
// its Load differs (an extra word before the detector count, other references). XXL2 names are used where
// the PS3 Load reads the same thing in the same place: the detector count and the two detector arrays
// allocated together, the 16-bit auto-action bits read just before the count, the two trigger starters.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/misc/CKHkActorBase.h"
#include "k2000/services/CTriggerStarter.h"

class CKHkDoor : public CKHkActorBase {
public:
    DOTD_CLASS_KEY(kCategoryHook, 0x65)
    DOTD_DECLARE_FACTORIES(CKHkDoor)

    CKHkDoor() {}  // 0x004174f0 CKHkDoor_Create: the CKHkActorBase defaults only
    ~CKHkDoor() override {}

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x00419150 CKHkDoor_Load
    void SetDefaultState(int32_t flag) override;  // vt+0x38 0x00416998 CKHkDoor_SetDefaultState
    void Start() override;                        // vt+0x50 0x00417358 CKHkDoor_Start
    // vt+0xc8 0x004179a8 CKHkDoor_ApplyStatePreset_maybe: bits 6/7 (state 0) or 8/9 (state 1) of the flags
    // are the preset's "initially open" and "applies" bits (XXL2's two door states).
    void ApplyStatePreset(int32_t state) override;

    uint32_t m_unk20[8];                   // +0x20 runtime (not set by Create or Load)
    uint8_t m_ui8NbOfDectector;            // +0x40 XXL2 m_ui8NbOfDectector (sic)
    uint8_t m_pad41;
    uint16_t m_baAutoAction;               // +0x42 XXL2 CBitArray16 m_baAutoAction
    float m_unk44;                         // +0x44 _maybe XXL2's distance/speed floats (DotD reads three)
    float m_unk48;                         // +0x48
    float m_unk4C;                         // +0x4c
    IKSerializable* m_unk50;               // +0x50
    IKSerializable* m_unk54;               // +0x54
    IKSerializable* m_unk58;               // +0x58
    IKSerializable* m_unk5C;               // +0x5c
    IKSerializable** m_apFrontDetector;    // +0x60 XXL2 CKDetectorBase** m_apFrontDetector
    IKSerializable** m_apBackDetector;     // +0x64 XXL2 CKDetectorBase** m_apBackDetector
    IKSerializable* m_unk68;               // +0x68
    IKSerializable* m_unk6C;               // +0x6c
    CTriggerStarter m_tsOpenStarter;       // +0x70 XXL2 m_tsOpenStarter_maybe (the first of the two)
    CTriggerStarter m_tsCloseStarter;      // +0x78 XXL2 m_tsCloseStarter_maybe
};
DOTD_ASSERT_SIZE(CKHkDoor, 0x80);
DOTD_ASSERT_OFFSET(CKHkDoor, m_ui8NbOfDectector, 0x40);
DOTD_ASSERT_OFFSET(CKHkDoor, m_baAutoAction, 0x42);
DOTD_ASSERT_OFFSET(CKHkDoor, m_unk44, 0x44);
DOTD_ASSERT_OFFSET(CKHkDoor, m_unk4C, 0x4c);
DOTD_ASSERT_OFFSET(CKHkDoor, m_unk50, 0x50);
DOTD_ASSERT_OFFSET(CKHkDoor, m_unk5C, 0x5c);
DOTD_ASSERT_OFFSET(CKHkDoor, m_apFrontDetector, 0x60);
DOTD_ASSERT_OFFSET(CKHkDoor, m_apBackDetector, 0x64);
DOTD_ASSERT_OFFSET(CKHkDoor, m_unk68, 0x68);
DOTD_ASSERT_OFFSET(CKHkDoor, m_unk6C, 0x6c);
DOTD_ASSERT_OFFSET(CKHkDoor, m_tsOpenStarter, 0x70);
DOTD_ASSERT_OFFSET(CKHkDoor, m_tsCloseStarter, 0x78);
