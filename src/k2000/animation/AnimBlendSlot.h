// AnimBlendSlot.h - the animation blend slot embedded in CAnimatedNode (+0x34; 0x18 bytes with its vtable:
// CAnimatedNode's constructor stores 0xb16560, then 0xb16530). Original units: AnimBlendSlot.cpp
// (0x78d18-0x7a018, the thunks) and AnimBlendSlot_2.cpp (0x7a710-0x7aad0). No XXL2 class; the names are
// the Ghidra ones (AnimBlendSlot_*), fields ours.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"

class IKFile;
class IKSerializable;

class AnimBlendSlot {
public:
    AnimBlendSlot() {}  // inlined in CAnimatedNode_Construct 0xc9480: the vtables only
    virtual ~AnimBlendSlot() {}  // 0x009996e0 / 0x00999710 (inline)

    // 0x0007a730 AnimBlendSlot_Load: only K_LEVEL_PLATEFORMS: the controller, the four state words cleared
    // and the controller's word +0x58 cleared (a CKBlenderController's m_unk58).
    int32_t Load(IKFile* file, int32_t type);

    // 0x0007a710 AnimBlendSlot_Init (vt+0x08, through AnimBlendSlot_InitThunk 0x00079ff0): the controller, three
    // of the four state words cleared (+0x14 is left alone).
    void Init(IKSerializable* controller);

    // 0x0007a848 AnimBlendSlot_StartCrossfade: the other controller becomes the active one (+0x10 toggled) unless a
    // crossfade is running; `duration` seconds to blend (+0x08, +0x0c), the mode (+0x14: 0 cut, 1 and 2 blend) returned
    // (a blend in the middle of one is mode 1; modes 0 and 1 first give the controller faded away the current pose:
    // KBase98D_vf50, a cut when no evaluated pose is found).
    uint32_t StartCrossfade(double duration, uint32_t mode);
    // 0x0007a7f8 AnimBlendSlot_SetWeight_maybe: no crossfade, the blender's weight, the first controller active.
    void SetWeight(float weight);
    // 0x00079e10 AnimBlendSlot_SetAnimPairAndWeight_maybe: both controllers' animations (dictionary words) at their start
    // times, then SetWeight.
    void SetAnimPairAndWeight(uint32_t word1, uint32_t word2, float start1, float start2, float weight);
    // 0x0007a9d0 AnimBlendSlot_UpdateCrossfade: the blend one step (`dt`): 1 while it runs, 0 when over or none.
    bool UpdateCrossfade(double dt);
    // 0x00079f30 AnimBlendSlot_AdvanceInactiveTrack_maybe (vt+0x10): the crossfade stepped and, in mode 2, the controller
    // being faded away kept running by `dt`.
    bool AdvanceInactiveTrack(double dt);
    // 0x00079ea0 AnimBlendSlot_CrossfadeToAnim: StartCrossfade, then the animation (a dictionary word) set on the active
    // controller at `start` seconds. Returns the mode.
    uint32_t CrossfadeToAnim(double blend, double start, uint32_t word, uint32_t mode);

    IKSerializable* m_pController;  // +0x04 a CKBlenderController (the Ghidra struct of CAnimatedNode)
    float m_unk08;                  // +0x08 Load sets 0: the crossfade length
    float m_unk0c;                  // +0x0c Load sets 0: the crossfade time left
    uint32_t m_unk10;               // +0x10 Load sets 0
    uint32_t m_unk14;               // +0x14 Load sets 0
};
DOTD_ASSERT_SIZE(AnimBlendSlot, 0x18);
DOTD_ASSERT_OFFSET(AnimBlendSlot, m_pController, 0x04);
DOTD_ASSERT_OFFSET(AnimBlendSlot, m_unk14, 0x14);

// 0x00079d98 AnimBlendSlot_LoadThunk: AnimBlendSlot_Load, then 1.
int32_t AnimBlendSlot_LoadThunk(AnimBlendSlot* slot, IKFile* file, int32_t type);

// A 0x24-byte animation key block (Ghidra AnimFloatBlock9: nine words): four words, a float, a vector and
// an object reference. The cinematic stream's channel types 0 and 2 load one per channel.
struct AnimFloatBlock9 {
    uint32_t m_aui32Unk00[4];  // +0x00 read third (one 16-byte read, each word swapped)
    float m_unk10;             // +0x10 read first
    float m_av14[3];           // +0x14 read second (one 12-byte read, each word swapped)
    IKSerializable* m_pUnk20;  // +0x20 a reference, read last
};
DOTD_ASSERT_SIZE(AnimFloatBlock9, 0x24);
DOTD_ASSERT_OFFSET(AnimFloatBlock9, m_unk10, 0x10);
DOTD_ASSERT_OFFSET(AnimFloatBlock9, m_av14, 0x14);
DOTD_ASSERT_OFFSET(AnimFloatBlock9, m_pUnk20, 0x20);

// 0x00079418 AnimFloatBlock9_LoadByteSwapped_maybe (no type test, nothing returned).
void AnimFloatBlock9_LoadByteSwapped(AnimFloatBlock9* block, IKFile* file);
