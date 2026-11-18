// CKHkS08ElectricGauge.cpp - reconstructed original translation unit 0x492650-0x4961c0 (GAME_TOC1, main_toc1), 44 functions, 40 live.
// Primary class: CKHkS08ElectricGauge  key 0x2e42  category Hook  size 0xf4  vtable 0xb281d0
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x492650  CKHkS08ElectricGauge_vfF0  (header: AcceptsAbilityTarget)
//   [x] 0x492658  CKHkS08ElectricGauge_vfFC
//   [x] 0x492660  CKHkS08ElectricGauge_vf104
//   [ ] 0x492668  CKHkS08ElectricGauge_ReleaseFxPair_maybe  [dead]
//   [ ] 0x492720  RegisterCKHkS08ElectricGaugeClass
//   [ ] 0x492798  _GLOBAL__I_492798
//   [ ] 0x4927a8  CKHkS08ElectricGauge_RandomizeSparkInterval_maybe  [dead]
//   [x] 0x492810  CKHkS08ElectricGauge_UpdateArcEndpoints_maybe
//   [x] 0x492948  CKHkS08ElectricGauge_Resume  (empty / no effect: inherited)
//   [x] 0x492970  CKHkS08ElectricGauge_Pause  (empty / no effect: inherited)
//   [x] 0x492998  CKHkS08ElectricGauge_Stop  (inherited, empty)
//   [x] 0x4929c0  CKHkS08ElectricGauge_PostLoad
//   [ ] 0x492a88  CKHkS08ElectricGauge_Save
//   [x] 0x492ab0  CKHkS08ElectricGauge_RecursiveRegistration  (inherited: CKHkS08ElectricGaugeBase's)
//   [x] 0x492ad8  CKHkS08ElectricGauge_Construct
//   [x] 0x492b30  CKHkS08ElectricGauge_DeleteArray
//   [ ] 0x492bd0  CKHkS08ElectricGauge_DestructBody  [dead: no pointer to its descriptor 0xbc4380, no call]
//   [x] 0x492c00  CKHkS08ElectricGauge_IsInState0
//   [x] 0x492c10  CKHkS08ElectricGauge_IsBelowBottomHotSpot_maybe
//   [x] 0x492c70  CKHkS08ElectricGauge_OnActivate
//   [x] 0x492d40  CKHkS08ElectricGauge_State2_Wait_maybe
//   [x] 0x492db0  CKHkS08ElectricGauge_Destroy  (inherited, empty)
//   [ ] 0x492dd8  CKHkS08ElectricGauge_Construct_2  [dead: no pointer to its descriptor 0xbc43b0, no call]
//   [x] 0x492e30  CKHkS08ElectricGauge_DeletingDestructor  (the destructor, CKHkS08ElectricGauge.h)
//   [x] 0x492e78  CKHkS08ElectricGauge_Destructor  (header)
//   [x] 0x492ea8  CKHkS08ElectricGauge_vf100  (GetGrabHotSpotPosition)
//   [x] 0x492f88  CKHkS08ElectricGauge_GetInfo
//   [x] 0x4930e8  CKHkS08ElectricGauge_GetLevelRatioSq_maybe
//   [x] 0x493198  CKHkS08ElectricGauge_CreateArray
//   [x] 0x493268  CKHkS08ElectricGauge_Create
//   [x] 0x4932d0  CKHkS08ElectricGauge_Restart
//   [x] 0x493458  CKHkS08ElectricGauge_OnDeactivate  (header)
//   [x] 0x493518  CKHkS08ElectricGauge_Start
//   [x] 0x4936b0  CKHkS08ElectricGauge_OnHeroLeave_maybe
//   [x] 0x493868  CKHkS08ElectricGauge_OnHeroEnter_maybe
//   [x] 0x493a38  CKHkS08ElectricGauge_Load
//   [ ] 0x494278  CKHkS08ElectricGauge_AcquireFxPair_maybe  [dead]
//   [x] 0x4944e8  CKHkS08ElectricGauge_TriggerBottomReachedFx_maybe
//   [x] 0x494a50  CKHkS08ElectricGauge_TriggerTopReachedFx_maybe
//   [x] 0x494d28  CKHkS08ElectricGauge_State1_Moving_maybe
//   [x] 0x495120  CKHkS08ElectricGauge_UpdateLevel_maybe
//   [x] 0x495490  CKHkS08ElectricGauge_TriggerRandomSparkFx_maybe
//   [ ] 0x4959f8  CKHkS08ElectricGauge_UpdateSparkTimer_maybe  [dead]
//   [x] 0x495ab0  CKHkS08ElectricGauge_Update
//
//   [ ] 0x9c4ca8  CKHkS08ElectricGauge_IsKindOfClass  [inline]
//   [ ] 0x9c4d08  CKHkS08ElectricGauge_GetClassType  [inline]
//   [ ] 0x9c4d10  CKHkS08ElectricGauge_GetClassID  [inline]
#include "Spyro2008/hooks/CKHkS08ElectricGauge.h"
#include "k2000/core/IKInfo.h"
#include "k2000/core/Ps3MemberFn.h"
#include "k2000/core/Stub.h"
#include "k2000/misc/ClassRegistry.h"

#include "k2000/io/IKFile.h"
#include <cmath>

#include "Renderware/rwcore/RwCamera.h"
#include "crt/ppc_ops.h"
#include "k2000/fx/IKFx.h"
#include "k2000/logic/CSGHotSpot.h"
#include "k2000/logic/IKFxData.h"
#include "k2000/misc/Engine.h"
#include "k2000/scenegraph/CSGLeaf.h"
#include "k2000/scenegraph/CSGMovable.h"
#include "k2000/services/CKSrvFx.h"
#include "k2000/services/CTriggerStarter.h"
#include "k2000/system/IKTime.h"
#include "k2000/logic/fx/CKElectricArcNodeFx.h"
#include "k2000/logic/fx/CKExplosionNodeFx.h"
#include "Spyro2008/hooks/CKHkS08Hero.h"

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
    {0x00bc4570u, &CKHkS08ElectricGauge::State0Held, "CKHkS08ElectricGauge_UpdateLevel_maybe 0x495120", false},
    {0x00bc4568u, &CKHkS08ElectricGauge::State1Moving, "CKHkS08ElectricGauge_State1_Moving_maybe 0x494d28", false},
    {0x00bc43a0u, &CKHkS08ElectricGauge::State2Wait, "CKHkS08ElectricGauge_State2_Wait_maybe 0x492d40", false},
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
// The gauge's position (+0x7c) integrates its velocity (+0x88, which integrates the acceleration +0x94: (0, +0x74, 0))
// clamped to the speed +0xa4; the top hot spot (+0x24) and the bottom one (+0x28) stop it (velocity and acceleration
// zeroed; reaching the top fires its effect and queues +0xb4, reaching the bottom fires its effect and returns state 2).
// The two arc nodes (+0x68, +0x6c) are hidden while the gauge is at the top; the gauge node (+0x20) takes the position.
uint8_t CKHkS08ElectricGauge::State1Moving(IKTime* clock, int32_t phase, uint8_t other) {
    if (phase != 0) return other;
    static const float kNull[3] = {0.0f, 0.0f, 0.0f};  // 0x00c50d64
    float* const position = &m_unk78[1];      // +0x7c
    float* const velocity = &m_unk78[4];      // +0x88
    float* const acceleration = &m_unk78[7];  // +0x94
    acceleration[1] = m_unk74;
    acceleration[0] = 0.0f;
    acceleration[2] = 0.0f;
    float dt = clock->m_afDeltaTime[0];
    float vy = ppc::fmadds(dt, acceleration[1], velocity[1]);
    float vx = ppc::fmadds(dt, acceleration[0], velocity[0]);
    float vz = ppc::fmadds(dt, acceleration[2], velocity[2]);
    velocity[1] = vy;
    velocity[0] = vx;
    velocity[2] = vz;
    const float speed = static_cast<float>(std::sqrt(static_cast<double>(ppc::fmadds(vz, vz, ppc::fmadds(vx, vx, vy * vy)))));
    if (m_unkA4 < speed) {
        const float length = static_cast<float>(std::sqrt(static_cast<double>(
            ppc::fmadds(velocity[2], velocity[2], ppc::fmadds(velocity[0], velocity[0], velocity[1] * velocity[1])))));
        vx = velocity[0];
        vy = velocity[1];
        vz = velocity[2];
        if (length != 0.0f) {
            const float inverse = 1.0f / length;
            vz = inverse * vz;
            vx = inverse * vx;
            vy = inverse * vy;
            velocity[2] = vz;
            velocity[0] = vx;
            velocity[1] = vy;
        }
        vz = m_unkA4 * vz;
        vx = m_unkA4 * vx;
        vy = m_unkA4 * vy;
        velocity[2] = vz;
        velocity[0] = vx;
        velocity[1] = vy;
    } else {
        vx = velocity[0];
        vy = velocity[1];
        vz = velocity[2];
    }
    dt = clock->m_afDeltaTime[0];
    position[0] = ppc::fmadds(dt, vx, position[0]);
    position[2] = ppc::fmadds(dt, vz, position[2]);
    position[1] = ppc::fmadds(dt, vy, position[1]);
    CSGMovable* gauge = static_cast<CSGMovable*>(m_unk20);
    uint32_t hidden = 0;
    CVector3 stop;
    if (m_apUnk24[0] != nullptr) {
        static_cast<CSGHotSpot*>(m_apUnk24[0])->GetWorldPosition(&stop);
        if (position[1] > stop.y) {
            hidden = 4;
            position[1] = stop.y;
            for (int i = 0; i < 3; ++i) velocity[i] = kNull[i];
            for (int i = 0; i < 3; ++i) acceleration[i] = kNull[i];
            if (gauge->m_pRwFrame->modelling.pos.y != stop.y) {
                TriggerTopReachedFx();  // 0x00494a50
                QueueTriggerSignals(&m_unkB4);
                hidden = 4;
            }
        }
    }
    CSGLeaf* arc0 = static_cast<CSGLeaf*>(m_unk68);
    arc0->m_sgProperties = hidden | (arc0->m_sgProperties & 0xfffffffbu);
    CSGLeaf* arc1 = static_cast<CSGLeaf*>(m_unk6c);
    arc1->m_sgProperties = hidden | (arc1->m_sgProperties & 0xfffffffbu);
    uint8_t result = other;
    if (m_apUnk24[1] != nullptr) {
        static_cast<CSGHotSpot*>(m_apUnk24[1])->GetWorldPosition(&stop);
        if (!(position[1] >= stop.y)) {
            position[1] = stop.y;
            for (int i = 0; i < 3; ++i) velocity[i] = kNull[i];
            for (int i = 0; i < 3; ++i) acceleration[i] = kNull[i];
            if (gauge->m_pRwFrame->modelling.pos.y != stop.y) {
                TriggerBottomReachedFx();  // 0x004944e8
                result = 2;
            }
        }
    }
    RwFrame* frame = gauge->m_pRwFrame;
    frame->modelling.pos.z = position[2];
    frame->modelling.pos.x = position[0];
    frame->modelling.pos.y = position[1];
    frame->modelling.flags &= 0xfffdffffu;
    RwFrame_MarkDirty(frame);
    return result;
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

// 0x004932d0 CKHkS08ElectricGauge_Restart (vt+0x54): with the life flag bit 2 the two arc effects released (vt+0x58
// with the gauge as owner), otherwise forgotten; then (bit 2 clear) the gauge node put back on the bottom hot spot
// (+0x24's world matrix as its local one), its world matrix updated (vt+0x50) and its LTM position kept (+0x7c).
void CKHkS08ElectricGauge::Restart() {
    if ((m_bitArray & 4u) == 0) {
        m_unk3c[1] = nullptr;
        m_unk3c[0] = nullptr;
    } else {
        for (IKSerializable*& arc : m_unk3c) {
            if (arc != nullptr) {
                static_cast<IKFx*>(arc)->StopAndRelease(this);  // vt+0x58
                arc = nullptr;
            }
        }
    }
    if ((m_bitArray & 4u) != 0) return;
    CSGMovable* node = static_cast<CSGMovable*>(m_unk20);
    if (m_apUnk24[0] != nullptr) {
        CMatrix34 world;
        static_cast<CSGHotSpot*>(m_apUnk24[0])->GetWorldMatrix(&world);  // 0x000ce970
        node->SetLocalMatrix(reinterpret_cast<const RwMatrix*>(&world));  // 0x000d0be8
    }
    node->ForceWorldMatrixUpdate();  // vt+0x50
    const RwFrame* frame = node->m_pRwFrame;
    m_unk78[1] = frame->ltm.pos.x;  // +0x7c
    m_unk78[2] = frame->ltm.pos.y;
    m_unk78[3] = frame->ltm.pos.z;
}

namespace {
// The FX service's free effect of `data`'s node class and type (the first mapping of the class with an entry of the
// type; in it the first effect that is stopped and not reserved), given the data (vt+0x84), reserved (bit 1), given
// the owner (vt+0x88) and started (vt+0x64); null when none is free. The original inlines it.
IKFx* AcquireFx(IKSerializable* dataObject, const IKSerializable* owner) {
    IKFxData* data = static_cast<IKFxData*>(dataObject);
    CKSrvFx* service = static_cast<CKSrvFx*>(g_pEngine->m_srvFx);
    const uint32_t nodeClass = data->GetAssociatedFxClassIdentifier();
    const uint32_t type = data->GetAssociatedFxClassType();
    for (uint32_t i = 0; i < service->m_ui32EltNb; ++i) {
        const CKSrvFx::CMappingindex& mapping = service->m_apMappingIndexTable[i];
        if (mapping.m_ui32ClassId != nodeClass || mapping.m_ui32NbTypeFx == 0) continue;
        for (uint32_t j = 0; j < mapping.m_ui32NbTypeFx; ++j) {
            const CKSrvFx::CUnderMappingindex& under = mapping.m_aUnderMapping[j];
            if (static_cast<uint32_t>(under.m_i32FxTypeId) != type) continue;
            for (uint32_t k = 0; k < under.m_ui32MaxSize; ++k) {
                IKFx* node = static_cast<IKFx*>(under.m_apFxArrayForTypeId[k]);
                if ((node->m_baFxData & 1) == 0 || (node->m_baFxData & 2) != 0) continue;
                node->SetFxData(data);
                node->m_baFxData = static_cast<uint8_t>((node->m_baFxData & 0xfc) | (node->m_baFxData & 1) | 2);
                node->SetOwner(owner);
                node->Vf64();
                return node;
            }
            return nullptr;
        }
    }
    return nullptr;
}

// The node at the hot spot's world position, visible unless the gauge is in state 3 or none (0xff).
void PlaceAtHotSpot(IKSerializable* hotSpot, IKSerializable* nodeObject, uint8_t state) {
    CVector3 world;
    static_cast<CSGHotSpot*>(hotSpot)->GetWorldPosition(&world);
    CSGMovable* node = static_cast<CSGMovable*>(nodeObject);
    RwFrame* frame = node->m_pRwFrame;
    frame->modelling.pos.z = world.z;
    frame->modelling.pos.x = world.x;
    frame->modelling.pos.y = world.y;
    frame->modelling.flags &= 0xfffdffffu;
    RwFrame_MarkDirty(frame);
    CSGLeaf* leaf = static_cast<CSGLeaf*>(nodeObject);
    if (state == 0xff || state == 3) {
        leaf->m_sgProperties = (leaf->m_sgProperties & 0xfffffffbu) | 4u;
    } else {
        leaf->m_sgProperties &= 0xfffffffbu;
    }
}
}  // namespace

// 0x00495ab0 CKHkS08ElectricGauge_Update: the base's update; the two arc nodes at their hot spots (+0x2c / +0x30);
// with the bottom hot spot (+0x24): when the gauge node is not at its height, the two arc effects are taken (data
// +0x34 / +0x38) and aimed, and the spark timer (+0x54) fires a random spark when it passes its interval (+0x5c: a new
// one drawn around +0x50 by +/- +0x58, one rand()); at that height both effects are released. Then the state engine.
void CKHkS08ElectricGauge::Update(IKTime* clock) {
    CKHkS08ElectricGaugeBase::Update(clock);
    if (m_apUnk24[2] != nullptr) PlaceAtHotSpot(m_apUnk24[2], m_unk68, m_unkD0);
    if (m_apUnk24[3] != nullptr) PlaceAtHotSpot(m_apUnk24[3], m_unk6c, m_unkD0);
    if (m_apUnk24[0] != nullptr) {
        CVector3 bottom;
        static_cast<CSGHotSpot*>(m_apUnk24[0])->GetWorldPosition(&bottom);
        if (static_cast<CSGMovable*>(m_unk20)->m_pRwFrame->modelling.pos.y != bottom.y) {
            for (int i = 0; i < 2; ++i) {
                if (m_unk3c[i] == nullptr) m_unk3c[i] = AcquireFx(m_apUnk24[4 + i], this);
            }
            UpdateArcEndpoints();  // 0x00492810
            const float timer = m_unk54 + clock->m_afDeltaTime[0];
            m_unk54 = timer;
            if (m_unk5c <= timer) {
                m_unk54 = 0.0f;
                const float unit = static_cast<float>(static_cast<uint16_t>(Rand_Int())) / 65535.0f;  // TOC +0x5f58
                const float scaled = unit * m_unk58;
                m_unk5c = ((scaled + scaled) - m_unk58) + m_unk50;
                TriggerRandomSparkFx();  // 0x00495490
            }
        } else {
            for (int i = 0; i < 2; ++i) {
                IKFx* arc = static_cast<IKFx*>(m_unk3c[i]);
                if (arc == nullptr) continue;
                arc->StopAndRelease(this);  // vt+0x58 with the gauge
                m_unk3c[i] = nullptr;
            }
        }
    }
    // The state engine: the current state's tick, then the state it returns (leave and enter with the clock).
    const uint8_t current = m_unkD0;
    if (current == 0xff) return;
    const uint8_t next = CallState(current, clock, 0, current);
    const uint8_t previous = m_unkD0;
    if (next == previous) return;
    if (previous != 0xff) CallState(previous, clock, 2, next);
    m_unkD0 = next;
    if (next != 0xff) CallState(next, clock, 1, previous);
}

// 0x004930e8 CKHkS08ElectricGauge_GetLevelRatioSq_maybe
float CKHkS08ElectricGauge::GetLevelRatioSq() const {
    CVector3 bottom;
    CVector3 top;
    static_cast<CSGHotSpot*>(m_apUnk24[0])->GetWorldPosition(&bottom);
    static_cast<CSGHotSpot*>(m_apUnk24[1])->GetWorldPosition(&top);
    const RwV3d& node = FrameLtm(static_cast<CSGMovable*>(m_unk20)->m_pRwFrame)->pos;  // RwFrame +0x80
    const float dy = node.y - bottom.y;
    const float dx = node.x - bottom.x;
    const float dz = node.z - bottom.z;
    const float ty = top.y - bottom.y;
    const float tx = top.x - bottom.x;
    const float tz = top.z - bottom.z;
    return ppc::fmadds(dz, dz, ppc::fmadds(dx, dx, dy * dy)) / ppc::fmadds(tz, tz, ppc::fmadds(tx, tx, ty * ty));
}

// 0x004929c0 CKHkS08ElectricGauge_PostLoad: the actor base's, +0x70 cleared for the level type, then the four trigger
// starters' (TriggerEventList_PostLoad_maybe 0x236330: returns at once).
int32_t CKHkS08ElectricGauge::PostLoad(int32_t type) {
    CKHkS08ElectricGaugeBase::PostLoad(type);
    if (type == K_LEVEL_PLATEFORMS) m_unk70 = 0;
    return 1;
}

// 0x00492c70 CKHkS08ElectricGauge_OnActivate (vt+0xa0): the actor base's (CKHkActorBase_d82_maybe_OnActivate 0x3f7338,
// the active-actor list), the gauge node put at the bottom hot spot's matrix and its world matrix updated (vt+0x50),
// the gauge's position (+0x7c) taken from it.
void CKHkS08ElectricGauge::VfA0() {
    CKHkS08ElectricGaugeBase::VfA0();
    CSGMovable* gauge = static_cast<CSGMovable*>(m_unk20);
    if (m_apUnk24[0] != nullptr) {
        alignas(16) CMatrix34 matrix;
        static_cast<CSGHotSpot*>(m_apUnk24[0])->GetWorldMatrix(&matrix);
        gauge->SetLocalMatrix(reinterpret_cast<const RwMatrix*>(&matrix));
    }
    gauge->ForceWorldMatrixUpdate();
    const RwV3d& position = FrameLtm(gauge->m_pRwFrame)->pos;  // RwFrame +0x80
    m_unk78[1] = position.x;
    m_unk78[3] = position.z;
    m_unk78[2] = position.y;
}

// 0x00492f88 CKHkS08ElectricGauge_GetInfo, with 0x00492c10 _IsBelowBottomHotSpot_maybe (the node's LTM y below the bottom
// hot spot's), 0x004930e8 GetLevelRatioSq and 0x00492c00 _IsInState0 (+0xd0 is 0). The actor base answers 1.
int32_t CKHkS08ElectricGauge::GetInfo(IKInfo* info, int32_t request) {
    if (request != kGetInfoValueAccessor) return 1;
    switch (info->m_ui32Id) {
    case 0x99:
        return AnswerInfo(info, [](IKSerializable* o, uint32_t) {
            const CKHkS08ElectricGauge* gauge = static_cast<CKHkS08ElectricGauge*>(o);
            CVector3 bottom;
            static_cast<CSGHotSpot*>(gauge->m_apUnk24[0])->GetWorldPosition(&bottom);  // 0x000ce790
            const float y = FrameLtm(static_cast<CSGMovable*>(gauge->m_unk20)->m_pRwFrame)->pos.y;  // +0x84
            return y < bottom.y ? 1u : 0u;
        }, 0);
    case 0x9a:
        return AnswerInfo(info, [](IKSerializable* o, uint32_t) {
            return FloatBits(static_cast<CKHkS08ElectricGauge*>(o)->GetLevelRatioSq());
        }, 2);
    case 0x9c:
        return AnswerInfo(info, [](IKSerializable* o, uint32_t) { return static_cast<CKHkS08ElectricGauge*>(o)->m_unkD0 == 0 ? 1u : 0u; }, 0);
    default:
        return 1;
    }
}

// 0x004936b0 CKHkS08ElectricGauge_OnHeroLeave_maybe (vt+0xf8): the state engine's switch to state 1 is inlined (no
// clock: the leave gets other 1, the enter the old state).
void CKHkS08ElectricGauge::OnHeroLeave(IKSerializable* hero) {
    if (m_unk70 != hero) return;
    const uint8_t old = m_unkD0;
    if (old != 2) {
        if (old != 0xff) CallState(old, nullptr, 2, 1);
        m_unkD0 = 1;
        CallState(1, nullptr, 1, old);
    }
    m_unk78[0] = 0.0f;
    m_unk70 = nullptr;
    QueueTriggerSignals(&m_unkAC);  // 0x00236338
}

// 0x00493868 CKHkS08ElectricGauge_OnHeroEnter_maybe (vt+0xf4): the switch to state 0 inlined as in OnHeroLeave.
uint8_t CKHkS08ElectricGauge::OnHeroEnter(IKSerializable* hero) {
    if (m_unk70 != nullptr) return 0;
    const uint8_t old = m_unkD0;
    if (old != 2) {
        if (old != 0xff) CallState(old, nullptr, 2, 0);
        m_unkD0 = 0;
        CallState(0, nullptr, 1, old);
    }
    m_unk78[0] = 0.0f;
    m_unk70 = hero;
    QueueTriggerSignals(&m_unkBC);  // 0x00236338
    return 1;
}

namespace {
// The position an explosion of the gauge goes off at: the hot spot's world position, else the hook node's modelling
// position (+0x40).
CVector3 GaugeFxPoint(const CKHkS08ElectricGauge* gauge, IKSerializable* hotSpot) {
    CVector3 at;
    if (hotSpot != nullptr) {
        static_cast<CSGHotSpot*>(hotSpot)->GetWorldPosition(&at);  // 0x000ce790
    } else {
        const RwV3d& p = static_cast<CSGMovable*>(gauge->m_pKGLObject)->m_pRwFrame->modelling.pos;
        at = {p.x, p.y, p.z};
    }
    return at;
}

// An explosion of `data` taken from the FX pool (the inlined lookup), set at `at`, set off and let go (vt+0x54).
void FireGaugeExplosion(CKHkS08ElectricGauge* gauge, IKSerializable* data, const CVector3& at) {
    CKExplosionNodeFx* explosion = static_cast<CKExplosionNodeFx*>(AcquireFx(data, gauge));
    if (explosion == nullptr) return;
    explosion->SetTranslation(&at, gauge);  // 0x001b66e8
    explosion->Trigger(gauge, 0);           // 0x001b82a8 (r5 0, r6 0)
    explosion->ReleaseReservation(gauge);   // vt+0x54
}
}  // namespace

// 0x00492810 CKHkS08ElectricGauge_UpdateArcEndpoints_maybe
void CKHkS08ElectricGauge::UpdateArcEndpoints() {
    CVector3 from;
    CVector3 to;
    if (m_apUnk24[2] != nullptr) {
        static_cast<CSGHotSpot*>(m_apUnk24[2])->GetWorldPosition(&from);  // 0x000ce790
    } else {
        const RwV3d& p = FrameLtm(static_cast<CSGMovable*>(m_pKGLObject)->m_pRwFrame)->pos;
        from = {p.x, p.y, p.z};
    }
    if (m_apUnk24[3] != nullptr) {
        static_cast<CSGHotSpot*>(m_apUnk24[3])->GetWorldPosition(&to);
    } else {
        const RwV3d& p = FrameLtm(static_cast<CSGMovable*>(m_pKGLObject)->m_pRwFrame)->pos;
        to = {p.x, p.y, p.z};
    }
    for (IKSerializable* fx : m_unk3c) {
        if (fx == nullptr) continue;
        static_cast<CKElectricArcNodeFx*>(fx)->SetStartPoint(&from, this);  // 0x001b1f80
        static_cast<CKElectricArcNodeFx*>(fx)->SetEndPoint(&to, this);      // 0x001b1f40
    }
}

// 0x00494a50 CKHkS08ElectricGauge_TriggerTopReachedFx_maybe
void CKHkS08ElectricGauge::TriggerTopReachedFx() {
    const CVector3 at = GaugeFxPoint(this, m_apUnk24[2]);
    FireGaugeExplosion(this, m_apUnk44[1], at);
}

// 0x004944e8 CKHkS08ElectricGauge_TriggerBottomReachedFx_maybe
void CKHkS08ElectricGauge::TriggerBottomReachedFx() {
    const CVector3 first = GaugeFxPoint(this, m_apUnk24[2]);
    FireGaugeExplosion(this, m_apUnk44[0], first);
    const CVector3 second = GaugeFxPoint(this, m_apUnk24[3]);
    FireGaugeExplosion(this, m_apUnk44[0], second);
}

// 0x00495490 CKHkS08ElectricGauge_TriggerRandomSparkFx_maybe (no draw of its own: Update draws the interval)
void CKHkS08ElectricGauge::TriggerRandomSparkFx() {
    const CVector3 first = GaugeFxPoint(this, m_apUnk24[2]);
    FireGaugeExplosion(this, m_apUnk44[2], first);
    const CVector3 second = GaugeFxPoint(this, m_apUnk24[3]);
    FireGaugeExplosion(this, m_apUnk44[2], second);
}

// 0x00495120 CKHkS08ElectricGauge_UpdateLevel_maybe (state 0, a hero holds the gauge). Entering or leaving does nothing.
// The holder's hot spot 0x12 is read (its world position, unused). The acceleration is (0, -+0xa0 * +0x78, 0) (the grab
// weight pulls it down); a zero acceleration stops the gauge (velocity zero), otherwise the velocity integrates it; the
// position integrates the velocity (fmadds). Above the hot spot +0x24: held there, stopped, and when the node was not
// there yet the top effect and the starter +0xb4. Below +0x28: held there, stopped, and when the node was not there yet
// the bottom effect, the node placed and state 2. The node (+0x20) takes the position.
uint8_t CKHkS08ElectricGauge::State0Held(IKTime* clock, int32_t phase, uint8_t other) {
    if (phase != 0) return other;
    static const float kNull[3] = {0.0f, 0.0f, 0.0f};  // TOC +0x5f60: 0x00c50d64
    CVector3 unused;
    static_cast<CSGHotSpot*>(static_cast<CKHkS08Hero*>(m_unk70)->GetHotSpot(0x12))->GetWorldPosition(&unused);  // 0x00361b70
    float* const position = &m_unk78[1];      // +0x7c
    float* const velocity = &m_unk78[4];      // +0x88
    float* const acceleration = &m_unk78[7];  // +0x94
    const float pull = m_unkA0 * m_unk78[0];
    acceleration[0] = 0.0f;  // TOC +0x5fb4
    acceleration[2] = 0.0f;
    const float side = pull * 0.0f;
    acceleration[1] = -pull;
    float vy;
    float vz;
    if (side == kNull[0] && kNull[1] == -pull && kNull[2] == side) {
        velocity[0] = kNull[0];
        velocity[2] = kNull[2];
        velocity[1] = kNull[1];
        vy = kNull[1];
        vz = velocity[2];
    } else {
        const float dt = clock->m_afDeltaTime[0];
        const float vx = ppc::fmadds(dt, acceleration[0], velocity[0]);
        vz = ppc::fmadds(dt, acceleration[2], velocity[2]);
        vy = ppc::fmadds(dt, acceleration[1], velocity[1]);
        velocity[0] = vx;
        velocity[2] = vz;
        velocity[1] = vy;
    }
    const float dt = clock->m_afDeltaTime[0];
    position[0] = ppc::fmadds(dt, velocity[0], position[0]);
    position[2] = ppc::fmadds(dt, vz, position[2]);
    position[1] = ppc::fmadds(dt, vy, position[1]);
    CVector3 stop;
    auto halt = [&]() {
        for (int i = 0; i < 3; ++i) velocity[i] = kNull[i];
        for (int i = 0; i < 3; ++i) acceleration[i] = kNull[i];
    };
    auto place = [&]() {
        RwFrame* frame = static_cast<CSGMovable*>(m_unk20)->m_pRwFrame;
        frame->modelling.pos.z = position[2];
        frame->modelling.pos.x = position[0];
        frame->modelling.pos.y = position[1];
        frame->modelling.flags &= 0xfffdffffu;
        RwFrame_MarkDirty(frame);  // 0x00010698
    };
    if (m_apUnk24[0] != nullptr) {
        static_cast<CSGHotSpot*>(m_apUnk24[0])->GetWorldPosition(&stop);
        if (position[1] > stop.y) {  // bgt
            position[1] = stop.y;
            halt();
            if (static_cast<CSGMovable*>(m_unk20)->m_pRwFrame->modelling.pos.y != stop.y) {
                TriggerTopReachedFx();          // 0x00494a50
                QueueTriggerSignals(&m_unkB4);  // 0x00236338
            }
        }
    }
    if (m_apUnk24[1] != nullptr) {
        static_cast<CSGHotSpot*>(m_apUnk24[1])->GetWorldPosition(&stop);
        if (!(position[1] >= stop.y)) {  // bge: NaN stays
            position[1] = stop.y;
            halt();
            if (static_cast<CSGMovable*>(m_unk20)->m_pRwFrame->modelling.pos.y != stop.y) {
                TriggerBottomReachedFx();  // 0x004944e8
                place();
                return 2;
            }
        }
    }
    place();
    return other;
}

// 0x00492d40 CKHkS08ElectricGauge_State2_Wait_maybe: enter: the wait time cleared. Tick: it grows by the frame; at +0x64
// state 0 while a hero holds the gauge, else state 1 ((abs(p) - 1) >> 31 of the holder pointer).
uint8_t CKHkS08ElectricGauge::State2Wait(IKTime* clock, int32_t phase, uint8_t other) {
    if (phase == 0) {
        const float time = m_fWaitTime + clock->m_afDeltaTime[0];
        m_fWaitTime = time;
        if (m_unk64 <= time) return m_unk70 == nullptr ? 1 : 0;
        return other;
    }
    if (phase == 1) m_fWaitTime = 0.0f;
    return other;
}

// 0x00492ea8 CKHkS08ElectricGauge_vf100: the grab hot spot's (+0x30) world position, the null vector (0x00c50d64) without one.
CVector3 CKHkS08ElectricGauge::GetGrabHotSpotPosition() {
    CSGHotSpot* hotSpot = static_cast<CSGHotSpot*>(m_apUnk24[3]);
    if (hotSpot == nullptr) return CVector3{0.0f, 0.0f, 0.0f};
    if (m_unk20 != nullptr) {
        static_cast<CSGMovable*>(m_unk20)->ForceWorldMatrixUpdate();  // vt+0x50
        hotSpot = static_cast<CSGHotSpot*>(m_apUnk24[3]);
    }
    CVector3 position;
    hotSpot->GetWorldPosition(&position);  // 0x000ce790
    return position;
}
