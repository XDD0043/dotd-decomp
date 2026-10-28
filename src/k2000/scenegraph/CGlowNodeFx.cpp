// CGlowNodeFx.cpp - reconstructed original translation unit 0xe3538-0xe4ed0 (GAME_TOC1, main_toc1), 14 functions, 13 live.
// Primary class: CGlowNodeFx  key 0x2cb  category SceneNode  size 0x5c  vtable 0xb18a30
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0xe3538  CGlowNodeFx_Delete
//   [ ] 0xe3588  RegisterCGlowNodeFxClass
//   [ ] 0xe3600  _GLOBAL__I_e3600
//   [ ] 0xe3610  CGlowNodeFx_Save
//   [ ] 0xe3638  CGlowNodeFx_RecursiveRegistration
//   [ ] 0xe3660  CGlowNodeFx_SetupMaterial_maybe
//   [ ] 0xe3980  CGlowNodeFx_PostLoad
//   [ ] 0xe39e8  CGlowNodeFx_Destroy
//   [x] 0xe3a38  CGlowNodeFx_DeleteArray
//   [x] 0xe3ad8  CGlowNodeFx_Create
//   [ ] 0xe3b38  FUN_000e3b38  [dead]
//   [x] 0xe3b88  CGlowNodeFx_CreateArray
//   [x] 0xe3c58  CGlowNodeFx_Load
//   [ ] 0xe4050  CGlowNodeFx_Enqueue
//
//   [ ] 0x9a5378  CGlowNodeFx_IsKindOfClass  [inline]
//   [ ] 0x9a53d8  CGlowNodeFx_GetClassType  [inline]
//   [ ] 0x9a53e0  CGlowNodeFx_GetClassID  [inline]
//   [ ] 0x9a53e8  CGlowNodeFx_Destructor  [inline]
//   [ ] 0x9a5428  CGlowNodeFx_DeletingDestructor  [inline]
#include "k2000/scenegraph/CGlowNodeFx.h"

#include "k2000/io/IKFile.h"
#include "k2000/memory/Mem.h"

// 0x000e3c58 CGlowNodeFx_Load
int32_t CGlowNodeFx::Load(IKFile* file, int32_t type) {
    INodeFx::Load(file, type);  // 0xeccd8
    ReadU32LE(file, &m_ui32NbGlows);
    ReadF32LE(file, &m_fPartSize);
    ReadRaw(file, m_color, 4);  // not swapped
    const uint32_t n = m_ui32NbGlows;
    uint32_t words = 0;
    if ((m_sgProperties & 0x400) == 0) {
        uint8_t* buffer = static_cast<uint8_t*>(Mem_AllocAligned16(n * 0xc));
        m_aWorldNormal = nullptr;
        m_aPosition = reinterpret_cast<CVector3*>(buffer);
        m_aNormal = nullptr;
        words = n * 3;
    } else {
        uint8_t* buffer;
        if ((m_sgProperties & 0x4000) == 0) {
            buffer = static_cast<uint8_t*>(Mem_AllocAligned16(n * 0x18));
            m_aWorldNormal = nullptr;
            m_aPosition = reinterpret_cast<CVector3*>(buffer);
            m_aNormal = reinterpret_cast<CVector3*>(buffer + n * 0xc);
        } else {
            buffer = static_cast<uint8_t*>(Mem_AllocAligned16(n * 0x24));
            m_aPosition = reinterpret_cast<CVector3*>(buffer);
            m_aNormal = reinterpret_cast<CVector3*>(buffer + n * 0xc);
            m_aWorldNormal = reinterpret_cast<CVector3*>(buffer + n * 0x18);
        }
        words = n * 6;  // positions and normals (the world normals are not in the file)
    }
    ReadU32LEWords(file, reinterpret_cast<uint32_t*>(m_aPosition), words);
    IKFile_ReadTextureRef(file, &m_pTexture, 0);
    ReadF32LE(file, &m_f32FlickSizeThreshold);
    ReadF32LE(file, &m_f32FlickSizeCoeff);
    ReadF32LE(file, &m_f32FlickAlphaThreshold);
    ReadRaw(file, &m_ui8FlickAlphaMean, 1);
    ReadRaw(file, &m_ui8FlickAlphaAmpl, 1);
    return 1;
}
