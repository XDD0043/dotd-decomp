// CKAnimatedCameraData.cpp - reconstructed original translation unit 0x5c0648-0x5c17a0 (GAME_TOC2, main_toc2), 19 functions, 15 live.
// Primary class: CKAnimatedCameraData  key 0x9e8c  category Logic  size ?  vtable 0xb2fad0
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x5c0648  CKAnimatedCameraData_Delete
//   [ ] 0x5c0698  CKAnimatedCameraData_Construct  [dead]
//   [ ] 0x5c06a8  CKAnimatedCameraData_Construct_2  [dead]
//   [x] 0x5c06b8  CKAnimatedCameraData_vf60  (Vf60, CKAnimatedCameraData.h)
//   [ ] 0x5c06c0  CKAnimatedCameraData_GetEnabledParams_maybe  [dead]
//   [ ] 0x5c0930  RegisterCKAnimatedCameraDataClass
//   [ ] 0x5c09a8  _GLOBAL__I_5c09a8
//   [x] 0x5c09b8  CKAnimatedCameraData_DeleteArray
//   [x] 0x5c0a58  CKAnimatedCameraData_Create
//   [x] 0x5c0a90  CKAnimatedCameraData_CreateArray
//   [x] 0x5c0b20  CKAnimatedCameraData_RecursiveRegistration  (returns 1: the default slot)
//   [x] 0x5c0b28  CKAnimatedCameraData_PostLoad  (CKAnimatedCameraData.h)
//   [x] 0x5c0b70  CKAnimatedCameraData_Destroy  (empty: the default slot)
//   [x] 0x5c0b78  CKAnimatedCameraData_Destructor  (C++ destructor chain: vtable stores only)
//   [x] 0x5c0b90  CKAnimatedCameraData_PickAnimation_maybe
//   [ ] 0x5c1058  CKAnimatedCameraData_Save
//   [ ] 0x5c1318  CKAnimatedCameraData_Destructor_2  [dead]
//   [x] 0x5c1330  CKAnimatedCameraData_DeletingDestructor  (the destructor; delete)
//   [x] 0x5c1370  CKAnimatedCameraData_Load
//
//   [ ] 0x9cd268  CKAnimatedCameraData_GetClassType  [inline]
//   [ ] 0x9cd270  CKAnimatedCameraData_GetClassID  [inline]
//   [x] 0x9cd278  CKAnimatedCameraData_vf54  [inline]
//   [x] 0x9cd2a8  CKAnimatedCameraData_vf58  [inline]
//   [x] 0x9cd2d0  CKAnimatedCameraData_vf5C  [inline]
//   [ ] 0x9cd2f8  CKAnimatedCameraData_IsKindOfClass  [inline]
#include "k2000/logic/animation/CKAnimatedCameraData.h"

#include "k2000/io/IKFile.h"
#include "k2000/misc/ClassRegistry.h"

// 0x005c1370 CKAnimatedCameraData_Load. Each array: the first min(count, 12) entries read, then, when
// count < 11, entries count + 1 .. 11 set to a default.
// BUG(original): entry `count` itself (count < 12) is neither read nor set (the fill starts one too far).
int32_t CKAnimatedCameraData::Load(IKFile* file, int32_t type) {
    if (type != K_LEVEL_PLATEFORMS) return 1;
    ReadF32LE(file, &m_unk04);
    uint8_t count;
    ReadU8(file, &count);
    const int32_t n = count > 12 ? 12 : count;
    for (int32_t i = 0; i < n; ++i) {
        ReadU8(file, &m_aUnk08[i]);
        ReadF32LE(file, &m_aUnk14[i]);
    }
    if (count < 12 && count + 1 < 12) {
        for (int32_t i = count + 1; i < 12; ++i) {
            m_aUnk08[i] = 0;
            m_aUnk14[i] = 0.0f;  // stored as the word 0
        }
    }
    for (int32_t i = 0; i < n; ++i) ReadF32LE(file, &m_aUnk44[i]);
    if (count < 12 && count + 1 < 12) {
        for (int32_t i = count + 1; i < 12; ++i) m_aUnk44[i] = 0.0f;  // the word 0
    }
    for (int32_t i = 0; i < n; ++i) ReadF32LE(file, &m_aUnk74[i]);
    if (count < 12 && count + 1 < 12) {
        for (int32_t i = count + 1; i < 12; ++i) m_aUnk74[i] = 2.0e-1f;  // TOC2 constant 0x3e4ccccd
    }
    for (int32_t i = 0; i < n; ++i) ReadU8(file, &m_aUnkA4[i]);
    if (count < 12 && count + 1 < 12) {
        for (int32_t i = count + 1; i < 12; ++i) m_aUnkA4[i] = 1;
    }
    return 1;
}

// 0x005c0b90 CKAnimatedCameraData_PickAnimation_maybe. The draws: (float)(rand & 0xffff) / 65535.0f * 100.0f (fdivs, fmuls; TOC2
// constants). The weight intervals [sum, sum + weight] are tested in entry order (fcmpu + cror: NaN fails).
uint8_t CKAnimatedCameraData::PickAnimation(uint32_t* index) {
    const float chance = static_cast<float>(static_cast<double>(static_cast<uint32_t>(Rand_Int()) & 0xffffu)) / 65535.0f * 100.0f;
    if (chance >= m_unk04) return 0;
    const float roll = static_cast<float>(static_cast<double>(static_cast<uint32_t>(Rand_Int()) & 0xffffu)) / 65535.0f * 100.0f;
    float weights[12];
    uint32_t ids[12];
    uint32_t count = 0;
    for (uint32_t i = 0; i < 12; ++i) {
        if (m_aUnk08[i] == 0) continue;
        ids[count] = i;
        weights[count] = m_aUnk14[i];
        ++count;
    }
    float sum = 0.0f;
    for (uint32_t k = 0; k < count; ++k) {
        if (roll >= sum && sum + weights[k] >= roll) {
            *index = ids[k];
            return 1;
        }
        sum = sum + weights[k];
    }
    return 0;
}
