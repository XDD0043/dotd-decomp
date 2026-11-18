// Reconstructed original translation unit: 0x445dc8-0x4472f0 (GAME_TOC1, main_toc1), 23 functions, 19 live.
// Primary class: CKHkPxObject  key 0x1ac2  category Hook  size 0x54  vtable 0xb269d0
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [ ] 0x445dc8  RegisterCKHkPxObjectClass
//   [ ] 0x445e40  _GLOBAL__I_445e40
//   [x] 0x445e50  CKHkPxObject_AddContactPointsToFxNode28_maybe  (AddContactPointsToFxNode28)
//   [ ] 0x4461f0  CKHkPxObject_ApplyBodyTransform_maybe  [dead]
//   [x] 0x446218  CKHkPxObject_Resume  (the actor base's KStub_Nop_3f6e60: inherited)
//   [x] 0x446240  CKHkPxObject_Pause  (the actor base's KStub_Nop_3f6e58: inherited)
//   [x] 0x446268  CKHkPxObject_Stop  (the actor base's Stop: inherited)
//   [x] 0x446290  CKHkPxObject_Start  (the actor base's Start (CKHkActorBase_d82_maybe_ResetRuntime): inherited)
//   [ ] 0x4462b8  CKHkPxObject_Save
//   [x] 0x4462e0  CKHkPxObject_RecursiveRegistration  (the actor base's: inherited)
//   [x] 0x446308  CKHkPxObject_Destroy  (the actor base's: inherited)
//   [x] 0x446330  CKHkPxObject_DeletingDestructor  (the header's destructor)
//   [x] 0x446378  CKHkPxObject_Destructor  (the header's destructor)
//   [x] 0x4463a8  CKHkPxObject_BaseDestructor  (the header's destructor)
//   [ ] 0x4463d8  CKHkPxObject_Construct  [dead]
//   [ ] 0x446410  CKHkPxObject_Construct_2  [dead]
//   [x] 0x446448  CKHkPxObject_DeleteArray  (DOTD_DECLARE_FACTORIES(CKHkPxObject))
//   [ ] 0x4464e8  CKHkPxObject_UpdateContactSounds_maybe  [dead]
//   [x] 0x446830  CKHkPxObject_CreateArray  (DOTD_DECLARE_FACTORIES)
//   [x] 0x4468e0  CKHkPxObject_Create  (DOTD_DECLARE_FACTORIES: the header's constructor)
//   [x] 0x446938  CKHkPxObject_AddContactHistoryPointsToFxNode34_maybe  (AddContactHistoryPointsToFxNode34)
//   [x] 0x446de0  CKHkPxObject_Update  (Update)
//   [x] 0x446ef0  CKHkPxObject_Load
//
//   [ ] 0x9c3ae0  CKHkPxObject_IsKindOfClass  [inline]
//   [ ] 0x9c3b38  CKHkPxObject_GetClassType  [inline]
//   [ ] 0x9c3b40  CKHkPxObject_GetClassID  [inline]
//
// C2.8 port-all P18: left. No game file holds class 0x1ac2 CKHkPxObject (work/level-class-keys.json: the class tables of all twelve
// levels; outputs/remake/kp3-class-usage.json), so no object of it is ever created and none of these functions can run.
//
// C2.8 port-rest R05: the class is written (CKHkPxObject.h) with its Load and the inherited slots, although no game file
// holds one. Update (0x446de0) and its emitters 0x445e50 / 0x446938 read the CKPx body (+0x24: its +0x20 bit 0x400000,
// its contact points and contact history), a CKPxBody: R06's class (k2000/logic/CKPxBody.cpp, no header yet); they are
// left for it.
#include "k2000/hooks/CKHkPxObject.h"

#include <cstdint>
#include <cstring>

#include "Renderware/rpprtstd/RpPrtStd.h"
#include "Renderware/rpprtstd/RpPrtStdRuntime.h"
#include "Renderware/rwcore/RwCamera.h"
#include "crt/ppc_ops.h"
#include "k2000/io/IKFile.h"
#include "k2000/logic/CKPxBody.h"
#include "k2000/logic/CKPxConstraintReport.h"
#include "k2000/misc/Mat4.h"
#include "k2000/misc/PxJointRows.h"
#include "k2000/scenegraph/CParticlesNodeFx.h"

CKHkPxObject::CKHkPxObject() {}
CKHkPxObject::~CKHkPxObject() {}

// 0x00446ef0 CKHkPxObject_Load: every word read swapped (lwbrx), the byte not.
int32_t CKHkPxObject::Load(IKFile* file, int32_t type) {
    CKHkActorBase::Load(file, type);  // 0x003f6e98
    if (type != K_LEVEL_PLATEFORMS) return 1;
    ReadU8(file, &m_ui8Options);
    IKFile_ReadRef(file, &m_pBody);
    IKFile_ReadRef(file, &m_unk28);
    ReadF32LE(file, &m_fUnk2c);
    ReadF32LE(file, &m_fUnk30);
    IKFile_ReadRef(file, &m_unk34);
    ReadF32LE(file, &m_fUnk38);
    ReadF32LE(file, &m_fUnk3c);
    IKFile_ReadRef(file, &m_unk40);
    for (uint32_t i = 0; i < 4; ++i) ReadU32LE(file, &m_unk44[i]);
    return 1;
}

// ---- C2.8 port-last Z7: Update and the two contact emitters ----

namespace {

CKPxBody* Body(IKSerializable* object) { return static_cast<CKPxBody*>(object); }

// The emitter's standard property block (the emitter class's property offset 1).
RpPrtStdEmitterStandard* Standard(CParticlesNodeFx* node) {
    RpPrtStdEmitter* emitter = node->m_pRpPrtStdEmitter;
    return reinterpret_cast<RpPrtStdEmitterStandard*>(reinterpret_cast<uint8_t*>(emitter) +
                                                      emitter->emtClass->propTab->propOffset[1]);
}

// |x| as the original takes it: the sign bit cleared in memory.
float AbsBits(float x) {
    uint32_t bits;
    std::memcpy(&bits, &x, sizeof(bits));
    bits &= 0x7fffffffu;
    std::memcpy(&x, &bits, sizeof(bits));
    return x;
}

// An emit point appended (below 64): the world point turned into the node's frame, the direction, property 0x2000.
void AppendEmitPoint(CParticlesNodeFx* node, const CVector3* world, const CVector3& direction) {
    CVector3 local;
    Mat4_InverseTransformPoints(reinterpret_cast<const CMatrix34*>(&node->m_pRwFrame->ltm), &local, world, 1);  // 0x2405b0
    if (node->m_ui8NbActivePoints > 0x3f) return;
    RwV3d* point = &node->m_pAdvEmtPointList->pointList[node->m_ui8NbActivePoints];
    point->z = local.z;
    point->x = local.x;
    point->y = local.y;
    RwV3d* along = &node->m_pAdvEmtPointList->directionList[node->m_ui8NbActivePoints];
    along->z = direction.z;
    along->x = direction.x;
    along->y = direction.y;
    node->m_sgProperties = (node->m_sgProperties & ~0x2000u) | 0x2000u;
    node->m_ui8NbActivePoints = static_cast<uint8_t>(node->m_ui8NbActivePoints + 1);
}

}  // namespace

// 0x00445e50 CKHkPxObject_AddContactPointsToFxNode28_maybe: for each current constraint of the body's constraint report
// (+0x114), the relative velocity of the second body (none: still) against the body at the constraint point; faster
// than +0x2c, an emit point of the node +0x28 at the point along the velocity's direction, the particles' initial
// speed the relative speed times +0x30.
void CKHkPxObject::AddContactPointsToFxNode28() {
    for (uint32_t i = 0; i < static_cast<CKPxConstraintReport*>(Body(m_pBody)->m_pUnk114)->m_ui16NbCurrent; ++i) {
        CKPxBody* body = Body(m_pBody);
        CKPxConstraintReport* report = static_cast<CKPxConstraintReport*>(body->m_pUnk114);
        const CKPxConstraintReport::SConstraint& c = report->m_current.m_pBlock[i];
        const CVector3 velocityA = pxrows::VelocityAt(body, c.m_vPointA);
        CVector3 velocityB{0.0f, 0.0f, 0.0f};  // the vector 0x00c50d64
        if (c.m_pBodyB != nullptr) velocityB = pxrows::VelocityAt(Body(c.m_pBodyB), c.m_vPointB);
        CVector3 direction = pxrows::Sub(velocityB, velocityA);
        float speed = pxrows::Length(direction);
        bool emit;
        if (speed == 0.0f) {
            speed = 0.0f;
            emit = m_fUnk2c < speed;  // blt: NaN skips
        } else {
            const float inverse = 1.0f / speed;
            direction = CVector3{direction.x * inverse, direction.y * inverse, direction.z * inverse};
            emit = !(m_fUnk2c >= speed);  // bge: NaN emits
        }
        if (!emit) continue;
        CParticlesNodeFx* node = static_cast<CParticlesNodeFx*>(m_unk28);
        Standard(node)->prtInitVel = speed * m_fUnk30;
        const CVector3& pos = Body(m_pBody)->m_pWorldMatrix->m_pos;
        const CKPxConstraintReport::SConstraint& again = static_cast<CKPxConstraintReport*>(Body(m_pBody)->m_pUnk114)
                                                             ->m_current.m_pBlock[i];
        const CVector3 world{again.m_vPointA.x + pos.x, again.m_vPointA.y + pos.y, again.m_vPointA.z + pos.z};
        AppendEmitPoint(node, &world, direction);
    }
}

// 0x00446938 CKHkPxObject_AddContactHistoryPointsToFxNode34_maybe: with the constraint report recording (0x400000), each
// history slot from the oldest (the read slot, wrapping) that holds snapshots, each of its constraints without a second
// body: the body's velocity at the point (turned to world space) reversed; faster than +0x38, an emit point of the node
// +0x34 there, the particles emitted per point the emitter's count times (age + 1) / the history size, their initial
// speed the speed times +0x3c. The emitter's count is restored at the end.
void CKHkPxObject::AddContactHistoryPointsToFxNode34() {
    CParticlesNodeFx* node = static_cast<CParticlesNodeFx*>(m_unk34);
    const int32_t emitCount = Standard(node)->emtPrtEmit;
    if ((Body(m_pBody)->m_ui32Flags & 0x400000) != 0) {
        const uint16_t size = static_cast<CKPxConstraintReport*>(Body(m_pBody)->m_pUnk114)->m_ui16HistorySize;
        for (uint16_t k = 0; size != 0;) {
            CKPxConstraintReport* report = static_cast<CKPxConstraintReport*>(Body(m_pBody)->m_pUnk114);
            const uint16_t read = report->m_ui16Read;
            const uint16_t total = report->m_ui16HistorySize;
            uint32_t index = static_cast<uint32_t>(k) + read;
            if (static_cast<uint16_t>(index) >= total) index = index - total;
            const uint16_t write = report->m_ui16Write;
            TVector<CKPxConstraintReport::SConstraint, 1>* slot = nullptr;
            if (read < write) {
                slot = &report->m_history[write];
                if (!(static_cast<uint16_t>(index) > write)) slot = &report->m_history[static_cast<uint16_t>(index)];
            } else if (read > write) {
                slot = &report->m_history[static_cast<uint16_t>(index)];
            }
            if (slot != nullptr && slot->m_ui32NbUsedElt != 0) {
                for (uint32_t j = 0; j < slot->m_ui32NbUsedElt; ++j) {
                    const CKPxConstraintReport::SConstraint& c = slot->m_pBlock[j];
                    if (c.m_pBodyB != nullptr) continue;
                    CKPxBody* body = Body(m_pBody);
                    CVector3 arm;
                    Mat4_TransformVectors(body->m_pWorldMatrix, &arm, &c.m_vPointA, 1);  // 0x0023f7b0
                    const CVector3& pos = body->m_pWorldMatrix->m_pos;
                    const CVector3 world{arm.x + pos.x, arm.y + pos.y, arm.z + pos.z};
                    const CVector3 velocity = pxrows::VelocityAt(body, arm);
                    CVector3 direction{-velocity.x, -velocity.y, -velocity.z};
                    float speed = pxrows::Length(direction);
                    if (speed != 0.0f) {
                        const float inverse = 1.0f / speed;
                        direction = CVector3{direction.x * inverse, direction.y * inverse, direction.z * inverse};
                    } else {
                        speed = 0.0f;
                    }
                    if (m_fUnk38 >= speed) continue;  // bge: NaN emits
                    const float age = static_cast<float>(static_cast<double>(static_cast<int32_t>(k) + 1));
                    const float count = static_cast<float>(static_cast<double>(static_cast<uint32_t>(emitCount)));
                    const float slots = static_cast<float>(static_cast<double>(static_cast<int32_t>(size)));
                    const int64_t emit = ppc::fctidz(static_cast<double>((count * age) / slots));
                    CParticlesNodeFx* fx = static_cast<CParticlesNodeFx*>(m_unk34);
                    Standard(fx)->emtPrtEmit = static_cast<int32_t>(static_cast<uint32_t>(static_cast<uint64_t>(emit)));
                    fx->m_ui8NbEmitParticlesPerPoint = static_cast<uint8_t>(static_cast<uint64_t>(emit));
                    Standard(static_cast<CParticlesNodeFx*>(m_unk34))->prtInitVel = speed * m_fUnk3c;
                    AppendEmitPoint(static_cast<CParticlesNodeFx*>(m_unk34), &world, direction);
                }
            }
            ++k;
            if (k == size) break;
        }
    }
    CParticlesNodeFx* fx = static_cast<CParticlesNodeFx*>(m_unk34);
    Standard(fx)->emtPrtEmit = emitCount;
    fx->m_ui8NbEmitParticlesPerPoint = static_cast<uint8_t>(emitCount);
}

// 0x00446de0 CKHkPxObject_Update (vt+0x7c; WorldObjectBase_Update_Nop 0x3f6e68 first: empty): a body moving (|vx| + |vy|
// + |vz| at least 2) and recording its constraints (0x400000) emits at its contacts (option bit 0) and at its contact
// history (bit 1).
void CKHkPxObject::Update(IKTime* /*frameClock*/) {
    const CVector3& v = Body(m_pBody)->m_unka4;
    float sum = AbsBits(v.x) + AbsBits(v.y);
    sum = sum + AbsBits(v.z);
    if (sum < 2.0f) return;  // blt: NaN goes on
    if ((Body(m_pBody)->m_ui32Flags & 0x400000) == 0) return;
    if ((m_ui8Options & 1) != 0) AddContactPointsToFxNode28();
    if ((m_ui8Options & 2) != 0) AddContactHistoryPointsToFxNode34();
}
