// CKFlashAnimation.cpp - reconstructed original translation unit 0x73b10-0x74e30 (GAME_TOC1, main_toc1), 31 functions, 17 live.
// Primary class: CKFlashAnimation  key 0x78d  category Graphical  size 0x30  vtable 0xb16140
// Other owners: CKFlashAnimEntry (4)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x73b10  CKFlashAnimation_Delete
//   [ ] 0x73b60  CKFlashAnimation_Construct  [dead]
//   [ ] 0x73b80  KStub_Return1_73b80  [dead]
//   [ ] 0x73b88  CKFlashAnimation_Construct_2  [dead]
//   [ ] 0x73ba8  RegisterCKFlashAnimationClass
//   [ ] 0x73c20  _GLOBAL__I_73c20
//   [ ] 0x73c30  CKFlashAnimEntry_FormatLabel_maybe  [dead]
//   [ ] 0x73c68  CKFlashAnimEntry_Load_maybe  [dead]
//   [ ] 0x73d10  CKFlashAnimEntry_Construct_maybe  [dead]
//   [ ] 0x73d40  CKFlashAnimEntry_Construct_2_maybe  [dead]
//   [x] 0x73d70  CKFlashAnimation_PostLoad  (IKFlashObject's, inherited)
//   [x] 0x73d98  CKFlashAnimation_RecursiveRegistration
//   [x] 0x73e20  CKFlashAnimation_DeleteArray
//   [x] 0x73ec8  CKFlashAnimation_vf54  (Vf54)
//   [ ] 0x73f60  CKFlashAnimation_FindEntryById_maybe  [dead]
//   [x] 0x73fd0  CKFlashAnimation_ApplyColorMultiplier_maybe  (ApplyColorMultiplier)
//   [x] 0x74108  CKFlashAnimation_vf64  (RegisterObjects)
//   [ ] 0x741d8  CKFlashAnimation_SetInterpolate_maybe  [dead]
//   [ ] 0x74260  CKFlashAnimation_GetNumKeyFrameLists_maybe  [dead]
//   [ ] 0x742c0  CKFlashAnimation_GetPrevFrameIndex_maybe  [dead]
//   [ ] 0x74320  CKFlashAnimation_SetObjectsVisible_maybe  [dead]
//   [ ] 0x74420  CKFlashAnimation_GotoKeyFrameList_maybe  [dead]
//   [x] 0x74598  CKFlashAnimation_vf50  (GetRt2dObject)
//   [x] 0x74720  CKFlashAnimation_GetFirstOnScreenObjectPos_maybe  (GetScreenAnchor)
//   [x] 0x74920  CKFlashAnimation_CreateArray
//   [x] 0x749e8  CKFlashAnimation_Create
//   [ ] 0x74a38  CKFlashAnimation_Save
//   [ ] 0x74ab8  CKFlashAnimation_Destructor_2  [dead]
//   [x] 0x74b20  CKFlashAnimation_DeletingDestructor
//   [x] 0x74b90  CKFlashAnimation_Destructor
//   [x] 0x74bf8  CKFlashAnimation_Load
//
//   [x] 0x999128  CKFlashAnimation_IsKindOfClass  [inline]
//   [x] 0x999150  CKFlashAnimation_GetClassType  [inline]
//   [x] 0x999158  CKFlashAnimation_GetClassID  [inline]
//   [x] 0x999160  CKFlashAnimation_Destroy  [inline]
//   [ ] 0x9991b8  IKFlashMessage_vf50  [inline]
//   [ ] 0x9991c0  IKFlashMessage_vf60  [inline]
//   [ ] 0x9991c8  IKFlashMessage_vf64  [inline]
//   [ ] 0x9991d0  IKFlashMessage_vf68  [inline]
//   [ ] 0x9991d8  IKFlashMessage_vf8  [inline]
//   [ ] 0x999200  IKFlashMessage_vf14  [inline]
//   [ ] 0x999208  IKFlashMessage_vf18  [inline]
#include "k2000/graphical/animation/CKFlashAnimation.h"

#include <cstring>

#include "Renderware/rt2d/Rt2d.h"
#include "Renderware/rt2d/Rt2dTypes.h"
#include "Renderware/rt2danim/Rt2dAnim.h"
#include "k2000/graphical/ui/CKFlashUI.h"
#include "k2000/io/IKFile.h"
#include "k2000/logic/CKSavingManager.h"
#include "k2000/logic/CKSector.h"
#include "k2000/memory/Mem.h"
#include "k2000/misc/Engine.h"

// C2.8 port-rest R02. No game file holds a CKFlashAnimation; ported from the disassembly.

namespace {
CKFlashUI* FlashUI(const CKFlashAnimation* animation) { return reinterpret_cast<CKFlashUI*>(animation->m_pFlashUI); }

bool SectorLoaded(const CKFlashUI* ui) { return ui->m_pSector != nullptr && (ui->m_pSector->m_ba16Properties & 1) != 0; }

// An entry's animation scene: its string label (by index), whose entity word (+0x08, an index) names the scene.
Rt2dObject* EntryScene(const CKFlashAnimation* animation, const CKFlashAnimEntry& entry) {
    Rt2dMaestro* maestro = FlashUI(animation)->m_pMaestro;  // interface +0xec
    const Rt2dStringLabel* label = Rt2dMaestroGetStringLabelByIndex(maestro, entry.m_i32LabelIndex);
    const int32_t entity = static_cast<int32_t>(reinterpret_cast<intptr_t>(label->internalData));
    return Rt2dMaestroGetAnimSceneByIndex(FlashUI(animation)->m_pMaestro, entity);
}

// A new / reset entry: unbound (0xffff), no animation or props, byte 0xff.
void ResetEntry(CKFlashAnimEntry* entry) {
    entry->m_i32LabelIndex = 0xffff;
    entry->m_pAnim = nullptr;
    entry->m_pProps = nullptr;
    entry->m_unk08 = 0xff;
}
}  // namespace

// 0x000749e8 CKFlashAnimation_Create
CKFlashAnimation::CKFlashAnimation() {
    m_szLabelName = nullptr;
    m_ui32LabelId = 0;
    m_pFlashUI = nullptr;
    m_unk10 = 0;
    std::memset(m_unk14, 0, sizeof(m_unk14));
    m_vEntries.m_pBlock = nullptr;
    m_vEntries.m_ui32NbElt = 1;
    m_vEntries.m_ui32NbUsedElt = 0;
}

// 0x00074b90 CKFlashAnimation_Destructor
CKFlashAnimation::~CKFlashAnimation() {
    if (m_vEntries.m_pBlock != nullptr) Mem_FreeAligned16(m_vEntries.m_pBlock);
}

// 0x00999160 CKFlashAnimation_Destroy
void CKFlashAnimation::Destroy() {
    IKFlashObject::Destroy();  // 0x00077b88
    if (m_vEntries.m_pBlock != nullptr) Mem_FreeAligned16(m_vEntries.m_pBlock);
    m_vEntries.m_ui32NbUsedElt = 0;
    m_vEntries.m_pBlock = nullptr;
}

// 0x00073d98 CKFlashAnimation_RecursiveRegistration
void CKFlashAnimation::RecursiveRegistration(int32_t type) {
    IKFlashObject::RecursiveRegistration(type);  // 0x00077b78
    if (type == 0) g_pEngine->m_pSavingManager->RegisterSerializableObject(this, nullptr);  // vt+0x24
}

// 0x00074bf8 CKFlashAnimation_Load. The entry block is replaced without freeing the old one.
int32_t CKFlashAnimation::Load(IKFile* file, int32_t type) {
    IKFlashObject::Load(file, type);  // 0x00077958
    uint32_t count = 0;
    ReadU32LE(file, &count);
    m_vEntries.m_ui32NbElt = count;
    m_vEntries.m_pBlock = static_cast<CKFlashAnimEntry*>(
        Mem_AllocAligned16(count * static_cast<uint32_t>(sizeof(CKFlashAnimEntry))));  // PS3: (n x 0x110) & ~0xf
    for (uint32_t i = 0; i < count; ++i) {
        uint32_t used = m_vEntries.m_ui32NbUsedElt;
        if (m_vEntries.m_ui32NbElt == used) {
            uint32_t capacity = used + 1;
            if (capacity == 0) capacity = 1;
            m_vEntries.m_pBlock = static_cast<CKFlashAnimEntry*>(Mem_ReallocAligned16(
                m_vEntries.m_pBlock, capacity * static_cast<uint32_t>(sizeof(CKFlashAnimEntry))));
            m_vEntries.m_ui32NbElt = capacity;
            used = m_vEntries.m_ui32NbUsedElt;
        }
        CKFlashAnimEntry* entry = &m_vEntries.m_pBlock[used];
        ResetEntry(entry);
        entry->m_szLabelName[0] = '\0';
        m_vEntries.m_ui32NbUsedElt = used + 1;
        if (type != 0) continue;
        ReadRaw(file, &entry->m_unk08, 1);
        IKFile_ReadLengthPrefixedString(file, entry->m_szLabelName, -1);  // 0x0004d2f0
        entry->m_pProps = nullptr;  // the type word (0)
        entry->m_pAnim = nullptr;
    }
    return 1;
}

// 0x00074598 CKFlashAnimation_vf50. The vector grows by one element at a time.
void CKFlashAnimation::GetRt2dObject(TVector<Rt2dObject*, 1>* objects) {
    if (!SectorLoaded(FlashUI(this))) return;
    for (uint32_t i = 0; i < m_vEntries.m_ui32NbUsedElt; ++i) {
        Rt2dObject* scene = EntryScene(this, m_vEntries.m_pBlock[i]);
        if (objects->m_ui32NbElt == objects->m_ui32NbUsedElt) {
            uint32_t capacity = objects->m_ui32NbUsedElt + 1;
            if (capacity == 0) capacity = 1;
            objects->m_pBlock = static_cast<Rt2dObject**>(
                Mem_ReallocAligned16(objects->m_pBlock, capacity * static_cast<uint32_t>(sizeof(Rt2dObject*))));
            objects->m_ui32NbElt = capacity;
        }
        objects->m_pBlock[objects->m_ui32NbUsedElt] = scene;
        ++objects->m_ui32NbUsedElt;
    }
}

// 0x00073ec8 CKFlashAnimation_vf54
void CKFlashAnimation::Vf54() {
    IKFlashObject::Vf54();  // 0x00077838
    for (uint32_t i = m_vEntries.m_ui32NbUsedElt; i != 0;) {
        --i;
        ResetEntry(&m_vEntries.m_pBlock[i]);
    }
}

// 0x00074720 CKFlashAnimation_GetFirstOnScreenObjectPos_maybe (TOC -0x6cd4 -3, -0x6cd0 4; NaN positions skipped)
uint8_t CKFlashAnimation::GetScreenAnchor(CVector2* position, CVector2* size, uint8_t* /*rgba*/) {
    if (!SectorLoaded(FlashUI(this))) return 0;
    for (uint32_t i = 0; i < m_vEntries.m_ui32NbUsedElt; ++i) {
        Rt2dObject* scene = EntryScene(this, m_vEntries.m_pBlock[i]);
        if (FlashUI(this)->IsRt2dObjectVisible(scene) == 0) continue;  // 0x0006ecc0
        float movieWidth;
        float movieHeight;
        FlashUI(this)->GetMovieSize(&movieWidth, &movieHeight);  // 0x0006d7d8
        CVector2 anchor;
        GetNormalizedPosition(scene, &anchor);  // 0x00077bd0
        if (!(anchor.m_fX >= -3.0f) || !(anchor.m_fX <= 4.0f) || !(anchor.m_fY >= -3.0f) || !(anchor.m_fY <= 4.0f)) continue;
        if (position != nullptr) *position = anchor;
        if (size != nullptr) {
            const RwMatrix* ltm = Rt2dObjectGetLTM(scene);
            size->m_fY = ltm->up.y * movieHeight;
            size->m_fX = ltm->right.x * movieWidth;
        }
        return 1;
    }
    return 0;
}

// 0x00074108 CKFlashAnimation_vf64
void CKFlashAnimation::RegisterObjects() {
    for (uint32_t i = 0; i < m_vEntries.m_ui32NbUsedElt; ++i) {
        FlashUI(this)->SetRt2dObjectParent(EntryScene(this, m_vEntries.m_pBlock[i]), nullptr);  // 0x00070ac0
    }
}

// 0x00073fd0 CKFlashAnimation_ApplyColorMultiplier_maybe (TOC -0x6cd8 -1)
void CKFlashAnimation::ApplyColorMultiplier() {
    if (m_unk14[3] == -0x1p+0f) return;
    for (uint32_t i = m_vEntries.m_ui32NbUsedElt; i != 0;) {
        --i;
        Rt2dObject* scene = EntryScene(this, m_vEntries.m_pBlock[i]);
        if (FlashUI(this)->IsRt2dObjectVisible(scene) == 0) continue;
        Rt2dScene_ApplyColorMultiplierToChildren(FlashUI(this), scene, reinterpret_cast<RwRGBAReal*>(m_unk14));  // 0x6da18
    }
    m_unk14[3] = -0x1p+0f;
}
