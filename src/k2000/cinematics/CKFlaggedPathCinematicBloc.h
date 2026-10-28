// CKFlaggedPathCinematicBloc.h - moves an actor along a flagged path (key 0x148, vtable 0xb1b268, size 0x100). Original unit: CKFlaggedPathCinematicBloc.cpp.
// XXL2: the same members (m_v3CurrentPos, m_sv3LookAt, m_sfSpeed, the speeds, the ground contact,
// m_pFlaggedPath, m_fDist, m_AnimStateEngine, m_pTime, m_bPutOnGround and the three arrays) at DotD's
// offsets. The ground-contact blocks are CKSrvCamera's XXL2 types.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/misc/IKCinematicBloc.h"
#include "k2000/cameras/CKSrvCamera.h"
#include "k2000/math/CMatrix34.h"

class IKFile;

class CKFlaggedPathCinematicBloc : public IKCinematicBloc {
public:
    DOTD_CLASS_KEY(kCategoryCinematic, 0x5)
    DOTD_DECLARE_FACTORIES(CKFlaggedPathCinematicBloc)
    DOTD_BLOC_IS_KIND_OF()

    CKFlaggedPathCinematicBloc();  // 0x001784d0 CKFlaggedPathCinematicBloc_Create (the constructor inlined)
    ~CKFlaggedPathCinematicBloc() override {}

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x00179320 CKFlaggedPathCinematicBloc_Load

    CVector3 m_v3CurrentPos;                             // +0x38 runtime
    uint32_t m_sv3LookAt[7];                             // +0x44 XXL2 CSmoothedCVector3Linear; runtime
    float m_sfSpeed[3];                                  // +0x60 XXL2 CSmoothedFloat32Linear; 0 in the constructor
    float m_fWalkSpeed;                                  // +0x6c
    float m_fRunSpeed;                                   // +0x70 read first
    float m_fTimeForStatique;                            // +0x74
    float m_fStatiqueStartTime;                          // +0x78 the Load sets -1
    float m_fRotationSpeed;                              // +0x7c
    CKSrvCamera::CGroundContactDatasIn m_DatasIn;        // +0x80 the Load sets 0.5, 1.2, 1, 8
    CKSrvCamera::CGroundContactDatasInOut m_DatasInOut;  // +0x90
    IKSerializable* m_pFlaggedPath;                      // +0xbc CKFlaggedPath
    float m_fDist;                                       // +0xc0 the Load sets 0
    CKFlaggedPathCinematicBloc* m_AnimStateEngineOwner;  // +0xc4 XXL2 CStateEngine m_AnimStateEngine: the owner (the Load sets this)
    uint32_t* m_AnimStateEngineTable;                    // +0xc8 Mem_AllocAligned16(0x18): the state handlers (see the Load)
    uint8_t m_AnimStateEngineState;                      // +0xcc the Load sets 3
    uint8_t m_AnimStateEngineUnkCd;                      // +0xcd 0xff in the constructor
    uint8_t m_padce[2];
    IKSerializable* m_pTime;                             // +0xd0 XXL2 IKTime*; the Load sets 0
    uint8_t m_bPutOnGround;                              // +0xd4
    uint8_t m_padd5[3];
    int32_t m_i32Tab[3];                                 // +0xd8
    float m_fSpeedArray[3];                              // +0xe4
    float m_fAccelerateArray[3];                         // +0xf0
    float m_fAngleRotate;                                // +0xfc
};
DOTD_ASSERT_SIZE(CKFlaggedPathCinematicBloc, 0x100);
DOTD_ASSERT_OFFSET(CKFlaggedPathCinematicBloc, m_v3CurrentPos, +0x38);
DOTD_ASSERT_OFFSET(CKFlaggedPathCinematicBloc, m_sv3LookAt, +0x44);
DOTD_ASSERT_OFFSET(CKFlaggedPathCinematicBloc, m_sfSpeed, +0x60);
DOTD_ASSERT_OFFSET(CKFlaggedPathCinematicBloc, m_fWalkSpeed, +0x6c);
DOTD_ASSERT_OFFSET(CKFlaggedPathCinematicBloc, m_fRunSpeed, +0x70);
DOTD_ASSERT_OFFSET(CKFlaggedPathCinematicBloc, m_fTimeForStatique, +0x74);
DOTD_ASSERT_OFFSET(CKFlaggedPathCinematicBloc, m_fStatiqueStartTime, +0x78);
DOTD_ASSERT_OFFSET(CKFlaggedPathCinematicBloc, m_fRotationSpeed, +0x7c);
DOTD_ASSERT_OFFSET(CKFlaggedPathCinematicBloc, m_DatasIn, +0x80);
DOTD_ASSERT_OFFSET(CKFlaggedPathCinematicBloc, m_DatasInOut, +0x90);
DOTD_ASSERT_OFFSET(CKFlaggedPathCinematicBloc, m_pFlaggedPath, +0xbc);
DOTD_ASSERT_OFFSET(CKFlaggedPathCinematicBloc, m_fDist, +0xc0);
DOTD_ASSERT_OFFSET(CKFlaggedPathCinematicBloc, m_AnimStateEngineOwner, +0xc4);
DOTD_ASSERT_OFFSET(CKFlaggedPathCinematicBloc, m_AnimStateEngineTable, +0xc8);
DOTD_ASSERT_OFFSET(CKFlaggedPathCinematicBloc, m_AnimStateEngineState, +0xcc);
DOTD_ASSERT_OFFSET(CKFlaggedPathCinematicBloc, m_AnimStateEngineUnkCd, +0xcd);
DOTD_ASSERT_OFFSET(CKFlaggedPathCinematicBloc, m_pTime, +0xd0);
DOTD_ASSERT_OFFSET(CKFlaggedPathCinematicBloc, m_bPutOnGround, +0xd4);
DOTD_ASSERT_OFFSET(CKFlaggedPathCinematicBloc, m_i32Tab, +0xd8);
DOTD_ASSERT_OFFSET(CKFlaggedPathCinematicBloc, m_fSpeedArray, +0xe4);
DOTD_ASSERT_OFFSET(CKFlaggedPathCinematicBloc, m_fAccelerateArray, +0xf0);
DOTD_ASSERT_OFFSET(CKFlaggedPathCinematicBloc, m_fAngleRotate, +0xfc);
