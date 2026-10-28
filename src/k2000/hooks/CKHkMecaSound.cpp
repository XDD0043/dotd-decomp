// CKHkMecaSound.cpp - reconstructed original translation unit 0x4dfc68-0x4e0920 (GAME_TOC1, main_toc1), 31 functions, 31 live.
// Primary class: CKHkMecaSound  key 0x3482  category Hook  size 0x3c  vtable 0xb2a360
// Other owners: CKHkS08ElectricGaugeBase (2), CKHkS08ElectricGauge (2), KBase3542 (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [ ] 0x4dfc68  CKHkMecaSound_vfCC
//   [ ] 0x4dfc70  RegisterCKHkMecaSoundClass
//   [ ] 0x4dfce8  _GLOBAL__I_4dfce8
//   [ ] 0x4dfcf8  CKHkMecaSound_MessageProc
//   [ ] 0x4dfd50  CKHkMecaSound_GetInfo
//   [ ] 0x4dfda0  CKHkMecaSound_OnDeactivate
//   [ ] 0x4dfe40  CKHkMecaSound_OnActivate
//   [ ] 0x4dfe68  CKHkMecaSound_Resume
//   [ ] 0x4dfe90  CKHkMecaSound_Pause
//   [x] 0x4dfeb8  CKHkMecaSound_SetDefaultState
//   [ ] 0x4dfef0  CKHkMecaSound_Stop
//   [x] 0x4dff18  CKHkMecaSound_Start
//   [ ] 0x4dff40  CKHkMecaSound_PostLoad
//   [ ] 0x4dff68  CKHkMecaSound_Save
//   [ ] 0x4dff90  CKHkMecaSound_RecursiveRegistration
//   [ ] 0x4dffb8  CKHkMecaSound_Destroy
//   [ ] 0x4dffe0  CKHkMecaSound_DeletingDestructor
//   [ ] 0x4e0028  CKHkMecaSound_Destructor
//   [ ] 0x4e0058  CKHkMecaSound_BaseDestructor
//   [ ] 0x4e0088  CKHkMecaSound_Construct_2
//   [x] 0x4e00c0  CKHkMecaSound_Construct
//   [x] 0x4e00f8  CKHkMecaSound_DeleteArray
//   [x] 0x4e01a0  CKHkMecaSound_CreateArray
//   [x] 0x4e0258  CKHkMecaSound_Create
//   [ ] 0x4e02b0  CKHkMecaSound_Update
//   [x] 0x4e0600  CKHkMecaSound_Load
//   [ ] 0x4e0858  CKHkS08ElectricGaugeBase_3542_maybe_Update
//   [ ] 0x4e0880  CKHkS08ElectricGauge_BaseResume_maybe
//   [ ] 0x4e08a8  CKHkS08ElectricGauge_BasePause_maybe
//   [ ] 0x4e08d0  CKHkS08ElectricGaugeBase_3542_maybe_OnLevelExit
//   [x] 0x4e08f8  KBase3542_ResetRuntime
//
//   [ ] 0x9c62c0  CKHkMecaSound_IsKindOfClass  [inline]
//   [ ] 0x9c6318  CKHkMecaSound_GetClassType  [inline]
//   [ ] 0x9c6320  CKHkMecaSound_GetClassID  [inline]
#include "k2000/hooks/CKHkMecaSound.h"

#include "k2000/io/IKFile.h"

// 0x004e0600 CKHkMecaSound_Load
int32_t CKHkMecaSound::Load(IKFile* file, int32_t type) {
    CKHkActorBase::Load(file, type);
    if (type == K_LEVEL_PLATEFORMS) {
        IKFile_ReadRef(file, &m_unk20);
        IKFile_ReadRef(file, &m_unk24);
        ReadF32LE(file, &m_unk28);
        ReadU8(file, &m_unk2C);
        ReadF32LE(file, &m_unk30);
        ReadF32LE(file, &m_unk34);
        return 1;
    }
    return 1;
}

// 0x004dfeb8 CKHkMecaSound_SetDefaultState
void CKHkMecaSound::SetDefaultState(int32_t flag) {
    CKHkActorBase::SetDefaultState(flag);
    m_unk38 = 1;
}

// 0x004dff18 CKHkMecaSound_Start: CKHkActorBase_d82_maybe_ResetRuntime only. 0x004e08f8 KBase3542_ResetRuntime
// is the same call for the unregistered base KBase3542 (no class of its own here).
void CKHkMecaSound::Start() { CKHkActorBase::Start(); }
