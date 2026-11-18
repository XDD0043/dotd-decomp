// Reconstructed original translation unit: 0x3ff9b8-0x4009b0 (GAME_TOC1, main_toc1), 20 functions, 18 live.
// Primary class: CKHkButterflyBridge  key 0xb42  category Hook  size 0x108  vtable 0xb25470
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x3ff9b8  CKHkButterflyBridge_Delete  (DOTD_DECLARE_FACTORIES)
//   [ ] 0x3ffa08  RegisterCKHkButterflyBridgeClass
//   [ ] 0x3ffa80  _GLOBAL__I_3ffa80
//   [x] 0x3ffa90  CKHkButterflyBridge_Load
//   [ ] 0x3ffb90  CKHkButterflyBridge_Save
//   [x] 0x3ffbb8  CKHkButterflyBridge_RecursiveRegistration  (the base's, then 1: inherited)
//   [x] 0x3ffbe0  CKHkButterflyBridge_Destroy  (the base's: inherited)
//   [x] 0x3ffc08  CKHkButterflyBridge_Destructor  (the header's destructor)
//   [ ] 0x3ffc38  CKHkButterflyBridge_Construct  [dead]
//   [ ] 0x3ffc70  CKHkButterflyBridge_Construct_2  [dead]
//   [x] 0x3ffca8  CKHkButterflyBridge_DeleteArray  (DOTD_DECLARE_FACTORIES)
//   [x] 0x3ffd50  CKHkButterflyBridge_SetWingsRetracted_maybe  (OnSnappedLowered)
//   [x] 0x3fff48  CKHkButterflyBridge_State3_RotateWingSegments_maybe  (StateNextSegmentUp)
//   [x] 0x400248  CKHkButterflyBridge_BaseDestructor  (the header's destructor)
//   [x] 0x400278  CKHkButterflyBridge_vf100  (IsBridgeGround)
//   [x] 0x400340  CKHkButterflyBridge_DeletingDestructor  (the header's destructor)
//   [x] 0x400388  CKHkButterflyBridge_StateRotateSegment_maybe  (StateNextSegmentDown)
//   [x] 0x4006a8  CKHkButterflyBridge_SetWingsDeployed_maybe  (OnSnappedRaised)
//   [x] 0x4008a0  CKHkButterflyBridge_CreateArray  (DOTD_DECLARE_FACTORIES)
//   [x] 0x400958  CKHkButterflyBridge_Create  (DOTD_DECLARE_FACTORIES)
//
//   [x] 0x9c0fb8  CKHkButterflyBridge_IsKindOfClass  [inline]  (CKHkButterflyBridge.h)
//   [x] 0x9c1018  CKHkButterflyBridge_GetClassType  [inline]  (DOTD_CLASS_KEY)
//   [x] 0x9c1020  CKHkButterflyBridge_GetClassID  [inline]  (DOTD_CLASS_KEY)
#include "k2000/hooks/CKHkButterflyBridge.h"

#include "k2000/dictionaries/CKSoundDictionaryID.h"
#include "k2000/io/IKFile.h"
#include "k2000/logic/physics/CDynamicGround.h"
#include "k2000/logic/sound/CKSound.h"
#include "k2000/scenegraph/CSGMovable.h"
#include "k2000/system/IKTime.h"
#include "crt/ppc_ops.h"

namespace {

const float kOne = 1.0f;          // TOC1 +0x47dc 0x3f800000
const float kHalfTurn = 180.0f;   // TOC1 +0x47e0 0x43340000
const float kFolded = 90.0f;      // TOC1 +0x47e4 0x42b40000
const float kFoldedB = -90.0f;    // TOC1 +0x47e8 0xc2b40000
const float kZero = 0.0f;         // TOC1 +0x47ec 0x00000000
const float kWingSoundSpeed = 0.9f;  // TOC1 +0x47f0 0x3f666666

CSGMovable* Wing(const CKHkButterflyBridge* b, uint32_t index) { return static_cast<CSGMovable*>(b->m_apExtraA[index]); }
CDynamicGround* WingGround(const CKHkButterflyBridge* b, uint32_t index) {
    return static_cast<CDynamicGround*>(b->m_apExtraB[index]);
}
CKSoundDictionaryID* Sounds(const CKHkButterflyBridge* b) {
    return static_cast<CKSoundDictionaryID*>(b->m_pSoundDictionary);
}

}  // namespace

void CKHkButterflyBridge::PoseWings(uint32_t segment, float angleA, float angleB) {
    const float yAxis[3] = {kZero, kOne, kZero};
    const float zAxis[3] = {kZero, kZero, kOne};
    Wing(this, segment * 2)->RotateKeepPosition(yAxis, kHalfTurn);  // 0x000d0c48
    Wing(this, segment * 2)->RotateInPlace(zAxis, angleA);          // 0x000d11b0
    Wing(this, segment * 2 + 1)->RotateKeepPosition(yAxis, kZero);
    Wing(this, segment * 2 + 1)->RotateInPlace(zAxis, angleB);
}

// 0x003ffa90 CKHkButterflyBridge_Load: the base's, then (level type 0) +0xfc a reference and +0x100 a word.
int32_t CKHkButterflyBridge::Load(IKFile* file, int32_t type) {
    CKHkBridgeBase::Load(file, type);  // 0x003fcd78
    if (type != 0) return 1;
    IKFile_ReadRef(file, &m_pUnk0fc);
    ReadF32LE(file, &m_fWingSpeed);
    return 1;
}

// 0x003ffd50 CKHkButterflyBridge_SetWingsRetracted_maybe (vt+0xf0, SnapToLowered): every segment's wings folded (90 /
// -90 degrees) and, unless the life sleeps (+0x0c bit 2), their grounds off. Nothing without the pair arrays (+0x24 0).
void CKHkButterflyBridge::OnSnappedLowered() {
    uint32_t count = m_ui8NbSegments;
    if (count == 0) return;
    for (uint32_t i = 0;; ++i) {
        if (m_ui32NbExtra != 0) {
            PoseWings(i, kFolded, kFoldedB);
            if ((m_bitArray & 4u) == 0) {
                WingGround(this, i * 2)->SetActive(0);  // 0x001a6b70
                WingGround(this, i * 2 + 1)->SetActive(0);
            }
            count = m_ui8NbSegments;
        }
        if (count <= i + 1) break;  // cmplw / ble
    }
}

// 0x004006a8 CKHkButterflyBridge_SetWingsDeployed_maybe (vt+0xf4, SnapToRaised): every segment's wings open (0 / 0
// degrees, fmr of the zero: no negative zero) and, unless the life sleeps, their grounds on.
void CKHkButterflyBridge::OnSnappedRaised() {
    uint32_t count = m_ui8NbSegments;
    if (count == 0) return;
    for (uint32_t i = 0;; ++i) {
        if (m_ui32NbExtra != 0) {
            PoseWings(i, kZero, kZero);
            if ((m_bitArray & 4u) == 0) {
                WingGround(this, i * 2)->SetActive(1);
                WingGround(this, i * 2 + 1)->SetActive(1);
            }
            count = m_ui8NbSegments;
        }
        if (count <= i + 1) break;
    }
}

// 0x003fff48 CKHkButterflyBridge_State3_RotateWingSegments_maybe (state 3, the next segment up): entering, the wings
// start folded (90), sound 0 plays at speed 0.9 and the segment's wing grounds go on; every frame the angle falls by
// +0x100 x dt to 0; once open the next segment rises (1), or the bridge blocks (8) when +0xfb is set, or the end
// segment follows (4) after the last one.
uint8_t CKHkButterflyBridge::StateNextSegmentUp(IKTime* clock, int32_t phase, uint8_t /*other*/) {
    if (phase == 0) {
        if (m_ui32NbExtra == 0) {
            m_fWingAngle = 0.0f;  // stw 0
        } else {
            const float angle = m_fWingAngle - m_fWingSpeed * clock->m_afDeltaTime[0];  // fmuls, fsubs
            m_fWingAngle = angle;
            if (angle < kZero) m_fWingAngle = kZero;  // fcmpu / blt
            const float current = m_fWingAngle;
            PoseWings(m_ui8CurrentSegment, current, -m_fWingAngle);  // fneg of the reloaded angle
            if (m_fWingAngle != kZero) return 3;
        }
        const uint8_t next = static_cast<uint8_t>(m_ui8CurrentSegment + 1);
        m_ui8CurrentSegment = next;
        if (m_ui8NbSegments <= next) return 4;  // cmplw / ble
        // srawi / rlwinm / rlwinm / addi: (+0xfb - 1) >> 31 rotated: 1 when +0xfb is 0, else 8.
        return m_ui8Unk0fb == 0 ? 1 : 8;
    }
    if (phase != 1) return 3;
    m_fWingAngle = kFolded;
    if (Sounds(this)->GetSound(0) != nullptr) Sounds(this)->GetSound(0)->SetSpeed(kWingSoundSpeed);  // 0x00110e98
    if (Sounds(this)->GetSound(0) != nullptr) CKSound_Play(kZero, Sounds(this)->GetSound(0));         // 0x00111230
    WingGround(this, m_ui8CurrentSegment * 2u)->SetActive(1);
    WingGround(this, m_ui8CurrentSegment * 2u + 1)->SetActive(1);
    return 3;
}

// 0x00400388 CKHkButterflyBridge_StateRotateSegment_maybe (state 6, the next segment down): the heroes walked off first
// (every phase); entering, the wings start open (0) and sound 0 plays at speed 0.9; every frame the angle rises by
// +0x100 x dt (fused) to 90, then the segment lowers (7); leaving, the segment's wing grounds go off.
uint8_t CKHkButterflyBridge::StateNextSegmentDown(IKTime* clock, int32_t phase, uint8_t /*other*/) {
    ReleaseHeroesOffBridge(clock);  // 0x003fd760
    if (phase == 1) {
        m_fWingAngle = 0.0f;  // stw 0
        if (Sounds(this)->GetSound(0) != nullptr) Sounds(this)->GetSound(0)->SetSpeed(kWingSoundSpeed);
        if (Sounds(this)->GetSound(0) != nullptr) CKSound_Play(0.0f, Sounds(this)->GetSound(0));  // the stored 0 word
        return m_ui32NbExtra == 0 ? 6 : 7;
    }
    if (phase == 2) {
        WingGround(this, m_ui8CurrentSegment * 2u)->SetActive(0);
        WingGround(this, m_ui8CurrentSegment * 2u + 1)->SetActive(0);
        return 6;
    }
    if (phase != 0) return 6;
    if (m_ui32NbExtra == 0) return 7;
    uint8_t next = 6;
    const float angle = ppc::fmadds(m_fWingSpeed, clock->m_afDeltaTime[0], m_fWingAngle);
    m_fWingAngle = angle;
    if (angle >= kFolded) {  // cror gt|eq, bne (NaN: keeps turning)
        next = 7;
        m_fWingAngle = kFolded;
    }
    const float current = m_fWingAngle;
    PoseWings(m_ui8CurrentSegment, current, -m_fWingAngle);
    return next;
}

// 0x00400278 CKHkButterflyBridge_vf100: whether `ground` is one of the segments' grounds A (+0x90) or, with the pair
// arrays, one of the wing grounds (+0x94, two per segment).
uint8_t CKHkButterflyBridge::IsBridgeGround(IKSerializable* ground) {
    const uint32_t count = m_ui8NbSegments;
    if (count == 0) return 0;
    if (static_cast<IKSerializable*>(m_apGroundsA[0]) == ground) return 1;
    if (m_ui32NbExtra == 0) {
        for (uint32_t i = 1; i < count; ++i) {
            if (static_cast<IKSerializable*>(m_apGroundsA[i]) == ground) return 1;
        }
        return 0;
    }
    for (uint32_t i = 0;; ++i) {
        if (m_apExtraB[i * 2] == ground) return 1;
        if (m_apExtraB[i * 2 + 1] == ground) return 1;
        if (i + 1 >= count) return 0;  // bdz
        if (static_cast<IKSerializable*>(m_apGroundsA[i + 1]) == ground) return 1;
    }
}
