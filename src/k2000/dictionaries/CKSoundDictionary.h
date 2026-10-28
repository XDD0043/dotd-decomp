// CKSoundDictionary.h - a level's sound waves (key 0xc9, vtable 0xb19830, size 0x18). Original unit:
// CKSoundDictionary.cpp (0x1122f8-0x112a60). XXL2: K/KModules/KSL/CKSoundDictionary.h (m_ui32NbSound,
// m_pRwSoundDictionary, m_pKWave, m_ui8NumSector). LVL000 holds one: 27 CKWave references and a
// 27.6 MB Rwa wave dictionary (RW chunk 0x809, 27 waves, 16-bit PCM 44.1 kHz mono).
#pragma once
#include <cstdint>

#include "k2000/core/IKSerializable.h"
#include "k2000/core/Layout.h"

struct RwaWaveDict;

class CKSoundDictionary : public IKSerializable {
public:
    DOTD_CLASS_KEY(kCategoryDictionary, 0x3)
    DOTD_DECLARE_FACTORIES(CKSoundDictionary)

    CKSoundDictionary();                                // 0x00112578 CKSoundDictionary_Create (inlined)
    ~CKSoundDictionary() override {}                    // STUB(C1.6): 0x9a6b30
    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x001126e0 CKSoundDictionary_Load

    // +0x04 the Rwa wave dictionary (RwaWaveDict_StreamRead_maybe; platform/audio/rwa.h)
    RwaWaveDict* m_pRwSoundDictionary;
    int8_t m_ui8NumSector;       // +0x08 read first; -3 makes Load return 0 without reading more
    uint8_t m_pad09[3];
    IKSerializable** m_apKWave;  // +0x0c CKWave references (Mem_AllocAligned16)
    uint32_t m_waveCapacity;     // +0x10 the constructor sets 1
    uint32_t m_ui32NbSound;      // +0x14
};
DOTD_ASSERT_SIZE(CKSoundDictionary, 0x18);
DOTD_ASSERT_OFFSET(CKSoundDictionary, m_ui8NumSector, 0x08);
DOTD_ASSERT_OFFSET(CKSoundDictionary, m_apKWave, 0x0c);
DOTD_ASSERT_OFFSET(CKSoundDictionary, m_ui32NbSound, 0x14);
