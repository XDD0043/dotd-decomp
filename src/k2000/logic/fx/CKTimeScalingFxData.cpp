// CKTimeScalingFxData.cpp - reconstructed original translation unit 0x1d7298-0x1d7d50 (GAME_TOC1, main_toc1), 15 functions, 15 live.
// Primary class: CKTimeScalingFxData  key 0x264c  category Logic  size 0x1c  vtable 0xb1db30
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x1d7298  CKTimeScalingFxData_Delete
//   [x] 0x1d72e8  CKTimeScalingFxData_GetNodeClassKey
//   [x] 0x1d72f0  CKTimeScalingFxData_EvaluateScaleCurve_maybe
//   [ ] 0x1d7378  RegisterCKTimeScalingFxDataClass
//   [ ] 0x1d73f0  _GLOBAL__I_1d73f0
//   [x] 0x1d7400  CKTimeScalingFxData_PostLoad  (= the inherited slot)
//   [ ] 0x1d7428  CKTimeScalingFxData_Save
//   [x] 0x1d7450  CKTimeScalingFxData_RecursiveRegistration  (KStub_Return1_1d8340, nothing: the IKSerializable default slot)
//   [x] 0x1d7478  CKTimeScalingFxData_DeleteArray
//   [x] 0x1d7520  CKTimeScalingFxData_CreateArray
//   [x] 0x1d75c8  CKTimeScalingFxData_Create
//   [x] 0x1d7610  CKTimeScalingFxData_GetInfo  (the default)
//   [x] 0x1d7618  CKTimeScalingFxData_MessageProc
//   [x] 0x1d7af8  CKTimeScalingFxData_Destroy  (in the header)
//   [x] 0x1d7b40  CKTimeScalingFxData_Load
//
//   [ ] 0x9ad650  CKTimeScalingFxData_IsKindOfClass  [inline]
//   [x] 0x9ad688  CKTimeScalingFxData_GetClassType  [inline]
//   [x] 0x9ad690  CKTimeScalingFxData_GetClassID  [inline]
//   [x] 0x9ad698  CKTimeScalingFxData_vf50  [inline]
//   [ ] 0x9ad6a0  CKTimeScalingFxData_DeletingDestructor  [inline]
//   [ ] 0x9ad6f8  CKTimeScalingFxData_Destructor  [inline]
#include "k2000/logic/fx/CKTimeScalingFxData.h"

#include <cstring>

#include "k2000/io/IKFile.h"
#include "k2000/memory/Mem.h"
#include "k2000/logic/fx/CKTimeScalingNodeFx.h"
#include "k2000/misc/Engine.h"
#include "k2000/services/CKSrvFx.h"

namespace {
// One Read of count words, then every word byte-swapped in place (an lwbrx/stw loop on the PS3). The
// file is little-endian: on a little-endian host the bytes stay as they are.
void ReadWordsLE(IKFile* file, void* dst, uint32_t count) {
    ReadRaw(file, dst, count * 4);
    uint8_t* p = static_cast<uint8_t*>(dst);
    for (uint32_t i = 0; i < count; ++i, p += 4) {
        const uint32_t v = static_cast<uint32_t>(p[0]) | (static_cast<uint32_t>(p[1]) << 8) |
                           (static_cast<uint32_t>(p[2]) << 16) | (static_cast<uint32_t>(p[3]) << 24);
        std::memcpy(p, &v, 4);
    }
}
}  // namespace

// 0x001d7b40 CKTimeScalingFxData_Load
int32_t CKTimeScalingFxData::Load(IKFile* file, int32_t type) {
    IKFxData::Load(file, type);
    if (type != K_LEVEL_PLATEFORMS) return 1;
    ReadF32LE(file, &m_unk0c);
    ReadU32LE(file, &m_unk10);
    ReadU8(file, &m_unk08);
    ReadU8(file, &m_nbKeys);
    // Allocated even for 0 keys (the old block, if any, is not freed).
    m_pKeys = static_cast<Key*>(Mem_AllocAligned16(m_nbKeys * static_cast<uint32_t>(sizeof(Key))));
    ReadWordsLE(file, m_pKeys, m_nbKeys * 2u);  // one read of the keys (8 bytes each)
    return 1;
}

// 0x001d72f0 CKTimeScalingFxData_EvaluateScaleCurve_maybe. The original's loop also reads the key after the last one (past
// the block) when t is at or after the last key's time; here that key counts as not containing t.
float CKTimeScalingFxData::EvaluateScaleCurve(float t) const {
    for (uint32_t i = 0; i < m_nbKeys; ++i) {
        const Key& a = m_pKeys[i];
        if (!(a.m_unk00 <= t) || i + 1 >= m_nbKeys) continue;  // fcmpu + cror lt|eq
        const Key& b = m_pKeys[i + 1];
        if (t < b.m_unk00) return a.m_unk04 + (b.m_unk04 - a.m_unk04) * (t - a.m_unk00) / (b.m_unk00 - a.m_unk00);
    }
    return 1.0f;
}

// 0x001d7618 CKTimeScalingFxData_MessageProc
int32_t CKTimeScalingFxData::MessageProc(uint16_t message, void* /*data*/) {
    if (message == 0x1b00) {
        static_cast<CKSrvFx*>(g_pEngine->m_srvFx)->StartEffect(this, this);
        return 0;
    }
    if (message == 0x1b01) {
        CKSrvFx* service = static_cast<CKSrvFx*>(g_pEngine->m_srvFx);
        const uint32_t key = GetAssociatedFxClassIdentifier();  // vt+0x54
        for (uint32_t i = 0; i < service->m_ui32UniqueFxArraySize; ++i) {
            IKSerializable* fx = service->m_apUniqueFxArray[i];
            if (static_cast<uint32_t>((fx->GetClassID() << 6) + fx->GetClassType()) != key) continue;
            static_cast<CKTimeScalingNodeFx*>(fx)->StopIfOwnedBy(this, this);
            break;
        }
    }
    return 1;
}
