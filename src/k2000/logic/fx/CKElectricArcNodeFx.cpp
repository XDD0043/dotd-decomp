// CKElectricArcNodeFx.cpp - reconstructed original translation unit 0x1b1300-0x1b3510 (GAME_TOC1, main_toc1), 28 functions, 27 live.
// Primary class: CKElectricArcNodeFx  key 0x164c  category Logic  size 0x50  vtable 0xb1c8c8
// Other owners: CKElectricArcFxData (1), CKExplosionFxData (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [ ] 0x1b1300  CKElectricArcNodeFx_SampleCurveWithJitter_maybe
//   [x] 0x1b1478  CKElectricArcFxData_Load
//   [x] 0x1b1918  CKElectricArcNodeFx_Delete
//   [ ] 0x1b1968  CKElectricArcNodeFx_Stop
//   [ ] 0x1b19c0  CKElectricArcNodeFx_OnPause
//   [ ] 0x1b1a00  RegisterCKElectricArcNodeFxClass
//   [ ] 0x1b1a78  _GLOBAL__I_1b1a78
//   [ ] 0x1b1a88  CKElectricArcNodeFx_BuildArcSegmentVerts_maybe
//   [ ] 0x1b1cd0  CKElectricArcNodeFx_Save
//   [ ] 0x1b1cf8  CKElectricArcNodeFx_RecursiveRegistration
//   [ ] 0x1b1d68  CKElectricArcNodeFx_Destroy
//   [x] 0x1b1d90  CKElectricArcNodeFx_DeleteArray
//   [x] 0x1b1e38  CKElectricArcNodeFx_CreateArray
//   [ ] 0x1b1ef0  CKElectricArcNodeFx_SetEndAlpha_maybe
//   [ ] 0x1b1f18  CKElectricArcNodeFx_SetStartAlpha_maybe
//   [ ] 0x1b1f40  CKElectricArcNodeFx_SetEndPoint
//   [ ] 0x1b1f80  CKElectricArcNodeFx_SetStartPoint
//   [ ] 0x1b1fc0  CKElectricArcNodeFx_SetStartAndEndPoints
//   [x] 0x1b2018  CKElectricArcNodeFx_PostLoad
//   [x] 0x1b20c0  CKElectricArcNodeFx_Create
//   [x] 0x1b2118  CKElectricArcNodeFx_Load
//   [ ] 0x1b2210  CKElectricArcNodeFx_InitTexCoords_maybe
//   [ ] 0x1b2468  CKElectricArcNodeFx_RebuildArcGeometry_maybe
//   [ ] 0x1b2940  CKElectricArcNodeFx_Start
//   [ ] 0x1b2bd0  CKElectricArcNodeFx_Update
//   [ ] 0x1b33d0  CKElectricArcNodeFx_SetAlphaForOwner_maybe  [dead]
//   [ ] 0x1b3500  CKExplosionFxData_GetNodeClassKey
//   [ ] 0x1b3508  KStub_Nop_1b3508
//
//   [ ] 0x9ab958  CKElectricArcNodeFx_IsKindOfClass  [inline]
//   [x] 0x9ab990  CKElectricArcNodeFx_GetClassType  [inline]
//   [x] 0x9ab998  CKElectricArcNodeFx_GetClassID  [inline]
//   [ ] 0x9ab9a0  CKElectricArcNodeFx_GetFxData  [inline]
//   [ ] 0x9ab9a8  CKElectricArcNodeFx_SetFxData  [inline]
//   [ ] 0x9ab9b0  CKElectricArcNodeFx_Destruct  [inline]
//   [ ] 0x9ab9d0  CKElectricArcNodeFx_DeletingDestruct  [inline]
//   [ ] 0x9aba18  KStub_Nop_9aba18  [inline]
#include "k2000/logic/fx/CKElectricArcNodeFx.h"

#include "k2000/io/IKFile.h"
#include "k2000/logic/fx/CKElectricArcFxData.h"

// 0x001b2018 CKElectricArcNodeFx_PostLoad: IKNodeFx_PostLoad (returns 1), the effect data cleared, the run-time
// words zero except +0x30 = 1.0f (TOC -0x2218; the others are TOC -0x220c = 0.0f), then vt+0x60 (the node hidden).
int32_t CKElectricArcNodeFx::PostLoad(int32_t type) {
    IKNodeFx::PostLoad(type);
    m_pFxData = nullptr;
    m_unk1c[0] = 0;  // +0x1c
    m_unk1c[3] = 0;  // +0x28
    m_unk1c[2] = 0;  // +0x24
    m_unk1c[1] = 0;  // +0x20
    m_unk1c[5] = 0x3f800000u;  // +0x30 1.0f
    m_unk1c[4] = 0;  // +0x2c
    m_unk1c[7] = 0;  // +0x38
    m_unk1c[6] = 0;  // +0x34
    Vf60();          // CKNodeFx3d_HideSceneNode
    return 1;
}

// 0x001b1478 CKElectricArcFxData_Load
int32_t CKElectricArcFxData::Load(IKFile* file, int32_t type) {
    IKFxData::Load(file, type);
    if (type != K_LEVEL_PLATEFORMS) return 1;
    ReadF32LE(file, &m_unk14);
    ReadF32LE(file, &m_unk1c);
    ReadF32LE(file, &m_unk20);
    ReadF32LE(file, &m_unk18);
    ReadF32LE(file, &m_unk24);
    ReadF32LE(file, &m_unk28);
    ReadF32LE(file, &m_unk2c);
    ReadF32LE(file, &m_unk10);
    ReadU8(file, &m_unk38);
    ReadF32LE(file, &m_unk30);
    ReadF32LE(file, &m_unk34);
    uint8_t flags = 0;
    ReadU8(file, &flags);
    m_flags39 = flags;
    m_unk08 = 0;
    m_unk0c = nullptr;
    if (((flags >> 2) & 1) != 0) {
        ReadU32LE(file, &m_unk08);
        m_unk0c = new Key[m_unk08];
        ReadU32LEWords(file, reinterpret_cast<uint32_t*>(m_unk0c), m_unk08 * 2);
    }
    return 1;
}

// 0x001b2118 CKElectricArcNodeFx_Load
int32_t CKElectricArcNodeFx::Load(IKFile* file, int32_t type) {
    IKNodeFx::Load(file, type);
    if (type == K_LEVEL_PLATEFORMS) {
        ReadU8(file, &m_unk18);
        ReadU8(file, &m_unk44);
        ReadU8(file, &m_unk48);
    }
    return 1;
}
