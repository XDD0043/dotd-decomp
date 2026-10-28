// props.cpp - RW 3.7 tool/2danim/props.c (0x7004f0-0x7008a0 by address; Ghidra's file split puts them
// at the end of message.c): an animation's props (its scene, the directory of the scene's children, the
// frame state), ported from the PS3 library code. See Rt2dAnim.h.
#include "Renderware/rt2d/Rt2d.h"
#include "Renderware/rt2danim/Rt2dAnimPrivate.h"

// 0x007004f0 Rt2dAnimGetKeyFrameListTime_maybe (_rt2dAnimPropsGet2dObjectByIndex): directory entry index.
Rt2dObject* _rt2dAnimPropsGet2dObjectByIndex(Rt2dAnimProps* props, RwInt32 index) {
    return *RwSListEntry<Rt2dObject*>(props->directory, index);
}

// 0x007005a8 Rt2dAnimState_Deinit_maybe (_rt2dAnimPropsDestruct)
Rt2dAnimProps* _rt2dAnimPropsDestruct(Rt2dAnimProps* props) {
    props->scene = nullptr;
    if (props->directory != nullptr) _rwSListDestroy(props->directory);
    props->directory = nullptr;
    if (props->sceneCurrentState != nullptr) _rwSListDestroy(props->sceneCurrentState);
    props->sceneCurrentState = nullptr;
    return props;
}

// 0x007006c8 _rt2dSListAppendPointerCB_maybe: Rt2dSceneForAllChildren callback, appends the child.
static Rt2dObject* _rt2dSListAppendPointerCB(Rt2dObject* object, Rt2dObject* /*parent*/, void* data) {
    *static_cast<Rt2dObject**>(_rwSListGetNewEntry(static_cast<RwSList*>(data), kRt2dAnimHint)) = object;
    return object;
}

// 0x00700628 Rt2dAnimState_Init_maybe (_rt2dAnimPropsInit): the directory is the scene's children in
// Rt2dSceneForAllChildren's order; one frame state per child.
Rt2dAnimProps* _rt2dAnimPropsInit(Rt2dAnimProps* props, Rt2dObject* scene) {
    props->scene = scene;
    props->directory = _rwSListCreate(static_cast<RwInt32>(sizeof(Rt2dObject*)), kRt2dAnimHint);
    if (props->directory == nullptr) return nullptr;
    Rt2dSceneForAllChildren(props->scene, _rt2dSListAppendPointerCB, props->directory);
    props->labels = nullptr;
    props->sceneCurrentState = _rt2dAnimPropsCreateSceneCurrentState(props);
    return props;
}
