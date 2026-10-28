// CKFlashManager.cpp - reconstructed original translation unit 0x6c6e8-0x6d460 (GAME_TOC1, main_toc1), 31 functions, 28 live.
// Primary class: CKFlashManager  key 0x70d  category Graphical  size 0x14  vtable 0xb16018
// Other owners: FlashUIList (2), UI2D (1), Rt2dDevice (1), FlashTextRegistry (1), DrawFlashUIManagerEntries (1), CKFlashUI (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x6c6e8  CKFlashManager_Delete
//   [ ] 0x6c738  CKFlashManager_RecursiveRegistration
//   [x] 0x6c798  CKFlashManager_MessageProc
//   [x] 0x6c7a0  CKFlashManager_GetInputMapping_maybe
//   [ ] 0x6c7a8  CKFlashManager_FindUIByMaestro_maybe  [dead]
//   [ ] 0x6c7f0  RegisterCKFlashManagerType
//   [ ] 0x6c868  _GLOBAL__I_6c868
//   [x] 0x6c878  CKFlashManager_BindPlayerInputMapping_maybe
//   [x] 0x6c990  UI2D_DestroyRt2dFreeLists_maybe
//   [x] 0x6c9b8  Rt2dDevice_Init_maybe
//   [ ] 0x6ca18  CKFlashManager_Construct  [dead]
//   [ ] 0x6ca48  CKFlashManager_Construct_2  [dead]
//   [x] 0x6ca78  CKFlashManager_DeleteArray
//   [x] 0x6cb20  CKFlashManager_VisitVisibleUIs_maybe
//   [x] 0x6cbc0  FlashTextRegistry_RefreshAll_maybe
//   [x] 0x6cc30  FlashUIList_ReapplyTextFonts_maybe
//   [x] 0x6cca0  CKFlashManager_ApplyFontsToAllUIs_maybe
//   [x] 0x6cd30  CKFlashManager_UpdateScreenTransforms_maybe
//   [x] 0x6cda0  FlashUIList_HideAllShown_maybe
//   [x] 0x6ce58  DrawFlashUIManagerEntries
//   [x] 0x6cef8  CKFlashManager_UpdateAllUIs_maybe
//   [ ] 0x6cf98  CKFlashManager_Save
//   [x] 0x6cfa0  CKFlashManager_Load
//   [x] 0x6d128  CKFlashManager_PostLoad
//   [x] 0x6d130  CKFlashManager_Destroy
//   [x] 0x6d180  CKFlashUI_MaestroMessageHandler_maybe
//   [x] 0x6d268  CKFlashManager_Create
//   [x] 0x6d2b8  CKFlashManager_CreateArray
//   [x] 0x6d370  CKFlashManager_DeletingDestructor
//   [x] 0x6d3d0  CKFlashManager_Destructor
//   [ ] 0x6d418  CKFlashManager_DestructBody
//
//   [x] 0x998ca8  CKFlashManager_GetClassType  [inline]
//   [x] 0x998cb0  CKFlashManager_GetClassID  [inline]
//   [x] 0x998cb8  CKFlashManager_GetSerializationFlags  [inline]
//   [x] 0x998cc0  CKFlashManager_IsKindOfClass  [inline]
#include "k2000/graphical/ui/CKFlashManager.h"

#include "Renderware/rt2d/Rt2d.h"
#include "Renderware/rt2danim/Rt2dAnim.h"
#include "k2000/graphical/ui/CKFlashUI.h"
#include "k2000/input/CKInputDico.h"
#include "k2000/io/IKFile.h"
#include "k2000/managers/CKInput.h"
#include "k2000/memory/Mem.h"
#include "k2000/misc/Engine.h"

// Inlined in 0x0006d268 CKFlashManager_Create: the vtable, then the engine slot (+0x3c).
CKFlashManager::CKFlashManager() { Engine_SetFlashManager(this); }

// 0x0006d3d0 CKFlashManager_Destructor
CKFlashManager::~CKFlashManager() { Engine_SetFlashManager(nullptr); }

CKFlashUI* CKFlashManager::GetInterfaceByIndex(uint32_t index) const { return static_cast<CKFlashUI*>(m_apFlashUI[index]); }

// 0x0006cfa0 CKFlashManager_Load
int32_t CKFlashManager::Load(IKFile* file, int32_t type) {
    if (type != K_LEVEL_PLATEFORMS) return 1;
    ReadU32LE(file, &m_ui32NbFlashUI);
    if (m_ui32NbFlashUI == 0) {
        m_apFlashUI = nullptr;
        return 1;
    }
    m_apFlashUI = static_cast<IKSerializable**>(
        Mem_AllocAligned16(m_ui32NbFlashUI * static_cast<uint32_t>(sizeof(IKSerializable*))));
    IKFile_ReadObjectRefArray(file, m_apFlashUI, m_ui32NbFlashUI);
    return 1;
}

// 0x0006d130 CKFlashManager_Destroy
void CKFlashManager::Destroy() {
    if (m_apFlashUI != nullptr) {
        Mem_FreeAligned16(m_apFlashUI);
        m_apFlashUI = nullptr;
    }
    m_ui32NbFlashUI = 0;
}

// 0x0006c9b8 Rt2dDevice_Init_maybe (XXL2 InitializeManager)
void CKFlashManager::InitializeManager() {
    m_bLockInputUpdate = 0;
    Rt2dAnimOpen();               // 0x6f7cf0 _rt2dFreeListsCreate_maybe
    Rt2dDeviceSetFlat(0x1.f4p+8f);  // 500.0 (0x407f400000000000)
    Rt2dMessageQueueSetDefaultSize(0x100);
    m_ui32NbFlashUI = 0;
    m_pInputDico = nullptr;
}

// 0x0006c990 UI2D_DestroyRt2dFreeLists_maybe (XXL2 DestroyManager)
void CKFlashManager::DestroyManager() { Rt2dAnimClose(); }

// 0x0006c878 CKFlashManager_BindPlayerInputMapping_maybe (XXL2 SetInputConfig). Called by
// IKGameManager_ResetRuntimeImpl (C1.6).
// BUG(original): without a "Flash Manager" project the dico is null and SetActionEnabled dereferences it.
void CKFlashManager::SetInputConfig(uint8_t player) {
    CKInput* input = g_pEngine->m_input;
    const uint32_t project = static_cast<uint32_t>(input->FindMappingIndexByName("Flash Manager")) & 0xff;
    CKInputDico* dico = nullptr;
    if (project != 0xff) dico = &input->m_aaInputDico[project][player];
    m_pInputDico = dico;
    m_pInputDico->SetActionEnabled(0xe, 1);
    m_pInputDico->SetActionEnabled(4, 1);
    m_pInputDico->SetActionEnabled(5, 1);
    m_pInputDico->SetActionEnabled(6, 1);
    m_pInputDico->SetActionEnabled(7, 1);
    m_pInputDico->SetActionEnabled(8, 1);
    m_pInputDico->SetActionEnabled(9, 1);
}

// 0x0006cb20 CKFlashManager_VisitVisibleUIs_maybe (XXL2 PreUpdate): CKFlashUI::PreUpdate (0x6d508, empty)
// of every interface not flagged kDontUpdate.
void CKFlashManager::PreUpdate(IKTime* time) {
    for (uint32_t i = 0; i < m_ui32NbFlashUI; ++i) {
        CKFlashUI* ui = GetInterfaceByIndex(i);
        if ((ui->m_baFlags & CKFlashUI::kDontUpdate) == 0) ui->PreUpdate(time);
    }
}

// 0x0006cef8 CKFlashManager_UpdateAllUIs_maybe (XXL2 Update)
void CKFlashManager::Update(IKTime* time) {
    for (uint32_t i = 0; i < m_ui32NbFlashUI; ++i) {
        CKFlashUI* ui = GetInterfaceByIndex(i);
        if ((ui->m_baFlags & CKFlashUI::kDontUpdate) == 0) ui->Update(time);
    }
}

// 0x0006ce58 DrawFlashUIManagerEntries (XXL2 Render)
void CKFlashManager::Render(IKTime* time) {
    for (uint32_t i = 0; i < m_ui32NbFlashUI; ++i) {
        CKFlashUI* ui = GetInterfaceByIndex(i);
        if ((ui->m_baFlags & CKFlashUI::kDontUpdate) == 0) ui->Render(time);
    }
}

// 0x0006cd30 CKFlashManager_UpdateScreenTransforms_maybe (XXL2 RefreshSize)
void CKFlashManager::RefreshSize() {
    for (uint32_t i = 0; i < m_ui32NbFlashUI; ++i) GetInterfaceByIndex(i)->InitializeMaestroScenePosition();
}

// 0x0006cbc0 FlashTextRegistry_RefreshAll_maybe (XXL2 RefreshAllTexts)
void CKFlashManager::RefreshAllTexts() {
    for (uint32_t i = 0; i < m_ui32NbFlashUI; ++i) GetInterfaceByIndex(i)->RefreshTexts();
}

// 0x0006cc30 FlashUIList_ReapplyTextFonts_maybe
void CKFlashManager::ReloadAllTextFonts() {
    for (uint32_t i = 0; i < m_ui32NbFlashUI; ++i) GetInterfaceByIndex(i)->ReloadTextFonts();
}

// 0x0006cca0 CKFlashManager_ApplyFontsToAllUIs_maybe
void CKFlashManager::UpdateLocalizedData(uint8_t /*first*/, void* /*errors*/) {
    for (uint32_t i = 0; i < m_ui32NbFlashUI; ++i) GetInterfaceByIndex(i)->ApplyFontsToTexts2();
}

// 0x0006cda0 FlashUIList_HideAllShown_maybe (XXL2 Stop): every started interface loses kNeverRender and
// is stopped and hidden.
void CKFlashManager::Stop() {
    for (uint32_t i = 0; i < m_ui32NbFlashUI; ++i) {
        CKFlashUI* ui = GetInterfaceByIndex(i);
        if ((ui->m_baFlags & CKFlashUI::kStateMask) != 2) continue;
        ui->m_baFlags &= ~CKFlashUI::kNeverRender;
        ui->StopInterface(1);
    }
}

// 0x0006d180 CKFlashUI_MaestroMessageHandler_maybe (XXL2 HandleMaestroEvent). The interfaces are searched
// from the last one.
Rt2dMessage* CKFlashManager::HandleMaestroEvent(Rt2dMaestro* maestro, Rt2dMessage* message) {
    if (message->messageType != rt2dMESSAGETYPEGETURL) return Rt2dMessageHandlerDefaultCallBack(maestro, message);
    CKFlashManager* manager = g_pEngine->m_flashManager;
    CKFlashUI* owner = nullptr;
    for (uint32_t i = manager->m_ui32NbFlashUI; i != 0;) {
        --i;
        CKFlashUI* ui = manager->GetInterfaceByIndex(i);
        if (ui->m_pMaestro == maestro) {
            owner = ui;
            break;
        }
    }
    // BUG(original): a maestro no interface owns queues on a null interface (TranslateMessageIn reads
    // its +0x24). DEV: skipped here.
    if (owner != nullptr) owner->TranslateMessageIn(message->intParam1);
    return Rt2dMessageHandlerDefaultCallBack(maestro, message);
}
