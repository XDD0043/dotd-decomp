// KBase98D.h - the unregistered base of the animation controllers (key 0x98d; CKAnmKeyFrameController,
// CKBlenderController). Original units: KBase98D.cpp (0x7c8a8-0x7ced0, the constructor, Reset, the evaluated-this-frame
// test and the pose snapshot) and CKAnimController.cpp (0x7ced0-0x7d350, PostLoad and Load; Ghidra calls the base
// CKAnimController_*_maybe). No XXL2 class; the names are ours. Size 0x50.
//
// The flags word +0x08 (read by Load; the bits the code tests): 0x01 the controller drives the whole hierarchy with the
// hierarchy's own interpolator (PostLoad), 0x02 the pose is a snapshot (vf50: Evaluate, GetBoundingSphere and
// UpdateActiveState answer from the stored mask / sphere), 0x04 active this frame (UpdateActiveState), 0x08 _maybe
// "inactive layer" (a blender only evaluates such a child when the other one has it too), 0x10 its pose is to be
// evaluated, 0x20 enabled, 0x40 restart the animation at the next Evaluate.
#pragma once
#include <cstdint>

#include "k2000/core/IKSerializable.h"
#include "k2000/core/Layout.h"

struct RtAnimInterpolator;

class KBase98D : public IKSerializable {
public:
    DOTD_CLASS_KEY(kCategoryGraphical, 0x26)

    // 0x0007c938 KBase98D_ConstructBase
    KBase98D() {
        m_aUnk28[0] = 0;
        m_aUnk28[3] = 0;
        m_aUnk28[2] = 0;
        m_aUnk28[1] = 0;
        m_aUnk38[0] = 0;
        m_aUnk38[3] = 0;
        m_aUnk38[2] = 0;
        m_aUnk38[1] = 0;
        m_unk26 = 0;
        m_pParentController = nullptr;
        m_unk0c = nullptr;
        m_pNode = nullptr;
        m_unk24 = 0;
    }
    ~KBase98D() override {}
    // 0x0007d050 CKAnimController_ClearReferencesBase_maybe (the controllers' Destroy): an interpolator of its own (flag
    // bit 0 clear: not the hierarchy's) destroyed, the parent controller cleared.
    void ClearReferencesBase();

    // vt+0x2c 0x0007d0d8 (Ghidra CKAnimController_LoadBase_maybe). Every type clears +0x0c, +0x24, +0x26;
    // only K_LEVEL_PLATEFORMS reads.
    int32_t Load(IKFile* file, int32_t type) override;
    // vt+0x24 0x0007cff8 (Ghidra KBase98D_LevelReset, animation/CKAnimController.cpp's row; body in KBase98D.cpp):
    // registers the controller (any type).
    void RecursiveRegistration(int32_t type) override;
    // vt+0x28 0x0007cec8 KBase98D_vf28: the base Save, 1 (both subclasses' Save call it).
    int32_t Save(IKFile* /*file*/, int32_t /*type*/) override { return 1; }
    // 0x0007ced0 CKAnimController_PostLoadBase_maybe (both subclasses' PostLoad, vt+0x30, call it): the interpolator
    // (+0x0c): the hierarchy's own one (flag 1), a new one for the whole hierarchy (start node 0 and the node count is the
    // node's bone count), else a sub-interpolator of the hierarchy's for nodes +0x48.. (+0x49 of them); scheme 1, no
    // callbacks; flag 2 cleared. 1.
    int32_t PostLoadBase();

    // vt+0x50 (CKAnmKeyFrameController_vf50 0x7af90 / CKBlenderController_vf50 0x7b830; both call KBase98D_vf50 below)
    // _maybe "take the pose": see Vf50Base.
    virtual uint8_t Vf50(KBase98D* chain, uint32_t* mask) = 0;
    // vt+0x54 GetBoundingSphere_maybe: the animation's bounding sphere (centre, radius) in the node's space, or null.
    virtual float* GetBoundingSphere() = 0;
    // vt+0x58 0x00999728 KBase98D_vf58: the node mask read by Load (+0x28, 128 bits: the hierarchy nodes it drives).
    virtual uint32_t* GetNodeMask() { return m_aUnk28; }
    // vt+0x5c 0x00999738 KBase98D_vf5C: the mask of the last evaluation (+0x38).
    virtual uint32_t* GetEvaluatedMask() { return m_aUnk38; }
    // vt+0x60 Reset_maybe (each subclass calls KBase98D_Reset_maybe 0x7c8d8: the interpolator's animation cleared).
    virtual void Reset() = 0;
    // vt+0x64 Evaluate_maybe: the pose of this frame into the interpolator (+0x0c) unless `skip`; `mask` gets the nodes it
    // posed, `weight` its weight. Returns the interpolator holding the pose (null with `skip`).
    virtual RtAnimInterpolator* Evaluate(uint32_t* mask, float* weight, uint8_t skip) = 0;
    // vt+0x68 UpdateActiveState_maybe: flags 4 / 0x10 for this frame (+0x26 stamped). Returns whether it is active.
    virtual uint8_t UpdateActiveState() = 0;
    // vt+0x6c 0x0007c8a8 (Ghidra KBase98D_vf6C; the base of both): this controller when it was evaluated in
    // this render frame (+0x24 equals the frame counter), else null.
    virtual KBase98D* GetIfEvaluatedThisFrame();

    // 0x0007c8d8 KBase98D_Reset_maybe: the interpolator's current animation cleared.
    void ResetBase();
    // 0x0007c988 KBase98D_vf50: from `chain` up through the parents, the first controller with a weight (+0x4c) of at least
    // 0.99 that was evaluated in this frame gives this one its pose: this mask = this node mask & its evaluated mask (copied
    // to `mask` when given); unless it is this controller, the interpolated frames of the nodes (all of them when both its
    // masks equal this node mask, else the ones of this mask) and its bounding sphere are copied. This one is then stamped
    // evaluated and flagged 2 (a snapshot). 0 when none is found.
    uint8_t Vf50Base(KBase98D* chain, uint32_t* mask);

    IKSerializable* m_pParentController;  // +0x04 the controller above this one (a CKBlenderController), or null
    uint32_t m_unk08;                     // +0x08 the flags (see above); read first (3, 0x20, 0x34 in LVL010)
    RtAnimInterpolator* m_unk0c;          // +0x0c the interpolator (PostLoad); Load sets 0
    IKSerializable* m_pNode;              // +0x10 the CAnimatedNode it drives
    float m_afUnk14[4];                   // +0x14 the bounding sphere (centre, radius) GetBoundingSphere returns
    uint16_t m_unk24;                     // +0x24 the render frame of the last evaluation (Load sets 0)
    uint16_t m_unk26;                     // +0x26 the render frame of the last UpdateActiveState (Load sets 0)
    uint32_t m_aUnk28[4];                 // +0x28 the node mask: one 0x10 read, each word swapped (-1 in some samples)
    uint32_t m_aUnk38[4];                 // +0x38 the evaluated mask; the constructor sets 0
    uint8_t m_unk48;                      // +0x48 the first node it drives
    uint8_t m_unk49;                      // +0x49 the node count
    uint16_t m_unk4a;                     // +0x4a not read
    float m_unk4c;                        // +0x4c the weight of the last evaluation
};
static_assert(KBase98D::kClassKey == 0x98d, "key");
DOTD_ASSERT_SIZE(KBase98D, 0x50);
DOTD_ASSERT_OFFSET(KBase98D, m_pParentController, 0x04);
DOTD_ASSERT_OFFSET(KBase98D, m_unk08, 0x08);
DOTD_ASSERT_OFFSET(KBase98D, m_unk0c, 0x0c);
DOTD_ASSERT_OFFSET(KBase98D, m_pNode, 0x10);
DOTD_ASSERT_OFFSET(KBase98D, m_afUnk14, 0x14);
DOTD_ASSERT_OFFSET(KBase98D, m_unk24, 0x24);
DOTD_ASSERT_OFFSET(KBase98D, m_aUnk28, 0x28);
DOTD_ASSERT_OFFSET(KBase98D, m_aUnk38, 0x38);
DOTD_ASSERT_OFFSET(KBase98D, m_unk48, 0x48);
DOTD_ASSERT_OFFSET(KBase98D, m_unk4c, 0x4c);
