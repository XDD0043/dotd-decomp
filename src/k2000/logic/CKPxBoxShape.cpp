// CKPxBoxShape.cpp - reconstructed original translation unit 0x22db30-0x22e1c8 (GAME_TOC1, main_toc1), 16 functions, 16 live.
// Primary class: CKPxBoxShape  key 0x478c  category Logic  size 0xa4  vtable 0xb203e0
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x22db30  CKPxBoxShape_Delete
//   [ ] 0x22db80  RegisterCKPxBoxShapeClass
//   [ ] 0x22dbf8  _GLOBAL__I_22dbf8
//   [x] 0x22dc08  CKPxBoxShape_Load
//   [ ] 0x22dc30  CKPxBoxShape_Save
//   [x] 0x22dc58  CKPxBoxShape_RecursiveRegistration  (the base's vf24: returns 1, registers nothing)
//   [x] 0x22dc80  CKPxBoxShape_Destroy  (KBase474C's: the matrices destroyed)
//   [x] 0x22dca8  CKPxBoxShape_DeletingDestructor  (the destructor; delete)
//   [x] 0x22dcf0  CKPxBoxShape_Destructor  (C++ destructor chain: vtable stores only)
//   [x] 0x22dd20  CKPxBoxShape_BaseDestructor  (C++ destructor chain: vtable stores only)
//   [x] 0x22dd50  CKPxBoxShape_Construct  (header)
//   [x] 0x22dd88  CKPxBoxShape_Construct_2  (the constructor's second C++ variant)
//   [x] 0x22ddc0  CKPxBoxShape_DeleteArray
//   [x] 0x22de60  CKPxBoxShape_vf68  (AddGroundContact, vt+0x68)
//   [x] 0x22e0c0  CKPxBoxShape_CreateArray
//   [x] 0x22e170  CKPxBoxShape_Create
//
//   [ ] 0x9b5330  CKPxBoxShape_IsKindOfClass  [inline]
//   [ ] 0x9b5368  CKPxBoxShape_GetClassType  [inline]
//   [ ] 0x9b5370  CKPxBoxShape_GetClassID  [inline]
//   [ ] 0x9b5378  CKPxBoxShape_ExportState  [inline]
//   [ ] 0x9b5550  CKPxBoxShape_InitFromDesc_maybe  [inline]
//   [ ] 0x9b5728  CKPxBoxShape_vf64  [inline]  (returns 0; no caller in the ported code)
//   [x] 0x9b5730  CKPxBoxShape_vf60  [inline]  (GetSupportPoint)
//   [x] 0x9b5868  CKPxBoxShape_ComputeInertiaTensor_maybe  [inline]  (ComputeInertiaTensor)
#include "k2000/logic/CKPxBoxShape.h"

#include "k2000/logic/CKPxBody.h"
#include "k2000/logic/physics/CKPxContactJoint.h"
#include "k2000/misc/Engine.h"
#include "k2000/services/CKSrvCollision.h"
#include "k2000/services/CKSrvPhysics.h"

namespace {
const CVector3 kDown{0.0f, -1.0f, 0.0f};  // 0x00c50d7c (TOC1 -0x74c; a static initialiser fills it)
}  // namespace

// 0x0022dc08 CKPxBoxShape_Load
int32_t CKPxBoxShape::Load(IKFile* file, int32_t type) {
    KBase474C::Load(file, type);  // 0x0022d470
    return 1;
}

// 0x009b5868 CKPxBoxShape_ComputeInertiaTensor_maybe (vt+0x5c)
void CKPxBoxShape::ComputeInertiaTensor(CMatrix34* out) {
    out->m_right = {1.0f, 0.0f, 0.0f};
    out->m_ui32Flags = 0x20003;
    out->m_up = {0.0f, 1.0f, 0.0f};
    out->m_at = {0.0f, 0.0f, 1.0f};
    out->m_pos = {0.0f, 0.0f, 0.0f};
    const float xx = m_unk1c.x * m_unk1c.x;
    const float zz = m_unk1c.z * m_unk1c.z;
    const float yy = m_unk1c.y * m_unk1c.y;
    const float yz = yy + zz;
    const float xz = xx + zz;
    const float xy = xx + yy;
    out->m_right.x = yz / 3.0f;
    out->m_ui32Flags &= 0xfffdfffcu;
    out->m_up.y = xz / 3.0f;
    out->m_ui32Flags &= 0xfffdfffcu;
    out->m_at.z = xy / 3.0f;
    out->m_ui32Flags &= 0xfffdfffcu;
}

// 0x009b5730 CKPxBoxShape_vf60 (vt+0x60)
void CKPxBoxShape::GetSupportPoint(const CVector3* direction, CVector3* out) {
    CVector3 local;
    Mat4_TransformVectorsInline(m_pLocalMatrix, &local, direction, 1);  // 0x00240520 (the world matrix +0x34)
    CVector3 corner;
    corner.x = local.x > 0.0f ? m_unk1c.x : -m_unk1c.x;  // ble: NaN takes the negative
    corner.y = local.y > 0.0f ? m_unk1c.y : -m_unk1c.y;
    corner.z = local.z > 0.0f ? m_unk1c.z : -m_unk1c.z;
    Mat4_TransformPoints(m_pLocalMatrix, out, &corner, 1);  // 0x0023f7e8
}

// 0x0022de60 CKPxBoxShape_vf68 (vt+0x68)
void CKPxBoxShape::AddGroundContact() {
    CKPxBody* body = static_cast<CKPxBody*>(GetOwnerBody());  // 0x0022cb98
    m_GrdIn.m_fObjectHeight = m_fUnk28;
    CVector3 point;
    GetSupportPoint(&kDown, &point);  // vt+0x60
    static_cast<CKSrvCollision*>(g_pEngine->m_srvCollision)->GroundProbePoints(&m_GrdIn, &m_GrdInOut, &point.x, 1);
    const uint32_t status = m_GrdInOut.m_eContactStatus;
    if (status != 2) return;
    CKSrvPhysics* physics = static_cast<CKSrvPhysics*>(g_pEngine->m_srvPhysics);
    CKPxContactJoint* contact = physics->NextContactJoint();
    contact->SetBodies(body, nullptr);  // 0x002203e0
    contact->m_unk2c = point;
    contact->m_unk38 = m_GrdInOut.m_Normal;
    contact->m_unk44 = m_GrdInOut.m_fdH;
    float bounce = m_fUnk30;
    if (bounce <= 0.0f) {  // cror lt|eq: NaN goes on
        contact->m_unk18 = 0;
        bounce = 0.0f;
    } else if (!(bounce > 2.0f)) {  // ble: NaN takes it
        contact->m_unk18 = 1;
    } else {
        contact->m_unk18 = status;  // 2
        bounce = 2.0f;
    }
    contact->m_unk48 = bounce;
    physics->CommitContactJoint();
}
