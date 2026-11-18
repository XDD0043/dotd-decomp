// CKAnimatedFx.h - an animated effect (key 0xa04c, vtable 0xb300c8, size 0x60). Original unit:
// CKAnimatedFx.cpp (0x5ca148-0x5cc298). Derived straight from IKSerializable, with two virtuals of its own.
// Not in XXL2; names ours. Grouped by CKAnimatedFxCollection (0xa08c).
#pragma once
#include <cstdint>

#include "k2000/core/IKSerializable.h"
#include "k2000/core/Layout.h"
#include "k2000/math/CMatrix34.h"

class CAnimatedNode;
class CSGHotSpot;
class CSGLeaf;

// A rig an animated effect plays on (16 bytes: CKAnimatedFxCollection's entries, or a hero's rigs at +0x1070): the
// animated node, a word, two hot spots (the effect's segment ends).
struct SAnimatedFxRig {
    CAnimatedNode* m_pNode;   // +0x00
    IKSerializable* m_unk04;  // +0x04
    CSGHotSpot* m_pHotSpotA;  // +0x08
    CSGHotSpot* m_pHotSpotB;  // +0x0c
};

class CKAnimatedFx : public IKSerializable {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x281)
    int32_t IsKindOfClass(uint32_t key) override { return key == 0xa04c || key == 0xc; }  // vt+0x08 0x9cd620
    DOTD_DECLARE_FACTORIES(CKAnimatedFx)

    CKAnimatedFx() {}  // 0x005caac0 CKAnimatedFx_Create (and 0x5ca198): stores the vtable only

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x005cab58 CKAnimatedFx_Load
    // vt+0x30 0x005cab08 CKAnimatedFx_PostLoad: ResetState (vt+0x50), then 1.
    int32_t PostLoad(int32_t type) override;
    // vt+0x50 0x005ca1b8 CKAnimatedFx_ResetState_maybe: not playing, no rig owner, delay -1.
    virtual void ResetState();
    // vt+0x54 0x005ca908 CKAnimatedFx_PlayAnim_maybe: animation `index` of the dictionary (+0x04) on the rig's node from
    // `start` (no restart), the node shown.
    virtual void PlayAnim(float start, int32_t index);

    // 0x005ca828 CKAnimatedFx_Play: on a rig (with a node) while not playing: the rig reset (ResetRigTransform), the
    // animation from 0, playing with the activation pending. 1 when it started.
    int32_t Play(CSGLeaf* owner, SAnimatedFxRig* rig, CSGHotSpot* attach);
    // 0x005cbfb8 CKAnimatedFx_Update: the delay counts down, then the effects switch on (the pending activation) or the
    // segment volumes follow the hot spots; the animation advances; at its end the effect stops, and loops (+0x1c)
    // after a random delay (1 rand draw). 1 while playing.
    int32_t Update(float dt);
    // 0x005cbf48 CKAnimatedFx_Stop_maybe
    void Stop();
    // 0x005ca4d8 CKAnimatedFx_ResetRigTransform_maybe: the rig's node under the owner (or the attach hot spot), its
    // matrix reset, three random turns (3 rand draws) and the scale; with +0x34 it moves to the dynamic scene root.
    void ResetRigTransform();
    // 0x005cb080 CKAnimatedFx_SetFxActive: see the definition.
    void SetFxActive(int32_t active);
    // 0x005ca3c8 CKAnimatedFx_UpdateSegmentVolumes_maybe (Update inlines the same loop): every ribbon of the trail
    // (+0x4c) takes the rig's two hot spots' world positions as its mode-1 anchors.
    void UpdateSegmentVolumes();
    // 0x005ca2d8 CKAnimatedFx_SetOrientation_maybe: while playing on a rig node that stays under its owner (+0x34
    // clear), the node oriented along `at` / `up` (CSGMovable_SetOrientationFromAtUp, inlined through its TocBridge).
    void SetOrientation(const CVector3* at, const CVector3* up);
    // 0x005ca340 CKAnimatedFx_SetPosition: while playing on a rig node, the node's frame placed at `position` (the
    // modelling position, the identity flag 0x20000 cleared, the frame marked dirty).
    void SetPosition(const CVector3* position);

    IKSerializable* m_unk04;   // +0x04 an object reference (the animation dictionary: +4 the animation words)
    SAnimatedFxRig* m_pRig;    // +0x08 not read: the rig Play got
    float m_unk0c;             // +0x0c the animation speed
    CVector3 m_unk10;          // +0x10 three byte-swapped words read in one block (LVL010: 1.5, 1.5, 1): the rig's scale
    uint8_t m_unk1c;           // +0x1c loops
    uint8_t m_pad1d[3];
    float m_unk20;             // +0x20 the loop delay
    float m_unk24;             // +0x24 the loop delay's random part
    float m_unk28;             // +0x28 (LVL010: 359) the random turn about the rig's at axis (degrees)
    float m_unk2c;             // +0x2c the random turn about its up axis
    float m_unk30;             // +0x30 the random turn about its right axis
    uint8_t m_unk34;           // +0x34 the rig moves to the dynamic scene root
    uint8_t m_unk35;           // +0x35 read first
    uint8_t m_unk36;           // +0x36
    uint8_t m_unk37;           // +0x37
    uint8_t m_bActivatePending;  // +0x38 not read: Play sets it, Update switches the effects on and clears it
    uint8_t m_pad39[3];
    IKSerializable* m_unk3c;   // +0x3c a CKSparkFxData (with +0x35): the spark under the rig's hot spot (+0x04)
    IKSerializable* m_unk40;   // +0x40 the spark of +0x3c's data taken from the FX pool (SetFxActive; ResetState 0)
    IKSerializable* m_unk44;   // +0x44 a CKParticlesEffectFxData (with +0x36): the particles at the rig's hot spot
    IKSerializable* m_unk48;   // +0x48 the particle effect of +0x44's data taken from the pool (SetFxActive; ResetState 0)
    IKSerializable* m_unk4c;   // +0x4c a CTrailNodeFx (LVL010..120 KP3): its ribbons follow the rig's two hot spots
    uint8_t m_bPlaying;        // +0x50 not read
    uint8_t m_pad51[3];
    float m_fDelay;            // +0x54 not read: ResetState -1, Play 0; Update waits while it is above 0
    CSGLeaf* m_pOwner;         // +0x58 not read: the node the rig hangs under (Play)
    CSGHotSpot* m_pAttach;     // +0x5c not read: the hot spot the rig hangs on when its node is the owner (Play)
};
static_assert(CKAnimatedFx::kClassKey == 0xa04c, "key");
DOTD_ASSERT_SIZE(CKAnimatedFx, 0x60);
DOTD_ASSERT_SIZE(SAnimatedFxRig, 0x10);
DOTD_ASSERT_OFFSET(CKAnimatedFx, m_unk04, 0x04);
DOTD_ASSERT_OFFSET(CKAnimatedFx, m_pRig, 0x08);
DOTD_ASSERT_OFFSET(CKAnimatedFx, m_unk0c, 0x0c);
DOTD_ASSERT_OFFSET(CKAnimatedFx, m_unk10, 0x10);
DOTD_ASSERT_OFFSET(CKAnimatedFx, m_unk1c, 0x1c);
DOTD_ASSERT_OFFSET(CKAnimatedFx, m_unk20, 0x20);
DOTD_ASSERT_OFFSET(CKAnimatedFx, m_unk30, 0x30);
DOTD_ASSERT_OFFSET(CKAnimatedFx, m_unk34, 0x34);
DOTD_ASSERT_OFFSET(CKAnimatedFx, m_unk37, 0x37);
DOTD_ASSERT_OFFSET(CKAnimatedFx, m_bActivatePending, 0x38);
DOTD_ASSERT_OFFSET(CKAnimatedFx, m_unk3c, 0x3c);
DOTD_ASSERT_OFFSET(CKAnimatedFx, m_unk44, 0x44);
DOTD_ASSERT_OFFSET(CKAnimatedFx, m_unk4c, 0x4c);
DOTD_ASSERT_OFFSET(CKAnimatedFx, m_bPlaying, 0x50);
DOTD_ASSERT_OFFSET(CKAnimatedFx, m_fDelay, 0x54);
DOTD_ASSERT_OFFSET(CKAnimatedFx, m_pAttach, 0x5c);
