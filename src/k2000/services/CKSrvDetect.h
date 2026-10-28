// CKSrvDetect.h - the detection service (key 0x4c1, vtable 0xb1c2a0, size 0x18). Original unit:
// CKSrvDetect.cpp (0x1a6b70-0x1a8120). XXL2: K/KServices/KServiceDetect/CKSrvDetect.h, the same two
// members read in the same order; +0x14 is DotD's.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/services/IKService.h"

class CKSrvDetect : public IKService {
public:
    DOTD_CLASS_KEY(kCategoryService, 0x13)
    DOTD_DECLARE_FACTORIES(CKSrvDetect)

    CKSrvDetect();  // 0x001a7580 CKSrvDetect_Construct
    ~CKSrvDetect() override {}

    void Destroy() override;  // vt+0x10 0x001a7530 CKSrvDetect_Destroy
    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x001a78e0 CKSrvDetect_Load
    void Start() override {}                            // vt+0x50 0x1a7320  STUB(C1.6)
    void Stop() override {}                             // vt+0x68 0x1a7380  STUB(C1.6)
    void Pause() override {}                            // vt+0x70 0x1a7378  STUB(C1.6)
    void Resume() override {}                           // vt+0x78 0x1a7388  STUB(C1.6)
    void Update(IKTime*) override {}                    // vt+0x7c 0x1a7c30 UpdateCKSrvDetect  STUB(C1.6)
    // vt+0x8c 0x001a7860 CKSrvDetect_SectorUnload: every detected-movable list forgets that its entries of
    // the sector are loaded.
    // vt+0x84 0x001a7488 CKSrvDetect_PreSectorLoaded: every detected-movable list activates its entries of the
    // sector. vt+0x88 0x1a7330 (SectorLoaded) is a bare return.
    void PreSectorLoaded(int32_t sector) override;
    void SectorUnload(int32_t sector) override;
    // vt+0x94 0x1a7a68. STUB(C1.6): the original clears +0x0c and +0x10, then returns 1.
    int32_t InitializeService() override { return 1; }
    void DestroyService() override {}                   // vt+0x98 0x1a7310 (empty)

    // 0x001a7348 CKSrvDetect_BeginCinematic_maybe: one more scene suspends the detection refresh (+0x14).
    // 0x001a7d08 CKSrvDetect_EndCinematic_maybe: the last scene to end lets the detection refresh again and refreshes the
    // old positions of every detected-movable list.
    void BeginCinematic() { ++m_unk14; }
    void EndCinematic();
    IKSerializable** m_apDetectedMovable;  // +0x0c CKDetectedMovable* (Mem_AllocAligned16)
    uint32_t m_ui32NbDetectedMovable;      // +0x10
    uint32_t m_unk14;                      // +0x14 the constructor sets 0
};
DOTD_ASSERT_SIZE(CKSrvDetect, 0x18);
DOTD_ASSERT_OFFSET(CKSrvDetect, m_ui32Priority, 0x08);
DOTD_ASSERT_OFFSET(CKSrvDetect, m_apDetectedMovable, 0x0c);
DOTD_ASSERT_OFFSET(CKSrvDetect, m_ui32NbDetectedMovable, 0x10);
DOTD_ASSERT_OFFSET(CKSrvDetect, m_unk14, 0x14);
