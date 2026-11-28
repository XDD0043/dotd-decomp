// CKInput.h - the input manager (key 0x100, vtable 0xb194f0, size 0x158). Original unit: CKInput.cpp.
// XXL2: K/KModules/KIL/CKInput.h; the members up to m_aProjectName are XXL2's in the same order (DotD adds
// m_aaMappings' CKMapping array type, a byte at +0x38 and the sequence vector at +0x14c).
// The Load builds the input subsystem: devices, configurations, filters, mappings, actions, sequences.
// PreUpdate polls the pads (and the mice and keyboards), drives the vibrations, updates the actions and the
// combos (CKComboManager::Update), detects the button activity.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/managers/IKModule.h"
#include "k2000/util/TVector.h"

class CKAction;
class CKCombo;
class CKComboManager;
class CKComboTransition;
class CKFilterAnalog;
class CKFilterBinary;
class CKFilterThreshold;
class CKInputDico;
class CKMapping;
class CKVibrationData;
class IKSerializable;
class KeyboardDevice;
class MouseDevice;
class PS3PadDevice;
struct CKCommand;

// XXL2 CKVibrationMotor (8 bytes): two per pad, CKInput::m_ppPadVibrationMotor.
struct CKVibrationMotor {
    uint32_t m_eState;     // +0x00 EVibrationMotorState; 1 after creation
    uint8_t m_ui8Value;    // +0x04
    uint8_t m_ui8OldValue; // +0x05
    uint8_t m_pad06[2];
};

// XXL2 CKVibration (a CSBaseNode<CKVibration*>, 0x14 bytes on the PS3).
struct CKVibration {
    CKVibration* m_pNext;                 // +0x00 CSBaseNode link
    IKSerializable* m_pVibrationOwner;    // +0x04
    uint8_t m_ui8VibrationOwnerIndex;     // +0x08
    uint8_t m_ui8NumDevice;               // +0x09
    uint8_t m_ui8NumMotor;                // +0x0a
    uint8_t m_ui8Value;                   // +0x0b
    float m_fTime;                        // +0x0c
    float m_fStopTime;                    // +0x10
};

// One record of an InputSequenceData (DotD; not in XXL2): five words read from GAME, meaning unknown.
struct InputSequenceEntry {
    uint32_t m_unk00;  // +0x00
    uint32_t m_unk04;  // +0x04
    uint32_t m_unk08;  // +0x08
    uint8_t m_unk0c;   // +0x0c
    uint8_t m_pad0d[3];
    uint32_t m_unk10;  // +0x10
};

// The elements of CKInput::m_vSequenceData (DotD; Ghidra: InputSequenceData, 0x18 bytes).
struct InputSequenceData {
    uint32_t m_unk00;                          // +0x00 read from the file (a name hash?)
    uint32_t m_unk04;                          // +0x04 the Load sets 0
    uint32_t m_unk08;                          // +0x08 the Load sets 0
    TVector<InputSequenceEntry, 8> m_vEntries; // +0x0c
};

class CKInput : public IKModule {
public:
    DOTD_CLASS_KEY(kCategoryManager, 4)
    int32_t IsKindOfClass(uint32_t key) override {  // vt+0x08 0x9a64c8
        return key == 0x100 || key == 0x33e || key == 0x3fe || key == 0xc;
    }

    CKInput();
    ~CKInput() override;

    static IKBaseClass* Create();                       // 0x00108340 CKInput_Create
    static void Delete(IKBaseClass* object);            // 0x00103770 CKInput_Delete (CKILError.cpp's unit)
    // 0x00108420 CKInput_CreateArray / 0x00105e38 CKInput_DeleteArray: new[] / delete[] (P21).
    static IKBaseClass* CreateArray(uint32_t count, uint16_t* elementSize) {
        if (elementSize != nullptr) *elementSize = static_cast<uint16_t>(sizeof(CKInput));
        return new CKInput[count];
    }
    static void DeleteArray(IKBaseClass* first) { delete[] static_cast<CKInput*>(first); }

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x0010c398 CKInput_Load
    // vt+0x24 0x00103a70 CKInput_RecursiveRegistration (C2.8 save-menu): types 0 and 1 register the input with the saving
    // manager; the save types nothing.
    void RecursiveRegistration(int32_t type) override;
    // vt+0x30 0x00107ac0 CKInput_PostLoad: every pad's two vibration motors back to state 1, values 0.
    int32_t PostLoad(int32_t /*type*/) override {
        for (uint32_t pad = 0; pad < m_ui8NbPads; ++pad) {
            for (int motor = 0; motor < 2; ++motor) {
                m_ppPadVibrationMotor[pad][motor].m_eState = 1;
                m_ppPadVibrationMotor[pad][motor].m_ui8Value = 0;
                m_ppPadVibrationMotor[pad][motor].m_ui8OldValue = 0;
            }
        }
        return 1;
    }
    void Start() override;                           // vt+0x50 0x00108568 CKInput_Start
    void Restart() override;                         // vt+0x54 0x0010d4c8 CKInput_Restart
    void Stop() override;                            // vt+0x68 0x0010d3e0 CKInput_Stop
    void Pause() override;                           // vt+0x70 0x00108998 CKInput_Pause
    void Resume() override;                          // vt+0x78 0x00107f50 CKInput_Resume
    void Update(IKTime* frameClock) override;        // vt+0x7c 0x103a60
    int32_t InitializeModule(void* params) override;     // vt+0x94 0x106fc8 CKInput_InitializeModule (fields only, no pad call)
    // vt+0x98 0x0010c450 CKInput_DestroyModule (CKGameLoop_ShutdownSubsystems_maybe): the pads ended, the combo manager,
    // the actions, the configuration tables, the combos and the sequence data freed (the devices, filters and mappings
    // are not: the original leaves them).
    void DestroyModule() override;
    // vt+0x0c 0x0010cdc0 CKInput_DestroyGame (P21): the mappings and the three filter arrays deleted, the pads
    // (DestroyPadDevices), mice and keyboards ended (their vt+0x0c) and deleted, the running vibrations back to the
    // waiting list, every action unbound, the sequence data freed.
    void DestroyGame() override;
    void Destroy() override {}  // vt+0x10 0x00107c98 CKInput_Destroy (empty)
    // vt+0xb0 0x001058c0 CKInput_vfB0 (P21): every pad's vt+0x64 (KStub_Nop_9a67e8).
    void VfB0() override;
    // 0x00105c20 CKInput_DestroyPadDevices_maybe (P21): each pad ended (vt+0x0c) and its motor pair deleted, then the
    // pad array and the motor table deleted, the pad count 0. 1.
    int32_t DestroyPadDevices();
    // 0x00105300 KStub_Return44_105300: the pad buttons' first glyph offset, 0x2c (KBase608C::GetButtonGlyph,
    // CKInputBlockSequential use the constant).
    uint32_t GetPadGlyphBase() const { return 0x2c; }
    void PreUpdate(IKTime* frameClock) override;     // vt+0x9c 0x108b78 CKInput_PreUpdate
    void PostUpdate(IKTime* frameClock) override;    // vt+0xa0 0x103a68

    // 0x0010a590 CKInput_LoadInputConfig_maybe (XXL2 LoadExportedInput): GAME's input configuration.
    int32_t LoadExportedInput(IKFile* file, int32_t type);
    // 0x0010a0d0 CKInput_LoadMappings_maybe: the sequence vector (DotD).
    void LoadSequenceData(IKFile* file, int32_t type);
    int32_t CreatePads();       // 0x00106cd0 CKInput_CreatePadDevices_maybe
    int32_t CreateMouses();     // 0x00106b78 CKInput_CreateMouseDevices_maybe
    int32_t CreateKeyboards();  // 0x00106a10 CKInput_CreateKeyboardDevices_maybe
    CKAction* GetAction(uint32_t index);  // 0x00105240 CKInput_GetActionEntry_maybe; null for 0xff
    // 0x00106978 CKInput_FindMappingIndexByName: the project whose name hash (Str_HashXor4) matches; -1.
    int32_t FindMappingIndexByName(const char* name);
    // 0x00107618 CKInput_SetMappingEnabled: enables or disables configuration `config` (its actions and
    // combos) and sets its bit in m_baActiveConfig. Returns 0 when there are no actions or no such config.
    int32_t SetMappingEnabled(uint32_t config, uint8_t enabled);
    // 0x001068d8 CKInput_SelectMappingSet_maybe: every action's mapping slot `set` made current (slot 4),
    // then the 2D manager's event 5 posted.
    void SelectMappingSet(int32_t set);
    // 0x00108fe8 CKInput_IsMenuStartPressed_maybe: entry 0xe (start) of the "Flash Manager" project's
    // configuration 1 is in its pressed state (0xff).
    bool IsMenuStartPressed();
    // 0x00108ee0 CKInput_IsMenuSkipPressed_maybe: entry 4 (validate) or 0xe (start) pressed (0xff).
    bool IsMenuSkipPressed();
    // 0x00105960 CKInput_FindButtonIconGlyph_maybe: the newest sequence whose m_unk00 is id (the "#$n#" text
    // tokens): its entry m_unk08 (project hash, configuration, action, alternate), or null.
    InputSequenceEntry* FindButtonIconGlyph(int32_t id);
    // 0x00109ee8 CKInput_GetActionButtonGlyph_maybe: the font glyph of the device button bound to `action`
    // of configuration `config` of the project whose name hash is projectHash, in mapping slot 4 (slotSelect
    // 0) or 3: pad 0xe800 + 2 x button, mouse 0xec00 + 2 x button, keyboard 0xee00 + 2 x the keyboard's
    // vt+0x1c (-1 in DotD: 0xedfe; 0xee00 without keyboards); + 1 when `alternate` is not 0. '?' when nothing
    // is bound.
    uint16_t GetActionButtonGlyph(uint32_t projectHash, uint32_t config, uint32_t action, int32_t alternate,
                                  uint32_t slotSelect);
    // 0x00104af0 CKInput_IsMappingEnabled_maybe: configuration `config`'s bit in m_baActiveConfig.
    uint8_t IsMappingEnabled(uint32_t config);
    // 0x001052d8 CKInput_GetPadRecord_maybe: pad `pad`, null past the last one.
    PS3PadDevice* GetPad(uint32_t pad);
    // 0x00107ca0 CKInput_IsPadConnected_maybe: pad `pad`'s m_bActive. BUG(original): past the last pad the
    // byte at address 4 is read (GetPad's null + 4).
    uint8_t IsPadConnected(uint32_t pad);
    // 0x00105340 CKInput_SetMotionSensorEnabled: pad `pad`'s sensor mode (vt+0x74), with a pad type set.
    void SetMotionSensorEnabled(int32_t pad, uint8_t enabled);
    // 0x0010cc90 CKInput_SetVibrationEnabled: disabling stops the vibration of pad `pad` (-1: every pad)
    // first; then the pad's flag (pad -1 writes the flag of the pad before the array: BUG(original)).
    void SetVibrationEnabled(int32_t pad, int32_t enabled);
    uint8_t GetVibrationEnabled(uint32_t pad);  // 0x001053c0 CKInput_GetVibrationEnabled
    // 0x001065e8 CKInput_ClearAllStates_maybe: every device's current and previous values and the
    // filtered actions cleared.
    void ClearAllStates();
    // 0x001049d8 CKInput_AddRumbleRequest_maybe: every running vibration of (owner, index) gets the new value
    // and duration; then a waiting node (if any) starts (owner, index, device, motor, value) for duration
    // seconds of system time. 1 when a node was started.
    int32_t AddRumbleRequest(float duration, IKSerializable* owner, int8_t index, uint8_t device, uint8_t motor, uint8_t value);
    // 0x00107538 CKInput_StopVibration_maybe: the first running vibration of (owner, index) back on the
    // waiting list. 1 when one was found.
    int32_t StopVibration(IKSerializable* owner, int8_t index);
    // step 4 INPUT.
    // 0x00103c50 CKInput_UpdateVibrations (XXL2 CKInput::UpdateVibrations): the motors' wanted values rebuilt
    // from the running vibrations (an expired timed one goes back to the waiting list), then each pad's two motors
    // driven from their state (0 running, 1 stopped) through the pad's actuator slots.
    void UpdateVibrations();
    // 0x001053f8 CKInput_DetectButtonActivity_maybe: +0x148 bit 0 and the game manager's vt+0x21c when a pad button's
    // value is above 100 this frame (the last such button per pad); bits 0..2 = 4 and device 2 for a keyboard key above
    // 100 or a mouse button above 10.
    void DetectButtonActivity();
    // 0x00107d38 CKInput_StartPadVibration (XXL2 CKInput::StartPadVibration(CKVibrationData*)): a vibration node
    // started from `data` (pad 0xfe: none, 1); untimed: not when (owner, index) runs already; timed: the running ones of
    // (owner, index) get the new value and duration too. 1 when a node was started.
    int32_t PlayVibration(const CKVibrationData* data);

    PS3PadDevice* m_aPads;              // +0x04 new[m_ui8NbPads]
    MouseDevice* m_aMouses;             // +0x08 new[m_ui8NbMouses]
    KeyboardDevice* m_aKeyboards;       // +0x0c new[m_ui8NbKeyboards]
    uint8_t m_ui8NbPads;                // +0x10
    uint8_t m_ui8NbMouses;              // +0x11
    uint8_t m_ui8NbKeyboards;           // +0x12
    uint8_t m_bUseAnalog;               // +0x13 passed to InitPad
    uint8_t m_bForceAnalog;             // +0x14 passed to InitPad
    uint8_t m_bUseVibration;            // +0x15 InitializeModule sets 1 (XXL2 order)
    uint8_t m_unk16;                    // +0x16 InitializeModule sets 0x14 (DotD)
    uint8_t m_unk17;                    // +0x17
    CKAction* m_aActions;               // +0x18 new[m_ui8NbAction]
    uint8_t* m_aFiltredActions;         // +0x1c new[m_ui8NbAction + combos], zeroed
    void* m_pKParams;                   // +0x20 InitializeModule's argument (CKParams*), given to the devices
    // XXL2 IKFilter* m_aaFilters[3]: one array per filter type, kept typed here.
    CKFilterBinary* m_aaFiltersBinary;        // +0x24 m_aaFilters[0]
    CKFilterThreshold* m_aaFiltersThreshold;  // +0x28 m_aaFilters[1]
    CKFilterAnalog* m_aaFiltersAnalog;        // +0x2c m_aaFilters[2]
    CKMapping* m_aaMappings;            // +0x30 new[count] when the count is not 0
    CKComboManager* m_pComboManager;    // +0x34 made by InitializeModule
    uint8_t m_bRefreshVibrationRequest;                    // +0x38 constructor 0 (DotD)
    uint8_t m_ui8NbInputProjet;         // +0x39
    uint8_t m_ui8NbInputConfig;         // +0x3a
    uint8_t m_ui8NbAction;              // +0x3b
    uint8_t* m_aNbActionByConfig;       // +0x3c new[m_ui8NbInputConfig]
    CKInputDico** m_aaInputDico;        // +0x40 [project][config]
    uint8_t** m_aaIndexConfigDico;      // +0x44 [config] new[m_aNbActionByConfig[config]]
    uint8_t* m_aNbComboByConfig;        // +0x48 new[m_ui8NbInputConfig]
    uint8_t** m_aaComboIndexConfigDico; // +0x4c [config] new[m_aNbComboByConfig[config]] or null
    CKCombo* m_aCombo;                  // +0x50
    CKComboTransition* m_aComboTransition;  // +0x54
    CKCommand* m_aComboCommand;         // +0x58
    uint32_t* m_aProjectName;           // +0x5c name hashes (Str_HashXor4), one per project
    uint32_t m_bNoActivityBeforeDetection;                   // _maybe: +0x60
    uint32_t m_unk64;                   // +0x64
    uint32_t m_baActiveConfig;          // +0x68 CBitArray: bit c = configuration c enabled (CKInput_SetMappingEnabled)
    int32_t m_ECurCommandMappingType;   // +0x6c CKInput_SelectMappingSet_maybe stores it and passes it to every action
    uint8_t m_bBlockedByTrc;                    // _maybe: +0x70
    uint8_t m_bExportedInputLoaded;                    // +0x71 constructor 0; the Load sets the type (1); SetMotionSensorEnabled tests it
    uint8_t m_pad72[2];
    CKVibrationMotor** m_ppPadVibrationMotor;   // +0x74 [pad] new CKVibrationMotor[2]
    CKVibration* m_lpPadVibrationsActiveList;   // +0x78 TSNodeList head
    CKVibration* m_lpPadVibrationsWaitingList;  // +0x7c TSNodeList head; InitializeModule links m_aPadVibrations
    CKVibration m_aPadVibrations[5];            // +0x80
    CKVibration m_aSavedPadVibrations[5];       // +0xe4
    uint8_t m_ui8InputActivityFlags;                   // +0x148 InitializeModule sets 0; CKInput_DetectButtonActivity_maybe (per frame) sets it
    uint8_t m_pad149[3];
    TVector<InputSequenceData, 8> m_vSequenceData;  // +0x14c (DotD)
};
DOTD_ASSERT_SIZE(CKInput, 0x158);
DOTD_ASSERT_OFFSET(CKInput, m_aPads, 0x04);
DOTD_ASSERT_OFFSET(CKInput, m_ui8NbPads, 0x10);
DOTD_ASSERT_OFFSET(CKInput, m_bForceAnalog, 0x14);
DOTD_ASSERT_OFFSET(CKInput, m_aActions, 0x18);
DOTD_ASSERT_OFFSET(CKInput, m_pKParams, 0x20);
DOTD_ASSERT_OFFSET(CKInput, m_aaFiltersBinary, 0x24);
DOTD_ASSERT_OFFSET(CKInput, m_aaMappings, 0x30);
DOTD_ASSERT_OFFSET(CKInput, m_pComboManager, 0x34);
DOTD_ASSERT_OFFSET(CKInput, m_bRefreshVibrationRequest, 0x38);
DOTD_ASSERT_OFFSET(CKInput, m_ui8NbInputProjet, 0x39);
DOTD_ASSERT_OFFSET(CKInput, m_ui8NbAction, 0x3b);
DOTD_ASSERT_OFFSET(CKInput, m_aNbActionByConfig, 0x3c);
DOTD_ASSERT_OFFSET(CKInput, m_aaInputDico, 0x40);
DOTD_ASSERT_OFFSET(CKInput, m_aaComboIndexConfigDico, 0x4c);
DOTD_ASSERT_OFFSET(CKInput, m_aCombo, 0x50);
DOTD_ASSERT_OFFSET(CKInput, m_aProjectName, 0x5c);
DOTD_ASSERT_OFFSET(CKInput, m_baActiveConfig, 0x68);
DOTD_ASSERT_OFFSET(CKInput, m_ECurCommandMappingType, 0x6c);
DOTD_ASSERT_OFFSET(CKInput, m_bExportedInputLoaded, 0x71);
DOTD_ASSERT_OFFSET(CKInput, m_ppPadVibrationMotor, 0x74);
DOTD_ASSERT_OFFSET(CKInput, m_aPadVibrations, 0x80);
DOTD_ASSERT_OFFSET(CKInput, m_aSavedPadVibrations, 0xe4);
DOTD_ASSERT_OFFSET(CKInput, m_ui8InputActivityFlags, 0x148);
DOTD_ASSERT_OFFSET(CKInput, m_vSequenceData, 0x14c);

// 0x00106fa0 Pad_Init: cellPadInit(7). Mode 0 step 0 calls it with the CKInput (unused).
void Pad_Init(CKInput* input);
