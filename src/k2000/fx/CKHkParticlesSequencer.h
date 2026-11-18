// CKHkParticlesSequencer.h - the hook driving a particles sequencer component (key 0x3ec2, vtable
// 0xb2eb10, size 0x38; library-TOC code). Original unit: k2000/fx/CKHkParticlesSequencer.cpp.
// XXL2: K/KParticlesSequencer/CKHkParticlesSequencer.h; same members in the same order.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/hooks/IKHook.h"
#include "k2000/services/CTriggerStarter.h"

class CKHkParticlesSequencer : public IKHook {
public:
    DOTD_CLASS_KEY(kCategoryHook, 0xfb)
    DOTD_DECLARE_FACTORIES(CKHkParticlesSequencer)

    // 0x005a9200 CKHkParticlesSequencer_Create (inlined constructor, = 0x005a8960 _Construct): only the
    // IKLife/IKHook defaults.
    CKHkParticlesSequencer() {}
    ~CKHkParticlesSequencer() override {}

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x005a8c18 CKHkParticlesSequencer_Load
    // C2.8 port-all P16. vt+0x30 0x005a8bb0 CKHkParticlesSequencer_PostLoad: IKLife's, the component's owner (+0x24) this
    // hook, the trigger starter's PostLoad; 1.
    int32_t PostLoad(int32_t type) override;
    // vt+0x38 0x005a9110 CKHkParticlesSequencer_vf38 (SetDefaultState): the current sequence back to the default.
    void SetDefaultState(int32_t /*flag*/) override { m_i32CurSequence = m_i32DefaultStartSequence; }
    // vt+0x3c 0x005a9120 CKHkParticlesSequencer_vf3C (SetGameState): info 100 sets the current sequence (state - 1);
    // answers whether it was 100.
    int32_t SetGameState(const SApplyGameState* state) override;
    // vt+0x40 0x005a9410 CKHkParticlesSequencer_ResolveTriggerProperty (GetInfo): 0x14 IsStopped, 0x15 IsAtStep,
    // 0x16 HasStoppedAtStep (bytes).
    int32_t GetInfo(IKInfo* info, int32_t request) override;
    // 0x005a93c0 _IsStopped_maybe: the component's current sequence (+0x14) is negative. 0x005a93e0 _IsAtStep_maybe: it
    // is `step` - 1. 0x005a94f8 _HasStoppedAtStep_maybe: stopped, and the last sequence (+0x1c) is `step` - 1.
    uint32_t IsStopped() const;
    uint32_t IsAtStep(uint32_t step) const;
    uint32_t HasStoppedAtStep(uint32_t step) const;

    // ---- C2.8 port-rest R02 (the component's sequence runtime is ported).
    // vt+0x1c 0x005a8f40 CKHkParticlesSequencer_HandleMessage: 0x900 (data +2: a u16 step) plays sequence step - 1 (the
    // current one set first, nothing played below 0) and marks it running; 0x901 (data: a pointer to a placement, its
    // position at +4 and quaternion at +0x10) starts the sequence there; 0x902 stops all (no current sequence); 0x903
    // (data: a node pointer) attaches the particles to the node. 0 when handled (0x901 without a placement: 1).
    int32_t MessageProc(uint16_t message, void* data) override;
    // vt+0x54 0x005a8b28 CKHkParticlesSequencer_ReinitRuntime (Restart): in a loaded sector, the current sequence played
    // again (or everything stopped without a valid one).
    void Restart() override;
    // vt+0x68 0x005a8ed8 CKHkParticlesSequencer_OnLevelExit_maybe (Stop): in a loaded sector everything stopped; the
    // running bit cleared and the current sequence back to the default.
    void Stop() override;
    // vt+0x7c 0x005a8e28 CKHkParticlesSequencer_Update: the component's Update; a running sequence that has stopped
    // fires the sequence-ended starter and clears the running bit.
    void Update(IKTime* frameClock) override;
    // vt+0x8c 0x005a8a38 CKHkParticlesSequencer_OnSectorDeactivate (SectorUnload): IKLife's, then the component's vt+0x54.
    void SectorUnload(int32_t sector) override;
    // vt+0xa0 0x005a9148 CKHkParticlesSequencer_OnActivate (SectorNowValid): the current sequence played (or everything
    // stopped without a valid one). vt+0xa4 0x005a91c0 CKHkParticlesSequencer_OnDeactivate: everything stopped, no
    // current sequence.
    void VfA0() override;
    void VfA4() override;

    IKSerializable* m_pSequencerPartCpnt;    // +0x20 XXL2 CKParticlesSequencerCpnt* (reference)
    int32_t m_i32DefaultStartSequence;       // +0x24 XXL2 (file: -1 in the LVL060 samples)
    int32_t m_i32CurSequence;                // +0x28 XXL2; runtime
    uint8_t m_baInfos;                       // +0x2c XXL2 CBitArray8 (byte accesses): bit 0 a sequence runs; runtime
    uint8_t m_pad2d[3];
    CTriggerStarter m_tsSequenceEnded;       // +0x30 XXL2
};
DOTD_ASSERT_SIZE(CKHkParticlesSequencer, 0x38);
DOTD_ASSERT_OFFSET(CKHkParticlesSequencer, m_pSequencerPartCpnt, 0x20);
DOTD_ASSERT_OFFSET(CKHkParticlesSequencer, m_i32DefaultStartSequence, 0x24);
DOTD_ASSERT_OFFSET(CKHkParticlesSequencer, m_tsSequenceEnded, 0x30);
