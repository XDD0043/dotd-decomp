// IKBonusCpnt.h - the base of the bonus components (key 0x606, abstract; XXL2: IKBonusCpnt with
// m_fSquareCatchDist, m_fSpawnedLifeExpectancy, m_pSoundDictionary). On the PS3 it has no Load of its own:
// CKS08BonusCpnt_Load reads these three fields itself, in XXL2's order. Its inline copies (KBase606_*)
// are in CKS08BonusCpnt.cpp's checklist.
#pragma once
#include <cstdint>

#include "k2000/components/IKComponent.h"
#include "k2000/core/Layout.h"

class IKBonusCpnt : public IKComponent {
public:
    IKBonusCpnt() {}  // the vtable only (inlined in CKS08BonusCpnt_Create 0x5ba090)

    float m_fSquareCatchDist;              // +0x04
    float m_fSpawnedLifeExpectancy;        // +0x08
    IKSerializable* m_pSoundDictionary;    // +0x0c XXL2 CKSoundDictionaryID* (the files' refs: key 0x109)
};
DOTD_ASSERT_SIZE(IKBonusCpnt, 0x10);
DOTD_ASSERT_OFFSET(IKBonusCpnt, m_fSquareCatchDist, 0x04);
DOTD_ASSERT_OFFSET(IKBonusCpnt, m_pSoundDictionary, 0x0c);
