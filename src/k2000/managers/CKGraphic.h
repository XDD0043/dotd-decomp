// CKGraphic.h - the graphics manager (key 0x80, vtable 0xb15580, size 0x30). Original unit:
// CKGraphic.cpp. STUB(C1.4): Init stands in for CKGraphic_InitializeModule (RenderWare engine, PSGL
// device, plugins); it creates the shader manager and the renderer's dependencies without drawing.
#pragma once
#include "k2000/core/Layout.h"
#include "k2000/managers/IKModule.h"

class CRenderer;
class TextureBank;

class CKGraphic : public IKModule {
public:
    DOTD_CLASS_KEY(kCategoryManager, 2)

    CKGraphic();  // 0x00059558 CKGraphic_Construct (inlined in CKGraphic_Create 0x5a780)
    ~CKGraphic() override;

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x0005a338 CKGraphic_Load
    void Destroy() override;                            // vt+0x10 0x0005a5c8 CKGraphic_Destroy (the level unload)
    // vt+0x30 0x0005a530 CKGraphic_PostLoad: for every type but 1 the renderer's PostLoad (C2.4 step 6: the backgrounds hidden)
    // and the texture bank's (a bare return).
    int32_t PostLoad(int32_t type) override;

    static IKBaseClass* Create();                       // 0x0005a780 CKGraphic_Create
    static void Delete(IKBaseClass* object);

    void Start() override;                    // vt+0x50 0x59c40
    void Stop() override;                         // vt+0x68 0x5a128 CKGraphic_Stop: the videos, the flash interfaces and the spawn shakes stopped
    void Pause() override {}                         // vt+0x70 0x59e78
    void Resume() override {}                        // vt+0x78 0x59e48
    void Update(IKTime* frameClock) override;        // vt+0x7c 0x59c00 (shader manager clock hook)
    // vt+0x90 0x00059ea8 CKGraphic_PostSectorUnload: the spawn manager's 0xb8e20 (a bare return).
    void PostSectorUnload(int32_t sector) override;
    // vt+0x84 0x00059ed8 CKGraphic_PreSectorLoaded: the spawn manager's pools start their shake caches of the sector.
    void PreSectorLoaded(int32_t sector) override;
    int32_t InitializeModule(void* params) override;     // vt+0x94 0x5a7e8 CKGraphic_InitializeModule
    void DestroyModule() override;                        // vt+0x98 0x59c88 CKGraphic_DestroyModule
    void PreUpdate(IKTime* frameClock) override;     // vt+0x9c 0x595c8 (empty)
    void PostUpdate(IKTime* frameClock) override;    // vt+0xa0 0x595d0 (empty)
    void UpdateLocalizedData() override;             // vt+0xa8 0x5a180 CKGraphic_UpdateLocalizedData
    // C1.6 gm: vt+0xac 0x000596c8 CKGraphic_DestroyLocalizedData: the 2D manager's level fonts (vt+0x7c).
    void DestroyLocalizedData() override;

    // C1.6 gm: the options' screen offset. 0x595f0 KStub_Return0_595f0 takes (x, y) and does nothing; the
    // offset fields are only read back (0x000595f8 Graphics_GetScreenOffset_maybe).
    uint32_t SetScreenOffset(int32_t /*x*/, int32_t /*y*/) { return 0; }
    void GetScreenOffset(int32_t* x, int32_t* y);

    // 0x000599c0 CKGraphic_CreateRenderer: CRenderer (key 0x4d) + InitializeRendererStages.
    CRenderer* CreateRenderer(void* startupContext);
    // CKGraphic_UpdateSceneWorldMatrices_maybe (UpdateGame's reset path)
    void UpdateSceneWorldMatrices();

    // vt+0x20 0x59f58 CKGraphic_FindNonRecreableInstances: the globals of categories 10/11/13 (renderer managers).
    uint8_t FindNonRecreableInstances(int32_t category, uint32_t id, uint32_t count, void* out) override;

    CRenderer* m_renderer;                  // +0x04 XXL2 m_pRenderer (CKGraphic_FindNonRecreableInstances and CVideoManager_InitRenderer read it)
    TextureBank* m_pTextureManager;         // +0x08 XXL2 m_pTextureManager (InitializeModule)
    IKSerializable* m_animationManager;     // +0x0c XXL2 m_pAnimationManager: CAnimationManager (13:8, key 0x20d)
    uint32_t m_baHardwareCaps;              // +0x10 XXL2 m_baHardwareCaps_maybe (InitializeModule sets bits)
    int32_t m_i32XScreenOffset;             // +0x14 XXL2 order_maybe
    int32_t m_i32YScreenOffset;             // +0x18 XXL2 order_maybe
    void* m_pFogTexture;                    // +0x1c DotD: the level's fog texture (an RwTexture, IKFile_ReadTextureRef, resolved): the ramp of the fog colour and amount the shaders sample on unit 7 (C2.4 step 6); not set by the constructor
    void* m_unk20;                          // +0x20 DotD: the 16x16 blank texture (InitializeModule)
    uint8_t m_unk24;                        // +0x24
    uint8_t m_pad25[3];
    uint32_t m_unk28;                       // +0x28 *params (InitializeModule); not set by the constructor
    uint32_t m_unk2c;                       // +0x2c
};
DOTD_ASSERT_SIZE(CKGraphic, 0x30);
DOTD_ASSERT_OFFSET(CKGraphic, m_renderer, 0x04);
DOTD_ASSERT_OFFSET(CKGraphic, m_pTextureManager, 0x08);
DOTD_ASSERT_OFFSET(CKGraphic, m_pFogTexture, 0x1c);
DOTD_ASSERT_OFFSET(CKGraphic, m_unk28, 0x28);

// 0x00059990 Rw_PurgeFreeLists_maybe (CKLoadingManager_UnloadSector, after a level unload):
// RwFreeListPurgeAllFreeLists and RwResourcesEmptyArena. The argument is not used.
void Rw_PurgeFreeLists(CKGraphic* graphic);
