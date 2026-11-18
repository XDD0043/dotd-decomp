// Reconstructed original translation unit: 0x2d4be0-0x2d4d48 (GAME_TOC1, main_toc1), 9 functions, 8 live.
// Primary class: CKGrpS08Hero  key 0x984  category Group  size 0xafc  vtable 0xb22b00
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x2d4be0  StaticInitAndDestruction_2d4be0  (the two file statics at the end)
//   [ ] 0x2d4c10  _GLOBAL__D_2d4c10
//   [ ] 0x2d4c20  _GLOBAL__I_2d4c20
//   [x] 0x2d4c30  CKGrpS08Hero_IsExternalLockFree_maybe
//   [x] 0x2d4c40  CKGrpS08Hero_ReleaseExternalLock_maybe
//   [x] 0x2d4c78  CKGrpS08Hero_SetExternalLockPosition_maybe
//   [x] 0x2d4cb8  CKGrpS08Hero_OnEnemyKilled_maybe
//   [x] 0x2d4d10  CKGrpS08Hero_AcquireExternalLock_maybe
//   [ ] 0x2d4d40  KStub_Nop_2d4d40  [dead]
#include "Spyro2008/groups/CKGrpS08Hero.h"

#include <cstdint>
#include <cstring>

namespace {
// DOTD: the lock's owner. The original keeps the pointer in the word at +0x2ec (m_unk2d4[6]); the port keeps the
// word (its low 32 bits) for the layout and compares owners through this (one hero group).
const IKSerializable* s_lockOwner = nullptr;
uint32_t OwnerWord(const IKSerializable* owner) {
    return static_cast<uint32_t>(reinterpret_cast<uintptr_t>(owner));
}
}  // namespace

// 0x002d4c30 CKGrpS08Hero_IsExternalLockFree_maybe
uint8_t CKGrpS08Hero::IsExternalLockFree() const { return static_cast<uint8_t>(~m_unk2c8 & 1u); }

// 0x002d4d10 CKGrpS08Hero_AcquireExternalLock_maybe: taken when free.
void CKGrpS08Hero::AcquireExternalLock(const IKSerializable* owner) {
    if ((m_unk2c8 & 1u) != 0) return;
    m_unk2c8 = (m_unk2c8 & 0xfffffffeu) | 1u;
    m_unk2d4[6] = OwnerWord(owner);  // +0x2ec
    s_lockOwner = owner;
}

// 0x002d4c40 CKGrpS08Hero_ReleaseExternalLock_maybe: by its owner only.
void CKGrpS08Hero::ReleaseExternalLock(const IKSerializable* owner) {
    if ((m_unk2c8 & 1u) == 0 || s_lockOwner != owner) return;
    m_unk2c8 &= 0xfffffffeu;
    m_unk2d4[6] = 0;
    s_lockOwner = nullptr;
}

// 0x002d4c78 CKGrpS08Hero_SetExternalLockPosition_maybe: the tether's middle (+0x2f0), by the owner only.
void CKGrpS08Hero::SetExternalLockPosition(const CVector3* position, const IKSerializable* owner) {
    if ((m_unk2c8 & 1u) == 0 || s_lockOwner != owner) return;
    std::memcpy(&m_unk2d4[7], &position->x, 4);
    std::memcpy(&m_unk2d4[9], &position->z, 4);
    std::memcpy(&m_unk2d4[8], &position->y, 4);
}

// 0x002d4be0 StaticInitAndDestruction_2d4be0 (_GLOBAL__I_2d4c20): two file statics (0x00ceadd8, 0x00ceaddc) set to
// -1.0f. Nothing in the game reads them.
namespace {
[[maybe_unused]] float s_unkceadd8 = -1.0f;
[[maybe_unused]] float s_unkceaddc = -1.0f;
}  // namespace
