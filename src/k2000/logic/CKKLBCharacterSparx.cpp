// CKKLBCharacterSparx.cpp - reconstructed original translation unit 0x450480-0x450df0 (GAME_TOC1, main_toc1), 39 functions, 36 live.
// Primary class: CKKLBCharacterSparx  key 0x9f8c  category Logic  size 0x14  vtable 0xb26db0
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x450480  CKKLBCharacterSparx_Delete
//   [x] 0x4504d0  CKKLBCharacterSparx_Construct  [dead]
//   [ ] 0x4504e0  CKKLBCharacterSparx_Construct_2  [dead]
//   [ ] 0x4504f0  CKKLBCharacterSparx_Save
//   [x] 0x4504f8  CKKLBCharacterSparx_vf50
//   [ ] 0x450528  CKKLBCharacterSparx_vf58
//   [ ] 0x450548  CKKLBCharacterSparx_vf60
//   [ ] 0x450550  CKKLBCharacterSparx_vf88
//   [ ] 0x450580  CKKLBCharacterSparx_SetTarget_maybe
//   [ ] 0x4505b0  CKKLBCharacterSparx_vf98
//   [ ] 0x4505e0  CKKLBCharacterSparx_vf7C
//   [ ] 0x450610  CKKLBCharacterSparx_MoveTowardTarget_maybe
//   [ ] 0x450640  CKKLBCharacterSparx_vf70
//   [ ] 0x450668  CKKLBCharacterSparx_vf64
//   [x] 0x450690  CKKLBCharacterSparx_vf54
//   [x] 0x450708  CKKLBCharacterSparx_DeleteArray
//   [ ] 0x4507b0  RegisterCKKLBCharacterSparxClass
//   [ ] 0x450838  _GLOBAL__D_450838
//   [ ] 0x450848  _GLOBAL__I_450848
//   [ ] 0x450858  CKKLBCharacterSparx_vf84
//   [ ] 0x450888  CKKLBCharacterSparx_vf80
//   [ ] 0x4508c0  CKKLBCharacterSparx_vf94
//   [ ] 0x450908  CKKLBCharacterSparx_vfA4
//   [ ] 0x450938  CKKLBCharacterSparx_vfA0
//   [ ] 0x450950  CKKLBCharacterSparx_vf5C
//   [ ] 0x450988  CKKLBCharacterSparx_vf6C
//   [ ] 0x450a28  CKKLBCharacterSparx_vf68
//   [ ] 0x450a78  CKKLBCharacterSparx_vf78
//   [ ] 0x450aa8  CKKLBCharacterSparx_vf9C
//   [ ] 0x450ab8  CKKLBCharacterSparx_vf8C
//   [x] 0x450b30  CKKLBCharacterSparx_CreateArray
//   [x] 0x450bc8  CKKLBCharacterSparx_Create
//   [ ] 0x450c00  CKKLBCharacterSparx_RecursiveRegistration
//   [ ] 0x450c08  CKKLBCharacterSparx_PostLoad
//   [ ] 0x450c10  CKKLBCharacterSparx_Destroy
//   [x] 0x450c18  CKKLBCharacterSparx_Load
//   [ ] 0x450d68  CKKLBCharacterSparx_Destructor_2  [dead]
//   [ ] 0x450d88  CKKLBCharacterSparx_DeletingDestructor
//   [ ] 0x450dd0  CKKLBCharacterSparx_Destructor
//
//   [ ] 0x9c3cd0  CKKLBCharacterSparx_GetClassType  [inline]
//   [ ] 0x9c3cd8  CKKLBCharacterSparx_GetClassID  [inline]
//   [ ] 0x9c3ce0  CKKLBCharacterSparx_vfA8  [inline]
//   [ ] 0x9c3ce8  CKKLBCharacterSparx_IsKindOfClass  [inline]
#include "k2000/logic/CKKLBCharacterSparx.h"

#include <cstdint>

#include "Spyro2008/groups/CKGrpS08Hero.h"
#include "Spyro2008/hooks/CKHkS08Sparx.h"
#include "Spyro2008/logic/CKS08GameManager.h"
#include "k2000/core/Stub.h"
#include "k2000/io/IKFile.h"
#include "k2000/misc/Engine.h"

// 0x004504f8 CKKLBCharacterSparx_vf50: the hero group's Sparx (its +0xad0), or none without a group.
void CKKLBCharacterSparx::Vf50() {
    IKSerializable* group = static_cast<CKS08GameManager*>(g_pEngine->m_gameManager)->m_unk04[1];
    if (group != nullptr) {
        m_pSparx = static_cast<CKGrpS08Hero*>(group)->m_pUnkad0;
        return;
    }
    m_pSparx = nullptr;
}

// 0x00450690 CKKLBCharacterSparx_vf54: the Sparx lets go of this beacon when it is its current target
// (CKHkS08Sparx_ClearTargetIfCurrentAndPlayAnim_maybe 0x3f48a8, CKHkS08Sparx_StopMoveUpdaterIfCurrent_maybe
// 0x3f4318). The Sparx's Start clears the target (+0xb8), so at the level start nothing matches; STUB(C2.7)
// for the rest (the Sparx's behaviour is not ported).
void CKKLBCharacterSparx::Vf54() {
    const CKHkS08Sparx* sparx = static_cast<const CKHkS08Sparx*>(m_pSparx);
    if (reinterpret_cast<uintptr_t>(m_pBeacon) != sparx->m_unkB8[0]) return;
    DOTD_STUB_ONCE("CKKLBCharacterSparx_vf54: the Sparx releases its target (C2.7)");
}

// 0x00450c18 CKKLBCharacterSparx_Load
int32_t CKKLBCharacterSparx::Load(IKFile* file, int32_t type) {
    CKKLBCharacterBase::Load(file, type);
    if (type != K_LEVEL_PLATEFORMS) return 1;
    IKFile_ReadRef(file, &m_pMoveCpnt);
    IKFile_ReadRef(file, &m_pMoveUpdater);
    return 1;
}
