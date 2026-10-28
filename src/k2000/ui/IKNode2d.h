// IKNode2d.h - base of the 2D scene nodes (key 0x24d, vtable 0xb14418, size 0x28; XXL2:
// K/KModules/KGL/2d/IKNode2d.h, the same members in the same order): CContainer2d, CBillboard2d,
// CText2d, CBillboardList2d, IKButton2d (0x2cd). Original unit: IKNode2d.cpp (0x69848-0x6a1f0).
//
// Slots after IKSerializable's: XXL2's 20..32 (SetOwner .. Render), plus one DotD inserted at +0x7c, so
// XXL2's Scale and Render sit at +0x80/+0x84. Evidence: co-override agreement over CContainer2d,
// CBillboard2d, CText2d, CBillboardList2d and IKButton2d (FreeMemory +0x54 overridden by
// CBillboardList2d only, RecursiveNodeReach +0x58 by CBillboard2d/CText2d, Enable/Disable by CText2d,
// Disable by IKButton2d, GetBoundingBox/Scale/Render by all; +0x7c is never overridden), and by the
// field each default writes. Pure slots hold __cxa_pure_virtual in the original.
// The constructor is out of line (0x69a00 IKNode2d_ConstructBase), called by every derived constructor.
#pragma once
#include <cstdint>

#include "k2000/core/IKSerializable.h"
#include "k2000/core/Layout.h"
#include "k2000/math/CVector2.h"

class IKTime;

class IKNode2d : public IKSerializable {
public:
    IKNode2d();                                                             // 0x00069a00 IKNode2d_ConstructBase
    ~IKNode2d() override {}                                                 // vt+0x00 / +0x04  0x9944b8 / 0x994478
    int32_t IsKindOfClass(uint32_t key) override { return key == 0x24d || key == 0xc; }  // vt+0x08 0x9943b8
    void Destroy() override { FreeMemory(); }                               // vt+0x10 0x69d68 (calls vt+0x54)
    int32_t GetClassType() override { return kCategoryGraphical; }          // vt+0x14 0x994260 (unregistered key 0x24d)
    int32_t GetClassID() override { return 9; }                             // vt+0x18 0x994268
    // vt+0x24 0x69848 (Ghidra: CColorTextButton2d_RecursiveRegistration; it is IKNode2d's own slot)
    void RecursiveRegistration(int32_t type) override;
    int32_t Save(IKFile* /*file*/) override { return 1; }                   // vt+0x28 0x69d60
    int32_t Load(IKFile* file, int32_t type) override;                      // vt+0x2c 0x69da8 IKNode2d_Load
    int32_t GetSerializationFlags() override { return 2; }                  // vt+0x34 0x994258 (XXL2 IKNode2d's own)
    // vt+0x50 0x994278. XXL2: SetOwner(CScene2d*).
    virtual void SetOwner(IKSerializable* owner) { m_pOwner = owner; }
    virtual void FreeMemory();                                              // vt+0x54 0x69ce8
    virtual void RecursiveNodeReach(uint8_t /*what*/, void* /*data*/) {}    // vt+0x58 0x994270 (empty)
    virtual void Lock() { m_baFlags = static_cast<uint8_t>(m_baFlags | 1); }                // vt+0x5c 0x994280
    virtual void Unlock() { m_baFlags = static_cast<uint8_t>(m_baFlags & 0xfe); }           // vt+0x60 0x9943a8
    virtual void Enable() { m_baFlags = static_cast<uint8_t>(m_baFlags | 2); }              // vt+0x64 0x994390 (Ghidra: Show)
    virtual void Disable() { m_baFlags = static_cast<uint8_t>(m_baFlags & 0xfd); }          // vt+0x68 0x994378 (Ghidra: Hide)
    // vt+0x6c 0x994298 / +0x70 0x9942a0 (they store +0x0c / +0x10; Ghidra has the two names swapped:
    // IKNode2d_SetNextSibling / IKNode2d_SetPrevSibling).
    virtual void SetPrevious(IKNode2d* previous) { m_pPrevious = previous; }
    virtual void SetNext(IKNode2d* next) { m_pNext = next; }
    virtual void SetPos(const CVector2& position) { m_vPosition = position; }  // vt+0x74 0x9942a8
    virtual void GetBoundingBox(CBox2D* /*box*/) const {}                   // vt+0x78 0x698a8 (empty)
    // vt+0x7c 0x698b0 IKNode2d_GetScreenRect_maybe (DotD): GetBoundingBox, then both corners through
    // UI2d_NormalizedToRasterPixels_maybe (engine +0x38). STUB(C1.6)
    virtual void Vf7C(CBox2D* /*box*/) {}
    virtual void Scale(const CVector2& scale) = 0;                          // vt+0x80 (XXL2 slot 31)
    virtual void Render(IKTime* time) = 0;                                  // vt+0x84 (XXL2 slot 32; arguments unverified)

    uint8_t m_ui8Type;             // +0x04
    uint8_t m_baFlags;             // +0x05 XXL2 CBitArray8: bit 0 Lock, bit 1 Enable
    uint8_t m_ui8CenterWAlign;     // +0x06
    uint8_t m_ui8CenterHAlign;     // +0x07
    IKSerializable* m_pOwner;      // +0x08 CScene2d (a reference)
    IKNode2d* m_pPrevious;         // +0x0c a reference
    IKNode2d* m_pNext;             // +0x10 a reference
    CVector2 m_vPosition;          // +0x14
    float m_f32RotateAngle;        // +0x1c
    CVector2 m_v2ConstantScale;    // +0x20 the constructor sets (1, 1); Load leaves it
};
DOTD_ASSERT_SIZE(IKNode2d, 0x28);
DOTD_ASSERT_OFFSET(IKNode2d, m_ui8Type, 0x04);
DOTD_ASSERT_OFFSET(IKNode2d, m_baFlags, 0x05);
DOTD_ASSERT_OFFSET(IKNode2d, m_ui8CenterWAlign, 0x06);
DOTD_ASSERT_OFFSET(IKNode2d, m_ui8CenterHAlign, 0x07);
DOTD_ASSERT_OFFSET(IKNode2d, m_pOwner, 0x08);
DOTD_ASSERT_OFFSET(IKNode2d, m_pPrevious, 0x0c);
DOTD_ASSERT_OFFSET(IKNode2d, m_pNext, 0x10);
DOTD_ASSERT_OFFSET(IKNode2d, m_vPosition, 0x14);
DOTD_ASSERT_OFFSET(IKNode2d, m_f32RotateAngle, 0x1c);
DOTD_ASSERT_OFFSET(IKNode2d, m_v2ConstantScale, 0x20);
