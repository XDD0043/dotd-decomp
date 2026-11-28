// CKS08MenuElements.cpp - reconstructed original translation unit 0x54ad98-0x553bc8 (GAME_TOC1, main_toc1), 43 functions, 35 live.
// Primary class: CKS08MenuElements  key 0x84cc  category Logic  size 0x498  vtable 0xb2c550
// Other owners: Color (3)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x54ad98  CKS08MenuElements_Delete
//   [ ] 0x54ade8  FUN_0054ade8  [dead]
//   [ ] 0x54ae30  FUN_0054ae30  [dead]
//   [ ] 0x54aef8  FUN_0054aef8  [dead]
//   [ ] 0x54af08  FUN_0054af08  [dead]
//   [ ] 0x54af58  CKS08MenuElements_SetSelectionAndWidgetStates_maybe  [dead]
//   [x] 0x54b040  CKS08MenuElements_ComputeElementRank_maybe
//   [x] 0x54b160  CKS08MenuElements_UpdateUpgradePointsDisplay_maybe
//   [x] 0x54b2e0  Color_ComputeFadeSpeed_maybe
//   [x] 0x54b3b0  CKS08MenuElements_ResetPlayerVisualEffects_maybe
//   [ ] 0x54be80  CKS08MenuElements_Save
//   [x] 0x54bea8  CKS08MenuElements_RecursiveRegistration
//   [x] 0x54c050  CKS08MenuElements_DeleteArray
//   [ ] 0x54c0f0  RegisterCKS08MenuElementsClass
//   [ ] 0x54c178  _GLOBAL__D_54c178
//   [ ] 0x54c188  _GLOBAL__I_54c188
//   [ ] 0x54c198  FUN_0054c198  [dead]
//   [ ] 0x54c288  CKS08MenuElements_Construct  [dead]
//   [x] 0x54c360  CKS08MenuElements_Destroy
//   [x] 0x54c490  CKS08MenuElements_SetTotalLevelGaugeTier_maybe
//   [ ] 0x54c6a8  CKS08MenuElements_Construct_2  [dead]
//   [x] 0x54c780  CKS08MenuElements_CreateArray
//   [x] 0x54c920  CKS08MenuElements_Create
//   [x] 0x54ca48  CKS08MenuElements_RefreshElementTexts_maybe
//   [x] 0x54d1c8  CKS08MenuElements_UpdateProgressIndicator_maybe
//   [x] 0x54d6a8  CKS08MenuElements_GetTotalLevelUpText_maybe
//   [x] 0x54d8f8  CKS08MenuElements_RefreshTotalLevelGauge_maybe
//   [x] 0x54dd08  CKS08MenuElements_CheckElementLevelUp_maybe
//   [x] 0x54e2d0  CKS08MenuElements_AnimateElementWheel_maybe
//   [x] 0x54e648  CKS08MenuElements_TransferGemsStep_maybe
//   [x] 0x54e940  CKS08MenuElements_OnItemEvent
//   [x] 0x54ea08  Color_UpdateBlinkFade_maybe
//   [x] 0x54eee8  CKS08MenuElements_UpdatePlayerVisualEffects_maybe
//   [x] 0x550030  Color_StartBlinkFade_maybe  (inlined by PlayLevelUpFeedback; the port calls it)
//   [x] 0x5501d0  CKS08MenuElements_ToggleActiveDragon_maybe
//   [x] 0x550610  CKS08MenuElements_HandleElementSelectInput
//   [x] 0x550af8  CKS08MenuElements_OnStatePhase
//   [x] 0x5513b8  CKS08MenuElements_Destructor_2  (implicit destructor: CKMenuBase114c's inlined)
//   [x] 0x5514f0  CKS08MenuElements_Load
//   [x] 0x551fd0  CKS08MenuElements_DeletingDestructor  (implicit destructor: CKMenuBase114c's inlined)
//   [x] 0x552108  CKS08MenuElements_Destructor  (~CKMenuBase114c inlined (the same frees, checked against 0x556498))
//   [x] 0x552240  CKS08MenuElements_PlayLevelUpFeedback_maybe
//   [x] 0x5538d0  CKS08MenuElements_MessageProc
//
//   [x] 0x9c9948  CKS08MenuElements_IsKindOfClass  [inline]
//   [x] 0x9c9988  CKS08MenuElements_GetClassType  [inline]
//   [x] 0x9c9990  CKS08MenuElements_GetClassID  [inline]
//   [x] 0x9c9998  CKS08MenuElements_vfB8  [inline]
//   [x] 0x9c99a0  CKS08MenuElements_vfE0  [inline]
//   [x] 0x9c99a8  CKS08MenuElements_vfC4  [inline]
//   [x] 0x9c99b0  CKS08MenuElements_vfC8  [inline]
//   [x] 0x9c99c0  CKS08MenuElements_vfCC  [inline]
//   [x] 0x9c99d0  CKS08MenuElements_vfBC  [inline]
//   [x] 0x9c99d8  CKS08MenuElements_vfC0  [inline]
//   [x] 0x9c99e8  CKS08MenuElements_GetWidgetSlotCount  [inline]
//   [x] 0x9c99f0  CKS08MenuElements_GetWidgetSlots  [inline]
//   [x] 0x9c9a00  CKS08MenuElements_vfF0  [inline]
//   [x] 0x9c9a08  CKS08MenuElements_vfF4  [inline]
#include "Spyro2008/logic/ui/CKS08MenuElements.h"

#include "k2000/io/IKFile.h"

// 0x005514f0 CKS08MenuElements_Load: no type test of its own.
int32_t CKS08MenuElements::Load(IKFile* file, int32_t type) {
    CKMenuBase114c::Load(file, type);
    m_unk32c = 0;
    m_unk240 = 0;
    for (float& value : m_afUnk25c) ReadF32LE(file, &value);
    ReadU8(file, &m_unk28c);
    ReadF32LE(file, &m_fUnk290);
    ReadF32LE(file, &m_fUnk294);
    for (uint32_t i = 8; i-- != 0;) IKFile_ReadTextureRef(file, &m_apTextures2ac[i], 1);
    IKFile_ReadRef(file, &m_pText2a0);
    IKFile_ReadRef(file, &m_pFlashFx);
    IKFile_ReadRef(file, &m_pQuake338);
    IKFile_ReadRef(file, &m_pQuakeUpdater33c);
    IKFile_ReadRef(file, &m_pQuake34c);
    IKFile_ReadRef(file, &m_pQuakeUpdater350);
    ReadRaw(file, m_unk380, 4);
    ReadF32LE(file, &m_unk384);
    ReadF32LE(file, &m_unk388);
    ReadRaw(file, m_unk3b8, 4);
    ReadF32LE(file, &m_fUnk3bc);
    ReadF32LE(file, &m_fUnk3c0);
    ReadRaw(file, m_unk450, 4);
    ReadF32LE(file, &m_fUnk454);
    ReadF32LE(file, &m_fUnk458);
    IKFile_ReadRef(file, &m_pSound);
    IKFile_ReadRef(file, &m_pText2a4);
    for (uint32_t i = 24; i-- != 0;) IKFile_ReadTextureRef(file, &m_apTextures2cc[i], 1);
    ReadU32LE(file, &m_unk244);
    ReadU8(file, &m_unk488);
    ReadU8(file, &m_unk489);
    ReadF32LE(file, &m_fUnk48c);
    ReadRaw(file, &m_unk474, 4);
    ReadF32LE(file, &m_fUnk478);
    ReadF32LE(file, &m_fUnk47c);
    return 1;
}

// 0x0054c360 CKS08MenuElements_Destroy (C2.8 save-menu)
#include "Renderware/rwcore/RwTexture.h"
void CKS08MenuElements::Destroy() {
    CKMenuBase114c::Destroy();  // 0x00513c60
    for (int32_t i = 7; i >= 0; --i) {
        if (m_apTextures2ac[i] != nullptr) RwTextureDestroy(static_cast<RwTexture*>(m_apTextures2ac[i]));
    }
    for (int32_t i = 23; i >= 0; --i) {
        if (m_apTextures2cc[i] != nullptr) RwTextureDestroy(static_cast<RwTexture*>(m_apTextures2cc[i]));
    }
}

// ==== C2.8 menus-load: the elements screen =========================================================================
// The screen of the element upgrades (interface menu 5): each dragon's wheel of four elements (the selected element
// m_aui8Element[dragon]), the free gems (the game structure's +0x84 / +0x88) given to the selected element step by step
// while the item is held (PlayerProgress_AddElementGems_maybe), the element's level (the game manager's
// GetElementLevel: the gems against the costs of the level records +0xc48.. / +0xc84..), and the total level (the sum of
// the four levels in tiers of 3, 4, 5... levels) with its gauge and bonus gems.
#include <cmath>
#include <cstdio>
#include <cstring>

#include "Spyro2008/groups/IKGrpHero.h"
#include "crt/ppc_ops.h"
#include "Renderware/rpprtstd/RpPrtStd.h"
#include "k2000/logic/ui/CKLocText.h"
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
#include "k2000/logic/ui/CLocManager.h"
#include "k2000/managers/CKInput.h"
#include "k2000/misc/Engine.h"
#include "k2000/misc/FloatApproach.h"
#include "k2000/misc/JobQueue.h"
#include "k2000/scenegraph/CParticlesNodeFx.h"
#include "k2000/system/CTimeManager.h"
#include "k2000/system/IKTime.h"
#include "crt/xsinf.h"

namespace {
CKS08GameManager* Gm(const CKS08MenuElements* menu) { return static_cast<CKS08GameManager*>(menu->m_pGameManager); }
CKS08GameStructure* Gs(const CKS08MenuElements* menu) {
    return static_cast<CKS08GameStructure*>(Gm(menu)->m_gameStructure);
}
// The level records' words (the game manager's +0xc44 + 4 (3 element + level) for Spyro, +0xc80 + ... for Cynder): the
// gems element `element` needs for `level` (1..3); element 4's words are the total level's bonus amounts.
uint32_t LevelCost(const CKS08GameManager* gm, uint8_t dragon, uint32_t element, uint32_t level) {
    const uint32_t* words = dragon == 0 ? &gm->m_aSpyroUpgradeCosts[0].m_unk0 : &gm->m_aCynderUpgradeCosts[0].m_unk0;
    return words[element * 3 + level - 1];
}
// The gems of an element (the game structure's +0x8c + 4 element for Spyro, +0xa0 + 4 element for Cynder).
uint32_t ElementGems(const CKS08MenuElements* menu, uint8_t dragon, uint32_t element) {
    return Gs(menu)->RtWord((dragon == 0 ? 0x8cu : 0xa0u) + element * 4u);
}
// The total level: the four element levels summed (elements 3, 2, 1, 0), counted in tiers of 3, 4, 5... levels; `rest` the
// levels above the last full tier.
uint32_t TotalLevelTier(CKS08MenuElements* menu, uint8_t dragon, uint32_t* rest) {
    CKS08GameManager* gm = Gm(menu);
    const uint32_t l3 = gm->GetElementLevel(dragon, 3);
    const uint32_t l2 = gm->GetElementLevel(dragon, 2);
    const uint32_t l1 = gm->GetElementLevel(dragon, 1);
    const uint32_t l0 = gm->GetElementLevel(dragon, 0);
    uint32_t sum = l2 + l3 + l1 + l0;
    uint32_t tier = 0;
    while (tier + 3 <= sum) {
        sum -= tier + 3;
        ++tier;
    }
    if (rest != nullptr) *rest = sum;
    return tier;
}
// A reference group button (m_apButtons; null past the count).
CKInterfaceButton* Button(CKS08MenuElements* menu, uint32_t index) {
    if (index >= menu->m_apButtons.m_ui32NbUsedElt) return nullptr;
    return static_cast<CKInterfaceButton*>(menu->m_apButtons.m_pBlock[index]);
}
// The text of a CKLocTextAccessor: its table's entry `index`, or its default (+0x10) without a table.
IKSerializable* AccessorText(IKSerializable* object, uint32_t index) {
    CKLocTextAccessor* accessor = static_cast<CKLocTextAccessor*>(object);
    return accessor->m_texts.m_pBlock != nullptr ? accessor->m_texts.m_pBlock[index] : accessor->m_pText;
}
CText2d* SlotText(CKS08MenuElements* menu, uint32_t slot) { return static_cast<CText2d*>(menu->m_aWidgetSlots[slot].m_pElement); }
CBillboard2d* SlotBillboard(CKS08MenuElements* menu, uint32_t slot) {
    return static_cast<CBillboard2d*>(menu->m_aWidgetSlots[slot].m_pElement);
}
// The element animation of `element` (CKMenuBase114c +0x28, searched from the last): its base scale (+0x28); without one
// the element's own constant scale (+0x20 / +0x24) takes the value.
void SetElementScale(CKS08MenuElements* menu, CBillboard2d* element, float value) {
    for (uint32_t i = menu->m_aElementAnims.m_ui32NbUsedElt; i != 0; --i) {
        CKMenuBase114c::ElementAnim& anim = menu->m_aElementAnims.m_pBlock[i - 1];
        if (anim.m_pElement == element) {
            anim.m_fUnk28 = value;
            return;
        }
    }
    element->m_v2ConstantScale.m_fX = value;
    element->m_v2ConstantScale.m_fY = value;
}
float FrameDt() { return g_pEngine->m_timeManager->m_pTime->m_afDeltaTime[IKTime::FIXED_GAME_TIME]; }
// The "Flash Manager" input project's second configuration (null: the original reads through address 0x10).
CKInputDico* FlashManagerDico() {
    CKInput* input = g_pEngine->m_input;
    const uint32_t project = static_cast<uint32_t>(input->FindMappingIndexByName("Flash Manager")) & 0xff;
    if (project == 0xff) return nullptr;
    return &input->m_aaInputDico[project][1];
}
const float kOne = 0x1p+0f;              // TOC1 +0x7df4
const float kMinusOne = -0x1p+0f;        // TOC1 +0x7dfc
const float kZero = 0.0f;                // TOC1 +0x7e20
const float k180 = 0x1.68p+7f;           // TOC1 +0x7dd4 180.0
const float k360 = 0x1.68p+8f;           // TOC1 +0x7dd8 360.0
const float kMinus360 = -0x1.68p+8f;     // TOC1 +0x7e68
const float kThree = 0x1.8p+1f;          // TOC1 +0x7e64
const float kHalf = 0x1p-1f;             // TOC1 +0x7e6c
const float kTen = 0x1.4p+3f;            // TOC1 +0x7e70
const float kSoundInterval = 0x1.99999ap-3f;  // TOC1 +0x7e74 0.2
const float kDegToRad = 0x1.1df468p-6f;  // TOC1 +0x7e60 0.01745329 (0x3c8efa34)
}  // namespace

// 0x0054e940 CKS08MenuElements_OnItemEvent (vt+0xe8): item 2 (Spyro's wheel) or 5 (Cynder's) in state 4 (validated) for
// the dragon shown: arg 0 (held) a delayed transfer step, arg 1 (pressed) the delay restarted and a step at once.
void CKS08MenuElements::OnItemState(uint8_t item, uint8_t state, uint8_t arg) {
    if (arg != 0 && arg != 1) return;
    if (state != 4) return;
    const uint8_t dragon = m_ui8Dragon;
    if (item == 2) {
        if (dragon != 0) return;
    } else {
        if (item != 5) return;
        if (dragon != 1) return;
    }
    if (arg == 0) {
        TransferGemsStep(dragon, m_unk244, 1);
        return;
    }
    m_vUnk248[2] = m_afUnk25c[0];
    m_fTransferSoundTime = 0.0f;
    m_fTransferTime = 0.0f;
    TransferGemsStep(dragon, m_unk244, 0);
}

// 0x0054e648 CKS08MenuElements_TransferGemsStep_maybe: `amount` gems (at most what the element still takes) from the
// dragon's free gems to its selected element, once the step delay (m_vUnk248, which shortens while held) ran when
// `delayed`; a sound (the wheel button's sound 2) at most every 0.2 s; then the level-up check.
void CKS08MenuElements::TransferGemsStep(uint8_t dragon, uint32_t amount, int32_t delayed) {
    CKS08GameManager* gm = Gm(this);
    const uint8_t element = m_aui8Element[dragon];
    const uint32_t gems = ElementGems(this, dragon, element);
    const uint32_t cap = LevelCost(gm, dragon, element, 3);
    if (cap < amount + gems) amount = cap - gems;
    if (amount == 0) return;
    const float dt = FrameDt();
    FloatApproach_Step(dt, m_vUnk248);
    m_fTransferTime = dt + m_fTransferTime;
    m_fTransferSoundTime = dt + m_fTransferSoundTime;
    if (!(m_fTransferTime >= m_vUnk248[2]) && delayed != 0) return;  // fcmpu, cror gt|eq
    const uint32_t left = m_aGemsLeft[dragon];
    uint32_t given;
    if (amount < left) {
        m_aGemsLeft[dragon] = left - amount;
        given = amount;
    } else {
        m_aGemsLeft[dragon] = 0;
        given = left;
    }
    if (given != 0 || amount < left) {
        Gs(this)->SetRtWord(dragon == 0 ? 0x84u : 0x88u, m_aGemsLeft[dragon]);
        Gs(this)->AddElementGems(dragon, m_aui8Element[dragon], static_cast<int32_t>(given));  // 0x00510748
        if (m_fTransferSoundTime >= kSoundInterval) {
            m_fTransferSoundTime = 0.0f;
            // The wheel button's sound dictionary (the original reads it through a null button too).
            CKInterfaceButton* button = Button(this, dragon * 3u + 2u);
            CKSound* sound = static_cast<CKSoundDictionaryID*>(button->m_pSounds)->GetSound(2);  // 0x00112bc0
            if (sound != nullptr) sound->Play(kZero);  // 0x00111230
        }
    }
    CheckElementLevelUp(dragon);
    m_fTransferTime = 0.0f;
}

// 0x0054dd08 CKS08MenuElements_CheckElementLevelUp_maybe: the selected element's level against the one kept. No new level:
// the wheel button disabled while the element is full and the texts refreshed. A new level: the element's level-up message
// box (text (dragon * 4 + element) of +0x2a4), the total level's bonus gems (element 4: the tier's amount / (tier + 3) + 1)
// while below tier 3, the button disabled, and the gems text "gems/cost" (the cost of the level reached; the top level's).
void CKS08MenuElements::CheckElementLevelUp(uint8_t dragon) {
    CKS08GameManager* gm = Gm(this);
    const uint32_t level = gm->GetElementLevel(dragon, m_aui8Element[dragon]);  // 0x004f9558
    if (level <= m_ui32ElementLevel) {
        CKInterfaceButton* button = Button(this, dragon * 3u + 2u);
        const uint8_t element = m_aui8Element[dragon];
        const uint32_t gems = ElementGems(this, dragon, element);
        const uint32_t cap = LevelCost(gm, dragon, element, 3);
        button->SetDisabled(gems == cap ? 1 : 0);  // vt+0x84 (abs(cap ^ gems) - 1 < 0)
        RefreshElementTexts(m_ui8Dragon);
        return;
    }
    m_ui32ElementLevel = level;
    MessageBox_Show(kOne, kMinusOne, this,
                    static_cast<const CKLocText*>(AccessorText(m_pText2a4, (dragon * 4u + m_aui8Element[dragon]) & 0xffu)),
                    1, 0, nullptr);  // 0x000695d0
    m_ui8LevelUpStep = 1;
    const uint32_t tier = TotalLevelTier(this, dragon, nullptr);
    if (tier < 3) {
        const uint32_t bonus = LevelCost(gm, dragon, 4, tier + 1) / (tier + 3) + 1;
        if (bonus != 0) Gs(this)->AddElementGems(dragon, 4, static_cast<int32_t>(bonus));
    }
    Button(this, dragon * 3u + 2u)->SetDisabled(1);
    if (m_aWidgetSlots[14 + dragon].m_pElement == nullptr) return;
    const uint8_t element = m_aui8Element[dragon];
    // BUG(original)? the cost shown is the reached level's (RefreshElementTexts shows the next level's).
    const uint32_t required = level < 3 ? LevelCost(gm, dragon, element, level & 0xffu) : LevelCost(gm, dragon, element, 3);
    char buffer[0x108];
    std::snprintf(buffer, sizeof(buffer), "%d/%d", static_cast<int32_t>(ElementGems(this, dragon, element)),
                  static_cast<int32_t>(required));  // 0x0098d3b0 FormatString, 0x00acb658
    SlotText(this, 14 + dragon)->SetTextAscii(buffer);  // vt+0x90
}

// 0x0054ca48 CKS08MenuElements_RefreshElementTexts_maybe: the element's name (the game manager's +0xf04 texts,
// dragon * 5 + element), the level line (below the top: text 10 of +0x2a4 and the counter variable 11 = level + 1; at the
// top: text 11), "gems/next cost", and the element's four description texts of +0x2a0 (dragon * 40 + element * 10: +0
// the title, +1, +2 / +3 + 2 level).
void CKS08MenuElements::RefreshElementTexts(uint8_t dragon) {
    CKS08GameManager* gm = Gm(this);
    const uint32_t level = gm->GetElementLevel(dragon, m_aui8Element[dragon]);
    if (CText2d* name = SlotText(this, 10 + dragon)) {
        name->Enable();  // vt+0x64
        name->SetTextById(AccessorText(gm->m_unkF00[1], dragon * 5u + m_aui8Element[dragon]));  // vt+0x88
    }
    if (CText2d* line = SlotText(this, 12 + dragon)) {
        if (level < 3) {
            line->SetTextById(AccessorText(m_pText2a4, 10));
            CLocManager* loc = g_pEngine->m_locManager;
            const uint32_t variable = gm->GetCounterTextVarTable()[11];  // vt+0x354 +0x2c
            if (static_cast<int32_t>(level + 1) != loc->GetTextVariableValue(variable)) {
                loc->SetTextVariableValue(gm->GetCounterTextVarTable()[11], static_cast<int32_t>(level + 1));
            }
        } else {
            line->SetTextById(AccessorText(m_pText2a4, 11));
        }
    }
    if (m_aWidgetSlots[14 + dragon].m_pElement != nullptr) {
        const uint8_t element = m_aui8Element[dragon];
        const uint32_t cost = level < 3 ? LevelCost(gm, dragon, element, (level + 1) & 0xffu) : LevelCost(gm, dragon, element, 3);
        char buffer[0x108];
        std::snprintf(buffer, sizeof(buffer), "%d/%d", static_cast<int32_t>(ElementGems(this, dragon, element)),
                      static_cast<int32_t>(cost));
        SlotText(this, 14 + dragon)->SetTextAscii(buffer);
    }
    const uint32_t base = dragon * 40u + m_aui8Element[dragon] * 10u;
    if (CText2d* text = SlotText(this, 18 + dragon)) {
        text->Enable();
        text->SetTextById(AccessorText(m_pText2a0, base + 1));
    }
    if (CText2d* text = SlotText(this, 22 + dragon)) {
        text->Enable();
        const uint32_t now = gm->GetElementLevel(dragon, m_aui8Element[dragon]);
        SlotText(this, 22 + dragon)->SetTextById(AccessorText(m_pText2a0, base + now * 2u + 3));
    }
    if (CText2d* text = SlotText(this, 16 + dragon)) {
        text->Enable();
        text->SetTextById(AccessorText(m_pText2a0, base));
    }
    if (CText2d* text = SlotText(this, 20 + dragon)) {
        text->Enable();
        const uint32_t now = gm->GetElementLevel(dragon, m_aui8Element[dragon]);
        SlotText(this, 20 + dragon)->SetTextById(AccessorText(m_pText2a0, base + now * 2u + 2));
    }
}

// 0x0054d6a8 CKS08MenuElements_GetTotalLevelUpText_maybe: text 8 of +0x2a4 at a full tier, else the counter variable 13 =
// the levels the next tier still needs and text 9.
IKSerializable* CKS08MenuElements::GetTotalLevelUpText(uint8_t dragon) {
    CKS08GameManager* gm = static_cast<CKS08GameManager*>(g_pEngine->m_gameManager);
    uint32_t rest = 0;
    const uint32_t tier = TotalLevelTier(this, dragon, &rest);
    if (rest == 0) return AccessorText(m_pText2a4, 8);
    const int32_t missing = static_cast<int32_t>(tier + 3 - rest);
    CLocManager* loc = g_pEngine->m_locManager;
    if (missing != loc->GetTextVariableValue(gm->GetCounterTextVarTable()[13])) {
        g_pEngine->m_locManager->SetTextVariableValue(gm->GetCounterTextVarTable()[13], missing);
    }
    return AccessorText(m_pText2a4, 9);
}

// 0x0054c490 CKS08MenuElements_SetTotalLevelGaugeTier_maybe: the gauge billboard of tier `tier` (slot 24 + dragon + 2 tier)
// shown with texture 12 dragon + `texture` of +0x2cc, white; `burst` starts the tier's two particle effects (slots 38 and
// 32 + dragon + 2 tier).
void CKS08MenuElements::SetTotalLevelGaugeTier(uint8_t dragon, uint32_t tier, uint32_t texture, int32_t burst) {
    const uint32_t slot = dragon + (tier & 0x7fffffffu) * 2u;
    if (CBillboard2d* gauge = SlotBillboard(this, 24 + slot)) {
        gauge->Enable();  // vt+0x64
        gauge->SetTexture(static_cast<RwTexture*>(m_apTextures2cc[(dragon * 12u + texture) & 0xffffffffu]));  // IKBillboard2d vt+0x3c
        const uint8_t white[4] = {0xff, 0xff, 0xff, 0xff};
        gauge->SetColor(white);  // IKBillboard2d vt+0x28
    }
    if (burst == 0) return;
    if (CParticlesNodeFx* fx = static_cast<CParticlesNodeFx*>(m_aWidgetSlots[38 + slot].m_pElement)) {
        fx->m_sgProperties = ((((fx->m_sgProperties | 0x40000u) | 0x200u) | 0x400u) & ~0x80000u);
        fx->m_fEmissionSpeedAdjustment = 0.0f;
        fx->m_pRpPrtStdEmitter->flag |= rpPRTSTDEMITTERFLAGACTIVE | rpPRTSTDEMITTERFLAGEMIT;
    }
    if (CParticlesNodeFx* fx = static_cast<CParticlesNodeFx*>(m_aWidgetSlots[32 + slot].m_pElement)) {
        fx->m_sgProperties = (((fx->m_sgProperties | 0x40000u) | 0x400u) & ~0x80000u);
        fx->m_fEmissionSpeedAdjustment = 0.0f;
        fx->m_pRpPrtStdEmitter->flag |= rpPRTSTDEMITTERFLAGACTIVE | rpPRTSTDEMITTERFLAGEMIT;
    }
}

// 0x0054d8f8 CKS08MenuElements_RefreshTotalLevelGauge_maybe: no level at all: the three tier gauges hidden, without
// texture, white with alpha 0. Else every full tier at its last texture (with its burst), and the tier being filled at the texture of
// its levels.
void CKS08MenuElements::RefreshTotalLevelGauge(uint8_t dragon) {
    uint32_t rest = 0;
    const uint32_t tier = TotalLevelTier(this, dragon, &rest);
    if (tier == 0 && rest == 0) {
        for (uint32_t slot : {24u, 26u, 28u}) {
            if (CBillboard2d* gauge = SlotBillboard(this, slot + dragon)) {
                gauge->Disable();  // vt+0x68
                gauge->SetTexture(nullptr);
                const uint8_t clear[4] = {0xff, 0xff, 0xff, 0x00};  // the alpha byte is the tier (0)
                gauge->SetColor(clear);
            }
        }
        return;
    }
    // The textures run on: tier t's levels are textures [sum of the earlier tiers' sizes, + t + 3).
    uint32_t first = 0;
    for (uint32_t t = 0; t <= tier; ++t) {
        if (t < tier) {
            first = t + 3 + first;
            SetTotalLevelGaugeTier(dragon, t, (first & 0xffu) - 1, 1);
        } else if (rest != 0) {
            first = rest + first - 1;
            SetTotalLevelGaugeTier(dragon, tier, first & 0xffu, 0);
            return;
        }
    }
}

// 0x005501d0 CKS08MenuElements_ToggleActiveDragon_maybe: once per opening (+0x240), the dragon switched: the message out
// 3 + dragon posted, the visual effects of the old one reset, the other wheel's buttons back to normal (its wheel button
// focused, state 2), the selections (+0x6c / +0x6d) on that wheel button (5 or 2), the level kept, the checks; with two
// players, the other player active and controlling.
void CKS08MenuElements::ToggleActiveDragon() {
    g_pEngine->m_input->FindMappingIndexByName("Flash Manager");  // 0x00106978 (the result is not used)
    if (m_unk240 != 0) return;
    const uint8_t old = m_ui8Dragon;
    m_unk240 = 1;
    const uint32_t out = (old + 3u) & 0xffu;
    if (VfC0()[out] != nullptr) static_cast<CKFlashMessageOut*>(VfC0()[out])->PostFlashMessage();  // 0x00075610
    if (m_unk32c != 0) ResetPlayerVisualEffects(m_ui8Dragon);
    const uint32_t focus = m_ui8Dragon == 0 ? 5u : 2u;
    m_ui8Dragon = m_ui8Dragon == 0 ? 1 : 0;
    m_aui8FocusedItem[1] = static_cast<uint8_t>(focus);
    m_aui8FocusedItem[0] = static_cast<uint8_t>(focus);
    for (uint32_t i = 8;;) {
        CKInterfaceButton* button = Button(this, i);
        if (button != nullptr) {
            if (i == focus) {
                // The focused button: state 2, then the loop goes on from below it.
                Button(this, focus)->SetInteractionState(2);  // vt+0x5c (the original calls through null when absent)
                i = focus - 1;
                continue;
            }
            button->SetInteractionState(0);
        }
        if (i == 0) break;
        --i;
    }
    m_ui32ElementLevel = Gm(this)->GetElementLevel(m_ui8Dragon, m_aui8Element[m_ui8Dragon]);
    CheckElementLevelUp(m_ui8Dragon);
    RefreshTotalLevelGauge(m_ui8Dragon);
    CKS08GameManager* gm = Gm(this);
    if (gm->GetPlayerCount() == 2) {  // vt+0x154
        gm->SetPlayerActive(0, m_ui8Dragon == 0 ? 1 : 0);  // vt+0x184
        gm->SetPlayerActive(1, m_ui8Dragon == 1 ? 1 : 0);
        m_ui8Player = m_ui8Dragon;
    }
}

// 0x00550610 CKS08MenuElements_HandleElementSelectInput: for the controlling player (when active): left / right (actions
// 0 / 6 and 1 / 7 of the "Flash Manager" project, player 2: + 0x14; Cynder's wheel turns the other way) turns the wheel one
// element (the target angle by 360 / the element count, the wheel button normal and faded in); otherwise action 0xc
// switches the dragon.
void CKS08MenuElements::HandleElementSelectInput(uint8_t dragon) {
    CKInputDico* dico = FlashManagerDico();
    CKS08GameManager* gm = Gm(this);
    if (gm->IsPlayerActive(m_ui8Player) == 0) return;  // vt+0x180
    const int32_t p = m_ui8Player * 0x14;
    auto state = [dico, p](int32_t action) { return dico->GetButtonState(static_cast<uint8_t>(p + action)); };
    int32_t turn = 0;  // 1 the next element, -1 the previous
    if (dragon == 0) {
        if (state(1) < 0x81 && state(7) != 0xff) {
            if (state(0) < 0x81 && state(6) < 0x81) turn = 0;
            else turn = -1;
        } else {
            turn = 1;
        }
    } else if (dragon == 1) {
        if (state(0) > 0x80 || state(6) == 0xff) {
            turn = 1;
        } else if (state(1) < 0x81 && state(7) != 0xff) {
            turn = 0;
        } else {
            turn = -1;
        }
    }
    if (turn == 0) {
        if (state(0xc) != 0xff) return;
        ToggleActiveDragon();
        return;
    }
    const int8_t previous = static_cast<int8_t>(m_aui8Element[dragon]);
    const int8_t next = static_cast<int8_t>(previous + turn);
    m_aui8PrevElement[dragon] = static_cast<uint8_t>(previous);
    if (next < 4) {
        if (next < 0) m_aui8Element[dragon] = static_cast<uint8_t>(previous + (turn > 0 ? 5 : 3));
        else m_aui8Element[dragon] = static_cast<uint8_t>(next);
    } else {
        m_aui8Element[dragon] = static_cast<uint8_t>(previous + (turn > 0 ? -3 : -5));
    }
    float* wheel = dragon == 0 ? m_vUnk274 : m_vUnk280;
    const float step = k360 / static_cast<float>(m_unk28c);
    wheel[0] = turn > 0 ? wheel[0] + step : wheel[0] - step;
    const uint32_t index = dragon * 2u + dragon + 2u;
    // The original calls these through a null button when the group is short.
    if (CKInterfaceButton* button = Button(this, index)) {
        button->SetInteractionState(0);  // vt+0x5c
        button->StartFade(kZero, kTen, 0);  // 0x00067ec0
    }
}

// 0x0054e2d0 CKS08MenuElements_AnimateElementWheel_maybe: the wheel's angle approaches its target (the billboard slot
// 8 + dragon turned by it; Cynder's 180 - angle); at the target the wheel button is focused (state 2); within half a step
// of it the button fades in with the new element's texture (+0x2ac [4 dragon + element]) and the checks and texts follow.
void CKS08MenuElements::AnimateElementWheel(uint8_t dragon) {
    CBillboard2d* wheelBillboard = SlotBillboard(this, 8 + dragon);
    if (wheelBillboard == nullptr) return;
    float* wheel = dragon == 0 ? m_vUnk274 : m_vUnk280;
    if (wheel[2] == wheel[0]) return;
    const float dt = FrameDt();
    m_ui32ElementLevel = Gm(this)->GetElementLevel(dragon, m_aui8Element[dragon]);
    const uint8_t count = m_unk28c;
    const float before = wheel[0] - wheel[2];  // the remaining turn before the step
    FloatApproach_Step(dt, wheel);
    float angle = wheel[2];
    if (SlotBillboard(this, 8 + dragon) != nullptr) {
        if (dragon == 1) angle = k180 - angle;
        SlotBillboard(this, 8 + dragon)->m_f32RotateAngle = angle;
    }
    const uint32_t index = dragon * 3u + 2u;
    if (wheel[2] == wheel[0]) {
        Button(this, index)->SetInteractionState(2);  // vt+0x5c (through null when absent, as the original)
        return;
    }
    const float remaining = std::fabs(wheel[0] - wheel[2]);
    if (!(kHalf < std::fabs(before) / (k360 / static_cast<float>(count)))) return;
    if (!(remaining / (k360 / static_cast<float>(m_unk28c)) <= kHalf)) return;
    if (CKInterfaceButton* button = Button(this, index)) {
        button->StartFade(kOne, kTen, 1);
        if (CBillboard2d* image = static_cast<CBillboard2d*>(button->m_apUnk38[0])) {
            image->SetTexture(static_cast<RwTexture*>(m_apTextures2ac[dragon * 4u + m_aui8Element[dragon]]));
        }
    }
    CheckElementLevelUp(dragon);
    RefreshElementTexts(dragon);
}

// 0x0054d1c8 CKS08MenuElements_UpdateProgressIndicator_maybe: the progress marker (slot 6 + dragon) placed on a circle
// (angle +0x268 degrees, radius between +0x26c and +0x270 by the element's progress: (gems - this level's cost) / (next
// level's cost - this level's cost) + level, over 3; full at the top; scaled up while the wheel turns).
void CKS08MenuElements::UpdateProgressIndicator(uint8_t dragon) {
    const uint32_t slot = dragon + 6u;
    if (m_aWidgetSlots[slot].m_pElement == nullptr) return;
    const float angle = m_afUnk25c[3] * kDegToRad;  // +0x268 (fmuls)
    CKS08GameManager* gm = Gm(this);
    const uint32_t level = gm->GetElementLevel(dragon, m_aui8Element[dragon]);
    float progress = kOne;
    if (level < 3) {
        const uint8_t element = m_aui8Element[dragon];
        const uint32_t gems = ElementGems(this, dragon, element);
        const uint32_t next = LevelCost(gm, dragon, element, (level + 1) & 0xffu);
        const uint32_t here = level != 0 ? LevelCost(gm, dragon, element, level & 0xffu) : 0;
        progress = (static_cast<float>(gems - here) / static_cast<float>(next - here) + static_cast<float>(level)) / kThree;
    }
    const float* wheel = dragon == 0 ? m_vUnk274 : m_vUnk280;
    if (wheel[2] != wheel[0]) {
        const float remaining = std::fabs(wheel[0] - wheel[2]);
        progress = progress * (remaining / (kMinus360 / static_cast<float>(m_unk28c)) + kOne);
    }
    const float radius = ppc::fmadds(progress, m_afUnk25c[5] - m_afUnk25c[4], m_afUnk25c[4]);
    // The inlined cosf / sinf (the sign bit tested; a negative angle through the library's).
    float c, s;
    int32_t bits;
    std::memcpy(&bits, &angle, 4);
    if (bits < 0) {
        c = crt::LibCosf(-angle);
        s = -crt::LibSinf(-angle);
    } else {
        c = crt::InlineCosf(angle);
        s = crt::InlineSinf(angle);
    }
    float x = c * radius;
    if (dragon == 1) x = -x;
    SetElementX(x, slot);       // vt+0x7c
    SetElementY(s * radius, slot);  // vt+0x80
}

// 0x00550af8 CKS08MenuElements_OnStatePhase (vt+0xdc). Enter (1): no effects, Spyro's wheel, the first player; with two
// players the pause player's dragon; the elements, the level, the transfer delay, the gems kept, both wheels at their start
// angle with their element textures, the selections on Spyro's wheel button, the buttons normal (Spyro's wheel button
// focused), then (Spyro's turn unless one player plays Cynder, or two players and the pause player is the first) the
// dragon switched and the message out 2 posted, else the message out 1; then the checks. Leave (2): player 0 active,
// player 1 with two players, the effects reset, both dragons' upgrade texts. Update (0): the opening flag cleared by the
// dragon's message in, the wheel input or its animation, the gems gauge (slot 2 + dragon: the free gems' share of those
// on entering, and their count in slot 4 + dragon), the progress marker, the wheel button's visibility, the effects.
uint8_t CKS08MenuElements::OnMenuState(int32_t phase, uint8_t /*other*/) {
    CKS08GameManager* gm = Gm(this);
    if (phase == 1) {
        const uint8_t players = gm->GetPlayerCount();  // vt+0x154
        m_unk32c = 0;
        m_ui8Dragon = 0;
        m_ui8Player = 0;
        if (players == 2) {
            gm->SetPlayerActive(0, gm->m_ui8PausePlayer ^ 1);  // vt+0x184
            gm->SetPlayerActive(1, gm->m_ui8PausePlayer);
        }
        m_aui8PrevElement[1] = 0;
        m_aui8Element[0] = 0;
        m_aui8Element[1] = 0;
        m_aui8PrevElement[0] = 0;
        m_ui32ElementLevel = gm->GetElementLevel(0, 0);
        m_fTransferSoundTime = 0.0f;
        m_fTransferTime = 0.0f;
        m_vUnk248[2] = m_afUnk25c[0];
        m_vUnk248[0] = m_afUnk25c[1];
        m_vUnk248[1] = m_afUnk25c[2];
        m_vUnk280[1] = m_fUnk290;
        m_aGemsLeft[1] = Gs(this)->RtWord(0x88);
        m_aGemsAtOpen[1] = m_aGemsLeft[1];
        m_vUnk280[2] = m_fUnk294;
        m_vUnk280[0] = m_fUnk294;
        if (CBillboard2d* wheel = SlotBillboard(this, 9)) wheel->m_f32RotateAngle = k180 - m_fUnk294;
        if (m_apButtons.m_ui32NbUsedElt > 5) {
            CKInterfaceButton* button = Button(this, 5);
            if (button != nullptr && button->m_apUnk38[0] != nullptr) {
                static_cast<CBillboard2d*>(button->m_apUnk38[0])->SetTexture(static_cast<RwTexture*>(m_apTextures2ac[4 + m_aui8Element[1]]));
            }
        }
        m_vUnk274[1] = m_fUnk290;
        m_aGemsLeft[0] = Gs(this)->RtWord(0x84);
        m_aGemsAtOpen[0] = m_aGemsLeft[0];
        m_vUnk274[2] = m_fUnk294;
        m_vUnk274[0] = m_fUnk294;
        if (CBillboard2d* wheel = SlotBillboard(this, 8)) wheel->m_f32RotateAngle = m_fUnk294;
        if (m_apButtons.m_ui32NbUsedElt > 2) {
            CKInterfaceButton* button = Button(this, 2);
            if (button != nullptr && button->m_apUnk38[0] != nullptr) {
                static_cast<CBillboard2d*>(button->m_apUnk38[0])->SetTexture(static_cast<RwTexture*>(m_apTextures2ac[m_aui8Element[0]]));
            }
        }
        m_aui8FocusedItem[1] = 2;
        m_aui8FocusedItem[0] = 2;
        for (uint32_t i = 8;;) {
            CKInterfaceButton* button = Button(this, i);
            if (button != nullptr) {
                if (i == 2) {
                    Button(this, 2)->SetInteractionState(2);  // (through null with fewer than 3 buttons, as the original)
                    i = 1;
                    continue;
                }
                button->SetInteractionState(0);
            }
            if (i == 0) break;
            --i;
        }
        IKGrpHero* heroes = static_cast<IKGrpHero*>(gm->m_unk04[1]);
        bool toggle = false;
        if (heroes != nullptr) {
            IKSerializable** controlled = heroes->m_apControlledHeroes;  // 0x002ca0e0
            if (players == 1) toggle = static_cast<CKHkS08Hero*>(controlled[0])->GetDragonIndex() != 0;  // 0x00361960
            else if (players == 2) toggle = gm->m_ui8PausePlayer != 0;
            else toggle = true;
        }
        if (toggle) {
            ToggleActiveDragon();
            if (VfC0()[2] != nullptr) static_cast<CKFlashMessageOut*>(VfC0()[2])->PostFlashMessage();
        } else if (VfC0()[1] != nullptr) {
            static_cast<CKFlashMessageOut*>(VfC0()[1])->PostFlashMessage();
        }
        const uint8_t dragon = m_ui8Dragon;
        m_unk240 = 1;
        CheckElementLevelUp(dragon);
        RefreshTotalLevelGauge(m_ui8Dragon);
    } else if (phase == 2) {
        gm->SetPlayerActive(0, 1);
        gm->SetPlayerActive(1, gm->GetPlayerCount() == 2 ? 1 : 0);
        if (m_unk32c != 0) ResetPlayerVisualEffects(m_ui8Dragon);
        gm->UpdateDragonUpgradeText(0, 1);  // 0x00500140
        gm->UpdateDragonUpgradeText(1, 1);
    } else if (phase == 0) {
        uint8_t dragon = m_ui8Dragon;
        if (VfCC()[dragon + 6u] != 0 && m_unk240 != 0) m_unk240 = 0;
        const float* wheel = dragon == 0 ? m_vUnk274 : m_vUnk280;
        if (wheel[2] == wheel[0]) HandleElementSelectInput(dragon);
        else AnimateElementWheel(dragon);
        dragon = m_ui8Dragon;
        if (CBillboard2d* gauge = SlotBillboard(this, 2 + dragon)) {
            const uint32_t left = dragon == 0 ? Gs(this)->RtWord(0x84) : Gs(this)->RtWord(0x88);
            float share = 0.0f;
            if (m_aGemsAtOpen[dragon] != 0) share = static_cast<float>(left) / static_cast<float>(m_aGemsAtOpen[dragon]);
            SetElementScale(this, gauge, share);
            if (CText2d* count = SlotText(this, 4 + dragon)) {
                char buffer[0x110];
                std::snprintf(buffer, sizeof(buffer), "%d", static_cast<int32_t>(left));  // 0x00acb638
                count->SetTextAscii(buffer);
            }
            dragon = m_ui8Dragon;
        }
        UpdateProgressIndicator(dragon);
        Button(this, m_ui8Dragon * 3u + 2u)->UpdateVisibility(0);  // vt+0x68 (through null when absent, as the original)
        if (m_unk32c != 0) UpdatePlayerVisualEffects(m_ui8Dragon);
    }
    return static_cast<uint8_t>(GetMenuId());  // vt+0xe0
}

// 0x005538d0 CKS08MenuElements_MessageProc: the base's, then the message box's answer (0x2d00, OK): after the element's
// level-up box the total level's (GetTotalLevelUpText); after that one the gauge, the texts, the level-up feedback, sound
// 0 and the wheel button disabled while the element is full.
int32_t CKS08MenuElements::MessageProc(uint16_t message, void* data) {
    const int32_t base = CKMenuBase114c::MessageProc(message, data);  // 0x00515b78
    int32_t own = 1;
    if (message == 0x2d00) {
        own = 0;
        if (data == nullptr) {
            if (m_ui8LevelUpStep == 1) {
                MessageBox_Show(kOne, kMinusOne, this, static_cast<const CKLocText*>(GetTotalLevelUpText(m_ui8Dragon)), 1, 0,
                                nullptr);
                m_ui8LevelUpStep = 2;
            } else if (m_ui8LevelUpStep == 2) {
                RefreshTotalLevelGauge(m_ui8Dragon);
                RefreshElementTexts(m_ui8Dragon);
                PlayLevelUpFeedback(m_ui8Dragon);
                if (CKSound* sound = static_cast<CKSoundDictionaryID*>(m_pSound)->GetSound2(0)) {  // 0x00112bd8
                    sound->ResetPan(1);  // 0x00111b70
                    sound->Play(kZero);
                }
                const uint8_t dragon = m_ui8Dragon;
                CKInterfaceButton* button = Button(this, dragon * 3u + 2u);
                const uint8_t element = m_aui8Element[dragon];
                const uint32_t gems = ElementGems(this, dragon, element);
                const uint32_t cap = LevelCost(Gm(this), dragon, element, 3);
                button->SetDisabled(gems == cap ? 1 : 0);  // vt+0x84
            }
        }
    }
    if (base == 3 || own == 3) return 3;
    if (base == 2 || own == 2) return 2;
    if (base == 0) return 0;
    return own;
}

// ==== C2.8 lvl020-misc: the level-up feedback ======================================================================
// After the total level's message box (MessageProc), PlayLevelUpFeedback starts the flash FX (+0x330), a shake of the
// badge (slot 0 + dragon: CKQuakeCpntUpdater +0x33c, its scale from the shake matrix' up vector and its position) and of
// the title (slot 12 + dragon: +0x350, its text size), colour blinks of the badge, the title and the four description
// texts (16, 20, 18, 22 + dragon), the burst of slot 30 + dragon and a pad rumble; +0x32c says effects run.
// UpdatePlayerVisualEffects (every frame while +0x32c) steps them and puts each widget back once its time ran out;
// ResetPlayerVisualEffects puts them all back at once. No rand draw.
#include "k2000/components/CKQuakeCpntUpdater.h"
#include "k2000/fx/IKFx.h"
#include "k2000/graphical/ui/CFlashHotSpot.h"
#include "k2000/logic/IKFxData.h"
#include "k2000/services/CKSrvFx.h"
#include "Renderware/rwcore/RwMatrix.h"

namespace {
const float k255 = 0x1.fep+7f;  // TOC1 +0x7df0 255.0
CKQuakeCpntUpdater* Quake(IKSerializable* object) { return static_cast<CKQuakeCpntUpdater*>(object); }
float MathSqrtf(float x) { return static_cast<float>(std::sqrt(static_cast<double>(x))); }  // 0x00010690 Math_Sqrtf
float ByteDiff(uint8_t to, uint8_t from) { return static_cast<float>(static_cast<int32_t>(to) - static_cast<int32_t>(from)); }
// The widget slot's binding (vt+0x6c) told `flags` for its element: a 2D node (IsKindOfClass 0x24d) through
// SetElement2dFlags 0x00072830, else SetAtomicFlags 0x00072a08.
void SetSlotFlags(CKS08MenuElements* menu, uint32_t slot, uint32_t flags) {
    IKSerializable* element = menu->m_aWidgetSlots[slot].m_pElement;
    const uint8_t is2d = static_cast<uint8_t>(element->IsKindOfClass(0x24d));
    CFlashHotSpot* binding = static_cast<CFlashHotSpot*>(menu->GetWidgetSlots()[slot].m_pHotSpot);
    if (is2d != 0) binding->SetObjectFlags(static_cast<IKNode2d*>(element), flags);
    else binding->SetObjectFlags(element, flags);
}
// The four description texts in the original's order, with their blink index.
constexpr uint32_t kTextSlots[4] = {16, 20, 18, 22};
// The inlined start of a blink (in Color_StartBlinkFade_maybe and Color_UpdateBlinkFade_maybe): the current colour set
// to `from` (bytes and floats; alpha twice), the speed to cover the distance to `to` in `period`, the target `to`.
void StartFade(float period, CKS08MenuElements::ColorBlink* fade, const uint8_t* from, const uint8_t* to);
}  // namespace

// 0x0054b2e0 Color_ComputeFadeSpeed_maybe: the distance between the two colours (channels 1, 0, 2, 3 summed with
// fmadds) over `period`, over 255.
static float ColorComputeFadeSpeed(float period, const uint8_t* from, const uint8_t* to) {
    const float d1 = ByteDiff(to[1], from[1]);
    const float d0 = ByteDiff(to[0], from[0]);
    const float d2 = ByteDiff(to[2], from[2]);
    const float d3 = ByteDiff(to[3], from[3]);
    float sum = d1 * d1;
    sum = ppc::fmadds(d0, d0, sum);
    sum = ppc::fmadds(d2, d2, sum);
    sum = ppc::fmadds(d3, d3, sum);
    return MathSqrtf(sum) / period / k255;
}

namespace {
void StartFade(float period, CKS08MenuElements::ColorBlink* fade, const uint8_t* from, const uint8_t* to) {
    std::memcpy(fade->m_aCurrent, from, 4);
    for (int i = 0; i < 4; ++i) fade->m_afCurrent[i] = static_cast<float>(fade->m_aCurrent[i]);
    fade->m_aCurrent[3] = from[3];
    fade->m_afCurrent[3] = static_cast<float>(from[3]);
    uint8_t a[4], b[4];  // the original's word copies
    std::memcpy(a, from, 4);
    std::memcpy(b, to, 4);
    fade->m_fSpeed = ColorComputeFadeSpeed(period, a, b);
    std::memcpy(fade->m_aTarget, to, 4);
    fade->m_aTarget[3] = to[3];
}
}  // namespace

// 0x00550030 Color_StartBlinkFade_maybe: the blink's phase 1, then the fade from `from` towards `to` (`unused` is not
// read). PlayLevelUpFeedback inlines it.
static void ColorStartBlinkFade(float period, CKS08MenuElements::ColorBlink* fade, const uint8_t* from, const uint8_t* to,
                                uint8_t* phase) {
    *phase = 1;
    StartFade(period, fade, from, to);
}

// 0x0054ea08 Color_UpdateBlinkFade_maybe (r3, the menu, is not read): every `period` seconds the blink turns (phase 0:
// from `a` towards `b`, phase 1: back), then the current colour moves towards its target by dt x speed x 255 (or
// reaches it).
static void ColorUpdateBlinkFade(float period, float dt, CKS08MenuElements::ColorBlink* fade, const uint8_t* a,
                                 const uint8_t* b, uint8_t* phase, float* time) {
    *time = dt + *time;  // fadds
    if (*time > period) {  // ble skips (NaN keeps the phase)
        *time = 0.0f;
        if (*phase == 0) {
            *phase = 1;
            StartFade(period, fade, a, b);
        } else {
            *phase = 0;
            StartFade(period, fade, b, a);
        }
    }
    if (std::memcmp(fade->m_aCurrent, fade->m_aTarget, 4) == 0) return;
    const float d1 = static_cast<float>(fade->m_aTarget[1]) - fade->m_afCurrent[1];
    const float d0 = static_cast<float>(fade->m_aTarget[0]) - fade->m_afCurrent[0];
    const float d2 = static_cast<float>(fade->m_aTarget[2]) - fade->m_afCurrent[2];
    const float d3 = static_cast<float>(fade->m_aTarget[3]) - fade->m_afCurrent[3];
    const float step = (dt * fade->m_fSpeed) * k255;
    float dist2 = d1 * d1;
    dist2 = ppc::fmadds(d0, d0, dist2);
    dist2 = ppc::fmadds(d2, d2, dist2);
    dist2 = ppc::fmadds(d3, d3, dist2);
    if (step * step > dist2) {  // ble takes the step (NaN too)
        std::memcpy(fade->m_aCurrent, fade->m_aTarget, 4);
        return;
    }
    const float scale = step * rwInvSqrt(dist2);  // 0x000114d8 Math_InvSqrtf
    fade->m_afCurrent[0] = ppc::fmadds(d0, scale, fade->m_afCurrent[0]);
    fade->m_afCurrent[1] = ppc::fmadds(d1, scale, fade->m_afCurrent[1]);
    fade->m_afCurrent[2] = ppc::fmadds(d2, scale, fade->m_afCurrent[2]);
    fade->m_afCurrent[3] = ppc::fmadds(d3, scale, fade->m_afCurrent[3]);
    fade->m_aCurrent[0] = static_cast<uint8_t>(ppc::fctiwz(fade->m_afCurrent[0]));
    fade->m_aCurrent[3] = static_cast<uint8_t>(ppc::fctiwz(fade->m_afCurrent[3]));
    fade->m_aCurrent[1] = static_cast<uint8_t>(ppc::fctiwz(fade->m_afCurrent[1]));
    fade->m_aCurrent[2] = static_cast<uint8_t>(ppc::fctiwz(fade->m_afCurrent[2]));
}

// 0x0054b3b0 CKS08MenuElements_ResetPlayerVisualEffects_maybe: the effects off (+0x32c), the shakes stopped with the
// badge's scale 1 and position and the title's size and position back, the colours back and the bindings told 0x1000.
void CKS08MenuElements::ResetPlayerVisualEffects(uint8_t dragon) {
    m_unk32c = 0;
    const uint32_t badge = dragon;
    const uint32_t title = 12u + dragon;
    if (m_aWidgetSlots[badge].m_pElement != nullptr) {
        m_fBadgeShakeTime = 0.0f;
        Quake(m_pQuakeUpdater33c)->Stop();  // 0x0024f738
        if (CBillboard2d* element = SlotBillboard(this, badge)) SetElementScale(this, element, kOne);
        SetElementX(m_fBadgeX, badge);  // vt+0x7c
        SetElementY(m_fBadgeY, badge);  // vt+0x80
    }
    if (m_aWidgetSlots[title].m_pElement != nullptr) {
        m_fTitleShakeTime = 0.0f;
        Quake(m_pQuakeUpdater350)->Stop();
        static_cast<IKText2d*>(SlotText(this, title))->SetFontHeight(m_fTitleHeight);  // 0x0006b530
        SetElementX(m_fTitleX, title);
        SetElementY(m_fTitleY, title);
    }
    if (m_aWidgetSlots[badge].m_pElement != nullptr) {
        SlotBillboard(this, badge)->SetColor(m_aBadgeColor);  // IKBillboard2d vt+0x28
        SetSlotFlags(this, badge, 0x1000);
    }
    if (m_aWidgetSlots[title].m_pElement != nullptr) {
        SlotText(this, title)->SetColor(m_aTitleColor);  // IKText2d vt+0x44
        SetSlotFlags(this, title, 0x1000);
    }
    for (uint32_t i = 0; i < 4; ++i) {
        const uint32_t slot = kTextSlots[i] + dragon;
        if (m_aWidgetSlots[slot].m_pElement == nullptr) continue;
        SlotText(this, slot)->SetColor(m_aaTextColor[i]);
        SetSlotFlags(this, slot, 0x1000);
    }
}

// 0x0054eee8 CKS08MenuElements_UpdatePlayerVisualEffects_maybe: with effects on, each one stepped by the frame's dt and
// +0x32c set again while any runs: the badge's shake (scale = the length of the shake matrix' up vector, position + its
// translation) until the quake's duration, then the badge back; the title's (size x that length) likewise; the
// badge's and the title's colour blinks until their durations (+0x388 / +0x3c0), then their colours back and the
// bindings told 0x1000; the description texts' blinks until +0x458, then their colours back and the bindings told 0x100.
void CKS08MenuElements::UpdatePlayerVisualEffects(uint8_t dragon) {
    const float dt = FrameDt();
    if (m_unk32c == 0) return;
    m_unk32c = 0;
    const uint32_t badge = dragon;
    const uint32_t title = 12u + dragon;
    float out[15];
    CMatrix34 shake;
    if (m_aWidgetSlots[badge].m_pElement != nullptr) {
        m_fBadgeShakeTime = dt + m_fBadgeShakeTime;
        if (static_cast<CKQuakeCpnt*>(m_pQuake338)->m_fDuration > m_fBadgeShakeTime) {  // ble: NaN ends it
            m_unk32c = 1;
            Quake(m_pQuakeUpdater33c)->EvaluateScaled(dt, kOne, out);  // 0x0024f5c8
            ShakeSample_BuildMatrix(Quake(m_pQuakeUpdater33c), out, &shake, nullptr);  // 0x0024ee90
            CBillboard2d* element = SlotBillboard(this, badge);
            float length = shake.m_up.y * shake.m_up.y;
            length = ppc::fmadds(shake.m_up.x, shake.m_up.x, length);
            length = MathSqrtf(ppc::fmadds(shake.m_up.z, shake.m_up.z, length));
            if (element != nullptr) SetElementScale(this, element, length);
            SetElementX(shake.m_pos.x + m_fBadgeX, badge);
            SetElementY(shake.m_pos.y + m_fBadgeY, badge);
        } else {
            m_fBadgeShakeTime = 0.0f;
            Quake(m_pQuakeUpdater33c)->Stop();
            if (CBillboard2d* element = SlotBillboard(this, badge)) SetElementScale(this, element, kOne);
            SetElementX(m_fBadgeX, badge);
            SetElementY(m_fBadgeY, badge);
        }
    }
    m_fTitleShakeTime = dt + m_fTitleShakeTime;
    if (m_aWidgetSlots[title].m_pElement != nullptr) {
        if (static_cast<CKQuakeCpnt*>(m_pQuake34c)->m_fDuration > m_fTitleShakeTime) {
            m_unk32c = 1;
            Quake(m_pQuakeUpdater350)->EvaluateScaled(dt, kOne, out);
            ShakeSample_BuildMatrix(Quake(m_pQuakeUpdater350), out, &shake, nullptr);
            CText2d* text = SlotText(this, title);
            const float height = m_fTitleHeight;
            float length = shake.m_up.y * shake.m_up.y;
            length = ppc::fmadds(shake.m_up.x, shake.m_up.x, length);
            length = MathSqrtf(ppc::fmadds(shake.m_up.z, shake.m_up.z, length));
            static_cast<IKText2d*>(text)->SetFontHeight(height * length);
            SetElementX(m_fTitleX + shake.m_pos.x, title);
            SetElementY(m_fTitleY + shake.m_pos.y, title);
        } else {
            m_fTitleShakeTime = 0.0f;
            Quake(m_pQuakeUpdater350)->Stop();
            static_cast<IKText2d*>(SlotText(this, title))->SetFontHeight(m_fTitleHeight);
            SetElementX(m_fTitleX, title);
            SetElementY(m_fTitleY, title);
        }
    }
    if (m_aWidgetSlots[badge].m_pElement != nullptr) {
        m_fBadgeBlinkTotal = dt + m_fBadgeBlinkTotal;
        if (m_unk388 > m_fBadgeBlinkTotal) {  // bgt
            m_unk32c = 1;
            uint8_t a[4], b[4];
            std::memcpy(a, m_aBadgeColor, 4);
            std::memcpy(b, m_unk380, 4);
            ColorUpdateBlinkFade(m_unk384, dt, &m_badgeBlink, a, b, &m_ui8BadgeBlinkOn, &m_fBadgeBlinkTime);
            SlotBillboard(this, badge)->SetColor(m_badgeBlink.m_aCurrent);
        } else {
            SlotBillboard(this, badge)->SetColor(m_aBadgeColor);
            SetSlotFlags(this, badge, 0x1000);
        }
    }
    if (m_aWidgetSlots[title].m_pElement != nullptr) {
        m_fTitleBlinkTotal = dt + m_fTitleBlinkTotal;
        if (m_fUnk3c0 > m_fTitleBlinkTotal) {  // bgt
            m_unk32c = 1;
            uint8_t a[4], b[4];
            std::memcpy(a, m_aTitleColor, 4);
            std::memcpy(b, m_unk3b8, 4);
            ColorUpdateBlinkFade(m_fUnk3bc, dt, &m_titleBlink, a, b, &m_ui8TitleBlinkOn, &m_fTitleBlinkTime);
            SlotText(this, title)->SetColor(m_titleBlink.m_aCurrent);
        } else {
            SlotText(this, title)->SetColor(m_aTitleColor);
            SetSlotFlags(this, title, 0x1000);
        }
    }
    m_fTextBlinkTotal = dt + m_fTextBlinkTotal;
    if (m_fUnk458 > m_fTextBlinkTotal) {  // ble: NaN ends it
        m_unk32c = 1;
        for (uint32_t i = 0; i < 4; ++i) {
            const uint32_t slot = kTextSlots[i] + dragon;
            if (m_aWidgetSlots[slot].m_pElement == nullptr) continue;
            uint8_t a[4], b[4];
            std::memcpy(a, m_aaTextColor[i], 4);
            std::memcpy(b, m_unk450, 4);
            ColorUpdateBlinkFade(m_fUnk454, dt, &m_aTextBlink[i], a, b, &m_aui8TextBlinkOn[i], &m_afTextBlinkTime[i]);
            SlotText(this, slot)->SetColor(m_aTextBlink[i].m_aCurrent);
        }
    } else {
        for (uint32_t i = 0; i < 4; ++i) {
            const uint32_t slot = kTextSlots[i] + dragon;
            if (m_aWidgetSlots[slot].m_pElement == nullptr) continue;
            SlotText(this, slot)->SetColor(m_aaTextColor[i]);
            SetSlotFlags(this, slot, 0x100);
        }
    }
}

// 0x00552240 CKS08MenuElements_PlayLevelUpFeedback_maybe: the effects on; the flash FX data (+0x330) started through the
// FX service (CKSrvFx::StartEffect inlined, owned by the menu) and kept updating while paused; the badge's shake
// (re)started from its position; the title's from its size (BUG(original): slot 13's text size for both dragons: the
// compiled test is on the slot index 12 / 13, never 0) and position; the colour blinks started from the widgets'
// colours, the bindings told 0x10000; the burst of slot 30 + dragon; the rumble.
void CKS08MenuElements::PlayLevelUpFeedback(uint8_t dragon) {
    m_unk32c = 1;
    if (CKSrvFx* fx = static_cast<CKSrvFx*>(g_pEngine->m_srvFx)) {
        IKFx* effect = fx->StartEffect(static_cast<IKFxData*>(m_pFlashFx), this);
        if (effect != nullptr) effect->SetUpdateWhenPaused(1);  // vt+0x90
    }
    const uint32_t badge = dragon;
    const uint32_t title = 12u + dragon;
    if (m_aWidgetSlots[badge].m_pElement != nullptr) {
        if (Quake(m_pQuakeUpdater33c)->m_bRunning != 0) Quake(m_pQuakeUpdater33c)->Stop();
        Quake(m_pQuakeUpdater33c)->Start();  // 0x0024f770
        m_fBadgeShakeTime = 0.0f;
        m_fBadgeX = GetElementX(badge);  // vt+0x70
        m_fBadgeY = GetElementY(badge);  // vt+0x74
    }
    if (Quake(m_pQuakeUpdater350)->m_bRunning != 0) Quake(m_pQuakeUpdater350)->Stop();
    Quake(m_pQuakeUpdater350)->Start();
    m_fTitleShakeTime = 0.0f;
    m_fTitleHeight = static_cast<IKText2d*>(SlotText(this, 13))->m_f32TextSize;  // BUG(original): slot 13 always
    m_fTitleX = GetElementX(title);
    m_fTitleY = GetElementY(title);
    if (m_aWidgetSlots[badge].m_pElement != nullptr) {
        m_fBadgeBlinkTime = 0.0f;
        m_fBadgeBlinkTotal = 0.0f;
        std::memcpy(m_aBadgeColor, &static_cast<IKBillboard2d*>(SlotBillboard(this, badge))->m_Color, 4);
        ColorStartBlinkFade(m_unk384, &m_badgeBlink, m_aBadgeColor, m_unk380, &m_ui8BadgeBlinkOn);
        SetSlotFlags(this, badge, 0x10000);
        SlotBillboard(this, badge)->SetColor(m_badgeBlink.m_aCurrent);
    }
    if (m_aWidgetSlots[title].m_pElement != nullptr) {
        m_fTitleBlinkTime = 0.0f;
        m_fTitleBlinkTotal = 0.0f;
        std::memcpy(m_aTitleColor, &static_cast<IKText2d*>(SlotText(this, title))->m_Color, 4);
        ColorStartBlinkFade(m_fUnk3bc, &m_titleBlink, m_aTitleColor, m_unk3b8, &m_ui8TitleBlinkOn);
        SetSlotFlags(this, title, 0x10000);
        SlotText(this, title)->SetColor(m_titleBlink.m_aCurrent);
    }
    m_fTextBlinkTotal = 0.0f;
    for (uint32_t i = 0; i < 4; ++i) {
        const uint32_t slot = kTextSlots[i] + dragon;
        if (m_aWidgetSlots[slot].m_pElement == nullptr) continue;
        m_afTextBlinkTime[i] = 0.0f;
        std::memcpy(m_aaTextColor[i], &static_cast<IKText2d*>(SlotText(this, slot))->m_Color, 4);
        ColorStartBlinkFade(m_fUnk454, &m_aTextBlink[i], m_aaTextColor[i], m_unk450, &m_aui8TextBlinkOn[i]);
        SlotText(this, slot)->SetColor(m_aTextBlink[i].m_aCurrent);
        SetSlotFlags(this, slot, 0x10000);
    }
    if (CParticlesNodeFx* burst = static_cast<CParticlesNodeFx*>(m_aWidgetSlots[30u + dragon].m_pElement)) {
        burst->m_sgProperties = ((((burst->m_sgProperties | 0x40000u) | 0x200u) | 0x400u) & ~0x80000u);
        burst->m_fEmissionSpeedAdjustment = 0.0f;
        burst->m_pRpPrtStdEmitter->flag |= rpPRTSTDEMITTERFLAGACTIVE | rpPRTSTDEMITTERFLAGEMIT;
    }
    g_pEngine->m_input->AddRumbleRequest(m_fUnk48c, this, 1, 0, m_unk488, m_unk489);  // 0x001049d8
}

// 0x0054bea8 CKS08MenuElements_RecursiveRegistration: the referenced objects' registration, then the base.
void CKS08MenuElements::RecursiveRegistration(int32_t type) {
    m_pText2a0->RecursiveRegistration(type);
    m_pText2a4->RecursiveRegistration(type);
    m_pFlashFx->RecursiveRegistration(type);
    m_pQuake338->RecursiveRegistration(type);
    m_pQuakeUpdater33c->RecursiveRegistration(type);
    m_pQuake34c->RecursiveRegistration(type);
    m_pQuakeUpdater350->RecursiveRegistration(type);
    m_pSound->RecursiveRegistration(type);
    CKMenuBase114c::RecursiveRegistration(type);
}

// ==== port-all P13 ==================================================================================================

// 0x0054b040 CKS08MenuElements_ComputeElementRank_maybe
void CKS08MenuElements::ComputeElementRank(uint8_t dragon, uint32_t* rank, uint32_t* rest) {
    *rank = 0;
    *rest = 0;
    *rank = TotalLevelTier(this, dragon, rest);  // the elements 3, 2, 1, 0 (GetElementLevel 0x4f9558), tiers of 3, 4, 5...
}

// 0x0054b160 CKS08MenuElements_UpdateUpgradePointsDisplay_maybe: u32 conversions (fcfid), 0.0 without gems on entering.
void CKS08MenuElements::UpdateUpgradePointsDisplay(uint8_t dragon) {
    CBillboard2d* bar = SlotBillboard(this, 2u + dragon);
    if (bar == nullptr) return;
    const uint32_t gems = Gs(this)->RtWord(dragon == 0 ? 0x84u : 0x88u);
    float ratio = 0.0f;
    if (m_aGemsAtOpen[dragon] != 0) {
        ratio = static_cast<float>(static_cast<double>(gems)) / static_cast<float>(static_cast<double>(m_aGemsAtOpen[dragon]));
    }
    SetElementScale(this, bar, ratio);
    CText2d* count = SlotText(this, 4u + dragon);
    if (count == nullptr) return;
    char buffer[0x118];
    std::snprintf(buffer, sizeof(buffer), "%d", static_cast<int32_t>(gems));  // 0x0098d3b0 FormatString, 0x00acb638
    count->SetTextAscii(buffer);  // vt+0x90
}
