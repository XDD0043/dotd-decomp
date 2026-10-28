// CKHkS08Enemy_9.cpp - reconstructed original translation unit 0x294b68-0x29d290 (GAME_TOC1, main_toc1), 31 functions, 31 live.
// Primary class: CKHkS08Enemy  key 0x26c2  category Hook  size 0x8f8  vtable 0xb22078
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [ ] 0x294b68  CKHkS08Enemy_MessageProc
//   [ ] 0x294d20  CKHkS08Enemy_Save
//   [x] 0x2951a0  CKHkS08Enemy_Load
//   [ ] 0x2962b8  CKHkS08Enemy_Update
//   [ ] 0x297160  CKHkS08Enemy_vf210
//   [ ] 0x297168  CKHkS08Enemy_vf214
//   [ ] 0x297170  CKHkS08Enemy_PendingDamageCausesHitReaction_maybe
//   [ ] 0x297250  CKHkS08Enemy_InitHitReactionStateMachine_maybe
//   [ ] 0x297408  StaticInitAndDestruction_297408
//   [ ] 0x297438  _GLOBAL__D_297438
//   [ ] 0x297448  _GLOBAL__I_297448
//   [ ] 0x297458  CKHkS08Enemy_vf21C
//   [ ] 0x297568  CKHkS08Enemy_ReactSM0B_GetUp_maybe
//   [ ] 0x2977c0  CKHkS08Enemy_ReactSM01_Burning_maybe
//   [ ] 0x297950  CKHkS08Enemy_PlayDirectionalHurtAnim_maybe
//   [ ] 0x298430  CKHkS08Enemy_UpdateHurtAnimPlayback_maybe
//   [ ] 0x2987c8  CKHkS08Enemy_IntegrateKnockbackMotion_maybe
//   [ ] 0x298d68  CKHkS08Enemy_ReactSM10_KnockbackAnim_maybe
//   [ ] 0x298e08  CKHkS08Enemy_ReactSM00_DispatchHit_maybe
//   [ ] 0x298ff0  CKHkS08Enemy_ReactSM05_Stunned_maybe
//   [ ] 0x299188  CKHkS08Enemy_ReactSM04_StunGaugeDrain_maybe
//   [ ] 0x2993e8  CKHkS08Enemy_ReactSM06_Airborne_maybe
//   [ ] 0x299708  CKHkS08Enemy_ReactSM03_HurtCheckStun_maybe
//   [ ] 0x2998d0  CKHkS08Enemy_ReactSM02_Hurt_maybe
//   [ ] 0x299f30  CKHkS08Enemy_ApplyPendingDamage
//   [ ] 0x29bd40  CKHkS08Enemy_ReactSM0F_DeathAnim_maybe
//   [ ] 0x29c018  CKHkS08Enemy_ReactSM0D_maybe
//   [ ] 0x29c148  CKHkS08Enemy_ReactSM0E_FallUntilGrounded_maybe
//   [ ] 0x29c350  CKHkS08Enemy_ReactSM08_Launched_maybe
//   [ ] 0x29c998  CKHkS08Enemy_ReactSM07_Knockdown_maybe
//   [ ] 0x29d078  CKHkS08Enemy_FindFreeWeapon
#include "Spyro2008/hooks/CKHkS08Enemy.h"

#include "k2000/io/IKFile.h"
#include "k2000/memory/Mem.h"

namespace {
// 0x00a701d8 (TOC +0x105c): the reference count per enemy kind (IKHkEnemy::m_ui8EnemyClassType), read only
// by CKHkS08Enemy_Load. 16 bytes before the next object (0xa701e8); nine kinds_maybe.
const uint8_t kEnemyRefCount[16] = {3, 1, 5, 4, 5, 7, 9, 0, 4, 0, 0, 0, 0, 0, 0, 0};

// The inlined TVector reserve: a vector without a block gets one element (capacity 1).
template <class T>
void EnsureBlock(TVector<T, 1>& vector) {
    if (vector.m_pBlock == nullptr) {
        vector.m_ui32NbElt = 1;
        vector.m_pBlock = static_cast<T*>(Mem_AllocAligned16(static_cast<uint32_t>(sizeof(T))));
    }
}

// The inlined resize to count elements: the block grows to count + 1 when the capacity is below count.
template <class T>
void Resize(TVector<T, 1>& vector, uint32_t count) {
    EnsureBlock(vector);
    if (vector.m_ui32NbElt < count) {
        uint32_t capacity = count + 1;
        if (capacity == 0) capacity = 1;
        vector.m_pBlock = static_cast<T*>(
            Mem_ReallocAligned16(vector.m_pBlock, capacity * static_cast<uint32_t>(sizeof(T))));
        vector.m_ui32NbElt = capacity;
    }
    vector.m_ui32NbUsedElt = count;
}

// The inlined push of a null element (growth step 1).
void PushNull(TVector<void*, 1>& vector) {
    if (vector.m_ui32NbElt == vector.m_ui32NbUsedElt) {
        uint32_t capacity = vector.m_ui32NbUsedElt + 1;
        if (capacity == 0) capacity = 1;
        vector.m_pBlock = static_cast<void**>(
            Mem_ReallocAligned16(vector.m_pBlock, capacity * static_cast<uint32_t>(sizeof(void*))));
        vector.m_ui32NbElt = capacity;
    }
    vector.m_pBlock[vector.m_ui32NbUsedElt] = nullptr;
    vector.m_ui32NbUsedElt++;
}

// One reference vector: the file's count, the vector sized by the kind's count. The first min of the two
// references go into the vector; extra file references are read and dropped; missing ones are nulls.
// With `nulls`, every element (read, dropped or nulled) also pushes a null into it.
void ReadRefVector(IKFile* file, TVector<IKSerializable*, 1>& vector, uint32_t kindCount,
                   TVector<void*, 1>* nulls) {
    uint32_t count = 0;
    ReadU32LE(file, &count);
    Resize(vector, kindCount);
    if (kindCount < count) {
        for (uint32_t i = 0; i < kindCount; ++i) {
            IKFile_ReadRef(file, &vector.m_pBlock[i]);
            if (nulls != nullptr) PushNull(*nulls);
        }
        for (uint32_t i = kindCount; i < count; ++i) {
            IKSerializable* dropped = nullptr;
            IKFile_ReadRef(file, &dropped);
            if (nulls != nullptr) PushNull(*nulls);
        }
    } else {
        for (uint32_t i = 0; i < count; ++i) {
            IKFile_ReadRef(file, &vector.m_pBlock[i]);
            if (nulls != nullptr) PushNull(*nulls);
        }
        for (uint32_t i = count; i < kindCount; ++i) {
            vector.m_pBlock[i] = nullptr;
            if (nulls != nullptr) PushNull(*nulls);
        }
    }
}
}  // namespace

// 0x002951a0 CKHkS08Enemy_Load. No branch on the type after IKHkEnemy's part.
int32_t CKHkS08Enemy::Load(IKFile* file, int32_t type) {
    IKHkEnemy::Load(file, type);
    EnsureBlock(m_unk4E4);
    EnsureBlock(m_unk4F0);
    EnsureBlock(m_unk4FC);
    EnsureBlock(m_unk508);
    EnsureBlock(m_unk514);
    ReadRefVector(file, m_unk4E4, kEnemyRefCount[m_ui8EnemyClassType], &m_unk514);
    ReadU8(file, &m_unk730);
    IKFile_ReadRef(file, &m_unk734);
    IKFile_ReadRef(file, &m_unk784);
    ReadRefVector(file, m_unk4F0, kEnemyRefCount[m_ui8EnemyClassType], nullptr);
    ReadRefVector(file, m_unk4FC, kEnemyRefCount[m_ui8EnemyClassType], nullptr);
    ReadRefVector(file, m_unk508, kEnemyRefCount[m_ui8EnemyClassType], nullptr);
    IKFile_ReadRef(file, &m_unk88C);
    return 1;
}
