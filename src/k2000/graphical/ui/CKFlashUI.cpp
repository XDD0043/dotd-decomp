// CKFlashUI.cpp - reconstructed original translation unit 0x6d460-0x722f8 (GAME_TOC1, main_toc1), 78 functions, 57 live.
// Primary class: CKFlashUI  key 0x6cd  category Graphical  size 0x23c  vtable 0xb16070
// Other owners: FlashUI (6), FlashWidgetBinding (4), Rt2dScene (2), Rt2dObject (1), FlashTextGroup (1), CameraContext (1), DrawFlashUISceneAndSynchronizeWidgets (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x6d460  CKFlashUI_Delete
//   [x] 0x6d4b0  CKFlashUI_MessageProc
//   [ ] 0x6d4b8  FUN_0006d4b8  [dead]
//   [x] 0x6d508  KStub_Nop_6d508
//   [x] 0x6d510  CKFlashUI_SetPaused_maybe
//   [ ] 0x6d528  FlashUI_FindMatchingAnimCB_maybe
//   [ ] 0x6d540  CKFlashUI_SendMessageInToObjects14_maybe  [dead]
//   [x] 0x6d5e0  CKFlashUI_ResetElements_maybe
//   [x] 0x6d7a0  CKFlashUI_GetScreenScaleAndRect_maybe
//   [x] 0x6d7d8  CKFlashUI_GetMovieSize_maybe
//   [ ] 0x6d7f0  CKFlashUI_SetColorMultiplier_maybe  [dead]
//   [ ] 0x6d808  CKFlashUI_SetAlphaMultiplier_maybe  [dead]
//   [x] 0x6d820  CKFlashUI_QueueMessageIn_maybe
//   [ ] 0x6d8b0  CKFlashUI_ClearQueuedMessagesIn_maybe  [dead]
//   [ ] 0x6d8c0  RegisterCKFlashUIType
//   [ ] 0x6d938  _GLOBAL__I_6d938
//   [ ] 0x6d948  CKFlashUI_FindWidgetBindingByElement2d_maybe  [dead]
//   [ ] 0x6da18  Rt2dScene_ApplyColorMultiplierToChildren_maybe
//   [ ] 0x6da50  Rt2dScene_ApplyColorMultiplierRGBA_maybe  [dead]
//   [x] 0x6daa0  CKFlashUI_IsSceneVisible_maybe
//   [x] 0x6db28  Rt2dObject_SetColorMultiplierRecursiveCB_maybe
//   [x] 0x6dbe8  CKFlashUI_ApplyFontsToTexts_maybe
//   [x] 0x6dc58  FlashTextGroup_RefreshAll_maybe
//   [x] 0x6dce0  CKFlashUI_SendMaestroMessage_maybe
//   [ ] 0x6dd60  FlashUI_TriggerMessageIn_maybe  [dead]
//   [x] 0x6dd88  FlashUI_AddMaestroMessageCB_maybe
//   [ ] 0x6dde8  FlashUI_GotoKeyFrameListCB_maybe  [dead]
//   [x] 0x6de28  FlashUI_SetAnimInterpolateCB_maybe
//   [ ] 0x6de68  FUN_0006de68  [dead]
//   [ ] 0x6de98  CKFlashUI_SetAllAnimationsInterpolate_maybe  [dead]
//   [x] 0x6ded0  CKFlashUI_SyncWidgetBindings_maybe
//   [x] 0x6df70  CKFlashUI_UpdateWidgetBindings_maybe
//   [x] 0x6dff0  CKFlashUI_HideLinkedWidgets_maybe
//   [x] 0x6e088  CKFlashUI_CollectNamedStrings_cb_maybe
//   [x] 0x6e230  CKFlashUI_DeleteArray
//   [ ] 0x6e2d0  CKFlashUI_Construct_2
//   [x] 0x6e3a8  FlashUI_ReapplyTextFonts_maybe
//   [x] 0x6e418  CKFlashUI_SetPlaying_maybe
//   [ ] 0x6e430  CKFlashUI_CopyTextIdToSameNamedTexts_maybe  [dead]
//   [x] 0x6e500  CameraContext_GetReferenceAspect_maybe
//   [x] 0x6e518  CKFlashUI_Save
//   [x] 0x6e520  CKFlashUI_RecursiveRegistration
//   [ ] 0x6e528  CKFlashUI_CallElementVf64AndIndexScene_maybe  [dead]
//   [x] 0x6e608  CKFlashUI_BindSceneObjects_maybe
//   [x] 0x6e820  CKFlashUI_Construct
//   [x] 0x6e8f8  CKFlashUI_ApplyFontsToTexts_2_maybe
//   [ ] 0x6e968  CKFlashUI_FlushQueuedMessagesIn_maybe  [dead]
//   [x] 0x6ea78  CKFlashUI_UpdateScreenTransform_maybe
//   [x] 0x6ec78  CKFlashUI_RefreshSceneLTM_maybe
//   [x] 0x6ecc0  CKFlashUI_IsObjectVisible_maybe
//   [x] 0x6edc8  CKFlashUI_Create
//   [x] 0x6eeb0  CKFlashUI_CreateArray
//   [x] 0x6f030  CKFlashUI_Destroy
//   [x] 0x6f280  DrawFlashUISceneAndSynchronizeWidgets
//   [x] 0x6f3d0  CKFlashUI_SetHidden_maybe
//   [ ] 0x6f4a0  CKFlashUI_GetElement2dFlagBit0_maybe  [dead]
//   [ ] 0x6f5c8  CKFlashUI_SetElement2dFlags_maybe  [dead]
//   [x] 0x6f6e0  CKFlashUI_Show_maybe
//   [x] 0x6f8b0  CKFlashUI_Hide_maybe
//   [x] 0x6f9e8  CKFlashUI_ProcessMaestroMessagesAndNotifyElements_maybe
//   [ ] 0x6fb30  CKFlashUI_DispatchButtonMessages_maybe  [dead]
//   [x] 0x6fc48  CKFlashUI_Load
//   [x] 0x70478  CKFlashUI_DeletingDestructor
//   [x] 0x705b8  CKFlashUI_Destructor
//   [ ] 0x706f0  CKFlashUI_Destructor_2_maybe
//   [ ] 0x70828  FUN_00070828  [dead]
//   [x] 0x70ac0  CKFlashUI_RegisterObjectOwnerInHashTable_maybe
//   [x] 0x70cc0  CKFlashUI_RefreshVisibilityCache_maybe
//   [x] 0x71040  CKFlashUI_Update_maybe
//   [x] 0x71470  CKFlashUI_IndexSceneObject_cb_maybe
//   [x] 0x71720  CKFlashUI_ResolveElementsAndIndexScene_maybe
//   [x] 0x71f48  CKFlashUI_PostLoad
//   [ ] 0x72088  CFlashHotSpot_Delete
//   [ ] 0x720d8  FlashWidgetBinding_FindElement2dIndex_maybe  [dead]
//   [ ] 0x72130  FlashWidgetBinding_FindAtomicIndex_maybe  [dead]
//   [x] 0x72198  FlashWidgetBinding_UpdateAnchor_maybe
//   [ ] 0x72208  FUN_00072208  [dead]
//   [x] 0x722e8  FlashWidgetBinding_IsAnchorUnresolved_maybe
//
//   [x] 0x998ce0  CKFlashUI_GetClassType  [inline]
//   [x] 0x998ce8  CKFlashUI_GetClassID  [inline]
//   [x] 0x998cf0  KStub_Nop_998cf0  [inline]
//   [x] 0x998d50  HashTableU32_Destructor_5  [inline]
//   [x] 0x998e70  CKFlashUI_IsKindOfClass  [inline]
//   [ ] 0x998e90  HashTableU32_DeletingDestructor_5  [inline]
#include "k2000/graphical/ui/CKFlashUI.h"

#include <cstring>

#include "Renderware/rt2d/Rt2d.h"
#include "Renderware/rt2danim/Rt2dAnim.h"
#include "Renderware/rwcore/RwStream.h"
#include "crt/ppc_ops.h"
#include "k2000/geometry/CGeometry.h"
#include "k2000/graphical/ui/CFlashHotSpot.h"
#include "k2000/graphical/ui/CKFlashManager.h"
#include "k2000/graphical/ui/CKFlashMessageIn.h"
#include "k2000/graphical/ui/CKFlashText.h"
#include "k2000/graphical/ui/CameraContextUi.h"
#include "k2000/input/CKInputDico.h"
#include "k2000/io/IKFile.h"
#include "k2000/logic/CKSector.h"
#include "k2000/memory/Mem.h"
#include "k2000/misc/Engine.h"
#include "k2000/system/IKTime.h"
#include "k2000/ui/IKFlashObject.h"

namespace {

IKFlashObject* AsFlashObject(IKSerializable* object) { return static_cast<IKFlashObject*>(object); }
CKFlashText* AsText(IKSerializable* object) { return static_cast<CKFlashText*>(object); }
CFlashHotSpot* AsHotSpot(IKSerializable* object) { return static_cast<CFlashHotSpot*>(object); }

// The interface runs only while its sector is loaded (CKSector +0x06 bit 0); inlined everywhere.
bool SectorLoaded(const CKFlashUI* ui) {
    return ui->m_pSector != nullptr && (ui->m_pSector->m_ba16Properties & 1) != 0;
}

// 0x00960160 strcasecmp (libc, C locale: the ctype table marks A-Z only as upper case).
int32_t Ps3StrCaseCmp(const char* a, const char* b) {
    for (;;) {
        const uint32_t ca = static_cast<uint8_t>(*a++);
        const uint32_t cb = static_cast<uint8_t>(*b++);
        const uint32_t la = (ca >= 'A' && ca <= 'Z') ? ca + 0x20 : ca;
        const uint32_t lb = (cb >= 'A' && cb <= 'Z') ? cb + 0x20 : cb;
        if (la != lb) return lb <= la ? 1 : -1;
        if (ca == 0) return 0;
    }
}

// The local vector ResolveElementsAndIndexScene hands to GetRt2dObject (one element allocated).
void InitObjectVector(TVector<Rt2dObject*, 1>* objects) {
    objects->m_ui32NbElt = 1;
    objects->m_pBlock = static_cast<Rt2dObject**>(Mem_AllocAligned16(static_cast<uint32_t>(sizeof(Rt2dObject*))));
}

// The part ResolveElementsAndIndexScene repeats per flash object: its objects into the map (not visible,
// no parent), then the vector freed and cleared.
void AddObjectsToMap(CKFlashUI* ui, IKFlashObject* object, TVector<Rt2dObject*, 1>* objects) {
    InitObjectVector(objects);
    object->GetRt2dObject(objects);
    for (uint32_t i = 0; i < objects->m_ui32NbUsedElt; ++i) ui->m_mMap.SetAt(objects->m_pBlock[i], CRt2dObjectInfos{0, nullptr});
    if (objects->m_pBlock != nullptr) Mem_FreeAligned16(objects->m_pBlock);
    objects->m_pBlock = nullptr;
    objects->m_ui32NbUsedElt = 0;
}

// 0x00071470 CKFlashUI_IndexSceneObject_cb_maybe: every scene object already in the map gets its parent
// (keeping its visibility); scenes are walked down.
Rt2dObject* IndexSceneObjectCB(Rt2dObject* object, Rt2dObject* parent, void* data) {
    CKFlashUI* ui = static_cast<CKFlashUI*>(data);
    CKFlashUI_ObjectInfosItem* item = ui->m_mMap.GetPtrToAssoc(object);
    if (item != nullptr) ui->m_mMap.SetAt(object, CRt2dObjectInfos{item->m_val.m_bIsVisible, parent});
    if (Rt2dObjectIsScene(object) != 0) Rt2dSceneForAllChildren(object, IndexSceneObjectCB, data);
    return object;
}

// 0x0006e088 CKFlashUI_CollectNamedStrings_cb_maybe: every object string whose text is a flash text's
// label (strcasecmp) is appended to that text's objects (the vector grows by 2); scenes are walked down.
Rt2dObject* CollectNamedStringsCB(Rt2dObject* object, Rt2dObject* /*parent*/, void* data) {
    CKFlashUI* ui = static_cast<CKFlashUI*>(data);
    if (Rt2dObjectIsScene(object) != 0) {
        Rt2dSceneForAllChildren(object, CollectNamedStringsCB, data);
        return object;
    }
    if (Rt2dObjectIsObjectString(object) == 0) return object;
    const RwChar* text = Rt2dObjectStringGetText(object);
    for (uint32_t i = 0; i < ui->m_ui32FlashTextNb; ++i) {
        CKFlashText* flashText = AsText(ui->m_apFlashText[i]);
        if (Ps3StrCaseCmp(text, flashText->m_szLabelName) != 0) continue;
        TVector<Rt2dObject*, 2>& objects = flashText->m_vpObject;
        if (objects.m_ui32NbElt == objects.m_ui32NbUsedElt) {
            uint32_t capacity = objects.m_ui32NbElt + 2;
            if (capacity == 0) capacity = 2;
            objects.m_pBlock = static_cast<Rt2dObject**>(
                Mem_ReallocAligned16(objects.m_pBlock, capacity * static_cast<uint32_t>(sizeof(Rt2dObject*))));
            objects.m_ui32NbElt = capacity;
        }
        objects.m_pBlock[objects.m_ui32NbUsedElt] = object;
        ++objects.m_ui32NbUsedElt;
        return object;
    }
    return object;
}

// 0x0006de28 FlashUI_SetAnimInterpolateCB_maybe (XXL2 ActivateAllAnimInterpolation)
Rt2dMaestro* SetAnimInterpolateCB(Rt2dMaestro* maestro, Rt2dAnim* anim, Rt2dAnimProps* /*props*/, void* data) {
    Rt2dAnimSetInterpolate(anim, *static_cast<uint8_t*>(data));
    return maestro;
}

// 0x0006dd88 FlashUI_AddMaestroMessageCB_maybe (XXL2 PostButtonMessage): a button-by-label message
// (type 13) for the label id in data, state 0x80, posted to the maestro.
Rt2dMaestro* PostButtonMessageCB(Rt2dMaestro* maestro, Rt2dAnim* /*anim*/, Rt2dAnimProps* /*props*/, void* data) {
    Rt2dMessage message;
    message.messageType = rt2dMESSAGETYPEBUTTONBYLABEL;
    message.index = -1;
    message.intParam1 = *static_cast<int32_t*>(data);
    message.intParam2 = 0x80;
    Rt2dMaestroPostMessages(maestro, &message, 1);  // 0x6ffe80 Rt2dMaestroAddMessages
    return maestro;
}

// 0x0006db28 Rt2dObject_SetColorMultiplierRecursiveCB_maybe: the colour (data +4) on every string and
// shape, scenes walked down.
struct ColorMultiplierData {
    CKFlashUI* ui;          // +0x00
    RwRGBAReal* multiply;   // +0x04
};
Rt2dObject* SetColorMultiplierCB(Rt2dObject* object, Rt2dObject* /*parent*/, void* data) {
    RwRGBAReal* multiply = static_cast<ColorMultiplierData*>(data)->multiply;
    if (Rt2dObjectIsObjectString(object) != 0) Rt2dObjectSetColorMultiplier(object, multiply);
    if (Rt2dObjectIsShape(object) != 0) Rt2dObjectSetColorMultiplier(object, multiply);
    if (Rt2dObjectIsScene(object) != 0) Rt2dSceneForAllChildren(object, SetColorMultiplierCB, data);
    return object;
}

}  // namespace

// --- the object map (TMap<Rt2dObject*, CRt2dObjectInfos>) --------------------------------------------

// 0x00998d50 HashTableU32_Destructor_5 (XXL2 ~TMap: RemoveAll, then the bucket array)
CKFlashUI_ObjectInfosMap::~CKFlashUI_ObjectInfosMap() {
    for (uint32_t b = 0; b < m_ui32HashSize; ++b) {
        while (m_ppHashTable[b] != nullptr) {
            CKFlashUI_ObjectInfosItem* item = m_ppHashTable[b];
            m_ppHashTable[b] = item->m_pNext;
            ClearValue(item);
            delete item;
        }
    }
    m_ui32Count = 0;
    if (m_ppHashTable != nullptr) delete[] m_ppHashTable;
}

// 0x00998cf8 HashTableU32_HashKey_5
uint32_t CKFlashUI_ObjectInfosMap::KeyToHashIndex(Rt2dObject* key) const {
    const uintptr_t k = reinterpret_cast<uintptr_t>(key);
    return static_cast<uint32_t>(k % m_ui32HashSize);
}

CKFlashUI_ObjectInfosItem* CKFlashUI_ObjectInfosMap::GetPtrToAssoc(Rt2dObject* key) const {
    for (CKFlashUI_ObjectInfosItem* item = m_ppHashTable[KeyToHashIndex(key)]; item != nullptr; item = item->m_pNext)
        if (IsKeysEqual(key, item->m_key) != 0) return item;
    return nullptr;
}

void CKFlashUI_ObjectInfosMap::SetAt(Rt2dObject* key, CRt2dObjectInfos value) {
    const uint32_t index = KeyToHashIndex(key);
    for (CKFlashUI_ObjectInfosItem* item = m_ppHashTable[index]; item != nullptr; item = item->m_pNext) {
        if (IsKeysEqual(key, item->m_key) != 0) {
            ClearValue(item);
            SetValue(item, key, value);
            return;
        }
    }
    CKFlashUI_ObjectInfosItem* item = new CKFlashUI_ObjectInfosItem;  // OperatorNew(0x10)
    SetValue(item, key, value);
    item->m_pNext = m_ppHashTable[index];
    m_ppHashTable[index] = item;
    ++m_ui32Count;
}

// --- CKFlashUI -----------------------------------------------------------------------------------------

// 0x0006e820 CKFlashUI_Construct: the map (its vtable, 37 zeroed buckets), then the fields it clears.
CKFlashUI::CKFlashUI() {
    m_mMap.m_ui32HashSize = 0x25;
    m_mMap.m_ui32Count = 0;
    m_mMap.m_ppHashTable = new CKFlashUI_ObjectInfosItem*[0x25];  // OperatorNewArray(0x94)
    std::memset(m_mMap.m_ppHashTable, 0, m_mMap.m_ui32HashSize * sizeof(CKFlashUI_ObjectInfosItem*));
    m_ui32HotSpotNb = 0;
    m_fOffsetX_maybe = 0.0f;
    m_ui32Unk22c = 0xffffffffu;
    m_ui32FlashMessageInQueuedNb = 0;
    m_baFlags = 0;
    m_pMaestro = nullptr;
    m_pSector = nullptr;
    m_apFlashAnimation = nullptr;
    m_apFlashText = nullptr;
    m_apFlashMessageIn = nullptr;
    m_apFlashMessageOut = nullptr;
    m_apObjectsToWarn = nullptr;
    m_apHotSpot = nullptr;
    m_ui32FlashAnimNb = 0;
    m_ui32FlashMessageInNb = 0;
    m_ui32FlashMessageOutNb = 0;
    m_ui32FlashObjectToWarnNb = 0;
    m_ui32FlashTextNb = 0;
}

namespace {

// The count + Mem_AllocAligned16(count * 4) + reference array the Load inlines for each table.
void ReadRefTable(IKFile* file, uint32_t* count, IKSerializable*** table) {
    ReadU32LE(file, count);
    if (*count == 0) {
        *table = nullptr;
        return;
    }
    *table = static_cast<IKSerializable**>(Mem_AllocAligned16(*count * static_cast<uint32_t>(sizeof(IKSerializable*))));
    IKFile_ReadObjectRefArray(file, *table, *count);
}

}  // namespace

// 0x0006fc48 CKFlashUI_Load
int32_t CKFlashUI::Load(IKFile* file, int32_t type) {
    if (type != K_LEVEL_PLATEFORMS) return 1;
    ReadRefTable(file, &m_ui32FlashAnimNb, &m_apFlashAnimation);
    ReadRefTable(file, &m_ui32FlashTextNb, &m_apFlashText);
    ReadRefTable(file, &m_ui32FlashMessageInNb, &m_apFlashMessageIn);
    ReadRefTable(file, &m_ui32FlashMessageOutNb, &m_apFlashMessageOut);
    ReadRefTable(file, &m_ui32FlashObjectToWarnNb, &m_apObjectsToWarn);
    IKFile_ReadRef(file, &m_pSoundDico);
    ReadU32LE(file, &m_baFlags);
    m_baFlags &= ~kNeverRender;  // rlwinm 26,1,31 + rlwinm 6 (XXL2: and 0xdf)
    ReadRefTable(file, &m_ui32HotSpotNb, &m_apHotSpot);
    ReadU32LEWords(file, reinterpret_cast<uint32_t*>(m_ai32InputLabelId), 40);
    ReadS32LE(file, &m_i32RestartInterfaceButton);
    IKFile_ReadRef(file, &m_pUnk218);
    uint32_t length = 0, version = 0;
    if (RwStreamFindChunk(file->m_pRwStream, 0x1b1, &length, &version) != 0)
        m_pMaestro = Rt2dMaestroStreamRead(nullptr, file->m_pRwStream);
    ReadU32LE(file, &m_ui32Unk22c);
    IKFile_ReadRef(file, &m_pSector);
    ReadU32LE(file, &m_ui32Alignment_maybe);
    return 1;
}

Rt2dObject* CKFlashUI::GetMaestroScene() { return m_pMaestro != nullptr ? Rt2dMaestroGetScene(m_pMaestro) : nullptr; }

// 0x0006e608 CKFlashUI_BindSceneObjects_maybe (XXL2 CheckAndInitializeAllFlashObjects): the label ids of
// the messages (in: URL labels, type 6; out: button labels, type 3) and the texts' string objects.
// STUB(C1.6): CKFlashAnimation (0x78d) is not ported and no front-end interface has one; the original
// first binds each animation instance (its +0x24 array, 0x110 bytes each, count +0x2c) to its anim label
// (type 1): Rt2dMaestroFindStringLabel, Rt2dMaestroGetAnimationsByIndex, then
// Rt2dMaestroForAllAnimations(0x6d528 FlashUI_FindMatchingAnimCB_maybe) for its props.
void CKFlashUI::BindSceneObjects() {
    for (uint32_t i = 0; i < m_ui32FlashMessageInNb; ++i) {
        IKFlashObject* message = AsFlashObject(m_apFlashMessageIn[i]);
        RwInt32 index = 0;
        if (Rt2dMaestroFindStringLabel(m_pMaestro, rt2dANIMLABELTYPEURL, message->m_szLabelName, &index) != nullptr)
            message->m_ui32LabelId = static_cast<uint32_t>(index);
    }
    for (uint32_t i = 0; i < m_ui32FlashMessageOutNb; ++i) {
        IKFlashObject* message = AsFlashObject(m_apFlashMessageOut[i]);
        RwInt32 index = 0;
        if (Rt2dMaestroFindStringLabel(m_pMaestro, rt2dANIMLABELTYPEBUTTON, message->m_szLabelName, &index) != nullptr)
            message->m_ui32LabelId = static_cast<uint32_t>(index);
    }
    CollectNamedStringsCB(Rt2dMaestroGetScene(m_pMaestro), nullptr, this);
}

// 0x00071720 CKFlashUI_ResolveElementsAndIndexScene_maybe (XXL2 CreateRt2dObjectMapFromAllObjects): the
// objects of the texts and animations (those with IKFlashObject +0x10 bit 0) and of the hot spots' flash
// objects into the map, then the scene walked to give them their parents.
void CKFlashUI::CreateRt2dObjectMapFromAllObjects() {
    TVector<Rt2dObject*, 1> objects;
    objects.m_pBlock = nullptr;
    objects.m_ui32NbElt = 1;
    objects.m_ui32NbUsedElt = 0;
    for (uint32_t i = 0; i < m_ui32FlashTextNb; ++i) {
        IKFlashObject* text = AsFlashObject(m_apFlashText[i]);
        if ((text->m_unk10 & 1) != 0) AddObjectsToMap(this, text, &objects);
    }
    for (uint32_t i = 0; i < m_ui32FlashAnimNb; ++i) {
        IKFlashObject* anim = AsFlashObject(m_apFlashAnimation[i]);
        if ((anim->m_unk10 & 1) != 0) AddObjectsToMap(this, anim, &objects);
    }
    for (uint32_t i = 0; i < m_ui32HotSpotNb; ++i) AddObjectsToMap(this, AsHotSpot(m_apHotSpot[i])->m_pFlashHotSpot, &objects);
    Rt2dSceneForAllChildren(GetMaestroScene(), IndexSceneObjectCB, this);
    if (objects.m_pBlock != nullptr) Mem_FreeAligned16(objects.m_pBlock);
}

// 0x00071f48 CKFlashUI_PostLoad: the flash objects bound, the object map built, the fonts applied (when
// +0x22c is set), the message handler installed, the movie placed on screen, its LTMs updated, every
// animation set to interpolate; the interface stopped.
int32_t CKFlashUI::PostLoad(int32_t type) {
    if (type != K_LEVEL_PLATEFORMS) return 1;
    BindSceneObjects();
    CreateRt2dObjectMapFromAllObjects();
    if (m_ui32Unk22c != 0) {
        for (uint32_t i = 0; i < m_ui32FlashTextNb; ++i) AsText(m_apFlashText[i])->ReloadFont();
    }
    Rt2dMaestroSetMessageHandler(m_pMaestro, CKFlashManager::HandleMaestroEvent);  // TOC1 -0x6d58 -> 0x6d180
    InitializeMaestroScenePosition();
    // PORT: under the render lock. Rt2dSceneUpdateLTM pushes onto the process-wide Rt2d CTM stack, which the
    // main thread's 2D drawing (the system message overlay of the loading frames, CManager2d::RenderMsgBox)
    // uses at the same time while this runs on the loader thread; the original has the same unguarded race.
    RenderLock_Lock();
    Rt2dSceneUpdateLTM(Rt2dMaestroGetScene(m_pMaestro));
    RenderLock_Unlock();
    uint8_t interpolate = 1;  // XXL2 stores Bool 1; the PS3 passes its stack byte the same way
    Rt2dMaestroForAllAnimations(m_pMaestro, SetAnimInterpolateCB, &interpolate);  // TOC1 -0x6d88 -> 0x6de28
    m_baFlags &= ~kStateMask;
    return 1;
}

// 0x0006f030 CKFlashUI_Destroy
void CKFlashUI::Destroy() {
    m_fOffsetX_maybe = 0.0f;
    ResetElements();
    if (m_apFlashAnimation != nullptr) {
        Mem_FreeAligned16(m_apFlashAnimation);
        m_apFlashAnimation = nullptr;
    }
    if (m_apFlashText != nullptr) {
        Mem_FreeAligned16(m_apFlashText);
        m_apFlashText = nullptr;
    }
    if (m_apFlashMessageIn != nullptr) {
        Mem_FreeAligned16(m_apFlashMessageIn);
        m_apFlashMessageIn = nullptr;
    }
    if (m_apFlashMessageOut != nullptr) {
        Mem_FreeAligned16(m_apFlashMessageOut);
        m_apFlashMessageOut = nullptr;
    }
    if (m_apObjectsToWarn != nullptr) {
        Mem_FreeAligned16(m_apObjectsToWarn);
        m_apObjectsToWarn = nullptr;
    }
    if (m_apHotSpot != nullptr) {
        Mem_FreeAligned16(m_apHotSpot);
        m_apHotSpot = nullptr;
    }
    m_ui32HotSpotNb = 0;
    m_ui32FlashAnimNb = 0;
    m_ui32FlashMessageInNb = 0;
    m_ui32FlashMessageOutNb = 0;
    m_ui32FlashObjectToWarnNb = 0;
    m_ui32FlashTextNb = 0;
    // XXL2 TMap::RemoveAll
    for (uint32_t b = 0; b < m_mMap.m_ui32HashSize; ++b) {
        while (m_mMap.m_ppHashTable[b] != nullptr) {
            CKFlashUI_ObjectInfosItem* item = m_mMap.m_ppHashTable[b];
            m_mMap.m_ppHashTable[b] = item->m_pNext;
            m_mMap.ClearValue(item);
            delete item;
        }
    }
    m_mMap.m_ui32Count = 0;
    m_i32RestartInterfaceButton = -1;
    m_pUnk218 = nullptr;
    m_pSoundDico = nullptr;
    for (int32_t i = 39; i >= 0; --i) m_ai32InputLabelId[i] = -1;  // from +0xe4 down
    if (m_pMaestro != nullptr) {
        Rt2dMaestroDestroy(m_pMaestro);
        m_pMaestro = nullptr;
    }
    m_ui32Unk22c = 0xffffffffu;
    m_pSector = nullptr;
}

// 0x0006d5e0 CKFlashUI_ResetElements_maybe: vt+0x54 of every animation, message in, message out and text,
// each list from the last one.
void CKFlashUI::ResetElements() {
    for (uint32_t i = m_ui32FlashAnimNb; i != 0;) AsFlashObject(m_apFlashAnimation[--i])->Vf54();
    for (uint32_t i = m_ui32FlashMessageInNb; i != 0;) AsFlashObject(m_apFlashMessageIn[--i])->Vf54();
    for (uint32_t i = m_ui32FlashMessageOutNb; i != 0;) AsFlashObject(m_apFlashMessageOut[--i])->Vf54();
    for (uint32_t i = m_ui32FlashTextNb; i != 0;) AsFlashObject(m_apFlashText[--i])->Vf54();
}

// 0x0006d510 CKFlashUI_SetPaused_maybe (XXL2 PauseInterface)
void CKFlashUI::PauseInterface() { m_baFlags = (m_baFlags & ~kStateMask) | 1; }

// 0x0006e418 CKFlashUI_SetPlaying_maybe (XXL2 ResumeInterface)
void CKFlashUI::ResumeInterface() { m_baFlags = (m_baFlags & ~kStateMask) | 2; }

// 0x0006d7a0 CKFlashUI_GetScreenScaleAndRect_maybe (XXL2 GetMaestroScaleWidthAndHeight)
void CKFlashUI::GetMaestroScaleWidthAndHeight(float* scaledWidth, float* scaledHeight, Rt2dBBox* bbox) const {
    *scaledHeight = m_fScaledHeight;
    *scaledWidth = m_fScaledWidth;
    bbox->x = m_MaestroBbox.x;
    bbox->y = m_MaestroBbox.y;
    bbox->w = m_MaestroBbox.w;
    bbox->h = m_MaestroBbox.h;
}

// 0x0006d7d8 CKFlashUI_GetMovieSize_maybe
void CKFlashUI::GetMovieSize(float* width, float* height) const {
    *width = m_fMovieWidth_maybe;
    *height = m_fMovieHeight_maybe;
}

// 0x0006d820 CKFlashUI_QueueMessageIn_maybe (XXL2 TranslateMessageIn): the message in whose label id is
// labelId goes to the queue that Update processes.
// BUG(original): the queue (64 entries) is not bounds-checked.
void CKFlashUI::TranslateMessageIn(int32_t labelId) {
    for (uint32_t i = 0; i < m_ui32FlashMessageInNb; ++i) {
        CKFlashMessageIn* message = static_cast<CKFlashMessageIn*>(m_apFlashMessageIn[i]);
        if (static_cast<int32_t>(message->m_ui32LabelId) == labelId) {
            m_vpFlashMessageIn[m_ui32FlashMessageInQueuedNb++] = message;
            return;
        }
    }
}

// 0x0006daa0 CKFlashUI_IsSceneVisible_maybe (XXL2 IsInterfaceVisible)
uint8_t CKFlashUI::IsInterfaceVisible() {
    if (!SectorLoaded(this)) return 0;
    return Rt2dObjectIsVisible(Rt2dMaestroGetScene(m_pMaestro)) != 0 ? 1 : 0;
}

// 0x0006dbe8 CKFlashUI_ApplyFontsToTexts_maybe
void CKFlashUI::ApplyFontsToTexts() {
    for (uint32_t i = 0; i < m_ui32FlashTextNb; ++i) AsText(m_apFlashText[i])->ReloadFont();
}

// 0x0006dc58 FlashTextGroup_RefreshAll_maybe (XXL2 RefreshTexts)
void CKFlashUI::RefreshTexts() {
    for (uint32_t i = 0; i < m_ui32FlashTextNb; ++i) {
        CKFlashText* text = AsText(m_apFlashText[i]);
        text->RefreshText();
        text->ApplyTextAlignment();
    }
}

// 0x0006dce0 CKFlashUI_SendMaestroMessage_maybe (XXL2 PostMessage): a button message for labelId to the
// visible animations, processed at once.
void CKFlashUI::PostMessage(int32_t labelId) {
    if (!SectorLoaded(this)) return;
    Rt2dMaestroForAllVisibleAnimations(m_pMaestro, PostButtonMessageCB, &labelId);  // TOC1 -0x6d90
    Rt2dMaestroProcessMessages(m_pMaestro);
}

// 0x0006ded0 CKFlashUI_SyncWidgetBindings_maybe
void CKFlashUI::SyncHotSpotAttachedObjects() {
    for (uint32_t i = 0; i < m_ui32HotSpotNb; ++i) AsHotSpot(m_apHotSpot[i])->Update3dAttachedObject(this);
    m_baFlags &= ~kHotSpotsHidden;
}

// 0x0006df70 CKFlashUI_UpdateWidgetBindings_maybe (XXL2 UpdateHotSpot)
void CKFlashUI::UpdateHotSpots() {
    for (uint32_t i = 0; i < m_ui32HotSpotNb; ++i) {
        CFlashHotSpot* hotSpot = AsHotSpot(m_apHotSpot[i]);
        hotSpot->UpdateAnchor();
        hotSpot->Update2dAttachedObject();
    }
}

// 0x0006dff0 CKFlashUI_HideLinkedWidgets_maybe (XXL2 HideAllHotSpotHierarchy)
void CKFlashUI::HideAllHotSpotHierarchy() {
    for (uint32_t i = 0; i < m_ui32HotSpotNb; ++i) AsHotSpot(m_apHotSpot[i])->HideHotSpotHierarchy(1);
    m_baFlags = (m_baFlags & ~kHotSpotsHidden) | kHotSpotsHidden;
}

// 0x0006e3a8 FlashUI_ReapplyTextFonts_maybe
void CKFlashUI::ReloadTextFonts() {
    for (uint32_t i = 0; i < m_ui32FlashTextNb; ++i) AsText(m_apFlashText[i])->ReloadFont();
}

// 0x0006e8f8 CKFlashUI_ApplyFontsToTexts_2_maybe
void CKFlashUI::ApplyFontsToTexts2() {
    for (uint32_t i = 0; i < m_ui32FlashTextNb; ++i) AsText(m_apFlashText[i])->ReloadFont();
}

// 0x0006e500 CameraContext_GetReferenceAspect_maybe: engine camera context +0x80.
float CameraContext_GetReferenceAspect() { return CameraContext_GetReferenceAspectValue(); }

// 0x0006ea78 CKFlashUI_UpdateScreenTransform_maybe (XXL2 InitializeMaestroScenePosition): the movie
// scaled to the screen height and placed by the alignment (+0x234); the texts refreshed. Under the render
// lock, inside a CTM push.
void CKFlashUI::InitializeMaestroScenePosition() {
    if (m_pMaestro == nullptr) return;
    RenderLock_Lock();  // sys_lwmutex_lock(0x00cf9c90, 0)
    Rt2dCTMPush();
    const float aspect = CameraContext_GetDisplayAspect();  // engine camera context +0x88
    Rt2dObject* scene = Rt2dMaestroGetScene(m_pMaestro);
    const Rt2dBBox* bbox = Rt2dMaestroGetBBox(m_pMaestro);
    RwV2d xstep, ystep, origin;
    Rt2dDeviceGetStep(&xstep, &ystep, &origin);  // the results are not used
    const float one = 0x1p+0f;   // TOC1 -0x6db8
    const float half = 0x1p-1f;  // TOC1 -0x6d68
    const float ratio = bbox->w / bbox->h;
    m_fScaledHeight = one / bbox->h;
    m_fMovieHeight_maybe = one / m_fScaledHeight;
    m_fScaledWidth = ratio / bbox->w;
    m_fMovieWidth_maybe = one / m_fScaledWidth;
    const float height = bbox->h;
    float offsetX = ppc::fmsubs(aspect, height, bbox->w) * half;
    m_fOffsetX_maybe = offsetX;
    if (m_ui32Alignment_maybe != 1) {
        if (m_ui32Alignment_maybe == 2) {
            offsetX = offsetX + offsetX;
        } else if (m_ui32Alignment_maybe == 0) {
            offsetX = 0.0f;  // TOC1 -0x6dbc
        }
    }
    Rt2dObjectMTMSetIdentity(scene);
    Rt2dObjectMTMScale(scene, m_fScaledWidth, m_fScaledHeight);
    Rt2dObjectMTMTranslate(scene, offsetX, height);
    Rt2dCTMSetIdentity();
    m_MaestroBbox.h = one;
    m_MaestroBbox.w = ratio;
    m_MaestroBbox.y = 0.0f;
    m_MaestroBbox.x = 0.0f;
    for (uint32_t i = 0; i < m_ui32FlashTextNb; ++i) {
        CKFlashText* text = AsText(m_apFlashText[i]);
        text->RefreshText();
        text->ApplyTextAlignment();
    }
    Rt2dCTMPop();
    RenderLock_Unlock();
}

// 0x0006ec78 CKFlashUI_RefreshSceneLTM_maybe
void CKFlashUI::RefreshSceneLTM() {
    InitializeMaestroScenePosition();
    Rt2dSceneUpdateLTM(Rt2dMaestroGetScene(m_pMaestro));
}

// 0x0006ecc0 CKFlashUI_IsObjectVisible_maybe (XXL2 IsRt2dObjectVisible): the cached visibility; 0 for
// an object not in the map.
uint8_t CKFlashUI::IsRt2dObjectVisible(Rt2dObject* object) {
    CKFlashUI_ObjectInfosItem* item = m_mMap.GetPtrToAssoc(object);
    return item != nullptr ? item->m_val.m_bIsVisible : 0;
}

// 0x00070ac0 CKFlashUI_RegisterObjectOwnerInHashTable_maybe
void CKFlashUI::SetRt2dObjectParent(Rt2dObject* object, Rt2dObject* parent) {
    m_mMap.SetAt(object, CRt2dObjectInfos{0, parent});
}

// 0x00070cc0 CKFlashUI_RefreshVisibilityCache_maybe (XXL2 UpdateRt2dObjectInfo): every map entry's
// visibility = the object's and its parent's (Rt2dObjectIsVisible), in the map's order.
void CKFlashUI::UpdateRt2dObjectInfo() {
    for (uint32_t b = 0; b < m_mMap.m_ui32HashSize; ++b) {
        for (CKFlashUI_ObjectInfosItem* item = m_mMap.m_ppHashTable[b]; item != nullptr;) {
            CKFlashUI_ObjectInfosItem* next = item->m_pNext;  // fetched before the update, as XXL2's GetNext
            Rt2dObject* key = item->m_key;
            Rt2dObject* parent = item->m_val.m_pParent;
            uint8_t visible = 0;
            if (Rt2dObjectIsVisible(key) != 0 && (parent == nullptr || Rt2dObjectIsVisible(parent) != 0)) visible = 1;
            m_mMap.SetAt(key, CRt2dObjectInfos{visible, parent});
            item = next;
        }
    }
}

// 0x0006f280 DrawFlashUISceneAndSynchronizeWidgets (XXL2 Render): the movie drawn when the sector is
// loaded, the scene visible and the interface not kNeverRender; then the hot spots follow their anchors.
// Otherwise the hot spots are hidden.
void CKFlashUI::Render(IKTime* /*time*/) {
    if (SectorLoaded(this) && Rt2dObjectIsVisible(Rt2dMaestroGetScene(m_pMaestro)) != 0 &&
        (m_baFlags & kNeverRender) == 0) {
        Rt2dCTMPush();
        Rt2dMaestroRender(m_pMaestro);
        Rt2dCTMPop();
        UpdateHotSpots();
        return;
    }
    HideAllHotSpotHierarchy();
}

// 0x0006f3d0 CKFlashUI_SetHidden_maybe (XXL2 HideInterfaceHierarchy)
void CKFlashUI::HideInterfaceHierarchy(uint8_t hide) {
    if (m_pMaestro == nullptr) return;
    Rt2dObjectSetVisible(Rt2dMaestroGetScene(m_pMaestro), hide ^ 1);
    HideAllHotSpotHierarchy();
}

// 0x0006f6e0 CKFlashUI_Show_maybe (XXL2 StartInterface): when the sector is loaded and the interface is
// not started: the scene's visibility set, the hot spots hidden, the state started (and bits 0x40 set,
// 0x100 cleared), the animations updated once, the colour multiplier marked done, vt+0x58 of every
// animation and text.
void CKFlashUI::StartInterface(uint8_t visible) {
    if (!SectorLoaded(this) || (m_baFlags & kStateMask) == 2) return;
    if (m_pMaestro != nullptr) {
        Rt2dObjectSetVisible(Rt2dMaestroGetScene(m_pMaestro), visible);
        HideAllHotSpotHierarchy();
    }
    m_baFlags = (m_baFlags & 0xfffffebcu) | 0x42;
    Rt2dMaestroUpdateAnimations(m_pMaestro);
    m_cColorMult_maybe.alpha = -0x1p+0f;  // TOC1 -0x6d64
    for (uint32_t i = 0; i < m_ui32FlashAnimNb; ++i) AsFlashObject(m_apFlashAnimation[i])->Vf58();
    for (uint32_t i = 0; i < m_ui32FlashTextNb; ++i) AsFlashObject(m_apFlashText[i])->Vf58();
}

// 0x0006f8b0 CKFlashUI_Hide_maybe (XXL2 StopInterface): the restart button message sent (sector loaded),
// the scene hidden (hide = 1), the hot spots hidden; the state stopped.
void CKFlashUI::StopInterface(uint8_t hide) {
    if (m_pMaestro != nullptr) {
        int32_t label = m_i32RestartInterfaceButton;
        if (SectorLoaded(this)) {
            Rt2dMaestroForAllVisibleAnimations(m_pMaestro, PostButtonMessageCB, &label);
            Rt2dMaestroProcessMessages(m_pMaestro);
        }
        if (m_pMaestro != nullptr) {
            Rt2dObjectSetVisible(Rt2dMaestroGetScene(m_pMaestro), hide ^ 1);
            HideAllHotSpotHierarchy();
        }
    }
    m_baFlags &= ~kStateMask;
}

// 0x0006f9e8 CKFlashUI_ProcessMaestroMessagesAndNotifyElements_maybe: the restart message's twin (the
// label data is the stack word, as in the original: uninitialised) then vt+0x5c of every animation and
// text; the hot spots marked hidden.
void CKFlashUI::StopAndNotifyElements() {
    if (SectorLoaded(this)) {
        // BUG(original): the label the callback reads is an uninitialised stack word (local_30); the port
        // passes -1 (no label) for it.
        int32_t label = -1;
        Rt2dMaestroForAllVisibleAnimations(m_pMaestro, PostButtonMessageCB, &label);
        Rt2dMaestroProcessMessages(m_pMaestro);
    }
    m_baFlags = (m_baFlags & ~kHotSpotsHidden) | kHotSpotsHidden;
    for (uint32_t i = 0; i < m_ui32FlashAnimNb; ++i) AsFlashObject(m_apFlashAnimation[i])->Vf5C();
    for (uint32_t i = 0; i < m_ui32FlashTextNb; ++i) AsFlashObject(m_apFlashText[i])->Vf5C();
}

// 0x00071040 CKFlashUI_Update_maybe (XXL2 Update): for a started interface whose sector is loaded and
// scene visible: the input labels pressed this frame (the "Flash Manager" input mapping, 40 actions) sent
// as button messages; the 3D hot-spot objects synced; the movie advanced (by the frame time, IKTime
// +0x20, or 0xaa948's 0.02 s), its animations and messages run, the visibility cache refreshed; the queued
// messages in sent to the objects to warn (message 0x2300) and triggered; the pending colour multiplier
// applied; vt+0x68 of every animation and text.
void CKFlashUI::Update(IKTime* time) {
    if (!SectorLoaded(this)) return;
    if (Rt2dObjectIsVisible(Rt2dMaestroGetScene(m_pMaestro)) == 0) return;
    uint32_t flags = m_baFlags;
    if ((flags & kStateMask) != 2) return;
    CKFlashManager* manager = g_pEngine->m_flashManager;
    if (manager->m_bLockInputUpdate == 0 || (flags & kDontUpdate) != 0 || (flags & kForceInputWhenLocked) != 0) {
        CKInputDico* input = manager->GetInputDico();
        for (uint32_t i = 0;; ++i) {
            if (input->GetButtonState(static_cast<int32_t>(i & 0xff)) != 0 && m_ai32InputLabelId[i] != -1) {
                int32_t label = m_ai32InputLabelId[i];
                if (SectorLoaded(this)) {
                    Rt2dMaestroForAllVisibleAnimations(m_pMaestro, PostButtonMessageCB, &label);
                    Rt2dMaestroProcessMessages(m_pMaestro);
                }
                flags = m_baFlags;
                if ((flags & kOneInputPerFrame) != 0) break;
            }
            if (i == 0x27) {
                flags = m_baFlags;
                break;
            }
        }
    }
    float deltaTime;
    if ((flags & kFixedTimeStep) == 0) {
        deltaTime = time->m_afDeltaTime[1];  // IKTime +0x20
    } else {
        deltaTime = 0x1.47ae14p-6f;  // 0x000aa948 KStub_ReturnFloat0p02_aa948 (TOC1 -0x5f9c: 0x3ca3d70a)
    }
    for (uint32_t i = 0; i < m_ui32HotSpotNb; ++i) AsHotSpot(m_apHotSpot[i])->Update3dAttachedObject(this);
    m_baFlags &= ~kHotSpotsHidden;
    Rt2dMaestroAddDeltaTime(m_pMaestro, deltaTime);
    Rt2dMaestroUpdateAnimations(m_pMaestro);
    Rt2dMaestroProcessMessages(m_pMaestro);
    UpdateRt2dObjectInfo();
    for (uint32_t q = 0; q < m_ui32FlashMessageInQueuedNb; ++q) {
        CKFlashMessageIn* message = m_vpFlashMessageIn[q];
        for (uint32_t i = 0; i < m_ui32FlashObjectToWarnNb; ++i) {
            // vt+0x1c MessageProc(0x2300, message)
            m_apObjectsToWarn[i]->MessageProc(0x2300, message);
        }
        message->StartAllEvents();
    }
    m_ui32FlashMessageInQueuedNb = 0;
    if (m_cColorMult_maybe.alpha != -0x1p+0f) {
        ColorMultiplierData data{this, &m_cColorMult_maybe};
        Rt2dSceneForAllChildren(GetMaestroScene(), SetColorMultiplierCB, &data);  // TOC1 -0x6d94 -> 0x6db28
        m_cColorMult_maybe.alpha = -0x1p+0f;
    }
    for (uint32_t i = 0; i < m_ui32FlashAnimNb; ++i) AsFlashObject(m_apFlashAnimation[i])->ApplyColorMultiplier();
    for (uint32_t i = 0; i < m_ui32FlashTextNb; ++i) AsFlashObject(m_apFlashText[i])->ApplyColorMultiplier();
}

// --- CFlashHotSpot methods in this unit ---------------------------------------------------------------

// 0x00072198 FlashWidgetBinding_UpdateAnchor_maybe: the flash object's anchor (vt+0x60) into the hot spot.
void CFlashHotSpot::UpdateAnchor() {
    m_bVisibilityTest = m_pFlashHotSpot->GetScreenAnchor(&m_v2Pos, &m_v2Size_maybe, m_aColor_maybe);
}
