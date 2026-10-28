// anim_interp_test - checkpoint C2.5 step 2: RtAnim's interpolator and the RpHAnim standard key frame scheme.
//
// Loads LVL010 like anim_read_test, takes a 60-node animation (the dragons) and a 3-node one (props) of the level's
// CSectorAnimation, sets each on a level hierarchy of the same node count (its interpolator, RpHAnimHierarchyCreate'd
// by the stream reader) and plays it at 1/60 s steps for 600 frames (RtAnimInterpolatorAddAnimTime, then
// RpHAnimHierarchyUpdateMatrices). Checks:
//   - the time wraps at the duration (it stays in [0, duration], and a frame that passes the duration lands at
//     time + dt - duration);
//   - every node's key frame walk (the index of its first key frame) never goes back except at a loop;
//   - the matrices stay orthonormal as far as the original's math keeps them: the key frames' quaternions are unit
//     (1e-5), a slerped node stays unit (1e-4) and its local matrix has |det - 1| < 1e-4; a node in RW's lerp branch
//     (dot >= 0.999, not renormalised: the plan's |det - 1| < 1e-4 does not hold there, in the original either) keeps
//     |q|^2 >= 0.9995 and |det - 1| <= 4 (1 - |q|^2) + 1e-5 (the matrix is s^2 R + (1 - s^2) I); every hierarchy
//     matrix's det is its local det times its parent's (1e-4: the parent chain of the node flags);
//   - at t = 0 the interpolated frames are the first key frames (their matrices within 1e-5).
// The comparison with the original's poses is step 4 (bones_compare.py). Skipped (exit 77) without game data.
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <map>
#include <set>
#include <vector>

#include "Renderware/rphanim/RpHAnim.h"
#include "Renderware/rtanim/RtAnim.h"
#include "Renderware/rwcore/RwMatrix.h"
#include "Spyro2008/logic/CKS08GameManager.h"
#include "boot_helper.h"
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

CKS08GameManager* Manager() { return static_cast<CKS08GameManager*>(g_pEngine->m_gameManager); }

bool LoadLevel(int level) {
    CKS08GameManager* manager = Manager();
    IKGameStructure* structure = static_cast<IKGameStructure*>(manager->m_gameStructure);
    CKGameSpawnPoint* spawnPoint = nullptr;
    for (uint32_t i = 0; i < structure->m_vpStages.m_ui32NbUsedElt; ++i) {
        CKGameLevel* stage = structure->m_vpStages.m_pBlock[i];
        if (stage != nullptr && stage->m_i32StageIndex == level && stage->m_vpSpawnPoints.m_ui32NbUsedElt != 0) {
            spawnPoint = stage->m_vpSpawnPoints.m_pBlock[0];
        }
    }
    if (spawnPoint == nullptr) return false;
    structure->m_pCurrentSpawnPoint = spawnPoint;
    manager->RequestSpawnPointLevel();
    for (uint32_t frame = 0; frame < 20000; ++frame) {
        c15::RunFrame();
        if (g_pCKGameLoop->m_mode == CKGameLoop::kModeStartLevel && manager->m_currentLevel == level) return true;
        if (g_pCKGameLoop->m_mode == CKGameLoop::kModeQuit) break;
    }
    return false;
}

std::vector<RtAnimAnimation*> g_animations;
std::map<RwInt32, RpHAnimHierarchy*> g_hierarchies;  // the first level hierarchy of each node count

void CollectObject(IKSerializable* object, uint32_t classKey, void*) {
    if (classKey == 0xdcd) {  // CSectorAnimation
        const CSectorAnimation* sector = static_cast<const CSectorAnimation*>(object);
        for (uint32_t i = 0; i < sector->m_ui32NbAnimations; ++i) g_animations.push_back(sector->m_apAnimations[i]);
    } else if (classKey == 0x54b) {  // CAnimatedNode
        RpHAnimHierarchy* h = static_cast<CAnimatedNode*>(object)->m_pRpHAnimHierarchy;
        if (h != nullptr && g_hierarchies.count(h->numNodes) == 0) g_hierarchies[h->numNodes] = h;
    }
}

double Det(const RwMatrix& m) {
    return static_cast<double>(m.right.x) * (static_cast<double>(m.up.y) * m.at.z - static_cast<double>(m.up.z) * m.at.y) -
           static_cast<double>(m.right.y) * (static_cast<double>(m.up.x) * m.at.z - static_cast<double>(m.up.z) * m.at.x) +
           static_cast<double>(m.right.z) * (static_cast<double>(m.up.x) * m.at.y - static_cast<double>(m.up.y) * m.at.x);
}
double MaxDiff(const RwMatrix& a, const RwMatrix& b) {
    const RwV3d* ra[4] = {&a.right, &a.up, &a.at, &a.pos};
    const RwV3d* rb[4] = {&b.right, &b.up, &b.at, &b.pos};
    double d = 0.0;
    for (int i = 0; i < 4; ++i) {
        d = std::fmax(d, std::fabs(static_cast<double>(ra[i]->x) - rb[i]->x));
        d = std::fmax(d, std::fabs(static_cast<double>(ra[i]->y) - rb[i]->y));
        d = std::fmax(d, std::fabs(static_cast<double>(ra[i]->z) - rb[i]->z));
    }
    return d;
}

// Plays `animation` on `h` for 600 frames of 1/60 s.
void Play(const char* label, RpHAnimHierarchy* h, RtAnimAnimation* animation) {
    RtAnimInterpolator* interpolator = h->currentAnim;
    C15_CHECK(interpolator != nullptr && interpolator->numNodes == h->numNodes);
    RtAnimInterpolatorSetCurrentAnim(interpolator, animation);
    const RwInt32 n = h->numNodes;
    RpHAnimStdKeyFrame* frames = static_cast<RpHAnimStdKeyFrame*>(animation->pFrames);

    // t = 0: every node between key frame i and its second one, interpolated at 0 = key frame i.
    double startDiff = 0.0;
    for (RwInt32 i = 0; i < n; ++i) {
        RpHAnimInterpFrame* f = static_cast<RpHAnimInterpFrame*>(RtAnimInterpolatorGetInterpFrame(interpolator, i));
        C15_CHECK(f->keyFrame1 == &frames[i]);
        RpHAnimInterpFrame key = {};
        key.q = frames[i].q;
        key.t = frames[i].t;
        RwMatrix a = {}, b = {};
        RpHAnimKeyFrameApply(&a, f);
        RpHAnimKeyFrameApply(&b, &key);
        startDiff = std::fmax(startDiff, MaxDiff(a, b));
    }
    C15_CHECK(startDiff < 1e-5);

    // The parent of each node (the push/pop stack of RpHAnimHierarchyUpdateMatrices); -1 for the root.
    std::vector<RwInt32> parentOf(static_cast<size_t>(n), -1);
    {
        std::vector<RwInt32> stack;
        RwInt32 parent = -1;
        for (RwInt32 i = 0; i < n; ++i) {
            parentOf[static_cast<size_t>(i)] = parent;
            switch (h->pNodeInfo[i].flags & 3) {
                case rpHANIMPOPPARENTMATRIX:  // the last node pops an empty stack (its parent is never used)
                    parent = stack.empty() ? -1 : stack.back();
                    if (!stack.empty()) stack.pop_back();
                    break;
                case rpHANIMPUSHPARENTMATRIX: stack.push_back(parent); parent = i; break;
                case 0: parent = i; break;
                default: break;
            }
        }
    }
    double worstKey = 0.0;
    for (RwInt32 k = 0; k < animation->numFrames; ++k) {
        const RtQuat& q = frames[k].q;
        const double q2 = static_cast<double>(q.imag.x) * q.imag.x + static_cast<double>(q.imag.y) * q.imag.y +
                          static_cast<double>(q.imag.z) * q.imag.z + static_cast<double>(q.real) * q.real;
        worstKey = std::fmax(worstKey, std::fabs(q2 - 1.0));
    }
    C15_CHECK(worstKey < 1e-5);
    std::vector<double> worldDet(static_cast<size_t>(n), 1.0);
    std::vector<RwInt32> lastIndex(static_cast<size_t>(n), 0);
    const RwReal dt = 1.0f / 60.0f;
    uint32_t loops = 0, walkBack = 0, timeBad = 0, matrixBad = 0, steps = 0, lerped = 0, slerped = 0;
    double worstSlerpDet = 0.0, worstSlerpNorm = 0.0, worstLerpDet = 0.0, worstWorldDet = 0.0, worstChain = 0.0;
    for (int frame = 0; frame < 600; ++frame) {
        const RwReal before = interpolator->currentTime;
        RtAnimInterpolatorAddAnimTime(interpolator, dt);
        RpHAnimHierarchyUpdateMatrices(h);
        const RwReal after = interpolator->currentTime;
        const bool looped = !(animation->duration >= before + dt);
        if (looped) {
            ++loops;
            if (std::fabs(after - (before + dt - animation->duration)) > 1e-5f) ++timeBad;
        } else if (after != before + dt) {
            ++timeBad;
        }
        if (after < 0.0f || after > animation->duration) ++timeBad;
        for (RwInt32 i = 0; i < n; ++i) {
            RpHAnimInterpFrame* f = static_cast<RpHAnimInterpFrame*>(RtAnimInterpolatorGetInterpFrame(interpolator, i));
            const RwInt32 index = static_cast<RwInt32>(f->keyFrame1 - frames);
            if (index < lastIndex[static_cast<size_t>(i)] && !looped) ++walkBack;
            lastIndex[static_cast<size_t>(i)] = index;
            C15_CHECK(f->keyFrame1->time <= after + 1e-6f && after <= f->keyFrame2->time + 1e-6f);
            // The branch the scheme took: the dot product of the two key frames (after the in-place negation).
            const RtQuat& a = f->keyFrame1->q;
            const RtQuat& b = f->keyFrame2->q;
            const double dot = std::fabs(static_cast<double>(a.imag.x) * b.imag.x + static_cast<double>(a.imag.y) * b.imag.y +
                                         static_cast<double>(a.imag.z) * b.imag.z + static_cast<double>(a.real) * b.real);
            const double q2 = static_cast<double>(f->q.imag.x) * f->q.imag.x + static_cast<double>(f->q.imag.y) * f->q.imag.y +
                              static_cast<double>(f->q.imag.z) * f->q.imag.z + static_cast<double>(f->q.real) * f->q.real;
            RwMatrix local = {};
            RpHAnimKeyFrameApply(&local, f);
            const double localDet = Det(local);
            // (dot is recomputed in double here: next to 0.999 either branch is accepted.)
            const bool slerpOk = std::fabs(q2 - 1.0) < 1e-4 && std::fabs(localDet - 1.0) < 1e-4;
            const bool lerpOk = q2 >= 0.9995 - 1e-6 && std::fabs(localDet - 1.0) <= 4.0 * std::fabs(1.0 - q2) + 1e-5;
            if (dot >= 0.999) {
                ++lerped;
                worstLerpDet = std::fmax(worstLerpDet, std::fabs(localDet - 1.0));
                if (!lerpOk && !(dot < 0.999 + 1e-6 && slerpOk)) ++matrixBad;
            } else {
                ++slerped;
                worstSlerpDet = std::fmax(worstSlerpDet, std::fabs(localDet - 1.0));
                worstSlerpNorm = std::fmax(worstSlerpNorm, std::fabs(q2 - 1.0));
                if (!slerpOk && !(dot > 0.999 - 1e-6 && lerpOk)) ++matrixBad;
            }
            const RwInt32 p = parentOf[static_cast<size_t>(i)];
            const double world = Det(h->pMatrixArray[i]);
            const double expected = localDet * (p < 0 ? 1.0 : worldDet[static_cast<size_t>(p)]);
            worldDet[static_cast<size_t>(i)] = world;
            worstWorldDet = std::fmax(worstWorldDet, std::fabs(world - 1.0));
            worstChain = std::fmax(worstChain, std::fabs(world - expected));
            if (!(std::fabs(world - expected) < 1e-4)) ++matrixBad;
        }
        ++steps;
    }
    std::printf("anim_interp: %s: %d nodes, %d key frames, duration %.4f s; %u steps, %u loops, time errors %u, walk back %u; "
                "key frames ||q|^2-1| <= %.1e; slerped %u (|q|^2-1 %.1e, local |det-1| %.1e), lerped %u (local |det-1| %.1e); "
                "hierarchy |det-1| up to %.1e, det vs local x parent %.1e; off %u; t=0 vs first key frames %.1e\n",
                label, n, animation->numFrames, static_cast<double>(animation->duration), steps, loops, timeBad, walkBack,
                worstKey, slerped, worstSlerpNorm, worstSlerpDet, lerped, worstLerpDet, worstWorldDet, worstChain, matrixBad,
                startDiff);
    C15_CHECK(loops > 0);
    C15_CHECK(timeBad == 0);
    C15_CHECK(walkBack == 0);
    C15_CHECK(matrixBad == 0);
}

}  // namespace

int main() {
    std::setvbuf(stdout, nullptr, _IONBF, 0);
    if (!c15::BootToFrontEnd()) {
        std::printf("anim_interp: no game data configured: skipped\n");
        return 77;
    }
    c15::ParkFrontEndSequence();
    const bool reached = LoadLevel(10);
    C15_CHECK(reached);
    if (reached) Kp3_ForEachLoadedObject(CollectObject, nullptr);
    std::printf("anim_interp: %zu animations, hierarchies of %zu sizes\n", g_animations.size(), g_hierarchies.size());
    const RwInt32 kSizes[2] = {60, 3};
    const char* kLabels[2] = {"60-node (dragon)", "3-node (prop)"};
    for (int k = 0; k < 2; ++k) {
        RtAnimAnimation* chosen = nullptr;
        for (RtAnimAnimation* a : g_animations) {
            // The first one of that node count shorter than the 10 s run, so that it loops.
            if (RtAnimAnimationGetNumNodes(a) == kSizes[k] && a->duration < 9.0f && a->duration > 0.5f) {
                chosen = a;
                break;
            }
        }
        C15_CHECK(chosen != nullptr && g_hierarchies.count(kSizes[k]) == 1);
        if (chosen != nullptr && g_hierarchies.count(kSizes[k]) == 1) Play(kLabels[k], g_hierarchies[kSizes[k]], chosen);
    }
    std::fflush(stdout);
    if (c15::g_failures == 0) std::printf("anim_interp: all tests passed\n");
    std::fflush(stdout);
    std::_Exit(c15::g_failures == 0 ? 0 : 1);
}
