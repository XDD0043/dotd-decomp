// CKMarkedTrigger.h - trigger starters keyed by marks (key 0xb08c, vtable 0xb30238, size 0x1c). Original
// unit: CKMarkedTrigger.cpp. DotD only; the names are ours.
#pragma once
#include <cstdint>

#include "k2000/core/IKSerializable.h"
#include "k2000/core/Layout.h"
#include "k2000/services/CTriggerStarter.h"
#include "k2000/util/TVector.h"

class IKTime;

class CKMarkedTrigger : public IKSerializable {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x2c2)
    int32_t IsKindOfClass(uint32_t key) override { return key == 0xb08c || key == 0xc; }  // vt+0x08 0x9cd700
    DOTD_DECLARE_FACTORIES(CKMarkedTrigger)

    // One mark (OperatorNew(0x10)): a starter and two words (a mark id and a value _maybe).
    struct Mark {
        CTriggerStarter m_tsStarter;  // +0x00 loaded last
        uint32_t m_unk08;             // +0x08 loaded first
        uint32_t m_unk0c;             // +0x0c
    };

    CKMarkedTrigger();  // 0x005d1798 CKMarkedTrigger_Construct
    // 0x005d2438 CKMarkedTrigger_Destructor (0x005d23b8 DeletingDestructor, 0x005d24a0 Destructor_2: the same): the mark
    // block freed (the marks are Destroy's), the count cleared.
    ~CKMarkedTrigger() override;
    // vt+0x10 0x005d1b90 CKMarkedTrigger_Destroy: every mark deleted, the count cleared (the block kept).
    void Destroy() override;
    // vt+0x40 0x005d1af8 CKMarkedTrigger_GetInfo: 1 (the inherited default).

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x005d1c10 CKMarkedTrigger_Load
    // 0x005d2068 CKMarkedTrigger_UpdateFromAnimMarks_maybe (C2.8 sequence; the sequence manager's Update): the integer
    // marks of the node's animation crossed between the evaluated time and the time now (both wrapped into the
    // animation; right after a change to another animation, the end of the one evaluated last) fire the starters of
    // the marks with that id (+0x08) and value (+0x0c).
    void UpdateFromAnimMarks(IKTime* clock);
    // 0x005d1888 CKMarkedTrigger_FireMatchingEntries_maybe: the starters of the marks with id `id` and value `value`
    // queued. 0x005d1f48 CKMarkedTrigger_FireMark_maybe: with an animation, its mark `id` crossed between *t0 and *t1
    // (vt+0x1c) does that with the crossed value. No caller of either (UpdateFromAnimMarks inlines them).
    void FireMatchingEntries(uint32_t id, uint32_t value);
    void FireMark(uint32_t id, struct RtAnimAnimation* animation, const float* t0, const float* t1);

    TVector<Mark*, 1> m_vMarks;  // +0x04
    IKSerializable* m_unk10;     // +0x10 a reference: the animated node (a CAnimatedNode)
    IKSerializable* m_unk14;     // +0x14 a reference
    uint32_t m_unk18;            // +0x18
};
DOTD_ASSERT_SIZE(CKMarkedTrigger::Mark, 0x10);
DOTD_ASSERT_SIZE(CKMarkedTrigger, 0x1c);
DOTD_ASSERT_OFFSET(CKMarkedTrigger, m_vMarks, 0x04);
DOTD_ASSERT_OFFSET(CKMarkedTrigger, m_unk10, 0x10);
DOTD_ASSERT_OFFSET(CKMarkedTrigger, m_unk14, 0x14);
DOTD_ASSERT_OFFSET(CKMarkedTrigger, m_unk18, 0x18);
