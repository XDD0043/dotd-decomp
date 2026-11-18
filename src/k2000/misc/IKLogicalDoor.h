// IKLogicalDoor.h - the logical doors of a cinematic scene (key 0x88c, abstract; XXL2:
// K/KServices/KServiceCinematic/CinematicElement/LogicalDoor/IKLogicalDoor.h). PS3 size 0x28.
// Original unit: CKCinematicDoor.cpp (0x18fc20-0x18ff28): BasicLoadCinematicElement is the Ghidra
// CKCinematicDoor_Load. There is no constructor of its own: the doors' Creates call
// IKCinematicElement_Construct and leave +0x20/+0x24 alone.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/misc/IKCinematicElement.h"

class IKFile;

class IKLogicalDoor : public IKCinematicElement {
public:
    int32_t IsKindOfClass(uint32_t key) override { return key == 0x88c || key == 0x808 || key == 0xc; }
    ~IKLogicalDoor() override {}

    // 0x0018fc90 CKCinematicDoor_Load (XXL2 IKLogicalDoor::BasicLoadCinematicElement).
    int32_t BasicLoadCinematicElement(IKFile* file, int32_t type);
    // vt+0x24 0x0018fc20 IKLogicalDoor_LevelReset (the recursive registration): registered with the saving manager
    // (vt+0x24) unless the type is 4..7. The doors' own (CKEndDoor 0x16eb80, CKLogicalAnd 0x16f208, CKLogicalOr
    // 0x16fa60, CKStartDoor 0x170080) register once more, then call this one.
    void RecursiveRegistration(int32_t type) override;

    // The door's Complete body, inlined three times (0x16e8f0 CKEndDoor_Complete, 0x16ef40 CKLogicalAnd_Complete, 0x16f840
    // CKLogicalOr_Complete): incoming count cleared, the door out of the scene's running list, flags bit 0 cleared and
    // bit 2 (completed) set; with bit 4 its outputs are activated (CKSrvCinematic_ActivateNode) and the elements to
    // interrupt stopped (vt+0x6c).
    void CompleteDoor();
    // The first activation of CKEndDoor_Start / CKLogicalAnd_ActivateInput: into the running list, flags bit 0 set,
    // bit 2 cleared (bit 1 kept); then one more incoming activation.
    void CountIncomingActivation();

    uint32_t m_ui32CurrentIncomingNumber;  // +0x20 the Load clears it
    uint32_t m_ui32IncomingNumber;         // +0x24
};
DOTD_ASSERT_SIZE(IKLogicalDoor, 0x28);
DOTD_ASSERT_OFFSET(IKLogicalDoor, m_ui32CurrentIncomingNumber, 0x20);
DOTD_ASSERT_OFFSET(IKLogicalDoor, m_ui32IncomingNumber, 0x24);
