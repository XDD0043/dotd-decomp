// CLightComponent.h - one light of a CLightSet (key 0xa4c, vtable 0xb17a98, size 0x2c). Original unit:
// CLightComponent.cpp. XXL2: K/KModules/KGL/MAterial/CLightComponent.h, the same members in the same
// order and the same Load (XXL2's CColorLine::Load is CurveKeys_Load).
#pragma once
#include <cstdint>

#include "k2000/core/IKSerializable.h"
#include "k2000/core/Layout.h"
#include "k2000/math/CMatrix34.h"
#include "k2000/math/CurveKeys.h"

class IKTime;

class CLightComponent : public IKSerializable {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x29)
    DOTD_DECLARE_FACTORIES(CLightComponent)

    // XXL2 CLightComponent::CBlinkData (0x14 bytes on the PS3): allocated by Load when m_baProperties & 8.
    struct CBlinkData {
        float m_fBlinkLength;              // +0x00 1.0, then read
        float m_fCurTime;                  // +0x04 0
        TVector<CurveKey, 20> m_ColorLine;  // +0x08 XXL2 CColorLine; 20 keys reserved
    };

    CLightComponent();                 // 0x000ba8b8 CLightComponent_Create (inlined)
    ~CLightComponent() override {}     // 0x009a1148 / 0x009a1108 CLightComponent_Destructor / _DeletingDestructor: the vtables only
    // vt+0x10 0x000bb278 CLightComponent_Destroy: the blink data's key block freed, the blink data deleted.
    void Destroy() override;
    // vt+0x08 0x9a10e8
    int32_t IsKindOfClass(uint32_t key) override { return key == 0xa4c || key == 0xc; }
    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x000bafe8 CLightComponent_Load
    // vt+0x24 0x000ba5e8 CLightComponent_RecursiveRegistration: type 0 registers the light with the saving manager.
    // vt+0x30 PostLoad 0xbaad0 returns 1 (IKSerializable's).
    void RecursiveRegistration(int32_t type) override;

    // 0x000bacd8 LightData_UpdateColorAnimation_maybe: a blinking light (property bit 3) advances its blink time by the
    // frame's delta (back to 0 when it passes the blink length) and takes the colour of its colour line at that
    // fraction of the length.
    void UpdateColorAnimation(const IKTime* frameClock);

    uint32_t m_unk04;              // +0x04 not written by the constructor or Load
    uint32_t m_baProperties;       // +0x08 (XXL2 CBitArray); bit 3: blinking
    uint8_t m_cLightColor[4];      // +0x0c CColor, read without a swap (the file's bytes); the constructor
                                   //       copies the white constant (0x00c50dfc)
    float m_fRadius;               // +0x10
    float m_fConeAngle;            // +0x14
    void* m_pLightFrame;           // +0x18 RwFrame*; the constructor sets 0
    CBlinkData* m_pBlinkColorData; // +0x1c
    CVector3 m_v3Dir;              // +0x20 the constructor copies the vector at 0x00c50d4c (0, 0, 1)
};
DOTD_ASSERT_SIZE(CLightComponent::CBlinkData, 0x14);
DOTD_ASSERT_SIZE(CLightComponent, 0x2c);
DOTD_ASSERT_OFFSET(CLightComponent, m_baProperties, 0x08);
DOTD_ASSERT_OFFSET(CLightComponent, m_cLightColor, 0x0c);
DOTD_ASSERT_OFFSET(CLightComponent, m_fRadius, 0x10);
DOTD_ASSERT_OFFSET(CLightComponent, m_fConeAngle, 0x14);
DOTD_ASSERT_OFFSET(CLightComponent, m_pBlinkColorData, 0x1c);
DOTD_ASSERT_OFFSET(CLightComponent, m_v3Dir, 0x20);
