// CKHkPlatform.h - a moving platform (key 0x3a42, vtable 0xb26000, size 0x1f4). Original unit:
// CKHkPlatform.cpp. XXL2 has CKHkPlatform (K/KMeca/Platform, base IKHkMeca); DotD's derives from
// CKHkActorBase and loads more (reference arrays, more floats). XXL2 names are used where the layout
// matches: the three vectors and the quaternion read in XXL2's order (m_vPositionOffset, m_vStartPath,
// m_vDirPath, m_qBaseOrientation), the ground-contact pair, and the runtime block that the Load's inlined
// InitVariables sets (XXL2 CKHkPlatform::InitVariables, called at the end of its Load for every type).
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/hooks/GroundContact.h"
#include "k2000/math/CMatrix34.h"
#include "k2000/misc/CKHkActorBase.h"
#include "k2000/services/CTriggerStarter.h"

class CKHkPlatform : public CKHkActorBase {
public:
    DOTD_CLASS_KEY(kCategoryHook, 0xe9)
    DOTD_DECLARE_FACTORIES(CKHkPlatform)

    // 0x0041f278 CKHkPlatform_Create (inlined constructor): the ground-contact defaults, +0x08 = -1 (the
    // IKLife priority word) and +0x190 = 0xffff.
    CKHkPlatform() {
        m_ui32Priority = 0xffffffffu;
        m_pfPointIndex = 0xffff;
    }
    ~CKHkPlatform() override {}

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x004212a0 CKHkPlatform_Load

    uint8_t m_unk20;                           // +0x20 the count of +0x24
    uint8_t m_pad21[3];
    IKSerializable** m_apUnk24;                // +0x24 references (Mem_AllocAligned16)
    IKSerializable* m_unk28;                   // +0x28
    IKSerializable* m_unk2C;                   // +0x2c
    float m_unk30[8];                          // +0x30..+0x4c read in order
    float m_unk50[3];                          // +0x50..+0x58 read after the quaternion
    float m_unk5C[11];                         // +0x5c..+0x84 read after +0x4c
    CVector3 m_vPositionOffset;                // +0x88 XXL2 name (12-byte read)
    CVector3 m_vStartPath;                     // +0x94 XXL2 name
    CVector3 m_vDirPath;                       // +0xa0 XXL2 name
    float m_qBaseOrientation[4];               // +0xac XXL2 CQuaternion m_qBaseOrientation (16-byte read)
    IKSerializable* m_unkBC;                   // +0xbc
    CGroundContactDatasIn m_GrndDataIn;        // +0xc0 XXL2 name
    CGroundContactDatasInOut m_GrndDataInOut;  // +0xd0 XXL2 name
    CTriggerStarter m_unkFC;                   // +0xfc _maybe XXL2 m_tsReachedEnd
    CTriggerStarter m_unk104;                  // +0x104 _maybe XXL2 m_tsReachedStart
    uint8_t m_unk10C;                          // +0x10c runtime
    uint8_t m_unk10D;                          // +0x10d
    uint8_t m_pad10E[2];
    float m_unk110[9];                         // +0x110..+0x130
    uint8_t m_unk134;                          // +0x134 the count of +0x138
    uint8_t m_pad135[3];
    IKSerializable** m_apUnk138;               // +0x138 references (Mem_AllocAligned16), 0 without
    float m_unk13C;                            // +0x13c
    float m_unk140;                            // +0x140
    IKSerializable* m_unk144[4];               // +0x144..+0x150 four single reference reads
    uint8_t m_unk154[6];                       // +0x154..+0x159
    uint8_t m_pad15A[2];
    // The block below is set by the Load's inlined InitVariables for every serialization type.
    float m_fPositionOnPath;                   // +0x15c _maybe XXL2: +0x40 * +0x6c
    float m_fTimer;                            // +0x160 _maybe XXL2: 0
    float m_qLastSlopeRotation[4];             // +0x164 _maybe XXL2: (0, 0, 0, 1)
    float m_qLastPathRotation[4];              // +0x174 _maybe XXL2: m_qBaseOrientation
    CVector3 m_pfPoint;                        // +0x184 _maybe XXL2 CPFPoint m_pfPoint: (0, 0, 0)
    uint16_t m_pfPointIndex;                   // +0x190 constructor and InitVariables 0xffff
    uint8_t m_pad192[2];
    CVector3 m_vPosition;                      // +0x194 _maybe XXL2: (0, 0, 0)
    uint32_t m_unk1A0[2];                      // +0x1a0 runtime
    float m_unk1A8;                            // +0x1a8 InitVariables 0
    CVector3 m_unk1AC;                         // +0x1ac InitVariables (0, 0, 0)
    CVector3 m_unk1B8;                         // +0x1b8 InitVariables (0, 0, 0)
    uint8_t m_unk1C4;                          // +0x1c4 InitVariables 0
    uint8_t m_pad1C5[3];
    CVector3 m_unk1C8;                         // +0x1c8 InitVariables (0, 0, 0)
    CVector3 m_unk1D4;                         // +0x1d4 InitVariables (0, 0, 0)
    uint32_t m_unk1E0[5];                      // +0x1e0 runtime
};
DOTD_ASSERT_SIZE(CKHkPlatform, 0x1f4);
DOTD_ASSERT_OFFSET(CKHkPlatform, m_unk20, 0x20);
DOTD_ASSERT_OFFSET(CKHkPlatform, m_apUnk24, 0x24);
DOTD_ASSERT_OFFSET(CKHkPlatform, m_unk28, 0x28);
DOTD_ASSERT_OFFSET(CKHkPlatform, m_unk30, 0x30);
DOTD_ASSERT_OFFSET(CKHkPlatform, m_unk50, 0x50);
DOTD_ASSERT_OFFSET(CKHkPlatform, m_unk5C, 0x5c);
DOTD_ASSERT_OFFSET(CKHkPlatform, m_vPositionOffset, 0x88);
DOTD_ASSERT_OFFSET(CKHkPlatform, m_vStartPath, 0x94);
DOTD_ASSERT_OFFSET(CKHkPlatform, m_vDirPath, 0xa0);
DOTD_ASSERT_OFFSET(CKHkPlatform, m_qBaseOrientation, 0xac);
DOTD_ASSERT_OFFSET(CKHkPlatform, m_unkBC, 0xbc);
DOTD_ASSERT_OFFSET(CKHkPlatform, m_GrndDataIn, 0xc0);
DOTD_ASSERT_OFFSET(CKHkPlatform, m_GrndDataInOut, 0xd0);
DOTD_ASSERT_OFFSET(CKHkPlatform, m_unkFC, 0xfc);
DOTD_ASSERT_OFFSET(CKHkPlatform, m_unk104, 0x104);
DOTD_ASSERT_OFFSET(CKHkPlatform, m_unk10D, 0x10d);
DOTD_ASSERT_OFFSET(CKHkPlatform, m_unk110, 0x110);
DOTD_ASSERT_OFFSET(CKHkPlatform, m_unk134, 0x134);
DOTD_ASSERT_OFFSET(CKHkPlatform, m_apUnk138, 0x138);
DOTD_ASSERT_OFFSET(CKHkPlatform, m_unk13C, 0x13c);
DOTD_ASSERT_OFFSET(CKHkPlatform, m_unk144, 0x144);
DOTD_ASSERT_OFFSET(CKHkPlatform, m_unk154, 0x154);
DOTD_ASSERT_OFFSET(CKHkPlatform, m_fPositionOnPath, 0x15c);
DOTD_ASSERT_OFFSET(CKHkPlatform, m_qLastSlopeRotation, 0x164);
DOTD_ASSERT_OFFSET(CKHkPlatform, m_qLastPathRotation, 0x174);
DOTD_ASSERT_OFFSET(CKHkPlatform, m_pfPoint, 0x184);
DOTD_ASSERT_OFFSET(CKHkPlatform, m_pfPointIndex, 0x190);
DOTD_ASSERT_OFFSET(CKHkPlatform, m_vPosition, 0x194);
DOTD_ASSERT_OFFSET(CKHkPlatform, m_unk1A8, 0x1a8);
DOTD_ASSERT_OFFSET(CKHkPlatform, m_unk1AC, 0x1ac);
DOTD_ASSERT_OFFSET(CKHkPlatform, m_unk1B8, 0x1b8);
DOTD_ASSERT_OFFSET(CKHkPlatform, m_unk1C4, 0x1c4);
DOTD_ASSERT_OFFSET(CKHkPlatform, m_unk1C8, 0x1c8);
DOTD_ASSERT_OFFSET(CKHkPlatform, m_unk1D4, 0x1d4);
