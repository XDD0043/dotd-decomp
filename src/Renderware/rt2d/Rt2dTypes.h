// Rt2dTypes.h - the RenderWare 3.7 2D toolkit (Rt2d, tool/2d) and its animation layer (Rt2dAnim and
// Maestro, tool/2danim) data structures, in the PS3 build's layout.
//
// Names, member order and types from XXL2's RW 3.7 build (the same Rt2d code; DWARF records in
// work/xxl2-dwarf/classes.jsonl). The PS3 offsets follow from 4-byte pointers and a 16-byte-aligned
// RwMatrix, and are checked against the PS3 code where it touches them (DOTD_ASSERT_*, 32-bit builds).
// RW's own struct names keep their RW spelling (_rt2dScene, Rt2dAnimNode, ...), as in the SDK.
#pragma once
#include <cstdint>

#include "Renderware/rwcore/RwTypes.h"

struct Rt2dObject;
struct Rt2dPath;
struct Rt2dBrush;
struct Rt2dFont;
struct Rt2dMaestro;
struct Rt2dMessage;
struct Rt2dKeyFrameList;
struct RpGeometry;
struct RpAtomic;
struct RpMaterial;

// --- tool/2d -----------------------------------------------------------------------------------------

// Rt2dObjectTypeEnum
enum Rt2dObjectTypeEnum : RwInt32 {
    rt2DOBJECTTYPEOBJECT = 0,
    rt2DOBJECTTYPESCENE = 1,
    rt2DOBJECTTYPESHAPE = 2,
    rt2DOBJECTTYPEPICKREGION = 3,
    rt2DOBJECTTYPEOBJECTSTRING = 4,
};

// Rt2dObject flags (object.c): rt2dOBJECTVISIBLE etc. The bit meanings are documented where the ports use
// them; _rt2dObjectBaseStreamReadTo leaves 6.

enum Rt2dJustificationType : RwInt32 {
    rt2dJUSTIFYLEFT = 0,
    rt2dJUSTIFYCENTER = 1,
    rt2dJUSTIFYRIGHT = 2,
};

// rt2dLinetype (path.c)
enum rt2dLinetype : RwInt32 {
    rt2dMOVE = 0,
    rt2dLINE = 1,
    rt2dCURVE = 2,
};

struct Rt2dBBox {
    RwReal x;
    RwReal y;
    RwReal w;
    RwReal h;
};
DOTD_ASSERT_SIZE(Rt2dBBox, 0x10);

// rt2dShadeParameters (brush.c): one corner's colour and UV.
struct rt2dShadeParameters {
    RwRGBAReal col;  // +0x00
    RwV2d uv;        // +0x10
};
DOTD_ASSERT_SIZE(rt2dShadeParameters, 0x18);

// Rt2dBrush (brush.c; PS3 0x78).
struct Rt2dBrush {
    rt2dShadeParameters top;      // +0x00
    rt2dShadeParameters dtop;     // +0x18
    rt2dShadeParameters bottom;   // +0x30
    rt2dShadeParameters dbottom;  // +0x48
    RwRGBA colorCache;            // +0x60
    RwInt32 flag;                 // +0x64
    RwTexture* texture;           // +0x68
    RpMaterial* material;         // +0x6c
    RwReal halfwidth;             // +0x70
    RwInt32 refCount;             // +0x74
};
DOTD_ASSERT_SIZE(Rt2dBrush, 0x78);
DOTD_ASSERT_OFFSET(Rt2dBrush, texture, 0x68);

// _rt2dStreamBrush: the brush's stream record (0x70; read as words, RwMemNative32).
struct _rt2dStreamBrush {
    RwUInt32 version;              // +0x00 (1)
    rt2dShadeParameters top;       // +0x04
    rt2dShadeParameters dtop;      // +0x1c
    rt2dShadeParameters bottom;    // +0x34
    rt2dShadeParameters dbottom;   // +0x4c
    RwUInt32 flag;                 // +0x64
    RwReal halfwidth;              // +0x68
    RwBool gotTexture;             // +0x6c
};
DOTD_ASSERT_SIZE(_rt2dStreamBrush, 0x70);

// rt2dPathNode (path.c; PS3 0x18): one point of a (sub)path.
struct rt2dPathNode {
    rt2dLinetype type;  // +0x00
    RwV2d pos;          // +0x04
    RwV2d normal;       // +0x0c
    RwReal dist;        // +0x14
};
DOTD_ASSERT_SIZE(rt2dPathNode, 0x18);

// Rt2dPath (path.c; PS3 0x1c). segments: the rt2dPathNode array (an RwSList while unlocked: see path.c).
struct Rt2dPath {
    void* segments;     // +0x00
    RwInt32 numSegment; // +0x04
    RwBool closed;      // +0x08
    RwBool flat;        // +0x0c
    RwReal inset;       // +0x10
    Rt2dPath* next;     // +0x14
    Rt2dPath* curr;     // +0x18
};
DOTD_ASSERT_SIZE(Rt2dPath, 0x1c);

// _rt2dShapeNode (shape.c; PS3 0xc).
struct _rt2dShapeNode {
    RwUInt32 flag;     // +0x00
    Rt2dPath* path;    // +0x04
    Rt2dBrush* brush;  // +0x08
};
DOTD_ASSERT_SIZE(_rt2dShapeNode, 0xc);

// _rt2dShapeRep (shape.c; PS3 0xc): a shape's nodes, shared between shapes by reference count.
struct _rt2dShapeRep {
    RwSList* nodes;        // +0x00 (_rt2dShapeNode)
    RwUInt32 refCount;     // +0x04
    RpGeometry* geometry;  // +0x08
};
DOTD_ASSERT_SIZE(_rt2dShapeRep, 0xc);

// _rt2dSceneResourcePool (scene.c): the shape reps a scene stream carries before its children.
struct _rt2dSceneResourcePool {
    _rt2dShapeRep** shapeReps;  // +0x00
    RwUInt32 numShapeReps;      // +0x04
};
DOTD_ASSERT_SIZE(_rt2dSceneResourcePool, 0x8);

// _rt2dPathMeshNode / _rt2dPathMeshHeader (shape.c geometry).
struct _rt2dPathMeshNode {
    Rt2dPath* path;    // +0x00
    RwUInt32 numTri;   // +0x04
    RwUInt32 numVert;  // +0x08
    RwUInt32 numIdx;   // +0x0c
    RwUInt32 flag;     // +0x10
    Rt2dBrush* brush;  // +0x14
};
DOTD_ASSERT_SIZE(_rt2dPathMeshNode, 0x18);

struct _rt2dPathMeshHeader {
    _rt2dPathMeshNode* node;  // +0x00
    RwUInt32 numNode;         // +0x04
    RwUInt32 numTri;          // +0x08
    RwUInt32 numVert;         // +0x0c
    RwUInt32 numIdx;          // +0x10
};
DOTD_ASSERT_SIZE(_rt2dPathMeshHeader, 0x14);

// Triangulation (tri.c).
struct _rt2dTriIndex {
    RwInt32 currIdx;  // +0x00
    RwInt32* idx;     // +0x04
};
DOTD_ASSERT_SIZE(_rt2dTriIndex, 0x8);

struct _rt2dTriVert {
    _rt2dTriVert* next;  // +0x00
    RwInt32 idx;         // +0x04
};
DOTD_ASSERT_SIZE(_rt2dTriVert, 0x8);

struct _rt2dTriPoly {
    _rt2dTriPoly* next;        // +0x00
    _rt2dTriVert* vert;        // +0x04
    _rt2dTriIndex* triIndex;   // +0x08
    RwInt32 vCount;            // +0x0c
    RwV2d* pos;                // +0x10
};
DOTD_ASSERT_SIZE(_rt2dTriPoly, 0x14);

// Object data by type (_rt2dObjectdata union; PS3 0x60, the pick region being the largest).
struct _rt2dScene {
    RwSList* objects;      // +0x00 (Rt2dObject, stored by value)
    RwInt32 objectCount;   // +0x04
    RwSList* depths;       // +0x08 (_rt2dDepthOfObject)
    RwBool isDirtyDepths;  // +0x0c
};
DOTD_ASSERT_SIZE(_rt2dScene, 0x10);

struct _rt2dShape {
    _rt2dShapeRep* rep;   // +0x00
    RwRGBA* colorCache;   // +0x04
    RpAtomic* atomic;     // +0x08
};
DOTD_ASSERT_SIZE(_rt2dShape, 0xc);

struct alignas(16) _rt2dPickRegion {
    Rt2dPath* path;            // +0x00
    Rt2dBBox bbox;             // +0x04
    RwMatrix transformation;   // +0x20
};
DOTD_ASSERT_SIZE(_rt2dPickRegion, 0x60);

// _rt2dFontDictionaryNode (font.c): the named-font list.
struct _rt2dFontDictionaryNode {
    RwChar* name;                   // +0x00
    Rt2dFont* font;                 // +0x04
    _rt2dFontDictionaryNode* next;  // +0x08
};
DOTD_ASSERT_SIZE(_rt2dFontDictionaryNode, 0xc);

struct _rt2dObjectString {
    RwChar* textString;               // +0x00 (2-byte characters on the PS3 build: Rt2dFontChar)
    Rt2dBrush* brush;                 // +0x04
    RwInt32 maxLength;                // +0x08
    RwReal height;                    // +0x0c
    _rt2dFontDictionaryNode* font;    // +0x10
    Rt2dJustificationType justiftype; // +0x14
    RwReal boxwidth;                  // +0x18
};
DOTD_ASSERT_SIZE(_rt2dObjectString, 0x1c);

union alignas(16) _rt2dObjectdata {
    _rt2dScene scene;
    _rt2dShape shape;
    _rt2dPickRegion pickRegion;
    _rt2dObjectString objectString;
};
DOTD_ASSERT_SIZE(_rt2dObjectdata, 0x60);

// Rt2dObject (object.c; PS3 0x110).
struct alignas(16) Rt2dObject {
    RwInt32 type;           // +0x00 Rt2dObjectTypeEnum
    RwInt32 depth;          // +0x04
    RwInt32 flag;           // +0x08
    RwMatrix MTM;           // +0x10 modelling transform (relative to the parent)
    RwMatrix LTM;           // +0x50 local-to-world (Rt2dSceneUpdateLTM)
    RwRGBAReal colorMult;   // +0x90
    RwRGBAReal colorOffs;   // +0xa0
    _rt2dObjectdata data;   // +0xb0
};
DOTD_ASSERT_SIZE(Rt2dObject, 0x110);
DOTD_ASSERT_OFFSET(Rt2dObject, MTM, 0x10);
DOTD_ASSERT_OFFSET(Rt2dObject, LTM, 0x50);
DOTD_ASSERT_OFFSET(Rt2dObject, colorMult, 0x90);
DOTD_ASSERT_OFFSET(Rt2dObject, colorOffs, 0xa0);
DOTD_ASSERT_OFFSET(Rt2dObject, data, 0xb0);

// _rt2dStreamObject: an object's stream record (0x2c).
struct _rt2dStreamObject {
    RwUInt32 version;      // +0x00
    RwInt32 type;          // +0x04
    RwInt32 depth;         // +0x08
    RwRGBAReal colorMult;  // +0x0c
    RwRGBAReal colorOffs;  // +0x1c
};
DOTD_ASSERT_SIZE(_rt2dStreamObject, 0x2c);

// _rt2dDepthOfObject (scene.c): the depth-sort list entry.
struct _rt2dDepthOfObject {
    Rt2dObject* object;  // +0x00
    RwInt32 depth;       // +0x04
};
DOTD_ASSERT_SIZE(_rt2dDepthOfObject, 0x8);

// Fonts (font.c).
typedef uint16_t Rt2dFontChar;  // the PS3 build's characters are 2 bytes (the object strings' text)

struct rt2dCharRect {
    RwReal width;      // +0x00
    RwTexture* tex;    // +0x04
    RwV2d uv[2];       // +0x08
    Rt2dPath* path;    // +0x18
    RwInt8 charpage;   // +0x1c
};
DOTD_ASSERT_SIZE(rt2dCharRect, 0x20);

typedef Rt2dFont* (*Rt2dFontShowCallBack)(Rt2dFont* font, const RwChar* string, RwReal height, RwV2d* anchor,
                                          Rt2dBrush* brush);

struct Rt2dFont {
    RwBool isOutline;            // +0x000
    RwReal height;               // +0x004
    RwReal baseline;             // +0x008
    RwReal intergap;             // +0x00c
    RwUInt32 flag;               // +0x010
    RwTexture* textures[4];      // +0x014
    RwInt16 aCharIndex[128];     // +0x024
    RwInt32 uCharOffset;         // +0x124
    RwInt32 uCharIndexCount;     // +0x128
    RwInt16* uCharIndex;         // +0x12c
    RwInt32 charCount;           // +0x130
    RwSList* charMap;            // +0x134 (rt2dCharRect)
    Rt2dFontShowCallBack fontshowCB;  // +0x138
    Rt2dFont* nextBatch;         // +0x13c
    void* strCache;              // +0x140
};
DOTD_ASSERT_SIZE(Rt2dFont, 0x144);
DOTD_ASSERT_OFFSET(Rt2dFont, uCharIndexCount, 0x128);
DOTD_ASSERT_OFFSET(Rt2dFont, charCount, 0x130);

// --- tool/2danim -------------------------------------------------------------------------------------

// Rt2dMessageType
enum Rt2dMessageType : RwUInt32 {
    rt2dMESSAGETYPENULL = 0,
    rt2dMESSAGETYPEPLAY = 1,
    rt2dMESSAGETYPESTOP = 2,
    rt2dMESSAGETYPENEXTFRAME = 3,
    rt2dMESSAGETYPEPREVFRAME = 4,
    rt2dMESSAGETYPEGOTOFRAME = 5,
    rt2dMESSAGETYPEGOTOLABEL = 6,
    rt2dMESSAGETYPEGETURL = 7,
    rt2dMESSAGETYPEDOACTION = 8,
    rt2dMESSAGETYPEFOREIGN = 9,
    rt2dMESSAGETYPEMOUSEMOVETO = 10,
    rt2dMESSAGETYPEMOUSEBUTTONSTATE = 11,
    rt2dMESSAGETYPESPECIALTELLTARGET = 12,
    rt2dMESSAGETYPEBUTTONBYLABEL = 13,
};

// Rt2dStringLabelType
enum Rt2dStringLabelType : RwUInt32 {
    rt2dANIMLABELTYPENONE = 0,
    rt2dANIMLABELTYPEANIM = 1,
    rt2dANIMLABELTYPEFRAME = 2,
    rt2dANIMLABELTYPEBUTTON = 3,
    rt2dANIMLABELTYPEFOREIGN = 4,
    rt2dANIMLABELTYPESHAPE = 5,
    rt2dANIMLABELTYPEURL = 6,
};

struct Rt2dMessage {
    RwUInt32 messageType;  // +0x00 Rt2dMessageType
    RwInt32 index;         // +0x04
    RwInt32 intParam1;     // +0x08
    RwInt32 intParam2;     // +0x0c
};
DOTD_ASSERT_SIZE(Rt2dMessage, 0x10);

struct Rt2dMessageQueue {
    Rt2dMessage* messageQueue;  // +0x00
    RwInt32 messageTop;         // +0x04
    RwInt32 messageBot;         // +0x08
    RwUInt32 size;              // +0x0c
};
DOTD_ASSERT_SIZE(Rt2dMessageQueue, 0x10);

struct Rt2dStringLabel {
    RwUInt32 entityType;  // +0x00 Rt2dStringLabelType
    RwInt32 nameIndex;    // +0x04 into the maestro's byte bucket
    void* internalData;   // +0x08 (read from the stream as a word: an index until resolved)
    void* userData;       // +0x0c
};
DOTD_ASSERT_SIZE(Rt2dStringLabel, 0x10);

struct Rt2dButton {
    RwInt32 strLabelIndex;                     // +0x00
    RwInt32 objectIndex;                       // +0x04
    RwUInt32 stateFlag;                        // +0x08
    RwUInt32 buttonState;                      // +0x0c
    RwInt32 actionListForStateTransition[32];  // +0x10
};
DOTD_ASSERT_SIZE(Rt2dButton, 0x90);

// Rt2dCel / Rt2dCelList (cel.c; Ghidra "Rt2dAnimNodeGroup(List)").
struct Rt2dCel {
    RwInt32 strLabelIndex;     // +0x00
    RwInt32 celIndex;          // +0x04
    RwSList* buttonIndices;    // +0x08 (RwInt32)
    RwInt32 messageListIndex;  // +0x0c
};
DOTD_ASSERT_SIZE(Rt2dCel, 0x10);

struct Rt2dCelList {
    RwSList* cel;    // +0x00 (Rt2dCel)
    RwUInt32 flag;   // +0x04
};
DOTD_ASSERT_SIZE(Rt2dCelList, 0x8);

// Keyframe updates (keyframe.c).
struct alignas(16) Rt2dKeyFrameTransform {
    RwMatrix matrix;
};
struct Rt2dKeyFrameColor {
    RwRGBAReal color;
};
struct Rt2dKeyFrameShow {
    RwBool show;       // +0x00
    RwInt32 depth;     // +0x04
    RwUInt8 pad1[8];   // +0x08
};
struct Rt2dKeyFrameMorph {
    Rt2dObject* source;       // +0x00
    Rt2dObject* destination;  // +0x04
    RwReal alpha;             // +0x08
    RwInt32 pad1;             // +0x0c
};
DOTD_ASSERT_SIZE(Rt2dKeyFrameShow, 0x10);
DOTD_ASSERT_SIZE(Rt2dKeyFrameMorph, 0x10);

// Rt2dAnimObjectUpdate (PS3 0xa0): one object's change in a keyframe. The stream reader builds an array
// of these, then packs them into the keyframe list's compact data (see Rt2dKeyFrameList).
struct alignas(16) Rt2dAnimObjectUpdate {
    RwBool hasSomething;              // +0x00
    Rt2dObject* object;               // +0x04 (the object index while not yet resolved)
    RwBool hasTransform;              // +0x08
    Rt2dKeyFrameTransform transform;  // +0x10
    RwBool hasColorOffs;              // +0x50
    Rt2dKeyFrameColor colorOffs;      // +0x54
    RwBool hasColorMult;              // +0x64
    Rt2dKeyFrameColor colorMult;      // +0x68
    RwBool hasShow;                   // +0x78
    Rt2dKeyFrameShow show;            // +0x7c
    RwBool hasMorph;                  // +0x8c
    Rt2dKeyFrameMorph morph;          // +0x90
};
DOTD_ASSERT_SIZE(Rt2dAnimObjectUpdate, 0xa0);
DOTD_ASSERT_OFFSET(Rt2dAnimObjectUpdate, hasTransform, 0x08);
DOTD_ASSERT_OFFSET(Rt2dAnimObjectUpdate, transform, 0x10);
DOTD_ASSERT_OFFSET(Rt2dAnimObjectUpdate, hasColorOffs, 0x50);
DOTD_ASSERT_OFFSET(Rt2dAnimObjectUpdate, hasColorMult, 0x64);
DOTD_ASSERT_OFFSET(Rt2dAnimObjectUpdate, hasShow, 0x78);
DOTD_ASSERT_OFFSET(Rt2dAnimObjectUpdate, hasMorph, 0x8c);

// Rt2dKeyFrameSet: the compact record header in a keyframe list's data.
struct Rt2dKeyFrameSet {
    RwUInt32 flag;      // +0x00 bit 0 transform, 1 colorOffs, 2 colorMult, 3 show, 4 morph; 0x20 ends
    RwInt32 objectIdx;  // +0x04
    RwUInt8 pad1[8];    // +0x08
};
DOTD_ASSERT_SIZE(Rt2dKeyFrameSet, 0x10);

// Rt2dKeyFrameList (PS3 0xc; allocated from the 0x301b0 free list). data: the compact array that
// _rt2dKeyFrameListStreamReadTo (0x6face8) builds: per object a Rt2dKeyFrameSet, then 0x40 (matrix),
// 0x10 (colorOffs), 0x10 (colorMult), 0x10 (show), 0x10 (morph) as its flag says; a 0x20 flag ends it.
struct Rt2dKeyFrameList {
    RwReal time;      // +0x00
    RwBool isLocked;  // +0x04
    RwUInt8* data;    // +0x08 (AnimKeyFrameData)
};
DOTD_ASSERT_SIZE(Rt2dKeyFrameList, 0xc);

// _rt2dAnimKeyFrameSched: an Rt2dAnim's keyframe-list entry (the RwSList element, 8 bytes).
struct _rt2dAnimKeyFrameSched {
    RwReal time;                     // +0x00
    Rt2dKeyFrameList* keyframeList;  // +0x04
};
DOTD_ASSERT_SIZE(_rt2dAnimKeyFrameSched, 0x8);

// Rt2dAnim (anim.c; PS3 0x1c).
struct Rt2dAnim {
    RwSList* keyframeLists;         // +0x00 (_rt2dAnimKeyFrameSched)
    RwReal deltaTimeScale;          // +0x04
    RwReal currentTime;             // +0x08
    RwUInt32 flag;                  // +0x0c
    _rt2dAnimKeyFrameSched* prev;   // +0x10
    _rt2dAnimKeyFrameSched* next;   // +0x14
    _rt2dAnimKeyFrameSched* last;   // +0x18
};
DOTD_ASSERT_SIZE(Rt2dAnim, 0x1c);

// Rt2dAnimProps (props.c; PS3 0x10).
struct Rt2dAnimProps {
    Rt2dObject* scene;            // +0x00
    RwSList* directory;           // +0x04
    RwSList* labels;              // +0x08
    RwSList* sceneCurrentState;   // +0x0c
};
DOTD_ASSERT_SIZE(Rt2dAnimProps, 0x10);

// Rt2dAnimNode (maestro.c; PS3 0x3c): one animation of the movie (the root timeline or a movie clip).
struct Rt2dAnimNode {
    RwInt32 flag;            // +0x00
    Rt2dAnim anim;           // +0x04
    Rt2dAnimProps props;     // +0x20
    Rt2dCelList* celList;    // +0x30
    RwInt32 parent;          // +0x34
    RwInt32 posInParentScene;// +0x38
};
DOTD_ASSERT_SIZE(Rt2dAnimNode, 0x3c);
DOTD_ASSERT_OFFSET(Rt2dAnimNode, props, 0x20);
DOTD_ASSERT_OFFSET(Rt2dAnimNode, celList, 0x30);

struct Rt2dMaestroMouseState {
    RwV2d position;   // +0x00
    RwInt32 button;   // +0x08
};
DOTD_ASSERT_SIZE(Rt2dMaestroMouseState, 0xc);

struct Rt2dStateTransData {
    RwInt32 transState;
    RwInt32 buttonUpImg;
    RwInt32 buttonDownImg;
    RwInt32 buttonOverImg;
};
DOTD_ASSERT_SIZE(Rt2dStateTransData, 0x10);

typedef Rt2dMessage* (*Rt2dMessageHandlerCallBack)(Rt2dMaestro* maestro, Rt2dMessage* message);

// Rt2dMaestro (maestro.c; PS3 0x158, free list 0x301b1).
struct Rt2dMaestro {
    RwInt32 flag;                          // +0x00
    RwInt32 version;                       // +0x04
    RwSList* animations;                   // +0x08 (Rt2dAnimNode)
    RwSList* labels;                       // +0x0c (Rt2dStringLabel)
    RwSList* buttons;                      // +0x10 (Rt2dButton)
    RwSList* messageStore;                 // +0x14 (Rt2dMessage)
    RwSList* messageList;                  // +0x18 (RwInt32)
    RwSList* byteBucket;                   // +0x1c (RwChar: the label names)
    Rt2dMessageQueue* messageQueue;        // +0x20
    Rt2dObject* scene;                     // +0x24
    Rt2dMessageHandlerCallBack messageHandler;  // +0x28
    Rt2dMaestroMouseState prevMouse;       // +0x2c
    RwReal invWinH;                        // +0x38
    RwReal invWinW;                        // +0x3c
    RwReal winAspectRatio;                 // +0x40
    RwInt32 currAnimIndex;                 // +0x44
    Rt2dBBox bbox;                         // +0x48
    Rt2dStateTransData stateTransTable[2][2][2][2];  // +0x58
};
DOTD_ASSERT_SIZE(Rt2dMaestro, 0x158);
DOTD_ASSERT_OFFSET(Rt2dMaestro, scene, 0x24);
DOTD_ASSERT_OFFSET(Rt2dMaestro, currAnimIndex, 0x44);
DOTD_ASSERT_OFFSET(Rt2dMaestro, bbox, 0x48);
