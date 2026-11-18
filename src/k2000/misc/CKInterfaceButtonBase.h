// CKInterfaceButtonBase.h - the base of the interface buttons (unregistered key 0x63cc: id 0x18f,
// category Logic; size 0x30; vtable 0xb15f80, 0x24 slots): CKInterfaceButton (0x630c),
// CKInterfaceButtonDouble (0x634c), CKInterfaceCheckBox (0xa14c), CKInterfaceScrollingMenu (0x638c). DotD
// only: no XXL2 counterpart, so the names are descriptive (Ghidra: CKInterfaceButtonBase_63cc_maybe_*).
// Original unit: CKInterfaceButtonBase.cpp (0x67ec0-0x683d8); the inline slots are at 0x9984d8..0x9985a8.
//
// A button is one item of a menu (CKMenuBase114c::m_apButtons). The menu drives it through the slots
// +0x50..+0x8c: Open/Close with the menu, Update every frame, SetInteractionState with the item state the
// menu decides (KBase730C_SetItemState 0x512040: 0 normal, 1 validated, 2 focused, 3/4 decrease/increase),
// GetNeighbor for the d-pad navigation (KBase730C_UpdateFocus_maybe 0x518248).
#pragma once
#include <cstdint>

#include "k2000/core/IKSerializable.h"
#include "k2000/core/Layout.h"
#include "k2000/math/CVector2.h"

class IKTime;

class CKInterfaceButtonBase : public IKSerializable {
public:
    // m_baFlags (+0x08; the file's byte, then the runtime bits). Names from the users.
    enum : uint8_t {
        kFlagHold = 0x01,      // HandleValidateButton 0x513188: the item validates while held (repeat delay)
        kFlagDisabled = 0x02,  // vt+0x84 SetDisabled; a disabled item is not validated
        kFlagUpdated = 0x04,   // vt+0x58 (the base Update sets it); Close clears it
        kFlagFading = 0x08,    // Open and the visibility update set it while the fade runs
        kFlagSkip = 0x10,      // the navigation skips the item (UpdateFocus_maybe, FindItemUnderCursor)
        kFlagShown = 0x20,     // vt+0x6c Show / vt+0x70 Hide
    };

    CKInterfaceButtonBase();  // 0x00067fa0 CKInterfaceButtonBase_63cc_maybe_ConstructBase
    ~CKInterfaceButtonBase() override {}
    int32_t IsKindOfClass(uint32_t key) override { return key == 0x63cc || key == 0xc; }  // vt+0x08 0x9985a8
    int32_t GetClassType() override { return kCategoryLogic; }  // vt+0x14 0x9984d8 (unregistered key 0x63cc)
    int32_t GetClassID() override { return 0x18f; }             // vt+0x18 0x9984e0
    void RecursiveRegistration(int32_t /*type*/) override {}  // vt+0x24 0x67fe8 (returns 1)
    int32_t Save(IKFile* /*file*/, int32_t /*type*/) override { return 1; }                   // vt+0x28 0x67fe0
    int32_t Load(IKFile* file, int32_t type) override;          // vt+0x2c 0x00068010 CKInterfaceButtonBase_63cc_maybe_Load

    // vt+0x50 0x000682e0 CKInterfaceButtonBase_63cc_maybe_Open: `focused` is 1 when a player's selection is
    // this item (KBase730C_Open 0x514a00).
    virtual void Open(uint8_t focused);
    virtual void Close();                                  // vt+0x54 0x00067ff8 CKInterfaceButtonBase_63cc_maybe_Close
    virtual void Update(IKTime* /*frameClock*/) { m_baFlags = static_cast<uint8_t>(m_baFlags | kFlagUpdated); }  // vt+0x58 0x998578
    virtual void SetInteractionState(int32_t /*state*/) {}  // vt+0x5c 0x9984e8
    virtual void SetPosition(const CVector2& position) { m_vPosition = position; }  // vt+0x60 0x9984f0
    virtual CVector2* GetPosition() { return &m_vPosition; }                        // vt+0x64 0x998508
    virtual void UpdateVisibility(uint8_t fadeIn) = 0;     // vt+0x68 pure
    virtual void Show() { m_baFlags = static_cast<uint8_t>(m_baFlags | kFlagShown); }   // vt+0x6c 0x998560
    virtual void Hide() { m_baFlags = static_cast<uint8_t>(m_baFlags & ~kFlagShown); }  // vt+0x70 0x998590
    virtual void StartFadeOut() {}                         // vt+0x74 0x998518
    virtual uint8_t IsFadeOutFinished() { return 1; }      // vt+0x78 0x998520
    // vt+0x7c 0x998528: the item to go to in direction `dir` (0 up, 1 down, 2 left, 3 right; 0xff none).
    virtual uint8_t GetNeighbor(int32_t dir) { return m_aNeighbors[dir]; }
    virtual void Vf80(IKTime* /*frameClock*/) {}           // vt+0x80 0x998538 (CKInterfaceButton: its elements' vt+0x84)
    // vt+0x84 0x998540: bit 1 of the flags.
    virtual void SetDisabled(uint8_t disabled) {
        m_baFlags = static_cast<uint8_t>((m_baFlags & ~kFlagDisabled) | static_cast<uint8_t>(disabled << 1));
    }
    virtual float Vf88() = 0;                              // vt+0x88 pure (CKInterfaceButton: +0x3bc)
    virtual void Vf8C(float value) = 0;                    // vt+0x8c pure

    // 0x00067ec0 CKInterfaceButtonBase_63cc_maybe_StartFade: fadeIn 1: the fade (+0x20) to `value` from 0,
    // else from `value` down to 0; then Show and UpdateVisibility(fadeIn).
    void StartFade(float value, float speed, uint8_t fadeIn);

    uint8_t m_aNeighbors[4];      // +0x04 the item per direction (vt+0x7c); Load reads +0x07 .. +0x04
    uint8_t m_baFlags;            // +0x08 (+0x09..+0x0b: padding the original never writes)
    uint8_t m_pad09[3];
    IKSerializable* m_pMenu;      // +0x0c the menu (a reference; CKInterfaceButton_Open calls its vt+0xec)
    float m_fDelay;               // +0x10 the menu's delay after validating the item (SetItemState: menu +0x5c)
    uint8_t m_ui8State;           // +0x14 the visual state; the menu passes it to its vt+0xe8 (Open: 0xff)
    uint8_t m_pad15[3];
    CVector2 m_vPosition;         // +0x18 vt+0x60 / +0x64
    // +0x20 the fade: target, speed, current (StartFade, UpdateVisibility). The constructor sets 0, Load 1.
    float m_fFadeTarget;          // +0x20
    float m_fFadeSpeed;           // +0x24
    float m_fFade;                // +0x28
    IKSerializable* m_unk2c;      // +0x2c a reference
    // The derived classes start at +0x30: CKInterfaceButton leaves it, CKInterfaceCheckBox reads two
    // bytes there, CKInterfaceButtonDouble a reference.
};
DOTD_ASSERT_SIZE(CKInterfaceButtonBase, 0x30);
DOTD_ASSERT_OFFSET(CKInterfaceButtonBase, m_aNeighbors, 0x04);
DOTD_ASSERT_OFFSET(CKInterfaceButtonBase, m_baFlags, 0x08);
DOTD_ASSERT_OFFSET(CKInterfaceButtonBase, m_pMenu, 0x0c);
DOTD_ASSERT_OFFSET(CKInterfaceButtonBase, m_fDelay, 0x10);
DOTD_ASSERT_OFFSET(CKInterfaceButtonBase, m_ui8State, 0x14);
DOTD_ASSERT_OFFSET(CKInterfaceButtonBase, m_vPosition, 0x18);
DOTD_ASSERT_OFFSET(CKInterfaceButtonBase, m_fFadeTarget, 0x20);
DOTD_ASSERT_OFFSET(CKInterfaceButtonBase, m_fFade, 0x28);
DOTD_ASSERT_OFFSET(CKInterfaceButtonBase, m_unk2c, 0x2c);
