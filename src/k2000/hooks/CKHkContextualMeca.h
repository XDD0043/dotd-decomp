// CKHkContextualMeca.h - a contextual mechanism hook (key 0x2a82, vtable 0xb27218, size 0x120). Original
// unit: CKHkContextualMeca.cpp. No XXL2 class. Field types from the Ghidra struct draft (live samples).
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/math/CMatrix34.h"
#include "k2000/misc/CKHkActorBase.h"
#include "k2000/services/CTriggerStarter.h"

class IKTime;

class CKHkContextualMeca : public CKHkActorBase {
public:
    // One hero slot of the +0x10c array (0x30 bytes on the PS3, m_unk5C of them): the hero using the mechanism at the
    // slot's activator.
    struct SSlot {
        IKSerializable* m_pHero;       // +0x00 a CKHkS08Hero, or null (OnActivate clears it)
        uint8_t m_ui8State;            // +0x04 0 snapped, 1 holding, 2 walking to the slot
        uint8_t m_pad05[3];
        IKSerializable* m_pHotSpot;    // +0x08 the slot's CSGHotSpot
        CVector3 m_vPosition;          // +0x0c the hero's position when it took the slot
        CVector3 m_vDirection;         // +0x18 its forward direction then
        float m_fTime;                 // +0x24
        IKSerializable* m_pActivator;  // +0x28 the slot's CKHkHeroActivator
        uint8_t m_unk2C;               // +0x2c
        uint8_t m_unk2D;               // +0x2d
        uint8_t m_pad2E[2];
    };

    DOTD_CLASS_KEY(kCategoryHook, 0xaa)

    // vt+0x08 0x009c3f58 CKHkContextualMeca_IsKindOfClass: 0x2a82, then CKHkActorBase's.
    int32_t IsKindOfClass(uint32_t key) override { return key == 0x2a82 || CKHkActorBase::IsKindOfClass(key); }
    DOTD_DECLARE_FACTORIES(CKHkContextualMeca)
    // vt+0x40 0x0045b1f0 CKHkContextualMeca_GetInfo: the trigger values 0x9a (at the end), 0x9b (being operated), 0x9c (the progress).
    int32_t GetInfo(IKInfo* info, int32_t request) override;

    CKHkContextualMeca() {}  // 0x0045b850 CKHkContextualMeca_Create: the CKHkActorBase defaults only
    ~CKHkContextualMeca() override {}

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x0045b9f0 CKHkContextualMeca_Load
    int32_t PostLoad(int32_t type) override;      // vt+0x30 0x0045aa30 CKHkContextualMeca_PostLoad
    void SetDefaultState(int32_t flag) override;  // vt+0x38 0x0045b330 CKHkContextualMeca_SetDefaultState
    void Start() override;                        // vt+0x50 0x0045b960 CKHkContextualMeca_Start
    // vt+0x54 0x0045d120 CKHkContextualMeca_Restart: the run-time state reset (as OnActivate); an enabled mechanism lets its
    // heroes go, takes its state's rest (state 0 / 1 -> 0, else 2), switches its activators by the rest bit (21), plays
    // the state's animation, shows itself by the flag word's top byte and sets the +0x44 node's alpha.
    void Restart() override;
    // vt+0xc8 0x0045b008 CKHkContextualMeca_ApplyStatePreset_maybe
    void ApplyStatePreset(int32_t state) override;
    void Update(IKTime* frameClock) override;     // vt+0x7c 0x004601d8 CKHkContextualMeca_Update
    // vt+0xa0 0x00460450 CKHkContextualMeca_OnActivate: the slots and run-time state reset, the activators switched
    // on (unless bit 21), the rest animation of the state played, the +0x44 node's alpha and the slots placed.
    void VfA0() override;
    void VfA4() override;                         // vt+0xa4 0x0045a990 CKHkContextualMeca_OnDeactivate
    // vt+0xd0 0x0045cfe0 CKHkContextualMeca_SetVisible: the scene node's hidden bit and the collision meshes.
    virtual void SetVisible(int32_t visible);

    // 0x0045a760 CKHkContextualMeca_PlaceSlotActivators_maybe: every activator at its hot spot, turned half a turn and
    // pushed out by +0xcc along the hot spot's at row.
    void PlaceSlotActivators();
    // 0x0045f420 CKHkContextualMeca_UpdateAtRest (bit 21): the rest animation, the +0x110 delay, the hero slots and
    // the activators of the state.
    void UpdateAtRest(IKTime* frameClock, uint32_t state);
    // 0x0045a3a0 CKHkContextualMeca_ReleaseHeroes: the heroes in the slots detached (with `all`, the player-controlled
    // ones stay and the slots' activators are switched back on).
    void ReleaseHeroes(uint8_t all);
    // 0x00459da8 CKHkContextualMeca_UpdateLoopSounds: the speed and volume of the two loop sounds (dictionary
    // entries 1 and 3) from the progress, while one of them plays.
    void UpdateLoopSounds();
    // ---- C2.8 meca-hero: the heroes working the mechanism ----
    // vt+0xcc 0x0045d9d0 CKHkContextualMeca_SetEnabled
    void SetEnabled(int32_t enabled) override;
    // vt+0x1c 0x0045ad48 CKHkContextualMeca_MessageProc
    int32_t MessageProc(uint16_t message, void* data) override;
    // vt+0xd4 0x0045d3f0 CKHkContextualMeca_MoveTo (`on`: towards the end; `mode` 1 jumps there)
    void VfD4(int32_t on, int32_t mode) override;
    // 0x0045dbd0 CKHkContextualMeca_UpdateHeroInteraction (side 1 or 3)
    void UpdateHeroInteraction(IKTime* clock, uint32_t side);
    // 0x0045b420 CKHkContextualMeca_SnapHeroToSlot_maybe
    void SnapHeroToSlot(float dt, int32_t index);
    // 0x0045a618 CKHkContextualMeca_IsHeroPullingAway_maybe
    uint8_t IsHeroPullingAway(uint32_t index);
    // 0x0045a288 CKHkContextualMeca_SetSlotActivatorsEnabled_maybe: every activator of both sides switched to `on`.
    void SetSlotActivatorsEnabled(int32_t on);
    // 0x00459f98 / 0x0045c940 / 0x0045cc48: the at-rest, interaction and step effects (explosions +0xdc / +0xd8 / +0xe0).
    void TriggerAtRestFx();
    void TriggerInteractionFx();
    void SpawnStepFx();
    // vt+0x10 0x0045ab80 CKHkContextualMeca_Destroy: the reference arrays (+0x4c, +0x60..+0x74, +0x88, +0x8c) freed
    // (Mem_FreeAligned16) and the slot records (+0x10c, with the cookie in front) deleted.
    void Destroy() override;
    // 0x00459c90 CKHkContextualMeca_GetProgressRatio_maybe: the progress (+0xfc, plus +0x118 and clamped to +0xd0 then
    // divided by it unless flag 0x80000), mirrored (1 - x) when the flags' bits 17-18 are 2 or 3.
    float GetProgressRatio() const;

    IKSerializable* m_unk20;         // +0x20 CAnimationDictionary* (struct draft)
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
    float m_unkEC;                    // +0xec runtime (OnActivate: 0)
    IKSerializable* m_unkF0;          // +0xf0 CKLocTextAccessor* (struct draft)
    IKSerializable* m_unkF4;          // +0xf4 CKCameraConstraint* (struct draft)
    // +0xf8 runtime floats: [0] the release delay (counts down), [1] the progress (UpdateLoopSounds), [2] / [3] the
    // progress time and its duration, [4]; OnActivate and Start clear them.
    float m_afUnkF8[5];
    SSlot* m_aSlots;                  // +0x10c runtime: PostLoad's OperatorNewArray (0x45aa30), m_unk5C slots
    float m_fUnk110;                  // +0x110 runtime (Start: -1.0f)
    float m_fUnk114;                  // +0x114 runtime: the +0x44 node's alpha (0..255)
    uint32_t m_unk118;                // +0x118 runtime
    float m_fUnk11C;                  // +0x11c runtime (OnActivate: 0)
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
DOTD_ASSERT_OFFSET(CKHkContextualMeca, m_aSlots, 0x10c);
DOTD_ASSERT_SIZE(CKHkContextualMeca::SSlot, 0x30);
