// CKCinematicSceneData.h - an actor of a cinematic scene (key 0xa8c, vtable 0xb1ac70, size 0x20).
// Original unit: CKCinematicSceneData.cpp. XXL2: K/KServices/KServiceCinematic/CKCinematicSceneData.h,
// the same members in the same order; DotD's interrupt position is four half-words.
#pragma once
#include <cstdint>

#include "k2000/core/IKSerializable.h"
#include "k2000/core/Layout.h"

class IKFile;

class CKCinematicSceneData : public IKSerializable {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x2a)
    DOTD_DECLARE_FACTORIES(CKCinematicSceneData)
    int32_t IsKindOfClass(uint32_t key) override { return key == kClassKey || key == 0xc; }  // 0x9a8d20

    CKCinematicSceneData();  // 0x0016e260 CKCinematicSceneData_Create (the constructor inlined)
    ~CKCinematicSceneData() override {}

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x0016e2b8 CKCinematicSceneData_Load
    // vt+0x30 0x0016dec8 CKCinematicSceneData_PostLoad: for type 0 the saved matrix pointer (+0x1c) cleared. 1.
    int32_t PostLoad(int32_t type) override {
        if (type == 0) m_pOriginalMatrix = nullptr;
        return 1;
    }
    // vt+0x24 0x0016de00 CKCinematicSceneData_RecursiveRegistration: registered with the saving manager unless the type
    // is 4..7, then the animation dictionary (+0x08, when there is one) with the same type. (vt+0x10 0x0016ddf8
    // CKCinematicSceneData_Destroy is empty.)
    void RecursiveRegistration(int32_t type) override;

    // 0x0016e0c8 CKCinematicSceneData_AllocSavedMatrix_maybe / 0x0016e088 FreeSavedMatrix_maybe: the actor's saved
    // local matrix (RwMatrixCreate / RwMatrixDestroy; SetActorsLocked fills it).
    void AllocSavedMatrix();
    void FreeSavedMatrix();
    // 0x0016dee0 CKCinematicSceneData_GetBeaconPosition_maybe: the interrupt beacon's (+0x10: sector, kluster, set id,
    // beacon) three half-words x 0.1.
    void GetBeaconPosition(float* position) const;
    // 0x0016e4a8 CKCinematicSceneData_GetBeaconDirection_maybe: the beacon's direction byte (+6) as a yaw (x pi / 128):
    // (sin, 0, cos) through the game's inlined polynomials.
    void GetBeaconDirection(float* direction) const;

    IKSerializable* m_pHook;        // +0x04 IKHook
    IKSerializable* m_pAnimDico;    // +0x08 CAnimationDictionary; 0 in the constructor
    uint8_t m_DataFlags;            // +0x0c CBitArray8
    uint8_t m_pad0d[3];
    uint16_t m_aUnk10[4];           // +0x10 _maybe XXL2 m_baInterrupPos (CKBeaconAccessor); 0xffff each
    IKSerializable* m_pShadowData;  // +0x18 _maybe XXL2 m_pShadowData (CKShadowGround); the Load clears it
    void* m_pOriginalMatrix;        // +0x1c _maybe XXL2 m_pOriginalMatrix (CMatrix34*); not set
};
DOTD_ASSERT_SIZE(CKCinematicSceneData, 0x20);
DOTD_ASSERT_OFFSET(CKCinematicSceneData, m_pHook, 0x04);
DOTD_ASSERT_OFFSET(CKCinematicSceneData, m_pAnimDico, 0x08);
DOTD_ASSERT_OFFSET(CKCinematicSceneData, m_DataFlags, 0x0c);
DOTD_ASSERT_OFFSET(CKCinematicSceneData, m_aUnk10, 0x10);
DOTD_ASSERT_OFFSET(CKCinematicSceneData, m_pShadowData, 0x18);
