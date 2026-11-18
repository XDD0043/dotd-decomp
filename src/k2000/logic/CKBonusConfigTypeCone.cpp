// CKBonusConfigTypeCone.cpp - reconstructed original translation unit 0x128258-0x128e18 (GAME_TOC1, main_toc1), 16 functions, 16 live.
// Primary class: CKBonusConfigTypeCone  key 0x2d0c  category Logic  size 0x18  vtable 0xb19ea8
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x128258  CKBonusConfigTypeCone_Delete
//   [ ] 0x1282a8  RegisterCKBonusConfigTypeConeClass
//   [ ] 0x128320  _GLOBAL__I_128320
//   [ ] 0x128330  CKBonusConfigTypeCone_Save
//   [x] 0x128358  CKBonusConfigTypeCone_RecursiveRegistration  (the base's only: CKBonusConfigType 0x127530 returns 1)
//   [x] 0x128380  CKBonusConfigTypeCone_Destroy  (inherited: CKBonusConfigType_2c8c_maybe_vf10)
//   [x] 0x1283a8  CKBonusConfigTypeCone_DeletingDestructor  (C++ deleting destructor)
//   [x] 0x1283f0  CKBonusConfigTypeCone_Destructor  (C++ destructor chain: vtable stores only)
//   [x] 0x128420  CKBonusConfigTypeCone_DestructBody  (C++ destructor chain: vtable stores only)
//   [x] 0x128450  CKBonusConfigTypeCone_Construct
//   [x] 0x128488  CKBonusConfigTypeCone_Construct_2  (the constructor)
//   [x] 0x1284c0  CKBonusConfigTypeCone_DeleteArray
//   [x] 0x128568  CKBonusConfigTypeCone_CreateArray
//   [x] 0x128620  CKBonusConfigTypeCone_Create
//   [x] 0x128678  CKBonusConfigTypeCone_Load
//   [x] 0x1287e8  CKBonusConfigTypeCone_GenerateSpawns_maybe
//
//   [ ] 0x9a70e8  CKBonusConfigTypeCone_IsKindOfClass  [inline]
//   [x] 0x9a7110  CKBonusConfigTypeCone_GetClassType  [inline]
//   [x] 0x9a7118  CKBonusConfigTypeCone_GetClassID  [inline]
//   [x] 0x9a7120  CKBonusConfigTypeCone_GetLayoutType_maybe  [inline]
#include "k2000/logic/CKBonusConfigTypeCone.h"

#include "k2000/io/IKFile.h"
#include "k2000/math/Vec3.h"
#include "k2000/misc/ClassRegistry.h"
#include "k2000/misc/Engine.h"
#include "k2000/services/KBase201.h"
#include "crt/ppc_ops.h"
#include "crt/xsinf.h"

#include <cmath>
#include <cstring>

// 0x00128678 CKBonusConfigTypeCone_Load: the same for every type.
int32_t CKBonusConfigTypeCone::Load(IKFile* file, int32_t type) {
    CKBonusConfigType::Load(file, type);
    ReadF32LE(file, &m_unk08);
    ReadF32LE(file, &m_unk0c);
    ReadF32LE(file, &m_unk10);
    ReadF32LE(file, &m_unk14);
    return 1;
}

namespace {
bool SignBitSet(float x) {
    int32_t bits;
    std::memcpy(&bits, &x, 4);
    return bits < 0;
}
}  // namespace

// 0x001287e8 CKBonusConfigTypeCone_GenerateSpawns_maybe: the count (mode 0: one draw in [+0x04, +0x08]; mode 1: a total
// drawn the first time (+0x18 -1 or past +0x08, one draw) then its share +0x1c of +0x14 each call, +0x18 what is left),
// then per spawn (the last index first): its angle across the cone (+0x14 degrees split in equal parts, each part
// jittered by a draw with `randomAngle`) about `dir`'s yaw, the flat direction (-sin, 0, cos; `dir` itself without a
// cone), one draw for the speed in [+0x0c, +0x10]: the velocity's x / z from `base` along the direction less `pos`,
// its y +0x08; started (CKSrvBonus vt+0xa8, the last spawn flagged) or queued (BonusSpawnList_Add_maybe).
void CKBonusConfigTypeCone::GenerateSpawns(CKBonusData::Entry* entry, const CVector3* pos, const CVector3* dir, const CVector3* base,
                                           uint8_t immediate, uint8_t randomAngle) {
    uint32_t count = 0;
    if (entry->m_unk10 == 0) {
        const uint32_t least = entry->m_unk04;
        const uint32_t r = static_cast<uint32_t>(Rand_Int()) & 0xffffu;  // 0x00011500
        count = least + ((r * (entry->m_unk08 - least + 1u)) >> 16);     // mullw, srwi
    } else if (entry->m_unk10 == 1) {
        int32_t left = static_cast<int32_t>(entry->m_unk18);
        if (left == -1 || static_cast<int32_t>(entry->m_unk08) < left) {
            entry->m_unk18 = entry->m_unk04;
            const uint32_t r = static_cast<uint32_t>(Rand_Int()) & 0xffffu;
            const uint32_t total = entry->m_unk18 + ((r * (entry->m_unk08 - entry->m_unk18 + 1u)) >> 16);
            entry->m_unk18 = total;
            entry->m_unk14 = total;
            left = static_cast<int32_t>(total);
        }
        float share;
        std::memcpy(&share, &entry->m_unk1c, 4);
        int32_t n = static_cast<int32_t>(ppc::fctidz(static_cast<float>(static_cast<double>(entry->m_unk14)) * share));
        if (n > left) {
            n = left;
            entry->m_unk18 = 0;
        } else {
            const int32_t rest = left - n;
            entry->m_unk18 = static_cast<uint32_t>(rest < 0 ? 0 : rest);
        }
        count = static_cast<uint32_t>(n);
    }
    const float step = count != 0 ? m_unk14 / static_cast<float>(static_cast<double>(count)) : 0.0f;  // TOC1 -0x4170
    KBase201* service = static_cast<KBase201*>(g_pEngine->m_srvBonus);  // TOC1 -0x4174 -> +0x64
    for (uint32_t i = count; i != 0;) {
        --i;
        CVector3 d;
        if (m_unk14 == 0.0f) {
            d = *dir;
        } else {
            float jitter = 0.0f;
            if (randomAngle != 0) {
                const uint32_t r = static_cast<uint32_t>(Rand_Int()) & 0xffffu;
                jitter = step * (static_cast<float>(static_cast<double>(r)) / 65535.0f);  // TOC1 -0x4184
            }
            const float half = m_unk14 * -0.5f;                                                       // TOC1 -0x4180
            float angle = ppc::fmadds(step, static_cast<float>(static_cast<double>(i)), half);
            angle = (jitter + angle) * 0.0174532905f;                                                // TOC1 -0x417c
            const float yaw = Vec3_GetYawAngleFromX(dir);                                            // 0x00244638
            angle = angle + (yaw - 1.57079637f);                                                     // TOC1 -0x4178
            const float sine = SignBitSet(angle) ? crt::LibSinf(angle) : crt::InlineSinf(angle);  // 0x009a1390 / inline
            const float x = -sine;
            const float cosine = SignBitSet(angle) ? crt::LibCosf(angle) : crt::InlineCosf(angle);  // 0x009a11d8 / inline
            d = {x, 0.0f, cosine};
            const float length = std::sqrt(ppc::fmadds(cosine, cosine, ppc::fmadds(x, x, 0.0f)));  // 0x00010690
            if (length != 0.0f) {
                const float k = 1.0f / length;
                d.z = d.z * k;
                d.x = d.x * k;
                d.y = d.y * k;
            }
        }
        const uint32_t r = static_cast<uint32_t>(Rand_Int()) & 0xffffu;
        const float speed = ppc::fmadds(static_cast<float>(static_cast<double>(r)) / 65535.0f, m_unk10 - m_unk0c, m_unk0c);
        CVector3 vel;
        vel.y = m_unk08;
        vel.z = ppc::fmadds(speed, d.z, base->z) - pos->z;
        vel.x = ppc::fmadds(speed, d.x, base->x) - pos->x;
        if (immediate == 0) {
            service->AddDelayedSpawn(entry->m_unk00, pos, &vel);  // 0x001268d0
        } else {
            service->SpawnBonusWithVelocity(entry->m_unk00, &pos->x, &vel.x, i == 0 ? 1 : 0);  // vt+0xa8
        }
    }
}
