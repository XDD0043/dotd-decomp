// CKCameraSector.h - a camera sector (the zone that picks the camera) (key 0x20c, vtable 0xb130f8, size 0x58). Original unit: CKCameraSector.cpp.
// XXL2: m_AABB, m_vpCamera, m_fTransitionTime, m_ui8TransitionMode, m_Flags and two rule bytes; DotD
// reads them in another order and adds references and trigger starters.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/core/IKSerializable.h"
#include "k2000/services/CTriggerStarter.h"

class IKCamera;
class IKFile;

class CKCameraSector : public IKSerializable {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x8)
    int32_t IsKindOfClass(uint32_t key) override { return key == 0x20c || key == 0xc; }  // vt+0x08 0x9917e0
    DOTD_DECLARE_FACTORIES(CKCameraSector)

    CKCameraSector();  // 0x00129308 CKCameraSector_Create (the constructor inlined)
    ~CKCameraSector() override;  // 0x00992090 CKCameraSector_Destructor (0x992010 the deleting form)

    // vt+0x38 0x00128e68 CKCameraSector_SetDefaultState: with flag 0, "switched on" (m_unk2d bit 1) takes the
    // initial state (bit 0).
    void SetDefaultState(int32_t flag) override;
    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x00129da8 CKCameraSector_Load
    // vt+0x24 0x00129178 CKCameraSector_RecursiveRegistration: type 0 registers it with the saving manager and the
    // reference +0x28 (when set) with type 0 (the starters' KStub_Return1_2361b0 register nothing).
    void RecursiveRegistration(int32_t type) override;
    // vt+0x3c 0x001293d8 CKCameraSector_SetGameState: game state 0 switches it on (m_unk2d bit 1), 1 off; returns 1.
    int32_t SetGameState(const SApplyGameState* state) override;
    // vt+0x1c 0x00129670 CKCameraSector_MessageProc: 0x700 switches it on (m_unk2d bit 1), 0x701 off (0 for both), else 1.
    int32_t MessageProc(uint16_t message, void* data) override;
    // vt+0x10 0x00129748 CKCameraSector_Destroy: the reference +0x28 destroyed (vt+0x10) and cleared, the camera list freed.
    void Destroy() override;

    // 0x00129438 CKCameraSector_IsEnabledForFocusedHero_maybe: switched on (m_unk2d bit 1) and, when it names a
    // level sector (+0x40, loaded as a float: the bits are the sector number), that sector is the level's current one.
    bool IsEnabledForFocusedHero() const;
    // 0x00129550 CKCameraSector_ContainsPoint_maybe: the box (m_AABB: max x, y, z then min x, y, z) narrowed by the
    // shape in m_unk2d bits 5-6 (0 box, 1 cylinder over x/z, 2 sphere over the x extent).
    bool ContainsPoint(const float* point) const;
    // 0x00128e90 CKCameraSector_TestCandidateByMode_maybe: the selection mode (m_unk2f): 0 every camera passes, 1 / 2
    // the nearest / farthest to `focusPos`, 3 / 4 to `cameraPos`; `best` is the distance so far (-1 = none), updated
    // when the camera wins. The distance is over x/z unless m_unk2d bit 2.
    bool TestCandidateByMode(const IKCamera* camera, const float* focusPos, const float* cameraPos, float* best) const;
    // 0x001297e8 CKCameraSector_ScoreCandidateAlignment_maybe: the dot product of the camera's view direction with the
    // current one (`direction3d`, or `direction2d` over x/z) against the alignment threshold of m_unk2e (modes 1-10);
    // `best` is the best score so far, updated when the camera wins.
    bool ScoreCandidateAlignment(const IKCamera* camera, const float* direction3d, const float* direction2d,
                                 float* best) const;
    // 0x00129aa8 CKCameraSector_FindValidCamera_maybe: starts each camera that is not the current one (with the
    // scripted start position while the service holds one) and picks the one the selection and alignment modes allow;
    // null when the sector has no camera or none passes.
    IKCamera* FindValidCamera();
    // 0x00129358 CKCameraSector_FlushTriggerSignals_maybe: leaving the sector. With bit 4 of m_unk2d or a transition time above
    // 0 the leave signals (+0x44) are queued and bit 1 of m_unk2d cleared.
    void FlushTriggerSignals();
    // 0x00129140 CKCameraSector_QueueActivateSignals_maybe: entering the sector, the signals +0x4c queued.
    void QueueActivateSignals();

    float m_AABB[6];              // +0x04 XXL2 CBBox; one 0x18 read, swapped
    IKSerializable** m_vpCamera;  // +0x1c XXL2 VectorOfpCamera (Mem_AllocAligned16); 0
    uint32_t m_vpCameraCapacity;  // +0x20 5 in the constructor
    uint32_t m_vpCameraCount;     // +0x24 0
    IKSerializable* m_unk28;      // +0x28
    uint8_t m_unk2c;              // +0x2c
    uint8_t m_unk2d;              // +0x2d read first
    uint8_t m_unk2e;              // +0x2e
    uint8_t m_unk2f;              // +0x2f
    float m_fTransitionTime;      // +0x30 _maybe (1.0 in LVL010)
    uint32_t m_unk34;             // +0x34
    uint8_t m_unk38;              // +0x38
    uint8_t m_pad39[3];
    uint32_t m_unk3c;             // +0x3c
    float m_unk40;                // +0x40
    CTriggerStarter m_tsUnk44;    // +0x44
    CTriggerStarter m_tsUnk4c;    // +0x4c
    float m_unk54;                // +0x54 -1.0 in LVL010
};
DOTD_ASSERT_SIZE(CKCameraSector, 0x58);
DOTD_ASSERT_OFFSET(CKCameraSector, m_AABB, +0x04);
DOTD_ASSERT_OFFSET(CKCameraSector, m_vpCamera, +0x1c);
DOTD_ASSERT_OFFSET(CKCameraSector, m_vpCameraCapacity, +0x20);
DOTD_ASSERT_OFFSET(CKCameraSector, m_vpCameraCount, +0x24);
DOTD_ASSERT_OFFSET(CKCameraSector, m_unk28, +0x28);
DOTD_ASSERT_OFFSET(CKCameraSector, m_unk2c, +0x2c);
DOTD_ASSERT_OFFSET(CKCameraSector, m_unk2d, +0x2d);
DOTD_ASSERT_OFFSET(CKCameraSector, m_unk2e, +0x2e);
DOTD_ASSERT_OFFSET(CKCameraSector, m_unk2f, +0x2f);
DOTD_ASSERT_OFFSET(CKCameraSector, m_fTransitionTime, +0x30);
DOTD_ASSERT_OFFSET(CKCameraSector, m_unk34, +0x34);
DOTD_ASSERT_OFFSET(CKCameraSector, m_unk38, +0x38);
DOTD_ASSERT_OFFSET(CKCameraSector, m_unk3c, +0x3c);
DOTD_ASSERT_OFFSET(CKCameraSector, m_unk40, +0x40);
DOTD_ASSERT_OFFSET(CKCameraSector, m_tsUnk44, +0x44);
DOTD_ASSERT_OFFSET(CKCameraSector, m_tsUnk4c, +0x4c);
DOTD_ASSERT_OFFSET(CKCameraSector, m_unk54, +0x54);
