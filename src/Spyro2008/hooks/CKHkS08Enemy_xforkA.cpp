// CKHkS08Enemy_xforkA.cpp - DOTD (C2.7 enemy family, fork A): stubs of the functions declared in CKHkS08Enemy_xforkA.h.
#include "Spyro2008/hooks/CKHkS08Enemy_xforkA.h"

#include "k2000/core/Stub.h"

#include <cstring>

#include "Spyro2008/hooks/CKHkS08Weapon.h"
#include "Spyro2008/logic/CKS08AccessoryManager.h"
#include "Spyro2008/logic/CKS08EnemyElement.h"

// 0x002c78e0 CKS08AccessoryManager_UpdateActiveItems_maybe: the flying accessories (+0x10: data, capacity, count): one
// no longer in use (+0x54) leaves the list (the later ones moved down), the others move (UpdateMotion).
void CKS08AccessoryManager_UpdateActiveItems(IKSerializable* manager, IKTime* clock) {
    CKS08AccessoryManager* accessories = static_cast<CKS08AccessoryManager*>(manager);
    uint32_t count = accessories->m_unk18;
    if (count == 0) return;
    for (uint32_t i = 0; i < count;) {
        CKS08EnemyElement** items = static_cast<CKS08EnemyElement**>(accessories->m_unk10);
        CKS08EnemyElement* item = items[i];
        if (item->m_inUse54 == 0) {
            const uint32_t last = accessories->m_unk18 - 1;
            accessories->m_unk18 = last;
            std::memmove(&items[i], &items[i + 1], (last - i) * sizeof(items[0]));  // TocBridge_memmove
            count = accessories->m_unk18;
            continue;
        }
        ++i;
        item->UpdateMotion(clock);  // 0x0026bb58
    }
}

// CKGrpS08Enemy_vf160 0x2681d0's two calls on a weapon left lying: vt+0xc8 0x002b1558 CKHkS08Weapon_ReturnToPool_maybe
// (back in its enemy-group pool, hidden) and vt+0xcc 0x002b0f08 CKHkS08Weapon_vfCC (empty).
void CKHkS08Weapon_ReleaseAtFightEnd(IKSerializable* weapon) {
    CKHkS08Weapon* w = static_cast<CKHkS08Weapon*>(weapon);
    w->ReturnToPool();  // vt+0xc8
    w->VfCC();          // vt+0xcc
}
