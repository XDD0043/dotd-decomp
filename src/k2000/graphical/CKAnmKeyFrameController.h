// CKAnmKeyFrameController.h - an animation controller playing one animation (key 0xb4d, vtable 0xb16590,
// size 0x60). Original unit: CKAnmKeyFrameController.cpp (0x7aad0-...). No XXL2 class; the names are ours.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/graphical/KBase98D.h"

struct RtAnimAnimation;

class CKAnmKeyFrameController : public KBase98D {
public:
    DOTD_CLASS_KEY(kCategoryGraphical, 0x2d)
    DOTD_DECLARE_FACTORIES(CKAnmKeyFrameController)

    CKAnmKeyFrameController() {}  // 0x0007ae08 CKAnmKeyFrameController_Create: KBase98D's constructor only
    ~CKAnmKeyFrameController() override {}

    // vt+0x2c 0x0007ac78 CKAnmKeyFrameController_Load: the base's, then the four runtime words cleared.
    int32_t Load(IKFile* file, int32_t type) override;
    // vt+0x30 0x0007ac50 CKAnmKeyFrameController_PostLoad: KBase98D::PostLoadBase. 1.
    int32_t PostLoad(int32_t type) override;

    // vt+0x50 0x0007af90 CKAnmKeyFrameController_vf50: KBase98D_vf50; when it took a pose, no animation any more (+0x50..
    // +0x5c cleared) and the restart flag 0x40 set. Returns the base's answer.
    uint8_t Vf50(KBase98D* chain, uint32_t* mask) override;
    // vt+0x54 0x0007ae60 CKAnmKeyFrameController_GetBoundingSphere_maybe: the stored sphere (+0x14); unless a snapshot
    // (flag 2), refreshed first from the animation's sector entry (centre +0x14, radius +0x10). Always +0x14.
    float* GetBoundingSphere() override;
    // vt+0x60 0x0007ac08 CKAnmKeyFrameController_Reset_maybe: KBase98D_Reset_maybe, then the time and both animation
    // words cleared.
    void Reset() override;
    // vt+0x64 0x0007b018 CKAnmKeyFrameController_Evaluate_maybe: weight 1; a snapshot (flag 2) gives its stored mask; else
    // the time (+0x50) wrapped into the duration (+0x54) and the animation latched (+0x5c); unless `skip`, the node mask is
    // the evaluated one, the animation set on the interpolator when it changed (or flag 0x40), and the interpolator moved
    // to the time (Add/SubAnimTime). The frame is stamped (+0x24). Returns the interpolator (null with `skip`).
    RtAnimInterpolator* Evaluate(uint32_t* mask, float* weight, uint8_t skip) override;
    // vt+0x68 0x0007aed0 CKAnmKeyFrameController_UpdateActiveState_maybe: active (4) when enabled (0x20) and with an
    // animation or a snapshot; 0x10 = active and not 8. +0x26 stamped.
    uint8_t UpdateActiveState() override;

    // 0x0007ab20 CKAnmKeyFrameController_SetAnim: the start time and the animation; `restart` also sets bit 6 of the
    // flags (m_unk08); bit 1 is cleared either way.
    void SetAnim(float start, RtAnimAnimation* animation, bool restart);
    // The same with a dictionary word (dotd keeps the words: CAnimationManager_GetAnimation turns it into the pointer the
    // original passes).
    void SetAnim(float start, uint32_t word, bool restart);

    // 0x0007ab60 Anim_GetDuration: the duration of the animation (+0x58), 1.0 without one.
    float GetDuration() const;
    // The duration of the animation a dictionary word names (1.0 for none): Anim_GetDuration's test on the pointer the
    // original reads from the dictionary.
    static float GetDurationOf(uint32_t word);
    // The test CKAnimatedNode / CKCinematicBloc make with a frame's time added (CAnimatedNode_IsAnimEndReached_maybe 0x000ca368,
    // CKCinematicBloc_IsActorAnimEndReached 0x0018f6a0): the time wrapped into the duration plus `dt` reaches the duration.
    bool HasEnded(float dt) const;
    // +0x54: the time (+0x50) wrapped into the duration by the last Evaluate.
    float GetEvaluatedTime() const { return m_unk54; }
    // The dictionary word of the evaluated animation (+0x5c; DOTD: the words are kept, see CAnimationManager_GetAnimationWord).
    uint32_t GetEvaluatedAnimWord() const;
    // The dictionary word of the animation (+0x58).
    uint32_t GetAnimWord() const;

    float m_unk50;              // +0x50 the animation time (SetAnim; the node / blocs add the frame time); Load sets 0
    float m_unk54;              // +0x54 the time wrapped into the duration (Evaluate); Load sets 0
    RtAnimAnimation* m_unk58;   // +0x58 the animation (SetAnim); Load sets 0
    RtAnimAnimation* m_unk5c;   // +0x5c the animation of the last Evaluate; Load sets 0
};
static_assert(CKAnmKeyFrameController::kClassKey == 0xb4d, "key");
DOTD_ASSERT_SIZE(CKAnmKeyFrameController, 0x60);
DOTD_ASSERT_OFFSET(CKAnmKeyFrameController, m_unk50, 0x50);
DOTD_ASSERT_OFFSET(CKAnmKeyFrameController, m_unk58, 0x58);
DOTD_ASSERT_OFFSET(CKAnmKeyFrameController, m_unk5c, 0x5c);
