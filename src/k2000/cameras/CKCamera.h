// CKCamera.h - a fixed camera (key 0x47, vtable 0xb1a2b8, size 0x88). Original unit: CKCamera.cpp.
// XXL2 has only m_fRollAngle after IKCamera; DotD keeps copies of the position and target and moves the camera by an
// offset over a duration (CKCamera_Update).
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/cameras/IKCamera.h"

class IKFile;

class CKCamera : public IKCamera {
public:
    DOTD_CLASS_KEY(kCategoryCamera, 0x1)
    int32_t IsKindOfClass(uint32_t key) override {  // vt+0x08 0x9a75e8
        return key == 0x47 || key == 0x347 || key == 0xc;
    }
    DOTD_DECLARE_FACTORIES(CKCamera)

    // 0x0013dae0 CKCamera_Create: IKCamera_ConstructBase, then the vtable.
    CKCamera() {}
    ~CKCamera() override {}

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x0013df58 CKCamera_Load
    // vt+0x50 0x0013d9d8 CKCamera_Activate_maybe: the attached fx started (+0x50), +0x74 cleared. The
    // start position argument is ignored.
    void Start(const CVector3* startPosition) override;
    // vt+0x58 0x0013db90 CKCamera_Deactivate_maybe: the attached fx stopped; with a move duration (+0x78) and a
    // non-zero move offset (+0x7c) the position and target are reset to the loaded ones (+0x5c / +0x68).
    void Stop() override;
    // vt+0x6c 0x0013db38 CKCamera_ResetTrack_maybe: the loaded pose back (position, target, the field of view and +0x58).
    void ResetTrack() override;
    // vt+0x60 0x0013dc60 CKCamera_Update: the attached fx (IKCamera_UpdateTrackBase), then while the move time
    // (+0x74) is below the move duration (+0x78) the position and target slide from the loaded ones by the offset +0x7c
    // (right, up, along the view) times the elapsed fraction.
    void Update(float frameTime) override;
    float Vf84() const override { return AsFloat(m_unk58); }  // vt+0x84 0x9a7620: +0x58
    // vt+0x88 0x9a7638: +0x58 = value, clamped to [-80, 80] (TOC -0x3e24 / -0x3e20; a NaN is stored as is).
    void Vf88(float value) override {
        if (value <= -80.0f) value = -80.0f;
        else if (value >= 80.0f) value = 80.0f;
        m_unk58 = AsWord(value);
    }
    uint8_t VfB0() const override { return static_cast<uint8_t>((m_Flags >> 8) & 1u); }  // vt+0xb0 0x9a7628: m_Flags bit 8
    // vt+0xb8 0x9a76e8 (CKCamera's own slot): the position and its loaded copy (+0x5c) = *position; the target's
    // loaded copy (+0x68) = the target.
    virtual void SetPosition(const CVector3* position) {
        m_unk5c.x = position->x;
        m_WorldPosition.x = position->x;
        m_WorldPosition.z = position->z;
        m_WorldPosition.y = position->y;
        m_unk5c.z = position->z;
        m_unk5c.y = position->y;
        m_unk68.x = m_WorldTarget.x;
        m_unk68.z = m_WorldTarget.z;
        m_unk68.y = m_WorldTarget.y;
    }

    uint32_t m_unk58;    // +0x58
    CVector3 m_unk5c;    // +0x5c every Load copies m_WorldPosition here
    CVector3 m_unk68;    // +0x68 every Load copies m_WorldTarget here
    float m_fMoveElapsed;     // +0x74 the move time (Start: 0; Update adds the frame time up to the duration)
    // +0x78 the move duration (0: no move). XXL2's one member m_fRollAngle sits here, but CKCamera_Update divides
    // the move time by it and Stop resets the pose only when it and the offset are set (LVL010: 0 to 20).
    float m_fMoveDuration;
    CVector3 m_v3MoveOffset;  // +0x7c the move (right, up, along the view); (0, 0, 1) when there is no move
};
DOTD_ASSERT_SIZE(CKCamera, 0x88);
DOTD_ASSERT_OFFSET(CKCamera, m_unk58, +0x58);
DOTD_ASSERT_OFFSET(CKCamera, m_unk5c, +0x5c);
DOTD_ASSERT_OFFSET(CKCamera, m_unk68, +0x68);
DOTD_ASSERT_OFFSET(CKCamera, m_fMoveElapsed, +0x74);
DOTD_ASSERT_OFFSET(CKCamera, m_fMoveDuration, +0x78);
DOTD_ASSERT_OFFSET(CKCamera, m_v3MoveOffset, +0x7c);
