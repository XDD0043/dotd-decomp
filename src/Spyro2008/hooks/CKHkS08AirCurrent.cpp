// CKHkS08AirCurrent.cpp - reconstructed original translation unit 0x4740f0-0x478940 (GAME_TOC1, main_toc1), 36 functions, 34 live.
// Primary class: CKHkS08AirCurrent  key 0x2b02  category Hook  size 0x130  vtable 0xb27918
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x4740f0  CKHkS08AirCurrent_Delete
//   [ ] 0x474140  CKHkS08AirCurrent_Restart
//   [ ] 0x474160  CKHkS08AirCurrent_MessageProc
//   [ ] 0x4741b8  CKHkS08AirCurrent_GetInfo
//   [ ] 0x474208  CKHkS08AirCurrent_UpdateAlphaFlicker_maybe
//   [ ] 0x474310  CKHkS08AirCurrent_SetFxIntensity_maybe
//   [ ] 0x474470  CKHkS08AirCurrent_UpdateFlowFx_maybe
//   [ ] 0x4748c0  CKHkS08AirCurrent_OnDeactivate
//   [ ] 0x474928  CKHkS08AirCurrent_Resume
//   [ ] 0x474950  CKHkS08AirCurrent_Pause
//   [ ] 0x474978  CKHkS08AirCurrent_Stop
//   [x] 0x4749a0  CKHkS08AirCurrent_Start
//   [ ] 0x4749c8  CKHkS08AirCurrent_PostLoad
//   [ ] 0x474a20  CKHkS08AirCurrent_Save
//   [ ] 0x474a48  CKHkS08AirCurrent_RecursiveRegistration
//   [ ] 0x474a70  CKHkS08AirCurrent_Destroy
//   [x] 0x474ad0  CKHkS08AirCurrent_DeleteArray
//   [x] 0x474b70  CKHkS08AirCurrent_Construct  [dead]
//   [ ] 0x474ba8  CKHkS08AirCurrent_DeletingDestructor
//   [ ] 0x474bf0  CKHkS08AirCurrent_Destructor
//   [ ] 0x474c20  CKHkS08AirCurrent_BaseDestructor
//   [ ] 0x474c50  RegisterCKHkS08AirCurrentClass
//   [ ] 0x474cd8  _GLOBAL__D_474cd8
//   [ ] 0x474ce8  _GLOBAL__I_474ce8
//   [ ] 0x474cf8  CKHkS08AirCurrent_Construct_2  [dead]
//   [ ] 0x474d30  CKHkS08AirCurrent_vfC8
//   [x] 0x474d90  CKHkS08AirCurrent_SetDefaultState
//   [x] 0x474e58  CKHkS08AirCurrent_Create
//   [x] 0x474eb0  CKHkS08AirCurrent_CreateArray
//   [ ] 0x474f60  CKHkS08AirCurrent_RemoveRecords_maybe
//   [ ] 0x475278  CKHkS08AirCurrent_ClampPositionToTube_maybe
//   [ ] 0x4754a0  CKHkS08AirCurrent_AddRecords_maybe
//   [ ] 0x476400  CKHkS08AirCurrent_vfCC
//   [ ] 0x476438  CKHkS08AirCurrent_OnActivate
//   [ ] 0x4765c0  CKHkS08AirCurrent_Update
//   [x] 0x4779e0  CKHkS08AirCurrent_Load
//
//   [ ] 0x9c46c8  CKHkS08AirCurrent_IsKindOfClass  [inline]
//   [ ] 0x9c4720  CKHkS08AirCurrent_GetClassType  [inline]
//   [ ] 0x9c4728  CKHkS08AirCurrent_GetClassID  [inline]
#include "Spyro2008/hooks/CKHkS08AirCurrent.h"

#include "k2000/io/IKFile.h"
#include "k2000/memory/Mem.h"

// 0x004779e0 CKHkS08AirCurrent_Load
int32_t CKHkS08AirCurrent::Load(IKFile* file, int32_t type) {
    CKHkActorBase::Load(file, type);
    if (type != K_LEVEL_PLATEFORMS) return 1;
    IKFile_ReadRef(file, &m_pUnk94);
    IKFile_ReadRef(file, &m_pUnk98);
    for (float& f : m_afUnk9C) ReadF32LE(file, &f);
    ReadF32LE(file, &m_fUnkA8);
    ReadF32LE(file, &m_fUnkAC);
    ReadU32LE(file, &m_unkB4);
    ReadU32LE(file, &m_unkB0);
    ReadU32LE(file, &m_unkB8);
    ReadF32LE(file, &m_fUnkBC);
    ReadF32LE(file, &m_fUnk5C);
    ReadF32LE(file, &m_fUnk60);
    for (float& f : m_afUnk68) ReadF32LE(file, &f);
    ReadF32LE(file, &m_fUnkC8);
    ReadF32LE(file, &m_fUnkCC);
    ReadU16LE(file, &m_ui16NbUnk24);
    if (m_ui16NbUnk24 == 0) {
        m_aUnk28 = nullptr;
        m_apUnk24 = nullptr;
    } else {
        m_apUnk24 = static_cast<IKSerializable**>(
            Mem_AllocAligned16(m_ui16NbUnk24 * static_cast<uint32_t>(sizeof(IKSerializable*))));
        IKFile_ReadObjectRefArray(file, m_apUnk24, m_ui16NbUnk24);
        m_aUnk28 = new uint8_t[m_ui16NbUnk24];  // OperatorNewArray
        ReadRaw(file, m_aUnk28, m_ui16NbUnk24);
    }
    IKFile_ReadRef(file, &m_pUnk2C);
    IKFile_ReadRef(file, &m_pUnk30);
    IKFile_ReadRef(file, &m_pUnk34);
    ReadU16LE(file, &m_unk38);
    IKFile_ReadRef(file, &m_pUnk3C);
    ReadU16LE(file, &m_unk40);
    IKFile_ReadRef(file, &m_pUnk44);
    ReadU32LE(file, &m_unk4C);
    ReadF32LE(file, &m_fUnk50);
    ReadF32LE(file, &m_fUnk54);
    ReadF32LE(file, &m_fUnk58);
    IKFile_ReadRef(file, &m_pUnkD0);
    ReadU32LE(file, &m_unkD4);
    IKFile_ReadRef(file, &m_pUnkD8);
    ReadF32LE(file, &m_fUnkC0);
    ReadF32LE(file, &m_fUnkC4);
    ReadF32LE(file, &m_fUnk64);
    IKFile_ReadRef(file, &m_pUnkDC);
    ReadU8(file, &m_ui8NbUnkE4);
    m_apUnkE4 = static_cast<IKSerializable**>(
        Mem_AllocAligned16(m_ui8NbUnkE4 * static_cast<uint32_t>(sizeof(IKSerializable*))));
    IKFile_ReadObjectRefArray(file, m_apUnkE4, m_ui8NbUnkE4);
    IKFile_ReadRef(file, &m_pUnk48);
    return 1;
}

// 0x004749a0 CKHkS08AirCurrent_Start: the actor base's (empty) ResetRuntime 0x3f6e48.
void CKHkS08AirCurrent::Start() {}

// 0x00474d90 CKHkS08AirCurrent_SetDefaultState (after the empty base call KStub_Nop_3f72a0): bit 11 of the
// flags takes bit 3, always for flag 0, otherwise only when bit 5 is set.
void CKHkS08AirCurrent::SetDefaultState(int32_t flag) {
    if (flag != 0 && (m_bitArray & 0x20u) == 0) return;
    m_bitArray = (m_bitArray & 0xfffff7ffu) | (((m_bitArray >> 3) & 1u) << 11);
}
