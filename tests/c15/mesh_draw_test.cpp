// mesh_draw_test - checkpoint C2.4 step 3 exit: LVL010's static geometries drawn through the PSGL atomic pipeline and
// the uber-shader.
//
// Loads LVL010 (as shader_variants_test does) and draws, with a fixed camera into the 1280x720 target, the biggest PS3
// native geometry and the biggest generic geometry that has no skin; each goes to a PNG (mesh_draw_<kind>.png in the
// working directory, or in DOTD_C24_OUT) and the test checks that a recognisable amount of the image was drawn and that
// the GL context reports no error. Looking at the PNGs is the exit check (shape and texture); there is no RPCS3
// reference yet.
#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <vector>

#include "Renderware/rpworld/RpAtomic.h"
#include "Renderware/rpworld/RpAtomicPSGL.h"
#include "Renderware/rpworld/RpGeometry.h"
#include "Renderware/rwcore/RwCamera.h"
#include "Renderware/rwcore/RwDevice.h"
#include "Renderware/rwcore/RwIm3D.h"
#include "Renderware/rwcore/RwTexture.h"
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
#include "k2000/graphical/render/CLightManager.h"
#include "k2000/render/MeshShaderPassState.h"
#include "k2000/render/ShaderVariantKey.h"
#include "platform/gfx/cg_program.h"
#include "platform/config.h"
#include "platform/gfx/device.h"
#include "platform/gfx/gl.h"
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

std::string OutPath(const char* name) {
    const char* dir = std::getenv("DOTD_C24_OUT");
    return std::string(dir != nullptr ? dir : ".") + "/" + name;
}

// The camera looks at the atomic's bounding sphere from `distance` radii away, a little above and to the side.
void PlaceCamera(RwCamera* camera, const float center[3], float radius) {
    const float eye[3] = {center[0] + radius * 1.2f, center[1] + radius * 0.8f, center[2] - radius * 2.2f};
    float at[3] = {center[0] - eye[0], center[1] - eye[1], center[2] - eye[2]};
    const float atLen = std::sqrt(at[0] * at[0] + at[1] * at[1] + at[2] * at[2]);
    for (float& v : at) v /= atLen;
    const float up0[3] = {0, 1, 0};
    // RW is left-handed: right = up x at (pointing to the left of the screen, as the camera's x axis does)
    float right[3] = {up0[1] * at[2] - up0[2] * at[1], up0[2] * at[0] - up0[0] * at[2], up0[0] * at[1] - up0[1] * at[0]};
    const float rl = std::sqrt(right[0] * right[0] + right[1] * right[1] + right[2] * right[2]);
    for (float& v : right) v /= rl;
    const float up[3] = {at[1] * right[2] - at[2] * right[1], at[2] * right[0] - at[0] * right[2], at[0] * right[1] - at[1] * right[0]};
    RwFrame* frame = RwCameraGetFrame(camera);
    RwMatrix m;
    std::memset(&m, 0, sizeof m);
    m.right = {right[0], right[1], right[2]};
    m.up = {up[0], up[1], up[2]};
    m.at = {at[0], at[1], at[2]};
    m.pos = {eye[0], eye[1], eye[2]};
    m.flags = rwMATRIXTYPEORTHONORMAL;
    RwFrameTransform(frame, &m, rwCOMBINEREPLACE);
    camera->nearPlane = radius * 0.05f;
    camera->farPlane = radius * 12.0f;
    RwDevice_SetCamera(camera);
}

void SetWorldStates() {
    RwRenderStateSet(rwRENDERSTATEZTESTENABLE, reinterpret_cast<void*>(1));
    RwRenderStateSet(rwRENDERSTATEZWRITEENABLE, reinterpret_cast<void*>(1));
    RwRenderStateSet(rwRENDERSTATECULLMODE, reinterpret_cast<void*>(2));
    RwRenderStateSet(rwRENDERSTATEVERTEXALPHAENABLE, reinterpret_cast<void*>(0));
    RwRenderStateSet(rwRENDERSTATEALPHATESTFUNCTION, reinterpret_cast<void*>(8));
}

// The native geometry's vertices and triangle strip as an in-memory RenderWare geometry (positions, normals, prelit
// colours, one texture coordinate set, a bin mesh of one strip) on the same frame and material.
RpAtomic* MakeGenericCopy(RpAtomic* source) {
    const RpGeometry* g = source->geometry;
    if (g->repEntry == nullptr || g->repEntry->meshes.empty()) return nullptr;
    const RpNativeGeometry& native = *g->repEntry;
    const RpNativeMesh& m = native.meshes[0];
    auto f32 = [&](const uint8_t* p) {
        uint32_t w = (static_cast<uint32_t>(p[0]) << 24) | (static_cast<uint32_t>(p[1]) << 16) | (static_cast<uint32_t>(p[2]) << 8) | p[3];
        float v;
        std::memcpy(&v, &w, 4);
        return v;
    };
    const RwUInt32 format = rpGEOMETRYPOSITIONS | rpGEOMETRYTEXTURED | rpGEOMETRYPRELIT | rpGEOMETRYNORMALS | rpGEOMETRYLIGHT |
                            rpGEOMETRYMODULATEMATERIALCOLOR | (1u << 16);
    RpGeometry* copy = RpGeometryCreate(static_cast<RwInt32>(m.numVertices), 0, format);
    for (uint32_t v = 0; v < m.numVertices; ++v) {
        const uint8_t* in = native.vertexData.data() + static_cast<size_t>(v) * m.stride;
        copy->morphTarget[0].verts[v] = {f32(in), f32(in + 4), f32(in + 8)};
        copy->morphTarget[0].normals[v] = {f32(in + m.normalOffset), f32(in + m.normalOffset + 4), f32(in + m.normalOffset + 8)};
        copy->preLitLum[v] = {in[m.colorOffset], in[m.colorOffset + 1], in[m.colorOffset + 2], in[m.colorOffset + 3]};
        copy->texCoords[0][v] = {f32(in + m.uvOffset[0]), f32(in + m.uvOffset[0] + 4)};
    }
    RpMaterial* material = g->matList.materials[0];
    ++material->refCount;
    _rpMaterialListAppendMaterial(&copy->matList, material);
    copy->mesh = new RpMeshHeader();
    copy->mesh->flags = 1;  // rpMESHHEADERTRISTRIP
    copy->mesh->numMeshes = 1;
    copy->mesh->indexStorage.resize(m.numIndices);
    for (uint32_t i = 0; i < m.numIndices; ++i) {
        const uint8_t* p = native.indexData.data() + static_cast<size_t>(i) * 4;
        copy->mesh->indexStorage[i] = (static_cast<uint32_t>(p[0]) << 24) | (static_cast<uint32_t>(p[1]) << 16) | (static_cast<uint32_t>(p[2]) << 8) | p[3];
    }
    RpMesh mesh = {copy->mesh->indexStorage.data(), m.numIndices, material};
    copy->mesh->meshes.push_back(mesh);
    RpAtomic* atomic = RpAtomicCreate();
    RpAtomicSetGeometry(atomic, copy, 1);
    RpAtomicSetFrame(atomic, source->frame);
    return atomic;
}

// Draws one atomic and counts the pixels that differ from the clear colour.
bool DrawOne(const char* kind, RpAtomic* atomic, RwCamera* camera) {
    const RpGeometry* g = atomic->geometry;
    float sphere[4] = {atomic->boundingSphere[0], atomic->boundingSphere[1], atomic->boundingSphere[2], atomic->boundingSphere[3]};
    if (sphere[3] <= 0.0f) {  // streamed atomics carry no sphere of their own: the bounds of the vertices
        const RwV3d* v = g->morphTarget[0].verts;
        RwV3d lo = v[0], hi = v[0];
        for (RwInt32 i = 1; i < g->numVertices; ++i) {
            lo = {std::fmin(lo.x, v[i].x), std::fmin(lo.y, v[i].y), std::fmin(lo.z, v[i].z)};
            hi = {std::fmax(hi.x, v[i].x), std::fmax(hi.y, v[i].y), std::fmax(hi.z, v[i].z)};
        }
        sphere[0] = (lo.x + hi.x) * 0.5f; sphere[1] = (lo.y + hi.y) * 0.5f; sphere[2] = (lo.z + hi.z) * 0.5f;
        sphere[3] = 0.5f * std::sqrt((hi.x - lo.x) * (hi.x - lo.x) + (hi.y - lo.y) * (hi.y - lo.y) + (hi.z - lo.z) * (hi.z - lo.z));
    }
    float center[3] = {sphere[0], sphere[1], sphere[2]};
    if (atomic->frame != nullptr) {
        const RwMatrix* ltm = RwFrameGetLTM(atomic->frame);
        center[0] = sphere[0] * ltm->right.x + sphere[1] * ltm->up.x + sphere[2] * ltm->at.x + ltm->pos.x;
        center[1] = sphere[0] * ltm->right.y + sphere[1] * ltm->up.y + sphere[2] * ltm->at.y + ltm->pos.y;
        center[2] = sphere[0] * ltm->right.z + sphere[1] * ltm->up.z + sphere[2] * ltm->at.z + ltm->pos.z;
    }
    std::printf("mesh_draw: %s: %d triangles, %d vertices, flags 0x%x, %d materials, sphere (%.1f %.1f %.1f) r %.1f, frame %s\n", kind,
                g->numTriangles, g->numVertices, g->flags, g->matList.numMaterials, center[0], center[1], center[2], sphere[3],
                atomic->frame != nullptr ? "yes" : "no");
    if (g->matList.numMaterials > 0) {
        const RpMaterial* material = g->matList.materials[0];
        std::printf("mesh_draw: %s: material 0: texture %s raster %s mode %d colour %02x%02x%02x%02x\n", kind,
                    material->texture != nullptr ? material->texture->name : "none",
                    material->texture != nullptr && material->texture->raster != nullptr ? "yes" : "no",
                    material->kMaterial != nullptr ? static_cast<int>((material->kMaterial->m_baProperties >> 3) & 0xf) : -1,
                    material->color.red, material->color.green, material->color.blue, material->color.alpha);
    }
    if (g->matList.numMaterials > 0 && g->matList.materials[0]->texture != nullptr) {
        RwRaster* raster = g->matList.materials[0]->texture->raster;
        std::printf("mesh_draw: %s: raster %dx%d levels %d format %04x device texture %u\n", kind, raster->width, raster->height,
                    RwRasterGetNumLevels(raster), raster->psgl.internalFormat, RwDevice_GetRasterTexture(raster));
    }
    if (g->matList.numMaterials > 0 && g->matList.materials[0]->kMaterial != nullptr) {
        RpMaterial* rpm = g->matList.materials[0];
        MeshShaderPassState pass(atomic, rpm);
        if (((rpm->kMaterial->m_baProperties >> 3) & 15) == 12) {
        float fx[4] = {-1, -1, -1, -1}, np[4] = {-1, -1, -1, -1};
        {
            ShaderVariantKey key;
            ShaderVariantKey_Init(&key);
            ShaderVariantKey_BuildForMesh(&key, &pass);
            const dotd::gfx::cg::Program* program = ShaderVariant_GetProgram(key);
            if (program != nullptr) {
                for (const auto& sampler : program->pixel.samplers) std::printf("mesh_draw: %s: sampler %s unit %d\n", kind, sampler.name.c_str(), sampler.unit);
            }
        }
        pass.FillEnvMapCoefficients(fx);
        pass.FillNormalParam(np);
        CMaterial* km = rpm->kMaterial;
        std::printf("mesh_draw: %s: matfx %.3f %.3f %.3f %.3f normalparam %.2f %.2f %.2f %.2f props 0x%x passes %d aux %p envtex %p aux88 %p aux8c %p ambient %.2f\n", kind, fx[0], fx[1], fx[2], fx[3],
                    np[0], np[1], np[2], np[3], km->m_baProperties, pass.m_passCount, static_cast<void*>(km->m_pAuxLayer),
                    static_cast<void*>(km->GetEnvMapTexture()), static_cast<void*>(km->m_pAuxTexture88), static_cast<void*>(km->m_pAuxTexture8C),
                    g_pLightManager->GetAmbientColor()[0]);
        auto name = [](RwTexture* t) { return t != nullptr ? t->name : "none"; };
        std::printf("mesh_draw: %s: textures: aux layer %s (raster %s) env %s aux8c %s\n", kind, name(km->m_pAuxLayer != nullptr ? km->m_pAuxLayer->m_pTexture : nullptr),
                    km->m_pAuxLayer != nullptr && km->m_pAuxLayer->m_pTexture != nullptr && km->m_pAuxLayer->m_pTexture->raster != nullptr ? "yes" : "no",
                    name(km->GetEnvMapTexture()), name(km->m_pAuxTexture8C));
        if (g->repEntry != nullptr) {
            const RpNativeMesh& nm = g->repEntry->meshes[0];
            std::printf("mesh_draw: %s: native mesh: prim %u format 0x%x stride %u verts %u idx %u first %u last %u normal@%u color@%u uv@%u tangent@%u w28 %u\n", kind, nm.primType,
                        nm.format, nm.stride, nm.numVertices, nm.numIndices, nm.firstIndex, nm.lastIndex, nm.normalOffset, nm.colorOffset, nm.uvOffset[0],
                        nm.tangentOffset, nm.word28);
        }
        }
    }
    PlaceCamera(camera, center, sphere[3] > 0.01f ? sphere[3] : 1.0f);
    dotd::gfx::BeginFrame();
    dotd::gfx::ClearTarget(true, true, 0.1f, 0.2f, 0.4f, 1.0f);
    SetWorldStates();
    C15_CHECK(RpAtomicPSGL_Render(atomic));
    std::vector<uint8_t> pixels(1280 * 720 * 4);
    C15_CHECK(dotd::gfx::ReadTarget(pixels.data()));
    size_t drawn = 0;
    double sum[3] = {0, 0, 0};
    for (size_t i = 0; i < pixels.size(); i += 4) {
        if (std::abs(pixels[i] - 26) > 3 || std::abs(pixels[i + 1] - 51) > 3 || std::abs(pixels[i + 2] - 102) > 3) {
            ++drawn;
            for (int c = 0; c < 3; ++c) sum[c] += pixels[i + c];
        }
    }
    if (drawn != 0) std::printf("mesh_draw: %s: mean colour of the drawn pixels %.0f %.0f %.0f\n", kind, sum[0] / drawn, sum[1] / drawn, sum[2] / drawn);
    std::printf("mesh_draw: %s: %zu of %d pixels drawn\n", kind, drawn, 1280 * 720);
    const std::string path = OutPath((std::string("mesh_draw_") + kind + ".png").c_str());
    dotd::gfx::SaveScreenshot(path.c_str());
    const GLenum error = dotd::gfx::gl::glGetError();
    if (error != 0) std::printf("mesh_draw: %s: GL error 0x%x\n", kind, error);
    C15_CHECK(error == 0);
    return drawn > 2000;
}
}  // namespace

int main() {
    std::setvbuf(stdout, nullptr, _IONBF, 0);
    dotd::platform::Config& config = dotd::platform::MutableConfig();
    dotd::platform::LoadConfig(0, nullptr, config);
    if (config.usrdir.empty()) {
        std::printf("mesh_draw: no game data configured; skipped\n");
        return 77;
    }
    config.hiddenWindow = true;
    config.vsync = false;
    config.frameRate = 0;
    if (!(dotd::platform::sdl::Init(config) && dotd::gfx::Init(1280, 720))) {
        std::printf("mesh_draw: no OpenGL 3.3 device; skipped\n");
        return 77;
    }
    if (!c15::BootToFrontEnd()) {
        std::printf("mesh_draw: boot failed\n");
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
    CGeometry* bestNative = nullptr;
    for (CGeometry* geometry : g_geometries) {
        RpAtomic* atomic = geometry->m_pRpAtomic;
        if (atomic == nullptr || atomic->geometry == nullptr || atomic->geometry->mesh == nullptr) continue;
        RpGeometry* g = atomic->geometry;
        if (g->skin != nullptr || g->numTriangles <= 0) continue;
        if ((g->flags & rpGEOMETRYNATIVE) != 0) {
            if (g->repEntry != nullptr && (bestNative == nullptr || g->numTriangles > bestNative->m_pRpAtomic->geometry->numTriangles)) bestNative = geometry;
        }
    }
    {
        int shown = 0, generic = 0;
        for (CGeometry* geometry : g_geometries) {
            RpAtomic* atomic = geometry->m_pRpAtomic;
            if (atomic == nullptr || atomic->geometry == nullptr || atomic->geometry->mesh == nullptr) continue;
            RpGeometry* g = atomic->geometry;
            if ((g->flags & rpGEOMETRYNATIVE) != 0 || g->numTriangles <= 0) continue;
            ++generic;
            if (shown < 12 && g->matList.numMaterials > 0) {
                ++shown;
                std::printf("mesh_draw: generic candidate: %d tris flags 0x%x skin %u texture %s mode %d\n", g->numTriangles, g->flags, g->skin != nullptr ? 1u : 0u,
                            g->matList.materials[0]->texture != nullptr ? g->matList.materials[0]->texture->name : "none",
                            g->matList.materials[0]->kMaterial != nullptr ? static_cast<int>((g->matList.materials[0]->kMaterial->m_baProperties >> 3) & 15) : -1);
            }
        }
        std::printf("mesh_draw: %d generic geometries with triangles\n", generic);
    }
    CGeometry* modeBest[16] = {};
    for (int wanted : {0, 2, 5, 14}) {  // the biggest geometries of each shader mode
        std::vector<CGeometry*> list;
        for (CGeometry* geometry : g_geometries) {
            RpAtomic* atomic = geometry->m_pRpAtomic;
            if (atomic == nullptr || atomic->geometry == nullptr || atomic->geometry->repEntry == nullptr || atomic->geometry->skin != nullptr) continue;
            const RpMaterial* material = atomic->geometry->matList.numMaterials > 0 ? atomic->geometry->matList.materials[0] : nullptr;
            if (material == nullptr || material->kMaterial == nullptr || static_cast<int>((material->kMaterial->m_baProperties >> 3) & 15) != wanted) continue;
            list.push_back(geometry);
        }
        std::sort(list.begin(), list.end(), [](CGeometry* a, CGeometry* b) { return a->m_pRpAtomic->geometry->numTriangles > b->m_pRpAtomic->geometry->numTriangles; });
        if (!list.empty()) modeBest[wanted] = list[0];
        for (size_t i = 0; i < list.size() && i < 4; ++i) {
            const RpGeometry* g = list[i]->m_pRpAtomic->geometry;
            std::printf("mesh_draw: mode %d candidate %zu/%zu: %d tris texture %s colour %02x%02x%02x%02x\n", wanted, i, list.size(), g->numTriangles,
                        g->matList.materials[0]->texture != nullptr ? g->matList.materials[0]->texture->name : "none", g->matList.materials[0]->color.red,
                        g->matList.materials[0]->color.green, g->matList.materials[0]->color.blue, g->matList.materials[0]->color.alpha);
        }
    }
    C15_CHECK(bestNative != nullptr);

    RwCamera* camera = RwCameraCreate();
    RwCameraSetFrame(camera, RwFrameCreate());
    const RwV2d window = {0.8f, 0.45f};  // a 16:9 view of about 77 degrees across
    RwCameraSetViewWindow(camera, &window);
    RwCameraSetProjection(camera, rwPERSPECTIVE);
    for (int wanted : {0, 2, 5, 14}) {
        if (modeBest[wanted] == nullptr) continue;
        const std::string name = "mode" + std::to_string(wanted);
        DrawOne(name.c_str(), modeBest[wanted]->m_pRpAtomic, camera);
    }
    if (bestNative != nullptr) {
        C15_CHECK(DrawOne("native", bestNative->m_pRpAtomic, camera));
        // The level has no static geometry in RenderWare's generic format (its 110 generic geometries are the weapon wipe
        // effects, filled at run time), so the generic path is exercised with the same geometry rebuilt as generic data.
        RpAtomic* generic = MakeGenericCopy(bestNative->m_pRpAtomic);
        C15_CHECK(generic != nullptr);
        if (generic != nullptr) C15_CHECK(DrawOne("generic", generic, camera));
    }

    std::fflush(stdout);
    if (c15::g_failures == 0) std::printf("mesh_draw: all tests passed\n");
    std::fflush(stdout);
    std::_Exit(c15::g_failures == 0 ? 0 : 1);
}
