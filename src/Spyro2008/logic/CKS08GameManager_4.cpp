// CKS08GameManager_4.cpp - reconstructed original translation unit 0x4fdb28-0x4fe428 (GAME_TOC1, main_toc1), 14 functions, 13 live.
// Primary class: CKS08GameManager  key 0x784c  category Logic  size 0xf2c  vtable 0xb2af78
// Other owners: DrainDragonFury (1), RestoreDragonMana (1), RestoreDragonHealth (1), IsFuryGaugeFull (1), AddDragonFuryFromAttack (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x4fdb28  DrainDragonFury_maybe
//   [x] 0x4fdc38  CKS08GameManager_vf334
//   [x] 0x4fdca8  RestoreDragonMana
//   [x] 0x4fdef8  RestoreDragonHealth
//   [x] 0x4fe148  IsFuryGaugeFull_maybe
//   [x] 0x4fe1a0  AddDragonFuryFromAttack_maybe
//   [x] 0x4fe2f8  KStub_Return1_4fe2f8  (nothing: in CKS08GameManager::RecursiveRegistration)
//   [x] 0x4fe300  KStub_Nop_4fe300  (nothing: in CKS08GameManager::Save)
//   [x] 0x4fe308  KStub_Nop_4fe308
//   [x] 0x4fe310  KStub_Nop_4fe310  (empty; no live reference)
//   [x] 0x4fe318  KStub_Nop_4fe318  (empty; no live reference)
//   [x] 0x4fe320  KStub_Nop_4fe320  (empty; no live reference)
//   [ ] 0x4fe328  KStub_Nop_4fe328  [dead]
//   [x] 0x4fe330  CKS08GameManager_RegisterBossGaugeZone_maybe
#include "Spyro2008/logic/CKS08GameManager.h"
#include "k2000/memory/Mem.h"
#include "k2000/components/CKCurve2DCpnt.h"

#include "Spyro2008/logic/CKS08GameStructure.h"
#include "Spyro2008/logic/CKS08InGameInterfaceCenter.h"
#include "Spyro2008/logic/CKS08InGameInterfaceLeft.h"
#include "Spyro2008/logic/CKS08InGameInterfaceRight.h"
#include "k2000/core/Stub.h"
#include "crt/ppc_ops.h"

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
        const uint32_t sum = static_cast<uint32_t>(amount) + stats->m_dwSpyroMana;
        if (sum < static_cast<uint32_t>(ComputeSpyroManaCapacity(stats, 0))) {  // 0x00511710
            stats->m_dwSpyroMana = static_cast<uint32_t>(amount) + stats->m_dwSpyroMana;
        } else {
            stats->m_dwSpyroMana = static_cast<uint32_t>(ComputeSpyroManaCapacity(stats, 0));
        }
        RefreshDragonStatDisplays(0, 0, 1);  // 0x005022b0
        if (GetHudInterfaces()[0] != nullptr && quiet == 0) {
            static_cast<CKS08InGameInterfaceLeft*>(GetHudInterfaces()[0])->QueueManaRestoredClip();  // 0x5395a8
        }
    } else if (dragon == 1) {
        const uint32_t sum = static_cast<uint32_t>(amount) + stats->m_dwCynderMana;
        if (sum < static_cast<uint32_t>(ComputeCynderManaCapacity(stats, 0))) {  // 0x005115d0
            stats->m_dwCynderMana = static_cast<uint32_t>(amount) + stats->m_dwCynderMana;
        } else {
            stats->m_dwCynderMana = static_cast<uint32_t>(ComputeCynderManaCapacity(stats, 0));
        }
        RefreshDragonStatDisplays(1, 0, 1);
        if (GetHudInterfaces()[2] != nullptr && quiet == 0) {
            static_cast<CKS08InGameInterfaceRight*>(GetHudInterfaces()[2])->QueueManaRestoredClip();  // 0x53ee18
        }
    }
}

// 0x004fdef8 RestoreDragonHealth: the same for the health (+0x4c / +0x54).
void CKS08GameManager::RestoreDragonHealth(int32_t dragon, int32_t amount, int32_t quiet) {
    CKS08GameStructure* stats = static_cast<CKS08GameStructure*>(m_gameStructure);
    if (dragon == 0) {
        const uint32_t sum = static_cast<uint32_t>(amount) + stats->m_dwSpyroHealth;
        if (sum < static_cast<uint32_t>(ComputeSpyroHealthCapacity(stats, 0))) {  // 0x005111a0
            stats->m_dwSpyroHealth = static_cast<uint32_t>(amount) + stats->m_dwSpyroHealth;
        } else {
            stats->m_dwSpyroHealth = static_cast<uint32_t>(ComputeSpyroHealthCapacity(stats, 0));
        }
        RefreshDragonStatDisplays(0, 1, 0);  // 0x005022b0
        if (GetHudInterfaces()[0] != nullptr && quiet == 0) {
            static_cast<CKS08InGameInterfaceLeft*>(GetHudInterfaces()[0])->QueueHealthRestoredClip();  // 0x539780
        }
    } else if (dragon == 1) {
        const uint32_t sum = static_cast<uint32_t>(amount) + stats->m_dwCynderHealth;
        if (sum < static_cast<uint32_t>(ComputeCynderHealthCapacity(stats, 0))) {  // 0x00511060
            stats->m_dwCynderHealth = static_cast<uint32_t>(amount) + stats->m_dwCynderHealth;
        } else {
            stats->m_dwCynderHealth = static_cast<uint32_t>(ComputeCynderHealthCapacity(stats, 0));
        }
        RefreshDragonStatDisplays(1, 1, 0);
        if (GetHudInterfaces()[2] != nullptr && quiet == 0) {
            static_cast<CKS08InGameInterfaceRight*>(GetHudInterfaces()[2])->QueueHealthRestoredClip();  // 0x53eff0
        }
    }
}

// 0x004fe1a0 AddDragonFuryFromAttack_maybe
void CKS08GameManager::AddDragonFuryFromAttack(uint8_t dragon, uint32_t hits) {
    const float amount = static_cast<float>(static_cast<double>(static_cast<int64_t>(hits)));  // fcfid of the word
    const float scale = static_cast<const CKCurve2DCpnt*>(m_pFuryComboCurve)->Evaluate(amount);  // 0x00249ea8
    const uint32_t gain = static_cast<uint32_t>(static_cast<int64_t>(amount * scale));  // fctidz
    CKS08GameStructure* structure = static_cast<CKS08GameStructure*>(m_gameStructure);
    if (dragon == 0) {
        if (structure->m_dwSpyroFury + structure->m_dwCynderFury + gain < structure->m_dwMaxTotalFury) {
            structure->m_dwSpyroFury = structure->m_dwSpyroFury + gain;
        } else {
            structure->m_dwSpyroFury = structure->m_dwMaxTotalFury - structure->m_dwCynderFury;
        }
    } else if (dragon == 1) {
        if (structure->m_dwCynderFury + structure->m_dwSpyroFury + gain < structure->m_dwMaxTotalFury) {
            structure->m_dwCynderFury = structure->m_dwCynderFury + gain;
        } else {
            structure->m_dwCynderFury = structure->m_dwMaxTotalFury - structure->m_dwSpyroFury;
        }
    }
    RefreshFuryGaugeHud();  // 0x004fec98
}

// 0x004fdb28 DrainDragonFury_maybe: with `shared`, both dragons' fury becomes half the total less half `amount` (each
// half a float product truncated by fctidz; the low words kept), or 0 when `amount` reaches the total; else `amount` is
// taken from dragon 0's or 1's fury (down to 0). Unsigned compares.
void CKS08GameManager::DrainDragonFury(int32_t dragon, uint32_t amount, int32_t shared) {
    CKS08GameStructure* structure = static_cast<CKS08GameStructure*>(m_gameStructure);  // +0x6c
    if (shared != 0) {
        const uint32_t total = structure->m_dwSpyroFury + structure->m_dwCynderFury;
        if (!(amount < total)) {  // bge
            structure->m_dwSpyroFury = 0;
            structure->m_dwCynderFury = 0;
            return;
        }
        const float half = static_cast<float>(static_cast<double>(amount)) * 0.5f;  // TOC +0x72c8
        const float totalHalf = static_cast<float>(static_cast<double>(total)) * 0.5f;
        const uint32_t halfWord = static_cast<uint32_t>(ppc::fctidz(half));
        const float rest = totalHalf - static_cast<float>(static_cast<double>(halfWord));
        structure->m_dwSpyroFury = static_cast<uint32_t>(ppc::fctidz(rest));
        structure->m_dwCynderFury = structure->m_dwSpyroFury;
        return;
    }
    if (dragon == 0) {
        structure->m_dwSpyroFury = amount < structure->m_dwSpyroFury ? structure->m_dwSpyroFury - amount : 0;
    } else if (dragon == 1) {
        structure->m_dwCynderFury = amount < structure->m_dwCynderFury ? structure->m_dwCynderFury - amount : 0;
    }
}

// 0x004fd680 GetDragonFury_maybe
uint32_t CKS08GameManager::GetDragonFury(int32_t dragon) {
    const CKS08GameStructure* structure = static_cast<const CKS08GameStructure*>(m_gameStructure);
    if (dragon == 0) return structure->m_dwSpyroFury;
    if (dragon != 1) return 0;
    return structure->m_dwCynderFury;
}

// 0x004fd420 GetTotalFury_maybe
uint32_t CKS08GameManager::GetTotalFury() {
    const CKS08GameStructure* structure = static_cast<const CKS08GameStructure*>(m_gameStructure);
    return structure->m_dwSpyroFury + structure->m_dwCynderFury;
}

// 0x004fec98 RefreshFuryGaugeHud_maybe: the centre interface (the HUD list's [1], vt+0x34c, read three times) shows its
// fury gauge (CKS08InGameInterfaceCenter_ShowFuryGauge_maybe 0x5353d0) unless it is already shown (+0x201).
void CKS08GameManager::RefreshFuryGaugeHud() {
    if (GetHudInterfaces()[1] == nullptr) return;
    if (static_cast<CKS08InGameInterfaceCenter*>(GetHudInterfaces()[1])->m_ui8FuryShown201 != 0) return;
    static_cast<CKS08InGameInterfaceCenter*>(GetHudInterfaces()[1])->ShowFuryGauge();
}

// 0x004fe148 IsFuryGaugeFull_maybe
uint8_t CKS08GameManager::IsFuryGaugeFull(uint32_t* capacity) {
    const CKS08GameStructure* stats = static_cast<const CKS08GameStructure*>(m_gameStructure);  // +0x6c
    *capacity = stats->m_dwMaxTotalFury;
    if ((m_flags64 & 0x1000000u) != 0) return 1;
    // (|sum ^ cap| - 1) >> 31: the sum equal to the cap.
    return stats->m_dwSpyroFury + stats->m_dwCynderFury == stats->m_dwMaxTotalFury ? 1 : 0;
}

// 0x004fe330 CKS08GameManager_RegisterBossGaugeZone_maybe
void CKS08GameManager::RegisterBossGaugeZone(IKSerializable* zone) {
    TVector<IKSerializable*, 5>& zones = m_unkBB4;
    for (uint32_t i = 0; i < zones.m_ui32NbUsedElt; ++i) {
        if (zones.m_pBlock[i] == zone) return;
    }
    if (zones.m_ui32NbElt == zones.m_ui32NbUsedElt) {
        uint32_t capacity = zones.m_ui32NbElt + 5;
        if (capacity == 0) capacity = 5;
        zones.m_pBlock = static_cast<IKSerializable**>(
            Mem_ReallocAligned16(zones.m_pBlock, capacity * static_cast<uint32_t>(sizeof(IKSerializable*))));
        zones.m_ui32NbElt = capacity;
    }
    zones.m_pBlock[zones.m_ui32NbUsedElt] = zone;
    ++zones.m_ui32NbUsedElt;
}
