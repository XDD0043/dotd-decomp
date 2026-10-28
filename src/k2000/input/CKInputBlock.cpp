// CKInputBlock.cpp - reconstructed original translation unit 0x209a90-0x20a208 (GAME_TOC1, main_toc1), 17 functions, 17 live.
// Primary owner: CKInputBlock (not a registered class)
// Other owners: KBase628C (5), PS3_CKInputBlockPosition (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [ ] 0x209a90  CKInputBlock_628c_maybe_IsActionPressed_maybe
//   [ ] 0x209ae8  StaticInitAndDestruction_209ae8
//   [ ] 0x209b18  _GLOBAL__I_209b18
//   [ ] 0x209b28  _GLOBAL__D_209b28
//   [x] 0x209b38  CKInputBlock_628c_maybe_Load
//   [ ] 0x209c40  CKInputBlock_628c_maybe_Save
//   [ ] 0x209c68  CKInputBlock_628c_maybe_LevelReset
//   [ ] 0x209c90  KBase628C_ClearReferences
//   [ ] 0x209cb8  CKInputBlock_628c_maybe_DeletingDestructor
//   [ ] 0x209d00  KBase628C_Destructor
//   [ ] 0x209d30  CKInputBlock_628c_maybe_BaseDestructor
//   [ ] 0x209d60  KBase628C_Construct_maybe_2
//   [x] 0x209d98  KBase628C_Construct_maybe
//   [ ] 0x209dd0  PS3_CKInputBlockPosition_CollectAnchors_maybe
//   [x] 0x209fa0  KBase628C_Evaluate
//   [ ] 0x20a108  CKInputBlock_628c_maybe_GetActionValue_maybe
//   [ ] 0x20a158  CKInputBlock_IsStickDirectionPressed_maybe
//
//   [ ] 0x9b17f0  KBase628C_IsKindOf  [inline]
//   [ ] 0x9b1818  KBase628C_GetClassGroup  [inline]
//   [ ] 0x9b1820  KBase628C_GetClassId  [inline]
//   [ ] 0x9b1870  KBase628C_vf9C  [inline]
//   [ ] 0x9b1878  KBase628C_vfA0  [inline]
//   [ ] 0x9b1880  KBase628C_vfA4  [inline]
//   [ ] 0x9b1888  KBase628C_vfA8  [inline]
//   [ ] 0x9b18c0  KBase628C_vf70  [inline]
#include "k2000/input/KBase628C.h"

#include "k2000/io/IKFile.h"
#include "k2000/logic/input/CKInputAnchor.h"

// 0x00209b38 CKInputBlock_628c_maybe_Load
int32_t KBase628C::Load(IKFile* file, int32_t type) {
    KBase60CC::Load(file, type);
    if (type != K_LEVEL_PLATEFORMS) return 1;
    ReadRaw(file, &m_unk0f, 1);
    IKFile_ReadObjectRefArray(file, reinterpret_cast<IKSerializable**>(m_apInputs), 2);
    return 1;
}

// 0x00209fa0 KBase628C_Evaluate
void KBase628C::Evaluate(uint8_t value) {
    if (value == 0) return;
    if (m_apInputs[1]->m_unk08 != 0) {
        m_apInputs[0]->SetValue(0);  // vt+0x58
        m_apInputs[1]->SetValue(0);
        OnDeactivate();              // vt+0x54
        return;
    }
    CKInputAnchor* input = m_apInputs[0];
    if (input->m_unk08 == 0) return;
    input->SetValue(0);
    if (m_unk08 == nullptr || m_unk0e == 0) OnActivate();  // vt+0x50
}
