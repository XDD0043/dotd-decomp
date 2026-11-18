// IKGrpEnemy.cpp - reconstructed original translation unit 0x2665a0-0x266d20 (GAME_TOC1, main_toc1), 2 functions, 2 live.
// Primary owner: IKGrpEnemy (not a registered class)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x2665a0  IKGrpEnemy_IsAnyEnemyInCone_maybe  (IsAnyEnemyInCone; its callers (CKHkPushObstacle) are not ported yet)
//   [x] 0x2667e0  IKGrpEnemy_Load
#include "k2000/misc/IKGrpEnemy.h"

#include <cmath>
#include <cstring>

#include "Spyro2008/hooks/IKHkEnemy.h"
#include "crt/ppc_ops.h"
#include "crt/xsinf.h"
#include "k2000/groups/TVectorPush.h"
#include "k2000/io/IKFile.h"

namespace {
// The vector read IKGrpEnemy_Load inlines three times: the count, the resize (TVector_ResizeForLoad),
// then each reference read into slot i.
void LoadRefVector(TVector<IKSerializable*, 1>& vector, IKFile* file) {
    uint32_t count = 0;
    ReadU32LE(file, &count);
    TVector_ResizeForLoad(vector, count);
    if (count == 0) return;
    for (uint32_t i = 0; i < count; ++i) IKFile_ReadRef(file, &vector.m_pBlock[i]);
}
}  // namespace

// 0x002667e0 IKGrpEnemy_Load
int32_t IKGrpEnemy::Load(IKFile* file, int32_t type) {
    GroupBasicLoad(file, type);
    if (type != K_LEVEL_PLATEFORMS) return 1;
    LoadRefVector(m_vUnk4c, file);
    IKFile_ReadRef(file, &m_pPoolGrpRoot);
    LoadRefVector(m_vpFZSectorGrpRoot, file);
    LoadRefVector(m_vUnk40, file);
    return 1;
}

// 0x002665a0 IKGrpEnemy_IsAnyEnemyInCone_maybe
uint8_t IKGrpEnemy::IsAnyEnemyInCone(float angle, float maxDistance, const CVector3* position,
                                     const CVector3* direction) {
    for (uint32_t i = m_ui32NbActiveEnemies; i != 0;) {
        --i;
        const CVector3& p = static_cast<IKHkEnemy*>(m_apActiveEnemies[i])->m_v3Position;  // +0x134
        float dy = p.y - position->y;
        float dx = p.x - position->x;
        float dz = p.z - position->z;
        float length = std::sqrt(ppc::fmadds(dz, dz, ppc::fmadds(dx, dx, dy * dy)));  // Math_Sqrtf
        if (length != 0.0f) {
            const float inv = 1.0f / length;
            dz = dz * inv;
            dx = dx * inv;
            dy = dy * inv;
        } else {
            length = 0.0f;
        }
        if (!(length < maxDistance)) continue;  // bge
        int32_t bits;
        std::memcpy(&bits, &angle, 4);
        const float cosine = bits < 0 ? crt::LibCosf(-angle) : crt::InlineCosf(angle);
        const float dot = ppc::fmadds(dz, direction->z, ppc::fmadds(direction->x, dx, dy * direction->y));
        if (dot >= cosine) return 1;  // cror gt|eq, bne
    }
    return 0;
}
