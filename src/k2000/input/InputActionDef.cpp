// InputActionDef.cpp - reconstructed original translation unit 0x10dcb0-0x10e380 (GAME_TOC1, main_toc1), 3 functions, 2 live.
// Primary owner: InputActionDef (not a registered class)
// Other owners: InputSequenceData (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [ ] 0x10dcb0  InputSequenceData_Load_maybe  [dead]
//   [x] 0x10de40  InputActionDef_Load_maybe
//   [x] 0x10e378  InputActionDef_Load_Thunk_maybe
#include "k2000/input/CKAction.h"

#include "k2000/io/IKFile.h"

// 0x0010de40 InputActionDef_Load_maybe: the 4 mapping slots and the filter type, then the filter data
// that type uses (the rest is cleared, m_bUp is only read for type 0), then m_bRepeat.
void CKActionConfig::Load(IKFile* file, int32_t /*type*/, int32_t /*unused*/) {
    uint8_t* bytes = reinterpret_cast<uint8_t*>(this);
    for (uint32_t i = 0; i < 0xc; ++i) ReadU8(file, &bytes[i]);
    ReadU8(file, &m_Filter.m_ui8FilterType);
    m_Filter.m_ui8FilterReturn[3] = 0;
    m_Filter.m_ui8FilterNbState = 0;
    m_Filter.m_ui8FilterThreshold[0] = 0;
    m_Filter.m_ui8FilterThreshold[1] = 0;
    m_Filter.m_ui8FilterThreshold[2] = 0;
    m_Filter.m_ui8FilterReturn[0] = 0;
    m_Filter.m_ui8FilterReturn[1] = 0;
    m_Filter.m_ui8FilterReturn[2] = 0;
    switch (m_Filter.m_ui8FilterType) {
    case 1: {  // threshold: nbState, then nbState - 1 (threshold, return) pairs and the last return
        ReadU8(file, &m_Filter.m_ui8FilterNbState);
        uint8_t i = 0;
        if (m_Filter.m_ui8FilterNbState > 1) {
            do {
                ReadU8(file, &m_Filter.m_ui8FilterThreshold[i]);
                ReadU8(file, &m_Filter.m_ui8FilterReturn[i]);
                ++i;
            } while (static_cast<int32_t>(m_Filter.m_ui8FilterNbState) - 1 > static_cast<int32_t>(i));
        }
        // With nbState 0 or 1 no return state is read.
        if (m_Filter.m_ui8FilterNbState > 1) ReadU8(file, &m_Filter.m_ui8FilterReturn[i]);
        break;
    }
    case 0:  // binary: threshold, two return states, bUp
        ReadU8(file, &m_Filter.m_ui8FilterThreshold[0]);
        ReadU8(file, &m_Filter.m_ui8FilterReturn[0]);
        ReadU8(file, &m_Filter.m_ui8FilterReturn[1]);
        ReadU8(file, &m_Filter.m_bUp);
        break;
    case 2:  // analog: two thresholds
        ReadU8(file, &m_Filter.m_ui8FilterThreshold[0]);
        ReadU8(file, &m_Filter.m_ui8FilterThreshold[1]);
        break;
    default:
        break;
    }
    ReadU8(file, &m_Filter.m_bRepeat);
}

// 0x0010e378 InputActionDef_Load_Thunk_maybe
void CKActionConfig::Load(IKFile* file, int32_t type) { Load(file, type, -1); }
