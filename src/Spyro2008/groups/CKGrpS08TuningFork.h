// CKGrpS08TuningFork.h - the tuning-fork puzzle group (key 0xcc4, vtable 0xb29968, size 0x38). Original
// unit: CKGrpS08TuningFork.cpp. No XXL2 class of this name.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/groups/IKBaseGroup.h"
#include "k2000/util/TVector.h"

class CKGrpS08TuningFork : public IKGroup<IKHook> {
public:
    DOTD_CLASS_KEY(kCategoryGroup, 0x33)
    DOTD_DECLARE_FACTORIES(CKGrpS08TuningFork)

    // One reference list (OperatorNew(0x10): the vector, then a word nobody sets).
    struct RefSet {
        TVector<IKSerializable*, 1> m_vRefs;  // +0x00 null, 1, 0, then a 4-byte block
        uint32_t m_unk0c;                     // +0x0c not set
    };

    // 0x004cd6e0 CKGrpS08TuningFork_Create (the constructor 0x4cc970 inlined): the vector null, 1, 0.
    CKGrpS08TuningFork() {
        m_vSets.m_pBlock = nullptr;
        m_vSets.m_ui32NbElt = 1;
        m_vSets.m_ui32NbUsedElt = 0;
    }

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x004cd2c8 CKGrpS08TuningFork_Load

    TVector<RefSet*, 1> m_vSets;  // +0x2c
};
DOTD_ASSERT_SIZE(CKGrpS08TuningFork::RefSet, 0x10);
DOTD_ASSERT_SIZE(CKGrpS08TuningFork, 0x38);
DOTD_ASSERT_OFFSET(CKGrpS08TuningFork, m_vSets, 0x2c);
