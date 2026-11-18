// CKProjectileDataTypeBallisticPFX.h - the launch parameters of a ballistic projectile (a component; key
// 0xa5cc, vtable 0xb2e158, size 0x74). Original unit: CKProjectileDataTypeBallisticPFX.cpp
// (0x5854c8-0x586258). Base: IKComponent. Referenced by CKProjectileAccessor (+0x08). No XXL2 class of
// this name. Types from the LVL010 data (floats where the samples are floats).
#pragma once
#include <cstdint>

#include "k2000/components/IKComponent.h"
#include "k2000/core/Layout.h"

class CKProjectileDataTypeBallisticPFX : public IKComponent {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x297)
    int32_t IsKindOfClass(uint32_t key) override {  // vt+0x08 0x9cb338
        return key == 0xa5cc || key == 0x6 || key == 0xc || key == 0xa58c;
    }
    DOTD_DECLARE_FACTORIES(CKProjectileDataTypeBallisticPFX)

    // The constructor inlined in 0x00585648 CKProjectileDataTypeBallisticPFX_Create: the vtable only.
    CKProjectileDataTypeBallisticPFX() {}
    ~CKProjectileDataTypeBallisticPFX() override {}
    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x00585928 CKProjectileDataTypeBallisticPFX_Load
    // vt+0x24 0x00585740 (Ghidra: IKComponent_RecursiveRegistration; this class's slot): type 0 registers the object with
    // the saving manager; types 4..7 stop there; then the references +0x04, +0x14, +0x08, +0x0c, +0x10, +0x18 recurse.
    void RecursiveRegistration(int32_t type) override;

    // The runtime's reads (C2.7, CKProjectileTypeBallisticPFX.cpp) name the fields; the flags +0x50 select the parts.
    IKSerializable* m_unk04;  // +0x04 a reference: the death explosion (CKExplosionFxData; flag 0x400)
    IKSerializable* m_unk08;  // +0x08 a reference: the shock wave (CKShockWaveFxData; death flag 0x800, impact 0x2000)
    IKSerializable* m_unk0c;  // +0x0c a reference: the fire ball (flag 0x1000; null in LVL010)
    IKSerializable* m_unk10;  // +0x10 a reference: the particle effect following the node (flag 0x40)
    IKSerializable* m_unk14;  // +0x14 a reference: the launch explosion (flag 0x2000000)
    IKSerializable* m_unk18;  // +0x18 a reference: the camera quake's settings (a CKQuakeCameraLauncher; flag 0x20000000)
    float m_unk1c;            // +0x1c (samples: 0, 30.0) the gravity
    float m_unk20;            // +0x20 the bounce restitution (flag 0x2), the speed kept after a damage bounce
    float m_unk24;            // +0x24 (samples: 0) the drag (the speed's fraction lost per second)
    float m_unk28;            // +0x28 the lifetime (plus a random part of +0x54)
    uint8_t m_unk2c;          // +0x2c (+0x2d..+0x2f padding) past its lifetime it dies only when not drawn
    uint8_t m_pad2d[3];
    float m_unk30;            // +0x30 the ground probe's half height (times the scale)
    float m_unk34;            // +0x34 the speed above which a hit leaves an emission point (option 0x20)
    float m_unk38;            // +0x38 the trail's half width
    float m_unk3c;            // +0x3c (samples: 180.0, 750.0) the spin in degrees per second (flags 0x40000 / 0x400000 /
                              //       0x1000000)
    float m_unk40;            // +0x40 the volume's radius (times the scale), the rolling radius
    uint8_t m_unk44;          // +0x44 a damage volume (CKDynBSphereProjectile)
    uint8_t m_unk45;          // +0x45 (+0x46..+0x47 padding) the ground collision on
    uint8_t m_pad46[2];
    float m_unk48;            // +0x48 (samples: 5.0, tiny garbage) the sound's distance to the camera (option 0x200000)
    uint8_t m_unk4c;          // +0x4c (+0x4d padding) the volume's owner type
    uint8_t m_pad4d;
    uint16_t m_unk4e;         // +0x4e the volume's property flags
    // +0x50 (samples: 0x02010459, 0x0316c4d9) the flags: 0x1 turned along the flight, 0x2 bounce, 0x4 land, 0x8 dies
    // slower than 0.1, 0x10 dies at the lifetime, 0x40 particle effect, 0x100 random rotation / rolling, 0x200 the ground
    // test masks (1, 0) (else (1, 8)), 0x400 death explosion, 0x800 death shock wave, 0x1000 fire ball, 0x2000 impact
    // shock wave, 0x4000 no hit answer, 0x8000 / 0x20000 / 0x10000 dies hitting a volume of owner type 1 / 2 / 3,
    // 0x40000 / 0x400000 / 0x1000000 spins about Y / X / Z, 0x80000 / 0x100000 the trail's side, 0x800000 dies on a wall
    // instead of landing (mode C), 0x2000000 launch explosion, 0x4000000 / 0x8000000 / 0x10000000 steering toward the
    // heroes / mechanisms / enemies, 0x20000000 camera quake.
    uint32_t m_ui32Flags;
    float m_unk54;            // +0x54 (samples: 0) the lifetime's random part
    float m_unk58;            // +0x58 the steering's attraction
    float m_unk5c;            // +0x5c the steering's reach (a box distance)
    float m_unk60;            // +0x60 (samples: 0) the age from which it steers
    float m_unk64;            // +0x64 the scale's lower bound
    float m_unk68;            // +0x68 the scale's upper bound
    float m_unk6c;            // +0x6c the scale reached at the lifetime (1: none)
    float m_unk70;            // +0x70 (samples: 0) the fade-out time before the lifetime
};
DOTD_ASSERT_SIZE(CKProjectileDataTypeBallisticPFX, 0x74);
DOTD_ASSERT_OFFSET(CKProjectileDataTypeBallisticPFX, m_unk04, 0x04);
DOTD_ASSERT_OFFSET(CKProjectileDataTypeBallisticPFX, m_unk08, 0x08);
DOTD_ASSERT_OFFSET(CKProjectileDataTypeBallisticPFX, m_unk0c, 0x0c);
DOTD_ASSERT_OFFSET(CKProjectileDataTypeBallisticPFX, m_unk10, 0x10);
DOTD_ASSERT_OFFSET(CKProjectileDataTypeBallisticPFX, m_unk14, 0x14);
DOTD_ASSERT_OFFSET(CKProjectileDataTypeBallisticPFX, m_unk18, 0x18);
DOTD_ASSERT_OFFSET(CKProjectileDataTypeBallisticPFX, m_unk1c, 0x1c);
DOTD_ASSERT_OFFSET(CKProjectileDataTypeBallisticPFX, m_unk20, 0x20);
DOTD_ASSERT_OFFSET(CKProjectileDataTypeBallisticPFX, m_unk24, 0x24);
DOTD_ASSERT_OFFSET(CKProjectileDataTypeBallisticPFX, m_unk28, 0x28);
DOTD_ASSERT_OFFSET(CKProjectileDataTypeBallisticPFX, m_unk2c, 0x2c);
DOTD_ASSERT_OFFSET(CKProjectileDataTypeBallisticPFX, m_unk30, 0x30);
DOTD_ASSERT_OFFSET(CKProjectileDataTypeBallisticPFX, m_unk34, 0x34);
DOTD_ASSERT_OFFSET(CKProjectileDataTypeBallisticPFX, m_unk38, 0x38);
DOTD_ASSERT_OFFSET(CKProjectileDataTypeBallisticPFX, m_unk3c, 0x3c);
DOTD_ASSERT_OFFSET(CKProjectileDataTypeBallisticPFX, m_unk40, 0x40);
DOTD_ASSERT_OFFSET(CKProjectileDataTypeBallisticPFX, m_unk44, 0x44);
DOTD_ASSERT_OFFSET(CKProjectileDataTypeBallisticPFX, m_unk45, 0x45);
DOTD_ASSERT_OFFSET(CKProjectileDataTypeBallisticPFX, m_unk48, 0x48);
DOTD_ASSERT_OFFSET(CKProjectileDataTypeBallisticPFX, m_unk4c, 0x4c);
DOTD_ASSERT_OFFSET(CKProjectileDataTypeBallisticPFX, m_unk4e, 0x4e);
DOTD_ASSERT_OFFSET(CKProjectileDataTypeBallisticPFX, m_ui32Flags, 0x50);
DOTD_ASSERT_OFFSET(CKProjectileDataTypeBallisticPFX, m_unk54, 0x54);
DOTD_ASSERT_OFFSET(CKProjectileDataTypeBallisticPFX, m_unk58, 0x58);
DOTD_ASSERT_OFFSET(CKProjectileDataTypeBallisticPFX, m_unk5c, 0x5c);
DOTD_ASSERT_OFFSET(CKProjectileDataTypeBallisticPFX, m_unk60, 0x60);
DOTD_ASSERT_OFFSET(CKProjectileDataTypeBallisticPFX, m_unk64, 0x64);
DOTD_ASSERT_OFFSET(CKProjectileDataTypeBallisticPFX, m_unk68, 0x68);
DOTD_ASSERT_OFFSET(CKProjectileDataTypeBallisticPFX, m_unk6c, 0x6c);
DOTD_ASSERT_OFFSET(CKProjectileDataTypeBallisticPFX, m_unk70, 0x70);
