// CKMoveCpnt.cpp - reconstructed original translation unit 0x24c378-0x24d2a8 (GAME_TOC1, main_toc1), 20 functions, 19 live.
// Primary class: CKMoveCpnt  key 0x968c  category Logic  size 0x34  vtable 0xb20e48
// Other owners: CKMoveCpntUpdater (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x24c378  CKMoveCpnt_Delete
//   [ ] 0x24c3c8  CKMoveCpnt_ResetUpdater
//   [ ] 0x24c3e0  CKMoveCpnt_PauseUpdater
//   [ ] 0x24c3f0  CKMoveCpnt_ResumeUpdater
//   [ ] 0x24c400  CKMoveCpnt_ResetTrackTimeToStart_maybe
//   [ ] 0x24c4a0  RegisterCKMoveCpntClass
//   [ ] 0x24c518  _GLOBAL__I_24c518
//   [ ] 0x24c528  CKMoveCpnt_Sample
//   [ ] 0x24c988  CKMoveCpnt_Advance
//   [x] 0x24c9e8  CKMoveCpnt_DeleteArray
//   [x] 0x24ca88  CKMoveCpnt_CreateArray
//   [x] 0x24cb48  CKMoveCpnt_Create
//   [ ] 0x24cb98  CKMoveCpnt_Save
//   [ ] 0x24cba0  CKMoveCpnt_RecursiveRegistration
//   [ ] 0x24cba8  CKMoveCpnt_PostLoad
//   [ ] 0x24cbb0  CKMoveCpnt_Destroy
//   [ ] 0x24cbf8  CKMoveCpnt_StartUpdater
//   [x] 0x24ccb8  CKMoveCpnt_Load
//   [ ] 0x24d250  CKMoveCpntUpdater_Delete
//   [ ] 0x24d2a0  KStub_Nop_24d2a0  [dead]
//
//   [ ] 0x9ba000  CKMoveCpnt_IsKindOfClass  [inline]
//   [x] 0x9ba030  CKMoveCpnt_GetClassType  [inline]
//   [x] 0x9ba038  CKMoveCpnt_GetClassID  [inline]
//   [ ] 0x9ba040  CKMoveCpnt_Destructor  [inline]
//   [ ] 0x9ba098  CKMoveCpnt_DeletingDestructor  [inline]
#include "k2000/logic/CKMoveCpnt.h"

#include "Renderware/rwcore/RwMatrix.h"
#include "k2000/io/IKFile.h"
#include "k2000/memory/Mem.h"

// 0x0024ccb8 CKMoveCpnt_Load
int32_t CKMoveCpnt::Load(IKFile* file, int32_t type) {
    if (type != K_LEVEL_PLATEFORMS) return 1;
    ReadF32LE(file, &m_unk04);
    ReadU8(file, &m_unk08);
    ReadU8(file, &m_unk09);
    IKFile_ReadRef(file, &m_pUnk0c);
    IKFile_ReadRef(file, &m_pUnk10);
    ReadU8(file, &m_unk14);
    ReadU8(file, &m_unk15);
    ReadU8(file, &m_unk16);
    uint8_t hasMatrix = 0;
    ReadU8(file, &hasMatrix);
    if (hasMatrix == 0) {
        m_pMatrix = nullptr;
    } else {
        // RwMatrixCreate_Thunk 0x0023fa68 (an RwMatrix: the CMatrix34 layout)
        m_pMatrix = reinterpret_cast<CMatrix34*>(RwMatrixCreate());
        CMatrix34_LoadMatrix(m_pMatrix, file);
    }
    for (float& v : m_unk1c) ReadF32LE(file, &v);  // one 0xc-byte read, then three swaps
    uint32_t count = 0;
    ReadU32LE(file, &count);
    // The capacity is set to the count before the block is allocated (the old block is not freed); the
    // reserve that follows never grows it.
    m_vTracks.m_ui32NbElt = count;
    m_vTracks.m_pBlock = static_cast<Track*>(Mem_AllocAligned16(count * static_cast<uint32_t>(sizeof(Track))));
    if (m_vTracks.m_ui32NbElt < count) {
        uint32_t capacity = count + 1;
        if (capacity == 0) capacity = 1;
        m_vTracks.m_pBlock = static_cast<Track*>(
            Mem_ReallocAligned16(m_vTracks.m_pBlock, capacity * static_cast<uint32_t>(sizeof(Track))));
        m_vTracks.m_ui32NbElt = capacity;
    }
    m_vTracks.m_ui32NbUsedElt = count;
    for (uint32_t i = 0; i < count; ++i) {
        Track& track = m_vTracks.m_pBlock[i];
        IKFile_ReadRef(file, &track.m_pCurve);
        ReadU32LE(file, &track.m_unk04);
        ReadF32LE(file, &track.m_unk08);
        ReadF32LE(file, &track.m_unk0c);
        ReadF32LE(file, &track.m_unk10);
        ReadU32LE(file, &track.m_unk14);
    }
    return 1;
}
