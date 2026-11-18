// PxJointRows.h - the CKPx joints' shared row helpers (C2.8 port-last Z7). The joints' solver slots (their vf60 Solve)
// inline these patterns over and over; each helper computes exactly what every inlined copy computes (the components
// are independent, so the original's interleaving does not change a bit).
#pragma once
#include <cmath>

#include "crt/ppc_ops.h"
#include "k2000/logic/CKPxBody.h"

namespace pxrows {

// The velocity of `body` at the arm `r` from its position: v + w x r (the x part fmsubs(w.y, r.z, w.z * r.y), ...).
inline CVector3 VelocityAt(const CKPxBody* body, const CVector3& r) {
    const CVector3& w = body->m_unkb8;
    const CVector3& v = body->m_unka4;
    const float cx = ppc::fmsubs(w.y, r.z, w.z * r.y);
    const float cy = ppc::fmsubs(w.z, r.x, r.z * w.x);
    const float cz = ppc::fmsubs(r.y, w.x, w.y * r.x);
    return CVector3{cx + v.x, cy + v.y, cz + v.z};
}

// a . b as the solvers take it: fmadds(a.z, b.z, fmadds(a.x, b.x, a.y * b.y)).
inline float Dot(const CVector3& a, const CVector3& b) { return ppc::fmadds(a.z, b.z, ppc::fmadds(a.x, b.x, a.y * b.y)); }

// |v| (Math_Sqrtf 0x10690).
inline float Length(const CVector3& v) { return std::sqrt(Dot(v, v)); }

// a - b.
inline CVector3 Sub(const CVector3& a, const CVector3& b) { return CVector3{a.x - b.x, a.y - b.y, a.z - b.z}; }

// a + b.
inline CVector3 Add(const CVector3& a, const CVector3& b) { return CVector3{a.x + b.x, a.y + b.y, a.z + b.z}; }

// The row's direction normalised in place when its length is not 0 (1 / length times each part); the length returned.
inline float NormaliseRow(CKPxBody::Record* row) {
    const float length = Length(row->m_vNormal);
    if (length != 0.0f) {
        const float inverse = 1.0f / length;
        row->m_vNormal = CVector3{inverse * row->m_vNormal.x, inverse * row->m_vNormal.y, inverse * row->m_vNormal.z};
    }
    return length;
}

}  // namespace pxrows
