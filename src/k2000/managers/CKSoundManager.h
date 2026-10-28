// CKSoundManager.h - the sound manager (key 0xc0, vtable 0xb198e0, size 0x44). Original unit:
// CKSoundManager.cpp (0x113080-0x114510). XXL2: K/KModules/KSL/CKSoundManager.h (m_pOutput,
// m_pSoundStreamManager, m_fSoundsVolume with the constructor's 1.0); DotD moves XXL2's listener and
// dictionaries into the voice manager (+0x08). Loaded from GAME.KP3 (mode 1), 00GLC.KP3 (mode 3) and each
// level (mode 0). STUB(audio): InitializeModule does not open RWA/MultiStream.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/managers/IKModule.h"

class CKSoundOutput;
class CKSoundStreamManager;
class SoundVoiceManager;

class CKSoundManager : public IKModule {
public:
    DOTD_CLASS_KEY(kCategoryManager, 3)

    CKSoundManager();                         // 0x00113ba8 CKSoundManager_Create (inlined)
    ~CKSoundManager() override {}             // 0x1144e8 (vtable stores only)

    static IKBaseClass* Create();             // 0x00113ba8 CKSoundManager_Create
    static void Delete(IKBaseClass* object);  // 0x00113080 CKSoundManager_Delete

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x00113d30 CKSoundManager_Load
    void Start() override;                              // vt+0x50 0x001135c0 CKSoundManager_Start
    void Stop() override;                               // vt+0x68 0x001141d8 CKSoundManager_Stop
    // vt+0x8c 0x00113248 CKSoundManager_SectorUnload: the voice manager's 0x1173c0 (a bare return).
    void SectorUnload(int32_t sector) override;
    // vt+0x84 0x00113270 CKSoundManager_PreSectorLoaded: the sector's auto-play sounds started.
    void PreSectorLoaded(int32_t sector) override;
    // vt+0x90 0x00113220 CKSoundManager_PostSectorUnload: the sector's sounds stopped.
    void PostSectorUnload(int32_t sector) override;
    void Pause() override;                              // vt+0x70 0x00113568 CKSoundManager_Pause
    void Resume() override;                             // vt+0x78 0x00113510 CKSoundManager_Resume
    void Update(IKTime* frameClock) override;           // vt+0x7c 0x00114058 CKSoundManager_Update
    int32_t InitializeModule(void* params) override;    // vt+0x94 0x00113a68 CKSoundManager_InitializeModule
    void DestroyModule() override {}                    // vt+0x98 0x1137b8  STUB(C1.6): never reached by the front end
    void PreUpdate(IKTime* frameClock) override;        // vt+0x9c 0x00113650 CKSoundManager_PreUpdate
    void PostUpdate(IKTime* frameClock) override;       // vt+0xa0 0x00113618 CKSoundManager_PostUpdate
    virtual void VfB4() {}                              // vt+0xb4 0x113780 Rwa terminate/close  STUB(audio): exit only
    virtual void ShutdownAudio() {}                     // vt+0xb8 0x113730 _maybe (CKGameLoop_ShutdownAndExit)  STUB(audio): exit only

    // 0x00113298 CKSoundManager_SetVolumes_maybe (IKGameManager_ApplyOptions_maybe 0x139b4): the master
    // (port) volume, the music and speech stream types' volumes, the effects volume (clamped to [0, 1];
    // kept in m_fSaveSoundsVolume while muted by a video).
    void SetVolumes(float master, float music, float speech, float effects);
    void UnsuspendSoundGroups();                 // 0x00113390 CKSoundManager_UnsuspendSoundGroups_maybe
    uint8_t AreStreamsState9();                  // 0x001133b8 CKSoundManager_AreStreamsState9_maybe
    void SuspendSoundGroups();                   // 0x00113478 CKSoundManager_SuspendSoundGroups_maybe
    // 0x00113a20 CKSoundManager_IsNotPausedAndTimeRunning_maybe
    uint32_t IsNotPausedAndTimeRunning();
    // 0x00113f68 CKSoundManager_SaveAndMuteVolume_maybe (videos, cinematic streams, the game manager)
    void SaveAndMuteVolume(int32_t flag);
    // 0x00113fe8 CKSoundManager_RestoreSavedVolume_maybe
    void RestoreSavedVolume(uint8_t flag);

    CKSoundOutput* m_pOutput;                     // +0x04 InitializeModule
    SoundVoiceManager* m_pVoiceManager;           // +0x08 InitializeModule
    CKSoundStreamManager* m_pSoundStreamManager;  // +0x0c InitializeModule
    float m_fSoundsVolume;                        // +0x10 the constructor sets 1.0
    uint32_t m_unk14;                             // +0x14 not written by the constructor, Init or Load
    uint32_t m_unk18;                             // +0x18 likewise
    uint8_t m_unk1c;    // +0x1c InitializeModule 0; Update sets/clears it around the job queue (voices paused meanwhile)
    uint8_t m_unk1d;    // +0x1d InitializeModule / Start 0
    uint8_t m_unk1e;    // +0x1e the paused flag (Pause 1, Resume 0); first set by Start
    uint8_t m_unk1f;    // +0x1f InitializeModule 0; CKSoundManager_SaveAndMuteVolume_maybe sets 1
    uint8_t m_unk20;    // +0x20 InitializeModule 0; RestoreSavedVolume(1) sets it, SaveAndMuteVolume(1) clears it
    uint8_t m_pad21[3];
    // +0x24 SaveAndMuteVolume_maybe keeps m_fSoundsVolume here, RestoreSavedVolume_maybe puts it back
    // (XXL2 m_fSaveSoundsVolume _maybe)
    float m_fSaveSoundsVolume;
    // +0x28 00GLC.KP3 (mode 3), one 12-byte read; 1.0 each. Volume factors: [0] music-flagged sounds,
    // [2] the other sounds (SoundVoice_ApplyParameters_maybe); [1] unread by the voices (speech _maybe)
    float m_unk28[3];
    float m_unk34[3];   // +0x34 GAME.KP3 (mode 1), one 12-byte read; 0.35 each; the same roles as m_unk28
    uint8_t m_unk40;    // +0x40 InitializeModule 0; set: the sound manager is off (Update skips the job-queue pause)
    uint8_t m_pad41[3];
};
DOTD_ASSERT_SIZE(CKSoundManager, 0x44);
DOTD_ASSERT_OFFSET(CKSoundManager, m_pOutput, 0x04);
DOTD_ASSERT_OFFSET(CKSoundManager, m_pVoiceManager, 0x08);
DOTD_ASSERT_OFFSET(CKSoundManager, m_pSoundStreamManager, 0x0c);
DOTD_ASSERT_OFFSET(CKSoundManager, m_fSoundsVolume, 0x10);
DOTD_ASSERT_OFFSET(CKSoundManager, m_unk1c, 0x1c);
DOTD_ASSERT_OFFSET(CKSoundManager, m_fSaveSoundsVolume, 0x24);
DOTD_ASSERT_OFFSET(CKSoundManager, m_unk28, 0x28);
DOTD_ASSERT_OFFSET(CKSoundManager, m_unk34, 0x34);
DOTD_ASSERT_OFFSET(CKSoundManager, m_unk40, 0x40);

// C1.6 gm: the sound calls the options make (family audio ports them; minimal bodies in
// k2000/stubs/BootStubs.cpp until then).
// 0x00113298 CKSoundManager_SetVolumes_maybe: master on the output (0x114518), music (0x117040) and speech
// (0x116e30) on the stream manager, then the sounds volume clamped to [0, 1] into +0x10, or into +0x24
// while muted (+0x1f set and +0x20 clear).
void CKSoundManager_SetVolumes(float master, float music, float speech, float sounds, CKSoundManager* manager);
// 0x001145a8 SoundOutput_GetOutputMode_maybe: 1 without a driver; the PS3 driver reports 6, which the
// function's table turns into 5.
int32_t SoundOutput_GetOutputMode(CKSoundOutput* output);
// 0x00114660 SoundOutput_SetOutputMode_maybe: the driver's output (1..4 -> 2..5, else 1; KStub_Nop_6eb040 on the PS3).
void SoundOutput_SetOutputMode(CKSoundOutput* output, int32_t mode);
// 0x00114508 KStub_Return0_114508: InitDefaultOptions' output mode.
inline int32_t KStub_Return0_114508(CKSoundOutput* /*output*/) { return 0; }
