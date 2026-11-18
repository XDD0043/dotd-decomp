// CKMecaCpnt.cpp - reconstructed original translation unit 0x3f7ab8-0x3f8130 (GAME_TOC1, main_toc1), 20 functions, 18 live.
// Primary class: CKMecaCpnt  key 0xac6  category Component  size 0x8  vtable 0xb24f10
// Other owners: CKGrpS08Meca (2), CKGrpMeca (1), ActiveActorList (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x3f7ab8  CKMecaCpnt_Delete
//   [ ] 0x3f7b08  RegisterCKMecaCpntClass
//   [ ] 0x3f7b80  _GLOBAL__I_3f7b80
//   [x] 0x3f7b90  CKMecaCpnt_Load
//   [ ] 0x3f7c70  CKMecaCpnt_Save
//   [x] 0x3f7c98  CKMecaCpnt_RecursiveRegistration  (the base's, inherited)
//   [x] 0x3f7cc0  CKMecaCpnt_Destroy  (the base's, inherited)
//   [x] 0x3f7ce8  CKMecaCpnt_DeletingDestructor
//   [x] 0x3f7d30  CKMecaCpnt_Destructor
//   [ ] 0x3f7d60  CKMecaCpnt_DestructBody  [dead: no pointer to its descriptor 0xbb1ce8]
//   [ ] 0x3f7d90  CKMecaCpnt_Construct  [dead]
//   [ ] 0x3f7dc8  CKMecaCpnt_Construct_2  [dead]
//   [x] 0x3f7e00  CKMecaCpnt_DeleteArray
//   [x] 0x3f7ea0  CKMecaCpnt_AppendPointAndRequestUpdate_maybe  (CKMecaCpnt::PlayMecaActivationFX)
//   [x] 0x3f7fb0  CKMecaCpnt_CreateArray
//   [x] 0x3f8060  CKMecaCpnt_Create
//   [x] 0x3f80b8  CKGrpS08Meca_BasePause_maybe  (CKGrpMeca's Pause (vt+0x70): empty, IKBaseGroup's)
//   [x] 0x3f80c0  CKGrpS08Meca_BaseResume_maybe  (CKGrpMeca's Resume (vt+0x78): empty, IKBaseGroup's)
//   [x] 0x3f80c8  CKGrpMeca_vfB8  (CKGrpMeca::GetParentClassID, k2000/misc/CKGrpMeca.h)
//   [x] 0x3f80d0  ActiveActorList_AddUnique_maybe  (CKGrpMeca::AddActiveActor, k2000/misc/CKGrpMeca.cpp)
//
//   [x] 0x9c0d18  CKMecaCpnt_IsKindOfClass  [inline]
//   [x] 0x9c0d50  CKMecaCpnt_GetClassType  [inline]
//   [x] 0x9c0d58  CKMecaCpnt_GetClassID  [inline]
#include "k2000/components/CKMecaCpnt.h"

#include "Renderware/rpprtstd/RpPrtStd.h"
#include "k2000/io/IKFile.h"
#include "k2000/math/CMatrix34.h"
#include "k2000/scenegraph/CParticlesNodeFx.h"

// C2.8 port-rest R02.

// 0x003f7b90 CKMecaCpnt_Load: the base's (reads nothing), then the particles reference for every load type.
int32_t CKMecaCpnt::Load(IKFile* file, int32_t type) {
    IKMecaCpnt::Load(file, type);  // 0x003f7a18
    IKFile_ReadRef(file, &m_pFx);
    return 1;
}

// 0x003f7ea0 CKMecaCpnt_AppendPointAndRequestUpdate_maybe: below 64 points, `position` appended to the emitter's point
// list (z, x, y stored) with property 0x2000; then properties 0x400 set (and 0x200 too with `flag`), 0x80000 cleared,
// the emission speed adjustment 0 (a word store) and the RpPrtStdEmitter's flags |= 0xa (ACTIVE | EMIT).
void CKMecaCpnt::PlayMecaActivationFX(const CVector3* position, int32_t flag) {
    CParticlesNodeFx* fx = m_pFx;
    if (fx->m_ui8NbActivePoints <= 0x3f) {
        RwV3d* at = &fx->m_pAdvEmtPointList->pointList[fx->m_ui8NbActivePoints];
        at->z = position->z;
        at->x = position->x;
        at->y = position->y;
        fx->m_sgProperties = (fx->m_sgProperties & ~0x2000u) | 0x2000u;
        fx->m_ui8NbActivePoints = static_cast<uint8_t>(fx->m_ui8NbActivePoints + 1);
        fx = m_pFx;
    }
    uint32_t properties = fx->m_sgProperties;
    if (flag != 0) properties = (properties & ~0x200u) | 0x200u;
    properties = (properties & ~0x400u) | 0x400u;
    properties &= ~0x80000u;
    fx->m_sgProperties = properties;
    fx->m_fEmissionSpeedAdjustment = 0.0f;  // stw 0
    fx->m_pRpPrtStdEmitter->flag |= rpPRTSTDEMITTERFLAGACTIVE | rpPRTSTDEMITTERFLAGEMIT;
}
