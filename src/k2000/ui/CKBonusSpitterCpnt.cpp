// Reconstructed original translation unit: 0x5bb7e8-0x5bc3e0 (GAME_TOC2, main_toc2), 17 functions, 16 live.
// Primary owner: CKBonusSpitterCpnt (not a registered class)
// Other owners: RegisterCKBonusSpitterCpntClass (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x5bb7e8  CKBonusSpitterCpnt_Destroy  (the registry factory Delete: DOTD_DECLARE_FACTORIES(CKBonusSpitterCpnt), CKBonusSpitterCpnt.h)
//   [ ] 0x5bb838  CKBonusSpitterCpnt_ClearSpawnList_maybe  [dead]
//   [ ] 0x5bb888  RegisterCKBonusSpitterCpntClass
//   [ ] 0x5bb900  _GLOBAL__I_5bb900
//   [x] 0x5bb910  CKBonusSpitterCpnt_DestroyArray  (DOTD_DECLARE_FACTORIES)
//   [x] 0x5bb9b0  CKBonusSpitterCpnt_Create  (DOTD_DECLARE_FACTORIES: the header's constructor)
//   [x] 0x5bb9f8  CKBonusSpitterCpnt_DeletingDestructor  (~CKBonusSpitterCpnt, then delete)
//   [x] 0x5bbac0  CKBonusSpitterCpnt_Destructor  (~CKBonusSpitterCpnt)
//   [ ] 0x5bbb78  CKBonusSpitterCpnt_Destructor_2  [dead: no pointer to its descriptor 0xbf1ee0, no call]
//   [ ] 0x5bbc30  CKBonusSpitterCpnt_UpdateEmission_maybe  [dead: no pointer to its descriptor 0xbf1f08, no call]
//   [x] 0x5bbee8  CKBonusSpitterCpnt_CreateArray  (DOTD_DECLARE_FACTORIES)
//   [ ] 0x5bbf90  CKBonusSpitterCpnt_Save
//   [x] 0x5bbf98  CKBonusSpitterCpnt_LevelReset  (RecursiveRegistration: registers nothing, the default)
//   [x] 0x5bbfa0  CKBonusSpitterCpnt_ClearReferences  (Destroy: empty, the default)
//   [ ] 0x5bbfa8  CKBonusSpitterCpnt_QueueConfiguredBonuses_maybe  [dead: no pointer to its descriptor 0xbf1f50, no call]
//   [ ] 0x5bc070  CKBonusSpitterCpnt_QueueBonus_maybe  [dead: no pointer to its descriptor 0xbf1f58, no call]
//   [x] 0x5bc120  CKBonusSpitterCpnt_Load
//
//   [ ] 0x9ccf50  CKBonusSpitterCpnt_IsKindOf  [inline]
//   [ ] 0x9ccf78  CKBonusSpitterCpnt_GetClassGroup  [inline]
//   [ ] 0x9ccf80  CKBonusSpitterCpnt_GetClassId  [inline]
//   [ ] 0x9ccf88  KBase2D82_IsKindOf  [inline]
//   [ ] 0x9ccfd0  KStub_Return2_9ccfd0  [inline]
//   [ ] 0x9ccfd8  KStub_Return182_9ccfd8  [inline]
#include "k2000/ui/CKBonusSpitterCpnt.h"

#include "k2000/io/IKFile.h"

namespace {
// The list's nodes back to their pool (the original pushes each on the FreeListPool's free list, 0x00ceaa34).
void FreeSpits(CKBonusSpitterCpnt::SSpitNode** head) {
    for (CKBonusSpitterCpnt::SSpitNode* node = *head; node != nullptr;) {
        CKBonusSpitterCpnt::SSpitNode* next = node->m_pNext;
        delete node;
        node = next;
    }
    *head = nullptr;
}
}  // namespace

// 0x005bbac0 CKBonusSpitterCpnt_Destructor (0x005bb9f8 the deleting one)
CKBonusSpitterCpnt::~CKBonusSpitterCpnt() {
    FreeSpits(&m_lCurrentSpit);
    FreeSpits(&m_lTypicalSpit);
}

// 0x005bc120 CKBonusSpitterCpnt_Load: type 0 only. Position and speed (one 0x18-byte read, each word swapped), the delta
// time and the speed delta (one 8-byte read), the byte, then a count of halfword pairs, each pushed at the head of +0x04
// (a node from the pool, grown by FreeListPool_Grow 0x244908 through TocBridge 0x98fe70 when empty).
int32_t CKBonusSpitterCpnt::Load(IKFile* file, int32_t type) {
    if (type != K_LEVEL_PLATEFORMS) return 1;
    ReadF32LE(file, &m_vPosition.x);
    ReadF32LE(file, &m_vPosition.y);
    ReadF32LE(file, &m_vPosition.z);
    ReadF32LE(file, &m_vSpeed.x);
    ReadF32LE(file, &m_vSpeed.y);
    ReadF32LE(file, &m_vSpeed.z);
    ReadF32LE(file, &m_fSpitDeltaTime);
    ReadF32LE(file, &m_fHorizontalSpeedDelta);
    ReadU8(file, &m_bSpitOnLeader);
    uint32_t count = 0;
    ReadU32LE(file, &count);
    for (uint32_t i = 0; i < count; ++i) {
        uint16_t a = 0, b = 0;
        ReadU16LE(file, &a);
        ReadU16LE(file, &b);
        SSpitNode* node = new SSpitNode;
        node->m_ui16A = a;
        node->m_pNext = nullptr;
        node->m_ui16B = b;
        node->m_pNext = m_lTypicalSpit;
        m_lTypicalSpit = node;
    }
    return 1;
}
