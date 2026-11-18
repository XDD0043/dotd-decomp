// CKGolemAttackCommon.h - a boss attack description (key 0x994c, vtable 0xb28fc0, size 0x98). Original unit:
// CKGolemAttackCommon.cpp (0x4b7728-0x4ba5a0). No XXL2 class of this name: the members keep placeholder
// names. Derives from KBase984C (Ghidra: CKGolemAttackBase_maybe); base of the Malefor attacks
// (CKS08MaleforBigBombDeathBall, CKS08MaleforColdBall, CKS08MaleforFireBreath). Two inlined growable arrays
// (data, capacity, count) at +0x08 (the attack's damage volumes) and +0x6c (timed triggers).
//
// The phase (CKGolemPhaseAttack) gives the attack its step's two condition lists (vt+0x70 / +0x74), the blend time
// (vt+0x78) and starts it (vt+0x50): the animation of +0x60 plays on the golem's node, the volumes are enabled. Each
// frame (vt+0x60) the conditions update, the golem tests the volumes' contacts (vt+0xa0: the golem's vt+0x120), the
// timed triggers fire, the animation runs and the step lists choose the golem's next phase / step.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/logic/KBase984C.h"
#include "k2000/services/CTriggerStarter.h"
#include "k2000/util/TVector.h"

class IKTime;
class CKHkGolem;
class IKBoundingVolume;
class CSGHotSpot;
class GolemPhaseCond;

class CKGolemAttackCommon : public KBase984C {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x265)
    int32_t IsKindOfClass(uint32_t key) override {  // vt+0x08 0x9c5580
        return key == 0x994c || key == 0xc || key == 0x984c;
    }
    DOTD_DECLARE_FACTORIES(CKGolemAttackCommon)

    // One entry of the +0x08 array (OperatorNew(0x1c)): a damage volume of the golem on a hot spot.
    struct Entry08 {
        IKBoundingVolume* m_unk00;  // +0x00 the volume (read second)
        CSGHotSpot* m_unk04;        // +0x04 the hot spot it hangs under (read first)
        uint8_t m_unk08;            // +0x08 the six bytes are read in the order +0d, +0c, +09, +08, +0a, +0b;
        uint8_t m_unk09;            // +0x09 PostLoad: +08 / +09 / +0a / +0b set the volume's property flags
        uint8_t m_unk0a;            // +0x0a 0x200 / 0x20 / 0x10 / 0x100
        uint8_t m_unk0b;            // +0x0b
        uint8_t m_unk0c;            // +0x0c the hero's hits on this volume count (ProcessDamageContacts)
        uint8_t m_unk0d;            // +0x0d (+0x0e..+0x0f padding)
        float m_unk10;              // +0x10 the offset added to the volume's frame position (file: 0.1, 0, ...)
        float m_unk14;              // +0x14 (file: -0.5, 0, ...)
        float m_unk18;              // +0x18 (file: 0.25, -0.7, ...)
    };
    // One entry of the +0x6c array (OperatorNew(0x14)): a trigger fired once per attack, at a time or at an animation
    // mark (channel 0x20, value +0x0c + 1).
    struct Entry6C {
        float m_unk00;                // +0x00 the time (file: 1.7); 0 or less: the mark value +0x0c instead
        CTriggerStarter m_unk04;      // +0x04 (loaded with type 0)
        uint32_t m_unk0c;             // +0x0c the mark value (below 10)
        uint8_t m_unk10;              // +0x10 not read by the Load: fired (StartAttack clears it)
        uint8_t m_pad11[3];
    };
    // The 8-byte sound slots +0x18..+0x3f (5): loop byte, playing byte, hot spot.
    struct SoundSlot {
        uint8_t m_unk00;            // +0x00 loop (read before the reference)
        uint8_t m_unk01;            // +0x01 not read: playing (PlayRandomSlotSound)
        uint8_t m_pad02[2];
        IKSerializable* m_unk04;    // +0x04 object reference (a CSGHotSpot: the sound's position)
    };

    CKGolemAttackCommon();  // 0x004b87b0 CKGolemAttackCommon_Construct
    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x004b9bb8 CKGolemAttackCommon_Load
    int32_t PostLoad(int32_t type) override;            // vt+0x30 0x004b8d80 CKGolemAttackCommon_PostLoad
    void Destroy() override;                            // vt+0x10 0x004b8820 CKGolemAttackCommon_Destroy
    ~CKGolemAttackCommon() override;                    // vt+0x00 0x004b8ae8 CKGolemAttackCommon_Destructor

    virtual void StartAttack();                         // vt+0x50 0x004b8400 CKGolemAttackCommon_StartAttack_maybe
    virtual void StopAttack();                          // vt+0x54 0x004b8908 CKGolemAttackCommon_StopAttack_maybe
    virtual void AttachVolumesToHotSpots();             // vt+0x58 0x004b8250 CKGolemAttackCommon_AttachVolumesToHotSpots_maybe
    virtual void Vf5C();                                // vt+0x5c 0x004b8128 CKGolemAttackCommon_vf5C
    virtual void Update(IKTime* clock);                 // vt+0x60 0x004b9898 CKGolemAttackCommon_Update_maybe
    virtual void Vf64() {}                              // vt+0x64 0x9c5578 KBaseC_vf64_3 (empty)
    virtual void Vf68();                                // vt+0x68 0x004c7420 KBaseC_vf68_3: the golem's vt+0xf0 with this
    virtual void Vf6C();                                // vt+0x6c 0x004c7478 KBaseC_vf6C_4: the golem's vt+0xf4 with this
    // vt+0x70 0x4b7628 KBaseC_vf70_3 / vt+0x74 0x4b7630 KBaseC_vf74_4: the step's condition lists (or none).
    virtual void SetStepListA(TVector<struct GolemStepA*, 1>* list) { m_unk58 = list; }
    virtual void SetStepListB(TVector<struct GolemStepB*, 1>* list) { m_unk5c = list; }
    virtual void SetBlendTime(float time) { m_unk78 = time; }  // vt+0x78 0x4b7638 KBaseC_vf78_3
    // The condition queries (vt+0x7c..+0x9c; DOTD: not virtual, no override known in DotD's attack classes).
    uint8_t IsAnimEnded() const { return m_unk65; }               // vt+0x7c 0x9c55c8 KBaseC_vf7C_2
    int32_t GetDamageSinceStartMark() const;                      // vt+0x80 0x4b7bc8 KBaseC_vf80_3
    void MarkDamageStart();                                       // vt+0x84 0x4b7b50 KBaseC_vf84
    int32_t GetDamageSinceStart() const;                          // vt+0x88 0x4b7b10 KBaseC_vf88
    int32_t GetDamageSinceUpdate() const;                         // vt+0x8c 0x4b7b88 KBaseC_vf8C_2
    uint32_t GetAnimLoopCount() const { return m_unk8c; }         // vt+0x90 0x9c55d0 KBaseC_vf90_3
    float GetStartTime() const { return m_unk90; }                // vt+0x94 0x4b7718 KBaseC_vf94_3
    float GetMarkedTime() const { return m_unk94; }               // vt+0x98 0x4b7720 KBaseC_vf98_2
    void MarkTime();                                              // vt+0x9c 0x4b8230 KBaseC_vf9C_2
    virtual void ProcessContacts(IKTime* clock);                  // vt+0xa0 0x4b75d8 KBaseC_vfA0_2

    CKHkGolem* Golem() const;  // the KBase984C reference (+0x04): the golem hook

    void PlayRandomSlotSound(uint32_t slot);   // 0x004b77b0 CKGolemAttackCommon_PlayRandomSlotSound_maybe
    void FireAnimMarkTriggers();               // 0x004b7d38 CKGolemAttackCommon_FireAnimMarkTriggers_maybe
    uint8_t AdvanceStepsList58();              // 0x004b9010 CKGolemAttackCommon_AdvanceStepsList58_maybe
    void UpdateAnimAndAdvanceSteps(IKTime* clock);  // 0x004b93a0 CKGolemAttackCommon_UpdateAnimAndAdvanceSteps_maybe
    uint8_t AdvanceStepsList5C();              // 0x004b9508 CKGolemAttackCommon_AdvanceStepsList5C_maybe

    Entry08** m_apUnk08;       // +0x08 (Mem_AllocAligned16 / Mem_ReallocAligned16)
    uint32_t m_unk08Capacity;  // +0x0c
    uint32_t m_unk08Count;     // +0x10
    uint32_t m_unk14;          // +0x14 (constructor 0; the destructor frees a node list from here: only the dead
                               // QueueTriggerSignals_maybe 0x4b7c08 fills it)
    SoundSlot m_aSlots[5];     // +0x18..+0x3f
    uint8_t m_pad40[0x10];     // +0x40..+0x4f not read by the Load
    IKSerializable* m_unk50;   // +0x50 object reference (a CKSoundDictionaryID)
    IKSerializable* m_unk54;   // +0x54 object reference (a second CKSoundDictionaryID, or null)
    TVector<struct GolemStepA*, 1>* m_unk58;  // +0x58 runtime: the step's first condition list (vt+0x70)
    TVector<struct GolemStepB*, 1>* m_unk5c;  // +0x5c runtime: the step's second condition list (vt+0x74)
    IKSerializable* m_unk60;   // +0x60 object reference (a CAnimationDictionary: the attack's animation, word 0)
    uint8_t m_unk64;           // +0x64 the animation loops (the step lists are asked at each loop)
    uint8_t m_unk65;           // +0x65 not read: the animation reached its end
    uint8_t m_pad66[2];
    IKSerializable* m_unk68;   // +0x68 object reference (the volumes' damage, a CKS08GolemDamage)
    Entry6C** m_apUnk6c;       // +0x6c (Mem_AllocAligned16 / Mem_ReallocAligned16)
    uint32_t m_unk6cCapacity;  // +0x70
    uint32_t m_unk6cCount;     // +0x74
    float m_unk78;             // +0x78 the blend time into the animation (vt+0x78)
    int32_t m_unk7c;           // +0x7c the golem's total damage at the start (vt+0x84 marks it again)
    int32_t m_unk80;           // +0x80 the golem's total damage at the start
    int32_t m_unk84;           // +0x84 the golem's damage since its mark, this frame
    float m_unk88;             // +0x88 the time in the attack (the frame times added)
    uint32_t m_unk8c;          // +0x8c the animation's loops
    float m_unk90;             // +0x90 the clock's time at the start
    float m_unk94;             // +0x94 the clock's time at the start (vt+0x9c marks it again)
};
DOTD_ASSERT_SIZE(CKGolemAttackCommon::Entry08, 0x1c);
DOTD_ASSERT_SIZE(CKGolemAttackCommon::Entry6C, 0x14);
DOTD_ASSERT_SIZE(CKGolemAttackCommon, 0x98);
DOTD_ASSERT_OFFSET(CKGolemAttackCommon, m_apUnk08, 0x08);
DOTD_ASSERT_OFFSET(CKGolemAttackCommon, m_unk08Count, 0x10);
DOTD_ASSERT_OFFSET(CKGolemAttackCommon, m_unk14, 0x14);
DOTD_ASSERT_OFFSET(CKGolemAttackCommon, m_aSlots, 0x18);
DOTD_ASSERT_OFFSET(CKGolemAttackCommon, m_unk50, 0x50);
DOTD_ASSERT_OFFSET(CKGolemAttackCommon, m_unk54, 0x54);
DOTD_ASSERT_OFFSET(CKGolemAttackCommon, m_unk58, 0x58);
DOTD_ASSERT_OFFSET(CKGolemAttackCommon, m_unk60, 0x60);
DOTD_ASSERT_OFFSET(CKGolemAttackCommon, m_unk64, 0x64);
DOTD_ASSERT_OFFSET(CKGolemAttackCommon, m_unk68, 0x68);
DOTD_ASSERT_OFFSET(CKGolemAttackCommon, m_apUnk6c, 0x6c);
DOTD_ASSERT_OFFSET(CKGolemAttackCommon, m_unk6cCount, 0x74);
DOTD_ASSERT_OFFSET(CKGolemAttackCommon, m_unk78, 0x78);
DOTD_ASSERT_OFFSET(CKGolemAttackCommon, m_unk88, 0x88);
DOTD_ASSERT_OFFSET(CKGolemAttackCommon, m_unk94, 0x94);

// The phase's step condition records (CKGolemPhaseAttack_Load; the attack walks them through +0x58 / +0x5c).
// OperatorNew(0x20) record: go to phase +0x00, step +0x04 (blend 0) when a condition holds.
struct GolemStepA {
    uint32_t m_unk00;                          // +0x00 the phase index (CKGolemPhaseManager_SwitchToPhase)
    uint32_t m_unk04;                          // +0x04 the step index
    TVector<GolemPhaseCond*, 1> m_conditions;  // +0x08 (null entries for condition id -1); any one met suffices,
                                               // no condition at all: always
    IKSerializable* m_unk14;                   // +0x14 a reference, read after the conditions (a CKMarkerBeacon:
                                               // the golem's node is put there first; null: not moved)
    uint8_t m_unk18;                           // +0x18 once: taken, it is closed (+0x19) and +0x1c opened
    uint8_t m_unk19;                           // +0x19 runtime: closed (the phase's Start clears it)
    uint8_t m_pad1a[2];
    int32_t m_unk1c;                           // +0x1c the record opened when this one is taken
};
// OperatorNew(0x24) record: the same with a blend time (+0x08).
struct GolemStepB {
    uint32_t m_unk00;                          // +0x00
    uint32_t m_unk04;                          // +0x04
    float m_unk08;                             // +0x08 the blend time (the phase's SwitchToStep / StartStepNoStop)
    TVector<GolemPhaseCond*, 1> m_conditions;  // +0x0c
    IKSerializable* m_unk18;                   // +0x18
    uint8_t m_unk1c;                           // +0x1c
    uint8_t m_unk1d;                           // +0x1d
    uint8_t m_pad1e[2];
    int32_t m_unk20;                           // +0x20
};
DOTD_ASSERT_SIZE(GolemStepA, 0x20);
DOTD_ASSERT_SIZE(GolemStepB, 0x24);
