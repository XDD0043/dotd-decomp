// CAnimationManager.h - the level's animations (key 0x20d, vtable 0xb15650, size 0xc). Original unit:
// CAnimationManager.cpp (0x92830-0x92e00). XXL2: K/KModules/KGL/Main/CAnimationManager.h
// (m_ui32NbAnimations, m_apAnimations). Created by CKGraphic_InitializeModule; the global 13:8.
#pragma once
#include <cstdint>

#include "k2000/core/IKSerializable.h"
#include "k2000/core/Layout.h"

struct RtAnimAnimation;

class CAnimationManager : public IKSerializable {
public:
    DOTD_CLASS_KEY(kCategoryGraphical, 0x8)
    DOTD_DECLARE_FACTORIES(CAnimationManager)

    // 0x00092d80 CAnimationManager_Create (inlined): the constructor only adds 0x24 to the custom data
    // size of RtAnim interpolator types 1 and 2 (RtAnimGetInterpolatorInfo): the room for the sector entry
    // (RtAnimSectorEntryData) behind each animation's key frames. Needs both schemes registered (CKGraphic::InitializeModule).
    CAnimationManager();
    ~CAnimationManager() override {}  // 0x009972b8 / 0x00997278 CAnimationManager_Destructor / _DeletingDestructor: the vtables only
    // vt+0x08 0x996988
    int32_t IsKindOfClass(uint32_t key) override { return key == 0x20d || key == 0xc; }
    void Destroy() override;  // vt+0x10 0x00092b00 CAnimationManager_Destroy
    int32_t Load(IKFile* file, int32_t type) override;      // vt+0x2c 0x00092970 CAnimationManager_Load
    int32_t GetSerializationFlags() override { return 0; }  // vt+0x34 0x996780
    // vt+0x24 0x00092880 CAnimationManager_RecursiveRegistration: registers the manager (any type).
    void RecursiveRegistration(int32_t type) override;
    int32_t PostLoad(int32_t /*type*/) override { return 1; }  // vt+0x30 0x000928e0 CAnimationManager_PostLoad

    IKSerializable** m_apAnimations;  // +0x04 CSectorAnimation references (Mem_AllocAligned16)
    uint32_t m_ui32NbAnimations;      // +0x08
};
DOTD_ASSERT_SIZE(CAnimationManager, 0xc);
DOTD_ASSERT_OFFSET(CAnimationManager, m_apAnimations, 0x04);
DOTD_ASSERT_OFFSET(CAnimationManager, m_ui32NbAnimations, 0x08);

// The animation a dictionary word names, as CAnimationDictionary_PostLoad 0x0007a288 resolves them (sector = word >> 24
// into the engine's manager, index = word & 0xffffff into that CSectorAnimation; null for 0xffffffff; no bounds checks).
// The original stores the result in the dictionary; dotd keeps the 32-bit words there (an x64 pointer does not fit) and
// resolves them where the original reads the pointer.
RtAnimAnimation* CAnimationManager_GetAnimation(uint32_t word);
// DOTD (not in the original): the dictionary word of an animation (0xffffffff for null), found by search; used where the
// original hands the pointer back to callers that compare it with dictionary entries.
uint32_t CAnimationManager_GetAnimationWord(const RtAnimAnimation* animation);
