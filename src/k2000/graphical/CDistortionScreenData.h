// CDistortionScreenData.h - the parameters of one distortion (key 0xc8d, vtable 0xb175b0, size 0x30).
// Original unit: CDistortionScreenData.cpp (0xb1580-0xb3170). XXL2: KGL/Main/ScreenFx/CDistortionScreenFx.h;
// DotD's Load reads XXL2's fields in XXL2's order without m_ui8Resol (CDistortionScreenFx reads it).
#pragma once
#include <cstdint>

#include "k2000/core/IKSerializable.h"
#include "k2000/core/Layout.h"
#include "k2000/math/CMatrix34.h"
#include "k2000/math/CVector2.h"

class CDistortionScreenData : public IKSerializable {
public:
    DOTD_CLASS_KEY(kCategoryGraphical, 0x32)
    DOTD_DECLARE_FACTORIES(CDistortionScreenData)

    CDistortionScreenData() {}               // 0x000b1f78 CDistortionScreenData_Create: the vtable only
    ~CDistortionScreenData() override {}     // 0x009a0a70 / 0x009a0a30 CDistortionScreenData_Destructor / _DeletingDestructor: the vtables only
    // vt+0x08 0x9a0990
    int32_t IsKindOfClass(uint32_t key) override { return key == 0xc8d || key == 0xc; }
    // vt+0x10 0x000b1800 CDistortionScreenData_Destroy: the amplitude curve freed (operator delete[]), the pointer cleared.
    void Destroy() override;
    // vt+0x24 0x000b16d8 CDistortionScreenData_RecursiveRegistration: type 0 registers the data.
    void RecursiveRegistration(int32_t type) override;
    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x000b2d28 CDistortionScreenData_Load
    int32_t PostLoad(int32_t /*type*/) override { return 1; }  // vt+0x30 0x000b16c8 CDistortionScreenData_PostLoad
    // vt+0x50 0x000b3008 CDistortionScreenData_vf50 (XXL2 KUInitialize): the defaults: duration 2, damping 0.002,
    // threshold 0.02, white, a two-point curve (0, 0) (1, 0), no offset. 1.
    virtual int32_t KUInitialize();
    // vt+0x54 0x000b2080 CDistortionScreenData_vf54 (XXL2 KUDestroy): Destroy's body.
    virtual void KUDestroy();
    // vt+0x58 0x000b16d0 CDistortionScreenData_vf58 (XXL2 KUPostLoadVersionUpdate): 1.
    virtual int32_t KUPostLoadVersionUpdate(int32_t /*type*/) { return 1; }

    uint8_t m_cColor[4];               // +0x04 CColor, read without a swap
    float m_fDuration;                 // +0x08
    CVector3 m_v3OffsetPos;            // +0x0c
    float m_fMaxAmp;                   // +0x18 not written by Load: the largest |amplitude| of the curve (RenderDistortionGridWarp)
    float m_fAmpThreshold;             // +0x1c
    float m_fDampCoeff;                // +0x20
    CVector2* m_pv2Amplitude;          // +0x24 operator new[] (count-prefixed on the PS3)
    uint32_t m_ui32NbAmplitudePoints;  // +0x28
    float m_fAmp;                      // +0x2c not written by Load: the curve's amplitude at the effect's time (RenderDistortionGridWarp)
};
DOTD_ASSERT_SIZE(CDistortionScreenData, 0x30);
DOTD_ASSERT_OFFSET(CDistortionScreenData, m_cColor, 0x04);
DOTD_ASSERT_OFFSET(CDistortionScreenData, m_fDuration, 0x08);
DOTD_ASSERT_OFFSET(CDistortionScreenData, m_v3OffsetPos, 0x0c);
DOTD_ASSERT_OFFSET(CDistortionScreenData, m_fAmpThreshold, 0x1c);
DOTD_ASSERT_OFFSET(CDistortionScreenData, m_fDampCoeff, 0x20);
DOTD_ASSERT_OFFSET(CDistortionScreenData, m_pv2Amplitude, 0x24);
DOTD_ASSERT_OFFSET(CDistortionScreenData, m_ui32NbAmplitudePoints, 0x28);
