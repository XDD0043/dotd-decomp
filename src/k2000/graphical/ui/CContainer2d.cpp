// CContainer2d.cpp - reconstructed original translation unit 0x600b0-0x61ab8 (GAME_TOC1, main_toc1), 53 functions, 38 live.
// Primary class: CContainer2d  key 0x4cd  category Graphical  size 0x38  vtable 0xb15ab0
// Other owners: DrawUIContainerChildScenes (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x600b0  CContainer2d_Delete
//   [ ] 0x60100  CContainer2d_RecursiveRegistration
//   [x] 0x601d8  CContainer2d_GetName
//   [ ] 0x601e0  FUN_000601e0  [dead]
//   [ ] 0x601e8  CContainer2d_vfB8
//   [ ] 0x601f8  CContainer2d_vfBC
//   [ ] 0x60208  CContainer2d_Destroy
//   [ ] 0x60230  RegisterCContainer2dClass
//   [ ] 0x602a8  _GLOBAL__I_602a8
//   [ ] 0x602b8  CContainer2d_vfDC
//   [ ] 0x60328  CContainer2d_vfD8
//   [ ] 0x60358  CContainer2d_vfD4
//   [ ] 0x60388  CContainer2d_vfD0
//   [ ] 0x603f8  CContainer2d_vfCC
//   [ ] 0x60428  CContainer2d_vfC8
//   [ ] 0x60458  CContainer2d_GetNextChildAcrossLists_maybe  [dead]
//   [ ] 0x604d0  CContainer2d_GetFirstChildAcrossLists_maybe  [dead]
//   [ ] 0x60558  CContainer2d_GetPrevChildAcrossLists_maybe  [dead]
//   [ ] 0x605d0  CContainer2d_GetLastChildAcrossLists_maybe  [dead]
//   [ ] 0x60658  CContainer2d_vfB4
//   [ ] 0x60688  CContainer2d_vfA4
//   [ ] 0x606b8  CContainer2d_vfB0
//   [ ] 0x606e8  CContainer2d_vfA0
//   [ ] 0x60718  CContainer2d_vfAC
//   [ ] 0x60748  CContainer2d_vfA8
//   [ ] 0x60778  CContainer2d_vf9C
//   [ ] 0x607a8  CContainer2d_vf98
//   [ ] 0x607d8  CContainer2d_vf90
//   [ ] 0x608a0  CContainer2d_FindSelectedButton_maybe  [dead]
//   [ ] 0x60998  CContainer2d_CountChildrenOfType_List30_maybe  [dead]
//   [ ] 0x609c8  CContainer2d_GetChildCount_List30_maybe  [dead]
//   [ ] 0x609f8  CContainer2d_GetChildCount_List2c_maybe  [dead]
//   [ ] 0x60a28  CContainer2d_GetTotalChildCount_maybe  [dead]
//   [ ] 0x60a80  CContainer2d_GetChildOfTypeAt_List30_maybe  [dead]
//   [ ] 0x60ab0  CContainer2d_GetChildAt_List30  [dead]
//   [ ] 0x60ae0  CContainer2d_GetChildAt_List2c  [dead]
//   [ ] 0x60b10  CContainer2d_ResetRuntime_maybe
//   [ ] 0x60b68  CContainer2d_SetNameString_maybe
//   [x] 0x60bf0  CContainer2d_OnEvent_maybe
//   [ ] 0x60c70  CContainer2d_Construct  [dead]
//   [ ] 0x60cc0  CContainer2d_Construct_2  [dead]
//   [x] 0x60d10  CContainer2d_DeleteArray
//   [x] 0x60db8  DrawUIContainerChildScenes
//   [ ] 0x60e70  CContainer2d_vf94
//   [ ] 0x60ee8  CContainer2d_vf8C
//   [ ] 0x60f50  CContainer2d_Save
//   [x] 0x611b0  CContainer2d_Load
//   [x] 0x61408  CContainer2d_CreateArray
//   [x] 0x614f0  CContainer2d_Create
//   [ ] 0x61560  CContainer2d_vfC4
//   [ ] 0x616c0  CContainer2d_vfC0
//   [x] 0x61820  CContainer2d_vf80
//   [ ] 0x61938  CContainer2d_GetBoundingRect
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
void CContainer2d::Render(IKTime* /*frameClock*/) {
    if ((m_baFlags & 2) == 0) return;
    Rt2dCTMPush();
    static_cast<CScene2d*>(m_pNonButtonObjects)->Render();  // vt+0x5c
    static_cast<CScene2d*>(m_pButtonObjects)->Render();
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
