// CKFlashText.cpp - reconstructed original translation unit 0x75960-0x777f8 (GAME_TOC1, main_toc1), 35 functions, 29 live.
// Primary class: CKFlashText  key 0x7cd  category Graphical  size 0x44  vtable 0xb16320
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x75960  CKFlashText_Delete
//   [ ] 0x759b0  CKFlashText_Construct  [dead]
//   [ ] 0x759d0  CKFlashText_Construct_2  [dead]
//   [ ] 0x759f0  RegisterCKFlashTextClass
//   [ ] 0x75a68  _GLOBAL__I_75a68
//   [ ] 0x75a78  FUN_00075a78  [dead]
//   [x] 0x75ad8  CKFlashText_vf54
//   [x] 0x75b10  CKFlashText_RefreshStrings_maybe
//   [x] 0x75c58  CKFlashText_SetFont_maybe
//   [x] 0x75ce8  CKFlashText_Load
//   [ ] 0x75ed8  CKFlashText_Save
//   [ ] 0x75f00  CKFlashText_RecursiveRegistration
//   [x] 0x75fb8  CKFlashText_Destroy
//   [x] 0x76018  CKFlashText_DeleteArray
//   [x] 0x760c0  CKFlashText_ApplyColorMultiplier_maybe
//   [x] 0x761a8  CKFlashText_vf64
//   [x] 0x76238  CKFlashText_CollectStringObjects_maybe
//   [x] 0x76358  CKFlashText_SetFontForStrings_maybe
//   [x] 0x764e0  CKFlashText_ApplyTextToStrings_maybe
//   [x] 0x76560  CKFlashText_SetTextId_maybe
//   [ ] 0x765c8  CKFlashText_GetTextId_maybe  [dead]
//   [x] 0x765f8  CKFlashText_GetScreenAnchor_maybe
//   [x] 0x76978  CKFlashText_CreateArray
//   [x] 0x76a40  CKFlashText_Create
//   [x] 0x76a90  CKFlashText_UpdateStringHeights_maybe
//   [x] 0x76b48  CKFlashText_DeletingDestructor
//   [x] 0x76bd0  CKFlashText_Destructor
//   [ ] 0x76c50  FUN_00076c50  [dead]
//   [x] 0x76f20  CKFlashText_SetFontName_maybe
//   [x] 0x77048  CKFlashText_SetTextW_maybe
//   [x] 0x77208  CKFlashText_SetText_maybe
//   [x] 0x773e0  CKFlashText_PostLoad
//   [ ] 0x77430  CKFlashText_Destructor_2  [dead]
//   [x] 0x774b0  CKFlashText_SetFontIndex_maybe
//   [x] 0x77600  CKFlashText_ApplyFont_maybe
//
//   [x] 0x9993f8  CKFlashText_IsKindOfClass  [inline]
//   [x] 0x999420  CKFlashText_GetClassType  [inline]
//   [x] 0x999428  CKFlashText_GetClassID  [inline]
#include "k2000/graphical/ui/CKFlashText.h"

#include <cstdio>
#include <cstring>

#include "Renderware/rt2d/Rt2d.h"
#include "crt/ppc_ops.h"
#include "k2000/components/CKLocTextAccessor.h"
#include "k2000/graphical/ui/CKFlashUI.h"
#include "k2000/graphical/ui/CManager2d.h"
#include "k2000/graphical/ui/CameraContextUi.h"
#include "k2000/io/IKFile.h"
#include "k2000/logic/CKSector.h"
#include "k2000/logic/ui/CKLocText.h"
#include "k2000/memory/Mem.h"
#include "k2000/misc/Engine.h"
#include "k2000/misc/Wcs.h"

namespace {

// The PS3 build's Rt2d object strings hold 16-bit characters (Rt2dFontChar): the K side passes UTF-16
// buffers through Rt2d.h's RwChar* parameters (see the C1.5 kside report: the declarations follow the
// Rt2d port).
const RwChar* AsRwChar(const uint16_t* text) { return reinterpret_cast<const RwChar*>(text); }
const uint16_t* AsWide(const RwChar* text) { return reinterpret_cast<const uint16_t*>(text); }

// The text accessor's current text: its vector's first entry, or its own pointer without a vector.
// Inlined in RefreshText, SetTextId and the setters.
IKSerializable* CurrentText(CKLocTextAccessor* accessor) {
    if (accessor->m_texts.m_pBlock == nullptr) return accessor->m_pText;
    return accessor->m_texts.m_pBlock[0];
}

bool SectorLoaded(const CKFlashUI* ui) { return ui->m_pSector != nullptr && (ui->m_pSector->m_ba16Properties & 1) != 0; }

}  // namespace

// Inlined in 0x00076a40 CKFlashText_Create, the stores in its order (the IKFlashObject part is not set).
CKFlashText::CKFlashText() {
    m_vpObject.m_pBlock = nullptr;
    m_vpObject.m_ui32NbElt = 2;
    m_vpObject.m_ui32NbUsedElt = 0;
}

// 0x00076bd0 CKFlashText_Destructor: m_vpObject's (inlined TVector destructor).
CKFlashText::~CKFlashText() {
    if (m_vpObject.m_pBlock != nullptr) Mem_FreeAligned16(m_vpObject.m_pBlock);
    m_vpObject.m_ui32NbUsedElt = 0;
    m_vpObject.m_pBlock = nullptr;
}

// 0x00075ce8 CKFlashText_Load
int32_t CKFlashText::Load(IKFile* file, int32_t type) {
    IKFlashObject::Load(file, type);
    if (type != K_LEVEL_PLATEFORMS) return 1;
    IKFile_ReadRef(file, &m_pTextAccessor);
    ReadU8(file, &m_bNoTextIdNeeded);
    ReadF32LE(file, &m_fBoxWidth);
    ReadU32LE(file, &m_JustifType);
    ReadS32LE(file, &m_i32FontId);
    // As in the original: a new block for 2 objects (Mem_AllocAligned16(8)); the count is left as it is.
    m_vpObject.m_ui32NbElt = 2;
    m_vpObject.m_pBlock =
        static_cast<Rt2dObject**>(Mem_AllocAligned16(2 * static_cast<uint32_t>(sizeof(Rt2dObject*))));
    return 1;
}

// 0x00075fb8 CKFlashText_Destroy
void CKFlashText::Destroy() {
    IKFlashObject::Destroy();
    if (m_vpObject.m_pBlock != nullptr) {
        Mem_FreeAligned16(m_vpObject.m_pBlock);
        m_vpObject.m_pBlock = nullptr;
    }
    m_vpObject.m_ui32NbUsedElt = 0;
    m_vpObject.m_pBlock = nullptr;
}

// 0x000773e0 CKFlashText_PostLoad: a field that needs no text id gets the empty text (TOC1 -0x6c00 ->
// 0x00ac4138 "").
int32_t CKFlashText::PostLoad(int32_t type) {
    IKFlashObject::PostLoad(type);
    if (m_bNoTextIdNeeded != 0) SetText("");
    return 1;
}

// 0x00076238 CKFlashText_CollectStringObjects_maybe (XXL2 GetRt2dObject): appends the string objects
// while the interface's sector is loaded. The vector grows by one element at a time.
void CKFlashText::GetRt2dObject(TVector<Rt2dObject*, 1>* objects) {
    if (!SectorLoaded(GetFlashUI()) || m_vpObject.m_ui32NbUsedElt == 0) return;
    uint32_t count = objects->m_ui32NbUsedElt;
    for (uint32_t i = 0; i < m_vpObject.m_ui32NbUsedElt; ++i) {
        if (objects->m_ui32NbElt == count) {
            uint32_t capacity = count + 1;
            if (capacity == 0) capacity = 1;
            objects->m_pBlock = static_cast<Rt2dObject**>(
                Mem_ReallocAligned16(objects->m_pBlock, capacity * static_cast<uint32_t>(sizeof(Rt2dObject*))));
            count = objects->m_ui32NbUsedElt;
            objects->m_ui32NbElt = capacity;
        }
        objects->m_pBlock[count] = m_vpObject.m_pBlock[i];
        count = objects->m_ui32NbUsedElt + 1;
        objects->m_ui32NbUsedElt = count;
    }
}

// 0x00075ad8 CKFlashText_vf54: the base's, then the gathered objects are forgotten.
void CKFlashText::Vf54() {
    IKFlashObject::Vf54();
    m_vpObject.m_ui32NbUsedElt = 0;
}

// 0x000761a8 CKFlashText_vf64: every object into the interface's object map, without a parent.
void CKFlashText::RegisterObjects() {
    for (uint32_t i = 0; i < m_vpObject.m_ui32NbUsedElt; ++i)
        GetFlashUI()->SetRt2dObjectParent(m_vpObject.m_pBlock[i], nullptr);
}

// 0x000760c0 CKFlashText_ApplyColorMultiplier_maybe: the pending colour multiplier (alpha not -1) on the
// objects, from the last one down, then alpha = -1.
void CKFlashText::ApplyColorMultiplier() {
    if (m_unk14[3] == -0x1p+0f) return;
    for (uint32_t i = m_vpObject.m_ui32NbUsedElt; i != 0;) {
        --i;
        Rt2dObject* object = m_vpObject.m_pBlock[i];
        // BUG(original): the loop ends at the first object the interface does not show; the ones before
        // it keep their old multiplier.
        if (GetFlashUI()->IsRt2dObjectVisible(object) == 0) break;
        Rt2dObjectSetColorMultiplier(object, reinterpret_cast<RwRGBAReal*>(m_unk14));
    }
    m_unk14[3] = -0x1p+0f;
}

// 0x00075b10 CKFlashText_RefreshStrings_maybe (XXL2 RefreshText): the accessor's text into every object;
// without a text, "NO_ID_<label>" unless the field needs none.
void CKFlashText::RefreshText() {
    uint16_t localised[350];  // 0x2bc bytes on the stack
    uint16_t text[358];       // 0x2cc bytes
    for (uint32_t i = 0; i < m_vpObject.m_ui32NbUsedElt; ++i) {
        IKSerializable* locText = CurrentText(m_pTextAccessor);
        if (locText != nullptr) {
            LocString_CopyText(static_cast<CKLocText*>(locText), localised);
            WStr_CopyReturnEnd(text, localised);
        } else {
            if (m_bNoTextIdNeeded != 0) continue;
            char ascii[700];
            // FormatString (0x98d3b0) with TOC1 -0x6c34 "%s_%s" and -0x6c30 "NO_ID".
            std::snprintf(ascii, sizeof(ascii), "%s_%s", "NO_ID", m_szLabelName);
            WStr_FromAscii(text, ascii);
        }
        Rt2dObjectStringSetText(m_vpObject.m_pBlock[i], AsRwChar(text));
    }
}

// 0x00076a90 CKFlashText_UpdateStringHeights_maybe (XXL2 ApplyTextAlignment; inlined by the setters):
// box width = movie-bbox width x m_fBoxWidth / scaled width, and the justification, into every object.
void CKFlashText::ApplyTextAlignment() {
    float scaledWidth = 0.0f;
    float scaledHeight = 0.0f;
    Rt2dBBox bbox;
    GetFlashUI()->GetMaestroScaleWidthAndHeight(&scaledWidth, &scaledHeight, &bbox);
    const float boxWidth = (bbox.w * m_fBoxWidth) / scaledWidth;  // fmuls, fdivs
    for (uint32_t i = 0; i < m_vpObject.m_ui32NbUsedElt; ++i) {
        m_vpObject.m_pBlock[i]->data.objectString.boxwidth = boxWidth;
        m_vpObject.m_pBlock[i]->data.objectString.justiftype = static_cast<Rt2dJustificationType>(m_JustifType);
    }
}

// 0x00077208 CKFlashText_SetText_maybe: the field no longer follows a text id; the text, widened, into
// every object (from the last one) when it differs from the first object's, then the alignment.
void CKFlashText::SetText(const char* text) {
    if (m_pTextAccessor->m_texts.m_pBlock == nullptr) {
        m_pTextAccessor->m_pText = nullptr;
    } else {
        m_pTextAccessor->m_texts.m_pBlock[0] = nullptr;
    }
    m_bNoTextIdNeeded = 1;
    const uint32_t count = m_vpObject.m_ui32NbUsedElt;
    if (count == 0) return;
    uint16_t wide[356];  // 0x2c8 bytes
    WStr_FromAscii(wide, text);
    if (Wcs_Compare(wide, AsWide(Rt2dObjectStringGetText(m_vpObject.m_pBlock[0]))) == 0) return;
    for (uint32_t i = count; i != 0;) {
        --i;
        Rt2dObjectStringSetText(m_vpObject.m_pBlock[i], AsRwChar(wide));
    }
    ApplyTextAlignment();
}

// 0x00077048 CKFlashText_SetTextW_maybe: SetText with a wide text.
void CKFlashText::SetTextW(const uint16_t* text) {
    if (m_pTextAccessor->m_texts.m_pBlock == nullptr) {
        m_pTextAccessor->m_pText = nullptr;
    } else {
        m_pTextAccessor->m_texts.m_pBlock[0] = nullptr;
    }
    m_bNoTextIdNeeded = 1;
    const uint32_t count = m_vpObject.m_ui32NbUsedElt;
    if (count == 0) return;
    if (Wcs_Compare(text, AsWide(Rt2dObjectStringGetText(m_vpObject.m_pBlock[0]))) == 0) return;
    for (uint32_t i = count; i != 0;) {
        --i;
        Rt2dObjectStringSetText(m_vpObject.m_pBlock[i], AsRwChar(text));
    }
    ApplyTextAlignment();
}

// 0x00076560 CKFlashText_SetTextId_maybe: a new text (a CKStdText) for the accessor; refreshed when it
// changes. A text clears m_bNoTextIdNeeded.
void CKFlashText::SetTextId(IKSerializable* text) {
    if (text != nullptr) m_bNoTextIdNeeded = 0;
    CKLocTextAccessor* accessor = m_pTextAccessor;
    IKSerializable** first = accessor->m_texts.m_pBlock;
    if (first == nullptr) {
        if (accessor->m_pText == text) return;
    } else if (*first == text) {
        return;
    }
    if (first != nullptr) {
        *first = text;
        RefreshText();
        return;
    }
    accessor->m_pText = text;
    RefreshText();
}

// 0x00075c58 CKFlashText_SetFont_maybe (XXL2 ChangeTextFont)
void CKFlashText::ChangeTextFont(const char* font) {
    for (uint32_t i = 0; i < m_vpObject.m_ui32NbUsedElt; ++i) Rt2dObjectStringSetFont(m_vpObject.m_pBlock[i], font);
    RefreshText();
}

// 0x00076f20 CKFlashText_SetFontName_maybe: ChangeTextFont, then the alignment.
void CKFlashText::SetFontName(const char* font) {
    for (uint32_t i = 0; i < m_vpObject.m_ui32NbUsedElt; ++i) Rt2dObjectStringSetFont(m_vpObject.m_pBlock[i], font);
    RefreshText();
    ApplyTextAlignment();
}

// 0x000774b0 CKFlashText_SetFontIndex_maybe (XXL2 SetFontId): the font of CManager2d's font-name table.
void CKFlashText::SetFontId(int32_t fontId) {
    m_i32FontId = fontId;
    if (fontId == -1) return;
    CManager2d* manager = g_pEngine->m_manager2d;
    for (uint32_t i = 0; i < m_vpObject.m_ui32NbUsedElt; ++i)
        Rt2dObjectStringSetFont(m_vpObject.m_pBlock[i], manager->m_aszFontsName[fontId]);
    RefreshText();
    ApplyTextAlignment();
}

// 0x00077600 CKFlashText_ApplyFont_maybe (XXL2 ReloadFont): the field's font id again (when set), the
// text, then the alignment (a second time in every case).
void CKFlashText::ReloadFont() {
    const int32_t fontId = m_i32FontId;
    m_i32FontId = fontId;
    if (fontId != -1) {
        CManager2d* manager = g_pEngine->m_manager2d;
        for (uint32_t i = 0; i < m_vpObject.m_ui32NbUsedElt; ++i)
            Rt2dObjectStringSetFont(m_vpObject.m_pBlock[i], manager->m_aszFontsName[fontId]);
        RefreshText();
        ApplyTextAlignment();
    }
    ApplyTextAlignment();
}

// 0x00076358 CKFlashText_SetFontForStrings_maybe (XXL2 InternChangeTextFont): each object's text is kept
// across the font change: widened for a font that is not unicode, narrowed for a unicode one.
void CKFlashText::InternChangeTextFont(const char* font, int32_t unicode) {
    uint16_t buffer[352];  // 0x2c0 bytes on the stack, shared by both forms
    for (uint32_t i = 0; i < m_vpObject.m_ui32NbUsedElt; ++i) {
        Rt2dObject* object = m_vpObject.m_pBlock[i];
        if (unicode == 0) {
            WStr_FromAscii(buffer, Rt2dObjectStringGetText(object));
        } else {
            Wcs_ToAscii(reinterpret_cast<char*>(buffer), AsWide(Rt2dObjectStringGetText(object)));
        }
        Rt2dObjectStringSetFont(object, font);
        Rt2dObjectStringSetText(object, AsRwChar(buffer));
    }
}

// 0x000764e0 CKFlashText_ApplyTextToStrings_maybe (XXL2 RestoreTextLabel): the label as the text.
void CKFlashText::RestoreTextLabel() {
    for (uint32_t i = 0; i < m_vpObject.m_ui32NbUsedElt; ++i)
        Rt2dObjectStringSetText(m_vpObject.m_pBlock[i], m_szLabelName);
}

// 0x000765f8 CKFlashText_GetScreenAnchor_maybe: the first object the interface shows whose anchor is on
// screen (x and y in [-3, 4]): its position, its size in movie pixels and its colour (multiplier +
// offset, x 255). Only while the interface's sector is loaded.
uint8_t CKFlashText::GetScreenAnchor(CVector2* position, CVector2* size, uint8_t* rgba) {
    CKFlashUI* ui = GetFlashUI();
    if (!SectorLoaded(ui)) return 0;
    for (uint32_t i = 0; i < m_vpObject.m_ui32NbUsedElt; ++i) {
        Rt2dObject* object = m_vpObject.m_pBlock[i];
        if (GetFlashUI()->IsRt2dObjectVisible(object) == 0) continue;
        float movieWidth;
        float movieHeight;
        GetFlashUI()->GetMovieSize(&movieWidth, &movieHeight);
        const RwMatrix* ltm = Rt2dObjectGetLTM(object);
        const float sizeY = ltm->up.y * movieHeight;    // fmuls f30
        const float sizeX = ltm->right.x * movieWidth;  // fmuls f31
        CVector2 anchor;
        GetNormalizedPosition(object, &anchor);
        const float boxWidth = m_fBoxWidth * CameraContext_GetPixelAspect();  // camera context +0x7c
        if (m_JustifType == 1) {
            anchor.m_fX = ppc::fmadds(sizeX, boxWidth * 0x1p-1f, anchor.m_fX);  // TOC1 -0x6c24 0.5
        } else if (m_JustifType == 2) {
            anchor.m_fX = ppc::fmadds(sizeX, boxWidth, anchor.m_fX);
        }
        // The raster size (camera context +0x04 -> +0x0c / +0x10; TOC1 -0x6c14 0.0 without a raster).
        const float rasterWidth = static_cast<float>(CameraContext_GetRasterWidth());
        const float rasterHeight = static_cast<float>(CameraContext_GetRasterHeight());
        anchor.m_fX = ((rasterHeight * ui->m_MaestroBbox.w) / rasterWidth) * anchor.m_fX;
        // TOC1 -0x6c20 -3.0 and -0x6c1c 4.0 (fcmpu + cror: NaN fails).
        const bool onScreen = anchor.m_fX >= -0x1.8p+1f && anchor.m_fX <= 0x1p+2f && anchor.m_fY >= -0x1.8p+1f &&
                              anchor.m_fY <= 0x1p+2f;
        if (!onScreen) {
            ui = GetFlashUI();
            continue;
        }
        if (position != nullptr) {
            position->m_fY = anchor.m_fY;
            position->m_fX = anchor.m_fX;
        }
        if (size != nullptr) {
            size->m_fX = sizeX;
            size->m_fY = sizeY;
        }
        if (rgba == nullptr) return 1;
        const RwRGBAReal* mult = Rt2dObjectGetColorMultiplier(object);
        const RwRGBAReal* offs = Rt2dObjectGetColorOffset(object);
        const float scale = 0x1.fep+7f;  // TOC1 -0x6c18 255.0
        const int32_t g = ppc::fctiwz((mult->green + offs->green) * scale);
        const int32_t b = ppc::fctiwz((mult->blue + offs->blue) * scale);
        const int32_t a = ppc::fctiwz((mult->alpha + offs->alpha) * scale);
        const int32_t r = ppc::fctiwz((mult->red + offs->red) * scale);
        rgba[1] = static_cast<uint8_t>(g);
        rgba[3] = static_cast<uint8_t>(a);
        rgba[2] = static_cast<uint8_t>(b);
        rgba[0] = static_cast<uint8_t>(r);
        return 1;
    }
    return 0;
}
