// PFPathQuery.cpp - reconstructed original translation unit 0x1e9ee0-0x1ea0a8 (GAME_TOC1, main_toc1), 4 functions, 3 live.
// Primary owner: PFPathQuery (not a registered class)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x1e9ee0  CPFPathSlot_Initialize
//   [x] 0x1e9fe0  PFPathQuery_Construct_maybe
//   [ ] 0x1ea040  PFPathQuery_Construct_2_maybe  [dead]
//   [x] 0x1ea0a0  KStub_Return1_1ea0a0  (CPFPortal::Save, vt+0x00 (CKPFGraphTransition.h))
#include "k2000/ai/CKSrvPathFinding.h"

// 0x001e9ee0 CPFPathSlot_Initialize. The character's bits are copied in four fields (3-10, 11, 12, 0-2), the bits
// above 12 of the slot's word kept; its other two floats are not copied.
void CPFPathSlot::Initialize(const CPFPoint* seeker, const CPFPoint* target, const CPFCharacter* character) {
    m_eState = 0x204;
    m_bIsFree = 0;
    m_SeekerPosition.m_position.z = seeker->m_position.z;
    m_SeekerPosition.m_position.x = seeker->m_position.x;
    m_SeekerPosition.m_position.y = seeker->m_position.y;
    m_SeekerPosition.m_unk0c = seeker->m_unk0c;
    m_TargetPosition.m_position.x = target->m_position.x;
    m_TargetPosition.m_position.y = target->m_position.y;
    m_TargetPosition.m_position.z = target->m_position.z;
    m_TargetPosition.m_unk0c = target->m_unk0c;
    m_ui32GridPathIndex = 0;
    m_ui32GraphPathSize = 0;
    m_ui32GridPathSize = 0;
    m_ui32GraphPathIndex = 0;
    uint32_t bits = m_Character.m_bits;
    bits = (bits & 0xfffff807u) | (character->m_bits & 0x7f8u);
    bits = (bits & 0xfffff7ffu) | (character->m_bits & 0x800u);
    bits = (bits & 0xffffefffu) | (character->m_bits & 0x1000u);
    m_Character.m_unk04 = character->m_unk04;
    m_Character.m_bits = (bits & 0xfffffff8u) | (character->m_bits & 7u);
    m_vCurrentSeekPoint.x = seeker->m_position.x;
    m_vCurrentSeekPoint.z = seeker->m_position.z;
    m_vCurrentSeekPoint.y = seeker->m_position.y;
}

// 0x001e9fe0 PFPathQuery_Construct_maybe (XXL2 CPFPathSlot::CPFPathSlot). The character's bits get 0x407,
// then 0, as in the original.
CPFPathSlot::CPFPathSlot() {
    m_TargetPosition.m_unk0c = 0xffff;
    m_SeekerPosition.m_unk0c = 0xffff;
    m_Character.m_bits = 0x407;
    m_Character.m_unk08 = 0x1.99999ap-3f;  // 0.2 (0x3e4ccccd)
    m_Character.m_unk0c = 1.0f;
    m_Character.m_bits = 0;
    m_Character.m_unk04 = g_pfGridScale.m_halfCellSize * 0x1.99999ap-3f;
    m_ui32GridPathIndex = 0;
    m_bIsFree = 1;
    m_eState = 0;
    m_ui32GraphPathSize = 0;
    m_ui32GridPathSize = 0;
    m_ui32GraphPathIndex = 0;
}
