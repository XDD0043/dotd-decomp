// CDistortionScreenFx.h - the screen distortion effect (key 0xc4d, vtable 0xb17618, size 0x38). Its code
// is in CDistortionScreenData.cpp (0xb1580-0xb3170). XXL2: KGL/Main/ScreenFx/CDistortionScreenFx.h
// (m_fTime, m_pLeaf, m_pDistortionData); the DotD field names are ours unless noted.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/graphical/fx/IScreenFx.h"
#include "k2000/math/CMatrix34.h"

class CDistortionScreenFx : public IScreenFx {
public:
    DOTD_CLASS_KEY(kCategoryGraphical, 0x31)
    DOTD_DECLARE_FACTORIES(CDistortionScreenFx)

    CDistortionScreenFx();                  // 0x000b1fb0 CDistortionScreenFx_Create (inlined)
    ~CDistortionScreenFx() override {}      // 0x009a0a88 / 0x009a09e8 CDistortionScreenFx_Destructor / _DeletingDestructor: the vtables only
    // vt+0x08 0x9a09b0
    int32_t IsKindOfClass(uint32_t key) override {
        return key == 0xc4d || key == 0xacd || key == 0xa8d || key == 0xc;
    }
    int32_t Load(IKFile* file, int32_t type) override;      // vt+0x2c 0x000b2378 CDistortionScreenFx_Load
    int32_t GetSerializationFlags() override { return 2; }  // vt+0x34 0x9a0988
    // vt+0x30 0x000b2280 CDistortionScreenFx_PostLoad: for the level (type 0) off (bits 8 and 9 of the properties), no
    // source, time and centres cleared, the grid built (BuildGrid).
    int32_t PostLoad(int32_t type) override;
    // vt+0x10 0x000b22e0 CDistortionScreenFx_Destroy: IRendableObject's, then the grid's vertices and indices freed.
    void Destroy() override;
    // vt+0x24 0x000b2220 CDistortionScreenFx_RecursiveRegistration: type 0 registers the effect (IScreenFx's registers
    // nothing).
    void RecursiveRegistration(int32_t type) override;
    // vt+0x78 0x000b1578 CDistortionScreenFx_vf78 (XXL2 CDistortionScreenFx::Clear): a bare blr.
    virtual void Clear() {}
    void UpdateAndExtract(float, RenderQueue**, IKTime*, RwCamera*, int32_t) override {}  // vt+0x58 0xb1570 (a bare blr)
    // vt+0x5c 0x000b2c88 CDistortionScreenFx_Draw (CPostRenderingFx_Draw calls it while +0x14 bit 0x100 is set, with
    // the render queue's frame clock): while the clock runs (+0x30 state 0) the time grows by its +0x20 delta; with a
    // source the grid warp is drawn (RenderDistortionGridWarp) and, once past the source's duration, the effect is off
    // and forgets its source and centres.
    void Render(IKTime* frameClock) override;
    // 0x000b1d20 CDistortionScreenFx_BuildGrid_maybe: the grid's index count (+0x28: 5n + 2(n-1)^2 - 6 for the
    // resolution n), its n x n Im2D vertices (+0x30) and the triangle strip's indices (+0x34: the rows joined by
    // degenerate triangles), the old buffers freed (Mem_AllocAligned16 / Mem_FreeAligned16).
    void BuildGrid();

    // 0x000b2008 CDistortionScreenData_Reset_maybe: off (bit 0x100 of the properties), no source, the run-time words 0.
    void Reset();
    // 0x000b2038 CDistortionScreenData_SetSource_maybe: the time (+0x18) 0; a source makes it the source and turns the
    // effect on (0x100); null only turns it off (the old source stays).
    void SetSource(IKSerializable* source);

    // +0x18..+0x20: PostLoad clears them; not written by Load.
    float m_fTime;              // +0x18 the time since SetSource (Draw adds the frame time)
    IKSerializable* m_unk1c;    // +0x1c a scene node whose LTM position is the warp's centre (before +0x20); no writer ported
    const CVector3* m_pCenter;  // +0x20 the world centre of the warp (CKDistortionNodeFx_SetCenterForOwner_maybe)
    // +0x24 the grid resolution _maybe: XXL2 reads m_ui8Resol (a byte) in CDistortionScreenData::Load before
    // BuildGrid; DotD reads the byte here and builds the grid in this class's PostLoad (LVL000: 20).
    uint8_t m_ui8Resol;
    uint8_t m_pad25[3];   // +0x25 never written
    uint32_t m_unk28;     // +0x28 Load sets 0; the strip's index count (BuildGrid)
    IKSerializable* m_pSource;  // +0x2c the distortion data shown (SetSource; CKDistortionNodeFx); PostLoad sets 0
    void* m_unk30;        // +0x30 Load sets 0; the grid's RwIm2DVertex array (BuildGrid)
    void* m_unk34;        // +0x34 Load sets 0; its RwImVertexIndex array (BuildGrid)
};
DOTD_ASSERT_SIZE(CDistortionScreenFx, 0x38);

class CDistortionScreenData;
// 0x000b2428 RenderDistortionGridWarp (CDistortionScreenData.cpp): see the definition. Returns whether the effect
// still runs (the source's duration above `time`).
uint8_t RenderDistortionGridWarp(CDistortionScreenFx* fx, float time, IKSerializable* centerNode, const CVector3* center,
                                 CDistortionScreenData* data);
DOTD_ASSERT_OFFSET(CDistortionScreenFx, m_ui8Resol, 0x24);
DOTD_ASSERT_OFFSET(CDistortionScreenFx, m_unk28, 0x28);
DOTD_ASSERT_OFFSET(CDistortionScreenFx, m_unk30, 0x30);
DOTD_ASSERT_OFFSET(CDistortionScreenFx, m_unk34, 0x34);
