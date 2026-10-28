// KBase201.cpp - reconstructed original translation unit 0x126268-0x126d20 (GAME_TOC1, main_toc1), 17 functions, 17 live.
// Primary owner: KBase201 (not a registered class)
// Other owners: CKSrvBonus (4), BonusSpawnList (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x126268  KBase201_vf68
//   [ ] 0x126278  CKSrvBonus_SpawnBonuses_maybe
//   [ ] 0x1265b0  CKSrvBonus_SpawnBonusesArgSwap_maybe
//   [ ] 0x1265c0  KBase201_PostLoad
//   [ ] 0x1265e8  KBase201_ClearReferences
//   [ ] 0x126638  KBase201_Shutdown
//   [ ] 0x126688  KBase201_Init
//   [ ] 0x1266d0  CKSrvBonus_ProcessDelayedSpawns_maybe
//   [ ] 0x126840  CKSrvBonus_ConstructBase_maybe
//   [ ] 0x1268d0  BonusSpawnList_Add_maybe
//   [x] 0x126a10  KBase201_Construct
//   [ ] 0x126aa0  KStub_Return1_126aa0
//   [x] 0x126aa8  KBase201_Load
//   [ ] 0x126bd8  KStub_Return1_126bd8
//   [ ] 0x126be0  KBase201_Destructor
//   [ ] 0x126c48  KBase201_BaseDestructor
//   [ ] 0x126cb0  KBase201_DeletingDestructor
//
//   [ ] 0x9a6ff8  KBase201_vf8  [inline]
//   [ ] 0x9a7030  KBase201_vf14  [inline]
//   [ ] 0x9a7038  KBase201_vf18  [inline]
#include "k2000/services/KBase201.h"

#include "k2000/io/IKFile.h"
#include "k2000/misc/Engine.h"

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
