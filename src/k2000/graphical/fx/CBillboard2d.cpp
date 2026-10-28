// CBillboard2d.cpp - reconstructed original translation unit 0x5af70-0x5be10 (GAME_TOC1, main_toc1), 21 functions, 18 live.
// Primary class: CBillboard2d  key 0x3cd  category Graphical  size 0x84  vtable 0xb156e8
// Other owners: DrawAnimatedUIBillboardWidget (1), CBillboardButton2d (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x5af70  CBillboard2d_Delete
//   [x] 0x5afc0  CBillboard2d_vf80
//   [ ] 0x5afe8  CBillboard2d_GetScreenRect_maybe  [dead]
//   [x] 0x5b098  CBillboard2d_SetAnimTime_maybe
//   [x] 0x5b118  CBillboard2d_SetSpriteSheetRows_maybe
//   [x] 0x5b158  CBillboard2d_SetSpriteSheetColumns_maybe
//   [ ] 0x5b198  CBillboard2d_GetBoundingRect
//   [ ] 0x5b200  RegisterCBillboard2dType
//   [ ] 0x5b278  _GLOBAL__I_5b278
//   [ ] 0x5b288  CBillboard2d_vf58
//   [ ] 0x5b318  CBillboard2d_RecursiveRegistration
//   [ ] 0x5b3a8  CBillboard2d_Destroy
//   [x] 0x5b3f0  CBillboard2d_DeleteArray
//   [x] 0x5b498  CBillboard2d_Create
//   [x] 0x5b508  DrawAnimatedUIBillboardWidget
//   [x] 0x5b768  CBillboard2d_Load
//   [ ] 0x5b9b8  CBillboard2d_Save
//   [x] 0x5bbe0  CBillboard2d_CreateArray
//   [ ] 0x5bcc8  CBillboard2d_ContainsScreenPoint_maybe  [dead]
//   [ ] 0x5bdb0  CBillboardButton2d_Delete
//   [ ] 0x5be00  FUN_0005be00  [dead]
//
//   [ ] 0x9972e8  CBillboard2d_GetClassGroup_Thunk  [inline]
//   [ ] 0x9972f0  CBillboard2d_GetClassType  [inline]
//   [ ] 0x9972f8  CBillboard2d_GetClassId_Thunk  [inline]
//   [ ] 0x997300  CBillboard2d_GetClassID  [inline]
//   [ ] 0x997308  CBillboard2d_vf80_Thunk  [inline]
//   [ ] 0x997398  CBillboard2d_LevelReset_Thunk  [inline]
//   [ ] 0x9973a0  CBillboard2d_ClearReferences_Thunk  [inline]
//   [x] 0x9973a8  CBillboard2d_IsKindOfClass  [inline]
//   [x] 0x9973d0  CBillboard2d_Load_Thunk  [inline]
//   [ ] 0x9973d8  CBillboard2d_Save_Thunk  [inline]
//   [ ] 0x9973e0  CBillboard2d_DeletingDestructor_Thunk  [inline]
//   [ ] 0x9973e8  CBillboard2d_DeletingDestructor  [inline]
//   [ ] 0x997438  CBillboard2d_Destructor_Thunk  [inline]
//   [ ] 0x997440  CBillboard2d_Destructor  [inline]
#include "k2000/graphical/fx/CBillboard2d.h"

#include "crt/ppc_ops.h"
#include "k2000/io/IKFile.h"
#include "k2000/system/IKTime.h"

// 0x0005afc0 CBillboard2d_vf80
void CBillboard2d::Scale(const CVector2& scale) {
    m_vBillboardSize.m_fX = m_vBillboardSize.m_fX * scale.m_fX;  // fmuls
    m_vBillboardSize.m_fY = m_vBillboardSize.m_fY * scale.m_fY;
}

// 0x0005b098 CBillboard2d_SetAnimTime_maybe (TOC1 -0x7198 0.0f, -0x7194 1.0f). The stores are the
// assembly's order: UVs (0, 1) (1, 1) (1, 0) (0, 0).
void CBillboard2d::SetAnimTime(float duration) {
    m_fAnimDuration = duration;
    if (duration != 0.0f) return;
    m_pvUVs[3].m_fY = 0.0f;
    m_pvUVs[0].m_fX = 0.0f;
    m_pvUVs[2].m_fY = 0.0f;
    m_pvUVs[3].m_fX = 0.0f;
    m_pvUVs[2].m_fX = 0x1p+0f;
    m_pvUVs[0].m_fY = 0x1p+0f;
    m_pvUVs[1].m_fX = 0x1p+0f;
    m_pvUVs[1].m_fY = 0x1p+0f;
    ApplyUV();  // the brush part's vt+0x34 (0x66c70; no front-end class overrides it)
}

// 0x0005b118 CBillboard2d_SetSpriteSheetRows_maybe
void CBillboard2d::SetSpriteSheetRows(int32_t count) {
    m_unk7c = count != 0 ? count : 1;
    m_fAnimTime = 0.0f;  // the word 0
    m_ui32AnimFrame = 0;
}

// 0x0005b158 CBillboard2d_SetSpriteSheetColumns_maybe
void CBillboard2d::SetSpriteSheetColumns(int32_t count) {
    m_unk80 = count != 0 ? count : 1;
    m_fAnimTime = 0.0f;  // the word 0
    m_ui32AnimFrame = 0;
}

// 0x0005b768 CBillboard2d_Load: both base Loads for every type, then the level's own fields.
int32_t CBillboard2d::Load(IKFile* file, int32_t type) {
    IKNode2d::Load(file, type);
    IKBillboard2d::Load(file, type);
    if (type != K_LEVEL_PLATEFORMS) return 1;
    IKFile_ReadRef(file, &m_unk6c);
    ReadF32LE(file, &m_fAnimTime);
    ReadF32LE(file, &m_fAnimDuration);
    ReadU32LE(file, &m_ui32AnimFrame);
    ReadS32LE(file, &m_unk7c);
    ReadS32LE(file, &m_unk80);
    return 1;
}

// 0x0005b508 DrawAnimatedUIBillboardWidget (from the assembly). The cell count is converted from the
// unsigned product (fcfid of the zero-extended word), the frame with fctiwz.
void CBillboard2d::Render(IKTime* frameClock) {
    if (m_unk6c != nullptr) {
        IKNode2d* leader = static_cast<IKNode2d*>(m_unk6c);
        if (((leader->m_baFlags >> 1) & 1) != 0) {
            Enable();   // vt+0x64
        } else {
            Disable();  // vt+0x68
        }
    }
    if ((m_baFlags & 2) == 0) return;
    const float duration = m_fAnimDuration;
    if (duration != 0.0f) {
        float t = m_fAnimTime + frameClock->m_afDeltaTime[1];  // frame context +0x20
        m_fAnimTime = t;
        if (!(duration >= t)) {  // bge: the loop runs while duration < t
            do {
                t = t - duration;
            } while (duration < t);
            m_fAnimTime = t;
        }
        const uint32_t columns = static_cast<uint32_t>(m_unk7c);
        const uint32_t rows = static_cast<uint32_t>(m_unk80);
        const float cells = static_cast<float>(static_cast<double>(columns * rows));
        const uint32_t frame = static_cast<uint32_t>(ppc::fctiwz((t / duration) * cells));
        m_ui32AnimFrame = frame;
        const uint32_t row = frame / rows;
        const float invColumns = 0x1p+0f / static_cast<float>(static_cast<double>(columns));
        const float invRows = 0x1p+0f / static_cast<float>(static_cast<double>(rows));
        const float u0 = invColumns * static_cast<float>(static_cast<double>(row));
        const float u1 = invColumns * static_cast<float>(static_cast<double>(row + 1));
        const uint32_t column = frame - rows * row;
        const float v0 = invRows * static_cast<float>(static_cast<double>(column));
        const float v1 = invRows * static_cast<float>(static_cast<double>(column + 1));
        m_pvUVs[2].m_fX = u1;
        m_pvUVs[3].m_fX = u0;
        m_pvUVs[0].m_fX = u0;
        m_pvUVs[1].m_fX = u1;
        m_pvUVs[3].m_fY = v0;
        m_pvUVs[2].m_fY = v0;
        m_pvUVs[1].m_fY = v1;
        m_pvUVs[0].m_fY = v1;
        ApplyUV();  // the brush part's vt+0x34
    }
    DrawShapeWithTransform(m_f32RotateAngle, &m_vPosition, m_ui8CenterWAlign, m_ui8CenterHAlign, &m_v2ConstantScale);
}
