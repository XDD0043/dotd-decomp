// CShaderManagerPSGL.h - shader programs, the shader cache and the embedded Cg compiler (key 0x124d,
// size 0x85e8). Original units: CShaderManagerPSGL*.cpp. Created by CKGraphic_InitializeModule; the
// global 0x00c685e0 points to it. The layout before +0x64 is not modelled (the fields below carry their PS3 offsets
// in comments; the variant key +0x4c lives in CShaderManagerPSGL_2.cpp).
#pragma once
#include "k2000/core/IKUpdatable.h"

class CShaderManagerPSGL : public IKUpdatable {
public:
    DOTD_CLASS_KEY(kCategoryGraphical, 0x49)

    // 0x001007f0 ConstructShaderManagerPSGL (the profile part and the pipelines; the members' construction,
    // ConstructMembers 0xf9138: +0x3c = 6, +0x44 = +0x45 = 0, is the initializers below).
    CShaderManagerPSGL();
    ~CShaderManagerPSGL() override;

    static IKBaseClass* Create();
    static void Delete(IKBaseClass* object);

    void Start() override;   // vt+0x50 0x100640 CShaderManagerPSGL_ResetRuntime_maybe (cgCreateContext)
    void Stop() override {}
    void Pause() override {}
    void Resume() override {}
    void Update(IKTime*) override {}
    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0xffb58 CShaderManagerPSGL_Load

    // 0x000f8888 KBase11CD_vf2C: the base class's Load (KBase11CD, not modelled yet).
    int32_t LoadBase(IKFile* file, int32_t type);

    int32_t m_i32DefaultShaderMode = 6;  // +0x3c (ShaderSceneInputs::defaultShaderMode reads the same value)
    // +0x40 the best Cg profile mode: 6 when cgGLGetLatestProfile gives the RSX vertex and fragment profiles
    // (CG_PROFILE_SCE_VP_RSX 0x1b5b, CG_PROFILE_SCE_FP_RSX 0x1b5c), else 0.
    int32_t m_i32ProfileMode = 4;
    // +0x44 the shader pipelines are in use (the profile mode reaches +0x3c); every post effect tests it.
    uint8_t m_bShadersEnabled = 0;
    uint8_t m_bAtomicPipeline = 0;  // +0x45 CShaderManagerPSGL_CreateAtomicPipeline 0xff888 made the atomic pipeline
    // +0x48 the post pass of the next Im2D draw (Immediate2DShaderPassState: 1 post depth of field, 2 Gaussian blur
    // 5x5, 3 copy to alpha, 4 down-sample 4x4, 5 the texture's alpha not modulated, 6 down-sample 16x16, 7 bloom; 0
    // the plain 2D shader). ShaderManagerPSGL_BindImmediate2DShaders_maybe clears it after every Im2D draw.
    uint32_t m_ui32Immediate2DMode = 0;
    // Read by the base's Load (PS3 offsets; the layout before them is not modelled yet).
    uint32_t m_unk64[6];  // +0x64 floats_maybe (LVL000: 0, -1, 0, 0, 1, 0)
    uint32_t m_unk7c[2];  // +0x7c floats_maybe (LVL000: 1, 0.2)
};

// 0x00c685e0
extern CShaderManagerPSGL* g_pShaderManager;

// ---- C2.4 step 3: the atomic pipeline's mesh callbacks (CShaderManagerPSGL_2.cpp) --------------------------
struct RpAtomic;
struct RpDeviceMesh;
// 0x000ff778 PreparePSGLAtomicMeshShaders (the pipeline's private +0x14): the pass state of the mesh drawn by `atomic`,
// its shader variant key and program. The state stays current for the DrawPSGLMeshPasses call that follows.
void PreparePSGLAtomicMeshShaders(RpDeviceMesh* mesh, RpAtomic* atomic);
// 0x000ffe78 DrawPSGLMeshPasses (private +0x1c): the passes of the current pass state: program, uniforms, textures,
// render states and the draw of the mesh, once per pass (more lights than the shader has slots mean more passes).
void DrawPSGLMeshPasses(RpDeviceMesh* mesh, uint32_t geometryFlags);

// 0x000ff960 InstallPSGLMeshCallbacks (CShaderManagerPSGL_2.cpp): the pipelines' shader callbacks (the Im2D one here).
void InstallPSGLMeshCallbacks(CShaderManagerPSGL* manager);

// 0x000f7fd8 BeginRenderCameraUpdate: BeginCameraUpdateAndCacheShaderMatrices 0x247ff8 (RwCameraBeginUpdate, then with the
// shader pipelines the view and projection copied into the shader matrix cache); the camera or null.
struct RwCamera;
RwCamera* BeginRenderCameraUpdate(RwCamera* camera);
