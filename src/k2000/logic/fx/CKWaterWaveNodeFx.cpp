// CKWaterWaveNodeFx.cpp - reconstructed original translation unit 0x56ff60-0x5710f0 (GAME_TOC2, main_toc2), 25 functions, 25 live.
// Primary class: CKWaterWaveNodeFx  key 0x3bcc  category Logic  size ?  vtable 0xb2dba0
// Other owners: CKWaterSplashFxData (9)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x56ff60  CKWaterWaveNodeFx_Delete  (DOTD_DECLARE_FACTORIES)
//   [x] 0x56ffb0  CKWaterWaveNodeFx_Destroy  (empty)
//   [x] 0x56ffb8  CKWaterWaveNodeFx_RecursiveRegistration
//   [x] 0x570060  CKWaterWaveNodeFx_PostLoad  (returns 1)
//   [x] 0x570068  CKWaterWaveNodeFx_SetPositionIfOwner_maybe
//   [ ] 0x5700c0  RegisterCKWaterWaveNodeFxClass
//   [ ] 0x570138  _GLOBAL__I_570138
//   [x] 0x570148  CKWaterWaveNodeFx_Load
//   [ ] 0x570240  CKWaterWaveNodeFx_Save
//   [x] 0x570268  CKWaterWaveNodeFx_DeleteArray  (DOTD_DECLARE_FACTORIES)
//   [x] 0x570310  CKWaterWaveNodeFx_Create  (DOTD_DECLARE_FACTORIES)
//   [x] 0x570368  CKWaterWaveNodeFx_Update
//   [x] 0x570498  CKWaterWaveNodeFx_StopIfLinkedTo_maybe
//   [x] 0x5704d0  CKWaterWaveNodeFx_Stop
//   [x] 0x5704f0  CKWaterWaveNodeFx_Start
//   [x] 0x570548  CKWaterWaveNodeFx_CreateArray  (DOTD_DECLARE_FACTORIES)
//   [x] 0x570600  CKWaterSplashFxData_GetNodeClassKey
//   [x] 0x570608  CKWaterSplashFxData_EvalMesh1HeightScale_maybe
//   [x] 0x5706a8  CKWaterSplashFxData_EvalMesh2HeightScale_maybe
//   [x] 0x570748  CKWaterSplashFxData_EvalWidthScale_maybe
//   [x] 0x5707e8  CKWaterSplashFxData_EvalAlpha_maybe
//   [x] 0x570888  CKWaterSplashFxData_RecursiveRegistration  (IKFxData's, nothing)
//   [x] 0x5708b0  CKWaterSplashFxData_Destroy
//   [x] 0x570948  CKWaterSplashFxData_Load
//   [ ] 0x570d68  CKWaterSplashFxData_Save
//
//   [x] 0x9ca9a8  CKWaterWaveNodeFx_IsKindOfClass  [inline]
//   [x] 0x9ca9e0  CKWaterWaveNodeFx_GetClassType  [inline]
//   [x] 0x9ca9e8  CKWaterWaveNodeFx_GetClassID  [inline]
//   [x] 0x9ca9f0  CKWaterWaveNodeFx_GetFxData  [inline]
//   [x] 0x9ca9f8  CKWaterWaveNodeFx_SetFxData  [inline]
//   [ ] 0x9caa00  CKWaterWaveNodeFx_DeletingDestruct  [inline]
//   [ ] 0x9caa48  CKWaterWaveNodeFx_Destruct  [inline]
//   [ ] 0x9caa68  CKWaterSplashFxData_IsKindOfClass  [inline]
//   [x] 0x9caaa0  CKWaterSplashFxData_GetClassType  [inline]
//   [x] 0x9caaa8  CKWaterSplashFxData_GetClassID  [inline]
//   [ ] 0x9caab0  CKWaterSplashFxData_Destructor  [inline]
//   [ ] 0x9caaf0  CKWaterSplashFxData_DeletingDestructor  [inline]
#include "k2000/logic/fx/CKWaterWaveNodeFx.h"

#include <cmath>

#include "crt/ppc_ops.h"
#include "k2000/components/CKParticlesCpnt.h"
#include "k2000/io/IKFile.h"
#include "k2000/logic/CKSavingManager.h"
#include "k2000/logic/fx/CKSrvFxParticlesAccessor.h"
#include "k2000/logic/fx/CKWaterSplashFxData.h"
#include "k2000/logic/fx/CKWaterWaveFxData.h"
#include "k2000/misc/Engine.h"
#include "k2000/system/IKTime.h"

namespace {
// new[] of count keys read in one block and byte-swapped word by word.
CKWaterSplashFxData::Key* ReadSplashKeys(IKFile* file, uint32_t count) {
    CKWaterSplashFxData::Key* keys = new CKWaterSplashFxData::Key[count];
    ReadU32LEWords(file, reinterpret_cast<uint32_t*>(keys), count * 2);
    return keys;
}
}  // namespace

// 0x00570948 CKWaterSplashFxData_Load
int32_t CKWaterSplashFxData::Load(IKFile* file, int32_t type) {
    IKFxData::Load(file, type);  // through TocBridge_IKFxData_Load
    if (type != K_LEVEL_PLATEFORMS) return 1;
    ReadF32LE(file, &m_unk08);
    ReadU32LE(file, &m_unk1c);
    m_unk20 = ReadSplashKeys(file, m_unk1c);
    ReadU32LE(file, &m_unk14);
    m_unk18 = ReadSplashKeys(file, m_unk14);
    ReadU32LE(file, &m_unk0c);
    m_unk10 = ReadSplashKeys(file, m_unk0c);
    ReadU32LE(file, &m_unk24);
    m_unk28 = ReadSplashKeys(file, m_unk24);
    return 1;
}

// 0x0056ffb8 CKWaterWaveNodeFx_RecursiveRegistration: registered with the saving manager (vt+0x24, no owner); for type 0
// the particles accessor's registration (its vt+0x24, no null test).
void CKWaterWaveNodeFx::RecursiveRegistration(int32_t type) {
    g_pEngine->m_pSavingManager->RegisterSerializableObject(this, nullptr);  // vt+0x24
    if (type == 0) m_pParticles->RecursiveRegistration(0);
}

// 0x00570148 CKWaterWaveNodeFx_Load: IKNodeFx's; level files then hold the accessor reference and the FX flag byte (+0x0c,
// read raw).
int32_t CKWaterWaveNodeFx::Load(IKFile* file, int32_t type) {
    IKNodeFx::Load(file, type);
    if (type == K_LEVEL_PLATEFORMS) {
        IKFile_ReadRef(file, &m_pParticles);
        ReadRaw(file, &m_baFxData, 1);
    }
    return 1;
}

// 0x005704f0 CKWaterWaveNodeFx_Start: running (bit 0 cleared, bit 2 set; the reservation kept), both positions at the
// null vector (TOC -0x76cc: 0x00c50d64), the timer 0.
void CKWaterWaveNodeFx::Vf64() {
    m_baFxData = static_cast<uint8_t>((m_baFxData & 0xfa) | 4);
    m_vPrevPosition = CVector3{0.0f, 0.0f, 0.0f};
    m_vPosition = CVector3{0.0f, 0.0f, 0.0f};
    m_fTimer = 0.0f;
}

// 0x005704d0 CKWaterWaveNodeFx_Stop: stopped (bit 0), not running (bit 2 cleared).
void CKWaterWaveNodeFx::Stop() { m_baFxData = static_cast<uint8_t>((m_baFxData & 0xfa) | 1); }

namespace {
// 0x00010690 Math_Sqrtf (TocBridge 0x98fc10): the double square root rounded to float.
inline float WaveSqrtf(float x) { return static_cast<float>(std::sqrt(static_cast<double>(x))); }
}  // namespace

// 0x00570368 CKWaterWaveNodeFx_Update: not running (bit 2) -> Stop (vt+0x6c). Else the timer advances by the scaled game
// time (IKTime +0x1c) and, once it is above the data's curve of the speed (the distance moved since the last position
// change / dt; ble: an unordered curve waits), the particle component (the accessor's +0x04) emits at the position and
// the timer restarts.
void CKWaterWaveNodeFx::Update(IKTime* frameClock) {
    if ((m_baFxData & 4) == 0) {
        Stop();  // vt+0x6c
        return;
    }
    const float dy = m_vPosition.y - m_vPrevPosition.y;
    const float dx = m_vPosition.x - m_vPrevPosition.x;
    const float dz = m_vPosition.z - m_vPrevPosition.z;
    const float distance = WaveSqrtf(ppc::fmadds(dz, dz, ppc::fmadds(dx, dx, dy * dy)));
    const float dt = frameClock->m_afDeltaTime[IKTime::SCALABLE_GAME_TIME];  // +0x1c
    m_fTimer = dt + m_fTimer;
    const float curve = m_pData->EvaluateCurve(distance / dt);
    if (!(m_fTimer > curve)) return;
    CKParticlesCpnt* particles =
        static_cast<CKParticlesCpnt*>(static_cast<CKSrvFxParticlesAccessor*>(m_pParticles)->m_pParticles);
    if (particles != nullptr) particles->QueueEmission(&m_vPosition, nullptr, nullptr);  // 0x001da840
    m_fTimer = 0.0f;
}

IKFxData* CKWaterWaveNodeFx::GetFxData() { return m_pData; }                                       // 0x009ca9f0
void CKWaterWaveNodeFx::SetFxData(IKFxData* data) { m_pData = static_cast<CKWaterWaveFxData*>(data); }  // 0x009ca9f8

// 0x00570068 CKWaterWaveNodeFx_SetPositionIfOwner_maybe
void CKWaterWaveNodeFx::SetPositionIfOwner(const CVector3* position, const IKSerializable* owner) {
    if ((m_baFxData & 2) == 0 || m_pOwner != owner) return;
    m_vPrevPosition = m_vPosition;
    m_vPosition = *position;
}

// 0x00570498 CKWaterWaveNodeFx_StopIfLinkedTo_maybe
void CKWaterWaveNodeFx::StopIfOwnedBy(const IKSerializable* owner) {
    if ((m_baFxData & 2) == 0 || m_pOwner != owner) return;
    m_baFxData = static_cast<uint8_t>(m_baFxData & 0xfb);
}

namespace {
// The four curves of CKWaterSplashFxData (0x570608 / 0x5706a8 / 0x570748 / 0x5707e8, one body): linear between the two
// keys around t (the first key whose time is <= t, cror gt|eq, and the next one's > t), else the last key's value.
// BUG(original): the test of the last key reads the key after the array, and without keys the answer is read before it
// (keys[-1]); here the missing key never contains t and no keys give 0.
float EvalSplashCurve(float t, const CKWaterSplashFxData::Key* keys, uint32_t count) {
    for (uint32_t i = 0; i < count; ++i) {
        const CKWaterSplashFxData::Key& k0 = keys[i];
        if (!(t > k0.m_unk00 || t == k0.m_unk00)) continue;
        if (i + 1 >= count) continue;
        const CKWaterSplashFxData::Key& k1 = keys[i + 1];
        if (t < k1.m_unk00) return k0.m_unk04 + ((k1.m_unk04 - k0.m_unk04) * (t - k0.m_unk00)) / (k1.m_unk00 - k0.m_unk00);
    }
    return count != 0 ? keys[count - 1].m_unk04 : 0.0f;
}
}  // namespace

float CKWaterSplashFxData::EvalMesh1HeightScale(float t) const { return EvalSplashCurve(t, m_unk10, m_unk0c); }  // 0x570608
float CKWaterSplashFxData::EvalMesh2HeightScale(float t) const { return EvalSplashCurve(t, m_unk18, m_unk14); }  // 0x5706a8
float CKWaterSplashFxData::EvalWidthScale(float t) const { return EvalSplashCurve(t, m_unk20, m_unk1c); }        // 0x570748
float CKWaterSplashFxData::EvalAlpha(float t) const { return EvalSplashCurve(t, m_unk28, m_unk24); }             // 0x5707e8

// 0x005708b0 CKWaterSplashFxData_Destroy: the four key arrays deleted. The original keeps the pointers; they are cleared
// here so that a second Destroy cannot delete them again.
void CKWaterSplashFxData::Destroy() {
    delete[] m_unk20;
    m_unk20 = nullptr;
    delete[] m_unk18;
    m_unk18 = nullptr;
    delete[] m_unk10;
    m_unk10 = nullptr;
    delete[] m_unk28;
    m_unk28 = nullptr;
}
