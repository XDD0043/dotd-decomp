// CKMapping.h - one action's device binding (XXL2: K/KModules/KIL/KMapping, IKMapping and CKMapping;
// Ghidra: InputSource). CKInput's Load allocates them (CKInput::m_aaMappings, size 0x58, vtable
// 0xb195e8, base vtable 0xb19600) and binds them through CKAction::InitializeMapping. Code in
// input/InputSource.cpp (0x10eba0-0x10f1f8).
//
// Each of the 5 slots points into a device's button-state arrays: m_aui8MappingActions[slot] at the
// current value, m_aui8OldMappingActions[slot] at the previous one (XXL2 IKMapping, the same two arrays).
// DotD adds per-slot mapping type, device index and command bytes after them.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"

class CKInput;

// EMappingType (XXL2 enum; the values the PS3 CKMapping::InitializeData tests).
enum : int32_t {
    kMappingPad = 0,
    kMappingKeyboard = 1,
    kMappingMouse = 2,
    kMappingNone = 4,
};

class IKMapping {
public:
    virtual ~IKMapping() {}  // vt+0x00 / +0x04
    // vt+0x08 InitializeData(numController, command, input, type, slot); 0x9a6700 returns 1 in the base.
    virtual int32_t InitializeData(uint8_t numController, uint8_t command, CKInput* input, int32_t type,
                                   uint32_t slot) {
        (void)numController, (void)command, (void)input, (void)type, (void)slot;
        return 1;
    }
    // vt+0x0c the same from two byte pointers; 0x9a6708 returns 1 in the base.
    virtual int32_t InitializeDataFromBytes(const uint8_t* numController, const uint8_t* command, CKInput* input,
                                            int32_t type, uint32_t slot) {
        (void)numController, (void)command, (void)input, (void)type, (void)slot;
        return 1;
    }

    uint8_t* m_aui8MappingActions[5];     // +0x04 current device value per slot
    uint8_t* m_aui8OldMappingActions[5];  // +0x18 previous device value per slot
};

class CKMapping : public IKMapping {
public:
    CKMapping();  // 0x0010eba0 InputSource_Construct_maybe

    int32_t InitializeData(uint8_t numController, uint8_t command, CKInput* input, int32_t type,
                           uint32_t slot) override;  // vt+0x08 0x0010ec80 InputSource_BindButton_maybe
    int32_t InitializeDataFromBytes(const uint8_t* numController, const uint8_t* command, CKInput* input,
                                    int32_t type, uint32_t slot) override;  // vt+0x0c 0x0010ec30

    uint32_t m_unk2c;               // +0x2c constructor 0
    uint32_t m_unk30;               // +0x30 constructor 4 (kMappingNone)
    uint8_t m_unk34;                // +0x34 constructor 0
    uint8_t m_pad35[3];
    int32_t m_aMappingType[5];      // +0x38 per slot: kMappingPad/Keyboard/Mouse, kMappingNone when unbound
    uint8_t m_aui8NumController[5]; // +0x4c per slot: the device index, 0xff when unbound
    uint8_t m_aui8Command[5];       // +0x51 per slot: the button or key, 0xff when unbound
    uint8_t m_pad56[2];
};
DOTD_ASSERT_SIZE(CKMapping, 0x58);
DOTD_ASSERT_OFFSET(CKMapping, m_aui8MappingActions, 0x04);
DOTD_ASSERT_OFFSET(CKMapping, m_aui8OldMappingActions, 0x18);
DOTD_ASSERT_OFFSET(CKMapping, m_unk2c, 0x2c);
DOTD_ASSERT_OFFSET(CKMapping, m_unk30, 0x30);
DOTD_ASSERT_OFFSET(CKMapping, m_unk34, 0x34);
DOTD_ASSERT_OFFSET(CKMapping, m_aMappingType, 0x38);
DOTD_ASSERT_OFFSET(CKMapping, m_aui8NumController, 0x4c);
DOTD_ASSERT_OFFSET(CKMapping, m_aui8Command, 0x51);
