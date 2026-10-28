// CKPlayAnimCinematicBloc.h - plays an animation on an actor (key 0xc8, vtable 0xb1b7d8, size 0x9c). Original unit: CKPlayAnimCinematicBloc.cpp.
// XXL2: the same members in the same load order.
// The ground-contact blocks are CKSrvCamera's XXL2 types (CGroundContactDatasIn/InOut).
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/misc/IKCinematicBloc.h"
#include "k2000/cameras/CKSrvCamera.h"
#include "k2000/math/CMatrix34.h"

class IKFile;

class CKPlayAnimCinematicBloc : public IKCinematicBloc {
public:
    DOTD_CLASS_KEY(kCategoryCinematic, 0x3)
    DOTD_DECLARE_FACTORIES(CKPlayAnimCinematicBloc)
    DOTD_BLOC_IS_KIND_OF()

    CKPlayAnimCinematicBloc();  // 0x00185560 CKPlayAnimCinematicBloc_Create (the constructor inlined)
    ~CKPlayAnimCinematicBloc() override {}

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x00185ad8 CKPlayAnimCinematicBloc_Load

    void Start() override;                 // vt+0x5c 0x00185710 CKPlayAnimCinematicBloc_Start
    void Complete() override;              // vt+0x64 0x00186240 CKPlayAnimCinematicBloc_Complete
    void Update(IKTime* time) override;    // vt+0x68 0x00185f18 CKPlayAnimCinematicBloc_Update
    void Stop() override;                  // vt+0x6c 0x00185250 CKPlayAnimCinematicBloc_Stop
    void Abort() override;                 // vt+0x70 0x00184d38 CKPlayAnimCinematicBloc_Abort
    uint8_t UsesActor() override { return 1; }              // vt+0x80 0x009a9d70
    uint8_t IsExclusiveOnActor() override { return 1; }     // vt+0x84 0x009a9d78
    uint8_t GetAnimCount() override { return 1; }           // vt+0x88 0x009a9d80
    int32_t GetAnimIndex() override { return static_cast<int32_t>(m_ui32AnimChosen); }  // vt+0x8c 0x009a9d88
    // 0x00184de0 CKPlayAnimCinematicBloc_AdvanceAnim_maybe: one frame of the animation, and the bloc's end (flags +0x50: bit 0
    // and 1 end with the animation, bit 2 at the end time, none after the animation time).
    void AdvanceAnim(IKTime* time);

    float m_fTimeElapsed;                                // +0x38 runtime
    float m_fAnimTime;                                   // +0x3c
    float m_fStartTime;                                  // +0x40
    float m_fBeginTime;                                  // +0x44
    float m_fEndTime;                                    // +0x48
    uint32_t m_ui32AnimChosen;                           // +0x4c
    uint8_t m_baPlayAnim;                                // +0x50 CBitArray8
    uint8_t m_pad51[3];
    CKSrvCamera::CGroundContactDatasIn m_DatasIn;        // +0x54 the Load sets 0.5, 1.2, 1, 8
    CKSrvCamera::CGroundContactDatasInOut m_DatasInOut;  // +0x64
    CVector3 m_v3Pos;                                    // +0x90
};
DOTD_ASSERT_SIZE(CKPlayAnimCinematicBloc, 0x9c);
DOTD_ASSERT_OFFSET(CKPlayAnimCinematicBloc, m_fTimeElapsed, +0x38);
DOTD_ASSERT_OFFSET(CKPlayAnimCinematicBloc, m_fAnimTime, +0x3c);
DOTD_ASSERT_OFFSET(CKPlayAnimCinematicBloc, m_fStartTime, +0x40);
DOTD_ASSERT_OFFSET(CKPlayAnimCinematicBloc, m_fBeginTime, +0x44);
DOTD_ASSERT_OFFSET(CKPlayAnimCinematicBloc, m_fEndTime, +0x48);
DOTD_ASSERT_OFFSET(CKPlayAnimCinematicBloc, m_ui32AnimChosen, +0x4c);
DOTD_ASSERT_OFFSET(CKPlayAnimCinematicBloc, m_baPlayAnim, +0x50);
DOTD_ASSERT_OFFSET(CKPlayAnimCinematicBloc, m_DatasIn, +0x54);
DOTD_ASSERT_OFFSET(CKPlayAnimCinematicBloc, m_DatasInOut, +0x64);
DOTD_ASSERT_OFFSET(CKPlayAnimCinematicBloc, m_v3Pos, +0x90);
