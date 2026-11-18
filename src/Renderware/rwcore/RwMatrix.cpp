// RwMatrix.cpp - RW 3.7 matrix and vector maths (rwcore matrix.c, vector.c), ported from the PS3
// assembly (library TOC 0xc25974). See RwMatrix.h.
//
// Operation order, fused vs separate multiply-adds and float vs double follow the assembly exactly.
// RwMatrixMultiply is VMX code on the PS3 (lvlx/lvrx, vspltw, vmaddfp); the vmx:: helpers below give
// vmaddfp's results: one rounding (fused) and the non-Java mode (VSCR[NJ] = 1, the Cell PPU default):
// denormal inputs and results are flushed to zero. That only matters for the w lanes, which carry the
// flags and pad words of the inputs (0x20003 as a float is a denormal) into the output's pads.
#include "Renderware/rwcore/RwMatrix.h"

#include <cmath>
#include <cstddef>
#include <cstring>
#include <vector>

#include "Renderware/rwcore/RwSList.h"
#include "Renderware/rwcore/RwStream.h"
#include "crt/ppc_ops.h"
#include "crt/xsin.h"

namespace {

// ---- bit access -------------------------------------------------------------------------------
inline RwUInt32 Bits(RwReal x) {
    RwUInt32 b;
    std::memcpy(&b, &x, sizeof b);
    return b;
}
inline RwReal Real(RwUInt32 b) {
    RwReal x;
    std::memcpy(&x, &b, sizeof x);
    return x;
}

// ---- VMX single-precision ops (vmaddfp / vaddfp), non-Java mode ------------------------------
namespace vmx {
inline float Ftz(float x) {
    const RwUInt32 b = Bits(x);
    return (b & 0x7f800000u) == 0 ? Real(b & 0x80000000u) : x;
}
// vmaddfp vD, vA, vC, vB: vA * vC + vB, one rounding. (ppc::detail::FusedMulAdd: std::fmaf's bits, the FMA3 instruction
// when the CPU has it.)
inline float Maddfp(float a, float c, float b) { return Ftz(ppc::detail::FusedMulAdd(Ftz(a), Ftz(c), Ftz(b))); }
inline float Addfp(float a, float b) { return Ftz(Ftz(a) + Ftz(b)); }

#if DOTD_PPC_HW_FMA
// PERF: the same two operations on the four lanes of a row at once (what the PS3's vmaddfp / vaddfp are). Each lane is
// Maddfp / Addfp above: the inputs' and the result's denormals flushed, one rounding of a * c + b by VFMADD (IEEE
// fusedMultiplyAdd, as std::fmaf). Only a NaN result's payload can differ from the library's, so RwMatrixMultiply
// computes a product with a NaN lane again with the scalar code.
inline __m128 Ftz4(__m128 x) {
    const __m128i bits = _mm_castps_si128(x);
    const __m128i tiny = _mm_cmpeq_epi32(_mm_and_si128(bits, _mm_set1_epi32(0x7f800000)), _mm_setzero_si128());
    // an exponent field of 0: only the sign stays
    return _mm_castsi128_ps(_mm_andnot_si128(_mm_and_si128(tiny, _mm_set1_epi32(0x7fffffff)), bits));
}
inline __m128 Maddfp4(__m128 a, __m128 c, __m128 b) { return Ftz4(_mm_fmadd_ps(Ftz4(a), Ftz4(c), Ftz4(b))); }
inline __m128 Addfp4(__m128 a, __m128 b) { return Ftz4(_mm_add_ps(Ftz4(a), Ftz4(b))); }
#endif
}  // namespace vmx

// ---- the matrix module globals (RWEngineInstance + [0xcf01bc]) --------------------------------
struct MatrixGlobals {
    RwFreeList* freeList = nullptr;                 // +0x00 (64-byte, 16-aligned entries)
    RwInt32 optimizations = rwMATRIXINTERNALIDENTITY;  // +0x04 rwMATRIXOPTIMIZE_IDENTITY (0x20000)
    // +0x08 the multiply callback (_rwMatrixMultiplyDefault 0x7580b8): only the RwFrame code calls it.
    RwMatrixTolerance tolerance = {0x1.47ae14p-7f, 0x1.47ae14p-7f, 0x1.47ae14p-7f};  // +0x0c 0.01f (0xa72778)
};
MatrixGlobals g_matrix;

RwFreeList* MatrixFreeList() {
    // _rwMatrixOpen 0x759c68: RwFreeListCreateAndPreallocateSpace(0x40, ..., 0x10, ...).
    if (g_matrix.freeList == nullptr) {
        g_matrix.freeList = RwFreeListCreateAndPreallocateSpace(sizeof(RwMatrix), 0x100, 0x10, 1, nullptr, 0x3000d);
    }
    return g_matrix.freeList;
}

// ---- the vector module globals (RWEngineInstance + [0xcf02a0]): the sqrt tables ----------------
struct SqrtTables {
    RwUInt32 sqrtTab[4096];     // +0x00
    RwUInt32 invSqrtTab[4096];  // +0x04
};

// 0x0075eb48 _rwV3dOpen_maybe (the table part). Entry i covers the mantissa's top 11 bits (rounded)
// and the exponent's low bit: [0x800, 0x1000) are built from [1, 2), [0, 0x800) from [2, 4), stepping
// the float's bits by 0x1000. The table holds the root's bits minus the exponent bias part that the
// lookup adds back.
const SqrtTables& Tables() {
    static const SqrtTables* tables = [] {
        SqrtTables* t = new SqrtTables;
        // sqrt: fsqrts (single, correctly rounded)
        RwUInt32 bits = 0x3f800000u;  // TOC 0xc22770: 1.0f
        for (int i = 0x800; i < 0x1000; ++i) {
            t->sqrtTab[i] = Bits(std::sqrt(Real(bits))) - 0x1fc00000u;
            bits += 0x1000u;
        }
        for (int i = 0; i < 0x800; ++i) {
            t->sqrtTab[i] = Bits(std::sqrt(Real(bits))) - 0x20000000u;
            bits += 0x1000u;
        }
        // inverse sqrt: fsqrt (double), fdiv 1.0 / root (double), frsp
        bits = 0x3f800000u;
        for (int i = 0x800; i < 0x1000; ++i) {
            t->invSqrtTab[i] = Bits(ppc::frsp(1.0 / std::sqrt(static_cast<double>(Real(bits))))) - 0x20000000u;
            bits += 0x1000u;
        }
        for (int i = 0; i < 0x800; ++i) {
            t->invSqrtTab[i] = Bits(ppc::frsp(1.0 / std::sqrt(static_cast<double>(Real(bits))))) - 0x1fc00000u;
            bits += 0x1000u;
        }
        return t;
    }();
    return *tables;
}

// The table lookup that RW_Sqrt / RW_InvSqrt (and their inlined copies) do.
inline RwReal TableSqrt(RwReal x) {
    RwUInt32 w = Bits(x);
    if (w == 0) return Real(0);
    w += 0x800u;
    return Real(Tables().sqrtTab[(w >> 12) & 0xfffu] + ((w >> 1) & 0x3fc00000u));
}
inline RwReal TableInvSqrt(RwReal x) {
    RwUInt32 w = Bits(x);
    if (w == 0) return Real(0);
    w += 0x800u;
    return Real(Tables().invSqrtTab[(w >> 12) & 0xfffu] + ((~w >> 1) & 0x3fc00000u));
}

// The row-vector maths the module repeats inline.
inline RwReal LengthSq3(RwReal x, RwReal y, RwReal z) {
    return ppc::fmadds(z, z, ppc::fmadds(x, x, y * y));
}

}  // namespace

// 0x0075e738 RW_Sqrt
RwReal rwSqrt(RwReal x) { return TableSqrt(x); }

// 0x0075e790 RW_InvSqrt
RwReal rwInvSqrt(RwReal x) { return TableInvSqrt(x); }

// RwMatrixSetIdentityMacro (inlined in RwMatrixTranslate/Scale's rwCOMBINEREPLACE, 0x759218).
RwMatrix* RwMatrixSetIdentity(RwMatrix* m) {
    m->flags |= rwMATRIXINTERNALIDENTITY | rwMATRIXTYPEORTHONORMAL;
    m->right.x = 1.0f;
    m->right.y = 0.0f;
    m->right.z = 0.0f;
    m->up.x = 0.0f;
    m->up.y = 1.0f;
    m->up.z = 0.0f;
    m->at.x = 0.0f;
    m->at.y = 0.0f;
    m->at.z = 1.0f;
    m->pos.x = 0.0f;
    m->pos.y = 0.0f;
    m->pos.z = 0.0f;
    return m;
}

// 0x007588f0 RwMatrixCreate
RwMatrix* RwMatrixCreate() {
    RwMatrix* m = static_cast<RwMatrix*>(RwFreeListAlloc(MatrixFreeList(), 0x3000d));
    if (m == nullptr) return nullptr;
    m->flags = rwMATRIXINTERNALIDENTITY | rwMATRIXTYPEORTHONORMAL;
    m->right.x = 1.0f;
    m->right.y = 0.0f;
    m->right.z = 0.0f;
    m->up.x = 0.0f;
    m->up.y = 1.0f;
    m->up.z = 0.0f;
    m->at.x = 0.0f;
    m->at.y = 0.0f;
    m->at.z = 1.0f;
    m->pos.x = 0.0f;
    m->pos.y = 0.0f;
    m->pos.z = 0.0f;
    // The PS3 leaves the pads as the free-list block held them; zeroed here so that the w lanes
    // RwMatrixMultiply carries into its output pads are deterministic.
    m->pad1 = m->pad2 = m->pad3 = 0;
    return m;
}

// 0x00758890 RwMatrixDestroy
RwBool RwMatrixDestroy(RwMatrix* m) {
    RwFreeListFree(MatrixFreeList(), m);
    return 1;
}

// 0x007586b8 RwMatrixUpdate
RwMatrix* RwMatrixUpdate(RwMatrix* m) {
    m->flags &= 0xfffdfffcu;  // ~(rwMATRIXINTERNALIDENTITY | rwMATRIXTYPEMASK)
    return m;
}

// 0x00759648 RwMatrixMultiply_maybe (VMX). Each output row i is
//   splat(a_i.x) * b.right + 0, then + splat(a_i.y) * b.up, then + splat(a_i.z) * b.at (vmaddfp),
// and the pos row adds b.pos (vaddfp). All four lanes are stored, so the output's flags/pad words get
// the w-lane results; the flags are then overwritten with a.flags & b.flags (read after the stores).
RwMatrix* RwMatrixMultiply(RwMatrix* out, const RwMatrix* a, const RwMatrix* b) {
#if DOTD_PPC_HW_FMA
    // PERF: the four lanes of each row in one register (vmx::Maddfp4 / Addfp4: the lanes' operations and their order are
    // those of the scalar code below, so the bits are the same); a product with a NaN in it is left to the scalar code.
    if (ppc::detail::g_hardwareFma) {
        static_assert(sizeof(RwMatrix) == 64 && offsetof(RwMatrix, right) == 0 && offsetof(RwMatrix, flags) == 12 &&
                          offsetof(RwMatrix, up) == 16 && offsetof(RwMatrix, pad1) == 28 && offsetof(RwMatrix, at) == 32 &&
                          offsetof(RwMatrix, pad2) == 44 && offsetof(RwMatrix, pos) == 48 && offsetof(RwMatrix, pad3) == 60,
                      "RwMatrix: four rows of x, y, z and a flags / pad word");
        const float* af = &a->right.x;
        const float* bf = &b->right.x;
        // b's rows with their fourth words as floats (the flags and pads), a's elements splatted.
        const __m128 b0 = _mm_loadu_ps(bf), b1 = _mm_loadu_ps(bf + 4), b2 = _mm_loadu_ps(bf + 8), b3 = _mm_loadu_ps(bf + 12);
        __m128 rows[4];
        for (int i = 0; i < 4; ++i) {
            __m128 r = vmx::Maddfp4(_mm_set1_ps(af[i * 4 + 0]), b0, _mm_setzero_ps());
            r = vmx::Maddfp4(b1, _mm_set1_ps(af[i * 4 + 1]), r);
            r = vmx::Maddfp4(b2, _mm_set1_ps(af[i * 4 + 2]), r);
            if (i == 3) r = vmx::Addfp4(r, b3);
            rows[i] = r;
        }
        const __m128 nan = _mm_or_ps(_mm_or_ps(_mm_cmpunord_ps(rows[0], rows[0]), _mm_cmpunord_ps(rows[1], rows[1])),
                                     _mm_or_ps(_mm_cmpunord_ps(rows[2], rows[2]), _mm_cmpunord_ps(rows[3], rows[3])));
        if (_mm_movemask_ps(nan) == 0) {
            float* of = &out->right.x;
            _mm_storeu_ps(of, rows[0]);
            _mm_storeu_ps(of + 4, rows[1]);
            _mm_storeu_ps(of + 8, rows[2]);
            _mm_storeu_ps(of + 12, rows[3]);
            out->flags = a->flags & b->flags;  // read after the stores, as the scalar code below
            return out;
        }
    }
#endif
    float A[4][3];
    float B[4][4];
    const RwV3d* arows[4] = {&a->right, &a->up, &a->at, &a->pos};
    const RwV3d* brows[4] = {&b->right, &b->up, &b->at, &b->pos};
    const RwUInt32 bw[4] = {b->flags, b->pad1, b->pad2, b->pad3};
    for (int i = 0; i < 4; ++i) {
        A[i][0] = arows[i]->x;
        A[i][1] = arows[i]->y;
        A[i][2] = arows[i]->z;
        B[i][0] = brows[i]->x;
        B[i][1] = brows[i]->y;
        B[i][2] = brows[i]->z;
        B[i][3] = Real(bw[i]);
    }
    float R[4][4];
    for (int i = 0; i < 4; ++i) {
        for (int k = 0; k < 4; ++k) {
            float r = vmx::Maddfp(A[i][0], B[0][k], 0.0f);
            r = vmx::Maddfp(B[1][k], A[i][1], r);
            r = vmx::Maddfp(B[2][k], A[i][2], r);
            if (i == 3) r = vmx::Addfp(r, B[3][k]);
            R[i][k] = r;
        }
    }
    RwV3d* orows[4] = {&out->right, &out->up, &out->at, &out->pos};
    RwUInt32* ow[4] = {&out->flags, &out->pad1, &out->pad2, &out->pad3};
    for (int i = 0; i < 4; ++i) {
        orows[i]->x = R[i][0];
        orows[i]->y = R[i][1];
        orows[i]->z = R[i][2];
        *ow[i] = Bits(R[i][3]);
    }
    out->flags = a->flags & b->flags;
    return out;
}

// 0x00759190 RwMatrixTranslate
RwMatrix* RwMatrixTranslate(RwMatrix* m, const RwV3d* t, RwOpCombineType op) {
    if (op == rwCOMBINEPRECONCAT) {
        const RwReal tx = t->x, ty = t->y, tz = t->z;
        const RwReal rx = m->right.x, ry = m->right.y, rz = m->right.z;
        const RwReal ux = m->up.x, uy = m->up.y, uz = m->up.z;
        const RwReal ax = m->at.x, ay = m->at.y, az = m->at.z;
        const RwReal px = m->pos.x, py = m->pos.y, pz = m->pos.z;
        const RwUInt32 flags = m->flags & ~rwMATRIXINTERNALIDENTITY;
        m->pos.x = px + ppc::fmadds(tz, ax, ppc::fmadds(tx, rx, ty * ux));
        const RwReal tx2 = t->x;  // reloaded after the store (as the PS3 does)
        m->pos.y = py + ppc::fmadds(tz, ay, ppc::fmadds(tx2, ry, ty * uy));
        const RwReal ty2 = t->y;
        m->flags = flags;
        m->pos.z = pz + ppc::fmadds(tz, az, ppc::fmadds(tx2, rz, ty2 * uz));
        return m;
    }
    if (op == rwCOMBINEREPLACE) {
        RwMatrixSetIdentity(m);
        const RwUInt32 flags = m->flags & ~rwMATRIXINTERNALIDENTITY;
        m->pos.x = t->x;
        m->pos.y = t->y;
        m->pos.z = t->z;
        m->flags = flags;
        return m;
    }
    if (op == rwCOMBINEPOSTCONCAT) {
        const RwReal x = m->pos.x + t->x, y = m->pos.y + t->y, z = m->pos.z + t->z;
        m->flags &= ~rwMATRIXINTERNALIDENTITY;
        m->pos.x = x;
        m->pos.y = y;
        m->pos.z = z;
        return m;
    }
    // _rwerror(E_RW_BADPARAM 0x80000003) + RwErrorSet.
    // BUG(original): then clears the identity flag of a null matrix (lwz/stw at address 0xc).
    return nullptr;
}

// 0x00759398 RwMatrixScale
RwMatrix* RwMatrixScale(RwMatrix* m, const RwV3d* s, RwOpCombineType op) {
    if (op == rwCOMBINEPRECONCAT) {
        // The matrix is loaded first; the scale is re-read after some stores (as the PS3 does).
        const RwReal rx = m->right.x, ry = m->right.y, rz = m->right.z;
        const RwReal ux = m->up.x, uy = m->up.y, uz = m->up.z;
        const RwReal ax = m->at.x, ay = m->at.y, az = m->at.z;
        const RwUInt32 flags = m->flags & 0xfffdfffcu;
        m->right.x = rx * s->x;
        const RwReal sx = s->x;
        m->right.y = ry * sx;
        const RwReal sy = s->y;
        m->right.z = rz * sx;
        m->up.y = uy * sy;
        const RwReal sy2 = s->y;
        m->up.x = ux * sy;
        m->up.z = uz * sy2;
        const RwReal sz = s->z;
        m->flags = flags;
        m->at.z = az * sz;
        m->at.x = ax * sz;
        m->at.y = ay * sz;
        return m;
    }
    if (op == rwCOMBINEREPLACE) {
        RwMatrixSetIdentity(m);
        const RwUInt32 flags = m->flags & 0xfffdfffcu;
        m->right.x = s->x;
        m->up.y = s->y;
        m->at.z = s->z;
        m->flags = flags;
        return m;
    }
    if (op == rwCOMBINEPOSTCONCAT) {
        RwV3d* rows[4] = {&m->right, &m->up, &m->at, &m->pos};
        for (RwV3d* r : rows) {
            r->x = r->x * s->x;
            r->y = r->y * s->y;
            r->z = r->z * s->z;
        }
        m->flags &= 0xfffdfffcu;
        return m;
    }
    // _rwerror(E_RW_BADPARAM) + RwErrorSet. BUG(original): then clears the flags of a null matrix.
    return nullptr;
}

// 0x007597d8 RwMatrixTransform
RwMatrix* RwMatrixTransform(RwMatrix* m, const RwMatrix* t, RwOpCombineType op) {
    RwMatrix tmp;
    if (op == rwCOMBINEPRECONCAT) {
        RwMatrixMultiply(&tmp, t, m);
        *m = tmp;
        return m;
    }
    if (op == rwCOMBINEREPLACE) {
        *m = *t;
        return m;
    }
    if (op == rwCOMBINEPOSTCONCAT) {
        RwMatrixMultiply(&tmp, m, t);
        *m = tmp;
        return m;
    }
    return nullptr;  // _rwerror(E_RW_BADPARAM) + RwErrorSet
}

// 0x00759920 RwMatrixRotateOneMinusCosineSine
RwMatrix* RwMatrixRotateOneMinusCosineSine(RwMatrix* m, const RwV3d* unitAxis, RwReal omc, RwReal s,
                                           RwOpCombineType op) {
    const RwReal x = unitAxis->x, y = unitAxis->y, z = unitAxis->z;
    const RwReal xs = x * s, ys = y * s, zs = z * s;
    const RwReal omcYz = omc * (y * z), omcXz = omc * (x * z), omcXy = omc * (x * y);
    RwMatrix rot;
    rot.right.x = 1.0f - (1.0f - x * x) * omc;
    rot.right.y = omcXy + zs;
    rot.right.z = omcXz - ys;
    rot.flags = rwMATRIXTYPEORTHONORMAL;
    rot.up.x = omcXy - zs;
    rot.up.y = 1.0f - (1.0f - y * y) * omc;
    rot.up.z = omcYz + xs;
    rot.at.x = omcXz + ys;
    rot.at.y = omcYz - xs;
    rot.at.z = 1.0f - (1.0f - z * z) * omc;
    rot.pos.x = rot.pos.y = rot.pos.z = 0.0f;
    // BUG(original): the pads of the stack matrix are never written; rwCOMBINEREPLACE copies them into
    // the result and rwCOMBINEPOSTCONCAT feeds them to the multiply's w lanes. Zero here.
    rot.pad1 = rot.pad2 = rot.pad3 = 0;
    if (op == rwCOMBINEPRECONCAT) {
        RwMatrix tmp;
        RwMatrixMultiply(&tmp, &rot, m);
        *m = tmp;
        return m;
    }
    if (op == rwCOMBINEREPLACE) {
        *m = rot;
        return m;
    }
    if (op == rwCOMBINEPOSTCONCAT) {
        RwMatrix tmp;
        RwMatrixMultiply(&tmp, m, &rot);
        *m = tmp;
        return m;
    }
    return nullptr;  // _rwerror(E_RW_BADPARAM) + RwErrorSet
}

// 0x00759af0 RwMatrixRotate
RwMatrix* RwMatrixRotate(RwMatrix* m, const RwV3d* axis, RwReal angle, RwOpCombineType op) {
    const RwReal inv = rwInvSqrt(LengthSq3(axis->x, axis->y, axis->z));
    const RwReal radians = angle * 0x1.1df46ap-6f;  // TOC 0xc226f4: 0.0174532924f (pi/180)
    RwV3d unit;
    unit.z = inv * axis->z;
    unit.y = inv * axis->y;
    unit.x = inv * axis->x;
    const double sine = crt::Sin(static_cast<double>(radians), 0);
    const double cosine = crt::Sin(static_cast<double>(radians), 1);
    const RwReal s = ppc::frsp(sine);
    const RwReal c = ppc::frsp(cosine);
    RwMatrixRotateOneMinusCosineSine(m, &unit, 1.0f - c, s, op);
    return m;
}

// 0x00758268 _rwMatrixInvertGeneric_maybe: the cofactor inverse; flags 0. A determinant of +0.0 (the
// bit pattern 0) uses 1.0 as its reciprocal.
static RwMatrix* _rwMatrixInvertGeneric(RwMatrix* out, const RwMatrix* in) {
    const RwReal rz = in->right.z, ay = in->at.y, uz = in->up.z, az = in->at.z, uy = in->up.y, ux = in->up.x,
                 ax = in->at.x;
    const RwReal c01 = ppc::fnmsubs(in->right.y, az, rz * ay);  // -(r.y*a.z - r.z*a.y)
    const RwReal c00 = ppc::fmsubs(uy, az, uz * ay);            // u.y*a.z - u.z*a.y
    out->right.y = c01;
    const RwReal ry = in->right.y;
    out->right.x = c00;
    const RwReal c02 = ppc::fmsubs(ry, uz, rz * uy);            // r.y*u.z - r.z*u.y
    const RwReal det0 = ppc::fmadds(c00, in->right.x, c01 * ux);
    out->right.z = c02;
    const RwReal det = ppc::fmadds(c02, ax, det0);
    const RwReal inv = Bits(det) == 0 ? 1.0f : 1.0f / det;  // fdivs
    const RwReal o02 = inv * out->right.z;
    const RwReal py = in->pos.y;
    const RwReal o00 = inv * c00;
    const RwReal o01 = inv * out->right.y;
    const RwReal px = in->pos.x;
    const RwReal pz = in->pos.z;
    out->flags = 0;
    const RwReal c10 = ppc::fnmsubs(ux, az, uz * ax);            // -(u.x*a.z - u.z*a.x)
    out->right.z = o02;
    const RwReal rz2 = in->right.z;
    out->right.x = o00;
    const RwReal rx = in->right.x;
    out->right.y = o01;
    const RwReal ry2 = in->right.y;
    const RwReal o10 = inv * c10;
    const RwReal c11 = ppc::fmsubs(rx, az, rz2 * ax);            // r.x*a.z - r.z*a.x
    out->up.x = o10;
    const RwReal pyo10 = py * o10;
    const RwReal ux2 = in->up.x;
    const RwReal ryux = ry2 * ux2;
    const RwReal o11 = inv * c11;
    const RwReal rzux = rz2 * ux2;
    const RwReal pos0 = ppc::fmadds(px, o00, pyo10);
    out->up.y = o11;
    const RwReal pyo11 = py * o11;
    const RwReal uy2 = in->up.y;
    const RwReal c12 = ppc::fnmsubs(rx, uz, rzux);               // -(r.x*u.z - r.z*u.x)
    const RwReal uyax = uy2 * ax;
    const RwReal c22 = ppc::fmsubs(rx, uy2, ryux);               // r.x*u.y - r.y*u.x
    const RwReal o12 = inv * c12;
    const RwReal c20 = ppc::fmsubs(ux2, ay, uyax);               // u.x*a.y - u.y*a.x
    const RwReal o22 = inv * c22;
    out->up.z = o12;
    const RwReal o20 = inv * c20;
    out->at.z = o22;
    out->at.x = o20;
    out->pos.x = ppc::fnmadds(pz, o20, pos0);
    const RwReal ax2 = in->at.x;
    const RwReal ryax = ry2 * ax2;
    const RwReal px2 = in->pos.x;
    const RwReal c21 = ppc::fnmsubs(rx, ay, ryax);               // -(r.x*a.y - r.y*a.x)
    const RwReal pos1 = ppc::fmadds(px2, o01, pyo11);
    const RwReal o21 = inv * c21;
    out->at.y = o21;
    out->pos.y = ppc::fnmadds(pz, o21, pos1);
    const RwReal py2 = in->pos.y;
    out->pos.z = ppc::fnmadds(pz, o22, ppc::fmadds(px2, o02, py2 * o12));
    return out;
}

// 0x007586d8 RwMatrixInvert_maybe
RwMatrix* RwMatrixInvert(RwMatrix* out, const RwMatrix* in) {
    const RwUInt32 type = in->flags & rwMATRIXTYPEMASK;
    if ((in->flags & static_cast<RwUInt32>(g_matrix.optimizations) & rwMATRIXINTERNALIDENTITY) != 0) {
        *out = *in;  // lvx/stvx: all 64 bytes
        return out;
    }
    if (type != rwMATRIXTYPEORTHONORMAL) return _rwMatrixInvertGeneric(out, in);
    // Orthonormal: the transpose, and pos = -(pos . axis) for each axis. The store/load order is the
    // PS3's (it matters only when out aliases in).
    out->right.y = in->up.x;
    out->right.z = in->at.x;
    out->up.z = in->at.y;
    const RwReal rx = in->right.x, ry = in->right.y, rz = in->right.z;
    out->right.x = rx;
    out->up.x = ry;
    out->at.x = rz;
    const RwReal uy = in->up.y, uz = in->up.z;
    out->up.y = uy;
    out->at.y = uz;
    const RwReal px = in->pos.x, py = in->pos.y;
    const RwReal ry2 = in->right.y;
    const RwReal rx2 = in->right.x;
    out->at.z = in->at.z;
    const RwReal pz = in->pos.z;
    const RwReal rz2 = in->right.z;
    out->pos.x = ppc::fnmadds(pz, rz2, ppc::fmadds(px, rx2, py * ry2));
    const RwReal ux2 = in->up.x, uy2 = in->up.y;
    const RwReal pyuy = py * uy2;
    const RwReal px2 = in->pos.x;
    const RwReal uz2 = in->up.z;
    const RwReal t1 = ppc::fmadds(px2, ux2, pyuy);
    const RwReal ax = in->at.x, az = in->at.z;
    out->pos.y = ppc::fnmadds(pz, uz2, t1);
    const RwReal py2 = in->pos.y;
    const RwReal ay = in->at.y;
    out->flags = type;
    out->pos.z = ppc::fnmadds(pz, az, ppc::fmadds(px2, ax, py2 * ay));
    return out;
}

// 0x00758d48 RwMatrixOrthoNormalize
RwMatrix* RwMatrixOrthoNormalize(RwMatrix* out, const RwMatrix* in) {
    RwV3d r = in->right, u = in->up, a = in->at;
    const RwV3d pos = in->pos;
    const RwReal invR = rwInvSqrt(LengthSq3(r.x, r.y, r.z));
    r.x = r.x * invR;
    r.y = r.y * invR;
    r.z = r.z * invR;
    const RwReal invU = rwInvSqrt(LengthSq3(u.x, u.y, u.z));
    u.x = u.x * invU;
    u.y = u.y * invU;
    u.z = u.z * invU;
    const RwReal invA = rwInvSqrt(LengthSq3(a.x, a.y, a.z));
    a.x = a.x * invA;
    a.y = a.y * invA;
    a.z = invA * a.z;
    // Pick the two axes to keep (p0, p1) and the one to rebuild (p2 = p0 x p1, then p1 = p2 x p0).
    RwV3d* p0;
    RwV3d* p1;
    RwV3d* p2;
    // (ble / bge branch on unordered too: the comparisons are written so that NaN goes the same way.)
    if (!(invR > 0.0f)) {
        p0 = &u, p1 = &a, p2 = &r;
    } else if (!(invU > 0.0f)) {
        p0 = &a, p1 = &r, p2 = &u;
    } else if (!(invA > 0.0f)) {
        p0 = &r, p1 = &u, p2 = &a;
    } else {
        RwReal dUA = ppc::fmadds(a.z, u.z, ppc::fmadds(u.x, a.x, u.y * a.y));
        if (!(dUA >= 0.0f)) dUA = -dUA;
        RwReal dRA = ppc::fmadds(a.z, r.z, ppc::fmadds(a.x, r.x, a.y * r.y));
        if (!(dRA >= 0.0f)) dRA = -dRA;
        RwReal dUR = ppc::fmadds(u.z, r.z, ppc::fmadds(u.x, r.x, u.y * r.y));
        if (!(dUR >= 0.0f)) dUR = -dUR;
        if (dUA < dRA) {
            if (dUA < dUR) {
                p0 = &u, p1 = &a, p2 = &r;
            } else {
                p0 = &r, p1 = &u, p2 = &a;
            }
        } else if (!(dRA < dUR)) {
            p0 = &r, p1 = &u, p2 = &a;
        } else {
            p0 = &a, p1 = &r, p2 = &u;
        }
    }
    {
        const RwReal cx = ppc::fmsubs(p0->y, p1->z, p0->z * p1->y);
        p2->x = cx;
        const RwReal cy = ppc::fmsubs(p0->z, p1->x, p0->x * p1->z);
        p2->y = cy;
        const RwReal cz = ppc::fmsubs(p0->x, p1->y, p0->y * p1->x);
        p2->z = cz;
        const RwReal inv = rwInvSqrt(ppc::fmadds(cz, cz, ppc::fmadds(cx, cx, cy * cy)));
        p2->y = inv * p2->y;
        p2->z = inv * p2->z;
        p2->x = inv * p2->x;
    }
    {
        const RwReal cx = ppc::fmsubs(p2->y, p0->z, p2->z * p0->y);
        p1->x = cx;
        const RwReal cy = ppc::fmsubs(p2->z, p0->x, p2->x * p0->z);
        p1->y = cy;
        const RwReal cz = ppc::fmsubs(p2->x, p0->y, p2->y * p0->x);
        p1->z = cz;
        const RwReal inv = rwInvSqrt(ppc::fmadds(cz, cz, ppc::fmadds(cx, cx, cy * cy)));
        p1->x = inv * p1->x;
        p1->z = inv * p1->z;
        p1->y = inv * p1->y;
    }
    // The flags come from the destination: (out.flags | 3) & ~identity.
    out->flags = (out->flags | rwMATRIXTYPEORTHONORMAL) & ~rwMATRIXINTERNALIDENTITY;
    out->right = r;
    out->up = u;
    out->at = a;
    out->pos = pos;
    return out;
}

// 0x00759d90 RwMatrixOptimize
RwMatrix* RwMatrixOptimize(RwMatrix* m, const RwMatrixTolerance* tolerance) {
    if (tolerance == nullptr) tolerance = &g_matrix.tolerance;
    const RwReal ax = m->at.x, ay = m->at.y, az = m->at.z;
    const RwReal rx = m->right.x, ry = m->right.y, rz = m->right.z;
    const RwReal ux = m->up.x, uy = m->up.y, uz = m->up.z;
    const RwReal uxux = ux * ux, ryry = ry * ry, uzuz = uz * uz, rzrz = rz * rz;
    const RwReal atLen0 = ppc::fmadds(ax, ax, ay * ay);
    const RwReal dotAR = ppc::fmadds(az, rz, ppc::fmadds(ax, rx, ay * ry));
    const RwReal dotUA = ppc::fmadds(uz, az, ppc::fmadds(ux, ax, uy * ay));
    const RwReal dotUR = ppc::fmadds(uz, rz, ppc::fmadds(ux, rx, uy * ry));
    const RwReal atErr = ppc::fmadds(az, az, atLen0) - 1.0f;
    const RwReal rErr = (ppc::fmadds(rx, rx, ryry) + rzrz) - 1.0f;
    const RwReal uErr = (ppc::fmadds(uy, uy, uxux) + uzuz) - 1.0f;
    const RwReal orthoErr = ppc::fmadds(dotUR, dotUR, ppc::fmadds(dotUA, dotUA, dotAR * dotAR));
    const bool orthogonal = tolerance->Orthogonal >= orthoErr;
    const RwReal normalErr = ppc::fmadds(atErr, atErr, ppc::fmadds(rErr, rErr, uErr * uErr));
    const bool normal = tolerance->Normal >= normalErr;
    bool identity = false;
    RwUInt32 flags;
    if (!normal) {
        flags = m->flags & ~rwMATRIXTYPENORMAL;
    } else {
        if (orthogonal) {
            const RwReal px = m->pos.x, py = m->pos.y, pz = m->pos.z;
            RwReal e = ppc::fmadds(rx - 1.0f, rx - 1.0f, ryry) + rzrz;
            const RwReal eu = ppc::fmadds(uy - 1.0f, uy - 1.0f, uxux) + uzuz;
            const RwReal ea = ppc::fmadds(az - 1.0f, az - 1.0f, atLen0);
            const RwReal ep = ppc::fmadds(pz, pz, ppc::fmadds(px, px, py * py));
            e = e + eu;
            e = ea + e;
            e = ep + e;
            identity = tolerance->Identity >= e;
        }
        flags = m->flags | rwMATRIXTYPENORMAL;
    }
    if (orthogonal) {
        flags |= 2u;
    } else {
        flags &= ~2u;
    }
    flags = identity ? (flags | rwMATRIXINTERNALIDENTITY) : (flags & ~rwMATRIXINTERNALIDENTITY);
    m->flags = flags;
    return m;
}

// 0x00758470 _rwMatrixDeterminant
RwReal _rwMatrixDeterminant(const RwMatrix* m) {
    const RwReal ux = m->up.x, uy = m->up.y, uz = m->up.z;
    const RwReal ax = m->at.x, ay = m->at.y, az = m->at.z;
    const RwReal c1 = ppc::fmsubs(uz, ax, az * ux);   // u.z*a.x - a.z*u.x
    const RwReal c0 = ppc::fmsubs(uy, az, uz * ay);   // u.y*a.z - u.z*a.y
    const RwReal c2 = ppc::fmsubs(ay, ux, uy * ax);   // a.y*u.x - u.y*a.x
    return ppc::fmadds(c2, m->right.z, ppc::fmadds(c0, m->right.x, c1 * m->right.y));
}

// 0x007584c8 _rwMatrixOrthogonalError
RwReal _rwMatrixOrthogonalError(const RwMatrix* m) {
    const RwReal rx = m->right.x, ry = m->right.y, rz = m->right.z;
    const RwReal ux = m->up.x, uy = m->up.y, uz = m->up.z;
    const RwReal ax = m->at.x, ay = m->at.y, az = m->at.z;
    const RwReal dAR = ppc::fmadds(az, rz, ppc::fmadds(ax, rx, ay * ry));
    const RwReal dUA = ppc::fmadds(uz, az, ppc::fmadds(ux, ax, uy * ay));
    const RwReal dUR = ppc::fmadds(uz, rz, ppc::fmadds(ux, rx, uy * ry));
    return ppc::fmadds(dUR, dUR, ppc::fmadds(dUA, dUA, dAR * dAR));
}

// 0x00758528 _rwMatrixNormalError_maybe
RwReal _rwMatrixNormalError(const RwMatrix* m) {
    const RwReal r = LengthSq3(m->right.x, m->right.y, m->right.z) - 1.0f;
    const RwReal u = LengthSq3(m->up.x, m->up.y, m->up.z) - 1.0f;
    const RwReal a = LengthSq3(m->at.x, m->at.y, m->at.z) - 1.0f;
    return ppc::fmadds(a, a, ppc::fmadds(r, r, u * u));
}

// 0x00758598 _rwMatrixIdentityError_maybe
RwReal _rwMatrixIdentityError(const RwMatrix* m) {
    const RwReal rx = m->right.x - 1.0f, uy = m->up.y - 1.0f, az = m->at.z - 1.0f;
    const RwReal r = ppc::fmadds(m->right.z, m->right.z, ppc::fmadds(rx, rx, m->right.y * m->right.y));
    const RwReal u = ppc::fmadds(m->up.z, m->up.z, ppc::fmadds(m->up.x, m->up.x, uy * uy));
    const RwReal a = ppc::fmadds(az, az, ppc::fmadds(m->at.x, m->at.x, m->at.y * m->at.y));
    const RwReal p = ppc::fmadds(m->pos.z, m->pos.z, ppc::fmadds(m->pos.x, m->pos.x, m->pos.y * m->pos.y));
    return p + (a + (r + u));
}

// 0x00758638 _rwMatrixGetOptimizeTolerances
RwBool _rwMatrixGetOptimizeTolerances(RwMatrixTolerance* tolerance) {
    *tolerance = g_matrix.tolerance;
    return 1;
}

// 0x00758678 _rwMatrixSetOptimizeTolerances
RwBool _rwMatrixSetOptimizeTolerances(const RwMatrixTolerance* tolerance) {
    g_matrix.tolerance = *tolerance;
    return 1;
}

// 0x00758448 RwMatrix_SetOptimizations_maybe
RwBool RwMatrixOptimizations(RwInt32 optimizeFlags) {
    g_matrix.optimizations = optimizeFlags;
    return 1;
}

// 0x007572e0 RwMatrixStreamRead
RwMatrix* RwMatrixStreamRead(RwStream* stream, RwMatrix* matrix) {
    uint32_t length = 0, version = 0;
    if (RwStreamFindChunk(stream, 1, &length, &version) == 0) return nullptr;  // E_RW_READ (0x8000001a)
    if (version - 0x35000u > 0x2002u) return nullptr;                       // E_RW_BADVERSION (0x80000004)
    // rwStreamMatrix: right, up, at, pos (12 RwReal), then the type word; zeroed, then `length` bytes.
    // BUG(original): the buffer is 0x34 bytes on the stack and `length` is not checked; a longer chunk
    // overruns it. Here the extra bytes are read (the stream position is the same) and ignored.
    std::vector<uint8_t> bytes(length > 0x34u ? length : 0x34u, 0);
    if (RwStreamRead(stream, bytes.data(), length) != length) return nullptr;  // E_RW_READ
    uint32_t w[13];
    std::memcpy(w, bytes.data(), sizeof w);  // RwMemNative32 / RwMemFloat32ToReal: already native here
    if (matrix == nullptr) {
        matrix = RwMatrixCreate();
        if (matrix == nullptr) return nullptr;
    }
    const RwUInt32 type = w[12] & rwMATRIXTYPEMASK;
    matrix->flags = 0;
    matrix->right.x = Real(w[0]);
    matrix->right.y = Real(w[1]);
    matrix->right.z = Real(w[2]);
    matrix->up.x = Real(w[3]);
    matrix->up.y = Real(w[4]);
    matrix->up.z = Real(w[5]);
    matrix->at.x = Real(w[6]);
    matrix->at.y = Real(w[7]);
    matrix->at.z = Real(w[8]);
    matrix->pos.x = Real(w[9]);
    matrix->pos.y = Real(w[10]);
    matrix->pos.z = Real(w[11]);
    matrix->flags = type;
    if (type == rwMATRIXTYPEORTHONORMAL) RwMatrixOrthoNormalize(matrix, matrix);
    return matrix;
}

// ---- vector.c ---------------------------------------------------------------------------------

// 0x0075e4c8 _rwV3dTransformPointDefault_maybe (through the vector globals +0x08)
// 0x0075e7f0 RwV3dTransformPoint
RwV3d* RwV3dTransformPoint(RwV3d* o, const RwV3d* p, const RwMatrix* m) {
    const RwReal x = p->x, y = p->y, z = p->z;
    const RwReal rx = ppc::fmadds(z, m->at.x, ppc::fmadds(x, m->right.x, y * m->up.x)) + m->pos.x;
    const RwReal rz = ppc::fmadds(z, m->at.z, ppc::fmadds(x, m->right.z, y * m->up.z)) + m->pos.z;
    const RwReal ry = ppc::fmadds(z, m->at.y, ppc::fmadds(x, m->right.y, y * m->up.y)) + m->pos.y;
    o->x = rx;
    o->z = rz;
    o->y = ry;
    return o;
}

// 0x0075e418 _rwV3dTransformPointsDefault_maybe (vector globals +0x0c)
// 0x0075e850 RwV3dTransformPoints
RwV3d* RwV3dTransformPoints(RwV3d* o, const RwV3d* p, RwInt32 n, const RwMatrix* m) {
    for (RwInt32 i = 0; i < n; ++i) RwV3dTransformPoint(&o[i], &p[i], m);
    return o;
}

// 0x0075e5e0 _rwV3dTransformVectorDefault_maybe (vector globals +0x10)
// 0x0075e8b0 RwV3dTransformVector
RwV3d* RwV3dTransformVector(RwV3d* o, const RwV3d* p, const RwMatrix* m) {
    const RwReal x = p->x, y = p->y, z = p->z;
    const RwReal ry = ppc::fmadds(z, m->at.y, ppc::fmadds(x, m->right.y, y * m->up.y));
    const RwReal rx = ppc::fmadds(z, m->at.x, ppc::fmadds(x, m->right.x, y * m->up.x));
    const RwReal rz = ppc::fmadds(z, m->at.z, ppc::fmadds(x, m->right.z, y * m->up.z));
    o->y = ry;
    o->x = rx;
    o->z = rz;
    return o;
}

// 0x0075e548 _rwV3dTransformVectorsDefault_maybe (vector globals +0x14)
// 0x0075e910 RwV3dTransformVectors
RwV3d* RwV3dTransformVectors(RwV3d* o, const RwV3d* p, RwInt32 n, const RwMatrix* m) {
    for (RwInt32 i = 0; i < n; ++i) RwV3dTransformVector(&o[i], &p[i], m);
    return o;
}

// 0x0075ead8 RwV3dLength_maybe
RwReal RwV3dLength(const RwV3d* v) { return TableSqrt(LengthSq3(v->x, v->y, v->z)); }

// 0x0075ea70 RwV2dLength_maybe
RwReal RwV2dLength(const RwV2d* v) { return TableSqrt(ppc::fmadds(v->x, v->x, v->y * v->y)); }

// 0x0075f018 RwV3dNormalize
RwReal RwV3dNormalize(RwV3d* o, const RwV3d* v) {
    const RwReal x = v->x, y = v->y, z = v->z;
    const RwReal lengthSq = LengthSq3(x, y, z);
    const RwReal length = TableSqrt(lengthSq);
    const RwReal inv = TableInvSqrt(lengthSq);
    o->z = inv * z;
    o->x = x * inv;
    o->y = inv * y;
    // length <= 0: _rwerror(E_RW_ZEROLENGTH 0x19) + RwErrorSet; the (zero) result is kept.
    return length;
}

// 0x0075ee40 _rwV3dNormalize_maybe
RwReal _rwV3dNormalize(RwV3d* o, const RwV3d* v) {
    const RwReal x = v->x, y = v->y, z = v->z;
    const RwReal inv = TableInvSqrt(LengthSq3(x, y, z));
    o->x = x * inv;
    o->z = inv * z;
    o->y = inv * y;
    return inv;
}

// 0x0075eed0 RwV2dNormalize_maybe
RwReal RwV2dNormalize(RwV2d* o, const RwV2d* v) {
    const RwReal x = v->x, y = v->y;
    const RwReal lengthSq = ppc::fmadds(x, x, y * y);
    const RwReal length = TableSqrt(lengthSq);
    const RwReal inv = TableInvSqrt(lengthSq);
    o->y = inv * y;
    o->x = x * inv;
    // length <= 0: _rwerror(E_RW_ZEROLENGTH 0x19) + RwErrorSet.
    return length;
}
