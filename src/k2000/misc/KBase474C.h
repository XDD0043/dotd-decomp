// KBase474C.h - the physics shapes' unregistered base (key 0x474c; Ghidra CKPxShape_474c_maybe_*, vtable 0xb20368,
// size 0xa4). Original unit: CKPxShape.cpp (0x22cba8-0x22db30). Base: KBase468C. Its classes are CKPxBoxShape,
// CKPxCapsuleShape, CKPxCylinderShape, CKPxMeshShape and CKPxSphereShape. No game file holds a shape
// (outputs/remake/kp3-class-usage.json). Names ours; the ground-contact blocks have the XXL2 layout of
// IKProjectileType's (the same masks 1 / 8, face index -1 and contact status 3).
//
// C2.8 port-all P03 wrote this header for its three shapes (their constructor, Load and Destroy need it); the bodies
// are inline here and CKPxShape.cpp's checklist (P10's file) is left as it was: ConstructBase 0x22cec8 (the
// constructor below), Load 0x22d470, ClearReferences 0x22cbf8 (Destroy), vf24 0x22cbd0 / vf28 0x22cba8
// (RecursiveRegistration / Save: the base's, returning 1), BaseDestructor 0x22cc48 (the destructor).
// C2.8 port-last Z7: the solver slots the CKPx core calls (vt+0x5c ComputeInertiaTensor, vt+0x60 GetSupportPoint, vt+0x68
// AddGroundContact, vt+0x6c AddWallContact) and the world / local matrix updates (CKPxShape.cpp). The matrix at +0x34
// is the shape's world matrix (+0x38 times the owner's), the one at +0x38 the shape's offset in its owner (the names
// m_pLocalMatrix / m_pWorldMatrix below are swapped against that use; kept as P03 wrote them).
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/core/Stub.h"
#include "k2000/hooks/GroundContact.h"
#include "k2000/io/IKFile.h"
#include "k2000/math/CMatrix34.h"
#include "k2000/misc/KBase468C.h"
#include "k2000/misc/Mat4.h"
#include "k2000/services/CollisionDatas.h"

class KBase474C : public KBase468C {
public:
    // 0x0022cec8 CKPxShape_474c_maybe_ConstructBase: the base, the vtable, the ground masks (1, 8), the sector 0, the face
    // index -1, the contact status 3, the ground 0.
    KBase474C() {
        m_GrdIn.m_MasksOfGrdForTest[0] = 1;
        m_GrdIn.m_MasksOfGrdForTest[1] = 8;
        m_GrdInOut.m_ui8SectorNumber = 0;
        m_GrdInOut.m_i32FaceIndex = -1;
        m_GrdInOut.m_eContactStatus = 3;
        m_GrdInOut.m_pGround = nullptr;
    }
    ~KBase474C() override {}

    int32_t IsKindOfClass(uint32_t key) override { return key == 0x474c || key == 0x468c || key == 0xc; }
    // vt+0x2c 0x0022d470 CKPxShape_474c_maybe_Load: the base's, then (level data only) a word, a 16-bit word (+0xa0),
    // three words (one read), three words, two matrices (RwMatrixCreate + CMatrix34_LoadMatrix each) and the
    // ground-contact state reset.
    int32_t Load(IKFile* file, int32_t type) override {
        KBase468C::Load(file, type);  // 0x00218078
        if (type != K_LEVEL_PLATEFORMS) return 1;
        ReadU32LE(file, &m_unk18);
        ReadU16LE(file, &m_unka0);
        ReadU32LEWords(file, reinterpret_cast<uint32_t*>(&m_unk1c), 3);
        ReadF32LE(file, &m_fUnk28);
        ReadF32LE(file, &m_fUnk2c);
        ReadF32LE(file, &m_fUnk30);
        m_pLocalMatrix = RwMatrixCreate_Thunk();
        CMatrix34_LoadMatrix(m_pLocalMatrix, file);
        m_pWorldMatrix = RwMatrixCreate_Thunk();
        CMatrix34_LoadMatrix(m_pWorldMatrix, file);
        m_GrdIn.m_MasksOfGrdForTest[0] = 1;
        m_GrdIn.m_MasksOfGrdForTest[1] = 8;
        m_GrdInOut.m_pGround = nullptr;
        m_GrdIn.m_fDeltaMax = 0.0f;  // stw 0
        m_GrdInOut.m_ui8SectorNumber = 0;
        m_GrdInOut.m_i32FaceIndex = -1;
        m_GrdInOut.m_eContactStatus = 3;
        return 1;
    }
    // vt+0x10 0x0022cbf8 CKPxShape_474c_maybe_ClearReferences: both matrices destroyed (the pointers kept), then the
    // base's (empty).
    void Destroy() override {
        RwMatrixDestroy_Thunk(m_pLocalMatrix);  // 0x0023f968
        RwMatrixDestroy_Thunk(m_pWorldMatrix);
        KBase468C::Destroy();
    }

    // 0x0022cf40 CKPxShape_UpdateWorldMatrix_maybe: the world matrix (+0x34) = the offset (+0x38) times the owner's
    // (+0x04): a body's world matrix (+0xf0) when the flag 0x80 of +0xa0 is set, else a node's frame LTM (frame +0x50);
    // orthonormalised. Without an owner (flag clear) the offset is copied.
    void UpdateWorldMatrix();
    // 0x0022ccf0 CKPxShape_UpdateLocalFromWorld_maybe: the offset (+0x38) = the world matrix times the inverse of the
    // owner's (the identity without an owner), orthonormalised. No caller in the original.
    void UpdateLocalFromWorld();

    // vt+0x5c ComputeInertiaTensor_maybe (pure in the base): the shape's unit-mass inertia tensor into `out`.
    virtual void ComputeInertiaTensor(CMatrix34* /*out*/) {
        DOTD_STUB_ONCE("KBase474C vt+0x5c ComputeInertiaTensor: this shape's slot is not ported (only CKPxBoxShape's)");
    }
    // vt+0x60 (pure in the base): the shape's farthest world point in the world direction `direction`.
    virtual void GetSupportPoint(const CVector3* /*direction*/, CVector3* out) {
        DOTD_STUB_ONCE("KBase474C vt+0x60 GetSupportPoint: this shape's slot is not ported (only CKPxBoxShape's)");
        *out = CVector3{0.0f, 0.0f, 0.0f};
    }
    // vt+0x68 0x0022d738 KBase474C_AddGroundContact_maybe: the ground under the shape's lowest point into a contact
    // joint of CKSrvPhysics' pool (CKPxShape.cpp).
    virtual void AddGroundContact();
    // vt+0x6c 0x0022d0c0 KBase474C_vf6C: the walls along the body's velocity into a contact joint of the pool
    // (CKPxShape.cpp).
    virtual void AddWallContact();

    uint32_t m_unk18;             // +0x18
    CVector3 m_unk1c;             // +0x1c one 12-byte read, each word swapped (CKPxBoxShape: the half extents)
    float m_fUnk28;               // +0x28 the ground / wall probes' object height and radius
    float m_fUnk2c;               // +0x2c (KBase474C_vf58 0x9b4f78 sets it)
    float m_fUnk30;               // +0x30 the contacts' bounce: <= 0 kind 0, <= 2 kind 1, above kind 2 (capped at 2)
    CMatrix34* m_pLocalMatrix;    // +0x34 the Load: RwMatrixCreate, read from the file (the world matrix, see above)
    CMatrix34* m_pWorldMatrix;    // +0x38 the Load: RwMatrixCreate, read from the file (the offset, see above)
    CGroundContactDatasIn m_GrdIn;        // +0x3c the ground probe's input (the Load sets the delta 0)
    CGroundContactDatasInOut m_GrdInOut;  // +0x4c the ground probe's result
    CSlideGroundEdgeDatasOut m_SlideOut;  // +0x78 the wall probe's result (AddWallContact)
    uint16_t m_unka0;             // +0xa0 bit 0x80: the owner is a CKPxBody
    uint8_t m_pada2[2];
};
DOTD_ASSERT_SIZE(KBase474C, 0xa4);
DOTD_ASSERT_OFFSET(KBase474C, m_unk18, 0x18);
DOTD_ASSERT_OFFSET(KBase474C, m_pLocalMatrix, 0x34);
DOTD_ASSERT_OFFSET(KBase474C, m_GrdIn, 0x3c);
DOTD_ASSERT_OFFSET(KBase474C, m_GrdInOut, 0x4c);
DOTD_ASSERT_OFFSET(KBase474C, m_SlideOut, 0x78);
DOTD_ASSERT_OFFSET(KBase474C, m_unka0, 0xa0);
