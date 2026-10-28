// Rt2dAnimPrivate.h - what the tool/2danim source files share among themselves (RW's toolkit-private
// headers: the globals block, the free lists, the internal functions one file calls in another).
// Nothing outside src/Renderware/rt2danim includes this; the cross-unit API is Rt2dAnim.h.
//
// Struct and member names are RW 3.7's (XXL2 DWARF). The PS3 names in comments are the Ghidra names.
#pragma once
#include <cstdint>
#include <cstring>

#include "Renderware/rt2danim/Rt2dAnim.h"
#include "Renderware/rwcore/RwSList.h"

struct RwStream;

// --- gstate.c: the toolkit globals (XXL2 Rt2dAnimGlobals) ---------------------------------------------
// The eleven free lists _rt2dFreeListsCreate (0x6f7cf0) creates, in their PS3 order (in place at
// 0xcf9ec0 + 0x24 * index). The PS3 entry sizes are in the comments; the ports use the native sizeof.
enum Rt2dAnimFreeList : int32_t {
    kRt2dAnimFreeListAnim = 0,             // 0xcf9ec0, 0x1c Rt2dAnim
    kRt2dAnimFreeListButton = 1,           // 0xcf9ee4, 0x90 Rt2dButton
    kRt2dAnimFreeListMaestro = 2,          // 0xcf9f08, 0x158 Rt2dMaestro (hint 0x301b1)
    kRt2dAnimFreeListStringLabel = 3,      // 0xcf9f2c, 0x10 Rt2dStringLabel
    kRt2dAnimFreeListMessage = 4,          // 0xcf9f50, 0x10 Rt2dMessage
    kRt2dAnimFreeListMessageQueue = 5,     // 0xcf9f74, 0x10 Rt2dMessageQueue
    kRt2dAnimFreeListObjectUpdate = 6,     // 0xcf9f98, 0xa0 Rt2dAnimObjectUpdate
    kRt2dAnimFreeListKeyFrameList = 7,     // 0xcf9fbc, 0xc Rt2dKeyFrameList (hint 0x301b0)
    kRt2dAnimFreeListProps = 8,            // 0xcf9fe0, 0x10 Rt2dAnimProps
    kRt2dAnimFreeListCelList = 9,          // 0xcfa004, 0x8 Rt2dCelList
    kRt2dAnimFreeListCel = 10,             // 0xcfa028, 0x10 Rt2dCel
    kRt2dAnimFreeListCount = 11,
};
extern RwFreeList* g_rt2dAnimFreeLists[kRt2dAnimFreeListCount];
// 0x00ced574 _rt2dAnimOpenCalled: set by Rt2dAnimOpen.
extern RwBool g_rt2dAnimOpenCalled;
// 0x00ced578 _rt2dAnimOnEndReachedCallBack: called by Rt2dAnimAddDeltaTime when the time runs past an
// end. Null in the EBOOT's data and in the running game (main menu, read live 2026-10-17).
extern Rt2dAnimOnEndReachedCallBack g_rt2dAnimOnEndReachedCallBack;
// 0x00c458b0 the message queue size new maestros get (EBOOT data 0x40; Rt2dDevice_Init sets 0x100).
extern RwInt32 g_rt2dMessageQueueDefaultSize;

// The RW hint words the toolkit passes to its allocations (rwID_2DANIM / rwID_2DMAESTRO / keyframes).
constexpr RwUInt32 kRt2dAnimHint = 0x301a9;
constexpr RwUInt32 kRt2dMaestroHint = 0x301b1;
constexpr RwUInt32 kRt2dKeyFrameHint = 0x301b0;

// --- stream helpers ----------------------------------------------------------------------------------
// 0x00757128 RwStreamReadInt32 / 0x00757200 RwStreamReadReal: RwStreamRead, then the words to native
// order. They fail only when RwStreamRead returns 0 (a short read succeeds, a zero-length read fails).
// The files are little-endian like the hosts, so the swap is the identity here.
inline RwStream* RwStreamReadInt32(RwStream* stream, void* ints, RwUInt32 numBytes);
inline RwStream* RwStreamReadReal(RwStream* stream, void* reals, RwUInt32 numBytes);
// 0x00756768 RwMemNative32: little-endian file words to native order (the identity on these hosts).
inline void* RwMemNative32(void* mem, RwUInt32 /*size*/) { return mem; }

// Rt2dStringLabel::internalData is read from the stream as a 4-byte word (an animation or frame index)
// and used as one; these keep the word's value on 64-bit hosts too.
inline RwInt32 Rt2dStringLabelData(const Rt2dStringLabel* label) {
    return static_cast<RwInt32>(reinterpret_cast<intptr_t>(label->internalData));
}
inline void* Rt2dWordAsPointer(RwInt32 word) { return reinterpret_cast<void*>(static_cast<intptr_t>(word)); }

// The animation-node callback type (_rt2dMaestroForAllAnimNode / _rt2dMaestroForAllVisibleAnimNode).
typedef Rt2dMaestro* (*Rt2dMaestroAnimNodeCallBack)(Rt2dMaestro* maestro, Rt2dAnimNode* node, void* data);

// --- anim.c ------------------------------------------------------------------------------------------
// 0x006f6240 Rt2dAnim_StepKeyFrameLists_maybe (Rt2dAnimAddDeltaFrameIndex)
Rt2dAnim* Rt2dAnimAddDeltaFrameIndex(Rt2dAnim* anim, Rt2dAnimProps* props, RwInt32 deltaFrame);
// 0x006f67d0 Rt2dAnimTimeUpdate_maybe
Rt2dAnim* Rt2dAnimTimeUpdate(Rt2dAnim* anim, Rt2dAnimProps* props);
// 0x006f7350 Rt2dAnimDestruct_maybe (_rt2dAnimDestruct)
Rt2dAnim* _rt2dAnimDestruct(Rt2dAnim* anim, Rt2dAnimProps* props);

// --- keyframe.c --------------------------------------------------------------------------------------
// 0x006f98f0 Rt2dAnimState_CreateFrameStateList_maybe: the props' sceneCurrentState list.
RwSList* _rt2dAnimPropsCreateSceneCurrentState(Rt2dAnimProps* props);
// 0x006face8 _rt2dKeyFrameListStreamReadTo_maybe
Rt2dKeyFrameList* _rt2dKeyFrameListStreamReadTo(RwStream* stream, Rt2dKeyFrameList* keyframeList);
// 0x006f9828 Rt2dKeyFrameListDestroy_maybe
RwBool Rt2dKeyFrameListDestroy(Rt2dKeyFrameList* keyframeList);

// --- maestro.c ---------------------------------------------------------------------------------------
// 0x006fb968 _rt2dMaestroGetAnimNodeByIndex_maybe
Rt2dAnimNode* _rt2dMaestroGetAnimNodeByIndex(Rt2dMaestro* maestro, RwInt32 index);
// 0x006fbee8 Rt2dMaestroForAllVisibleAnimations (Ghidra) = _rt2dMaestroForAllVisibleAnimNode
Rt2dMaestro* _rt2dMaestroForAllVisibleAnimNode(Rt2dMaestro* maestro, Rt2dMaestroAnimNodeCallBack callback,
                                               void* data);
// 0x006fc678 _rt2dMaestroInit
Rt2dMaestro* _rt2dMaestroInit(Rt2dMaestro* maestro);

// --- message.c ---------------------------------------------------------------------------------------
// 0x006ff1a8 Rt2dMaestro_CreateMessageLists_maybe (_rt2dMaestroCreateMessageList)
Rt2dMaestro* _rt2dMaestroCreateMessageList(Rt2dMaestro* maestro);
// 0x006ffa10 Rt2dMaestro_CreateFrameMessageList_maybe (_rt2dMaestroCreateMessageQueue)
Rt2dMaestro* _rt2dMaestroCreateMessageQueue(Rt2dMaestro* maestro);
// 0x006ffb28 Rt2dMaestro_DestroyMessageLists_maybe (_rt2dMaestroDestroyMessageList)
Rt2dMaestro* _rt2dMaestroDestroyMessageList(Rt2dMaestro* maestro);
// 0x006ff940 Rt2dMaestro_DestroyFrameMessageList_maybe (_rt2dMaestroDestroyMessageQueue)
Rt2dMaestro* _rt2dMaestroDestroyMessageQueue(Rt2dMaestro* maestro);
// 0x006ffc08 _rt2dMaestroMessageStoreStreamRead / 0x006ffd68 _rt2dMaestroMessageListStreamRead
Rt2dMaestro* _rt2dMaestroMessageStoreStreamRead(Rt2dMaestro* maestro, RwStream* stream);
Rt2dMaestro* _rt2dMaestroMessageListStreamRead(Rt2dMaestro* maestro, RwStream* stream);
// 0x007001f8 Rt2dMaestroAddFrameMessages_maybe (_rt2dMaestroMessageListPostByIndex)
Rt2dMaestro* _rt2dMaestroMessageListPostByIndex(Rt2dMaestro* maestro, RwInt32 index);
// 0x006f7f40 KStub_Nop_6f7f40 (_rt2dApplyMouseState: empty on the PS3)
void _rt2dApplyMouseState(Rt2dMaestro* maestro, Rt2dMaestroMouseState* mouseState);

// --- props.c -----------------------------------------------------------------------------------------
// 0x00700628 Rt2dAnimState_Init_maybe (_rt2dAnimPropsInit)
Rt2dAnimProps* _rt2dAnimPropsInit(Rt2dAnimProps* props, Rt2dObject* scene);
// 0x007005a8 Rt2dAnimState_Deinit_maybe (_rt2dAnimPropsDestruct)
Rt2dAnimProps* _rt2dAnimPropsDestruct(Rt2dAnimProps* props);
// 0x007004f0 Rt2dAnimGetKeyFrameListTime_maybe (_rt2dAnimPropsGet2dObjectByIndex)
Rt2dObject* _rt2dAnimPropsGet2dObjectByIndex(Rt2dAnimProps* props, RwInt32 index);

// --- strlabel.c --------------------------------------------------------------------------------------
// 0x00700ce8 Rt2dMaestro_CreateStringLabelList_maybe (_rt2dMaestroCreateStringLabels)
Rt2dMaestro* _rt2dMaestroCreateStringLabels(Rt2dMaestro* maestro);
// 0x007010c0 Rt2dMaestro_DestroyStringLabelList_maybe (_rt2dMaestroDestroyStringLabels)
Rt2dMaestro* _rt2dMaestroDestroyStringLabels(Rt2dMaestro* maestro);
// 0x00701410 _rt2dMaestroStringLabelsStreamRead
Rt2dMaestro* _rt2dMaestroStringLabelsStreamRead(Rt2dMaestro* maestro, RwStream* stream);
// The byte bucket (an RwSList of bytes holding the label names).
// 0x00701858 Rt2dStringBuffer_Create_maybe (_rt2dByteBucketCreate)
RwSList* _rt2dByteBucketCreate();
// 0x00701830 Rt2dStringBuffer_Destroy_maybe (_rt2dByteBucketDestroy)
RwBool _rt2dByteBucketDestroy(RwSList* bucket);

// --- button.c ----------------------------------------------------------------------------------------
// 0x007019e0 Rt2dMaestro_InitDefaultLimits_maybe (_rt2dStateTransTableInit)
Rt2dStateTransData* _rt2dStateTransTableInit(Rt2dStateTransData* table);
// 0x00701b18 Rt2dElem90_ApplyButtonStateVisibility_maybe (_rt2dButtonReset_maybe)
Rt2dButton* _rt2dButtonReset(Rt2dButton* button, Rt2dObject* scene);
// 0x00701c68 Rt2dMaestro_GetElem90_maybe (_rt2dMaestroGetButtonByIndex)
Rt2dButton* _rt2dMaestroGetButtonByIndex(Rt2dMaestro* maestro, RwInt32 index);
// 0x00701cf0 Rt2dMaestro_CreateElem90List_maybe (_rt2dMaestroCreateButtons)
Rt2dMaestro* _rt2dMaestroCreateButtons(Rt2dMaestro* maestro);
// 0x00701c98 Rt2dMaestro_DestroyElem90List_maybe (_rt2dMaestroDestroyButtons)
Rt2dMaestro* _rt2dMaestroDestroyButtons(Rt2dMaestro* maestro);
// 0x007021f8 _rt2dMaestroButtonsStreamRead
Rt2dMaestro* _rt2dMaestroButtonsStreamRead(Rt2dMaestro* maestro, RwStream* stream);

// --- cel.c -------------------------------------------------------------------------------------------
// 0x00702850 Rt2dAnimNodeGroupList_GetByIndex_maybe (_rt2dCelListGetCelByIndex)
Rt2dCel* _rt2dCelListGetCelByIndex(Rt2dCelList* celList, RwInt32 index);
// 0x00702648 Rt2dMaestro_GetAnimNodeGroupValue_maybe: the label index of a cel's button.
Rt2dCelList* _rt2dCelListGetButtonLabelIndex(Rt2dMaestro* maestro, Rt2dCelList* celList, RwInt32 celIndex,
                                             RwInt32 buttonIndex, RwInt32* strLabelIndex);
// 0x00703600 Rt2dAnimNodeGroupList_Create_maybe (_rt2dCelListCreate)
Rt2dCelList* _rt2dCelListCreate();
// 0x007034c8 Rt2dAnimNodeGroupList_Destroy_maybe (_rt2dCelListDestroy)
RwBool _rt2dCelListDestroy(Rt2dCelList* celList);
// 0x00703838 _rt2dCelListStreamRead
Rt2dCelList* _rt2dCelListStreamRead(Rt2dMaestro* maestro, Rt2dCelList* celList, RwStream* stream);

// --- inline bodies -----------------------------------------------------------------------------------
#include "Renderware/rwcore/RwStream.h"

inline RwStream* RwStreamReadInt32(RwStream* stream, void* ints, RwUInt32 numBytes) {
    if (RwStreamRead(stream, ints, numBytes) == 0) return nullptr;  // _rwerror(0x8000001a) + RwErrorSet
    RwMemNative32(ints, numBytes);
    return stream;
}
inline RwStream* RwStreamReadReal(RwStream* stream, void* reals, RwUInt32 numBytes) {
    if (RwStreamRead(stream, reals, numBytes) == 0) return nullptr;
    RwMemNative32(reals, numBytes);
    return stream;
}
