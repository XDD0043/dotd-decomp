// CTrailNodeFx.h - a ribbon trail effect node (key 0x6cb, vtable 0xb18c38, size 0x38). Original unit:
// CTrailNodeFx.cpp (0xea630-0xec920). XXL2: K/KModules/KGL/SceneGraph/NodeFx/CTrailNodeFx.h (m_apTrailData,
// m_ui32NbTrail, m_pTrailCtrlPoints) and STrailNodeData (LoadTrail: the same reads, DotD has three more
// words).
//
// A ribbon's control points are a grid: m_unk34 strips across the ribbon (strip 0 at the first anchor, the last one at
// the second, the others evenly between), each with m_ui32NbCtrPoints points along time (point 0 the newest). Every
// m_unk44 seconds the points move one place back and point 0 is laid out between the anchors again; the node's
// geometry (one per node, its vertices m_unk38 per strip) is the Bezier curve of each strip's points.
// The anchors, by the node's scene flags bits 9-10: 0 two bones of the parent (CAnimatedNode), 1 the stored extremes,
// 2 the two hot spots, 3 none.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/fx/INodeFx.h"
#include "k2000/math/CMatrix34.h"

class CSGHotSpot;

// One trail (XXL2 STrailNodeData; PS3 0x64 bytes, allocated with room to spare, see CTrailNodeFx::Load).
struct STrailNodeData {
    CVector3* m_pCtrlPoints;      // +0x00 Load sets 0; PostLoad points it into the node's m_pTrailCtrlPoints
    uint8_t m_ui8Extrem1;         // +0x04 the first anchor's bone (mode 0)
    uint8_t m_ui8Extrem2;         // +0x05
    uint8_t m_pad06[2];
    CVector3 m_v3Extrem1;         // +0x08 not read; the anchors of mode 1 (PostLoad: the null vector)
    CVector3 m_v3Extrem2;         // +0x14
    // +0x20 CBitArray8; Load sets 0. Bit 0 on (SetRibbonActive), bit 1 the colour changed (the geometry's
    // pre-lit colours written again, then cleared).
    uint8_t m_ba8Properties;
    uint8_t m_pad21[3];
    uint8_t m_cColor[4];          // +0x24 CColor, read raw (file bytes); every vertex's pre-lit colour
    // +0x28 Load sets 0: the points still drawn while the ribbon is off (SetRibbonActive sets m_ui32NbCtrPoints;
    // one fewer every period, the others collapsed onto the last one).
    uint8_t m_ui8Visible;
    uint8_t m_pad29[3];
    CSGHotSpot* m_pHotSpot1;      // +0x2c
    CSGHotSpot* m_pHotSpot2;      // +0x30
    uint32_t m_unk34;             // +0x34 read last (DotD): the strips across the ribbon (_maybe)
    uint32_t m_unk38;             // +0x38 read fourth (DotD): the vertices of a strip (the Bezier samples, _maybe)
    uint32_t m_ui32NbLineVertex;  // +0x3c read second: the vertices of the ribbon (its colours; _maybe XXL2's name)
    uint32_t m_ui32NbCtrPoints;   // +0x40 read first: the control points of a strip (_maybe)
    float m_unk44;                // +0x44 read third (DotD): the time between two control points (_maybe)
    float m_unk48;                // +0x48 PostLoad 0: the time since the points last moved
    CVector3 m_unk4c;             // +0x4c PostLoad null: the first strip's last point when the points last moved
    CVector3 m_unk58;             // +0x58 PostLoad null: the last strip's last point then
};
DOTD_ASSERT_SIZE(STrailNodeData, 0x64);
DOTD_ASSERT_OFFSET(STrailNodeData, m_ui8Extrem1, 0x04);
DOTD_ASSERT_OFFSET(STrailNodeData, m_v3Extrem1, 0x08);
DOTD_ASSERT_OFFSET(STrailNodeData, m_v3Extrem2, 0x14);
DOTD_ASSERT_OFFSET(STrailNodeData, m_ba8Properties, 0x20);
DOTD_ASSERT_OFFSET(STrailNodeData, m_cColor, 0x24);
DOTD_ASSERT_OFFSET(STrailNodeData, m_ui8Visible, 0x28);
DOTD_ASSERT_OFFSET(STrailNodeData, m_pHotSpot1, 0x2c);
DOTD_ASSERT_OFFSET(STrailNodeData, m_unk34, 0x34);
DOTD_ASSERT_OFFSET(STrailNodeData, m_ui32NbCtrPoints, 0x40);
DOTD_ASSERT_OFFSET(STrailNodeData, m_unk44, 0x44);
DOTD_ASSERT_OFFSET(STrailNodeData, m_unk48, 0x48);
DOTD_ASSERT_OFFSET(STrailNodeData, m_unk4c, 0x4c);
DOTD_ASSERT_OFFSET(STrailNodeData, m_unk58, 0x58);

class CTrailNodeFx : public INodeFx {
public:
    DOTD_CLASS_KEY(kCategoryNode, 0x1b)
    int32_t IsKindOfClass(uint32_t key) override {  // vt+0x08 0x9a5628
        return key == 0x6cb || key == 0x50b || key == 0xcb || key == 0x24b || key == 0x20b || key == 0x14b || key == 0xc;
    }
    DOTD_DECLARE_FACTORIES(CTrailNodeFx)

    CTrailNodeFx() {}  // 0x000ea990 CTrailNodeFx_Create: CNode's constructor, then the vtables
    ~CTrailNodeFx() override {}

    // vt+0x10 0x000ea9f0 CTrailNodeFx_Destroy: CNode's, then the trails, the control points and the trail array freed.
    void Destroy() override;
    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x000eb5f0 CTrailNodeFx_Load
    // vt+0x30 0x000ec708 CTrailNodeFx_PostLoad (whatever the type): INodeFx's, then one block of control points for all
    // trails (null points), each trail's slice, its timer 0 and its stored points null.
    int32_t PostLoad(int32_t type) override;
    // vt+0x58 0x000ec240 CTrailNodeFx_Enqueue: unless hidden (flag 4) or paused, the ribbons moved and their geometry
    // rebuilt (UpdateTrailGeometry); when something is to draw the node's geometry culled and queued (vt+0x84). No
    // child is traversed.
    void UpdateAndExtract(float maxDistanceSquared, RenderQueue** stages, IKTime* frameClock, RwCamera* camera,
                          int32_t distanceCull) override;

    // 0x000eb2d8 CTrailNodeFx_LoadPart (XXL2 CTrailNodeFx::LoadTrail): one trail; every type clears
    // m_ui8Visible, m_pCtrlPoints and m_ba8Properties.
    void LoadTrail(uint32_t index, STrailNodeData* trail, IKFile* file, int32_t type);

    // 0x009bdfb8 CTrailNodeFx_SetRibbonActive_maybe (inline in the original): ribbon `ribbon` on or off. A change sets
    // the ribbon's visible count to its number of control points and, unless the ribbon goes off without
    // `resetGeometry`, lays every control point out between the two anchors (the strips straight, every point of a
    // strip at the same place).
    void SetRibbonActive(uint32_t ribbon, uint32_t active, int32_t resetGeometry);

    // 0x000eabb0 TrailStrip_ResetPointsBetweenAnchors_maybe: the first point of each strip between the two anchors
    // (the bones' positions are not taken through the parent's matrix here; UpdateTrailGeometry does that).
    void ResetPointsBetweenAnchors(STrailNodeData* trail);
    // 0x000eb7b0 CTrailNodeFx_UpdateTrailGeometry_maybe: every ribbon's points moved on by the frame time; when one was
    // on or still visible the geometry's vertices (the strips' Bezier curves, collapsed when nothing is visible), its
    // colours (when changed) and texture coordinates written; the atomic's bounding sphere at the parent; the node's
    // LTM the identity. 1 when the geometry was rebuilt.
    uint8_t UpdateTrailGeometry(IKTime* frameClock);

    STrailNodeData** m_apTrailData;  // +0x2c Mem_AllocAligned16; null when there are none
    uint32_t m_ui32NbTrail;          // +0x30
    CVector3* m_pTrailCtrlPoints;    // +0x34 Load sets 0
};
static_assert(CTrailNodeFx::kClassKey == 0x6cb, "key");
DOTD_ASSERT_SIZE(CTrailNodeFx, 0x38);
DOTD_ASSERT_OFFSET(CTrailNodeFx, m_apTrailData, 0x2c);
DOTD_ASSERT_OFFSET(CTrailNodeFx, m_ui32NbTrail, 0x30);
DOTD_ASSERT_OFFSET(CTrailNodeFx, m_pTrailCtrlPoints, 0x34);
