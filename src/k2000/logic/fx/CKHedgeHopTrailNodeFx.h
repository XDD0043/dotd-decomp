// CKHedgeHopTrailNodeFx.h - the hedge-hop trail effect (key 0x2c4c, vtable 0xb1cf88, size 0x70): a two-sided ribbon of
// points behind two pairs of anchors, sampled as Bezier curves into the node's geometry each frame, with a vertex-alpha
// fade-out. Original unit: CKHedgeHopTrailNodeFx.cpp (0x1c0f90-0x1c2a68); its Delete and PostLoad sit in
// CKHedgeHopTrailFxData.cpp. Not in XXL2; names ours. No game file holds the class (C2.8 port-rest R06).
//
// Per side s (0, 1): m_apSide[s] holds m_ui32NbPoints points of strip A, then m_ui32NbPoints of strip B; their heads follow
// the anchors m_aAnchors[s].m_vA / m_vB (written by the owner; nothing in this unit sets them).
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/fx/IKNodeFx.h"
#include "k2000/math/CMatrix34.h"

class CKHedgeHopTrailFxData;

class CKHedgeHopTrailNodeFx : public IKNodeFx {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0xb1)
    int32_t IsKindOfClass(uint32_t key) override {  // vt+0x08 0x9ac648
        return key == 0x2c4c || key == 0x148c || key == 0x154c || key == 0xc;
    }
    DOTD_DECLARE_FACTORIES(CKHedgeHopTrailNodeFx)

    struct Anchors {
        CVector3 m_vA;  // +0x00 the head of strip A
        CVector3 m_vB;  // +0x0c the head of strip B
    };

    CKHedgeHopTrailNodeFx();             // inlined in 0x001c1450 CKHedgeHopTrailNodeFx_Create (out of line: LNK1163)
    ~CKHedgeHopTrailNodeFx() override;  // the vtables only

    // vt+0x10 0x001c11b8 CKHedgeHopTrailNodeFx_Destroy: IKNodeFx's (no node), the point buffer freed.
    void Destroy() override;
    // vt+0x24 0x001c1148 CKHedgeHopTrailNodeFx_RecursiveRegistration: IKNodeFx's (the node), then the saving manager's.
    void RecursiveRegistration(int32_t type) override;
    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x001c14a8 CKHedgeHopTrailNodeFx_Load
    int32_t PostLoad(int32_t /*type*/) override { return 1; }  // vt+0x30 0x001c0f30
    void Vf64() override;                               // vt+0x64 0x001c1bf0 CKHedgeHopTrailNodeFx_Start
    void Stop() override;                               // vt+0x6c 0x001c1b20 CKHedgeHopTrailNodeFx_Stop
    // vt+0x78 0x001c2a60 CKHedgeHopTrailNodeFx_Update: a tail jump to UpdateTrailGeometry.
    void Update(IKTime* frameClock) override { UpdateTrailGeometry(frameClock); }
    IKFxData* GetFxData() override;                     // vt+0x80 0x009ac690 (+0x20)
    void SetFxData(IKFxData* data) override;            // vt+0x84 0x009ac698 (+0x20)

    // 0x001c10e0 CKHedgeHopTrailNodeFx_CacheUVTransform_maybe: the material's UV matrix kept. No caller in the EBOOT
    // (only its descriptor).
    void CacheUVTransform();
    // 0x001c1368 CKHedgeHopTrailNodeFx_InitVertexAlphaGradient_maybe: per side, the two halves' prelit alphas from 0xff
    // down to 0 in m_ui32NbVertices / 2 steps. No caller in the EBOOT (only its descriptor).
    void InitVertexAlphaGradient();
    // 0x001c1c88 CKHedgeHopTrailNodeFx_RespaceTrailSide_maybe: side s's heads moved to the anchors and every point
    // after them pushed along the strip by the head's move; returns the move's length.
    float RespaceTrailSide(uint32_t side);
    // 0x001c1f38 CKHedgeHopTrailNodeFx_ExtrudeTrailRibbon_maybe: the B strip pulled out from the A strip, then the two
    // sides spread apart where they are closer than the spread threshold.
    void ExtrudeTrailRibbon(IKTime* frameClock);
    // 0x001c23b8 CKHedgeHopTrailNodeFx_UpdateTrailGeometry_maybe: the points grown / respaced, extruded, sampled into the
    // geometry and faded; the atomic's bounding sphere at the node with radius 300000. 1 when the geometry was
    // rebuilt.
    int32_t UpdateTrailGeometry(IKTime* frameClock);

    // +0x14 bit 0 growing (Start), bit 1 fading (Stop); the constructor leaves it.
    uint8_t m_baTrail;
    uint8_t m_pad15[3];
    uint32_t m_aui32NbUsed[2];         // +0x18 the points laid per side (Start 0)
    CKHedgeHopTrailFxData* m_pData;    // +0x20
    CMatrix34* m_pUVTransform;         // +0x24 the material's UV matrix (Load)
    uint32_t m_ui32NbVertices;         // +0x28 per side (level files): two strips of half as many
    Anchors m_aAnchors[2];             // +0x2c
    CVector3* m_pPoints;               // +0x5c the buffer: 4 x m_ui32NbPoints points (Mem_AllocAligned16)
    CVector3* m_apSide[2];             // +0x60 its two halves
    uint32_t m_ui32NbPoints;           // +0x68 per strip (level files)
    uint32_t m_unk6c;                  // +0x6c not used by this unit
};
static_assert(CKHedgeHopTrailNodeFx::kClassKey == 0x2c4c, "key");
DOTD_ASSERT_SIZE(CKHedgeHopTrailNodeFx, 0x70);
DOTD_ASSERT_OFFSET(CKHedgeHopTrailNodeFx, m_baTrail, 0x14);
DOTD_ASSERT_OFFSET(CKHedgeHopTrailNodeFx, m_aui32NbUsed, 0x18);
DOTD_ASSERT_OFFSET(CKHedgeHopTrailNodeFx, m_pData, 0x20);
DOTD_ASSERT_OFFSET(CKHedgeHopTrailNodeFx, m_pUVTransform, 0x24);
DOTD_ASSERT_OFFSET(CKHedgeHopTrailNodeFx, m_ui32NbVertices, 0x28);
DOTD_ASSERT_OFFSET(CKHedgeHopTrailNodeFx, m_aAnchors, 0x2c);
DOTD_ASSERT_OFFSET(CKHedgeHopTrailNodeFx, m_pPoints, 0x5c);
DOTD_ASSERT_OFFSET(CKHedgeHopTrailNodeFx, m_apSide, 0x60);
DOTD_ASSERT_OFFSET(CKHedgeHopTrailNodeFx, m_ui32NbPoints, 0x68);
