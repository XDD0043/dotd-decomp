// CKWindBeam.h - the wind beam grab (key 0xa50c, vtable 0xb24920, size 0x318). Original unit: CKWindBeam.cpp
// (0x3e0248-0x3e6f80). Derives from CKGrabElement (its constructor and Load run first). No XXL2 class of this name.
// Cynder's wind element (ability id 0x12, C2.7: LVL010's breath2 recording uses it from +2752). The beam is a cubic
// Bezier from the hot spot (+0x12c) to an end point (+0x2f4) that flies to the grabbed enemy (or along the aim), its
// two inner control points (+0x2c4, +0x2d0) wandering at random rates; particles are emitted along it (+0x21c / +0x228
// per level), a beam mesh (+0x1a4) spins at the target and a tip mesh (+0x1f8) hangs under the hot spot. The held
// enemy is pulled (the hero host's GrabEnemy / GetGrabPullRatio) until its wind gauge is full, then thrown.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/logic/CKGrabElement.h"
#include "k2000/math/Vec3.h"

class CKSound;

class CKWindBeam : public CKGrabElement {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x294)
    int32_t IsKindOfClass(uint32_t key) override {  // vt+0x08 0x9c0930
        return key == 0xa50c || key == 0xc || key == 0x9fcc || key == 0x90cc;
    }
    DOTD_DECLARE_FACTORIES(CKWindBeam)

    CKWindBeam() {}  // 0x003e04a0 CKWindBeam_Construct: CKGrabElement's constructor, then the vtable only
    ~CKWindBeam() override {}
    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x003e4a18 CKWindBeam_Load
    // vt+0x30 0x003e03e8 CKWindBeam_PostLoad: the base's (ResetRuntime), then both meshes (+0x1a4, +0x1f8) hidden under
    // sector 0's root.
    int32_t PostLoad(int32_t type) override;

    // The ability protocol (CKGrabElement.h).
    // vt+0x50 0x003e0238 CKWindBeam_GetAbilityId (its address is in CKTransformElement.cpp's range: that unit's
    // checklist lists it).
    uint8_t GetAbilityId() override { return 0x12; }
    // vt+0x58 0x003e0658 CKWindBeam_Start: the loop sound dropped, the base's, then the beam state cleared (fades,
    // times, points, the control points, rates and end point the null vector, the pull state 0).
    void Start(CKS08AbilityHostBase* host) override;
    // vt+0x64 0x003e0800 CKWindBeam_End: the loop sound stopped, the target let go (vt+0x7c with the null vector), both
    // meshes hidden under sector 0's root, the base's.
    void End(int32_t forced) override;
    // vt+0x6c 0x003e0e38 CKWindBeam_ResetRuntime: the base's, the hot spot 2, the beam state cleared, the six particle
    // nodes' scene property 0x8000 set.
    void ResetRuntime() override;
    // vt+0x70 0x003e14a0 CKWindBeam_SetFxActive: on: the level's two particle effects (+0x1fc on the hot spot, +0x20c
    // on the beam mesh), the tip mesh under the hot spot, the level's particle nodes emitting, the start and loop
    // sounds; off: the effects stopped and released, the nodes not emitting, the loop sound stopped.
    void SetFxActive(int32_t on) override;
    // vt+0x7c 0x003e0f98 CKWindBeam_GrabTarget_maybe: before a pulled target (state 3) is let go, `direction` and the
    // damage's push take the end point's velocity; then the base's (with a copy of `direction`). Let go: the attack
    // spheres off (host vt+0xfc), the permissions 1 / 0 back; grabbed: the beam mesh at the target's aim point, shown
    // with the level's alpha, permission 1 off and 0 on in the air and on the ground.
    void GrabTarget(uint8_t grab, uint8_t mode, CVector3* direction) override;
    // vt+0x80 0x003e08f0 CKWindBeam_Slot80_maybe: the hold goes on while a target is held (host GrabEnemy, vt+0xec,
    // keeps it): the pull state machine (0 aim, 1 the damage parameters, 2 pulling with the attack spheres until the
    // host's pull ratio reaches 1, then 3 the throw spheres). 0: lost.
    uint8_t Vf80(float dt) override;
    // vt+0x84 0x003e1e60 CKWindBeam_Slot84_maybe: the meshes' fades and spin, the beam's control points (28 Rand_Int
    // draw sites) and its particle emission. See the definition.
    void Vf84(float dt) override;
    // vt+0x88 0x003e0cd8 CKWindBeam_ReleaseAndStopFx_maybe: the base's, then both meshes start fading from their current
    // alpha (or are hidden at once without a fade time); the release time noted.
    void ReleaseAndStopFx() override;
    // vt+0x8c 0x003e0248 CKWindBeam_ApplyDamageParams: the base's, then the damage's knock angle (+0x18) the level's
    // +0x140 in radians.
    void ApplyDamageParams(uint8_t continuous) override;
    uint8_t Vf90() override { return 1; }  // vt+0x90 0x009c0990: the effects follow the loop phase
    // (vt+0x78 0x009c0998 CKWindBeam_StartEmitterFx only calls the base's.)

    // 0x003e02a0 CKWindBeam_GetFxSound_maybe: sound 0 of the dictionary (`which` 0, the start), or (1) the loop of the
    // level: index 1 by default, 2 at level index 1 and 2, 3 at level index 2, each only when it has a sample.
    CKSound* GetFxSound(int32_t which);

    float m_afKnockAngleDeg[3];            // +0x140 (file and live: 0) the knock angle in degrees (ApplyDamageParams)
    int32_t m_ai32BeamMeshFullAlpha[3];          // +0x14c the beam mesh's alpha at full pull (Vf84), else at release
    int32_t m_ai32BeamMeshGrabAlpha[3];          // +0x158 the beam mesh's alpha when grabbed (GrabTarget, Vf84)
    int32_t m_ai32BeamMeshEndAlpha[3];          // +0x164 (live: 0) the beam mesh's alpha at the end of its fade
    float m_afBeamMeshSpinDegPerSec[3];            // +0x170 the beam mesh's spin, degrees per second
    float m_avBeamMeshScale[3][3];         // +0x17c three vectors, each one 12-byte read: the beam mesh's scale
    float m_fBeamMeshFadeTime;               // +0x1a0 the beam mesh's fade time (0: hidden at release)
    IKSerializable* m_pBeamMesh;     // +0x1a4 reference (live: CNode): the beam mesh
    int32_t m_ai32TipMeshFullAlpha[3];          // +0x1a8 the tip mesh's alpha once shown
    int32_t m_ai32TipMeshStartAlpha[3];          // +0x1b4 (live: 0) the tip mesh's alpha at SetFxActive
    int32_t m_ai32TipMeshEndAlpha[3];          // +0x1c0 (live: 0) the tip mesh's alpha at the end of its fade
    float m_avTipMeshScale[3][3];         // +0x1cc three vectors, each one 12-byte read: the tip mesh's scale
    float m_fTipMeshFadeInTime;               // +0x1f0 (live: 0) the tip mesh's fade-in time
    float m_fTipMeshFadeOutTime;               // +0x1f4 (live: 0) the tip mesh's fade-out time (0: hidden at release)
    IKSerializable* m_pTipMesh;     // +0x1f8 reference (live: CNode): the tip mesh
    IKSerializable* m_apHotSpotParticles[3];  // +0x1fc references (live: CKParticlesEffectFxData): the effect on the hot spot
    IKSerializable* m_pFx208;     // +0x208 (not loaded) runtime: +0x1fc's effect (CKParticlesEffectNodeFx)
    IKSerializable* m_apBeamMeshParticles[3];  // +0x20c references (live: CKParticlesEffectFxData): the effect on the beam mesh
    IKSerializable* m_pFx218;     // +0x218 (not loaded) runtime: +0x20c's effect (CKParticlesEffectNodeFx)
    IKSerializable* m_apBeamStreamParticlesA[3];  // +0x21c references (live: CParticlesNodeFx): the beam's particles
    IKSerializable* m_apBeamStreamParticlesB[3];  // +0x228 references (live: CParticlesNodeFx): the beam's second particles
    uint32_t m_ui32BezierSampleCount;            // +0x234 the beam's point count (the Bezier samples)
    // +0x238..+0x288 (index = (offset - 0x238) / 4): [0] the beam's growth speed, [1..3] the end point's top speed
    // per level, [4..6] its acceleration per level, then the inner control points' random ranges (base, spread):
    // [7, 8] +0x2c4's length rate, [9] its cone (degrees), [10, 11] its length, [12, 13] its turn rates; [14, 15]
    // +0x2d0's length rate, [16] its cone, [17, 18] its length, [19, 20] its turn rates.
    float m_afBezierDynamics[21];
    IKSerializable* m_pSoundDico;     // +0x28c reference (live: CKSoundDictionaryID)
    IKSerializable* m_apThrowDamages[3];  // +0x290 references (live: CKS08StunDamage): the throw's damage per level
    // Runtime (not loaded).
    uint32_t m_unk29c;            // +0x29c cleared by GrabTarget and ResetRuntime (not read here)
    float m_fElapsedTime;               // +0x2a0 the time since Start
    float m_fReleaseTime;               // +0x2a4 +0x2a0 at the release
    uint8_t m_bBeamMeshFadingOut;             // +0x2a8 the beam mesh fades out
    uint8_t m_pad2a9[3];
    uint32_t m_ui32BeamReleaseAlpha;            // +0x2ac the beam mesh's alpha at the release
    uint8_t m_bTipMeshShown;             // +0x2b0 the tip mesh is shown (fades out once released)
    uint8_t m_pad2b1[3];
    uint32_t m_ui32TipReleaseAlpha;            // +0x2b4 the tip mesh's alpha at the release
    CKSound* m_pLoopSound;        // +0x2b8 the loop sound playing
    uint32_t m_ui32GrownPoints;            // +0x2bc the beam's points grown so far (up to +0x234)
    float m_fEmitPhase;               // +0x2c0 the emission phase (the fraction of a point)
    CVector3 m_vCtrlPoint1;            // +0x2c4 the first inner control point (from the hot spot)
    CVector3 m_vCtrlPoint2;            // +0x2d0 the second inner control point (from the end point)
    // +0x2dc the six random rates: +0x2c4's length, z turn, x turn; +0x2d0's length, z turn, x turn.
    float m_afCtrlWanderRates[6];
    CVector3 m_vEndPoint;            // +0x2f4 the end point
    CVector3 m_vEndVelocity;            // +0x300 the end point's velocity
    float m_fPullStateTime;               // +0x30c the time in pull state 2
    uint32_t m_ui32PullState;            // +0x310 the pull state (0 aim, 1 damage set, 2 pulling, 3 thrown)
    uint8_t m_bTargetUncatchable;             // +0x314 the target could not be held at the beam's end (CanGrabTarget)
    uint8_t m_pad315[3];
};
DOTD_ASSERT_SIZE(CKWindBeam, 0x318);
DOTD_ASSERT_OFFSET(CKWindBeam, m_afKnockAngleDeg, 0x140);
DOTD_ASSERT_OFFSET(CKWindBeam, m_ai32BeamMeshFullAlpha, 0x14c);
DOTD_ASSERT_OFFSET(CKWindBeam, m_ai32BeamMeshGrabAlpha, 0x158);
DOTD_ASSERT_OFFSET(CKWindBeam, m_ai32BeamMeshEndAlpha, 0x164);
DOTD_ASSERT_OFFSET(CKWindBeam, m_afBeamMeshSpinDegPerSec, 0x170);
DOTD_ASSERT_OFFSET(CKWindBeam, m_avBeamMeshScale, 0x17c);
DOTD_ASSERT_OFFSET(CKWindBeam, m_fBeamMeshFadeTime, 0x1a0);
DOTD_ASSERT_OFFSET(CKWindBeam, m_pBeamMesh, 0x1a4);
DOTD_ASSERT_OFFSET(CKWindBeam, m_ai32TipMeshFullAlpha, 0x1a8);
DOTD_ASSERT_OFFSET(CKWindBeam, m_ai32TipMeshStartAlpha, 0x1b4);
DOTD_ASSERT_OFFSET(CKWindBeam, m_ai32TipMeshEndAlpha, 0x1c0);
DOTD_ASSERT_OFFSET(CKWindBeam, m_avTipMeshScale, 0x1cc);
DOTD_ASSERT_OFFSET(CKWindBeam, m_fTipMeshFadeInTime, 0x1f0);
DOTD_ASSERT_OFFSET(CKWindBeam, m_fTipMeshFadeOutTime, 0x1f4);
DOTD_ASSERT_OFFSET(CKWindBeam, m_pTipMesh, 0x1f8);
DOTD_ASSERT_OFFSET(CKWindBeam, m_apHotSpotParticles, 0x1fc);
DOTD_ASSERT_OFFSET(CKWindBeam, m_pFx208, 0x208);
DOTD_ASSERT_OFFSET(CKWindBeam, m_apBeamMeshParticles, 0x20c);
DOTD_ASSERT_OFFSET(CKWindBeam, m_pFx218, 0x218);
DOTD_ASSERT_OFFSET(CKWindBeam, m_apBeamStreamParticlesA, 0x21c);
DOTD_ASSERT_OFFSET(CKWindBeam, m_apBeamStreamParticlesB, 0x228);
DOTD_ASSERT_OFFSET(CKWindBeam, m_ui32BezierSampleCount, 0x234);
DOTD_ASSERT_OFFSET(CKWindBeam, m_afBezierDynamics, 0x238);
DOTD_ASSERT_OFFSET(CKWindBeam, m_pSoundDico, 0x28c);
DOTD_ASSERT_OFFSET(CKWindBeam, m_apThrowDamages, 0x290);
DOTD_ASSERT_OFFSET(CKWindBeam, m_unk29c, 0x29c);
DOTD_ASSERT_OFFSET(CKWindBeam, m_fElapsedTime, 0x2a0);
DOTD_ASSERT_OFFSET(CKWindBeam, m_bBeamMeshFadingOut, 0x2a8);
DOTD_ASSERT_OFFSET(CKWindBeam, m_bTipMeshShown, 0x2b0);
DOTD_ASSERT_OFFSET(CKWindBeam, m_pLoopSound, 0x2b8);
DOTD_ASSERT_OFFSET(CKWindBeam, m_ui32GrownPoints, 0x2bc);
DOTD_ASSERT_OFFSET(CKWindBeam, m_vCtrlPoint1, 0x2c4);
DOTD_ASSERT_OFFSET(CKWindBeam, m_vCtrlPoint2, 0x2d0);
DOTD_ASSERT_OFFSET(CKWindBeam, m_afCtrlWanderRates, 0x2dc);
DOTD_ASSERT_OFFSET(CKWindBeam, m_vEndPoint, 0x2f4);
DOTD_ASSERT_OFFSET(CKWindBeam, m_vEndVelocity, 0x300);
DOTD_ASSERT_OFFSET(CKWindBeam, m_fPullStateTime, 0x30c);
DOTD_ASSERT_OFFSET(CKWindBeam, m_ui32PullState, 0x310);
DOTD_ASSERT_OFFSET(CKWindBeam, m_bTargetUncatchable, 0x314);
