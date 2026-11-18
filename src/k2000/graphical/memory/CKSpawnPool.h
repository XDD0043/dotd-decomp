// CKSpawnPool.h - a pool of spawned scene nodes (key 0xbcd, vtable 0xb17910, size 0x30). Original unit:
// CKSpawnPool.cpp. XXL2: K/KModules/KGL/Main/CSpawnManager.h (CKSpawnPool: m_vpSpawnPoolParams,
// m_asRpHAnimHierarchy, m_ui32NumHierarchy); DotD has a second vector and a template node.
#pragma once
#include <cstdint>

#include "k2000/core/IKSerializable.h"
#include "k2000/core/Layout.h"

struct RwFrame;
struct RpHAnimHierarchy;
struct RwCamera;
class CAnimatedNode;
class IKTime;
class RenderQueue;

class CKSpawnPool : public IKSerializable {
public:
    DOTD_CLASS_KEY(kCategoryGraphical, 0x2f)
    int32_t IsKindOfClass(uint32_t key) override { return key == 0xbcd || key == 0xc; }  // vt+0x08 0x9a0f08
    DOTD_DECLARE_FACTORIES(CKSpawnPool)

    // XXL2 CKSpawnPool::SAnimHierarchy (PS3 0x24 bytes).
    struct SAnimHierarchy {
        RpHAnimHierarchy* m_pRpHAnimHierarchy;  // +0x00 IKFile_ReadBoneFrameList
        IKSerializable* m_pController;          // +0x04 a CKAnmKeyFrameController (PostLoad sets its animation)
        RwFrame* m_pRootFrame;                  // +0x08 IKFile_ReadBoneFrameList
        uint16_t m_unk0c;                       // +0x0c Load sets 0
        uint16_t m_pad0e;
        float m_aUnk10[4];                      // +0x10 not read; the local bounding sphere UpdateAnimSlot caches
        float m_unk20;                          // +0x20 the animation time (read; AcquireAnimSlot draws a start)
    };

    // 0x000b6e78 CKSpawnPool_Create (the constructor inlined)
    CKSpawnPool() {
        m_apSpawnPoolParams = nullptr;
        m_ui32ParamsCapacity = 2;
        m_ui32NbSpawnPoolParams = 0;
        m_ui32RenderParamsCapacity = 2;
        m_ui32NbRenderParams = 0;
        m_apRenderParams = nullptr;
        m_unk2c = 0;
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
    // animation.
    int32_t PostLoad(int32_t type) override;
    // vt+0x24 0x000b7160 CKSpawnPool_RecursiveRegistration: (type 0) itself registered; every params and render params
    // block's with the type; (type 0) the template node's and the controllers' of the hierarchies 1.. (the first one is
    // skipped).
    void RecursiveRegistration(int32_t type) override;
    // vt+0x10 0x000b7a60 CKSpawnPool_Destroy: each hierarchy's frame (RpHAnimHierarchy parentFrame) destroyed
    // (RwFrameDestroy_Field14_Thunk_maybe 0xc8d60), then the hierarchy block freed.
    void Destroy() override;

    // ---- C2.8 port-rest R02 (CSpawnAnimatedNode_UpdateSharedAnim_maybe 0xd4a60, CZoneNode.cpp, calls both).
    // 0x000b6d00 CKSpawnPool_AcquireAnimSlot_maybe: the next hierarchy slot (+0x2c, back to 0 past the count) is handed
    // out; unless flag bit 0 (+0x08), its animation starts at a random time: (draw & 0xffff) / 65535 x the controller's
    // duration (Rand_Int before Anim_GetDuration), stored in the slot and the controller.
    uint32_t AcquireAnimSlot();
    // 0x000b6f48 CKSpawnPool_UpdateAnimSlot_maybe: `node` takes slot `slot`'s hierarchy and controller; a slot already
    // posed this render frame only puts its cached sphere into world space (TransformNodeBoundingSphereToWorld); else
    // (the clock running: its time advanced by the frame delta into the controller) the node is posed and culled
    // (UpdateAnimatedNodePoseAndCull) and the slot caches the sphere and the frame.
    void UpdateAnimSlot(CAnimatedNode* node, RenderQueue** stages, IKTime* clock, uint32_t slot, float* sphere,
                        float* worldSphere, RwCamera* camera);

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
    uint32_t m_unk2c;                         // +0x2c the next hierarchy slot (AcquireAnimSlot); not set by the
                                              //       constructor or Load (zeroed here: the fresh heap)
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
