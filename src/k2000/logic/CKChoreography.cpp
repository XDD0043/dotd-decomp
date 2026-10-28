// CKChoreography.cpp - reconstructed original translation unit 0x264590-0x264e18 (GAME_TOC1, main_toc1), 14 functions, 14 live.
// Primary class: CKChoreography  key 0x6cc  category Logic  size 0x18  vtable 0xb213a8
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x264590  CKChoreography_Delete
//   [ ] 0x2645e0  CKChoreography_Destroy
//   [ ] 0x2645e8  CKChoreography_RecursiveRegistration
//   [ ] 0x264650  CKChoreography_Save
//   [ ] 0x264658  RegisterCKChoreographyClass
//   [ ] 0x2646d0  _GLOBAL__I_2646d0
//   [x] 0x2646e0  CKChoreography_DeleteArray
//   [x] 0x264788  CKChoreography_Create
//   [ ] 0x2647d8  CKChoreography_Reset_maybe
//   [ ] 0x264818  CKChoreography_Update_maybe
//   [ ] 0x2649e8  CKChoreography_GetCurrentKey_maybe
//   [ ] 0x264a20  CKChoreography_SwitchToKey_maybe
//   [x] 0x264b40  CKChoreography_CreateArray
//   [x] 0x264bf8  CKChoreography_Load
//
//   [x] 0x9bafc8  CKChoreography_GetClassType  [inline]
//   [x] 0x9bafd0  CKChoreography_GetClassID  [inline]
//   [ ] 0x9bafd8  CKChoreography_Destructor  [inline]
//   [ ] 0x9bb040  CKChoreography_IsKindOfClass  [inline]
//   [ ] 0x9bb060  CKChoreography_DeletingDestructor  [inline]
#include "k2000/logic/CKChoreography.h"

#include "Spyro2008/groups/CKChoreoKey.h"

#include "k2000/io/IKFile.h"
#include "k2000/memory/Mem.h"

// 0x00264bf8 CKChoreography_Load. Types 4..7 (the save restores) read nothing.
int32_t CKChoreography::Load(IKFile* file, int32_t type) {
    if (static_cast<uint32_t>(type) - 4u <= 3u) return 1;
    ReadF32LE(file, &m_fElapsedTime);
    ReadU8(file, &m_ui8CurrentKey);
    uint8_t count = 0;  // XXL2 m_ui8NbKey
    ReadU8(file, &count);
    // The block is replaced (the old one is not freed). Without keys the capacity is 1 and the count is
    // left alone; the reserve that follows never grows it.
    if (count == 0) {
        m_apChoreoKey.m_ui32NbElt = 1;
        m_apChoreoKey.m_pBlock = static_cast<CKChoreoKey**>(Mem_AllocAligned16(static_cast<uint32_t>(sizeof(CKChoreoKey*))));
    } else {
        m_apChoreoKey.m_ui32NbElt = count;
        m_apChoreoKey.m_pBlock = static_cast<CKChoreoKey**>(
            Mem_AllocAligned16(count * static_cast<uint32_t>(sizeof(CKChoreoKey*))));
        if (m_apChoreoKey.m_ui32NbElt < count) {
            uint32_t capacity = count + 1u;
            if (capacity == 0) capacity = 1;
            m_apChoreoKey.m_pBlock = static_cast<CKChoreoKey**>(Mem_ReallocAligned16(
                m_apChoreoKey.m_pBlock, capacity * static_cast<uint32_t>(sizeof(CKChoreoKey*))));
            m_apChoreoKey.m_ui32NbElt = capacity;
        }
        m_apChoreoKey.m_ui32NbUsedElt = count;
    }
    for (uint32_t i = 0; i < count; ++i) IKFile_ReadRef(file, &m_apChoreoKey.m_pBlock[i]);
    return 1;
}
