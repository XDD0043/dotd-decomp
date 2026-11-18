// CKSrvPhysics.cpp - reconstructed original translation unit 0x213028-0x218040 (GAME_TOC1, main_toc1), 29 functions, 28 live.
// Primary class: CKSrvPhysics  key 0x3c1  category Service  size 0x154  vtable 0xb1fcc0
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x213028  CKSrvPhysics_Delete
//   [x] 0x213078  CKSrvPhysics_Pause
//   [x] 0x213080  CKSrvPhysics_Resume
//   [x] 0x213088  CKSrvPhysics_DestroyService
//   [ ] 0x2130c8  RegisterCKSrvPhysicsClass
//   [ ] 0x213140  _GLOBAL__I_213140
//   [x] 0x213150  CKSrvPhysics_CollideBoxBoxSAT_maybe  (CollideBoxBoxSAT)
//   [x] 0x213fe0  CKSrvPhysics_IntegrateBodies_maybe  (the awake-body loop with the bodies' steps: C2.8 port-last Z7)
//   [x] 0x214220  CKSrvPhysics_DeleteArray
//   [ ] 0x2142c0  FUN_002142c0  [dead]
//   [x] 0x2143c0  CKSrvPhysics_Destroy
//   [x] 0x214460  CKSrvPhysics_InitializeService
//   [x] 0x2144a8  CKSrvPhysics_Construct
//   [x] 0x214568  CKSrvPhysics_Construct_2  (the constructor's second C++ variant)
//   [ ] 0x214628  CKSrvPhysics_Save
//   [x] 0x214630  CKSrvPhysics_RecursiveRegistration  (returns 1: the root's empty slot)
//   [x] 0x214638  CKSrvPhysics_Stop  (the bodies' reset and the contact list: port-last Z7)
//   [x] 0x214c10  CKSrvPhysics_DetectCollisions_maybe  (the awake-body loop with the shape contacts and box tests: port-last Z7)
//   [x] 0x214f30  CKSrvPhysics_CreateArray
//   [x] 0x215090  CKSrvPhysics_Create
//   [x] 0x215168  CKSrvPhysics_DeletingDestructor  (the destructor; delete)
//   [x] 0x215318  CKSrvPhysics_ProcessBodyContacts_maybe  (ProcessBodyContacts)
//   [x] 0x216668  CKSrvPhysics_GatherContacts_maybe  (the awake-body loop with the rows: port-last Z7)
//   [x] 0x216aa0  CKSrvPhysics_RunFixedSteps_maybe
//   [x] 0x216c88  UpdateCKSrvPhysics  (the time step, then RunFixedSteps; the rest feeds debug prints)
//   [x] 0x216e28  CKSrvPhysics_Start  (the bodies' preparation: port-last Z7)
//   [x] 0x217550  CKSrvPhysics_Destructor
//   [x] 0x2176f0  CKSrvPhysics_Load
//   [x] 0x217ea0  CKSrvPhysics_Destructor_2  (= 0x217550)
//
//   [ ] 0x9b2158  CKSrvPhysics_IsKindOfClass  [inline]
//   [ ] 0x9b2190  CKSrvPhysics_GetClassType  [inline]
//   [ ] 0x9b2198  CKSrvPhysics_GetClassID  [inline]
//   [x] 0x9b2480  CKSrvPhysics_WakeBodyIsland_maybe  [inline]  (WakeBodyIsland)
#include "k2000/services/CKSrvPhysics.h"

#include <cstdint>
#include <cstring>

#include "crt/ppc_ops.h"

#include "k2000/core/Stub.h"
#include "k2000/io/IKFile.h"
#include "k2000/logic/CKPxBody.h"
#include "k2000/logic/CKPxConstraintReport.h"
#include "k2000/logic/memory/CKPxContainer.h"
#include "k2000/logic/physics/CKPxContactJoint.h"
#include "k2000/misc/KBase474C.h"
#include "k2000/misc/KBase488C.h"
#include "k2000/misc/KBase468C.h"
#include "k2000/memory/Mem.h"
#include "k2000/misc/Engine.h"
#include "k2000/misc/Mat4.h"
#include "platform/fps.h"

namespace {
// One Read of count words, then every word byte-swapped in place (lwbrx/stw), as the original does.
void ReadWordsLE(IKFile* file, uint32_t* words, uint32_t count) {
    uint8_t* bytes = reinterpret_cast<uint8_t*>(words);
    file->Read(bytes, count * 4);
    for (uint32_t i = 0; i < count; ++i) {
        const uint8_t* b = bytes + 4 * i;
        words[i] = static_cast<uint32_t>(b[0]) | (static_cast<uint32_t>(b[1]) << 8) |
                   (static_cast<uint32_t>(b[2]) << 16) | (static_cast<uint32_t>(b[3]) << 24);
    }
}
CKPxContainer* Container(IKSerializable* object) { return static_cast<CKPxContainer*>(object); }
KBase468C* Element(IKSerializable* object) { return static_cast<KBase468C*>(object); }
CKPxBody* Body(IKSerializable* object) { return static_cast<CKPxBody*>(object); }

// A container's list emptied when it holds any (the inlined loop of RunFixedSteps and Stop): every element's owner,
// next and previous cleared (stw +0x08, +0x10, +0x0c), then the count, head and tail.
void ClearContainerList(CKPxContainer* container) {
    if (container->m_unk24 == 0) return;
    for (IKSerializable* object = container->m_unk1c; object != nullptr;) {
        KBase468C* element = Element(object);
        IKSerializable* next = element->m_unk10;
        element->m_unk08 = nullptr;
        element->m_unk10 = nullptr;
        element->m_unk0c = nullptr;
        object = next;
    }
    container->m_unk24 = 0;
    container->m_unk1c = nullptr;
    container->m_unk20 = nullptr;
}
}  // namespace

// 0x002144a8 CKSrvPhysics_Construct (the same stores inlined in 0x215090 CKSrvPhysics_Create).
CKSrvPhysics::CKSrvPhysics() {
    m_unk30.m_ui32NbElt = 1;
    m_unk30.m_pBlock = nullptr;
    m_unk30.m_ui32NbUsedElt = 0;
    m_unk114.m_ui32NbElt = 1;
    m_unk114.m_pBlock = nullptr;
    m_unk114.m_ui32NbUsedElt = 0;
    m_unk14e = 0;
    for (uint32_t i = 0; i < 5; ++i) m_unk138[i] = nullptr;
    m_unk14c = 0;
    m_ui32Priority = 0xcd;
    Engine_SetSrvPhysics(this);
}

// 0x00217550 CKSrvPhysics_Destructor (0x217ea0 _Destructor_2 the same, 0x215168 _DeletingDestructor then the delete):
// the engine's physics service cleared; the +0x138 table (m_unk14c arrays) and its four sibling arrays deleted; the two
// reference vectors' blocks freed. The +0x138 arrays are ProcessBodyContacts' solver tables (no game file holds a
// CKPxBody, so they stay null).
CKSrvPhysics::~CKSrvPhysics() {
    Engine_SetSrvPhysics(nullptr);
    float** table = static_cast<float**>(m_unk138[0]);
    for (uint16_t i = 0; i < m_unk14c; ++i) {
        if (table[i] != nullptr) delete[] table[i];
    }
    if (table != nullptr) delete[] table;
    m_unk138[0] = nullptr;
    for (uint32_t i = 1; i < 5; ++i) {
        if (m_unk138[i] != nullptr) delete[] static_cast<float*>(m_unk138[i]);
        m_unk138[i] = nullptr;
    }
    m_unk14c = 0;
    if (m_unk114.m_pBlock != nullptr) Mem_FreeAligned16(m_unk114.m_pBlock);
    m_unk114.m_ui32NbUsedElt = 0;
    m_unk114.m_pBlock = nullptr;
    if (m_unk30.m_pBlock != nullptr) Mem_FreeAligned16(m_unk30.m_pBlock);
    m_unk30.m_ui32NbUsedElt = 0;
    m_unk30.m_pBlock = nullptr;
}

// 0x00214460 CKSrvPhysics_InitializeService
int32_t CKSrvPhysics::InitializeService() {
    m_unkdc = RwMatrixCreate_Thunk();
    m_unke0 = RwMatrixCreate_Thunk();
    return 1;
}

// 0x00213088 CKSrvPhysics_DestroyService (the pointers are kept)
void CKSrvPhysics::DestroyService() {
    RwMatrixDestroy_Thunk(static_cast<CMatrix34*>(m_unkdc));  // 0x23f968
    RwMatrixDestroy_Thunk(static_cast<CMatrix34*>(m_unke0));
}

// 0x00216e28 CKSrvPhysics_Start: the accumulator cleared, then every body of +0x30 prepared: its inertia, its state
// exported into its description (vt+0x50), and an awake body (flag 2) woken with its island (WakeBodyIsland, inlined
// in the original one level deep). No game file holds a CKPxBody (outputs/remake/kp3-class-usage.json), so the list is
// empty in every level.
void CKSrvPhysics::Start() {
    m_unk20 = 0.0f;
    for (uint32_t i = 0; i < m_unk30.m_ui32NbUsedElt; ++i) {
        CKPxBody* body = Body(m_unk30.m_pBlock[i]);
        body->UpdateInertiaTensor();  // 0x00219e50
        body->ExportState(body->m_pDesc);  // vt+0x50
        if ((body->m_ui32Flags & 2) != 0) WakeBodyIsland(body);
    }
}

// 0x009b2480 CKSrvPhysics_WakeBodyIsland_maybe (inline)
void CKSrvPhysics::WakeBodyIsland(CKPxBody* body) {
    if ((body->m_ui32Flags & 0x14) != 0) return;
    if ((body->m_ui32Flags & 0x20) != 0) return;
    body->m_ui32Flags = (body->m_ui32Flags | 4) & ~0x18u;
    CKPxContainer::Unlink(body);
    Container(m_unk40)->PushFront(body);
    if (body->m_unk04 != nullptr) {
        body->m_unk04->MessageProc(0x2c00, reinterpret_cast<void*>(static_cast<uintptr_t>(body->m_unk14)));  // vt+0x1c
    }
    for (uint32_t i = 0; i < static_cast<uint16_t>(body->m_vUnk104.m_ui32NbUsedElt); ++i) {
        KBase488C* joint = static_cast<KBase488C*>(body->m_vUnk104.m_pBlock[i]);
        if ((joint->m_unk18 & 0x4000) != 0) continue;
        if ((joint->m_unk18 & 0x2000) != 0) continue;
        joint->m_unk18 |= 0x4000;
        if (joint->m_unk08 == nullptr) Container(m_unk54)->PushFront(joint);
        if (joint->m_unk1c != nullptr) WakeBodyIsland(Body(joint->m_unk1c));
        if (joint->m_unk24 != nullptr) WakeBodyIsland(Body(joint->m_unk24));
    }
}

// The pool's next contact joint linked at the head of the contact list (+0xd8), the pool's count up (the inlined tail of
// the shapes' contact slots and of CollideBoxBoxSAT).
void CKSrvPhysics::CommitContactJoint() {
    Container(m_unkd8)->PushFront(NextContactJoint());
    ++m_unk120;
}

// 0x00216c88 UpdateCKSrvPhysics: the time step 1/60 (0x3c888889) stored at +0x0c, then RunFixedSteps with it (the rest
// of the function, two frame-clock reads (vt+0x08) and the containers' counts, only feeds KStub_Nop_106d8 debug prints).
void CKSrvPhysics::Update(IKTime* /*frameClock*/) {
    m_unk0c = 0.016666668f;
    // --fps N (not in the original): 1/60 per 60 Hz frame (0..6 per displayed frame), so the bodies keep the speed
    // and the step sequence of 60 fps.
    if (dotd::fps::Unlocked()) {
        const int32_t ticks = dotd::fps::Ticks();
        for (int32_t i = 0; i < ticks; ++i) RunFixedSteps(&m_unk0c);
        return;
    }
    RunFixedSteps(&m_unk0c);
}

// 0x00216aa0 CKSrvPhysics_RunFixedSteps_maybe: dt added to the accumulator; while it is above 0, steps of 1 / frequency
// (+0x10), at most 11: the collisions, the joints' vt+0x60 (the container +0x54), the contact joints' records (+0xd8)
// then that list emptied, the contact count (+0x120) cleared, the contacts and the integration. `last` (passed on) is 1
// when the accumulator is used up (<= 0) or on step 10 (the 11th).
uint16_t CKSrvPhysics::RunFixedSteps(const float* dt) {
    m_unk20 = m_unk20 + *dt;  // fadds
    if (!(m_unk20 > 0.0f)) return 0;  // ble (NaN returns)
    uint16_t steps = 0;
    for (;;) {
        const float left = m_unk20 - m_unk10;  // fsubs
        m_unk20 = left;
        uint8_t last = 1;
        if (!(left <= 0.0f)) last = steps == 10 ? 1 : 0;  // cror lt|eq: NaN as above 0
        DetectCollisions();
        for (IKSerializable* object = Container(m_unk54)->m_unk1c; object != nullptr;) {
            KBase488C* joint = static_cast<KBase488C*>(object);
            object = joint->m_unk10;
            joint->Solve();  // vt+0x60
        }
        for (IKSerializable* object = Container(m_unkd8)->m_unk1c; object != nullptr;) {
            CKPxContactJoint* contact = static_cast<CKPxContactJoint*>(object);
            object = contact->m_unk10;
            contact->EmitContactRecord();  // 0x00221b40
        }
        ClearContainerList(Container(m_unkd8));
        m_unk120 = 0;
        GatherContacts(last);
        ++steps;
        IntegrateBodies(last);
        if (!(m_unk20 > 0.0f)) break;  // ble
        if (static_cast<int16_t>(steps) == 11) break;
    }
    return steps;
}

// 0x00214c10 CKSrvPhysics_DetectCollisions_maybe: per awake body (+0x40): its constraint report's count cleared (flag
// 0x400000), its shapes' ground (vt+0x68, unless flag 0x80) and wall (vt+0x6c, unless 0x100) contacts, then the box-box
// tests (CollideBoxBoxSAT, 10 points) of its shapes against every other awake body's and every sleeping body's (+0x44),
// unless either is flagged 0x200 or the collision mask (+0x58 [group +0x12a]) leaves the pair out.
void CKSrvPhysics::DetectCollisions() {
    for (IKSerializable* object = Container(m_unk40)->m_unk1c; object != nullptr;) {
        CKPxBody* body = Body(object);
        if ((body->m_ui32Flags & 0x400000) != 0) static_cast<CKPxConstraintReport*>(body->m_pUnk114)->m_ui16NbCurrent = 0;
        for (IKSerializable* s2 = Container(body->m_pContainer)->m_unk1c; s2 != nullptr;) {
            KBase474C* shape = static_cast<KBase474C*>(s2);
            if ((body->m_ui32Flags & 0x80) == 0) shape->AddGroundContact();  // vt+0x68
            if ((body->m_ui32Flags & 0x100) == 0) shape->AddWallContact();  // vt+0x6c
            s2 = shape->m_unk10;
        }
        for (int32_t pass = 0; pass < 2; ++pass) {
            for (IKSerializable* o2 = Container(pass == 0 ? m_unk40 : m_unk44)->m_unk1c; o2 != nullptr;) {
                CKPxBody* other = Body(o2);
                o2 = other->m_unk10;
                if (pass == 0 && other == body) continue;
                if ((body->m_ui32Flags & 0x200) != 0) continue;
                if ((other->m_ui32Flags & 0x200) != 0) continue;
                if ((ppc::slw(1u, other->m_ui8Unk12a) & m_unk58[body->m_ui8Unk12a]) != 0) continue;
                for (IKSerializable* a = Container(body->m_pContainer)->m_unk1c; a != nullptr;) {
                    KBase474C* shapeA = static_cast<KBase474C*>(a);
                    for (IKSerializable* b = Container(other->m_pContainer)->m_unk1c; b != nullptr;) {
                        KBase474C* shapeB = static_cast<KBase474C*>(b);
                        CollideBoxBoxSAT(shapeA, shapeB, 10);  // 0x00213150
                        b = shapeB->m_unk10;
                    }
                    a = shapeA->m_unk10;
                }
            }
        }
        object = body->m_unk10;
    }
}

// 0x00216668 CKSrvPhysics_GatherContacts_maybe: per awake body, the constraint rows of the bodies on its pending list
// (+0x110) appended to its own (+0x11c, count +0x128; written over the stale ones first, then grown by one), their counts
// cleared, then ProcessBodyContacts when the body has any; its count cleared.
void CKSrvPhysics::GatherContacts(uint8_t lastStep) {
    for (IKSerializable* object = Container(m_unk40)->m_unk1c; object != nullptr;) {
        CKPxBody* body = Body(object);
        TVector<CKPxBody::Record, 1>& rows = body->m_vRecords;
        for (IKSerializable* o2 = Container(body->m_pUnk110)->m_unk1c; o2 != nullptr;) {
            CKPxBody* child = Body(o2);
            for (uint32_t i = 0; i < child->m_ui16Unk128; ++i) {
                const CKPxBody::Record& row = child->m_vRecords.m_pBlock[i];
                const uint16_t at = body->m_ui16Unk128;
                if (at < rows.m_ui32NbUsedElt) {
                    rows.m_pBlock[at] = row;
                } else {
                    if (rows.m_ui32NbElt == rows.m_ui32NbUsedElt) {
                        uint32_t capacity = rows.m_ui32NbUsedElt + 1;
                        if (capacity == 0) capacity = 1;
                        rows.m_pBlock = static_cast<CKPxBody::Record*>(Mem_ReallocAligned16(
                            rows.m_pBlock, (capacity * static_cast<uint32_t>(sizeof(CKPxBody::Record))) & ~3u));
                        rows.m_ui32NbElt = capacity;
                    }
                    rows.m_pBlock[rows.m_ui32NbUsedElt] = row;
                    ++rows.m_ui32NbUsedElt;
                }
                ++body->m_ui16Unk128;
            }
            child->m_ui16Unk128 = 0;
            o2 = child->m_unk10;
        }
        if (body->m_ui16Unk128 != 0) ProcessBodyContacts(body, lastStep);  // 0x00215318
        object = body->m_unk10;
        body->m_ui16Unk128 = 0;
    }
}

// 0x00213fe0 CKSrvPhysics_IntegrateBodies_maybe: per awake body (its next read first), its pending list (+0x110) moved
// to the awake container's tail, the constraint report's snapshot on the last step (flag 0x400000), its vt+0x64 step
// with the service's step fields (+0x10, +0x14, +0x18, +0x1c), and a body that fell asleep (flag 8) moved to the
// sleeping container (+0x44).
void CKSrvPhysics::IntegrateBodies(uint8_t lastStep) {
    for (IKSerializable* object = Container(m_unk40)->m_unk1c; object != nullptr;) {
        CKPxBody* body = Body(object);
        CKPxContainer* pending = Container(body->m_pUnk110);
        if (pending->m_unk24 != 0) Container(m_unk40)->AppendAll(pending);
        IKSerializable* next = body->m_unk10;
        if (lastStep != 0 && (body->m_ui32Flags & 0x400000) != 0) {
            static_cast<CKPxConstraintReport*>(body->m_pUnk114)->SnapshotConstraintsEveryN();  // 0x002319e0
        }
        body->Step(m_unk10, m_unk14, m_unk18, m_unk1c, lastStep);  // vt+0x64
        if ((body->m_ui32Flags & 8) != 0) {
            CKPxContainer::Unlink(body);
            Container(m_unk44)->PushFront(body);
        }
        object = next;
    }
}

// 0x002143c0 CKSrvPhysics_Destroy: the two container lists freed.
void CKSrvPhysics::Destroy() {
    if (m_unk30.m_pBlock != nullptr) {
        Mem_FreeAligned16(m_unk30.m_pBlock);
        m_unk30.m_pBlock = nullptr;
    }
    m_unk30.m_ui32NbUsedElt = 0;
    m_unk30.m_pBlock = nullptr;
    if (m_unk114.m_pBlock != nullptr) {
        Mem_FreeAligned16(m_unk114.m_pBlock);
        m_unk114.m_pBlock = nullptr;
    }
    m_unk114.m_ui32NbUsedElt = 0;
    m_unk114.m_pBlock = nullptr;
    // IKService's part (0x1a5b8, empty) comes last here.
}

// 0x002176f0 CKSrvPhysics_Load
int32_t CKSrvPhysics::Load(IKFile* file, int32_t type) {
    if (type != K_LEVEL_PLATEFORMS) return 1;
    ReadF32LE(file, &m_unk18);
    const float frequency = m_unk18;
    m_unk20 = 0;
    const float half = frequency * frequency * 0x1p-1f;  // fmuls, then fmuls by the TOC's 0.5
    m_unk10 = 0x1p+0f / frequency;
    m_unk1c = half;
    m_unk14 = 0x1p+0f / half;
    uint32_t vector[3];
    ReadWordsLE(file, vector, 3);  // one 12-byte read
    std::memcpy(&m_unk24, vector, sizeof(vector));

    uint16_t count = 0;
    ReadU16LE(file, &count);
    if (count == 0) {
        m_unk30.m_ui32NbElt = 1;
        m_unk30.m_pBlock = static_cast<IKSerializable**>(Mem_AllocAligned16(static_cast<uint32_t>(sizeof(IKSerializable*))));
    } else {
        m_unk30.m_ui32NbElt = count;
        m_unk30.m_pBlock = static_cast<IKSerializable**>(Mem_AllocAligned16(count * static_cast<uint32_t>(sizeof(IKSerializable*))));
    }
    if (m_unk30.m_ui32NbElt < count) {  // as in the original: cannot happen right after the assignment
        uint32_t capacity = count + 1u;
        if (capacity == 0) capacity = 1;
        m_unk30.m_pBlock = static_cast<IKSerializable**>(
            Mem_ReallocAligned16(m_unk30.m_pBlock, capacity * static_cast<uint32_t>(sizeof(IKSerializable*))));
        m_unk30.m_ui32NbElt = capacity;
    }
    m_unk30.m_ui32NbUsedElt = count;
    IKFile_ReadObjectRefArray(file, m_unk30.m_pBlock, count);  // also with count 0, as in the original

    IKFile_ReadRef(file, &m_unk3c);
    IKFile_ReadRef(file, &m_unk40);
    IKFile_ReadRef(file, &m_unk44);
    ReadU32LE(file, &m_unk48);
    IKFile_ReadRef(file, &m_unk4c);
    IKFile_ReadRef(file, &m_unk50);
    IKFile_ReadRef(file, &m_unk54);
    ReadWordsLE(file, m_unk58, 32);  // one 0x80-byte read
    IKFile_ReadRef(file, &m_unkd8);

    m_unk114.m_ui32NbElt = 100;
    m_unk114.m_pBlock = static_cast<IKSerializable**>(Mem_AllocAligned16(100 * static_cast<uint32_t>(sizeof(IKSerializable*))));
    if (m_unk114.m_ui32NbElt < 100) {  // as in the original: cannot happen right after the assignment
        m_unk114.m_pBlock = static_cast<IKSerializable**>(
            Mem_ReallocAligned16(m_unk114.m_pBlock, 101 * static_cast<uint32_t>(sizeof(IKSerializable*))));
        m_unk114.m_ui32NbElt = 101;
    }
    m_unk114.m_ui32NbUsedElt = 100;
    IKFile_ReadObjectRefArray(file, m_unk114.m_pBlock, 100);
    m_unk120 = 0;
    IKFile_ReadRef(file, &m_unk124);
    IKFile_ReadRef(file, &m_unk128);
    ReadF32LE(file, &m_unk12c);
    ReadF32LE(file, &m_unk130);
    ReadF32LE(file, &m_unk134);
    m_unk150 = 0;
    return 1;
}

// 0x00214638 CKSrvPhysics_Stop: every body (the references at +0x30): an awake or resting one (0x1c) is put to sleep
// (0x1c cleared, its rows and reports cleared, its rest time 0) and moved to the container +0x3c, its owner told
// (0x2c02); then each body is reset from its description (vt+0x54), its forces cleared, its pending list emptied, its
// rows and reports cleared again; the contact joints' list (+0xd8) is emptied, the contact count cleared.
void CKSrvPhysics::Stop() {
    m_unk20 = 0.0f;
    for (uint32_t i = 0; i < m_unk30.m_ui32NbUsedElt; ++i) {
        CKPxBody* body = Body(m_unk30.m_pBlock[i]);
        const uint32_t flags = body->m_ui32Flags;
        if ((flags & 0x1c) != 0) {
            body->m_ui32Flags = flags & ~0x1cu;
            body->m_ui16Unk128 = 0;
            body->ResetReports(flags);
            body->m_fUnk24 = 0.0f;  // stw 0
            CKPxContainer::Unlink(body);
            Container(m_unk3c)->PushFront(body);
            if (body->m_unk04 != nullptr) {
                body->m_unk04->MessageProc(0x2c02, reinterpret_cast<void*>(static_cast<uintptr_t>(body->m_unk14)));
            }
        }
        body->InitFromDesc(body->m_pDesc);  // vt+0x54
        body->m_unk50 = CVector3{0.0f, 0.0f, 0.0f};  // the vector 0x00c50d64
        body->m_unk5c = CVector3{0.0f, 0.0f, 0.0f};
        body->m_unk78 = CVector3{0.0f, 0.0f, 0.0f};
        body->m_unk84 = CVector3{0.0f, 0.0f, 0.0f};
        ClearContainerList(Container(body->m_pUnk110));
        body->m_ui16Unk128 = 0;
        body->ResetReports(body->m_ui32Flags);
    }
    ClearContainerList(Container(m_unkd8));
    m_unk120 = 0;
}


namespace {

// a x b with the solver's operand order (each part fmsubs over two plain products; the products commute).
CVector3 CrossRows(const CVector3& a, const CVector3& b) {
    return CVector3{ppc::fmsubs(a.y, b.z, a.z * b.y), ppc::fmsubs(a.z, b.x, a.x * b.z), ppc::fmsubs(a.x, b.y, a.y * b.x)};
}

// One coupling term of ProcessBodyContacts' matrix through the shared body `body`: the response of row I's direction
// (`normalI`, negated for a second body) to a unit impulse of row J (`normalJ`, likewise): u = the world inertia times
// (armJ x normalJ), then normalI . (inverse mass * normalJ + u x armI).
float CouplingTerm(const CKPxBody* body, const CVector3& armI, const CVector3& normalI, const CVector3& armJ,
                   const CVector3& normalJ) {
    CVector3 t = CrossRows(armJ, normalJ);
    CVector3 u;
    Mat4_TransformVectors(body->m_pWorldInertia, &u, &t, 1);  // 0x0023f7b0
    const CVector3 c{ppc::fmsubs(u.y, armI.z, u.z * armI.y), ppc::fmsubs(u.z, armI.x, armI.z * u.x),
                     ppc::fmsubs(armI.y, u.x, u.y * armI.x)};
    const float m = body->m_fInvMass;
    const CVector3 g{ppc::fmadds(m, normalJ.x, c.x), ppc::fmadds(m, normalJ.y, c.y), ppc::fmadds(m, normalJ.z, c.z)};
    return ppc::fmadds(g.z, normalI.z, ppc::fmadds(g.x, normalI.x, g.y * normalI.y));
}

CVector3 Negated(const CVector3& v) { return CVector3{-v.x, -v.y, -v.z}; }

// The impulses `linear` (into the force +0x50 and the torque +0x78) and `bias` (into +0x5c and +0x84) at `arm`.
void ApplyRowImpulses(CKPxBody* body, const CVector3& arm, const CVector3& linear, const CVector3& bias) {
    body->m_unk50 = CVector3{linear.x + body->m_unk50.x, linear.y + body->m_unk50.y, linear.z + body->m_unk50.z};
    const CVector3 t1{ppc::fmsubs(linear.z, arm.y, linear.y * arm.z), ppc::fmsubs(linear.x, arm.z, linear.z * arm.x),
                      ppc::fmsubs(linear.y, arm.x, linear.x * arm.y)};
    body->m_unk78 = CVector3{t1.x + body->m_unk78.x, t1.y + body->m_unk78.y, t1.z + body->m_unk78.z};
    body->m_unk5c = CVector3{bias.x + body->m_unk5c.x, bias.y + body->m_unk5c.y, bias.z + body->m_unk5c.z};
    const CVector3 t2{ppc::fmsubs(bias.z, arm.y, bias.y * arm.z), ppc::fmsubs(bias.x, arm.z, bias.z * arm.x),
                      ppc::fmsubs(bias.y, arm.x, bias.x * arm.y)};
    body->m_unk84 = CVector3{t2.x + body->m_unk84.x, t2.y + body->m_unk84.y, t2.z + body->m_unk84.z};
}

// Whether the body's constraint report records rows of `kind` (its flags bit 0 for kind 0, 1 for 1, 2 for 2, 3 for 4,
// ... 8 for 0x80; other kinds never).
bool ReportRecordsKind(const CKPxBody* body, uint32_t kind) {
    const uint16_t flags = static_cast<CKPxConstraintReport*>(body->m_pUnk114)->m_ui16Flags;
    switch (kind) {
        case 0: return (flags & 1) != 0;
        case 1: return ((flags >> 1) & 1) != 0;
        case 2: return ((flags >> 2) & 1) != 0;
        case 4: return ((flags >> 3) & 1) != 0;
        case 8: return ((flags >> 4) & 1) != 0;
        case 0x10: return ((flags >> 5) & 1) != 0;
        case 0x20: return ((flags >> 6) & 1) != 0;
        case 0x40: return ((flags >> 7) & 1) != 0;
        case 0x80: return ((flags >> 8) & 1) != 0;
        default: return false;
    }
}

// The report's next current constraint (written over a stale one, else appended, grown by one).
CKPxConstraintReport::SConstraint* NextConstraint(CKPxConstraintReport* report) {
    TVector<CKPxConstraintReport::SConstraint, 1>& list = report->m_current;
    if (report->m_ui16NbCurrent < list.m_ui32NbUsedElt) return &list.m_pBlock[report->m_ui16NbCurrent];
    if (list.m_ui32NbElt == list.m_ui32NbUsedElt) {
        uint32_t capacity = list.m_ui32NbUsedElt + 1;
        if (capacity == 0) capacity = 1;
        list.m_pBlock = static_cast<CKPxConstraintReport::SConstraint*>(Mem_ReallocAligned16(
            list.m_pBlock, capacity * static_cast<uint32_t>(sizeof(CKPxConstraintReport::SConstraint))));  // 0x53190
        list.m_ui32NbElt = capacity;
    }
    return &list.m_pBlock[list.m_ui32NbUsedElt++];
}

}  // namespace

// 0x00215318 CKSrvPhysics_ProcessBodyContacts_maybe: the island's constraint rows (the body's +0x11c, count +0x128) solved
// together: the coupling matrix (the table +0x138 [0], kept and doubled when the count reaches its size +0x14c), the
// right-hand sides (+0x34 times the frequency +0x18, +0x38 times +0x1c) into [1] / [2] and, divided by the diagonal,
// as the start [3] / [4]; eight Gauss-Seidel sweeps; then each row's two impulses (its direction times [3] and [4])
// applied to its moving bodies (forces and torques +0x50 / +0x78, +0x5c / +0x84), and on the last step recorded in the
// constraint report of a body that records the row's kind (the first body's only, when it records).
void CKSrvPhysics::ProcessBodyContacts(CKPxBody* body, uint8_t lastStep) {
    const uint16_t count = body->m_ui16Unk128;
    m_unk14e = count;
    if (count >= m_unk14c) {
        float** table = static_cast<float**>(m_unk138[0]);
        if (m_unk14c != 0) {
            for (uint32_t i = 0; i < m_unk14c; ++i) {
                if (table[i] != nullptr) {
                    delete[] table[i];  // TocBridge_OperatorDeleteArray 0x98d360
                    table = static_cast<float**>(m_unk138[0]);
                }
            }
        }
        if (table != nullptr) delete[] table;
        m_unk138[0] = nullptr;
        for (uint32_t k = 1; k < 5; ++k) {
            if (m_unk138[k] != nullptr) delete[] static_cast<float*>(m_unk138[k]);
            m_unk138[k] = nullptr;
        }
        m_unk14c = static_cast<uint16_t>(m_unk14e << 1);
        table = new float*[m_unk14c];  // TocBridge_OperatorNewArray 0x98d380
        m_unk138[0] = table;
        for (uint32_t i = 0; i < m_unk14c; ++i) static_cast<float**>(m_unk138[0])[i] = new float[m_unk14c];
        m_unk138[1] = new float[m_unk14c];
        m_unk138[2] = new float[m_unk14c];
        m_unk138[3] = new float[m_unk14c];
        m_unk138[4] = new float[m_unk14c];
    }
    float** matrix = static_cast<float**>(m_unk138[0]);
    float* rhs1 = static_cast<float*>(m_unk138[1]);
    float* rhs2 = static_cast<float*>(m_unk138[2]);
    float* x1 = static_cast<float*>(m_unk138[3]);
    float* x2 = static_cast<float*>(m_unk138[4]);
    CKPxBody::Record* rows = body->m_vRecords.m_pBlock;
    for (uint32_t i = 0; i < body->m_ui16Unk128; ++i) {
        const CKPxBody::Record& ri = rows[i];
        for (uint32_t j = i; j < body->m_ui16Unk128; ++j) {
            const CKPxBody::Record& rj = rows[j];
            float& a = matrix[i][j];
            a = 0.0f;
            if (ri.m_pBodyA != nullptr) {
                if (rj.m_pBodyA == ri.m_pBodyA) {
                    a = CouplingTerm(ri.m_pBodyA, ri.m_vArmA, ri.m_vNormal, rj.m_vArmA, rj.m_vNormal) + 0.0f;
                } else if (rj.m_pBodyB == ri.m_pBodyA) {
                    a = CouplingTerm(ri.m_pBodyA, ri.m_vArmA, ri.m_vNormal, rj.m_vArmB, Negated(rj.m_vNormal)) + 0.0f;
                }
            }
            if (ri.m_pBodyB != nullptr) {
                if (rj.m_pBodyB == ri.m_pBodyB) {
                    a = a + CouplingTerm(ri.m_pBodyB, ri.m_vArmB, Negated(ri.m_vNormal), rj.m_vArmB,
                                         Negated(rj.m_vNormal));
                } else if (rj.m_pBodyA == ri.m_pBodyB) {
                    a = a + CouplingTerm(ri.m_pBodyB, ri.m_vArmB, Negated(ri.m_vNormal), rj.m_vArmA, rj.m_vNormal);
                }
            }
            matrix[j][i] = matrix[i][j];
        }
        rhs1[i] = ri.m_fUnk34 * m_unk18;
        rhs2[i] = ri.m_fUnk38 * m_unk1c;
        x1[i] = rhs1[i];
        x2[i] = rhs2[i];
        const float diagonal = matrix[i][i];
        if (diagonal != 0.0f) {
            const float inverse = 1.0f / diagonal;
            x1[i] = inverse * x1[i];
            x2[i] = inverse * x2[i];
        }
    }
    for (int32_t sweep = 0; sweep < 8; ++sweep) {
        for (uint32_t i = 0; i < m_unk14e; ++i) {
            float b1 = rhs1[i];
            float b2 = rhs2[i];
            for (uint32_t j = 0; j < i; ++j) {
                const float a = matrix[i][j];
                b1 = b1 - a * x1[j];
                b2 = b2 - a * x2[j];
            }
            for (uint32_t j = i + 1; j < m_unk14e; ++j) {
                const float a = matrix[i][j];
                b1 = b1 - a * x1[j];
                b2 = b2 - a * x2[j];
            }
            const float diagonal = matrix[i][i];
            if (diagonal != 0.0f) {
                const float inverse = 1.0f / diagonal;
                b2 = b2 * inverse;
                b1 = b1 * inverse;
            }
            x1[i] = b1;
            x2[i] = b2;
        }
    }
    for (uint32_t i = 0; i < body->m_ui16Unk128; ++i) {
        const CKPxBody::Record& r = body->m_vRecords.m_pBlock[i];
        const float s1 = x1[i];
        const float s2 = x2[i];
        const CVector3 linear{s1 * r.m_vNormal.x, s1 * r.m_vNormal.y, s1 * r.m_vNormal.z};
        const CVector3 bias{r.m_vNormal.x * s2, r.m_vNormal.y * s2, r.m_vNormal.z * s2};
        uint8_t record = lastStep;
        if (CKPxBody* a = r.m_pBodyA) {
            if (lastStep != 0 && (a->m_ui32Flags & 0x400000) != 0 && ReportRecordsKind(a, r.m_unk00)) {
                CKPxConstraintReport* report = static_cast<CKPxConstraintReport*>(a->m_pUnk114);
                const float along3c = ppc::fmadds(linear.z, r.m_unk3c.z, ppc::fmadds(linear.x, r.m_unk3c.x, linear.y * r.m_unk3c.y));
                const float along4c = ppc::fmadds(linear.z, r.m_unk4c.z, ppc::fmadds(linear.x, r.m_unk4c.x, linear.y * r.m_unk4c.y));
                CKPxConstraintReport::SConstraint* c = NextConstraint(report);
                c->m_pBodyA = a;
                c->m_vPointA = r.m_vArmA;
                c->m_pBodyB = r.m_pBodyB;
                c->m_vPointB = r.m_vArmB;
                c->m_vDirA = r.m_unk3c;
                c->m_unk2c = along3c;
                c->m_vDirB = r.m_unk4c;
                c->m_unk3c = along4c;
                ++report->m_ui16NbCurrent;
                record = 0;
            }
            ApplyRowImpulses(a, r.m_vArmA, linear, bias);
        }
        if (CKPxBody* b = r.m_pBodyB) {
            if (record != 0 && (b->m_ui32Flags & 0x400000) != 0 && ReportRecordsKind(b, r.m_unk00)) {
                CKPxConstraintReport* report = static_cast<CKPxConstraintReport*>(b->m_pUnk114);
                const float along4c = ppc::fnmadds(linear.z, r.m_unk4c.z, ppc::fmadds(linear.x, r.m_unk4c.x, linear.y * r.m_unk4c.y));
                const float along3c = ppc::fnmadds(linear.z, r.m_unk3c.z, ppc::fmadds(linear.x, r.m_unk3c.x, linear.y * r.m_unk3c.y));
                CKPxConstraintReport::SConstraint* c = NextConstraint(report);
                c->m_pBodyA = b;
                c->m_vPointA = r.m_vArmB;
                c->m_pBodyB = r.m_pBodyA;
                c->m_vPointB = r.m_vArmA;
                c->m_vDirA = Negated(r.m_unk3c);
                c->m_unk2c = along3c;
                c->m_vDirB = Negated(r.m_unk4c);
                c->m_unk3c = along4c;
                ++report->m_ui16NbCurrent;
            }
            ApplyRowImpulses(b, r.m_vArmB, Negated(linear), Negated(bias));
        }
    }
}

namespace {

// |x| as the original takes it: the float stored, its sign bit cleared in memory, reloaded.
float AbsMem(float x) {
    uint32_t bits;
    std::memcpy(&bits, &x, sizeof(bits));
    bits &= 0x7fffffffu;
    std::memcpy(&x, &bits, sizeof(bits));
    return x;
}

// The matrix's nine rotation floats by their byte offset (0, 4, 8, 0x10, ...), as the test reads them.
float At(const CMatrix34* m, uint32_t offset) {
    const float* f = reinterpret_cast<const float*>(m);
    return f[offset / 4];
}

constexpr float kFltMax = 3.4028235e+38f;  // the word at 0x00c4acb8 + 0x28 (0x7f7fffff)

}  // namespace

// 0x00213150 CKSrvPhysics_CollideBoxBoxSAT_maybe: two box shapes (their half extents +0x1c grown by 0.05, their world
// matrices +0x34) tested on the 15 separating axes (the relative rotation in +0xe0, its absolute values + 1e-6 in +0xdc,
// the centre offset +0xe4 and in A's frame +0xf0); a separating axis returns 0. The face axis of least depth (+0x108,
// +0x10c / +0x110) gives the normal (+0xfc, pointing from A to B), refined `maxPoints` times from the two support points
// (vt+0x60) towards the deepest direction (a positive gap beyond 0.1 returns 0; a converged direction returns 1 without
// a contact); then the pool's next contact joint gets the two bodies, B's support point, the normal reversed, the depth
// along it, bounce kind 1 / 0.3, and joins the contact list; 1.
int32_t CKSrvPhysics::CollideBoxBoxSAT(KBase474C* shapeA, KBase474C* shapeB, int32_t maxPoints) {
    CMatrix34 inverse{};
    Mat4_Invert(&inverse, shapeB->m_pLocalMatrix);  // 0x0023f878 (+0x34: the world matrix)
    CMatrix34* r = static_cast<CMatrix34*>(m_unke0);
    Mat4_Multiply(r, shapeA->m_pLocalMatrix, &inverse);  // 0x0023f788
    const CVector3& posA = shapeA->m_pLocalMatrix->m_pos;
    const CVector3& posB = shapeB->m_pLocalMatrix->m_pos;
    m_vSatDelta = CVector3{posB.x - posA.x, posB.y - posA.y, posB.z - posA.z};
    Mat4_TransformVectorsInline(shapeA->m_pLocalMatrix, &m_vSatDeltaLocal, &m_vSatDelta, 1);  // 0x00240520
    m_fSatDepth = -kFltMax;
    const float eps = 1e-6f;  // TOC1 -0xc70 (0x358637bd)
    CMatrix34* absR = static_cast<CMatrix34*>(m_unkdc);
    float* absF = reinterpret_cast<float*>(absR);
    static const uint32_t kOffsets[9] = {0, 4, 8, 0x10, 0x14, 0x18, 0x20, 0x24, 0x28};
    for (uint32_t k = 0; k < 9; ++k) {
        const float v = AbsMem(At(r, kOffsets[k])) + eps;
        absR->m_ui32Flags &= 0xfffdfffcu;
        absF[kOffsets[k] / 4] = v;
    }
    const float grow = 0.05f;  // TOC1 -0xc6c (0x3d4ccccd)
    const float hbx = shapeB->m_unk1c.x + grow;
    const float hby = shapeB->m_unk1c.y + grow;
    const float hbz = shapeB->m_unk1c.z + grow;
    const float hax = shapeA->m_unk1c.x + grow;
    const float hay = shapeA->m_unk1c.y + grow;
    const float haz = shapeA->m_unk1c.z + grow;
    const float tx = m_vSatDeltaLocal.x;
    const float ty = m_vSatDeltaLocal.y;
    const float tz = m_vSatDeltaLocal.z;
    auto A = [absR](uint32_t o) { return At(absR, o); };
    auto R = [r](uint32_t o) { return At(r, o); };
    // A's face axes.
    {
        const float rb = ppc::fmadds(hbz, A(8), ppc::fmadds(hbx, A(0), hby * A(4)));
        const float d = AbsMem(tx) - (hax + rb);
        if (d > 0.0f) return 0;  // ble goes on (NaN too)
        if (m_fSatDepth < d) {  // blt
            m_fSatDepth = d;
            m_ui32SatAxis = 0;
            m_ui32SatKind = 3;
        }
    }
    {
        const float rb = ppc::fmadds(hbz, A(0x18), ppc::fmadds(hbx, A(0x10), hby * A(0x14)));
        const float d = AbsMem(ty) - (hay + rb);
        if (d > 0.0f) return 0;  // bgt
        if (!(m_fSatDepth >= d)) {  // bge skips
            m_fSatDepth = d;
            m_ui32SatAxis = 1;
            m_ui32SatKind = 3;
        }
    }
    {
        const float rb = ppc::fmadds(hbz, A(0x28), ppc::fmadds(hbx, A(0x20), hby * A(0x24)));
        const float d = AbsMem(tz) - (haz + rb);
        if (d > 0.0f) return 0;
        if (!(m_fSatDepth >= d)) {
            m_fSatDepth = d;
            m_ui32SatAxis = 2;
            m_ui32SatKind = 3;
        }
    }
    // B's face axes (the columns of the relative rotation).
    const float hb[3] = {hbx, hby, hbz};
    for (uint32_t k = 0; k < 3; ++k) {
        const uint32_t c = 4 * k;
        const float ra = ppc::fmadds(haz, A(0x20 + c), ppc::fmadds(hax, A(0 + c), hay * A(0x10 + c)));
        const float proj = ppc::fmadds(tz, R(0x20 + c), ppc::fmadds(tx, R(0 + c), ty * R(0x10 + c)));
        const float d = AbsMem(proj) - (hb[k] + ra);
        if (d > 0.0f) return 0;
        if (!(m_fSatDepth >= d)) {
            m_fSatDepth = d;
            m_ui32SatAxis = 3;
            m_ui32SatKind = k;
        }
    }
    // The nine edge-edge axes: no depth kept, a gap returns 0 (blt: NaN goes on).
    if (ppc::fmadds(hbz, A(4), ppc::fmadds(hby, A(8), ppc::fmadds(hay, A(0x20), haz * A(0x10)))) <
        AbsMem(ppc::fmsubs(tz, R(0x10), ty * R(0x20)))) return 0;
    if (ppc::fmadds(hbz, A(0), ppc::fmadds(hbx, A(8), ppc::fmadds(hay, A(0x24), haz * A(0x14)))) <
        AbsMem(ppc::fmsubs(tz, R(0x14), ty * R(0x24)))) return 0;
    if (ppc::fmadds(hby, A(0), ppc::fmadds(hbx, A(4), ppc::fmadds(hay, A(0x28), haz * A(0x18)))) <
        AbsMem(ppc::fmsubs(tz, R(0x18), ty * R(0x28)))) return 0;
    if (ppc::fmadds(hbz, A(0x14), ppc::fmadds(hby, A(0x18), ppc::fmadds(hax, A(0x20), haz * A(0)))) <
        AbsMem(ppc::fmsubs(tx, R(0x20), tz * R(0)))) return 0;
    if (ppc::fmadds(hbz, A(0x10), ppc::fmadds(hbx, A(0x18), ppc::fmadds(hax, A(0x24), haz * A(4)))) <
        AbsMem(ppc::fmsubs(tx, R(0x24), tz * R(4)))) return 0;
    if (ppc::fmadds(hby, A(0x10), ppc::fmadds(hbx, A(0x14), ppc::fmadds(hax, A(0x28), haz * A(8)))) <
        AbsMem(ppc::fmsubs(tx, R(0x28), tz * R(8)))) return 0;
    if (ppc::fmadds(hbz, A(0x24), ppc::fmadds(hby, A(0x28), ppc::fmadds(hax, A(0x10), hay * A(0)))) <
        AbsMem(ppc::fmsubs(ty, R(0), tx * R(0x10)))) return 0;
    if (ppc::fmadds(hbz, A(0x20), ppc::fmadds(hbx, A(0x28), ppc::fmadds(hax, A(0x14), hay * A(4)))) <
        AbsMem(ppc::fmsubs(ty, R(4), tx * R(0x14)))) return 0;
    if (ppc::fmadds(hby, A(0x20), ppc::fmadds(hbx, A(0x24), ppc::fmadds(hax, A(0x18), hay * A(8)))) <
        AbsMem(ppc::fmsubs(ty, R(8), tx * R(0x18)))) return 0;
    // The normal: the chosen face axis of A (axis 0..2) or of B (axis 3, kind 0..2), towards B.
    const CMatrix34* frame = nullptr;
    uint32_t row = 0;
    if (m_ui32SatAxis == 3) {
        frame = shapeB->m_pLocalMatrix;
        row = m_ui32SatKind;
    } else {
        frame = shapeA->m_pLocalMatrix;
        row = m_ui32SatAxis;
    }
    if (row <= 2) {
        const CVector3* axes[3] = {&frame->m_right, &frame->m_up, &frame->m_at};
        m_vSatAxis = *axes[row];
    }
    CVector3& n = m_vSatAxis;
    if (ppc::fmadds(n.z, m_vSatDelta.z, ppc::fmadds(n.x, m_vSatDelta.x, n.y * m_vSatDelta.y)) < 0.0f) {  // blt
        n = CVector3{-n.x, -n.y, -n.z};
    }
    float bestX = n.x;
    float bestY = n.y;
    float bestZ = n.z;
    CVector3 supportA;
    CVector3 supportB;
    if (static_cast<uint16_t>(maxPoints) != 0) {
        float best = -kFltMax;
        const float slack = -0.1f;  // TOC1 -0xc68 (0xbdcccccd)
        for (uint16_t iteration = 0;;) {
            shapeA->GetSupportPoint(&n, &supportA);  // vt+0x60
            const CVector3 against{-n.x, -n.y, -n.z};
            shapeB->GetSupportPoint(&against, &supportB);
            const float wy = supportB.y - supportA.y;
            const float wx = supportB.x - supportA.x;
            const float wz = supportB.z - supportA.z;
            const float nx = n.x;
            const float ny = n.y;
            const float nz = n.z;
            const float gap = ppc::fmadds(wz, nz, ppc::fmadds(wx, nx, wy * ny)) + slack;
            if (gap > 0.0f) return 0;  // ble goes on
            if (!(best >= gap)) {  // bge skips
                best = gap;
                bestZ = nz;
                bestY = ny;
                bestX = nx;
            }
            // The next direction (w x n) x w.
            const float cz = ppc::fmsubs(wx, ny, wy * nx);
            const float cy = ppc::fmsubs(wz, nx, wx * nz);
            const float cx = ppc::fmsubs(wy, nz, wz * ny);
            float mx = ppc::fmsubs(wz, cy, wy * cz);
            float mz = ppc::fmsubs(wy, cx, wx * cy);
            float my = ppc::fmsubs(wx, cz, wz * cx);
            const CVector3 zero{0.0f, 0.0f, 0.0f};  // the vector 0x00c50d64
            if (mx - eps <= zero.x && mx + eps >= zero.x && my - eps <= zero.y && my + eps >= zero.y &&
                mz - eps <= zero.z && mz + eps >= zero.z) {  // cror lt|eq / gt|eq
                n = CVector3{bestX, bestY, bestZ};
                return 1;
            }
            const float length = std::sqrt(ppc::fmadds(mz, mz, ppc::fmadds(mx, mx, my * my)));  // Math_Sqrtf 0x10690
            if (length != 0.0f) {
                const float inverse = 1.0f / length;
                mz = mz * inverse;
                mx = mx * inverse;
                my = my * inverse;
            }
            ++iteration;
            n = CVector3{mx, my, mz};
            if (static_cast<uint16_t>(maxPoints) == iteration) break;
        }
    }
    n = CVector3{bestX, bestY, bestZ};
    shapeA->GetSupportPoint(&n, &supportA);  // vt+0x60
    const CVector3 against{-n.x, -n.y, -n.z};
    shapeB->GetSupportPoint(&against, &supportB);
    CKPxContactJoint* contact = NextContactJoint();
    const float wx = supportB.x - supportA.x;
    const float wy = supportB.y - supportA.y;
    const float wz = supportB.z - supportA.z;
    CKPxBody* bodyA = static_cast<CKPxBody*>(shapeA->GetOwnerBody());  // 0x0022cb98
    CKPxBody* bodyB = static_cast<CKPxBody*>(shapeB->GetOwnerBody());
    contact->SetBodies(bodyA, bodyB);  // 0x002203e0
    contact->m_unk2c = supportB;
    const CVector3 normal{-n.x, -n.y, -n.z};
    contact->m_unk38 = normal;
    contact->m_unk48 = 0.3f;  // TOC1 -0xc5c (0x3e99999a)
    contact->m_unk18 = 1;
    contact->m_unk44 = ppc::fmadds(wz, normal.z, ppc::fmadds(wx, normal.x, wy * normal.y));
    CommitContactJoint();
    return 1;
}

// The inlined sleep (see the header).
void CKSrvPhysics::PutBodyToSleep(CKPxBody* body) {
    const uint32_t flags = body->m_ui32Flags;
    body->m_ui32Flags = flags & ~0x1cu;
    body->m_ui16Unk128 = 0;
    body->ResetReports(flags);
    body->m_fUnk24 = 0.0f;  // stw 0
    body->m_ui32Flags |= 8;
    CKPxContainer::Unlink(body);
    Container(m_unk44)->PushFront(body);
    if (body->m_unk04 != nullptr) {
        body->m_unk04->MessageProc(0x2c01, reinterpret_cast<void*>(static_cast<uintptr_t>(body->m_unk14)));  // vt+0x1c
    }
}

namespace {
// An island's root: the body owning the container the body is in (its +0x18), or the body itself.
CKPxBody* IslandRoot(CKPxBody* body) {
    IKSerializable* owner = static_cast<CKPxContainer*>(body->m_unk08)->m_unk18;
    return owner != nullptr ? static_cast<CKPxBody*>(owner) : body;
}
// `body` (a root) moved into `into`'s island: its members appended to `into`'s list (+0x110), itself unlinked and put at
// the head of that list.
void MergeIsland(CKPxBody* body, CKPxBody* into) {
    CKPxContainer* from = static_cast<CKPxContainer*>(body->m_pUnk110);
    CKPxContainer* to = static_cast<CKPxContainer*>(into->m_pUnk110);
    if (from->m_unk24 != 0) to->AppendAll(from);
    if (body->m_unk08 != nullptr) CKPxContainer::Unlink(body);
    static_cast<CKPxContainer*>(into->m_pUnk110)->PushFront(body);
}
}  // namespace

// The inlined island merge (see the header).
CKPxBody* CKSrvPhysics::MergeIslands(CKPxBody* a, CKPxBody* b) {
    a = IslandRoot(a);
    b = IslandRoot(b);
    if (a == b) return a;
    const uint16_t countA = Container(a->m_pUnk110)->m_unk24;
    const uint16_t countB = Container(b->m_pUnk110)->m_unk24;
    if (countA < countB && a->m_unk18 != 1) {
        MergeIsland(a, b);
        return b;
    }
    MergeIsland(b, a);
    return a;
}
