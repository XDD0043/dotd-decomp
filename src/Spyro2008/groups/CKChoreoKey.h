// CKChoreoKey.h - one key of a choreography: the squad members' positions (key 0x3cc, category logic,
// vtable 0xb21400, size 0x18). Its functions sit in the IKGrpEnemy.cpp unit (0x2651b0 Load). XXL2:
// K/KSquad/CKChoreoKey.h (m_asPos TVector<SChoreoPos, 10>, m_fKeyDuration, m_baFlags): the same members
// and Load order; DotD's vector grows by 5.
#pragma once
#include <cstdint>

#include "k2000/core/IKSerializable.h"
#include "k2000/core/Layout.h"
#include "k2000/math/CMatrix34.h"
#include "k2000/util/TVector.h"

class CKChoreoKey : public IKSerializable {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0xf)
    DOTD_DECLARE_FACTORIES(CKChoreoKey)

    // XXL2 SChoreoPos (0x1c bytes): two vectors read 0xc bytes at a time, each word swapped, two bytes,
    // and m_bUsed, which the Load clears.
    struct SChoreoPos {
        CVector3 m_vPos;         // +0x00
        CVector3 m_vDir;         // +0x0c
        uint8_t m_ui8Type;       // +0x18
        uint8_t m_ui8Priority;   // +0x19
        uint8_t m_bUsed;         // +0x1a
        uint8_t m_pad1b;
    };

    // 0x00265060 CKChoreoKey_Create (inlined constructor): the vector null, 5, 0.
    CKChoreoKey() {
        m_asPos.m_pBlock = nullptr;
        m_asPos.m_ui32NbElt = 5;
        m_asPos.m_ui32NbUsedElt = 0;
    }

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x002651b0 CKChoreoKey_Load

    TVector<SChoreoPos, 5> m_asPos;  // +0x04
    float m_fKeyDuration;            // +0x10
    uint16_t m_baFlags;              // +0x14 XXL2 CBitArray16
    uint8_t m_pad16[2];
};
DOTD_ASSERT_SIZE(CKChoreoKey::SChoreoPos, 0x1c);
DOTD_ASSERT_SIZE(CKChoreoKey, 0x18);
DOTD_ASSERT_OFFSET(CKChoreoKey, m_asPos, 0x04);
DOTD_ASSERT_OFFSET(CKChoreoKey, m_fKeyDuration, 0x10);
DOTD_ASSERT_OFFSET(CKChoreoKey, m_baFlags, 0x14);
