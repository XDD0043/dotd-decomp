// CKHkHeroActivator.h - a hook the hero activates on approach (key 0x1a02, vtable 0xb26bc0, size 0xb8).
// Original unit: CKHkHeroActivator.cpp (0x447fc0-0x44ae90). No XXL2 class. Field types from the Ghidra
// struct draft (live samples); names stay m_unkXX until the runtime code is ported.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/math/CMatrix34.h"
#include "k2000/misc/CKHkActorBase.h"
#include "k2000/services/CTriggerStarter.h"

class CKHkHeroActivator : public CKHkActorBase {
public:
    DOTD_CLASS_KEY(kCategoryHook, 0x68)
    DOTD_DECLARE_FACTORIES(CKHkHeroActivator)

    CKHkHeroActivator() {}  // 0x00448fb0 CKHkHeroActivator_Create: the CKHkActorBase defaults only
    ~CKHkHeroActivator() override {}

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x0044a5e0 CKHkHeroActivator_Load
    void SetDefaultState(int32_t flag) override;  // vt+0x38 0x00448b08 CKHkHeroActivator_SetDefaultState
    void Start() override;                        // vt+0x50 0x00448828 CKHkHeroActivator_Start
    void Restart() override;                      // vt+0x54 0x00448010 CKHkHeroActivator_Restart
    void SetEnabled(int32_t enabled) override;    // vt+0xcc 0x004497d0 CKHkHeroActivator_SetEnabled
    // 0x004494c0 CKHkHeroActivator_SetMarkerFx_maybe (not virtual): 0 releases the input-icon effect
    // (m_unk94), nonzero acquires one from the effect service and places it at m_unk20. STUB(C2.2): the
    // effect pool's acquire/release (CKSrvFx, IKFx slots) is the services' work; no effect is ever acquired
    // here, so m_unk94 stays null and nothing is released.
    void SetMarkerFx(int32_t on);

    CVector3 m_unk20;                 // +0x20 a position_maybe (one 12-byte read, each word swapped)
    CVector3 m_unk2C;                 // +0x2c a unit direction_maybe (LVL010: (0, 0, -1))
    CTriggerStarter m_unk38;          // +0x38 loaded second
    CTriggerStarter m_unk40;          // +0x40 loaded third
    CTriggerStarter m_unk48;          // +0x48 loaded first
    IKSerializable* m_unk50;          // +0x50 CKLocTextAccessor* (struct draft)
    uint8_t m_unk54[3];               // +0x54 three byte reads
    uint8_t m_pad57;
    uint32_t m_unk58;                 // +0x58
    IKSerializable* m_unk5C;          // +0x5c CKInputIconFxData* (struct draft)
    IKSerializable* m_unk60;          // +0x60
    IKSerializable* m_unk64;          // +0x64
    float m_unk68;                    // +0x68
    IKSerializable* m_unk6C;          // +0x6c CKSoundDictionaryID* (struct draft)
    IKSerializable* m_unk70;          // +0x70 CKDetectorBase* (struct draft)
    float m_unk74;                    // +0x74 read after +0x78
    float m_unk78;                    // +0x78
    float m_unk7C;                    // +0x7c
    float m_unk80;                    // +0x80
    IKSerializable* m_unk84;          // +0x84
    uint8_t m_unk88;                  // +0x88
    uint8_t m_unk89;                  // +0x89
    uint8_t m_pad8A[2];
    float m_unk8C;                    // +0x8c
    IKSerializable* m_unk90;          // +0x90
    uint32_t m_unk94;                 // +0x94 runtime: 0 at PostLoad (0x448880)
    uint32_t m_unk98;                 // +0x98 runtime (Restart clears it)
    uint32_t m_unk9C;                 // +0x9c runtime (Restart and SetEnabled clear it)
    float m_fUnkA0;                   // +0xa0 runtime (SetDefaultState: 0, or the byte m_unk88)
    uint32_t m_unkA4;                 // +0xa4 runtime
    uint32_t m_unkA8;                 // +0xa8 runtime
    float m_unkAC;                    // +0xac
    float m_unkB0;                    // +0xb0
    uint32_t m_unkB4;                 // +0xb4 runtime
};
DOTD_ASSERT_SIZE(CKHkHeroActivator, 0xb8);
DOTD_ASSERT_OFFSET(CKHkHeroActivator, m_unk20, 0x20);
DOTD_ASSERT_OFFSET(CKHkHeroActivator, m_unk2C, 0x2c);
DOTD_ASSERT_OFFSET(CKHkHeroActivator, m_unk38, 0x38);
DOTD_ASSERT_OFFSET(CKHkHeroActivator, m_unk40, 0x40);
DOTD_ASSERT_OFFSET(CKHkHeroActivator, m_unk48, 0x48);
DOTD_ASSERT_OFFSET(CKHkHeroActivator, m_unk50, 0x50);
DOTD_ASSERT_OFFSET(CKHkHeroActivator, m_unk54, 0x54);
DOTD_ASSERT_OFFSET(CKHkHeroActivator, m_unk58, 0x58);
DOTD_ASSERT_OFFSET(CKHkHeroActivator, m_unk5C, 0x5c);
DOTD_ASSERT_OFFSET(CKHkHeroActivator, m_unk60, 0x60);
DOTD_ASSERT_OFFSET(CKHkHeroActivator, m_unk64, 0x64);
DOTD_ASSERT_OFFSET(CKHkHeroActivator, m_unk68, 0x68);
DOTD_ASSERT_OFFSET(CKHkHeroActivator, m_unk6C, 0x6c);
DOTD_ASSERT_OFFSET(CKHkHeroActivator, m_unk70, 0x70);
DOTD_ASSERT_OFFSET(CKHkHeroActivator, m_unk74, 0x74);
DOTD_ASSERT_OFFSET(CKHkHeroActivator, m_unk80, 0x80);
DOTD_ASSERT_OFFSET(CKHkHeroActivator, m_unk84, 0x84);
DOTD_ASSERT_OFFSET(CKHkHeroActivator, m_unk88, 0x88);
DOTD_ASSERT_OFFSET(CKHkHeroActivator, m_unk8C, 0x8c);
DOTD_ASSERT_OFFSET(CKHkHeroActivator, m_unk90, 0x90);
DOTD_ASSERT_OFFSET(CKHkHeroActivator, m_unkAC, 0xac);
DOTD_ASSERT_OFFSET(CKHkHeroActivator, m_unkB0, 0xb0);
