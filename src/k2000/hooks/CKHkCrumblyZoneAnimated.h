// CKHkCrumblyZoneAnimated.h - a crumbly zone whose node plays animations (key 0x3982, vtable 0xb258c0, size 0x1cc).
// Original unit: CKHkCrumblyZoneAnimated.cpp (0x410190-0x411100). XXL2: KMeca/CrumblyZone/CKHkCrumblyZoneAnimated.h
// (m_pZFAAnimDictionary, m_ui8CurrentAnim, m_ui8NextAnim, m_fAnimScale: the same members in the same order; DotD
// adds a byte, +0x1c8). No level file holds one (work/level-class-keys.json); C2.8 port-rest R03 ported it from the
// code.
//
// An intact zone (+0x188) with an animated node (class id 0x15) plays animation 0 of its dictionary; vt+0x104 (a
// collapse) switches to animation 1 with +0x1c8, which falls back to 0 at its end.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/hooks/CKHkCrumblyZone.h"

class CKHkCrumblyZoneAnimated : public CKHkCrumblyZone {
public:
    DOTD_CLASS_KEY(kCategoryHook, 0xe6)
    int32_t IsKindOfClass(uint32_t key) override {  // vt+0x08 0x9c2550
        return key == 0x3982 || CKHkCrumblyZone::IsKindOfClass(key);
    }
    DOTD_DECLARE_FACTORIES(CKHkCrumblyZoneAnimated)

    // 0x00410aa8 CKHkCrumblyZoneAnimated_Create (the dead 0x410660 / 0x4108b0 _Construct copies): the crumbly zone's
    // constructor; the members past it are what the fresh heap leaves (zero).
    CKHkCrumblyZoneAnimated() {
        m_pZFAAnimDictionary = nullptr;
        m_ui8CurrentAnim = 0;
        m_ui8NextAnim = 0;
        m_fAnimScale = 0.0f;
        m_unk1C8 = 0;
    }
    // 0x00410f58 CKHkCrumblyZoneAnimated_Destructor (= 0x4104b8 _BaseDestructor, 0x410d98 _DeletingDestructor): its own
    // vtable store, then CKHkCrumblyZone's inline destructor 0x9c11e8 (the vector blocks freed, the ground and contact
    // lists back to their pools), which dotd's CKHkCrumblyZone does not port ([inline] in CKHkCrumblyZone.cpp).
    ~CKHkCrumblyZoneAnimated() override {}

    // vt+0x2c 0x00410b70 CKHkCrumblyZoneAnimated_Load: the crumbly zone's, then for the level type the dictionary and
    // the scale (swapped).
    int32_t Load(IKFile* file, int32_t type) override;
    // vt+0x10 0x00410480 CKHkCrumblyZoneAnimated_Destroy: the crumbly zone's, then no dictionary.
    void Destroy() override;
    // vt+0x24 0x00410458 RecursiveRegistration, vt+0x50 0x4103e0 Start, vt+0xa4 0x410408 OnDeactivate, vt+0xf0 0x410298
    // (UpdateStageNodeMotion) and vt+0xf8 0x4102c0: the crumbly zone's, inherited; vt+0x68 / +0x70 / +0x78 0x4103b8 /
    // 0x410390 / 0x410368 Stop / Pause / Resume: the actor base's, inherited.
    // vt+0xa0 0x004107a8 CKHkCrumblyZoneAnimated_OnActivate: the crumbly zone's, then an intact zone with an animated
    // node plays animation 0 from the start.
    void VfA0() override;
    // vt+0x7c 0x00410c70 CKHkCrumblyZoneAnimated_Update: the crumbly zone's, then for an intact zone with an animated
    // node the animation step (UpdateAnim inlined, the time scaled by +0x1c4) and, with +0x1c8, animation 1's end
    // brings animation 0 back.
    void Update(IKTime* clock) override;
    // vt+0x104 0x00410868 CKHkCrumblyZoneAnimated_vf104 (new here): the collapse (vt+0xf4 0x407880 with arg 0), then
    // with +0x1c8 animation 1 next. No caller of the slot is known.
    virtual void Vf104(uint32_t mode, const CVector3* point);
    // 0x004102e8 CKHkCrumblyZoneAnimated_UpdateAnim_maybe (only its OPD refers to it; Update inlines the same): a new
    // animation (+0x1c1) played from 0, else the current one advanced by `dt`.
    void UpdateAnim(float dt);

    IKSerializable* m_pZFAAnimDictionary;  // +0x1bc XXL2 (a CAnimationDictionary)
    uint8_t m_ui8CurrentAnim;              // +0x1c0 XXL2
    uint8_t m_ui8NextAnim;                 // +0x1c1 XXL2
    uint8_t m_pad1c2[2];
    float m_fAnimScale;                    // +0x1c4 XXL2 (the animation time's scale)
    uint8_t m_unk1C8;                      // +0x1c8 DotD only: animation 1 is a one-shot (not loaded here)
    uint8_t m_pad1c9[3];
};
DOTD_ASSERT_SIZE(CKHkCrumblyZoneAnimated, 0x1cc);
DOTD_ASSERT_OFFSET(CKHkCrumblyZoneAnimated, m_pZFAAnimDictionary, 0x1bc);
DOTD_ASSERT_OFFSET(CKHkCrumblyZoneAnimated, m_ui8CurrentAnim, 0x1c0);
DOTD_ASSERT_OFFSET(CKHkCrumblyZoneAnimated, m_ui8NextAnim, 0x1c1);
DOTD_ASSERT_OFFSET(CKHkCrumblyZoneAnimated, m_fAnimScale, 0x1c4);
DOTD_ASSERT_OFFSET(CKHkCrumblyZoneAnimated, m_unk1C8, 0x1c8);
