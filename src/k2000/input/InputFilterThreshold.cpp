// InputFilterThreshold.cpp - reconstructed original translation unit 0x102ff8-0x103288 (GAME_TOC1, main_toc1), 8 functions, 6 live.
// Primary owner: InputFilterThreshold (not a registered class)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x102ff8  InputFilterThreshold_Construct_maybe
//   [x] 0x103040  InputFilterThreshold_Filter_maybe
//   [x] 0x1030b0  InputFilterThreshold_Filter_2_maybe
//   [x] 0x103120  InputFilterThreshold_Init_maybe
//   [x] 0x1031f0  InputFilterThreshold_Destructor_maybe  (the implicit destructor (~IKFilter: vtable store only))
//   [ ] 0x103200  InputFilterThreshold_Construct_2_maybe  [dead]
//   [ ] 0x103248  InputFilterThreshold_Destructor_2_maybe  [dead]
//   [x] 0x103258  InputFilterThreshold_DeletingDestructor_maybe  (the implicit destructor, delete)
//
//   [x] 0x9a6378  InputFilterThreshold_GetByte5_maybe  [inline]
//   [x] 0x9a6380  KStub_Return1_9a6380  [inline]
#include "k2000/input/IKFilter.h"

// 0x00102ff8 InputFilterThreshold_Construct_maybe, in the original's store order.
CKFilterThreshold::CKFilterThreshold() {
    m_pReturnState[3] = 0xff;
    m_ui8NbState = 4;
    m_pThreshold[0] = 0x50;
    m_pThreshold[1] = 0x82;
    m_pReturnState[0] = 0;
    m_pReturnState[1] = 100;
    m_pReturnState[2] = 200;
    m_pThreshold[2] = 200;
}

// 0x00103120 InputFilterThreshold_Init_maybe (XXL2 CKFilterThreshold::InitializeData): nbState - 1
// (threshold, return state) pairs, then the last return state. More than 4 states is an error
// (KStub_Nop_10b60(0x30005, "K_Err: FILTER_THRESHOLD_OUT_OF_M...") passes the code through).
int32_t CKFilterThreshold::InitializeData(uint8_t nbState, const uint8_t* threshold, const uint8_t* returnState,
                                          uint8_t /*bUp*/) {
    if (nbState > 4) return 0x30005;
    m_ui8NbState = nbState;
    uint32_t i = 0;
    while (static_cast<int32_t>(i) < static_cast<int32_t>(nbState) - 1) {
        m_pThreshold[i] = threshold[i];
        m_pReturnState[i] = returnState[i];
        i = (i + 1) & 0xff;
    }
    m_pReturnState[i] = returnState[i];
    return 1;
}

// 0x00103040 InputFilterThreshold_Filter_maybe (XXL2 CKFilterThreshold::Filter): the return state of the
// first threshold the value does not exceed.
uint8_t CKFilterThreshold::Filter(uint8_t value) {
    uint32_t state = 0;
    const int32_t last = static_cast<int32_t>(m_ui8NbState) - 1;
    if (last > 0 && m_pThreshold[0] < value) {
        uint32_t i = 0;
        do {
            ++i;
            state = i & 0xff;
            if (last <= static_cast<int32_t>(state)) break;
        } while (m_pThreshold[state] < value);
    }
    return m_pReturnState[state];
}

// 0x001030b0 InputFilterThreshold_Filter_2_maybe (XXL2 FilterForActivity): the same code.
uint8_t CKFilterThreshold::FilterForActivity(uint8_t value) {
    uint32_t state = 0;
    const int32_t last = static_cast<int32_t>(m_ui8NbState) - 1;
    if (last > 0 && m_pThreshold[0] < value) {
        uint32_t i = 0;
        do {
            ++i;
            state = i & 0xff;
            if (last <= static_cast<int32_t>(state)) break;
        } while (m_pThreshold[state] < value);
    }
    return m_pReturnState[state];
}
