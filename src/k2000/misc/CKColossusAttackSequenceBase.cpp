// Reconstructed original translation unit: 0x470388-0x470778 (GAME_TOC1, main_toc1), 20 functions, 17 live.
// Primary owner: CKColossusAttackSequenceBase (not a registered class; key 0x7c0c, vtable 0xb27708)
// Other owners: CKColossusAttackSequence (2), IKSerializable (1), CKColossusContextualAttackElement (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [ ] 0x470388  CKColossusAttackSequence_ConstructBase_2_maybe  [dead]
//   [ ] 0x470398  KStub_Return1_470398  [dead]
//   [ ] 0x4703a0  KStub_Return1_4703a0  [dead]
//   [x] 0x4703a8  KStub_Return1_4703a8  (CKColossusAttackSequenceBase::LoadNothing, the header)
//   [x] 0x4703b0  CKColossusAttackSequenceBase_7c0c_maybe_vf74  (the header)
//   [x] 0x4703d8  CKColossusAttackSequenceBase_7c0c_maybe_vf78  (the header)
//   [x] 0x4703e8  CKColossusAttackSequenceBase_7c0c_maybe_vf60  (the header)
//   [x] 0x470400  CKColossusAttackSequenceBase_7c0c_maybe_vf50  (the header)
//   [x] 0x470410  CKColossusAttackSequence_ConstructBase_maybe  (the header's constructor)
//   [x] 0x470420  CKColossusAttackSequenceBase_7c0c_maybe_vf28  (the header: Save)
//   [x] 0x470428  CKColossusAttackSequenceBase_7c0c_maybe_vf30  (the header: PostLoad)
//   [x] 0x470470  CKColossusAttackSequenceBase_7c0c_maybe_vf24  (the header: RecursiveRegistration)
//   [x] 0x470478  KStub_Nop_470478  (the header: Destroy)
//   [x] 0x470480  CKColossusAttackSequenceBase_7c0c_maybe_vf2C_2  (= 0x470560: CKColossusAttackSequenceBase::Load)
//   [x] 0x470560  CKColossusAttackSequenceBase_7c0c_maybe_vf2C
//   [x] 0x470640  CKColossusAttackSequenceBase_7c0c_maybe_DeletingDestructor  (the header's destructor)
//   [x] 0x470680  CKColossusAttackSequenceBase_7c0c_maybe_vf0  (the header's destructor)
//   [x] 0x470698  CKColossusAttackSequenceBase_7c0c_maybe_BaseDestructor  (the header's destructor)
//   [x] 0x4706b0  KBaseC_vf80_2  (KBase7CCC::Vf80, k2000/misc/KBase7CCC.h, R11)
//   [x] 0x4706c0  CKColossusContextualAttackElement_vf60  (KBase7CCC::Vf60, Spyro2008/logic/IKSerializable.cpp, R11)
//
//   [x] 0x9c4530  CKColossusAttackSequenceBase_7c0c_maybe_vf14  [inline]  (DOTD_CLASS_KEY)
//   [x] 0x9c4538  CKColossusAttackSequenceBase_7c0c_maybe_vf18  [inline]  (DOTD_CLASS_KEY)
//   [x] 0x9c4540  CKColossusAttackSequenceBase_7c0c_maybe_vf54  [inline]
//   [x] 0x9c4548  CKColossusAttackSequenceBase_7c0c_maybe_vf58  [inline]
//   [x] 0x9c4550  CKColossusAttackSequenceBase_7c0c_maybe_vf5C  [inline]
//   [x] 0x9c4558  CKColossusAttackSequenceBase_7c0c_maybe_vf8  [inline]
#include "k2000/misc/CKColossusAttackSequenceBase.h"

#include "k2000/io/IKFile.h"

// 0x00470560 CKColossusAttackSequenceBase_7c0c_maybe_vf2C (= 0x470480 _vf2C_2): with a level file (type 0) the words
// +0x0c and +0x14, each read (vt+0x14, 4 bytes) and then byte-swapped in place; 1 whatever the type.
int32_t CKColossusAttackSequenceBase::Load(IKFile* file, int32_t type) {
    if (type == 0) {
        ReadU32LE(file, &m_ui32Index);
        ReadS32LE(file, &m_i32Unk14);
    }
    return 1;
}
