// CKSoundManager.cpp - reconstructed original translation unit 0x113080-0x114510 (GAME_TOC1, main_toc1), 53 functions, 43 live.
// Primary class: CKSoundManager  key 0xc0  category Manager  size 0x44  vtable 0xb198e0
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x113080  CKSoundManager_Delete
//   [ ] 0x1130d0  CKSoundManager_Construct  [dead]
//   [ ] 0x1130f0  CKSoundManager_Construct_2  [dead]
//   [ ] 0x113110  KStub_Return200_113110  [dead]
//   [ ] 0x113118  KStub_Nop_113118  [dead]
//   [ ] 0x113120  KStub_Nop_113120  [dead]
//   [x] 0x113128  CKSoundManager_MessageProc  (MessageProc: 1, IKBaseClass's default)
//   [ ] 0x113130  CKSoundManager_SetSfxVolume_maybe  [dead]
//   [x] 0x113190  KStub_Nop_113190  (empty: CKSoundDictionary::Load's failure notice (its note))
//   [ ] 0x113198  RegisterCKSoundManagerClass
//   [ ] 0x113210  _GLOBAL__I_113210
//   [x] 0x113220  CKSoundManager_PostSectorUnload
//   [x] 0x113248  CKSoundManager_SectorUnload
//   [x] 0x113270  CKSoundManager_PreSectorLoaded
//   [x] 0x113298  CKSoundManager_SetVolumes_maybe
//   [x] 0x113390  CKSoundManager_UnsuspendSoundGroups_maybe
//   [x] 0x1133b8  CKSoundManager_AreStreamsState9_maybe
//   [x] 0x1133e8  CKSoundManager_AreStreamsIdle_maybe
//   [x] 0x113418  CKSoundManager_AreStreamsSettled_maybe
//   [x] 0x113448  CKSoundManager_AreStreamsIdle_2_maybe
//   [x] 0x113478  CKSoundManager_SuspendSoundGroups_maybe
//   [ ] 0x1134a0  CKSoundManager_ResumeChannelSet_maybe  [dead]
//   [ ] 0x1134d8  CKSoundManager_PauseChannelSet_maybe  [dead]
//   [x] 0x113510  CKSoundManager_Resume
//   [x] 0x113568  CKSoundManager_Pause
//   [x] 0x1135c0  CKSoundManager_Start
//   [x] 0x113618  CKSoundManager_PostUpdate
//   [x] 0x113650  CKSoundManager_PreUpdate
//   [x] 0x113678  CKSoundManager_RecursiveRegistration  (CKSoundManager::RecursiveRegistration)
//   [ ] 0x113730  CKSoundManager_vfB8  [platform]  (the RWA PS3 driver's audio thread stopped and joined and the driver closed (exit only): the platform mixer shuts down in vt+0xb4 (CKSoundManager::VfB4); CKSoundManager::ShutdownAudio stays empty)
//   [x] 0x113780  CKSoundManager_vfB4
//   [x] 0x1137b8  CKSoundManager_DestroyModule
//   [x] 0x113978  CKSoundManager_DeleteArray  (CKSoundManager::DeleteArray, CKSoundManager.h)
//   [x] 0x113a20  CKSoundManager_IsNotPausedAndTimeRunning_maybe
//   [x] 0x113a68  CKSoundManager_InitializeModule
//   [x] 0x113ba8  CKSoundManager_Create
//   [x] 0x113bf8  CKSoundManager_CreateArray  (CKSoundManager::CreateArray, CKSoundManager.h)
//   [ ] 0x113ca8  CKSoundManager_Save
//   [x] 0x113cb0  CKSoundManager_PostLoad  (PostLoad: 1, IKSerializable's default)
//   [x] 0x113cb8  CKSoundManager_Destroy
//   [x] 0x113d08  CKSoundManager_DestroyGame  (CKSoundManager::DestroyGame)
//   [x] 0x113d30  CKSoundManager_Load
//   [ ] 0x113f00  FUN_00113f00  [dead]
//   [x] 0x113f68  CKSoundManager_SaveAndMuteVolume_maybe
//   [x] 0x113fe8  CKSoundManager_RestoreSavedVolume_maybe
//   [x] 0x114058  CKSoundManager_Update
//   [x] 0x1141d8  CKSoundManager_Stop
//   [x] 0x114290  CKSoundManager_Restart
//   [ ] 0x114340  CKSoundManager_Destructor_2  [dead]
//   [x] 0x114360  CKSoundManager_UpdateLocalizedData
//   [x] 0x1144a0  CKSoundManager_DeletingDestructor  (~CKSoundManager (vtable stores), delete)
//   [x] 0x1144e8  CKSoundManager_Destructor  (~CKSoundManager (vtable stores only), CKSoundManager.h)
//   [x] 0x114508  KStub_Return0_114508  (KStub_Return0_114508, CKSoundManager.h)
//
//   [ ] 0x9a6bc8  CKSoundManager_GetClassType  [inline]
//   [ ] 0x9a6bd0  CKSoundManager_GetClassID  [inline]
//   [ ] 0x9a6bd8  CKSoundManager_SectorLoaded  [inline]
//   [ ] 0x9a6be0  CKSoundManager_IsKindOfClass  [inline]
#include "k2000/managers/CKSoundManager.h"

#include <cstring>

#include "k2000/core/Stub.h"
#include "k2000/io/IKFile.h"
#include "k2000/logic/CKSavingManager.h"
#include "k2000/sound/CKSoundOutput.h"
#include "k2000/sound/CKSoundStreamManager.h"
#include "k2000/sound/SoundVoiceManager.h"
#include "k2000/misc/Engine.h"
#include "k2000/system/CTimeManager.h"
#include "k2000/system/IKTime.h"
#include "platform/audio/mixer.h"
#include "platform/audio/rwa.h"
#include "platform/audio/rwa_stream.h"
#include "k2000/system/Fps60Hz.h"

namespace {

// One Read of `count` little-endian words into consecutive fields, each then swapped (the original's
// lwbrx/stw after a 12-byte read). Local until IKFile.h has such a helper.
void ReadWordsLE(IKFile* file, void* dst, uint32_t count) {
    uint8_t bytes[0x10];
    file->Read(bytes, count * 4);
    for (uint32_t i = 0; i < count; ++i) {
        const uint8_t* b = bytes + 4 * i;
        const uint32_t word = static_cast<uint32_t>(b[0]) | (static_cast<uint32_t>(b[1]) << 8) |
                              (static_cast<uint32_t>(b[2]) << 16) | (static_cast<uint32_t>(b[3]) << 24);
        std::memcpy(static_cast<uint8_t*>(dst) + 4 * i, &word, 4);
    }
}

// 0x00023b98 KStub_Return0_23b98(job queue) (CKServiceManager.cpp): whether the job queue holds the
// sounds back; always 0.
uint8_t JobQueue_HoldsSounds() { return 0; }

}  // namespace

// 0x00113ba8 CKSoundManager_Create (the constructor is inlined there; 0x1130d0 is dead)
CKSoundManager::CKSoundManager() { m_fSoundsVolume = 1.0f; }

IKBaseClass* CKSoundManager::Create() { return new CKSoundManager(); }

// 0x00113080 CKSoundManager_Delete
void CKSoundManager::Delete(IKBaseClass* object) { delete object; }

// 0x001137b8 CKSoundManager_DestroyModule. The stream manager and the voice manager are released without a null test
// and their pointers are left; the voice manager's destructor is inlined here.
void CKSoundManager::DestroyModule() {
    m_pSoundStreamManager->FreeArrays();
    if (m_pSoundStreamManager != nullptr) delete m_pSoundStreamManager;
    m_pVoiceManager->ReleaseVoices();
    if (m_pVoiceManager != nullptr) delete m_pVoiceManager;
    if (m_pOutput != nullptr) {
        m_pOutput->ShutdownDriver();
        if (m_pOutput != nullptr) delete m_pOutput;
        m_pOutput = nullptr;
    }
    VfB4();  // vt+0xb4
}

// 0x00113780 CKSoundManager_vfB4
void CKSoundManager::VfB4() { dotd::audio::Shutdown(); }

// 0x00113a68 CKSoundManager_InitializeModule
int32_t CKSoundManager::InitializeModule(void*) {
    dotd::trace::Boot("CKSoundManager::Init (RWA + MultiStream: platform/audio)");
    // RwaSystem_Open_maybe(open parameters, 1) -> 0x00c451ec, RwaSystem_RegisterCoreTypes_maybe and
    // Rwa_Initialize_maybe set up the RWA library; the platform layer opens the mixer instead.
    dotd::audio::Init();
    CKSoundOutput* output = new CKSoundOutput();  // OperatorNew(0x28)
    m_pOutput = output;
    output->Init();
    m_pVoiceManager = new SoundVoiceManager();             // OperatorNew(0x38), constructor inlined
    m_pSoundStreamManager = new CKSoundStreamManager();    // OperatorNew(0x1c)
    m_pVoiceManager->Init();
    m_pSoundStreamManager->Init();
    m_unk20 = 0;
    m_unk1c = 0;
    m_unk1d = 0;
    m_unk40 = 0;
    m_unk1f = 0;
    return 1;
}

// 0x00113d30 CKSoundManager_Load
int32_t CKSoundManager::Load(IKFile* file, int32_t type) {
    if (type == K_GAME_PLATEFORMS) {
        ReadWordsLE(file, m_unk34, 3);
        m_pSoundStreamManager->Load(file, K_GAME_PLATEFORMS);  // its result is ignored
        return 1;
    }
    if (type == K_GAME_LOCALIZATION) {
        ReadWordsLE(file, m_unk28, 3);
        return 1;
    }
    if (type == K_LEVEL_PLATEFORMS) {
        m_pOutput->Load(file, K_LEVEL_PLATEFORMS);
        m_pSoundStreamManager->Load(file, K_LEVEL_PLATEFORMS);
        m_pVoiceManager->Load(file, K_LEVEL_PLATEFORMS);
    }
    return 1;
}

// 0x00113298 CKSoundManager_SetVolumes_maybe
void CKSoundManager::SetVolumes(float master, float music, float speech, float effects) {
    SoundOutput_SetMasterVolume(master, m_pOutput);
    m_pSoundStreamManager->SetMusicVolume(music);
    m_pSoundStreamManager->SetSpeechVolume(speech);
    if (m_unk1f != 0 && m_unk20 == 0) {
        m_fSaveSoundsVolume = effects;
        return;
    }
    float v;
    if (!(effects <= 1.0f)) {
        v = 1.0f;
    } else if (effects <= 0.0f) {
        v = 0.0f;
    } else {
        v = effects;
    }
    m_fSoundsVolume = v;
}

// 0x00113510 CKSoundManager_Resume
void CKSoundManager::Resume() {
    if (m_unk1e == 0) return;
    m_unk1e = 0;
    m_pVoiceManager->ResumeAll();
    m_pSoundStreamManager->ResumeAll();
}

// 0x00113568 CKSoundManager_Pause
void CKSoundManager::Pause() {
    if (m_unk1e != 0) return;
    m_unk1e = 1;
    m_pVoiceManager->PauseAll();
    m_pSoundStreamManager->PauseAll();
}

// 0x001135c0 CKSoundManager_Start
// 0x00113678 CKSoundManager_RecursiveRegistration (P21)
void CKSoundManager::RecursiveRegistration(int32_t type) {
    m_pOutput->RecursiveRegistration(type);              // 0x00114738 SoundOutput_LevelReset_maybe
    m_pVoiceManager->RecursiveRegistration(type);        // 0x00117368 SoundVoiceManager_LevelReset_maybe
    m_pSoundStreamManager->RecursiveRegistration(type);  // 0x00115b98 SoundEmitterArray_LevelReset_maybe
    if (type == 0) g_pEngine->m_pSavingManager->RegisterSerializableObject(this, nullptr);  // vt+0x24
}

// 0x00113d08 CKSoundManager_DestroyGame (P21)
void CKSoundManager::DestroyGame() { m_pSoundStreamManager->DeleteAll(); }  // 0x001165e0

void CKSoundManager::Start() {
    m_unk1e = 0;
    m_unk40 = 0;
    m_unk1d = 0;
    m_unk1c = 0;
    // KStub_Nop_1172f8(voice manager)
    m_pSoundStreamManager->SnapVolumes();
}

// 0x00113618 CKSoundManager_PostUpdate: closes RWA's update bracket (every voice commits). Host hooks (not
// in the original): RWA's stream players (its "RWA" thread on the PS3) and the headless mixer advance by the
// frame's time here. The stream players run in real time on the PS3: they advance by the exact time since the last
// frame (IKTime +0x28, KGetExactTime as sampled by the clock), not by the game's delta, which the clock clamps (0.01 s
// in the two frames after CKGameLoop_Restart: the death recording's music stream then opens in the original's frame).
void CKSoundManager::PostUpdate(IKTime* frameClock) {
    if (Rwa_IsUpdating() != 0) Rwa_EndUpdate();
    const float dt = frameClock != nullptr ? frameClock->m_afDeltaTime[IKTime::SYSTEM_TIME] : 0.0f;
    static float s_lastExact = -1.0f;  // host state: the exact time of the previous frame's advance
    float streamDt = dt;
    if (frameClock != nullptr) {
        const float exact = frameClock->m_fLastExactTime;
        if (s_lastExact >= 0.0f && exact >= s_lastExact) streamDt = exact - s_lastExact;
        s_lastExact = exact;
    }
    if (dotd::fps::Unlocked()) {
        // --fps N: the players step per 60 Hz frame (a request taken costs a step, as the fitted 60 fps model has it),
        // with the time since the last 60 Hz frame shared out; none in a displayed frame that ends no 60 Hz frame.
        static float s_pending = 0.0f;
        s_pending += streamDt;
        const int32_t ticks = dotd::fps::Ticks();
        if (ticks > 0) {
            const float share = s_pending / static_cast<float>(ticks);
            for (int32_t i = 0; i < ticks; ++i) dotd::audio::RwaStreamPlayers_Advance(share);
            s_pending = 0.0f;
        }
    } else {
        dotd::audio::RwaStreamPlayers_Advance(streamDt);
    }
    dotd::audio::OnGameFrame(dt);
}

// 0x00113650 CKSoundManager_PreUpdate: opens RWA's update bracket.
void CKSoundManager::PreUpdate(IKTime*) { Rwa_BeginUpdate(); }

// 0x00113a20 CKSoundManager_IsNotPausedAndTimeRunning_maybe: on, and the engine clock running (state 0).
uint32_t CKSoundManager::IsNotPausedAndTimeRunning() {
    if (m_unk40 != 0) return 0;
    return g_pEngine->m_timeManager->m_pTime->m_eCurrentState == IKTime::RUNNING ? 1u : 0u;
}

// 0x00113f68 CKSoundManager_SaveAndMuteVolume_maybe: the effects volume is kept and set to 0.
void CKSoundManager::SaveAndMuteVolume(int32_t flag) {
    if (flag == 0) {
        if (m_unk1f != 0) return;
        m_fSaveSoundsVolume = m_fSoundsVolume;
        m_unk1f = 1;
        m_fSoundsVolume = 0.0f;
        return;
    }
    if (m_unk20 == 0) return;
    if (m_unk1f != 0) {
        m_unk20 = 0;
        m_fSoundsVolume = 0.0f;
        return;
    }
    m_fSaveSoundsVolume = m_fSoundsVolume;
    m_unk20 = 0;
    m_fSoundsVolume = 0.0f;
}

// 0x00113fe8 CKSoundManager_RestoreSavedVolume_maybe: the kept volume back, clamped to [0, 1].
void CKSoundManager::RestoreSavedVolume(uint8_t flag) {
    if (m_unk1f == 0) return;
    const float saved = m_fSaveSoundsVolume;
    float v;
    if (flag != 0) {
        m_unk20 = 1;
        if (!(saved <= 1.0f)) {
            v = 1.0f;
        } else {
            v = saved <= 0.0f ? 0.0f : saved;
        }
    } else {
        m_unk1f = 0;
        if (saved > 1.0f) {
            v = 1.0f;
        } else {
            v = saved <= 0.0f ? 0.0f : saved;
        }
    }
    m_fSoundsVolume = v;
}

namespace {
// --fps N (not in the original): the sound streams' state machines (one state per update: open, preload, play, stop)
// run whole 60 Hz updates (k2000/system/Fps60Hz.h), so a stream starts and ends after as long as at 60 fps (a sekens
// line with speech waits for its stream's player and position). The stream players themselves advance by real time.
void UpdateStreams(CKSoundStreamManager* streams, IKTime* frameClock) {
    if (dotd::fps::Unlocked()) {
        RunOn60HzFrames(frameClock, [streams, frameClock] { streams->UpdateAll(frameClock); });
        return;
    }
    streams->UpdateAll(frameClock);
}
}  // namespace

// 0x00114058 CKSoundManager_Update: while the job queue holds the sounds back the voices are paused
// (never here: KStub_Return0_23b98); then the voice engine and the stream types update.
void CKSoundManager::Update(IKTime* frameClock) {
    if (m_unk1c == 0) {
        if (m_unk40 == 0 && JobQueue_HoldsSounds() != 0) {
            const uint8_t paused = m_unk1e;
            m_unk1c = 1;
            if (paused == 0) {
                m_pVoiceManager->PauseAll();
                m_pVoiceManager->Update(frameClock);
                UpdateStreams(m_pSoundStreamManager, frameClock);
                return;
            }
        }
    } else if (JobQueue_HoldsSounds() == 0) {
        if (m_unk1e == 0) m_pVoiceManager->ResumeAll();
        m_unk1c = 0;
        m_pVoiceManager->Update(frameClock);
        UpdateStreams(m_pSoundStreamManager, frameClock);
        return;
    }
    m_pVoiceManager->Update(frameClock);
    UpdateStreams(m_pSoundStreamManager, frameClock);
}

// 0x001141d8 CKSoundManager_Stop: the voices resume if the job queue held them, the output effect is
// reset, every sound stops.
void CKSoundManager::Stop() {
    if (m_unk40 == 0 && m_unk1c != 0 && JobQueue_HoldsSounds() == 0) {
        if (m_unk1e == 0) m_pVoiceManager->ResumeAll();
        m_unk1c = 0;
    }
    m_pOutput->ResetOutputEffect();
    m_pVoiceManager->StopAll();
    m_pSoundStreamManager->CallNopHookOnEntries();
}

// 0x00114290 CKSoundManager_Restart (vt+0x54): the voices resume if the job queue held them (as in Stop), every voice
// released and the sectors' auto-play sounds started again, the stream types' hooks, not paused.
void CKSoundManager::Restart() {
    if (m_unk40 == 0 && m_unk1c != 0 && JobQueue_HoldsSounds() == 0) {
        if (m_unk1e == 0) m_pVoiceManager->ResumeAll();
        m_unk1c = 0;
    }
    m_pVoiceManager->ReleaseAllVoices();
    m_pSoundStreamManager->ResetEntries();
    m_unk1e = 0;
}

// 0x00113448 CKSoundManager_AreStreamsIdle_2_maybe (vt+0x58; CKGameLoop's mode 6 waits for it): every stream
// type's voices inactive.
int32_t CKSoundManager::Vf58() { return m_pSoundStreamManager->TestAllGroups(0); }

// 0x001133e8 CKSoundManager_AreStreamsIdle_maybe (vt+0x6c)
int32_t CKSoundManager::Vf6C() { return m_pSoundStreamManager->TestAllGroups(0); }

// 0x00113418 CKSoundManager_AreStreamsSettled_maybe (vt+0x74)
int32_t CKSoundManager::Vf74() { return m_pSoundStreamManager->TestAllGroups(1); }  // rldicl r3,r3,0,56

// 0x00114360 CKSoundManager_UpdateLocalizedData (vt+0xa8). The music and speech volumes are read through the engine's
// sound manager (TOC -0x4520 = 0xc50f20, +0x1c) and set on this one's stream manager.
void CKSoundManager::UpdateLocalizedData() {
    const float master = SoundOutput_GetMasterVolume(m_pOutput);  // 0x114510
    const float music = g_pEngine->m_soundManager->m_pSoundStreamManager->GetMusicVolume();  // 0x116cb8
    const float speech = g_pEngine->m_soundManager->m_pSoundStreamManager->GetSpeechVolume();  // 0x116ef0
    const float sounds = m_fSoundsVolume;
    SoundOutput_SetMasterVolume(master, m_pOutput);  // 0x114518
    m_pSoundStreamManager->SetMusicVolume(music);    // 0x117040
    m_pSoundStreamManager->SetSpeechVolume(speech);  // 0x116e30
    if (m_unk1f != 0 && m_unk20 == 0) {
        m_fSaveSoundsVolume = sounds;
        return;
    }
    float v;
    if (!(sounds <= 1.0f)) {  // ble without cror: a NaN takes 1.0
        v = 1.0f;
    } else if (sounds <= 0.0f) {
        v = 0.0f;
    } else {
        v = sounds;
    }
    m_fSoundsVolume = v;
}

// 0x00113390 CKSoundManager_UnsuspendSoundGroups_maybe
void CKSoundManager::UnsuspendSoundGroups() { m_pSoundStreamManager->Unsuspend(); }

// 0x001133b8 CKSoundManager_AreStreamsState9_maybe
uint8_t CKSoundManager::AreStreamsState9() { return m_pSoundStreamManager->TestAllGroups(2); }

// 0x00113478 CKSoundManager_SuspendSoundGroups_maybe
void CKSoundManager::SuspendSoundGroups() { m_pSoundStreamManager->Suspend(); }

// 0x00113270 CKSoundManager_PreSectorLoaded (SoundBank_PlaySectorAutoSounds_maybe 0x119000)
void CKSoundManager::PreSectorLoaded(int32_t sector) { m_pVoiceManager->PlaySectorAutoSounds(sector); }

// 0x00113248 CKSoundManager_SectorUnload: SoundVoiceManager 0x1173c0 is a bare return.
void CKSoundManager::SectorUnload(int32_t /*sector*/) {}

// 0x00113220 CKSoundManager_PostSectorUnload (SoundBank_StopSectorSounds 0x1175c0)
void CKSoundManager::PostSectorUnload(int32_t sector) { m_pVoiceManager->StopSectorSounds(sector); }

// 0x00113cb8 CKSoundManager_Destroy
void CKSoundManager::Destroy() {
    m_pVoiceManager->ReleaseVoicePool();
    m_pOutput->ClearEffectRefs();
    // KStub_Nop_115b00 on the stream manager
}
