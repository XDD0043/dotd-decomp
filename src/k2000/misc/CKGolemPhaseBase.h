// CKGolemPhaseBase.h - an unregistered abstract base (key 0x978c, Ghidra: CKGolemPhaseBase_maybe / KBase978C;
// no XXL2 counterpart). Original unit: CKGolemPhaseBase.cpp (0x4c75f8-0x4c7730). Derived straight from
// IKSerializable; its classes are CKGolemPhaseAttack (0x97cc) and CKGolemPhaseQTE (0xa10c), the golem boss's
// phases (CKGolemPhaseManager holds them).
//
// The phase slots (vt+0x50..+0x84; both classes fill them): the manager updates the current phase (vt+0x50), starts
// (vt+0x54) and stops (vt+0x58) it, resets (vt+0x5c) and restarts (vt+0x60) every phase, and switches the current
// phase's step (vt+0x64) or a new phase's first step (vt+0x68); the conditions read the damage and time marks
// (vt+0x6c..+0x84).
#pragma once
#include <cstdint>

#include "k2000/core/IKSerializable.h"
#include "k2000/core/Layout.h"

class IKTime;
class CKHkGolem;

class CKGolemPhaseBase : public IKSerializable {
public:
    CKGolemPhaseBase() {}  // 0x004c7620 CKGolemPhaseBase_maybe_Construct: stores the vtable only
    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x004c7630 CKGolemPhaseBase_maybe_Load

    virtual void Update(IKTime* clock) = 0;                     // vt+0x50
    virtual void Start() = 0;                                   // vt+0x54
    virtual void Stop() = 0;                                    // vt+0x58
    virtual void ResetPhases() = 0;                             // vt+0x5c
    virtual void Vf60() = 0;                                    // vt+0x60
    virtual void SwitchToStep(uint32_t step, float blend) = 0;  // vt+0x64
    virtual void StartStepNoStop(uint32_t step, float blend) = 0;  // vt+0x68
    virtual int32_t GetDamageSincePhaseStart() = 0;             // vt+0x6c
    virtual void MarkDamageBaseline() = 0;                      // vt+0x70
    virtual int32_t GetDamageSinceMark2() = 0;                  // vt+0x74
    virtual int32_t GetDamageSinceUpdate() = 0;                 // vt+0x78
    virtual float GetStartTime() = 0;                           // vt+0x7c
    virtual float GetMarkedTime() = 0;                          // vt+0x80
    virtual void MarkTime() = 0;                                // vt+0x84

    CKHkGolem* Golem() const;  // +0x04 (the golem hook)

    IKSerializable* m_unk04;  // +0x04 object reference (file: the golem hook, CKHkS08DragonCityGolem 0x31c2)
};
DOTD_ASSERT_OFFSET(CKGolemPhaseBase, m_unk04, 0x04);
