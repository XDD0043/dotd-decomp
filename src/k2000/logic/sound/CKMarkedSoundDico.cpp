// CKMarkedSoundDico.cpp - reconstructed original translation unit 0x5cdee0-0x5ceb68 (GAME_TOC2, main_toc2), 22 functions, 19 live.
// Primary class: CKMarkedSoundDico  key 0xab0c  category Logic  size ?  vtable 0xb30180
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x5cdee0  CKMarkedSoundDico_Delete
//   [ ] 0x5cdf30  CKMarkedSoundDico_Construct  [dead]
//   [ ] 0x5cdf50  CKMarkedSoundDico_SetAnimatedNode_maybe  [dead]
//   [ ] 0x5cdf58  CKMarkedSoundDico_SetTimeline_maybe
//   [ ] 0x5cdf60  CKMarkedSoundDico_SetSourceMode_maybe
//   [ ] 0x5cdf68  CKMarkedSoundDico_SetPositionCallback_maybe
//   [ ] 0x5cdf80  CKMarkedSoundDico_Construct_2  [dead]
//   [ ] 0x5cdfa0  CKMarkedSoundDico_PlaySoundsForMark_maybe
//   [x] 0x5ce118  CKMarkedSoundDico_DeleteArray
//   [ ] 0x5ce1c0  RegisterCKMarkedSoundDicoClass
//   [ ] 0x5ce248  _GLOBAL__D_5ce248
//   [ ] 0x5ce258  _GLOBAL__I_5ce258
//   [ ] 0x5ce268  CKMarkedSoundDico_UpdateFromAnimMarks_maybe
//   [x] 0x5ce4f0  CKMarkedSoundDico_CreateArray
//   [x] 0x5ce5a8  CKMarkedSoundDico_Create
//   [ ] 0x5ce5f8  CKMarkedSoundDico_Save
//   [ ] 0x5ce600  CKMarkedSoundDico_RecursiveRegistration
//   [ ] 0x5ce608  CKMarkedSoundDico_Destroy
//   [x] 0x5ce678  CKMarkedSoundDico_Load
//   [ ] 0x5cea18  CKMarkedSoundDico_DeletingDestructor
//   [ ] 0x5cea98  CKMarkedSoundDico_Destructor
//   [ ] 0x5ceb00  CKMarkedSoundDico_Destructor_2
//
//   [ ] 0x9cd680  CKMarkedSoundDico_GetClassType  [inline]
//   [ ] 0x9cd688  CKMarkedSoundDico_GetClassID  [inline]
//   [ ] 0x9cd690  CKMarkedSoundDico_IsKindOfClass  [inline]
#include "k2000/logic/sound/CKMarkedSoundDico.h"

#include "k2000/io/IKFile.h"
#include "k2000/memory/Mem.h"

// 0x005ce5a8 CKMarkedSoundDico_Create (the constructor inlined)
CKMarkedSoundDico::CKMarkedSoundDico() {
    m_apIds = nullptr;
    m_idsCapacity = 1;
    m_idsCount = 0;
}

// 0x005ce678 CKMarkedSoundDico_Load
int32_t CKMarkedSoundDico::Load(IKFile* file, int32_t type) {
    if (type != K_LEVEL_PLATEFORMS) return 1;
    IKFile_ReadRef(file, &m_unk08);
    IKFile_ReadRef(file, &m_unk1c);
    IKFile_ReadRef(file, &m_unk20);
    ReadU8(file, &m_unk18);
    IKFile_ReadRef(file, &m_unk04);
    ReadU32LE(file, &m_idCount);
    // The vector is re-created (capacity 1); its count is not reset (BUG(original) if loaded twice).
    m_idsCapacity = 1;
    m_apIds = static_cast<uint32_t**>(Mem_AllocAligned16(static_cast<uint32_t>(sizeof(uint32_t*))));
    for (uint32_t i = 0; i < m_idCount; ++i) {
        uint32_t* id = static_cast<uint32_t*>(::operator new(4));  // OperatorNew(4)
        ReadU32LE(file, id);
        if (m_idsCapacity == m_idsCount) {  // push_back: grow by one
            uint32_t grown = m_idsCount + 1;
            m_apIds = static_cast<uint32_t**>(Mem_ReallocAligned16(m_apIds, grown * static_cast<uint32_t>(sizeof(uint32_t*))));
            m_idsCapacity = grown;
        }
        m_apIds[m_idsCount] = id;
        ++m_idsCount;
    }
    return 1;
}
