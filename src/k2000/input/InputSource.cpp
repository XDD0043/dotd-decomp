// InputSource.cpp - reconstructed original translation unit 0x10eba0-0x10f1f8 (GAME_TOC1, main_toc1), 7 functions, 5 live.
// Primary owner: InputSource (not a registered class)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x10eba0  InputSource_Construct_maybe
//   [x] 0x10ec30  InputSource_BindButtonFromBytes_maybe
//   [x] 0x10ec80  InputSource_BindButton_maybe
//   [ ] 0x10f118  InputSource_Destructor_maybe
//   [ ] 0x10f128  InputSource_Construct_2_maybe  [dead]
//   [ ] 0x10f1b8  InputSource_Destructor_2_maybe  [dead]
//   [ ] 0x10f1c8  InputSource_DeletingDestructor_maybe
#include "k2000/input/CKMapping.h"

#include "k2000/input/KeyboardDevice.h"
#include "k2000/input/MouseDevice.h"
#include "k2000/input/PS3PadDevice.h"
#include "k2000/managers/CKInput.h"

// 0x0010eba0 InputSource_Construct_maybe, in the original's store order (the IKMapping vtable store is
// immediately replaced): every slot unbound.
CKMapping::CKMapping() {
    m_aui8Command[0] = 0xff;
    m_aui8OldMappingActions[0] = nullptr;
    m_unk30 = 4;
    m_unk2c = 0;
    m_aMappingType[0] = 4;
    m_unk34 = 0;
    m_aui8MappingActions[4] = nullptr;
    m_aui8OldMappingActions[4] = nullptr;
    m_aMappingType[4] = 4;
    m_aui8NumController[4] = 0xff;
    m_aui8Command[4] = 0xff;
    m_aui8MappingActions[3] = nullptr;
    m_aui8OldMappingActions[3] = nullptr;
    m_aMappingType[3] = 4;
    m_aui8NumController[3] = 0xff;
    m_aui8Command[3] = 0xff;
    m_aui8MappingActions[2] = nullptr;
    m_aui8OldMappingActions[2] = nullptr;
    m_aMappingType[2] = 4;
    m_aui8NumController[2] = 0xff;
    m_aui8Command[2] = 0xff;
    m_aui8MappingActions[1] = nullptr;
    m_aui8OldMappingActions[1] = nullptr;
    m_aMappingType[1] = 4;
    m_aui8NumController[1] = 0xff;
    m_aui8Command[1] = 0xff;
    m_aui8MappingActions[0] = nullptr;
    m_aui8NumController[0] = 0xff;
}

// 0x0010ec80 InputSource_BindButton_maybe (XXL2 CKMapping::InitializeData(UInt8, UInt8, CKInput*,
// EMappingType, UInt32)): points the slot at the device's current and previous value of `command`; an
// out-of-range command or another type unbinds the slot.
int32_t CKMapping::InitializeData(uint8_t numController, uint8_t command, CKInput* input, int32_t type,
                                  uint32_t slot) {
    if (type == kMappingKeyboard) {
        if (command <= 0x8f) {
            KeyboardDevice& keyboard = input->m_aKeyboards[numController];
            m_aui8OldMappingActions[slot] = &keyboard.m_ui8OldVirtualKeyboardValue[command];
            m_aui8MappingActions[slot] = &keyboard.m_ui8VirtualKeyboardValue[command];
            m_aMappingType[slot] = type;
            m_aui8Command[slot] = command;
            m_aui8NumController[slot] = numController;
            return 1;
        }
    } else if (type == kMappingMouse) {
        if (command <= 0xd) {
            MouseDevice& mouse = input->m_aMouses[numController];
            m_aui8NumController[slot] = numController;
            m_aMappingType[slot] = type;
            m_aui8OldMappingActions[slot] = &mouse.m_ui8OldVirtualMouseValue[command];
            m_aui8MappingActions[slot] = &mouse.m_ui8VirtualMouseValue[command];
            m_aui8Command[slot] = command;
            return 1;
        }
    } else if (type == kMappingPad) {
        PS3PadDevice& pad = input->m_aPads[numController];
        uint8_t* current = pad.GetCurrentState();
        uint8_t* previous = pad.GetPreviousState();
        if (static_cast<int32_t>(command) < pad.GetButtonCount()) {
            m_aui8OldMappingActions[slot] = previous + command;
            m_aui8MappingActions[slot] = current + command;
            m_aMappingType[slot] = type;
            m_aui8Command[slot] = command;
            m_aui8NumController[slot] = numController;
            return 1;
        }
        m_aui8OldMappingActions[slot] = nullptr;
        m_aMappingType[slot] = kMappingNone;
        m_aui8NumController[slot] = 0xff;
        m_aui8MappingActions[slot] = nullptr;
        m_aui8Command[slot] = 0xff;
        return 1;
    }
    // The original reports 0x30004 "K_Err: MAPPING_UNKNOWN_MAPPING_TYPE" here when `this` is null (never).
    m_aui8OldMappingActions[slot] = nullptr;
    m_aMappingType[slot] = kMappingNone;
    m_aui8NumController[slot] = 0xff;
    m_aui8MappingActions[slot] = nullptr;
    m_aui8Command[slot] = 0xff;
    return 1;
}

// 0x0010ec30 InputSource_BindButtonFromBytes_maybe
int32_t CKMapping::InitializeDataFromBytes(const uint8_t* numController, const uint8_t* command, CKInput* input,
                                           int32_t type, uint32_t slot) {
    return InitializeData(*numController, *command, input, type, slot);
}
