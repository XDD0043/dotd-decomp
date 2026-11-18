// IKGrpEnemy.cpp - reconstructed original translation unit 0x264fa8-0x265b78 (GAME_TOC1, main_toc1), 23 functions, 22 live.
// Primary owner: IKGrpEnemy (not a registered class)
// Other owners: CKChoreoKey (5), Vt (2), AddActiveEncounterEnemy (1), RemoveActiveEncounterEnemy (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [ ] 0x264fa8  _GLOBAL__I_264fa8
//   [x] 0x264fb8  CKChoreoKey_DeleteArray
//   [x] 0x265060  CKChoreoKey_Create
//   [x] 0x2650b0  CKChoreoKey_ClearSlotsTaken_maybe
//   [x] 0x2650f8  CKChoreoKey_CreateArray
//   [x] 0x2651b0  CKChoreoKey_Load
//   [ ] 0x265548  KStub_Nop_265548  [dead: only the second-base vtable 0xb21458 of CKHkS08Enemy +0x1c0 holds it (installed by the enemy constructors / destructors), and no code forms that sub-object's address (no addi 0x1c0 in 0x264000..0x2a8000, none returning it): its slots are never dispatched]
//   [ ] 0x265550  Vt_b21458_Save_maybe  [dead: only the second-base vtable 0xb21458 of CKHkS08Enemy +0x1c0 holds it (installed by the enemy constructors / destructors), and no code forms that sub-object's address (no addi 0x1c0 in 0x264000..0x2a8000, none returning it): its slots are never dispatched]
//   [ ] 0x265870  Vt_b21458_Load_maybe  [dead: only the second-base vtable 0xb21458 of CKHkS08Enemy +0x1c0 holds it (installed by the enemy constructors / destructors), and no code forms that sub-object's address (no addi 0x1c0 in 0x264000..0x2a8000, none returning it): its slots are never dispatched]
//   [x] 0x2659d0  IKGrpEnemy_vfB8  (returns 1: undeclared slot, see IKGrpEnemy.h)
//   [x] 0x2659d8  IKGrpEnemy_ResetRuntime
//   [x] 0x2659e8  IKGrpEnemy_OnLevelExit_maybe  (empty, IKBaseGroup's)
//   [x] 0x2659f0  IKGrpEnemy_vf7C  (empty: IKBaseGroup's Update)
//   [x] 0x2659f8  IKGrpEnemy_ReinitRuntime
//   [x] 0x265a08  IKGrpEnemy_vf150  (returns 1: CKGrpS08Enemy::CanTransferEnemy, see IKGrpEnemy.h)
//   [ ] 0x265a10  KStub_Return0_265a10  [dead]
//   [x] 0x265a18  KStub_Return0_265a18  (returns 0: inline as CKProjectileTypeBallisticPFX.cpp's EnemyGroupHazardSource)
//   [x] 0x265a20  IKGrpEnemy_vf15C
//   [x] 0x265a38  IKGrpEnemy_vf160
//   [x] 0x265a50  AddActiveEncounterEnemy
//   [x] 0x265a78  RemoveActiveEncounterEnemy
//   [x] 0x265b08  IKGrpEnemy_PostLoad
//   [x] 0x265b48  IKGrpEnemy_vf168  (AllocSaveRecord)
//
//   [ ] 0x9bb238  IKGrpEnemy_GetClassGroup  [inline]
//   [ ] 0x9bb240  IKGrpEnemy_GetClassId  [inline]
//   [ ] 0x9bb248  IKGrpEnemy_vfCC  [inline]
//   [ ] 0x9bb250  IKGrpEnemy_vf70  [inline]
//   [ ] 0x9bb258  IKGrpEnemy_vf78  [inline]
//   [ ] 0x9bb260  IKGrpEnemy_vf164  [inline]
//   [ ] 0x9bb268  IKGrpEnemy_vf174  [inline]
//   [ ] 0x9bb270  IKGrpEnemy_IsKindOf  [inline]
//   [ ] 0x9bb2c8  IKGrpEnemy_Destructor  [inline]
//   [ ] 0x9bb390  IKGrpEnemy_DeletingDestructor  [inline]
#include "Spyro2008/groups/CKChoreoKey.h"

#include "k2000/io/IKFile.h"
#include "k2000/memory/Mem.h"
#include "k2000/misc/IKGrpEnemy.h"

// 0x00265a78 RemoveActiveEncounterEnemy (0x265a20 vf15C, 0x265a38 vf160 and 0x265a50 AddActiveEncounterEnemy are
// inline in k2000/misc/IKGrpEnemy.h).
void IKGrpEnemy::RemoveActiveEnemy(IKSerializable* enemy) {
    const uint32_t count = m_ui32NbActiveEnemies;
    if (count == 0) return;
    uint32_t i = 0;
    while (m_apActiveEnemies[i] != enemy) {
        if (++i == count) return;
    }
    m_ui32NbActiveEnemies = count - 1;
    if (count - 1 == i) return;
    m_apActiveEnemies[i] = m_apActiveEnemies[count - 1];
}

// 0x002659d8 IKGrpEnemy_ResetRuntime (Ghidra IKGrpEnemy_Start)
void IKGrpEnemy::Start() {
    m_pCurrentFightZone = nullptr;
}

// 0x002659f8 IKGrpEnemy_ReinitRuntime (vt+0x54, Ghidra IKGrpEnemy_Restart): no current fight zone (Start's body).
void IKGrpEnemy::Restart() {
    m_pCurrentFightZone = nullptr;
}

// 0x002651b0 CKChoreoKey_Load. Types 4..7 (the save restores) read nothing.
int32_t CKChoreoKey::Load(IKFile* file, int32_t type) {
    if (static_cast<uint32_t>(type) - 4u < 4u) return 1;
    uint32_t count = 0;
    ReadU32LE(file, &count);
    // The block is replaced (the old one is not freed). Without positions the capacity is 5 and the count
    // is left alone; the reserve never grows it (it would round up to a multiple of 5).
    if (count == 0) {
        m_asPos.m_ui32NbElt = 5;
        m_asPos.m_pBlock = static_cast<SChoreoPos*>(Mem_AllocAligned16(5u * static_cast<uint32_t>(sizeof(SChoreoPos))));
    } else {
        m_asPos.m_ui32NbElt = count;
        m_asPos.m_pBlock = static_cast<SChoreoPos*>(Mem_AllocAligned16(count * static_cast<uint32_t>(sizeof(SChoreoPos))));
        if (m_asPos.m_ui32NbElt < count) {
            uint32_t capacity = (count / 5u) * 5u + 5u;
            if (capacity == 0) capacity = 5;
            m_asPos.m_pBlock = static_cast<SChoreoPos*>(
                Mem_ReallocAligned16(m_asPos.m_pBlock, capacity * static_cast<uint32_t>(sizeof(SChoreoPos))));
            m_asPos.m_ui32NbElt = capacity;
        }
        m_asPos.m_ui32NbUsedElt = count;
        for (uint32_t i = 0; i < count; ++i) {
            SChoreoPos& pos = m_asPos.m_pBlock[i];
            ReadF32LE(file, &pos.m_vPos.x);  // one 0xc-byte read, then three swaps
            ReadF32LE(file, &pos.m_vPos.y);
            ReadF32LE(file, &pos.m_vPos.z);
            ReadF32LE(file, &pos.m_vDir.x);
            ReadF32LE(file, &pos.m_vDir.y);
            ReadF32LE(file, &pos.m_vDir.z);
            ReadU8(file, &pos.m_ui8Type);
            ReadU8(file, &pos.m_ui8Priority);
            pos.m_bUsed = 0;
        }
    }
    ReadF32LE(file, &m_fKeyDuration);
    ReadU16LE(file, &m_baFlags);
    return 1;
}

// 0x00265b08 IKGrpEnemy_PostLoad: IKLife's, no active enemy.
int32_t IKGrpEnemy::PostLoad(int32_t type) {
    PostLoadLife(type);  // 0x19f68
    m_ui32NbActiveEnemies = 0;
    return 1;
}

// 0x00265b48 IKGrpEnemy_vf168: the save record, zeroed.
void* IKGrpEnemy::AllocSaveRecord() { return Mem_CallocAligned16(1, sizeof(SSaveRecord)); }
