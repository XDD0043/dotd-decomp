// CKHkTrackerManager.h - (key 0xf42, vtable 0xb26f78, size 0x108). Original unit: CKHkTrackerManager.cpp.
// No XXL2 class. Field names are placeholders (C2.1 ports the constructor and Load only).
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/misc/CKHkActorBase.h"
#include "k2000/util/TVector.h"

class CKHkTrackerManager : public CKHkActorBase {
public:
    DOTD_CLASS_KEY(kCategoryHook, 0x3d)
    int32_t IsKindOfClass(uint32_t key) override {  // vt+0x08 0x9c3dd8
        return key == 0xf42 || key == 0xd82 || key == 0x2 || key == 0x2fe || key == 0x3fe || key == 0xc;
    }
    DOTD_DECLARE_FACTORIES(CKHkTrackerManager)

    struct RefValue {               // 0x8
        IKSerializable* m_pRef;     // +0x0 reference
        uint32_t m_unk4;            // +0x4
    };
    // A track's filter (ApplyTrackFilterByType 0x453f68): m_unk0 the type (0 distance to the first controlled hero, 1 to
    // the hero, 2 to the camera, 3 the camera frustum / view, 5 to the reference's node), m_unk4 the filter's mode, m_unk8
    // its value (a distance), m_pRef the reference of type 5.
    struct ValuesRef {              // 0x10
        uint32_t m_unk0;            // +0x0
        uint32_t m_unk4;            // +0x4
        float m_unk8;               // +0x8
        IKSerializable* m_pRef;     // +0xc reference
    };
    // A track point (LVL010: a CKMarkerBeacon) with the dragon assigned to it (-1 none; OnActivate) and a flag OnActivate
    // copies from the loaded +0x9.
    struct RefByte {                // 0xc (only +0x0 and +0x9 are written by the Load)
        IKSerializable* m_pRef;     // +0x0 reference
        int32_t m_i32Dragon;        // +0x4 runtime
        uint8_t m_ui8Taken;         // +0x8 runtime (OnActivate: +0x9)
        uint8_t m_unk9;             // +0x9
        uint8_t m_padA[2];
    };
    // A track (six at +0x3c): its points (RefValue: the point and a word whose bit `dragon` allows that dragon, bit 3 /
    // bit 4 choose the hero's message), +0x0c a flag, +0x10 the time a dragon keeps it, its filters.
    struct Slot {                   // 0x20, six of them at +0x3c
        TVector<RefValue, 1> m_vRefValues;   // +0x00
        uint8_t m_unkC;                      // +0x0c
        uint8_t m_padD[3];
        float m_unk10;                       // +0x10
        TVector<ValuesRef, 1> m_vValuesRefs; // +0x14
    };
    // The candidate list node of PickTrackForHero (a node of the global free-list pool 0x00ceaa20 in the original): the
    // track point's index (+0x0), the point's index in the track (+0x4), the next node (+0x8).
    struct Candidate {
        int32_t m_i32Point;
        int32_t m_i32Index;
        Candidate* m_pNext;
    };

    // 0x00453dd8 CKHkTrackerManager_Create (inlined constructor, the same as 0x451c80
    // CKHkTrackerManager_Construct): every vector empty with capacity 1.
    CKHkTrackerManager() {
        for (Slot& slot : m_aSlots) {
            slot.m_vRefValues.m_pBlock = nullptr;
            slot.m_vRefValues.m_ui32NbUsedElt = 0;
            slot.m_vRefValues.m_ui32NbElt = 1;
            slot.m_vValuesRefs.m_pBlock = nullptr;
            slot.m_vValuesRefs.m_ui32NbUsedElt = 0;
            slot.m_vValuesRefs.m_ui32NbElt = 1;
        }
        m_vRefBytes.m_ui32NbElt = 1;
        m_vRefBytes.m_ui32NbUsedElt = 0;
        m_vRefBytes.m_pBlock = nullptr;
    }
    // 0x00453968 CKHkTrackerManager_Destructor: the point vector (+0xfc) freed and emptied, then each track's two vectors
    // (last track first: its filters, then its points; FreeBuffers emptied them already at a level exit), then the actor
    // base's (vtable only).
    ~CKHkTrackerManager() override;
    // vt+0xc0 0x00451790 CKHkTrackerManager_FreeBuffers_maybe (the actor base's Destroy calls it): the two reference
    // tables freed (not cleared), then each track's vectors freed and emptied, last track first (points, then filters).
    void VfC0() override;

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x004552f0 CKHkTrackerManager_Load
    // vt+0x54 0x00451b68 CKHkTrackerManager_Restart: CKHkActorBase_d82_maybe_Stop 0x3f6e50 (empty) only.
    void Restart() override {}
    void SetDefaultState(int32_t flag) override;  // vt+0x38 0x00451b20 CKHkTrackerManager_SetDefaultState
    void Start() override;                        // vt+0x50 0x00451bb8 CKHkTrackerManager_Start
    void VfA0() override;                         // vt+0xa0 0x00453278 CKHkTrackerManager_OnActivate
    void Update(IKTime* clock) override;          // vt+0x7c 0x00454888 CKHkTrackerManager_Update
    // vt+0x40 0x00451a58 CKHkTrackerManager_GetInfo: the actor base's answer (KStub_Return1 0x3f7140) folded: 2 stays 2,
    // 0 stays 0, anything else is 1 (no info of its own).
    int32_t GetInfo(IKInfo* info, int32_t request) override;
    // vt+0x1c 0x00453378 CKHkTrackerManager_MessageProc: the actor messages, then 0x996 (enabled: +0x0c bit 9 set), 0x997
    // (disabled: an enabled manager first sends every companion that fails PassesTrackerAssignFlagChecks off its track,
    // message 0xc3b, track 6, its point freed), and any 0x9xx message whose low byte is 0xaa + a track point index: that
    // point's taken flag (+0x8) = the data's first byte, every dragon's track 6.
    int32_t MessageProc(uint16_t message, void* data) override;
    // vt+0xc8 0x004526e0 CKHkTrackerManager_vfC8 (the state preset): 0 enables the manager (+0x0c bit 9 set), else
    // disables it.
    void ApplyStatePreset(int32_t state) override;
    // 0x004544b8 CKHkTrackerManager_AssignHeroToTrack_maybe
    void AssignHeroToTrack(uint32_t track, uint32_t dragon);
    // 0x00454178 CKHkTrackerManager_PickTrackForHero_maybe: {point, index} or {-1, -1}.
    void PickTrackForHero(int32_t out[2], uint32_t track, uint32_t dragon);
    // 0x00453f68 CKHkTrackerManager_ApplyTrackFilterByType_maybe
    void ApplyTrackFilterByType(const ValuesRef* filter, Candidate** list, uint32_t dragon);
    // 0x00452c40 CKHkTrackerManager_FilterCandidatesByDistance_maybe
    void FilterCandidatesByDistance(float limit, const float* position, uint32_t mode, Candidate** list);
    // 0x00452720 CKHkTrackerManager_FilterCandidatesByCameraFrustum_maybe
    void FilterCandidatesByCameraFrustum(uint32_t mode, Candidate** list);
    // The release the original inlines everywhere: from the last track point down, the first one assigned to `dragon` is
    // freed (-1).
    void ReleasePointOf(uint32_t dragon);

    uint8_t m_ui8InsideMask;             // +0x20 runtime: bit `dragon` set while a controlled hero is in a track zone
    uint8_t m_aui8Track[3];              // +0x21 runtime: the track of each dragon (6 none)
    float m_afTrackTime[3];              // +0x24 runtime: the time each dragon has had its track
    uint8_t m_ui8NbRows;                 // +0x30 the row count of +0x34 and +0x38
    uint8_t m_ui8NbCols34;               // +0x31
    uint8_t m_ui8NbCols38;               // +0x32
    uint8_t m_pad33;
    IKSerializable** m_apRefs34;         // +0x34 rows * cols34 references
    IKSerializable** m_apRefs38;         // +0x38 rows * cols38 references
    Slot m_aSlots[6];                    // +0x3c
    TVector<RefByte, 1> m_vRefBytes;     // +0xfc
};
DOTD_ASSERT_SIZE(CKHkTrackerManager, 0x108);
DOTD_ASSERT_SIZE(CKHkTrackerManager::Slot, 0x20);
DOTD_ASSERT_SIZE(CKHkTrackerManager::RefByte, 0xc);
DOTD_ASSERT_SIZE(CKHkTrackerManager::ValuesRef, 0x10);
DOTD_ASSERT_OFFSET(CKHkTrackerManager::RefByte, m_unk9, 0x9);
DOTD_ASSERT_OFFSET(CKHkTrackerManager, m_ui8NbRows, 0x30);
DOTD_ASSERT_OFFSET(CKHkTrackerManager, m_apRefs34, 0x34);
DOTD_ASSERT_OFFSET(CKHkTrackerManager, m_apRefs38, 0x38);
DOTD_ASSERT_OFFSET(CKHkTrackerManager, m_aSlots, 0x3c);
DOTD_ASSERT_OFFSET(CKHkTrackerManager, m_vRefBytes, 0xfc);
