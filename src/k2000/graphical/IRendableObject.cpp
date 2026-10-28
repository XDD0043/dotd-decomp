// IRendableObject.cpp - reconstructed original translation unit 0xa71e8-0xa73c8 (GAME_TOC1, main_toc1), 4 functions, 4 live.
// Primary owner: IRendableObject (not a registered class)
// Other owners: IKRenderable (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0xa71e8  IRendableObject_LevelReset
//   [x] 0xa7240  IRendableObject_Save
//   [x] 0xa7248  IRendableObject_ClearReferences
//   [x] 0xa7258  IRendableObject_Load
//
//   [x] 0x990c20  IRendableObject_vf68  [inline]
//   [ ] 0x990c28  KStub_Return1_990c28  [inline]
//   [x] 0x997ce0  IRendableObject_vf58  [inline]
//   [x] 0x997ce8  IRendableObject_vf74  [inline]
//   [x] 0x9a0510  IRendableObject_GetClassGroup  [inline]
//   [x] 0x9a0518  IRendableObject_GetClassId  [inline]
//   [x] 0x9a0520  IRendableObject_IsKindOf  [inline]
//   [x] 0x9a0540  IRendableObject_DeletingDestructor  [inline]
//   [x] 0x9a0580  IRendableObject_Destructor  [inline]
#include "k2000/graphical/IRendableObject.h"

#include "k2000/io/IKFile.h"
#include "k2000/logic/CKSavingManager.h"
#include "k2000/misc/Engine.h"

// 0x000a71d8 IRendableObject_ChangeLightSet
IKSerializable* IRendableObject::ChangeLightSet(IKSerializable* lightSet) {
    IKSerializable* previous = m_pLightSet;
    m_pLightSet = lightSet;
    return previous;
}

// 0x000a71b0 IRendableObject_GetRenderingProperties
void IRendableObject::GetRenderingProperties(uint8_t* first, uint8_t* second, uint8_t* third, uint32_t* blendMode) {
    *first = 0;
    *second = 0xff;
    *third = 0;
    *blendMode = 0;
}

// 0x000a71e8 IRendableObject_RecursiveRegistration
void IRendableObject::RecursiveRegistration(int32_t /*type*/) {
    g_pEngine->m_pSavingManager->RegisterSerializableObject(this, nullptr);
}

// 0x000a7258 IRendableObject_Load
int32_t IRendableObject::Load(IKFile* file, int32_t type) {
    if (type != K_LEVEL_PLATEFORMS) return 1;
    ReadU32LE(file, &m_pPriorityParent);
    IKFile_ReadRef(file, &m_pLightSet);
    ReadU32LE(file, &m_BitProperties);
    m_pNextAccumulatedObject = nullptr;
    return 1;
}
