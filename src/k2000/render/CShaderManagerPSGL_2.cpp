// CShaderManagerPSGL_2.cpp - reconstructed original translation unit 0xff620-0x100bf0 (GAME_TOC1, main_toc1), 24 functions, 24 live.
// Primary owner: CShaderManagerPSGL (not a registered class)
// Other owners: ShaderManagerPSGL (2), ConstructShaderManagerPSGL (2), RegisterCShaderManagerPSGLClass (1), PreparePSGLAtomicMeshShaders (1), InstallPSGLMeshCallbacks (1), DrawPSGLMeshPasses (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [ ] 0xff620  RegisterCShaderManagerPSGLClass
//   [ ] 0xff698  _GLOBAL__I_ff698
//   [x] 0xff6a8  CShaderManagerPSGL_UpdateProfileCapabilities_maybe  (CShaderManagerPSGL::Vf64)
//   [x] 0xff778  PreparePSGLAtomicMeshShaders
//   [x] 0xff888  CShaderManagerPSGL_CreateAtomicPipeline  (CShaderManagerPSGL::Vf60 and the constructor)
//   [~] 0xff960  InstallPSGLMeshCallbacks (the Im3D / Im2D shader bind callbacks and the PTank hook; the atomic pipelines' callbacks are direct calls)
//   [x] 0xffb58  CShaderManagerPSGL_Load
//   [ ] 0xffb80  CShaderManagerPSGL_Save
//   [x] 0xffba8  CShaderManagerPSGL_LevelReset  (KBase11CD's (nothing), then 1: IKSerializable's default)
//   [x] 0xffbd0  CShaderManagerPSGL_ClearReferences  (inherited: KStub_Nop_f8828)
//   [x] 0xffbf8  CShaderManagerPSGL_DeletingDestructor  (BootStubs.cpp's ~CShaderManagerPSGL and the delete)
//   [x] 0xffc40  CShaderManagerPSGL_Destructor  (BootStubs.cpp's ~CShaderManagerPSGL)
//   [ ] 0xffc70  CShaderManagerPSGL_Destruct_maybe  [dead: no pointer to its descriptor 0xb56cb8, no call]
//   [x] 0xffca0  CShaderManagerPSGL_DestroyArray  (CShaderManagerPSGL::DeleteArray)
//   [x] 0xffd58  ShaderManagerPSGL_BindImmediate2DShaders_maybe
//   [x] 0xffde8  ShaderManagerPSGL_BindImmediate3DShaders_maybe
//   [x] 0xffe78  DrawPSGLMeshPasses
//   [x] 0x100638  CShaderManagerPSGL_vf5C  (empty: IKUpdatable's PreRestart)
//   [ ] 0x100640  CShaderManagerPSGL_ResetRuntime_maybe  [platform]  (the Cg context (CgRuntime_EnableEmbeddedCompiler, cgCreateContext): BootStubs.cpp's Start; cg_program needs no context)
//   [x] 0x100698  CShaderManagerPSGL_ReleaseShaderResources_maybe
//   [x] 0x1007f0  ConstructShaderManagerPSGL
//   [x] 0x100978  CShaderManagerPSGL_CreateArray  (CShaderManagerPSGL::CreateArray)
//   [x] 0x100a20  CShaderManagerPSGL_Create  (BootStubs.cpp's CShaderManagerPSGL::Create)
//   [ ] 0x100a68  ConstructShaderManagerPSGL_2  [dead: no pointer to its descriptor 0xb56d80, no call]
//
//   [ ] 0x9a6260  CShaderManagerPSGL_IsKindOf  [inline]
//   [ ] 0x9a6288  CShaderManagerPSGL_GetClassGroup  [inline]
//   [ ] 0x9a6290  CShaderManagerPSGL_GetClassId  [inline]
#include "k2000/render/CShaderManagerPSGL.h"

#include <cstring>
#include <map>
#include <memory>
#include <new>
#include <string>
#include <unordered_map>
#include <vector>

#include "Renderware/rpworld/RpAtomic.h"
#include "Renderware/rpworld/RpGeometry.h"
#include "Renderware/rwcore/RwDevice.h"
#include "Renderware/rwcore/RwIm3D.h"
#include "Renderware/rwcore/RwTexture.h"
#include "k2000/io/IKFile.h"
#include "k2000/render/Immediate2DShaderPassState.h"
#include "k2000/render/Immediate3DShaderPassState.h"
#include "k2000/render/MeshShaderPassState.h"
#include "k2000/render/ShaderMatrixCache.h"
#include "k2000/render/ShaderVariantKey.h"
#include "platform/config.h"
#include "platform/gfx/cg_program.h"
#include "platform/gfx/device.h"
#include "platform/gfx/mesh.h"
#include "platform/gfx/raster.h"
#include "platform/heap_fill.h"

// 0x000ffb58 CShaderManagerPSGL_Load: the base's Load (0xf8888), then 1.
int32_t CShaderManagerPSGL::Load(IKFile* file, int32_t type) {
    LoadBase(file, type);
    return 1;
}

// ==== the atomic pipeline's mesh callbacks (C2.4 step 3) ==============================================
// The original keeps the pass state at 0x00c685c0 (copied out of PreparePSGLAtomicMeshShaders' stack object) and the
// current key at g_ShaderManagerPSGL +0x4c; both live here as file state.

namespace {
// PERF: the pass state lives in one block of static storage (it was a heap block made and freed for every mesh draw).
// The block is filled as a new heap block is (platform/heap_fill.h) before each construction, so the object starts from
// the same bytes as before.
alignas(MeshShaderPassState) unsigned char g_passStorage[sizeof(MeshShaderPassState)];
MeshShaderPassState* g_pass = nullptr;                 // 0x00c685c0

void NewMeshPass(RpAtomic* atomic, RpMaterial* material) {
    if (g_pass != nullptr) g_pass->~MeshShaderPassState();
    dotd::HeapFill(g_passStorage, sizeof g_passStorage);
    g_pass = new (g_passStorage) MeshShaderPassState(atomic, material);
}
ShaderVariantKey g_key;                                // g_ShaderManagerPSGL +0x4c
const dotd::gfx::cg::Program* g_program = nullptr;     // the programs BindSelectedPSGLShaderPrograms bound

// A uniform of a program and how it is filled: a ShaderUniformId (>= 0) or a boolean constant slot.
// perf: the type is parsed once (dotd::gfx::UniformType) and the value last uploaded is kept (lastOffset into the
// program's lastValues, lastInt for the boolean slots): a uniform is a GL program object's state, and nothing but
// FillUniforms writes these locations (DrawThroughProgram / DrawPSGLMeshPasses set only dotd_alphaFunc / dotd_alphaRef,
// through gfx::SetAlphaTest; cg_program the samplers at link time), so an upload of the value the program already holds
// is skipped.
struct BoundUniform {
    int location = -1;
    int id = -1;
    int boolSlot = -1;
    dotd::gfx::UniformType type = dotd::gfx::UniformType::kUnknown;
    int count = 1;
    int floats = 0;       // floats the upload reads (dotd::gfx::UniformFloats)
    size_t lastOffset = 0;
    int lastInt = 0;
    bool known = false;   // lastValues / lastInt hold what the program has
};
struct ProgramUniforms {
    std::vector<BoundUniform> uniforms;
    std::vector<float> lastValues;
};
std::unordered_map<uint32_t, ProgramUniforms> g_programUniforms;  // by GL program (node-based: entries never move)
uint32_t g_lastUniformsProgram = 0;                                // perf: the last lookup
ProgramUniforms* g_lastUniforms = nullptr;

ProgramUniforms& UniformsOf(const dotd::gfx::cg::Program* program) {
    if (g_lastUniforms != nullptr && g_lastUniformsProgram == program->glProgram) return *g_lastUniforms;
    auto found = g_programUniforms.find(program->glProgram);
    if (found != g_programUniforms.end()) {
        g_lastUniformsProgram = program->glProgram;
        g_lastUniforms = &found->second;
        return found->second;
    }
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
            bound.type = dotd::gfx::UniformTypeOf(info.glslType.c_str());
            bound.count = info.arraySize > 0 ? info.arraySize : 1;
            bound.floats = dotd::gfx::UniformFloats(bound.type, bound.count);
            if (info.name == "u_bModulateVertex") bound.boolSlot = 0;
            else if (info.name == "u_bVertexColorFirst") bound.boolSlot = 1;
            else {
                auto id = idsByName.find(info.name);
                if (id == idsByName.end()) continue;
                bound.id = id->second;
            }
            bound.lastOffset = entry.lastValues.size();
            if (bound.boolSlot < 0) entry.lastValues.resize(entry.lastValues.size() + static_cast<size_t>(bound.floats));
            entry.uniforms.push_back(bound);
        }
    };
    collect(program->vertex);
    collect(program->pixel);
    ProgramUniforms& stored = g_programUniforms.emplace(program->glProgram, std::move(entry)).first->second;
    g_lastUniformsProgram = program->glProgram;
    g_lastUniforms = &stored;
    return stored;
}

// 0x000fda80 BindSelectedPSGLShaderPrograms's last store: after the programs are bound, the manager's flag word +0x8c
// (ShaderSceneInputs::managerFlags) gets bits 0 (shadow textures) and 1 (point lights) set and bit 2 (far texture)
// cleared, whatever the pass state was. CGeometry::Render and ParticleDraw_SetShaderParticleFlags_maybe 0x88190 set the
// three bits again for their geometry; the key of a mesh's later pass reads what the bind of its first pass left.
void MarkProgramsBound() {
    ShaderSceneInputs& scene = SceneInputs();
    scene.managerFlags = (scene.managerFlags & ~7u) | 3u;
}

// 0x000fda80 BindSelectedPSGLShaderPrograms: the programs of the current key.
void SelectProgram() {
    ShaderVariantKey_BuildForMesh(&g_key, g_pass);
    g_program = ShaderVariant_GetProgram(g_key);
    MarkProgramsBound();
}

// The fill of every uniform of the bound program from the pass state (BindPSGLShaderProgramWithParameters 0xf5128:
// the world matrix, FillShaderUniformFromPassState per record, the boolean constants, the upload). An upload whose
// value the program already holds is skipped (BoundUniform).
void FillUniforms(const dotd::gfx::cg::Program* program, ShaderPassState* pass) {
    ProgramUniforms& uniforms = UniformsOf(program);
    ShaderMatrixCache_SetWorld(pass->GetWorldMatrix());  // PrepareVertexProgramWorldMatrix 0xff118
    // The largest record is the bone palette (210 registers); the others hold at most 72 (the point lights' arrays).
    static float buffer[kSkinBoneMatrixFloats];
    constexpr int kRecordFloats = 4 * 72;
    for (BoundUniform& u : uniforms.uniforms) {
        if (u.boolSlot >= 0) {
            const int value = static_cast<int>(ShaderPassState_EnableFlag(pass, u.boolSlot));
            if (u.known && u.lastInt == value) continue;
            dotd::gfx::SetUniformInt(u.location, value);
            u.lastInt = value;
            u.known = true;
            continue;
        }
        // Only the floats the upload reads need clearing (the record size as before: the bone palette or 72 registers;
        // beyond that the buffer keeps what the earlier fills left, as it did).
        const int clear = u.id == kVscBoneMatrices ? kSkinBoneMatrixFloats : kRecordFloats;
        std::memset(buffer, 0, static_cast<size_t>(u.floats < clear ? u.floats : clear) * sizeof(float));
        FillShaderUniformFromPassState(pass, u.id, buffer);
        float* last = uniforms.lastValues.data() + u.lastOffset;
        const size_t bytes = static_cast<size_t>(u.floats) * sizeof(float);
        if (u.known && std::memcmp(last, buffer, bytes) == 0) continue;
        dotd::gfx::SetUniformTyped(u.location, u.type, u.count, buffer);
        std::memcpy(last, buffer, bytes);
        u.known = true;
    }
}
void FillUniforms(const dotd::gfx::cg::Program* program) { FillUniforms(program, g_pass); }

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
    MarkProgramsBound();  // BindSelectedPSGLShaderPrograms runs for every Im2D draw
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

// 0x000ffde8 ShaderManagerPSGL_BindImmediate3DShaders_maybe (the immediate 3D pipeline's shader bind callback,
// DrawPSGLImmediateGeometry 0x76b610 calls it with the pool's descriptor before every Im3D draw: the Rt2d shapes, brushes
// and fonts, the 2D billboards' outlines): the pass state of the draw on the stack (ShaderPassStateBase_Construct_maybe
// 0xf5260, the vtable 0xb18f28 and +0x14 = the descriptor: Immediate3DShaderPassState_Construct_maybe 0xf3040 inlined), its
// key into the manager's (+0x4c, ShaderVariantKey_BuildForImmediate3D_maybe 0xf07a8), the programs bound with their
// uniforms (BindSelectedPSGLShaderPrograms 0xfda80), the pass state destroyed (0xf2fe0). The key: mode 0, no lights, no
// fog, vertex colour and material modulation (RwIm3DTransform always adds rwIM3D_VERTEXXYZ | rwIM3D_VERTEXRGBA), one
// texture coordinate set with rwIM3D_VERTEXUV, the first pass: the uber-shader's colour is the vertex colour (times the
// texture), the position the LTM times the camera's view-projection.
// The shader matrix cache is refreshed from the device's current camera first, as RpAtomicPSGL_Render does for the
// atomics (the PS3 copies it in BeginRenderCameraUpdate 0xf7fd8: the UI camera's Rt2d draws begin there too).
uint32_t BindImmediate3DShaders(const RwIm3DDraw& draw) {
    Immediate3DShaderPassState pass(&draw);
    ShaderVariantKey_BuildForImmediate3D(&g_key, &pass);
    const dotd::gfx::cg::Program* program = ShaderVariant_GetProgram(g_key);
    MarkProgramsBound();
    if (program == nullptr || program->glProgram == 0) return 0;
    ShaderMatrixCache_BeginCamera();
    dotd::gfx::BindTarget();
    dotd::gfx::UseProgram(program->glProgram);
    FillUniforms(program, &pass);
    pass.BindMaterialTextures();  // vt+0xd0 MeshShaderPassState_BindFallbackTextureUnit7_maybe 0xf69c8
    return program->glProgram;
}

// The PTank quads' bind (RwDevice_SetIm3DShaderBindOverride): the programs and the pass state the PTank's shader hook
// prepared (PreparePSGLAtomicMeshShaders with the PTank atomic: its first material's mesh pass state and key).
uint32_t BindPreparedMeshPrograms(const RwIm3DDraw& /*draw*/) {
    const dotd::gfx::cg::Program* program = g_program;
    if (program == nullptr || program->glProgram == 0 || g_pass == nullptr) return 0;
    dotd::gfx::BindTarget();
    dotd::gfx::UseProgram(program->glProgram);
    FillUniforms(program);
    g_pass->BindMaterialTextures();  // vt+0xd0 MeshShaderPassState_BindMaterialTextures_maybe 0xeefe8 (unit 7: the fog texture)
    return program->glProgram;
}

// The PTank's shader hook (0xc4d708): InstallPSGLMeshCallbacks gives it opd_PreparePSGLAtomicMeshShaders
// (RpPTank_SetShaderBindCallBack_maybe 0x77add8), which DrawPSGLParticleQuadBatch 0x77aea8 calls with (0, the PTank atomic)
// before its glDrawArrays: the programs of the PTank's mesh pass state are bound for its quads. The shader matrix cache
// is refreshed first, as RpAtomicPSGL_Render does for the atomics. Without a device nothing is drawn (the atomics' pass
// states are not built either).
void PreparePTankShaders(void* /*meshData*/, RpAtomic* atomic) {
    if (!dotd::gfx::IsReady()) return;
    ShaderMatrixCache_BeginCamera();
    PreparePSGLAtomicMeshShaders(nullptr, atomic);
    RwDevice_SetIm3DShaderBindOverride(&BindPreparedMeshPrograms);
}
}  // namespace

namespace {
// The shader manager's atomic pipeline (+0x04), as a tag (see CShaderManagerPSGL.h).
uint8_t s_atomicPipelineObject = 0;
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
        // 0x000ff888 CShaderManagerPSGL_CreateAtomicPipeline: +0x04 the new pipeline. The RenderWare pipeline objects are
        // not modelled (every atomic renders through RpAtomicPSGL_Render, C2.4 step 3): the pipeline is a tag object and
        // cannot fail here.
        m_pAtomicPipeline = &s_atomicPipelineObject;
        m_bAtomicPipeline = 1;
        if (m_bAtomicPipeline != 0) InstallPSGLMeshCallbacks(this);
    }
}

// 0x000ff960 InstallPSGLMeshCallbacks (with +0x44): the atomic, skin and team pipelines' setup / prepare-mesh /
// draw callbacks (direct calls of PreparePSGLAtomicMeshShaders and DrawPSGLMeshPasses in RpAtomicPSGL.cpp), the
// immediate 3D pipeline's shader bind callback (PSGLImmediate_SetShaderBindCallBack_maybe 0x76b590), the Im2D one and the
// PTank's shader hook (RpPTank_SetShaderBindCallBack_maybe 0x77add8 with opd_PreparePSGLAtomicMeshShaders).
void InstallPSGLMeshCallbacks(CShaderManagerPSGL* manager) {
    if (manager->m_bShadersEnabled == 0) return;
    RwDevice_SetIm3DShaderBindCallBack(&BindImmediate3DShaders);  // PSGLImmediate_SetShaderBindCallBack_maybe 0x76b590
    RwDevice_SetIm2DShaderBindCallBack(&BindImmediate2DShaders);  // PSGLIm2D_SetShaderBindCallBack_maybe 0x735968
    RpPTankSetShaderBindCallBack(&PreparePTankShaders);            // RpPTank_SetShaderBindCallBack_maybe 0x77add8
}

// PLATFORM (perf): see CShaderManagerPSGL.h.
void ShaderManagerPSGL_PrewarmLevelPrograms(int32_t level) {
    namespace cg = dotd::gfx::cg;
    cg::SetVariantGroup(level);
    if (!dotd::gfx::IsReady()) return;
    dotd::gfx::MakeRasterTexturesAhead();  // (the web build: the level's textures too, platform/gfx/raster.h)
    if (!cg::SourcesLoaded()) {  // (as ShaderVariant_GetProgram's first call)
        const std::string path = cg::GameExecutablePath(dotd::platform::GetConfig().usrdir);
        std::string error;
        if (!cg::InitSources(path.c_str(), &error)) return;
    }
    // Each program's uniform bindings too (UniformsOf: the locations, one driver round trip per uniform).
    cg::PrewarmVariantGroup(level, [](const cg::Program* program) { UniformsOf(program); });
}

// 0x000ff778 PreparePSGLAtomicMeshShaders: ConstructMeshShaderPassState(atomic, material), the key
// (ShaderVariantKey_BuildForMesh_maybe) and the programs (BindSelectedPSGLShaderPrograms). The original ignores its first
// argument and always takes the geometry's first material (atomic +0x18 -> +0x20 -> [0]); the device meshes here pass
// their own material (C2.4 step 3), the PTank hook passes none and gets the first one, as on the PS3.
void PreparePSGLAtomicMeshShaders(RpDeviceMesh* mesh, RpAtomic* atomic) {
    RpMaterial* material = mesh != nullptr ? mesh->record.material : atomic->geometry->matList.materials[0];
    NewMeshPass(atomic, material);
    SelectProgram();
}

// 0x000ffe78 DrawPSGLMeshPasses. Pass 0 draws the mesh with the programs Prepare selected. Each later pass (more lights
// than the shader has slots) selects its programs again (BindSelectedPSGLShaderPrograms 0xfda80: the key follows the
// pass's light counters), sets the additive blend states (RW 0xc vertex alpha on, 0xa source alpha, 0xb destination one)
// and binds the diffuse texture, but DRAWS NOTHING: the vertex array setup and the glDrawRangeElements / glDrawArrays
// block (0x100188..0x10036c) is entered only with the pass index 0 (0x10000c lbz r0,5(r28) / cmpwi / beq 0x100188, and
// 0x100178 / bne 0x100018 on the path without a texture); a later pass falls through to the texture unit clears and
// ShaderPassState_AdvanceToNextPass_maybe. The three blend states are read before the loop and set back after it (pass
// count above 1), so a later pass leaves nothing but the key and the manager's flag word. BUG(original)?: the lights
// beyond the first pass's slots are never drawn. (Until 2026-11-18 the later passes were drawn here, additively.)
void DrawPSGLMeshPasses(RpDeviceMesh* mesh, uint32_t geometryFlags) {
    (void)geometryFlags;  // the attribute layout is part of the device mesh
    static const float kDefaults[16][4] = {{0, 0, 0, 1}, {1, 0, 0, 0}, {0, 0, 1, 0}, {1, 1, 1, 1}, {0, 0, 0, 1}, {0, 0, 0, 0},
                                           {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0},
                                           {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}};
    RpMaterial* material = mesh->record.material;
    while (g_pass->m_passIndex < g_pass->m_passCount) {
        const bool later = g_pass->m_passIndex != 0;
        if (later) {
            // The key of the pass and the manager's flag word, as BindSelectedPSGLShaderPrograms leaves them (its programs
            // are not built here: nothing is drawn with them).
            ShaderVariantKey_BuildForMesh(&g_key, g_pass);
            MarkProgramsBound();
        }
        const dotd::gfx::cg::Program* program = g_program;
        if (!later && program != nullptr && program->glProgram != 0) {
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
            const dotd::gfx::DrawState state = RwDevice_CurrentMeshState(&alphaFunc, &alphaRef);
            dotd::gfx::ApplyState(state);
            dotd::gfx::SetAlphaTest(program->glProgram, alphaFunc, alphaRef);
            const RpNativeMesh& m = mesh->record;
            dotd::gfx::DrawMesh(mesh->gfxMesh, m.primType, m.indexed != 0, m.firstIndex, m.lastIndex,
                                m.indexed != 0 ? m.numIndices : m.numVertices, m.firstIndex, kDefaults);
        }
        g_pass->AdvanceToNextPass();
    }
    dotd::gfx::UseProgram(0);
}

// 0x00100698 CShaderManagerPSGL_ReleaseShaderResources_maybe (vt+0x54; CKGraphic_DestroyModule, before the manager is
// destroyed): KBase11CD_vf54 0xfa068 (the program-pair cache +0x08 emptied, the pixel and vertex shader caches cleared:
// CShaderManager_ClearPixelShaderCache_maybe 0xf9d40 / ClearVertexShaderCache_maybe 0xf9a18 release and delete every
// shader object, ShaderManager_DestroyGlobalCgPrograms_maybe), then the same caches once more and cgDestroyContext
// (+0x85e0). The remake's shader objects and Cg context are the GLSL translation's (platform/gfx/cg_program: the
// compiled programs by variant, the context-free translator), and the uniform bindings above are kept per GL program:
// those are released here, which is what the PS3's caches and context hold.
void CShaderManagerPSGL::ReleaseShaderResources() {
    g_programUniforms.clear();
    g_lastUniforms = nullptr;
    g_lastUniformsProgram = 0;
    g_program = nullptr;
    dotd::gfx::cg::DestroyPrograms();
}

// C2.8 port-all P18.
// 0x000ff888 CShaderManagerPSGL_CreateAtomicPipeline (vt+0x60; the constructor makes the same call): RxPipelineCreate,
// RxPipelineLock and the PS3 all-in-one atomic node; the pipeline at +0x04 (0 when the lock fails). Here the tag object
// of the constructor (the pipeline cannot fail).
void CShaderManagerPSGL::Vf60() {
    m_pAtomicPipeline = nullptr;
    m_pAtomicPipeline = &s_atomicPipelineObject;
}

// C2.8 port-all P18.
// 0x000ff6a8 CShaderManagerPSGL_UpdateProfileCapabilities_maybe (vt+0x64): CShaderManager_InvalidateProfileCapabilities_maybe
// 0xf7e68 (+0x44 = 0), +0x40 = 4, the profile mode of the latest vertex / fragment profiles (6 each for the RSX ones, the
// smaller of the two), +0x44 when it reaches +0x3c. cgGLGetLatestProfile answers the RSX profiles (the constructor's
// note).
void CShaderManagerPSGL::Vf64() {
    m_bShadersEnabled = 0;
    m_i32ProfileMode = 4;
    m_bShadersEnabled = 0;
    const int32_t vertexProfile = 0x1b5b;    // cgGLGetLatestProfile(8)
    const int32_t fragmentProfile = 0x1b5c;  // cgGLGetLatestProfile(9)
    int32_t mode = vertexProfile == 0x1b5b ? 6 : 0;
    const uint32_t vertexMode = static_cast<uint32_t>(mode);
    const int32_t fragment = fragmentProfile == 0x1b5c ? 6 : 0;
    if (static_cast<uint32_t>(fragment) <= vertexMode) mode = fragment;
    m_i32ProfileMode = mode;
    m_bShadersEnabled = 1;
    if (mode < m_i32DefaultShaderMode) m_bShadersEnabled = 0;
}

// C2.8 port-all P18.
// 0x00100978 CShaderManagerPSGL_CreateArray (the element size 0x85e8 on the PS3)
IKBaseClass* CShaderManagerPSGL::CreateArray(uint32_t count, uint16_t* elementSize) {
    if (elementSize != nullptr) *elementSize = static_cast<uint16_t>(sizeof(CShaderManagerPSGL));
    return new CShaderManagerPSGL[count];
}

// C2.8 port-all P18.
// 0x000ffca0 CShaderManagerPSGL_DeleteArray: each element's destructor (vt+0x00), last first, then the block.
void CShaderManagerPSGL::DeleteArray(IKBaseClass* first) { delete[] static_cast<CShaderManagerPSGL*>(first); }
