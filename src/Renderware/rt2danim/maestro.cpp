// maestro.cpp - RW 3.7 tool/2danim/maestro.c (0x6fb840-0x6fe450): the Maestro movie player (the
// animation nodes, their time stepping and end-of-animation looping, the stream reader), ported from the
// PS3 library code. See Rt2dAnim.h.
//
// A maestro's animations are Rt2dAnimNode entries: node 0 is the root timeline on the maestro's scene,
// node i > 0 a movie clip whose scene is child posInParentScene of its parent node's scene. Node flags:
// bit 0 stopped, bit 1 "the frame changed" (its frame messages are still to post), bit 2 visible in the
// last walk.
#include "Renderware/rt2d/Rt2d.h"
#include "Renderware/rt2danim/Rt2dAnimPrivate.h"
#include "k2000/io/IKFile.h"

namespace {
// The {callback, data} pair Rt2dMaestroForAllVisibleAnimations hands to _rt2dMaestroUserAnimCallBackCB.
struct UserAnimCallBackData {
    Rt2dMaestroAnimationsCallBack callback;
    void* data;
};

constexpr RwReal kMinDeltaTime = 0x1.a36e2ep-14f;  // TOC2-0x3b58 0x38d1b717 (1.0e-4f)
constexpr RwReal kMouseUnset = 4294967296.0f;      // TOC2-0x3b3c 0x4f800000
}  // namespace

static Rt2dMaestro* _rt2dMaestroAnimNodeEndCB(Rt2dMaestro* maestro, Rt2dAnimNode* node, void* data);

// 0x006fb840 _rt2dMaestroUserAnimCallBackCB_maybe (the first function of maestro.c; Ghidra's file split
// puts it at the end of keyframe.c): the user's callback with the node's anim and props.
static Rt2dMaestro* _rt2dMaestroUserAnimCallBackCB(Rt2dMaestro* maestro, Rt2dAnimNode* node, void* data) {
    UserAnimCallBackData* user = static_cast<UserAnimCallBackData*>(data);
    return user->callback(maestro, &node->anim, &node->props, user->data);
}

// 0x006fb898 Rt2dMaestroGetScene
Rt2dObject* Rt2dMaestroGetScene(Rt2dMaestro* maestro) { return maestro->scene; }

// 0x006fb8a0 Rt2dMaestroSetScene_maybe
Rt2dMaestro* Rt2dMaestroSetScene(Rt2dMaestro* maestro, Rt2dObject* scene) {
    maestro->scene = scene;
    return maestro;
}

// 0x006fb8b0 Rt2dMaestroGetBBox_maybe
Rt2dBBox* Rt2dMaestroGetBBox(Rt2dMaestro* maestro) { return &maestro->bbox; }

// 0x006fb8c0 Rt2dMaestroSetBBox_maybe
Rt2dMaestro* Rt2dMaestroSetBBox(Rt2dMaestro* maestro, Rt2dBBox* bbox) {
    maestro->bbox.x = bbox->x;
    maestro->bbox.y = bbox->y;
    maestro->bbox.w = bbox->w;
    maestro->bbox.h = bbox->h;
    return maestro;
}

// 0x006fb8e8 Rt2dMaestroRender_maybe
Rt2dMaestro* Rt2dMaestroRender(Rt2dMaestro* maestro) {
    if (maestro->scene == nullptr) return maestro;
    return Rt2dSceneRender(maestro->scene) != nullptr ? maestro : nullptr;
}

// 0x006fb968 _rt2dMaestroGetAnimNodeByIndex_maybe (no range check)
Rt2dAnimNode* _rt2dMaestroGetAnimNodeByIndex(Rt2dMaestro* maestro, RwInt32 index) {
    return RwSListEntry<Rt2dAnimNode>(maestro->animations, index);
}

// 0x006fb998 Rt2dMaestroAnimNodeUpdateCallBack_maybe (_rt2dMaestroAnimNodeAddDeltaTimeCallBack): data is
// the time step. A node whose frame changed first posts its current cel's frame messages and processes
// the queue; a visible, playing node then advances by the step, posting the new cel's frame messages
// when the keyframe changed.
// BUG(original): the cel is the cel array's entry at the keyframe index without a check (index -1 before
// the first keyframe, or an empty cel list, reads outside the array).
static Rt2dMaestro* _rt2dMaestroAnimNodeAddDeltaTimeCallBack(Rt2dMaestro* maestro, Rt2dAnimNode* node,
                                                             void* data) {
    const RwReal deltaTime = *static_cast<RwReal*>(data);
    Rt2dAnim* anim = &node->anim;
    const RwInt32 prevIndex = Rt2dAnimGetPrevFrameIndex(anim);
    if ((node->flag & 2) != 0) {
        node->flag &= ~2;
        const Rt2dCel* cel = RwSListArray<Rt2dCel>(node->celList->cel) + prevIndex;
        if (cel->messageListIndex >= 0) _rt2dMaestroMessageListPostByIndex(maestro, cel->messageListIndex);
        Rt2dMaestroProcessMessages(maestro);
        _rt2dApplyMouseState(maestro, &maestro->prevMouse);
    }
    if (Rt2dObjectIsVisible(node->props.scene) == 0) return maestro;
    if ((node->flag & 1) != 0) return maestro;
    if (Rt2dAnimAddDeltaTime(anim, &node->props, deltaTime) == nullptr) return nullptr;
    const RwInt32 newIndex = Rt2dAnimGetPrevFrameIndex(anim);
    if (prevIndex == newIndex) return maestro;
    const Rt2dCel* cel = RwSListArray<Rt2dCel>(node->celList->cel) + newIndex;
    if (cel->messageListIndex < 0) return maestro;
    _rt2dMaestroMessageListPostByIndex(maestro, cel->messageListIndex);
    return maestro;
}

// 0x006fbc40 _rt2dMaestroAnimTimeUpdateCB_maybe
static Rt2dMaestro* _rt2dMaestroAnimTimeUpdateCB(Rt2dMaestro* maestro, Rt2dAnimNode* node, void* /*data*/) {
    return Rt2dAnimTimeUpdate(&node->anim, &node->props) != nullptr ? maestro : nullptr;
}

// 0x006fbca0 Rt2dMaestroForAllAnimations_maybe: currAnimIndex is the node's index during its callback;
// a callback that does not return the maestro stops the walk (null, currAnimIndex left as it was).
Rt2dMaestro* Rt2dMaestroForAllAnimations(Rt2dMaestro* maestro, Rt2dMaestroAnimationsCallBack callback, void* data) {
    const RwInt32 count = _rwSListGetNumEntries(maestro->animations);
    if (count > 0) {
        Rt2dAnimNode* node = RwSListArray<Rt2dAnimNode>(maestro->animations);
        for (RwInt32 i = 0; i < count; ++i, ++node) {
            maestro->currAnimIndex = i;
            if (callback(maestro, &node->anim, &node->props, data) != maestro) return nullptr;
        }
    }
    maestro->currAnimIndex = -1;
    return maestro;
}

// 0x006fbdc8 Rt2dMaestroForAllAnimations (Ghidra) = _rt2dMaestroForAllAnimNode: the same walk with the
// node itself.
static Rt2dMaestro* _rt2dMaestroForAllAnimNode(Rt2dMaestro* maestro, Rt2dMaestroAnimNodeCallBack callback,
                                               void* data) {
    const RwInt32 count = _rwSListGetNumEntries(maestro->animations);
    if (count > 0) {
        Rt2dAnimNode* node = RwSListArray<Rt2dAnimNode>(maestro->animations);
        for (RwInt32 i = 0; i < count; ++i, ++node) {
            maestro->currAnimIndex = i;
            if (callback(maestro, node, data) != maestro) return nullptr;
        }
    }
    maestro->currAnimIndex = -1;
    return maestro;
}

// 0x006fbee8 Rt2dMaestroForAllVisibleAnimations (Ghidra) = _rt2dMaestroForAllVisibleAnimNode: every node
// whose scene is visible gets flag bit 2 and the callback, the others lose bit 2. (The PS3 also looks up
// the parent node of each node with a parent and drops the result.)
Rt2dMaestro* _rt2dMaestroForAllVisibleAnimNode(Rt2dMaestro* maestro, Rt2dMaestroAnimNodeCallBack callback,
                                               void* data) {
    const RwInt32 count = _rwSListGetNumEntries(maestro->animations);
    if (count > 0) {
        Rt2dAnimNode* node = RwSListArray<Rt2dAnimNode>(maestro->animations);
        for (RwInt32 i = 0; i < count; ++i, ++node) {
            maestro->currAnimIndex = i;
            if (Rt2dObjectIsVisible(node->props.scene) != 0) {
                node->flag |= 4;
                if (callback(maestro, node, data) != maestro) return nullptr;
            } else {
                node->flag &= ~4;
            }
        }
    }
    maestro->currAnimIndex = -1;
    return maestro;
}

// 0x006fc030 Rt2dMaestroAddDeltaTime_maybe. The frame length comes from the first playing node that has
// a keyframe ahead (next - prev), or, past its end, from its last two keyframes; the time then advances
// in steps that stop at every frame boundary: each step is applied to every visible node
// (_rt2dMaestroAnimNodeAddDeltaTimeCallBack), the queue is processed after a step that reached a
// boundary, and the end-of-animation pass (_rt2dMaestroAnimNodeEndCB) runs after every step. Steps stop
// when what is left is 1e-4 or less.
Rt2dMaestro* Rt2dMaestroAddDeltaTime(Rt2dMaestro* maestro, RwReal deltaTime) {
    Rt2dAnimNode* const end = RwSListEnd<Rt2dAnimNode>(maestro->animations);
    Rt2dAnimNode* node = RwSListArray<Rt2dAnimNode>(maestro->animations);
    RwReal frameLength = 0.0f;
    RwReal currentTime = 0.0f;
    RwReal nextTime = 0.0f;
    for (;; ++node) {
        if (node == end) return maestro;
        if ((node->flag & 1) != 0) continue;
        Rt2dAnim* anim = &node->anim;
        if (anim->next != nullptr) {
            const RwReal prevTime = Rt2dAnimGetPrevFrameTime(anim);
            currentTime = Rt2dAnimGetCurrentTime(anim);
            nextTime = Rt2dAnimGetNextFrameTime(anim);
            frameLength = nextTime - prevTime;
            break;
        }
        const RwInt32 prevIndex = Rt2dAnimGetPrevFrameIndex(anim);
        if (prevIndex > 0) {
            const RwReal beforeTime = Rt2dAnimGetKeyFrameListByIndex(anim, prevIndex - 1)->time;
            nextTime = Rt2dAnimGetPrevFrameTime(anim);
            const RwReal time = Rt2dAnimGetCurrentTime(anim);
            frameLength = nextTime - beforeTime;
            currentTime = time - frameLength;
            break;
        }
    }
    if (frameLength == 0.0f) return maestro;
    if (deltaTime <= kMinDeltaTime) return maestro;
    for (;;) {
        RwReal step;
        RwInt32 crossed = 1;
        Rt2dMaestro* result;
        const RwReal toNext = nextTime - currentTime;
        if (toNext < deltaTime) {
            deltaTime = deltaTime - toNext;
            currentTime = currentTime + toNext;
            step = toNext;
            nextTime = nextTime + frameLength;
            result = _rt2dMaestroForAllVisibleAnimNode(maestro, _rt2dMaestroAnimNodeAddDeltaTimeCallBack, &step);
        } else {
            step = deltaTime;
            deltaTime = 0.0f;
            crossed = 0;
            result = _rt2dMaestroForAllVisibleAnimNode(maestro, _rt2dMaestroAnimNodeAddDeltaTimeCallBack, &step);
        }
        if (result == nullptr) return nullptr;
        if (crossed != 0) {
            Rt2dMaestroProcessMessages(maestro);
            _rt2dApplyMouseState(maestro, &maestro->prevMouse);
        }
        _rt2dMaestroForAllVisibleAnimNode(maestro, _rt2dMaestroAnimNodeEndCB, nullptr);
        if (deltaTime <= kMinDeltaTime) return maestro;
    }
}

// 0x006fc2a8 Rt2dMaestroUpdateAnimations_maybe: Rt2dAnimTimeUpdate on every visible node.
Rt2dMaestro* Rt2dMaestroUpdateAnimations(Rt2dMaestro* maestro) {
    if (maestro->animations == nullptr) return maestro;
    return _rt2dMaestroForAllVisibleAnimNode(maestro, _rt2dMaestroAnimTimeUpdateCB, nullptr) != nullptr ? maestro
                                                                                                     : nullptr;
}

// 0x006fc328 _rt2dMaestroForAllVisibleAnimationsUser_maybe (Rt2dMaestroForAllVisibleAnimations): the
// walk's result is dropped; the maestro is returned.
Rt2dMaestro* Rt2dMaestroForAllVisibleAnimations(Rt2dMaestro* maestro, Rt2dMaestroAnimationsCallBack callback,
                                                void* data) {
    UserAnimCallBackData user{callback, data};
    _rt2dMaestroForAllVisibleAnimNode(maestro, _rt2dMaestroUserAnimCallBackCB, &user);
    return maestro;
}

// 0x006fc618 Rt2dMaestro_GetAnimNodeAnim_maybe (Rt2dMaestroGetAnimationsByIndex)
Rt2dAnim* Rt2dMaestroGetAnimationsByIndex(Rt2dMaestro* maestro, RwInt32 index) {
    return &RwSListEntry<Rt2dAnimNode>(maestro->animations, index)->anim;
}

// 0x006fc648 Rt2dMaestroGetAnimPropsByIndex_maybe
Rt2dAnimProps* Rt2dMaestroGetAnimPropsByIndex(Rt2dMaestro* maestro, RwInt32 index) {
    return &RwSListEntry<Rt2dAnimNode>(maestro->animations, index)->props;
}

// 0x006fc678 _rt2dMaestroInit. invWinH/invWinW/winAspectRatio are left as they are (the PS3 too):
// Rt2dMaestroProcessMessages sets them before anything reads them.
Rt2dMaestro* _rt2dMaestroInit(Rt2dMaestro* maestro) {
    maestro->currAnimIndex = -1;
    maestro->flag = 0;
    maestro->version = 0;
    maestro->animations = nullptr;
    maestro->labels = nullptr;
    maestro->byteBucket = nullptr;
    maestro->scene = nullptr;
    maestro->buttons = nullptr;
    maestro->animations = _rwSListCreate(static_cast<RwInt32>(sizeof(Rt2dAnimNode)), kRt2dAnimHint);
    _rt2dMaestroCreateStringLabels(maestro);
    _rt2dMaestroCreateButtons(maestro);
    _rt2dMaestroCreateMessageList(maestro);
    _rt2dMaestroCreateMessageQueue(maestro);
    RwSList* bucket = _rt2dByteBucketCreate();
    maestro->prevMouse.position.y = kMouseUnset;
    maestro->byteBucket = bucket;
    maestro->prevMouse.position.x = kMouseUnset;
    maestro->bbox.h = 0.0f;
    maestro->prevMouse.button = 0;
    maestro->bbox.x = 0.0f;
    maestro->bbox.y = 0.0f;
    maestro->bbox.w = 0.0f;
    maestro->messageHandler = Rt2dMessageHandlerDefaultCallBack;
    _rt2dStateTransTableInit(&maestro->stateTransTable[0][0][0][0]);
    return maestro;
}

// 0x006fc778 Rt2dMaestroCreate
Rt2dMaestro* Rt2dMaestroCreate() {
    Rt2dMaestro* maestro = static_cast<Rt2dMaestro*>(
        RwFreeListAlloc(g_rt2dAnimFreeLists[kRt2dAnimFreeListMaestro], kRt2dMaestroHint));
    if (maestro != nullptr) _rt2dMaestroInit(maestro);
    return maestro;
}

// 0x006fc8a0 Rt2dMaestro_DestroyAnimNode_maybe (_rt2dAnimNodeDestruct as a node callback)
static Rt2dMaestro* _rt2dMaestroDestroyAnimNode(Rt2dMaestro* maestro, Rt2dAnimNode* node, void* /*data*/) {
    _rt2dAnimDestruct(&node->anim, &node->props);
    node->posInParentScene = -1;
    node->flag = 0;
    node->parent = -1;
    if (node->celList != nullptr) _rt2dCelListDestroy(node->celList);
    _rt2dAnimPropsDestruct(&node->props);
    node->celList = nullptr;
    return maestro;
}

// 0x006fc940 Rt2dMaestro_ResolveAnimNodeObject_maybe (Rt2dMaestroGetAnimSceneByIndex): the scene object of
// node index (the maestro's scene for index 0 and below). The PS3 unrolls the recursion eight levels.
Rt2dObject* Rt2dMaestroGetAnimSceneByIndex(Rt2dMaestro* maestro, RwInt32 index) {
    if (index <= 0) return maestro->scene;
    Rt2dAnimNode* node = RwSListEntry<Rt2dAnimNode>(maestro->animations, index);
    Rt2dObject* parentScene = node->parent < 1 ? maestro->scene : Rt2dMaestroGetAnimSceneByIndex(maestro, node->parent);
    return Rt2dSceneGetChildByIndex(parentScene, node->posInParentScene);
}

// 0x006fcc20 _rt2dMaestroAnimationsStreamRead: the node count, then per node: flag 2, parent and
// position -1, a new cel list and its stream data, parent, position, the 0x1a9 chunk header, the props
// on the node's scene (node 0: the maestro's scene) and the anim.
Rt2dMaestro* _rt2dMaestroAnimationsStreamRead(Rt2dMaestro* maestro, RwStream* stream) {
    RwInt32 count = 0;
    if (RwStreamReadInt32(stream, &count, 4) == nullptr) return nullptr;
    if (count < 1) return maestro;
    if (maestro->animations == nullptr) {
        maestro->animations = _rwSListCreate(static_cast<RwInt32>(sizeof(Rt2dAnimNode)), kRt2dAnimHint);
        if (maestro->animations == nullptr) return nullptr;
    }
    Rt2dAnimNode* node =
        static_cast<Rt2dAnimNode*>(_rwSListGetNewEntries(maestro->animations, count, kRt2dAnimHint));
    if (node == nullptr) return nullptr;
    for (RwInt32 i = 0; i < count; ++i, ++node) {
        node->posInParentScene = -1;
        node->parent = -1;
        node->flag = 2;
        node->celList = _rt2dCelListCreate();
        if (node->celList == nullptr) return nullptr;
        if (_rt2dCelListStreamRead(maestro, node->celList, stream) == nullptr) return nullptr;
        if (RwStreamReadInt32(stream, &node->parent, 4) == nullptr) return nullptr;
        if (RwStreamReadInt32(stream, &node->posInParentScene, 4) == nullptr) return nullptr;
        RwChunkHeaderInfo info;
        if (RwStreamReadChunkHeaderInfo(stream, &info) == nullptr) return nullptr;
        Rt2dObject* scene;
        if (i > 0) {
            Rt2dAnimNode* self = RwSListEntry<Rt2dAnimNode>(maestro->animations, i);
            scene = Rt2dSceneGetChildByIndex(Rt2dMaestroGetAnimSceneByIndex(maestro, self->parent),
                                             self->posInParentScene);
        } else {
            scene = maestro->scene;
        }
        if (_rt2dAnimPropsInit(&node->props, scene) == nullptr) return nullptr;
        if (_rt2dAnimStreamRead(&node->anim, stream, &node->props) == nullptr) return nullptr;
    }
    RwSListEntry<Rt2dAnimNode>(maestro->animations, 0);  // the PS3 looks up entry 0 and drops it
    return maestro;
}

// 0x006fcea8 _rt2dMaestroInitAnimNodePostRead_maybe: a clip's scene is hidden (the keyframes show it);
// every button of every cel is put in its up state; the anim is reset and stepped to its first keyframe.
// BUG(original): the cels are looked up for every keyframe index without checking the cel count.
static Rt2dMaestro* _rt2dMaestroInitAnimNodePostRead(Rt2dMaestro* maestro, Rt2dAnimNode* node, void* /*data*/) {
    Rt2dObject* scene;
    if (node->parent == -1 && node->posInParentScene == -1) {
        scene = maestro->scene;
    } else {
        Rt2dObject* parentScene;
        if (node->parent == -1 || node->parent <= 0) {
            parentScene = maestro->scene;
        } else {
            Rt2dAnimNode* parent = RwSListEntry<Rt2dAnimNode>(maestro->animations, node->parent);
            parentScene = Rt2dSceneGetChildByIndex(Rt2dMaestroGetAnimSceneByIndex(maestro, parent->parent),
                                                   parent->posInParentScene);
        }
        scene = Rt2dSceneGetChildByIndex(parentScene, node->posInParentScene);
        Rt2dObjectSetVisible(scene, 0);
    }
    Rt2dAnim* anim = &node->anim;
    const RwInt32 count = Rt2dAnimGetNumKeyFrameLists(anim);
    for (RwInt32 i = 0; i < count; ++i) {
        Rt2dCel* cel = _rt2dCelListGetCelByIndex(node->celList, i);
        if (cel == nullptr) continue;
        const RwInt32 numButtons = _rwSListGetNumEntries(cel->buttonIndices);
        RwInt32* buttonIndex = RwSListArray<RwInt32>(cel->buttonIndices);
        for (RwInt32 k = 0; k < numButtons; ++k, ++buttonIndex) {
            _rt2dButtonReset(_rt2dMaestroGetButtonByIndex(maestro, *buttonIndex), scene);
        }
    }
    Rt2dAnimReset(anim, &node->props);
    Rt2dAnimAddDeltaFrameIndex(anim, &node->props, 1);
    return maestro;
}

// 0x006fd0a8 _rt2dMaestroAnimNodeEndCB_maybe (EndLooping): a playing node at or past its last keyframe
// (or any node when data is non-zero) goes back to keyframe 0 and is marked changed; its child clips
// (later nodes whose parent it is) are looped the same way (forced) and hidden.
static Rt2dMaestro* _rt2dMaestroAnimNodeEndCB(Rt2dMaestro* maestro, Rt2dAnimNode* node, void* data) {
    if ((node->flag & 1) == 0) {
        if (!(node->anim.currentTime >= Rt2dAnimGetFinalKeyFrameListTime(&node->anim))) {  // cror gt|eq
            if (data == nullptr) return maestro;
        }
    } else if (data == nullptr) {
        return maestro;
    }
    Rt2dAnimNode* const end = RwSListEnd<Rt2dAnimNode>(maestro->animations);
    const RwInt32 index = static_cast<RwInt32>(node - RwSListArray<Rt2dAnimNode>(maestro->animations));
    Rt2dAnimGotoKeyFrameListByIndex(&node->anim, &node->props, 0);
    node->flag |= 2;
    for (Rt2dAnimNode* child = node + 1; child != end; ++child) {
        if (child->parent != index) continue;
        Rt2dObject* parentScene;
        if (index <= 0) {
            parentScene = maestro->scene;
        } else {
            Rt2dAnimNode* self = RwSListEntry<Rt2dAnimNode>(maestro->animations, index);
            parentScene = Rt2dSceneGetChildByIndex(Rt2dMaestroGetAnimSceneByIndex(maestro, self->parent),
                                                   self->posInParentScene);
        }
        Rt2dObject* childScene = Rt2dSceneGetChildByIndex(parentScene, child->posInParentScene);
        _rt2dMaestroAnimNodeEndCB(maestro, child, Rt2dWordAsPointer(1));
        Rt2dObjectSetVisible(childScene, 0);
    }
    return maestro;
}

// 0x006fdc60 Rt2dMaestroStreamRead: a new maestro when none is given; the stream version (kept in a
// local: the maestro's version stays 0), the bbox, string labels, the scene (when the count word is
// positive: RwStreamFindChunk(0x1a5) and Rt2dSceneStreamRead), buttons, message list, message store and
// animations; then the post-read pass over every node (currAnimIndex = its index; -1 after).
// The PS3 leaks a maestro it created when a read fails; a node pass that fails returns the maestro with
// currAnimIndex left at that node.
Rt2dMaestro* Rt2dMaestroStreamRead(Rt2dMaestro* maestro, RwStream* stream) {
    if (maestro == nullptr) {
        maestro = static_cast<Rt2dMaestro*>(
            RwFreeListAlloc(g_rt2dAnimFreeLists[kRt2dAnimFreeListMaestro], kRt2dMaestroHint));
        if (maestro == nullptr) return nullptr;
        _rt2dMaestroInit(maestro);
    }
    RwInt32 version = 0;
    if (RwStreamReadInt32(stream, &version, 4) == nullptr) return nullptr;
    if (RwStreamReadReal(stream, &maestro->bbox, 0x10) == nullptr) return nullptr;
    if (_rt2dMaestroStringLabelsStreamRead(maestro, stream) == nullptr) return nullptr;
    RwInt32 sceneCount = 0;
    if (RwStreamReadInt32(stream, &sceneCount, 4) == nullptr) return nullptr;
    if (sceneCount > 0) {
        RwUInt32 length = 0, chunkVersion = 0;
        if (RwStreamFindChunk(stream, 0x1a5, &length, &chunkVersion) == 0) return nullptr;
        maestro->scene = Rt2dSceneStreamRead(stream);
        if (maestro->scene == nullptr) return nullptr;
    }
    if (_rt2dMaestroButtonsStreamRead(maestro, stream) == nullptr) return nullptr;
    if (_rt2dMaestroMessageListStreamRead(maestro, stream) == nullptr) return nullptr;
    if (_rt2dMaestroMessageStoreStreamRead(maestro, stream) == nullptr) return nullptr;
    if (_rt2dMaestroAnimationsStreamRead(maestro, stream) == nullptr) return nullptr;
    const RwInt32 count = _rwSListGetNumEntries(maestro->animations);
    if (count > 0) {
        Rt2dAnimNode* node = RwSListArray<Rt2dAnimNode>(maestro->animations);
        for (RwInt32 i = 0; i < count; ++i, ++node) {
            maestro->currAnimIndex = i;
            if (_rt2dMaestroInitAnimNodePostRead(maestro, node, nullptr) != maestro) return maestro;
        }
    }
    maestro->currAnimIndex = -1;
    return maestro;
}

// 0x006fdff8 Rt2dMaestro_Destruct_maybe (_rt2dMaestroDestruct)
static RwBool _rt2dMaestroDestruct(Rt2dMaestro* maestro) {
    if (maestro->animations != nullptr) {
        _rt2dMaestroForAllAnimNode(maestro, _rt2dMaestroDestroyAnimNode, nullptr);
        _rwSListDestroy(maestro->animations);
        maestro->animations = nullptr;
    }
    if (maestro->labels != nullptr) _rt2dMaestroDestroyStringLabels(maestro);
    if (maestro->buttons != nullptr) _rt2dMaestroDestroyButtons(maestro);
    if (maestro->messageList != nullptr) _rt2dMaestroDestroyMessageList(maestro);
    if (maestro->scene != nullptr) Rt2dSceneDestroy(maestro->scene);
    if (maestro->messageQueue != nullptr) _rt2dMaestroDestroyMessageQueue(maestro);
    if (maestro->byteBucket != nullptr) {
        _rt2dByteBucketDestroy(maestro->byteBucket);
        maestro->byteBucket = nullptr;
    }
    return 1;
}

// 0x006fe190 Rt2dMaestroDestroy
RwBool Rt2dMaestroDestroy(Rt2dMaestro* maestro) {
    _rt2dMaestroDestruct(maestro);
    RwFreeListFree(g_rt2dAnimFreeLists[kRt2dAnimFreeListMaestro], maestro);
    return 1;
}

// 0x006fe450 _rt2dMessageQueueSetDefaultSize_maybe (Rt2dMessageQueueSetDefaultSize). The PS3 function
// only stores the size; r3 still holds it on return.
RwBool Rt2dMessageQueueSetDefaultSize(RwInt32 size) {
    g_rt2dMessageQueueDefaultSize = size;
    return size;
}
