// CKS08MaleforBigBombDeathBall.cpp - reconstructed original translation unit 0x4e7ac0-0x4e9120 (GAME_TOC1, main_toc1), 27 functions, 26 live.
// Primary class: CKS08MaleforBigBombDeathBall  key 0xac0c  category Logic  size 0xd4  vtable 0xb2a790
// Other owners: CKS08MaleforColdBall (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x4e7ac0  CKS08MaleforBigBombDeathBall_Delete
//   [ ] 0x4e7b10  RegisterCKS08MaleforBigBombDeathBallClass
//   [ ] 0x4e7b88  _GLOBAL__I_4e7b88
//   [ ] 0x4e7b98  CKS08MaleforBigBombDeathBall_Explode
//   [ ] 0x4e7ef0  CKS08MaleforBigBombDeathBall_vf5C
//   [ ] 0x4e7f18  CKS08MaleforBigBombDeathBall_AttachVolumesToHotSpots_maybe
//   [ ] 0x4e7f40  CKS08MaleforBigBombDeathBall_StopAttack_maybe
//   [ ] 0x4e7f68  CKS08MaleforBigBombDeathBall_StartAttack_maybe
//   [ ] 0x4e7fa0  CKS08MaleforBigBombDeathBall_PostLoad
//   [ ] 0x4e7fc8  CKS08MaleforBigBombDeathBall_Save
//   [ ] 0x4e7ff0  CKS08MaleforBigBombDeathBall_RecursiveRegistration
//   [ ] 0x4e8018  CKS08MaleforBigBombDeathBall_Destroy
//   [ ] 0x4e80a0  CKS08MaleforBigBombDeathBall_Destructor
//   [ ] 0x4e8110  CKS08MaleforBigBombDeathBall_Construct_2
//   [x] 0x4e8170  CKS08MaleforBigBombDeathBall_Construct
//   [x] 0x4e81d0  CKS08MaleforBigBombDeathBall_DeleteArray
//   [ ] 0x4e8270  CKS08MaleforBigBombDeathBall_DestructBody
//   [ ] 0x4e82e0  CKS08MaleforBigBombDeathBall_DeletingDestructor
//   [ ] 0x4e8358  CKS08MaleforBigBombDeathBall_ComputeSpreadDirections_maybe
//   [ ] 0x4e85f8  CKS08MaleforBigBombDeathBall_RandomizeBallParams_maybe
//   [ ] 0x4e8720  CKS08MaleforBigBombDeathBall_LaunchBalls_maybe
//   [ ] 0x4e8868  CKS08MaleforBigBombDeathBall_Update_maybe
//   [x] 0x4e88f0  CKS08MaleforBigBombDeathBall_Create
//   [x] 0x4e8960  CKS08MaleforBigBombDeathBall_CreateArray
//   [x] 0x4e8a40  CKS08MaleforBigBombDeathBall_Load
//   [ ] 0x4e8fb8  CKS08MaleforColdBall_Delete
//   [ ] 0x4e9008  FUN_004e9008  [dead]
//
//   [ ] 0x9c66a8  CKS08MaleforBigBombDeathBall_IsKindOfClass  [inline]
//   [ ] 0x9c66f8  CKS08MaleforBigBombDeathBall_GetClassType  [inline]
//   [ ] 0x9c6700  CKS08MaleforBigBombDeathBall_GetClassID  [inline]
#include "Spyro2008/logic/CKS08MaleforBigBombDeathBall.h"

#include "k2000/io/IKFile.h"
#include "k2000/memory/Mem.h"

// 0x004e8170 CKS08MaleforBigBombDeathBall_Construct: CKGolemAttackCommon's constructor, then the array header.
CKS08MaleforBigBombDeathBall::CKS08MaleforBigBombDeathBall() {
    m_apEntries = nullptr;
    m_entryCapacity = 1;
    m_entryCount = 0;
}

// 0x004e8a40 CKS08MaleforBigBombDeathBall_Load: CKGolemAttackCommon's data, then, for K_LEVEL_PLATEFORMS only,
// five words, a reference, a counted array of two-float entries, and words and references.
int32_t CKS08MaleforBigBombDeathBall::Load(IKFile* file, int32_t type) {
    CKGolemAttackCommon::Load(file, type);
    if (type != 0) return 1;

    ReadS32LE(file, &m_unkac);
    ReadF32LE(file, &m_unkb0);
    ReadF32LE(file, &m_unkb4);
    ReadF32LE(file, &m_unkb8);
    ReadF32LE(file, &m_unkbc);
    IKFile_ReadRef(file, &m_unk98);

    uint32_t count = 0;
    ReadU32LE(file, &count);
    // BUG(original): a fresh one-entry block every Load; the old block is not freed and the count is kept.
    m_entryCapacity = 1;
    m_apEntries = static_cast<Entry**>(Mem_AllocAligned16(static_cast<uint32_t>(sizeof(Entry*))));
    for (uint32_t i = 0; i < count; ++i) {
        Entry* entry = new Entry;
        ReadF32LE(file, &entry->m_unk00);
        ReadF32LE(file, &entry->m_unk04);
        if (m_entryCapacity == m_entryCount) {
            uint32_t capacity = m_entryCount + 1;
            if (capacity == 0) capacity = 1;
            m_apEntries = static_cast<Entry**>(
                Mem_ReallocAligned16(m_apEntries, capacity * static_cast<uint32_t>(sizeof(Entry*))));
            m_entryCapacity = capacity;
        }
        m_apEntries[m_entryCount] = entry;
        m_entryCount = m_entryCount + 1;
    }

    ReadF32LE(file, &m_unka8);
    IKFile_ReadRef(file, &m_unk9c);
    ReadF32LE(file, &m_unka0);
    IKFile_ReadRef(file, &m_unkc0);
    IKFile_ReadRef(file, &m_unkc4);
    return 1;
}
