// Rt2dAnim.h - the RenderWare 3.7 2D animation toolkit (tool/2danim: Rt2dAnim, keyframes, the Maestro
// movie player, messages, buttons, cels, string labels), ported from the PS3 library code
// (0x6f5f80-0x703a60, library TOC 0xc25974): the functions other units call. Each original source file
// has its .cpp here (anim, gstate, handler, keyframe, maestro, message, props, strlabel, button, cel);
// file-local functions stay in their .cpp, the ones the files share are in Rt2dAnimPrivate.h.
//
// Names: RW 3.7's (XXL2 build, same code) where the PS3 function matches; the PS3 address and the Ghidra
// name are on each declaration.
#pragma once
#include "Renderware/rt2d/Rt2dTypes.h"
#include "Renderware/rwcore/RwTypes.h"

struct RwStream;

typedef Rt2dMaestro* (*Rt2dMaestroAnimationsCallBack)(Rt2dMaestro* maestro, Rt2dAnim* anim, Rt2dAnimProps* props,
                                                      void* pData);
// Rt2dAnimOnEndReachedCallBack: (anim, props, the time left over past the end).
typedef Rt2dAnim* (*Rt2dAnimOnEndReachedCallBack)(Rt2dAnim* anim, Rt2dAnimProps* props, RwReal remainingDeltaTime);

// --- 2danim/gstate.c ---------------------------------------------------------------------------------
// 0x006f7cf0 _rt2dFreeListsCreate_maybe (Rt2dAnimOpen): the eleven free lists. Rt2dDevice_Init (0x6c9b8)
// calls it, then Rt2dMessageQueueSetDefaultSize(0x100).
RwBool Rt2dAnimOpen();
// 0x006f7c18 _rt2dFreeListsDestroy_maybe (Rt2dAnimClose)
RwBool Rt2dAnimClose();
// 0x006f7c08 Rt2dAnimSetFreeListCreateParams_maybe
void Rt2dAnimSetFreeListCreateParams(RwInt32 blockSize, RwInt32 numBlocksToPrealloc);

// --- 2danim/anim.c -----------------------------------------------------------------------------------
// 0x006f5f80 Rt2dAnimGetCurrentTime
RwReal Rt2dAnimGetCurrentTime(Rt2dAnim* anim);
// 0x006f5f88 Rt2dAnimGetFinalKeyFrameListTime_maybe
RwReal Rt2dAnimGetFinalKeyFrameListTime(Rt2dAnim* anim);
// 0x006f5f98 Rt2dAnimGetPrevFrameTime_maybe / 0x006f5fb8 Rt2dAnimGetNextFrameTime_maybe
RwReal Rt2dAnimGetPrevFrameTime(Rt2dAnim* anim);
RwReal Rt2dAnimGetNextFrameTime(Rt2dAnim* anim);
// 0x006f6028 Rt2dAnimGetPrevFrameIndex_maybe / 0x006f6078 Rt2dAnimGetNextFrameIndex_maybe
RwInt32 Rt2dAnimGetPrevFrameIndex(Rt2dAnim* anim);
RwInt32 Rt2dAnimGetNextFrameIndex(Rt2dAnim* anim);
// 0x006f60e8 Rt2dAnimGetNumKeyFrameLists_maybe
RwInt32 Rt2dAnimGetNumKeyFrameLists(Rt2dAnim* anim);
// 0x006f6210 Rt2dAnimGetKeyFrameListByIndex_maybe
Rt2dKeyFrameList* Rt2dAnimGetKeyFrameListByIndex(Rt2dAnim* anim, RwInt32 frameIndex);
// 0x006f5fe0 Rt2dAnimIsInterpolated_maybe / 0x006f5ff0 Rt2dAnimSetInterpolate_maybe (anim flag bit 1)
RwBool Rt2dAnimIsInterpolated(Rt2dAnim* anim);
Rt2dAnim* Rt2dAnimSetInterpolate(Rt2dAnim* anim, RwBool interpolate);
// 0x006f6e80 Rt2dAnimGotoKeyFrameListByIndex_maybe
Rt2dAnim* Rt2dAnimGotoKeyFrameListByIndex(Rt2dAnim* anim, Rt2dAnimProps* props, RwInt32 targetFrameIndex);
// 0x006f7428 Rt2dAnimAddDeltaTime_maybe
Rt2dAnim* Rt2dAnimAddDeltaTime(Rt2dAnim* anim, Rt2dAnimProps* props, RwReal deltaTime);
// 0x006f6390 Rt2dAnim_ResetPlayback_maybe (Rt2dAnimReset)
Rt2dAnim* Rt2dAnimReset(Rt2dAnim* anim, Rt2dAnimProps* props);
// 0x006f68c8 _rt2dAnimStreamRead_maybe: into an Rt2dAnimNode's anim. The PS3 caller passes the node's
// props in r5; the function does not use them.
Rt2dAnim* _rt2dAnimStreamRead(Rt2dAnim* anim, RwStream* stream, Rt2dAnimProps* props);

// --- 2danim/keyframe.c -------------------------------------------------------------------------------
// 0x006fb7e0 Rt2dKeyFrameListStreamRead_maybe (after the caller's RwStreamFindChunk(0x1b0))
Rt2dKeyFrameList* Rt2dKeyFrameListStreamRead(RwStream* stream);
// 0x006f87a8 Rt2dKeyFrameListApply_maybe: interpolates the pending frame state towards this keyframe
// list by alpha (only for 0 < alpha < 1), then applies the frame state to the objects.
Rt2dKeyFrameList* Rt2dKeyFrameListApply(Rt2dKeyFrameList* keyframeList, Rt2dAnimProps* props, RwReal alpha);
// 0x006fa218 Rt2dKeyFrameListAdvance_maybe: copies this keyframe list's changes into the frame state.
Rt2dKeyFrameList* Rt2dKeyFrameListAdvance(Rt2dKeyFrameList* keyframeList, Rt2dAnimProps* props);

// --- 2danim/maestro.c --------------------------------------------------------------------------------
// 0x006fc778 Rt2dMaestroCreate
Rt2dMaestro* Rt2dMaestroCreate();
// 0x006fe190 Rt2dMaestroDestroy
RwBool Rt2dMaestroDestroy(Rt2dMaestro* maestro);
// 0x006fdc60 Rt2dMaestroStreamRead (after the caller's RwStreamFindChunk(0x1b1)); maestro may be null.
Rt2dMaestro* Rt2dMaestroStreamRead(Rt2dMaestro* maestro, RwStream* stream);
// 0x006fb898 Rt2dMaestroGetScene / 0x006fb8a0 Rt2dMaestroSetScene_maybe
Rt2dObject* Rt2dMaestroGetScene(Rt2dMaestro* maestro);
Rt2dMaestro* Rt2dMaestroSetScene(Rt2dMaestro* maestro, Rt2dObject* scene);
// 0x006fb8b0 Rt2dMaestroGetBBox_maybe / 0x006fb8c0 Rt2dMaestroSetBBox_maybe
Rt2dBBox* Rt2dMaestroGetBBox(Rt2dMaestro* maestro);
Rt2dMaestro* Rt2dMaestroSetBBox(Rt2dMaestro* maestro, Rt2dBBox* bbox);
// 0x006fc030 Rt2dMaestroAddDeltaTime_maybe
Rt2dMaestro* Rt2dMaestroAddDeltaTime(Rt2dMaestro* maestro, RwReal deltaTime);
// 0x006fc2a8 Rt2dMaestroUpdateAnimations_maybe
Rt2dMaestro* Rt2dMaestroUpdateAnimations(Rt2dMaestro* maestro);
// 0x006fb8e8 Rt2dMaestroRender_maybe
Rt2dMaestro* Rt2dMaestroRender(Rt2dMaestro* maestro);
// 0x006fbca0 Rt2dMaestroForAllAnimations_maybe
Rt2dMaestro* Rt2dMaestroForAllAnimations(Rt2dMaestro* maestro, Rt2dMaestroAnimationsCallBack callback, void* data);
// 0x006fc328 _rt2dMaestroForAllVisibleAnimationsUser_maybe (Rt2dMaestroForAllVisibleAnimations): the
// callback gets (maestro, anim, props, data) for every animation whose scene is visible. (Ghidra's
// "Rt2dMaestroForAllVisibleAnimations" 0x6fbee8 is the internal per-node walk it wraps.)
Rt2dMaestro* Rt2dMaestroForAllVisibleAnimations(Rt2dMaestro* maestro, Rt2dMaestroAnimationsCallBack callback,
                                                void* data);
// Old name of the same function (foundation header): kept for callers written against it.
inline Rt2dMaestro* _rt2dMaestroForAllVisibleAnimationsUser(Rt2dMaestro* maestro,
                                                            Rt2dMaestroAnimationsCallBack callback, void* data) {
    return Rt2dMaestroForAllVisibleAnimations(maestro, callback, data);
}
// 0x006fc618 Rt2dMaestro_GetAnimNodeAnim_maybe (Rt2dMaestroGetAnimationsByIndex)
Rt2dAnim* Rt2dMaestroGetAnimationsByIndex(Rt2dMaestro* maestro, RwInt32 index);
// 0x006fc648 Rt2dMaestroGetAnimPropsByIndex_maybe
Rt2dAnimProps* Rt2dMaestroGetAnimPropsByIndex(Rt2dMaestro* maestro, RwInt32 index);
// 0x006fc940 Rt2dMaestro_ResolveAnimNodeObject_maybe (Rt2dMaestroGetAnimSceneByIndex): the scene object
// of animation index (the maestro's scene for index 0 and below).
Rt2dObject* Rt2dMaestroGetAnimSceneByIndex(Rt2dMaestro* maestro, RwInt32 index);

// --- 2danim/message.c, handler.c ---------------------------------------------------------------------
// 0x006ff430 Rt2dMaestroProcessMessages_maybe
Rt2dMaestro* Rt2dMaestroProcessMessages(Rt2dMaestro* maestro);
// 0x006ffe80 Rt2dMaestroAddMessages (Rt2dMaestroPostMessages): queues num messages (tell-target
// messages retarget the ones after them; index < 0 means the current animation).
Rt2dMaestro* Rt2dMaestroPostMessages(Rt2dMaestro* maestro, Rt2dMessage* message, RwInt32 num);
// 0x006fe450 _rt2dMessageQueueSetDefaultSize_maybe (Rt2dMessageQueueSetDefaultSize). The PS3 function
// returns nothing (it only stores the size).
RwBool Rt2dMessageQueueSetDefaultSize(RwInt32 size);
// 0x006f7f48 Rt2dMaestroGetMessageHandler_maybe / 0x006f7f50 Rt2dMaestroSetMessageHandler_maybe
Rt2dMessageHandlerCallBack Rt2dMaestroGetMessageHandler(Rt2dMaestro* maestro);
Rt2dMaestro* Rt2dMaestroSetMessageHandler(Rt2dMaestro* maestro, Rt2dMessageHandlerCallBack handler);
// 0x006f7f60 Rt2dMessageHandlerDefaultCallBack
Rt2dMessage* Rt2dMessageHandlerDefaultCallBack(Rt2dMaestro* maestro, Rt2dMessage* message);

// --- 2danim/strlabel.c -------------------------------------------------------------------------------
// 0x00700ba0 Rt2dMaestro_FindStringLabel_maybe (Rt2dMaestroFindStringLabel)
Rt2dStringLabel* Rt2dMaestroFindStringLabel(Rt2dMaestro* maestro, Rt2dStringLabelType entityType,
                                            const RwChar* lookupName, RwInt32* index);
// 0x00700b20 Rt2dMaestro_GetStringLabelByIndex_maybe (Rt2dMaestroGetStringLabelByIndex)
Rt2dStringLabel* Rt2dMaestroGetStringLabelByIndex(Rt2dMaestro* maestro, RwInt32 index);
// 0x00700ae8 Rt2dMaestro_GetLabelString_maybe (Rt2dMaestroGetStringLabelName): the label's name in the
// byte bucket.
const RwChar* Rt2dMaestroGetStringLabelName(Rt2dMaestro* maestro, Rt2dStringLabel* strLabel);
