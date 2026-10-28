// CKHkS08ElectricGauge.cpp - reconstructed original translation unit 0x492650-0x4961c0 (GAME_TOC1, main_toc1), 44 functions, 40 live.
// Primary class: CKHkS08ElectricGauge  key 0x2e42  category Hook  size 0xf4  vtable 0xb281d0
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [ ] 0x492650  CKHkS08ElectricGauge_vfF0
//   [ ] 0x492658  CKHkS08ElectricGauge_vfFC
//   [ ] 0x492660  CKHkS08ElectricGauge_vf104
//   [ ] 0x492668  CKHkS08ElectricGauge_ReleaseFxPair_maybe  [dead]
//   [ ] 0x492720  RegisterCKHkS08ElectricGaugeClass
//   [ ] 0x492798  _GLOBAL__I_492798
//   [ ] 0x4927a8  CKHkS08ElectricGauge_RandomizeSparkInterval_maybe  [dead]
//   [ ] 0x492810  CKHkS08ElectricGauge_UpdateArcEndpoints_maybe
//   [ ] 0x492948  CKHkS08ElectricGauge_Resume
//   [ ] 0x492970  CKHkS08ElectricGauge_Pause
//   [ ] 0x492998  CKHkS08ElectricGauge_Stop
//   [ ] 0x4929c0  CKHkS08ElectricGauge_PostLoad
//   [ ] 0x492a88  CKHkS08ElectricGauge_Save
//   [ ] 0x492ab0  CKHkS08ElectricGauge_RecursiveRegistration
//   [x] 0x492ad8  CKHkS08ElectricGauge_Construct
//   [x] 0x492b30  CKHkS08ElectricGauge_DeleteArray
//   [ ] 0x492bd0  CKHkS08ElectricGauge_DestructBody
//   [ ] 0x492c00  CKHkS08ElectricGauge_IsInState0
//   [ ] 0x492c10  CKHkS08ElectricGauge_IsBelowBottomHotSpot_maybe
//   [ ] 0x492c70  CKHkS08ElectricGauge_OnActivate
//   [ ] 0x492d40  CKHkS08ElectricGauge_State2_Wait_maybe
//   [ ] 0x492db0  CKHkS08ElectricGauge_Destroy
//   [ ] 0x492dd8  CKHkS08ElectricGauge_Construct_2
//   [ ] 0x492e30  CKHkS08ElectricGauge_DeletingDestructor
//   [ ] 0x492e78  CKHkS08ElectricGauge_Destructor
//   [ ] 0x492ea8  CKHkS08ElectricGauge_vf100
//   [ ] 0x492f88  CKHkS08ElectricGauge_GetInfo
//   [ ] 0x4930e8  CKHkS08ElectricGauge_GetLevelRatioSq_maybe
//   [x] 0x493198  CKHkS08ElectricGauge_CreateArray
//   [x] 0x493268  CKHkS08ElectricGauge_Create
//   [ ] 0x4932d0  CKHkS08ElectricGauge_Restart
//   [ ] 0x493458  CKHkS08ElectricGauge_OnDeactivate
//   [x] 0x493518  CKHkS08ElectricGauge_Start
//   [ ] 0x4936b0  CKHkS08ElectricGauge_OnHeroLeave_maybe
//   [ ] 0x493868  CKHkS08ElectricGauge_OnHeroEnter_maybe
//   [x] 0x493a38  CKHkS08ElectricGauge_Load
//   [ ] 0x494278  CKHkS08ElectricGauge_AcquireFxPair_maybe  [dead]
//   [ ] 0x4944e8  CKHkS08ElectricGauge_TriggerBottomReachedFx_maybe
//   [ ] 0x494a50  CKHkS08ElectricGauge_TriggerTopReachedFx_maybe
//   [x] 0x494d28  CKHkS08ElectricGauge_State1_Moving_maybe
//   [ ] 0x495120  CKHkS08ElectricGauge_UpdateLevel_maybe
//   [ ] 0x495490  CKHkS08ElectricGauge_TriggerRandomSparkFx_maybe
//   [ ] 0x4959f8  CKHkS08ElectricGauge_UpdateSparkTimer_maybe  [dead]
//   [ ] 0x495ab0  CKHkS08ElectricGauge_Update
//
//   [ ] 0x9c4ca8  CKHkS08ElectricGauge_IsKindOfClass  [inline]
//   [ ] 0x9c4d08  CKHkS08ElectricGauge_GetClassType  [inline]
//   [ ] 0x9c4d10  CKHkS08ElectricGauge_GetClassID  [inline]
#include "Spyro2008/hooks/CKHkS08ElectricGauge.h"
#include "k2000/core/Ps3MemberFn.h"
#include "k2000/core/Stub.h"
#include "k2000/misc/ClassRegistry.h"

#include "k2000/io/IKFile.h"

// 0x00493a38 CKHkS08ElectricGauge_Load
int32_t CKHkS08ElectricGauge::Load(IKFile* file, int32_t type) {
    CKHkS08ElectricGaugeBase::Load(file, type);
    if (type == K_LEVEL_PLATEFORMS) {
        IKFile_ReadRef(file, &m_apUnk24[0]);
        IKFile_ReadRef(file, &m_apUnk24[1]);
        IKFile_ReadRef(file, &m_apUnk24[2]);
        IKFile_ReadRef(file, &m_apUnk24[3]);
        IKFile_ReadRef(file, &m_unk20);
        ReadF32LE(file, &m_unk74);
        IKFile_ReadRef(file, &m_apUnk24[4]);
        IKFile_ReadRef(file, &m_apUnk24[5]);
        IKFile_ReadRef(file, &m_apUnk44[0]);
        IKFile_ReadRef(file, &m_apUnk44[1]);
        IKFile_ReadRef(file, &m_apUnk44[2]);
        ReadF32LE(file, &m_unk50);
        ReadF32LE(file, &m_unk58);
        ReadF32LE(file, &m_unk64);
        m_unkBC.Load(file, K_LEVEL_PLATEFORMS);
        m_unkB4.Load(file, K_LEVEL_PLATEFORMS);
        m_unkAC.Load(file, K_LEVEL_PLATEFORMS);
        ReadF32LE(file, &m_unkA4);
        ReadF32LE(file, &m_unkA8);
        ReadF32LE(file, &m_unkA0);
        m_unkC4.Load(file, K_LEVEL_PLATEFORMS);
        IKFile_ReadRef(file, &m_unk6c);
        IKFile_ReadRef(file, &m_unk68);
        return 1;
    }
    return 1;
}

namespace {
// DOTD: the gauge's state handlers by descriptor (k2000/core/Ps3MemberFn.h; the table Start builds at +0xd4).
Ps3MemberFnEntry<CKHkS08ElectricGauge::StateFn> g_gaugeStates[] = {
    {0x00bc4570u, nullptr, "CKHkS08ElectricGauge_UpdateLevel_maybe 0x495120 (C2.8: level objects)", false},
    {0x00bc4568u, &CKHkS08ElectricGauge::State1Moving, "CKHkS08ElectricGauge_State1_Moving_maybe 0x494d28", false},
    {0x00bc43a0u, nullptr, "CKHkS08ElectricGauge_State2_Wait_maybe 0x492d40 (C2.8: level objects)", false},
    {0x00bc4290u, &CKHkS08ElectricGauge::State3Idle, "KStub_ReturnArg4_492648", false},
};
}  // namespace

// The state engine's call of the state `state`: the PS3 table holds the descriptors of CKHkS08ElectricGauge's
// pointers to member function (OPD addresses; the adjustment is 0), mapped to the native handlers; a handler not
// ported yet leaves the state as given. Start only enters state 1.
uint8_t CKHkS08ElectricGauge::CallState(uint8_t state, IKTime* clock, int32_t phase, uint8_t other) {
    StateFn fn = ResolvePs3MemberFn(g_gaugeStates, &m_unkD4[state * 2u], "CKHkS08ElectricGauge state handler");
    if (fn == nullptr) return other;
    return (this->*fn)(clock, phase, other);
}

// 0x00494d28 CKHkS08ElectricGauge_State1_Moving_maybe: entering or leaving the state does nothing.
uint8_t CKHkS08ElectricGauge::State1Moving(IKTime* /*clock*/, int32_t phase, uint8_t other) {
    if (phase != 0) return other;
    // STUB(C2.8, level objects): the per-frame movement of the gauge (velocity integration clamped to m_unkA4 through
    // Math_Sqrtf, the two end stops through CSGHotSpot_GetWorldPosition, the top/bottom reached effects and
    // QueueTriggerSignals, the node frame through RwFrame_MarkDirty). Start only enters the state (phase 1).
    DOTD_STUB_ONCE("CKHkS08ElectricGauge::State1Moving: the per-frame movement");
    return other;
}

// 0x00493518 CKHkS08ElectricGauge_Start
void CKHkS08ElectricGauge::Start() {
    // KBase3542_ResetRuntime 0x4e08f8: the actor base's empty ResetRuntime.
    // The state table: the descriptors of the states 0..3 (TOC +0x5f9c / +0x5fa0 / +0x5fa4 / +0x5fa8), no adjustment.
    // CallState maps them to the native handlers (g_gaugeStates).
    m_unkD4[7] = 0;            // +0xf0
    m_unkD4[3] = 0;            // +0xe0
    m_unkD4[2] = 0x00bc4568u;  // +0xdc
    m_unkD4[1] = 0;            // +0xd8
    m_unkD4[5] = 0;            // +0xe8
    m_unkD4[0] = 0x00bc4570u;  // +0xd4
    m_unkD4[4] = 0x00bc43a0u;  // +0xe4
    m_unkD4[6] = 0x00bc4290u;  // +0xec
    m_unkD0 = 1;
    m_unkD1 = 4;
    m_pStateTable = &m_unkD4[0];
    CallState(1, nullptr, 1, 0xff);  // enter state 1
    for (int i = 4; i < 10; ++i) m_unk78[i] = 0;  // +0x88 and +0x94: the zero vector 0xc50d64
    m_unk54 = 0;
    const float randomUnit = static_cast<float>(static_cast<uint16_t>(Rand_Int())) / 65535.0f;  // TOC +0x5f58
    m_unk3c[1] = 0;  // +0x40
    m_unk3c[0] = 0;
    const float scaled = randomUnit * m_unk58;
    m_unk5c = ((scaled + scaled) - m_unk58) + m_unk50;
}
