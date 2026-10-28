// CKAction.h - one input action (XXL2: K/KModules/KIL/CKAction.h, the same members in the same order;
// Ghidra: InputAction). CKInput's Load allocates m_ui8NbAction of them (CKInput::m_aActions, size 0x20,
// vtable 0xb19390) and gives each its filter and its 4 mapping slots. Code in input/InputAction.cpp
// (0x1014a8-0x101c48).
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"

class CKInput;
class IKTime;
class IKFile;
class IKFilter;
class IKMapping;

class CKAction {
public:
    CKAction();  // 0x001014f0 InputAction_Construct_maybe
    virtual ~CKAction() {}  // vt+0x00 / +0x04 (0x9a62c8 / 0x9a6298)

    // 0x00101550 InputAction_SetFilter_maybe; XXL2 InitializeFilter(IKFilter*, UInt8, UInt8*, UInt8*, Bool, Bool).
    int32_t InitializeFilter(IKFilter* filter, uint8_t nbState, const uint8_t* threshold, const uint8_t* returnState,
                             uint8_t bRepeat, uint8_t bUp);
    // 0x00101bb0 InputAction_SetSource_maybe; XXL2 InitializeMapping(IKMapping*, UInt8, UInt8, EMappingType, UInt32).
    int32_t InitializeMapping(IKMapping* mapping, uint8_t numController, uint8_t command, int32_t type,
                              uint32_t slot);
    // 0x00101708 InputAction_SelectMappingSet_maybe: the mapping's slot `set` copied to slot 4 (current).
    void SelectMappingSet(int32_t set);
    // 0x001018d0 InputAction_ResetState_maybe (XXL2 CKAction::Reset)
    void Reset();
    // 0x001018f8 InputAction_UpdateState_maybe (XXL2 CKAction::Update(UInt8&, IKTime*)): the mapped value
    // (the largest of slots 2, 0 and 3) through the filter into *filtered (CKInput::m_aFiltredActions).
    int32_t Update(uint8_t* filtered, IKTime* frameClock);

    uint8_t m_bActive;                 // +0x04 constructor 1
    uint8_t m_bActionValidate;         // +0x05
    uint8_t m_ui8Value;                // +0x06
    uint8_t m_ui8OldValue;             // +0x07
    IKFilter* m_pFilter;               // +0x08
    IKMapping* m_pMapping;             // +0x0c
    uint8_t m_bRepeat;                 // +0x10
    uint8_t m_pad11[3];
    float m_fStartAction;              // +0x14 constructor 0 (integer store)
    float m_fActionTimePressed;        // +0x18 constructor 0 (integer store)
    uint8_t m_bLockedForChangeConfig;  // +0x1c constructor 1
    uint8_t m_unk1d;                   // +0x1d constructor 0 (DotD, not in XXL2)
    uint8_t m_pad1e[2];
};
DOTD_ASSERT_SIZE(CKAction, 0x20);
DOTD_ASSERT_OFFSET(CKAction, m_bActive, 0x04);
DOTD_ASSERT_OFFSET(CKAction, m_pFilter, 0x08);
DOTD_ASSERT_OFFSET(CKAction, m_pMapping, 0x0c);
DOTD_ASSERT_OFFSET(CKAction, m_bRepeat, 0x10);
DOTD_ASSERT_OFFSET(CKAction, m_fStartAction, 0x14);
DOTD_ASSERT_OFFSET(CKAction, m_fActionTimePressed, 0x18);
DOTD_ASSERT_OFFSET(CKAction, m_bLockedForChangeConfig, 0x1c);
DOTD_ASSERT_OFFSET(CKAction, m_unk1d, 0x1d);

// The action definition the Load reads per action into a stack buffer (XXL2: CKActionConfig and
// SKActionMappingConfig, K/KModules/KIL/CKInputConfig.h, 23 bytes; Ghidra: InputActionDef). Code in
// input/InputActionDef.cpp (0x10dcb0-0x10e380).
struct SKActionMappingConfig {
    uint8_t m_ui8MappingType;     // +0x00 kMappingPad/Keyboard/Mouse; above 2 = no mapping
    uint8_t m_ui8MappingCommand;  // +0x01 the button or key
    uint8_t m_ui8NumController;   // +0x02 the device index
};

struct CKActionFilter {
    uint8_t m_ui8FilterType;          // +0x00 0 CKFilterBinary, 1 CKFilterThreshold, 2 CKFilterAnalog
    uint8_t m_ui8FilterNbState;       // +0x01
    uint8_t m_ui8FilterThreshold[3];  // +0x02
    uint8_t m_ui8FilterReturn[4];     // +0x05
    uint8_t m_bRepeat;                // +0x09
    uint8_t m_bUp;                    // +0x0a
};

struct CKActionConfig {
    // 0x0010e378 InputActionDef_Load_Thunk_maybe: the three-argument Load with -1.
    void Load(IKFile* file, int32_t type);
    // 0x0010de40 InputActionDef_Load_maybe (XXL2 CKActionConfig::Load(IKFile*, ESerializationType)). The
    // last argument is not used.
    void Load(IKFile* file, int32_t type, int32_t unused);

    SKActionMappingConfig m_asActionMappingConfig[4];  // +0x00
    CKActionFilter m_Filter;                           // +0x0c
};
DOTD_ASSERT_SIZE(CKActionConfig, 0x17);
DOTD_ASSERT_OFFSET(CKActionConfig, m_Filter, 0x0c);
