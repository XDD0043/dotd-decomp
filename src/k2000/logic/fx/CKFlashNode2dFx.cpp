// CKFlashNode2dFx.cpp - reconstructed original translation unit 0x1bc520-0x1be2a0 (GAME_TOC1, main_toc1), 21 functions, 17 live.
// Primary class: CKFlashNode2dFx  key 0x15cc  category Logic  size 0x7c  vtable 0xb1cd68
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x1bc520  CKFlashNode2dFx_Delete
//   [x] 0x1bc570  CKFlashNode2dFx_Destroy
//   [ ] 0x1bc578  FUN_001bc578  [dead]
//   [ ] 0x1bc610  FUN_001bc610  [dead]
//   [x] 0x1bc638  CKFlashNode2dFx_Stop
//   [x] 0x1bc6d8  CKFlashNode2dFx_PostLoad  (the PostLoad above)
//   [ ] 0x1bc728  RegisterCKFlashNode2dFxClass
//   [ ] 0x1bc7a0  _GLOBAL__I_1bc7a0
//   [ ] 0x1bc7b0  FUN_001bc7b0  [dead]
//   [ ] 0x1bc8b0  CKFlashNode2dFx_MoveTowardTarget_maybe  [dead]
//   [x] 0x1bca10  CKFlashNode2dFx_Load
//   [ ] 0x1bca38  CKFlashNode2dFx_Save
//   [x] 0x1bca60  CKFlashNode2dFx_RecursiveRegistration
//   [x] 0x1bcae0  CKFlashNode2dFx_DeleteArray
//   [x] 0x1bcb88  CKFlashNode2dFx_Create
//   [x] 0x1bcbf0  CKFlashNode2dFx_CreateArray
//   [x] 0x1bccc8  CKFlashNode2dFx_Start
//   [x] 0x1bcf30  CKFlashNode2dFx_State0
//   [x] 0x1bd4a0  CKFlashNode2dFx_State2
//   [x] 0x1bda30  CKFlashNode2dFx_State1
//   [x] 0x1bdd68  CKFlashNode2dFx_Update
//
//   [ ] 0x9ac278  CKFlashNode2dFx_IsKindOfClass  [inline]
//   [x] 0x9ac2b0  CKFlashNode2dFx_GetClassType  [inline]
//   [x] 0x9ac2b8  CKFlashNode2dFx_GetClassID  [inline]
//   [ ] 0x9ac2c0  CKFlashNode2dFx_GetFxData  [inline]
//   [ ] 0x9ac2c8  CKFlashNode2dFx_SetFxData  [inline]
//   [ ] 0x9ac2d0  CKFlashNode2dFx_DeletingDestruct  [inline]
//   [ ] 0x9ac318  CKFlashNode2dFx_Destruct  [inline]
#include "k2000/logic/fx/CKFlashNode2dFx.h"

#include <cmath>
#include <cstring>

#include "Renderware/rwcore/RwMatrix.h"
#include "crt/ppc_ops.h"
#include "k2000/graphical/fx/CBillboard2d.h"
#include "k2000/logic/fx/CKFlashFxData.h"
#include "k2000/logic/CKSavingManager.h"
#include "k2000/misc/ClassRegistry.h"
#include "k2000/misc/Engine.h"
#include "k2000/system/IKTime.h"

// Inlined in 0x001bcb88 CKFlashNode2dFx_Create (+0x61 is stored first).
CKFlashNode2dFx::CKFlashNode2dFx() {
    m_unk61 = 0xff;
    m_unk60 = 0xff;
}

// 0x001bca10 CKFlashNode2dFx_Load
int32_t CKFlashNode2dFx::Load(IKFile* file, int32_t type) {
    IKNode2dFx::Load(file, type);
    return 1;
}

// 0x001bc6d8 CKFlashNode2dFx_PostLoad: the three states (their handlers' descriptors 0xb6f388 / 0xb6f398 / 0xb6f390,
// here the indices 0 / 1 / 2), no current state (0xff), three of them.
int32_t CKFlashNode2dFx::PostLoad(int32_t /*type*/) {
    for (uint32_t i = 0; i < 3; ++i) {
        m_aStates[i].m_handler = nullptr;
        m_aStates[i].m_value = 0;
    }
    m_pCurState = &m_aStates[0];
    m_unk60 = 0xff;
    m_unk61 = 3;
    return 1;
}

// 0x001bccc8 CKFlashNode2dFx_Start: reserved and running (+0x0c bit 1, bit 0 cleared); the size from the data
// (+0x34); one draw spreads the position (+0x14 + the spread x +0x24) and its target (+0x1c + the same) alike; the
// rotation from +0x4c; no current state, the scene node shown (vt+0x5c). STUB(C2.8): the billboard's texture, size
// and colour (pixels only).
void CKFlashNode2dFx::Vf64() {
    m_baFxData = static_cast<uint8_t>((m_baFxData & 0xfc) | 2);
    const CKFlashFxData* data = m_pFlashData;
    m_afSize[0] = data->m_unk34[0];
    m_afSize[1] = data->m_unk34[1];
    const uint32_t r = static_cast<uint32_t>(Rand_Int()) & 0xffffu;  // 0x00011500
    const float spread = ppc::fmadds(static_cast<float>(static_cast<double>(r)), -3.05180438e-05f, 1.0f);  // TOC -0x1fe8 / -0x1fe4
    const float dx = spread * data->m_unk24[0];
    const float dy = spread * data->m_unk24[1];
    m_afPos[0] = dx + data->m_unk14[0];
    m_afPos[1] = dy + data->m_unk14[1];
    m_afTargetPos[0] = dx + data->m_unk1c[0];
    m_afTargetPos[1] = dy + data->m_unk1c[1];
    std::memcpy(&m_fRotation, &data->m_unk4c, 4);  // the word as stored
    m_unk60 = 0xff;
}

// 0x001bc638 CKFlashNode2dFx_Stop: stopped, not reserved; the node's billboard (the CBillboard2d's IKBillboard2d base,
// +0x28) gets a new brush (vt+0x40 BillboardBrush_RecreateBrush_maybe) and the node leaves the 2D scene (vt+0x60).
void CKFlashNode2dFx::Stop() {
    m_baFxData = static_cast<uint8_t>((m_baFxData & 0xfc) | 1);
    static_cast<IKBillboard2d*>(static_cast<CBillboard2d*>(m_pNode))->RecreateBrush();  // vt+0x40 (no null test)
    Vf60();                                                                              // vt+0x60
}

namespace {
// The data's durations: fade in (+0x54), hold (+0x5c), fade out (+0x60).
bool Positive(float value) { return value > 0.0f; }  // TOC -0x2018 (0.0): "<= 0" is the original's test
}  // namespace

// The colour fade of states 0 and 2: the colour (+0x44, its float copy +0x4c) moves towards the target (+0x40) by
// dt x rate x 255 (TOC -0x1fcc) along the 4D difference, or takes it when closer.
void CKFlashNode2dFx::FadeColour(float dt) {
    if (std::memcmp(m_aColour, m_aTargetColour, 4) == 0) return;
    const float d1 = static_cast<float>(static_cast<double>(m_aTargetColour[1])) - m_afColour[1];
    const float d0 = static_cast<float>(static_cast<double>(m_aTargetColour[0])) - m_afColour[0];
    const float d2 = static_cast<float>(static_cast<double>(m_aTargetColour[2])) - m_afColour[2];
    const float d3 = static_cast<float>(static_cast<double>(m_aTargetColour[3])) - m_afColour[3];
    const float step = (dt * m_fFadeRate) * 255.0f;
    const float length2 = ppc::fmadds(d3, d3, ppc::fmadds(d2, d2, ppc::fmadds(d0, d0, d1 * d1)));
    if (!(step * step <= length2)) {
        std::memcpy(m_aColour, m_aTargetColour, 4);
        return;
    }
    const float scale = step * rwInvSqrt(length2);  // Math_InvSqrtf 0x114d8
    m_afColour[0] = ppc::fmadds(d0, scale, m_afColour[0]);
    m_afColour[3] = ppc::fmadds(d3, scale, m_afColour[3]);
    m_afColour[1] = ppc::fmadds(d1, scale, m_afColour[1]);
    m_afColour[2] = ppc::fmadds(d2, scale, m_afColour[2]);
    for (int i = 0; i < 4; ++i) m_aColour[i] = static_cast<uint8_t>(ppc::fctiwz(m_afColour[i]));
}

namespace {
// 0x00010690 Math_Sqrtf: the double square root rounded to float.
inline float Sqrtf(float x) { return static_cast<float>(std::sqrt(static_cast<double>(x))); }
}  // namespace

// The moves the three states share, each enabled by its state's bit (`mask`) of a data flag byte: the size (+0x14)
// towards the data's +0x3c at the rates +0x44 / +0x48 (flags +0x11; it takes the target when within 1e-5 squared,
// TOC -0x201c), the rotation (+0x30) by the rate +0x30 (flags +0x10; not when the rate is 0), the position (+0x1c)
// towards its target (+0x34) at the speed +0x2c (flags +0x12; it takes the target when closer than a step).
void CKFlashNode2dFx::MoveSizeRotationPosition(float dt, uint8_t mask) {
    const CKFlashFxData* data = m_pFlashData;
    if ((data->m_unk11 & mask) != 0) {
        if (m_afSize[0] != data->m_unk3c[0] || m_afSize[1] != data->m_unk3c[1]) {
            m_afSize[1] = ppc::fmadds(dt, data->m_unk44[1], m_afSize[1]);
            m_afSize[0] = ppc::fmadds(dt, data->m_unk44[0], m_afSize[0]);
            const float dy = m_afSize[1] - data->m_unk3c[1];
            const float dx = m_afSize[0] - data->m_unk3c[0];
            if (ppc::fmadds(dx, dx, dy * dy) < 1e-05f) {  // bge skips: NaN keeps the moved size
                m_afSize[0] = data->m_unk3c[0];
                m_afSize[1] = data->m_unk3c[1];
            }
        }
    }
    data = m_pFlashData;
    if ((data->m_unk10 & mask) != 0 && data->m_unk30 != 0.0f) m_fRotation = ppc::fmadds(dt, data->m_unk30, m_fRotation);
    if ((data->m_unk12 & mask) == 0) return;
    if (m_afPos[0] == m_afTargetPos[0] && m_afPos[1] == m_afTargetPos[1]) return;
    float dy = m_afTargetPos[1] - m_afPos[1];
    float dx = m_afTargetPos[0] - m_afPos[0];
    float length = Sqrtf(ppc::fmadds(dx, dx, dy * dy));
    if (length != 0.0f) {
        const float inverse = 1.0f / length;  // TOC -0x1fe4
        dy = dy * inverse;
        dx = dx * inverse;
    } else {
        length = 0.0f;
    }
    const float step = dt * m_pFlashData->m_unk2c;
    if (length < step) {  // bge moves: NaN moves
        m_afPos[0] = m_afTargetPos[0];
        m_afPos[1] = m_afTargetPos[1];
        return;
    }
    m_afPos[0] = ppc::fmadds(dx, step, m_afPos[0]);
    m_afPos[1] = ppc::fmadds(dy, step, m_afPos[1]);
}

// The billboard's colour (IKBillboard2d vt+0x28 SetColor, with a copy of the word).
void CKFlashNode2dFx::SetBillboardColour(const uint8_t* colour) {
    uint8_t copy[4];
    std::memcpy(copy, colour, 4);
    static_cast<IKBillboard2d*>(static_cast<CBillboard2d*>(m_pNode))->SetColor(copy);
}

// 0x001bcf30 CKFlashNode2dFx_State0 (fade in), 0x001bda30 _State1 (hold), 0x001bd4a0 _State2 (fade out): phase 1
// enters, 0 ticks (returns the next state), 2 leaves (nothing). Each state moves the size, rotation and position with its
// own bit of the data's flag bytes (bit 0 / 1 / 2).
uint8_t CKFlashNode2dFx::RunState(uint8_t state, float dt, int32_t phase, uint8_t other) {
    const CKFlashFxData* data = m_pFlashData;
    if (state == 0 || state == 2) {
        if (phase == 1) {
            std::memcpy(m_aColour, data->m_Color, 4);
            std::memcpy(m_aTargetColour, data->m_Color, 4);
            if (state == 0) {
                m_aColour[3] = 0;  // from transparent to the data's colour
            } else {
                m_aTargetColour[3] = 0;  // from the data's colour to transparent
            }
            for (int i = 0; i < 4; ++i) m_afColour[i] = static_cast<float>(static_cast<double>(m_aColour[i]));
            m_fFadeRate = (state == 0 ? data->m_unk58 : data->m_unk64) / 255.0f;
            SetBillboardColour(m_aColour);
            return other;
        }
        if (phase != 0) return other;
        FadeColour(dt);
        SetBillboardColour(m_aColour);
        MoveSizeRotationPosition(dt, state == 0 ? 1 : 4);
        data = m_pFlashData;
        if (state == 0) {
            if (m_aColour[3] < m_aTargetColour[3]) return other;
            if (Positive(data->m_unk5c)) return 1;
            if (Positive(data->m_unk60)) return 2;
            Stop();  // vt+0x6c
            return 0xff;
        }
        if (m_aColour[3] != m_aTargetColour[3]) return other;
        Stop();
        return 0xff;
    }
    if (phase == 1) {
        SetBillboardColour(data->m_Color);
        m_fHoldTime = 0.0f;
        return other;
    }
    if (phase != 0) return other;
    m_fHoldTime = m_fHoldTime + dt;
    MoveSizeRotationPosition(dt, 2);
    data = m_pFlashData;
    if (data->m_unk5c < m_fHoldTime) {
        if (!Positive(data->m_unk60)) {
            Stop();
            return 0xff;
        }
        return 2;
    }
    return other;
}

// 0x001bdd68 CKFlashNode2dFx_Update: without a state the first one with a duration starts (fade in +0x54, hold +0x5c,
// fade out +0x60; none: Stop), then the state ticks and a new state leaves the old one and enters. STUB(C2.8): the
// billboard's size, position and rotation.
void CKFlashNode2dFx::Update(IKTime* frameClock) {
    const float dt = frameClock->m_afDeltaTime[IKTime::SCALABLE_GAME_TIME];  // +0x1c
    const CKFlashFxData* data = m_pFlashData;
    if (m_unk60 == 0xff) {
        uint8_t first;
        if (Positive(data->m_unk54)) {
            first = 0;
        } else if (Positive(data->m_unk5c)) {
            first = 1;
        } else if (Positive(data->m_unk60)) {
            first = 2;
        } else {
            Stop();
            first = 0xff;
        }
        if (first != 0xff) {
            m_unk60 = first;
            RunState(first, dt, 1, 0xff);
        }
    }
    const uint8_t state = m_unk60;
    if (state == 0xff) return;
    const uint8_t next = RunState(state, dt, 0, state);
    const uint8_t was = m_unk60;
    if (next == was) return;
    if (was != 0xff) RunState(was, dt, 2, next);
    m_unk60 = next;
    if (next != 0xff) RunState(next, dt, 1, was);
}

// 0x001bca60 CKFlashNode2dFx_RecursiveRegistration: registered with the saving manager (vt+0x24, no owner), then
// IKNode2dFx's (0x1d8518 CKNode2dFx_LevelReset): the node's own registration (its vt+0x24) when there is one.
void CKFlashNode2dFx::RecursiveRegistration(int32_t type) {
    g_pEngine->m_pSavingManager->RegisterSerializableObject(this, nullptr);  // vt+0x24
    IKNode2dFx::RecursiveRegistration(type);
}
