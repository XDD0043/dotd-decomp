// CKBonusConfigTypeStar.cpp - reconstructed original translation unit 0x1275b0-0x128258 (GAME_TOC1, main_toc1), 16 functions, 16 live.
// Primary class: CKBonusConfigTypeStar  key 0x2f8c  category Logic  size 0x1c  vtable 0xb19e48
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x1275b0  CKBonusConfigTypeStar_Delete
//   [ ] 0x127600  RegisterCKBonusConfigTypeStarClass
//   [ ] 0x127678  _GLOBAL__I_127678
//   [ ] 0x127688  CKBonusConfigTypeStar_Save
//   [x] 0x1276b0  CKBonusConfigTypeStar_RecursiveRegistration  (the base's only: CKBonusConfigType 0x127530 returns 1)
//   [x] 0x1276d8  CKBonusConfigTypeStar_Destroy  (inherited: CKBonusConfigType_2c8c_maybe_vf10)
//   [x] 0x127700  CKBonusConfigTypeStar_DeletingDestructor  (C++ deleting destructor)
//   [x] 0x127748  CKBonusConfigTypeStar_Destructor  (C++ destructor chain: vtable stores only)
//   [x] 0x127778  CKBonusConfigTypeStar_DestructBody  (C++ destructor chain: vtable stores only)
//   [x] 0x1277a8  CKBonusConfigTypeStar_Construct
//   [x] 0x1277e0  CKBonusConfigTypeStar_Construct_2  (the constructor)
//   [x] 0x127818  CKBonusConfigTypeStar_DeleteArray
//   [x] 0x1278c0  CKBonusConfigTypeStar_Create
//   [x] 0x127918  CKBonusConfigTypeStar_CreateArray
//   [x] 0x1279d0  CKBonusConfigTypeStar_Load
//   [x] 0x127b78  CKBonusConfigTypeStar_GenerateSpawns_maybe
//
//   [ ] 0x9a70a8  CKBonusConfigTypeStar_IsKindOfClass  [inline]
//   [x] 0x9a70d0  CKBonusConfigTypeStar_GetClassType  [inline]
//   [x] 0x9a70d8  CKBonusConfigTypeStar_GetClassID  [inline]
//   [x] 0x9a70e0  CKBonusConfigTypeStar_GetLayoutType_maybe  [inline]
#include "k2000/logic/CKBonusConfigTypeStar.h"

#include "k2000/io/IKFile.h"
#include "k2000/math/Vec3.h"
#include "k2000/misc/ClassRegistry.h"
#include "k2000/misc/Engine.h"
#include "k2000/services/KBase201.h"
#include "crt/ppc_ops.h"
#include "crt/xsinf.h"

#include <cmath>
#include <cstring>

// 0x001279d0 CKBonusConfigTypeStar_Load: the same for every type.
int32_t CKBonusConfigTypeStar::Load(IKFile* file, int32_t type) {
    CKBonusConfigType::Load(file, type);
    ReadF32LE(file, &m_unk08);
    ReadF32LE(file, &m_unk0c);
    ReadF32LE(file, &m_unk10);
    ReadU8(file, &m_unk14);
    ReadF32LE(file, &m_unk18);
    return 1;
}

namespace {
bool SignBitSet(float x) {
    int32_t bits;
    std::memcpy(&bits, &x, 4);
    return bits < 0;
}
}  // namespace

// 0x00127b78 CKBonusConfigTypeStar_GenerateSpawns_maybe: the count as CKBonusConfigTypeCone's (mode 0: one draw in
// [+0x04, +0x08]; mode 1: a total drawn the first time, then its share +0x1c of +0x14 each call). The spawns (the last
// index first) are shared among the star's arms (+0x14, a byte; an arm every 2 pi / arms about `dir`'s yaw): an arm takes
// over when index x arms falls below the remaining arms x count. The flat direction of the arm (-sin, 0, cos, through the
// inlined or the library sine / cosine as the sign asks); with `randomAngle` one draw for the distance in [+0x0c, +0x10],
// else the index within the arm as the step; then one draw for a sideways offset ((1 - r / 32768) x +0x18 / 2, across
// the arm). The velocity's x / z from `base` less `pos`, its y +0x08; started (CKSrvBonus vt+0xa8, the last spawn
// flagged) or queued (BonusSpawnList_Add_maybe 0x1268d0).
void CKBonusConfigTypeStar::GenerateSpawns(CKBonusData::Entry* entry, const CVector3* pos, const CVector3* dir,
                                           const CVector3* base, uint8_t immediate, uint8_t randomAngle) {
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
    uint32_t arm = m_unk14;
    uint32_t armLimit = arm * count;  // mullw
    uint32_t armStart = count;
    const float step = 6.28318548f / static_cast<float>(static_cast<int32_t>(m_unk14));  // TOC1 -0x41e8
    KBase201* service = static_cast<KBase201*>(g_pEngine->m_srvBonus);                // TOC1 -0x41d4 -> +0x64
    for (uint32_t i = count; i != 0;) {
        --i;
        if (i * m_unk14 < armLimit) {  // cmplw
            --arm;
            armLimit -= count;
            armStart = i;
        }
        const float armAngle = static_cast<float>(static_cast<double>(arm));
        const float yaw = Vec3_GetYawAngleFromX(dir);  // 0x00244638
        const float angle = step * armAngle + (yaw - 1.57079637f);  // TOC1 -0x41e4
        const float sine = SignBitSet(angle) ? crt::LibSinf(angle) : crt::InlineSinf(angle);  // 0x009a1390 / inline
        const float x = -sine;
        const float cosine = SignBitSet(angle) ? crt::LibCosf(angle) : crt::InlineCosf(angle);  // 0x009a11d8 / inline
        CVector3 d = {x, 0.0f, cosine};
        const float length = std::sqrt(ppc::fmadds(cosine, cosine, ppc::fmadds(x, x, 0.0f)));  // 0x00010690
        if (length != 0.0f) {
            const float k = 1.0f / length;
            d.z = d.z * k;
            d.x = d.x * k;
            d.y = d.y * k;
        }
        CVector3 p;
        if (randomAngle == 0) {
            const float along = static_cast<float>(static_cast<double>(armStart - i));
            const float distance = ppc::fmadds(along, m_unk10 - m_unk0c, m_unk0c);
            p.z = ppc::fmadds(d.z, distance, base->z);
            p.x = ppc::fmadds(d.x, distance, base->x);
            p.y = ppc::fmadds(distance, d.y, base->y);
        } else {
            const uint32_t r = static_cast<uint32_t>(Rand_Int()) & 0xffffu;
            const float distance =
                ppc::fmadds(static_cast<float>(static_cast<double>(r)) / 65535.0f, m_unk10 - m_unk0c, m_unk0c);  // TOC1 -0x41e0
            p.z = ppc::fmadds(distance, d.z, base->z);
            p.x = ppc::fmadds(distance, d.x, base->x);
            p.y = ppc::fmadds(distance, d.y, base->y);
        }
        const uint32_t r = static_cast<uint32_t>(Rand_Int()) & 0xffffu;
        float side = ppc::fmadds(static_cast<float>(static_cast<double>(r)), -0x1.0001p-15f, 1.0f);  // TOC1 -0x41dc
        side = side * m_unk18;
        side = side * 0.5f;  // TOC1 -0x41d8
        CVector3 vel;
        vel.y = m_unk08;
        vel.z = ppc::fmadds(-d.x, side, p.z) - pos->z;
        vel.x = ppc::fmadds(d.z, side, p.x) - pos->x;
        if (immediate == 0) {
            service->AddDelayedSpawn(entry->m_unk00, pos, &vel);  // 0x001268d0
        } else {
            service->SpawnBonusWithVelocity(entry->m_unk00, &pos->x, &vel.x, i == 0 ? 1 : 0);  // vt+0xa8
        }
    }
}
