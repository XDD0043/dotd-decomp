// anim_test - C1.5 family C (tool/2danim): the Rt2dAnim time stepping and the keyframe interpolation on
// hand-built data, then every LVL000 movie read by Rt2dMaestroStreamRead against the counts of the live
// maestros (RPCS3 at the main menu, 2026-10-17), and the press-start movie's labels, cels and messages.
// When the maestros have their scenes (family B's reader), the press-start movie is also played at 1/60 s
// per frame and the GETURL labels it posts are checked against the frames their keyframes are on.
#include <cmath>
#include <cstdio>
#include <cstring>
#include <string>
#include <vector>

#include "Renderware/rt2d/Rt2d.h"
#include "Renderware/rt2danim/Rt2dAnimPrivate.h"
#include "Renderware/rwcore/RwMatrix.h"
#include "boot_helper.h"
#include "k2000/graphical/ui/CKFlashManager.h"
#include "k2000/graphical/ui/CKFlashUI.h"
#include "k2000/misc/Engine.h"

namespace {

uint32_t Bits(float f) {
    uint32_t u;
    std::memcpy(&u, &f, 4);
    return u;
}
float FromBits(uint32_t u) {
    float f;
    std::memcpy(&f, &u, 4);
    return f;
}

// A keyframe list whose compact data is the given bytes followed by the end set.
Rt2dKeyFrameList* MakeKeyFrameList(const std::vector<uint8_t>& sets) {
    Rt2dKeyFrameList* list = static_cast<Rt2dKeyFrameList*>(RwMalloc(sizeof(Rt2dKeyFrameList), 0));
    list->time = 0.0f;
    list->isLocked = 0;
    list->data = static_cast<RwUInt8*>(RwMalloc(static_cast<RwUInt32>(sets.size() + sizeof(Rt2dKeyFrameSet)), 0));
    std::memcpy(list->data, sets.data(), sets.size());
    Rt2dKeyFrameSet end{};
    end.flag = 0x20;
    std::memcpy(list->data + sets.size(), &end, sizeof(end));
    return list;
}

void Append(std::vector<uint8_t>& bytes, const void* p, size_t size) {
    const uint8_t* b = static_cast<const uint8_t*>(p);
    bytes.insert(bytes.end(), b, b + size);
}

// An anim over keyframes at the given times, each with the given compact data.
void MakeAnim(Rt2dAnim* anim, const std::vector<float>& times, const std::vector<std::vector<uint8_t>>& sets) {
    anim->keyframeLists = _rwSListCreate(static_cast<RwInt32>(sizeof(_rt2dAnimKeyFrameSched)), 0);
    for (size_t i = 0; i < times.size(); ++i) {
        _rt2dAnimKeyFrameSched* entry = static_cast<_rt2dAnimKeyFrameSched*>(_rwSListGetNewEntry(anim->keyframeLists, 0));
        entry->time = times[i];
        entry->keyframeList = MakeKeyFrameList(sets[i]);
    }
    anim->deltaTimeScale = 1.0f;
    anim->currentTime = 0.0f;
    anim->flag = 1;
    anim->prev = anim->next = anim->last = nullptr;
}

// Part A: the cursors and the time over five keyframes 0.04 s apart (the movies' 25 frames per second),
// stepped at 1/60 s; the end clamps and Goto goes back through a reset.
void TestAnimStepping() {
    const std::vector<float> times = {0.0f, FromBits(0x3d23d70a), FromBits(0x3da3d70a), FromBits(0x3df5c28f),
                                      FromBits(0x3e23d70a)};  // 0, 0.04, 0.08, 0.12, 0.16 as in the movies
    Rt2dAnim anim;
    MakeAnim(&anim, times, std::vector<std::vector<uint8_t>>(times.size()));
    Rt2dAnimProps props{};
    props.directory = _rwSListCreate(static_cast<RwInt32>(sizeof(Rt2dObject*)), 0);
    props.sceneCurrentState = _rt2dAnimPropsCreateSceneCurrentState(&props);

    Rt2dAnimReset(&anim, &props);
    C15_CHECK(anim.prev == nullptr && Rt2dAnimGetNextFrameIndex(&anim) == 0 && Rt2dAnimGetPrevFrameIndex(&anim) == -1);
    C15_CHECK(Rt2dAnimGetFinalKeyFrameListTime(&anim) == times[4]);
    Rt2dAnimAddDeltaFrameIndex(&anim, &props, 1);
    C15_CHECK(Rt2dAnimGetPrevFrameIndex(&anim) == 0 && Rt2dAnimGetNextFrameIndex(&anim) == 1);

    const float dt = 1.0f / 60.0f;
    // Expected: time += dt (fmadds with scale 1: one rounding), the prev keyframe the last one at or
    // before it, clamped to the last keyframe's time.
    float expected = 0.0f;
    for (int step = 1; step <= 12; ++step) {
        Rt2dAnimAddDeltaTime(&anim, &props, dt);
        expected = expected + dt;
        if (expected > times[4]) expected = times[4];
        int32_t prevIndex = 0;
        for (int32_t k = 0; k < 5; ++k)
            if (times[k] <= expected) prevIndex = k;
        C15_CHECK(Bits(Rt2dAnimGetCurrentTime(&anim)) == Bits(expected));
        C15_CHECK(Rt2dAnimGetPrevFrameIndex(&anim) == prevIndex);
    }
    C15_CHECK(anim.next == nullptr && Rt2dAnimGetPrevFrameIndex(&anim) == 4);
    C15_CHECK(Rt2dAnimGetNextFrameIndex(&anim) == 5);
    C15_CHECK(Rt2dAnimGetNextFrameTime(&anim) == times[4]);
    // Step 3 lands on 0.05 (frame 1), step 5 on 0.0833 (frame 2): the frame each keyframe is reached on.
    Rt2dAnimReset(&anim, &props);
    Rt2dAnimAddDeltaFrameIndex(&anim, &props, 1);
    int32_t firstStep[5] = {0, -1, -1, -1, -1};
    for (int step = 1; step <= 12; ++step) {
        Rt2dAnimAddDeltaTime(&anim, &props, dt);
        const int32_t k = Rt2dAnimGetPrevFrameIndex(&anim);
        if (firstStep[k] < 0) firstStep[k] = step;
    }
    C15_CHECK(firstStep[1] == 3 && firstStep[2] == 5 && firstStep[3] == 8 && firstStep[4] == 10);

    // Goto backwards: reset, step to keyframe 0, then forward to the target.
    Rt2dAnimGotoKeyFrameListByIndex(&anim, &props, 1);
    C15_CHECK(Rt2dAnimGetPrevFrameIndex(&anim) == 1 && anim.currentTime == times[1]);
    Rt2dAnimGotoKeyFrameListByIndex(&anim, &props, 3);
    C15_CHECK(Rt2dAnimGetPrevFrameIndex(&anim) == 3 && anim.currentTime == times[3]);
    // A delta of 0 changes nothing; the interpolate flag is bit 1.
    Rt2dAnimAddDeltaTime(&anim, &props, 0.0f);
    C15_CHECK(Rt2dAnimGetPrevFrameIndex(&anim) == 3);
    C15_CHECK(Rt2dAnimIsInterpolated(&anim) == 0);
    Rt2dAnimSetInterpolate(&anim, 1);
    C15_CHECK(anim.flag == 3 && Rt2dAnimIsInterpolated(&anim) == 1);
    C15_CHECK(Rt2dAnimTimeUpdate(&anim, &props) == &anim);
    _rt2dAnimDestruct(&anim, &props);
    _rt2dAnimPropsDestruct(&props);
}

// Part B: Advance puts a keyframe's transform and colours in the frame state; Apply interpolates the
// pending ones into the object for 0 < alpha < 1 (fsubs/fmuls/fadds for the transform, fmadds for the
// colours, the offset times 255).
void TestKeyFrameInterpolation() {
    Rt2dObject* object = static_cast<Rt2dObject*>(RwMalloc(sizeof(Rt2dObject), 0));
    std::memset(object, 0, sizeof(Rt2dObject));
    object->type = rt2DOBJECTTYPESHAPE;
    object->flag = 6;
    Rt2dAnimProps props{};
    props.directory = _rwSListCreate(static_cast<RwInt32>(sizeof(Rt2dObject*)), 0);
    *static_cast<Rt2dObject**>(_rwSListGetNewEntry(props.directory, 0)) = object;
    props.sceneCurrentState = _rt2dAnimPropsCreateSceneCurrentState(&props);
    C15_CHECK(_rwSListGetNumEntries(props.sceneCurrentState) == 1);
    C15_CHECK(RwSListArray<Rt2dAnimObjectUpdate>(props.sceneCurrentState)->object == object);

    auto frame = [](float x, float scale, float mult, float offs) {
        std::vector<uint8_t> bytes;
        Rt2dKeyFrameSet set{};
        set.flag = 1 | 2 | 4;
        set.objectIdx = 0;
        Append(bytes, &set, sizeof(set));
        RwMatrix m{};
        m.right = {scale, 0.0f, 0.0f};
        m.up = {0.0f, scale, 0.0f};
        m.at = {0.0f, 0.0f, 1.0f};
        m.pos = {x, 2.0f * x, 0.0f};
        m.flags = 0;
        Append(bytes, &m, sizeof(m));
        RwRGBAReal o = {offs, offs, offs, 0.0f};
        Append(bytes, &o, sizeof(o));
        RwRGBAReal c = {mult, mult, mult, 1.0f};
        Append(bytes, &c, sizeof(c));
        return bytes;
    };
    Rt2dKeyFrameList* from = MakeKeyFrameList(frame(0.0f, 1.0f, 1.0f, 0.0f));
    Rt2dKeyFrameList* to = MakeKeyFrameList(frame(8.0f, 3.0f, 0.0f, 1.0f));
    Rt2dKeyFrameListAdvance(from, &props);
    const Rt2dAnimObjectUpdate* state = RwSListArray<Rt2dAnimObjectUpdate>(props.sceneCurrentState);
    C15_CHECK(state->hasSomething == 1 && state->hasTransform == 1 && state->hasColorOffs == 1 &&
              state->hasColorMult == 1 && state->hasShow == 0);
    Rt2dKeyFrameListApply(to, &props, 0.25f);
    C15_CHECK(object->MTM.pos.x == 2.0f && object->MTM.pos.y == 4.0f);
    C15_CHECK(object->MTM.right.x == 1.5f && object->MTM.up.y == 1.5f);
    C15_CHECK(object->colorMult.red == 0.75f && object->colorMult.alpha == 1.0f);
    C15_CHECK(object->colorOffs.red == 63.75f && object->colorOffs.alpha == 0.0f);
    C15_CHECK((object->flag & 8) != 0);
    C15_CHECK(state->hasSomething == 0 && state->hasTransform == 0 && state->hasColorMult == 0);
    // alpha 0 does not interpolate: the pending parts go to the object through the Rt2d setters.
    Rt2dKeyFrameListAdvance(to, &props);
    object->MTM.pos.x = 0.0f;
    Rt2dKeyFrameListApply(to, &props, 0.0f);
    C15_CHECK(state->hasSomething == 0 && state->hasTransform == 0);
    Rt2dKeyFrameListDestroy(from);
    Rt2dKeyFrameListDestroy(to);
    _rt2dAnimPropsDestruct(&props);
    RwFree(object);
}

// The live maestros' sizes per LVL000 CKFlashUI (RPCS3, main menu, 2026-10-17): animation nodes, labels,
// buttons, message store, message list, keyframes and cels over all nodes, cel button entries, bytes of
// label names.
struct MovieCounts {
    int32_t nodes, labels, buttons, store, list, keyframes, cels, celButtons, nameBytes;
};
const MovieCounts kLive[29] = {
    {1, 8, 2, 22, 13, 63, 63, 65, 123},    {1, 8, 2, 22, 13, 68, 68, 124, 123},  {1, 7, 2, 21, 13, 58, 58, 107, 108},
    {2, 14, 3, 33, 15, 22, 22, 25, 213},   {1, 10, 5, 31, 21, 5, 5, 25, 90},     {1, 7, 2, 21, 15, 30, 30, 60, 76},
    {1, 5, 2, 12, 6, 31, 31, 46, 66},      {1, 7, 2, 21, 13, 30, 30, 44, 103},   {1, 20, 7, 50, 20, 131, 131, 267, 292},
    {1, 6, 2, 19, 12, 2, 2, 3, 88},        {1, 6, 2, 17, 12, 30, 30, 44, 88},    {1, 6, 2, 19, 12, 30, 30, 44, 88},
    {1, 6, 2, 13, 6, 3, 3, 4, 88},         {1, 6, 2, 13, 6, 3, 3, 4, 88},        {1, 6, 3, 19, 12, 3, 3, 7, 88},
    {1, 7, 2, 21, 13, 23, 23, 35, 108},    {1, 6, 2, 19, 12, 11, 11, 15, 88},    {1, 7, 2, 21, 13, 30, 30, 44, 103},
    {1, 19, 8, 49, 20, 104, 104, 204, 271}, {2, 12, 3, 21, 9, 22, 22, 22, 156},  {1, 8, 2, 22, 13, 3, 3, 3, 123},
    {1, 6, 2, 19, 12, 23, 23, 34, 88},     {1, 6, 2, 19, 12, 17, 17, 25, 88},    {1, 6, 2, 13, 6, 3, 3, 4, 88},
    {2, 12, 3, 21, 9, 22, 22, 22, 141},    {1, 7, 2, 21, 13, 30, 30, 44, 103},   {1, 7, 2, 21, 13, 18, 18, 26, 103},
    {1, 8, 2, 22, 13, 30, 30, 44, 123},    {1, 8, 2, 22, 13, 65, 65, 83, 123},
};

MovieCounts Count(Rt2dMaestro* maestro) {
    MovieCounts c{};
    c.nodes = _rwSListGetNumEntries(maestro->animations);
    c.labels = _rwSListGetNumEntries(maestro->labels);
    c.buttons = _rwSListGetNumEntries(maestro->buttons);
    c.store = _rwSListGetNumEntries(maestro->messageStore);
    c.list = _rwSListGetNumEntries(maestro->messageList);
    c.nameBytes = _rwSListGetNumEntries(maestro->byteBucket);
    for (int32_t i = 0; i < c.nodes; ++i) {
        Rt2dAnimNode* node = _rt2dMaestroGetAnimNodeByIndex(maestro, i);
        c.keyframes += Rt2dAnimGetNumKeyFrameLists(&node->anim);
        const int32_t cels = _rwSListGetNumEntries(node->celList->cel);
        c.cels += cels;
        for (int32_t k = 0; k < cels; ++k) c.celButtons += _rwSListGetNumEntries(_rt2dCelListGetCelByIndex(node->celList, k)->buttonIndices);
    }
    return c;
}

// Part C, the press-start movie (#3): its labels as the live maestro has them, its root timeline's
// schedule (25 frames per second) and frame actions.
void TestPressStart(Rt2dMaestro* maestro) {
    struct Label {
        uint32_t type;
        const char* name;
        int32_t data;
    };
    const Label labels[14] = {
        {6, "onPressStart_Start", -1}, {2, "entree_press_start", 0}, {6, "onPressStart_Open", -1},
        {6, "onMenu_OpeningAnimEnd", -1}, {3, "Start_Interface", 0}, {2, "press_start", 2},
        {3, "Input_Start", 1}, {3, "Input_Confirm", 2}, {2, "sortie_press_start", 4},
        {6, "OnSnd_MenuClose", -1}, {6, "onPressStart_Close", -1}, {6, "onMenu_ClosingAnimEnd", -1},
        {1, "/", 0}, {1, "//", 1},
    };
    for (int32_t i = 0; i < 14; ++i) {
        Rt2dStringLabel* label = Rt2dMaestroGetStringLabelByIndex(maestro, i);
        C15_CHECK(label != nullptr && label->entityType == labels[i].type);
        C15_CHECK(std::strcmp(Rt2dMaestroGetStringLabelName(maestro, label), labels[i].name) == 0);
        C15_CHECK(Rt2dStringLabelData(label) == labels[i].data);
        int32_t index = -1;
        C15_CHECK(Rt2dMaestroFindStringLabel(maestro, static_cast<Rt2dStringLabelType>(labels[i].type),
                                             labels[i].name, &index) == label && index == i);
    }
    C15_CHECK(Rt2dMaestroGetStringLabelByIndex(maestro, 14) == nullptr);
    C15_CHECK(Rt2dMaestroFindStringLabel(maestro, rt2dANIMLABELTYPEFRAME, "onPressStart_Open", nullptr) == nullptr);
    Rt2dAnim* root = Rt2dMaestroGetAnimationsByIndex(maestro, 0);
    C15_CHECK(Rt2dAnimGetNumKeyFrameLists(root) == 21);
    for (int32_t k = 0; k < 21; ++k) {
        // The schedule times: k * 0.04 as the exporter computed them (bits read live).
        static const uint32_t kTimes[21] = {0x0, 0x3d23d70a, 0x3da3d70a, 0x3df5c28f, 0x3e23d70a, 0x3e4ccccc,
                                            0x3e75c28e, 0x3e8f5c28, 0x3ea3d709, 0x3eb851ea, 0x3ecccccb, 0x3ee147ac,
                                            0x3ef5c28d, 0x3f051eb7, 0x3f0f5c28, 0x3f199999, 0x3f23d70a, 0x3f2e147b,
                                            0x3f3851ec, 0x3f428f5d, 0x3f4cccce};
        C15_CHECK(Bits(RwSListEntry<_rt2dAnimKeyFrameSched>(root->keyframeLists, k)->time) == kTimes[k]);
    }
    C15_CHECK(root->last == RwSListEntry<_rt2dAnimKeyFrameSched>(root->keyframeLists, 20));
    // Frame actions: cels 0, 3, 4, 20 post message lists 11, 12, 13, 14.
    Rt2dAnimNode* node = _rt2dMaestroGetAnimNodeByIndex(maestro, 0);
    const int32_t celLists[21] = {11, -1, -1, 12, 13, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 14};
    for (int32_t k = 0; k < 21; ++k) C15_CHECK(_rt2dCelListGetCelByIndex(node->celList, k)->messageListIndex == celLists[k]);
    C15_CHECK(RwSListArray<RwInt32>(maestro->messageList)[12] == 22);
    const Rt2dMessage* stop = RwSListEntry<Rt2dMessage>(maestro->messageStore, 22);
    C15_CHECK(stop->messageType == rt2dMESSAGETYPESTOP && stop->index == -1);
    const Rt2dMessage* tell = RwSListEntry<Rt2dMessage>(maestro->messageStore, 24);
    C15_CHECK(tell->messageType == rt2dMESSAGETYPESPECIALTELLTARGET && tell->intParam1 == 0 && tell->intParam2 == 1);
    // Node 1 is the clip at child 3 of the root scene.
    Rt2dAnimNode* clip = _rt2dMaestroGetAnimNodeByIndex(maestro, 1);
    C15_CHECK(clip->parent == 0 && clip->posInParentScene == 3);
    C15_CHECK(maestro->bbox.w == 800.0f && maestro->bbox.h == 600.0f);
    C15_CHECK(maestro->messageHandler != nullptr && maestro->currAnimIndex == -1);
    C15_CHECK(maestro->stateTransTable[0][1][1][1].transState == 0xa00);
}

// After B: the GETURL labels the press-start movie posts, by frame, played from its first keyframe.
std::vector<std::string> g_urls;
uint32_t g_frame = 0;
Rt2dMessage* RecordingHandler(Rt2dMaestro* maestro, Rt2dMessage* message) {
    if (message->messageType == rt2dMESSAGETYPEGETURL) {
        Rt2dStringLabel* label = Rt2dMaestroGetStringLabelByIndex(maestro, message->intParam1);
        g_urls.push_back(std::to_string(g_frame) + ":" +
                         (label != nullptr ? Rt2dMaestroGetStringLabelName(maestro, label) : "?"));
    }
    return Rt2dMessageHandlerDefaultCallBack(maestro, message);
}

}  // namespace

int main() {
    Rt2dAnimOpen();
    TestAnimStepping();
    TestKeyFrameInterpolation();

    if (!c15::BootToFrontEnd()) {
        std::printf("anim: no game data configured; data tests skipped\n");
        return c15::g_failures == 0 ? 77 : 1;
    }
    CKFlashManager* manager = g_pEngine->m_flashManager;
    C15_CHECK(manager != nullptr && manager->m_ui32NbFlashUI == 29);
    bool haveScenes = true;
    if (manager != nullptr) {
        for (uint32_t i = 0; i < manager->m_ui32NbFlashUI && i < 29; ++i) {
            CKFlashUI* ui = static_cast<CKFlashUI*>(manager->m_apFlashUI[i]);
            Rt2dMaestro* maestro = ui->m_pMaestro;
            C15_CHECK(maestro != nullptr);
            if (maestro == nullptr) continue;
            const MovieCounts c = Count(maestro);
            const MovieCounts& e = kLive[i];
            const bool same = c.nodes == e.nodes && c.labels == e.labels && c.buttons == e.buttons &&
                              c.store == e.store && c.list == e.list && c.keyframes == e.keyframes &&
                              c.cels == e.cels && c.celButtons == e.celButtons && c.nameBytes == e.nameBytes;
            if (!same) std::printf("anim: movie %u counts differ from the live maestro\n", i);
            C15_CHECK(same);
            if (maestro->scene == nullptr) haveScenes = false;
        }
        TestPressStart(static_cast<CKFlashUI*>(manager->m_apFlashUI[3])->m_pMaestro);
    }
    if (haveScenes && manager != nullptr) {
        // Play the press-start movie's root from its first keyframe, as when the menu opens.
        Rt2dMaestro* maestro = static_cast<CKFlashUI*>(manager->m_apFlashUI[3])->m_pMaestro;
        Rt2dMaestroSetMessageHandler(maestro, RecordingHandler);
        Rt2dObjectSetVisible(maestro->scene, 1);
        Rt2dAnimNode* root = _rt2dMaestroGetAnimNodeByIndex(maestro, 0);
        root->flag &= ~1;
        for (g_frame = 1; g_frame <= 60; ++g_frame) {
            Rt2dMaestroAddDeltaTime(maestro, 1.0f / 60.0f);
            Rt2dMaestroUpdateAnimations(maestro);
            Rt2dMaestroProcessMessages(maestro);
        }
        for (const std::string& url : g_urls) std::printf("anim: press start %s\n", url.c_str());
        // Frame 0's actions (GETURL onPressStart_Open, onMenu_OpeningAnimEnd) go out on the first step;
        // keyframe 3 (0.12 s) stops the root: reached on step 8 (8/60 = 0.1333).
        C15_CHECK(g_urls.size() >= 2 && g_urls[0] == "1:onPressStart_Open" && g_urls[1] == "1:onMenu_OpeningAnimEnd");
        C15_CHECK(Rt2dAnimGetPrevFrameIndex(&root->anim) == 3 && (root->flag & 1) != 0);
    } else {
        std::printf("anim: maestros have no scenes yet (family B); playback test skipped\n");
    }
    c15::Shutdown();
    if (c15::g_failures == 0) std::printf("anim: all tests passed\n");
    return c15::g_failures == 0 ? 0 : 1;
}
