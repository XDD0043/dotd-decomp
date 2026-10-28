// CKChoreography.h - a squad's formation sequence (key 0x6cc, category logic, vtable 0xb213a8, size 0x18).
// Original unit: CKChoreography.cpp. XXL2: K/KSquad/CKChoreography.h (m_fElapsedTime, m_ui8CurrentKey,
// m_ui8NbKey, m_apChoreoKey[16]); the Load reads the same fields in the same order, but DotD keeps the keys
// in a TVector (block, capacity, count) instead of a fixed array and the count byte is not stored apart.
#pragma once
#include <cstdint>

#include "k2000/core/IKSerializable.h"
#include "k2000/core/Layout.h"
#include "k2000/util/TVector.h"

class CKChoreoKey;

class CKChoreography : public IKSerializable {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x1b)
    DOTD_DECLARE_FACTORIES(CKChoreography)

    // 0x00264788 CKChoreography_Create (inlined constructor): the key vector null, 1, 0.
    CKChoreography() {
        m_apChoreoKey.m_pBlock = nullptr;
        m_apChoreoKey.m_ui32NbElt = 1;
        m_apChoreoKey.m_ui32NbUsedElt = 0;
    }

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x00264bf8 CKChoreography_Load

    float m_fElapsedTime;     // +0x04
    uint8_t m_ui8CurrentKey;  // +0x08
    uint8_t m_pad09[3];
    TVector<CKChoreoKey*, 1> m_apChoreoKey;  // +0x0c
};
DOTD_ASSERT_SIZE(CKChoreography, 0x18);
DOTD_ASSERT_OFFSET(CKChoreography, m_fElapsedTime, 0x04);
DOTD_ASSERT_OFFSET(CKChoreography, m_ui8CurrentKey, 0x08);
DOTD_ASSERT_OFFSET(CKChoreography, m_apChoreoKey, 0x0c);
