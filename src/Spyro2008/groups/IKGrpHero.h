// IKGrpHero.h - the unregistered base of the hero group (key 0x1544, vtable 0xb22968, size 0xf8). Original
// units: IKGrpHero.cpp (0x2c8718 the constructor, Ghidra CKGrpS08Hero_ConstructBase_maybe) and
// CKGrpS08Hero.cpp (0x2c8fb0 IKGrpHero_Load). XXL2: Commun/K/KHero/IKGrpHero.h (m_ui8NumberOfHeros,
// m_apHeros, ..., SGrpHeroProperties m_sProperties). XXL2's Load reads the same start (the hero count, a
// count byte, m_apHeros) and ends with m_sProperties (words, three 16-bit values, a byte); DotD reads more
// arrays and words in between, so only those keep XXL2's names.
#pragma once
#include <cstdint>

#include "Spyro2008/hooks/IKHkHero.h"
#include "k2000/core/Layout.h"
#include "k2000/groups/IKBaseGroup.h"
#include "k2000/math/CMatrix34.h"
#include "k2000/services/CTriggerStarter.h"

class IKGrpHero : public IKGroup<IKHook> {
public:
    // 0x002c8718 CKGrpS08Hero_ConstructBase_maybe (the IKGrpHero constructor).
    IKGrpHero() {
        m_ui32Priority = 0x8000001du;
        // C2.2 gm: the original leaves the hero lists and counts uninitialised until the group restarts
        // (RebuildControlledAndCompanionHeroArrays); the game manager reads the count every frame, so a group
        // that has not restarted yet has no heroes here (the PS3's memory content is not reproducible).
        m_apControlledHeroes = nullptr;
        m_apCompanionHeroes = nullptr;
        m_ui8ControlledHeroCount = 0;
        m_ui8CompanionHeroCount = 0;
    }

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x002c8fb0 IKGrpHero_Load
    // vt+0x10 0x002c8d58 IKGrpHero_Destroy: no child groups, no members (vt+0xb0's head), then FreeArrays.
    void Destroy() override;
    // 0x002c82a8 IKGrpHero_FreeArrays_maybe: the hero and runtime arrays freed (the pointers kept), the player slots
    // deleted.
    void FreeArrays();
    int32_t PostLoad(int32_t type) override;            // vt+0x30 0x002c8598 IKGrpHero_PostLoad (C2.2)
    // vt+0x24 0x002c8b00 IKGrpHero_LevelReset: IKGroup's (0x12a68), then for the types below 4 or above 7 the group
    // registered with the saving manager, each hero's three references (+0x44, +0x48, +0x4c; vt+0xf4 heroes) and +0x58
    // registered (the five trigger starters register nothing).
    void RecursiveRegistration(int32_t type) override;
    // vt+0xa8 0x002c81f0 IKGrpHero_EnableMembers / vt+0xac 0x002c8660 DisableMembers (OnLock / OnUnlock): every hero
    // (vt+0xf4, from the last) locked / unlocked (SetObjectLocked 0x1c250).
    void OnLock() override;
    void OnUnlock() override;
    // vt+0x60 0x002c8af8 CKGrpS08Hero_vf60, vt+0x70 0x002c8af0 CKGrpS08Hero_BasePause_maybe and vt+0x78 0x002c8a88
    // CKGrpS08Hero_BaseResume_maybe: empty, IKUpdatable's Vf60 / IKBaseGroup's Pause and Resume (CKGrpS08Hero's Pause /
    // Resume call the latter two).
    // vt+0x184 0x002ca978 IKGrpHero_vf184: the focused hero's (+0x66) camera target (+0x44) pushed on the camera
    // service's target stack (blend -1). CKGrpS08Hero, the only concrete hero group, overrides the slot
    // (UpdateHeroCameraTargets 0x2d52d8), so nothing calls it; the slot is not modelled (non-virtual here).
    void PushFocusedCameraTarget();
    // vt+0x40 0x002c8788 IKGrpHero_GetInfo (checklist: IKGrpHero_ResolveTriggerProperty_maybe): the trigger values
    // 0 the first controlled dragon, 1 the game manager's vt+0x270 of it, 2 the controlled hero's distance to the
    // nearest companion (a float), 3 the controlled hero count.
    int32_t GetInfo(IKInfo* info, int32_t request) override;
    // Its accessors (CKGrpS08Hero.cpp, the original's unit): the value as a raw word.
    static uint32_t InfoFirstControlledDragon(IKSerializable* self, uint32_t arg);      // 0x002ca928
    static uint32_t InfoFirstControlledDragonVf270(IKSerializable* self, uint32_t arg); // 0x002ca8b0
    static uint32_t InfoCompanionDistance(IKSerializable* self, uint32_t arg);          // 0x002ca7a0
    static uint32_t InfoControlledHeroCount(IKSerializable* self, uint32_t arg);        // 0x002ca2e0
    // vt+0xf4 CKGrpS08Hero 0x2ce318 returns 2 (the heroes of the group); named _maybe.
    virtual uint8_t GetHeroCount() = 0;
    // The tables the heroes' InitRuntimeTables (0x00345408) takes from the group (CKGrpS08Hero returns constants;
    // the names are ours): the hero state tables (rows of 0x14 bytes, see SHeroStateRow) and their sizes.
    virtual uint8_t GetHeroRuntimeBlockSize() = 0;                     // vt+0x10c CKGrpS08Hero_GetNbHeroInputBytes_maybe: 0x34
    // step 4 (input): the hero's logical inputs (ReadHeroPlayerInput 0x369670 / UpdateHeroInputDerivedState
    // 0x368f18): the game manager actions read before (vt+0x110) and after (vt+0x114) the two analog values, and the
    // action of the hero's logical input `index` (vt+0x118). vt+0x10c is the size of the hero's input bytes (+0x36c).
    virtual uint8_t GetNbInputActions() = 0;                           // vt+0x110 CKGrpS08Hero_vf110: 0x32
    virtual uint8_t GetNbExtraInputActions() = 0;                      // vt+0x114 CKGrpS08Hero_vf114: 2
    virtual uint8_t GetInputAction(uint8_t index) = 0;                 // vt+0x118 CKGrpS08Hero_vf118 (table 0x00a70470)
    virtual const SHeroStateRow* GetHeroStatesC() = 0;                 // vt+0x128 CKGrpS08Hero_vf128
    virtual uint8_t GetNbHeroStatesC() = 0;                            // vt+0x12c CKGrpS08Hero_vf12C: 5
    virtual uint8_t GetNbAnimBlendSlots(uint8_t hero) = 0;             // vt+0x134 CKGrpS08Hero_vf134 (table 0x00a70498)
    // vt+0x16c CKGrpS08Hero_vf16C 0x002ce4b8: the index into the hero's hot spots of its body part `part` (0..5),
    // 0xff when the hero has none (table pointers at 0x00b01018, one per hero).
    virtual uint8_t GetHotSpotIndex(uint8_t hero, uint8_t part) = 0;
    // vt+0x170 CKGrpS08Hero_vf170 0x002ce4d8: the hero's active inner blend layer (table 0x00a704c0: 0xff, none).
    virtual uint8_t GetActiveInnerBlendSlot(uint8_t hero) = 0;
    virtual const SHeroStateRow* GetHeroStatesD() = 0;                 // vt+0x13c CKGrpS08Hero_vf13C
    virtual uint8_t GetNbHeroStatesD() = 0;                            // vt+0x140 CKGrpS08Hero_vf140: 11
    virtual const SHeroStateRow* GetHeroStatesA() = 0;                 // vt+0x144 CKGrpS08Hero_vf144
    virtual uint8_t GetNbHeroStatesA() = 0;                            // vt+0x148 CKGrpS08Hero_vf148: 11
    virtual const SHeroStateRow* GetHeroStatesB() = 0;                 // vt+0x14c CKGrpS08Hero_vf14C
    virtual uint8_t GetNbHeroStatesB() = 0;                            // vt+0x150 CKGrpS08Hero_vf150: 13
    void AllocRuntimeArrays();       // 0x002c83f0 IKGrpHero_AllocRuntimeArrays_maybe
    void ResetSoundChannelFlags();   // 0x002c8a90 IKGrpHero_ResetSoundChannelFlags_maybe

    // XXL2 SGrpHeroProperties (_maybe): DotD has twelve words before the three 16-bit values and the byte.
    struct SProperties {
        uint32_t m_aui32Words[12];  // +0x00 (LVL010: floats)
        uint16_t m_aui16Values[3];  // +0x30
        uint8_t m_ui8Value;         // +0x36 read raw
        uint8_t m_pad37;
    };

    uint8_t m_ui8NumberOfHeros;     // +0x2c XXL2 m_ui8NumberOfHeros; also set by IKHkHero::Load (stb +0x2c)
    uint8_t m_pad2d[3];
    IKSerializable** m_apHeros;     // +0x30 XXL2 IKHkHero** m_apHeros (count byte references)
    // +0x34..+0x3c run-time arrays, allocated by PostLoad (AllocRuntimeArrays, zeroed, 4 bytes each).
    IKSerializable** m_apControlledHeroes;  // +0x34 Ghidra ppControlledHeroes: GetMaxPlayers + 1 entries
    IKSerializable** m_apCompanionHeroes;   // +0x38 Ghidra ppCompanionHeroes: hero count + 1 entries
    IKSerializable** m_apHeroesCopy;        // +0x3c a copy of m_apHeros, null-terminated (ResetRuntimeState)
    IKSerializable* m_pUnk40;       // +0x40 reference
    IKSerializable** m_apCameraTargets;     // _maybe: +0x44 count byte references
    IKSerializable** m_apUnk48;     // +0x48 count byte references
    IKSerializable** m_apUnk4c;     // +0x4c count byte references
    uint8_t m_ui8ControlledHeroCount;  // +0x50 Ghidra bControlledHeroCount (RebuildControlledAndCompanionHeroArrays)
    uint8_t m_ui8CompanionHeroCount;   // +0x51 Ghidra bCompanionHeroCount
    uint8_t m_pad52[2];
    uint32_t m_unk54;               // +0x54 run-time word
    IKSerializable* m_pLocTextAccessor;       // +0x58 reference (LVL010: a CKLocTextAccessor)
    float m_unk5c;                  // +0x5c ResetRuntimeState copies m_sProperties.m_aui32Words[0] here
    float m_unk60;                  // +0x60 ResetRuntimeState: -1000.0f
    uint8_t m_ui8SelectedDragon;                // +0x64
    uint8_t m_ui8RequestedDragon;                // +0x65
    uint8_t m_ui8FocusedDragon;                // +0x66 0xff (AllocRuntimeArrays, ResetRuntimeState)
    uint8_t m_pad67;
    float m_unk68;                  // +0x68 -1000.0f
    float m_unk6c;                  // +0x6c -1000.0f
    uint32_t m_unk70;               // +0x70
    void* m_asPosAroundLead;                 // +0x74 AllocRuntimeArrays: Mem_CallocAligned16(0x18, maxPlayers * m_sProperties.m_ui8Value)
    void* m_asAltPosAroundLead;                 // +0x78 Mem_CallocAligned16(0x18, hero count)
    uint8_t* m_ai8WantedPos;              // +0x7c Mem_CallocAligned16(1, hero count); ResetRuntimeState fills it with 0xff
    // One 0x2c-byte entry per (player x m_sProperties.m_ui8Value); the block comes from OperatorNewArray
    // (a count cookie before it). step 4: a ground contact (CGroundContactDatasInOut, the four fields the resets
    // write are its ground 0, face -1, status 3 and sector 0): UpdateCatchUpPoints validates catch-up point j of a
    // player with the contact of the same index (CKHkS08Hero_ValidateNavPosition_maybe fills it).
    using SPlayerSlot = CGroundContactDatasInOut;
    SPlayerSlot* m_pPlayerSlots;    // +0x80
    float m_unk84;                  // +0x84 ResetRuntimeState copies m_sProperties.m_aui32Words[4] here
    CVector3 m_vUnk88;              // +0x88 ResetRuntimeState: the zero vector
    uint8_t m_unk94;                // +0x94
    uint8_t m_unk95;                // +0x95
    uint8_t m_pad96[2];
    CTriggerStarter m_aTriggers[5];  // +0x98..+0xbf
    SProperties m_sProperties;      // +0xc0 XXL2 m_sProperties (_maybe)
};
DOTD_ASSERT_SIZE(IKGrpHero, 0xf8);
DOTD_ASSERT_OFFSET(IKGrpHero, m_ui8NumberOfHeros, 0x2c);
DOTD_ASSERT_OFFSET(IKGrpHero, m_apHeros, 0x30);
DOTD_ASSERT_OFFSET(IKGrpHero, m_apControlledHeroes, 0x34);
DOTD_ASSERT_OFFSET(IKGrpHero, m_apHeroesCopy, 0x3c);
DOTD_ASSERT_OFFSET(IKGrpHero, m_ui8ControlledHeroCount, 0x50);
DOTD_ASSERT_OFFSET(IKGrpHero, m_unk54, 0x54);
DOTD_ASSERT_OFFSET(IKGrpHero, m_unk5c, 0x5c);
DOTD_ASSERT_OFFSET(IKGrpHero, m_ui8FocusedDragon, 0x66);
DOTD_ASSERT_OFFSET(IKGrpHero, m_unk70, 0x70);
DOTD_ASSERT_OFFSET(IKGrpHero, m_asPosAroundLead, 0x74);
DOTD_ASSERT_OFFSET(IKGrpHero, m_pPlayerSlots, 0x80);
DOTD_ASSERT_OFFSET(IKGrpHero, m_vUnk88, 0x88);
DOTD_ASSERT_OFFSET(IKGrpHero, m_unk94, 0x94);
DOTD_ASSERT_SIZE(IKGrpHero::SPlayerSlot, 0x2c);
DOTD_ASSERT_OFFSET(IKGrpHero, m_pUnk40, 0x40);
DOTD_ASSERT_OFFSET(IKGrpHero, m_apCameraTargets, 0x44);
DOTD_ASSERT_OFFSET(IKGrpHero, m_apUnk4c, 0x4c);
DOTD_ASSERT_OFFSET(IKGrpHero, m_pLocTextAccessor, 0x58);
DOTD_ASSERT_OFFSET(IKGrpHero, m_aTriggers, 0x98);
DOTD_ASSERT_OFFSET(IKGrpHero, m_sProperties, 0xc0);
