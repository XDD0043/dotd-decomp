// KBase7CCC.h - the colossus attack elements' unregistered base (key 0x7ccc, vtable 0xb27790, size 0x68; Ghidra
// KBase7CCC_* / CKColossusAttackElementBase_maybe_* / CKColossusContextualAttackElement_vf54 / _StartAttack_maybe and
// a run of KBaseC_vfXX). Its out-of-line methods are in Spyro2008/logic/IKSerializable.cpp (0x470778-0x472af8), two
// more (vf60 0x4706c0, vf80 0x4706b0) in CKColossusAttackSequenceBase.cpp's unit and three inline ones (vf8 / vf14 /
// vf18 0x9c4578..0x9c4588). CKColossusContextualAttackElement (0x7d0c) keeps every slot from vt+0x50 on and
// CKColossusBaseAttackElement (0x7e8c) overrides vt+0x50 / +0x54 / +0x60. No XXL2 class; names ours. No game file holds
// an element (work/level-class-keys.json): C2.8 port-rest R11 ported it from the code.
//
// An element is one attack of a colossus sequence: an animation of the colossus (the dictionary +0x54), two lists of
// hot spot volumes (+0x38: the attack's own volumes, added to the collision service while it runs, their radius ramped
// over time and their damage the block +0x60; +0x44: the volumes that take hits: every contact of a damaging volume
// lowers the colossus' +0x54) and the colossus' yaw turned toward the first hero (flag bit 3) or back (bit 4).
#pragma once
#include <cstdint>

#include "k2000/core/IKSerializable.h"
#include "k2000/core/Layout.h"
#include "k2000/util/TVector.h"

class CKColossusAttackSequenceBase;
class CKHkColossus;
class CKGrpS08Hero;
class IKBoundingVolume;
class IKHook;
class IKTime;
struct ContactHistoryNode;

// The object a damaging volume carries at +0x1c whose vt+0x54 the contact walk (vt+0x74) takes off the colossus' +0x54.
// Its class is not known: a CKDamage / CKS08Damage (what the other code puts there) has no slot +0x54.
class IKColossusHitSource_maybe : public IKSerializable {
public:
    virtual void Vf50() = 0;
    virtual int32_t Vf54() = 0;
};

class KBase7CCC : public IKSerializable {
public:
    int32_t GetClassType() override { return 0xc; }   // vt+0x14 0x009c4578
    int32_t GetClassID() override { return 0x1f3; }   // vt+0x18 0x009c4580
    int32_t IsKindOfClass(uint32_t key) override { return key == 0x7ccc || key == 0xc; }  // vt+0x08 0x009c4588

    // A volume record of the two lists (0x1c bytes, operator new and zeroed by the Load; Destroy deletes them).
    struct Entry {
        IKBoundingVolume* m_pVolume;  // +0x00 PostLoad: the colossus' hot spot record's volume (+0x08 / +0x0c)
        uint32_t m_ui32HotSpot;       // +0x04 the hot spot record's index (Load)
        float m_fStart;               // +0x08 the time (+0x34) the radius ramp starts at (Load)
        float m_fDuration;            // +0x0c the ramp's length; 0: no ramp (Load)
        float m_fRadiusFrom;          // +0x10 the radius at the start (Load; not above 0: 0.001)
        float m_fRadiusTo;            // +0x14 StartAttack: the volume's radius then (the end of the ramp)
        float m_fRadiusSaved;         // +0x18 StartAttack: the same, put back by the stop (vt+0x54)
    };
    // The block the attack volumes carry at +0x1c (operator new 0x38 in PostLoad, no constructor; Destroy deletes it).
    struct HitInfo {
        uint8_t m_aUnk00[0x28];  // +0x00 not written by this unit
        float m_fUnk28;          // +0x28 StartAttack: 1.0
        uint32_t m_unk2C;        // +0x2c StartAttack: 0
        uint32_t m_unk30;        // +0x30 StartAttack: 0
        uint32_t m_unk34;        // +0x34 StartAttack: 0
    };

    // 0x00471160 CKColossusAttackElementBase_maybe_Construct (the dead 0x471198 copy): both lists empty with a capacity of
    // 1 (blocks null), no contacts. The original leaves the rest to its fresh heap (zero here).
    KBase7CCC() {
        for (float& value : m_afApproach) value = 0.0f;
        m_fTurnTopSpeed = 0.0f;
        m_fTurnAccel = 0.0f;
        m_fTurnDecel = 0.0f;
        m_pOwner = nullptr;
        m_pSequence = nullptr;
        m_fTime = 0.0f;
        m_vVolumes.m_pBlock = nullptr;
        m_vVolumes.m_ui32NbElt = 1;
        m_vVolumes.m_ui32NbUsedElt = 0;
        m_vTargets.m_pBlock = nullptr;
        m_vTargets.m_ui32NbElt = 1;
        m_vTargets.m_ui32NbUsedElt = 0;
        m_pContacts = nullptr;
        m_pAnimations = nullptr;
        m_ui32Flags = 0;
        m_pHeroGroup = nullptr;
        m_pHitInfo = nullptr;
        m_pHook = nullptr;
    }
    // 0x00472860 KBase7CCC_Destructor (= 0x472938 CKColossusAttackElementBase_maybe_BaseDestructor, 0x472a10
    // KBase7CCC_DeletingDestructor): the contacts back to their pool, both blocks freed and cleared (IKSerializable.cpp).
    ~KBase7CCC() override;

    void Destroy() override;                                   // vt+0x10 0x004712f8 KBase7CCC_ClearReferences
    void RecursiveRegistration(int32_t /*type*/) override {}  // vt+0x24 0x004712f0 KBase7CCC_vf24 (returns 1)
    int32_t Save(IKFile* /*file*/, int32_t /*type*/) override { return 1; }  // vt+0x28 0x004712e8 KBase7CCC_vf28
    int32_t Load(IKFile* file, int32_t type) override;         // vt+0x2c 0x00472148 KBase7CCC_Load
    int32_t PostLoad(int32_t type) override;                   // vt+0x30 0x00470a10 (Ghidra IKSerializable_PostLoad)

    // vt+0x50 0x00471df8 CKColossusContextualAttackElement_StartAttack_maybe: the attack starts.
    virtual void Vf50();
    // vt+0x54 0x004713e8 CKColossusContextualAttackElement_vf54: the attack stops.
    virtual void Vf54();
    virtual void Vf58() {}  // vt+0x58 0x009c44f0 (empty)
    virtual void Vf5C() {}  // vt+0x5c 0x009c44f8 (empty)
    // vt+0x60 0x004706c0 CKColossusContextualAttackElement_vf60: the time +0x34 advances by the clock's dt, then the
    // volumes (vt+0x6c), the animation (vt+0x64) and the turn (vt+0x68).
    virtual void Vf60(IKTime* frameClock);
    virtual void Vf64(IKTime* frameClock);  // vt+0x64 0x00470e20 KBaseC_vf64_2: the colossus' animation
    virtual void Vf68(IKTime* frameClock);  // vt+0x68 0x00471930 KBaseC_vf68_2: the colossus' turn
    virtual void Vf6C(IKTime* frameClock);  // vt+0x6c 0x00470778 KBaseC_vf6C_3: vt+0x78, vt+0x74, vt+0x70
    virtual void Vf70(IKTime* frameClock);  // vt+0x70 0x00470b50 KBaseC_vf70_2: the attack volumes' contacts (no effect)
    virtual void Vf74(IKTime* frameClock);  // vt+0x74 0x00470f10 KBaseC_vf74_3: the hits on the target volumes
    virtual void Vf78(IKTime* frameClock);  // vt+0x78 0x00470cc0 KBaseC_vf78_2: vt+0x7c for every record
    virtual void Vf7C(Entry* entry);        // vt+0x7c 0x004711d0 KBaseC_vf7C: a record's radius ramp
    virtual void Vf80() { m_fTime = 0.0f; }  // vt+0x80 0x004706b0 KBaseC_vf80_2

    float m_afApproach[7];          // +0x04 the turn's Math_ApproachAngleWithAccelDecel state (k2000/misc/FloatApproach.h)
    float m_fTurnTopSpeed;          // +0x20 (Load) StartAttack copies it to the state's top speed (+0x0c)
    float m_fTurnAccel;             // +0x24 (Load) to the state's acceleration (+0x04)
    float m_fTurnDecel;             // +0x28 (Load) to the state's deceleration (+0x08)
    CKHkColossus* m_pOwner;         // +0x2c the colossus (not set by this unit)
    // +0x30 the sequence running the element (CKColossusAttackSequence stores itself when it starts the element; C2.8
    // port-final F03); not read by this unit.
    CKColossusAttackSequenceBase* m_pSequence;
    float m_fTime;                  // +0x34 the attack's time (vt+0x60; StartAttack / vt+0x80: 0)
    TVector<Entry*, 1> m_vVolumes;  // +0x38 the attack's volumes (Load)
    TVector<Entry*, 1> m_vTargets;  // +0x44 the volumes that take hits (Load)
    ContactHistoryNode* m_pContacts;  // +0x50 the hits of vt+0x74 (ContactHistory); constructor 0
    IKSerializable* m_pAnimations;    // +0x54 reference (Load): a CAnimationDictionary, its first word the attack's
    // +0x58 bit 0 (Load) the animation loops, bit 1 its end reached, bits 2 / 3 / 4 (Load): bit 3 the colossus turns
    // toward the first hero, bit 4 it turns back.
    uint32_t m_ui32Flags;
    CKGrpS08Hero* m_pHeroGroup;     // +0x5c StartAttack: the game manager's hero group (PostLoad: 0)
    HitInfo* m_pHitInfo;            // +0x60 PostLoad: a new block; the attack volumes carry it at +0x1c
    IKHook* m_pHook;                // +0x64 a hook woken while the attack runs (not set by this unit; PostLoad: 0)
};
DOTD_ASSERT_SIZE(KBase7CCC, 0x68);
DOTD_ASSERT_OFFSET(KBase7CCC, m_afApproach, 0x04);
DOTD_ASSERT_OFFSET(KBase7CCC, m_fTurnTopSpeed, 0x20);
DOTD_ASSERT_OFFSET(KBase7CCC, m_pOwner, 0x2c);
DOTD_ASSERT_OFFSET(KBase7CCC, m_fTime, 0x34);
DOTD_ASSERT_OFFSET(KBase7CCC, m_vVolumes, 0x38);
DOTD_ASSERT_OFFSET(KBase7CCC, m_vTargets, 0x44);
DOTD_ASSERT_OFFSET(KBase7CCC, m_pContacts, 0x50);
DOTD_ASSERT_OFFSET(KBase7CCC, m_pAnimations, 0x54);
DOTD_ASSERT_OFFSET(KBase7CCC, m_ui32Flags, 0x58);
DOTD_ASSERT_OFFSET(KBase7CCC, m_pHeroGroup, 0x5c);
DOTD_ASSERT_OFFSET(KBase7CCC, m_pHitInfo, 0x60);
DOTD_ASSERT_OFFSET(KBase7CCC, m_pHook, 0x64);
