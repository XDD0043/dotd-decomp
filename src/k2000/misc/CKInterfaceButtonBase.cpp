// CKInterfaceButtonBase.cpp - reconstructed original translation unit 0x67ec0-0x683d8 (GAME_TOC1, main_toc1), 12 functions, 11 live.
// Primary owner: CKInterfaceButtonBase (not a registered class)
// Other owners: CKInterfaceObject (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x67ec0  CKInterfaceButtonBase_63cc_maybe_StartFade
//   [x] 0x67f88  CKInterfaceButtonBase_63cc_maybe_vf0
//   [x] 0x67fa0  CKInterfaceButtonBase_63cc_maybe_ConstructBase
//   [ ] 0x67fc0  CKInterfaceButtonBase_63cc_maybe_ConstructBase_2  [dead]
//   [x] 0x67fe0  CKInterfaceButtonBase_63cc_maybe_vf28
//   [x] 0x67fe8  CKInterfaceButtonBase_63cc_maybe_vf24
//   [x] 0x67ff0  CKInterfaceObject_ClearReferences_BaseNop_maybe  (Destroy: empty; the derived Destroy calls it, nothing to port)
//   [x] 0x67ff8  CKInterfaceButtonBase_63cc_maybe_Close
//   [x] 0x68010  CKInterfaceButtonBase_63cc_maybe_Load
//   [x] 0x68288  CKInterfaceButtonBase_63cc_maybe_BaseDestructor  (C++ destructor chain: vtable stores only)
//   [x] 0x682a0  CKInterfaceButtonBase_63cc_maybe_DeletingDestructor  (the destructor; delete)
//   [x] 0x682e0  CKInterfaceButtonBase_63cc_maybe_Open
//
//   [x] 0x9984d8  CKInterfaceButtonBase_63cc_maybe_vf14  [inline]
//   [x] 0x9984e0  CKInterfaceButtonBase_63cc_maybe_vf18  [inline]
//   [x] 0x9984e8  CKInterfaceButtonBase_63cc_maybe_vf5C  [inline]
//   [x] 0x9984f0  CKInterfaceButtonBase_63cc_maybe_vf60  [inline]
//   [x] 0x998508  KBase63CC_vf64  [inline]
//   [x] 0x998520  CKInterfaceButtonBase_63cc_maybe_vf78  [inline]
//   [x] 0x998528  KBase63CC_vf7C  [inline]
//   [x] 0x998538  KBase63CC_vf80  [inline]
//   [x] 0x998540  CKInterfaceButtonBase_63cc_maybe_vf84  [inline]
//   [x] 0x998560  CKInterfaceButtonBase_63cc_maybe_vf6C  [inline]
//   [x] 0x998578  CKInterfaceButtonBase_63cc_maybe_vf58  [inline]
//   [x] 0x998590  CKInterfaceButtonBase_63cc_maybe_vf70  [inline]
//   [x] 0x9985a8  CKInterfaceButtonBase_63cc_maybe_vf8  [inline]
#include "k2000/misc/CKInterfaceButtonBase.h"

#include "k2000/io/IKFile.h"
#include "k2000/math/CVector2.h"

namespace {
// 0x00c50dc4: a CVector2 (0, 0) in the data segment (read live: 0.0, 0.0); Open places the button there.
const CVector2 kZeroVector2 = {0.0f, 0.0f};
}  // namespace

// 0x00067fa0 CKInterfaceButtonBase_63cc_maybe_ConstructBase: the vtable, then +0x20, +0x28, +0x24 = 0.
CKInterfaceButtonBase::CKInterfaceButtonBase() {
    m_fFadeTarget = 0.0f;
    m_fFade = 0.0f;
    m_fFadeSpeed = 0.0f;
}

// 0x00068010 CKInterfaceButtonBase_63cc_maybe_Load: K_LEVEL_PLATEFORMS only.
int32_t CKInterfaceButtonBase::Load(IKFile* file, int32_t type) {
    if (type != K_LEVEL_PLATEFORMS) return 1;
    ReadU8(file, &m_baFlags);
    ReadF32LE(file, &m_fDelay);
    ReadU8(file, &m_aNeighbors[3]);
    ReadU8(file, &m_aNeighbors[2]);
    ReadU8(file, &m_aNeighbors[1]);
    ReadU8(file, &m_aNeighbors[0]);
    IKFile_ReadRef(file, &m_pMenu);
    IKFile_ReadRef(file, &m_unk2c);
    m_fFadeSpeed = 0x1p+0f;
    m_fFade = 0x1p+0f;
    m_fFadeTarget = 0x1p+0f;
    return 1;
}

// 0x00067ec0 CKInterfaceButtonBase_63cc_maybe_StartFade (the test is on the whole register).
void CKInterfaceButtonBase::StartFade(float value, float speed, uint8_t fadeIn) {
    if (fadeIn != 0) {
        m_fFadeTarget = value;
        m_fFade = 0.0f;
    } else {
        m_fFade = value;
        m_fFadeTarget = 0.0f;
    }
    m_fFadeSpeed = speed;
    Show();                    // vt+0x6c
    UpdateVisibility(fadeIn);  // vt+0x68
}

// 0x00067ff8 CKInterfaceButtonBase_63cc_maybe_Close: the disabled and updated bits cleared.
void CKInterfaceButtonBase::Close() { m_baFlags = static_cast<uint8_t>(m_baFlags & 0xf9); }

// 0x000682e0 CKInterfaceButtonBase_63cc_maybe_Open: bits 1..4 cleared and the fading bit set, the button
// placed at (0, 0), the fade set to 1 from 0 (current 0), shown, then UpdateVisibility(1). `focused` is
// not read at this level.
void CKInterfaceButtonBase::Open(uint8_t /*focused*/) {
    m_baFlags = static_cast<uint8_t>((m_baFlags & ~0x1eu) | kFlagFading);
    SetPosition(kZeroVector2);   // vt+0x60
    m_fFadeSpeed = 0x1p+0f;      // TOC -0x6ecc
    m_fFadeTarget = 0x1p+0f;
    m_fFade = 0.0f;
    Show();                      // vt+0x6c
    UpdateVisibility(1);         // vt+0x68
}
