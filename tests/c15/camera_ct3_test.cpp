// camera_ct3_test - step 5: the third-person follow track (CKCameraClassicTrack3) against the original. In the idle
// recording the track runs one frame at control: Start (vt+0x50, from the cinematic camera's axes) and one Update
// (a zero-length blend to the zone's pose). The live census taken at control (outputs/remake/census
// objects-lvl010_ingame-20261018-223707) holds the track, its zone and the camera service after that frame; the test
// sets the service and the zone up from it, runs Start + Update and compares the track's fields with the live ones.
#include <cmath>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>

#include "Spyro2008/logic/CKS08GameManager.h"
#include "boot_helper.h"
#include "k2000/cameras/CKCameraClassicTrack3.h"
#include "k2000/cameras/CKSrvCamera.h"
#include "k2000/cameras/CameraContext.h"
#include "k2000/logic/CKGameLevel.h"
#include "k2000/logic/CKGameSpawnPoint.h"
#include "k2000/logic/CKLevel.h"
#include "k2000/logic/CKSector.h"
#include "k2000/logic/cameras/CKCameraConstraint.h"
#include "k2000/misc/CKGameLoop.h"
#include "k2000/misc/CoreSingletons.h"
#include "k2000/misc/Engine.h"
#include "k2000/misc/IKGameStructure.h"

namespace {

constexpr float kRadiusFactor = 1.0f;

const uint32_t kLiveTrack[198] = {
    0x00b1aa50, 0x00000000, 0x00003000, 0x00cf533b, 0x02020000, 0x43160000, 0x42a00000, 0x42a00000,
    0x40d9c1dc, 0x4202275f, 0x43d56667, 0x3fd9999a, 0x41fe9168, 0x43d56667, 0x33f9f84c, 0x00ae0100,
    0x00000001, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x3f800000,
    0x3f5f66f1, 0x3f860a91, 0x40a00000, 0x41a00000, 0x43480000, 0x41200000, 0x41000000, 0x3f800000,
    0x41400000, 0x40400000, 0x3f800000, 0x41c80000, 0x40a00000, 0x41200000, 0x40a00000, 0x42960000,
    0x40800000, 0x40f00000, 0x3fc00000, 0x00000000, 0x00000000, 0x00000000, 0xbf1c61a9, 0x3f91361d,
    0x3f32b8c1, 0x3fbde44d, 0x408e6b3a, 0x3edf66f1, 0x40800000, 0x41200000, 0x40400000, 0x40060a91,
    0x3fb2b8c1, 0x40060a91, 0x00040000, 0x3f5f66f1, 0x3f860a91, 0x40c90fdb, 0x3e0efa34, 0x00000000,
    0x3e0efa34, 0x00000000, 0x3e0efa34, 0xbe2122a4, 0x7f7fffff, 0xff7fffff, 0x7f7fffff, 0x00000000,
    0x00000000, 0x40a3a293, 0x00000001, 0x00000000, 0xbf7d8235, 0xbe0e8367, 0x00000000, 0x3f7d8237,
    0x3e0e8356, 0x80000000, 0xc1239c5a, 0xbf7d8237, 0xbe0e8356, 0x00000000, 0xc15c63aa, 0x3f3d02fa,
    0x3dd482ad, 0x3f2a9a0e, 0xc39265bd, 0x3f3d02fa, 0x3dd482ad, 0xbf2a9a0e, 0x438a071a, 0x3ed1be72,
    0x3f698890, 0x80000000, 0xc201cb37, 0x3f252e0b, 0xbf439488, 0x00000000, 0x41a3ebfc, 0x00000000,
    0x00000000, 0x3e0efa34, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x3f800000, 0x3f800000, 0x32d3c594, 0x00000000,
    0x00000000, 0x00000000, 0x7f7fffff, 0x00000000, 0xffffffff, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x000003e8, 0x00002901, 0x00002901, 0x00002901, 0x00000000, 0x3f800000,
    0x00001909, 0x00000000, 0x00000203, 0x00000000, 0xbf7fffff, 0x00000000, 0x3496cbe4, 0x3fd9999a,
    0x41fe9168, 0x43d56667, 0x3cac2171, 0xbf800000, 0x00000000, 0x00000000, 0x40a3a293, 0x3e0efa34,
    0x4095e38c, 0x3fd9999a, 0x41fe9168, 0x43d56667, 0x40a4f673, 0x3e0efa34, 0x4096cbe5, 0x3fd9999a,
    0x41fe9168, 0x43d56667, 0x40a4f673, 0x3e0efa34, 0x4096cbe5, 0x3fd9999a, 0x41fe9168, 0x43d56667,
    0x00000000, 0x80000000, 0x3f800000, 0x42200000, 0x42a00000, 0x43200000, 0x42a00000, 0x00000000,
    0x42a00000, 0x00000000, 0xbf800000, 0xbf800000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x42c80000, 0x42c80000, 0x42c80000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
};

const uint32_t kLiveZone[40] = {
    0x00b130a0, 0x41c00000, 0x42480000, 0x43de2000, 0xc1c00000, 0x41a60000, 0x43c58000, 0x2763b63c,
    0x00000102, 0x00000001, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x02636c30, 0x00000000,
    0x00000000, 0x3fc90fd9, 0x00000000, 0x00000000, 0x3f800000, 0x3f800000, 0x3f800000, 0x3f800000,
    0x405f66f1, 0x3fdf66f1, 0x405f66f1, 0x00000000, 0x00000000, 0x00000000, 0xbf800000, 0x00000000,
    0x3eb2b8c1, 0x3f060a91, 0x3f060a91, 0xffffffff, 0x00000000, 0x00000000, 0x00000000, 0xff636fb4,
};

const uint32_t kLiveServiceFov[3] = {
    0x42200000, 0x43200000, 0x42a00000,
};

const uint32_t kLiveServiceAxes[9] = {
    0xbce850a6, 0x00000000, 0x3f7fe5a4, 0xbe74bfcf, 0x3f7892f9, 0xbbde31cf, 0xbf787962, 0xbe74d905,
    0xbce19382,
};

const uint32_t kLiveStack0[12] = {
    0x32decdac, 0x0101646c, 0xbf800000, 0x00616e2e, 0x40200000, 0x3f800000, 0x3f800000, 0x3fc00000,
    0xbf800000, 0x3fd9999a, 0x41f0020c, 0x43d56667,
};

const uint32_t kLiveRecords[20] = {
    0x400f5c29, 0x3e8b3965, 0x3f800000, 0x3f800000, 0x3f000000, 0x3fe8f5c3, 0x3e0efa34, 0x3f800000,
    0x3fe00000, 0x3f000000, 0x3f000000, 0x3dd6774e, 0x40000000, 0x40400000, 0x3f000000, 0x00000000,
    0x3edf66f1, 0x3f800000, 0x3f800000, 0x3f000000,
};


// The game state the track saw in that frame: the camera service's focus target (the hero, stack entry 0 and its
// record), the fov approach parameters, the real axes (the cinematic camera's), the constraint zone.
float F(uint32_t word) { return IKCamera::AsFloat(word); }

struct Field {
    uint32_t offset;
    const char* name;
};
// The fields the track's code writes in Start + the first Update: the CT3 family's, then the COLL family's (the pitch
// limits of the ground clearance, the volume follow state, the obstruction turn, the obstruction hit, the ground point).
// The wall hit (+0x1f8..+0x22f) and +0x128 are left out: not written in that frame (the live words are stale memory).
const Field kChecked[] = {
    {0x20, "position.x"}, {0x24, "position.y"}, {0x28, "position.z"}, {0x2c, "target.x"}, {0x30, "target.y"},
    {0x34, "target.z"}, {0xe8, "track flags"}, {0xec, "pitch.accel"}, {0xf0, "pitch.decel"}, {0xf4, "pitch.max"},
    {0xf8, "pitch.current"}, {0x100, "pitch.target"}, {0x108, "desired pitch"},
    {0x124, "distance"}, {0x130, "view.x"}, {0x134, "view.y"}, {0x138, "view.z"}, {0x13c, "plane0.x"},
    {0x140, "plane0.y"}, {0x144, "plane0.z"}, {0x148, "plane0.d"}, {0x14c, "plane1.x"}, {0x150, "plane1.y"},
    {0x154, "plane1.z"}, {0x158, "plane1.d"}, {0x15c, "plane2.x"}, {0x160, "plane2.y"}, {0x164, "plane2.z"},
    {0x168, "plane2.d"}, {0x16c, "plane3.x"}, {0x170, "plane3.y"}, {0x174, "plane3.z"}, {0x178, "plane3.d"},
    {0x17c, "plane4.x"}, {0x180, "plane4.y"}, {0x184, "plane4.z"}, {0x188, "plane4.d"}, {0x18c, "plane5.x"},
    {0x190, "plane5.y"}, {0x194, "plane5.z"}, {0x198, "plane5.d"}, {0x1a4, "stick pitch"}, {0x1d0, "framing scale"},
    {0x230, "look.x"}, {0x238, "look.z"}, {0x23c, "prev focus.x"}, {0x240, "prev focus.y"}, {0x248, "blend time"},
    {0x24c, "blend duration"}, {0x258, "start.distance"}, {0x25c, "start.pitch"}, {0x260, "start.yaw"},
    {0x264, "start.focus.x"}, {0x270, "end.distance"}, {0x274, "end.pitch"}, {0x278, "end.yaw"},
    {0x288, "current.distance"}, {0x28c, "current.pitch"}, {0x290, "current.yaw"}, {0x2a0, "right.x"},
    {0x2a8, "right.z"}, {0x2ac, "fov.accel"}, {0x2b8, "fov.current"}, {0x2c0, "fov.target"}, {0x2c8, "requested fov"},
    {0x2cc, "wall distance"}, {0x2e8, "unk44.accel"}, {0x2f4, "unk44.current"},
    {0x10c, "pitch min A"}, {0x110, "pitch max A"}, {0x114, "pitch min B"}, {0x118, "pitch max B"},
    {0x1b0, "obstruction speed"}, {0x1b4, "obstruction pt.x"}, {0x1b8, "obstruction pt.y"},
    {0x1bc, "obstruction pt.z"}, {0x1c0, "obstruction time"}, {0x1c4, "unk1c4.x"}, {0x1dc, "volume yaw speed"},
    {0x1e0, "volume yaw"}, {0x1e4, "volume yaw range"}, {0x1e8, "obstruction hit t"}, {0x30c, "ground point.x"},
    {0x310, "ground point.y"}, {0x314, "ground point.z"},
};

}  // namespace

// The native offset of a PS3 offset of the track: the same within each run of fields without pointers (the x64 build
// has larger pointers), so each run is found from a member at its start.
uint32_t NativeOffset(const CKCameraClassicTrack3* track, uint32_t ps3) {
    const unsigned char* base = reinterpret_cast<const unsigned char*>(track);
    struct Anchor {
        uint32_t ps3;
        const void* native;
    };
    const Anchor anchors[] = {
        {0x1f8, &track->m_wallHit},
        {0x1e8, &track->m_obstructionHit},  // a pointer inside: 8-aligned on x64
        {0x1dc, &track->m_volumeYawSpeed},
        {0x58, &track->m_unk58},
        {0x20, &track->m_WorldPosition},
    };
    for (const Anchor& anchor : anchors) {
        if (ps3 >= anchor.ps3) {
            return static_cast<uint32_t>(static_cast<const unsigned char*>(anchor.native) - base) + (ps3 - anchor.ps3);
        }
    }
    return ps3;
}

CKS08GameManager* Manager() { return static_cast<CKS08GameManager*>(g_pEngine->m_gameManager); }

// LVL010 requested from its spawn point in `sector` (New game's start), as ground_probe_test does, run until the game
// loop is in mode 5 (or 8) with that sector current and active: the collision service then holds the level's grounds
// and walls, which the COLL family's functions (the obstruction test in Start, the ground clearance in Update) query.
bool StartLevel(int level, int32_t sector) {
    CKS08GameManager* manager = Manager();
    IKGameStructure* structure = static_cast<IKGameStructure*>(manager->m_gameStructure);
    for (uint32_t i = 0; i < structure->m_vpStages.m_ui32NbUsedElt; ++i) {
        CKGameLevel* stage = structure->m_vpStages.m_pBlock[i];
        if (stage == nullptr || stage->m_i32StageIndex != level) continue;
        for (uint32_t s = 0; s < stage->m_vpSpawnPoints.m_ui32NbUsedElt; ++s) {
            CKGameSpawnPoint* spawnPoint = stage->m_vpSpawnPoints.m_pBlock[s];
            if (spawnPoint != nullptr && spawnPoint->m_iSectorIndex == sector) {
                structure->m_pCurrentSpawnPoint = spawnPoint;
                break;
            }
        }
    }
    manager->RequestSpawnPointLevel();  // vt+0x2e8
    uint32_t gameplayFrames = 0;
    for (uint32_t frame = 0; frame < 20000; ++frame) {
        c15::RunFrame();
        if (g_pCKGameLoop->m_mode == CKGameLoop::kModeQuit) return false;
        const uint32_t mode = g_pCKGameLoop->m_mode;
        if ((mode != 5 && mode != 8) || manager->m_currentLevel != level) continue;
        CKLevel* ckLevel = g_pEngine->m_level;
        const int32_t current = ckLevel->m_currentSector;
        const bool active = current >= 0 &&
                            (static_cast<const CKSector*>(ckLevel->m_vpSectors.m_pBlock[current])->m_ba16Properties & 1) != 0;
        if (active && ++gameplayFrames == 3) return true;
    }
    return false;
}

int main() {
    if (!c15::BootToFrontEnd()) {
        std::printf("camera_ct3_test: no game data configured: skipped\n");
        return 77;
    }
    c15::ParkFrontEndSequence();
    if (!StartLevel(10, 1)) {
        std::printf("camera_ct3_test: LVL010 did not start\n");
        std::_Exit(1);
    }
    // The level's camera service (its loaded avoiding datas, push sphere, ...); the fields the frame depends on are set
    // below from the census. The camera context is the test's own (the PS3 frame's height / width).
    alignas(16) static unsigned char contextStorage[sizeof(CameraContext)];
    std::memset(contextStorage, 0, sizeof(contextStorage));
    CKSrvCamera* camera = static_cast<CKSrvCamera*>(g_pEngine->m_srvCamera);
    CameraContext* context = reinterpret_cast<CameraContext*>(contextStorage);
    // The camera context's height / width (+0x48): 720 / 1280 = 0.5625 exactly. (The CT3 family pinned 0x3f100001 here to
    // make frustum planes 2 and 3 match; the real cause was the degree-to-radian constant, one ulp off: the TOC word is
    // 0x3c8efa34. With it fixed, 0.5625 gives the planes bit for bit.)
    context->m_fHeightOverWidth = F(0x3f100000u);
    camera->m_pCameraContext = context;

    CKCameraConstraint* zone = new CKCameraConstraint();
    for (int i = 0; i < 6; ++i) zone->m_afBox[i] = F(kLiveZone[1 + i]);
    zone->m_unk1c = static_cast<uint8_t>(kLiveZone[7] >> 24);
    zone->m_unk20 = F(kLiveZone[8]);
    zone->m_unk24 = F(kLiveZone[9]);
    zone->m_unk38 = static_cast<uint8_t>(kLiveZone[14] >> 24);
    zone->m_unk3c = nullptr;
    zone->m_unk40 = nullptr;
    for (int i = 0; i < 12; ++i) zone->m_afUnk44[i] = F(kLiveZone[17 + i]);
    zone->m_unk74 = kLiveZone[29];
    zone->m_unk78 = F(kLiveZone[30]);
    zone->m_unk7c = nullptr;
    for (int i = 0; i < 7; ++i) zone->m_afUnk80[i] = F(kLiveZone[32 + i]);

    for (int i = 0; i < 3; ++i) camera->m_unk2c[3 + i] = kLiveServiceFov[i];
    camera->m_v3RealAxisX = {F(kLiveServiceAxes[0]), F(kLiveServiceAxes[1]), F(kLiveServiceAxes[2])};
    camera->m_v3RealAxisZ = {F(kLiveServiceAxes[6]), F(kLiveServiceAxes[7]), F(kLiveServiceAxes[8])};
    CKSrvCamera::StackEntry& entry = camera->m_aStack[0];
    entry.m_unk04 = static_cast<uint8_t>(kLiveStack0[1] >> 24);
    entry.m_unk05 = static_cast<uint8_t>(kLiveStack0[1] >> 16);
    entry.m_unk08 = F(kLiveStack0[2]);
    entry.m_unk0c = static_cast<uint8_t>(kLiveStack0[3] >> 24);
    for (int i = 0; i < 4; ++i) entry.m_unk10[i] = F(kLiveStack0[4 + i]);
    // At control the hero's entry has the pitch factor 2.5 and the radius factor 1.5 (the fight's intro); in the frame
    // the track ran they were 1 (the desired pitch the track kept, 0.1396, is record[1] * 1).
    entry.m_unk10[0] = 1.0f;
    entry.m_unk10[3] = kRadiusFactor;
    entry.m_unk20 = F(kLiveStack0[8]);
    for (int i = 0; i < 3; ++i) entry.m_unk24[i] = F(kLiveStack0[9 + i]);
    camera->m_ui32NbStacked = 1;
    for (int r = 0; r < 4; ++r) {
        for (int w = 0; w < 5; ++w) camera->m_unkc40[r][w] = kLiveRecords[r * 5 + w];
    }
    camera->m_baTemporaryFlags = 0x200000u;
    camera->m_pActiveConstraint = zone;

    CKCameraClassicTrack3* track = new CKCameraClassicTrack3();
    std::memcpy(&track->m_param5c, &kLiveTrack[0x5c / 4], 35 * 4);
    track->m_Flags = kLiveTrack[2];
    track->m_fFar = F(kLiveTrack[5]);
    track->m_unk18 = F(kLiveTrack[6]);
    track->m_fFov = F(kLiveTrack[7]);
    track->m_unk44 = 0;
    track->m_unk48 = 0;
    track->m_unk4c = 0;
    track->m_unk50 = nullptr;

    track->Start(nullptr);
    track->Update(F(0x3cac2171u));  // the frame's dt (the track's blend time after it)

    const unsigned char* native = reinterpret_cast<const unsigned char*>(track);
    int bad = 0;
    for (const Field& field : kChecked) {
        uint32_t mine;
        std::memcpy(&mine, native + NativeOffset(track, field.offset), 4);
        const uint32_t live = kLiveTrack[field.offset / 4];
        const double a = F(mine);
        const double b = F(live);
        const bool same = mine == live;
        std::printf("%s +0x%03x %-18s dotd %08x %14.7g  live %08x %14.7g\n", same ? "  " : "!!", field.offset, field.name,
                    mine, a, live, b);
        if (!same) ++bad;
    }
    std::printf("camera_ct3_test: %d of %d fields differ\n", bad, static_cast<int>(sizeof(kChecked) / sizeof(kChecked[0])));

    // Plausibility of the steady follow (no RPCS3 truth): the hero walks 0.1 unit per frame along x for two seconds,
    // then stands; the right stick is off (no camera service flag 0x200000). The target must follow it (it stops
    // within the spring's dead zone of 0.1), the camera keep its orbit distance in [the shortest, the longest + the
    // framing] and nothing become NaN.
    camera->m_baTemporaryFlags = 0;
    const float dt = 1.0f / 60.0f;
    int steadyBad = 0;
    for (int frame = 0; frame < 240; ++frame) {
        if (frame < 120) entry.m_unk24[0] += 0.1f;
        track->Update(dt);
        const CVector3& p = track->m_WorldPosition;
        const CVector3& t = track->m_WorldTarget;
        const float dx = p.x - t.x, dy = p.y - t.y, dz = p.z - t.z;
        const float distance = std::sqrt(dx * dx + dy * dy + dz * dz);
        if (std::isnan(p.x) || std::isnan(p.y) || std::isnan(p.z) || std::isnan(t.x) || !(distance >= track->m_minDistance - 1e-3f) ||
            !(distance <= track->m_maxDistance + 10.0f)) {
            ++steadyBad;
            if (steadyBad < 5) std::printf("steady frame %d: position (%g %g %g) target (%g %g %g) distance %g\n", frame, p.x, p.y, p.z, t.x, t.y, t.z, distance);
        }
        if (frame % 30 == 0 || frame == 239) {
            std::printf("steady %3d: hero x %7.3f target (%7.3f %7.3f %7.3f) position (%7.3f %7.3f %7.3f) distance %6.3f\n", frame,
                        entry.m_unk24[0], t.x, t.y, t.z, p.x, p.y, p.z, distance);
        }
    }
    const float lag = entry.m_unk24[0] - track->m_WorldTarget.x;
    if (!(std::fabs(lag) < 0.1f)) {  // the follow spring does not close a gap below 0.1 (its dead zone)
        std::printf("steady: the target is %g behind the hero after the stop\n", lag);
        ++steadyBad;
    }
    std::printf("camera_ct3_test: steady follow %s\n", steadyBad == 0 ? "ok" : "FAILED");
    std::fflush(stdout);
    std::_Exit(bad == 0 && steadyBad == 0 ? 0 : 1);  // the level's shutdown is not ported (as ground_probe_test)
}
