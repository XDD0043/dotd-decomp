// CKDefaultGameStructure.h - the engine's default game structure (key 0x354c, vtable 0xb146e8, size 0x48; XXL2:
// CKGameStructure). Original unit: CKDefaultGameStructure.cpp (0x38cf0-0x39108). Spyro creates CKS08GameStructure
// instead (GetGameStructureClassKey); this class only adds its memory-card Load. Its other slots are IKGameStructure's
// (Ghidra names several of those after this class: DestroyGame 0x41888, PostLoad 0x41aa0, vf58 / vf5C).
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/misc/IKGameStructure.h"

class CKDefaultGameStructure : public IKGameStructure {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0xd5)
    int32_t IsKindOfClass(uint32_t key) override {  // vt+0x08 0x9948e0
        return key == 0x354c || key == 0x3b4c || key == 0xc;
    }
    DOTD_DECLARE_FACTORIES(CKDefaultGameStructure)

    // 0x00039058 CKDefaultGameStructure_Create / 0x00038fa0 CreateArray inline it: IKGameStructure_Construct, the vtable.
    CKDefaultGameStructure() {}
    ~CKDefaultGameStructure() override {}  // vt+0x00 / +0x04 0x9949f0 / 0x994918

    // vt+0x24 0x00038ea8 RecursiveRegistration and vt+0x10 0x00038ed0 Destroy: IKGameStructure's (inherited).
    // vt+0x2c 0x000390b0 CKDefaultGameStructure_Load: IKGameStructure's; for the game's memory card (type 5) the
    // current spawn point is then written as a handle (the file's saving manager, vt+0x48), or without one as its raw
    // big-endian word (vt+0x20).
    int32_t Load(IKFile* file, int32_t type) override;
};
DOTD_ASSERT_SIZE(CKDefaultGameStructure, 0x48);
