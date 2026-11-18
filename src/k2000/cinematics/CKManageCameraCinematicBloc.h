// CKManageCameraCinematicBloc.h - switches the camera (key 0x5c8, vtable 0xb1b578, size 0x50). Original unit: CKManageCameraCinematicBloc.cpp.
// XXL2: the same members in the same load order (m_bCameraSet and m_fCameraCurTime are runtime).
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/misc/IKCinematicBloc.h"

class IKFile;

class CKManageCameraCinematicBloc : public IKCinematicBloc {
public:
    DOTD_CLASS_KEY(kCategoryCinematic, 0x17)
    DOTD_DECLARE_FACTORIES(CKManageCameraCinematicBloc)
    DOTD_BLOC_IS_KIND_OF()

    // 0x0017fac0 CKManageCameraCinematicBloc_Create: IKCinematicBloc_Construct, then the vtable.
    CKManageCameraCinematicBloc() {}
    ~CKManageCameraCinematicBloc() override {}

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x0017ffb8 CKManageCameraCinematicBloc_Load
    // vt+0x24 0x0017f8e0 CKManageCameraCinematicBloc_RecursiveRegistration: registered (unless 4..7), the base's, the camera's,
    // then the target leaf's when it has no parent (CSGLeaf +0x0c).
    void RecursiveRegistration(int32_t type) override;

    void Start() override;                  // vt+0x5c 0x0017fbd8 CKManageCameraCinematicBloc_Start
    void Complete() override;               // vt+0x64 0x00180188 CKManageCameraCinematicBloc_Complete
    void Update(IKTime* time) override;     // vt+0x68 0x0017f770 CKManageCameraCinematicBloc_Update
    void Stop() override;                   // vt+0x6c 0x0017f590 CKManageCameraCinematicBloc_Stop
    void Abort() override;                  // vt+0x70 0x0017f4a8 CKManageCameraCinematicBloc_Abort

    IKSerializable* m_pCamera;   // +0x38 IKCamera
    float m_fTransitionTime;     // +0x3c
    uint8_t m_ui8CamTransition;  // +0x40
    uint8_t m_bCameraSet;        // +0x41 _maybe (XXL2 order); runtime
    uint8_t m_pad42[2];
    IKSerializable* m_pTarget;   // +0x44 XXL2 CSGLeaf
    float m_fCameraTime;         // +0x48
    float m_fCameraCurTime;      // +0x4c _maybe (XXL2 order); runtime
};
DOTD_ASSERT_SIZE(CKManageCameraCinematicBloc, 0x50);
DOTD_ASSERT_OFFSET(CKManageCameraCinematicBloc, m_pCamera, +0x38);
DOTD_ASSERT_OFFSET(CKManageCameraCinematicBloc, m_fTransitionTime, +0x3c);
DOTD_ASSERT_OFFSET(CKManageCameraCinematicBloc, m_ui8CamTransition, +0x40);
DOTD_ASSERT_OFFSET(CKManageCameraCinematicBloc, m_bCameraSet, +0x41);
DOTD_ASSERT_OFFSET(CKManageCameraCinematicBloc, m_pTarget, +0x44);
DOTD_ASSERT_OFFSET(CKManageCameraCinematicBloc, m_fCameraTime, +0x48);
DOTD_ASSERT_OFFSET(CKManageCameraCinematicBloc, m_fCameraCurTime, +0x4c);
