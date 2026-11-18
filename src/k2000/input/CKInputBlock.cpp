// CKInputBlock.cpp - reconstructed original translation unit 0x209a90-0x20a208 (GAME_TOC1, main_toc1), 17 functions, 17 live.
// Primary owner: CKInputBlock (not a registered class)
// Other owners: KBase628C (5), PS3_CKInputBlockPosition (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x209a90  CKInputBlock_628c_maybe_IsActionPressed_maybe  (InputBlock_IsActionPressed, k2000/logic/input/InputBlockQueries.h (P06))
//   [x] 0x209ae8  StaticInitAndDestruction_209ae8  (s_inputBlockPair)
//   [ ] 0x209b18  _GLOBAL__I_209b18
//   [ ] 0x209b28  _GLOBAL__D_209b28
//   [x] 0x209b38  CKInputBlock_628c_maybe_Load
//   [ ] 0x209c40  CKInputBlock_628c_maybe_Save
//   [x] 0x209c68  CKInputBlock_628c_maybe_LevelReset  (RecursiveRegistration: KBase60CC's (0x2036e0, the default slot), then 1)
//   [x] 0x209c90  KBase628C_ClearReferences  (inherited: KBase60CC_Destroy)
//   [x] 0x209cb8  CKInputBlock_628c_maybe_DeletingDestructor  (the implicit destructor: the vtable, KBase60CC's, delete)
//   [x] 0x209d00  KBase628C_Destructor  (C++ destructor chain: vtable stores only)
//   [x] 0x209d30  CKInputBlock_628c_maybe_BaseDestructor  (C++ destructor chain: vtable stores only)
//   [ ] 0x209d60  KBase628C_Construct_maybe_2  [dead: no pointer to its descriptor 0xb7ac60, no call]
//   [x] 0x209d98  KBase628C_Construct_maybe
//   [x] 0x209dd0  PS3_CKInputBlockPosition_CollectAnchors_maybe  (ported by P05 with CKInputBlockSequential's)
//   [x] 0x209fa0  KBase628C_Evaluate
//   [x] 0x20a108  CKInputBlock_628c_maybe_GetActionValue_maybe  (InputBlock_GetActionValue, k2000/logic/input/InputBlockQueries.h (P06))
//   [x] 0x20a158  CKInputBlock_IsStickDirectionPressed_maybe  (InputBlock_IsStickDirectionPressed, k2000/logic/input/InputBlockQueries.h (P06))
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

// 0x00209ae8 StaticInitAndDestruction_209ae8: the unit's static pair at 0xcea974 set to (-1, -1) (TOC -0xf50). Only
// this initialiser loads its TOC slot (-0xf54); nothing reads it.
[[maybe_unused]] static float s_inputBlockPair[2] = {-1.0f, -1.0f};

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

// 0x00209dd0 PS3_CKInputBlockPosition_CollectAnchors_maybe: the two input anchors appended (each append grows the block
// by one element when full).
void KBase628C::CollectAnchors(TVector<KBase610C*, 1>* out) {
    KAnchor_PushBack(out, static_cast<KBase610C*>(m_apInputs[0]));
    KAnchor_PushBack(out, static_cast<KBase610C*>(m_apInputs[1]));
}
