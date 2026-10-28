// Rt2d.h - the Rt2d (RenderWare 3.7 2D toolkit) objects the 2D classes stream in (C1.3 shim).
//
// STUB(C1.4): the Rt2d objects themselves (brush colours and UVs, fonts, paths, Maestro movies). Here the
// readers consume exactly what the PS3 readers consume and keep the bytes for C1.4:
//   - a brush is a fixed 0x70-byte record (0x0070b5b0 Rt2dBrushStreamRead_maybe), not its chunk: the
//     0x1a2 chunk lengths in the files are 0xc larger than what the reader reads (LVL000: length 0x7c,
//     record 0x70), so the chunk cannot be kept whole as a blob;
//   - a font is read field by field (0x0070df88 Rt2dFontStreamRead) and is longer than its 0x199 chunk
//     (00GLC's "TrcFont": length 0x1186, 0x1df80 bytes read): the shim walks the same fields and keeps
//     the bytes it read;
//   - a Maestro movie (0x006fdc60 Rt2dMaestroStreamRead) reads past its 0x1b1 chunk (LVL000's first
//     CKFlashUI: length 0x3965, 0x3f89 bytes read): the shim ports the whole read path, see below;
//   - images (0x18) are kept as their chunk (RwShim_Blob).
#pragma once
#include <cstdint>
#include <memory>
#include <vector>

struct RwShim_Blob;
struct RwStream;

// RW 3.7 Rt2dShimBrush as far as the loaders need it.
struct Rt2dShimBrush {
    // The stream record as read (little-endian words; the PS3 swaps it with RwMemNative32): word 0 the
    // record version (1), +0x04..+0x63 the corner colours and UVs (_rt2dBrushStreamReadData_maybe
    // 0x70a940), +0x64 flags, +0x68 a float, +0x6c the "texture follows" flag.
    uint8_t record[0x70];
    RwShim_Blob* streamedTexture;  // the type-6 texture chunk when the record says one follows (RwTextureStreamRead)
    void* texture;                 // PS3 brush +0x68: the brush texture (RwTexture*), set by the caller's texture reference
};

// RwShim_Rt2dBrushCreate (Rt2dBrushCreate, library; TocBridge 0x98d900): an empty brush. STUB(C1.4): RW's default colours.
Rt2dShimBrush* RwShim_Rt2dBrushCreate();

// 0x0070b5b0 Rt2dBrushStreamRead_maybe, as far as the stream goes: Rt2dBrushCreate, RwStreamRead of the
// 0x70-byte record; with version 1 and the texture flag, RwStreamFindChunk(6) and the texture chunk. The
// original's failure paths (short read, other version, missing texture chunk) destroy the brush and still
// return it; the shim returns the brush in every case.
Rt2dShimBrush* RwShim_Rt2dBrushStreamRead(RwStream* stream);

// 0x0070df88 Rt2dFontStreamRead, as far as the stream goes (after the caller's RwStreamFindChunk(0x199)):
// a version word (its most significant byte 0: null), the font type (0 bitmap, else outline), three
// reals, three words (the third the glyph count), a u16 table of the size the next word gives, the
// 128-entry u16 character map, then per glyph: bitmap fonts 0x10 + 4 + 1 bytes, followed by a texture
// count and a 0x20-byte name per texture (RwTextureRead by name, no stream data); outline fonts three
// words and a fourth, with an Rt2dShimPath (0x1a1 chunk) when the glyph kind is 5. A short read ends it with
// null (the original destroys the font). The result's bytes are the ones read (type 0x199).
// STUB(C1.4): the outline glyph paths (Rt2dPathStreamRead) are kept as their 0x1a1 chunk.
RwShim_Blob* RwShim_Rt2dFontStreamRead(RwStream* stream);

// ---------------------------------------------------------------------------------------------------
// Maestro movies (RW 3.7 rt2d maestro, as the PS3 library reads them). Names from XXL2's RW 3.7 build
// (the same Rt2d code): Rt2dShimMaestro, Rt2dShimObject, _rt2dScene, _rt2dShape(Rep), Rt2dShimStringLabel,
// Rt2dShimButton, Rt2dShimMessage, Rt2dShimAnimNode, Rt2dShimCel(List), Rt2dAnim, Rt2dShimKeyFrameList, Rt2dShimAnimObjectUpdate.
// The shim structs keep what the readers read (words as the PS3 holds them after RwMemNative32), with the
// PS3 offsets in comments; nothing is rendered. STUB(C1.4): geometry (_rt2dShapeRepCreateGeometry, the
// shape atomics and frames), depth sorting, the string-bucket layout, the font lookup by name, the
// anim-node scene resolution and frame-state lists, the post-read pass (_rt2dMaestroInitAnimNodePostRead
// 0x6fcea8), matrix orthonormalisation and the compact keyframe arrays.

// RwMatrix as RwMatrixStreamRead (0x007572e0) fills it: right +0x00, flags +0x0c (stream word 12 & 3),
// up +0x10, at +0x20, pos +0x30.
struct Rt2dShimMatrix {
    float right[3];
    uint32_t flags;
    float up[3];
    uint32_t pad1;
    float at[3];
    uint32_t pad2;
    float pos[3];
    uint32_t pad3;
};

// An Rt2dShimPath (sub)path (_rt2dSubPathStreamReadData 0x007181f8): the 0x10-byte header {version 1,
// numPoints, flags (bit 0 closed, bit 1 flat, bit 2 another subpath follows in a 0x1a1 chunk), word 3},
// then numPoints 0x18-byte points (RwMemLittleEndian32 words).
struct Rt2dShimPath {
    int32_t numPoints = 0;           // PS3 +0x04
    uint32_t closed = 0;             // PS3 +0x08 (header flags bit 0)
    uint32_t flat = 0;               // PS3 +0x0c (header flags bit 1)
    int32_t unk10 = 0;               // PS3 +0x10 (header word 3)
    std::vector<uint8_t> points;     // PS3 +0x00 (numPoints * 0x18 bytes)
    std::unique_ptr<Rt2dShimPath> next;  // PS3 +0x14 the next subpath
};

// A shape node (0xc on the PS3): the node flag and, when the stream flag has bit 2, a path and a brush.
struct Rt2dShimShapeNode {
    uint32_t flag = 0;               // +0x00 a second word, read only when the stream flag has bit 2
    std::unique_ptr<Rt2dShimPath> path;  // +0x04
    Rt2dShimBrush* brush = nullptr;      // +0x08
};

// _rt2dShapeRep (PS3 0xc): nodes (RwSList of 0xc), refCount, geometry (STUB(C1.4)).
struct Rt2dShimShapeRep {
    int32_t streamWord0 = 0;          // the first header word (read into a local by the PS3)
    std::vector<Rt2dShimShapeNode> nodes; // +0x00
    uint32_t refCount = 1;            // +0x04
};

// Rt2dShimObject (PS3 0x110: type +0x00, depth +0x04, flag +0x08, MTM +0x10, LTM +0x50, colorMult +0x90,
// colorOffs +0xa0, data +0xb0), with the data of each type.
struct Rt2dShimObject {
    int32_t type = 0;      // 1 scene, 2 shape, 3 pick region, 4 object string
    int32_t depth = 0;
    uint32_t flag = 0;     // 6 after _rt2dObjectBaseStreamRead
    int32_t streamWord0 = 0;  // the base record's first word (read into a local by the PS3)
    Rt2dShimMatrix MTM{};
    float colorMult[4] = {};
    float colorOffs[4] = {};
    // scene (_rt2dScene at +0xb0): objects +0xb0 (RwSList of 0x110), objectCount +0xb4
    std::vector<Rt2dShimObject> objects;
    // shape (_rt2dShape at +0xb0): rep +0xb0, the scene's shared rep by index (or one read inline)
    std::shared_ptr<Rt2dShimShapeRep> rep;
    int32_t repIndex = -1;
    // pick region: the path at +0xb0
    std::unique_ptr<Rt2dShimPath> pickPath;
    // object string: text +0xb0 (2-byte characters; byte length +0xb8), brush +0xb4, height +0xbc,
    // font +0xc0 (_rt2dFontDictionaryFindEntry by name: STUB(C1.4))
    std::vector<uint8_t> text;      // the textLength + 1 bytes read, then two zero bytes
    std::vector<uint8_t> fontName;  // fontNameLength + 1 bytes (none when the length is 0)
    Rt2dShimBrush* stringBrush = nullptr;
    int32_t heightRaw = 0;          // +0xbc the second word read (stored once the brush read succeeds)
};

// Rt2dShimStringLabel (PS3 0x10).
struct Rt2dShimStringLabel {
    uint32_t entityType = 0;  // +0x00
    int32_t nameIndex = -1;   // +0x04 the name's index in the maestro string bucket (+0x1c)
    int32_t internalData = 0; // +0x08
    int32_t userData = 0;     // +0x0c (not read)
};

// Rt2dShimButton (PS3 0x90).
struct Rt2dShimButton {
    int32_t strLabelIndex = -1;  // +0x00
    int32_t objectIndex = -1;    // +0x04
    uint32_t stateFlag = 0;      // +0x08
    uint32_t buttonState = 0;    // +0x0c (not read)
    int32_t actionListForStateTransition[32];  // +0x10: -1, then the list header's word-2 count read
};

// Rt2dShimMessage (PS3 0x10).
struct Rt2dShimMessage {
    uint32_t messageType = 0;
    int32_t index = -1;
    int32_t intParam1 = 0;
    int32_t intParam2 = 0;
};

// Rt2dShimCel (PS3 0x10; Ghidra "Rt2dAnimNodeGroup") and Rt2dShimCelList (PS3 8; "Rt2dAnimNodeGroupList").
struct Rt2dShimCel {
    int32_t strLabelIndex = -1;          // +0x00
    int32_t celIndex = -1;               // +0x04
    std::vector<int32_t> buttonIndices;  // +0x08
    int32_t messageListIndex = -1;       // +0x0c
};
struct Rt2dShimCelList {
    std::vector<Rt2dShimCel> cel;  // +0x00
    uint32_t flag = 0;         // +0x04
};

// Rt2dShimAnimObjectUpdate (PS3 0xa0): one object's keyframe in a frame state.
struct Rt2dShimAnimObjectUpdate {
    uint32_t streamFlag = 0;  // the record's flag word (bit 0 transform, 1 colorOffs, 2 colorMult, 3 show,
                              // 4 morph; kept in a register by the PS3)
    int32_t objectIdx = 0;    // +0x04
    uint32_t hasTransform = 0;      // +0x08
    Rt2dShimMatrix transform{};     // +0x10
    uint32_t hasColorOffs = 0;      // +0x50
    float colorOffs[4] = {};        // +0x54
    uint32_t hasColorMult = 0;      // +0x64
    float colorMult[4] = {};        // +0x68
    uint32_t hasShow = 0;           // +0x78
    int32_t show = 0;               // +0x7c (stream word != 0)
    int32_t showWord1 = 0;          // +0x80
    uint32_t hasMorph = 0;          // +0x8c
    uint32_t morph[4] = {};         // +0x90
};

// A keyframe list: its time and its frame state (chunk 0x1b0, 0x006face8 Rt2dAnimFrameState_StreamRead).
struct Rt2dShimKeyFrameList {
    float time = 0;           // +0x00
    int32_t stateWord0 = 0;   // the frame-state header's first word (read into a local by the PS3)
    float stateTime = 0;      // frame state +0x00 (header word 1)
    std::vector<Rt2dShimAnimObjectUpdate> updates;  // header word 2 entries
};

// Rt2dShimAnimNode (PS3 0x3c): flag +0x00 (2), anim +0x04, props +0x20, celList +0x30, parent +0x34,
// posInParentScene +0x38.
struct Rt2dShimAnimNode {
    int32_t flag = 2;
    std::vector<Rt2dShimKeyFrameList> keyframeLists;  // anim +0x04 (Rt2dAnim keyframeLists)
    Rt2dShimCelList celList;
    int32_t parent = -1;
    int32_t posInParentScene = -1;
    uint32_t chunkType = 0, chunkLength = 0, chunkVersion = 0;  // what RwStreamReadChunkHeaderInfo reads
};

// Rt2dShimMaestro (PS3 0x301b1 object): animations +0x08, labels +0x0c, buttons +0x10, messageStore +0x14,
// messageList +0x18, the string bucket +0x1c, scene +0x24, currAnimIndex +0x44, bbox +0x48.
struct Rt2dShimMaestro {
    int32_t streamVersion = 0;        // the first word (read into a local by the PS3)
    float bbox[4] = {};
    std::vector<Rt2dShimStringLabel> labels;
    std::vector<char> stringBucket;
    std::unique_ptr<Rt2dShimObject> scene;
    int32_t buttonListWord1 = 0;      // the button list header's second word (passed on, unused)
    int32_t buttonTransitionCount = 0; // its third word: the words each button's action list reads
    std::vector<Rt2dShimButton> buttons;
    std::vector<int32_t> messageList;
    std::vector<Rt2dShimMessage> messageStore;
    std::vector<Rt2dShimAnimNode> animations;
    int32_t currAnimIndex = -1;       // +0x44, -1 after the read
};

// 0x006fdc60 Rt2dMaestroStreamRead (after the caller's RwStreamFindChunk(0x1b1)) and the readers it
// calls: the version word, the bbox (RwStreamReadReal 0x10), _rt2dMaestroStringLabelsStreamRead
// (0x701410), the scene count and, when positive, RwStreamFindChunk(0x1a5) + Rt2dSceneStreamRead
// (0x71acc0), _rt2dMaestroButtonsStreamRead (0x7021f8), _rt2dMaestroMessageListStreamRead (0x6ffd68),
// _rt2dMaestroMessageStoreStreamRead (0x6ffc08), _rt2dMaestroAnimationsStreamRead (0x6fcc20). Null when
// a reader fails (the stream stays where that reader stopped), like the original.
Rt2dShimMaestro* RwShim_Rt2dMaestroStreamRead(Rt2dShimMaestro* maestro, RwStream* stream);
