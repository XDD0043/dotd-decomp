// CKHkDynamicObject.h - an object that translates/rotates on its own (key 0x39c2, vtable 0xb2ec90, size
// 0xf8; library-TOC code). Original unit: k2000/ui/CKHkDynamicObject.cpp. XXL2 has a class of this name
// (K/KDynamicObject, 240 bytes), but the DotD layout differs (two matrices, references where XXL2 has
// CVector2 arrays): the fields keep m_unkXX names; XXL2 counterparts are noted as _maybe.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/hooks/IKHook.h"
#include "k2000/math/CMatrix34.h"
#include "k2000/services/CTriggerStarter.h"

class CKHkDynamicObject : public IKHook {
public:
    DOTD_CLASS_KEY(kCategoryHook, 0xe7)
    DOTD_DECLARE_FACTORIES(CKHkDynamicObject)

    // 0x005aa418 CKHkDynamicObject_Create (inlined constructor, = 0x005a9c18 _Construct): only the
    // IKLife/IKHook defaults.
    CKHkDynamicObject() {}
    ~CKHkDynamicObject() override {}

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x005ab7a8 CKHkDynamicObject_Load

    CMatrix34* m_pMatrix20;          // +0x20 RwMatrixCreate + CMatrix34_LoadMatrix (XXL2 m_pStartMatrix_maybe)
    CMatrix34* m_pMatrix24;          // +0x24 RwMatrixCreate + CMatrix34_LoadMatrix
    uint32_t m_unk28;                // +0x28 a word (0x10284 in the LVL030 samples)
    float m_aUnk2C[3];               // +0x2c one 0xc-byte read (axis_maybe: 0,0,1 in the samples)
    float m_unk38;                   // +0x38
    float m_unk3C;                   // +0x3c
    float m_unk40;                   // +0x40
    IKSerializable* m_pUnk44;        // +0x44 reference
    float m_aUnk48[3];               // +0x48 one 0xc-byte read (a point_maybe)
    float m_aUnk54[3];               // +0x54 one 0xc-byte read (axis_maybe: 0,1,0)
    float m_unk60;                   // +0x60
    float m_unk64;                   // +0x64
    IKSerializable* m_pUnk68;        // +0x68 reference
    float m_unk6C;                   // +0x6c
    float m_unk70;                   // +0x70
    float m_unk74;                   // +0x74
    float m_unk78;                   // +0x78
    float m_unk7C;                   // +0x7c
    IKSerializable* m_pUnk80;        // +0x80 reference
    IKSerializable* m_pUnk84;        // +0x84 reference
    float m_unk88;                   // +0x88
    float m_unk8C;                   // +0x8c
    float m_unk90;                   // +0x90
    IKSerializable* m_pUnk94;        // +0x94 reference
    CTriggerStarter m_tsUnk98;       // +0x98
    CTriggerStarter m_tsUnkA0;       // +0xa0
    uint8_t m_unkA8;                 // +0xa8
    uint8_t m_unkA9;                 // +0xa9
    uint8_t m_padAA[2];
    uint32_t m_unkAC[17];            // +0xac..+0xef runtime (not set by Create or Load)
    IKSerializable* m_pUnkF0;        // +0xf0 reference
    uint32_t m_unkF4;                // +0xf4 runtime
};
DOTD_ASSERT_SIZE(CKHkDynamicObject, 0xf8);
DOTD_ASSERT_OFFSET(CKHkDynamicObject, m_pMatrix20, 0x20);
DOTD_ASSERT_OFFSET(CKHkDynamicObject, m_unk28, 0x28);
DOTD_ASSERT_OFFSET(CKHkDynamicObject, m_aUnk2C, 0x2c);
DOTD_ASSERT_OFFSET(CKHkDynamicObject, m_unk38, 0x38);
DOTD_ASSERT_OFFSET(CKHkDynamicObject, m_pUnk44, 0x44);
DOTD_ASSERT_OFFSET(CKHkDynamicObject, m_aUnk48, 0x48);
DOTD_ASSERT_OFFSET(CKHkDynamicObject, m_aUnk54, 0x54);
DOTD_ASSERT_OFFSET(CKHkDynamicObject, m_unk60, 0x60);
DOTD_ASSERT_OFFSET(CKHkDynamicObject, m_pUnk68, 0x68);
DOTD_ASSERT_OFFSET(CKHkDynamicObject, m_unk6C, 0x6c);
DOTD_ASSERT_OFFSET(CKHkDynamicObject, m_pUnk80, 0x80);
DOTD_ASSERT_OFFSET(CKHkDynamicObject, m_unk88, 0x88);
DOTD_ASSERT_OFFSET(CKHkDynamicObject, m_pUnk94, 0x94);
DOTD_ASSERT_OFFSET(CKHkDynamicObject, m_tsUnk98, 0x98);
DOTD_ASSERT_OFFSET(CKHkDynamicObject, m_unkA8, 0xa8);
DOTD_ASSERT_OFFSET(CKHkDynamicObject, m_pUnkF0, 0xf0);
