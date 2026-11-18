// CKLightningBoltFxData_2.cpp - reconstructed original translation unit 0x5774e8-0x57a7c8 (GAME_TOC2, main_toc2), 26 functions, 14 live.
// Primary class: CKLightningBoltFxData  key 0xa64c  category Logic  size ?  vtable 0xb2e048
// Other owners: CKLightningBoltNodeFx (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x5774e8  CKLightningBoltFxData_GetNodeClassKey
//   [x] 0x5774f8  CKLightningBoltFxData_PostLoad
//   [x] 0x577548  CKLightningBoltFxData_RandomValue6C_maybe
//   [x] 0x5775b8  CKLightningBoltFxData_RandomInterval58_maybe
//   [x] 0x577630  CKLightningBoltFxData_RandomInterval50_maybe
//   [x] 0x5776a8  CKLightningBoltFxData_RecursiveRegistration
//   [ ] 0x5777f8  CKLightningBoltFxData_GetLevelField10_maybe  [dead]
//   [ ] 0x577830  CKLightningBoltFxData_GetLevelField00_maybe  [dead]
//   [x] 0x577868  CKLightningBoltFxData_CopyEntry60_maybe
//   [ ] 0x5778c0  CKLightningBoltFxData_GetLevelField38_maybe  [dead]
//   [ ] 0x5778f8  CKLightningBoltFxData_GetLevelField34_maybe  [dead]
//   [ ] 0x577930  CKLightningBoltFxData_GetLevelField30_maybe  [dead]
//   [ ] 0x577968  CKLightningBoltFxData_GetLevelField2C_maybe  [dead]
//   [ ] 0x5779a0  CKLightningBoltFxData_GetLevelField24_maybe  [dead]
//   [ ] 0x5779d8  CKLightningBoltFxData_GetLevelField20_maybe  [dead]
//   [ ] 0x577a10  CKLightningBoltFxData_GetLevelField1C_maybe  [dead]
//   [ ] 0x577a48  CKLightningBoltFxData_GetLevelField18_maybe  [dead]
//   [ ] 0x577a80  CKLightningBoltFxData_GetLevelField14_maybe  [dead]
//   [x] 0x577ab8  CKLightningBoltNodeFx_GetBranchLevelScale_maybe
//   [ ] 0x577b38  CKLightningBoltFxData_GetLevelField28_maybe  [dead]
//   [x] 0x577b70  CKLightningBoltFxData_GetInfo  (IKSerializable's: returns 1)
//   [x] 0x577b78  CKLightningBoltFxData_Destroy
//   [x] 0x577bd0  CKLightningBoltFxData_EvaluateColor_maybe
//   [x] 0x578158  CKLightningBoltFxData_Load
//   [ ] 0x578ea8  CKLightningBoltFxData_Save
//   [x] 0x579a10  CKLightningBoltFxData_MessageProc
//
//   [ ] 0x9caf08  CKLightningBoltFxData_IsKindOfClass  [inline]
//   [x] 0x9caf48  CKLightningBoltFxData_GetClassType  [inline]
//   [x] 0x9caf50  CKLightningBoltFxData_GetClassID  [inline]
//   [ ] 0x9caf58  CKLightningBoltFxData_DeletingDestructor  [inline]
//   [ ] 0x9cafe8  CKLightningBoltFxData_Destructor  [inline]
#include "k2000/logic/render/CKLightningBoltFxData.h"

#include <cstring>

#include "crt/ppc_ops.h"
#include "k2000/io/IKFile.h"
#include "k2000/memory/Mem.h"
#include "k2000/misc/ClassRegistry.h"
#include "k2000/fx/IKFx.h"
#include "k2000/hooks/IKHook.h"
#include "k2000/logic/ai/CKMarkerBeacon.h"
#include "k2000/logic/render/CKLightningBoltNodeFx.h"
#include "k2000/misc/Engine.h"
#include "k2000/services/CKSrvFx.h"

// 0x0056eec8 CKLightningBoltFxData_Create, the inlined constructor, in its store order.
CKLightningBoltFxData::CKLightningBoltFxData() {
    // DOTD: the original leaves the source and target (+0x08..+0x14) to the heap (null in LVL010: the heroes set only
    // the source, and the bolt reads the target pointers); the port's heap is not zeroed.
    m_pSourceNode = nullptr;
    m_pSourceHotSpot = nullptr;
    m_pTargetNode = nullptr;
    m_pTargetHotSpot = nullptr;
    m_segments.m_pBlock = nullptr;
    m_segments.m_ui32NbElt = 1;
    m_segments.m_ui32NbUsedElt = 0;
}

// 0x00578158 CKLightningBoltFxData_Load
int32_t CKLightningBoltFxData::Load(IKFile* file, int32_t type) {
    IKFxData::Load(file, type);  // through TocBridge_IKFxData_Load
    if (type != K_LEVEL_PLATEFORMS) return 1;
    ReadF32LE(file, &m_unk1c);
    ReadU16LE(file, &m_unk18);
    ReadRaw(file, m_unk2c, 4);
    ReadRaw(file, m_unk30, 4);
    ReadRaw(file, m_unk34, 4);
    ReadRaw(file, m_unk38, 4);
    ReadF32LE(file, &m_unk3c);
    uint32_t count = 0;
    ReadU32LE(file, &count);
    if (count == 0) {
        m_segments.m_ui32NbElt = 1;
        m_segments.m_pBlock = static_cast<Segment*>(Mem_AllocAligned16(static_cast<uint32_t>(sizeof(Segment))));
    } else {
        m_segments.m_ui32NbElt = count;
        m_segments.m_pBlock = static_cast<Segment*>(Mem_AllocAligned16(count * static_cast<uint32_t>(sizeof(Segment))));
        for (uint32_t i = 0; i < count; ++i) {
            Segment segment;  // read into locals, then copied into the list
            for (uint32_t w = 0; w < 15; ++w) ReadF32LE(file, &segment.m_values[w]);
            const uint32_t used = m_segments.m_ui32NbUsedElt;
            if (m_segments.m_ui32NbElt == used) {  // full: grow by one
                uint32_t capacity = used + 1;
                uint32_t bytes = capacity * static_cast<uint32_t>(sizeof(Segment));
                if (capacity == 0) {
                    capacity = 1;
                    bytes = static_cast<uint32_t>(sizeof(Segment));
                }
                m_segments.m_pBlock = static_cast<Segment*>(Mem_ReallocAligned16(m_segments.m_pBlock, bytes));
                m_segments.m_ui32NbElt = capacity;
            }
            m_segments.m_pBlock[m_segments.m_ui32NbUsedElt] = segment;
            ++m_segments.m_ui32NbUsedElt;
        }
    }
    IKFile_ReadRef(file, &m_unk40);
    IKFile_ReadRef(file, &m_unk44);
    IKFile_ReadRef(file, &m_pSourceExplosion);
    IKFile_ReadRef(file, &m_pEndExplosion);
    ReadF32LE(file, &m_unk50);
    ReadF32LE(file, &m_unk54);
    ReadF32LE(file, &m_unk58);
    ReadF32LE(file, &m_unk5c);
    ReadF32LE(file, &m_unk6c);
    ReadF32LE(file, &m_unk70);
    IKFile_ReadRef(file, &m_unk8c);
    ReadS32LE(file, &m_i32ImpactsMin);  // the same bytes as the original's float read
    ReadS32LE(file, &m_i32ImpactsMax);
    ReadF32LE(file, &m_unk98);
    ReadF32LE(file, &m_unk9c);
    ReadF32LE(file, &m_unka0);
    ReadF32LE(file, &m_unka4);
    ReadF32LE(file, &m_unk88);
    return 1;
}

namespace {
// (rand & 0xffff) / 65535 x -2 (TOC2 -0x746c 65535.0, -0x7468 -2.0): fcfid, frsp, fdivs, fmuls.
float RandSigned() {
    const uint32_t r = static_cast<uint32_t>(Rand_Int()) & 0xffffu;
    return (static_cast<float>(static_cast<double>(r)) / 65535.0f) * -2.0f;
}
}  // namespace

// 0x00577548 CKLightningBoltFxData_RandomValue6C_maybe
float CKLightningBoltFxData::RandomValue6C() {
    const float base = m_unk6c + m_unk70;
    return ppc::fmadds(RandSigned(), m_unk70, base);
}

// 0x005775b8 CKLightningBoltFxData_RandomInterval58_maybe
float CKLightningBoltFxData::RandomInterval58() {
    const float base = m_unk58 + m_unk5c;
    return 1.0f / ppc::fmadds(RandSigned(), m_unk5c, base);  // TOC2 -0x7464 1.0f
}

// 0x00577630 CKLightningBoltFxData_RandomInterval50_maybe
float CKLightningBoltFxData::RandomInterval50() {
    const float base = m_unk50 + m_unk54;
    return 1.0f / ppc::fmadds(RandSigned(), m_unk54, base);
}

// 0x00577868 CKLightningBoltFxData_CopyEntry60_maybe
void* CKLightningBoltFxData::CopyEntry60(void* out, uint32_t index) const {
    std::memmove(out, &m_segments.m_pBlock[index], sizeof(Segment));
    return out;
}

// 0x00577ab8 CKLightningBoltNodeFx_GetBranchLevelScale_maybe
float CKLightningBoltFxData::GetBranchLevelScale(float length, uint32_t level) const {
    if (m_segments.m_ui32NbUsedElt < level) return 1.0f;  // TOC2 -0x7464
    const Segment& s = m_segments.m_pBlock[level];
    const float value = length * s.m_values[1];
    if (value <= s.m_values[3]) return s.m_values[3];
    if (value >= s.m_values[2]) return s.m_values[2];
    return value;
}

namespace {

// fctidz of a channel, its low byte (stb).
uint8_t MixByte(float x) { return static_cast<uint8_t>(ppc::fctidz(x)); }

}  // namespace

// 0x00577bd0 CKLightningBoltFxData_EvaluateColor_maybe: the colour at `t` along the
// strip (0 at the start, 1 at the end) at the bolt's `time`: the start and end colours (+0x2c, +0x30), or with the data's
// flag bit 3 the pair swinging between them and the second pair (+0x34, +0x38) over +0x3c seconds and back.
void CKLightningBoltFxData::EvaluateColor(float time, float t, uint8_t* out) const {
    const CKLightningBoltFxData* data = this;
    uint8_t a[4];
    uint8_t b[4];
    std::memcpy(a, data->m_unk2c, 4);
    std::memcpy(b, data->m_unk30, 4);
    const float one = 1.0f;  // TOC2 -0x7464
    if (((data->m_unk18 >> 3) & 1u) != 0) {
        const float zero = 0.0f;  // TOC2 -0x7460
        const float period = data->m_unk3c;
        const float twice = period + period;
        float x = time;
        if (x < zero) {
            do {
                x = x + twice;
            } while (x < zero);
        }
        const float limit = twice + zero;
        if (x >= limit) {
            do {
                x = x - twice;
            } while (limit <= x);
        }
        auto lerp = [](float u, float v, const uint8_t* p, const uint8_t* q, uint8_t* r) {
            // r = v * p + u * q per channel (fmuls u * q, fmadds v, p, that).
            for (int32_t c = 0; c < 4; ++c) {
                r[c] = MixByte(ppc::fmadds(v, static_cast<float>(p[c]), u * static_cast<float>(q[c])));
            }
        };
        if (period <= x) {
            // Back from the second pair to the first.
            const float u = (x - period) / period;
            const float v = one - u;
            lerp(u, v, data->m_unk34, data->m_unk2c, a);
            lerp(u, v, data->m_unk38, data->m_unk30, b);
        } else {
            const float u = x / period;
            const float v = one - u;
            lerp(u, v, data->m_unk2c, data->m_unk34, a);
            lerp(u, v, data->m_unk30, data->m_unk38, b);
        }
    }
    const float v = one - t;
    for (int32_t c = 0; c < 4; ++c) {
        out[c] = MixByte(ppc::fmadds(v, static_cast<float>(a[c]), t * static_cast<float>(b[c])));
    }
}

// 0x00579a10 CKLightningBoltFxData_MessageProc
int32_t CKLightningBoltFxData::MessageProc(uint16_t message, void* data) {
    IKSerializable* object = message == 0x1b01 ? nullptr : *static_cast<IKSerializable* const*>(data);
    if (message == 0x1b01) {
        if (m_pReservedFx == nullptr) return 0;
        m_pReservedFx->StopAndRelease(this);  // vt+0x58
        m_pReservedFx = nullptr;
        return 0;
    }
    if (message == 0x1b91) {
        if (object == nullptr) return 0;
        // The object's position (+0x04; LVL010 sends CKMarkerBeacons).
        const CKMarkerBeacon* marker = static_cast<const CKMarkerBeacon*>(object);
        m_v3TargetPoint[0] = marker->m_v3Position.x;
        m_v3TargetPoint[2] = marker->m_v3Position.z;
        m_v3TargetPoint[1] = marker->m_v3Position.y;
        m_pTargetHotSpot = nullptr;
        m_bHasTargetPoint = 1;
        m_pTargetNode = nullptr;
        return 0;
    }
    if (message == 0x1b92) {
        if (object == nullptr) return 0;
        m_v3TargetPoint[0] = 0.0f;  // 0x00c50d64
        m_v3TargetPoint[2] = 0.0f;
        m_v3TargetPoint[1] = 0.0f;
        m_bHasTargetPoint = 0;
        IKSerializable* node = static_cast<IKHook*>(object)->m_pKGLObject;  // +0x1c
        if (node->IsKindOfClass(0xcb) == 0) return 0;  // a CNode
        m_pTargetHotSpot = nullptr;
        m_pTargetNode = node;
        return 0;
    }
    if (message != 0x1b00 && message != 0x1b02) return 1;
    if (object == nullptr) return 0;
    if (message == 0x1b00) {
        m_pSourceHotSpot = nullptr;
        m_pSourceNode = nullptr;
    } else {
        IKSerializable* node = static_cast<IKHook*>(object)->m_pKGLObject;  // +0x1c
        if (node->IsKindOfClass(0xcb) != 0) {
            m_pSourceNode = node;
            m_pSourceHotSpot = nullptr;
        }
    }
    CKSrvFx* service = static_cast<CKSrvFx*>(g_pEngine->m_srvFx);
    IKFx* fx;
    if ((m_unk18 & 2) == 0 && (m_unk18 & 1) == 0) {
        if (m_pReservedFx != nullptr) return 0;
        fx = service->AcquireFx(this, this);  // the reserving pool lookup, inlined
        m_pReservedFx = fx;
    } else {
        fx = service->StartEffect(this, this);  // inlined (pooled: the first free one; unique: SetDataAndOwner)
    }
    if (fx == nullptr) return 0;
    CKLightningBoltNodeFx* bolt = static_cast<CKLightningBoltNodeFx*>(fx);
    if (message == 0x1b00) {
        const CVector3 position = static_cast<const CKMarkerBeacon*>(object)->m_v3Position;
        bolt->SetNodePosition(&position, this);  // 0x0057c430
    }
    if (m_bHasTargetPoint != 0) {
        const CVector3 target = {m_v3TargetPoint[0], m_v3TargetPoint[1], m_v3TargetPoint[2]};
        bolt->SetTargetPoint(&target, this);  // 0x0057a9d0
    }
    bolt->SetActiveForOwner(this, 1);  // 0x00581380
    return 0;
}

// 0x005774f8 CKLightningBoltFxData_PostLoad (the zero vector at 0x00c50d64)
int32_t CKLightningBoltFxData::PostLoad(int32_t type) {
    if (type != 0) return 1;
    m_pSourceNode = nullptr;
    m_pSourceHotSpot = nullptr;
    m_pTargetNode = nullptr;
    m_pTargetHotSpot = nullptr;
    m_v3TargetPoint[0] = 0.0f;
    m_v3TargetPoint[2] = 0.0f;
    m_v3TargetPoint[1] = 0.0f;
    m_pReservedFx = nullptr;
    m_bHasTargetPoint = 0;
    return 1;
}

// 0x005776a8 CKLightningBoltFxData_RecursiveRegistration (KStub_Return1_1d8340 first: nothing)
void CKLightningBoltFxData::RecursiveRegistration(int32_t type) {
    if (type != 0) return;
    m_unk40->RecursiveRegistration(0);  // vt+0x24
    m_unk44->RecursiveRegistration(0);
    m_pSourceExplosion->RecursiveRegistration(0);
    m_pEndExplosion->RecursiveRegistration(0);
    if (m_unk8c != nullptr) m_unk8c->RecursiveRegistration(0);
}

// 0x00577b78 CKLightningBoltFxData_Destroy (TocBridge_Mem_FreeAligned16)
void CKLightningBoltFxData::Destroy() {
    if (m_segments.m_pBlock != nullptr) {
        Mem_FreeAligned16(m_segments.m_pBlock);
        m_segments.m_pBlock = nullptr;
    }
    m_segments.m_ui32NbUsedElt = 0;
    m_segments.m_pBlock = nullptr;
}
