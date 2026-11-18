// CKStdText.h - a standard localised text (key 0x688c, vtable 0xb14578, PS3 size 0x20). Original unit:
// CKStdText.cpp (0x36500-0x36a90). Not in XXL2. GAME.KP3 holds 1641 ("Texte standard").
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/logic/ui/CKLocText.h"

class CKLocSpeaker;

class CKStdText : public CKLocText {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x1a2)
    int32_t IsKindOfClass(uint32_t key) override {  // vt+0x08 0x994550
        return key == 0x688c || key == 0x680c || key == 0x700c || key == 0x330c || key == 0xc;
    }
    DOTD_DECLARE_FACTORIES(CKStdText)

    // The live constructor is inlined in CKStdText_Create 0x36a30 / CreateArray 0x36970 (CKStdText_Construct
    // 0x367c8 is dead): CKLocText_Construct, the vtable, then +0x1c = 0.
    CKStdText() { m_pSpeaker = nullptr; }
    ~CKStdText() override { m_pSpeaker = nullptr; }  // vt+0x00 / +0x04  0x36790 / 0x36920

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x00036600 CKStdText_Load
    void InitializeGameData() override;                 // vt+0x58 0x00036758 CKStdText_InitGameData
    // vt+0x64 0x36730 CKStdText_ClearGameData_maybe only calls the base's.

    // +0x1c the speaker, read in K_GAME_PLATEFORMS (null in every GAME.KP3 text). Name ours: the struct
    // draft types it CKLocSpeaker* (Ghidra pUnk1c).
    CKLocSpeaker* m_pSpeaker;
};
DOTD_ASSERT_SIZE(CKStdText, 0x20);
DOTD_ASSERT_OFFSET(CKStdText, m_pSpeaker, 0x1c);
