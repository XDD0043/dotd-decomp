// CKLightningBoltNodeFx.h - the lightning-bolt effect node (key 0xa60c, vtable 0xb2e0b0, size 0x250).
// Original unit: CKLightningBoltNodeFx.cpp (0x57a7c8-0x582b00, GAME_TOC2). Its data is CKLightningBoltFxData (0xa64c).
// Not in XXL2; names ours (from the code: the heroes' partner link, the electrical grapple and the hazardous jets use it).
//
// The bolt is a tree of segments (+0x54, 100-byte records) from the node's origin to its end point: the root (index 0)
// runs from the origin to the start point (+0x30); each segment of a level splits into children that follow it, offset
// across it and wiggling (GenerateBranch, UpdateBranchesRecursive), with random lifetimes that regrow them. The four
// level channels (+0x90) hold the branching parameters of each level (CKLightningBoltFxData's segments, copied in).
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/fx/IKNodeFx.h"
#include "k2000/math/CMatrix34.h"
#include "k2000/util/TVector.h"

class CKDynamicBoundingSphere;
class IKTime;

class CKLightningBoltNodeFx : public IKNodeFx {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x298)
    int32_t IsKindOfClass(uint32_t key) override {  // vt+0x08 0x9cb068
        return key == 0xa60c || key == 0x148c || key == 0x154c || key == 0xc;
    }
    DOTD_DECLARE_FACTORIES(CKLightningBoltNodeFx)

    // One level's branching parameters (0x3c bytes; CKLightningBoltFxData_CopyEntry60 0x577868 copies the data's).
    struct SLevel {
        float m_fBranchChance;   // +0x00 the percent chance that a segment of this level branches
        float m_unk04;           // +0x04
        float m_unk08;           // +0x08
        float m_unk0c;           // +0x0c
        float m_fDensity;        // +0x10 the children per (scaled) length
        float m_fWidth;          // +0x14 a segment's width: the centre and its random range
        float m_fWidthRange;     // +0x18
        float m_fLifetime;       // +0x1c a segment's lifetime: the rate (1 / seconds) and its range
        float m_fLifetimeRange;  // +0x20
        float m_fSpread;         // +0x24 the children's offset across the parent (x the scaled length)
        float m_fJitter;         // +0x28 the children's spacing jitter along the parent
        float m_fSpeed;          // +0x2c the wiggle speed and its range
        float m_fSpeedRange;     // +0x30
        float m_fAccel;          // +0x34 the wiggle acceleration and its range
        float m_fAccelRange;     // +0x38
    };

    // One segment of the tree (100 bytes). A child's start / end are (t along the parent, offset along the parent's up,
    // unused); the root's are points of the node's space.
    struct SSegment {
        uint32_t m_ui32Level;       // +0x00
        float m_afStart[3];         // +0x04
        float m_afEnd[3];           // +0x10 the next sibling's start (UpdateBranchesRecursive)
        float m_fSpeed;             // +0x1c the wiggle of the start offset (+0x08)
        float m_fAccel;             // +0x20
        float m_fAmplitude;         // +0x24 the offset's bound (the offset folds back at it)
        uint32_t m_ui32Parent;      // +0x28 the parent's index (the root: itself)
        uint32_t m_ui32FirstChild;  // +0x2c
        uint32_t m_ui32NbChildren;  // +0x30
        uint8_t m_bLeaf;            // +0x34 set when the segment did not branch
        uint8_t m_bPointsCached;    // +0x35 ComputeBranchPoint's results are current (cleared every frame)
        uint8_t m_pad36[2];
        float m_fWidth;             // +0x38
        CVector3 m_vPoint;          // +0x3c ComputeBranchPoint: the start in the node's space
        CVector3 m_vDirection;      // +0x48 the vector to the end
        CVector3 m_vUp;             // +0x54 the up of the basis from the direction and the node's right
        float m_fExpiry;            // +0x60 the bolt time (+0x48) at which it regrows
    };

    // One impact slot (+0x184, five): a sub-bolt (the data's +0x8c) jumping from the end point to a target in range.
    struct SImpactSlot {
        IKSerializable* m_pTarget;  // +0x00 the hero, enemy or mechanism actor hit (CollectTargetsInRange)
        IKSerializable* m_pFx;  // +0x04 the sub-bolt (Stop releases it through vt+0x58)
        float m_fTimer;     // +0x08 the time to the next search (a random interval: the data's +0xa0 / +0xa4)
        uint8_t m_bActive;  // +0x0c a sub-bolt is on its target
        uint8_t m_pad0d[3];
    };

    CKLightningBoltNodeFx();  // inlined in 0x0057b710 CKLightningBoltNodeFx_Create
    ~CKLightningBoltNodeFx() override {}

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x0057bae0 CKLightningBoltNodeFx_Load
    // vt+0x30 0x0057c3c8 CKLightningBoltNodeFx_PostLoad: IKNodeFx's, the segments allocated, bit 3 cleared, the bolt reset.
    int32_t PostLoad(int32_t type) override;
    void Destroy() override;  // vt+0x10 0x0057ab48 CKLightningBoltNodeFx_Destroy: the segment block freed
    // vt+0x64 0x0057c320 CKLightningBoltNodeFx_Start: reserved, the bolt reset; without data stopped.
    void Vf64() override;
    IKFxData* GetFxData() override { return reinterpret_cast<IKFxData*>(m_pFxData); }  // vt+0x80 0x9cb0b8
    void SetFxData(IKFxData* data) override { m_pFxData = reinterpret_cast<IKSerializable*>(data); }  // vt+0x84 0x9cb0c0

    // 0x0057aad8 / 0x0057b990 CKLightningBoltNodeFx_SetStart/EndIntensity_maybe: for the owner, byte / 255 in [0, 1].
    void SetStartIntensity(uint8_t intensity, const IKSerializable* owner);
    void SetEndIntensity(uint8_t intensity, const IKSerializable* owner);
    // 0x0057b968 CKLightningBoltNodeFx_SetField20C_maybe: for the owner (reserved, +0x08), the width scale +0x20c.
    void SetField20C(float value, const IKSerializable* owner);
    // 0x0057a890 / 0x0057a8d0 CKLightningBoltNodeFx_SetStart/EndSmoothParams_maybe: when `owner` holds the reservation,
    // the fade's target ([5]), speed ([4]) and rates ([0], [1], [2]), and its timer (+0x248 / +0x24c).
    void SetStartSmoothParams(float target, float timer, float rate0, float rate1, float speed, float rate2,
                              const IKSerializable* owner);
    void SetEndSmoothParams(float target, float timer, float rate0, float rate1, float speed, float rate2,
                            const IKSerializable* owner);
    // 0x0057a9d0 CKLightningBoltNodeFx_SetTargetPoint_maybe: when `owner` holds the reservation, the offset (+0x24).
    void SetTargetPoint(const CVector3* point, const IKSerializable* owner);
    // 0x0057c430 CKLightningBoltNodeFx_SetNodePositionIfOwner_maybe: when `owner` holds the reservation, the node's
    // modelling position.
    void SetNodePosition(const CVector3* point, const IKSerializable* owner);
    // 0x0057aab0 / 0x0057aa10 / 0x0057aa60 / 0x0057aa88 / 0x0057aa38 CKLightningBoltNodeFx_SetField1D8 / 1E0 / 1E4 /
    // 1E6 / 1E8_maybe: when `owner` holds the reservation, the sphere's damage, owner, owner type, property flags and
    // +0x1e8 (the grab's target; the electric grapple sets them).
    void SetDamage(IKSerializable* damage, const IKSerializable* owner);
    void SetDamageOwner(IKSerializable* damageOwner, const IKSerializable* owner);
    void SetDamageCategory(uint8_t category, const IKSerializable* owner);
    void SetDamageFlags(uint16_t flags, const IKSerializable* owner);
    void SetUnk1e8(IKSerializable* value, const IKSerializable* owner);
    // 0x005829a0 CKLightningBoltNodeFx_RestartForOwner_maybe: when `owner` holds the reservation, started for it
    // (SetActiveForOwner) with the lifetime `lifetime` and the lifetime flag (bit 2).
    void RestartForOwner(float lifetime, const IKSerializable* owner);

    // 0x0057b3d0 CKLightningBoltNodeFx_AllocSegments_maybe: +0x20 segments (100 bytes each), the new ones blank.
    void AllocSegments();
    // 0x0057bfd8 CKLightningBoltNodeFx_ResetBolt_maybe: the node at the origin, the points, levels, impacts and fades
    // reset, a random roll angle (+0x50, one rand draw).
    void ResetBolt();
    // 0x0057b0c0 CKLightningBoltNodeFx_UpdateFades_maybe: the start and end fades (+0x210, +0x22c) step; a fade done
    // with its timer running counts it down and, at its end, starts fading back in.
    void UpdateFades(IKTime* frameClock);
    // 0x0057c818 CKLightningBoltNodeFx_ComputeBranchPoint_maybe: segment `index`'s point, direction and up (cached).
    void ComputeBranchPoint(uint32_t index, CVector3* point, CVector3* direction, CVector3* up);
    // 0x0057cc20 CKLightningBoltNodeFx_GenerateBranch_maybe: segment `index` (spanning [t0, t1] of the bolt) gets a new
    // lifetime (and the root a width) and may branch into children laid out along it, which are generated in turn.
    void GenerateBranch(float t0, float t1, uint32_t index);
    // 0x0057d678 CKLightningBoltNodeFx_UpdateBranchesRecursive_maybe: an expired segment regrows; the others wiggle;
    // the children are updated and joined end to start.
    void UpdateBranchesRecursive(float t0, float t1, IKTime* frameClock, uint32_t index);
    // 0x0057bd30 CKLightningBoltNodeFx_RemoveBranchRecursive_maybe: segment `index`'s children (and theirs) removed, the
    // later segments moved down and the indices fixed.
    void RemoveBranchRecursive(uint32_t index);
    // vt+0x6c 0x00581178 CKLightningBoltNodeFx_Stop: the end particles, impacts and sphere released, stopped, the node
    // hidden under the dynamic scene root, inactive.
    void Stop() override;
    // 0x00580c58 CKLightningBoltNodeFx_SetEndParticlesActive_maybe: on, the data's two particle effects (+0x40, +0x44)
    // attached to the node and taken from the FX pool; off, released.
    void SetEndParticlesActive(int32_t active);
    void PlaceNodeAtSource(const IKSerializable* owner);  // 0x0057c650 CKLightningBoltNodeFx_PlaceNodeAtSource_maybe
    void SyncNodeToTarget();                              // 0x0057c4c8 CKLightningBoltNodeFx_SyncNodeToTarget_maybe
    void UpdateEndpoints();                               // 0x0057ae68 CKLightningBoltNodeFx_UpdateEndpoints_maybe
    void ResetImpactSlots();                              // 0x0057ac28 CKLightningBoltNodeFx_ResetImpactSlots_maybe
    void SetActiveForOwner(const IKSerializable* owner, int32_t active);  // 0x00581380 _SetActiveForOwner_maybe
    // 0x005806c8 CKLightningBoltNodeFx_UpdateImpactExplosions_maybe: the two explosion timers count down; one past 0
    // sets off the data's explosion (+0x48 at the node, +0x4c at the end point) and draws its next interval.
    void UpdateImpactExplosions(IKTime* frameClock);
    // 0x00581c38 CKLightningBoltNodeFx_UpdateImpactSlots_maybe: see the definition.
    void UpdateImpactSlots(IKTime* frameClock);
    // 0x005823f0 CKLightningBoltNodeFx_UpdateImpacts_maybe: UpdateImpactExplosions, UpdateImpactSlots, then the end
    // particles (+0x1f0) placed at the start point. No caller in the EBOOT (Update inlines the same three steps).
    void UpdateImpacts(IKTime* frameClock);
    // vt+0x7c 0x0057b780 CKLightningBoltNodeFx_StopIfLinkedTo: a running bolt whose data has flag 4 (+0x18) stops (vt+0x6c)
    // when its source node, the source hot spot's node, the target node or the target hot spot's node is in `sector`.
    void StopIfLinkedTo(int32_t sector) override;
    // vt+0x24 0x0057b5f0 CKLightningBoltNodeFx_RecursiveRegistration: registered with the saving manager (every type),
    // then the node base's.
    void RecursiveRegistration(int32_t type) override;
    // 0x0057e348 CKLightningBoltNodeFx_CollectTargetsInRange_maybe: the nearest target (Manhattan distance from the end
    // point within the data's +0x98 -/+ +0x9c) among the heroes (data flag 0x40), the active enemies (0x80) and the
    // mechanism group's active actors (0x100) that has a node, is not linked to this bolt already (IsLinkedTo) and that
    // the game manager accepts (vf13C); its aim point (vf140) into `position`. Null when none.
    IKSerializable* CollectTargetsInRange(CVector3* position);
    // 0x0057dce8 CKLightningBoltNodeFx_IsLinkedTo_maybe: `target` is one of the impact slots' targets, of a running
    // sub-bolt's (recursively, but `from`), of the owner bolt's (recursively, when the owner is a bolt but `from`) or
    // the +0x1e8 target. The compiler inlines two levels of the recursion.
    uint8_t IsLinkedTo(const IKSerializable* target, const CKLightningBoltNodeFx* from);
    // 0x00580030 CKLightningBoltNodeFx_RebuildGeometry_maybe: the strip of the node's geometry rebuilt: the texture's
    // height over width (+0x8c), the leaves' vertex pairs (BuildBranchVertices), then the end cap at the start point
    // repeated over the unused vertices, the texture coordinates along both sides, the atomic's sphere.
    void RebuildGeometry();
    // 0x0057ec40 CKLightningBoltNodeFx_BuildBranchVertices_maybe: depth first, a segment with children passes
    // `previous` (the last leaf) through them; a leaf adds a vertex pair across the joint between the previous leaf and
    // itself (the first leaf: across its own start), widened by the joint's angle (two pairs with the data's flag 0x20),
    // and the texture distance along each side, unless the strip is full (+0x20 - 1); returns the last leaf.
    uint32_t BuildBranchVertices(uint32_t index, uint32_t previous, float* texLeft, float* texRight, CVector3** left,
                                 CVector3** right, float** uvs);
    // 0x0057b230 CKLightningBoltNodeFx_UpdateVertexColors_maybe: the data's colours along the strip (both sides).
    void UpdateVertexColors();
    // vt+0x78 0x00582470 CKLightningBoltNodeFx_Update: stops when the lifetime (or the data's) is over; else the node
    // follows the source and turns toward the end point, rolling by the data's speed; the branches, fades,
    // explosions and end particles updated.
    void Update(IKTime* frameClock) override;

    IKSerializable* m_pFxData;          // +0x14 a CKLightningBoltFxData (GetFxData / SetFxData 0x9cb0b8 / 0x9cb0c0)
    uint8_t m_unk18;                    // +0x18
    uint8_t m_pad19[3];
    uint32_t m_ui32MaxLevels;           // +0x1c the levels that may branch (LVL010: 2)
    uint32_t m_ui32NbVertices;          // +0x20 the segment budget and the strip's vertices per side (LVL010: 100)
    CVector3 m_vSourceOffset;           // +0x24 added to the end hot spot's position (UpdateEndpoints)
    CVector3 m_vStart;                  // +0x30 the root's end point in the node's space
    CVector3 m_vEnd;                    // +0x3c the end point in the world
    float m_fTime;                      // +0x48 the bolt's time
    float m_fLifetime;                  // +0x4c with bit 2: the bolt stops after it
    float m_fRollAngle;                 // +0x50 degrees: the node turns about its direction (ResetBolt: random)
    TVector<SSegment, 1> m_segments;    // +0x54 the constructor: null, 1, 0
    uint32_t m_ui32NbStripVertices;     // +0x60 the vertices per side of the built strip
    uint32_t m_ui32NbSegments;          // +0x64 the segments in use
    CVector3 m_vDirection;              // +0x68 the normalised root direction
    CVector3 m_vRight;                  // +0x74 the node basis (Update)
    CVector3 m_vUp;                     // +0x80
    float m_unk8c;                      // +0x8c ResetBolt: 1.0
    SLevel m_aLevels[4];                // +0x90
    uint32_t m_ui32MaxSegments;         // +0x180 ResetBolt / AllocSegments: m_ui32NbVertices
    SImpactSlot m_aImpacts[5];          // +0x184
    uint32_t m_ui32NbImpacts;           // +0x1d4
    IKSerializable* m_pDamage;          // +0x1d8 the sphere's +0x1c (a CKS08Damage)
    CKDynamicBoundingSphere* m_pSphere; // +0x1dc the collision service's projectile sphere at the end point
    IKSerializable* m_pDamageOwner;     // +0x1e0 the sphere's owner; none: no sphere
    uint8_t m_ui8DamageCategory;        // +0x1e4 the sphere's owner type
    uint8_t m_pad1e5;
    uint16_t m_ui16DamageFlags;         // +0x1e6 or-ed into the sphere's property flags
    IKSerializable* m_unk1e8;           // +0x1e8 the electric grapple's target (SetUnk1e8)
    IKSerializable* m_pStartParticles;  // +0x1ec the owned particle effect of the data's +0x40
    IKSerializable* m_pEndParticles;    // +0x1f0 the owned particle effect at the start point
    uint32_t m_unk1f4;                  // +0x1f4
    uint32_t m_unk1f8;                  // +0x1f8
    float m_fSourceExplosionTimer;      // +0x1fc UpdateImpactExplosions: to the next source explosion
    float m_fEndExplosionTimer;         // +0x200 to the next end explosion
    float m_fStartIntensity;            // +0x204 the colour scale at the start / end of the strip (SetStart/EndIntensity)
    float m_fEndIntensity;              // +0x208
    float m_unk20c;                     // +0x20c ResetBolt: 1.0
    float m_afStartFade[7];             // +0x210 a Math_ApproachWithAccelDecel state: current +0x21c, target +0x224
    float m_afEndFade[7];               // +0x22c current +0x238, target +0x240
    float m_fStartFadeTimer;            // +0x248 -1: none
    float m_fEndFadeTimer;              // +0x24c
};
static_assert(CKLightningBoltNodeFx::kClassKey == 0xa60c, "key");
DOTD_ASSERT_SIZE(CKLightningBoltNodeFx::SLevel, 0x3c);
DOTD_ASSERT_SIZE(CKLightningBoltNodeFx::SSegment, 0x64);
DOTD_ASSERT_SIZE(CKLightningBoltNodeFx::SImpactSlot, 0x10);
DOTD_ASSERT_SIZE(CKLightningBoltNodeFx, 0x250);
DOTD_ASSERT_OFFSET(CKLightningBoltNodeFx, m_pFxData, 0x14);
DOTD_ASSERT_OFFSET(CKLightningBoltNodeFx, m_unk18, 0x18);
DOTD_ASSERT_OFFSET(CKLightningBoltNodeFx, m_ui32MaxLevels, 0x1c);
DOTD_ASSERT_OFFSET(CKLightningBoltNodeFx, m_ui32NbVertices, 0x20);
DOTD_ASSERT_OFFSET(CKLightningBoltNodeFx, m_vStart, 0x30);
DOTD_ASSERT_OFFSET(CKLightningBoltNodeFx, m_fTime, 0x48);
DOTD_ASSERT_OFFSET(CKLightningBoltNodeFx, m_segments, 0x54);
DOTD_ASSERT_OFFSET(CKLightningBoltNodeFx, m_ui32NbSegments, 0x64);
DOTD_ASSERT_OFFSET(CKLightningBoltNodeFx, m_vRight, 0x74);
DOTD_ASSERT_OFFSET(CKLightningBoltNodeFx, m_aLevels, 0x90);
DOTD_ASSERT_OFFSET(CKLightningBoltNodeFx, m_ui32MaxSegments, 0x180);
DOTD_ASSERT_OFFSET(CKLightningBoltNodeFx, m_aImpacts, 0x184);
DOTD_ASSERT_OFFSET(CKLightningBoltNodeFx, m_ui32NbImpacts, 0x1d4);
DOTD_ASSERT_OFFSET(CKLightningBoltNodeFx, m_pSphere, 0x1dc);
DOTD_ASSERT_OFFSET(CKLightningBoltNodeFx, m_pDamageOwner, 0x1e0);
DOTD_ASSERT_OFFSET(CKLightningBoltNodeFx, m_pStartParticles, 0x1ec);
DOTD_ASSERT_OFFSET(CKLightningBoltNodeFx, m_pEndParticles, 0x1f0);
DOTD_ASSERT_OFFSET(CKLightningBoltNodeFx, m_fStartIntensity, 0x204);
DOTD_ASSERT_OFFSET(CKLightningBoltNodeFx, m_afStartFade, 0x210);
DOTD_ASSERT_OFFSET(CKLightningBoltNodeFx, m_afEndFade, 0x22c);
DOTD_ASSERT_OFFSET(CKLightningBoltNodeFx, m_fEndFadeTimer, 0x24c);
