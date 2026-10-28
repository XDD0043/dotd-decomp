// Reconstructed original translation unit: 0x291478-0x294b18 (GAME_TOC1, main_toc1), 28 functions, 26 live.
// Primary class: CKHkS08Enemy  key 0x26c2  category Hook  size 0x8f8  vtable 0xb22078
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [ ] 0x291478  CKHkS08Enemy_vfD4
//   [ ] 0x291480  CKHkS08Enemy_ReleaseAllElements_maybe  [dead]
//   [ ] 0x2915e8  CKHkS08Enemy_DropShield
//   [ ] 0x2916f0  CKHkS08Enemy_DetachWeapon_maybe
//   [ ] 0x2917e0  CKHkS08Enemy_AttachRandomAccessories_maybe
//   [ ] 0x291e60  CKHkS08Enemy_vfC8
//   [x] 0x291e88  CKHkS08Enemy_ResetRuntimeState_maybe
//   [ ] 0x292008  StaticInitAndDestruction_292008
//   [ ] 0x292038  _GLOBAL__D_292038
//   [ ] 0x292048  _GLOBAL__I_292048
//   [ ] 0x292058  CKHkS08Enemy_ConstrainToGroundAndNavMesh_maybe
//   [ ] 0x292278  CKHkS08Enemy_ReleaseElement_maybe  [dead]
//   [ ] 0x2923c8  CKHkS08Enemy_CanSpawnFromSquad_maybe
//   [ ] 0x292710  CKHkS08Enemy_AttachRandomShield
//   [ ] 0x292a10  CKHkS08Enemy_EquipWeapon_maybe
//   [ ] 0x292b40  CKHkS08Enemy_AttachRandomWeapon
//   [ ] 0x292e60  CKHkS08Enemy_Activate
//   [ ] 0x2937c8  CKHkS08Enemy_SpawnAtPosition_maybe
//   [ ] 0x293cb0  CKHkS08Enemy_Deactivate
//   [ ] 0x294860  CKHkS08Enemy_Restart
//   [ ] 0x294868  CKHkS08Enemy_Pause
//   [ ] 0x294870  CKHkS08Enemy_Resume
//   [ ] 0x294878  CKHkS08Enemy_InitMainStateMachine
//   [ ] 0x294a50  CKHkS08Enemy_Stop
//   [x] 0x294a78  CKHkS08Enemy_Start
//   [x] 0x294aa0  CKHkS08Enemy_PostLoad
//   [ ] 0x294ac8  CKHkS08Enemy_RecursiveRegistration
//   [ ] 0x294af0  CKHkS08Enemy_Destroy
#include "Spyro2008/hooks/CKHkS08Enemy.h"

// 0x00291e88 CKHkS08Enemy_ResetRuntimeState_maybe
void CKHkS08Enemy::ResetRuntimeState() {
    ResetMovementState();  // 0x00277df8
    m_unk290 = 0;
    m_unk298 = 0;
    m_unk238 = 0;
    m_unk239 = 0;
    m_unk25c = 0;
    m_unk260 = 0;
    m_unk264 = 0;
    m_unk294 = 0;
    m_unk2a4 = 0;
    m_unk2a8 = 0;
    m_unk2ac = 0;
    for (uint32_t i = 0; i < 30; ++i) m_unk2b0[i] = 0;
    m_unk344 = 0;
    m_unk32c = 0;
    m_unk330 = 0;
    m_unk348 = 0;
    m_unk328 = 0;
    m_bitArray = m_bitArray & 0xfff8ffffu;
    m_unk35c = 0;
    m_unk358 = 0;
    // the zero vector 0x00c50d64 twice
    m_unk364 = 0.0f;
    m_unk36c = 0.0f;
    m_unk368 = 0.0f;
    m_unk370 = 0.0f;
    m_unk378 = 0.0f;
    m_unk374 = 0.0f;
    m_unk37c = m_v3Position.x;
    m_unk384 = m_v3Position.z;
    m_unk380 = m_v3Position.y;
    // the unit X vector 0x00c50d34 (TOC1 +0xf9c)
    m_unk388 = 1.0f;
    m_unk38c = 0.0f;
    m_unk390 = 0.0f;
    m_unk394 = 1;
    m_unk398 = 0;
    m_PFCpnt.m_CharacterType.m_bits |= 0xf0u;
    m_unk1ee = 0;
}

// 0x00294aa0 CKHkS08Enemy_PostLoad
int32_t CKHkS08Enemy::PostLoad(int32_t type) {
    IKHkEnemy::PostLoad(type);  // 0x00277528
    return 1;
}

// 0x00294a78 CKHkS08Enemy_Start
void CKHkS08Enemy::Start() {
    IKHkEnemy::Start();  // 0x276f40, empty
}
