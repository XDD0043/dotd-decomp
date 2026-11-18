// PS3_CKInputBlockPosition.cpp - reconstructed original translation unit 0x20ddd8-0x20e4b0 (GAME_TOC1, main_toc1), 19 functions, 19 live.
// Primary class: PS3_CKInputBlockPosition  key 0x678c  category Logic  size 0x2c  vtable 0xb1f800
// Other owners: RegisterPS3 (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x20ddd8  PS3_CKInputBlockPosition_Delete  (the registry factory: DOTD_DECLARE_FACTORIES)
//   [x] 0x20de28  PS3_CKInputBlockPosition_vf58
//   [x] 0x20dfd8  PS3_CKInputBlockPosition_OnDeactivate_maybe  (KBase620C::OnDeactivate 0x20da38 (the slot calls it))
//   [x] 0x20e000  PS3_CKInputBlockPosition_OnActivate_maybe  (KBase620C::OnActivate 0x20da80 (the slot calls it))
//   [x] 0x20e028  PS3_CKInputBlockPosition_Load
//   [ ] 0x20e0d0  PS3_CKInputBlockPosition_Save
//   [x] 0x20e0f8  PS3_CKInputBlockPosition_RecursiveRegistration  (KBase620C's vf24 0x20dc20: KBase628C's)
//   [x] 0x20e120  PS3_CKInputBlockPosition_Destroy  (KBase620C's vf10 0x20dc48: KBase628C's Destroy)
//   [x] 0x20e148  PS3_CKInputBlockPosition_DeletingDestructor  (the destructor; delete)
//   [x] 0x20e190  PS3_CKInputBlockPosition_Destructor  (C++ destructor chain: vtable stores only)
//   [x] 0x20e1c0  PS3_CKInputBlockPosition_DestructBody  (C++ destructor chain: vtable stores only)
//   [x] 0x20e1f0  PS3_CKInputBlockPosition_Construct  (header)
//   [x] 0x20e228  PS3_CKInputBlockPosition_Construct_2  (the same as 0x20e1f0 PS3_CKInputBlockPosition_Construct)
//   [x] 0x20e260  PS3_CKInputBlockPosition_DeleteArray  (the registry factory: DOTD_DECLARE_FACTORIES)
//   [x] 0x20e300  RegisterPS3_CKInputBlockPositionClass  (the registration: DOTD_DECLARE_FACTORIES, Kp3Ported.inc by gen_kp3_stubs)
//   [ ] 0x20e388  _GLOBAL__D_20e388
//   [ ] 0x20e398  _GLOBAL__I_20e398
//   [x] 0x20e3a8  PS3_CKInputBlockPosition_Create  (the registry factory: DOTD_DECLARE_FACTORIES)
//   [x] 0x20e400  PS3_CKInputBlockPosition_CreateArray  (the registry factory: DOTD_DECLARE_FACTORIES)
//
//   [ ] 0x9b1828  PS3_CKInputBlockPosition_vf74  [inline]
//   [ ] 0x9b1830  PS3_CKInputBlockPosition_vf78  [inline]
//   [ ] 0x9b1838  PS3_CKInputBlockPosition_vf7C  [inline]
//   [ ] 0x9b1840  PS3_CKInputBlockPosition_vf80  [inline]
//   [ ] 0x9b1848  PS3_CKInputBlockPosition_vf88  [inline]
//   [ ] 0x9b1850  PS3_CKInputBlockPosition_vf8C  [inline]
//   [ ] 0x9b1858  PS3_CKInputBlockPosition_vf90  [inline]
//   [ ] 0x9b1860  PS3_CKInputBlockPosition_vf94  [inline]
//   [ ] 0x9b1868  PS3_CKInputBlockPosition_vf98  [inline]
//   [ ] 0x9b1890  PS3_CKInputBlockPosition_vfAC  [inline]
//   [ ] 0x9b1898  PS3_CKInputBlockPosition_vfB0  [inline]
//   [ ] 0x9b18a0  PS3_CKInputBlockPosition_vfB4  [inline]
//   [ ] 0x9b18a8  PS3_CKInputBlockPosition_vfB8  [inline]
//   [ ] 0x9b18b0  PS3_CKInputBlockPosition_vfBC  [inline]
//   [ ] 0x9b18b8  PS3_CKInputBlockPosition_vfC0  [inline]
//   [x] 0x9b1bc0  PS3_CKInputBlockPosition_IsKindOfClass  [inline]  (header)
//   [ ] 0x9b1c08  PS3_CKInputBlockPosition_GetClassType  [inline]
//   [ ] 0x9b1c10  PS3_CKInputBlockPosition_GetClassID  [inline]
//   [ ] 0x9b1c18  KStub_Nop_9b1c18  [inline]
//   [ ] 0x9b1c20  KStub_Nop_9b1c20  [inline]
//   [ ] 0x9b1c28  KStub_Nop_9b1c28  [inline]
#include "k2000/logic/input/PS3_CKInputBlockPosition.h"

#include "crt/ppc_ops.h"
#include "k2000/io/IKFile.h"
#include "k2000/logic/input/InputBlockQueries.h"

// 0x0020e028 PS3_CKInputBlockPosition_Load
int32_t PS3_CKInputBlockPosition::Load(IKFile* file, int32_t type) {
    KBase620C::Load(file, type);  // 0x0020db98
    if (type != K_LEVEL_PLATEFORMS) return 1;
    ReadF32LE(file, &m_fSpeed);
    return 1;
}

// 0x0020de28 PS3_CKInputBlockPosition_vf58: the position in pixels (the "no position" (-1, -1) of 0xcea9b0 as it is,
// static initialiser 0x20e300), moved by speed x dt along stick directions 1 - 0 (x) and 2 - 3 (y) (fmadds), kept
// within [0, size] (the vector 0x00c50dc4: 0, 0; fcmpu + bgt: a NaN takes the bound) and stored normalised.
void PS3_CKInputBlockPosition::Update(float dt) {
    constexpr float kNone = -1.0f;  // 0xcea9b0 / 0xcea9b4 (TOC -0xe0c)
    const float step = dt * m_fSpeed;
    float x;
    float y;
    if (m_fX == kNone && m_fY == kNone) {  // fcmpu + bne: a NaN takes the product
        x = kNone;
        y = kNone;
    } else {
        x = m_fX * m_fWidth;
        y = m_fY * m_fHeight;
    }
    const int32_t dx = static_cast<int32_t>(InputBlock_IsStickDirectionPressed(this, 1)) -
                       static_cast<int32_t>(InputBlock_IsStickDirectionPressed(this, 0));  // 0x0020a158
    x = ppc::fmadds(step, static_cast<float>(static_cast<double>(static_cast<int64_t>(dx))), x);
    const int32_t dy = static_cast<int32_t>(InputBlock_IsStickDirectionPressed(this, 2)) -
                       static_cast<int32_t>(InputBlock_IsStickDirectionPressed(this, 3));
    y = ppc::fmadds(step, static_cast<float>(static_cast<double>(static_cast<int64_t>(dy))), y);
    float cx = m_fWidth;
    if (!(x > cx)) cx = x;
    float cy = m_fHeight;
    if (!(y > cy)) cy = y;
    if (!(cx > 0.0f)) cx = 0.0f;
    if (!(cy > 0.0f)) cy = 0.0f;
    m_fX = cx / m_fWidth;
    m_fY = cy / m_fHeight;
}
