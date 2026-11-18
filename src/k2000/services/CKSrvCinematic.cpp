// CKSrvCinematic.cpp - reconstructed original translation unit 0x166328-0x168e40 (GAME_TOC1, main_toc1), 52 functions, 51 live.
// Primary class: CKSrvCinematic  key 0x101  category Service  size 0x70  vtable 0xb1ab68
// Other owners: Input (1), CKSrvCamera (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x166328  CKSrvCinematic_Delete
//   [ ] 0x166378  CKSrvCinematic_ReinitRuntime_2  [dead]
//   [x] 0x166390  CKSrvCinematic_RecursiveRegistration
//   [x] 0x166570  CKSrvCinematic_IsSkippableScenePlaying_maybe
//   [x] 0x1665e8  CKSrvCinematic_GetScenes_maybe
//   [ ] 0x1665f8  RegisterCKSrvCinematicClass
//   [ ] 0x166670  _GLOBAL__I_166670
//   [x] 0x166680  CKSrvCinematic_FinishCurrentVideo_maybe
//   [x] 0x1666a8  CKSrvCinematic_PlayNextVideo_maybe
//   [x] 0x1666d0  CKSrvCinematic_RemoveCinemaBars_maybe
//   [x] 0x166748  CKSrvCinematic_ShowFadeQuad_maybe
//   [x] 0x166780  CKSrvCinematic_ShowLetterboxBars_maybe
//   [x] 0x166810  CKSrvCinematic_StartScene_maybe
//   [x] 0x166838  CKSrvCinematic_StartSceneByIndex_maybe
//   [x] 0x166870  CKSrvCinematic_InitializeService
//   [x] 0x166928  Input_IsStartPressedAnyPlayer_maybe
//   [x] 0x166ab8  CKSrvCinematic_PostLoad
//   [x] 0x166b40  CKSrvCinematic_DeleteArray
//   [x] 0x166be8  CKSrvCinematic_Construct
//   [x] 0x166c98  CKSrvCinematic_SetDefaultState
//   [x] 0x166d50  CKSrvCinematic_InterruptPlayingScenes_maybe
//   [x] 0x166dc0  CKSrvCinematic_Stop
//   [x] 0x166e48  CKSrvCinematic_PreRestart
//   [x] 0x166f10  CKSrvCinematic_StopSceneByIndex_maybe
//   [x] 0x166f60  CKSrvCinematic_Resume
//   [x] 0x166ff8  CKSrvCinematic_Pause
//   [x] 0x167090  CKSrvCinematic_AddBlockingScene_maybe
//   [x] 0x167208  CKSrvCinematic_RemoveBlockingScene_maybe
//   [x] 0x167320  CKSrvCinematic_Restart
//   [x] 0x167338  CKSrvCinematic_Start
//   [x] 0x1673d8  CKSrvCinematic_SectorUnload
//   [x] 0x167498  CKSrvCinematic_NotifyListeners
//   [x] 0x167548  CKSrvCinematic_Destroy
//   [x] 0x1675b0  CKSrvCinematic_HideFadeQuad_maybe
//   [x] 0x1675e8  CKSrvCinematic_Construct_2  (the not-in-charge copy of the constructor 0x166be8: CKSrvCinematic())
//   [x] 0x167698  CKSrvCinematic_ForceEndAllScenes_maybe
//   [x] 0x167778  CKSrvCinematic_MessageProc
//   [x] 0x167780  CKSrvCinematic_PreSectorLoaded  (PreSectorLoaded: empty, the IKUpdatable default)
//   [x] 0x167788  CKSrvCinematic_SectorLoaded  (SectorLoaded: empty, the IKUpdatable default)
//   [x] 0x167790  CKSrvCinematic_PostSectorUnload  (PostSectorUnload: empty, the IKUpdatable default)
//   [x] 0x167798  CKSrvCamera_AddOrRemoveCameraOwner_maybe
//   [x] 0x1678b0  CKSrvCinematic_DestroyService
//   [x] 0x167940  CKSrvCinematic_ActivateNode
//   [x] 0x167d18  CKSrvCinematic_UpdateVideoSkipPrompt_maybe
//   [x] 0x168048  UpdateCKSrvCinematic
//   [ ] 0x168320  CKSrvCinematic_Save
//   [x] 0x1685e8  CKSrvCinematic_Load
//   [x] 0x168968  CKSrvCinematic_CreateArray
//   [x] 0x168ad0  CKSrvCinematic_Create
//   [x] 0x168b98  CKSrvCinematic_Destructor  (~CKSrvCinematic)
//   [x] 0x168c78  CKSrvCinematic_DestructBody  (~CKSrvCinematic)
//   [x] 0x168d58  CKSrvCinematic_DeletingDestructor  (~CKSrvCinematic + delete)
//
//   [ ] 0x9a8c30  CKSrvCinematic_IsKindOfClass  [inline]
//   [ ] 0x9a8c68  CKSrvCinematic_GetClassType  [inline]
//   [ ] 0x9a8c70  CKSrvCinematic_GetClassID  [inline]
#include "k2000/services/CKSrvCinematic.h"

#include <cstring>

#include "k2000/cameras/CKSrvCamera.h"
#include "k2000/graphical/fx/CBillboard2d.h"
#include "k2000/graphical/ui/CManager2d.h"
#include "k2000/graphical/ui/CScene2d.h"
#include "k2000/io/IKFile.h"
#include "k2000/logic/CKCinematicSceneData.h"
#include "k2000/logic/CDefaultGameManager.h"
#include "k2000/logic/CKCinematicScene.h"
#include "k2000/logic/CKSavingManager.h"
#include "k2000/memory/Mem.h"
#include "k2000/misc/Engine.h"
#include "k2000/misc/IKCinematicElement.h"
#include "k2000/cinematics/CKPlayVideoCinematicBloc.h"
#include "k2000/input/CKInputDico.h"
#include "k2000/managers/CKInput.h"
#include "k2000/misc/CKGameLoop.h"
#include "k2000/misc/JobQueue.h"
#include "k2000/system/CTimeManager.h"
#include "k2000/system/IKTime.h"

// 0x00166be8 CKSrvCinematic_Construct (the same stores inlined in 0x168ad0 CKSrvCinematic_Create).
CKSrvCinematic::CKSrvCinematic() {
    m_vpSerializableToWarn.m_ui32NbElt = 2;
    m_vpSerializableToWarn.m_pBlock = nullptr;
    m_vpSerializableToWarn.m_ui32NbUsedElt = 0;
    m_vpBlockingScenes.m_ui32NbElt = 4;
    m_vpBlockingScenes.m_pBlock = nullptr;
    m_vpBlockingScenes.m_ui32NbUsedElt = 0;
    m_vpActivationGuard.m_ui32NbElt = 2;
    m_vpActivationGuard.m_ui32NbUsedElt = 0;
    m_vpActivationGuard.m_pBlock = nullptr;
    m_ui32Priority = 0x6e;
    Engine_SetSrvCinematic(this);
}

// 0x00166870 CKSrvCinematic_InitializeService: clears the scene and billboard fields and allocates
// the first blocks of the two vectors (2 and 4 elements).
int32_t CKSrvCinematic::InitializeService() {
    m_pSceneList = nullptr;
    m_ui32SceneNumber = 0;
    m_baData = 0;
    m_pBlackBandBillBoard[0] = nullptr;
    m_pBlackBandBillBoard[1] = nullptr;
    m_pBlackBandBillBoard[2] = nullptr;
    m_baData &= 0xfe;
    m_vpSerializableToWarn.m_ui32NbElt = 2;
    m_vpSerializableToWarn.m_pBlock =
        static_cast<IKSerializable**>(Mem_AllocAligned16(2 * static_cast<uint32_t>(sizeof(IKSerializable*))));
    m_vpBlockingScenes.m_ui32NbElt = 4;
    m_vpBlockingScenes.m_pBlock = static_cast<CKCinematicScene**>(Mem_AllocAligned16(4 * static_cast<uint32_t>(sizeof(IKSerializable*))));
    m_pCurrentVideoBloc = nullptr;
    m_unk58 = -1;
    return 1;
}

// 0x00167548 CKSrvCinematic_Destroy: the scene list freed, the flags and the black-band billboards cleared.
void CKSrvCinematic::Destroy() {
    if (m_pSceneList != nullptr) {
        delete[] m_pSceneList;
        m_pSceneList = nullptr;
    }
    m_baData = 0;
    m_pBlackBandBillBoard[0] = nullptr;
    m_pBlackBandBillBoard[1] = nullptr;
    m_pBlackBandBillBoard[2] = nullptr;
}

// 0x001685e8 CKSrvCinematic_Load. A level gives the scenes, the three black-band billboards and the
// objects to warn; GAME.KP3 gives one word.
int32_t CKSrvCinematic::Load(IKFile* file, int32_t type) {
    if (type == K_GAME_PLATEFORMS) {
        ReadS32LE(file, &m_unk58);
        return 1;
    }
    if (type != K_LEVEL_PLATEFORMS) return 1;
    ReadU32LE(file, &m_ui32SceneNumber);
    if (m_ui32SceneNumber == 0) {
        m_pSceneList = nullptr;
    } else {
        m_pSceneList = new IKSerializable*[m_ui32SceneNumber];
        IKFile_ReadObjectRefArray(file, m_pSceneList, m_ui32SceneNumber);
    }
    IKFile_ReadObjectRefArray(file, m_pBlackBandBillBoard, 3);
    uint32_t count = 0;
    ReadU32LE(file, &count);
    if (m_vpSerializableToWarn.m_ui32NbElt < count) {  // TVector growth: to the next even count above
        uint32_t capacity = (count & ~1u) + 2;
        if (capacity == 0) capacity = 2;
        m_vpSerializableToWarn.m_pBlock = static_cast<IKSerializable**>(Mem_ReallocAligned16(
            m_vpSerializableToWarn.m_pBlock, capacity * static_cast<uint32_t>(sizeof(IKSerializable*))));
        m_vpSerializableToWarn.m_ui32NbElt = capacity;
    }
    m_vpSerializableToWarn.m_ui32NbUsedElt = count;
    if (count != 0) IKFile_ReadObjectRefArray(file, m_vpSerializableToWarn.m_pBlock, count);
    m_ui32SavedInvulnerableMask = 0;
    m_baData = 0;
    m_vpBlockingScenes.m_ui32NbUsedElt = 0;
    return 1;
}

namespace {
CKCinematicScene* SceneAt(CKSrvCinematic* service, uint32_t index) {
    return static_cast<CKCinematicScene*>(service->m_pSceneList[index]);
}
}  // namespace

// 0x00166dc0 CKSrvCinematic_Stop: every scene's bit 5 of +0x22 cleared and its blocs reinitialised.
void CKSrvCinematic::Stop() {
    for (uint32_t i = 0; i < m_ui32SceneNumber; ++i) {
        CKCinematicScene* scene = SceneAt(this, i);
        scene->ClearFlag22Bit5();
        scene->ReinitBlocksRuntime();
    }
}

// 0x001673d8 CKSrvCinematic_SectorUnload: a scene that plays (bit 0 of its flags) in the unloading sector
// is stopped; bit 15 of every scene's flags cleared.
void CKSrvCinematic::SectorUnload(int32_t sector) {
    for (uint32_t i = 0; i < m_ui32SceneNumber; ++i) {
        CKCinematicScene* scene = SceneAt(this, i);
        if ((scene->m_baData & 1) != 0 && static_cast<int32_t>(scene->m_ui32SectorNum) == sector) scene->Stop(0);
        scene->m_baData = static_cast<uint16_t>(scene->m_baData & 0x7fff);
    }
}

// 0x00167698 CKSrvCinematic_ForceEndAllScenes_maybe
void CKSrvCinematic::ForceEndAllScenes() {
    for (uint32_t i = 0; i < m_ui32SceneNumber; ++i) {
        CKCinematicScene* scene = SceneAt(this, i);
        if ((scene->m_baData & 1) != 0) scene->ForceEnd();
        scene->m_baData = static_cast<uint16_t>(scene->m_baData & 0x7fff);
    }
    m_baData = static_cast<uint8_t>(m_baData & 0xfe);
}

namespace {
CManager2d* Ui() { return g_pEngine->m_manager2d; }
}  // namespace

// 0x00166ab8 CKSrvCinematic_PostLoad: the level type sets the bands' colour to the shared white (0x00c50dfc, all
// bytes 0xff) and its float channels to 255.0, with no speed.
int32_t CKSrvCinematic::PostLoad(int32_t type) {
    if (type == 0) {
        std::memset(m_scBandColor.m_acTarget, 0xff, 4);
        std::memset(m_scBandColor.m_acCurrent, 0xff, 4);
        m_scBandColor.m_fSpeed = 0.0f;
        for (int i = 0; i < 4; ++i) m_scBandColor.m_afCurrent[i] = 255.0f;
    }
    return 1;
}

// 0x00166c98 CKSrvCinematic_SetDefaultState: every scene's SetDefaultState (vt+0x38); bit 1 of the flags cleared.
void CKSrvCinematic::SetDefaultState(int32_t flag) {
    for (uint32_t i = 0; i < m_ui32SceneNumber; ++i) SceneAt(this, i)->SetDefaultState(flag);
    m_baData = static_cast<uint8_t>((m_baData & 0xfc) | (m_baData & 1));
}

// 0x00167338 CKSrvCinematic_Start: no video bloc, every scene's elements reset (PreStart), no flags.
void CKSrvCinematic::Start() {
    m_pCurrentVideoBloc = nullptr;
    for (uint32_t i = 0; i < m_ui32SceneNumber; ++i) {
        CKCinematicScene* scene = SceneAt(this, i);
        if (scene != nullptr) scene->ResetNodesRuntime();
    }
    m_ui32SavedInvulnerableMask = 0;
    m_baData = 0;
    m_vpBlockingScenes.m_ui32NbUsedElt = 0;
}

// 0x00167320 CKSrvCinematic_Restart
void CKSrvCinematic::Restart() {
    m_ui32SavedInvulnerableMask = 0;
    m_baData = 0;
    m_vpBlockingScenes.m_ui32NbUsedElt = 0;
}

// 0x00166e48 CKSrvCinematic_PreRestart: a playing scene is stopped at once; every scene's bit 15 cleared.
void CKSrvCinematic::PreRestart() {
    for (uint32_t i = 0; i < m_ui32SceneNumber; ++i) {
        CKCinematicScene* scene = SceneAt(this, i);
        if ((scene->m_baData & 1) != 0) scene->Stop(1);
        scene->m_baData = static_cast<uint16_t>(scene->m_baData & 0x7fff);
    }
}

// 0x00166ff8 CKSrvCinematic_Pause / 0x00166f60 CKSrvCinematic_Resume: the playing scenes' running elements.
void CKSrvCinematic::Pause() {
    for (uint32_t i = 0; i < m_ui32SceneNumber; ++i) {
        CKCinematicScene* scene = SceneAt(this, i);
        if ((scene->m_baData & 1) != 0) scene->PauseActiveNodes();
    }
}
void CKSrvCinematic::Resume() {
    for (uint32_t i = 0; i < m_ui32SceneNumber; ++i) {
        CKCinematicScene* scene = SceneAt(this, i);
        if ((scene->m_baData & 1) != 0) scene->ResumeActiveNodes();
    }
}

// 0x001678b0 CKSrvCinematic_DestroyService: the two vectors (the warned objects and the blocking scenes) freed.
void CKSrvCinematic::DestroyService() {
    if (m_vpSerializableToWarn.m_pBlock != nullptr) {
        Mem_FreeAligned16(m_vpSerializableToWarn.m_pBlock);
        m_vpSerializableToWarn.m_pBlock = nullptr;
    }
    m_vpSerializableToWarn.m_ui32NbUsedElt = 0;
    m_vpSerializableToWarn.m_pBlock = nullptr;
    if (m_vpBlockingScenes.m_pBlock != nullptr) {
        Mem_FreeAligned16(m_vpBlockingScenes.m_pBlock);
        m_vpBlockingScenes.m_pBlock = nullptr;
    }
    m_vpBlockingScenes.m_ui32NbUsedElt = 0;
    m_vpBlockingScenes.m_pBlock = nullptr;
}

// 0x00166810 CKSrvCinematic_StartScene_maybe / 0x00166838 StartSceneByIndex_maybe / 0x00166f10 StopSceneByIndex_maybe
void CKSrvCinematic::StartScene(CKCinematicScene* scene) { scene->Start(); }
void CKSrvCinematic::StartSceneByIndex(uint32_t index) { SceneAt(this, index)->Start(); }
void CKSrvCinematic::StopSceneByIndex(uint32_t index) {
    CKCinematicScene* scene = SceneAt(this, index);
    if ((scene->m_baData & 1) != 0) scene->Stop(0);
}

// 0x00166570 CKSrvCinematic_IsSkippableScenePlaying_maybe: a scene plays (bit 0) and can be skipped (+0x22 bit 4).
uint8_t CKSrvCinematic::IsSkippableScenePlaying() const {
    for (uint32_t i = 0; i < m_ui32SceneNumber; ++i) {
        const CKCinematicScene* scene = static_cast<const CKCinematicScene*>(m_pSceneList[i]);
        if ((scene->m_baData & 1) != 0 && (scene->m_unk22 & 0x10) != 0) return 1;
    }
    return 0;
}

// 0x00166d50 CKSrvCinematic_InterruptPlayingScenes_maybe
void CKSrvCinematic::InterruptPlayingScenes() {
    for (uint32_t i = 0; i < m_ui32SceneNumber; ++i) SceneAt(this, i)->InterruptForTransition();
}

// 0x00166780 CKSrvCinematic_ShowLetterboxBars_maybe: the two bands into the UI manager's first scene (+0xa70).
void CKSrvCinematic::ShowLetterboxBars() {
    CScene2d* scene = static_cast<CScene2d*>(Ui()->m_pFirstScene);
    if ((m_baData & 1) == 0) {
        scene->AddChild(static_cast<CBillboard2d*>(m_pBlackBandBillBoard[0]));
        scene->AddChild(static_cast<CBillboard2d*>(m_pBlackBandBillBoard[1]));
        m_baData = static_cast<uint8_t>((m_baData & 0xfe) | 1);
    }
}

// 0x001666d0 CKSrvCinematic_RemoveCinemaBars_maybe
void CKSrvCinematic::RemoveCinemaBars() {
    CScene2d* scene = static_cast<CScene2d*>(Ui()->m_pFirstScene);
    scene->RemoveChild(static_cast<CBillboard2d*>(m_pBlackBandBillBoard[0]));
    scene->RemoveChild(static_cast<CBillboard2d*>(m_pBlackBandBillBoard[1]));
    m_baData = static_cast<uint8_t>(m_baData & 0xfe);
}

// 0x00166748 CKSrvCinematic_ShowFadeQuad_maybe / 0x001675b0 HideFadeQuad_maybe: the fade quad in the UI manager's
// scene +0xa68.
void CKSrvCinematic::ShowFadeQuad() {
    static_cast<CScene2d*>(Ui()->m_unkA68)->AddChild(static_cast<CBillboard2d*>(m_pBlackBandBillBoard[2]));
}
void CKSrvCinematic::HideFadeQuad() {
    static_cast<CScene2d*>(Ui()->m_unkA68)->RemoveChild(static_cast<CBillboard2d*>(m_pBlackBandBillBoard[2]));
}

// 0x00167090 CKSrvCinematic_AddBlockingScene_maybe
void CKSrvCinematic::AddBlockingScene(CKCinematicScene* scene) {
    CDefaultGameManager* manager = g_pEngine->m_gameManager;
    if (scene == nullptr) return;
    if (m_vpBlockingScenes.m_ui32NbUsedElt == 0) {
        manager->GetHeroesInvulnerableMask(&m_ui32SavedInvulnerableMask);  // vt+0x1f0
        manager->SetAllHeroesInvulnerable(1);                              // vt+0x1f8
    }
    const uint32_t count = m_vpBlockingScenes.m_ui32NbUsedElt;
    for (uint32_t i = 0; i < count; ++i) {
        if (m_vpBlockingScenes.m_pBlock[i] == scene) return;
    }
    if (m_vpBlockingScenes.m_ui32NbElt == count) {  // grows by 4 elements
        uint32_t capacity = m_vpBlockingScenes.m_ui32NbElt + 4;
        if (capacity == 0) capacity = 4;
        m_vpBlockingScenes.m_pBlock = static_cast<CKCinematicScene**>(
            Mem_ReallocAligned16(m_vpBlockingScenes.m_pBlock, (capacity & 0x3fffffffu) << 2));
        m_vpBlockingScenes.m_ui32NbElt = capacity;
    }
    m_vpBlockingScenes.m_pBlock[count] = scene;
    ++m_vpBlockingScenes.m_ui32NbUsedElt;
}

// 0x00167208 CKSrvCinematic_RemoveBlockingScene_maybe
void CKSrvCinematic::RemoveBlockingScene(CKCinematicScene* scene) {
    CDefaultGameManager* manager = g_pEngine->m_gameManager;
    if (scene == nullptr) return;
    uint32_t count = m_vpBlockingScenes.m_ui32NbUsedElt;
    if (count == 0) return;
    uint32_t index = 0;
    while (m_vpBlockingScenes.m_pBlock[index] != scene) {
        ++index;
        if (index == count) return;
    }
    --count;
    m_vpBlockingScenes.m_ui32NbUsedElt = count;
    if (index != count) m_vpBlockingScenes.m_pBlock[index] = m_vpBlockingScenes.m_pBlock[count];
    if (m_vpBlockingScenes.m_ui32NbUsedElt == 0) manager->SetHeroesInvulnerableFromMask(&m_ui32SavedInvulnerableMask);  // vt+0x1f4
}

// 0x00167498 CKSrvCinematic_NotifyListeners: MessageProc(0x500 | what, scene) to every object to warn.
void CKSrvCinematic::NotifyListeners(CKCinematicScene* scene, uint8_t what) {
    for (uint32_t i = 0; i < m_vpSerializableToWarn.m_ui32NbUsedElt; ++i) {
        m_vpSerializableToWarn.m_pBlock[i]->MessageProc(static_cast<uint16_t>(what | 0x500), scene);  // vt+0x1c
    }
}

// 0x00167798 CKSrvCamera_AddOrRemoveCameraOwner_maybe (in this unit): the scenes that took the camera, in the
// camera service's list (+0xe14, count +0xe24; four entries, unchecked).
void CKSrvCinematic::AddOrRemoveCameraOwner(CKCinematicScene* scene, int32_t remove) {
    CKSrvCamera* camera = static_cast<CKSrvCamera*>(g_pEngine->m_srvCamera);
    IKSerializable** owners = camera->m_apCinematicOwner;
    if (remove == 0) {
        const uint32_t count = camera->m_unke24;
        for (uint32_t i = 0; i < count; ++i) {
            if (owners[i] == scene) return;
        }
        camera->m_unke24 = camera->m_unke24 + 1;
        owners[count] = scene;
        return;
    }
    uint32_t count = camera->m_unke24;
    if (count == 0) return;
    uint32_t index = 0;
    while (owners[index] != scene) {
        ++index;
        if (index == count) return;
    }
    --count;
    camera->m_unke24 = count;
    if (index == count) return;
    owners[index] = owners[count];
}

// 0x00167940 CKSrvCinematic_ActivateNode(service, source, node)
void CKSrvCinematic::ActivateNode(IKCinematicElement* source, IKCinematicElement* node) {
    CKCinematicSceneData* data = static_cast<CKCinematicSceneData*>(node->m_pElementData);
    if (data == nullptr || data->m_pHook != nullptr) {
        // A node without actor data, or with its actor present.
        if ((node->m_DataFlags & 1) != 0 && node->IsKindOfClass(0x88c) == 0) return;  // running, and not a door
        node->Activate(source);  // vt+0x60
        return;
    }
    // The actor is missing: the node is skipped, but what it leads to goes on. The nodes seen are kept so that a cycle
    // of such nodes ends.
    if (source == nullptr) {
        m_vpActivationGuard.m_ui32NbElt = 2;
        m_vpActivationGuard.m_pBlock = static_cast<IKCinematicElement**>(Mem_AllocAligned16(8));  // BUG(original): the old block leaks
        const uint32_t count = m_vpActivationGuard.m_ui32NbUsedElt;
        if (m_vpActivationGuard.m_ui32NbElt == count) {
            uint32_t capacity = count + 2;
            if (capacity == 0) capacity = 2;
            m_vpActivationGuard.m_pBlock = static_cast<IKCinematicElement**>(
                Mem_ReallocAligned16(m_vpActivationGuard.m_pBlock, (capacity & 0x3fffffffu) << 2));
            m_vpActivationGuard.m_ui32NbElt = capacity;
        }
        m_vpActivationGuard.m_pBlock[count] = node;
        ++m_vpActivationGuard.m_ui32NbUsedElt;
    } else {
        const uint32_t count = m_vpActivationGuard.m_ui32NbUsedElt;
        for (uint32_t i = 0; i < count; ++i) {
            if (m_vpActivationGuard.m_pBlock[i] == node) return;
        }
        if (m_vpActivationGuard.m_ui32NbElt == count) {
            uint32_t capacity = m_vpActivationGuard.m_ui32NbElt + 2;
            if (capacity == 0) capacity = 2;
            m_vpActivationGuard.m_pBlock = static_cast<IKCinematicElement**>(
                Mem_ReallocAligned16(m_vpActivationGuard.m_pBlock, (capacity & 0x3fffffffu) << 2));
            m_vpActivationGuard.m_ui32NbElt = capacity;
        }
        m_vpActivationGuard.m_pBlock[count] = node;
        ++m_vpActivationGuard.m_ui32NbUsedElt;
    }
    if ((node->m_DataFlags & 0x10) != 0) {
        uint32_t count = 0;
        IKCinematicElement** outputs = node->m_pRelatedScene->GetNodeOutputs(&count, 1, node);
        for (uint32_t i = 0; i < count; ++i) ActivateNode(node, outputs[i]);
        count = 0;
        outputs = node->m_pRelatedScene->GetNodeOutputs(&count, 2, node);
        for (uint32_t i = 0; i < count; ++i) outputs[i]->Stop();  // vt+0x6c
    }
    if (source == nullptr) {
        if (m_vpActivationGuard.m_pBlock != nullptr) {
            Mem_FreeAligned16(m_vpActivationGuard.m_pBlock);
            m_vpActivationGuard.m_pBlock = nullptr;
        }
        m_vpActivationGuard.m_ui32NbUsedElt = 0;
        m_vpActivationGuard.m_pBlock = nullptr;
    }
}

// 0x00168048 UpdateCKSrvCinematic. Not while the clock is stopped (IKTime +0x30). The bands come off the UI scene
// each frame and go back when a scene needs them; a requested skip (bit 3) skips the skippable playing scenes; each
// scene that plays is updated, and one whose bit 15 is set (a start was requested) is started.
void CKSrvCinematic::Update(IKTime* time) {
    if (time->m_eCurrentState != 0) return;
    CScene2d* ui = static_cast<CScene2d*>(Ui()->m_pFirstScene);
    ui->RemoveChild(static_cast<CBillboard2d*>(m_pBlackBandBillBoard[0]));
    ui->RemoveChild(static_cast<CBillboard2d*>(m_pBlackBandBillBoard[1]));
    m_baData = static_cast<uint8_t>(m_baData & 0xfe);
    const uint32_t count = m_ui32SceneNumber;
    if (((m_baData >> 3) & 1) != 0) {
        m_baData = static_cast<uint8_t>(m_baData & 0xf7);
        if (count == 0) return;
        for (uint32_t i = 0; i < count; ++i) {
            CKCinematicScene* scene = SceneAt(this, i);
            if ((scene->m_baData & 1) != 0 && (scene->m_unk22 & 0x10) != 0) scene->Skip();
        }
    } else if (count == 0) {
        return;
    }
    uint32_t needBands = 0;
    for (uint32_t i = 0; i < count;) {
        CKCinematicScene* scene = SceneAt(this, i);
        if ((scene->m_baData & 1) != 0) {
            scene->Update(time);
            const uint8_t band = scene->m_baBlackBandData;
            if ((band & 1) != 0 && (scene->m_baData & 1) != 0 && ((band & 0x80) == 0 || (scene->m_baData & 0x200) == 0))
                needBands = 1;
            if ((scene->m_baData & 0x2000) != 0) needBands = 1;
            if ((m_baData & 0x10) != 0) needBands = 1;
            if ((m_baData & 0x20) != 0) needBands &= (band >> 6) & 1;
        }
        ++i;
        if (static_cast<int16_t>(scene->m_baData) < 0) {
            scene->m_baData = static_cast<uint16_t>(scene->m_baData & 0x7fff);
            scene->Start();
        }
    }
    if (needBands != 0) {
        ui = static_cast<CScene2d*>(Ui()->m_pFirstScene);
        if ((m_baData & 1) == 0) {
            ui->AddChild(static_cast<CBillboard2d*>(m_pBlackBandBillBoard[0]));
            ui->AddChild(static_cast<CBillboard2d*>(m_pBlackBandBillBoard[1]));
            m_baData = static_cast<uint8_t>((m_baData & 0xfe) | 1);
        }
    }
}

// 0x00166680 CKSrvCinematic_FinishCurrentVideo_maybe / 0x001666a8 CKSrvCinematic_PlayNextVideo_maybe: the current video bloc's.
void CKSrvCinematic::FinishCurrentVideo() { m_pCurrentVideoBloc->FinishVideo(); }
void CKSrvCinematic::PlayNextVideo() { m_pCurrentVideoBloc->PlayNextVideo(); }

// 0x00166928 Input_IsStartPressedAnyPlayer_maybe: the "Flash Manager" project's second configuration: entry 0xe
// pressed (0xff), or with two players and the second active entry 0x22.
uint8_t CKSrvCinematic::IsStartPressedAnyPlayer() {
    CKInput* input = g_pEngine->m_input;
    const uint32_t project = static_cast<uint32_t>(input->FindMappingIndexByName("Flash Manager")) & 0xff;
    const CKInputDico* dico = project != 0xff ? &input->m_aaInputDico[project][1] : nullptr;
    CDefaultGameManager* manager = g_pEngine->m_gameManager;
    const bool start = dico->GetButtonState(0xe) == 0xff;
    uint8_t second = 0;
    if (manager->GetPlayerCount() >= 2 && manager->IsPlayerActive(1) != 0 && dico->GetButtonState(0x22) == 0xff) second = 1;
    return start ? 1 : second;
}

// 0x00167d18 CKSrvCinematic_UpdateVideoSkipPrompt_maybe. Called every frame by the playing cutscene video (flag 0x100000).
// The video bloc is updated while no prompt is open; a START press with a skippable video or scene opens the yes / no
// prompt (the game loop is inhibited meanwhile), a press without one the "cannot skip" notice. Returns 0 nothing, 1 the
// prompt is open, 2 the video is skipped (yes), 3 the scene's skip (yes on a skippable scene).
int32_t CKSrvCinematic::UpdateVideoSkipPrompt() {
    const uint8_t skippableVideo = m_pCurrentVideoBloc->IsCurrentVideoSkippable();
    bool skippableScene = false;
    for (uint32_t i = 0; i < m_ui32SceneNumber; ++i) {
        const CKCinematicScene* scene = static_cast<const CKCinematicScene*>(m_pSceneList[i]);
        if ((scene->m_baData & 1) != 0 && (scene->m_unk22 & 0x10) != 0) {
            skippableScene = true;
            break;
        }
    }
    const uint8_t pressed = IsStartPressedAnyPlayer();
    CDefaultGameManager* manager = g_pEngine->m_gameManager;
    if ((m_baData & 4) == 0) {
        m_pCurrentVideoBloc->Update(g_pEngine->m_timeManager->m_pTime);  // vt+0x68
        if (skippableVideo != 0 || skippableScene) {
            if (pressed != 0) {
                const CKLocText* text = skippableScene ? manager->GetSkipCinematicPromptText() : manager->GetSkipVideoPromptText();
                MessageBox_Push(1.0f, -1.0f, this, text, 3, 6, nullptr);
                ++g_pEngine->m_gameLoop->m_inhibitCount;  // CKGameLoop_IncPauseCount_maybe
                m_baData = static_cast<uint8_t>((m_baData & 0xf8) | (m_baData & 3) | 4);
            }
        } else if (pressed != 0) {
            MessageBox_Push(1.0f, -1.0f, this, manager->GetCannotSkipPromptText(), 1, 0, nullptr);
            ++g_pEngine->m_gameLoop->m_inhibitCount;
            m_baData = static_cast<uint8_t>((m_baData & 0xf8) | (m_baData & 3) | 4);
        }
    }
    int32_t result = 0;
    if (((m_baData >> 2) & 1) != 0) {
        const int32_t answer = MessageBox_TakeResult(this);
        result = 1;
        if (answer != 0xb) {
            --g_pEngine->m_gameLoop->m_inhibitCount;  // CKGameLoop_DecPauseCount_maybe
            const uint8_t flags = m_baData;
            if (answer == 5) {  // yes
                result = 2;
                m_baData = static_cast<uint8_t>((flags & 0xf8) | (flags & 3));
                if (skippableScene) {
                    m_baData = static_cast<uint8_t>((flags & 0xf0) | (flags & 3) | 8);
                    return 3;
                }
            } else {
                result = 0;
                m_baData = static_cast<uint8_t>((flags & 0xf8) | (flags & 3));
            }
        }
    }
    return result;
}

// C2.8 port-all P11.

// 0x00168b98 CKSrvCinematic_Destructor (0x168c78 / 0x168d58 the same)
CKSrvCinematic::~CKSrvCinematic() {
    Engine_SetSrvCinematic(nullptr);
    if (m_vpActivationGuard.m_pBlock != nullptr) Mem_FreeAligned16(m_vpActivationGuard.m_pBlock);
    m_vpActivationGuard.m_ui32NbUsedElt = 0;
    m_vpActivationGuard.m_pBlock = nullptr;
    if (m_vpBlockingScenes.m_pBlock != nullptr) Mem_FreeAligned16(m_vpBlockingScenes.m_pBlock);
    m_vpBlockingScenes.m_ui32NbUsedElt = 0;
    m_vpBlockingScenes.m_pBlock = nullptr;
    if (m_vpSerializableToWarn.m_pBlock != nullptr) Mem_FreeAligned16(m_vpSerializableToWarn.m_pBlock);
    m_vpSerializableToWarn.m_ui32NbUsedElt = 0;
    m_vpSerializableToWarn.m_pBlock = nullptr;
}

// 0x00166390 CKSrvCinematic_RecursiveRegistration
void CKSrvCinematic::RecursiveRegistration(int32_t type) {
    if (static_cast<uint32_t>(type) < 2) g_pEngine->m_pSavingManager->RegisterSerializableObject(this, nullptr);
    if (type != 0 && type != 4) return;
    for (uint16_t i = 0; i < m_ui32SceneNumber; ++i) m_pSceneList[i]->RecursiveRegistration(type);  // vt+0x24
    if (type != 0) return;
    for (IKSerializable* band : m_pBlackBandBillBoard) {
        if (band != nullptr) band->RecursiveRegistration(0);
    }
}
