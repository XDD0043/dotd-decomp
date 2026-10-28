// KBase730C.cpp - reconstructed original translation unit 0x5122f8-0x51b9d0 (GAME_TOC1, main_toc1), 50 functions, 46 live.
// Primary owner: KBase730C (not a registered class)
// Other owners: CKMenuBase (4)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x512040  KBase730C_SetItemState  (the TU map lists it in CKS08GameStructure.cpp)
//   [ ] 0x5122f8  KBase730C_CallOwnerVfDCObjectVf80_maybe
//   [ ] 0x512370  KBase730C_SetElementPosition_maybe
//   [ ] 0x512510  KBase730C_SetElementX_maybe
//   [ ] 0x5126a0  KBase730C_SetElementY_maybe
//   [ ] 0x512830  KBase730C_GetElementX_maybe
//   [x] 0x512938  KBase730C_ReadNavDirection
//   [x] 0x512d68  KBase730C_HandleShortcutButtons
//   [x] 0x513188  KBase730C_HandleValidateButton
//   [x] 0x513700  KBase730C_Open_maybe
//   [ ] 0x5137d8  KBase730C_SetFlashHidden_maybe
//   [ ] 0x513848  FUN_00513848  [dead]
//   [ ] 0x513880  KBase730C_PlayVideoSegmentById_maybe
//   [x] 0x5139a0  KBase730C_vf54
//   [ ] 0x513ab0  KBase730C_FindWidgetByName_maybe
//   [ ] 0x513b48  KBase730C_ZeroVfCCBuffer_maybe  [dead]
//   [ ] 0x513c10  CKMenuBase_114c_maybe_Save
//   [ ] 0x513c38  CKMenuBase_114c_maybe_LevelReset
//   [ ] 0x513c60  CKMenuBase_114c_maybe_ClearReferences
//   [ ] 0x513da8  StaticInitAndDestruction_513da8
//   [ ] 0x513dd8  _GLOBAL__D_513dd8
//   [ ] 0x513de8  _GLOBAL__I_513de8
//   [x] 0x513df8  KBase730C_RefreshOptionWidgets_maybe
//   [x] 0x513f88  KBase730C_Close
//   [x] 0x5140b0  KBase730C_vfA0
//   [ ] 0x514228  KBase730C_GetSelectionOfFirstActivePlayer_maybe
//   [ ] 0x514388  KBase730C_SetSelectionOfFirstActivePlayer_maybe
//   [x] 0x5144f0  KBase730C_PlayScreenVideo_maybe
//   [ ] 0x514668  KBase730C_CallOwnerVfDCObjectVf78AfterVf308_maybe
//   [x] 0x514720  KBase730C_TryBackButton
//   [x] 0x5148c0  KBase730C_StartTransitionToMenu
//   [x] 0x514a00  KBase730C_Open
//   [ ] 0x514e10  KBase730C_GetElementY_maybe
//   [x] 0x514f18  KBase730C_PostLoad
//   [x] 0x514f98  KBase730C_SetVisible_maybe
//   [x] 0x515050  KBase730C_vf9C
//   [ ] 0x515128  FUN_00515128  [dead]
//   [x] 0x5151b0  KBase730C_ResetWidgets_maybe
//   [ ] 0x515848  FUN_00515848  [dead]
//   [ ] 0x5159a8  KBase730C_FindWidgetByName_2_maybe
//   [ ] 0x515a48  KBase730C_FindWidgetByName_3_maybe
//   [ ] 0x515ae8  KBase730C_SendFlashMessageByName_maybe
//   [x] 0x515b78  KBase730C_MessageProc
//   [x] 0x515f20  KBase730C_FindItemUnderCursor
//   [x] 0x516de0  KBase730C_MoveFocusByInput_maybe
//   [x] 0x518248  KBase730C_UpdateFocus_maybe
//   [x] 0x518428  KBase730C_UpdateInput
//   [x] 0x518760  KBase730C_HandleStatePhase
//   [x] 0x518f28  KBase730C_ClearSlotsAndClose_maybe
//   [x] 0x519130  KBase730C_UpdateElementAnimations_maybe
//   [x] 0x51a160  CKMenuBase_114c_maybe_Load
//
//   [x] 0x9983f8  KBase730C_GetClassGroup  [inline]
//   [x] 0x998400  KBase730C_GetClassId  [inline]
//   [x] 0x998408  KBase730C_vf50  [inline]
//   [x] 0x998410  KBase730C_vf54_2  [inline]
//   [x] 0x998418  KBase730C_vf58  [inline]
//   [x] 0x998420  KBase730C_vf5C  [inline]
//   [x] 0x998428  KBase730C_vf68  [inline]
//   [x] 0x998430  KBase730C_vf6C  [inline]
//   [x] 0x998438  KBase730C_vf70  [inline]
//   [x] 0x998440  KBase730C_vf74  [inline]
//   [x] 0x998448  KBase730C_vf78  [inline]
//   [x] 0x998450  KBase730C_vf7C  [inline]
//   [x] 0x998458  KBase730C_vf80  [inline]
//   [x] 0x998460  KBase730C_DeletingDestructor  [inline]
//   [x] 0x9984a0  KBase730C_IsKindOf  [inline]
//   [x] 0x9984c0  KBase730C_Destructor  [inline]
//   [x] 0x9c7240  CKMenuBase_114c_maybe_IsKindOf  [inline]
//   [x] 0x9c7268  CKMenuBase_114c_maybe_GetClassGroup  [inline]
//   [x] 0x9c7270  CKMenuBase_114c_maybe_GetClassId  [inline]
//   [x] 0x9c7278  KBase730C_vf60  [inline]
//   [x] 0x9c7280  KStub_Return0_9c7280  [inline]
//   [x] 0x9c7288  KStub_Return0_9c7288  [inline]
//   [x] 0x9c7290  KStub_Return0_9c7290  [inline]
//   [x] 0x9c7298  KStub_Return0_9c7298  [inline]
//   [x] 0x9c72a0  KStub_Return0_9c72a0  [inline]
//   [x] 0x9c72a8  KStub_Return0_9c72a8  [inline]
//   [x] 0x9c72b0  KStub_Nop_9c72b0  [inline]
//   [x] 0x9c72b8  KStub_Nop_9c72b8  [inline]
//   [x] 0x9c72c0  KBase730C_vf64  [inline]
//   [x] 0x9c72d8  KStub_Return0_9c72d8  [inline]
//   [x] 0x9c72e0  CKMenuBase_114c_maybe_vfBC  [inline]
//   [x] 0x9c72e8  CKMenuBase_114c_maybe_vfC0  [inline]
//   [x] 0x9c72f0  CKMenuBase_114c_maybe_vfC4  [inline]
//   [x] 0x9c72f8  CKMenuBase_114c_maybe_vfC8  [inline]
//   [x] 0x9c7300  CKMenuBase_114c_maybe_vfCC  [inline]
//   [x] 0x9c7308  KStub_Return0_9c7308  [inline]
//   [x] 0x9c7310  KStub_Return0_9c7310  [inline]
//   [x] 0x9c7318  KBase730C_vfDC  [inline]
//   [x] 0x9c7360  KStub_Return0_9c7360  [inline]
//   [x] 0x9c7368  KStub_Nop_9c7368  [inline]
//   [x] 0x9c7370  KStub_Nop_9c7370  [inline]
//   [x] 0x9c7378  KStub_Return0_9c7378  [inline]
//   [x] 0x9c7380  KStub_Return255_9c7380  [inline]
//   [x] 0x9c7388  CKMenuBase_114c_maybe_Destructor  [inline]
//   [x] 0x9c74c0  CKMenuBase_114c_maybe_DeletingDestructor  [inline]
#include "Spyro2008/logic/CKMenuBase114c.h"
#include "Spyro2008/logic/CKS08GameStructure.h"

#include <cstring>

#include "Renderware/rpprtstd/RpPrtStd.h"
#include "k2000/core/Stub.h"
#include "k2000/graphical/system/CKVideoSegment.h"
#include "k2000/graphical/system/IKVideo.h"
#include "k2000/graphical/system/CKVideoSegment.h"
#include "k2000/graphical/system/CVideoManager.h"
#include "k2000/graphical/system/PS3_CKVideo.h"
#include "k2000/graphical/ui/CKFlashMessageIn.h"
#include "k2000/graphical/ui/CKFlashUI.h"
#include "k2000/io/IKFile.h"
#include "k2000/logic/CKSector.h"
#include "k2000/managers/CKInput.h"
#include "k2000/memory/Mem.h"
#include "k2000/misc/CKGameLoop.h"
#include "k2000/misc/Engine.h"
#include "k2000/system/CTimeManager.h"
#include "k2000/system/IKTime.h"
#include "k2000/ui/IKNode2d.h"
#include "Spyro2008/logic/CKS08GameManager.h"
#include "crt/ppc_ops.h"
#include "k2000/graphical/ui/CKFlashMessageOut.h"
#include "k2000/input/CKAction.h"
#include "k2000/input/CKInputDico.h"
#include "k2000/logic/CKInterfaceButton.h"
#include "k2000/logic/CKInterfaceButtonDouble.h"
#include "k2000/logic/CKInterfaceCheckBox.h"
#include "k2000/math/CVector2.h"
#include "k2000/misc/CKInterfaceButtonBase.h"
#include "k2000/scenegraph/CSGLeaf.h"
#include "k2000/scenegraph/CParticlesNodeFx.h"
#include "k2000/scenegraph/CNode.h"

namespace {

// The TVector sizing the Load inlines for each table: the capacity is set to the count and the block
// allocated for it, so the grow branch after it cannot run (kept as in the original).
template <class T, uint32_t Grow>
void LoadReserve(TVector<T, Grow>& v, uint32_t count) {
    v.m_ui32NbElt = count;
    v.m_pBlock = static_cast<T*>(Mem_AllocAligned16(count * static_cast<uint32_t>(sizeof(T))));
    if (v.m_ui32NbElt < count) {
        uint32_t capacity = (count / Grow) * Grow + Grow;
        if (capacity == 0) capacity = Grow;
        v.m_pBlock = static_cast<T*>(Mem_ReallocAligned16(v.m_pBlock, capacity * static_cast<uint32_t>(sizeof(T))));
        v.m_ui32NbElt = capacity;
    }
    v.m_ui32NbUsedElt = count;
}

// Read(dst, 4 * n) followed by lwbrx/stw on each word (the original's vector reads).
void ReadFloatsLE(IKFile* file, float* dst, uint32_t n) {
    for (uint32_t i = 0; i < n; ++i) ReadF32LE(file, &dst[i]);
}

}  // namespace

// The constructor every leaf's Create inlines (e.g. 0x0056e0f0 CKS08MenuBonus_Create), in its store
// order. KBase730C adds nothing. +0x04, +0x40..+0x44, +0x54..+0x80 and +0x90 are left as they are.
CKMenuBase114c::CKMenuBase114c() {
    m_pGameManager = nullptr;
    m_pFlashUI = nullptr;
    m_aNamedObjects.m_ui32NbElt = 5;
    m_aNamedObjects.m_pBlock = nullptr;
    m_aNamedObjects.m_ui32NbUsedElt = 0;
    m_aNodeAnims.m_ui32NbElt = 5;
    m_aNodeAnims.m_pBlock = nullptr;
    m_aNodeAnims.m_ui32NbUsedElt = 0;
    m_aElementAnims.m_ui32NbElt = 5;
    m_aElementAnims.m_pBlock = nullptr;
    m_aElementAnims.m_ui32NbUsedElt = 0;
    m_aDelayedShows.m_ui32NbElt = 5;
    m_aDelayedShows.m_pBlock = nullptr;
    m_aDelayedShows.m_ui32NbUsedElt = 0;
    m_aVideoTriggers.m_ui32NbElt = 8;
    m_aVideoTriggers.m_pBlock = nullptr;
    m_aVideoTriggers.m_ui32NbUsedElt = 0;
    m_apButtons.m_ui32NbElt = 3;
    m_apButtons.m_ui32NbUsedElt = 0;
    m_apButtons.m_pBlock = nullptr;
}

// 0x009c7388 CKMenuBase_114c_maybe_Destructor: the TVector destructors, last member first (the +0x48
// one does not clear its fields).
CKMenuBase114c::~CKMenuBase114c() {
    if (m_apButtons.m_pBlock != nullptr) Mem_FreeAligned16(m_apButtons.m_pBlock);
    m_apButtons.m_ui32NbUsedElt = 0;
    m_apButtons.m_pBlock = nullptr;
    if (m_aVideoTriggers.m_pBlock != nullptr) Mem_FreeAligned16(m_aVideoTriggers.m_pBlock);
    if (m_aDelayedShows.m_pBlock != nullptr) Mem_FreeAligned16(m_aDelayedShows.m_pBlock);
    m_aDelayedShows.m_ui32NbUsedElt = 0;
    m_aDelayedShows.m_pBlock = nullptr;
    if (m_aElementAnims.m_pBlock != nullptr) Mem_FreeAligned16(m_aElementAnims.m_pBlock);
    m_aElementAnims.m_ui32NbUsedElt = 0;
    m_aElementAnims.m_pBlock = nullptr;
    if (m_aNodeAnims.m_pBlock != nullptr) Mem_FreeAligned16(m_aNodeAnims.m_pBlock);
    m_aNodeAnims.m_ui32NbUsedElt = 0;
    m_aNodeAnims.m_pBlock = nullptr;
    if (m_aNamedObjects.m_pBlock != nullptr) Mem_FreeAligned16(m_aNamedObjects.m_pBlock);
    m_aNamedObjects.m_ui32NbUsedElt = 0;
    m_aNamedObjects.m_pBlock = nullptr;
}

// 0x0051a160 CKMenuBase_114c_maybe_Load. Only the level file (type 0) carries menu data. The tables
// are read from the last element down, except the video triggers and the reference groups.
int32_t CKMenuBase114c::Load(IKFile* file, int32_t type) {
    KBase730C::Load(file, type);
    if (type != K_LEVEL_PLATEFORMS) return 1;
    IKFile_ReadRef(file, &m_pGameManager);
    IKFile_ReadRef(file, &m_pFlashUI);

    uint32_t count = 0;
    ReadU32LE(file, &count);
    if (count != 0) {
        LoadReserve(m_aNamedObjects, count);
        for (uint32_t i = count; i-- != 0;) {
            NamedObject& entry = m_aNamedObjects.m_pBlock[i];
            ReadU32LE(file, &entry.m_ui32NameHash);
            IKFile_ReadRef(file, &entry.m_pObject);
        }
    }

    for (uint32_t i = GetWidgetSlotCount(); i-- != 0;) {
        IKFile_ReadRef(file, &GetWidgetSlots()[i].m_pHotSpot);
        IKFile_ReadRef(file, &GetWidgetSlots()[i].m_pElement);
    }

    ReadU32LE(file, &count);
    if (count != 0) {
        LoadReserve(m_aNodeAnims, count);
        for (uint32_t i = count; i-- != 0;) {
            NodeAnim& entry = m_aNodeAnims.m_pBlock[i];
            IKFile_ReadRef(file, &entry.m_pBinding);
            IKFile_ReadRef(file, &entry.m_pNode);
            ReadFloatsLE(file, entry.m_vUnk08, 3);
            ReadFloatsLE(file, entry.m_vUnk14, 3);
            ReadFloatsLE(file, entry.m_vUnk20, 3);
            ReadF32LE(file, &entry.m_fUnk2c);
            ReadF32LE(file, &entry.m_fUnk38);
            ReadF32LE(file, &entry.m_fUnk40);
            ReadF32LE(file, &entry.m_fUnk48);
            ReadU32LE(file, &entry.m_unk50);
        }
    }

    ReadU32LE(file, &count);
    if (count != 0) {
        LoadReserve(m_aElementAnims, count);
        for (uint32_t i = count; i-- != 0;) {
            ElementAnim& entry = m_aElementAnims.m_pBlock[i];
            IKFile_ReadRef(file, &entry.m_pBinding);
            IKFile_ReadRef(file, &entry.m_pElement);
            ReadFloatsLE(file, entry.m_vUnk0c, 2);
            ReadFloatsLE(file, entry.m_vUnk14, 2);
            ReadFloatsLE(file, entry.m_vUnk1c, 2);
            ReadF32LE(file, &entry.m_fUnk30);
            ReadF32LE(file, &entry.m_fUnk40);
            ReadU32LE(file, &entry.m_unk38);
            ReadU32LE(file, &entry.m_unk48);
            ReadF32LE(file, &entry.m_fUnk4c);
        }
    }

    ReadU32LE(file, &count);
    if (count != 0) {
        LoadReserve(m_aDelayedShows, count);
        for (uint32_t i = count; i-- != 0;) {
            DelayedShow& entry = m_aDelayedShows.m_pBlock[i];
            IKFile_ReadRef(file, &entry.m_pElement);
            IKFile_ReadRef(file, &entry.m_pShowSender);
            IKFile_ReadRef(file, &entry.m_pHideSender);
            ReadF32LE(file, &entry.m_fDelay);
            IKFile_ReadRef(file, &entry.m_pBinding);
        }
    }

    const uint32_t groups = Vf84();
    for (uint32_t i = 0; i < groups; ++i) {
        IKFile_ReadRef(file, &Vf88()[i].m_pObject);
        ReadU32LE(file, &Vf88()[i].m_unk04);
        ReadU32LE(file, &Vf88()[i].m_unk08);
        uint32_t refs = 0;
        ReadU32LE(file, &refs);
        for (uint32_t j = 0; j < refs; ++j) IKFile_ReadRef(file, &Vf8C(i)[j]);
    }

    if (VfC4() != 0) {
        IKSerializable** objects = VfC8();
        IKFile_ReadObjectRefArray(file, objects, VfC4());
    }
    if (VfBC() != 0) {
        IKSerializable** objects = VfC0();
        IKFile_ReadObjectRefArray(file, objects, VfBC());
    }

    ReadU32LE(file, &count);
    if (count != 0) {
        LoadReserve(m_aVideoTriggers, count);
        for (uint32_t i = 0; i < m_aVideoTriggers.m_ui32NbUsedElt; ++i) {
            IKFile_ReadRef(file, &m_aVideoTriggers.m_pBlock[i].m_pSender);
            IKFile_ReadRef(file, &m_aVideoTriggers.m_pBlock[i].m_pVideo);
            ReadU32LE(file, &m_aVideoTriggers.m_pBlock[i].m_unk08);
        }
    }

    if (VfD0() != 0) {
        IKSerializable** objects = VfD4();
        IKFile_ReadObjectRefArray(file, objects, VfD0());
    }

    ReadU32LE(file, &m_ui32Flags);
    ReadU32LE(file, &count);
    // The buttons always get a block for 3 references first, then grow in steps of 3.
    m_apButtons.m_ui32NbElt = 3;
    m_apButtons.m_pBlock = static_cast<IKSerializable**>(
        Mem_AllocAligned16(3 * static_cast<uint32_t>(sizeof(IKSerializable*))));
    if (m_apButtons.m_ui32NbElt < count) {
        uint32_t capacity = (count / 3) * 3 + 3;
        if (capacity == 0) capacity = 3;
        m_apButtons.m_pBlock = static_cast<IKSerializable**>(
            Mem_ReallocAligned16(m_apButtons.m_pBlock, capacity * static_cast<uint32_t>(sizeof(IKSerializable*))));
        m_apButtons.m_ui32NbElt = capacity;
    }
    m_apButtons.m_ui32NbUsedElt = count;
    for (uint32_t i = count; i-- != 0;) IKFile_ReadRef(file, &m_apButtons.m_pBlock[i]);
    return 1;
}

// 0x00514f18 KBase730C_PostLoad: the menu's interface hidden, then vt+0x94.
// STUB(C1.6): vt+0x94 is 0x9c72b0 KStub_Nop_9c72b0 at this level; the leaves' slot is not declared yet.
int32_t CKMenuBase114c::PostLoad(int32_t type) {
    if (type != K_LEVEL_PLATEFORMS) return 1;
    if (m_pFlashUI != nullptr) static_cast<CKFlashUI*>(m_pFlashUI)->HideInterfaceHierarchy(1);
    return 1;
}

namespace {
CKS08GameManager* GameManagerOf(CKMenuBase114c* menu) { return static_cast<CKS08GameManager*>(menu->m_pGameManager); }
CKInterfaceButtonBase* ButtonAt(CKMenuBase114c* menu, uint32_t i) {
    return static_cast<CKInterfaceButtonBase*>(menu->m_apButtons.m_pBlock[i]);
}
CKFlashUI* FlashUIOf(CKMenuBase114c* menu) { return static_cast<CKFlashUI*>(menu->m_pFlashUI); }
// The interface's sector is loaded and active (bit 0 of CKSector::m_ba16Properties).
bool FlashUIActive(CKFlashUI* ui) {
    return ui != nullptr && ui->m_pSector != nullptr && (ui->m_pSector->m_ba16Properties & 1) != 0;
}
}  // namespace

// 0x00514a00 KBase730C_Open: the input delay (0.5 s), the "Flash Manager" input and the interface
// started, the widgets reset (with vt+0xb4), the buttons opened (focused: a player's selection, vt+0xe4,
// is the button), the selections focused, the transition flag cleared.
void CKMenuBase114c::Open() {
    m_fUnk7c = 0x1p-1f;  // TOC +0x7680
    if (m_pFlashUI != nullptr) {
        g_pEngine->m_input->SetMappingEnabled(1, 1);
        FlashUIOf(this)->StartInterface(1);
    }
    if (VfB4() != 0) ResetWidgets();
    CDefaultGameManager* manager = GameManagerOf(this);
    for (uint32_t i = m_apButtons.m_ui32NbUsedElt; i-- != 0;) {
        CKInterfaceButtonBase* button = ButtonAt(this, i);
        if (button == nullptr) continue;
        uint8_t focused;
        if (manager->IsPlayerActive(1) != 0 && GetSelection(1) == i) {
            focused = 1;
        } else {
            focused = 0;
            if (manager->IsPlayerActive(0) != 0 && GetSelection(0) == i) focused = 1;
        }
        button->Open(focused);  // vt+0x50
    }
    if (m_apButtons.m_ui32NbUsedElt != 0) {
        uint8_t selection = GetSelection(1);
        if (selection != 0xff && manager->IsPlayerActive(1) != 0 && ButtonAt(this, selection) != nullptr)
            SetItemState(selection, 2, 0);
        selection = GetSelection(0);
        if (selection != 0xff && manager->IsPlayerActive(0) != 0 && ButtonAt(this, selection) != nullptr)
            SetItemState(selection, 2, 0);
    }
    m_ui32Flags &= ~8u;
}

// 0x005139a0 KBase730C_vf54: a started interface paused; with stopVideo the interface video stopped and
// its segment kept for Resume.
void CKMenuBase114c::Pause(int32_t stopVideo) {
    CKFlashUI* ui = FlashUIOf(this);
    if (ui == nullptr || (ui->m_baFlags & CKFlashUI::kStateMask) != 2) return;
    ui->PauseInterface();
    m_pPausedSegment = nullptr;
    if (stopVideo != 0) {
        CKS08GameManager* manager = GameManagerOf(this);
        m_pPausedSegment = manager->GetInterfaceVideo()->m_pSegment;
        manager->GetInterfaceVideo()->Stop();
    }
}

// 0x00513700 KBase730C_Open_maybe: a paused interface resumed; the paused segment replayed when the
// interface video is not playing.
void CKMenuBase114c::Resume() {
    CKFlashUI* ui = FlashUIOf(this);
    if (ui == nullptr || (ui->m_baFlags & CKFlashUI::kStateMask) != 1) return;
    ui->ResumeInterface();
    IKVideo* video = GameManagerOf(this)->GetInterfaceVideo();
    if (video != nullptr && (video->m_baData & 1) == 0 && m_pPausedSegment != nullptr)
        m_pPausedSegment->Play(3, 0, 0);
}

// 0x00513f88 KBase730C_Close: the interface stopped, the buttons closed, then the game manager's two
// full-screen billboards (+0x2ac, +0x2a8) hidden.
void CKMenuBase114c::Close() {
    CKFlashUI* ui = FlashUIOf(this);
    if (ui == nullptr) return;
    ui->StopInterface(1);
    for (uint32_t i = m_apButtons.m_ui32NbUsedElt; i-- != 0;) {
        CKInterfaceButtonBase* button = ButtonAt(this, i);
        if (button != nullptr) button->Close();  // vt+0x54
    }
    CKS08GameManager* manager = GameManagerOf(this);
    static_cast<IKNode2d*>(manager->m_unk2A8[1])->Disable();  // vt+0x68
    static_cast<IKNode2d*>(manager->m_unk2A8[0])->Disable();
}

// 0x00514f98 KBase730C_SetVisible_maybe: a started interface hidden (visible 0: kNeverRender set and its
// hot spots hidden) or shown again; returns 1 when that changed it.
uint8_t CKMenuBase114c::SetVisible(uint8_t visible) {
    CKFlashUI* ui = FlashUIOf(this);
    if (ui == nullptr || (ui->m_baFlags & CKFlashUI::kStateMask) != 2) return 0;
    const bool hidden = (ui->m_baFlags & CKFlashUI::kNeverRender) != 0;
    if (visible == 0) {
        if (!hidden) {
            ui->m_baFlags |= CKFlashUI::kNeverRender;
            ui->HideAllHotSpotHierarchy();
            return 1;
        }
    } else if (hidden) {
        ui->m_baFlags &= ~CKFlashUI::kNeverRender;
        return 1;
    }
    return 0;
}

// 0x00515050 KBase730C_vf9C: with the interface's sector active, the widgets reset and, for an open menu
// (flag bit 0), the enter phase run again.
void CKMenuBase114c::Reset() {
    if (!FlashUIActive(FlashUIOf(this))) return;
    ResetWidgets();
    if ((m_ui32Flags & 1) != 0) HandleStatePhase(1, 0);
}

// 0x005151b0 KBase730C_ResetWidgets_maybe: the run state cleared (the menu's own fields, in the original's
// store order); the node animations' time cleared and ramps set to 1.0, their nodes hidden (scene bit 2);
// the element animations' flags and time cleared and ramps set to 1.0; the delayed shows' particle
// elements stopped (scene bits 10 and 19 cleared, the emitter's EMIT flag cleared) with the end time
// FLT_MAX (0x00c4ace0); the widget slots' elements reset; the reference groups' particle objects stopped
// the same way, their dynamic references and states cleared. (No front-end menu has node, element or
// delayed-show entries nor reference groups, LVL000 and live RPCS3; the HUD screens have.)
void CKMenuBase114c::ResetWidgets() {
    m_aUnk78[0] = 0xff;
    m_unk80[2] = 0;
    m_unk6c[1] = 0;
    m_aUnk78[1] = 0xff;
    m_unk6c[0] = 0;
    m_unk80[3] = 1;
    m_unk80[0] = 1;
    m_ui32Flags = (m_ui32Flags & ~0x1fu) | (m_ui32Flags & 1) | 2;
    m_unk90 = 0;
    m_fTime = 0.0f;
    const float one = 0x1p+0f;  // TOC 0x7684
    for (uint32_t i = m_aNodeAnims.m_ui32NbUsedElt; i-- != 0;) {
        NodeAnim& anim = m_aNodeAnims.m_pBlock[i];
        anim.m_fTime = 0.0f;
        anim.m_fUnk3c = one;
        anim.m_fUnk34 = one;
        anim.m_fUnk4c = one;
        anim.m_fUnk44 = one;
        if (anim.m_pNode != nullptr) {
            CSGLeaf* node = static_cast<CSGLeaf*>(static_cast<CNode*>(anim.m_pNode));
            node->m_sgProperties = (node->m_sgProperties & ~4u) | 4u;
        }
    }
    for (uint32_t i = m_aElementAnims.m_ui32NbUsedElt; i-- != 0;) {
        ElementAnim& anim = m_aElementAnims.m_pBlock[i];
        std::memcpy(&anim.m_unk28, &one, 4);  // stfs 1.0
        anim.m_unk08 = 0;
        anim.m_unk09 = 0;
        anim.m_unk0a = 0;
        anim.m_fTime = 0.0f;
        anim.m_fUnk34 = one;
        anim.m_fUnk2c = one;
        anim.m_fUnk44 = one;
        anim.m_fUnk3c = one;
    }
    const float endTime = 0x1.fffffep+127f;  // 0x00c4ace0 (FLT_MAX)
    for (uint32_t i = m_aDelayedShows.m_ui32NbUsedElt; i-- != 0;) {
        DelayedShow& show = m_aDelayedShows.m_pBlock[i];
        CParticlesNodeFx* particles = static_cast<CParticlesNodeFx*>(show.m_pElement);
        particles->m_sgProperties &= 0xfff7fbffu;
        particles->m_pRpPrtStdEmitter->flag &= ~rpPRTSTDEMITTERFLAGEMIT;
        show.m_fEndTime = endTime;
    }
    // The widget slots' elements, from the last: a CParticlesNodeFx (0x4cb) stopped (scene-graph bits 2 set,
    // 10 and 19 cleared; its emitter's EMIT flag cleared), a CNode (0xcb) bit 2 set, a 2D node (0x24d)
    // disabled.
    for (uint32_t i = GetWidgetSlotCount(); i-- != 0;) {
        IKSerializable* element = GetWidgetSlots()[i].m_pElement;
        if (element == nullptr) continue;
        if (element->IsKindOfClass(0x4cb) != 0) {
            CParticlesNodeFx* particles = static_cast<CParticlesNodeFx*>(GetWidgetSlots()[i].m_pElement);
            if (particles != nullptr) {
                const uint32_t bits = particles->m_sgProperties;
                particles->m_sgProperties = (bits & 0xfff7fbf8u) | (bits & 3u) | 4u;
                particles->m_pRpPrtStdEmitter->flag &= ~rpPRTSTDEMITTERFLAGEMIT;
            }
        }
        if (element->IsKindOfClass(0xcb) != 0) {
            CSGLeaf* node = static_cast<CSGLeaf*>(static_cast<CNode*>(element));
            node->m_sgProperties = (node->m_sgProperties & ~4u) | 4u;
        }
        if (element->IsKindOfClass(0x24d) != 0) static_cast<IKNode2d*>(element)->Disable();  // vt+0x68
    }
    // The reference groups, from the last (vt+0x84 count, vt+0x88 groups, vt+0x8c references, vt+0x90
    // states): the group's particle object stopped, the references [m_unk04, m_unk08) and the first
    // m_unk08 states cleared.
    for (uint32_t i = Vf84(); i-- != 0;) {
        if (Vf88()[i].m_pObject != nullptr) {
            CParticlesNodeFx* particles = static_cast<CParticlesNodeFx*>(Vf88()[i].m_pObject);
            particles->m_sgProperties &= 0xfff7fbffu;
            particles->m_pRpPrtStdEmitter->flag &= ~rpPRTSTDEMITTERFLAGEMIT;
        }
        RefGroup& group = Vf88()[i];
        GroupState* states = Vf90(i);
        const int32_t dynamic = static_cast<int32_t>(group.m_unk08 - group.m_unk04);
        if (dynamic > 0) {
            IKSerializable** references = Vf8C(i) + group.m_unk04;
            for (int32_t j = 0; j < dynamic; ++j) references[j] = nullptr;  // memset (4-byte references)
        }
        if (states != nullptr) std::memset(states, 0, group.m_unk08 * sizeof(GroupState));
    }
    m_pPausedSegment = nullptr;
}

// 0x00519130 KBase730C_UpdateElementAnimations_maybe: the menu clock (+0x40) advanced by the frame's
// fixed delta while the clock runs, then, for a started interface, the node and element animations, the
// delayed shows and the reference groups. STUB(C1.6): those four loops (none of the boot-sequence menus
// has node, element or delayed-show entries, nor reference groups, in LVL000).
void CKMenuBase114c::UpdateElementAnimations() {
    IKTime* frameClock = g_pEngine->m_timeManager->m_pTime;
    if (frameClock->m_eCurrentState == IKTime::RUNNING)
        m_fTime = frameClock->m_afDeltaTime[IKTime::FIXED_GAME_TIME] + m_fTime;  // fadds
    CKFlashUI* ui = FlashUIOf(this);
    if (ui == nullptr || (ui->m_baFlags & CKFlashUI::kStateMask) != 2) return;
    if (m_aNodeAnims.m_ui32NbUsedElt != 0 || m_aElementAnims.m_ui32NbUsedElt != 0 ||
        m_aDelayedShows.m_ui32NbUsedElt != 0 || Vf84() != 0)
        DOTD_STUB_ONCE("KBase730C_UpdateElementAnimations_maybe: animation loops (C1.6)");
}

// 0x00518428 KBase730C_UpdateInput: the per-player results cleared; once the open delay (+0x7c) ran out,
// every button ready and input allowed (+0x61), each player's navigation; otherwise the delay counts
// down. Then every button updated.
void CKMenuBase114c::UpdateInput(IKTime* frameClock) {
    for (uint32_t i = m_unk80[0]; i != 0; --i) m_aUnk78[i - 1] = 0xff;
    bool countDown = true;
    if ((m_ui32Flags & 8) == 0 && (m_ui32Flags & 0x10) == 0 && m_fUnk7c <= 0.0f) {
        countDown = false;
        // Every button's fade-out finished (vt+0x78), and at least one button.
        const uint32_t count = m_apButtons.m_ui32NbUsedElt;
        bool ready = count != 0;
        for (uint32_t i = count; i-- != 0;) {
            CKInterfaceButtonBase* button = ButtonAt(this, i);
            if (button != nullptr) ready = ready && button->IsFadeOutFinished() != 0;
        }
        if (ready && m_unk60[1] != 0 && m_unk80[0] != 0) {
            for (uint32_t player = 0; player < m_unk80[0]; ++player) {
                // BUG(original): every pass reads player 0 (r4 = 0 for each call); the game manager's
                // player count (vt+0x154) is read and not used.
                g_pEngine->m_gameManager->GetPlayerCount();
                m_unk80[1] = 1;
                const uint8_t dir = ReadNavDirection(0, frameClock);
                m_aUnk78[0] = dir;
                if (m_unk64 <= 0.0f && HandleShortcutButtons(0, frameClock) != 0) continue;
                if (HandleValidateButton(0, dir, frameClock) != 0) continue;
                UpdateFocus(0, dir);
            }
        }
    }
    if (countDown) m_fUnk7c = m_fUnk7c - frameClock->m_afDeltaTime[IKTime::FIXED_GAME_TIME];  // fsubs
    // Every button updated (vt+0x58), then the menu's vt+0xe8 with its state (phase 0).
    for (uint32_t i = m_apButtons.m_ui32NbUsedElt; i-- != 0;) {
        CKInterfaceButtonBase* button = ButtonAt(this, i);
        if (button == nullptr) continue;
        button->Update(frameClock);
        OnItemState(static_cast<uint8_t>(i), ButtonAt(this, i)->m_ui8State, 0);
    }
}

// 0x00518760 KBase730C_HandleStatePhase
uint8_t CKMenuBase114c::HandleStatePhase(int32_t phase, uint8_t other) {
    if (!FlashUIActive(FlashUIOf(this))) return static_cast<uint8_t>(GetMenuId());
    if (phase == 1) {
        if (VfB4() == 0) Open();
        if (VfC4() != 0) std::memset(VfCC(), 0, VfC4());
        m_i32WaitVideoFrame = -1;
        m_unk44[0] = 0xff;
        m_unk60[1] = 0;
        m_ui32Flags &= ~4u;
        m_unk68 = 0;
        m_unk6c[1] = GetSelection(1);
        m_fUnk74 = 0x1.99999ap-3f;  // 0.2f (0x3e4ccccd)
        m_unk64 = 0;
        m_unk6c[0] = GetSelection(0);
        m_fUnk70 = 0x1.99999ap-3f;
        m_fUnk5c = 0.0f;
        m_unk60[0] = 0;
        OnMenuState(1, other);
        UpdateElementAnimations();
    } else if (phase == 2) {
        Close();
        OnMenuState(2, other);
        UpdateElementAnimations();
        return static_cast<uint8_t>(GetMenuId());
    } else if (phase == 0) {
        UpdateInput(g_pEngine->m_timeManager->m_pTime);
        if (VfCC()[4] != 0) {
            // The last raised message-in other than entry 4 becomes the pending one (+0x44).
            uint8_t i = VfC4();
            for (;;) {
                i = static_cast<uint8_t>(i - 1);
                if (i == 0xff) break;
                if (i == 4 || VfCC()[i] == 0) continue;
                m_unk44[0] = i;
                VfCC()[i] = 0;
                break;
            }
        }
        if (VfCC()[1] != 0) m_unk60[1] = 1;  // input allowed (the movie's opening animation ended)
        if (VfCC()[3] != 0) {
            if ((m_ui32Flags & 8) != 0) {
                CKS08GameManager* manager = GameManagerOf(this);
                manager->m_ui32MenuStackDepth = 1;
                manager->m_aMenuStack[0] = m_unk90;
            }
            if (m_unk44[0] != 0xff) {
                VfCC()[static_cast<int8_t>(m_unk44[0])] = 1;
                m_unk44[0] = 0xff;
            }
        }
        if (VfCC()[5] != 0) Close();
        IKVideo* video = GameManagerOf(this)->GetInterfaceVideo();
        const int32_t waitFrame = m_i32WaitVideoFrame;
        if (waitFrame >= 0) {
            if (video->GetPlaybackPosition() < waitFrame) {
                if ((video->m_baData & 2) != 0) video->Resume();
            } else {
                m_i32WaitVideoFrame = -1;
                FlashUIOf(this)->ResumeInterface();
            }
        }
        OnMenuState(0, other);
        UpdateElementAnimations();
        if (VfC4() != 0) std::memset(VfCC(), 0, VfC4());
        return static_cast<uint8_t>(GetMenuId());
    } else {
        OnMenuState(phase, other);
        UpdateElementAnimations();
        return static_cast<uint8_t>(GetMenuId());
    }
    // Phase 1 ends with the player count: 1 with +0x83, else the game manager's (vt+0x154), at most 2.
    if (m_unk80[3] == 0) {
        const uint8_t players = g_pEngine->m_gameManager->GetPlayerCount();
        m_unk80[0] = players;
        if (players > 2) m_unk80[0] = 2;
    } else {
        m_unk80[0] = 1;
    }
    return static_cast<uint8_t>(GetMenuId());
}

// 0x005144f0 KBase730C_PlayScreenVideo_maybe
void CKMenuBase114c::PlayScreenVideo(int32_t mode, uint8_t arg) {
    CKS08GameManager* manager = GameManagerOf(this);
    IKVideo* video = manager->GetInterfaceVideo();
    CKVideoSegment* segment = manager->GetInterfaceSegment();  // vt+0x30c
    if (segment == nullptr) {
        if (video == nullptr) return;
        segment = video->m_pSegment;
        if (segment == nullptr) return;
        manager->SetInterfaceSegment(segment);  // vt+0x308
    }
    segment->Play(mode, arg, 1);
    Resume();
    SetVisible(1);
}

// 0x00515b78 KBase730C_MessageProc: for message 0x2300 from a CKFlashMessageIn: the delayed shows it
// starts or stops, the message-in flag it raises (vt+0xc8 / +0xcc), and the video trigger it plays.
// Returns 0 for message 0x2300 (handled), 1 for any other.
int32_t CKMenuBase114c::MessageProc(uint16_t message, void* data) {
    if ((message >> 8) != 0x23 || (message & 0xff) != 0) return 1;
    IKSerializable* sender = static_cast<IKSerializable*>(data);
    if (m_aDelayedShows.m_ui32NbUsedElt != 0) DOTD_STUB_ONCE("KBase730C_MessageProc: delayed shows (C1.6)");
    for (uint32_t i = VfC4(); i != 0; --i) {
        if (VfC8()[i - 1] == sender) {
            VfCC()[i - 1] = 1;
            break;
        }
    }
    GameManagerOf(this)->GetInterfaceVideo();  // vt+0xdc, the result unused
    for (uint32_t i = m_aVideoTriggers.m_ui32NbUsedElt; i != 0; --i) {
        VideoTrigger* trigger = &m_aVideoTriggers.m_pBlock[i - 1];
        if (trigger->m_pSender != sender) continue;
        CKVideoSegment* segment = static_cast<CKVideoSegment*>(trigger->m_pVideo);
        segment->Play(3, 0, 0);
        GameManagerOf(this)->SetInterfaceSegment(segment);
        if (segment->m_ended != 0 || trigger->m_unk08 == 0) return 0;
        m_i32WaitVideoFrame = static_cast<int32_t>(trigger->m_unk08);
        FlashUIOf(this)->PauseInterface();
        return 0;
    }
    return 0;
}

// ---- C1.6: the menu navigation ----

namespace {

const float kHalf = 0x1p-1f;        // TOC +0x7680
const float kMinusHalf = -0x1p-1f;  // TOC +0x7694
const float kNavRepeat = 0x1.99999ap-3f;  // TOC +0x7670 0.2f (0x3e4ccccd)
const float kPointerSlack = 0x1.99999ap-5f;  // TOC +0x769c 0.05f (0x3d4ccccd)
// 0x00c50dc4 (TOC +0x7698): a CVector2 (0, 0) in the data segment (read live: 0.0, 0.0).
const CVector2 kZeroVector2 = {0.0f, 0.0f};

// The "Flash Manager" input project's second configuration (CKInput::m_aaInputDico[project][1]), or null
// (the original then reads through address 0x10).
CKInputDico* FlashManagerDico() {
    CKInput* input = g_pEngine->m_input;
    const uint32_t project = static_cast<uint32_t>(input->FindMappingIndexByName("Flash Manager")) & 0xff;
    if (project == 0xff) return nullptr;
    return &input->m_aaInputDico[project][1];
}

// 0x0010e408 InputMapping_GetAnalogValue (the input family's file has it unticked; a local copy): the time
// entry `index`'s action has been held (CKAction +0x18).
float DicoHeldTime(const CKInputDico* dico, int32_t index) {
    return dico->m_pInput->m_aActions[dico->m_aNumAction[index]].m_fActionTimePressed;
}

// The game manager's vt+0x31c (CKS08GameManager::GetPointerPosition 0x4f6b48): the pointer position of
// `player`, always (-1, -1) on the PS3, also stored in the manager's +0x298.
CVector2 GameManagerPointer(CKS08GameManager* manager, int32_t player) { return manager->GetPointerPosition(player); }

// The pointer of `player` (0 or 1) refreshed as FindItemUnderCursor and MoveFocusByInput do: when the
// manager's pointer flag (vt+0x310) is clear or the game loop's +0x5c set, the flag set (vt+0x314) and the
// position read (vt+0x31c); then the pointer billboard (+0x2a8) placed there (vt+0x74) and enabled (+0x64).
void RefreshPointer(CKS08GameManager* manager, uint8_t player) {
    if (manager->Vf310(player) == 0 || g_pEngine->m_gameLoop->m_unk5c != 0) {
        manager->Vf314(player, 1);
        const CVector2 position = GameManagerPointer(manager, player);
        manager->m_afUnk298[player * 2] = position.m_fX;
        manager->m_afUnk298[player * 2 + 1] = position.m_fY;
    }
    IKNode2d* billboard = static_cast<IKNode2d*>(manager->m_unk2A8[player]);
    billboard->SetPos(CVector2{manager->m_afUnk298[player * 2], manager->m_afUnk298[player * 2 + 1]});
    billboard->Enable();
}

const CVector2& NodePosition(IKSerializable* node) { return static_cast<IKNode2d*>(node)->m_vPosition; }

// The size of a CKInterfaceButton / CKInterfaceCheckBox visual state (+0x14/+0x18 of the state record, read
// as floats by FindItemUnderCursor).
float ButtonStateSize(const CKInterfaceButton::StateVisual& state, int axis) { return state.m_afSize[axis]; }
// The check box's state record holds a size per billboard; the test uses billboard 1's (+0x40).
float CheckBoxStateSize(const CKInterfaceCheckBox::StateVisual& state, int axis) {
    return axis == 0 ? state.m_avSizes[1].m_fX : state.m_avSizes[1].m_fY;
}

// FindItemUnderCursor's test of a CKInterfaceButton (fmuls/fadds): the state's size around the first of the
// elements +0x3c, +0x38 (else +0x34). The original tests "not outside" (unordered compares count as inside).
bool ButtonUnderPointer(CKInterfaceButton* button, float px, float py) {
    const CKInterfaceButton::StateVisual& state = button->m_aStates[button->m_ui8State];
    const float w = ButtonStateSize(state, 0), h = ButtonStateSize(state, 1);
    float minY = h * kMinusHalf, minX = w * kMinusHalf, maxX, maxY;
    IKSerializable* element = button->m_apUnk38[1] != nullptr ? button->m_apUnk38[1] : button->m_apUnk38[0];
    if (element != nullptr) {
        maxX = w * kHalf;
        maxY = h * kHalf;
        minY = minY + NodePosition(element).m_fY;
        minX = minX + NodePosition(element).m_fX;
        maxY = maxY + NodePosition(element).m_fY;
        maxX = maxX + NodePosition(element).m_fX;
    } else {
        if (button->m_unk34 != nullptr) {
            minY = minY + NodePosition(button->m_unk34).m_fY;
            minX = minX + NodePosition(button->m_unk34).m_fX;
        }
        maxX = w * kHalf;
        maxY = h * kHalf;
        if (button->m_unk34 != nullptr) {
            maxY = maxY + NodePosition(button->m_unk34).m_fY;
            maxX = maxX + NodePosition(button->m_unk34).m_fX;
        }
    }
    return !(px < minX || py < minY || maxX < px || maxY < py);
}

// The same for a CKInterfaceCheckBox: around the first of +0x40, +0x3c, else of +0x34, +0x38 (fmuls/fadds).
bool CheckBoxUnderPointer(CKInterfaceCheckBox* box, float px, float py) {
    const CKInterfaceCheckBox::StateVisual& state = box->m_aStates[box->m_ui8State];
    const float w = CheckBoxStateSize(state, 0), h = CheckBoxStateSize(state, 1);
    float minY = h * kMinusHalf, minX = w * kMinusHalf, maxX, maxY;
    IKSerializable* element = box->m_apUnk3c[1] != nullptr ? box->m_apUnk3c[1] : box->m_apUnk3c[0];
    if (element != nullptr) {
        maxX = w * kHalf;
        maxY = h * kHalf;
        minY = minY + NodePosition(element).m_fY;
        minX = minX + NodePosition(element).m_fX;
        maxY = maxY + NodePosition(element).m_fY;
        maxX = maxX + NodePosition(element).m_fX;
    } else {
        IKSerializable* other = box->m_unk34 != nullptr ? box->m_unk34 : box->m_unk38;
        if (other != nullptr) {
            minY = minY + NodePosition(other).m_fY;
            minX = minX + NodePosition(other).m_fX;
        }
        maxX = w * kHalf;
        maxY = h * kHalf;
        if (other != nullptr) {
            maxY = maxY + NodePosition(other).m_fY;
            maxX = maxX + NodePosition(other).m_fX;
        }
    }
    return minX <= px && minY <= py && px <= maxX && py <= maxY;
}

// The same for a CKInterfaceButtonDouble (fmadds): the union of the left arrow (RecordB's first size around
// +0x50), the value (RecordA's size around +0x58) and the right arrow (RecordB's second size around +0x54).
// RecordA is the state's for states below 4, else the third.
bool DoubleUnderPointer(CKInterfaceButtonDouble* item, float px, float py) {
    const uint8_t s = item->m_ui8State;
    const CKInterfaceButtonDouble::RecordA& value = item->m_aRecordsA[s < 4 ? s : 2];
    const CKInterfaceButtonDouble::RecordB& arrows = item->m_aRecordsB[s];
    const CVector2& left = NodePosition(item->m_apUnk50[0]);
    const CVector2& right = NodePosition(item->m_apUnk50[1]);
    const CVector2& middle = NodePosition(item->m_apUnk58[0]);
    float minXLeft = ppc::fmadds(arrows.m_vUnk04[0], kMinusHalf, left.m_fX);
    float minX = ppc::fmadds(value.m_vUnk1c[0], kMinusHalf, middle.m_fX);
    float minY = ppc::fmadds(value.m_vUnk1c[1], kMinusHalf, middle.m_fY);
    float minYLeft = ppc::fmadds(arrows.m_vUnk04[1], kMinusHalf, left.m_fY);
    if (minXLeft < minX) minX = minXLeft;
    if (minYLeft < minY) minY = minYLeft;
    float maxXRight = ppc::fmadds(arrows.m_vUnk04[2], kHalf, right.m_fX);
    float maxX = ppc::fmadds(value.m_vUnk1c[0], kHalf, middle.m_fX);
    float maxY = ppc::fmadds(value.m_vUnk1c[1], kHalf, middle.m_fY);
    float maxYRight = ppc::fmadds(arrows.m_vUnk04[3], kHalf, right.m_fY);
    if (maxX < maxXRight) maxX = maxXRight;
    if (maxY < maxYRight) maxY = maxYRight;
    return minX <= px && minY <= py && px <= maxX && py <= maxY;
}

}  // namespace

// 0x00512040 KBase730C_SetItemState
void CKMenuBase114c::SetItemState(uint8_t item, uint32_t state, uint8_t delayed) {
    if (item == 0xff || ButtonAt(this, item) == nullptr) return;
    if (delayed != 0 && state == 1 && !(m_fUnk5c <= 0.0f)) return;
    OnItemState(item, ButtonAt(this, item)->m_ui8State, 2);  // vt+0xe8
    ButtonAt(this, item)->SetInteractionState(static_cast<uint8_t>(state));  // vt+0x5c
    if (delayed != 0 && state == 1) {
        m_unk60[0] = item;
        m_fUnk5c = ButtonAt(this, item)->m_fDelay;
    }
    OnItemState(item, ButtonAt(this, item)->m_ui8State, 1);
}

// 0x00512938 KBase730C_ReadNavDirection: the four directions summed over the active players; the first
// held one in the order down-up... (actions 2/8 first) once the player's repeat timer (+0x70) reached 0.2 s.
uint8_t CKMenuBase114c::ReadNavDirection(uint8_t player, IKTime* frameClock) {
    CKInputDico* dico = FlashManagerDico();
    CDefaultGameManager* manager = GameManagerOf(this);
    uint32_t a = 0, b = 0, c = 0, d = 0;  // actions 0/6, 1/7, 2/8, 3/9
    if (manager->IsPlayerActive(0) != 0) {
        a = dico->GetButtonState(0);
        a += dico->GetButtonState(6);
        b = dico->GetButtonState(1);
        b += dico->GetButtonState(7);
        c = dico->GetButtonState(2);
        c += dico->GetButtonState(8);
        d = dico->GetButtonState(3);
        d += dico->GetButtonState(9);
    }
    if (manager->IsPlayerActive(1) != 0) {
        a += dico->GetButtonState(0x14);
        a += dico->GetButtonState(0x1a);
        b += dico->GetButtonState(0x15);
        b += dico->GetButtonState(0x1b);
        c += dico->GetButtonState(0x16);
        c += dico->GetButtonState(0x1c);
        d += dico->GetButtonState(0x17);
        d += dico->GetButtonState(0x1d);
    }
    // The per-player timer at +0x70 + 4 * player (the original masks the index to a byte).
    float& timer = player == 0 ? m_fUnk70 : m_fUnk74;
    uint8_t dir = 0xff;
    if (c != 0 || d != 0 || a != 0 || b != 0) {
        const uint8_t wanted = c != 0 ? 0 : d != 0 ? 1 : a != 0 ? 2 : 3;
        if (timer >= kNavRepeat) {
            dir = wanted;
            timer = 0.0f;
        }
    } else {
        timer = kNavRepeat;
    }
    timer = timer + frameClock->m_afDeltaTime[IKTime::FIXED_GAME_TIME];  // fadds
    return dir;
}

// 0x00512d68 KBase730C_HandleShortcutButtons
uint8_t CKMenuBase114c::HandleShortcutButtons(uint8_t /*player*/, IKTime* frameClock) {
    float timer = m_fUnk5c;
    if (timer <= 0.0f) {
        CKInputDico* dico = FlashManagerDico();
        CDefaultGameManager* manager = GameManagerOf(this);
        uint8_t used = 0;
        bool found = false;
        for (uint32_t i = m_apButtons.m_ui32NbUsedElt; i-- != 0;) {
            // BUG(original)?: the focus tested is player 0's (+0x6c), whatever the player.
            const uint8_t focus = m_unk6c[0];
            if (focus != 0xff && ButtonAt(this, focus) == nullptr) continue;
            IKSerializable* object = m_apButtons.m_pBlock[i];
            if (object == nullptr || object->IsKindOfClass(0x630c) == 0) continue;
            const uint8_t action = static_cast<CKInterfaceButton*>(object)->m_unk3b4;
            if (action == 0xff) continue;
            uint8_t pressed = 0;
            if (manager->IsPlayerActive(0) != 0) pressed = dico->GetButtonState(action) != 0 ? 1 : 0;
            if (manager->IsPlayerActive(1) != 0)
                pressed = static_cast<uint8_t>(pressed | (dico->GetButtonState(static_cast<uint8_t>(action + 0x14)) != 0 ? 1 : 0));
            if (pressed == 0) continue;
            CKInterfaceButtonBase* button = ButtonAt(this, i);
            if (button == nullptr || (button->m_baFlags & CKInterfaceButtonBase::kFlagDisabled) != 0) continue;
            SetItemState(static_cast<uint8_t>(i), 1, 1);
            used = 1;
            found = true;
            break;
        }
        if (!found && VfF0() != 0) used = TryBackButton(VfF4());  // vt+0xf8(vt+0xf4())
        timer = m_fUnk5c;
        if (used == 0 && timer <= 0.0f) return 0;
    } else if (timer <= 0.0f) {
        return 0;
    }
    timer = timer - frameClock->m_afDeltaTime[IKTime::FIXED_GAME_TIME];  // fsubs
    m_fUnk5c = timer;
    if (timer <= 0.0f) {
        const uint8_t item = m_unk60[0];
        if (ButtonAt(this, item) != nullptr) SetItemState(item, m_unk6c[0] != item ? 0 : 2, 0);
    }
    return 1;
}

// 0x00513188 KBase730C_HandleValidateButton
uint8_t CKMenuBase114c::HandleValidateButton(uint8_t player, uint8_t dir, IKTime* frameClock) {
    CKInputDico* dico = FlashManagerDico();
    CDefaultGameManager* manager = GameManagerOf(this);
    float held = 0.0f;
    uint8_t pressed = 0;
    if (manager->IsPlayerActive(0) != 0) {
        dico->GetButtonState(4);  // read twice; the first result unused
        pressed = dico->GetButtonState(4);
        const float time = DicoHeldTime(dico, 4);
        held = 0.0f;
        if (held <= time) held = DicoHeldTime(dico, 4);
    }
    if (manager->IsPlayerActive(1) != 0) {
        if (pressed <= dico->GetButtonState(0x18)) pressed = dico->GetButtonState(0x18);
        if (held <= DicoHeldTime(dico, 0x18)) held = DicoHeldTime(dico, 0x18);
    }
    uint8_t& focus = m_unk6c[player];
    // left/right on a two-part item (CKInterfaceButtonDouble) count as validating it
    bool arrow = false;
    if (focus != 0xff) {
        IKSerializable* object = m_apButtons.m_pBlock[focus];
        arrow = object != nullptr && object->IsKindOfClass(0x634c) != 0 && static_cast<uint8_t>(dir - 2) <= 1;
    }
    float& timer = player == 0 ? m_unk64 : m_unk68;  // +0x64 + 4 * player
    if (timer <= 0.0f) {
        if (pressed != 0 || arrow) {
            if ((m_ui32Flags & 4) == 0) {
                const uint8_t item = focus;
                if (item != 0xff && ButtonAt(this, item) != nullptr &&
                    (ButtonAt(this, item)->m_baFlags & CKInterfaceButtonBase::kFlagDisabled) == 0) {
                    if (arrow && dir == 2)
                        SetItemState(item, 3, 0);
                    else if (arrow && dir == 3)
                        SetItemState(item, 4, 0);
                    else
                        SetItemState(item, 1, 0);
                    CKInterfaceButtonBase* button = ButtonAt(this, focus);
                    if ((button->m_baFlags & CKInterfaceButtonBase::kFlagHold) == 0) {
                        timer = button->m_fDelay;
                        m_ui32Flags = (m_ui32Flags & ~4u) | 4u;
                        goto countDown;
                    }
                    timer = 0.0f;
                }
                m_ui32Flags = (m_ui32Flags & ~4u) | 4u;
            }
        } else if ((m_ui32Flags & 4) != 0 && focus != 0xff && ButtonAt(this, focus) != nullptr) {
            CKInterfaceButtonBase* button = ButtonAt(this, focus);
            if ((button->m_baFlags & CKInterfaceButtonBase::kFlagHold) == 0) {
                m_ui32Flags &= ~4u;
            } else if (held == 0.0f) {
                timer = button->m_fDelay;
                m_ui32Flags &= ~4u;
                goto countDown;
            }
        }
    }
    if (timer <= 0.0f) return 0;
countDown:
    timer = timer - frameClock->m_afDeltaTime[IKTime::FIXED_GAME_TIME];  // fsubs
    if (timer <= 0.0f && ButtonAt(this, focus) != nullptr) SetItemState(focus, 2, 0);
    return 1;
}

// 0x00514720 KBase730C_TryBackButton
uint8_t CKMenuBase114c::TryBackButton(uint8_t item) {
    CKInputDico* dico = FlashManagerDico();
    CDefaultGameManager* manager = GameManagerOf(this);
    for (uint8_t player = 0; player < manager->GetPlayerCount(); ++player) {
        if (manager->IsPlayerActive(player) == 0) continue;
        if (dico->GetButtonState(static_cast<uint8_t>(player * 0x14 + 5)) != 0xff) continue;
        SetItemState(item, 1, 1);
        return 1;
    }
    return 0;
}

// 0x005148c0 KBase730C_StartTransitionToMenu
void CKMenuBase114c::StartTransitionToMenu(uint8_t menu) {
    m_ui32Flags = (m_ui32Flags & ~8u) | 8u;
    if (VfC0()[0] != nullptr) static_cast<CKFlashMessageOut*>(VfC0()[0])->PostFlashMessage();
    m_unk90 = menu;
    for (uint32_t i = m_apButtons.m_ui32NbUsedElt; i-- != 0;) {
        CKInterfaceButtonBase* button = ButtonAt(this, i);
        if (button != nullptr) button->StartFadeOut();  // vt+0x74
    }
}

// 0x00515f20 KBase730C_FindItemUnderCursor: the buttons from the last; a shortcut button (+0x3b4) and the
// back item (vt+0xf4) are never under the pointer.
uint8_t CKMenuBase114c::FindItemUnderCursor(uint8_t player) {
    CKS08GameManager* manager = GameManagerOf(this);
    const uint8_t p = player != 0 ? 1 : 0;
    RefreshPointer(manager, p);
    const float px = manager->m_afUnk298[p * 2];
    const float py = manager->m_afUnk298[p * 2 + 1];
    for (uint32_t i = m_apButtons.m_ui32NbUsedElt; i-- != 0;) {
        IKSerializable* object = m_apButtons.m_pBlock[i];
        if (object == nullptr || (ButtonAt(this, i)->m_baFlags & CKInterfaceButtonBase::kFlagSkip) != 0) continue;
        if (object->IsKindOfClass(0x630c) != 0) {
            CKInterfaceButton* button = static_cast<CKInterfaceButton*>(object);
            if (button->m_unk3b4 != 0xff || VfF4() == i) continue;
            if (ButtonUnderPointer(button, px, py)) return static_cast<uint8_t>(i);
        } else if (object->IsKindOfClass(0x634c) != 0) {
            if (DoubleUnderPointer(static_cast<CKInterfaceButtonDouble*>(object), px, py)) return static_cast<uint8_t>(i);
        } else if (object->IsKindOfClass(0x638c) != 0) {
            // CKInterfaceScrollingMenu: its two arrows (+0x34, +0x3c, with the state sizes at +0xc0) and its
            // visible entries (+0x194). STUB(C1.6): no front-end menu has a scrolling menu.
            DOTD_STUB_ONCE("KBase730C_FindItemUnderCursor: CKInterfaceScrollingMenu (C1.6)");
        } else if (object->IsKindOfClass(0xa14c) != 0) {
            if (CheckBoxUnderPointer(static_cast<CKInterfaceCheckBox*>(object), px, py)) return static_cast<uint8_t>(i);
        }
    }
    return 0xff;
}

// 0x00516de0 KBase730C_MoveFocusByInput_maybe: the focus of `player` moved to `item` (state 2), the previous
// item back to 0 unless another player's focus is on it; on a two-part item the pointer and left/right
// decide states 3/4 instead. With +0x83 every player gets the focus.
void CKMenuBase114c::MoveFocusByInput(uint8_t player, uint8_t /*dir*/, uint8_t item) {
    if (item == 0xff) return;
    if (ButtonAt(this, item) != nullptr) {
        // Another active player's focus is the same item (only without +0x83).
        uint8_t shared = 0;
        for (uint32_t other = 0; other < m_unk80[0]; ++other) {
            if (other == player) continue;
            if (GameManagerOf(this)->IsPlayerActive(static_cast<int32_t>(other)) == 0) continue;
            if (m_unk6c[other] == m_unk6c[player] && m_unk80[3] == 0) shared = 1;
        }
        uint8_t& focus = m_unk6c[player];
        IKSerializable* object = m_apButtons.m_pBlock[item];
        if (object->IsKindOfClass(0x634c) != 0) {
            if (shared == 0 && focus != item) SetItemState(focus, 0, 0);
            focus = item;
            const uint8_t p = player > 0 ? 1 : player;
            CKS08GameManager* manager = GameManagerOf(this);
            RefreshPointer(manager, p);
            const float px = manager->m_afUnk298[p * 2];
            const float py = manager->m_afUnk298[p * 2 + 1];
            CKInterfaceButtonDouble* button = static_cast<CKInterfaceButtonDouble*>(object);
            const CKInterfaceButtonDouble::RecordB& arrows = button->m_aRecordsB[button->m_ui8State];
            const CVector2& left = NodePosition(button->m_apUnk50[0]);
            float maxXLeft = ppc::fmadds(arrows.m_vUnk04[0], kHalf, left.m_fX);
            float maxYLeft = ppc::fmadds(arrows.m_vUnk04[1], kHalf, left.m_fY);
            float minXLeft = ppc::fmadds(arrows.m_vUnk04[0], kMinusHalf, left.m_fX);
            float minYLeft = ppc::fmadds(arrows.m_vUnk04[1], kMinusHalf, left.m_fY);
            uint8_t state = 2;
            bool testPointer = true;
            if (m_unk80[1] != 0) {
                // Validate held (pressed or held time) by an active player: the pointer test with slack;
                // else left/right decide.
                CKInputDico* dico = FlashManagerDico();
                float held = 0.0f;
                uint8_t pressed = 0;
                if (manager->IsPlayerActive(0) != 0) {
                    dico->GetButtonState(4);
                    pressed = dico->GetButtonState(4);
                    if (!(DicoHeldTime(dico, 4) < held)) held = DicoHeldTime(dico, 4);
                }
                if (manager->IsPlayerActive(1) != 0) {
                    if (pressed <= dico->GetButtonState(0x18)) pressed = dico->GetButtonState(0x18);
                    if (!(held > DicoHeldTime(dico, 0x18))) held = DicoHeldTime(dico, 0x18);
                }
                if (pressed == 0 && held == 0.0f) {
                    testPointer = false;
                    uint8_t leftHeld = 0, rightHeld = 0;
                    if (manager->IsPlayerActive(0) != 0) {
                        dico->GetButtonState(6);
                        leftHeld = dico->GetButtonState(6);
                        dico->GetButtonState(7);
                        rightHeld = dico->GetButtonState(7);
                        if (dico->GetButtonState(0) >= leftHeld) leftHeld = dico->GetButtonState(0);
                        if (dico->GetButtonState(1) >= rightHeld) rightHeld = dico->GetButtonState(1);
                    }
                    if (manager->IsPlayerActive(1) != 0) {
                        if (leftHeld <= dico->GetButtonState(0x1a)) leftHeld = dico->GetButtonState(0x1a);
                        if (rightHeld <= dico->GetButtonState(0x1b)) rightHeld = dico->GetButtonState(0x1b);
                        if (leftHeld <= dico->GetButtonState(0x14)) leftHeld = dico->GetButtonState(0x14);
                        if (rightHeld <= dico->GetButtonState(0x15)) rightHeld = dico->GetButtonState(0x15);
                    }
                    state = leftHeld != 0 ? 3 : rightHeld != 0 ? 4 : 2;
                } else {
                    maxYLeft = maxYLeft + kPointerSlack;
                    minXLeft = minXLeft - kPointerSlack;
                    minYLeft = minYLeft - kPointerSlack;
                    maxXLeft = maxXLeft + kPointerSlack;
                }
            }
            if (testPointer) {
                if (px >= minXLeft && minYLeft <= py && px <= maxXLeft && py <= maxYLeft) {
                    state = 3;
                } else {
                    const CVector2& right = NodePosition(button->m_apUnk50[1]);
                    float maxXRight = ppc::fmadds(arrows.m_vUnk04[2], kHalf, right.m_fX);
                    float maxYRight = ppc::fmadds(arrows.m_vUnk04[3], kHalf, right.m_fY);
                    float minYRight = ppc::fmadds(arrows.m_vUnk04[3], kMinusHalf, right.m_fY);
                    float minXRight = ppc::fmadds(arrows.m_vUnk04[2], kMinusHalf, right.m_fX);
                    if (m_unk80[1] != 0) {
                        maxYRight = maxYRight + kPointerSlack;
                        minXRight = minXRight - kPointerSlack;
                        minYRight = minYRight - kPointerSlack;
                        maxXRight = maxXRight + kPointerSlack;
                    }
                    if (px >= minXRight && minYRight <= py && px <= maxXRight && py <= maxYRight) state = 4;
                }
            }
            SetItemState(item, state, 0);
            if (state == 2) focus = item;
        } else if (object->IsKindOfClass(0x638c) != 0) {
            // CKInterfaceScrollingMenu (its entries under the pointer, 0x5255c0 / 0x5276d0). STUB(C1.6): no
            // front-end menu has a scrolling menu.
            DOTD_STUB_ONCE("KBase730C_MoveFocusByInput_maybe: CKInterfaceScrollingMenu (C1.6)");
            return;
        } else {
            if (focus != item) {
                if (shared == 0) SetItemState(focus, 0, 0);
                focus = item;
                SetItemState(item, 2, 0);
            }
            focus = item;
        }
    }
    if (m_unk80[3] != 0) {
        for (uint32_t p = 0; GameManagerOf(this)->GetPlayerCount() > p; ++p) m_unk6c[p] = item;
    }
}

// 0x00518248 KBase730C_UpdateFocus_maybe: the item under the pointer (+0x82 0 or 5) or the focus itself
// (other modes) when there is one; else, with a direction, the focus's neighbour that way (items with the
// skip bit passed over, at most 255 steps).
void CKMenuBase114c::UpdateFocus(uint8_t player, uint8_t dir) {
    uint8_t item = 0xff;
    if (m_unk80[1] != 0) {
        item = (m_unk80[2] == 5 || m_unk80[2] == 0) ? FindItemUnderCursor(player) : m_unk6c[player];
        if (item != 0xff) {
            MoveFocusByInput(player, dir, item);
            return;
        }
    }
    item = 0xff;
    const uint8_t focus = m_unk6c[player];
    if (dir != 0xff && focus != 0xff && ButtonAt(this, focus) != nullptr) {
        uint8_t next = ButtonAt(this, focus)->GetNeighbor(dir);  // vt+0x7c
        for (uint32_t step = 1; next != 0xff; ++step) {
            CKInterfaceButtonBase* button = ButtonAt(this, next);
            if ((button->m_baFlags & CKInterfaceButtonBase::kFlagSkip) == 0) {
                item = next;
                break;
            }
            next = button->GetNeighbor(dir);
            if (step == 0xff) break;  // 255 steps: none
        }
    }
    MoveFocusByInput(player, dir, item);
}

// 0x005140b0 KBase730C_vfA0
void CKMenuBase114c::VfA0() {
    if (!FlashUIActive(FlashUIOf(this))) return;
    if (VfB4() == 0) {
        if (FlashUIOf(this) != nullptr) FlashUIOf(this)->StopAndNotifyElements();
    } else {
        Close();  // vt+0x5c
    }
    ResetWidgets();  // vt+0x98
    if ((m_ui32Flags & 1) != 0) {
        HandleStatePhase(2, 0);
        HandleStatePhase(1, 0);
    }
}

// 0x00518f28 KBase730C_ClearSlotsAndClose_maybe: closed (vt+0x5c), each reference group's dynamic references
// [first, count) and its states cleared, an open menu left, flags bits 1, 3 and 4 cleared.
void CKMenuBase114c::VfA8() {
    Close();
    for (uint32_t group = Vf84(); group-- != 0;) {
        RefGroup* entry = &Vf88()[group];
        GroupState* states = Vf90(group);
        const int32_t dynamic = static_cast<int32_t>(entry->m_unk08 - entry->m_unk04);
        if (dynamic > 0)
            std::memset(&Vf8C(group)[entry->m_unk04], 0, (static_cast<uint32_t>(dynamic) & 0x3fffffffu) * sizeof(IKSerializable*));
        if (states == nullptr) break;
        std::memset(states, 0, entry->m_unk08 * sizeof(GroupState));
    }
    if ((m_ui32Flags & 1) != 0) HandleStatePhase(2, 0);
    m_ui32Flags &= 0xffffffe5u;
}

// 0x00513df8 KBase730C_RefreshOptionWidgets_maybe: the buttons from the last; each index re-tested against
// the count (the inlined TVector accessor).
void CKMenuBase114c::RefreshOptionWidgets() {
    for (uint32_t i = m_apButtons.m_ui32NbUsedElt; i-- != 0;) {
        IKSerializable* object = i < m_apButtons.m_ui32NbUsedElt ? m_apButtons.m_pBlock[i] : nullptr;
        if (object == nullptr) continue;
        if (object->IsKindOfClass(0x634c) != 0) {
            static_cast<CKInterfaceButtonDouble*>(object)->LoadOptionValue();
        } else if (object->IsKindOfClass(0xa14c) != 0) {
            static_cast<CKInterfaceCheckBox*>(object)->LoadOptionValue();
        }
    }
}

// ---- C1.6 menus: the game manager calls the menus make ----
// (vt+0xb4, +0xb8, +0x1d4, +0x1e4, +0x31c and the game structure's vt+0x60 are the game manager's and the
// structure's own methods now.)

// A menu request as the menus write it: the game manager's stack set to the one menu (vt+0x304's id).
void MenuGm_RequestMenu(CKS08GameManager* manager, uint8_t menu) {
    const uint8_t id = manager->MenuId(menu);
    manager->m_ui32MenuStackDepth = 1;
    manager->m_aMenuStack[0] = id;
}

