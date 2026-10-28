// CKSpawnPool.h - a pool of spawned scene nodes (key 0xbcd, vtable 0xb17910, size 0x30). Original unit:
// CKSpawnPool.cpp. XXL2: K/KModules/KGL/Main/CSpawnManager.h (CKSpawnPool: m_vpSpawnPoolParams,
// m_asRpHAnimHierarchy, m_ui32NumHierarchy); DotD has a second vector and a template node.
#pragma once
#include <cstdint>

#include "k2000/core/IKSerializable.h"
#include "k2000/core/Layout.h"

struct RwFrame;
struct RpHAnimHierarchy;

class CKSpawnPool : public IKSerializable {
public:
    DOTD_CLASS_KEY(kCategoryGraphical, 0x2f)
    DOTD_DECLARE_FACTORIES(CKSpawnPool)

    // XXL2 CKSpawnPool::SAnimHierarchy (PS3 0x24 bytes).
    struct SAnimHierarchy {
        RpHAnimHierarchy* m_pRpHAnimHierarchy;  // +0x00 IKFile_ReadBoneFrameList
        IKSerializable* m_pController;          // +0x04 a CKAnmKeyFrameController (PostLoad sets its animation)
        RwFrame* m_pRootFrame;                  // +0x08 IKFile_ReadBoneFrameList
        uint16_t m_unk0c;                       // +0x0c Load sets 0
        uint16_t m_pad0e;
        uint32_t m_aUnk10[4];                   // +0x10 not read
        uint32_t m_unk20;                       // +0x20
    };

    // 0x000b6e78 CKSpawnPool_Create (the constructor inlined)
    CKSpawnPool() {
        m_apSpawnPoolParams = nullptr;
        m_ui32ParamsCapacity = 2;
        m_ui32NbSpawnPoolParams = 0;
        m_ui32RenderParamsCapacity = 2;
        m_ui32NbRenderParams = 0;
        m_apRenderParams = nullptr;
    }
    ~CKSpawnPool() override {}

    // vt+0x2c 0x000b7518 CKSpawnPool_Load (type 0 only)
    int32_t Load(IKFile* file, int32_t type) override;

    // 0x000b70e8 CKSpawnPool_StopAllShakeCaches_maybe: StopAllShakes of every params block that exists.
    void StopAllShakeCaches();
    // 0x000b6ed8 CKSpawnPool_StartSlotShakeCache_maybe: the params block of that slot, when it has the shake flag
    // (bit 1 of its +0x04), starts all its shakes.
    void StartSlotShakeCache(int32_t slot);
    // vt+0x30 0x000b7480 CKSpawnPool_PostLoad: every hierarchy's controller gets the template node's
    // animation. STUB(C2.2) (default).

    IKSerializable* m_pNode;                  // +0x04 the template node (a CNode)
    uint32_t m_unk08;                         // +0x08
    IKSerializable** m_apSpawnPoolParams;     // +0x0c CKSpawnPoolParams references (Mem_AllocAligned16)
    uint32_t m_ui32ParamsCapacity;            // +0x10 (2 when empty)
    uint32_t m_ui32NbSpawnPoolParams;         // +0x14
    IKSerializable** m_apRenderParams;        // +0x18 CSpawnPoolRenderParam references
    uint32_t m_ui32RenderParamsCapacity;      // +0x1c
    uint32_t m_ui32NbRenderParams;            // +0x20
    SAnimHierarchy* m_asRpHAnimHierarchy;     // +0x24 null when there are none
    uint32_t m_ui32NumHierarchy;              // +0x28
    void* m_unk2c;                            // +0x2c not set by the constructor or Load
};
DOTD_ASSERT_SIZE(CKSpawnPool::SAnimHierarchy, 0x24);
static_assert(CKSpawnPool::kClassKey == 0xbcd, "key");
DOTD_ASSERT_SIZE(CKSpawnPool, 0x30);
DOTD_ASSERT_OFFSET(CKSpawnPool, m_pNode, 0x04);
DOTD_ASSERT_OFFSET(CKSpawnPool, m_unk08, 0x08);
DOTD_ASSERT_OFFSET(CKSpawnPool, m_apSpawnPoolParams, 0x0c);
DOTD_ASSERT_OFFSET(CKSpawnPool, m_ui32NbSpawnPoolParams, 0x14);
DOTD_ASSERT_OFFSET(CKSpawnPool, m_apRenderParams, 0x18);
DOTD_ASSERT_OFFSET(CKSpawnPool, m_ui32NbRenderParams, 0x20);
DOTD_ASSERT_OFFSET(CKSpawnPool, m_asRpHAnimHierarchy, 0x24);
DOTD_ASSERT_OFFSET(CKSpawnPool, m_ui32NumHierarchy, 0x28);
