// CKFlashUICinematicBloc.cpp - reconstructed original translation unit 0x17a760-0x17c080 (GAME_TOC1, main_toc1), 24 functions, 22 live.
// Primary class: CKFlashUICinematicBloc  key 0x8c8  category CinematicNode  size 0x54  vtable 0xb1b318
// Other owners: CKGroupBlocCinematicBloc (2)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x17a760  CKFlashUICinematicBloc_Delete  (the Delete factory: DOTD_DECLARE_FACTORIES(CKFlashUICinematicBloc))
//   [ ] 0x17a7b0  FUN_0017a7b0  [dead]
//   [ ] 0x17a7e8  RegisterCKFlashUICinematicBlocClass
//   [ ] 0x17a860  _GLOBAL__I_17a860
//   [x] 0x17a870  CKFlashUICinematicBloc_ReleaseUIIfUnshared_maybe  (CKFlashUICinematicBloc::ReleaseUIIfUnshared)
//   [x] 0x17aa38  CKFlashUICinematicBloc_Complete
//   [x] 0x17ac10  CKFlashUICinematicBloc_PostLoad
//   [x] 0x17ac78  CKFlashUICinematicBloc_RecursiveRegistration
//   [x] 0x17ade0  CKFlashUICinematicBloc_MessageProc
//   [x] 0x17aff8  CKFlashUICinematicBloc_DeleteArray  (DOTD_DECLARE_FACTORIES(CKFlashUICinematicBloc))
//   [x] 0x17b098  CKFlashUICinematicBloc_CreateArray  (DOTD_DECLARE_FACTORIES(CKFlashUICinematicBloc))
//   [x] 0x17b148  CKFlashUICinematicBloc_Abort
//   [x] 0x17b1b0  CKFlashUICinematicBloc_Stop
//   [x] 0x17b220  CKFlashUICinematicBloc_Destroy  (empty: the default)
//   [x] 0x17b228  CKFlashUICinematicBloc_Create  (CKFlashUICinematicBloc())
//   [x] 0x17b280  CKFlashUICinematicBloc_Update
//   [x] 0x17b538  CKFlashUICinematicBloc_Start
//   [x] 0x17b8f0  CKFlashUICinematicBloc_OnResume  (CKFlashUICinematicBloc::Resume, vt+0x7c)
//   [x] 0x17b9b0  CKFlashUICinematicBloc_OnPause  (CKFlashUICinematicBloc::Pause, vt+0x78)
//   [x] 0x17ba18  CKFlashUICinematicBloc_Load
//   [ ] 0x17bce8  CKFlashUICinematicBloc_Save
//   [x] 0x17bfd8  CKGroupBlocCinematicBloc_Delete  (the Delete factory: DOTD_DECLARE_FACTORIES(CKGroupBlocCinematicBloc))
//   [x] 0x17c028  CKGroupBlocCinematicBloc_PreActivate  (CKGroupBlocCinematicBloc.h)
//   [ ] 0x17c070  FUN_0017c070  [dead]
//
//   [ ] 0x9a96d8  CKFlashUICinematicBloc_IsKindOfClass  [inline]
//   [ ] 0x9a9710  CKFlashUICinematicBloc_GetClassType  [inline]
//   [ ] 0x9a9718  CKFlashUICinematicBloc_GetClassID  [inline]
//   [ ] 0x9a9720  CKFlashUICinematicBloc_PreActivate  [inline]
//   [ ] 0x9a9728  CKFlashUICinematicBloc_Destructor  [inline]
//   [ ] 0x9a9748  CKFlashUICinematicBloc_DeletingDestructor  [inline]
#include "k2000/cinematics/CKFlashUICinematicBloc.h"

#include "k2000/graphical/ui/CKFlashMessageIn.h"
#include "k2000/graphical/ui/CKFlashMessageOut.h"
#include "k2000/graphical/ui/CKFlashUI.h"
#include "k2000/io/IKFile.h"
#include "k2000/logic/CKCinematicScene.h"
#include "k2000/logic/CKSekens.h"
#include "k2000/managers/CKInput.h"
#include "k2000/misc/Engine.h"
#include "k2000/services/CKSrvCinematic.h"
#include "k2000/services/CKSrvSekensor.h"

namespace {
CKSrvSekensor* Sekensor() { return static_cast<CKSrvSekensor*>(g_pEngine->m_srvSekensor); }  // engine +0x84
}  // namespace

// 0x0017ba18 CKFlashUICinematicBloc_Load: the element part, then (level files only) the state byte and the six references.
int32_t CKFlashUICinematicBloc::Load(IKFile* file, int32_t type) {
    BasicLoadCinematicElement(file, type);
    if (type != K_LEVEL_PLATEFORMS) return 1;
    ReadRaw(file, &m_uiState, 1);
    IKFile_ReadRef(file, &m_pSekens);
    IKFile_ReadRef(file, &m_pFlashUI);
    IKFile_ReadRef(file, &m_pOpeningStartMsgOut);
    IKFile_ReadRef(file, &m_pOpeningEndMsgIn);
    IKFile_ReadRef(file, &m_pClosingStartMsgOut);
    IKFile_ReadRef(file, &m_pClosingEndMsgIn);
    return 1;
}

// 0x0017ac78 CKFlashUICinematicBloc_RecursiveRegistration
void CKFlashUICinematicBloc::RecursiveRegistration(int32_t type) {
    IKCinematicBloc::RecursiveRegistration(type);  // 0x0018e8d8
    if (type != 0) return;
    if (m_pFlashUI != nullptr) m_pFlashUI->RecursiveRegistration(0);  // vt+0x24
    if (m_pOpeningStartMsgOut != nullptr) m_pOpeningStartMsgOut->RecursiveRegistration(0);
    if (m_pOpeningEndMsgIn != nullptr) m_pOpeningEndMsgIn->RecursiveRegistration(0);
    if (m_pClosingStartMsgOut != nullptr) m_pClosingStartMsgOut->RecursiveRegistration(0);
    if (m_pClosingEndMsgIn != nullptr) m_pClosingEndMsgIn->RecursiveRegistration(0);
}

// 0x0017ac10 CKFlashUICinematicBloc_PostLoad
int32_t CKFlashUICinematicBloc::PostLoad(int32_t type) {
    IKCinematicBloc::PostLoad(type);  // 0x0018eac0 (1)
    if (type == K_LEVEL_PLATEFORMS && m_pFlashUI != nullptr) m_pFlashUI->HideInterfaceHierarchy(1);  // 0x0006f3d0
    return 1;
}

void CKFlashUICinematicBloc::ApplySubtitleLink() {
    CKFlashUI* ui = m_pFlashUI;
    if ((m_DataFlags & 0x800) != 0 && (Sekensor()->m_unk2c & 1) == 0) {
        ui->m_baFlags = (ui->m_baFlags & 0xffffffdfu) | 0x20u;
        ui->HideAllHotSpotHierarchy();  // 0x0006dff0
        return;
    }
    ui->m_baFlags &= 0xffffffdfu;
}

// 0x0017a870 CKFlashUICinematicBloc_ReleaseUIIfUnshared_maybe: the scenes from the last; a playing scene's running elements
// (+0x0c, linked by +0x04) other than this bloc that are Flash UI blocs (IsKindOfClass 0x8c8) with the same interface keep it.
void CKFlashUICinematicBloc::ReleaseUIIfUnshared(int32_t force) {
    if (m_pFlashUI == nullptr) return;
    if (force == 0) {
        uint32_t count = 0;
        IKSerializable** scenes = static_cast<CKSrvCinematic*>(g_pEngine->m_srvCinematic)->GetScenes(&count);  // 0x001665e8
        for (count = count - 1; count != 0xffffffffu; count = count - 1) {
            const CKCinematicScene* scene = static_cast<const CKCinematicScene*>(scenes[count]);
            if ((scene->m_baData & 1u) == 0) continue;
            for (IKCinematicElement* element = scene->m_pActiveNodes; element != nullptr; element = element->m_pNext) {
                if (element == this) continue;
                if (element->IsKindOfClass(0x8c8) != 0 &&  // vt+0x08
                    static_cast<CKFlashUICinematicBloc*>(element)->m_pFlashUI == m_pFlashUI) {
                    return;
                }
            }
        }
    }
    m_pFlashUI->StopInterface(1);  // 0x0006f8b0
    g_pEngine->m_input->SetMappingEnabled(1, static_cast<uint8_t>((m_DataFlags >> 9) & 1u));  // 0x00107618
}

// 0x0017ade0 CKFlashUICinematicBloc_MessageProc. In state 2 the closing-end message releases and completes the bloc, then
// (as in state 1) the opening-end message completes it too.
int32_t CKFlashUICinematicBloc::MessageProc(uint16_t message, void* data) {
    const int32_t element = ElementMessageProc(message, data);  // 0x0018faf8
    int32_t own = 1;
    if (message == 0x2300) {
        if ((m_DataFlags & 1u) != 0) {
            const uint8_t state = m_uiState;
            if (state == 0) {
                if (static_cast<void*>(m_pOpeningEndMsgIn) == data) {
                    m_uiState = 1;
                    m_DataFlags = (m_DataFlags & 0xfffffbffu) | 0x400u;
                }
            } else if (state == 1 || state == 2) {
                if (state == 2 && static_cast<void*>(m_pClosingEndMsgIn) == data) {
                    ReleaseUIIfUnshared(0);
                    Complete();  // vt+0x64
                }
                if (static_cast<void*>(m_pOpeningEndMsgIn) == data) Complete();  // vt+0x64
            }
        }
        own = 0;
    }
    if (element == 3 || own == 3) return 3;
    if (element == 2 || own == 2) return 2;
    if (element == 0) return 0;
    return own;
}

// 0x0017b538 CKFlashUICinematicBloc_Start: the blocs' common start; with an interface: state 0, the interface started
// (shown), the subtitle link, the opening-start message posted, the input configuration 1's state kept in flag 0x200 and
// set from flag 0x100, flag 0x400 cleared.
void CKFlashUICinematicBloc::Start() {
    StartCommon();
    if (m_pFlashUI == nullptr) return;
    m_uiState = 0;
    m_pFlashUI->StartInterface(1);  // 0x0006f6e0
    ApplySubtitleLink();
    if (m_pOpeningStartMsgOut != nullptr) m_pOpeningStartMsgOut->PostFlashMessage();  // 0x00075610
    const uint8_t enabled = g_pEngine->m_input->IsMappingEnabled(1);  // 0x00104af0
    m_DataFlags = (m_DataFlags & 0xfffffdffu) | ((static_cast<uint32_t>(enabled) << 9) & 0x1fe00u);
    g_pEngine->m_input->SetMappingEnabled(1, static_cast<uint8_t>((m_DataFlags >> 8) & 1u));
    m_DataFlags &= 0xfffffbffu;
}

// 0x0017b280 CKFlashUICinematicBloc_Update: (unless its sekens stopped it) the subtitle link; state 0 without an
// opening-end message opens at once (state 1, flag 0x400); state 1 requests the sekens once (flag 0x400: its flags 0x10
// and 0x20 = flag 0x800), then waits while it runs; when the sekensor's current sekens runs with its flag bit 4 the bloc
// completes, else it closes (state 2, the closing-start message); state 2 without a closing-end message releases the
// interface and completes.
void CKFlashUICinematicBloc::Update(IKTime* /*time*/) {
    if (CheckSekensStop() == 0) return;
    if (m_pFlashUI != nullptr) ApplySubtitleLink();
    uint8_t state = m_uiState;
    if (state == 0) {
        if (m_pOpeningEndMsgIn != nullptr) return;
        m_uiState = 1;
        m_DataFlags = (m_DataFlags & 0xfffffbffu) | 0x400u;
        state = m_uiState;
    }
    if (state == 1) {
        bool waiting = false;
        if ((m_DataFlags & 0x400u) != 0) {
            m_DataFlags &= 0xfffffbffu;
            if (m_pSekens != nullptr) {
                m_pSekens->m_flags = (m_pSekens->m_flags & 0xffffffefu) | 0x10u;
                m_pSekens->m_flags = (m_pSekens->m_flags & 0xffffffdfu) | (((m_DataFlags >> 11) & 1u) << 5);
                Sekensor()->RequestSekens(m_pSekens);  // 0x001f89b0
                waiting = Sekensor()->IsSekensDone(m_pSekens) == 0;  // 0x001f4728
            }
        } else if (m_pSekens != nullptr) {
            waiting = Sekensor()->IsSekensDone(m_pSekens) == 0;
        }
        if (waiting) {
            state = m_uiState;
        } else if (Sekensor()->IsCurrentSekensRunningWithFlag14Bit4() != 0) {  // 0x001f88f0
            Complete();  // vt+0x64
            state = m_uiState;
        } else {
            m_uiState = 2;
            if (m_pClosingStartMsgOut != nullptr) {
                m_pClosingStartMsgOut->PostFlashMessage();
                state = m_uiState;
            } else {
                state = 2;
            }
        }
    }
    if (state != 2) return;
    if (m_pClosingEndMsgIn != nullptr) return;
    ReleaseUIIfUnshared(0);
    Complete();  // vt+0x64
}

// 0x0017b1b0 CKFlashUICinematicBloc_Stop: state 2 (closing), the closing-start message posted, the sekens stopped.
void CKFlashUICinematicBloc::Stop() {
    m_uiState = 2;
    if (m_pClosingStartMsgOut != nullptr) m_pClosingStartMsgOut->PostFlashMessage();
    if (m_pSekens != nullptr) Sekensor()->StopSekens(m_pSekens);  // 0x001f8ce0
}

// 0x0017b148 CKFlashUICinematicBloc_Abort: not running, the interface released (forced), the sekens stopped.
void CKFlashUICinematicBloc::Abort() {
    m_DataFlags &= 0xfffffffeu;
    ReleaseUIIfUnshared(1);
    if (m_pSekens != nullptr) Sekensor()->StopSekens(m_pSekens);
}

// 0x0017aa38 CKFlashUICinematicBloc_Complete
void CKFlashUICinematicBloc::Complete() { CompleteBloc(); }

// 0x0017b9b0 CKFlashUICinematicBloc_OnPause: the interface's flag 0x20 set, its hot spots hidden, the interface paused.
void CKFlashUICinematicBloc::Pause() {
    CKFlashUI* ui = m_pFlashUI;
    if (ui == nullptr) return;
    ui->m_baFlags = (ui->m_baFlags & 0xffffffdfu) | 0x20u;
    ui->HideAllHotSpotHierarchy();
    m_pFlashUI->PauseInterface();  // 0x0006d510
}

// 0x0017b8f0 CKFlashUICinematicBloc_OnResume: the interface playing again (0x0006e418), then the subtitle link.
void CKFlashUICinematicBloc::Resume() {
    if (m_pFlashUI == nullptr) return;
    m_pFlashUI->ResumeInterface();
    ApplySubtitleLink();
}
