// CKAnimatedChain.h - a bone chain posed from a grid of key quaternions by two angles towards a target (key 0x18d,
// vtable 0xb16c30, size 0x6c; XXL2: K/KModules/KGL/KinematicsChain/ChainAnimation/CKAnimatedChain.h, the same members in
// the same order). Original unit: CKAnimatedChain.cpp (0x90308-0x92830). No game file holds one.
//
// m_ChainState (XXL2 CBitArray16): bit 0 active, bit 1 blend before stop, bit 2 the approach is moving, bit 3 the target
// is given as angles (no recompute from the bones), bit 4 the target is a direction, bit 5 the goal was reached, bit 6
// two key sets (the inter grid) / blend with the animation, bit 7 first update, bit 8 cleared by the first update, bit 9
// the angles overran the key range (_maybe for bits 1, 6 and 8: XXL2's accessor order).
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/graphical/IKKinematicsChain.h"
#include "k2000/math/CMatrix34.h"

class CKAnimatedChain : public IKKinematicsChain {
public:
    DOTD_CLASS_KEY(kCategoryGraphical, 0x6)
    int32_t IsKindOfClass(uint32_t key) override {  // vt+0x08 0x99c5c8
        return key == 0x18d || key == 0x10d || key == 0xc;
    }
    DOTD_DECLARE_FACTORIES(CKAnimatedChain)

    // XXL2 CQuaternion: (x, y, z, w).
    struct Quat {
        float m_a[4];
    };

    // 0x00090be8 CKAnimatedChain_Create: operator new(0x6c), the base (the next link null), the vtable, the speed 50.
    // The rest is left as the heap has it (Load sets most of it); zeroed here (the port's fresh heap).
    CKAnimatedChain();
    ~CKAnimatedChain() override {}  // vt+0x00 / +0x04 0x99c638 / 0x99c5f0: the vtables only

    // vt+0x10 0x00090c38 CKAnimatedChain_Destroy: the bone numbers, the final and animated quaternions and the two angle
    // arrays freed (nothing cleared; the key grids are not freed).
    void Destroy() override;
    // vt+0x24 0x00090358 CKAnimatedChain_RecursiveRegistration: itself registered with the saving manager (engine
    // +0x50, vt+0x24 with a null second argument), every type.
    void RecursiveRegistration(int32_t type) override;
    // vt+0x2c 0x00091298 CKAnimatedChain_Load (every type): the defaults (speed 2, maximum 2, no reference bone), the
    // next link, the bone count, the node and its hierarchy, the bone numbers, the key count and the two angle arrays.
    int32_t Load(IKFile* file, int32_t type) override;

    // vt+0x50 0x00090650 CKAnimatedChain_vf50 (XXL2 GetBoneNumInHierarchy).
    uint32_t GetBoneNumInHierarchy(uint32_t bone) override { return m_pTabOfBoneNum[bone]; }
    // vt+0x54 0x00092610 CKAnimatedChain_Update_maybe (XXL2 UpdateChain): while the clock runs: an active chain blends
    // its final quaternions with the animation (bit 6), or steps towards the target (bit 7 first takes the frames as the
    // final quaternions); an inactive one blending before its stop approaches the target angles; then the hierarchy's
    // matrices.
    void UpdateChain(IKTime* clock) override;

    // 0x000909c8 CKAnimatedChain_SampleBlendGrid_maybe / 0x000907e0 CKAnimatedChain_SampleBlendGridLayered_maybe (XXL2
    // GetInterKey): bone `bone`'s animated quaternion from the key grid cell (x, y) at (tx, ty); the layered one also
    // blends in the inter grid by m_fInterBlendCoef.
    void SampleBlendGrid(int32_t x, int32_t y, uint8_t bone, float tx, float ty);
    void SampleBlendGridLayered(int32_t x, int32_t y, uint8_t bone, float tx, float ty);
    // 0x000910a8 CKAnimatedChain_ApproachTargetBlend_maybe (XXL2 BlendBeforeStop): the angles move towards the target
    // angles at the accelerated speed, the frames slerped from the final quaternions by the step made.
    void BlendBeforeStop(IKTime* clock);
    // 0x00091950 CKAnimatedChain_ComputeTargetCoordsFromBones_maybe (XXL2 InterpolationAimAtSolver): the two target
    // angles (degrees) of the target (a point, or a direction with bit 4) seen from the reference bone.
    void InterpolationAimAtSolver();
    // 0x00091d08 CKAnimatedChain_SampleAtCoords_maybe (XXL2 GetInterpolationParam + the sampling): `y` / `x` clamped
    // into the key ranges (bit 9 set when the x one overran), their cells and fractions found, every bone sampled; 1.
    int32_t SampleAtCoords(float* y, float* x);
    // 0x00092270 CKAnimatedChain_StepToTargetCoords_maybe (XXL2 UpDateInterpolationAimAtMode): the target angles (from the
    // bones unless bit 3), the sample there, then either the pose taken at once or (bit 1) approached at the accelerated
    // speed.
    void UpDateInterpolationAimAtMode(IKTime* clock);

    uint8_t m_ui8NumOfBone;          // +0x10
    uint8_t m_ui8NumOfKeyByAxe;      // +0x11
    uint8_t m_ui8BoneRef;            // +0x12
    int8_t m_i8NumBoneForPosRef;     // +0x13 Load sets -1 (the first chain bone)
    uint32_t* m_pTabOfBoneNum;       // +0x14 OperatorNewArray(count * 4)
    float* m_pfAngleValues[2];       // +0x18 the y and x key angles (OperatorNewArray(keys * 4) each)
    float m_fYTargetAngle;           // +0x20
    float m_fXTargetAngle;           // +0x24
    CVector3 m_vTarget;              // +0x28
    float m_fYAngle;                 // +0x34
    float m_fXAngle;                 // +0x38
    Quat*** m_pQuatMatrix;           // +0x3c [bone][x][y] key quaternions (not loaded here)
    Quat*** m_pQuatInterMatrix;      // +0x40 the second key set, same shape
    Quat* m_pQuatAnim;               // +0x44 per bone (the original's OperatorNewArray with a count word)
    Quat* m_pQuatFinal;              // +0x48 per bone
    float m_fSpeedUp;                // +0x4c the acceleration
    float m_fCurrentSpeed;           // +0x50
    float m_fSpeed;                  // +0x54 Create 50; Load 2
    float m_fSpeedMin;               // +0x58
    float m_fSpeedMax;               // +0x5c Load 2
    float m_fInterBlendCoef;         // +0x60
    float m_fInterAnimCoef;          // +0x64
    uint16_t m_ChainState;           // +0x68 XXL2 CBitArray16
    uint8_t m_pad6a[2];
};
DOTD_ASSERT_SIZE(CKAnimatedChain, 0x6c);
DOTD_ASSERT_OFFSET(CKAnimatedChain, m_ui8NumOfBone, 0x10);
DOTD_ASSERT_OFFSET(CKAnimatedChain, m_pTabOfBoneNum, 0x14);
DOTD_ASSERT_OFFSET(CKAnimatedChain, m_pfAngleValues, 0x18);
DOTD_ASSERT_OFFSET(CKAnimatedChain, m_vTarget, 0x28);
DOTD_ASSERT_OFFSET(CKAnimatedChain, m_pQuatMatrix, 0x3c);
DOTD_ASSERT_OFFSET(CKAnimatedChain, m_pQuatAnim, 0x44);
DOTD_ASSERT_OFFSET(CKAnimatedChain, m_fSpeedUp, 0x4c);
DOTD_ASSERT_OFFSET(CKAnimatedChain, m_fInterAnimCoef, 0x64);
DOTD_ASSERT_OFFSET(CKAnimatedChain, m_ChainState, 0x68);
