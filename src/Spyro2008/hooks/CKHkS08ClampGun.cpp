// CKHkS08ClampGun.cpp - reconstructed original translation unit 0x486570-0x48c7a0 (GAME_TOC1, main_toc1), 58 functions, 45 live.
// Primary class: CKHkS08ClampGun  key 0x2c42  category Hook  size 0x158  vtable 0xb27df0
// Other owners: Vec3 (2), HeroGroup (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x486570  CKHkS08ClampGun_Delete
//   [ ] 0x4865c0  CKHkS08ClampGun_vfC8
//   [ ] 0x4865f8  CKHkS08ClampGun_CountAttachedClamps_maybe  [dead]
//   [ ] 0x486650  CKHkS08ClampGun_AnyEntryFlagged_maybe  [dead]
//   [ ] 0x4866c8  CKHkS08ClampGun_GetTriggerProp96
//   [ ] 0x4866f0  CKHkS08ClampGun_vfCC
//   [ ] 0x4866f8  CKHkS08ClampGun_ReleaseFlaggedClampsWithFx_maybe  [dead]
//   [ ] 0x4867f8  CKHkS08ClampGun_ReleaseClampAt_maybe  [dead]
//   [ ] 0x486868  HeroGroup_IsExternallyLockedOrMissing_maybe  [dead]
//   [ ] 0x4868b8  CKHkS08ClampGun_GetRandomSpreadAngle_maybe  [dead]
//   [ ] 0x486920  CKHkS08ClampGun_AreAllHeroesWithinRadius_maybe
//   [ ] 0x486a48  CKHkS08ClampGun_AreAllHeroesBeyondRadius_maybe
//   [ ] 0x486b70  CKHkS08ClampGun_InitCollisionVolume_maybe  [dead]
//   [ ] 0x486c30  Vec3_YawDifferenceWrappedFromZ_maybe  [dead]
//   [ ] 0x486cc0  CKHkS08ClampGun_UpdateTurnSound_maybe
//   [ ] 0x486e60  CKHkS08ClampGun_TickTimerAndPlayImpactFx_maybe
//   [ ] 0x4871b0  CKHkS08ClampGun_ProcessContacts_maybe
//   [ ] 0x4873f0  CKHkS08ClampGun_SetDefaultState
//   [ ] 0x487430  CKHkS08ClampGun_Resume
//   [ ] 0x487458  CKHkS08ClampGun_Pause
//   [ ] 0x487480  CKHkS08ClampGun_Start
//   [ ] 0x4874d8  CKHkS08ClampGun_GetInfo
//   [ ] 0x4875b8  CKHkS08ClampGun_Save
//   [ ] 0x4875e0  CKHkS08ClampGun_RecursiveRegistration
//   [x] 0x487608  CKHkS08ClampGun_Construct  [dead]
//   [x] 0x487688  CKHkS08ClampGun_DeleteArray
//   [ ] 0x487728  RegisterCKHkS08ClampGunClass
//   [ ] 0x4877b0  _GLOBAL__D_4877b0
//   [ ] 0x4877c0  _GLOBAL__I_4877c0
//   [ ] 0x4877d0  CKHkS08ClampGun_vfD0
//   [ ] 0x487818  CKHkS08ClampGun_Destroy
//   [ ] 0x487898  CKHkS08ClampGun_SM140_State1_Cooldown_maybe
//   [ ] 0x4878f8  CKHkS08ClampGun_OnDeactivate
//   [ ] 0x487a00  CKHkS08ClampGun_DeletingDestructor
//   [ ] 0x487ac0  CKHkS08ClampGun_OnActivate
//   [ ] 0x487cb8  CKHkS08ClampGun_Construct_2  [dead]
//   [ ] 0x487d38  CKHkS08ClampGun_SetupSound0_maybe  [dead]
//   [ ] 0x487df8  CKHkS08ClampGun_Destructor
//   [ ] 0x487ea8  CKHkS08ClampGun_BaseDestructor
//   [ ] 0x487f58  CKHkS08ClampGun_ReleaseUnflaggedClamps_maybe  [dead]
//   [ ] 0x488018  CKHkS08ClampGun_ReleaseAllClamps_maybe  [dead]
//   [ ] 0x4880d0  CKHkS08ClampGun_Stop
//   [x] 0x488190  CKHkS08ClampGun_CreateArray
//   [x] 0x4882a0  CKHkS08ClampGun_Create
//   [ ] 0x488330  CKHkS08ClampGun_ComputeBallisticSpeed_maybe
//   [ ] 0x488490  CKHkS08ClampGun_PostLoad
//   [ ] 0x488558  CKHkS08ClampGun_MessageProc
//   [ ] 0x488738  CKHkS08ClampGun_AimAtHeroesMidpoint_maybe
//   [ ] 0x488b10  CKHkS08ClampGun_RotateTowardPresetYaw_maybe
//   [ ] 0x488f98  CKHkS08ClampGun_RotateTowardTarget_maybe
//   [ ] 0x4893c0  Vec3_RotateYawFlatNormalized_2_maybe
//   [x] 0x489690  CKHkS08ClampGun_Load
//   [ ] 0x48a1c0  CKHkS08ClampGun_Restart
//   [ ] 0x48a560  CKHkS08ClampGun_Update
//   [ ] 0x48ab98  CKHkS08ClampGun_FireShot_maybe
//   [ ] 0x48b4f8  CKHkS08ClampGun_FireSalvoState_maybe
//   [ ] 0x48b680  CKHkS08ClampGun_SM128_State0
//   [ ] 0x48bc30  CKHkS08ClampGun_SM128_State1
//
//   [ ] 0x9c48d0  CKHkS08ClampGun_IsKindOfClass  [inline]
//   [ ] 0x9c4928  CKHkS08ClampGun_GetClassType  [inline]
//   [ ] 0x9c4930  CKHkS08ClampGun_GetClassID  [inline]
//   [ ] 0x9c4938  KStub_ReturnArg4_9c4938  [inline]
#include "Spyro2008/hooks/CKHkS08ClampGun.h"

#include "k2000/io/IKFile.h"
#include "k2000/memory/Mem.h"

// 0x00489690 CKHkS08ClampGun_Load: the actor base, then the level data (type 0 only). The trigger
// starter is loaded with type 0.
int32_t CKHkS08ClampGun::Load(IKFile* file, int32_t type) {
    CKHkActorBase::Load(file, type);
    if (type == K_LEVEL_PLATEFORMS) {
        ReadF32LE(file, &m_fUnk44);
        ReadF32LE(file, &m_fUnk40);
        ReadF32LE(file, &m_fUnk48);
        ReadF32LE(file, &m_fUnk4C);
        ReadF32LE(file, &m_fUnk54);
        ReadF32LE(file, &m_fUnk58);
        ReadF32LE(file, &m_fUnk60);
        IKFile_ReadRef(file, &m_pUnk28);
        ReadU8(file, &m_unk5D);
        uint32_t count = 0;
        ReadU32LE(file, &count);
        // BUG(original): a new block of capacity 1 replaces the old one (leaked); the length is not reset.
        m_vUnkB4.m_ui32NbElt = 1;
        m_vUnkB4.m_pBlock = static_cast<SElem**>(Mem_AllocAligned16(static_cast<uint32_t>(sizeof(SElem*))));
        for (uint32_t i = 0; i < count; ++i) {
            SElem* elem = new SElem;  // OperatorNew(0xc)
            elem->m_fUnk0 = 0.0f;
            elem->m_unk4 = 0;
            elem->m_unk8 = 0;
            elem->m_pad9[0] = elem->m_pad9[1] = elem->m_pad9[2] = 0;
            ReadF32LE(file, &elem->m_fUnk0);
            elem->m_unk4 = 0;
            elem->m_unk8 = 0;
            const uint32_t used = m_vUnkB4.m_ui32NbUsedElt;
            if (m_vUnkB4.m_ui32NbElt == used) {
                uint32_t capacity = used + 1;
                uint32_t bytes = capacity * static_cast<uint32_t>(sizeof(SElem*));
                if (capacity == 0) {
                    capacity = 1;
                    bytes = static_cast<uint32_t>(sizeof(SElem*));
                }
                m_vUnkB4.m_pBlock = static_cast<SElem**>(Mem_ReallocAligned16(m_vUnkB4.m_pBlock, bytes & ~3u));
                m_vUnkB4.m_ui32NbElt = capacity;
            }
            m_vUnkB4.m_pBlock[m_vUnkB4.m_ui32NbUsedElt] = elem;
            m_vUnkB4.m_ui32NbUsedElt = m_vUnkB4.m_ui32NbUsedElt + 1;
        }
        IKFile_ReadRef(file, &m_pUnkD8);
        IKFile_ReadRef(file, &m_pUnk38);
        m_unkDC.Load(file, K_LEVEL_PLATEFORMS);
        IKFile_ReadRef(file, &m_pUnk24);
        IKFile_ReadRef(file, &m_pUnkEC);
        IKFile_ReadRef(file, &m_pUnkF4);
        IKFile_ReadRef(file, &m_pUnk20);
        IKFile_ReadRef(file, &m_pUnkD4);
        ReadF32LE(file, &m_fUnk98);
        ReadF32LE(file, &m_fUnk9C);
        ReadF32LE(file, &m_fUnkA0);
        ReadF32LE(file, &m_fUnk84);
        IKFile_ReadRef(file, &m_pUnkFC);
        ReadF32LE(file, &m_fUnk8C);
        IKFile_ReadRef(file, &m_pUnk104);
        ReadF32LE(file, &m_fUnk10C);
        ReadU32LE(file, &m_unk110);
        ReadF32LE(file, &m_fUnk114);
        ReadF32LE(file, &m_fUnk90);
        ReadU8(file, &m_unk118);
        ReadU8(file, &m_unk119);
        ReadU8(file, &m_unk11A);
        ReadU8(file, &m_unk11C);
        ReadU8(file, &m_unk11D);
        ReadU8(file, &m_unk11E);
        IKFile_ReadRef(file, &m_pUnkE4);
    }
    return 1;
}
