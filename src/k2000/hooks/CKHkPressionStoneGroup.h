// CKHkPressionStoneGroup.h - a puzzle of pressure plates the heroes must hold down together (key 0x342, vtable
// 0xb261f8, size 0x64). Original unit: CKHkPressionStoneGroup.cpp (0x42a308-0x42cce0). No XXL2 class of this key; the
// layout comes from the Load (level type 0 only) and the users in the unit. The group claims its stones
// (CKHkPressionStone::SetOccupant) and drives the AI heroes onto free ones (mode 1). No level of the game holds one (C2.8
// port-rest R04: ported from the disassembly, nothing replays it).
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/misc/CKHkActorBase.h"
#include "k2000/services/CTriggerStarter.h"
#include "k2000/util/TVector.h"

class IKTime;

class CKHkPressionStoneGroup : public CKHkActorBase {
public:
    DOTD_CLASS_KEY(kCategoryHook, 0xd)
    // vt+0x08 0x009c3238 CKHkPressionStoneGroup_IsKindOfClass [inline]
    int32_t IsKindOfClass(uint32_t key) override {
        return key == 0x342 || key == 0xd82 || key == 0x2 || key == 0x2fe || key == 0x3fe || key == 0xc;
    }
    DOTD_DECLARE_FACTORIES(CKHkPressionStoneGroup)

    // 0x0042c648 CKHkPressionStoneGroup_Create: the actor base's defaults, the free stone list empty with capacity 1.
    CKHkPressionStoneGroup() {
        m_vFreeStones.m_pBlock = nullptr;
        m_vFreeStones.m_ui32NbElt = 1;
        m_vFreeStones.m_ui32NbUsedElt = 0;
    }
    // 0x0042bfd0 CKHkPressionStoneGroup_Destructor (0x42c040 / 0x42ba60 the same with the base): the free stone list's
    // block freed (Mem_FreeAligned16) and the list cleared.
    ~CKHkPressionStoneGroup() override;

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x0042c0b0 CKHkPressionStoneGroup_Load
    // vt+0x10 0x0042b840 CKHkPressionStoneGroup_Destroy: the actor base's (vt+0xc0: FreeBuffers).
    // vt+0xc0 0x0042b7e0 CKHkPressionStoneGroup_FreeBuffers_maybe: +0x60 and +0x30 freed (Mem_FreeAligned16), +0x38 freed
    // and cleared when there.
    void VfC0() override;
    // vt+0x38 0x0042b968 CKHkPressionStoneGroup_SetDefaultState: the actor base's (empty), then the preset (vt+0xc8): with
    // `flag` the solved state (+0x21 bit 0) when the group was solved (bit 3), else 0; +0x5c set around the call.
    void SetDefaultState(int32_t flag) override;
    // vt+0xc8 0x0042bed0 CKHkPressionStoneGroup_ApplyStatePreset_maybe: the preset bits of +0x22 (state 0: bits 0 / 2,
    // state 1: bits 1 / 3) into +0x21 bits 3 and 7 (bit 2 cleared outside SetDefaultState) and every stone's bits 21 / 28.
    void ApplyStatePreset(int32_t state) override;
    // vt+0x40 0x0042bdb8 CKHkPressionStoneGroup_GetInfo: the trigger values 0x98 (+0x21 bit 2, 0x9c32a8) and 0x99 (+0x24,
    // 0x9c32a0), bytes; merged with the actor base's answer (KStub_Return1 0x3f7140).
    int32_t GetInfo(struct IKInfo* info, int32_t request) override;
    // vt+0x1c 0x0042bad8 CKHkPressionStoneGroup_MessageProc: the actor messages, then 0x997 enable (+0x24, the stones'
    // bit 21 cleared, their hot spot hold stopped with +0x22 bit 4), 0x940 / 0x996 every hero let go, 0x998 disable,
    // 0x999 solved (+0x21 bits 3 and 7, the stones' bit 21); the answers merged.
    int32_t MessageProc(uint16_t message, void* data) override;
    void Start() override;    // vt+0x50 0x0042c990 CKHkPressionStoneGroup_Start
    void Restart() override;  // vt+0x54 0x0042cb58 CKHkPressionStoneGroup_Restart
    void VfA0() override;     // vt+0xa0 0x0042ca80 CKHkPressionStoneGroup_OnActivate
    // vt+0xa4 0x0042a650 CKHkPressionStoneGroup_OnDeactivate: the actor base's, then every hero let go (forced).
    void VfA4() override;
    void Update(IKTime* frameClock) override;  // vt+0x7c 0x0042c6b8 CKHkPressionStoneGroup_Update

    // The runtime reset Start / OnActivate / Restart inline: +0x54 = 0, +0x55 = 1, +0x58 = 0, +0x23 = +0x24 = 1, no
    // stone assigned, the free list's block (one element) when it has none, +0x21 bit 4 cleared.
    void ResetRuntime();
    // 0x0042a3e0 CKHkPressionStoneGroup_ReleaseAllHeroes_maybe
    void ReleaseAllHeroes(int32_t force);
    // 0x0042a688 CKHkPressionStoneGroup_UpdateHeroesOnStones_maybe
    void UpdateHeroesOnStones(IKTime* frameClock);
    // 0x0042a9f8 CKHkPressionStoneGroup_AssignStonesToAIHeroes_maybe
    void AssignStonesToAIHeroes();
    // 0x0042acc0 CKHkPressionStoneGroup_UpdateStoneStates_maybe
    void UpdateStoneStates();
    // 0x0042b170 CKHkPressionStoneGroup_UpdateOccupantsAndDetachHeroes_maybe
    void UpdateOccupantsAndDetachHeroes(IKTime* frameClock);
    // 0x0042b4b0 CKHkPressionStoneGroup_CheckSolved_maybe
    void CheckSolved();
    // The hero `hero` attached to the group and sent walking to `stone`'s node (its LTM position and at row): the walk
    // AssignStonesToAIHeroes and UpdateHeroesOnStones inline.
    void SendHeroToStone(IKSerializable* hero, IKSerializable* stone);

    uint8_t m_ui8Mode;                     // +0x20 0 the player's heroes, 1 the AI heroes walk onto the stones
    // +0x21 bits: 0, 1, 6 loaded (0 solved state, 1 timed reset, 6 keep heroes); 2 timing, 3 solved, 4 a hero on a
    // stone, 7 the solved preset (ApplyStatePreset / 0x999).
    uint8_t m_ui8Flags;
    uint8_t m_ui8Presets;                  // +0x22 loaded: bits 0..3 the presets, bit 4 the stones' hot spot hold
    uint8_t m_unk23;                       // +0x23 runtime
    uint8_t m_ui8Enabled;                  // +0x24 runtime (0x997 / 0x998; trigger value 0x99)
    uint8_t m_pad25[3];
    float m_fTimeout;                      // +0x28 the hold time before the heroes are let go
    uint8_t m_ui8HeroCount;                // +0x2c
    uint8_t m_pad2D[3];
    IKSerializable** m_apHeroes;           // +0x30 CKHkS08Hero references (one contiguous read)
    uint8_t m_ui8StoneCount;               // +0x34
    uint8_t m_pad35[3];
    IKSerializable** m_apStones;           // +0x38 CKHkPressionStone references
    IKSerializable* m_pSekens;             // +0x3c a CKSekensLauncherCpnt
    CTriggerStarter m_tsSolved;            // +0x40 queued when solved
    TVector<IKSerializable*, 1> m_vFreeStones;  // +0x48 the stones not pressed this frame
    uint8_t m_unk54;                       // +0x54 runtime: sekens 3 played
    uint8_t m_unk55;                       // +0x55 runtime: the heroes are held (timed by +0x58 / +0x28)
    uint8_t m_pad56[2];
    float m_fHoldStart;                    // +0x58 runtime: the time the hold started
    uint8_t m_unk5C;                       // +0x5c runtime: set while SetDefaultState applies the preset
    uint8_t m_pad5D[3];
    IKSerializable** m_apAssignedStones;   // +0x60 the stone of each hero of +0x30 (by dragon index in the detach loop)
};
DOTD_ASSERT_SIZE(CKHkPressionStoneGroup, 0x64);
DOTD_ASSERT_OFFSET(CKHkPressionStoneGroup, m_ui8Mode, 0x20);
DOTD_ASSERT_OFFSET(CKHkPressionStoneGroup, m_ui8Enabled, 0x24);
DOTD_ASSERT_OFFSET(CKHkPressionStoneGroup, m_fTimeout, 0x28);
DOTD_ASSERT_OFFSET(CKHkPressionStoneGroup, m_ui8HeroCount, 0x2c);
DOTD_ASSERT_OFFSET(CKHkPressionStoneGroup, m_apHeroes, 0x30);
DOTD_ASSERT_OFFSET(CKHkPressionStoneGroup, m_ui8StoneCount, 0x34);
DOTD_ASSERT_OFFSET(CKHkPressionStoneGroup, m_apStones, 0x38);
DOTD_ASSERT_OFFSET(CKHkPressionStoneGroup, m_pSekens, 0x3c);
DOTD_ASSERT_OFFSET(CKHkPressionStoneGroup, m_tsSolved, 0x40);
DOTD_ASSERT_OFFSET(CKHkPressionStoneGroup, m_vFreeStones, 0x48);
DOTD_ASSERT_OFFSET(CKHkPressionStoneGroup, m_unk54, 0x54);
DOTD_ASSERT_OFFSET(CKHkPressionStoneGroup, m_fHoldStart, 0x58);
DOTD_ASSERT_OFFSET(CKHkPressionStoneGroup, m_unk5C, 0x5c);
DOTD_ASSERT_OFFSET(CKHkPressionStoneGroup, m_apAssignedStones, 0x60);
