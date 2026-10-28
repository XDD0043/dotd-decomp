//
// Reconstructed original translation unit: 0x1fee18-0x1ffbf8 (GAME_TOC1, main_toc1), 4 functions, 4 live.
// Primary owner: ShadowProjector (not a registered class)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [ ] 0x1fee18  ShadowProjector_ResetFade
//   [x] 0x1fee38  ShadowProjector_Bind
//   [ ] 0x1feff0  ShadowProjector_BuildGroundAlignedMatrix_maybe
//   [ ] 0x1ff2c0  ShadowProjector_Update
//
//   [ ] 0x9b1230  ShadowProjector_Destructor  [inline]
//   [ ] 0x9b1240  ShadowProjector_DeletingDestructor  [inline]

#include <cstring>

#include "k2000/core/Stub.h"
#include "k2000/geometry/CGeometry.h"
#include "k2000/logic/render/CMaterial.h"
#include "k2000/misc/Engine.h"
#include "k2000/scenegraph/CNode.h"
#include "k2000/services/CKSrvShadow.h"

// 0x001fee38 CKShadowSpot_SetData_maybe. The shadow component's fields are read by offset (its class is not
// ported): +0x1c a colour word, +0x20 and +0x24 floats.
void CKShadowSpot::SetData(IKSerializable* shadowCpnt, IKSerializable* leaf, void* ground) {
    const uint8_t* cpnt = reinterpret_cast<const uint8_t*>(shadowCpnt);
    auto word = [](const uint8_t* base, uint32_t offset) {
        uint32_t value;
        std::memcpy(&value, base + offset, 4);
        return value;
    };
    auto real = [](const uint8_t* base, uint32_t offset) {
        float value;
        std::memcpy(&value, base + offset, 4);
        return value;
    };
    m_pShadowCpnt = shadowCpnt;
    m_pLeaf = leaf;
    CGeometry* spotGeometry = static_cast<CGeometry*>(static_cast<CNode*>(g_pSrvShadow->m_pShadowSpotNode)->m_lGeometryList);
    const uint32_t color = word(cpnt, 0x1c);
    std::memcpy(m_cColor, &color, 4);
    for (int i = 0; i < 4; ++i) m_afColor[i] = static_cast<float>(m_cColor[i]);
    m_unk14 = word(cpnt, 0x1c);
    m_fUnk1c = real(cpnt, 0x20);
    static const CVector3 kUp = {0.0f, 1.0f, 0.0f};  // 0x00c50d40
    m_v3c = kUp;
    m_v30 = kUp;
    m_fUnk48 = real(cpnt, 0x24);
    // The spot node's material takes the service's shadow texture (SetMaterialTexture_maybe);
    // without a component it is cleared.
    static_cast<CMaterial*>(spotGeometry->m_pMaterial)
        ->SetTexture(m_pShadowCpnt == nullptr ? nullptr : static_cast<RwTexture*>(static_cast<CKSrvShadow*>(g_pEngine->m_srvShadow)->m_pShadowTexture));
    m_pGround = ground;
    m_unk58 = 1;
    m_unk5c = 8;
    m_fUnk50 = 0.2f;  // TOC1 -0x11ac (0x3e4ccccd)
    m_unk54 = 0;
    m_unk60 = 0;
    m_unk88 = 0;
    m_unk64 = -1;
    m_unk74 = 3;
}
