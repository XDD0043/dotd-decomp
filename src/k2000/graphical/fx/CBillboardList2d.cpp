// CBillboardList2d.cpp - reconstructed original translation unit 0x5c868-0x5f768 (GAME_TOC1, main_toc1), 38 functions, 33 live.
// Primary class: CBillboardList2d  key 0x58d  category Graphical  size 0x84  vtable 0xb158c8
// Other owners: CColorTextButton2d (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x5c868  CBillboardList2d_vfD0  (SetSpacing, the header)
//   [x] 0x5c870  CBillboardList2d_Destroy  (IKNode2d's Destroy, inherited)
//   [ ] 0x5c898  RegisterCBillboardList2dClass
//   [ ] 0x5c910  _GLOBAL__I_5c910
//   [x] 0x5c920  CBillboardList2d_FreeTextures_maybe  (DestroyTextures)
//   [x] 0x5c9d0  CBillboardList2d_ClearBillboards  (DestroyBillboards)
//   [x] 0x5cb70  CBillboardList2d_vf98  (AddTexture)
//   [ ] 0x5cc48  CBillboardList2d_Construct  [dead]
//   [x] 0x5cd10  CBillboardList2d_DeleteArray
//   [ ] 0x5cdb8  FUN_0005cdb8  [dead]
//   [ ] 0x5cde0  FUN_0005cde0  [dead]
//   [x] 0x5ce10  CBillboardList2d_RefreshAllItemShapes_maybe  (CreateBillboards)
//   [x] 0x5ceb8  CBillboardList2d_vfA8  (SetColor)
//   [x] 0x5cf50  CBillboardList2d_vfD8  (HideBillboard)
//   [x] 0x5cf80  CBillboardList2d_vfD4  (ShowBillboard)
//   [x] 0x5cfb0  CBillboardList2d_RefreshItemShape_maybe  (CreateBillboard)
//   [x] 0x5d0c8  CBillboardList2d_RemoveBillboard
//   [x] 0x5d228  CBillboardList2d_vfC8  (DisableStretchToAspectRatio, the header)
//   [x] 0x5d240  CBillboardList2d_vfC4  (EnableStretchToAspectRatio, the header)
//   [ ] 0x5d258  CBillboardList2d_Construct_2  [dead]
//   [x] 0x5d320  CBillboardList2d_ResetItemBrush  (RemoveTextureFromBillboard)
//   [x] 0x5d428  CBillboardList2d_vfB8  (LinkTextureToBillboard)
//   [x] 0x5d518  CBillboardList2d_Draw  (Render)
//   [x] 0x5d7c0  CBillboardList2d_GetBoundingRect  (GetBoundingBox)
//   [x] 0x5d9d0  CBillboardList2d_AddBillboard
//   [x] 0x5dd50  CBillboardList2d_vfC0  (SetTexture)
//   [x] 0x5dea0  CBillboardList2d_RemoveTexture
//   [x] 0x5dff8  CBillboardList2d_vf58  (RecursiveNodeReach)
//   [ ] 0x5e0e0  CBillboardList2d_Save
//   [x] 0x5e6a0  CBillboardList2d_Load
//   [x] 0x5ee28  CBillboardList2d_SetBillboardCount  (CreateBillboardsList)
//   [x] 0x5f210  CBillboardList2d_vf80  (Scale)
//   [x] 0x5f278  CBillboardList2d_Create
//   [x] 0x5f350  CBillboardList2d_CreateArray
//   [x] 0x5f4c8  CBillboardList2d_ResetRuntime_maybe  (FreeMemory)
//   [x] 0x5f5b8  CBillboardList2d_ResetTextureSlots_maybe  (CreateTexturesList)
//   [x] 0x5f708  CColorTextButton2d_Delete  (CColorTextButton2d's Delete factory (CColorTextButton2d.h))
//   [ ] 0x5f758  FUN_0005f758  [dead]
//
//   [x] 0x997580  CBillboardList2d_GetClassType  [inline]
//   [x] 0x997588  CBillboardList2d_GetClassID  [inline]
//   [x] 0x997590  CBillboardList2d_vfB4  [inline]  (SetUVs)
//   [x] 0x997638  CBillboardList2d_vfB0  [inline]  (UpdateUVs)
//   [x] 0x9976a8  CBillboardList2d_IsKindOfClass  [inline]
//   [x] 0x9976d0  CBillboardList2d_DeletingDestructor  [inline]
//   [x] 0x997818  CBillboardList2d_Destructor  [inline]
#include "k2000/graphical/fx/CBillboardList2d.h"

#include <cstring>

#include "Renderware/rt2d/Rt2d.h"
#include "Renderware/rwcore/RwStream.h"
#include "Renderware/rwcore/RwTexture.h"
#include "crt/ppc_ops.h"
#include "k2000/graphical/ui/CManager2d.h"
#include "k2000/io/IKFile.h"
#include "k2000/memory/Mem.h"
#include "k2000/misc/Engine.h"

// C2.8 port-rest R02. No game file holds a CBillboardList2d; ported from the disassembly. The element sizes are the
// native ones (sizeof(T)) where the PS3 code has 4-byte pointers.

namespace {
// The TVector push every Add inlines: when full, the capacity grows to the length + 5 (5 when that wraps to 0).
template <class T>
void PushBack(TVector<T, 5>& vector, const T& value) {
    if (vector.m_ui32NbElt == vector.m_ui32NbUsedElt) {
        uint32_t capacity = vector.m_ui32NbUsedElt + 5;
        if (capacity == 0) capacity = 5;
        vector.m_pBlock = static_cast<T*>(Mem_ReallocAligned16(vector.m_pBlock, capacity * static_cast<uint32_t>(sizeof(T))));
        vector.m_ui32NbElt = capacity;
    }
    vector.m_pBlock[vector.m_ui32NbUsedElt] = value;
    ++vector.m_ui32NbUsedElt;
}

// The resize Load and CreateBillboardsList inline: a fresh block of 5 (the old block is not freed), grown to
// (count / 5) x 5 + 5 when 5 is not enough, the length set to `count`.
template <class T>
void ResetToCount(TVector<T, 5>& vector, uint32_t count) {
    vector.m_ui32NbElt = 5;
    vector.m_pBlock = static_cast<T*>(Mem_AllocAligned16(5 * static_cast<uint32_t>(sizeof(T))));
    if (vector.m_ui32NbElt < count) {
        uint32_t capacity = (count / 5) * 5 + 5;
        if (capacity == 0) capacity = 5;
        vector.m_pBlock = static_cast<T*>(Mem_ReallocAligned16(vector.m_pBlock, capacity * static_cast<uint32_t>(sizeof(T))));
        vector.m_ui32NbElt = capacity;
    }
    vector.m_ui32NbUsedElt = count;
}

// A vector's block freed (when there is one) and the vector emptied: the length and the block cleared.
template <class T>
void FreeVector(TVector<T, 5>& vector) {
    if (vector.m_pBlock != nullptr) {
        Mem_FreeAligned16(vector.m_pBlock);
        vector.m_pBlock = nullptr;
    }
    vector.m_ui32NbUsedElt = 0;
    vector.m_pBlock = nullptr;
}

// Entry `index` removed, the later ones moved down (memmove of length - 1 - index entries), the length lowered.
template <class T>
void EraseAt(TVector<T, 5>& vector, uint32_t index) {
    const uint32_t last = vector.m_ui32NbUsedElt - 1;
    vector.m_ui32NbUsedElt = last;
    std::memmove(&vector.m_pBlock[index], &vector.m_pBlock[index] + 1, (last - index) * sizeof(T));
}

// The default UVs of a new billboard: (0, 1), (1, 1), (1, 0), (0, 0).
CBillboardList2d::BillboardUVs DefaultUVs() {
    CBillboardList2d::BillboardUVs uvs;
    uvs.m_aUV[0] = {0.0f, 1.0f};
    uvs.m_aUV[1] = {1.0f, 1.0f};
    uvs.m_aUV[2] = {1.0f, 0.0f};
    uvs.m_aUV[3] = {0.0f, 0.0f};
    return uvs;
}

RwRGBA* AsRGBA(uint32_t* color) { return reinterpret_cast<RwRGBA*>(color); }
RwV2d* AsV2d(CVector2* v) { return reinterpret_cast<RwV2d*>(v); }

// (float) of an unsigned word (fcfid of the zero-extended register, frsp).
float U32ToFloat(uint32_t value) { return static_cast<float>(static_cast<double>(value)); }
}  // namespace

// 0x0005f278 CBillboardList2d_Create
CBillboardList2d::CBillboardList2d() {
    m_vpBillboards = {nullptr, 5, 0};
    m_vi32LinkedTextures = {nullptr, 5, 0};
    m_vpBrushes = {nullptr, 5, 0};
    m_vbShowBillboards = {nullptr, 5, 0};
    m_vpTextures = {nullptr, 5, 0};
    m_vvUVs = {nullptr, 5, 0};
    m_f32Spacing = 0.0f;
    m_ui8AlignType = 0;
    m_vBillboardsSize = {0.0f, 0.0f};
    m_Color = 0;
}

// 0x00997818 CBillboardList2d_Destructor
CBillboardList2d::~CBillboardList2d() {
    FreeVector(m_vvUVs);
    FreeVector(m_vpTextures);
    FreeVector(m_vbShowBillboards);
    FreeVector(m_vpBrushes);
    FreeVector(m_vi32LinkedTextures);
    FreeVector(m_vpBillboards);
}

// 0x0005c920 CBillboardList2d_FreeTextures_maybe
void CBillboardList2d::DestroyTextures() {
    const uint32_t count = m_vpTextures.m_ui32NbUsedElt;
    for (uint32_t i = 0; i < count; ++i) {
        if (m_vpTextures.m_pBlock[i] != nullptr) RwTextureDestroy(m_vpTextures.m_pBlock[i]);
    }
    FreeVector(m_vpTextures);
}

// 0x0005c9d0 CBillboardList2d_ClearBillboards
void CBillboardList2d::DestroyBillboards() {
    const uint32_t count = m_vpBillboards.m_ui32NbUsedElt;
    for (uint32_t i = 0; i < count; ++i) {
        if (m_vpBillboards.m_pBlock[i] != nullptr) Rt2dPathDestroy(m_vpBillboards.m_pBlock[i]);
        if (m_vpBrushes.m_pBlock[i] != nullptr) Rt2dBrushDestroy(m_vpBrushes.m_pBlock[i]);
    }
    FreeVector(m_vpBillboards);
    FreeVector(m_vi32LinkedTextures);
    FreeVector(m_vpBrushes);
    FreeVector(m_vbShowBillboards);
    FreeVector(m_vvUVs);
}

// 0x0005f4c8 CBillboardList2d_ResetRuntime_maybe
void CBillboardList2d::FreeMemory() {
    IKNode2d::FreeMemory();  // 0x00069ce8
    DestroyBillboards();     // 0x0005c9d0
    DestroyTextures();       // inlined
    m_f32Spacing = 0.0f;
    m_ui8AlignType = 0;
    m_vBillboardsSize = {0.0f, 0.0f};
    m_Color = 0;
}

// 0x0005e6a0 CBillboardList2d_Load
int32_t CBillboardList2d::Load(IKFile* file, int32_t type) {
    IKNode2d::Load(file, type);  // 0x00069da8
    uint32_t count = 0;
    ReadU32LE(file, &count);
    ResetToCount(m_vpBillboards, count);
    ResetToCount(m_vi32LinkedTextures, count);
    ResetToCount(m_vpBrushes, count);
    ResetToCount(m_vbShowBillboards, count);
    ResetToCount(m_vvUVs, count);
    for (uint32_t i = 0; i < count; ++i) {
        m_vpBillboards.m_pBlock[i] = nullptr;
        ReadS32LE(file, &m_vi32LinkedTextures.m_pBlock[i]);
        RwStream* stream = file->m_pRwStream;
        RwStreamFindChunk(stream, 0x1a2, nullptr, nullptr);  // result ignored
        m_vpBrushes.m_pBlock[i] = Rt2dBrushStreamRead(stream);
        ReadU8(file, &m_vbShowBillboards.m_pBlock[i]);
        for (CVector2& uv : m_vvUVs.m_pBlock[i].m_aUV) {  // one 0x20-byte read, every word swapped
            ReadF32LE(file, &uv.m_fX);
            ReadF32LE(file, &uv.m_fY);
        }
    }
    ReadRaw(file, &m_Color, 4);
    uint32_t textures = 0;
    ReadU32LE(file, &textures);
    ResetToCount(m_vpTextures, textures);
    for (uint32_t i = 0; i < textures; ++i) {
        IKFile_ReadTextureRef(file, reinterpret_cast<void**>(&m_vpTextures.m_pBlock[i]), 0);  // 0x0004d218
        if (m_vpTextures.m_pBlock[i] != nullptr) ++m_vpTextures.m_pBlock[i]->refCount;      // RwTexture +0x54
    }
    ReadF32LE(file, &m_vBillboardsSize.m_fX);  // one 8-byte read, both words swapped
    ReadF32LE(file, &m_vBillboardsSize.m_fY);
    ReadU8(file, &m_ui8AlignType);
    ReadF32LE(file, &m_f32Spacing);
    CreateBillboards();  // vt+0xa4
    for (uint32_t i = 0; i < count; ++i) {
        const int32_t texture = m_vi32LinkedTextures.m_pBlock[i];
        if (texture > -1) LinkTextureToBillboard(static_cast<uint32_t>(texture), i);  // vt+0xb8
    }
    return 1;
}

// 0x0005dff8 CBillboardList2d_vf58. The bound is the brush count, re-read after each SetTexture.
void CBillboardList2d::RecursiveNodeReach(uint8_t what, void* data) {
    if (what != 7) return;
    if (m_vpBrushes.m_ui32NbUsedElt == 0) return;
    uint32_t i = 0;
    do {
        RwTexture* texture = m_vpTextures.m_ui32NbUsedElt > i ? m_vpTextures.m_pBlock[i] : nullptr;
        if (texture == data) SetTexture(nullptr, i);  // vt+0xc0
        ++i;
    } while (m_vpBrushes.m_ui32NbUsedElt > i);
}

// 0x0005d7c0 CBillboardList2d_GetBoundingRect. The half sizes and the spacing are divided by the aspect unless
// stretched; alignments 2 and 3 read the spacing as stored. Alignments 0 and 3 fuse their last multiply-add.
void CBillboardList2d::GetBoundingBox(CBox2D* box) const {
    float halfWidth;
    float halfHeight;
    float spacing;
    if (((m_baFlags >> 2) & 1u) == 0) {
        const float inverse = 0x1p+0f / g_pEngine->m_manager2d->m_fAspect;  // engine +0x38, +0x18
        halfWidth = inverse * 0x1p-1f * m_vBillboardsSize.m_fX;
        spacing = inverse * m_f32Spacing;
        halfHeight = m_vBillboardsSize.m_fY * 0x1p-1f;
    } else {
        halfWidth = m_vBillboardsSize.m_fX * 0x1p-1f;
        halfHeight = m_vBillboardsSize.m_fY * 0x1p-1f;
        spacing = m_f32Spacing;
    }
    const float steps = U32ToFloat(m_vpBillboards.m_ui32NbUsedElt - 1u);
    switch (m_ui8AlignType) {
    case 0:
        box->m_inf.m_fX = m_vPosition.m_fX - halfWidth;
        box->m_inf.m_fY = m_vPosition.m_fY - halfHeight;
        box->m_sup.m_fY = halfHeight + m_vPosition.m_fY;
        box->m_sup.m_fX = ppc::fmadds(spacing + (halfWidth + halfWidth), steps, halfWidth + m_vPosition.m_fX);
        break;
    case 1:
        box->m_inf.m_fY = m_vPosition.m_fY - halfHeight;
        box->m_sup.m_fY = halfHeight + m_vPosition.m_fY;
        box->m_inf.m_fX = (m_vPosition.m_fX - halfWidth) - (spacing + (halfWidth + halfWidth)) * steps;
        box->m_sup.m_fX = halfWidth + m_vPosition.m_fX;
        break;
    case 2:
        box->m_inf.m_fX = m_vPosition.m_fX - halfWidth;
        box->m_sup.m_fX = halfWidth + m_vPosition.m_fX;
        box->m_inf.m_fY = (m_vPosition.m_fY - halfHeight) - ((halfHeight + halfHeight) + m_f32Spacing) * steps;
        box->m_sup.m_fY = halfHeight + m_vPosition.m_fY;
        break;
    case 3:
        box->m_inf.m_fX = m_vPosition.m_fX - halfWidth;
        box->m_inf.m_fY = m_vPosition.m_fY - halfHeight;
        box->m_sup.m_fX = halfWidth + m_vPosition.m_fX;
        box->m_sup.m_fY = ppc::fmadds((halfHeight + halfHeight) + m_f32Spacing, steps, halfHeight + m_vPosition.m_fY);
        break;
    default:
        break;
    }
}

// 0x0005f210 CBillboardList2d_vf80
void CBillboardList2d::Scale(const CVector2& scale) {
    CVector2 size;
    size.m_fY = m_vBillboardsSize.m_fY * scale.m_fY;
    size.m_fX = m_vBillboardsSize.m_fX * scale.m_fX;
    SetBillboardsSize(&size);  // vt+0xac
}

// 0x0005d518 CBillboardList2d_Draw (returns 1 when drawn; the slot is void here)
void CBillboardList2d::Render(IKTime* /*time*/) {
    if ((m_baFlags & 0x2u) == 0) return;
    const uint32_t count = m_vpBillboards.m_ui32NbUsedElt;
    const float x = m_vPosition.m_fX;
    const float y = m_vPosition.m_fY;
    const float aspect = g_pEngine->m_manager2d->m_fAspect;  // engine +0x38, +0x18
    float width;
    float height;
    if (((m_baFlags >> 2) & 1u) != 0) {
        width = aspect * m_vBillboardsSize.m_fX;
        height = m_vBillboardsSize.m_fY;
    } else {
        height = m_vBillboardsSize.m_fY;
        width = m_vBillboardsSize.m_fX;
    }
    Rt2dCTMPush();
    Rt2dCTMTranslate(x * aspect, y);
    for (uint32_t i = 0; i < count; ++i) {
        Rt2dPath* path = m_vpBillboards.m_pBlock[i];
        Rt2dBrush* brush = m_vpBrushes.m_pBlock[i];
        if (path == nullptr || brush == nullptr || m_vbShowBillboards.m_pBlock[i] == 0) continue;
        Rt2dCTMPush();
        const float step = U32ToFloat(i);
        switch (m_ui8AlignType) {
        case 0: Rt2dCTMTranslate(step * (width + m_f32Spacing), 0.0f); break;
        case 1: Rt2dCTMTranslate(-(step * (width + m_f32Spacing)), 0.0f); break;
        case 2: Rt2dCTMTranslate(0.0f, -(step * (height + m_f32Spacing))); break;
        case 3: Rt2dCTMTranslate(0.0f, step * (height + m_f32Spacing)); break;
        default: break;
        }
        Rt2dCTMRotate(m_f32RotateAngle);
        Rt2dCTMScale(width, height);
        _rt2dPathRenderChain(path, brush);  // 0x0070cad0 (TocBridge__rt2dPathFillChain_maybe)
        Rt2dCTMPop();
    }
    Rt2dCTMPop();
}

// 0x0005ee28 CBillboardList2d_SetBillboardCount
void CBillboardList2d::CreateBillboardsList(uint32_t count) {
    DestroyBillboards();  // 0x0005c9d0
    ResetToCount(m_vpBillboards, count);
    ResetToCount(m_vi32LinkedTextures, count);
    ResetToCount(m_vpBrushes, count);
    ResetToCount(m_vbShowBillboards, count);
    ResetToCount(m_vvUVs, count);
    for (uint32_t i = 0; i < count; ++i) {
        m_vpBillboards.m_pBlock[i] = nullptr;
        m_vi32LinkedTextures.m_pBlock[i] = -1;
        m_vpBrushes.m_pBlock[i] = Rt2dBrushCreate();
        m_vbShowBillboards.m_pBlock[i] = 0;
        m_vvUVs.m_pBlock[i] = DefaultUVs();
    }
}

// 0x0005f5b8 CBillboardList2d_ResetTextureSlots_maybe: the slots zeroed (memset) when there are any.
void CBillboardList2d::CreateTexturesList(uint32_t count) {
    DestroyTextures();  // inlined
    m_vpTextures.m_ui32NbElt = 5;
    m_vpTextures.m_ui32NbUsedElt = 0;
    m_vpTextures.m_pBlock = nullptr;
    m_vpTextures.m_pBlock = static_cast<RwTexture**>(Mem_AllocAligned16(5 * static_cast<uint32_t>(sizeof(RwTexture*))));
    if (m_vpTextures.m_ui32NbElt < count) {
        uint32_t capacity = (count / 5) * 5 + 5;
        if (capacity == 0) capacity = 5;
        m_vpTextures.m_pBlock = static_cast<RwTexture**>(
            Mem_ReallocAligned16(m_vpTextures.m_pBlock, capacity * static_cast<uint32_t>(sizeof(RwTexture*))));
        m_vpTextures.m_ui32NbElt = capacity;
    }
    m_vpTextures.m_ui32NbUsedElt = count;
    if (count != 0) std::memset(m_vpTextures.m_pBlock, 0, count * sizeof(RwTexture*));
}

// 0x0005d9d0 CBillboardList2d_AddBillboard
void CBillboardList2d::AddBillboard() {
    PushBack(m_vpBillboards, static_cast<Rt2dPath*>(nullptr));
    const uint32_t index = m_vpBillboards.m_ui32NbUsedElt - 1;
    PushBack(m_vi32LinkedTextures, -1);
    Rt2dBrush* brush = Rt2dBrushCreate();
    Rt2dBrushSetRGBA(brush, AsRGBA(&m_Color), AsRGBA(&m_Color), AsRGBA(&m_Color), AsRGBA(&m_Color));
    PushBack(m_vpBrushes, brush);
    PushBack(m_vvUVs, DefaultUVs());
    CreateBillboard(index);  // vt+0xa0, the answer unused
    PushBack(m_vbShowBillboards, static_cast<uint8_t>(1));
}

// 0x0005d0c8 CBillboardList2d_RemoveBillboard
void CBillboardList2d::RemoveBillboard(uint32_t index) {
    if (m_vpBillboards.m_pBlock[index] != nullptr) Rt2dPathDestroy(m_vpBillboards.m_pBlock[index]);
    EraseAt(m_vpBillboards, index);
    EraseAt(m_vi32LinkedTextures, index);
    if (m_vpBrushes.m_pBlock[index] != nullptr) Rt2dBrushDestroy(m_vpBrushes.m_pBlock[index]);
    EraseAt(m_vpBrushes, index);
    EraseAt(m_vbShowBillboards, index);
}

// 0x0005cb70 CBillboardList2d_vf98
void CBillboardList2d::AddTexture() { PushBack(m_vpTextures, static_cast<RwTexture*>(nullptr)); }

// 0x0005dea0 CBillboardList2d_RemoveTexture
void CBillboardList2d::RemoveTexture(uint32_t index) {
    const uint32_t count = m_vpBillboards.m_ui32NbUsedElt;
    for (uint32_t i = 0; i < count; ++i) {
        const int32_t linked = m_vi32LinkedTextures.m_pBlock[i];
        if (static_cast<int32_t>(index) < linked) {
            m_vi32LinkedTextures.m_pBlock[i] = linked - 1;
        } else if (static_cast<int32_t>(index) == linked) {
            RemoveTextureFromBillboard(i);  // vt+0xbc
        }
    }
    if (m_vpTextures.m_pBlock[index] != nullptr) RwTextureDestroy(m_vpTextures.m_pBlock[index]);
    EraseAt(m_vpTextures, index);
}

// 0x0005cfb0 CBillboardList2d_RefreshItemShape_maybe
int32_t CBillboardList2d::CreateBillboard(uint32_t index) {
    if (m_vpBillboards.m_ui32NbUsedElt <= index) return 0;
    Rt2dBrush* brush = m_vpBrushes.m_pBlock[index];
    if (brush == nullptr) return 0;
    BillboardUVs* uvs = &m_vvUVs.m_pBlock[index];
    Rt2dBrushSetUV(brush, AsV2d(&uvs->m_aUV[0]), AsV2d(&uvs->m_aUV[1]), AsV2d(&uvs->m_aUV[2]), AsV2d(&uvs->m_aUV[3]));
    Rt2dPath** slot = &m_vpBillboards.m_pBlock[index];
    if (*slot != nullptr) Rt2dPathDestroy(*slot);
    *slot = Rt2dPathCreate();
    if (*slot == nullptr) return 0;
    Rt2dPathEmpty(*slot);
    Rt2dPathRect(*slot, -0x1p-1f, -0x1p-1f, 0x1p+0f, 0x1p+0f);  // TOC -0x70fc, -0x70f8
    return 1;
}

// 0x0005ce10 CBillboardList2d_RefreshAllItemShapes_maybe
int32_t CBillboardList2d::CreateBillboards() {
    const uint32_t count = m_vpBillboards.m_ui32NbUsedElt;
    uint32_t all = 1;
    for (uint32_t i = 0; i < count; ++i) all &= static_cast<uint8_t>(CreateBillboard(i));  // vt+0xa0
    return static_cast<uint8_t>(all);
}

// 0x0005ceb8 CBillboardList2d_vfA8
void CBillboardList2d::SetColor(const uint32_t* color) {
    m_Color = *color;
    const uint32_t count = m_vpBillboards.m_ui32NbUsedElt;
    for (uint32_t i = 0; i < count; ++i) {
        Rt2dBrushSetRGBA(m_vpBrushes.m_pBlock[i], AsRGBA(&m_Color), AsRGBA(&m_Color), AsRGBA(&m_Color), AsRGBA(&m_Color));
    }
}

// 0x00997638 CBillboardList2d_vfB0
void CBillboardList2d::UpdateUVs(uint32_t index) {
    if (m_vpBillboards.m_ui32NbUsedElt <= index) return;
    BillboardUVs* uvs = &m_vvUVs.m_pBlock[index];
    Rt2dBrushSetUV(m_vpBrushes.m_pBlock[index], AsV2d(&uvs->m_aUV[0]), AsV2d(&uvs->m_aUV[1]), AsV2d(&uvs->m_aUV[2]),
                   AsV2d(&uvs->m_aUV[3]));
}

// 0x00997590 CBillboardList2d_vfB4
void CBillboardList2d::SetUVs(uint32_t index, const BillboardUVs* uvs) {
    if (m_vpBillboards.m_ui32NbUsedElt <= index) return;
    m_vvUVs.m_pBlock[index] = *uvs;
    UpdateUVs(index);  // vt+0xb0
}

// 0x0005d428 CBillboardList2d_vfB8
int32_t CBillboardList2d::LinkTextureToBillboard(uint32_t texture, uint32_t billboard) {
    if (m_vpTextures.m_ui32NbUsedElt <= texture) return 0;
    if (m_vpBillboards.m_ui32NbUsedElt <= billboard) return 0;
    Rt2dBrush* brush = m_vpBrushes.m_pBlock[billboard];
    if (brush == nullptr) return 0;
    Rt2dBrushSetTexture(brush, m_vpTextures.m_pBlock[texture]);
    m_vi32LinkedTextures.m_pBlock[billboard] = static_cast<int32_t>(texture);
    m_vbShowBillboards.m_pBlock[billboard] = 1;
    return 1;
}

// 0x0005d320 CBillboardList2d_ResetItemBrush
int32_t CBillboardList2d::RemoveTextureFromBillboard(uint32_t billboard) {
    if (m_vpBillboards.m_ui32NbUsedElt <= billboard) return 0;
    Rt2dBrush** slot = &m_vpBrushes.m_pBlock[billboard];
    if (*slot != nullptr) Rt2dBrushDestroy(*slot);
    *slot = Rt2dBrushCreate();
    m_vi32LinkedTextures.m_pBlock[billboard] = -1;
    const uint32_t color = m_Color;
    SetColor(&color);  // vt+0xa8
    return static_cast<uint8_t>(CreateBillboard(billboard));  // vt+0xa0
}

// 0x0005dd50 CBillboardList2d_vfC0
int32_t CBillboardList2d::SetTexture(RwTexture* texture, uint32_t index) {
    if (m_vpTextures.m_ui32NbUsedElt <= index) return 0;
    RwTexture** slot = &m_vpTextures.m_pBlock[index];
    if (*slot == texture) return 1;
    if (*slot != nullptr) RwTextureDestroy(*slot);
    *slot = texture;
    if (texture != nullptr) ++texture->refCount;  // RwTexture +0x54
    const uint32_t count = m_vpBillboards.m_ui32NbUsedElt;
    for (uint32_t i = 0; i < count; ++i) {
        if (m_vi32LinkedTextures.m_pBlock[i] == static_cast<int32_t>(index)) LinkTextureToBillboard(index, i);  // vt+0xb8
    }
    return 1;
}

// 0x0005cf80 CBillboardList2d_vfD4
int32_t CBillboardList2d::ShowBillboard(uint32_t index) {
    if (m_vpBillboards.m_ui32NbUsedElt < index) return 0;
    m_vbShowBillboards.m_pBlock[index] = 1;
    return 1;
}

// 0x0005cf50 CBillboardList2d_vfD8
int32_t CBillboardList2d::HideBillboard(uint32_t index) {
    if (m_vpBillboards.m_ui32NbUsedElt < index) return 0;
    m_vbShowBillboards.m_pBlock[index] = 0;
    return 1;
}
