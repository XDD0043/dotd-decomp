// KBase201.h - the base of the bonus service (key 0x201 = service id 8, vtable 0xb19cd8; not registered,
// not in XXL2: no name). Original unit: KBase201.cpp (0x126268-0x126d20). Its only class is
// CKSrvBonus (k2000/ui/CKSrvBonus.h); the fields are all here.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/services/IKService.h"
#include "k2000/util/TVector.h"

class CKBonusData;
struct CVector3;

class KBase201 : public IKService {
public:
    DOTD_CLASS_KEY(kCategoryService, 0x8)  // KBase201_vf14 / vf18 (0x9a7030 / 0x9a7038)

    // A delayed spawn, 0x20 bytes (InitializeService allocates 150: 0x12c0 bytes; BonusSpawnList_Add_maybe 0x1268d0).
    struct Entry {
        uint32_t m_kind;  // +0x00 the bonus kind (the drop entry's +0x00)
        float m_fTime;    // +0x04 when it spawns (the service's time); -1 until SpawnBonuses times it
        float m_aPos[3];  // +0x08
        float m_aVel[3];  // +0x14
    };

    KBase201();  // 0x00126a10 KBase201_Construct
    ~KBase201() override;  // 0x00126be0 KBase201_Destructor
    // vt+0x10 0x001265e8 KBase201_Destroy: IKService's (empty), the reference array deleted.
    void Destroy() override;

    // vt+0x2c 0x00126aa8 KBase201_Load. No type test.
    int32_t Load(IKFile* file, int32_t type) override;
    void Start() override { m_fNow = 0.0f; }            // vt+0x50 0x126248 KBase201_vf50
    void Stop() override;                               // vt+0x68 0x126268 KBase201_vf68: no delayed spawns
    void Pause() override {}                            // vt+0x70 0x126258 (empty)
    void Resume() override {}                           // vt+0x78 0x126260 (empty)
    // vt+0x7c 0x001266d0 CKSrvBonus_ProcessDelayedSpawns_maybe: while the clock runs, the time taken from it (+0x04)
    // and every delayed spawn due started (vt+0xa8, the last of its drop) and removed (the last one moved into its place).
    void Update(IKTime* frameClock) override;
    // vt+0x94 0x00126688 KBase201_Init: room for 150 delayed spawns.
    int32_t InitializeService() override;
    // vt+0xa8 (CKSrvBonus 0x5a9638 CKSrvBonus_SpawnBonusWithVelocity_maybe): a bonus of `kind` from the game manager's
    // pool at `pos`, launched at `vel`.
    virtual void SpawnBonusWithVelocity(uint32_t /*kind*/, const float* /*pos*/, const float* /*vel*/, uint8_t /*last*/) {}
    // vt+0xac (CKSrvBonus 0x5a9a18 CKSrvBonus_SpawnBonus_maybe): a bonus of `kind` from the game manager's pool at `pos`,
    // given to `hero` with `velocity` (the bonus's vt+0xe4).
    virtual void SpawnBonusForHero(uint32_t /*kind*/, const CVector3* /*pos*/, const CVector3* /*velocity*/,
                                   IKSerializable* /*hero*/, uint8_t /*last*/) {}

    // 0x00126278 CKSrvBonus_SpawnBonuses_maybe: the drop table's entries (from the last; a layout index past the
    // service's references ends it) generate their spawns through their layout (vt+0x50): every entry of count mode 0
    // or 1, only mode 1 with `onlyMode1`; started at once without a delay (+0x0c 0), else queued and timed: the new ones
    // `delay` apart from now, in order or (+0x10 bit 0) each slot to a random untimed one (one draw each).
    void SpawnBonuses(CKBonusData* table, const CVector3* pos, const CVector3* dir, const CVector3* base, int32_t onlyMode1);
    // 0x001265b0 CKSrvBonus_SpawnBonusesArgSwap_maybe: SpawnBonuses with `pos` as the base too (a tail call).
    void SpawnBonusesArgSwap(CKBonusData* table, const CVector3* pos, const CVector3* dir, int32_t onlyMode1) {
        SpawnBonuses(table, pos, dir, pos, onlyMode1);
    }
    // 0x001268d0 BonusSpawnList_Add_maybe: a delayed spawn (untimed: -1), the list grown by 10 when full.
    void AddDelayedSpawn(uint32_t kind, const CVector3* pos, const CVector3* vel);
    // vt+0x98 0x00126638 KBase201_Shutdown: the delayed-spawn block freed, the list emptied (the capacity is kept).
    void DestroyService() override;

    float m_fNow;                 // +0x0c the clock's time at the last Update (Start: 0); not set by the constructor
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
