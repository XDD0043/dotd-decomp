// CKGaugeCpnt.cpp - reconstructed original translation unit 0x24a0d0-0x24b248 (GAME_TOC1, main_toc1), 16 functions, 15 live.
// Primary class: CKGaugeCpnt  key 0xa84c  category Logic  size 0x64  vtable 0xb20d40
// Other owners: SuperGaugeRecord (2), CKGaugeCpntUpdater (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x24a0d0  CKGaugeCpnt_Delete
//   [ ] 0x24a120  RegisterCKGaugeCpntType
//   [ ] 0x24a198  _GLOBAL__I_24a198
//   [ ] 0x24a1a8  CKGaugeCpnt_EvaluateSample_maybe
//   [ ] 0x24a340  CKGaugeCpnt_UpdateDisplayedValue_maybe
//   [x] 0x24a4b0  CKGaugeCpnt_DeleteArray
//   [ ] 0x24a550  CKGaugeCpnt_PostLoad
//   [ ] 0x24a558  CKGaugeCpnt_RecursiveRegistration
//   [ ] 0x24a560  CKGaugeCpnt_Destroy
//   [x] 0x24a568  CKGaugeCpnt_Create
//   [x] 0x24a618  CKGaugeCpnt_CreateArray
//   [ ] 0x24a740  CKGaugeCpnt_Save
//   [x] 0x24ac88  CKGaugeCpnt_Load
//   [ ] 0x24b1c8  CKGaugeCpntUpdater_Delete
//   [ ] 0x24b218  SuperGaugeRecord_Reset_maybe
//   [ ] 0x24b240  SuperGaugeRecord_GetCpnt_maybe  [dead]
//
//   [ ] 0x9b9dd8  CKGaugeCpnt_IsKindOfClass  [inline]
//   [x] 0x9b9e08  CKGaugeCpnt_GetClassType  [inline]
//   [x] 0x9b9e10  CKGaugeCpnt_GetClassID  [inline]
//   [ ] 0x9b9e18  CKGaugeCpnt_Destructor  [inline]
//   [ ] 0x9b9e90  CKGaugeCpnt_DeletingDestructor  [inline]
#include "k2000/logic/ui/CKGaugeCpnt.h"

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
    ReadU32LE(file, &m_unk34);
    ReadF32LE(file, &m_unk4c);
    ReadU8(file, &m_unk20);
    ReadU8(file, &m_unk21);
    ReadF32LE(file, &m_unk24);
    CurveKeys_Load(&m_unk28, file);
    return 1;
}
