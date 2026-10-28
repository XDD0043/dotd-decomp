// CShaderManagerPSGL_2.cpp - reconstructed original translation unit 0xff620-0x100bf0 (GAME_TOC1, main_toc1), 24 functions, 24 live.
// Primary owner: CShaderManagerPSGL (not a registered class)
// Other owners: ShaderManagerPSGL (2), ConstructShaderManagerPSGL (2), RegisterCShaderManagerPSGLClass (1), PreparePSGLAtomicMeshShaders (1), InstallPSGLMeshCallbacks (1), DrawPSGLMeshPasses (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [ ] 0xff620  RegisterCShaderManagerPSGLClass
//   [ ] 0xff698  _GLOBAL__I_ff698
//   [ ] 0xff6a8  CShaderManagerPSGL_UpdateProfileCapabilities_maybe
//   [x] 0xff778  PreparePSGLAtomicMeshShaders
//   [ ] 0xff888  CShaderManagerPSGL_CreateAtomicPipeline
//   [~] 0xff960  InstallPSGLMeshCallbacks (the Im2D shader bind callback; the atomic pipelines' callbacks are direct calls)
//   [x] 0xffb58  CShaderManagerPSGL_Load
//   [ ] 0xffb80  CShaderManagerPSGL_Save
//   [ ] 0xffba8  CShaderManagerPSGL_LevelReset
//   [ ] 0xffbd0  CShaderManagerPSGL_ClearReferences
//   [ ] 0xffbf8  CShaderManagerPSGL_DeletingDestructor
//   [ ] 0xffc40  CShaderManagerPSGL_Destructor
//   [ ] 0xffc70  CShaderManagerPSGL_Destruct_maybe
//   [ ] 0xffca0  CShaderManagerPSGL_DestroyArray
//   [x] 0xffd58  ShaderManagerPSGL_BindImmediate2DShaders_maybe
//   [ ] 0xffde8  ShaderManagerPSGL_BindImmediate3DShaders_maybe
//   [x] 0xffe78  DrawPSGLMeshPasses
//   [ ] 0x100638  CShaderManagerPSGL_vf5C
//   [ ] 0x100640  CShaderManagerPSGL_ResetRuntime_maybe
//   [ ] 0x100698  CShaderManagerPSGL_ReleaseShaderResources_maybe
//   [x] 0x1007f0  ConstructShaderManagerPSGL
//   [ ] 0x100978  CShaderManagerPSGL_CreateArray
//   [ ] 0x100a20  CShaderManagerPSGL_Create
//   [ ] 0x100a68  ConstructShaderManagerPSGL_2
//
//   [ ] 0x9a6260  CShaderManagerPSGL_IsKindOf  [inline]
//   [ ] 0x9a6288  CShaderManagerPSGL_GetClassGroup  [inline]
//   [ ] 0x9a6290  CShaderManagerPSGL_GetClassId  [inline]
#include "k2000/render/CShaderManagerPSGL.h"

#include <cstring>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include "Renderware/rpworld/RpAtomic.h"
#include "Renderware/rpworld/RpGeometry.h"
#include "Renderware/rwcore/RwDevice.h"
#include "Renderware/rwcore/RwTexture.h"
#include "k2000/io/IKFile.h"
#include "k2000/render/Immediate2DShaderPassState.h"
#include "k2000/render/MeshShaderPassState.h"
#include "k2000/render/ShaderMatrixCache.h"
#include "k2000/render/ShaderVariantKey.h"
#include "platform/gfx/mesh.h"

// 0x000ffb58 CShaderManagerPSGL_Load: the base's Load (0xf8888), then 1.
int32_t CShaderManagerPSGL::Load(IKFile* file, int32_t type) {
    LoadBase(file, type);
    return 1;
}

// ==== the atomic pipeline's mesh callbacks (C2.4 step 3) ==============================================
// The original keeps the pass state at 0x00c685c0 (copied out of PreparePSGLAtomicMeshShaders' stack object) and the
// current key at g_ShaderManagerPSGL +0x4c; both live here as file state.

namespace {
std::unique_ptr<MeshShaderPassState> g_pass;           // 0x00c685c0
ShaderVariantKey g_key;                                // g_ShaderManagerPSGL +0x4c
const dotd::gfx::cg::Program* g_program = nullptr;     // the programs BindSelectedPSGLShaderPrograms bound

// A uniform of a program and how it is filled: a ShaderUniformId (>= 0) or a boolean constant slot.
struct BoundUniform {
    int location = -1;
    int id = -1;
    int boolSlot = -1;
    std::string glslType;
    int count = 1;
};
struct ProgramUniforms {
    std::vector<BoundUniform> uniforms;
    int alphaFunc = -1;
    int alphaRef = -1;
};
std::map<uint32_t, ProgramUniforms> g_programUniforms;

const ProgramUniforms& UniformsOf(const dotd::gfx::cg::Program* program) {
    auto found = g_programUniforms.find(program->glProgram);
    if (found != g_programUniforms.end()) return found->second;
    ProgramUniforms entry;
    std::map<std::string, int32_t> idsByName;
    for (int32_t id = 0; id <= kPscGauss5x5; ++id) {
        if (const char* name = ShaderUniformCgName(id)) idsByName.emplace(name, id);
    }
    auto collect = [&](const dotd::gfx::cg::Translation& stage) {
        for (const dotd::gfx::cg::UniformInfo& info : stage.uniforms) {
            BoundUniform bound;
            bound.location = dotd::gfx::UniformLocation(program->glProgram, info.name.c_str());
            if (bound.location < 0) continue;  // optimised out of the linked program
            bound.glslType = info.glslType;
            bound.count = info.arraySize > 0 ? info.arraySize : 1;
            if (info.name == "u_bModulateVertex") bound.boolSlot = 0;
            else if (info.name == "u_bVertexColorFirst") bound.boolSlot = 1;
            else {
                auto id = idsByName.find(info.name);
                if (id == idsByName.end()) continue;
                bound.id = id->second;
            }
            entry.uniforms.push_back(bound);
        }
    };
    collect(program->vertex);
    collect(program->pixel);
    entry.alphaFunc = dotd::gfx::UniformLocation(program->glProgram, "dotd_alphaFunc");
    entry.alphaRef = dotd::gfx::UniformLocation(program->glProgram, "dotd_alphaRef");
    return g_programUniforms.emplace(program->glProgram, std::move(entry)).first->second;
}

// 0x000fda80 BindSelectedPSGLShaderPrograms: the programs of the current key.
void SelectProgram() {
    ShaderVariantKey_BuildForMesh(&g_key, g_pass.get());
    g_program = ShaderVariant_GetProgram(g_key);
}

// The fill of every uniform of the bound program from the pass state (BindPSGLShaderProgramWithParameters 0xf5128:
// the world matrix, FillShaderUniformFromPassState per record, the boolean constants, the upload).
void FillUniforms(const dotd::gfx::cg::Program* program, ShaderPassState* pass) {
    const ProgramUniforms& uniforms = UniformsOf(program);
    ShaderMatrixCache_SetWorld(pass->GetWorldMatrix());  // PrepareVertexProgramWorldMatrix 0xff118
    // The largest record is the bone palette (210 registers); the others hold at most 72 (the point lights' arrays).
    static float buffer[kSkinBoneMatrixFloats];
    for (const BoundUniform& u : uniforms.uniforms) {
        if (u.boolSlot >= 0) {
            dotd::gfx::SetUniformInt(u.location, static_cast<int>(ShaderPassState_EnableFlag(pass, u.boolSlot)));
            continue;
        }
        std::memset(buffer, 0, u.id == kVscBoneMatrices ? sizeof buffer : 4 * 72 * sizeof(float));
        FillShaderUniformFromPassState(pass, u.id, buffer);
        dotd::gfx::SetUniform(u.location, u.glslType.c_str(), u.count, buffer);
    }
}
void FillUniforms(const dotd::gfx::cg::Program* program) { FillUniforms(program, g_pass.get()); }

// 0x000ffd58 ShaderManagerPSGL_BindImmediate2DShaders_maybe (the Im2D pipeline's shader bind callback): the pass state
// of an Im2D draw (Immediate2DShaderPassState_Construct_maybe 0xf2d48), its key into the manager's (+0x4c,
// ShaderVariantKey_BuildFromPassState_maybe 0xf0108), the programs bound with their uniforms (BindSelectedPSGLShaderPrograms
// 0xfda80), the post mode +0x48 cleared. STUB(C2.9): only the post passes (mode 1..7) draw through the uber-shader; every
// other Im2D draw (menus, HUD, videos, mode 0) keeps the device's 2D program (texture times vertex colour, which the
// mode-0 variant computes too) until the front end is compared with RPCS3 through the uber-shader.
uint32_t BindImmediate2DShaders() {
    CShaderManagerPSGL* manager = g_pShaderManager;
    Immediate2DShaderPassState pass;
    ShaderVariantKey_BuildFromPassState(&g_key, &pass);
    const uint32_t mode = manager->m_ui32Immediate2DMode;
    manager->m_ui32Immediate2DMode = 0;
    if (mode == 0) return 0;
    const dotd::gfx::cg::Program* program = ShaderVariant_GetProgram(g_key);
    if (program == nullptr || program->glProgram == 0) return 0;
    dotd::gfx::BindTarget();
    dotd::gfx::UseProgram(program->glProgram);
    FillUniforms(program, &pass);
    pass.BindMaterialTextures();  // vt+0xd0 MeshShaderPassState_BindFallbackTextureUnit7_maybe 0xf69c8
    return program->glProgram;
}
}  // namespace

// 0x001007f0 ConstructShaderManagerPSGL: CShaderManager_InvalidateProfileCapabilities_maybe 0xf7e68 (+0x44 = 0), +0x40 = 4,
// then the best profile mode of the vertex and fragment profiles (6 each for the RSX profiles; the smaller of the two),
// +0x44 when it reaches the default mode +0x3c, and with it the atomic pipeline (+0x45) and the mesh callbacks.
// cgGLGetLatestProfile(CG_GL_VERTEX 8 / CG_GL_FRAGMENT 9) answers the PS3's RSX profiles: the GL port runs the programs
// written for them (platform/gfx/cg_program.h). The other constructor stores (+0x64..+0x80: TOC pointers that the base's
// Load overwrites, +0x85e4) are not modelled.
CShaderManagerPSGL::CShaderManagerPSGL() {
    m_bShadersEnabled = 0;
    m_i32ProfileMode = 4;
    const int32_t vertexProfile = 0x1b5b;    // cgGLGetLatestProfile(8)
    const int32_t fragmentProfile = 0x1b5c;  // cgGLGetLatestProfile(9)
    int32_t mode = vertexProfile == 0x1b5b ? 6 : 0;
    const uint32_t vertexMode = static_cast<uint32_t>(mode);
    const int32_t fragment = fragmentProfile == 0x1b5c ? 6 : 0;
    if (static_cast<uint32_t>(fragment) <= vertexMode) mode = fragment;
    m_i32ProfileMode = mode;
    m_bShadersEnabled = 1;
    if (mode < m_i32DefaultShaderMode) m_bShadersEnabled = 0;
    if (m_bShadersEnabled != 0) {
        m_bAtomicPipeline = 1;
        // 0x000ff888 CShaderManagerPSGL_CreateAtomicPipeline: the RenderWare pipeline objects are not modelled (every
        // atomic renders through RpAtomicPSGL_Render, C2.4 step 3), so it cannot fail here.
        if (m_bAtomicPipeline != 0) InstallPSGLMeshCallbacks(this);
    }
}

// 0x000ff960 InstallPSGLMeshCallbacks (with +0x44): the atomic, skin and team pipelines' setup / prepare-mesh /
// draw callbacks (direct calls of PreparePSGLAtomicMeshShaders and DrawPSGLMeshPasses in RpAtomicPSGL.cpp), the
// immediate 3D pipeline's shader bind callback (STUB(C2.7): the Im3D draws keep the device program; the immediate 3D pipeline draws the PTank particles and the 2D shapes, and the particles are C2.7) and the Im2D one.
void InstallPSGLMeshCallbacks(CShaderManagerPSGL* manager) {
    if (manager->m_bShadersEnabled == 0) return;
    RwDevice_SetIm2DShaderBindCallBack(&BindImmediate2DShaders);  // PSGLIm2D_SetShaderBindCallBack_maybe 0x735968
}

// 0x000ff778 PreparePSGLAtomicMeshShaders: ConstructMeshShaderPassState(atomic, the mesh's material), the key
// (ShaderVariantKey_BuildForMesh_maybe) and the programs (BindSelectedPSGLShaderPrograms).
void PreparePSGLAtomicMeshShaders(RpDeviceMesh* mesh, RpAtomic* atomic) {
    g_pass.reset(new MeshShaderPassState(atomic, mesh->record.material));
    SelectProgram();
}

// 0x000ffe78 DrawPSGLMeshPasses. Pass 0 uses the programs Prepare selected; each later pass selects again (the key
// follows the pass's light counters), blends additively (RW states 0xc vertex alpha on, 0xa source alpha, 0xb
// destination one) and draws the mesh again. The texture units 0..3 are cleared after every pass in the original; the
// next pass rebinds them here.
void DrawPSGLMeshPasses(RpDeviceMesh* mesh, uint32_t geometryFlags) {
    (void)geometryFlags;  // the attribute layout is part of the device mesh
    static const float kDefaults[16][4] = {{0, 0, 0, 1}, {1, 0, 0, 0}, {0, 0, 1, 0}, {1, 1, 1, 1}, {0, 0, 0, 1}, {0, 0, 0, 0},
                                           {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0},
                                           {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}};
    RpMaterial* material = mesh->record.material;
    while (g_pass->m_passIndex < g_pass->m_passCount) {
        const bool later = g_pass->m_passIndex != 0;
        if (later) SelectProgram();
        const dotd::gfx::cg::Program* program = g_program;
        if (program != nullptr && program->glProgram != 0) {
            dotd::gfx::BindTarget();
            dotd::gfx::UseProgram(program->glProgram);
            FillUniforms(program);
            // The diffuse texture (unit 0), then the material's extra textures (vt+0xd0).
            if (material->texture != nullptr && material->texture->raster != nullptr) {
                dotd::gfx::BindTextureUnit(0, RwDevice_GetRasterTexture(material->texture->raster),
                                           RwDevice_TextureState(material->texture));
            } else {
                dotd::gfx::BindTextureUnit(0, 0, dotd::gfx::DrawState());
            }
            g_pass->BindMaterialTextures();
            int alphaFunc = 8;
            float alphaRef = 0.0f;
            dotd::gfx::DrawState state = RwDevice_CurrentMeshState(&alphaFunc, &alphaRef);
            if (later) {
                state.blend = true;
                state.srcBlend = dotd::gfx::Blend::kSrcAlpha;
                state.dstBlend = dotd::gfx::Blend::kOne;
            }
            dotd::gfx::ApplyState(state);
            const ProgramUniforms& uniforms = UniformsOf(program);
            dotd::gfx::SetUniformInt(uniforms.alphaFunc, alphaFunc);
            const float ref = alphaRef;
            dotd::gfx::SetUniform(uniforms.alphaRef, "float", 1, &ref);
            const RpNativeMesh& m = mesh->record;
            dotd::gfx::DrawMesh(mesh->gfxMesh, m.primType, m.indexed != 0, m.firstIndex, m.lastIndex,
                                m.indexed != 0 ? m.numIndices : m.numVertices, m.firstIndex, kDefaults);
        }
        g_pass->AdvanceToNextPass();
    }
    dotd::gfx::UseProgram(0);
}
