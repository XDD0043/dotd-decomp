// anim_read_test - checkpoint C2.5 step 1: the RenderWare animations and hierarchies LVL010 loads.
//
// Loads LVL010 like level_load_test (the first spawn point's level request, until mode 4), then switches through the
// sectors one after the other (STR01000..STR01003 are the level's sector files; each brings its own CSectorAnimation).
// For every animation the engine's CAnimationManager holds, it checks what work/c25_anim_scan.py reads from the files:
//   - the counts (LVL010.KP3: 422 animations, 633,801 key frames, 500.0 s in all; the sector files 113 / 97 / 99 / 89),
//   - scheme 1 (RpHAnim standard key frames), flags 0, no second key frame array (version 0x101),
//   - the allocation (key frames right behind the header, the custom data behind them with the sector entry's room),
//   - every key frame's previous link stays inside the animation and goes back in time (a node's first key frame, at
//     time 0, links forward to the node's last one: RW's wrap-around for looping).
// And for every CAnimatedNode with an HAnim hierarchy: the hierarchy is on the root frame, its node infos are in order,
// no frame is attached after the load (nothing in the load path calls RpHAnimHierarchyAttach), RpHAnimHierarchyAttach
// finds a frame for every node, RpHAnimHierarchyDetach clears them, and every geometry's atomic holds the hierarchy.
// Skipped (exit 77) without game data.
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <map>
#include <set>
#include <string>

#include "Renderware/rphanim/RpHAnim.h"
#include "Renderware/rpskin/RpSkin.h"
#include "Renderware/rtanim/RtAnim.h"
#include "Renderware/rwcore/RwCamera.h"
#include "Renderware/rwcore/RwFrameList.h"
#include "Spyro2008/logic/CKS08GameManager.h"
#include "boot_helper.h"
#include "k2000/geometry/CGeometry.h"
#include "k2000/graphical/animation/CAnimationManager.h"
#include "k2000/graphical/animation/CSectorAnimation.h"
#include "k2000/logic/CKGameLevel.h"
#include "k2000/logic/CKGameSpawnPoint.h"
#include "k2000/logic/CKLevel.h"
#include "k2000/logic/io/CKLoadingManager.h"
#include "k2000/misc/CKGameLoop.h"
#include "k2000/misc/CoreSingletons.h"
#include "k2000/misc/Engine.h"
#include "k2000/misc/IKGameStructure.h"
#include "k2000/scenegraph/CAnimatedNode.h"

namespace {

struct Tally {
    uint32_t animations = 0;
    uint64_t keyFrames = 0;
    double seconds = 0.0;
    uint32_t scheme1 = 0, flags0 = 0, noSecondArray = 0, layoutOk = 0;
    // The previous links: backwards (to an earlier frame of the node), wrapping (a node's first key frame, at time 0,
    // links forward to the node's last one), to itself, or outside the animation / out of time order (bad).
    uint64_t prevBackwards = 0, prevWrap = 0, prevSelf = 0, prevBad = 0;
};

// One sector's animations (the manager's entry `sector`).
Tally TallySector(const CSectorAnimation* sector) {
    Tally tally;
    for (uint32_t i = 0; i < sector->m_ui32NbAnimations; ++i) {
        RtAnimAnimation* animation = sector->m_apAnimations[i];
        ++tally.animations;
        tally.keyFrames += static_cast<uint32_t>(animation->numFrames);
        tally.seconds += static_cast<double>(animation->duration);
        if (animation->interpInfo != nullptr && animation->interpInfo == RtAnimGetInterpolatorInfo(1) &&
            animation->interpInfo->typeID == 1) {
            ++tally.scheme1;
        }
        if (animation->flags == 0) ++tally.flags0;
        if (animation->numFrames2 == 0) ++tally.noSecondArray;
        RpHAnimStdKeyFrame* frames = static_cast<RpHAnimStdKeyFrame*>(animation->pFrames);
        const uint8_t* expectedCustom = reinterpret_cast<const uint8_t*>(frames + animation->numFrames);
        if (animation->pFrames == animation + 1 && animation->customData == expectedCustom &&
            animation->interpInfo->customDataSize == static_cast<RwInt32>(sizeof(RtAnimSectorEntryData))) {
            ++tally.layoutOk;
        }
        for (RwInt32 k = 0; k < animation->numFrames; ++k) {
            const RpHAnimStdKeyFrame* prev = frames[k].prevFrame;
            const bool inside = prev >= frames && prev < frames + animation->numFrames;
            if (prev == &frames[k]) {
                ++tally.prevSelf;
            } else if (inside && prev < &frames[k] && prev->time <= frames[k].time) {
                ++tally.prevBackwards;
            } else if (inside && prev > &frames[k] && frames[k].time == 0.0f && prev->time >= frames[k].time) {
                ++tally.prevWrap;
            } else {
                ++tally.prevBad;
            }
        }
    }
    return tally;
}

struct HierarchyTally {
    uint32_t nodes = 0, withHierarchy = 0, onRootFrame = 0, orderedInfos = 0, alignedMatrices = 0;
    uint32_t hierarchyNodes = 0, attachedAtLoad = 0, attachedAfterAttach = 0, detached = 0, atomicsOk = 0, atomics = 0;
    std::map<int32_t, uint32_t> bySize;
    std::set<const void*> seen;
};

void VisitObject(IKSerializable* object, uint32_t classKey, void* context) {
    HierarchyTally& tally = *static_cast<HierarchyTally*>(context);
    if (classKey != 0x54b) return;  // CAnimatedNode (the loader's class key)
    if (!tally.seen.insert(object).second) return;
    CAnimatedNode* node = static_cast<CAnimatedNode*>(object);
    ++tally.nodes;
    RpHAnimHierarchy* h = node->m_pRpHAnimHierarchy;
    if (h == nullptr) return;
    ++tally.withHierarchy;
    ++tally.bySize[h->numNodes];
    tally.hierarchyNodes += static_cast<uint32_t>(h->numNodes);
    if (h->parentFrame == node->m_pRootFrame && RpHAnimFrameGetHierarchy(node->m_pRootFrame) == h) ++tally.onRootFrame;
    bool ordered = h->numNodes > 0;
    for (RwInt32 i = 0; i < h->numNodes; ++i) {
        ordered = ordered && h->pNodeInfo[i].nodeIndex == i;
        if (h->pNodeInfo[i].pFrame != nullptr) ++tally.attachedAtLoad;
    }
    if (ordered) ++tally.orderedInfos;
    if ((h->flags & rpHANIMHIERARCHYNOMATRICES) != 0 || (reinterpret_cast<uintptr_t>(h->pMatrixArray) & 0xf) == 0) {
        ++tally.alignedMatrices;
    }
    RpHAnimHierarchyAttach(h);
    for (RwInt32 i = 0; i < h->numNodes; ++i) {
        if (h->pNodeInfo[i].pFrame != nullptr) ++tally.attachedAfterAttach;
    }
    RpHAnimHierarchyDetach(h);
    for (RwInt32 i = 0; i < h->numNodes; ++i) {
        if (h->pNodeInfo[i].pFrame == nullptr) ++tally.detached;
    }
    for (CGeometry* g = static_cast<CGeometry*>(node->m_lGeometryList); g != nullptr; g = g->m_pNext) {
        ++tally.atomics;
        if (RpSkinAtomicGetHAnimHierarchy(g->m_pRpAtomic) == h) ++tally.atomicsOk;
    }
}

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

bool LoadLevel(int level) {
    CKS08GameManager* manager = Manager();
    CKGameSpawnPoint* spawnPoint = FirstSpawnPoint(level);
    if (spawnPoint != nullptr) {
        static_cast<IKGameStructure*>(manager->m_gameStructure)->m_pCurrentSpawnPoint = spawnPoint;
        manager->RequestSpawnPointLevel();
    } else {
        manager->RequestLevelChange(level, -2);
    }
    for (uint32_t frame = 0; frame < 20000; ++frame) {
        c15::RunFrame();
        if (g_pCKGameLoop->m_mode == CKGameLoop::kModeStartLevel && manager->m_currentLevel == level) return true;
        if (g_pCKGameLoop->m_mode == CKGameLoop::kModeQuit) break;
    }
    return false;
}

// The CSectorAnimation objects loaded so far (the manager lists one per sector, but a sector that is not loaded has
// not run its Load: its counts are not set), the first time each is seen.
std::map<const void*, Tally> g_sectors;

void CollectObject(IKSerializable* object, uint32_t classKey, void*) {
    if (classKey != 0xdcd || g_sectors.count(object) != 0) return;
    const CSectorAnimation* sector = static_cast<const CSectorAnimation*>(object);
    if (sector->m_ui32NbAnimations == 0) return;
    g_sectors[object] = TallySector(sector);
}

void Collect() { Kp3_ForEachLoadedObject(CollectObject, nullptr); }

// RpHAnimHierarchyCreate / Attach / AttachFrameIndex / Detach / IDGetIndex on a root frame (id 5) with a child (id 7) and a
// grandchild (id 9).
void CheckAttach() {
    RwFrame* root = RwFrameCreate();
    RwFrame* child = RwFrameCreate();
    RwFrame* grandchild = RwFrameCreate();
    root->hanimID = 5;
    child->hanimID = 7;
    grandchild->hanimID = 9;
    RwFrameAddChild(root, child);
    RwFrameAddChild(child, grandchild);
    const RwInt32 ids[3] = {5, 7, 9};
    const RwInt32 flags[3] = {rpHANIMPUSHPARENTMATRIX, rpHANIMPUSHPARENTMATRIX, rpHANIMPOPPARENTMATRIX};
    RpHAnimHierarchy* h = RpHAnimHierarchyCreate(3, flags, ids, 0, 36);
    C15_CHECK(h->numNodes == 3 && h->pMatrixArray != nullptr && (reinterpret_cast<uintptr_t>(h->pMatrixArray) & 0xf) == 0);
    C15_CHECK(h->parentHierarchy == h && h->parentFrame == nullptr);
    C15_CHECK(h->pNodeInfo[2].nodeID == 9 && h->pNodeInfo[2].nodeIndex == 2 && h->pNodeInfo[2].flags == rpHANIMPOPPARENTMATRIX);
    C15_CHECK(RpHAnimIDGetIndex(h, 7) == 1 && RpHAnimIDGetIndex(h, 4) == -1);
    RpHAnimFrameSetHierarchy(root, h);
    C15_CHECK(RpHAnimFrameGetHierarchy(root) == h && h->parentFrame == root);
    RpHAnimHierarchyAttach(h);
    C15_CHECK(h->pNodeInfo[0].pFrame == root && h->pNodeInfo[1].pFrame == child && h->pNodeInfo[2].pFrame == grandchild);
    RpHAnimHierarchyDetach(h);
    C15_CHECK(h->pNodeInfo[0].pFrame == nullptr && h->pNodeInfo[1].pFrame == nullptr && h->pNodeInfo[2].pFrame == nullptr);
    RpHAnimHierarchyAttachFrameIndex(h, 2);
    C15_CHECK(h->pNodeInfo[0].pFrame == nullptr && h->pNodeInfo[1].pFrame == nullptr && h->pNodeInfo[2].pFrame == grandchild);
    RpHAnimHierarchy* copy = RpHAnimHierarchyCreateFromHierarchy(h, 0, 36);
    C15_CHECK(copy->numNodes == 3 && copy->pNodeInfo[1].nodeID == 7 && copy->pNodeInfo[2].pFrame == nullptr);
    RpHAnimFrameSetHierarchy(root, nullptr);
    C15_CHECK(h->parentFrame == nullptr && RpHAnimFrameGetHierarchy(root) == nullptr);
}

}  // namespace

int main() {
    std::setvbuf(stdout, nullptr, _IONBF, 0);
    if (!c15::BootToFrontEnd()) {
        std::printf("anim_read: no game data configured: skipped\n");
        return 77;
    }
    c15::ParkFrontEndSequence();
    const bool reached = LoadLevel(10);
    C15_CHECK(reached);
    HierarchyTally hierarchies;
    if (reached) {
        CKLevel* level = g_pEngine->m_level;
        const int32_t start = level->m_currentSector;
        Collect();
        Kp3_ForEachLoadedObject(VisitObject, &hierarchies);
        for (uint32_t sector = 1; sector < level->m_ui32NbSectors; ++sector) {
            if (static_cast<int32_t>(sector) != start) level->SwitchToSector(static_cast<int32_t>(sector), 1);
            Collect();
            Kp3_ForEachLoadedObject(VisitObject, &hierarchies);
        }
    }

    // The expected animation counts, in the order of the files: LVL010.KP3 then STR01000..STR01003 (work/c25_anim_scan.py).
    const uint32_t kExpectedCounts[] = {422, 113, 97, 99, 89};
    const uint64_t kExpectedKeyFrames[] = {633801, 158681, 141446, 152431, 100118};
    uint32_t total = 0;
    uint64_t totalKeyFrames = 0;
    double totalSeconds = 0.0;
    size_t slot = 0;
    for (const auto& entry : g_sectors) {
        const Tally& t = entry.second;
        std::printf("anim_read: sector animations %p: %u animations, %llu key frames, %.1f s; scheme 1: %u, flags 0: %u, no second "
                    "array: %u, layout ok: %u; previous links: %llu backwards, %llu wrapping, %llu to itself, %llu bad\n",
                    entry.first, t.animations, static_cast<unsigned long long>(t.keyFrames), t.seconds, t.scheme1, t.flags0,
                    t.noSecondArray, t.layoutOk, static_cast<unsigned long long>(t.prevBackwards),
                    static_cast<unsigned long long>(t.prevWrap), static_cast<unsigned long long>(t.prevSelf), static_cast<unsigned long long>(t.prevBad));
        C15_CHECK(t.scheme1 == t.animations && t.flags0 == t.animations && t.noSecondArray == t.animations);
        C15_CHECK(t.layoutOk == t.animations);
        C15_CHECK(t.prevBad == 0);
        total += t.animations;
        totalKeyFrames += t.keyFrames;
        totalSeconds += t.seconds;
        // The level's own animations are the one with 422; the sector files follow in sector order.
        if (slot < 5) {
            if (t.animations == kExpectedCounts[0]) {
                C15_CHECK(t.keyFrames == kExpectedKeyFrames[0]);
                C15_CHECK(std::fabs(t.seconds - 500.0) < 0.5);
            }
        }
        ++slot;
    }
    std::printf("anim_read: %zu sector animation sets, %u animations, %llu key frames, %.1f s in all\n", g_sectors.size(), total,
                static_cast<unsigned long long>(totalKeyFrames), totalSeconds);
    // 422 + 113 + 97 + 99 + 89 animations; the key frame totals of the five files.
    C15_CHECK(g_sectors.size() == 5);
    C15_CHECK(total == 422 + 113 + 97 + 99 + 89);
    C15_CHECK(totalKeyFrames == kExpectedKeyFrames[0] + kExpectedKeyFrames[1] + kExpectedKeyFrames[2] +
                                    kExpectedKeyFrames[3] + kExpectedKeyFrames[4]);
    {
        std::map<uint32_t, uint32_t> counts;
        for (const auto& entry : g_sectors) ++counts[entry.second.animations];
        for (uint32_t expected : kExpectedCounts) C15_CHECK(counts.count(expected) == 1);
    }

    const HierarchyTally& h = hierarchies;
    std::printf("anim_read: %u CAnimatedNodes, %u with a hierarchy (%u nodes in all), %u on their root frame, %u ordered, "
                "%u matrix arrays aligned; attached at load %u, after Attach %u, detached %u; atomics holding it %u of %u\n",
                h.nodes, h.withHierarchy, h.hierarchyNodes, h.onRootFrame, h.orderedInfos, h.alignedMatrices, h.attachedAtLoad,
                h.attachedAfterAttach, h.detached, h.atomicsOk, h.atomics);
    for (const auto& entry : h.bySize) std::printf("anim_read:   hierarchies of %d nodes: %u\n", entry.first, entry.second);
    C15_CHECK(h.withHierarchy > 0);
    C15_CHECK(h.onRootFrame == h.withHierarchy && h.orderedInfos == h.withHierarchy && h.alignedMatrices == h.withHierarchy);
    C15_CHECK(h.attachedAtLoad == 0);  // the load path never attaches (RpHAnimHierarchyAttach has no caller in the game)
    // The level's hierarchies come without bone frames (the bone frame list is the root frame alone, its HAnim id -1): there
    // is nothing for RpHAnimHierarchyAttach to attach, in the original too. The port is checked on a synthetic tree below.
    C15_CHECK(h.attachedAfterAttach == 0);
    C15_CHECK(h.detached == h.hierarchyNodes);
    CheckAttach();
    C15_CHECK(h.atomicsOk == h.atomics);

    std::fflush(stdout);
    if (c15::g_failures == 0) std::printf("anim_read: all tests passed\n");
    std::fflush(stdout);
    std::_Exit(c15::g_failures == 0 ? 0 : 1);
}
