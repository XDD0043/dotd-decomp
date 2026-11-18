// MouseDevice.cpp - reconstructed original translation unit 0x110038-0x110108 (GAME_TOC1, main_toc1), 9 functions, 7 live.
// Primary owner: MouseDevice (not a registered class)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x110038  MouseDevice_Construct_maybe
//   [x] 0x110048  MouseDevice_Init_maybe
//   [x] 0x110090  KStub_Return1_110090
//   [x] 0x110098  KStub_Return1_110098
//   [x] 0x1100a0  KStub_Return1_1100a0
//   [ ] 0x1100a8  MouseDevice_Destructor_2_maybe  [dead]
//   [ ] 0x1100b8  MouseDevice_Construct_2_maybe  [dead]
//   [x] 0x1100c8  MouseDevice_DeletingDestructor_maybe  (~MouseDevice, MouseDevice.h: delete)
//   [x] 0x1100f8  MouseDevice_Destructor_maybe  (~MouseDevice, MouseDevice.h (vtable store only))
#include "k2000/input/MouseDevice.h"

// 0x00110048 MouseDevice_Init_maybe (XXL2 InitializeData(CKParams*)): no name for any button, in the
// original's store order.
int32_t MouseDevice::InitializeData(void* /*params*/) {
    m_i32VirtualMouseButtonNames[13] = -1;
    for (uint32_t i = 0; i < 13; ++i) m_i32VirtualMouseButtonNames[i] = -1;
    return 1;
}
