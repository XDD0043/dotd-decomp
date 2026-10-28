// InputFilterAnalogRange.cpp - reconstructed original translation unit 0x102d70-0x102e80 (GAME_TOC1, main_toc1), 8 functions, 6 live.
// Primary owner: InputFilterAnalogRange (not a registered class)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x102d70  InputFilterAnalogRange_Construct_maybe
//   [x] 0x102d90  InputFilterAnalogRange_Init_maybe
//   [x] 0x102db0  InputFilterAnalogRange_MapLinear_maybe
//   [x] 0x102df0  InputFilterAnalogRange_ApplyDeadzone_maybe
//   [ ] 0x102e10  InputFilterAnalogRange_Destructor_maybe
//   [ ] 0x102e20  InputFilterAnalogRange_Construct_2_maybe  [dead]
//   [ ] 0x102e40  InputFilterAnalogRange_Destructor_2_maybe  [dead]
//   [ ] 0x102e50  InputFilterAnalogRange_DeletingDestructor_maybe
//
//   [x] 0x9a6318  InputFilterAnalogRange_GetByte4_maybe  [inline]
//   [x] 0x9a6320  KStub_Return2_9a6320  [inline]
#include "k2000/input/IKFilter.h"

// 0x00102d70 InputFilterAnalogRange_Construct_maybe, in the original's store order.
CKFilterAnalog::CKFilterAnalog() {
    m_unk05 = 0xff;
    m_ui8Threshold = 0x50;
}

// 0x00102d90 InputFilterAnalogRange_Init_maybe (XXL2 CKFilterAnalog::InitializeData): the first two
// thresholds.
int32_t CKFilterAnalog::InitializeData(uint8_t /*nbState*/, const uint8_t* threshold,
                                       const uint8_t* /*returnState*/, uint8_t /*bUp*/) {
    m_ui8Threshold = threshold[0];
    m_unk05 = threshold[1];
    return 1;
}

// 0x00102db0 InputFilterAnalogRange_MapLinear_maybe (XXL2 CKFilterAnalog::Filter): [threshold, m_unk05]
// mapped linearly onto [0, 0xff].
uint8_t CKFilterAnalog::Filter(uint8_t value) {
    uint32_t result = 0;
    if (m_ui8Threshold < value) {
        result = 0xff;
        // The divisor is positive here (m_ui8Threshold < value < m_unk05).
        if (value < m_unk05)
            result = static_cast<uint32_t>((static_cast<int32_t>(value - m_ui8Threshold) * 0xff) /
                                           static_cast<int32_t>(m_unk05 - m_ui8Threshold)) & 0xff;
    }
    return static_cast<uint8_t>(result);
}

// 0x00102df0 InputFilterAnalogRange_ApplyDeadzone_maybe (XXL2 FilterForActivity)
uint8_t CKFilterAnalog::FilterForActivity(uint8_t value) { return m_ui8Threshold < value ? value : 0; }
