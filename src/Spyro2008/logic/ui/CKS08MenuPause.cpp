// CKS08MenuPause.cpp - reconstructed original translation unit 0x55da70-0x55f7a0 (GAME_TOC2, main_toc2), 24 functions, 20 live.
// Primary class: CKS08MenuPause  key 0x838c  category Logic  size ?  vtable 0xb2cfa0
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x55da70  CKS08MenuPause_Delete
//   [ ] 0x55dac0  CKS08MenuPause_Construct  [dead]
//   [ ] 0x55db68  CKS08MenuPause_ClearInputStateFields_maybe  [dead]
//   [ ] 0x55db98  CKS08MenuPause_CheckButtonPairPressed_maybe  [dead]
//   [x] 0x55dd18  CKS08MenuPause_ApplyCheatCode_maybe
//   [x] 0x55e028  CKS08MenuPause_MessageProc
//   [x] 0x55e208  CKS08MenuPause_Load
//   [ ] 0x55e2e8  CKS08MenuPause_Save
//   [x] 0x55e3c8  CKS08MenuPause_RecursiveRegistration
//   [x] 0x55e438  CKS08MenuPause_Destroy  (inherited: TocBridge_CKMenuBase_114c_maybe_Destroy)
//   [x] 0x55e460  CKS08MenuPause_DeleteArray
//   [ ] 0x55e508  RegisterCKS08MenuPauseClass
//   [ ] 0x55e590  _GLOBAL__D_55e590
//   [ ] 0x55e5a0  _GLOBAL__I_55e5a0
//   [x] 0x55e5b0  CKS08MenuPause_vfEC
//   [x] 0x55e6b0  CKS08MenuPause_OnItemEvent
//   [ ] 0x55e8f8  CKS08MenuPause_Construct_2  [dead]
//   [x] 0x55e9a0  CKS08MenuPause_Create
//   [x] 0x55ea88  CKS08MenuPause_CreateArray
//   [x] 0x55ebd0  CKS08MenuPause_UpdateCheatInput_maybe
//   [x] 0x55ef18  CKS08MenuPause_Destructor
//   [x] 0x55f050  CKS08MenuPause_Destructor_2
//   [x] 0x55f188  CKS08MenuPause_DeletingDestructor
//   [x] 0x55f2c0  CKS08MenuPause_OnStatePhase
//
//   [x] 0x9ca0a0  CKS08MenuPause_IsKindOfClass  [inline]
//   [x] 0x9ca0e0  CKS08MenuPause_GetClassType  [inline]
//   [x] 0x9ca0e8  CKS08MenuPause_GetClassID  [inline]
//   [x] 0x9ca0f0  CKS08MenuPause_vfB8  [inline]
//   [x] 0x9ca0f8  CKS08MenuPause_GetMenuId  [inline]
//   [x] 0x9ca100  CKS08MenuPause_GetWatchedMessageCount  [inline]
//   [x] 0x9ca108  CKS08MenuPause_GetWatchedMessageIds  [inline]
//   [x] 0x9ca118  CKS08MenuPause_GetMessageFlags  [inline]
//   [x] 0x9ca128  CKS08MenuPause_vfBC  [inline]
//   [x] 0x9ca130  CKS08MenuPause_vfC0  [inline]
//   [x] 0x9ca140  CKS08MenuPause_GetWidgetSlotCount  [inline]
//   [x] 0x9ca148  CKS08MenuPause_GetWidgetSlots  [inline]
//   [x] 0x9ca158  CKS08MenuPause_HasBackItem  [inline]
//   [x] 0x9ca160  CKS08MenuPause_GetBackItemIndex  [inline]
//
// The destructors are the implicit one (only CKMenuBase114c's, inlined there). Save waits for the base menu's own
// Save (0x98f730 bridge), not ported (the menus are not saved).
#include "Spyro2008/logic/ui/CKS08MenuPause.h"

#include <cstdint>

#include "Spyro2008/logic/CKS08GameManager.h"
#include "k2000/components/CKLocTextAccessor.h"
#include "k2000/dictionaries/CKSoundDictionaryID.h"
#include "k2000/io/IKFile.h"
#include "k2000/logic/CKInterfaceButtonDouble.h"
#include "k2000/logic/sound/CKSound.h"
#include "k2000/logic/ui/CKLocText.h"
#include "k2000/misc/Engine.h"
#include "k2000/misc/JobQueue.h"
#include "k2000/system/CTimeManager.h"
#include "k2000/system/IKTime.h"

namespace {
// 0x00c40c98 (TOC2 -0x7c74): each cheat code's held action (7 bytes), then (+7) its five steps.
const uint8_t kCheatFirst[7] = {6, 8, 8, 7, 7, 6, 6};
const uint8_t kCheatSteps[7][5] = {
    {0xb, 0xb, 0xd, 0xd, 0xa}, {0xc, 0xb, 0xc, 0xa, 0xd}, {0xc, 0xa, 0xa, 0xd, 0xc}, {0xd, 0xb, 0xa, 0xa, 0xa},
    {0xd, 0xa, 0xb, 0xb, 0xb}, {0xa, 0xc, 0xd, 0xc, 0xb}, {0xa, 0xd, 0xd, 0xc, 0xc},
};

CKS08GameManager* GameManager(CKS08MenuPause* menu) { return static_cast<CKS08GameManager*>(menu->m_pGameManager); }

// The first button (item 0, the two-part resume item), null without buttons.
CKInterfaceButtonDouble* FirstButton(CKS08MenuPause* menu) {
    if (menu->m_apButtons.m_ui32NbUsedElt == 0) return nullptr;
    return static_cast<CKInterfaceButtonDouble*>(menu->m_apButtons.m_pBlock[0]);
}

// The game manager's text accessor's text `index`, or its single text without a list (no null test of the accessor).
const CKLocText* AccessorText(IKSerializable* accessor, uint32_t index) {
    CKLocTextAccessor* texts = static_cast<CKLocTextAccessor*>(accessor);
    if (texts->m_texts.m_pBlock != nullptr) return static_cast<const CKLocText*>(texts->m_texts.m_pBlock[index]);
    return static_cast<const CKLocText*>(texts->m_pText);
}

CKSound* MenuSound(CKS08MenuPause* menu, uint32_t index) {
    return static_cast<CKSoundDictionaryID*>(menu->m_pSound)->GetSound2(index);  // 0x112bd8
}
}  // namespace

// 0x0055e208 CKS08MenuPause_Load: no type test of its own, so its fields are read whatever the type.
int32_t CKS08MenuPause::Load(IKFile* file, int32_t type) {
    CKMenuBase114c::Load(file, type);
    IKFile_ReadRef(file, &m_pSound);
    return 1;
}

// 0x0055dd18 CKS08MenuPause_ApplyCheatCode_maybe. The bit toggles are read-modify-writes of the word (or of its top byte
// for bit 24), the same as an exclusive or.
void CKS08MenuPause::ApplyCheatCode(uint8_t code) {
    CKS08GameManager* manager = GameManager(this);
    switch (code) {
    case 0: manager->m_flags64 ^= 0x100u; break;      // bit 8
    case 1: manager->m_flags64 ^= 0x800000u; break;   // bit 23
    case 2: manager->CheatMaxUpgradePoints(); break;  // 0x500880
    case 3: manager->m_unkAFC ^= 0x100u; break;       // +0xafc bit 8
    case 4: manager->m_flags64 ^= 0x4000000u; break;  // bit 26
    case 5:
        manager->m_flags64 ^= 0x2000000u;  // bit 25
        for (int32_t dragon = 0; dragon != 2; ++dragon) {
            manager->RestoreDragonHealth(dragon, 100000, 1);  // 0x4fdef8
            manager->RestoreDragonMana(dragon, 100000, 1);    // 0x4fdca8
            if ((manager->m_flags64 & 0x2000000u) != 0) {
                manager->SetEquippedArmor(static_cast<uint8_t>(dragon), 0, 0);  // 0x4fd480
                manager->SetEquippedArmor(static_cast<uint8_t>(dragon), 1, 0);
                manager->SetEquippedArmor(static_cast<uint8_t>(dragon), 2, 0);
            }
        }
        break;
    case 6: {
        manager->m_flags64 ^= 0x1000000u;  // bit 24 (IsFuryGaugeFull_maybe's cheat flag)
        uint32_t capacity = 1;
        manager->IsFuryGaugeFull(&capacity);  // 0x4fe148: the cap into `capacity`
        manager->AddDragonFury(0, capacity);  // 0x4fd528
        manager->AddDragonFury(1, capacity);
        break;
    }
    default: break;
    }
    CKSound* sound = static_cast<CKSoundDictionaryID*>(manager->m_unkBDC)->GetSound2(0xb);  // 0x112bd8
    if (sound == nullptr) return;
    sound->ResetPan(1);  // 0x111b70
    sound->Play(0.0f);   // 0x111230; TOC2 -0x7ccc
}

// 0x0055e028 CKS08MenuPause_MessageProc
int32_t CKS08MenuPause::MessageProc(uint16_t message, void* data) {
    const int32_t base = CKMenuBase114c::MessageProc(message, data);  // 0x515b78 KBase730C_MessageProc
    int32_t own = 1;
    if (message == 0x2d00) {
        own = 0;
        if (static_cast<int32_t>(reinterpret_cast<intptr_t>(data)) == 5) {
            CKS08GameManager* manager = GameManager(this);
            if (manager->VfC4() == 0) {  // vt+0xc4
                manager->Vf2EC();          // vt+0x2ec
                manager->RequestState(7);  // 0x4ec420
            } else {
                manager->m_unkAFC |= 0x200u;
                manager->m_aMenuStack[0] = manager->MenuId(0x15);  // vt+0x304
                manager->m_ui32MenuStackDepth = 1;
            }
        }
    }
    if (base == 3 || own == 3) return 3;
    if (base == 2 || own == 2) return 2;
    if (base == 0) return 0;
    return own;
}

// 0x0055e5b0 CKS08MenuPause_vfEC
void CKS08MenuPause::VfEC(IKSerializable* button) {
    if (static_cast<IKSerializable*>(FirstButton(this)) != button) return;
    CKS08GameManager* manager = GameManager(this);
    uint32_t players = manager->m_unk270;
    if (players == 0) {
        players = manager->GetPlayerCount();  // vt+0x154
        if (players == 0) {
            FirstButton(this)->m_ui8Value = 0xff;
            return;
        }
    }
    FirstButton(this)->m_ui8Value = static_cast<uint8_t>(players - 1);
}

// 0x0055e6b0 CKS08MenuPause_OnItemEvent
void CKS08MenuPause::OnItemState(uint8_t item, uint8_t state, uint8_t arg) {
    CKS08GameManager* manager = GameManager(this);
    if (item == 4) {
        if (state != 4 || arg != 1) return;
        manager->BackupOptions();  // 0x16500
        const uint8_t menu = manager->MenuId(0x17);  // vt+0x304
        manager->m_ui32MenuStackDepth = arg;
        manager->m_aMenuStack[0] = menu;
    } else if (item == 0) {
        if (state != 5 || arg != 1) return;
        manager->m_unk270 = FirstButton(this)->m_ui8Value + 1u;
        manager->RequestState(7);  // 0x4ec420
    } else if (item == 5) {
        if (state != 4 || arg != 2) return;
        const CKLocText* text = manager->VfC4() != 0 ? AccessorText(manager->m_pPromptTextAccessor, 15) : AccessorText(manager->m_pPromptTextAccessor, 14);
        MessageBox_Show(1.0f, -1.0f, this, text, 3, 6, nullptr);  // 0x695d0; TOC2 -0x7c94 / -0x7cb4
    } else if (item == 6) {
        if (state != 4 || arg != 1) return;
        if (CKSound* sound = MenuSound(this, 0)) sound->Stop(0);  // 0x1111b0
        if (CKSound* sound = MenuSound(this, 1)) sound->Stop(0);
        manager->RequestState(7);
    }
}

// 0x0055ebd0 CKS08MenuPause_UpdateCheatInput_maybe
void CKS08MenuPause::UpdateCheatInput() {
    if (!(m_fCheatTimer <= 0.0f)) {  // fcmpu + ble against 0 (TOC2 -0x7ccc)
        m_fCheatTimer = m_fCheatTimer - g_pEngine->m_timeManager->m_pTime->m_afDeltaTime[1];  // fsubs
        return;
    }
    for (uint8_t code = 0; code < 7; ++code) {
        uint8_t& progress = m_abCheatSteps[code];
        const uint8_t current = progress;
        CKS08GameManager* manager = GameManager(this);
        uint32_t held = kCheatFirst[code];
        uint32_t next = kCheatSteps[code][current];
        uint8_t player = manager->m_ui8PausePlayer;
        bool restart = manager->GetActionValue(held, player) == 0.0f;  // vt+0x164
        for (uint32_t k = 0; !restart && k <= 0x17; ++k) {
            if (k == held || k == next) continue;
            if (manager->IsActionPressed(k, player) > 0x80) restart = true;  // vt+0x160
        }
        if (!restart) {
            if (manager->IsActionPressed(next, player) > 0x80) {
                progress = static_cast<uint8_t>(current + 1);
                m_fCheatTimer = 0.3f;  // TOC2 -0x7c70
                if (progress == 5) {
                    ApplyCheatCode(code);
                    progress = 0;
                }
            }
            continue;
        }
        // A wrong press (or the held action released): the code starts again, at its first step when that is pressed.
        manager = GameManager(this);
        held = kCheatFirst[code];
        next = kCheatSteps[code][0];
        player = manager->m_ui8PausePlayer;
        if (manager->GetActionValue(held, player) == 0.0f) {
            progress = 0;
            continue;
        }
        bool other = false;
        for (uint32_t k = 0; k <= 0x17; ++k) {
            if (k == held || k == next) continue;
            if (manager->IsActionPressed(k, player) > 0x80) {
                other = true;
                break;
            }
        }
        if (other) {
            progress = 0;
            continue;
        }
        progress = manager->IsActionPressed(next, player) > 0x80 ? 1 : 0;
    }
}

// 0x0055f2c0 CKS08MenuPause_OnStatePhase
uint8_t CKS08MenuPause::OnMenuState(int32_t phase, uint8_t /*other*/) {
    if (phase == 0) {
        UpdateCheatInput();  // inlined in the original
    } else if (phase == 1) {
        CKS08GameManager* manager = GameManager(this);
        manager->SetPlayerActive(0, 1);                                                    // vt+0x184
        manager->SetPlayerActive(1, static_cast<uint8_t>(manager->GetPlayerCount() == 2));  // vt+0x184, vt+0x154
        m_abCheatSteps[6] = 0;
        m_abCheatSteps[0] = 0;
        m_abCheatSteps[1] = 0;
        m_abCheatSteps[2] = 0;
        m_abCheatSteps[3] = 0;
        m_abCheatSteps[4] = 0;
        m_abCheatSteps[5] = 0;
        m_fCheatTimer = 0.0f;
        CKSound* sound = MenuSound(this, 0);
        if (sound != nullptr && sound->IsPlaying() == 0) sound->Play(0.0f);  // 0x111568, 0x111230
        sound = MenuSound(this, 1);
        if (sound != nullptr && sound->IsPlaying() == 0) sound->Play(0.0f);  // TOC2 -0x7ccc
    }
    return static_cast<uint8_t>(GetMenuId());  // vt+0xe0
}

// 0x0055e3c8 CKS08MenuPause_RecursiveRegistration: the referenced objects' registration, then the base.
void CKS08MenuPause::RecursiveRegistration(int32_t type) {
    m_pSound->RecursiveRegistration(type);
    CKMenuBase114c::RecursiveRegistration(type);
}
