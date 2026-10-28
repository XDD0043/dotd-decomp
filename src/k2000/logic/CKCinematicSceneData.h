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

    // 0x0016e0c8 CKCinematicSceneData_AllocSavedMatrix_maybe / 0x0016e088 FreeSavedMatrix_maybe: the actor's saved
    // local matrix (RwMatrixCreate / RwMatrixDestroy; SetActorsLocked fills it).
    void AllocSavedMatrix();
    void FreeSavedMatrix();
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
