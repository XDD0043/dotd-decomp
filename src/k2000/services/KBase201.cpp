// KBase201.cpp - reconstructed original translation unit 0x126268-0x126d20 (GAME_TOC1, main_toc1), 17 functions, 17 live.
// Primary owner: KBase201 (not a registered class)
// Other owners: CKSrvBonus (4), BonusSpawnList (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x126268  KBase201_vf68
//   [x] 0x126278  CKSrvBonus_SpawnBonuses_maybe
//   [x] 0x1265b0  CKSrvBonus_SpawnBonusesArgSwap_maybe
//   [x] 0x1265c0  KBase201_PostLoad  (= the inherited slot)
//   [x] 0x1265e8  KBase201_ClearReferences
//   [x] 0x126638  KBase201_Shutdown
//   [x] 0x126688  KBase201_Init
//   [x] 0x1266d0  CKSrvBonus_ProcessDelayedSpawns_maybe
//   [x] 0x126840  CKSrvBonus_ConstructBase_maybe  (= 0x126a10 KBase201_Construct)
//   [x] 0x1268d0  BonusSpawnList_Add_maybe
//   [x] 0x126a10  KBase201_Construct
//   [x] 0x126aa0  KStub_Return1_126aa0  (vt+0x28 Save: returns 1, the root's default)
//   [x] 0x126aa8  KBase201_Load
//   [x] 0x126bd8  KStub_Return1_126bd8  (vt+0x24 RecursiveRegistration: returns 1, the root's empty slot)
//   [x] 0x126be0  KBase201_Destructor
//   [x] 0x126c48  KBase201_BaseDestructor  (= 0x126be0)
//   [x] 0x126cb0  KBase201_DeletingDestructor  (the destructor; delete)
//
//   [ ] 0x9a6ff8  KBase201_vf8  [inline]
//   [ ] 0x9a7030  KBase201_vf14  [inline]
//   [ ] 0x9a7038  KBase201_vf18  [inline]
#include "k2000/services/KBase201.h"

#include "k2000/io/IKFile.h"
#include "k2000/misc/Engine.h"
#include "k2000/components/CKBonusData.h"
#include "k2000/memory/Mem.h"
#include "k2000/misc/CKBonusConfigType.h"
#include "k2000/misc/ClassRegistry.h"
#include "k2000/system/IKTime.h"
#include "crt/ppc_ops.h"

#include <cstring>

// 0x00126a10 KBase201_Construct (0x126840 is an identical copy): the IKService part, the spawn
// vector (grows by 10), the priority, the engine slot, then the references.
KBase201::KBase201() {
    m_vSpawns.m_ui32NbElt = 10;
    m_vSpawns.m_pBlock = nullptr;
    m_vSpawns.m_ui32NbUsedElt = 0;
    m_ui32Priority = 0x3c;
    Engine_SetBonusService(this);
    m_unk20 = nullptr;
    m_unk1c = 0;
}

// 0x00126aa8 KBase201_Load: a byte count, then the references (OperatorNewArray). Every type.
int32_t KBase201::Load(IKFile* file, int32_t /*type*/) {
    ReadU8(file, &m_unk1c);
    if (m_unk1c == 0) {
        m_unk20 = nullptr;
        return 1;
    }
    m_unk20 = new IKSerializable*[m_unk1c];
    IKFile_ReadObjectRefArray(file, m_unk20, m_unk1c);
    return 1;
}

// 0x00126268 KBase201_vf68: the delayed spawn list emptied (its used count, +0x18, set to 0).
void KBase201::Stop() { m_vSpawns.m_ui32NbUsedElt = 0; }

namespace {
constexpr float kUntimed = -1.0f;  // TOC1 -0x4278: a delayed spawn not timed yet
}  // namespace

// 0x00126688 KBase201_Init
int32_t KBase201::InitializeService() {
    m_vSpawns.m_ui32NbElt = 150;
    m_vSpawns.m_pBlock = static_cast<Entry*>(Mem_AllocAligned16(150 * sizeof(Entry)));
    return 1;
}

// 0x00126638 KBase201_Shutdown
void KBase201::DestroyService() {
    if (m_vSpawns.m_pBlock != nullptr) Mem_FreeAligned16(m_vSpawns.m_pBlock);
    m_vSpawns.m_ui32NbUsedElt = 0;
    m_vSpawns.m_pBlock = nullptr;
}

// 0x001266d0 CKSrvBonus_ProcessDelayedSpawns_maybe
void KBase201::Update(IKTime* frameClock) {
    if (frameClock->m_eCurrentState != 0) return;
    m_fNow = frameClock->m_afCurrentTime[IKTime::SCALABLE_GAME_TIME];  // +0x04
    uint32_t i = m_vSpawns.m_ui32NbUsedElt;
    while (i != 0) {
        --i;
        Entry& entry = m_vSpawns.m_pBlock[i];
        if (!(entry.m_fTime <= m_fNow)) continue;
        SpawnBonusWithVelocity(entry.m_kind, entry.m_aPos, entry.m_aVel, 1);  // vt+0xa8
        const uint32_t last = m_vSpawns.m_ui32NbUsedElt - 1;
        m_vSpawns.m_ui32NbUsedElt = last;
        if (i != last) std::memcpy(&m_vSpawns.m_pBlock[i], &m_vSpawns.m_pBlock[last], sizeof(Entry));
    }
}

// 0x001268d0 BonusSpawnList_Add_maybe
void KBase201::AddDelayedSpawn(uint32_t kind, const CVector3* pos, const CVector3* vel) {
    uint32_t used = m_vSpawns.m_ui32NbUsedElt;
    if (m_vSpawns.m_ui32NbElt == used) {
        uint32_t capacity = used + 10;
        if (capacity == 0) capacity = 10;
        m_vSpawns.m_pBlock = static_cast<Entry*>(Mem_ReallocAligned16(m_vSpawns.m_pBlock, capacity * sizeof(Entry)));
        used = m_vSpawns.m_ui32NbUsedElt;
        m_vSpawns.m_ui32NbElt = capacity;
    }
    m_vSpawns.m_ui32NbUsedElt = used + 1;
    Entry& entry = m_vSpawns.m_pBlock[used];
    entry.m_fTime = kUntimed;
    std::memcpy(entry.m_aVel, vel, 12);
    std::memcpy(entry.m_aPos, pos, 12);
    entry.m_kind = kind;
}

// 0x00126278 CKSrvBonus_SpawnBonuses_maybe
void KBase201::SpawnBonuses(CKBonusData* table, const CVector3* pos, const CVector3* dir, const CVector3* base, int32_t onlyMode1) {
    const bool immediate = table->m_unk0c == 0.0f;  // TOC1 -0x4274
    const uint32_t before = m_vSpawns.m_ui32NbUsedElt;
    const uint8_t randomAngle = static_cast<uint8_t>((table->m_unk10 >> 1) & 1u);
    for (uint32_t i = table->m_count; i != 0;) {
        --i;
        CKBonusData::Entry& entry = table->m_pEntries[i];
        if (static_cast<int32_t>(m_unk1c) <= static_cast<int32_t>(entry.m_unk0c)) return;
        const uint32_t mode = entry.m_unk10;
        if (onlyMode1 != 0 ? mode != 1 : mode > 1) continue;
        CKBonusConfigType* layout = static_cast<CKBonusConfigType*>(m_unk20[entry.m_unk0c]);
        layout->GenerateSpawns(&entry, pos, dir, base, immediate ? 1 : 0, randomAngle);  // vt+0x50
    }
    if (immediate) return;
    const uint32_t count = m_vSpawns.m_ui32NbUsedElt;
    for (uint32_t k = count - before; k != 0;) {
        --k;
        if ((table->m_unk10 & 1u) == 0) {
            m_vSpawns.m_pBlock[before + k].m_fTime =
                ppc::fmadds(static_cast<float>(static_cast<double>(k)), table->m_unk0c, m_fNow);
            continue;
        }
        // A random untimed one of the new spawns takes slot k.
        const uint32_t pick = ((static_cast<uint32_t>(Rand_Int()) & 0xffffu) * (k + 1)) >> 16;  // 0x00011500 (mullw)
        uint32_t seen = 0;
        for (uint32_t j = before; j < count; ++j) {
            Entry& entry = m_vSpawns.m_pBlock[j];
            const bool hit = pick == seen;
            if (entry.m_fTime != kUntimed) continue;
            ++seen;
            if (!hit) continue;
            entry.m_fTime = ppc::fmadds(static_cast<float>(static_cast<double>(k)), table->m_unk0c, m_fNow);
            break;
        }
    }
}

// 0x001265e8 KBase201_Destroy
void KBase201::Destroy() {
    if (m_unk20 != nullptr) {
        delete[] m_unk20;  // OperatorDeleteArray
        m_unk20 = nullptr;
    }
}

// 0x00126be0 KBase201_Destructor (0x126c48 _BaseDestructor the same, 0x126cb0 _DeletingDestructor then the delete): the
// delayed-spawn block freed (Shutdown has normally done it; the fields are left).
KBase201::~KBase201() {
    if (m_vSpawns.m_pBlock != nullptr) Mem_FreeAligned16(m_vSpawns.m_pBlock);
}
