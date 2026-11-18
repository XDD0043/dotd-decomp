// CKBeamBreath.h - DOTD: the common part of the two fury beam breaths, CKFearEyes (Cynder, 0x92cc) and CKPurpleRay
// (Spyro, 0x930c). Not an original class: the two original units (CKFearEyes.cpp 0x39cf88-0x3a0f00 and CKPurpleRay.cpp
// 0x3c5af0-0x3c9a68) are the same code instruction for instruction (same layout, same Load, same TOC values), except the
// hot spot ResetRuntime picks (fear eyes 6, purple ray 2) and the impact point's pull-back (0.2 / 0.1, TOC +0x373c /
// +0x3d60). The bodies live here once; each class passes its two constants, and every function names both addresses.
//
// The beam: a mesh (one of three CNode, +0x1e8[level]) hung under the breath's hot spot, faded in (+0x1b4 seconds from
// the alpha +0x184 to +0x178), held, and faded out after the breath (+0x1b8 seconds to +0x190); it pitches towards the
// locked target (at most 30 degrees, 2 pi rad/s), yaws onto it when it reaches it, and is scaled to the distance it
// covers (the target, a mesh or a wall). A particle effect follows the hot spot (+0x1c8[level]), an impact effect
// (+0x1d4[level]) sits where the beam stops, a point light (+0x1f4[level]) on the hot spot, and two sounds play.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/logic/CKBreathElement.h"

class CKSound;
class CNode;
struct RwMatrix;

class CKBeamBreath : public CKBreathElement {
public:
    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x0039d9d0 CKFearEyes_Load / 0x003c6538 CKPurpleRay_Load
    // vt+0x30 0x0039d3a0 CKFearEyes_PostLoad / 0x003c5f08 CKPurpleRay_PostLoad: CKBreathElement's (ResetRuntime), then
    // the three beam meshes hidden under sector 0's root (SceneNode_SetVisibleInLayer 1, 0, 0); 1.
    int32_t PostLoad(int32_t type) override;
    // vt+0x58 0x0039d350 CKFearEyes_Start / 0x003c5eb8 CKPurpleRay_Start: the loop sound forgotten (not stopped),
    // CKBreathElement's, then no fade, no pitch, the fade clock at 0.
    void Start(CKS08AbilityHostBase* host) override;
    // vt+0x60 0x0039d328 CKFearEyes_Update / 0x003c5e90 CKPurpleRay_Update: CKBreathElement's (a tail call; inherited).
    // vt+0x64 0x0039d290 CKFearEyes_End / 0x003c5df8 CKPurpleRay_End: the loop sound stopped and forgotten,
    // CKBreathElement's, then the beam mesh hidden again under sector 0's root and forgotten.
    void End(int32_t forced) override;
    // vt+0x74 0x009bfd88 CKFearEyes_StartEmitterFx / 0x009c0298 CKPurpleRay_StartEmitterFx: CKBreathElement's (inherited).
    // vt+0x7c 0x0039d7f0 CKFearEyes_StopBreathing / 0x003c6358 CKPurpleRay_StopBreathing: CKBreathElement's, then the
    // fade-out starts from the mesh's alpha (its first geometry's, else +0x178[level]), or the mesh is hidden at once
    // without a fade-out time (+0x1b8 0).
    void StopBreathing() override;
    // vt+0x84 0x0039d6e8 CKFearEyes_GetEmitterPosition / 0x003c6250 CKPurpleRay_GetEmitterPosition: the beam mesh's at
    // row (its frame's LTM, `raw`: its modelling matrix), else (no mesh, or the null vector) CKBreathElement's.
    CVector3 GetEmitterPosition(uint8_t raw) override;

    // 0x0039d070 CKFearEyes_GetFxSound_maybe / 0x003c5bd8 CKPurpleRay_GetFxSound_maybe: `which` 0 the start sound (1 at
    // level index 2 when it has a sample, else 0); 1 the loop sound (level 2: 6, then 5, then 4; level 1: 5, then 4;
    // else 4; each only with a sample); 4 the end sound (level 2: 3 with a sample, else 2); anything else null.
    CKSound* GetFxSound(uint32_t which);

protected:
    // vt+0x6c 0x0039cfe0 CKFearEyes_ResetRuntime / 0x003c5b48 CKPurpleRay_ResetRuntime: CKBreathElement's, no effects,
    // no mesh, no fade, the hot spot `hotSpot`, the button 2; level data (type 0) also gets a new matrix for the mesh.
    void ResetBeamRuntime(int32_t type, uint8_t hotSpot);
    // vt+0x70 0x003a0518 CKFearEyes_SetFxActive / 0x003c9080 CKPurpleRay_SetFxActive. On: the beam particles on the hot
    // spot (pooled, +0x1e0), the level's mesh shown at its start alpha and hung under the hot spot (its local matrix kept
    // in +0x21c), the beam placed once, the point light on the hot spot (+0x200), the start and loop sounds. Off: the
    // particles, the impact and the light released, the end sound played and the loop sound stopped.
    void SetBeamFxActive(uint8_t on, float impactPullBack);
    // vt+0x78 0x0039ff48 CKFearEyes_UpdateFx / 0x003c8ab0 CKPurpleRay_UpdateFx: the fade clock runs; while the mesh is
    // hung and shown: fade in, hold, or (once the breath stopped) fade out and hide; then the beam placed and the impact
    // effect moved to its end.
    void UpdateBeamFx(float dt, float impactPullBack);
    // 0x0039f228 CKFearEyes_UpdateBeamAndImpact_maybe / 0x003c7d90 CKPurpleRay_UpdateBeamAndImpact_maybe: the mesh put
    // back at its kept local matrix, pitched (towards the locked target, else back to level), yawed onto the target when
    // the beam reaches it, and scaled to its length; the impact effect started where it stops (a mesh, a wall, the
    // target) or released when it stops nowhere. Returns the beam's end (lifted by `impactPullBack` on a mesh hit).
    CVector3 UpdateBeamAndImpact(float impactPullBack);

public:
    int32_t m_unk178[3];         // +0x178 the beam's alpha while held (an integer per level)
    int32_t m_unk184[3];         // +0x184 its alpha at the start of the fade-in
    int32_t m_unk190[3];         // +0x190 its alpha at the end of the fade-out
    float m_unk19c[3];           // +0x19c the mesh's scale across (x and y)
    float m_unk1a8[3];           // +0x1a8 the mesh's own length (the z scale divides by it)
    float m_unk1b4;              // +0x1b4 the fade-in time
    float m_unk1b8;              // +0x1b8 the fade-out time (0: hidden at once)
    float m_unk1bc[3];           // +0x1bc the beam's length (the Load reads five words +0x1b4..+0x1c4)
    IKSerializable* m_unk1c8[3]; // +0x1c8 references (live: CKParticlesEffectFxData): the beam particles of each level
    IKSerializable* m_unk1d4[3]; // +0x1d4 references (live: CKParticlesEffectFxData): the impact particles of each level
    IKSerializable* m_unk1e0;    // +0x1e0 (not loaded) the beam particle effect (a CKParticlesEffectNodeFx)
    IKSerializable* m_unk1e4;    // +0x1e4 (not loaded) the impact particle effect
    CNode* m_unk1e8[3];          // +0x1e8 references (live: CNode): the beam meshes of each level
    IKSerializable* m_unk1f4[3]; // +0x1f4 references (live: CKPointLightFxData) of each level
    IKSerializable* m_unk200;    // +0x200 (not loaded) the point light effect
    IKSerializable* m_unk204;    // +0x204 reference (live: CKAimCamembert)
    IKSerializable* m_unk208;    // +0x208 reference (live: CKSoundDictionaryID)
    CNode* m_unk20c;             // +0x20c (not loaded) the mesh in use
    uint32_t m_unk210;           // +0x210 (not loaded) the mesh's alpha when the breath stopped
    uint8_t m_unk214;            // +0x214 (not loaded) faded in (set once held; the fade-out runs while it is set)
    uint8_t m_pad215[3];
    float m_unk218;              // +0x218 (not loaded) the fade clock
    RwMatrix* m_unk21c;          // +0x21c (not loaded) the mesh's local matrix under the hot spot (ResetRuntime type 0)
    CKSound* m_unk220;           // +0x220 (not loaded) the loop sound
    float m_unk224;              // +0x224 (not loaded) the beam's pitch (radians)
};
DOTD_ASSERT_SIZE(CKBeamBreath, 0x228);
DOTD_ASSERT_OFFSET(CKBeamBreath, m_unk178, 0x178);
DOTD_ASSERT_OFFSET(CKBeamBreath, m_unk184, 0x184);
DOTD_ASSERT_OFFSET(CKBeamBreath, m_unk190, 0x190);
DOTD_ASSERT_OFFSET(CKBeamBreath, m_unk19c, 0x19c);
DOTD_ASSERT_OFFSET(CKBeamBreath, m_unk1a8, 0x1a8);
DOTD_ASSERT_OFFSET(CKBeamBreath, m_unk1b4, 0x1b4);
DOTD_ASSERT_OFFSET(CKBeamBreath, m_unk1b8, 0x1b8);
DOTD_ASSERT_OFFSET(CKBeamBreath, m_unk1bc, 0x1bc);
DOTD_ASSERT_OFFSET(CKBeamBreath, m_unk1c8, 0x1c8);
DOTD_ASSERT_OFFSET(CKBeamBreath, m_unk1d4, 0x1d4);
DOTD_ASSERT_OFFSET(CKBeamBreath, m_unk1e0, 0x1e0);
DOTD_ASSERT_OFFSET(CKBeamBreath, m_unk1e4, 0x1e4);
DOTD_ASSERT_OFFSET(CKBeamBreath, m_unk1e8, 0x1e8);
DOTD_ASSERT_OFFSET(CKBeamBreath, m_unk1f4, 0x1f4);
DOTD_ASSERT_OFFSET(CKBeamBreath, m_unk200, 0x200);
DOTD_ASSERT_OFFSET(CKBeamBreath, m_unk204, 0x204);
DOTD_ASSERT_OFFSET(CKBeamBreath, m_unk208, 0x208);
DOTD_ASSERT_OFFSET(CKBeamBreath, m_unk20c, 0x20c);
DOTD_ASSERT_OFFSET(CKBeamBreath, m_unk210, 0x210);
DOTD_ASSERT_OFFSET(CKBeamBreath, m_unk214, 0x214);
DOTD_ASSERT_OFFSET(CKBeamBreath, m_unk218, 0x218);
DOTD_ASSERT_OFFSET(CKBeamBreath, m_unk21c, 0x21c);
DOTD_ASSERT_OFFSET(CKBeamBreath, m_unk220, 0x220);
DOTD_ASSERT_OFFSET(CKBeamBreath, m_unk224, 0x224);
