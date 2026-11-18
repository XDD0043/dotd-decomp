// CKPxConstraintReport.h - the physics constraints' history (key 0x564c, vtable 0xb20740, size 0x114). Original unit:
// CKPxConstraintReport.cpp (0x2317a8-0x2322b0). Derived straight from IKSerializable. No game file holds one
// (outputs/remake/kp3-class-usage.json). Names ours.
#pragma once
#include <cstdint>

#include "k2000/core/IKSerializable.h"
#include "k2000/core/Layout.h"
#include "k2000/math/CMatrix34.h"
#include "k2000/util/TVector.h"

class CKPxConstraintReport : public IKSerializable {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x159)
    int32_t IsKindOfClass(uint32_t key) override { return key == 0x564c || key == 0xc; }
    DOTD_DECLARE_FACTORIES(CKPxConstraintReport)

    // One constraint (PS3 0x40 bytes): two bodies with a point and a direction each (Snapshot turns them into world
    // space through each body's matrix +0xf0).
    struct SConstraint {
        IKSerializable* m_pBodyA;  // +0x00 a CKPxBody
        CVector3 m_vPointA;        // +0x04
        IKSerializable* m_pBodyB;  // +0x10
        CVector3 m_vPointB;        // +0x14
        CVector3 m_vDirA;          // +0x20
        float m_unk2c;             // +0x2c (ProcessBodyContacts: the impulse along m_vDirA)
        CVector3 m_vDirB;          // +0x30
        float m_unk3c;             // +0x3c (the impulse along m_vDirB)
    };

    CKPxConstraintReport();  // inlined in 0x00231db8 CKPxConstraintReport_Create: the 21 arrays (null, 1, 0)
    // 0x00232160 CKPxConstraintReport_Destructor (_2 0x232208, the deleting one 0x2320a8): the history's blocks freed
    // last to first, then the current list's.
    ~CKPxConstraintReport() override;
    // vt+0x2c 0x00231ef0 CKPxConstraintReport_Load (level data only): the flags, a fresh one-record block for the current
    // list and for each history slot, the history's size and period, the counters cleared.
    int32_t Load(IKFile* file, int32_t type) override;
    // vt+0x10 0x00231e38 CKPxConstraintReport_Destroy: every block freed, each length and block cleared.
    void Destroy() override;
    // vt+0x24 0x002319d8 CKPxConstraintReport_RecursiveRegistration: returns 1, registers nothing (the default).
    // 0x002319e0 CKPxConstraintReport_SnapshotConstraintsEveryN_maybe (C2.8 port-last Z7; CKPxConstraintReport.cpp)
    void SnapshotConstraintsEveryN();

    uint16_t m_ui16Flags;                       // +0x04 bit 0x200: recording
    uint8_t m_pad06[2];
    TVector<SConstraint, 1> m_current;          // +0x08 the constraints of the step
    uint16_t m_ui16NbCurrent;                   // +0x14 the Load sets 0
    uint8_t m_pad16[2];
    TVector<SConstraint, 1> m_history[20];      // +0x18 the snapshots (a ring)
    uint16_t m_ui16HistorySize;                 // +0x108 the ring's used slots
    uint16_t m_ui16Period;                      // +0x10a a snapshot every that many steps
    uint16_t m_ui16StepCounter;                 // +0x10c
    uint16_t m_ui16Write;                       // +0x10e the ring's write slot
    uint16_t m_ui16Read;                        // +0x110 the ring's oldest slot
    uint8_t m_pad112[2];
};
DOTD_ASSERT_SIZE(CKPxConstraintReport, 0x114);
DOTD_ASSERT_OFFSET(CKPxConstraintReport, m_current, 0x08);
DOTD_ASSERT_OFFSET(CKPxConstraintReport, m_ui16NbCurrent, 0x14);
DOTD_ASSERT_OFFSET(CKPxConstraintReport, m_history, 0x18);
DOTD_ASSERT_OFFSET(CKPxConstraintReport, m_ui16HistorySize, 0x108);
DOTD_ASSERT_OFFSET(CKPxConstraintReport, m_ui16Read, 0x110);
