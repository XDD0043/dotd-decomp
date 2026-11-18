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
    int32_t IsKindOfClass(uint32_t key) override {  // vt+0x08 0x9c46c8
        return key == 0x2b02 || key == 0xd82 || key == 0x2 || key == 0x2fe || key == 0x3fe || key == 0xc;
    }
    DOTD_DECLARE_FACTORIES(CKHkS08AirCurrent)

    // 0x00474b70 CKHkS08AirCurrent_Construct (inlined in 0x00474e58 CKHkS08AirCurrent_Create): the base's only.
    CKHkS08AirCurrent();
    // 0x00474bf0 CKHkS08AirCurrent_Destructor: the vtable, then CKHkActorBase's (0x474c20 BaseDestructor / 0x474ba8
    // DeletingDestructor the same).
    ~CKHkS08AirCurrent() override;
    // vt+0x24 0x00474a48 CKHkS08AirCurrent_RecursiveRegistration: CKHkActorBase's (inherited here).
    // vt+0x40 0x004741b8 CKHkS08AirCurrent_GetInfo: the actor base's answer (KStub_Return1_3f7140) folded: 2 kept, else
    // whether it is non-zero.
    int32_t GetInfo(struct IKInfo* info, int32_t request) override {
        const int32_t base = CKHkActorBase::GetInfo(info, request);
        if (base == 2) return 2;
        return base != 0 ? 1 : 0;
    }
    // vt+0x10 0x00474a70 CKHkS08AirCurrent_Destroy: CKHkActorBase's (empty), +0x24 freed (Mem_FreeAligned16), +0x28 deleted
    // (OperatorDeleteArray, when set), +0xe4 freed.
    void Destroy() override;
    // vt+0x1c 0x00474160 CKHkS08AirCurrent_MessageProc: the actor base's answer folded (3 and 2 kept, 0 stays 0, else 1).
    int32_t MessageProc(uint16_t message, void* data) override {
        const int32_t base = CKHkActorBase::MessageProc(message, data);  // 0x003f7148
        if (base == 3 || base == 2) return base;
        return base == 0 ? 0 : 1;
    }

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x004779e0 CKHkS08AirCurrent_Load
    void SetDefaultState(int32_t flag) override;        // vt+0x38 0x00474d90 CKHkS08AirCurrent_SetDefaultState (C2.2)
    void Start() override;                              // vt+0x50 0x004749a0 CKHkS08AirCurrent_Start (C2.2)
    // vt+0x30 0x004749c8 CKHkS08AirCurrent_PostLoad: the base's; type 0: both FX intensities 1.
    int32_t PostLoad(int32_t type) override;
    // vt+0x54 0x00474140 CKHkS08AirCurrent_Restart: unless bit 2, the time inside back to 0.
    void Restart() override;
    // vt+0x7c 0x004765c0 CKHkS08AirCurrent_Update: the flow FX, the alpha flicker, the sound, the FX intensities, the
    // gusts (4 rand draws when their timer runs out) and the heroes inside (the game manager's per-hero wind records),
    // the camera constraint.
    void Update(IKTime* frameClock) override;
    // vt+0xa0 0x00476438 CKHkS08AirCurrent_OnActivate (the sector became active): the wind, the timers (1 rand draw),
    // the FX intensities, the records, the FX collection (+0xdc) played.
    void VfA0() override;
    // vt+0xa4 0x004748c0 CKHkS08AirCurrent_OnDeactivate: the base's, the sound stopped.
    void VfA4() override;
    // vt+0xc8 0x00474d30 CKHkS08AirCurrent_vfC8: bit 11 (on) from bit 3 (state 0) or bit 4 (state 1).
    void ApplyStatePreset(int32_t state) override;
    // vt+0xcc 0x00476400 CKHkS08AirCurrent_vfCC: bit 11 = `enabled`, the records added or removed.
    void SetEnabled(int32_t enabled) override;

    // 0x00474208 CKHkS08AirCurrent_UpdateAlphaFlicker_maybe (inlined in Update): +0x30's alpha moves toward a random
    // target (1 rand draw when reached).
    void UpdateAlphaFlicker(float dt);
    // 0x00474310 CKHkS08AirCurrent_SetFxIntensity_maybe: the alphas of +0x30 / +0x34 (intensity a) and of the +0x24
    // nodes / the flow node +0x2c (intensity b).
    void SetFxIntensity(float a, float b);
    // 0x00474470 CKHkS08AirCurrent_UpdateFlowFx_maybe: the flow node (+0x2c) runs along the spline (+0x98) and fades;
    // a new run when its timer runs out (6 rand draws); the FX collections (+0xe4) not playing restart on a random node
    // of +0x24 (1 rand draw each), the others advance.
    void UpdateFlowFx(float dt);
    // 0x004754a0 CKHkS08AirCurrent_AddRecords_maybe / 0x00474f60 RemoveRecords_maybe: the fog boxes' (+0x3c / +0x44)
    // records (boxes): at even distances along the spline, or in a grid over the shape (3 rand draws each); the
    // records leave the boxes again.
    void AddRecords();
    void RemoveRecords();
    // 0x00475278 CKHkS08AirCurrent_ClampPositionToTube_maybe (CKHkS08Hero_UpdateFlyingMovement_maybe's, the hero's
    // position +0x54c; its third argument, the hero's +0x558, is not read): the spline (+0x98) point nearest to the
    // position; a position farther than the tube radius (+0xac) less 0.05 from it, with the point inside the spline's
    // ends (more than 0.05 from each), is put back on the tube's wall; otherwise it is returned as it is.
    CVector3 ClampPositionToTube(const CVector3* position);
    // DOTD (x64): the hero record's air current word (+0xe14, word 7) holds the low 32 bits of the current's address;
    // this finds the live air current with those bits (null when none). Not in the original.
    static CKHkS08AirCurrent* FromRecordWord(uint32_t word);

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
    float m_fUnk4C;                            // +0x4c AddRecords: the records' height base
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
    float m_unkB0;                             // +0xb0 the gust interval (minimum)
    float m_unkB4;                             // +0xb4 the gust interval (maximum)
    float m_unkB8;                             // +0xb8 the gust strength (minimum; +0xbc the maximum)
    float m_fUnkBC;                            // +0xbc
    float m_fUnkC0;                            // +0xc0
    float m_fUnkC4;                            // +0xc4
    float m_fUnkC8;                            // +0xc8
    float m_fUnkCC;                            // +0xcc
    IKSerializable* m_pUnkD0;                  // +0xd0 a CKHkDetectorGroup
    float m_unkD4;                             // +0xd4 the ramp time of the push for a hero inside
    IKSerializable* m_pUnkD8;                  // +0xd8 a CKCameraConstraint
    IKSerializable* m_pUnkDC;                  // +0xdc
    uint8_t m_ui8NbUnkE4;                      // +0xe0 (the live word holds a pointer later: runtime)
    uint8_t m_padE1[3];
    IKSerializable** m_apUnkE4;                // +0xe4 Mem_AllocAligned16, m_ui8NbUnkE4 references
    // Runtime (not read).
    float m_afWind[3];                         // +0xe8 the push direction times the strength (OnActivate, the gusts)
    float m_fStrength;                         // +0xf4 OnActivate: +0xa8
    float m_fGustTimer;                        // +0xf8
    float m_fFlowTimer;                        // +0xfc the flow FX's current run
    float m_fFlowSpeed;                        // +0x100
    float m_fFlowFadeIn;                       // +0x104
    float m_fFlowFadeOut;                      // +0x108
    float m_fFlowDistance;                     // +0x10c along the spline
    float m_fFlowAngle;                        // +0x110 degrees
    float m_fFlowAlpha;                        // +0x114
    float m_fFlowFadeInTotal;                  // +0x118
    float m_fAlpha;                            // +0x11c +0x30's alpha
    float m_fAlphaTarget;                      // +0x120
    float m_fIntensityA;                       // +0x124 PostLoad 1
    float m_fIntensityB;                       // +0x128 PostLoad 1
    float m_fTimeInside;                       // +0x12c a hero inside
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
DOTD_ASSERT_OFFSET(CKHkS08AirCurrent, m_fUnk4C, 0x4c);
DOTD_ASSERT_OFFSET(CKHkS08AirCurrent, m_afWind, 0xe8);
DOTD_ASSERT_OFFSET(CKHkS08AirCurrent, m_fFlowTimer, 0xfc);
DOTD_ASSERT_OFFSET(CKHkS08AirCurrent, m_fAlpha, 0x11c);
DOTD_ASSERT_OFFSET(CKHkS08AirCurrent, m_fTimeInside, 0x12c);
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
