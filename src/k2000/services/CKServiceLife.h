// CKServiceLife.h - the life service (key 0x41, vtable 0xb1e150, size 0x14). Original unit:
// CKServiceLife.cpp (0x1dece0-0x1dfb50). XXL2: K/KServices/KServiceLife/CKServiceLife.h, the same two
// members in the same order.
//
// It owns the list of the level's bundles (CKBundle): Start/Stop walk it.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/services/IKService.h"
#include "k2000/hooks/IKLife.h"

class CKServiceLife : public IKService {
public:
    DOTD_CLASS_KEY(kCategoryService, 0x1)
    int32_t IsKindOfClass(uint32_t key) override {  // vt+0x08 0x9adcb0
        return key == 0x41 || key == 0x1 || key == 0x3fe || key == 0xc;
    }
    DOTD_DECLARE_FACTORIES(CKServiceLife)

    CKServiceLife();  // 0x001dee30 CKServiceLife_Construct
    // 0x001dfaf0 CKServiceLife_Destructor (0x1dfa90 Destructor_2 the same, 0x1dfa28 DeletingDestructor + delete): the
    // engine's life service cleared.
    ~CKServiceLife() override;
    // vt+0x24 0x001df058 CKServiceLife_RecursiveRegistration: type 4: every bundle of the list (linked through +0x04)
    // gets RecursiveRegistration(4).
    void RecursiveRegistration(int32_t type) override;

    void Destroy() override;  // vt+0x10 0x001ded90 CKServiceLife_Destroy
    // vt+0x2c 0x001df670 (Ghidra: DeserializeLifeServiceBundleHead). Reads for every type.
    int32_t Load(IKFile* file, int32_t type) override;
    // vt+0x38 0x001df720 CKServiceLife_SetDefaultState: every bundle's SetDefaultState (vt+0x38) with the flag's low byte.
    void SetDefaultState(int32_t flag) override;
    void Start() override;                              // vt+0x50 0x1df320 CKServiceLife_Start
    void Restart() override;                            // vt+0x54 0x1def40 CKServiceLife_Restart
    void Vf60() override;                               // vt+0x60 0x1df3d8 CKServiceLife_BroadcastPostReinit_maybe
    void Stop() override;                               // vt+0x68 0x1df1e8 CKServiceLife_Stop
    void Pause() override;                              // vt+0x70 0x1df2a0 CKServiceLife_Pause
    void Resume() override;                             // vt+0x78 0x1df168 CKServiceLife_Resume
    void Update(IKTime* frameClock) override;           // vt+0x7c 0x1df0e8 UpdateLifeServiceBundles
    void SectorLoaded(int32_t sector) override;         // vt+0x88 0x1df798 CKServiceLife_SectorLoaded
    // vt+0x8c 0x001df810 CKServiceLife_SectorUnload: every bundle told (its vt+0x8c).
    void SectorUnload(int32_t sector) override;
    // vt+0x94 0x1dec50 CKServiceLife_InitializeService: the state 2, returns 1.
    int32_t InitializeService() override {
        m_eCurrentState = 2;
        return 1;
    }
    void DestroyService() override {}                   // vt+0x98 0x1dec60 (empty)

    // +0x0c the first CKBundle of the list (XXL2 BundleList, a TSNodeList: only the head; the bundles
    // link themselves). Read as one reference (XXL2: EUL_TSNodeList_Read).
    IKSerializable* m_lBundleList;
    // +0x10 XXL2 IKTime::ECurrentState: InitializeService sets 2, Start 0, Stop 2. Not set by the
    // constructor.
    uint32_t m_eCurrentState;
    // 0x001df458 ObjectList_SetObjectActive_maybe (XXL2 CKServiceLife::AwakeLife(IKLife*, bool, CKBundle*)): the
    // life moves between its bundle's lists; while the service is running (state 0) a life going to sleep gets
    // Vf98 and bit 0 set, one waking gets Vf94 and bit 0 cleared; otherwise only bit 0 follows `active`.
    void SetObjectActive(IKLife* life, uint32_t active, class CKBundle* bundle);
};
DOTD_ASSERT_SIZE(CKServiceLife, 0x14);
DOTD_ASSERT_OFFSET(CKServiceLife, m_ui32Priority, 0x08);
DOTD_ASSERT_OFFSET(CKServiceLife, m_lBundleList, 0x0c);
DOTD_ASSERT_OFFSET(CKServiceLife, m_eCurrentState, 0x10);
