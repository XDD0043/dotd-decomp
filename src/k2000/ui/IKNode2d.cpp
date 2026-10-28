// IKNode2d.cpp - reconstructed original translation unit 0x69848-0x6a1f0 (GAME_TOC1, main_toc1), 25 functions, 17 live.
// Primary owner: IKNode2d (not a registered class)
// Other owners: Text2dBlock (3), C2dElementBase (2), CText2d (2), CColorTextButton2d (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x69848  CColorTextButton2d_RecursiveRegistration
//   [x] 0x698a8  KStub_Nop_698a8
//   [ ] 0x698b0  IKNode2d_GetScreenRect_maybe
//   [ ] 0x69950  IKNode2d_RemoveFromParent_maybe  [dead]
//   [ ] 0x699a0  IKNode2d_BringToFront_maybe
//   [x] 0x69a00  IKNode2d_ConstructBase
//   [ ] 0x69a50  IKNode2d_IsOnScreen_maybe  [dead]
//   [ ] 0x69b68  IKNode2d_MoveByPixels_maybe  [dead]
//   [ ] 0x69bf0  IKNode2d_SetPositionPixels_maybe  [dead]
//   [ ] 0x69c68  IKNode2d_GetPositionPixels_maybe  [dead]
//   [x] 0x69ce8  IKNode2d_ResetRuntime_maybe
//   [ ] 0x69d10  IKNode2d_ConstructBase_2  [dead]
//   [x] 0x69d60  IKNode2d_Save
//   [x] 0x69d68  IKNode2d_ClearReferences
//   [x] 0x69da8  IKNode2d_Load
//   [ ] 0x6a0b0  KStub_Nop_6a0b0
//   [ ] 0x6a0b8  KStub_Return1_6a0b8
//   [ ] 0x6a0c0  Text2dBlock_ClearReferences_maybe
//   [ ] 0x6a100  Text2dBlock_ClearTextState_maybe
//   [ ] 0x6a118  FUN_0006a118  [dead]
//   [ ] 0x6a128  FUN_0006a128  [dead]
//   [ ] 0x6a148  CText2d_RetokenizeText_maybe
//   [ ] 0x6a190  KStub_Return1_6a190
//   [x] 0x6a198  Text2dBlock_GetTextId_maybe  (IKText2d::GetTextId, TextData.cpp)
//   [ ] 0x6a1a8  CText2d_SetAlpha_maybe
//
//   [ ] 0x994260  IKNode2d_GetClassGroup  [inline]
//   [ ] 0x994268  IKNode2d_GetClassId  [inline]
//   [x] 0x994278  IKNode2d_vf50  [inline]
//   [x] 0x994280  IKNode2d_vf5C  [inline]
//   [x] 0x994298  IKNode2d_SetNextSibling  [inline]
//   [x] 0x9942a0  IKNode2d_SetPrevSibling  [inline]
//   [x] 0x9942a8  IKNode2d_vf74  [inline]
//   [ ] 0x9942c0  KStub_Return0_9942c0  [inline]
//   [ ] 0x9942c8  KStub_Return0_9942c8  [inline]
//   [x] 0x994378  IKNode2d_Hide  [inline]
//   [x] 0x994390  IKNode2d_Show  [inline]
//   [x] 0x9943a8  IKNode2d_vf60  [inline]
//   [x] 0x9943b8  IKNode2d_IsKindOf  [inline]
//   [x] 0x994478  IKNode2d_DeletingDestructor  [inline]
//   [x] 0x9944b8  IKNode2d_Destructor  [inline]
//
// Ported: the constructor, RecursiveRegistration, FreeMemory and Load; the one-line slots are inline in
// IKNode2d.h. Not yet: the screen-rectangle helpers (0x698b0 is the stubbed slot +0x7c) and the
// Text2dBlock/CText2d functions of this unit (CText2d's port).
#include "k2000/ui/IKNode2d.h"

#include <cstring>

#include "k2000/io/IKFile.h"
#include "k2000/logic/CKSavingManager.h"
#include "k2000/misc/Engine.h"

namespace {
// One Read of count little-endian words, then each word byte-swapped (lwbrx after the Read).
uint32_t ReadWordsLE(IKFile* file, void* dst, uint32_t count) {
    uint8_t bytes[16];
    const uint32_t got = file->Read(bytes, 4 * count);
    for (uint32_t i = 0; i < count; ++i) {
        const uint8_t* b = bytes + 4 * i;
        const uint32_t word = static_cast<uint32_t>(b[0]) | (static_cast<uint32_t>(b[1]) << 8) |
                              (static_cast<uint32_t>(b[2]) << 16) | (static_cast<uint32_t>(b[3]) << 24);
        std::memcpy(static_cast<uint8_t*>(dst) + 4 * i, &word, 4);
    }
    return got;
}
}  // namespace

// 0x00069a00 IKNode2d_ConstructBase. The stores in the original's order.
IKNode2d::IKNode2d() {
    m_v2ConstantScale.m_fX = 0x1p+0f;
    m_ui8CenterHAlign = 0;
    m_pNext = nullptr;
    m_f32RotateAngle = 0.0f;  // the word 0
    m_ui8Type = 0;
    m_baFlags = 0;
    m_ui8CenterWAlign = 0;
    m_pOwner = nullptr;
    m_pPrevious = nullptr;
    m_vPosition.m_fX = 0.0f;
    m_vPosition.m_fY = 0.0f;
    m_v2ConstantScale.m_fY = 0x1p+0f;
}

// 0x00069848 (Ghidra: CColorTextButton2d_RecursiveRegistration)
void IKNode2d::RecursiveRegistration(int32_t type) {
    if (type == K_LEVEL_PLATEFORMS) g_pEngine->m_pSavingManager->RegisterSerializableObject(this, nullptr);
}

// 0x00069ce8 IKNode2d_ResetRuntime_maybe (XXL2 slot FreeMemory). The stores in the original's order.
void IKNode2d::FreeMemory() {
    m_ui8CenterHAlign = 0;
    m_f32RotateAngle = 0.0f;
    m_ui8Type = 0;
    m_baFlags = 0;
    m_ui8CenterWAlign = 0;
    m_vPosition.m_fX = 0.0f;
    m_vPosition.m_fY = 0.0f;
}

// 0x00069da8 IKNode2d_Load. Reads for every type (no branch).
int32_t IKNode2d::Load(IKFile* file, int32_t /*type*/) {
    ReadU8(file, &m_ui8Type);
    ReadU8(file, &m_baFlags);
    ReadU8(file, &m_ui8CenterWAlign);
    ReadU8(file, &m_ui8CenterHAlign);
    IKFile_ReadRef(file, &m_pOwner);
    IKFile_ReadRef(file, &m_pPrevious);
    IKFile_ReadRef(file, &m_pNext);
    ReadWordsLE(file, &m_vPosition, 2);  // one 8-byte read, both words swapped
    ReadF32LE(file, &m_f32RotateAngle);
    return 1;
}
