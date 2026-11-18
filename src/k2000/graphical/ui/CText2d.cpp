// CText2d.cpp - reconstructed original translation unit 0x65e50-0x66e30 (GAME_TOC1, main_toc1), 32 functions, 30 live.
// Primary class: CText2d  key 0x5cd  category Graphical  size 0x748  vtable 0xb15d00
// Other owners: BillboardBrush (5), DrawUITextWidget (1), Element2dBrush (1), Rt2dShape (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x65e50  CText2d_Delete
//   [ ] 0x65ea0  CText2d_GetPixelRect_maybe  [dead]
//   [x] 0x65f48  CText2d_OnEvent_maybe
//   [x] 0x65f88  CText2d_Destroy  (CText2d::Destroy)
//   [x] 0x65fd0  CText2d_RecursiveRegistration  (CText2d::RecursiveRegistration)
//   [ ] 0x66028  CText2d_Save
//   [x] 0x66090  CText2d_GetBoundingRect  (CText2d::GetBoundingBox)
//   [x] 0x660f8  RegisterCText2dType  (RegisterAllClasses: ClassTable.inc)
//   [ ] 0x66170  _GLOBAL__I_66170
//   [x] 0x66180  CText2d_DeleteArray
//   [x] 0x66220  CText2d_Create
//   [x] 0x66290  DrawUITextWidget
//   [x] 0x66300  CText2d_SetTextAscii
//   [x] 0x66398  CText2d_SetTextWide_maybe
//   [x] 0x66440  CText2d_SetTextById
//   [x] 0x664e8  CText2d_InitDefaults_maybe
//   [x] 0x665f8  CText2d_MessageProc  (MessageProc: the text part's KStub_Return1_6a0b8, then 1: the default slot)
//   [x] 0x66628  CText2d_PostLoad
//   [x] 0x666b0  CText2d_Show
//   [x] 0x66810  CText2d_Hide  (CText2d::Disable)
//   [x] 0x66878  CText2d_CreateArray
//   [x] 0x66958  CText2d_vf80
//   [x] 0x669c8  CText2d_Load
//   [ ] 0x66b38  CText2d_HitTestPoint_maybe  [dead]
//   [x] 0x66c18  BillboardBrush_ClearReferences_maybe  (IKBillboard2d::DestroyBillboard, IKBillboard2d.h)
//   [x] 0x66c58  KStub_Return1_66c58  (IKBillboard2d RecursiveRegistration slot: returns 1, nothing to port)
//   [x] 0x66c60  BillboardBrush_GetTexture  (IKBillboard2d::GetTexture)
//   [x] 0x66c70  BillboardBrush_ApplyUV (in CBillboard2d_2.cpp with IKBillboard2d)
//   [x] 0x66cb8  BillboardBrush_SetTexture (in CBillboard2d_2.cpp with IKBillboard2d)
//   [x] 0x66d20  BillboardBrush_SetAlpha_maybe  (IKBillboard2d::SetAlpha)
//   [x] 0x66d68  Element2dBrush_SetColor_maybe
//   [x] 0x66db0  Rt2dShape_Release_maybe  (IKBillboard2d::FreeMemoryBillboard2D)
//
//   [ ] 0x9972d0  BillboardBrush_SetSize_maybe  [inline]
//   [ ] 0x997310  BillboardBrush_SetUVs_maybe  [inline]
//   [ ] 0x9981c0  CText2d_GetClassGroup_Thunk  [inline]
//   [ ] 0x9981c8  CText2d_GetClassType  [inline]
//   [ ] 0x9981d0  CText2d_GetClassId_Thunk  [inline]
//   [ ] 0x9981d8  CText2d_GetClassID  [inline]
//   [ ] 0x9981e0  CText2d_ClearReferences_Thunk  [inline]
//   [ ] 0x9981e8  CText2d_LevelReset_Thunk  [inline]
//   [ ] 0x9981f0  CText2d_Save_Thunk  [inline]
//   [ ] 0x9981f8  CText2d_SetTextAscii_Thunk  [inline]
//   [ ] 0x998200  CText2d_SetTextWide_maybe_Thunk  [inline]
//   [ ] 0x998208  CText2d_SetTextById_Thunk  [inline]
//   [ ] 0x998210  CText2d_HandleMessage_Thunk  [inline]
//   [ ] 0x998218  CText2d_PostLoad_Thunk  [inline]
//   [x] 0x998220  CText2d_IsKindOfClass  [inline]
//   [ ] 0x998248  CText2d_DeletingDestructor_Thunk  [inline]
//   [ ] 0x998250  CText2d_DeletingDestructor  [inline]
//   [ ] 0x9982a0  CText2d_vf80_Thunk  [inline]
//   [x] 0x9982a8  CText2d_Load_Thunk  [inline]
//   [ ] 0x9982b0  CText2d_Destructor_Thunk  [inline]
//   [ ] 0x9982b8  CText2d_Destructor  [inline]
//   [ ] 0x9982e0  KStub_Return0_9982e0  [inline]
//   [ ] 0x9982e8  KStub_Return0_9982e8  [inline]
//   [ ] 0x9982f0  BillboardBrush_ScaleSize_maybe  [inline]
#include "k2000/graphical/ui/CText2d.h"

#include <cstring>

#include "Renderware/rt2d/Rt2d.h"
#include "k2000/ui/IKBillboard2d.h"
#include "k2000/io/IKFile.h"
#include "k2000/misc/Engine.h"

// 0x00066958 CText2d_vf80
void CText2d::Scale(const CVector2& scale) {
    m_bAutoSize = 0;
    m_vBoxSize.m_fX = m_vBoxSize.m_fX * scale.m_fX;  // fmuls
    m_vBoxSize.m_fY = m_vBoxSize.m_fY * scale.m_fY;
    ComputeLayout();
    // 0x0006a0b0 KStub_Nop_6a0b0 (the text part's empty post-layout hook): nothing.
}

// 0x000669c8 CText2d_Load: both base Loads for every type, then two references (K_LEVEL_PLATEFORMS).
int32_t CText2d::Load(IKFile* file, int32_t type) {
    IKNode2d::Load(file, type);
    IKText2d::Load(file, type);
    if (type != K_LEVEL_PLATEFORMS) return 1;
    IKFile_ReadRef(file, &m_unk740);
    IKFile_ReadRef(file, &m_unk744);
    return 1;
}

// 0x000664e8 CText2d_InitDefaults_maybe, in its store order.
void CText2d::InitDefaults() {
    m_ui8Type = 1;
    m_ui8CenterWAlign = 1;
    m_ui8CenterHAlign = 1;
    m_pOwner = nullptr;
    m_pPrevious = nullptr;
    m_pNext = nullptr;
    m_baFlags = 0;
    m_vPosition.m_fX = 0x1p-1f;
    m_vPosition.m_fY = 0x1p-1f;
    m_f32RotateAngle = 0.0f;
    m_pLocManager = reinterpret_cast<IKSerializable*>(g_pEngine->m_locManager);  // engine +0x94
    m_vBoxSize.m_fX = 0x1.19999ap+0f;  // 1.1 (0x3f8ccccd)
    m_vBoxSize.m_fY = 0x1p+0f;
    m_i32FontId = 0x29a;
    m_ui32BoxLinesCount = 0;
    m_wszText[0] = 0;
    m_pBrush = Rt2dBrushCreate();
    m_f32CharHeight = 0.0f;
    m_f32SpaceWidth = 0.0f;
    // DEV: TOC1 -0x6f48 -> 0x00c50dfc, a colour word in the BSS (0 in the EBOOT; its writer, a static
    // initializer_maybe, is not traced). The live system text holds 0xffffffff (white) from it.
    static const uint32_t kDefaultColor_maybe = 0xffffffffu;
    m_Color = kDefaultColor_maybe;
    m_pTextAccessor = nullptr;
    m_VarColor = kDefaultColor_maybe;
    m_f32TextSize = 0x1.99999ap-2f;  // 0.4 (0x3ecccccd)
    m_ui8HAlignType = 1;
    m_bAutoSize = 0;
    m_f32NextLineTime = 0.0f;
    m_f32Leading = 0.0f;
    m_ui8WAlignType = 1;
    m_ui32CurrentBeginLine = 0;
    m_unk740 = nullptr;
    m_unk744 = nullptr;
}

// 0x00066d68 Element2dBrush_SetColor_maybe (IKBillboard2d vt+0x28, XXL2 IKBillboard2d::SetColor)
void IKBillboard2d::SetColor(const uint8_t* color) {
    std::memcpy(&m_Color, color, 4);
    RwRGBA* rgba = reinterpret_cast<RwRGBA*>(&m_Color);
    Rt2dBrushSetRGBA(m_pBrush, rgba, rgba, rgba, rgba);
}

// 0x00066628 CText2d_PostLoad: the text part is tokenised for every type (0x6b2d8: the accessor's text,
// or the loaded text split into words and laid out; without a font yet the layout only clears the box line
// count), then (type 0) the linked node (+0x740) is disabled (vt+0x68).
int32_t CText2d::PostLoad(int32_t type) {
    TokenizeText();
    if (type == K_LEVEL_PLATEFORMS && m_unk740 != nullptr) static_cast<IKNode2d*>(m_unk740)->Disable();
    return 1;
}

// 0x00065f48 CText2d_OnEvent_maybe
void CText2d::RecursiveNodeReach(uint8_t what, void* data) {
    IKText2d::RecursiveNodeReach(static_cast<uint8_t>((m_baFlags >> 1) & 1), what, data);
}

// 0x00066290 DrawUITextWidget
void CText2d::Render(IKTime* time) {
    if ((m_baFlags & 2) == 0) return;
    IKText2d::Render(m_f32RotateAngle, &m_vPosition, &m_v2ConstantScale, m_ui8CenterWAlign, m_ui8CenterHAlign, time);
}

// 0x00066440 CText2d_SetTextById. The linked node's vt+0x88 is this slot (the node is a CText2d).
uint8_t CText2d::SetTextById(IKSerializable* text) {
    if (m_unk744 != nullptr) {
        IKNode2d* linked = static_cast<IKNode2d*>(m_unk740);
        if (linked != nullptr && ((linked->m_baFlags >> 1) & 1) != 0)
            return static_cast<CText2d*>(linked)->SetTextById(text);
    }
    return SetTextFromLocString(text);
}

// 0x00066398 CText2d_SetTextWide_maybe
uint8_t CText2d::SetTextWide(const uint16_t* text) {
    if (m_unk744 != nullptr) {
        IKNode2d* linked = static_cast<IKNode2d*>(m_unk740);
        if (linked != nullptr && ((linked->m_baFlags >> 1) & 1) != 0)
            return static_cast<CText2d*>(linked)->SetTextWide(text);
    }
    return SetTextClearLocRef(text);
}

// 0x000666b0 CText2d_Show
void CText2d::Enable() {
    if ((m_baFlags & 2) != 0) return;
    if (m_unk744 != nullptr && m_unk740 != nullptr) {
        CText2d* linked = static_cast<CText2d*>(static_cast<IKNode2d*>(m_unk740));
        if (((linked->m_baFlags >> 1) & 1) != 0) return;
        if (((static_cast<IKNode2d*>(m_unk744)->m_baFlags >> 1) & 1) != 0) {
            linked->Enable();  // vt+0x64
            IKSerializable* text = GetTextId();
            if (text != nullptr) {
                linked->SetTextById(GetTextId());  // vt+0x88
                return;
            }
            linked->SetTextWide(m_wszText);  // vt+0x8c with this text's +0x3c (IKText2d +0x14)
            return;
        }
    }
    m_baFlags = static_cast<uint8_t>(m_baFlags | 2);  // rlwimi: bit 0 kept, bit 1 set
    RefreshFromLocString();
}


// 0x00066300 CText2d_SetTextAscii
void CText2d::SetTextAscii(const char* text) {
    if (m_unk744 != nullptr) {
        IKNode2d* linked = static_cast<IKNode2d*>(m_unk740);
        if (linked != nullptr && ((linked->m_baFlags >> 1) & 1) != 0) {
            static_cast<CText2d*>(linked)->SetTextAscii(text);
            return;
        }
    }
    IKText2d::SetTextAscii(text);
}

#include "k2000/components/CKLocTextAccessor.h"

// 0x00065f88 CText2d_Destroy
void CText2d::Destroy() {
    IKNode2d::Destroy();
    FreeMemoryText2D();  // 0x0006a0c0 -> text part vt+0x14
}

// 0x00065fd0 CText2d_RecursiveRegistration
void CText2d::RecursiveRegistration(int32_t type) {
    IKNode2d::RecursiveRegistration(type);
    m_pTextAccessor->RecursiveRegistration(type);  // 0x0006a148: vt+0x24
}

// 0x00066090 CText2d_GetBoundingRect
void CText2d::GetBoundingBox(CBox2D* box) const {
    ComputeAlignedRect(box, &m_vPosition, m_ui8CenterWAlign, m_ui8CenterHAlign);  // 0x009985c8
    IKNode2d::GetBoundingBox(box);                                              // 0x000698a8 (empty)
}

// 0x00066810 CText2d_Hide: (flags >> 2 << 2) | bit 0, i.e. bit 1 cleared.
void CText2d::Disable() {
    m_baFlags = static_cast<uint8_t>(m_baFlags & 0xfd);
    if (m_unk740 != nullptr) static_cast<IKNode2d*>(m_unk740)->Disable();  // vt+0x68
}

// 0x00066db0 Rt2dShape_Release_maybe (IKBillboard2d vt+0x00), in its store order.
void IKBillboard2d::FreeMemoryBillboard2D() {
    if (m_pBillboard != nullptr) {
        Rt2dPathDestroy(static_cast<Rt2dPath*>(m_pBillboard));
        m_pBillboard = nullptr;
    }
    if (m_pBrush != nullptr) {
        Rt2dBrushDestroy(m_pBrush);
        m_pBrush = nullptr;
    }
    m_bStretchToAspectRatio = 0;
    m_vBillboardSize.m_fX = 0.0f;
    m_Color = 0;
    m_vBillboardSize.m_fY = 0.0f;
}

// 0x00066c60 BillboardBrush_GetTexture
RwTexture* IKBillboard2d::GetTexture() const { return m_pBrush->texture; }

// 0x00066d20 BillboardBrush_SetAlpha_maybe
void IKBillboard2d::SetAlpha(uint8_t alpha) {
    reinterpret_cast<uint8_t*>(&m_Color)[3] = alpha;
    RwRGBA* rgba = reinterpret_cast<RwRGBA*>(&m_Color);
    Rt2dBrushSetRGBA(m_pBrush, rgba, rgba, rgba, rgba);
}
