// CBillboard2d.h - a textured 2D quad of a scene (key 0x3cd, vtable 0xb156e8, size 0x84). Original unit:
// CBillboard2d.cpp (0x5af70-0x5be10). XXL2: K/KModules/KGL/2d/CBillboard2d.h, bases IKNode2d and
// IKBillboard2d (at +0x28); XXL2's Load only calls the two base Loads, DotD's then reads +0x6c..+0x83
// (K_LEVEL_PLATEFORMS only): a reference and five words (sprite-sheet animation_maybe: the class's
// SetAnimTime/SetSpriteSheetRows/SetSpriteSheetColumns setters 0x5b098..0x5b158).
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/ui/IKBillboard2d.h"
#include "k2000/ui/IKNode2d.h"

class CBillboard2d : public IKNode2d, public IKBillboard2d {
public:
    DOTD_CLASS_KEY(kCategoryGraphical, 0xf)
    DOTD_DECLARE_FACTORIES(CBillboard2d)

    CBillboard2d() {}  // 0x0005b498 CBillboard2d_Create: the two base constructors, then the vtables
    ~CBillboard2d() override {}
    int32_t IsKindOfClass(uint32_t key) override {  // vt+0x08 0x9973a8
        return key == 0x3cd || key == 0x24d || key == 0xc;
    }
    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x0005b768 CBillboard2d_Load (+ thunk 0x9973d0)
    // vt+0x80 0x0005afc0 CBillboard2d_vf80 (XXL2 slot 31 Scale): the billboard size times the scale.
    void Scale(const CVector2& scale) override;
    // vt+0x84 0x0005b508 DrawAnimatedUIBillboardWidget: follows +0x6c's visibility, advances the
    // sprite-sheet animation by the frame's fixed-time delta and draws the quad.
    void Render(IKTime* frameClock) override;

    // 0x0005b098 CBillboard2d_SetAnimTime_maybe: the animation's duration (+0x74); 0 stops the animation
    // and puts the full-texture UVs back on the brush. (The menus' buttons and check boxes call it.)
    void SetAnimTime(float duration);
    // 0x0005b118 CBillboard2d_SetSpriteSheetRows_maybe: +0x7c (0 -> 1), the time and the frame reset.
    void SetSpriteSheetRows(int32_t count);
    // 0x0005b158 CBillboard2d_SetSpriteSheetColumns_maybe: +0x80 (0 -> 1), the time and the frame reset.
    void SetSpriteSheetColumns(int32_t count);

    IKSerializable* m_unk6c;  // +0x6c a reference: an IKNode2d whose Enable bit this billboard copies
    float m_fAnimTime;        // +0x70 the animation's time (wraps at +0x74); read as a raw word
    float m_fAnimDuration;    // +0x74 0 = no animation; read as a raw word
    uint32_t m_ui32AnimFrame; // +0x78 the sprite-sheet cell, frame / +0x80 and frame % +0x80
    int32_t m_unk7c;          // +0x7c the sheet's cells along u (1 / +0x7c per cell)
    int32_t m_unk80;          // +0x80 the sheet's cells along v
};
DOTD_ASSERT_SIZE(CBillboard2d, 0x84);
DOTD_ASSERT_OFFSET(CBillboard2d, m_pBillboard, 0x2c);
DOTD_ASSERT_OFFSET(CBillboard2d, m_unk6c, 0x6c);
DOTD_ASSERT_OFFSET(CBillboard2d, m_fAnimTime, 0x70);
DOTD_ASSERT_OFFSET(CBillboard2d, m_unk80, 0x80);
