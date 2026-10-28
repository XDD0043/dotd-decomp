// CKLogicalAnd.h - a cinematic scene's AND door (key 0x48, vtable 0xb1add8, size 0x34). Original unit:
// CKLogicalAnd.cpp. XXL2: no members of its own; DotD keeps the inputs already received in a vector
// (CKLogicalAnd_ActivateInput adds to it, growing by 8 with Mem_ReallocAligned16, and fires the door
// when its count reaches m_ui32IncomingNumber).
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/misc/IKLogicalDoor.h"

class CKLogicalAnd : public IKLogicalDoor {
public:
    DOTD_CLASS_KEY(kCategoryCinematic, 0x1)
    DOTD_DECLARE_FACTORIES(CKLogicalAnd)
    DOTD_DOOR_IS_KIND_OF()

    CKLogicalAnd();  // 0x0016f338 CKLogicalAnd_Create (IKCinematicElement_Construct + these fields)
    ~CKLogicalAnd() override {}

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x0016f128 CKLogicalAnd_Load
    void Start() override {}                            // vt+0x5c 0x0016ee48 CKLogicalAnd_Start (empty)
    void Activate(IKCinematicElement* source) override { ActivateInput(source); }  // vt+0x60 0x0016f528
    void Complete() override;                           // vt+0x64 0x0016ef40 CKLogicalAnd_Complete
    void Update(IKTime*) override {}                    // vt+0x68 0x0016ee50 CKLogicalAnd_Update (empty)
    void Abort() override;                              // vt+0x70 0x0016f3b0 CKLogicalAnd_Abort
    // 0x0016f528 CKLogicalAnd_ActivateInput: the input counted (once per source), the door completes when it has
    // received m_ui32IncomingNumber distinct sources.
    void ActivateInput(IKCinematicElement* source);

    IKCinematicElement** m_apReceived;  // +0x28 the inputs received (Mem_AllocAligned16 by the Load); 0
    uint32_t m_receivedCapacity;        // +0x2c 8 in the constructor; the Load sets max(incoming, 1)
    uint32_t m_receivedCount;           // +0x30 0
};
DOTD_ASSERT_SIZE(CKLogicalAnd, 0x34);
DOTD_ASSERT_OFFSET(CKLogicalAnd, m_apReceived, 0x28);
DOTD_ASSERT_OFFSET(CKLogicalAnd, m_receivedCapacity, 0x2c);
DOTD_ASSERT_OFFSET(CKLogicalAnd, m_receivedCount, 0x30);
