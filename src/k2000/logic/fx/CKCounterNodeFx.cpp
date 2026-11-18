// CKCounterNodeFx.cpp - reconstructed original translation unit 0x575810-0x5774e8 (GAME_TOC2, main_toc2), 28 functions, 25 live.
// Primary class: CKCounterNodeFx  key 0x590c  category Logic  size 0x68  vtable 0xb2dfa0
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x575810  CKCounterNodeFx_Delete  (DOTD_DECLARE_FACTORIES)
//   [ ] 0x575860  CKCounterNodeFx_EvaluateKeyCurve_maybe  [dead]
//   [x] 0x575918  CKCounterNodeFx_EnterState2_maybe  (EnterFadeOut)
//   [ ] 0x575a60  RegisterCKCounterNodeFxClass
//   [ ] 0x575ad8  _GLOBAL__I_575ad8
//   [ ] 0x575ae8  CKCounterNodeFx_Save
//   [x] 0x575b10  CKCounterNodeFx_RecursiveRegistration
//   [x] 0x575b38  CKCounterNodeFx_DeleteArray  (DOTD_DECLARE_FACTORIES)
//   [x] 0x575bd8  CKCounterNodeFx_Construct_2  (the constructor)
//   [x] 0x575c30  CKCounterNodeFx_Construct  (the constructor)
//   [ ] 0x575c88  FUN_00575c88  [dead]
//   [x] 0x575d80  CKCounterNodeFx_Destroy
//   [x] 0x575e00  FUN_00575e00  (SetParticlesEmitting, here)
//   [x] 0x575ea8  CKCounterNodeFx_SetAlpha_maybe
//   [x] 0x576028  CKCounterNodeFx_CreateArray  (DOTD_DECLARE_FACTORIES; the constructor)
//   [x] 0x5760f8  CKCounterNodeFx_Create  (DOTD_DECLARE_FACTORIES; the constructor)
//   [x] 0x576160  CKCounterNodeFx_Load
//   [x] 0x576458  CKCounterNodeFx_ResetDisplay_maybe
//   [x] 0x5764c8  CKCounterNodeFx_Stop
//   [x] 0x5765d8  CKCounterNodeFx_Update
//   [x] 0x576d68  CKCounterNodeFx_InitStateMachine_maybe
//   [x] 0x576ec8  CKCounterNodeFx_Start
//   [ ] 0x5771e8  CKCounterNodeFx_Destruct_2  [dead]
//   [x] 0x577208  CKCounterNodeFx_DeletingDestruct  (the destructor; delete)
//   [x] 0x577250  CKCounterNodeFx_Destruct  (the destructor)
//   [x] 0x577270  KStub_Return1_577270  (state 1, StateShown)
//   [x] 0x577278  CKCounterNodeFx_State2_FadeOut_maybe  (StateFadeOut)
//   [x] 0x5773d8  CKCounterNodeFx_State0_FadeIn_maybe  (StateFadeIn)
//
//   [x] 0x9caeb0  CKCounterNodeFx_IsKindOfClass  [inline]  (CKCounterNodeFx.h)
//   [x] 0x9caee8  CKCounterNodeFx_GetClassType  [inline]  (DOTD_CLASS_KEY)
//   [x] 0x9caef0  CKCounterNodeFx_GetClassID  [inline]  (DOTD_CLASS_KEY)
//   [x] 0x9caef8  CKCounterNodeFx_GetFxData  [inline]
//   [x] 0x9caf00  CKCounterNodeFx_SetFxData  [inline]
//
// C2.8 port-final F04: in no level file of the game; ported from the disassembly (port-rest R06's analysis).
#include "k2000/logic/fx/CKCounterNodeFx.h"

#include <cstring>
#include <vector>

#include "Renderware/rpprtstd/RpPrtStd.h"
#include "Renderware/rwcore/RwCamera.h"
#include "crt/ppc_ops.h"
#include "crt/xtanf.h"
#include "k2000/cameras/CameraContext.h"
#include "k2000/cameras/CKSrvCamera.h"
#include "k2000/geometry/CGeometry.h"
#include "k2000/io/IKFile.h"
#include "k2000/logic/CKLevel.h"
#include "k2000/logic/CKSector.h"
#include "k2000/logic/fx/CKCounterFxData.h"
#include "k2000/logic/render/CMaterial.h"
#include "k2000/math/CurveKeys.h"
#include "k2000/math/Math.h"
#include "k2000/misc/Engine.h"
#include "k2000/scenegraph/CNode.h"
#include "k2000/scenegraph/CParticlesNodeFx.h"
#include "k2000/scenegraph/CSGSectorRoot.h"
#include "k2000/system/IKTime.h"

namespace {

const CVector3 kAxisY = {0.0f, 1.0f, 0.0f};  // 0x00c50d40 (TOC2 -0x74e0)
constexpr float kZero = 0.0f;                // TOC2 -0x751c / -0x7494
constexpr float kOne = 1.0f;                 // TOC2 -0x7520
constexpr float kMaxScale = 10.0f;           // TOC2 -0x74dc (0x41200000)
constexpr float kDegToRad = 0x1.1df468p-6f;  // TOC2 -0x74d8 (0x3c8efa34)
constexpr float kHalf = 0.5f;                // TOC2 -0x74d4
constexpr float kAlphaMax = 255.0f;          // TOC2 -0x7498 (0x437f0000)
constexpr float kMinusAlphaMax = -255.0f;    // TOC2 -0x749c (0xc37f0000)

CGeometry* FirstGeometry(CNode* node) { return static_cast<CGeometry*>(node->m_lGeometryList); }

// 0x00575e00 FUN_00575e00 (the particle node's message 0x1a00 / 0x1a01 inlined, with the hidden bit): hidden unless
// `emit`; `show`: shown (0x200) and emitting (0x400); else emitting follows `emit`; 0x80000 cleared. Emitting or shown:
// the speed adjustment 0 and the emitter active and emitting (0xa); else the emitter's emit flag (0x8) off.
void SetParticlesEmitting(CParticlesNodeFx* node, uint8_t emit, int32_t show) {
    const uint32_t hidden = (node->m_sgProperties & ~4u) | ((static_cast<uint32_t>(emit) ^ 1u) << 2);
    node->m_sgProperties = hidden;
    if (show != 0) {
        node->m_sgProperties = (hidden | 0x200u | 0x400u) & ~0x80000u;
    } else {
        node->m_sgProperties = ((hidden & ~0x400u) | (static_cast<uint32_t>(emit) << 10)) & ~0x80000u;
        if (emit == 0) {
            node->m_pRpPrtStdEmitter->flag &= ~8u;
            return;
        }
    }
    node->m_fEmissionSpeedAdjustment = 0.0f;  // stw 0
    node->m_pRpPrtStdEmitter->flag |= 0xau;
}

// The particle node's start (inlined in Start / ResetDisplay): the given bits cleared and 0x400 set, 0x80000 cleared; the
// speed adjustment 0, the emitter active and emitting.
void StartParticles(CParticlesNodeFx* node, uint32_t clear, uint32_t set) {
    node->m_sgProperties = ((node->m_sgProperties & ~clear) | set) & ~0x80000u;
    node->m_fEmissionSpeedAdjustment = 0.0f;
    node->m_pRpPrtStdEmitter->flag |= 0xau;
}

// The particle node's stop (inlined in Stop): hidden, emitting (0x400) and 0x80000 off, the emitter's emit flag off.
void StopParticles(CParticlesNodeFx* node) {
    node->m_sgProperties = ((node->m_sgProperties & ~4u) | 4u) & 0xfff7fbffu;
    node->m_pRpPrtStdEmitter->flag &= ~8u;
}

// A leaf moved under `parent` (vt+0x78 from its parent, vt+0x70 to the new one).
void Reparent(CSGBranch* parent, CSGLeaf* child) {
    if (child->m_pParent != nullptr) child->m_pParent->RemoveChild(child);
    parent->AddChild(child);
}

// 0x005773d8 CKCounterNodeFx_State0_FadeIn_maybe: the alpha rises to 255 over the data's fade-in time, then state 1.
uint8_t StateFadeIn(CKCounterNodeFx* node, IKTime* frameClock, int32_t event, uint8_t /*other*/) {
    if (event == 0) {
        const float time = node->m_pData->m_fFadeInTime;
        if (!(time > node->m_fFadeTime)) {  // bgt: a NaN ends the fade
            node->SetAlpha(kAlphaMax);
            return 1;
        }
        node->SetAlpha((node->m_fFadeTime / time) * kAlphaMax);
        node->m_fFadeTime = node->m_fFadeTime + frameClock->m_afDeltaTime[0];
        return 0;
    }
    if (event == 1) node->m_fFadeTime = 0.0f;  // stw 0
    return 0;
}

// 0x00577270 KStub_Return1_577270: state 1 stays.
uint8_t StateShown(CKCounterNodeFx* /*node*/, IKTime* /*frameClock*/, int32_t /*event*/, uint8_t /*other*/) { return 1; }

// 0x00577278 CKCounterNodeFx_State2_FadeOut_maybe: on entering, the start particles stop; the alpha falls to 0 over the
// data's fade-out time, then the node is stopped and released for its owner (vt+0x58) and the machine has no state.
uint8_t StateFadeOut(CKCounterNodeFx* node, IKTime* frameClock, int32_t event, uint8_t /*other*/) {
    if (event == 0) {
        const float time = node->m_pData->m_fFadeOutTime;
        if (!(time > node->m_fFadeTime)) {
            node->SetAlpha(kZero);
            node->StopAndRelease(node->m_pReleaseOwner);  // vt+0x58
            return 0xff;
        }
        node->SetAlpha(ppc::fmadds(node->m_fFadeTime / time, kMinusAlphaMax, kAlphaMax));
        node->m_fFadeTime = node->m_fFadeTime + frameClock->m_afDeltaTime[0];
        return 2;
    }
    if (event == 1) {
        node->m_fFadeTime = 0.0f;
        SetParticlesEmitting(node->m_pStartParticles, 0, 0);  // 0x00575e00
    }
    return 2;
}

}  // namespace

CKCounterNodeFx::CKCounterNodeFx() {
    m_ui8NbStates = 0xff;
    m_ui8State = 0xff;
}
CKCounterNodeFx::~CKCounterNodeFx() {}

IKFxData* CKCounterNodeFx::GetFxData() { return m_pData; }  // 0x009caef8
void CKCounterNodeFx::SetFxData(IKFxData* data) { m_pData = static_cast<CKCounterFxData*>(data); }  // 0x009caf00

// 0x00575d80 CKCounterNodeFx_Destroy. The pointers are kept (as the original).
void CKCounterNodeFx::Destroy() {
    IKNodeFx::Destroy();
    if (m_pTexture18 != nullptr) TextureRef_Release(m_pTexture18);  // RwTextureDestroy
    if (m_pTexture1c != nullptr) TextureRef_Release(m_pTexture1c);
    if (m_aPulseKeys != nullptr) delete[] m_aPulseKeys;  // OperatorDeleteArray(keys - 4)
}

// 0x00575b10 CKCounterNodeFx_RecursiveRegistration
void CKCounterNodeFx::RecursiveRegistration(int32_t type) { IKNodeFx::RecursiveRegistration(type); }

// 0x00576160 CKCounterNodeFx_Load: IKNodeFx's; level files: the gauge and the two particle nodes, the two textures, the
// pulse keys (a count, then count x (time, value), one read, each word swapped) and the pulse duration.
int32_t CKCounterNodeFx::Load(IKFile* file, int32_t type) {
    IKNodeFx::Load(file, type);
    if (type != K_LEVEL_PLATEFORMS) return 1;
    IKFile_ReadRef(file, &m_pGauge);
    IKFile_ReadRef(file, &m_pStartParticles);
    IKFile_ReadRef(file, &m_pPulseParticles);
    IKFile_ReadTextureRef(file, reinterpret_cast<void**>(&m_pTexture18), 1);
    IKFile_ReadTextureRef(file, reinterpret_cast<void**>(&m_pTexture1c), 1);
    ReadU32LE(file, &m_ui32NbPulseKeys);
    if (m_ui32NbPulseKeys == 0) {
        m_aPulseKeys = nullptr;
    } else {
        m_aPulseKeys = new PulseKey[m_ui32NbPulseKeys];  // OperatorNewArray(count * 8 + 4)
        std::vector<uint32_t> words(m_ui32NbPulseKeys * 2u);
        ReadU32LEWords(file, words.data(), m_ui32NbPulseKeys * 2u);
        std::memcpy(m_aPulseKeys, words.data(), words.size() * sizeof(uint32_t));
    }
    ReadF32LE(file, &m_fPulseDuration);
    return 1;
}

// 0x00575ea8 CKCounterNodeFx_SetAlpha_maybe: the gauge's geometries' colour alpha (+0x23) and their alpha-blended bit
// (11, vt+0x60 when it changes); 0xff clears the bit everywhere; a geometry with property 0x1000 and a material of mode
// 1..6 keeps 0xff and the bit cleared.
void CKCounterNodeFx::SetAlpha(float alpha) {
    CGeometry* geometry = FirstGeometry(m_pGauge);
    if (geometry == nullptr) return;
    const uint8_t value = static_cast<uint8_t>(static_cast<uint32_t>(ppc::fctiwz(alpha)) & 0xffu);  // fctiwz, lbz +3
    if (value == 0xff) {
        for (; geometry != nullptr; geometry = geometry->m_pNext) {
            geometry->m_cGeometryColor[3] = 0xff;
            const uint32_t bits = geometry->m_BitProperties;
            if (((bits >> 11) & 1u) != 0) {
                geometry->m_BitProperties = bits & 0xfffff7ffu;
                geometry->UpdateProperties();  // vt+0x60
            }
        }
        return;
    }
    for (; geometry != nullptr; geometry = geometry->m_pNext) {
        uint32_t blend = 1;
        uint8_t byte = value;
        if ((geometry->m_BitProperties & 0x1000u) != 0) {
            const int32_t mode = static_cast<int32_t>((static_cast<CMaterial*>(geometry->m_pMaterial)->m_baProperties >> 3) & 0xfu);
            if (mode > 0 && mode <= 6) {
                blend = 0;
                byte = 0xff;
            }
        }
        geometry->m_cGeometryColor[3] = byte;
        const uint32_t bits = geometry->m_BitProperties;
        if (((bits >> 11) & 1u) != blend) {
            geometry->m_BitProperties = (bits & 0xfffff7ffu) | (blend << 11);
            geometry->UpdateProperties();  // vt+0x60
        }
    }
}

// The machine's state switch (inlined): the old state (when there is one) told it is left for `next`, `next` set, then
// (when it is a state) told it is entered from the old one.
void CKCounterNodeFx::SwitchState(uint8_t next, IKTime* frameClock) {
    const uint8_t old = m_ui8State;
    if (old != 0xff) m_pStates[old].m_pfn(this, frameClock, 2, next);
    m_ui8State = next;
    if (next != 0xff) m_pStates[next].m_pfn(this, frameClock, 1, old);
}

// 0x00575918 CKCounterNodeFx_EnterState2_maybe
void CKCounterNodeFx::EnterFadeOut(IKSerializable* owner) {
    m_pReleaseOwner = owner;
    SwitchState(2, nullptr);
}

// 0x00576458 CKCounterNodeFx_ResetDisplay_maybe: the pulse from 0 (bit 0 on); the pulse particles shown and emitting.
void CKCounterNodeFx::ResetDisplay() {
    m_fPulseTime = 0.0f;  // stw 0
    m_flags44 = static_cast<uint8_t>((m_flags44 & 0xfe) | 1);
    StartParticles(m_pPulseParticles, 0x204u, 0x600u);
}

// 0x005764c8 CKCounterNodeFx_Stop: stopped; both particle nodes stopped; the gauge hidden and taken out of its parent.
// BUG(original): without a gauge its parent is read at address 0x0c.
void CKCounterNodeFx::Stop() {
    m_baFxData = static_cast<uint8_t>((m_baFxData & 0xfe) | 1);
    StopParticles(m_pStartParticles);
    StopParticles(m_pPulseParticles);
    if (m_pGauge != nullptr) m_pGauge->m_sgProperties = (m_pGauge->m_sgProperties & ~4u) | 4u;
    CNode* gauge = m_pGauge;
    if (gauge->m_pParent != nullptr) gauge->m_pParent->RemoveChild(gauge);  // vt+0x78
}

// 0x00576d68 CKCounterNodeFx_InitStateMachine_maybe
void CKCounterNodeFx::InitStateMachine() {
    m_aStates[1].m_pfn = &StateShown;    // 0xbe65d0 (TOC2 -0x74cc)
    m_aStates[2].m_pfn = &StateFadeOut;  // 0xbe6610 (TOC2 -0x74c8)
    m_aStates[0].m_pfn = &StateFadeIn;   // 0xbe6618 (TOC2 -0x74d0)
    m_aStates[0].m_adjust = 0;
    m_aStates[1].m_adjust = 0;
    m_aStates[2].m_adjust = 0;
    m_ui8NbStates = 3;
    m_ui8State = 0xff;
    m_pStates = m_aStates;
    m_flags44 = static_cast<uint8_t>(m_flags44 & 0xfe);
    m_pReleaseOwner = nullptr;
    Reparent(m_pGauge, m_pStartParticles);
    Reparent(m_pGauge, m_pPulseParticles);
}

// 0x00576ec8 CKCounterNodeFx_Start: running, the machine set up; without data stopped (vt+0x6c). Else the gauge under
// sector 0's root, placed at the target's position (data flag 2) or the data's, raised by the height; the start particles
// emitting; the gauge's textures (CounterNode_SetDigitTextures); then state 0 (fade in).
void CKCounterNodeFx::Vf64() {
    m_baFxData = static_cast<uint8_t>(m_baFxData & 0xfe);
    InitStateMachine();
    if (m_pData == nullptr) {
        Stop();
        return;
    }
    CKSector* base = static_cast<CKSector*>(g_pEngine->m_level->m_vpSectors.m_pBlock[0]);
    Reparent(base->m_pSectorRoot, m_pGauge);
    const CKCounterFxData* data = m_pData;
    // BUG(original): data flag 2 without a target leaves the position registers (f29..f31) as the caller had them;
    // natively 0.
    float x = 0.0f;
    float y = 0.0f;
    float z = 0.0f;
    if (((data->m_flags >> 1) & 1u) == 0) {
        z = data->m_vPosition.z;
        x = data->m_vPosition.x;
        y = data->m_vPosition.y;
    } else if (data->m_pTarget != nullptr) {
        const RwV3d& pos = static_cast<CSGMovable*>(data->m_pTarget)->m_pRwFrame->modelling.pos;
        z = pos.z;
        x = pos.x;
        y = pos.y;
    }
    RwFrame* frame = m_pGauge->m_pRwFrame;
    frame->modelling.pos.y = y + data->m_fHeight;
    frame->modelling.pos.z = z;
    frame->modelling.pos.x = x;
    frame->modelling.flags &= 0xfffdffffu;
    RwFrame_MarkDirty(frame);  // through 0x0098fbd0
    StartParticles(m_pStartParticles, 0x404u, 0x400u);
    CounterNode_SetDigitTextures(m_pGauge, m_pTexture1c, m_pTexture18);  // 0x00583028
    SwitchState(0, nullptr);
}

// 0x005765d8 CKCounterNodeFx_Update: the gauge shown and turned to face the camera (at: minus its real Z axis, up: Y),
// placed as Start does; its fan filled by value / maximum (CounterNode_UpdateRadialGauge, the UVs of cell 0) and coloured
// by the colour keys at that fill; its size: the data's scale, plus the pulse curve while pulsing (clamped to 0..10), and
// with data flag 1 times the camera distance (clamped to the data's range) and the screen's height at that distance; then
// the machine's tick (a returned state other than the current one switches).
void CKCounterNodeFx::Update(IKTime* frameClock) {
    if (m_pGauge != nullptr) m_pGauge->m_sgProperties &= ~4u;
    CKSrvCamera* camera = static_cast<CKSrvCamera*>(g_pEngine->m_srvCamera);
    {
        CVector3 at;
        at.z = -camera->m_v3RealAxisZ.z;
        at.x = -camera->m_v3RealAxisZ.x;
        at.y = -camera->m_v3RealAxisZ.y;
        m_pGauge->SetOrientationFromAtUp(&at, &kAxisY);  // 0x000d0918 through 0x0098fcf0
    }
    const CKCounterFxData* data = m_pData;
    if (((data->m_flags >> 1) & 1u) == 0) {
        RwFrame* frame = m_pGauge->m_pRwFrame;
        const float y = data->m_vPosition.y + data->m_fHeight;
        frame->modelling.pos.z = data->m_vPosition.z;
        frame->modelling.pos.x = data->m_vPosition.x;
        frame->modelling.pos.y = y;
        frame->modelling.flags &= 0xfffdffffu;
        RwFrame_MarkDirty(frame);
    } else if (data->m_pTarget != nullptr) {
        const RwV3d& pos = static_cast<CSGMovable*>(data->m_pTarget)->m_pRwFrame->modelling.pos;
        RwFrame* frame = m_pGauge->m_pRwFrame;
        const float y = pos.y + data->m_fHeight;
        frame->modelling.pos.x = pos.x;
        frame->modelling.pos.z = pos.z;
        frame->modelling.pos.y = y;
        frame->modelling.flags &= 0xfffdffffu;
        RwFrame_MarkDirty(frame);
    }
    data = m_pData;
    const float fill = data->m_fValue / data->m_fMaxValue;
    CounterNode_UpdateRadialGauge(m_pGauge, fill, 1, 1, 0);  // 0x005845f8
    CounterNode_SetDigitUVs(m_pGauge, 1, 1, 0);              // 0x00583878
    CGeometry* geometry = FirstGeometry(m_pGauge);
    uint8_t colour[4];
    ColorCurve_Evaluate(fill, colour, &m_pData->m_colorKeys);  // 0x00246408 through 0x0098fd00
    std::memcpy(geometry->m_cGeometryColor, colour, 4);
    if (colour[3] != 0xff && (geometry->m_BitProperties & 0x1000u) != 0) {
        const int32_t mode = static_cast<int32_t>((static_cast<CMaterial*>(geometry->m_pMaterial)->m_baProperties >> 3) & 0xfu);
        if (mode > 0 && mode <= 6) geometry->m_cGeometryColor[3] = 0xff;
    }
    {
        const uint32_t blend = geometry->m_cGeometryColor[3] != 0xff ? 1u : 0u;
        const uint32_t bits = geometry->m_BitProperties;
        if (((bits >> 11) & 1u) != blend) {
            geometry->m_BitProperties = (bits & 0xfffff7ffu) | (blend << 11);
            geometry->UpdateProperties();  // vt+0x60
        }
    }
    data = m_pData;
    float scale = data->m_fScale;
    if ((m_flags44 & 1u) != 0) {
        const float time = m_fPulseTime;
        if (m_fPulseDuration > time) {
            float pulse = kZero;
            const uint32_t count = m_ui32NbPulseKeys;
            if (count != 0) {
                const float t = time / m_fPulseDuration;
                if (!(t > kOne)) {
                    if (count == 1) {
                        pulse = m_aPulseKeys[0].m_fValue;
                    } else {
                        const PulseKey* next = nullptr;
                        bool found = false;
                        for (uint32_t i = 0; i < count - 1; ++i) {
                            const PulseKey* cur = &m_aPulseKeys[i];
                            next = cur + 1;
                            if (t >= cur->m_fTime && t < next->m_fTime) {  // cror gt|eq, then blt
                                const float span = next->m_fTime - cur->m_fTime;
                                const float rise = next->m_fValue - cur->m_fValue;
                                pulse = ppc::fmadds((t - cur->m_fTime) / span, rise, cur->m_fValue);
                                found = true;
                                break;
                            }
                        }
                        if (!found) pulse = next->m_fValue;
                    }
                }
            }
            scale = scale + pulse;
            if (!(scale <= kMaxScale)) {  // ble: a NaN takes 10
                scale = kMaxScale;
            } else if (!(scale >= kZero)) {
                scale = kZero;
            }
            m_fPulseTime = time + frameClock->m_afDeltaTime[0];
        } else {
            m_flags44 = static_cast<uint8_t>(m_flags44 & 0xfe);
        }
    }
    data = m_pData;
    if ((data->m_flags & 1u) != 0) {
        const float nearest = data->m_fMinDistance;
        const RwV3d& pos = m_pGauge->m_pRwFrame->ltm.pos;
        const float dy = pos.y - camera->m_v3RealPos.y;
        const float dx = pos.x - camera->m_v3RealPos.x;
        const float dz = pos.z - camera->m_v3RealPos.z;
        const float depth = ppc::fmadds(dz, camera->m_v3RealAxisZ.z,
                                        ppc::fmadds(dx, camera->m_v3RealAxisZ.x, dy * camera->m_v3RealAxisZ.y));
        const float farthest = data->m_fMaxDistance;
        float distance;
        if (depth <= nearest) {  // ble
            if (nearest > farthest) {
                distance = farthest;
            } else {
                distance = depth > nearest ? depth : nearest;
            }
        } else if (depth <= farthest) {  // ble: a NaN depth takes the far bound
            distance = depth > nearest ? depth : nearest;
        } else {
            distance = farthest;
        }
        CameraContext* context = static_cast<CameraContext*>(g_pEngine->m_cameraContext);
        scale = scale * distance;
        const float halfFov = (context->m_fFieldOfView * kDegToRad) * kHalf;
        const float aspect = context->m_fHeightOverWidth;
        scale = scale * crt::Tanf(halfFov);  // 0x00780a90
        scale = (aspect * scale) * kHalf;
    }
    RwFrame* frame = m_pGauge->m_pRwFrame;
    RwMatrix& m = frame->modelling;
    m.right.x = scale * m.right.x;
    m.right.y = scale * m.right.y;
    m.right.z = scale * m.right.z;
    m.up.x = scale * m.up.x;
    m.up.y = scale * m.up.y;
    m.up.z = scale * m.up.z;
    m.at.x = scale * m.at.x;
    m.at.y = scale * m.at.y;
    m.at.z = scale * m.at.z;
    m.flags &= 0xfffdfffeu;
    RwFrame_MarkDirty(frame);  // through 0x0098fbd0
    const uint8_t current = m_ui8State;
    if (current == 0xff) return;
    const uint8_t next = m_pStates[current].m_pfn(this, frameClock, 0, current);
    if (next == m_ui8State) return;
    SwitchState(next, frameClock);
}
