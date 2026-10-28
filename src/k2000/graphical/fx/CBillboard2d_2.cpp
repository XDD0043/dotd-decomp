// CBillboard2d_2.cpp - reconstructed original translation unit 0x66e30-0x67ec0 (GAME_TOC1, main_toc1), 19 functions, 18 live.
// Primary class: CBillboard2d  key 0x3cd  category Graphical  size 0x84  vtable 0xb156e8
// Other owners: BillboardBrush (3), Button2d (3), C2dButtonBase (3), KBase730C (3), DrawUIBillboardShapeWithTransform (1), IKButton2d (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x66e30  BillboardBrush_RebuildPath_maybe (IKBillboard2d_CreateBillboard)
//   [ ] 0x66ef8  BillboardBrush_ComputeAlignedRect_maybe
//   [ ] 0x67028  BillboardBrush_RecreateBrush_maybe
//   [x] 0x670f0  CBillboard2d_ConstructBrush_maybe
//   [ ] 0x67148  CBillboard2d_ConstructBrush_2_maybe  [dead]
//   [x] 0x671a0  DrawUIBillboardShapeWithTransform
//   [x] 0x67598  CBillboard2d_LoadBrush
//   [ ] 0x67888  CBillboard2d_SaveCommon_maybe
//   [ ] 0x67cd8  Button2d_IsSelected_maybe
//   [ ] 0x67ce8  IKButton2d_ClearReferences
//   [ ] 0x67d10  IKButton2d_Save
//   [ ] 0x67d38  IKButton2d_Load
//   [ ] 0x67d60  Button2d_Deselect_maybe
//   [ ] 0x67d78  Button2d_Select_maybe
//   [ ] 0x67e48  IKButton2d_Hide
//   [ ] 0x67ea0  KBase730C_Load
//   [ ] 0x67ea8  KBase730C_Save
//   [ ] 0x67eb0  KBase730C_LevelReset
//   [ ] 0x67eb8  KStub_Nop_67eb8
//
//   [ ] 0x998358  IKButton2d_GetClassGroup  [inline]
//   [ ] 0x998360  IKButton2d_GetClassId  [inline]
//   [ ] 0x998368  IKButton2d_IsKindOf  [inline]
//   [ ] 0x998390  IKButton2d_DeletingDestructor  [inline]
//   [ ] 0x9983d8  IKButton2d_Destructor  [inline]
#include "k2000/ui/IKBillboard2d.h"

#include <cstring>

#include "Renderware/rt2d/Rt2d.h"
#include "Renderware/rwcore/RwStream.h"
#include "Renderware/rwcore/RwIm3D.h"
#include "crt/ppc_ops.h"
#include "k2000/cameras/CameraContext.h"
#include "k2000/graphical/ui/CManager2d.h"
#include "k2000/io/IKFile.h"
#include "k2000/misc/Engine.h"
#include "k2000/render/CRenderer.h"

// 0x000670f0 CBillboard2d_ConstructBrush_maybe, in its store order; +0x10 is left as it is.
IKBillboard2d::IKBillboard2d() {
    m_pvUVs[3].m_fY = 0.0f;
    m_bEnableBorder = 0;
    m_bUseAlpha = 1;
    m_pBillboard = nullptr;
    m_pBrush = nullptr;
    m_Color = 0;
    m_vBillboardSize.m_fX = 0.0f;
    m_vBillboardSize.m_fY = 0.0f;
    m_bStretchToAspectRatio = 0;
    m_pvUVs[0].m_fX = 0.0f;
    m_pvUVs[0].m_fY = 0.0f;
    m_pvUVs[1].m_fX = 0.0f;
    m_pvUVs[1].m_fY = 0.0f;
    m_pvUVs[2].m_fX = 0.0f;
    m_pvUVs[2].m_fY = 0.0f;
    m_pvUVs[3].m_fX = 0.0f;
}

// 0x00067598 CBillboard2d_LoadBrush (XXL2 IKBillboard2d::Load): every type. The brush comes from the RW
// stream (the file's own position), then its texture by reference (no resolve; one count added here).
int32_t IKBillboard2d::Load(IKFile* file, int32_t /*type*/) {
    RwStream* stream = file->m_pRwStream;
    // RwStreamFindChunk(0x1a2) (result ignored), then Rt2dBrushStreamRead_maybe. STUB(C1.4): the brush is
    // kept as its stream record (Renderware/rt2d/Rt2d.h).
    RwStreamFindChunk(stream, 0x1a2, nullptr, nullptr);
    m_pBrush = Rt2dBrushStreamRead(stream);
    IKFile_ReadTextureRef(file, reinterpret_cast<void**>(&m_pBrush->texture), 0);
    if (m_pBrush->texture != nullptr) TextureRef_AddRef(m_pBrush->texture);  // RwTexture +0x54 refCount + 1
    ReadRaw(file, &m_Color, 4);
    ReadRaw(file, &m_borderColor, 4);
    ReadF32LE(file, &m_vBillboardSize.m_fX);  // one 8-byte read, both words swapped
    ReadF32LE(file, &m_vBillboardSize.m_fY);
    ReadU8(file, &m_bStretchToAspectRatio);
    ReadU8(file, &m_bEnableBorder);
    for (CVector2& uv : m_pvUVs) {         // one 0x20-byte read, every word swapped
        ReadF32LE(file, &uv.m_fX);
        ReadF32LE(file, &uv.m_fY);
    }
    ReadU8(file, &m_bUseAlpha);
    CreateBillboard();  // vt+0x24
    return 1;
}

// 0x00066e30 IKBillboard2d_CreateBillboard (BillboardBrush_RebuildPath_maybe)
int32_t IKBillboard2d::CreateBillboard() {
    Rt2dBrushSetUV(m_pBrush, reinterpret_cast<RwV2d*>(&m_pvUVs[0]), reinterpret_cast<RwV2d*>(&m_pvUVs[1]),
                   reinterpret_cast<RwV2d*>(&m_pvUVs[2]), reinterpret_cast<RwV2d*>(&m_pvUVs[3]));
    if (m_pBillboard != nullptr) Rt2dPathDestroy(static_cast<Rt2dPath*>(m_pBillboard));
    Rt2dPath* path = Rt2dPathCreate();
    m_pBillboard = path;
    if (path == nullptr) return 0;
    // 1 when Rt2dPathRect returns the path (the original's ((|a ^ b|) - 1) >> 31).
    return Rt2dPathRect(path, -0x1p-1f, -0x1p-1f, 0x1p+0f, 0x1p+0f) == m_pBillboard ? 1 : 0;
}

// 0x00066c70 BillboardBrush_ApplyUV
void IKBillboard2d::ApplyUV() {
    Rt2dBrushSetUV(m_pBrush, reinterpret_cast<RwV2d*>(&m_pvUVs[0]), reinterpret_cast<RwV2d*>(&m_pvUVs[1]),
                   reinterpret_cast<RwV2d*>(&m_pvUVs[2]), reinterpret_cast<RwV2d*>(&m_pvUVs[3]));
}

// 0x00066cb8 BillboardBrush_SetTexture
int32_t IKBillboard2d::SetTexture(RwTexture* texture) {
    Rt2dBrush* const brush = m_pBrush;
    if (brush == nullptr) return 0;
    if (brush->texture == texture) return 1;
    // ((r >> 31) - ((r >> 31) ^ r)) >> 31 of the returned brush: 1 for any brush (a positive address), 0
    // for null.
    return Rt2dBrushSetTexture(brush, texture) != nullptr ? 1 : 0;
}

namespace {
// 0x00c5b864: the border outline's five Im3D vertices (a closed square, -0.5..0.5 at z 1).
RwIm3DVertex s_borderOutline[5];
}  // namespace

// 0x000671a0 DrawUIBillboardShapeWithTransform (from the assembly: every operation is single precision).
uint8_t IKBillboard2d::DrawShapeWithTransform(float rotation, const CVector2* position, uint8_t hAlign, uint8_t vAlign,
                                              const CVector2* scale) {
    float y = position->m_fY;
    float x = position->m_fX;
    float width;
    const float height0 = m_vBillboardSize.m_fY;
    if (m_bStretchToAspectRatio != 0) {
        width = m_vBillboardSize.m_fX * g_pEngine->m_manager2d->m_fAspect;
    } else {
        width = m_vBillboardSize.m_fX;
    }
    const float height = height0 * scale->m_fY;
    width = width * scale->m_fX;
    if (hAlign == 0) {
        x = x + (width * 0x1p-1f) / g_pEngine->m_manager2d->m_fAspect;
    } else if (hAlign == 2) {
        x = x + (width * -0x1p-1f) / g_pEngine->m_manager2d->m_fAspect;
    }
    if (vAlign == 0) {
        y = ppc::fmadds(height, -0x1p-1f, y);
    } else if (vAlign == 2) {
        y = ppc::fmadds(height, 0x1p-1f, y);
    }
    const float screenX = x * g_pEngine->m_manager2d->m_fAspect;
    RwRenderStateSet(rwRENDERSTATESRCBLEND, reinterpret_cast<void*>(static_cast<intptr_t>(kBlendTableSrc[m_bUseAlpha])));
    RwRenderStateSet(rwRENDERSTATEDESTBLEND, reinterpret_cast<void*>(static_cast<intptr_t>(kBlendTableDest[m_bUseAlpha])));
    Rt2dCTMPush();
    Rt2dCTMTranslate(screenX, y);
    Rt2dCTMScale(width, height);
    if (m_bStretchToAspectRatio == 0) Rt2dCTMScale(Engine_GetCameraContext()->m_fPixelAspect84, 0x1p+0f);
    Rt2dCTMRotate(rotation);
    _rt2dPathRenderChain(static_cast<Rt2dPath*>(m_pBillboard), m_pBrush);
    if (m_bEnableBorder != 0) {
        static const float kCorners[5][2] = {{-0.5f, -0.5f}, {-0.5f, 0.5f}, {0.5f, 0.5f}, {0.5f, -0.5f}, {-0.5f, -0.5f}};
        for (int i = 0; i < 5; ++i) {
            s_borderOutline[i].objVertex.x = kCorners[i][0];
            s_borderOutline[i].objVertex.y = kCorners[i][1];
            s_borderOutline[i].objVertex.z = 0x1p+0f;
            std::memcpy(&s_borderOutline[i].color, &m_borderColor, 4);  // the four file bytes (R G B A)
        }
        RwRenderStateSet(rwRENDERSTATETEXTURERASTER, nullptr);
        if (RwIm3DTransform(s_borderOutline, 5, _rt2dCTMGetComposite(), 0x1e) != nullptr) {
            RwIm3DRenderPrimitive(rwPRIMTYPEPOLYLINE);
            RwIm3DEnd();
        }
    }
    Rt2dCTMPop();
    RwRenderStateSet(rwRENDERSTATESRCBLEND, reinterpret_cast<void*>(static_cast<intptr_t>(kBlendTableSrc[1])));
    RwRenderStateSet(rwRENDERSTATEDESTBLEND, reinterpret_cast<void*>(static_cast<intptr_t>(kBlendTableDest[1])));
    return 1;
}
