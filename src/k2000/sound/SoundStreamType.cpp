// SoundStreamType.cpp - reconstructed original translation unit 0x11d650-0x11ef08 (GAME_TOC1, main_toc1), 27 functions, 23 live.
// Primary owner: SoundStreamType (not a registered class)
// Other owners: SoundEmitterGroup (11), SoundStream (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [ ] 0x11d650  SoundStreamType_RemovePending_maybe
//   [ ] 0x11d6e0  SoundStreamType_AssignObjectToFreeStream_maybe  [dead]
//   [ ] 0x11d7e0  SoundEmitterGroup_DestroyVoices_maybe
//   [ ] 0x11d880  SoundStreamType_Construct_2_maybe  [dead]
//   [x] 0x11d940  SoundEmitterGroup_SnapVolumeToTarget_maybe
//   [x] 0x11d958  SoundEmitterGroup_SetVolume_maybe
//   [ ] 0x11d980  SoundEmitterGroup_AreAllVoicesInactive_maybe
//   [x] 0x11d9f8  SoundStreamType_StartVolumeFade_maybe
//   [ ] 0x11da78  SoundStreamType_CountStreamsInState3_maybe  [dead]
//   [ ] 0x11dad0  SoundEmitterGroup_AreAllVoicesState9_maybe
//   [ ] 0x11db78  SoundStreamType_UnpauseObject_maybe
//   [ ] 0x11dc20  SoundEmitterGroup_ResumeVoiceOf_maybe
//   [ ] 0x11dcc8  SoundEmitterGroup_PauseVoiceOf_maybe
//   [x] 0x11dd70  SoundEmitterGroup_PauseInstances_maybe
//   [x] 0x11ddc0  SoundEmitterGroup_ResumeInstances_maybe
//   [x] 0x11de10  SoundEmitterGroup_StartVolumeFade_maybe
//   [ ] 0x11de70  SoundEmitterGroup_AreAllVoicesSettled_maybe
//   [x] 0x11df10  SoundStreamType_Construct_maybe
//   [x] 0x11dfd0  SoundStreamType_Load_maybe
//   [ ] 0x11e1b0  SoundStreamType_StopObject_maybe
//   [ ] 0x11e340  SoundStreamType_Save_maybe
//   [x] 0x11e588  SoundStream_Update_maybe
//   [ ] 0x11e818  SoundStreamType_PlayObject_maybe
//   [x] 0x11ea28  SoundStreamType_SetStreamCount_maybe
//   [ ] 0x11ebe0  SoundStreamType_Destructor_2_maybe  [dead]
//   [ ] 0x11ece8  SoundStreamType_DeletingDestructor_maybe
//   [ ] 0x11ee00  SoundStreamType_Destructor_maybe
#include "k2000/sound/SoundStreamType.h"

#include <cmath>

#include "k2000/core/IKSerializable.h"
#include "k2000/io/IKFile.h"
#include "k2000/memory/Mem.h"
#include "k2000/misc/FloatApproach.h"
#include "k2000/system/IKTime.h"

namespace {

// Local copy of 0x000107d8 Str_HashXor4 (misc/Wcs.cpp, not ported yet): the bytes XORed into four
// accumulators in turn, returned as a little-endian word (lwbrx).
uint32_t Str_HashXor4(const char* s) {
    uint8_t acc[4] = {0, 0, 0, 0};
    for (uint32_t i = 0; s[i] != 0; ++i) acc[i & 3] ^= static_cast<uint8_t>(s[i]);
    return static_cast<uint32_t>(acc[0]) | (static_cast<uint32_t>(acc[1]) << 8) | (static_cast<uint32_t>(acc[2]) << 16) |
           (static_cast<uint32_t>(acc[3]) << 24);
}

}  // namespace

// 0x0011df10 SoundStreamType_Construct_maybe. The stores in the original's order.
SoundStreamType::SoundStreamType() {
    m_vpStreams.m_pBlock = nullptr;
    m_vpStreams.m_ui32NbUsedElt = 0;
    m_unk118 = 0.0f;
    m_unk11c = 0.0f;
    m_unk120 = 0.0f;
    m_unk130 = 0;
    m_vpStreams.m_ui32NbElt = 2;
    m_vpStreams.m_pBlock = static_cast<void**>(Mem_AllocAligned16(2 * static_cast<uint32_t>(sizeof(void*))));
    m_fVolume = 1.0f;          // TOC 0xc115f4
    m_unk12c = 0x1.99999ap-1f;  // 0.8, TOC 0xc115f8
    m_unk11c = 0.0f;
    m_unk120 = m_fVolume;
    m_unk118 = m_fVolume;
    m_ui32NameHash = 0;
    m_unk128 = 0x1.99999ap-1f;
    m_unk124 = 0x1.99999ap-1f;
}

// 0x0011ea28 SoundStreamType_SetStreamCount_maybe. STUB(audio): when the time manager's clock runs
// (g_pEngine->m_timeManager, clock state != 0) and the count changes, the original releases the type's
// streams (SoundEmitterVoice_Release_maybe, then delete), creates `count` new ones (OperatorNew(0x38),
// SoundStream_Init_maybe: one RwaStreamPlayer each) into m_vpStreams (grown by 2) and rebuilds the voice
// pool (SoundVoiceManager_RebuildVoicePool_maybe). No stream is created until the audio layer exists.
void SoundStreamType::SetStreamCount(uint32_t /*count*/) {}

// 0x0011dfd0 SoundStreamType_Load_maybe
void SoundStreamType::Load(IKFile* file, int32_t type) {
    if (type != K_GAME_PLATEFORMS) return;
    IKFile_ReadLengthPrefixedString(file, m_szName, -1);
    m_ui32NameHash = Str_HashXor4(m_szName);
    ReadF32LE(file, &m_fVolume);
    ReadF32LE(file, &m_unk12c);
    ReadF32LE(file, &m_unk124);
    ReadF32LE(file, &m_unk128);
}

// 0x0011d940 SoundEmitterGroup_SnapVolumeToTarget_maybe
void SoundStreamType::SnapVolumeToTarget() {
    m_unk118 = m_fVolume;
    m_unk120 = m_fVolume;
}

// 0x0011d958 SoundEmitterGroup_SetVolume_maybe: without a fade running the ramp jumps to the volume.
void SoundStreamType::SetVolume(float volume) {
    if (m_unk118 == m_fVolume) {
        m_unk120 = volume;
        m_unk118 = volume;
    }
    m_fVolume = volume;
}

// 0x0011d9f8 SoundStreamType_StartVolumeFade_maybe: towards min(volume, +0x12c) over +0x128 seconds.
void SoundStreamType::StartVolumeFade(int32_t fromTarget) {
    const float volume = m_fVolume;
    if (fromTarget != 0) m_unk120 = volume;
    const float target = volume <= m_unk12c ? volume : m_unk12c;
    m_unk118 = target;
    if (m_unk128 != 0.0f) {
        m_unk11c = std::fabs((m_unk120 - target) / m_unk128);
        return;
    }
    m_unk120 = target;
}

// 0x0011de10 SoundEmitterGroup_StartVolumeFade_maybe
void SoundStreamType::ReleaseVolumeFade() {
    m_unk118 = m_fVolume;
    if (m_unk124 != 0.0f) {
        m_unk11c = std::fabs((m_unk120 - m_fVolume) / m_unk124);
        return;
    }
    m_unk120 = m_fVolume;
}

// 0x0011dd70 SoundEmitterGroup_PauseInstances_maybe: pauses the tracks on +0x130. STUB(C2): none exist.
void SoundStreamType::PauseInstances() {}

// 0x0011ddc0 SoundEmitterGroup_ResumeInstances_maybe: resumes the tracks on +0x130. STUB(C2): none exist.
void SoundStreamType::ResumeInstances() {}

// 0x0011e588 SoundStream_Update_maybe: the volume ramp, then the tracks (+0x130) get stream players and
// the players (+0x108) run their state machines. STUB(C2): no track or player exists before the level
// streams (SetStreamCount creates no RwaStreamPlayer yet), so only the ramp runs.
void SoundStreamType::Update(IKTime* clock) {
    FloatApproach_Step(clock->m_afDeltaTime[IKTime::FIXED_GAME_TIME], &m_unk118);
    // KStub_Nop_106d8(6, "%s volume %f", name, +0x120): a debug print
}
