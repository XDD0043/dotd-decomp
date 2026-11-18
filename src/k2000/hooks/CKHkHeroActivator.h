// CKHkHeroActivator.h - a hook the hero activates on approach (key 0x1a02, vtable 0xb26bc0, size 0xb8).
// Original unit: CKHkHeroActivator.cpp (0x447fc0-0x44ae90). No XXL2 class. Field types from the Ghidra
// struct draft (live samples); names stay m_unkXX until the runtime code is ported.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/fx/IKFx.h"
#include "k2000/math/CMatrix34.h"
#include "k2000/misc/CKHkActorBase.h"
#include "k2000/services/CTriggerStarter.h"

class IKTime;
struct IKInfo;

class CKHkHeroActivator : public CKHkActorBase {
public:
    DOTD_CLASS_KEY(kCategoryHook, 0x68)
    int32_t IsKindOfClass(uint32_t key) override {  // vt+0x08 0x9c3bb0
        return key == 0x1a02 || key == 0xd82 || key == 0x2 || key == 0x2fe || key == 0x3fe || key == 0xc;
    }
    DOTD_DECLARE_FACTORIES(CKHkHeroActivator)

    CKHkHeroActivator() {}  // 0x00448fb0 CKHkHeroActivator_Create: the CKHkActorBase defaults only
    ~CKHkHeroActivator() override {}

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x0044a5e0 CKHkHeroActivator_Load
    int32_t PostLoad(int32_t type) override;            // vt+0x30 0x00448880 CKHkHeroActivator_PostLoad
    void SetDefaultState(int32_t flag) override;  // vt+0x38 0x00448b08 CKHkHeroActivator_SetDefaultState
    void Start() override;                        // vt+0x50 0x00448828 CKHkHeroActivator_Start
    void Restart() override;                      // vt+0x54 0x00448010 CKHkHeroActivator_Restart
    void SetEnabled(int32_t enabled) override;    // vt+0xcc 0x004497d0 CKHkHeroActivator_SetEnabled
    // 0x00448100 CKHkHeroActivator_SetTransform_maybe (not virtual): the position (+0x20) and the direction (+0x2c)
    // from the matrix's position and at row; the matrix becomes the local matrix of the +0x60, scene (+0x1c) and
    // +0x84 nodes (each when set).
    void SetTransform(const CMatrix34* matrix);
    // 0x004494c0 CKHkHeroActivator_SetMarkerFx_maybe (not virtual): 0 releases the input-icon effect
    // (m_pMarkerFx: its vt+0x58 with this hook), nonzero acquires one from the effect service (the pool of the
    // data +0x5c, CKSrvFx_AcquireFx inlined) and places it at m_unk20 (CKInputIconNodeFx_SetPosition_maybe), or
    // moves the one it holds there.
    void SetMarkerFx(int32_t on);
    // vt+0x40 0x004481c8 CKHkHeroActivator_GetInfo: the actor base's answer (KStub_Return1 0x3f7140) normalised (2 stays,
    // 0 stays, anything else 1).
    int32_t GetInfo(IKInfo* info, int32_t request) override;
    // vt+0x7c 0x00449bd0 CKHkHeroActivator_Update: the transform from the +0x90 node, the heroes in the activation
    // cone (+0xb4), the activation rule of the bytes +0x54..+0x56 (bit 9, the +0x38 / +0x40 signals), the interaction
    // target of the player's hero (or the automatic use with bit 6 clear), the proximity effect and the two alphas.
    void Update(IKTime* frameClock) override;
    // vt+0x1c 0x00449990 CKHkHeroActivator_MessageProc: 0x93f (a hero uses the activator: the marker released with bit 7,
    // the +0x48 signals, bit 10, sound 0 at the position, +0x9c = the hero) and 0x2666 (the text of +0x50).
    int32_t MessageProc(uint16_t message, void* data) override;
    // vt+0xa0 0x00448cc0 CKHkHeroActivator_OnActivate
    void VfA0() override;
    // vt+0xa4 0x0044a518 CKHkHeroActivator_OnDeactivate: the ring effect's bits 10 / 19 and emitting flag cleared, the
    // marker and the proximity effect released.
    void VfA4() override;
    // vt+0xc8 0x00448c38 CKHkHeroActivator_ApplyStatePreset_maybe: bit 3 (state 0) or 4 (state 1) of the flags enables
    // (bit 8, +0xa4 = 0, +0xa0 = the byte +0x88), else disables (bit 8 cleared, +0xa0 = 0).
    void ApplyStatePreset(int32_t state) override;
    // 0x00449008 CKHkHeroActivator_IsInActivationCone_maybe: with a detector (+0x70), its box or sphere holds `position`;
    // without, `position` is within +0x78 of +0x20, inside the cone of half-angle +0x74 (degrees) around +0x2c from the
    // point +0x80 behind +0x20, and `direction` faces back within +0x7c degrees.
    uint8_t IsInActivationCone(const CVector3* position, const CVector3* direction) const;
    // 0x00448268 CKHkHeroActivator_UpdateProximityFx_maybe: the proximity effect (data +0x64) acquired at the node's
    // world matrix (or +0x20 / +0x2c) while a controlled hero is within +0xb0, else released.
    void UpdateProximityFx();

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
    IKFx* m_pMarkerFx;                // +0x94 runtime: the input-icon effect (SetMarkerFx); 0 at PostLoad (0x448880)
    // +0x98 runtime: the proximity effect (UpdateProximityFx: from the CKParticlesEffectFxData +0x64 while a controlled
    // hero is within +0xb0; Restart and OnActivate clear the word, Update / OnDeactivate release it through vt+0x58).
    IKFx* m_pProximityFx;
    // +0x9c runtime: the hero that used the activator (message 0x93f's data; Restart and SetEnabled clear it).
    IKSerializable* m_pUser;
    float m_fUnkA0;                   // +0xa0 runtime: the scene node's alpha (SetDefaultState: 0, or the byte m_unk88)
    float m_fUnkA4;                   // +0xa4 runtime: the +0x84 node's alpha (ApplyStatePreset / SetDefaultState: 0)
    float m_fUnkA8;                   // +0xa8 runtime: the proximity test's countdown (OnActivate: m_unk68)
    float m_unkAC;                    // +0xac the proximity effect's height above the node
    float m_unkB0;                    // +0xb0 the proximity effect's radius
    uint32_t m_ui32HeroesInCone;      // +0xb4 runtime: bit n = hero n in the activation cone (Update)
};
DOTD_ASSERT_SIZE(CKHkHeroActivator, 0xb8);

// 0x00448038 CKHkHeroActivator_CallSetEnabled: the activator's vt+0xcc with `enabled` (the caller's r4, passed on).
void CKHkHeroActivator_CallSetEnabled(IKSerializable* activator, int32_t enabled);
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
