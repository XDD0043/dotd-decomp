// scene.cpp - RW 3.7 tool/2d/scene.c, ported from the PS3 library code (0x7191f8-0x71b4b8; the PS3 build
// also keeps Rt2dSceneGetChildCount, SetDepthDirty and ForAllChildren at 0x719110-0x719130, after
// pickreg.c). See Rt2d.h.
//
// A scene's children: while the scene is locked (flag 1) data.scene.objects is an RwSList of
// Rt2dObject pointers; unlocked (Rt2dSceneUnlock) it holds the objects by value (0x110 bytes each),
// with data.scene.depths an RwSList of {object, depth} sorted by depth (selection sort, ascending).
//
// Not ported (stream writers, sizes and copies; the front end never reaches them):
// _rt2dSceneStreamGetSizeChildCB_maybe 0x719520, _rt2dSceneStreamWriteChildCB_maybe 0x719578,
// _rt2dSceneCopyData_maybe 0x719d80, Rt2dSceneGetNewChildObjectString 0x71a238,
// Rt2dSceneGetNewChildPickRegion 0x71a2f0, Rt2dSceneGetNewChildShape 0x71a388,
// Rt2dSceneGetNewChildScene 0x71a428, _rt2dSceneCollectShapeReps_maybe 0x71a588,
// _rt2dSceneCountShapes_maybe 0x71a708, _rt2dSceneGatherShapeReps_maybe 0x71ada8,
// _rt2dSceneStreamGetDataSize_maybe 0x71af48, Rt2dSceneStreamGetSize 0x71b190,
// _rt2dSceneStreamWriteData_maybe 0x71b198, Rt2dSceneStreamWrite 0x71b418, _rt2dShapeRepAddRef_maybe
// 0x71b4b8.
#include "Renderware/rt2d/Rt2dInternal.h"

DOTD_ASSERT_OFFSET(Rt2dObject, data.scene.objects, 0xb0);
DOTD_ASSERT_OFFSET(Rt2dObject, data.scene.objectCount, 0xb4);
DOTD_ASSERT_OFFSET(Rt2dObject, data.scene.depths, 0xb8);
DOTD_ASSERT_OFFSET(Rt2dObject, data.scene.isDirtyDepths, 0xbc);

namespace {

// 0x00a72480 / 0x00a72490: the root colour transform (multiplier 1, offset 0).
RwRGBAReal s_rootColorMult = {1.0f, 1.0f, 1.0f, 1.0f};
RwRGBAReal s_rootColorOffs = {0.0f, 0.0f, 0.0f, 0.0f};

// The depth list's refresh and sort (inlined in _rt2dSceneStreamReadTo, Rt2dSceneUnlock and the render):
// each entry's depth from its object, then a selection sort by swapping (an entry moves when a later one
// is strictly smaller), ascending.
void SortDepths(Rt2dObject* scene) {
    _rt2dDepthOfObject* first = RwSListArray<_rt2dDepthOfObject>(scene->data.scene.depths);
    _rt2dDepthOfObject* end = first + scene->data.scene.objectCount;
    if (first == end) return;
    for (_rt2dDepthOfObject* d = first; d != end; ++d) d->depth = d->object->depth;
    for (_rt2dDepthOfObject* i = first; i < end - 1; ++i) {
        for (_rt2dDepthOfObject* j = i + 1; j < end; ++j) {
            if (j->depth < i->depth) {
                const _rt2dDepthOfObject t = *i;
                *i = *j;
                *j = t;
            }
        }
    }
}

// The depth list built anew over the (unlocked) children, in child order.
void FillDepths(Rt2dObject* scene) {
    _rt2dDepthOfObject* d = RwSListArray<_rt2dDepthOfObject>(scene->data.scene.depths);
    Rt2dObject* child = RwSListArray<Rt2dObject>(scene->data.scene.objects);
    _rt2dDepthOfObject* end = d + scene->data.scene.objectCount;
    for (; d != end; ++d, ++child) d->object = child;
}

// The children as an array by value (the scene unlocked).
inline Rt2dObject* Children(Rt2dObject* scene) { return RwSListArray<Rt2dObject>(scene->data.scene.objects); }

// _rt2dSceneStreamReadTo's per-child context: the stream and the shape-rep pool.
struct ChildReadContext {
    RwStream* stream;
    _rt2dSceneResourcePool* pool;
};

// 0x007194b8 _rt2dSceneStreamReadToChildCallback: the child's base, then its type data.
Rt2dObject* SceneStreamReadToChildCallback(Rt2dObject* child, Rt2dObject* /*scene*/, ChildReadContext* context) {
    if (_rt2dObjectBaseStreamReadTo(child, context->stream) == nullptr) return nullptr;
    return _rt2dObjectStreamReadTo(child, context->stream, context->pool);
}

}  // namespace

// 0x00719110 Rt2dSceneGetChildCount
RwInt32 Rt2dSceneGetChildCount(Rt2dObject* scene) { return scene->data.scene.objectCount; }

// 0x00719120 Rt2dSceneSetDepthDirty
Rt2dObject* Rt2dSceneSetDepthDirty(Rt2dObject* scene) {
    scene->data.scene.isDirtyDepths = 1;
    return scene;
}

// 0x00719130 Rt2dSceneForAllChildren: every child in child order (the scene unlocked); the callback's
// result is ignored.
Rt2dObject* Rt2dSceneForAllChildren(Rt2dObject* scene, Rt2dObjectCallBack callback, void* pData) {
    Rt2dObject* child = Children(scene);
    Rt2dObject* end = child + scene->data.scene.objectCount;
    for (; child != end; ++child) callback(child, scene, pData);
    return scene;
}

// 0x007191f8 Rt2dSceneUpdateLTM: the scene's LTM (CTM x MTM when the MTM changed, else the LTM as it is)
// pushed, then every child by depth: a changed parent marks the child changed; scenes recurse, others
// get LTM = CTM x MTM when changed; pick regions keep the inverse LTM as their transformation.
// BUG(original): after a child scene's own update (which pushes and pops) the loop pops once more, so the
// siblings after a child scene are combined with the grandparent's CTM (and the LTMs above the root
// scene's are popped; Rt2dCTMPop stops at the bottom of the stack).
Rt2dObject* Rt2dSceneUpdateLTM(Rt2dObject* scene) {
    RwBool parentChanged;
    if ((scene->flag & 2) != 0) {
        parentChanged = 1;
        _rt2dCTMPushMult(&scene->MTM);
        scene->LTM = *_rt2dCTMGet();
        scene->flag &= ~2;
    } else {
        parentChanged = 0;
        _rt2dCTMPush(&scene->LTM);
    }
    _rt2dDepthOfObject* d = RwSListArray<_rt2dDepthOfObject>(scene->data.scene.depths);
    _rt2dDepthOfObject* end = d + scene->data.scene.objectCount;
    for (; d != end; ++d) {
        if (parentChanged == 1) d->object->flag |= 2;
        Rt2dObject* child = d->object;
        if (child->type == rt2DOBJECTTYPESCENE) {
            Rt2dSceneUpdateLTM(child);
            Rt2dCTMPop();
            continue;
        }
        if ((child->flag & 2) != 0) {
            _rt2dCTMPushMult(&child->MTM);
            Rt2dObject* object = d->object;
            object->LTM = *_rt2dCTMGet();
            object->flag &= ~2;
        } else {
            _rt2dCTMPush(&child->LTM);
        }
        Rt2dObject* object = d->object;
        if (object->type == rt2DOBJECTTYPEPICKREGION) {
            RwMatrixInvert(&object->data.pickRegion.transformation, &object->LTM);
        }
        Rt2dCTMPop();
    }
    Rt2dCTMPop();
    return scene;
}

// 0x007195b0 DrawUIOrderedSceneChildren (_rt2dSceneRender): a visible scene pushes its LTM (recomputed
// from the MTM when it changed, which then marks every child changed), combines its colour transform with
// the inherited one (multiplier x inherited; offset / 255 x inherited multiplier + inherited offset,
// fmadds), re-sorts the depth list when dirty, and draws the children by depth.
Rt2dObject* _rt2dSceneRender(Rt2dObject* scene, RwRGBAReal* colorMult, RwRGBAReal* colorOffs) {
    if ((scene->flag & 4) == 0) return scene;
    RwBool changed;
    if ((scene->flag & 2) != 0) {
        changed = 1;
        _rt2dCTMPushMult(&scene->MTM);
        scene->LTM = *_rt2dCTMGet();
        scene->flag &= ~2;
    } else {
        changed = 0;
        _rt2dCTMPush(&scene->LTM);
    }
    RwRGBAReal mult;
    RwRGBAReal offs;
    offs.red = ppc::fmadds(scene->colorOffs.red / 255.0f, colorMult->red, colorOffs->red);
    offs.blue = ppc::fmadds(scene->colorOffs.blue / 255.0f, colorMult->blue, colorOffs->blue);
    mult.red = scene->colorMult.red * colorMult->red;
    mult.green = scene->colorMult.green * colorMult->green;
    mult.blue = scene->colorMult.blue * colorMult->blue;
    mult.alpha = scene->colorMult.alpha * colorMult->alpha;
    offs.alpha = ppc::fmadds(scene->colorOffs.alpha / 255.0f, colorMult->alpha, colorOffs->alpha);
    offs.green = ppc::fmadds(scene->colorOffs.green / 255.0f, colorMult->green, colorOffs->green);
    _rt2dDepthOfObject* first = RwSListArray<_rt2dDepthOfObject>(scene->data.scene.depths);
    _rt2dDepthOfObject* end = first + scene->data.scene.objectCount;
    if (scene->data.scene.isDirtyDepths != 0) {
        SortDepths(scene);
        scene->data.scene.isDirtyDepths = 0;
    }
    for (_rt2dDepthOfObject* d = first; d != end; ++d) {
        if (changed != 0) d->object->flag |= 2;
        _rt2dObjectRender(d->object, &mult, &offs);
    }
    Rt2dCTMPop();
    return scene;
}

// 0x007198c8 DrawUIRootScene (Rt2dSceneRender): the scene with the root colour transform.
Rt2dObject* Rt2dSceneRender(Rt2dObject* object) { return _rt2dSceneRender(object, &s_rootColorMult, &s_rootColorOffs); }

// 0x007198d8 Rt2dSceneGetChildByIndex: the child pointer when locked, the child in place when unlocked.
Rt2dObject* Rt2dSceneGetChildByIndex(Rt2dObject* scene, RwInt32 index) {
    if ((scene->flag & 1) != 0) return *RwSListEntry<Rt2dObject*>(scene->data.scene.objects, index);
    return RwSListEntry<Rt2dObject>(scene->data.scene.objects, index);
}

// 0x00719948 Rt2dSceneAddChild (the scene locked): null when the list cannot grow.
Rt2dObject* Rt2dSceneAddChild(Rt2dObject* scene, Rt2dObject* object) {
    Rt2dObject** entry = static_cast<Rt2dObject**>(_rwSListGetNewEntry(scene->data.scene.objects, 0x301a3));
    if (entry == nullptr) return nullptr;
    *entry = object;
    ++scene->data.scene.objectCount;
    return scene;
}

// 0x007199d0 Rt2dSceneLock: the children copied into fresh objects (pointer list), the depth list dropped.
Rt2dObject* Rt2dSceneLock(Rt2dObject* scene) {
    if ((scene->flag & 1) != 0) return scene;
    RwSList* list = _rwSListCreate(sizeof(Rt2dObject*), 0x301a3);
    Rt2dObject* child = Children(scene);
    Rt2dObject* end = child + scene->data.scene.objectCount;
    for (; child != end; ++child) {
        Rt2dObject** entry = static_cast<Rt2dObject**>(_rwSListGetNewEntry(list, 0x301a3));
        Rt2dObject* copy = _rt2dObjectAlloc();
        *entry = copy;
        _rt2dObjectMemCopy(copy, child);
    }
    _rwSListDestroy(scene->data.scene.objects);
    _rwSListDestroy(scene->data.scene.depths);
    scene->data.scene.depths = nullptr;
    scene->flag |= 1;
    scene->data.scene.objects = list;
    return scene;
}

// 0x00719b30 _rt2dSceneDestruct_maybe: the depth list, every child's destructor (stopping at the first
// failure), the child list. 0 when anything failed.
RwBool _rt2dSceneDestruct(Rt2dObject* scene) {
    RwBool ok = 1;
    if (scene->data.scene.depths != nullptr) ok = _rwSListDestroy(scene->data.scene.depths);
    Rt2dObject* end = Children(scene) + scene->data.scene.objectCount;
    for (Rt2dObject* child = Children(scene); child != end; ++child) {
        if (ok == 0) continue;
        ok = _rt2dObjectDestruct(child) != 0 ? 1 : 0;
    }
    if (ok == 0) return 0;
    return _rwSListDestroy(scene->data.scene.objects) != 0 ? 1 : 0;
}

// 0x00719c38 Rt2dSceneDestroy
RwBool Rt2dSceneDestroy(Rt2dObject* scene) {
    if (scene == nullptr) return 0;
    const RwBool result = _rt2dSceneDestruct(scene);
    _rt2dObjectFree(scene);
    return result;
}

// 0x00719cb8 _rt2dSceneInit_maybe: objectCount null child pointers (locked), no depth list.
Rt2dObject* _rt2dSceneInit(Rt2dObject* scene, RwInt32 objectCount) {
    scene->data.scene.objectCount = objectCount;
    scene->data.scene.objects = _rwSListCreatePreallocated(sizeof(Rt2dObject*), objectCount, 0x30190);
    if (objectCount != 0) {
        _rwSListGetNewEntries(scene->data.scene.objects, objectCount, 0x30190);
        std::memset(_rwSListGetArray(scene->data.scene.objects), 0, objectCount * sizeof(Rt2dObject*));
    }
    scene->data.scene.isDirtyDepths = 0;
    scene->flag |= 1;
    scene->data.scene.depths = nullptr;
    return scene;
}

// 0x00719f00 _rt2dSceneGetNewChild_maybe (the scene locked): a new object of objectType added as a child.
Rt2dObject* _rt2dSceneGetNewChild(Rt2dObject* scene, RwInt32 objectType) {
    Rt2dObject* object = _rt2dObjectAlloc();
    _rt2dObjectInit(object, objectType);
    Rt2dObject** entry = static_cast<Rt2dObject**>(_rwSListGetNewEntry(scene->data.scene.objects, 0x301a3));
    if (entry != nullptr) {
        *entry = object;
        ++scene->data.scene.objectCount;
    }
    return object;
}

// 0x00719f98 Rt2dSceneUnlock: the child pointers become objects by value (each pointed object copied,
// then freed), and a fresh depth list is built and sorted.
// BUG(original): a null child pointer (a scene read from a stream starts with null pointers) leaves its
// new entry uninitialised; its depth is read for the sort before the children are read (the stream reader
// sorts again afterwards).
Rt2dObject* Rt2dSceneUnlock(Rt2dObject* scene) {
    if ((scene->flag & 1) == 0) return scene;
    RwSList* list = _rwSListCreatePreallocated(sizeof(Rt2dObject), scene->data.scene.objectCount, 0x301a3);
    Rt2dObject** pointer = static_cast<Rt2dObject**>(_rwSListGetArray(scene->data.scene.objects));
    Rt2dObject** end = pointer + scene->data.scene.objectCount;
    for (; pointer != end; ++pointer) {
        Rt2dObject* entry = static_cast<Rt2dObject*>(_rwSListGetNewEntry(list, 0x301a3));
        if (*pointer != nullptr) {
            _rt2dObjectMemCopy(entry, *pointer);
            _rt2dObjectFree(*pointer);
        }
    }
    _rwSListDestroy(scene->data.scene.objects);
    scene->data.scene.objects = list;
    scene->flag &= ~1;
    scene->data.scene.depths = _rwSListCreatePreallocated(sizeof(_rt2dDepthOfObject), scene->data.scene.objectCount, 0x30190);
    if (scene->data.scene.objectCount == 0) return scene;
    _rwSListGetNewEntries(scene->data.scene.depths, scene->data.scene.objectCount, 0x30190);
    FillDepths(scene);
    SortDepths(scene);
    scene->data.scene.isDirtyDepths = 0;
    return scene;
}

// 0x0071a4f8 Rt2dSceneCreate: an empty, locked scene.
Rt2dObject* Rt2dSceneCreate() {
    Rt2dObject* scene = _rt2dObjectAlloc();
    _rt2dObjectInit(scene, rt2DOBJECTTYPESCENE);
    scene->data.scene.objectCount = 0;
    scene->data.scene.objects = _rwSListCreatePreallocated(sizeof(Rt2dObject*), 0, 0x30190);
    scene->flag |= 1;
    scene->data.scene.isDirtyDepths = 0;
    scene->data.scene.depths = nullptr;
    return scene;
}

// 0x0071a808 _rt2dSceneStreamReadTo: the child count, the (locked) child list unlocked into
// uninitialised objects; at the top of a movie (no pool) the shape reps, read into a pool the children
// share and released afterwards; then every child (base, then data) in child order, the results ignored;
// then the depth list rebuilt and sorted.
Rt2dObject* _rt2dSceneStreamReadTo(Rt2dObject* scene, RwStream* stream, _rt2dSceneResourcePool* pool) {
    RwInt32 count = 0;
    if (RwStreamRead(stream, &count, 4) != 4) return nullptr;
    _rt2dSceneInit(scene, count);
    Rt2dSceneUnlock(scene);
    if (pool != nullptr) {
        ChildReadContext context = {stream, pool};
        Rt2dObject* end = Children(scene) + scene->data.scene.objectCount;
        for (Rt2dObject* child = Children(scene); child != end; ++child) {
            SceneStreamReadToChildCallback(child, scene, &context);
        }
    } else {
        RwUInt32 numReps = 0;
        if (Rt2dStreamReadInt32(stream, &numReps, 4) == nullptr) return nullptr;
        _rt2dSceneResourcePool own = {nullptr, numReps};
        if (numReps != 0) {
            own.shapeReps = static_cast<_rt2dShapeRep**>(RwMalloc(numReps * sizeof(_rt2dShapeRep*), 0x30190));
            if (own.shapeReps == nullptr) return nullptr;  // _rwerror(0x80000013, numReps * 4)
            for (RwUInt32 i = 0; i < numReps; ++i) {
                own.shapeReps[i] = _rt2dShapeRepStreamRead(stream);
                if (own.shapeReps[i] == nullptr) return nullptr;  // BUG(original): the reps read so far leak
            }
        }
        ChildReadContext context = {stream, &own};
        Rt2dObject* end = Children(scene) + scene->data.scene.objectCount;
        for (Rt2dObject* child = Children(scene); child != end; ++child) {
            SceneStreamReadToChildCallback(child, scene, &context);
        }
        if (own.numShapeReps != 0) {
            for (RwUInt32 i = 0; i < own.numShapeReps; ++i) _rt2dShapeRepDestroy(own.shapeReps[i]);
            RwFree(own.shapeReps);
        }
    }
    FillDepths(scene);
    SortDepths(scene);
    scene->flag &= ~1;
    return scene;
}

// 0x0071acc0 Rt2dSceneStreamRead (after the caller's RwStreamFindChunk(0x1a5)): a new scene object, its
// base, then its data; a failed data read destroys it.
// BUG(original): a failed base read returns null and leaks the object.
Rt2dObject* Rt2dSceneStreamRead(RwStream* stream) {
    Rt2dObject* scene = _rt2dObjectAlloc();
    _rt2dObjectInit(scene, rt2DOBJECTTYPESCENE);
    if (_rt2dObjectBaseStreamReadTo(scene, stream) == nullptr) return nullptr;
    Rt2dObject* result = _rt2dSceneStreamReadTo(scene, stream, nullptr);
    if (result == nullptr && scene != nullptr) {
        _rt2dSceneDestruct(scene);
        _rt2dObjectFree(scene);
    }
    return result;
}
