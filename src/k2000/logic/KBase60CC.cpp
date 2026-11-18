// KBase60CC.cpp - reconstructed original translation unit 0x203460-0x203760 (GAME_TOC1, main_toc1), 14 functions, 13 live.
// Primary owner: KBase60CC (not a registered class)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x203460  KBase60CC_Construct
//   [x] 0x203478  StaticInitAndDestruction_203478  (the two file statics below)
//   [ ] 0x2034a8  _GLOBAL__I_2034a8
//   [ ] 0x2034b8  _GLOBAL__D_2034b8
//   [x] 0x2034c8  KBase60CC_Activate_maybe
//   [ ] 0x203540  KBase60CC_Construct_2  [dead]
//   [x] 0x203558  KBase60CC_Deactivate_maybe
//   [ ] 0x2035d0  KBase60CC_Save
//   [x] 0x2035d8  KBase60CC_Load
//   [x] 0x2036e0  KBase60CC_LevelReset  (RecursiveRegistration: returns 1, the default slot)
//   [x] 0x2036e8  KBase60CC_ClearReferences  (empty)
//   [x] 0x2036f0  KBase60CC_DeletingDestructor  (the destructor; delete)
//   [x] 0x203730  KBase60CC_Destructor  (C++ destructor chain: vtable stores only)
//   [x] 0x203748  KBase60CC_BaseDestructor  (C++ destructor chain: vtable stores only)
//
//   [ ] 0x9b1628  KBase60CC_GetClassGroup  [inline]
//   [ ] 0x9b1630  KBase60CC_GetClassId  [inline]
//   [ ] 0x9b1638  KBase60CC_IsKindOf  [inline]
//   [x] 0x9b1658  KBase610C_vf58  [inline]
#include "k2000/logic/KBase60CC.h"

#include "k2000/core/Stub.h"
#include "k2000/io/IKFile.h"
#include "k2000/logic/input/CKInputBlockSequential.h"
#include "k2000/misc/Engine.h"
#include "k2000/services/CKSrvInput.h"

// 0x002035d8 KBase60CC_Load
int32_t KBase60CC::Load(IKFile* file, int32_t type) {
    if (type != K_LEVEL_PLATEFORMS) return 1;
    ReadU16LE(file, &m_unk0c);
    m_unk0e = 0;
    IKFile_ReadRef(file, &m_unk08);
    return 1;
}

// 0x002034c8 KBase60CC_Activate_maybe
void KBase60CC::Activate() {
    if (m_unk0e != 0) return;
    if (m_unk08 == nullptr)
        static_cast<CKSrvInput*>(g_pEngine->m_srvInput)->PushActiveBlock(this);
    else
        static_cast<CKInputBlockSequential*>(m_unk08)->PushActiveChild(this);
    m_unk0e = 1;
}

// 0x00203558 KBase60CC_Deactivate_maybe
void KBase60CC::Deactivate() {
    if (m_unk0e == 0) return;
    if (m_unk08 == nullptr)
        static_cast<CKSrvInput*>(g_pEngine->m_srvInput)->RemoveActiveBlock(this);
    else
        static_cast<CKInputBlockSequential*>(m_unk08)->RemoveActiveChild(this);
    m_unk0e = 0;
}

// vt+0x5c / +0x60: pure in KBase60CC's vtable 0xb1f068. KBase628C and CKLogicalBlock (0x20fe70 / 0x20fdd0) override
// both, so nothing reaches these defaults.
void KBase60CC::CollectAnchors(TVector<KBase610C*, 1>* /*out*/) {}
void KBase60CC::DisconnectAnchors() {}

// 0x00203478 StaticInitAndDestruction_203478 (_GLOBAL__I_2034a8): two file statics (0x00cea940, 0x00cea944) set to
// -1.0f. Nothing in the game reads them.
namespace {
[[maybe_unused]] float s_unkcea940 = -1.0f;
[[maybe_unused]] float s_unkcea944 = -1.0f;
}  // namespace
