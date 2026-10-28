// RtAnim.h - RenderWare 3.7 RtAnim (animations and their interpolation schemes), ported from the PS3 build's
// library code (TOC 0xc25974), animation checkpoint step 1. RW 3.7's rtanim.h gives the names and the layouts; the PS3 build
// differs in two places: the scheme record has a second key frame size (+0xc) and an animation has a second
// key frame count (+0x8, stream version 0x101), both the same as the first for the standard scheme.
//   RtAnimAnimationStreamRead 0x707d58, RtAnimAnimationCreate 0x708118, RtAnimRegisterInterpolationScheme
//   0x706a68, RtAnimGetInterpolatorInfo 0x706b70, RtAnimInitialize 0x707870 (the plugin; its open 0x707920 and
//   close 0x7078b8).
// Layouts: the PS3 offsets are in the comments and asserted in the 32-bit builds; the x64 build has 8-byte
// pointers (callbacks, interpInfo, prevFrame), so every size is a sizeof, never a PS3 byte count.
// Animation checkpoint, step 2: the interpolator (RtAnimInterpolator: Create 0x706e90, Destroy 0x706f68, SetCurrentAnim 0x706fa8,
// AddAnimTime 0x708298, SubAnimTime 0x708870, SetCurrentTime 0x708c70, the callbacks 0x707188 / 0x707198, the scheme
// switch 0x707998, CreateSubInterpolator 0x707c50, Blend 0x7071a8, AddTogether 0x7072a0, Copy 0x707820). The PS3
// interpolator is 0x50 bytes (one word more than RW 3.7's: the second key frame size at +0x2c), and its key frame walk
// steps by the first or the second key frame size as the frame time's lowest bit says. Not ported because nothing in
// the game calls them (their only references are RW's own function table): AddSubInterpolator 0x707388,
// BlendSubInterpolator 0x7074b0, MakeDelta 0x708cd0.
#pragma once
#include <cstdint>

#include "Renderware/rwcore/RwTypes.h"
#include "k2000/core/Layout.h"

struct RwStream;
class IKSerializable;
struct RtAnimAnimation;

// The scheme callbacks (rtanim.h). Pointers into PS3 code in the original (the table at 0xcfa04c).
typedef void (*RtAnimKeyFrameApplyCallBack)(void* result, void* voidIFrame);
typedef void (*RtAnimKeyFrameBlendCallBack)(void* voidOut, void* voidIn1, void* voidIn2, RwReal alpha);
// PS3: the interpolate callback gets the node index as a sixth argument (r8; RW 3.7 has five). Scheme 1 ignores it.
typedef void (*RtAnimKeyFrameInterpolateCallBack)(void* voidOut, void* voidIn1, void* voidIn2, RwReal time,
                                                  void* customData, RwInt32 nodeIndex);
typedef void (*RtAnimKeyFrameAddCallBack)(void* voidOut, void* voidIn1, void* voidIn2);
typedef void (*RtAnimKeyFrameMulRecipCallBack)(void* voidFrame, void* voidStart);
typedef RtAnimAnimation* (*RtAnimKeyFrameStreamReadCallBack)(RwStream* stream, RtAnimAnimation* animation);
typedef RwBool (*RtAnimKeyFrameStreamWriteCallBack)(const RtAnimAnimation* animation, RwStream* stream);
typedef RwInt32 (*RtAnimKeyFrameStreamGetSizeCallBack)(const RtAnimAnimation* animation);

// RtAnimInterpolatorInfo (PS3 0x34 bytes, the registered scheme table's entry size).
struct RtAnimInterpolatorInfo {
    RwInt32 typeID;                                       // +0x00 1 RpHAnim standard, 2 compressed
    RwInt32 interpKeyFrameSize;                           // +0x04 the interpolated key frame
    RwInt32 animKeyFrameSize;                             // +0x08 the animation's key frame
    RwInt32 animKeyFrameSize2;                            // +0x0c PS3: the second key frame array's element size (_maybe)
    RtAnimKeyFrameApplyCallBack keyFrameApplyCB;          // +0x10
    RtAnimKeyFrameBlendCallBack keyFrameBlendCB;          // +0x14
    RtAnimKeyFrameInterpolateCallBack keyFrameInterpolateCB;  // +0x18
    RtAnimKeyFrameAddCallBack keyFrameAddCB;              // +0x1c
    RtAnimKeyFrameMulRecipCallBack keyFrameMulRecipCB;    // +0x20
    RtAnimKeyFrameStreamReadCallBack keyFrameStreamReadCB;    // +0x24
    RtAnimKeyFrameStreamWriteCallBack keyFrameStreamWriteCB;  // +0x28
    RtAnimKeyFrameStreamGetSizeCallBack keyFrameStreamGetSizeCB;  // +0x2c
    RwInt32 customDataSize;                               // +0x30 per animation (CAnimationManager adds the sector entry)
};
DOTD_ASSERT_SIZE(RtAnimInterpolatorInfo, 0x34);
DOTD_ASSERT_OFFSET(RtAnimInterpolatorInfo, keyFrameStreamReadCB, 0x24);
DOTD_ASSERT_OFFSET(RtAnimInterpolatorInfo, customDataSize, 0x30);

// The header every scheme's key frame starts with (rtanim.h RtAnimKeyFrameHeader).
struct RtAnimKeyFrameHeader {
    RtAnimKeyFrameHeader* prevFrame;  // +0x00 the previous key frame of the same node
    RwReal time;                      // +0x04
};

// RtAnimAnimation (PS3 header 0x1c bytes; the key frames follow it in the same allocation, then the custom data):
// RtAnimAnimationStreamRead 0x707d58 / RtAnimAnimationCreate 0x708118.
struct RtAnimAnimation {
    RtAnimInterpolatorInfo* interpInfo;  // +0x00 the scheme
    RwInt32 numFrames;                   // +0x04
    RwInt32 numFrames2;                  // +0x08 PS3 (stream version 0x101): a second key frame array after the first
    RwInt32 flags;                       // +0x0c
    RwReal duration;                     // +0x10 seconds (CKAnmKeyFrameController reads it at +0x10: Anim_GetDuration 0x7ab60)
    void* pFrames;                       // +0x14 the first key frames, right behind this header
    void* customData;                    // +0x18 behind both key frame arrays; null without custom data
};
DOTD_ASSERT_SIZE(RtAnimAnimation, 0x1c);
DOTD_ASSERT_OFFSET(RtAnimAnimation, duration, 0x10);
DOTD_ASSERT_OFFSET(RtAnimAnimation, pFrames, 0x14);
DOTD_ASSERT_OFFSET(RtAnimAnimation, customData, 0x18);

// The 0x24 bytes CSectorAnimation_LoadEntry_maybe (0x79898) reads from the IKFile into the animation: the last
// customDataSize bytes' tail (CAnimationManager's constructor added them to the schemes 1 and 2 custom data size).
struct RtAnimSectorEntryData {
    uint32_t words00[4];    // +0x00 read third (16 bytes, each swapped)
    uint32_t word10;        // +0x10 read first: the animation's bounding sphere radius (a float; CKAnmKeyFrameController
                            //       GetBoundingSphere_maybe 0x7ae60 copies it)
    uint32_t words14[3];    // +0x14 read second (12 bytes, each swapped): the bounding sphere's centre (3 floats)
    IKSerializable* ref20;  // +0x20 a handle, read last
};
DOTD_ASSERT_SIZE(RtAnimSectorEntryData, 0x24);

// 0x00079898's addressing: (animation + 0x18) + (interpInfo + 0x30) - 0x24.
inline RtAnimSectorEntryData* RtAnimSectorEntry(RtAnimAnimation* animation) {
    return reinterpret_cast<RtAnimSectorEntryData*>(static_cast<uint8_t*>(animation->customData) +
                                                    animation->interpInfo->customDataSize - sizeof(RtAnimSectorEntryData));
}

// The registered schemes: at most 16 (RtAnimRegisterInterpolationScheme).
constexpr RwInt32 kRtAnimMaxInterpolators = 16;

// 0x00707870 RtAnimInitialize (the plugin registration) with its open 0x707920 (the animation free list is the host
// heap here) and 0x007078b8 close: the scheme table starts empty.
RwBool RtAnimInitialize();
// 0x00706a68 RtAnimRegisterInterpolationScheme: copies `info` into the table; 0 when the table is full or the type
// is registered already.
RwBool RtAnimRegisterInterpolationScheme(const RtAnimInterpolatorInfo* info);
// 0x00706b70 RtAnimGetInterpolatorInfo: the table entry of a type id, or null.
RtAnimInterpolatorInfo* RtAnimGetInterpolatorInfo(RwInt32 typeID);

// 0x00707d58 RtAnimAnimationStreamRead, after RwStreamFindChunk(0x1b): version (< 0x102), scheme type, the key frame
// count (and the second count from version 0x101), flags, duration; one allocation (header, key frames, custom
// data); then the scheme's StreamRead (its result is not looked at). Null for an unknown scheme or a short read.
RtAnimAnimation* RtAnimAnimationStreamRead(RwStream* stream);
// 0x00708118 RtAnimAnimationCreate: an animation of `typeID` with `numFrames` key frames (second count 0), the
// key frames unread.
RtAnimAnimation* RtAnimAnimationCreate(RwReal duration, RwInt32 typeID, RwInt32 numFrames, RwInt32 flags);

// 0x00706da0 RtAnimAnimationDestroy_maybe: the animation back to the engine heap. 1.
RwBool RtAnimAnimationDestroy(RtAnimAnimation* animation);
// 0x00706e30 RtAnimAnimationGetNumNodes: the key frames before the first one whose previous frame is the first
// key frame (the node count); the walk steps by the scheme's first or second key frame size (the time's lowest bit).
RwInt32 RtAnimAnimationGetNumNodes(const RtAnimAnimation* animation);

// The header every interpolated key frame starts with (rtanim.h RtAnimInterpFrameHeader): the two key frames the node
// is between.
struct RtAnimInterpFrameHeader {
    void* keyFrame1;  // +0x00
    void* keyFrame2;  // +0x04
};

struct RtAnimInterpolator;
// RtAnimCallBack (rtanim.h): null from a callback clears it.
typedef RtAnimInterpolator* (*RtAnimCallBack)(RtAnimInterpolator* animInstance, void* data);

// RtAnimInterpolator (PS3 0x50 bytes, the interpolated key frames behind it: RtAnimInterpolatorCreate allocates
// 0x50 + numNodes * maxInterpKeyFrameSize). Names from rtanim.h; +0x2c is the PS3's second key frame size.
struct RtAnimInterpolator {
    RtAnimAnimation* pCurrentAnim;                            // +0x00
    RwReal currentTime;                                       // +0x04
    void* pNextFrame;                                         // +0x08 the next key frame the walk takes
    RtAnimCallBack pAnimCallBack;                             // +0x0c
    void* pAnimCallBackData;                                  // +0x10
    RwReal animCallBackTime;                                  // +0x14 -1 at creation
    RtAnimCallBack pAnimLoopCallBack;                         // +0x18
    void* pAnimLoopCallBackData;                              // +0x1c
    RwInt32 maxInterpKeyFrameSize;                            // +0x20 the creation size (a PS3 byte count)
    RwInt32 currentInterpKeyFrameSize;                        // +0x24 the frame stride (host bytes)
    RwInt32 currentAnimKeyFrameSize;                          // +0x28 -1 until an animation is set
    RwInt32 currentAnimKeyFrameSize2;                         // +0x2c PS3: the second key frame size (_maybe), -1
    RwInt32 numNodes;                                         // +0x30
    RwBool isSubInterpolator;                                 // +0x34
    RwInt32 offsetInParent;                                   // +0x38
    RtAnimInterpolator* parentAnimation;                      // +0x3c itself for a main interpolator
    RtAnimKeyFrameApplyCallBack keyFrameApplyCB;              // +0x40
    RtAnimKeyFrameBlendCallBack keyFrameBlendCB;              // +0x44
    RtAnimKeyFrameInterpolateCallBack keyFrameInterpolateCB;  // +0x48
    RtAnimKeyFrameAddCallBack keyFrameAddCB;                  // +0x4c
};
DOTD_ASSERT_SIZE(RtAnimInterpolator, 0x50);
DOTD_ASSERT_OFFSET(RtAnimInterpolator, maxInterpKeyFrameSize, 0x20);
DOTD_ASSERT_OFFSET(RtAnimInterpolator, numNodes, 0x30);
DOTD_ASSERT_OFFSET(RtAnimInterpolator, keyFrameApplyCB, 0x40);

// rtANIMGETINTERPFRAME: node `nodeIndex`'s interpolated key frame (behind the header, currentInterpKeyFrameSize apart).
inline void* RtAnimInterpolatorGetInterpFrame(RtAnimInterpolator* interpolator, RwInt32 nodeIndex) {
    return reinterpret_cast<uint8_t*>(interpolator + 1) + nodeIndex * interpolator->currentInterpKeyFrameSize;
}

// The host size of an interpolated key frame of `ps3Size` PS3 bytes: its header holds two pointers (8 bytes on the PS3),
// so the x64 build adds the pointers' growth and pointer alignment. The same value in the 32-bit builds.
constexpr RwInt32 RtAnimHostInterpKeyFrameSize(RwInt32 ps3Size) {
    return static_cast<RwInt32>(((static_cast<size_t>(ps3Size) + 2 * (sizeof(void*) - 4)) + alignof(void*) - 1) &
                                ~(alignof(void*) - 1));
}

// 0x00706e90 RtAnimInterpolatorCreate(numNodes, maxInterpKeyFrameSize): numNodes interpolated frames of the size
// (host: RtAnimHostInterpKeyFrameSize), no animation, callback time -1, its own parent.
RtAnimInterpolator* RtAnimInterpolatorCreate(RwInt32 numNodes, RwInt32 maxInterpKeyFrameSize);
// 0x00706f68 RtAnimInterpolatorDestroy: back to the engine heap.
void RtAnimInterpolatorDestroy(RtAnimInterpolator* interpolator);
// 0x00706fa8 RtAnimInterpolatorSetCurrentAnim: the animation and its scheme's sizes and callbacks, time 0, every node
// between its first two key frames (interpolated at time 0), the walk at the third set. 1.
RwBool RtAnimInterpolatorSetCurrentAnim(RtAnimInterpolator* interpolator, RtAnimAnimation* animation);
// 0x00707188 RtAnimInterpolatorSetAnimLoopCallBack
void RtAnimInterpolatorSetAnimLoopCallBack(RtAnimInterpolator* interpolator, RtAnimCallBack callBack, void* data);
// 0x00707198 RtAnimInterpolatorSetAnimCallBack
void RtAnimInterpolatorSetAnimCallBack(RtAnimInterpolator* interpolator, RtAnimCallBack callBack, RwReal time,
                                       void* data);
// 0x00707998 RtAnimInterpolatorSetKeyFrameCallBacks (RtAnimInterpolatorSetKeyFrameCallBacks): the four
// callbacks of the registered scheme `typeID`. 0 for an unknown scheme.
RwBool RtAnimInterpolatorSetKeyFrameCallBacks(RtAnimInterpolator* interpolator, RwInt32 typeID);
// 0x00708298 RtAnimInterpolatorAddAnimTime: time forward (nothing for time <= 0), the loop at the duration (the
// animation set again), the key frame walk, every node interpolated, then the callbacks. 1.
RwBool RtAnimInterpolatorAddAnimTime(RtAnimInterpolator* interpolator, RwReal time);
// 0x00708870 RtAnimInterpolatorSubAnimTime: time backwards (the walk goes back per node; under 0 the animation
// is set again and played forward to the wrapped time). 1.
RwBool RtAnimInterpolatorSubAnimTime(RtAnimInterpolator* interpolator, RwReal time);
// 0x00708c70 RtAnimInterpolatorSetCurrentTime: Add or Sub by the difference. 1.
RwBool RtAnimInterpolatorSetCurrentTime(RtAnimInterpolator* interpolator, RwReal time);
// 0x00707c50 RtAnimInterpolatorCreateSubInterpolator_maybe: an interpolator for numNodes nodes from startNode of the
// parent (maxInterpKeyFrameSize -1: the parent's).
RtAnimInterpolator* RtAnimInterpolatorCreateSubInterpolator(RtAnimInterpolator* parentAnim, RwInt32 startNode,
                                                            RwInt32 numNodes, RwInt32 maxInterpKeyFrameSize);
// 0x007071a8 RtAnimInterpolatorBlend (RtAnimInterpolatorBlend): out's blend callback per node. 1.
RwBool RtAnimInterpolatorBlend(RtAnimInterpolator* outAnim, RtAnimInterpolator* inAnim1, RtAnimInterpolator* inAnim2,
                               RwReal alpha);
// 0x007072a0 RtAnimInterpolatorAddTogether (RtAnimInterpolatorAddTogether): out's add callback per node. 1.
RwBool RtAnimInterpolatorAddTogether(RtAnimInterpolator* outAnim, RtAnimInterpolator* inAnim1,
                                     RtAnimInterpolator* inAnim2);
// 0x00707820 RtAnimInterpolatorCopy (RtAnimInterpolatorCopy): the interpolated frames (out's count
// and size). 1.
RwBool RtAnimInterpolatorCopy(RtAnimInterpolator* outAnim, RtAnimInterpolator* inAnim);
