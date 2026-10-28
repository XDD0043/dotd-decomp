// object.cpp - RW 3.7 tool/2d/object.c, ported from the PS3 library code (0x713398-0x7146d0). See Rt2d.h.
//
// Object flags (Rt2dObject +0x08): 1 a scene's child list is locked (pointers) or a shape's rep is being
// built, 2 the MTM changed (the LTM is recomputed), 4 visible, 8 the colour transform changed;
// 0x1000000 (object strings) the font name was not found in the font dictionary.
//
// Not ported (stream writers, sizes and copies; the front end never reaches them):
// _rt2dObjectStreamWriteData_maybe 0x713918, _rt2dObjectStreamGetDataSize_maybe 0x7139e8,
// _rt2dObjectBaseStreamWrite_maybe 0x713bb0, _rt2dObjectBaseStreamGetSize_maybe 0x713cd0,
// _rt2dObjectCopyData_maybe 0x714178, Rt2dObjectCopy 0x7144a8.
#include "Renderware/rt2d/Rt2dInternal.h"
#include "Renderware/rwcore/RwMatrix.h"

namespace {

// 0x00c458d4: Rt2dObjectSetFreeListCreateParams' block {entries per block 0x20, blocks 1}.
RwInt32 s_objectFreeListBlockSize = 0x20;
RwInt32 s_objectFreeListPreallocBlocks = 1;

// 0x00ced610: Rt2dObjectGetColorOffset's result buffer (the free list's in-place block follows at +0x10).
RwRGBAReal s_colorOffset;

}  // namespace

DOTD_ASSERT_OFFSET(Rt2dObject, type, 0x0);
DOTD_ASSERT_OFFSET(Rt2dObject, depth, 0x4);
DOTD_ASSERT_OFFSET(Rt2dObject, flag, 0x8);

// 0x00713398 Rt2dObjectSetFreeListCreateParams
void Rt2dObjectSetFreeListCreateParams(RwInt32 blockSize, RwInt32 numBlocksToPrealloc) {
    s_objectFreeListPreallocBlocks = numBlocksToPrealloc;
    s_objectFreeListBlockSize = blockSize;
}

// 0x00713ec0 _rt2dObjectOpen_maybe: the object free list (0x110-byte entries, 16-byte aligned).
RwBool _rt2dObjectOpen() {
    rt2dGlobals.objectFreeList = RwFreeListCreateAndPreallocateSpace(
        sizeof(Rt2dObject), s_objectFreeListBlockSize, 0x10, s_objectFreeListPreallocBlocks, nullptr, 0x401a3);
    return 1;
}

// 0x00713f20 _rt2dObjectClose_maybe
RwBool _rt2dObjectClose() {
    RwFreeListDestroy(rt2dGlobals.objectFreeList);
    rt2dGlobals.objectFreeList = nullptr;
    return 1;
}

// 0x007133f8 _rt2dObjectAlloc_maybe: an uninitialised object from the free list.
Rt2dObject* _rt2dObjectAlloc() { return static_cast<Rt2dObject*>(RwFreeListAlloc(rt2dGlobals.objectFreeList, 0x301a3)); }

// 0x007133a8 _rt2dObjectFree_maybe
void _rt2dObjectFree(Rt2dObject* object) { RwFreeListFree(rt2dGlobals.objectFreeList, object); }

// 0x00713450 Rt2dObjectSetVisible
Rt2dObject* Rt2dObjectSetVisible(Rt2dObject* object, RwBool visible) {
    if (visible == 1) {
        object->flag |= 4;
    } else {
        object->flag &= ~4;
    }
    return object;
}

// 0x00713490 Rt2dObjectIsVisible: the flag bit itself (4 when visible).
RwBool Rt2dObjectIsVisible(Rt2dObject* object) { return object->flag & 4; }

// 0x007134a0 Rt2dObjectGetMTM
RwMatrix* Rt2dObjectGetMTM(Rt2dObject* object) { return &object->MTM; }

// 0x007134b0 Rt2dObjectSetMTM
Rt2dObject* Rt2dObjectSetMTM(Rt2dObject* object, RwMatrix* mtm) {
    object->flag |= 2;
    object->MTM = *mtm;
    return object;
}

// 0x007134f0 Rt2dObjectGetLTM
RwMatrix* Rt2dObjectGetLTM(Rt2dObject* object) { return &object->LTM; }

// 0x00713500 Rt2dObjectMTMChanged
Rt2dObject* Rt2dObjectMTMChanged(Rt2dObject* object) {
    object->flag |= 2;
    return object;
}

// 0x00713510 Rt2dObjectGetColorMultiplier
RwRGBAReal* Rt2dObjectGetColorMultiplier(Rt2dObject* object) { return &object->colorMult; }

// 0x00713520 Rt2dObjectGetObjectType
RwInt32 Rt2dObjectGetObjectType(Rt2dObject* object) { return object->type; }

// 0x00713530 Rt2dObjectGetDepth
RwInt32 Rt2dObjectGetDepth(Rt2dObject* object) { return object->depth; }

// 0x00713540 Rt2dObjectSetDepth. The parent scene's depth list is not marked dirty here (the callers
// call Rt2dSceneSetDepthDirty).
Rt2dObject* Rt2dObjectSetDepth(Rt2dObject* object, RwInt32 depth) {
    object->depth = depth;
    return object;
}

// 0x00713550 Rt2dObjectIsScene / 0x00713578 Rt2dObjectIsShape / 0x007135a0 Rt2dObjectIsPickRegion /
// 0x007135c8 Rt2dObjectIsObjectString
RwBool Rt2dObjectIsScene(Rt2dObject* object) { return object->type == rt2DOBJECTTYPESCENE ? 1 : 0; }
RwBool Rt2dObjectIsShape(Rt2dObject* object) { return object->type == rt2DOBJECTTYPESHAPE ? 1 : 0; }
RwBool Rt2dObjectIsPickRegion(Rt2dObject* object) { return object->type == rt2DOBJECTTYPEPICKREGION ? 1 : 0; }
RwBool Rt2dObjectIsObjectString(Rt2dObject* object) { return object->type == rt2DOBJECTTYPEOBJECTSTRING ? 1 : 0; }

// 0x007135f0 Rt2dObjectSetColorOffset: stored x 255 (0x437f0000).
Rt2dObject* Rt2dObjectSetColorOffset(Rt2dObject* object, RwRGBAReal* oofsCol) {
    object->colorOffs = *oofsCol;
    object->flag |= 8;
    object->colorOffs.red = object->colorOffs.red * 255.0f;
    object->colorOffs.green = object->colorOffs.green * 255.0f;
    object->colorOffs.blue = object->colorOffs.blue * 255.0f;
    object->colorOffs.alpha = object->colorOffs.alpha * 255.0f;
    return object;
}

// 0x00713660 Rt2dObjectGetColorOffset: a static copy x 1/255 (0x3b808081).
RwRGBAReal* Rt2dObjectGetColorOffset(Rt2dObject* object) {
    s_colorOffset = object->colorOffs;
    const RwReal k = 0.00392156886f;  // 0x3b808081
    s_colorOffset.red = s_colorOffset.red * k;
    s_colorOffset.green = s_colorOffset.green * k;
    s_colorOffset.blue = s_colorOffset.blue * k;
    s_colorOffset.alpha = s_colorOffset.alpha * k;
    return &s_colorOffset;
}

// 0x007136c8 Rt2dObjectSetColorMultiplier
Rt2dObject* Rt2dObjectSetColorMultiplier(Rt2dObject* object, RwRGBAReal* multCol) {
    object->colorMult = *multCol;
    object->flag |= 8;
    return object;
}

// 0x00713708 _rt2dObjectMemCopy_maybe: the whole 0x110-byte object.
Rt2dObject* _rt2dObjectMemCopy(Rt2dObject* dst, const Rt2dObject* src) {
    std::memcpy(dst, src, sizeof(Rt2dObject));
    return dst;
}

// 0x00713730 DrawUIObjectByType (_rt2dObjectRender): by type through a jump table (0x71376c); the
// object itself is returned for every type below 5, null otherwise. Type 0 draws nothing; the pick
// region gets the colour transform registers but only updates its transform.
Rt2dObject* _rt2dObjectRender(Rt2dObject* object, RwRGBAReal* colorMult, RwRGBAReal* colorOffs) {
    switch (static_cast<RwUInt32>(object->type)) {
        case rt2DOBJECTTYPEOBJECT: return object;
        case rt2DOBJECTTYPESCENE: _rt2dSceneRender(object, colorMult, colorOffs); return object;
        case rt2DOBJECTTYPESHAPE: _rt2dShapeRender(object, colorMult, colorOffs); return object;
        case rt2DOBJECTTYPEPICKREGION: _rt2dPickRegionRender(object); return object;
        case rt2DOBJECTTYPEOBJECTSTRING: _rt2dObjectStringRender(object, colorMult, colorOffs); return object;
        default: return nullptr;
    }
}

// 0x00713838 _rt2dObjectStreamReadTo: the type's data (the base was read before).
Rt2dObject* _rt2dObjectStreamReadTo(Rt2dObject* object, RwStream* stream, _rt2dSceneResourcePool* pool) {
    switch (object->type) {
        case rt2DOBJECTTYPESHAPE: return _rt2dShapeStreamReadTo(object, stream, pool);
        case rt2DOBJECTTYPESCENE: return _rt2dSceneStreamReadTo(object, stream, pool);
        case rt2DOBJECTTYPEPICKREGION: return _rt2dPickRegionStreamReadTo(object, stream);
        case rt2DOBJECTTYPEOBJECTSTRING: return _rt2dObjectStringStreamReadTo(object, stream);
        default: return nullptr;
    }
}

// 0x00713aa8 _rt2dObjectBaseStreamReadTo: the 0x2c-byte record, RwStreamFindChunk(rwID_MATRIX) and the
// MTM (RwMatrixStreamRead's result is not checked), then type, depth, colours; flag = 6 (visible, MTM
// changed). The record's version word is not checked.
Rt2dObject* _rt2dObjectBaseStreamReadTo(Rt2dObject* object, RwStream* stream) {
    _rt2dStreamObject record;
    if (RwStreamRead(stream, &record, sizeof(record)) != sizeof(record)) return nullptr;
    // RwMemNative32: the record's words are little-endian on disc, already native here.
    if (RwStreamFindChunk(stream, 0xd, nullptr, nullptr) == 0) return nullptr;
    RwMatrixStreamRead(stream, &object->MTM);
    object->type = record.type;
    object->depth = record.depth;
    object->colorMult = record.colorMult;
    object->colorOffs = record.colorOffs;
    object->flag = 6;
    return object;
}

// 0x00713d08 _rt2dObjectInit_maybe: the type, depth 666 (0x29a), visible with the MTM changed (6),
// identity MTM and LTM, colour multiplier (1, 1, 1, 1), offset 0, the type data zeroed.
Rt2dObject* _rt2dObjectInit(Rt2dObject* object, RwInt32 objectType) {
    object->depth = 0x29a;
    object->type = objectType;
    object->MTM.flags |= rwMATRIXINTERNALIDENTITY | rwMATRIXTYPEORTHONORMAL;
    object->LTM.flags |= rwMATRIXINTERNALIDENTITY | rwMATRIXTYPEORTHONORMAL;
    object->MTM.right = RwV3d{1.0f, 0.0f, 0.0f};
    object->MTM.up = RwV3d{0.0f, 1.0f, 0.0f};
    object->MTM.at = RwV3d{0.0f, 0.0f, 1.0f};
    object->MTM.pos = RwV3d{0.0f, 0.0f, 0.0f};
    object->LTM.right = RwV3d{1.0f, 0.0f, 0.0f};
    object->LTM.up = RwV3d{0.0f, 1.0f, 0.0f};
    object->LTM.at = RwV3d{0.0f, 0.0f, 1.0f};
    object->LTM.pos = RwV3d{0.0f, 0.0f, 0.0f};
    object->colorMult = RwRGBAReal{1.0f, 1.0f, 1.0f, 1.0f};
    object->flag = 6;
    object->colorOffs = RwRGBAReal{0.0f, 0.0f, 0.0f, 0.0f};
    std::memset(&object->data, 0, sizeof(object->data));
    return object;
}

// 0x00713e08 _rt2dObjectDestruct_maybe: the type's destructor; 0 for an unknown type.
RwBool _rt2dObjectDestruct(Rt2dObject* object) {
    switch (object->type) {
        case rt2DOBJECTTYPESHAPE: return _rt2dShapeDestruct(object);
        case rt2DOBJECTTYPESCENE: return _rt2dSceneDestruct(object);
        case rt2DOBJECTTYPEPICKREGION: return _rt2dPickRegionDestruct(object);
        case rt2DOBJECTTYPEOBJECTSTRING: return _rt2dObjectStringDestruct(object);
        default: return 0;
    }
}

// 0x007145d8 Rt2dObjectDestroy_maybe: the destructor, then the object back to the free list (also for
// an unknown type, which returns 0). A null object returns 0.
RwBool Rt2dObjectDestroy(Rt2dObject* object) {
    if (object == nullptr) return 0;
    RwBool result = 0;
    switch (object->type) {
        case rt2DOBJECTTYPESHAPE: result = _rt2dShapeDestruct(object); break;
        case rt2DOBJECTTYPESCENE: result = _rt2dSceneDestruct(object); break;
        case rt2DOBJECTTYPEPICKREGION: result = _rt2dPickRegionDestruct(object); break;
        case rt2DOBJECTTYPEOBJECTSTRING: result = _rt2dObjectStringDestruct(object); break;
        default: result = 0; break;
    }
    _rt2dObjectFree(object);
    return result;
}

// 0x00713f60 Rt2dObjectMTMSetIdentity
Rt2dObject* Rt2dObjectMTMSetIdentity(Rt2dObject* object) {
    object->MTM.flags |= rwMATRIXINTERNALIDENTITY | rwMATRIXTYPEORTHONORMAL;
    object->flag |= 2;
    object->MTM.right = RwV3d{1.0f, 0.0f, 0.0f};
    object->MTM.up = RwV3d{0.0f, 1.0f, 0.0f};
    object->MTM.at = RwV3d{0.0f, 0.0f, 1.0f};
    object->MTM.pos = RwV3d{0.0f, 0.0f, 0.0f};
    return object;
}

// 0x00713fc0 Rt2dObjectMTMRotate: about z, degrees, pre-concatenated.
Rt2dObject* Rt2dObjectMTMRotate(Rt2dObject* object, RwReal rotation) {
    RwV3d axis = {0.0f, 0.0f, 1.0f};
    RwMatrixRotate(&object->MTM, &axis, rotation, rwCOMBINEPRECONCAT);
    object->flag |= 2;
    return object;
}

// 0x00714030 Rt2dObjectMTMTranslate: pre-concatenated.
Rt2dObject* Rt2dObjectMTMTranslate(Rt2dObject* object, RwReal x, RwReal y) {
    RwV3d v = {x, y, 0.0f};
    RwMatrixTranslate(&object->MTM, &v, rwCOMBINEPRECONCAT);
    object->flag |= 2;
    return object;
}

// 0x00714098 Rt2dObjectMTMScale: pre-concatenated.
Rt2dObject* Rt2dObjectMTMScale(Rt2dObject* object, RwReal x, RwReal y) {
    RwV3d v = {x, y, 1.0f};
    RwMatrixScale(&object->MTM, &v, rwCOMBINEPRECONCAT);
    object->flag |= 2;
    return object;
}

// 0x00714100 Rt2dObjectApplyCTM: the MTM becomes the current CTM.
Rt2dObject* Rt2dObjectApplyCTM(Rt2dObject* object) {
    RwMatrix* top = _rt2dCTMGet();
    object->flag |= 2;
    object->MTM = *top;
    return object;
}
