// CKHkS08PowerBucket.cpp - reconstructed original translation unit 0x4d3438-0x4d5418 (GAME_TOC1, main_toc1), 34 functions, 34 live.
// Primary class: CKHkS08PowerBucket  key 0x30c2  category Hook  size 0x20c  vtable 0xb29c50
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x4d3438  CKHkS08PowerBucket_vf124  (CKHkS08PowerBucket.h)
//   [x] 0x4d3490  CKHkS08PowerBucket_vf120  (CKHkS08PowerBucket.h)
//   [x] 0x4d34e8  CKHkS08PowerBucket_vf168
//   [x] 0x4d3510  CKHkS08PowerBucket_vfEC  (CKHkS08PowerBucket.h)
//   [x] 0x4d3588  CKHkS08PowerBucket_Resume  (the Weight's: empty, inherited)
//   [x] 0x4d35b0  CKHkS08PowerBucket_Restart
//   [x] 0x4d3648  CKHkS08PowerBucket_Pause  (the Weight's: empty, inherited)
//   [x] 0x4d3670  CKHkS08PowerBucket_PostLoad
//   [ ] 0x4d36c0  CKHkS08PowerBucket_Save
//   [x] 0x4d36e8  CKHkS08PowerBucket_RecursiveRegistration  (the Weight's: inherited)
//   [x] 0x4d3710  CKHkS08PowerBucket_Destroy  (the Weight's: inherited)
//   [x] 0x4d3738  CKHkS08PowerBucket_DeletingDestructor  (C++ deleting destructor)
//   [x] 0x4d3780  CKHkS08PowerBucket_Construct
//   [x] 0x4d37b8  CKHkS08PowerBucket_Construct_2  (the constructor, CKHkS08PowerBucket.h)
//   [x] 0x4d37f0  CKHkS08PowerBucket_DeleteArray
//   [ ] 0x4d3890  RegisterCKHkS08PowerBucketClass
//   [ ] 0x4d3918  _GLOBAL__D_4d3918
//   [ ] 0x4d3928  _GLOBAL__I_4d3928
//   [x] 0x4d3938  CKHkS08PowerBucket_vf174
//   [x] 0x4d39c8  CKHkS08PowerBucket_vf170
//   [x] 0x4d3a58  CKHkS08PowerBucket_vf16C
//   [x] 0x4d3ae8  CKHkS08PowerBucket_vfF8
//   [x] 0x4d3cf8  CKHkS08PowerBucket_Stop  (CKHkS08PowerBucket.h)
//   [x] 0x4d3d48  CKHkS08PowerBucket_vf194  (SetCarriedShown, CKHkS08PowerBucket.h)
//   [x] 0x4d3da0  CKHkS08PowerBucket_Destructor  (C++ destructor chain)
//   [x] 0x4d3dd0  CKHkS08PowerBucket_DestructBody  (C++ destructor chain)
//   [x] 0x4d3e00  CKHkS08PowerBucket_Start
//   [x] 0x4d3f10  CKHkS08PowerBucket_CreateArray
//   [x] 0x4d3fc0  CKHkS08PowerBucket_Create
//   [x] 0x4d4018  CKHkS08PowerBucket_Load
//   [x] 0x4d4358  CKHkS08PowerBucket_TriggerFx_maybe
//   [x] 0x4d4628  CKHkS08PowerBucket_Update
//   [x] 0x4d48c0  CKHkS08PowerBucket_OnImpact_maybe
//   [x] 0x4d4fc0  CKHkS08PowerBucket_SpawnAltImpactFx_maybe
//
//   [ ] 0x9c5e20  CKHkS08PowerBucket_IsKindOfClass  [inline]
//   [ ] 0x9c5e98  CKHkS08PowerBucket_GetClassType  [inline]
//   [ ] 0x9c5ea0  CKHkS08PowerBucket_GetClassID  [inline]
//   [ ] 0x9c5ea8  CKHkS08PowerBucket_vf104  [inline]
#include "Spyro2008/hooks/CKHkS08PowerBucket.h"

#include "k2000/dictionaries/CKSoundDictionaryID.h"
#include "k2000/io/IKFile.h"
#include "Renderware/rwcore/RwCamera.h"
#include "Spyro2008/logic/CKS08GameManager.h"
#include "crt/ppc_ops.h"
#include "k2000/groups/CKGrpTransportableObject.h"
#include "k2000/logic/CKLevel.h"
#include "k2000/logic/CKParticlesEffectFxData.h"
#include "k2000/logic/CKSector.h"
#include "k2000/logic/CSGHotSpot.h"
#include "k2000/logic/fx/CKExplosionNodeFx.h"
#include "k2000/logic/KBase910C.h"
#include "k2000/logic/sound/CKSound.h"
#include "k2000/misc/Engine.h"
#include "k2000/scenegraph/CSGBranch.h"
#include "k2000/scenegraph/CSGSectorRoot.h"
#include "k2000/services/CKSrvFx.h"
#include "k2000/services/CollisionDatas.h"
#include "k2000/services/ICollisionMesh.h"

#include <cmath>

// 0x004d4018 CKHkS08PowerBucket_Load
int32_t CKHkS08PowerBucket::Load(IKFile* file, int32_t type) {
    CKHkS08TransportableWeight::Load(file, type);
    if (type != K_LEVEL_PLATEFORMS) return 1;
    ReadF32LE(file, &m_unk1f4);
    IKFile_ReadRef(file, &m_unk1d4);
    IKFile_ReadRef(file, &m_unk1d8);
    ReadF32LE(file, &m_unk1f8);
    IKFile_ReadRef(file, &m_unk1d0);
    IKFile_ReadRef(file, &m_unk1e0);
    ReadF32LE(file, &m_unk1dc);
    IKFile_ReadRef(file, &m_unk1cc);
    ReadF32LE(file, &m_unk1ec);
    return 1;
}

// ---- C2.8 port-all P16 ----

// 0x004d35b0 CKHkS08PowerBucket_Restart
void CKHkS08PowerBucket::Restart() {
    CKHkS08TransportableKey::Restart();  // 0x004adb08
    CSGLeaf* node = static_cast<CSGLeaf*>(m_unk1d8);
    node->m_sgProperties = (node->m_sgProperties & 0xfffffffbu) | 4u;
    m_unk1e8 = 0;        // +0x1e8
    SetCarriedShown(0);  // vt+0x194
    m_fPrevSwingAtSpeed = 0.0f;     // +0x208 (word stores of 0)
    m_fPrevSwingRight = 0.0f;       // +0x1fc
    m_fPrevSwingAt = 0.0f;          // +0x200
    m_fPrevSwingRightSpeed = 0.0f;  // +0x204
}

// 0x004d3a58 CKHkS08PowerBucket_vf16C / 0x004d39c8 _vf170 / 0x004d3938 _vf174
CKSound* CKHkS08PowerBucket::Vf16C() {
    return static_cast<CKSoundDictionaryID*>(m_unk1d0)->GetSound(Vf190() != 0 ? 3 : 0);  // 0x00112bc0
}
CKSound* CKHkS08PowerBucket::Vf170() {
    return static_cast<CKSoundDictionaryID*>(m_unk1d0)->GetSound(Vf190() != 0 ? 4 : 1);
}
CKSound* CKHkS08PowerBucket::Vf174() {
    return static_cast<CKSoundDictionaryID*>(m_unk1d0)->GetSound(Vf190() != 0 ? 5 : 2);
}

// ---- C2.8 port-rest R10 ----

namespace {
// 0x00c50d40 (a static initialiser; the Weight's kWeightAxisY): the explosions' direction.
const CVector3 kBucketAxisY = {0.0f, 1.0f, 0.0f};
CSGLeaf* BucketNode(CKHkS08PowerBucket* bucket) { return static_cast<CSGLeaf*>(bucket->m_pKGLObject); }
}  // namespace

// 0x004d3670 CKHkS08PowerBucket_PostLoad
int32_t CKHkS08PowerBucket::PostLoad(int32_t type) {
    CKHkS08TransportableWeight::PostLoad(type);  // 0x004b48c0
    if (m_unk1cc != nullptr) {
        CKParticlesEffectFxData* data = static_cast<CKParticlesEffectFxData*>(m_unk1e0);
        data->m_pAttachHotSpot = m_unk1cc;
        data->m_pAttachOwner = nullptr;
    }
    return 1;
}

// 0x004d3e00 CKHkS08PowerBucket_Start
void CKHkS08PowerBucket::Start() {
    CKHkS08TransportableWeight::Start();  // 0x004b4880
    CSGLeaf* node = static_cast<CSGLeaf*>(m_unk1d8);
    m_pEffect = nullptr;
    if (node->m_pParent != nullptr) {
        node->m_pParent->RemoveChild(node);  // vt+0x78
        node = static_cast<CSGLeaf*>(m_unk1d8);
    }
    // engine +0x8c (the game manager) +0x18 (its level): sector 0's root.
    CKLevel* level = g_pEngine->m_gameManager->m_level;
    static_cast<CKSector*>(level->m_vpSectors.m_pBlock[0])->m_pSectorRoot->AddChild(node);  // vt+0x70
    CSGLeaf* shown = static_cast<CSGLeaf*>(m_unk1d8);
    shown->m_sgProperties = (shown->m_sgProperties & 0xfffffffbu) | 4u;
    Restart();  // vt+0x54
}

// 0x004d3ae8 CKHkS08PowerBucket_vfF8: the Key's let-go without its carrier and ground tests (`carrier` is not read).
uint8_t CKHkS08PowerBucket::VfF8(IKSerializable* /*carrier*/, const CVector3* velocity) {
    if (static_cast<KBase910C*>(m_pCarrier)->Vf5C(this) == 0) return 0;  // vt+0x5c
    m_vVelocity.x = velocity->x;
    m_vVelocity.z = velocity->z;
    m_vVelocity.y = velocity->y;
    static_cast<KBase910C*>(m_pCarrier)->StopCarrying(this);  // vt+0x54
    m_pCarrier = nullptr;
    SwitchState(2, nullptr, 2);
    return 1;
}

// 0x004d4358 CKHkS08PowerBucket_TriggerFx_maybe (the effect lookup is CKSrvFx::AcquireFx inlined).
void CKHkS08PowerBucket::TriggerFx() {
    CKParticlesEffectFxData* data = static_cast<CKParticlesEffectFxData*>(m_unk1e0);
    data->m_pAttachOwner = nullptr;
    data->m_pAttachHotSpot = m_unk1cc;
    IKFx* fx = static_cast<CKSrvFx*>(g_pEngine->m_srvFx)->AcquireFx(data, this);
    m_pEffect = fx;
    if (fx == nullptr) return;
    fx->ReleaseReservation(this);  // vt+0x54
    // BUG(original): r31 still holds the effect's reserved bit (flag bit 1) from the lookup, 0 for the effect picked.
    m_pEffect = nullptr;
    CKSound* sound = static_cast<CKSoundDictionaryID*>(m_unk1d0)->GetSound(6);  // 0x00112bc0
    if (sound == nullptr) return;
    const RwV3d& p = BucketNode(this)->m_pRwFrame->ltm.pos;  // node +0x4 -> +0x80
    const CVector3 position = {p.x, p.y, p.z};
    sound->SetPosition(&position);  // 0x00110fa0
    sound->Play(0.0f);              // 0x00111230; TOC +0x6a4c
}

// 0x004d4628 CKHkS08PowerBucket_Update
void CKHkS08PowerBucket::Update(IKTime* clock) {
    CKHkS08TransportableWeight::Update(clock);  // 0x004b5df0
    bool trigger = false;
    if (m_unk114 != 0 || Vf190() == 0) {  // vt+0x190
        if (m_pEffect != nullptr) {
            m_pEffect->StopAndRelease(this);  // vt+0x58
            m_pEffect = nullptr;
        }
    } else {
        // TOC +0x6a4c 0.0, +0x50 -0.5, +0x54 0.5. The right axis: past +-0.5 with its speed changing sign (a NaN previous
        // speed counts as positive); then the at axis the same way (a NaN previous speed counts as negative).
        const float zero = 0.0f;
        const float right = m_fSwingRight;
        const bool rightOut = right < zero ? !(right >= -0.5f) : !(right <= 0.5f);
        if (rightOut) {
            const float prev = m_fPrevSwingRightSpeed;
            if (prev <= zero) {
                if (prev < zero && m_fSwingRightSpeed > zero) trigger = true;
            } else if (!(m_fSwingRightSpeed >= zero)) {
                trigger = true;
            }
        }
        if (!trigger) {
            const float at = m_fSwingAt;
            const bool atOut = at < zero ? !(at >= -0.5f) : !(at <= 0.5f);
            if (atOut) {
                const float prev = m_fPrevSwingAtSpeed;
                if (prev > zero) {
                    if (m_fSwingAtSpeed < zero) trigger = true;
                } else if (!(prev >= zero)) {
                    if (m_fSwingAtSpeed > zero) trigger = true;
                }
            }
        }
        if (trigger) TriggerFx();  // 0x004d4358
    }
    CVector3 position;
    if (m_unk1cc != nullptr) {
        static_cast<CSGHotSpot*>(m_unk1cc)->GetWorldPosition(&position);  // 0x000ce790
    } else {
        BucketNode(this)->ForceWorldMatrixUpdate();  // vt+0x50
        const RwV3d& p = BucketNode(this)->m_pRwFrame->ltm.pos;
        position.x = p.x;
        position.y = p.y + m_unk1dc;
        position.z = p.z;
    }
    RwFrame* frame = static_cast<CSGLeaf*>(m_unk1d8)->m_pRwFrame;
    frame->modelling.pos.z = position.z;
    frame->modelling.pos.x = position.x;
    frame->modelling.pos.y = position.y;
    frame->modelling.flags &= 0xfffdffffu;
    RwFrame_MarkDirty(static_cast<CSGLeaf*>(m_unk1d8)->m_pRwFrame);  // 0x00010698
    m_fPrevSwingRight = m_fSwingRight;
    m_fPrevSwingAtSpeed = m_fSwingAtSpeed;
    m_fPrevSwingAt = m_fSwingAt;
    m_fPrevSwingRightSpeed = m_fSwingRightSpeed;
}

// 0x004d48c0 CKHkS08PowerBucket_OnImpact_maybe (the explosion lookup is CKSrvFx::AcquireFx inlined).
void CKHkS08PowerBucket::Vf154(const CGroundContactDatasInOut* contact) {
    Vf168();  // vt+0x168
    const ICollisionMesh* ground = static_cast<const ICollisionMesh*>(contact->m_pGround);
    if (ground == nullptr) return;
    if ((ground->m_ui16PropertiesFlags & 0x200u) != 0 && ((ground->m_ba16EngineFlags >> 1) & 1u) == 0) return;
    const CVector3& n = contact->m_Normal;
    const float dot = ppc::fmadds(n.z, m_vVelocity.z, ppc::fmadds(n.x, m_vVelocity.x, n.y * m_vVelocity.y));
    const float py = n.y * dot;
    const float px = n.x * dot;
    const float pz = n.z * dot;
    const float speed = std::sqrt(ppc::fmadds(pz, pz, ppc::fmadds(px, px, py * py)));  // 0x00010690
    ground = static_cast<const ICollisionMesh*>(contact->m_pGround);
    if (m_unk1f8 <= speed && ((ground->m_ba16EngineFlags >> 1) & 1u) == 0) {
        IKFxData* data = static_cast<IKFxData*>(Vf190() != 0 ? m_unk1d4 : m_unk1b0);  // vt+0x190
        IKFx* fx = static_cast<CKSrvFx*>(g_pEngine->m_srvFx)->AcquireFx(data, this);
        if (fx != nullptr) {
            CKExplosionNodeFx* explosion = static_cast<CKExplosionNodeFx*>(fx);
            CMatrix34 matrix;
            Vf118()->GetWorldMatrix(&matrix);  // vt+0x118, 0x000ce970
            explosion->SetPosition(&matrix.m_at, &matrix.m_pos, this);  // 0x001b6438
            if (Vf190() != 0) {
                explosion->SetDamageOwner(this, this);  // 0x001b6340
                explosion->SetDamageCategory(1, this);  // 0x001b6318
                explosion->SetDamageFlags(8, this);     // 0x001b62f0
                explosion->SetDamage(nullptr, this);    // 0x001b62c8
            }
            explosion->Trigger(this, nullptr);    // 0x001b82a8 (r5 0, r6 0)
            explosion->ReleaseReservation(this);  // vt+0x54
            SetCarriedShown(0);                   // vt+0x194
        }
        Vf108();  // vt+0x108
        static_cast<CKGrpTransportableObject*>(m_unk20)->ReleaseObject(this);  // 0x004a7ce0
        return;
    }
    if (((ground->m_ba16EngineFlags >> 1) & 1u) == 0) return;
    static_cast<CKS08GameManager*>(g_pEngine->m_gameManager)
        ->SpawnSurfaceFx(0.0f, this, 3, 2, &contact->m_ProjectionOnGround.x);  // 0x004f9628; TOC +0x6a4c
    CKSound* sound = static_cast<CKSoundDictionaryID*>(m_unk130)->GetSound(0);  // 0x00112bc0
    if (sound != nullptr) {
        sound->SetPosition(&contact->m_ProjectionOnGround);  // 0x00110fa0
        sound->Play(0.0f);                                   // 0x00111230
    }
    SetCarriedShown(0);  // vt+0x194
    Vf108();             // vt+0x108
    static_cast<CKGrpTransportableObject*>(m_unk20)->ReleaseObject(this);  // 0x004a7ce0
}

// 0x004d4fc0 CKHkS08PowerBucket_SpawnAltImpactFx_maybe
void CKHkS08PowerBucket::Vf18C() {
    IKFxData* data = static_cast<IKFxData*>(Vf190() != 0 ? m_unk1d4 : m_unk1b0);  // vt+0x190
    IKFx* fx = static_cast<CKSrvFx*>(g_pEngine->m_srvFx)->AcquireFx(data, this);
    if (fx == nullptr) return;
    CKExplosionNodeFx* explosion = static_cast<CKExplosionNodeFx*>(fx);
    CVector3 at;
    Vf118()->GetWorldPosition(&at);                    // vt+0x118, 0x000ce790
    explosion->SetPosition(&kBucketAxisY, &at, this);  // 0x001b6438; TOC +0x6a58
    explosion->Trigger(this, nullptr);                 // 0x001b82a8
    explosion->ReleaseReservation(this);               // vt+0x54
}
