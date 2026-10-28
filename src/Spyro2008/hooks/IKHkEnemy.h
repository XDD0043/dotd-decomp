// IKHkEnemy.h - the enemies' hook base (key 0x1402, vtable 0xb21f38, size 0x1b4_maybe; XXL2:
// Commun/K/KEnemy/IKHkEnemy.h). Its Load (0x27b908) and constructor (0x2790d8, Ghidra
// CKHkS08Enemy_ConstructBase_maybe) sit in the CKHkS08Enemy.cpp unit. Only CKHkS08Enemy derives from it.
//
// The size is the Ghidra struct of the base (CKHkS08Enemy_Load indexes it as 0x1b4-byte elements) and
// matches the last field the base touches (+0x1b0).
//
// Names: DotD reads its arrays in XXL2's member order where the shapes agree: the bounding counts and
// index tables (m_ui8NumberOfBoundingTypes, m_aui8BoundingNumberByType, m_aui8BoundingIndexByType), the
// projectile bounding volumes (m_apBVProj, m_asProjPropeties, m_afBVProjRadius, m_av3BVProjPos), the FX node
// reference arrays (particles, trails, fog boxes), m_ui8EnemyClassType, the ground-contact pair,
// m_PFCpnt, m_v3Position. The rest stays m_unkXX.
#pragma once
#include <cstdint>

#include "k2000/components/CKPathFindingCpnt.h"
#include "k2000/core/Layout.h"
#include "k2000/hooks/GroundContact.h"
#include "k2000/hooks/IKHook.h"
#include "k2000/math/CMatrix34.h"

// XXL2 SEnemyProjectileBoundingProperties (EnemyDef.h): the same 12 bytes.
struct SEnemyProjectileBoundingProperties {
    uint16_t m_ui16Properties;        // +0x00 (u16, swapped)
    uint8_t m_pad02[2];
    uint32_t m_eOwnerType;            // +0x04 EBoundingVolumeOwner, read as one byte
    int8_t m_i8ParentIndex;           // +0x08
    int8_t m_i8AttachHotSpotIndex;    // +0x09
    uint8_t m_pad0A[2];
};
DOTD_ASSERT_SIZE(SEnemyProjectileBoundingProperties, 0xc);

// One animation-layer slot of an enemy (0x2c bytes; AllocAnimLayerSlots 0x277240 fills the first three words, with
// the PS3 data addresses 0xb22068 (the layer's vtable) / 0xb16530 (an AnimBlendSlot embedded at +0x04: +0x08 its
// controller). STUB(C2.7): the layer objects are not ported; only the enemy's animation update drives them).
struct SEnemyAnimLayerSlot {
    uint32_t m_unk00;      // +0x00 0x00b22068
    uint32_t m_unk04;      // +0x04 0x00b16530
    uint32_t m_unk08;      // +0x08 0
    uint32_t m_unk0c[8];   // +0x0c not set
};
DOTD_ASSERT_SIZE(SEnemyAnimLayerSlot, 0x2c);

class IKHkEnemy : public IKHook {
public:
    DOTD_CLASS_KEY(kCategoryHook, 0x50)

    IKHkEnemy();  // 0x002790d8 CKHkS08Enemy_ConstructBase_maybe
    ~IKHkEnemy() override {}

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x0027b908 IKHkEnemy_Load
    int32_t PostLoad(int32_t type) override;  // vt+0x30 0x00277528 IKHkEnemy_PostLoad
    void Start() override {}  // vt+0x50 0x00276f40 IKHkEnemy_Start (empty; Spyro2008/components/CKS08FightZoneCpnt.cpp)
    // vt+0xc4 (CKHkS08Enemy_ResetRuntimeState_maybe 0x00291e88; called by PostLoad).
    virtual void ResetRuntimeState() = 0;
    void ResetMovementState();     // 0x00277df8 IKHkEnemy_ResetMovementState_maybe
    void AllocAnimLayerSlots();    // 0x00277240 CKHkS08Enemy_AllocAnimLayerSlots_maybe

    // The u16 arrays are read raw (no swap): they keep the file bytes (the PS3 sees them big-endian).
    uint16_t* m_unk20;                            // +0x20 count byte, raw u16s
    uint16_t* m_unk24;                            // +0x24 count byte, raw u16s
    uint16_t* m_unk28;                            // +0x28 count byte, raw u16s
    IKSerializable** m_unk2C;                     // +0x2c count byte, references (_maybe XXL2 m_apBV)
    uint8_t m_ui8NumberOfBoundingTypes;           // +0x30 XXL2
    uint8_t m_pad31[3];
    uint8_t* m_aui8BoundingNumberByType;          // +0x34 XXL2 (m_ui8NumberOfBoundingTypes bytes)
    uint8_t* m_aui8BoundingIndexByType;           // +0x38 XXL2
    CVector3* m_unk3C;                            // +0x3c read last (count byte, vectors); not set by the constructor
    uint16_t* m_unk40;                            // +0x40 raw u16s, one per +0x2c reference
    IKSerializable** m_apBVProj;                  // +0x44 XXL2 CKDynBSphereProjectile** (zeroed block; runtime)
    SEnemyProjectileBoundingProperties* m_asProjPropeties;  // +0x48 XXL2
    float* m_afBVProjRadius;                      // +0x4c XXL2
    CVector3* m_av3BVProjPos;                     // +0x50 XXL2
    IKSerializable** m_apParticleNodeFx;          // +0x54 XXL2 CParticlesNodeFx**_maybe
    uint16_t* m_unk58;                            // +0x58 raw u16s, one per particle node
    IKSerializable** m_apTrailNodeFx;             // +0x5c XXL2 CTrailNodeFx**_maybe
    uint8_t* m_unk60;                             // +0x60 one byte per trail, Load fills 0xff
    IKSerializable** m_apFogBoxNodeFx;            // +0x64 XXL2 CFogBoxNodeFx**_maybe
    uint16_t* m_unk68;                            // +0x68 raw u16s, one per fog box
    uint8_t m_ui8EnemyClassType;                  // +0x6c XXL2 (indexes CKHkS08Enemy's per-kind counts)
    uint8_t m_pad6D[3];
    CGroundContactDatasIn m_GrdContDatasIn;       // +0x70 XXL2
    CGroundContactDatasInOut m_GrdContDatasInOut; // +0x80 XXL2
    uint32_t m_unkac;  // +0xac  (C2.2 strict3)
    float m_unkb0;  // +0xb0  (C2.2 strict3)
    uint32_t m_unkb4;  // +0xb4  (C2.2 strict3)
    IKSerializable* m_unkB8;                      // +0xb8 reference (null in the LVL010 samples)
    CKPathFindingCpnt m_PFCpnt;                   // +0xbc XXL2
    CVector3 m_v3Position;                        // +0x134 XXL2
    float m_unk140;  // +0x140  (C2.2 strict3)
    float m_unk144;  // +0x144  (C2.2 strict3)
    float m_unk148;  // +0x148  (C2.2 strict3)
    uint8_t m_unk14c;  // +0x14c  (C2.2 strict3)
    uint8_t m_pad14d[3];
    CMatrix34* m_unk150;  // +0x150 PostLoad: RwMatrixCreate
    uint32_t m_pad154;
    CVector3 m_unk158;                            // +0x158 Load copies the zero vector (0xc50d64); _maybe m_v3Speed
    SEnemyAnimLayerSlot** m_unk164;               // +0x164 constructor 0; AllocAnimLayerSlots: one block of slots per layer
    IKSerializable* m_pGroupSquad;                // +0x168 _maybe XXL2 CKGrpSquad* m_pGroupSquad (reference)
    float m_unk16C;                               // +0x16c
    uint32_t m_unk170;                            // +0x170
    IKSerializable* m_unk174;                     // +0x174 Load 0; ResetMovementState: the scene node (+0x1c)
    uint32_t m_unk178[4];                         // +0x178
    IKSerializable* m_unk188;                     // +0x188 reference
    IKSerializable** m_unk18C;                    // +0x18c read first (count byte, references; _maybe XXL2 m_apObjectNode)
    uint32_t m_unk190[7];                         // +0x190
    uint8_t m_unk1AC;                             // +0x1ac constructor 0
    uint8_t m_unk1ad;  // +0x1ad  (C2.2 strict3)
    uint8_t m_pad1ae[2];
    IKSerializable* m_pShadowCpnt;                // +0x1b0 XXL2 CKShadowCpnt* (reference)
};
DOTD_ASSERT_SIZE(IKHkEnemy, 0x1b4);
DOTD_ASSERT_OFFSET(IKHkEnemy, m_unk20, 0x20);
DOTD_ASSERT_OFFSET(IKHkEnemy, m_unk2C, 0x2c);
DOTD_ASSERT_OFFSET(IKHkEnemy, m_ui8NumberOfBoundingTypes, 0x30);
DOTD_ASSERT_OFFSET(IKHkEnemy, m_aui8BoundingNumberByType, 0x34);
DOTD_ASSERT_OFFSET(IKHkEnemy, m_unk3C, 0x3c);
DOTD_ASSERT_OFFSET(IKHkEnemy, m_unk40, 0x40);
DOTD_ASSERT_OFFSET(IKHkEnemy, m_apBVProj, 0x44);
DOTD_ASSERT_OFFSET(IKHkEnemy, m_av3BVProjPos, 0x50);
DOTD_ASSERT_OFFSET(IKHkEnemy, m_apParticleNodeFx, 0x54);
DOTD_ASSERT_OFFSET(IKHkEnemy, m_unk60, 0x60);
DOTD_ASSERT_OFFSET(IKHkEnemy, m_unk68, 0x68);
DOTD_ASSERT_OFFSET(IKHkEnemy, m_ui8EnemyClassType, 0x6c);
DOTD_ASSERT_OFFSET(IKHkEnemy, m_GrdContDatasIn, 0x70);
DOTD_ASSERT_OFFSET(IKHkEnemy, m_GrdContDatasInOut, 0x80);
DOTD_ASSERT_OFFSET(IKHkEnemy, m_unkB8, 0xb8);
DOTD_ASSERT_OFFSET(IKHkEnemy, m_PFCpnt, 0xbc);
DOTD_ASSERT_OFFSET(IKHkEnemy, m_v3Position, 0x134);
DOTD_ASSERT_OFFSET(IKHkEnemy, m_unk158, 0x158);
DOTD_ASSERT_OFFSET(IKHkEnemy, m_unk164, 0x164);
DOTD_ASSERT_OFFSET(IKHkEnemy, m_pGroupSquad, 0x168);
DOTD_ASSERT_OFFSET(IKHkEnemy, m_unk16C, 0x16c);
DOTD_ASSERT_OFFSET(IKHkEnemy, m_unk174, 0x174);
DOTD_ASSERT_OFFSET(IKHkEnemy, m_unk188, 0x188);
DOTD_ASSERT_OFFSET(IKHkEnemy, m_unk18C, 0x18c);
DOTD_ASSERT_OFFSET(IKHkEnemy, m_unk1AC, 0x1ac);
DOTD_ASSERT_OFFSET(IKHkEnemy, m_pShadowCpnt, 0x1b0);
DOTD_ASSERT_OFFSET(IKHkEnemy, m_unkac, 0xac);
DOTD_ASSERT_OFFSET(IKHkEnemy, m_unkb0, 0xb0);
DOTD_ASSERT_OFFSET(IKHkEnemy, m_unkb4, 0xb4);
DOTD_ASSERT_OFFSET(IKHkEnemy, m_unk140, 0x140);
DOTD_ASSERT_OFFSET(IKHkEnemy, m_unk144, 0x144);
DOTD_ASSERT_OFFSET(IKHkEnemy, m_unk148, 0x148);
DOTD_ASSERT_OFFSET(IKHkEnemy, m_unk14c, 0x14c);
DOTD_ASSERT_OFFSET(IKHkEnemy, m_unk150, 0x150);
DOTD_ASSERT_OFFSET(IKHkEnemy, m_unk1ad, 0x1ad);
