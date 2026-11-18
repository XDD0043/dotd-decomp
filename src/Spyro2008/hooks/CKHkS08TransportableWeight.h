// CKHkS08TransportableWeight.h - a transportable weight hook (key 0x3142, vtable 0xb28e28, size 0x1cc).
// Original unit: CKHkS08TransportableWeight.cpp. No XXL2 class. Derives from CKHkS08TransportableKey (its
// Load 0x4b6500 calls CKHkS08TransportableKey_Load first; the class tree's 0x3002 parent is the Key's own
// base). Base of CKHkS08PowerBucket. Field names are placeholders.
#pragma once
#include <cstdint>

#include "Spyro2008/hooks/CKHkS08TransportableKey.h"
#include "k2000/core/Layout.h"

class CKHkS08TransportableWeight : public CKHkS08TransportableKey {
public:
    DOTD_CLASS_KEY(kCategoryHook, 0xc5)
    int32_t IsKindOfClass(uint32_t key) override {  // vt+0x08 0x9c54d0
        return key == 0x3142 || key == 0x3002 || key == 0x3082 || key == 0xd82 || key == 0x2 || key == 0x2fe ||
               key == 0x3fe || key == 0xc;
    }
    DOTD_DECLARE_FACTORIES(CKHkS08TransportableWeight)

    // 0x004b4a98 (Ghidra CKHkS08PowerBucket_ConstructBase_maybe; it sets this class's vtable 0xb28e28),
    // inlined in 0x004b5808 CKHkS08TransportableWeight_Create: the CKHkS08TransportableKey part only.
    CKHkS08TransportableWeight() {}
    ~CKHkS08TransportableWeight() override {}

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x004b6500 CKHkS08TransportableWeight_Load
    int32_t PostLoad(int32_t type) override;            // vt+0x30 0x004b48c0 CKHkS08TransportableWeight_PostLoad
    void Start() override;  // vt+0x50 0x004b4880 CKHkS08TransportableWeight_Start (C2.2)
    void Vf124() override;  // vt+0x124 0x004b5d78 CKHkS08TransportableWeight_vf124
    void Vf180() override {}  // vt+0x180 0x9c5560 CKHkS08TransportableWeight_vf180 (empty)
    // vt+0x10 0x004b4968 CKHkS08TransportableWeight_Destroy / vt+0x68 0x004b4858 _Stop: the Key's.
    // (0x004b4bc0 _Destructor / 0x004b4a68 _BaseDestructor: the vtable, then the Key's.)
    void Update(IKTime* clock) override;  // vt+0x7c 0x004b5df0 CKHkS08TransportableWeight_Update
    float Vf104() override { return m_unk18c; }  // vt+0x104 0x9c5550: +0x18c
    CSGHotSpot* Vf118() override { return reinterpret_cast<CSGHotSpot*>(m_unk140); }  // vt+0x118 0x9c5548: +0x140
    void Vf120() override;     // vt+0x120 0x004b7308 CKHkS08TransportableWeight_vf120
    void Vf17C() override {}   // vt+0x17c 0x9c5558 (empty)
    uint8_t Vf184() override { return static_cast<uint8_t>(m_unk2C ^ 1u); }  // vt+0x184 0x9c5568: not marked (+0x2c)
    // vt+0xec 0x004b4bf0 CKHkS08TransportableWeight_vfEC: the ground it rests on (+0xc0) once in a state (+0x114 not
    // 0xff) and landed (+0xbc), or at rest (state 1) with +0x2d set; else null.
    IKSerializable* VfEC() override {
        if (m_unk114 == 0xff) return nullptr;
        if (m_bLanded != 0) return m_pDynamicGround;
        if (m_unk114 == 1 && m_unk2D != 0) return m_pDynamicGround;
        return nullptr;
    }
    uint8_t VfF0(IKSerializable* carrier) override;  // vt+0xf0 0x004b4c30 CKHkS08TransportableWeight_vfF0
    // vt+0xf8 0x004b4d18 CKHkS08TransportableWeight_vfF8
    uint8_t VfF8(IKSerializable* carrier, const CVector3* velocity) override;
    // vt+0x154 0x004b4f38 CKHkS08TransportableWeight_OnImpact_maybe
    void Vf154(const CGroundContactDatasInOut* contact) override;
    uint8_t Vf160(IKTime* clock) override;  // vt+0x160 0x004b5120 CKHkS08TransportableWeight_vf160
    void Vf168() override;                  // vt+0x168 0x004b6ae8 CKHkS08TransportableWeight_SpawnImpactFx_maybe
    void Vf188(float dt) override;          // vt+0x188 0x004b5860 CKHkS08TransportableWeight_vf188
    void Vf18C() override;                  // vt+0x18c 0x004b7038 CKHkS08TransportableWeight_SpawnAltImpactFx_maybe
    // The weight's effect (+0x138): its data +0x134 attached to the hot spot +0x144 and acquired (the inlined pooled lookup
    // of vf120 and Update).
    void AcquireWeightFx();

    IKSerializable* m_unk130;   // +0x130 reference (LVL010: a CKSoundDictionaryID)
    IKSerializable* m_unk134;   // +0x134 reference
    IKSerializable* m_unk138;   // +0x138 runtime (PostLoad 0x4b48c0 clears it): an effect (vf124 releases it)
    IKSerializable* m_unk13c;   // +0x13c reference (LVL010: a CKExplosionFxData)
    IKSerializable* m_unk140;   // +0x140 reference (LVL010: a CSGHotSpot)
    IKSerializable* m_unk144;   // +0x144 reference (LVL010: a CSGHotSpot)
    float m_unk148;             // +0x148
    float m_unk14c;             // +0x14c
    CVector3 m_vUnk150;         // +0x150 runtime (vfF0: 0)
    CVector3 m_vUnk15c;         // +0x15c runtime (vfF0: 0)
    float m_unk168;             // +0x168
    float m_unk16c;             // +0x16c
    float m_unk170;             // +0x170
    float m_unk174;             // +0x174
    float m_unk178;             // +0x178
    CVector3 m_vSwingUp;        // +0x17c runtime: the carried weight's up axis (vf188), the pose's up
    float m_unk188;             // +0x188
    float m_unk18c;             // +0x18c
    CVector3 m_vAimPoint;       // +0x190 runtime (vfF0: FLT_MAX x3 = none): +0x19c from the node towards the hot spot +0x140
    float m_unk19c;             // +0x19c
    float m_fSwingRight;        // +0x1a0 runtime: the swing about the hot spot's right axis (vf188, clamped to [-1, 1])
    float m_fSwingAt;           // +0x1a4 runtime: the swing about its at axis (clamped to [lower, 1])
    float m_fSwingRightSpeed;   // +0x1a8 runtime
    float m_fSwingAtSpeed;      // +0x1ac runtime
    IKSerializable* m_unk1b0;   // +0x1b0 reference (LVL010: a CKExplosionFxData)
    CVector3 m_vPrevGripPos;    // +0x1b4 runtime (vfF0: FLT_MAX x3 = none): the hot spot's last world position (vf188)
    CVector3 m_vPrevGripVel;    // +0x1c0 runtime (vfF0: 0): its last velocity (vf188)
};
DOTD_ASSERT_SIZE(CKHkS08TransportableWeight, 0x1cc);
DOTD_ASSERT_OFFSET(CKHkS08TransportableWeight, m_unk130, 0x130);
DOTD_ASSERT_OFFSET(CKHkS08TransportableWeight, m_unk134, 0x134);
DOTD_ASSERT_OFFSET(CKHkS08TransportableWeight, m_unk13c, 0x13c);
DOTD_ASSERT_OFFSET(CKHkS08TransportableWeight, m_unk140, 0x140);
DOTD_ASSERT_OFFSET(CKHkS08TransportableWeight, m_unk144, 0x144);
DOTD_ASSERT_OFFSET(CKHkS08TransportableWeight, m_unk148, 0x148);
DOTD_ASSERT_OFFSET(CKHkS08TransportableWeight, m_unk14c, 0x14c);
DOTD_ASSERT_OFFSET(CKHkS08TransportableWeight, m_unk168, 0x168);
DOTD_ASSERT_OFFSET(CKHkS08TransportableWeight, m_unk16c, 0x16c);
DOTD_ASSERT_OFFSET(CKHkS08TransportableWeight, m_unk170, 0x170);
DOTD_ASSERT_OFFSET(CKHkS08TransportableWeight, m_unk174, 0x174);
DOTD_ASSERT_OFFSET(CKHkS08TransportableWeight, m_unk178, 0x178);
DOTD_ASSERT_OFFSET(CKHkS08TransportableWeight, m_unk188, 0x188);
DOTD_ASSERT_OFFSET(CKHkS08TransportableWeight, m_unk18c, 0x18c);
DOTD_ASSERT_OFFSET(CKHkS08TransportableWeight, m_unk19c, 0x19c);
DOTD_ASSERT_OFFSET(CKHkS08TransportableWeight, m_unk1b0, 0x1b0);
DOTD_ASSERT_OFFSET(CKHkS08TransportableWeight, m_vSwingUp, 0x17c);
DOTD_ASSERT_OFFSET(CKHkS08TransportableWeight, m_vAimPoint, 0x190);
DOTD_ASSERT_OFFSET(CKHkS08TransportableWeight, m_fSwingRight, 0x1a0);
DOTD_ASSERT_OFFSET(CKHkS08TransportableWeight, m_vPrevGripPos, 0x1b4);
DOTD_ASSERT_OFFSET(CKHkS08TransportableWeight, m_vPrevGripVel, 0x1c0);
