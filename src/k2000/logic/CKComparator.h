// CKComparator.h - a trigger condition comparing two CKComparedData (key 0x230c, vtable 0xb20978,
// size 0x14). Original unit: CKComparator.cpp. XXL2: K/KServices/KServiceTrigger/CKComparator.h
// (m_aDatas[2], the same Load).
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/misc/IKEvaluator.h"

class CKComparedData;

class CKComparator : public IKEvaluator {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x8c)
    int32_t IsKindOfClass(uint32_t key) override {  // vt+0x08 0x9b75b8
        return key == 0x230c || key == 0x228c || key == 0xc;
    }
    DOTD_DECLARE_FACTORIES(CKComparator)

    CKComparator() {}  // inlined in 0x00234ce0 CKComparator_Create: the IKEvaluator part only
    ~CKComparator() override {}

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x00234938 CKComparator_Load
    // vt+0x24 0x00234b48 CKComparator_RecursiveRegistration: the base's (0x235030), then for type 0 both operands (each
    // when present, vt+0x24 with 0).
    void RecursiveRegistration(int32_t type) override;
    // vt+0x10 0x00234c10 CKComparator_Destroy: KStub_Nop_235180 (IKEvaluator's empty Destroy) only.
    // vt+0x58 0x00234d30 CKComparator_ClearFiredEvents_maybe: an operand of mode 2 (flags bits 2-3) loses its
    // "fired" bit (bit 24 of its +0x08 word).
    void Start() override;
    // vt+0x50 0x00234f78 and vt+0x5c 0x00234db0: the same body as Start (0x234d30).
    void Vf50() override;
    void Vf5C() override;
    // vt+0x54 0x00234ff8 CKComparator_Evaluate: CKComparator_CompareOperands(a, (flags >> 1) & 7, b), the inline at
    // 0x9b7658. The operator (flags bits 1-3) and the first operand's type (its flags bits 0-1) pick the compare:
    // type 0 byte, 1 integer, 2 float (3 as 1); operators 0 <=, 1 <, 2 >=, 3 >, 4 ==, 5 !=. Type 0 only exists for
    // == and !=; the other combinations give false.
    bool Vf54() override;
    // vt+0x64 0x00234e30 CKComparator_vf64: the same for the operands whose bit 25 is clear.
    void Asleep() override;
    // vt+0x68 0x002348a8 CKComparator_vf68: empty (the default).

    CKComparedData* m_aDatas[2];  // +0x0c XXL2 m_aDatas
};
DOTD_ASSERT_SIZE(CKComparator, 0x14);
DOTD_ASSERT_OFFSET(CKComparator, m_aDatas, 0x0c);
