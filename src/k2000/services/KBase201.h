// KBase201.h - the base of the bonus service (key 0x201 = service id 8, vtable 0xb19cd8; not registered,
// not in XXL2: no name). Original unit: KBase201.cpp (0x126268-0x126d20). Its only class is
// CKSrvBonus (k2000/ui/CKSrvBonus.h); the fields are all here.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/services/IKService.h"
#include "k2000/util/TVector.h"

class KBase201 : public IKService {
public:
    DOTD_CLASS_KEY(kCategoryService, 0x8)  // KBase201_vf14 / vf18 (0x9a7030 / 0x9a7038)

    // One 0x20-byte element of the +0x10 vector (InitializeService allocates 150 of them: 0x12c0
    // bytes; BonusSpawnList_Add_maybe 0x1268d0). Content not traced.
    struct Entry {
        uint32_t m_unk[8];
    };

    KBase201();  // 0x00126a10 KBase201_Construct
    ~KBase201() override {}

    // vt+0x2c 0x00126aa8 KBase201_Load. No type test.
    int32_t Load(IKFile* file, int32_t type) override;
    void Start() override {}                            // vt+0x50 0x126248 KBase201_vf50  STUB(C1.6)
    void Stop() override;                               // vt+0x68 0x126268 KBase201_vf68: no delayed spawns
    void Pause() override {}                            // vt+0x70 0x126258 (empty)
    void Resume() override {}                           // vt+0x78 0x126260 (empty)
    void Update(IKTime*) override {}                    // vt+0x7c 0x1266d0  STUB(C1.6)
    // vt+0x94 0x126688 KBase201_Init. STUB(C1.6): the original sizes m_vSpawns (150 entries,
    // Mem_AllocAligned16(0x12c0)), then returns 1.
    int32_t InitializeService() override { return 1; }
    void DestroyService() override {}                   // vt+0x98 0x126638 KBase201_Shutdown  STUB(C1.6)

    uint32_t m_unk0c;             // +0x0c Start sets 0; not set by the constructor
    TVector<Entry, 10> m_vSpawns; // +0x10 delayed bonus spawns _maybe (CKSrvBonus_ProcessDelayedSpawns_maybe)
    uint8_t m_unk1c;              // +0x1c read: the reference count
    uint8_t m_pad1d[3];           // +0x1d
    IKSerializable** m_unk20;     // +0x20 read: references (OperatorNewArray)
};
DOTD_ASSERT_SIZE(KBase201::Entry, 0x20);
DOTD_ASSERT_SIZE(KBase201, 0x24);
DOTD_ASSERT_OFFSET(KBase201, m_ui32Priority, 0x08);
DOTD_ASSERT_OFFSET(KBase201, m_vSpawns, 0x10);
DOTD_ASSERT_OFFSET(KBase201, m_unk1c, 0x1c);
DOTD_ASSERT_OFFSET(KBase201, m_unk20, 0x20);
