// CKHkDoor.cpp - reconstructed original translation unit 0x416710-0x419a18 (GAME_TOC1, main_toc1), 31 functions, 25 live.
// Primary class: CKHkDoor  key 0x1942  category Hook  size 0x80  vtable 0xb25d10
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x416710  CKHkDoor_Delete
//   [ ] 0x416760  FUN_00416760  [dead]
//   [ ] 0x416858  CKHkDoor_ResetStateEntriesToNone_maybe  [dead]
//   [ ] 0x4168e0  CKHkDoor_SetStateTableEntry2Bit_maybe  [dead]
//   [ ] 0x416910  RegisterCKHkDoorClass
//   [ ] 0x416988  _GLOBAL__I_416988
//   [x] 0x416998  CKHkDoor_SetDefaultState
//   [ ] 0x4169f0  CKHkDoor_SetClosedCollisionState_maybe  [dead]
//   [ ] 0x416a70  CKHkDoor_SetOpenCollisionState_maybe  [dead]
//   [ ] 0x416af8  CKHkDoor_UpdateStateFromLinkedObjects_maybe
//   [ ] 0x4172e0  CKHkDoor_Resume
//   [ ] 0x417308  CKHkDoor_Pause
//   [ ] 0x417330  CKHkDoor_Stop
//   [x] 0x417358  CKHkDoor_Start
//   [ ] 0x417390  CKHkDoor_PostLoad
//   [ ] 0x417400  CKHkDoor_Save
//   [ ] 0x417428  CKHkDoor_RecursiveRegistration
//   [x] 0x417450  CKHkDoor_DeleteArray
//   [x] 0x4174f0  CKHkDoor_Create
//   [ ] 0x417548  CKHkDoor_AttachSounds
//   [ ] 0x4175f0  CKHkDoor_Destroy
//   [ ] 0x417638  CKHkDoor_GetInfo
//   [x] 0x417768  CKHkDoor_CreateArray
//   [ ] 0x417818  CKHkDoor_OnDeactivate
//   [x] 0x4179a8  CKHkDoor_ApplyStatePreset_maybe
//   [ ] 0x417b30  CKHkDoor_Update
//   [ ] 0x4186b8  CKHkDoor_SetOpenState_maybe  [dead]
//   [ ] 0x418810  CKHkDoor_MessageProc
//   [ ] 0x418c60  CKHkDoor_OnActivate
//   [x] 0x419150  CKHkDoor_Load
//   [ ] 0x419738  CKHkDoor_Restart
//
//   [ ] 0x9c2e10  CKHkDoor_IsKindOfClass  [inline]
//   [ ] 0x9c2e68  CKHkDoor_GetClassType  [inline]
//   [ ] 0x9c2e70  CKHkDoor_GetClassID  [inline]
//   [ ] 0x9c2e78  CKHkDoor_GetTriggerProp9D  [inline]
//   [ ] 0x9c2e98  CKHkDoor_Destructor  [inline]
//   [ ] 0x9c2ec8  CKHkDoor_GetTriggerProp9C  [inline]
//   [ ] 0x9c2ed8  CKHkDoor_DeletingDestructor  [inline]
#include "k2000/hooks/CKHkDoor.h"

#include "k2000/io/IKFile.h"
#include "k2000/memory/Mem.h"
#include "crt/ppc_ops.h"

// 0x00419150 CKHkDoor_Load: no branch on the serialization type (only the trigger starters get it).
int32_t CKHkDoor::Load(IKFile* file, int32_t type) {
    CKHkActorBase::Load(file, type);
    ReadF32LE(file, &m_unk44);
    ReadF32LE(file, &m_unk48);
    ReadF32LE(file, &m_unk4C);
    ReadU16LE(file, &m_baAutoAction);
    ReadU8(file, &m_ui8NbOfDectector);
    if (m_ui8NbOfDectector == 0) {
        m_apBackDetector = nullptr;
        m_apFrontDetector = nullptr;
    } else {
        const uint32_t bytes = static_cast<uint32_t>(m_ui8NbOfDectector * sizeof(IKSerializable*));
        m_apFrontDetector = static_cast<IKSerializable**>(Mem_AllocAligned16(bytes));
        m_apBackDetector = static_cast<IKSerializable**>(Mem_AllocAligned16(bytes));
        IKFile_ReadObjectRefArray(file, m_apFrontDetector, m_ui8NbOfDectector);
        IKFile_ReadObjectRefArray(file, m_apBackDetector, m_ui8NbOfDectector);
    }
    IKFile_ReadRef(file, &m_unk68);
    IKFile_ReadRef(file, &m_unk54);
    IKFile_ReadRef(file, &m_unk50);
    IKFile_ReadRef(file, &m_unk58);
    IKFile_ReadRef(file, &m_unk5C);
    m_tsOpenStarter.Load(file, type);
    m_tsCloseStarter.Load(file, type);
    IKFile_ReadRef(file, &m_unk6C);
    return 1;
}

// 0x00416998 CKHkDoor_SetDefaultState: KStub_Nop_3f72a0, then the preset 0.
void CKHkDoor::SetDefaultState(int32_t flag) {
    CKHkActorBase::SetDefaultState(flag);
    ApplyStatePreset(0);
}

// 0x00417358 CKHkDoor_Start: CKHkActorBase_d82_maybe_ResetRuntime (empty), then the first runtime word 0.
void CKHkDoor::Start() {
    CKHkActorBase::Start();
    m_unk20[0] = 0;
}

// 0x004179a8 CKHkDoor_ApplyStatePreset_maybe. Bits 10/11 of the flags take the preset's two bits; when
// bit 11 (the preset's second bit) is set, bits 15 and 16 are set and bit 14 cleared, every detector's
// 3-bit state in the first runtime word becomes 6 (shifts through ppc::slw: the count of detectors can
// exceed what 32 bits hold) and bit 12 is set.
void CKHkDoor::ApplyStatePreset(int32_t state) {
    const uint32_t first = state == 0 ? 6u : 8u;
    uint32_t f = m_bitArray;
    f = (f & ~0xc00u) | (((f >> first) & 1) << 10) | (((f >> (first + 1)) & 1) << 11);
    m_bitArray = f;
    if (((f >> 11) & 1) == 0) return;
    f = (f & ~0x1c000u) | 0x18000u;
    m_bitArray = f;
    uint32_t states = m_unk20[0];
    for (uint32_t i = m_ui8NbOfDectector; i != 0; --i) {
        const uint32_t shift = (i - 1) * 3;
        states = states & ~ppc::slw(7, shift) | ppc::slw(6, shift);
    }
    if (m_ui8NbOfDectector != 0) m_unk20[0] = states;
    m_bitArray = (m_bitArray & 0xffffefffu) | 0x1000u;
}
