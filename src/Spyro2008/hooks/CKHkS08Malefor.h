// CKHkS08Malefor.h - Malefor's hook (key 0x3502, vtable 0xb2a660, size 0x1d4). Original unit:
// CKHkS08Malefor.cpp. No XXL2 class. Derives from CKHkGolem. Values in the comments: LVL120.
//
// C2.8 port-last Z6: the runtime. Malefor has a "weak" state (+0x168, messages 0x99e / 0x99f): his collision volume
// (+0x164, owned by him, radius 5 at PostLoad / Start) is on, the node +0x178 shown, an explosion (+0x174 on, +0x17c
// off) marks the change. The heroes' damage volumes touching that volume or the current attack's volumes hurt him
// (ProcessDamageContacts, vt+0x120): one-shot damages once per contact (the contact histories +0x20 and +0xc0), the
// continuous ones kept per dragon (+0xc4 / +0xc8) and applied each frame (ApplyPendingDamage). The damage is scaled by
// the element kind's factor (weak: +0x19c.., else the golem's +0x94..) and gathered per dragon (+0xcc / +0xd0) until a
// whole point is reached. Two particle nodes (+0xe4 / +0xe8) emit from hot spots once the health is at or below +0xfc,
// more as it drops, and the node +0x178 is scaled (and the volume's radius with it) by the health percentage.
// The animation channel 0x24 (vt+0x10c / +0x110) switches the ribbons of two trail effects (+0x18c / +0x190: CTrailNodeFx,
// two ribbons each, laid out across the hot spots 12 / 13 when switched on).
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/hooks/CKHkGolem.h"

class CKS08Damage;
class CKGolemAttackCommon;
class CNode;
class CParticlesNodeFx;
class CTrailNodeFx;
class IKBoundingVolume;

class CKHkS08Malefor : public CKHkGolem {
public:
    DOTD_CLASS_KEY(kCategoryHook, 0xd4)
    int32_t IsKindOfClass(uint32_t key) override {  // vt+0x08 0x9c63f8
        return key == 0x3502 || key == 0x3182 || key == 0xd82 || key == 0x2 || key == 0x2fe || key == 0x3fe ||
               key == 0xc;
    }
    DOTD_DECLARE_FACTORIES(CKHkS08Malefor)

    // 0x004e2860 CKHkS08Malefor_Construct (inlined in CKHkS08Malefor_Create 0x4e3070): +0xc0 = 0.
    CKHkS08Malefor() { m_unkC0 = nullptr; }
    // 0x004e2e60 CKHkS08Malefor_Destructor (0x004e2dd8 the deleting one): the contacts (+0xc0) back to their pool
    // (ContactHistory_FreeNode), the list cleared, then CKHkGolem's.
    ~CKHkS08Malefor() override;

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x004e3eb8 CKHkS08Malefor_Load
    // vt+0x30 0x004e3198 CKHkS08Malefor_PostLoad: CKHkGolem's; a level load sets the collision volume up (owned by
    // Malefor, owner type 1, flag 0x80 of its infos, radius 5.0). Returns 0.
    int32_t PostLoad(int32_t type) override;
    // vt+0x10 0x004e2760 CKHkS08Malefor_Destroy: CKHkGolem's, then the +0xf0 array freed and cleared.
    void Destroy() override;
    // vt+0x1c 0x004e2c48 CKHkS08Malefor_MessageProc: CKHkGolem's answer merged with 0x99e / 0x99f (weak on / off),
    // 0x9a0 / 0x9a1 (while weak, the node +0x178 shown / hidden).
    int32_t MessageProc(uint16_t message, void* data) override;
    // vt+0x40 0x004e2080 CKHkS08Malefor_GetInfo: CKHkGolem's answer kept as 2, else 1 when not 0.
    int32_t GetInfo(IKInfo* info, int32_t request) override;
    void Start() override;                  // vt+0x50 0x004e30d0 CKHkS08Malefor_Start
    void Restart() override;                // vt+0x54 0x004e2ed8 CKHkS08Malefor_Restart
    void Update(IKTime* clock) override;    // vt+0x7c 0x004e75d8 CKHkS08Malefor_Update
    void VfA0() override;                   // vt+0xa0 0x004e2ad8 CKHkS08Malefor_OnActivate
    void VfA4() override;                   // vt+0xa4 0x004e29e8 CKHkS08Malefor_OnDeactivate
    uint32_t GetMaxExplosionMark() override { return 9; }   // vt+0x100 0x004e1620 CKHkS08Malefor_vf100
    uint32_t GetMaxParticleMark() override { return 12; }   // vt+0x104 0x004e1628 CKHkS08Malefor_vf104
    uint32_t GetMaxLauncherMark() override { return 0; }    // vt+0x108 0x004e1630 CKHkS08Malefor_vf108
    // vt+0x10c 0x004e6570 CKHkS08Malefor_vf10C / vt+0x110 0x004e6560 CKHkS08Malefor_vf110: the channel 0x24's value on /
    // off: SetTrailRibbonsActive(1 / 0, value).
    void OnMark24(uint32_t value) override { SetTrailRibbonsActive(1, value); }
    void OnMark24Off(uint32_t value) override { SetTrailRibbonsActive(0, value); }
    // vt+0x114 0x004e1d28 CKHkS08Malefor_vf114: CKHkGolem's, then vt+0x110 with 3 (every trail ribbon off).
    void ReleaseAllEntryObjects() override;
    // vt+0x11c 0x004e1638 (empty), Resume / Pause / Stop / RecursiveRegistration (0x4e2698 .. 0x4e26e8, 0x4e2738): CKHkGolem's.
    // vt+0x120 0x004e3248 CKHkS08Malefor_ProcessDamageContacts_maybe (DOTD: the attack itself, as CKHkGolem's slot).
    void ProcessContacts(IKTime* clock, CKGolemAttackCommon* attack) override;

    // 0x004e17d8 CKHkS08Malefor_AccumulateDamage_maybe (weak) / 0x004e1a80 CKHkS08Malefor_AccumulateDamage_2_maybe: `amount`
    // scaled by the damage's kind into dragon `slot`'s pending damage; its whole part, when there is one, is applied.
    void AccumulateWeakDamage(float amount, CKS08Damage* damage, uint32_t slot);
    void AccumulateDamage(float amount, CKS08Damage* damage, uint32_t slot);
    // 0x004e1d80 CKHkS08Malefor_UpdateHotSpotSegmentVolumes_maybe: the trails' fixed anchors across the hot spots 12 / 13.
    void UpdateTrailAnchors();
    // 0x004e2190 CKHkS08Malefor_TriggerHotSpotExplosionFx_maybe: an explosion of `data` triggered where it is.
    void TriggerExplosion(IKSerializable* data);
    // 0x004e2270 CKHkS08Malefor_SpawnDamageImpactFx_maybe: the impact explosion of the damage's element kind (+0x110..),
    // else the golem's hit explosion.
    void SpawnDamageImpactFx(const CVector3* position, const CVector3* direction, CKS08Damage* damage);
    // 0x004e2510 CKHkS08Malefor_SetCollisionActive_maybe: the weak state on / off.
    void SetWeak(uint8_t on);
    // 0x004e54d0 CKHkS08Malefor_UpdateCollisionVolumesFromBones_maybe: the trails' ribbons on / off (value 1: +0x18c,
    // 2: +0x190, 3: both).
    void SetTrailRibbonsActive(int32_t on, uint32_t value);
    // 0x004e6580 CKHkS08Malefor_SpawnElementHitFx_maybe: the element kind's hit explosion (+0x140.., kind 4: +0x120) at the
    // hot spot 6.
    void SpawnElementHitFx(CKS08Damage* damage);
    // 0x004e6fd8 CKHkS08Malefor_ApplyPendingDamage_maybe: the dragons' continuous damages of this frame.
    void ApplyPendingDamage(IKTime* clock);

    struct ContactHistoryNode* m_unkC0;  // +0xc0 constructor 0: the contacts of the damages with +0x26 set
    CKS08Damage* m_apUnkC4[2];          // +0xc4 runtime: each dragon's continuous damage this frame
    float m_afUnkCC[2];                 // +0xcc runtime: each dragon's pending damage (below one point)
    uint8_t m_abUnkD4[2];               // +0xd4 runtime: each dragon's continuous damage runs
    uint8_t m_padD6[2];
    float m_afUnkD8[2];                 // +0xd8 runtime: each dragon's time since its last hit count
    float m_unkE0;                      // +0xe0 (0.5) the hit count interval of a continuous damage
    CParticlesNodeFx* m_unkE4;          // +0xe4 reference (read first): emits from the +0xf0 hot spots
    CParticlesNodeFx* m_unkE8;          // +0xe8 reference: emits from the +0xf4 hot spots
    uint8_t m_unkEC;                    // +0xec the +0xf0 count (12)
    uint8_t m_padED[3];
    IKSerializable** m_apUnkF0;         // +0xf0 m_unkEC references (Mem_AllocAligned16): CSGHotSpot
    IKSerializable* m_apUnkF4[2];       // +0xf4 two references (one array read): CSGHotSpot
    // +0xfc (0, 1, 10, 1, 10): [0] the health at or below which the particle nodes emit (a signed word); the particles
    // per point of +0xe4 from [1] (full health) to [2] (none), of +0xe8 from [3] to [4].
    uint32_t m_unkFC[5];
    IKSerializable* m_apUnk110[9];      // +0x110 references: the impact explosions by element kind (8 / 9: [8])
    // +0x134 never written (BUG(original): Load skips it; the fresh heap's value): the hit effect interval;
    // +0x138 / +0x13c runtime: each dragon's time toward it.
    float m_afUnk134[3];
    IKSerializable* m_apUnk140[9];      // +0x140 references: the hit explosions by element kind (8 / 9: [8])
    IKBoundingVolume* m_unk164;         // +0x164 reference: the weak state's collision volume (PostLoad configures it)
    uint8_t m_unk168;                   // +0x168 runtime: weak
    uint8_t m_pad169[3];
    uint32_t m_unk16C;                  // +0x16c (75) the fury of a one-shot hit while weak
    uint32_t m_unk170;                  // +0x170 (50) the fury of a continuous damage's hit count while weak
    IKSerializable* m_unk174;           // +0x174 reference: the explosion when weak starts
    CNode* m_pUnk178;                   // +0x178 reference: the node shown while weak, scaled by the health
    IKSerializable* m_unk17C;           // +0x17c reference: the explosion when weak ends
    IKSerializable* m_unk180;           // +0x180 reference: the explosion of a one-shot hit on the weak volume
    IKSerializable* m_unk184;           // +0x184 reference: the hit explosion while weak
    IKSerializable* m_unk188;           // +0x188 reference: the hit explosion while weak (element kinds 8 / 9)
    CTrailNodeFx* m_unk18C;             // +0x18c reference: a trail (ribbons 0 / 1 across the hot spot 12)
    CTrailNodeFx* m_unk190;             // +0x190 reference: a trail (ribbons 0 / 1 across the hot spot 13)
    // +0x194 floats: [0] / [1] the ribbons' widths; [2..10] the weak damage factors (element kinds 0..7, then a hero
    // damage); [11] / [12] the health percentages between which the node +0x178 scales from [13] to [14]; [15] the
    // volume's radius per unit of scale.
    float m_afUnk194[16];
};
DOTD_ASSERT_SIZE(CKHkS08Malefor, 0x1d4);
DOTD_ASSERT_OFFSET(CKHkS08Malefor, m_unkC0, 0xc0);
DOTD_ASSERT_OFFSET(CKHkS08Malefor, m_apUnkC4, 0xc4);
DOTD_ASSERT_OFFSET(CKHkS08Malefor, m_afUnkCC, 0xcc);
DOTD_ASSERT_OFFSET(CKHkS08Malefor, m_abUnkD4, 0xd4);
DOTD_ASSERT_OFFSET(CKHkS08Malefor, m_afUnkD8, 0xd8);
DOTD_ASSERT_OFFSET(CKHkS08Malefor, m_unkE0, 0xe0);
DOTD_ASSERT_OFFSET(CKHkS08Malefor, m_unkEC, 0xec);
DOTD_ASSERT_OFFSET(CKHkS08Malefor, m_apUnkF0, 0xf0);
DOTD_ASSERT_OFFSET(CKHkS08Malefor, m_apUnkF4, 0xf4);
DOTD_ASSERT_OFFSET(CKHkS08Malefor, m_unkFC, 0xfc);
DOTD_ASSERT_OFFSET(CKHkS08Malefor, m_apUnk110, 0x110);
DOTD_ASSERT_OFFSET(CKHkS08Malefor, m_afUnk134, 0x134);
DOTD_ASSERT_OFFSET(CKHkS08Malefor, m_apUnk140, 0x140);
DOTD_ASSERT_OFFSET(CKHkS08Malefor, m_unk164, 0x164);
DOTD_ASSERT_OFFSET(CKHkS08Malefor, m_unk168, 0x168);
DOTD_ASSERT_OFFSET(CKHkS08Malefor, m_unk16C, 0x16c);
DOTD_ASSERT_OFFSET(CKHkS08Malefor, m_unk174, 0x174);
DOTD_ASSERT_OFFSET(CKHkS08Malefor, m_pUnk178, 0x178);
DOTD_ASSERT_OFFSET(CKHkS08Malefor, m_unk184, 0x184);
DOTD_ASSERT_OFFSET(CKHkS08Malefor, m_unk188, 0x188);
DOTD_ASSERT_OFFSET(CKHkS08Malefor, m_unk190, 0x190);
DOTD_ASSERT_OFFSET(CKHkS08Malefor, m_afUnk194, 0x194);
