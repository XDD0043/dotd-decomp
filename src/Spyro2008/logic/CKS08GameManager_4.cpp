// CKS08GameManager_4.cpp - reconstructed original translation unit 0x4fdb28-0x4fe428 (GAME_TOC1, main_toc1), 14 functions, 13 live.
// Primary class: CKS08GameManager  key 0x784c  category Logic  size 0xf2c  vtable 0xb2af78
// Other owners: DrainDragonFury (1), RestoreDragonMana (1), RestoreDragonHealth (1), IsFuryGaugeFull (1), AddDragonFuryFromAttack (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [ ] 0x4fdb28  DrainDragonFury_maybe
//   [x] 0x4fdc38  CKS08GameManager_vf334
//   [x] 0x4fdca8  RestoreDragonMana
//   [x] 0x4fdef8  RestoreDragonHealth
//   [ ] 0x4fe148  IsFuryGaugeFull_maybe
//   [ ] 0x4fe1a0  AddDragonFuryFromAttack_maybe
//   [ ] 0x4fe2f8  KStub_Return1_4fe2f8
//   [ ] 0x4fe300  KStub_Nop_4fe300
//   [x] 0x4fe308  KStub_Nop_4fe308
//   [ ] 0x4fe310  KStub_Nop_4fe310
//   [ ] 0x4fe318  KStub_Nop_4fe318
//   [ ] 0x4fe320  KStub_Nop_4fe320
//   [ ] 0x4fe328  KStub_Nop_4fe328  [dead]
//   [ ] 0x4fe330  CKS08GameManager_RegisterBossGaugeZone_maybe
#include "Spyro2008/logic/CKS08GameManager.h"

#include "Spyro2008/logic/CKS08GameStructure.h"
#include "k2000/core/Stub.h"

// 0x004fdc38 CKS08GameManager_vf334: with flags +0x64 bit 25 the dragon stats' six bytes +0xb4..+0xb9 set to
// 3, then IKCommonGameManager's (0x4f4900): flags +0x64 bits 8, 20-22 and 24-26 cleared.
void CKS08GameManager::Vf334() {
    if ((m_flags64 & 0x2000000) != 0) {
        CKS08GameStructure* stats = static_cast<CKS08GameStructure*>(m_gameStructure);  // pDragonStats (+0x6c)
        for (uint32_t offset = 0xb4; offset <= 0xb9; ++offset) stats->RtByte(offset) = 3;
    }
    m_flags64 &= 0xf84ffeffu;
}

// 0x004fe308 KStub_Nop_4fe308: empty (CKS08GameManager_Start calls it first).

// 0x004fdca8 RestoreDragonMana: the mana plus `amount`, at most the capacity (unsigned compare); the mana display
// refreshed; unless `quiet`, the dragon's HUD panel (vt+0x34c: [0] Spyro, [2] Cynder) plays its mana clip.
void CKS08GameManager::RestoreDragonMana(int32_t dragon, int32_t amount, int32_t quiet) {
    CKS08GameStructure* stats = static_cast<CKS08GameStructure*>(m_gameStructure);
    if (dragon == 0) {
        const uint32_t sum = static_cast<uint32_t>(amount) + stats->m_unk64;
        if (sum < static_cast<uint32_t>(ComputeSpyroManaCapacity(stats, 0))) {  // 0x00511710
            stats->m_unk64 = static_cast<uint32_t>(amount) + stats->m_unk64;
        } else {
            stats->m_unk64 = static_cast<uint32_t>(ComputeSpyroManaCapacity(stats, 0));
        }
        RefreshDragonStatDisplays(0, 0, 1);  // 0x005022b0
        if (GetHudInterfaces()[0] != nullptr && quiet == 0) {
            // STUB(C2.7: HUD): CKS08InGameInterfaceLeft_QueueManaRestoredClip 0x5395a8 of the left panel.
            DOTD_STUB_ONCE("CKS08InGameInterfaceLeft_QueueManaRestoredClip 0x5395a8 (C2.7)");
        }
    } else if (dragon == 1) {
        const uint32_t sum = static_cast<uint32_t>(amount) + stats->m_unk6c;
        if (sum < static_cast<uint32_t>(ComputeCynderManaCapacity(stats, 0))) {  // 0x005115d0
            stats->m_unk6c = static_cast<uint32_t>(amount) + stats->m_unk6c;
        } else {
            stats->m_unk6c = static_cast<uint32_t>(ComputeCynderManaCapacity(stats, 0));
        }
        RefreshDragonStatDisplays(1, 0, 1);
        if (GetHudInterfaces()[2] != nullptr && quiet == 0) {
            // STUB(C2.7: HUD): CKS08InGameInterfaceRight_QueueManaRestoredClip 0x53ee18 of the right panel.
            DOTD_STUB_ONCE("CKS08InGameInterfaceRight_QueueManaRestoredClip 0x53ee18 (C2.7)");
        }
    }
}

// 0x004fdef8 RestoreDragonHealth: the same for the health (+0x4c / +0x54).
void CKS08GameManager::RestoreDragonHealth(int32_t dragon, int32_t amount, int32_t quiet) {
    CKS08GameStructure* stats = static_cast<CKS08GameStructure*>(m_gameStructure);
    if (dragon == 0) {
        const uint32_t sum = static_cast<uint32_t>(amount) + stats->m_unk4c;
        if (sum < static_cast<uint32_t>(ComputeSpyroHealthCapacity(stats, 0))) {  // 0x005111a0
            stats->m_unk4c = static_cast<uint32_t>(amount) + stats->m_unk4c;
        } else {
            stats->m_unk4c = static_cast<uint32_t>(ComputeSpyroHealthCapacity(stats, 0));
        }
        RefreshDragonStatDisplays(0, 1, 0);  // 0x005022b0
        if (GetHudInterfaces()[0] != nullptr && quiet == 0) {
            // STUB(C2.7: HUD): CKS08InGameInterfaceLeft_QueueHealthRestoredClip 0x539780 of the left panel.
            DOTD_STUB_ONCE("CKS08InGameInterfaceLeft_QueueHealthRestoredClip 0x539780 (C2.7)");
        }
    } else if (dragon == 1) {
        const uint32_t sum = static_cast<uint32_t>(amount) + stats->m_unk54;
        if (sum < static_cast<uint32_t>(ComputeCynderHealthCapacity(stats, 0))) {  // 0x00511060
            stats->m_unk54 = static_cast<uint32_t>(amount) + stats->m_unk54;
        } else {
            stats->m_unk54 = static_cast<uint32_t>(ComputeCynderHealthCapacity(stats, 0));
        }
        RefreshDragonStatDisplays(1, 1, 0);
        if (GetHudInterfaces()[2] != nullptr && quiet == 0) {
            // STUB(C2.7: HUD): CKS08InGameInterfaceRight_QueueHealthRestoredClip 0x53eff0 of the right panel.
            DOTD_STUB_ONCE("CKS08InGameInterfaceRight_QueueHealthRestoredClip 0x53eff0 (C2.7)");
        }
    }
}
