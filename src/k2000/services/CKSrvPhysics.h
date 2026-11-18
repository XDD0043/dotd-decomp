// CKSrvPhysics.h - the physics service (key 0x3c1, vtable 0xb1fcc0, size 0x154). Original unit:
// CKSrvPhysics.cpp (0x213028-0x218040). Not in XXL2; names ours. The references are CKPxContainer
// objects (live dump), the step fields derive from the read frequency.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/math/CMatrix34.h"
#include "k2000/services/IKService.h"
#include "k2000/util/TVector.h"

class CKPxBody;
class CKPxContactJoint;
class KBase474C;

class CKSrvPhysics : public IKService {
public:
    DOTD_CLASS_KEY(kCategoryService, 0xf)
    int32_t IsKindOfClass(uint32_t key) override {  // vt+0x08 0x9b2158
        return key == 0x3c1 || key == 0x1 || key == 0x3fe || key == 0xc;
    }
    DOTD_DECLARE_FACTORIES(CKSrvPhysics)

    CKSrvPhysics();  // 0x002144a8 CKSrvPhysics_Construct
    ~CKSrvPhysics() override;  // 0x00217550 CKSrvPhysics_Destructor

    void Destroy() override;  // vt+0x10 0x002143c0 CKSrvPhysics_Destroy
    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x002176f0 CKSrvPhysics_Load
    // vt+0x50 0x00216e28 CKSrvPhysics_Start: the step accumulator (+0x20) cleared, then every body (+0x30) prepared:
    // its inertia (CKPxBody_UpdateInertiaTensor_maybe), vt+0x50 with its +0x28, and an awake body not in the awake
    // container moved there (+0x40) with its joints (+0x54) and the bodies they link (CKSrvPhysics_WakeBodyIsland_maybe).
    void Start() override;
    void Stop() override;                               // vt+0x68 0x214638 CKSrvPhysics_Stop
    void Pause() override {}                            // vt+0x70 0x213078 CKSrvPhysics_Pause (empty)
    void Resume() override {}                           // vt+0x78 0x213080 CKSrvPhysics_Resume (empty)
    void Update(IKTime* frameClock) override;           // vt+0x7c 0x216c88 UpdateCKSrvPhysics
    // vt+0x94 0x214460 CKSrvPhysics_InitializeService: the two RwMatrix at +0xdc/+0xe0 (RwMatrixCreate),
    // then 1.
    int32_t InitializeService() override;
    // vt+0x98 0x00213088 CKSrvPhysics_DestroyService: the two matrices of InitializeService destroyed (RwMatrixDestroy_Thunk).
    void DestroyService() override;

    // The fixed-step loop (UpdateCKSrvPhysics). The awake bodies' list is the container +0x40 (KBase468C list: head
    // +0x1c, tail +0x20, count +0x24, the elements linked by +0x08 owner / +0x0c previous / +0x10 next).
    uint16_t RunFixedSteps(const float* dt);   // 0x00216aa0 CKSrvPhysics_RunFixedSteps_maybe
    void DetectCollisions();                  // 0x00214c10 CKSrvPhysics_DetectCollisions_maybe
    void GatherContacts(uint8_t lastStep);    // 0x00216668 CKSrvPhysics_GatherContacts_maybe
    void IntegrateBodies(uint8_t lastStep);   // 0x00213fe0 CKSrvPhysics_IntegrateBodies_maybe

    // C2.8 port-last Z7. 0x00213150 CKSrvPhysics_CollideBoxBoxSAT_maybe: the separating-axis test of two shapes' boxes;
    // up to `maxPoints` contact joints of the pool for the deepest axis.
    int32_t CollideBoxBoxSAT(KBase474C* shapeA, KBase474C* shapeB, int32_t maxPoints);
    // 0x00215318 CKSrvPhysics_ProcessBodyContacts_maybe: a body's gathered contact records (+0x11c, count +0x128).
    void ProcessBodyContacts(CKPxBody* body, uint8_t lastStep);
    // 0x009b2480 CKSrvPhysics_WakeBodyIsland_maybe (inline): a body that is neither asleep-locked (0x14) nor fixed (0x20)
    // woken (flag 4 set, 8 cleared) and moved to the awake container (+0x40), its owner told (0x2c00), then each of its
    // joints not yet visited (0x4000 / 0x2000 clear) marked, put in the joint container (+0x54) when in none, and the
    // two bodies it links woken the same way.
    void WakeBodyIsland(CKPxBody* body);
    // The inlined sleep of the joints' and contact joints' island code: the body's 0x1c cleared, its rows and reports
    // cleared, its rest time 0, flag 8, moved to the sleeping container (+0x44), its owner told (0x2c01).
    void PutBodyToSleep(CKPxBody* body);
    // The inlined island merge (KBase488C_vf5C 0x21df28, CKPxContactJoint_WakeIslandsAndPickBody_maybe 0x220560): the two
    // bodies' island roots (the body owning their container, else themselves); different ones are merged, the first's
    // into the second's when it is smaller and the first is not of kind 1, else the other way; the merged root returned.
    CKPxBody* MergeIslands(CKPxBody* a, CKPxBody* b);
    // The pool's next free contact joint (+0x114 [+0x120]).
    CKPxContactJoint* NextContactJoint() const {
        return reinterpret_cast<CKPxContactJoint*>(m_unk114.m_pBlock[m_unk120]);
    }
    // The pool's next contact joint linked at the head of the contact list (+0xd8), the pool's count (+0x120) up.
    void CommitContactJoint();

    float m_unk0c;                     // +0x0c not set by the constructor or Load (live: 1/60)
    float m_unk10;                     // +0x10 1 / m_unk18
    float m_unk14;                     // +0x14 1 / m_unk1c
    float m_unk18;                     // +0x18 read (LVL000: 60.0, a step frequency _maybe)
    float m_unk1c;                     // +0x1c m_unk18^2 * 0.5
    float m_unk20;                     // +0x20 the step accumulator (seconds; RunFixedSteps): Load, Start and Stop set 0
    CVector3 m_unk24;                  // +0x24 read (LVL000: 0, -9.8, 0: the gravity _maybe)
    TVector<IKSerializable*, 1> m_unk30;  // +0x30 read: references (CKPxContainer)
    IKSerializable* m_unk3c;           // +0x3c CKPxContainer
    IKSerializable* m_unk40;           // +0x40 CKPxContainer
    IKSerializable* m_unk44;           // +0x44 CKPxContainer
    uint32_t m_unk48;                  // +0x48 read (LVL000: 100)
    IKSerializable* m_unk4c;           // +0x4c CKPxContainer
    IKSerializable* m_unk50;           // +0x50 CKPxContainer
    IKSerializable* m_unk54;           // +0x54 CKPxContainer
    uint32_t m_unk58[32];              // +0x58 read: one 0x80-byte read, then every word byte-swapped
    IKSerializable* m_unkd8;           // +0xd8 CKPxContainer
    void* m_unkdc;                     // +0xdc RwMatrix (InitializeService)
    void* m_unke0;                     // +0xe0 RwMatrix (InitializeService)
    CVector3 m_vSatDelta;              // +0xe4 CollideBoxBoxSAT: the centre offset B - A (not set by the constructor or Load)
    CVector3 m_vSatDeltaLocal;         // +0xf0 the offset in A's frame
    CVector3 m_vSatAxis;               // +0xfc the contact normal
    float m_fSatDepth;                 // +0x108 the least face depth
    uint32_t m_ui32SatAxis;            // +0x10c its axis (0..2 A's faces, 3 B's)
    uint32_t m_ui32SatKind;            // +0x110 B's face (0..2), or 3
    TVector<IKSerializable*, 1> m_unk114;  // +0x114 read: 100 references (CKPxContainer)
    uint16_t m_unk120;                 // +0x120 Load sets 0
    uint16_t m_unk122;                 // +0x122 not set by the constructor or Load
    IKSerializable* m_unk124;          // +0x124 CKPxContainer
    IKSerializable* m_unk128;          // +0x128 CKPxContainer
    float m_unk12c;                    // +0x12c read (LVL000: 0.01)
    float m_unk130;                    // +0x130 read (LVL000: 1.0)
    float m_unk134;                    // +0x134 read (LVL000: 2 pi)
    void* m_unk138[5];                 // +0x138 the constructor sets 0; arrays (OperatorNewArray), [0] a table of m_unk14c arrays
    uint16_t m_unk14c;                 // +0x14c the constructor sets 0
    uint16_t m_unk14e;                 // +0x14e the constructor sets 0
    uint16_t m_unk150;                 // +0x150 Load sets 0
    uint16_t m_unk152;                 // +0x152 not set by the constructor or Load
};
DOTD_ASSERT_SIZE(CKSrvPhysics, 0x154);
DOTD_ASSERT_OFFSET(CKSrvPhysics, m_ui32Priority, 0x08);
DOTD_ASSERT_OFFSET(CKSrvPhysics, m_unk10, 0x10);
DOTD_ASSERT_OFFSET(CKSrvPhysics, m_unk18, 0x18);
DOTD_ASSERT_OFFSET(CKSrvPhysics, m_unk20, 0x20);
DOTD_ASSERT_OFFSET(CKSrvPhysics, m_unk24, 0x24);
DOTD_ASSERT_OFFSET(CKSrvPhysics, m_unk30, 0x30);
DOTD_ASSERT_OFFSET(CKSrvPhysics, m_unk3c, 0x3c);
DOTD_ASSERT_OFFSET(CKSrvPhysics, m_unk48, 0x48);
DOTD_ASSERT_OFFSET(CKSrvPhysics, m_unk54, 0x54);
DOTD_ASSERT_OFFSET(CKSrvPhysics, m_unk58, 0x58);
DOTD_ASSERT_OFFSET(CKSrvPhysics, m_unkd8, 0xd8);
DOTD_ASSERT_OFFSET(CKSrvPhysics, m_unk114, 0x114);
DOTD_ASSERT_OFFSET(CKSrvPhysics, m_unk120, 0x120);
DOTD_ASSERT_OFFSET(CKSrvPhysics, m_unk124, 0x124);
DOTD_ASSERT_OFFSET(CKSrvPhysics, m_unk12c, 0x12c);
DOTD_ASSERT_OFFSET(CKSrvPhysics, m_unk134, 0x134);
DOTD_ASSERT_OFFSET(CKSrvPhysics, m_unk138, 0x138);
DOTD_ASSERT_OFFSET(CKSrvPhysics, m_unk14c, 0x14c);
DOTD_ASSERT_OFFSET(CKSrvPhysics, m_unk150, 0x150);
