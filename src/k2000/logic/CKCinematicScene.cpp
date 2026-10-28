// CKCinematicScene.cpp - reconstructed original translation unit 0x168e40-0x16dd48 (GAME_TOC1, main_toc1), 56 functions, 44 live.
// Primary class: CKCinematicScene  key 0x94c  category Logic  size 0x8c  vtable 0xb1ac18
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x168e40  CKCinematicScene_Delete
//   [ ] 0x168e90  CKCinematicScene_Construct  [dead]
//   [x] 0x168ec0  CKCinematicScene_ResetRuntimeState
//   [ ] 0x168f20  FUN_00168f20  [dead]
//   [ ] 0x168f38  CKCinematicScene_ForEachNodeCall_maybe  [dead]
//   [ ] 0x169058  FUN_00169058  [dead]
//   [ ] 0x1690a8  KStub_Nop_1690a8  [dead]
//   [ ] 0x1690b0  KStub_Nop_1690b0  [dead]
//   [x] 0x1690b8  CKCinematicScene_GetNodeOutputs
//   [ ] 0x169190  FUN_00169190  [dead]
//   [ ] 0x1691a0  CKCinematicScene_ClearNodeCompletedFlags_maybe  [dead]
//   [ ] 0x1691f0  FUN_001691f0  [dead]
//   [ ] 0x169210  FUN_00169210  [dead]
//   [x] 0x169240  CKCinematicScene_AddActiveNode
//   [x] 0x169288  CKCinematicScene_RemoveActiveNode
//   [ ] 0x1692f8  RegisterCKCinematicSceneClass
//   [ ] 0x169370  _GLOBAL__I_169370
//   [x] 0x169380  CKCinematicScene_ReleaseCamera_maybe
//   [x] 0x169538  CKCinematicScene_SetLinkedHooksLocked_maybe
//   [x] 0x169608  CKCinematicScene_SetActorsLocked_maybe
//   [x] 0x169890  CKCinematicScene_StartFadeTransition_maybe
//   [x] 0x169980  CKCinematicScene_StartExitTransition_maybe
//   [x] 0x169ef8  CKCinematicScene_UpdateTransition_maybe
//   [x] 0x16a5d0  CKCinematicScene_StartEntryTransition_maybe
//   [x] 0x16acc8  CKCinematicScene_ReleaseSoundListener_maybe
//   [ ] 0x16ad20  CKCinematicScene_RecursiveRegistration
//   [x] 0x16af58  CKCinematicScene_DeleteArray
//   [x] 0x16aff8  CKCinematicScene_ResumeActiveNodes
//   [ ] 0x16b080  CKCinematicScene_IsNodeActive_maybe  [dead]
//   [x] 0x16b0c8  CKCinematicScene_PauseActiveNodes
//   [x] 0x16b150  CKCinematicScene_SetDefaultState
//   [ ] 0x16b178  CKCinematicScene_Construct_2  [dead]
//   [x] 0x16b1a8  CKCinematicScene_SetGameState
//   [x] 0x16b218  CKCinematicScene_InterruptForTransition_maybe
//   [x] 0x16b3a8  CKCinematicScene_ClearFlag22Bit5_maybe
//   [ ] 0x16b3c0  CKCinematicScene_GetInfo
//   [x] 0x16b418  CKCinematicScene_PostLoad
//   [ ] 0x16b4b8  CKCinematicScene_Destroy
//   [x] 0x16b560  CKCinematicScene_CreateArray
//   [x] 0x16b618  CKCinematicScene_Create
//   [x] 0x16b670  CKCinematicScene_SetChainedScenesFlag88_maybe
//   [ ] 0x16b728  CKCinematicScene_PlaceActorAtBeacon_maybe
//   [x] 0x16baa8  CKCinematicScene_SetPlayingState_maybe
//   [x] 0x16bdb0  CKCinematicScene_EndImmediate_maybe
//   [x] 0x16bf28  CKCinematicScene_UpdateFadeStep_maybe
//   [x] 0x16c1d8  CKCinematicScene_Start
//   [x] 0x16c448  CKCinematicScene_ResetNodesRuntime_maybe
//   [x] 0x16c4d8  CKCinematicScene_Stop
//   [x] 0x16c7f8  CKCinematicScene_ForceEnd_maybe
//   [x] 0x16c928  CKCinematicScene_Update
//   [x] 0x16cb48  CKCinematicScene_Skip_maybe
//   [x] 0x16cbc0  CKCinematicScene_MessageProc
//   [x] 0x16cc48  CKCinematicScene_ReinitBlocksRuntime_maybe
//   [ ] 0x16ccd8  CKCinematicScene_Save
//   [x] 0x16d3b0  CKCinematicScene_Load
//   [x] 0x16dba8  CKCinematicScene_AbortActiveNodes_maybe
//
//   [ ] 0x9a8c78  CKCinematicScene_GetClassType  [inline]
//   [ ] 0x9a8c80  CKCinematicScene_GetClassID  [inline]
//   [ ] 0x9a8c88  CKCinematicScene_GetIsPlaying  [inline]
//   [ ] 0x9a8c98  CKCinematicScene_IsKindOfClass  [inline]
//   [ ] 0x9a8cb8  CKCinematicScene_DeletingDestructor  [inline]
//   [ ] 0x9a8cf8  CKCinematicScene_Destructor  [inline]
#include "k2000/logic/CKCinematicScene.h"

#include <cstring>

#include "crt/ppc_ops.h"
#include "Renderware/rwcore/RwMatrix.h"
#include "k2000/cameras/CKSrvCamera.h"
#include "k2000/core/Stub.h"
#include "k2000/graphical/fx/CBillboard2d.h"
#include "k2000/graphical/ui/CameraContextUi.h"
#include "k2000/groups/IKBaseGroup.h"
#include "k2000/hooks/IKHook.h"
#include "k2000/hooks/IKLife.h"
#include "k2000/io/IKFile.h"
#include "k2000/logic/CDefaultGameManager.h"
#include "k2000/logic/CKCinematicSceneData.h"
#include "k2000/logic/CKCoreManager.h"
#include "k2000/logic/CKLevel.h"
#include "k2000/managers/CKSoundManager.h"
#include "k2000/misc/Engine.h"
#include "k2000/misc/IKCinematicElement.h"
#include "k2000/misc/Mat4.h"
#include "k2000/scenegraph/CSGMovable.h"
#include "k2000/services/CKSrvCinematic.h"
#include "k2000/services/CKSrvDetect.h"
#include "k2000/sound/CKListener.h"
#include "k2000/sound/SoundVoiceManager.h"
#include "k2000/system/IKTime.h"

// 0x0016b618 CKCinematicScene_Create (the same stores as the dead CKCinematicScene_Construct 0x168e90)
CKCinematicScene::CKCinematicScene() {
    m_pActiveNodes = nullptr;
    m_unk88 = 0;
    m_unk24 = static_cast<uint8_t>(m_unk24 & 0xfe);
    m_unk24 = 0;
}

// 0x00168ec0 CKCinematicScene_ResetRuntimeState
void CKCinematicScene::ResetRuntimeState() {
    m_baData = static_cast<uint16_t>(m_baData & 0x77da);
    m_ui8CurAlpha = 0xff;
    m_fCurCenterPos = 0.0f;  // stored as the word 0
    m_fAlphaSpeed = 0.0f;
    m_baBlackBandData = static_cast<uint8_t>(m_baBlackBandData & 0x1f);
    m_baData = static_cast<uint16_t>(m_baData & 0xffbf);
    m_unk40 = 0;
    m_pLastEvent = nullptr;
}

namespace {
// The count + reference array pattern the Load inlines three times: new[] of count pointers, or 0.
void ReadSceneRefArray(IKFile* file, IKSerializable*** array, uint32_t* count) {
    ReadU32LE(file, count);
    if (*count == 0) {
        *array = nullptr;
    } else {
        *array = new IKSerializable*[*count];
        IKFile_ReadObjectRefArray(file, *array, *count);
    }
}
}  // namespace

// 0x0016d3b0 CKCinematicScene_Load
int32_t CKCinematicScene::Load(IKFile* file, int32_t type) {
    if (type == K_LEVEL_PLATEFORMS) {
        ReadU16LE(file, &m_baData);
        ReadU16LE(file, &m_unk22);
        ReadSceneRefArray(file, &m_apCinematicSceneData, &m_ui32HookNumber);
        ReadSceneRefArray(file, &m_pCinematicPointerList, &m_ui32CinematicPointerLength);
        IKFile_ReadRef(file, &m_pFirstBloc);
        ReadU8(file, &m_baBlackBandData);
        ReadRaw(file, &m_BandColor, 4);
        ReadF32LE(file, &m_fBandHeight);
        ReadF32LE(file, &m_fAlphaAppearTime);
        ReadF32LE(file, &m_fAlphaDisappearTime);
        ReadF32LE(file, &m_fAppearTime);
        ReadF32LE(file, &m_fDisappearTime);
        ReadF32LE(file, &m_fTimeForFade);
        ReadU32LE(file, &m_ui32SectorNum);
        m_tsEnd.Load(file, K_LEVEL_PLATEFORMS);
        m_tsUnk68.Load(file, K_LEVEL_PLATEFORMS);
        m_tsUnk70.Load(file, K_LEVEL_PLATEFORMS);
        ReadSceneRefArray(file, &m_apGroupToAsleep, &m_ui32GroupToAsleep);
        IKFile_ReadRef(file, &m_pSoundDico);
        ReadU8(file, &m_bDesactivateCameraSector);
        ReadF32LE(file, &m_fCameraEndTransitionTime);
        ResetRuntimeState();
        IKFile_ReadRef(file, &m_unk78);
    } else if (type == K_LEVEL_MEMCARD) {
        ReadU16LE(file, &m_baData);
        m_baData = static_cast<uint16_t>(m_baData & 0xf79a);
    }
    return 1;
}

// 0x0016cc48 CKCinematicScene_ReinitBlocksRuntime_maybe
void CKCinematicScene::ReinitBlocksRuntime() {
    for (uint32_t i = 0; i < m_ui32CinematicPointerLength; ++i) {
        static_cast<IKCinematicElement*>(m_pCinematicPointerList[i])->Vf54();
    }
}

// 0x0016b670 CKCinematicScene_SetChainedScenesFlag88_maybe (unrolled nine times in the original)
void CKCinematicScene::SetChainedScenesFlag88(uint8_t value) {
    CKCinematicScene* scene = this;
    while (scene != nullptr) {
        scene->m_unk88 = value;
        scene = static_cast<CKCinematicScene*>(scene->m_unk78);
    }
}

// 0x0016c448 CKCinematicScene_ResetNodesRuntime_maybe
void CKCinematicScene::ResetNodesRuntime() {
    for (uint32_t i = 0; i < m_ui32CinematicPointerLength; ++i) {
        static_cast<IKCinematicElement*>(m_pCinematicPointerList[i])->PreStart();
    }
}

namespace {

CKSrvCinematic* Service() { return static_cast<CKSrvCinematic*>(g_pEngine->m_srvCinematic); }

// A byte of the band colour as the file stored it (R, G, B, A).
uint8_t* ColorBytes(uint32_t* color) { return reinterpret_cast<uint8_t*>(color); }

// The service's current colour (+0x28) taken from the scene's band colour: the four bytes and their float
// channels (CSmoothedCColorLinear: lbz, fcfid, frsp per channel).
void SetBandCurrentFromScene(SBandColor* band, const uint32_t* color) {
    std::memcpy(band->m_acCurrent, color, 4);
    for (int i = 0; i < 4; ++i) band->m_afCurrent[i] = static_cast<float>(band->m_acCurrent[i]);
}

// The band billboards (CBillboard2d, position at +0x14, size at +0x3c of the object).
CBillboard2d* Band(CKSrvCinematic* service, int index) {
    return static_cast<CBillboard2d*>(service->m_pBlackBandBillBoard[index]);
}

void SetBarPosition(CBillboard2d* bar, float x, float y) {
    bar->m_vPosition.m_fX = x;
    bar->m_vPosition.m_fY = y;
}
void SetBarSize(CBillboard2d* bar, float x, float y) {
    bar->m_vBillboardSize.m_fX = x;
    bar->m_vBillboardSize.m_fY = y;
}
// IKBillboard2d::SetColor (vt+0x28 of the second base) with a copy of the colour word on the stack.
void SetBarColor(CBillboard2d* bar, const void* color) {
    uint8_t copy[4];
    std::memcpy(copy, color, 4);
    bar->SetColor(copy);
}

// The listeners' MessageProc ids (0x500 | what).
constexpr uint8_t kSceneStarted = 0;
constexpr uint8_t kPlayingStateChanged = 1;
constexpr uint8_t kSceneEnded = 2;

}  // namespace

// 0x0016b418 CKCinematicScene_PostLoad (every type): the five times at least 0.01 (0x3c23d70a), bit 5 of +0x22 cleared.
int32_t CKCinematicScene::PostLoad(int32_t /*type*/) {
    const float kMinTime = 0.01f;
    if (m_fAlphaAppearTime < kMinTime) m_fAlphaAppearTime = kMinTime;
    if (m_fAlphaDisappearTime < kMinTime) m_fAlphaDisappearTime = kMinTime;
    if (m_fDisappearTime < kMinTime) m_fDisappearTime = kMinTime;
    if (m_fAppearTime < kMinTime) m_fAppearTime = kMinTime;
    if (m_fTimeForFade < kMinTime) m_fTimeForFade = kMinTime;
    m_unk22 = static_cast<uint16_t>(m_unk22 & 0xffdf);
    return 1;
}

// 0x0016b150 CKCinematicScene_SetDefaultState: "played" (bit 14) cleared; with flag 0 also bit 2 ("has played").
void CKCinematicScene::SetDefaultState(int32_t flag) {
    const uint16_t flags = m_baData;
    m_baData = static_cast<uint16_t>(flags & 0xbfff);
    if (flag != 0) return;
    m_baData = static_cast<uint16_t>(flags & 0xbffb);
}

// 0x0016b1a8 CKCinematicScene_SetGameState: info 4 with state 0 marks the scene played (bit 14), state 1 clears it.
int32_t CKCinematicScene::SetGameState(const SApplyGameState* state) {
    int32_t result = 0;
    if (state->m_ui32InfoId == 4) {
        const uint8_t id = static_cast<uint8_t>(state->m_ui32GameStateId & 0xff);  // the byte at +7 of the big-endian word
        if (id == 0) {
            m_baData = static_cast<uint16_t>(m_baData | 0x4000);
            return 1;
        }
        if (id == 1) {
            result = 1;
            m_baData = static_cast<uint16_t>(m_baData & 0xbfff);
        }
    }
    return result;
}

// 0x001690b8 CKCinematicScene_GetNodeOutputs
IKCinematicElement** CKCinematicScene::GetNodeOutputs(uint32_t* count, int32_t type, IKCinematicElement* node) {
    const uint32_t number = node->m_ui16ElementsNumber;
    const uint32_t start = node->m_ui16StartElementsFirstIndex;
    const uint32_t interrupt = node->m_ui16InterruptElementsFirstIndex;
    IKCinematicElement** list = reinterpret_cast<IKCinematicElement**>(m_pCinematicPointerList);
    if (type == 1) {
        if (start != 0xffff) {
            if (interrupt == 0xffff) {
                *count = number;
                return list + start;
            }
            *count = interrupt - start;
            return list + start;
        }
    } else {
        if (type != 2) return nullptr;
        if (interrupt != 0xffff) {
            if (start == 0xffff) {
                *count = number;
                return list + interrupt;
            }
            *count = number - (interrupt - start);
            return list + interrupt;
        }
    }
    *count = 0;
    return nullptr;
}

// 0x00169240 CKCinematicScene_AddActiveNode: pushed on the list unless it is in it.
void CKCinematicScene::AddActiveNode(IKCinematicElement* node) {
    IKCinematicElement* head = m_pActiveNodes;
    if (head != nullptr) {
        IKCinematicElement* walk = head;
        if (node == head) return;
        while ((walk = walk->m_pNext) != nullptr) {
            if (node == walk) return;
        }
    }
    node->m_pNext = head;
    m_pActiveNodes = node;
}

// 0x00169288 CKCinematicScene_RemoveActiveNode
void CKCinematicScene::RemoveActiveNode(IKCinematicElement* node) {
    IKCinematicElement* head = m_pActiveNodes;
    if (head == nullptr) return;
    if (node == head) {
        m_pActiveNodes = node->m_pNext;
    } else {
        IKCinematicElement* previous;
        do {
            previous = head;
            head = previous->m_pNext;
            if (head == nullptr) return;
        } while (node != head);
        previous->m_pNext = node->m_pNext;
        if (node->m_pNext != nullptr) node->m_pNext = nullptr;
    }
    node->m_pNext = nullptr;
}

// 0x0016b0c8 CKCinematicScene_PauseActiveNodes
void CKCinematicScene::PauseActiveNodes() {
    IKCinematicElement* node = m_pActiveNodes;
    while (node != nullptr) {
        while ((node->m_DataFlags & 2) == 0) {
            node = node->m_pNext;
            if (node == nullptr) return;
        }
        node->Pause();  // vt+0x78
        node = node->m_pNext;
    }
}

// 0x0016aff8 CKCinematicScene_ResumeActiveNodes
void CKCinematicScene::ResumeActiveNodes() {
    IKCinematicElement* node = m_pActiveNodes;
    while (node != nullptr) {
        while ((node->m_DataFlags & 2) == 0) {
            node = node->m_pNext;
            if (node == nullptr) return;
        }
        node->Resume();  // vt+0x7c
        node = node->m_pNext;
    }
}

// 0x00169608 CKCinematicScene_SetActorsLocked_maybe. Every actor hook of the scene (CKCinematicSceneData): locked
// (its life object, or the hook itself, SetObjectLocked) when the scene starts, for the data flagged for it; and
// unlocked when it ends. With data flag bit 2 the hook's local matrix is saved at the lock and put back at the
// unlock.
void CKCinematicScene::SetActorsLocked(uint32_t locked) {
    const uint32_t count16 = m_ui32HookNumber & 0xffff;
    if (count16 == 0) return;
    const uint32_t lock = locked & 0xff;
    const uint32_t loops = ((m_ui32HookNumber - 1) & 0xffff) + 1;
    for (uint32_t i = 0; i != loops; ++i) {
        CKCinematicSceneData* data = static_cast<CKCinematicSceneData*>(m_apCinematicSceneData[i & 0xffff]);
        IKHook* hook = static_cast<IKHook*>(data->m_pHook);
        if (hook == nullptr) continue;
        if (lock == 0 || (data->m_DataFlags & 1) != 0) {
            IKLife* object = hook->m_pHookLife != nullptr ? static_cast<IKLife*>(hook->m_pHookLife) : hook;
            if (lock != ((object->m_bitArray >> 1) & 1)) {
                SetObjectLocked(g_pEngine->m_coreManager, object, locked & 0xff);
                if (lock != 0) data->m_pShadowData = hook->GetComponent(0x486);
            }
        }
        if ((data->m_DataFlags & 4) == 0) continue;
        if (lock == 0) {
            if (data->m_pOriginalMatrix != nullptr) {
                static_cast<CSGMovable*>(hook->m_pKGLObject)
                    ->SetLocalMatrix(static_cast<const RwMatrix*>(data->m_pOriginalMatrix));
                data->FreeSavedMatrix();
            }
            continue;
        }
        data->AllocSavedMatrix();
        const RwFrame* frame = static_cast<CSGMovable*>(hook->m_pKGLObject)->m_pRwFrame;
        std::memcpy(data->m_pOriginalMatrix, &frame->modelling, 0x40);
    }
}

// 0x0016baa8 CKCinematicScene_SetPlayingState_maybe
void CKCinematicScene::SetPlayingState(uint32_t playing) {
    CKSrvCinematic* service = Service();
    CDefaultGameManager* manager = g_pEngine->m_gameManager;
    const uint32_t state = playing & 0xff;
    SetActorsLocked(playing & 0xff);
    for (uint32_t i = 0; i < m_ui32GroupToAsleep; ++i) {
        IKBaseGroup* group = static_cast<IKBaseGroup*>(m_apGroupToAsleep[i]);
        IKLife* object = group->m_pGroupLife != nullptr ? static_cast<IKLife*>(group->m_pGroupLife) : group;
        if (state != ((object->m_bitArray >> 1) & 1)) SetObjectLocked(g_pEngine->m_coreManager, object, playing & 0xff);
    }
    uint16_t flags = m_unk22;
    if ((flags & 2) != 0) {
        if (state != 0) {
            // The input state before the scene is kept (bit 2) and the input blocked.
            const uint32_t wasBlocked = manager->IsInputBlocked();  // vt+0x1ec
            m_unk22 = static_cast<uint16_t>((m_unk22 & ~4u) | ((wasBlocked << 2) & 0x3fc));
            manager->SetInputBlocked(1);  // vt+0x1e8
            flags = m_unk22;
        } else if ((flags & 4) == 0) {
            manager->SetInputBlocked(0);
            flags = m_unk22;
        }
    }
    if (((flags >> 3) & 1) == 0) {
        if (state == 0) {
            service->NotifyListeners(this, kPlayingStateChanged);
            m_unk22 = static_cast<uint16_t>(m_unk22 | 0x20);
        }
        return;
    }
    if (state != 0) {
        service->AddBlockingScene(this);
        return;
    }
    service->RemoveBlockingScene(this);
    service->NotifyListeners(this, kPlayingStateChanged);
    m_unk22 = static_cast<uint16_t>(m_unk22 | 0x20);
}

// 0x0016a5d0 CKCinematicScene_StartEntryTransition_maybe. The bands are put at the position their entry mode starts
// from, coloured, and shown; the service's colour is set up for the modes that move it.
void CKCinematicScene::StartEntryTransition() {
    CKSrvCinematic* service = Service();
    const uint32_t mode = (m_baBlackBandData >> 1) & 3;
    CBillboard2d* bar0 = Band(service, 0);
    CBillboard2d* bar1 = Band(service, 1);
    CBillboard2d* quad = Band(service, 2);
    uint8_t* color = reinterpret_cast<uint8_t*>(&m_BandColor);
    const float h = (-0.5f / (CameraContext_GetHeightOverWidth() * m_fBandHeight)) + 0.5f;  // fdivs, fadds
    const float centre = h * 0.5f;                    // fmuls f12 = f31 * 0.5
    const float lower = ppc::fmadds(h, -0.5f, 1.0f);  // fmadds f0 = f31 * -0.5 + 1.0
    if (mode == 1) {
        m_ui8CurAlpha = 0;
        color[3] = 0;
        SetBarPosition(bar0, 0.5f, centre);
        SetBarSize(bar0, 1.5f, h);
        SetBarPosition(bar1, 0.5f, lower);
        SetBarSize(bar1, 1.5f, h);
        SetBarColor(bar0, &m_BandColor);
        SetBarColor(bar1, &m_BandColor);
        m_fAlphaSpeed = 255.0f / m_fAlphaAppearTime;
        service->ShowLetterboxBars();
        std::memcpy(service->m_scBandColor.m_acTarget, &m_BandColor, 4);
        service->m_scBandColor.m_acTarget[3] = 0xff;
        SetBandCurrentFromScene(&service->m_scBandColor, &m_BandColor);
        service->m_scBandColor.m_fSpeed = m_fAlphaSpeed / 255.0f;
    } else if (mode == 0) {
        SetBarPosition(bar0, 0.5f, centre);
        SetBarSize(bar0, 1.5f, h);
        SetBarPosition(bar1, 0.5f, lower);
        SetBarSize(bar1, 1.5f, h);
        color[3] = 0xff;
        SetBandCurrentFromScene(&service->m_scBandColor, &m_BandColor);
        SetBarColor(bar0, &m_BandColor);
        SetBarColor(bar1, &m_BandColor);
        service->ShowLetterboxBars();
    } else if (mode == 2) {
        if (((m_baBlackBandData >> 5) & 1) != 0) return;
        m_fCurCenterPos = h;
        color[3] = 0xff;
        m_fAlphaSpeed = h / m_fAppearTime;
        float first = ppc::fmadds(h, -0.5f, 1.0f);
        if ((service->m_baData & 1) != 0) {
            m_fCurCenterPos = bar0->m_vPosition.m_fY - first;  // fsubs: the band that is still there
            service->InterruptPlayingScenes();
        }
        SetBarPosition(bar0, 0.5f, first + m_fCurCenterPos);
        SetBarSize(bar0, 1.5f, h);
        SetBarPosition(bar1, 0.5f, ppc::fmsubs(h, 0.5f, m_fCurCenterPos));
        SetBarSize(bar1, 1.5f, h);
        SetBarColor(bar0, &m_BandColor);
        SetBarColor(bar1, &m_BandColor);
        service->ShowLetterboxBars();
        std::memcpy(service->m_scBandColor.m_acTarget, &m_BandColor, 4);
        SetBandCurrentFromScene(&service->m_scBandColor, &m_BandColor);
    } else if (mode == 3) {
        SetBarPosition(bar0, 0.5f, centre);
        SetBarSize(bar0, 1.5f, h);
        SetBarPosition(bar1, 0.5f, lower);
        SetBarSize(bar1, 1.5f, h);
        color[3] = 0xff;
        SetBarColor(bar0, &m_BandColor);
        SetBarColor(bar1, &m_BandColor);
        m_ui8CurAlpha = 0xff;
        SetBarColor(quad, &m_BandColor);
        m_fAlphaSpeed = 510.0f / m_fTimeForFade;
        SetBandCurrentFromScene(&service->m_scBandColor, &m_BandColor);
        std::memcpy(service->m_scBandColor.m_acTarget, &m_BandColor, 4);
        service->m_scBandColor.m_acTarget[3] = 0;
        service->m_scBandColor.m_fSpeed = m_fAlphaSpeed / 255.0f;
        service->ShowFadeQuad();
        service->ShowLetterboxBars();
    }
    m_baBlackBandData = static_cast<uint8_t>((m_baBlackBandData & 0xdf) | 0x20);
}

// 0x00169ef8 CKCinematicScene_UpdateTransition_maybe: the service's colour moves to its target; then the entry
// transition (bit 5) or the exit transition (bit 6) of the bands runs one step.
void CKCinematicScene::UpdateTransition(IKTime* time) {
    CKSrvCinematic* service = Service();
    SBandColor* band = &service->m_scBandColor;
    CBillboard2d* bar0 = Band(service, 0);
    CBillboard2d* bar1 = Band(service, 1);
    const float h = (-0.5f / (CameraContext_GetHeightOverWidth() * m_fBandHeight)) + 0.5f;
    const float dt = time->m_afDeltaTime[0];

    if (std::memcmp(band->m_acCurrent, band->m_acTarget, 4) != 0) {
        const float dG = static_cast<float>(band->m_acTarget[1]) - band->m_afCurrent[1];
        const float dR = static_cast<float>(band->m_acTarget[0]) - band->m_afCurrent[0];
        const float dB = static_cast<float>(band->m_acTarget[2]) - band->m_afCurrent[2];
        const float dA = static_cast<float>(band->m_acTarget[3]) - band->m_afCurrent[3];
        float dist2 = dG * dG;
        dist2 = ppc::fmadds(dR, dR, dist2);
        const float step = (dt * band->m_fSpeed) * 255.0f;
        dist2 = ppc::fmadds(dB, dB, dist2);
        dist2 = ppc::fmadds(dA, dA, dist2);
        if (step * step <= dist2) {
            const float scale = step * rwInvSqrt(dist2);  // 0x000114d8 Math_InvSqrtf
            band->m_afCurrent[0] = ppc::fmadds(dR, scale, band->m_afCurrent[0]);
            band->m_afCurrent[3] = ppc::fmadds(dA, scale, band->m_afCurrent[3]);
            band->m_afCurrent[1] = ppc::fmadds(dG, scale, band->m_afCurrent[1]);
            band->m_afCurrent[2] = ppc::fmadds(dB, scale, band->m_afCurrent[2]);
            for (int i = 0; i < 4; ++i) band->m_acCurrent[i] = static_cast<uint8_t>(ppc::fctiwz(band->m_afCurrent[i]));
        } else {
            std::memcpy(band->m_acCurrent, band->m_acTarget, 4);
        }
    }

    const uint8_t b = m_baBlackBandData;
    if (((b >> 5) & 1) != 0) {
        // The entry transition.
        const uint32_t mode = (b >> 1) & 3;
        if (mode == 1) {
            if (std::memcmp(band->m_acCurrent, band->m_acTarget, 4) == 0)
                m_baBlackBandData = static_cast<uint8_t>(m_baBlackBandData & 0xdf);
            SetBarColor(bar0, band->m_acCurrent);
            SetBarColor(bar1, band->m_acCurrent);
        } else if (mode == 0) {
            m_baBlackBandData = static_cast<uint8_t>(m_baBlackBandData & 0xdf);
        } else if (mode == 2) {
            const float position = m_fCurCenterPos - m_fAlphaSpeed * dt;
            if (position <= 0.0f) {
                m_fCurCenterPos = 0.0f;
                m_baBlackBandData = static_cast<uint8_t>(m_baBlackBandData & 0xdf);
                m_unk40 = 1;
            } else {
                m_fCurCenterPos = position;
                m_unk40 = 0;
            }
            SetBarPosition(bar0, 0.5f, ppc::fmadds(h, -0.5f, 1.0f) + m_fCurCenterPos);
            SetBarPosition(bar1, 0.5f, ppc::fmsubs(h, 0.5f, m_fCurCenterPos));
        } else if (mode == 3) {
            CBillboard2d* quad = Band(service, 2);
            if (std::memcmp(band->m_acCurrent, band->m_acTarget, 4) == 0)
                m_baBlackBandData = static_cast<uint8_t>(m_baBlackBandData & 0xdf);
            SetBarColor(quad, band->m_acCurrent);
        }
        return;
    }
    if (((b >> 6) & 1) == 0) return;
    // The exit transition.
    const uint32_t mode = (b >> 3) & 3;
    if (mode == 1) {
        if (std::memcmp(band->m_acCurrent, band->m_acTarget, 4) == 0) {
            m_ui8CurAlpha = 0xff;
            m_baData = static_cast<uint16_t>(m_baData & 0xffbe);
            service->NotifyListeners(this, kSceneEnded);
            if ((m_baData & 0x2000) == 0) service->RemoveCinemaBars();
        }
        SetBarColor(bar0, band->m_acCurrent);
        SetBarColor(bar1, band->m_acCurrent);
    } else if (mode == 0) {
        m_baData = static_cast<uint16_t>(m_baData & 0xffbe);
        if ((m_baData & 0x2000) == 0) service->RemoveCinemaBars();
        service->NotifyListeners(this, kSceneEnded);
    } else if (mode == 2) {
        const float position = ppc::fmadds(m_fAlphaSpeed, dt, m_fCurCenterPos);
        if (h <= position) {
            if ((service->m_baData & 0x20) == 0) {
                m_fCurCenterPos = 0.0f;
                m_baData = static_cast<uint16_t>(m_baData & 0xffbe);
                service->NotifyListeners(this, kSceneEnded);
            } else {
                m_fCurCenterPos = h;
                m_baBlackBandData = static_cast<uint8_t>(m_baBlackBandData & 0xbf);
            }
            if ((m_baData & 0x2000) == 0) service->RemoveCinemaBars();
        } else {
            m_fCurCenterPos = position;
            m_unk40 = static_cast<uint8_t>((b >> 5) & 1);
        }
        SetBarPosition(bar0, 0.5f, ppc::fmadds(h, -0.5f, 1.0f) + m_fCurCenterPos);
        SetBarPosition(bar1, 0.5f, ppc::fmsubs(h, 0.5f, m_fCurCenterPos));
    } else if (mode == 3) {
        CBillboard2d* quad = Band(service, 2);
        if (std::memcmp(band->m_acCurrent, band->m_acTarget, 4) == 0) {
            m_baData = static_cast<uint16_t>(m_baData & 0xffbe);
            QueueTriggerSignals(&m_tsUnk68);
            service->NotifyListeners(this, kSceneEnded);
            reinterpret_cast<uint8_t*>(&m_BandColor)[3] = m_ui8CurAlpha;
            if ((m_baData & 0x2000) == 0) {
                service->RemoveCinemaBars();
                service->HideFadeQuad();
            }
        }
        SetBarColor(quad, band->m_acCurrent);
    }
}

// 0x0016c1d8 CKCinematicScene_Start
void CKCinematicScene::Start() {
    CKSrvCinematic* service = Service();
    CKLevel* level = g_pEngine->m_level;
    if (!((m_ui32SectorNum == 0 || static_cast<uint32_t>(level->m_currentSector) == m_ui32SectorNum) &&
          ((m_baData & 1) == 0 || ((m_baBlackBandData >> 6) & 1) != 0)))
        return;
    uint16_t flags = m_baData;
    if ((flags & 2) == 0 || (((flags >> 14) & 1) == 0 && (flags & 4) == 0)) {
        if (m_unk88 != 0) static_cast<CKSrvDetect*>(g_pEngine->m_srvDetect)->BeginCinematic();
        service->NotifyListeners(this, kSceneStarted);
        if (m_pFirstBloc != nullptr) static_cast<IKCinematicElement*>(m_pFirstBloc)->PreActivate();  // vt+0x58
        SetPlayingState(1);
        flags = m_baData;
        m_baData = static_cast<uint16_t>((flags & 0xff80) | (flags & 0x3e) | 1);
        if ((m_baBlackBandData & 1) != 0) {
            m_baBlackBandData = static_cast<uint8_t>(m_baBlackBandData & 0x1f);
            StartEntryTransition();
        }
        m_unk40 = 0;
        if (m_bDesactivateCameraSector != 0) service->AddOrRemoveCameraOwner(this, 0);
        CKListener* listener = g_pEngine->m_soundManager->m_pVoiceManager->m_pListener;
        if (listener->m_unk38 == 1 || listener->m_unk3c == 1) {
            m_bListenerFollowsCamera = 1;
            listener->SetFollowCamera(1);
        } else {
            m_bListenerFollowsCamera = 0;
        }
        if (m_pFirstBloc != nullptr) service->ActivateNode(nullptr, static_cast<IKCinematicElement*>(m_pFirstBloc));
        QueueTriggerSignals(&m_tsEnd);
    }
    m_pLastEvent = nullptr;
}

// 0x0016c928 CKCinematicScene_Update. (The original first sends a debug line, "Cinematique en lecture -> %s", to
// KStub_Nop_106d8, and calls GetName for it.)
void CKCinematicScene::Update(IKTime* time) {
    if ((m_baData & 1) == 0) return;
    uint8_t b = m_baBlackBandData;
    if ((b & 0x80) != 0) {
        UpdateFadeStep(time);
        return;
    }
    if (m_pActiveNodes == nullptr && ((m_baData >> 6) & 1) == 0) {
        Stop(0);
        m_baData = static_cast<uint16_t>((m_baData & 0xff80) | (m_baData & 0x3f) | 0x40);
        b = m_baBlackBandData;
    }
    if ((b & 1) != 0 || (Service()->m_baData & 0x10) != 0 || (Service()->m_baData & 0x20) != 0) UpdateTransition(time);
    IKCinematicElement* node = m_pActiveNodes;
    while (node != nullptr) {
        IKCinematicElement** nextField;
        IKCinematicElement* next;
        do {
            nextField = &node->m_pNext;
            next = *nextField;
            if ((node->m_DataFlags & 8) == 0) {
                if ((node->m_DataFlags & 2) != 0) node->Update(time);  // vt+0x68
            } else {
                Stop(0);
                m_baData = static_cast<uint16_t>((m_baData & 0xff80) | (m_baData & 0x3f) | 0x40);
            }
            if (next == nullptr) return;
            node = next;
        } while ((next->m_DataFlags & 1) != 0);
        node = *nextField;
    }
}

// 0x0016b218 CKCinematicScene_InterruptForTransition_maybe: a playing scene that is in an exit transition (bit 6 of
// the band data, with bands) ends at once.
void CKCinematicScene::InterruptForTransition() {
    CKSrvCinematic* service = Service();
    if ((m_baData & 1) == 0) return;
    const uint8_t b = m_baBlackBandData;
    if ((b & 1) == 0 || (b & 0x40) == 0) return;
    const uint32_t mode = (b >> 3) & 3;
    if (mode == 1) {
        m_ui8CurAlpha = 0xff;
    } else {
        if (mode == 0) {
            m_baData = static_cast<uint16_t>(m_baData & 0xffbe);
            service->NotifyListeners(this, kSceneEnded);
            return;
        }
        if (mode != 2) {
            if (mode != 3) return;
            m_baData = static_cast<uint16_t>(m_baData & 0xffbe);
            QueueTriggerSignals(&m_tsUnk68);
            service->NotifyListeners(this, kSceneEnded);
            reinterpret_cast<uint8_t*>(&m_BandColor)[3] = m_ui8CurAlpha;
            return;
        }
        m_fCurCenterPos = 0.0f;  // stored as the word 0
    }
    m_baData = static_cast<uint16_t>(m_baData & 0xffbe);
    service->NotifyListeners(this, kSceneEnded);
}

// 0x0016cb48 CKCinematicScene_Skip_maybe
void CKCinematicScene::Skip() {
    Stop(1);
    if (m_unk78 != nullptr) static_cast<CKCinematicScene*>(m_unk78)->Start();
    QueueTriggerSignals(&m_tsUnk70);
}

// 0x0016cbc0 CKCinematicScene_MessageProc
int32_t CKCinematicScene::MessageProc(uint16_t message, void* /*data*/) {
    if (message == 0x500) {
        Start();
        return 0;
    }
    if (message != 0x501) return 1;
    Stop(0);
    return 0;
}

// 0x0016c4d8 CKCinematicScene_Stop. Only a scene that plays (bit 0 of m_baData) and is not in its exit
// transition (bit 6 of the band data) does anything: the running elements are aborted (vt+0x70) and every
// element told (vt+0x74), the playing state taken off (actors unlocked, input given back, listeners told),
// "has played" (bit 2) set, the running list emptied; a scene without bands, or stopped at once, ends here
// (the end trigger +0x68 queued, the listeners told), the others start their exit transition.
void CKCinematicScene::Stop(int32_t stopImmediately) {
    if ((m_baData & 1) == 0 || ((m_baBlackBandData >> 6) & 1) != 0) return;
    CKSrvCinematic* service = Service();
    if (m_unk88 != 0) static_cast<CKSrvDetect*>(g_pEngine->m_srvDetect)->EndCinematic();
    for (IKCinematicElement* node = m_pActiveNodes; node != nullptr; node = node->m_pNext) node->Abort();  // vt+0x70
    for (uint32_t i = 0; i < m_ui32CinematicPointerLength; ++i) {
        static_cast<IKCinematicElement*>(m_pCinematicPointerList[i])->OnSceneStopped();  // vt+0x74
    }
    SetPlayingState(0);
    m_baData = static_cast<uint16_t>((m_baData & 0xfff8) | (m_baData & 3) | 4);
    IKCinematicElement* node = m_pActiveNodes;
    while (node != nullptr) {
        IKCinematicElement* next = node->m_pNext;
        node->m_pNext = nullptr;
        node = next;
    }
    m_pActiveNodes = nullptr;
    if ((m_baBlackBandData & 1) == 0 || stopImmediately != 0) {
        m_baBlackBandData = static_cast<uint8_t>((m_baBlackBandData & 0x80) | (m_baBlackBandData & 0x1f));
        m_baData = static_cast<uint16_t>(m_baData & 0xffbf);
        for (uint32_t i = 0; i < m_ui32CinematicPointerLength; ++i) {
            static_cast<IKCinematicElement*>(m_pCinematicPointerList[i])->m_DataFlags &= 0xfffffffbu;
        }
        m_baData = static_cast<uint16_t>(m_baData & 0x7ffe);
        QueueTriggerSignals(&m_tsUnk68);
        service->NotifyListeners(this, kSceneEnded);
    } else {
        StartExitTransition(1);
    }
    service->m_baData = static_cast<uint8_t>((service->m_baData & 0xc0) | (service->m_baData & 0x1f));  // bit 5
    service->m_baData = static_cast<uint8_t>((service->m_baData & 0xe0) | (service->m_baData & 0x0f));  // bit 4
    ReleaseCamera();
    ReleaseSoundListener();
    m_baData = static_cast<uint16_t>(m_baData & 0xf7df);
    m_unk24 = static_cast<uint8_t>(m_unk24 & 0xfe);
}

// 0x0016c7f8 CKCinematicScene_ForceEnd_maybe: Stop(0), then the end state at once (no transition, bars and fade quad
// hidden, the elements' "completed" bit cleared, the service's fade bits cleared).
void CKCinematicScene::ForceEnd() {
    Stop(0);
    CKSrvCinematic* service = Service();
    m_baBlackBandData = static_cast<uint8_t>((m_baBlackBandData & 0x80) | (m_baBlackBandData & 0x1f));
    m_baData = static_cast<uint16_t>((m_baData & 0xff80) | (m_baData & 0x3f));
    service->RemoveCinemaBars();
    service->HideFadeQuad();
    for (uint32_t i = 0; i < m_ui32CinematicPointerLength; ++i) {
        static_cast<IKCinematicElement*>(m_pCinematicPointerList[i])->m_DataFlags &= 0xfffffffbu;
    }
    m_baData = static_cast<uint16_t>(m_baData & 0x7ffe);
    service->m_baData = static_cast<uint8_t>((service->m_baData & 0xe0) | (service->m_baData & 0x0f));
    service->m_baData = static_cast<uint8_t>((service->m_baData & 0xc0) | (service->m_baData & 0x1f));
}

// 0x00169380 CKCinematicScene_ReleaseCamera_maybe. A scene that took the camera over with a CKManageCameraCinematicBloc
// (bit 0 of +0x24) gives it back: the game manager's camera follows the focused hero (vt+0x148), the scene leaves the
// camera owners and, when no other scene owns it, the zone camera at the target position is switched to with the scene's
// end transition time. A scene that only switched the camera sector off (+0x81) leaves the owners.
void CKCinematicScene::ReleaseCamera() {
    CKSrvCinematic* service = Service();
    if ((m_unk24 & 1) == 0) {
        if (m_bDesactivateCameraSector != 0) service->AddOrRemoveCameraOwner(this, 1);
        return;
    }
    CKSrvCamera* camera = static_cast<CKSrvCamera*>(g_pEngine->m_srvCamera);
    g_pEngine->m_gameManager->SwitchToFocusedHeroCamera();  // vt+0x148
    service->AddOrRemoveCameraOwner(this, 1);
    if (camera->m_unke24 != 0) return;
    IKCamera* zone = camera->FindZoneCameraAtPosition(0);
    if (zone == nullptr || camera->m_pCurrentCamera == zone) return;
    camera->m_pNextCamera = zone;
    if ((camera->m_baTemporaryFlags & 0x10u) == 0) {
        camera->m_fSwitchTimer = 0.0f;
        camera->m_ui8TransitionMode = 0;
        camera->m_baTemporaryFlags = (camera->m_baTemporaryFlags & 0xffbfffffu) | 0x400000u;
    }
    IKSerializable* target = camera->m_ui32NbStacked != 0 ? camera->m_aStack[0].m_pTarget : nullptr;
    camera->PushCamera(m_fCameraEndTransitionTime, target, 1);
}

// 0x0016acc8 CKCinematicScene_ReleaseSoundListener_maybe
void CKCinematicScene::ReleaseSoundListener() {
    CKListener* listener = g_pEngine->m_soundManager->m_pVoiceManager->m_pListener;
    if (m_bListenerFollowsCamera != 0) {
        m_bListenerFollowsCamera = 0;
        listener->SetFollowCamera(0);
    }
}

// 0x00169538 CKCinematicScene_SetLinkedHooksLocked_maybe
void CKCinematicScene::SetLinkedHooksLocked(uint32_t locked) {
    for (uint32_t i = 0; i < m_ui32GroupToAsleep; ++i) {
        IKBaseGroup* group = static_cast<IKBaseGroup*>(m_apGroupToAsleep[i]);
        IKLife* object = group->m_pGroupLife != nullptr ? static_cast<IKLife*>(group->m_pGroupLife) : group;
        if ((locked & 0xff) != ((object->m_bitArray >> 1) & 1)) SetObjectLocked(g_pEngine->m_coreManager, object, locked & 0xff);
    }
}

// 0x00169980 CKCinematicScene_StartExitTransition_maybe
void CKCinematicScene::StartExitTransition(int32_t signal) {
    CKSrvCinematic* service = Service();
    const uint8_t bands = m_baBlackBandData;
    const uint32_t mode = (bands >> 3) & 3;
    CBillboard2d* bar0 = Band(service, 0);
    CBillboard2d* bar1 = Band(service, 1);
    CBillboard2d* quad = Band(service, 2);
    uint8_t* color = reinterpret_cast<uint8_t*>(&m_BandColor);
    const float h = (-0.5f / (CameraContext_GetHeightOverWidth() * m_fBandHeight)) + 0.5f;
    const float centre = h * 0.5f;
    const float lower = ppc::fmadds(h, -0.5f, 1.0f);
    if (mode == 1) {
        m_ui8CurAlpha = 0xff;
        color[3] = 0xff;
        SetBarPosition(bar0, 0.5f, centre);
        SetBarSize(bar0, 1.5f, h);
        SetBarPosition(bar1, 0.5f, lower);
        SetBarSize(bar1, 1.5f, h);
        SetBarColor(bar0, &m_BandColor);
        SetBarColor(bar1, &m_BandColor);
        m_fAlphaSpeed = 255.0f / m_fAlphaDisappearTime;
        SetBandCurrentFromScene(&service->m_scBandColor, &m_BandColor);
        service->m_scBandColor.m_fSpeed = m_fAlphaSpeed / 255.0f;
        std::memcpy(service->m_scBandColor.m_acTarget, &m_BandColor, 4);
        service->m_scBandColor.m_acTarget[3] = 0;
        QueueTriggerSignals(&m_tsUnk68);
    } else if (mode == 0) {
        SetBarPosition(bar0, 0.5f, centre);
        SetBarSize(bar0, 1.5f, h);
        SetBarPosition(bar1, 0.5f, lower);
        SetBarSize(bar1, 1.5f, h);
        SetBarColor(bar0, &m_BandColor);
        SetBarColor(bar1, &m_BandColor);
        QueueTriggerSignals(&m_tsUnk68);
    } else if (mode == 2) {
        if (((bands >> 6) & 1) != 0) return;
        color[3] = 0xff;
        if ((bands & 0x20) == 0) {
            if ((service->m_baData & 0x20) == 0) m_fCurCenterPos = 0.0f;  // stored as the word 0
        } else {
            m_baBlackBandData = static_cast<uint8_t>((m_baBlackBandData & 0xc0) | (m_baBlackBandData & 0x1f));
        }
        SetBarPosition(bar0, 0.5f, lower + m_fCurCenterPos);
        SetBarSize(bar0, 1.5f, h);
        SetBarPosition(bar1, 0.5f, ppc::fmsubs(h, 0.5f, m_fCurCenterPos));
        SetBarSize(bar1, 1.5f, h);
        SetBarColor(bar0, &m_BandColor);
        SetBarColor(bar1, &m_BandColor);
        m_fAlphaSpeed = h / m_fDisappearTime;
        if (signal != 0) QueueTriggerSignals(&m_tsUnk68);
    } else if (mode == 3) {
        m_ui8CurAlpha = 0;
        color[3] = 0;
        SetBarColor(quad, &m_BandColor);
        m_fAlphaSpeed = 510.0f / m_fTimeForFade;
        SetBandCurrentFromScene(&service->m_scBandColor, &m_BandColor);
        service->m_scBandColor.m_fSpeed = m_fAlphaSpeed / 255.0f;
        std::memcpy(service->m_scBandColor.m_acTarget, &m_BandColor, 4);
        service->m_scBandColor.m_acTarget[3] = 0xff;
        service->ShowFadeQuad();
    }
    m_baBlackBandData = static_cast<uint8_t>((m_baBlackBandData & 0x80) | (m_baBlackBandData & 0x3f) | 0x40);
}

// 0x00169890 CKCinematicScene_StartFadeTransition_maybe
void CKCinematicScene::StartFadeTransition() {
    CKSrvCinematic* service = Service();
    CBillboard2d* quad = Band(service, 2);
    reinterpret_cast<uint8_t*>(&m_BandColor)[3] = 0;
    m_ui8CurAlpha = 0;
    SetBarColor(quad, &m_BandColor);
    if (m_fTimeForFade == 0.0f) m_fTimeForFade = 0.001f;  // 0x3a83126f
    m_fAlphaSpeed = 510.0f / m_fTimeForFade;
    m_baData = static_cast<uint16_t>(m_baData & 0xfdff);
    service->ShowFadeQuad();
    m_baBlackBandData = static_cast<uint8_t>((m_baBlackBandData & 0x7f) | 0x80);
}

// 0x0016dba8 CKCinematicScene_AbortActiveNodes_maybe
void CKCinematicScene::AbortActiveNodes() {
    if ((m_baBlackBandData & 0x80) != 0) return;
    for (IKCinematicElement* node = m_pActiveNodes; node != nullptr; node = node->m_pNext) node->Abort();  // vt+0x70
    m_baData = static_cast<uint16_t>((m_baData & 0xfff8) | (m_baData & 3) | 4);
    IKCinematicElement* node = m_pActiveNodes;
    while (node != nullptr) {
        IKCinematicElement* next = node->m_pNext;
        node->m_pNext = nullptr;
        node = next;
    }
    m_pActiveNodes = nullptr;
    StartFadeTransition();
}

// 0x0016bdb0 CKCinematicScene_EndImmediate_maybe
void CKCinematicScene::EndImmediate() {
    CKSrvCinematic* service = Service();
    for (uint32_t i = 0; i < (m_ui32HookNumber & 0xffff); ++i) {
        CKCinematicSceneData* data = static_cast<CKCinematicSceneData*>(m_apCinematicSceneData[i]);
        if ((data->m_DataFlags & 1) != 0) PlaceActorAtBeacon(data);
    }
    QueueTriggerSignals(&m_tsUnk68);
    service->NotifyListeners(this, kSceneEnded);
    SetPlayingState(0);
    m_baBlackBandData = static_cast<uint8_t>(m_baBlackBandData & 0x1f);
    m_baData = static_cast<uint16_t>(m_baData & 0xffbe);
    ReleaseCamera();
    ReleaseSoundListener();
    service->HideFadeQuad();
}

// 0x0016bf28 CKCinematicScene_UpdateFadeStep_maybe
void CKCinematicScene::UpdateFadeStep(IKTime* time) {
    const int32_t step = ppc::fctiwz(m_fAlphaSpeed * time->m_afDeltaTime[0]);
    CKSrvCinematic* service = Service();
    CBillboard2d* quad = Band(service, 2);
    uint8_t* color = reinterpret_cast<uint8_t*>(&m_BandColor);
    if (m_bNeedsUnlock != 0) {
        SetPlayingState(0);
        m_bNeedsUnlock = 0;
    }
    const uint32_t alpha = m_ui8CurAlpha;
    if ((m_baData & 0x200) == 0) {
        if (alpha + (static_cast<uint32_t>(step) & 0xff) > 0xfe) {
            m_ui8CurAlpha = 0xff;
            m_baData = static_cast<uint16_t>(m_baData | 0x200);
            service->RemoveCinemaBars();
            for (uint32_t i = 0; i < (m_ui32HookNumber & 0xffff); ++i) {
                CKCinematicSceneData* data = static_cast<CKCinematicSceneData*>(m_apCinematicSceneData[i]);
                if ((data->m_DataFlags & 1) != 0) PlaceActorAtBeacon(data);
            }
            QueueTriggerSignals(&m_tsUnk68);
            service->NotifyListeners(this, kSceneEnded);
            m_bNeedsUnlock = 1;
            ReleaseCamera();
            ReleaseSoundListener();
        } else {
            const uint8_t value = static_cast<uint8_t>(static_cast<uint32_t>(step) + alpha);
            color[3] = value;
            m_ui8CurAlpha = value;
        }
    } else if (static_cast<int32_t>(alpha - (static_cast<uint32_t>(step) & 0xff)) < 1) {
        m_ui8CurAlpha = 0;
        m_baBlackBandData = static_cast<uint8_t>(m_baBlackBandData & 0x1f);
        m_baData = static_cast<uint16_t>(m_baData & 0xffbe);
        service->HideFadeQuad();
    } else {
        const uint8_t value = static_cast<uint8_t>(alpha - static_cast<uint32_t>(step));
        color[3] = value;
        m_ui8CurAlpha = value;
    }
    color[3] = m_ui8CurAlpha;
    SetBarColor(quad, &m_BandColor);
}

// 0x0016b728 CKCinematicScene_PlaceActorAtBeacon_maybe. STUB(C2.7): only a scene with interrupt beacons on its actors
// (CKCinematicSceneData +0x10, not 0xffff) ends through here, and none of LVL010's does (not reached, so a port could not
// be checked). The ground probe it uses (GroundProbePoints 0x196540, step 3) is ported; still missing are the beacon
// getters 0x16dee0 / 0x16e4a8 (the beacon service's +0x18 table) and CKSrvDetect_SetDetectablePosition_maybe.
void CKCinematicScene::PlaceActorAtBeacon(CKCinematicSceneData* /*data*/) {
    DOTD_STUB_ONCE("CKCinematicScene_PlaceActorAtBeacon_maybe 0x16b728: the actor placed at its beacon (C2.7)");
}
