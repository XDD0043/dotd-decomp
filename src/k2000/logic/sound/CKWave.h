// CKWave.h - one sound wave of a level (key 0x50cc, vtable 0xb19ac8, size 0x10). Original unit:
// CKWave.cpp (0x1225b0-0x122a50). XXL2: K/KModules/KSL/CKWave.h (m_fLength, m_ui16SampleRate, read in the
// same order; DotD has no m_szOriginalWavName). LVL000 holds 27; the level's CKSoundDictionary references
// them and gives each its Rwa wave.
#pragma once
#include <cstdint>

#include "k2000/core/IKSerializable.h"
#include "k2000/core/Layout.h"

struct RwaWave;

class CKWave : public IKSerializable {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x143)
    DOTD_DECLARE_FACTORIES(CKWave)

    CKWave();                                           // 0x001227b8 CKWave_Create (inlined)
    ~CKWave() override {}                               // STUB(C1.6): 0x9a6e00
    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x00122970 CKWave_Load

    float m_fLength;            // +0x04 seconds
    uint16_t m_ui16SampleRate;  // +0x08 44100 in LVL000
    uint8_t m_pad0a[2];         // never written (uninitialised heap)
    // +0x0c the wave in the level's Rwa wave dictionary: CKSoundDictionary_Load stores
    // RwaWaveDict_GetWave_maybe(dictionary, i) here for its i-th reference. Name ours.
    RwaWave* m_pRwaWave;
};
DOTD_ASSERT_SIZE(CKWave, 0x10);
DOTD_ASSERT_OFFSET(CKWave, m_fLength, 0x04);
DOTD_ASSERT_OFFSET(CKWave, m_ui16SampleRate, 0x08);
DOTD_ASSERT_OFFSET(CKWave, m_pRwaWave, 0x0c);
