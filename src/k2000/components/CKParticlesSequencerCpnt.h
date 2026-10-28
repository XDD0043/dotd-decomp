// CKParticlesSequencerCpnt.h - timed sequences of particle emitter states (key 0xc86, vtable 0xb1df58,
// size 0x28). Original unit: CKParticlesSequencerCpnt.cpp (0x1dab88-0x1dca00). XXL2:
// K/KServices/KServiceFx/Effects/Components/CKParticlesSequencerCpnt.h; the member order and the Load
// match (particles, sequences, their u16 counts); DotD's CSequence has two more per-key arrays.
#pragma once
#include <cstdint>

#include "k2000/components/IKComponent.h"
#include "k2000/core/Layout.h"
#include "k2000/math/CMatrix34.h"

class CKParticlesSequencerCpnt : public IKComponent {
public:
    DOTD_CLASS_KEY(kCategoryComponent, 0x32)
    DOTD_DECLARE_FACTORIES(CKParticlesSequencerCpnt)

    // XXL2 CParticleState (m_pParticle, m_aePartState, m_pMatrixPart): 0xc bytes.
    struct CParticleState {
        IKSerializable* m_pParticle;  // +0x00 XXL2 CParticlesNodeFx*
        uint32_t* m_aePartState;      // +0x04 one word per key time (byte-swapped)
        CMatrix34* m_pMatrixPart;     // +0x08 RwMatrixCreate + CMatrix34_LoadMatrix
    };
    // XXL2 CSequence: 0x20 bytes; CKParticlesSequencerCpnt_LoadSequence_maybe (0x1db508) reads it.
    struct CSequence {
        int32_t Load(IKFile* file, int32_t type);  // 0x001db508 CKParticlesSequencerCpnt_LoadSequence_maybe
        uint8_t m_bLoop;                   // +0x00
        uint8_t m_pad01[3];
        float m_fSeqDuration;              // +0x04
        float* m_afKeyTime;                // +0x08 per key (XXL2's one per-key array; _maybe the key times)
        uint32_t* m_aUnk0c;                // +0x0c per key, a second word (DotD only)
        uint32_t* m_aUnk10;                // +0x10 per key, a third word (DotD only)
        CParticleState* m_aParticleState;  // +0x14
        uint16_t m_ui16KeyTimeNb;          // +0x18
        uint16_t m_ui16PartStateNb;        // +0x1a
        CMatrix34* m_pCentralMatrix;       // +0x1c
    };

    CKParticlesSequencerCpnt() {}  // 0x001db1c8 CKParticlesSequencerCpnt_Create: the vtable only

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x001db948 CKParticlesSequencerCpnt_Load

    IKSerializable** m_apSequencerParticles;  // +0x04 OperatorNewArray (XXL2 CParticlesNodeFx**)
    CSequence* m_aSequences;                  // +0x08 OperatorNewArray (no cookie)
    uint16_t m_ui16PartNb;                    // +0x0c
    uint16_t m_ui16SeqNb;                     // +0x0e
    float m_fCurSeqTime;                      // +0x10 _maybe (XXL2 order); not set by the constructor or the Load
    int32_t m_i32CurSeq;                      // +0x14 the Load sets -1 (every type)
    int32_t m_i32CurKeyTime;                  // +0x18 _maybe (XXL2 order)
    int32_t m_i32LastSeq;                     // +0x1c _maybe (XXL2 order)
    uint8_t m_baInfos;                        // +0x20 XXL2 CBitArray8; the Load sets 0 (every type)
    uint8_t m_pad21[3];
    uint32_t m_unk24;                         // +0x24
};
DOTD_ASSERT_SIZE(CKParticlesSequencerCpnt::CParticleState, 0xc);
DOTD_ASSERT_SIZE(CKParticlesSequencerCpnt::CSequence, 0x20);
DOTD_ASSERT_OFFSET(CKParticlesSequencerCpnt::CSequence, m_ui16KeyTimeNb, 0x18);
DOTD_ASSERT_OFFSET(CKParticlesSequencerCpnt::CSequence, m_pCentralMatrix, 0x1c);
DOTD_ASSERT_SIZE(CKParticlesSequencerCpnt, 0x28);
DOTD_ASSERT_OFFSET(CKParticlesSequencerCpnt, m_apSequencerParticles, 0x04);
DOTD_ASSERT_OFFSET(CKParticlesSequencerCpnt, m_ui16PartNb, 0x0c);
DOTD_ASSERT_OFFSET(CKParticlesSequencerCpnt, m_i32CurSeq, 0x14);
DOTD_ASSERT_OFFSET(CKParticlesSequencerCpnt, m_baInfos, 0x20);
