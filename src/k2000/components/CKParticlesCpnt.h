// CKParticlesCpnt.h - a particle emitter's parameters (key 0x646, vtable 0xb1df00, size 0x6c). Original
// unit: CKParticlesCpnt.cpp (0x1d9080-0x1dab88). No XXL2 class of this name.
//
// The file only holds the particle node reference; +0x0c..+0x68 are copied from the node's RenderWare
// emitter at runtime (CKParticlesCpnt_CachePropertyValuesFromEmitter_maybe 0x1d96f8).
#pragma once
#include <cstdint>

#include "k2000/components/IKComponent.h"
#include "k2000/core/Layout.h"

// A queued emission (0x20 bytes on the PS3, FreeListPool 0x00ceaa94): the position and the emission's
// parameters, then the next request. Only the link is known (Flush, QueueParticleComponentEmission).
struct ParticleEmitRequest {
    uint32_t m_unk00[7];             // +0x00 the position (+0x00) and the parameters _maybe
    ParticleEmitRequest* m_pNext;    // +0x1c
};
DOTD_ASSERT_OFFSET(ParticleEmitRequest, m_pNext, 0x1c);

class CKParticlesCpnt : public IKComponent {
public:
    DOTD_CLASS_KEY(kCategoryComponent, 0x19)
    DOTD_DECLARE_FACTORIES(CKParticlesCpnt)

    CKParticlesCpnt();  // 0x001d9610 CKParticlesCpnt_Create (the constructor is inlined there)

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x001d9658 CKParticlesCpnt_Load

    // 0x001d90e8 CKParticlesCpnt_FlushEmissionRequests: the queued emissions given back to their pool.
    void FlushEmissionRequests();

    IKSerializable* m_pParticleNode;  // +0x04 CParticlesNodeFx (Ghidra pParticleNode)
    ParticleEmitRequest* m_pEmissionQueueHead;  // +0x08 the queued emissions (Ghidra); the constructor sets 0
    uint32_t m_unk0c;                 // +0x0c..+0x68: emitter property values, set at runtime by
    uint32_t m_unk10;                 //   CachePropertyValuesFromEmitter_maybe (0x1d96f8); not set by
    float m_unk14[0x16];              //   the constructor or the Load
};
DOTD_ASSERT_SIZE(CKParticlesCpnt, 0x6c);
DOTD_ASSERT_OFFSET(CKParticlesCpnt, m_pParticleNode, 0x04);
DOTD_ASSERT_OFFSET(CKParticlesCpnt, m_pEmissionQueueHead, 0x08);
