// CKHkS08SavePoint.h - a save point hook (key 0x2e02, size 0x84). Original unit: CKHkS08SavePoint.cpp.
// No XXL2 class. The fields are named by offset until their use is known.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/misc/CKHkActorBase.h"
#include "k2000/services/CTriggerStarter.h"

class CKHkS08SavePoint : public CKHkActorBase {
public:
    DOTD_CLASS_KEY(kCategoryHook, 0xb8)
    int32_t IsKindOfClass(uint32_t key) override {  // vt+0x08 0x9c5a50
        return key == 0x2e02 || key == 0xd82 || key == 0x2 || key == 0x2fe || key == 0x3fe || key == 0xc;
    }
    DOTD_DECLARE_FACTORIES(CKHkS08SavePoint)

    // 0x004c9e88 CKHkS08SavePoint_Construct (inlined in 0x004ca1b0 CKHkS08SavePoint_Create): the actor
    // base only.
    CKHkS08SavePoint() {}
    ~CKHkS08SavePoint() override {}

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x004cc318 CKHkS08SavePoint_Load
    void Start() override;    // vt+0x50 0x004c9d90 CKHkS08SavePoint_Start (C2.2)
    void Restart() override {}  // vt+0x54 0x004c9928 CKHkS08SavePoint_Restart (empty)

    // vt+0xcc 0x004ca0b8 CKHkS08SavePoint_SetEnabled: +0x0c bit 3 = `enabled` while the game manager's vt+0xc4 answers 0.
    void SetEnabled(int32_t enabled) override;
    // vt+0xd0 0x004ca2c0 CKHkS08SavePoint_SetVisible: shown (while the game manager's vt+0xc4 answers 0): enabled (+0x0c
    // bit 3), both particle nodes emitting, the fog box placed (PlaceFogBox), the node shown; else not enabled, the
    // particles stopped, the fog box given back (as OnDeactivate) and the node hidden.
    void SetVisible(int32_t visible) override;

    // C2.8 save-menu. The flag word +0x0c: bit 3 enabled, bit 4 a hero in reach, bit 5 just used (the save asked).
    // vt+0x1c 0x004ca9c8 CKHkS08SavePoint_MessageProc: 0x93f (a hero uses it: sounds 0 and 1, the spawn point +0x34
    // current, a save asked, the used state) and 0x2666 (the prompt text of the CKLocTextAccessor +0x64).
    int32_t MessageProc(uint16_t message, void* data) override;
    int32_t GetInfo(IKInfo* info, int32_t request) override;  // vt+0x40 0x004c9930 CKHkS08SavePoint_GetInfo
    // vt+0x24 0x004c9e38 / vt+0x28 0x004c9e10: the actor base's (CKHkActorBase_d82_maybe_RecursiveRegistration
    // 0x3f6ee8: the node's below type 4; IKHook_Save writes nothing), then 1.
    void RecursiveRegistration(int32_t type) override {
        if (static_cast<uint32_t>(type - 4) > 3u && m_pKGLObject != nullptr) m_pKGLObject->RecursiveRegistration(type);
    }
    int32_t Save(IKFile* /*file*/, int32_t /*type*/) override { return 1; }
    void Stop() override {}   // vt+0x68 0x004c9d68 CKHkS08SavePoint_Stop: CKHkActorBase_d82_maybe_Stop (empty)
    // vt+0x7c 0x004cb030 CKHkS08SavePoint_Update: the alphas and the fog's toward the state's targets, the model's turn,
    // the heroes in reach (the nearest within the radius +0x54 and the height +0x58), the sounds 2 / 3, the particle
    // node +0x3c and the hero interaction target (mode 2).
    void Update(IKTime* frameClock) override;
    void VfA0() override;  // vt+0xa0 0x004cbbf0 CKHkS08SavePoint_OnActivate
    void VfA4() override;  // vt+0xa4 0x004ca7e8 CKHkS08SavePoint_OnDeactivate

    // The alphas of the node's first three geometries and of the fog box node +0x40, and the model's turn, set from
    // the colour groups: 0x44 / 0x4d (idle or used), 0x47 / 0x4e (enabled), 0x4a / 0x4f (a hero in reach).
    void ApplyAlphas();
    // The model turned by m_fYaw about its own y at its modelling position (the node's local matrix).
    void ApplyYaw();
    // The fog box +0x40's box of this save point (a new one when there is none and room): the node's world matrix,
    // the box's particles randomised (CFogBoxNodeFx_RandomizeEmitterParticles_maybe).
    void PlaceFogBox();

    IKSerializable* m_pSoundDico;   // +0x20
    CTriggerStarter m_unk24;    // +0x24
    CTriggerStarter m_unk2C;    // +0x2c
    IKSerializable* m_pSpawnPoint;   // +0x34
    IKSerializable* m_pUnk38;   // +0x38
    IKSerializable* m_pReachParticlesNode;   // +0x3c
    IKSerializable* m_pFogBoxNode;   // +0x40 a CFogBoxNodeFx (Ghidra struct type)_maybe
    // +0x44..+0x4f bytes read raw (file order): the geometries' alphas when off (disabled or just used), idle (no
    // hero near) and with a hero in reach (Update 0x4cb030; LVL010: 1e0a1e, 783c50, ffffff), then the fog box's three.
    uint8_t m_aui8OffGeomAlpha[3];         // +0x44
    uint8_t m_aui8IdleGeomAlpha[3];         // +0x47
    uint8_t m_aui8ReachGeomAlpha[3];         // +0x4a
    uint8_t m_ui8OffFogAlpha;            // +0x4d
    uint8_t m_ui8IdleFogAlpha;            // +0x4e
    uint8_t m_ui8ReachFogAlpha;            // +0x4f
    float m_fAlphaApproachSpeed;             // +0x50 the alphas' speed (per second)
    float m_fReachRadius;             // +0x54 the reach radius
    float m_fReachHeight;             // +0x58 the reach height (above the node)
    float m_fActiveYawSpeedDeg;             // +0x5c the turn speed with a hero in reach (degrees per second; read as a word)
    float m_fYawAccel;             // +0x60 the turn acceleration (read as a word)
    IKSerializable* m_pPromptTextAccessor;   // +0x64 CKLocTextAccessor: the prompt (message 0x2666)
    // C2.8 save-menu: the run-time state (the constructor leaves it to the zeroed heap; OnActivate sets it).
    float m_fAlpha0;            // +0x68 the first geometry's alpha (toward +0x44 / +0x47 / +0x4a)
    float m_fAlpha1;            // +0x6c the second geometry's (+0x45 / +0x48 / +0x4b)
    float m_fAlpha2;            // +0x70 the third geometry's (+0x46 / +0x49 / +0x4c)
    float m_fFogAlpha;          // +0x74 the fog box node's (+0x4d / +0x4e / +0x4f)
    float m_fYaw;               // +0x78 the model's turn (degrees)
    float m_fYawSpeed;          // +0x7c toward 0 or +0x5c at +0x60
    float m_fUsedTime;          // +0x80 the time since the save point was used (flag bit 5)
};
DOTD_ASSERT_SIZE(CKHkS08SavePoint, 0x84);
DOTD_ASSERT_OFFSET(CKHkS08SavePoint, m_pSoundDico, 0x20);
DOTD_ASSERT_OFFSET(CKHkS08SavePoint, m_unk24, 0x24);
DOTD_ASSERT_OFFSET(CKHkS08SavePoint, m_unk2C, 0x2c);
DOTD_ASSERT_OFFSET(CKHkS08SavePoint, m_pSpawnPoint, 0x34);
DOTD_ASSERT_OFFSET(CKHkS08SavePoint, m_pFogBoxNode, 0x40);
DOTD_ASSERT_OFFSET(CKHkS08SavePoint, m_aui8OffGeomAlpha, 0x44);
DOTD_ASSERT_OFFSET(CKHkS08SavePoint, m_aui8IdleGeomAlpha, 0x47);
DOTD_ASSERT_OFFSET(CKHkS08SavePoint, m_aui8ReachGeomAlpha, 0x4a);
DOTD_ASSERT_OFFSET(CKHkS08SavePoint, m_ui8OffFogAlpha, 0x4d);
DOTD_ASSERT_OFFSET(CKHkS08SavePoint, m_fAlphaApproachSpeed, 0x50);
DOTD_ASSERT_OFFSET(CKHkS08SavePoint, m_fActiveYawSpeedDeg, 0x5c);
DOTD_ASSERT_OFFSET(CKHkS08SavePoint, m_fYawAccel, 0x60);
DOTD_ASSERT_OFFSET(CKHkS08SavePoint, m_pPromptTextAccessor, 0x64);
DOTD_ASSERT_OFFSET(CKHkS08SavePoint, m_fAlpha0, 0x68);
DOTD_ASSERT_OFFSET(CKHkS08SavePoint, m_fUsedTime, 0x80);
