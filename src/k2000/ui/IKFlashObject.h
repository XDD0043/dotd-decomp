// IKFlashObject.h - base of the objects a Flash (Rt2d Maestro) interface owns (key 0x74d, vtable 0xb16398,
// size 0x24; XXL2: K/KModules/KGL/2d/Maestro/FlashObject/IKFlashObject.h): IKFlashMessage (0x80d,
// CKFlashMessageIn/Out), CKFlashText, CKFlashAnimation. Original unit: IKFlashObject.cpp (0x77828-0x77e48).
//
// XXL2 has m_szLabelName (Char[1024]), m_ui32LabelId, m_pFlashUI, read by its Load in that order; DotD
// allocates the name, and adds a byte (+0x10, read by Load) and four floats (+0x14..+0x23).
// Slots after IKSerializable's: XXL2's 20 (GetRt2dObject), then six DotD slots (+0x54..+0x68), whose
// names are unknown. The constructor is empty (the derived constructors only store vtables).
#pragma once
#include <cstdint>

#include "k2000/core/IKSerializable.h"
#include "k2000/core/Layout.h"
#include "k2000/math/CVector2.h"
#include "k2000/util/TVector.h"

struct Rt2dObject;

class IKFlashObject : public IKSerializable {
public:
    ~IKFlashObject() override {}                                            // vt+0x00 / +0x04  0x999460 / 0x999478
    int32_t IsKindOfClass(uint32_t key) override { return key == 0x74d || key == 0xc; }  // vt+0x08 0x999440
    void Destroy() override;                                                // vt+0x10 0x77b88
    int32_t GetClassType() override { return kCategoryGraphical; }          // vt+0x14 0x999430 (unregistered key 0x74d)
    int32_t GetClassID() override { return 0x1d; }                          // vt+0x18 0x999438
    void RecursiveRegistration(int32_t /*type*/) override {}                // vt+0x24 0x77b78 (returns 1)
    int32_t Save(IKFile* /*file*/) override { return 1; }                   // vt+0x28 0x77950
    int32_t Load(IKFile* file, int32_t type) override;                      // vt+0x2c 0x77958 IKFlashObject_Load
    int32_t PostLoad(int32_t /*type*/) override { return 1; }               // vt+0x30 0x77b80
    // vt+0x50 0x9991b8 (empty; Ghidra: IKFlashMessage_vf50). XXL2: GetRt2dObject(VectorOfRt2dObject&):
    // the overrides append their Rt2d objects.
    virtual void GetRt2dObject(TVector<Rt2dObject*, 1>* /*objects*/) {}
    // vt+0x54 0x77838 IKFlashObject_SetColorWhite_maybe (DotD): the label id becomes 0xffffff (the value
    // the CKFlashText files hold); the overrides also clear what they gathered.
    virtual void Vf54() { m_ui32LabelId = 0xffffff; }
    virtual void Vf58() { m_unk14[3] = -0x1p+0f; }                          // vt+0x58 0x77828 (DotD)
    virtual void Vf5C() { m_unk14[3] = -0x1p+0f; }                          // vt+0x5c 0x77940 (DotD)
    // vt+0x60 0x9991c0 (DotD; Ghidra: IKFlashMessage_vf60) returns 0. The overrides (CKFlashText 0x765f8,
    // CKFlashAnimation) give the screen anchor of their first visible object: the position (normalised),
    // the size in movie pixels and the colour (RGBA bytes); each out-pointer may be null. 1 when found.
    // Called by FlashWidgetBinding_UpdateAnchor_maybe 0x72198 (the hot spot's +0x2c, +0x34, +0x3c).
    virtual uint8_t GetScreenAnchor(CVector2* /*position*/, CVector2* /*size*/, uint8_t* /*rgba*/) { return 0; }
    // vt+0x64 0x9991c8 (DotD; empty). CKFlashText's (0x761a8) registers its objects in the interface's
    // object map (no parent).
    virtual void RegisterObjects() {}
    // vt+0x68 0x9991d0 (DotD; empty). The overrides apply m_unk14 as the Rt2d colour multiplier of their
    // visible objects when its alpha is not -1, then set it to -1.
    virtual void ApplyColorMultiplier() {}

    // 0x00077bd0 CKFlashElement_GetObjectScreenPos_maybe (XXL2 GetNormalizedPosition(Rt2dObject*,
    // CVector2&)): the object's LTM position, x divided by the reference aspect (4:3).
    void GetNormalizedPosition(Rt2dObject* object, CVector2* position);
    // 0x00077d68 CKFlashElement_GetScreenPosNormalized_maybe (XXL2 GetNormalizedPosition(CVector2&)): the
    // same for the first object GetRt2dObject gives.
    void GetNormalizedPosition(CVector2* position);
    // 0x00077c48 CKFlashElement_GetScreenPosPixels_maybe (XXL2 GetPosition): in raster pixels, y down.
    void GetPosition(CVector2* position);
    // 0x000778a8 FlashUI_NormalizedToScreenPixels_maybe (XXL2 GetRealPosition): a normalised position in
    // raster pixels, y down.
    void GetRealPosition(const CVector2* normalized, CVector2* position);

    char* m_szLabelName;           // +0x04 Mem_AllocAligned16(length + 1); null for a negative length
    uint32_t m_ui32LabelId;        // +0x08
    IKSerializable* m_pFlashUI;    // +0x0c CKFlashUI (a reference)
    uint8_t m_unk10;               // +0x10 (DotD; +0x11..+0x13: padding the original never writes)
    // +0x14 (DotD) an RwRGBAReal colour multiplier: CKFlashText/CKFlashAnimation pass &m_unk14 to
    // Rt2dObjectSetColorMultiplier; alpha -1 = nothing to apply. Neither the constructor nor Load sets it.
    float m_unk14[4];
};
DOTD_ASSERT_SIZE(IKFlashObject, 0x24);
DOTD_ASSERT_OFFSET(IKFlashObject, m_szLabelName, 0x04);
DOTD_ASSERT_OFFSET(IKFlashObject, m_ui32LabelId, 0x08);
DOTD_ASSERT_OFFSET(IKFlashObject, m_pFlashUI, 0x0c);
DOTD_ASSERT_OFFSET(IKFlashObject, m_unk10, 0x10);
DOTD_ASSERT_OFFSET(IKFlashObject, m_unk14, 0x14);
