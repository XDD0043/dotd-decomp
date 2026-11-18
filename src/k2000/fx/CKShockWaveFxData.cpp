// CKShockWaveFxData.cpp - reconstructed original translation unit 0x1d1288-0x1d22e8 (GAME_TOC1, main_toc1), 16 functions, 15 live.
// Primary owner: CKShockWaveFxData (not a registered class)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [ ] 0x1d1288  CKShockWaveFxData_ConstructBase_2_maybe  [dead]
//   [x] 0x1d12b0  CKShockWaveFxData_GetNodeClassKey
//   [x] 0x1d12b8  CKShockWaveFxData_EvalRadiusScale_maybe
//   [x] 0x1d1388  CKShockWaveFxData_EvalHeightScale_maybe
//   [x] 0x1d1458  CKShockWaveFxData_EvalAlpha_maybe
//   [x] 0x1d1500  CKShockWaveFxData_PostLoad
//   [x] 0x1d1548  CKShockWaveFxData_LevelReset  (RecursiveRegistration: IKFxData's, nothing; the default)
//   [x] 0x1d1570  CKShockWaveFxData_DeletingDestructor  (C++ deleting destructor)
//   [x] 0x1d15c8  CKShockWaveFxData_ConstructBase_maybe
//   [x] 0x1d15f0  CKShockWaveFxData_vf40  (GetInfo: 1, the default)
//   [x] 0x1d15f8  CKShockWaveFxData_HandleMessage
//   [x] 0x1d1950  CKShockWaveFxData_ClearReferences  (Destroy)
//   [x] 0x1d19e8  CKShockWaveFxData_Destructor  (C++ destructor chain: vtable stores only)
//   [x] 0x1d1a28  CKShockWaveFxData_BaseDestructor  (C++ destructor chain)
//   [x] 0x1d1a68  CKShockWaveFxData_Load
//   [ ] 0x1d1ef0  CKShockWaveFxData_Save
//
//   [ ] 0x9ad1d8  CKShockWaveFxData_IsKindOf  [inline]
//   [x] 0x9ad210  CKShockWaveFxData_GetClassGroup  [inline]
//   [x] 0x9ad218  CKShockWaveFxData_GetClassId  [inline]
#include "k2000/fx/CKShockWaveFxData.h"
#include <cstring>

#include "k2000/io/IKFile.h"
#include "k2000/logic/fx/CKShockWaveNodeFx.h"
#include "k2000/math/CMatrix34.h"
#include "k2000/math/Quat.h"
#include "k2000/misc/Engine.h"
#include "k2000/services/CKSrvFx.h"

namespace {
// A count, then new[] of count keys read in one block and byte-swapped word by word.
CKShockWaveFxData::Key* ReadKeys(IKFile* file, uint32_t count) {
    CKShockWaveFxData::Key* keys = new CKShockWaveFxData::Key[count];
    ReadU32LEWords(file, reinterpret_cast<uint32_t*>(keys), count * 2);
    return keys;
}
}  // namespace

// 0x001d15c8 CKShockWaveFxData_ConstructBase_maybe, in its store order.
CKShockWaveFxData::CKShockWaveFxData() {
    m_pDamage3c = nullptr;
    m_unk24 = nullptr;
    m_unk1c = nullptr;
    m_unk14 = nullptr;
}

// 0x001d1a68 CKShockWaveFxData_Load
int32_t CKShockWaveFxData::Load(IKFile* file, int32_t type) {
    IKFxData::Load(file, type);
    if (type != K_LEVEL_PLATEFORMS) return 1;
    ReadF32LE(file, &m_unk08);
    ReadF32LE(file, &m_unk0c);
    ReadU32LE(file, &m_unk18);
    m_unk1c = ReadKeys(file, m_unk18);
    ReadU32LE(file, &m_unk10);
    m_unk14 = ReadKeys(file, m_unk10);
    ReadU32LE(file, &m_unk20);
    m_unk24 = ReadKeys(file, m_unk20);
    ReadU8(file, &m_unk30);
    ReadF32LE(file, &m_unk34);
    ReadF32LE(file, &m_unk38);
    ReadRaw(file, m_unk40, 4);
    return 1;
}

// 0x001d1500 CKShockWaveFxData_PostLoad
int32_t CKShockWaveFxData::PostLoad(int32_t type) {
    IKFxData::PostLoad(type);  // 0x1d8338 KStub_Return1_1d8338
    m_unk2c = 1.0f;            // lfs -0x1ab0(r2)
    m_pDamage3c = nullptr;
    return 1;
}

namespace {
// The shared key walk of the three evaluators: `t` already divided by the duration.
float EvalKeys(const CKShockWaveFxData::Key* keys, uint32_t count, float t) {
    if (count != 1) {
        for (uint32_t i = 0; i + 1 < count; ++i) {
            const float t0 = keys[i].m_unk00;
            if (!(t >= t0)) continue;  // cror gt / eq
            const float t1 = keys[i + 1].m_unk00;
            if (!(t < t1)) continue;
            const float v0 = keys[i].m_unk04;
            return v0 + (keys[i + 1].m_unk04 - v0) * (t - t0) / (t1 - t0);
        }
    }
    return keys[count - 1].m_unk04;
}
}  // namespace

// 0x001d12b8 CKShockWaveFxData_EvalRadiusScale_maybe
float CKShockWaveFxData::EvalRadiusScale(float time) const {
    const float scale = ((m_unk30 >> 1) & 1u) != 0 ? m_unk2c : 1.0f;  // TOC -0x1ab0
    return scale * EvalKeys(m_unk1c, m_unk18, time / m_unk08);
}

// 0x001d1388 CKShockWaveFxData_EvalHeightScale_maybe
float CKShockWaveFxData::EvalHeightScale(float time) const {
    float scale = 1.0f;
    if ((m_unk30 & 1u) != 0) std::memcpy(&scale, &m_unk28, sizeof scale);
    return scale * EvalKeys(m_unk14, m_unk10, time / m_unk08);
}

// 0x001d1458 CKShockWaveFxData_EvalAlpha_maybe
float CKShockWaveFxData::EvalAlpha(float time) const { return EvalKeys(m_unk24, m_unk20, time / m_unk08); }

// 0x001d1950 CKShockWaveFxData_ClearReferences (Destroy)
void CKShockWaveFxData::Destroy() {
    if (m_unk1c != nullptr) {
        delete[] m_unk1c;  // TocBridge_OperatorDeleteArray (the count cookie at -4)
        m_unk1c = nullptr;
    }
    if (m_unk14 != nullptr) {
        delete[] m_unk14;
        m_unk14 = nullptr;
    }
    if (m_unk24 != nullptr) {
        delete[] m_unk24;
        m_unk24 = nullptr;
    }
}

namespace {
// The 0x1b00 payload (no sender ported yet; _maybe a beacon or transform record): a position at +0x04 and a
// quaternion at +0x10, as CKInputIconFxData's.
struct ShockWavePlacement {
    uint32_t m_unk00;
    float m_pos[3];   // +0x04
    float m_quat[4];  // +0x10
};
}  // namespace

// 0x001d15f8 CKShockWaveFxData_HandleMessage (MessageProc)
int32_t CKShockWaveFxData::MessageProc(uint16_t message, void* data) {
    if (message != 0x1b00) return 1;
    const ShockWavePlacement* object = nullptr;
    std::memcpy(&object, data, sizeof(object));
    if (object == nullptr) return 0;
    CMatrix34 matrix;
    Quat_ToMatrixNormalizing(object->m_quat, &matrix);  // 0x241d78
    matrix.m_pos = CVector3{object->m_pos[0], object->m_pos[1], object->m_pos[2]};
    matrix.m_ui32Flags &= ~0x20000u;
    CKSrvFx* service = static_cast<CKSrvFx*>(g_pEngine->m_srvFx);  // TOC1 -0x1aa4 -> +0x60
    IKFx* node = service->AcquireFx(this, this);
    if (node == nullptr) return 0;
    CKShockWaveNodeFx* wave = static_cast<CKShockWaveNodeFx*>(node);
    wave->SetDirection(&matrix.m_at, this);  // 0x001d3340
    wave->SetPosition(&matrix.m_pos, this);  // 0x001d2410 FxAttachment_SetPositionIfOwner_maybe
    wave->Trigger(this);                     // 0x001d2928
    wave->ReleaseReservation(this);          // vt+0x54
    return 0;
}
