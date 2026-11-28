// CKGrpS08Hero.h - DotD's hero group: the heroes' shared tuning, FX and camera data (key 0x984, vtable
// 0xb22a00, size 0xafc). Original unit: CKGrpS08Hero.cpp (0x2d0b60 Load, 0x2cf1b0 Create). No XXL2 class of
// this name; the fields keep their offset names (types from the LVL010 live samples, _maybe).
#pragma once
#include <cstdint>

#include "Spyro2008/groups/IKGrpHero.h"
#include "k2000/core/Layout.h"
#include "k2000/math/CMatrix34.h"
#include "k2000/services/CTriggerStarter.h"

class CKHkS08Hero;

class CKGrpS08Hero : public IKGrpHero {
public:
    DOTD_CLASS_KEY(kCategoryGroup, 0x26)
    int32_t IsKindOfClass(uint32_t key) override {  // vt+0x08 0x9bd280
        return key == 0x984 || key == 0x1544 || key == 0x17e || key == 0x4 || key == 0x2fe || key == 0x3fe || key == 0xc;
    }
    DOTD_DECLARE_FACTORIES(CKGrpS08Hero)

    // 0x002cf1b0 CKGrpS08Hero_Create (after the IKGrpHero constructor), in its order: 0.0f (TOC 0x1c28).
    CKGrpS08Hero() {
        m_unk100 = 0.0f;
        m_fFinisherCooldownTarget = 0.0f;
        m_unk108 = 0.0f;
        m_unk104 = 0.0f;
        m_fFinisherCooldown = 0.0f;
        m_fFinisherCooldownSpeed = 0.0f;
        m_ui32FollowTrailCount = 0;
        m_pAnnounced = nullptr;
    }

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x002d0b60 CKGrpS08Hero_Load
    // vt+0x10 0x002cf410 CKGrpS08Hero_Destroy: IKGrpHero's, then the group off the dynamic service.
    void Destroy() override;
    // vt+0x40 0x002cf940 CKGrpS08Hero_GetInfo: IKGrpHero_GetInfo 0x2c8788 first (ids 0-3), then the trigger
    // values 7 (+0xab8), 0xb (+0xf8 bit 10), 0xd the focused hero free (no combo), 0xf the focused dragon (+0x66),
    // 0x13 (+0x2c8 bit 8), 0xc the average mana at least half, 0xe the fury gauge full.
    int32_t GetInfo(IKInfo* info, int32_t request) override;
    // vt+0x30 0x002cf2e0 CKGrpS08Hero_PostLoad (step 4): the CKSrvDynamic entry of the hero pair's geometry.
    int32_t PostLoad(int32_t type) override;
    // C2.2 spyro: the level start.
    void Start() override;             // vt+0x50 0x002ceee8 CKGrpS08Hero_Start
    void Restart() override;           // vt+0x54 0x002d0a08 CKGrpS08Hero_Restart
    uint8_t GetHeroCount() override { return 2; }  // vt+0xf4 0x002ce318 GetCKGrpS08HeroCount
    // 0x002ca188 CKGrpS08Hero_IsDragonSwitchPending_maybe (C2.8 sequence: the sequence manager's Update): +0xf8 bit 5.
    uint8_t IsDragonSwitchPending() const { return static_cast<uint8_t>((m_baWorkFlags >> 5) & 1u); }
    // vt+0x1c 0x002cfb68 CKGrpS08Hero_MessageProc: IKGrpHero's messages (0x2ce1f0: the commands 0xc00..0xc10,
    // 0x2666), then the group's own 0xc11..0xc1f (+0x2c8 bits 8, 9, 11, 12, +0xfc, the heroes' +0xed4 bit 4).
    int32_t MessageProc(uint16_t message, void* data) override;
    int32_t HandleHeroCommand(uint32_t command, void* data);  // 0x002cde60 IKGrpHero_HandleCommandMessage_maybe
    // vt+0x100 0x002ce340 CKGrpS08Hero_vf100: the number of collision volumes of a hero (0x00a70458: 9, 9).
    uint8_t GetNbBoundingVolumes(uint8_t hero) { return kNbBoundingVolumes[hero]; }
    static constexpr uint8_t kNbBoundingVolumes[2] = {9, 9};
    // vt+0xf8 0x002ce320 CKGrpS08Hero_vfF8 / vt+0x104 0x002ce350 CKGrpS08Hero_vf104 (P16, for IKHkHero's
    // RecursiveRegistration): the hero's hot spot count (0x00a70448: 0x21, 0x1d) and object count (0x00a70460: 14, 14).
    uint8_t GetNbHotSpots(uint8_t hero) { return kNbHotSpots[hero]; }
    static constexpr uint8_t kNbHotSpots[2] = {0x21, 0x1d};
    uint8_t GetNbObjects(uint8_t hero) { return kNbObjects[hero]; }
    static constexpr uint8_t kNbObjects[2] = {0x0e, 0x0e};
    uint8_t GetHeroRuntimeBlockSize() override { return 0x34; }  // vt+0x10c 0x002ce370
    uint8_t GetNbInputActions() override { return 0x32; }        // vt+0x110 0x002ce378
    uint8_t GetNbExtraInputActions() override { return 2; }      // vt+0x114 0x002ce380
    // vt+0x118 0x002ce388: the byte at 0x00a70448 + 0x28 + index (TOC +0x1bec): the game manager actions of the logical
    // inputs 0..8: 0 - 1 the move's z (+0x392), 2 - 3 its x (+0x390), 4 / 5 the held times read into +0x388 / +0x38c
    // (CKInputDico_GetActionTimePressed), 6 (vt+0x144), 7 (+0x364 bit 21), 8 (+0x360 bit 17). The bytes after are zero.
    uint8_t GetInputAction(uint8_t index) override { return index < 9 ? kInputActions[index] : 0; }
    static constexpr uint8_t kInputActions[9] = {0x0c, 0x0d, 0x0a, 0x0b, 0x02, 0x03, 0x05, 0x04, 0x07};
    const SHeroStateRow* GetHeroStatesC() override;              // vt+0x128 0x002ce3c8 (CKGrpS08Hero.cpp)
    uint8_t GetNbHeroStatesC() override { return 5; }            // vt+0x12c 0x002ce3d0
    uint8_t GetNbAnimBlendSlots(uint8_t hero) override;          // vt+0x134 0x002ce3e0
    uint8_t GetHotSpotIndex(uint8_t hero, uint8_t part) override;  // vt+0x16c 0x002ce4b8
    uint8_t GetActiveInnerBlendSlot(uint8_t hero) override;        // vt+0x170 0x002ce4d8
    // vt+0x11c 0x002ce398 CKGrpS08Hero_GetNbSpeedModes_maybe and vt+0x164 0x002ce480 CKGrpS08Hero_vf164 (the
    // hero's speed-scaled volume, -1 none): constants per hero (0x00a70480 / 0x00a704b0); the heroes call them through
    // the group's vtable, these are the same tables without the object.
    static uint8_t GetNbSpeedModesOf(uint8_t hero);
    // 0x002ce520 CKGrpS08Hero_GetTetherSpringRadius_maybe: +0x124 with +0xfc set, else +0x110.
    float GetTetherSpringRadius() const { return m_bUseAltTetherParams != 0 ? m_fAltTetherSpringRadius : m_fTetherSpringRadius; }
    static uint8_t GetSpeedVolumeIndexOf(uint8_t hero);
    // step 4 ANIM: the sound tables the heroes read through the group's vtable (constants; BUG(original): no bound
    // checks). vt+0x158 0x002ce448: the sound of movement event `event` (0..15; table 0x00a704a0, signed byte: -1 for
    // every event in DotD). vt+0x168 0x002ce498: a byte per hero (0x00a704b8: 0, 0). vt+0x160 0x002ce468: the surface
    // entry `surface` (two bytes at 0x00c40950: footstep FX on, footstep sounds on; the hero's surface +0x16c is always 0).
    static int8_t GetMovementEventSound(uint32_t event) {
        static const int8_t kEventSounds[16] = {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1};
        return kEventSounds[event];
    }
    static int8_t GetHeroSoundByte(uint8_t hero) {
        static const int8_t kBytes[2] = {0, 0};
        return kBytes[hero];
    }
    static const uint8_t* GetSurfaceEntry(uint8_t surface) {
        static const uint8_t kEntries[16] = {1, 1, 0, 1, 0, 0, 0, 0, 4, 14, 22, 23, 5, 0, 0, 0};
        return &kEntries[surface * 2u];
    }
    // 0x002cc3f0 SetFocusedDragon: `hero` (null: the first controlled one) becomes the focused dragon when `force` or
    // when none is focused (CKGrpS08Hero.cpp).
    void SetFocusedDragon(IKSerializable* hero, uint8_t force);
    // step 2: the group's frame.
    void Update(IKTime* clock) override;                   // vt+0x7c 0x002cf7c8 UpdateCKGrpS08Hero
    void UpdateHeroGroup(IKTime* clock);                   // 0x002c8870 IKGrpHero_Update (IKGrpHero.cpp)
    void UpdateSwitchPressFeedback(IKTime* clock);         // 0x002ce5c8
    void UpdateCatchUpPoints();                            // 0x002ccbe0
    void UpdatePartnerInteraction(IKTime* clock);          // 0x002cbf10
    // step 4 (AI-GRP): the partner's catch-up points. A point is 0x18 bytes; IKGrpHero +0x74 (m_pUnk74) holds
    // m_sProperties.m_ui8Value of them per player (the player's block at m_ui8Leader * count), +0x78 (m_pUnk78) the
    // extra points UpdateCatchUpPoints finds around the leader's nav point; +0x7c (m_pUnk7c) the point index each hero
    // holds (-1 none). Names ours (_maybe).
    struct SCatchUpPoint {
        CVector3 m_vPosition;     // +0x00
        float m_fScore;           // +0x0c lower is better (sorted ascending; vf17C writes the distances to the
                                  //       companion, divided by the largest)
        int8_t m_i8Index;         // +0x10 the point's index around the leader (-1: an extra point)
        uint8_t m_ui8Unavailable; // +0x11 1: behind the leader, off the nav, too high, or taken (AssignFollowSlot)
        uint8_t m_ui8Raised;      // +0x12 ValidateNavPosition put the point up on its ground
        uint8_t m_ui8CellBlocked; // +0x13 the point's nav cell was a dynamic obstacle before the search blocked it
        uint8_t m_ui8Reachable;   // +0x14 the point's sector is the leader's or reachable through a transition
        uint8_t m_pad15[3];
    };
    // 0x002caf58 CKGrpS08Hero_FindCatchUpPoint_maybe: the point of the hero's player block the hero holds (its
    // +0x7c index) when its score is below the block's first point's plus +0xd4, else that first point; the first
    // point when the hero holds none; null without points.
    SCatchUpPoint* FindCatchUpPoint(CKHkS08Hero* hero);
    // 0x002cb6f0 CKGrpS08Hero_AssignFollowSlot_maybe: the hero takes a free catch-up point of its leader's player
    // block (the first one no other hero of the player holds, or the one it already held when that scores below it
    // plus +0xd4), marks it taken and returns its position; null (and the hero holds none) when there is none.
    const CVector3* AssignFollowSlot(CKHkS08Hero* hero);
    // vt+0x17c 0x002d0018 CKGrpS08Hero_ScoreCatchUpPointsByCompanionDistance_maybe: with at most one controlled hero, the scores of the points of block 0 are
    // the distances to the first companion divided by the largest (non-virtual here: only UpdateCatchUpPoints calls it).
    void ScoreCatchUpPointsByCompanionDistance();
    // 0x002cb9c0 CKGrpS08Hero_CanSwitchToDragon_maybe / vt+0x188 0x002cb4c0 CKGrpS08Hero_IsDragonSelectable_maybe / 0x002cbb08
    // CKGrpS08Hero_RequestDragonSelection_maybe: the dragon switch (+0x64 the selected dragon, +0x65 the requested one).
    uint8_t CanSwitchToDragon(uint8_t dragon);
    uint8_t IsDragonSelectable(uint8_t dragon);
    // 0x002cb0a8 CKGrpS08Hero_FindNextSelectableHero_maybe without its filter (a member function pointer; null from
    // CKHkS08Hero's message 0xc42): the next hero index after `start` (wrapping over vt+0xf4) that the player does
    // not control and whose dragon is selectable (vt+0x188); -1 when none.
    int8_t FindNextSelectableHero(int8_t start);
    void RequestDragonSelection(uint8_t selected, uint8_t requested, uint8_t flag6, uint8_t flag7, uint8_t immediate,
                                uint8_t applyArg, uint8_t forceFlag8);
    // 0x002ca740 CKGrpS08Hero_RequestDragonSelection_Thunk_maybe: RequestDragonSelection with the last two arguments 0.
    void RequestDragonSelectionThunk(uint8_t selected, uint8_t requested, uint8_t flag6, uint8_t flag7, uint8_t immediate) {
        RequestDragonSelection(selected, requested, flag6, flag7, immediate, 0, 0);
    }
    // 0x002ceb30 CKGrpS08Hero_ApplyTetherPullToHero_maybe: the hero's external displacement (+0x1668) toward the
    // tether's middle when its distance to it (+0x314 / +0x318) is above half `maxDistance` (that distance is cut to
    // the half).
    void ApplyTetherPullToHero(float maxDistance, CKHkS08Hero* hero);
    // 0x002d01d8 CKGrpS08Hero_UpdateHeroPairGeometry_maybe: the CKSrvDynamic sub-step hook (PostLoad): the heroes'
    // separation (+0x2e0, its length +0x2d8), the tether's middle (+0x2f0, unless +0x2c8 bit 0), the directions from
    // each hero to it (+0x2fc / +0x308) and their lengths (+0x314 / +0x318), the tether pull, and the heroes' +0xec4
    // bit 22 (no tether) and +0x2c8 bits 1 / 2, all at the heroes' positions predicted `dt` ahead.
    void UpdateHeroPairGeometry(float dt);
    // DOTD: CKSrvDynamic's native dispatcher of the group's entry (CKSrvDynamic::SetNativeDispatch).
    static void DispatchDynamicHook(IKSerializable* object, const uint32_t pair[2], float step);
    // The external lock (CKHkS08Clamp holds the two heroes): +0x2c8 bit 0 and its owner (+0x2ec); while it is held the
    // tether's middle (+0x2f0) is the owner's and the heroes have no tether (UpdateHeroPairGeometry).
    // 0x002d4c30 / 0x002d4d10 / 0x002d4c40 / 0x002d4c78 CKGrpS08Hero_IsExternalLockFree / AcquireExternalLock /
    // ReleaseExternalLock / SetExternalLockPosition_maybe (CKGrpS08Hero_2.cpp).
    uint8_t IsExternalLockFree() const;
    void AcquireExternalLock(const IKSerializable* owner);
    void ReleaseExternalLock(const IKSerializable* owner);
    void SetExternalLockPosition(const CVector3* position, const IKSerializable* owner);
    // 0x002d4d48 CKGrpS08Hero_IsGameManagerVf154Le1AndField36CNonNegative_maybe (CKGrpS08Hero_3.cpp): at most one
    // player (the game manager's vt+0x154) and +0x36c not negative.
    uint8_t IsSinglePlayerAndTimer36cSet();
    // step 6 AI: one record of the leader's follow trail at +0x380 (0x24 bytes, +0xa88 records; written by
    // CKGrpS08Hero_RecordLeaderTrail_maybe 0x2d5be0: dead, no pointer to its descriptor).
    struct SFollowWaypoint {
        CVector3 m_vPosition;  // +0x00
        CVector3 m_vDirection;     // _maybe: +0x0c
        float m_unk18;         // +0x18
        uint32_t m_unk1c;      // +0x1c (AIComputeFollowFlyingThrottle tests 1)
        uint16_t m_unk20;      // +0x20 (0xffff for none)
        uint16_t m_pad22;
    };
    // 0x002d4fd8 CKGrpS08Hero_GetFollowTrailPoint_maybe (CKGrpS08Hero_3.cpp): the trail record +0xaa8 back from the end
    // when that index is above 0, else the last one; none (zero, 0xffff) for an empty trail.
    SFollowWaypoint GetFollowWaypoint() const;
    // vt+0x180 0x002d6f90 CKGrpS08Hero_ProcessDragonSwitchRequest (CKGrpS08Hero_3.cpp).
    void ProcessDragonSwitchRequest(uint8_t arg);
    // 0x002cc7c0 ApplyRequestedDragonSelection (CKGrpS08Hero.cpp): the requested dragon takes the selected one's player.
    void ApplyRequestedDragonSelection(uint8_t applyArg);
    void UpdateHeroSpeechAnims(IKTime* clock);             // 0x002cb280
    void UpdateFlightAltitudeGap();                        // 0x002ce888
    void UpdateCoopFocusedDragon(IKTime* clock);           // 0x002d6c60 (CKGrpS08Hero_3.cpp)
    void SynchronizeHeroPlayerAssignments();               // 0x002d63f8 (CKGrpS08Hero_3.cpp)
    void UpdateFury(IKTime* clock);                        // 0x002d71f0 (CKGrpS08Hero_3.cpp)
    void UpdateTimers364(IKTime* clock);                   // 0x002d61b8 (CKGrpS08Hero_3.cpp)
    // 0x002d5430 CKGrpS08Hero_AllowFinisherCamera_maybe: with at most one player and the announcer idle (+0x36c -1): a
    // blow already announced refuses it (`lethal`: the blow is forgotten instead); else the announcer restarts (+0x364 0,
    // +0x368 1, +0x36c +0x1c4 + +0x1c8 less a random part of +0x1c8 up to two, one draw; +0x374 0) and the blow is
    // remembered (the oldest forgotten past +0x1d4 of them; none kept without +0x1d4): 1.
    uint8_t AllowFinisherCamera(const void* blow, int32_t lethal);   // (CKGrpS08Hero_3.cpp)
    void UpdateSinglePlayerPartnerFlags();                 // 0x002d57a8 (CKGrpS08Hero_3.cpp)
    const SHeroStateRow* GetHeroStatesD() override;              // vt+0x13c 0x002ce3f8
    uint8_t GetNbHeroStatesD() override { return 0xb; }          // vt+0x140 0x002ce400
    const SHeroStateRow* GetHeroStatesA() override;              // vt+0x144 0x002ce408
    uint8_t GetNbHeroStatesA() override { return 0xb; }          // vt+0x148 0x002ce410
    const SHeroStateRow* GetHeroStatesB() override;              // vt+0x14c 0x002ce418
    uint8_t GetNbHeroStatesB() override { return 0xd; }          // vt+0x150 0x002ce420
    // port-all P22: the group's small slots and helpers. The slots IKGrpHero does not declare stay non-virtual (the
    // heroes read most of them through local copies: CKHkS08Hero_7 / _11 / _15 / _19, IKHkHero, CKGrpSquad,
    // CKS08GameManager_2 / _3, CKHkS08Enemy_7 / _11).
    // 0x002ca1b8 CKGrpS08Hero_SetDragonSwitchLocked_maybe: locking takes the selected dragon as the requested one (+0x64
    // into +0x65) and clears the pending switch (+0xf8 bit 5); +0xf8 bit 1 = `locked` (the whole word or'ed in).
    void SetDragonSwitchLocked(uint32_t locked) {
        if (locked != 0) {
            m_ui8RequestedDragon = m_ui8SelectedDragon;
            m_baWorkFlags &= ~0x20u;
        }
        m_baWorkFlags = (m_baWorkFlags & ~2u) | (locked << 1);
    }
    // 0x002ca258 CKGrpS08Hero_IsInputBlocked_maybe / 0x002ca268 SetInputBlocked_maybe: +0xf8 bit 3.
    uint8_t IsInputBlocked() const { return static_cast<uint8_t>((m_baWorkFlags >> 3) & 1u); }
    void SetInputBlocked(uint32_t blocked) { m_baWorkFlags = (m_baWorkFlags & ~8u) | (blocked << 3); }
    // 0x002ca298 CKGrpS08Hero_vf16C_Thunk_maybe: vt+0x16c, sign-extended (CKHkPushObstacle / CKHkPushKillObject).
    int8_t GetHotSpotIndexSigned(uint8_t hero, uint8_t part) { return static_cast<int8_t>(GetHotSpotIndex(hero, part)); }
    // vt+0xb8 0x002ce308 CKGrpS08Hero_vfB8 returns 1 and vt+0xec 0x002ce310 CKGrpS08Hero_vfEC is empty: IKBaseGroup
    // models no slot there and no ported code calls them (see CKCommonBaseGroup.h).
    // vt+0xfc 0x002ce330 CKGrpS08Hero_vfFC (0x00a70450: 0x11, 0x11) and vt+0x108 0x002ce360 CKGrpS08Hero_vf108
    // (0x00a70468: 13, 13): constants per hero. BUG(original): no bound checks.
    uint8_t GetHeroTableFC(uint8_t hero) const {
        static const uint8_t kValues[2] = {0x11, 0x11};
        return kValues[hero];
    }
    uint8_t GetHeroTable108(uint8_t hero) const {
        static const uint8_t kValues[2] = {0x0d, 0x0d};
        return kValues[hero];
    }
    // vt+0x120 0x002ce3a8 CKGrpS08Hero_vf120 (0x00a70488: 1, 1) and vt+0x124 0x002ce3b8 CKGrpS08Hero_GetNbJumps_maybe
    // (0x00a70490: 2, 2; IKHkHero.cpp / IKHkHero_2.cpp have copies).
    uint8_t GetHeroTable120(uint8_t hero) const {
        static const uint8_t kValues[2] = {1, 1};
        return kValues[hero];
    }
    uint8_t GetNbJumps(uint8_t hero) const {
        static const uint8_t kValues[2] = {2, 2};
        return kValues[hero];
    }
    uint32_t GetHeroConst130() const { return 0x117; }  // vt+0x130 0x002ce3d8
    uint32_t GetHeroConst138() const { return 0x61; }   // vt+0x138 0x002ce3f0
    // vt+0x154 0x002ce428 CKGrpS08Hero_vf154: the signed byte [hero][kind] of the two 8-byte tables named at 0x00b01020
    // (0x00ceadc8 / 0x00ceadd0: zero-filled data nothing writes). CKHkS08Hero_19.cpp's FootstepParticleIndex is a copy.
    int8_t GetFootstepParticleIndex(uint8_t /*hero*/, uint8_t /*kind*/) const { return 0; }
    uint32_t GetHeroConst15C() const { return 2; }      // vt+0x15c 0x002ce460
    uint32_t GetHeroConst174() const { return 0; }      // vt+0x174 0x002ce4f0 (CKGrpS08Hero.cpp reads it as 0)
    // vt+0x178 0x002ce4f8 CKGrpS08Hero_vf178: the hot spot of secondary shadow `index` of `hero` (0x00c40958 /
    // 0x00c40960 through 0x00b01010; CKHkS08Hero_15.cpp's SecondaryShadowHotSpot is a copy). BUG(original): no bound
    // checks.
    int8_t GetSecondaryShadowHotSpot(uint8_t hero, uint32_t index) const {
        static const int8_t kHotSpots[2][8] = {{4, 0x0e, 0x16, 0x17, 5, 0, 0, 0}, {4, 0x0e, 0x15, 0x16, 5, 0, 0, 0}};
        return kHotSpots[hero][index];
    }
    int32_t GetHeroConst18C() const { return -1; }      // vt+0x18c 0x002ce4b0
    // 0x002ce540 / 0x002ce560 / 0x002ce580 CKGrpS08Hero_GetTetherDampingRadius_maybe / SpringStiffness_maybe /
    // DampingCoeff_maybe: +0x128 / +0x12c / +0x130 with +0xfc set, else +0x114 / +0x118 / +0x11c.
    // 0x002d51e0 CKGrpS08Hero_ClearFollowTrail_maybe: no trail points (+0xa88 = 0; CKHkS08Hero_11.cpp has a copy).
    void ClearFollowTrail() { m_ui32FollowTrailCount = 0; }
    float GetTetherDampingRadius() const { return m_bUseAltTetherParams != 0 ? m_fAltTetherDampingRadius : m_fTetherDampingRadius; }
    float GetTetherSpringStiffness() const { return m_bUseAltTetherParams != 0 ? m_fAltTetherSpringStiffness : m_fTetherSpringStiffness; }
    float GetTetherDampingCoeff() const { return m_bUseAltTetherParams != 0 ? m_fAltTetherDampingCoeff : m_fTetherDampingCoeff; }
    // 0x002d4bc0 CKGrpS08Hero_GetFocusedHeroCamera_maybe: the focused hero's (+0x66) camera target (+0x1818)
    // (CKS08GameManager::GetFocusedHeroCamera has it inline with its guard).
    IKSerializable* GetFocusedHeroCamera() const;
    // vt+0x24 0x002cef40 CKGrpS08Hero_RecursiveRegistration: IKGrpHero's, then the references' (+0x2cc, +0xabc, +0x348,
    // +0x34c, +0x354, +0x358, +0x360; the trigger starters +0xab0, +0x338, +0x340, +0xac0 register nothing).
    void RecursiveRegistration(int32_t type) override;
    void ReinitRuntime();              // 0x002c8f78 CKGrpS08Hero_ReinitRuntime
    // 0x002c8dc8 IKGrpHero_ResetRuntimeState_maybe: written on a CKGrpS08Hero (it clears +0xf8).
    void ResetRuntimeState();
    void RebuildControlledAndCompanionHeroArrays();  // 0x002cb528
    // vt+0x184 0x002d52d8 CKGrpS08Hero_vf184 (C2.2 strict2; 0x2ca598 is its thunk): every hero registers its camera
    // target (CKHkS08Hero_UpdateModeFlagsAndTetherTimers_maybe).
    void UpdateHeroCameraTargets();
    // 0x002d4cb8 CKGrpS08Hero_OnEnemyKilled_maybe: both heroes' kill bonus (CKHkS08Hero_GrantKillUpgradeBonus_maybe).
    void OnEnemyKilled(IKSerializable* enemy);
    static uint8_t GetMaxPlayers();    // 0x002cabd8 GetMaxPlayers_maybe: the game manager's vt+0x150

    uint32_t m_baWorkFlags;  // +0xf8 not loaded
    uint8_t m_bUseAltTetherParams;   // +0xfc not loaded (Restart: a byte, 0)
    uint8_t m_padfd[3];
    float m_unk100;  // +0x100 the constructor sets 0.0; not loaded
    float m_unk104;  // +0x104 the constructor sets 0.0; not loaded
    float m_unk108;  // +0x108 the constructor sets 0.0; not loaded
    float m_unk10c;  // +0x10c
    float m_fTetherSpringRadius;  // +0x110
    float m_fTetherDampingRadius;  // +0x114
    float m_fTetherSpringStiffness;  // +0x118
    float m_fTetherDampingCoeff;  // +0x11c
    float m_unk120;  // +0x120
    float m_fAltTetherSpringRadius;  // +0x124
    float m_fAltTetherDampingRadius;  // +0x128
    float m_fAltTetherSpringStiffness;  // +0x12c
    float m_fAltTetherDampingCoeff;  // +0x130
    float m_unk134;  // +0x134
    float m_unk138;  // +0x138
    float m_unk13c;  // +0x13c
    float m_unk140;  // +0x140
    float m_unk144;  // +0x144
    float m_unk148;  // +0x148
    float m_unk14c;  // +0x14c
    float m_unk150;  // +0x150
    float m_unk154;  // +0x154
    float m_unk158;  // +0x158
    float m_unk15c;  // +0x15c
    float m_unk160;  // +0x160
    float m_unk164;  // +0x164
    float m_unk168;  // +0x168
    float m_unk16c;  // +0x16c
    float m_unk170;  // +0x170
    float m_unk174;  // +0x174
    float m_unk178;  // +0x178
    float m_unk17c;  // +0x17c
    float m_unk180;  // +0x180
    float m_unk184;  // +0x184
    float m_unk188;  // +0x188
    float m_unk18c;  // +0x18c
    float m_unk190;  // +0x190
    float m_unk194;  // +0x194
    float m_unk198;  // +0x198
    float m_unk19c;  // +0x19c
    float m_unk1a0;  // +0x1a0
    float m_unk1a4;  // +0x1a4
    float m_unk1a8;  // +0x1a8
    float m_unk1ac;  // +0x1ac
    float m_unk1b0;  // +0x1b0
    float m_unk1b4;  // +0x1b4
    float m_unk1b8;  // +0x1b8
    float m_unk1bc;  // +0x1bc
    float m_unk1c0;  // +0x1c0
    float m_unk1c4;  // +0x1c4
    float m_unk1c8;  // +0x1c8
    float m_unk1cc;  // +0x1cc
    float m_unk1d0;  // +0x1d0
    int32_t m_unk1d4;  // +0x1d4
    float m_unk1d8;  // +0x1d8
    float m_unk1dc;  // +0x1dc
    float m_unk1e0;  // +0x1e0
    float m_unk1e4;  // +0x1e4
    float m_unk1e8;  // +0x1e8
    float m_unk1ec;  // +0x1ec
    uint32_t m_unk1f0;  // +0x1f0
    float m_unk1f4;  // +0x1f4
    float m_unk1f8;  // +0x1f8
    uint8_t m_unk1fc;  // +0x1fc
    uint8_t m_unk1fd;  // +0x1fd
    uint8_t m_pad1fe;
    uint8_t m_pad1ff;
    float m_unk200;  // +0x200
    float m_unk204;  // +0x204
    float m_unk208;  // +0x208
    float m_unk20c;  // +0x20c
    float m_unk210;  // +0x210
    float m_unk214;  // +0x214
    float m_unk218;  // +0x218
    float m_unk21c;  // +0x21c
    float m_unk220;  // +0x220
    float m_unk224;  // +0x224
    float m_unk228;  // +0x228
    float m_unk22c;  // +0x22c
    float m_unk230;  // +0x230
    float m_unk234;  // +0x234
    float m_unk238;  // +0x238
    float m_unk23c;  // +0x23c
    uint32_t m_unk240;  // +0x240
    float m_unk244;  // +0x244
    float m_unk248;  // +0x248
    float m_unk24c;  // +0x24c
    float m_unk250;  // +0x250
    float m_unk254;  // +0x254
    float m_unk258;  // +0x258
    float m_unk25c;  // +0x25c
    float m_unk260;  // +0x260
    float m_unk264;  // +0x264
    int32_t m_unk268;  // +0x268
    int32_t m_unk26c;  // +0x26c
    float m_unk270;  // +0x270
    float m_unk274;  // +0x274
    float m_unk278;  // +0x278
    float m_unk27c;  // +0x27c
    uint32_t m_unk280;  // +0x280
    float m_unk284;  // +0x284
    uint32_t m_unk288;  // +0x288
    float m_unk28c;  // +0x28c
    float m_unk290;  // +0x290
    float m_unk294;  // +0x294
    uint32_t m_unk298;  // +0x298
    uint32_t m_unk29c;  // +0x29c
    uint32_t m_unk2a0;  // +0x2a0
    float m_unk2a4;  // +0x2a4
    uint32_t m_unk2a8;  // +0x2a8
    float m_unk2ac;  // +0x2ac
    uint32_t m_unk2b0;  // +0x2b0
    float m_unk2b4;  // +0x2b4
    float m_unk2b8;  // +0x2b8
    float m_unk2bc;  // +0x2bc
    uint32_t m_unk2c0;  // +0x2c0
    float m_unk2c4;  // +0x2c4
    uint32_t m_ui32PairStateFlags;  // +0x2c8 not loaded
    IKSerializable* m_pQuakeLauncher;  // +0x2cc reference (LVL010: CKQuakeCameraLauncher)
    float m_fSwitchFeedbackTimer;          // +0x2d0 not loaded (Restart: 0; ProcessDragonSwitchRequest: 2.0)
    uint32_t m_unk2d4[17];   // +0x2d4..+0x314 not loaded
    uint32_t m_fHero1ToMidDist;       // +0x318 not loaded
    float m_unk31c;          // +0x31c not loaded (Restart copies m_unk178)
    uint8_t m_unk320;        // +0x320 not loaded (Restart: 0, then 1)
    uint8_t m_pad321[3];
    float m_unk324;          // +0x324 not loaded (PostLoad: 50.0)
    float m_unk328;          // +0x328 not loaded (PostLoad: 20.0)
    uint32_t m_unk32c;       // +0x32c not loaded (PostLoad: 0)
    uint32_t m_unk330;       // +0x330 not loaded (PostLoad: 0)
    uint32_t m_unk334;       // +0x334 not loaded (PostLoad: 1000)
    CTriggerStarter m_tsOnFuryChargeStart;  // +0x338
    CTriggerStarter m_tsOnFuryEnd;  // +0x340
    IKSerializable* m_pFuryFlashFxData;  // +0x348 reference (LVL010: CKFlashFxData)
    IKSerializable* m_pFuryFilterFxData;  // +0x34c reference (LVL010: CKFilterFxData)
    IKSerializable* m_pActiveFuryFilterFx;  // +0x350 not loaded: the fury's filter effect (UpdateFury)
    IKSerializable* m_pFuryExplosionFxData;  // +0x354 reference (LVL010: CKExplosionFxData)
    IKSerializable* m_pFuryHdrFxData;  // +0x358 reference (LVL010: CKHDRFxData)
    IKSerializable* m_pActiveFuryHdrFx;  // +0x35c not loaded: the fury's HDR effect (UpdateFury)
    IKSerializable* m_pFuryChargeCurve;  // +0x360 reference (LVL010: CKCurve2DCpnt)
    float m_fFinisherCooldownTarget;  // +0x364 the constructor sets 0.0; not loaded
    float m_fFinisherCooldownSpeed;  // +0x368 the constructor sets 0.0; not loaded
    float m_fFinisherCooldown;  // +0x36c the constructor sets 0.0; not loaded
    // +0x370 the blows whose finisher camera was shown (AllowFinisherCamera; FreeListPool 0x00ceaa20 nodes in the original,
    // new / delete here): the constructor sets null; not loaded.
    struct AnnouncedBlow {
        const void* m_pBlow;     // +0x00
        AnnouncedBlow* m_pNext;  // +0x04
    };
    AnnouncedBlow* m_pAnnounced;
    float m_fAnnouncerElapsedTime;          // +0x374 not loaded (Restart: 0); the announcer time (UpdateTimers364 adds dt)
    uint32_t m_unk378;       // +0x378 not loaded
    uint32_t m_unk37c;       // +0x37c not loaded (Restart: 0)
    uint32_t m_aFollowTrail[450];  // +0x380..+0xa84 not loaded
    uint32_t m_ui32FollowTrailCount;  // +0xa88 the constructor sets 0; not loaded
    uint32_t m_unka8c[2];    // +0xa8c..+0xa90 not loaded
    CVector3 m_vFollowTargetOverride;      // +0xa94 not loaded (Restart: the zero vector)
    uint32_t m_unkaa0[3];    // +0xaa0..+0xaa8 not loaded (Restart: 0)
    uint32_t m_unkaac;       // +0xaac not loaded
    CTriggerStarter m_tsOnPowerBucketFill;  // _maybe: +0xab0
    uint8_t m_ui8PowerBucketFillHero;   // _maybe: +0xab8 not loaded (PostLoad: a byte, 0)
    uint8_t m_padab9[3];
    IKSerializable* m_pPromptTextAccessor;  // +0xabc reference (LVL010: CKLocTextAccessor)
    CTriggerStarter m_tsOnPlayerHeroHurt;  // +0xac0
    float m_fFlightFloorLevel;     // +0xac8 not loaded (the flight altitude gap)
    uint8_t m_ui8FlightFloorHero;   // +0xacc not loaded (Restart: a byte, 0xff)
    uint8_t m_padacd[3];
    IKSerializable* m_pSparx;  // +0xad0 reference (LVL010: CKHkS08Sparx)
    uint32_t m_unkad4[10];  // +0xad4..+0xaf8 not loaded
};
static_assert(CKGrpS08Hero::kClassKey == 0x984, "key");
static_assert(sizeof(CKGrpS08Hero::SCatchUpPoint) == 0x18, "catch-up point");
DOTD_ASSERT_SIZE(CKGrpS08Hero, 0xafc);
DOTD_ASSERT_OFFSET(CKGrpS08Hero, m_baWorkFlags, 0xf8);
DOTD_ASSERT_OFFSET(CKGrpS08Hero, m_bUseAltTetherParams, 0xfc);
DOTD_ASSERT_OFFSET(CKGrpS08Hero, m_unk100, 0x100);
DOTD_ASSERT_OFFSET(CKGrpS08Hero, m_fSwitchFeedbackTimer, 0x2d0);
DOTD_ASSERT_OFFSET(CKGrpS08Hero, m_unk31c, 0x31c);
DOTD_ASSERT_OFFSET(CKGrpS08Hero, m_unk320, 0x320);
DOTD_ASSERT_OFFSET(CKGrpS08Hero, m_fAnnouncerElapsedTime, 0x374);
DOTD_ASSERT_OFFSET(CKGrpS08Hero, m_unk37c, 0x37c);
DOTD_ASSERT_OFFSET(CKGrpS08Hero, m_vFollowTargetOverride, 0xa94);
DOTD_ASSERT_OFFSET(CKGrpS08Hero, m_unkaa0, 0xaa0);
DOTD_ASSERT_OFFSET(CKGrpS08Hero, m_ui8FlightFloorHero, 0xacc);
DOTD_ASSERT_OFFSET(CKGrpS08Hero, m_unk104, 0x104);
DOTD_ASSERT_OFFSET(CKGrpS08Hero, m_unk108, 0x108);
DOTD_ASSERT_OFFSET(CKGrpS08Hero, m_unk10c, 0x10c);
DOTD_ASSERT_OFFSET(CKGrpS08Hero, m_fTetherSpringRadius, 0x110);
DOTD_ASSERT_OFFSET(CKGrpS08Hero, m_fTetherDampingRadius, 0x114);
DOTD_ASSERT_OFFSET(CKGrpS08Hero, m_fTetherSpringStiffness, 0x118);
DOTD_ASSERT_OFFSET(CKGrpS08Hero, m_fTetherDampingCoeff, 0x11c);
DOTD_ASSERT_OFFSET(CKGrpS08Hero, m_unk120, 0x120);
DOTD_ASSERT_OFFSET(CKGrpS08Hero, m_fAltTetherSpringRadius, 0x124);
DOTD_ASSERT_OFFSET(CKGrpS08Hero, m_fAltTetherDampingRadius, 0x128);
DOTD_ASSERT_OFFSET(CKGrpS08Hero, m_fAltTetherSpringStiffness, 0x12c);
DOTD_ASSERT_OFFSET(CKGrpS08Hero, m_fAltTetherDampingCoeff, 0x130);
DOTD_ASSERT_OFFSET(CKGrpS08Hero, m_unk134, 0x134);
DOTD_ASSERT_OFFSET(CKGrpS08Hero, m_unk138, 0x138);
DOTD_ASSERT_OFFSET(CKGrpS08Hero, m_unk13c, 0x13c);
DOTD_ASSERT_OFFSET(CKGrpS08Hero, m_unk140, 0x140);
DOTD_ASSERT_OFFSET(CKGrpS08Hero, m_unk144, 0x144);
DOTD_ASSERT_OFFSET(CKGrpS08Hero, m_unk148, 0x148);
DOTD_ASSERT_OFFSET(CKGrpS08Hero, m_unk14c, 0x14c);
DOTD_ASSERT_OFFSET(CKGrpS08Hero, m_unk150, 0x150);
DOTD_ASSERT_OFFSET(CKGrpS08Hero, m_unk154, 0x154);
DOTD_ASSERT_OFFSET(CKGrpS08Hero, m_unk158, 0x158);
DOTD_ASSERT_OFFSET(CKGrpS08Hero, m_unk15c, 0x15c);
DOTD_ASSERT_OFFSET(CKGrpS08Hero, m_unk160, 0x160);
DOTD_ASSERT_OFFSET(CKGrpS08Hero, m_unk164, 0x164);
DOTD_ASSERT_OFFSET(CKGrpS08Hero, m_unk168, 0x168);
DOTD_ASSERT_OFFSET(CKGrpS08Hero, m_unk16c, 0x16c);
DOTD_ASSERT_OFFSET(CKGrpS08Hero, m_unk170, 0x170);
DOTD_ASSERT_OFFSET(CKGrpS08Hero, m_unk174, 0x174);
DOTD_ASSERT_OFFSET(CKGrpS08Hero, m_unk178, 0x178);
DOTD_ASSERT_OFFSET(CKGrpS08Hero, m_unk17c, 0x17c);
DOTD_ASSERT_OFFSET(CKGrpS08Hero, m_unk180, 0x180);
DOTD_ASSERT_OFFSET(CKGrpS08Hero, m_unk184, 0x184);
DOTD_ASSERT_OFFSET(CKGrpS08Hero, m_unk188, 0x188);
DOTD_ASSERT_OFFSET(CKGrpS08Hero, m_unk18c, 0x18c);
DOTD_ASSERT_OFFSET(CKGrpS08Hero, m_unk190, 0x190);
DOTD_ASSERT_OFFSET(CKGrpS08Hero, m_unk194, 0x194);
DOTD_ASSERT_OFFSET(CKGrpS08Hero, m_unk198, 0x198);
DOTD_ASSERT_OFFSET(CKGrpS08Hero, m_unk19c, 0x19c);
DOTD_ASSERT_OFFSET(CKGrpS08Hero, m_unk1a0, 0x1a0);
DOTD_ASSERT_OFFSET(CKGrpS08Hero, m_unk1a4, 0x1a4);
DOTD_ASSERT_OFFSET(CKGrpS08Hero, m_unk1a8, 0x1a8);
DOTD_ASSERT_OFFSET(CKGrpS08Hero, m_unk1ac, 0x1ac);
DOTD_ASSERT_OFFSET(CKGrpS08Hero, m_unk1b0, 0x1b0);
DOTD_ASSERT_OFFSET(CKGrpS08Hero, m_unk1b4, 0x1b4);
DOTD_ASSERT_OFFSET(CKGrpS08Hero, m_unk1b8, 0x1b8);
DOTD_ASSERT_OFFSET(CKGrpS08Hero, m_unk1bc, 0x1bc);
DOTD_ASSERT_OFFSET(CKGrpS08Hero, m_unk1c0, 0x1c0);
DOTD_ASSERT_OFFSET(CKGrpS08Hero, m_unk1c4, 0x1c4);
DOTD_ASSERT_OFFSET(CKGrpS08Hero, m_unk1c8, 0x1c8);
DOTD_ASSERT_OFFSET(CKGrpS08Hero, m_unk1cc, 0x1cc);
DOTD_ASSERT_OFFSET(CKGrpS08Hero, m_unk1d0, 0x1d0);
DOTD_ASSERT_OFFSET(CKGrpS08Hero, m_unk1d4, 0x1d4);
DOTD_ASSERT_OFFSET(CKGrpS08Hero, m_unk1d8, 0x1d8);
DOTD_ASSERT_OFFSET(CKGrpS08Hero, m_unk1dc, 0x1dc);
DOTD_ASSERT_OFFSET(CKGrpS08Hero, m_unk1e0, 0x1e0);
DOTD_ASSERT_OFFSET(CKGrpS08Hero, m_unk1e4, 0x1e4);
DOTD_ASSERT_OFFSET(CKGrpS08Hero, m_unk1e8, 0x1e8);
DOTD_ASSERT_OFFSET(CKGrpS08Hero, m_unk1ec, 0x1ec);
DOTD_ASSERT_OFFSET(CKGrpS08Hero, m_unk1f0, 0x1f0);
DOTD_ASSERT_OFFSET(CKGrpS08Hero, m_unk1f4, 0x1f4);
DOTD_ASSERT_OFFSET(CKGrpS08Hero, m_unk1f8, 0x1f8);
DOTD_ASSERT_OFFSET(CKGrpS08Hero, m_unk1fc, 0x1fc);
DOTD_ASSERT_OFFSET(CKGrpS08Hero, m_unk1fd, 0x1fd);
DOTD_ASSERT_OFFSET(CKGrpS08Hero, m_unk200, 0x200);
DOTD_ASSERT_OFFSET(CKGrpS08Hero, m_unk204, 0x204);
DOTD_ASSERT_OFFSET(CKGrpS08Hero, m_unk208, 0x208);
DOTD_ASSERT_OFFSET(CKGrpS08Hero, m_unk20c, 0x20c);
DOTD_ASSERT_OFFSET(CKGrpS08Hero, m_unk210, 0x210);
DOTD_ASSERT_OFFSET(CKGrpS08Hero, m_unk214, 0x214);
DOTD_ASSERT_OFFSET(CKGrpS08Hero, m_unk218, 0x218);
DOTD_ASSERT_OFFSET(CKGrpS08Hero, m_unk21c, 0x21c);
DOTD_ASSERT_OFFSET(CKGrpS08Hero, m_unk220, 0x220);
DOTD_ASSERT_OFFSET(CKGrpS08Hero, m_unk224, 0x224);
DOTD_ASSERT_OFFSET(CKGrpS08Hero, m_unk228, 0x228);
DOTD_ASSERT_OFFSET(CKGrpS08Hero, m_unk22c, 0x22c);
DOTD_ASSERT_OFFSET(CKGrpS08Hero, m_unk230, 0x230);
DOTD_ASSERT_OFFSET(CKGrpS08Hero, m_unk234, 0x234);
DOTD_ASSERT_OFFSET(CKGrpS08Hero, m_unk238, 0x238);
DOTD_ASSERT_OFFSET(CKGrpS08Hero, m_unk23c, 0x23c);
DOTD_ASSERT_OFFSET(CKGrpS08Hero, m_unk240, 0x240);
DOTD_ASSERT_OFFSET(CKGrpS08Hero, m_unk244, 0x244);
DOTD_ASSERT_OFFSET(CKGrpS08Hero, m_unk248, 0x248);
DOTD_ASSERT_OFFSET(CKGrpS08Hero, m_unk24c, 0x24c);
DOTD_ASSERT_OFFSET(CKGrpS08Hero, m_unk250, 0x250);
DOTD_ASSERT_OFFSET(CKGrpS08Hero, m_unk254, 0x254);
DOTD_ASSERT_OFFSET(CKGrpS08Hero, m_unk258, 0x258);
DOTD_ASSERT_OFFSET(CKGrpS08Hero, m_unk25c, 0x25c);
DOTD_ASSERT_OFFSET(CKGrpS08Hero, m_unk260, 0x260);
DOTD_ASSERT_OFFSET(CKGrpS08Hero, m_unk264, 0x264);
DOTD_ASSERT_OFFSET(CKGrpS08Hero, m_unk268, 0x268);
DOTD_ASSERT_OFFSET(CKGrpS08Hero, m_unk26c, 0x26c);
DOTD_ASSERT_OFFSET(CKGrpS08Hero, m_unk270, 0x270);
DOTD_ASSERT_OFFSET(CKGrpS08Hero, m_unk274, 0x274);
DOTD_ASSERT_OFFSET(CKGrpS08Hero, m_unk278, 0x278);
DOTD_ASSERT_OFFSET(CKGrpS08Hero, m_unk27c, 0x27c);
DOTD_ASSERT_OFFSET(CKGrpS08Hero, m_unk280, 0x280);
DOTD_ASSERT_OFFSET(CKGrpS08Hero, m_unk284, 0x284);
DOTD_ASSERT_OFFSET(CKGrpS08Hero, m_unk288, 0x288);
DOTD_ASSERT_OFFSET(CKGrpS08Hero, m_unk28c, 0x28c);
DOTD_ASSERT_OFFSET(CKGrpS08Hero, m_unk290, 0x290);
DOTD_ASSERT_OFFSET(CKGrpS08Hero, m_unk294, 0x294);
DOTD_ASSERT_OFFSET(CKGrpS08Hero, m_unk298, 0x298);
DOTD_ASSERT_OFFSET(CKGrpS08Hero, m_unk29c, 0x29c);
DOTD_ASSERT_OFFSET(CKGrpS08Hero, m_unk2a0, 0x2a0);
DOTD_ASSERT_OFFSET(CKGrpS08Hero, m_unk2a4, 0x2a4);
DOTD_ASSERT_OFFSET(CKGrpS08Hero, m_unk2a8, 0x2a8);
DOTD_ASSERT_OFFSET(CKGrpS08Hero, m_unk2ac, 0x2ac);
DOTD_ASSERT_OFFSET(CKGrpS08Hero, m_unk2b0, 0x2b0);
DOTD_ASSERT_OFFSET(CKGrpS08Hero, m_unk2b4, 0x2b4);
DOTD_ASSERT_OFFSET(CKGrpS08Hero, m_unk2b8, 0x2b8);
DOTD_ASSERT_OFFSET(CKGrpS08Hero, m_unk2bc, 0x2bc);
DOTD_ASSERT_OFFSET(CKGrpS08Hero, m_unk2c0, 0x2c0);
DOTD_ASSERT_OFFSET(CKGrpS08Hero, m_unk2c4, 0x2c4);
DOTD_ASSERT_OFFSET(CKGrpS08Hero, m_pQuakeLauncher, 0x2cc);
DOTD_ASSERT_OFFSET(CKGrpS08Hero, m_tsOnFuryChargeStart, 0x338);
DOTD_ASSERT_OFFSET(CKGrpS08Hero, m_tsOnFuryEnd, 0x340);
DOTD_ASSERT_OFFSET(CKGrpS08Hero, m_pFuryFlashFxData, 0x348);
DOTD_ASSERT_OFFSET(CKGrpS08Hero, m_pFuryFilterFxData, 0x34c);
DOTD_ASSERT_OFFSET(CKGrpS08Hero, m_pFuryExplosionFxData, 0x354);
DOTD_ASSERT_OFFSET(CKGrpS08Hero, m_pFuryHdrFxData, 0x358);
DOTD_ASSERT_OFFSET(CKGrpS08Hero, m_pFuryChargeCurve, 0x360);
DOTD_ASSERT_OFFSET(CKGrpS08Hero, m_fFinisherCooldownTarget, 0x364);
DOTD_ASSERT_OFFSET(CKGrpS08Hero, m_fFinisherCooldownSpeed, 0x368);
DOTD_ASSERT_OFFSET(CKGrpS08Hero, m_fFinisherCooldown, 0x36c);
DOTD_ASSERT_OFFSET(CKGrpS08Hero, m_pAnnounced, 0x370);
DOTD_ASSERT_OFFSET(CKGrpS08Hero, m_ui32FollowTrailCount, 0xa88);
DOTD_ASSERT_OFFSET(CKGrpS08Hero, m_tsOnPowerBucketFill, 0xab0);
DOTD_ASSERT_OFFSET(CKGrpS08Hero, m_pPromptTextAccessor, 0xabc);
DOTD_ASSERT_OFFSET(CKGrpS08Hero, m_tsOnPlayerHeroHurt, 0xac0);
DOTD_ASSERT_OFFSET(CKGrpS08Hero, m_pSparx, 0xad0);
