// CBackgroundManager.cpp - reconstructed original translation unit 0x935d0-0x94bf0 (GAME_TOC1, main_toc1), 31 functions, 19 live.
// Primary class: CBackgroundManager  key 0x68d  category Graphical  size 0x24  vtable 0xb16d90
// Other owners: BackgroundSectorEntry (2), DrawBackgroundGradientQuad (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x935d0  CBackgroundManager_Delete
//   [ ] 0x93620  CBackgroundManager_Construct  [dead]
//   [ ] 0x93648  CBackgroundManager_Construct_2  [dead]
//   [ ] 0x93670  CBackgroundManager_GetEntryArray_maybe  [dead]
//   [x] 0x93680  CBackgroundManager_Init_maybe
//   [x] 0x93690  CBackgroundManager_HideAllBackgrounds_maybe
//   [ ] 0x936f8  CBackgroundManager_RecursiveRegistration
//   [ ] 0x93758  BackgroundSectorEntry_Construct_maybe  [dead]
//   [ ] 0x937a8  BackgroundSectorEntry_Construct_2_maybe  [dead]
//   [ ] 0x937f8  KStub_Nop_937f8  [dead]
//   [ ] 0x93800  KStub_Return1_93800  [dead]
//   [ ] 0x93808  CBackgroundManager_SetEntryVisible_maybe  [dead]
//   [ ] 0x93840  RegisterCBackgroundManagerClass
//   [ ] 0x938b8  _GLOBAL__I_938b8
//   [ ] 0x938c8  CBackgroundManager_Save
//   [ ] 0x938f0  CBackgroundManager_Update_2  [dead]
//   [x] 0x939a0  CBackgroundManager_DeleteArray
//   [ ] 0x93a48  KStub_Nop_93a48  [dead]
//   [x] 0x93a50  CBackgroundManager_vf70
//   [ ] 0x93a70  CBackgroundManager_PostLoad
//   [x] 0x93a78  CBackgroundManager_CreateArray
//   [x] 0x93b30  CBackgroundManager_Create
//   [x] 0x93b88  CBackgroundManager_Destroy
//   [ ] 0x93c48  DrawBackgroundGradientQuad_maybe
//   [x] 0x944c8  CBackgroundManager_LoadSectorBackground
//   [x] 0x946e0  CBackgroundManager_Update
//   [x] 0x94790  CBackgroundManager_Load
//   [ ] 0x94988  CBackgroundManager_SaveSectorBackground_maybe  [dead]
//   [ ] 0x94b68  CBackgroundManager_Destructor
//   [ ] 0x94b88  CBackgroundManager_Destructor_2  [dead]
//   [ ] 0x94ba8  CBackgroundManager_DeletingDestructor
//
//   [x] 0x99c860  CBackgroundManager_GetClassType  [inline]
//   [x] 0x99c868  CBackgroundManager_GetClassID  [inline]
//   [x] 0x99c870  CBackgroundManager_GetSerializationFlags  [inline]
//   [ ] 0x99c878  CBackgroundManager_Draw  [inline]
//   [x] 0x99c880  CBackgroundManager_IsKindOfClass  [inline]
#include "k2000/graphical/CBackgroundManager.h"

#include "k2000/io/IKFile.h"
#include "k2000/logic/CKLevel.h"
#include "k2000/logic/CKSector.h"
#include "k2000/managers/CKGraphic.h"
#include "k2000/misc/Engine.h"
#include "k2000/render/CRenderer.h"
#include "k2000/scenegraph/CSGLeaf.h"

// 0x00093b30 CBackgroundManager_Create (= CBackgroundManager_Construct 0x93620): the IRendableObject
// part only, in the original's store order.
CBackgroundManager::CBackgroundManager() {
    m_pLightSet = nullptr;
    m_pNextAccumulatedObject = nullptr;
    m_BitProperties = 0;
    m_pPriorityParent = 0;
}

// Inlined in CBackgroundManager_Load (0x948c8..0x94928), in the original's store order. The two floats
// are TOC constants (-0x6464 0.33, -0x6460 10000.0).
CBackgroundData::CBackgroundData() {
    m_unk18 = 0;
    m_fPercentFogFadeBegin = 0x1.51eb86p-2f;  // 0.33 (0x3ea8f5c3)
    m_fRadiusModel = 0x1.388p+13f;            // 10000.0 (0x461c4000)
    m_eRenderType = 0;
    m_fHorizon = 0.0f;
    // Bit fields of the last word: bit 0 = 1, bit 1 = 1, bits 2-3 = 0.
    m_unk18 = (m_unk18 & ~0xfu) | 3u;
}

// 0x000944c8 CBackgroundData::Load (Ghidra CBackgroundManager_LoadSectorBackground)
int32_t CBackgroundData::Load(IKFile* file, int32_t type) {
    if (type != K_LEVEL_PLATEFORMS) return 1;
    IKFile_ReadRef(file, &m_pRootNode);
    ReadU32LE(file, &m_eRenderType);
    ReadF32LE(file, &m_fPercentFogFadeBegin);
    ReadF32LE(file, &m_fHorizon);
    ReadF32LE(file, &m_fRadiusModel);
    ReadU32LE(file, &m_unk18);
    return 1;
}

// 0x00093680 CBackgroundManager_Init_maybe (InitializeRendererStages): no backgrounds.
void CBackgroundManager::Init() {
    m_ui8NbRootNode = 0;
    m_apRootNode = nullptr;
}

// 0x00093b88 CBackgroundManager_Destroy (the level unload): IRendableObject's, then every background
// deleted (operator delete, no destructor call) and the array (operator delete[]). The count is kept.
void CBackgroundManager::Destroy() {
    IRendableObject::Destroy();  // 0xa7248
    CBackgroundData** array = m_apRootNode;
    for (uint32_t i = 0; i < m_ui8NbRootNode; ++i) {
        if (m_apRootNode[i] != nullptr) ::operator delete(m_apRootNode[i]);  // 0xa3ce18 OperatorDelete
    }
    if (array != nullptr) delete[] array;
    m_apRootNode = nullptr;
}

// 0x00094790 CBackgroundManager_Load
int32_t CBackgroundManager::Load(IKFile* file, int32_t type) {
    IRendableObject::Load(file, type);
    if (type != K_LEVEL_PLATEFORMS) return 1;
    ReadU8(file, &m_ui8NbRootNode);
    if (m_ui8NbRootNode == 0) {
        m_apRootNode = nullptr;
        return 1;
    }
    m_apRootNode = new CBackgroundData*[m_ui8NbRootNode];  // OperatorNewArray(count * 4)
    for (uint32_t i = 0; i < m_ui8NbRootNode; ++i) {
        m_apRootNode[i] = new CBackgroundData();  // OperatorNew(0x1c)
        m_apRootNode[i]->Load(file, K_LEVEL_PLATEFORMS);
    }
    return 1;
}

// 0x00093a50 CBackgroundManager_CanBeUpdated
int32_t CBackgroundManager::CanBeUpdated() {
    return static_cast<int32_t>(((g_pEngine->m_graphic->m_renderer->m_bitProperties ^ 2) >> 1) & 1);
}

// 0x000946e0 CBackgroundManager_PreUpdate: the backgrounds start hidden (flag 4 of the root node: CBackgroundManager_HideAllBackgrounds
// 0x93690, the level's load) and the active sectors' are shown here every frame.
void CBackgroundManager::PreUpdate(IKTime* /*frameClock*/) {
    CKLevel* level = g_pEngine->m_level;
    for (CKSector* sector = level->IterateActiveSectors(nullptr); sector != nullptr; sector = level->IterateActiveSectors(sector)) {
        const uint32_t index = sector->m_ui16NumSector & 0xff;
        if (m_apRootNode == nullptr || index >= m_ui8NbRootNode) continue;
        CSGLeaf* root = static_cast<CSGLeaf*>(m_apRootNode[index]->m_pRootNode);
        if (root != nullptr) root->m_sgProperties &= ~4u;
    }
}

// 0x00093690 CBackgroundManager_HideAllBackgrounds_maybe
void CBackgroundManager::HideAllBackgrounds() {
    for (uint32_t i = 0; i < m_ui8NbRootNode; ++i) {
        CSGLeaf* root = static_cast<CSGLeaf*>(m_apRootNode[i]->m_pRootNode);
        if (root != nullptr) root->m_sgProperties |= 4;
    }
}
