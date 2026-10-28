// CKHkS08AirCurrent.h - an air current the dragon glides in (key 0x2b02, vtable 0xb27918, size 0x130).
// Original unit: CKHkS08AirCurrent.cpp. No XXL2 class. Reference types in comments come from the struct
// draft (live samples).
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/misc/CKHkActorBase.h"

class CKHkS08AirCurrent : public CKHkActorBase {
public:
    DOTD_CLASS_KEY(kCategoryHook, 0xac)
    DOTD_DECLARE_FACTORIES(CKHkS08AirCurrent)

    // 0x00474b70 CKHkS08AirCurrent_Construct (inlined in 0x00474e58 CKHkS08AirCurrent_Create): the base's only.
    CKHkS08AirCurrent() {}
    ~CKHkS08AirCurrent() override {}

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x004779e0 CKHkS08AirCurrent_Load
    void SetDefaultState(int32_t flag) override;        // vt+0x38 0x00474d90 CKHkS08AirCurrent_SetDefaultState (C2.2)
    void Start() override;                              // vt+0x50 0x004749a0 CKHkS08AirCurrent_Start (C2.2)

    uint16_t m_ui16NbUnk24;                    // +0x20 lhbrx: the count of +0x24 and +0x28
    uint8_t m_pad22[2];
    IKSerializable** m_apUnk24;                // +0x24 Mem_AllocAligned16, m_ui16NbUnk24 references (0: null)
    uint8_t* m_aUnk28;                         // +0x28 OperatorNewArray, m_ui16NbUnk24 bytes (0: null)
    IKSerializable* m_pUnk2C;                  // +0x2c
    IKSerializable* m_pUnk30;                  // +0x30 a CNode
    IKSerializable* m_pUnk34;                  // +0x34
    uint16_t m_unk38;                          // +0x38 lhbrx
    uint8_t m_pad3A[2];
    IKSerializable* m_pUnk3C;                  // +0x3c a CFogBoxNodeFx
    uint16_t m_unk40;                          // +0x40 lhbrx
    uint8_t m_pad42[2];
    IKSerializable* m_pUnk44;                  // +0x44 a CFogBoxNodeFx
    IKSerializable* m_pUnk48;                  // +0x48 a CKSoundDictionaryID (read last)
    uint32_t m_unk4C;                          // +0x4c
    float m_fUnk50;                            // +0x50
    float m_fUnk54;                            // +0x54
    float m_fUnk58;                            // +0x58
    float m_fUnk5C;                            // +0x5c
    float m_fUnk60;                            // +0x60
    float m_fUnk64;                            // +0x64
    float m_afUnk68[11];                       // +0x68..+0x93 read one by one
    IKSerializable* m_pUnk94;                  // +0x94 a CMultiGeometryBasic
    IKSerializable* m_pUnk98;                  // +0x98 a CKSpline4L
    float m_afUnk9C[3];                        // +0x9c a vector
    float m_fUnkA8;                            // +0xa8
    float m_fUnkAC;                            // +0xac
    uint32_t m_unkB0;                          // +0xb0
    uint32_t m_unkB4;                          // +0xb4
    uint32_t m_unkB8;                          // +0xb8
    float m_fUnkBC;                            // +0xbc
    float m_fUnkC0;                            // +0xc0
    float m_fUnkC4;                            // +0xc4
    float m_fUnkC8;                            // +0xc8
    float m_fUnkCC;                            // +0xcc
    IKSerializable* m_pUnkD0;                  // +0xd0 a CKHkDetectorGroup
    uint32_t m_unkD4;                          // +0xd4
    IKSerializable* m_pUnkD8;                  // +0xd8 a CKCameraConstraint
    IKSerializable* m_pUnkDC;                  // +0xdc
    uint8_t m_ui8NbUnkE4;                      // +0xe0 (the live word holds a pointer later: runtime)
    uint8_t m_padE1[3];
    IKSerializable** m_apUnkE4;                // +0xe4 Mem_AllocAligned16, m_ui8NbUnkE4 references
    uint32_t m_unkE8[18];                      // +0xe8..+0x12f runtime (PostLoad sets +0x124/+0x128)
};
DOTD_ASSERT_SIZE(CKHkS08AirCurrent, 0x130);
DOTD_ASSERT_OFFSET(CKHkS08AirCurrent, m_ui16NbUnk24, 0x20);
DOTD_ASSERT_OFFSET(CKHkS08AirCurrent, m_apUnk24, 0x24);
DOTD_ASSERT_OFFSET(CKHkS08AirCurrent, m_aUnk28, 0x28);
DOTD_ASSERT_OFFSET(CKHkS08AirCurrent, m_pUnk2C, 0x2c);
DOTD_ASSERT_OFFSET(CKHkS08AirCurrent, m_unk38, 0x38);
DOTD_ASSERT_OFFSET(CKHkS08AirCurrent, m_pUnk3C, 0x3c);
DOTD_ASSERT_OFFSET(CKHkS08AirCurrent, m_unk40, 0x40);
DOTD_ASSERT_OFFSET(CKHkS08AirCurrent, m_pUnk44, 0x44);
DOTD_ASSERT_OFFSET(CKHkS08AirCurrent, m_pUnk48, 0x48);
DOTD_ASSERT_OFFSET(CKHkS08AirCurrent, m_unk4C, 0x4c);
DOTD_ASSERT_OFFSET(CKHkS08AirCurrent, m_fUnk50, 0x50);
DOTD_ASSERT_OFFSET(CKHkS08AirCurrent, m_fUnk5C, 0x5c);
DOTD_ASSERT_OFFSET(CKHkS08AirCurrent, m_fUnk64, 0x64);
DOTD_ASSERT_OFFSET(CKHkS08AirCurrent, m_afUnk68, 0x68);
DOTD_ASSERT_OFFSET(CKHkS08AirCurrent, m_pUnk94, 0x94);
DOTD_ASSERT_OFFSET(CKHkS08AirCurrent, m_afUnk9C, 0x9c);
DOTD_ASSERT_OFFSET(CKHkS08AirCurrent, m_fUnkA8, 0xa8);
DOTD_ASSERT_OFFSET(CKHkS08AirCurrent, m_unkB0, 0xb0);
DOTD_ASSERT_OFFSET(CKHkS08AirCurrent, m_fUnkBC, 0xbc);
DOTD_ASSERT_OFFSET(CKHkS08AirCurrent, m_fUnkCC, 0xcc);
DOTD_ASSERT_OFFSET(CKHkS08AirCurrent, m_pUnkD0, 0xd0);
DOTD_ASSERT_OFFSET(CKHkS08AirCurrent, m_unkD4, 0xd4);
DOTD_ASSERT_OFFSET(CKHkS08AirCurrent, m_pUnkDC, 0xdc);
DOTD_ASSERT_OFFSET(CKHkS08AirCurrent, m_ui8NbUnkE4, 0xe0);
DOTD_ASSERT_OFFSET(CKHkS08AirCurrent, m_apUnkE4, 0xe4);
