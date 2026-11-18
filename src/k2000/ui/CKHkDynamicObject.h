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
    // vt+0x10 0x005aa040 CKHkDynamicObject_Destroy: the three matrices (+0x20, +0x24, +0xe4) destroyed and cleared.
    void Destroy() override;
    // vt+0x40 0x005aa2f0 CKHkDynamicObject_vf40 (GetInfo): 0x10 the accessor 0x9cbe88 GetTriggerProp10 (the angle
    // +0xbc - +0xe8 in whole degrees, lroundf), value type 2 (a float).
    int32_t GetInfo(IKInfo* info, int32_t request) override;
    // port-rest R09:
    int32_t PostLoad(int32_t type) override;                      // vt+0x30 0x005abff8 CKHkDynamicObject_PostLoad
    void SetDefaultState(int32_t flag) override;                  // vt+0x38 0x005ac608 _ResetToInitialState_maybe
    int32_t SetGameState(const SApplyGameState* state) override;  // vt+0x3c 0x005ac2a0 CKHkDynamicObject_vf3C
    void Start() override;                                        // vt+0x50 0x005ac9a0 CKHkDynamicObject_ResetRuntime
    void Restart() override;                                      // vt+0x54 0x005ac818 CKHkDynamicObject_ReinitRuntime
    void VfA0() override;                                         // vt+0xa0 0x005aa248 CKHkDynamicObject_OnActivate
    void VfA4() override;                                         // vt+0xa4 0x005aa1c8 CKHkDynamicObject_OnDeactivate
    virtual void SetActive(uint8_t active);                       // vt+0xc0 0x005aa170 CKHkDynamicObject_SetActive_maybe
    // The resets' shared part (inlined in each): +0xc4 = 1, +0xd4 = 1, +0xc0 / +0xc8 / +0xcc / +0xd0 / +0xd8 = 0, the
    // bits 6..8 axis through the start matrix into +0xb0.
    void ResetMotionState();
    // port-final F06:
    // vt+0x1c 0x005aa480 CKHkDynamicObject_HandleMessage (MessageProc): the messages 0x496..0x4a4 (a 15-case jump
    // table): the angle targets (0x496 absolute / 0x497 relative, degrees), the motion bits of +0x28 set / cleared, the
    // running matrix (+0xe4) taken from the node, the active flag (vt+0xc0). 1 for any other message.
    int32_t MessageProc(uint16_t message, void* data) override;
    // vt+0x7c 0x005aab98 CKHkDynamicObject_Update: when active (+0xec), the translation (bit 0: along +0x2c, linear
    // or the curve +0x44), the turn about the point +0x48 / axis +0x54 (bit 1), the rotation (bit 2 spin / bit 3 face
    // the focused hero / bit 4 the angle target, with its curve +0x84 under bit 18), then the axes scaled by +0x90.
    void Update(IKTime* clock) override;
    // vt+0x24 0x5aa018: IKHook's RecursiveRegistration (inherited). vt+0x68 / +0x70 / +0x78 0x5a9c60 / 0x5a9c68 /
    // 0x5a9c70: empty (IKHook's). 0x5ab788 / 0x5acb00: the vtables only (implicit).

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
    // +0xac..+0xef runtime (not set by Create or Load).
    uint32_t m_unkAC;                // +0xac the flags word (+0x28) saved by ResetRuntime, restored by ReinitRuntime
    float m_aUnkB0[3];               // +0xb0 (Mat4_TransformVectors of +0x20 into it: PostLoad, the resets)
    float m_unkBC;                   // +0xbc the angle (radians_maybe; GetTriggerProp10)
    float m_unkC0;                   // +0xc0
    float m_unkC4;                   // +0xc4 the resets: 1.0f
    float m_unkC8;                   // +0xc8
    float m_unkCC;                   // +0xcc
    float m_unkD0;                   // +0xd0
    uint8_t m_unkD4;                 // +0xd4 the resets: 1
    uint8_t m_padD5[3];
    float m_unkD8;                   // +0xd8
    float m_unkDC;                   // +0xdc the angle a move to the target +0xd8 starts from (MessageProc 0x496 / 0x497)
    float m_unkE0;                   // +0xe0
    CMatrix34* m_pMatrixE4;          // +0xe4 RwMatrixCreate (PostLoad); the node's matrix while active
    float m_unkE8;                   // +0xe8 the angle's origin (GetTriggerProp10)
    uint8_t m_unkEC;                 // +0xec active (SetActive); SetDefaultState copies +0xa8
    uint8_t m_padED[3];
    IKSerializable* m_pUnkF0;        // +0xf0 reference (a CKGroundCpnt: the collision grounds)
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
