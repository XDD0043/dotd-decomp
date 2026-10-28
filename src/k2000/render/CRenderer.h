// CRenderer.h - the renderer (key 0x4d, size 0xd8): render stages, queues, cameras. Original unit:
// CRenderer.cpp (0x9e1a0-0xa2cc0).
//
// The front end's part of the frame is ported (C1.4): the 23 render-stage queues (the three queue types
// the stages use), the render-state stack, the 2D stage group (ExecuteRenderStages7CTo90) and the two
// frame functions as far as the front end needs them. The world and post stages (0-16), the scene roots'
// extraction and the particle scheduler are STUB(M2).
#pragma once
#include <cstdint>

#include "k2000/managers/IKModule.h"

class CVideoManager;
class CameraContext;
class IKTime;
class IRendableObject;

// A render-stage queue (0x14 bytes: vtable, items, capacity, count, z-test byte). Its vtable is one of
// eight "RenderQueueType" tables (0xb17110.., slots Add / Clear / IsEmpty / AllocBuffer / FreeBuffer /
// BeginPass / Execute); the stages use types 0, 1 and 6. The type number is Ghidra's navigation name.
class RenderQueue {
public:
    enum Type : uint8_t {
        kTransparentATestPrio = 0,  // vtable 0xb17138
        kOpaque = 1,                // vtable 0xb17110
        kOpaqueCutout = 2,          // vtable 0xb17020
        kTransparent = 3,           // vtable 0xb17098
        kBlendedZWrite = 4,         // vtable 0xb17070
        kTransparentUnsorted = 5,   // vtable 0xb170c0
        kTransparentATest = 6,      // vtable 0xb17160
        kTransparentPrio = 7,       // vtable 0xb170e8
    };
    explicit RenderQueue(Type type) : m_type(type) {}

    // vt+0x00 (0x99d068 / 0x99ecd0 / 0x99ebf0): appends the item (the array grows by 100), then the
    // item's vt+0x74 (ComputeSortingCoef) with the queue's sorting order (types 6 and 0: 1, type 1: 2).
    void Add(IRendableObject* item);
    void Clear() { m_count = 0; }                                  // vt+0x04 0x99d2b8 / 0x99d268 / 0x99d258
    bool IsEmpty() const { return m_count == 0; }                 // vt+0x08 0x99d228 / 0x99d188 / 0x99d168
    void AllocBuffer();                                            // vt+0x0c 0x99e728 / 0x99e7a8 / 0x99d028
    // vt+0x14 (0x99e1d8 / 0x99d548 / 0x99d2c8): the pass's render states.
    void BeginPass();
    // vt+0x18 (0x9a0068 / 0x99f510 / 0x99f130): BeginPass, the items sorted far to near (type 0: by
    // priority first), each item's rendering properties applied (types 0 and 6) and its vt+0x5c called;
    // then the queue is empty.
    void Execute();

    Type m_type;
    IRendableObject** m_ppItems = nullptr;  // +0x04
    uint32_t m_capacity = 100;              // +0x08
    uint32_t m_count = 0;                   // +0x0c
    uint8_t m_zTest = 1;                    // +0x10
};

class CRenderer : public IKSerializable {
public:
    DOTD_CLASS_KEY(kCategoryGraphical, 1)

    CRenderer();  // 0x0009fd30 ConstructRenderer (= CRenderer_Construct 0x9f0a8)
    ~CRenderer() override;

    static IKBaseClass* Create();
    static void Delete(IKBaseClass* object);

    // 0x0009f620 InitializeRendererStages: camera context, world, 23 render queues, CManager2d,
    // CBackgroundManager, CLightManager, CKFlashManager, CVideoManager, CSpawnManager.
    int32_t InitializeStages(void* startupContext);

    // 0x000a1c08 RenderGameFrame (modes 2, 5, 8)
    void RenderGameFrame(IKTime* frameClock);
    // 0x000a11b0 RenderFallbackFrame_maybe (the loading frame: the video manager, the 2D group with the
    // stages only cleared, present)
    void RenderFallbackFrame(IKTime* frameClock);
    // 0x000a0ac8 ExecuteRenderStages7CTo90: the 2D group (stages 17-22) on the UI camera.
    void ExecuteRenderStages7CTo90(IKTime* frameClock);
    // The world groups (C2.4 step 5): 0x000a04e8 SyncSceneCamerasAndClipPlanes, 0x0009ed38 ApplySceneRenderStatesAndFog,
    // 0x000a1408 ExecuteRenderStages38To48 (stages 0-4, the far group), 0x0009ff70 ExecuteRenderStages4CTo74 (stages 5-15),
    // 0x000a1a78 ExecuteRenderStage78 (stage 16).
    void SyncSceneCamerasAndClipPlanes();
    // `fogColor` (red, green, blue): FogManager_GetMainColor for the main group, GetColorForFarPass for the far one.
    void ApplySceneRenderStatesAndFog(const uint8_t fogColor[4]);
    void ExecuteRenderStages38To48(IKTime* frameClock);
    void ExecuteRenderStages4CTo74(IKTime* frameClock);
    void ExecuteRenderStage78(IKTime* frameClock);

    // vt+0x2c 0xa2330 CRenderer_Load
    int32_t Load(IKFile* file, int32_t type) override;
    // vt+0x30 0x000a2180 CRenderer_PostLoad: for the level (type 0) every background hidden (the active sectors' are shown by
    // CBackgroundManager::PreUpdate) and the video manager moved to the head of the renderable list.
    int32_t PostLoad(int32_t type) override;
    void Destroy() override;  // vt+0x10 0x0009eb70 CRenderer_Destroy (the level unload)

    // A node of the renderable-object list (8 bytes, FreeListPool at TOC -0x6260 in the original).
    struct RendableNode {
        IKSerializable* m_pObject;  // +0x00
        RendableNode* m_pNext;      // +0x04
    };
    // Inlined in CRenderer_Load (XXL2 CRenderer::AddRendeableObject).
    void AddRendeableObject(IKSerializable* object);
    // 0x0009eaa0 CRenderer_RegisterPostRenderingFx_maybe: the same insertion (a CPostRenderingFx's CKPBuffer).
    void RegisterPostRenderingFx(IKSerializable* object);

    // The stage queue `stage` (0..22; renderer +0x38 + 4 * stage).
    RenderQueue* GetStage(uint32_t stage) { return m_aStages[stage]; }

    CameraContext* m_cameraContext;               // +0x28 (engine +0x08 too)
    IKSerializable* m_pRootNode;                  // +0x2c XXL2 m_pRootNode (Engine_SetMainSceneRoot_maybe)
    IKSerializable* m_pSecondaryRootNode;         // +0x30 DotD (Engine_SetSecondarySceneRoot_maybe); name ours
    RenderQueue* m_aStages[23];                   // +0x38 the stage array (stages 17-22 at +0x7c..+0x90)
    IKSerializable* m_cloneManager;               // +0x94 CCloneManager (13:3)
    class CManager2d* m_manager2d;                // +0x98 (13:16; its +0xa78 = CMenuManager 13:17)
    uint8_t m_cFogColor[4];                       // +0x9c XXL2 m_cFogColor: read raw, keeps the file bytes
    float m_fFogDistance;                         // +0xa0 XXL2 m_fFogDistance
    // +0xa4 XXL2 m_bitProperties; the Load clears bits 1-3. Bit 2: the 2D stages are only cleared (the
    // loading frame), bit 3: no clear, bit 1/2 also skip the scene roots' extraction.
    uint32_t m_bitProperties;
    IKSerializable* m_backgroundManager;          // +0xa8 (13:26)
    IKSerializable* m_lightManager;               // +0xac (13:36)
    IKSerializable* m_flashManager;               // +0xb0 CKFlashManager (13:28)
    CVideoManager* m_videoManager;                // +0xb4 (13:39)
    IKSerializable* m_spawnManager;               // +0xb8 (13:46)
    RendableNode* m_lRenderableObjectList;        // +0xbc XXL2 m_lRenderableObjectList
    uint32_t m_renderStateDepth;                  // +0xc0 PushRenderStates' stack depth
    uint16_t m_renderStateCapacity;               // +0xc4 20
    uint8_t* m_pRenderStateStack;                 // +0xc8 20 entries of 0x38 bytes (Mem_AllocAligned16(0x460))
    float m_fInvFarSquared;                       // +0xcc
    uint32_t m_unkD4;                             // +0xd4 CKLevel_Load sets 99 (every type)
};

// 0x00c5c90c: the renderer whose state stack Push/PopRenderStates use (CRenderer_Construct stores it).
extern CRenderer* g_pRenderStateRenderer;
// 0x00c29694: the render frame counter (RenderGameFrame: +1 per frame, -2 wraps to 1); scene nodes and
// geometries store it when they are queued.
extern uint16_t g_ui16RenderFrameCounter;

// 0x0009e1a0 Apply2DRenderStates: the 2D group's base states (Z test and write on, no raster, Gouraud,
// back culling, the blend table's entry 0 (ONE/ZERO), no fog, alpha reference 200, alpha test always,
// no vertex alpha).
void Apply2DRenderStates();
// 0x0009e590 PushRenderStates / 0x0009e858 PopRenderStates: 14 render states (Z test, Z write, shade
// mode, filter, blends, vertex alpha, border colour, fog, fog colour, fog type, cull mode, alpha test
// function and reference) saved on the renderer's stack, and restored where they differ.
void PushRenderStates(CRenderer* renderer);
void PopRenderStates(CRenderer* renderer);
// The blend table (0x00c297ec source, 0x00c297fc destination; RW blend enums) indexed by brush, video
// and screen effect blend modes: opaque, alpha, additive, subtractive.
extern const int32_t kBlendTableSrc[4];
extern const int32_t kBlendTableDest[4];
