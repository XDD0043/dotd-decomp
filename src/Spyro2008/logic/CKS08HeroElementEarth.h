// CKS08HeroElementEarth.h - the earth hero element (key 0x89cc, vtable 0xb24008, size 0x328). Original unit:
// CKS08HeroElementEarth.cpp (0x3c9f90-0x3cb878). C2.8 port-final F08. No XXL2 class of this name: the members keep
// placeholder names. No level file of DotD holds one (CKS08HeroElement.h).
//
// Its repeated shot (vt+0x68 / vt+0x74) shows a mesh (+0x30c) that fades in from alpha +0x2e8 to +0x2e4 over +0x2f0
// seconds and spawns an explosion (+0x300) at the hero; vt+0x7c starts its fade out (from its current alpha +0x324 to
// +0x2ec over +0x2f4 seconds; hidden at once without a fade-out time), vt+0x88 hides it.
//
// BUG(original): nothing sets the mesh +0x30c (PostLoad clears it; Load, the slots and the base never write it), so
// every slot but vt+0x88 (which tests it) would read through a null node. Natively the node part of those slots is
// skipped (a null node reads as one without geometry).
#pragma once
#include <cstdint>

#include "Spyro2008/logic/CKS08HeroElement.h"

class CNode;

class CKS08HeroElementEarth : public CKS08HeroElement {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x227)
    // vt+0x08 0x009c0350 CKS08HeroElementEarth_IsKindOfClass
    int32_t IsKindOfClass(uint32_t key) override {
        return (key == 0x89cc || key == 0x890c) ? 1 : (key == 0xc ? 1 : 0);
    }
    DOTD_DECLARE_FACTORIES(CKS08HeroElementEarth)

    CKS08HeroElementEarth() {}  // inlined in 0x003ca558 CKS08HeroElementEarth_Create: the vtable only
    // 0x009c03f0 Destructor / 0x009c03a8 DeletingDestructor: the base's vtables back, nothing freed.
    ~CKS08HeroElementEarth() override {}
    void Destroy() override;                            // vt+0x10 0x003ca490: the base's
    void RecursiveRegistration(int32_t type) override;  // vt+0x24 0x003ca468: the base's, then 1
    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x003cade8
    int32_t PostLoad(int32_t type) override;            // vt+0x30 0x003ca788

    // vt+0x68 0x003ca2e8 CKS08HeroElementEarth_vf68: with the hero and not active yet, the mesh shown at alpha +0x2e8
    // (its low byte), the fade restarted and the explosion spawned (SpawnFx); then active (+0x318).
    void StartRepeatFire(int8_t level) override;
    // vt+0x74 0x003cacf8 CKS08HeroElementEarth_vf74: the fade clock +0x314 advanced by `dt`; fading out: hidden once
    // +0x2f4 has passed, else UpdateNodeAlphaFade.
    void UpdateRepeatFire(float dt, int8_t level) override;
    // vt+0x7c 0x003ca670 CKS08HeroElementEarth_vf7C: no longer active; the fade out starts from the mesh's first
    // geometry alpha (or +0x2e4), or the mesh is hidden at once without a fade-out time (+0x2f4 == 0).
    void Vf7C() override;
    uint8_t Vf84() override { return m_unk31a; }  // vt+0x84 0x009c0398: fading out
    // vt+0x88 0x003ca638 CKS08HeroElementEarth_vf88: no fade out, the mesh (when set) hidden.
    void Vf88() override;
    uint8_t Vf138() override { return 1; }  // vt+0x138 0x009c03a0

    // 0x003ca028 CKS08HeroElementEarth_SpawnFx_maybe: with the hero, an explosion of +0x300 (the inlined
    // CKSrvFx::AcquireFx) put at the hero's position, triggered and let go.
    void SpawnFx();
    // 0x003ca800 CKS08HeroElementEarth_UpdateNodeAlphaFade_maybe: the mesh's alpha: fading in (+0x318) from +0x2e8 to
    // +0x2e4 over +0x2f0 s, then once +0x2e4 (+0x319 set); not active: from +0x324 to +0x2ec over +0x2f4 s.
    void UpdateNodeAlphaFade();

    uint32_t m_unk2cc;          // +0x2cc (loaded, no reader found)
    uint32_t m_unk2d0;          // +0x2d0 (loaded, no reader found)
    uint32_t m_unk2d4;          // +0x2d4 (loaded, no reader found)
    uint32_t m_unk2d8;          // +0x2d8 (loaded, no reader found)
    uint32_t m_unk2dc;          // +0x2dc (loaded, no reader found)
    uint32_t m_unk2e0;          // +0x2e0 (loaded, no reader found)
    uint32_t m_unk2e4;          // +0x2e4 the mesh's alpha once faded in (and the fade out's start without a geometry)
    uint32_t m_unk2e8;          // +0x2e8 the mesh's alpha when shown (the fade in's start)
    uint32_t m_unk2ec;          // +0x2ec the mesh's alpha at the end of the fade out
    float m_unk2f0;             // +0x2f0 the fade in's duration
    float m_unk2f4;             // +0x2f4 the fade out's duration (0: hidden at once)
    IKSerializable* m_unk2f8;   // +0x2f8 reference (no reader found)
    uint32_t m_unk2fc;          // +0x2fc PostLoad 0 (no reader found)
    IKSerializable* m_unk300;   // +0x300 reference: the explosion's data (SpawnFx)
    IKSerializable* m_unk304;   // +0x304 reference (no reader found)
    IKSerializable* m_unk308;   // +0x308 reference (no reader found)
    CNode* m_unk30c;            // +0x30c the mesh (PostLoad 0; see the BUG above)
    uint32_t m_unk310;          // +0x310 (loaded, no reader found)
    float m_unk314;             // +0x314 the fade clock
    uint8_t m_unk318;           // +0x318 active (vt+0x68 .. vt+0x7c)
    uint8_t m_unk319;           // +0x319 the fade in is done
    uint8_t m_unk31a;           // +0x31a fading out (vt+0x84)
    uint8_t m_pad31b;
    uint32_t m_unk31c;          // +0x31c PostLoad / vt+0x68 0 (no reader found)
    uint32_t m_unk320;          // +0x320 PostLoad / vt+0x68 0 (no reader found)
    uint32_t m_unk324;          // +0x324 the fade out's start alpha
};
DOTD_ASSERT_SIZE(CKS08HeroElementEarth, 0x328);
DOTD_ASSERT_OFFSET(CKS08HeroElementEarth, m_unk2cc, 0x2cc);
DOTD_ASSERT_OFFSET(CKS08HeroElementEarth, m_unk2f0, 0x2f0);
DOTD_ASSERT_OFFSET(CKS08HeroElementEarth, m_unk300, 0x300);
DOTD_ASSERT_OFFSET(CKS08HeroElementEarth, m_unk30c, 0x30c);
DOTD_ASSERT_OFFSET(CKS08HeroElementEarth, m_unk314, 0x314);
DOTD_ASSERT_OFFSET(CKS08HeroElementEarth, m_unk324, 0x324);
