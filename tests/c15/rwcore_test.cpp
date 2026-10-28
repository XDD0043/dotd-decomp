// rwcore_test - C1.5 family A: the RW core maths and the immediate-mode path, bit for bit.
//
// Expected values: the sqrt tables were compared word for word with the live tables in RPCS3 (vector
// globals +0 / +4, 2026-10-17) and their FNV-1a hashes are below; the other values come from an exact
// rational model of the PS3 instruction sequences (fused ops rounded once, float vs double as in the
// assembly), or are derived by hand where noted.
#include <cmath>
#include <cstdint>
#include <cstdio>
#include <cstring>
#include <vector>

#include "Renderware/rwcore/RwIm3D.h"
#include "Renderware/rwcore/RwMatrix.h"
#include "boot_helper.h"
#include "crt/xsin.h"

namespace {

uint32_t Bits(float x) {
    uint32_t b;
    std::memcpy(&b, &x, sizeof b);
    return b;
}
float Real(uint32_t b) {
    float x;
    std::memcpy(&x, &b, sizeof x);
    return x;
}
uint64_t Bits64(double x) {
    uint64_t b;
    std::memcpy(&b, &x, sizeof b);
    return b;
}

#define CHECK_BITS(value, expected)                                                                    \
    do {                                                                                               \
        const uint32_t got_ = Bits(value);                                                             \
        if (got_ != (expected)) {                                                                      \
            std::printf("FAIL %s:%d: %s = %08x, expected %08x\n", __FILE__, __LINE__, #value, got_,   \
                        static_cast<uint32_t>(expected));                                              \
            ++c15::g_failures;                                                                         \
        }                                                                                              \
    } while (0)

uint32_t Fnv(const std::vector<uint32_t>& words) {
    uint32_t h = 0x811c9dc5u;
    for (uint32_t w : words) {
        for (int k = 0; k < 4; ++k) {
            h ^= (w >> (8 * k)) & 0xffu;
            h *= 0x01000193u;
        }
    }
    return h;
}

// Recovers table entry i through the public lookup: an input whose index is i, minus the exponent part
// the lookup adds.
std::vector<uint32_t> RecoverTable(bool inverse) {
    std::vector<uint32_t> t(4096);
    for (uint32_t i = 0; i < 4096; ++i) {
        const uint32_t x = i >= 0x800 ? 0x3f800000u + ((i - 0x800u) << 12) : 0x40000000u + (i << 12);
        const uint32_t w = x + 0x800u;
        const uint32_t e = ((inverse ? ~w : w) >> 1) & 0x3fc00000u;
        t[i] = Bits(inverse ? rwInvSqrt(Real(x)) : rwSqrt(Real(x))) - e;
    }
    return t;
}

RwMatrix MakeMatrix(RwV3d r, RwV3d u, RwV3d a, RwV3d p, uint32_t flags) {
    RwMatrix m;
    m.right = r;
    m.up = u;
    m.at = a;
    m.pos = p;
    m.flags = flags;
    m.pad1 = m.pad2 = m.pad3 = 0;
    return m;
}

void TestSqrt() {
    C15_CHECK(Fnv(RecoverTable(false)) == 0x851dfe2cu);
    C15_CHECK(Fnv(RecoverTable(true)) == 0xb05db5f4u);
    struct Case {
        uint32_t in, sqrt, inv;
    } cases[] = {
        {0x3f800000u, 0x3f800000u, 0x3f800000u},  // 1
        {0x40000000u, 0x3fb504f3u, 0x3f3504f3u},  // 2
        {0x40400000u, 0x3fddb3d7u, 0x3f13cd3au},  // 3
        {0x41200000u, 0x404a62c2u, 0x3ea1e89bu},  // 10
        {0x42c80000u, 0x41200000u, 0x3dcccccdu},  // 100
        {0x3a83126fu, 0x3d0185afu, 0x41fcfdcbu},  // 0.001f
        {0xbf800000u, 0x3f800000u, 0x3f800000u},  // -1: the sign bit is ignored
        {0x80000000u, 0x1fb504f3u, 0x5f3504f3u},  // -0.0 goes through the table
        {0x00000000u, 0x00000000u, 0x00000000u},  // +0.0
    };
    for (const Case& c : cases) {
        CHECK_BITS(rwSqrt(Real(c.in)), c.sqrt);
        CHECK_BITS(rwInvSqrt(Real(c.in)), c.inv);
    }
}

void TestSin() {
    struct Case {
        uint32_t radians;
        uint64_t sine, cosine;
    } cases[] = {
        {0x3fc90fdbu, 0x3feffffffffffff7ull, 0xbe6777a5cf72ceccull},  // 90 deg (as RwMatrixRotate computes it)
        {0x3f060a92u, 0x3fe0000006c6422dull, 0x3febb67ae46f065dull},  // 30
        {0x3f490fdbu, 0x3fe6a09e6ecb41feull, 0x3fe6a09e5e333599ull},  // 45
        {0xbf860a92u, 0xbfebb67af02ad942ull, 0x3fdfffffe4e6f747ull},  // -60
        {0x40490fdbu, 0xbe7777a5cf72cec6ull, 0xbfefffffffffffdeull},  // 180
        {0x3c8efa35u, 0x3f91df0b29375714ull, 0x3feffec097f6028full},  // 1
        {0x40c880e0u, 0xbf91df18ccdc45f8ull, 0x3feffec0960e6ea0ull},  // 359
        {0x41493399u, 0x3f81df2011c97138ull, 0x3fefffb0266d900aull},  // 720.5
    };
    for (const Case& c : cases) {
        const double x = static_cast<double>(Real(c.radians));
        C15_CHECK(Bits64(crt::Sin(x, 0)) == c.sine);
        C15_CHECK(Bits64(crt::Sin(x, 1)) == c.cosine);
    }
    C15_CHECK(Bits64(crt::Sin(-0.0, 0)) == 0x8000000000000000ull);  // zero: x itself
    C15_CHECK(crt::Sin(0.0, 1) == 1.0);
}

void TestRotate() {
    // RwMatrixRotate(axis (1,1,0), 30 deg, replace): the axis through rwInvSqrt, sin/cos through _Sin.
    RwMatrix m = MakeMatrix({1, 0, 0}, {0, 1, 0}, {0, 0, 1}, {0, 0, 0}, 0x20003u);
    const RwV3d axis = {1.0f, 1.0f, 0.0f};
    C15_CHECK(RwMatrixRotate(&m, &axis, 30.0f, rwCOMBINEREPLACE) == &m);
    CHECK_BITS(m.right.x, 0x3f6ed9ecu);
    CHECK_BITS(m.right.y, 0x3d8930a3u);
    CHECK_BITS(m.right.z, 0xbeb504f3u);
    CHECK_BITS(m.up.x, 0x3d8930a3u);
    CHECK_BITS(m.up.y, 0x3f6ed9ecu);
    CHECK_BITS(m.up.z, 0x3eb504f3u);
    CHECK_BITS(m.at.x, 0x3eb504f3u);
    CHECK_BITS(m.at.y, 0xbeb504f3u);
    CHECK_BITS(m.at.z, 0x3f5db3d7u);
    C15_CHECK(m.flags == rwMATRIXTYPEORTHONORMAL);
    CHECK_BITS(m.pos.x, 0u);
}

void TestMultiply() {
    // Integer entries: every lane is exact. B's w lanes: flags 0x20003 (a denormal: flushed, non-Java
    // mode), pads 1.0, 2.0, 0.5. Output w lanes (pads) = a_i.y * 1 + a_i.z * 2 (+ 0.5 for pos).
    const RwMatrix a = MakeMatrix({1, 2, 3}, {4, 5, 6}, {7, 8, 9}, {10, 11, 12}, 0x3u);
    RwMatrix b = MakeMatrix({1, 0, 0}, {0, 2, 0}, {0, 0, 4}, {5, 6, 7}, 0x20003u);
    b.pad1 = Bits(1.0f);
    b.pad2 = Bits(2.0f);
    b.pad3 = Bits(0.5f);
    RwMatrix o;
    RwMatrixMultiply(&o, &a, &b);
    CHECK_BITS(o.right.x, Bits(1.0f));
    CHECK_BITS(o.right.y, Bits(4.0f));
    CHECK_BITS(o.right.z, Bits(12.0f));
    CHECK_BITS(o.up.z, Bits(24.0f));
    CHECK_BITS(o.at.y, Bits(16.0f));
    CHECK_BITS(o.pos.x, Bits(15.0f));
    CHECK_BITS(o.pos.y, Bits(28.0f));
    CHECK_BITS(o.pos.z, Bits(55.0f));
    C15_CHECK(o.flags == 0x3u);
    C15_CHECK(o.pad1 == Bits(17.0f));
    C15_CHECK(o.pad2 == Bits(26.0f));
    C15_CHECK(o.pad3 == Bits(35.5f));
    // In place (dst == a): every lane is loaded before the stores, so the axes are the same; but the
    // flags are read after the stores, from the right row's w lane (2 + 3*2 = 8.0f): 0x41000000 & 0x20003.
    RwMatrix c = a;
    RwMatrixMultiply(&c, &c, &b);
    C15_CHECK(c.flags == 0u);
    c.flags = o.flags;
    C15_CHECK(std::memcmp(&c, &o, sizeof c) == 0);
    // Only denormal w inputs: the pos pad is 10 * denormal + 0, flushed to +0 (non-Java mode).
    RwMatrix b2 = MakeMatrix({1, 0, 0}, {0, 1, 0}, {0, 0, 1}, {0, 0, 0}, 0x20003u);
    RwMatrixMultiply(&o, &a, &b2);
    C15_CHECK(o.pad3 == 0u);
    C15_CHECK(o.flags == 0x3u);
}

void TestInvert() {
    // Generic (flags 0): scale (2,4,8) with pos (2,4,8). Hand-derived through the cofactor sequence: the
    // fnmsubs cofactors give -0.0 where the minors are 0 - 0.
    RwMatrix in = MakeMatrix({2, 0, 0}, {0, 4, 0}, {0, 0, 8}, {2, 4, 8}, 0u);
    RwMatrix o;
    RwMatrixInvert(&o, &in);
    CHECK_BITS(o.right.x, Bits(0.5f));
    CHECK_BITS(o.right.y, 0x80000000u);
    CHECK_BITS(o.right.z, 0x00000000u);
    CHECK_BITS(o.up.x, 0x80000000u);
    CHECK_BITS(o.up.y, Bits(0.25f));
    CHECK_BITS(o.up.z, 0x80000000u);
    CHECK_BITS(o.at.x, 0x00000000u);
    CHECK_BITS(o.at.y, 0x80000000u);
    CHECK_BITS(o.at.z, Bits(0.125f));
    CHECK_BITS(o.pos.x, Bits(-1.0f));
    CHECK_BITS(o.pos.y, Bits(-1.0f));
    CHECK_BITS(o.pos.z, Bits(-1.0f));
    C15_CHECK(o.flags == 0u);
    // Orthonormal (flags 3): the transpose, pos = -(p . axis).
    in = MakeMatrix({0, 1, 0}, {-1, 0, 0}, {0, 0, 1}, {1, 2, 3}, 3u);
    RwMatrixInvert(&o, &in);
    CHECK_BITS(o.right.x, 0u);
    CHECK_BITS(o.right.y, Bits(-1.0f));
    CHECK_BITS(o.up.x, Bits(1.0f));
    CHECK_BITS(o.at.z, Bits(1.0f));
    CHECK_BITS(o.pos.x, Bits(-2.0f));
    CHECK_BITS(o.pos.y, Bits(1.0f));
    CHECK_BITS(o.pos.z, Bits(-3.0f));
    C15_CHECK(o.flags == 3u);
    // Identity-flagged: a plain copy, pads included.
    in = MakeMatrix({3, 0, 0}, {0, 3, 0}, {0, 0, 3}, {1, 1, 1}, 0x20003u);
    in.pad2 = 0x12345678u;
    RwMatrixInvert(&o, &in);
    C15_CHECK(std::memcmp(&o, &in, sizeof o) == 0);
}

void TestEdits() {
    RwMatrix m = MakeMatrix({1, 0, 0}, {0, 1, 0}, {0, 0, 1}, {0, 0, 0}, 0x20003u);
    const RwV3d t = {1.0f, 2.0f, 3.0f};
    RwMatrixTranslate(&m, &t, rwCOMBINEPOSTCONCAT);
    C15_CHECK(m.flags == 0x3u);  // only the identity bit goes
    CHECK_BITS(m.pos.z, Bits(3.0f));
    const RwV3d s = {2.0f, 2.0f, 2.0f};
    RwMatrixScale(&m, &s, rwCOMBINEPRECONCAT);
    C15_CHECK(m.flags == 0u);    // type and identity go
    CHECK_BITS(m.right.x, Bits(2.0f));
    CHECK_BITS(m.pos.z, Bits(3.0f));  // preconcat scale leaves pos
    RwMatrixTranslate(&m, &t, rwCOMBINEPRECONCAT);
    CHECK_BITS(m.pos.x, Bits(3.0f));  // 1 + 1*2
    CHECK_BITS(m.pos.z, Bits(9.0f));  // 3 + 3*2
    m.flags = 0x40u;
    RwMatrixTranslate(&m, &t, rwCOMBINEREPLACE);
    C15_CHECK(m.flags == 0x43u);       // (flags | 0x20003) & ~0x20000
    CHECK_BITS(m.right.x, Bits(1.0f));
    CHECK_BITS(m.pos.y, Bits(2.0f));
    RwMatrixUpdate(&m);
    C15_CHECK(m.flags == 0x40u);
    RwMatrix* created = RwMatrixCreate();
    C15_CHECK(created != nullptr && created->flags == 0x20003u && created->at.z == 1.0f);
    RwMatrixDestroy(created);
}

void TestOrthoNormalizeAndOptimize() {
    RwMatrix m = MakeMatrix({2, 0, 0}, {0, 4, 0}, {0, 0, 0.25f}, {5, 6, 7}, 0x20000u);  // exact table roots
    RwMatrixOrthoNormalize(&m, &m);
    CHECK_BITS(m.right.x, Bits(1.0f));
    CHECK_BITS(m.up.y, Bits(1.0f));
    CHECK_BITS(m.at.z, Bits(1.0f));
    CHECK_BITS(m.pos.y, Bits(6.0f));
    C15_CHECK(m.flags == 0x3u);
    RwMatrixOptimize(&m, nullptr);
    C15_CHECK(m.flags == 0x3u);  // normal + orthogonal, pos (5,6,7) is far from the identity
    m.pos = {0, 0, 0};
    RwMatrixOptimize(&m, nullptr);
    C15_CHECK(m.flags == 0x20003u);
    const RwMatrix scaled = MakeMatrix({2, 0, 0}, {0, 1, 0}, {0, 0, 1}, {0, 0, 0}, 0u);
    m = scaled;
    RwMatrixOptimize(&m, nullptr);
    C15_CHECK(m.flags == 0x2u);  // orthogonal, not normal
    CHECK_BITS(_rwMatrixDeterminant(&scaled), Bits(2.0f));
    CHECK_BITS(_rwMatrixNormalError(&scaled), Bits(9.0f));
}

void TestVectors() {
    const RwV3d v = {3.0f, 4.0f, 12.0f};
    RwV3d n;
    CHECK_BITS(RwV3dNormalize(&n, &v), 0x41500000u);  // 13
    CHECK_BITS(n.x, 0x3e6c4ec6u);
    CHECK_BITS(n.y, 0x3e9d89d9u);
    CHECK_BITS(n.z, 0x3f6c4ec6u);
    CHECK_BITS(_rwV3dNormalize(&n, &v), 0x3d9d89d9u);
    CHECK_BITS(RwV3dLength(&v), 0x41500000u);
    const RwV2d w = {1.0f, 1.0f};
    CHECK_BITS(RwV2dLength(&w), 0x3fb504f3u);
    RwV2d wn;
    CHECK_BITS(RwV2dNormalize(&wn, &w), 0x3fb504f3u);
    CHECK_BITS(wn.x, 0x3f3504f3u);
    const RwV3d zero = {0.0f, 0.0f, 0.0f};
    CHECK_BITS(RwV3dNormalize(&n, &zero), 0u);
    CHECK_BITS(n.x, 0u);
    // TransformPoint: (1,2,3) through right (1,0,0) up (0,2,0) at (0,0,4) pos (5,6,7).
    const RwMatrix m = MakeMatrix({1, 0, 0}, {0, 2, 0}, {0, 0, 4}, {5, 6, 7}, 0u);
    RwV3d p = {1.0f, 2.0f, 3.0f};
    RwV3dTransformPoint(&p, &p, &m);  // in place
    CHECK_BITS(p.x, Bits(6.0f));
    CHECK_BITS(p.y, Bits(10.0f));
    CHECK_BITS(p.z, Bits(19.0f));
    RwV3d q = {1.0f, 2.0f, 3.0f};
    RwV3dTransformVectors(&q, &q, 1, &m);
    CHECK_BITS(q.z, Bits(12.0f));
}

void TestIm3D() {
    RwIm3DResetForTest();
    RwInt32 word = -1;
    // Device-start states (RwPSGL_SetupDefaultRenderStates_maybe).
    struct Default {
        RwRenderState state;
        RwInt32 value;
    } defaults[] = {
        {rwRENDERSTATEZTESTENABLE, 1},       {rwRENDERSTATEZWRITEENABLE, 1},
        {rwRENDERSTATESHADEMODE, 2},         {rwRENDERSTATESRCBLEND, 5},
        {rwRENDERSTATEDESTBLEND, 6},         {rwRENDERSTATEVERTEXALPHAENABLE, 0},
        {rwRENDERSTATECULLMODE, 2},          {rwRENDERSTATEALPHATESTFUNCTION, 5},
        {rwRENDERSTATEALPHATESTFUNCTIONREF, 0}, {rwRENDERSTATETEXTUREADDRESS, 1},
        {rwRENDERSTATETEXTUREFILTER, 2},     {rwRENDERSTATEFOGTYPE, 1},
        {rwRENDERSTATEFOGDENSITY, 1},        {rwRENDERSTATETEXTUREPERSPECTIVE, 1},
        {rwRENDERSTATESRCBLENDALPHA, 5},     {rwRENDERSTATEDESTBLENDALPHA, 6},
    };
    for (const Default& d : defaults) {
        C15_CHECK(RwRenderStateGet(d.state, &word) == 1 && word == d.value);
    }
    C15_CHECK(RwRenderStateGet(rwRENDERSTATEBORDERCOLOR, &word) == 0);
    // Setter results (Apply2DRenderStates / SetUIOverlayRenderStates values and rejected ones).
    C15_CHECK(RwRenderStateSet(rwRENDERSTATESHADEMODE, reinterpret_cast<void*>(3)) == 0);
    C15_CHECK(RwRenderStateSet(rwRENDERSTATEDESTBLEND, reinterpret_cast<void*>(11)) == 0);
    C15_CHECK(RwRenderStateSet(rwRENDERSTATESRCBLEND, reinterpret_cast<void*>(11)) == 1);
    C15_CHECK(RwRenderStateSet(rwRENDERSTATECULLMODE, reinterpret_cast<void*>(1)) == 1);
    C15_CHECK(RwRenderStateGet(rwRENDERSTATECULLMODE, &word) == 1 && word == 1);
    C15_CHECK(RwRenderStateSet(rwRENDERSTATEALPHATESTFUNCTIONREF, reinterpret_cast<void*>(0x1c8)) == 1);
    C15_CHECK(RwRenderStateGet(rwRENDERSTATEALPHATESTFUNCTIONREF, &word) == 1 && word == 0xc8);
    C15_CHECK(RwRenderStateSet(rwRENDERSTATEVERTEXALPHAENABLE, reinterpret_cast<void*>(5)) == 1);
    C15_CHECK(RwRenderStateGet(rwRENDERSTATEVERTEXALPHAENABLE, &word) == 1 && word == 1);
    C15_CHECK(RwRenderStateSet(rwRENDERSTATEBORDERCOLOR, nullptr) == 0);
    C15_CHECK(RwRenderStateSet(rwRENDERSTATETEXTUREADDRESSU, reinterpret_cast<void*>(3)) == 1);
    C15_CHECK(RwRenderStateGet(rwRENDERSTATETEXTUREADDRESS, &word) == 1 && word == 0);  // U != V

    // The pool.
    RwIm3DVertex verts[4] = {};
    for (int i = 0; i < 4; ++i) verts[i].objVertex = {static_cast<float>(i), 0.0f, 0.0f};
    RwImVertexIndex idx[7] = {0, 1, 2, 0, 2, 3, 1};
    C15_CHECK(RwIm3DRenderPrimitive(rwPRIMTYPETRILIST) == 0);  // nothing open
    C15_CHECK(RwIm3DEnd() == 0);
    C15_CHECK(RwIm3DTransform(verts, 0x10001u, nullptr, 0) == nullptr);
    C15_CHECK(RwIm3DTransform(verts, 4, nullptr, rwIM3D_VERTEXUV) == verts);
    C15_CHECK(RwIm3DRenderIndexedPrimitive(rwPRIMTYPETRILIST, idx, 7) == 1);
    C15_CHECK(RwIm3DRenderIndexedPrimitive(rwPRIMTYPELINELIST, idx, 5) == 1);
    C15_CHECK(RwIm3DRenderPrimitive(rwPRIMTYPEPOINTLIST) == 0);  // not a PS3 im3d primitive
    C15_CHECK(RwIm3DRenderPrimitive(rwPRIMTYPETRIFAN) == 1);
    C15_CHECK(RwIm3DEnd() == 1);
    C15_CHECK(RwIm3DEnd() == 0);
    // Zero vertices still open the pool; exactly 0x10000 wraps the 16-bit count to 0.
    C15_CHECK(RwIm3DTransform(verts, 0, nullptr, 0) == verts);
    C15_CHECK(RwIm3DRenderPrimitive(rwPRIMTYPETRILIST) == 1);
    RwIm3DEnd();
    const std::vector<RwIm3DDraw>& draws = RwIm3DFrameDraws();
    C15_CHECK(draws.size() == 4);
    if (draws.size() == 4) {
        C15_CHECK(draws[0].indexed && draws[0].indices.size() == 6 && draws[0].vertices.size() == 4);
        C15_CHECK(draws[0].transformFlags == (rwIM3D_VERTEXUV | rwIM3D_VERTEXXYZ | rwIM3D_VERTEXRGBA));
        C15_CHECK(!draws[0].hasLtm);
        C15_CHECK(draws[0].states.srcBlend == 11 && draws[0].states.cullEnabled == 0);
        C15_CHECK(draws[1].primType == rwPRIMTYPELINELIST && draws[1].indices.size() == 4);
        C15_CHECK(!draws[2].indexed && draws[2].primType == rwPRIMTYPETRIFAN && draws[2].vertices.size() == 4);
        C15_CHECK(draws[3].vertices.empty());
        CHECK_BITS(draws[2].vertices[3].objVertex.x, Bits(3.0f));
    }
    RwIm3DBeginFrame();
    C15_CHECK(RwIm3DFrameDraws().empty());
    RwIm3DResetForTest();
}

}  // namespace

int main() {
    TestSqrt();
    TestSin();
    TestRotate();
    TestMultiply();
    TestInvert();
    TestEdits();
    TestOrthoNormalizeAndOptimize();
    TestVectors();
    TestIm3D();
    if (c15::g_failures == 0) std::printf("rwcore: all tests passed\n");
    return c15::g_failures == 0 ? 0 : 1;
}
