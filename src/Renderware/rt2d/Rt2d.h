// Rt2d.h - the RenderWare 3.7 2D toolkit (tool/2d), ported from the PS3 library code (0x704f00-0x71f3d8,
// library TOC 0xc25974): the functions other units call. Each original source file has its .cpp here
// (brush with fill, path, shape with stroke and tri, object, scene, pickreg, gstate, 2dstr, font);
// file-local functions stay in their .cpp, shared internals in Rt2dInternal.h.
//
// Names: RW 3.7's (XXL2 build, same code) where the PS3 function matches; the PS3 address and the Ghidra
// name are on each declaration. The signatures follow the PS3 code (C1.5 family B report lists the
// changes from the foundation's first reading).
#pragma once
#include "Renderware/rt2d/Rt2dTypes.h"
#include "Renderware/rwcore/RwTypes.h"

struct RwStream;

typedef Rt2dObject* (*Rt2dObjectCallBack)(Rt2dObject* object, Rt2dObject* parent, void* data);

// --- 2d/gstate.c: toolkit state, device, CTM stack ---------------------------------------------------
// 0x007130e8 Rt2dOpen (cam may be null: no view window then)
RwBool Rt2dOpen(RwCamera* cam);
// 0x00713000 Rt2dClose
RwBool Rt2dClose();
// 0x00711b78 Rt2dDeviceSetCamera: 0 without a frame buffer
RwBool Rt2dDeviceSetCamera(RwCamera* cam);
// 0x00711c48 Rt2dDeviceGetCamera
RwCamera* Rt2dDeviceGetCamera();
// 0x00712cb0 Rt2dDeviceSetMetric
RwBool Rt2dDeviceSetMetric(RwReal x, RwReal y, RwReal w, RwReal h);
// 0x00711ae8 Rt2dDeviceGetMetric
RwBool Rt2dDeviceGetMetric(RwReal* x, RwReal* y, RwReal* w, RwReal* h);
// 0x007128b0 Rt2dDeviceGetStep
RwBool Rt2dDeviceGetStep(RwV2d* xstep, RwV2d* ystep, RwV2d* origin);
// 0x00711b18 Rt2dDeviceSetFlat
RwBool Rt2dDeviceSetFlat(RwReal r);
// 0x00711b48 Rt2dDeviceSetLayerDepth_maybe
RwBool Rt2dDeviceSetLayerDepth(RwReal depth);
// 0x00711c58 Rt2dDeviceSetIm3DTransformFlags_maybe
RwBool Rt2dDeviceSetIm3DTransformFlags(RwUInt32 flags);
// 0x00711a20 Rt2dCTMSetIdentity
RwBool Rt2dCTMSetIdentity();
// 0x00712320 UI2D_PushMatrix (Rt2dCTMPush)
RwBool Rt2dCTMPush();
// 0x00711c68 UI2D_PopMatrix (Rt2dCTMPop)
RwBool Rt2dCTMPop();
// 0x00711cc0 UI2D_ScaleMatrix (Rt2dCTMScale)
RwBool Rt2dCTMScale(RwReal x, RwReal y);
// 0x00711d30 UI2D_TranslateMatrix (Rt2dCTMTranslate)
RwBool Rt2dCTMTranslate(RwReal x, RwReal y);
// 0x00712a48 UI2d_RotateCurrentMatrix_maybe (Rt2dCTMRotate; degrees)
RwBool Rt2dCTMRotate(RwReal theta);
// 0x00712090 UI2D_PushLoadMatrix (_rt2dCTMPush: push, then load matrix)
RwBool _rt2dCTMPush(RwMatrix* matrix);
// 0x007121a0 UI2D_PushMultMatrix (_rt2dCTMPushMult: push matrix x the previous top)
RwBool _rt2dCTMPushMult(RwMatrix* matrix);
// 0x00711ca0 UI2D_GetTopMatrix (_rt2dCTMGet: the top of the stack)
RwMatrix* _rt2dCTMGet();
// 0x00711da0 UI2D_GetCompositeMatrix_maybe (the CTM in world space: CTM2d x the camera frame's LTM)
RwMatrix* _rt2dCTMGetComposite();
// 0x00712068 UI2D_GetCompositeMatrixGlobal_maybe (the inverse CTM2d)
RwMatrix* _rt2dCTMGetInverse();
// 0x00712018 UI2D_IsCompositeMatrixMirrored_maybe
RwBool _rt2dCTMIsMirrored();
// 0x00712c08 _rt2dGetFlatnessTolerance_maybe (_rt2dGetTolerance: squared, object space)
RwReal _rt2dGetTolerance();

// --- 2d/brush.c (with fill.c) --------------------------------------------------------------------------
// 0x0070a430 Rt2dBrushSetFreeListCreateParams
void Rt2dBrushSetFreeListCreateParams(RwInt32 blockSize, RwInt32 numBlocksToPrealloc);
// 0x0070b488 Rt2dBrushCreate
Rt2dBrush* Rt2dBrushCreate();
// 0x0070ae10 Rt2dBrushDestroy (drops a reference; 1 when freed)
RwBool Rt2dBrushDestroy(Rt2dBrush* brush);
// 0x0070b208 Rt2dBrushSetRGBA
Rt2dBrush* Rt2dBrushSetRGBA(Rt2dBrush* brush, RwRGBA* col0, RwRGBA* col1, RwRGBA* col2, RwRGBA* col3);
// 0x0070a888 Rt2dBrushSetUV
Rt2dBrush* Rt2dBrushSetUV(Rt2dBrush* brush, RwV2d* uv0, RwV2d* uv1, RwV2d* uv2, RwV2d* uv3);
// 0x0070ad70 Rt2dBrushSetTexture
Rt2dBrush* Rt2dBrushSetTexture(Rt2dBrush* brush, RwTexture* texture);
// 0x0070b5b0 Rt2dBrushStreamRead (after the caller's RwStreamFindChunk(0x1a2))
Rt2dBrush* Rt2dBrushStreamRead(RwStream* stream);
// 0x0070ac38 _rt2dBrushStreamReadTo_maybe
Rt2dBrush* _rt2dBrushStreamReadTo(Rt2dBrush* brush, RwStream* stream);
// 0x0070a440 Rt2d_ColorMulAddClamped_maybe (_rt2dBrushTransformColor: brush colours = given x mult + offs)
Rt2dBrush* _rt2dBrushTransformColor(Rt2dBrush* brush, const RwRGBAReal* bottom, const RwRGBAReal* dbottom,
                                    const RwRGBAReal* dtop, const RwRGBAReal* top, const RwRGBAReal* mult,
                                    const RwRGBAReal* offs);
// 0x0070be48 DrawUIFilledPathGeometry (Rt2dPathFill: one subpath, immediate mode)
Rt2dPath* Rt2dPathFill(Rt2dPath* path, Rt2dBrush* brush);
// 0x0070cad0 DrawUIShapePathChain (+ 0x0070c8e0): every closed subpath of the chain filled
Rt2dPath* _rt2dPathRenderChain(Rt2dPath* path, Rt2dBrush* brush);

// --- 2d/path.c ---------------------------------------------------------------------------------------
// 0x007146d0 Rt2dPathSetFreeListCreateParams
void Rt2dPathSetFreeListCreateParams(RwInt32 blockSize, RwInt32 numBlocksToPrealloc);
// 0x00715198 Rt2dPathCreate (locked)
Rt2dPath* Rt2dPathCreate();
// 0x00716658 Rt2dPathDestroy
RwBool Rt2dPathDestroy(Rt2dPath* path);
// 0x00717580 Rt2dPathEmpty
Rt2dPath* Rt2dPathEmpty(Rt2dPath* path);
// 0x00715028 Rt2dPathLock_maybe
Rt2dPath* Rt2dPathLock(Rt2dPath* path);
// 0x007163d0 Rt2dPathUnlock_maybe
Rt2dPath* Rt2dPathUnlock(Rt2dPath* path);
// 0x00717b90 Rt2dPathMoveto
Rt2dPath* Rt2dPathMoveto(Rt2dPath* path, RwReal x, RwReal y);
// 0x007158b8 Rt2dPathLineto
Rt2dPath* Rt2dPathLineto(Rt2dPath* path, RwReal x, RwReal y);
// 0x00715630 Rt2dPathCurveto
Rt2dPath* Rt2dPathCurveto(Rt2dPath* path, RwReal x1, RwReal y1, RwReal x2, RwReal y2, RwReal x3, RwReal y3);
// 0x00715a38 Rt2dPathClose
Rt2dPath* Rt2dPathClose(Rt2dPath* path);
// 0x00717e60 Rt2dPathRect
Rt2dPath* Rt2dPathRect(Rt2dPath* path, RwReal x, RwReal y, RwReal w, RwReal h);
// 0x007185e0 Rt2dPathStreamRead (after the caller's RwStreamFindChunk(0x1a1))
Rt2dPath* Rt2dPathStreamRead(RwStream* stream);
// 0x00718540 _rt2dPathStreamReadTo
Rt2dPath* _rt2dPathStreamReadTo(Rt2dPath* path, RwStream* stream);

// --- 2d/shape.c (with stroke.c, tri.c) ------------------------------------------------------------------
// 0x0071ce08 _rt2dShapeRepStreamRead
_rt2dShapeRep* _rt2dShapeRepStreamRead(RwStream* stream);
// 0x0071c5c8 _rt2dShapeRepDestroy_maybe (drops a reference; 1 when destroyed)
RwBool _rt2dShapeRepDestroy(_rt2dShapeRep* rep);
// 0x0071d0c0 _rt2dShapeStreamReadTo (pool: the scene's shape reps, or null when the shape carries its own)
Rt2dObject* _rt2dShapeStreamReadTo(Rt2dObject* shape, RwStream* stream, _rt2dSceneResourcePool* pool);
// 0x0071ccf0 _rt2dShapeInit_maybe (rep null: a new rep of nodeCount nodes)
RwBool _rt2dShapeInit(Rt2dObject* shape, RwInt32 nodeCount, _rt2dShapeRep* rep);
// 0x0071c718 _rt2dShapeDestruct_maybe
RwBool _rt2dShapeDestruct(Rt2dObject* shape);
// 0x0071bb80 DrawUIShapeSceneObject (_rt2dShapeRender: with the inherited colour transform)
Rt2dObject* _rt2dShapeRender(Rt2dObject* shape, RwRGBAReal* colorMult, RwRGBAReal* colorOffs);
// 0x0071de20 DrawUIStrokePathGeometry (Rt2dPathStroke: every subpath, immediate mode)
Rt2dPath* Rt2dPathStroke(Rt2dPath* path, Rt2dBrush* brush);

// --- 2d/object.c -------------------------------------------------------------------------------------
// 0x00713398 Rt2dObjectSetFreeListCreateParams
void Rt2dObjectSetFreeListCreateParams(RwInt32 blockSize, RwInt32 numBlocksToPrealloc);
// 0x007133f8 _rt2dObjectAlloc_maybe
Rt2dObject* _rt2dObjectAlloc();
// 0x007133a8 _rt2dObjectFree_maybe
void _rt2dObjectFree(Rt2dObject* object);
// 0x00713708 _rt2dObjectMemCopy_maybe
Rt2dObject* _rt2dObjectMemCopy(Rt2dObject* dst, const Rt2dObject* src);
// 0x00713d08 _rt2dObjectInit_maybe
Rt2dObject* _rt2dObjectInit(Rt2dObject* object, RwInt32 objectType);
// 0x00713e08 _rt2dObjectDestruct_maybe (0 for an unknown type)
RwBool _rt2dObjectDestruct(Rt2dObject* object);
// 0x007145d8 Rt2dObjectDestroy_maybe
RwBool Rt2dObjectDestroy(Rt2dObject* object);
// 0x00713aa8 _rt2dObjectBaseStreamReadTo
Rt2dObject* _rt2dObjectBaseStreamReadTo(Rt2dObject* object, RwStream* stream);
// 0x00713838 _rt2dObjectStreamReadTo
Rt2dObject* _rt2dObjectStreamReadTo(Rt2dObject* object, RwStream* stream, _rt2dSceneResourcePool* pool);
// 0x00713730 DrawUIObjectByType (_rt2dObjectRender: by type, with the inherited colour transform)
Rt2dObject* _rt2dObjectRender(Rt2dObject* object, RwRGBAReal* colorMult, RwRGBAReal* colorOffs);
// 0x00713490 Rt2dObjectIsVisible (the flag bit: 4 when visible)
RwBool Rt2dObjectIsVisible(Rt2dObject* object);
// 0x00713450 Rt2dObjectSetVisible (only 1 makes it visible)
Rt2dObject* Rt2dObjectSetVisible(Rt2dObject* object, RwBool visible);
// 0x00713550 / 0x00713578 / 0x007135a0 / 0x007135c8 Rt2dObjectIs{Scene,Shape,PickRegion,ObjectString}
RwBool Rt2dObjectIsScene(Rt2dObject* object);
RwBool Rt2dObjectIsShape(Rt2dObject* object);
RwBool Rt2dObjectIsPickRegion(Rt2dObject* object);
RwBool Rt2dObjectIsObjectString(Rt2dObject* object);
// 0x00713520 Rt2dObjectGetObjectType / 0x00713530 Rt2dObjectGetDepth
RwInt32 Rt2dObjectGetObjectType(Rt2dObject* object);
RwInt32 Rt2dObjectGetDepth(Rt2dObject* object);
// 0x007134a0 Rt2dObjectGetMTM / 0x007134b0 Rt2dObjectSetMTM
RwMatrix* Rt2dObjectGetMTM(Rt2dObject* object);
Rt2dObject* Rt2dObjectSetMTM(Rt2dObject* object, RwMatrix* mtm);
// 0x007134f0 Rt2dObjectGetLTM
RwMatrix* Rt2dObjectGetLTM(Rt2dObject* object);
// 0x00713500 Rt2dObjectMTMChanged
Rt2dObject* Rt2dObjectMTMChanged(Rt2dObject* object);
// 0x00713f60 Rt2dObjectMTMSetIdentity
Rt2dObject* Rt2dObjectMTMSetIdentity(Rt2dObject* object);
// 0x00713fc0 Rt2dObjectMTMRotate (degrees)
Rt2dObject* Rt2dObjectMTMRotate(Rt2dObject* object, RwReal rotation);
// 0x00714030 Rt2dObjectMTMTranslate
Rt2dObject* Rt2dObjectMTMTranslate(Rt2dObject* object, RwReal x, RwReal y);
// 0x00714098 Rt2dObjectMTMScale
Rt2dObject* Rt2dObjectMTMScale(Rt2dObject* object, RwReal x, RwReal y);
// 0x00714100 Rt2dObjectApplyCTM
Rt2dObject* Rt2dObjectApplyCTM(Rt2dObject* object);
// 0x00713540 Rt2dObjectSetDepth
Rt2dObject* Rt2dObjectSetDepth(Rt2dObject* object, RwInt32 depth);
// 0x007136c8 Rt2dObjectSetColorMultiplier / 0x00713510 Rt2dObjectGetColorMultiplier
Rt2dObject* Rt2dObjectSetColorMultiplier(Rt2dObject* object, RwRGBAReal* multCol);
RwRGBAReal* Rt2dObjectGetColorMultiplier(Rt2dObject* object);
// 0x007135f0 Rt2dObjectSetColorOffset (stored x 255) / 0x00713660 Rt2dObjectGetColorOffset (a static copy / 255)
Rt2dObject* Rt2dObjectSetColorOffset(Rt2dObject* object, RwRGBAReal* oofsCol);
RwRGBAReal* Rt2dObjectGetColorOffset(Rt2dObject* object);

// --- 2d/scene.c --------------------------------------------------------------------------------------
// 0x0071acc0 Rt2dSceneStreamRead (after the caller's RwStreamFindChunk(0x1a5))
Rt2dObject* Rt2dSceneStreamRead(RwStream* stream);
// 0x0071a808 _rt2dSceneStreamReadTo
Rt2dObject* _rt2dSceneStreamReadTo(Rt2dObject* scene, RwStream* stream, _rt2dSceneResourcePool* pool);
// 0x0071a4f8 Rt2dSceneCreate (empty, locked)
Rt2dObject* Rt2dSceneCreate();
// 0x00719c38 Rt2dSceneDestroy
RwBool Rt2dSceneDestroy(Rt2dObject* scene);
// 0x00719b30 _rt2dSceneDestruct_maybe
RwBool _rt2dSceneDestruct(Rt2dObject* scene);
// 0x007199d0 Rt2dSceneLock
Rt2dObject* Rt2dSceneLock(Rt2dObject* scene);
// 0x00719f98 Rt2dSceneUnlock
Rt2dObject* Rt2dSceneUnlock(Rt2dObject* scene);
// 0x00719948 Rt2dSceneAddChild (locked)
Rt2dObject* Rt2dSceneAddChild(Rt2dObject* scene, Rt2dObject* object);
// 0x00719f00 _rt2dSceneGetNewChild_maybe (locked)
Rt2dObject* _rt2dSceneGetNewChild(Rt2dObject* scene, RwInt32 objectType);
// 0x00719110 Rt2dSceneGetChildCount
RwInt32 Rt2dSceneGetChildCount(Rt2dObject* scene);
// 0x00719130 Rt2dSceneForAllChildren
Rt2dObject* Rt2dSceneForAllChildren(Rt2dObject* scene, Rt2dObjectCallBack callback, void* pData);
// 0x007198d8 Rt2dSceneGetChildByIndex
Rt2dObject* Rt2dSceneGetChildByIndex(Rt2dObject* scene, RwInt32 index);
// 0x007191f8 Rt2dSceneUpdateLTM
Rt2dObject* Rt2dSceneUpdateLTM(Rt2dObject* scene);
// 0x00719120 Rt2dSceneSetDepthDirty
Rt2dObject* Rt2dSceneSetDepthDirty(Rt2dObject* scene);
// 0x007198c8 DrawUIRootScene (Rt2dSceneRender)
Rt2dObject* Rt2dSceneRender(Rt2dObject* object);

// --- 2d/2dstr.c --------------------------------------------------------------------------------------
// 0x00709bf8 _rt2dObjectStringStreamReadTo
Rt2dObject* _rt2dObjectStringStreamReadTo(Rt2dObject* string, RwStream* stream);
// 0x00709a20 _rt2dObjectStringInit_maybe
Rt2dObject* _rt2dObjectStringInit(Rt2dObject* string, const RwChar* text, const RwChar* font);
// 0x007090e8 Rt2dObjectStringGetText
RwChar* Rt2dObjectStringGetText(Rt2dObject* string);
// 0x007090f0 Rt2dObjectStringGetFont (the font's name)
RwChar* Rt2dObjectStringGetFont(Rt2dObject* string);
// 0x00709100 Rt2dObjectStringGetHeight / 0x00709108 Rt2dObjectStringSetHeight
RwReal Rt2dObjectStringGetHeight(Rt2dObject* string);
Rt2dObject* Rt2dObjectStringSetHeight(Rt2dObject* string, RwReal height);
// 0x007093b8 Rt2dObjectStringSetText (text ends with two zero bytes)
Rt2dObject* Rt2dObjectStringSetText(Rt2dObject* string, const RwChar* text);
// 0x007094e0 Rt2dObjectStringSetBrush (copies the brush's contents)
Rt2dObject* Rt2dObjectStringSetBrush(Rt2dObject* string, Rt2dBrush* brush);
// 0x00709930 Rt2dObjectStringSetFont (null when the font is not in the dictionary)
Rt2dObject* Rt2dObjectStringSetFont(Rt2dObject* string, const RwChar* font);

// --- 2d/pickreg.c ------------------------------------------------------------------------------------
// 0x00718d88 _rt2dPickRegionStreamReadTo
Rt2dObject* _rt2dPickRegionStreamReadTo(Rt2dObject* region, RwStream* stream);
// 0x00718cc0 _rt2dPickRegionInit_maybe
Rt2dObject* _rt2dPickRegionInit(Rt2dObject* region);
// 0x00718a28 Rt2dPickRegionGetPath
Rt2dPath* Rt2dPickRegionGetPath(Rt2dObject* region);

// --- 2d/font.c ---------------------------------------------------------------------------------------
// 0x0070cb48 Rt2dFontSetFreeListCreateParams / 0x0070cb58 Rt2dFontDictNodeSetFreeListCreateParams_maybe
void Rt2dFontSetFreeListCreateParams(RwInt32 blockSize, RwInt32 numBlocksToPrealloc);
void Rt2dFontDictNodeSetFreeListCreateParams(RwInt32 blockSize, RwInt32 numBlocksToPrealloc);
// 0x0070df88 Rt2dFontStreamRead (after the caller's RwStreamFindChunk(0x199))
Rt2dFont* Rt2dFontStreamRead(RwStream* stream);
// 0x0070d9a0 Rt2dFontDestroy
RwBool Rt2dFontDestroy(Rt2dFont* font);
// 0x0070d638 Rt2dFontGetStringWidth
RwReal Rt2dFontGetStringWidth(Rt2dFont* font, const RwChar* string, RwReal height);
// 0x0070cd08 Rt2dFontSetIntergapSpacing_maybe
Rt2dFont* Rt2dFontSetIntergapSpacing(Rt2dFont* font, RwReal gap);
// 0x0070ccc8 DispatchUIFontRenderCallback (Rt2dFontShow)
Rt2dFont* Rt2dFontShow(Rt2dFont* font, const RwChar* string, RwReal height, RwV2d* anchor, Rt2dBrush* brush);
// 0x0070d240 DrawUIWrappedFontText (Rt2dFontFlow; the text is terminated in place line by line)
Rt2dFont* Rt2dFontFlow(Rt2dFont* font, RwChar* string, RwReal height, Rt2dBBox* bbox, Rt2dJustificationType format,
                       Rt2dBrush* brush);
// 0x0070d220 Rt2dFontTexDictionarySet / 0x0070d230 Rt2dFontTexDictionaryGet_maybe
RwTexDictionary* Rt2dFontTexDictionarySet(RwTexDictionary* texDict);
RwTexDictionary* Rt2dFontTexDictionaryGet();
// 0x0070cde0 _rt2dFontDictionaryAdd_maybe (returns the font)
Rt2dFont* _rt2dFontDictionaryAdd(Rt2dFont* font, const RwChar* name);
// 0x0070cf08 _rt2dFontDictionaryRemove_maybe (the entry of font; returns it, null when absent)
Rt2dFont* _rt2dFontDictionaryRemove(Rt2dFont* font);
// 0x0070e770 _rt2dFontDictionaryFindEntry_maybe
_rt2dFontDictionaryNode* _rt2dFontDictionaryFindEntry(const RwChar* name);
// The character decoding and glyph lookup the string walks share (inlined on the PS3).
RwInt32 _rt2dFontDecodeChar(const Rt2dFont* font, const RwChar* s, RwInt32* step);
RwInt32 _rt2dFontCharIndex(const Rt2dFont* font, RwInt32 c);
