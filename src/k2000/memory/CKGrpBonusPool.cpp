// CKGrpBonusPool.cpp - reconstructed original translation unit: 0x5b1348-0x5b15e0 (GAME_TOC2, main_toc2), 11 functions, 7 live.
// Primary owner: CKGrpBonusPool (not a registered class)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x5b1348  CKGrpBonusPool_Destroy  (the Delete factory: DOTD_DECLARE_FACTORIES(CKGrpBonusPool); port-rest R07)
//   [x] 0x5b1398  CKGrpBonusPool_vfB8  (VfB8 in the header (returns 0x5c; no slot in IKBaseGroup); port-rest R07)
//   [x] 0x5b13a0  CKGrpBonusPool_vfF0
//   [x] 0x5b13e0  CKGrpBonusPool_vf100  (Vf100 in the header (empty); port-rest R07; CKGrpS08BonusPool inherits it)
//   [x] 0x5b13e8  CKGrpBonusPool_vf110  (Vf110 in the header; port-rest R07; CKGrpS08BonusPool inherits it)
//   [ ] 0x5b1458  CKGrpBonusPool_BonusList_PushFront_maybe  [dead]
//   [ ] 0x5b1468  CKGrpBonusPool_BonusList_PopFront_maybe  [dead]
//   [ ] 0x5b1490  CKGrpBonusPool_BonusList_TakeAll_maybe  [dead]
//   [ ] 0x5b14a8  CKGrpBonusPool_BonusList_Append_maybe  [dead]
//   [x] 0x5b1508  CKGrpBonusPool_SetBonusTrailEndpoints_maybe
//   [x] 0x5b15b8  CKGrpBonusPool_PostLoad  (header)
#include "k2000/memory/CKGrpBonusPool.h"

#include "crt/ppc_ops.h"
#include "k2000/scenegraph/CTrailNodeFx.h"

// 0x005b1508 CKGrpBonusPool_SetBonusTrailEndpoints_maybe: ribbon `index`'s two extremes (its stored anchors, mode 1):
// the position plus / minus the half height (+0x5c) along y, or along `up` with +0x60.
void CKGrpBonusPool::SetBonusTrailEndpoints(uint32_t index, const CVector3* position, const CVector3* up) {
    if (m_pUnk58 == nullptr) return;
    const float px = position->x;
    const float pz = position->z;
    const float py = position->y;
    float ax = px, ay, az = pz;  // the first extreme
    float bx = px, by, bz = pz;  // the second
    if (m_unk60 != 0) {
        const float h = m_unk5c;
        const float n = -h;
        ax = ppc::fmadds(h, up->x, px);
        ay = ppc::fmadds(h, up->y, py);
        bx = ppc::fmadds(up->x, n, px);
        by = ppc::fmadds(up->y, n, py);
        bz = ppc::fmadds(up->z, n, pz);
        az = ppc::fmadds(h, up->z, pz);
    } else {
        by = py - m_unk5c;
        ay = py + m_unk5c;
    }
    STrailNodeData* trail = static_cast<CTrailNodeFx*>(m_pUnk58)->m_apTrailData[index & 0xffu];
    trail->m_v3Extrem1.z = az;
    trail->m_v3Extrem1.x = ax;
    trail->m_v3Extrem1.y = ay;
    trail->m_v3Extrem2.z = bz;
    trail->m_v3Extrem2.x = bx;
    trail->m_v3Extrem2.y = by;
}
