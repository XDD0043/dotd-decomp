// KeyboardDevice.cpp - reconstructed original translation unit 0x10f1f8-0x10f2b0 (GAME_TOC1, main_toc1), 9 functions, 7 live.
// Primary owner: KeyboardDevice (not a registered class)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x10f1f8  KeyboardDevice_Construct_maybe
//   [x] 0x10f208  KeyboardDevice_Init_maybe
//   [x] 0x10f238  KStub_Return1_10f238
//   [x] 0x10f240  KStub_Return1_10f240
//   [x] 0x10f248  KStub_Return1_10f248
//   [ ] 0x10f250  KeyboardDevice_Destructor_2_maybe  [dead]
//   [ ] 0x10f260  KeyboardDevice_Construct_2_maybe  [dead]
//   [x] 0x10f270  KeyboardDevice_DeletingDestructor_maybe  (~KeyboardDevice, KeyboardDevice.h: delete)
//   [x] 0x10f2a0  KeyboardDevice_Destructor_maybe  (~KeyboardDevice, KeyboardDevice.h (vtable store only))
#include "k2000/input/KeyboardDevice.h"

// 0x0010f208 KeyboardDevice_Init_maybe (XXL2 InitializeData(CKParams*)): no name for any key.
int32_t KeyboardDevice::InitializeData(void* /*params*/) {
    for (uint32_t i = 0; i < 0x90; ++i) m_i32VirtualKeyboardButtonNames[i] = -1;
    return 1;
}
