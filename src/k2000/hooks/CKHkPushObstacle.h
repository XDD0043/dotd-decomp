// CKHkPushObstacle.h - a block the heroes grab and push cell by cell on the path-finding grid (key 0x842, vtable 0xb263e8,
// size 0x1e8). Original unit: CKHkPushObstacle.cpp (0x42ffb0-0x43ef98). No XXL2 class of this key; names ours. No game
// file holds one (work/level-class-keys.json). C2.8 port-final F02 wrote the class from the Load, the constructor and
// the users in the unit: the Load, the slots, the animation / effect / sound helpers, the grid blocking, the pushers'
// release and OnDeactivate; C2.8 port-last Z2 the hero grab / push logic, the moves, the five states and MessageProc /
// Update / OnActivate / Restart (nothing replays the class).
//
// The obstacle faces one of the four axes (its node's at axis); it covers a footprint of +0xd8 x +0xd9 cells (+0xda /
// +0xdb the half extents in grid units, +0xdc / +0xdd the centre's offset), blocks those cells while it rests and moves
// one cell per push from one of its four sides (+0x185, the grab points of the side's array +0xc4 + side x 4, one per
// dragon). The heroes pushing it are a list of nodes (+0x178).
#pragma once
#include <cstddef>
#include <cstdint>

#include "k2000/ai/CKSrvPathFinding.h"
#include "k2000/core/Layout.h"
#include "k2000/hooks/GroundContact.h"
#include "k2000/math/CMatrix34.h"
#include "k2000/misc/CKHkActorBase.h"
#include "k2000/services/CTriggerStarter.h"

class CKHkS08Hero;

class CKHkPushObstacle : public CKHkActorBase {
public:
    DOTD_CLASS_KEY(kCategoryHook, 0x21)
    int32_t IsKindOfClass(uint32_t key) override {  // vt+0x08 0x9c3328
        return key == 0x842 || key == 0xd82 || key == 0x2 || key == 0x2fe || key == 0x3fe || key == 0xc;
    }
    DOTD_DECLARE_FACTORIES(CKHkPushObstacle)

    // A hero at the obstacle (0x20 bytes on the PS3, from the FreeListPool 0x00ceaa90's free list 0x00ceaa94, which
    // links through +0x00; here new / delete). The grab code (not ported) fills it.
    struct Pusher {
        CKHkS08Hero* m_pHero;   // +0x00
        CPFPoint m_point;       // +0x04 the hero's grid cell (node +0x10; DetachPushingHeroes frees its cell)
        int8_t m_i8GrabPoint;   // +0x14 its grab point in the side's array (+0xc4[side][m_i8GrabPoint])
        uint8_t m_bReady;       // +0x15 at its grab point (the push animations and the readiness test take it)
        uint8_t m_bPushing;     // +0x16 its push animation runs (the hand effect points follow it)
        uint8_t m_bHandFx;      // +0x17 its hands feed the push effect (+0x90)
        uint8_t m_unk18;        // +0x18 set by the move animations
        uint8_t m_pad19[3];
        Pusher* m_pNext;        // +0x1c
    };
    // A state (the original's pointers to member functions: {vtable offset + 1, 0}, the virtual slots +0xf0..+0x100):
    // phase 1 on enter, 2 on leave, 0 every frame (the next state).
    typedef uint8_t (CKHkPushObstacle::*StateHandler)(IKTime* clock, int32_t phase, uint8_t other);
    enum { kStateCount = 5 };

    // 0x004336f8 CKHkPushObstacle_Create (the dead 0x4313a8 / 0x432778 _Construct copies): the actor base, no state
    // (+0x24 / +0x25 0xff), the nav node -1, the pushers none, the ground contact's defaults (masks 1, 8; ground 0, face
    // -1, status 3, sector 0). Out of line (LNK1163).
    CKHkPushObstacle();
    // 0x00431cf8 CKHkPushObstacle_Destructor (0x4326f0 _DeletingDestructor + delete): the pushers back to their pool,
    // the list cleared, then the actor base's.
    ~CKHkPushObstacle() override;

    int32_t Load(IKFile* file, int32_t type) override;             // vt+0x2c 0x00439060 CKHkPushObstacle_Load
    // vt+0x30 0x00431318 CKHkPushObstacle_PostLoad: the actor base's (IKLife's), then the state table; 1.
    int32_t PostLoad(int32_t type) override;
    // vt+0x38 0x004311e8 CKHkPushObstacle_SetDefaultState: the actor base's (empty), then the preset 0 (vt+0xc8).
    void SetDefaultState(int32_t flag) override;
    int32_t GetInfo(IKInfo* info, int32_t request) override;        // vt+0x40 0x00432810 CKHkPushObstacle_GetInfo
    // vt+0x50 0x004312b8 CKHkPushObstacle_Start: the actor base's (empty), Restart (vt+0x54), then +0x1e0 = 0.
    void Start() override;
    // vt+0xb4 0x00430c78 CKHkPushObstacle_AttachSounds (KGLObjectAttached): the four sounds attached to the node.
    void KGLObjectAttached(IKSerializable* node) override;
    // vt+0xc0 0x00431180 CKHkPushObstacle_FreeBuffers_maybe (the actor base's Destroy calls it): the five reference
    // arrays freed (the pointers kept).
    void VfC0() override;
    // vt+0xc8 0x00431ad8 CKHkPushObstacle_ApplyStatePreset_maybe: preset 0 takes the flags +0xd4, 1 the flags +0xd5 and
    // the start cell offsets +0xd6 / +0xd7; the side bits +0x1a1 and the start move +0x1a0 (0 locked, 0xff when the
    // flags' bit 1 has the node +0x70, else 1) follow.
    void ApplyStatePreset(int32_t state) override;
    // vt+0x1c 0x0043bf88 CKHkPushObstacle_MessageProc
    int32_t MessageProc(uint16_t message, void* data) override;
    // vt+0x54 0x0043d1a8 CKHkPushObstacle_Restart (Start calls it)
    void Restart() override;
    // vt+0x7c 0x004387b0 CKHkPushObstacle_Update
    void Update(IKTime* clock) override;
    // vt+0xa0 0x0043cbc8 CKHkPushObstacle_OnActivate
    void VfA0() override;
    // vt+0x10 0x4316a0 Destroy, vt+0x24 0x431380 RecursiveRegistration, vt+0x68 / +0x70 / +0x78 0x431290 / 0x431268 /
    // 0x431240 Stop / Pause / Resume: the actor base's (inherited).

    // 0x0043d7e8 CKHkPushObstacle_InitStateTable_maybe: the five states (+0x28..+0x4f), the table pointer +0x20, no
    // state (0xff), five of them.
    void InitStateTable();
    // The states (vt+0xf0..+0x100): phase 1 on enter, 2 on leave, 0 every frame (the next state).
    virtual uint8_t State0(IKTime* clock, int32_t phase, uint8_t other);  // 0x0043d848 _State0_PlayAnimWithImpact_maybe
    virtual uint8_t State1(IKTime* clock, int32_t phase, uint8_t other);  // 0x0043e3c0 _State1_Idle_maybe
    virtual uint8_t State2(IKTime* clock, int32_t phase, uint8_t other);  // 0x0043e760 _State2_Moving_maybe
    virtual uint8_t State3(IKTime* clock, int32_t phase, uint8_t other);  // 0x0043dfd0 _State3_WaitForPush_maybe
    virtual uint8_t State4(IKTime* clock, int32_t phase, uint8_t other);  // 0x0043db10 _State4_FinalAnimAndLock_maybe

    // 0x004304a8 CKHkPushObstacle_SnapToGroundAndBlockNav_maybe: the footprint's centre (from the facing) dropped on the
    // ground (the obstacle's three grounds switched off meanwhile), and its box less 0.1 blocked in the path-finding
    // grid when the centre is in a nav node.
    void SnapToGroundAndBlockNav();
    // 0x00430f20 CKHkPushObstacle_PlayPushAnimsOnMove_maybe: every pusher crossfades to its push animation (word 1)
    // unless it plays it, the move flags; the node plays its animation 0.
    void PlayPushAnimsOnMove();
    // 0x00431028 CKHkPushObstacle_AreAllPushersReady_maybe: with a side, as many pushers as the side has grab points,
    // all of them ready (none: 0).
    uint8_t AreAllPushersReady();
    // 0x004316c8 CKHkPushObstacle_PlayIdleAnims_maybe / 0x004317b0 _PlayFinalAnims_maybe / 0x004319d8
    // _PlayPushAnimsForReadyPushers_maybe: the node's animation 0 / 2 / 0 and the pushers' animations.
    void PlayIdleAnims();
    void PlayFinalAnims();
    void PlayPushAnimsForReadyPushers();
    // 0x004318c8 CKHkPushObstacle_SetAnimTimeAll_maybe / 0x00431950 _AdvanceAnimTime_maybe: the node's and the ready
    // pushers' animation time set / run on.
    void SetAnimTimeAll(float time);
    void AdvanceAnimTime(float nodeDt, float heroDt);
    // 0x00431d70 CKHkPushObstacle_UpdatePusherHandFxPoints_maybe: the pushing heroes' two hand hot spots (parts 2 / 3)
    // as the hand effect's (+0x90) emit points.
    void UpdatePusherHandFxPoints();
    // 0x00431f78 CKHkPushObstacle_PlayImpactFx_maybe: the impact explosion (+0x9c) at the footprint's centre on the
    // ground, raised by +0xfc; the quake (+0x158 bit 2), the impact sound (sound 2, unless bit 3), the pad vibration.
    void PlayImpactFx();
    // 0x00432bf0 CKHkPushObstacle_SetNavBoxBlocked_maybe: the footprint around the rest position +0x164 blocked / freed
    // in the nav node +0x170 (none: nothing).
    void SetNavBoxBlocked(uint8_t blocked);
    // 0x00432d30 CKHkPushObstacle_ResetPushState_maybe: both push effects off, the move sound stopped, no hand effects.
    void ResetPushState();
    // 0x00432e20 CKHkPushObstacle_StopMoveFeedbackFx_maybe / 0x00432f18 _StartMoveFeedback_maybe: the move effect
    // (+0x98) back under the node's parent and off / the move sound, then (unless +0x158 bit 5) the effect under the
    // node with three emit points along the pushed side, on.
    void StopMoveFeedbackFx();
    void StartMoveFeedback();
    // 0x0043a258 CKHkPushObstacle_DetachPushingHeroes_maybe: the dragon switch unlocked, the grab volume (+0xac) out of
    // the collision; every pusher's grid cell freed, and every pusher let go (a player's one fires starter 9, +0x148)
    // except, unless `all`, a player's dragon still pushing (input +0x38c not 0) outside state 4. None left: starter 8
    // (+0x140), no side (outside state 2), +0x184 0, +0x1e4 bit 2 cleared, state 3 goes to state 1.
    void DetachPushingHeroes(uint8_t all);
    // 0x00435b98 CKHkPushObstacle_ShowInputIcon_maybe: the input icon effect (data +0x15c) acquired and placed at the
    // node (only when none is shown), or released.
    void ShowInputIcon(int32_t show);
    // vt+0xa4 0x0043bc88 CKHkPushObstacle_OnDeactivate: the actor base's; the footprint freed, the pushers let go, the
    // node back at +0x188, the move effect off, the push state reset, +0x70 hidden, the node shown, both volumes (+0x80,
    // +0xac) out of the collision and of their parents, the input icon off.
    void VfA4() override;

    // C2.8 port-last Z2: the grab / push / move logic (the .cpp has each one's description).
    void CellPosition(int8_t cellA, int8_t cellB, CVector3* out);  // the shared body of the two below
    void ComputeRestPosition(CVector3* out);     // 0x004373d8 _ComputeRestPosition_maybe (cells +0x194 / +0x195)
    void ComputeFootprintCorner(CVector3* out);  // 0x00436630 _ComputeFootprintCorner_maybe (cells +0x196 / +0x197)
    void StepGridCoordAndFireSignals();          // 0x00435e70
    void UpdateMoveStep(float dt);               // 0x004371b0
    void BeginMove();                            // 0x00438550
    uint8_t ProbeMoveTarget();                   // 0x004381e0
    uint8_t CanPushInDirection();                // 0x00437950
    int8_t CountActivePushers(uint8_t keep);     // 0x0043a640
    int8_t ChoosePushState();                    // 0x0043acd0
    int8_t SelectNextState();                    // 0x0043aff8
    void UnblockGrabPointCells();                // 0x004358b8
    void SetPusherCellsBlocked(uint8_t blocked); // 0x00435a80 (inlined by Update)
    void SnapPushersToGrabPoints();              // 0x00434008
    void StopMoveFeedbackAndCollision();         // 0x004341b8
    void StartPushFxAndSound();                  // 0x004337a0
    void CheckGrabPointsForHero();               // 0x004342c0
    void AttachHeroesToGrabPoints();             // 0x00434728
    uint8_t IsHeroInGrabArea(CKHkS08Hero* hero); // 0x004351a8
    uint8_t IsHeroOnMoveTrajectory(CKHkS08Hero* hero);  // 0x00436ba8
    void UpdateHeroInteraction();                // 0x00436150
    void UpdateHeroPush(IKTime* clock);          // 0x0043b290
    void ApplyStartMove(uint8_t fromMessage);    // the start move (+0x1a0) block of MessageProc / OnActivate / Restart
    void ResetRuntime();                         // the run-time reset of OnActivate / Restart
    // +0x164 / +0x170 are a CPFPoint (the rest position and its nav node: Update's FindSectorForPoint).
    CPFPoint* RestPoint() { return reinterpret_cast<CPFPoint*>(&m_vRestPos); }

    // +0x20..+0x4f the state machine (the table, the current state, the count, the handlers; 8 bytes each on the PS3).
    StateHandler* m_pStateTable;       // +0x20
    uint8_t m_ui8State;                // +0x24
    uint8_t m_ui8NbStates;             // +0x25
    uint8_t m_pad26[2];
    StateHandler m_aStates[kStateCount];  // +0x28
    // The Load's references (level data).
    IKSerializable* m_pAnimDictionary;      // +0x50 a CAnimationDictionary: 0 rest / push, 2 the final animation
    IKSerializable* m_unk54;                // +0x54
    IKSerializable** m_apHeroAnimDictionaries;  // +0x58 one CAnimationDictionary per dragon (count +0xb0): 0, 1 push, 2
    IKSerializable* m_pSoundDictionary;     // +0x5c a CKSoundDictionaryID: 0..3 (1 the move loop, 2 the impact, 3 push)
    IKSerializable* m_apGrounds[3];         // +0x60 the obstacle's ICollisionMeshes (off while it probes the ground)
    IKSerializable* m_pNode;                // +0x6c a CSGBranch: the moving part (the move effect's parent)
    IKSerializable* m_unk70;                // +0x70 a node (the impact sound's when set); preset flags bit 1 tests it
    IKSerializable* m_unk74;                // +0x74
    IKSerializable* m_unk78;                // +0x78
    IKSerializable* m_unk7c;                // +0x7c
    IKSerializable* m_unk80;                // +0x80
    CVector3 m_unk84;                       // +0x84 three words
    IKSerializable* m_pHandFx;              // +0x90 a CParticlesNodeFx: the pushers' hands
    IKSerializable* m_pPushFx;              // +0x94 a CParticlesNodeFx
    IKSerializable* m_pMoveFx;              // +0x98 a CParticlesNodeFx: the move feedback along the pushed side
    IKSerializable* m_pImpactFxData;        // +0x9c an explosion's IKFxData
    IKSerializable* m_pQuake;               // +0xa0 a CKQuakeCameraLauncher
    IKSerializable* m_unka4;                // +0xa4
    IKSerializable* m_pVibration;           // +0xa8 a CKVibrationData
    IKSerializable* m_unkac;                // +0xac
    uint8_t m_ui8NbDragons;                 // +0xb0 the per-dragon arrays' count
    uint8_t m_padb1[3];
    float m_fVolumeHeight;                  // +0xb4 the grab volume +0xac's height (x 0.5) for two pushers
    float m_fImpactTime0;                   // +0xb8 state 0: the impact once the node's animation time reaches it
    float m_fEnemyConeCheck;                // +0xbc CanPushInDirection tests the enemies in front when above 0
    float m_fImpactTime4;                   // +0xc0 state 4: the impact when the node's animation crosses it
    IKSerializable** m_apGrabPoints[4];     // +0xc4 per side, one per dragon (count +0xb0)
    uint8_t m_aPresetFlags[2];              // +0xd4 preset 0 / 1: bit 0 locked, 1 needs +0x70, 2..5 the side bits
    int8_t m_aPresetCell[2];                // +0xd6 preset 1's start cell offsets
    uint8_t m_ui8CellsA;                    // +0xd8 the footprint in cells (along / across the facing)
    uint8_t m_ui8CellsB;                    // +0xd9
    uint8_t m_ui8HalfA;                     // +0xda the half extents in grid units
    uint8_t m_ui8HalfB;                     // +0xdb
    int8_t m_i8CentreA;                     // +0xdc the centre's offset in grid units
    int8_t m_i8CentreB;                     // +0xdd
    uint8_t m_unkde;                        // +0xde
    uint8_t m_paddf;
    uint32_t m_unke0;                       // +0xe0
    float m_fGrabRadius;                    // +0xe4 the reach of the grab points (UpdateHeroInteraction / Push)
    float m_fHeight;                        // +0xe8 the footprint centre's height (x 0.5)
    float m_fFxHeight;                      // +0xec the move effect points' height (x 0.5)
    float m_fGroundDeltaMax;                // +0xf0 the ground probe's delta (OnActivate / Restart: +0x1a4)
    float m_fMoveToTimeout;                 // +0xf4 the heroes' walk to their grab points (SetMoveDestination)
    float m_fPushAnimTime;                  // +0xf8 state 3: a pushing hero's animation time that ends the wait
    float m_fImpactRaise;                   // +0xfc the impact explosion's height above the ground
    CTriggerStarter m_aStarters[11];        // +0x100 (the file's order: +0x100..+0x120, +0x130, +0x128, +0x138..+0x150)
    uint8_t m_ui8Flags;                     // +0x158 bit 2 quake, 3 no impact sound, 4 no push / hand effects, 5 no
                                            //        move effect
    uint8_t m_pad159[3];
    IKSerializable* m_unk15c;               // +0x15c
    IKSerializable* m_unk160;               // +0x160
    // The run time.
    CVector3 m_vRestPos;                    // +0x164 the grid position the footprint is blocked around
    int16_t m_i16NavNode;                   // +0x170 the nav node of the blocked box (-1 none)
    uint8_t m_pad172[2];
    float m_fPlayerPushTime;                // +0x174 the clock's time a player last pushed (Update, +0x1e4 bit 4)
    Pusher* m_pPushers;                     // +0x178
    CKHkS08Hero* m_pCandidateHero;          // +0x17c the hero of the last grab message 0x93f
    CKHkS08Hero* m_pReleasedHero;           // +0x180 the hero CountActivePushers let go last (Update: null)
    uint8_t m_ui8Unk184;                    // +0x184 (GetInfo 0xa5: not 0)
    int8_t m_i8Side;                        // +0x185 the pushed side (0..3, -1 none)
    int8_t m_i8LastSide;                    // +0x186 the last pushed side (the moves read its grab points)
    int8_t m_i8PendingSide;                 // +0x187 the side a player's switch grabs next (UpdateHeroPush)
    CVector3 m_unk188;                      // +0x188 the footprint matrix's position
    int8_t m_i8CellA;                       // +0x194 the cell offsets (GetInfo 0xa2 / 0xa3)
    int8_t m_i8CellB;                       // +0x195
    int8_t m_i8StartCellA;                  // +0x196
    int8_t m_i8StartCellB;                  // +0x197
    float m_fMoveDist;                      // +0x198 the distance moved in the current cell step
    float m_fIdleTimer;                     // +0x19c state 1 counts it down while +0x1e4 bit 7 is set
    uint8_t m_ui8StartMove;                 // +0x1a0 (preset) 0 locked, 1, 0xff
    uint8_t m_ui8SideBits;                  // +0x1a1 bits 0..3 the sides it may be pushed from (preset)
    uint8_t m_pad1a2[2];
    CGroundContactDatasIn m_GrdContDatasIn;       // +0x1a4
    CGroundContactDatasInOut m_GrdContDatasInOut;  // +0x1b4
    IKSerializable* m_pInputIconFx;         // +0x1e0 the input icon effect (ShowInputIcon; Start: null)
    uint16_t m_ui16Flags1e4;                // +0x1e4 (a halfword: DetachPushingHeroes clears bit 2 when none is left)
    uint16_t m_pad1e6;
};
static_assert(CKHkPushObstacle::kClassKey == 0x842, "key");
DOTD_ASSERT_SIZE(CKHkPushObstacle, 0x1e8);
DOTD_ASSERT_OFFSET(CKHkPushObstacle, m_pAnimDictionary, 0x50);
DOTD_ASSERT_OFFSET(CKHkPushObstacle, m_pHandFx, 0x90);
DOTD_ASSERT_OFFSET(CKHkPushObstacle, m_ui8NbDragons, 0xb0);
DOTD_ASSERT_OFFSET(CKHkPushObstacle, m_apGrabPoints, 0xc4);
DOTD_ASSERT_OFFSET(CKHkPushObstacle, m_ui8CellsA, 0xd8);
DOTD_ASSERT_OFFSET(CKHkPushObstacle, m_fHeight, 0xe8);
DOTD_ASSERT_OFFSET(CKHkPushObstacle, m_aStarters, 0x100);
DOTD_ASSERT_OFFSET(CKHkPushObstacle, m_ui8Flags, 0x158);
DOTD_ASSERT_OFFSET(CKHkPushObstacle, m_vRestPos, 0x164);
DOTD_ASSERT_OFFSET(CKHkPushObstacle, m_pPushers, 0x178);
DOTD_ASSERT_OFFSET(CKHkPushObstacle, m_i8Side, 0x185);
DOTD_ASSERT_OFFSET(CKHkPushObstacle, m_unk188, 0x188);
DOTD_ASSERT_OFFSET(CKHkPushObstacle, m_ui8SideBits, 0x1a1);
DOTD_ASSERT_OFFSET(CKHkPushObstacle, m_GrdContDatasIn, 0x1a4);
DOTD_ASSERT_OFFSET(CKHkPushObstacle, m_GrdContDatasInOut, 0x1b4);
DOTD_ASSERT_OFFSET(CKHkPushObstacle, m_ui16Flags1e4, 0x1e4);
static_assert(offsetof(CKHkPushObstacle, m_i16NavNode) == offsetof(CKHkPushObstacle, m_vRestPos) + offsetof(CPFPoint, m_i16GraphNodeIndex),
              "RestPoint: +0x164 / +0x170 as a CPFPoint");
