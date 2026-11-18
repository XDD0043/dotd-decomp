// CKGaugeCpnt.cpp - reconstructed original translation unit 0x24a0d0-0x24b248 (GAME_TOC1, main_toc1), 16 functions, 15 live.
// Primary class: CKGaugeCpnt  key 0xa84c  category Logic  size 0x64  vtable 0xb20d40
// Other owners: SuperGaugeRecord (2), CKGaugeCpntUpdater (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x24a0d0  CKGaugeCpnt_Delete
//   [x] 0x24a120  RegisterCKGaugeCpntType  (the class registry: ClassTable.inc 0xa84c / Kp3Ported.inc (gen_kp3_stubs.py); port-rest R07)
//   [ ] 0x24a198  _GLOBAL__I_24a198
//   [x] 0x24a1a8  CKGaugeCpnt_EvaluateSample_maybe
//   [x] 0x24a340  CKGaugeCpnt_UpdateDisplayedValue_maybe
//   [x] 0x24a4b0  CKGaugeCpnt_DeleteArray
//   [x] 0x24a550  CKGaugeCpnt_PostLoad  (IKSerializable's default (1))
//   [x] 0x24a558  CKGaugeCpnt_RecursiveRegistration  (IKSerializable's empty default)
//   [x] 0x24a560  CKGaugeCpnt_Destroy  (IKBaseClass's empty default)
//   [x] 0x24a568  CKGaugeCpnt_Create
//   [x] 0x24a618  CKGaugeCpnt_CreateArray
//   [ ] 0x24a740  CKGaugeCpnt_Save
//   [x] 0x24ac88  CKGaugeCpnt_Load
//   [x] 0x24b1c8  CKGaugeCpntUpdater_Delete  (CKGaugeCpntUpdater::Delete, DOTD_DECLARE_FACTORIES)
//   [x] 0x24b218  SuperGaugeRecord_Reset_maybe
//   [ ] 0x24b240  SuperGaugeRecord_GetCpnt_maybe  [dead]
//
//   [ ] 0x9b9dd8  CKGaugeCpnt_IsKindOfClass  [inline]
//   [x] 0x9b9e08  CKGaugeCpnt_GetClassType  [inline]
//   [x] 0x9b9e10  CKGaugeCpnt_GetClassID  [inline]
//   [ ] 0x9b9e18  CKGaugeCpnt_Destructor  [inline]
//   [ ] 0x9b9e90  CKGaugeCpnt_DeletingDestructor  [inline]
#include "k2000/logic/ui/CKGaugeCpnt.h"

#include "crt/ppc_ops.h"
#include "k2000/components/CKGaugeCpntUpdater.h"
#include "k2000/io/IKFile.h"
#include "k2000/memory/Mem.h"

// 0x0024a568 CKGaugeCpnt_Create, the inlined constructor: the two key lists, each with a block of 20 keys
// (0xa0 bytes), in the original's store order.
CKGaugeCpnt::CKGaugeCpnt() {
    m_unk14.m_pBlock = nullptr;
    m_unk14.m_ui32NbUsedElt = 0;
    m_unk14.m_ui32NbElt = 20;
    void* block = Mem_AllocAligned16(20 * static_cast<uint32_t>(sizeof(CurveKey)));
    m_unk28.m_ui32NbUsedElt = 0;
    m_unk14.m_pBlock = static_cast<CurveKey*>(block);
    m_unk28.m_ui32NbElt = 20;
    m_unk28.m_pBlock = nullptr;
    m_unk28.m_pBlock = static_cast<CurveKey*>(Mem_AllocAligned16(20 * static_cast<uint32_t>(sizeof(CurveKey))));
}

// 0x0024ac88 CKGaugeCpnt_Load
int32_t CKGaugeCpnt::Load(IKFile* file, int32_t type) {
    if (type == K_LEVEL_PLATEFORMS) {
        ReadF32LE(file, &m_unk04);
        IKFile_ReadRef(file, &m_pTransformation);
        IKFile_ReadRef(file, &m_pTransformationUpdater);
        ReadU8(file, &m_unk10);
        CurveKeys_Load(&m_unk14, file);
        ReadU8(file, &m_unk38);
        ReadF32LE(file, &m_unk3c);
        ReadF32LE(file, &m_unk40);
        ReadU8(file, &m_unk44);
        IKFile_ReadRef(file, &m_pCurve48);
        ReadU8(file, &m_unk50);
        ReadF32LE(file, &m_unk54);
        ReadF32LE(file, &m_unk58);
        ReadU8(file, &m_unk5c);
        IKFile_ReadRef(file, &m_pCurve60);
    }
    // Every type.
    ReadF32LE(file, &m_unk34);
    ReadF32LE(file, &m_unk4c);
    ReadU8(file, &m_unk20);
    ReadU8(file, &m_unk21);
    ReadF32LE(file, &m_unk24);
    CurveKeys_Load(&m_unk28, file);
    return 1;
}

// 0x0024a1a8 CKGaugeCpnt_EvaluateSample_maybe
void CKGaugeCpnt::EvaluateSample(float t, GaugeSample* sample, CKGaugeCpntUpdater* record) const {
    for (int32_t i = 0; i < 9; ++i) sample->m_transform.m_abSet[i] = 0;
    for (int32_t i = 0; i < 9; ++i) sample->m_transform.m_af[i] = 0.0f;
    sample->m_bHasColor = 0;
    for (int32_t i = 0; i < 4; ++i) sample->m_aColor[i] = 0xff;
    m_pTransformationUpdater->Restart();
    m_pTransformation->Evaluate(t, &sample->m_transform, m_pTransformationUpdater);
    if (m_unk10 != 0) {
        sample->m_bHasColor = 1;
        ColorCurve_Evaluate(t, sample->m_aColor, &m_unk14);
    }
    if (m_unk20 != 0 && record->m_unk18 != 0) {
        const float x = m_unk24 > 0.0f ? record->m_fFlashTime / m_unk24 : 1.0f;  // lfs TOC-0xc4 = 1.0
        sample->m_bHasColor = 1;
        ColorCurve_Evaluate(x, sample->m_aColor, &m_unk28);
    }
}

// 0x0024a340 CKGaugeCpnt_UpdateDisplayedValue_maybe
void CKGaugeCpnt::UpdateDisplayedValue(float dt, GaugeSample* sample, CKGaugeCpntUpdater* record) const {
    const float target = record->m_unk10;
    float displayed = record->m_unk08;
    if (displayed < target) {
        if (m_unk34 > record->m_unk14) {
            record->m_unk14 = dt + record->m_unk14;  // the rise delay
        } else if (m_unk38 == 0) {
            displayed = target;
            record->m_unk08 = target;
        } else if (m_unk38 == 1) {
            displayed = ppc::fmadds(dt, m_unk3c, displayed);
            record->m_unk08 = displayed;
            if (displayed > target) {
                displayed = target;
                record->m_unk08 = target;
            }
        }
    } else if (displayed > target) {
        if (m_unk4c > record->m_unk14) {
            record->m_unk14 = dt + record->m_unk14;  // the fall delay
        } else if (m_unk50 == 0) {
            displayed = target;
            record->m_unk08 = target;
        } else if (m_unk50 == 1) {
            displayed = displayed - dt * m_unk54;
            record->m_unk08 = displayed;
            if (!(displayed >= target)) {
                displayed = target;
                record->m_unk08 = target;
            }
        }
    }
    const float maximum = m_unk04;
    const float duration = m_pTransformation->m_unk04;
    if (m_unk20 != 0 && record->m_unk18 != 0 && m_unk24 > 0.0f) {
        float time = record->m_fFlashTime + dt;
        record->m_fFlashTime = time;
        if (m_unk21 == 0) {
            record->m_fFlashTime = time > m_unk24 ? m_unk24 : time;
        } else if (time > m_unk24) {
            do {
                time = time - m_unk24;
                record->m_fFlashTime = time;
            } while (m_unk24 < time);
        }
    }
    EvaluateSample(displayed / maximum * duration, sample, record);
}
