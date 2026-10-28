// CKSoundDictionaryID.h - a list of sound references (key 0x109, vtable 0xb19888, size 0x10). Original
// unit: CKSoundDictionaryID.cpp (0x112b18-0x113080). XXL2: K/KModules/KSL/CKSoundDictionaryID.h, the same
// members read in the same order (m_ui32NbKSound, m_apKSound, m_ui32SectorNum). LVL000 holds 179.
#pragma once
#include <cstdint>

#include "k2000/core/IKSerializable.h"
#include "k2000/core/Layout.h"

class CKSound;

class CKSoundDictionaryID : public IKSerializable {
public:
    DOTD_CLASS_KEY(kCategoryDictionary, 0x4)
    DOTD_DECLARE_FACTORIES(CKSoundDictionaryID)

    CKSoundDictionaryID();                              // 0x00112f20 CKSoundDictionaryID_Create (inlined)
    ~CKSoundDictionaryID() override {}                  // STUB(C1.6): 0x113050
    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x00112c78 CKSoundDictionaryID_Load
    CKSound* GetSound(uint32_t index);    // 0x00112bc0 CKSoundDictionaryID_GetSound (no range check)
    CKSound* GetSound2(uint32_t index);   // 0x00112bd8 CKSoundDictionaryID_GetSound_2 (the same code)

    CKSound** m_apKSound;       // +0x04 OperatorNewArray; null when there are none
    uint32_t m_ui32NbKSound;    // +0x08
    uint32_t m_ui32SectorNum;   // +0x0c KSectorIndex
};
DOTD_ASSERT_SIZE(CKSoundDictionaryID, 0x10);
DOTD_ASSERT_OFFSET(CKSoundDictionaryID, m_apKSound, 0x04);
DOTD_ASSERT_OFFSET(CKSoundDictionaryID, m_ui32NbKSound, 0x08);
DOTD_ASSERT_OFFSET(CKSoundDictionaryID, m_ui32SectorNum, 0x0c);

// The original's free functions, for the callers in other units (menus, game manager, hooks).
inline CKSound* CKSoundDictionaryID_GetSound(CKSoundDictionaryID* id, uint32_t index) { return id->GetSound(index); }
inline CKSound* CKSoundDictionaryID_GetSound_2(CKSoundDictionaryID* id, uint32_t index) { return id->GetSound2(index); }
