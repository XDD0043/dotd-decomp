// CKHkMoveCpnt.h - the movement parameters of an enemy (key 0x300c, vtable 0xb22630, size 0xac). Original
// unit: CKHkMoveCpnt.cpp. XXL2: Commun/K/KSquad/CKHkMoveCpnt.h (m_fRadius ... m_fJumpFallStartRatio: 27
// floats, then m_eMvtAnim, m_fAnimScaleRatio, m_sfSpeed, m_sv3Speed). DotD reads 30 floats, so the floats do
// not map one to one onto XXL2's names; the two words its Load sets after them keep XXL2's names (_maybe).
// Embedded in CKEnemyCpnt (+0x08) and CKS08EnemyCpnt (+0x37c); no KP3 file holds one on its own.
#pragma once
#include <cstdint>

#include "k2000/core/IKSerializable.h"
#include "k2000/core/Layout.h"

class CKHkMoveCpnt : public IKSerializable {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0xc0)
    DOTD_DECLARE_FACTORIES(CKHkMoveCpnt)

    // 0x002bc9c0 CKHkMoveCpnt_Create: the vtable and three 0.0f (TOC 0x18e4) at +0x84..+0x8c.
    CKHkMoveCpnt() {
        m_afUnk84[0] = 0.0f;
        m_afUnk84[2] = 0.0f;
        m_afUnk84[1] = 0.0f;
    }
    ~CKHkMoveCpnt() override {}

    // vt+0x2c 0x002bcc98 CKHkMoveCpnt_Load: 30 floats for K_LEVEL_PLATEFORMS, then +0x7c = 0, +0x80 = 1.0.
    int32_t Load(IKFile* file, int32_t type) override;

    float m_afParams[30];      // +0x04..+0x78 XXL2 m_fRadius, m_fAnimRunSpeed, ... (DotD has three more)
    uint32_t m_eMvtAnim;       // +0x7c _maybe XXL2 EEnemyMvtAnim m_eMvtAnim (the Load sets 0)
    float m_fAnimScaleRatio;   // +0x80 _maybe XXL2 m_fAnimScaleRatio (the Load sets 1.0, as XXL2's)
    float m_afUnk84[3];        // +0x84 the constructor sets 0.0 (XXL2 m_sfSpeed _maybe)
    uint32_t m_unk90[7];       // +0x90..+0xa8 run-time state
};
static_assert(CKHkMoveCpnt::kClassKey == 0x300c, "key");
DOTD_ASSERT_SIZE(CKHkMoveCpnt, 0xac);
DOTD_ASSERT_OFFSET(CKHkMoveCpnt, m_afParams, 0x04);
DOTD_ASSERT_OFFSET(CKHkMoveCpnt, m_eMvtAnim, 0x7c);
DOTD_ASSERT_OFFSET(CKHkMoveCpnt, m_fAnimScaleRatio, 0x80);
DOTD_ASSERT_OFFSET(CKHkMoveCpnt, m_afUnk84, 0x84);
