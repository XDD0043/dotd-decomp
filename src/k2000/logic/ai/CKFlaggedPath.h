// CKFlaggedPath.h - a path with trigger starters at given positions (key 0x5cc, vtable 0xb17bd8, size
// 0x28). Original unit: CKFlaggedPath.cpp. XXL2: K/KServices/KServiceBeacon/CKFlaggedPath.h (m_pPath,
// m_ui32NbOfBeacon, m_fCursorPos, m_bInOrder, m_aBeaconList, m_aTriggerToCallList); DotD adds a vector
// of word pairs at +0x1c.
#pragma once
#include <cstdint>

#include "k2000/core/IKSerializable.h"
#include "k2000/core/Layout.h"
#include "k2000/math/CMatrix34.h"
#include "k2000/services/CTriggerStarter.h"
#include "k2000/util/TVector.h"

class CKFlaggedPath : public IKSerializable {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x17)
    int32_t IsKindOfClass(uint32_t key) override { return key == 0x5cc || key == 0xc; }  // vt+0x08 0x9a1c70
    DOTD_DECLARE_FACTORIES(CKFlaggedPath)

    struct Pair {  // 8 bytes; names ours
        uint32_t m_unk0;
        uint32_t m_unk4;
    };

    CKFlaggedPath();  // inlined in 0x000c44b0 CKFlaggedPath_Create
    ~CKFlaggedPath() override {}

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x000c4568 CKFlaggedPath_Load
    // vt+0x10 0x000c4520 CKFlaggedPath_Destroy: the beacon block (with the starters) freed.
    void Destroy() override;
    // 0x000c4350 CKFlaggedPath_GetSegmentValueAt_maybe: the value of the last pair whose beacon lies before `distance`
    // (at 0, the first pair's value when its beacon is at 0); 0 without pairs.
    float GetSegmentValueAt(float distance) const;

    // 0x000c4eb8 CKFlaggedPath_SetDistanceAndGetPosition: the cursor moves to `distance`; every beacon crossed on the way
    // (forwards or backwards) fires its trigger starter (QueueTriggerSignals); then as SetDistanceAndGetPositionUp.
    // (The PS3 passes an unused word between `point` and `direction`.)
    void SetDistanceAndGetPosition(float distance, CVector3* point, CVector3* direction, CVector3* up);
    // 0x000c4d88 CKFlaggedPath_SetDistanceAndGetPositionUp_maybe: the cursor set, the path's point at the distance (and
    // its direction, vt+0x54), with `up` the roll up vector there (ComputeRollUpVector).
    void SetDistanceAndGetPositionUp(float distance, CVector3* point, CVector3* direction, CVector3* up);
    // 0x000c4908 CKFlaggedPath_ComputeRollUpVector_maybe: the up vector for the path direction: the roll angle (degrees)
    // interpolated between the pairs (beacon index, angle) around the distance, turned about the direction from the
    // horizontal up; a direction within 0.95 of vertical gives the z axis.
    void ComputeRollUpVector(float distance, const CVector3* direction, CVector3* up);

    IKSerializable* m_pPath;                   // +0x04 XXL2 m_pPath (CKSpline4L / CKLine in the files)
    uint32_t m_ui32NbOfBeacon;                 // +0x08 XXL2 m_ui32NbOfBeacon
    float m_fCursorPos;                        // +0x0c XXL2 m_fCursorPos
    uint32_t m_unk10;                          // +0x10 not loaded (XXL2 m_bInOrder _maybe)
    float* m_aBeaconList;                      // +0x14 XXL2 m_aBeaconList (one block with the starters)
    CTriggerStarter* m_aTriggerToCallList;     // +0x18 XXL2 m_aTriggerToCallList
    TVector<Pair, 1> m_vPairs;                 // +0x1c the constructor: null, capacity 1, 0 used
};
DOTD_ASSERT_SIZE(CKFlaggedPath, 0x28);
DOTD_ASSERT_OFFSET(CKFlaggedPath, m_pPath, 0x04);
DOTD_ASSERT_OFFSET(CKFlaggedPath, m_ui32NbOfBeacon, 0x08);
DOTD_ASSERT_OFFSET(CKFlaggedPath, m_fCursorPos, 0x0c);
DOTD_ASSERT_OFFSET(CKFlaggedPath, m_aBeaconList, 0x14);
DOTD_ASSERT_OFFSET(CKFlaggedPath, m_aTriggerToCallList, 0x18);
DOTD_ASSERT_OFFSET(CKFlaggedPath, m_vPairs, 0x1c);
