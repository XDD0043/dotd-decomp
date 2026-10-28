// CKLightningBoltFxData_2.cpp - reconstructed original translation unit 0x5774e8-0x57a7c8 (GAME_TOC2, main_toc2), 26 functions, 14 live.
// Primary class: CKLightningBoltFxData  key 0xa64c  category Logic  size ?  vtable 0xb2e048
// Other owners: CKLightningBoltNodeFx (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x5774e8  CKLightningBoltFxData_GetNodeClassKey
//   [ ] 0x5774f8  CKLightningBoltFxData_PostLoad
//   [ ] 0x577548  CKLightningBoltFxData_RandomValue6C_maybe
//   [ ] 0x5775b8  CKLightningBoltFxData_RandomInterval58_maybe
//   [ ] 0x577630  CKLightningBoltFxData_RandomInterval50_maybe
//   [ ] 0x5776a8  CKLightningBoltFxData_RecursiveRegistration
//   [ ] 0x5777f8  CKLightningBoltFxData_GetLevelField10_maybe  [dead]
//   [ ] 0x577830  CKLightningBoltFxData_GetLevelField00_maybe  [dead]
//   [ ] 0x577868  CKLightningBoltFxData_CopyEntry60_maybe
//   [ ] 0x5778c0  CKLightningBoltFxData_GetLevelField38_maybe  [dead]
//   [ ] 0x5778f8  CKLightningBoltFxData_GetLevelField34_maybe  [dead]
//   [ ] 0x577930  CKLightningBoltFxData_GetLevelField30_maybe  [dead]
//   [ ] 0x577968  CKLightningBoltFxData_GetLevelField2C_maybe  [dead]
//   [ ] 0x5779a0  CKLightningBoltFxData_GetLevelField24_maybe  [dead]
//   [ ] 0x5779d8  CKLightningBoltFxData_GetLevelField20_maybe  [dead]
//   [ ] 0x577a10  CKLightningBoltFxData_GetLevelField1C_maybe  [dead]
//   [ ] 0x577a48  CKLightningBoltFxData_GetLevelField18_maybe  [dead]
//   [ ] 0x577a80  CKLightningBoltFxData_GetLevelField14_maybe  [dead]
//   [ ] 0x577ab8  CKLightningBoltNodeFx_GetBranchLevelScale_maybe
//   [ ] 0x577b38  CKLightningBoltFxData_GetLevelField28_maybe  [dead]
//   [ ] 0x577b70  CKLightningBoltFxData_GetInfo
//   [ ] 0x577b78  CKLightningBoltFxData_Destroy
//   [ ] 0x577bd0  CKLightningBoltFxData_EvaluateColor_maybe
//   [x] 0x578158  CKLightningBoltFxData_Load
//   [ ] 0x578ea8  CKLightningBoltFxData_Save
//   [ ] 0x579a10  CKLightningBoltFxData_MessageProc
//
//   [ ] 0x9caf08  CKLightningBoltFxData_IsKindOfClass  [inline]
//   [x] 0x9caf48  CKLightningBoltFxData_GetClassType  [inline]
//   [x] 0x9caf50  CKLightningBoltFxData_GetClassID  [inline]
//   [ ] 0x9caf58  CKLightningBoltFxData_DeletingDestructor  [inline]
//   [ ] 0x9cafe8  CKLightningBoltFxData_Destructor  [inline]
#include "k2000/logic/render/CKLightningBoltFxData.h"

#include "k2000/io/IKFile.h"
#include "k2000/memory/Mem.h"

// 0x0056eec8 CKLightningBoltFxData_Create, the inlined constructor, in its store order.
CKLightningBoltFxData::CKLightningBoltFxData() {
    m_segments.m_pBlock = nullptr;
    m_segments.m_ui32NbElt = 1;
    m_segments.m_ui32NbUsedElt = 0;
}

// 0x00578158 CKLightningBoltFxData_Load
int32_t CKLightningBoltFxData::Load(IKFile* file, int32_t type) {
    IKFxData::Load(file, type);  // through TocBridge_IKFxData_Load
    if (type != K_LEVEL_PLATEFORMS) return 1;
    ReadF32LE(file, &m_unk1c);
    ReadU16LE(file, &m_unk18);
    ReadRaw(file, m_unk2c, 4);
    ReadRaw(file, m_unk30, 4);
    ReadRaw(file, m_unk34, 4);
    ReadRaw(file, m_unk38, 4);
    ReadF32LE(file, &m_unk3c);
    uint32_t count = 0;
    ReadU32LE(file, &count);
    if (count == 0) {
        m_segments.m_ui32NbElt = 1;
        m_segments.m_pBlock = static_cast<Segment*>(Mem_AllocAligned16(static_cast<uint32_t>(sizeof(Segment))));
    } else {
        m_segments.m_ui32NbElt = count;
        m_segments.m_pBlock = static_cast<Segment*>(Mem_AllocAligned16(count * static_cast<uint32_t>(sizeof(Segment))));
        for (uint32_t i = 0; i < count; ++i) {
            Segment segment;  // read into locals, then copied into the list
            for (uint32_t w = 0; w < 15; ++w) ReadF32LE(file, &segment.m_values[w]);
            const uint32_t used = m_segments.m_ui32NbUsedElt;
            if (m_segments.m_ui32NbElt == used) {  // full: grow by one
                uint32_t capacity = used + 1;
                uint32_t bytes = capacity * static_cast<uint32_t>(sizeof(Segment));
                if (capacity == 0) {
                    capacity = 1;
                    bytes = static_cast<uint32_t>(sizeof(Segment));
                }
                m_segments.m_pBlock = static_cast<Segment*>(Mem_ReallocAligned16(m_segments.m_pBlock, bytes));
                m_segments.m_ui32NbElt = capacity;
            }
            m_segments.m_pBlock[m_segments.m_ui32NbUsedElt] = segment;
            ++m_segments.m_ui32NbUsedElt;
        }
    }
    IKFile_ReadRef(file, &m_unk40);
    IKFile_ReadRef(file, &m_unk44);
    IKFile_ReadRef(file, &m_unk48);
    IKFile_ReadRef(file, &m_unk4c);
    ReadF32LE(file, &m_unk50);
    ReadF32LE(file, &m_unk54);
    ReadF32LE(file, &m_unk58);
    ReadF32LE(file, &m_unk5c);
    ReadF32LE(file, &m_unk6c);
    ReadF32LE(file, &m_unk70);
    IKFile_ReadRef(file, &m_unk8c);
    ReadF32LE(file, &m_unk90);
    ReadF32LE(file, &m_unk94);
    ReadF32LE(file, &m_unk98);
    ReadF32LE(file, &m_unk9c);
    ReadF32LE(file, &m_unka0);
    ReadF32LE(file, &m_unka4);
    ReadF32LE(file, &m_unk88);
    return 1;
}
