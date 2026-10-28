// RpTeam.h - the RenderWare Team plugin (a crowd of "players" that share a dictionary of elements), as the PS3
// library has it (TOC 0xc25974, 0x721aa8-0x72a000) and CCloneManager uses it. The layouts and names are XXL2's
// (DWARF: RwSrc/Graphics/rwsdk/plugin/team/*.h); the PS3 offsets are in the comments (32-bit pointers).
//
// The game's data has only what a static prop needs: every clone manager of the nine levels that have one (LVL010 ..
// LVL110) holds a dictionary of rpTEAMELEMENTSTATIC elements with their LOD 0 atomic only, players whose clump is two
// frames (no HAnim hierarchy), no team textures and no LOD requests (LOD 0 and no per-frame LOD sync). What those
// players need is ported: streams, dictionary, element selection, activity, the static render lists
// (_rpTeamOptimizeCreate = _rpTeamOptimizeCreate_maybe 0x7251e0) and the render (RpTeamRender 0x722088 with
// flags 2 | 4 | 8, _rpTeamRender = _rpTeamRenderPlayers_maybe 0x728988).
//
// STUB(C2.9), nothing in the data needs them: skinned elements (rpTEAMELEMENTSKINNED: the skin lists, the matrix cache
// pass RpSkinPrepareAtomicMatrices_2_maybe 0x728ea8 and their render), the LOD callbacks (flag 1 of RpTeamRender,
// RpTeamSetLODCallBack), team textures and player colours (RpTeamMaterial*), the shadow elements (LOD 5 / 6, the
// frustum test _rpTeamPlayerTestVisibility_maybe 0x7260f0 that nothing calls), RpTeamDictionaryInstance 0x723058 (its
// pipeline lookup KStub_Return0_728980 gives null, so it does nothing), the stream writers and size functions.
// The RW pipeline objects the original attaches to the element atomics (static / skin / MatFX / shadow pipelines of
// _rpTeamCreate*Pipeline 0x729138..0x7292c8, _rpTeamAtomicSet*Pipeline) are not modelled: every element atomic draws
// through RpAtomicPSGL_Render, the shader manager's pipeline.
#pragma once
#include <cstdint>
#include <vector>

#include "Renderware/rwcore/RwMatrix.h"
#include "Renderware/rwcore/RwTypes.h"

struct RwStream;
struct RwFrame;
struct RpAtomic;
struct RpLight;
struct RpHAnimHierarchy;

// RpTeamElementType (rpteam.h)
enum RpTeamElementType : int32_t {
    rpNATEAMELEMENTTYPE = 0,
    rpTEAMELEMENTSTATIC = 1,
    rpTEAMELEMENTSKINNED = 2,
    rpTEAMELEMENTPATCH = 4,
    rpTEAMELEMENTALL = 255,
};

// RpTeamElementLOD (RpTeam.h): the LOD slots of an element; 5 and 6 are the shadow atomics.
enum RpTeamElementLOD : int32_t {
    rpTEAMELEMENTLODFIRST = 0,
    rpTEAMELEMENTLODMAX = 5,
    rpTEAMELEMENTLODSHADOW1 = 5,
    rpTEAMELEMENTLODSHADOW4 = 6,
    rpTEAMELEMENTLODSUP = 7,
};

// RpTeamShadows (XXL2 DWARF): what CCloneManager keeps at +0x1c and hands to RpTeamSetShadows.
struct RpTeamShadows {
    RwFrame* shadowFrames[4];  // +0x00
    float shadowValues[4];     // +0x10
    RwFrame* shadowPlane;      // +0x20
    uint32_t number;           // +0x24
    uint32_t shadowLOD;        // +0x28 RpTeamElementLOD
};

struct RpTeam;

// RpTeamPlayer (0xf8 bytes on the PS3). The first 0xb0 bytes are RpTeamShadowRenderData (written only by the camera
// test _rpTeamPlayerTestVisibility_maybe, which nothing calls); +0xa0 renderNumShadows stays 0, so a player's shadow
// element is never drawn.
struct RpTeamPlayer {
    uint32_t renderNumShadows = 0;  // +0xa0 (RpTeamShadowRenderData)
    uint32_t shadowClip = 0;        // +0xa4
    uint32_t playerClip = 0;        // +0xa8 0: not drawn; 1 / 3: drawn (RpTeamRender sets it from the flags: 3 when bit 0x10)
    RpTeamShadows* shadows = nullptr;  // +0xac
    float boundingSphere[4] = {};   // +0xb0 RwSphere (centre, radius), read from the IKFile by CCloneManager_Load
    uint32_t flags = 0;             // +0xc0 1 active, 2 drawn this frame, 4 casts a shadow, 0x10 the sphere crosses the frustum
    uint32_t elementFlags = 0;      // +0xc4 the OR of the types of the player's elements
    uint32_t currentLOD = 0;        // +0xc8 RpTeamPlayerLOD
    int32_t syncLODPerFrame = 0;    // +0xcc
    RpTeam* team = nullptr;         // +0xd0
    std::vector<int32_t> elements;  // +0xd4 one dictionary element index per element slot, -1 for none
    RwFrame* frame = nullptr;       // +0xd8 the hierarchy frame (RpTeamPlayerGetHierarchyFrame)
    std::vector<RwMatrix> skinCache;  // +0xdc _rpTeamPlayerAllocMatrices: one matrix per hierarchy node (skinned elements)
    // +0xe8 / +0xec the render callbacks (PlayerCallBackData: before, after, data); null for every player here.
    int32_t (*preRender)(RpTeam* team, uint32_t player, RpAtomic* atomic, void* data) = nullptr;
    int32_t (*postRender)(RpTeam* team, uint32_t player, RpAtomic* atomic, void* data) = nullptr;
    void* callBackData = nullptr;   // +0xf0
    uint32_t unkF4 = 0;             // +0xf4 the frame stamp CClone_Enqueue writes and CCloneManager_UpdateAndExtract reads
};

// RpTeamDictionaryElement (0x24 bytes): the LOD atomics of one element.
struct RpTeamDictionaryElement {
    RpAtomic* lodAtomic[7];       // +0x00 TeamLODAtomic
    RpTeamElementType type;       // +0x1c
    uint32_t refCount;            // +0x20 the number of player slots that use the element
};

// RpTeamDictionary: the elements, and `map` (+0x08), the group an element's players are drawn in.
struct RpTeamDictionary {
    uint32_t numOfElements;                         // +0x00
    std::vector<RpTeamDictionaryElement> elements;  // +0x04 (allocated once: the groups keep their addresses)
    std::vector<uint32_t> map;                      // +0x08 numOfElements entries
};

// RpTeamRenderStatic: one player's draw of a static element: the matrix of the element's node (its hierarchy's, or the
// player frame's LTM), and the player.
struct RpTeamRenderStatic {
    const RwMatrix* matrices;     // +0x00 the hierarchy node's matrix; null when `frame` is the source
    RwFrame* frame;               // DOTD: the LTM source without a hierarchy (the PS3 keeps the address of the frame's LTM and
                                  // reads it as the RW sync left it; natively RwFrameGetLTM computes it on demand)
    RpTeamPlayer* player;         // +0x04
};

// RpTeamOptElement: the players that draw one dictionary element, as `numClones` (capacity) entries, `stack` of them used.
struct RpTeamOptElement {
    uint32_t numClones;           // +0x00 the number of active players using the element
    uint32_t stack;               // +0x04 entries filled
    RpTeamDictionaryElement* lodAtomic;  // +0x08 the element
    std::vector<RpTeamRenderStatic> render;  // +0x0c
};

struct RpTeamOptStatic {
    int32_t optimized;            // +0x1c (team) the lists are valid
    uint32_t numElements;         // +0x20 the groups
    std::vector<RpTeamOptElement> data;  // +0x24
};

struct RpTeam {
    uint32_t lockFlags;           // +0x08 RpTeamLock ORs, RpTeamUnlock clears
    uint32_t numOfPlayerElements; // +0x0c RpTeamPlayerData
    uint32_t numOfPlayers;        // +0x10
    int32_t optimized;            // +0x18 RpTeamOptElements.optimized: the lists and the skin matrices are valid
    RpTeamOptStatic stat;         // +0x1c
    int32_t skinOptimized;        // +0x28 the skinned lists are valid (STUB(C2.9): none is ever built)
    int32_t patchOptimized;       // +0x38
    float farRange;               // +0x40 RpTeamLOD
    float invFarRange;            // +0x44
    RpTeamDictionary* dictionary; // +0x50
    std::vector<uint32_t> selected;  // +0x54 per dictionary element, the active players that use it
    std::vector<RpTeamPlayer> players;  // +0x58 allocated once by RpTeamCreate: the players' addresses are stable
    RpTeamShadows* shadows;       // +0x5c
    RpLight* lights[6];           // +0x68 RpTeamSetPersistentLights: [0] the second light given, [1] the first
    int32_t lightType;            // +0x80 rpTEAMAMBIENTDIRECTIONLIGHTING 0
};

// 0x00726da8 RpTeamDictionaryStreamRead (0x726aa8 is the same code), after RwStreamFindChunk(0x22): the struct chunk, the
// element count, a bit mask of the LODs per element, then per element its type and one atomic chunk per set bit (a frame id
// after each when the type is static); every atomic goes into the dictionary through RpTeamDictionarySetElement.
RpTeamDictionary* RpTeamDictionaryStreamRead(RwStream* stream);
// 0x00727740 RpTeamStreamRead (0x727240 is the same code), after RwStreamFindChunk(0x1c): the struct chunk, the element and
// player counts (RpTeamCreate(players, elements)), the far range, then per player its sphere, flags / LOD / sync, element
// indices and clump (the hierarchy frame), then the team texture records (STUB(C2.9): skipped).
RpTeam* RpTeamStreamRead(RwStream* stream, RpTeamDictionary* dictionary);

// 0x00722830 RpTeamCreate
RpTeam* RpTeamCreate(uint32_t numOfPlayers, uint32_t numOfPlayerElements);
// 0x00722aa0 RpTeamDestroy
void RpTeamDestroy(RpTeam* team);
// 0x007223b0 RpTeamSetDictionary
RpTeam* RpTeamSetDictionary(RpTeam* team, RpTeamDictionary* dictionary);
// 0x00723e80 RpTeamSetLODFarRange
void RpTeamSetLODFarRange(RpTeam* team, float farRange);
inline uint32_t RpTeamGetNumberOfPlayers(const RpTeam* team) { return team->numOfPlayers; }      // 0x00721f08
inline RpTeamDictionary* RpTeamGetDictionary(RpTeam* team) { return team->dictionary; }          // 0x00721f10
inline uint32_t RpTeamGetNumberOfElements(const RpTeam* team) { return team->numOfPlayerElements; }  // 0x00721f50
// 0x00721f18 RpTeamGetPlayer
inline RpTeamPlayer* RpTeamGetPlayer(RpTeam* team, uint32_t index) { return &team->players[index]; }
// 0x00721f38 RpTeamLock: the flags ORed into the lock word.
inline RpTeam* RpTeamLock(RpTeam* team, uint32_t flags) {
    team->lockFlags |= flags;
    return team;
}
// 0x00721ff0 RpTeamUnlock: with bits 1 or 2 locked (RpTeamLock(2) is what CCloneManager_UpdateAndExtract does) the render lists
// are rebuilt (_rpTeamOptimizeCreate_maybe), then the lock word is cleared.
RpTeam* RpTeamUnlock(RpTeam* team);
// 0x00721fa8 RpTeamSetPersistentLights: the first light is stored at team +0x6c, the second at +0x68, and +0x80 cleared.
RpTeam* RpTeamSetPersistentLights(RpTeam* team, RpLight* first, RpLight* second);
// 0x007260d8 RpTeamSetShadows
RpTeam* RpTeamSetShadows(RpTeam* team, RpTeamShadows* shadows);

// DEV (not in the original): the number of element atomics RenderPlayerAtomic (0x722540) has sent through the pipeline since the
// start; newgame_test checks that a shown clone is drawn.
uint32_t RpTeamDrawnAtomics();

// 0x00722088 _rpTeamUpdateAndRender_maybe (XXL2 RpTeamRender): the passes the flags select: 1 the LOD callbacks (STUB(C2.9):
// the game never asks), 2 each player's clip state, 4 the skin matrix caches (STUB(C2.9): no skinned element), 8 the draw.
void RpTeamRender(RpTeam* team, uint32_t flags);

// 0x00725ca8 RpTeamPlayerSetActivity: 0 / 1 switches the player's elements out of / into the render lists (the active counts
// of the dictionary elements move, the lists are marked dirty). Null when the activity does not change or is not 0 / 1.
RpTeamPlayer* RpTeamPlayerSetActivity(RpTeamPlayer* player, int32_t active);
// 0x00725f18 RpTeamPlayerSetElement: element slot `slot` takes dictionary element `index` (-1: none).
RpTeamPlayer* RpTeamPlayerSetElement(RpTeamPlayer* player, uint32_t slot, int32_t index);
// 0x00725e58 RpTeamPlayerSetHierarchyFrame: the old frame destroyed (RwFrameDestroyHierarchy), the new one set; a frame with
// an RpHAnim hierarchy also gets the player's matrix cache.
RpTeamPlayer* RpTeamPlayerSetHierarchyFrame(RpTeamPlayer* player, RwFrame* frame);
// 0x00725c60 RpTeamPlayerSetShadowFlag
inline RpTeamPlayer* RpTeamPlayerSetShadowFlag(RpTeamPlayer* player, int32_t shadow) {
    player->flags = shadow != 0 ? (player->flags | 4u) : (player->flags & ~4u);
    return player;
}
inline RpTeamPlayer* RpTeamPlayerSetLOD(RpTeamPlayer* player, uint32_t lod) {  // 0x00723ee8
    player->currentLOD = lod;
    return player;
}
inline RpTeamPlayer* RpTeamPlayerSetSyncLODPerFrame(RpTeamPlayer* player, int32_t sync) {  // 0x00723f00
    player->syncLODPerFrame = sync;
    return player;
}
inline float* RpTeamPlayerGetBoundingSphere(RpTeamPlayer* player) { return player->boundingSphere; }  // 0x00725c50
inline RwFrame* RpTeamPlayerGetHierarchyFrame(RpTeamPlayer* player) { return player->frame; }         // 0x00725be0

// 0x00722ca0 RpTeamDictionaryCreate: `numOfElements` empty elements.
RpTeamDictionary* RpTeamDictionaryCreate(uint32_t numOfElements);
// 0x00723250 RpTeamDictionarySetElement: the old LOD atomic of the slot destroyed, `atomic` cloned into it (the clone's render
// callback cleared); a static element's clone gets a frame of its own carrying the source frame's HAnim id.
RpTeamDictionary* RpTeamDictionarySetElement(RpTeamDictionary* dictionary, RpAtomic* atomic, RpTeamElementType type, uint32_t lod,
                                             uint32_t element);
// 0x00723038 RpTeamDictionaryGetElement (the first LOD's atomic) / 0x00722bc0 RpTeamDictionaryGetLODElement.
RpAtomic* RpTeamDictionaryGetElement(RpTeamDictionary* dictionary, uint32_t element);
RpAtomic* RpTeamDictionaryGetLODElement(RpTeamDictionary* dictionary, uint32_t element, uint32_t lod);
inline uint32_t RpTeamDictionaryGetNumberOfElements(const RpTeamDictionary* dictionary) { return dictionary->numOfElements; }  // 0x722bb8
// 0x00723aa0 RpTeamDictionaryDestroy: every element's atomics (and a static element's frames) destroyed.
void RpTeamDictionaryDestroy(RpTeamDictionary* dictionary);
