// CKS08HeroCombo.cpp - reconstructed original translation unit 0x36f578-0x36ffa0 (GAME_TOC1, main_toc1), 12 functions, 12 live.
// Primary class: CKS08HeroCombo  key 0x7acc  category Logic  size 0x1c  vtable 0xb23180
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x36f578  CKS08HeroCombo_GetNext
//   [x] 0x36f610  CKS08HeroCombo_GetMinRemainingDamage
//   [ ] 0x36f720  RegisterCKS08HeroComboClass
//   [ ] 0x36f798  _GLOBAL__I_36f798
//   [x] 0x36f7a8  CKS08HeroCombo_DeleteArray
//   [x] 0x36f850  CKS08HeroCombo_Create
//   [x] 0x36f888  CKS08HeroCombo_CreateArray
//   [x] 0x36f920  CKS08HeroCombo_RecursiveRegistration  (returns 1: the root's empty slot)
//   [x] 0x36f928  CKS08HeroCombo_Destroy  (empty: the root's default)
//   [x] 0x36f930  CKS08HeroCombo_PostLoad  (returns 1: the root's default)
//   [x] 0x36f938  CKS08HeroCombo_Load
//   [ ] 0x36fc08  CKS08HeroCombo_Save
//
//   [ ] 0x9bed28  CKS08HeroCombo_GetClassType  [inline]
//   [ ] 0x9bed30  CKS08HeroCombo_GetClassID  [inline]
//   [ ] 0x9bed38  CKS08HeroCombo_GetOwnClassId  [inline]
//   [ ] 0x9bed40  CKS08HeroCombo_GetBlow  [inline]
//   [ ] 0x9bed48  CKS08HeroCombo_SetBlow  [inline]
//   [ ] 0x9bed50  CKS08HeroCombo_SetRef14  [inline]
//   [ ] 0x9bed58  CKS08HeroCombo_GetRef14  [inline]
//   [ ] 0x9bed60  CKS08HeroCombo_GetByte18  [inline]
//   [ ] 0x9bed68  CKS08HeroCombo_IsKindOfClass  [inline]
//   [ ] 0x9bed88  CKS08HeroCombo_Destructor  [inline]
//   [ ] 0x9beda0  CKS08HeroCombo_DeletingDestructor  [inline]
#include "Spyro2008/logic/CKS08HeroCombo.h"

#include "Spyro2008/logic/CKS08HeroBlow.h"

#include "k2000/io/IKFile.h"

// 0x0036f938 CKS08HeroCombo_Load: five references and a byte, whatever the type.
int32_t CKS08HeroCombo::Load(IKFile* file, int32_t /*type*/) {
    IKFile_ReadRef(file, &m_unk04);
    IKFile_ReadRef(file, &m_unk08);
    IKFile_ReadRef(file, &m_unk0c);
    IKFile_ReadRef(file, &m_pBlow);
    IKFile_ReadRef(file, &m_unk14);
    ReadU8(file, &m_unk18);
    return 1;
}

// 0x0036f610 CKS08HeroCombo_GetMinRemainingDamage (each branch's recursion runs twice, as the original's).
int32_t CKS08HeroCombo::GetMinRemainingDamage() const {
    if (m_pBlow == nullptr) return 0;
    bool any = false;
    uint32_t best = 0xffffffffu;
    if (m_unk04 != nullptr) {
        const int32_t first = m_unk04->GetMinRemainingDamage();
        any = true;
        if (first != -1) best = static_cast<uint32_t>(m_unk04->GetMinRemainingDamage());
    }
    if (m_unk08 == nullptr) {
        if (!any) return m_pBlow->GetDamageAmount();  // vt+0x54
    } else if (static_cast<uint32_t>(m_unk08->GetMinRemainingDamage()) < best) {
        best = static_cast<uint32_t>(m_unk08->GetMinRemainingDamage());
    }
    return static_cast<int32_t>(static_cast<uint32_t>(m_pBlow->GetDamageAmount()) + best);
}
