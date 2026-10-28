// rpteam_test - C2.5 step 6: the RpTeam model on a synthetic team (no game data, no device): a dictionary of two static elements,
// three players with two element slots each. Activity moves the dictionary's per-element counts, unlocking rebuilds the static
// render lists (one group per used element, one {matrix, player} entry per active player's slot), RpTeamRender's passes give the
// players their clip state and put each node's matrix on the element atomic's frame, and the team tears down.
#include <cstdio>

#include "Renderware/rpteam/RpTeam.h"
#include "Renderware/rpworld/RpAtomic.h"
#include "Renderware/rpworld/RpGeometry.h"
#include "Renderware/rwcore/RwCamera.h"
#include "Renderware/rwcore/RwFrameList.h"

namespace {
int g_failures = 0;
void Expect(bool ok, const char* what) {
    if (!ok) {
        std::printf("rpteam: FAIL %s\n", what);
        ++g_failures;
    }
}

RpAtomic* ElementAtomic(int32_t hanimId) {
    RpAtomic* atomic = RpAtomicCreate();
    RwFrame* frame = RwFrameCreate();
    frame->hanimID = hanimId;
    RpAtomicSetFrame(atomic, frame);
    return atomic;
}
}  // namespace

int main() {
    RpTeamDictionary* dictionary = RpTeamDictionaryCreate(2);
    for (uint32_t element = 0; element < 2; ++element) {
        RpAtomic* source = ElementAtomic(static_cast<int32_t>(7 + element));
        RpTeamDictionarySetElement(dictionary, source, rpTEAMELEMENTSTATIC, 0, element);
        RwFrame* sourceFrame = source->frame;
        RpAtomicDestroy(source);
        RwFrameDestroy(sourceFrame);
    }
    RpAtomic* first = RpTeamDictionaryGetElement(dictionary, 0);
    Expect(first != nullptr && first->frame != nullptr && first->frame->hanimID == 7, "the element keeps its frame id (own frame)");
    Expect(first->renderCallBack == nullptr, "the element atomic has no render callback");
    Expect(dictionary->elements[0].type == rpTEAMELEMENTSTATIC && RpTeamDictionaryGetLODElement(dictionary, 0, 3) == nullptr, "LOD 0 only");

    RpTeam* team = RpTeamCreate(3, 2);
    RpTeamSetDictionary(team, dictionary);
    // player 0: elements 0 and 1; player 1: element 1; player 2: element 0
    const int32_t slots[3][2] = {{0, 1}, {1, -1}, {0, -1}};
    for (uint32_t p = 0; p < 3; ++p) {
        RpTeamPlayer* player = RpTeamGetPlayer(team, p);
        for (uint32_t slot = 0; slot < 2; ++slot) RpTeamPlayerSetElement(player, slot, slots[p][slot]);
        RwFrame* frame = RwFrameCreate();
        frame->modelling.pos = {10.0f * (p + 1), 0.0f, 0.0f};
        RpTeamPlayerSetHierarchyFrame(player, frame);
    }
    Expect(dictionary->elements[0].refCount == 2 && dictionary->elements[1].refCount == 2, "every slot counts on its element");
    Expect(team->selected[0] == 0 && team->selected[1] == 0, "inactive players are not selected");
    RpTeamUnlock(team);
    Expect(team->stat.optimized == 1 && team->stat.numElements == 0, "no active player: no group");

    RpTeamLock(team, 2);
    RpTeamPlayerSetActivity(RpTeamGetPlayer(team, 0), 1);
    RpTeamPlayerSetActivity(RpTeamGetPlayer(team, 1), 1);
    Expect(RpTeamPlayerSetActivity(RpTeamGetPlayer(team, 1), 1) == nullptr, "a second activation does nothing");
    Expect(RpTeamPlayerSetActivity(RpTeamGetPlayer(team, 2), 0) == nullptr, "switching off an inactive player does nothing");
    Expect(team->selected[0] == 1 && team->selected[1] == 2, "active counts per element: 1 and 2");
    Expect(team->stat.optimized == 0, "the lists are stale after an activation");
    RpTeamUnlock(team);
    Expect(team->stat.optimized == 1 && team->stat.numElements == 2, "two groups after the unlock");
    if (team->stat.numElements == 2) {
        const RpTeamOptElement& g0 = team->stat.data[0];
        const RpTeamOptElement& g1 = team->stat.data[1];
        Expect(g0.lodAtomic == &dictionary->elements[0] && g0.numClones == 1 && g0.stack == 1, "group 0: element 0, one player");
        Expect(g1.lodAtomic == &dictionary->elements[1] && g1.numClones == 2 && g1.stack == 2, "group 1: element 1, two players");
        Expect(g0.render[0].player == RpTeamGetPlayer(team, 0), "group 0 holds player 0");
        Expect(g1.render[0].player == RpTeamGetPlayer(team, 0) && g1.render[1].player == RpTeamGetPlayer(team, 1), "group 1 holds players 0 and 1 in player order");
        Expect(g1.render[1].frame == RpTeamGetPlayer(team, 1)->frame && g1.render[1].matrices == nullptr, "without a hierarchy the entry's matrix is the player frame's LTM");
    }

    const uint32_t drawnBefore = RpTeamDrawnAtomics();
    RpTeamRender(team, 2 | 8);
    Expect(RpTeamGetPlayer(team, 0)->playerClip == 1 && RpTeamGetPlayer(team, 2)->playerClip == 0, "the clip state: 1 for an active player, 0 for the others");
    Expect((RpTeamGetPlayer(team, 0)->flags & 2) != 0 && (RpTeamGetPlayer(team, 2)->flags & 2) == 0, "flag 2 follows the activity");
    Expect(RpTeamDrawnAtomics() - drawnBefore == 3, "three element atomics drawn: player 0 twice, player 1 once");
    const RwMatrix* ltm = RwFrameGetLTM(RpTeamDictionaryGetElement(dictionary, 1)->frame);
    Expect(ltm->pos.x == 20.0f, "the last drawn entry (player 1) left its node's matrix on the element atomic's frame");
    RpTeamGetPlayer(team, 0)->flags |= 0x10;  // the sphere crossed the frustum
    RpTeamRender(team, 2);
    Expect(RpTeamGetPlayer(team, 0)->playerClip == 3, "a player that crosses the frustum clips with 3");

    RpTeamLock(team, 2);
    RpTeamPlayerSetActivity(RpTeamGetPlayer(team, 0), 0);
    RpTeamPlayerSetActivity(RpTeamGetPlayer(team, 2), 1);
    RpTeamUnlock(team);
    Expect(team->selected[0] == 1 && team->selected[1] == 1, "after the swap: one player each");
    Expect(team->stat.numElements == 2 && team->stat.data[0].render[0].player == RpTeamGetPlayer(team, 2) &&
               team->stat.data[1].render[0].player == RpTeamGetPlayer(team, 1),
           "the lists follow the swap");
    RpTeamPlayerSetElement(RpTeamGetPlayer(team, 2), 0, -1);  // an active player loses its element
    Expect(team->selected[0] == 0 && dictionary->elements[0].refCount == 1 && team->stat.optimized == 0, "an element given up leaves the counts and stales the lists");

    RpTeamLock(team, 0xff);
    RpTeamDictionaryDestroy(RpTeamGetDictionary(team));
    RpTeamSetDictionary(team, nullptr);
    RpTeamDestroy(team);
    std::printf("rpteam: %d failure(s)\n", g_failures);
    return g_failures == 0 ? 0 : 1;
}
