// CKCinematicScene.h - a cinematic scene (key 0x94c, vtable 0xb1ac18, size 0x8c). Original unit:
// CKCinematicScene.cpp. XXL2: K/KServices/KServiceCinematic/CKCinematicScene.h; the members below are
// XXL2's in XXL2's load order, plus DotD's +0x22, +0x24, +0x40, two more trigger starters (+0x68,
// +0x70), +0x78 and +0x88.
#pragma once
#include <cstdint>

#include "k2000/core/IKSerializable.h"
#include "k2000/core/Layout.h"
#include "k2000/services/CTriggerStarter.h"

class IKFile;
class IKCinematicElement;
class CKCinematicSceneData;
class IKTime;

class CKCinematicScene : public IKSerializable {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x25)
    DOTD_DECLARE_FACTORIES(CKCinematicScene)
    // vt+0x40 0x0016b3c0 CKCinematicScene_GetInfo: the trigger values 5 (the scene plays).
    int32_t GetInfo(IKInfo* info, int32_t request) override;
    int32_t IsKindOfClass(uint32_t key) override { return key == kClassKey || key == 0xc; }  // 0x9a8c98

    CKCinematicScene();  // 0x0016b618 CKCinematicScene_Create (the constructor inlined)
    ~CKCinematicScene() override {}
    // vt+0x10 0x0016b4b8 CKCinematicScene_Destroy: the running list unlinked (each element's +0x04 cleared) and emptied,
    // then the three reference arrays deleted (the pointers are kept, as the original's).
    void Destroy() override;

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x0016d3b0 CKCinematicScene_Load
    // vt+0x24 0x0016ad20 CKCinematicScene_RecursiveRegistration: for type 0 the scene registers itself with the saving
    // manager, then every element and every scene data (vt+0x24 with 0), the start door when there is one and the sound
    // dictionary (not null-checked). The three trigger starters' registration (KStub_Return1_2361b0) does nothing.
    void RecursiveRegistration(int32_t type) override;

    void ResetRuntimeState();  // 0x00168ec0 CKCinematicScene_ResetRuntimeState
    // 0x0016b3a8 CKCinematicScene_ClearFlag22Bit5_maybe
    void ClearFlag22Bit5() { m_unk22 = static_cast<uint16_t>(m_unk22 & 0xffdf); }
    // vt+0x1c 0x0016cbc0 CKCinematicScene_MessageProc: a trigger action's message 0x500 starts the scene, 0x501 stops it.
    int32_t MessageProc(uint16_t message, void* data) override;
    int32_t PostLoad(int32_t type) override;              // vt+0x30 0x0016b418 CKCinematicScene_PostLoad  (see the .cpp)
    void SetDefaultState(int32_t flag) override;          // vt+0x38 0x0016b150 CKCinematicScene_SetDefaultState
    int32_t SetGameState(const SApplyGameState* state) override;  // vt+0x3c 0x0016b1a8 CKCinematicScene_SetGameState

    // 0x0016cc48 CKCinematicScene_ReinitBlocksRuntime_maybe: vt+0x54 of every element of the scene.
    void ReinitBlocksRuntime();
    // 0x0016c1d8 CKCinematicScene_Start: the scene begins if its sector is current and it is not playing (or is
    // fading out): listeners told, the entry transition started, the first element activated, the end trigger queued.
    void Start();
    // 0x0016c928 CKCinematicScene_Update: one frame of a playing scene (the fade, the transition, the running elements).
    void Update(IKTime* time);
    // 0x00169ef8 CKCinematicScene_UpdateTransition_maybe: the bands' entry / exit animation (modes of m_baBlackBandData).
    void UpdateTransition(IKTime* time);
    // 0x0016a5d0 CKCinematicScene_StartEntryTransition_maybe: the bands set up for the entry mode and shown.
    void StartEntryTransition();
    // 0x0016baa8 CKCinematicScene_SetPlayingState_maybe: the actors locked or unlocked (SetActorsLocked), the
    // groups to put to sleep locked, input blocked and the game manager's state kept (flags +0x22), the scene
    // registered as blocking or not, the listeners told (what 1).
    void SetPlayingState(uint32_t playing);
    // 0x00169608 CKCinematicScene_SetActorsLocked_maybe: every actor hook (CKCinematicSceneData) locked or unlocked.
    void SetActorsLocked(uint32_t locked);
    // 0x001690b8 CKCinematicScene_GetNodeOutputs: the elements `node` activates (type 1) or stops (type 2): a slice of the
    // scene's element array from the node's indices; *count is the length.
    IKCinematicElement** GetNodeOutputs(uint32_t* count, int32_t type, IKCinematicElement* node);
    // 0x00169240 CKCinematicScene_AddActiveNode / 0x00169288 RemoveActiveNode: the list of running elements (+0x0c, linked by
    // the elements' +0x04); an element is in it at most once.
    void AddActiveNode(IKCinematicElement* node);
    void RemoveActiveNode(IKCinematicElement* node);
    // 0x0016b0c8 CKCinematicScene_PauseActiveNodes / 0x0016aff8 ResumeActiveNodes: vt+0x78 / vt+0x7c on every running element
    // with bit 1 set.
    void PauseActiveNodes();
    void ResumeActiveNodes();
    // 0x0016b218 CKCinematicScene_InterruptForTransition_maybe: a scene in its band transition ends it at once.
    void InterruptForTransition();
    // 0x0016cb48 CKCinematicScene_Skip_maybe: Stop(1), the chained scene (+0x78) started, the skip trigger queued.
    void Skip();
    // 0x0016bf28 CKCinematicScene_UpdateFadeStep_maybe: one step of the whole scene fading to (bit 9 of m_baData clear) or
    // from black (set) with the fade quad; at the end of the fade to black the actors are placed at their beacons.
    void UpdateFadeStep(IKTime* time);
    // 0x0016c4d8 CKCinematicScene_Stop: the running elements aborted, the playing state taken off, then the scene's
    // end (the end trigger +0x68 queued, the listeners told) or, with bands and not `stopImmediately`, its exit transition.
    void Stop(int32_t stopImmediately);
    // 0x0016c7f8 CKCinematicScene_ForceEnd_maybe: Stop(0) and the end state at once.
    void ForceEnd();
    // 0x00169980 CKCinematicScene_StartExitTransition_maybe: the bands (and the fade quad) set up for the exit mode
    // (bits 3-4 of m_baBlackBandData) and the exit transition (bit 6) started; `signal` queues the end trigger for the
    // slide mode.
    void StartExitTransition(int32_t signal);
    // 0x00169890 CKCinematicScene_StartFadeTransition_maybe: the fade to black of the whole scene started.
    void StartFadeTransition();
    // 0x0016bdb0 CKCinematicScene_EndImmediate_maybe: the scene's actors placed at their beacons and the scene ended at once.
    void EndImmediate();
    // 0x00169380 CKCinematicScene_ReleaseCamera_maybe: the scene gives the camera back (see the .cpp).
    void ReleaseCamera();
    // 0x0016acc8 CKCinematicScene_ReleaseSoundListener_maybe: the sound listener follows its object again.
    void ReleaseSoundListener();
    // 0x00169538 CKCinematicScene_SetLinkedHooksLocked_maybe: the scene's groups to put to sleep locked or unlocked.
    void SetLinkedHooksLocked(uint32_t locked);
    // 0x0016dba8 CKCinematicScene_AbortActiveNodes_maybe: the running elements aborted and the fade to black started.
    void AbortActiveNodes();
    // 0x0016b728 CKCinematicScene_PlaceActorAtBeacon_maybe: the actor of `data` put at its interrupt beacon.
    void PlaceActorAtBeacon(CKCinematicSceneData* data);
    // 0x0016b670 CKCinematicScene_SetChainedScenesFlag88_maybe: byte +0x88 of this scene and of every scene
    // chained after it (+0x78) set to `value`.
    void SetChainedScenesFlag88(uint8_t value);
    // 0x0016c448 CKCinematicScene_ResetNodesRuntime_maybe: every element's PreStart (vt+0x50).
    void ResetNodesRuntime();

    // m_baData (+0x20) bits: 0 the scene plays, 1 it plays only once, 2 it has played, 6 it has ended (Update),
    // 9 fading out (UpdateFadeStep), 13 the bands stay, 14 played (saved), 15 a start was requested (the service's
    // Update starts it).
    // m_unk22 (+0x22) bits: 1 the scene blocks the input and keeps the game manager's input state, 2 the input was
    // blocked before, 3 a blocking scene (AddBlockingScene), 4 it can be skipped, 5 the listeners were told its
    // playing state changed.
    // m_baBlackBandData (+0x34) bits: 0 bands, 1-2 entry mode (0 at once, 1 colour fade, 2 slide, 3 fade quad), 3-4 exit
    // mode, 5 entry transition running, 6 exit transition running, 7 fade running.

    IKSerializable** m_pCinematicPointerList;     // +0x04 IKCinematicElement* references (new[]); 0 when empty
    uint32_t m_ui32CinematicPointerLength;        // +0x08
    IKCinematicElement* m_pActiveNodes;           // +0x0c XXL2 TSNodeList<IKCinematicElement*> m_pCurrentList: the running elements; 0
    IKSerializable** m_apCinematicSceneData;      // +0x10 CKCinematicSceneData references (new[])
    uint32_t m_ui32HookNumber;                    // +0x14
    IKSerializable** m_apGroupToAsleep;           // +0x18 IKBaseGroup references (new[])
    uint32_t m_ui32GroupToAsleep;                 // +0x1c
    uint16_t m_baData;                            // +0x20 CBitArray16; ResetRuntimeState clears bits
    uint16_t m_unk22;                             // +0x22 DotD, read after m_baData
    uint8_t m_unk24;                              // +0x24 DotD; the constructor clears it
    uint8_t m_pad25[3];
    IKSerializable* m_pLastEvent;                 // +0x28 IKCinematicElement; ResetRuntimeState sets 0
    IKSerializable* m_pFirstBloc;                 // +0x2c the scene's CKStartDoor in the files
    uint32_t m_ui32SectorNum;                     // +0x30
    uint8_t m_baBlackBandData;                    // +0x34 CBitArray8; ResetRuntimeState keeps bits 0-4
    uint8_t m_pad35[3];
    uint32_t m_BandColor;                         // +0x38 CColor, read raw (the file's bytes: R, G, B, A)
    float m_fBandHeight;                          // +0x3c
    uint8_t m_unk40;                              // +0x40 DotD; ResetRuntimeState sets 0
    uint8_t m_ui8CurAlpha;                        // +0x41 ResetRuntimeState sets 0xff
    uint8_t m_pad42[2];
    float m_fAlphaSpeed;                          // +0x44 ResetRuntimeState sets 0
    float m_fAlphaAppearTime;                     // +0x48
    float m_fAlphaDisappearTime;                  // +0x4c
    float m_fCurCenterPos;                        // +0x50 ResetRuntimeState sets 0
    float m_fAppearTime;                          // +0x54
    float m_fDisappearTime;                       // +0x58
    float m_fTimeForFade;                         // +0x5c
    CTriggerStarter m_tsEnd;                      // +0x60
    CTriggerStarter m_tsUnk68;                    // +0x68 DotD
    CTriggerStarter m_tsUnk70;                    // +0x70 DotD
    IKSerializable* m_unk78;                      // +0x78 DotD reference, read last (after ResetRuntimeState)
    IKSerializable* m_pSoundDico;                 // +0x7c CKSoundDictionaryID
    uint8_t m_bNeedsUnlock;                       // +0x80 not read
    uint8_t m_bDesactivateCameraSector;           // +0x81
    uint8_t m_bListenerFollowsCamera;             // +0x82 DotD; Start sets it when the sound listener followed an object
    uint8_t m_pad83;
    float m_fCameraEndTransitionTime;             // +0x84
    uint8_t m_unk88;                              // +0x88 DotD; 0 in the constructor
    uint8_t m_pad89[3];
};
DOTD_ASSERT_SIZE(CKCinematicScene, 0x8c);
DOTD_ASSERT_OFFSET(CKCinematicScene, m_pCinematicPointerList, 0x04);
DOTD_ASSERT_OFFSET(CKCinematicScene, m_apCinematicSceneData, 0x10);
DOTD_ASSERT_OFFSET(CKCinematicScene, m_apGroupToAsleep, 0x18);
DOTD_ASSERT_OFFSET(CKCinematicScene, m_baData, 0x20);
DOTD_ASSERT_OFFSET(CKCinematicScene, m_unk24, 0x24);
DOTD_ASSERT_OFFSET(CKCinematicScene, m_pFirstBloc, 0x2c);
DOTD_ASSERT_OFFSET(CKCinematicScene, m_baBlackBandData, 0x34);
DOTD_ASSERT_OFFSET(CKCinematicScene, m_BandColor, 0x38);
DOTD_ASSERT_OFFSET(CKCinematicScene, m_ui8CurAlpha, 0x41);
DOTD_ASSERT_OFFSET(CKCinematicScene, m_fCurCenterPos, 0x50);
DOTD_ASSERT_OFFSET(CKCinematicScene, m_fTimeForFade, 0x5c);
DOTD_ASSERT_OFFSET(CKCinematicScene, m_tsEnd, 0x60);
DOTD_ASSERT_OFFSET(CKCinematicScene, m_tsUnk70, 0x70);
DOTD_ASSERT_OFFSET(CKCinematicScene, m_unk78, 0x78);
DOTD_ASSERT_OFFSET(CKCinematicScene, m_pSoundDico, 0x7c);
DOTD_ASSERT_OFFSET(CKCinematicScene, m_bDesactivateCameraSector, 0x81);
DOTD_ASSERT_OFFSET(CKCinematicScene, m_fCameraEndTransitionTime, 0x84);
DOTD_ASSERT_OFFSET(CKCinematicScene, m_unk88, 0x88);
