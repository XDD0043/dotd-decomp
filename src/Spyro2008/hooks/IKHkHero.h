// IKHkHero.h - the base of the heroes (key 0x3642, unregistered; Ghidra CKHkS08HeroBase_3642_maybe; XXL2
// K/KHero/IKHkHero.h, whose IKHkHero::Load reads the same members in nearly the same order). Original unit:
// IKHkHero.cpp (0x344ef0-0x34f9f0). Size 0x848_maybe: the last member the CKHkS08Hero constructor sets before
// it stores the derived vtable ends there.
//
// Names: XXL2's where its Load reads the same thing at the same place in the read order (m_pGrpHero ...
// m_afBoundingsRadius, m_PFCpnt, the ground contacts); m_unkXXX elsewhere. +0x1c8..+0x351 is XXL2's
// m_sProperties (SHeroProperties, 220 bytes there, 0x18a here); its members are not mapped.
#pragma once
#include "k2000/math/Math.h"
#include <cstdint>

#include "k2000/animation/AnimBlendSlot.h"
#include "k2000/components/CKPathFindingCpnt.h"
#include "k2000/core/Layout.h"
#include "k2000/hooks/GroundContact.h"
#include "k2000/hooks/IKHook.h"
#include "k2000/math/CMatrix34.h"
#include "k2000/services/CollisionDatas.h"

// XXL2 SHeroInitialState (28 bytes there; DotD adds +0x1c and +0x20). Read by ReadHeroInitialState.
struct SHeroInitialState {
    CVector3 m_vPos;             // +0x00
    CVector3 m_vDir;             // +0x0c
    uint8_t m_ui8TrackedLeader;  // +0x18
    uint8_t m_ui8Leader;         // +0x19
    uint8_t m_pad1a[2];
    uint32_t m_unk1c;            // +0x1c a byte from the file, widened
    uint8_t m_unk20;             // +0x20
    uint8_t m_pad21[3];
};
DOTD_ASSERT_SIZE(SHeroInitialState, 0x24);

// XXL2 SHeroSpeedMode: the same 40 bytes and the same read order.
struct SHeroSpeedMode {
    float m_afHSpeeds[3];            // +0x00
    float m_afAnimHSpeeds[3];        // +0x0c
    float m_fMaxHSpeed;              // +0x18
    uint16_t m_aui16YRotSpeeds[2];   // +0x1c
    uint8_t m_ui8Threshold;          // +0x20
    uint8_t m_bDefaultEnable;        // +0x21
    uint8_t m_abAnimMustBeTurned[3]; // +0x22 read raw (3 bytes)
    uint8_t m_bEnable;               // +0x25 not read
    uint8_t m_bLocked;               // +0x26 not read
    uint8_t m_pad27;
};
DOTD_ASSERT_SIZE(SHeroSpeedMode, 0x28);

// XXL2 SHeroJump.
struct SHeroJump {
    float m_fImpulse;          // +0x00
    uint8_t m_bDefaultEnable;  // +0x04
    uint8_t m_bEnable;         // +0x05 not read
    uint8_t m_bLocked;         // +0x06 not read
    uint8_t m_pad07;
};
DOTD_ASSERT_SIZE(SHeroJump, 0x8);

// One row (0x14 bytes) of a hero state table (the hero group's tables at 0xc4b1e0 / 0xc4b2bc / 0xc4b398 /
// 0xc4b3fc, copied and sorted by the hero's InitRuntimeTables): two pointers to member functions of the hero
// (PS3 function descriptor + this-adjust: the state's enter/exit handler and its update) and the state id in
// the top byte of the last word. DOTD: the words stay the PS3's descriptor addresses; CKHkS08Hero::CallStateHandler /
// CallStateCondition map them to native functions (k2000/core/Ps3MemberFn.h).
struct SHeroStateRow {
    uint32_t m_aPtmf0[2];  // +0x00 descriptor, adjust
    uint32_t m_aPtmf1[2];  // +0x08
    uint32_t m_key;        // +0x10 the state id is the top byte
};
DOTD_ASSERT_SIZE(SHeroStateRow, 0x14);

// The first pointer to member function of a row, in the 8-byte array the hero indexes by state id.
struct SHeroStateHandler {
    uint32_t m_aPtmf[2];
};
DOTD_ASSERT_SIZE(SHeroStateHandler, 0x8);

class IKHkHero : public IKHook {
public:
    DOTD_CLASS_KEY(kCategoryHook, 0xd9)

    IKHkHero();  // the IKHkHero part of 0x002dd000 CKHkS08Hero_Create (inlined constructor)
    ~IKHkHero() override {}

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x00349930 CKHkS08HeroBase_Load_maybe

    int32_t PostLoad(int32_t type) override;        // vt+0x30 0x00346400 IKHkHero_PostLoad
    // vt+0xbc 0x00344d48 IKHkHero_GetCinematicAnimSlots (k2000/logic/CKControlableHero.cpp): the group's blend slot count
    // for this hero (vt+0x134, a byte) and that many slots of the +0x138 array, from the last. CKHkS08Hero overrides it.
    void GetBlendSlot(AnimBlendSlot** slots, int32_t* count) override;
    // vt+0x40 0x003462c0 IKHkHero_GetInfo (Ghidra IKHkHero_ResolveTriggerProperty_maybe): the trigger values 0 (not
    // +0x354 bit 0, a byte), 1 (the distance to the controlling dragon, a float) and 2 (controlled by itself, a byte).
    int32_t GetInfo(struct IKInfo* info, int32_t request) override;

    // C2.2 spyro: the level start.
    void Start() override;                          // vt+0x50 0x003462b0 IKHkHero_vf50
    // vt+0xd4 0x002d8c58 CKHkS08Hero_vfD4: five state bytes cleared (called by InitRuntimeTables).
    virtual void VfD4() = 0;
    // vt+0xd8 0x002dbb50 CKHkS08Hero_InitAnimBlendSlot (called by PostLoad).
    virtual void InitAnimBlendSlot() = 0;
    // vt+0x130 0x0030d528 CKHkS08Hero_RestoreDefaultVolumes_maybe (called through IKHkHero_CallRestoreDefaultVolumes
    // 0x00352bf8).
    virtual void RestoreDefaultVolumes() = 0;
    // vt+0x160: the height of the hero's collision body (CKHkS08Hero returns m_unk894).
    virtual float Vf160() = 0;
    void InitRuntimeTables();                       // 0x00345408 IKHkHero_InitRuntimeTables_maybe
    void ResetRuntimeState(int32_t flag);           // 0x00346480 IKHkHero_ResetRuntimeState_maybe
    // vt+0xac 0x00347528 IKHkHero_OnDisable_maybe (OnUnlock): ResetRuntimeState(0). CKHkS08Hero_OnUnlock 0x2dafa8 calls it.
    void OnUnlock() override { ResetRuntimeState(0); }
    // vt+0x24 0x00345b60 CKHkS08HeroBase_LevelReset_maybe (RecursiveRegistration; CKHkS08Hero_RecursiveRegistration
    // 0x2d98f8 calls it first): IKHook's, then outside the memory-card types 4..7 the hero registered with the saving
    // manager (no owner), its hot spots and objects (the group's per-hero counts, vt+0xf8 / vt+0x104), the animation and
    // sound dictionaries, the shadow component and the water wave / splash FX data registered with the same type.
    void RecursiveRegistration(int32_t type) override;

    // C2.8 port-all P16: the hero accessors of IKHkHero_2.cpp the meca / platform / bridge / squad code calls (several
    // callers inline them); the bodies are in IKHkHero_2.cpp.
    CPFCharacter* GetPFCharacter();                 // 0x00361a30 IKHkHero_GetPtr3E0_maybe: +0x3e0
    void* GetPFDestination();                       // 0x00361a40 IKHkHero_GetVec3Ptr430_maybe: +0x430 (the path cpnt's)
    float* GetUnk3B8Ptr();                          // 0x00361a60 IKHkHero_GetVec3Ptr3B8_maybe: +0x3b8
    uint32_t GetFlag354Bit0() const;                // 0x00361a90 IKHkHero_GetFlag354Bit0_Word_maybe
    uint32_t GetFlag35CBit8() const;                // 0x00361ab0 IKHkHero_GetFlag35CBit8_maybe
    uint32_t IsInvulnerable() const;                // 0x00361b10 IKHkHero_IsInvulnerable_maybe: +0x35c bit 2
    uint32_t GetFlag358Bit8() const;                // 0x00361b50 IKHkHero_GetFlag358Bit8_maybe
    float GetUnk26C() const;                        // 0x00361b60 IKHkHero_GetFloat26C_maybe
    float GetUnk510() const;                        // 0x00361c00 CKHkS08Hero_GetFloat510_maybe
    float GetUnk530() const;                        // 0x00361c10 IKHkHero_GetFloat530_maybe
    CGroundContactDatasIn* GetGroundContactIn();    // 0x00361ca0 IKHkHero_GetVec3Ptr4A8_maybe: +0x4a8
    void SetFlag354Bit9(uint8_t on);                // 0x00361cc0 IKHkHero_SetFlag354Bit9_maybe
    void SetFlag364Bit5();                          // 0x00361d98 IKHkHero_SetFlag364Bit5_maybe
    uint32_t IsObjectControllingAnim() const;       // 0x00362000 IKHkHero_IsObjectControllingAnim_maybe: +0x358 bit 1
    uint32_t GetFlag35CBit0IfAttached() const;      // 0x00362878 IKHkHero_GetFlag35CBit0_IfAttached_maybe
    void ClearFlag358Bit21IfAttached();             // 0x003628e0 IKHkHero_ClearFlag358Bit21_IfAttached_maybe
    // 0x00362fd0 IKHkHero_SetPendingSourceAndVec3_Flag35CBit4_maybe: with a source, +0xd4 = it, +0xd8 = `point` (null: the
    // zero vector 0x00c50d64) and +0x35c bit 4 set.
    void SetPendingSource(IKSerializable* source, const float* point);
    IKSerializable* GetLedgeGroundContact() const;  // 0x00363770 IKHkHero_GetLedgeGroundContact_maybe: +0x35c bit 22: +0x81c
    // 0x00363c78 IKHkHero_GetTargetingPositionPtr_maybe: the node's world position (frame LTM) with life bit 1, else +0x570.
    const float* GetTargetingPositionPtr();
    uint32_t GetFlag360Bit12() const;               // 0x00363ca0 IKHkHero_GetFlag360Bit12_maybe
    void ApplyPositionToFrame();                    // 0x00355c00 IKHkHero_ApplyPositionToFrame_maybe
    // 0x00359988 IKHkHero_SetPositionAndDirection_maybe: either argument null takes the scene node's current one.
    void SetPositionAndDirection(const CVector3* position, const CVector3* direction);

    // 0x00349730 CKHkS08HeroBase_LoadArray2xVec3_4xU8_maybe (XXL2 IKHkHero::ReadHeroInitialState)
    void ReadHeroInitialState(IKFile* file, int32_t type, SHeroInitialState* states, uint32_t count);
    // 0x003493c0 CKHkS08HeroBase_LoadArray2xVec3_2xU32_5xU8_maybe (XXL2 IKHkHero::ReadHeroSpeedMode)
    void ReadHeroSpeedMode(IKFile* file, int32_t type, SHeroSpeedMode* modes, uint32_t count);

    // 0x00345140 IKHkHero_FreeBuffers_maybe (CKHkS08Hero_Destroy; 0x3452c0, the IKHkHero vtable's Destroy, branches to it):
    // the hero's buffers freed (the pointers are kept), the blend slots deleted.
    void FreeBuffers();
    void Destroy() override { FreeBuffers(); }  // vt+0x10 0x003452c0

    IKSerializable* m_pGrpHero;                  // +0x20 XXL2 IKGrpHero* m_pGrpHero; a CKGrpS08Hero (the only IKGrpHero in DotD)
    uint8_t m_ui8Hero;                           // +0x24 XXL2 m_ui8Hero (the hero index; 0 and 1 in LVL010)
    uint8_t m_ui8TrackedLeader;                  // +0x25 XXL2 m_ui8TrackedLeader
    uint8_t m_ui8Leader;                         // +0x26 XXL2 m_ui8Leader
    uint8_t m_pad27[1];
    SHeroInitialState m_aInitialStates[1];       // +0x28 XXL2 m_aInitialStates
    IKSerializable** m_apHotSpots;               // +0x4c XXL2 CSGHotSpot** m_apHotSpots (count byte + references)
    IKSerializable** m_apParticles;              // +0x50 XXL2 CParticlesNodeFx** m_apParticles
    IKSerializable** m_apBoundings;              // +0x54 XXL2 IKBoundingVolume** m_apBoundings
    IKSerializable** m_apObjects;                // +0x58 XXL2 CNode** m_apObjects
    IKSerializable** m_apTrails;                 // +0x5c XXL2 CTrailNodeFx** m_apTrails
    IKSerializable* m_pShadowCpnt;               // +0x60 XXL2 m_pShadowCpnt (CKShadowCpnt)
    float m_unk64;  // +0x64  (C2.2 spyro)
    float m_unk68;  // +0x68  (C2.2 spyro)
    float m_unk6c;  // +0x6c  (C2.2 spyro)
    float m_unk70;  // +0x70  (C2.2 strict3)
    float m_unk74;  // +0x74  (C2.2 strict3)
    float m_unk78;  // +0x78  (C2.2 strict3)
    uint32_t m_unk7c;  // +0x7c  (C2.2 strict3)
    uint8_t m_unk80;                             // +0x80 constructor 0
    uint8_t m_unk81;  // +0x81  (C2.2 strict3)
    uint8_t m_pad82[2];
    IKSerializable* m_pWaterWaveFxData;          // +0x84 CKWaterWaveFxData (embedded in XXL2, a reference in DotD)
    class IKFx* m_unk88;  // +0x88 the water wave effect (a CKWaterWaveNodeFx, reserved: UpdateMainShadowAndSurfaceFx)
    IKSerializable* m_pWaterSplashFxData;        // +0x8c CKWaterSplashFxData (embedded in XXL2, a reference in DotD)
    IKSerializable* m_unk90;  // +0x90  (C2.2 strict3) receives the hero message 0xc4d
    uint32_t m_unk94;  // +0x94  (C2.2 strict3)
    IKSerializable* m_unk98;  // +0x98 the object a message 0x93e asks the hero to attach to (HeroBaseMessageProc)
    uint32_t m_unk9c;  // +0x9c  (C2.2 strict3)
    SHeroStateRow* m_unka0;  // +0xa0  (C2.2 strict3)
    SHeroStateHandler* m_unka4;  // +0xa4  (C2.2 strict3)
    SHeroStateHandler* m_unka8;  // +0xa8  (C2.2 strict3)
    uint8_t m_unkAC;                             // +0xac constructor 0xff
    uint8_t m_unkAD;                             // +0xad constructor 0xff
    uint8_t m_padae[2];
    uint8_t m_unkb0;  // +0xb0  (C2.2 strict3)
    uint8_t m_padb1[3];
    float m_unkb4;  // +0xb4  (C2.2 strict3)
    float m_unkb8;  // +0xb8  (C2.2 strict3)
    float m_unkbc;  // +0xbc  (C2.2 strict3; a float: the squared distance to the focused dragon)
    SHeroStateRow* m_unkc0;  // +0xc0  (C2.2 strict3)
    SHeroStateHandler* m_unkc4;  // +0xc4  (C2.2 strict3)
    SHeroStateHandler* m_unkc8;  // +0xc8  (C2.2 strict3)
    uint8_t m_unkCC;                             // +0xcc constructor 0xff
    uint8_t m_unkCD;                             // +0xcd constructor 0xff
    uint8_t m_padce[2];
    uint8_t m_unkd0;  // +0xd0  (C2.2 strict3)
    uint8_t m_padd1[3];
    IKSerializable* m_unkd4;  // +0xd4 the pending hit's source (+0x35c bit 4; ResolveHeroContactMovement)
    float m_unkd8;  // +0xd8  (C2.2 strict3)
    float m_unkdc;  // +0xdc  (C2.2 strict3)
    float m_unke0;  // +0xe0  (C2.2 strict3)
    IKSerializable* m_unke4;  // +0xe4  (C2.2 strict3) the volume last touched (ResolveHeroContactMovement_maybe)
    float m_unke8;  // +0xe8  (C2.2 strict3)
    float m_unkec;  // +0xec  (C2.2 strict3)
    float m_unkf0;  // +0xf0  (C2.2 strict3)
    uint32_t m_unkf4;  // +0xf4  (C2.2 strict3)
    float m_unkf8;  // +0xf8  (C2.2 strict3)
    float m_unkfc;  // +0xfc  (C2.2 strict3)
    float m_unk100;  // +0x100  (C2.2 strict3)
    uint32_t m_unk104;  // +0x104  (C2.2 strict3)
    IKSerializable* m_unk108;  // +0x108  (C2.2 strict3) the owner of the last solid contact (ResolveHeroContactMovement_maybe)
    ContactHistoryNode* m_unk10c;                // +0x10c constructor 0; the volumes that hurt the hero (ContactHistory)
    ContactHistoryNode* m_unk110;                // +0x110 constructor 0; the volumes the hero touched (ContactHistory)
    float m_unk114;  // +0x114  (C2.2 strict3)
    uint8_t m_unk118;  // +0x118  (C2.2 strict3)
    uint8_t m_pad119[3];
    float m_unk11c;  // +0x11c  (C2.2 strict3)
    IKSerializable* m_unk120;  // +0x120 a target (GetAITarget(0) first)
    IKSerializable* m_unk124;  // +0x124 the grabbed enemy _maybe (ApplyGrabbedEnemyMarkDamage: a CKHkS08Enemy)
    IKSerializable* m_unk128;  // +0x128 a target (GetAITarget(0) second)
    IKSerializable* m_unk12c;  // +0x12c the targeted hook (a crumbly zone; GetAITarget(1) second)
    uint8_t m_unk130;  // +0x130  (C2.2 strict3)
    uint8_t m_pad131[3];
    IKSerializable** m_apUnk134;                 // +0x134 count byte + references (allocated even for 0)
    AnimBlendSlot* m_unk138;  // +0x138  (C2.2 strict3)
    IKSerializable* m_pAnimDico;                 // +0x13c XXL2 m_pAnimDico (CAnimationDictionary; the XXL2 reads come in another order)
    SHeroStateRow* m_unk140;  // +0x140  (C2.2 strict3)
    SHeroStateHandler* m_unk144;  // +0x144  (C2.2 strict3)
    SHeroStateHandler* m_unk148;  // +0x148  (C2.2 strict3)
    uint8_t m_unk14c;                            // +0x14c constructor 0xff
    uint8_t m_unk14d;                            // +0x14d constructor 0xff
    uint8_t m_pad14e[2];
    uint32_t m_unk150;  // +0x150  (C2.2 strict3)
    float m_unk154;  // +0x154  (C2.2 strict3; AdvanceAnimTime: the last frame time)
    float m_unk158;  // +0x158  (C2.2 strict3; PlayAnim: the blend time)
    float m_unk15c;  // +0x15c  (C2.2 strict3; PlayAnim: the start time)
    // +0x158..+0x160 are also read as one vector (ResolveHeroContactMovement_maybe 0x353528 compares the partner's
    // with the null vector; the anim id +0x160 is the upper half of its z).
    uint16_t m_unk160;  // +0x160 the animation id (CKHkS08HeroBase_PlayAnim sth; UpdateGroundMovement lhz)
    uint8_t m_pad162[2];
    IKSerializable* m_unk164;  // +0x164  (C2.2 spyro)
    IKSerializable* m_pSoundDico;                // +0x168 XXL2 m_pSoundDico (CKSoundDictionaryID)
    uint8_t m_unk16c;  // +0x16c  (C2.2 strict3)
    uint8_t m_unk16d;  // +0x16d  (C2.2 strict3)
    uint8_t m_unk16e;  // +0x16e  (C2.2 strict3)
    uint8_t m_unk16f;  // +0x16f  (C2.2 strict3)
    uint8_t m_unk170;  // +0x170  (C2.2 strict3)
    uint8_t m_unk171;  // +0x171  (C2.2 strict3)
    uint8_t m_unk172;  // +0x172  (C2.2 strict3)
    uint8_t m_pad173[1];
    CGroundContactDatasInOut m_unk174;           // +0x174 constructor defaults only
    IKSerializable* m_unk1a0;                    // +0x1a0
    uint8_t m_aui8Unk1a4[24];                    // +0x1a4 24 bytes; XXL2 reads m_i8HotLeftFootIndex, m_i8HotRightFootIndex and SHeroCapabilities (21) here
    SHeroSpeedMode* m_asSpeedModes;              // +0x1bc XXL2 m_asSpeedModes (count from the hero group)
    SHeroJump* m_asJumps;                        // +0x1c0 XXL2 m_asJumps (count from the hero group)
    float* m_afBoundingsRadius;                  // +0x1c4 XXL2 m_afBoundingsRadius (one per bounding)
    float m_unk1c8;                              // +0x1c8
    float m_unk1cc;                              // +0x1cc
    float m_unk1d0;                              // +0x1d0
    float m_unk1d4;                              // +0x1d4
    uint32_t m_unk1d8;                           // +0x1d8
    float m_unk1dc;                              // +0x1dc
    uint32_t m_unk1e0;                           // +0x1e0
    float m_unk1e4;                              // +0x1e4
    uint32_t m_unk1e8;                           // +0x1e8
    float m_unk1ec;                              // +0x1ec
    float m_unk1f0;                              // +0x1f0
    float m_unk1f4;                              // +0x1f4
    float m_unk1f8;                              // +0x1f8
    float m_unk1fc;                              // +0x1fc
    float m_unk200;                              // +0x200
    float m_unk204;                              // +0x204
    float m_unk208;                              // +0x208
    float m_unk20c;                              // +0x20c
    float m_unk210;                              // +0x210
    float m_unk214;                              // +0x214
    float m_unk218;                              // +0x218
    float m_unk21c;                              // +0x21c
    float m_unk220;                              // +0x220
    float m_unk224;                              // +0x224
    float m_unk228;                              // +0x228
    float m_unk22c;                              // +0x22c
    float m_unk230;                              // +0x230
    float m_unk234;                              // +0x234
    float m_unk238;                              // +0x238
    float m_unk23c;                              // +0x23c
    float m_unk240;                              // +0x240
    float m_unk244;                              // +0x244
    float m_unk248;                              // +0x248
    float m_unk24c;                              // +0x24c
    float m_unk250;                              // +0x250
    float m_unk254;                              // +0x254
    float m_unk258;                              // +0x258
    float m_unk25c;                              // +0x25c
    float m_unk260;                              // +0x260
    float m_unk264;                              // +0x264
    float m_unk268;                              // +0x268
    float m_unk26c;                              // +0x26c
    float m_unk270;                              // +0x270
    float m_unk274;                              // +0x274
    float m_unk278;                              // +0x278
    float m_unk27c;                              // +0x27c
    float m_unk280;                              // +0x280
    float m_unk284;                              // +0x284
    float m_unk288;                              // +0x288
    float m_unk28c;                              // +0x28c
    float m_unk290;                              // +0x290
    float m_unk294;                              // +0x294
    float m_unk298;                              // +0x298
    float m_unk29c;                              // +0x29c
    float m_unk2a0;                              // +0x2a0
    float m_unk2a4;                              // +0x2a4
    float m_unk2a8;                              // +0x2a8
    float m_unk2ac;                              // +0x2ac
    float m_unk2b0;                              // +0x2b0
    float m_unk2b4;                              // +0x2b4
    float m_unk2b8;                              // +0x2b8
    float m_unk2bc;                              // +0x2bc
    float m_unk2c0;                              // +0x2c0
    float m_unk2c4;                              // +0x2c4
    float m_unk2c8;                              // +0x2c8
    float m_unk2cc;                              // +0x2cc
    float m_unk2d0;                              // +0x2d0
    float m_unk2d4;                              // +0x2d4
    float m_unk2d8;                              // +0x2d8
    float m_unk2dc;                              // +0x2dc
    float m_unk2e0;                              // +0x2e0
    float m_unk2e4;                              // +0x2e4
    float m_unk2e8;                              // +0x2e8
    float m_unk2ec;                              // +0x2ec
    float m_unk2f0;                              // +0x2f0
    float m_unk2f4;                              // +0x2f4
    float m_unk2f8;                              // +0x2f8
    float m_unk2fc;                              // +0x2fc
    float m_unk300;                              // +0x300 the fall height that hurts (UpdateHazardAndSavedPositionRespawn)
    float m_unk304;                              // +0x304
    float m_unk308;                              // +0x308
    float m_unk30c;                              // +0x30c
    float m_unk310;                              // +0x310
    float m_unk314;                              // +0x314
    float m_unk318;                              // +0x318
    float m_unk31c;                              // +0x31c
    float m_unk320;                              // +0x320
    float m_unk324;                              // +0x324
    float m_unk328;                              // +0x328
    float m_unk32c;                              // +0x32c
    int32_t m_unk330;                            // +0x330
    uint16_t m_unk334;                           // +0x334
    uint16_t m_unk336;                           // +0x336
    uint16_t m_unk338;                           // +0x338
    uint16_t m_unk33a;                           // +0x33a
    uint16_t m_unk33c;                           // +0x33c
    uint16_t m_unk33e;                           // +0x33e
    uint16_t m_unk340;                           // +0x340
    uint8_t m_unk342;                            // +0x342
    uint8_t m_unk343;                            // +0x343
    uint8_t m_unk344;                            // +0x344
    uint8_t m_unk345;                            // +0x345
    uint8_t m_unk346;                            // +0x346
    uint8_t m_unk347;                            // +0x347
    uint8_t m_unk348;                            // +0x348
    uint8_t m_unk349;                            // +0x349
    uint8_t m_unk34a;                            // +0x34a
    uint8_t m_unk34b;                            // +0x34b
    uint8_t m_unk34c;                            // +0x34c
    uint8_t m_unk34d;                            // +0x34d
    uint8_t m_unk34e;                            // +0x34e
    uint8_t m_unk34f;                            // +0x34f
    uint8_t m_unk350;                            // +0x350
    uint8_t m_pad351[3];
    uint32_t m_unk354;  // +0x354  (C2.2 strict3)
    uint32_t m_unk358;  // +0x358  (C2.2 spyro)
    uint32_t m_unk35c;  // +0x35c  (C2.2 strict3)
    uint32_t m_unk360;  // +0x360  (C2.2 strict3)
    uint32_t m_unk364;  // +0x364  (C2.2 strict3)
    uint32_t m_unk368;  // +0x368  (C2.2 spyro)
    uint8_t* m_unk36c;  // +0x36c  (C2.2 strict3)
    float m_unk370;  // +0x370  (C2.2 strict3)
    float m_unk374;  // +0x374  (C2.2 strict3)
    float m_unk378;  // +0x378  (C2.2 strict3)
    float m_unk37c;  // +0x37c  (C2.2 spyro)
    float m_unk380;  // +0x380  (C2.2 spyro)
    float m_unk384;  // +0x384  (C2.2 spyro)
    float m_unk388;  // +0x388 the time input 4 is held (ReadHeroPlayerInput: the game manager's GetActionValue)
    float m_unk38c;  // +0x38c the same for input 5
    uint16_t m_unk390;  // +0x390  (C2.2 strict3)
    uint16_t m_unk392;  // +0x392  (C2.2 strict3)
    uint8_t m_unk394;  // +0x394  (C2.2 strict3)
    uint8_t m_unk395;  // +0x395  (C2.2 strict3)
    uint8_t m_pad396[2];
    float m_unk398;  // +0x398  (C2.2 strict3)
    float m_unk39c;  // +0x39c  (C2.2 strict3)
    float m_unk3a0;  // +0x3a0  (C2.2 strict3)
    float m_unk3a4;  // +0x3a4  (C2.2 strict3)
    float m_unk3a8;  // +0x3a8  (C2.2 strict3)
    float m_unk3ac;  // +0x3ac  (C2.2 strict3)
    uint32_t m_unk3b0;  // +0x3b0  (C2.2 strict3)
    uint8_t m_unk3b4;  // +0x3b4  (C2.2 strict3)
    uint8_t m_pad3b5[3];
    float m_unk3b8;  // +0x3b8  (C2.2 strict3)
    float m_unk3bc;  // +0x3bc  (C2.2 strict3)
    float m_unk3c0;  // +0x3c0  (C2.2 strict3)
    float m_unk3c4;  // +0x3c4  (C2.2 strict3)
    float m_unk3c8;  // +0x3c8  (C2.2 strict3)
    float m_unk3cc;  // +0x3cc  (C2.2 strict3)
    float m_unk3d0;  // +0x3d0  (C2.2 strict3)
    float m_unk3d4;  // +0x3d4  (C2.2 strict3)
    float m_unk3d8;  // +0x3d8  (C2.2 strict3)
    float m_unk3dc;  // +0x3dc  (C2.2 strict3; a float: the AI follow distance)
    CPFCharacter m_PFCharacter;                  // +0x3e0 XXL2 m_PFCharacter
    CKPathFindingCpnt m_PFCpnt;                  // +0x3f0 XXL2 m_PFCpnt (embedded component)
    float m_unk468;  // +0x468  (C2.2 strict3)
    float m_unk46c;  // +0x46c  (C2.2 strict3)
    float m_unk470;  // +0x470  (C2.2 strict3)
    float m_unk474;  // +0x474  (C2.2 strict3)
    float m_unk478;  // +0x478  (C2.2 strict3)
    float m_unk47c;  // +0x47c  (C2.2 strict3)
    float m_unk480;  // +0x480 the move-to timeout (SetMoveDestination; ResetRuntimeState: stw 0)
    float m_unk484;  // +0x484  (C2.2 strict3)
    float m_unk488;  // +0x488  (C2.2 strict3)
    float m_unk48c;  // +0x48c  (C2.2 strict3)
    float m_unk490;  // +0x490  (C2.2 strict3)
    float m_unk494;  // +0x494  (C2.2 strict3)
    float m_unk498;  // +0x498  (C2.2 strict3)
    float m_unk49c;  // +0x49c  (C2.2 strict3)
    float m_unk4a0;  // +0x4a0  (C2.2 strict3)
    float m_unk4a4;  // +0x4a4  (C2.2 strict3)
    CGroundContactDatasIn m_gcDatasIn;           // +0x4a8 XXL2 m_gcDatasIn
    CGroundContactDatasInOut m_gcCurDatasInOut;  // +0x4b8 XXL2 m_gcCurDatasInOut
    CGroundContactDatasInOut m_gcOldDatasInOut;  // +0x4e4 XXL2 m_gcOldDatasInOut
    float m_unk510;  // +0x510  (C2.2 strict3)
    float m_unk514;                              // +0x514 (locomotion)
    float m_unk518;                              // +0x518 (locomotion)
    float m_unk51c;                              // +0x51c (locomotion)
    SHeroStateRow* m_unk520;  // +0x520  (C2.2 strict3)
    SHeroStateHandler* m_unk524;  // +0x524  (C2.2 strict3)
    SHeroStateHandler* m_unk528;  // +0x528  (C2.2 strict3)
    uint8_t m_unk52c;                            // +0x52c constructor 0xff
    uint8_t m_unk52d;                            // +0x52d constructor 0xff
    uint8_t m_pad52e[2];
    float m_unk530;  // +0x530  (C2.2 strict3; a float: the horizontal speed)
    float m_unk534;  // +0x534  (C2.2 strict3; a float: the vertical speed)
    float m_unk538;  // +0x538  (C2.2 spyro)
    float m_unk53c;  // +0x53c  (C2.2 strict3)
    float m_unk540;  // +0x540  (C2.2 spyro)
    float m_unk544;  // +0x544  (C2.2 spyro)
    float m_unk548;  // +0x548  (C2.2 spyro)
    float m_unk54c;  // +0x54c  (C2.2 spyro)
    float m_unk550;  // +0x550  (C2.2 spyro)
    float m_unk554;  // +0x554  (C2.2 spyro)
    float m_unk558;  // +0x558  (C2.2 spyro)
    float m_unk55c;  // +0x55c  (C2.2 spyro)
    float m_unk560;  // +0x560  (C2.2 spyro)
    float m_unk564;  // +0x564  (C2.2 strict3)
    float m_unk568;  // +0x568  (C2.2 strict3)
    float m_unk56c;  // +0x56c  (C2.2 strict3)
    float m_unk570;  // +0x570  (C2.2 strict3)
    float m_unk574;  // +0x574  (C2.2 strict3)
    float m_unk578;  // +0x578  (C2.2 strict3)
    float m_unk57c;  // +0x57c  (C2.2 strict3)
    float m_unk580;  // +0x580  (C2.2 strict3)
    float m_unk584;  // +0x584  (C2.2 strict3)
    uint8_t m_unk588;  // +0x588  (C2.2 strict3)
    uint8_t m_unk589;  // +0x589  (C2.2 strict3)
    uint8_t m_pad58a[2];
    uint32_t m_unk58c;  // +0x58c  (C2.2 strict3)
    uint8_t m_unk590;  // +0x590  (C2.2 strict3)
    uint8_t m_unk591;  // +0x591  (C2.2 strict3)
    uint8_t m_pad592[2];
    uint32_t m_unk594;  // +0x594  (C2.2 strict3)
    uint32_t m_unk598;  // +0x598  (C2.2 strict3)
    IKSerializable* m_unk59c;  // +0x59c the moving ground the hero was carried by (UpdateDynamicGroundAttachment)
    float m_unk5a0;  // +0x5a0 that ground's yaw last frame
    float m_unk5a4;  // +0x5a4 the yaw it turned this frame
    float m_unk5a8;  // +0x5a8  (C2.2 strict3)
    float m_unk5ac;  // +0x5ac  (C2.2 strict3)
    float m_unk5b0;  // +0x5b0  (C2.2 strict3)
    float m_unk5b4;  // +0x5b4  (C2.2 strict3)
    float m_unk5b8;  // +0x5b8  (C2.2 strict3)
    float m_unk5bc;  // +0x5bc  (C2.2 strict3)
    float m_unk5c0;  // +0x5c0  (C2.2 strict3)
    float m_unk5c4;  // +0x5c4  (C2.2 strict3)
    float m_unk5c8;  // +0x5c8  (C2.2 strict3)
    float m_unk5cc;  // +0x5cc  (C2.2 strict3)
    float m_unk5d0;  // +0x5d0  (C2.2 strict3)
    float m_unk5d4;  // +0x5d4  (C2.2 strict3)
    float m_unk5d8;  // +0x5d8  (C2.2 strict3)
    float m_unk5dc;  // +0x5dc  (C2.2 strict3)
    float m_unk5e0;  // +0x5e0  (C2.2 strict3)
    float m_unk5e4;  // +0x5e4  (C2.2 strict3)
    float m_unk5e8;  // +0x5e8  (C2.2 strict3)
    float m_unk5ec;  // +0x5ec  (C2.2 strict3)
    float m_unk5f0;  // +0x5f0  (C2.2 strict3)
    float m_unk5f4;  // +0x5f4  (C2.2 strict3)
    float m_unk5f8;  // +0x5f8  (C2.2 strict3)
    float m_unk5fc;  // +0x5fc  (C2.2 strict3)
    float m_unk600;  // +0x600  (C2.2 strict3)
    float m_unk604;  // +0x604  (C2.2 strict3)
    float m_unk608;  // +0x608  (C2.2 strict3)
    uint32_t m_unk60c;  // +0x60c  (C2.2 strict3; the last wall sweep's result: 0 free, 1 blocked, 2 slid, 3 pushed out)
    // +0x610 / +0x638 the wall sweep's result and its copy (CKSrvCollision_ResolveSweptCylinderWalls_maybe 0x19aa68,
    // from CKHkS08Hero_ResolveWallMovement_maybe 0x35b278): the bouncing vector, the wall's normal (+0x61c), heights.
    CSlideGroundEdgeDatasOut m_wallSlide;        // +0x610
    CSlideGroundEdgeDatasOut m_wallSlidePrev;    // +0x638
    float m_unk660;  // +0x660  (C2.2 strict3)
    float m_unk664;  // +0x664  (C2.2 strict3)
    float m_unk668;  // +0x668  (C2.2 strict3)
    float m_unk66c;  // +0x66c  (C2.2 strict3)
    float m_unk670;  // +0x670  (C2.2 strict3)
    float m_unk674;  // +0x674  (C2.2 strict3)
    float m_unk678;  // +0x678 the push duration (InitMoveRequestFromSourcePoint: factor x +0x318)
    float m_unk67c;  // +0x67c the word +0x33c as a float (InitMoveRequestFromSourcePoint)
    uint8_t m_unk680;  // +0x680  (C2.2 strict3)
    uint8_t m_pad681[3];
    float m_unk684;  // +0x684  (C2.2 strict3)
    float m_unk688;  // +0x688  (C2.2 strict3)
    float m_unk68c;  // +0x68c  (C2.2 strict3)
    float m_unk690;  // +0x690  (C2.2 strict3)
    float m_unk694;  // +0x694  (C2.2 strict3)
    float m_unk698;  // +0x698  (C2.2 strict3)
    float m_unk69c;  // +0x69c  (C2.2 strict3)
    float m_unk6a0;  // +0x6a0  (C2.2 strict3)
    float m_unk6a4;  // +0x6a4  (C2.2 strict3)
    float m_unk6a8;  // +0x6a8  (C2.2 strict3)
    float m_unk6ac;  // +0x6ac  (C2.2 strict3)
    float m_unk6b0;  // +0x6b0  (C2.2 strict3)
    float m_unk6b4;  // +0x6b4  (C2.2 strict3)
    float m_unk6b8;  // +0x6b8  (C2.2 strict3)
    float m_unk6bc;  // +0x6bc  (C2.2 strict3)
    uint32_t m_unk6c0;  // +0x6c0  (C2.2 strict3)
    uint32_t m_unk6c4;  // +0x6c4  (C2.2 strict3)
    uint32_t m_unk6c8;  // +0x6c8  (C2.2 strict3)
    uint32_t m_unk6cc;  // +0x6cc  (C2.2 strict3)
    uint8_t m_unk6d0;  // +0x6d0  (C2.2 strict3)
    uint8_t m_unk6d1;  // +0x6d1  (C2.2 strict3)
    uint8_t m_pad6d2[2];
    float m_unk6d4;  // +0x6d4  (C2.2 strict3)
    float m_unk6d8;  // +0x6d8  (C2.2 strict3)
    float m_unk6dc;  // +0x6dc  (C2.2 strict3)
    float m_unk6e0;  // +0x6e0  (C2.2 strict3)
    float m_unk6e4;  // +0x6e4  (C2.2 strict3)
    float m_unk6e8;  // +0x6e8  (C2.2 strict3)
    float m_unk6ec;  // +0x6ec  (C2.2 strict3)
    float m_unk6f0;  // +0x6f0  (C2.2 strict3)
    float m_unk6f4;  // +0x6f4  (C2.2 strict3)
    float m_unk6f8;  // +0x6f8  (C2.2 strict3)
    float m_unk6fc;  // +0x6fc  (C2.2 strict3)
    float m_unk700;  // +0x700  (C2.2 strict3)
    float m_unk704;  // +0x704  (C2.2 strict3)
    float m_unk708;  // +0x708  (C2.2 strict3)
    float m_unk70c;  // +0x70c  (C2.2 strict3)
    float m_unk710;  // +0x710  (C2.2 strict3)
    float m_unk714;  // +0x714  (C2.2 strict3)
    float m_unk718;  // +0x718  (C2.2 strict3)
    float m_unk71c;  // +0x71c  (C2.2 strict3)
    float m_unk720;  // +0x720  (C2.2 strict3)
    float m_unk724;  // +0x724  (C2.2 strict3)
    float m_unk728;  // +0x728  (C2.2 strict3)
    float m_unk72c;  // +0x72c  (C2.2 strict3)
    float m_unk730;  // +0x730  (C2.2 strict3)
    float m_unk734;  // +0x734  (C2.2 strict3)
    float m_unk738;  // +0x738  (C2.2 strict3)
    float m_unk73c;  // +0x73c  (C2.2 strict3)
    float m_unk740;  // +0x740  (C2.2 strict3)
    float m_unk744;  // +0x744  (C2.2 strict3)
    float m_unk748;  // +0x748  (C2.2 strict3)
    float m_unk74c;  // +0x74c  (C2.2 strict3)
    float m_unk750;  // +0x750  (C2.2 strict3)
    float m_unk754;  // +0x754  (C2.2 strict3)
    float m_unk758;  // +0x758  (C2.2 strict3)
    float m_unk75c;  // +0x75c  (C2.2 strict3)
    float m_unk760;  // +0x760  (C2.2 strict3)
    float m_unk764;  // +0x764  (C2.2 strict3)
    float m_unk768;  // +0x768  (C2.2 strict3)
    float m_unk76c;  // +0x76c  (C2.2 strict3)
    float m_unk770;  // +0x770  (C2.2 strict3)
    float m_unk774;  // +0x774  (C2.2 strict3)
    float m_unk778;  // +0x778  (C2.2 strict3)
    float m_unk77c;  // +0x77c  (C2.2 strict3)
    float m_unk780;  // +0x780  (C2.2 strict3)
    float m_unk784;  // +0x784  (C2.2 strict3)
    uint8_t m_unk788;  // +0x788  (C2.2 strict3)
    uint8_t m_pad789[3];
    uint32_t m_unk78c;  // +0x78c  (C2.2 strict3)
    float m_unk790;  // +0x790  (C2.2 strict3)
    float m_unk794;  // +0x794  (C2.2 strict3)
    float m_unk798;  // +0x798  (C2.2 strict3)
    float m_unk79c;  // +0x79c  (C2.2 strict3)
    float m_unk7a0;  // +0x7a0  (C2.2 strict3)
    float m_unk7a4;  // +0x7a4 the signed slope angle under the move, degrees (UpdateSignedSlopePitchClass 0x359c60)
    uint32_t m_unk7a8;  // +0x7a8  (C2.2 strict3)
    uint32_t m_unk7ac;  // +0x7ac  (C2.2 strict3)
    uint32_t m_unk7b0;  // +0x7b0  (C2.2 strict3)
    uint32_t m_unk7b4;  // +0x7b4  (C2.2 strict3)
    uint32_t m_unk7b8;  // +0x7b8  (C2.2 strict3)
    uint32_t m_unk7bc;  // +0x7bc  (C2.2 strict3)
    float m_unk7c0;  // +0x7c0  (C2.2 strict3)
    float m_unk7c4;  // +0x7c4  (C2.2 strict3)
    float m_unk7c8;  // +0x7c8  (C2.2 strict3)
    float m_unk7cc;  // +0x7cc  (C2.2 strict3)
    float m_unk7d0;  // +0x7d0  (C2.2 strict3)
    float m_unk7d4;  // +0x7d4  (C2.2 strict3)
    float m_unk7d8;  // +0x7d8  (C2.2 strict3)
    uint32_t m_unk7dc;  // +0x7dc  (C2.2 strict3)
    CGroundContactDatasIn m_gcDatasIn2_maybe;    // +0x7e0 a second ground-contact set
    CGroundContactDatasInOut m_gcCurDatasInOut2_maybe; // +0x7f0
    CGroundContactDatasInOut m_gcOldDatasInOut2_maybe; // +0x81c
};
DOTD_ASSERT_SIZE(IKHkHero, 0x848);
DOTD_ASSERT_OFFSET(IKHkHero, m_pGrpHero, 0x20);
DOTD_ASSERT_OFFSET(IKHkHero, m_ui8Hero, 0x24);
DOTD_ASSERT_OFFSET(IKHkHero, m_ui8TrackedLeader, 0x25);
DOTD_ASSERT_OFFSET(IKHkHero, m_ui8Leader, 0x26);
DOTD_ASSERT_OFFSET(IKHkHero, m_aInitialStates, 0x28);
DOTD_ASSERT_OFFSET(IKHkHero, m_apHotSpots, 0x4c);
DOTD_ASSERT_OFFSET(IKHkHero, m_apParticles, 0x50);
DOTD_ASSERT_OFFSET(IKHkHero, m_apBoundings, 0x54);
DOTD_ASSERT_OFFSET(IKHkHero, m_apObjects, 0x58);
DOTD_ASSERT_OFFSET(IKHkHero, m_apTrails, 0x5c);
DOTD_ASSERT_OFFSET(IKHkHero, m_pShadowCpnt, 0x60);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk80, 0x80);
DOTD_ASSERT_OFFSET(IKHkHero, m_pWaterWaveFxData, 0x84);
DOTD_ASSERT_OFFSET(IKHkHero, m_pWaterSplashFxData, 0x8c);
DOTD_ASSERT_OFFSET(IKHkHero, m_unkAC, 0xac);
DOTD_ASSERT_OFFSET(IKHkHero, m_unkAD, 0xad);
DOTD_ASSERT_OFFSET(IKHkHero, m_unkCC, 0xcc);
DOTD_ASSERT_OFFSET(IKHkHero, m_unkCD, 0xcd);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk10c, 0x10c);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk110, 0x110);
DOTD_ASSERT_OFFSET(IKHkHero, m_apUnk134, 0x134);
DOTD_ASSERT_OFFSET(IKHkHero, m_pAnimDico, 0x13c);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk14c, 0x14c);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk14d, 0x14d);
DOTD_ASSERT_OFFSET(IKHkHero, m_pSoundDico, 0x168);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk174, 0x174);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk1a0, 0x1a0);
DOTD_ASSERT_OFFSET(IKHkHero, m_aui8Unk1a4, 0x1a4);
DOTD_ASSERT_OFFSET(IKHkHero, m_asSpeedModes, 0x1bc);
DOTD_ASSERT_OFFSET(IKHkHero, m_asJumps, 0x1c0);
DOTD_ASSERT_OFFSET(IKHkHero, m_afBoundingsRadius, 0x1c4);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk1c8, 0x1c8);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk1cc, 0x1cc);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk1d0, 0x1d0);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk1d4, 0x1d4);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk1d8, 0x1d8);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk1dc, 0x1dc);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk1e0, 0x1e0);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk1e4, 0x1e4);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk1e8, 0x1e8);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk1ec, 0x1ec);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk1f0, 0x1f0);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk1f4, 0x1f4);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk1f8, 0x1f8);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk1fc, 0x1fc);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk200, 0x200);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk204, 0x204);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk208, 0x208);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk20c, 0x20c);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk210, 0x210);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk214, 0x214);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk218, 0x218);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk21c, 0x21c);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk220, 0x220);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk224, 0x224);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk228, 0x228);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk22c, 0x22c);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk230, 0x230);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk234, 0x234);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk238, 0x238);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk23c, 0x23c);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk240, 0x240);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk244, 0x244);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk248, 0x248);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk24c, 0x24c);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk250, 0x250);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk254, 0x254);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk258, 0x258);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk25c, 0x25c);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk260, 0x260);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk264, 0x264);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk268, 0x268);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk26c, 0x26c);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk270, 0x270);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk274, 0x274);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk278, 0x278);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk27c, 0x27c);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk280, 0x280);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk284, 0x284);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk288, 0x288);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk28c, 0x28c);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk290, 0x290);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk294, 0x294);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk298, 0x298);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk29c, 0x29c);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk2a0, 0x2a0);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk2a4, 0x2a4);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk2a8, 0x2a8);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk2ac, 0x2ac);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk2b0, 0x2b0);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk2b4, 0x2b4);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk2b8, 0x2b8);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk2bc, 0x2bc);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk2c0, 0x2c0);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk2c4, 0x2c4);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk2c8, 0x2c8);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk2cc, 0x2cc);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk2d0, 0x2d0);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk2d4, 0x2d4);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk2d8, 0x2d8);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk2dc, 0x2dc);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk2e0, 0x2e0);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk2e4, 0x2e4);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk2e8, 0x2e8);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk2ec, 0x2ec);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk2f0, 0x2f0);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk2f4, 0x2f4);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk2f8, 0x2f8);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk2fc, 0x2fc);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk300, 0x300);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk304, 0x304);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk308, 0x308);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk30c, 0x30c);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk310, 0x310);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk314, 0x314);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk318, 0x318);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk31c, 0x31c);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk320, 0x320);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk324, 0x324);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk328, 0x328);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk32c, 0x32c);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk330, 0x330);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk334, 0x334);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk336, 0x336);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk338, 0x338);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk33a, 0x33a);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk33c, 0x33c);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk33e, 0x33e);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk340, 0x340);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk342, 0x342);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk343, 0x343);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk344, 0x344);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk345, 0x345);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk346, 0x346);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk347, 0x347);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk348, 0x348);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk349, 0x349);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk34a, 0x34a);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk34b, 0x34b);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk34c, 0x34c);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk34d, 0x34d);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk34e, 0x34e);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk34f, 0x34f);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk350, 0x350);
DOTD_ASSERT_OFFSET(IKHkHero, m_PFCharacter, 0x3e0);
DOTD_ASSERT_OFFSET(IKHkHero, m_PFCpnt, 0x3f0);
DOTD_ASSERT_OFFSET(IKHkHero, m_gcDatasIn, 0x4a8);
DOTD_ASSERT_OFFSET(IKHkHero, m_gcCurDatasInOut, 0x4b8);
DOTD_ASSERT_OFFSET(IKHkHero, m_gcOldDatasInOut, 0x4e4);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk52c, 0x52c);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk52d, 0x52d);
DOTD_ASSERT_OFFSET(IKHkHero, m_gcDatasIn2_maybe, 0x7e0);
DOTD_ASSERT_OFFSET(IKHkHero, m_gcCurDatasInOut2_maybe, 0x7f0);
DOTD_ASSERT_OFFSET(IKHkHero, m_gcOldDatasInOut2_maybe, 0x81c);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk164, 0x164);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk540, 0x540);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk544, 0x544);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk548, 0x548);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk54c, 0x54c);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk550, 0x550);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk554, 0x554);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk558, 0x558);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk55c, 0x55c);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk560, 0x560);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk538, 0x538);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk37c, 0x37c);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk384, 0x384);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk380, 0x380);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk64, 0x64);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk68, 0x68);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk6c, 0x6c);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk368, 0x368);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk358, 0x358);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk70, 0x70);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk74, 0x74);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk78, 0x78);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk7c, 0x7c);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk81, 0x81);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk88, 0x88);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk90, 0x90);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk94, 0x94);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk98, 0x98);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk9c, 0x9c);
DOTD_ASSERT_OFFSET(IKHkHero, m_unka0, 0xa0);
DOTD_ASSERT_OFFSET(IKHkHero, m_unka4, 0xa4);
DOTD_ASSERT_OFFSET(IKHkHero, m_unka8, 0xa8);
DOTD_ASSERT_OFFSET(IKHkHero, m_unkb0, 0xb0);
DOTD_ASSERT_OFFSET(IKHkHero, m_unkb4, 0xb4);
DOTD_ASSERT_OFFSET(IKHkHero, m_unkb8, 0xb8);
DOTD_ASSERT_OFFSET(IKHkHero, m_unkbc, 0xbc);
DOTD_ASSERT_OFFSET(IKHkHero, m_unkc0, 0xc0);
DOTD_ASSERT_OFFSET(IKHkHero, m_unkc4, 0xc4);
DOTD_ASSERT_OFFSET(IKHkHero, m_unkc8, 0xc8);
DOTD_ASSERT_OFFSET(IKHkHero, m_unkd0, 0xd0);
DOTD_ASSERT_OFFSET(IKHkHero, m_unkd4, 0xd4);
DOTD_ASSERT_OFFSET(IKHkHero, m_unkd8, 0xd8);
DOTD_ASSERT_OFFSET(IKHkHero, m_unkdc, 0xdc);
DOTD_ASSERT_OFFSET(IKHkHero, m_unke0, 0xe0);
DOTD_ASSERT_OFFSET(IKHkHero, m_unke4, 0xe4);
DOTD_ASSERT_OFFSET(IKHkHero, m_unke8, 0xe8);
DOTD_ASSERT_OFFSET(IKHkHero, m_unkec, 0xec);
DOTD_ASSERT_OFFSET(IKHkHero, m_unkf0, 0xf0);
DOTD_ASSERT_OFFSET(IKHkHero, m_unkf4, 0xf4);
DOTD_ASSERT_OFFSET(IKHkHero, m_unkf8, 0xf8);
DOTD_ASSERT_OFFSET(IKHkHero, m_unkfc, 0xfc);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk100, 0x100);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk104, 0x104);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk108, 0x108);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk114, 0x114);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk118, 0x118);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk11c, 0x11c);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk120, 0x120);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk124, 0x124);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk128, 0x128);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk12c, 0x12c);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk130, 0x130);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk138, 0x138);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk140, 0x140);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk144, 0x144);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk148, 0x148);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk150, 0x150);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk154, 0x154);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk158, 0x158);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk15c, 0x15c);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk160, 0x160);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk16c, 0x16c);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk16d, 0x16d);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk16e, 0x16e);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk16f, 0x16f);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk170, 0x170);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk171, 0x171);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk172, 0x172);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk354, 0x354);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk35c, 0x35c);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk360, 0x360);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk364, 0x364);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk36c, 0x36c);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk370, 0x370);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk374, 0x374);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk378, 0x378);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk388, 0x388);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk38c, 0x38c);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk390, 0x390);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk392, 0x392);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk394, 0x394);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk395, 0x395);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk398, 0x398);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk39c, 0x39c);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk3a0, 0x3a0);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk3a4, 0x3a4);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk3a8, 0x3a8);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk3ac, 0x3ac);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk3b0, 0x3b0);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk3b4, 0x3b4);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk3b8, 0x3b8);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk3bc, 0x3bc);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk3c0, 0x3c0);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk3c4, 0x3c4);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk3c8, 0x3c8);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk3cc, 0x3cc);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk3d0, 0x3d0);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk3d4, 0x3d4);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk3d8, 0x3d8);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk3dc, 0x3dc);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk468, 0x468);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk46c, 0x46c);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk470, 0x470);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk474, 0x474);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk478, 0x478);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk47c, 0x47c);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk480, 0x480);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk484, 0x484);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk488, 0x488);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk48c, 0x48c);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk490, 0x490);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk494, 0x494);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk498, 0x498);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk49c, 0x49c);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk4a0, 0x4a0);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk4a4, 0x4a4);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk510, 0x510);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk520, 0x520);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk524, 0x524);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk528, 0x528);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk530, 0x530);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk534, 0x534);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk53c, 0x53c);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk564, 0x564);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk568, 0x568);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk56c, 0x56c);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk570, 0x570);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk574, 0x574);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk578, 0x578);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk57c, 0x57c);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk580, 0x580);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk584, 0x584);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk588, 0x588);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk589, 0x589);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk58c, 0x58c);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk590, 0x590);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk591, 0x591);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk594, 0x594);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk598, 0x598);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk59c, 0x59c);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk5a0, 0x5a0);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk5a4, 0x5a4);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk5a8, 0x5a8);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk5ac, 0x5ac);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk5b0, 0x5b0);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk5b4, 0x5b4);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk5b8, 0x5b8);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk5bc, 0x5bc);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk5c0, 0x5c0);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk5c4, 0x5c4);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk5c8, 0x5c8);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk5cc, 0x5cc);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk5d0, 0x5d0);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk5d4, 0x5d4);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk5d8, 0x5d8);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk5dc, 0x5dc);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk5e0, 0x5e0);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk5e4, 0x5e4);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk5e8, 0x5e8);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk5ec, 0x5ec);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk5f0, 0x5f0);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk5f4, 0x5f4);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk5f8, 0x5f8);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk5fc, 0x5fc);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk600, 0x600);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk604, 0x604);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk608, 0x608);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk60c, 0x60c);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk660, 0x660);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk664, 0x664);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk668, 0x668);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk66c, 0x66c);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk670, 0x670);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk674, 0x674);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk678, 0x678);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk67c, 0x67c);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk680, 0x680);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk684, 0x684);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk688, 0x688);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk68c, 0x68c);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk690, 0x690);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk694, 0x694);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk698, 0x698);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk69c, 0x69c);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk6a0, 0x6a0);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk6a4, 0x6a4);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk6a8, 0x6a8);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk6ac, 0x6ac);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk6b0, 0x6b0);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk6b4, 0x6b4);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk6b8, 0x6b8);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk6bc, 0x6bc);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk6c0, 0x6c0);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk6c4, 0x6c4);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk6c8, 0x6c8);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk6cc, 0x6cc);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk6d0, 0x6d0);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk6d1, 0x6d1);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk6d4, 0x6d4);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk6d8, 0x6d8);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk6dc, 0x6dc);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk6e0, 0x6e0);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk6e4, 0x6e4);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk6e8, 0x6e8);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk6ec, 0x6ec);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk6f0, 0x6f0);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk6f4, 0x6f4);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk6f8, 0x6f8);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk6fc, 0x6fc);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk700, 0x700);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk704, 0x704);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk708, 0x708);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk70c, 0x70c);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk710, 0x710);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk714, 0x714);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk718, 0x718);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk71c, 0x71c);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk720, 0x720);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk724, 0x724);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk728, 0x728);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk72c, 0x72c);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk730, 0x730);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk734, 0x734);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk738, 0x738);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk73c, 0x73c);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk740, 0x740);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk744, 0x744);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk748, 0x748);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk74c, 0x74c);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk750, 0x750);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk754, 0x754);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk758, 0x758);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk75c, 0x75c);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk760, 0x760);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk764, 0x764);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk768, 0x768);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk76c, 0x76c);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk770, 0x770);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk774, 0x774);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk778, 0x778);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk77c, 0x77c);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk780, 0x780);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk784, 0x784);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk788, 0x788);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk78c, 0x78c);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk790, 0x790);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk794, 0x794);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk798, 0x798);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk79c, 0x79c);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk7a0, 0x7a0);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk7a4, 0x7a4);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk7a8, 0x7a8);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk7ac, 0x7ac);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk7b0, 0x7b0);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk7b4, 0x7b4);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk7b8, 0x7b8);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk7bc, 0x7bc);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk7c0, 0x7c0);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk7c4, 0x7c4);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk7c8, 0x7c8);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk7cc, 0x7cc);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk7d0, 0x7d0);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk7d4, 0x7d4);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk7d8, 0x7d8);
DOTD_ASSERT_OFFSET(IKHkHero, m_unk7dc, 0x7dc);
