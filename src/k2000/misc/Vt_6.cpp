// Vt_6.cpp - reconstructed original translation unit: 0x19ce30-0x19d020 (GAME_TOC1, main_toc1), 9 functions, 9 live.
// Primary owner: Vt (not a registered class)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x19ce30  Vt_b1c010_GetDynSphereProjectileNode_maybe
//   [x] 0x19ce50  Vt_b1c010_GetProjectileTarget_maybe
//   [x] 0x19ce88  Vt_b1c010_ContactHasAnyFlags_maybe
//   [x] 0x19ced0  Vt_b1c010_ContactFlagsContainMask_maybe
//   [x] 0x19cf28  Vt_b1c010_ContactFlagsLowNibbleEquals_maybe
//   [x] 0x19cf80  Vt_b1c010_GetContactFloat04_maybe
//   [x] 0x19cfa8  Vt_b1c010_GetContactFloat08_maybe
//   [x] 0x19cfd0  Vt_b1c010_GetContactVec0C_maybe
//   [x] 0x19cff8  Vt_b1c010_GetContactVec18_maybe
#include "k2000/services/CKSrvCollision.h"

namespace {
uint8_t IsZero(uint32_t x) { return x == 0 ? 1 : 0; }
}  // namespace

// 0x0019ce30 Vt_b1c010_GetDynSphereProjectileNode_maybe (XXL2 CProjectileCollision::GetBoundingVolume1): the
// projectile's volume.
IKSerializable* CProjectileCollision::GetBoundingVolume1() { return g_aProjectile[m_ui8ProjectileIndex].m_pBoundingVolume; }

// 0x0019ce50 Vt_b1c010_GetProjectileTarget_maybe (XXL2 GetBoundingVolume2): the target's volume.
IKSerializable* CProjectileCollision::GetBoundingVolume2() {
    return g_aProjectileTarget[m_ui16TargetIndex].m_apBoundingVolume[m_ui8TargetBoundingVolumeIndex];
}

// 0x0019ce88 Vt_b1c010_ContactHasAnyFlags_maybe
uint8_t CProjectileCollision::HasContactSet() {
    if (m_ui8ContactSetIndex == 0xc9) return 0;
    return g_aContactSet[m_ui8ContactSetIndex].m_Infos != 0 ? 1 : 0;
}

// 0x0019ced0 Vt_b1c010_ContactFlagsContainMask_maybe
uint8_t CProjectileCollision::AreResponseParamsActive(uint32_t mask) {
    if (m_ui8ContactSetIndex == 0xc9) return 0;
    return IsZero(mask & ~(g_aContactSet[m_ui8ContactSetIndex].m_Infos & 0xfu));
}

// 0x0019cf28 Vt_b1c010_ContactFlagsLowNibbleEquals_maybe
uint8_t CProjectileCollision::IsResponseParamsMaskEqualTo(uint32_t mask) {
    if (m_ui8ContactSetIndex == 0xc9) return 0;
    return IsZero(mask ^ (g_aContactSet[m_ui8ContactSetIndex].m_Infos & 0xfu));
}

// 0x0019cf80 Vt_b1c010_GetContactFloat04_maybe (no 0xc9 test: a projectile collision always has a set)
float CProjectileCollision::GetUDeltaTime() { return g_aContactSet[m_ui8ContactSetIndex].m_fUDeltaTime; }

// 0x0019cfa8 Vt_b1c010_GetContactFloat08_maybe
float CProjectileCollision::GetdInterpenetration() { return g_aContactSet[m_ui8ContactSetIndex].m_fdInterpenetration; }

// 0x0019cfd0 Vt_b1c010_GetContactVec0C_maybe
const CVector3* CProjectileCollision::GetNormale12() { return &g_aContactSet[m_ui8ContactSetIndex].m_Normale12; }

// 0x0019cff8 Vt_b1c010_GetContactVec18_maybe
const CVector3* CProjectileCollision::GetWorldContactPoint() {
    return &g_aContactSet[m_ui8ContactSetIndex].m_WorldContactPoint;
}
