// CKS08EnemyAttack.cpp - reconstructed original translation unit 0x2acb08-0x2ae2d0 (GAME_TOC1, main_toc1), 20 functions, 16 live.
// Primary class: CKS08EnemyAttack  key 0x990c  category Logic  size 0x70  vtable 0xb223a0
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x2acb08  CKS08EnemyAttack_Delete
//   [x] 0x2acb58  CKS08EnemyAttack_Construct  [dead]
//   [x] 0x2acb90  CKS08EnemyAttack_DeleteArray
//   [ ] 0x2acc38  RegisterCKS08EnemyAttackClass
//   [ ] 0x2accc0  _GLOBAL__D_2accc0
//   [ ] 0x2accd0  _GLOBAL__I_2accd0
//   [ ] 0x2acce0  CKS08EnemyAttack_Construct_2  [dead]
//   [ ] 0x2acd18  CKS08EnemyAttack_Save
//   [ ] 0x2acd20  CKS08EnemyAttack_RecursiveRegistration
//   [ ] 0x2acd28  CKS08EnemyAttack_PostLoad
//   [ ] 0x2acd30  CKS08EnemyAttack_Destroy
//   [x] 0x2acd38  CKS08EnemyAttack_CreateArray
//   [x] 0x2ace00  CKS08EnemyAttack_Create
//   [ ] 0x2ace60  CKS08EnemyAttack_CopyConstruct_maybe
//   [ ] 0x2ad110  CKS08EnemyAttack_Assign_maybe  [dead]
//   [ ] 0x2ad3e0  CKS08EnemyAttack_CopyConstruct_2_maybe
//   [x] 0x2ad690  CKS08EnemyAttack_Load
//   [ ] 0x2ae0d8  CKS08EnemyAttack_Destructor
//   [ ] 0x2ae178  CKS08EnemyAttack_Destructor_2  [dead]
//   [ ] 0x2ae218  CKS08EnemyAttack_DeletingDestructor
//
//   [ ] 0x9bca68  CKS08EnemyAttack_GetClassType  [inline]
//   [ ] 0x9bca70  CKS08EnemyAttack_GetClassID  [inline]
//   [ ] 0x9bca78  CKS08EnemyAttack_IsKindOfClass  [inline]
#include "Spyro2008/logic/CKS08EnemyAttack.h"

#include "k2000/io/IKFile.h"
#include "k2000/memory/Mem.h"

namespace {

// 0x00a70378 (TOC +0x132c), the attack-type table both arrays are sized from: 10 four-byte records
// whose last byte sizes the +0x48 array, then (+0x28) one byte per type sizing the +0x54 array. Kept
// as the original's 0x40 bytes so an out-of-range type reads what the PS3 reads.
const uint8_t kEnemyAttackTypeTable[0x40] = {
    0x01, 0x02, 0x02, 0x01, 0x01, 0x02, 0x02, 0x02, 0x01, 0x07, 0x07, 0x02, 0x01, 0x07, 0x07, 0x01,
    0x01, 0x07, 0x07, 0x02, 0x01, 0x0a, 0x0a, 0x03, 0x01, 0x0d, 0x0d, 0x02, 0x01, 0x02, 0x02, 0x02,
    0x01, 0x06, 0x06, 0x02, 0x00, 0x00, 0x00, 0x00, 0x02, 0x03, 0x03, 0x02, 0x03, 0x03, 0x03, 0x03,
    0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x0a, 0x0e, 0x0d, 0x0e, 0x11, 0x19, 0x11,
};

// The inlined array fill of CKS08EnemyAttack_Load: a count from the file, the array sized to exactly
// `size` bytes (grown to size + 1 when its capacity is smaller), count bytes read into it (those past
// `size` read and dropped) and the rest up to `size` zeroed.
void LoadByteArray(CKS08EnemyAttack::ByteArray* array, IKFile* file, uint32_t size) {
    uint32_t count = 0;
    ReadU32LE(file, &count);
    if (array->m_data == nullptr) {
        array->m_capacity = 1;
        array->m_data = static_cast<uint8_t*>(Mem_AllocAligned16(1));
    }
    if (array->m_capacity < size) {
        uint32_t capacity = size + 1;
        if (capacity == 0) capacity = 1;
        array->m_data = static_cast<uint8_t*>(Mem_ReallocAligned16(array->m_data, capacity & 0x1ff));
        array->m_capacity = capacity;
    }
    array->m_count = size;
    if (size < count) {
        for (uint32_t i = 0; i < size; ++i) ReadU8(file, &array->m_data[i]);
        for (uint32_t i = size; i < count; ++i) {
            uint8_t dropped = 0;
            ReadU8(file, &dropped);
        }
    } else {
        for (uint32_t i = 0; i < count; ++i) ReadU8(file, &array->m_data[i]);
        for (uint32_t i = count; i < size; ++i) array->m_data[i] = 0;
    }
}

}  // namespace

// 0x002ad690 CKS08EnemyAttack_Load: level data only.
int32_t CKS08EnemyAttack::Load(IKFile* file, int32_t type) {
    if (type != K_LEVEL_PLATEFORMS) return 1;
    ReadS32LE(file, &m_unk04);
    ReadS32LE(file, &m_unk08);
    ReadF32LE(file, &m_unk0c);
    ReadF32LE(file, &m_unk10);
    ReadF32LE(file, &m_unk14);
    ReadU8(file, &m_unk18);
    ReadF32LE(file, &m_unk1c);
    IKFile_ReadRef(file, &m_pDamage);
    ReadS32LE(file, &m_unk24);
    for (int i = 0; i < 6; ++i) ReadF32LE(file, &m_unk28[i]);
    // The projectile reference is kept only when it is a CKProjectileAccessor (IsKindOfClass 0x1e0c).
    IKSerializable* projectile = nullptr;
    IKFile_ReadRef(file, &projectile);
    m_pProjectile = nullptr;
    if (projectile != nullptr && static_cast<uint8_t>(projectile->IsKindOfClass(0x1e0c)) != 0)
        m_pProjectile = static_cast<CKProjectileAccessor*>(projectile);
    ReadF32LE(file, &m_unk44);
    // BUG(original): no range check on the type (lbzx table + type * 4 + 3, then lbz table + type + 0x28).
    LoadByteArray(&m_array48, file, kEnemyAttackTypeTable[m_unk04 * 4 + 3]);
    LoadByteArray(&m_array54, file, kEnemyAttackTypeTable[m_unk04 + 0x28]);
    ReadF32LE(file, &m_unk60);
    ReadF32LE(file, &m_unk68);
    ReadS32LE(file, &m_unk64);
    ReadU8(file, &m_unk6c);
    return 1;
}
