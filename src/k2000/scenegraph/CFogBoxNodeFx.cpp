// CFogBoxNodeFx.cpp - reconstructed original translation unit 0xda260-0xe3538 (GAME_TOC1, main_toc1), 29 functions, 21 live.
// Primary class: CFogBoxNodeFx  key 0x68b  category SceneNode  size 0x838  vtable 0xb189a0
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [ ] 0xda260  RegisterCFogBoxNodeFxClass
//   [ ] 0xda2d8  _GLOBAL__I_da2d8
//   [x] 0xda2e8  CFogBoxNodeFx_DeleteArray
//   [ ] 0xda388  CFogBoxNodeFx_GetInfo
//   [ ] 0xda3d8  CFogBoxNodeFx_InitParticlePhaseTables_maybe  [dead]
//   [ ] 0xda4d8  CFogBoxNodeFx_AdvanceFlipbookFrame_maybe  [dead]
//   [ ] 0xda598  CFogBoxNodeFx_RecursiveRegistration
//   [ ] 0xda5c0  CFogBoxNodeFx_Destroy
//   [ ] 0xda7c0  CFogBoxNodeFx_Construct  [dead]
//   [ ] 0xda968  CFogBoxNodeFx_RandomizeEmitterParticles_maybe
//   [ ] 0xdab30  CFogBoxNodeFx_MessageProc
//   [ ] 0xdaba0  CFogBoxNodeFx_Construct_2  [dead]
//   [ ] 0xdad48  CFogBoxNodeFx_SortParticlesByDistance_maybe  [dead]
//   [ ] 0xdae70  CFogBoxNodeFx_InitParticleRandomValues_maybe
//   [ ] 0xdb018  CFogBoxNodeFx_InitAtomicRenderState_maybe  [dead]
//   [ ] 0xdb1a0  CFogBoxNodeFx_InitParticleColors_maybe
//   [ ] 0xdbac8  CFogBoxNodeFx_ResetFlipbookAndColors_maybe  [dead]
//   [ ] 0xdbae0  CFogBoxNodeFx_InitParticlesRandomInBox_maybe
//   [ ] 0xdbfa0  CFogBoxNodeFx_AllocParticleArrays_maybe
//   [ ] 0xdc1f8  CFogBoxNodeFx_InitParticlePositions_maybe
//   [ ] 0xdc548  CFogBoxNodeFx_UploadParticlePositions_maybe  [dead]
//   [ ] 0xdc618  CFogBoxNodeFx_RandomizeParticlePositions_maybe
//   [ ] 0xdc8b0  CFogBoxNodeFx_InitParticles_maybe
//   [x] 0xdcb20  CFogBoxNodeFx_PostLoad
//   [x] 0xdcde0  CFogBoxNodeFx_Create
//   [x] 0xdcfa0  CFogBoxNodeFx_CreateArray
//   [x] 0xdd1f8  CFogBoxNodeFx_Load
//   [ ] 0xde0b0  CFogBoxNodeFx_Save
//   [ ] 0xdef38  CFogBoxNodeFx_UpdateParticles_maybe
//
//   [ ] 0x9a4da8  CFogBoxNodeFx_IsKindOfClass  [inline]
//   [ ] 0x9a4e08  CFogBoxNodeFx_GetClassType  [inline]
//   [ ] 0x9a4e10  CFogBoxNodeFx_GetClassID  [inline]
//   [ ] 0x9a4e18  CFogBoxNodeFx_Destructor  [inline]
//   [ ] 0x9a4e58  SortParticlesByKey_maybe  [inline]
//   [ ] 0x9a5320  CFogBoxNodeFx_DeletingDestructor  [inline]
#include "k2000/scenegraph/CFogBoxNodeFx.h"

#include <cmath>
#include <cstring>

#include "crt/ppc_ops.h"
#include "k2000/core/Stub.h"
#include "k2000/io/IKFile.h"
#include "k2000/memory/Mem.h"
#include "k2000/misc/Mat4.h"

// 0x000dcb20 CFogBoxNodeFx_PostLoad. The derived values and the box/flag resets are ported; the particle
// system the original builds here sits on the RenderWare PTank atomic (locks, per-particle positions, colours
// and random values from Rand_Int) and is STUB(C2.7, particles: the PTank pipeline): CFogBoxNodeFx_AllocParticleArrays_maybe 0xdbfa0 (the
// buffers +0x82c / +0x830), the atomic's bounding sphere / render flags / blend mode (CGeometry_SetBlendMode),
// CFogBoxNodeFx_InitParticles_maybe 0xdc8b0 (+0x7b8, +0x824, +0x828 through InitParticleRandomValues 0xdae70 and
// RandomizeParticlePositions 0xdc618) and CFogBoxNodeFx_InitParticleColors_maybe 0xdb1a0 (+0x7a8). None of
// them changes the fields written here; their Rand_Int calls are not made.
int32_t CFogBoxNodeFx::PostLoad(int32_t type) {
    INodeFx::PostLoad(type);  // 0xeca78 CNodeFx_PostLoadBase_maybe (itself still the CNode one here)
    m_pGeometry = m_lGeometryList;
    const float length3 = std::sqrt(ppc::fmadds(m_unk5c[2], m_unk5c[2], ppc::fmadds(m_unk5c[0], m_unk5c[0], m_unk5c[1] * m_unk5c[1])));
    const float length2 = std::sqrt(ppc::fmadds(m_unk68[0], m_unk68[0], m_unk68[1] * m_unk68[1]));
    m_unk7d4 = 1.0f / m_unk7d0;                    // TOC -0x5034 = 1.0f
    m_unk30 = ppc::fmadds(length2, 0.5f, length3);  // TOC -0x5014 = 0.5f
    m_unk7e4 = 1.0f / m_unk7e0;
    DOTD_STUB_ONCE("CFogBoxNodeFx_PostLoad: the PTank particle setup (C2.7)");
    m_unk70 = -1.0f;  // TOC -0x5004
    m_unk71c = 0;
    if (type == 0) {
        for (uint32_t i = 0; i < m_ui32NbBoxes; ++i) m_aBoxes[i].m_unk04 = 0;
        if ((m_sgProperties & 0x800) != 0) m_unk40 = 0;
    }
    return 1;
}

// 0x000dd1f8 CFogBoxNodeFx_Load
int32_t CFogBoxNodeFx::Load(IKFile* file, int32_t type) {
    INodeFx::Load(file, type);  // 0xeccd8
    if (type != K_LEVEL_PLATEFORMS) return 1;
    ReadU32LE(file, &m_unk40);
    ReadU32LE(file, &m_ui32NbBoxes);
    // One buffer: the boxes, then m_ui32NbBoxes words (PS3: n * 0x14 bytes).
    uint8_t* buffer = static_cast<uint8_t*>(Mem_AllocAligned16(m_ui32NbBoxes * (sizeof(SBox) + 4)));
    m_aBoxes = reinterpret_cast<SBox*>(buffer);
    m_pUnk34 = reinterpret_cast<uint32_t*>(buffer + m_ui32NbBoxes * sizeof(SBox));
    for (uint32_t i = 0; i < m_ui32NbBoxes; ++i) {
        SBox* box = &m_aBoxes[i];
        box->m_pMatrix = RwMatrixCreate_Thunk();
        box->m_unk08 = 1.0f;
        box->m_unk04 = 0;
        CMatrix34_LoadMatrix(box->m_pMatrix, file);
    }
    IKFile_ReadTextureRef(file, &m_pTexture, 0);
    ReadRaw(file, &m_unk71f, 1);
    for (int32_t i = 0; i < 4; ++i) ReadRaw(file, &m_aUnk720[i], 1);
    ReadU32LE(file, &m_unk50);
    ReadU32LE(file, &m_unk54);
    ReadU32LE(file, &m_unk58);
    {
        uint32_t words[3];
        ReadU32LEWords(file, words, 3);
        std::memcpy(m_unk5c, words, 0xc);
    }
    ReadF32LE(file, &m_unk74);
    uint32_t count = 0;
    ReadU32LE(file, &count);
    ReadU32LEWords(file, &m_aPairs78[0][0], count * 2);  // count * 8 bytes
    ReadRaw(file, m_aBytes6b8, count >> 1);
    ReadRaw(file, &m_unk71d, 1);
    ReadRaw(file, &m_unk71e, 1);
    ReadU32LE(file, &m_unk724);
    uint32_t entries = 0;
    ReadU32LE(file, &entries);
    for (uint32_t i = 0; i < entries; ++i) {
        SEntry728* entry = &m_aEntries728[i];
        ReadF32LE(file, &entry->m_af[0]);
        ReadF32LE(file, &entry->m_af[1]);
        ReadRaw(file, entry->m_raw08, 4);
        ReadRaw(file, entry->m_raw0c, 4);
    }
    if (m_unk71f != 1) {
        m_pUnk7ac = static_cast<uint32_t*>(Mem_AllocAligned16(m_unk50 * 0x1c));
        ReadU32LEWords(file, m_pUnk7ac, m_unk50 * 7);
    }
    ReadF32LE(file, &m_unk7b0);
    ReadF32LE(file, &m_unk7b4);
    for (int32_t i = 0; i < 4; ++i) ReadF32LE(file, &m_unk7bc[i]);
    if (m_unk71f == 1) {
        m_pUnk7ec = static_cast<uint32_t*>(Mem_AllocAligned16(m_unk50 * 4));
        m_pUnk7f0 = static_cast<uint32_t*>(Mem_AllocAligned16(m_unk50 * 4));
        ReadU32LEWords(file, m_pUnk7ec, m_unk50);
        ReadU32LEWords(file, m_pUnk7f0, m_unk50);
    }
    ReadF32LE(file, &m_unk7f4);
    ReadF32LE(file, &m_unk7f8);
    ReadU32LE(file, &m_unk800);
    ReadF32LE(file, &m_unk804);
    {
        uint32_t words[3];
        ReadU32LEWords(file, words, 3);
        std::memcpy(&m_unk808, &words[0], 4);
        m_unk80c = words[1];
        std::memcpy(&m_unk810, &words[2], 4);
    }
    ReadF32LE(file, &m_unk814);
    ReadF32LE(file, &m_unk818);
    ReadF32LE(file, &m_unk81c);
    ReadF32LE(file, &m_unk820);
    {
        uint32_t words[2];
        ReadU32LEWords(file, words, 2);
        std::memcpy(m_unk68, words, 8);
    }
    ReadF32LE(file, &m_unk30);
    ReadF32LE(file, &m_unk7cc);
    ReadF32LE(file, &m_unk7d0);
    ReadRaw(file, &m_unk7d8, 1);
    ReadF32LE(file, &m_unk7dc);
    ReadF32LE(file, &m_unk7e0);
    ReadRaw(file, &m_unk7e8, 1);
    m_pUnk834 = static_cast<uint8_t*>(Mem_AllocAligned16(m_unk54 * 4));
    ReadRaw(file, m_pUnk834, m_unk54 * 4);  // not swapped
    return 1;
}
