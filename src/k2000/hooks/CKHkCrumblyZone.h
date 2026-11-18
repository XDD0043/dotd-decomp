// CKHkCrumblyZone.h - a ground that breaks under the hero (key 0x1982, vtable 0xb257b0, size 0x1bc). Original
// unit: CKHkCrumblyZone.cpp (0x405608-0x410190). XXL2: KMeca/CrumblyZone/CKHkCrumblyZone.h (384 bytes, base
// IKHkMeca); DotD's class is larger. Registered, but no object of this exact class occurs in the files: only
// its Spyro2008 leaf CKHkS08CrumblyZone does.
//
// Names: the first seven members (+0x20..+0x38) follow XXL2's member layout, which has the same shape
// (two pointers, a ground list, a pointer, a ground list, two pointers); the rest stay m_unkXX.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/math/CMatrix34.h"
#include "k2000/misc/CKHkActorBase.h"
#include "k2000/services/CTriggerStarter.h"
#include "k2000/util/TVector.h"

class IKBoundingVolume;

class CKHkCrumblyZone : public CKHkActorBase {
public:
    DOTD_CLASS_KEY(kCategoryHook, 0x66)
    // 0x00405608 Delete / 0x00407168 CreateArray / 0x00406128 DeleteArray (the registry factories; no object of this
    // exact class occurs in the files).
    DOTD_DECLARE_FACTORIES(CKHkCrumblyZone)
    int32_t IsKindOfClass(uint32_t key) override {  // vt+0x08 0x9c1178
        return key == 0x1982 || key == 0xd82 || key == 0x2 || key == 0x2fe || key == 0x3fe || key == 0xc;
    }

    // A node of the ground lists (XXL2 CKHkCrumblyZone::GroundList), 8 bytes, taken from the FreeListPool
    // at TOC+0x49a8 in the original (FreeListPool_Grow when empty). New nodes go to the front.
    struct GroundNode {
        IKSerializable* m_pGround;  // +0x0
        GroundNode* m_pNext;        // +0x4
    };
    // One element of the +0xa4 vector (0x14 bytes on the PS3).
    struct Entry14 {
        IKSerializable* m_pUnk0;  // +0x0
        float m_afUnk4[3];        // +0x4
        uint8_t m_unk10;          // +0x10
        uint8_t m_pad11[3];
    };
    // One element of the +0x88 vector (8 bytes on the PS3).
    struct Entry8 {
        uint32_t m_unk0;          // +0x0 lwbrx
        IKSerializable* m_pUnk4;  // +0x4
    };

    // 0x004061c8 CKHkCrumblyZone_Create (inlined constructor), in its store order.
    CKHkCrumblyZone() {
        m_lAddedSafeGround = nullptr;
        m_lAddedBrokenGround = nullptr;
        m_vUnk7C.m_ui32NbElt = 1;
        m_vUnk7C.m_pBlock = nullptr;
        m_vUnk7C.m_ui32NbUsedElt = 0;
        m_vUnk88.m_ui32NbElt = 1;
        m_vUnk88.m_pBlock = nullptr;
        m_vUnk88.m_ui32NbUsedElt = 0;
        m_pContactHistory = nullptr;
        m_vUnkA4.m_ui32NbElt = 1;
        m_vUnkA4.m_pBlock = nullptr;
        m_vUnkA4.m_ui32NbUsedElt = 0;
        m_vUnk1A0.m_ui32NbElt = 10;
        m_vUnk1A0.m_ui32NbUsedElt = 0;
        m_vUnk1A0.m_pBlock = nullptr;
    }
    ~CKHkCrumblyZone() override {}
    // vt+0x10 0x00406398 CKHkCrumblyZone_Destroy: the actor base's, the child zone references deleted, both matrices
    // destroyed, the +0x1b4 references freed (those two pointers kept, as in the original).
    void Destroy() override;

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x0040ca50 CKHkCrumblyZone_Load
    int32_t PostLoad(int32_t type) override;            // vt+0x30 0x00406080 CKHkCrumblyZone_PostLoad
    // 0x00405b40 CKHkCrumblyZone_SetGroundSets_maybe: the safe grounds (+0x24 and the list +0x28) switched to `safe`, the
    // broken ones (+0x2c, +0x30) to the opposite (ICollisionMesh_SetActive).
    void SetGroundSets(uint8_t safe);
    void SetDefaultState(int32_t flag) override;  // vt+0x38 0x00406290 CKHkCrumblyZone_SetDefaultState
    // vt+0x3c 0x00406308 CKHkCrumblyZone_SetGameState: info 1 only; state 0 restores the hit points, any other breaks
    // the zone (hit points and stage counter 0). The game modules apply it (CKGameModule ApplyLeft / ApplyDone):
    // this is how LVL010's ten courtyard walls are broken at control.
    int32_t SetGameState(const SApplyGameState* state) override;
    void Start() override;                        // vt+0x50 0x00406de0 CKHkCrumblyZone_Start
    void Restart() override;                      // vt+0x54 0x0040c7d8 CKHkCrumblyZone_Restart
    // vt+0xa0 0x0040bf00 CKHkCrumblyZone_OnActivate (IKLife::SectorLoaded calls it when the zone's sector is valid,
    // C2.4 exit): the stage node of the zone's state shown (the intact one, or the broken one when the zone is broken).
    void VfA0() override;
    void VfA4() override;  // vt+0xa4 0x0040bcd8 CKHkCrumblyZone_OnDeactivate
    // 0x0040b500 CKHkCrumblyZone_MessageProc (vt+0x1c): the actor base's answer merged with the zone's (see the .cpp): the
    // collision lists 0x300 / 0x301 (each hit to OnHit), the aim queries 0x400 / 0x402, the ground 0x401, restore 0x900,
    // crumble 0x901, reset 0x902, the hit masks and flags 0x996..0x99f, 0x9a0 (the regrowth timer stopped), the hero's
    // hazard query 0xc32 and the hit points 0x2668.
    int32_t MessageProc(uint16_t message, void* data) override;
    // vt+0x40 0x00406c20 CKHkCrumblyZone_GetInfo: the trigger values 0x4e (intact: hit points +0x188 not 0, a byte;
    // 0x00406280), 0x4f (destroyed: hit points 0, a byte; 0x00405658) and 0x50 (the hit points, an integer; 0x00406278);
    // the actor base (KStub_Return1 0x3f7140) answers 1.
    int32_t GetInfo(struct IKInfo* info, int32_t request) override;
    // vt+0x24 0x00406810 CKHkCrumblyZone_RecursiveRegistration (see the .cpp).
    void RecursiveRegistration(int32_t type) override;
    // vt+0xfc 0x0040b120 CKHkCrumblyZone_OnHit_maybe: a hit by `volume` (properties bit 2: kind 4, bit 3: kind 8) unless the
    // zone was hit this frame (+0x0c bit 10): its owner type picks the flags that let it through (1: +0x154 bits 0 / 1,
    // 2: bits 19 / 20, 5: +0x0c bits 13 / 14, 3 a hero: the hero masks +0x148 / +0x144, all heroes or the volume's hero);
    // kind 4 first (ApplyHitDamageType4), else kind 8 (ApplyHitDamageType8).
    virtual void OnHit(IKBoundingVolume* volume);
    // vt+0x100 0x009c11e0 CKHkCrumblyZone_vf100: whether the hero's hazard query (0xc32) gets the zone's hit: 1.
    virtual uint8_t Vf100(IKSerializable* /*hero*/) { return 1; }
    // 0x0040abc0 CKHkCrumblyZone_ApplyHitDamageType4_maybe / 0x0040ae70 CKHkCrumblyZone_ApplyHitDamageType8_maybe (the
    // same body, the damage +0x18e / +0x18c): the zone marked hit (+0x0c bit 10); a new touch of the contact history
    // (0.2 s, -1000) hits it: an unbreakable zone (+0x0c bit 30) or one with more hit points than the damage collapses
    // (vt+0xf4, mode 1 at the volume's position; the hit points lowered unless unbreakable) and spawns its bonuses at the
    // safe leaf; else it crumbles at the volume's position when in view (IsInCameraView).
    void ApplyHitDamageType4(IKBoundingVolume* volume);
    void ApplyHitDamageType8(IKBoundingVolume* volume);
    void ApplyHitDamage(IKBoundingVolume* volume, uint16_t damage);
    // 0x00408e58 CKHkCrumblyZone_ForceBroken_maybe: the stage counter and hit points 0; a zone in play (+0x0c bit 2 clear)
    // shows its broken leaf, switches its grounds, its volumes off, its path blocking, its component's state (+0x9c +0x0d:
    // 2 becomes 3, else 1) and stops sound 2.
    void ForceBroken();
    // 0x004085d8 CKHkCrumblyZone_Restore: the zone intact again with its effects (see the .cpp).
    void Restore();
    // 0x004057b0 CKHkS08CrumblyZone_IsInCameraView_maybe: without a view distance (+0x198 negative) 1; else the zone's
    // sphere (its node's position, the radius by the camera distance: +0x190 beyond +0x194, +0x198 within +0x19c,
    // between them interpolated) inside the camera's frustum (planes 5 .. 0). ApplyHitDamage inlines the same test.
    uint8_t IsInCameraView() const;
    // 0x00408fe8 CKHkCrumblyZone_Crumble: one stage breaks at `point` (the null point: none); see the .cpp.
    void Crumble(const struct CVector3* point, uint8_t child);
    // 0x0040aab8 CKHkCrumblyZone_StartCrumble_maybe: the animated crumble or Crumble.
    void StartCrumble(const struct CVector3* point, uint8_t child);
    // Spyro2008/hooks/CKHkS08CrumblyZone.cpp's unit (CKHkClimbZone_Update calls them on its zone +0x54):
    void RestoreIfDestroyed();   // 0x00414808 CKHkCrumblyZone_RestoreIfDestroyed_maybe: Restore when +0x188 is 0
    void CrumbleIfIntact();      // 0x00414840 CKHkCrumblyZone_CrumbleIfIntact_maybe: StartCrumble(null point, 0) when +0x188 is not 0
    void TryTriggerCollapse();   // 0x00414e00 CKHkCrumblyZone_TryTriggerCollapse_maybe: vt+0xf4 (0, null point, 0) without +0x154 bit 3
    // 0x0040aa28 CKHkCrumblyZone_UpdateCrumbleAnim_maybe (the zone Update's animated-crumble step).
    void UpdateCrumbleAnim(double dt);
    // 0x00406f90 CKHkCrumblyZone_ShowStageNode: `node` shown, the zone's other stage nodes hidden (scene node flag 4).
    void ShowStageNode(IKSerializable* node);

    // vt+0x7c 0x0040c2f8 CKHkCrumblyZone_Update (CKHkS08CrumblyZone_Update 0x414358 calls it): bit 15 of +0x158
    // cleared, the hook's bit 10 moved into bit 9; then the animated crumble (+0x158 bit 17) or the regrowth animation
    // (bit 16) advances; else an intact zone (+0x188) updates its weight (vt+0xf8), its motion (vt+0xf0, with +0x154
    // bit 3), its animation (+0x17c) and its looping sound 2; a broken one regrows after +0x11c s (+0x128, at most
    // +0x114 times). Then the path blocking (the component's step above 1) and the contact history (+0xa0).
    void Update(IKTime* clock) override;
    // vt+0xf0 0x00406410 CKHkCrumblyZone_UpdateStageNodeMotion_maybe (CKHkS08CrumblyZone_vfF0 0x4143a8 calls it).
    virtual void UpdateStageNodeMotion(IKTime* clock);
    // 0x00405d18 CKHkCrumblyZone_PickRandomStageMotionTargetByMode_maybe: `base` moved by random draws (see the .cpp).
    CVector3 PickRandomStageMotionTarget(const CVector3* base) const;
    // vt+0xf4 0x00407880 CKHkCrumblyZone_TriggerCollapse_maybe (CKHkS08CrumblyZone_vfF4 0x414380 calls it).
    virtual void TriggerCollapse(uint32_t mode, const CVector3* point, uint32_t arg);
    // vt+0xf8 0x004072a8 CKHkCrumblyZone_vfF8 (the Spyro zone's: UpdateHeroWeight 0x414638).
    virtual void VfF8();
    // 0x00405c30 CKHkCrumblyZone_CountHeroesOnZone_maybe: the heroes standing on the zone's ground (+0x24).
    uint8_t CountHeroesOnZone() const;
    // 0x009c1538 CKHkCrumblyZone_UpdatePathBlocking_maybe: the path-finding boxes of the zone's grounds (the box of each
    // ground's AABB scaled about its centre by +0x12c on x and +0x130 on z; with no ground a 1 x 1 box at the node's
    // position) in the node +0x12a's grid (CKSrvPathFinding_SetBoxBlocked_maybe). `update` 0 first frees the boxes of
    // the set that is not in use (intact: the safe grounds, else the broken ones first); then, or with `update` only
    // when +0x154 bit 17 (intact) / bit 18 (broken) is set, the other set is blocked by that bit.
    void UpdatePathBlocking(int32_t update);
    // 0x00405720 CKHkCrumblyZone_CollapseAndSpawnBonuses_maybe: the hit points set, the collapse (vt+0xf4, mode 1 at
    // `point`) and the bonuses at the safe leaf.
    void CollapseAndSpawnBonuses(uint16_t hits, const CVector3* point);
    // 0x004082f8 CKHkCrumblyZone_ResetStageRecursive_maybe: the zone intact again (hit points, stage counter, bonus data,
    // its safe leaf, grounds and volumes), and with +0x154 bit 29 its child zones (+0x1ac) too.
    void ResetStageRecursive();
    // 0x00407410 CKHkCrumblyZone_PlaceEffectNodeB0_maybe: the crumble's effect at `position` along `direction`: mode 1
    // (hook bits 24-25) the particle node +0xb0 turned and started, else a placement queued on the component's impulse
    // emitter +0xbc.
    void PlaceEffectNodeB0(const CVector3* position, const CVector3* direction);
    // 0x00407648 CKHkCrumblyZone_PlaceEffectNodeB8_maybe: the same for the collapse's effect (hook bits 22-23, the
    // particle node +0xb8, the component's emitter +0xc0).
    void PlaceEffectNodeB8(const CVector3* position, const CVector3* direction);

    IKSerializable* m_pSoundDico;              // +0x20 XXL2 m_pSoundDico (layout)
    IKSerializable* m_pGround;                 // +0x24 XXL2 m_pGround (layout)
    GroundNode* m_lAddedSafeGround;            // +0x28 XXL2 m_lAddedSafeGround (layout)
    IKSerializable* m_pBrokenGround;           // +0x2c XXL2 m_pBrokenGround (layout)
    GroundNode* m_lAddedBrokenGround;          // +0x30 XXL2 m_lAddedBrokenGround (layout)
    IKSerializable* m_pSafeLeaf;               // +0x34 XXL2 m_pSafeLeaf (layout)
    IKSerializable* m_pBrokenLeaf;             // +0x38 XXL2 m_pBrokenLeaf (layout)
    CVector3 m_vUnk3C;                         // +0x3c not set by Create or Load: the stage node's motion target
    CVector3 m_vUnk48;                         // +0x48 not set by Create or Load: the stage node's motion position
    float m_fUnk54;                            // +0x54 read (lwbrx) into a local, stored last of its group
    uint32_t m_unk58;                          // +0x58 a float word: the motion's random spread, the +0x60 reload
    uint32_t m_unk5C;                          // +0x5c a float word: the motion's duration (against +0x64)
    float m_fUnk60;                            // +0x60 runtime: a countdown reloaded with +0x58
    float m_fUnk64;                            // +0x64 runtime: the motion's time
    uint8_t m_unk68;                           // +0x68 OnActivate: how many heroes stand on the zone's ground
    uint8_t m_pad69[3];
    IKSerializable* m_pUnk6C;                  // +0x6c
    IKSerializable* m_pUnk70;                  // +0x70
    CMatrix34* m_pUnk74[2];                    // +0x74 PostLoad: two RwMatrixCreate_Thunk matrices
    TVector<IKSerializable*, 1> m_vUnk7C;      // +0x7c
    TVector<Entry8, 1> m_vUnk88;               // +0x88
    uint32_t m_unk94;                          // +0x94
    float m_fUnk98;                            // +0x98 the stage material's env map coefficient at rest
    IKSerializable* m_pUnk9C;                  // +0x9c
    struct ContactHistoryNode* m_pContactHistory;  // +0xa0 constructor 0: the contacts (ContactHistory_Update)
    TVector<Entry14, 1> m_vUnkA4;              // +0xa4
    IKSerializable* m_pUnkB0;                  // +0xb0
    uint32_t m_unkB4;                          // +0xb4
    IKSerializable* m_pUnkB8;                  // +0xb8
    uint32_t m_unkBC;                          // +0xbc
    uint32_t m_unkC0;                          // +0xc0
    IKSerializable* m_pUnkC4;                  // +0xc4
    uint32_t m_unkC8;                          // +0xc8
    float m_afUnkCC[3];                        // +0xcc a vector (Read 12 + three lwbrx)
    float m_afUnkD8[3];                        // +0xd8
    float m_afUnkE4[3];                        // +0xe4
    float m_afUnkF0[3];                        // +0xf0
    IKSerializable* m_pUnkFC;                  // +0xfc
    IKSerializable* m_pUnk100;                 // +0x100
    IKSerializable* m_pUnk104;                 // +0x104
    uint32_t m_unk108;                         // +0x108
    IKSerializable* m_pUnk10C;                 // +0x10c
    uint8_t m_unk110;                          // +0x110
    uint8_t m_pad111[3];
    uint32_t m_unk114;                         // +0x114
    uint8_t m_unk118;                          // +0x118
    uint8_t m_pad119[3];
    uint32_t m_unk11C;                         // +0x11c
    float m_fUnk120;                           // +0x120 Update: the time since the zone broke (the regrowth timer)
    int32_t m_unk124;                          // +0x124 Update: the regrowths so far (against +0x114, negative: no limit)
    uint8_t m_unk128;                          // +0x128 OnActivate 1: the regrowth timer runs
    uint8_t m_unk129;                          // +0x129
    uint16_t m_unk12A;                         // +0x12a lhbrx
    uint32_t m_unk12C;                         // +0x12c
    uint32_t m_unk130;                         // +0x130
    CTriggerStarter m_tsUnk134;                // +0x134
    CTriggerStarter m_tsUnk13C;                // +0x13c
    uint32_t m_unk144[2];                      // +0x144
    uint32_t m_unk14C;                         // +0x14c zeroed by Load for every type, then read
    uint32_t m_unk150;                         // +0x150 zeroed by Load for every type, then read
    uint32_t m_unk154;                         // +0x154
    uint32_t m_flags158;                       // +0x158 flags: Load copies bit 11 into bit 12
    uint32_t m_unk15C;                         // +0x15c
    uint32_t m_unk160;                         // +0x160
    uint32_t m_unk164;                         // +0x164
    uint8_t m_unk168;                          // +0x168
    uint8_t m_unk169;                          // +0x169
    uint8_t m_unk16A;                          // +0x16a
    uint8_t m_unk16B;                          // +0x16b
    uint8_t m_unk16C;                          // +0x16c
    uint8_t m_pad16D[3];
    uint32_t m_unk170;                         // +0x170
    uint8_t m_unk174;                          // +0x174
    uint8_t m_unk175;                          // +0x175
    uint8_t m_pad176[2];
    uint32_t m_unk178;                         // +0x178
    IKSerializable* m_pUnk17C;                 // +0x17c
    uint8_t m_unk180;                          // +0x180 OnActivate: 0 before the animation starts
    uint8_t m_unk181;                          // +0x181 OnActivate: 0 before the animation starts
    uint8_t m_pad182[2];
    uint32_t m_unk184;                         // +0x184
    uint16_t m_unk188;                         // +0x188 Load copies +0x18a into it (before reading +0x18a)
    uint16_t m_unk18A;                         // +0x18a lhbrx
    uint16_t m_unk18C;                         // +0x18c lhbrx
    uint16_t m_unk18E;                         // +0x18e lhbrx
    uint32_t m_unk190;                         // +0x190
    uint32_t m_unk194;                         // +0x194
    uint32_t m_unk198;                         // +0x198
    uint32_t m_unk19C;                         // +0x19c
    TVector<IKSerializable*, 10> m_vUnk1A0;    // +0x1a0 references (one array read)
    IKSerializable** m_apUnk1AC;               // +0x1ac OperatorNewArray, m_ui8NbUnk1AC references
    uint8_t m_ui8NbUnk1AC;                     // +0x1b0
    uint8_t m_ui8NbUnk1B4;                     // +0x1b1
    uint8_t m_pad1B2[2];
    IKSerializable** m_apUnk1B4;               // +0x1b4 Mem_AllocAligned16, m_ui8NbUnk1B4 references (0: null)
    uint8_t m_unk1B8;                          // +0x1b8 SetDefaultState: m_ui8NbUnk1B4 + 1 (a byte store)
    uint8_t m_pad1B9[3];
};
DOTD_ASSERT_SIZE(CKHkCrumblyZone, 0x1bc);
DOTD_ASSERT_OFFSET(CKHkCrumblyZone, m_pSoundDico, 0x20);
DOTD_ASSERT_OFFSET(CKHkCrumblyZone, m_lAddedSafeGround, 0x28);
DOTD_ASSERT_OFFSET(CKHkCrumblyZone, m_lAddedBrokenGround, 0x30);
DOTD_ASSERT_OFFSET(CKHkCrumblyZone, m_pBrokenLeaf, 0x38);
DOTD_ASSERT_OFFSET(CKHkCrumblyZone, m_fUnk54, 0x54);
DOTD_ASSERT_OFFSET(CKHkCrumblyZone, m_unk68, 0x68);
DOTD_ASSERT_OFFSET(CKHkCrumblyZone, m_pUnk6C, 0x6c);
DOTD_ASSERT_OFFSET(CKHkCrumblyZone, m_vUnk7C, 0x7c);
DOTD_ASSERT_OFFSET(CKHkCrumblyZone, m_vUnk88, 0x88);
DOTD_ASSERT_OFFSET(CKHkCrumblyZone, m_unk94, 0x94);
DOTD_ASSERT_OFFSET(CKHkCrumblyZone, m_pUnk9C, 0x9c);
DOTD_ASSERT_OFFSET(CKHkCrumblyZone, m_vUnkA4, 0xa4);
DOTD_ASSERT_OFFSET(CKHkCrumblyZone, m_pUnkB0, 0xb0);
DOTD_ASSERT_OFFSET(CKHkCrumblyZone, m_pUnkC4, 0xc4);
DOTD_ASSERT_OFFSET(CKHkCrumblyZone, m_afUnkCC, 0xcc);
DOTD_ASSERT_OFFSET(CKHkCrumblyZone, m_afUnkF0, 0xf0);
DOTD_ASSERT_OFFSET(CKHkCrumblyZone, m_pUnkFC, 0xfc);
DOTD_ASSERT_OFFSET(CKHkCrumblyZone, m_unk110, 0x110);
DOTD_ASSERT_OFFSET(CKHkCrumblyZone, m_unk118, 0x118);
DOTD_ASSERT_OFFSET(CKHkCrumblyZone, m_unk12A, 0x12a);
DOTD_ASSERT_OFFSET(CKHkCrumblyZone, m_tsUnk134, 0x134);
DOTD_ASSERT_OFFSET(CKHkCrumblyZone, m_tsUnk13C, 0x13c);
DOTD_ASSERT_OFFSET(CKHkCrumblyZone, m_unk14C, 0x14c);
DOTD_ASSERT_OFFSET(CKHkCrumblyZone, m_flags158, 0x158);
DOTD_ASSERT_OFFSET(CKHkCrumblyZone, m_unk168, 0x168);
DOTD_ASSERT_OFFSET(CKHkCrumblyZone, m_unk170, 0x170);
DOTD_ASSERT_OFFSET(CKHkCrumblyZone, m_unk178, 0x178);
DOTD_ASSERT_OFFSET(CKHkCrumblyZone, m_pUnk17C, 0x17c);
DOTD_ASSERT_OFFSET(CKHkCrumblyZone, m_unk180, 0x180);
DOTD_ASSERT_OFFSET(CKHkCrumblyZone, m_unk184, 0x184);
DOTD_ASSERT_OFFSET(CKHkCrumblyZone, m_unk188, 0x188);
DOTD_ASSERT_OFFSET(CKHkCrumblyZone, m_unk190, 0x190);
DOTD_ASSERT_OFFSET(CKHkCrumblyZone, m_vUnk1A0, 0x1a0);
DOTD_ASSERT_OFFSET(CKHkCrumblyZone, m_apUnk1AC, 0x1ac);
DOTD_ASSERT_OFFSET(CKHkCrumblyZone, m_ui8NbUnk1AC, 0x1b0);
DOTD_ASSERT_OFFSET(CKHkCrumblyZone, m_apUnk1B4, 0x1b4);
