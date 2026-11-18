// CKMoveCpntUpdater.cpp - reconstructed original translation unit 0x24d2a8-0x24df08 (GAME_TOC1, main_toc1), 20 functions, 20 live.
// Primary class: CKMoveCpntUpdater  key 0x12c6  category Component  size 0x10  vtable 0xb20ea0
// Other owners: CKMoveCpnt (1), CKHkMovingObject (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x24d2a8  CKMoveCpntUpdater_GetMoveCpnt  (GetMoveCpnt, CKMoveCpntUpdater.h; CKHkMovingObject reads m_pMoveCpnt)
//   [ ] 0x24d2b0  RegisterCKMoveCpntUpdaterClass
//   [ ] 0x24d328  _GLOBAL__I_24d328
//   [x] 0x24d338  CKMoveCpnt_ApplySampleToMatrix_maybe
//   [x] 0x24d9c0  CKMoveCpntUpdater_ApplyToNode
//   [x] 0x24dad0  CKHkMovingObject_SampleMoveCpnt_maybe
//   [x] 0x24db60  CKMoveCpntUpdater_Evaluate
//   [x] 0x24dbf0  CKMoveCpntUpdater_Resume
//   [x] 0x24dc28  CKMoveCpntUpdater_Pause
//   [x] 0x24dc60  CKMoveCpntUpdater_Stop
//   [x] 0x24dc98  CKMoveCpntUpdater_Start
//   [x] 0x24dcd0  CKMoveCpntUpdater_DeleteArray
//   [x] 0x24dd70  CKMoveCpntUpdater_Create
//   [x] 0x24dda8  CKMoveCpntUpdater_SetMoveCpnt
//   [x] 0x24ddb0  CKMoveCpntUpdater_CreateArray
//   [ ] 0x24de40  CKMoveCpntUpdater_Save
//   [x] 0x24de48  CKMoveCpntUpdater_Load
//   [x] 0x24ded8  CKMoveCpntUpdater_PostLoad  (PostLoad, CKMoveCpntUpdater.h)
//   [x] 0x24def8  CKMoveCpntUpdater_RecursiveRegistration  (returns 1, registers nothing: the default)
//   [x] 0x24df00  CKMoveCpntUpdater_Destroy  (empty: the default)
//
//   [ ] 0x9ba0f8  CKMoveCpntUpdater_IsKindOfClass  [inline]
//   [x] 0x9ba120  CKMoveCpntUpdater_GetClassType  [inline]
//   [x] 0x9ba128  CKMoveCpntUpdater_GetClassID  [inline]
//   [ ] 0x9ba130  CKMoveCpntUpdater_DeletingDestructor  [inline]
//   [ ] 0x9ba178  CKMoveCpntUpdater_Destructor  [inline]
#include "k2000/components/CKMoveCpntUpdater.h"

#include <cstring>

#include "Renderware/rwcore/RwMatrix.h"
#include "Renderware/rwcore/RwCamera.h"
#include "k2000/core/Stub.h"
#include "k2000/io/IKFile.h"
#include "k2000/logic/CKMoveCpnt.h"
#include "k2000/logic/ai/CKFlaggedPath.h"
#include "k2000/logic/math/IKPath.h"
#include "k2000/misc/Mat4.h"
#include "k2000/scenegraph/CSGMovable.h"

#include "crt/ppc_ops.h"

// 0x0024de48 CKMoveCpntUpdater_Load
int32_t CKMoveCpntUpdater::Load(IKFile* file, int32_t type) {
    if (type == K_LEVEL_PLATEFORMS) IKFile_ReadRef(file, &m_pMoveCpnt);
    return 1;
}

namespace {

// An identity CMatrix34 with the flags 0x20003 (the stack matrices' stores).
void SetIdentity20003(CMatrix34* m) {
    m->m_right = {1.0f, 0.0f, 0.0f};  // TOC +0x04 1.0, +0x10 0.0
    m->m_up = {0.0f, 1.0f, 0.0f};
    m->m_at = {0.0f, 0.0f, 1.0f};
    m->m_pos = {0.0f, 0.0f, 0.0f};
    m->m_ui32Flags = 0x20003u;
    m->m_ui32pad1 = 0;
    m->m_ui32pad2 = 0;
    m->m_ui32pad3 = 0;
}

const CVector3 kAxisY = {0.0f, 1.0f, 0.0f};  // 0x00c50d40 (TOC +0x08; filled by a static initialiser)

void PostConcat(CMatrix34* m, const CMatrix34* transform) {  // 0x0023f760 Mat4_TransformPostConcat
    RwMatrixTransform(reinterpret_cast<RwMatrix*>(m), reinterpret_cast<const RwMatrix*>(transform), rwCOMBINEPOSTCONCAT);
}

}  // namespace

// 0x0024d338 CKMoveCpnt_ApplySampleToMatrix_maybe
void CKMoveCpntUpdater::ApplySampleToMatrix(const float* sample, CMatrix34* m) const {
    const CKMoveCpnt* cpnt = m_pMoveCpnt;
    CMatrix34 turn;
    SetIdentity20003(&turn);
    if (cpnt->m_pUnk0c != nullptr || cpnt->m_pUnk10 != nullptr) {
        // The path placement: the point (and direction) at channel 6's distance along the path (+0x0c, vt+0x54) or the
        // flagged path (+0x10: its beacons' triggers fire on the way).
        const float oldX = m->m_pos.x;
        const float oldY = m->m_pos.y;
        const float oldZ = m->m_pos.z;
        CMatrix34 frame;
        SetIdentity20003(&frame);
        CVector3 point;      // sp+0x70 (written by the path)
        CVector3 direction;  // sp+0x7c
        IKPath* path = static_cast<IKPath*>(cpnt->m_pUnk0c);
        CKFlaggedPath* flagged = static_cast<CKFlaggedPath*>(cpnt->m_pUnk10);
        bool offset = false;
        if (cpnt->m_unk14 != 0) {
            // Oriented along the path: the frame from the direction and the world up (+0x15: at / up, else up / forward).
            // (The PS3 passes the matrix in the paths' unused word.)
            if (path != nullptr) {
                path->GetPointAtDistance(sample[6], &point, &direction);  // vt+0x54
            } else {
                flagged->SetDistanceAndGetPosition(sample[6], &point, &direction, nullptr);  // 0x000c4eb8
            }
            if (cpnt->m_unk15 == 0) {
                Mat4_BuildFromUpAndForward(&frame, &kAxisY, &direction);  // 0x0023ff80
            } else {
                Mat4_SetBasisFromAtUp(&frame, &direction, &kAxisY);  // 0x0023fd30
            }
            if (cpnt->m_unk16 == 0) {
                Mat4_Multiply(&turn, cpnt->m_pMatrix, &frame);  // 0x0023f788
                PostConcat(m, &turn);
                offset = true;
            } else {
                frame.m_pos = point;
                frame.m_ui32Flags &= 0xfffdffffu;
                Mat4_Multiply(&turn, cpnt->m_pMatrix, &frame);
                PostConcat(m, &turn);
            }
        } else {
            // The point only.
            if (path != nullptr) {
                path->GetPointAtDistance(sample[6], &point, nullptr);  // vt+0x54
            } else {
                flagged->SetDistanceAndGetPosition(sample[6], &point, nullptr, nullptr);  // 0x000c4eb8
            }
            if (cpnt->m_unk16 == 0) {
                offset = true;
            } else {
                // The frame is the matrix +0x18's inverse placed at the point.
                Mat4_Invert(&frame, cpnt->m_pMatrix);  // 0x0023f878
                frame.m_pos = point;
                frame.m_ui32Flags &= 0xfffdffffu;
                Mat4_Multiply(&turn, cpnt->m_pMatrix, &frame);
                PostConcat(m, &turn);
            }
        }
        if (offset) {
            // The position from before the placement moved by the point less the offset +0x1c.
            const float dy = point.y - cpnt->m_unk1c[1];
            const float dz = point.z - cpnt->m_unk1c[2];
            const float dx = point.x - cpnt->m_unk1c[0];
            m->m_pos.y = oldY + dy;
            m->m_pos.z = oldZ + dz;
            m->m_pos.x = oldX + dx;
            m->m_ui32Flags &= 0xfffdffffu;
        }
        SetIdentity20003(&turn);  // 0x24d528: the turn matrix set again for the sample's rotations
    }
    float px = m->m_pos.x;
    float py = m->m_pos.y;
    float pz = m->m_pos.z;
    const CVector3* axes[3] = {&m->m_right, &m->m_up, &m->m_at};
    for (int32_t i = 0; i < 3; ++i) {
        const float d = sample[i];
        if (d == 0.0f) continue;
        px = ppc::fmadds(d, axes[i]->x, px);
        py = ppc::fmadds(d, axes[i]->y, py);
        pz = ppc::fmadds(d, axes[i]->z, pz);
    }
    for (int32_t i = 0; i < 3; ++i) {
        if (sample[3 + i] != 0.0f) Mat4_RotateInPlace(&turn, axes[i], sample[3 + i]);  // 0x00240498
    }
    float sx = 1.0f;
    float sy = 1.0f;
    float sz = 1.0f;
    if (sample[7] != 0.0f || sample[8] != 0.0f || sample[9] != 0.0f) {
        const float least = 0.01f;  // TOC +0x0c
        sx = sample[7] + 1.0f;
        if (sx < least) sx = least;
        sy = sample[8] + 1.0f;
        if (sy < least) sy = least;
        sz = sample[9] + 1.0f;
        if (sz < least) sz = least;
    }
    RwMatrixTransform(reinterpret_cast<RwMatrix*>(m), reinterpret_cast<const RwMatrix*>(&turn), rwCOMBINEPOSTCONCAT);  // 0x0023f760
    m->m_right = {sx * m->m_right.x, sx * m->m_right.y, sx * m->m_right.z};
    m->m_up = {sy * m->m_up.x, sy * m->m_up.y, sy * m->m_up.z};
    m->m_at = {sz * m->m_at.x, sz * m->m_at.y, sz * m->m_at.z};
    m->m_ui32Flags = m->m_ui32Flags & 0xfffdfffeu;
    m->m_pos.z = pz;
    m->m_pos.x = px;
    m->m_pos.y = py;
    m->m_ui32Flags = m->m_ui32Flags & 0xfffdffffu;
}

void CKMoveCpntUpdater::ApplyToNode(const float* sample, CSGMovable* node) const {
    CMatrix34 matrix;
    std::memcpy(&matrix, &node->m_pRwFrame->modelling, sizeof matrix);
    ApplySampleToMatrix(sample, &matrix);
    node->SetLocalMatrix(reinterpret_cast<const RwMatrix*>(&matrix));  // 0x000d0be8
}

uint8_t CKMoveCpntUpdater::Evaluate(float dt, float* out) {
    if (m_pMoveCpnt != nullptr) return m_pMoveCpnt->Advance(dt, out, this);  // 0x0024c988
    for (int32_t i = 0; i < 10; ++i) out[i] = 0.0f;
    return 0;
}

// 0x0024dad0 CKHkMovingObject_SampleMoveCpnt_maybe
uint8_t CKMoveCpntUpdater::SampleMoveCpnt(float time, float* out) {
    if (m_pMoveCpnt != nullptr) return m_pMoveCpnt->Sample(time, out, this);  // 0x0024c528
    for (int32_t i = 0; i < 10; ++i) out[i] = 0.0f;
    return 0;
}

void CKMoveCpntUpdater::Resume() {
    if (m_pMoveCpnt != nullptr) CKMoveCpnt::ResumeUpdater(this);
}

void CKMoveCpntUpdater::Pause() {
    if (m_pMoveCpnt != nullptr) CKMoveCpnt::PauseUpdater(this);
}

void CKMoveCpntUpdater::Stop() {
    if (m_pMoveCpnt != nullptr) CKMoveCpnt::ResetUpdater(this);
}

void CKMoveCpntUpdater::Start() {
    if (m_pMoveCpnt != nullptr) m_pMoveCpnt->StartUpdater(this);
}
