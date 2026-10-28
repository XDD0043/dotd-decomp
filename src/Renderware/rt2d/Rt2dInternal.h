// Rt2dInternal.h - state and helpers shared by the tool/2d ports (not part of the cross-unit API).
//
// Rt2dGlobalVars is RW 3.7's Rt2d globals block (gstate.h; names and order from XXL2's DWARF), at
// 0x00cfa3c0 in the PS3 build (TOC2 -0x399c and the other per-file TOC words). The PS3 offsets are in the
// comments; the struct is file-scope state here, so its host layout is not asserted. The PS3 block is
// XXL2's with 4-byte pointers, 32-bit vertex indices (RwImVertexIndex is a 32-bit word on the PS3: topo
// fills 0x400 bytes) and one PS3-only word at +0x1630 (a CTM override, see _rt2dCTMGetComposite).
#pragma once
#include <cstdint>
#include <cstring>

#include "Renderware/rt2d/Rt2d.h"
#include "Renderware/rwcore/RwIm3D.h"
#include "Renderware/rwcore/RwMatrix.h"
#include "Renderware/rwcore/RwSList.h"
#include "Renderware/rwcore/RwStream.h"
#include "crt/ppc_ops.h"

struct RwCamera;
struct RpGeometry;
struct RpMaterial;

struct Rt2dStrBuffer {
    RwInt32 space;         // +0x00
    RwChar* str;           // +0x04
    RwChar buffer[1024];   // +0x08
};

typedef Rt2dFont* (*Rt2dFontCallBackRead)(const RwChar* name);

struct Rt2dGlobalVars {
    RwImVertexIndex topo[256];          // +0x000 0, 1, 2, ... (Rt2dOpen)
    RwImVertexIndex fonttopo[384];      // +0x400 per glyph quad q: 4q, 4q+2, 4q+3, 4q, 4q+3, 4q+1 (_rt2dFontOpen)
    RwFreeList* brushFreeList;          // +0xa00 (0x78 entries)
    RwIm3DVertex* brushVertexCache;     // +0xa04 (0x2400 bytes: 256 vertices)
    RwFreeList* fontFreeList;           // +0xa08 (0x144 entries)
    RwChar* fontPath;                   // +0xa0c
    RwUInt32 fontPathSize;              // +0xa10
    RwFreeList* fontDictNodeFreeList;   // +0xa14 (0xc entries)
    _rt2dFontDictionaryNode* fontDictionary;  // +0xa18
    RwTexDictionary* fontTexDictionary;       // +0xa1c
    RwTexDictionary* currFontTexDictionary;   // +0xa20
    RwFreeList* pathFreeList;           // +0xa24 (0x1c entries)
    Rt2dPath* scratch;                  // +0xa28
    RwFreeList* objectFreeList;         // +0xa2c (0x110 entries)
    RwFreeList* fillFreeList;           // +0xa30
    RwFreeList* triVertFreeList;        // +0xa34 (8-byte entries)
    RwFreeList* triPolyFreeList;        // +0xa38 (0x14-byte entries)
    _rt2dTriIndex triVertIndex;         // +0xa3c
    RwMatrix metricMtx;                 // +0xa50
    RwMatrix* ctm[32];                  // +0xa90
    RwInt32 mtos;                       // +0xb10
    RwV2d vw;                           // +0xb14 the camera's view window x 2
    RwV2d vp;                           // +0xb1c the frame buffer's width and height
    RwMatrix CTM2d;                     // +0xb30
    RwMatrix iCTM2d;                    // +0xb70
    RwMatrix CTM;                       // +0xbb0
    RwBool CTMValid;                    // +0xbf0
    RwUInt32 TransformFlags;            // +0xbf4
    RwReal layerDepth;                  // +0xbf8
    RwReal tolerance;                   // +0xbfc
    RwReal sqTolerance;                 // +0xc00
    RwBool sqToleranceValid;            // +0xc04
    RwInt32 flatDepth;                  // +0xc08
    RwInt32 extensionOffset;            // +0xc0c
    RwReal deviceX;                     // +0xc10
    RwReal deviceY;                     // +0xc14
    RwReal deviceW;                     // +0xc18
    RwReal deviceH;                     // +0xc1c
    RwBool pixelSpace;                  // +0xc20
    RwCamera* viewCamera;               // +0xc24
    Rt2dBrush* brush;                   // +0xc28
    Rt2dFont* font;                     // +0xc2c
    Rt2dPath* path;                     // +0xc30
    RwChar* str;                        // +0xc34
    rt2dPathNode* pnode0;               // +0xc38
    rt2dPathNode* pnode1;               // +0xc3c
    RwReal pathInset;                   // +0xc40
    RwReal oobaseu;                     // +0xc44
    RwReal fontbaseu;                   // +0xc48
    Rt2dBBox bbox;                      // +0xc4c
    RwV2d delta;                        // +0xc5c
    RwInt32 numVerts;                   // +0xc64
    RwInt32 numBatches;                 // +0xc68
    Rt2dStrBuffer strBuffer;            // +0xd0c
    Rt2dFont* fontBatch;                // +0x1114
    Rt2dFontCallBackRead fontReadFunc;  // +0x1118 (Rt2dFontRead 0x70fa60; not ported: no font files are read)
    RwRGBA colorCache[64];              // +0x111c
    RwUInt32* triIdxCache;              // +0x121c
    RwUInt32 triIdxCacheSize;           // +0x1220
    RwChar filename[1024];              // +0x1224
    RwInt32* uCharIndex;                // +0x1624
    RwInt32 uCharIndexSize;             // +0x1628
    RwMatrix* overrideCTM;              // +0x1630 PS3 only: when set, _rt2dCTMGetComposite returns a copy of it
};

extern Rt2dGlobalVars rt2dGlobals;

// The RW engine's string functions (RWEngineInstance +0xcc strcpy, +0xe8 strcmp, +0xf4 strlen: the libc
// ones, case-sensitive).
inline RwChar* rwstrcpy(RwChar* dst, const RwChar* src) { return std::strcpy(dst, src); }
inline int rwstrcmp(const RwChar* a, const RwChar* b) { return std::strcmp(a, b); }
inline size_t rwstrlen(const RwChar* s) { return std::strlen(s); }

// 0x00757128 RwStreamReadInt32 / 0x00757200 RwStreamReadReal / 0x00757060 RwStreamReadInt16: RwStreamRead,
// then the little-endian words to native (a copy on a little-endian host). Null only when RwStreamRead
// returns 0 (a short read still succeeds).
inline RwStream* Rt2dStreamReadInt32(RwStream* stream, void* data, RwUInt32 size) {
    return RwStreamRead(stream, data, size) == 0 ? nullptr : stream;
}
inline RwStream* Rt2dStreamReadReal(RwStream* stream, void* data, RwUInt32 size) {
    return RwStreamRead(stream, data, size) == 0 ? nullptr : stream;
}
inline RwStream* Rt2dStreamReadInt16(RwStream* stream, void* data, RwUInt32 size) {
    return RwStreamRead(stream, data, size) == 0 ? nullptr : stream;
}

// --- file-local ports other files call -------------------------------------------------------------
// path.c
// 0x00715238 _rt2dFlattenBezier_maybe: flattens the cubic pts[0..3] into owner's segment list (line nodes).
void _rt2dFlattenBezier(Rt2dPath* owner, const RwV2d* pts, RwInt32 depth);
// 0x00715c78 _rt2dSubPathFlatten_maybe: appends src's flattened nodes to dst (locked); closes dst when src is.
Rt2dPath* _rt2dSubPathFlatten(Rt2dPath* dst, Rt2dPath* src);
// 0x00714df0 _rt2dSubPathAccumulateBBox_maybe: grows bbox {minx, miny, maxx, maxy} by the subpath's points.
RwReal* _rt2dSubPathAccumulateBBox(Rt2dPath* path, RwReal* bbox);
// 0x00716ab0 _rt2dGetEmptyScratchPath_maybe
Rt2dPath* _rt2dGetEmptyScratchPath();
// 0x00714f08 _rt2dPathRemoveDegenerateSubPaths_maybe
Rt2dPath* _rt2dPathRemoveDegenerateSubPaths(Rt2dPath* path);
// 0x007181f8 _rt2dSubPathStreamReadData_maybe (header: the 0x10-byte record already read)
Rt2dPath* _rt2dSubPathStreamReadData(Rt2dPath* path, const RwInt32* header, RwStream* stream);
// 0x00716e70 _rt2dSubPathDestroyChain_maybe
Rt2dPath* _rt2dSubPathDestroyChain(Rt2dPath* path);
// 0x00717930 _rt2dPathOpen_maybe / 0x00716d78 _rt2dPathClose_maybe
RwBool _rt2dPathOpen();
RwBool _rt2dPathClose();

// brush.c
// 0x0070aec0 _rt2dBrushOpen_maybe / 0x0070af58 _rt2dBrushClose_maybe
RwBool _rt2dBrushOpen();
RwBool _rt2dBrushClose();
// 0x0070b748 _rt2dShapeAddFillGeometry_maybe (the fill of one shape node into the shape rep's geometry)
Rt2dPath* _rt2dShapeAddFillGeometry(Rt2dPath* path, Rt2dBrush* brush, RpGeometry* geometry, RwUInt32* vertexBase,
                                    RwUInt32* triangleBase);

// font.c
// 0x0070f810 _rt2dFontOpen_maybe / 0x0070de08 _rt2dFontClose_maybe
RwBool _rt2dFontOpen();
RwBool _rt2dFontClose();

// object.c
// 0x00713ec0 _rt2dObjectOpen_maybe / 0x00713f20 _rt2dObjectClose_maybe
RwBool _rt2dObjectOpen();
RwBool _rt2dObjectClose();

// scene.c
// 0x00719cb8 _rt2dSceneInit_maybe
Rt2dObject* _rt2dSceneInit(Rt2dObject* scene, RwInt32 objectCount);
// 0x007195b0 DrawUIOrderedSceneChildren (_rt2dSceneRender: the scene's children by depth)
Rt2dObject* _rt2dSceneRender(Rt2dObject* scene, RwRGBAReal* colorMult, RwRGBAReal* colorOffs);

// shape.c
// 0x0071e3e8 Rt2d_CreateFreeLists_maybe (_rt2dTriangulateOpen) / 0x0071e490 Rt2d_DestroyFreeLists_maybe
RwBool _rt2dTriangulateOpen();
RwBool _rt2dTriangulateClose();
// 0x0071ef48 _rt2dShapeTriangulateFill_maybe: triangulates a closed subpath; *numTri, index triples in idx.
Rt2dPath* _rt2dShapeTriangulateFill(Rt2dPath* path, RwInt32* numTri, RwImVertexIndex* idx);
// The brush's shape material with a reference taken (created and cached in the brush when missing).
RpMaterial* _rt2dBrushGetMaterial(Rt2dBrush* brush);
// 0x0071b500 _rt2dShapeRepCreateGeometry_maybe
RpGeometry* _rt2dShapeRepCreateGeometry(_rt2dShapeRep* rep);
// 0x0071d790 _rt2dShapeAddStrokeGeometry_maybe
Rt2dPath* _rt2dShapeAddStrokeGeometry(Rt2dPath* path, Rt2dBrush* brush, RpGeometry* geometry, RwUInt32* vertexBase,
                                      RwUInt32* triangleBase);

// pickreg.c
// 0x00718a30 _rt2dPickRegionRender_maybe
Rt2dObject* _rt2dPickRegionRender(Rt2dObject* region);
// 0x00718c90 _rt2dPickRegionDestruct_maybe
RwBool _rt2dPickRegionDestruct(Rt2dObject* region);

// 2dstr.c
// 0x007099a0 _rt2dObjectStringDestruct_maybe
RwBool _rt2dObjectStringDestruct(Rt2dObject* string);
// 0x00709520 DrawUITextSceneObject (_rt2dObjectStringRender)
Rt2dObject* _rt2dObjectStringRender(Rt2dObject* string, RwRGBAReal* colorMult, RwRGBAReal* colorOffs);
