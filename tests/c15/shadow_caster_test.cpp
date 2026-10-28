// shadow_caster_test - C2.5 step 6: CKSrvShadow_UnregisterCaster (0x1fd6f0) on hand-built lists (no game data, no engine).
// The drawing list of a priority gives its spot back to the unused list (the ground's in-use byte cleared, the spot told
// to hide, its links cleared); a ground that only waits leaves its waiting list; a priority other than 0 / 1 does nothing; a
// waiting caster that was not queued this frame does not take the freed spot. (The taker's path registers it again: that is
// RegisterCaster's SetData, which needs the spot node's material, so it is not built here.)
#include <cstdio>

#include "k2000/components/CKShadowCpnt.h"
#include "k2000/render/CRenderer.h"
#include "k2000/scenegraph/CSGLeaf.h"
#include "k2000/services/CKSrvShadow.h"

namespace {
int g_failures = 0;
void Expect(bool ok, const char* what) {
    if (!ok) {
        std::printf("shadow_caster: FAIL %s\n", what);
        ++g_failures;
    }
}

using Spot = CKSrvShadow::CKShadowDataSpot;
using Waiting = CKSrvShadow::CKShadowDataWaiting;

void Arm(Spot& spot, CKShadowSpot& shadow, CKShadowGround& ground, IKSerializable* component) {
    ground.m_bUsed_maybe = 1;
    spot.m_pShadow = &shadow;
    spot.m_pShadowGround = &ground;
    spot.m_pShadowCpnt = component;
    spot.m_pShadowedLeaf = &spot;  // any non-null leaf
    shadow.m_pShadowCpnt = component;
}
}  // namespace

int main() {
    g_ui16RenderFrameCounter = 7;
    CKShadowCpnt high, low, odd;
    high.m_ui8Priority = 0;
    low.m_ui8Priority = 1;
    odd.m_ui8Priority = 2;

    {  // the only spot of the high-priority drawing list goes back to the unused list
        CKSrvShadow service;
        Spot spot;
        CKShadowSpot shadow;
        CKShadowGround ground = {};
        Arm(spot, shadow, ground, &high);
        service.m_lDrawingShadowHighPriority = &spot;
        service.m_lShadowUnused = nullptr;
        service.UnregisterCaster(&ground, &high);
        Expect(service.m_lDrawingShadowHighPriority == nullptr, "high: the drawing list is empty");
        Expect(service.m_lShadowUnused == &spot, "high: the spot is on the unused list");
        Expect(ground.m_bUsed_maybe == 0, "high: the ground's byte is cleared");
        Expect(spot.m_pShadowGround == nullptr && spot.m_pShadowCpnt == nullptr && spot.m_pShadowedLeaf == nullptr, "high: the spot's links are cleared");
        Expect(shadow.m_pShadowCpnt == nullptr, "high: the shadow no longer knows its component");
    }
    {  // the second of two low-priority spots: the first stays, ends the list
        CKSrvShadow service;
        Spot first, second;
        CKShadowSpot shadowA, shadowB;
        CKShadowGround groundA = {}, groundB = {};
        Arm(first, shadowA, groundA, &low);
        Arm(second, shadowB, groundB, &low);
        first.m_pNext = &second;
        service.m_lDrawingShadowLowPriority = &first;
        Spot spare;
        service.m_lShadowUnused = &spare;
        service.UnregisterCaster(&groundB, &low);
        Expect(service.m_lDrawingShadowLowPriority == &first && first.m_pNext == nullptr, "low: the second spot left the list");
        Expect(service.m_lShadowUnused == &second && second.m_pNext == &spare, "low: the spot heads the unused list");
        Expect(groundA.m_bUsed_maybe == 1 && groundB.m_bUsed_maybe == 0, "low: only the freed ground's byte is cleared");
        service.UnregisterCaster(&groundA, &low);
        Expect(service.m_lDrawingShadowLowPriority == nullptr && service.m_lShadowUnused == &first, "low: the first spot goes too");
    }
    {  // a ground that is only waiting leaves the waiting list of its priority
        CKSrvShadow service;
        Waiting a, b;
        CKShadowGround groundA = {}, groundB = {};
        groundA.m_bUsed_maybe = groundB.m_bUsed_maybe = 1;
        a.m_pShadowGround = &groundA;
        a.m_pShadowCpnt = &low;
        a.m_pShadowedLeaf = &a;
        b.m_pShadowGround = &groundB;
        b.m_pShadowCpnt = &low;
        b.m_pShadowedLeaf = &b;
        a.m_pNext = &b;
        service.m_lShadowWaitingLowPriority = &a;
        service.m_lShadowWaitingUnused = nullptr;
        service.UnregisterCaster(&groundB, &low);
        Expect(a.m_pNext == nullptr && service.m_lShadowWaitingLowPriority == &a, "waiting: the slot left the list");
        Expect(service.m_lShadowWaitingUnused == &b, "waiting: the slot is unused");
        Expect(groundB.m_bUsed_maybe == 0 && b.m_pShadowGround == nullptr && b.m_pShadowCpnt == nullptr && b.m_pShadowedLeaf == nullptr,
               "waiting: its links and the ground's byte are cleared");
        Expect(groundA.m_bUsed_maybe == 1, "waiting: the other ground is untouched");
        service.UnregisterCaster(&groundB, &low);  // not found any more: nothing
        Expect(service.m_lShadowWaitingUnused == &b && service.m_lShadowWaitingLowPriority == &a, "waiting: an unknown ground changes nothing");
    }
    {  // a waiting caster whose leaf was not queued this frame does not take the freed spot; a priority 2 does nothing
        CKSrvShadow service;
        Spot spot;
        CKShadowSpot shadow;
        CKShadowGround ground = {};
        Arm(spot, shadow, ground, &high);
        service.m_lDrawingShadowHighPriority = &spot;
        CSGLeaf leaf;
        leaf.m_ui16LastRenderedFrame = 3;  // not the frame counter (7)
        Waiting waiting;
        CKShadowGround waitingGround = {};
        waitingGround.m_bUsed_maybe = 1;
        waiting.m_pShadowGround = &waitingGround;
        waiting.m_pShadowCpnt = &high;
        waiting.m_pShadowedLeaf = &leaf;
        service.m_lShadowWaitingHighPriority = &waiting;
        service.UnregisterCaster(&ground, &odd);
        Expect(service.m_lDrawingShadowHighPriority == &spot && ground.m_bUsed_maybe == 1, "priority 2: nothing happens");
        service.UnregisterCaster(&ground, &high);
        Expect(service.m_lShadowUnused == &spot, "a stale waiting caster leaves the spot to the unused list");
        Expect(service.m_lShadowWaitingHighPriority == &waiting && waitingGround.m_bUsed_maybe == 1, "the waiting caster stays");
    }
    std::printf("shadow_caster: %d failure(s)\n", g_failures);
    return g_failures == 0 ? 0 : 1;
}
