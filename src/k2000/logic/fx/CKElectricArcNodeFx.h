// CKElectricArcNodeFx.h - the electric-arc effect node (key 0x164c, vtable 0xb1c8c8, size 0x50). Original
// unit: CKElectricArcNodeFx.cpp. Its data is CKElectricArcFxData (0x174c). Not in XXL2; names ours.
//
// Load reads three single bytes into the first byte of the words +0x18, +0x44 and +0x48: on the PS3 a word
// load of them sees the byte in bits 24..31.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/fx/IKNodeFx.h"
#include "k2000/math/CMatrix34.h"

struct RwV3d;
class CKElectricArcFxData;

class CKElectricArcNodeFx : public IKNodeFx {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x59)
    int32_t IsKindOfClass(uint32_t key) override {  // vt+0x08 0x9ab958
        return key == 0x164c || key == 0x148c || key == 0x154c || key == 0xc;
    }
    DOTD_DECLARE_FACTORIES(CKElectricArcNodeFx)

    CKElectricArcNodeFx() {}  // inlined in 0x001b20c0 CKElectricArcNodeFx_Create: the IKNodeFx part only
    ~CKElectricArcNodeFx() override {}

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x001b2118 CKElectricArcNodeFx_Load
    // vt+0x24 0x001b1cf8 CKElectricArcNodeFx_RecursiveRegistration: IKNodeFx's (0x1d88c0: the node's, when set), then
    // registered with the saving manager whatever the type.
    void RecursiveRegistration(int32_t type) override;
    int32_t PostLoad(int32_t type) override;            // vt+0x30 0x001b2018 CKElectricArcNodeFx_PostLoad

    void Vf64() override;                      // vt+0x64 0x001b2940 CKElectricArcNodeFx_Start
    void Stop() override;                      // vt+0x6c 0x001b1968 CKElectricArcNodeFx_Stop: stopped, hidden (vt+0x60)
    void Vf70() override;                      // vt+0x70 0x001b19c0 CKElectricArcNodeFx_OnPause: vt+0x5c
    void Update(IKTime* frameClock) override;  // vt+0x78 0x001b2bd0 CKElectricArcNodeFx_Update
    IKFxData* GetFxData() override;            // vt+0x80 0x009ab9a0 [inline]
    void SetFxData(IKFxData* data) override;   // vt+0x84 0x009ab9a8 [inline]

    // The owner's setters (a running effect reserved by `owner` only; the hero's link arcs, not taken in DotD).
    void SetEndAlpha(uint8_t alpha, const IKSerializable* owner);    // 0x001b1ef0 CKElectricArcNodeFx_SetEndAlpha_maybe
    void SetStartAlpha(uint8_t alpha, const IKSerializable* owner);  // 0x001b1f18 CKElectricArcNodeFx_SetStartAlpha_maybe
    void SetEndPoint(const CVector3* point, const IKSerializable* owner);    // 0x001b1f40
    void SetStartPoint(const CVector3* point, const IKSerializable* owner);  // 0x001b1f80
    void SetStartAndEndPoints(const CVector3* start, const CVector3* end, const IKSerializable* owner);  // 0x001b1fc0

    // 0x001b2468 CKElectricArcNodeFx_RebuildArcGeometry_maybe: the bolt's vertices (a strip along local z from -0.5 to
    // 0.5, m_unk18 steps of the data's curve with jitter, half width data +0x1c along x), the branch (m_unk44 steps) from
    // the segment m_i16BranchSegment, the vertex alphas from the end alphas, the node centred between the points and
    // stretched to their distance.
    void RebuildArcGeometry();
    // 0x001b1300 CKElectricArcNodeFx_SampleCurveWithJitter_maybe: the data's curve at `t` plus one rand jitter draw (a member
    // so that the rand log names it).
    static float SampleCurveWithJitter(float t, const CKElectricArcFxData* data);
    // 0x001b2210 CKElectricArcNodeFx_InitTexCoords_maybe: the strip's v coordinates for the texture frame m_unk49.
    void InitTexCoords();
    // 0x001b1a88 CKElectricArcNodeFx_BuildArcSegmentVerts_maybe: the branch's vertex pairs from `point` along `direction`.
    void BuildArcSegmentVerts(RwV3d** vertex, const CVector3* point, const CVector3* direction);
    // The geometries' alpha (inlined in Start and Update): m_ui8Alpha, opaque without blending for a material of modes
    // 1..6 with render flag 12 (render flag 11 = blended; UpdateProperties when it changes).
    void ApplyAlpha();

    IKSerializable* m_pFxData;  // +0x14 the inline GetFxData/SetFxData (0x9ab9a0/0x9ab9a8) use it
    uint8_t m_unk18;            // +0x18 one byte (LVL010: 5): the bolt's segment count
    uint8_t m_pad19[3];
    CVector3 m_vStart;          // +0x1c the start point (PostLoad 0)
    CVector3 m_vEnd;            // +0x28 the end point (PostLoad (0, 0, 1))
    float m_fTime;              // +0x34 seconds since Start
    float m_fRebuildTime;       // +0x38 seconds since the vertices were rebuilt (data +0x18 between rebuilds)
    float m_fLifetime;          // +0x3c data +0x14, with data flag 1 minus up to 2 x data +0x10 at random
    float m_fFadeOutTime;       // +0x40 m_fLifetime - 255 / data +0x34: the alpha fades out after it
    uint8_t m_unk44;            // +0x44 one byte (LVL010: 0): the branch's segment count (0: no branch)
    uint8_t m_pad45;
    int16_t m_i16BranchSegment;  // +0x46 the bolt segment the branch starts from (-1 until Update draws it)
    uint8_t m_unk48;            // +0x48 one byte (LVL010: 4): the texture's frame count
    uint8_t m_ui8Frame;         // +0x49 the texture frame (Start: data +0x38 when within the count)
    uint8_t m_ui8Alpha;         // +0x4a the arc's alpha (fades in from 0 at data +0x30 per second; 0xff with data flag 4)
    uint8_t m_ui8StartAlpha;    // +0x4b the alpha at the start point (Start 0xff)
    uint8_t m_ui8EndAlpha;      // +0x4c the alpha at the end point (Start 0xff)
    uint8_t m_ui8Flipped;       // +0x4d the arc faces away from the camera: the end alphas swapped
    uint8_t m_pad4e[2];
};
static_assert(CKElectricArcNodeFx::kClassKey == 0x164c, "key");
DOTD_ASSERT_SIZE(CKElectricArcNodeFx, 0x50);
DOTD_ASSERT_OFFSET(CKElectricArcNodeFx, m_pFxData, 0x14);
DOTD_ASSERT_OFFSET(CKElectricArcNodeFx, m_unk18, 0x18);
DOTD_ASSERT_OFFSET(CKElectricArcNodeFx, m_unk44, 0x44);
DOTD_ASSERT_OFFSET(CKElectricArcNodeFx, m_unk48, 0x48);
DOTD_ASSERT_OFFSET(CKElectricArcNodeFx, m_vStart, 0x1c);
DOTD_ASSERT_OFFSET(CKElectricArcNodeFx, m_fTime, 0x34);
DOTD_ASSERT_OFFSET(CKElectricArcNodeFx, m_fFadeOutTime, 0x40);
DOTD_ASSERT_OFFSET(CKElectricArcNodeFx, m_i16BranchSegment, 0x46);
DOTD_ASSERT_OFFSET(CKElectricArcNodeFx, m_ui8Flipped, 0x4d);
