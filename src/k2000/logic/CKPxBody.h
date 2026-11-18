// CKPxBody.h - a rigid body of the engine's own physics (key 0x498c, vtable 0xb1fe18, size 0x12c). Original unit:
// CKPxBody.cpp (0x2182d0-0x21ae38). Base: KBase468C (the physics elements). Its subclass CKPxKinematic (0x580c, vtable
// 0xb1fe90, the same size) adds the axis locks (+0x12b). No XXL2 class; names ours. No game file holds a body
// (outputs/remake/kp3-class-usage.json): C2.8 port-final F03 ported the class layout (Load), its construction /
// destruction, the transform slots and the kinematic locks from the code; the solver (Integrate, the inertia update,
// the sample recorder, the kinematic drive) and the inline slots CKSrvPhysics calls (ExportState / InitFromDesc / vf58
// / Step, vt+0x50..+0x64) were left; C2.8 port-last Z7 ported them with CKSrvPhysics' body loops.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/math/CMatrix34.h"
#include "k2000/misc/KBase468C.h"
#include "k2000/util/TVector.h"

// The body's runtime description (vtable 0xb1fd70, 0x68 bytes; the kinematic one 0xb1ff08, 0x6c with a byte at
// +0x68): CreateRuntimeState (vt+0x6c) makes it, Destroy deletes it (vt+0x04), ExportState / InitFromDesc copy the
// body's parameters to / from it. Its destructor destroys the two matrices.
class CKPxBodyDesc {
public:
    CKPxBodyDesc();
    virtual ~CKPxBodyDesc();  // 0x009b2328 (0x9b22d0 deleting): both matrices destroyed

    uint32_t m_unk04;      // +0x04 0
    uint32_t m_unk08;      // +0x08 0
    uint32_t m_unk0c;      // +0x0c 0
    uint8_t m_unk10;       // +0x10 0
    uint8_t m_pad11[3];
    float m_fUnk14;        // +0x14 1.0 (the mass)
    CVector3 m_unk18;      // +0x18 (0, 0, 0)
    float m_fUnk24;        // +0x24 0
    float m_fUnk28;        // +0x28 0
    float m_fUnk2c;        // +0x2c 0.01
    CVector3 m_unk30;      // +0x30 (0, 0, 0)
    float m_fUnk3c;        // +0x3c 0
    float m_fUnk40;        // +0x40 0.01
    CVector3 m_unk44;      // +0x44 (0, 0, 0)
    float m_fUnk50;        // +0x50 0
    CVector3 m_unk54;      // +0x54 (0, 0, 0)
    CMatrix34* m_pUnk60;   // +0x60 RwMatrixCreate
    CMatrix34* m_pUnk64;   // +0x64 RwMatrixCreate
};

class CKPxKinematicDesc : public CKPxBodyDesc {
public:
    CKPxKinematicDesc() : m_ui8Unk68(0) {}
    ~CKPxKinematicDesc() override {}  // 0x009b3ac0 (0x9b3e78 deleting): the base's
    uint8_t m_ui8Unk68;    // +0x68 0
    uint8_t m_pad69[3];
};

class CKPxBody : public KBase468C {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x126)
    int32_t IsKindOfClass(uint32_t key) override { return key == 0x498c || key == 0x468c || key == 0xc; }
    DOTD_DECLARE_FACTORIES(CKPxBody)

    // 0x00218528 CKPxBody_Construct (= 0x218638 CKPxKinematic_ConstructBase_maybe, the same stores; 0x218e20 Create):
    // the base, the reference list empty with a capacity of 2, the record list with a capacity of 1 (blocks null).
    CKPxBody();
    // 0x00218c98 CKPxBody_Destructor (= 0x218b80 _BaseDestructor; 0x218c08 _DeletingDestructor adds the delete): the
    // record block freed, the reference block freed and the list emptied, then the base's.
    ~CKPxBody() override;

    // vt+0x10 0x002183f8 CKPxBody_Destroy: the description deleted, the six matrices destroyed (the pointers kept), both
    // blocks freed and emptied, then the base's (KStub: nothing).
    void Destroy() override;
    // vt+0x24 0x002183d0 CKPxBody_RecursiveRegistration: the base's vf24 (nothing), 1.
    void RecursiveRegistration(int32_t /*type*/) override {}
    // vt+0x2c 0x0021a298 CKPxBody_Load
    int32_t Load(IKFile* file, int32_t type) override;

    // C2.8 port-last Z7: the solver slots.
    // vt+0x50 0x009b2d18 CKPxBody_ExportState (inline): the parameters, the world matrix and the node offset (+0xf8)
    // copied into `desc`.
    virtual void ExportState(CKPxBodyDesc* desc);
    // vt+0x54 0x009b30f0 CKPxBody_InitFromDesc_maybe (inline): the parameters back from `desc` (+0x24 cleared, the mass's
    // inverse), the node offset and its inverse (+0xfc), then the world matrix as SetWorldMatrix sets it.
    virtual void InitFromDesc(const CKPxBodyDesc* desc);
    // vt+0x58 0x009b2f78 CKPxBody_vf58 (inline): `delta` added to the velocity (+0xa4); with flag 0x1000 a speed above
    // +0xb0 is scaled down to it, `delta` set to the change actually made and flag 0x2000 set (else cleared).
    virtual void AddVelocity(CVector3* delta);
    // vt+0x64 0x009b34b0 CKPxBody_Step_maybe (inline): Integrate, the sample and the shapes, then the sleep test:
    // a body not fixed (0x20) whose speeds sum (|v| + |w| per axis, squared over two) is below 1 counts the rest time
    // (+0x24); above 2 s it falls asleep (8; 0x1c and the reports cleared), above 0.1 s it is flagged 0x10.
    virtual void Step(float dt, float dt2, float frequency, float halfFrequencySq, uint8_t lastStep);

    // 0x00218ea8 CKPxBody_Integrate_maybe: the forces (friction 0x800 / the axis drag 0x100000, the pending +0x5c), the
    // acceleration (clamped with 0x1000), the move (+0xd8), the velocity (vt+0x58), gravity (unless 0x40), the angular
    // friction (unless 0x8000), the torques (+0x84 pending), the turn (+0xe4) and the angular velocity (clamped with
    // 0x10000 / 0x1000); the node synced on the last step.
    void Integrate(float dt, float dt2, float frequency, uint8_t lastStep);
    // Integrate's code, shared with CKPxKinematic_Integrate_maybe 0x21b9f8 (`kinematic`: its limits and axis locks).
    void IntegrateCommon(float dt, float dt2, float frequency, uint8_t lastStep, bool kinematic);
    // 0x00218790 CKPxBody_RecordSampleAndUpdateShapes_maybe: on the last step with flag 0x800000 a sample (acceleration,
    // velocity, local velocity, position, angular acceleration, angular velocity, local angular velocity, dt) written
    // into the parameter report's (+0x118) window; then every shape's world matrix updated.
    void RecordSampleAndUpdateShapes(float dt, uint8_t lastStep);
    // 0x00219e50 CKPxBody_UpdateInertiaTensor_maybe: the body inertia (+0x44): the diagonal +0x38 with flag 0x80000,
    // else the sum of the shapes' tensors (vt+0x5c) turned into the body frame, times the mass; its inverse (+0x48) and
    // the world inertia rebuilt.
    void UpdateInertiaTensor();
    // The parameters InitFromDesc takes back, up to the node offset's inverse (inlined in both InitFromDesc slots).
    void InitParametersFromDesc(const CKPxBodyDesc* desc);
    // The next constraint row (the inlined slot of every row writer): the one at the count (+0x128) when the block holds
    // it, else a new one at the end (the block grown by one when full; the size masked ~3 as the original).
    struct Record;
    Record* NextRecord();
    // The sleep test at the end of Step (0x9b34fc..).
    void UpdateRestState(float dt);
    // The reports cleared as Stop and the sleep test do: the constraint report (+0x114) when `flags` has 0x400000, the
    // parameter report (+0x118) when the body's flags have 0x800000.
    void ResetReports(uint32_t flags);

    // vt+0x5c 0x00219c70 CKPxBody_SetWorldMatrix_maybe: the world matrix (+0xf0) copied, the world inertia rebuilt, the
    // shapes moved, the node synced (with a node).
    virtual void SetWorldMatrix(const CMatrix34* matrix);
    // vt+0x60 0x002186a8 CKPxBody_vf60: the world matrix moved by `offset` (its dirty bit cleared), the shapes moved, the
    // node synced.
    virtual void Translate(const CVector3* offset);
    // vt+0x68 0x009b2cb8 CKPxBody_SyncNodeFromBody_maybe (inline): the node's local matrix = +0xfc times the world matrix.
    virtual void SyncNodeFromBody();
    // vt+0x6c 0x009b2b98 CKPxBody_CreateRuntimeState_maybe (inline): a new description at +0x28.
    virtual void CreateRuntimeState();

    // 0x002199e8 CKPxBody_ApplyTransform_maybe: the world matrix transformed (post-concatenated) by `transform` and
    // orthonormalised, the world inertia rebuilt, the shapes moved, the node synced.
    void ApplyTransform(const CMatrix34* transform);
    // 0x00219b30 CKPxBody_SyncFromNode_maybe: the node updated (its vt+0x50), the world matrix = +0xf8 times the node
    // frame's LTM, orthonormalised, the world inertia rebuilt, the shapes moved.
    void SyncFromNode();
    // The world inertia (+0x4c) = the world rotation's transpose times the local inertia (+0x48), post-concatenated with
    // the world matrix (inlined in Load, SetWorldMatrix, ApplyTransform, SyncFromNode, InitFromDesc).
    void RebuildWorldInertia();
    // Every shape of the container (+0x100: its +0x1c list, linked by +0x10) updates its world matrix.
    void UpdateShapes();

    uint32_t m_unk18;              // +0x18 read
    uint32_t m_unk1c;              // +0x1c read
    uint32_t m_ui32Flags;          // +0x20 read (0x20, 0x1000, 0x2000, 0x800000 tested by the solver)
    float m_fUnk24;                // +0x24 Load 0 (the solver's rest timer _maybe)
    CKPxBodyDesc* m_pDesc;         // +0x28 CreateRuntimeState
    float m_fMass;                 // +0x2c read
    float m_fInvMass;              // +0x30 1 / the mass
    CVector3* m_pGravity;          // +0x34 the physics service's +0x24 (its gravity _maybe)
    CVector3 m_unk38;              // +0x38 read (one 12-byte read)
    CMatrix34* m_pUnk44;           // +0x44 read
    CMatrix34* m_pLocalInertia;    // +0x48 read
    CMatrix34* m_pWorldInertia;    // +0x4c RwMatrixCreate; RebuildWorldInertia
    CVector3 m_unk50;              // +0x50 (0, 0, 0)
    CVector3 m_unk5c;              // +0x5c (0, 0, 0)
    float m_fUnk68;                // +0x68 read
    CVector3 m_unk6c;              // +0x6c read
    CVector3 m_unk78;              // +0x78 (0, 0, 0)
    CVector3 m_unk84;              // +0x84 (0, 0, 0)
    float m_fUnk90;                // +0x90 read
    CVector3 m_unk94;              // +0x94 read
    float m_fUnka0;                // +0xa0 read
    CVector3 m_unka4;              // +0xa4 read
    float m_fUnkb0;                // +0xb0 read
    float m_fUnkb4;                // +0xb4 read
    CVector3 m_unkb8;              // +0xb8 read
    float m_fUnkc4;                // +0xc4 read
    CVector3 m_unkc8;              // +0xc8 read
    float m_fUnkd4;                // +0xd4 read
    CVector3 m_unkd8;              // +0xd8 (0, 0, 0) (the kinematic locks: a linear velocity _maybe)
    CVector3 m_unke4;              // +0xe4 (0, 0, 0) (the kinematic locks: an angular velocity _maybe)
    CMatrix34* m_pWorldMatrix;     // +0xf0 read
    IKSerializable* m_pNode;       // +0xf4 reference: a CSGMovable (SyncNodeFromBody, SyncFromNode)
    CMatrix34* m_pUnkf8;           // +0xf8 read (SyncFromNode: the node-to-body offset)
    CMatrix34* m_pUnkfc;           // +0xfc read (SyncNodeFromBody: the body-to-node offset)
    IKSerializable* m_pContainer;  // +0x100 reference: its +0x1c is the shape list
    TVector<IKSerializable*, 2> m_vUnk104;  // +0x104 references (a 16-bit count)
    IKSerializable* m_pUnk110;     // +0x110 reference
    IKSerializable* m_pUnk114;     // +0x114 reference (a CKPxConstraintReport _maybe)
    IKSerializable* m_pUnk118;     // +0x118 reference (a CKPxParameterReport _maybe)
    struct Record {                // a constraint row (PS3 0x5c bytes; the joints and contact joints fill them, the
                                   // shapes' are gathered into the body's, ProcessBodyContacts solves them)
        uint32_t m_unk00;          // +0x00 copied as a word
        uint32_t m_unk04;          // +0x04 copied as a word
        CKPxBody* m_pBodyA;        // +0x08 the first body (its world inertia +0x4c, inverse mass +0x30)
        CVector3 m_vArmA;          // +0x0c the contact point from the first body
        CKPxBody* m_pBodyB;        // +0x18 the second body
        CVector3 m_vArmB;          // +0x1c the contact point from the second body
        CVector3 m_vNormal;        // +0x28 the row's direction
        float m_fUnk34;            // +0x34 (times the service's frequency +0x18)
        float m_fUnk38;            // +0x38 (times the service's +0x1c)
        CVector3 m_unk3c;          // +0x3c
        float m_fUnk48;            // +0x48
        CVector3 m_unk4c;          // +0x4c
        float m_fUnk58;            // +0x58
    };
    TVector<Record, 1> m_vRecords;  // +0x11c
    uint16_t m_ui16Unk128;         // +0x128 Load 0
    uint8_t m_ui8Unk12a;           // +0x12a read
    uint8_t m_ui8Unk12b;           // +0x12b CKPxKinematic: the axis locks (Load reads it; bits 0-2 the translation,
                                   // 3-5 the rotation)
};
DOTD_ASSERT_SIZE(CKPxBody, 0x12c);
DOTD_ASSERT_OFFSET(CKPxBody, m_unk18, 0x18);
DOTD_ASSERT_OFFSET(CKPxBody, m_pDesc, 0x28);
DOTD_ASSERT_OFFSET(CKPxBody, m_unk38, 0x38);
DOTD_ASSERT_OFFSET(CKPxBody, m_pWorldInertia, 0x4c);
DOTD_ASSERT_OFFSET(CKPxBody, m_fUnk68, 0x68);
DOTD_ASSERT_OFFSET(CKPxBody, m_fUnk90, 0x90);
DOTD_ASSERT_OFFSET(CKPxBody, m_unka4, 0xa4);
DOTD_ASSERT_OFFSET(CKPxBody, m_unkb8, 0xb8);
DOTD_ASSERT_OFFSET(CKPxBody, m_unkd8, 0xd8);
DOTD_ASSERT_OFFSET(CKPxBody, m_pWorldMatrix, 0xf0);
DOTD_ASSERT_OFFSET(CKPxBody, m_pContainer, 0x100);
DOTD_ASSERT_OFFSET(CKPxBody, m_vUnk104, 0x104);
DOTD_ASSERT_OFFSET(CKPxBody, m_vRecords, 0x11c);
DOTD_ASSERT_OFFSET(CKPxBody, m_ui16Unk128, 0x128);
DOTD_ASSERT_OFFSET(CKPxBody, m_ui8Unk12a, 0x12a);
