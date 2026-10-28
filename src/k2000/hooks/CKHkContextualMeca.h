// CKHkContextualMeca.h - a contextual mechanism hook (key 0x2a82, vtable 0xb27218, size 0x120). Original
// unit: CKHkContextualMeca.cpp. No XXL2 class. Field types from the Ghidra struct draft (live samples).
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/misc/CKHkActorBase.h"
#include "k2000/services/CTriggerStarter.h"

class CKHkContextualMeca : public CKHkActorBase {
public:
    DOTD_CLASS_KEY(kCategoryHook, 0xaa)
    DOTD_DECLARE_FACTORIES(CKHkContextualMeca)

    CKHkContextualMeca() {}  // 0x0045b850 CKHkContextualMeca_Create: the CKHkActorBase defaults only
    ~CKHkContextualMeca() override {}

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x0045b9f0 CKHkContextualMeca_Load
    int32_t PostLoad(int32_t type) override;      // vt+0x30 0x0045aa30 CKHkContextualMeca_PostLoad
    void SetDefaultState(int32_t flag) override;  // vt+0x38 0x0045b330 CKHkContextualMeca_SetDefaultState
    void Start() override;                        // vt+0x50 0x0045b960 CKHkContextualMeca_Start
    // vt+0xc8 0x0045b008 CKHkContextualMeca_ApplyStatePreset_maybe
    void ApplyStatePreset(int32_t state) override;

    IKSerializable* m_unk20;          // +0x20 CAnimationDictionary* (struct draft)
    IKSerializable* m_unk24;          // +0x24 CKGroundCpnt* (struct draft)
    IKSerializable* m_unk28;          // +0x28
    IKSerializable* m_unk2C;          // +0x2c CKSoundDictionaryID* (struct draft)
    float m_unk30;                    // +0x30
    float m_unk34;                    // +0x34
    float m_unk38;                    // +0x38
    float m_unk3C;                    // +0x3c
    uint8_t m_unk40;                  // +0x40
    uint8_t m_pad41[3];
    IKSerializable* m_unk44;          // +0x44
    uint8_t m_unk48;                  // +0x48 the count of +0x4c
    uint8_t m_pad49[3];
    IKSerializable** m_apUnk4C;       // +0x4c references (Mem_AllocAligned16)
    uint8_t m_unk50;                  // +0x50
    uint8_t m_pad51[3];
    float m_unk54;                    // +0x54
    float m_unk58;                    // +0x58
    uint8_t m_unk5C;                  // +0x5c (PostLoad sizes its 0x30-byte array at +0x10c by it)
    uint8_t m_unk5D;                  // +0x5d runtime (Start clears it)
    uint8_t m_unk5E;                  // +0x5e the count of the +0x60/+0x68/+0x88(/+0x70) arrays
    uint8_t m_unk5F;                  // +0x5f the count of the +0x64/+0x6c/+0x8c(/+0x74) arrays
    IKSerializable** m_apUnk60;       // +0x60
    IKSerializable** m_apUnk64;       // +0x64
    IKSerializable** m_apUnk68;       // +0x68
    IKSerializable** m_apUnk6C;       // +0x6c
    IKSerializable** m_apUnk70;       // +0x70 only with bit 0x1000 of m_bitArray, else 0
    IKSerializable** m_apUnk74;       // +0x74 only with bit 0x1000 of m_bitArray, else 0
    float m_unk78;                    // +0x78
    float m_unk7C;                    // +0x7c
    float m_unk80;                    // +0x80
    float m_unk84;                    // +0x84
    IKSerializable** m_apUnk88;       // +0x88
    IKSerializable** m_apUnk8C;       // +0x8c
    float m_unk90;                    // +0x90
    float m_unk94;                    // +0x94
    float m_unk98;                    // +0x98
    CTriggerStarter m_unk9C;          // +0x9c
    CTriggerStarter m_unkA4;          // +0xa4
    CTriggerStarter m_unkAC;          // +0xac
    CTriggerStarter m_unkB4;          // +0xb4
    CTriggerStarter m_unkBC;          // +0xbc
    CTriggerStarter m_unkC4;          // +0xc4
    float m_unkCC;                    // +0xcc
    uint32_t m_unkD0;                 // +0xd0
    float m_unkD4;                    // +0xd4
    IKSerializable* m_unkD8;          // +0xd8 CKExplosionFxData* (struct draft)
    IKSerializable* m_unkDC;          // +0xdc CKExplosionFxData* (struct draft)
    IKSerializable* m_unkE0;          // +0xe0
    float m_unkE4;                    // +0xe4
    float m_unkE8;                    // +0xe8
    uint32_t m_unkEC;                 // +0xec runtime
    IKSerializable* m_unkF0;          // +0xf0 CKLocTextAccessor* (struct draft)
    IKSerializable* m_unkF4;          // +0xf4 CKCameraConstraint* (struct draft)
    uint32_t m_unkF8[5];              // +0xf8 runtime
    void* m_unk10C;                   // +0x10c runtime: PostLoad's OperatorNewArray (0x45aa30)
    float m_fUnk110;                  // +0x110 runtime (Start: -1.0f)
    uint32_t m_unk114;                // +0x114 runtime
    uint32_t m_unk118;                // +0x118 runtime
    uint32_t m_unk11C;                // +0x11c runtime
};
DOTD_ASSERT_SIZE(CKHkContextualMeca, 0x120);
DOTD_ASSERT_OFFSET(CKHkContextualMeca, m_unk20, 0x20);
DOTD_ASSERT_OFFSET(CKHkContextualMeca, m_unk2C, 0x2c);
DOTD_ASSERT_OFFSET(CKHkContextualMeca, m_unk38, 0x38);
DOTD_ASSERT_OFFSET(CKHkContextualMeca, m_unk40, 0x40);
DOTD_ASSERT_OFFSET(CKHkContextualMeca, m_unk44, 0x44);
DOTD_ASSERT_OFFSET(CKHkContextualMeca, m_unk48, 0x48);
DOTD_ASSERT_OFFSET(CKHkContextualMeca, m_apUnk4C, 0x4c);
DOTD_ASSERT_OFFSET(CKHkContextualMeca, m_unk50, 0x50);
DOTD_ASSERT_OFFSET(CKHkContextualMeca, m_unk54, 0x54);
DOTD_ASSERT_OFFSET(CKHkContextualMeca, m_unk5C, 0x5c);
DOTD_ASSERT_OFFSET(CKHkContextualMeca, m_unk5E, 0x5e);
DOTD_ASSERT_OFFSET(CKHkContextualMeca, m_unk5F, 0x5f);
DOTD_ASSERT_OFFSET(CKHkContextualMeca, m_apUnk60, 0x60);
DOTD_ASSERT_OFFSET(CKHkContextualMeca, m_apUnk74, 0x74);
DOTD_ASSERT_OFFSET(CKHkContextualMeca, m_unk78, 0x78);
DOTD_ASSERT_OFFSET(CKHkContextualMeca, m_apUnk88, 0x88);
DOTD_ASSERT_OFFSET(CKHkContextualMeca, m_unk90, 0x90);
DOTD_ASSERT_OFFSET(CKHkContextualMeca, m_unk9C, 0x9c);
DOTD_ASSERT_OFFSET(CKHkContextualMeca, m_unkC4, 0xc4);
DOTD_ASSERT_OFFSET(CKHkContextualMeca, m_unkCC, 0xcc);
DOTD_ASSERT_OFFSET(CKHkContextualMeca, m_unkD8, 0xd8);
DOTD_ASSERT_OFFSET(CKHkContextualMeca, m_unkE0, 0xe0);
DOTD_ASSERT_OFFSET(CKHkContextualMeca, m_unkF0, 0xf0);
DOTD_ASSERT_OFFSET(CKHkContextualMeca, m_unkF4, 0xf4);
DOTD_ASSERT_OFFSET(CKHkContextualMeca, m_unk10C, 0x10c);
