// CKS08FightZoneCpnt.cpp - reconstructed original translation unit 0x274b00-0x276f58 (GAME_TOC1, main_toc1), 25 functions, 25 live.
// Primary class: CKS08FightZoneCpnt  key 0x1146  category Component  size 0xb0  vtable 0xb21eb0
// Other owners: IKHkEnemy (4)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x274b00  CKS08FightZoneCpnt_vf50  (empty: see CKS08FightZoneCpnt.h)
//   [x] 0x274b08  CKS08FightZoneCpnt_vf54  (empty: see CKS08FightZoneCpnt.h)
//   [x] 0x274b10  CKS08FightZoneCpnt_vf78
//   [x] 0x274b18  CKS08FightZoneCpnt_GetFirstNonNullRef4C_maybe  (CKS08FightZoneCpnt.h)
//   [x] 0x274b48  CKS08FightZoneCpnt_RecursiveRegistration  (KBaseDC6's (IKSerializable's): inherited)
//   [x] 0x274b70  CKS08FightZoneCpnt_Destroy  (KBaseDC6_ClearReferences only: empty, the default)
//   [x] 0x274b98  CKS08FightZoneCpnt_DeleteArray
//   [x] 0x274c38  CKS08FightZoneCpnt_Create
//   [ ] 0x274ce0  RegisterCKS08FightZoneCpntClass
//   [ ] 0x274d68  _GLOBAL__D_274d68
//   [ ] 0x274d78  _GLOBAL__I_274d78
//   [x] 0x274d88  CKS08FightZoneCpnt_vf6C
//   [x] 0x274dd8  CKS08FightZoneCpnt_vf60
//   [x] 0x274e08  CKS08FightZoneCpnt_vf58
//   [x] 0x274fd0  CKS08FightZoneCpnt_vf7C
//   [x] 0x275050  CKS08FightZoneCpnt_PostLoad  (returns 1: IKSerializable's PostLoad inherited)
//   [x] 0x275058  CKS08FightZoneCpnt_Update_maybe
//   [x] 0x275510  CKS08FightZoneCpnt_CreateArray
//   [x] 0x275630  CKS08FightZoneCpnt_vf68  (ResizeByteVectors)
//   [x] 0x2758c0  CKS08FightZoneCpnt_Load
//   [ ] 0x2765c0  CKS08FightZoneCpnt_Save
//   [x] 0x276f00  IKHkEnemy_ClearReferences  (IKHkEnemy.h Destroy)
//   [x] 0x276f40  IKHkEnemy_ResetRuntime  (empty: IKHkEnemy::Start)
//   [x] 0x276f48  IKHkEnemy_OnLevelExit_maybe  (empty: IKHook's)
//   [x] 0x276f50  IKHkEnemy_vfC8  (empty: IKHkEnemy::VfC8)
//
//   [x] 0x9bc418  CKS08FightZoneCpnt_vf64  [inline]
//   [x] 0x9bc4c8  CKS08FightZoneCpnt_IsKindOfClass  [inline]
//   [x] 0x9bc4f0  CKS08FightZoneCpnt_GetClassType  [inline]
//   [x] 0x9bc4f8  CKS08FightZoneCpnt_GetClassID  [inline]
//   [x] 0x9bc500  CKS08FightZoneCpnt_vf74  [inline]
//   [ ] 0x9bc510  CKS08FightZoneCpnt_vf70  [inline]
//   [ ] 0x9bc518  CKS08FightZoneCpnt_Destructor  [inline]
//   [ ] 0x9bc640  CKS08FightZoneCpnt_DeletingDestructor  [inline]
#include "Spyro2008/components/CKS08FightZoneCpnt.h"

#include "Spyro2008/groups/CKGrpS08Enemy.h"
#include "Spyro2008/hooks/CKHkS08CristalReceiver.h"
#include "Spyro2008/hooks/CKHkS08CrumblyZoneMultiState.h"
#include "Spyro2008/hooks/CKHkS08Egg.h"
#include "Spyro2008/hooks/CKHkS08FogHorn.h"
#include "Spyro2008/logic/CKS08GameManager.h"
#include "k2000/groups/CKGrpSquad.h"
#include "k2000/hooks/CKHkContextualMeca.h"
#include "k2000/core/Stub.h"
#include "k2000/groups/CKGrpFightZone.h"
#include "k2000/groups/TVectorPush.h"
#include "k2000/logic/CDefaultGameManager.h"
#include "k2000/misc/Engine.h"
#include "k2000/memory/Mem.h"
#include "k2000/scenegraph/CSGLeaf.h"
#include "k2000/system/IKTime.h"

// 0x00274dd8 CKS08FightZoneCpnt_vf60: the byte +0xa4 is 1 when the vector at +0x30 is empty (the original's
// |n| - 1 sign bit), 0 otherwise.
void CKS08FightZoneCpnt::Vf60() {
    m_unka8 = 0;
    m_unk94 = 0;
    m_unka4 = m_vUnk30.m_ui32NbUsedElt == 0 ? 1 : 0;
}

// 0x002758c0 CKS08FightZoneCpnt_Load. No type test: every type reads the data.
int32_t CKS08FightZoneCpnt::Load(IKFile* file, int32_t type) {
    KBaseDC6::Load(file, type);
    ReadU32LE(file, &m_unk04);
    ReadF32LE(file, &m_unk18);
    ReadF32LE(file, &m_unk1c);
    ReadU32LE(file, &m_unk20);
    for (uint32_t& w : m_unk24) ReadU32LE(file, &w);
    TVector_LoadRefsCounted(m_vUnk30, file);
    ReadU32LE(file, &m_unk3c);
    ReadF32LE(file, &m_unk0c);
    ReadU8(file, &m_unk10);
    ReadF32LE(file, &m_unk40);
    ReadF32LE(file, &m_unk48);
    IKFile_ReadRef(file, &m_pUnk4c);
    ReadU32LE(file, &m_unk58);
    TVector_LoadRefsCounted(m_vUnk64, file);
    TVector_LoadBytes(m_vUnk70, file);
    TVector_LoadRefsCounted(m_vUnk98, file);
    TVector_LoadBytes(m_vUnk7c, file);
    TVector_LoadBytes(m_vUnk88, file);
    IKFile_ReadRef(file, &m_pUnk50);
    ReadF32LE(file, &m_unk60);
    IKFile_ReadRef(file, &m_pUnk54);
    ReadU8(file, &m_unkac);
    return 1;
}

// 0x00274d88 CKS08FightZoneCpnt_vf6C: how many of the +0x30 objects (the zone's eggs) have their byte +0x30 set (the
// high byte of the egg's big-endian word +0x30).
uint32_t CKS08FightZoneCpnt::CountActiveObjectives() {
    uint32_t count = 0;
    for (uint32_t i = 0; i < m_vUnk30.m_ui32NbUsedElt; ++i) {
        if ((static_cast<const CKHkS08Egg*>(m_vUnk30.m_pBlock[i])->m_unk30 >> 24) != 0) ++count;
    }
    return count;
}

// 0x00274fd0 CKS08FightZoneCpnt_vf7C (the argument is not read): the first +0x30 object whose scene node (+0x1c) has
// bit 2 of its word +0x10 set and whose byte +0x30 is set gets that bit cleared.
void CKS08FightZoneCpnt::Vf7C(uint32_t /*unused*/) {
    for (uint32_t i = 0; i < m_vUnk30.m_ui32NbUsedElt; ++i) {
        const CKHkS08Egg* egg = static_cast<const CKHkS08Egg*>(m_vUnk30.m_pBlock[i]);
        uint32_t* flags = &static_cast<CSGLeaf*>(egg->m_pKGLObject)->m_sgProperties;  // the node (+0x1c)'s word +0x10
        if ((*flags & 4u) != 0 && (egg->m_unk30 >> 24) != 0) {
            *flags &= ~4u;
            return;
        }
    }
}

// 0x00274e08 CKS08FightZoneCpnt_vf58: the zone entered. +0x44 cleared; modes 1 and 2 clear +0x5c; mode 5 (with +0xac)
// totals the crumbly zones' maximum health for the game manager's fight zone gauge.
void CKS08FightZoneCpnt::Vf58() {
    m_unk44 = 0.0f;
    const uint32_t mode = m_unk04;
    if (mode - 1u <= 1u) {
        m_unk5c = 0;
        return;
    }
    if (mode != 5 || m_unkac == 0) return;
    CKS08GameManager* manager = static_cast<CKS08GameManager*>(g_pEngine->m_gameManager);
    const float total = CrumblyZonesHealth(true);
    manager->SetFightZoneGaugeValue(total);  // 0x4fe920
    manager->SetFightZoneGaugeMax(total);    // 0x4fe880
    manager->SetFightZoneGaugeMax2(total);   // 0x4fe7e0
    manager->SendFightZoneHudMessageAndClearTimer();  // 0x501c90
}

// The crumbly zones of +0x98 (the non-null ones of class 0x3582, CKHkS08CrumblyZoneMultiState): their health (0x413fe8)
// or maximum health (0x414098) summed with float adds from 0 (TOC 0xa24).
float CKS08FightZoneCpnt::CrumblyZonesHealth(bool maximum) {
    float total = 0.0f;
    for (uint32_t i = 0; i < m_vUnk98.m_ui32NbUsedElt; ++i) {
        IKSerializable* zone = m_vUnk98.m_pBlock[i];
        if (zone == nullptr || zone->IsKindOfClass(0x3582) == 0) continue;  // vt+0x08
        const CKHkS08CrumblyZoneMultiState* multi = static_cast<CKHkS08CrumblyZoneMultiState*>(zone);
        total = total + (maximum ? multi->GetTotalMaxHealth() : multi->GetTotalHealth());
    }
    return total;
}

// 0x00275058 CKS08FightZoneCpnt_Update_maybe: the zone's objective by mode, then (once, while +0xa4 is clear) the zone's
// trigger starter +0x104 fired when no +0x30 objective is active. Modes 0 and 6: the zone's
// total kills reached its spawn cap (+0x84, unless -1) completes the objective (CompleteObjective, while the zone's
// +0x10d is clear); mode 3: a timer (+0x44, counted while the enemy group's +0x1bc is set) against +0x40; modes 1 and
// 2: a mechanism's progress (+0x4c a CKHkContextualMeca, else +0x50 a CKHkS08FogHorn) reaching 1; mode 4: the crystal
// receivers (+0x64); mode 5: the crumbly zones' health shown on the fight zone gauge.
void CKS08FightZoneCpnt::Update(IKTime* clock) {
    const uint32_t mode = m_unk04;
    CKGrpS08Enemy* enemies = static_cast<CKGrpS08Enemy*>(g_pEngine->m_gameManager->m_unk04[0]);
    if (mode == 3) {
        const float duration = m_unk40;
        if (duration > 0.0f && m_pFightZone->m_unk10d == 0) {
            float elapsed = m_unk44;
            if (enemies->m_unk1bc != 0) {
                elapsed = elapsed + clock->m_afDeltaTime[0];
                m_unk44 = elapsed;
            }
            if (elapsed >= duration) {
                m_unk44 = 0.0f;
                enemies->CompleteObjective();  // 0x2679f0
            }
        }
    } else if (mode == 1) {  // 0x275258: a mechanism's progress; past +0x60 the squads still in their first phase move on
        if (m_pUnk4c != nullptr || m_pUnk50 != nullptr) {  // neither: straight to the tail
            const float ratio = m_pUnk4c != nullptr
                                    ? static_cast<CKHkContextualMeca*>(m_pUnk4c)->GetProgressRatio()  // 0x459c90
                                    : static_cast<CKHkS08FogHorn*>(m_pUnk50)->GetChargeRatio();      // 0x49c278
            if (m_unk60 <= ratio) {  // fcmpu + cror lt|eq
                const TVector<IKSerializable*, 1>& squads = m_pFightZone->m_vUnk40;
                for (uint32_t i = 0; i < squads.m_ui32NbUsedElt; ++i) {
                    CKGrpSquad* squad = static_cast<CKGrpSquad*>(squads.m_pBlock[i]);
                    if (squad->m_unk55 == squad->m_unk54) squad->SetPhase(1);  // 0x25c278
                }
            }
            if (ratio >= 1.0f && m_pFightZone->m_unk10d == 0) enemies->CompleteObjective();  // TOC 0xa20, 0x2679f0
        }
    } else if (mode == 2) {  // 0x2752f0: a mechanism's progress, else (without mechanisms, with +0x54) the kill cap
        float ratio = 0.0f;  // TOC 0xa24
        if (m_pUnk4c != nullptr) {
            ratio = static_cast<CKHkContextualMeca*>(m_pUnk4c)->GetProgressRatio();
        } else if (m_pUnk50 != nullptr) {
            ratio = static_cast<CKHkS08FogHorn*>(m_pUnk50)->GetChargeRatio();
        }
        if (m_pFightZone->m_unk10d == 0) {
            if (ratio >= 1.0f) {
                enemies->CompleteObjective();
            } else if (m_pUnk4c == nullptr && m_pUnk50 == nullptr && m_pUnk54 != nullptr && m_pFightZone->m_unk84 != -1 &&
                       m_pFightZone->m_unk84 <= m_pFightZone->GetTotalKilledCount()) {
                enemies->CompleteObjective();
            }
        }
    } else if (mode == 4) {  // 0x275480: every crystal receiver of +0x64 holds (an empty list completes at once)
        if (m_pFightZone->m_unk10d == 0) {
            bool all = true;
            for (uint32_t i = 0; i < m_vUnk64.m_ui32NbUsedElt; ++i) {
                if (static_cast<CKHkS08CristalReceiver*>(m_vUnk64.m_pBlock[i])->GetTriggerProp96() == 0) {  // 0x483ae0
                    all = false;
                    break;
                }
            }
            if (all) enemies->CompleteObjective();
        }
    } else if ((mode == 0 || mode == 6) && m_pFightZone->m_unk10d == 0) {
        if (m_pFightZone->m_unk84 != -1 && m_pFightZone->m_unk84 <= m_pFightZone->GetTotalKilledCount()) {
            enemies->CompleteObjective();  // 0x271bb8
        }
    } else if (mode == 5 && m_unkac != 0) {  // 0x2750d0: the crumbly zones' health on the fight zone gauge
        CKS08GameManager* manager = static_cast<CKS08GameManager*>(g_pEngine->m_gameManager);
        manager->SetFightZoneGaugeValue(CrumblyZonesHealth(false));  // 0x4fe920
        manager->SendFightZoneHudMessageAndClearTimer();             // 0x501c90
    }
    if (m_unka4 != 0) return;
    if (CountActiveObjectives() != 0) return;  // vt+0x6c
    QueueTriggerSignals(&m_pFightZone->m_aTriggers[11]);  // +0x104
    m_unka4 = 1;
}

namespace {
// The byte push of vf68: a full block grows by one (0 counts as 1), then the zero byte.
void PushZeroByte(TVector<uint8_t, 1>& vector) {
    if (vector.m_ui32NbElt == vector.m_ui32NbUsedElt) {
        uint32_t capacity = vector.m_ui32NbUsedElt + 1;
        if (capacity == 0) capacity = 1;
        vector.m_pBlock = static_cast<uint8_t*>(Mem_ReallocAligned16(vector.m_pBlock, capacity));
        vector.m_ui32NbElt = capacity;
    }
    vector.m_pBlock[vector.m_ui32NbUsedElt] = 0;
    vector.m_ui32NbUsedElt += 1;
}
}  // namespace

// 0x00275630 CKS08FightZoneCpnt_vf68
void CKS08FightZoneCpnt::ResizeByteVectors(uint32_t count) {
    const int32_t delta = static_cast<int32_t>(count - m_vUnk70.m_ui32NbUsedElt);
    if (delta < 0) {
        for (int32_t i = delta; i != 0; ++i) {
            m_vUnk70.m_ui32NbUsedElt -= 1;
            m_vUnk7c.m_ui32NbUsedElt -= 1;
            m_vUnk88.m_ui32NbUsedElt -= 1;
        }
        return;
    }
    for (int32_t i = delta; i > 0; --i) {
        PushZeroByte(m_vUnk70);
        PushZeroByte(m_vUnk7c);
        PushZeroByte(m_vUnk88);
    }
}
