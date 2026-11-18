// CKImpulsionCpnt.cpp - reconstructed original translation unit 0x24bc70-0x24c378 (GAME_TOC1, main_toc1), 17 functions, 15 live.
// Primary class: CKImpulsionCpnt  key 0x806  category Component  size 0x30  vtable 0xb20df0
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x24bc70  CKImpulsionCpnt_Delete
//   [ ] 0x24bcc0  CKImpulsionCpnt_Construct  [dead]
//   [ ] 0x24bcd0  CKImpulsionCpnt_Construct_2  [dead]
//   [x] 0x24bce0  CKImpulsionCpnt_Impulse
//   [x] 0x24bd40  CKImpulsionCpnt_Update
//   [ ] 0x24be48  RegisterCKImpulsionCpntClass
//   [ ] 0x24bec0  _GLOBAL__I_24bec0
//   [x] 0x24bed0  CKImpulsionCpnt_DeletingDestructor  (the deleting form of the implicit destructor)
//   [x] 0x24bf18  CKImpulsionCpnt_Destructor  (C++ destructor chain: vtable stores only)
//   [x] 0x24bf48  CKImpulsionCpnt_BaseDestructor  (C++ destructor chain: vtable stores only)
//   [x] 0x24bf78  CKImpulsionCpnt_DeleteArray
//   [x] 0x24c020  CKImpulsionCpnt_Create
//   [x] 0x24c058  CKImpulsionCpnt_CreateArray
//   [ ] 0x24c0f0  CKImpulsionCpnt_Save
//   [x] 0x24c0f8  CKImpulsionCpnt_RecursiveRegistration  (returns 1, registers nothing: the default)
//   [x] 0x24c100  CKImpulsionCpnt_Destroy  (empty: the default)
//   [x] 0x24c108  CKImpulsionCpnt_Load
//
//   [ ] 0x9b9fc8  CKImpulsionCpnt_IsKindOfClass  [inline]
//   [x] 0x9b9ff0  CKImpulsionCpnt_GetClassType  [inline]
//   [x] 0x9b9ff8  CKImpulsionCpnt_GetClassID  [inline]
#include "k2000/components/CKImpulsionCpnt.h"

#include "crt/ppc_ops.h"
#include "k2000/io/IKFile.h"

// 0x0024bce0 CKImpulsionCpnt_Impulse (step 6: the hero's flight flaps).
void CKImpulsionCpnt::Impulse(float scale) {
    if (m_unk20 != 0 && !(m_unk2c <= 0.0f)) return;  // TOC -0x7c / a stack 0.0
    m_unk2c = m_unk04[4] * scale;                      // +0x14
    if (m_unk04[2] != 0.0f) return;                    // +0x0c
    m_unk28 = scale * m_unk04[3];                      // +0x10
}

// 0x0024bd40 CKImpulsionCpnt_Update (step 6: the hero's flight flaps).
void CKImpulsionCpnt::Update(float dt) {
    const float timer = m_unk2c;
    float speed;
    if (timer > 0.0f) {  // TOC -0x7c
        m_unk2c = timer - dt;
        speed = m_unk28;
        const float top = m_unk04[3];  // +0x10
        if (top > speed) {
            speed = ppc::fmadds(dt, m_unk04[2], speed);  // +0x0c
            m_unk28 = speed;
            if (speed >= top) speed = top;
            m_unk28 = speed;
        }
    } else {
        speed = m_unk28;
        float lowest = m_unk04[6];  // +0x1c
        if (!(lowest >= speed)) {
            speed = speed - dt * m_unk04[5];  // +0x18
            m_unk28 = speed;
            if (!(speed < lowest)) lowest = speed;
            speed = lowest;
            m_unk28 = lowest;
        }
    }
    const float value = ppc::fmadds(dt, speed, m_unk24);
    m_unk24 = value;
    if (value <= m_unk04[1]) {  // +0x08
        m_unk24 = m_unk04[1];
        return;
    }
    if (value >= m_unk04[0]) {  // +0x04
        m_unk24 = m_unk04[0];
        return;
    }
    m_unk24 = value;
}

// 0x0024c108 CKImpulsionCpnt_Load. No type test: every type reads the data.
int32_t CKImpulsionCpnt::Load(IKFile* file, int32_t /*type*/) {
    for (float& v : m_unk04) ReadF32LE(file, &v);
    ReadU8(file, &m_unk20);
    return 1;
}
