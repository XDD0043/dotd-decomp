// newgame_test - checkpoint C2.2's / C2.3's harness: boot, press START, then New game -> Start Story Mode -> Single Player
// through the menus exactly as a player does (Cross three times), then step into LVL010 (modes 9 -> 1 -> 4 -> 5)
// and log every loop mode / game state change. C2.2: game state 7, mode 5, the level started at the spawn sector.
// C2.3: the opening scene starts on the first gameplay frame (playing, input blocked, letterbox, blocking), its video
// (MOVIE/01/PS3_019.VID) takes the loop to modes 7 and 8 and back to 5 at its end; the frames in mode 8 are compared with
// the Bink header's frame count converted to the loop's 60 Hz (the harness clock steps 16667 microseconds per frame).
// DOTD_DUMP_LEVEL_OBJECTS=<path> writes the loaded objects at the end (objects_diff.py against objects-lvl010_ingame-*.json.gz).
// Skipped (77) without the game data, like the other tests that boot.
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <cmath>
#include <cstring>
#include <map>
#include <string>
#include <typeinfo>

#include "Spyro2008/logic/CKS08GameManager.h"
#include "boot_helper.h"
#include "k2000/cinematics/CKManageCameraCinematicBloc.h"
#include "k2000/cinematics/CKPathFindingCinematicBloc.h"
#include "k2000/cinematics/CKPlayAnimCinematicBloc.h"
#include "k2000/cinematics/CKPlayVideoCinematicBloc.h"
#include "k2000/dictionaries/CAnimationDictionary.h"
#include "k2000/graphical/animation/CAnimationManager.h"
#include "k2000/graphical/animation/CSectorAnimation.h"
#include "Renderware/rphanim/RpHAnim.h"
#include "Renderware/rtanim/RtAnim.h"
#include "k2000/graphical/CKAnmKeyFrameController.h"
#include "k2000/graphical/animation/CKBlenderController.h"
#include "k2000/render/CRenderer.h"
#include "k2000/scenegraph/CAnimatedNode.h"
#include "Renderware/rwcore/RwStream.h"
#include "k2000/cinematics/CKSekensorCinematicBloc.h"
#include "k2000/logic/io/CKStreamObject.h"
#include "k2000/logic/sound/CKStreamWave.h"
#include "k2000/graphical/system/IKVideo.h"
#include "k2000/logic/CKCinematicScene.h"
#include "k2000/logic/CKCinematicSceneData.h"
#include "k2000/hooks/IKHook.h"
#include "k2000/scenegraph/CSGMovable.h"
#include "Renderware/rwcore/RwCamera.h"
#include "k2000/logic/CKGameLevel.h"
#include "k2000/logic/CKGameSpawnPoint.h"
#include "k2000/logic/CKLevel.h"
#include "k2000/logic/io/CKLoadingManager.h"
#include "k2000/misc/CKGameLoop.h"
#include "k2000/system/CTimeManager.h"
#include "k2000/system/IKTime.h"
#include "k2000/misc/CoreSingletons.h"
#include "k2000/misc/Engine.h"
#include "k2000/managers/CKGraphic.h"
#include "k2000/misc/JobQueue.h"
#include "k2000/misc/IKCinematicElement.h"
#include "k2000/misc/IKGameStructure.h"
#include "k2000/logic/CKSekens.h"
#include "k2000/services/CKSrvCinematic.h"
#include "k2000/services/CKSrvSekensor.h"
#include <chrono>
#include "platform/cell/pad.h"
#include "platform/config.h"
#include "platform/gfx/device.h"
#include "platform/gfx/gl.h"
#include "platform/sdl/app.h"
#include "platform/sdl/freecam.h"
#include "Renderware/rpteam/RpTeam.h"
#include "k2000/graphical/CCloneManager.h"
#include "k2000/scenegraph/CClone.h"
#include "platform/video/bink.h"
// step 1 (the replay player, newgame_replay.inc)
#include <algorithm>
#include "crt/rand.h"
#include "platform/debug_symbols.h"
#include <thread>
#include "platform/cell/sys_time.h"
#include "Spyro2008/hooks/CKHkS08Hero.h"
#include "k2000/hooks/CKHkClimbZone.h"
#include "k2000/logic/CKSas.h"
#include "k2000/services/ICollisionMesh.h"
#include "k2000/hooks/CKHkCrumblyZone.h"
#include "k2000/logic/physics/CDynamicGround.h"
#include "k2000/logic/physics/CGround.h"
#include "k2000/services/CKSrvCollision.h"
#include "k2000/scenegraph/IKBoundingVolume.h"
#include "k2000/logic/CKSector.h"
#include "Spyro2008/groups/CKGrpS08Hero.h"
#include "Spyro2008/groups/IKGrpHero.h"
#include "k2000/animation/AnimBlendSlot.h"
#include "k2000/cameras/CameraContext.h"
#include "k2000/graphical/KBase98D.h"
#include "k2000/input/PS3PadDevice.h"
#include "k2000/managers/CKInput.h"
#include "k2000/sound/SpeechStreamModel.h"

namespace {
uint16_t g_d1 = 0, g_d2 = 0;
bool TestPad(int port, uint16_t words[24]) {
    if (port != 0) return false;
    std::memset(words, 0, 24 * sizeof(uint16_t));
    words[CELL_PAD_BTN_OFFSET_DIGITAL1] = g_d1;
    words[CELL_PAD_BTN_OFFSET_DIGITAL2] = g_d2;
    for (int i = CELL_PAD_BTN_OFFSET_ANALOG_RIGHT_X; i <= CELL_PAD_BTN_OFFSET_ANALOG_LEFT_Y; ++i) words[i] = 0x80;
    return true;
}
CKS08GameManager* M() { return static_cast<CKS08GameManager*>(g_pEngine->m_gameManager); }
int g_last = -1;
uint32_t g_frame = 0;
bool g_traceCine = false;

// C2.3 step 3: every scene that starts or stops and every element (bloc / door) that starts running or completes,
// with its class name and the frame (DOTD_CINE_TRACE=1), to compare the scenes after the video with the capture.
void TraceCinematics() {
    static uint32_t sceneFlags[64];
    static std::map<const IKCinematicElement*, uint32_t> elementFlags;
    if (g_pEngine->m_srvCinematic == nullptr) return;
    CKSrvCinematic* service = static_cast<CKSrvCinematic*>(g_pEngine->m_srvCinematic);
    for (uint32_t i = 0; i < service->m_ui32SceneNumber && i < 64; ++i) {
        const CKCinematicScene* scene = static_cast<CKCinematicScene*>(service->m_pSceneList[i]);
        if ((scene->m_baData & 0x41) != (sceneFlags[i] & 0x41)) {
            std::printf("cine: frame %u scene #%u flags %04x -> %04x\n", g_frame, i, sceneFlags[i], scene->m_baData);
            sceneFlags[i] = scene->m_baData;
        }
        for (uint32_t k = 0; k < scene->m_ui32CinematicPointerLength; ++k) {
            IKCinematicElement* e = static_cast<IKCinematicElement*>(scene->m_pCinematicPointerList[k]);
            const uint32_t now = e->m_DataFlags & 5;
            auto it = elementFlags.find(e);
            const uint32_t before = it == elementFlags.end() ? 0 : it->second;
            if (now != before) {
                if (e->IsKindOfClass(0x88c) == 0 || (now & 4) != 0)
                    std::printf("cine: frame %u scene #%u element %u %s flags %u -> %u\n", g_frame, i, k, typeid(*e).name(), before, now);
                elementFlags[e] = now;
            }
        }
    }
}
// DOTD_CINE_DUMP=1: every scene of the service with its elements (class, actor present).
void DumpScenes() {
    CKSrvCinematic* service = static_cast<CKSrvCinematic*>(g_pEngine->m_srvCinematic);
    for (uint32_t i = 0; i < service->m_ui32SceneNumber; ++i) {
        const CKCinematicScene* scene = static_cast<CKCinematicScene*>(service->m_pSceneList[i]);
        std::printf("dump: scene #%u sector %u flags %04x/%04x bands %02x first %s elements %u actors %u end %.2f start-of-chain %p\n", i,
                    scene->m_ui32SectorNum, scene->m_baData, scene->m_unk22, scene->m_baBlackBandData,
                    scene->m_pFirstBloc != nullptr ? typeid(*scene->m_pFirstBloc).name() : "-", scene->m_ui32CinematicPointerLength,
                    scene->m_ui32HookNumber, scene->m_fCameraEndTransitionTime, static_cast<const void*>(scene->m_unk78));
        for (uint32_t h = 0; h < (scene->m_ui32HookNumber & 0xffff); ++h) {
            const CKCinematicSceneData* sd = static_cast<const CKCinematicSceneData*>(scene->m_apCinematicSceneData[h]);
            std::printf("dump:   actor #%u.%u %s flags %02x interrupt %04x %04x %04x %04x\n", i, h,
                        sd->m_pHook != nullptr ? typeid(*sd->m_pHook).name() : "-", sd->m_DataFlags, sd->m_aUnk10[0], sd->m_aUnk10[1],
                        sd->m_aUnk10[2], sd->m_aUnk10[3]);
        }
        for (uint32_t k = 0; k < scene->m_ui32CinematicPointerLength; ++k) {
            IKCinematicElement* e = static_cast<IKCinematicElement*>(scene->m_pCinematicPointerList[k]);
            const CKCinematicSceneData* data = static_cast<const CKCinematicSceneData*>(e->m_pElementData);
            std::printf("dump:   #%u.%u %s flags %02x actor %s", i, k, typeid(*e).name(), e->m_DataFlags,
                        data == nullptr ? "-" : (data->m_pHook != nullptr ? "yes" : "MISSING"));
            if (e->IsKindOfClass(0x5c8) != 0 && static_cast<CKManageCameraCinematicBloc*>(e)->m_pCamera != nullptr)
                std::printf(" camera %s", typeid(*static_cast<CKManageCameraCinematicBloc*>(e)->m_pCamera).name());
            std::printf("\n");
            if (e->IsKindOfClass(0xc8) != 0 || e->IsKindOfClass(0x108) != 0) {
                const CKCinematicSceneData* sd = static_cast<const CKCinematicSceneData*>(e->m_pElementData);
                const uint32_t anim = e->IsKindOfClass(0xc8) != 0 ? static_cast<CKPlayAnimCinematicBloc*>(e)->m_ui32AnimChosen
                                                                  : static_cast<CKPathFindingCinematicBloc*>(e)->m_ui32AnimChosen;
                std::printf("dump:     anim index %u", anim);
                if (sd != nullptr && sd->m_pAnimDico != nullptr && anim != 0xffffffffu) {
                    const CAnimationDictionary* dict = static_cast<const CAnimationDictionary*>(sd->m_pAnimDico);
                    const uint32_t w = static_cast<uint32_t>(dict->m_apAnimations[anim]);
                    std::printf(" handle %08x", w);
                    CAnimationManager* mgr = static_cast<CAnimationManager*>(g_pEngine->m_animationManager);
                    if (w != 0xffffffffu && mgr != nullptr && (w >> 24) < mgr->m_ui32NbAnimations) {
                        CSectorAnimation* sec = static_cast<CSectorAnimation*>(mgr->m_apAnimations[w >> 24]);
                        if ((w & 0xffffff) < sec->m_ui32NbAnimations) {
                            const RtAnimAnimation* a = sec->m_apAnimations[w & 0xffffff];
                            std::printf(" duration %.3f (frames %d, scheme %d)", a->duration, a->numFrames, a->interpInfo->typeID);
                        }
                    }
                }
                std::printf(" playanim flags %02x\n", e->IsKindOfClass(0xc8) != 0 ? static_cast<CKPlayAnimCinematicBloc*>(e)->m_baPlayAnim : 0);
            }
            if (e->IsKindOfClass(0x508) != 0 && static_cast<CKSekensorCinematicBloc*>(e)->m_pSekens != nullptr) {
                const CKSekens* sk = static_cast<const CKSekens*>(static_cast<CKSekensorCinematicBloc*>(e)->m_pSekens);
                std::printf("dump:     sekens flags %08x lines %u delay %u order %u base %u stream %p wave %p", sk->m_flags,
                            sk->m_vBlocks.m_ui32NbUsedElt, sk->m_ui32DelayIndex, sk->m_ui32OrderMode, sk->m_unk68,
                            static_cast<const void*>(sk->m_pStreamObject),
                            sk->m_pStreamObject != nullptr ? static_cast<const void*>(sk->m_pStreamObject->m_pStreamWave) : nullptr);
                if (sk->m_pStreamObject != nullptr && sk->m_pStreamObject->m_pStreamWave != nullptr)
                    std::printf(" length %.3f path %s | %s", static_cast<const CKStreamWave*>(sk->m_pStreamObject->m_pStreamWave)->m_fStreamLength, static_cast<const CKStreamWave*>(sk->m_pStreamObject->m_pStreamWave)->m_szOriginalStreamPath, static_cast<const CKStreamWave*>(sk->m_pStreamObject->m_pStreamWave)->m_szFilePath);
                std::printf("\n");
                if (sk->m_pDataBuffers != nullptr) {
                    for (uint32_t n = 0; n < sk->m_pDataBuffers->m_count; ++n) {
                        float w0, w1;
                        std::memcpy(&w0, &sk->m_pDataBuffers->m_aWords0[n], 4);
                        std::memcpy(&w1, &sk->m_pDataBuffers->m_aWords1[n], 4);
                        std::printf("dump:       line %u w0 %.3f w1 %.3f byte %u\n", n, w0, w1, sk->m_pDataBuffers->m_aBytes[n]);
                    }
                }
            }
        }
    }
}
// C2.4 step 8: DOTD_NEWGAME_SHOT_ABS=<frame>,<frame>,... saves the frames with these loop frame numbers (g_frame, counted
// from the boot) as abs_<frame>.png into DOTD_NEWGAME_SHOTS, wherever the run is (the front end, the video, the scene).
const char* g_shotsDir = nullptr;
std::vector<uint32_t> g_absShots;
std::vector<uint32_t> ParseFrames(const char* list) {
    std::vector<uint32_t> frames;
    for (const char* p = list; p != nullptr && *p != 0;) {
        char* end = nullptr;
        const unsigned long value = std::strtoul(p, &end, 10);
        if (end == p) break;
        frames.push_back(static_cast<uint32_t>(value));
        p = *end == ',' ? end + 1 : end;
    }
    return frames;
}

// C2.5 step 3: DOTD_BONES_OUT=<file.json>:<moment>,<moment>,... writes every CAnimatedNode's bone matrices at the given
// moments of the in-engine scene: "video_end+N" (or just "N": N frames after the video's end), "control" (the frame
// the input is given back) and "control+N" (N frames after it). The JSON (format "dotd-bones-1";
// work/rpcs3_frame_capture.py --bones writes the same from
// RPCS3, work/bones_compare.py compares two files):
//   {"format": "dotd-bones-1", "source": "dotd", "build": "x86-parity" | "x64", "level": 10,
//    "frames": [{"moment": "video_end+1", "since_video_end": 1, "loop_frame": <n>, "render_frame": <the frame counter>,
//                "nodes": [{"id": "0x........", "num_nodes": <n>, "hierarchy_flags": <n>, "node_ids_crc": "0x........",
//                           "posed": 0 | 1, "controller": {...}, "ltm_pos": [x, y, z],
//                           "m": [[16 floats] x num_nodes]}, ...]}, ...]}
//   - "id" names the node the same on both sides: its KP3 object id, category | class index << 6 | instance << 17 (the
//     encoding CKLoadingManager_DecodeObjectId 0x27e68 decodes: the instance in the loading manager's array of the class;
//     CAnimatedNode is category 0xb, class 0x15). "node_ids_crc" (CRC-32 of the hierarchy's node ids as 32-bit
//     little-endian words) and "num_nodes" check the match; "ltm_pos" is the node frame's world position.
//   - "m": the hierarchy's matrix array (RpHAnimHierarchy +0x08, 0x40 bytes per node) as 16 floats per node in RwMatrix
//     order: right.xyz, w, up.xyz, w, at.xyz, w, pos.xyz, w. The w words are the matrix flags and pads (not floats, never
//     compared): written 0, 0, 0, 1 on both sides.
//   - "posed": a controller of the node was evaluated in this render frame (the root's vt+0x6c answers);
//     "controller": the node's controller tree (+0x30): a key frame controller {"anm": its evaluated animation as a
//     dictionary word (0xffffffff none), "time": +0x54, "t": +0x50, "flags": +0x08}, a blender {"w": +0x58, "flags",
//     "c": [first, second]}.
struct BonesMoment {
    std::string name;
    int32_t since = -1;  // frames after the video's end; -1 = the control frame
    int32_t afterControl = 0;  // "control+N": N frames after the control frame (since -1)
};
const char* g_bonesPath = nullptr;
std::vector<BonesMoment> g_bonesMoments;
std::FILE* g_bonesFile = nullptr;
int g_bonesWritten = 0;

void ParseBonesSpec(const char* spec) {
    if (spec == nullptr) return;
    static std::string s_path;
    const char* colon = std::strrchr(spec, ':');
    // A drive letter's colon is not the separator (C:\...): the list follows the last colon.
    if (colon == nullptr) return;
    s_path.assign(spec, colon);
    g_bonesPath = s_path.c_str();
    for (const char* p = colon + 1; *p != 0;) {
        const char* end = std::strchr(p, ',');
        std::string token(p, end != nullptr ? end : p + std::strlen(p));
        BonesMoment moment;
        moment.name = token;
        if (token == "control") {
            moment.since = -1;
        } else if (token.compare(0, 8, "control+") == 0) {
            moment.since = -1;
            moment.afterControl = std::atoi(token.c_str() + 8);
        } else {
            const std::string prefix = "video_end+";
            const std::string number = token.compare(0, prefix.size(), prefix) == 0 ? token.substr(prefix.size()) : token;
            moment.since = std::atoi(number.c_str());
            moment.name = "video_end+" + std::to_string(moment.since);
        }
        g_bonesMoments.push_back(moment);
        if (end == nullptr) break;
        p = end + 1;
    }
}

uint32_t Crc32(const uint8_t* data, size_t size, uint32_t crc = 0) {
    crc = ~crc;
    for (size_t i = 0; i < size; ++i) {
        crc ^= data[i];
        for (int k = 0; k < 8; ++k) crc = (crc >> 1) ^ (0xedb88320u & (0u - (crc & 1u)));
    }
    return ~crc;
}

// The KP3 object id of a loaded object (0xffffffff when its class record holds no array).
uint32_t Kp3ObjectId(const void* object, uint32_t key) {
    CKLoadingManager* database = g_pEngine->m_objectDatabase;
    if (database == nullptr || database->m_pTypeBundleLoad == nullptr) return 0xffffffffu;
    const uint32_t category = key & 0x3f;
    const uint32_t index = key >> 6;
    const CKIDBundleLoad* record = &database->m_pTypeBundleLoad[category].m_pID[index];
    if (record->m_ui8StreamType == CKIDBundleLoad::kGlobal || record->instances == nullptr || record->m_ui16SizeOfClass == 0) {
        return 0xffffffffu;
    }
    const uint8_t* base = static_cast<const uint8_t*>(record->instances);
    const uint8_t* at = static_cast<const uint8_t*>(object);
    if (at < base || (at - base) % record->m_ui16SizeOfClass != 0) return 0xffffffffu;
    const uint32_t instance = static_cast<uint32_t>((at - base) / record->m_ui16SizeOfClass);
    return category | (index << 6) | (instance << 17);
}

struct BonesContext {
    std::FILE* file;
    bool first;
    int nodes;
    int posed;
};

bool IsClass(IKSerializable* object, uint32_t key) {
    return object->GetClassType() == static_cast<int32_t>(key & 0x3f) && object->GetClassID() == static_cast<int32_t>(key >> 6);
}

// The controller tree: {"anm": word, "time": +0x54, "t": +0x50, "flags": +0x08} for a key frame controller, {"w": +0x58,
// "flags", "c": [first, second]} for a blender.
void WriteController(std::FILE* file, IKSerializable* object, int depth) {
    if (object == nullptr || depth > 6) {
        std::fputs("null", file);
        return;
    }
    if (IsClass(object, CKAnmKeyFrameController::kClassKey)) {
        CKAnmKeyFrameController* k = static_cast<CKAnmKeyFrameController*>(object);
        std::fprintf(file, "{\"anm\": \"0x%08x\", \"time\": %.9g, \"t\": %.9g, \"flags\": %u}", k->GetEvaluatedAnimWord(),
                     static_cast<double>(k->m_unk54), static_cast<double>(k->m_unk50), k->m_unk08);
    } else if (IsClass(object, CKBlenderController::kClassKey)) {
        CKBlenderController* b = static_cast<CKBlenderController*>(object);
        std::fprintf(file, "{\"w\": %.9g, \"flags\": %u, \"c\": [", static_cast<double>(b->m_unk58), b->m_unk08);
        WriteController(file, b->m_apControllers[0], depth + 1);
        std::fputs(", ", file);
        WriteController(file, b->m_apControllers[1], depth + 1);
        std::fputs("]}", file);
    } else {
        std::fputs("null", file);
    }
}

void WriteBonesNode(IKSerializable* object, uint32_t key, void* context) {
    if (key != CAnimatedNode::kClassKey) return;
    BonesContext& c = *static_cast<BonesContext*>(context);
    CAnimatedNode* node = static_cast<CAnimatedNode*>(object);
    const RpHAnimHierarchy* h = node->m_pRpHAnimHierarchy;
    if (h == nullptr || h->pMatrixArray == nullptr) return;
    std::vector<uint32_t> ids(static_cast<size_t>(h->numNodes));
    for (RwInt32 i = 0; i < h->numNodes; ++i) ids[static_cast<size_t>(i)] = static_cast<uint32_t>(h->pNodeInfo[i].nodeID);
    const uint32_t crc = Crc32(reinterpret_cast<const uint8_t*>(ids.data()), ids.size() * 4);
    KBase98D* root = static_cast<KBase98D*>(node->m_pController);
    const bool posed = root != nullptr && root->GetIfEvaluatedThisFrame() != nullptr;  // vt+0x6c
    const RwMatrix* ltm = RwFrameGetLTM(node->m_pRwFrame);
    std::fprintf(c.file, "%s\n    {\"id\": \"0x%08x\", \"num_nodes\": %d, \"hierarchy_flags\": %d, \"node_ids_crc\": \"0x%08x\", \"posed\": %d",
                 c.first ? "" : ",", Kp3ObjectId(object, key), h->numNodes, h->flags, crc, posed ? 1 : 0);
    if (root != nullptr) {
        std::fputs(", \"controller\": ", c.file);
        WriteController(c.file, root, 0);
    }
    std::fprintf(c.file, ", \"ltm_pos\": [%.9g, %.9g, %.9g], \"m\": [", static_cast<double>(ltm->pos.x),
                 static_cast<double>(ltm->pos.y), static_cast<double>(ltm->pos.z));
    for (RwInt32 i = 0; i < h->numNodes; ++i) {
        const RwMatrix& m = h->pMatrixArray[i];
        std::fprintf(c.file, "%s[%.9g, %.9g, %.9g, 0, %.9g, %.9g, %.9g, 0, %.9g, %.9g, %.9g, 0, %.9g, %.9g, %.9g, 1]", i == 0 ? "" : ", ",
                     static_cast<double>(m.right.x), static_cast<double>(m.right.y), static_cast<double>(m.right.z),
                     static_cast<double>(m.up.x), static_cast<double>(m.up.y), static_cast<double>(m.up.z),
                     static_cast<double>(m.at.x), static_cast<double>(m.at.y), static_cast<double>(m.at.z),
                     static_cast<double>(m.pos.x), static_cast<double>(m.pos.y), static_cast<double>(m.pos.z));
    }
    std::fputs("]}", c.file);
    c.first = false;
    ++c.nodes;
    if (posed) ++c.posed;
}

void WriteRetimedMoment(const BonesMoment& moment, uint32_t since);  // below (DOTD_BONES_POSE_FROM)

// Writes one moment (called right after the frame ran: its render traversal posed the nodes).
void WriteBonesMoment(const BonesMoment& moment, uint32_t since) {
    if (g_bonesFile == nullptr) {
        g_bonesFile = std::fopen(g_bonesPath, "wb");
        if (g_bonesFile == nullptr) {
            std::printf("bones: could not write %s\n", g_bonesPath);
            return;
        }
        std::fprintf(g_bonesFile, "{\"format\": \"dotd-bones-1\", \"source\": \"dotd\", \"build\": \"%s\", \"level\": 10, \"frames\": [",
                     sizeof(void*) == 4 ? "x86-parity" : "x64");
    }
    std::fprintf(g_bonesFile, "%s\n {\"moment\": \"%s\", \"since_video_end\": %u, \"loop_frame\": %u, \"render_frame\": %u, \"nodes\": [",
                 g_bonesWritten == 0 ? "" : ",", moment.name.c_str(), since, g_frame, static_cast<unsigned>(g_ui16RenderFrameCounter));
    BonesContext context{g_bonesFile, true, 0, 0};
    Kp3_ForEachLoadedObject(WriteBonesNode, &context);
    std::fputs("]}", g_bonesFile);
    ++g_bonesWritten;
    std::printf("bones: %s (+%u, loop frame %u): %d animated nodes with matrices, %d posed this frame\n", moment.name.c_str(), since,
                g_frame, context.nodes, context.posed);
    WriteRetimedMoment(moment, since);
}

// C2.5 step 4: DOTD_BONES_POSE_FROM=<pose spec> (written by `work/bones_compare.py --pose-spec` from an RPCS3 bones.json)
// gives, per moment, the controller trees of the nodes RPCS3 posed: "moment <name>", then "node <id> <tree>" lines, the
// tree in preorder: "K <word> <time>" a key frame controller (its evaluated animation and time +0x54), "B <w>" a blender
// followed by its two children, "N" none. After the moment's frame-aligned dump, each such node is posed again with the
// original's animation, time and blend weight put on its controllers (the per-frame path's posed branch,
// UpdateAnimatedNodePoseAndCull 0xcabc8: UpdateActiveState, Evaluate, RpHAnimHierarchyUpdateMatrices) and written as the
// moment "retimed:<name>". The original's animation time comes from its real-time frame clock, so the frame-aligned
// poses differ by the time difference; the retimed ones compare the interpolation, blending and matrices at the same
// time. The controllers' fields are put back afterwards.
struct PoseSpecNode {
    uint32_t id = 0;
    std::vector<std::string> tokens;
};
std::map<std::string, std::vector<PoseSpecNode>> g_poseSpec;

void ParsePoseSpec(const char* path) {
    if (path == nullptr) return;
    std::FILE* file = std::fopen(path, "rb");
    if (file == nullptr) {
        std::printf("bones: cannot open the pose spec %s\n", path);
        return;
    }
    std::string moment;
    char line[4096];
    while (std::fgets(line, sizeof line, file) != nullptr) {
        std::vector<std::string> words;
        for (char* token = std::strtok(line, " \t\r\n"); token != nullptr; token = std::strtok(nullptr, " \t\r\n")) words.push_back(token);
        if (words.size() >= 2 && words[0] == "moment") {
            moment = words[1];
        } else if (words.size() >= 3 && words[0] == "node" && !moment.empty()) {
            PoseSpecNode node;
            node.id = static_cast<uint32_t>(std::strtoul(words[1].c_str(), nullptr, 16));
            node.tokens.assign(words.begin() + 2, words.end());
            g_poseSpec[moment].push_back(node);
        }
    }
    std::fclose(file);
    std::printf("bones: pose spec %s: %zu moment(s)\n", path, g_poseSpec.size());
}

struct SavedController {
    KBase98D* controller;
    uint32_t flags;
    float time;              // a key frame controller's +0x50
    RtAnimAnimation* anim;   // its +0x58
    float weight;            // a blender's +0x58
};

// Puts the spec's tree on the controller tree; false (with the reason) when the classes differ.
bool ApplyPoseSpec(IKSerializable* object, const std::vector<std::string>& tokens, size_t& at, std::vector<SavedController>& saved,
                   std::string& why) {
    if (at >= tokens.size()) {
        why = "spec too short";
        return false;
    }
    const std::string kind = tokens[at++];
    if (kind == "N") return true;
    if (object == nullptr) {
        why = "no controller where the original has one";
        return false;
    }
    if (kind == "K") {
        if (!IsClass(object, CKAnmKeyFrameController::kClassKey) || at + 2 > tokens.size()) {
            why = "not a key frame controller";
            return false;
        }
        CKAnmKeyFrameController* k = static_cast<CKAnmKeyFrameController*>(object);
        saved.push_back({k, k->m_unk08, k->m_unk50, k->m_unk58, 0.0f});
        k->m_unk58 = CAnimationManager_GetAnimation(static_cast<uint32_t>(std::strtoul(tokens[at].c_str(), nullptr, 16)));
        k->m_unk50 = std::strtof(tokens[at + 1].c_str(), nullptr);
        at += 2;
        return true;
    }
    if (kind == "B") {
        if (!IsClass(object, CKBlenderController::kClassKey) || at + 1 > tokens.size()) {
            why = "not a blender";
            return false;
        }
        CKBlenderController* b = static_cast<CKBlenderController*>(object);
        saved.push_back({b, b->m_unk08, 0.0f, nullptr, b->m_unk58});
        b->m_unk58 = std::strtof(tokens[at].c_str(), nullptr);
        ++at;
        return ApplyPoseSpec(b->m_apControllers[0], tokens, at, saved, why) && ApplyPoseSpec(b->m_apControllers[1], tokens, at, saved, why);
    }
    why = "unknown spec token " + kind;
    return false;
}

struct FindNodeContext {
    uint32_t id;
    CAnimatedNode* found;
};
void FindNodeById(IKSerializable* object, uint32_t key, void* context) {
    FindNodeContext& c = *static_cast<FindNodeContext*>(context);
    if (key == CAnimatedNode::kClassKey && c.found == nullptr && Kp3ObjectId(object, key) == c.id) c.found = static_cast<CAnimatedNode*>(object);
}

void WriteRetimedMoment(const BonesMoment& moment, uint32_t since) {
    const auto spec = g_poseSpec.find(moment.name);
    if (spec == g_poseSpec.end() || g_bonesFile == nullptr) return;
    std::fprintf(g_bonesFile, ",\n {\"moment\": \"retimed:%s\", \"since_video_end\": %u, \"loop_frame\": %u, \"render_frame\": %u, \"nodes\": [",
                 moment.name.c_str(), since, g_frame, static_cast<unsigned>(g_ui16RenderFrameCounter));
    BonesContext context{g_bonesFile, true, 0, 0};
    // C2.5 step 5: DOTD_POSE_DRAW=1 (with DOTD_NEWGAME_SHOTS) keeps every spec node's controller state until all are
    // set, draws the frame once more (RenderGameFrame with the frame clock stopped, so no animation time advances and
    // the posed branch evaluates the original's times; the camera, lights and scene are this frame's) and saves it as
    // newgame_<since>_retimed.png: the pixel comparison of the skinned characters at the original's animation times.
    // The game state after that redraw is not the run's own any more: use it for the last shot of a run.
    const bool redraw = std::getenv("DOTD_POSE_DRAW") != nullptr && g_shotsDir != nullptr;
    std::vector<std::vector<SavedController>> kept;
    for (const PoseSpecNode& entry : spec->second) {
        FindNodeContext find{entry.id, nullptr};
        Kp3_ForEachLoadedObject(FindNodeById, &find);
        CAnimatedNode* node = find.found;
        if (node == nullptr || node->m_pRpHAnimHierarchy == nullptr || node->m_pController == nullptr) {
            std::printf("bones: retimed %s: node 0x%08x not found or without hierarchy / controller\n", moment.name.c_str(), entry.id);
            continue;
        }
        kept.emplace_back();
        std::vector<SavedController>& saved = kept.back();
        std::string why;
        size_t at = 0;
        const bool applied = ApplyPoseSpec(node->m_pController, entry.tokens, at, saved, why);
        KBase98D* root = static_cast<KBase98D*>(node->m_pController);
        if (applied) {
            // UpdateAnimatedNodePoseAndCull 0xcabc8's posed branch (the visibility test left out: the original posed it).
            root->UpdateActiveState();  // vt+0x68
            if ((root->m_unk08 & 0x10u) != 0) {
                uint32_t mask[4] = {0, 0, 0, 0};
                float weight = 0.0f;
                RpHAnimHierarchy* hierarchy = node->m_pRpHAnimHierarchy;
                RtAnimInterpolator* own = hierarchy->currentAnim;
                hierarchy->currentAnim = root->Evaluate(mask, &weight, 0);  // vt+0x64
                RpHAnimHierarchyUpdateMatrices(hierarchy);
                hierarchy->currentAnim = own;
            } else {
                std::printf("bones: retimed %s: node 0x%08x not to be evaluated with the original's controller state (flags 0x%x)\n",
                            moment.name.c_str(), entry.id, root->m_unk08);
            }
        } else {
            std::printf("bones: retimed %s: node 0x%08x: %s\n", moment.name.c_str(), entry.id, why.c_str());
        }
        WriteBonesNode(node, CAnimatedNode::kClassKey, &context);
    }
    if (redraw) {
        IKTime* clock = g_pCKGameLoop->m_timeManager->m_pTime;
        const int32_t state = clock->m_eCurrentState;
        clock->m_eCurrentState = 1;
        g_pCKGameLoop->m_renderer->RenderGameFrame(clock);
        clock->m_eCurrentState = state;
        char path[512];
        std::snprintf(path, sizeof path, "%s/newgame_%u_retimed.png", g_shotsDir, since);
        std::printf("shot: %s (the frame drawn again with the original's animation state)\n", path);
        dotd::gfx::SaveScreenshot(path);
    }
    for (std::vector<SavedController>& saved : kept) {
        for (auto it = saved.rbegin(); it != saved.rend(); ++it) {
            it->controller->m_unk08 = it->flags;
            if (IsClass(it->controller, CKAnmKeyFrameController::kClassKey)) {
                CKAnmKeyFrameController* k = static_cast<CKAnmKeyFrameController*>(it->controller);
                k->m_unk50 = it->time;
                k->m_unk58 = it->anim;
            } else {
                static_cast<CKBlenderController*>(it->controller)->m_unk58 = it->weight;
            }
        }
    }
    std::fputs("]}", g_bonesFile);
    std::printf("bones: retimed:%s: %d node(s) posed with the original's controller state\n", moment.name.c_str(), context.posed);
}

void FinishBones() {
    if (g_bonesFile == nullptr) return;
    std::fputs("\n]}\n", g_bonesFile);
    std::fclose(g_bonesFile);
    g_bonesFile = nullptr;
    std::printf("bones: %d moment(s) written to %s\n", g_bonesWritten, g_bonesPath);
}

// C2.5 step 6, DOTD_SHOW_CLONES=1: the level's clone nodes (CClone: static props the RpTeam draws; LVL010's one starts hidden, flag 4,
// as in the original, until a script shows it) are shown every frame and the place of each printed once. DOTD_SHOW_CLONES=2 also puts the
// free-fly camera at the offset DOTD_CLONE_CAM=dx,dy,dz (default 0,0.6,-1.8) from the first one's sphere centre, looking at it.
void ShowClones() {
    static const char* mode = std::getenv("DOTD_SHOW_CLONES");
    if (mode == nullptr) return;
    CCloneManager* manager = static_cast<CCloneManager*>(g_pEngine->m_graphic->m_renderer->m_cloneManager);
    if (manager == nullptr || manager->m_pRpTeam == nullptr) return;
    static bool announced = false;
    for (uint32_t i = 0; i < manager->m_ui32NbInstanceClones; ++i) {
        CClone* clone = static_cast<CClone*>(manager->m_vClones.m_pBlock[i]);
        clone->m_sgProperties &= ~4u;
        if (announced) continue;
        const RwMatrix* ltm = RwFrameGetLTM(clone->m_pRwFrame);
        const float* sphere = static_cast<const float*>(clone->m_pRwPlayerBSphere);
        std::printf("clone %u: at (%.2f, %.2f, %.2f), sphere (%.2f, %.2f, %.2f) r %.2f%s\n", i, ltm->pos.x, ltm->pos.y, ltm->pos.z, sphere[0], sphere[1],
                    sphere[2], sphere[3], (i == 0 && mode[0] == '2') ? ", free camera on it" : "");
        if (i == 0 && mode[0] == '2') {
            const float target[3] = {ltm->pos.x + sphere[0], ltm->pos.y + sphere[1], ltm->pos.z + sphere[2]};
            float offset[3] = {0.0f, 0.6f, -1.8f};
            if (const char* text = std::getenv("DOTD_CLONE_CAM")) std::sscanf(text, "%f,%f,%f", &offset[0], &offset[1], &offset[2]);
            const float eye[3] = {target[0] + offset[0], target[1] + offset[1], target[2] + offset[2]};
            const float yaw = std::atan2(-offset[0], -offset[2]) * 180.0f / 3.14159265f;  // yaw 0 looks along +z
            const float pitch = std::atan2(-offset[1], std::sqrt(offset[0] * offset[0] + offset[2] * offset[2])) * 180.0f / 3.14159265f;
            dotd::platform::freecam::SetPose(eye, yaw, pitch);
            dotd::platform::freecam::SetEnabled(true);
        }
    }
    announced = true;
}

#include "newgame_replay.inc"

void Step() {
    ShowClones();
    ReplayBeforeFrame(g_frame + 1);
    c15::RunFrame();
    ++g_frame;
    ReplayAfterFrame();
    if (g_shotsDir != nullptr) {
        for (uint32_t wanted : g_absShots) {
            if (wanted != g_frame) continue;
            char path[512];
            std::snprintf(path, sizeof path, "%s/abs_%u.png", g_shotsDir, g_frame);
            std::printf("shot: %s (loop frame %u, gfx frame %u, mode %d)\n", path, g_frame, dotd::gfx::FrameCount(), g_pCKGameLoop->m_mode);
            dotd::gfx::SaveScreenshot(path);
        }
    }
    if (g_traceCine) TraceCinematics();
    const int key = g_pCKGameLoop->m_mode * 1000 + M()->m_gameState.m_ui8Current;
    if (key != g_last) {
        std::printf("probe: frame %u mode %d state %d\n", g_frame, g_pCKGameLoop->m_mode, M()->m_gameState.m_ui8Current);
        std::fflush(stdout);
        g_last = key;
    }
}

// The scene of the service that plays, and its video bloc.
CKCinematicScene* PlayingScene(int* playing, int* first) {
    CKSrvCinematic* service = static_cast<CKSrvCinematic*>(g_pEngine->m_srvCinematic);
    CKCinematicScene* result = nullptr;
    *playing = 0;
    *first = -1;
    for (uint32_t i = 0; i < service->m_ui32SceneNumber; ++i) {
        CKCinematicScene* scene = static_cast<CKCinematicScene*>(service->m_pSceneList[i]);
        if ((scene->m_baData & 1) == 0) continue;
        if (result == nullptr) {
            result = scene;
            *first = static_cast<int>(i);
        }
        ++*playing;
    }
    return result;
}
CKPlayVideoCinematicBloc* VideoBlocOf(const CKCinematicScene* scene) {
    for (uint32_t i = 0; scene != nullptr && i < scene->m_ui32CinematicPointerLength; ++i) {
        IKCinematicElement* element = static_cast<IKCinematicElement*>(scene->m_pCinematicPointerList[i]);
        if (element->IsKindOfClass(0x888) != 0) return static_cast<CKPlayVideoCinematicBloc*>(element);
    }
    return nullptr;
}

// C2.3: the opening cutscene's state, as the original has it once the level started.
bool PrintSceneState(const char* when) {
    CKSrvCinematic* service = static_cast<CKSrvCinematic*>(g_pEngine->m_srvCinematic);
    int playing = 0;
    int first = -1;
    const CKCinematicScene* scene = PlayingScene(&playing, &first);
    std::printf("scene: %s: %d scene(s) playing, first #%d flags %04x/%04x bands %02x, input blocked %d, letterbox %d, blocking %u\n",
                when, playing, first, scene != nullptr ? scene->m_baData : 0, scene != nullptr ? scene->m_unk22 : 0,
                scene != nullptr ? scene->m_baBlackBandData : 0, M()->IsInputBlocked(), service->m_baData & 1,
                service->m_vpBlockingScenes.m_ui32NbUsedElt);
    return playing > 0 && M()->IsInputBlocked() != 0 && (service->m_baData & 1) != 0;
}
}  // namespace

int main() {
    std::setvbuf(stdout, nullptr, _IONBF, 0);
    dotd::platform::SetPadSource(&TestPad);
    // DOTD_NEWGAME_SHOTS=<directory> (C2.4 step 5): the run draws into a hidden window and saves the in-engine scene's frames
    // (newgame_<n>.png, n = frames since the video ended) for looking at: the world as the game's own cameras see it.
    const char* shotsDir = std::getenv("DOTD_NEWGAME_SHOTS");
    g_shotsDir = shotsDir;
    g_absShots = ParseFrames(std::getenv("DOTD_NEWGAME_SHOT_ABS"));
    // DOTD_NEWGAME_SHOT_FRAMES=<n>,<n>,...: the frames after the video's end to save (newgame_<n>.png; default below).
    const std::vector<uint32_t> relativeShots = ParseFrames(std::getenv("DOTD_NEWGAME_SHOT_FRAMES"));
    ParseBonesSpec(std::getenv("DOTD_BONES_OUT"));
    ParsePoseSpec(std::getenv("DOTD_BONES_POSE_FROM"));
    // step 1: DOTD_REPLAY=<rpcs3.rec> plays a recording of the original from the video's end (newgame_replay.inc).
    const char* replayPath = std::getenv("DOTD_REPLAY");
    const bool replay = replayPath != nullptr;
    if (replay && !LoadReplay(replayPath)) return 1;
    if (shotsDir != nullptr) {
        dotd::platform::Config& config = dotd::platform::MutableConfig();
        dotd::platform::LoadConfig(0, nullptr, config);
        config.hiddenWindow = true;
        config.vsync = false;
        config.frameRate = 0;
        if (!(dotd::platform::sdl::Init(config) && dotd::gfx::Init(1280, 720))) {
            std::printf("newgame: no OpenGL 3.3 device\n");
            return 77;
        }
    }
    if (!c15::BootToFrontEnd()) return 77;
    // DOTD_NO_POST=1 (C2.4 step 8, for before / after pictures): the graphic caps' post-effect bit 0x400 cleared, so
    // CPostRenderingFx / CKPBuffer draw nothing (the scene colour copy into the frame stays).
    if (std::getenv("DOTD_NO_POST") != nullptr) g_pEngine->m_graphic->m_baHardwareCaps &= ~0x400u;
    for (int i = 0; i < 3000 && M()->m_gameState.m_ui8Current != 5; ++i) Step();
    for (int i = 0; i < 60; ++i) Step();
    g_d1 = CELL_PAD_CTRL_START;
    for (int i = 0; i < 6; ++i) Step();
    g_d1 = 0;
    for (int i = 0; i < 600 && M()->m_gameState.m_ui8Current != 6; ++i) Step();
    for (int i = 0; i < 90; ++i) Step();
    // Through the menus as a player: main menu Cross (New game -> game menu), Cross (Start Story Mode -> start
    // player), Cross (Single Player).
    for (int k = 0; k < 6 && g_pCKGameLoop->m_mode == 5; ++k) {
        std::printf("probe: Cross in menu 0x%02x\n", M()->m_interfaceState.m_ui8Current);
        g_d2 = CELL_PAD_CTRL_CROSS;
        for (int i = 0; i < 4; ++i) Step();
        g_d2 = 0;
        for (int i = 0; i < 150 && g_pCKGameLoop->m_mode == 5; ++i) Step();
    }
    // The level start: mode 5 (gameplay) with the game state 7.
    for (int i = 0; i < 3000 && !(g_pCKGameLoop->m_mode == 5 && M()->m_gameState.m_ui8Current == 7); ++i) Step();
    int failures = 0;
    auto expect = [&failures](bool ok, const char* what) {
        if (!ok) {
            std::printf("newgame: FAIL %s\n", what);
            ++failures;
        }
    };
    const uint32_t levelStartFrame = g_frame;
    g_traceCine = std::getenv("DOTD_CINE_TRACE") != nullptr;
    if (std::getenv("DOTD_CINE_DUMP") != nullptr) DumpScenes();
    const bool sceneStarted = PrintSceneState("first mode-5 frame");
    expect(sceneStarted, "the opening scene started: playing, input blocked, letterbox shown");
    expect(g_pCKGameLoop->m_mode == 5, "loop mode 5 after the level start");
    expect(M()->m_gameState.m_ui8Current == 7, "game state 7 (in game)");

    // The opening video: the loop goes to modes 7 and 8 for it and returns to mode 5 when it ends (the start of the
    // video is the first frame in mode 8). The Bink header gives the video's own length.
    uint32_t modeEightFrame = 0;
    uint32_t modeFiveAgainFrame = 0;
    uint32_t binkFrames = 0, binkRate = 0, binkRateDiv = 0;
    const IKVideo* video = nullptr;
    {
        int playing = 0, first = -1;
        const CKPlayVideoCinematicBloc* bloc = VideoBlocOf(PlayingScene(&playing, &first));
        if (bloc != nullptr && bloc->m_vpVideoCount != 0) video = static_cast<const IKVideo*>(bloc->m_vpVideo[0]);
        if (video != nullptr) std::printf("scene: the video bloc plays %s\n", video->m_szFileName);
    }
    // The video's sekens (subtitles): the lines it goes through.
    CKSekens* sekens = nullptr;
    int32_t lastLine = -2;
    uint32_t lineChanges = 0;
    {
        int playing = 0, first = -1;
        const CKPlayVideoCinematicBloc* bloc = VideoBlocOf(PlayingScene(&playing, &first));
        if (bloc != nullptr && bloc->m_vpVideoCount != 0 && bloc->m_vi32SekIndex[0] != -1)
            sekens = static_cast<CKSrvSekensor*>(g_pEngine->m_srvSekensor)->GetSekens(static_cast<uint32_t>(bloc->m_vi32SekIndex[0]));
    }
    // DOTD_NEWGAME_SKIP=1: START during the video opens the skip prompt, Left + Cross answers yes, the video ends early.
    const bool skipTest = std::getenv("DOTD_NEWGAME_SKIP") != nullptr || replay;  // a replay is recorded with the video skipped
    uint32_t skipPhaseFrame = 0;
    int skipPhase = 0;
    for (int i = 0; i < 40000; ++i) {
        Step();
        if (skipTest && modeEightFrame != 0) {
            const uint32_t since = g_frame - modeEightFrame;
            CKSrvCinematic* srv = static_cast<CKSrvCinematic*>(g_pEngine->m_srvCinematic);
            if (skipPhase == 0 && since == 300) { g_d1 = CELL_PAD_CTRL_START; skipPhase = 1; skipPhaseFrame = g_frame; }
            else if (skipPhase == 1 && g_frame - skipPhaseFrame == 4) {
                g_d1 = 0;
                skipPhase = 2;
                skipPhaseFrame = g_frame;
                std::printf("skip: START pressed at frame %u: prompt open %d, message boxes queued %d\n", g_frame, (srv->m_baData >> 2) & 1, MessageBox_GetQueuedCount());
            } else if (skipPhase == 2 && g_frame - skipPhaseFrame == 120) { g_d1 = CELL_PAD_CTRL_LEFT; skipPhase = 3; skipPhaseFrame = g_frame; }
            else if (skipPhase == 3 && g_frame - skipPhaseFrame == 4) { g_d1 = 0; g_d2 = CELL_PAD_CTRL_CROSS; skipPhase = 4; skipPhaseFrame = g_frame; }
            else if (skipPhase == 4 && g_frame - skipPhaseFrame == 4) { g_d2 = 0; skipPhase = 5; skipPhaseFrame = g_frame; }
            else if (skipPhase == 5 && g_frame - skipPhaseFrame == 20)
                std::printf("skip: 20 frames after the answer: mode %d, prompt open %d, queued %d, video state %d\n", g_pCKGameLoop->m_mode, (srv->m_baData >> 2) & 1, MessageBox_GetQueuedCount(), video != nullptr ? video->m_state : -1);
        }
        if (sekens != nullptr && sekens->m_i32CurrentLine != lastLine) {
            lastLine = sekens->m_i32CurrentLine;
            ++lineChanges;
            if (lineChanges <= 3 || lastLine == -1)
                std::printf("subtitles: frame %u line %d of %u\n", g_frame, lastLine, sekens->m_vBlocks.m_ui32NbUsedElt);
        }
        if (g_pCKGameLoop->m_mode == 8 && modeEightFrame == 0) modeEightFrame = g_frame;
        if (modeEightFrame != 0 && binkFrames == 0 && video != nullptr && video->m_pBink != nullptr) {
            binkFrames = video->m_pBink->Frames;
            binkRate = video->m_pBink->FrameRate;
            binkRateDiv = video->m_pBink->FrameRateDiv;
        }
        if (modeEightFrame != 0 && g_pCKGameLoop->m_mode == 5) {
            modeFiveAgainFrame = g_frame;
            break;
        }
    }
    expect(modeEightFrame != 0 && modeFiveAgainFrame != 0, "the opening video played: mode 8 and then mode 5 again");
    if (replay && modeFiveAgainFrame != 0) StartReplay(modeFiveAgainFrame);
    if (modeEightFrame != 0 && modeFiveAgainFrame != 0 && binkRate != 0) {
        // Frames from the first frame in mode 8 to the one before the return to mode 5, against the video's own length
        // (Bink frames x FrameRateDiv / FrameRate seconds at 60 Hz). The clean RPCS3 capture measured 12263 (1144 -> 13407).
        const uint32_t measured = modeFiveAgainFrame - 1 - modeEightFrame;
        const double expected = static_cast<double>(binkFrames) * binkRateDiv / binkRate * 60.0;
        std::printf("video: %u Bink frames at %u/%u = %.3f s = %.2f loop frames expected; level start frame %u, mode 8 at %u, mode 5 again at %u, measured %u\n",
                    binkFrames, binkRate, binkRateDiv, static_cast<double>(binkFrames) * binkRateDiv / binkRate, expected,
                    levelStartFrame, modeEightFrame, modeFiveAgainFrame, measured);
        if (!skipTest) {
            expect(static_cast<double>(measured) >= expected - 1.5 && static_cast<double>(measured) <= expected + 1.5,
                   "the video's frames in mode 8 equal its Bink length at 60 Hz (within one frame)");
        } else {
            expect(static_cast<double>(measured) < expected - 1000.0, "the skipped video ended early");
        }
    }
    std::printf("subtitles: %u line change(s) during the video, the sekens %s\n", lineChanges,
                sekens != nullptr ? "exists" : "is missing");
    expect(sekens != nullptr && lineChanges >= 2, "the video's subtitle lines advanced");
    if (!skipTest) expect(lineChanges >= 50, "the video's subtitle lines went through the whole sekens");
    PrintSceneState("after the video");
    // C2.3 step 3: the in-engine part of the opening cutscene. The frames are counted from the first mode-5 frame after the
    // video (the capture's 13408): the scene that starts then (LVL010's #13: teleports, the sekensor's line, cameras, the walk
    // to the targets, the events) has its sekensor bloc done at +255 (13663), its first path-finding bloc at +336
    // (13744) and ends at +558 (13966, SwitchToFocusedHeroCamera): the input given back, the bars off a transition later.
    // The capture ran at about 59.83 Hz: the 558 frames are 9.3 s there, so two frames of slack.
    {
        CKSrvCinematic* service = static_cast<CKSrvCinematic*>(g_pEngine->m_srvCinematic);
        const uint32_t videoEnd = modeFiveAgainFrame != 0 ? modeFiveAgainFrame : g_frame;
        int inEngine = -1;
        bool inputWasBlocked = false;
        // C2.3 step 4, DOTD_NEWGAME_SKIP2=1: START 150 frames into the in-engine scene opens the skip prompt (the game loop is
        // inhibited), Left + Cross answers yes, and the scene must end at once with the state the watched run ends in.
        const bool skipScene = std::getenv("DOTD_NEWGAME_SKIP2") != nullptr;
        int scenePhase = 0;
        uint32_t scenePhaseFrame = 0, promptOpenFrame = 0, answerFrame = 0;
        int inhibitAtPrompt = -1, pauseState = -1;
        uint32_t sekensorFrame = 0, pathFrame = 0, controlFrame = 0, barsFrame = 0, endedFrame = 0;
        // A replay runs to the recording's last frame.
        for (int i = 0; replay ? !ReplayOver() : i < 1500; ++i) {
            Step();
            if (inEngine < 0) {
                for (uint32_t s = 0; s < service->m_ui32SceneNumber; ++s) {
                    const CKCinematicScene* scene = static_cast<CKCinematicScene*>(service->m_pSceneList[s]);
                    if ((scene->m_baData & 1) != 0 && (scene->m_baData & 0x40) == 0 && scene->m_ui32CinematicPointerLength > 10) {
                        inEngine = static_cast<int>(s);
                        std::printf("cinematic: the in-engine scene is #%d, started %u frame(s) after the video, flags +0x22 0x%x\n", inEngine, g_frame - videoEnd, scene->m_unk22);
                        break;
                    }
                }
            }
            if (inEngine < 0) continue;
            if (shotsDir != nullptr) {
                static auto s_start = std::chrono::steady_clock::now();
                static const std::vector<uint32_t> kDefaultShots = {1, 30, 90, 150, 220, 300, 380, 450, 520, 560, 600, 700};
                const std::vector<uint32_t>& shots = relativeShots.empty() ? kDefaultShots : relativeShots;
                const uint32_t since = g_frame - videoEnd;
                for (uint32_t wanted : shots) {
                    if (since == wanted) {
                        const double ms = std::chrono::duration<double, std::milli>(std::chrono::steady_clock::now() - s_start).count();
                        std::printf("frames: %u frames in %.0f ms = %.2f ms per frame (loop + draw, no vsync, this build)\n", since, ms, ms / since);
                        char path[512];
                        std::snprintf(path, sizeof path, "%s/newgame_%u.png", shotsDir, since);
                        std::printf("shot: %s at gfx frame %u, loop frame %u\n", path, dotd::gfx::FrameCount(), g_frame);
                        dotd::gfx::SaveScreenshot(path);
                        const unsigned glError = dotd::gfx::gl::glGetError();
                        std::printf("gl: error 0x%x after the frame\n", glError);
                        expect(glError == 0, "no GL error while the world is drawn");
                    }
                }
            }
            for (const BonesMoment& moment : g_bonesMoments) {
                if (moment.since >= 0 && g_frame - videoEnd == static_cast<uint32_t>(moment.since)) WriteBonesMoment(moment, g_frame - videoEnd);
                if (moment.afterControl > 0 && controlFrame != 0 && g_frame - controlFrame == static_cast<uint32_t>(moment.afterControl))
                    WriteBonesMoment(moment, g_frame - videoEnd);
            }
            const CKCinematicScene* scene = static_cast<CKCinematicScene*>(service->m_pSceneList[inEngine]);
            if (skipScene) {
                const uint32_t since = g_frame - videoEnd;
                if (scenePhase == 0 && since == 150) { g_d1 = CELL_PAD_CTRL_START; scenePhase = 1; scenePhaseFrame = g_frame; }
                else if (scenePhase == 1 && g_frame - scenePhaseFrame == 4) { g_d1 = 0; scenePhase = 2; scenePhaseFrame = g_frame; }
                else if (scenePhase == 2 && g_frame - scenePhaseFrame == 20) {
                    promptOpenFrame = g_frame;
                    inhibitAtPrompt = g_pCKGameLoop->m_inhibitCount;
                    std::printf("skip: START pressed during the scene: queued boxes %d, game loop inhibited %d, scene still playing %d, game state %d\n",
                                MessageBox_GetQueuedCount(), inhibitAtPrompt, scene->m_baData & 1, M()->m_gameState.m_ui8Current);
                    pauseState = M()->m_gameState.m_ui8Current;
                    scenePhase = 3;
                    scenePhaseFrame = g_frame;
                }
            }
            for (uint32_t k = 0; k < scene->m_ui32CinematicPointerLength; ++k) {
                IKCinematicElement* element = static_cast<IKCinematicElement*>(scene->m_pCinematicPointerList[k]);
                if ((element->m_DataFlags & 4) == 0) continue;
                if (sekensorFrame == 0 && element->IsKindOfClass(0x508) != 0) sekensorFrame = g_frame;
                if (pathFrame == 0 && element->IsKindOfClass(0x108) != 0) pathFrame = g_frame;
            }
            if (M()->IsInputBlocked() != 0) inputWasBlocked = true;
            else if (inputWasBlocked && controlFrame == 0) {
                controlFrame = g_frame;
                g_replayControlSeen = static_cast<int32_t>(g_frame - videoEnd);
                for (const BonesMoment& moment : g_bonesMoments) {
                    if (moment.since < 0 && moment.afterControl == 0) WriteBonesMoment(moment, g_frame - videoEnd);
                }
                // C2.4 exit: the frame control is given (the RPCS3 capture's moment "control") as newgame_control.png.
                if (shotsDir != nullptr) {
                    char path[512];
                    std::snprintf(path, sizeof path, "%s/newgame_control.png", shotsDir);
                    std::printf("shot: %s (control, +%u after the video) at gfx frame %u, loop frame %u\n", path, g_frame - videoEnd,
                                dotd::gfx::FrameCount(), g_frame);
                    dotd::gfx::SaveScreenshot(path);
                }
            }
            if (controlFrame != 0 && barsFrame == 0 && (service->m_baData & 1) == 0) barsFrame = g_frame;
            if (controlFrame != 0 && endedFrame == 0 && (scene->m_baData & 1) == 0) endedFrame = g_frame;
        }
        std::printf("cinematic: after the video (frame %u): sekensor done +%d, first path bloc done +%d, control given +%d, bars off +%d, scene over +%d\n",
                    videoEnd, static_cast<int>(sekensorFrame - videoEnd), static_cast<int>(pathFrame - videoEnd),
                    static_cast<int>(controlFrame - videoEnd), static_cast<int>(barsFrame - videoEnd), static_cast<int>(endedFrame - videoEnd));
        // C2.7: after the scene the first fight's intro (scene #16) starts the tutorial pages (CKS08MenuPauseInfo, interface
        // state 0x10) with the slow motion down to 0 and the heroes' input blocked, as the original (the idle recordings
        // stay there until a button is pressed).
        auto introHoldsInput = [&]() {
            return barsFrame != 0 && endedFrame != 0 && (service->m_baData & 1) == 0 && M()->IsInputBlocked() != 0 &&
                   M()->m_interfaceState.m_ui8Current == 0x10 && g_pEngine->m_timeManager->m_fTimeScale == 0.0f;
        };
        auto within = [](uint32_t frame, uint32_t base, int expected) {
            const int measured = static_cast<int>(frame - base);
            return frame != 0 && measured >= expected - 2 && measured <= expected + 2;
        };
        if (replay) {
            // The original's frame times: the scene's milestones come when they came in the recording.
            std::printf("replay: control +%d, recorded +%d\n", static_cast<int>(controlFrame - videoEnd), g_replayControl);
            expect(controlFrame != 0 && static_cast<int32_t>(controlFrame - videoEnd) == g_replayControl,
                   "the replay gives control on the recording's frame");
            expect(introHoldsInput(), "the scene is over and the first fight's intro holds the input in the tutorial pages");
        } else if (skipScene) {
            // The in-engine scene's flag +0x22 bit 4 is clear: it cannot be skipped, so START is the pause request (state 8)
            // and the skip prompt stays closed (CKS08GameManager_CheckPauseRequest_maybe).
            expect(promptOpenFrame != 0 && MessageBox_GetQueuedCount() == 0 && inhibitAtPrompt == 0,
                   "START during the in-engine scene opened no skip prompt");
            expect(pauseState == 8, "START during the unskippable in-engine scene switched to the pause state 8");
        } else if (!skipTest) {
            expect(inEngine >= 0, "the in-engine scene started after the video");
            expect(within(sekensorFrame, videoEnd, 255), "the sekensor bloc is done 255 frames after the video (capture 13408 -> 13663)");
            expect(within(pathFrame, videoEnd, 336), "the first path bloc is done 336 frames after the video (capture 13408 -> 13744)");
            expect(within(controlFrame, videoEnd, 558), "the player gets control 558 frames after the video (capture 13408 -> 13966)");
            expect(introHoldsInput(), "the scene is over and the first fight's intro holds the input in the tutorial pages");
        } else {
            // The video skipped: the scene's follow-up (the in-engine part) starts at once, a few frames before the watched
            // video's end sequence would start it, and then takes as long: same spans between its milestones (measured 251 /
            // 332 / 554 after the video's end against 255 / 336 / 558).
            expect(within(sekensorFrame, videoEnd, 251) && within(pathFrame, videoEnd, 332) && within(controlFrame, videoEnd, 554),
                   "the skipped video leads into the same in-engine scene (its milestones 4 frames before the watched run's)");
            expect(introHoldsInput(), "the scene is over and the first fight's intro holds the input in the tutorial pages");
        }
    }
    PrintSceneState("1500 frames after the video");
    expect(g_pCKGameLoop->m_mode == 5, "loop mode 5 after the video");
    if (std::getenv("DOTD_NEWGAME_SKIP2") == nullptr) expect(M()->m_gameState.m_ui8Current == 7, "game state 7 after the video");
    {
        // The state the scene leaves: the same after watching it and after skipping the video into it.
        const float* hero = M()->GetFocusedHeroNodePosition();
        // The scene's actors (the hero, the NPCs it walks and teleports): where they stand and face.
        // The scene's blocs put them on their marks, so skipping the video into it ends on the same ones.
        int actorMismatch = 0;
        {
            CKSrvCinematic* service = static_cast<CKSrvCinematic*>(g_pEngine->m_srvCinematic);
            for (uint32_t s = 0; s < service->m_ui32SceneNumber; ++s) {
                const CKCinematicScene* scene = static_cast<CKCinematicScene*>(service->m_pSceneList[s]);
                if (scene->m_ui32CinematicPointerLength <= 10) continue;
                for (uint32_t h = 0; h < (scene->m_ui32HookNumber & 0xffff); ++h) {
                    const CKCinematicSceneData* sd = static_cast<const CKCinematicSceneData*>(scene->m_apCinematicSceneData[h]);
                    if (sd->m_pHook == nullptr) continue;
                    const CSGMovable* node = static_cast<const CSGMovable*>(static_cast<IKHook*>(sd->m_pHook)->m_pKGLObject);
                    if (node == nullptr || node->m_pRwFrame == nullptr) continue;
                    const RwFrame* frame = node->m_pRwFrame;
                    const float v[6] = {frame->modelling.pos.x, frame->modelling.pos.y, frame->modelling.pos.z,
                                        frame->modelling.at.x, frame->modelling.at.y, frame->modelling.at.z};
                    if (s == 13 && h < 7) {
                        // Where the in-engine scene (#13) leaves its seven actors: the first stays on its teleport mark, the
                        // second walked to its target on the ground (it varies by about 1e-4 with the frame clock; RPCS3
                        // (-49.8398, 33.8373, 426.747)), the five others stand in the crowd. The same after watching the scene
                        // and after skipping the video into it.
                        static const float kMarks[7][3] = {{-69.0f, 36.0f, 426.0f}, {-49.8404f, 33.8373f, 426.747f}, {-56.0f, 34.001f, 425.0f},
                                                           {-55.0f, 34.001f, 426.0f}, {-54.0f, 34.001f, 425.0f}, {-53.0f, 34.001f, 426.0f},
                                                           {-52.0f, 34.001f, 425.0f}};
                        for (int c = 0; c < 3; ++c) {
                            if (std::fabs(v[c] - kMarks[h][c]) > 0.01f) {
                                std::printf("end state: actor %u coordinate %d is %.4f, expected %.4f\n", h, c, v[c], kMarks[h][c]);
                                ++actorMismatch;
                            }
                        }
                    }
                    std::printf("end state: scene #%u actor %u %s pos (%.9g, %.9g, %.9g) at (%.9g, %.9g, %.9g)\n", s, h,
                                typeid(*sd->m_pHook).name(), v[0], v[1], v[2], v[3], v[4], v[5]);
                }
            }
        }
        expect(actorMismatch == 0, "the in-engine scene left its actors on their marks");
        std::printf("end state: hero node (%.3f, %.3f, %.3f), input blocked %d, game loop inhibited %d, queued boxes %d, game state %d\n",
                    hero[0], hero[1], hero[2], M()->IsInputBlocked(), g_pCKGameLoop->m_inhibitCount, MessageBox_GetQueuedCount(),
                    M()->m_gameState.m_ui8Current);
    }
    IKGameStructure* structure = static_cast<IKGameStructure*>(M()->m_gameStructure);
    expect(structure->m_pCurrentSpawnPoint != nullptr &&
               g_pEngine->m_level->m_currentSector == structure->m_pCurrentSpawnPoint->m_iSectorIndex,
           "the current sector is the spawn point's sector");
    if (const char* pattern = std::getenv("DOTD_DUMP_LEVEL_OBJECTS")) {
        char path[512];
        std::snprintf(path, sizeof(path), pattern, 10);
        if (!Kp3_DumpObjects(path)) std::printf("newgame: could not write %s\n", path);
    }
    FinishBones();
    if (replay) failures += FinishReplay(g_replayControlSeen);
    if (std::getenv("DOTD_SHOW_CLONES") != nullptr) {
        // C2.5 step 6: the shown clone went through the team's render (CClone queued, the manager's players switched on, RpTeamRender).
        std::printf("clone: %u element atomic(s) went through the team's render\n", RpTeamDrawnAtomics());
        expect(RpTeamDrawnAtomics() > 0, "a shown clone node is drawn by the team (CClone -> CCloneManager -> RpTeamRender)");
    }
    std::printf("probe: %d frames in total, mode %d state %d, %d failure(s)\n", static_cast<int>(g_frame),
                g_pCKGameLoop->m_mode, M()->m_gameState.m_ui8Current, failures);
    // The load threads of the engine are still running (joinable std::thread objects): leave without the
    // static destructors, which would abort.
    std::fflush(stdout);
    std::_Exit(failures != 0 ? 1 : 0);
}
