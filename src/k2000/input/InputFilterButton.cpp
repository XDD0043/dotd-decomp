// InputFilterButton.cpp - reconstructed original translation unit 0x102e80-0x102ff8 (GAME_TOC1, main_toc1), 8 functions, 6 live.
// Primary owner: InputFilterButton (not a registered class)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x102e80  InputFilterButton_Construct_maybe
//   [x] 0x102eb0  InputFilterButton_Init_maybe
//   [x] 0x102ee0  InputFilterButton_FilterEdge_maybe
//   [x] 0x102f50  InputFilterButton_Filter_maybe
//   [ ] 0x102f78  InputFilterButton_Destructor_maybe
//   [ ] 0x102f88  InputFilterButton_Construct_2_maybe  [dead]
//   [ ] 0x102fb8  InputFilterButton_Destructor_2_maybe  [dead]
//   [ ] 0x102fc8  InputFilterButton_DeletingDestructor_maybe
//
//   [x] 0x9a6368  InputFilterButton_GetByte4_maybe  [inline]
//   [x] 0x9a6370  KStub_Return0_9a6370  [inline]
#include "k2000/input/IKFilter.h"

// 0x00102e80 InputFilterButton_Construct_maybe, in the original's store order.
CKFilterBinary::CKFilterBinary() {
    m_bButtonPressed = 0;
    m_ui8Threshold = 0x7f;
    m_pReturnState[1] = 0xff;
    m_pReturnState[0] = 0;
    m_bUp = 0;
}

// 0x00102eb0 InputFilterButton_Init_maybe (XXL2 CKFilterBinary::InitializeData); nbState is not used.
int32_t CKFilterBinary::InitializeData(uint8_t /*nbState*/, const uint8_t* threshold, const uint8_t* returnState,
                                       uint8_t bUp) {
    m_ui8Threshold = threshold[0];
    m_pReturnState[0] = returnState[0];
    m_bUp = bUp;
    m_bButtonPressed = 0;
    m_pReturnState[1] = returnState[1];
    return 1;
}

// 0x00102ee0 InputFilterButton_FilterEdge_maybe (XXL2 CKFilterBinary::Filter): above the threshold the
// pressed state; with m_bUp the pressed state only on the release.
uint8_t CKFilterBinary::Filter(uint8_t value) {
    if (m_bUp == 0) {
        if (m_ui8Threshold < value) return m_pReturnState[1];
    } else if (m_ui8Threshold < value) {
        m_bButtonPressed = 1;
    } else if (m_bButtonPressed != 0) {
        m_bButtonPressed = 0;
        return m_pReturnState[1];
    }
    return m_pReturnState[0];
}

// 0x00102f50 InputFilterButton_Filter_maybe (XXL2 FilterForActivity)
uint8_t CKFilterBinary::FilterForActivity(uint8_t value) {
    if (value <= m_ui8Threshold) return m_pReturnState[0];
    return m_pReturnState[1];
}
