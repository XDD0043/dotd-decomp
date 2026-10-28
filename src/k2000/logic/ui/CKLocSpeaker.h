// CKLocSpeaker.h - a dialogue speaker (key 0x68cc, vtable 0xb14340, PS3 size 0x18). Original unit:
// CKLocSpeaker.cpp (0x35470-0x35948). Not in XXL2. GAME.KP3 holds 36; CKStdText (+0x1c) refers to them.
// Only the IKGameObject part: no fields of its own.
#pragma once
#include <cstdint>

#include "Spyro2008/logic/IKGameObject.h"
#include "k2000/core/Layout.h"

class CKLocSpeaker : public IKGameObject {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x1a3)
    DOTD_DECLARE_FACTORIES(CKLocSpeaker)

    // The live constructor is inlined in CKLocSpeaker_Create 0x357b0 / CreateArray 0x35808
    // (CKLocSpeaker_Construct 0x35698 is dead): IKGameObject_ConstructBase, then the vtable.
    CKLocSpeaker() {}
    ~CKLocSpeaker() override {}  // vt+0x00 / +0x04  0x358c0 / 0x35900

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x000355f8 CKLocSpeaker_Load
    // vt+0x58 0x35670 CKLocSpeaker_InitGameData and vt+0x64 0x35648 CKLocSpeaker_ClearGameData_maybe only
    // call IKGameObject's.
};
DOTD_ASSERT_SIZE(CKLocSpeaker, 0x18);
