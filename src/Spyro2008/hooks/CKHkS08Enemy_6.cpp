// Reconstructed original translation unit: 0x28b4b0-0x28b910 (GAME_TOC1, main_toc1), 5 functions, 4 live.
// Primary class: CKHkS08Enemy  key 0x26c2  category Hook  size 0x8f8  vtable 0xb22078
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x28b4b0  StaticInitAndDestruction_28b4b0  (the two file statics at the end)
//   [ ] 0x28b4e0  _GLOBAL__D_28b4e0
//   [ ] 0x28b4f0  _GLOBAL__I_28b4f0
//   [x] 0x28b500  CKHkS08Enemy_EmitKind7HotspotParticles_maybe
//   [ ] 0x28b870  CKHkS08Enemy_RefreshShadowCaster_maybe  [dead]
#include "Spyro2008/hooks/CKHkS08Enemy.h"

#include "k2000/logic/CSGHotSpot.h"

// 0x0028b500 CKHkS08Enemy_EmitKind7HotspotParticles_maybe: kind 7's particle points: node 0xd at hot spots 4 and 5,
// node 0x13 at 6 and 7, node 0x14 at 8..13 (each position taken before the emissions of its group).
void CKHkS08Enemy::EmitKind7HotspotParticles() {
    CVector3 p4;
    CVector3 p5;
    GetHotSpot(4)->GetWorldPosition(&p4);  // 0x002892e8, 0x000ce790
    GetHotSpot(5)->GetWorldPosition(&p5);
    EmitParticleAt(0xd, &p4, nullptr, 0);  // 0x00278028
    EmitParticleAt(0xd, &p5, nullptr, 0);
    CVector3 p6;
    CVector3 p7;
    GetHotSpot(6)->GetWorldPosition(&p6);
    GetHotSpot(7)->GetWorldPosition(&p7);
    EmitParticleAt(0x13, &p6, nullptr, 0);
    EmitParticleAt(0x13, &p7, nullptr, 0);
    CVector3 p[6];
    for (int32_t i = 0; i < 6; ++i) GetHotSpot(8 + i)->GetWorldPosition(&p[i]);
    for (int32_t i = 0; i < 6; ++i) EmitParticleAt(0x14, &p[i], nullptr, 0);
}

// 0x0028b4b0 StaticInitAndDestruction_28b4b0: two file statics (0x00ceacd8, 0x00ceacdc) set to -1.0f. Nothing in the game
// reads them (their only references are the initialiser's TOC entries).
namespace {
[[maybe_unused]] float s_unkceacd8 = -1.0f;
[[maybe_unused]] float s_unkceacdc = -1.0f;
}  // namespace
