// CKHkFoldawayBridge.h - a drawbridge whose segments slide out one after another (key 0x4042, vtable 0xb25580, size
// 0x11c). Original unit: CKHkFoldawayBridge.cpp (0x4009b0-0x401850). Derives from the bridge base (KBase9C2,
// CKHkBridgeBase.h): each segment has one sliding node (the base's +0x8c references) and one ground (+0x94); states 3 /
// 6 move the current segment's node along y between 0 (folded) and +0xfc (unfolded) with a damped spring (+0x110).
// No XXL2 class; no level file holds one (work/level-class-keys.json). C2.8 port-final F01 ported it from the code.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/misc/CKHkBridgeBase.h"

class CKHkFoldawayBridge : public CKHkBridgeBase {
public:
    // vt+0x14 / +0x18 0x9c1088 / 0x9c1090: category 2 (hook), id 0x101.
    DOTD_CLASS_KEY(kCategoryHook, 0x101)
    // vt+0x08 0x009c1028 CKHkFoldawayBridge_IsKindOfClass [inline]
    int32_t IsKindOfClass(uint32_t key) override {
        return key == 0x4042 || key == 0x9c2 || key == 0xd82 || key == 0x2 || key == 0x2fe || key == 0x3fe || key == 0xc;
    }
    // 0x004009b0 _Delete, 0x00400bf8 _DeleteArray, 0x004014e8 _CreateArray, 0x004015b8 _Create.
    DOTD_DECLARE_FACTORIES(CKHkFoldawayBridge)

    // 0x004015b8 CKHkFoldawayBridge_Create: the base constructor, then the spring (+0x110 / +0x114 / +0x118) 0.0 (TOC1
    // +0x482c). The loaded words are the fresh heap's zeroes.
    CKHkFoldawayBridge()
        : m_fUnfolded(0.0f), m_fStiffness(0.0f), m_fDamping(0.0f), m_fRestThreshold(0.0f), m_fMaxLag(0.0f) {
        m_fSpringTarget = 0.0f;
        m_fSpringSpeed = 0.0f;
        m_fSpringCurrent = 0.0f;
    }
    // 0x00400c98 _Destructor / 0x00400cc8 _BaseDestructor / 0x00400b00 _DeletingDestructor: the vtable, the base's.
    ~CKHkFoldawayBridge() override {}

    // vt+0x10 0x00400ad8 _Destroy: the base's, inherited. vt+0x24 0x00400ab0 _RecursiveRegistration: the base's, then
    // 1: inherited. vt+0x28 0x400a88 _Save: not ported (the saves are out of scope).
    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x00401620 CKHkFoldawayBridge_Load

    void OnSnappedLowered() override;  // vt+0xf0 0x00401120 CKHkFoldawayBridge_SnapAllSegmentsFolded_maybe
    void OnSnappedRaised() override;   // vt+0xf4 0x00401028 CKHkFoldawayBridge_SnapAllSegmentsUnfolded_maybe
    // vt+0xf8 0x00401218 CKHkFoldawayBridge_State3_UnfoldSegment_maybe
    uint8_t StateNextSegmentUp(IKTime* clock, int32_t phase, uint8_t other) override;
    // vt+0xfc 0x00400cf8 CKHkFoldawayBridge_StateMoveSegment_maybe
    uint8_t StateNextSegmentDown(IKTime* clock, int32_t phase, uint8_t other) override;
    uint8_t IsBridgeGround(IKSerializable* ground) override;  // vt+0x100 0x00400f88 CKHkFoldawayBridge_vf100
    // vt+0x104: the vtable ends there (a zero word); nothing calls it.
    void Vf104() override {}

    // The spring step inlined in states 3 and 6 (one frame of `dt`): its new current is the current segment's height.
    void StepSegmentSpring(float dt);

    float m_fUnfolded;       // +0xfc (Load, read last) a segment's unfolded height (y)
    float m_fStiffness;      // +0x100 (Load)
    float m_fDamping;        // +0x104 (Load)
    float m_fRestThreshold;  // +0x108 (Load) speed and distance under which the spring rests on its target
    float m_fMaxLag;         // +0x10c (Load) the farthest the current trails the target
    float m_fSpringTarget;   // +0x110
    float m_fSpringCurrent;  // +0x114
    float m_fSpringSpeed;    // +0x118
};
// The base's offsets past its handler table hold only with the PS3's 8-byte pointers to member functions (see
// CKHkBridgeBase.h): +0xfc..+0x118, size 0x11c, are not asserted.
