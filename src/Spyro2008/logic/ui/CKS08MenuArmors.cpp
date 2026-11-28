// CKS08MenuArmors.cpp - reconstructed original translation unit 0x541ff8-0x547150 (GAME_TOC1, main_toc1), 30 functions, 19 live.
// Primary class: CKS08MenuArmors  key 0xab8c  category Logic  size 0x1c4  vtable 0xb2c130
// Other owners: SetArmors (1), CKS08MenuChapter (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [ ] 0x541ff8  FUN_00541ff8  [dead]
//   [ ] 0x542220  CKS08MenuArmors_GetFullSetArmorType_maybe  [dead]
//   [ ] 0x542290  FUN_00542290  [dead]
//   [ ] 0x542340  FUN_00542340  [dead]
//   [x] 0x542390  CKS08MenuArmors_RecursiveRegistration
//   [x] 0x542428  CKS08MenuArmors_Destroy
//   [x] 0x542488  CKS08MenuArmors_DeleteArray
//   [ ] 0x542528  RegisterCKS08MenuArmorsClass
//   [ ] 0x5425b0  _GLOBAL__D_5425b0
//   [ ] 0x5425c0  _GLOBAL__I_5425c0
//   [ ] 0x5425d0  CKS08MenuArmors_GetFullSetArmorType_2_maybe  [dead]
//   [ ] 0x542638  CKS08MenuArmors_Construct  [dead]
//   [ ] 0x5426e0  FUN_005426e0  [dead]
//   [ ] 0x542798  CKS08MenuArmors_Construct_2  [dead]
//   [x] 0x542840  CKS08MenuArmors_CreateArray
//   [x] 0x542980  CKS08MenuArmors_Create
//   [x] 0x542a68  CKS08MenuArmors_Load
//   [ ] 0x542d10  CKS08MenuArmors_Save
//   [ ] 0x542f00  FUN_00542f00  [dead]
//   [ ] 0x5433c8  FUN_005433c8  [dead]
//   [x] 0x543898  CKS08MenuArmors_RefreshDragonPanelItems_maybe
//   [x] 0x544938  CKS08MenuArmors_ToggleActiveDragonPanel_maybe
//   [x] 0x544bb0  CKS08MenuArmors_HandleSlotInput_maybe
//   [x] 0x544fb8  CKS08MenuArmors_Destructor  (~CKMenuBase114c inlined (the same frees, checked against 0x556498))
//   [x] 0x5450f0  CKS08MenuArmors_Destructor_2  (implicit destructor: CKMenuBase114c's inlined)
//   [x] 0x545228  CKS08MenuArmors_DeletingDestructor  (implicit destructor: CKMenuBase114c's inlined)
//   [x] 0x545360  CKS08MenuArmors_UpdateSlotAnimations_maybe
//   [x] 0x5468d0  SetArmors
//   [x] 0x547050  CKS08MenuChapter_Delete  (CKS08MenuChapter::Delete, DOTD_DECLARE_FACTORIES)
//   [ ] 0x5470a0  FUN_005470a0  [dead]
//
//   [x] 0x9c9618  CKS08MenuArmors_IsKindOfClass  [inline]
//   [x] 0x9c9658  CKS08MenuArmors_GetClassType  [inline]
//   [x] 0x9c9660  CKS08MenuArmors_GetClassID  [inline]
//   [x] 0x9c9668  CKS08MenuArmors_vfB8  [inline]
//   [x] 0x9c9670  CKS08MenuArmors_vfE0  [inline]
//   [x] 0x9c9678  CKS08MenuArmors_GetWidgetSlotCount  [inline]
//   [x] 0x9c9680  CKS08MenuArmors_GetWidgetSlots  [inline]
//   [x] 0x9c9690  CKS08MenuArmors_vfC4  [inline]
//   [x] 0x9c9698  CKS08MenuArmors_vfC8  [inline]
//   [x] 0x9c96a8  CKS08MenuArmors_vfCC  [inline]
//   [x] 0x9c96b8  CKS08MenuArmors_vfBC  [inline]
//   [x] 0x9c96c0  CKS08MenuArmors_vfC0  [inline]
//   [x] 0x9c96d0  CKS08MenuArmors_vfF0  [inline]
//   [x] 0x9c96d8  CKS08MenuArmors_vfF4  [inline]
//   [x] 0x9c96e0  CKS08MenuArmors_vf84  [inline]
//   [x] 0x9c96e8  CKS08MenuArmors_vf88  [inline]
#include "Spyro2008/logic/ui/CKS08MenuArmors.h"

#include <cstring>

#include "k2000/io/IKFile.h"

// 0x00542a68 CKS08MenuArmors_Load: no type test of its own.
int32_t CKS08MenuArmors::Load(IKFile* file, int32_t type) {
    CKMenuBase114c::Load(file, type);
    m_ui8Switched = 0;
    m_ui8Dragon = 0;
    m_ui8Player = 0;
    // Clear the group's dynamic references [m_unk04, m_unk08) and its first m_unk08 states (signed test).
    RefGroup* group = Vf88();
    GroupState* states = Vf90(0);
    const int32_t dynamic = static_cast<int32_t>(group->m_unk08 - group->m_unk04);
    if (dynamic > 0) {
        std::memset(Vf8C(0) + group->m_unk04, 0, static_cast<uint32_t>(dynamic) * sizeof(IKSerializable*));
    }
    if (states != nullptr) std::memset(states, 0, group->m_unk08 * sizeof(GroupState));
    Vf88()->m_unk0c = 1;
    IKFile_ReadTextureRef(file, &m_pTexture1b8, 1);
    IKFile_ReadTextureRef(file, &m_pTexture1b4, 1);
    IKFile_ReadRef(file, &m_pText);
    ReadF32LE(file, &m_fUnk174);
    IKFile_ReadRef(file, &m_pSound);
    return 1;
}

// 0x00542428 CKS08MenuArmors_Destroy (C2.8 save-menu)
#include "Renderware/rwcore/RwTexture.h"
void CKS08MenuArmors::Destroy() {
    CKMenuBase114c::Destroy();  // 0x00513c60
    if (m_pTexture1b8 != nullptr) RwTextureDestroy(static_cast<RwTexture*>(m_pTexture1b8));
    if (m_pTexture1b4 != nullptr) RwTextureDestroy(static_cast<RwTexture*>(m_pTexture1b4));  // TocBridge
}

// ==== C2.8 live-fixes: the armours page ===========================================================================
// The pause menu's armours page (interface menu 0): eighteen items, nine per dragon (item 9 dragon + 3 group + armour:
// groups 0, 1, 2 are the slots 0, 2, 1), one item per armour piece, disabled until the piece is collected (the game
// structure's collectibles of category 0; the game manager's +0x64 bit 25 shows them all), and item 18 the back item.
// Cross on an item puts its armour in its slot (Cross again takes it off, 3 none); a full set (the three slots with one
// armour) plays the set animation (UpdateSlotAnimations: the slots' items lit one by one, a message out per item, the
// page's sound). Action 0xc switches the dragon's panel. Leaving the page writes the chosen armours to the game
// structure (SetEquippedArmor 0x4fd480), where CKHkS08Hero_ApplyEquippedArmor_maybe 0x30c700 finds them.
#include "Spyro2008/groups/IKGrpHero.h"
#include "Spyro2008/hooks/CKHkS08Hero.h"
#include "Spyro2008/logic/CKS08GameManager.h"
#include "Spyro2008/logic/CKS08GameStructure.h"
#include "k2000/components/CKLocTextAccessor.h"
#include "k2000/dictionaries/CKSoundDictionaryID.h"
#include "k2000/graphical/fx/CBillboard2d.h"
#include "k2000/graphical/ui/CKFlashMessageOut.h"
#include "k2000/graphical/ui/CText2d.h"
#include "k2000/input/CKInputDico.h"
#include "k2000/logic/CKInterfaceButton.h"
#include "k2000/logic/sound/CKSound.h"
#include "k2000/managers/CKInput.h"
#include "k2000/misc/Engine.h"
#include "k2000/system/CTimeManager.h"
#include "k2000/system/IKTime.h"

namespace {
CKS08GameManager* Gm(const CKS08MenuArmors* menu) { return static_cast<CKS08GameManager*>(menu->m_pGameManager); }
CKInterfaceButton* Button(CKS08MenuArmors* menu, uint32_t index) {
    if (index >= menu->m_apButtons.m_ui32NbUsedElt) return nullptr;
    return static_cast<CKInterfaceButton*>(menu->m_apButtons.m_pBlock[index]);
}
// The text of the page's CKLocTextAccessor (+0x1bc): its table's entry `index`, or its default (+0x10) without a table.
IKSerializable* PageText(CKS08MenuArmors* menu, uint32_t index) {
    CKLocTextAccessor* accessor = static_cast<CKLocTextAccessor*>(menu->m_pText);
    return accessor->m_texts.m_pBlock != nullptr ? accessor->m_texts.m_pBlock[index] : accessor->m_pText;
}
CText2d* SlotText(CKS08MenuArmors* menu, uint32_t slot) { return static_cast<CText2d*>(menu->m_aWidgetSlots[slot].m_pElement); }
void PostOut(CKS08MenuArmors* menu, uint32_t index) {
    if (menu->VfC0()[index] != nullptr) static_cast<CKFlashMessageOut*>(menu->VfC0()[index])->PostFlashMessage();  // 0x00075610
}
// An item's piece: the dragon, the armour and the slot (the switch tables of 0x5468d0, 0x544bb0 and 0x543898; items
// past 17 take item 2's case, the jump tables' default).
struct Piece {
    uint8_t dragon, armor, slot;
};
Piece ItemPiece(uint32_t item) {
    if (item > 17) item = 2;
    static const uint8_t kSlots[3] = {0, 2, 1};
    return {static_cast<uint8_t>(item / 9), static_cast<uint8_t>(item % 3), kSlots[(item % 9) / 3]};
}
// The billboards of the button's current state shown again (inlined at every texture change of the page; the same steps
// as CKInterfaceButton_SetVisualState's, without its duration test): billboards 2, 1, 0 take the state's texture (when it
// has one), colour, blend, sprite-sheet duration, rows and columns.
void ApplyStateBillboards(CKInterfaceButton* button) {
    for (int32_t i = 2; i >= 0; --i) {
        CBillboard2d* billboard = static_cast<CBillboard2d*>(button->m_apUnk38[i]);
        if (billboard == nullptr) continue;
        const CKInterfaceButton::StateVisual& s = button->m_aStates[button->m_ui8State];
        if (s.m_apTextures[i] != nullptr) billboard->SetTexture(static_cast<RwTexture*>(s.m_apTextures[i]));  // IKBillboard2d vt+0x3c
        const uint32_t color = s.m_aBillboardColorsRaw[i];
        billboard->SetColor(reinterpret_cast<const uint8_t*>(&color));  // IKBillboard2d vt+0x28
        billboard->m_bUseAlpha = s.m_abUseAlpha[i];
        billboard->SetAnimTime(s.m_afAnimDurations[i]);                                         // 0x0005b098
        billboard->SetSpriteSheetRows(static_cast<int32_t>(s.m_aui32SheetRows[i]));          // 0x0005b118
        billboard->SetSpriteSheetColumns(static_cast<int32_t>(s.m_aui32SheetColumns[i]));    // 0x0005b158
    }
}
// The second billboard's colour of states 0, 2 and 4 (+0xc4, +0x204, +0x344; RGBA bytes in memory order).
void SetItemColor(CKInterfaceButton* button, uint8_t alpha) {
    const uint8_t bytes[4] = {0xff, 0xff, 0xff, alpha};
    uint32_t word;
    std::memcpy(&word, bytes, 4);
    button->m_aStates[0].m_aBillboardColorsRaw[1] = word;
    button->m_aStates[2].m_aBillboardColorsRaw[1] = word;
    button->m_aStates[4].m_aBillboardColorsRaw[1] = word;
}
// An item lit: the second billboard's texture of states 0, 2 and 4 (+0xb8, +0x1f8, +0x338) and opaque white.
void LightItem(CKInterfaceButton* button, void* texture) {
    button->m_aStates[0].m_apTextures[1] = texture;
    button->m_aStates[2].m_apTextures[1] = texture;
    button->m_aStates[4].m_apTextures[1] = texture;
    SetItemColor(button, 0xff);
    ApplyStateBillboards(button);
}
const float kHalf = 0x1p-1f;  // TOC1 +0x7c60
const float kZero = 0.0f;     // TOC1 +0x7c64
}  // namespace

// 0x00543898 CKS08MenuArmors_RefreshDragonPanelItems_maybe: for each item of the dragon (an enabled one: lit with the
// chosen texture +0x1b4 and its slot text naming the armour when its armour is chosen, its second billboard transparent
// otherwise; a slot with no armour names nothing chosen), then the full-set text (widget slot 6 + dragon): a new full set
// starts the set animation (unless `opening`), a broken one shows the game manager's empty text.
void CKS08MenuArmors::RefreshDragonPanelItems(uint8_t dragon, int32_t opening) {
    // The text of a chosen armour (the switch at 0x544508: dragon, slot, armour).
    static const uint8_t kChosenText[2][3][3] = {{{1, 2, 0}, {7, 8, 6}, {4, 5, 3}},
                                                 {{0xe, 0xd, 0xc}, {0x14, 0x13, 0x12}, {0x11, 0x10, 0xf}}};
    const uint32_t end = dragon == 0 ? 9u : 18u;
    uint32_t item = dragon == 0 ? 0u : 9u;
    do {
        CKInterfaceButton* button = Button(this, item);
        const Piece p = ItemPiece(item);
        const uint32_t group = (item % 9) / 3;
        CText2d* text = SlotText(this, 2 * group + p.dragon);  // widget slots 0..5: the slot group, then the dragon
        const uint8_t chosen = m_aaui8Equipped[p.dragon][p.slot];
        if ((button->m_baFlags & 2) == 0) {  // not disabled; no null test (as the original)
            if (chosen == p.armor) {
                LightItem(button, m_pTexture1b4);
                if (text != nullptr) text->SetTextById(PageText(this, kChosenText[p.dragon][p.slot][chosen]));  // vt+0x88
            } else {
                SetItemColor(button, 0);  // the alpha is the disabled bit, clear here
                ApplyStateBillboards(button);
            }
        }
        if (m_aaui8Equipped[p.dragon][p.slot] == 3 && text != nullptr) {
            const uint32_t index = p.slot == 1 ? 0x1au : p.slot == 0 ? 0x18u : 0x19u;
            text->SetTextById(PageText(this, index));  // vt+0x88
        }
        item = (item + 1) & 0xff;
    } while (item < end);

    const uint8_t* e = m_aaui8Equipped[dragon];
    CText2d* setText = SlotText(this, 6u + dragon);
    uint8_t& current = m_aui8FullSet[dragon];
    const uint8_t full = (e[0] == e[1] && e[2] == e[0] && e[0] != 3) ? e[0] : 3;
    bool named = false;
    if (current == full) {
        named = current != 3;
    } else if (e[0] == e[1] && e[2] == e[0] && e[2] != 3) {
        current = e[2];
        if (opening == 0 && m_ui8SetAnim == 0) {
            m_ui8SetAnim = 1;
            m_abSetAnimStep[2] = 0;
            m_fSetAnimTime = 0.0f;  // stw 0
            m_abSetAnimStep[0] = 0;
            m_abSetAnimStep[1] = 0;
            current = e[0];
            named = current != 3;
        } else {
            named = true;
        }
    } else {
        current = 3;
    }
    if (!named) {
        if (setText != nullptr) setText->SetTextById(Gm(this)->Vf214());  // vt+0x214, vt+0x88
        return;
    }
    if (setText == nullptr) return;
    uint32_t index = 0x1b;
    if (dragon == 0) index = e[0] == 1 ? 0xbu : e[0] == 0 ? 0xau : e[0] == 2 ? 9u : 0x1bu;
    else if (dragon == 1) index = e[0] == 1 ? 0x16u : e[0] == 0 ? 0x17u : e[0] == 2 ? 0x15u : 0x1bu;
    setText->SetTextById(PageText(this, index));  // vt+0x88
}

// 0x00544938 CKS08MenuArmors_ToggleActiveDragonPanel_maybe: once per switch (+0x162, cleared when the panel's message in
// [6 + dragon] came): the panel's message out [3 + dragon], the other dragon's panel active with the focus on its first
// item (0 or 9) and its items refreshed; with two players, the player of the active panel active alone and browsing.
void CKS08MenuArmors::ToggleActiveDragonPanel() {
    const uint8_t switched = m_ui8Switched;
    if (switched == 0) {
        m_ui8Switched = 1;
        PostOut(this, (m_ui8Dragon + 3u) & 0xffu);
        m_unk60[1] = switched;
        if (m_ui8Dragon != 0) {
            m_ui8Dragon = switched;
            MoveFocusByInput(m_ui8Player, 0xff, 0);  // 0x00516de0
            RefreshDragonPanelItems(0, 0);
        } else {
            m_ui8Dragon = 1;
            MoveFocusByInput(m_ui8Player, 0xff, 9);  // 0x00516de0
            RefreshDragonPanelItems(1, 0);
        }
    }
    CKS08GameManager* gm = Gm(this);
    if (gm->GetPlayerCount() != 2) return;  // vt+0x154
    gm->SetPlayerActive(0, static_cast<uint8_t>(m_ui8Dragon == 0));  // vt+0x184
    gm = Gm(this);
    gm->SetPlayerActive(1, static_cast<uint8_t>(m_ui8Dragon == 1));
    m_ui8Player = static_cast<uint8_t>(m_ui8Dragon == 1);
}

// 0x00544bb0 CKS08MenuArmors_HandleSlotInput_maybe: for the browsing player (when active), validate (action 4 of the
// "Flash Manager" project, player 2: + 0x14) on an item takes its armour off its slot when chosen, else puts it there
// when the item is enabled, and refreshes the dragon's items; action 0xc switches the panel.
// BUG(original): an item past 17 (the back item 18, or none) takes item 2's piece (the jump table's default), so
// validating the back item also toggles Spyro's armour 2 in slot 0 when the back item is enabled.
void CKS08MenuArmors::HandleSlotInput() {
    CKInput* input = g_pEngine->m_input;
    const uint32_t project = static_cast<uint32_t>(input->FindMappingIndexByName("Flash Manager")) & 0xff;  // 0x00106978
    CKInputDico* dico = project == 0xff ? nullptr : &input->m_aaInputDico[project][1];  // null: the original reads at 0x10
    if (Gm(this)->IsPlayerActive(m_ui8Player) == 0) return;  // vt+0x180
    if (dico->GetButtonState(static_cast<uint8_t>((m_ui8Player * 0x14 + 4) & 0xfc)) == 0xff) {  // 0x0010e7d0
        const uint8_t item = m_aui8FocusedItem[m_ui8Player];
        const Piece p = ItemPiece(item);
        uint8_t& chosen = m_aaui8Equipped[p.dragon][p.slot];
        if (chosen == p.armor) {
            chosen = 3;
        } else if ((Button(this, item)->m_baFlags & 2) == 0) {
            chosen = p.armor;
        }
        m_ui8SetAnim = 0;
        RefreshDragonPanelItems(p.dragon, 0);
        return;
    }
    if (dico->GetButtonState(static_cast<uint8_t>((m_ui8Player * 0x14 + 0xc) & 0xfc)) == 0xff) ToggleActiveDragonPanel();
}

// 0x00545360 CKS08MenuArmors_UpdateSlotAnimations_maybe: the full-set animation of `dragon`: at once slot 0's item, at
// half the duration (+0x174) slot 2's, at the end slot 1's (and the animation over), each lit with the set texture
// (+0x1b8), its message out [7 + item] put in the page's reference group and the page's sound 0 played.
void CKS08MenuArmors::UpdateSlotAnimations(uint8_t dragon) {
    if (m_ui8SetAnim == 0) return;
    m_fSetAnimTime = g_pEngine->m_timeManager->m_pTime->m_afDeltaTime[IKTime::SCALABLE_GAME_TIME] + m_fSetAnimTime;  // fadds
    auto step = [this](uint32_t item) {
        if (CKInterfaceButton* button = Button(this, item)) LightItem(button, m_pTexture1b8);
        AddToRefGroup(VfC0()[(item + 7) & 0xff], 0);
        CKSound* sound = static_cast<CKSoundDictionaryID*>(m_pSound)->GetSound2(0);  // 0x00112bd8
        if (sound == nullptr) return;
        sound->ResetPan(1);  // 0x00111b70
        sound->Play(kZero);  // 0x00111230
    };
    const uint32_t base = dragon * 9u;
    if (m_abSetAnimStep[0] == 0) {
        m_abSetAnimStep[0] = 1;
        step(base + m_aaui8Equipped[dragon][0]);
    }
    if (m_fSetAnimTime >= m_fUnk174 * kHalf && m_abSetAnimStep[1] == 0) {  // fcmpu + cror (NaN: no)
        m_abSetAnimStep[1] = 1;
        step(base + m_aaui8Equipped[dragon][2] + 3);
    }
    if (m_fSetAnimTime >= m_fUnk174 && m_abSetAnimStep[2] == 0) {
        m_ui8SetAnim = 0;
        m_abSetAnimStep[2] = 1;
        step(base + m_aaui8Equipped[dragon][1] + 6);
    }
}

// 0x005468d0 SetArmors (the page's OnMenuState). Enter: Spyro's panel for player 0 (with two players the pause player's
// partner inactive), the items enabled by the collected pieces, the chosen armours read from the game structure
// (GetEquippedArmor 0x4fd658), both panels refreshed, then Cynder's panel when she is the controlled dragon (one player)
// or the pause player is player 2 (two players; any other player count too), with message out 2 (else 1). Update: the
// input, the reference group cleared, the set animation. Leave: the chosen armours written (SetEquippedArmor 0x4fd480)
// when there is a hero group.
uint8_t CKS08MenuArmors::OnMenuState(int32_t phase, uint8_t /*other*/) {
    if (phase == 1) {
        CKS08GameManager* gm = Gm(this);
        const uint8_t players = gm->GetPlayerCount();  // vt+0x154
        m_ui8Player = 0;
        m_ui8Dragon = 0;
        if (players == 2) {
            gm->SetPlayerActive(0, static_cast<uint8_t>(gm->m_ui8PausePlayer ^ 1));  // vt+0x184
            gm = Gm(this);
            gm->SetPlayerActive(1, gm->m_ui8PausePlayer);
        }
        gm = Gm(this);
        CKS08GameStructure* structure = static_cast<CKS08GameStructure*>(gm->m_gameStructure);
        for (uint32_t item = 0; item < 18; ++item) {
            CKInterfaceButton* button = Button(this, item);
            if (button == nullptr) continue;
            const Piece p = ItemPiece(item);
            const uint8_t collected = structure->IsArmorPieceCollected(p.dragon, p.armor, p.slot);  // 0x00510078
            button->SetDisabled(static_cast<uint8_t>(collected == 0 && (gm->m_flags64 & 0x2000000u) == 0));  // vt+0x84
        }
        m_ui32Selection = m_aui8FocusedItem[m_ui8Player];
        m_aaui8Equipped[0][0] = gm->GetEquippedArmor(0, 0);  // 0x004fd658
        m_aaui8Equipped[1][0] = gm->GetEquippedArmor(1, 0);
        m_aaui8Equipped[0][1] = gm->GetEquippedArmor(0, 1);
        m_aaui8Equipped[1][1] = gm->GetEquippedArmor(1, 1);
        m_aaui8Equipped[0][2] = gm->GetEquippedArmor(0, 2);
        m_aaui8Equipped[1][2] = gm->GetEquippedArmor(1, 2);
        m_ui8SetAnim = 0;
        m_aui8FullSet[0] = 3;
        RefreshDragonPanelItems(0, 1);
        m_aui8FullSet[1] = 3;
        RefreshDragonPanelItems(1, 1);
        IKGrpHero* heroes = static_cast<IKGrpHero*>(Gm(this)->m_unk04[1]);
        bool cynder = false;
        if (heroes != nullptr) {
            CKHkS08Hero* hero = static_cast<CKHkS08Hero*>(heroes->m_apControlledHeroes[0]);  // 0x002ca0e0
            if (players == 1) cynder = hero->GetDragonIndex() != 0;  // 0x00361960
            else if (players == 2) cynder = Gm(this)->m_ui8PausePlayer != 0;
            else cynder = true;
        }
        if (cynder) {
            ToggleActiveDragonPanel();
            PostOut(this, 2);
        } else {
            PostOut(this, 1);
        }
        m_ui8Switched = 1;
    } else if (phase == 2) {
        CKS08GameManager* gm = static_cast<CKS08GameManager*>(g_pEngine->m_gameManager);
        if (gm->m_unk04[1] != nullptr) {
            for (uint8_t dragon = 0; dragon < 2; ++dragon) {
                gm->SetEquippedArmor(dragon, 0, m_aaui8Equipped[dragon][0]);  // 0x004fd480
                gm->SetEquippedArmor(dragon, 1, m_aaui8Equipped[dragon][1]);
                gm->SetEquippedArmor(dragon, 2, m_aaui8Equipped[dragon][2]);
            }
        }
    } else if (phase == 0) {
        if (VfCC()[m_ui8Dragon + 6u] != 0 && m_ui8Switched != 0) m_ui8Switched = 0;
        HandleSlotInput();
        ClearRefGroup(0);
        if (m_ui8SetAnim != 0) UpdateSlotAnimations(m_ui8Dragon);
    }
    return static_cast<uint8_t>(GetMenuId());  // vt+0xe0
}

// 0x00542390 CKS08MenuArmors_RecursiveRegistration: the base first, then the referenced objects' registration.
void CKS08MenuArmors::RecursiveRegistration(int32_t type) {
    CKMenuBase114c::RecursiveRegistration(type);
    m_pText->RecursiveRegistration(type);
    m_pSound->RecursiveRegistration(type);
}
