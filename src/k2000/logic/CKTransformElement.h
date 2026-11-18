// CKTransformElement.h - the shared base of the element attacks (key 0x954c, vtable 0xb24888, size 0x154). Original
// unit: CKTransformElement.cpp (0x3dc3d8-0x3e0248). No XXL2 class of this name. Base (family id 23) of CKEarthBoulder,
// CKIceSpin, CKWindTwister, CKElectricSphere and CKShadowSurprise. The member names are the Ghidra struct's (curated
// from the attack code); the per-level arrays are indexed by the element's upgrade level (0..2). The family drives its
// user only through the ability host (CKS08AbilityHostBase). Phases: the start animation (+0x132, phase 0), the loop
// (+0x131, phase 1: the start cost +0x44, then the mana per second +0x38), the end animation (+0x133, phase 4); the
// button let go, or the mana run out, ends it.
#pragma once
#include "k2000/logic/CKAbilityElement.h"
#include <cstdint>

#include "k2000/core/IKSerializable.h"
#include "k2000/core/Layout.h"

class CKS08AbilityHostBase;

class CKTransformElement : public CKAbilityElement {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x255)
    int32_t IsKindOfClass(uint32_t key) override {  // vt+0x08 0x9c08f8
        return key == 0x954c || key == 0xc || key == 0x90cc;
    }
    DOTD_DECLARE_FACTORIES(CKTransformElement)

    CKTransformElement() {}  // 0x003dc428 CKTransformElement_Construct: stores the vtable only
    ~CKTransformElement() override {}
    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x003de4f8 CKTransformElement_Load
    // vt+0x30 0x003de488 CKTransformElement_PostLoad: the run-time state reset (vt+0x6c).
    int32_t PostLoad(int32_t type) override;

    // The ability protocol (CKAbilityElement.h).
    // vt+0x50 0x003dc448 CKTransformElement_GetAbilityId (the base returns 0x17; the elements override it).
    uint8_t GetAbilityId() override { return 0x17; }
    uint8_t GetFamilyId() override { return 0x17; }  // vt+0x54 0x003dc450 CKTransformElement_GetFamilyId
    // vt+0x58 0x003dc458 CKTransformElement_Start: when not running and with a host: the host kept, the phases cleared,
    // the start cost pending (+0x148), running; the level index (host vt+0xf4), the hero control on, the mana
    // accumulator and the ground FX timer cleared; the start animation (phase 0), else the loop (phase 1) with the
    // effects on (vt+0x70) when the host's mana is above the start cost; the start time (the game clock).
    void Start(CKS08AbilityHostBase* host) override;
    // vt+0x5c 0x003dc690 CKTransformElement_Stop: while running, the effects stopped (vt+0x84) and End(forced).
    void Stop(int32_t forced) override;
    // vt+0x60 0x003dd958 CKTransformElement_Update: the phases, the start cost and the mana per second, the loop
    // animation following the user's ground state, the ground FX, the attack (vt+0x7c) and the effects (vt+0x74).
    // Rand_Int: one draw per frame of the loop and of the end animation (the damage's knock angle), four more per
    // ground FX (the ice spin's).
    uint8_t Update(float dt) override;
    // vt+0x64 0x003dc720 CKTransformElement_End: the hero control off, not running, the level's cooldown (+0x2c
    // forced, else +0x20) set through the host (per slot unless forced), the host dropped.
    void End(int32_t forced) override;
    // vt+0x68 0x003dc800 CKTransformElement_ApplyHeroControl: the user's permissions, turn, 11f8 and move speed from
    // the data's air / flying / ground settings (on), or all of them off; +0x134 = in the air (host vt+0x30 inverted).
    void ApplyHeroControl(uint8_t on) override;

    // The Transform family's slots.
    // vt+0x6c 0x003dcea0 CKTransformElement_ResetRuntime: the run-time words of the base (the elements' overrides
    // call it first).
    virtual void ResetRuntime();
    virtual void SetFxActive(int32_t /*on*/) {}  // vt+0x70 0x009c08e0 (empty)
    virtual void UpdateEffect(float /*dt*/) {}   // vt+0x74 0x009c08e8 CKTransformElement_vf74 (empty)
    // vt+0x78 0x003dd068 CKTransformElement_StartEmitterFx: a pooled effect of the emitter data (+0x128) for this
    // element (CKSrvFx::AcquireFx), put at the hot spot +0x13c, triggered and released.
    virtual void StartEmitterFx();
    virtual void UpdateAttack(float /*dt*/) {}  // vt+0x7c 0x009c08f0 CKTransformElement_UpdateAttack_maybe (empty)
    // vt+0x80 0x003dcf40 CKTransformElement_SwitchLoopAnim_maybe: +0x134 = `onGround` inverted, the hero control
    // re-applied and the loop animation (phase 1) replayed.
    virtual void SwitchLoopAnim(uint8_t onGround);
    // vt+0x84 0x003dcee8 CKTransformElement_StopFx: the effects off (vt+0x70), the loop phase over.
    virtual void StopFx();
    // vt+0x88 0x003dd3d8 CKTransformElement_ApplyDamageParams: the damage object (+0x14c, a CKS08ElementDamage) set
    // up from the level's values, scaled by the host's damage / effect scales; one Rand_Int draw (the knock angle).
    virtual void ApplyDamageParams(uint8_t continuous);
    virtual uint8_t IsGroundTrailActive() { return 0; }  // vt+0x8c 0x009bfc98 KBaseC_vf8C

    int32_t m_levelIndex;              // +0x004 (not loaded) the level index (0..2, host vt+0xf4) at Start
    int32_t m_damage[3];               // +0x008 (file: 100, 150, ...)
    float m_damageParam10[3];          // +0x014
    float m_cooldown[3];               // +0x020
    float m_cooldownForced[3];         // +0x02c
    int32_t m_manaPerSecond[3];        // +0x038
    int32_t m_manaRequired[3];         // +0x044
    float m_dmgRandBase;               // +0x050 _maybe
    float m_dmgRandRange;              // +0x054 _maybe
    float m_dmgParam2C[3];             // +0x058
    float m_dmgParam28[3];             // +0x064
    float m_dmgEffect0[3];             // +0x070
    float m_dmgEffect1[3];             // +0x07c
    float m_dmgEffect2[3];             // +0x088
    float m_dmgEffect4[3];             // +0x094
    float m_dmgEffect6[3];             // +0x0a0
    float m_dmgEffect5[3];             // +0x0ac
    float m_dmgEffect7[3];             // +0x0b8
    float m_dmgEffect3[3];             // +0x0c4
    uint8_t m_dmgFlag34[3];            // +0x0d0
    uint8_t m_dmgFlag35[3];            // +0x0d3
    uint8_t m_padD6[2];                // +0x0d6
    float m_groundFxIntervalBase;      // +0x0d8 _maybe
    float m_groundFxIntervalRange;     // +0x0dc _maybe
    float m_unkE0;                     // +0x0e0 (file: 0.5) the ground FX scatter radius (Update)
    uint8_t m_airPerm1Perm0TurnEnable[3];    // +0x0e4
    uint8_t m_padE7;                         // +0x0e7
    float m_airTurnAB[2];                    // +0x0e8
    uint8_t m_mode1Perm1Perm0TurnEnable[3];  // +0x0f0
    uint8_t m_padF3;                         // +0x0f3
    float m_mode1TurnAB[2];                  // +0x0f4
    float m_airMoveSpeed;                    // +0x0fc
    float m_mode1MoveSpeed;                  // +0x100
    uint8_t m_airMode1P11f8Enable[2];        // +0x104
    uint8_t m_pad106[2];                     // +0x106
    float m_airMode1P11f8[2];                // +0x108
    uint8_t m_groundPerm1Perm0TurnEnable[3]; // +0x110
    uint8_t m_pad113;                        // +0x113
    float m_groundTurnAB[2];                 // +0x114
    float m_groundMoveSpeed;                 // +0x11c
    uint8_t m_groundP11f8Enable;             // +0x120
    uint8_t m_pad121[3];                     // +0x121
    float m_groundP11f8;                     // +0x124
    IKSerializable* m_emitterFxData;   // +0x128 (reference; live: CKExplosionFxData): StartEmitterFx's effect
    // +0x12c..+0x153 the run-time state, not loaded (ResetRuntime / Start).
    CKS08AbilityHostBase* m_pHost;     // +0x12c the host while running
    uint8_t m_bRunning;                // +0x130
    uint8_t m_bLoop;                   // +0x131 in the loop phase (phase 1)
    uint8_t m_bStartAnim;              // +0x132 in the start animation (phase 0)
    uint8_t m_bEndAnim;                // +0x133 in the end animation (phase 4)
    // +0x134 the user is in the air: the host's vt+0x30 inverted (ApplyHeroControl, SwitchLoopAnim). The hero host calls
    // vt+0x30 IsAirborne_maybe, but the elements read it as "on the ground" (the earth boulder's landing explosion when
    // it turns 1 while falling, its jump sound when it turns 0; the enemy host's is CKHkS08Enemy_IsOnGround).
    // ResetRuntime does not write it; its writers run before every read (Start applies the control).
    uint8_t m_bInAir;
    uint8_t m_pad135[3];
    float m_fMana;                     // +0x138 the mana spent and not yet taken (whole points go to the host, vt+0xb8)
    uint8_t m_ui8HotSpot;              // +0x13c the hot spot index (host vt+0xcc / +0xd0; ResetRuntime 0xff)
    uint8_t m_ui8Button;               // +0x13d the button (host vt+0x8c / +0x94; ResetRuntime 0)
    uint8_t m_pad13e[2];
    float m_fStartTime;                // +0x140 the game clock at Start (ResetRuntime -1.0f, TOC +0x41ac)
    float m_fGroundFxTimer;            // +0x144 the time to the next ground FX (Update)
    uint8_t m_bStartCostPending;       // +0x148 the start cost (+0x44) is taken at the loop's first frame
    uint8_t m_pad149[3];
    IKSerializable* m_elementDamage;   // +0x14c (reference; Ghidra: CKS08ElementDamage* pDamage)
    // +0x150 the end is forced (out of mana): End's argument (Start clears it; ResetRuntime does not).
    uint8_t m_bForcedEnd;
    uint8_t m_pad151[3];
};
DOTD_ASSERT_SIZE(CKTransformElement, 0x154);

// The Transform elements' inlined effect code (each unit has its own copies; one set here for the five elements).
class CSGLeaf;
class IKFx;
struct CVector3;
struct SAnimatedFxRig;
namespace TransformFx {
// The inlined reserving lookup 0x9c6468 (CKSrvFx::AcquireFx; not 0x9bdc18, which is StartEffect): a free pooled effect of `data` reserved for `owner`
// and started; null when none.
IKFx* Acquire(IKSerializable* data, const IKSerializable* owner);
// The inlined MessageProc start (CKSrvFx::StartEffect): `data`'s pooled effect (not reserved) or its unique effect.
IKFx* Start(IKSerializable* data, const IKSerializable* owner);
// A pooled explosion of `data` for `owner`: put at `position`, triggered (CKExplosionNodeFx_Trigger 0x1b82a8) and
// released (vt+0x54).
void Explode(IKSerializable* data, const IKSerializable* owner, const CVector3& position);
// The owned effects let go: the particles stopped (StopOwnedParticleEffect 0x1cdde8), the sparks stopped
// (StopOwnedSparkEffect_maybe 0x1d4698), the mesh pop deactivated (CKMeshPopNodeFx_SetActive_maybe 0x1cb568), each then
// released (vt+0x54); the slot cleared. Nothing when the slot is empty.
void ReleaseParticles(IKSerializable** slot, const IKSerializable* owner);
void ReleaseSpark(IKSerializable** slot, const IKSerializable* owner);
void ReleaseMeshPop(IKSerializable** slot, const IKSerializable* owner);
// The inlined geometry alpha walk: every geometry of the node (a CNode) takes `alpha` (the CGeometry colour byte +0x23)
// and the "alpha blended" property bit 11 (vt+0x60 UpdateProperties when it changes); 0xff clears the bit everywhere,
// and a geometry with property bit 12 and a material of mode 1..6 keeps 0xff without blending.
void SetGeometriesAlpha(IKSerializable* node, uint8_t alpha);
// The same for one geometry (a CGeometry).
void SetGeometryAlpha(IKSerializable* geometry, uint8_t alpha);
// The node's scene property bit 2 (hidden) set / cleared.
void HideNode(IKSerializable* node);
void ShowNode(IKSerializable* node);
uint8_t IsNodeHidden(IKSerializable* node);
// The node's frame: the modelling position set, the matrix no longer the identity (flags bit 17 cleared), the frame
// marked dirty (RwFrame_MarkDirty 0x10698).
void SetNodePosition(IKSerializable* node, const CVector3& position);
// The user's scene node (host vt+0x08, IKHook +0x1c).
CSGLeaf* OwnerNode(CKS08AbilityHostBase* host);
// The host's vt+0x104 (the rigs the animated collections play on): the hero host's 0x3ee6a0 answers the hero's +0x1070
// (not overridden by dotd's hero host: read here, as CKFireBreath does); the others' slot is asked.
SAnimatedFxRig* AttachmentSets(CKS08AbilityHostBase* host);
// The game clock (the time manager's IKTime, scalable game time) and this frame's delta.
float GameClock();
float FrameDelta();
}  // namespace TransformFx
DOTD_ASSERT_OFFSET(CKTransformElement, m_damage, 0x8);
DOTD_ASSERT_OFFSET(CKTransformElement, m_damageParam10, 0x14);
DOTD_ASSERT_OFFSET(CKTransformElement, m_cooldown, 0x20);
DOTD_ASSERT_OFFSET(CKTransformElement, m_cooldownForced, 0x2c);
DOTD_ASSERT_OFFSET(CKTransformElement, m_manaPerSecond, 0x38);
DOTD_ASSERT_OFFSET(CKTransformElement, m_manaRequired, 0x44);
DOTD_ASSERT_OFFSET(CKTransformElement, m_dmgRandBase, 0x50);
DOTD_ASSERT_OFFSET(CKTransformElement, m_dmgRandRange, 0x54);
DOTD_ASSERT_OFFSET(CKTransformElement, m_dmgParam2C, 0x58);
DOTD_ASSERT_OFFSET(CKTransformElement, m_dmgParam28, 0x64);
DOTD_ASSERT_OFFSET(CKTransformElement, m_dmgEffect0, 0x70);
DOTD_ASSERT_OFFSET(CKTransformElement, m_dmgEffect1, 0x7c);
DOTD_ASSERT_OFFSET(CKTransformElement, m_dmgEffect2, 0x88);
DOTD_ASSERT_OFFSET(CKTransformElement, m_dmgEffect4, 0x94);
DOTD_ASSERT_OFFSET(CKTransformElement, m_dmgEffect6, 0xa0);
DOTD_ASSERT_OFFSET(CKTransformElement, m_dmgEffect5, 0xac);
DOTD_ASSERT_OFFSET(CKTransformElement, m_dmgEffect7, 0xb8);
DOTD_ASSERT_OFFSET(CKTransformElement, m_dmgEffect3, 0xc4);
DOTD_ASSERT_OFFSET(CKTransformElement, m_dmgFlag34, 0xd0);
DOTD_ASSERT_OFFSET(CKTransformElement, m_dmgFlag35, 0xd3);
DOTD_ASSERT_OFFSET(CKTransformElement, m_groundFxIntervalBase, 0xd8);
DOTD_ASSERT_OFFSET(CKTransformElement, m_groundFxIntervalRange, 0xdc);
DOTD_ASSERT_OFFSET(CKTransformElement, m_unkE0, 0xe0);
DOTD_ASSERT_OFFSET(CKTransformElement, m_airPerm1Perm0TurnEnable, 0xe4);
DOTD_ASSERT_OFFSET(CKTransformElement, m_airTurnAB, 0xe8);
DOTD_ASSERT_OFFSET(CKTransformElement, m_mode1Perm1Perm0TurnEnable, 0xf0);
DOTD_ASSERT_OFFSET(CKTransformElement, m_mode1TurnAB, 0xf4);
DOTD_ASSERT_OFFSET(CKTransformElement, m_airMoveSpeed, 0xfc);
DOTD_ASSERT_OFFSET(CKTransformElement, m_mode1MoveSpeed, 0x100);
DOTD_ASSERT_OFFSET(CKTransformElement, m_airMode1P11f8Enable, 0x104);
DOTD_ASSERT_OFFSET(CKTransformElement, m_airMode1P11f8, 0x108);
DOTD_ASSERT_OFFSET(CKTransformElement, m_groundPerm1Perm0TurnEnable, 0x110);
DOTD_ASSERT_OFFSET(CKTransformElement, m_groundTurnAB, 0x114);
DOTD_ASSERT_OFFSET(CKTransformElement, m_groundMoveSpeed, 0x11c);
DOTD_ASSERT_OFFSET(CKTransformElement, m_groundP11f8Enable, 0x120);
DOTD_ASSERT_OFFSET(CKTransformElement, m_groundP11f8, 0x124);
DOTD_ASSERT_OFFSET(CKTransformElement, m_emitterFxData, 0x128);
DOTD_ASSERT_OFFSET(CKTransformElement, m_pHost, 0x12c);
DOTD_ASSERT_OFFSET(CKTransformElement, m_bRunning, 0x130);
DOTD_ASSERT_OFFSET(CKTransformElement, m_bEndAnim, 0x133);
DOTD_ASSERT_OFFSET(CKTransformElement, m_bInAir, 0x134);
DOTD_ASSERT_OFFSET(CKTransformElement, m_fMana, 0x138);
DOTD_ASSERT_OFFSET(CKTransformElement, m_ui8HotSpot, 0x13c);
DOTD_ASSERT_OFFSET(CKTransformElement, m_ui8Button, 0x13d);
DOTD_ASSERT_OFFSET(CKTransformElement, m_fStartTime, 0x140);
DOTD_ASSERT_OFFSET(CKTransformElement, m_fGroundFxTimer, 0x144);
DOTD_ASSERT_OFFSET(CKTransformElement, m_bStartCostPending, 0x148);
DOTD_ASSERT_OFFSET(CKTransformElement, m_elementDamage, 0x14c);
DOTD_ASSERT_OFFSET(CKTransformElement, m_bForcedEnd, 0x150);
