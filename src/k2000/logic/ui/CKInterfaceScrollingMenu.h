// CKInterfaceScrollingMenu.h - a menu item holding a scrolling list of other items (key 0x638c, vtable 0xb2b890,
// size 0x1c4): the list (m_vItems, CKInterfaceButtonBase references) shows m_i32NbVisibleItems at a time, from
// m_i32FirstVisible to m_i32LastVisible, laid out along m_i32Axis, with an arrow pair at each end (m_apArrowNodes:
// [0] towards the first item, [1] towards the last; each pair two CBillboard2d references) that scrolls the list by
// one when validated. Original unit: CKInterfaceScrollingMenu.cpp (0x5255c0-0x52a150). DotD only: no XXL2 class of
// this name, so the member names are descriptive. Base: CKInterfaceButtonBase (0x63cc). No front-end or level file
// holds one (F05 / R07 reports); the layout is from the constructor (0x525a78), Load (0x5263c0) and the users.
//
// The focus is either an item of the list (m_i32FocusedItem, -1 none) or an arrow (m_i32FocusedArrow 0 / 1, 2 none,
// with m_i32FocusedItem -1). The menu drives the whole item through SetInteractionState (vt+0x5c): 0 normal,
// 1 validated (passed to the focused item, or the focused arrow's state 4), 2 focused, 3 next (focus to the next
// visible item, or onto arrow 1 at the last one), 4 previous (focus to the previous item, or onto arrow 0). Update
// also moves the focus by the selection of the first active player (KBase730C_GetSelectionOfFirstActivePlayer:
// 0 / 2 previous, 1 / 3 next) while m_bFocused.
//
// An arrow's visual state (m_aui8ArrowState, SetArrowState) indexes m_aArrowRecords: 0 normal, 1 disabled, 2 focused,
// 3 focused while disabled_maybe, 4 validated (scrolls by one). Its two nodes' sizes animate through the ramps
// m_aArrowSizeX / m_aArrowSizeY ([pair][node], FloatApproach) towards the record's sizes; hidden arrows go to size 0.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/math/CVector2.h"
#include "k2000/misc/CKInterfaceButtonBase.h"
#include "k2000/util/TVector.h"

class IKTime;

class CKInterfaceScrollingMenu : public CKInterfaceButtonBase {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x18e)  // vt+0x14 / +0x18  0x9c84a0 / 0x9c84a8
    // 0x005252f8 CKInterfaceScrollingMenu_Delete, 0x00526cf8 _Create, 0x00526de8 _CreateArray, 0x005258a8 _DeleteArray
    DOTD_DECLARE_FACTORIES(CKInterfaceScrollingMenu)

    // +0xbc, five 0x28-byte records (read from the first up), one per arrow visual state.
    struct ArrowRecord {
        uint8_t m_aui8Blend[2];      // +0x00 the two nodes' blend (IKBillboard2d::m_bUseAlpha); read raw after +0x04 (+0x02..+0x03: padding)
        uint8_t m_pad02[2];
        float m_afSizes[4];          // +0x04 [0..1] node 0's size, [2..3] node 1's (the ramps' targets); one 16-byte read, swapped
        void* m_apTextures[2];       // +0x14 the two nodes' textures (resolved; [0] read first)
        uint8_t m_aColors[8];        // +0x1c [0..3] node 0's colour, [4..7] node 1's (RGBA); read raw
        // +0x24 a reference: an effect started on entering the state (a CParticlesNodeFx, the same blocks as the
        // other buttons' state effects), reset by Open.
        IKSerializable* m_pEffect;
    };
    // A FloatApproach ramp (k2000/misc/FloatApproach.h): the current value moves to the target at the speed.
    struct Ramp {
        float m_fTarget;
        float m_fSpeed;
        float m_fCurrent;
    };
    enum : int32_t { kArrowNone = 2 };  // m_i32FocusedArrow

    CKInterfaceScrollingMenu();            // inlined in 0x00526cf8 CKInterfaceScrollingMenu_Create (copies 0x525a78, 0x5257c8)
    ~CKInterfaceScrollingMenu() override;  // 0x00525be0 CKInterfaceScrollingMenu_Destructor
    int32_t IsKindOfClass(uint32_t key) override {  // vt+0x08 0x9c8478
        return key == 0x638c || key == 0x63cc || key == 0xc;
    }
    // vt+0x10 0x00525700 CKInterfaceScrollingMenu_Destroy: the base's (empty), the records' textures released, the
    // item block freed.
    void Destroy() override;
    // vt+0x24 0x005256d8 CKInterfaceScrollingMenu_RecursiveRegistration: the base's only (returns 1).
    void RecursiveRegistration(int32_t type) override;
    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x005263c0 CKInterfaceScrollingMenu_Load
    int32_t PostLoad(int32_t type) override;            // vt+0x30 0x00525b58 CKInterfaceScrollingMenu_PostLoad

    // The button slots (CKInterfaceButtonBase.h).
    void Open(uint8_t focused) override;                  // vt+0x50 0x00528508 CKInterfaceScrollingMenu_Open
    void Close() override;                                // vt+0x54 0x005259b8 CKInterfaceScrollingMenu_Close
    void Update(IKTime* frameClock) override;             // vt+0x58 0x005296e8 CKInterfaceScrollingMenu_Update
    void SetInteractionState(int32_t state) override;     // vt+0x5c 0x00528ab8 CKInterfaceScrollingMenu_vf5C
    void SetPosition(const CVector2& position) override;  // vt+0x60 0x00526250 CKInterfaceScrollingMenu_vf60
    void UpdateVisibility(uint8_t fadeIn) override;       // vt+0x68 0x005260c0 CKInterfaceScrollingMenu_UpdateVisibility_maybe
    void Show() override;                                 // vt+0x6c 0x00528370 CKInterfaceScrollingMenu_Show
    void Hide() override;                                 // vt+0x70 0x00528448 CKInterfaceScrollingMenu_Hide
    // vt+0x74 0x998518: the base's StartFadeOut (empty).
    // vt+0x78 0x9c84b0 (lfs TOC +0x77ac = 0.0; cror lt|eq: NaN gives 0)
    uint8_t IsFadeOutFinished() override { return m_fFadeOutTime <= 0.0f ? 1 : 0; }
    uint8_t GetNeighbor(int32_t dir) override;            // vt+0x7c 0x00525e78 CKInterfaceScrollingMenu_vf7C
    void SetDisabled(uint8_t disabled) override;          // vt+0x84 0x00527e48 CKInterfaceScrollingMenu_vf84
    float Vf88() override { return m_fFadeOutDuration; }             // vt+0x88 0x9c84d8
    void Vf8C(float value) override { m_fFadeOutDuration = value; }  // vt+0x8c 0x9c84e0

    // 0x005255c0 CKInterfaceScrollingMenu_CallItemVf5C_maybe: item `index`'s SetInteractionState(state) when there is
    // one (KBase730C_MoveFocusByInput_maybe 0x516de0 calls it).
    void SetItemInteractionState(int32_t index, uint8_t state);
    // 0x00525c50 CKInterfaceScrollingMenu_RemoveItem_maybe: the item swapped with the last and the list shrunk by one,
    // the block reallocated one element smaller when the capacity allows. No caller in the original.
    void RemoveItem(IKSerializable* item);
    // 0x00525d90 CKInterfaceScrollingMenu_AddItem_maybe: appended (grow by one); returns the index. No caller in the
    // original.
    uint32_t AddItem(IKSerializable* item);
    // 0x00526a78 CKInterfaceScrollingMenu_UpdateItemLayout_maybe: the scroll target from the first visible item (snapped
    // too unless `animate`), each item faded in (visible) or out (the others, unfocused first) and placed along the axis.
    void UpdateItemLayout(uint8_t animate, uint8_t fadeIn);
    // 0x00526f48 CKInterfaceScrollingMenu_HideScrollArrow_maybe: arrow pair `arrow` hidden (animated: the size targets
    // 0; else size 0 and disabled at once); a focused arrow hands the focus to the visible item at its end first.
    void HideScrollArrow(int32_t arrow, uint8_t animate);
    // 0x00527498 CKInterfaceScrollingMenu_SetSelectedRow_maybe: the first visible item (clamped to the list), the last
    // from it, the end arrows hidden / shown, the focused item kept in view, then the layout animated.
    void SetFirstVisible(int32_t first);
    // 0x005276d0 CKInterfaceScrollingMenu_SetColumnSelection_maybe: arrow pair `arrow`'s visual state: the record's sizes
    // as the ramp targets, textures, colours and blends, the state's sound and effect; state 4 scrolls by one.
    void SetArrowState(int32_t arrow, uint8_t state);
    // 0x005280b8 CKInterfaceScrollingMenu_ShowScrollArrow_maybe: arrow pair `arrow` enabled (animated: its state from
    // the disabled bit and the size targets from its record).
    void ShowScrollArrow(int32_t arrow, uint8_t animate);

    uint8_t m_bFocused;                   // +0x30 states 2..4 set 1, state 0 clears it; Update moves the focus while set (+0x31..+0x33: padding)
    uint8_t m_pad31[3];
    IKSerializable* m_apArrowNodes[2][2];  // +0x34 [pair][node] CBillboard2d references (two arrays of two)
    int32_t m_i32Axis;                    // +0x44 0: the items along x (the offsets negated), else along y
    int32_t m_i32FocusedArrow;            // +0x48 0 / 1, kArrowNone; Load sets 0
    float m_fListOffset;                  // +0x4c the list's offset along the axis
    float m_afArrowOffsets[2];            // +0x50 each arrow pair's offset beyond m_fListOffset
    float m_fArrowAnimSpeed;              // +0x58 the arrow ramps' speed
    Ramp m_aArrowSizeX[2][2];             // +0x5c [pair][node]; the constructor sets 0, Open {0, m_fArrowAnimSpeed, 0}
    Ramp m_aArrowSizeY[2][2];             // +0x8c
    ArrowRecord m_aArrowRecords[5];       // +0xbc
    uint8_t m_aui8ArrowState[2];          // +0x184 the record of each pair; Open sets 0xff first (+0x186..+0x187: padding)
    uint8_t m_pad186[2];
    IKSerializable* m_pSounds;            // +0x188 a CKSoundDictionaryID (a reference): 0 focus, 1 state 3, 2 validate
    float m_fFadeOutTime;                 // +0x18c vt+0x78 tests it <= 0; Open copies +0x190
    float m_fFadeOutDuration;             // +0x190 (vt+0x88 / +0x8c; read as a word, swapped)
    TVector<IKSerializable*, 1> m_vItems;  // +0x194 the list (CKInterfaceButtonBase references); the constructor {0, 1, 0}
    int32_t m_i32FocusedItem;             // +0x1a0 -1 none (PostLoad, Open)
    float m_fItemFadeSpeed;               // +0x1a4 the items' fade speed (StartFade)
    Ramp m_scroll;                        // +0x1a8 the first item's position along the axis; the speed is read, the rest 0
    float m_fItemSpacing;                 // +0x1b4 the distance between two items
    int32_t m_i32NbVisibleItems;          // +0x1b8
    int32_t m_i32FirstVisible;            // +0x1bc Load sets 0
    int32_t m_i32LastVisible;             // +0x1c0 not set by the constructor or Load (SetFirstVisible)
};
DOTD_ASSERT_SIZE(CKInterfaceScrollingMenu::ArrowRecord, 0x28);
DOTD_ASSERT_OFFSET(CKInterfaceScrollingMenu::ArrowRecord, m_afSizes, 0x04);
DOTD_ASSERT_OFFSET(CKInterfaceScrollingMenu::ArrowRecord, m_apTextures, 0x14);
DOTD_ASSERT_OFFSET(CKInterfaceScrollingMenu::ArrowRecord, m_aColors, 0x1c);
DOTD_ASSERT_OFFSET(CKInterfaceScrollingMenu::ArrowRecord, m_pEffect, 0x24);
DOTD_ASSERT_SIZE(CKInterfaceScrollingMenu::Ramp, 0xc);
DOTD_ASSERT_SIZE(CKInterfaceScrollingMenu, 0x1c4);
DOTD_ASSERT_OFFSET(CKInterfaceScrollingMenu, m_bFocused, 0x30);
DOTD_ASSERT_OFFSET(CKInterfaceScrollingMenu, m_apArrowNodes, 0x34);
DOTD_ASSERT_OFFSET(CKInterfaceScrollingMenu, m_i32Axis, 0x44);
DOTD_ASSERT_OFFSET(CKInterfaceScrollingMenu, m_i32FocusedArrow, 0x48);
DOTD_ASSERT_OFFSET(CKInterfaceScrollingMenu, m_fListOffset, 0x4c);
DOTD_ASSERT_OFFSET(CKInterfaceScrollingMenu, m_afArrowOffsets, 0x50);
DOTD_ASSERT_OFFSET(CKInterfaceScrollingMenu, m_fArrowAnimSpeed, 0x58);
DOTD_ASSERT_OFFSET(CKInterfaceScrollingMenu, m_aArrowSizeX, 0x5c);
DOTD_ASSERT_OFFSET(CKInterfaceScrollingMenu, m_aArrowSizeY, 0x8c);
DOTD_ASSERT_OFFSET(CKInterfaceScrollingMenu, m_aArrowRecords, 0xbc);
DOTD_ASSERT_OFFSET(CKInterfaceScrollingMenu, m_aui8ArrowState, 0x184);
DOTD_ASSERT_OFFSET(CKInterfaceScrollingMenu, m_pSounds, 0x188);
DOTD_ASSERT_OFFSET(CKInterfaceScrollingMenu, m_fFadeOutTime, 0x18c);
DOTD_ASSERT_OFFSET(CKInterfaceScrollingMenu, m_fFadeOutDuration, 0x190);
DOTD_ASSERT_OFFSET(CKInterfaceScrollingMenu, m_vItems, 0x194);
DOTD_ASSERT_OFFSET(CKInterfaceScrollingMenu, m_i32FocusedItem, 0x1a0);
DOTD_ASSERT_OFFSET(CKInterfaceScrollingMenu, m_fItemFadeSpeed, 0x1a4);
DOTD_ASSERT_OFFSET(CKInterfaceScrollingMenu, m_scroll, 0x1a8);
DOTD_ASSERT_OFFSET(CKInterfaceScrollingMenu, m_fItemSpacing, 0x1b4);
DOTD_ASSERT_OFFSET(CKInterfaceScrollingMenu, m_i32NbVisibleItems, 0x1b8);
DOTD_ASSERT_OFFSET(CKInterfaceScrollingMenu, m_i32FirstVisible, 0x1bc);
DOTD_ASSERT_OFFSET(CKInterfaceScrollingMenu, m_i32LastVisible, 0x1c0);
