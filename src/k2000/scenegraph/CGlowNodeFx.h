// CGlowNodeFx.h - glow sprites at points (key 0x2cb, vtable 0xb18a30, size 0x5c). Original unit:
// CGlowNodeFx.cpp. XXL2: K/KModules/KGL/SceneGraph/NodeFx/CGlowNodeFx.h, the same members (m_pTexture,
// m_aPosition, m_aNormal, m_aWorldNormal, m_fPartSize, m_ui32NbGlows, m_color, the flicker values) in the
// same order; DotD has one word before them.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/fx/INodeFx.h"
#include "k2000/math/CMatrix34.h"

class CGlowNodeFx : public INodeFx {
public:
    DOTD_CLASS_KEY(kCategoryNode, 0xb)
    DOTD_DECLARE_FACTORIES(CGlowNodeFx)

    CGlowNodeFx() {}  // 0x000e3ad8 CGlowNodeFx_Create: CNode's constructor, then the vtables
    ~CGlowNodeFx() override {}

    // vt+0x2c 0x000e3c58 CGlowNodeFx_Load. No type check of its own.
    int32_t Load(IKFile* file, int32_t type) override;
    // vt+0x30 0x000e3980 CGlowNodeFx_PostLoad: INodeFx's, the material set up, +0x2c cleared (type 0).
    // STUB(C2.2): INodeFx's only (inherited).

    IKSerializable* m_unk2c;          // +0x2c (the Ghidra struct: a CAnimatedNode); PostLoad sets 0
    void* m_pTexture;                 // +0x30 IKFile_ReadTextureRef (resolve 0)
    CVector3* m_aPosition;            // +0x34 the glows' buffer (Mem_AllocAligned16)
    CVector3* m_aNormal;              // +0x38 in the same buffer (property 0x400), else null
    CVector3* m_aWorldNormal;         // +0x3c in the same buffer (properties 0x400 and 0x4000), else null
    float m_fPartSize;                // +0x40
    uint32_t m_ui32NbGlows;           // +0x44
    uint8_t m_color[4];               // +0x48 CColor, read raw (file bytes)
    float m_f32FlickSizeThreshold;    // +0x4c
    float m_f32FlickSizeCoeff;        // +0x50
    float m_f32FlickAlphaThreshold;   // +0x54
    uint8_t m_ui8FlickAlphaMean;      // +0x58
    uint8_t m_ui8FlickAlphaAmpl;      // +0x59
    uint8_t m_pad5a[2];
};
static_assert(CGlowNodeFx::kClassKey == 0x2cb, "key");
DOTD_ASSERT_SIZE(CGlowNodeFx, 0x5c);
DOTD_ASSERT_OFFSET(CGlowNodeFx, m_unk2c, 0x2c);
DOTD_ASSERT_OFFSET(CGlowNodeFx, m_pTexture, 0x30);
DOTD_ASSERT_OFFSET(CGlowNodeFx, m_aPosition, 0x34);
DOTD_ASSERT_OFFSET(CGlowNodeFx, m_aWorldNormal, 0x3c);
DOTD_ASSERT_OFFSET(CGlowNodeFx, m_fPartSize, 0x40);
DOTD_ASSERT_OFFSET(CGlowNodeFx, m_ui32NbGlows, 0x44);
DOTD_ASSERT_OFFSET(CGlowNodeFx, m_color, 0x48);
DOTD_ASSERT_OFFSET(CGlowNodeFx, m_f32FlickSizeThreshold, 0x4c);
DOTD_ASSERT_OFFSET(CGlowNodeFx, m_ui8FlickAlphaMean, 0x58);
DOTD_ASSERT_OFFSET(CGlowNodeFx, m_ui8FlickAlphaAmpl, 0x59);
