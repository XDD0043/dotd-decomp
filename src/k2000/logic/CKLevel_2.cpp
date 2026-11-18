// Reconstructed original translation unit: 0x4b688-0x4b7b8 (GAME_TOC1, main_toc1), 1 functions, 1 live.
// Primary class: CKLevel  key 0x14c  category Logic  size 0x48  vtable 0xb14010
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x4b688  CKLevel_EnterSector_HostFsStateJobCallback_maybe
#include "k2000/logic/CKLevel.h"

#include "k2000/io/KHostFS.h"

// 0x0004b688 CKLevel_EnterSector_HostFsStateJobCallback_maybe
uint8_t CKLevel::HostFsStateJobCallback(void* /*data*/, int32_t id, void* /*userData*/) {
    const uint32_t state = static_cast<uint32_t>(KHostFS_GetInstance()->GetDeviceState()) - 3u;  // 0x00051990, 0x000519c8
    static const int32_t kStateJobs[5] = {0xcc, 0xc8, 0xc9, 0xca, 0xca};  // jump table 0x4b6dc
    const int32_t expected = state <= 4 ? kStateJobs[state] : -1;
    return id != expected ? 1 : 0;
}
