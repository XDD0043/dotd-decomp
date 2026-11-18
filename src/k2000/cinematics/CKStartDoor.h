// CKStartDoor.h - a cinematic scene's start door (key 0x448, vtable 0xb1aee8, size 0x28). Original unit:
// CKStartDoor.cpp. XXL2: no members of its own.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/misc/IKLogicalDoor.h"

class CKStartDoor : public IKLogicalDoor {
public:
    DOTD_CLASS_KEY(kCategoryCinematic, 0x11)
    DOTD_DECLARE_FACTORIES(CKStartDoor)
    DOTD_DOOR_IS_KIND_OF()

    // 0x001701b8 CKStartDoor_Create: IKCinematicElement_Construct, then the vtable.
    CKStartDoor() {}
    ~CKStartDoor() override {}

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x00170030 CKStartDoor_Load
    // vt+0x24 0x00170080 CKStartDoor_RecursiveRegistration: registered with the saving manager (vt+0x24) unless the type is 4..7,
    // then IKLogicalDoor_LevelReset 0x18fc20 (which registers it once more).
    void RecursiveRegistration(int32_t type) override;
    // The scene's first element: its outputs are prepared (vt+0x58) and activated (vt+0x60) in turn, then it completes.
    void Start() override;                              // vt+0x5c 0x0016ff10 CKStartDoor_Start
    void Complete() override {}                         // vt+0x64 0x0016fe78 CKStartDoor_Complete (empty)
    void Update(IKTime*) override {}                    // vt+0x68 0x0016fe80 CKStartDoor_Update (empty)
    void Abort() override {}                            // vt+0x70 0x009a9188 CKStartDoor_Abort (empty)
};
DOTD_ASSERT_SIZE(CKStartDoor, 0x28);
