// CKAnimController.cpp - reconstructed original translation unit 0x7ced0-0x7d350 (GAME_TOC1, main_toc1), 4 functions, 4 live.
// Primary owner: CKAnimController (not a registered class)
// Other owners: KBase98D (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x7ced0  CKAnimController_PostLoadBase_maybe
//   [ ] 0x7cff8  KBase98D_LevelReset
//   [ ] 0x7d050  CKAnimController_ClearReferencesBase_maybe
//   [x] 0x7d0d8  CKAnimController_LoadBase_maybe
#include "k2000/graphical/KBase98D.h"

#include "Renderware/rphanim/RpHAnim.h"
#include "Renderware/rtanim/RtAnim.h"
#include "k2000/io/IKFile.h"
#include "k2000/scenegraph/CAnimatedNode.h"

// 0x0007d0d8 CKAnimController_LoadBase_maybe (KBase98D vt+0x2c)
int32_t KBase98D::Load(IKFile* file, int32_t type) {
    if (type == K_LEVEL_PLATEFORMS) {
        ReadU32LE(file, &m_unk08);
        IKFile_ReadRef(file, &m_pNode);
        IKFile_ReadRef(file, &m_pParentController);
        ReadU32LEWords(file, reinterpret_cast<uint32_t*>(m_aUnk28), 4);
        ReadRaw(file, &m_unk48, 1);
        ReadRaw(file, &m_unk49, 1);
    }
    m_unk26 = 0;
    m_unk0c = nullptr;
    m_unk24 = 0;
    return 1;
}

// 0x0007ced0 CKAnimController_PostLoadBase_maybe
int32_t KBase98D::PostLoadBase() {
    CAnimatedNode* node = static_cast<CAnimatedNode*>(m_pNode);
    if ((m_unk08 & 1u) != 0) {
        m_unk0c = node->m_pRpHAnimHierarchy->currentAnim;
    } else if (m_unk48 == 0 && m_unk49 == node->GetSubtreeBoneCount(0)) {
        m_unk0c = RtAnimInterpolatorCreate(m_unk49, 0x24);
    } else {
        m_unk0c = RtAnimInterpolatorCreateSubInterpolator(node->m_pRpHAnimHierarchy->currentAnim, m_unk48, m_unk49, 0x24);
    }
    RtAnimInterpolatorSetKeyFrameCallBacks(m_unk0c, 1);
    RtAnimInterpolatorSetAnimCallBack(m_unk0c, nullptr, 0.0f, nullptr);  // TOC -0x6a54: 0.0f
    RtAnimInterpolatorSetAnimLoopCallBack(m_unk0c, nullptr, nullptr);
    m_unk08 &= 0xfffffffdu;
    return 1;
}
