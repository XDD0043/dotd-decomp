// OnNewHit.cpp - the game manager's combo hit counter (reconstructed original translation unit 0x4fe428-0x4fe5a8).
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x4fe428  OnNewHit
//   [x] 0x4fe568  OnNewHitW
#include "k2000/misc/OnNewHit.h"

#include <cstring>

#include "Spyro2008/groups/IKGrpHero.h"
#include "Spyro2008/hooks/CKHkS08Hero.h"
#include "Spyro2008/logic/CKS08GameManager.h"

// 0x004fe428 OnNewHit: the dragon's hit count (+0xc34 + 4 x dragon, at most 999) grows; its combo timer (+0xc2c + 4 x
// dragon) restarts at the base time (+0xc3c) times the hero's combo timer factor (+0xea0 with +0xed0 bit 24, else 1);
// the first hit starts the combo display (vt+0x360), the others continue it (vt+0x368), with the count / 100.
void OnNewHit(CKS08GameManager* manager, uint8_t dragon, CVector3 /*point*/) {
    const CKHkS08Hero* hero =
        static_cast<const CKHkS08Hero*>(static_cast<IKGrpHero*>(manager->m_unk04[1])->m_apHeros[dragon]);  // 0x002ca080
    const float factor = (hero->m_ui32StatusFlagsED0 & 0x1000000u) != 0 ? hero->m_unkea0 : 1.0f;  // 0x0032a3b0, TOC +0x2688
    float base;
    std::memcpy(&base, &manager->m_unkC3C, sizeof base);
    uint32_t* hits = dragon == 0 ? &manager->m_ui32SpyroComboHits : &manager->m_ui32CynderComboHits;
    float* timer = dragon == 0 ? &manager->m_fSpyroComboTimer : &manager->m_fCynderComboTimer;
    *timer = factor * base;
    uint32_t count = *hits + 1;
    if (count > 999) count = 999;
    *hits = count;
    const float value = static_cast<float>(count) / 100.0f;  // TOC +0x730c
    if (count == 1) {
        manager->OnComboHitComboStart(dragon, value);  // vt+0x360
    } else {
        manager->OnNewHitContinueCombo(dragon, value);  // vt+0x368
    }
}

// 0x004fe568 OnNewHitW: OnNewHit with a copy of the point.
void OnNewHitW(CKS08GameManager* manager, uint8_t dragon, const CVector3* point) {
    OnNewHit(manager, dragon, *point);
}
