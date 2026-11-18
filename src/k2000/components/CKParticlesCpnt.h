// CKParticlesCpnt.h - a particle emitter's parameters (key 0x646, vtable 0xb1df00, size 0x6c). Original
// unit: CKParticlesCpnt.cpp (0x1d9080-0x1dab88). No XXL2 class of this name.
//
// The file only holds the particle node reference; +0x0c..+0x68 are copied from the node's RenderWare
// emitter at runtime (CKParticlesCpnt_CachePropertyValuesFromEmitter_maybe 0x1d96f8).
#pragma once
#include <cstdint>

#include "k2000/components/IKComponent.h"
#include "k2000/core/Layout.h"

#include "k2000/math/CMatrix34.h"

class CParticlesNodeFx;

// An emission's overrides of the emitter's standard values (0x64 bytes; CKExplosionFxData's type-0 part holds one at
// +0x0c): each value replaces the emitter's when its bit of +0x60 is set (ApplyParticleComponentOverrides 0x1d9b80).
// Names after RpPrtStdEmitterStandard / RpPrtStdEmitterPrtSize, the fields they are copied into.
struct ParticleEmitOverrides {
    uint32_t m_emtPrtEmit;      // +0x00 bit 0x001 (also the node's particles per point, +0x51)
    uint32_t m_emtPrtEmitBias;  // +0x04 bit 0x002
    CVector3 m_emtSize;         // +0x08 bit 0x004
    CVector3 m_force;           // +0x14 bit 0x100
    CVector3 m_prtInitDir;      // +0x20 bit 0x008
    CVector3 m_prtInitDirBias;  // +0x2c bit 0x010
    float m_prtInitVel;         // +0x38 bit 0x020
    float m_prtInitVelBias;     // +0x3c bit 0x040
    // +0x40 bit 0x080: the size property's eight floats in its order (start, start bias, end, end bias; x and y);
    // without the property only the start size, into the standard size and the PTank's constant size.
    float m_prtSize[8];
    uint32_t m_overrideMask;    // +0x60
};
DOTD_ASSERT_SIZE(ParticleEmitOverrides, 0x64);
DOTD_ASSERT_OFFSET(ParticleEmitOverrides, m_force, 0x14);
DOTD_ASSERT_OFFSET(ParticleEmitOverrides, m_prtInitVel, 0x38);
DOTD_ASSERT_OFFSET(ParticleEmitOverrides, m_prtSize, 0x40);
DOTD_ASSERT_OFFSET(ParticleEmitOverrides, m_overrideMask, 0x60);

// A queued emission (0x20 bytes on the PS3, from the FreeListPool 0x00ceaa94, whose free list links through +0x00;
// here new / delete): the position, the direction, the overrides, then the next request.
struct ParticleEmitRequest {
    CVector3 m_position;                    // +0x00
    CVector3 m_direction;                   // +0x0c the null vector without a direction
    const ParticleEmitOverrides* m_pOverrides;  // +0x18 may be null
    ParticleEmitRequest* m_pNext;           // +0x1c
};
DOTD_ASSERT_OFFSET(ParticleEmitRequest, m_direction, 0x0c);
DOTD_ASSERT_OFFSET(ParticleEmitRequest, m_pOverrides, 0x18);
DOTD_ASSERT_OFFSET(ParticleEmitRequest, m_pNext, 0x1c);

class CKParticlesCpnt : public IKComponent {
public:
    DOTD_CLASS_KEY(kCategoryComponent, 0x19)
    int32_t IsKindOfClass(uint32_t key) override {  // vt+0x08 0x9adb30
        return key == 0x646 || key == 0x6 || key == 0xc;
    }
    DOTD_DECLARE_FACTORIES(CKParticlesCpnt)

    CKParticlesCpnt();  // 0x001d9610 CKParticlesCpnt_Create (the constructor is inlined there)
    // 0x001d94f8 CKParticlesCpnt_Destructor (0x1d93e0 Destructor_2 the same, 0x1d9470 DeletingDestructor + delete): the
    // queued emissions given back to their pool (FlushEmissionRequests' body), then the component base.
    ~CKParticlesCpnt() override;
    // vt+0x10 0x1d96f0 Destroy (empty) and vt+0x24 0x1d96e8 RecursiveRegistration (returns 1): the defaults.

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x001d9658 CKParticlesCpnt_Load

    // 0x001d90e8 CKParticlesCpnt_FlushEmissionRequests: the queued emissions given back to their pool.
    void FlushEmissionRequests();
    // 0x001d96f8 CKParticlesCpnt_CachePropertyValuesFromEmitter_maybe (CKSrvFx_Start, through the thunk 0x1d9b78): the
    // node's RenderWare emitter's standard values (property 1) and particle sizes (property 5, else the standard size)
    // kept as the defaults the emissions are given. Nothing without a node.
    void CachePropertyValuesFromEmitter();

    // 0x001da840 QueueParticleComponentEmission (TocBridge 0x98fbe0; CKExplosionNodeFx's type-0 sub-effect, the water
    // splash / wave nodes): the emitter's cached defaults restored (ApplyParticleComponentParameters); a node with a
    // point list takes the position (and direction) as its next point at once (at most 64), emission started if it was
    // not; any other node gets a request queued at the head (a stack), handled by ProcessEmissionQueue. Nothing
    // without a node.
    void QueueEmission(const CVector3* position, const CVector3* direction, const ParticleEmitOverrides* overrides);
    // 0x001da1a8 ProcessParticleComponentEmissionQueue (UpdateCKSrvFx, unless paused): the node's visibility (flag 4)
    // and, for the head request (one per frame), its overrides, the node placed and emitting, the request freed.
    void ProcessEmissionQueue();
    // 0x001d91b0 TriggerParticleNodeEmission: the node's frame at `position`, turned along `direction` (unless null or
    // the null vector) with the Y axis as up, else the X axis; then emitting (flags 0x200 | 0x400, 0x80000 off),
    // the speed adjustment 0, the emitter active and emitting (0xa).
    void TriggerNodeEmission(CParticlesNodeFx* node, const CVector3* position, const CVector3* direction);
    // 0x001d9b80 ApplyParticleComponentOverrides: the overrides whose mask bit is set into the emitter.
    void ApplyOverrides(const ParticleEmitOverrides* overrides);
    // 0x001da328 ApplyParticleComponentParameters (0x1da838 is a branch to it): the cached values (+0x0c..+0x68)
    // back into the emitter.
    void ApplyParameters();

    IKSerializable* m_pParticleNode;  // +0x04 CParticlesNodeFx (Ghidra pParticleNode)
    ParticleEmitRequest* m_pEmissionQueueHead;  // +0x08 the queued emissions (Ghidra); the constructor sets 0
    // +0x0c..+0x68: the emitter's values, set by CachePropertyValuesFromEmitter (CKSrvFx_Start); not set by the
    // constructor or the Load. Names after RpPrtStdEmitterStandard / RpPrtStdEmitterPrtSize.
    uint32_t m_unk0c;                 // +0x0c emtPrtEmit (also the node's particles per point, +0x51)
    uint32_t m_unk10;                 // +0x10 emtPrtEmitBias
    float m_unk14[3];                 // +0x14 emtSize
    float m_unk20[3];                 // +0x20 force
    float m_unk2c[3];                 // +0x2c prtInitDir
    float m_unk38[3];                 // +0x38 prtInitDirBias
    float m_unk44;                    // +0x44 prtInitVel
    float m_unk48;                    // +0x48 prtInitVelBias
    // +0x4c the sizes: start (x, y), end (x, y), start bias, end bias (property 5, absent ones 1.0); without the
    // property only the standard size (+0x4c, +0x50) is set. (ParticleEmitOverrides keeps the property's order.)
    float m_unk4c[8];
};
DOTD_ASSERT_SIZE(CKParticlesCpnt, 0x6c);
DOTD_ASSERT_OFFSET(CKParticlesCpnt, m_pParticleNode, 0x04);
DOTD_ASSERT_OFFSET(CKParticlesCpnt, m_pEmissionQueueHead, 0x08);
DOTD_ASSERT_OFFSET(CKParticlesCpnt, m_unk20, 0x20);
DOTD_ASSERT_OFFSET(CKParticlesCpnt, m_unk44, 0x44);
DOTD_ASSERT_OFFSET(CKParticlesCpnt, m_unk4c, 0x4c);
