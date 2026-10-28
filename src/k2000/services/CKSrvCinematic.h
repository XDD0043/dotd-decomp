// CKSrvCinematic.h - the cinematic service (key 0x101, vtable 0xb1ab68, size 0x70). Original unit:
// CKSrvCinematic.cpp (0x166328-0x168e40). XXL2: K/KServices/KServiceCinematic/CKSrvCinematic.h: the
// scene list, the three black-band billboards and the vector of objects to warn are read in the same
// order; the black-band callbacks and the input dico are not in DotD, the +0x4c/+0x64 vectors are
// DotD's.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/services/IKService.h"
#include "k2000/util/TVector.h"

class CKCinematicScene;
class CKPlayVideoCinematicBloc;
class IKCinematicElement;
class IKTime;

// XXL2 CSmoothedCColorLinear (0x1c bytes): the black bands' colour moving to its target at m_fSpeed (in units of
// 255 per second); the floats are the exact current channels (the bytes follow them).
struct SBandColor {
    uint8_t m_acTarget[4];   // +0x00 R, G, B, A as the file stores them
    uint8_t m_acCurrent[4];  // +0x04
    float m_fSpeed;          // +0x08
    float m_afCurrent[4];    // +0x0c R, G, B, A
};
DOTD_ASSERT_SIZE(SBandColor, 0x1c);

class CKSrvCinematic : public IKService {
public:
    DOTD_CLASS_KEY(kCategoryService, 0x4)
    DOTD_DECLARE_FACTORIES(CKSrvCinematic)

    CKSrvCinematic();  // 0x00166be8 CKSrvCinematic_Construct
    ~CKSrvCinematic() override {}

    void Destroy() override;  // vt+0x10 0x00167548 CKSrvCinematic_Destroy
    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x001685e8 CKSrvCinematic_Load
    int32_t PostLoad(int32_t type) override;            // vt+0x30 0x00166ab8 CKSrvCinematic_PostLoad
    void SetDefaultState(int32_t flag) override;        // vt+0x38 0x00166c98 CKSrvCinematic_SetDefaultState
    void Start() override;                              // vt+0x50 0x167338 CKSrvCinematic_Start
    void Restart() override;                            // vt+0x54 0x167320 CKSrvCinematic_Restart
    void PreRestart() override;                         // vt+0x5c 0x166e48 CKSrvCinematic_PreRestart
    void Stop() override;                               // vt+0x68 0x166dc0 CKSrvCinematic_Stop
    void Pause() override;                              // vt+0x70 0x166ff8 CKSrvCinematic_Pause
    void Resume() override;                             // vt+0x78 0x166f60 CKSrvCinematic_Resume
    // vt+0x7c 0x168048 UpdateCKSrvCinematic: the bands, the scenes' updates, the requested skips and starts.
    void Update(IKTime* time) override;
    // vt+0x8c 0x001673d8 CKSrvCinematic_SectorUnload: the scenes of that sector that play are stopped.
    void SectorUnload(int32_t sector) override;
    // 0x00167698 CKSrvCinematic_ForceEndAllScenes_maybe (vt+0x64): every playing scene ended at once.
    void ForceEndAllScenes();
    // vt+0x94 0x00166870 CKSrvCinematic_InitializeService. Ported: Load reads into the block it
    // allocates for m_vpSerializableToWarn.
    int32_t InitializeService() override;
    void DestroyService() override;                     // vt+0x98 0x1678b0 CKSrvCinematic_DestroyService

    // 0x00166810 CKSrvCinematic_StartScene_maybe (the first argument is the service) / 0x00166838
    // StartSceneByIndex_maybe: CKCinematicScene_Start on the scene.
    void StartScene(CKCinematicScene* scene);
    void StartSceneByIndex(uint32_t index);
    // 0x00166f10 CKSrvCinematic_StopSceneByIndex_maybe: CKCinematicScene_Stop(0) when it plays.
    void StopSceneByIndex(uint32_t index);
    // 0x00166570 CKSrvCinematic_IsSkippableScenePlaying_maybe
    uint8_t IsSkippableScenePlaying() const;
    // 0x00166928 Input_IsStartPressedAnyPlayer_maybe (the service argument is unused)
    static uint8_t IsStartPressedAnyPlayer();
    // 0x001665e8 CKSrvCinematic_GetScenes_maybe
    IKSerializable** GetScenes(uint32_t* count) const {
        *count = m_ui32SceneNumber;
        return m_pSceneList;
    }
    // 0x00166d50 CKSrvCinematic_InterruptPlayingScenes_maybe: CKCinematicScene_InterruptForTransition on every scene.
    void InterruptPlayingScenes();
    // 0x00166780 / 0x001666d0 ShowLetterboxBars_maybe / RemoveCinemaBars_maybe: the two black bands in or out of
    // the UI manager's first scene (+0xa70); bit 0 of m_baData says they are in.
    void ShowLetterboxBars();
    void RemoveCinemaBars();
    // 0x00166748 / 0x001675b0 ShowFadeQuad_maybe / HideFadeQuad_maybe: the fade quad in or out of the UI manager's
    // scene +0xa68.
    void ShowFadeQuad();
    void HideFadeQuad();
    // 0x00167090 / 0x00167208 AddBlockingScene_maybe / RemoveBlockingScene_maybe: the first blocking scene makes the
    // heroes invulnerable (the mask saved in m_ui32SavedInvulnerableMask), the last one puts them back.
    void AddBlockingScene(CKCinematicScene* scene);
    void RemoveBlockingScene(CKCinematicScene* scene);
    // 0x00167498 CKSrvCinematic_NotifyListeners: MessageProc(0x500 | what, scene) to every object to warn
    // (what 0 = scene started, 1 = playing state changed, 2 = scene ended).
    void NotifyListeners(CKCinematicScene* scene, uint8_t what);
    // 0x00167798 CKSrvCamera_AddOrRemoveCameraOwner_maybe (in the cinematic unit): the scene put in (remove == 0) or out of
    // the camera service's list of cinematic camera owners.
    void AddOrRemoveCameraOwner(CKCinematicScene* scene, int32_t remove);
    // 0x00167940 CKSrvCinematic_ActivateNode(service, source, node): the node is activated through its Activate (vt+0x60)
    // unless its actor is missing; then the element is skipped and its outputs go on (the nodes seen are kept in
    // m_vpActivationGuard until the chain that started with source == null ends).
    void ActivateNode(IKCinematicElement* source, IKCinematicElement* node);
    // 0x00167d18 CKSrvCinematic_UpdateVideoSkipPrompt_maybe (C2.3 step 2).
    int32_t UpdateVideoSkipPrompt();
    // 0x00166680 / 0x001666a8 FinishCurrentVideo_maybe / PlayNextVideo_maybe: the current video bloc's.
    void FinishCurrentVideo();
    void PlayNextVideo();

    uint8_t m_baData;                           // +0x0c XXL2 CBitArray8: bit 0 bands in, bit 1 interrupting, bit 2 skip prompt
                                                // open, bit 3 skip requested, bit 4/5 set by the scenes' fades; Load clears it
    uint8_t m_pad0d[3];                         // +0x0d never written (heap residue on the live dump)
    IKSerializable** m_pSceneList;              // +0x10 CKCinematicScene* (OperatorNewArray)
    uint32_t m_ui32SceneNumber;                 // +0x14
    IKSerializable* m_pBlackBandBillBoard[3];   // +0x18 CBillboard2d*: top band, bottom band, fade quad
    SBandColor m_scBandColor;                   // +0x24 XXL2 CSmoothedCColorLinear (0x1c bytes); PostLoad sets it
    TVector<IKSerializable*, 2> m_vpSerializableToWarn;  // +0x40
    TVector<CKCinematicScene*, 4> m_vpBlockingScenes;    // +0x4c the playing scenes that block the game; Load sets the length to 0
    int32_t m_unk58;                            // +0x58 read from GAME.KP3 (-1); XXL2 m_i32TextStopId _maybe
    CKPlayVideoCinematicBloc* m_pCurrentVideoBloc;  // +0x5c the bloc whose video plays (InitializeService sets 0)
    uint32_t m_ui32SavedInvulnerableMask;       // +0x60 Load sets 0; AddBlockingScene saves the heroes' mask here
    TVector<IKCinematicElement*, 2> m_vpActivationGuard;  // +0x64 ActivateNode's visited list
};
DOTD_ASSERT_SIZE(CKSrvCinematic, 0x70);
DOTD_ASSERT_OFFSET(CKSrvCinematic, m_ui32Priority, 0x08);
DOTD_ASSERT_OFFSET(CKSrvCinematic, m_baData, 0x0c);
DOTD_ASSERT_OFFSET(CKSrvCinematic, m_pSceneList, 0x10);
DOTD_ASSERT_OFFSET(CKSrvCinematic, m_ui32SceneNumber, 0x14);
DOTD_ASSERT_OFFSET(CKSrvCinematic, m_pBlackBandBillBoard, 0x18);
DOTD_ASSERT_OFFSET(CKSrvCinematic, m_scBandColor, 0x24);
DOTD_ASSERT_OFFSET(CKSrvCinematic, m_vpSerializableToWarn, 0x40);
DOTD_ASSERT_OFFSET(CKSrvCinematic, m_vpBlockingScenes, 0x4c);
DOTD_ASSERT_OFFSET(CKSrvCinematic, m_unk58, 0x58);
DOTD_ASSERT_OFFSET(CKSrvCinematic, m_pCurrentVideoBloc, 0x5c);
DOTD_ASSERT_OFFSET(CKSrvCinematic, m_ui32SavedInvulnerableMask, 0x60);
DOTD_ASSERT_OFFSET(CKSrvCinematic, m_vpActivationGuard, 0x64);
