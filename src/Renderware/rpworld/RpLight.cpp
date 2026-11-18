// RpLight.cpp - the light rig's RenderWare light (see RpLight.h).
#include "Renderware/rpworld/RpLight.h"

#include <cstring>

#include "Renderware/rpworld/RpWorld.h"
#include "Renderware/rwcore/RwFrameList.h"
#include "Renderware/rwcore/RwMatrix.h"
#include "crt/ppc_ops.h"

RwUInt16 g_rwLightFrame = 0;

// 0x006a2970 RpLightCreate
RpLight* RpLightCreate(RwInt32 type) {
    RpLight* light = new RpLight();
    std::memset(light, 0, sizeof(RpLight));
    light->object.type = 3;  // rpLIGHT
    light->object.subType = static_cast<RwUInt8>(type);
    light->object.privateFlags = 1;
    light->object.flags = 3;  // rpLIGHTLIGHTATOMICS | rpLIGHTLIGHTWORLD
    light->lightFrame = static_cast<RwUInt16>(g_rwLightFrame - 1);
    light->radius = 0.0f;
    for (float& channel : light->color) channel = 1.0f;
    light->minusCosAngle = 0.0f;
    light->WorldSectorsInLight.next = &light->WorldSectorsInLight;  // rwLinkListInitialize
    light->WorldSectorsInLight.prev = &light->WorldSectorsInLight;
    light->world = nullptr;
    // The PSGL light extension's constructor 0x006ba398 (TOC -0x43c0 5.0f, -0x43c4 1.0f, a zero word).
    light->psglSoftSpotExponent = 5.0f;
    light->psglAttenuation[0] = 1.0f;
    light->psglAttenuation[1] = 0.0f;
    light->psglAttenuation[2] = 5.0f;
    return light;
}

RwBool RpLightDestroy(RpLight* light) {
    delete light;
    return 1;
}

// 0x006b2e50 RpLightGetWorld
RpWorld* RpLightGetWorld(const RpLight* light) { return light->world; }

// 0x006b2e68 RpWorldAddLight: an ambient or directional light (subType below 0x80) at the head of the world's directional
// light list; a positional one has its frame marked dirty (it is placed in the sectors at the next sync) and goes at the
// head of the light list.
RpWorld* RpWorldAddLight(RpWorld* world, RpLight* light) {
    light->world = world;
    RwLLLink* head;
    if (static_cast<int8_t>(light->object.subType) >= 0) {
        head = &world->directionalLightList.link;
    } else {
        if (light->object.parent != nullptr) RwFrameUpdateObjects(static_cast<RwFrame*>(light->object.parent));
        head = &world->lightList.link;
    }
    light->inWorld.next = head->next;
    light->inWorld.prev = head;
    RwLLLink* first = head->next;
    head->next = &light->inWorld;
    first->prev = &light->inWorld;
    return world;
}

// 0x006b52d8 RpWorldRemoveLight: the world extension cleared, the light's sector ties freed (none: no light here is
// positional), the light unlinked from the world's list.
RpWorld* RpWorldRemoveLight(RpWorld* world, RpLight* light) {
    light->world = nullptr;
    RwLLLink* prev = light->inWorld.prev;
    prev->next = light->inWorld.next;
    light->inWorld.next->prev = prev;
    return world;
}

namespace {
inline RwReal Word(uint32_t bits) {
    RwReal value;
    std::memcpy(&value, &bits, 4);
    return value;
}
// RpLightGetConeAngle's TOC constants (lib TOC 0xc25974 - 0x4620 .. - 0x45d8, 0xc21354 ..), by their bits.
const RwReal kOne = Word(0x3f800000);        // -0x4620
const RwReal kPi = Word(0x40490fdb);         // -0x461c
const RwReal kHalfPi = Word(0x3fc90fdb);     // -0x4618
const RwReal kAcosP1 = Word(0x3811ef08);     // -0x4614
const RwReal kAcosP0 = Word(0x3a4f7f04);     // -0x4610
const RwReal kAcosP2 = Word(0x3d241146);     // -0x460c
const RwReal kAcosP3 = Word(0x3e4e0aa8);     // -0x4608
const RwReal kAcosP4 = Word(0x3ea6b090);     // -0x4604
const RwReal kAcosP5 = Word(0x3e2aaaab);     // -0x4600
const RwReal kAcosQ1 = Word(0x3d9dc62e);     // -0x45fc
const RwReal kAcosQ0 = Word(0x3f303361);     // -0x45f8
const RwReal kAcosQ2 = Word(0x4001572d);     // -0x45f4
const RwReal kAcosQ3 = Word(0x4019d139);     // -0x45f0
const RwReal kPio2Lo = Word(0x33a22168);     // -0x45ec
const RwReal kPio2Hi = Word(0x3fc90fda);     // -0x45e8
const RwReal kHalf = Word(0x3f000000);       // -0x45e4
const RwReal kMinusTwo = Word(0xc0000000);   // -0x45e0
const RwReal kPiHi = Word(0x40490fda);       // -0x45dc
const RwReal kZero = Word(0x00000000);       // -0x45d8

// The acos polynomials: p(z) one fused chain, q(z) the other (the same in the three branches).
RwReal ConeAcosP(RwReal z) {
    RwReal p = ppc::fmadds(z, kAcosP1, kAcosP0);
    p = ppc::fmsubs(z, p, kAcosP2);
    p = ppc::fmadds(z, p, kAcosP3);
    p = ppc::fmsubs(z, p, kAcosP4);
    return ppc::fmadds(z, p, kAcosP5);
}
RwReal ConeAcosQ(RwReal z) {
    RwReal q = ppc::fmsubs(z, kAcosQ1, kAcosQ0);
    q = ppc::fmadds(z, q, kAcosQ2);
    q = ppc::fmsubs(z, q, kAcosQ3);
    return ppc::fmadds(z, q, kOne);
}
}  // namespace

// 0x006a2be8 RpLightGetConeAngle: x = -minusCosAngle, branching on its bits: |x| >= 1 (or NaN) pi for a negative sign
// (or zero bits), else 0; |x| < 0.5: pi/2 below 2^-57 (0x23000000), else pio2_hi - (x - (pio2_lo - x r(x^2))); x <= -0.5:
// s = sqrt((1 + x) / 2), pi_hi - 2 (s + (s r - pio2_lo)) (one fmadds by -2); x >= 0.5: s = sqrt((1 - x) / 2), its high
// bits df, 2 (df + (s r + (z - df^2) / (s + df))). r(z) = z p(z) / q(z).
RwReal RpLightGetConeAngle(const RpLight* light) {
    const RwReal x = -light->minusCosAngle;
    uint32_t bits;
    std::memcpy(&bits, &x, 4);
    const int32_t sbits = static_cast<int32_t>(bits);
    const int32_t ix = static_cast<int32_t>(bits & 0x7fffffffu);
    if (ix > 0x3f7fffff) return sbits <= 0 ? kPi : kZero;
    if (ix <= 0x3effffff) {
        if (ix <= 0x23000000) return kHalfPi;
        const RwReal z = x * x;
        const RwReal r = (z * ConeAcosP(z)) / ConeAcosQ(z);
        return kPio2Hi - (x - (kPio2Lo - x * r));
    }
    if (sbits < 0) {
        const RwReal z = (x + kOne) * kHalf;
        const RwReal s = rwSqrt(z);  // 0x0075e738
        const RwReal r = (z * ConeAcosP(z)) / ConeAcosQ(z);
        const RwReal w = ppc::fmsubs(s, r, kPio2Lo);
        return ppc::fmadds(s + w, kMinusTwo, kPiHi);
    }
    const RwReal z = (kOne - x) * kHalf;
    const RwReal s = rwSqrt(z);
    uint32_t high;
    std::memcpy(&high, &s, 4);
    high &= 0xfffff000u;  // rlwinm 0, 0x13
    RwReal df;
    std::memcpy(&df, &high, 4);
    const RwReal c = (z - df * df) / (s + df);
    const RwReal r = (z * ConeAcosP(z)) / ConeAcosQ(z);
    const RwReal half = df + ppc::fmadds(s, r, c);
    return half + half;
}
