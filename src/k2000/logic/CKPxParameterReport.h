// CKPxParameterReport.h - a body's parameters averaged over a sliding window (key 0x568c, vtable 0xb20798, size 0x70).
// Original unit: CKPxParameterReport.cpp (0x2322b0-0x232f30). Derived straight from IKSerializable. No game file holds
// one (outputs/remake/kp3-class-usage.json). Names ours.
#pragma once
#include <cstdint>

#include "k2000/core/IKSerializable.h"
#include "k2000/core/Layout.h"
#include "k2000/math/CMatrix34.h"
#include "k2000/util/TVector.h"

class CKPxParameterReport : public IKSerializable {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x15a)
    int32_t IsKindOfClass(uint32_t key) override { return key == 0x568c || key == 0xc; }
    DOTD_DECLARE_FACTORIES(CKPxParameterReport)

    // One sample (0x58 bytes): seven vectors and their weight.
    struct SSample {
        CVector3 m_values[7];  // +0x00
        float m_fWeight;       // +0x54
    };

    // Inlined in 0x00232b20 CKPxParameterReport_Create: the sample block (null, 1, 0).
    CKPxParameterReport() {
        m_samples.m_pBlock = nullptr;
        m_samples.m_ui32NbElt = 1;
        m_samples.m_ui32NbUsedElt = 0;
    }
    // 0x00232e28 CKPxParameterReport_Destructor (_2 0x232e78, the deleting one 0x232ec8): the sample block freed.
    ~CKPxParameterReport() override;
    // vt+0x2c 0x00232c30 CKPxParameterReport_Load (level data only): a fresh one-sample block, the window size, the
    // averages zero (the vector at 0x00c50d64), the weight and the ring indices cleared.
    int32_t Load(IKFile* file, int32_t type) override;
    // vt+0x10 0x00232dd8 CKPxParameterReport_Destroy: the sample block freed, its length and block cleared.
    void Destroy() override;
    // vt+0x24 0x00232dd0 CKPxParameterReport_RecursiveRegistration: returns 1, registers nothing (the default).
    // 0x00232470 CKPxParameterReport_AddSampleToSlidingWindow_maybe (C2.8 port-last Z7; CKPxParameterReport.cpp)
    void AddSampleToSlidingWindow(const uint16_t* next);

    TVector<SSample, 1> m_samples;  // +0x04
    uint16_t m_ui16WindowSize;      // +0x10
    uint8_t m_pad12[2];
    CVector3 m_averages[7];         // +0x14
    float m_fTotalWeight;           // +0x68
    uint16_t m_ui16Newest;          // +0x6c
    uint16_t m_ui16Oldest;          // +0x6e
};
DOTD_ASSERT_SIZE(CKPxParameterReport, 0x70);
DOTD_ASSERT_OFFSET(CKPxParameterReport, m_samples, 0x04);
DOTD_ASSERT_OFFSET(CKPxParameterReport, m_ui16WindowSize, 0x10);
DOTD_ASSERT_OFFSET(CKPxParameterReport, m_averages, 0x14);
DOTD_ASSERT_OFFSET(CKPxParameterReport, m_fTotalWeight, 0x68);
DOTD_ASSERT_OFFSET(CKPxParameterReport, m_ui16Oldest, 0x6e);
