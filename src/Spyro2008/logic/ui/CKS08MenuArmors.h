// CKS08MenuArmors.h - the "Menu Armors" screen (key 0xab8c, vtable 0xb2c130, size 0x1c4 from 0x542980 CKS08MenuArmors_Create). DotD only.
// Original unit: CKS08MenuArmors.cpp (0x541ff8-0x547150).
#pragma once
#include <cstdint>

#include "Spyro2008/logic/CKMenuBase114c.h"
#include "k2000/core/Layout.h"

class CKS08MenuArmors : public CKMenuBase114c {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x2ae)
    DOTD_DECLARE_FACTORIES(CKS08MenuArmors)

    CKS08MenuArmors() {}  // 0x542980 CKS08MenuArmors_Create: the CKMenuBase114c part only
    int32_t IsKindOfClass(uint32_t key) override {  // vt+0x08 0x9c9618
        return key == 0xab8c || key == 0x114c || key == 0x730c || key == 0xc;
    }
    int32_t Load(IKFile* file, int32_t type) override;                                   // vt+0x2c 0x542a68 CKS08MenuArmors_Load
    void RecursiveRegistration(int32_t type) override;                                  // vt+0x24 0x542390 CKS08MenuArmors_RecursiveRegistration
    void Destroy() override;  // vt+0x10 0x00542428 CKS08MenuArmors_Destroy: the base's, then the textures +0x1b8, +0x1b4
    uint32_t GetWidgetSlotCount() override { return 8; }                                 // vt+0x68 0x9c9678
    WidgetSlot* GetWidgetSlots() override { return m_aWidgetSlots; }                     // vt+0x6c 0x9c9680
    uint8_t Vf84() override { return 1; }                                                // vt+0x84 0x9c96e0
    RefGroup* Vf88() override { return m_aRefGroups; }                                   // vt+0x88 0x9c96e8
    IKSerializable** Vf8C(uint32_t group) override { return group == 0 ? m_apGroupRefs : nullptr; }  // vt+0x8c 0x541d18
    GroupState* Vf90(uint32_t group) override { return group == 0 ? m_aGroupStates : nullptr; }  // vt+0x90 0x541d30
    const char* GetMenuName() override { return "Menu Armors"; }                         // vt+0xb8 0x9c9668
    uint8_t VfBC() override { return 25; }                                               // vt+0xbc 0x9c96b8
    IKSerializable** VfC0() override { return m_apMessageOuts; }                         // vt+0xc0 0x9c96c0
    uint8_t VfC4() override { return 8; }                                                // vt+0xc4 0x9c9690
    IKSerializable** VfC8() override { return m_apMessageIns; }                          // vt+0xc8 0x9c9698
    uint8_t* VfCC() override { return m_abMessageInFlags; }                              // vt+0xcc 0x9c96a8
    int32_t GetMenuId() override { return 0x0; }                                         // vt+0xe0 0x9c9670
    uint8_t VfF0() override { return 1; }                                                // vt+0xf0 0x9c96d0
    uint8_t VfF4() override { return 18; }                                               // vt+0xf4 0x9c96d8 the back item
    // vt+0xdc 0x005468d0 SetArmors (Ghidra's name; the page's OnMenuState): 1 enter, 0 update, 2 leave (the chosen armours
    // written to the game structure).
    uint8_t OnMenuState(int32_t phase, uint8_t other) override;

    // 0x00543898 CKS08MenuArmors_RefreshDragonPanelItems_maybe: the dragon's nine armour items (the chosen ones with the
    // equipped texture), the slot texts and the full-set text; `opening` keeps the full-set animation from starting.
    void RefreshDragonPanelItems(uint8_t dragon, int32_t opening);
    // 0x00544938 CKS08MenuArmors_ToggleActiveDragonPanel_maybe
    void ToggleActiveDragonPanel();
    // 0x00544bb0 CKS08MenuArmors_HandleSlotInput_maybe
    void HandleSlotInput();
    // 0x00545360 CKS08MenuArmors_UpdateSlotAnimations_maybe
    void UpdateSlotAnimations(uint8_t dragon);

    WidgetSlot m_aWidgetSlots[8];                // +0x94
    IKSerializable* m_apMessageIns[8];           // +0xd4
    uint8_t m_abMessageInFlags[8];               // +0xf4 MessageProc sets one per VfC8 entry
    IKSerializable* m_apMessageOuts[25];         // +0xfc
    // +0x160..+0x17f the page's run state (C2.8 live-fixes; names ours). The Load clears +0x160..+0x162.
    uint8_t m_ui8Dragon;                         // +0x160 the dragon whose panel is active (0 Spyro, 1 Cynder)
    uint8_t m_ui8Player;                         // +0x161 the player browsing it (the panel's player with two players)
    uint8_t m_ui8Switched;                       // +0x162 a panel switch ran (ToggleActiveDragonPanel); cleared by message in [6 + dragon]
    uint8_t m_aui8FullSet[2];                    // +0x163 per dragon: the armour of a full set (all three slots), 3 none
    uint8_t m_aaui8Equipped[2][3];               // +0x165 per dragon and slot: the armour chosen on the page (3 none)
    uint8_t m_ui8SetAnim;                        // +0x16b the full-set animation runs (UpdateSlotAnimations)
    uint8_t m_unk16c[4];                         // +0x16c no access seen
    float m_fSetAnimTime;                        // +0x170 the full-set animation's time
    float m_fUnk174;                             // +0x174 the full-set animation's duration (read by the Load)
    uint8_t m_abSetAnimStep[3];                  // +0x178 the animation's three steps done (slots 0, 2, 1)
    uint8_t m_pad17b;
    uint32_t m_ui32Selection;                    // +0x17c the player's selection on opening (stw of a byte; not read)
    RefGroup m_aRefGroups[1];                    // +0x180
    IKSerializable* m_apGroupRefs[3];            // +0x190 Vf8C(0); the Load clears [m_unk04, m_unk08)
    GroupState m_aGroupStates[3];                // +0x19c Vf90(0); the Load clears the first m_unk08
    void* m_pTexture1b4;                         // +0x1b4 IKFile_ReadTextureRef
    void* m_pTexture1b8;                         // +0x1b8 IKFile_ReadTextureRef (read before +0x1b4)
    IKSerializable* m_pText;                     // +0x1bc CKLocTextAccessor (struct draft)
    IKSerializable* m_pSound;                    // +0x1c0 CKSoundDictionaryID (struct draft)
};
DOTD_ASSERT_SIZE(CKS08MenuArmors, 0x1c4);
DOTD_ASSERT_OFFSET(CKS08MenuArmors, m_aWidgetSlots, 0x94);
DOTD_ASSERT_OFFSET(CKS08MenuArmors, m_apMessageIns, 0xd4);
DOTD_ASSERT_OFFSET(CKS08MenuArmors, m_abMessageInFlags, 0xf4);
DOTD_ASSERT_OFFSET(CKS08MenuArmors, m_apMessageOuts, 0xfc);
DOTD_ASSERT_OFFSET(CKS08MenuArmors, m_ui8Dragon, 0x160);
DOTD_ASSERT_OFFSET(CKS08MenuArmors, m_aui8FullSet, 0x163);
DOTD_ASSERT_OFFSET(CKS08MenuArmors, m_aaui8Equipped, 0x165);
DOTD_ASSERT_OFFSET(CKS08MenuArmors, m_ui8SetAnim, 0x16b);
DOTD_ASSERT_OFFSET(CKS08MenuArmors, m_fSetAnimTime, 0x170);
DOTD_ASSERT_OFFSET(CKS08MenuArmors, m_abSetAnimStep, 0x178);
DOTD_ASSERT_OFFSET(CKS08MenuArmors, m_ui32Selection, 0x17c);
DOTD_ASSERT_OFFSET(CKS08MenuArmors, m_fUnk174, 0x174);
DOTD_ASSERT_OFFSET(CKS08MenuArmors, m_aRefGroups, 0x180);
DOTD_ASSERT_OFFSET(CKS08MenuArmors, m_apGroupRefs, 0x190);
DOTD_ASSERT_OFFSET(CKS08MenuArmors, m_aGroupStates, 0x19c);
DOTD_ASSERT_OFFSET(CKS08MenuArmors, m_pTexture1b4, 0x1b4);
DOTD_ASSERT_OFFSET(CKS08MenuArmors, m_pTexture1b8, 0x1b8);
DOTD_ASSERT_OFFSET(CKS08MenuArmors, m_pText, 0x1bc);
DOTD_ASSERT_OFFSET(CKS08MenuArmors, m_pSound, 0x1c0);
