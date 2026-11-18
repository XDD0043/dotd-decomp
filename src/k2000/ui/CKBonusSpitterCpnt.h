// CKBonusSpitterCpnt.h - a bonus spitter's parameters (key 0xb46, vtable 0xb2f710, size 0x34; library-TOC code).
// Original unit: CKBonusSpitterCpnt.cpp (0x5bb7e8-0x5bc3e0). XXL2 CKBonusSpitterCpnt (IKComponent, m_lTypicalSpit,
// m_lCurrentSpit, m_vPosition, m_vSpeed, m_fSpitDeltaTime, m_fHorizontalSpeedDelta, m_bSpitOnLeader, ...): the names
// below where the read order matches. Its only users (UpdateEmission 0x5bbc30, QueueConfiguredBonuses 0x5bbfa8,
// QueueBonus 0x5bc070) are dead: the component is loaded and freed, nothing else.
#pragma once
#include <cstdint>

#include "k2000/components/IKComponent.h"
#include "k2000/core/Layout.h"
#include "k2000/math/CMatrix34.h"

class CKBonusSpitterCpnt : public IKComponent {
public:
    DOTD_CLASS_KEY(kCategoryComponent, 0x2d)
    DOTD_DECLARE_FACTORIES(CKBonusSpitterCpnt)

    int32_t IsKindOfClass(uint32_t key) override {  // vt+0x08 0x9ccf50
        return key == 0xb46 || key == 0x6 || key == 0xc;
    }

    // One spit of a list (8 bytes on the PS3, from the FreeListPool at 0x00ceaa30 / its free list 0x00ceaa34 in the
    // original; plain new / delete here): two halfwords (the Load's pair, in the file's order) and the next node.
    struct SSpitNode {
        uint16_t m_ui16A;   // +0x00
        uint16_t m_ui16B;   // +0x02
        SSpitNode* m_pNext;  // +0x04
    };

    // 0x005bb9b0 CKBonusSpitterCpnt_Create (OperatorNew(0x34)): the vtable, both lists empty.
    CKBonusSpitterCpnt() {
        m_lCurrentSpit = nullptr;
        m_lTypicalSpit = nullptr;
    }
    // 0x005bbac0 CKBonusSpitterCpnt_Destructor / 0x005bb9f8 _DeletingDestructor: the nodes of +0x08, then of +0x04, back
    // to their pool (each pushed on its free list), both heads cleared; then IKBaseClass's.
    ~CKBonusSpitterCpnt() override;
    // vt+0x10 0x005bbfa0 CKBonusSpitterCpnt_ClearReferences (the Destroy slot): empty. vt+0x24 0x005bbf98 _LevelReset:
    // registers nothing (returns 1). Both are the defaults.
    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x005bc120 CKBonusSpitterCpnt_Load

    SSpitNode* m_lTypicalSpit;       // +0x04 XXL2: the Load's pairs (each pushed at the head)
    SSpitNode* m_lCurrentSpit;       // +0x08 XXL2 (filled by the dead QueueBonus)
    CVector3 m_vPosition;            // +0x0c XXL2 (one 0x18-byte read with +0x18)
    CVector3 m_vSpeed;               // +0x18 XXL2
    float m_fSpitDeltaTime;          // +0x24 XXL2 (one 8-byte read with +0x28)
    float m_fHorizontalSpeedDelta;   // +0x28 XXL2
    uint8_t m_bSpitOnLeader;         // +0x2c XXL2 (a byte read)
    uint8_t m_pad2D[3];
    float m_fTimer;                  // +0x30 not loaded (XXL2 m_fTimer)
};
DOTD_ASSERT_SIZE(CKBonusSpitterCpnt, 0x34);
DOTD_ASSERT_OFFSET(CKBonusSpitterCpnt, m_lTypicalSpit, 0x04);
DOTD_ASSERT_OFFSET(CKBonusSpitterCpnt, m_vPosition, 0x0c);
DOTD_ASSERT_OFFSET(CKBonusSpitterCpnt, m_fSpitDeltaTime, 0x24);
DOTD_ASSERT_OFFSET(CKBonusSpitterCpnt, m_bSpitOnLeader, 0x2c);
