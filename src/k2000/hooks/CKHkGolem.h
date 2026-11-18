// CKHkGolem.h - the golem bosses' hook base (key 0x3182, vtable 0xb29260, size 0xc0). Original unit:
// CKHkGolem.cpp. No XXL2 class. Derives from CKHkActorBase; base of CKHkS08DragonCityGolem(Tail) and
// CKHkS08Malefor. Registered, but no level file holds a plain CKHkGolem.
//
// The Load reads one reference vector (+0x34) and three vectors of heap nodes (+0x58, +0x64, +0x70), each node
// holding a reference and a vector of small heap records (a word and a reference, read word first). The
// vectors grow one element at a time; every Load starts each of them with a fresh one-element block
// (BUG(original): the previous block, if any, is not freed).
//
// At run time the golem drives its phase manager (+0x30): CKHkGolem_Update updates the current phase (the attacks,
// their conditions), the boss gauge, the projectile launchers (+0x70), the attached objects (+0x2c) and, outside the
// QTE phase, the animation marks: step explosions (+0x58, channel 0x1f), particle effects (+0x64, channel 0x21) and
// the launchers' switches (+0x70, channel 0x22). The health is +0x8c of +0x88; the damage taken is counted at +0x40.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/math/CMatrix34.h"
#include "k2000/misc/CKHkActorBase.h"
#include "k2000/util/TVector.h"

class IKFx;
class IKTime;
class GolemPhaseCond;
class CKGolemPhaseManager;
class CKGolemAttackCommon;
class CSGHotSpot;
struct ContactHistoryNode;

// The records of the node vectors (::operator new, all words cleared first).
struct CKHkGolemRecord8 {      // 8 bytes (+0x58 nodes): an explosion's hot spot
    IKSerializable* m_pObject;  // +0x00 reference (read second): a CSGHotSpot
    uint32_t m_ui32Value;       // +0x04 (read first; LVL010: 0x34/0x35, kinds_maybe): the mark value - 1
};
struct CKHkGolemRecordC {      // 0xc bytes (+0x64 nodes): a particle effect's hot spot
    IKSerializable* m_pObject;  // +0x00 reference (read second): a CSGHotSpot
    uint32_t m_ui32Value;       // +0x04 (read first): the mark value - 1
    IKFx* m_unk8;               // +0x08 Load 0: the running effect (UpdateAnimMarkEvents)
};
struct CKHkGolemRecord20 {     // 0x20 bytes (+0x70 nodes): a projectile launcher's hot spot
    IKSerializable* m_pObject;  // +0x00 reference (read second): a CSGHotSpot
    uint32_t m_ui32Value;       // +0x04 (read first): the mark value - 1
    uint32_t m_unk8;            // +0x08 read after the reference (the mark switches clear it)
    float m_unkC;               // +0x0c read: the launch interval
    uint32_t m_unk10;           // +0x10 read
    float m_unk14;              // +0x14 cleared, not read: this launch's interval (0: draw a new one)
    float m_unk18;              // +0x18 cleared, not read: the time since the last launch
    uint8_t m_unk1C;            // +0x1c cleared, not read: on (channel 0x22)
    uint8_t m_pad1D[3];
};

// The nodes (::operator new; vector constructed empty with capacity 1).
struct CKHkGolemNode18 {                     // 0x18 bytes (+0x58)
    IKSerializable* m_pObject;               // +0x00 reference: the explosion's FX data (a CKExplosionFxData)
    TVector<CKHkGolemRecord8*, 1> m_records; // +0x04
    uint8_t m_unk10;                         // +0x10 read after the second reference: the explosion takes the hot
                                             // spot's matrix (else its position only)
    uint8_t m_pad11[3];
    IKSerializable* m_pObject14;             // +0x14 reference (read second): the explosion's damage (null: +0x24)
};
template <class Record>
struct CKHkGolemNode10 {                     // 0x10 bytes (+0x64, +0x70)
    IKSerializable* m_pObject;               // +0x00 reference (+0x64: a particle FX data; +0x70: a
                                             // CKProjectileAccessor)
    TVector<Record*, 1> m_records;           // +0x04
};

class CKHkGolem : public CKHkActorBase {
public:
    DOTD_CLASS_KEY(kCategoryHook, 0xc6)
    // The registry factories (0x004c0ce0 Create, 0x004be6f0 Delete, ...); LVL010 creates the derived
    // CKHkS08DragonCityGolem only.
    DOTD_DECLARE_FACTORIES(CKHkGolem)
    int32_t IsKindOfClass(uint32_t key) override {  // vt+0x08 0x9c56e8
        return key == 0x3182 || key == 0xd82 || key == 0x2 || key == 0x2fe || key == 0x3fe || key == 0xc;
    }

    // A node of the +0x2c object list (FreeListPool 0x00ceaa30 in the original; 8 bytes).
    struct ObjectNode {
        IKSerializable* m_pObject;  // +0x00 an attack (vt+0x64 each frame)
        ObjectNode* m_pNext;        // +0x04
    };

    CKHkGolem();  // 0x004bf6b8 CKHkGolem_Construct (inlined in CKHkGolem_Create 0x4c0ce0)
    ~CKHkGolem() override;  // 0x004c0850 CKHkGolem_Destructor / 0x004c09b0 CKHkGolem_BaseDestructor
    void Destroy() override;  // vt+0x10 0x004c0388 CKHkGolem_Destroy

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x004c11c0 CKHkGolem_Load
    int32_t PostLoad(int32_t type) override;  // vt+0x30 0x004bf308 CKHkGolem_PostLoad
    int32_t MessageProc(uint16_t message, void* data) override;  // vt+0x1c 0x004bf348 CKHkGolem_MessageProc
    int32_t GetInfo(IKInfo* info, int32_t request) override;      // vt+0x40 0x004c0678 CKHkGolem_GetInfo
    void Start() override;  // vt+0x50 0x004bf970 CKHkGolem_Start
    void Restart() override;  // vt+0x54 0x004bfa18 CKHkGolem_Restart
    void Stop() override;  // vt+0x68 0x004bf298 CKHkGolem_Stop
    void Update(IKTime* clock) override;  // vt+0x7c 0x004c4838 CKHkGolem_Update
    void VfA0() override;  // vt+0xa0 0x004c00c8 CKHkGolem_OnActivate
    void VfA4() override;  // vt+0xa4 0x004bfc88 CKHkGolem_OnDeactivate
    void SetEnabled(int32_t enabled) override { m_unk45 = static_cast<uint8_t>(enabled); }  // vt+0xcc 0x004bed50 SetByte45
    void VfD4(int32_t on, int32_t mode) override;  // vt+0xd4 0x004bfdf0 CKHkGolem_SetActiveWithBossGauge_maybe
    virtual void AddObject(IKSerializable* object);     // vt+0xf0 0x004bf8a0 CKHkGolem_AddObjectToList2C_maybe
    virtual void RemoveObject(IKSerializable* object);  // vt+0xf4 0x004c07c0 CKHkGolem_RemoveObjectFromList2C_maybe
    // vt+0xf8 0x009c5790 CKHkGolem_vfF8_GetAt_maybe: the reference `index` of +0x34, null past the count (the hero's
    // ability host reads Malefor's 6th; DOTD: not declared virtual, no override is known).
    IKSerializable* GetReference(uint32_t index) const {
        return m_unk34.m_ui32NbUsedElt > index ? m_unk34.m_pBlock[index] : nullptr;
    }
    // vt+0xfc 0x009c5788 CKHkGolem_vfFC_GetCount_maybe (DOTD: not virtual)
    uint32_t GetReferenceCount() const { return m_unk34.m_ui32NbUsedElt; }
    // vt+0x100 / +0x104 / +0x108 (0x9c5760 / 0x9c5768 / 0x9c5770: 0 here): the highest mark value of the step
    // explosions (channel 0x1f), the particle effects (0x21) and the launchers (0x22).
    virtual uint32_t GetMaxExplosionMark() { return 0; }
    virtual uint32_t GetMaxParticleMark() { return 0; }
    virtual uint32_t GetMaxLauncherMark() { return 0; }
    virtual void OnMark24(uint32_t /*value*/) {}        // vt+0x10c 0x9c5778 KStub_Nop (channel 0x24 on)
    virtual void OnMark24Off(uint32_t /*value*/) {}     // vt+0x110 0x9c5780 KStub_Nop (channel 0x24 off)
    virtual void ReleaseAllEntryObjects();               // vt+0x114 0x004bfb88 CKHkGolem_ReleaseAllEntryObjects_maybe
    virtual GolemPhaseCond* CreatePhaseCondition(uint32_t id);  // vt+0x118 0x004beda0 CKHkGolem_CreatePhaseCondition
    virtual void Vf11C() {}                              // vt+0x11c 0x4becf8 KStub_Nop
    // vt+0x120 0x004c31c0 CKHkGolem_ProcessContacts_maybe: the attack's volumes' contacts (CKHkS08DragonCityGolem has
    // its own; C2.8 port-rest R03 ported the base's for the other golems).
    // DOTD: the attack itself is passed (the original passes its +0x08 volume vector).
    virtual void ProcessContacts(IKTime* clock, CKGolemAttackCommon* attack);

    void LoadObjectVector(IKFile* file, int32_t type);  // 0x004c0ff0 CKHkGolem_LoadRefArray34_maybe
    CKGolemPhaseManager* PhaseManager() const;           // +0x30

    // The damage and time accessors (CKGolemPhaseQTE.cpp unit, 0x4bec68..0x4becc8).
    int32_t GetDamageTakenSinceMark() const { return m_unk40 - m_unk48; }  // 0x004bec68
    int32_t GetTotalDamageTaken() const { return m_unk40; }                // 0x004bec80
    void MarkDamageTaken() { m_unk48 = m_unk40; }                          // 0x004bec88
    float GetTime50() const { return m_fUnk50; }                           // 0x004becb0
    float GetTime54() const { return m_fUnk54; }                           // 0x004becb8
    void SetTime54ToNow();                                                 // 0x004bf9f8
    // 0x004becc8 CKHkGolem_ApplyDamagePoints_maybe: the damage counted, the health lowered (not below 0).
    void ApplyDamagePoints(int32_t points);
    float GetHealthPercent() const;      // 0x004bed00 CKHkGolem_GetHealthPercent_maybe
    int32_t GetHealthPercentInt() const; // 0x004c0c80 CKHkGolem_GetHealthPercentInt_maybe

    void SpawnBonuses(const CVector3* position, const CVector3* direction);  // 0x004bed58
    void SpawnFxAt(const CVector3* position, const CVector3* direction);     // 0x004c2758
    void UpdateProjectileLaunchers(IKTime* clock);                           // 0x004befc0
    void TriggerStepExplosions(uint32_t value);                              // 0x004c2288
    void UpdateAnimMarkEvents();                                             // 0x004c3998
    // 0x004c2dc8 CKHkGolem_SpawnContactParticleFx_maybe (ProcessContacts): the particle data +0x80 at `point` along
    // `direction` (normalised in place) at the hot spot of the hit volume.
    void SpawnContactParticleFx(CSGHotSpot* hotSpot, const CVector3* point, CVector3* direction);

    ContactHistoryNode* m_unk20;                            // +0x20 constructor 0: the contacts (ContactHistory)
    IKSerializable* m_unk24;                                // +0x24 reference: the step explosions' default damage
    IKSerializable* m_unk28;                                // +0x28 reference: the bonus table (SpawnBonuses)
    ObjectNode* m_unk2C;                                    // +0x2c constructor 0: the attached objects
    IKSerializable* m_unk30;                                // +0x30 reference (read first): the phase manager
    TVector<IKSerializable*, 1> m_unk34;                    // +0x34 references
    int32_t m_unk40;                                        // +0x40 runtime (Start: 0): the damage taken
    uint8_t m_unk44;                                        // +0x44 runtime (Start: 0): the boss fight runs
    uint8_t m_unk45;                                        // +0x45 runtime (Start: 1): updated
    uint8_t m_pad46[2];
    int32_t m_unk48;                                        // +0x48 runtime (Start: 0): the damage mark
    int32_t m_unk4C;                                        // +0x4c runtime: the damage taken at the frame's start
    float m_fUnk50;                                         // +0x50 runtime (Start: the game time)
    float m_fUnk54;                                         // +0x54 runtime (Start: the game time)
    TVector<CKHkGolemNode18*, 1> m_unk58;                   // +0x58
    TVector<CKHkGolemNode10<CKHkGolemRecordC>*, 1> m_unk64;  // +0x64
    TVector<CKHkGolemNode10<CKHkGolemRecord20>*, 1> m_unk70; // +0x70
    IKSerializable* m_unk7C;                                // +0x7c reference: the hit explosion's FX data (SpawnFxAt)
    IKSerializable* m_unk80;                                // +0x80 reference
    CMatrix34* m_pUnk84;                                    // +0x84 PostLoad: RwMatrixCreate (OnActivate: the node's
                                                            // matrix; Restart / OnDeactivate put it back)
    int32_t m_unk88;                                        // +0x88 (LVL050: 1000): the maximum health
    int32_t m_unk8C;                                        // +0x8c the health
    uint8_t m_unk90;                                        // +0x90 the boss gauge shows the health
    uint8_t m_pad91[3];
    float m_af94[10];                                       // +0x94 (LVL010/120: 1.0, 0.7, 0.4, ...): the damage
                                                            // factors per damage kind (CKHkS08DragonCityGolem)
    IKSerializable* m_unkBC;                                // +0xbc reference (read before +0x94): a CKMarkedFX
};
DOTD_ASSERT_SIZE(CKHkGolem, 0xc0);
DOTD_ASSERT_OFFSET(CKHkGolem, m_unk20, 0x20);
DOTD_ASSERT_OFFSET(CKHkGolem, m_unk24, 0x24);
DOTD_ASSERT_OFFSET(CKHkGolem, m_unk30, 0x30);
DOTD_ASSERT_OFFSET(CKHkGolem, m_unk34, 0x34);
DOTD_ASSERT_OFFSET(CKHkGolem, m_unk58, 0x58);
DOTD_ASSERT_OFFSET(CKHkGolem, m_unk64, 0x64);
DOTD_ASSERT_OFFSET(CKHkGolem, m_unk70, 0x70);
DOTD_ASSERT_OFFSET(CKHkGolem, m_unk7C, 0x7c);
DOTD_ASSERT_OFFSET(CKHkGolem, m_pUnk84, 0x84);
DOTD_ASSERT_OFFSET(CKHkGolem, m_unk88, 0x88);
DOTD_ASSERT_OFFSET(CKHkGolem, m_unk90, 0x90);
DOTD_ASSERT_OFFSET(CKHkGolem, m_af94, 0x94);
DOTD_ASSERT_OFFSET(CKHkGolem, m_unkBC, 0xbc);
DOTD_ASSERT_SIZE(CKHkGolemRecord20, 0x20);
DOTD_ASSERT_SIZE(CKHkGolemNode18, 0x18);

// The frame clock's game time (g_pEngine +0x48 -> +0x04 -> +0x04), the golem classes' "now".
float GolemClockTime();
