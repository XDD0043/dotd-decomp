// Reconstructed original translation unit: 0x4009b0-0x401850 (GAME_TOC1, main_toc1), 22 functions, 19 live.
// Primary class: CKHkFoldawayBridge  key 0x4042  category Hook  size 0x11c  vtable 0xb25580
// Other owners: CKCrumblyZoneCpnt (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x4009b0  CKHkFoldawayBridge_Delete  (DOTD_DECLARE_FACTORIES)
//   [ ] 0x400a00  RegisterCKHkFoldawayBridgeClass
//   [ ] 0x400a78  _GLOBAL__I_400a78
//   [ ] 0x400a88  CKHkFoldawayBridge_Save
//   [x] 0x400ab0  CKHkFoldawayBridge_RecursiveRegistration  (the base's, then 1: inherited)
//   [x] 0x400ad8  CKHkFoldawayBridge_Destroy  (the base's: inherited)
//   [x] 0x400b00  CKHkFoldawayBridge_DeletingDestructor  (the header's destructor)
//   [ ] 0x400b48  CKHkFoldawayBridge_Construct  [dead]
//   [ ] 0x400ba0  CKHkFoldawayBridge_Construct_2  [dead]
//   [x] 0x400bf8  CKHkFoldawayBridge_DeleteArray  (DOTD_DECLARE_FACTORIES)
//   [x] 0x400c98  CKHkFoldawayBridge_Destructor  (the header's destructor)
//   [x] 0x400cc8  CKHkFoldawayBridge_BaseDestructor  (the header's destructor)
//   [x] 0x400cf8  CKHkFoldawayBridge_StateMoveSegment_maybe  (StateNextSegmentDown)
//   [x] 0x400f88  CKHkFoldawayBridge_vf100  (IsBridgeGround)
//   [x] 0x401028  CKHkFoldawayBridge_SnapAllSegmentsUnfolded_maybe  (OnSnappedRaised)
//   [x] 0x401120  CKHkFoldawayBridge_SnapAllSegmentsFolded_maybe  (OnSnappedLowered)
//   [x] 0x401218  CKHkFoldawayBridge_State3_UnfoldSegment_maybe  (StateNextSegmentUp)
//   [x] 0x4014e8  CKHkFoldawayBridge_CreateArray  (DOTD_DECLARE_FACTORIES)
//   [x] 0x4015b8  CKHkFoldawayBridge_Create  (DOTD_DECLARE_FACTORIES; the header's constructor)
//   [x] 0x401620  CKHkFoldawayBridge_Load
//   [x] 0x4017f8  CKCrumblyZoneCpnt_Delete  (DOTD_DECLARE_FACTORIES in CKCrumblyZoneCpnt.h)
//   [ ] 0x401848  FUN_00401848  [dead]
//
//   [x] 0x9c1028  CKHkFoldawayBridge_IsKindOfClass  [inline]  (CKHkFoldawayBridge.h)
//   [x] 0x9c1088  CKHkFoldawayBridge_GetClassType  [inline]  (DOTD_CLASS_KEY)
//   [x] 0x9c1090  CKHkFoldawayBridge_GetClassID  [inline]  (DOTD_CLASS_KEY)
#include "k2000/hooks/CKHkFoldawayBridge.h"

#include <cmath>

#include "Renderware/rwcore/RwCamera.h"
#include "crt/ppc_ops.h"
#include "k2000/dictionaries/CKSoundDictionaryID.h"
#include "k2000/io/IKFile.h"
#include "k2000/logic/physics/CDynamicGround.h"
#include "k2000/logic/sound/CKSound.h"
#include "k2000/scenegraph/CSGMovable.h"
#include "k2000/system/IKTime.h"

namespace {

const float kZero = 0.0f;  // TOC1 +0x482c 0x00000000

CSGMovable* Segment(const CKHkFoldawayBridge* b, uint32_t index) {
    return static_cast<CSGMovable*>(b->m_apExtraA[index]);
}
CDynamicGround* SegmentGround(const CKHkFoldawayBridge* b, uint32_t index) {
    return static_cast<CDynamicGround*>(b->m_apExtraB[index]);
}

// A sliding node's modelling position set to (0, y, 0), its matrix no longer the identity (flags bit 17 cleared), the
// frame marked dirty (RwFrame_MarkDirty 0x10698), as the base's segment helper.
void SetSlidePosition(CSGMovable* segment, float y) {
    RwFrame* frame = segment->m_pRwFrame;
    frame->modelling.pos.y = y;
    frame->modelling.pos.z = 0.0f;
    frame->modelling.pos.x = 0.0f;
    frame->modelling.flags &= 0xfffdffffu;
    RwFrame_MarkDirty(segment->m_pRwFrame);
}

}  // namespace

// The spring inlined in 0x400cf8 / 0x401218: the speed driven by stiffness x (target - current) - damping x speed
// (fmuls, fmsubs, fmadds), the current by speed x dt (fmadds), kept within +0x10c of the target; at rest (|speed| and
// |current - target| both within +0x108) it sits on the target. With the current on the target and no speed nothing
// is stored.
void CKHkFoldawayBridge::StepSegmentSpring(float dt) {
    const float target = m_fSpringTarget;
    float current = m_fSpringCurrent;
    const float offset = target - current;
    float speed = 0.0f;
    if (offset == kZero) {  // fcmpu / beq (NaN: the driven branch)
        const float s = m_fSpringSpeed;
        if (s == kZero) return;
        const float drag = s * -m_fDamping;  // fneg, fmuls
        speed = ppc::fmadds(drag, dt, s);
        current = ppc::fmadds(dt, speed, current);
    } else {
        const float s = m_fSpringSpeed;
        const float force = ppc::fmsubs(m_fStiffness, offset, m_fDamping * s);
        speed = ppc::fmadds(force, dt, s);
        current = ppc::fmadds(dt, speed, current);
    }
    const float lag = target - current;
    if (m_fMaxLag <= lag) {  // cror lt|eq, bne
        current = target - m_fMaxLag;
    } else if (-m_fMaxLag >= lag) {  // cror gt|eq, bne
        current = m_fMaxLag + target;
    }
    if (m_fRestThreshold >= std::fabs(speed) && m_fRestThreshold >= std::fabs(current - m_fSpringTarget)) {
        m_fSpringSpeed = kZero;
        m_fSpringCurrent = m_fSpringTarget;
        return;
    }
    m_fSpringSpeed = speed;
    m_fSpringCurrent = current;
}

// 0x00401620 CKHkFoldawayBridge_Load: the base's, then (level type 0) +0x100, +0x104, +0x108, +0x10c and +0xfc.
int32_t CKHkFoldawayBridge::Load(IKFile* file, int32_t type) {
    CKHkBridgeBase::Load(file, type);  // 0x003fcd78
    if (type != 0) return 1;
    ReadF32LE(file, &m_fStiffness);
    ReadF32LE(file, &m_fDamping);
    ReadF32LE(file, &m_fRestThreshold);
    ReadF32LE(file, &m_fMaxLag);
    ReadF32LE(file, &m_fUnfolded);
    return 1;
}

// 0x00401120 CKHkFoldawayBridge_SnapAllSegmentsFolded_maybe (vt+0xf0, SnapToLowered): every segment's node at y 0 and,
// unless the life sleeps (+0x0c bit 2), its ground off.
void CKHkFoldawayBridge::OnSnappedLowered() {
    if (m_ui8NbSegments == 0) return;
    for (uint32_t i = 0;; ++i) {
        SetSlidePosition(Segment(this, i), 0.0f);  // three stw 0
        if ((m_bitArray & 4u) == 0) SegmentGround(this, i)->SetActive(0);  // 0x001a6b70
        if (m_ui8NbSegments <= i + 1) break;  // cmplw / ble
    }
}

// 0x00401028 CKHkFoldawayBridge_SnapAllSegmentsUnfolded_maybe (vt+0xf4, SnapToRaised): every segment's node at y +0xfc
// and, unless the life sleeps, its ground on.
void CKHkFoldawayBridge::OnSnappedRaised() {
    if (m_ui8NbSegments == 0) return;
    for (uint32_t i = 0;; ++i) {
        SetSlidePosition(Segment(this, i), m_fUnfolded);
        if ((m_bitArray & 4u) == 0) SegmentGround(this, i)->SetActive(1);
        if (m_ui8NbSegments <= i + 1) break;
    }
}

// 0x00401218 CKHkFoldawayBridge_State3_UnfoldSegment_maybe (state 3, the next segment up): entering, the spring runs
// from 0 to +0xfc, the segment's ground goes on and sound 0 plays; every frame the spring steps and places the node;
// once it no longer moves the current is set to +0xfc and the next segment rises (1), or the bridge blocks (8) when
// +0xfb is set, or the end segment follows (4) after the last one.
uint8_t CKHkFoldawayBridge::StateNextSegmentUp(IKTime* clock, int32_t phase, uint8_t /*other*/) {
    if (phase == 0) {
        const float before = m_fSpringCurrent;
        StepSegmentSpring(clock->m_afDeltaTime[0]);
        SetSlidePosition(Segment(this, m_ui8CurrentSegment), m_fSpringCurrent);
        if (m_fSpringCurrent != before) return 3;  // fcmpu / bne (NaN: still moving)
        m_fSpringCurrent = m_fUnfolded;
        const uint8_t next = static_cast<uint8_t>(m_ui8CurrentSegment + 1);
        m_ui8CurrentSegment = next;
        if (m_ui8NbSegments <= next) return 4;  // cmplw / ble
        return m_ui8Unk0fb == 0 ? 1 : 8;  // srawi / rlwinm / rlwinm / addi
    }
    if (phase != 1) return 3;
    m_fSpringCurrent = m_fSpringTarget;
    m_fSpringSpeed = kZero;
    m_fSpringTarget = m_fUnfolded;
    m_fSpringCurrent = kZero;
    SegmentGround(this, m_ui8CurrentSegment)->SetActive(1);
    CKSoundDictionaryID* sounds = static_cast<CKSoundDictionaryID*>(m_pSoundDictionary);
    if (sounds->GetSound(0) == nullptr) return 3;
    CKSound_Play(kZero, sounds->GetSound(0));  // 0x00111230
    return 3;
}

// 0x00400cf8 CKHkFoldawayBridge_StateMoveSegment_maybe (state 6, the next segment down): the heroes walked off first
// (every phase); entering, the spring runs from +0xfc to 0 and the segment's ground goes on (sic); every frame the
// spring steps and places the node; once it no longer moves the current is set to +0xfc and the segment lowers (7).
uint8_t CKHkFoldawayBridge::StateNextSegmentDown(IKTime* clock, int32_t phase, uint8_t /*other*/) {
    ReleaseHeroesOffBridge(clock);  // 0x003fd760
    if (phase == 0) {
        const float before = m_fSpringCurrent;
        StepSegmentSpring(clock->m_afDeltaTime[0]);
        SetSlidePosition(Segment(this, m_ui8CurrentSegment), m_fSpringCurrent);
        if (m_fSpringCurrent != before) return 6;
        m_fSpringCurrent = m_fUnfolded;
        return 7;
    }
    if (phase != 1) return 6;
    m_fSpringCurrent = m_fSpringTarget;
    m_fSpringTarget = 0.0f;  // stw 0
    m_fSpringSpeed = 0.0f;   // stw 0
    m_fSpringCurrent = m_fUnfolded;
    // BUG(original)?: the ground of a segment about to fold is switched on (state 3 does the same entering).
    SegmentGround(this, m_ui8CurrentSegment)->SetActive(1);
    return 6;
}

// 0x00400f88 CKHkFoldawayBridge_vf100: whether `ground` is one of the segments' grounds A (+0x90) or their sliding
// grounds (+0x94).
uint8_t CKHkFoldawayBridge::IsBridgeGround(IKSerializable* ground) {
    const uint32_t count = m_ui8NbSegments;
    if (count == 0) return 0;
    if (static_cast<IKSerializable*>(m_apGroundsA[0]) == ground) return 1;
    if (m_apExtraB[0] == ground) return 1;
    for (uint32_t i = 1; i < count; ++i) {
        if (static_cast<IKSerializable*>(m_apGroundsA[i]) == ground) return 1;
        if (m_apExtraB[i] == ground) return 1;
    }
    return 0;
}
