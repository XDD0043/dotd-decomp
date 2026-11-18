// CKExplosionNodeFx.cpp - reconstructed original translation unit 0x1b5d98-0x1b8778 (GAME_TOC1, main_toc1), 27 functions, 27 live.
// Primary class: CKExplosionNodeFx  key 0x1a4c  category Logic  size 0x50  vtable 0xb1ca38
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [ ] 0x1b5d98  RegisterCKExplosionNodeFxClass
//   [ ] 0x1b5e10  _GLOBAL__I_1b5e10
//   [x] 0x1b5e20  CKExplosionNodeFx_SetDirection
//   [x] 0x1b5fd8  CKExplosionNodeFx_PostLoad
//   [ ] 0x1b6040  CKExplosionNodeFx_Save
//   [x] 0x1b6068  CKExplosionNodeFx_Destroy
//   [x] 0x1b60a8  CKExplosionNodeFx_DeleteArray
//   [x] 0x1b6150  CKExplosionNodeFx_Create
//   [x] 0x1b61c0  CKExplosionNodeFx_RecursiveRegistration
//   [x] 0x1b62c8  CKExplosionNodeFx_SetDamage
//   [x] 0x1b62f0  CKExplosionNodeFx_SetDamageFlags
//   [x] 0x1b6318  CKExplosionNodeFx_SetDamageCategory
//   [x] 0x1b6340  CKExplosionNodeFx_SetDamageOwner
//   [x] 0x1b6368  CKExplosionNodeFx_SetMatrix
//   [x] 0x1b6438  CKExplosionNodeFx_SetPosition
//   [x] 0x1b64a0  CKExplosionNodeFx_CountSubEffectsOfType_maybe  (no caller in the original)
//   [x] 0x1b6530  CKExplosionNodeFx_GetNthSubEffectOfType_maybe  (callers: CKPurpleCombo (P03's local copy replaced), CKBlackCombo / CKCometDash / CKPoisonSpin (not ported there))
//   [x] 0x1b65f0  CKExplosionNodeFx_Start
//   [x] 0x1b66e8  CKExplosionNodeFx_SetTranslation
//   [x] 0x1b6740  CKExplosionNodeFx_Stop
//   [x] 0x1b6858  CKExplosionNodeFx_CreateArray
//   [x] 0x1b6940  CKExplosionNodeFx_Load
//   [x] 0x1b6c20  CKExplosionNodeFx_FireSubEffect
//   [x] 0x1b7fa8  CKExplosionNodeFx_UpdateActive_maybe
//   [x] 0x1b8288  CKExplosionNodeFx_Update
//   [x] 0x1b82a8  CKExplosionNodeFx_Trigger
//   [x] 0x1b8770  CKExplosionNodeFx_Trigger  (a branch to 0x1b82a8: CKExplosionNodeFx::Trigger)
//
//   [ ] 0x9abc08  CKExplosionNodeFx_IsKindOfClass  [inline]
//   [x] 0x9abc40  CKExplosionNodeFx_GetClassType  [inline]
//   [x] 0x9abc48  CKExplosionNodeFx_GetClassID  [inline]
//   [x] 0x9abc50  CKExplosionNodeFx_GetFxData  [inline]
//   [x] 0x9abc58  CKExplosionNodeFx_SetFxData  [inline]
//   [ ] 0x9abc60  CKExplosionNodeFx_Destruct  [inline]
//   [ ] 0x9abce0  CKExplosionNodeFx_DeletingDestruct  [inline]
#include "k2000/logic/fx/CKExplosionNodeFx.h"
#include "k2000/components/CKParticlesCpnt.h"
#include "k2000/logic/fx/CKSrvFxParticlesAccessor.h"
#include "k2000/misc/Mat4.h"
#include "k2000/logic/CKProjectileAccessor.h"
#include "k2000/logic/fx/CKShockWaveNodeFx.h"
#include "k2000/logic/fx/CKDistortionNodeFx.h"
#include "k2000/fx/CKShockWaveFxData.h"

#include <cmath>
#include <cstring>

#include "Renderware/rwcore/RwCamera.h"
#include "Renderware/rwcore/RwMatrix.h"
#include "crt/ppc_ops.h"
#include "k2000/misc/ClassRegistry.h"
#include "k2000/services/CKSrvFx.h"
#include "k2000/logic/render/CKMeshPopNodeFx.h"
#include "k2000/fx/CKSparkFxData.h"
#include "k2000/components/CKQuakeCameraLauncher.h"
#include "k2000/core/Stub.h"
#include "k2000/dictionaries/CKSoundDictionaryID.h"
#include "k2000/io/IKFile.h"
#include "k2000/logic/CKSavingManager.h"
#include "k2000/logic/sound/CKSound.h"
#include "k2000/managers/CKInput.h"
#include "k2000/managers/CKVibrationData.h"
#include "k2000/memory/Mem.h"
#include "k2000/misc/Engine.h"
#include "k2000/scenegraph/CKDynamicBoundingSphere.h"
#include "k2000/scenegraph/CSGBranch.h"
#include "k2000/services/CKSrvCollision.h"
#include "k2000/system/IKTime.h"

// 0x001b6150 CKExplosionNodeFx_Create, the inlined constructor: the sub-effect list.
CKExplosionNodeFx::CKExplosionNodeFx() {
    m_subEffects.m_pBlock = nullptr;
    m_subEffects.m_ui32NbElt = 10;
    m_subEffects.m_ui32NbUsedElt = 0;
}

// 0x001b6940 CKExplosionNodeFx_Load
int32_t CKExplosionNodeFx::Load(IKFile* file, int32_t type) {
    IKNodeFx::Load(file, type);
    if (type == K_LEVEL_PLATEFORMS) {
        uint32_t count = 0;
        ReadU32LE(file, &count);
        if (count == 0) {
            m_subEffects.m_ui32NbElt = 1;
            m_subEffects.m_pBlock = static_cast<SubEffect*>(Mem_AllocAligned16(static_cast<uint32_t>(sizeof(SubEffect))));
        } else {
            m_subEffects.m_ui32NbElt = count;
            m_subEffects.m_pBlock =
                static_cast<SubEffect*>(Mem_AllocAligned16(count * static_cast<uint32_t>(sizeof(SubEffect))));
        }
        if (m_subEffects.m_ui32NbElt < count) {  // never true: the capacity is at least count here
            uint32_t capacity = (count / 10) * 10 + 10;
            uint32_t bytes = capacity * static_cast<uint32_t>(sizeof(SubEffect));
            if (capacity == 0) {
                capacity = 10;
                bytes = 10 * static_cast<uint32_t>(sizeof(SubEffect));
            }
            m_subEffects.m_pBlock = static_cast<SubEffect*>(Mem_ReallocAligned16(m_subEffects.m_pBlock, bytes));
            m_subEffects.m_ui32NbElt = capacity;
        }
        m_subEffects.m_ui32NbUsedElt = count;
        for (uint32_t i = 0; i < count; ++i) {
            SubEffect& e = m_subEffects.m_pBlock[i];
            ReadS32LE(file, &e.m_value);
            if (e.m_value > 0) {
                e.m_pObject = nullptr;
            } else {
                IKFile_ReadRef(file, &e.m_pObject);
            }
        }
        ReadU8(file, &m_baFxData);  // one byte, no swap
        m_pMatrix = RwMatrixCreate();  // RwMatrixCreate_Thunk
    }
    m_pDamage = nullptr;
    m_fElapsed = 0.0f;
    m_pFxData = nullptr;
    m_pDamageSphere = nullptr;
    m_pDamageOwner = nullptr;
    return 1;
}

namespace {
const float kZero = 0.0f;               // TOC1 -0x2144
const float kTriggerRadius = 0.1f;      // TOC1 -0x2104 (0x3dcccccd)
const float kMinimumRadius = 0.001f;    // TOC1 -0x2100 (0x3a83126f)
const uint8_t kWhite[4] = {0xff, 0xff, 0xff, 0xff};  // 0x00c50dfc
const CVector3 kNullVector = {0.0f, 0.0f, 0.0f};    // g_nullVector 0x00c50d64 (TOC1 -0x2110)

CKExplosionFxData* DataOf(const CKExplosionNodeFx* node) { return static_cast<CKExplosionFxData*>(node->m_pFxData); }
}  // namespace

// 0x001b5fd8 CKExplosionNodeFx_PostLoad
int32_t CKExplosionNodeFx::PostLoad(int32_t type) {
    IKNodeFx::PostLoad(type);  // 0x001d8b48
    std::memcpy(m_aColor, kWhite, 4);
    Stop();  // vt+0x6c
    return 1;
}

// 0x001b6068 CKExplosionNodeFx_Destroy
void CKExplosionNodeFx::Destroy() {
    RwMatrixDestroy(m_pMatrix);  // RwMatrixDestroy_Thunk 0x0023f968
    m_pMatrix = nullptr;
}

// 0x001b65f0 CKExplosionNodeFx_Start
void CKExplosionNodeFx::Vf64() {
    m_baFxData = static_cast<uint8_t>((m_baFxData & 0xfc) | 2);
    m_unk44 = nullptr;
    RwMatrix* m = m_pMatrix;
    m->flags = 0x20003;  // rwMATRIXINTERNALIDENTITY | rwMATRIXTYPEORTHONORMAL
    m->right = {1.0f, 0.0f, 0.0f};
    m->up = {0.0f, 1.0f, 0.0f};
    m->at = {0.0f, 0.0f, 1.0f};
    m->pos = {0.0f, 0.0f, 0.0f};
    if (m_pFxData == nullptr) {
        Stop();  // vt+0x6c
        return;
    }
    m_pTriggerOwner = nullptr;
    m_pDamageSphere = nullptr;  // BUG(original): a sphere still held is dropped, not released
    m_pDamageOwner = nullptr;
    m_pDamage = nullptr;
    m_baFxData = static_cast<uint8_t>(m_baFxData & 0xfb);
    m_fDuration = DataOf(this)->m_unk08;
    std::memcpy(m_aColor, DataOf(this)->m_unk38, 4);
}

// 0x001b6740 CKExplosionNodeFx_Stop
void CKExplosionNodeFx::Stop() {
    if (m_pDamageSphere != nullptr) {
        CSGBranch* parent = m_pDamageSphere->m_pParent;
        if (parent != nullptr) parent->RemoveChild(m_pDamageSphere);  // vt+0x78
        static_cast<CKSrvCollision*>(g_pEngine->m_srvCollision)->ReleaseDynSphere(m_pDamageSphere);  // 0x00191a38
        m_pDamageSphere = nullptr;
    }
    if (m_pFxData != nullptr) {
        CKVibrationData* vibration = DataOf(this)->m_pVibrationPadData;
        if (vibration != nullptr && vibration->m_bUseTime == 0) {
            g_pEngine->m_input->StopVibration(this, 0);  // 0x00107538
        }
    }
    m_baFxData = static_cast<uint8_t>((m_baFxData & 0xfc) | 1);
    m_pDamage = nullptr;
    m_pDamageOwner = nullptr;
    m_baFxData = static_cast<uint8_t>(m_baFxData & 0xfb);
}

// 0x001b8288 CKExplosionNodeFx_Update
void CKExplosionNodeFx::Update(IKTime* frameClock) {
    if (((m_baFxData >> 2) & 1) == 0) return;
    UpdateActive(frameClock);
}

// 0x001b5e20 CKExplosionNodeFx_SetDirection (TOC1 -0x2144 0, -0x2158 1, -0x2154 0.99, -0x2150 -0.99; the axes
// 0x00c50d34 X / 0x00c50d40 Y): the cross products with fmsubs as the original.
void CKExplosionNodeFx::SetDirection(const CVector3* direction, const IKSerializable* owner) {
    if ((m_baFxData & 2u) == 0 || m_pOwner != owner) return;
    float ax = direction->x, ay = direction->y, az = direction->z;
    const float length = std::sqrt(ppc::fmadds(az, az, ppc::fmadds(ax, ax, ay * ay)));  // 0x00010690
    if (length != 0.0f) {
        const float inverse = 1.0f / length;
        az = az * inverse;
        ay = ay * inverse;
        ax = ax * inverse;
    }
    float ux, uy, uz, vx, vy, vz;
    if (ay >= 0.99f || !(ay > -0.99f)) {
        const float rx = 1.0f, ry = 0.0f, rz = 0.0f;  // the X axis
        ux = ppc::fmsubs(rz, ay, ry * az);
        uz = ppc::fmsubs(ry, ax, rx * ay);
        uy = ppc::fmsubs(rx, az, rz * ax);
        vy = ppc::fmsubs(uz, ax, ux * az);
        vx = ppc::fmsubs(uy, az, uz * ay);
        vz = ppc::fmsubs(ux, ay, uy * ax);
    } else {
        const float rx = 0.0f, ry = 1.0f, rz = 0.0f;  // the Y axis
        vx = ppc::fmsubs(ry, az, rz * ay);
        vy = ppc::fmsubs(rz, ax, rx * az);
        vz = ppc::fmsubs(rx, ay, ry * ax);
        uz = ppc::fmsubs(vy, ax, vx * ay);
        ux = ppc::fmsubs(vz, ay, vy * az);
        uy = ppc::fmsubs(vx, az, vz * ax);
    }
    RwMatrix* m = m_pMatrix;
    m->at = {ax, ay, az};
    m->flags &= 0xfffdfffcu;
    m->right = {vx, vy, vz};
    m->flags &= 0xfffdfffcu;
    m->up = {ux, uy, uz};
    m->flags &= 0xfffdfffcu;
}

// 0x001b6438 CKExplosionNodeFx_SetPosition (CKProjectileTypeBallisticPFX's launch explosion)
void CKExplosionNodeFx::SetPosition(const CVector3* direction, const CVector3* position, const IKSerializable* owner) {
    if ((m_baFxData & 2u) == 0 || m_pOwner != owner) return;
    m_pMatrix->pos = {position->x, position->y, position->z};
    m_pMatrix->flags &= 0xfffdffffu;
    SetDirection(direction, m_pOwner);  // 0x001b5e20
}

// 0x001b66e8 CKExplosionNodeFx_SetTranslation
void CKExplosionNodeFx::SetTranslation(const CVector3* position, const IKSerializable* owner) {
    if ((m_baFxData & 2u) == 0 || m_pOwner != owner) return;
    m_pMatrix->pos = {position->x, position->y, position->z};
    m_pMatrix->flags &= 0xfffdffffu;
}

// 0x001b6368 CKExplosionNodeFx_SetMatrix
void CKExplosionNodeFx::SetMatrix(const RwMatrix* matrix, const IKSerializable* owner) {
    if ((m_baFxData & 2u) == 0 || m_pOwner != owner) return;
    *m_pMatrix = *matrix;
}

// 0x001b6318 CKExplosionNodeFx_SetDamageCategory
void CKExplosionNodeFx::SetDamageCategory(uint8_t category, const IKSerializable* owner) {
    if ((m_baFxData & 2u) == 0 || m_pOwner != owner) return;
    m_ui8DamageCategory = category;
}

// 0x001b6340 CKExplosionNodeFx_SetDamageOwner
void CKExplosionNodeFx::SetDamageOwner(IKSerializable* damageOwner, const IKSerializable* owner) {
    if ((m_baFxData & 2u) == 0 || m_pOwner != owner) return;
    m_pDamageOwner = damageOwner;
}

// 0x001b62c8 CKExplosionNodeFx_SetDamage
void CKExplosionNodeFx::SetDamage(IKSerializable* damage, const IKSerializable* owner) {
    if ((m_baFxData & 2u) == 0 || m_pOwner != owner) return;
    m_pDamage = damage;
}

// 0x001b62f0 CKExplosionNodeFx_SetDamageFlags
void CKExplosionNodeFx::SetDamageFlags(uint16_t flags, const IKSerializable* owner) {
    if ((m_baFxData & 2u) == 0 || m_pOwner != owner) return;
    m_ui16DamageFlags = flags;
}

// 0x001b82a8 CKExplosionNodeFx_Trigger (0x1b8770 is an identical copy)
void CKExplosionNodeFx::Trigger(const IKSerializable* owner, const void* launch) {
    if ((m_baFxData & 2u) == 0 || m_pOwner != owner) return;
    m_baFxData = static_cast<uint8_t>(m_baFxData | 4);
    m_unk44 = launch;
    m_pTriggerOwner = m_pOwner;
    CKExplosionFxData* data = DataOf(this);
    const uint32_t r = static_cast<uint32_t>(Rand_Int());
    const uint32_t pick = static_cast<uint32_t>(
        (static_cast<int64_t>(static_cast<int32_t>(r & 0xffffu)) * static_cast<int32_t>(data->m_unk20)) >> 16);
    CKSound* sound = static_cast<CKSoundDictionaryID*>(data->m_pSoundDico)->GetSound(pick & 0xffffu);  // 0x00112bc0
    if (sound != nullptr) {
        const CVector3 position = {m_pMatrix->pos.x, m_pMatrix->pos.y, m_pMatrix->pos.z};
        sound->SetPosition(&position);  // 0x00110fa0
        sound->m_SoundFlags = (sound->m_SoundFlags & 0xffffffbfu) | CKSound::kFlagMultiInstance;
        sound->SetLoop(0);  // 0x00110fd0
        sound->Play(kZero);  // 0x00111230
    }
    m_fDamageRadius = kTriggerRadius;
    m_fElapsed = 0.0f;
    if (m_pDamageOwner != nullptr) {
        CKSrvCollision* collision = static_cast<CKSrvCollision*>(g_pEngine->m_srvCollision);
        if (m_pDamageSphere == nullptr) {
            m_pDamageSphere = static_cast<CKDynamicBoundingSphere*>(collision->AcquireDynSphere());  // 0x00192a70
        }
        CKDynamicBoundingSphere* sphere = m_pDamageSphere;
        if (sphere != nullptr) {
            sphere->m_fRadius = kTriggerRadius;
            sphere->m_ba8Infos = static_cast<uint8_t>(sphere->m_ba8Infos | 0x08);  // three bit inserts in turn
            sphere->m_ba8Infos = static_cast<uint8_t>(sphere->m_ba8Infos | 0x20);
            sphere->m_ba8Infos = static_cast<uint8_t>(sphere->m_ba8Infos | 0x04);
            sphere->m_v3WorldMove = kNullVector;
            const CVector3 position = {m_pMatrix->pos.x, m_pMatrix->pos.y, m_pMatrix->pos.z};
            sphere->m_v3OldPos = position;
            sphere->m_v3LastWorldPos = position;
            sphere->m_ui8OwnerType = 0;
            sphere->m_ui16PropertiesFlags = 0;
            sphere->m_pOwner = m_pDamageOwner;
            sphere->m_ui8OwnerType = m_ui8DamageCategory;
            sphere->m_ui16PropertiesFlags = static_cast<uint16_t>(sphere->m_ui16PropertiesFlags | m_ui16DamageFlags);
            sphere->m_unk1c = m_pDamage;
            RwFrame* frame = sphere->m_pRwFrame;
            frame->modelling.pos = m_pMatrix->pos;
            frame->modelling.flags &= 0xfffdffffu;
            RwFrame_MarkDirty(frame);  // 0x00010698
            CSGBranch* root = static_cast<CSGBranch*>(g_pEngine->m_dynamicSceneRoot);
            CSGBranch* parent = sphere->m_pParent;
            if (parent != root) {
                if (parent != nullptr) parent->RemoveChild(sphere);  // vt+0x78
                root->AddChild(sphere);                              // vt+0x70
            }
        }
    }
    // The sub-effects due at time 0.
    for (uint32_t i = 0; i < m_subEffects.m_ui32NbUsedElt; ++i) {
        SubEffect& effect = m_subEffects.m_pBlock[i];
        effect.m_bFired = 0;
        CKExplosionFxData::Part* part = data->m_parts.m_pBlock[i];
        if (part->m_unk08 <= m_fElapsed) FireSubEffect(&effect, part);
    }
    data = DataOf(this);
    if (data->m_pVibrationPadData != nullptr) {
        data->m_pVibrationPadData->m_pOwner = this;
        g_pEngine->m_input->PlayVibration(data->m_pVibrationPadData);  // 0x00107d38
        data = DataOf(this);
    }
    const CVector3 position = {m_pMatrix->pos.x, m_pMatrix->pos.y, m_pMatrix->pos.z};
    data->m_pQuakeLauncher->SetSourcePosition(&position);  // 0x001532c8
    data->m_pQuakeLauncher->Trigger();                     // 0x001533c0
}

// 0x001b7fa8 CKExplosionNodeFx_UpdateActive_maybe
void CKExplosionNodeFx::UpdateActive(IKTime* frameClock) {
    if (m_fDuration <= m_fElapsed) {
        bool pending = false;
        for (uint32_t i = 0; i < m_subEffects.m_ui32NbUsedElt && !pending; ++i) pending = m_subEffects.m_pBlock[i].m_bFired == 0;
        if (!pending) {
            Stop();  // vt+0x6c
            return;
        }
    }
    const float dt = frameClock->m_afDeltaTime[0];
    m_fElapsed = m_fElapsed + dt;
    CKExplosionFxData* data = DataOf(this);
    for (uint32_t i = 0; i < m_subEffects.m_ui32NbUsedElt; ++i) {
        SubEffect& effect = m_subEffects.m_pBlock[i];
        if (effect.m_bFired != 0) continue;
        CKExplosionFxData::Part* part = DataOf(this)->m_parts.m_pBlock[i];
        if (part->m_unk08 <= m_fElapsed) FireSubEffect(&effect, part);
    }
    if (m_pDamageOwner == nullptr || m_pDamageSphere == nullptr) return;
    data = DataOf(this);
    const float radius = m_fDamageRadius;
    if (data->m_unk14 - data->m_unk0c < radius) {
        m_pDamageSphere->m_ba8Infos = static_cast<uint8_t>(m_pDamageSphere->m_ba8Infos & 0xfb);
        return;
    }
    const float grown = ppc::fmadds(data->m_unk10 * dt, data->m_unk14 - radius, radius);
    m_pDamageSphere->m_fRadius = grown <= kZero ? kMinimumRadius : grown;
    RwFrame* frame = m_pDamageSphere->m_pRwFrame;
    frame->modelling.pos = m_pMatrix->pos;
    frame->modelling.flags &= 0xfffdffffu;
    RwFrame_MarkDirty(frame);  // 0x00010698
    m_fDamageRadius = data->m_unk14 < grown ? data->m_unk14 : grown;
}

// 0x001b6c20 CKExplosionNodeFx_FireSubEffect: the jump table at TOC1 -0x210c, types 0..8 (others: nothing).
void CKExplosionNodeFx::FireSubEffect(SubEffect* effect, CKExplosionFxData::Part* part) {
    effect->m_bFired = 1;
    switch (effect->m_value) {
    case 0: {
        // The accessor's particle component (+0x04) queues an emission at the matrix's position along its at row with
        // the part's overrides (+0x0c).
        CKSrvFxParticlesAccessor* accessor = static_cast<CKSrvFxParticlesAccessor*>(effect->m_pObject);
        if (accessor == nullptr || accessor->m_pParticles == nullptr) return;
        CKParticlesCpnt* particles = static_cast<CKParticlesCpnt*>(accessor->m_pParticles);
        const CVector3 position{m_pMatrix->pos.x, m_pMatrix->pos.y, m_pMatrix->pos.z};
        const CVector3 at{m_pMatrix->at.x, m_pMatrix->at.y, m_pMatrix->at.z};
        particles->QueueEmission(&position, &at, &static_cast<CKExplosionFxData::PartType0*>(part)->m_overrides);  // 0x001da840
        return;
    }
    case 1: {
        // The projectiles: +0x10 of them from the part's accessor (+0x0c, one with a type), each from the matrix's
        // position raised by 0.1 and spread by +0x34 (x a random in (-1, 1] per axis), along +0x1c spread by +0x28 (the
        // same, normalised; through the matrix with the data's +0x18 bit 1), at +0x14 spread by +0x18; seven draws each.
        // The damage +0x40, the owner the damage owner (+0x30) or the trigger's (+0x4c). The original's Launch90 (with
        // +0x44) forwards to the type's LaunchEx without it. DOTD: the matrix argument of the original (Trigger's third
        // argument, 0 for every LVL010 caller but the crumbly zones) is not kept: null.
        CKExplosionFxData::PartType1* p = static_cast<CKExplosionFxData::PartType1*>(part);
        CKProjectileAccessor* accessor = static_cast<CKProjectileAccessor*>(p->m_pObject);
        if (accessor == nullptr || accessor->m_pProjectileType == nullptr) return;
        auto spread = []() {
            const uint32_t r = static_cast<uint32_t>(Rand_Int()) & 0xffffu;  // 0x00011500
            return ppc::fmadds(static_cast<float>(static_cast<double>(r)), -3.05180438e-05f, 1.0f);  // TOC -0x2108 / -0x2158
        };
        for (uint32_t n = p->m_unk10; n != 0; --n) {
            CVector3 pos{m_pMatrix->pos.x, m_pMatrix->pos.y, m_pMatrix->pos.z};
            const float rx = spread();
            const float ry = spread();
            const float rz = spread();
            CVector3 dir{p->m_unk28.x * rx, p->m_unk28.y * ry, p->m_unk28.z * rz};
            dir.x = dir.x + p->m_unk1c.x;
            dir.y = dir.y + p->m_unk1c.y;
            dir.z = dir.z + p->m_unk1c.z;
            const float length = static_cast<float>(std::sqrt(static_cast<double>(
                ppc::fmadds(dir.z, dir.z, ppc::fmadds(dir.x, dir.x, dir.y * dir.y)))));  // 0x00010690
            if (length != 0.0f) {
                const float inverse = 1.0f / length;
                dir.z = dir.z * inverse;
                dir.x = dir.x * inverse;
                dir.y = dir.y * inverse;
            }
            CVector3 along = dir;
            if ((DataOf(this)->m_unk18 & 2u) != 0) {
                Mat4_TransformVectors(reinterpret_cast<const CMatrix34*>(m_pMatrix), &along, &dir, 1);  // 0x0023f7b0
            }
            pos.y = pos.y + 0.1f;  // TOC -0x2104
            const float bx = pos.x;
            const float by = pos.y;
            pos.x = ppc::fmadds(spread(), p->m_unk34.x, bx);
            const float bz = pos.z;
            pos.y = ppc::fmadds(spread(), p->m_unk34.y, by);
            pos.z = ppc::fmadds(spread(), p->m_unk34.z, bz);
            const float speed = ppc::fmadds(spread(), p->m_unk18, p->m_unk14);
            IKSerializable* owner = m_pDamageOwner != nullptr ? m_pDamageOwner : const_cast<IKSerializable*>(m_pTriggerOwner);
            accessor->LaunchEx(&pos, &along, speed, m_pDamage, owner, nullptr);  // 0x001f2a98 Launch90 / 0x001f2988
        }
        return;
    }
    case 3: {
        // The sparks: the part's spark data (+0x0c) takes the explosion's matrix as its own (+0x14), then one of its
        // nodes from the FX service's pool is started and released (the shared tail 0x001b7c7c).
        CKSparkFxData* data = static_cast<CKSparkFxData*>(static_cast<CKExplosionFxData::PartObject*>(part)->m_pObject);
        if (m_pMatrix != nullptr) *static_cast<RwMatrix*>(data->m_unk14) = *m_pMatrix;
        IKFx* node = static_cast<CKSrvFx*>(g_pEngine->m_srvFx)->AcquireFx(data, this);  // TOC1 -0x2138 -> +0x60
        if (node != nullptr) node->ReleaseReservation(this);  // vt+0x54
        return;
    }
    case 2: {
        // The shock wave: the part's data (+0x0c) takes the explosion's colour (+0x48 into its +0x40), then a node of it
        // from the FX service's pool turned to the matrix's up, placed at its position, triggered and released.
        CKShockWaveFxData* data = static_cast<CKShockWaveFxData*>(static_cast<CKExplosionFxData::PartObject*>(part)->m_pObject);
        std::memcpy(data->m_unk40, m_aColor, sizeof m_aColor);
        IKFx* node = static_cast<CKSrvFx*>(g_pEngine->m_srvFx)->AcquireFx(data, this);
        if (node == nullptr) return;
        CKShockWaveNodeFx* wave = static_cast<CKShockWaveNodeFx*>(node);
        if (m_pMatrix != nullptr) {
            const CVector3 up{m_pMatrix->up.x, m_pMatrix->up.y, m_pMatrix->up.z};
            wave->SetDirection(&up, this);  // 0x001d3340
            const CVector3 at{m_pMatrix->pos.x, m_pMatrix->pos.y, m_pMatrix->pos.z};
            wave->SetPosition(&at, this);   // 0x001d2410
        }
        wave->Trigger(this);                // 0x001d2928
        wave->ReleaseReservation(this);     // vt+0x54
        return;
    }
    case 4:
    case 8: {
        // A node of the part's data from the FX service's pool, started and released (the shared tail 0x001b7c7c).
        IKFxData* data = static_cast<IKFxData*>(static_cast<CKExplosionFxData::PartObject*>(part)->m_pObject);
        IKFx* node = static_cast<CKSrvFx*>(g_pEngine->m_srvFx)->AcquireFx(data, this);
        if (node != nullptr) node->ReleaseReservation(this);  // vt+0x54
        return;
    }
    case 6: {
        // A data whose vt+0x50 is set (the time scaling's) goes to the FX service's unique node of its class (+0x1c, the
        // first whose class key is the data's vt+0x54): SetDataAndOwner (vt+0x8c), then Start (vt+0x64) when the node
        // is free (flags +0x0c: bit 0 set, bit 1 clear). Any other: a pooled node of it, set and started but neither
        // reserved (the +0x0c bits are left) nor released.
        IKFxData* data = static_cast<IKFxData*>(static_cast<CKExplosionFxData::PartObject*>(part)->m_pObject);
        CKSrvFx* service = static_cast<CKSrvFx*>(g_pEngine->m_srvFx);
        const uint32_t key = data->GetAssociatedFxClassIdentifier();  // vt+0x54
        if (data->Vf50() != 0) {
            for (uint32_t i = 0; i < service->m_ui32UniqueFxArraySize; ++i) {
                IKFx* node = static_cast<IKFx*>(service->m_apUniqueFxArray[i]);
                if ((node->GetClassID() << 6) + node->GetClassType() != key) continue;  // vt+0x18 / vt+0x14
                node->SetDataAndOwner(data, this);                                      // vt+0x8c
                if ((node->m_baFxData & 1u) != 0 && (node->m_baFxData & 2u) == 0) node->Vf64();
                return;
            }
            return;
        }
        const int32_t typeId = static_cast<int32_t>(data->GetAssociatedFxClassType());  // vt+0x58
        for (uint32_t i = 0; i < service->m_ui32EltNb; ++i) {
            const CKSrvFx::CMappingindex& mapping = service->m_apMappingIndexTable[i];
            if (mapping.m_ui32ClassId != key || mapping.m_ui32NbTypeFx == 0) continue;
            const CKSrvFx::CUnderMappingindex* under = mapping.m_aUnderMapping;
            uint32_t k = 0;
            while (under[k].m_i32FxTypeId != typeId) {
                if (++k == mapping.m_ui32NbTypeFx) break;
            }
            if (k == mapping.m_ui32NbTypeFx) continue;
            for (uint32_t n = 0; n < under[k].m_ui32MaxSize; ++n) {
                IKFx* node = static_cast<IKFx*>(under[k].m_apFxArrayForTypeId[n]);
                if ((node->m_baFxData & 1u) == 0 || (node->m_baFxData & 2u) != 0) continue;
                node->SetFxData(data);  // vt+0x84
                node->SetOwner(this);   // vt+0x88
                node->Vf64();           // vt+0x64
                return;
            }
            return;
        }
        return;
    }
    case 7: {
        // The mesh pop: a node of the part's data from the FX service's pool, placed at the explosion's matrix
        // (CKMeshPopNodeFx_SetMatrixForOwner_maybe 0x1c9428), popped and released (the shared tail 0x001b6dc0).
        IKFxData* data = static_cast<IKFxData*>(static_cast<CKExplosionFxData::PartObject*>(part)->m_pObject);
        IKFx* node = static_cast<CKSrvFx*>(g_pEngine->m_srvFx)->AcquireFx(data, this);
        if (node == nullptr) return;
        CKMeshPopNodeFx* pop = static_cast<CKMeshPopNodeFx*>(node);
        if (m_pMatrix != nullptr) pop->SetMatrixForOwner(this, reinterpret_cast<const CMatrix34*>(m_pMatrix));
        pop->TriggerPop(this, 0);         // 0x001caf50
        pop->ReleaseReservation(this);    // vt+0x54
        return;
    }
    case 5: {
        // The distortion: a node of the part's data from the FX service's pool, centred on the explosion's matrix
        // position (no null test of the matrix), then released.
        IKFxData* data = static_cast<IKFxData*>(static_cast<CKExplosionFxData::PartObject*>(part)->m_pObject);
        IKFx* node = static_cast<CKSrvFx*>(g_pEngine->m_srvFx)->AcquireFx(data, this);
        if (node == nullptr) return;
        CKDistortionNodeFx* distortion = static_cast<CKDistortionNodeFx*>(node);
        const CVector3 center = {m_pMatrix->pos.x, m_pMatrix->pos.y, m_pMatrix->pos.z};
        distortion->SetCenterForOwner(&center, this);  // 0x001af410
        distortion->ReleaseReservation(this);          // vt+0x54
        return;
    }
    default:
        return;
    }
}

// 0x001b61c0 CKExplosionNodeFx_RecursiveRegistration
void CKExplosionNodeFx::RecursiveRegistration(int32_t type) {
    g_pEngine->m_pSavingManager->RegisterSerializableObject(this, nullptr);  // vt+0x24
    for (uint8_t i = 0; i < m_subEffects.m_ui32NbUsedElt; ++i) {
        const SubEffect& effect = m_subEffects.m_pBlock[i];
        if (effect.m_pObject != nullptr && effect.m_value < 1) effect.m_pObject->RecursiveRegistration(type);  // vt+0x24
    }
}

// 0x001b64a0 CKExplosionNodeFx_CountSubEffectsOfType_maybe
int32_t CKExplosionNodeFx::CountSubEffectsOfType(uint32_t type, const IKSerializable* owner) const {
    if ((m_baFxData & 2u) == 0 || m_pOwner != owner) return 0;
    int32_t count = 0;
    for (uint32_t i = 0; i < m_subEffects.m_ui32NbUsedElt; ++i) {
        if (static_cast<uint32_t>(m_subEffects.m_pBlock[i].m_value) == type) ++count;
    }
    return count;
}

// 0x001b6530 CKExplosionNodeFx_GetNthSubEffectOfType_maybe
IKSerializable* CKExplosionNodeFx::GetNthSubEffectOfType(uint32_t type, const IKSerializable* owner, int32_t n) const {
    if ((m_baFxData & 2u) == 0 || m_pOwner != owner || type <= 1) return nullptr;
    const CKExplosionFxData* data = static_cast<const CKExplosionFxData*>(m_pFxData);
    for (uint32_t i = 0; i < m_subEffects.m_ui32NbUsedElt; ++i) {
        if (static_cast<uint32_t>(m_subEffects.m_pBlock[i].m_value) == type) --n;
        if (n < 0) return static_cast<CKExplosionFxData::PartObject*>(data->m_parts.m_pBlock[i])->m_pObject;
    }
    return nullptr;
}
