// CKInput.cpp - reconstructed original translation unit 0x103810-0x10dcb0 (GAME_TOC1, main_toc1), 108 functions, 58 live.
// Primary class: CKInput  key 0x100  category Manager  size 0x158  vtable 0xb194f0
// Other owners: CKVibrationData (6), RegisterCKInputAndCKVibrationDataClasses (1), Pad (1), InputSequenceData (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [ ] 0x103810  CKInput_Construct  [dead]
//   [x] 0x1038c8  KStub_Nop_1038c8
//   [ ] 0x1038d0  CKInput_StopPadVibration_maybe  [dead]
//   [ ] 0x1039c8  CKInput_RefreshAllPadInfo_maybe  [dead]
//   [x] 0x103a60  CKInput_Update
//   [x] 0x103a68  CKInput_PostUpdate
//   [ ] 0x103a70  CKInput_RecursiveRegistration
//   [ ] 0x103ae8  KStub_Return1_103ae8  [dead]
//   [ ] 0x103af0  KStub_Return1_103af0  [dead]
//   [ ] 0x103af8  FUN_00103af8  [dead]
//   [ ] 0x103b98  CKInput_PollAllPads_maybe  [dead]
//   [x] 0x103c50  CKInput_UpdateVibrations
//   [ ] 0x104360  CKInput_PushRumbleSlotsToList_maybe  [dead]
//   [ ] 0x104628  CKInput_PopRumbleListToSlots_maybe  [dead]
//   [ ] 0x104788  CKInput_ClearConnectedMice_maybe  [dead]
//   [ ] 0x104850  CKInput_ClearConnectedKeyboards_maybe  [dead]
//   [ ] 0x104920  CKInput_AddPersistentRumbleRequest_maybe  [dead]
//   [x] 0x1049d8  CKInput_AddRumbleRequest_maybe
//   [x] 0x104af0  CKInput_IsMappingEnabled_maybe
//   [ ] 0x104b18  CKInput_GetMappingNameHash_maybe  [dead]
//   [ ] 0x104b30  CKInput_FindMappingIndexByHash_maybe  [dead]
//   [ ] 0x104b90  FUN_00104b90  [dead]
//   [ ] 0x104ba8  CKInput_FindPressedPadButton_maybe  [dead]
//   [ ] 0x104d58  CKInput_FindPressedMouseButton_maybe  [dead]
//   [ ] 0x104fe0  CKInput_FindPressedKeyboardKey_maybe  [dead]
//   [ ] 0x105180  FUN_00105180  [dead]
//   [x] 0x105240  CKInput_GetActionEntry_maybe
//   [ ] 0x105268  CKInput_CountConnectedPads_maybe  [dead]
//   [x] 0x1052d8  CKInput_GetPadRecord_maybe
//   [ ] 0x105300  KStub_Return44_105300
//   [ ] 0x105308  CKInput_GetKeyboardRecord_maybe  [dead]
//   [ ] 0x105328  CKInput_GetMouseRecord_maybe  [dead]
//   [x] 0x105340  CKInput_SetMotionSensorEnabled
//   [ ] 0x1053b8  KStub_Nop_1053b8  [dead]
//   [x] 0x1053c0  CKInput_GetVibrationEnabled
//   [x] 0x1053f8  CKInput_DetectButtonActivity_maybe
//   [ ] 0x105790  KStub_Nop_105790  [dead]
//   [ ] 0x105798  CKInput_ResetButtonIconAnims_maybe  [dead]
//   [ ] 0x1057f0  CKInput_AdvanceButtonIconAnims_maybe  [dead]
//   [ ] 0x1058b8  KStub_Nop_1058b8
//   [ ] 0x1058c0  CKInput_vfB0
//   [x] 0x105960  CKInput_FindButtonIconGlyph_maybe
//   [ ] 0x1059d0  CKInput_DestroyKeyboardDevices_maybe  [dead]
//   [ ] 0x105b00  CKInput_DestroyMouseDevices_maybe  [dead]
//   [ ] 0x105c20  CKInput_DestroyPadDevices_maybe
//   [x] 0x105d90  CKVibrationData_DeleteArray
//   [ ] 0x105e38  CKInput_DeleteArray
//   [x] 0x105ed8  CKVibrationData_CreateArray
//   [ ] 0x105f70  CKInput_ResolveButtonPointer_maybe  [dead]
//   [ ] 0x106310  RegisterCKInputAndCKVibrationDataClasses
//   [ ] 0x1063c8  _GLOBAL__I_1063c8
//   [ ] 0x1063d8  FUN_001063d8  [dead]
//   [ ] 0x106538  CKInput_ResetMappingActionStates_maybe  [dead]
//   [x] 0x1065e8  CKInput_ClearAllStates_maybe
//   [ ] 0x1067f8  CKInput_ClearAllStatesIfFlag_maybe  [dead]
//   [ ] 0x106808  CKInput_RestoreAllActionSourceStates_maybe  [dead]
//   [ ] 0x106870  CKInput_SaveAllActionSourceStates_maybe  [dead]
//   [x] 0x1068d8  CKInput_SelectMappingSet_maybe
//   [x] 0x106978  CKInput_FindMappingIndexByName
//   [x] 0x106a10  CKInput_CreateKeyboardDevices_maybe
//   [x] 0x106b78  CKInput_CreateMouseDevices_maybe
//   [x] 0x106cd0  CKInput_CreatePadDevices_maybe
//   [ ] 0x106f18  CKInput_CreateAllDevices_maybe  [dead]
//   [x] 0x106fa0  Pad_Init
//   [x] 0x106fc8  CKInput_InitializeModule
//   [ ] 0x107198  CKInput_GetBoundButtonCode_maybe  [dead]
//   [x] 0x107538  CKInput_StopVibration_maybe
//   [x] 0x107618  CKInput_SetMappingEnabled
//   [ ] 0x107888  CKInput_Construct_2  [dead]
//   [x] 0x107940  CKVibrationData_Create
//   [ ] 0x107978  CKInput_GetMappingButtonState_maybe  [dead]
//   [ ] 0x107a58  CKInput_Save
//   [ ] 0x107a60  CKVibrationData_RecursiveRegistration
//   [ ] 0x107ac0  CKInput_PostLoad
//   [ ] 0x107b70  CKVibrationData_Save
//   [ ] 0x107c98  CKInput_Destroy
//   [x] 0x107ca0  CKInput_IsPadConnected_maybe
//   [ ] 0x107cc8  CKInput_CountConnectedPads_2_maybe  [dead]
//   [x] 0x107d38  CKInput_StartPadVibration
//   [x] 0x107f50  CKInput_Resume
//   [x] 0x108340  CKInput_Create
//   [ ] 0x108420  CKInput_CreateArray
//   [x] 0x108568  CKInput_Start
//   [x] 0x108768  CKVibrationData_Load
//   [ ] 0x1088c0  CKInput_FreeButtonIconAnims_maybe  [dead]
//   [x] 0x108998  CKInput_Pause
//   [x] 0x108b78  CKInput_PreUpdate
//   [x] 0x108ee0  CKInput_IsMenuSkipPressed_maybe
//   [x] 0x108fe8  CKInput_IsMenuStartPressed_maybe
//   [ ] 0x1090f8  CKInput_CaptureAnyButton_maybe  [dead]
//   [ ] 0x109890  CKInput_CaptureAndBindButton_maybe  [dead]
//   [x] 0x109ee8  CKInput_GetActionButtonGlyph_maybe
//   [x] 0x10a0d0  CKInput_LoadMappings_maybe
//   [x] 0x10a590  CKInput_LoadInputConfig_maybe
//   [x] 0x10c398  CKInput_Load
//   [ ] 0x10c450  CKInput_DestroyModule
//   [ ] 0x10c9c0  CKInput_DestroyAllDevices_maybe  [dead]
//   [ ] 0x10cbf0  CKInput_StopAllPadVibration_maybe  [dead]
//   [x] 0x10cc90  CKInput_SetVibrationEnabled
//   [ ] 0x10cdc0  CKInput_DestroyGame
//   [ ] 0x10d340  CKInput_StopAllPadVibration_2_maybe  [dead]
//   [x] 0x10d3e0  CKInput_Stop
//   [ ] 0x10d4c8  CKInput_Restart
//   [ ] 0x10d630  FUN_0010d630  [dead]
//   [ ] 0x10d670  FUN_0010d670  [dead]
//   [ ] 0x10d690  InputSequenceData_Save_maybe  [dead]
//   [ ] 0x10d798  FUN_0010d798  [dead]
//   [ ] 0x10dca8  FUN_0010dca8  [dead]
//
//   [ ] 0x9a63c8  CKVibrationData_IsKindOfClass  [inline]
//   [x] 0x9a63f0  CKVibrationData_GetClassType  [inline]
//   [x] 0x9a63f8  CKVibrationData_GetClassID  [inline]
//   [ ] 0x9a6400  CKInput_GetClassType  [inline]
//   [ ] 0x9a6408  CKInput_GetClassID  [inline]
//   [ ] 0x9a6450  CKVibrationData_DeletingDestructor  [inline]
//   [ ] 0x9a6498  CKVibrationData_Destructor  [inline]
//   [ ] 0x9a64c8  CKInput_IsKindOfClass  [inline]
//   [ ] 0x9a6500  CKInput_DeletingDestructor  [inline]
//   [ ] 0x9a6600  CKInput_Destructor  [inline]
//   [ ] 0x9a66f0  KStub_Return9_9a66f0  [inline]
//   [ ] 0x9a66f8  KStub_Return5_9a66f8  [inline]
//   [ ] 0x9a6700  KStub_Return1_9a6700  [inline]
//   [ ] 0x9a6708  KStub_Return1_9a6708  [inline]
#include "k2000/managers/CKInput.h"

#include <cstring>

#include "k2000/core/Stub.h"
#include "k2000/input/CKAction.h"
#include "k2000/input/CKCombo.h"
#include "k2000/input/CKComboManager.h"
#include "k2000/input/CKInputDico.h"
#include "k2000/input/CKMapping.h"
#include "k2000/input/IKFilter.h"
#include "k2000/input/KeyboardDevice.h"
#include "k2000/input/MouseDevice.h"
#include "k2000/input/PS3PadDevice.h"
#include "k2000/io/IKFile.h"
#include "k2000/logic/CDefaultGameManager.h"
#include "crt/ppc_ops.h"
#include "k2000/memory/Mem.h"
#include "k2000/misc/Engine.h"
#include "k2000/system/CTimeManager.h"
#include "k2000/system/CellSysutilCallback.h"
#include "k2000/system/IKTime.h"
#include "platform/cell/pad.h"

namespace {
// Local copy of 0x000107d8 Str_HashXor4 (misc/Wcs.cpp, not ported yet): the bytes XORed into four
// accumulators in turn, returned as a little-endian word (lwbrx).
uint32_t Str_HashXor4(const char* s) {
    uint8_t acc[4] = {0, 0, 0, 0};
    for (uint32_t i = 0; s[i] != 0; ++i) acc[i & 3] ^= static_cast<uint8_t>(s[i]);
    return static_cast<uint32_t>(acc[0]) | (static_cast<uint32_t>(acc[1]) << 8) | (static_cast<uint32_t>(acc[2]) << 16) |
           (static_cast<uint32_t>(acc[3]) << 24);
}
}  // namespace

// 0x001038c8 KStub_Nop_1038c8
void KStub_Nop_1038c8(CKInput*) {}

// 0x00106fa0 Pad_Init
void Pad_Init(CKInput* /*input*/) { cellPadInit(7); }

// 0x00108340 CKInput_Create (0x103810 CKInput_Construct is its dead out-of-line copy), in the original's
// store order: the list heads, the vibration nodes' links and the sequence vector; the rest is left as it is.
CKInput::CKInput() {
    m_lpPadVibrationsActiveList = nullptr;
    m_lpPadVibrationsWaitingList = nullptr;
    m_aPadVibrations[0].m_pNext = nullptr;
    m_aPadVibrations[1].m_pNext = nullptr;
    m_aPadVibrations[2].m_pNext = nullptr;
    m_aPadVibrations[4].m_pNext = nullptr;
    m_aPadVibrations[3].m_pNext = nullptr;
    m_aSavedPadVibrations[0].m_pNext = nullptr;
    m_aSavedPadVibrations[1].m_pNext = nullptr;
    m_aSavedPadVibrations[2].m_pNext = nullptr;
    m_aSavedPadVibrations[4].m_pNext = nullptr;
    m_aSavedPadVibrations[3].m_pNext = nullptr;
    m_vSequenceData.m_ui32NbElt = 8;
    m_vSequenceData.m_pBlock = nullptr;
    m_vSequenceData.m_ui32NbUsedElt = 0;
    m_unk38 = 0;
    m_unk71 = 0;
}
// STUB(C1.6): 0x9a6600 CKInput_Destructor (frees the devices and tables) is not ported.
CKInput::~CKInput() {}
IKBaseClass* CKInput::Create() { return new CKInput(); }
void CKInput::Delete(IKBaseClass* object) { delete object; }
// 0x00103a60 CKInput_Update (empty)
void CKInput::Update(IKTime*) {}
// 0x00103a68 CKInput_PostUpdate (empty)
void CKInput::PostUpdate(IKTime*) {}

// 0x00106fc8 CKInput_InitializeModule, in the original's store order. Mode 0 step 0 initializes the pads
// separately (Pad_Init).
int32_t CKInput::InitializeModule(void* params) {
    m_bUseVibration = 1;
    m_pKParams = params;
    m_aPads = nullptr;
    m_ui8NbPads = 0;
    m_aMouses = nullptr;
    m_ui8NbMouses = 0;
    m_aKeyboards = nullptr;
    m_ui8NbKeyboards = 0;
    m_bUseAnalog = 0;
    m_bForceAnalog = 0;
    m_aaMappings = nullptr;
    m_aaFiltersBinary = nullptr;
    m_aaFiltersThreshold = nullptr;
    m_aaFiltersAnalog = nullptr;
    CKComboManager* comboManager = new CKComboManager();
    m_aPadVibrations[0].m_fTime = -1.0f;
    m_aPadVibrations[0].m_fStopTime = -1.0f;
    m_pComboManager = comboManager;
    m_ui8NbAction = 0;
    m_aActions = nullptr;
    m_aFiltredActions = nullptr;
    m_aNbActionByConfig = nullptr;
    m_aNbComboByConfig = nullptr;
    m_aaInputDico = nullptr;
    m_aaIndexConfigDico = nullptr;
    m_aaComboIndexConfigDico = nullptr;
    m_aCombo = nullptr;
    m_aComboTransition = nullptr;
    m_aComboCommand = nullptr;
    m_aProjectName = nullptr;
    m_ECurCommandMappingType = 0;
    m_baActiveConfig = 0;
    m_unk16 = 0x14;
    // The five vibrations, each cleared and pushed on the waiting list (CSBaseNode insert at the head).
    for (uint32_t i = 0; i < 5; ++i) {
        CKVibration& vibration = m_aPadVibrations[i];
        vibration.m_pVibrationOwner = nullptr;
        vibration.m_ui8VibrationOwnerIndex = 0;
        vibration.m_ui8NumDevice = 0;
        vibration.m_ui8NumMotor = 0;
        vibration.m_ui8Value = 0;
        vibration.m_fTime = -1.0f;
        vibration.m_fStopTime = -1.0f;
        vibration.m_pNext = m_lpPadVibrationsWaitingList;
        m_lpPadVibrationsWaitingList = &vibration;
    }
    m_unk148 = 0;
    return 1;
}

// 0x00105240 CKInput_GetActionEntry_maybe
CKAction* CKInput::GetAction(uint32_t index) {
    if (index == 0xff) return nullptr;
    return &m_aActions[index];
}

// 0x00106cd0 CKInput_CreatePadDevices_maybe: the pads, then two vibration motors per pad.
int32_t CKInput::CreatePads() {
    if (m_ui8NbPads == 0) return 1;
    m_aPads = new PS3PadDevice[m_ui8NbPads];
    if (m_ui8NbPads == 0) return 1;
    for (uint32_t i = 0; i < m_ui8NbPads; ++i) {
        m_aPads[i].InitializeData(m_pKParams);
        m_aPads[i].InitPad(static_cast<uint8_t>(i), 0, 0, m_bUseAnalog, m_bForceAnalog);
    }
    if (m_ui8NbPads == 0) return 1;
    m_ppPadVibrationMotor = new CKVibrationMotor*[m_ui8NbPads];
    for (uint32_t i = 0; i < m_ui8NbPads; ++i) m_ppPadVibrationMotor[i] = new CKVibrationMotor[2];
    for (uint32_t i = 0; i < m_ui8NbPads; ++i) {
        CKVibrationMotor* motors = m_ppPadVibrationMotor[i];
        motors[0].m_eState = 1;
        motors[0].m_ui8Value = 0;
        motors[0].m_ui8OldValue = 0;
        motors[1].m_eState = 1;
        motors[1].m_ui8Value = 0;
        motors[1].m_ui8OldValue = 0;
    }
    return 1;
}

// 0x00106b78 CKInput_CreateMouseDevices_maybe
int32_t CKInput::CreateMouses() {
    if (m_ui8NbMouses == 0) return 1;
    m_aMouses = new MouseDevice[m_ui8NbMouses];
    for (uint32_t i = 0; i < m_ui8NbMouses; ++i) {
        m_aMouses[i].InitializeData(m_pKParams);
        m_aMouses[i].InitMouse();
    }
    return 1;
}

// 0x00106a10 CKInput_CreateKeyboardDevices_maybe
int32_t CKInput::CreateKeyboards() {
    if (m_ui8NbKeyboards == 0) return 1;
    m_aKeyboards = new KeyboardDevice[m_ui8NbKeyboards];
    for (uint32_t i = 0; i < m_ui8NbKeyboards; ++i) {
        m_aKeyboards[i].InitializeData(m_pKParams);
        m_aKeyboards[i].InitKeyboard();
    }
    return 1;
}

// 0x0010a0d0 CKInput_LoadMappings_maybe: GAME's sequence data (DotD), an inlined TVector resize to the
// file's count, then per element a word and its records.
void CKInput::LoadSequenceData(IKFile* file, int32_t type) {
    if (type != K_GAME_PLATEFORMS) return;
    uint32_t count = 0;
    ReadU32LE(file, &count);
    if (count == 0) return;
    TVector<InputSequenceData, 8>& vector = m_vSequenceData;
    vector.m_ui32NbElt = count;
    // The previous block is not freed.
    vector.m_pBlock = static_cast<InputSequenceData*>(Mem_AllocAligned16(count * static_cast<uint32_t>(sizeof(InputSequenceData))));
    if (vector.m_ui32NbElt < count) {  // never true here: the capacity is the count
        uint32_t capacity = (count & ~7u) + 8;
        if (capacity == 0) capacity = 8;
        vector.m_pBlock = static_cast<InputSequenceData*>(
            Mem_ReallocAligned16(vector.m_pBlock, capacity * static_cast<uint32_t>(sizeof(InputSequenceData))));
        vector.m_ui32NbElt = capacity;
    }
    for (uint32_t i = vector.m_ui32NbUsedElt; i < count; ++i) {  // the element constructor
        TVector<InputSequenceEntry, 8>& entries = vector.m_pBlock[i].m_vEntries;
        entries.m_ui32NbElt = 8;
        entries.m_pBlock = nullptr;
        entries.m_ui32NbUsedElt = 0;
    }
    // BUG(original): the element destructor runs on the new block's (uninitialized) elements. Only a second
    // Load with a smaller count gets here.
    for (uint32_t i = count; i < vector.m_ui32NbUsedElt; ++i) {
        TVector<InputSequenceEntry, 8>& entries = vector.m_pBlock[i].m_vEntries;
        if (entries.m_pBlock != nullptr) {
            Mem_FreeAligned16(entries.m_pBlock);
            entries.m_pBlock = nullptr;
        }
        entries.m_ui32NbUsedElt = 0;
        entries.m_pBlock = nullptr;
    }
    vector.m_ui32NbUsedElt = count;
    for (uint32_t i = 0; i < count; ++i) {
        InputSequenceData& data = vector.m_pBlock[i];
        ReadU32LE(file, &data.m_unk00);
        data.m_unk08 = 0;
        data.m_unk04 = 0;
        uint32_t nbEntries = 0;
        ReadU32LE(file, &nbEntries);
        TVector<InputSequenceEntry, 8>& entries = data.m_vEntries;
        if (nbEntries == 0) {
            entries.m_ui32NbElt = 1;
            entries.m_pBlock = static_cast<InputSequenceEntry*>(Mem_AllocAligned16(static_cast<uint32_t>(sizeof(InputSequenceEntry))));
        } else {
            entries.m_ui32NbElt = nbEntries;
            entries.m_pBlock = static_cast<InputSequenceEntry*>(
                Mem_AllocAligned16(nbEntries * static_cast<uint32_t>(sizeof(InputSequenceEntry))));
        }
        if (entries.m_ui32NbElt < nbEntries) {  // never true here
            uint32_t capacity = (nbEntries & ~7u) + 8;
            if (capacity == 0) capacity = 8;
            entries.m_pBlock = static_cast<InputSequenceEntry*>(
                Mem_ReallocAligned16(entries.m_pBlock, capacity * static_cast<uint32_t>(sizeof(InputSequenceEntry))));
            entries.m_ui32NbElt = capacity;
        }
        entries.m_ui32NbUsedElt = nbEntries;
        for (uint32_t j = 0; j < nbEntries; ++j) {
            InputSequenceEntry& entry = entries.m_pBlock[j];
            ReadU32LE(file, &entry.m_unk00);
            ReadU32LE(file, &entry.m_unk04);
            ReadU32LE(file, &entry.m_unk08);
            ReadU8(file, &entry.m_unk0c);
            ReadU32LE(file, &entry.m_unk10);
        }
    }
}

// 0x0010a590 CKInput_LoadInputConfig_maybe (XXL2 CKInput::LoadExportedInput): the devices, the
// configurations and their action tables, the filters, mappings and actions, the sequences and the
// device button names. Returns 0 when the version byte is not 7.
int32_t CKInput::LoadExportedInput(IKFile* file, int32_t /*type*/) {
    uint8_t version = 0;
    if (file == nullptr) return 0;
    ReadU8(file, &version);
    if (version != 7) return 0;
    ReadU8(file, &m_ui8NbPads);
    ReadU8(file, &m_ui8NbMouses);
    ReadU8(file, &m_ui8NbKeyboards);
    ReadU8(file, &m_bUseAnalog);
    ReadU8(file, &m_bForceAnalog);
    ReadU8(file, &m_ui8NbInputProjet);
    m_aProjectName = new uint32_t[m_ui8NbInputProjet];
    for (uint32_t i = 0; i < m_ui8NbInputProjet; ++i) ReadU32LE(file, &m_aProjectName[i]);
    ReadU8(file, &m_ui8NbInputConfig);
    if (m_ui8NbPads != 0) CreatePads();
    if (m_ui8NbMouses != 0) CreateMouses();
    if (m_ui8NbKeyboards != 0) CreateKeyboards();
    m_aNbActionByConfig = new uint8_t[m_ui8NbInputConfig];
    for (uint32_t i = 0; i < m_ui8NbInputConfig; ++i) ReadU8(file, &m_aNbActionByConfig[i]);
    m_aaInputDico = new CKInputDico*[m_ui8NbInputProjet];
    for (uint32_t i = 0; i < m_ui8NbInputProjet; ++i) m_aaInputDico[i] = new CKInputDico[m_ui8NbInputConfig];

    // The mappings and the filters. The three filter counts are read raw and then reused as the next free
    // filter of each type.
    uint32_t nbMappings = 0;
    ReadU32LE(file, &nbMappings);
    uint8_t filterIndex[3];
    ReadRaw(file, filterIndex, 3);
    if (nbMappings != 0) m_aaMappings = new CKMapping[nbMappings];
    if (filterIndex[0] != 0) m_aaFiltersBinary = new CKFilterBinary[filterIndex[0]];
    if (filterIndex[1] != 0) m_aaFiltersThreshold = new CKFilterThreshold[filterIndex[1]];
    if (filterIndex[2] != 0) m_aaFiltersAnalog = new CKFilterAnalog[filterIndex[2]];
    filterIndex[2] = 0;
    filterIndex[0] = 0;
    filterIndex[1] = 0;

    // The actions: per action its definition, its filter, then its 4 mapping slots. An action with at least
    // one mapped slot takes the next CKMapping; its unmapped slots are cleared on it.
    ReadU8(file, &m_ui8NbAction);
    if (m_ui8NbAction != 0) {
        m_aActions = new CKAction[m_ui8NbAction];
        // The original's stack buffer is not cleared; the only byte the definition Load does not always set
        // (m_bUp) goes to a filter only for type 0, which reads it.
        CKActionConfig config = {};
        uint32_t mapping = 0;
        for (uint32_t i = 0; i < m_ui8NbAction; ++i) {
            config.Load(file, K_GAME_PLATEFORMS);
            CKAction& action = m_aActions[i];
            const CKActionFilter& filter = config.m_Filter;
            switch (filter.m_ui8FilterType) {
            case 0:
                action.InitializeFilter(&m_aaFiltersBinary[filterIndex[0]], filter.m_ui8FilterNbState,
                                        filter.m_ui8FilterThreshold, filter.m_ui8FilterReturn, filter.m_bRepeat,
                                        filter.m_bUp);
                ++filterIndex[0];
                break;
            case 1:
                action.InitializeFilter(&m_aaFiltersThreshold[filterIndex[1]], filter.m_ui8FilterNbState,
                                        filter.m_ui8FilterThreshold, filter.m_ui8FilterReturn, filter.m_bRepeat,
                                        filter.m_bUp);
                ++filterIndex[1];
                break;
            case 2:
                action.InitializeFilter(&m_aaFiltersAnalog[filterIndex[2]], filter.m_ui8FilterNbState,
                                        filter.m_ui8FilterThreshold, filter.m_ui8FilterReturn, filter.m_bRepeat,
                                        filter.m_bUp);
                ++filterIndex[2];
                break;
            default:
                action.InitializeFilter(nullptr, 0, nullptr, nullptr, 0, 0);
                break;
            }
            bool mapped = false;
            for (uint32_t slot = 0; slot < 4; ++slot) {
                if (config.m_asActionMappingConfig[slot].m_ui8MappingType <= 2) mapped = true;
            }
            for (uint32_t slot = 0; slot < 4; ++slot) {
                const SKActionMappingConfig& slotConfig = config.m_asActionMappingConfig[slot];
                if (slotConfig.m_ui8MappingType <= 2) {
                    action.InitializeMapping(&m_aaMappings[mapping], slotConfig.m_ui8NumController,
                                             slotConfig.m_ui8MappingCommand, slotConfig.m_ui8MappingType, slot);
                } else if (mapped) {
                    action.InitializeMapping(&m_aaMappings[mapping], 4, 0, kMappingNone, slot);
                } else {
                    action.InitializeMapping(nullptr, 4, 0, kMappingNone, 0xffffffffu);
                }
            }
            if (mapped) ++mapping;
        }
    }

    uint8_t comboManagerActive = 0;
    ReadU8(file, &comboManagerActive);
    m_pComboManager->ActiveComboManager(comboManagerActive);
    m_aNbComboByConfig = new uint8_t[m_ui8NbInputConfig];
    for (uint32_t i = 0; i < m_ui8NbInputConfig; ++i) ReadU8(file, &m_aNbComboByConfig[i]);

    // The sequences: their transitions and commands are two flat arrays, taken in file order.
    uint8_t nbCombo = 0;
    uint32_t nbCommand = 0;
    uint32_t nbTransition = 0;
    ReadU8(file, &nbCombo);
    ReadU32LE(file, &nbCommand);
    ReadU32LE(file, &nbTransition);
    if (nbCombo != 0) {
        m_aCombo = new CKCombo[nbCombo];
        m_aComboTransition = nbTransition == 0 ? nullptr : new CKComboTransition[nbTransition];
        if (nbCommand == 0) {
            m_aComboCommand = nullptr;
        } else {
            m_aComboCommand = new CKCommand[nbCommand];
            for (uint32_t i = 0; i < nbCommand; ++i) {  // the inlined CKCommand constructor
                CKCommand& command = m_aComboCommand[i];
                command.m_bValidate = 0;
                command.m_ui8Command = 0xff;
                command.m_ui8Value = 0x7f;
                command.m_fTimePressed = 0.0f;
                command.m_fEndTimePressed = 0.0f;
            }
            for (uint32_t i = 0; i < nbCommand; ++i) {
                m_aComboCommand[i].m_ui8Command = 0xff;
                m_aComboCommand[i].m_ui8Value = 0;
            }
        }
        uint32_t command = 0;
        uint32_t transition = 0;
        for (uint32_t c = 0; c < nbCombo; ++c) {
            uint8_t nbState = 0;
            float comboTime = 0.0f;
            ReadU8(file, &nbState);
            ReadF32LE(file, &comboTime);
            const uint32_t firstTransition = transition;
            for (uint32_t s = 0; s < nbState; ++s) {
                uint8_t nbValid = 0;
                uint8_t nbBreak = 0;
                ReadU8(file, &nbValid);
                ReadU8(file, &nbBreak);
                const uint32_t firstValid = command;
                for (uint32_t k = 0; k < nbValid; ++k, ++command) {
                    CKCommand& entry = m_aComboCommand[command];
                    ReadU8(file, &entry.m_ui8Command);
                    ReadU8(file, &entry.m_ui8Value);
                    ReadF32LE(file, &entry.m_fTimePressed);
                    entry.m_bValidate = 0;
                }
                const uint32_t firstBreak = command;
                for (uint32_t k = 0; k < nbBreak; ++k, ++command) {
                    CKCommand& entry = m_aComboCommand[command];
                    ReadU8(file, &entry.m_ui8Command);
                    ReadU8(file, &entry.m_ui8Value);
                    ReadF32LE(file, &entry.m_fTimePressed);
                    entry.m_bValidate = 0;
                }
                m_aComboTransition[transition].InitializeData(nbValid, nbBreak, m_aComboCommand + firstValid,
                                                              m_aComboCommand + firstBreak);
                ++transition;
            }
            m_aCombo[c].InitializeData(nbState, m_aComboTransition + firstTransition, comboTime, 1);
        }
        m_pComboManager->Initialize(nbCombo, m_aCombo);
    }

    // Per configuration the action and sequence index tables, then each project's configurations.
    m_aaIndexConfigDico = new uint8_t*[m_ui8NbInputConfig];
    for (uint32_t i = 0; i < m_ui8NbInputConfig; ++i) m_aaIndexConfigDico[i] = new uint8_t[m_aNbActionByConfig[i]];
    m_aaComboIndexConfigDico = new uint8_t*[m_ui8NbInputConfig];
    for (uint32_t i = 0; i < m_ui8NbInputConfig; ++i) {
        m_aaComboIndexConfigDico[i] = m_aNbComboByConfig[i] == 0 ? nullptr : new uint8_t[m_aNbComboByConfig[i]];
    }
    uint8_t actionBase = 0;
    uint8_t comboBase = 0;
    for (uint32_t p = 0; p < m_ui8NbInputProjet; ++p) {
        for (uint32_t c = 0; c < m_ui8NbInputConfig; ++c) {
            m_aaInputDico[p][c].Load(file, m_ui8NbAction, &actionBase, &comboBase);
        }
    }
    for (uint32_t c = 0; c < m_ui8NbInputConfig; ++c) {
        for (uint32_t k = 0; k < m_aNbActionByConfig[c]; ++k) ReadU8(file, &m_aaIndexConfigDico[c][k]);
        for (uint32_t k = 0; k < m_aNbComboByConfig[c]; ++k) ReadU8(file, &m_aaComboIndexConfigDico[c][k]);
    }

    // The device button names: a counted list for the pads, then a count (not used) and a fixed list for
    // the mice (14) and the keyboards (144).
    uint32_t count = 0;
    ReadU32LE(file, &count);
    uint32_t* padNames = new uint32_t[count];
    ReadU32LEWords(file, padNames, count);
    for (uint32_t i = 0; i < m_ui8NbPads; ++i) std::memcpy(m_aPads[i].GetButtonNames(), padNames, count * 4);
    if (padNames != nullptr) delete[] padNames;
    ReadU32LE(file, &count);
    uint32_t mouseNames[14];
    ReadU32LEWords(file, mouseNames, 14);
    for (uint32_t i = 0; i < m_ui8NbMouses; ++i) {
        std::memcpy(m_aMouses[i].m_i32VirtualMouseButtonNames, mouseNames, sizeof(mouseNames));
    }
    ReadU32LE(file, &count);
    uint32_t keyboardNames[0x90];
    ReadU32LEWords(file, keyboardNames, 0x90);
    for (uint32_t i = 0; i < m_ui8NbKeyboards; ++i) {
        std::memcpy(m_aKeyboards[i].m_i32VirtualKeyboardButtonNames, keyboardNames, sizeof(keyboardNames));
    }

    const uint32_t nbFiltred = static_cast<uint32_t>(m_ui8NbAction) + nbCombo;
    m_aFiltredActions = new uint8_t[nbFiltred];
    for (uint32_t i = 0; i < nbFiltred; ++i) m_aFiltredActions[i] = 0;

    // The "Flash Manager" project's second configuration: its entries 4 and 0x18 (pads 0 and 1) and 5 and
    // 0x19 get the confirm and cancel buttons (0xc / 0xe), swapped by the system's enter-button setting.
    // BUG(original): no project of that name, or a null entry or mapping, is not checked for.
    const uint32_t hash = Str_HashXor4("Flash Manager");
    CKInputDico* dico = nullptr;
    for (uint32_t p = 0; p < m_ui8NbInputProjet; ++p) {
        if (m_aProjectName[p] == hash) {
            if (static_cast<uint8_t>(p) != 0xff) dico = &m_aaInputDico[p][1];
            break;
        }
    }
    uint32_t confirm = 0xe;
    uint32_t cancel = 0xc;
    IKMapping* mapping4 = dico->GetActionPointer(4)->m_pMapping;
    IKMapping* mapping18 = dico->GetActionPointer(0x18)->m_pMapping;
    IKMapping* mapping5 = dico->GetActionPointer(5)->m_pMapping;
    IKMapping* mapping19 = dico->GetActionPointer(0x19)->m_pMapping;
    if (g_enterButtonAssign != 0) {
        confirm = 0xc;
        cancel = 0xe;
    }
    if (mapping4 != nullptr) mapping4->InitializeData(0, static_cast<uint8_t>(confirm & 0xe), this, kMappingPad, 0);
    if (mapping18 != nullptr) mapping18->InitializeData(1, static_cast<uint8_t>(confirm & 0xe), this, kMappingPad, 0);
    if (mapping5 != nullptr) mapping5->InitializeData(0, static_cast<uint8_t>(cancel & 0xe), this, kMappingPad, 0);
    if (mapping19 != nullptr) mapping19->InitializeData(1, static_cast<uint8_t>(cancel & 0xe), this, kMappingPad, 0);
    return 1;
}

// 0x0010c398 CKInput_Load. GAME (type 1) holds the exported input and the sequence data; the other files'
// objects read nothing. XXL2 reads only the exported input.
int32_t CKInput::Load(IKFile* file, int32_t type) {
    if (type != K_GAME_PLATEFORMS) {
        LoadSequenceData(file, type);
        return 1;
    }
    LoadExportedInput(file, K_GAME_PLATEFORMS);
    LoadSequenceData(file, K_GAME_PLATEFORMS);
    m_unk71 = static_cast<uint8_t>(type);
    return 1;
}

// ---- CKVibrationData (managers/CKVibrationData.h) ----
#include "k2000/managers/CKVibrationData.h"

#include "k2000/io/IKFile.h"

// 0x00108768 CKVibrationData_Load
int32_t CKVibrationData::Load(IKFile* file, int32_t type) {
    if (type != K_LEVEL_PLATEFORMS) return 1;
    m_ui8NumPad = 0xff;
    ReadU8(file, &m_ui8NumMotor);
    ReadU8(file, &m_ui8Value);
    ReadF32LE(file, &m_fTime);
    ReadU8(file, &m_bUseTime);
    m_pOwner = nullptr;  // the original stores the type register (0 here)
    m_ui8OwnerIndex = 0;
    return 1;
}

// 0x00106978 CKInput_FindMappingIndexByName
int32_t CKInput::FindMappingIndexByName(const char* name) {
    const uint32_t hash = Str_HashXor4(name);
    for (uint32_t i = 0; i < m_ui8NbInputProjet; ++i)
        if (m_aProjectName[i] == hash) return static_cast<int32_t>(i);
    return -1;
}

// 0x00108b78 CKInput_PreUpdate: the pads read, then every active action updated into m_aFiltredActions,
// then the sequence-data timers advanced.
void CKInput::PreUpdate(IKTime* frameClock) {
    if (m_aPads != nullptr) {
        for (uint32_t i = 0; i < m_ui8NbPads; i = (i + 1) & 0xff) m_aPads[i].Update();  // vt+0x2c
    }
    UpdateVibrations();  // 0x00103c50
    // The mice (vt+0x14 of each active one) and keyboards: none on the PS3 (GAME: 0 of each).
    if (m_aMouses != nullptr && m_ui8NbMouses != 0) DOTD_STUB_ONCE("CKInput_PreUpdate: mouse devices");
    if (m_aKeyboards != nullptr && m_ui8NbKeyboards != 0) DOTD_STUB_ONCE("CKInput_PreUpdate: keyboard devices");
    for (uint32_t i = 0; i < m_ui8NbAction; i = (i + 1) & 0xff) {
        CKAction* action = &m_aActions[i];
        if (action->m_bActive != 0) action->Update(&m_aFiltredActions[i], frameClock);
    }
    // STUB(C1.6): 0x00102220 InputSequenceTracker_Update_maybe (the combo manager +0x34 over the filtered actions).
    DetectButtonActivity();  // 0x001053f8
    // The sequence data, last first: each runs through its entries, m_unk04 counting up to the entry's
    // duration (+0x10, a float; 0 = stays) on the engine clock's FIXED_GAME_TIME delta.
    const float dt = g_pEngine->m_timeManager->m_pTime->m_afDeltaTime[IKTime::FIXED_GAME_TIME];
    for (uint32_t n = m_vSequenceData.m_ui32NbUsedElt; n != 0; --n) {
        InputSequenceData* data = &m_vSequenceData.m_pBlock[n - 1];
        const InputSequenceEntry* entry = &data->m_vEntries.m_pBlock[data->m_unk08];
        float duration;
        std::memcpy(&duration, &entry->m_unk10, 4);
        if (duration == 0.0f) continue;
        float timer;
        std::memcpy(&timer, &data->m_unk04, 4);
        timer = dt + timer;
        std::memcpy(&data->m_unk04, &timer, 4);
        if (!(duration <= timer)) continue;
        const float zero = 0.0f;
        std::memcpy(&data->m_unk04, &zero, 4);
        const uint32_t next = data->m_unk08 + 1;
        data->m_unk08 = next;
        if (data->m_vEntries.m_ui32NbUsedElt <= next) data->m_unk08 = 0;
    }
}

// 0x00107618 CKInput_SetMappingEnabled
int32_t CKInput::SetMappingEnabled(uint32_t config, uint8_t enabled) {
    if (m_aActions == nullptr) return 0;
    const uint32_t index = config & 0xff;
    if (index >= m_ui8NbInputConfig) return 0;
    const uint8_t count = m_aNbActionByConfig[index];
    if (count != 0) {
        uint32_t i = 0;
        if (enabled == 0) {
            do {
                const uint8_t action = m_aaIndexConfigDico[index][i];
                m_aActions[action].m_bActive = 0;
                m_aFiltredActions[action] = 0;
                i = (i + 1) & 0xff;
            } while (i != count);
        } else {
            do {
                CKAction* action = &m_aActions[m_aaIndexConfigDico[index][i]];
                if (action->m_bActive == 0) action->Reset();
                action->m_bActive = 1;
                i = (i + 1) & 0xff;
            } while (i != count);
        }
    }
    const uint32_t combos = m_aNbComboByConfig[index];
    if (combos != 0) {
        uint32_t i = 0;
        do {
            m_pComboManager->SetComboActive(m_aaComboIndexConfigDico[index][i], enabled);
            i = (i + 1) & 0xff;
        } while (i != combos);
    }
    // rlwnm of ~1 by the config (a rotate: bit config & 0x1f cleared), then slw by config & 0x3f.
    m_baActiveConfig = (m_baActiveConfig & ~(1u << (config & 0x1f))) | ppc::slw(enabled, config & 0x3f);
    return 1;
}

namespace {
// The "Flash Manager" project's configuration 1, as the two menu tests inline the lookup: the first
// project with the name's hash; 0xff (not found) leaves the null set. BUG(original): without the project
// the PS3 reads through a null pointer (the project always exists in GAME.KP3).
CKInputDico* FlashManagerConfig1(CKInput* input) {
    const uint32_t hash = Str_HashXor4("Flash Manager");
    const uint8_t count = input->m_ui8NbInputProjet;
    if (count == 0) return nullptr;
    uint8_t found = 0;
    if (input->m_aProjectName[0] != hash) {
        uint32_t left = count;
        const uint32_t* name = input->m_aProjectName;
        do {
            ++name;
            found = static_cast<uint8_t>(found + 1);
            if (--left == 0) return nullptr;
        } while (*name != hash);
        if (found == 0xff) return nullptr;
    }
    return &input->m_aaInputDico[found][1];
}
}  // namespace

// 0x00108fe8 CKInput_IsMenuStartPressed_maybe
bool CKInput::IsMenuStartPressed() {
    const CKInputDico* config = FlashManagerConfig1(this);
    return config->GetButtonState(0xe) == 0xff;
}

// 0x00108ee0 CKInput_IsMenuSkipPressed_maybe
bool CKInput::IsMenuSkipPressed() {
    const CKInputDico* config = FlashManagerConfig1(this);
    if (config->GetButtonState(4) == 0xff) return true;
    return config->GetButtonState(0xe) == 0xff;
}

#include "k2000/graphical/ui/CManager2d.h"

// 0x001068d8 CKInput_SelectMappingSet_maybe
void CKInput::SelectMappingSet(int32_t set) {
    m_ECurCommandMappingType = set;
    for (uint32_t i = 0; m_ui8NbAction > i; ++i) m_aActions[i].SelectMappingSet(set);
    g_pEngine->m_manager2d->PostEvent(5, nullptr);
}

// 0x00105960 CKInput_FindButtonIconGlyph_maybe: searched from the last sequence.
InputSequenceEntry* CKInput::FindButtonIconGlyph(int32_t id) {
    for (uint32_t i = m_vSequenceData.m_ui32NbUsedElt; i != 0; --i) {
        InputSequenceData& data = m_vSequenceData.m_pBlock[i - 1];
        if (static_cast<int32_t>(data.m_unk00) == id) return &data.m_vEntries.m_pBlock[data.m_unk08];
    }
    return nullptr;
}

// 0x00109ee8 CKInput_GetActionButtonGlyph_maybe
uint16_t CKInput::GetActionButtonGlyph(uint32_t projectHash, uint32_t config, uint32_t action, int32_t alternate,
                                       uint32_t slotSelect) {
    uint32_t project = 0xffffffffu;
    for (uint32_t i = 0; i < m_ui8NbInputProjet; ++i) {
        if (m_aProjectName[i] == projectHash) {
            project = i;
            break;
        }
    }
    const uint32_t slot = (slotSelect & 0xff) == 0 ? 4u : 3u;
    if ((project & 0xff) == 0xff) return 0x3f;  // '?'
    // The PS3 tests the element's address: null only for a null array and configuration 0.
    CKInputDico* const dicos = m_aaInputDico[project & 0xff];
    if (dicos == nullptr && (config & 0xff) == 0) return 0x3f;
    CKInputDico* const dico = &dicos[config & 0xff];
    CKAction* const entry = dico->GetActionPointer(static_cast<int32_t>(action & 0xff));
    if (entry == nullptr) return 0x3f;
    const CKMapping* const mapping = static_cast<const CKMapping*>(entry->m_pMapping);
    if (mapping == nullptr) return 0x3f;
    const uint32_t command = mapping->m_aui8Command[slot];
    const int32_t type = mapping->m_aMappingType[slot];
    int32_t base;
    if (type == kMappingKeyboard) {
        base = -0x1200;
        // The keyboard's vt+0x1c with the key code: 0x9a6758 KStub_ReturnM1_9a6758 in DotD (KeyboardDevice.h
        // declares the slots up to +0x10).
        if (m_aKeyboards != nullptr) base = -1 * 2 - 0x1200;
    } else if (static_cast<uint32_t>(type) < 1) {
        base = static_cast<int32_t>(command * 2) - 0x1800;
    } else if (type == kMappingMouse) {
        base = static_cast<int32_t>(command * 2) - 0x1400;
    } else {
        return 0x3f;
    }
    // (-|alternate| >> 31): 1 for any alternate but 0.
    return static_cast<uint16_t>(base + (alternate != 0 ? 1 : 0));
}

// ---- C1.6: the module's run states, the pads' helpers ----

namespace {
// The TSNodeList head pop the vibration lists inline (TSNodeList::RemoveHead): the head's successor
// becomes the head (or the list empty), the node unlinked.
CKVibration* PopVibration(CKVibration** list) {
    CKVibration* node = *list;
    if (node == nullptr) return nullptr;
    CKVibration* next = node->m_pNext;
    if (next == nullptr) {
        *list = nullptr;
    } else {
        node->m_pNext = nullptr;
        *list = next;
    }
    return node;
}

// The filtered actions and the combos' entries cleared (Start, Stop, ClearAllStates).
void ClearFilteredActions(CKInput* input) {
    int32_t count = static_cast<int32_t>(input->m_ui8NbAction) + static_cast<int32_t>(input->m_pComboManager->m_ui8NbCombo);
    for (int32_t i = count; i != 0; --i) {
        --count;
        input->m_aFiltredActions[count] = 0;
    }
}
}  // namespace

// 0x00108568 CKInput_Start: every pad's ReInitPad (vt+0x14), every configuration's actions reset, the
// filtered actions cleared, the sequences' two run-time words cleared.
void CKInput::Start() {
    if (m_ui8NbPads != 0) {
        uint32_t i = 0;
        do {
            m_aPads[i].ReInitPad();
            i = (i + 1) & 0xff;
        } while (i < m_ui8NbPads);
    }
    uint32_t configs = m_ui8NbInputConfig;
    if (configs != 0) {
        uint32_t config = 0;
        do {
            const uint8_t actions = m_aNbActionByConfig[config];
            if (actions != 0) {
                for (uint32_t i = 0; i != actions; ++i) m_aActions[m_aaIndexConfigDico[config][i]].Reset();
                configs = m_ui8NbInputConfig;
            }
            config = (config + 1) & 0xff;
        } while (config < configs);
    }
    m_unk70 = 0;
    m_unk60 &= 0x00ffffffu;  // the byte at +0x60
    m_unk64 = 0;
    ClearFilteredActions(this);
    for (uint32_t i = m_vSequenceData.m_ui32NbUsedElt; i != 0; --i) {
        m_vSequenceData.m_pBlock[i - 1].m_unk08 = 0;
        m_vSequenceData.m_pBlock[i - 1].m_unk04 = 0;
    }
}

// 0x0010d3e0 CKInput_Stop: every pad's vibration stopped (with a pad type set), the filtered actions
// cleared.
void CKInput::Stop() {
    if (m_unk71 != 0 && m_ui8NbPads != 0) {
        uint32_t i = 0;
        do {
            m_aPads[i].StopAllVibration();
            ++i;
        } while (i < m_ui8NbPads);
    }
    ClearFilteredActions(this);
}

// 0x00108998 CKInput_Pause: every pad's Pause (vt+0x1c: its vibration stopped), then the running
// vibrations saved in order (m_aSavedPadVibrations, their nodes back on the waiting list) and the other
// saved entries cleared.
void CKInput::Pause() {
    if (m_ui8NbPads != 0) {
        uint32_t i = 0;
        do {
            m_aPads[i].Pause();
            ++i;
        } while (i < m_ui8NbPads);
    }
    int32_t saved = 0;
    for (CKVibration* node = PopVibration(&m_lpPadVibrationsActiveList); node != nullptr;
         node = PopVibration(&m_lpPadVibrationsActiveList)) {
        CKVibration* slot = &m_aSavedPadVibrations[saved];
        slot->m_pVibrationOwner = node->m_pVibrationOwner;
        slot->m_ui8VibrationOwnerIndex = node->m_ui8VibrationOwnerIndex;
        slot->m_ui8NumDevice = node->m_ui8NumDevice;
        slot->m_ui8NumMotor = node->m_ui8NumMotor;
        slot->m_ui8Value = node->m_ui8Value;
        slot->m_fTime = node->m_fTime;
        slot->m_fStopTime = node->m_fStopTime;
        node->m_pNext = m_lpPadVibrationsWaitingList;
        m_lpPadVibrationsWaitingList = node;
        ++saved;
        // BUG(original): no bound; the lists hold the five nodes of m_aPadVibrations, so at most five.
    }
    for (int32_t i = saved; i < 5; ++i) {
        CKVibration* slot = &m_aSavedPadVibrations[i];
        slot->m_fStopTime = 0.0f;
        slot->m_ui8Value = 0;
        slot->m_pVibrationOwner = nullptr;
        slot->m_ui8VibrationOwnerIndex = 0;
        slot->m_ui8NumDevice = 0;
        slot->m_ui8NumMotor = 0;
        slot->m_fTime = 0.0f;
    }
}

// 0x00107f50 CKInput_Resume: every pad's Resume (vt+0x24, empty), every running vibration's node back
// on the waiting list, then each saved vibration with an owner restarted on a node from the waiting list
// (pushed on the running list's head), in the saved order.
void CKInput::Resume() {
    if (m_ui8NbPads != 0) {
        uint32_t i = 0;
        do {
            m_aPads[i].Resume();
            ++i;
        } while (i < m_ui8NbPads);
    }
    for (CKVibration* node = PopVibration(&m_lpPadVibrationsActiveList); node != nullptr;
         node = PopVibration(&m_lpPadVibrationsActiveList)) {
        node->m_pNext = m_lpPadVibrationsWaitingList;
        m_lpPadVibrationsWaitingList = node;
    }
    for (uint32_t i = 0; i < 5; ++i) {
        if (m_lpPadVibrationsWaitingList == nullptr) break;
        const CKVibration* slot = &m_aSavedPadVibrations[i];
        if (slot->m_pVibrationOwner == nullptr) continue;
        CKVibration* node = PopVibration(&m_lpPadVibrationsWaitingList);
        node->m_pVibrationOwner = slot->m_pVibrationOwner;
        node->m_ui8VibrationOwnerIndex = slot->m_ui8VibrationOwnerIndex;
        node->m_ui8NumDevice = slot->m_ui8NumDevice;
        node->m_ui8NumMotor = slot->m_ui8NumMotor;
        node->m_ui8Value = slot->m_ui8Value;
        node->m_fTime = slot->m_fTime;
        node->m_fStopTime = slot->m_fStopTime;
        node->m_pNext = m_lpPadVibrationsActiveList;
        m_lpPadVibrationsActiveList = node;
    }
}

// 0x00104af0 CKInput_IsMappingEnabled_maybe
uint8_t CKInput::IsMappingEnabled(uint32_t config) {
    return static_cast<uint8_t>(((ppc::slw(1u, config & 0x3f) & m_baActiveConfig) != 0) ? 1 : 0);
}

// 0x001052d8 CKInput_GetPadRecord_maybe
PS3PadDevice* CKInput::GetPad(uint32_t pad) {
    if (pad < m_ui8NbPads) return &m_aPads[pad];
    return nullptr;
}

// 0x00107ca0 CKInput_IsPadConnected_maybe
uint8_t CKInput::IsPadConnected(uint32_t pad) {
    PS3PadDevice* device = GetPad(pad);
    // BUG(original): no pad reads address 4 (zero in the PS3's first page); not reproduced.
    if (device == nullptr) return 0;
    return device->m_bActive;
}

// 0x00105340 CKInput_SetMotionSensorEnabled
void CKInput::SetMotionSensorEnabled(int32_t pad, uint8_t enabled) {
    if (m_unk71 == 0 || m_ui8NbPads == 0 || pad >= static_cast<int32_t>(m_ui8NbPads)) return;
    m_aPads[pad].SetSensorMode(enabled);
}

// 0x0010cc90 CKInput_SetVibrationEnabled
void CKInput::SetVibrationEnabled(int32_t pad, int32_t enabled) {
    if (m_unk71 == 0) return;
    uint32_t count = m_ui8NbPads;
    if (count == 0) return;
    if (enabled == 0) {
        if (pad == -1) {
            uint32_t i = 0;
            do {
                ++i;
                m_aPads[i - 1].StopAllVibration();
                count = m_ui8NbPads;
            } while (i < m_ui8NbPads);
        } else {
            m_aPads[pad].StopAllVibration();
            count = m_ui8NbPads;
        }
    }
    // BUG(original): pad -1 writes the flag 0x21c bytes before the array (+6); not reproduced, it would
    // write outside the native allocation.
    if (pad < static_cast<int32_t>(count) && pad >= 0) m_aPads[pad].m_bVibrationEnabled = static_cast<uint8_t>(enabled);
}

// 0x001053c0 CKInput_GetVibrationEnabled
uint8_t CKInput::GetVibrationEnabled(uint32_t pad) {
    if (pad >= m_ui8NbPads) return 0;
    return m_aPads[pad].m_bVibrationEnabled;
}

// 0x001065e8 CKInput_ClearAllStates_maybe
void CKInput::ClearAllStates() {
    if (m_ui8NbPads != 0) {
        uint32_t i = 0;
        do {
            ++i;
            m_aPads[i - 1].ClearStates();  // vt+0x60
        } while (i < m_ui8NbPads);
    }
    for (uint32_t i = 0; i < m_ui8NbKeyboards; ++i) {
        KeyboardDevice* keyboard = &m_aKeyboards[i];
        std::memset(keyboard->m_ui8VirtualKeyboardValue, 0, 0x90);
        std::memset(keyboard->m_ui8InternKeyboardValue, 0, 0x90);
        std::memset(keyboard->m_ui8OldVirtualKeyboardValue, 0, 0x90);
    }
    for (uint32_t i = 0; i < m_ui8NbMouses; ++i) {
        MouseDevice* mouse = &m_aMouses[i];
        std::memset(mouse->m_ui8VirtualMouseValue, 0, sizeof(mouse->m_ui8VirtualMouseValue));
        std::memset(mouse->m_ui8OldVirtualMouseValue, 0, sizeof(mouse->m_ui8OldVirtualMouseValue));
    }
    ClearFilteredActions(this);
}

// 0x001049d8 CKInput_AddRumbleRequest_maybe. BUG(original): the matching running vibrations are updated and
// a new node is started anyway.
int32_t CKInput::AddRumbleRequest(float duration, IKSerializable* owner, int8_t index, uint8_t device, uint8_t motor,
                                  uint8_t value) {
    const IKTime* clock = g_pEngine->m_timeManager->m_pTime;
    for (CKVibration* node = m_lpPadVibrationsActiveList; node != nullptr; node = node->m_pNext) {
        if (node->m_pVibrationOwner != owner || static_cast<int8_t>(node->m_ui8VibrationOwnerIndex) != index) continue;
        node->m_ui8Value = value;
        node->m_fTime = duration;
        node->m_fStopTime = duration + clock->m_afCurrentTime[IKTime::SYSTEM_TIME];
    }
    CKVibration* node = PopVibration(&m_lpPadVibrationsWaitingList);
    if (node == nullptr) return 0;
    node->m_pVibrationOwner = owner;
    node->m_ui8VibrationOwnerIndex = static_cast<uint8_t>(index);
    node->m_ui8NumDevice = device;
    node->m_ui8NumMotor = motor;
    node->m_ui8Value = value;
    node->m_fTime = duration;
    node->m_fStopTime = duration + clock->m_afCurrentTime[IKTime::SYSTEM_TIME];
    node->m_pNext = m_lpPadVibrationsActiveList;
    m_lpPadVibrationsActiveList = node;
    return 1;
}

// 0x00107538 CKInput_StopVibration_maybe
int32_t CKInput::StopVibration(IKSerializable* owner, int8_t index) {
    CKVibration* previous = nullptr;
    for (CKVibration* node = m_lpPadVibrationsActiveList; node != nullptr; previous = node, node = node->m_pNext) {
        if (node->m_pVibrationOwner != owner || static_cast<int8_t>(node->m_ui8VibrationOwnerIndex) != index) continue;
        if (previous == nullptr) {
            PopVibration(&m_lpPadVibrationsActiveList);
        } else {
            previous->m_pNext = node->m_pNext;
            node->m_pNext = nullptr;
        }
        node->m_pNext = m_lpPadVibrationsWaitingList;
        m_lpPadVibrationsWaitingList = node;
        return 1;
    }
    return 0;
}

// 0x00107d38 CKInput_StartPadVibration
int32_t CKInput::PlayVibration(const CKVibrationData* data) {
    const uint8_t pad = data->m_ui8NumPad;
    if (pad == 0xfe) return 1;
    IKSerializable* owner = data->m_pOwner;
    const uint8_t index = data->m_ui8OwnerIndex;
    const uint8_t motor = data->m_ui8NumMotor;
    const uint8_t value = data->m_ui8Value;
    const IKTime* clock = g_pEngine->m_timeManager->m_pTime;
    if (data->m_bUseTime == 0) {
        for (CKVibration* node = m_lpPadVibrationsActiveList; node != nullptr; node = node->m_pNext) {
            if (node->m_pVibrationOwner == owner && node->m_ui8VibrationOwnerIndex == index) return 0;
        }
        CKVibration* node = PopVibration(&m_lpPadVibrationsWaitingList);
        if (node == nullptr) return 0;
        node->m_pVibrationOwner = owner;
        node->m_ui8VibrationOwnerIndex = index;
        node->m_ui8NumDevice = pad;
        node->m_ui8NumMotor = motor;
        node->m_ui8Value = value;
        node->m_fStopTime = -1.0f;  // TOC1 -0x4720
        node->m_fTime = -1.0f;
        node->m_pNext = m_lpPadVibrationsActiveList;
        m_lpPadVibrationsActiveList = node;
        return 1;
    }
    const float time = data->m_fTime;
    for (CKVibration* node = m_lpPadVibrationsActiveList; node != nullptr; node = node->m_pNext) {
        if (node->m_pVibrationOwner != owner || node->m_ui8VibrationOwnerIndex != index) continue;
        node->m_ui8Value = value;
        node->m_fTime = time;
        node->m_fStopTime = time + clock->m_afCurrentTime[IKTime::SYSTEM_TIME];
    }
    CKVibration* node = PopVibration(&m_lpPadVibrationsWaitingList);
    if (node == nullptr) return 0;
    node->m_pVibrationOwner = owner;
    node->m_ui8VibrationOwnerIndex = index;
    node->m_ui8NumDevice = pad;
    node->m_ui8NumMotor = motor;
    node->m_ui8Value = value;
    node->m_fTime = time;
    node->m_fStopTime = time + clock->m_afCurrentTime[IKTime::SYSTEM_TIME];
    node->m_pNext = m_lpPadVibrationsActiveList;
    m_lpPadVibrationsActiveList = node;
    return 1;
}

namespace {
// A running vibration's value into the wanted value of its motor (the larger one): on its pad, or (pad -1) on every pad
// of the controlled heroes (the game manager's vt+0x134, at most the pad count).
void RaiseMotorValues(CKInput* input, const CKVibration* node) {
    const int8_t device = static_cast<int8_t>(node->m_ui8NumDevice);
    if (device == -1) {
        uint32_t count = static_cast<CDefaultGameManager*>(g_pEngine->m_gameManager)->GetControlledHeroCount();
        if (count > input->m_ui8NbPads) count = input->m_ui8NbPads;
        for (uint32_t k = 0; k < count; ++k) {
            CKVibrationMotor& motor = input->m_ppPadVibrationMotor[k][node->m_ui8NumMotor];
            if (motor.m_ui8Value < node->m_ui8Value) motor.m_ui8Value = node->m_ui8Value;
        }
        return;
    }
    CKVibrationMotor& motor = input->m_ppPadVibrationMotor[device][node->m_ui8NumMotor];
    if (motor.m_ui8Value < node->m_ui8Value) motor.m_ui8Value = node->m_ui8Value;
}
}  // namespace

// 0x00103c50 CKInput_UpdateVibrations. The pads' actuators (PS3PadDevice vt+0x3c / +0x40 / +0x44) reach the
// platform pad layer (cellPadSetActDirect: SDL gamepad rumble); nothing here feeds back into the game.
void CKInput::UpdateVibrations() {
    for (uint32_t i = 0; i < m_ui8NbPads; i = (i + 1) & 0xffu) {
        m_ppPadVibrationMotor[i][0].m_ui8Value = 0;
        m_ppPadVibrationMotor[i][1].m_ui8Value = 0;
    }
    const IKTime* clock = g_pEngine->m_timeManager->m_pTime;
    CKVibration* previous = nullptr;
    CKVibration* node = m_lpPadVibrationsActiveList;
    while (node != nullptr) {
        CKVibration* next = node->m_pNext;
        if (node->m_fTime == -1.0f || clock->m_afCurrentTime[IKTime::SYSTEM_TIME] <= node->m_fStopTime) {
            RaiseMotorValues(this, node);
            previous = node;
        } else {
            // Expired: unlinked (after `previous`, or the head) and put back on the waiting list.
            if (previous == nullptr) {
                PopVibration(&m_lpPadVibrationsActiveList);
            } else {
                previous->m_pNext = node->m_pNext;
                if (node->m_pNext != nullptr) node->m_pNext = nullptr;
            }
            node->m_pNext = m_lpPadVibrationsWaitingList;
            m_lpPadVibrationsWaitingList = node;
        }
        node = next;
    }
    for (uint32_t i = 0; i < m_ui8NbPads; i = (i + 1) & 0xffu) {
        if (m_aPads == nullptr) continue;  // the address of pad 0 of a null array
        PS3PadDevice* pad = &m_aPads[i];
        if (pad->m_bVibrationEnabled == 0) continue;
        CKVibrationMotor* motors = m_ppPadVibrationMotor[i];
        for (int32_t m = 0; m < 2; ++m) {
            CKVibrationMotor& motor = motors[m];
            const uint8_t value = motor.m_ui8Value;
            if (motor.m_eState == 0) {
                if (motor.m_ui8OldValue != value) {
                    if (value != 0) {
                        pad->UpdateVibrationValue(m, value);  // vt+0x40
                    } else {
                        pad->StopVibration(m);  // vt+0x44
                        motor.m_eState = 1;
                    }
                }
            } else if (motor.m_eState == 1) {
                if (motor.m_ui8OldValue == value) {
                    // A refresh request (+0x38) sends the value again once.
                    if (m_unk38 != 0) {
                        m_unk38 = 0;
                        pad->UpdateVibrationValue(m, motor.m_ui8Value);  // vt+0x40
                    }
                } else if (value != 0) {
                    pad->StartVibration(m, value);  // vt+0x3c
                    motor.m_eState = 0;
                }
            }
            motor.m_ui8OldValue = motor.m_ui8Value;
        }
    }
}

// 0x001053f8 CKInput_DetectButtonActivity_maybe
void CKInput::DetectButtonActivity() {
    m_unk148 = 0;
    for (uint32_t i = 0; i < m_ui8NbPads; ++i) {
        PS3PadDevice* pad = &m_aPads[i];
        const uint8_t* values = pad->GetCurrentState();  // vt+0x30
        const int32_t count = pad->GetButtonCount();    // vt+0x68
        for (int32_t button = count - 1; button >= 0; --button) {
            if (values[button] <= 0x64) continue;
            static_cast<CDefaultGameManager*>(g_pEngine->m_gameManager)->NotifyInputActivity(0, button);  // vt+0x21c
            m_unk148 = static_cast<uint8_t>((m_unk148 & 0xfeu) | 1u);
            break;
        }
    }
    // STUB(C1.6: no such devices): the keyboards (keys 0x8f..0 above 100: the game manager's vt+0x21c with device 2,
    // +0x148 bits 0..2 = 4) and the mice (buttons 0xd..0 above 10, the same). The PS3 data has none (GAME: 0 of each).
    if (m_ui8NbKeyboards != 0) DOTD_STUB_ONCE("CKInput_DetectButtonActivity_maybe: keyboard devices");
    if (m_ui8NbMouses != 0) DOTD_STUB_ONCE("CKInput_DetectButtonActivity_maybe: mouse devices");
}
