// Reconstructed original translation unit: 0x89688-0x89908 (GAME_TOC1, main_toc1), 8 functions, 8 live.
// Primary class: CParticleGeometry  key 0x4a  category Geometry  size 0x34  vtable 0xb169d0
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [ ] 0x89688  CParticleGeometry_Delete
//   [ ] 0x896d8  CParticleGeometry_RecursiveRegistration
//   [ ] 0x896e0  CParticleGeometry_Save
//   [x] 0x896e8  CParticleGeometry_GetWorldBoundingSphere
//   [ ] 0x89798  RegisterCParticleGeometryClass
//   [ ] 0x89810  _GLOBAL__I_89810
//   [ ] 0x89820  CParticleGeometry_vf80
//   [ ] 0x898c8  CParticleGeometry_UnlockPTank_maybe
#include "Renderware/rpworld/RpAtomic.h"
#include "k2000/geometry/CGeometry.h"

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
        m_pRpAtomic->objectFlags &= 0xfe;
        return m_pRpAtomic->worldSphere;
    }
    return CGeometry::GetWorldBoundingSphere(node);
}
