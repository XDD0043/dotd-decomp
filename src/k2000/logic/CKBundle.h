// CKBundle.h - a bundle of hooks updated together (key 0xcc, vtable 0xb1dfb8, size 0x18). Original
// unit: CKBundle.cpp. XXL2: K/KCore/Life/CKBundle.h (bases IKUpdatable and CSPriorityBaseNode<CKBundle*>:
// m_pNext, m_ui32Priority; then m_pGroup, m_lAwakeLifeList, m_lAsleepLifeList).
#pragma once
#include <cstdint>

#include "k2000/core/IKUpdatable.h"
#include "k2000/core/Layout.h"

class IKLife;

class CKBundle : public IKUpdatable {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x3)
    DOTD_DECLARE_FACTORIES(CKBundle)

    CKBundle();  // inlined in 0x001ddd70 CKBundle_Create
    ~CKBundle() override {}

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x001de128 CKBundle_Load
    // The bundle runs its group first, then its awake hooks (sorted by priority), then (for the calls that
    // visit them) its asleep hooks, calling the same IKUpdatable slot on each.
    void SetDefaultState(int32_t flag) override;        // vt+0x38 0x1ddb90 CKBundle_SetDefaultState
    void Start() override;                              // vt+0x50 0x1dd5e8 CKBundle_Start
    void Restart() override;                            // vt+0x54 0x1dd3f0 CKBundle_Restart
    void Vf60() override;                               // vt+0x60 0x1dd300 CKBundle_BroadcastPostReinit_maybe
    void Stop() override;                               // vt+0x68 0x1dd030 CKBundle_Stop
    void Pause() override;                              // vt+0x70 0x1dd210 CKBundle_Pause
    void Resume() override;                             // vt+0x78 0x1dd120 CKBundle_Resume
    void Update(IKTime* frameClock) override;           // vt+0x7c 0x1de010 UpdateCKBundleObjects
    void SectorLoaded(int32_t sector) override;         // vt+0x88 0x1dd988 CKBundle_SectorLoaded
    void SectorUnload(int32_t sector) override;         // vt+0x8c 0x1dda88 CKBundle_SectorUnload
    // 0x1dd4e0 CKBundle_InitHooks_maybe (XXL2 AwakeOnStart): vt+0x94 on every life whose bit 0 is clear
    // (not virtual; the bundle's own vt+0x94 is CKBundle_vf94).
    void InitHooks();
    // 0x001dd788 CKBundle_ShutdownHooks_maybe (CKServiceLife_Stop, before the bundles' Stop).
    void ShutdownHooks();
    // 0x001dddc8 ObjectList_MoveBetweenActiveLists_maybe (XXL2 CKBundle::AwakeLife(IKLife*, bool)): for a hook
    // (class key 2), `active` 0 moves it from the awake list to the front of the asleep list (when it is awake),
    // nonzero moves a sleeping one from the asleep list into the awake list, by descending priority.
    void MoveBetweenActiveLists(IKLife* life, uint32_t active);

    CKBundle* m_pNext;           // +0x04 XXL2 CSPriorityBaseNode<CKBundle*>::m_pNext (a reference in the file)
    uint32_t m_ui32Priority;     // +0x08 XXL2 CSPriorityBaseNode::m_ui32Priority; the constructor sets 0x7fffffff
    IKSerializable* m_pGroup;    // +0x0c XXL2 m_pGroup (IKBaseGroup)
    IKLife* m_lAwakeLifeList;    // +0x10 XXL2 m_lAwakeLifeList: the hooks, sorted by priority at load
    IKLife* m_lAsleepLifeList;   // +0x14 XXL2 m_lAsleepLifeList
};
DOTD_ASSERT_SIZE(CKBundle, 0x18);
DOTD_ASSERT_OFFSET(CKBundle, m_pNext, 0x04);
DOTD_ASSERT_OFFSET(CKBundle, m_ui32Priority, 0x08);
DOTD_ASSERT_OFFSET(CKBundle, m_pGroup, 0x0c);
DOTD_ASSERT_OFFSET(CKBundle, m_lAwakeLifeList, 0x10);
DOTD_ASSERT_OFFSET(CKBundle, m_lAsleepLifeList, 0x14);
