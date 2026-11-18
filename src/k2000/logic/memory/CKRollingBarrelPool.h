// CKRollingBarrelPool.h - the barrels a CKHkRollingBarrel rolls (key 0x118c, vtable 0xb26668, size 0x9c): a fixed pool
// of barrel records (node, mesh, ...), the barrels' scale curve, the trail effects and the trail's points. Original unit:
// CKRollingBarrelPool.cpp (0x441f60-0x443bb8). No game file holds one (outputs/remake/kp3-class-usage.json); its users
// are CKHkRollingBarrel's methods (P18). DotD only; names ours.
#pragma once
#include <cstdint>

#include "k2000/core/IKSerializable.h"
#include "k2000/core/Layout.h"
#include "k2000/hooks/GroundContact.h"
#include "k2000/math/CMatrix34.h"
#include "k2000/services/CKSrvShadow.h"
#include "k2000/util/TVector.h"

class CKRollingBarrelPool : public IKSerializable {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x46)
    int32_t IsKindOfClass(uint32_t key) override { return key == 0x118c || key == 0xc; }  // vt+0x08 0x9c3520
    DOTD_DECLARE_FACTORIES(CKRollingBarrelPool)

    // One barrel (0x90 bytes; the pool's block +0x0c). The Load sets the four references and clears the rest it
    // touches; the hook's spawn / update code (CKHkRollingBarrel) fills the others. (C2.8 port-final F02 typed the
    // runtime words from CKHkRollingBarrel's code: +0x08 / +0x18 / +0x3c are floats, +0x1c..+0x8b the fields below.)
    struct Barrel {
        IKSerializable* m_pUnk00;   // +0x00 a reference: the barrel's CSGMovable (placed on the path, turned, scaled)
        IKSerializable* m_pNode;    // +0x04 a reference: a scene node, hidden by the Load (scene flag 4); it rolls
        float m_unk08;              // +0x08 the Load sets 0: the distance along the hook's path
        CVector3 m_unk0c;           // +0x0c the Load copies the vector at 0x00c50d4c (0, 0, 1): the path direction
        float m_unk18;              // +0x18 the Load sets 0: the speed along the path
        CVector3 m_vTargetDir;      // +0x1c the horizontal heading the barrel turns towards
        CVector3 m_vDir;            // +0x28 the barrel's heading (its movable's at axis)
        float m_fTurnRate;          // +0x34 the heading's turn per second (spawn: pi / 2)
        IKSerializable* m_pUnk38;   // +0x38 a reference: its collision volume (owner = the hook)
        float m_unk3c;              // +0x3c the Load sets 0: the scale curve's time (0: no squash)
        CKShadowGround m_ShadowGround;            // +0x40 the blob shadow's ground (CKSrvShadow casters)
        CGroundContactDatasInOut m_GrdContDatasInOut;  // +0x60 the ground under the barrel
        IKSerializable* m_pUnk8c;   // +0x8c a reference: the barrel's CKSoundDictionaryID (0 rolls, 1 loops)
    };
    // A key of the barrels' scale curve (+0x14): x in [0, 1] of the curve's span (+0x10), the value.
    struct CurveKey {
        float m_fX;
        float m_fY;
    };

    // 0x00442690 CKRollingBarrelPool_Create (the constructor inlined; = 0x441fb0 / 0x4422c8 Construct, dead): the vtable,
    // both point vectors empty (capacity 1), +0x5c 1, +0x60 8.
    CKRollingBarrelPool();
    // 0x00442d38 CKRollingBarrelPool_Destructor: the two point vectors' blocks freed and cleared.
    ~CKRollingBarrelPool() override;

    // vt+0x2c 0x00442e78 CKRollingBarrelPool_Load: (level data only) the barrel count; two floats; (level) the barrels
    // and a reference; the curve's span and key count, (level) the keys; six bytes, five references, two floats, two
    // bytes, three floats; the trail points.
    int32_t Load(IKFile* file, int32_t type) override;
    // vt+0x30 0x00442320 CKRollingBarrelPool_PostLoad: none used, +0x54 = +0x48, +0x58 = 2 x +0x48, +0x5c 1, +0x60 8.
    int32_t PostLoad(int32_t type) override;
    // vt+0x10 0x00442360 CKRollingBarrelPool_Destroy: the barrel table and block freed (the pointers kept), the curve
    // keys deleted. vt+0x24 RecursiveRegistration 0x442318: returns 1 (IKSerializable's).
    void Destroy() override;

    // 0x00442000 CKHkRollingBarrel_PoolTakeNext_maybe: the next free barrel (one more used), null when all are used.
    Barrel* TakeNext();
    // 0x00442040 CKHkRollingBarrel_PoolRelease_maybe: `barrel` given back (the last used one takes its slot).
    void Release(Barrel* barrel);
    // 0x00442200 NormalizedCurve_Evaluate_maybe: the scale curve at `t` (keys scaled by the span +0x10), linear between
    // keys; 1.0 without keys or past the span, the first key's value with one key, 0.0 when no pair holds t.
    float EvaluateCurve(float t) const;
    // The trail effects (CParticlesNodeFx; port-rest R07, for CKHkRollingBarrel's callers 0x441168 / 0x4410c4):
    // 0x00442700 RollingBarrelFx_AddImpactPoint_maybe: `point` appended to +0x20's emit points (at most 64), which starts
    // emitting (shown too with `show`).
    void AddImpactPoint(const CVector3* point, int32_t show);
    // 0x00442810 RollingBarrelFx_EmitTrailPoints_maybe: the matrix's position (no trail points) or the trail points
    // through `matrix` appended to +0x24 (and +0x28 / +0x2c when set), which start emitting.
    void EmitTrailPoints(const CMatrix34* matrix);

    uint8_t m_ui8NbBarrel;          // +0x04 read raw (level data)
    uint8_t m_ui8NbUsed;            // +0x05 the barrels taken (PostLoad 0)
    uint8_t m_pad06[2];
    Barrel** m_apBarrels;           // +0x08 Mem_AllocAligned16(count x 4): the free barrels after the used ones
    Barrel* m_aBarrels;             // +0x0c Mem_AllocAligned16(count x 0x90)
    float m_fCurveSpan;             // +0x10
    CurveKey* m_aCurveKeys;         // +0x14 new[] of the key count (null without keys)
    uint32_t m_ui32NbCurveKey;      // +0x18
    IKSerializable* m_pUnk1c;       // +0x1c five references
    // +0x20 the CParticlesNodeFx effects RollingBarrelFx_* feed: [0] (+0x20) the impact effect (AddImpactPoint), [1]
    // (+0x24) the trail, [2] (+0x28) a second trail when set
    IKSerializable* m_pTrail[3];
    IKSerializable* m_pUnk2c;       // +0x2c a third trail effect when set (EmitTrailPoints)
    TVector<CVector3, 1> m_vPoints;       // +0x30 the trail's points (read last)
    TVector<CVector3, 1> m_vWorldPoints;  // +0x3c the points in the world (RollingBarrelFx_EmitTrailPoints_maybe)
    float m_unk48;                  // +0x48
    float m_unk4c;                  // +0x4c
    IKSerializable* m_pUnk50;       // +0x50 a reference (level data)
    float m_unk54;                  // +0x54 PostLoad: +0x48
    float m_unk58;                  // +0x58 PostLoad: 2 x +0x48
    int32_t m_unk5c;                // +0x5c 1
    int32_t m_unk60;                // +0x60 8
    float m_unk64;                  // +0x64
    float m_unk68;                  // +0x68
    uint8_t m_unk6c[7];             // +0x6c six bytes read one by one, then +0x72 after the floats
    uint8_t m_pad73;
    uint32_t m_unk74[2];            // +0x74 runtime
    float m_unk7c;                  // +0x7c
    float m_unk80;                  // +0x80
    float m_unk84;                  // +0x84
    uint32_t m_unk88[4];            // +0x88 runtime
    uint8_t m_unk98;                // +0x98
    uint8_t m_pad99[3];
};
static_assert(CKRollingBarrelPool::kClassKey == 0x118c, "key");
DOTD_ASSERT_SIZE(CKRollingBarrelPool::Barrel, 0x90);
DOTD_ASSERT_OFFSET(CKRollingBarrelPool::Barrel, m_vTargetDir, 0x1c);
DOTD_ASSERT_OFFSET(CKRollingBarrelPool::Barrel, m_fTurnRate, 0x34);
DOTD_ASSERT_OFFSET(CKRollingBarrelPool::Barrel, m_ShadowGround, 0x40);
DOTD_ASSERT_OFFSET(CKRollingBarrelPool::Barrel, m_GrdContDatasInOut, 0x60);
DOTD_ASSERT_OFFSET(CKRollingBarrelPool::Barrel, m_pUnk8c, 0x8c);
DOTD_ASSERT_SIZE(CKRollingBarrelPool, 0x9c);
DOTD_ASSERT_OFFSET(CKRollingBarrelPool, m_apBarrels, 0x08);
DOTD_ASSERT_OFFSET(CKRollingBarrelPool, m_fCurveSpan, 0x10);
DOTD_ASSERT_OFFSET(CKRollingBarrelPool, m_pUnk1c, 0x1c);
DOTD_ASSERT_OFFSET(CKRollingBarrelPool, m_vPoints, 0x30);
DOTD_ASSERT_OFFSET(CKRollingBarrelPool, m_vWorldPoints, 0x3c);
DOTD_ASSERT_OFFSET(CKRollingBarrelPool, m_unk48, 0x48);
DOTD_ASSERT_OFFSET(CKRollingBarrelPool, m_pUnk50, 0x50);
DOTD_ASSERT_OFFSET(CKRollingBarrelPool, m_unk5c, 0x5c);
DOTD_ASSERT_OFFSET(CKRollingBarrelPool, m_unk6c, 0x6c);
DOTD_ASSERT_OFFSET(CKRollingBarrelPool, m_unk7c, 0x7c);
DOTD_ASSERT_OFFSET(CKRollingBarrelPool, m_unk98, 0x98);
