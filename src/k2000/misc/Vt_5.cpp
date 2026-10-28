// Vt_5.cpp - reconstructed original translation unit: 0x18ff28-0x190128 (GAME_TOC1, main_toc1), 9 functions, 9 live.
// Primary owner: Vt (not a registered class)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x18ff28  Vt_b1be50_GetObjectA_maybe
//   [x] 0x18ff38  Vt_b1be50_GetObjectB_maybe
//   [x] 0x18ff48  Vt_b1be50_ContactFlagsContainMask_maybe
//   [x] 0x18ffa0  Vt_b1be50_ContactHasAnyFlags_maybe
//   [x] 0x18fff0  Vt_b1be50_GetContactVec18_maybe
//   [x] 0x190028  Vt_b1be50_GetContactVec0C_maybe
//   [x] 0x190060  Vt_b1be50_GetContactFloat08_maybe
//   [x] 0x190098  Vt_b1be50_GetContactFloat04_maybe
//   [x] 0x1900d0  Vt_b1be50_ContactFlagsLowNibbleEquals_maybe
#include "k2000/services/CKSrvCollision.h"

namespace {
// The contact set of a detected contact; 0xc9 = none. The original then reads from the null base (address 0 + the
// field): the getters are only asked about collisions with a set; here such a read gets zeros.
const CContactSet kNoContactSet = {};
const CContactSet* SetOf(const CContactToTest* contact) {
    const uint8_t index = contact->m_ui8ContactSetIndex;
    return index == 0xc9 ? &kNoContactSet : &g_aContactSet[index];
}
// The original's (|x| - 1) >> 31 bit: 1 when x is 0.
uint8_t IsZero(uint32_t x) { return x == 0 ? 1 : 0; }
}  // namespace

// 0x0018ff28 Vt_b1be50_GetObjectA_maybe (XXL2 CCollision::GetBoundingVolume1)
IKSerializable* CCollision::GetBoundingVolume1() { return m_pDetectedContact->m_apBoundingVolume[0]; }

// 0x0018ff38 Vt_b1be50_GetObjectB_maybe (XXL2 GetBoundingVolume2)
IKSerializable* CCollision::GetBoundingVolume2() { return m_pDetectedContact->m_apBoundingVolume[1]; }

// 0x0018ff48 Vt_b1be50_ContactFlagsContainMask_maybe (XXL2 AreResponseParamsActive): every bit of `mask` is among the
// set's response bits (m_Infos & 0xf); no set: 0.
uint8_t CCollision::AreResponseParamsActive(uint32_t mask) {
    if (m_pDetectedContact->m_ui8ContactSetIndex == 0xc9) return 0;
    return IsZero(mask & ~(SetOf(m_pDetectedContact)->m_Infos & 0xfu));
}

// 0x0018ffa0 Vt_b1be50_ContactHasAnyFlags_maybe (XXL2 HasContactSet): the set's m_Infos is not 0; no set: 0.
uint8_t CCollision::HasContactSet() {
    if (m_pDetectedContact->m_ui8ContactSetIndex == 0xc9) return 0;
    return SetOf(m_pDetectedContact)->m_Infos != 0 ? 1 : 0;
}

// 0x0018fff0 Vt_b1be50_GetContactVec18_maybe (XXL2 GetWorldContactPoint)
const CVector3* CCollision::GetWorldContactPoint() { return &SetOf(m_pDetectedContact)->m_WorldContactPoint; }

// 0x00190028 Vt_b1be50_GetContactVec0C_maybe (XXL2 GetNormale12)
const CVector3* CCollision::GetNormale12() { return &SetOf(m_pDetectedContact)->m_Normale12; }

// 0x00190060 Vt_b1be50_GetContactFloat08_maybe (XXL2 GetdInterpenetration)
float CCollision::GetdInterpenetration() { return SetOf(m_pDetectedContact)->m_fdInterpenetration; }

// 0x00190098 Vt_b1be50_GetContactFloat04_maybe (XXL2 GetUDeltaTime)
float CCollision::GetUDeltaTime() { return SetOf(m_pDetectedContact)->m_fUDeltaTime; }

// 0x001900d0 Vt_b1be50_ContactFlagsLowNibbleEquals_maybe (XXL2 IsResponseParamsMaskEqualTo): the set's response bits
// equal `mask` in the low nibble (and `mask` has no other bit); no set: 0.
uint8_t CCollision::IsResponseParamsMaskEqualTo(uint32_t mask) {
    if (m_pDetectedContact->m_ui8ContactSetIndex == 0xc9) return 0;
    return IsZero(mask ^ (SetOf(m_pDetectedContact)->m_Infos & 0xfu));
}
