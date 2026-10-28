// CKPxContactJoint.cpp - reconstructed original translation unit 0x220020-0x222068 (GAME_TOC1, main_toc1), 18 functions, 18 live.
// Primary class: CKPxContactJoint  key 0x4d0c  category Logic  size 0x4c  vtable 0xb1ffe8
// Other owners: PxContactPair (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x220020  CKPxContactJoint_Delete
//   [ ] 0x220070  RegisterCKPxContactJointClass
//   [ ] 0x2200e8  _GLOBAL__I_2200e8
//   [ ] 0x2200f8  CKPxContactJoint_Save
//   [ ] 0x220120  CKPxContactJoint_RecursiveRegistration
//   [ ] 0x220148  CKPxContactJoint_Destroy
//   [x] 0x220170  CKPxContactJoint_Construct
//   [x] 0x2201a8  CKPxContactJoint_DeleteArray
//   [ ] 0x220248  CKPxContactJoint_DeletingDestructor
//   [ ] 0x220290  CKPxContactJoint_Destructor
//   [ ] 0x2202c0  CKPxContactJoint_DestructBody
//   [x] 0x2202f0  CKPxContactJoint_Load
//   [ ] 0x2203a8  CKPxContactJoint_Construct_2
//   [ ] 0x2203e0  PxContactPair_SetBodies_maybe
//   [x] 0x220458  CKPxContactJoint_CreateArray
//   [x] 0x220508  CKPxContactJoint_Create
//   [ ] 0x220560  CKPxContactJoint_WakeIslandsAndPickBody_maybe
//   [ ] 0x221b40  CKPxContactJoint_EmitContactRecord_maybe
//
//   [ ] 0x9b4050  CKPxContactJoint_IsKindOfClass  [inline]
//   [ ] 0x9b4078  CKPxContactJoint_GetClassType  [inline]
//   [ ] 0x9b4080  CKPxContactJoint_GetClassID  [inline]
#include "k2000/logic/physics/CKPxContactJoint.h"

#include "k2000/io/IKFile.h"

namespace {

// 0x00c50d64 and 0x00c50d40: the shared vectors the original copies (live (0, 0, 0) and (0, 1, 0)).
const CVector3 kVector3_c50d64 = {0.0f, 0.0f, 0.0f};
const CVector3 kVector3_c50d40 = {0.0f, 1.0f, 0.0f};

}  // namespace

// 0x002202f0 CKPxContactJoint_Load
int32_t CKPxContactJoint::Load(IKFile* file, int32_t type) {
    KBase468C::Load(file, type);
    if (type != K_LEVEL_PLATEFORMS) return 1;
    m_unk24 = 0;
    m_unk18 = 0;
    m_unk1c = 0;
    m_unk2c = kVector3_c50d64;
    m_unk38 = kVector3_c50d40;
    m_unk48 = 0;
    m_unk44 = 0;
    return 1;
}
