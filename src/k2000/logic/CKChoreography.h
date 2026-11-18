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
class IKTime;

class CKChoreography : public IKSerializable {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x1b)
    int32_t IsKindOfClass(uint32_t key) override { return key == 0x6cc || key == 0xc; }  // vt+0x08 0x9bb040
    DOTD_DECLARE_FACTORIES(CKChoreography)

    // 0x00264788 CKChoreography_Create (inlined constructor): the key vector null, 1, 0.
    CKChoreography() {
        m_apChoreoKey.m_pBlock = nullptr;
        m_apChoreoKey.m_ui32NbElt = 1;
        m_apChoreoKey.m_ui32NbUsedElt = 0;
    }

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x00264bf8 CKChoreography_Load
    // vt+0x24 0x002645e8 CKChoreography_RecursiveRegistration: registered with the saving manager (vt+0x24, no owner)
    // unless the type is 4..7 (an unsigned type - 4 > 3). (vt+0x10 0x002645e0 CKChoreography_Destroy is empty.)
    void RecursiveRegistration(int32_t type) override;
    // 0x002649e8 CKChoreography_GetCurrentKey_maybe: the current key, null without keys.
    CKChoreoKey* GetCurrentKey() const {
        return m_apChoreoKey.m_ui32NbUsedElt != 0 ? m_apChoreoKey.m_pBlock[m_ui8CurrentKey] : nullptr;
    }
    // 0x002647d8 CKChoreography_Reset_maybe: back to the first key (time 0), its slots freed.
    void Reset();
    // 0x00264818 CKChoreography_Update_maybe: the key's time runs (a key of negative duration holds); when it is over
    // the next key (wrapping) becomes current, its slots freed then given the previous key's taken flags. 1 when the
    // key changed (also when the choreography has a single key), 0 otherwise.
    uint8_t Update(IKTime* clock);
    // 0x00264a20 CKChoreography_SwitchToKey_maybe (the squads' message 0xd10).
    void SwitchToKey(uint8_t key);

    float m_fElapsedTime;     // +0x04
    uint8_t m_ui8CurrentKey;  // +0x08
    uint8_t m_pad09[3];
    TVector<CKChoreoKey*, 1> m_apChoreoKey;  // +0x0c
};
DOTD_ASSERT_SIZE(CKChoreography, 0x18);
DOTD_ASSERT_OFFSET(CKChoreography, m_fElapsedTime, 0x04);
DOTD_ASSERT_OFFSET(CKChoreography, m_ui8CurrentKey, 0x08);
DOTD_ASSERT_OFFSET(CKChoreography, m_apChoreoKey, 0x0c);
