// CKHkS08Enemy_xforkC.cpp - DOTD (C2.7, fork C of the enemy family): functions fork C needs that other forks own, written
// here so that fork C's code builds on its own. The main session merges each into its owner's unit and deletes this file.
#include "Spyro2008/hooks/CKHkS08Enemy.h"

#include "Spyro2008/hooks/CKHkS08EnemyShared.h"
#include "k2000/core/Stub.h"
#include "k2000/misc/IKGrpEnemy.h"

// 0x00265a50 AddActiveEncounterEnemy (fork A: Spyro2008/groups/IKGrpEnemy.cpp). DOTD: the active list is the group's
// run-time words +0x58 (count +0x120), read here as pointers (fork A types the field).
void AddActiveEncounterEnemy(IKGrpEnemy* group, IKHkEnemy* enemy) {
    IKHkEnemy** list = reinterpret_cast<IKHkEnemy**>(group->m_apActiveEnemies);
    const uint32_t count = group->m_ui32NbActiveEnemies;
    group->m_ui32NbActiveEnemies = count + 1;
    list[count] = enemy;
}

// 0x00265a78 RemoveActiveEncounterEnemy (fork A).
void RemoveActiveEncounterEnemy(IKGrpEnemy* group, IKHkEnemy* enemy) {
    IKHkEnemy** list = reinterpret_cast<IKHkEnemy**>(group->m_apActiveEnemies);
    const uint32_t count = group->m_ui32NbActiveEnemies;
    if (count == 0) return;
    uint32_t i = 0;
    while (list[i] != enemy) {
        if (++i == count) return;
    }
    const uint32_t last = count - 1;
    group->m_ui32NbActiveEnemies = last;
    if (last == i) return;
    list[i] = list[last];
}

// Inlined in 0x0027b590 CKHkS08Enemy_RegisterActive (0x27b808..0x27b844): the slot's AnimBlendSlot (+0x04) initialised
// with `controller` (AnimBlendSlot_InitThunk 0x79ff0), then +0x27, +0x1c, +0x24, +0x25, +0x20, +0x26 cleared.
void CKHkS08Enemy::InitAnimLayerSlot(SEnemyAnimLayerSlot* slot, IKSerializable* controller) {
    slot->m_blendSlot.Init(controller);  // 0x0007a710
    slot->m_unk27 = 0;
    slot->m_unk1c = 0.0f;
    slot->m_unk24 = 0;
    slot->m_unk25 = 0;
    slot->m_unk20 = 0.0f;
    slot->m_unk26 = 0;
}
