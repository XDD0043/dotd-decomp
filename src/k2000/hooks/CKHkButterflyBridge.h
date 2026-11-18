// CKHkButterflyBridge.h - a drawbridge whose segments open like wings (key 0xb42, vtable 0xb25470, size 0x108).
// Original unit: CKHkButterflyBridge.cpp (0x3ff9b8-0x4009b0). Derives from the bridge base (KBase9C2, CKHkBridgeBase.h):
// each segment has two wing nodes (the base's +0x8c references, read in pairs) and two wing grounds (+0x94, in pairs);
// states 3 / 6 turn the current segment's wings between 90 degrees (folded) and 0 (open) at +0x100 degrees a second.
// No XXL2 class; no level file holds one (work/level-class-keys.json). C2.8 port-final F01 ported it from the code.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/misc/CKHkBridgeBase.h"

class CKHkButterflyBridge : public CKHkBridgeBase {
public:
    // vt+0x14 / +0x18 0x9c1018 / 0x9c1020: category 2 (hook), id 0x2d.
    DOTD_CLASS_KEY(kCategoryHook, 0x2d)
    // vt+0x08 0x009c0fb8 CKHkButterflyBridge_IsKindOfClass [inline]
    int32_t IsKindOfClass(uint32_t key) override {
        return key == 0xb42 || key == 0x9c2 || key == 0xd82 || key == 0x2 || key == 0x2fe || key == 0x3fe || key == 0xc;
    }
    // 0x003ff9b8 _Delete, 0x003ffca8 _DeleteArray, 0x004008a0 _CreateArray, 0x00400958 _Create (operator new(0x108), the
    // base constructor, the vtable).
    DOTD_DECLARE_FACTORIES(CKHkButterflyBridge)

    // The fresh heap's zeroes (the original's Create leaves +0xfc..+0x104 untouched).
    CKHkButterflyBridge() : m_pUnk0fc(nullptr), m_fWingSpeed(0.0f), m_fWingAngle(0.0f) {}
    // 0x003ffc08 _Destructor / 0x00400248 _BaseDestructor / 0x00400340 _DeletingDestructor: the vtable, the base's.
    ~CKHkButterflyBridge() override {}

    // vt+0x10 0x003ffbe0 _Destroy: the base's (CKHkBridgeBase::Destroy), inherited.
    // vt+0x24 0x003ffbb8 _RecursiveRegistration: the base's, then 1 (the same answer): inherited.
    // vt+0x28 0x3ffb90 _Save: not ported (the saves are out of scope).
    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x003ffa90 CKHkButterflyBridge_Load

    void OnSnappedLowered() override;  // vt+0xf0 0x003ffd50 CKHkButterflyBridge_SetWingsRetracted_maybe
    void OnSnappedRaised() override;   // vt+0xf4 0x004006a8 CKHkButterflyBridge_SetWingsDeployed_maybe
    // vt+0xf8 0x003fff48 CKHkButterflyBridge_State3_RotateWingSegments_maybe
    uint8_t StateNextSegmentUp(IKTime* clock, int32_t phase, uint8_t other) override;
    // vt+0xfc 0x00400388 CKHkButterflyBridge_StateRotateSegment_maybe
    uint8_t StateNextSegmentDown(IKTime* clock, int32_t phase, uint8_t other) override;
    uint8_t IsBridgeGround(IKSerializable* ground) override;  // vt+0x100 0x00400278 CKHkButterflyBridge_vf100
    // vt+0x104: the vtable ends there (a zero word); nothing calls it.
    void Vf104() override {}

    // The inlined four rotations of the snaps and states 3 / 6: segment `segment`'s wing A (+0x8c [2 * segment]) turned
    // 180 degrees about y (its modelling matrix replaced) then `angleA` about z, wing B (+0x8c [2 * segment + 1]) 0
    // degrees about y then `angleB` about z.
    void PoseWings(uint32_t segment, float angleA, float angleB);

    IKSerializable* m_pUnk0fc;  // +0xfc (Load, a reference; not used in the unit)
    float m_fWingSpeed;         // +0x100 (Load) degrees a second
    float m_fWingAngle;         // +0x104 the current segment's wing angle (90 folded .. 0 open)
};
// The base's offsets past its handler table hold only with the PS3's 8-byte pointers to member functions (see
// CKHkBridgeBase.h): +0xfc / +0x100 / +0x104, size 0x108, are not asserted.
