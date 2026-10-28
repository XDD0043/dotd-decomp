// CScene2d.cpp - reconstructed original translation unit 0x649d8-0x65e50 (GAME_TOC1, main_toc1), 38 functions, 25 live.
// Primary class: CScene2d  key 0x50d  category Graphical  size 0x28  vtable 0xb15c80
// Other owners: CContainer2d (17), DrawUISceneWidgetList (1), IKNode2d (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x649d8  CScene2d_Delete
//   [ ] 0x64a28  CScene2d_Construct  [dead]
//   [ ] 0x64a60  CScene2d_Construct_2  [dead]
//   [x] 0x64a98  CScene2d_BroadcastEvent_maybe
//   [x] 0x64b20  CContainer2d_GetFirstChild
//   [x] 0x64b28  CContainer2d_GetLastChild
//   [x] 0x64b30  CContainer2d_GetChildAt
//   [ ] 0x64b90  CContainer2d_GetChildCount  [dead]
//   [ ] 0x64b98  CContainer2d_IsEmpty  [dead]
//   [ ] 0x64bb8  CScene2d_Enable  [dead]
//   [ ] 0x64bc8  CScene2d_Disable  [dead]
//   [ ] 0x64bd8  CScene2d_IsEnabled  [dead]
//   [ ] 0x64be0  CContainer2d_SwapChildWithPrev
//   [ ] 0x64dd0  CContainer2d_MoveChildToHead_maybe
//   [ ] 0x64e70  CContainer2d_SwapChildWithNext
//   [ ] 0x65060  CContainer2d_MoveChildToTail_maybe
//   [x] 0x650d8  CContainer2d_RemoveChild_maybe
//   [x] 0x652b8  CScene2d_AddChild
//   [x] 0x65468  CScene2d_AddChild_Thunk
//   [ ] 0x65490  RegisterCScene2dType
//   [ ] 0x65508  _GLOBAL__I_65508
//   [ ] 0x65518  CScene2d_Destroy
//   [x] 0x65560  CScene2d_DeleteArray
//   [x] 0x65608  DrawUISceneWidgetList
//   [ ] 0x656c8  CContainer2d_ShowChildren_maybe
//   [ ] 0x65750  CContainer2d_InsertChildAt_maybe  [dead]
//   [ ] 0x659b8  CContainer2d_GetChildOfTypeAt_maybe  [dead]
//   [ ] 0x65a28  CContainer2d_HideChildren_maybe
//   [ ] 0x65ab0  CContainer2d_DestroyChildrenWithoutFlag5Bit0_maybe  [dead]
//   [ ] 0x65bb8  CContainer2d_CountChildrenOfType_maybe  [dead]
//   [ ] 0x65c00  IKNode2d_IsChildOf_maybe  [dead]
//   [ ] 0x65c28  CScene2d_PostLoad
//   [ ] 0x65c30  CContainer2d_RemoveChildAt
//   [x] 0x65c98  CScene2d_Create
//   [x] 0x65d00  CScene2d_CreateArray
//   [ ] 0x65dc8  CScene2d_Destructor
//   [ ] 0x65de8  CScene2d_Destructor_2  [dead]
//   [ ] 0x65e08  CScene2d_DeletingDestructor
//
//   [x] 0x997cf8  CScene2d_IsKindOfClass  [inline]
//   [x] 0x997d20  CScene2d_GetClassType  [inline]
//   [x] 0x997d28  CScene2d_GetClassID  [inline]
//   [ ] 0x997d30  CScene2d_RecursiveRegistration  [inline]
//   [ ] 0x997e40  CScene2d_Save  [inline]
//   [x] 0x998010  CScene2d_Load  [inline]
#include "k2000/graphical/ui/CScene2d.h"

#include "k2000/graphical/ui/CManager2d.h"
#include "k2000/io/IKFile.h"
#include "k2000/misc/Engine.h"
#include "k2000/render/CRenderer.h"
#include "k2000/system/CTimeManager.h"
#include "k2000/ui/IKNode2d.h"

// 0x00065c98 CScene2d_Create (the same stores as CScene2d_Construct 0x64a28): the IRendableObject part,
// then the scene's fields, in the original's order. +0x0c is left as it is.
CScene2d::CScene2d() {
    m_pNextAccumulatedObject = nullptr;
    m_BitProperties = 0;
    m_pPriorityParent = 0;
    m_pLightSet = nullptr;
    m_bEnable = 0;
    m_pLastNode = nullptr;
    m_pRootNode = nullptr;
    m_ui32NodeCount = 0;
}

// 0x00998010 CScene2d_Load
int32_t CScene2d::Load(IKFile* file, int32_t type) {
    IRendableObject::Load(file, type);
    IKFile_ReadRef(file, &m_pRootNode);
    IKFile_ReadRef(file, &m_pLastNode);
    ReadU32LE(file, &m_ui32NodeCount);
    ReadU8(file, &m_bEnable);
    return 1;
}

// 0x00065608 DrawUISceneWidgetList. The frame context the renderer passes down is the game loop's frame
// clock (CTimeManager's IKTime, what RenderGameFrame receives). BUG(original): a disabled scene returns
// without PopRenderStates, so the renderer's state stack grows by one entry per frame.
void CScene2d::Render() {
    PushRenderStates(g_pRenderStateRenderer);
    SetUIOverlayRenderStates();
    if (m_bEnable == 0) return;
    IKTime* frameClock = g_pEngine->m_timeManager->m_pTime;
    for (IKNode2d* node = static_cast<IKNode2d*>(m_pRootNode); node != nullptr; node = node->m_pNext) {
        node->Render(frameClock);
    }
    PopRenderStates(g_pRenderStateRenderer);
}

// 0x00064b30 CContainer2d_GetChildAt
IKSerializable* CScene2d::GetChildAt(uint32_t index) const {
    if (!(index < m_ui32NodeCount)) return nullptr;
    IKSerializable* node = m_pRootNode;
    if (index == 0 || node == nullptr) return node;
    for (uint32_t i = index; i != 0 && node != nullptr; --i) node = static_cast<IKNode2d*>(node)->m_pNext;
    return node;
}

// 0x00064a98 CScene2d_BroadcastEvent_maybe
void CScene2d::BroadcastEvent(uint8_t event, void* data) {
    for (IKNode2d* node = static_cast<IKNode2d*>(m_pRootNode); node != nullptr; node = node->m_pNext) {
        node->RecursiveNodeReach(event, data);
    }
}

// 0x000650d8 CContainer2d_RemoveChild_maybe (Ghidra's name; it is CScene2d's): `node` leaves this scene's list
// (its neighbours linked together, the root / last node moved on) and loses its owner. Null when it is not
// in this scene.
IKNode2d* CScene2d::RemoveChild(IKNode2d* node) {
    if (node == nullptr) return nullptr;
    if (node->m_pOwner != this) return nullptr;
    IKNode2d* previous = node->m_pPrevious;
    IKNode2d* next = node->m_pNext;
    if (previous != nullptr) {
        previous->SetNext(next);  // vt+0x70
        node->SetPrevious(nullptr);  // vt+0x6c
    }
    if (next != nullptr) {
        next->SetPrevious(previous);
        node->SetNext(nullptr);
    }
    if (m_pRootNode == node) m_pRootNode = next;
    if (m_pLastNode == node) m_pLastNode = previous;
    node->SetOwner(nullptr);  // vt+0x50
    --m_ui32NodeCount;
    return node;
}

// 0x000652b8 CScene2d_AddChild (the thunk 0x65468 CScene2d_AddChild_Thunk calls it): `node` is appended to the
// scene's list; a node of another scene is taken out of it first. 0 when the node is null or stays owned.
// BUG(original): the owner is read before the null check.
uint8_t CScene2d::AddChild(IKNode2d* node) {
    if (node->m_pOwner != nullptr) static_cast<CScene2d*>(node->m_pOwner)->RemoveChild(node);
    if (node != nullptr && node->m_pOwner == nullptr) {
        IKNode2d* last = static_cast<IKNode2d*>(m_pLastNode);
        if (last == nullptr) {
            m_pRootNode = node;
            node->SetPrevious(nullptr);
        } else {
            last->SetNext(node);
            node->SetPrevious(last);
        }
        m_pLastNode = node;
        node->SetNext(nullptr);
        node->SetOwner(this);
        ++m_ui32NodeCount;
        return 1;
    }
    return 0;
}
