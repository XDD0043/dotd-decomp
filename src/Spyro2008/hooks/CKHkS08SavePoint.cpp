// CKHkS08SavePoint.cpp - reconstructed original translation unit 0x4c98d8-0x4cc920 (GAME_TOC1, main_toc1), 31 functions, 28 live.
// Primary class: CKHkS08SavePoint  key 0x2e02  category Hook  size 0x84  vtable 0xb29870
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x4c98d8  CKHkS08SavePoint_Delete
//   [x] 0x4c9928  CKHkS08SavePoint_Restart  (CKHkS08SavePoint.h: empty)
//   [x] 0x4c9930  CKHkS08SavePoint_GetInfo
//   [ ] 0x4c9980  CKHkS08SavePoint_SetModelYaw_maybe  [dead: no pointer to its descriptor 0xbcb540, no call]
//   [ ] 0x4c9a60  CKHkS08SavePoint_ApplyNodeAlphas_maybe  [dead]
//   [x] 0x4c9d18  CKHkS08SavePoint_Resume  (empty / no effect: inherited)
//   [x] 0x4c9d40  CKHkS08SavePoint_Pause  (empty / no effect: inherited)
//   [x] 0x4c9d68  CKHkS08SavePoint_Stop  (inherited: CKHkActorBase_d82_maybe_Stop)
//   [x] 0x4c9d90  CKHkS08SavePoint_Start
//   [x] 0x4c9de8  CKHkS08SavePoint_PostLoad  (= the inherited slot)
//   [ ] 0x4c9e10  CKHkS08SavePoint_Save
//   [x] 0x4c9e38  CKHkS08SavePoint_RecursiveRegistration  (CKHkS08SavePoint.h)
//   [x] 0x4c9e60  CKHkS08SavePoint_Destroy  (inherited: CKHkActorBase::Destroy)
//   [x] 0x4c9e88  CKHkS08SavePoint_Construct  [dead]
//   [x] 0x4c9ec0  CKHkS08SavePoint_DeleteArray
//   [ ] 0x4c9f68  RegisterCKHkS08SavePointClass
//   [ ] 0x4c9ff0  _GLOBAL__D_4c9ff0
//   [ ] 0x4ca000  _GLOBAL__I_4ca000
//   [x] 0x4ca010  CKHkS08SavePoint_DeletingDestructor  (C++ deleting destructor)
//   [x] 0x4ca058  CKHkS08SavePoint_Destructor  (C++ destructor chain: vtable stores only)
//   [x] 0x4ca088  CKHkS08SavePoint_BaseDestructor  (C++ destructor chain)
//   [x] 0x4ca0b8  CKHkS08SavePoint_SetEnabled
//   [ ] 0x4ca178  CKHkS08SavePoint_Construct_2  [dead]
//   [x] 0x4ca1b0  CKHkS08SavePoint_Create
//   [x] 0x4ca208  CKHkS08SavePoint_CreateArray
//   [x] 0x4ca2c0  CKHkS08SavePoint_SetVisible
//   [x] 0x4ca7e8  CKHkS08SavePoint_OnDeactivate
//   [x] 0x4ca9c8  CKHkS08SavePoint_MessageProc
//   [x] 0x4cb030  CKHkS08SavePoint_Update
//   [x] 0x4cbbf0  CKHkS08SavePoint_OnActivate
//   [x] 0x4cc318  CKHkS08SavePoint_Load
//
//   [ ] 0x9c5a50  CKHkS08SavePoint_IsKindOfClass  [inline]
//   [ ] 0x9c5aa8  CKHkS08SavePoint_GetClassType  [inline]
//   [ ] 0x9c5ab0  CKHkS08SavePoint_GetClassID  [inline]
#include "Spyro2008/hooks/CKHkS08SavePoint.h"
#include "k2000/logic/CDefaultGameManager.h"
#include "k2000/misc/Engine.h"

#include <cstring>

#include "Renderware/rpprtstd/RpPrtStd.h"
#include "Renderware/rwcore/RwCamera.h"
#include "Spyro2008/groups/CKGrpS08Hero.h"
#include "Spyro2008/hooks/CKHkS08Hero.h"
#include "Spyro2008/logic/CKS08GameManager.h"
#include "crt/ppc_ops.h"
#include "k2000/components/CKLocTextAccessor.h"
#include "k2000/core/IKInfo.h"
#include "k2000/dictionaries/CKSoundDictionaryID.h"
#include "k2000/geometry/CGeometry.h"
#include "k2000/io/IKFile.h"
#include "k2000/logic/render/CMaterial.h"
#include "k2000/logic/sound/CKSound.h"
#include "k2000/math/CMatrix34.h"
#include "k2000/math/Math.h"
#include "k2000/misc/IKGameStructure.h"
#include "k2000/misc/Mat4.h"
#include "k2000/scenegraph/CFogBoxNodeFx.h"
#include "k2000/scenegraph/CNode.h"
#include "k2000/scenegraph/CParticlesNodeFx.h"
#include "k2000/scenegraph/CSGMovable.h"
#include "k2000/system/IKTime.h"

// 0x004cc318 CKHkS08SavePoint_Load: the actor base, then the level data (type 0 only). The trigger
// starters are loaded with type 0.
int32_t CKHkS08SavePoint::Load(IKFile* file, int32_t type) {
    CKHkActorBase::Load(file, type);
    if (type == K_LEVEL_PLATEFORMS) {
        IKFile_ReadRef(file, &m_pUnk20);
        IKFile_ReadRef(file, &m_pUnk64);
        IKFile_ReadRef(file, &m_pUnk34);
        IKFile_ReadRef(file, &m_pUnk38);
        IKFile_ReadRef(file, &m_pUnk3C);
        IKFile_ReadRef(file, &m_pUnk40);
        m_unk24.Load(file, K_LEVEL_PLATEFORMS);
        m_unk2C.Load(file, K_LEVEL_PLATEFORMS);
        ReadRaw(file, m_unk44, 3);
        ReadRaw(file, m_unk47, 3);
        ReadRaw(file, m_unk4A, 3);
        ReadU8(file, &m_unk4D);
        ReadU8(file, &m_unk4E);
        ReadU8(file, &m_unk4F);
        ReadF32LE(file, &m_fUnk50);
        ReadF32LE(file, &m_fUnk54);
        ReadF32LE(file, &m_fUnk58);
        ReadF32LE(file, &m_fUnk5C);  // the original reads both as words (the same bytes)
        ReadF32LE(file, &m_fUnk60);
    }
    return 1;
}

// 0x004c9d90 CKHkS08SavePoint_Start (the actor base's empty ResetRuntime 0x3f6e48, then vt+0x54)
void CKHkS08SavePoint::Start() {
    Restart();
}

// 0x004ca0b8 CKHkS08SavePoint_SetEnabled
void CKHkS08SavePoint::SetEnabled(int32_t enabled) {
    uint32_t bit = 0;
    if (enabled != 0 && g_pEngine->m_gameManager->VfC4() == 0) bit = 8;  // vt+0xc4
    m_bitArray = (m_bitArray & ~8u) | bit;
}

// ==== C2.8 save-menu: the save point's run time ====================================================================
namespace {
const float kZero = 0.0f;                // TOC1 +0x68d4
const float kOne = 1.0f;                 // TOC1 +0x688c
const float kFltMax = 0x1.fffffep+127f;  // the word at 0x00c4acb8 + 0x28 (read through a TOC pointer)

uint8_t AlphaByte(float alpha) { return static_cast<uint8_t>(ppc::fctiwz(alpha)); }  // fctiwz, stfiwx, lbz +3

// The per-geometry alpha block inlined three times (SceneNode_SetAlphaRecursive's body for one geometry): below 255 the
// geometry blends, unless its bit 0x1000 and material mode 1..6 keep it opaque at 255; the properties updated (vt+0x60)
// when the blend bit changes.
void SetGeometryAlpha(CGeometry* geometry, uint8_t alpha) {
    uint32_t blend = 0;
    uint8_t value = alpha;
    if (alpha != 0xff) {
        blend = 1;
        if ((geometry->m_BitProperties & 0x1000u) != 0) {
            const int32_t mode =
                static_cast<int32_t>((static_cast<CMaterial*>(geometry->m_pMaterial)->m_baProperties >> 3) & 0xfu);
            if (mode > 0 && mode <= 6) {
                value = 0xff;
                blend = 0;
            }
        }
    }
    geometry->m_cGeometryColor[3] = value;
    if (((geometry->m_BitProperties >> 11) & 1u) != blend) {
        geometry->m_BitProperties = (geometry->m_BitProperties & 0xfffff7ffu) | (blend << 11);
        geometry->UpdateProperties();  // vt+0x60
    }
}

// A particle node shown with its emitter emitting (bit 10 set, bit 19 cleared, the emission speed adjustment 0).
void StartParticles(IKSerializable* object) {
    CParticlesNodeFx* node = static_cast<CParticlesNodeFx*>(object);
    const uint32_t p = node->m_sgProperties;
    node->m_sgProperties = (p & 0xfff00000u) | (p & 0x7f800u) | (p & 0x3ffu) | 0x400u;
    node->m_fEmissionSpeedAdjustment = kZero;
    node->m_pRpPrtStdEmitter->flag |= rpPRTSTDEMITTERFLAGACTIVE | rpPRTSTDEMITTERFLAGEMIT;  // | 10
}
// Bits 10 and 19 cleared, the emitter no longer emitting.
void StopParticles(IKSerializable* object) {
    CParticlesNodeFx* node = static_cast<CParticlesNodeFx*>(object);
    node->m_sgProperties &= 0xfff7fbffu;
    node->m_pRpPrtStdEmitter->flag &= ~static_cast<uint32_t>(rpPRTSTDEMITTERFLAGEMIT);
}
bool ParticlesShown(IKSerializable* object) {
    return (static_cast<CParticlesNodeFx*>(object)->m_sgProperties & 0x400u) != 0;
}

CKSound* Sound(IKSerializable* sounds, uint32_t index) {
    return static_cast<CKSoundDictionaryID*>(sounds)->GetSound2(index);  // 0x00112bd8 CKSoundDictionaryID_GetSound_2
}
void StopIfPlaying(CKSound* sound) {
    if (sound->IsPlaying() != 0) sound->Stop(0);  // 0x00111568, 0x001111b0
}
void LoopIfSilent(CKSound* sound) {
    if (sound->IsPlaying() != 0) return;
    sound->SetLoop(1);   // 0x00110fd0
    sound->Play(kZero);  // 0x00111230
}
}  // namespace

// The block inlined in OnActivate, MessageProc and Update.
void CKHkS08SavePoint::ApplyAlphas() {
    SceneNode_SetAlphaRecursive(m_pUnk40, AlphaByte(m_fFogAlpha), 1);  // TocBridge 0x98f570 -> 0x00582c60
    CGeometry* geometry = static_cast<CGeometry*>(static_cast<CNode*>(m_pKGLObject)->m_lGeometryList);
    if (geometry == nullptr) return;
    SetGeometryAlpha(geometry, AlphaByte(m_fAlpha0));
    geometry = geometry->m_pNext;
    if (geometry == nullptr) return;
    SetGeometryAlpha(geometry, AlphaByte(m_fAlpha1));
    geometry = geometry->m_pNext;
    if (geometry == nullptr) return;
    SetGeometryAlpha(geometry, AlphaByte(m_fAlpha2));
}

// The identity (flags 0x20003, the identity bit then cleared; the pads not written) at the node's modelling position,
// turned by m_fYaw (Mat4_RotateLocalYDeg 0x2413d0), the node's local matrix (CSGMovable_SetLocalMatrix_maybe 0xd0be8).
void CKHkS08SavePoint::ApplyYaw() {
    CMatrix34 matrix;
    matrix.m_right = {kOne, kZero, kZero};
    matrix.m_ui32Flags = 0x20003u;
    matrix.m_up = {kZero, kOne, kZero};
    matrix.m_at = {kZero, kZero, kOne};
    const RwFrame* frame = static_cast<CSGMovable*>(m_pKGLObject)->m_pRwFrame;
    matrix.m_pos = {frame->modelling.pos.x, frame->modelling.pos.y, frame->modelling.pos.z};
    matrix.m_ui32Flags &= 0xfffdffffu;
    Mat4_RotateLocalYDeg(m_fYaw, &matrix);
    static_cast<CSGMovable*>(m_pKGLObject)->SetLocalMatrix(reinterpret_cast<const RwMatrix*>(&matrix));
}

// The fog box record step inlined in OnActivate (and SetVisible): the boxes in use searched from the last for this save
// point; found, its scale back to 1; else, with room, the next box taken (its matrix the identity, flags 0x20003; the
// copy below overwrites it) and the box count raised. Then the box takes the node's world matrix and its particles are
// randomised (`enable` 1 for a new box).
void CKHkS08SavePoint::PlaceFogBox() {
    CFogBoxNodeFx* fog = static_cast<CFogBoxNodeFx*>(m_pUnk40);
    const RwFrame* frame = static_cast<CSGMovable*>(m_pKGLObject)->m_pRwFrame;
    const uint32_t count = fog->m_unk40;
    const uintptr_t owner = reinterpret_cast<uintptr_t>(this);
    uint32_t index = count;
    int32_t enable = 0;
    bool found = false;
    while (index != 0) {
        --index;
        if (fog->m_aBoxes[index].m_unk04 == owner) {
            fog->m_aBoxes[index].m_unk08 = kOne;
            found = true;
            break;
        }
    }
    if (!found) {
        if (fog->m_ui32NbBoxes == count) return;
        CMatrix34* box = fog->m_aBoxes[count].m_pMatrix;
        box->m_right = {kOne, kZero, kZero};
        box->m_ui32Flags = 0x20003u;
        box->m_up = {kZero, kOne, kZero};
        box->m_at = {kZero, kZero, kOne};
        box->m_pos = {kZero, kZero, kZero};
        fog->m_aBoxes[fog->m_unk40].m_unk04 = owner;
        fog->m_aBoxes[fog->m_unk40].m_unk08 = kOne;
        fog->m_unk40 = fog->m_unk40 + 1;
        index = count;
        enable = 1;
    }
    std::memcpy(fog->m_aBoxes[index].m_pMatrix, FrameLtm(frame), sizeof(CMatrix34));
    fog->RandomizeEmitterParticles(enable, index);  // 0x000da968
}

// 0x004cbbf0 CKHkS08SavePoint_OnActivate
void CKHkS08SavePoint::VfA0() {
    CKHkActorBase::VfA0();  // 0x003f7338
    const uint32_t idle = static_cast<uint32_t>(g_pEngine->m_gameManager->VfC4()) ^ 1u;  // vt+0xc4
    const uint32_t flags = m_bitArray;
    m_bitArray = ((flags & 0xfffffff0u) | (flags & 7u) | ((idle & 0xffu) << 3)) & 0xffffffcfu;  // bit 3; bits 4, 5 cleared
    m_fAlpha0 = static_cast<float>(m_unk47[0]);
    m_fAlpha1 = static_cast<float>(m_unk47[1]);
    m_fUsedTime = kZero;
    m_fYaw = kZero;
    m_fYawSpeed = kZero;
    m_fAlpha2 = static_cast<float>(m_unk47[2]);
    m_fFogAlpha = static_cast<float>(m_unk4E);
    StartParticles(m_pUnk38);
    StartParticles(m_pUnk3C);
    if (m_fUnk5C != kZero) ApplyYaw();
    ApplyAlphas();
    CNode* node = static_cast<CNode*>(m_pKGLObject);
    node->m_sgProperties &= 0xfffffffbu;  // shown
    PlaceFogBox();
    for (CGeometry* geometry = static_cast<CGeometry*>(node->m_lGeometryList); geometry != nullptr;
         geometry = geometry->m_pNext) {
        geometry->m_BitProperties = (geometry->m_BitProperties & 0xffffffc0u) | 0x2eu;
    }
}

// 0x004ca7e8 CKHkS08SavePoint_OnDeactivate: the particles stopped; the fog box's box of this save point given back (the
// last box in use moved into its place: matrix and owner, not the scale).
void CKHkS08SavePoint::VfA4() {
    CKHkActorBase::VfA4();  // 0x003f7370
    StopParticles(m_pUnk38);
    StopParticles(m_pUnk3C);
    CFogBoxNodeFx* fog = static_cast<CFogBoxNodeFx*>(m_pUnk40);
    const uint32_t count = fog->m_unk40;
    const uintptr_t owner = reinterpret_cast<uintptr_t>(this);
    uint32_t index = count;
    for (;;) {
        if (index == 0) return;
        --index;
        if (fog->m_aBoxes[index].m_unk04 == owner) break;
    }
    const uint32_t last = count - 1;
    fog->m_unk40 = last;
    if (index != last) {
        std::memcpy(fog->m_aBoxes[index].m_pMatrix, fog->m_aBoxes[last].m_pMatrix, sizeof(CMatrix34));
        fog->m_aBoxes[index].m_unk04 = fog->m_aBoxes[last].m_unk04;
    }
    fog->m_aBoxes[fog->m_unk40].m_unk04 = 0;
}

// 0x004ca2c0 CKHkS08SavePoint_SetVisible
void CKHkS08SavePoint::SetVisible(int32_t visible) {
    CNode* node = static_cast<CNode*>(m_pKGLObject);
    if (visible != 0 && g_pEngine->m_gameManager->VfC4() == 0) {  // vt+0xc4
        m_bitArray = (m_bitArray & ~8u) | 8u;
        StartParticles(m_pUnk38);
        StartParticles(m_pUnk3C);
        PlaceFogBox();
        node->m_sgProperties &= 0xfffffffbu;  // shown
        return;
    }
    m_bitArray &= ~8u;
    StopParticles(m_pUnk38);
    StopParticles(m_pUnk3C);
    // The fog box record given back, as OnDeactivate: the last box in use moved into its place (matrix and owner).
    CFogBoxNodeFx* fog = static_cast<CFogBoxNodeFx*>(m_pUnk40);
    const uint32_t count = fog->m_unk40;
    const uintptr_t owner = reinterpret_cast<uintptr_t>(this);
    uint32_t index = count;
    bool found = false;
    while (index != 0) {
        --index;
        if (fog->m_aBoxes[index].m_unk04 == owner) {
            found = true;
            break;
        }
    }
    if (found) {
        const uint32_t last = count - 1;
        fog->m_unk40 = last;
        if (index != last) {
            std::memcpy(fog->m_aBoxes[index].m_pMatrix, fog->m_aBoxes[last].m_pMatrix, sizeof(CMatrix34));
            fog->m_aBoxes[index].m_unk04 = fog->m_aBoxes[last].m_unk04;
        }
        fog->m_aBoxes[fog->m_unk40].m_unk04 = 0;
    }
    node->m_sgProperties = (node->m_sgProperties & 0xfffffffbu) | 4u;  // hidden
}

// 0x004c9930 CKHkS08SavePoint_GetInfo: the actor base's (KStub_Return1 0x3f7140) answer folded to 2 / 0 / 1.
int32_t CKHkS08SavePoint::GetInfo(IKInfo* info, int32_t request) {
    const int32_t base = CKHkActorBase::GetInfo(info, request);
    if (base == 2) return 2;
    return base == 0 ? 0 : 1;
}

// 0x004ca9c8 CKHkS08SavePoint_MessageProc
int32_t CKHkS08SavePoint::MessageProc(uint16_t message, void* data) {
    const int32_t base = CKHkActorBase::MessageProc(message, data);  // 0x003f7148
    int32_t own = 1;
    if (message == 0x93f) {
        if (Sound(m_pUnk20, 0) != nullptr) Sound(m_pUnk20, 0)->Play(kZero);
        if (Sound(m_pUnk20, 1) != nullptr) Sound(m_pUnk20, 1)->Play(kZero);
        CDefaultGameManager* manager = g_pEngine->m_gameManager;
        static_cast<IKGameStructure*>(manager->m_gameStructure)
            ->SetCurrentSpawnPoint(reinterpret_cast<CKGameSpawnPoint*>(m_pUnk34));  // vt+0x6c
        manager->RequestSave(0, 0);  // vt+0x104
        // CKHkS08Hero_GetPlayerIndexIfControlled_maybe (0x362ac8, a getter) of the hero (`data`) goes to KStub_Nop_4ec920.
        m_bitArray = (m_bitArray & 0xffffffdfu) | 0x20u;
        m_fAlpha0 = static_cast<float>(m_unk44[0]);
        m_fAlpha1 = static_cast<float>(m_unk44[1]);
        m_fUsedTime = kZero;
        m_fYaw = kZero;
        m_fYawSpeed = kZero;
        m_fAlpha2 = static_cast<float>(m_unk44[2]);
        m_fFogAlpha = static_cast<float>(m_unk4D);
        if (m_fUnk5C != kZero) ApplyYaw();
        ApplyAlphas();
        StopParticles(m_pUnk38);
        StopParticles(m_pUnk3C);
        own = 0;
    } else if (message == 0x2666) {
        CKLocTextAccessor* accessor = static_cast<CKLocTextAccessor*>(m_pUnk64);
        IKSerializable* text = accessor->m_texts.m_pBlock != nullptr ? accessor->m_texts.m_pBlock[0] : accessor->m_pText;
        own = 0;
        *static_cast<IKSerializable**>(data) = text;
    }
    if (base == 3 || own == 3) return 3;
    if (base == 2 || own == 2) return 2;
    if (base != 0) return own;
    return 0;
}

// 0x004cb030 CKHkS08SavePoint_Update. The alphas approach their targets at +0x50 per second; each stage's increase /
// decrease and clamp tests keep the original's compare senses (they differ for a NaN only).
void CKHkS08SavePoint::Update(IKTime* frameClock) {
    // WorldObjectBase_Update_Nop 0x3f6e68: nothing.
    const float dt = frameClock->m_afDeltaTime[0];
    const uint32_t flags = m_bitArray;
    uint8_t b0;
    uint8_t b1;
    uint8_t b2;
    uint8_t bFog;
    float speedTarget = kZero;
    if ((flags & 8u) == 0 || (flags & 0x20u) != 0) {
        b0 = m_unk44[0];
        b1 = m_unk44[1];
        b2 = m_unk44[2];
        bFog = m_unk4D;
    } else if ((flags & 0x10u) == 0) {
        b0 = m_unk47[0];
        b1 = m_unk47[1];
        b2 = m_unk47[2];
        bFog = m_unk4E;
    } else {
        b0 = m_unk4A[0];
        b1 = m_unk4A[1];
        b2 = m_unk4A[2];
        bFog = m_unk4F;
        speedTarget = m_fUnk5C;
    }
    const float t0 = static_cast<float>(b0);
    const float t1 = static_cast<float>(b1);
    const float t2 = static_cast<float>(b2);
    const float tFog = static_cast<float>(bFog);
    const float speed = m_fUnk50;

    // The fog box node's alpha.
    bool clamped = false;
    const float fog = m_fFogAlpha;
    if (!(tFog == fog)) {
        if (tFog > fog) {
            const float v = ppc::fmadds(dt, speed, fog);
            m_fFogAlpha = v;
            if (!(tFog >= v)) clamped = true;
        } else {
            const float v = fog - dt * speed;
            m_fFogAlpha = v;
            if (!(tFog <= v)) clamped = true;
        }
        if (clamped) m_fFogAlpha = tFog;
    }
    // The first geometry's: after a clamp the increase test is bge-not (4cb144), else blt (4cb4e4).
    {
        const float c = m_fAlpha0;
        const bool up = clamped ? !(c >= t0) : (c < t0);
        clamped = false;
        if (up) {
            const float v = ppc::fmadds(dt, speed, c);
            m_fAlpha0 = v;
            if (t0 < v) clamped = true;
        } else {
            const float v = c - dt * speed;
            m_fAlpha0 = v;
            if (!(t0 <= v)) clamped = true;
        }
        if (clamped) m_fAlpha0 = t0;
    }
    // The second's: after a clamp bge-not (4cb50c), else blt (4cb168).
    {
        const float c = m_fAlpha1;
        const bool up = clamped ? !(c >= t1) : (c < t1);
        clamped = false;
        if (up) {
            const float v = ppc::fmadds(dt, speed, c);
            m_fAlpha1 = v;
            if (!(t1 >= v)) clamped = true;
        } else {
            const float v = c - dt * speed;
            m_fAlpha1 = v;
            if (t1 > v) clamped = true;
        }
        if (clamped) m_fAlpha1 = t1;
    }
    // The third's: after a clamp blt (4cb530), else bge-not (4cb18c).
    {
        const float c = m_fAlpha2;
        const bool up = clamped ? (c < t2) : !(c >= t2);
        clamped = false;
        if (up) {
            const float v = ppc::fmadds(dt, speed, c);
            m_fAlpha2 = v;
            if (t2 < v) clamped = true;
        } else {
            const float v = c - dt * speed;
            m_fAlpha2 = v;
            if (!(t2 <= v)) clamped = true;
        }
        if (clamped) m_fAlpha2 = t2;
    }
    ApplyAlphas();

    // The turn speed toward its target at +0x60 per second, then the turn.
    float turn = m_fYawSpeed;
    if (!(speedTarget == turn)) {
        if (speedTarget > turn) {
            turn = ppc::fmadds(dt, m_fUnk60, turn);
            m_fYawSpeed = turn;
            if (!(speedTarget >= turn)) {
                turn = speedTarget;
                m_fYawSpeed = turn;
            }
        } else {
            turn = turn - dt * m_fUnk60;
            m_fYawSpeed = turn;
            if (speedTarget > turn) {
                turn = speedTarget;
                m_fYawSpeed = turn;
            }
        }
    }
    if (turn != kZero) {
        m_fYaw = ppc::fmadds(dt, turn, m_fYaw);
        ApplyYaw();
    }

    CKSound* idleLoop = Sound(m_pUnk20, 3);
    CKSound* reachLoop = Sound(m_pUnk20, 2);
    if ((m_bitArray & 8u) == 0) {
        if (ParticlesShown(m_pUnk38)) StopParticles(m_pUnk38);
        if (idleLoop != nullptr) StopIfPlaying(idleLoop);
        if (reachLoop != nullptr) StopIfPlaying(reachLoop);
        return;
    }
    if (!ParticlesShown(m_pUnk38)) StartParticles(m_pUnk38);
    // The nearest controlled hero within the radius; inside the height band above the node the height counts 0.
    CKS08GameManager* manager = static_cast<CKS08GameManager*>(g_pEngine->m_gameManager);
    CKGrpS08Hero* group = static_cast<CKGrpS08Hero*>(manager->m_unk04[1]);
    const RwMatrix* ltm = FrameLtm(static_cast<CSGMovable*>(m_pKGLObject)->m_pRwFrame);
    const float px = ltm->pos.x;
    const float py = ltm->pos.y;
    const float pz = ltm->pos.z;
    float best = kFltMax;
    uint32_t nearest = 0xffffffffu;
    const uint8_t count = group->m_ui8ControlledHeroCount;  // 0x002ca288 GetControlledHeroCount
    for (uint32_t i = 0; i != count; ++i) {
        CKHkS08Hero* hero = static_cast<CKHkS08Hero*>(group->m_apControlledHeroes[i]);  // 0x002ca0e0
        const float* p = hero->GetPositionPtr();  // 0x00361968
        const float top = py + m_fUnk58;
        float y = p[1];
        const float dz = p[2] - pz;
        const float dx = p[0] - px;
        if (top >= y && py <= y) y = py;  // cror gt|eq, cror lt|eq
        const float dy = y - py;
        const float d = ppc::fmadds(dz, dz, ppc::fmadds(dx, dx, dy * dy));
        if (d < best && m_fUnk54 * m_fUnk54 >= d) {
            best = d;
            nearest = i;
        }
    }
    const uint32_t inReach = nearest != 0xffffffffu ? 0x10u : 0u;
    if ((m_bitArray & 0x20u) != 0) {
        const float used = dt + m_fUsedTime;
        m_fUsedTime = used;
        if (nearest != 0xffffffffu && used <= kOne) {  // ble: a NaN goes on
            StopIfPlaying(idleLoop);
            StopIfPlaying(reachLoop);
            return;
        }
        m_bitArray &= 0xffffffdfu;
    }
    m_bitArray = (m_bitArray & 0xffffffefu) | inReach;
    if ((m_bitArray & 0x10u) == 0) {
        StopIfPlaying(reachLoop);
        LoopIfSilent(idleLoop);
        if (ParticlesShown(m_pUnk3C)) StopParticles(m_pUnk3C);
        return;
    }
    StopIfPlaying(idleLoop);
    LoopIfSilent(reachLoop);
    if (!ParticlesShown(m_pUnk3C)) StartParticles(m_pUnk3C);
    manager->SetHeroInteractionTarget(this, 2, static_cast<uint8_t>(nearest));  // 0x004ee770
}
