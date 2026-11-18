// CContainer2d.cpp - reconstructed original translation unit 0x600b0-0x61ab8 (GAME_TOC1, main_toc1), 53 functions, 38 live.
// Primary class: CContainer2d  key 0x4cd  category Graphical  size 0x38  vtable 0xb15ab0
// Other owners: DrawUIContainerChildScenes (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x600b0  CContainer2d_Delete
//   [x] 0x60100  CContainer2d_RecursiveRegistration  (CContainer2d::RecursiveRegistration)
//   [x] 0x601d8  CContainer2d_GetName
//   [ ] 0x601e0  FUN_000601e0  [dead]
//   [x] 0x601e8  CContainer2d_vfB8  (CContainer2d::EnableButtonLoop, CContainer2d.h)
//   [x] 0x601f8  CContainer2d_vfBC  (CContainer2d::DisableButtonLoop, CContainer2d.h)
//   [x] 0x60208  CContainer2d_Destroy  (inherited: IKNode2d_Destroy)
//   [ ] 0x60230  RegisterCContainer2dClass
//   [ ] 0x602a8  _GLOBAL__I_602a8
//   [x] 0x602b8  CContainer2d_vfDC  (CContainer2d::ShowAll)
//   [x] 0x60328  CContainer2d_vfD8  (CContainer2d::ShowNonButtons)
//   [x] 0x60358  CContainer2d_vfD4  (CContainer2d::ShowButtons)
//   [x] 0x60388  CContainer2d_vfD0  (CContainer2d::HideAll)
//   [x] 0x603f8  CContainer2d_vfCC  (CContainer2d::HideNonButtons)
//   [x] 0x60428  CContainer2d_vfC8  (CContainer2d::HideButtons)
//   [ ] 0x60458  CContainer2d_GetNextChildAcrossLists_maybe  [dead]
//   [ ] 0x604d0  CContainer2d_GetFirstChildAcrossLists_maybe  [dead]
//   [ ] 0x60558  CContainer2d_GetPrevChildAcrossLists_maybe  [dead]
//   [ ] 0x605d0  CContainer2d_GetLastChildAcrossLists_maybe  [dead]
//   [x] 0x60658  CContainer2d_vfB4  (CContainer2d::NonButtonGoDown)
//   [x] 0x60688  CContainer2d_vfA4  (CContainer2d::ButtonGoDown)
//   [x] 0x606b8  CContainer2d_vfB0  (CContainer2d::NonButtonGoUp)
//   [x] 0x606e8  CContainer2d_vfA0  (CContainer2d::ButtonGoUp)
//   [x] 0x60718  CContainer2d_vfAC  (CContainer2d::NonButtonToTail)
//   [x] 0x60748  CContainer2d_vfA8  (CContainer2d::NonButtonToHead)
//   [x] 0x60778  CContainer2d_vf9C  (CContainer2d::RemoveNonButton)
//   [x] 0x607a8  CContainer2d_vf98  (CContainer2d::RemoveButton)
//   [x] 0x607d8  CContainer2d_vf90  (CContainer2d::AddNode)
//   [ ] 0x608a0  CContainer2d_FindSelectedButton_maybe  [dead]
//   [ ] 0x60998  CContainer2d_CountChildrenOfType_List30_maybe  [dead]
//   [ ] 0x609c8  CContainer2d_GetChildCount_List30_maybe  [dead]
//   [ ] 0x609f8  CContainer2d_GetChildCount_List2c_maybe  [dead]
//   [ ] 0x60a28  CContainer2d_GetTotalChildCount_maybe  [dead]
//   [ ] 0x60a80  CContainer2d_GetChildOfTypeAt_List30_maybe  [dead]
//   [ ] 0x60ab0  CContainer2d_GetChildAt_List30  [dead]
//   [ ] 0x60ae0  CContainer2d_GetChildAt_List2c  [dead]
//   [x] 0x60b10  CContainer2d_ResetRuntime_maybe  (CContainer2d::FreeMemory)
//   [x] 0x60b68  CContainer2d_SetNameString_maybe  (CContainer2d::SetName)
//   [x] 0x60bf0  CContainer2d_OnEvent_maybe
//   [ ] 0x60c70  CContainer2d_Construct  [dead]
//   [ ] 0x60cc0  CContainer2d_Construct_2  [dead]
//   [x] 0x60d10  CContainer2d_DeleteArray
//   [x] 0x60db8  DrawUIContainerChildScenes
//   [x] 0x60e70  CContainer2d_vf94  (CContainer2d::RemoveNode)
//   [x] 0x60ee8  CContainer2d_vf8C  (CContainer2d::SelectButton)
//   [ ] 0x60f50  CContainer2d_Save
//   [x] 0x611b0  CContainer2d_Load
//   [x] 0x61408  CContainer2d_CreateArray
//   [x] 0x614f0  CContainer2d_Create
//   [x] 0x61560  CContainer2d_vfC4  (CContainer2d::NextButton)
//   [x] 0x616c0  CContainer2d_vfC0  (CContainer2d::PreviousButton)
//   [x] 0x61820  CContainer2d_vf80
//   [x] 0x61938  CContainer2d_GetBoundingRect  (CContainer2d::GetBoundingBox)
//
//   [x] 0x997a68  CContainer2d_GetClassType  [inline]
//   [x] 0x997a70  CContainer2d_GetClassID  [inline]
//   [x] 0x997a78  CContainer2d_IsKindOfClass  [inline]
//   [x] 0x997aa0  CContainer2d_DeletingDestructor  [inline]
//   [x] 0x997ae8  CContainer2d_Destructor  [inline]
//   [ ] 0x997b08  KStub_Nop_997b08  [inline]
#include "k2000/graphical/ui/CContainer2d.h"

#include "Renderware/rt2d/Rt2d.h"
#include "k2000/graphical/ui/CScene2d.h"
#include "k2000/io/IKFile.h"
#include "k2000/memory/Mem.h"
#include "k2000/ui/IKButton2d.h"

// Inlined in 0x000614f0 CContainer2d_Create (after IKNode2d_ConstructBase), the stores in its order.
CContainer2d::CContainer2d() {
    m_bButtonLoop = 0;
    m_szName = nullptr;
    m_pButtonObjects = nullptr;
    m_pNonButtonObjects = nullptr;
}

// 0x000611b0 CContainer2d_Load. Reads for every type (no branch).
int32_t CContainer2d::Load(IKFile* file, int32_t type) {
    IKNode2d::Load(file, type);
    int16_t length = 0;
    ReadS16LE(file, &length);
    if (length < 0) {
        m_szName = nullptr;
    } else {
        m_szName = static_cast<char*>(Mem_AllocAligned16(static_cast<uint32_t>(length + 1)));
        ReadRaw(file, m_szName, static_cast<uint32_t>(length));
        m_szName[length] = 0;
    }
    IKFile_ReadRef(file, &m_pButtonObjects);
    IKFile_ReadRef(file, &m_pNonButtonObjects);
    ReadU8(file, &m_bButtonLoop);
    return 1;
}

// 0x00060db8 DrawUIContainerChildScenes (returns whether it drew; no caller reads it)
void CContainer2d::Render(IKTime* frameClock) {
    if ((m_baFlags & 2) == 0) return;
    Rt2dCTMPush();
    static_cast<CScene2d*>(m_pNonButtonObjects)->Render(frameClock);  // vt+0x5c
    static_cast<CScene2d*>(m_pButtonObjects)->Render(frameClock);
    Rt2dCTMPop();
}

// 0x00061820 CContainer2d_Scale (from the assembly). The walk follows each node's owner: a node owned by
// the button scene continues along m_pNext and then with the other scene's first node; a node owned by
// the other scene continues along m_pNext; a node with no owner, or owned by neither, ends the walk.
// BUG(original): when the button scene runs out, the other scene's first node is read without the null
// test of the start (a container without m_pNonButtonObjects reads +0x18 of null).
void CContainer2d::Scale(const CVector2& scale) {
    CScene2d* const buttons = static_cast<CScene2d*>(m_pButtonObjects);
    IKNode2d* node = nullptr;
    if (buttons != nullptr) node = static_cast<IKNode2d*>(buttons->GetFirstChild());
    if (node == nullptr) {
        CScene2d* const others = static_cast<CScene2d*>(m_pNonButtonObjects);
        if (others == nullptr) return;
        node = static_cast<IKNode2d*>(others->GetFirstChild());
        if (node == nullptr) return;
    }
    for (;;) {
        node->Scale(scale);  // vt+0x80
        IKSerializable* const owner = node->m_pOwner;
        if (owner == nullptr) return;
        IKNode2d* const next = node->m_pNext;
        if (m_pButtonObjects == owner) {
            if (next != nullptr) {
                node = next;
                continue;
            }
            node = static_cast<IKNode2d*>(static_cast<CScene2d*>(m_pNonButtonObjects)->GetFirstChild());
        } else if (m_pNonButtonObjects == owner) {
            node = next;
        } else {
            return;
        }
        if (node == nullptr) return;
    }
}

// 0x00060bf0 CContainer2d_OnEvent_maybe
void CContainer2d::RecursiveNodeReach(uint8_t what, void* data) {
    if (m_pButtonObjects != nullptr) static_cast<CScene2d*>(m_pButtonObjects)->BroadcastEvent(what, data);
    if (m_pNonButtonObjects != nullptr) static_cast<CScene2d*>(m_pNonButtonObjects)->BroadcastEvent(what, data);
}

#include <cstring>

#include "k2000/logic/CKSavingManager.h"
#include "k2000/misc/Engine.h"

namespace {
CScene2d* Scene(IKSerializable* scene) { return static_cast<CScene2d*>(scene); }
}  // namespace

// 0x00060100 CContainer2d_RecursiveRegistration
void CContainer2d::RecursiveRegistration(int32_t type) {
    if (static_cast<uint32_t>(type - 4) <= 3) return;
    g_pEngine->m_pSavingManager->RegisterSerializableObject(this, nullptr);  // vt+0x24
    m_pButtonObjects->RecursiveRegistration(type);
    m_pNonButtonObjects->RecursiveRegistration(type);
}

// 0x00060b10 CContainer2d_ResetRuntime_maybe
void CContainer2d::FreeMemory() {
    IKNode2d::FreeMemory();
    if (m_szName != nullptr) {
        Mem_FreeAligned16(m_szName);
        m_szName = nullptr;
    }
    m_bButtonLoop = 0;
}

// 0x00060b68 CContainer2d_SetNameString_maybe
void CContainer2d::SetName(const char* name) {
    if (name == nullptr) return;
    if (m_szName != nullptr) Mem_FreeAligned16(m_szName);
    m_szName = static_cast<char*>(Mem_AllocAligned16(static_cast<uint32_t>(std::strlen(name) + 1)));
    std::strcpy(m_szName, name);
}

// 0x00060ee8 CContainer2d_vf8C
bool CContainer2d::SelectButton(uint32_t index) {
    IKButton2d* button = static_cast<IKButton2d*>(Scene(m_pButtonObjects)->GetChildAt(index));
    if (button != nullptr) button->Select();  // vt+0x88
    return button != nullptr;
}

// 0x000607d8 CContainer2d_vf90
uint8_t CContainer2d::AddNode(IKNode2d* node) {
    if (node != nullptr && node->m_ui8Type == 2) {
        const uint8_t added = Scene(m_pButtonObjects)->AddChild(node);  // the thunk 0x65468
        static_cast<IKButton2d*>(node)->Select();                       // vt+0x88
        return added;
    }
    return Scene(m_pNonButtonObjects)->AddChild(node);
}

// 0x00060e70 CContainer2d_vf94
IKNode2d* CContainer2d::RemoveNode(IKNode2d* node) {
    if (node != nullptr && node->m_ui8Type == 2) return Scene(m_pButtonObjects)->RemoveChild(node);
    return Scene(m_pNonButtonObjects)->RemoveChild(node);
}

// 0x000607a8 CContainer2d_vf98 / 0x00060778 CContainer2d_vf9C
IKNode2d* CContainer2d::RemoveButton(uint32_t index) { return Scene(m_pButtonObjects)->RemoveChildAt(index); }
IKNode2d* CContainer2d::RemoveNonButton(uint32_t index) { return Scene(m_pNonButtonObjects)->RemoveChildAt(index); }

// 0x000606e8 CContainer2d_vfA0 / 0x00060688 CContainer2d_vfA4
uint8_t CContainer2d::ButtonGoUp(IKNode2d* node) { return Scene(m_pButtonObjects)->SwapChildWithPrev(node); }
uint8_t CContainer2d::ButtonGoDown(IKNode2d* node) { return Scene(m_pButtonObjects)->SwapChildWithNext(node); }
// 0x00060748 CContainer2d_vfA8 / 0x00060718 CContainer2d_vfAC
uint8_t CContainer2d::NonButtonToHead(IKNode2d* node) { return Scene(m_pNonButtonObjects)->MoveChildToHead(node); }
uint8_t CContainer2d::NonButtonToTail(IKNode2d* node) { return Scene(m_pNonButtonObjects)->MoveChildToTail(node); }
// 0x000606b8 CContainer2d_vfB0 / 0x00060658 CContainer2d_vfB4
uint8_t CContainer2d::NonButtonGoUp(IKNode2d* node) { return Scene(m_pNonButtonObjects)->SwapChildWithPrev(node); }
uint8_t CContainer2d::NonButtonGoDown(IKNode2d* node) { return Scene(m_pNonButtonObjects)->SwapChildWithNext(node); }

// 0x00061560 CContainer2d_vfC4 (NextButton): the first selected button; from its next node (or, with the button loop,
// the first one) on, the first enabled node (+0x05 bit 1) is selected. Meeting the selected button again, or the end
// without the loop, selects nothing. BUG(original): after a wrap the first node is not null-tested, and a wrap that
// starts on the selected button never meets it again (no enabled button: an endless walk).
uint8_t CContainer2d::NextButton() {
    IKNode2d* selected = static_cast<IKNode2d*>(Scene(m_pButtonObjects)->GetFirstChild());
    for (;; selected = selected->m_pNext) {
        if (selected == nullptr) return 0;
        if (Button2d_IsSelected(selected) != 0) break;
    }
    IKNode2d* node = selected->m_pNext;
    if (node == nullptr) {
        if (m_bButtonLoop == 0) return 0;
        node = static_cast<IKNode2d*>(Scene(m_pButtonObjects)->GetFirstChild());
        if (node == nullptr) return 0;
    }
    while ((node->m_baFlags & 2) == 0) {
        IKNode2d* next = node->m_pNext;
        if (next == selected) return 0;
        if (next == nullptr) {
            if (m_bButtonLoop == 0) return 0;
            next = static_cast<IKNode2d*>(Scene(m_pButtonObjects)->GetFirstChild());
        }
        node = next;
    }
    static_cast<IKButton2d*>(node)->Select();  // vt+0x88
    return 1;
}

// 0x000616c0 CContainer2d_vfC0 (PreviousButton): the same walk backwards (m_pPrevious, the last node).
uint8_t CContainer2d::PreviousButton() {
    IKNode2d* selected = static_cast<IKNode2d*>(Scene(m_pButtonObjects)->GetFirstChild());
    for (;; selected = selected->m_pNext) {
        if (selected == nullptr) return 0;
        if (Button2d_IsSelected(selected) != 0) break;
    }
    IKNode2d* node = selected->m_pPrevious;
    if (node == nullptr) {
        if (m_bButtonLoop == 0) return 0;
        node = static_cast<IKNode2d*>(Scene(m_pButtonObjects)->GetLastChild());
        if (node == nullptr) return 0;
    }
    while ((node->m_baFlags & 2) == 0) {
        IKNode2d* previous = node->m_pPrevious;
        if (previous == selected) return 0;
        if (previous == nullptr) {
            if (m_bButtonLoop == 0) return 0;
            previous = static_cast<IKNode2d*>(Scene(m_pButtonObjects)->GetLastChild());
        }
        node = previous;
    }
    static_cast<IKButton2d*>(node)->Select();  // vt+0x88
    return 1;
}

// 0x00060428 CContainer2d_vfC8 .. 0x000602b8 CContainer2d_vfDC
uint8_t CContainer2d::HideButtons() { return Scene(m_pButtonObjects)->HideChildren(); }
uint8_t CContainer2d::HideNonButtons() { return Scene(m_pNonButtonObjects)->HideChildren(); }
uint8_t CContainer2d::HideAll() {
    const uint8_t buttons = Scene(m_pButtonObjects)->HideChildren();
    const uint8_t others = Scene(m_pNonButtonObjects)->HideChildren();
    return (buttons != 0 && others != 0) ? 1 : 0;
}
uint8_t CContainer2d::ShowButtons() { return Scene(m_pButtonObjects)->ShowChildren(); }
uint8_t CContainer2d::ShowNonButtons() { return Scene(m_pNonButtonObjects)->ShowChildren(); }
uint8_t CContainer2d::ShowAll() {
    const uint8_t buttons = Scene(m_pButtonObjects)->ShowChildren();
    const uint8_t others = Scene(m_pNonButtonObjects)->ShowChildren();
    return (buttons != 0 && others != 0) ? 1 : 0;
}

// 0x00061938 CContainer2d_GetBoundingRect (the node walk of Scale: the button scene, then the others)
void CContainer2d::GetBoundingBox(CBox2D* box) const {
    box->m_sup.m_fX = 0.0f;
    box->m_inf.m_fY = 1.0f;
    box->m_sup.m_fY = 0.0f;
    box->m_inf.m_fX = 1.0f;
    IKNode2d* node = nullptr;
    if (m_pButtonObjects != nullptr) node = static_cast<IKNode2d*>(Scene(m_pButtonObjects)->GetFirstChild());
    if (node == nullptr) {
        if (m_pNonButtonObjects == nullptr) return;
        node = static_cast<IKNode2d*>(Scene(m_pNonButtonObjects)->GetFirstChild());
    }
    while (node != nullptr) {
        CBox2D nodeBox;
        node->GetBoundingBox(&nodeBox);  // vt+0x78
        if (!(box->m_inf.m_fX <= nodeBox.m_inf.m_fX)) box->m_inf.m_fX = nodeBox.m_inf.m_fX;
        if (!(box->m_inf.m_fY <= nodeBox.m_inf.m_fY)) box->m_inf.m_fY = nodeBox.m_inf.m_fY;
        if (!(box->m_sup.m_fX <= nodeBox.m_sup.m_fX)) box->m_sup.m_fX = nodeBox.m_sup.m_fX;
        if (!(box->m_sup.m_fY <= nodeBox.m_sup.m_fY)) box->m_sup.m_fY = nodeBox.m_sup.m_fY;
        IKSerializable* const owner = node->m_pOwner;
        if (owner == nullptr) return;
        IKNode2d* const next = node->m_pNext;
        if (m_pButtonObjects == owner) {
            node = next != nullptr ? next : static_cast<IKNode2d*>(Scene(m_pNonButtonObjects)->GetFirstChild());
        } else if (m_pNonButtonObjects == owner) {
            node = next;
        } else {
            return;
        }
    }
}
