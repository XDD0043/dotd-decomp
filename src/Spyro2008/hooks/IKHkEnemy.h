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
#include "k2000/animation/AnimBlendSlot.h"
#include "k2000/core/Layout.h"
#include "k2000/hooks/GroundContact.h"
#include "k2000/hooks/IKHook.h"
#include "k2000/math/CMatrix34.h"
#include "k2000/services/CKSrvAvoidance.h"

class CKS08EnemyCpnt;
class CKSrvCollision;
class CKSrvPathFinding;
struct CLine;
struct CPFPoint;
struct CSlideGroundEdgeDatasOut;

class CKEnemySectorCpnt;

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

// One animation-layer slot of an enemy (0x2c bytes, a small object: its PS3 vtable 0xb22068 holds only destructors). An
// AnimBlendSlot is embedded at +0x04 (CKHkS08Enemy's layer controller: a CKBlenderController whose active child
// (+0x10) plays the slot's animation; IKHkEnemy::Activate gives it its controller, AnimBlendSlot_InitThunk 0x79ff0),
// then the request the layer update (CKHkS08Enemy_AdvanceAnimLayer_maybe 0x286220) turns into a crossfade.
// Animations are rows of the kind's CAnimationDictionary (the sector component's +0x08 per layer, column = slot).
struct SEnemyAnimLayerSlot {
    uint32_t m_unk00;           // +0x00 the PS3 vtable word 0x00b22068 (AllocAnimLayerSlots)
    AnimBlendSlot m_blendSlot;  // +0x04 (its vtable 0xb16530; controller +0x08 cleared by AllocAnimLayerSlots)
    float m_unk1c;              // +0x1c the requested start time (RequestAnim)
    float m_unk20;              // +0x20 the requested crossfade length (RequestAnim)
    uint8_t m_unk24;            // +0x24 the playing animation (dictionary row)
    uint8_t m_unk25;            // +0x25 the requested animation (dictionary row)
    uint8_t m_unk26;            // +0x26 keep the normalised time over the change (and play backwards while set on slot 0)
    uint8_t m_unk27;            // +0x27 restart even when the row does not change
    uint8_t m_unk28;            // +0x28 forced (ForceAnimSlot)
    uint8_t m_pad29[3];
};
DOTD_ASSERT_SIZE(SEnemyAnimLayerSlot, 0x2c);
DOTD_ASSERT_OFFSET(SEnemyAnimLayerSlot, m_blendSlot, 0x04);
DOTD_ASSERT_OFFSET(SEnemyAnimLayerSlot, m_unk1c, 0x1c);
DOTD_ASSERT_OFFSET(SEnemyAnimLayerSlot, m_unk24, 0x24);

class IKHkEnemy : public IKHook {
public:
    DOTD_CLASS_KEY(kCategoryHook, 0x50)

    // vt+0x08 0x009bc778 IKHkEnemy_IsKindOfClass: 0x1402, then IKHook's.
    int32_t IsKindOfClass(uint32_t key) override { return key == 0x1402 || IKHook::IsKindOfClass(key); }

    IKHkEnemy();  // 0x002790d8 CKHkS08Enemy_ConstructBase_maybe
    ~IKHkEnemy() override {}
    // vt+0x10 0x00276f00 IKHkEnemy_ClearReferences (CKHkS08Enemy_Destroy 0x294af0 calls it): vt+0xc0 (FreeBuffers).
    void Destroy() override { FreeBuffers(); }
    // vt+0x68 0x00276f48 IKHkEnemy_OnLevelExit_maybe (and CKHkS08Enemy_Stop 0x294a50, which only calls it): empty, as
    // IKHook's.

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x0027b908 IKHkEnemy_Load
    int32_t PostLoad(int32_t type) override;  // vt+0x30 0x00277528 IKHkEnemy_PostLoad
    void Update(IKTime* clock) override;  // vt+0x7c 0x00277650 IKHkEnemy_Update
    void Start() override {}  // vt+0x50 0x00276f40 IKHkEnemy_Start (empty; Spyro2008/components/CKS08FightZoneCpnt.cpp)
    // vt+0xc4 (CKHkS08Enemy_ResetRuntimeState_maybe 0x00291e88; called by PostLoad).
    virtual void ResetRuntimeState() = 0;
    // The rest of IKHkEnemy's slots (vtable 0xb21f38; CKHkS08Enemy's own start at vt+0x128). Where the base and the
    // derived vtables hold the same function, it is IKHkEnemy's (its body sits in CKHkS08Enemy.cpp).
    virtual void FreeBuffers();                                // vt+0xc0 0x002778a0 CKHkS08Enemy_FreeBuffers_maybe
    virtual void VfC8() {}                                     // vt+0xc8 0x00276f50 IKHkEnemy_vfC8 (empty)
    virtual void Activate();                                   // vt+0xcc 0x0027b590 CKHkS08Enemy_RegisterActive (IKHkEnemy's)
    virtual void Deactivate();                                 // vt+0xd0 0x0027a748 CKHkS08Enemy_UnregisterActive (IKHkEnemy's)
    virtual void VfD4() {}                                     // vt+0xd4 0x009bc7e0 IKHkEnemy_vfD4 (empty)
    virtual uint8_t CanSpawnFromSquad(IKSerializable* /*squad*/) { return 1; }  // vt+0xd8 0x009bc7e8 IKHkEnemy_vfD8
    // vt+0xdc 0x00277c90 IKHkEnemy_TeleportTo_maybe: the position into +0x134 and the path finding (0x1e3a40), then the
    // node placed by (0xd0918). CKHkS08Enemy's override is SpawnAtPosition 0x2937c8.
    virtual void SpawnAtPosition(const CVector3* position, const CVector3* direction, uint32_t flags);
    virtual uint32_t ConstrainToGroundAndNavMesh();            // vt+0xe0 0x00278330 IKHkEnemy_ConstrainToGroundAndNavMesh_maybe
    virtual void UpdateShadowCaster();                         // vt+0xe4 0x002796e8 CKHkS08Enemy_UpdateShadowCaster
    // vt+0xe8 0x009bc7f0 CKHkS08Enemy_vfE8: the ground of the contact (+0x80).
    virtual void* GetGround() { return m_GrdContDatasInOut.m_pGround; }
    virtual void* VfEC() = 0;                                  // vt+0xec (pure; CKHkS08Enemy 0x9bc998: this + 0x1c4)
    virtual void EnableVolume(int32_t index);                  // vt+0xf0 0x00277850 CKHkS08Enemy_EnableVolume
    virtual void DisableVolume(int32_t index);                 // vt+0xf4 0x00277800 CKHkS08Enemy_DisableVolume
    virtual void EnableVolumeGroup(int32_t group);             // vt+0xf8 0x00277738 CKHkS08Enemy_EnableVolumeGroup
    virtual void DisableVolumeGroup(int32_t group);            // vt+0xfc 0x00277670 CKHkS08Enemy_DisableVolumeGroup
    virtual void ClearVolumeGroupFlags(int32_t group, uint16_t flags);  // vt+0x100 0x00276f88 CKHkS08Enemy_ClearVolumeGroupFlags
    virtual void SetVolumeGroupFlags(int32_t group, uint16_t flags);    // vt+0x104 0x00277008 CKHkS08Enemy_SetVolumeGroupFlags
    virtual void EnableCollisionSphere(uint32_t index);        // vt+0x108 0x00279998 CKHkS08Enemy_EnableCollisionSphere_maybe
    virtual void ReleaseDynSphere(int32_t index);              // vt+0x10c 0x00277d08 CKHkS08Enemy_ReleaseDynSphere_maybe
    virtual void ClearDynSphereFlags(int32_t index, uint16_t flags);    // vt+0x110 0x00277f50 CKHkS08Enemy_ClearDynSphereFlags
    virtual void SetDynSphereFlags(int32_t index, uint16_t flags);      // vt+0x114 0x00277dc8 CKHkS08Enemy_SetDynSphereFlags
    virtual void StartTrailRibbon(int32_t index, const void* a, const void* b);        // vt+0x118 0x0027c7b0 CKHkS08Enemy_StartTrailRibbon_maybe
    virtual void StopTrailRibbon(int32_t index);               // vt+0x11c 0x0027c700 CKHkS08Enemy_StopTrailRibbon_maybe
    virtual void SetTrailRibbonEndpoints(int32_t index, const void* a, const void* b); // vt+0x120 0x00277f80 CKHkS08Enemy_SetTrailRibbonEndpoints_maybe
    // vt+0x124 0x00278008 IKHkEnemy_vf124: the life flags' bit 3 (the update skip bit) set (rlwinm 28 / rlwinm 4 clear
    // it, ori 8 sets it). CKHkS08Enemy's override is ForceState16_maybe 0x2820e8.
    virtual void ForceState16() { m_bitArray |= 8u; }
    void ResetMovementState();     // 0x00277df8 IKHkEnemy_ResetMovementState_maybe
    // DOTD helpers of ConstrainToGroundAndNavMesh (inlined code of the original; CKHkS08Enemy.cpp).
    uint8_t SweepFromPrevious(CKSrvCollision* collision, CLine* line, CSlideGroundEdgeDatasOut* slide);
    float ComponentHeight() const;
    static bool PointInNodeBox(CKSrvPathFinding* pathFinding, const CPFPoint* point);
    static void CopyMatrix(CMatrix34* to, const CMatrix34* from);
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
    float m_unk154;  // +0x154 the yaw (the steering, ResolveGroundAndApplyTransform's Mat4_SetRotationAboutAxis)
    CVector3 m_unk158;                            // +0x158 Load copies the zero vector (0xc50d64); _maybe m_v3Speed
    SEnemyAnimLayerSlot** m_unk164;               // +0x164 constructor 0; AllocAnimLayerSlots: one block of slots per layer
    IKSerializable* m_pGroupSquad;                // +0x168 _maybe XXL2 CKGrpSquad* m_pGroupSquad (reference)
    // +0x16c the avoidance agent the avoidance service lists while the enemy is active (RegisterActive /
    // UnregisterActive): radius (Load, then the component's m_afParams[1]), a Load word, the node (Load 0;
    // ResetMovementState: the scene node +0x1c), a vector and a word AddAgent sets.
    CKAvoidanceAgent m_avoidance;                 // +0x16c
    CKS08EnemyCpnt* m_unk188;                     // +0x188 reference: the enemy's tuning component (Activate copies it to +0x884)
    CKEnemySectorCpnt** m_unk18C;                 // +0x18c read first (count byte, references): one CKEnemySectorCpnt per
                                                  //        fight-zone variant (GetSectorIndex)
    // +0x190 the shadow caster's ground (a CKShadowGround for CKSrvShadow: point, normal, word, flags byte +0x1ac, used
    // byte +0x1ad).
    CVector3 m_unk190;                            // +0x190 the ground point
    CVector3 m_unk19C;                            // +0x19c the ground normal
    float m_unk1a8;                               // +0x1a8
    uint8_t m_unk1AC;                             // +0x1ac constructor 0 (bit 4: the ground is not a shadow receiver)
    uint8_t m_unk1ad;                             // +0x1ad the shadow service's used byte (registered)
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
DOTD_ASSERT_OFFSET(IKHkEnemy, m_avoidance, 0x16c);
DOTD_ASSERT_OFFSET(IKHkEnemy, m_unk190, 0x190);
DOTD_ASSERT_OFFSET(IKHkEnemy, m_unk1a8, 0x1a8);
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
