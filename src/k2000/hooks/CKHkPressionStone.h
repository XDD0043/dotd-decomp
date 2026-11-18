// CKHkPressionStone.h - a pressure plate (key 0x542, vtable 0xb26100, size 0xd0). Original unit:
// CKHkPressionStone.cpp. XXL2 has CKHkPressionStone (K/KMeca/PressionStone, base IKHkMeca); DotD's derives
// from CKHkActorBase and loads more. XXL2 reads m_fMaxClearance, m_fUpSpeed, m_fDownSpeed and
// m_ui16HerosToTest in that order; DotD reads +0x50, +0x54, +0x58, then an extra word (+0x60), then the
// 16-bit word (+0x4e): the names below follow that order (_maybe).
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/misc/CKHkActorBase.h"
#include "k2000/services/CTriggerStarter.h"

class CKHkS08Hero;
class IKFx;
class IKTime;

class CKHkPressionStone : public CKHkActorBase {
public:
    DOTD_CLASS_KEY(kCategoryHook, 0x15)
    int32_t IsKindOfClass(uint32_t key) override {  // vt+0x08 0x9c30d8
        return key == 0x542 || key == 0xd82 || key == 0x2 || key == 0x2fe || key == 0x3fe || key == 0xc;
    }
    DOTD_DECLARE_FACTORIES(CKHkPressionStone)

    CKHkPressionStone() {}  // 0x00427060 CKHkPressionStone_Create: the CKHkActorBase defaults only
    ~CKHkPressionStone() override {}

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x00429618 CKHkPressionStone_Load
    // vt+0x30 0x00426410 CKHkPressionStone_PostLoad: the actor base's; for the level type +0x98 = +0x94 = 0 and the
    // six trigger lists' PostLoad (TriggerEventList_PostLoad_maybe: return 1).
    int32_t PostLoad(int32_t type) override {
        CKHkActorBase::PostLoad(type);
        if (type == K_LEVEL_PLATEFORMS) {
            m_unk98 = nullptr;
            m_unk94 = nullptr;
        }
        return 1;
    }
    void SetDefaultState(int32_t flag) override;  // vt+0x38 0x00426e50 CKHkPressionStone_SetDefaultState
    void Start() override;                        // vt+0x50 0x004263a8 CKHkPressionStone_Start
    // vt+0xc8 0x00426d20 CKHkPressionStone_ApplyStatePreset_maybe
    void ApplyStatePreset(int32_t state) override;
    // vt+0xa0 0x00429d38 CKHkPressionStone_OnActivate: flag bit 24 set and 25 cleared, the node shown, the run-time
    // words +0x30..+0x3c cleared, the moving part placed (PlaceMovingPart), the state's animation on +0x68, the node's
    // position kept (+0x20), then the path-finding block (UpdateNavBlocking).
    void VfA0() override;
    // vt+0x54 0x004280f0 CKHkPressionStone_Restart: an enabled stone (flag bit 2 clear) places its moving part again and
    // updates its path-finding block; +0x48 = 0 and +0xcc = 1 in every case.
    void Restart() override;
    // vt+0x40 0x004266e0 CKHkPressionStone_GetInfo: the trigger values (the jump table 0x0042679c on id - 0x9a): 0x9a
    // flag bit 17 (0x9c3188), 0x9b the hero of index `arg` on the stone (0x4268f0), 0xa2 / 0xa3 +0x3c / +0x38 set
    // (0x9c3148 / 0x9c3168), 0xa4 flag bit 27 (0x9c3198), all bytes, and 0xa8 the object's spawner (0x9c31b0, type 3).
    // The actor base's answer (KStub_Return1 0x3f7140) merged: the stone's.
    int32_t GetInfo(IKInfo* info, int32_t request) override;
    // vt+0x1c 0x00427608 CKHkPressionStone_MessageProc: the actor messages (0x3f7148), then the stone's: 0x93f an NPC
    // hero that is +0x34 attaches, 0x940 / 0x99a the hero +0x34 detached, 0x996 / 0x997 flag bit 18 set / cleared, 0x998
    // pressed (bits 17, 18, 26 set, 19 and 29 cleared, the moving part raised by +0x50), 0x999 released (bits 17 and 18
    // cleared, the moving part at rest), 0x99b / 0x99c the hot spot sequence; the answers merged (3, then 2, then the
    // stone's unless the base answered 0).
    int32_t MessageProc(uint16_t message, void* data) override;

    // The moving part (+0x64) at the null vector plus +0x50 along the node's modelling up row when flag bit 17 is set
    // (+0x2c = +0x50), else at the null vector (+0x2c = 0); its frame's identity flag cleared and marked dirty.
    void PlaceMovingPart();
    // The common end of OnActivate and Restart (from the store of flag bit 22): with bit 9 the stone's nav box blocked
    // (BlockNavBox), bit 26 cleared; with bit 22 the box again (bit 9) and bit 23 set; +0x48 = 0.
    void UpdateNavBlocking();
    // The stone's box in the path-finding grid (inlined twice in each of the two, and in Update / UpdateStandingHero):
    // the graph node holding +0x20 (looked up from no hint), the square of half side +0x60 * 0.75 around the found
    // point, at its height, blocked (1) or freed (0) there.
    void SetNavBox(int32_t blocked);
    void BlockNavBox() { SetNavBox(1); }
    // The moving part's frame at the null vector plus `raise` (+0x2c as stored) along the node's modelling up row, its
    // identity flag cleared and marked dirty (PlaceMovingPart's and Update's inline).
    void PlaceMovingPartAt(float raise);
    // vt+0x7c 0x004284b8 CKHkPressionStone_Update
    void Update(IKTime* frameClock) override;
    // 0x00425e28 CKHkPressionStone_AcquireInputIconFx_maybe: with no input-icon effect held (+0x94), one acquired from the
    // data +0x90 (CKSrvFx_AcquireFx inlined, this stone the owner) and placed at the node's LTM position.
    void AcquireInputIconFx();
    // 0x004260d0 CKHkPressionStone_FindPressingObject_maybe: with flag bit 6, the object on the stone (+0x3c, kept as
    // +0x40) still presses it (within +0x5c of the node, any distance when +0x5c is 0; with bit 7 its vt+0xec must be the
    // stone's ground), else the meca group's first active actor that does becomes +0x3c. 1 when one presses it.
    uint8_t FindPressingObject();
    // 0x00427a28 CKHkPressionStone_UpdateStandingHero_maybe: with flag bit 4, a hero of the +0x4e mask standing on the
    // stone (IsHeroOnStone) is +0x34 (the last one found with bit 25); a hero that left is detached (an NPC told
    // message 0xc3b, the nav box blocked again). 1 when a hero stands on it.
    uint8_t UpdateStandingHero();
    // The test UpdateStandingHero inlines twice: a hero with life bit 1 whose position is 0.1 (squared) or more from its
    // node stands on the stone when its node is within 0.25 (squared) of the stone's node; else when its ground
    // (GetGroundObject 0x363c40) is the stone's (+0x6c).
    uint8_t IsHeroOnStone(CKHkS08Hero* hero) const;
    // 0x004270b8 CKHkPressionStone_UpdateHotspotSequence_maybe: the hot spot timer (+0x48) run down by `dt`; each hot spot
    // (+0x80, from the last) whose period (+0x84) passed moves the particles (+0x78) there and emits (sound 1).
    void UpdateHotspotSequence(float dt);
    // 0x00427380 CKHkPressionStone_StartHotspotSequence_maybe: with a period (+0x84 > 0) the timer = period * (count +
    // 0.99), else every hot spot emits at once (only the particles' emission without hot spots).
    void StartHotspotSequence();
    // The particles' emission (+0x78, a CParticlesNodeFx) both hot spot functions inline: scene bits 9 and 10 set, 19
    // cleared, the emission speed adjustment 0, the emitter's flags 0xa.
    void EmitParticles();
    // The particles moved to hot spot `index` (relative to the animated node +0x68), emitted, sound 1 played.
    void EmitAtHotspot(uint32_t index);
    // vt+0xe4 0x009c3140 CKHkPressionStone_vfE4 / vt+0xe8 0x009c31a8 CKHkPressionStone_vfE8 (inline; non-virtual here,
    // only stones answer them): the stone's ground count (1) and its ground (+0x6c, whatever the index).
    uint32_t GetGroundCount() const { return 1; }
    // vt+0xa4 0x00426fa0 CKHkPressionStone_OnDeactivate: the hero attached to the stone (+0x34) detached and forgotten, the
    // input-icon effect (+0x94) released.
    void VfA4() override;
    // vt+0x10 0x00426658 CKHkPressionStone_Destroy: the +0x80 references freed (Mem_FreeAligned16) and cleared.
    void Destroy() override;
    IKSerializable* GetGround(uint32_t /*index*/) const { return m_apUnk6C[0]; }

    // 0x00425cd0 CKHkPressionStone_SetOccupant_maybe (CKHkPressionStoneGroup): `set` claims the stone for `hero` (free or
    // already its own), else a claim of `hero` is let go. 1 when done.
    uint8_t SetOccupant(IKSerializable* hero, int32_t set);
    // 0x004275c8 CKHkPressionStone_ClearFlagC28_StartHotspotSequenceIfFlagC27_maybe (CKHkPressionStoneGroup_MessageProc;
    // message 0x99c inlines it): flag bit 28 cleared; with bit 27 bits 27 and 28 cleared and the hot spot sequence started.
    void StopHotspotHold();
    // 0x0042a1a8 CKHkPressionStone_SetNavBlockedForGroup_maybe: for the stone's occupant `hero` only, flag bit 22 =
    // `blocked` (the byte shifted in) and, with bit 9, the nav box blocked or freed.
    void SetNavBlockedForGroup(IKSerializable* hero, uint8_t blocked);
    // vt+0xb4 0x00426a20 CKHkPressionStone_AttachSounds: sounds 0 and 1 (+0x8c) on the node; a dynamic ground (+0x70,
    // key 0x4cc) gets `leaf` as its parent and the inverse of its matrix (identity without one); the moving part (+0x64)
    // leaves its parent and goes under the node.
    void KGLObjectAttached(IKSerializable* leaf) override;

    CVector3 m_vPosition;                 // +0x20 runtime: OnActivate keeps the node's LTM position
    float m_fRaise;                       // +0x2c runtime: +0x50 (flag bit 17) or 0, the moving part's offset
    // +0x30..+0x48 runtime (OnActivate clears +0x30..+0x3c, Start +0x40..+0x48; Update and its helpers write them):
    // GetInfo reads +0x34 as a hero (its dragon index, 0x9b), +0x38 and +0x3c as flags (0xa3 / 0xa2) and +0x3c as an
    // object (a transportable's spawner, 0xa8).
    // +0x30 the group hero that claims the stone (SetOccupant, CKHkPressionStoneGroup); cleared by OnActivate / Restart.
    IKSerializable* m_unk30;
    IKSerializable* m_pHero;              // +0x34 _maybe the hero on the stone (CKHkS08Hero_GetDragonIndex 0x361960)
    IKSerializable* m_unk38;              // +0x38 the enemy on the stone (flag bit 5: an active enemy whose ground is +0x6c)
    IKSerializable* m_pObject;            // +0x3c _maybe the object on the stone (IsKindOf 0x3002: a transportable)
    IKSerializable* m_unk40;              // +0x40 the object that pressed the stone (FindPressingObject keeps +0x3c here)
    IKSerializable* m_unk44;              // +0x44 the last hero on the stone (UpdateStandingHero)
    float m_unk48;                        // +0x48 the hot spot sequence's timer (StartHotspotSequence / UpdateHotspotSequence)
    uint8_t m_unk4C;                      // +0x4c
    uint8_t m_pad4D;
    uint16_t m_ui16HerosToTest;           // +0x4e _maybe XXL2 m_ui16HerosToTest
    float m_fMaxClearance;                // +0x50 _maybe XXL2 m_fMaxClearance
    float m_fUpSpeed;                     // +0x54 _maybe XXL2 m_fUpSpeed
    float m_fDownSpeed;                   // +0x58 _maybe XXL2 m_fDownSpeed
    float m_unk5C;                        // +0x5c
    float m_unk60;                        // +0x60
    IKSerializable* m_unk64;              // +0x64
    IKSerializable* m_unk68;              // +0x68
    IKSerializable* m_apUnk6C[3];         // +0x6c one contiguous read of three references
    IKSerializable* m_unk78;              // +0x78
    uint8_t m_unk7C;                      // +0x7c the count of +0x80
    uint8_t m_pad7D[3];
    IKSerializable** m_apUnk80;           // +0x80 references (Mem_AllocAligned16), 0 without
    float m_unk84;                        // +0x84
    IKSerializable* m_unk88;              // +0x88
    IKSerializable* m_unk8C;              // +0x8c
    IKSerializable* m_unk90;              // +0x90 read for K_LEVEL_PLATEFORMS only
    IKFx* m_unk94;                        // +0x94 runtime: the input-icon effect (vt+0x58 releases it); 0 at PostLoad (0x426410)
    IKSerializable* m_unk98;              // +0x98 runtime: 0 at PostLoad; the carrier hero near it (CKS08CarrierHero_CarryState_maybe)
    CTriggerStarter m_unk9C;              // +0x9c
    CTriggerStarter m_unkA4;              // +0xa4
    CTriggerStarter m_unkAC;              // +0xac
    CTriggerStarter m_unkB4;              // +0xb4
    CTriggerStarter m_unkBC;              // +0xbc
    CTriggerStarter m_unkC4;              // +0xc4
    uint8_t m_unkCC;                      // +0xcc runtime (Start stores a byte)
    uint8_t m_padCD[3];
};
DOTD_ASSERT_SIZE(CKHkPressionStone, 0xd0);
DOTD_ASSERT_OFFSET(CKHkPressionStone, m_vPosition, 0x20);
DOTD_ASSERT_OFFSET(CKHkPressionStone, m_fRaise, 0x2c);
DOTD_ASSERT_OFFSET(CKHkPressionStone, m_unk30, 0x30);
DOTD_ASSERT_OFFSET(CKHkPressionStone, m_pHero, 0x34);
DOTD_ASSERT_OFFSET(CKHkPressionStone, m_pObject, 0x3c);
DOTD_ASSERT_OFFSET(CKHkPressionStone, m_unk48, 0x48);
DOTD_ASSERT_OFFSET(CKHkPressionStone, m_unk4C, 0x4c);
DOTD_ASSERT_OFFSET(CKHkPressionStone, m_ui16HerosToTest, 0x4e);
DOTD_ASSERT_OFFSET(CKHkPressionStone, m_fMaxClearance, 0x50);
DOTD_ASSERT_OFFSET(CKHkPressionStone, m_unk5C, 0x5c);
DOTD_ASSERT_OFFSET(CKHkPressionStone, m_unk60, 0x60);
DOTD_ASSERT_OFFSET(CKHkPressionStone, m_unk64, 0x64);
DOTD_ASSERT_OFFSET(CKHkPressionStone, m_apUnk6C, 0x6c);
DOTD_ASSERT_OFFSET(CKHkPressionStone, m_unk78, 0x78);
DOTD_ASSERT_OFFSET(CKHkPressionStone, m_unk7C, 0x7c);
DOTD_ASSERT_OFFSET(CKHkPressionStone, m_apUnk80, 0x80);
DOTD_ASSERT_OFFSET(CKHkPressionStone, m_unk84, 0x84);
DOTD_ASSERT_OFFSET(CKHkPressionStone, m_unk88, 0x88);
DOTD_ASSERT_OFFSET(CKHkPressionStone, m_unk90, 0x90);
DOTD_ASSERT_OFFSET(CKHkPressionStone, m_unk9C, 0x9c);
DOTD_ASSERT_OFFSET(CKHkPressionStone, m_unkC4, 0xc4);
