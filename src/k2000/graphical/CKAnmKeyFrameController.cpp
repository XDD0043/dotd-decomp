// CKAnmKeyFrameController.cpp - reconstructed original translation unit 0x7aad0-0x7b2d8 (GAME_TOC1, main_toc1), 18 functions, 18 live.
// Primary class: CKAnmKeyFrameController  key 0xb4d  category Graphical  size 0x60  vtable 0xb16590
// Other owners: Anim (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x7aad0  CKAnmKeyFrameController_Delete
//   [x] 0x7ab20  CKAnmKeyFrameController_SetAnim
//   [x] 0x7ab60  Anim_GetDuration
//   [ ] 0x7ab80  RegisterCKAnmKeyFrameControllerClass
//   [ ] 0x7abf8  _GLOBAL__I_7abf8
//   [x] 0x7ac08  CKAnmKeyFrameController_Reset_maybe
//   [x] 0x7ac50  CKAnmKeyFrameController_PostLoad
//   [x] 0x7ac78  CKAnmKeyFrameController_Load
//   [ ] 0x7acc8  CKAnmKeyFrameController_Save
//   [ ] 0x7acf0  CKAnmKeyFrameController_RecursiveRegistration
//   [ ] 0x7ad18  CKAnmKeyFrameController_Destroy
//   [x] 0x7ad60  CKAnmKeyFrameController_DeleteArray
//   [x] 0x7ae08  CKAnmKeyFrameController_Create
//   [x] 0x7ae60  CKAnmKeyFrameController_GetBoundingSphere_maybe
//   [x] 0x7aed0  CKAnmKeyFrameController_UpdateActiveState_maybe
//   [x] 0x7af90  CKAnmKeyFrameController_vf50
//   [x] 0x7b018  CKAnmKeyFrameController_Evaluate_maybe
//   [x] 0x7b220  CKAnmKeyFrameController_CreateArray
//
//   [ ] 0x999748  CKAnmKeyFrameController_IsKindOfClass  [inline]
//   [ ] 0x999770  CKAnmKeyFrameController_GetClassType  [inline]
//   [ ] 0x999778  CKAnmKeyFrameController_GetClassID  [inline]
//   [ ] 0x999780  CKAnmKeyFrameController_DeletingDestructor  [inline]
//   [ ] 0x9997c8  CKAnmKeyFrameController_Destructor  [inline]
#include "k2000/graphical/CKAnmKeyFrameController.h"

#include "k2000/io/IKFile.h"

#include <cstring>

#include "Renderware/rtanim/RtAnim.h"
#include "Renderware/rwcore/RwStream.h"
#include "crt/ppc_ops.h"
#include "k2000/graphical/animation/CAnimationManager.h"
#include "k2000/graphical/animation/CSectorAnimation.h"
#include "k2000/misc/Engine.h"
#include "k2000/render/CRenderer.h"

// 0x0007ac78 CKAnmKeyFrameController_Load
int32_t CKAnmKeyFrameController::Load(IKFile* file, int32_t type) {
    KBase98D::Load(file, type);  // 0x7d0d8
    m_unk54 = 0.0f;
    m_unk5c = nullptr;
    m_unk50 = 0.0f;
    m_unk58 = nullptr;
    return 1;
}

// 0x0007ac50 CKAnmKeyFrameController_PostLoad
int32_t CKAnmKeyFrameController::PostLoad(int32_t /*type*/) {
    PostLoadBase();  // 0x7ced0
    return 1;
}

// 0x0007ab20 CKAnmKeyFrameController_SetAnim
void CKAnmKeyFrameController::SetAnim(float start, RtAnimAnimation* animation, bool restart) {
    m_unk50 = start;
    m_unk58 = animation;
    if (restart) m_unk08 = (m_unk08 & 0xffffffbfu) | 0x40u;
    m_unk08 = m_unk08 & 0xfffffffdu;
}

void CKAnmKeyFrameController::SetAnim(float start, uint32_t word, bool restart) {
    SetAnim(start, CAnimationManager_GetAnimation(word), restart);
}

// 0x0007ab60 Anim_GetDuration
float CKAnmKeyFrameController::GetDuration() const { return m_unk58 != nullptr ? m_unk58->duration : 1.0f; }

float CKAnmKeyFrameController::GetDurationOf(uint32_t word) {
    const RtAnimAnimation* animation = CAnimationManager_GetAnimation(word);
    return animation != nullptr ? animation->duration : 1.0f;
}

uint32_t CKAnmKeyFrameController::GetEvaluatedAnimWord() const { return CAnimationManager_GetAnimationWord(m_unk5c); }
uint32_t CKAnmKeyFrameController::GetAnimWord() const { return CAnimationManager_GetAnimationWord(m_unk58); }

// The animation-end test of 0x000ca368 / 0x0018f6a0 (float throughout: fdivs, fctiwz, fmuls, fsubs, fadds).
bool CKAnmKeyFrameController::HasEnded(float dt) const {
    if (m_unk58 == nullptr) return false;
    const float duration = GetDuration();
    const float time = m_unk50;
    const float whole = static_cast<float>(ppc::fctiwz(time / duration));
    const float remainder = time - duration * whole;
    return duration <= dt + remainder;
}

// 0x0007ac08 CKAnmKeyFrameController_Reset_maybe
void CKAnmKeyFrameController::Reset() {
    ResetBase();  // 0x7c8d8
    m_unk5c = nullptr;
    m_unk54 = 0.0f;
    m_unk58 = nullptr;
    m_unk50 = 0.0f;
}

// 0x0007af90 CKAnmKeyFrameController_vf50
uint8_t CKAnmKeyFrameController::Vf50(KBase98D* chain, uint32_t* mask) {
    if (Vf50Base(chain, mask) == 0) return 0;  // 0x7c988
    m_unk58 = nullptr;
    m_unk5c = nullptr;
    m_unk54 = 0.0f;
    m_unk50 = 0.0f;
    m_unk08 = (m_unk08 & 0xffffffbfu) | 0x40u;
    return 1;
}

// 0x0007ae60 CKAnmKeyFrameController_GetBoundingSphere_maybe
float* CKAnmKeyFrameController::GetBoundingSphere() {
    if ((m_unk08 & 2u) == 0 && m_unk58 != nullptr) {
        const RtAnimSectorEntryData* entry = RtAnimSectorEntry(m_unk58);
        std::memcpy(&m_afUnk14[0], &entry->words14[0], 4);
        std::memcpy(&m_afUnk14[1], &entry->words14[1], 4);
        std::memcpy(&m_afUnk14[2], &entry->words14[2], 4);
        std::memcpy(&m_afUnk14[3], &entry->word10, 4);
    }
    return m_afUnk14;
}

// 0x0007aed0 CKAnmKeyFrameController_UpdateActiveState_maybe
uint8_t CKAnmKeyFrameController::UpdateActiveState() {
    uint8_t active = 0;
    uint32_t evaluate = 0;
    if ((m_unk08 & 0x20u) != 0 && (m_unk58 != nullptr || (m_unk08 & 2u) != 0)) {
        active = 1;
        m_unk08 = (m_unk08 & 0xfffffffbu) | 4u;
        m_unk26 = g_ui16RenderFrameCounter;
        evaluate = (m_unk08 & 8u) != 0 ? 0u : 0x10u;
    } else {
        m_unk08 = m_unk08 & 0xfffffffbu;
        m_unk26 = g_ui16RenderFrameCounter;
    }
    m_unk08 = (m_unk08 & 0xffffffefu) | evaluate;
    m_unk26 = g_ui16RenderFrameCounter;
    return active;
}

// 0x0007b018 CKAnmKeyFrameController_Evaluate_maybe
RtAnimInterpolator* CKAnmKeyFrameController::Evaluate(uint32_t* mask, float* weight, uint8_t skip) {
    m_unk4c = 1.0f;  // TOC -0x6ae4
    *weight = 1.0f;
    if ((m_unk08 & 2u) != 0) {
        mask[0] = m_aUnk38[0];
        mask[1] = m_aUnk38[1];
        mask[2] = m_aUnk38[2];
        mask[3] = m_aUnk38[3];
        m_unk24 = g_ui16RenderFrameCounter;
        return m_unk0c;
    }
    const float duration = m_unk58 != nullptr ? m_unk58->duration : 1.0f;
    float time = m_unk50;
    if (!(duration >= time)) time = time - duration * static_cast<float>(ppc::fctiwz(time / duration));
    m_unk54 = time;
    m_unk5c = m_unk58;
    if (skip != 0) return nullptr;
    mask[0] = m_aUnk28[0];
    mask[1] = m_aUnk28[1];
    mask[2] = m_aUnk28[2];
    mask[3] = m_aUnk28[3];
    m_aUnk38[0] = m_aUnk28[0];
    m_aUnk38[1] = m_aUnk28[1];
    m_aUnk38[2] = m_aUnk28[2];
    m_aUnk38[3] = m_aUnk28[3];
    RtAnimInterpolator* interpolator = m_unk0c;
    if ((m_unk08 & 0x40u) != 0 || interpolator->pCurrentAnim != m_unk5c) {
        RtAnimInterpolatorSetCurrentAnim(interpolator, m_unk5c);
        m_unk08 &= 0xffffffbfu;
        interpolator = m_unk0c;
    }
    if (interpolator->pCurrentAnim == nullptr) return interpolator;
    const float delta = m_unk54 - interpolator->currentTime;
    if (delta < 0.0f) {
        RtAnimInterpolatorSubAnimTime(interpolator, -delta);
        interpolator = m_unk0c;
    } else if (!(delta <= 0.0f)) {
        RtAnimInterpolatorAddAnimTime(interpolator, delta);
        interpolator = m_unk0c;
    }
    m_unk24 = g_ui16RenderFrameCounter;
    return interpolator;
}
