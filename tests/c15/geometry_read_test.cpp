// geometry_read_test - checkpoint C2.4 step 1: the world geometry is read for real.
//
// Loads LVL010 as level_load_test does (request the level as the menus do, step frames until mode 4) and counts
// what RpGeometryStreamRead made of LVL010.KP3's atomics (the loader notes the geometry read log per file).
// The numbers are those of `python work/c24_geometry_scan.py LVL010`, which counts the same chunks in the file:
//   1,103 atomics with 1,103 geometries; 620 empty (format flags 0: particle holders), 111 in RenderWare's
//   generic format, 372 with the native flag; 204,107 triangles and 134,862 vertices (header totals).
// Native-data chunks (0x510): 372 with 7,420,100 bytes, one per native-flagged geometry. The scan used to print
// 371 and 7,419,096: for the geometry at file offset 0x7930028 (format 0x101025f) its find() of the bytes
// 10 05 00 00 stopped at the geometry chunk's own length field (the chunk is 0x510 = 1,296 bytes long), so that
// chunk was not counted; the scan now starts behind the chunk header.
//
// Beyond the counts: every geometry has its bin mesh (0x50e), every native geometry one mesh record, and the 19
// skinned atomics carry the skin chunk. The level load itself must still pass (level_load_test).
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <vector>

#include "Renderware/rpworld/RpGeometry.h"
#include "Spyro2008/logic/CKS08GameManager.h"
#include "boot_helper.h"
#include "k2000/logic/CKGameLevel.h"
#include "k2000/logic/CKGameSpawnPoint.h"
#include "k2000/logic/CKLevel.h"
#include "k2000/logic/io/CKLoadingManager.h"
#include "k2000/misc/CKGameLoop.h"
#include "k2000/misc/CoreSingletons.h"
#include "k2000/misc/Engine.h"
#include "k2000/misc/IKGameStructure.h"

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

uint32_t BigEndian32(const uint8_t* b) {
    return (static_cast<uint32_t>(b[0]) << 24) | (static_cast<uint32_t>(b[1]) << 16) | (static_cast<uint32_t>(b[2]) << 8) |
           static_cast<uint32_t>(b[3]);
}
}  // namespace

int main() {
    if (!c15::BootToFrontEnd()) {
        std::printf("geometry_read: no game data configured: skipped\n");
        return 77;
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

    uint32_t reportCount = 0;
    const KLoadReport* reports = Kp3_LoadReports(&reportCount);
    const std::vector<RpGeometryReadRecord>& log = RpGeometryReadLog();
    uint32_t geometries = 0, empty = 0, generic = 0, native = 0, nativeChunks = 0;
    uint64_t triangles = 0, vertices = 0, nativeBytes = 0;
    uint32_t badIndices = 0, badVertices = 0, badRanges = 0;
    uint32_t noBinMesh = 0, multiMesh = 0, noNativeFlagged = 0, textured = 0, materials = 0, skinned = 0;
    for (uint32_t r = 0; r < reportCount; ++r) {
        const KLoadReport& report = reports[r];
        std::printf("geometry_read: %-28s %5u geometries\n", report.file, report.geometriesEnd - report.geometriesBegin);
        if (std::strstr(report.file, "LVL010.KP3") == nullptr) continue;
        for (uint32_t i = report.geometriesBegin; i < report.geometriesEnd; ++i) {
            const RpGeometryReadRecord& g = log[i];
            ++geometries;
            const uint32_t format = g.flags & 0xff;
            if (format == 0) {
                ++empty;
            } else if ((g.flags & rpGEOMETRYNATIVE) != 0) {
                ++native;
                if (g.nativeMeshes != 0) {
                    ++nativeChunks;
                } else {
                    ++noNativeFlagged;
                    std::printf("geometry_read: native-flagged geometry without native data: flags 0x%x, %d triangles, "
                                "%d vertices, %d materials, %u bin meshes\n", g.flags, g.numTriangles, g.numVertices,
                                g.numMaterials, g.numMeshes);
                }
            } else {
                ++generic;
            }
            if (g.hasBinMesh == 0) ++noBinMesh;
            if (g.nativeMeshes > 1) ++multiMesh;
            if (g.skinBytes != 0) ++skinned;
            triangles += static_cast<uint32_t>(g.numTriangles);
            vertices += static_cast<uint32_t>(g.numVertices);
            nativeBytes += g.nativeBytes;
            badIndices += g.nativeBadIndices;
            badVertices += g.nativeBadVertices;
            badRanges += g.nativeBadRanges;
            textured += static_cast<uint32_t>(g.numTexturedMaterials);
            materials += static_cast<uint32_t>(g.numMaterials);
        }
    }
    std::printf("geometry_read: LVL010.KP3: %u geometries: %u empty, %u generic, %u native; %llu triangles, %llu vertices; "
                "%u native-data chunks, %llu bytes; %u without a bin mesh, %u native with several meshes, %u native-flagged "
                "without native data, %u skin chunks; %u of %u materials have their texture\n",
                geometries, empty, generic, native, static_cast<unsigned long long>(triangles),
                static_cast<unsigned long long>(vertices), nativeChunks, static_cast<unsigned long long>(nativeBytes),
                noBinMesh, multiMesh, noNativeFlagged, skinned, textured, materials);
    std::printf("geometry_read: native buffers as big-endian data: %u bad indices, %u bad vertex positions, %u ranges off\n",
                badIndices, badVertices, badRanges);
    C15_CHECK(badIndices == 0 && badVertices == 0 && badRanges == 0);
    C15_CHECK(geometries == 1103);
    C15_CHECK(empty == 620);
    C15_CHECK(generic == 111);
    C15_CHECK(native == 372);
    C15_CHECK(triangles == 204107);
    C15_CHECK(vertices == 134862);
    C15_CHECK(nativeChunks == 372);
    C15_CHECK(nativeBytes == 7420100);
    C15_CHECK(noNativeFlagged == 0);
    C15_CHECK(noBinMesh == 0);
    C15_CHECK(multiMesh == 0);
    C15_CHECK(skinned == 19);

    std::fflush(stdout);
    if (c15::g_failures == 0) std::printf("geometry_read: all tests passed\n");
    std::fflush(stdout);
    std::_Exit(c15::g_failures == 0 ? 0 : 1);
}
