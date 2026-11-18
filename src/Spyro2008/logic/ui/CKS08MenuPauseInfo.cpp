// CKS08MenuPauseInfo.cpp - reconstructed original translation unit 0x55f7a0-0x560f38 (GAME_TOC2, main_toc2), 21 functions, 19 live.
// Primary class: CKS08MenuPauseInfo  key 0x960c  category Logic  size ?  vtable 0xb2d0a8
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x55f7a0  CKS08MenuPauseInfo_Delete
//   [ ] 0x55f7f0  CKS08MenuPauseInfo_Construct  [dead]
//   [x] 0x55f8b8  CKS08MenuPauseInfo_CheckContinueInput_maybe
//   [x] 0x55fa18  CKS08MenuPauseInfo_RecursiveRegistration
//   [x] 0x55fa88  CKS08MenuPauseInfo_Destroy  (inherited: TocBridge_CKMenuBase_114c_maybe_Destroy)
//   [x] 0x55fab0  CKS08MenuPauseInfo_DeleteArray
//   [ ] 0x55fb50  RegisterCKS08MenuPauseInfoClass
//   [ ] 0x55fbd8  _GLOBAL__D_55fbd8
//   [ ] 0x55fbe8  _GLOBAL__I_55fbe8
//   [x] 0x55fbf8  CKS08MenuPauseInfo_SetTitleText_maybe
//   [x] 0x55fc60  CKS08MenuPauseInfo_ShowNextPage_maybe
//   [x] 0x55fdd0  CKS08MenuPauseInfo_OnItemEvent
//   [x] 0x55fe00  CKS08MenuPauseInfo_OnStatePhase
//   [ ] 0x560580  CKS08MenuPauseInfo_Construct_2  [dead]
//   [x] 0x560648  CKS08MenuPauseInfo_Load
//   [x] 0x5607c8  CKS08MenuPauseInfo_CreateArray
//   [x] 0x560920  CKS08MenuPauseInfo_Create
//   [ ] 0x560a28  CKS08MenuPauseInfo_Save
//   [x] 0x560b30  CKS08MenuPauseInfo_DeletingDestructor
//   [x] 0x560c88  CKS08MenuPauseInfo_Destructor
//   [x] 0x560de0  CKS08MenuPauseInfo_Destructor_2
//
//   [x] 0x9ca168  CKS08MenuPauseInfo_IsKindOfClass  [inline]
//   [x] 0x9ca1a8  CKS08MenuPauseInfo_GetClassType  [inline]
//   [x] 0x9ca1b0  CKS08MenuPauseInfo_GetClassID  [inline]
//   [x] 0x9ca1b8  CKS08MenuPauseInfo_vfB8  [inline]
//   [x] 0x9ca1c0  CKS08MenuPauseInfo_vfE0  [inline]
//   [x] 0x9ca1c8  CKS08MenuPauseInfo_GetWidgetSlotCount  [inline]
//   [x] 0x9ca1d0  CKS08MenuPauseInfo_GetWidgetSlots  [inline]
//   [x] 0x9ca1e0  CKS08MenuPauseInfo_vfC4  [inline]
//   [x] 0x9ca1e8  CKS08MenuPauseInfo_vfC8  [inline]
//   [x] 0x9ca1f8  CKS08MenuPauseInfo_vfCC  [inline]
//   [x] 0x9ca208  CKS08MenuPauseInfo_vfBC  [inline]
//   [x] 0x9ca210  CKS08MenuPauseInfo_vfC0  [inline]
#include "Spyro2008/logic/ui/CKS08MenuPauseInfo.h"

#include <cstring>

#include "Spyro2008/logic/CKS08GameManager.h"
#include "k2000/graphical/fx/CBillboard2d.h"
#include "k2000/graphical/ui/CText2d.h"
#include "k2000/input/CKInputDico.h"
#include "k2000/io/IKFile.h"
#include "k2000/logic/IKFxData.h"
#include "k2000/logic/fx/CKTimeScalingFxData.h"
#include "k2000/logic/fx/CKTimeScalingNodeFx.h"
#include "k2000/managers/CKInput.h"
#include "k2000/memory/Mem.h"
#include "k2000/misc/CKInterfaceButtonBase.h"
#include "k2000/misc/Engine.h"
#include "k2000/services/CKSrvFx.h"
#include "k2000/system/CTimeManager.h"
#include "k2000/system/IKTime.h"

// 0x00560c88 CKS08MenuPauseInfo_Destructor: the page vector, then the base.
CKS08MenuPauseInfo::~CKS08MenuPauseInfo() {
    if (m_aPageTextIds.m_pBlock != nullptr) Mem_FreeAligned16(m_aPageTextIds.m_pBlock);
    m_aPageTextIds.m_ui32NbUsedElt = 0;
    m_aPageTextIds.m_pBlock = nullptr;
}

// 0x00560648 CKS08MenuPauseInfo_Load. The page vector gets a block for one id (capacity 1; the length
// and any earlier block are left as they are).
int32_t CKS08MenuPauseInfo::Load(IKFile* file, int32_t type) {
    CKMenuBase114c::Load(file, type);
    if (type != K_LEVEL_PLATEFORMS) return 1;
    m_ui32Page = 0;
    m_aPageTextIds.m_ui32NbElt = 1;
    m_aPageTextIds.m_pBlock = static_cast<IKSerializable**>(Mem_AllocAligned16(static_cast<uint32_t>(sizeof(IKSerializable*))));
    m_pTimeScalingNode = nullptr;
    m_bTimeScaling = 1;
    IKFile_ReadRef(file, &m_pTimeScalingFx);
    ReadF32LE(file, &m_fPageDuration);
    return 1;
}

namespace {
// 0x0006a100 Text2dBlock_ClearTextState_maybe (CText2d +0x28, the text part): no variables, no words, auto-size off.
void ClearTextState(IKText2d* text) {
    text->m_ui32VarsCount = 0;
    text->m_ui32WordsCount = 0;
    text->m_bAutoSize = 0;
}

// The billboard's colour (IKBillboard2d +0x0c, raw bytes) with another alpha (byte 3), through IKBillboard2d_SetColor
// (vt+0x28 of the part at +0x28).
void SetBillboardAlpha(IKSerializable* element, uint8_t alpha) {
    IKBillboard2d* billboard = static_cast<CBillboard2d*>(element);
    uint8_t color[4];
    std::memcpy(color, &billboard->m_Color, sizeof color);
    color[3] = alpha;
    billboard->SetColor(color);
}

CKS08GameManager* GameManager(CKS08MenuPauseInfo* menu) { return static_cast<CKS08GameManager*>(menu->m_pGameManager); }
}  // namespace

// 0x0055fbf8 CKS08MenuPauseInfo_SetTitleText_maybe
void CKS08MenuPauseInfo::SetTitleText(IKSerializable* text) {
    CText2d* title = static_cast<CText2d*>(m_aWidgetSlots[0].m_pElement);
    if (title == nullptr) return;
    title->SetTextById(text);  // vt+0x88
    m_unk91 = 1;
}

// 0x0055fc60 CKS08MenuPauseInfo_ShowNextPage_maybe
void CKS08MenuPauseInfo::ShowNextPage() {
    if (m_ui32Page < m_aPageTextIds.m_ui32NbUsedElt) {
        CText2d* page = static_cast<CText2d*>(m_aWidgetSlots[2].m_pElement);
        if (page != nullptr) page->SetTextById(m_aPageTextIds.m_pBlock[m_ui32Page]);  // vt+0x88
        m_fPageTimer = m_fPageDuration;
        ++m_ui32Page;
        return;
    }
    m_unk91 = 0;
    m_ui32Page = 0;
    if (CText2d* title = static_cast<CText2d*>(m_aWidgetSlots[0].m_pElement)) {
        ClearTextState(title);
        title->SetTextById(nullptr);
    }
    if (CText2d* page = static_cast<CText2d*>(m_aWidgetSlots[2].m_pElement)) {
        ClearTextState(page);
        page->SetTextById(nullptr);
    }
    GameManager(this)->m_unkAFC &= 0xffffff7fu;
}

// 0x0055f8b8 CKS08MenuPauseInfo_CheckContinueInput_maybe. The "Flash Manager" project's dico at +0x10 of its entry is
// configuration 1 (CKInputDico is 0x10 bytes); without the project the original reads a null dico.
void CKS08MenuPauseInfo::CheckContinueInput() {
    CKInput* input = g_pEngine->m_input;
    const uint32_t project = static_cast<uint32_t>(input->FindMappingIndexByName("Flash Manager")) & 0xff;
    const CKInputDico* dico = project != 0xff ? &input->m_aaInputDico[project][1] : nullptr;
    CKS08GameManager* manager = GameManager(this);
    for (uint8_t player = 0; player < manager->GetPlayerCount(); ++player) {  // vt+0x154, read every turn
        if (manager->IsPlayerActive(player) == 0) continue;  // vt+0x180
        if (dico->GetButtonState(static_cast<int32_t>((player * 0x14u + 0xeu) & 0xfeu)) == 0xff) SetItemState(0, 1, 0);
    }
}

// 0x0055fdd0 CKS08MenuPauseInfo_OnItemEvent
void CKS08MenuPauseInfo::OnItemState(uint8_t item, uint8_t state, uint8_t arg) {
    if (arg != 2 || state != 4 || item != 0) return;
    if (m_bTimeScaling == 0) return;
    ShowNextPage();
}

// 0x0055fe00 CKS08MenuPauseInfo_OnStatePhase
uint8_t CKS08MenuPauseInfo::OnMenuState(int32_t phase, uint8_t /*other*/) {
    CKS08GameManager* manager = GameManager(this);
    if (phase == 1) {
        manager->SetPlayerActive(0, 1);                                                    // vt+0x184
        manager->SetPlayerActive(1, static_cast<uint8_t>(manager->GetPlayerCount() == 2));  // vt+0x184, vt+0x154
        m_fPageTimer = 0.0f;
        CKInterfaceButtonBase* button = nullptr;
        if (m_bTimeScaling != 0 && m_pTimeScalingNode == nullptr) {
            // The FX service's start of the data, inlined here, with the menu as owner.
            CKSrvFx* service = static_cast<CKSrvFx*>(g_pEngine->m_srvFx);
            m_pTimeScalingNode = service->StartEffect(static_cast<IKFxData*>(m_pTimeScalingFx), this);
            manager->SetInputBlocked(1);  // vt+0x1e8
            if (m_apButtons.m_ui32NbUsedElt != 0) button = static_cast<CKInterfaceButtonBase*>(m_apButtons.m_pBlock[0]);
            button->Show();  // vt+0x6c
        } else {
            m_fPageTimer = m_fPageDuration;
            if (m_apButtons.m_ui32NbUsedElt != 0) button = static_cast<CKInterfaceButtonBase*>(m_apButtons.m_pBlock[0]);
            button->Hide();  // vt+0x70
        }
        if (m_unk91 == 0) {
            if (m_aWidgetSlots[1].m_pElement != nullptr) SetBillboardAlpha(m_aWidgetSlots[1].m_pElement, 0);
            if (CText2d* title = static_cast<CText2d*>(m_aWidgetSlots[0].m_pElement)) {
                ClearTextState(title);
                title->SetTextById(nullptr);  // vt+0x88
            }
        } else if (m_aWidgetSlots[1].m_pElement != nullptr) {
            SetBillboardAlpha(m_aWidgetSlots[1].m_pElement, 0xff);
        }
        if (m_ui32Page < m_aPageTextIds.m_ui32NbUsedElt) {
            CText2d* page = static_cast<CText2d*>(m_aWidgetSlots[2].m_pElement);
            if (page != nullptr) page->SetTextById(m_aPageTextIds.m_pBlock[m_ui32Page]);
            ++m_ui32Page;
        }
    } else if (phase == 2) {
        m_aPageTextIds.m_ui32NbUsedElt = 0;
        m_ui32Page = 0;
        if (m_pTimeScalingNode != nullptr) {
            static_cast<CKTimeScalingNodeFx*>(m_pTimeScalingNode)
                ->StopIfOwnedBy(static_cast<CKTimeScalingFxData*>(m_pTimeScalingFx), this);
            m_pTimeScalingNode = nullptr;
            manager->SetInputBlocked(0);  // vt+0x1e8
        }
        manager->m_unkAFC &= 0xffffff7fu;
    } else if (phase == 0) {
        const float dt = g_pEngine->m_timeManager->m_pTime->m_afDeltaTime[1];
        if (m_bTimeScaling == 0) {
            m_fPageTimer = m_fPageTimer - dt;
            if (m_fPageTimer <= 0.0f) ShowNextPage();  // fcmpu + cror lt|eq against 0 (TOC -0x7c0c)
        }
        CheckContinueInput();
    }
    return static_cast<uint8_t>(GetMenuId());  // vt+0xe0
}

// 0x0055fa18 CKS08MenuPauseInfo_RecursiveRegistration: the referenced objects' registration, then the base.
void CKS08MenuPauseInfo::RecursiveRegistration(int32_t type) {
    m_pTimeScalingFx->RecursiveRegistration(type);
    CKMenuBase114c::RecursiveRegistration(type);
}
