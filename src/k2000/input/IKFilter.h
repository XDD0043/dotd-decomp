// IKFilter.h - the input filters (XXL2: K/KModules/KIL/KFilter): the abstract IKFilter and the three
// filters CKInput's Load creates (CKInput_LoadInputConfig_maybe allocates them; CKAction::InitializeFilter
// fills them). The XXL2 layouts and vtables match the PS3 ones (Ghidra names in brackets).
//   CKFilterBinary    [InputFilterButton]       size 0x0c, vtable 0xb19410, input/InputFilterButton.cpp
//   CKFilterThreshold [InputFilterThreshold]    size 0x0c, vtable 0xb19438, input/InputFilterThreshold.cpp
//   CKFilterAnalog    [InputFilterAnalogRange]  size 0x08, vtable 0xb193c0, input/InputFilterAnalogRange.cpp
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"

class IKFilter {
public:
    virtual ~IKFilter() {}  // vt+0x00 / +0x04
    // vt+0x08 InitializeData(nbState, thresholds, return states, bUp); XXL2 (UInt8, UInt8*, UInt8*, Bool).
    virtual int32_t InitializeData(uint8_t nbState, const uint8_t* threshold, const uint8_t* returnState,
                                   uint8_t bUp) = 0;
    // vt+0x0c XXL2 Filter(UInt8): the action's value -> its state (CKAction::UpdateState, every frame).
    virtual uint8_t Filter(uint8_t value) = 0;
    // vt+0x10 XXL2 FilterForActivity(UInt8): the same without edge state (CKInput_DetectButtonActivity_maybe).
    virtual uint8_t FilterForActivity(uint8_t value) = 0;
    // vt+0x14 XXL2 GetFilterThreshold, +0x18 (DotD): the filter's type (0 binary, 1 threshold, 2 analog).
    virtual uint8_t GetFilterThreshold() = 0;
    virtual int32_t GetFilterType() = 0;
};

class CKFilterBinary : public IKFilter {
public:
    CKFilterBinary();  // 0x00102e80 InputFilterButton_Construct_maybe
    int32_t InitializeData(uint8_t nbState, const uint8_t* threshold, const uint8_t* returnState,
                           uint8_t bUp) override;  // vt+0x08 0x00102eb0
    uint8_t Filter(uint8_t value) override;             // vt+0x0c 0x00102ee0 InputFilterButton_FilterEdge_maybe
    uint8_t FilterForActivity(uint8_t value) override;  // vt+0x10 0x00102f50 InputFilterButton_Filter_maybe
    uint8_t GetFilterThreshold() override { return m_ui8Threshold; }  // vt+0x14 0x9a6368
    int32_t GetFilterType() override { return 0; }                    // vt+0x18 0x9a6370

    uint8_t m_ui8Threshold;       // +0x04 constructor 0x7f
    uint8_t m_pReturnState[2];    // +0x05 constructor 0, 0xff
    uint8_t m_bUp;                // +0x07
    uint8_t m_bButtonPressed;     // +0x08 InitializeData clears it
    uint8_t m_pad09[3];
};
DOTD_ASSERT_SIZE(CKFilterBinary, 0x0c);
DOTD_ASSERT_OFFSET(CKFilterBinary, m_ui8Threshold, 0x04);
DOTD_ASSERT_OFFSET(CKFilterBinary, m_pReturnState, 0x05);
DOTD_ASSERT_OFFSET(CKFilterBinary, m_bUp, 0x07);
DOTD_ASSERT_OFFSET(CKFilterBinary, m_bButtonPressed, 0x08);

class CKFilterThreshold : public IKFilter {
public:
    CKFilterThreshold();  // 0x00102ff8 InputFilterThreshold_Construct_maybe
    int32_t InitializeData(uint8_t nbState, const uint8_t* threshold, const uint8_t* returnState,
                           uint8_t bUp) override;  // vt+0x08 0x00103120
    uint8_t Filter(uint8_t value) override;             // vt+0x0c 0x00103040 InputFilterThreshold_Filter_maybe
    uint8_t FilterForActivity(uint8_t value) override;  // vt+0x10 0x001030b0 InputFilterThreshold_Filter_2_maybe
    uint8_t GetFilterThreshold() override { return m_pThreshold[0]; }  // vt+0x14 0x9a6378
    int32_t GetFilterType() override { return 1; }                     // vt+0x18 0x9a6380

    uint8_t m_ui8NbState;       // +0x04 constructor 4; at most 4
    uint8_t m_pThreshold[3];    // +0x05 constructor 0x50, 0x82, 0xc8
    uint8_t m_pReturnState[4];  // +0x08 constructor 0, 100, 200, 0xff
};
DOTD_ASSERT_SIZE(CKFilterThreshold, 0x0c);
DOTD_ASSERT_OFFSET(CKFilterThreshold, m_ui8NbState, 0x04);
DOTD_ASSERT_OFFSET(CKFilterThreshold, m_pThreshold, 0x05);
DOTD_ASSERT_OFFSET(CKFilterThreshold, m_pReturnState, 0x08);

class CKFilterAnalog : public IKFilter {
public:
    CKFilterAnalog();  // 0x00102d70 InputFilterAnalogRange_Construct_maybe
    int32_t InitializeData(uint8_t nbState, const uint8_t* threshold, const uint8_t* returnState,
                           uint8_t bUp) override;  // vt+0x08 0x00102d90
    uint8_t Filter(uint8_t value) override;             // vt+0x0c 0x00102db0 InputFilterAnalogRange_MapLinear_maybe
    uint8_t FilterForActivity(uint8_t value) override;  // vt+0x10 0x00102df0 InputFilterAnalogRange_ApplyDeadzone_maybe
    uint8_t GetFilterThreshold() override { return m_ui8Threshold; }  // vt+0x14 0x9a6318
    int32_t GetFilterType() override { return 2; }                    // vt+0x18 0x9a6320

    uint8_t m_ui8Threshold;  // +0x04 constructor 0x50; threshold[0]
    uint8_t m_unk05;         // +0x05 constructor 0xff; threshold[1] (DotD, not in XXL2)
    uint8_t m_pad06[2];
};
DOTD_ASSERT_SIZE(CKFilterAnalog, 0x08);
DOTD_ASSERT_OFFSET(CKFilterAnalog, m_ui8Threshold, 0x04);
DOTD_ASSERT_OFFSET(CKFilterAnalog, m_unk05, 0x05);
