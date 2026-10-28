// verify_test - C1.5 family E: the native Maestro dump (Rt2dDebugDump).
//
// 1. The walker on a small hand-built maestro (no game data): the JSON holds what the structs hold, in
//    maestro_live.py's shape (structural references, float bits, the compact keyframe data decoded). With
//    DOTD_VERIFY_IMAGE=dir (32-bit parity build) it also writes dir/verify-image.json (the memory of that
//    maestro) and dir/verify-native.json: `python work/maestro_live.py --image dir/verify-image.json --out
//    walk.json`, then `python work/maestro_diff.py dir/verify-native.json walk.json --strict` checks that
//    the live walker and this one agree (0 differences).
// 2. Boots to the front end (skipped without game data), optionally steps DOTD_DUMP_MAESTRO_FRAMES frames
//    of 1/60 s, and dumps every CKFlashUI's maestro. With DOTD_DUMP_MAESTRO=path the dump is written there
//    (compare it with an RPCS3 dump: python work/maestro_diff.py path outputs/remake/maestro/maestro-*.json.gz);
//    without it the test only walks them.
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <vector>

#include "Renderware/rt2d/Rt2dDebugDump.h"
#include "Renderware/rt2d/Rt2dTypes.h"
#include "Renderware/rwcore/RwSList.h"
#include "boot_helper.h"
#include "k2000/graphical/ui/CKFlashManager.h"
#include "k2000/graphical/ui/CKFlashUI.h"
#include "k2000/logic/CKSector.h"
#include "k2000/misc/Engine.h"

namespace {

bool Has(const std::string& json, const char* fragment) {
    if (json.find(fragment) != std::string::npos) return true;
    std::printf("  missing: %s\n", fragment);
    return false;
}

// The memory the hand-built maestro occupies, for the image DOTD_VERIFY_IMAGE writes.
std::vector<std::pair<const void*, size_t>> g_regions;

void Region(const void* p, size_t size) { g_regions.emplace_back(p, size); }

void RegionList(const RwSList* list) {
    Region(list, sizeof(RwSList));
    if (list->listElements != nullptr)
        Region(list->listElements, static_cast<size_t>(list->numElementsAlloced) * static_cast<size_t>(list->entrySize));
}

// Writes dir/verify-image.json (the regions, little-endian, 32-bit pointers) and dir/verify-native.json
// (this walker's dump of the same maestro). work/maestro_live.py --image walks the image with the live
// walker; maestro_diff.py then compares the two walks (they must agree).
void WriteImage(const char* dir, const Rt2dMaestro* maestro) {
    if (sizeof(void*) != 4) {
        std::printf("verify: DOTD_VERIFY_IMAGE needs the 32-bit (parity) build; not written\n");
        return;
    }
    std::string image = "{\"littleEndian\":true,\"maestro\":";
    image += std::to_string(static_cast<uint32_t>(reinterpret_cast<uintptr_t>(maestro)));
    image += ",\"regions\":[";
    static const char kHex[] = "0123456789abcdef";
    for (size_t i = 0; i < g_regions.size(); ++i) {
        if (i != 0) image += ',';
        image += '[' + std::to_string(static_cast<uint32_t>(reinterpret_cast<uintptr_t>(g_regions[i].first))) + ",\"";
        const uint8_t* b = static_cast<const uint8_t*>(g_regions[i].first);
        for (size_t k = 0; k < g_regions[i].second; ++k) {
            image += kHex[b[k] >> 4];
            image += kHex[b[k] & 15];
        }
        image += "\"]";
    }
    image += "]}";
    const std::string imagePath = std::string(dir) + "/verify-image.json";
    FILE* f = std::fopen(imagePath.c_str(), "wb");
    C15_CHECK(f != nullptr);
    if (f == nullptr) return;
    std::fwrite(image.data(), 1, image.size(), f);
    std::fclose(f);
    Rt2dDebugDumpUI ui = {0, 0, Rt2dDebugDumpSceneVisible(maestro), false, maestro};
    C15_CHECK(Rt2dDebugDumpWrite((std::string(dir) + "/verify-native.json").c_str(), "image", 0, &ui, 1));
    std::printf("verify: image and native walk -> %s\n", dir);
}

void Identity(RwMatrix* m) {
    std::memset(m, 0, sizeof(*m));
    m->right.x = 1.0f;
    m->up.y = 1.0f;
    m->at.z = 1.0f;
}

void SyntheticTest() {
    // A scene with two children: a shape (one node: a closed 2-point path, a red brush) and an object string.
    Rt2dObject* scene = new Rt2dObject();
    std::memset(scene, 0, sizeof(*scene));
    scene->type = rt2DOBJECTTYPESCENE;
    scene->depth = 666;
    scene->flag = 4;
    Identity(&scene->MTM);
    Identity(&scene->LTM);
    scene->colorMult = {1.0f, 1.0f, 1.0f, 1.0f};
    scene->data.scene.objects = _rwSListCreate(sizeof(Rt2dObject), 0);
    Rt2dObject* shape = static_cast<Rt2dObject*>(_rwSListGetNewEntries(scene->data.scene.objects, 3, 0));
    Rt2dObject* text = shape + 1;
    Rt2dObject* pick = shape + 2;
    std::memset(shape, 0, 3 * sizeof(Rt2dObject));
    scene->data.scene.objectCount = 3;
    scene->data.scene.depths = _rwSListCreate(sizeof(_rt2dDepthOfObject), 0);
    _rt2dDepthOfObject* depth = static_cast<_rt2dDepthOfObject*>(_rwSListGetNewEntry(scene->data.scene.depths, 0));
    depth->object = text;
    depth->depth = 3;

    shape->type = rt2DOBJECTTYPESHAPE;
    shape->depth = -666;
    shape->flag = 3;
    Identity(&shape->MTM);
    shape->MTM.pos.x = 2.5f;
    rt2dPathNode nodes[2] = {{rt2dMOVE, {0.0f, 0.0f}, {0.0f, 0.0f}, 0.0f}, {rt2dLINE, {10.0f, 0.0f}, {0.0f, 1.0f}, 10.0f}};
    Rt2dPath path = {nodes, 2, 1, 1, 0.0f, nullptr, nullptr};
    path.curr = &path;
    Rt2dBrush brush;
    std::memset(&brush, 0, sizeof(brush));
    brush.top.col = {255.0f, 0.0f, 0.0f, 255.0f};
    brush.colorCache = {0xff, 0x00, 0x00, 0xff};
    brush.refCount = 1;
    _rt2dShapeRep rep = {_rwSListCreate(sizeof(_rt2dShapeNode), 0), 2, nullptr};
    _rt2dShapeNode* node = static_cast<_rt2dShapeNode*>(_rwSListGetNewEntry(rep.nodes, 0));
    node->flag = 1;
    node->path = &path;
    node->brush = &brush;
    RwRGBA cache = {0x11, 0x22, 0x33, 0x44};
    shape->data.shape.rep = &rep;
    shape->data.shape.colorCache = &cache;

    text->type = rt2DOBJECTTYPEOBJECTSTRING;
    text->depth = 3;
    text->flag = 0xc;
    Rt2dFontChar chars[4] = {'O', 'k', '!', 0};
    Rt2dFont* font = new Rt2dFont();
    std::memset(font, 0, sizeof(*font));
    font->flag = 2;  // 2-byte characters
    char fontName[] = "Fonte_Flash_0";
    _rt2dFontDictionaryNode fontNode = {fontName, font, nullptr};
    text->data.objectString.textString = reinterpret_cast<RwChar*>(chars);
    text->data.objectString.maxLength = 6;
    text->data.objectString.height = 28.0f;
    text->data.objectString.font = &fontNode;
    text->data.objectString.brush = &brush;
    text->data.objectString.boxwidth = 0.8f;

    // The maestro: two labels in the byte bucket, one animation node with a two-entry schedule.
    Rt2dMaestro* maestro = new Rt2dMaestro();
    std::memset(maestro, 0, sizeof(*maestro));
    maestro->scene = scene;
    maestro->currAnimIndex = -1;
    maestro->bbox = {0.0f, -0.0f, 800.0f, 600.0f};
    maestro->byteBucket = _rwSListCreate(1, 0);
    const char names[] = "start\0close";
    std::memcpy(_rwSListGetNewEntries(maestro->byteBucket, sizeof(names), 0), names, sizeof(names));
    maestro->labels = _rwSListCreate(sizeof(Rt2dStringLabel), 0);
    Rt2dStringLabel* labels = static_cast<Rt2dStringLabel*>(_rwSListGetNewEntries(maestro->labels, 2, 0));
    labels[0] = {rt2dANIMLABELTYPEFRAME, 0, reinterpret_cast<void*>(static_cast<intptr_t>(1)), nullptr};
    labels[1] = {rt2dANIMLABELTYPEURL, 6, reinterpret_cast<void*>(static_cast<intptr_t>(-1)), nullptr};
    Rt2dMessage queueStore[4] = {{rt2dMESSAGETYPEGETURL, 0, 4, 0}, {rt2dMESSAGETYPESTOP, 0, 4, 0}, {}, {}};
    Rt2dMessageQueue queue = {queueStore, 0, 2, 4};
    maestro->messageQueue = &queue;
    maestro->animations = _rwSListCreate(sizeof(Rt2dAnimNode), 0);
    Rt2dAnimNode* anim = static_cast<Rt2dAnimNode*>(_rwSListGetNewEntry(maestro->animations, 0));
    std::memset(anim, 0, sizeof(*anim));
    anim->flag = 6;
    anim->parent = -1;
    anim->posInParentScene = -1;
    anim->props.scene = scene;
    anim->props.directory = _rwSListCreate(sizeof(Rt2dObject*), 0);
    *static_cast<Rt2dObject**>(_rwSListGetNewEntry(anim->props.directory, 0)) = shape;
    *static_cast<Rt2dObject**>(_rwSListGetNewEntry(anim->props.directory, 0)) = text;
    anim->anim.deltaTimeScale = 1.0f;
    anim->anim.currentTime = 0.5f;
    anim->anim.flag = 3;
    // Compact data of keyframe list 0: object 0 with a transform and show, object 1 with show; then the end.
    alignas(16) RwUInt8 data[0x10 + 0x40 + 0x10 + 0x10 + 0x10 + 0x10] = {};
    RwUInt8* q = data;
    *reinterpret_cast<Rt2dKeyFrameSet*>(q) = {1 | 8, 0, {}};
    q += sizeof(Rt2dKeyFrameSet);
    Identity(&reinterpret_cast<Rt2dKeyFrameTransform*>(q)->matrix);
    reinterpret_cast<Rt2dKeyFrameTransform*>(q)->matrix.pos.y = -622.0f;
    q += sizeof(Rt2dKeyFrameTransform);
    *reinterpret_cast<Rt2dKeyFrameShow*>(q) = {1, 5, {}};
    q += sizeof(Rt2dKeyFrameShow);
    *reinterpret_cast<Rt2dKeyFrameSet*>(q) = {8, 1, {}};
    q += sizeof(Rt2dKeyFrameSet);
    *reinterpret_cast<Rt2dKeyFrameShow*>(q) = {0, -666, {}};
    q += sizeof(Rt2dKeyFrameShow);
    reinterpret_cast<Rt2dKeyFrameSet*>(q)->flag = 0x20;
    Rt2dKeyFrameList list0 = {0.0f, 0, data};
    Rt2dKeyFrameList list1 = {0.0f, 1, nullptr};
    anim->anim.keyframeLists = _rwSListCreate(sizeof(_rt2dAnimKeyFrameSched), 0);
    _rt2dAnimKeyFrameSched* sched =
        static_cast<_rt2dAnimKeyFrameSched*>(_rwSListGetNewEntries(anim->anim.keyframeLists, 2, 0));
    sched[0] = {0.0f, &list0};
    sched[1] = {1.0f / 30.0f, &list1};
    anim->anim.prev = &sched[0];
    anim->anim.next = &sched[1];
    anim->anim.last = &sched[1];

    // A pick region (reusing the path), a button, the message list and store, a cel list, a frame state.
    pick->type = rt2DOBJECTTYPEPICKREGION;
    pick->depth = 9;
    pick->data.pickRegion.path = &path;
    pick->data.pickRegion.bbox = {0.0f, 0.0f, 10.0f, 4.0f};
    Identity(&pick->data.pickRegion.transformation);
    maestro->buttons = _rwSListCreate(sizeof(Rt2dButton), 0);
    Rt2dButton* button = static_cast<Rt2dButton*>(_rwSListGetNewEntry(maestro->buttons, 0));
    std::memset(button, 0xff, sizeof(*button));
    button->strLabelIndex = 1;
    button->objectIndex = 2;
    button->stateFlag = 0x82;
    button->buttonState = 0;
    button->actionListForStateTransition[0] = 10;
    maestro->messageList = _rwSListCreate(sizeof(RwInt32), 0);
    RwInt32* messageList = static_cast<RwInt32*>(_rwSListGetNewEntries(maestro->messageList, 2, 0));
    messageList[0] = 0;
    messageList[1] = 12;
    maestro->messageStore = _rwSListCreate(sizeof(Rt2dMessage), 0);
    *static_cast<Rt2dMessage*>(_rwSListGetNewEntry(maestro->messageStore, 0)) = {rt2dMESSAGETYPEGOTOLABEL, 0, 1, -1};
    Rt2dCelList celList = {_rwSListCreate(sizeof(Rt2dCel), 0), 1};
    Rt2dCel* cel = static_cast<Rt2dCel*>(_rwSListGetNewEntry(celList.cel, 0));
    *cel = {0, 1, _rwSListCreate(sizeof(RwInt32), 0), 1};
    *static_cast<RwInt32*>(_rwSListGetNewEntry(cel->buttonIndices, 0)) = 0;
    anim->celList = &celList;
    anim->props.sceneCurrentState = _rwSListCreate(sizeof(Rt2dAnimObjectUpdate), 0);
    Rt2dAnimObjectUpdate* update =
        static_cast<Rt2dAnimObjectUpdate*>(_rwSListGetNewEntry(anim->props.sceneCurrentState, 0));
    std::memset(update, 0, sizeof(*update));
    update->hasSomething = 1;
    update->object = shape;
    update->hasShow = 1;
    update->show.show = 1;
    update->show.depth = 5;
    update->morph.source = text;  // stale contents with hasMorph 0, as in the original

    if (const char* dir = std::getenv("DOTD_VERIFY_IMAGE")) {
        Region(maestro, sizeof(*maestro));
        Region(scene, sizeof(*scene));
        RegionList(scene->data.scene.objects);
        RegionList(scene->data.scene.depths);
        Region(nodes, sizeof(nodes));
        Region(&path, sizeof(path));
        Region(&brush, sizeof(brush));
        Region(&rep, sizeof(rep));
        RegionList(rep.nodes);
        Region(&cache, sizeof(cache));
        Region(chars, sizeof(chars));
        Region(font, sizeof(*font));
        Region(fontName, sizeof(fontName));
        Region(&fontNode, sizeof(fontNode));
        RegionList(maestro->byteBucket);
        RegionList(maestro->labels);
        Region(queueStore, sizeof(queueStore));
        Region(&queue, sizeof(queue));
        RegionList(maestro->animations);
        RegionList(anim->props.directory);
        RegionList(anim->anim.keyframeLists);
        RegionList(maestro->buttons);
        RegionList(maestro->messageList);
        RegionList(maestro->messageStore);
        Region(&celList, sizeof(celList));
        RegionList(celList.cel);
        RegionList(cel->buttonIndices);
        RegionList(anim->props.sceneCurrentState);
        Region(data, sizeof(data));
        Region(&list0, sizeof(list0));
        Region(&list1, sizeof(list1));
        WriteImage(dir, maestro);
    }

    const std::string json = Rt2dDebugDumpMaestro(maestro);
    C15_CHECK(Has(json, "\"bbox\":[\"f:00000000\",\"f:80000000\",\"f:44480000\",\"f:44160000\"]"));
    C15_CHECK(Has(json, "\"name\":\"start\""));
    C15_CHECK(Has(json, "\"name\":\"close\""));
    C15_CHECK(Has(json, "\"pending\":[[7,0,4,0],[2,0,4,0]]"));
    C15_CHECK(Has(json, "\"path\":\"s/0\""));
    C15_CHECK(Has(json, "\"path\":\"s/1\""));
    C15_CHECK(Has(json, "\"pos\":[\"f:40200000\",\"f:00000000\",\"f:00000000\"]"));  // the shape's MTM
    C15_CHECK(Has(json, "\"rep\":\"#0\""));
    C15_CHECK(Has(json, "\"colorCache\":[\"11223344\"]"));
    C15_CHECK(Has(json, "\"segments\":\"array\",\"numSegment\":2,\"closed\":1,\"flat\":1"));
    C15_CHECK(Has(json, "\"curr\":0"));
    C15_CHECK(Has(json, "[1,\"f:41200000\",\"f:00000000\",\"f:00000000\",\"f:3f800000\",\"f:41200000\"]"));
    C15_CHECK(Has(json, "\"colorCache\":\"ff0000ff\""));
    C15_CHECK(Has(json, "\"text\":\"Ok!\""));
    C15_CHECK(Has(json, "\"font\":\"Fonte_Flash_0\",\"wideChars\":true"));
    C15_CHECK(Has(json, "\"depths\":[[\"@s/1\",3]]"));
    C15_CHECK(Has(json, "\"directory\":[\"@s/0\",\"@s/1\"]"));
    C15_CHECK(Has(json, "\"prev\":0,\"next\":1,\"last\":1"));
    C15_CHECK(Has(json, "\"currentTime\":\"f:3f000000\""));
    C15_CHECK(Has(json, "{\"flag\":8,\"objectIdx\":1,\"show\":[0,-666]}"));
    C15_CHECK(Has(json, "\"pos\":[\"f:00000000\",\"f:c41b8000\",\"f:00000000\"]},\"show\":[1,5]}"));
    C15_CHECK(Has(json, "\"isLocked\":1,\"sets\":null"));
    C15_CHECK(Has(json, "\"scene\":\"@s\""));
    C15_CHECK(Has(json, "\"type\":3,\"depth\":9"));
    C15_CHECK(Has(json, "\"bbox\":[\"f:00000000\",\"f:00000000\",\"f:41200000\",\"f:40800000\"]"));
    C15_CHECK(Has(json, "\"strLabelIndex\":1,\"objectIndex\":2,\"stateFlag\":\"00000082\",\"buttonState\":\"00000000\","
                        "\"actions\":[10,-1,"));
    C15_CHECK(Has(json, "\"messageList\":[0,12]"));
    C15_CHECK(Has(json, "\"messageStore\":[[6,0,1,-1]]"));
    C15_CHECK(Has(json, "\"celList\":{\"flag\":\"00000001\",\"cels\":[{\"strLabelIndex\":0,\"celIndex\":1,"
                        "\"buttonIndices\":[0],\"messageListIndex\":1}]}"));
    C15_CHECK(Has(json, "\"hasSomething\":1,\"object\":\"@s/0\""));
    C15_CHECK(Has(json, "\"hasMorph\":0,\"morph\":[\"@s/1\",null,\"f:00000000\"]"));
    C15_CHECK(Rt2dDebugDumpSceneVisible(maestro));
    C15_CHECK(Rt2dDebugDumpMaestro(nullptr) == "null");
    // Lists and objects stay allocated: the process ends right after the test.
}

}  // namespace

int main() {
    SyntheticTest();

    if (!c15::BootToFrontEnd()) {
        std::printf("verify: no game data configured; boot part skipped\n");
        return c15::g_failures == 0 ? 77 : 1;
    }
    int frames = 0;
    if (const char* env = std::getenv("DOTD_DUMP_MAESTRO_FRAMES")) frames = std::atoi(env);
    for (int i = 0; i < frames; ++i) c15::RunFrame();

    CKFlashManager* manager = g_pEngine->m_flashManager;
    C15_CHECK(manager != nullptr);
    std::vector<Rt2dDebugDumpUI> uis;
    if (manager != nullptr) {
        for (uint32_t i = 0; i < manager->m_ui32NbFlashUI; ++i) {
            CKFlashUI* ui = static_cast<CKFlashUI*>(manager->m_apFlashUI[i]);
            Rt2dDebugDumpUI entry = {static_cast<int32_t>(i), 0, false, false, nullptr};
            if (ui != nullptr) {
                entry.flags44 = ui->m_baFlags;
                entry.maestro = ui->m_pMaestro;
                entry.sceneVisible = Rt2dDebugDumpSceneVisible(ui->m_pMaestro);
                // DrawFlashUISceneAndSynchronizeWidgets 0x6f280: the +0x230 sector's property bit 0, the scene
                // visible, CKFlashUI flag 0x20 clear.
                bool active = false;
                if (ui->m_pSector != nullptr)
                    active = (ui->m_pSector->m_ba16Properties & 1) != 0;
                entry.drawn = active && entry.sceneVisible && (ui->m_baFlags & 0x20) == 0;
            }
            uis.push_back(entry);
            // Every maestro walks (whatever the readers have filled in so far).
            C15_CHECK(!Rt2dDebugDumpMaestro(entry.maestro).empty());
        }
        std::printf("verify: %u CKFlashUI after %d frames, %d with a maestro\n", manager->m_ui32NbFlashUI, frames,
                    static_cast<int>(std::count_if(uis.begin(), uis.end(),
                                                   [](const Rt2dDebugDumpUI& u) { return u.maestro != nullptr; })));
        C15_CHECK(manager->m_ui32NbFlashUI == 29);  // LVL000's CKFlashUI count
    }
    if (const char* path = std::getenv("DOTD_DUMP_MAESTRO")) {
        const bool written = Rt2dDebugDumpWrite(path, "native", c15::FrameCount(), uis.data(),
                                                static_cast<int32_t>(uis.size()));
        C15_CHECK(written);
        if (written) std::printf("verify: maestro dump -> %s\n", path);
    }
    c15::Shutdown();
    if (c15::g_failures == 0) std::printf("verify: all tests passed\n");
    return c15::g_failures == 0 ? 0 : 1;
}
