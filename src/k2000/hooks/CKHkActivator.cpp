// Reconstructed original translation unit: 0x3f9830-0x3fb460 (GAME_TOC1, main_toc1), 32 functions, 30 live.
// Primary class: CKHkActivator  key 0xd02  category Hook  size 0x54  vtable 0xb25268
// Other owners: KBase9C2 (2)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x3f9830  CKHkActivator_Delete  (the factory Delete, DOTD_DECLARE_FACTORIES)
//   [x] 0x3f9880  CKHkActivator_SetDefaultState
//   [ ] 0x3f98c8  RegisterCKHkActivatorClass
//   [ ] 0x3f9940  _GLOBAL__I_3f9940
//   [x] 0x3f9950  CKHkActivator_GetInfo
//   [x] 0x3f9a50  CKHkActivator_CheckContactsAndToggle_maybe  (the CKMecaCpnt FX call: a STUB until R02's CKMecaCpnt lands)
//   [x] 0x3f9c28  CKHkActivator_Resume  (the actor base's 0x3f6e60: inherited)
//   [x] 0x3f9c50  CKHkActivator_Pause  (the actor base's 0x3f6e58: inherited)
//   [x] 0x3f9c78  CKHkActivator_Stop  (the actor base's 0x3f6e50: inherited)
//   [x] 0x3f9ca0  CKHkActivator_PostLoad
//   [ ] 0x3f9d10  CKHkActivator_Save
//   [x] 0x3f9d38  CKHkActivator_RecursiveRegistration  (the actor base's 0x3f6ee8: inherited)
//   [ ] 0x3f9d60  CKHkActivator_Construct  [dead]
//   [x] 0x3f9d98  CKHkActivator_DeleteArray  (DOTD_DECLARE_FACTORIES)
//   [x] 0x3f9e38  CKHkActivator_AttachSounds  (CKHkActivator::KGLObjectAttached)
//   [x] 0x3f9ec0  CKHkActivator_Restart
//   [x] 0x3f9f78  CKHkActivator_Destructor  (the header's destructor)
//   [x] 0x3f9fa8  CKHkActivator_BaseDestructor  (the header's destructor)
//   [x] 0x3f9fd8  CKHkActivator_DeletingDestructor  (the header's destructor)
//   [x] 0x3fa020  CKHkActivator_Start
//   [x] 0x3fa0e0  CKHkActivator_MessageProc
//   [x] 0x3fa2a0  CKHkActivator_ApplyStatePreset_maybe  (CKHkActivator::ApplyStatePreset)
//   [x] 0x3fa2c8  CKHkActivator_Destroy  (the actor base's 0x3f6e08: inherited)
//   [ ] 0x3fa2f0  CKHkActivator_Construct_2  [dead]
//   [x] 0x3fa328  CKHkActivator_OnActivate  (CKHkActivator::VfA0)
//   [x] 0x3fa618  CKHkActivator_Update
//   [x] 0x3face0  CKHkActivator_OnDeactivate  (CKHkActivator::VfA4)
//   [x] 0x3faf38  CKHkActivator_CreateArray  (DOTD_DECLARE_FACTORIES)
//   [x] 0x3fafe8  CKHkActivator_Create  (the constructor)
//   [x] 0x3fb040  CKHkActivator_Load
//   [x] 0x3fb408  KBase9C2_SetDefaultState  (CKHkBridgeBase::SetDefaultState, k2000/misc/CKHkBridgeBase.h)
//   [x] 0x3fb420  KBase9C2_SetGameState  (CKHkBridgeBase::SetGameState, k2000/misc/CKHkBridgeBase.cpp)
//
//   [ ] 0x9c0eb8  CKHkActivator_IsKindOfClass  [inline]
//   [ ] 0x9c0f10  CKHkActivator_GetClassType  [inline]
//   [ ] 0x9c0f18  CKHkActivator_GetClassID  [inline]
//   [ ] 0x9c0f20  CKHkActivator_vfD8  [inline]
//   [ ] 0x9c0f28  CKHkActivator_GetTriggerProp98  [inline]
#include "k2000/hooks/CKHkActivator.h"

#include <cmath>

#include "Renderware/rpprtstd/RpPrtStd.h"
#include "Renderware/rwcore/RwCamera.h"
#include "Spyro2008/groups/IKGrpHero.h"
#include "Spyro2008/hooks/CKHkS08Hero.h"
#include "Spyro2008/logic/CKS08GameManager.h"
#include "crt/ppc_ops.h"
#include "k2000/core/IKInfo.h"
#include "k2000/core/Stub.h"
#include "k2000/dictionaries/CAnimationDictionary.h"
#include "k2000/dictionaries/CKSoundDictionaryID.h"
#include "k2000/io/IKFile.h"
#include "k2000/logic/CDefaultGameManager.h"
#include "k2000/logic/sound/CKSound.h"
#include "k2000/misc/Engine.h"
#include "k2000/misc/Mat4.h"
#include "k2000/scenegraph/CAnimatedNode.h"
#include "k2000/scenegraph/CParticlesNodeFx.h"
#include "k2000/scenegraph/CSGBranch.h"
#include "k2000/scenegraph/CSGMovable.h"
#include "k2000/scenegraph/IKBoundingVolume.h"
#include "k2000/components/CKMecaCpnt.h"
#include "k2000/services/CKSrvCollision.h"
#include "k2000/services/ICollisionMesh.h"
#include "k2000/system/IKTime.h"

namespace {

const float kZero = 0.0f;  // TOC1 +0x4714

CKSrvCollision* Collision() { return static_cast<CKSrvCollision*>(g_pEngine->m_srvCollision); }  // engine +0x58
CKSoundDictionaryID* Sounds(const CKHkActivator* a) { return static_cast<CKSoundDictionaryID*>(a->m_pSoundDictionary); }
CAnimatedNode* Node(const CKHkActivator* a) { return static_cast<CAnimatedNode*>(a->m_pKGLObject); }
IKBoundingVolume* Volume(IKSerializable* v) { return static_cast<IKBoundingVolume*>(v); }

// The grounds' hurt flag (+0x38 bit 3, a halfword) set or cleared, the advance ground's too when there is one.
void SetGroundsHurt(CKHkActivator* a, bool hurt) {
    ICollisionMesh* ground = static_cast<ICollisionMesh*>(a->m_pGround);
    ground->m_ui16PropertiesFlags = hurt ? static_cast<uint16_t>(ground->m_ui16PropertiesFlags | 8u)
                                         : static_cast<uint16_t>(ground->m_ui16PropertiesFlags & ~8u);
    ICollisionMesh* advance = static_cast<ICollisionMesh*>(a->m_pAdvanceGround);
    if (advance == nullptr) return;
    advance->m_ui16PropertiesFlags = hurt ? static_cast<uint16_t>(advance->m_ui16PropertiesFlags | 8u)
                                          : static_cast<uint16_t>(advance->m_ui16PropertiesFlags & ~8u);
}

// The particle node stopped (properties 0x400 / 0x80000 cleared, the emitter's emit flag 0x8 cleared).
void StopParticles(IKSerializable* node) {
    CParticlesNodeFx* fx = static_cast<CParticlesNodeFx*>(node);
    fx->m_sgProperties &= 0xfff7fbffu;
    fx->m_pRpPrtStdEmitter->flag &= ~static_cast<uint32_t>(rpPRTSTDEMITTERFLAGEMIT);
}

// A sphere moved under `parent` (its old parent's vt+0x78, the new one's vt+0x70).
void Reparent(IKSerializable* sphere, IKSerializable* parent) {
    IKBoundingVolume* volume = Volume(sphere);
    if (volume->m_pParent != nullptr) volume->m_pParent->RemoveChild(volume);  // vt+0x78
    static_cast<CSGBranch*>(parent)->AddChild(volume);                       // vt+0x70
}

// 0x003f7ea0 CKMecaCpnt_AppendPointAndRequestUpdate_maybe (XXL2 CKMecaCpnt::PlayMecaActivationFX(CVector3, bool)):
// the component's particle node (+0x04) gets the point and starts (R02's CKMecaCpnt).
void PlayMecaActivationFx(IKSerializable* cpnt, const CVector3* point, int32_t show) {
    static_cast<CKMecaCpnt*>(cpnt)->PlayMecaActivationFX(point, show);
}

// 0x009c0f28 CKHkActivator_GetTriggerProp98: +0x0c bit 6.
uint32_t TriggerProp98(IKSerializable* self, uint32_t) { return (static_cast<CKHkActivator*>(self)->m_bitArray >> 6) & 1u; }

}  // namespace

CKHkActivator::CKHkActivator() {
    m_i32MessageIndex = 0;
    m_tsActivateStarter.m_apDatas = nullptr;
    m_tsActivateStarter.m_ui32NbDatas = 0;
    m_tsDeactivateStarter.m_apDatas = nullptr;
    m_tsDeactivateStarter.m_ui32NbDatas = 0;
    m_pAnimatedDictionary = nullptr;
    m_pSoundDictionary = nullptr;
    m_pDodgeBS = nullptr;
    m_pHitBS = nullptr;
    m_pMecaCpnt = nullptr;
    m_pGround = nullptr;
    m_pParticle = nullptr;
    m_pAdvanceGround = nullptr;
}

// 0x003f9880 CKHkActivator_SetDefaultState
void CKHkActivator::SetDefaultState(int32_t /*flag*/) { ApplyStatePreset(0); }  // vt+0xc8

// 0x003f9950 CKHkActivator_GetInfo
int32_t CKHkActivator::GetInfo(IKInfo* info, int32_t request) {
    const int32_t base = CKHkActorBase::GetInfo(info, request);  // KStub_Return1 0x3f7140
    int32_t own = 1;
    if (request == kGetInfoValueAccessor && info->m_ui32Id == 0x98) {
        AnswerInfo(info, TriggerProp98, 0);  // 0x00038cd8
        own = 0;
    }
    if (base == 2 || own == 2) return 2;
    if (base != 0) return own;
    return 0;
}

// 0x003f9a50 CKHkActivator_CheckContactsAndToggle_maybe
void CKHkActivator::CheckContactsAndToggle() {
    for (ICollision* c = static_cast<ICollision*>(Volume(m_pHitBS)->m_CollisionResList); c != nullptr; c = c->m_pNext) {
        IKSerializable* other = c->GetBoundingVolume1();  // vt+0x00
        if (Volume(other)->m_pOwner == this) {
            other = c->GetBoundingVolume2();  // vt+0x04
        } else {
            c->GetBoundingVolume2();  // vt+0x04 (the result unused)
        }
        if ((Volume(other)->m_ui16PropertiesFlags & 2u) == 0) continue;
        const uint32_t bits = m_bitArray;
        if ((bits & 0x40u) == 0) {
            m_bitArray = (m_bitArray & 0xffffff7fu) | 0x80u;
        } else {
            m_bitArray = (m_bitArray & 0xffffff7fu) | ((((bits >> 7) & 1u) ^ 1u) << 7);  // reusable: toggled
        }
        Collision()->RemoveVolume(Volume(m_pHitBS));  // 0x00192bc0
        CKSound_Play(kZero, Sounds(this)->GetSound(0));  // 0x00112bc0, 0x00111230
        PlayMecaActivationFx(m_pMecaCpnt, c->GetWorldContactPoint(), 1);  // vt+0x20, 0x003f7ea0
    }
}

// 0x003f9ca0 CKHkActivator_PostLoad
int32_t CKHkActivator::PostLoad(int32_t type) {
    CKHkActorBase::PostLoad(type);  // 0x003f6e70
    m_tsActivateStarter.PostLoad(type);    // 0x00236330
    m_tsDeactivateStarter.PostLoad(type);  // 0x00236330
    return 1;
}

// 0x003f9e38 CKHkActivator_AttachSounds
void CKHkActivator::KGLObjectAttached(IKSerializable* /*leaf*/) {
    Sounds(this)->GetSound(0)->SetAttachObject(m_pKGLObject);  // 0x00112bc0, 0x00111350
    Sounds(this)->GetSound(1)->SetAttachObject(m_pKGLObject);
    Sounds(this)->GetSound(2)->SetAttachObject(m_pKGLObject);
}

// 0x003f9ec0 CKHkActivator_Restart
void CKHkActivator::Restart() {
    if ((m_bitArray & 4u) != 0) return;
    m_bitArray = (m_bitArray & 0xfffffdffu) | 0x200u;
    if (m_pGround == nullptr) return;
    if ((m_bitArray & 0x10u) == 0) return;
    SetGroundsHurt(this, (m_bitArray & 0x80u) != 0);
}

// 0x003fa020 CKHkActivator_Start
void CKHkActivator::Start() {
    CKHkActorBase::Start();  // 0x003f6e48 (empty)
    m_bitArray = (m_bitArray & 0xfffffdffu) | 0x200u;
    if (m_pDodgeBS != nullptr) Collision()->RemoveVolume(Volume(m_pDodgeBS));  // 0x00192bc0
    Collision()->RemoveVolume(Volume(m_pHitBS));
}

// 0x003fa0e0 CKHkActivator_MessageProc
int32_t CKHkActivator::MessageProc(uint16_t message, void* data) {
    const int32_t base = CKHkActorBase::MessageProc(message, data);  // 0x003f7148
    int32_t own = 1;
    if (message == 0x997) {
        own = 0;
        const uint8_t on = *static_cast<const uint8_t*>(data);
        if (on != ((m_bitArray >> 9) & 1u)) {
            if (on == 0) {
                m_bitArray &= 0xfffffdffu;
            } else {
                m_bitArray = (m_bitArray & 0xfffffdffu) | 0x200u;
            }
        }
    } else if (message == 0x2666) {
        own = 0;
        reinterpret_cast<int32_t*>(data)[1] = m_i32MessageIndex;  // the data's word +4
    } else if (message == 0x996) {
        own = 0;
        if (*static_cast<const uint8_t*>(data) == 0) {
            m_bitArray &= 0xffffff7fu;
        } else {
            m_bitArray = (m_bitArray & 0xffffff7fu) | 0x80u;
        }
    }
    if (base == 3 || own == 3) return 3;
    if (base == 2 || own == 2) return 2;
    return base == 0 ? 0 : own;
}

// 0x003fa2a0 CKHkActivator_ApplyStatePreset_maybe
void CKHkActivator::ApplyStatePreset(int32_t state) {
    const uint32_t bits = (m_bitArray & 0xffffff7fu) | ((static_cast<uint32_t>(state) << 7) & 0xffffff80u);
    m_bitArray = (bits & 0xfffffeffu) | 0x100u;
}

// 0x003fa328 CKHkActivator_OnActivate
void CKHkActivator::VfA0() {
    CKHkActorBase::VfA0();  // 0x003f7338
    CAnimatedNode* node = Node(this);
    node->m_sgProperties &= 0xfffffffbu;  // shown
    const uint32_t word = static_cast<uint32_t>(static_cast<CAnimationDictionary*>(m_pAnimatedDictionary)->m_apAnimations[0]);
    if ((m_bitArray & 0x80u) == 0) {
        node->PlayAnim(kZero, word, 0);  // 0x000c98b8
    } else {
        node->PlayAnim(node->GetCurrentAnimDuration(), word, 0);  // 0x000c9768: on, at its end
    }
    if (m_pDodgeBS != nullptr) Reparent(m_pDodgeBS, m_pKGLObject);
    Reparent(m_pHitBS, m_pKGLObject);
    if ((m_bitArray & 0x80u) == 0) {
        if (m_pDodgeBS != nullptr) Collision()->AddVolume(Volume(m_pDodgeBS));  // 0x00192b80
        Collision()->AddVolume(Volume(m_pHitBS));
    }
    if (m_pGround != nullptr) {
        static_cast<ICollisionMesh*>(m_pGround)->SetActive(1);  // 0x001a6b70
        if ((m_bitArray & 0x10u) != 0) SetGroundsHurt(this, (m_bitArray & 0x80u) != 0);
    }
    if (m_pParticle != nullptr) StopParticles(m_pParticle);
}

// 0x003fa618 CKHkActivator_Update
void CKHkActivator::Update(IKTime* clock) {
    CKHkActorBase::Update(clock);  // 0x003f6e68 (empty)
    CAnimatedNode* node = Node(this);
    const float duration = node->GetCurrentAnimDuration();  // 0x000c9768
    const float time = node->GetCurrentAnimTime();          // 0x000c95a8
    if ((m_bitArray & 0x200u) == 0) {
        if (duration <= time) return;  // cror lt|eq: a NaN goes on
        m_bitArray = (m_bitArray & 0xffffff7fu) | 0x80u;
        Collision()->RemoveVolume(Volume(m_pHitBS));  // 0x00192bc0
    }
    CheckContactsAndToggle();
    const float dt = clock->m_afDeltaTime[0];  // +0x1c
    if ((m_bitArray & 0x80u) == 0) {
        // Off: back to the start.
        m_bitArray &= 0xfffffeffu;
        if (time != kZero) {
            const float t = time - dt;
            if (t > kZero) {
                node->SetCurrentAnimTime(t);  // 0x000c9690
            } else {  // ble: a NaN ends too
                QueueTriggerSignals(&m_tsDeactivateStarter);  // 0x00236338
                if (m_pParticle != nullptr) StopParticles(m_pParticle);
                Sound_Stop(Sounds(this)->GetSound(1), 0);  // 0x001111b0
                Sound_Stop(Sounds(this)->GetSound(2), 0);
                node->SetCurrentAnimTime(kZero);
                Collision()->AddVolume(Volume(m_pHitBS));  // 0x00192b80
                if (m_pGround != nullptr && (m_bitArray & 0x10u) != 0) SetGroundsHurt(this, false);
            }
        }
    } else if (duration != time) {
        // On: forward to the end.
        const float t = time + dt;
        if (duration > t) {
            node->SetCurrentAnimTime(t);  // 0x000c9690
        } else {  // bgt not taken: a NaN ends too
            CParticlesNodeFx* fx = static_cast<CParticlesNodeFx*>(m_pParticle);
            if (fx == nullptr) {
                CKSound* sound = Sounds(this)->GetSound(1);
                if (sound->CountInstances() == 0) {
                    sound->SetLoop(1);   // 0x00110fd0
                    sound->Play(kZero);  // 0x00111230
                }
            } else {
                const uint32_t properties = (fx->m_sgProperties & ~0x400u) | 0x400u;
                fx->m_sgProperties = properties & 0xfff7ffffu;
                fx->m_fEmissionSpeedAdjustment = 0.0f;  // stw 0
                fx->m_pRpPrtStdEmitter->flag |= rpPRTSTDEMITTERFLAGACTIVE | rpPRTSTDEMITTERFLAGEMIT;  // | 0xa
                CVector3 points[2];
                fx->TransformEmitPointsToWorld(points, 2, nullptr, 0);  // 0x000e64b0
                CKSound* first = Sounds(this)->GetSound(1);
                if (first->CountInstances() == 0) {
                    first->SetPosition(&points[0]);  // 0x00110fa0
                    first->SetLoop(1);
                    first->Play(kZero);
                }
                CKSound* second = Sounds(this)->GetSound(2);
                if (second->CountInstances() == 0) {
                    second->SetPosition(&points[1]);
                    second->SetLoop(1);
                    second->Play(kZero);
                }
            }
            if (m_pGround != nullptr && (m_bitArray & 0x10u) != 0) SetGroundsHurt(this, true);
            node->SetCurrentAnimTime(duration);
            if ((m_bitArray & 0x100u) == 0 && (m_bitArray & 0x200u) != 0) {
                QueueTriggerSignals(&m_tsActivateStarter);  // 0x00236338
                m_bitArray = (m_bitArray & 0xfffffeffu) | 0x100u;
            }
            if ((m_bitArray & 8u) != 0) m_bitArray &= 0xffffff7fu;  // switches itself off again
            if ((m_bitArray & 0x40u) != 0) Collision()->AddVolume(Volume(m_pHitBS));  // reusable: hit again
        }
    }
    // The contextual message (bit 5) of an activator that is off: the controlled heroes within 1.5 that face it.
    if ((m_bitArray & 0x20u) == 0 || (m_bitArray & 0x80u) != 0) return;
    IKGrpHero* group = static_cast<IKGrpHero*>(g_pEngine->m_gameManager->m_unk04[1]);  // engine +0x8c -> +0x08
    const uint8_t count = group->m_ui8ControlledHeroCount;  // 0x002ca288
    const float one = 1.0f;    // TOC1 +0x4724
    const float range = 1.5f;  // TOC1 +0x4720
    for (int32_t i = static_cast<int32_t>(count) - 1; i != -1; --i) {
        const RwMatrix* ltm = FrameLtm(static_cast<CSGMovable*>(m_pKGLObject)->m_pRwFrame);  // node +0x04, +0x80
        CKHkS08Hero* hero = static_cast<CKHkS08Hero*>(group->m_apControlledHeroes[i]);  // 0x002ca0e0
        const float* p = hero->GetPositionPtr();  // 0x00361968
        float dy = ltm->pos.y - p[1];
        float dx = ltm->pos.x - p[0];
        float dz = ltm->pos.z - p[2];
        const float length = std::sqrt(ppc::fmadds(dz, dz, ppc::fmadds(dx, dx, dy * dy)));  // Math_Sqrtf 0x10690
        if (length != kZero) {
            if (!(length <= range)) continue;  // cror lt|eq: a NaN skips the hero
            const float scale = one / length;
            dz = dz * scale;
            dx = dx * scale;
            dy = dy * scale;
        }
        const float facing = ppc::fmadds(dz, hero->m_unk548, ppc::fmadds(dx, hero->m_unk540, dy * hero->m_unk544));  // 0x00361a50
        if (!(facing > kZero)) continue;  // ble
        static_cast<CKS08GameManager*>(g_pEngine->m_gameManager)->SetHeroInteractionTarget(this, 1, static_cast<uint8_t>(i));  // 0x004ee770
    }
}

// 0x003face0 CKHkActivator_OnDeactivate
void CKHkActivator::VfA4() {
    CKHkActorBase::VfA4();  // 0x003f7370
    if (m_pDodgeBS != nullptr) {
        Collision()->RemoveVolume(Volume(m_pDodgeBS));  // 0x00192bc0
        Reparent(m_pDodgeBS, g_pEngine->m_dynamicSceneRoot);  // engine +0x14
    }
    Collision()->RemoveVolume(Volume(m_pHitBS));
    Reparent(m_pHitBS, g_pEngine->m_dynamicSceneRoot);
    if (m_pGround != nullptr) {
        static_cast<ICollisionMesh*>(m_pGround)->SetActive(1);  // 0x001a6b70 (1 here too, as in OnActivate)
        if ((m_bitArray & 0x10u) != 0) SetGroundsHurt(this, false);
    }
    if (m_pParticle != nullptr) StopParticles(m_pParticle);
    Sound_Stop(Sounds(this)->GetSound(1), 0);  // 0x001111b0
    Sound_Stop(Sounds(this)->GetSound(2), 0);
}

// 0x003fb040 CKHkActivator_Load: the actor base's, then for the level type the message index (swapped), the eight
// references (+0x34, +0x38, +0x3c, +0x40, +0x48, +0x50, +0x4c, +0x44: the file's order) and the two trigger starters.
int32_t CKHkActivator::Load(IKFile* file, int32_t type) {
    CKHkActorBase::Load(file, type);  // 0x003f6e98
    if (type != K_LEVEL_PLATEFORMS) return 1;
    ReadS32LE(file, &m_i32MessageIndex);
    IKFile_ReadRef(file, &m_pAnimatedDictionary);
    IKFile_ReadRef(file, &m_pSoundDictionary);
    IKFile_ReadRef(file, &m_pDodgeBS);
    IKFile_ReadRef(file, &m_pHitBS);
    IKFile_ReadRef(file, &m_pGround);
    IKFile_ReadRef(file, &m_pAdvanceGround);
    IKFile_ReadRef(file, &m_pParticle);
    IKFile_ReadRef(file, &m_pMecaCpnt);
    m_tsActivateStarter.Load(file, 0);    // 0x002361c0
    m_tsDeactivateStarter.Load(file, 0);  // 0x002361c0
    return 1;
}
