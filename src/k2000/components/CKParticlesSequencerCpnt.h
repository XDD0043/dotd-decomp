// CKParticlesSequencerCpnt.h - timed sequences of particle emitter states (key 0xc86, vtable 0xb1df58,
// size 0x28). Original unit: CKParticlesSequencerCpnt.cpp (0x1dab88-0x1dca00). XXL2:
// K/KServices/KServiceFx/Effects/Components/CKParticlesSequencerCpnt.h; the member order and the Load
// match (particles, sequences, their u16 counts); DotD's CSequence has two more per-key arrays.
#pragma once
#include <cstdint>

#include "k2000/components/IKComponent.h"
#include "k2000/core/Layout.h"
#include "k2000/math/CMatrix34.h"

class IKTime;

class CKParticlesSequencerCpnt : public IKComponent {
public:
    DOTD_CLASS_KEY(kCategoryComponent, 0x32)
    int32_t IsKindOfClass(uint32_t key) override {  // vt+0x08 0x9adb68
        return key == 0xc86 || key == 0x6 || key == 0xc;
    }
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
        // +0x0c per key (DotD only): the key's random delay (it fires at key time + delay), redrawn by PlaySequence and
        // at each loop as (1 - (draw & 0xffff) x 2^-15 (1 + 2^-16)) x m_aUnk10; the file's value is only a start value.
        float* m_aUnk0c;
        float* m_aUnk10;                   // +0x10 per key (DotD only): the delay's scale
        CParticleState* m_aParticleState;  // +0x14
        uint16_t m_ui16KeyTimeNb;          // +0x18
        uint16_t m_ui16PartStateNb;        // +0x1a
        CMatrix34* m_pCentralMatrix;       // +0x1c
    };

    CKParticlesSequencerCpnt() {}  // 0x001db1c8 CKParticlesSequencerCpnt_Create: the vtable only

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x001db948 CKParticlesSequencerCpnt_Load
    // vt+0x10 0x001db208 CKParticlesSequencerCpnt_Destroy: per sequence every particle state's matrix (RwMatrixDestroy)
    // and state array, then the state, key-time and two per-key arrays and the central matrix; then the particle and
    // sequence arrays (nothing cleared). PostLoad 0x1dac00 / RecursiveRegistration 0x1dabf8 return 1 (the defaults),
    // the destructors 0x1daf18 / 0x1daf90 / 0x1daf48 are the component base's.
    void Destroy() override;

    // ---- C2.8 port-rest R02: the sequence runtime (CKHkParticlesSequencer drives it). m_baInfos: bit 0 the sequence is
    // stopped (StopSequence), bit 1 its particles hang under an attached node (AttachSequenceFxTo), bit 2 started at a
    // place (StartSequence).
    // vt+0x50 0x001dac20 CKParticlesSequencerCpnt_vf50: empty.
    virtual void Vf50() {}
    // vt+0x54 0x001dc338 CKParticlesSequencerCpnt_vf54 (CKHkParticlesSequencer::SectorUnload passes the sector on):
    // attached particles whose parent node lies in `sector` (its GetSectorIndex, vt+0x6c, non-zero and equal) stop the
    // sequence at once (StopSequence(1)).
    virtual void Vf54(int32_t sector);
    // 0x001dafc0 CKParticlesSequencerCpnt_AttachSequenceFxTo_maybe: with a current sequence and a node, each particle
    // state's node leaves its parent (vt+0x78) for `node` (vt+0x70) and takes the state's matrix as its local one; bit 1
    // set, bit 2 cleared.
    void AttachSequenceFxTo(IKSerializable* node);
    // 0x001dbb90 CKParticlesSequencerCpnt_ReleaseSequenceFx_maybe: with a current sequence, each particle state's node
    // leaves its parent for the owner hook's sector root (an IKHook of a sector other than 0) or the dynamic scene root;
    // bit 1 cleared.
    void ReleaseSequenceFx();
    // 0x001dbd60 CKParticlesSequencerCpnt_StartSequence_maybe: with a current sequence, attached particles released;
    // bit 2 set, and each particle state's node gets the state's matrix times `place` (Mat4_TransformPostConcat).
    void StartSequence(const CMatrix34* place);
    // 0x001dbf50 CKParticlesSequencerCpnt_StopAll_maybe: attached particles released (else bit 2 cleared); every
    // particle node stops emitting and is hidden; no current, key or last sequence, the time 0, bit 2 cleared.
    void StopAll();
    // 0x001dc0d8 CKParticlesSequencerCpnt_StopSequence_maybe: the current sequence's particles stop (`now`: emitting cut
    // as StopAll does; else only the flags); the last sequence the current one, none current, bit 0 set.
    void StopSequence(int32_t now);
    // 0x001dc4c0 CKParticlesSequencerCpnt_PlaySequence_maybe: sequence `index` (when below the count) made current, the
    // previous one stopped softly unless already stopped; its particles reset under the central matrix, the key -1, the
    // time 0, bit 0 cleared, and every key's delay redrawn (one Rand_Int per key).
    void PlaySequence(uint32_t index);
    // 0x001dc7d0 CKParticlesSequencerCpnt_Update: the current running sequence's keys whose time (plus delay) has come
    // set their particles' states (2 off, 3 shown and on, 1 on); a looping sequence wraps (delays redrawn), another one
    // ends past its duration (StopSequence(1)); the time advances by the clock's delta.
    void Update(IKTime* clock);

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
    IKSerializable* m_unk24;                  // +0x24 the owner hook (CKHkParticlesSequencer_PostLoad); a pointer on x64
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
