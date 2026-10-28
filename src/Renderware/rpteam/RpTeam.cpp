// RpTeam.cpp - see RpTeam.h.
#include "Renderware/rpteam/RpTeam.h"

#include <cstring>

#include "Renderware/rphanim/RpHAnim.h"
#include "Renderware/rpworld/RpAtomic.h"
#include "Renderware/rpworld/RpAtomicPSGL.h"
#include "Renderware/rpworld/RpClump.h"
#include "Renderware/rpworld/RpGeometry.h"
#include "Renderware/rwcore/RwCamera.h"
#include "Renderware/rwcore/RwFrameList.h"
#include "Renderware/rwcore/RwStream.h"
#include "k2000/core/Stub.h"

namespace {
uint32_t g_drawnAtomics = 0;  // DEV: RpTeamDrawnAtomics
constexpr uint32_t kIdStruct = 0x1;
constexpr uint32_t kIdTexture = 0x6;
constexpr uint32_t kIdClump = 0x10;
constexpr uint32_t kIdAtomic = 0x14;

bool ReadBytes(RwStream* stream, void* data, uint32_t length) { return length == 0 || RwStreamRead(stream, data, length) == length; }

// 0x00725170 _rpTeamSetRenderListsDirty_maybe: the lists of the element types in `types` (1 static, 2 skinned, 4 patch)
// are stale; the team is optimised again only when the skinned and patch parts are.
void SetRenderListsDirty(RpTeam* team, uint32_t types) {
    if ((types & 1) != 0) team->stat.optimized = 0;
    if ((types & 2) != 0) team->skinOptimized = 0;
    if ((types & 4) != 0) team->patchOptimized = 0;
    team->optimized = (team->patchOptimized != 0 && team->skinOptimized != 0) ? 1 : 0;
}

// 0x00722dd8 _rpTeamPlayerSetElementIndex_maybe: the slot's element changes; an active player keeps the dictionary's
// per-element counts and marks the lists of both element types stale.
void PlayerSetElementIndex(RpTeamPlayer* player, uint32_t slot, int32_t index) {
    RpTeam* team = player->team;
    RpTeamDictionary* dictionary = team->dictionary;
    const int32_t old = player->elements[slot];
    if (old != -1) {
        RpTeamDictionaryElement& element = dictionary->elements[static_cast<uint32_t>(old)];
        --element.refCount;
        player->elements[slot] = -1;
        if ((player->flags & 1) != 0) {
            --team->selected[static_cast<uint32_t>(old)];
            SetRenderListsDirty(team, static_cast<uint32_t>(element.type));
        }
    }
    if (index != -1) {
        RpTeamDictionaryElement& element = dictionary->elements[static_cast<uint32_t>(index)];
        ++element.refCount;
        if ((player->flags & 1) != 0) {
            ++team->selected[static_cast<uint32_t>(index)];
            SetRenderListsDirty(team, static_cast<uint32_t>(element.type));
        }
    }
    player->elements[slot] = index;
}

// 0x00721e98 _rpTeamAtomicSetFrameFast_maybe is the atomic's frame link; RpAtomic keeps the frame pointer only.

// RpHAnimFindHierarchyCB_maybe 0x727748 with RwFrameForAllChildren: the first frame below `frame`, depth first, that
// has an RpHAnim hierarchy; null when none has.
bool FindHierarchyFrame(RwFrame* frame, RwFrame** found);
void ForAllChildren(RwFrame* frame, RwFrame** found) {
    for (RwFrame* child = frame->child; child != nullptr;) {
        RwFrame* next = child->next;
        if (!FindHierarchyFrame(child, found)) break;
        child = next;
    }
}
bool FindHierarchyFrame(RwFrame* frame, RwFrame** found) {
    if (RpHAnimFrameGetHierarchy(frame) != nullptr) {
        *found = frame;
        return false;
    }
    ForAllChildren(frame, found);
    return *found == nullptr;
}

// 0x00726980 _rpTeamPlayerAllocMatrices_maybe: one matrix per node of the player's hierarchy (the skinned elements'
// palette cache, zeroed).
void PlayerAllocMatrices(RpTeamPlayer* player, const RpHAnimHierarchy* hierarchy) {
    player->skinCache.assign(static_cast<size_t>(hierarchy->numNodes), RwMatrix{});
}

// 0x00723058.. the element destroy of _rpTeamDictionaryElementDestroy_maybe 0x7234f0, per LOD slot (0x722f98): a static
// element's atomics own their frames.
void DestroyElementLOD(RpTeamDictionaryElement* element, uint32_t lod) {
    RpAtomic* atomic = element->lodAtomic[lod];
    if (atomic == nullptr) return;
    if (element->type == rpTEAMELEMENTSTATIC) {
        RwFrame* frame = atomic->frame;
        RpAtomicSetFrame(atomic, nullptr);
        RwFrameDestroy(frame);
    }
    RpAtomicDestroy(atomic);
    element->lodAtomic[lod] = nullptr;
}

// 0x00728980 .. the lists' reset of _rpTeamClearRenderLists_maybe 0x725978.
void ClearRenderLists(RpTeam* team) {
    team->stat.data.clear();
    team->stat.numElements = 0;
    team->stat.optimized = 0;
}

// _rpTeamOptimizeCreate_maybe 0x7251e0 (XXL2 _rpTeamOptimizeCreate), the static part (bit 1 of `which`): per dictionary
// element that is static and has active players, a group holding one {matrix, player} entry per active player (numClones
// of them); the matrix is the hierarchy's matrix of the element's node, or the player frame's LTM without a hierarchy.
// The skinned part (bit 2) has nothing to build here (STUB(C2.9): no skinned element is ever selected); bit 4 only marks
// the patch part valid.
void UpdateLockedData(RpTeam* team, uint32_t which) {
    RpTeamDictionary* dictionary = team->dictionary;
    if ((which & 1) != 0 && team->stat.optimized == 0) {
        ClearRenderLists(team);
        uint32_t groups = 0;
        uint32_t total = 0;
        if (dictionary != nullptr) {
            for (uint32_t i = 0; i < dictionary->numOfElements; ++i) {
                if (dictionary->elements[i].type == rpTEAMELEMENTSTATIC && team->selected[i] != 0) {
                    total += team->selected[i];
                    ++groups;
                }
            }
        }
        if (total != 0) {
            team->stat.data.assign(groups, RpTeamOptElement{});
            team->stat.numElements = groups;
            uint32_t group = 0;
            for (uint32_t i = 0; group < groups; ++i) {
                dictionary->map[i] = group;
                RpTeamDictionaryElement* element = &dictionary->elements[i];
                if (element->type == rpTEAMELEMENTSTATIC && team->selected[i] != 0) {
                    RpTeamOptElement& optElement = team->stat.data[group++];
                    optElement.numClones = team->selected[i];
                    optElement.stack = 0;
                    optElement.lodAtomic = element;
                    optElement.render.assign(optElement.numClones, RpTeamRenderStatic{});
                }
            }
            for (uint32_t p = 0; p < team->numOfPlayers; ++p) {
                RpTeamPlayer* player = &team->players[p];
                if ((player->flags & 1) == 0 || (player->elementFlags & 1) == 0) continue;
                RpHAnimHierarchy* hierarchy = RpHAnimFrameGetHierarchy(player->frame);
                for (uint32_t slot = 0; slot < team->numOfPlayerElements; ++slot) {
                    const int32_t index = player->elements[slot];
                    if (index == -1) continue;
                    RpTeamDictionaryElement* element = &dictionary->elements[static_cast<uint32_t>(index)];
                    if (element->type != rpTEAMELEMENTSTATIC) continue;
                    RpTeamRenderStatic entry = {};
                    if (hierarchy == nullptr) {
                        entry.frame = player->frame;  // + 0x50: the frame's LTM
                    } else {
                        const RwInt32 id = RpHAnimFrameGetID(element->lodAtomic[0]->frame);
                        entry.matrices = &hierarchy->pMatrixArray[RpHAnimIDGetIndex(hierarchy, id)];
                    }
                    entry.player = player;
                    RpTeamOptElement& optElement = team->stat.data[dictionary->map[static_cast<uint32_t>(index)]];
                    optElement.render[optElement.stack++] = entry;
                }
            }
        }
        team->stat.optimized = 1;
        team->optimized = (team->patchOptimized != 0 && team->skinOptimized != 0) ? 1 : 0;
    }
    if ((which & 2) != 0 && team->skinOptimized == 0) {
        if (dictionary != nullptr) {
            for (uint32_t i = 0; i < dictionary->numOfElements; ++i) {
                if (dictionary->elements[i].type == rpTEAMELEMENTSKINNED && team->selected[i] != 0) {
                    DOTD_STUB_ONCE("RpTeam: skinned elements (the skin lists and their matrix caches, C2.9)");
                }
            }
        }
        team->skinOptimized = 1;
        team->optimized = (team->patchOptimized != 0) ? 1 : 0;
    }
    if ((which & 4) != 0 && team->patchOptimized == 0) {
        team->patchOptimized = 1;
        team->optimized = (team->skinOptimized != 0) ? 1 : 0;
    }
}

// 0x00722540 _rpTeamPlayerRenderAtomic_maybe (XXL2 _rpTeamPlayerRenderAtomic): the player's before / after callbacks around
// the atomic's pipeline. The original also parks the player in two library globals (0xced6c4, 0xcfb9f4) that no code reads.
void RenderPlayerAtomic(RpAtomic* atomic, RpTeam* team, RpTeamPlayer* player) {
    const uint32_t index = static_cast<uint32_t>(player - team->players.data());
    int32_t before = 0;
    if (player->preRender != nullptr) before = player->preRender(team, index, atomic, player->callBackData);
    RpAtomicPSGL_Render(atomic);  // RW_ExecutePipeline of the atomic's pipeline (the shader manager's)
    ++g_drawnAtomics;
    if (player->postRender != nullptr && before != 0) player->postRender(team, index, atomic, player->callBackData);
}

// 0x00728988 _rpTeamRenderPlayers_maybe (XXL2 _rpTeamRender), the static part: every drawn player's atomic of its current
// LOD gets the matrix of its node as its frame's LTM and goes through the pipeline. The skinned lists come first and the
// shadow elements last in the original (STUB(C2.9) / dead: renderNumShadows is never set).
void RenderPlayers(RpTeam* team) {
    if (team->stat.optimized == 0) return;
    for (uint32_t g = 0; g < team->stat.numElements; ++g) {
        RpTeamOptElement& group = team->stat.data[g];
        for (uint32_t e = 0; e < group.stack; ++e) {
            RpTeamRenderStatic& entry = group.render[e];
            RpTeamPlayer* player = entry.player;
            if (player->playerClip == 0) continue;
            RpAtomic* atomic = group.lodAtomic->lodAtomic[player->currentLOD];
            if (atomic == nullptr) continue;
            const RwMatrix* matrix = entry.matrices != nullptr ? entry.matrices : RwFrameGetLTM(entry.frame);
            // The element atomic's own frame takes the node's matrix as its LTM (all 0x40 bytes), and the atomic is marked
            // changed. Natively the frame is a root whose LTM is owned by its writer (RwFrameGetLTM keeps it).
            RwFrame* atomicFrame = atomic->frame;
            atomicFrame->ltm = *matrix;
            atomicFrame->dotdLtmOwned = 1;
            atomicFrame->object.privateFlags = static_cast<RwUInt8>(atomicFrame->object.privateFlags & ~4u);
            RenderPlayerAtomic(atomic, team, player);
        }
    }
}
}  // namespace

// 0x00722ca0 RpTeamDictionaryCreate
RpTeamDictionary* RpTeamDictionaryCreate(uint32_t numOfElements) {
    RpTeamDictionary* dictionary = new RpTeamDictionary();
    dictionary->numOfElements = numOfElements;
    RpTeamDictionaryElement empty = {};
    dictionary->elements.assign(numOfElements, empty);
    dictionary->map.assign(numOfElements, 0);
    return dictionary;
}

// 0x00723250 RpTeamDictionarySetElement
RpTeamDictionary* RpTeamDictionarySetElement(RpTeamDictionary* dictionary, RpAtomic* atomic, RpTeamElementType type, uint32_t lod,
                                             uint32_t element) {
    RpTeamDictionaryElement* slot = &dictionary->elements[element];
    DestroyElementLOD(slot, lod);
    if (atomic != nullptr) {
        RpAtomic* clone = RpAtomicClone(atomic);
        clone->renderCallBack = nullptr;
        slot->lodAtomic[lod] = clone;
        slot->type = type;
        if (type == rpTEAMELEMENTSTATIC) {
            // The clone gets a frame of its own with the source frame's HAnim id (RpHAnimFrameSetID_maybe); then
            // _rpTeamAtomicSetStaticPipeline_maybe (not modelled).
            RwFrame* frame = RwFrameCreate();
            frame->hanimID = RpHAnimFrameGetID(atomic->frame);
            RpAtomicSetFrame(clone, frame);
        } else if (type == rpTEAMELEMENTSKINNED) {
            DOTD_STUB_ONCE("RpTeamDictionarySetElement: a skinned element (_rpTeamAtomicSetSkinPipeline_maybe 0x726948, C2.9)");
        }
        // lod 5 / 6: _rpTeamAtomicSetShadowPipeline_maybe; an atomic with MatFX effects: _rpTeamAtomicSetMatFXPipeline_maybe
        // (RW pipeline objects, not modelled).
    }
    return dictionary;
}

// 0x00723038 RpTeamDictionaryGetElement
RpAtomic* RpTeamDictionaryGetElement(RpTeamDictionary* dictionary, uint32_t element) { return dictionary->elements[element].lodAtomic[0]; }

// 0x00722bc0 RpTeamDictionaryGetLODElement
RpAtomic* RpTeamDictionaryGetLODElement(RpTeamDictionary* dictionary, uint32_t element, uint32_t lod) {
    return dictionary->elements[element].lodAtomic[lod];
}

// 0x00723aa0 RpTeamDictionaryDestroy
void RpTeamDictionaryDestroy(RpTeamDictionary* dictionary) {
    if (dictionary == nullptr) return;
    for (RpTeamDictionaryElement& element : dictionary->elements) {
        for (uint32_t lod = 0; lod < 7; ++lod) DestroyElementLOD(&element, lod);
        element.type = rpNATEAMELEMENTTYPE;
    }
    delete dictionary;
}

// 0x00722830 RpTeamCreate. The RW free list / allocation, the global team list (RpTeam_LinkIntoGlobalList_maybe) and
// the default LOD / camera callbacks (0x723f20, 0x721d10, unused) are not kept.
RpTeam* RpTeamCreate(uint32_t numOfPlayers, uint32_t numOfPlayerElements) {
    RpTeam* team = new RpTeam();
    team->lockFlags |= 0xff;
    team->numOfPlayerElements = numOfPlayerElements;
    team->numOfPlayers = numOfPlayers;
    team->players.resize(numOfPlayers);
    for (RpTeamPlayer& player : team->players) {
        player.team = team;
        player.elements.assign(numOfPlayerElements, -1);
    }
    RpTeamSetDictionary(team, nullptr);
    return team;
}

// 0x007223b0 RpTeamSetDictionary: the per-element counts for the new dictionary (and the lists' storage).
RpTeam* RpTeamSetDictionary(RpTeam* team, RpTeamDictionary* dictionary) {
    team->selected.clear();
    if (dictionary != nullptr) team->selected.assign(dictionary->numOfElements, 0);
    team->dictionary = dictionary;
    return team;
}

// 0x00723e80 RpTeamSetLODFarRange
void RpTeamSetLODFarRange(RpTeam* team, float farRange) {
    team->farRange = farRange;
    team->invFarRange = 5.0f / farRange;
}

// 0x00725fa0 _rpTeamPlayerDestroy_maybe (XXL2 _rpTeamPlayerDestroy): the hierarchy frame (a hierarchy: all of it; else its
// children one by one, then the frame), the element slots released while a dictionary is set, the matrix cache freed.
static void PlayerDestroy(RpTeamPlayer* player) {
    RwFrame* frame = player->frame;
    if (frame != nullptr) {
        if (frame->object.parent != nullptr) RwFrameRemoveChild(frame);  // RwFrameDestroy leaves the parent's child list
        if (RpHAnimFrameGetHierarchy(frame) == nullptr) {
            for (RwFrame* child = frame->child; child != nullptr;) {
                RwFrame* next = child->next;
                RwFrameDestroy(child);
                child = next;
            }
            RwFrameDestroy(frame);
        } else {
            RwFrameDestroyHierarchy(frame);
        }
    }
    if (player->team->dictionary != nullptr && player->team->numOfPlayerElements != 0) {
        player->elementFlags = 0;
        for (uint32_t slot = 0; slot < player->team->numOfPlayerElements; ++slot) PlayerSetElementIndex(player, slot, -1);
    }
    player->skinCache.clear();
    player->frame = nullptr;
}

// 0x00722aa0 RpTeamDestroy
void RpTeamDestroy(RpTeam* team) {
    if (team == nullptr) return;
    team->lockFlags |= 0xff;
    ClearRenderLists(team);
    for (uint32_t i = 0; i < team->numOfPlayers; ++i) PlayerDestroy(&team->players[i]);
    RpTeamSetDictionary(team, nullptr);
    delete team;
}

// 0x00721ff0 RpTeamUnlock
RpTeam* RpTeamUnlock(RpTeam* team) {
    if ((team->lockFlags & 6) != 0) UpdateLockedData(team, 0xff);
    // (lock bit 0x10: _rpTeamOptimizeCreate_maybe(team, 0, 0x10): nothing is selected by `which` 0.)
    team->lockFlags = 0;
    return team;
}

// 0x00721fa8 RpTeamSetPersistentLights
RpTeam* RpTeamSetPersistentLights(RpTeam* team, RpLight* first, RpLight* second) {
    team->lights[1] = first;
    team->lights[0] = second;
    team->lightType = 0;
    return team;
}

// 0x007260d8 RpTeamSetShadows
RpTeam* RpTeamSetShadows(RpTeam* team, RpTeamShadows* shadows) {
    team->shadows = shadows;
    return team;
}

uint32_t RpTeamDrawnAtomics() { return g_drawnAtomics; }

// 0x00722088 _rpTeamUpdateAndRender_maybe
void RpTeamRender(RpTeam* team, uint32_t flags) {
    if ((flags & 1) != 0) DOTD_STUB_ONCE("RpTeamRender: the LOD callbacks (flag 1, C2.9)");
    if ((flags & 2) != 0) {
        for (uint32_t i = 0; i < team->numOfPlayers; ++i) {
            RpTeamPlayer* player = &team->players[i];
            player->shadows = team->shadows;
            if ((player->flags & 1) == 0) {
                player->flags &= ~2u;
                player->playerClip = 0;
            } else {
                player->flags |= 2u;
                player->playerClip = (player->flags & 0x10) == 0 ? 1 : 3;
            }
        }
    }
    // flag 4: RpSkinPrepareAtomicMatrices_2_maybe for each drawn player with a skinned element (STUB(C2.9): none has one).
    if ((flags & 8) != 0) RenderPlayers(team);
}

// 0x00725ca8 RpTeamPlayerSetActivity
RpTeamPlayer* RpTeamPlayerSetActivity(RpTeamPlayer* player, int32_t active) {
    if (active == 0) {
        if ((player->flags & 1) == 0) return nullptr;
        player->flags &= ~1u;
    } else {
        if (active != 1 || (player->flags & 1) != 0) return nullptr;
        player->flags |= 1u;
    }
    RpTeam* team = player->team;
    uint32_t types = 0;
    for (uint32_t slot = 0; slot < team->numOfPlayerElements; ++slot) {
        const int32_t index = player->elements[slot];
        if (index == -1) continue;
        team->selected[static_cast<uint32_t>(index)] += active == 1 ? 1u : static_cast<uint32_t>(-1);
        types |= static_cast<uint32_t>(team->dictionary->elements[static_cast<uint32_t>(index)].type);
    }
    SetRenderListsDirty(team, types);
    return player;
}

// 0x00725f18 RpTeamPlayerSetElement
RpTeamPlayer* RpTeamPlayerSetElement(RpTeamPlayer* player, uint32_t slot, int32_t index) {
    if (slot == 0) player->elementFlags = 0;
    if (index != -1) {
        player->elementFlags |= static_cast<uint32_t>(player->team->dictionary->elements[static_cast<uint32_t>(index)].type);
    }
    PlayerSetElementIndex(player, slot, index);
    return player;
}

// 0x00725e58 RpTeamPlayerSetHierarchyFrame
RpTeamPlayer* RpTeamPlayerSetHierarchyFrame(RpTeamPlayer* player, RwFrame* frame) {
    if (player->frame != nullptr) {
        RwFrameDestroyHierarchy(player->frame);
        player->frame = nullptr;
        player->skinCache.clear();
    }
    if (frame != nullptr) {
        player->frame = frame;
        RpHAnimHierarchy* hierarchy = RpHAnimFrameGetHierarchy(frame);
        if (hierarchy != nullptr) PlayerAllocMatrices(player, hierarchy);
    }
    return player;
}

// 0x00726da8 RpTeamDictionaryStreamRead
RpTeamDictionary* RpTeamDictionaryStreamRead(RwStream* stream) {
    uint32_t length = 0, version = 0;
    if (RwStreamFindChunk(stream, kIdStruct, &length, &version) == 0) return nullptr;
    uint32_t header[2] = {};  // the element count, then a word this reader does not use
    if (!ReadBytes(stream, header, 8)) return nullptr;
    RpTeamDictionary* dictionary = RpTeamDictionaryCreate(header[0]);
    std::vector<uint32_t> masks(header[0]);
    if (!ReadBytes(stream, masks.data(), header[0] * 4u)) return dictionary;
    for (uint32_t element = 0; element < header[0]; ++element) {
        int32_t type = 0;
        if (!ReadBytes(stream, &type, 4)) return dictionary;
        for (uint32_t bit = 0; bit < 7; ++bit) {
            if ((masks[element] & (1u << bit)) == 0) continue;
            uint32_t atomicLength = 0;
            RwStreamFindChunk(stream, kIdAtomic, &atomicLength, &version);
            RpAtomic* atomic = RpAtomicStreamRead(stream);
            if (type != rpTEAMELEMENTSTATIC) {
                RpTeamDictionarySetElement(dictionary, atomic, static_cast<RpTeamElementType>(type), bit, element);
                RpAtomicDestroy(atomic);
                continue;
            }
            int32_t frameId = 0;
            ReadBytes(stream, &frameId, 4);  // the frame's RpHAnim id
            RwFrame* frame = RwFrameCreate();
            frame->hanimID = frameId;  // RpHAnimFrameSetID_maybe
            RpAtomicSetFrame(atomic, frame);
            RpTeamDictionarySetElement(dictionary, atomic, rpTEAMELEMENTSTATIC, bit, element);
            RpAtomicDestroy(atomic);
            RwFrameDestroy(frame);
        }
    }
    return dictionary;
}

// 0x00727740 RpTeamStreamRead
RpTeam* RpTeamStreamRead(RwStream* stream, RpTeamDictionary* dictionary) {
    uint32_t length = 0, version = 0;
    if (RwStreamFindChunk(stream, kIdStruct, &length, &version) == 0) return nullptr;
    int32_t counts[2] = {};  // the element count, the player count
    float reals[2] = {};     // the LOD far range, one more
    if (!ReadBytes(stream, counts, 8) || !ReadBytes(stream, reals, 8)) return nullptr;
    RpTeam* team = RpTeamCreate(static_cast<uint32_t>(counts[1]), static_cast<uint32_t>(counts[0]));
    RpTeamSetDictionary(team, dictionary);
    RpTeamSetLODFarRange(team, reals[0]);
    std::vector<int32_t> indices(team->numOfPlayerElements);
    for (uint32_t i = 0; i < team->numOfPlayers; ++i) {
        RpTeamPlayer* player = RpTeamGetPlayer(team, i);
        float sphere[4];
        uint32_t words[3];  // flags (1 active, 4 shadow), the LOD, the per-frame LOD sync
        if (!ReadBytes(stream, sphere, 16) || !ReadBytes(stream, words, 12)) return nullptr;
        std::memcpy(player->boundingSphere, sphere, sizeof sphere);
        if ((words[0] & 1) != 0) RpTeamPlayerSetActivity(player, 1);
        if ((words[0] & 4) != 0) RpTeamPlayerSetShadowFlag(player, 1);
        RpTeamPlayerSetLOD(player, words[1]);
        RpTeamPlayerSetSyncLODPerFrame(player, static_cast<int32_t>(words[2]));
        if (!ReadBytes(stream, indices.data(), static_cast<uint32_t>(indices.size()) * 4u)) return nullptr;
        for (uint32_t element = 0; element < team->numOfPlayerElements; ++element) {
            RpTeamPlayerSetElement(player, element, indices[element]);
        }
        RwStreamFindChunk(stream, kIdClump, &length, &version);
        RpClump* clump = RpClumpStreamRead(stream);
        if (clump == nullptr) return nullptr;
        // The hierarchy frame: the clump's root, or without a hierarchy there the first frame below it that has one.
        RwFrame* frame = clump->frame;
        RwFrame* found = nullptr;
        if (RpHAnimFrameGetHierarchy(frame) == nullptr) {
            ForAllChildren(frame, &found);
            if (found != nullptr) frame = found;
        }
        RpTeamPlayerSetHierarchyFrame(player, frame);
        RwFrameUpdateObjects(frame->root);
        clump->frame = nullptr;
        RpClumpDestroy(clump);
    }
    // The team texture records: five words {kind (1 team, 2 player, 3 dual), LOD, element, material, player} and a
    // texture chunk each, up to a record whose first word is 0.
    // STUB(C2.9): RpTeamMaterialSetTeamTexture / SetPlayerTexture / SetPlayerDualTexture (0x724500 ..). No level has a
    // record (the terminator follows the last player), so the chunks are only skipped.
    for (;;) {
        uint32_t record[5];
        if (!ReadBytes(stream, record, sizeof record) || record[0] == 0) break;
        DOTD_STUB_ONCE("RpTeamStreamRead: team texture records (C2.9)");
        uint32_t textureLength = 0;
        if (RwStreamFindChunk(stream, kIdTexture, &textureLength, &version) == 0 || RwStreamSkip(stream, textureLength) == nullptr) break;
    }
    return team;
}
