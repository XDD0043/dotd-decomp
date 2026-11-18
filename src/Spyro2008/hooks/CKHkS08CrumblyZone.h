// CKHkS08CrumblyZone.h - Spyro's crumbly zone (key 0x2ec2, vtable 0xb25ae8, size 0x1cc). Original unit:
// CKHkS08CrumblyZone.cpp (0x4140f0-0x4150b8). No XXL2 class.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/hooks/CKHkCrumblyZone.h"

class CKHkS08CrumblyZone : public CKHkCrumblyZone {
public:
    DOTD_CLASS_KEY(kCategoryHook, 0xbb)
    int32_t IsKindOfClass(uint32_t key) override {  // vt+0x08 0x9c2778
        return key == 0x2ec2 || key == 0x1982 || key == 0xd82 || key == 0x2 || key == 0x2fe || key == 0x3fe ||
               key == 0xc;
    }
    DOTD_DECLARE_FACTORIES(CKHkS08CrumblyZone)

    // 0x00414e60 CKHkS08CrumblyZone_Create (inlined constructor): the base's only.
    CKHkS08CrumblyZone() {}
    ~CKHkS08CrumblyZone() override {}

    int32_t PostLoad(int32_t type) override;  // vt+0x30 0x004143d0 CKHkS08CrumblyZone_PostLoad: CKHkCrumblyZone's
    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x00414f28 CKHkS08CrumblyZone_Load
    void Start() override;  // vt+0x50 0x00414320 CKHkS08CrumblyZone_Start (C2.2)
    // vt+0x54 0x004142e8 CKHkS08CrumblyZone_Restart: the base's, then +0x1c8 cleared.
    void Restart() override {
        CKHkCrumblyZone::Restart();  // 0x0040c7d8
        m_unk1C8 = 0;
    }
    void VfA0() override;   // vt+0xa0 0x004142b0 CKHkS08CrumblyZone_OnActivate (C2.4 exit)
    // (vt+0x7c 0x00414358 CKHkS08CrumblyZone_Update, vt+0xf0 0x004143a8 and vt+0xf4 0x00414380 only call the base's.)
    // vt+0xf8 0x00414638 CKHkS08CrumblyZone_UpdateHeroWeight_maybe: the heroes standing on the zone counted; a change
    // of the count (+0x154 bit 2), or standing heroes on a zone marked +0x154 bit 27 not collapsed yet (bit 3), sets
    // off the collapse (vt+0xf4); with at least +0x1c1 heroes on it, every +0x1c4 s the zone loses its stages down to
    // +0x1c2 (the bonuses: CollapseAndSpawnBonuses) or, at that point and in view, crumbles.
    void VfF8() override;
    // (0x004057b0 CKHkS08CrumblyZone_IsInCameraView_maybe: CKHkCrumblyZone::IsInCameraView, its unit's.)
    // vt+0x1c 0x00414230 CKHkS08CrumblyZone_MessageProc: the base's answer, 2 and 3 kept, any other non-zero one 1.
    int32_t MessageProc(uint16_t message, void* data) override;
    // vt+0xfc 0x00414880 CKHkS08CrumblyZone_OnHit_maybe: a hero's volume (owner type 3) with a hero damage (0x998c) is
    // ignored when +0x1c0 is set and the damage's kind (+0x20) is not 5; an element damage (0x99cc) whose element is in
    // the mask +0x1bc takes its whole amount (+0x04, times dt when per second) off the hit points at the hit volume (the
    // first volume of +0xa4 present: the hitting volume, else the zone's node): CollapseAndSpawnBonuses while hit points
    // remain, else the crumble when in view. Anything else: the base's OnHit.
    void OnHit(IKBoundingVolume* volume) override;
    // vt+0x100 0x004141c8 CKHkS08CrumblyZone_vf100: a hero in a combo does not get the hit of a zone with +0x169 set.
    uint8_t Vf100(IKSerializable* hero) override;

    uint32_t m_unk1BC;     // +0x1bc
    uint8_t m_unk1C0;      // +0x1c0 read last
    uint8_t m_unk1C1;      // +0x1c1
    uint8_t m_unk1C2;      // +0x1c2
    uint8_t m_pad1C3;
    uint32_t m_unk1C4;     // +0x1c4
    uint32_t m_unk1C8;     // +0x1c8 not set by Create or Load
};
DOTD_ASSERT_SIZE(CKHkS08CrumblyZone, 0x1cc);
DOTD_ASSERT_OFFSET(CKHkS08CrumblyZone, m_unk1BC, 0x1bc);
DOTD_ASSERT_OFFSET(CKHkS08CrumblyZone, m_unk1C0, 0x1c0);
DOTD_ASSERT_OFFSET(CKHkS08CrumblyZone, m_unk1C1, 0x1c1);
DOTD_ASSERT_OFFSET(CKHkS08CrumblyZone, m_unk1C2, 0x1c2);
DOTD_ASSERT_OFFSET(CKHkS08CrumblyZone, m_unk1C4, 0x1c4);
