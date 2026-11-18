// kcs_stream_test - pre-C2.7 package E3: the streamed cutscenes (KCS) of LVL010 played through their component.
//
// Loads LVL010 like geometry_read_test, then takes every CKCinematicStreamCpnt a CKStreamAnimCinematicBeginBloc starts
// (two in LVL010: STREAMS/PS3<n>.KCS) and runs the stream the way the stream blocs do, without media (no sekens or
// music): StartStream, then every frame UpdateStream and, once ready, Update, until the stream ends; Finish and Stop.
// It checks the stream file's reads (the header and body state machine on the synchronous RtFS layer), the chunk bodies
// converted to native images and fixed up by the channel types (animations: scheme 1, key frames linked inside the
// animation; camera tracks: keys behind the header), every segment read and played, and the run flag cleared at the end.
// The replays (fight, idle) never reach a streamed cutscene. Skipped (exit 77) without game data.
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "Renderware/rphanim/RpHAnim.h"
#include "Renderware/rtanim/RtAnim.h"
#include "Spyro2008/logic/CKS08GameManager.h"
#include "boot_helper.h"
#include "k2000/cinematics/CKStreamAnimCinematicBeginBloc.h"
#include "k2000/components/CKCinematicStreamCpnt.h"
#include "k2000/logic/CKGameLevel.h"
#include "k2000/logic/CKGameSpawnPoint.h"
#include "k2000/logic/io/CKLoadingManager.h"
#include "k2000/misc/CKGameLoop.h"
#include "k2000/misc/CoreSingletons.h"
#include "k2000/misc/Engine.h"
#include "k2000/misc/IKGameStructure.h"
#include "k2000/render/CRenderer.h"
#include "k2000/scenegraph/CAnimatedNode.h"
#include "k2000/system/CTimeManager.h"
#include "k2000/system/IKTime.h"

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

std::vector<CKCinematicStreamCpnt*> g_streams;

void CollectBegin(IKSerializable* object, uint32_t classKey, void*) {
    if (classKey != CKStreamAnimCinematicBeginBloc::kClassKey) return;
    IKSerializable* stream = static_cast<CKStreamAnimCinematicBeginBloc*>(object)->m_pStreamCpnt;
    if (stream == nullptr) return;
    for (CKCinematicStreamCpnt* s : g_streams) {
        if (s == stream) return;
    }
    g_streams.push_back(static_cast<CKCinematicStreamCpnt*>(stream));
}

uint32_t g_animChunks = 0, g_cameraChunks = 0, g_badChunks = 0;

// The chunks dispatched so far (state 5, or playing / played): their native images as the types left them.
void CheckChunks(const CKCinematicStreamCpnt* stream, std::vector<const void*>* seen) {
    const uint32_t channels = stream->m_vChannels.m_ui32NbUsedElt;
    for (uint32_t i = 0; i < stream->m_vChunks.m_ui32NbUsedElt; ++i) {
        const CKCinematicStreamCpnt::SChunk& chunk = stream->m_vChunks.m_pBlock[i];
        if (chunk.m_pData == nullptr) continue;
        bool known = false;
        for (const void* p : *seen) known = known || p == chunk.m_pData;
        if (known) continue;
        seen->push_back(chunk.m_pData);
        const uint32_t type = stream->m_vChannels.m_pBlock[i % channels].m_type;
        if (type == 1) {
            const SCinematicCameraTrack* track = static_cast<const SCinematicCameraTrack*>(chunk.m_pData);
            ++g_cameraChunks;
            if (track->m_pKeys != reinterpret_cast<const SCinematicCameraKey*>(track + 1) || track->m_ui32NbKeys == 0) {
                ++g_badChunks;
                std::printf("kcs_stream: bad camera chunk %u: %u keys\n", i, track->m_ui32NbKeys);
            }
            continue;
        }
        const RtAnimAnimation* animation = static_cast<const RtAnimAnimation*>(chunk.m_pData);
        ++g_animChunks;
        bool ok = animation->interpInfo == RtAnimGetInterpolatorInfo(1) && animation->numFrames > 0 &&
                  animation->duration > 0.0f && animation->pFrames == animation + 1 && animation->customData != nullptr;
        const RpHAnimStdKeyFrame* frames = static_cast<const RpHAnimStdKeyFrame*>(animation->pFrames);
        for (int32_t f = 0; ok && f < animation->numFrames; ++f) {
            ok = frames[f].prevFrame >= frames && frames[f].prevFrame < frames + animation->numFrames;
        }
        if (!ok) {
            ++g_badChunks;
            std::printf("kcs_stream: bad animation chunk %u: %d frames, duration %g\n", i, animation->numFrames,
                        animation->duration);
        }
    }
}
}  // namespace

int main() {
    if (!c15::BootToFrontEnd()) {
        std::printf("kcs_stream: no game data configured: skipped\n");
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

    Kp3_ForEachLoadedObject(CollectBegin, nullptr);
    std::printf("kcs_stream: %zu stream(s) started by a begin bloc\n", g_streams.size());
    C15_CHECK(g_streams.size() == 2);

    for (CKCinematicStreamCpnt* stream : g_streams) {
        std::printf("kcs_stream: PS3%d.KCS: %u channels, %d segments of %g s, %u kept, length %g s\n", stream->m_unkc4,
                    stream->m_vChannels.m_ui32NbUsedElt, stream->m_unkc8, stream->m_fTime, stream->m_unkdc, stream->m_unkd0);
        C15_CHECK(stream->StartStream(0) == 1);
        C15_CHECK(g_cinematicStreamFile.m_bRunning == 1);
        // The first segments read: each channel's actor and its first chunk. The RtFS callbacks come with the PS3's
        // latency (CinematicStreamFile.cpp: the open a frame later, each read two frames later), so the frames advance
        // (the render frame counter) until they are in.
        for (int i = 0; i < 400 && stream->m_ui32SegmentsRead != static_cast<uint32_t>(stream->m_unkdc); ++i) {
            g_ui16RenderFrameCounter = static_cast<uint16_t>(g_ui16RenderFrameCounter == 0xfffe ? 1 : g_ui16RenderFrameCounter + 1);
            stream->UpdateStream(g_pEngine->m_timeManager->m_pTime);
        }
        C15_CHECK(g_cinematicStreamFile.m_file.m_bOpened == 1);
        C15_CHECK(stream->m_ui32SegmentsRead == static_cast<uint32_t>(stream->m_unkdc));
        for (uint32_t c = 0; c < stream->m_vChannels.m_ui32NbUsedElt; ++c) {
            const CKCinematicStreamCpnt::SChannel& channel = stream->m_vChannels.m_pBlock[c];
            const CKCinematicStreamCpnt::SChunk& chunk = stream->m_vChunks.m_pBlock[c];
            int32_t hierarchyNodes = -1, animationNodes = -1, animationFrames = -1;
            if (channel.m_pUnk04 != nullptr && channel.m_pUnk04->IsKindOfClass(0x54b) != 0) {
                const RpHAnimHierarchy* hierarchy = static_cast<const CAnimatedNode*>(channel.m_pUnk04)->m_pRpHAnimHierarchy;
                if (hierarchy != nullptr) hierarchyNodes = hierarchy->numNodes;
            }
            if (channel.m_type != 1 && chunk.m_pData != nullptr) {
                const RtAnimAnimation* animation = static_cast<const RtAnimAnimation*>(chunk.m_pData);
                animationNodes = RtAnimAnimationGetNumNodes(animation);
                animationFrames = animation->numFrames;
            }
            std::printf("kcs_stream:   channel %u type %u: node %s, hook %s, second node %s; hierarchy %d nodes, first "
                        "chunk %d key frames for %d nodes\n", c, channel.m_type, channel.m_pUnk04 != nullptr ? "yes" : "no",
                        channel.m_pUnk08 != nullptr ? "yes" : "no", channel.m_pUnk18 != nullptr ? "yes" : "no",
                        hierarchyNodes, animationFrames, animationNodes);
        }
        std::vector<const void*> seen;
        uint32_t frames = 0, readyFrame = 0, endFrame = 0;
        const uint32_t limit = static_cast<uint32_t>(static_cast<float>(stream->m_unkc8) * stream->m_fTime * 60.0f) + 600;
        for (; frames < limit; ++frames) {
            c15::RunFrame();
            IKTime* clock = g_pEngine->m_timeManager->m_pTime;
            const uint8_t going = stream->UpdateStream(clock);
            CheckChunks(stream, &seen);
            if (going == 0) {
                endFrame = frames;
                break;
            }
            if ((stream->m_unkfc & 0x400) != 0) {
                if (readyFrame == 0) readyFrame = frames;
                stream->Update(clock);
            }
        }
        std::printf("kcs_stream: ready at +%u, ended at +%u, %u of %d segments read, %u played, flags 0x%x\n", readyFrame,
                    endFrame, stream->m_ui32SegmentsRead, stream->m_unkc8, stream->m_ui32SegmentsPlayed,
                    stream->m_unkfc);
        C15_CHECK(endFrame != 0);
        C15_CHECK((stream->m_unkfc & 0x20) == 0);  // no time-out
        C15_CHECK(stream->m_ui32SegmentsRead == static_cast<uint32_t>(stream->m_unkc8));
        C15_CHECK(stream->m_ui32SegmentsPlayed == static_cast<uint32_t>(stream->m_unkc8) ||
                  (stream->m_unkfc & 0x4000) != 0);
        stream->Finish();
        stream->Stop();
        C15_CHECK(g_cinematicStreamFile.m_bRunning == 0);
        C15_CHECK(g_cinematicStreamFile.m_file.m_pFile == nullptr);
    }
    std::printf("kcs_stream: %u animation and %u camera chunks checked, %u bad\n", g_animChunks, g_cameraChunks, g_badChunks);
    C15_CHECK(g_animChunks > 0);
    C15_CHECK(g_cameraChunks > 0);
    C15_CHECK(g_badChunks == 0);

    std::fflush(stdout);
    if (c15::g_failures == 0) std::printf("kcs_stream: all tests passed\n");
    std::fflush(stdout);
    std::_Exit(c15::g_failures == 0 ? 0 : 1);
}
