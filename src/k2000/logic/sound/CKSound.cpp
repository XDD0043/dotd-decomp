// CKSound.cpp - reconstructed original translation unit 0x110e40-0x1122f8 (GAME_TOC1, main_toc1), 43 functions, 31 live.
// Primary class: CKSound  key 0x2acc  category Logic  size 0x74  vtable 0xb197d8
// Other owners: Sound (1), SoundInstance (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x110e40  CKSound_Delete
//   [ ] 0x110e90  CKSound_RecursiveRegistration
//   [x] 0x110e98  CKSound_SetSpeed_maybe
//   [x] 0x110ea0  CKSound_SetPitch_maybe
//   [ ] 0x110ec8  CKSound_SetRandomPitchRange_maybe  [dead]
//   [ ] 0x110ed0  CKSound_SetRandomVolumeRange_maybe  [dead]
//   [ ] 0x110ed8  FUN_00110ed8  [dead]
//   [ ] 0x110ee0  FUN_00110ee0  [dead]
//   [x] 0x110ee8  CKSound_SetBaseVolume_maybe
//   [x] 0x110f10  CKSound_SetVolume_maybe
//   [ ] 0x110f38  CKSound_SetMinDistance_maybe  [dead]
//   [ ] 0x110f58  CKSound_SetMaxDistance_maybe  [dead]
//   [ ] 0x110f78  CKSound_SetDistanceRange_maybe  [dead]
//   [x] 0x110fa0  CKSound_SetPosition
//   [x] 0x110fd0  CKSound_SetLoop_maybe
//   [x] 0x110ff0  CKSound_GetPosition
//   [x] 0x111000  CKSound_GetSample_maybe
//   [x] 0x111008  CKSound_GetAttachedNode_maybe
//   [ ] 0x111010  CKSound_ClearInstanceList_maybe  [dead]
//   [x] 0x111050  CKSound_GetInstanceAt_maybe
//   [ ] 0x1110a8  RegisterCKSoundClass
//   [ ] 0x111120  _GLOBAL__I_111120
//   [ ] 0x111130  FUN_00111130  [dead]
//   [x] 0x111158  CKSound_GetRandomVolumeOffset_maybe
//   [x] 0x1111b0  Sound_Stop
//   [x] 0x111230  CKSound_Play
//   [x] 0x111270  CKSound_DeleteArray
//   [x] 0x111310  CKSound_Create
//   [x] 0x111350  CKSound_SetAttachObject
//   [x] 0x1113c0  SoundInstance_ComputePlaybackRate_maybe
//   [x] 0x1114c8  CKSound_CreateArray
//   [x] 0x111568  CKSound_IsPlaying_maybe
//   [ ] 0x111600  CKSound_GetInfo
//   [ ] 0x111608  CKSound_Save
//   [ ] 0x111610  CKSound_Destroy
//   [ ] 0x111648  FUN_00111648  [dead]
//   [x] 0x111728  CKSound_MessageProc
//   [x] 0x111818  CKSound_UpdatePan_maybe
//   [ ] 0x111aa8  CKSound_SetPan_maybe  [dead]
//   [x] 0x111ae0  CKSound_PostLoad
//   [x] 0x111b70  CKSound_ResetPan_maybe
//   [ ] 0x111ba0  CKSound_ResetDefaults_maybe  [dead]
//   [x] 0x111d08  CKSound_Load
//
//   [ ] 0x9a6978  CKSound_GetClassType  [inline]
//   [ ] 0x9a6980  CKSound_GetClassID  [inline]
//   [ ] 0x9a6988  CKSound_IsKindOfClass  [inline]
//   [ ] 0x9a69a8  CKSound_DeletingDestructor  [inline]
//   [ ] 0x9a6a28  CKSound_Destructor  [inline]
#include "k2000/logic/sound/CKSound.h"

#include <cstring>

#include "crt/ppc_ops.h"
#include "k2000/io/IKFile.h"
#include "k2000/logic/sound/CKWave.h"
#include "k2000/managers/CKSoundManager.h"
#include "k2000/misc/ClassRegistry.h"
#include "k2000/misc/Engine.h"
#include "k2000/sound/SoundInstance.h"
#include "k2000/sound/SoundVoiceManager.h"

namespace {

// 0x00c50d64: the shared zero vector the original copies (statically and live (0, 0, 0)).
const CVector3 kZeroVector = {0.0f, 0.0f, 0.0f};

// TOC constants (game TOC 0xc159d8)
constexpr float kOne = 1.0f;                  // -0x4620
constexpr float kZero = 0.0f;                 // -0x461c
constexpr float kRandScale = -0x1.000100p-15f;  // -0x45f4 (0xb8000080)
constexpr float kMinPitch = 0x1.47ae14p-7f;   // -0x4628 (0x3c23d70a, 0.01)
constexpr float kMaxPitch = 10.0f;            // -0x4624
constexpr float kMinRate = 100.0f;            // -0x45e4
constexpr float kMaxRate = 96000.0f;          // -0x45e0
constexpr float kPanRadius = 10.0f;           // -0x4624
constexpr float kHalfPi = 0x1.921fb6p+0f;     // -0x45b8 (0x3fc90fdb)
constexpr float kFourOverPi = 0x1.45f306p+0f; // -0x45dc (0x3fa2f983)
// the inlined float sine (x in quarter turns) and cosine polynomials
constexpr float kSin0 = -0x1.2d92fap-15f;     // -0x45c8 (0xb816c97d)
constexpr float kSin1 = 0x1.465e92p-9f;       // -0x45c4 (0x3b232f49)
constexpr float kSin2 = 0x1.4abbbap-4f;       // -0x45c0 (0x3da55ddd)
constexpr float kSin3 = 0x1.921fb6p-1f;       // -0x45bc (0x3f490fdb)
constexpr float kCos0 = -0x1.4e35dap-12f;     // -0x45d8 (0xb9a71aed)
constexpr float kCos1 = 0x1.03ae64p-6f;       // -0x45d4 (0x3c81d732)
constexpr float kCos2 = 0x1.3bd38cp-2f;       // -0x45d0 (0x3e9de9c6)
constexpr float kCos3 = 0x1.fffffep-1f;       // -0x45cc (0x3f7fffff)

// One Read of `count` little-endian words into consecutive fields, each then swapped (the original's
// lwbrx/stw after a multi-word read). Local until IKFile.h has such a helper.
void ReadWordsLE(IKFile* file, void* dst, uint32_t count) {
    uint8_t bytes[0x18];
    file->Read(bytes, count * 4);
    for (uint32_t i = 0; i < count; ++i) {
        const uint8_t* b = bytes + 4 * i;
        const uint32_t word = static_cast<uint32_t>(b[0]) | (static_cast<uint32_t>(b[1]) << 8) |
                              (static_cast<uint32_t>(b[2]) << 16) | (static_cast<uint32_t>(b[3]) << 24);
        std::memcpy(static_cast<uint8_t*>(dst) + 4 * i, &word, 4);
    }
}

SoundVoiceManager* VoiceManager() { return g_pEngine->m_soundManager->m_pVoiceManager; }

// The two polynomials of the inlined sine/cosine (f: the fraction of the octant).
float SinPoly(float f) {
    float t = f * kSin0;
    t = ppc::fmadds(f, t, kSin1);
    t = f * t;
    t = ppc::fmsubs(f, t, kSin2);
    t = f * t;
    t = ppc::fmadds(f, t, kSin3);
    return f * t;
}
float CosPoly(float f) {
    float t = f * kCos0;
    t = ppc::fmadds(f, t, kCos1);
    t = f * t;
    t = ppc::fmsubs(f, t, kCos2);
    t = f * t;
    return ppc::fmadds(f, t, kCos3);
}

// The octant split both inlined functions share: q = trunc(x * 4/pi), f = the fraction, mirrored on odd q.
float Octant(float x, int32_t* q) {
    const float scaled = x * kFourOverPi;
    *q = ppc::fctiwz(scaled);
    float f = scaled - static_cast<float>(static_cast<double>(*q));
    if ((*q & 1) != 0) f = kOne - f;
    return f;
}

// The inlined cosf (non-negative x; 0x009a11d8 for negative ones, see UpdatePan).
float InlineCos(float x) {
    int32_t q;
    const float f = Octant(x, &q);
    float r = ((q + 1) & 2) != 0 ? SinPoly(f) : CosPoly(f);
    if (((q + 2) & 7) > 3) r = -r;
    return r;
}
// The inlined sinf (non-negative x; 0x009a1390 for negative ones).
float InlineSin(float x) {
    int32_t q;
    const float f = Octant(x, &q);
    float r = ((q + 1) & 2) != 0 ? CosPoly(f) : SinPoly(f);
    if ((q & 7) > 3) r = -r;
    return r;
}

bool IsNegative(float x) {
    int32_t bits;
    std::memcpy(&bits, &x, 4);
    return bits < 0;
}

}  // namespace

// 0x00111310 CKSound_Create (the constructor is inlined there)
CKSound::CKSound() { m_pInstances = nullptr; }

// 0x00111d08 CKSound_Load
int32_t CKSound::Load(IKFile* file, int32_t type) {
    if (type != K_LEVEL_PLATEFORMS) return 1;
    IKFile_ReadRef(file, &m_pKWave);
    ReadF32LE(file, &m_fVolume);
    ReadF32LE(file, &m_fRandomVolume);
    ReadF32LE(file, &m_fSpeed);
    ReadF32LE(file, &m_fRandomPitch);
    ReadF32LE(file, &m_fPan);
    ReadF32LE(file, &m_fFadeInTime);
    ReadF32LE(file, &m_fFadeOutTime);
    ReadU32LE(file, &m_SoundFlags);
    ReadU32LE(file, &m_ui32MaxInstances);
    ReadU32LE(file, &m_eInstanceMode);
    if ((m_SoundFlags & kFlagAttached) == 0) {
        ReadWordsLE(file, &m_v3LeafPosition, 3);
        m_pLeafObjectAttached = nullptr;
    } else {
        IKFile_ReadRef(file, &m_pLeafObjectAttached);
        m_v3LeafPosition.x = kZeroVector.x;
        m_v3LeafPosition.z = kZeroVector.z;
        m_v3LeafPosition.y = kZeroVector.y;
    }
    ReadF32LE(file, &m_fDistanceMin);
    ReadF32LE(file, &m_fDistanceMax);
    ReadF32LE(file, &m_fPauseTime);
    ReadWordsLE(file, m_BoundingBox, 6);
    ReadU32LE(file, &m_iSectorIndex);
    return 1;
}

// 0x00110e98 CKSound_SetSpeed_maybe
void CKSound::SetSpeed(float speed) { m_fSpeed = speed; }

// 0x00110ea0 CKSound_SetPitch_maybe: clamped to [0.01, 10] (NaN is stored).
void CKSound::SetPitch(float pitch) {
    if (pitch < kMinPitch) {
        m_fPitch = kMinPitch;
    } else if (pitch > kMaxPitch) {
        m_fPitch = kMaxPitch;
    } else {
        m_fPitch = pitch;
    }
}

// 0x00110ee8 CKSound_SetBaseVolume_maybe: clamped to [0, 1] (NaN gives 1).
void CKSound::SetBaseVolume(float volume) {
    if (volume < kZero) {
        m_fVolume = kZero;
    } else if (volume <= kOne) {
        m_fVolume = volume;
    } else {
        m_fVolume = kOne;
    }
}

// 0x00110f10 CKSound_SetVolume_maybe: clamped to [0, 1] (NaN gives 1).
void CKSound::SetVolume(float volume) {
    if (volume < kZero) {
        m_fVolumeScale = kZero;
    } else if (volume <= kOne) {
        m_fVolumeScale = volume;
    } else {
        m_fVolumeScale = kOne;
    }
}

// 0x00110fa0 CKSound_SetPosition: ignored for panned sounds.
void CKSound::SetPosition(const CVector3* position) {
    if ((m_SoundFlags & kFlagPan) != 0) return;
    const float z = position->z, y = position->y;
    m_v3LeafPosition.x = position->x;
    m_v3LeafPosition.z = z;
    m_v3LeafPosition.y = y;
}

// 0x00110fd0 CKSound_SetLoop_maybe
void CKSound::SetLoop(int32_t loop) {
    m_SoundFlags = (m_SoundFlags & ~kFlagLoop) | (static_cast<uint32_t>(loop) << 1);
}

// 0x00110ff0 CKSound_GetPosition
CVector3* CKSound::GetPosition() { return &m_v3LeafPosition; }

// 0x00111000 CKSound_GetSample_maybe
CKWave* CKSound::GetSample() { return m_pKWave; }

// 0x00111008 CKSound_GetAttachedNode_maybe
IKSerializable* CKSound::GetAttachedNode() { return m_pLeafObjectAttached; }

uint32_t CKSound::CountInstances() const {
    uint32_t n = 0;
    for (const SoundNode* node = m_pInstances; node != nullptr; node = node->m_pNext) ++n;
    return n;
}

// 0x00111050 CKSound_GetInstanceAt_maybe
SoundInstance* CKSound::GetInstanceAt(uint32_t index) {
    SoundNode* node = m_pInstances;
    if (node == nullptr) return nullptr;
    for (uint32_t i = 0; i < index; ++i) {
        node = node->m_pNext;
        if (node == nullptr) return nullptr;
    }
    return node->m_pInstance;
}

// 0x00111158 CKSound_GetRandomVolumeOffset_maybe: (rand() * -2^-15 + 1) * m_fRandomVolume, in (0, 1].
float CKSound::GetRandomVolumeOffset() {
    const uint16_t r = static_cast<uint16_t>(Rand_Int());
    const float f = static_cast<float>(static_cast<double>(r));
    return ppc::fmadds(f, kRandScale, kOne) * m_fRandomVolume;
}

// 0x001111b0 Sound_Stop
int32_t CKSound::Stop(uint8_t immediate) {
    if (m_pKWave != nullptr && CountInstances() != 0) VoiceManager()->StopSound(this, immediate);
    return 1;
}

// 0x00111230 CKSound_Play
int32_t CKSound::Play(float startSeconds) {
    VoiceManager()->PlaySound(startSeconds, this);
    return 1;
}

// 0x00111350 CKSound_SetAttachObject
int32_t CKSound::SetAttachObject(IKSerializable* node) {
    if (node != nullptr) {
        m_SoundFlags = (m_SoundFlags & ~kFlagAttached) | kFlagAttached;
        m_pLeafObjectAttached = node;
        m_v3LeafPosition.x = kZeroVector.x;
        m_v3LeafPosition.z = kZeroVector.z;
        m_v3LeafPosition.y = kZeroVector.y;
        return 1;
    }
    m_SoundFlags &= ~kFlagAttached;
    m_pLeafObjectAttached = nullptr;
    return 1;
}

// 0x001113c0 SoundInstance_ComputePlaybackRate_maybe: speed x pitch (+ a random part) x the wave's sample
// rate, clamped to [100, 96000] Hz (NaN passes).
float CKSound::ComputePlaybackRate() {
    float factor;
    if (m_fRandomPitch == kZero) {
        factor = m_fSpeed * m_fPitch;
    } else {
        const float base = m_fSpeed * m_fPitch;
        const uint16_t r = static_cast<uint16_t>(Rand_Int());
        const float f = ppc::fmadds(static_cast<float>(static_cast<double>(r)), kRandScale, kOne);
        factor = ppc::fmadds(f, m_fRandomPitch, base);
    }
    const float rate = factor * static_cast<float>(static_cast<double>(m_pKWave->m_ui16SampleRate));
    if (rate <= kMinRate) return kMinRate;
    if (rate >= kMaxRate) return kMaxRate;
    return rate;
}

// 0x00111568 CKSound_IsPlaying_maybe: an instance not stopped (state 4).
uint32_t CKSound::IsPlaying() {
    if (m_pInstances == nullptr || CountInstances() == 0) return 0;
    for (SoundNode* node = m_pInstances; node != nullptr; node = node->m_pNext) {
        if (node->m_pInstance->m_state != SoundInstance::kStateStopped) return 1;
    }
    return 0;
}

// 0x00111728 CKSound_MessageProc: 0x100 plays, 0x101 stops (with the fade-out).
int32_t CKSound::MessageProc(uint16_t message, void*) {
    if (message == 0x100) {
        VoiceManager()->PlaySound(0.0f, this);
        return 0;
    }
    if (message == 0x101) {
        if (m_pKWave != nullptr && CountInstances() != 0) VoiceManager()->StopSound(this, 0);
        return 0;
    }
    return 1;
}

// 0x00111818 CKSound_UpdatePan_maybe: the position on the 10-unit circle in the listener's frame,
// angle (m_fPan + 1) * pi/2 (pan -1: +x, the listener's right row, which RenderWare points to the
// screen's left). The cosine and sine are inlined (octant polynomials); a negative angle (pan < -1)
// calls the library's cosf 0x9a11d8 / sinf 0x9a1390, taken here as the same polynomials (never reached
// by the data: pan is in [-1, 1]).
void CKSound::UpdatePan() {
    const float angle = (m_fPan + kOne) * kHalfPi;
    float c, s;
    if (IsNegative(angle)) {
        c = InlineCos(-angle);
        s = -InlineSin(-angle);
    } else {
        c = InlineCos(angle);
        s = InlineSin(angle);
    }
    m_v3LeafPosition.y = 0.0f;
    m_v3LeafPosition.z = s * kPanRadius;
    m_v3LeafPosition.x = c * kPanRadius;
}

// 0x00111ae0 CKSound_PostLoad: panned sounds get their position; a level's sounds join the voice
// manager's sound list.
int32_t CKSound::PostLoad(int32_t type) {
    if ((m_SoundFlags & kFlagPan) != 0) UpdatePan();
    if (type == K_LEVEL_PLATEFORMS) VoiceManager()->AppendSound(this);
    m_fPitch = kOne;
    m_fVolumeScale = kOne;
    return 1;
}

// 0x00111b70 CKSound_ResetPan_maybe
void CKSound::ResetPan(int32_t pan) {
    m_SoundFlags = (m_SoundFlags & ~kFlagPan) | ((static_cast<uint32_t>(pan) << 2) & 0xfffffffcu);
    m_fPan = 0.0f;
    UpdatePan();
}
