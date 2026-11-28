// CKGrpS08Enemy.h - DotD's enemy group (key 0xa44, vtable 0xb215f8, size 0x290). Original unit:
// CKGrpS08Enemy.cpp (Spyro2008/groups/CKGrpS08Enemy_2.cpp: 0x269118 Load, 0x267630 Create). No XXL2 class
// of this name; the names are placeholders (reference classes from the LVL010 live dump, _maybe).
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/math/CMatrix34.h"
#include "k2000/misc/IKGrpEnemy.h"
#include "k2000/services/CTriggerStarter.h"
#include "k2000/util/TVector.h"

class CKGrpS08Enemy : public IKGrpEnemy {
public:
    DOTD_CLASS_KEY(kCategoryGroup, 0x29)
    int32_t IsKindOfClass(uint32_t key) override {  // vt+0x08 0x9bb468
        return key == 0xa44 || key == 0x9c4 || key == 0x4 || key == 0x17e || key == 0x2fe || key == 0x3fe || key == 0xc;
    }
    DOTD_DECLARE_FACTORIES(CKGrpS08Enemy)

    // Three floats and a count: the Load pushes 1, 2, 3 at the count, then reads the three floats over them.
    struct SFloat3List {
        float m_af[3];         // +0x00
        uint32_t m_ui32NbElt;  // +0x0c
    };

    // 0x00267630 CKGrpS08Enemy_Create (after the IKGrpEnemy constructor), in its order.
    CKGrpS08Enemy() {
        m_vUnk164 = {nullptr, 1, 0};
        m_vUnk180 = {nullptr, 1, 0};
        m_vUnk19c = {nullptr, 1, 0};
        m_vUnk1b0 = {nullptr, 1, 0};
        m_aFloat3Lists[3].m_ui32NbElt = 0;
        m_aFloat3Lists[0].m_ui32NbElt = 0;
        m_aFloat3Lists[1].m_ui32NbElt = 0;
        m_aFloat3Lists[2].m_ui32NbElt = 0;
    }

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x00269118 CKGrpS08Enemy_Load
    void Start() override;                              // vt+0x50 0x00268eb8 CKGrpS08Enemy_Start (C2.2)
    // vt+0x68 0x00267478 CKGrpS08Enemy_Stop: IKGrpEnemy's (empty), then the accessory manager's (+0x1ec) flying
    // accessories cleared (vt+0x58 ClearAccessories). vt+0x10 0x00267568 CKGrpS08Enemy_Destroy is IKGrpEnemy's.
    void Stop() override;
    void Restart() override;                            // vt+0x54 0x00268d28 CKGrpS08Enemy_Restart
    int32_t PostLoad(int32_t type) override;            // vt+0x30 0x00267a68 CKGrpS08Enemy_PostLoad
    // 0x00266ea0 CKGrpS08Enemy_CountGroundedWeapons_maybe: the weapons of the weapon group (+0x190) on the ground
    // (+0xab); the list is walked again from its head for every member, as the original does.
    uint32_t CountGroundedWeapons();
    uint8_t GetNbAnimLayers(uint8_t kind) override;                      // vt+0x108 0x009bb4f8
    uint8_t GetNbTrailNodes(uint8_t kind) override;                      // vt+0x128 0x009bb570
    uint8_t GetNbAnimLayerSlots(uint8_t kind, uint8_t layer) override;   // vt+0x130 0x009bb590
    // vt+0xec 0x009bb648 CKGrpS08Enemy_vfEC: a zone component is current and +0x178 bit 0.
    uint8_t IsInFight() override { return m_pFightZoneCpnt170 != nullptr ? static_cast<uint8_t>(m_ui32FightFlags & 1u) : 0; }
    // vt+0xf0 0x009bb668 CKGrpS08Enemy_vfF0: a zone component is current and +0x178 bit 1 ("a fight is on").
    uint8_t IsFightOn() override { return m_pFightZoneCpnt170 != nullptr ? static_cast<uint8_t>((m_ui32FightFlags >> 1) & 1u) : 0; }
    uint8_t GetNbEnemyKinds() override { return 9; }   // vt+0xf4 0x009bb4e0
    uint8_t GetSpawnFlagBits() override { return 2; }  // vt+0x158 0x009bb608
    // vt+0x150 0x00266dd0 CKGrpS08Enemy_vf150: every enemy may change squads (CKGrpFightZone_TransferEnemyToSquad_maybe);
    // the only enemy group of DotD, so not declared in IKGrpEnemy.
    uint8_t CanTransferEnemy(IKSerializable* /*enemy*/) { return 1; }
    void SetCurrentFightZone(CKGrpFightZone* zone) override;    // vt+0x15c 0x00267cb8 CKGrpS08Enemy_vf15C
    // port-all P22:
    // vt+0x1c 0x00267ff8 CKGrpS08Enemy_MessageProc: 0x1305 / 0x1306 / 0x1309 +0x178 bits 0 / 1 / 3 (the message byte
    // or'ed in), 0x1307 +0x174, 0x940 / 0x1000 / 0x1001 known; then IKGrpEnemy's (the beacons' save / load).
    int32_t MessageProc(uint16_t message, void* data) override;
    // vt+0x24 0x002674f8 CKGrpS08Enemy_RecursiveRegistration: IKGrpEnemy's (IKGroup's), then +0x1e4's.
    void RecursiveRegistration(int32_t type) override;
    // vt+0x40 0x00267f10 CKGrpS08Enemy_GetInfo: 0x64 in a fight (byte), 0x65 a fight on (byte), 0x66 0 (byte), 0x67 the
    // active enemy count (+0x120, an integer).
    int32_t GetInfo(IKInfo* info, int32_t request) override;
    static uint32_t InfoInFight(IKSerializable* self, uint32_t arg);       // 0x009bb628 CKGrpS08Enemy_GetTriggerProp64
    static uint32_t InfoFightOn(IKSerializable* self, uint32_t arg);       // 0x009bb688 CKGrpS08Enemy_GetTriggerProp65
    static uint32_t InfoZero(IKSerializable* self, uint32_t arg);          // 0x009bb6a8 KStub_Return0_9bb6a8
    static uint32_t InfoActiveEnemies(IKSerializable* self, uint32_t arg); // 0x009bb618 CKGrpS08Enemy_GetTriggerProp67
    // vt+0xa8 0x00265b78 CKGrpS08Enemy_vfA8 / vt+0xac 0x00265cc0 vfAC (OnLock / OnUnlock): every fight zone sector
    // group (+0x34, from the first) locked / unlocked (SetObjectLocked 0x1c250).
    void OnLock() override;
    void OnUnlock() override;
    // vt+0x70 0x00266db8 / vt+0x78 0x00266dc0 CKGrpS08Enemy_Pause / Resume: empty (IKBaseGroup's). vt+0xb8 0x00266dc8
    // CKGrpS08Enemy_vfB8 returns 1: IKBaseGroup models no slot there and no ported code calls it.
    // vt+0xf8 / +0xfc / +0x100 0x00266d70 / 0x00266d88 / 0x00266da0: a word per enemy kind (0..8; tables 0x00a6ffcc
    // 0x9b, 0x00a6fff0 0x906, 0x00a70014 0x2d for every kind). BUG(original): no bound checks.
    uint32_t GetKindTableF8(uint32_t /*kind*/) const { return 0x9b; }
    uint32_t GetKindTableFC(uint32_t /*kind*/) const { return 0x906; }
    uint32_t GetKindTable100(uint32_t /*kind*/) const { return 0x2d; }
    // 0x00267950 CKS08FightZoneCpnt_RemoveCristalOrb_maybe (the enemy group's, CKHkS08CristalOrb_Stop): `orb` out of
    // +0x1b0 (the last one takes its place).
    void RemoveCristalOrb(IKSerializable* orb);
    // vt+0x168 0x00267368 / vt+0x16c 0x00268be0 / vt+0x170 0x00268fe0: the save record (0x38 bytes: IKGrpEnemy's, then
    // the floats +0x28, +0x30, +0x34, +0x2c).
    void* AllocSaveRecord() override;
    void SaveRecord(IKFile* file, void* unused, void* record) override;
    void LoadRecord(IKFile* file, void* unused, void* record) override;
    void ClearCurrentFightZone(CKGrpFightZone* zone) override;  // vt+0x160 0x002681d0 CKGrpS08Enemy_vf160
    void Update(IKTime* clock) override;                        // vt+0x7c 0x002683a0 UpdateCKGrpS08Enemy
    // 0x002679f0 CKS08FightZoneCpnt_CompleteObjective_maybe (in this unit): the trigger starter +0x134 fired; the current
    // zone (if any) marked completed and the checkpoint snapshot taken; +0x1bc cleared.
    void CompleteObjective();
    // vt+0x14c 0x00267d68 CKGrpS08Enemy_GetHeroMatrix: a hero's node frame matrix (0: the first controlled hero, 1 and 2:
    // the dragons 0 and 1) with its targeting position, into `out`.
    void GetHeroMatrix(uint8_t hero, CMatrix34* out);
    // 0x00268178 CKGrpS08Enemy_SignalAlert_maybe: the group's trigger 3 (+0x13c) and the current fight zone's trigger 9
    // (+0xf4) queued (a member saw a hero).
    void SignalAlert();
    // 0x00267090 CKGrpS08Enemy_SignalEnemyHit_maybe: the group's trigger 4 (+0x144) queued (a member took a hit).
    void SignalEnemyHit() { QueueTriggerSignals(&m_aTriggers[4]); }
    // vt+0x184 / +0x188 / +0x18c / +0x190 0x00267770 / 0x00267740 / 0x00267710 / 0x002676e0 CKGrpS08Enemy_vf184 / vf188 /
    // vf18C / vf190: the value of element level `level` in the list +0x1f8 / +0x208 / +0x218 / +0x228 (the held element
    // hit FX interval's divisor, CKHkS08Enemy_ApplyPendingDamage): level n reads +0x1f4 + 4n of the list, level 0 the
    // level 1 value. Not virtual here: no class derives from CKGrpS08Enemy. GetElementLevel gives at most 3.
    float GetElementLevelValue(uint32_t list, uint8_t level) const {
        return m_aFloat3Lists[list].m_af[level == 0 ? 0 : level - 1];
    }
    // vt+0x164 0x00267220 CKGrpS08Enemy_vf164: with a member and a current zone component, the component's empty slot
    // KStub_Return0 0x274ae0 (nothing).
    void ReleaseAttackSlotOf(IKSerializable* /*member*/) {}
    // The attack slots: +0x154 the reserved total, +0x158 + 4 x category the reserved per category (three), +0x164 the
    // holders; the limits are the current fight zone component's +0x20 (total) and +0x24 + 4 x category.
    uint8_t CanReserveAttackSlot(int32_t category);                  // 0x00267848 CKGrpS08Enemy_CanReserveAttackSlot_maybe
    void ReserveAttackSlot(int32_t category, IKSerializable* enemy);  // 0x00267260 CKGrpS08Enemy_ReserveAttackSlot_maybe
    void ReleaseAttackSlot(int32_t category, IKSerializable* enemy);  // 0x00267138 CKGrpS08Enemy_ReleaseAttackSlot
    // 0x00268a60 CKGrpS08Enemy_ReleaseAttackSlotOfType_maybe: the newest holder whose attack is of `category` gives its slot
    // up (its reservation cleared, taken out of the holders, the counts lowered).
    void ReleaseAttackSlotOfType(int32_t category);
    // vt+0x178 0x00266dd8 CKGrpS08Enemy_vf178: dragon 0's (+0x14c) or another's (+0x150) attack timer is over (<= 0).
    uint8_t IsAttackCooldownOver(uint8_t dragon) const {
        return (dragon == 0 ? m_fAttackCooldownSpyro : m_fAttackCooldownCynder) <= 0.0f ? 1 : 0;
    }
    void MoveAttackerToBack(IKSerializable* enemy);  // vt+0x180 0x00268738 CKGrpS08Enemy_MoveAttackerToBack_maybe
    // vt+0x17c 0x00268898 CKGrpS08Enemy_StartAttackCooldownAndRequeue_maybe: the hero's attack timer (+0x14c for dragon
    // 0 while over, else +0x150 while over) restarted from the current fight zone's +0x18 / +0x1c, and `enemy` moved to
    // the back of the slot holders (MoveAttackerToBack).
    void StartAttackCooldown(uint8_t dragon, IKSerializable* enemy);

    CTriggerStarter m_aTriggers[5];       // +0x124 Ghidra aEvt124; loaded from the first to the last
    float m_fAttackCooldownSpyro;                       // +0x14c a timer counted down by Update (vf15C: 0)
    float m_fAttackCooldownCynder;                       // +0x150 a timer counted down by Update (vf15C: 0)
    uint32_t m_ui32ReservedAttackSlotsTotal;                    // +0x154 Update: non-zero keeps the fight on
    uint32_t m_unk158;                    // +0x158
    uint32_t m_unk15c;                    // +0x15c
    uint32_t m_unk160;                    // +0x160
    TVector<IKSerializable*, 1> m_vUnk164;  // +0x164 the attack slots' holders (enemies); not loaded
    IKSerializable* m_pFightZoneCpnt170;  // +0x170 the current fight zone's CKS08FightZoneCpnt (vf15C)
    uint8_t m_unk174;                     // +0x174 vf15C clears it
    uint8_t m_pad175[3];
    uint32_t m_ui32FightFlags;                    // +0x178 bit 0: in a fight (vf15C), bit 1: a fight is on (Update), bit 2
    IKSerializable* m_pUnk17c;            // +0x17c reference (LVL010: a CKCommonBaseGroup)
    TVector<IKSerializable*, 1> m_vUnk180;  // +0x180 references, at most 9 kept
    uint32_t m_unk18c;                    // +0x18c
    IKSerializable* m_pWeaponPool;            // +0x190 reference (LVL010: a CKGrpS08WeaponPool)
    uint32_t m_unk194;                    // +0x194
    IKSerializable* m_pShieldGroupRoot;            // +0x198 reference (LVL010: a CKCommonBaseGroup)
    TVector<IKSerializable*, 1> m_vUnk19c;  // +0x19c the Load only gives it a block; PostLoad: +0x198's children after the first
    float m_unk1a8;                       // +0x1a8
    IKSerializable* m_pShieldPool;            // +0x1ac (LVL010: a CKGrpS08ShieldPool; not loaded): PostLoad, +0x198's first child
    TVector<IKSerializable*, 1> m_vUnk1b0;  // +0x1b0 not loaded: the cristal orbs (RemoveCristalOrb)
    uint8_t m_bAlerted;                     // +0x1bc a byte (Start clears it); non-zero keeps the fight on (Update)
    uint8_t m_pad1bd[3];
    uint32_t m_unk1c0[4];                 // +0x1c0..+0x1cc
    uint32_t m_unk1d0[3];                 // +0x1d0..+0x1d8
    uint32_t m_unk1dc;                    // +0x1dc
    float m_unk1e0;                       // +0x1e0 Start: 20.0f (TOC 0x518)
    IKSerializable* m_pQuakeLauncher;            // +0x1e4 reference (LVL010: a CKQuakeCameraLauncher)
    uint8_t m_bAlertedThisFrame;                     // +0x1e8 Update: non-zero keeps the fight on; cleared every frame
    uint8_t m_pad1e9[3];
    IKSerializable* m_pAccessoryManager;            // +0x1ec reference (LVL010: a CKS08AccessoryManager)
    float m_unk1f0;                       // +0x1f0 Start: 0.3f (TOC 0x51c)
    uint32_t m_unk1f4;                    // +0x1f4
    SFloat3List m_aFloat3Lists[4];        // +0x1f8 / +0x208 / +0x218 / +0x228
    float m_unk238[11];                   // +0x238..+0x260
    IKSerializable* m_pCameraEventCpnt;            // +0x264 reference (LVL010: a CKCameraEventCpnt)
    float m_unk268[10];                   // +0x268..+0x28c
};
static_assert(CKGrpS08Enemy::kClassKey == 0xa44, "key");
DOTD_ASSERT_SIZE(CKGrpS08Enemy, 0x290);
DOTD_ASSERT_OFFSET(CKGrpS08Enemy, m_aTriggers, 0x124);
DOTD_ASSERT_OFFSET(CKGrpS08Enemy, m_vUnk164, 0x164);
DOTD_ASSERT_OFFSET(CKGrpS08Enemy, m_pUnk17c, 0x17c);
DOTD_ASSERT_OFFSET(CKGrpS08Enemy, m_vUnk180, 0x180);
DOTD_ASSERT_OFFSET(CKGrpS08Enemy, m_pWeaponPool, 0x190);
DOTD_ASSERT_OFFSET(CKGrpS08Enemy, m_unk194, 0x194);
DOTD_ASSERT_OFFSET(CKGrpS08Enemy, m_pShieldGroupRoot, 0x198);
DOTD_ASSERT_OFFSET(CKGrpS08Enemy, m_vUnk19c, 0x19c);
DOTD_ASSERT_OFFSET(CKGrpS08Enemy, m_vUnk1b0, 0x1b0);
DOTD_ASSERT_OFFSET(CKGrpS08Enemy, m_pQuakeLauncher, 0x1e4);
DOTD_ASSERT_OFFSET(CKGrpS08Enemy, m_pAccessoryManager, 0x1ec);
DOTD_ASSERT_OFFSET(CKGrpS08Enemy, m_aFloat3Lists, 0x1f8);
DOTD_ASSERT_OFFSET(CKGrpS08Enemy, m_unk238, 0x238);
DOTD_ASSERT_OFFSET(CKGrpS08Enemy, m_pCameraEventCpnt, 0x264);
DOTD_ASSERT_OFFSET(CKGrpS08Enemy, m_unk268, 0x268);
