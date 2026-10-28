// CKSrvCounter.h - the counter service (key 0x441, vtable 0xb1ef08, size 0x24). Original unit:
// CKSrvCounter.cpp (0x201390-0x202248). XXL2: K/KServices/KServiceCounter/CKSrvCounter.h, the same two
// vectors read in the same order (integer counters first).
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/services/IKService.h"
#include "k2000/util/TVector.h"

class CKSrvCounter : public IKService {
public:
    DOTD_CLASS_KEY(kCategoryService, 0x11)
    DOTD_DECLARE_FACTORIES(CKSrvCounter)

    CKSrvCounter();  // 0x00201558 CKSrvCounter_Construct
    ~CKSrvCounter() override {}

    void Destroy() override;  // vt+0x10 0x002014c0 CKSrvCounter_Destroy
    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x00201ad8 CKSrvCounter_Load
    void Start() override {}                            // vt+0x50 0x201a20  STUB(C1.6)
    void Stop() override {}                             // vt+0x68 0x2013e8  STUB(C1.6)
    void Pause() override {}                            // vt+0x70 0x2013f0  STUB(C1.6)
    void Resume() override {}                           // vt+0x78 0x2013f8  STUB(C1.6)
    void Update(IKTime*) override {}                    // vt+0x7c 0x201838 UpdateCKSrvCounter  STUB(C1.6)
    int32_t InitializeService() override { return 1; }  // vt+0x94 0x201400
    void DestroyService() override {}                   // vt+0x98 0x201408 (empty)

    // XXL2 order and names (the Ghidra struct calls +0x0c the time counters; XXL2's Load reads the
    // integer counters first, like the PS3's first vector).
    TVector<IKSerializable*, 1> m_vpIntegerCounterList;  // +0x0c CKIntegerCounter*
    TVector<IKSerializable*, 1> m_vpTimeCounterList;     // +0x18 CKTimeCounter*
};
DOTD_ASSERT_SIZE(CKSrvCounter, 0x24);
DOTD_ASSERT_OFFSET(CKSrvCounter, m_ui32Priority, 0x08);
DOTD_ASSERT_OFFSET(CKSrvCounter, m_vpIntegerCounterList, 0x0c);
DOTD_ASSERT_OFFSET(CKSrvCounter, m_vpTimeCounterList, 0x18);
