// Reconstructed original translation unit: 0x89688-0x89908 (GAME_TOC1, main_toc1), 8 functions, 8 live.
// Primary class: CParticleGeometry  key 0x4a  category Geometry  size 0x34  vtable 0xb169d0
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x89688  CParticleGeometry_Delete  (DOTD_DECLARE_FACTORIES)
//   [x] 0x896d8  CParticleGeometry_RecursiveRegistration  (CGeometry.h: returns 1, registers nothing)
//   [ ] 0x896e0  CParticleGeometry_Save
//   [x] 0x896e8  CParticleGeometry_GetWorldBoundingSphere
//   [ ] 0x89798  RegisterCParticleGeometryClass
//   [ ] 0x89810  _GLOBAL__I_89810
//   [x] 0x89820  CParticleGeometry_vf80
//   [x] 0x898c8  CParticleGeometry_UnlockPTank_maybe
#include "Renderware/rpworld/RpAtomic.h"
#include "k2000/geometry/CGeometry.h"
#include "k2000/misc/Engine.h"
#include "k2000/services/CKSrvShadow.h"

// 0x000896e8 CParticleGeometry_GetWorldBoundingSphere: with render flag 0x200000 the atomic's sphere is
// already in world space: copied, the atomic's sphere-dirty flag (2) and its object flag 1 cleared;
// otherwise CGeometry's.
float* CParticleGeometry::GetWorldBoundingSphere(CNode* node) {
    if ((m_BitProperties & 0x200000) != 0) {
        RpAtomic* atomic = m_pRpAtomic;
        atomic->worldSphere[0] = atomic->boundingSphere[0];
        atomic->worldSphere[3] = atomic->boundingSphere[3];
        atomic->worldSphere[1] = atomic->boundingSphere[1];
        atomic->worldSphere[2] = atomic->boundingSphere[2];
        m_pRpAtomic->flags &= 0xfffffffdu;
        m_pRpAtomic->privateFlags &= 0xfe;
        return m_pRpAtomic->worldSphere;
    }
    return CGeometry::GetWorldBoundingSphere(node);
}

// 0x00089820 CParticleGeometry_vf80: CGeometry's (0x882a8) with the shadow service asked for mode 1 whatever the
// argument.
void CParticleGeometry::Vf80(int32_t /*mode*/) {
    const CKSrvShadow* shadow = static_cast<const CKSrvShadow*>(g_pEngine->m_srvShadow);
    if ((m_BitProperties & 0x800000) != 0 && shadow->IsShadowModeEnabled(1) != 0 && (m_BitProperties & 0x1000000) != 0) {
        SetShaderFlag(1);
        return;
    }
    SetShaderFlag(0);
}

// 0x000898c8 CParticleGeometry_UnlockPTank_maybe: (x != 0) as 0 / 1 through the sign trick of the original.
int32_t CParticleGeometry::UnlockPTank() { return RpPTankAtomicUnlock(m_pRpAtomic) != nullptr ? 1 : 0; }
