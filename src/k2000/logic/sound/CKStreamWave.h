// CKStreamWave.h - one streamed sound file (key 0x5a8c, vtable 0xb19a70, size 0x21c). Original unit:
// CKStreamWave.cpp (0x11ef08-0x11f6c8). Not in XXL2 as a class: XXL2's CKSoundStreamManager reads the
// same two values in the same order into its CKStreamParam records (m_szOriginalStreamPath, then
// m_fStreamLength). GAME.KP3 holds 143 (MUSIC\nn\STRAnnn.RWS); LVL000 refers to them by GUID.
//
// The chain is IKSerializable only: the class keeps its own GUID (+0x208), returned by GetGuid
// (0x9a6d28 returns this + 0x208) and set by SetGuid (0x9a6d48: Uuid_Copy to this + 0x208).
#pragma once
#include <cstdint>

#include "k2000/core/IKSerializable.h"
#include "k2000/core/Layout.h"

class CKStreamWave : public IKSerializable {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x16a)
    int32_t IsKindOfClass(uint32_t key) override { return key == 0x5a8c || key == 0xc; }  // vt+0x08 0x9a6d90
    DOTD_DECLARE_FACTORIES(CKStreamWave)

    CKStreamWave();                                     // 0x0011f418 CKStreamWave_Create (inlined)
    ~CKStreamWave() override {}                         // 0x009a6d78 CKStreamWave_Destructor (0x9a6db0 deleting): the vtables only
    // vt+0x24 0x0011f1b0 CKStreamWave_RecursiveRegistration: registered with the saving manager for types 0 and 1.
    void RecursiveRegistration(int32_t type) override;
    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x0011f280 CKStreamWave_Load
    const uint32_t* GetGuid() override { return m_uuid; }  // vt+0x44 0x009a6d28 CKStreamWave_GetGuid
    void SetGuid(const uint32_t* guid) override;            // vt+0x48 0x009a6d48 CKStreamWave_SetGuid
    void SetFilePath(const char* path);                     // 0x0011f050 CKStreamWave_SetFilePath_maybe
    const char* BuildFilePath();                            // 0x0011f618 CKStreamWave_BuildFilePath_maybe

    float m_fStreamLength;              // +0x004 seconds; read after the path
    // +0x008 the path under the data root (length-prefixed, read without a length limit); the bytes
    // after the terminator are not written (uninitialised heap)
    char m_szOriginalStreamPath[0x100];
    // +0x108 data root + path with forward slashes, built by CKStreamWave_BuildFilePath_maybe when the
    // stream opens. Name ours. Only byte 0 is set by the constructor.
    char m_szFilePath[0x100];
    uint32_t m_uuid[4];                 // +0x208 the GUID (the loader's SetGuid)
    uint8_t m_unk218;                   // +0x218 the constructor sets 0; 1 when played on the "Speech" type (Play)
    uint8_t m_pad219[3];
};
DOTD_ASSERT_SIZE(CKStreamWave, 0x21c);
DOTD_ASSERT_OFFSET(CKStreamWave, m_fStreamLength, 0x004);
DOTD_ASSERT_OFFSET(CKStreamWave, m_szOriginalStreamPath, 0x008);
DOTD_ASSERT_OFFSET(CKStreamWave, m_szFilePath, 0x108);
DOTD_ASSERT_OFFSET(CKStreamWave, m_uuid, 0x208);
DOTD_ASSERT_OFFSET(CKStreamWave, m_unk218, 0x218);
