// CKInterfaceScrollingMenu.cpp - reconstructed original translation unit 0x5255c0-0x52a150 (GAME_TOC1, main_toc1), 34 functions, 33 live.
// Primary class: CKInterfaceScrollingMenu  key 0x638c  category Logic  size 0x1c4  vtable 0xb2b890
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x5255c0  CKInterfaceScrollingMenu_CallItemVf5C_maybe  (SetItemInteractionState)
//   [ ] 0x525628  RegisterCKInterfaceScrollingMenuClass
//   [ ] 0x5256a0  _GLOBAL__I_5256a0
//   [ ] 0x5256b0  CKInterfaceScrollingMenu_Save
//   [x] 0x5256d8  CKInterfaceScrollingMenu_RecursiveRegistration
//   [x] 0x525700  CKInterfaceScrollingMenu_Destroy
//   [x] 0x5257c8  CKInterfaceScrollingMenu_Construct_2  (the same code as 0x525a78 CKInterfaceScrollingMenu_Construct)
//   [x] 0x5258a8  CKInterfaceScrollingMenu_DeleteArray  (DOTD_DECLARE_FACTORIES)
//   [x] 0x525948  CKInterfaceScrollingMenu_BaseDestructor  (the destructor's body, then the base's)
//   [x] 0x5259b8  CKInterfaceScrollingMenu_Close
//   [x] 0x525a78  CKInterfaceScrollingMenu_Construct
//   [x] 0x525b58  CKInterfaceScrollingMenu_PostLoad
//   [x] 0x525b68  CKInterfaceScrollingMenu_DeletingDestructor  (the destructor; delete)
//   [x] 0x525be0  CKInterfaceScrollingMenu_Destructor
//   [x] 0x525c50  CKInterfaceScrollingMenu_RemoveItem_maybe  (no caller in the original)
//   [x] 0x525d90  CKInterfaceScrollingMenu_AddItem_maybe  (no caller in the original)
//   [x] 0x525e78  CKInterfaceScrollingMenu_vf7C  (GetNeighbor)
//   [x] 0x5260c0  CKInterfaceScrollingMenu_UpdateVisibility_maybe
//   [x] 0x526250  CKInterfaceScrollingMenu_vf60  (SetPosition)
//   [x] 0x5263c0  CKInterfaceScrollingMenu_Load
//   [x] 0x526a78  CKInterfaceScrollingMenu_UpdateItemLayout_maybe
//   [x] 0x526cf8  CKInterfaceScrollingMenu_Create  (DOTD_DECLARE_FACTORIES; the constructor inlined)
//   [x] 0x526de8  CKInterfaceScrollingMenu_CreateArray  (DOTD_DECLARE_FACTORIES)
//   [x] 0x526f48  CKInterfaceScrollingMenu_HideScrollArrow_maybe
//   [x] 0x527498  CKInterfaceScrollingMenu_SetSelectedRow_maybe  (SetFirstVisible)
//   [ ] 0x527608  CKInterfaceScrollingMenu_AutoScrollStep_maybe  [dead]
//   [x] 0x5276d0  CKInterfaceScrollingMenu_SetColumnSelection_maybe  (SetArrowState)
//   [x] 0x527e48  CKInterfaceScrollingMenu_vf84  (SetDisabled)
//   [x] 0x5280b8  CKInterfaceScrollingMenu_ShowScrollArrow_maybe
//   [x] 0x528370  CKInterfaceScrollingMenu_Show
//   [x] 0x528448  CKInterfaceScrollingMenu_Hide
//   [x] 0x528508  CKInterfaceScrollingMenu_Open
//   [x] 0x528ab8  CKInterfaceScrollingMenu_vf5C  (SetInteractionState)
//   [x] 0x5296e8  CKInterfaceScrollingMenu_Update
//
//   [x] 0x998518  CKInterfaceScrollingMenu_vf74  [inline]  (CKInterfaceButtonBase::StartFadeOut, empty)
//   [x] 0x9c8478  CKInterfaceScrollingMenu_IsKindOfClass  [inline]
//   [x] 0x9c84a0  CKInterfaceScrollingMenu_GetClassType  [inline]
//   [x] 0x9c84a8  CKInterfaceScrollingMenu_GetClassID  [inline]
//   [x] 0x9c84b0  CKInterfaceScrollingMenu_IsFadeOutFinished_maybe  [inline]
//   [x] 0x9c84d8  CKInterfaceScrollingMenu_vf88  [inline]
//   [x] 0x9c84e0  CKInterfaceScrollingMenu_vf8C  [inline]
//   [x] 0x9c84e8  KBaseE8D_vf8  [inline]  (KBaseE8D.h)
//   [x] 0x9c8508  KBaseE8D_vf14  [inline]  (KBaseE8D.h)
//   [x] 0x9c8510  KBaseE8D_vf18  [inline]  (KBaseE8D.h)
//   [x] 0x9c8518  KBaseE8D_vf10  [inline]  (KBaseE8D.h)
//   [x] 0x9c8520  KBaseE8D_vf58  [inline]  (KBaseE8D.h)
//   [x] 0x9c8528  KBaseE8D_vf5C  [inline]  (KBaseE8D.h)
#include "k2000/logic/ui/CKInterfaceScrollingMenu.h"

#include <cmath>
#include <cstring>

#include "Renderware/rpprtstd/RpPrtStd.h"
#include "Spyro2008/logic/CKMenuBase114c.h"
#include "crt/ppc_ops.h"
#include "k2000/dictionaries/CKSoundDictionaryID.h"
#include "k2000/graphical/fx/CBillboard2d.h"
#include "k2000/graphical/ui/CFlashHotSpot.h"
#include "k2000/groups/TVectorPush.h"
#include "k2000/io/IKFile.h"
#include "k2000/logic/sound/CKSound.h"
#include "k2000/memory/Mem.h"
#include "k2000/misc/FloatApproach.h"
#include "k2000/scenegraph/CParticlesNodeFx.h"
#include "k2000/system/IKTime.h"
#include "k2000/ui/IKNode2d.h"

namespace {

using Menu = CKInterfaceScrollingMenu;
using Ramp = CKInterfaceScrollingMenu::Ramp;

// 0x00c50dc4: a CVector2 (0, 0) in the data segment (read live: 0.0, 0.0).
const CVector2 kZeroVector2 = {0.0f, 0.0f};

CBillboard2d* AsBillboard(IKSerializable* node) { return static_cast<CBillboard2d*>(node); }
IKNode2d* AsNode(IKSerializable* node) { return static_cast<IKNode2d*>(node); }
CKInterfaceButtonBase* AsItem(IKSerializable* item) { return static_cast<CKInterfaceButtonBase*>(item); }
float DeltaTime(const IKTime* frameClock) { return frameClock->m_afDeltaTime[IKTime::FIXED_GAME_TIME]; }  // +0x20

// 0x009972d0 IKBillboard2d_SetBillboardSize (the billboard part's vt+0x30; CBillboard2d does not override it).
void SetBillboardSize(IKSerializable* node, const CVector2& size) { AsBillboard(node)->m_vBillboardSize = size; }

// The disabled bit (m_baFlags bit 1) as 0 / 1: the arrows' state 0 / 1 (or 2 / 3, 4 / 3) follow it.
uint8_t DisabledBit(const Menu* m) { return static_cast<uint8_t>((m->m_baFlags >> 1) & 1); }

// The arrow test every slot inlines: pair `arrow` (not kArrowNone) has a first node, and that node's size ramps
// are heading somewhere or the node is enabled (IKNode2d flag bit 1). fcmpu + beq: a NaN target counts as moving.
bool IsArrowActive(const Menu* m, int32_t arrow) {
    if (arrow == Menu::kArrowNone) return false;
    IKSerializable* node = m->m_apArrowNodes[arrow][0];
    if (node == nullptr) return false;
    return m->m_aArrowSizeX[arrow][0].m_fTarget != 0.0f || m->m_aArrowSizeY[arrow][0].m_fTarget != 0.0f ||
           ((AsNode(node)->m_baFlags >> 1) & 1) != 0;
}

// The item accessor the slots inline with a byte index (rlwinm (i & 0xff) * 4).
IKSerializable* ItemAt8(const Menu* m, int32_t index) { return m->m_vItems.m_pBlock[static_cast<uint8_t>(index)]; }
// index > -1 and below the count (both signed compares).
bool InList(const Menu* m, int32_t index) {
    return index > -1 && static_cast<int32_t>(m->m_vItems.m_ui32NbUsedElt) > index;
}
void SetItemState8(const Menu* m, int32_t index, int32_t state) {
    IKSerializable* item = ItemAt8(m, index);
    if (item != nullptr) AsItem(item)->SetInteractionState(state);  // vt+0x5c
}

// The focus moved to item `row` (inlined in SetInteractionState 2..4, Open, HideScrollArrow and Update): the item
// focused (state 2), a focused arrow back to its plain state; then the focused item is `row` (-1: none).
void FocusItem(Menu* m, int32_t row) {
    if (row != -1) {
        SetItemState8(m, row, 2);
        const int32_t arrow = m->m_i32FocusedArrow;
        // The original tests the arrow twice; nothing runs between the two tests.
        if (IsArrowActive(m, arrow) && m->m_i32FocusedItem == -1) m->SetArrowState(arrow, DisabledBit(m));
    }
    m->m_i32FocusedItem = row;
}

// The focus moved onto arrow pair `arrow` (SetInteractionState 3 / 4, Update): the item's visual state is the
// arrow's, the previous item (if in the list) back to state 0, no focused item, the arrow focused (2, or 3 while
// disabled).
void FocusArrow(Menu* m, int32_t arrow, int32_t previous) {
    m->m_ui8State = m->m_aui8ArrowState[arrow];
    m->m_i32FocusedArrow = arrow;
    if (InList(m, previous)) SetItemState8(m, previous, 0);
    const int32_t focused = m->m_i32FocusedArrow;
    m->m_i32FocusedItem = -1;
    if (IsArrowActive(m, focused)) m->SetArrowState(focused, DisabledBit(m) != 0 ? 3 : 2);
}

// The hot spot's 2D object entry of `node`, searched from the last (SetPosition inlines one search per
// coordinate); nothing when it is not attached. (CKInterfaceButtonDouble.cpp's copy.)
SAttached2dObject* FindAttached(IKSerializable* hotSpot, IKSerializable* node) {
    TVector<SAttached2dObject, 2>& objects = static_cast<CFlashHotSpot*>(hotSpot)->m_vp2dObject;
    for (uint32_t i = objects.m_ui32NbUsedElt; i-- != 0;) {
        if (static_cast<IKSerializable*>(objects.m_pBlock[i].m_pNode) == node) return &objects.m_pBlock[i];
    }
    return nullptr;
}
void SetAttachedOffset(IKSerializable* hotSpot, IKSerializable* node, float x, float y) {
    if (SAttached2dObject* entry = FindAttached(hotSpot, node)) entry->m_vPosOffset.m_fX = x;
    if (SAttached2dObject* entry = FindAttached(hotSpot, node)) entry->m_vPosOffset.m_fY = y;
}

// ArrowRecord::m_pEffect: a CParticlesNodeFx; the same two inlined blocks as the other buttons' state effects
// (CKInterfaceButtonDouble.cpp's copies). SetArrowState: below 64 points, the null vector (0x00c50d64) appended to the
// emitter's point list with property 0x2000; properties 0x200 | 0x400 set and 0x80000 cleared, the emission speed
// adjustment 0 (stw), the emitter's flags |= 0xa (ACTIVE | EMIT).
void StateEffect_Start(IKSerializable* effect) {
    if (effect == nullptr) return;
    static const RwV3d kNullVector = {0.0f, 0.0f, 0.0f};  // g_nullVector 0x00c50d64
    CParticlesNodeFx* fx = static_cast<CParticlesNodeFx*>(effect);
    if (fx->m_ui8NbActivePoints <= 0x3f) {
        fx->m_pAdvEmtPointList->pointList[fx->m_ui8NbActivePoints] = kNullVector;
        fx->m_sgProperties = (fx->m_sgProperties & ~0x2000u) | 0x2000u;
        fx->m_ui8NbActivePoints = static_cast<uint8_t>(fx->m_ui8NbActivePoints + 1);
    }
    uint32_t properties = fx->m_sgProperties;
    properties = (properties & ~0x200u) | 0x200u;
    properties = (properties & ~0x400u) | 0x400u;
    fx->m_sgProperties = properties & ~0x80000u;
    fx->m_fEmissionSpeedAdjustment = 0.0f;  // stw 0
    fx->m_pRpPrtStdEmitter->flag |= rpPRTSTDEMITTERFLAGACTIVE | rpPRTSTDEMITTERFLAGEMIT;
}
// Open: properties 0x80400 cleared (and 0xfff7fbff), the emitter's EMIT flag (8) cleared.
void StateEffect_Reset(IKSerializable* effect) {
    if (effect == nullptr) return;
    CParticlesNodeFx* fx = static_cast<CParticlesNodeFx*>(effect);
    fx->m_sgProperties &= 0xfff7fbffu;
    fx->m_pRpPrtStdEmitter->flag &= ~static_cast<uint32_t>(rpPRTSTDEMITTERFLAGEMIT);
}

// 0x00112bc0 CKSoundDictionaryID_GetSound (no bounds check), 0x00111b70 CKSound_ResetPan_maybe, 0x00111230 CKSound_Play.
CKSound* GetSound(IKSerializable* dictionary, uint32_t index) {
    return static_cast<CKSoundDictionaryID*>(dictionary)->GetSound(index);
}

// A copy of a record's colour (4 raw bytes), as the original copies the word to the stack for SetColor.
void SetNodeColor(IKSerializable* node, const uint8_t* raw) {
    uint8_t color[4];
    std::memcpy(color, raw, 4);
    static_cast<IKBillboard2d*>(AsBillboard(node))->SetColor(color);  // billboard part vt+0x28
}

// The focus moved back by one (Update, selection 0 / 2): from the first visible item onto arrow 0; from another
// item to the previous one; with nothing focused and arrow 1 focused, to the last visible item.
void MovePrevious(Menu* m) {
    const int32_t focused = m->m_i32FocusedItem;
    if (InList(m, focused)) {
        if (m->m_i32FirstVisible == focused) {
            if (IsArrowActive(m, 0)) FocusArrow(m, 0, focused);
        } else {
            SetItemState8(m, focused, 0);
            FocusItem(m, focused - 1);
        }
    } else if (IsArrowActive(m, m->m_i32FocusedArrow) && focused == -1 && m->m_i32FocusedArrow == 1) {
        FocusItem(m, m->m_i32LastVisible);
    }
    m->m_baFlags = static_cast<uint8_t>(m->m_baFlags | CKInterfaceButtonBase::kFlagFading);
}

// The focus moved on by one (Update, selection 1 / 3): from the last visible item onto arrow 1; from another item
// to the next one; with nothing focused and arrow 0 focused, to the first visible item.
void MoveNext(Menu* m) {
    const int32_t focused = m->m_i32FocusedItem;
    if (InList(m, focused)) {
        if (m->m_i32LastVisible != focused) {
            SetItemState8(m, focused, 0);
            FocusItem(m, focused + 1);
        } else if (IsArrowActive(m, 1)) {
            FocusArrow(m, 1, focused);
        }
    } else if (IsArrowActive(m, m->m_i32FocusedArrow) && focused == -1 && m->m_i32FocusedArrow == 0) {
        FocusItem(m, m->m_i32FirstVisible);
    }
    m->m_baFlags = static_cast<uint8_t>(m->m_baFlags | CKInterfaceButtonBase::kFlagFading);
}

}  // namespace

// 0x00526cf8 CKInterfaceScrollingMenu_Create (the constructor inlined; the same stores as 0x525a78 / 0x5257c8): the
// base, +0x5c..+0x8b = 0 (words), +0x8c..+0xbb = 0.0, the item list {0, 1, 0}, the scroll ramp 0.0. The rest is the
// fresh heap's zero (m_bFocused, the records, the arrow states, m_i32LastVisible are written by Load or the slots).
CKInterfaceScrollingMenu::CKInterfaceScrollingMenu()
    : m_bFocused(0),
      m_pad31{},
      m_apArrowNodes{},
      m_i32Axis(0),
      m_i32FocusedArrow(0),
      m_fListOffset(0.0f),
      m_afArrowOffsets{},
      m_fArrowAnimSpeed(0.0f),
      m_aArrowRecords{},
      m_aui8ArrowState{},
      m_pad186{},
      m_pSounds(nullptr),
      m_fFadeOutTime(0.0f),
      m_fFadeOutDuration(0.0f),
      m_i32FocusedItem(0),
      m_fItemFadeSpeed(0.0f),
      m_fItemSpacing(0.0f),
      m_i32NbVisibleItems(0),
      m_i32FirstVisible(0),
      m_i32LastVisible(0) {
    for (uint32_t a = 0; a < 2; ++a) {
        for (uint32_t n = 0; n < 2; ++n) {
            m_aArrowSizeX[a][n] = {0.0f, 0.0f, 0.0f};
            m_aArrowSizeY[a][n] = {0.0f, 0.0f, 0.0f};
        }
    }
    m_vItems.m_pBlock = nullptr;
    m_vItems.m_ui32NbElt = 1;
    m_vItems.m_ui32NbUsedElt = 0;
    m_scroll.m_fTarget = 0.0f;
    m_scroll.m_fCurrent = 0.0f;
    m_scroll.m_fSpeed = 0.0f;
}

// 0x00525be0 CKInterfaceScrollingMenu_Destructor (0x525948 the same body, 0x525b68 with the delete): the item block
// freed (the TVector's destructor), then the base's.
CKInterfaceScrollingMenu::~CKInterfaceScrollingMenu() {
    if (m_vItems.m_pBlock != nullptr) Mem_FreeAligned16(m_vItems.m_pBlock);
    m_vItems.m_ui32NbUsedElt = 0;
    m_vItems.m_pBlock = nullptr;
}

// 0x005255c0 CKInterfaceScrollingMenu_CallItemVf5C_maybe (the whole index here, unlike the inlined copies)
void CKInterfaceScrollingMenu::SetItemInteractionState(int32_t index, uint8_t state) {
    IKSerializable* item = m_vItems.m_pBlock[index];
    if (item != nullptr) AsItem(item)->SetInteractionState(state);  // vt+0x5c
}

// 0x005256d8 CKInterfaceScrollingMenu_RecursiveRegistration: the base's (0x67fe8) only; the arrows, the sounds and
// the items are not registered here.
void CKInterfaceScrollingMenu::RecursiveRegistration(int32_t type) { CKInterfaceButtonBase::RecursiveRegistration(type); }

// 0x00525700 CKInterfaceScrollingMenu_Destroy
void CKInterfaceScrollingMenu::Destroy() {
    CKInterfaceButtonBase::Destroy();  // 0x67ff0 (empty)
    for (ArrowRecord& r : m_aArrowRecords) {
        if (r.m_apTextures[0] != nullptr) TextureRef_Release(r.m_apTextures[0]);  // RwTextureDestroy
        if (r.m_apTextures[1] != nullptr) TextureRef_Release(r.m_apTextures[1]);
    }
    if (m_vItems.m_pBlock != nullptr) {
        Mem_FreeAligned16(m_vItems.m_pBlock);
        m_vItems.m_pBlock = nullptr;
    }
    m_vItems.m_ui32NbUsedElt = 0;
    m_vItems.m_pBlock = nullptr;
}

// 0x005259b8 CKInterfaceScrollingMenu_Close: the base's, every item closed, then Hide.
void CKInterfaceScrollingMenu::Close() {
    CKInterfaceButtonBase::Close();
    for (uint32_t i = 0; i < m_vItems.m_ui32NbUsedElt; ++i) AsItem(m_vItems.m_pBlock[i])->Close();  // vt+0x54
    Hide();  // vt+0x70
}

// 0x00525b58 CKInterfaceScrollingMenu_PostLoad
int32_t CKInterfaceScrollingMenu::PostLoad(int32_t /*type*/) {
    m_i32FocusedItem = -1;
    return 1;
}

// 0x00525c50 CKInterfaceScrollingMenu_RemoveItem_maybe: the first slot holding `item` (from the first); the capacity
// test is signed (blt).
void CKInterfaceScrollingMenu::RemoveItem(IKSerializable* item) {
    TVector<IKSerializable*, 1>& v = m_vItems;
    const uint32_t count = v.m_ui32NbUsedElt;
    if (count == 0) return;
    uint32_t index = 0;
    while (v.m_pBlock[index] != item) {
        if (++index == count) return;
    }
    const uint32_t last = count - 1;
    v.m_ui32NbUsedElt = last;
    if (last != index) v.m_pBlock[index] = v.m_pBlock[last];
    int32_t capacity = static_cast<int32_t>(v.m_ui32NbElt) - 1;
    if (capacity < static_cast<int32_t>(v.m_ui32NbUsedElt)) return;
    uint32_t size = static_cast<uint32_t>(capacity) * static_cast<uint32_t>(sizeof(IKSerializable*));
    if (capacity == 0) {
        size = static_cast<uint32_t>(sizeof(IKSerializable*));
        capacity = 1;
    }
    v.m_pBlock = static_cast<IKSerializable**>(Mem_ReallocAligned16(v.m_pBlock, size));
    v.m_ui32NbElt = static_cast<uint32_t>(capacity);
}

// 0x00525d90 CKInterfaceScrollingMenu_AddItem_maybe: grow by one when full (Mem_ReallocAligned16), then the push.
uint32_t CKInterfaceScrollingMenu::AddItem(IKSerializable* item) {
    TVector_GrowIfFull(m_vItems);
    m_vItems.m_pBlock[m_vItems.m_ui32NbUsedElt] = item;
    return m_vItems.m_ui32NbUsedElt++;
}

// 0x00525e78 CKInterfaceScrollingMenu_vf7C: up / left (0 / 2) belong to arrow 0 and the first visible item, down /
// right (1 / 3) to arrow 1 and the last. Without that arrow the neighbour is reached from the item at that end;
// with it, only from the arrow itself when it holds the focus.
uint8_t CKInterfaceScrollingMenu::GetNeighbor(int32_t dir) {
    int32_t arrow;
    int32_t edge;
    if (dir == 0 || dir == 2) {
        arrow = 0;
        edge = m_i32FirstVisible;
    } else if (dir == 1 || dir == 3) {
        arrow = 1;
        edge = m_i32LastVisible;
    } else {
        return 0xff;
    }
    if (!IsArrowActive(this, arrow)) return m_i32FocusedItem == edge ? m_aNeighbors[dir] : 0xff;
    const int32_t focused = m_i32FocusedArrow;
    if (IsArrowActive(this, focused) && m_i32FocusedItem == -1 && focused == arrow) return m_aNeighbors[dir];
    return 0xff;
}

// 0x005260c0 CKInterfaceScrollingMenu_UpdateVisibility_maybe: each arrow node's own colour with its alpha scaled by
// the fade (fctiwz of byte x fade, fmuls) set back (SetColor). `fadeIn` is not read. BUG(original): the colour is the
// node's current one, so every call scales the alpha again.
void CKInterfaceScrollingMenu::UpdateVisibility(uint8_t /*fadeIn*/) {
    for (uint32_t a = 0; a < 2; ++a) {
        for (uint32_t n = 0; n < 2; ++n) {
            IKSerializable* node = m_apArrowNodes[a][n];
            if (node == nullptr) continue;
            IKBillboard2d* billboard = static_cast<IKBillboard2d*>(AsBillboard(node));
            uint8_t color[4];
            std::memcpy(color, &billboard->m_Color, 4);
            color[3] = static_cast<uint8_t>(ppc::fctiwz(static_cast<float>(color[3]) * m_fFade));
            billboard->SetColor(color);  // billboard part vt+0x28
        }
    }
    if (m_fFadeTarget != m_fFade) m_baFlags = static_cast<uint8_t>(m_baFlags | kFlagFading);
}

// 0x00526250 CKInterfaceScrollingMenu_vf60: the position, then each arrow pair's two nodes at the position moved
// along the axis by m_fListOffset + the pair's offset (negated on the x axis), as offsets in the base's hot spot
// (+0x2c, a CFlashHotSpot). The original indexes the stack vector by m_i32Axis (only 0 / 1 stay inside it).
void CKInterfaceScrollingMenu::SetPosition(const CVector2& position) {
    m_vPosition = position;
    for (uint32_t a = 0; a < 2; ++a) {
        float local[2] = {position.m_fX, position.m_fY};
        float offset = m_fListOffset + m_afArrowOffsets[a];
        if (m_i32Axis == 0) offset = -offset;
        local[m_i32Axis] = offset + local[m_i32Axis];
        for (uint32_t n = 0; n < 2; ++n) {
            IKSerializable* node = m_apArrowNodes[a][n];
            if (node != nullptr) SetAttachedOffset(m_unk2c, node, local[0], local[1]);
        }
    }
}

namespace {

// The "resize to count" of the item list (Load): a new one-element block (the old one is not freed), grown to
// count + 1 elements when the count is larger, then the count. (CKInterfaceButton.cpp's LoadReserve.)
void LoadReserve(TVector<IKSerializable*, 1>& v, uint32_t count) {
    v.m_ui32NbElt = 1;
    v.m_pBlock = static_cast<IKSerializable**>(Mem_AllocAligned16(static_cast<uint32_t>(sizeof(IKSerializable*))));
    if (v.m_ui32NbElt < count) {
        uint32_t capacity = count + 1;
        uint32_t size = capacity * static_cast<uint32_t>(sizeof(IKSerializable*));
        if (capacity == 0) {
            capacity = 1;
            size = static_cast<uint32_t>(sizeof(IKSerializable*));
        }
        v.m_pBlock = static_cast<IKSerializable**>(Mem_ReallocAligned16(v.m_pBlock, size));
        v.m_ui32NbElt = capacity;
    }
    v.m_ui32NbUsedElt = count;
}

}  // namespace

// 0x005263c0 CKInterfaceScrollingMenu_Load: the base's, then (K_LEVEL_PLATEFORMS only) the arrows, the layout, the
// five records (from the first), the sounds, the fade-out duration, the item list (one reference array), the item
// fade speed, the scroll speed, the spacing and the visible count. Each vector is one read, every word swapped.
int32_t CKInterfaceScrollingMenu::Load(IKFile* file, int32_t type) {
    CKInterfaceButtonBase::Load(file, type);
    if (type != K_LEVEL_PLATEFORMS) return 1;
    IKFile_ReadObjectRefArray(file, m_apArrowNodes[0], 2);
    IKFile_ReadObjectRefArray(file, m_apArrowNodes[1], 2);
    ReadS32LE(file, &m_i32Axis);
    m_i32FocusedArrow = 0;
    ReadF32LE(file, &m_fListOffset);
    ReadF32LE(file, &m_afArrowOffsets[0]);
    ReadF32LE(file, &m_afArrowOffsets[1]);
    ReadF32LE(file, &m_fArrowAnimSpeed);
    for (ArrowRecord& r : m_aArrowRecords) {
        for (float& f : r.m_afSizes) ReadF32LE(file, &f);
        ReadRaw(file, r.m_aui8Blend, 2);
        ReadRaw(file, r.m_aColors, 8);
        IKFile_ReadTextureRef(file, &r.m_apTextures[0], 1);
        IKFile_ReadTextureRef(file, &r.m_apTextures[1], 1);
        IKFile_ReadRef(file, &r.m_pEffect);
    }
    IKFile_ReadRef(file, &m_pSounds);
    ReadF32LE(file, &m_fFadeOutDuration);
    uint32_t count = 0;
    ReadU32LE(file, &count);
    LoadReserve(m_vItems, count);
    IKFile_ReadObjectRefArray(file, m_vItems.m_pBlock, count);
    ReadF32LE(file, &m_fItemFadeSpeed);
    ReadF32LE(file, &m_scroll.m_fSpeed);
    ReadF32LE(file, &m_fItemSpacing);
    ReadS32LE(file, &m_i32NbVisibleItems);
    m_i32FirstVisible = 0;
    return 1;
}

// 0x00526a78 CKInterfaceScrollingMenu_UpdateItemLayout_maybe: the scroll target = ((visible - 1) x 0.5 + first) x
// spacing + list offset (the counts as unsigned words through fcfid; fmuls, fadds, fmadds), negated on the x axis;
// the current position too unless `animate`. Then from the current position each item along the axis (+spacing
// on x, -spacing on y): the visible ones fade to 1, the others are unfocused (state 0) and fade to 0.
void CKInterfaceScrollingMenu::UpdateItemLayout(uint8_t animate, uint8_t fadeIn) {
    float local[2] = {0.0f, 0.0f};
    const float first = static_cast<float>(static_cast<uint32_t>(m_i32FirstVisible));
    float target = static_cast<float>(static_cast<uint32_t>(m_i32NbVisibleItems - 1));
    target = target * 0x1p-1f;  // TOC +0x77e0 (0x3f000000)
    target = target + first;
    target = ppc::fmadds(target, m_fItemSpacing, m_fListOffset);
    if (m_i32Axis == 0) target = -target;
    m_scroll.m_fTarget = target;
    if (animate == 0) m_scroll.m_fCurrent = target;
    float p = m_scroll.m_fCurrent;
    for (uint32_t i = 0; i < m_vItems.m_ui32NbUsedElt; ++i) {
        CKInterfaceButtonBase* item = AsItem(m_vItems.m_pBlock[i]);
        if (static_cast<uint32_t>(m_i32FirstVisible) > i || static_cast<uint32_t>(m_i32LastVisible) < i) {
            SetItemState8(this, static_cast<int32_t>(i), 0);
            item->StartFade(0.0f, m_fItemFadeSpeed, fadeIn);
        } else {
            item->StartFade(0x1p+0f, m_fItemFadeSpeed, fadeIn);  // TOC +0x77e4
        }
        local[m_i32Axis] = p;  // the stack vector indexed by the word (only 0 / 1 stay inside it)
        const CVector2 position = {local[0], local[1]};
        item->SetPosition(position);  // vt+0x60
        if (m_i32Axis == 0)
            p = p + m_fItemSpacing;
        else
            p = p - m_fItemSpacing;
    }
    if (m_scroll.m_fTarget != m_scroll.m_fCurrent) m_baFlags = static_cast<uint8_t>(m_baFlags | kFlagFading);
}

// 0x00526f48 CKInterfaceScrollingMenu_HideScrollArrow_maybe
void CKInterfaceScrollingMenu::HideScrollArrow(int32_t arrow, uint8_t animate) {
    const int32_t focused = m_i32FocusedArrow;
    if (IsArrowActive(this, focused) && m_i32FocusedItem == -1 && arrow == focused) {
        if (arrow == 0)
            FocusItem(this, m_i32FirstVisible);
        else if (arrow == 1)
            FocusItem(this, m_i32LastVisible);
    }
    if (animate == 0) {
        for (uint32_t n = 0; n < 2; ++n) {
            IKSerializable* node = m_apArrowNodes[arrow][n];
            if (node == nullptr) continue;
            SetBillboardSize(node, kZeroVector2);  // billboard part vt+0x30
            AsNode(node)->Disable();               // vt+0x68
        }
        return;
    }
    if (m_apArrowNodes[arrow][0] != nullptr) {
        m_aArrowSizeX[arrow][0].m_fTarget = 0.0f;  // stw 0
        m_aArrowSizeY[arrow][0].m_fTarget = 0.0f;
    }
    if (m_apArrowNodes[arrow][1] != nullptr) {
        m_aArrowSizeX[arrow][1].m_fTarget = 0.0f;
        m_aArrowSizeY[arrow][1].m_fTarget = 0.0f;
    }
    m_baFlags = static_cast<uint8_t>(m_baFlags | kFlagFading);
}

// 0x00527498 CKInterfaceScrollingMenu_SetSelectedRow_maybe: the first visible item `first` clamped to [0, count - 1]
// (signed); the last = first + visible - 1 from the unclamped argument, clamped the same way; arrow 0 hidden at the
// top, arrow 1 at the bottom (animated), else shown; a focused item kept between them (unsigned compares).
void CKInterfaceScrollingMenu::SetFirstVisible(int32_t first) {
    const int32_t last = static_cast<int32_t>(m_vItems.m_ui32NbUsedElt) - 1;
    int32_t clamped = 0;
    if (first > 0) {
        clamped = first;
        if (first > last) clamped = last;
    }
    m_i32FirstVisible = clamped;
    int32_t end = first + m_i32NbVisibleItems - 1;
    if (end <= 0) {
        end = 0;
    } else if (last <= end) {
        end = last < 0 ? 0 : last;
    }
    m_i32LastVisible = end;
    if (m_i32FirstVisible == 0)
        HideScrollArrow(0, 1);
    else
        ShowScrollArrow(0, 1);
    if (m_i32LastVisible == last)
        HideScrollArrow(1, 1);
    else
        ShowScrollArrow(1, 1);
    if (m_i32FocusedItem != -1) {
        const uint32_t focused = static_cast<uint32_t>(m_i32FocusedItem);
        const uint32_t top = static_cast<uint32_t>(m_i32FirstVisible);
        const uint32_t bottom = static_cast<uint32_t>(m_i32LastVisible);
        uint32_t kept = top;
        if (top < focused) kept = focused > bottom ? bottom : focused;
        m_i32FocusedItem = static_cast<int32_t>(kept);
    }
    UpdateItemLayout(1, 0);
}

// 0x005276d0 CKInterfaceScrollingMenu_SetColumnSelection_maybe: nothing when the pair is in that state already. The
// node 0 ramps go to the record's sizes, X at m_fArrowAnimSpeed and Y at a speed that arrives with it (speed x
// |dy / dx|, fdivs, the sign cleared, fmuls; the plain speed when dx is 0); node 1's ramps use node 0's dx too.
// Then (the updated bit set) the state's sound, the state's effect, and in state 4 the list scrolled towards the
// focused arrow.
void CKInterfaceScrollingMenu::SetArrowState(int32_t arrow, uint8_t state) {
    if (m_aui8ArrowState[arrow] == state) return;
    m_aui8ArrowState[arrow] = state;
    m_baFlags = static_cast<uint8_t>(m_baFlags | kFlagFading);
    const ArrowRecord& r = m_aArrowRecords[state];
    Ramp& x0 = m_aArrowSizeX[arrow][0];
    Ramp& y0 = m_aArrowSizeY[arrow][0];
    Ramp& x1 = m_aArrowSizeX[arrow][1];
    Ramp& y1 = m_aArrowSizeY[arrow][1];
    const float dx = r.m_afSizes[0] - x0.m_fTarget;
    x0.m_fSpeed = m_fArrowAnimSpeed;
    float speed = m_fArrowAnimSpeed;
    if (dx != 0.0f) speed = m_fArrowAnimSpeed * std::fabs((r.m_afSizes[1] - y0.m_fTarget) / dx);
    y0.m_fSpeed = speed;
    x0.m_fTarget = r.m_afSizes[0];
    y0.m_fTarget = r.m_afSizes[1];
    // BUG(original): both node tests read pair 0's nodes (+0x34 / +0x38) whatever the pair.
    if (m_apArrowNodes[0][0] != nullptr) {
        IKSerializable* node = m_apArrowNodes[arrow][0];
        if (r.m_apTextures[0] != nullptr) {
            static_cast<IKBillboard2d*>(AsBillboard(node))->SetTexture(static_cast<RwTexture*>(r.m_apTextures[0]));  // vt+0x3c
        }
        SetNodeColor(node, &r.m_aColors[0]);
        static_cast<IKBillboard2d*>(AsBillboard(m_apArrowNodes[arrow][0]))->m_bUseAlpha = r.m_aui8Blend[0];
    }
    if (dx == 0.0f) {
        x1.m_fSpeed = m_fArrowAnimSpeed;
        speed = m_fArrowAnimSpeed;
    } else {
        x1.m_fSpeed = m_fArrowAnimSpeed * std::fabs((r.m_afSizes[2] - x1.m_fTarget) / dx);
        speed = m_fArrowAnimSpeed * std::fabs((r.m_afSizes[3] - y1.m_fTarget) / dx);
    }
    y1.m_fSpeed = speed;
    x1.m_fTarget = r.m_afSizes[2];
    y1.m_fTarget = r.m_afSizes[3];
    if (m_apArrowNodes[0][1] != nullptr) {
        IKSerializable* node = m_apArrowNodes[arrow][1];
        if (r.m_apTextures[1] != nullptr) {
            static_cast<IKBillboard2d*>(AsBillboard(node))->SetTexture(static_cast<RwTexture*>(r.m_apTextures[1]));  // vt+0x3c
        }
        SetNodeColor(node, &r.m_aColors[4]);
        static_cast<IKBillboard2d*>(AsBillboard(m_apArrowNodes[arrow][1]))->m_bUseAlpha = r.m_aui8Blend[1];
    }
    if ((m_baFlags & kFlagUpdated) != 0) {
        int32_t sound = -1;
        if (state == 3)
            sound = 1;
        else if (state == 4)
            sound = 2;
        else if (state == 2)
            sound = 0;
        if (sound >= 0 && GetSound(m_pSounds, static_cast<uint32_t>(sound)) != nullptr) {
            GetSound(m_pSounds, static_cast<uint32_t>(sound))->ResetPan(1);
            GetSound(m_pSounds, static_cast<uint32_t>(sound))->Play(0.0f);
        }
    }
    StateEffect_Start(r.m_pEffect);
    if (state == 4) {
        const int32_t focused = m_i32FocusedArrow;
        if (IsArrowActive(this, focused) && m_i32FocusedItem == -1) {
            if (focused == 0)
                SetFirstVisible(m_i32FirstVisible - 1);
            else if (focused == 1)
                SetFirstVisible(m_i32FirstVisible + 1);
        }
    }
}

// 0x00527e48 CKInterfaceScrollingMenu_vf84: the disabled bit when it changes; each arrow's state follows it (0 / 1
// -> 1 or 0, 2 / 3 -> 3 or 2, 4 -> 3 or 4; above 4 untouched), then every item's SetDisabled.
void CKInterfaceScrollingMenu::SetDisabled(uint8_t disabled) {
    if (disabled == DisabledBit(this)) return;
    m_baFlags = static_cast<uint8_t>((m_baFlags & ~kFlagDisabled) | static_cast<uint8_t>(disabled << 1));
    for (int32_t a = 0; a < 2; ++a) {
        const uint8_t s = m_aui8ArrowState[a];
        if (s > 4) continue;
        const bool off = (m_baFlags & kFlagDisabled) != 0;
        if (s <= 1)
            SetArrowState(a, off ? 1 : 0);
        else if (s <= 3)
            SetArrowState(a, off ? 3 : 2);
        else
            SetArrowState(a, off ? 3 : 4);
    }
    for (uint32_t i = 0; i < m_vItems.m_ui32NbUsedElt; ++i) AsItem(m_vItems.m_pBlock[i])->SetDisabled(disabled);  // vt+0x84
}

// 0x005280b8 CKInterfaceScrollingMenu_ShowScrollArrow_maybe. Animated: the pair's state from the disabled bit (not
// for kArrowNone; the callers pass 0 / 1), then each node enabled with its ramps' targets from the state's record.
void CKInterfaceScrollingMenu::ShowScrollArrow(int32_t arrow, uint8_t animate) {
    if (animate == 0) {
        if (m_apArrowNodes[arrow][0] != nullptr) AsNode(m_apArrowNodes[arrow][0])->Enable();  // vt+0x64
        if (m_apArrowNodes[arrow][1] != nullptr) AsNode(m_apArrowNodes[arrow][1])->Enable();
        return;
    }
    if (arrow != kArrowNone) SetArrowState(arrow, DisabledBit(this));
    const ArrowRecord& r = m_aArrowRecords[m_aui8ArrowState[arrow]];
    if (m_apArrowNodes[arrow][0] != nullptr) {
        AsNode(m_apArrowNodes[arrow][0])->Enable();
        m_aArrowSizeX[arrow][0].m_fTarget = r.m_afSizes[0];
        m_aArrowSizeY[arrow][0].m_fTarget = r.m_afSizes[1];
    }
    if (m_apArrowNodes[arrow][1] != nullptr) {
        AsNode(m_apArrowNodes[arrow][1])->Enable();
        m_aArrowSizeX[arrow][1].m_fTarget = r.m_afSizes[2];
        m_aArrowSizeY[arrow][1].m_fTarget = r.m_afSizes[3];
    }
    m_baFlags = static_cast<uint8_t>(m_baFlags | kFlagFading);
}

// 0x00528370 CKInterfaceScrollingMenu_Show: the shown bit, both arrows enabled, every item shown, then the first
// visible item set again (tail call).
void CKInterfaceScrollingMenu::Show() {
    m_baFlags = static_cast<uint8_t>(m_baFlags | kFlagShown);
    ShowScrollArrow(0, 0);
    ShowScrollArrow(1, 0);
    for (uint32_t i = 0; i < m_vItems.m_ui32NbUsedElt; ++i) AsItem(m_vItems.m_pBlock[i])->Show();  // vt+0x6c
    SetFirstVisible(m_i32FirstVisible);
}

// 0x00528448 CKInterfaceScrollingMenu_Hide: the shown bit cleared, both arrows hidden at once, every item hidden.
void CKInterfaceScrollingMenu::Hide() {
    m_baFlags = static_cast<uint8_t>(m_baFlags & ~kFlagShown);
    HideScrollArrow(0, 0);
    HideScrollArrow(1, 0);
    for (uint32_t i = 0; i < m_vItems.m_ui32NbUsedElt; ++i) AsItem(m_vItems.m_pBlock[i])->Hide();  // vt+0x70
}

// 0x00528508 CKInterfaceScrollingMenu_Open: no focused item, the menu's vt+0xec(this), the base's Open, the fade-out
// timer, the arrow ramps reset ({0, m_fArrowAnimSpeed, 0}) and both arrows to state 0 (from 0xff), the records'
// effects reset, every item given the fade-out duration (vt+0x8c) and opened (vt+0x50 with 0), the first visible
// item and the layout set at once; the focus to the first visible item, then SetInteractionState(2) when `focused`.
void CKInterfaceScrollingMenu::Open(uint8_t focused) {
    m_i32FocusedItem = -1;
    static_cast<CKMenuBase114c*>(m_pMenu)->VfEC(this);  // vt+0xec(menu, this)
    CKInterfaceButtonBase::Open(focused);
    m_fFadeOutTime = m_fFadeOutDuration;
    m_ui8State = 0xff;
    for (int32_t a = 0; a < 2; ++a) {
        m_aui8ArrowState[a] = 0xff;
        m_aArrowSizeX[a][0].m_fCurrent = 0.0f;
        m_aArrowSizeX[a][0].m_fSpeed = m_fArrowAnimSpeed;
        m_aArrowSizeX[a][0].m_fTarget = 0.0f;
        m_aArrowSizeY[a][0].m_fCurrent = 0.0f;
        m_aArrowSizeY[a][0].m_fSpeed = m_fArrowAnimSpeed;
        m_aArrowSizeY[a][0].m_fTarget = 0.0f;
        m_aArrowSizeX[a][1].m_fCurrent = 0.0f;
        m_aArrowSizeX[a][1].m_fTarget = 0.0f;
        m_aArrowSizeX[a][1].m_fSpeed = m_fArrowAnimSpeed;
        m_aArrowSizeY[a][1].m_fCurrent = 0.0f;
        m_aArrowSizeY[a][1].m_fSpeed = m_fArrowAnimSpeed;
        m_aArrowSizeY[a][1].m_fTarget = 0.0f;
        SetArrowState(a, 0);
    }
    m_ui8State = 0;
    for (ArrowRecord& r : m_aArrowRecords) StateEffect_Reset(r.m_pEffect);
    for (uint32_t i = 0; i < m_vItems.m_ui32NbUsedElt; ++i) {
        AsItem(m_vItems.m_pBlock[i])->Vf8C(m_fFadeOutDuration);  // vt+0x8c
        AsItem(m_vItems.m_pBlock[i])->Open(0);                   // vt+0x50
    }
    SetFirstVisible(m_i32FirstVisible);
    UpdateItemLayout(0, 1);
    const int32_t previous = m_i32FocusedItem;
    const int32_t first = m_i32FirstVisible;
    if (InList(this, previous) && first != previous) SetItemState8(this, previous, 0);
    FocusItem(this, first);
    if (focused != 0) SetInteractionState(2);  // vt+0x5c
}

// 0x00528ab8 CKInterfaceScrollingMenu_vf5C (jump table 0x528b08; above 4 nothing). 0 normal: the focused arrow back
// to its plain state, else the focused item to 0. 1 validated: the focused arrow to 4 (3 while disabled), else the
// focused item to 1. 2 focused: the focused arrow to 2 (3), else the focused item to 2, else the focus to the first
// visible item. 3 / 4 next / previous: the focus onto arrow 1 / 0 when it is active (another focused arrow back to its
// plain state first), else to the last / first visible item; both end with the fading bit.
void CKInterfaceScrollingMenu::SetInteractionState(int32_t state) {
    if (static_cast<uint32_t>(state) > 4) return;
    const int32_t arrow = m_i32FocusedArrow;
    switch (state) {
    case 0:
        if (IsArrowActive(this, arrow) && m_i32FocusedItem == -1) {
            SetArrowState(arrow, DisabledBit(this));
        } else if (InList(this, m_i32FocusedItem)) {
            SetItemState8(this, m_i32FocusedItem, 0);
        }
        m_bFocused = 0;
        return;
    case 1:
        if (IsArrowActive(this, arrow) && m_i32FocusedItem == -1) {
            SetArrowState(arrow, DisabledBit(this) != 0 ? 3 : 4);
            return;
        }
        if (InList(this, m_i32FocusedItem)) SetItemState8(this, m_i32FocusedItem, 1);
        return;
    case 2:
        m_bFocused = 1;
        if (IsArrowActive(this, arrow) && m_i32FocusedItem == -1) {
            SetArrowState(arrow, DisabledBit(this) != 0 ? 3 : 2);
            return;
        }
        if (InList(this, m_i32FocusedItem)) {
            SetItemState8(this, m_i32FocusedItem, 2);
            return;
        }
        FocusItem(this, m_i32FirstVisible);
        return;
    default: {
        // 3: arrow 1 and the last visible item; 4: arrow 0 and the first.
        const int32_t target = state == 3 ? 1 : 0;
        m_bFocused = 1;
        static_cast<CKMenuBase114c*>(m_pMenu)->SetSelectionOfFirstActivePlayer(0xff);
        if (IsArrowActive(this, target)) {
            const int32_t focused = m_i32FocusedArrow;
            if (IsArrowActive(this, focused) && m_i32FocusedItem == -1 && focused != target) {
                SetArrowState(focused, DisabledBit(this));
            }
            FocusArrow(this, target, m_i32FocusedItem);
        } else {
            const int32_t row = state == 3 ? m_i32LastVisible : m_i32FirstVisible;
            const int32_t previous = m_i32FocusedItem;
            if (InList(this, previous) && row != previous) SetItemState8(this, previous, 0);
            FocusItem(this, row);
        }
        m_baFlags = static_cast<uint8_t>(m_baFlags | kFlagFading);
        return;
    }
    }
}

// 0x005296e8 CKInterfaceScrollingMenu_Update: the updated bit; while focused, the focus moved by the first active
// player's selection; every item updated. While fading: the arrow sizes stepped (pair 0 then pair 1, node by node;
// a node whose ramps arrived at size (0, 0) is disabled) or, while the fade-out timer runs (or is NaN), the focused
// pair's nodes held at their current sizes; then the fade, the colours, the scroll position and the layout; the
// fade-out timer runs down.
void CKInterfaceScrollingMenu::Update(IKTime* frameClock) {
    m_baFlags = static_cast<uint8_t>(m_baFlags | kFlagUpdated);
    if (m_bFocused != 0) {
        const uint8_t selection = static_cast<CKMenuBase114c*>(m_pMenu)->GetSelectionOfFirstActivePlayer();
        if (selection == 0 || selection == 2)
            MovePrevious(this);
        else if (selection == 1 || selection == 3)
            MoveNext(this);
    }
    for (uint32_t i = 0; i < m_vItems.m_ui32NbUsedElt; ++i) AsItem(m_vItems.m_pBlock[i])->Update(frameClock);  // vt+0x58
    if ((m_baFlags & kFlagFading) == 0) return;
    m_baFlags = static_cast<uint8_t>(m_baFlags & ~kFlagFading);
    for (uint32_t n = 0; n < 2; ++n) {
        if (m_fFadeOutTime <= 0.0f) {
            CVector2 size;
            size.m_fX = FloatApproach_Step(DeltaTime(frameClock), &m_aArrowSizeX[0][n].m_fTarget);
            size.m_fY = FloatApproach_Step(DeltaTime(frameClock), &m_aArrowSizeY[0][n].m_fTarget);
            IKSerializable* node = m_apArrowNodes[0][n];
            SetBillboardSize(node, size);  // no null test
            if (m_aArrowSizeX[0][n].m_fCurrent != m_aArrowSizeX[0][n].m_fTarget ||
                m_aArrowSizeY[0][n].m_fCurrent != m_aArrowSizeY[0][n].m_fTarget) {
                m_baFlags = static_cast<uint8_t>(m_baFlags | kFlagFading);
            } else if (size.m_fX == kZeroVector2.m_fX && size.m_fY == kZeroVector2.m_fY) {
                AsNode(node)->Disable();  // vt+0x68
            }
            size.m_fX = FloatApproach_Step(DeltaTime(frameClock), &m_aArrowSizeX[1][n].m_fTarget);
            size.m_fY = FloatApproach_Step(DeltaTime(frameClock), &m_aArrowSizeY[1][n].m_fTarget);
            node = m_apArrowNodes[1][n];
            SetBillboardSize(node, size);
            if (m_aArrowSizeX[1][n].m_fCurrent != m_aArrowSizeX[1][n].m_fTarget ||
                m_aArrowSizeY[1][n].m_fCurrent != m_aArrowSizeY[1][n].m_fTarget) {
                m_baFlags = static_cast<uint8_t>(m_baFlags | kFlagFading);
            } else if (size.m_fX == kZeroVector2.m_fX && size.m_fY == kZeroVector2.m_fY) {
                AsNode(node)->Disable();
            }
        } else {
            const int32_t focused = m_i32FocusedArrow;
            const CVector2 size = {m_aArrowSizeX[focused][n].m_fCurrent, m_aArrowSizeY[focused][n].m_fCurrent};
            SetBillboardSize(m_apArrowNodes[focused][n], size);
            m_baFlags = static_cast<uint8_t>(m_baFlags | kFlagFading);
        }
    }
    FloatApproach_Step(DeltaTime(frameClock), &m_fFadeTarget);
    UpdateVisibility(0);  // vt+0x68
    FloatApproach_Step(DeltaTime(frameClock), &m_scroll.m_fTarget);
    UpdateItemLayout(1, 0);
    if (m_fFadeOutTime > 0.0f) m_fFadeOutTime = m_fFadeOutTime - DeltaTime(frameClock);
}
