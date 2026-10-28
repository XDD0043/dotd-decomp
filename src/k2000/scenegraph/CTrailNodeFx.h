// CTrailNodeFx.h - a ribbon trail effect node (key 0x6cb, vtable 0xb18c38, size 0x38). Original unit:
// CTrailNodeFx.cpp (0xea630-...). XXL2: K/KModules/KGL/SceneGraph/NodeFx/CTrailNodeFx.h (m_apTrailData,
// m_ui32NbTrail, m_pTrailCtrlPoints) and STrailNodeData (LoadTrail: the same reads, DotD has three more
// words).
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/fx/INodeFx.h"
#include "k2000/math/CMatrix34.h"

class CSGHotSpot;

// One trail (XXL2 STrailNodeData; PS3 0x48 bytes, allocated with room to spare, see CTrailNodeFx::Load).
struct STrailNodeData {
    CVector3* m_pCtrlPoints;      // +0x00 Load sets 0
    uint8_t m_ui8Extrem1;         // +0x04
    uint8_t m_ui8Extrem2;         // +0x05
    uint8_t m_pad06[2];
    CVector3 m_v3Extrem1;         // +0x08 not read
    CVector3 m_v3Extrem2;         // +0x14 not read
    uint8_t m_ba8Properties;      // +0x20 CBitArray8; Load sets 0
    uint8_t m_pad21[3];
    uint8_t m_cColor[4];          // +0x24 CColor, read raw (file bytes)
    uint8_t m_ui8Visible;         // +0x28 Load sets 0
    uint8_t m_pad29[3];
    CSGHotSpot* m_pHotSpot1;      // +0x2c
    CSGHotSpot* m_pHotSpot2;      // +0x30
    uint32_t m_unk34;             // +0x34 read last (DotD)
    uint32_t m_unk38;             // +0x38 read fourth (DotD)
    uint32_t m_ui32NbLineVertex;  // +0x3c read second (_maybe: XXL2 reads its two counts in a row)
    uint32_t m_ui32NbCtrPoints;   // +0x40 read first (_maybe)
    uint32_t m_unk44;             // +0x44 read third (DotD)
};
DOTD_ASSERT_SIZE(STrailNodeData, 0x48);
DOTD_ASSERT_OFFSET(STrailNodeData, m_ui8Extrem1, 0x04);
DOTD_ASSERT_OFFSET(STrailNodeData, m_ba8Properties, 0x20);
DOTD_ASSERT_OFFSET(STrailNodeData, m_cColor, 0x24);
DOTD_ASSERT_OFFSET(STrailNodeData, m_ui8Visible, 0x28);
DOTD_ASSERT_OFFSET(STrailNodeData, m_pHotSpot1, 0x2c);
DOTD_ASSERT_OFFSET(STrailNodeData, m_unk34, 0x34);
DOTD_ASSERT_OFFSET(STrailNodeData, m_ui32NbCtrPoints, 0x40);
DOTD_ASSERT_OFFSET(STrailNodeData, m_unk44, 0x44);

class CTrailNodeFx : public INodeFx {
public:
    DOTD_CLASS_KEY(kCategoryNode, 0x1b)
    DOTD_DECLARE_FACTORIES(CTrailNodeFx)

    CTrailNodeFx() {}  // 0x000ea990 CTrailNodeFx_Create: CNode's constructor, then the vtables
    ~CTrailNodeFx() override {}

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x000eb5f0 CTrailNodeFx_Load
    // 0x000eb2d8 CTrailNodeFx_LoadPart (XXL2 CTrailNodeFx::LoadTrail): one trail; every type clears
    // m_ui8Visible, m_pCtrlPoints and m_ba8Properties.
    void LoadTrail(uint32_t index, STrailNodeData* trail, IKFile* file, int32_t type);

    // 0x009bdfb8 CTrailNodeFx_SetRibbonActive_maybe (inline in the original): ribbon `ribbon` on or off. A change sets
    // the ribbon's visible count to its number of control points and, unless the ribbon stays off without
    // `resetGeometry`, rebuilds its points between the two anchors (STUB(C2.7, the FX service: trail drawing): draw state, not ported).
    void SetRibbonActive(uint32_t ribbon, uint32_t active, int32_t resetGeometry);

    STrailNodeData** m_apTrailData;  // +0x2c Mem_AllocAligned16; null when there are none
    uint32_t m_ui32NbTrail;          // +0x30
    CVector3* m_pTrailCtrlPoints;    // +0x34 Load sets 0
};
static_assert(CTrailNodeFx::kClassKey == 0x6cb, "key");
DOTD_ASSERT_SIZE(CTrailNodeFx, 0x38);
DOTD_ASSERT_OFFSET(CTrailNodeFx, m_apTrailData, 0x2c);
DOTD_ASSERT_OFFSET(CTrailNodeFx, m_ui32NbTrail, 0x30);
DOTD_ASSERT_OFFSET(CTrailNodeFx, m_pTrailCtrlPoints, 0x34);
