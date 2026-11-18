// CKBlenderController.cpp - reconstructed original translation unit 0x7b2d8-0x7c8a8 (GAME_TOC1, main_toc1), 17 functions, 17 live.
// Primary class: CKBlenderController  key 0xd4d  category Graphical  size 0x5c  vtable 0xb16608
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x7b2d8  CKBlenderController_Delete
//   [ ] 0x7b328  RegisterCKBlenderControllerClass
//   [ ] 0x7b3a0  _GLOBAL__I_7b3a0
//   [x] 0x7b3b0  CKBlenderController_Reset_maybe
//   [x] 0x7b430  CKBlenderController_vf6C
//   [x] 0x7b4f0  CKBlenderController_PostLoad
//   [x] 0x7b518  CKBlenderController_Load
//   [ ] 0x7b630  CKBlenderController_Save
//   [x] 0x7b658  CKBlenderController_RecursiveRegistration
//   [x] 0x7b6f0  CKBlenderController_Destroy
//   [x] 0x7b738  CKBlenderController_DeleteArray
//   [x] 0x7b7d8  CKBlenderController_Create
//   [x] 0x7b830  CKBlenderController_vf50
//   [x] 0x7b8b8  CKBlenderController_CreateArray
//   [x] 0x7b968  CKBlenderController_Evaluate_maybe
//   [x] 0x7c110  CKBlenderController_UpdateActiveState_maybe
//   [x] 0x7c4e0  CKBlenderController_GetBoundingSphere_maybe
//
//   [ ] 0x9997e8  CKBlenderController_IsKindOfClass  [inline]
//   [ ] 0x999810  CKBlenderController_GetClassType  [inline]
//   [ ] 0x999818  CKBlenderController_GetClassID  [inline]
//   [ ] 0x999820  CKBlenderController_DeletingDestructor  [inline]
//   [ ] 0x999868  CKBlenderController_Destructor  [inline]
#include "k2000/graphical/animation/CKBlenderController.h"

#include <cmath>

#include "Renderware/rphanim/RpHAnim.h"
#include "Renderware/rtanim/RtAnim.h"
#include "crt/ppc_ops.h"
#include "k2000/io/IKFile.h"
#include "k2000/render/CRenderer.h"
#include "k2000/scenegraph/CAnimatedNode.h"

namespace {
// TOC -0x6a78 / -0x6a74 / -0x6a80: 0.99f (0x3f7d70a4), 0.01f (0x3c23d70a), 1.0f.
constexpr float kAlmostOne = 9.9e-1f;
constexpr float kAlmostZero = 1.0e-2f;

KBase98D* Child(const CKBlenderController* blender, int index) { return static_cast<KBase98D*>(blender->m_apControllers[index]); }

void Stamp(KBase98D* controller) {
    if (controller->m_unk26 != g_ui16RenderFrameCounter) controller->UpdateActiveState();  // vt+0x68
}

// Whether a child takes part (Evaluate, UpdateActiveState and GetBoundingSphere test the same): the first one below
// 0.99, the second one above 0.01, or either when it alone is not flagged 8.
bool UsesFirst(const CKBlenderController* blender) {
    const KBase98D* first = Child(blender, 0);
    if ((first->m_unk08 & 4u) == 0) return false;
    if (blender->m_unk58 < kAlmostOne) return true;
    if ((Child(blender, 0)->m_unk08 & 8u) != 0) return false;
    return (Child(blender, 1)->m_unk08 & 8u) != 0;
}
bool UsesSecond(const CKBlenderController* blender) {
    const KBase98D* second = Child(blender, 1);
    if ((second->m_unk08 & 4u) == 0) return false;
    if (blender->m_unk58 > kAlmostZero) return true;
    if ((Child(blender, 1)->m_unk08 & 8u) != 0) return false;
    return (Child(blender, 0)->m_unk08 & 8u) != 0;
}

// Node `index` of an interpolator, indexed in the main interpolator's numbering (the frame base moved back by the
// interpolator's offset in its parent); the frames are 0x24 bytes apart in the original (the scheme 1 size).
RpHAnimInterpFrame* NodeFrame(RtAnimInterpolator* interpolator, RwInt32 index) {
    return static_cast<RpHAnimInterpFrame*>(RtAnimInterpolatorGetInterpFrame(interpolator, index - interpolator->offsetInParent));
}
RpHAnimInterpFrame* Frame(RtAnimInterpolator* interpolator, RwInt32 index) {
    return static_cast<RpHAnimInterpFrame*>(RtAnimInterpolatorGetInterpFrame(interpolator, index));
}
}  // namespace

// 0x0007b518 CKBlenderController_Load
int32_t CKBlenderController::Load(IKFile* file, int32_t type) {
    KBase98D::Load(file, type);  // 0x7d0d8
    if (type != K_LEVEL_PLATEFORMS) return 1;
    IKFile_ReadObjectRefArray(file, m_apControllers, 2);  // the resolver's vt+0x28 (count 2)
    ReadF32LE(file, &m_unk58);
    return 1;
}

// 0x0007b4f0 CKBlenderController_PostLoad
int32_t CKBlenderController::PostLoad(int32_t /*type*/) {
    PostLoadBase();  // 0x7ced0
    return 1;
}

// 0x0007b830 CKBlenderController_vf50
uint8_t CKBlenderController::Vf50(KBase98D* chain, uint32_t* mask) {
    const uint8_t taken = Vf50Base(chain, m_aUnk38);  // 0x7c988
    if (taken != 0 && mask != nullptr) {
        mask[0] = m_aUnk38[0];
        mask[1] = m_aUnk38[1];
        mask[2] = m_aUnk38[2];
        mask[3] = m_aUnk38[3];
    }
    return taken;
}

// 0x0007b3b0 CKBlenderController_Reset_maybe
void CKBlenderController::Reset() {
    ResetBase();          // 0x7c8d8
    Child(this, 0)->Reset();  // vt+0x60
    Child(this, 1)->Reset();
}

// 0x0007b430 CKBlenderController_vf6C
KBase98D* CKBlenderController::GetIfEvaluatedThisFrame() {
    KBase98D* self = KBase98D::GetIfEvaluatedThisFrame();  // 0x7c8a8
    if (self == this) return self;
    KBase98D* first = Child(this, 0)->GetIfEvaluatedThisFrame();  // vt+0x6c
    if (first != nullptr) return first;
    return Child(this, 1)->GetIfEvaluatedThisFrame();
}

// 0x0007c110 CKBlenderController_UpdateActiveState_maybe
uint8_t CKBlenderController::UpdateActiveState() {
    const uint8_t first = Child(this, 0)->UpdateActiveState();   // vt+0x68
    const uint8_t second = Child(this, 1)->UpdateActiveState();
    const uint32_t snapshot = (m_unk08 >> 1) & 1u;
    uint32_t active;
    uint32_t evaluate;
    if (first == 0 && second == 0 && snapshot == 0) {
        active = 0;
        evaluate = 0;
    } else {
        // A snapshot keeps the blender active; it still needs evaluating when its mask is its node mask.
        uint32_t keep = 0;
        if (snapshot != 0) {
            keep = (m_aUnk38[0] == m_aUnk28[0] && m_aUnk38[1] == m_aUnk28[1] && m_aUnk38[2] == m_aUnk28[2] &&
                    m_aUnk38[3] == m_aUnk28[3]) ? 1u : 0u;
        }
        Stamp(Child(this, 0));
        uint32_t activeSoFar;
        uint32_t evaluateSoFar;
        if (UsesFirst(this)) {
            Stamp(Child(this, 0));
            activeSoFar = 1;
            evaluateSoFar = ((Child(this, 0)->m_unk08 & 0x10u) != 0 ? 1u : 0u) | keep;
        } else {
            activeSoFar = snapshot;
            evaluateSoFar = keep;
        }
        Stamp(Child(this, 1));
        if (UsesSecond(this)) {
            Stamp(Child(this, 1));
            active = 1;
            evaluate = ((Child(this, 1)->m_unk08 & 0x10u) != 0 ? 1u : 0u) | evaluateSoFar;
        } else {
            active = activeSoFar;
            evaluate = evaluateSoFar;
        }
    }
    m_unk08 = (m_unk08 & 0xfffffffbu) | (active << 2);
    m_unk26 = g_ui16RenderFrameCounter;
    m_unk08 = (m_unk08 & 0xffffffefu) | (evaluate << 4);
    m_unk26 = g_ui16RenderFrameCounter;
    return static_cast<uint8_t>(active);
}

// 0x0007c4e0 CKBlenderController_GetBoundingSphere_maybe
float* CKBlenderController::GetBoundingSphere() {
    if (m_unk26 != g_ui16RenderFrameCounter) UpdateActiveState();  // vt+0x68
    if ((m_unk08 & 4u) == 0) return nullptr;
    if ((m_unk08 & 2u) != 0) return m_afUnk14;
    Stamp(Child(this, 0));
    const float* first = UsesFirst(this) ? Child(this, 0)->GetBoundingSphere() : nullptr;  // vt+0x54
    Stamp(Child(this, 1));
    const float* second = UsesSecond(this) ? Child(this, 1)->GetBoundingSphere() : nullptr;
    if (first == nullptr && second == nullptr) return nullptr;
    const float* only = nullptr;
    if (first == nullptr) {
        only = second;
    } else if (second == nullptr) {
        only = first;
    }
    if (only != nullptr) {
        m_afUnk14[0] = only[0];
        m_afUnk14[1] = only[1];
        m_afUnk14[2] = only[2];
        m_afUnk14[3] = only[3];
        return m_afUnk14;
    }
    // The sphere around both (the second's centre minus the first's, the radii's difference).
    const float dy = second[1] - first[1];
    const float dx = second[0] - first[0];
    const float dz = second[2] - first[2];
    const float dr = first[3] - second[3];
    float d2 = dy * dy;
    const float dr2 = dr * dr;
    d2 = ppc::fmadds(dx, dx, d2);
    d2 = ppc::fmadds(dz, dz, d2);
    if (dr2 >= d2) {
        // One holds the other: the bigger one.
        const float* bigger = dr < 0.0f ? second : first;
        m_afUnk14[0] = bigger[0];
        m_afUnk14[1] = bigger[1];
        m_afUnk14[2] = bigger[2];
        m_afUnk14[3] = bigger[3];
        return m_afUnk14;
    }
    const float d = std::sqrt(d2);  // Math_Sqrtf 0x10690 (fsqrts)
    const float grow = (d - dr) * 0.5f;  // TOC -0x6a6c
    const float t = grow / d;
    const float cx = ppc::fmadds(dx, t, first[0]);
    const float cz = ppc::fmadds(dz, t, first[2]);
    const float cy = ppc::fmadds(dy, t, first[1]);
    m_afUnk14[0] = cx;
    m_afUnk14[2] = cz;
    m_afUnk14[1] = cy;
    m_afUnk14[3] = grow + first[3];
    return m_afUnk14;
}

// 0x0007b968 CKBlenderController_Evaluate_maybe
RtAnimInterpolator* CKBlenderController::Evaluate(uint32_t* mask, float* weight, uint8_t skip) {
    if ((m_unk08 & 2u) != 0) {
        mask[0] = m_aUnk38[0];
        mask[1] = m_aUnk38[1];
        mask[2] = m_aUnk38[2];
        mask[3] = m_aUnk38[3];
        m_unk4c = 1.0f;
        *weight = 1.0f;
        m_unk24 = g_ui16RenderFrameCounter;
        return m_unk0c;
    }
    uint32_t mask1[4] = {0, 0, 0, 0};  // sp+0x88
    uint32_t mask2[4] = {0, 0, 0, 0};  // sp+0x78
    float weight1 = 0.0f;              // sp+0x70
    float weight2 = 0.0f;              // sp+0x74
    Stamp(Child(this, 0));
    RtAnimInterpolator* first = nullptr;
    if (UsesFirst(this)) first = Child(this, 0)->Evaluate(mask1, &weight1, skip);  // vt+0x64
    Stamp(Child(this, 1));
    RtAnimInterpolator* second = nullptr;
    if (UsesSecond(this)) second = Child(this, 1)->Evaluate(mask2, &weight2, skip);
    if (skip != 0) return nullptr;

    const bool on1 = (Child(this, 0)->m_unk08 & 8u) == 0;
    const bool on2 = (Child(this, 1)->m_unk08 & 8u) == 0;
    float result;
    if (on1 == on2) {
        result = ppc::fmadds(1.0f - m_unk58, weight1, m_unk58 * weight2);
    } else if (!on1) {
        result = weight2;
    } else {
        result = weight1;
    }
    m_unk4c = result;
    *weight = result;
    // The effective blend: (1 - w)(1 - w1) + w w2.
    const float alpha = ppc::fmadds(1.0f - m_unk58, 1.0f - weight1, m_unk58 * weight2);

    const uint32_t* nodeMask = static_cast<CAnimatedNode*>(m_pNode)->m_aUnk4c;
    bool same = true;
    for (int i = 0; i < 4 && same; ++i) same = nodeMask[i] == mask1[i];
    for (int i = 0; i < 4 && same; ++i) same = mask2[i] == mask1[i];
    if (same) {
        for (int i = 0; i < 4; ++i) m_aUnk38[i] = nodeMask[i];
        for (int i = 0; i < 4; ++i) mask[i] = nodeMask[i];
        if (first == nullptr) return second;
        if (!(alpha <= kAlmostOne)) {
            Child(this, 0)->m_unk24 = 0;
            return second;
        }
        if (second == nullptr) return first;
        if (!(alpha >= kAlmostZero)) {
            Child(this, 1)->m_unk24 = 0;
            return first;
        }
        for (RwInt32 i = 0; i < m_unk49; ++i) RpHAnimKeyFrameBlend(Frame(m_unk0c, i), Frame(first, i), Frame(second, i), alpha);
        m_unk24 = g_ui16RenderFrameCounter;
        return m_unk0c;
    }
    if (first == nullptr) {
        for (int i = 0; i < 4; ++i) m_aUnk38[i] = mask2[i];
        for (int i = 0; i < 4; ++i) mask[i] = mask2[i];
        return second;
    }
    if (second == nullptr) {
        for (int i = 0; i < 4; ++i) m_aUnk38[i] = mask1[i];
        for (int i = 0; i < 4; ++i) mask[i] = mask1[i];
        return first;
    }
    for (int i = 0; i < 4; ++i) m_aUnk38[i] = mask1[i] | mask2[i];
    for (int i = 0; i < 4; ++i) mask[i] = m_aUnk38[i];
    for (RwInt32 i = 0; i < m_unk49; ++i) {
        const uint32_t bit = 1u << (i & 31);
        const int word = i >> 5;
        if ((m_aUnk38[word] & bit) == 0) continue;
        const bool has1 = (mask1[word] & bit) != 0;
        const bool has2 = (mask2[word] & bit) != 0;
        RpHAnimInterpFrame* source;
        if (!has1) {
            if (!has2) continue;
            source = NodeFrame(second, i);
        } else if (!has2 || alpha < kAlmostZero) {
            source = NodeFrame(first, i);
        } else if (alpha <= kAlmostOne) {
            RpHAnimKeyFrameBlend(Frame(m_unk0c, i), NodeFrame(first, i), NodeFrame(second, i), alpha);
            continue;
        } else {
            source = NodeFrame(second, i);
        }
        RpHAnimInterpFrame* destination = Frame(m_unk0c, i);
        destination->q = source->q;
        destination->t = source->t;
    }
    m_unk24 = g_ui16RenderFrameCounter;
    return m_unk0c;
}

// 0x0007b6f0 CKBlenderController_Destroy
void CKBlenderController::Destroy() {
    ClearReferencesBase();
    m_apControllers[1] = nullptr;
    m_unk58 = 0.0f;
    m_apControllers[0] = nullptr;
}

// C2.8 port-all P08.
// 0x0007b658 CKBlenderController_RecursiveRegistration
void CKBlenderController::RecursiveRegistration(int32_t type) {
    KBase98D::RecursiveRegistration(type);  // 0x0007cff8
    m_apControllers[0]->RecursiveRegistration(type);  // vt+0x24
    m_apControllers[1]->RecursiveRegistration(type);
}
