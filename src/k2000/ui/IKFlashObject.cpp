// IKFlashObject.cpp - reconstructed original translation unit 0x77828-0x77e48 (GAME_TOC1, main_toc1), 13 functions, 12 live.
// Primary owner: IKFlashObject (not a registered class)
// Other owners: CKFlashElement (4), FlashUI (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x77828  IKFlashObject_vf58
//   [x] 0x77838  IKFlashObject_SetColorWhite_maybe
//   [ ] 0x77848  CKFlashElement_DivideXByAspect_maybe  [dead]
//   [x] 0x778a8  FlashUI_NormalizedToScreenPixels_maybe
//   [x] 0x77940  IKFlashObject_vf5C
//   [x] 0x77950  IKFlashObject_vf28
//   [x] 0x77958  IKFlashObject_Load
//   [x] 0x77b78  IKFlashObject_vf24
//   [x] 0x77b80  IKFlashObject_PostLoad
//   [x] 0x77b88  IKFlashObject_ClearReferences
//   [x] 0x77bd0  CKFlashElement_GetObjectScreenPos_maybe
//   [x] 0x77c48  CKFlashElement_GetScreenPosPixels_maybe
//   [x] 0x77d68  CKFlashElement_GetScreenPosNormalized_maybe
//
//   [x] 0x999430  IKFlashObject_vf14  [inline]
//   [x] 0x999438  IKFlashObject_vf18  [inline]
//   [x] 0x999440  IKFlashObject_vf8  [inline]
//   [x] 0x999460  IKFlashObject_vf0  [inline]
//   [x] 0x999478  IKFlashObject_DeletingDestructor  [inline]
//
// Ported: Destroy, Load and the screen-position helpers; the one-line slots are inline in IKFlashObject.h.
#include "k2000/ui/IKFlashObject.h"

#include "Renderware/rt2d/Rt2d.h"
#include "k2000/graphical/ui/CKFlashUI.h"
#include "k2000/graphical/ui/CameraContextUi.h"
#include "k2000/io/IKFile.h"
#include "k2000/memory/Mem.h"

// 0x00077b88 IKFlashObject_Destroy
void IKFlashObject::Destroy() {
    if (m_szLabelName != nullptr) {
        Mem_FreeAligned16(m_szLabelName);
        m_szLabelName = nullptr;
    }
}

// 0x00077958 IKFlashObject_Load. Note the order: the reference (+0x0c) before the label id (+0x08), as in
// XXL2.
int32_t IKFlashObject::Load(IKFile* file, int32_t type) {
    if (type != K_LEVEL_PLATEFORMS) return 1;
    int16_t length = 0;
    ReadS16LE(file, &length);
    if (length < 0) {
        m_szLabelName = nullptr;
    } else {
        m_szLabelName = static_cast<char*>(Mem_AllocAligned16(static_cast<uint32_t>(length + 1)));
        ReadRaw(file, m_szLabelName, static_cast<uint32_t>(length));
        m_szLabelName[length] = 0;
    }
    IKFile_ReadRef(file, &m_pFlashUI);
    ReadU32LE(file, &m_ui32LabelId);
    ReadU8(file, &m_unk10);
    return 1;
}

namespace {
// The local vector the position helpers hand to GetRt2dObject: one element allocated, none used.
struct ObjectVector {
    TVector<Rt2dObject*, 1> v;
    ObjectVector() {
        v.m_ui32NbUsedElt = 0;
        v.m_ui32NbElt = 1;
        v.m_pBlock = nullptr;
        v.m_pBlock = static_cast<Rt2dObject**>(Mem_AllocAligned16(static_cast<uint32_t>(sizeof(Rt2dObject*))));
    }
    ~ObjectVector() {
        if (v.m_pBlock != nullptr) Mem_FreeAligned16(v.m_pBlock);
    }
};
}  // namespace

// 0x000778a8 FlashUI_NormalizedToScreenPixels_maybe (XXL2 GetRealPosition): x through the reference aspect
// and the raster height, y flipped. All single precision.
void IKFlashObject::GetRealPosition(const CVector2* normalized, CVector2* position) {
    const float aspect = CameraContext_GetReferenceAspect();
    // The raster height (engine camera context +0x04 -> +0x10; TOC1 -0x6be8 0.0 without a raster).
    const float height = static_cast<float>(CameraContext_GetRasterHeight());
    const float width = aspect * height;
    const float y = height * normalized->m_fY;
    const float x = width * normalized->m_fX;
    position->m_fY = height - y;
    position->m_fX = x / aspect;
}

// 0x00077bd0 CKFlashElement_GetObjectScreenPos_maybe (XXL2 GetNormalizedPosition): the LTM position, x
// divided by the reference aspect.
void IKFlashObject::GetNormalizedPosition(Rt2dObject* object, CVector2* position) {
    const RwMatrix* ltm = Rt2dObjectGetLTM(object);
    const float x = ltm->pos.x;
    const float y = ltm->pos.y;
    const float aspect = CameraContext_GetReferenceAspect();
    position->m_fY = y;
    position->m_fX = x / aspect;
}

// 0x00077d68 CKFlashElement_GetScreenPosNormalized_maybe: the same for the first object of GetRt2dObject.
// BUG(original): no object (an empty vector) reads the uninitialised first entry.
void IKFlashObject::GetNormalizedPosition(CVector2* position) {
    ObjectVector objects;
    GetRt2dObject(&objects.v);
    const RwMatrix* ltm = Rt2dObjectGetLTM(objects.v.m_pBlock[0]);
    const float x = ltm->pos.x;
    const float y = ltm->pos.y;
    const float aspect = CameraContext_GetReferenceAspect();
    position->m_fY = y;
    position->m_fX = x / aspect;
}

// 0x00077c48 CKFlashElement_GetScreenPosPixels_maybe (XXL2 GetPosition): the first object's LTM position
// in raster pixels, y down.
void IKFlashObject::GetPosition(CVector2* position) {
    ObjectVector objects;
    GetRt2dObject(&objects.v);
    const RwMatrix* ltm = Rt2dObjectGetLTM(objects.v.m_pBlock[0]);
    const float x = ltm->pos.x;
    const float y = ltm->pos.y;
    const float aspect = CameraContext_GetReferenceAspect();
    const float height = static_cast<float>(CameraContext_GetRasterHeight());
    const float width = aspect * height;
    const float yPixels = y * height;
    const float xPixels = x * width;
    position->m_fY = height - yPixels;
    position->m_fX = xPixels / aspect;
}
