// CKS08MenuObjectives.h - the "Menu Objectives" screen (key 0x878c, vtable 0xb2ca78, size 0x220 from 0x559438 CKS08MenuObjectives_Create). DotD only.
// Original unit: CKS08MenuObjectives.cpp (0x5582b8-0x55aec0).
#pragma once
#include <cstdint>

#include "Spyro2008/logic/CKMenuBase114c.h"
#include "Spyro2008/logic/CKS08ObjectiveList.h"
#include "k2000/core/Layout.h"

class CKS08MenuObjectives : public CKMenuBase114c {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x21e)
    DOTD_DECLARE_FACTORIES(CKS08MenuObjectives)

    CKS08MenuObjectives() { m_unk1dc = 0; }  // 0x559438 CKS08MenuObjectives_Create: then +0x1dc = 0
    int32_t IsKindOfClass(uint32_t key) override {  // vt+0x08 0x9c9d00
        return key == 0x878c || key == 0x114c || key == 0x730c || key == 0xc;
    }
    int32_t Load(IKFile* file, int32_t type) override;                                   // vt+0x2c 0x55a128 CKS08MenuObjectives_Load
    void RecursiveRegistration(int32_t type) override;                                  // vt+0x24 0x558e30 CKS08MenuObjectives_RecursiveRegistration
    void Destroy() override;  // vt+0x10 0x00558ed0 CKS08MenuObjectives_Destroy: the base's, then the texture +0x118
    uint32_t GetWidgetSlotCount() override { return 12; }                                // vt+0x68 0x9c9da0
    WidgetSlot* GetWidgetSlots() override { return m_aWidgetSlots; }                     // vt+0x6c 0x9c9da8
    const char* GetMenuName() override { return "Menu Objectives"; }                     // vt+0xb8 0x9c9d50
    uint8_t VfBC() override { return 1; }                                                // vt+0xbc 0x9c9d88
    IKSerializable** VfC0() override { return m_apMessageOuts; }                         // vt+0xc0 0x9c9d90
    uint8_t VfC4() override { return 6; }                                                // vt+0xc4 0x9c9d60
    IKSerializable** VfC8() override { return m_apMessageIns; }                          // vt+0xc8 0x9c9d68
    uint8_t* VfCC() override { return m_abMessageInFlags; }                              // vt+0xcc 0x9c9d78
    // vt+0xdc 0x00559c60 CKS08MenuObjectives_OnMenuState_maybe: update: the page buttons (HandleInput); enter: players set,
    // the rows hidden, the level's title, the open objectives of every level listed, page 0 shown.
    uint8_t OnMenuState(int32_t phase, uint8_t other) override;
    int32_t GetMenuId() override { return 0xa; }                                         // vt+0xe0 0x9c9d58
    // vt+0xe8 0x00559068 CKS08MenuObjectives_OnItemEvent: item 0 validated (state 4, after) asks the game manager for state 7.
    void OnItemState(uint8_t item, uint8_t state, uint8_t phase) override;
    // 0x00558ce8 CKS08MenuObjectives_BuildObjectiveList_maybe: the counter texts updated, then every level's entries whose
    // state byte is 1 appended to m_aItems (OnMenuState inlines the same loop).
    void BuildObjectiveList();
    // 0x00559528 CKS08MenuObjectives_RefreshPage_maybe: up to five items from `first` in rows 0..4 (by entry type 0..2: the
    // icon's x / scale m_afUnk200[3 + t] / [t], the text's x / height m_afUnk1e0[3 + t] / [t], coloured by the state);
    // the bottom text (slot 11) hidden with the game manager's text, or shown with m_pText's without objectives.
    void RefreshPage(uint32_t first);
    // 0x00559a10 CKS08MenuObjectives_HandleInput_maybe: an active player's action 10 (+ 0x14 per player, of "Flash
    // Manager") goes to menu 0x14, action 11 to menu 0x18, each with the confirm sound.
    void HandleInput();
    // 0x005585c0 CKS08MenuObjectives_SetEntryFontAndScale_maybe: row `row`'s icon (slot row + 6) shown with `texture`,
    // its x and scale (its element animation's base scale, else the node's constant scale) and colour.
    void SetEntryFontAndScale(float x, float scale, uint8_t row, void* texture, const uint32_t* color);
    // 0x00558820 CKS08MenuObjectives_SetEntryText_maybe: row `row`'s text (slot row + 1) shown with `text`, its x, font
    // height and colour.
    void SetEntryText(float x, float height, uint8_t row, IKSerializable* text, const uint32_t* color);
    uint8_t GetSelection(uint8_t /*player*/) override { return 0xff; }                   // vt+0xe4 0x9c9dc8
    uint8_t VfF0() override { return 1; }                                                // vt+0xf0 0x9c9db8
    uint8_t VfF4() override { return 0; }                                                // vt+0xf4 0x9c9dc0 the back item

    WidgetSlot m_aWidgetSlots[12];               // +0x94
    IKSerializable* m_apMessageIns[6];           // +0xf4
    uint8_t m_abMessageInFlags[6];               // +0x10c MessageProc sets one per VfC8 entry
    uint8_t m_unk112[2];
    IKSerializable* m_apMessageOuts[1];          // +0x114
    void* m_pTexture;                            // +0x118 IKFile_ReadTextureRef
    // +0x11c the shown objectives (OnMenuState builds them; no bound check, BUG(original) past 16): the entry, the main
    // level and the entry's index (the game structure's byte list of that level says its state: 1 open, 2 done).
    struct ObjectiveItem {
        const CKS08ObjectiveList::Entry* m_pEntry;  // +0x00
        uint32_t m_ui32Level;                       // +0x04
        uint32_t m_ui32Index;                       // +0x08
    };
    ObjectiveItem m_aItems[16];
    uint32_t m_unk1dc;                           // +0x1dc the constructor sets 0, the Load too (type 0)
    float m_afUnk1e0[6];                         // +0x1e0 read by the Load (0.48 0.44 0.4 0.02 0.07 0.12 in LVL000)
    uint32_t m_unk1f8;                           // +0x1f8 read raw (no swap): the file bytes, e.g. 8b 57 52 9b; a word load sees them big-endian (RGBA colour_maybe)
    uint32_t m_unk1fc;                           // +0x1fc read raw, like +0x1f8
    float m_afUnk200[6];                         // +0x200 read by the Load (0.5 0.4 0.3 0 0.03 0.06)
    IKSerializable* m_pText;                     // +0x218 CKLocTextAccessor (file key 0xe46)
    IKSerializable* m_pSound;                    // +0x21c CKSoundDictionaryID (file key 0x109)
};
DOTD_ASSERT_SIZE(CKS08MenuObjectives, 0x220);
DOTD_ASSERT_OFFSET(CKS08MenuObjectives, m_aWidgetSlots, 0x94);
DOTD_ASSERT_OFFSET(CKS08MenuObjectives, m_apMessageIns, 0xf4);
DOTD_ASSERT_OFFSET(CKS08MenuObjectives, m_abMessageInFlags, 0x10c);
DOTD_ASSERT_OFFSET(CKS08MenuObjectives, m_apMessageOuts, 0x114);
DOTD_ASSERT_OFFSET(CKS08MenuObjectives, m_pTexture, 0x118);
DOTD_ASSERT_OFFSET(CKS08MenuObjectives, m_unk1dc, 0x1dc);
DOTD_ASSERT_OFFSET(CKS08MenuObjectives, m_afUnk1e0, 0x1e0);
DOTD_ASSERT_OFFSET(CKS08MenuObjectives, m_unk1f8, 0x1f8);
DOTD_ASSERT_OFFSET(CKS08MenuObjectives, m_unk1fc, 0x1fc);
DOTD_ASSERT_OFFSET(CKS08MenuObjectives, m_afUnk200, 0x200);
DOTD_ASSERT_OFFSET(CKS08MenuObjectives, m_pText, 0x218);
DOTD_ASSERT_OFFSET(CKS08MenuObjectives, m_pSound, 0x21c);
// 0x005587c0 Menu_PlayConfirmSound_maybe (C2.8 menus-load): sound 0 of the menu's dictionary (+0x21c), the pan reset.
void Menu_PlayConfirmSound(CKS08MenuObjectives* menu);
