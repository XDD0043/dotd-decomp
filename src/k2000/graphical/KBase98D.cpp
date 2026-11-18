// KBase98D.cpp - reconstructed original translation unit 0x7c8a8-0x7ced0 (GAME_TOC1, main_toc1), 6 functions, 5 live.
// Primary owner: KBase98D (not a registered class)
// Other owners: CKAnmKeyFrameController (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x7c8a8  KBase98D_vf6C
//   [x] 0x7c8d8  KBase98D_Reset_maybe
//   [ ] 0x7c8e8  KBase98D_ConstructBase_2  [dead]
//   [x] 0x7c938  KBase98D_ConstructBase
//   [x] 0x7c988  KBase98D_vf50
//   [x] 0x7cec8  KBase98D_vf28  (KBase98D::Save, KBase98D.h)
//
//   [ ] 0x999720  KBase98D_GetSerializationFlags  [inline]
//   [x] 0x999728  KBase98D_vf58  [inline]
//   [x] 0x999738  KBase98D_vf5C  [inline]
//   [ ] 0x999888  KBase98D_vf14  [inline]
//   [ ] 0x999890  KBase98D_vf18  [inline]
//   [ ] 0x999898  KBase98D_vf8  [inline]
//   [ ] 0x9998b8  KBase98D_vf0  [inline]
//   [ ] 0x9998d0  KBase98D_DeletingDestructor  [inline]
// 0x0007c938 KBase98D_ConstructBase: KBase98D's constructor (k2000/graphical/KBase98D.h).
#include "k2000/graphical/KBase98D.h"

#include "Renderware/rphanim/RpHAnim.h"
#include "Renderware/rtanim/RtAnim.h"
#include "k2000/render/CRenderer.h"
#include "k2000/logic/CKSavingManager.h"
#include "k2000/misc/Engine.h"

// 0x0007c8a8 KBase98D_vf6C
KBase98D* KBase98D::GetIfEvaluatedThisFrame() { return m_unk24 == g_ui16RenderFrameCounter ? this : nullptr; }

// 0x0007c8d8 KBase98D_Reset_maybe
void KBase98D::ResetBase() { m_unk0c->pCurrentAnim = nullptr; }

namespace {
// The 0x1c bytes the snapshot copies per node (+0x08..+0x23 of the PS3's interpolated frame: the quaternion and the
// translation, copied byte by byte in the original).
void CopyPose(RpHAnimInterpFrame* dst, const RpHAnimInterpFrame* src) {
    dst->q = src->q;
    dst->t = src->t;
}
}  // namespace

// 0x0007c988 KBase98D_vf50
uint8_t KBase98D::Vf50Base(KBase98D* chain, uint32_t* mask) {
    if (chain == nullptr) return 0;
    KBase98D* found = nullptr;
    for (KBase98D* link = chain; link != nullptr; link = static_cast<KBase98D*>(link->m_pParentController)) {
        if (link->m_unk4c >= 9.9e-1f) {  // TOC -0x6a58: 0x3f7d70a4
            found = link->GetIfEvaluatedThisFrame();  // vt+0x6c
            if (found != nullptr) break;
        }
    }
    if (found == nullptr) return 0;
    const uint32_t* evaluated = found->GetEvaluatedMask();  // vt+0x5c
    const uint32_t* nodeMask = found->GetNodeMask();        // vt+0x58
    for (int i = 0; i < 4; ++i) m_aUnk38[i] = m_aUnk28[i] & evaluated[i];
    if (mask != nullptr) {
        for (int i = 0; i < 4; ++i) mask[i] = m_aUnk38[i];
    }
    if (this != found) {
        RtAnimInterpolator* source = found->m_unk0c;
        bool same = true;
        for (int i = 0; i < 4 && same; ++i) same = m_aUnk28[i] == nodeMask[i];
        for (int i = 0; i < 4 && same; ++i) same = m_aUnk28[i] == evaluated[i];
        // The frames are 0x24 bytes apart in the original whatever the interpolators' sizes (the scheme 1 size).
        if (same) {
            for (uint32_t i = 0; i < m_unk49; ++i) {
                CopyPose(static_cast<RpHAnimInterpFrame*>(RtAnimInterpolatorGetInterpFrame(m_unk0c, static_cast<RwInt32>(i))),
                         static_cast<RpHAnimInterpFrame*>(RtAnimInterpolatorGetInterpFrame(source, static_cast<RwInt32>(i))));
            }
        } else {
            // The nodes of this mask, indexed in the main interpolator (each frame base moved back by the start node).
            const RwInt32 count = m_unk0c->parentAnimation->numNodes;
            for (RwInt32 i = 0; i < count; ++i) {
                if ((m_aUnk38[i >> 5] & (1u << (i & 31))) == 0) continue;
                CopyPose(static_cast<RpHAnimInterpFrame*>(RtAnimInterpolatorGetInterpFrame(m_unk0c, i - m_unk48)),
                         static_cast<RpHAnimInterpFrame*>(RtAnimInterpolatorGetInterpFrame(source, i - found->m_unk48)));
            }
        }
        m_afUnk14[0] = found->m_afUnk14[0];
        m_afUnk14[1] = found->m_afUnk14[1];
        m_afUnk14[2] = found->m_afUnk14[2];
        m_afUnk14[3] = found->m_afUnk14[3];
    }
    m_unk24 = g_ui16RenderFrameCounter;
    m_unk08 = (m_unk08 & 0xfffffffdu) | 2u;
    return 1;
}

// C2.8 port-all P08: 0x0007cff8 (Ghidra KBase98D_LevelReset; the checklist line is animation/CKAnimController.cpp's):
// the saving manager's vt+0x24 on the controller, no type test; 1.
void KBase98D::RecursiveRegistration(int32_t /*type*/) {
    g_pEngine->m_pSavingManager->RegisterSerializableObject(this, nullptr);
}
