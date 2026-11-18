// Reconstructed original translation unit: 0x17d0f0-0x17e7f0 (GAME_TOC1, main_toc1), 14 functions, 14 live.
// Primary class: CKLightningCinematicBloc  key 0x6c8  category CinematicNode  size 0xa0  vtable 0xb1b448
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x17d0f0  CKLightningCinematicBloc_Delete  (DOTD_DECLARE_FACTORIES)
//   [ ] 0x17d140  RegisterCKLightningCinematicBlocClass
//   [ ] 0x17d1b8  _GLOBAL__I_17d1b8
//   [x] 0x17d1c8  CKLightningCinematicBloc_RecursiveRegistration  (the base's, then 1: inherited)
//   [x] 0x17d1f0  CKLightningCinematicBloc_DeleteArray  (DOTD_DECLARE_FACTORIES)
//   [x] 0x17d2a0  CKLightningCinematicBloc_CreateArray  (DOTD_DECLARE_FACTORIES; the constructor)
//   [x] 0x17d3b0  CKLightningCinematicBloc_Stop
//   [x] 0x17d5e0  CKLightningCinematicBloc_Load
//   [ ] 0x17d7b0  CKLightningCinematicBloc_Save
//   [x] 0x17da88  CKLightningCinematicBloc_Destroy  (CKLightningCinematicBloc.h, empty)
//   [x] 0x17da90  CKLightningCinematicBloc_Start
//   [x] 0x17e1a0  CKLightningCinematicBloc_Create  (DOTD_DECLARE_FACTORIES; the constructor)
//   [x] 0x17e238  CKLightningCinematicBloc_Complete
//   [x] 0x17e410  CKLightningCinematicBloc_Update
//
//   [x] 0x9a9840  CKLightningCinematicBloc_IsKindOfClass  [inline]  (DOTD_BLOC_IS_KIND_OF)
//   [x] 0x9a9878  CKLightningCinematicBloc_GetClassType  [inline]  (DOTD_CLASS_KEY)
//   [x] 0x9a9880  CKLightningCinematicBloc_GetClassID  [inline]  (DOTD_CLASS_KEY)
//   [x] 0x9a9888  CKLightningCinematicBloc_PreActivate  [inline]  (empty: the default)
//   [x] 0x9a9890  CKLightningCinematicBloc_Abort  [inline]  (CKLightningCinematicBloc.h)
//   [x] 0x9a98a0  CKLightningCinematicBloc_Destructor  [inline]  (the header's destructor)
//   [x] 0x9a9910  CKLightningCinematicBloc_DeletingDestructor  [inline]  (the header's destructor)
#include "k2000/cinematics/CKLightningCinematicBloc.h"

#include "k2000/fx/IKFx.h"
#include "k2000/io/IKFile.h"
#include "k2000/misc/Engine.h"
#include "k2000/services/CKSrvBeacon.h"
#include "k2000/services/CKSrvFx.h"
#include "k2000/system/IKTime.h"

namespace {

const float kTenth = 0.1f;  // TOC1 -0x30ec 0x3dcccccd
const float kZero = 0.0f;   // TOC1 -0x30c0 0x00000000

// The 8-byte read of a beacon accessor, each half-word swapped after it.
void ReadAccessor(IKFile* file, uint16_t* accessor) {
    file->Read(accessor, 8);
    for (int i = 0; i < 4; ++i) {
        const uint8_t* b = reinterpret_cast<const uint8_t*>(accessor + i);
        accessor[i] = static_cast<uint16_t>(b[0] | (b[1] << 8));
    }
}

// A beacon's three tenths. BUG(original): a sector without klusters (or an id without a set) is read from the low
// addresses (0, 2, 4, or the set fields at 0x8 / 0x10); zeros here, as CKTeleportCinematicBloc does.
const int16_t* BeaconPosition(const uint16_t* accessor) {
    static const int16_t kNone[3] = {0, 0, 0};
    const uint8_t* data = static_cast<CKSrvBeacon*>(g_pEngine->m_srvBeacon)->GetBeaconData(accessor);
    return data != nullptr ? reinterpret_cast<const int16_t*>(data) : kNone;
}

}  // namespace

CKLightningCinematicBloc::CKLightningCinematicBloc() {
    for (uint16_t& v : m_aui16EndBeacon) v = 0xffff;
    for (uint16_t& v : m_aui16StartBeacon) v = 0xffff;
    // The fresh heap's zeroes.
    m_pEffect = nullptr;
    m_unk84 = 0;
    m_fDuration = 0.0f;
    m_fTimeLeft = 0.0f;
}

// 0x0017d5e0 CKLightningCinematicBloc_Load: the element part; for the level type 0 the two beacon accessors, the
// embedded data (its own Load, type 0) and the duration; then (every type) no effect.
int32_t CKLightningCinematicBloc::Load(IKFile* file, int32_t type) {
    BasicLoadCinematicElement(file, type);  // 0x0018edd8
    if (type == 0) {
        ReadAccessor(file, m_aui16StartBeacon);
        ReadAccessor(file, m_aui16EndBeacon);
        m_lightningData.CKLightningObjectFxData::Load(file, 0);  // 0x001c6d48
        ReadF32LE(file, &m_fDuration);
    }
    m_pEffect = nullptr;
    return 1;
}

void CKLightningCinematicBloc::StrikeEffect() {
    m_pEffect = static_cast<CKSrvFx*>(g_pEngine->m_srvFx)->AcquireFx(&m_lightningData, this);  // engine +0x60
    if (m_pEffect != nullptr) return;
    m_pEffect = nullptr;
    Complete();  // vt+0x64
}

void CKLightningCinematicBloc::ReleaseRunningEffect() {
    IKFx* effect = m_pEffect;
    if (effect == nullptr) return;
    const uint8_t flags = effect->m_baFxData;
    if ((flags & 1u) != 0) return;
    effect->StopAndRelease(this);  // vt+0x58
    m_pEffect = nullptr;           // stw of the clear bit 0
}

// 0x0017da90 CKLightningCinematicBloc_Start: the blocs' common start, then the data's ends on the two beacons (tenths,
// fcfid / frsp then x 0.1), the countdown from the duration, the data's flags bits 0 and 1 set and bit 2 cleared, then
// the strike.
void CKLightningCinematicBloc::Start() {
    StartCommon();
    const int16_t* start = BeaconPosition(m_aui16StartBeacon);
    const int16_t* end = BeaconPosition(m_aui16EndBeacon);
    m_lightningData.m_afUnk18[0] = static_cast<float>(start[0]) * kTenth;
    m_lightningData.m_afUnk18[1] = static_cast<float>(start[1]) * kTenth;
    m_lightningData.m_afUnk18[2] = static_cast<float>(start[2]) * kTenth;
    m_lightningData.m_afUnk18[3] = static_cast<float>(end[0]) * kTenth;
    m_lightningData.m_afUnk18[4] = static_cast<float>(end[1]) * kTenth;
    m_fTimeLeft = m_fDuration;
    m_lightningData.m_afUnk18[5] = static_cast<float>(end[2]) * kTenth;
    m_lightningData.m_baFlags44 = static_cast<uint8_t>((m_lightningData.m_baFlags44 & 0xf8u) | 3u);
    StrikeEffect();
}

// 0x0017e238 CKLightningCinematicBloc_Complete: the completion only.
void CKLightningCinematicBloc::Complete() {
    CompleteBloc();
}

// 0x0017e410 CKLightningCinematicBloc_Update: (unless its sekens stopped it) without flag 0x80 the bloc completes once
// its effect has ended (the node stopped and released); with it the countdown runs (ble: a NaN one has run out) and,
// while time is left, an ended effect is struck again; once out, a running effect is stopped and the bloc completes.
void CKLightningCinematicBloc::Update(IKTime* time) {
    if (CheckSekensStop() == 0) return;  // 0x0018e9e0
    if ((m_DataFlags & 0x80u) == 0) {
        IKFx* effect = m_pEffect;
        if (effect == nullptr) return;
        if ((effect->m_baFxData & 1u) == 0) return;
        effect->StopAndRelease(this);  // vt+0x58
        m_pEffect = nullptr;
        Complete();  // vt+0x64
        return;
    }
    if (!(m_fTimeLeft > kZero)) {  // fcmpu / ble
        ReleaseRunningEffect();
        Complete();
        return;
    }
    m_fTimeLeft = m_fTimeLeft - time->m_afDeltaTime[0];
    if (m_pEffect == nullptr) return;
    if ((m_pEffect->m_baFxData & 1u) == 0) return;
    StrikeEffect();
}

// 0x0017d3b0 CKLightningCinematicBloc_Stop: the completion (inlined), a running effect stopped and released, then
// Complete (vt+0x64).
void CKLightningCinematicBloc::Stop() {
    CompleteBloc();
    ReleaseRunningEffect();
    Complete();  // vt+0x64
}
