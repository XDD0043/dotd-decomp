// shader_variants_test - checkpoint C2.4 step 2 exit: the shader variants LVL010 needs all translate, compile and link.
//
// Loads LVL010 (as geometry_read_test does), builds the ShaderVariantKey of every mesh of every loaded CGeometry
// (MeshShaderPassState over the mesh's atomic and RpMaterial, ShaderVariantKey_BuildForMesh_maybe), counts the
// distinct keys, takes each key through ShaderVariant_GetProgram (the define list of the original's
// ShaderGen_CollectExternFragments_maybe -> preprocessor -> Cg -> GLSL -> GL compile and link, hidden window) and
// prints the numbers: meshes, distinct keys, distinct vertex / pixel GLSL texts and linked programs.
//
// The scene inputs the pass state reads (lights, fog, shadow, the shader manager's flags) are still the zero state
// of steps 5-7, so the keys of the level's own materials have no lights and no fog. To cover the translator for what
// the finished renderer will ask for, every distinct key is then swept through lights (0 / 2 directional, 0 / 2 point),
// fog + shadow on / off and, for the normal-mapped materials, the shader manager's pixel-lighting mode; those
// variants must compile too.
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <set>
#include <string>
#include <vector>

#include "Renderware/rpworld/RpAtomic.h"
#include "Renderware/rpworld/RpGeometry.h"
#include "Spyro2008/logic/CKS08GameManager.h"
#include "boot_helper.h"
#include "k2000/geometry/CGeometry.h"
#include "k2000/logic/CKGameLevel.h"
#include "k2000/logic/CKGameSpawnPoint.h"
#include "k2000/logic/CKLevel.h"
#include "k2000/logic/io/CKLoadingManager.h"
#include "k2000/logic/render/CMaterial.h"
#include "k2000/misc/CKGameLoop.h"
#include "k2000/misc/CoreSingletons.h"
#include "k2000/misc/Engine.h"
#include "k2000/misc/IKGameStructure.h"
#include "k2000/render/MeshShaderPassState.h"
#include "k2000/render/ShaderVariantKey.h"
#include "platform/config.h"
#include "platform/gfx/cg_program.h"
#include "platform/gfx/device.h"
#include "platform/sdl/app.h"

namespace {
CKS08GameManager* Manager() { return static_cast<CKS08GameManager*>(g_pEngine->m_gameManager); }

CKGameSpawnPoint* FirstSpawnPoint(int level) {
    IKGameStructure* structure = static_cast<IKGameStructure*>(Manager()->m_gameStructure);
    for (uint32_t i = 0; i < structure->m_vpStages.m_ui32NbUsedElt; ++i) {
        CKGameLevel* stage = structure->m_vpStages.m_pBlock[i];
        if (stage == nullptr || stage->m_i32StageIndex != level) continue;
        if (stage->m_vpSpawnPoints.m_ui32NbUsedElt == 0) return nullptr;
        return stage->m_vpSpawnPoints.m_pBlock[0];
    }
    return nullptr;
}

std::vector<CGeometry*> g_geometries;

void CollectGeometry(IKSerializable* object, uint32_t, void*) {
    if (CGeometry* geometry = dynamic_cast<CGeometry*>(object)) g_geometries.push_back(geometry);
}

bool Known(const std::vector<ShaderVariantKey>& keys, const ShaderVariantKey& key) {
    for (const ShaderVariantKey& k : keys) {
        if (ShaderVariantKey_Equals(k, key)) return true;
    }
    return false;
}

// Compiles the key; false (and counted) on any error.
bool Build(const ShaderVariantKey& key, uint32_t* failures) {
    const dotd::gfx::cg::Program* program = ShaderVariant_GetProgram(key);
    if (program == nullptr || (dotd::gfx::IsReady() && program->glProgram == 0)) {
        ++*failures;
        const auto defines = ShaderGen_CollectExternFragments(key);
        std::string text;
        for (const auto& d : defines) text += d.name + "=" + d.value + " ";
        std::printf("FAIL shader_variants: key mode %u flags 0x%x does not build: %s\n", key.mode, key.flags, text.c_str());
        return false;
    }
    return true;
}
}  // namespace

int main() {
    std::setvbuf(stdout, nullptr, _IONBF, 0);
    dotd::platform::Config& config = dotd::platform::MutableConfig();
    dotd::platform::LoadConfig(0, nullptr, config);
    if (config.usrdir.empty()) {
        std::printf("shader_variants: no game data configured; skipped\n");
        return 77;
    }
    config.hiddenWindow = true;
    config.vsync = false;
    config.frameRate = 0;
    const bool device = dotd::platform::sdl::Init(config) && dotd::gfx::Init(1280, 720);
    if (!device) std::printf("shader_variants: no OpenGL 3.3 device: the variants are translated but not compiled\n");
    if (!c15::BootToFrontEnd()) {
        std::printf("shader_variants: boot failed\n");
        return 1;
    }
    c15::ParkFrontEndSequence();

    constexpr int kLevel = 10;
    CKS08GameManager* manager = Manager();
    CKGameSpawnPoint* spawnPoint = FirstSpawnPoint(kLevel);
    C15_CHECK(spawnPoint != nullptr);
    static_cast<IKGameStructure*>(manager->m_gameStructure)->m_pCurrentSpawnPoint = spawnPoint;
    manager->RequestSpawnPointLevel();
    bool reached = false;
    for (uint32_t frame = 0; frame < 20000 && !reached; ++frame) {
        c15::RunFrame();
        if (g_pCKGameLoop->m_mode == CKGameLoop::kModeStartLevel && manager->m_currentLevel == kLevel) reached = true;
        if (g_pCKGameLoop->m_mode == CKGameLoop::kModeQuit) break;
    }
    C15_CHECK(reached);

    Kp3_ForEachLoadedObject(&CollectGeometry, nullptr);
    uint32_t meshes = 0, withKMaterial = 0, skinned = 0;
    uint32_t modeCount[16] = {};
    std::vector<ShaderVariantKey> keys;
    for (CGeometry* geometry : g_geometries) {
        RpAtomic* atomic = geometry->m_pRpAtomic;
        if (atomic == nullptr || atomic->geometry == nullptr || atomic->geometry->mesh == nullptr) continue;
        for (const RpMesh& mesh : atomic->geometry->mesh->meshes) {
            if (mesh.material == nullptr) continue;
            MeshShaderPassState pass(atomic, mesh.material);
            ShaderVariantKey key;
            ShaderVariantKey_Init(&key);
            ShaderVariantKey_BuildForMesh(&key, &pass);
            ++meshes;
            if (mesh.material->kMaterial != nullptr) ++withKMaterial;
            if (key.weights != 0) ++skinned;
            ++modeCount[key.mode & 15];
            if (!Known(keys, key)) keys.push_back(key);
        }
    }
    std::printf("shader_variants: LVL010 + start sector: %zu geometries with an atomic, %u meshes (%u with a K material, %u skinned)\n",
                g_geometries.size(), meshes, withKMaterial, skinned);
    std::printf("shader_variants: meshes by shader mode:");
    for (int m = 0; m < 15; ++m) {
        if (modeCount[m] != 0) std::printf(" %d:%u", m, modeCount[m]);
    }
    std::printf("\n");
    C15_CHECK(meshes != 0);

    uint32_t failures = 0;
    // C2.5 step 5: the skinned meshes' keys (externWeightNb 1 or 2: the palette u_f34BoneMatrix, BLENDINDICES and, for
    // 2, BLENDWEIGHT) by weight count, and their failures.
    uint32_t skinnedKeys[3] = {}, skinnedFailures = 0;
    for (const ShaderVariantKey& key : keys) {
        const uint32_t before = failures;
        Build(key, &failures);
        if (key.weights != 0) {
            ++skinnedKeys[key.weights < 3 ? key.weights : 2];
            skinnedFailures += failures - before;
        }
    }
    std::printf("shader_variants: skinned keys: %u with 1 weight, %u with blend weights; %u failures\n", skinnedKeys[1], skinnedKeys[2],
                skinnedFailures);
    C15_CHECK(skinned != 0 && skinnedKeys[1] + skinnedKeys[2] != 0 && skinnedFailures == 0);
    dotd::gfx::cg::Statistics stats = dotd::gfx::cg::GetStatistics();
    // The vertex / pixel classes by the original's own comparison (first fit).
    std::vector<ShaderVariantKey> vertexClasses, pixelClasses;
    for (const ShaderVariantKey& key : keys) {
        bool found = false;
        for (const ShaderVariantKey& c : vertexClasses) found = found || ShaderVariantKey_MatchesVertexShader(c, key);
        if (!found) vertexClasses.push_back(key);
        found = false;
        for (const ShaderVariantKey& c : pixelClasses) found = found || ShaderVariantKey_MatchesPixelShader(c, key);
        if (!found) pixelClasses.push_back(key);
    }
    std::printf("shader_variants: LVL010 needs %zu distinct keys = %u distinct vertex GLSL programs and %u pixel programs, %u linked pairs "
                "(by the original's key comparison: %zu vertex and %zu pixel programs); %u failures\n",
                keys.size(), stats.vertexShaders, stats.pixelShaders, stats.linkedPrograms, vertexClasses.size(), pixelClasses.size(), failures);

    // The sweep over the scene state the renderer will provide.
    const uint32_t before = stats.variants;
    uint32_t swept = 0;
    for (uint8_t pixelLightning = 0; pixelLightning < 2; ++pixelLightning) {
        SceneInputs().pixelLightning = pixelLightning;
        for (const ShaderVariantKey& base : keys) {
            // The shader's pixel lighting needs a normal map (without internNormalMap it reads f3NormalLS, which only
            // the effects that output the normal declare): the Cg compiler of the original rejects that too, so the
            // pixel-lighting mode of the shader manager can only apply to the normal-mapped materials (mode 12).
            if (pixelLightning != 0 && !(base.mode == 12 && (base.flags & kShaderKeyAuxLayerTexture) != 0)) continue;
            for (int combo = 0; combo < 8; ++combo) {
                ShaderVariantKey key = base;
                key.dirLights = (combo & 1) != 0 ? 2 : 0;
                key.pointLights = (combo & 2) != 0 ? 2 : 0;
                key.fogType = (combo & 4) != 0 ? 1 : 0;
                if ((combo & 4) != 0) key.flags |= kShaderKeyShadow;
                if (combo == 7) key.specialLights = 1;
                ++swept;
                Build(key, &failures);
            }
        }
    }
    SceneInputs().pixelLightning = 0;
    stats = dotd::gfx::cg::GetStatistics();
    std::printf("shader_variants: sweep: %u more variants (%u new define lists), %u vertex / %u pixel GLSL programs / %u linked pairs in total, "
                "%u failures\n", swept, stats.variants - before, stats.vertexShaders, stats.pixelShaders, stats.linkedPrograms, failures);
    C15_CHECK(failures == 0);

    std::fflush(stdout);
    if (c15::g_failures == 0) std::printf("shader_variants: all tests passed\n");
    std::fflush(stdout);
    std::_Exit(c15::g_failures == 0 ? 0 : 1);
}
