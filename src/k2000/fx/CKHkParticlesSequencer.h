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

    IKSerializable* m_pSequencerPartCpnt;    // +0x20 XXL2 CKParticlesSequencerCpnt* (reference)
    int32_t m_i32DefaultStartSequence;       // +0x24 XXL2 (file: -1 in the LVL060 samples)
    int32_t m_i32CurSequence;                // +0x28 XXL2; runtime
    uint32_t m_baInfos;                      // +0x2c XXL2 CBitArray8 m_baInfos_maybe; runtime
    CTriggerStarter m_tsSequenceEnded;       // +0x30 XXL2
};
DOTD_ASSERT_SIZE(CKHkParticlesSequencer, 0x38);
DOTD_ASSERT_OFFSET(CKHkParticlesSequencer, m_pSequencerPartCpnt, 0x20);
DOTD_ASSERT_OFFSET(CKHkParticlesSequencer, m_i32DefaultStartSequence, 0x24);
DOTD_ASSERT_OFFSET(CKHkParticlesSequencer, m_tsSequenceEnded, 0x30);
