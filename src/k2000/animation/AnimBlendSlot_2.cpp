// AnimBlendSlot_2.cpp - reconstructed original translation unit 0x7a710-0x7aad0 (GAME_TOC1, main_toc1), 5 functions, 5 live.
// Primary owner: AnimBlendSlot (not a registered class)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x7a710  AnimBlendSlot_Init
//   [x] 0x7a730  AnimBlendSlot_Load
//   [x] 0x7a7f8  AnimBlendSlot_SetWeight_maybe
//   [x] 0x7a848  AnimBlendSlot_StartCrossfade
//   [x] 0x7a9d0  AnimBlendSlot_UpdateCrossfade
#include "k2000/animation/AnimBlendSlot.h"

#include "k2000/graphical/CKAnmKeyFrameController.h"
#include "k2000/graphical/animation/CKBlenderController.h"
#include "k2000/io/IKFile.h"

// 0x0007a710 AnimBlendSlot_Init
void AnimBlendSlot::Init(IKSerializable* controller) {
    m_pController = controller;
    m_unk10 = 0;
    m_unk0c = 0;
    m_unk08 = 0;
}

// 0x0007a730 AnimBlendSlot_Load
int32_t AnimBlendSlot::Load(IKFile* file, int32_t type) {
    if (type == K_LEVEL_PLATEFORMS) {
        IKFile_ReadRef(file, &m_pController);
        m_unk14 = 0;
        m_unk10 = 0;
        if (m_pController != nullptr) {
            // The word at +0x58 of the controller (stw 0 at +0x58, whatever its class): a forward reference
            // is overwritten again by the controller's own Load.
            const uint32_t key = (static_cast<uint32_t>(m_pController->GetClassID()) << 6) |
                                static_cast<uint32_t>(m_pController->GetClassType());
            if (key == CKBlenderController::kClassKey) {
                static_cast<CKBlenderController*>(m_pController)->m_unk58 = 0.0f;
            } else if (key == CKAnmKeyFrameController::kClassKey) {
                static_cast<CKAnmKeyFrameController*>(m_pController)->m_unk58 = nullptr;
            }
        }
        m_unk0c = 0;
        m_unk08 = 0;
    }
    return 1;
}

// 0x0007a7f8 AnimBlendSlot_SetWeight_maybe: no crossfade; the blender's weight (its word +0x58 first set to the active
// side's 0 / 1 when there is a blender, then to `weight` without that test), the first controller active.
void AnimBlendSlot::SetWeight(float weight) {
    m_unk14 = 0;
    if (m_pController != nullptr) {
        static_cast<CKBlenderController*>(m_pController)->m_unk58 = m_unk10 != 0 ? 1.0f : 0.0f;  // TOC -0x6af4: 1.0f
    }
    static_cast<CKBlenderController*>(m_pController)->m_unk58 = weight;
    m_unk10 = 0;
}

// 0x0007a848 AnimBlendSlot_StartCrossfade
uint32_t AnimBlendSlot::StartCrossfade(double duration, uint32_t mode) {
    CKBlenderController* blender = static_cast<CKBlenderController*>(m_pController);
    const float weight = blender->m_unk58;
    if (weight > 1.0e-2f && weight < 9.9e-1f) mode = 1;  // TOC -0x6af0 / -0x6aec: a blend in the middle of one
    if (m_unk0c != m_unk08 || m_unk08 == 0.0f || m_unk14 == 0) {
        if (mode != 2) {
            // The active controller takes the pose of the first fully weighted, evaluated controller from the blender up
            // (KBase98D_vf50, vt+0x50); a cut (mode 0) when there is none.
            KBase98D* active = static_cast<KBase98D*>(blender->m_apControllers[m_unk10]);
            const uint8_t found = active->Vf50(blender, nullptr);
            mode = mode & (found != 0 ? 0xffffffffu : 0u);
        }
        m_unk10 ^= 1u;
    }
    m_unk0c = static_cast<float>(duration);
    m_unk08 = static_cast<float>(duration);
    m_unk14 = mode;
    if (mode == 0 && m_pController != nullptr) blender->m_unk58 = m_unk10 != 0 ? 1.0f : 0.0f;
    static_cast<KBase98D*>(blender->m_apControllers[m_unk10])->m_unk08 &= 0xfffffffdu;
    return mode;
}

// 0x0007a9d0 AnimBlendSlot_UpdateCrossfade (float throughout).
bool AnimBlendSlot::UpdateCrossfade(double dt) {
    if (m_unk14 == 0) return false;
    CKBlenderController* blender = static_cast<CKBlenderController*>(m_pController);
    if (!(m_unk0c > 0.0f)) {
        m_unk14 = 0;
        if (m_pController != nullptr) blender->m_unk58 = m_unk10 != 0 ? 1.0f : 0.0f;
        static_cast<KBase98D*>(blender->m_apControllers[m_unk10 ^ 1u])->m_unk08 &= 0xfffffffdu;
        return false;
    }
    float left = m_unk0c - static_cast<float>(dt);
    if (left < 0.0f) left = 0.0f;
    m_unk0c = left;
    float weight = left / m_unk08;
    if (m_unk10 == 1) weight = 1.0f - weight;
    blender->m_unk58 = weight;
    return true;
}

// 0x00079f30 AnimBlendSlot_AdvanceInactiveTrack_maybe
bool AnimBlendSlot::AdvanceInactiveTrack(double dt) {
    if (UpdateCrossfade(dt) && m_unk14 == 2) {
        CKBlenderController* blender = static_cast<CKBlenderController*>(m_pController);
        CKAnmKeyFrameController* inactive = static_cast<CKAnmKeyFrameController*>(blender->m_apControllers[m_unk10 ^ 1u]);
        inactive->m_unk50 = static_cast<float>(dt) + inactive->m_unk50;
        return true;
    }
    return false;
}

// 0x00079ea0 AnimBlendSlot_CrossfadeToAnim
uint32_t AnimBlendSlot::CrossfadeToAnim(double blend, double start, uint32_t word, uint32_t mode) {
    const uint32_t result = StartCrossfade(blend, mode);
    CKBlenderController* blender = static_cast<CKBlenderController*>(m_pController);
    static_cast<CKAnmKeyFrameController*>(blender->m_apControllers[m_unk10])->SetAnim(static_cast<float>(start), word, false);
    return result;
}

// 0x00079e10 AnimBlendSlot_SetAnimPairAndWeight_maybe: both controllers' animations at their times, then SetWeight.
void AnimBlendSlot::SetAnimPairAndWeight(uint32_t word1, uint32_t word2, float start1, float start2, float weight) {
    CKBlenderController* blender = static_cast<CKBlenderController*>(m_pController);
    static_cast<CKAnmKeyFrameController*>(blender->m_apControllers[0])->SetAnim(start1, word1, false);
    blender = static_cast<CKBlenderController*>(m_pController);
    static_cast<CKAnmKeyFrameController*>(blender->m_apControllers[1])->SetAnim(start2, word2, false);
    SetWeight(weight);
}
