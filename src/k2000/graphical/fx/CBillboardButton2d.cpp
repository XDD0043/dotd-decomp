// CBillboardButton2d.cpp - the 2D billboard button (C2.8 port-all P08).
//
// Reconstructed original translation unit: 0x5be10-0x5c868 (GAME_TOC1, main_toc1), 33 functions, 23 live.
// Primary class: CBillboardButton2d  key 0x64d  category Graphical  size 0x70  vtable 0xb157d0
// Other owners: CBillboardList2d (7)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x5be10  CBillboardButton2d_vf80  (Scale)
//   [x] 0x5be38  CBillboardButton2d_GetBoundingRect  (GetBoundingBox)
//   [x] 0x5be78  CBillboardButton2d_ResetRuntime_maybe  (FreeMemory)
//   [ ] 0x5beb0  RegisterCBillboardButton2dClass
//   [ ] 0x5bf28  _GLOBAL__I_5bf28
//   [x] 0x5bf38  CBillboardButton2d_vf90  (SetButtonColor)
//   [x] 0x5bfb0  CBillboardButton2d_vf8C  (Deselect)
//   [x] 0x5c038  CBillboardButton2d_vf88  (Select)
//   [ ] 0x5c0e8  CBillboardButton2d_Save
//   [x] 0x5c180  CBillboardButton2d_Load
//   [x] 0x5c218  CBillboardButton2d_RecursiveRegistration
//   [x] 0x5c2c8  CBillboardButton2d_Destroy
//   [x] 0x5c310  CBillboardButton2d_Construct  (the constructor)
//   [x] 0x5c380  CBillboardButton2d_DeleteArray  (DOTD_DECLARE_FACTORIES)
//   [x] 0x5c428  CBillboardButton2d_vf94  (SetSelectColor)
//   [x] 0x5c498  CBillboardButton2d_Draw_maybe  (Render)
//   [x] 0x5c508  CBillboardButton2d_Construct_2  (the constructor)
//   [x] 0x5c578  CBillboardButton2d_CreateArray  (DOTD_DECLARE_FACTORIES)
//   [x] 0x5c680  CBillboardButton2d_Create  (the constructor)
//   [x] 0x5c700  CBillboardList2d_Delete  (CBillboardList2d's Delete factory (CBillboardList2d.h))
//   [x] 0x5c750  CBillboardList2d_RecursiveRegistration  (CBillboardList2d::RecursiveRegistration (CBillboardList2d.h))
//   [ ] 0x5c758  CBillboardList2d_GetBillboardCount_maybe  [dead]
//   [ ] 0x5c760  CBillboardList2d_GetTextureCount_maybe  [dead]
//   [ ] 0x5c768  FUN_0005c768  [dead]
//   [ ] 0x5c778  FUN_0005c778  [dead]
//   [x] 0x5c790  CBillboardList2d_vfAC  (CBillboardList2d::SetBillboardsSize (CBillboardList2d.h))
//   [ ] 0x5c7a8  FUN_0005c7a8  [dead]
//   [ ] 0x5c7c0  FUN_0005c7c0  [dead]
//   [ ] 0x5c810  CBillboardList2d_GetTextureAt_maybe  [dead]
//   [ ] 0x5c840  FUN_0005c840  [dead]
//   [ ] 0x5c850  FUN_0005c850  [dead]
//   [x] 0x5c858  CBillboardList2d_vfCC  (CBillboardList2d::SetAlignType (CBillboardList2d.h))
//   [ ] 0x5c860  FUN_0005c860  [dead]
//
//   [ ] 0x994270  CBillboardButton2d_vf58  [inline]
//   [ ] 0x997468  CBillboardButton2d_IsKindOfClass  [inline]
//   [ ] 0x9974a0  CBillboardButton2d_GetClassGroup_Thunk  [inline]
//   [ ] 0x9974a8  CBillboardButton2d_GetClassType  [inline]
//   [ ] 0x9974b0  CBillboardButton2d_GetClassId_Thunk  [inline]
//   [ ] 0x9974b8  CBillboardButton2d_GetClassID  [inline]
//   [ ] 0x9974c0  CBillboardButton2d_vf80_Thunk  [inline]
//   [ ] 0x9974c8  CBillboardButton2d_vf90_Thunk  [inline]
//   [ ] 0x9974d0  CBillboardButton2d_Save_Thunk  [inline]
//   [ ] 0x9974d8  CBillboardButton2d_Load_Thunk  [inline]
//   [ ] 0x9974e0  CBillboardButton2d_LevelReset_Thunk  [inline]
//   [ ] 0x9974e8  CBillboardButton2d_ClearReferences_Thunk  [inline]
//   [ ] 0x9974f0  CBillboardButton2d_DeletingDestructor_Thunk  [inline]
//   [ ] 0x9974f8  CBillboardButton2d_DeletingDestructor  [inline]
//   [ ] 0x997550  CBillboardButton2d_Destructor_Thunk  [inline]
//   [ ] 0x997558  CBillboardButton2d_Destructor  [inline]
#include "k2000/graphical/fx/CBillboardButton2d.h"

#include "Renderware/rt2d/Rt2d.h"
#include "k2000/logic/CKSavingManager.h"
#include "k2000/io/IKFile.h"
#include "k2000/misc/Engine.h"

// 0x0005c680 CBillboardButton2d_Create (the constructor inlined; also 0x5c310 / 0x5c508)
CBillboardButton2d::CBillboardButton2d() { m_SelectColor = 0; }

// 0x00997558 / 0x009974f8 (inline in the original): the vtables only.
CBillboardButton2d::~CBillboardButton2d() {}

// 0x0005be10 CBillboardButton2d_vf80
void CBillboardButton2d::Scale(const CVector2& scale) {
    const float y = scale.m_fY;
    m_vBillboardSize.m_fX = m_vBillboardSize.m_fX * scale.m_fX;
    m_vBillboardSize.m_fY = m_vBillboardSize.m_fY * y;
}

// 0x0005be38 CBillboardButton2d_GetBoundingRect
void CBillboardButton2d::GetBoundingBox(CBox2D* box) const {
    IKBillboard2d::GetBoundingBox(box, &m_vPosition, m_ui8CenterWAlign, m_ui8CenterHAlign);  // 0x00066ef8
}

// 0x0005be78 CBillboardButton2d_ResetRuntime_maybe
void CBillboardButton2d::FreeMemory() {
    IKNode2d::FreeMemory();  // 0x00069ce8
    m_SelectColor = 0;
}

// 0x0005bf38 CBillboardButton2d_vf90
void CBillboardButton2d::SetButtonColor(const uint32_t* color) {
    m_Color = *color;
    if (IsSelected() == 0) {
        RwRGBA* rgba = reinterpret_cast<RwRGBA*>(&m_Color);
        Rt2dBrushSetRGBA(m_pBrush, rgba, rgba, rgba, rgba);
    }
}

// 0x0005bfb0 CBillboardButton2d_vf8C
void CBillboardButton2d::Deselect() {
    if (IsSelected() != 0) {
        RwRGBA* rgba = reinterpret_cast<RwRGBA*>(&m_Color);
        Rt2dBrushSetRGBA(m_pBrush, rgba, rgba, rgba, rgba);
    }
    IKButton2d::Deselect();  // 0x00067d60
}

// 0x0005c038 CBillboardButton2d_vf88
void CBillboardButton2d::Select() {
    if ((m_baFlags & 2) == 0) return;
    if (IsSelected() == 0) {
        RwRGBA* rgba = reinterpret_cast<RwRGBA*>(&m_SelectColor);
        Rt2dBrushSetRGBA(m_pBrush, rgba, rgba, rgba, rgba);
    }
    IKButton2d::Select();  // 0x00067d78
}

// 0x0005c180 CBillboardButton2d_Load (no type test)
int32_t CBillboardButton2d::Load(IKFile* file, int32_t type) {
    IKButton2d::Load(file, type);     // 0x00067d38
    IKBillboard2d::Load(file, type);  // 0x00067598
    ReadRaw(file, &m_SelectColor, 4);
    return 1;
}

// 0x0005c218 CBillboardButton2d_RecursiveRegistration
void CBillboardButton2d::RecursiveRegistration(int32_t type) {
    if (static_cast<uint32_t>(type - 4) > 3) {
        g_pEngine->m_pSavingManager->RegisterSerializableObject(this, nullptr);  // vt+0x24
        IKNode2d::RecursiveRegistration(type);  // 0x00069848
        // KStub_Return1_66c58: the billboard part's RecursiveRegistration, nothing.
    }
}

// 0x0005c2c8 CBillboardButton2d_Destroy
void CBillboardButton2d::Destroy() {
    FreeMemoryBillboard2D();  // 0x00066c18 -> vt+0x00 0x00066db0
    IKButton2d::Destroy();    // 0x00067ce8
}

// 0x0005c428 CBillboardButton2d_vf94: the colour argument itself goes to the brush.
void CBillboardButton2d::SetSelectColor(const uint32_t* color) {
    m_SelectColor = *color;
    if (IsSelected() != 0) {
        RwRGBA* rgba = reinterpret_cast<RwRGBA*>(const_cast<uint32_t*>(color));
        Rt2dBrushSetRGBA(m_pBrush, rgba, rgba, rgba, rgba);
    }
}

// 0x0005c498 CBillboardButton2d_Draw_maybe
void CBillboardButton2d::Render(IKTime* /*time*/) {
    if ((m_baFlags & 2) == 0) return;
    DrawShapeWithTransform(m_f32RotateAngle, &m_vPosition, m_ui8CenterWAlign, m_ui8CenterHAlign, &m_v2ConstantScale);
}
