// CKQuadFxData.h - the data of a textured quad effect (key 0x17cc, vtable 0xb1d690, size 0x28). Original unit:
// CKQuadFxData.cpp (0x1d0470-0x1d0978). Its node is CKQuadNodeFx (0x178c). Not in XXL2; names ours.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/logic/IKFxData.h"
#include "k2000/math/CMatrix34.h"

class CKQuadFxData : public IKFxData {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x5f)
    int32_t IsKindOfClass(uint32_t key) override {  // vt+0x08 0x9ad038
        return key == 0x17cc || key == 0x304c || key == 0x6 || key == 0xc;
    }
    DOTD_DECLARE_FACTORIES(CKQuadFxData)

    CKQuadFxData() {}  // CKFlashFxData.cpp's Create / CreateArray: the vtables only

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x001d04d8 CKQuadFxData_Load
    // vt+0x10 0x001d0478 CKQuadFxData_Destroy: the texture reference released (the pointer kept).
    void Destroy() override;
    // vt+0x24 0x001d04b0 RecursiveRegistration: IKFxData's (nothing).
    uint32_t GetAssociatedFxClassIdentifier() override { return 0x178c; }  // vt+0x54 0x1d0470

    void* m_pTexture;          // +0x08 IKFile_ReadTextureRef (unresolved), one reference more
    float m_afSize[2];         // +0x0c the quad's size (x, y)
    const CVector3* m_pPosition;  // +0x14 the quad's position, given by its user (Load sets 0)
    float m_fRotationSpeed;    // +0x18 degrees per second, signed by +0x25
    float m_fSizeJitter;       // +0x1c with +0x24, the size varies by up to this fraction (one rand per frame)
    uint32_t m_color;          // +0x20 the colour word, read raw (RwRGBA bytes)
    uint8_t m_bJitterSize;     // +0x24
    int8_t m_i8RotationSign;   // +0x25
    uint8_t m_pad26[2];
};
static_assert(CKQuadFxData::kClassKey == 0x17cc, "key");
DOTD_ASSERT_SIZE(CKQuadFxData, 0x28);
DOTD_ASSERT_OFFSET(CKQuadFxData, m_afSize, 0x0c);
DOTD_ASSERT_OFFSET(CKQuadFxData, m_fRotationSpeed, 0x18);
DOTD_ASSERT_OFFSET(CKQuadFxData, m_color, 0x20);
DOTD_ASSERT_OFFSET(CKQuadFxData, m_bJitterSize, 0x24);
