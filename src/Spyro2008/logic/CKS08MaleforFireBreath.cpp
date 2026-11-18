// CKS08MaleforFireBreath.cpp - reconstructed original translation unit 0x4ea4c8-0x4eafb0 (GAME_TOC1, main_toc1), 23 functions, 23 live.
// Primary class: CKS08MaleforFireBreath  key 0xac4c  category Logic  size 0x130  vtable 0xb2a8f0
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x4ea4c8  CKS08MaleforFireBreath_Delete
//   [x] 0x4ea518  CKS08MaleforFireBreath_vf64  (a nop: CKGolemAttackCommon's Vf64 is one too)
//   [x] 0x4ea520  CKS08MaleforFireBreath_vf5C  (inherited: CKGolemAttackCommon::Vf5C)
//   [x] 0x4ea548  CKS08MaleforFireBreath_AttachVolumesToHotSpots_maybe  (inherited: CKGolemAttackCommon::AttachVolumesToHotSpots)
//   [x] 0x4ea570  CKS08MaleforFireBreath_StopAttack_maybe
//   [x] 0x4ea608  CKS08MaleforFireBreath_StartAttack_maybe
//   [x] 0x4ea650  CKS08MaleforFireBreath_PostLoad
//   [ ] 0x4ea6c8  CKS08MaleforFireBreath_Save
//   [x] 0x4ea6f0  CKS08MaleforFireBreath_RecursiveRegistration  (inherited: CKGolemAttackCommon's RecursiveRegistration slot)
//   [x] 0x4ea718  CKS08MaleforFireBreath_Destroy
//   [x] 0x4ea780  CKS08MaleforFireBreath_DeletingDestructor  (implicit destructor: CKGolemAttackCommon's)
//   [x] 0x4ea7c8  CKS08MaleforFireBreath_Destructor  (implicit destructor: CKGolemAttackCommon's)
//   [x] 0x4ea7f8  CKS08MaleforFireBreath_DestructBody  (implicit destructor: CKGolemAttackCommon's)
//   [x] 0x4ea828  CKS08MaleforFireBreath_Construct_2  (the constructor CKS08MaleforFireBreath() (a second copy))
//   [x] 0x4ea860  CKS08MaleforFireBreath_Construct
//   [x] 0x4ea898  CKS08MaleforFireBreath_DeleteArray
//   [ ] 0x4ea938  RegisterCKS08MaleforFireBreathClass
//   [ ] 0x4ea9c0  _GLOBAL__D_4ea9c0
//   [ ] 0x4ea9d0  _GLOBAL__I_4ea9d0
//   [x] 0x4ea9e0  CKS08MaleforFireBreath_Update_maybe
//   [x] 0x4eab58  CKS08MaleforFireBreath_Create
//   [x] 0x4eabb0  CKS08MaleforFireBreath_CreateArray
//   [x] 0x4eac60  CKS08MaleforFireBreath_Load
//
//   [ ] 0x9c6768  CKS08MaleforFireBreath_IsKindOfClass  [inline]
//   [ ] 0x9c67b8  CKS08MaleforFireBreath_GetClassType  [inline]
//   [ ] 0x9c67c0  CKS08MaleforFireBreath_GetClassID  [inline]
#include "Spyro2008/logic/CKS08MaleforFireBreath.h"

#include "Spyro2008/misc/CKS08MaleforFireBreathAbilityHost.h"
#include "k2000/io/IKFile.h"
#include "k2000/logic/CKAbilityElement.h"
#include "k2000/system/IKTime.h"

// 0x004eac60 CKS08MaleforFireBreath_Load: CKGolemAttackCommon's data, then, for K_LEVEL_PLATEFORMS only, two
// floats, a reference and eight groups of four references.
int32_t CKS08MaleforFireBreath::Load(IKFile* file, int32_t type) {
    CKGolemAttackCommon::Load(file, type);
    if (type != 0) return 1;

    ReadF32LE(file, &m_unk120);
    ReadF32LE(file, &m_unk124);
    IKFile_ReadRef(file, &m_unk12c);
    for (int32_t i = 0; i < 8; ++i) {
        IKFile_ReadRef(file, &m_unk98[i].m_unk00);
        IKFile_ReadRef(file, &m_unk98[i].m_unk04);
        IKFile_ReadRef(file, &m_unk98[i].m_unk08);
        IKFile_ReadRef(file, &m_unk98[i].m_unk0c);
    }
    return 1;
}

// 0x004ea718 CKS08MaleforFireBreath_Destroy
void CKS08MaleforFireBreath::Destroy() {
    CKGolemAttackCommon::Destroy();
    if (m_unk118 != nullptr) delete m_unk118;  // vt+0x04 (the pointer is kept)
}

// 0x004ea608 CKS08MaleforFireBreath_StartAttack_maybe
void CKS08MaleforFireBreath::StartAttack() {
    CKGolemAttackCommon::StartAttack();
    m_unk11d = 0;
    m_unk128 = 0.0f;
    m_unk11c = 0;
}

// 0x004ea570 CKS08MaleforFireBreath_StopAttack_maybe
void CKS08MaleforFireBreath::StopAttack() {
    CKGolemAttackCommon::StopAttack();
    if (m_unk11d != 0 || m_unk11c == 0) return;
    static_cast<CKAbilityElement*>(m_unk12c)->Stop(0);  // vt+0x5c
    m_unk11d = 1;
}

// 0x004ea650 CKS08MaleforFireBreath_PostLoad
int32_t CKS08MaleforFireBreath::PostLoad(int32_t type) {
    CKGolemAttackCommon::PostLoad(type);  // 0x004b8d80
    if (type == 0) m_unk118 = new CKS08MaleforFireBreathAbilityHost(this);  // OperatorNew(8) + 0x004eb810
    return 1;
}

// 0x004ea9e0 CKS08MaleforFireBreath_Update_maybe. The time tests are fcmpu + cror lt|eq: not taken for NaN, as `<=`.
void CKS08MaleforFireBreath::Update(IKTime* clock) {
    CKGolemAttackCommon::Update(clock);  // 0x004b9898
    const float t = m_unk128 + clock->m_afDeltaTime[IKTime::SCALABLE_GAME_TIME];
    m_unk128 = t;
    CKAbilityElement* ability = static_cast<CKAbilityElement*>(m_unk12c);
    if (m_unk120 <= t && m_unk11c == 0) {
        m_unk11c = 1;
        ability->Start(m_unk118);  // vt+0x58
    } else if (m_unk124 <= t && m_unk11d == 0) {
        if (m_unk11c == 0) return;
        m_unk11d = 1;
        ability->Stop(0);  // vt+0x5c
    }
    if (m_unk11c == 0 || m_unk11d != 0) return;
    if (ability->Update(clock->m_afDeltaTime[IKTime::SCALABLE_GAME_TIME]) == 0) m_unk11d = 1;  // vt+0x60
}
