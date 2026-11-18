// CKS08HeroBlow.cpp - reconstructed original translation unit 0x36e2d0-0x36f578 (GAME_TOC1, main_toc1), 17 functions, 16 live.
// Primary class: CKS08HeroBlow  key 0x7a8c  category Logic  size 0x68  vtable 0xb230b0
// Other owners: CKS08HeroCombo (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x36e2d0  CKS08HeroBlow_GetAnimId
//   [x] 0x36e2e0  CKS08HeroBlow_GetDamageAmount
//   [x] 0x36e330  CKS08HeroBlow_GetReleaseDelay
//   [x] 0x36e350  CKS08HeroBlow_EvalTimeScale
//   [x] 0x36e3a0  CKS08HeroBlow_DeleteArray
//   [x] 0x36e440  CKS08HeroBlow_Create
//   [ ] 0x36e478  RegisterCKS08HeroBlowClass
//   [ ] 0x36e500  _GLOBAL__D_36e500
//   [ ] 0x36e510  _GLOBAL__I_36e510
//   [x] 0x36e520  CKS08HeroBlow_CreateArray
//   [x] 0x36e5b0  CKS08HeroBlow_RecursiveRegistration
//   [x] 0x36e650  CKS08HeroBlow_PostLoad
//   [x] 0x36e670  CKS08HeroBlow_Destroy
//   [x] 0x36e6b8  CKS08HeroBlow_Load
//   [ ] 0x36ee10  CKS08HeroBlow_Save
//   [x] 0x36f520  CKS08HeroCombo_Delete  (the registry Delete of CKS08HeroCombo: DOTD_DECLARE_FACTORIES, CKS08HeroCombo.h)
//   [ ] 0x36f570  KStub_Nop_36f570  [dead]
//
//   [ ] 0x9beb88  CKS08HeroBlow_GetClassType  [inline]
//   [ ] 0x9beb90  CKS08HeroBlow_GetClassID  [inline]
//   [ ] 0x9beb98  CKS08HeroBlow_GetOwnClassId  [inline]
//   [ ] 0x9beba0  CKS08HeroBlow_GetLinkCode  [inline]
//   [ ] 0x9beba8  CKS08HeroBlow_vf5C  [inline]
//   [ ] 0x9bebb0  CKS08HeroBlow_vf60  [inline]
//   [ ] 0x9bebb8  CKS08HeroBlow_GetHotspotIndex  [inline]
//   [ ] 0x9bebc0  CKS08HeroBlow_GetHitRadius  [inline]
//   [ ] 0x9bebc8  CKS08HeroBlow_vf6C  [inline]
//   [ ] 0x9bebd8  CKS08HeroBlow_vf70  [inline]
//   [ ] 0x9bebe0  CKS08HeroBlow_vf74  [inline]
//   [ ] 0x9bebe8  CKS08HeroBlow_vf78  [inline]
//   [ ] 0x9bebf0  CKS08HeroBlow_GetRecoveryDelay  [inline]
//   [ ] 0x9bebf8  CKS08HeroBlow_GetCameraData  [inline]
//   [ ] 0x9bec00  CKS08HeroBlow_vf84  [inline]
//   [ ] 0x9bec08  CKS08HeroBlow_vf88  [inline]
//   [ ] 0x9bec10  CKS08HeroBlow_GetAnimSpeed  [inline]
//   [ ] 0x9bec18  CKS08HeroBlow_vf94  [inline]
//   [ ] 0x9bec20  CKS08HeroBlow_vf98  [inline]
//   [ ] 0x9bec28  CKS08HeroBlow_IsGrabBlow  [inline]
//   [ ] 0x9bec30  CKS08HeroBlow_ShouldThrowOnTimeout_maybe  [inline]
//   [ ] 0x9bec58  CKS08HeroBlow_GetThrowDelay  [inline]
//   [ ] 0x9bec60  CKS08HeroBlow_vfAC  [inline]
//   [ ] 0x9bec68  CKS08HeroBlow_GetDamage  [inline]
//   [ ] 0x9bec70  CKS08HeroBlow_TickTimer  [inline]
//   [ ] 0x9bec80  CKS08HeroBlow_vfB8  [inline]
//   [ ] 0x9beca0  CKS08HeroBlow_ResetTimer  [inline]
//   [ ] 0x9becb0  CKS08HeroBlow_IsKindOfClass  [inline]
//   [ ] 0x9becd0  CKS08HeroBlow_Destructor  [inline]
//   [ ] 0x9bece8  CKS08HeroBlow_DeletingDestructor  [inline]
#include "Spyro2008/logic/CKS08HeroBlow.h"

#include "k2000/components/CKCurve2DCpnt.h"

#include "k2000/io/IKFile.h"

// 0x0036e6b8 CKS08HeroBlow_Load: level data only; the fields in the file's order.
int32_t CKS08HeroBlow::Load(IKFile* file, int32_t type) {
    if (type != K_LEVEL_PLATEFORMS) return 1;
    ReadU8(file, &m_unk04);
    ReadU8(file, &m_unk2d);
    ReadS32LE(file, &m_unk30);
    ReadU8(file, &m_unk34);
    ReadF32LE(file, &m_unk08);
    ReadF32LE(file, &m_unk20);
    ReadF32LE(file, &m_unk24);
    ReadF32LE(file, &m_unk28);
    ReadF32LE(file, &m_unk0c);
    ReadF32LE(file, &m_unk1c);
    ReadF32LE(file, &m_unk10);
    ReadU8(file, &m_unk14);
    ReadU8(file, &m_unk52);
    ReadF32LE(file, &m_unk54);
    ReadU8(file, &m_unk58);
    ReadF32LE(file, &m_unk5c);
    ReadU8(file, &m_unk48);
    if (m_unk48 != 0) {
        IKFile_ReadRef(file, &m_unk4c);
    } else {
        m_unk4c = nullptr;  // the original stores the flag byte (0) as a word
    }
    ReadU8(file, &m_unk60);
    ReadU8(file, &m_unk50);
    ReadU8(file, &m_unk51);
    ReadU8(file, &m_unk53);
    IKFile_ReadRef(file, &m_pDamage);
    ReadF32LE(file, &m_unk38);
    IKFile_ReadRef(file, &m_unk3c);
    ReadU8(file, &m_unk61);
    ReadU8(file, &m_unk40);
    ReadF32LE(file, &m_unk44);
    return 1;
}

// 0x0036e350 CKS08HeroBlow_EvalTimeScale (vt+0xc0)
float CKS08HeroBlow::EvalTimeScale(float x) const {
    if (m_unk48 == 0) return 1.0f;  // TOC +0x2f58
    return static_cast<const CKCurve2DCpnt*>(m_unk4c)->Evaluate(x);  // 0x00249ea8
}

// vt+0x24 0x0036e5b0 CKS08HeroBlow_RecursiveRegistration: the time-scale curve's (when there is one), then the camera
// data's (vt+0x24), with the same type.
void CKS08HeroBlow::RecursiveRegistration(int32_t type) {
    if (m_unk4c != nullptr) m_unk4c->RecursiveRegistration(type);
    m_unk3c->RecursiveRegistration(type);
}

// vt+0x30 0x0036e650 CKS08HeroBlow_PostLoad: for type 0 the timer (+0x18) back to its reset value (+0x0c).
int32_t CKS08HeroBlow::PostLoad(int32_t type) {
    if (type != 0) return 1;
    m_unk18 = m_unk0c;
    return 1;
}

// vt+0x10 0x0036e670 CKS08HeroBlow_Destroy: the camera data's Destroy (vt+0x10).
void CKS08HeroBlow::Destroy() { m_unk3c->Destroy(); }
