// CColorTextButton2d.cpp - reconstructed original translation unit 0x5f768-0x600b0 (GAME_TOC1, main_toc1), 21 functions, 21 live.
// Primary class: CColorTextButton2d  key 0x30d  category Graphical  size 0x744  vtable 0xb159b0
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x5f768  CColorTextButton2d_vf58  (RecursiveNodeReach)
//   [x] 0x5f7a8  CColorTextButton2d_GetBoundingRect  (GetBoundingBox)
//   [x] 0x5f7e8  CColorTextButton2d_ResetRuntime_maybe  (FreeMemory)
//   [ ] 0x5f820  RegisterCColorTextButton2dClass
//   [ ] 0x5f898  _GLOBAL__I_5f898
//   [x] 0x5f8a8  CColorTextButton2d_vf94  (SetSelectColor)
//   [x] 0x5f920  CColorTextButton2d_vf8C  (Deselect)
//   [ ] 0x5f9a8  CColorTextButton2d_Save
//   [x] 0x5fa40  CColorTextButton2d_Load
//   [x] 0x5fad8  CColorTextButton2d_Destroy
//   [x] 0x5fb20  CColorTextButton2d_Construct  (the constructor)
//   [x] 0x5fb90  CColorTextButton2d_DeleteArray
//   [x] 0x5fc30  CColorTextButton2d_vf84  (Render)
//   [x] 0x5fca0  CColorTextButton2d_vf88  (Select)
//   [x] 0x5fd50  CColorTextButton2d_vf90  (SetButtonColor)
//   [x] 0x5fdc8  CColorTextButton2d_PostLoad
//   [x] 0x5fdf8  CColorTextButton2d_Construct_2_maybe  (the constructor)
//   [x] 0x5fe68  CColorTextButton2d_Show  (Enable)
//   [x] 0x5fec0  CColorTextButton2d_vf80  (Scale)
//   [x] 0x5ff30  CColorTextButton2d_Create
//   [x] 0x5ffb0  CColorTextButton2d_CreateArray
//
//   [x] 0x997950  CColorTextButton2d_IsKindOfClass  [inline]
//   [ ] 0x997988  CColorTextButton2d_GetClassGroup_Thunk  [inline]
//   [x] 0x997990  CColorTextButton2d_GetClassType  [inline]
//   [ ] 0x997998  CColorTextButton2d_GetClassId_Thunk  [inline]
//   [x] 0x9979a0  CColorTextButton2d_GetClassID  [inline]
//   [ ] 0x9979a8  CColorTextButton2d_Save_Thunk  [inline]
//   [ ] 0x9979b0  CColorTextButton2d_Load_Thunk  [inline]
//   [ ] 0x9979b8  CColorTextButton2d_ClearReferences_Thunk  [inline]
//   [ ] 0x9979c0  CColorTextButton2d_vf90_Thunk  [inline]
//   [ ] 0x9979c8  CColorTextButton2d_PostLoad_Thunk  [inline]
//   [ ] 0x9979d0  CColorTextButton2d_Destructor_Thunk  [inline]
//   [x] 0x9979d8  CColorTextButton2d_Destructor  [inline]
//   [ ] 0x997a00  CColorTextButton2d_vf80_Thunk  [inline]
//   [ ] 0x997a08  CColorTextButton2d_DeletingDestructor_Thunk  [inline]
//   [x] 0x997a10  CColorTextButton2d_DeletingDestructor  [inline]
#include "k2000/graphical/ui/CColorTextButton2d.h"

#include "Renderware/rt2d/Rt2d.h"
#include "k2000/io/IKFile.h"

// C2.8 port-rest R02. No game file holds a CColorTextButton2d; ported from the disassembly.

namespace {
RwRGBA* AsRGBA(uint32_t* color) { return reinterpret_cast<RwRGBA*>(color); }
}  // namespace

// 0x0005fad8 CColorTextButton2d_Destroy
void CColorTextButton2d::Destroy() {
    FreeMemoryText2D();     // 0x0006a0c0 Text2dBlock_Destroy -> the text part's vt+0x14
    IKButton2d::Destroy();  // 0x00067ce8
}

// 0x0005fa40 CColorTextButton2d_Load
int32_t CColorTextButton2d::Load(IKFile* file, int32_t type) {
    IKButton2d::Load(file, type);  // 0x00067d38
    IKText2d::Load(file, type);    // 0x0006b728
    ReadRaw(file, &m_SelectColor, 4);
    return 1;
}

// 0x0005fdc8 CColorTextButton2d_PostLoad
int32_t CColorTextButton2d::PostLoad(int32_t /*type*/) {
    TokenizeText();  // 0x0006b2d8
    return 1;
}

// 0x0005f7e8 CColorTextButton2d_ResetRuntime_maybe
void CColorTextButton2d::FreeMemory() {
    IKNode2d::FreeMemory();  // 0x00069ce8
    m_SelectColor = 0;
}

// 0x0005f768 CColorTextButton2d_vf58
void CColorTextButton2d::RecursiveNodeReach(uint8_t what, void* data) {
    IKText2d::RecursiveNodeReach(static_cast<uint8_t>((m_baFlags >> 1) & 1), what, data);  // 0x0006c0a8
}

// 0x0005fe68 CColorTextButton2d_Show
void CColorTextButton2d::Enable() {
    if ((m_baFlags & 2) != 0) return;
    m_baFlags = static_cast<uint8_t>((m_baFlags & ~0x2u) | 0x2u);
    RefreshFromLocString();  // 0x0006bd10
}

// 0x0005f7a8 CColorTextButton2d_GetBoundingRect
void CColorTextButton2d::GetBoundingBox(CBox2D* box) const {
    ComputeAlignedRect(box, &m_vPosition, m_ui8CenterWAlign, m_ui8CenterHAlign);  // 0x009985c8
}

// 0x0005fec0 CColorTextButton2d_vf80
void CColorTextButton2d::Scale(const CVector2& scale) {
    m_bAutoSize = 0;
    m_vBoxSize.m_fX = m_vBoxSize.m_fX * scale.m_fX;  // fmuls
    m_vBoxSize.m_fY = m_vBoxSize.m_fY * scale.m_fY;
    ComputeLayout();  // 0x0006a468
    // 0x0006a0b0 KStub_Nop_6a0b0 (the text part's empty post-layout hook): nothing.
}

// 0x0005fc30 CColorTextButton2d_vf84
void CColorTextButton2d::Render(IKTime* time) {
    if ((m_baFlags & 2) == 0) return;
    IKText2d::Render(m_f32RotateAngle, &m_vPosition, &m_v2ConstantScale, m_ui8CenterWAlign, m_ui8CenterHAlign, time);
}

// 0x0005fca0 CColorTextButton2d_vf88
void CColorTextButton2d::Select() {
    if ((m_baFlags & 2) == 0) return;
    if (Button2d_IsSelected(this) == 0) {  // 0x00067cd8
        Rt2dBrushSetRGBA(m_pBrush, AsRGBA(&m_SelectColor), AsRGBA(&m_SelectColor), AsRGBA(&m_SelectColor),
                         AsRGBA(&m_SelectColor));
    }
    IKButton2d::Select();  // 0x00067d78
}

// 0x0005f920 CColorTextButton2d_vf8C
void CColorTextButton2d::Deselect() {
    if (Button2d_IsSelected(this) != 0) {
        Rt2dBrushSetRGBA(m_pBrush, AsRGBA(&m_Color), AsRGBA(&m_Color), AsRGBA(&m_Color), AsRGBA(&m_Color));
    }
    IKButton2d::Deselect();  // 0x00067d60
}

// 0x0005fd50 CColorTextButton2d_vf90
void CColorTextButton2d::SetButtonColor(const uint32_t* color) {
    m_Color = *color;
    if (Button2d_IsSelected(this) == 0) {
        Rt2dBrushSetRGBA(m_pBrush, AsRGBA(&m_Color), AsRGBA(&m_Color), AsRGBA(&m_Color), AsRGBA(&m_Color));
    }
}

// 0x0005f8a8 CColorTextButton2d_vf94
void CColorTextButton2d::SetSelectColor(const uint32_t* color) {
    m_SelectColor = *color;
    if (Button2d_IsSelected(this) != 0) {
        Rt2dBrushSetRGBA(m_pBrush, AsRGBA(&m_SelectColor), AsRGBA(&m_SelectColor), AsRGBA(&m_SelectColor),
                         AsRGBA(&m_SelectColor));
    }
}
