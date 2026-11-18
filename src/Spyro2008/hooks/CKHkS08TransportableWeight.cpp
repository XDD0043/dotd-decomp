// CKHkS08TransportableWeight.cpp - reconstructed original translation unit 0x4b4750-0x4b7728 (GAME_TOC1, main_toc1), 43 functions, 39 live.
// Primary class: CKHkS08TransportableWeight  key 0x3142  category Hook  size 0x1cc  vtable 0xb28e28
// Other owners: IKSerializable (6), CKGolemAttackCommon (2), CKHkS08PowerBucket (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x4b4750  CKHkS08TransportableWeight_Delete
//   [ ] 0x4b47a0  CKHkS08TransportableWeight_ReleaseFxAt138_maybe  [dead]
//   [x] 0x4b4808  CKHkS08TransportableWeight_Resume  (empty / no effect: inherited)
//   [x] 0x4b4830  CKHkS08TransportableWeight_Pause  (empty / no effect: inherited)
//   [x] 0x4b4858  CKHkS08TransportableWeight_Stop  (header)
//   [x] 0x4b4880  CKHkS08TransportableWeight_Start
//   [x] 0x4b48c0  CKHkS08TransportableWeight_PostLoad
//   [ ] 0x4b4918  CKHkS08TransportableWeight_Save
//   [x] 0x4b4940  CKHkS08TransportableWeight_RecursiveRegistration  (the Key's 0x4ace60 -> the base's 0x4ac1f0 -> CKHkActorBase's 0x3f6ee8 -> IKHook's: inherited)
//   [x] 0x4b4968  CKHkS08TransportableWeight_Destroy  (header)
//   [x] 0x4b4990  CKHkS08TransportableWeight_Construct
//   [x] 0x4b49c8  CKHkS08TransportableWeight_DeleteArray
//   [x] 0x4b4a68  CKHkS08TransportableWeight_BaseDestructor  (header)
//   [x] 0x4b4a98  CKHkS08PowerBucket_ConstructBase_maybe
//   [ ] 0x4b4ad0  RegisterCKHkS08TransportableWeightClass
//   [ ] 0x4b4b58  _GLOBAL__D_4b4b58
//   [ ] 0x4b4b68  _GLOBAL__I_4b4b68
//   [x] 0x4b4b78  CKHkS08TransportableWeight_DeletingDestructor  (header)
//   [x] 0x4b4bc0  CKHkS08TransportableWeight_Destructor  (header)
//   [x] 0x4b4bf0  CKHkS08TransportableWeight_vfEC  (CKHkS08TransportableWeight.h)
//   [x] 0x4b4c30  CKHkS08TransportableWeight_vfF0
//   [x] 0x4b4d18  CKHkS08TransportableWeight_vfF8
//   [x] 0x4b4f38  CKHkS08TransportableWeight_OnImpact_maybe
//   [x] 0x4b5120  CKHkS08TransportableWeight_vf160
//   [x] 0x4b5758  CKHkS08TransportableWeight_CreateArray
//   [x] 0x4b5808  CKHkS08TransportableWeight_Create
//   [x] 0x4b5860  CKHkS08TransportableWeight_vf188
//   [x] 0x4b5d78  CKHkS08TransportableWeight_vf124
//   [x] 0x4b5df0  CKHkS08TransportableWeight_Update
//   [x] 0x4b6500  CKHkS08TransportableWeight_Load
//   [x] 0x4b6ae8  CKHkS08TransportableWeight_SpawnImpactFx_maybe
//   [ ] 0x4b6db8  CKHkS08TransportableWeight_vf120_2  [dead]
//   [x] 0x4b7038  CKHkS08TransportableWeight_SpawnAltImpactFx_maybe
//   [x] 0x4b7308  CKHkS08TransportableWeight_vf120
//   [x] 0x4b7588  CKGolemAttackCommon_Delete  (DOTD_DECLARE_FACTORIES, k2000/logic/CKGolemAttackCommon.h)
//   [x] 0x4b75d8  KBaseC_vfA0_2  (CKGolemAttackCommon)
//   [x] 0x4b7628  KBaseC_vf70_3  (CKGolemAttackCommon)
//   [x] 0x4b7630  KBaseC_vf74_4  (CKGolemAttackCommon)
//   [x] 0x4b7638  KBaseC_vf78_3  (CKGolemAttackCommon)
//   [ ] 0x4b7640  CKGolemAttackCommon_InitAttackVolume_maybe  [dead]
//   [ ] 0x4b7710  KStub_Nop_4b7710  [dead]
//   [x] 0x4b7718  KBaseC_vf94_3  (CKGolemAttackCommon)
//   [x] 0x4b7720  KBaseC_vf98_2  (CKGolemAttackCommon)
//
//   [x] 0x9c54d0  CKHkS08TransportableWeight_IsKindOfClass  [inline]
//   [x] 0x9c5538  CKHkS08TransportableWeight_GetClassType  [inline]
//   [x] 0x9c5540  CKHkS08TransportableWeight_GetClassID  [inline]
//   [x] 0x9c5548  CKHkS08TransportableWeight_vf118  [inline]  (header)
//   [x] 0x9c5550  CKHkS08TransportableWeight_vf104  [inline]  (header)
//   [x] 0x9c5558  CKHkS08TransportableWeight_vf17C  [inline]  (header)
//   [x] 0x9c5560  CKHkS08TransportableWeight_vf180  [inline]
//   [x] 0x9c5568  CKHkS08TransportableWeight_vf184  [inline]  (header)
#include "Spyro2008/hooks/CKHkS08TransportableWeight.h"

#include "k2000/io/IKFile.h"
#include "k2000/fx/IKFx.h"
#include "k2000/cameras/CKSrvCamera.h"
#include "k2000/cameras/IKCamera.h"
#include "k2000/core/Stub.h"
#include "k2000/logic/CKParticlesEffectFxData.h"
#include "k2000/misc/Engine.h"
#include "k2000/scenegraph/CNode.h"
#include "k2000/scenegraph/CSGBranch.h"
#include "k2000/services/CKSrvFx.h"
#include "Renderware/rwcore/RwCamera.h"
#include "Spyro2008/groups/C22SpyroShims.h"
#include "Spyro2008/logic/CKS08CarrierHero.h"
#include "crt/ppc_ops.h"
#include "crt/xatanf.h"
#include "k2000/dictionaries/CKSoundDictionaryID.h"
#include "k2000/groups/CKGrpTransportableObject.h"
#include "k2000/logic/CSGHotSpot.h"
#include "k2000/logic/KBase910C.h"
#include "k2000/logic/fx/CKExplosionNodeFx.h"
#include "k2000/logic/sound/CKSound.h"
#include "k2000/misc/Mat4.h"
#include "k2000/render/CRenderer.h"
#include "k2000/scenegraph/CSGLeaf.h"
#include "k2000/services/CKSrvCollision.h"
#include "k2000/services/CollisionDatas.h"
#include "k2000/services/ICollisionMesh.h"
#include "k2000/system/IKTime.h"
#include "Spyro2008/hooks/CKHkS08Hero.h"
#include "Spyro2008/logic/CKS08GameManager.h"

#include <cfloat>

namespace {
// 0x00c50d64 / 0x00c50d40 (static initialisers): the null vector and the shared Y axis.
const CVector3 kWeightZero = {0.0f, 0.0f, 0.0f};
const CVector3 kWeightAxisY = {0.0f, 1.0f, 0.0f};
// The float at 0x00c4ace0 (TOC +0x64c8 -> 0x00c4acb8, +0x28): FLT_MAX, the "unset" value of +0x190 / +0x1b4.
constexpr float kUnset = FLT_MAX;

CSGLeaf* WeightNode(CKHkS08TransportableWeight* weight) { return static_cast<CSGLeaf*>(weight->m_pKGLObject); }

// 0x004b6ae8 / 0x004b7038 (identical but for the data): an explosion of `data` acquired for the weight (the inlined pooled
// lookup), set at its grip's world position facing the Y axis (0x00c50d40), set off and let go (vt+0x54).
void SpawnExplosionAtGrip(CKHkS08TransportableWeight* weight, IKSerializable* data) {
    IKFx* fx = static_cast<CKSrvFx*>(g_pEngine->m_srvFx)->AcquireFx(static_cast<IKFxData*>(data), weight);
    if (fx == nullptr) return;
    CKExplosionNodeFx* explosion = static_cast<CKExplosionNodeFx*>(fx);
    CVector3 at;
    weight->Vf118()->GetWorldPosition(&at);  // vt+0x118, 0x000ce790
    explosion->SetPosition(&kWeightAxisY, &at, weight);  // 0x001b6438; TOC +0x64fc
    explosion->Trigger(weight, 0);                       // 0x001b82a8 (r5 0, r6 0)
    explosion->ReleaseReservation(weight);               // vt+0x54
}
}  // namespace

// 0x004b6500 CKHkS08TransportableWeight_Load
int32_t CKHkS08TransportableWeight::Load(IKFile* file, int32_t type) {
    CKHkS08TransportableKey::Load(file, type);
    if (type == K_LEVEL_PLATEFORMS) {
        IKFile_ReadRef(file, &m_unk140);
        IKFile_ReadRef(file, &m_unk144);
        ReadF32LE(file, &m_unk148);
        ReadF32LE(file, &m_unk170);
        ReadF32LE(file, &m_unk168);
        ReadF32LE(file, &m_unk14c);
        ReadF32LE(file, &m_unk16c);
        ReadF32LE(file, &m_unk174);
        ReadF32LE(file, &m_unk188);
        ReadF32LE(file, &m_unk18c);
        ReadF32LE(file, &m_unk178);
        ReadF32LE(file, &m_unk19c);
        IKFile_ReadRef(file, &m_unk1b0);
        IKFile_ReadRef(file, &m_unk134);
        IKFile_ReadRef(file, &m_unk13c);
        IKFile_ReadRef(file, &m_unk130);
        return 1;
    }
    return 1;
}

// 0x004b48c0 CKHkS08TransportableWeight_PostLoad: the Key's, then for the level type +0x138 = 0.
int32_t CKHkS08TransportableWeight::PostLoad(int32_t type) {
    CKHkS08TransportableKey::PostLoad(type);
    if (type == K_LEVEL_PLATEFORMS) m_unk138 = nullptr;  // stw of the type (0)
    return 1;
}

// 0x004b4880 CKHkS08TransportableWeight_Start
void CKHkS08TransportableWeight::Start() {
    CKHkS08TransportableKey::Start();  // 0x4af358
    m_unk138 = nullptr;
    m_pDynamicGround = nullptr;  // +0xc0
}

void CKHkS08TransportableWeight::AcquireWeightFx() {
    CKParticlesEffectFxData* data = static_cast<CKParticlesEffectFxData*>(m_unk134);
    data->m_pAttachHotSpot = m_unk144;
    data->m_pAttachOwner = nullptr;
    m_unk138 = static_cast<CKSrvFx*>(g_pEngine->m_srvFx)->AcquireFx(data, this);
}

// 0x004b7308 CKHkS08TransportableWeight_vf120: with a hot spot +0x144 and no effect yet, the effect acquired.
void CKHkS08TransportableWeight::Vf120() {
    if (m_unk144 == nullptr || m_unk138 != nullptr) return;
    AcquireWeightFx();
}

// 0x004b5df0 CKHkS08TransportableWeight_Update. The Key's; with the node's distance limit on (CNode_GetFlag10Bit7_WhenBit8Set
// 0xcbab8): the current camera farther than sqrt(+0x20) squared (fmadds) releases the effect, nearer (re)acquires it
// (with a hot spot +0x144). Then, carried (state 0) by a carrier hero (class id 0x247) whose hot spot holds it
// (0x4b0960) under the carrier's branch, the carried pose.
void CKHkS08TransportableWeight::Update(IKTime* clock) {
    CKHkS08TransportableKey::Update(clock);  // 0x004aff00
    CNode* node = static_cast<CNode*>(m_pKGLObject);
    const uint32_t flags = node->m_sgProperties;
    if ((flags & 0x100u) != 0 && ((flags >> 7) & 1u) != 0) {  // 0x000cbab8
        const IKCamera* camera = static_cast<CKSrvCamera*>(g_pEngine->m_srvCamera)->m_pCurrentCamera;
        const float limit = static_cast<float>(c22spyro::MathSqrtf(node->m_fDistanceLimitSquared));
        const float limit2 = limit * limit;
        const RwV3d& p = FrameLtm(node->m_pRwFrame)->pos;
        const float dy = camera->m_WorldPosition.y - p.y;
        const float dx = camera->m_WorldPosition.x - p.x;
        const float dz = camera->m_WorldPosition.z - p.z;
        if (ppc::fmadds(dz, dz, ppc::fmadds(dx, dx, dy * dy)) > limit2) {
            if (m_unk138 != nullptr) {
                static_cast<IKFx*>(m_unk138)->StopAndRelease(this);  // vt+0x58
                m_unk138 = nullptr;
            }
        } else if (m_unk144 != nullptr && m_unk138 == nullptr) {
            AcquireWeightFx();
        }
    }
    if (m_unk114 != 0 || m_pCarrier == nullptr || m_pCarrier->GetClassID() != 0x247) return;
    CKS08CarrierHero* carrier = static_cast<CKS08CarrierHero*>(m_pCarrier);
    if (carrier->IsCarriedObjectAttachedToCarrierHotSpot() == 0) return;  // 0x004b0960
    if (static_cast<CSGLeaf*>(m_pKGLObject)->m_pParent != static_cast<CSGBranch*>(carrier->m_pBranch)) return;
    if (m_vAimPoint.x == kUnset && m_vAimPoint.y == kUnset && m_vAimPoint.z == kUnset) {
        // No aim point yet: +0x19c from the node's LTM position towards the hot spot +0x140 (unless they coincide).
        static_cast<CSGLeaf*>(m_pKGLObject)->ForceWorldMatrixUpdate();  // vt+0x50
        CVector3 spot;
        static_cast<CSGHotSpot*>(m_unk140)->GetWorldPosition(&spot);  // 0x000ce790
        const RwV3d& p = FrameLtm(static_cast<CSGLeaf*>(m_pKGLObject)->m_pRwFrame)->pos;
        const float dx = spot.x - p.x;
        const float dz = spot.z - p.z;
        const float dy = spot.y - p.y;
        if (kWeightZero.x == dx && kWeightZero.y == dy && kWeightZero.z == dz) return;  // TOC +0x64c4: 0x00c50d64
        const float length = static_cast<float>(c22spyro::MathSqrtf(ppc::fmadds(dz, dz, ppc::fmadds(dx, dx, dy * dy))));
        const float s = m_unk19c / length;
        const RwV3d& q = FrameLtm(static_cast<CSGLeaf*>(m_pKGLObject)->m_pRwFrame)->pos;
        m_vAimPoint.z = ppc::fmadds(dz, s, q.z);
        m_vAimPoint.x = ppc::fmadds(dx, s, q.x);
        m_vAimPoint.y = ppc::fmadds(dy, s, q.y);
        return;
    }
    // The carried pose: the branch's and the node's LTMs refreshed (vt+0x50), the swing stepped (vt+0x188), then a frame
    // with up = the swing's up and forward = the hot spot's at axis normalised (Mat4_BuildFromUpAndForward over the
    // identity), at the hot spot's world position, taken into the hot spot's space (post-concatenated with its inverse).
    static_cast<CSGBranch*>(carrier->m_pBranch)->ForceWorldMatrixUpdate();  // vt+0x50
    static_cast<CSGLeaf*>(m_pKGLObject)->ForceWorldMatrixUpdate();
    CMatrix34 spot;
    static_cast<CSGHotSpot*>(carrier->Vf7C())->GetWorldMatrix(&spot);  // vt+0x7c, 0x000ce970
    CMatrix34 inverse;
    Mat4_Invert(&inverse, &spot);  // 0x0023f878
    Vf188(clock->m_afDeltaTime[0]);  // vt+0x188
    CMatrix34 m;
    m.m_right = {1.0f, 0.0f, 0.0f};
    m.m_ui32Flags = 0x20003u;
    m.m_up = {0.0f, 1.0f, 0.0f};
    m.m_at = {0.0f, 0.0f, 1.0f};
    m.m_pos = {0.0f, 0.0f, 0.0f};
    m.m_ui32pad1 = 0;  // not written by the original (stack words); unread
    m.m_ui32pad2 = 0;
    m.m_ui32pad3 = 0;
    CVector3 forward = spot.m_at;
    const float length = static_cast<float>(
        c22spyro::MathSqrtf(ppc::fmadds(forward.z, forward.z, ppc::fmadds(forward.x, forward.x, forward.y * forward.y))));
    if (length != 0.0f) {
        const float s = 1.0f / length;
        forward.z = forward.z * s;
        forward.x = forward.x * s;
        forward.y = forward.y * s;
    }
    Mat4_BuildFromUpAndForward(&m, &m_vSwingUp, &forward);  // 0x0023ff80
    m.m_pos = spot.m_pos;
    m.m_ui32Flags &= 0xfffdffffu;
    Mat4_TransformPostConcat(&m, &inverse);  // 0x0023f760
    static_cast<CSGLeaf*>(m_pKGLObject)->SetLocalMatrix(reinterpret_cast<const RwMatrix*>(&m));  // 0x000d0be8
}

// 0x004b5d78 CKHkS08TransportableWeight_vf124: the Key's, then the effect +0x138 released (vt+0x58).
void CKHkS08TransportableWeight::Vf124() {
    CKHkS08TransportableKey::Vf124();  // 0x004ac580
    if (m_unk138 != nullptr) {
        static_cast<IKFx*>(m_unk138)->StopAndRelease(this);
        m_unk138 = nullptr;
    }
}

// 0x004b4c30 CKHkS08TransportableWeight_vfF0: the Key's pickup; picked up, the swing state is reset: +0x150 / +0x15c
// zero, the aim point and the last grip position unset (FLT_MAX), the last grip velocity and the swing zero.
uint8_t CKHkS08TransportableWeight::VfF0(IKSerializable* carrier) {
    if (CKHkS08TransportableKey::VfF0(carrier) == 0) return 0;  // 0x004afd08
    m_vUnk150 = kWeightZero;  // TOC +0x64c4: 0x00c50d64
    m_vUnk15c = kWeightZero;
    m_vAimPoint = {kUnset, kUnset, kUnset};
    m_vPrevGripVel = {0.0f, 0.0f, 0.0f};
    m_vPrevGripPos = {kUnset, kUnset, kUnset};
    m_fSwingAtSpeed = 0.0f;
    m_fSwingRight = 0.0f;
    m_fSwingAt = 0.0f;
    m_fSwingRightSpeed = 0.0f;
    return 1;
}

// 0x004b4d18 CKHkS08TransportableWeight_vfF8: let go with `velocity` unless it is not on a ground (status 3) or the
// carrier refuses (vt+0x5c): the velocity kept (+0x8c), the carrier told (vt+0x54), no carrier, the machine switched to
// state 2 (falling; no clock). (`carrier` is not read: the carrier held, +0x48, is asked.)
uint8_t CKHkS08TransportableWeight::VfF8(IKSerializable* /*carrier*/, const CVector3* velocity) {
    if (m_GContactInOut.m_eContactStatus == 3) return 0;
    if (static_cast<KBase910C*>(m_pCarrier)->Vf5C(this) == 0) return 0;  // vt+0x5c
    m_vVelocity.x = velocity->x;
    m_vVelocity.z = velocity->z;
    m_vVelocity.y = velocity->y;
    static_cast<KBase910C*>(m_pCarrier)->StopCarrying(this);  // vt+0x54
    m_pCarrier = nullptr;
    SwitchState(2, nullptr, 2);
    return 1;
}

// 0x004b4f38 CKHkS08TransportableWeight_OnImpact_maybe (vt+0x154): landed on a ground that is not a slide (0x200): the
// impact feedback (vt+0x168). On a slide: with engine flag bit 1 the surface effect 3 / 2 (volume 0) and the sound 0 of
// +0x130 at the contact point, then vt+0x108 and back into the group's pool; without it, a slide with property bit 1
// sets off the other explosion (vt+0x18c) first; any other slide: nothing.
void CKHkS08TransportableWeight::Vf154(const CGroundContactDatasInOut* contact) {
    const ICollisionMesh* ground = static_cast<const ICollisionMesh*>(contact->m_pGround);
    if (ground == nullptr) return;
    if ((ground->m_ui16PropertiesFlags & 0x200u) == 0) {
        Vf168();  // vt+0x168
        return;
    }
    if (((ground->m_ba16EngineFlags >> 1) & 1u) == 0) {
        if ((ground->m_ui16PropertiesFlags & 2u) == 0) return;
        Vf18C();  // vt+0x18c
        Vf108();  // vt+0x108
        static_cast<CKGrpTransportableObject*>(m_unk20)->ReleaseObject(this);  // 0x004a7ce0
        return;
    }
    static_cast<CKS08GameManager*>(g_pEngine->m_gameManager)
        ->SpawnSurfaceFx(0.0f, this, 3, 2, &contact->m_ProjectionOnGround.x);  // 0x004f9628; TOC +0x64d0
    CKSound* sound = static_cast<CKSoundDictionaryID*>(m_unk130)->GetSound(0);  // 0x00112bc0
    if (sound != nullptr) {
        sound->SetPosition(&contact->m_ProjectionOnGround);  // 0x00110fa0
        sound->Play(0.0f);                                   // 0x00111230
    }
    Vf108();
    static_cast<CKGrpTransportableObject*>(m_unk20)->ReleaseObject(this);
}

// 0x004b6ae8 CKHkS08TransportableWeight_SpawnImpactFx_maybe (vt+0x168): the explosion +0x13c at the grip.
void CKHkS08TransportableWeight::Vf168() { SpawnExplosionAtGrip(this, m_unk13c); }

// 0x004b7038 CKHkS08TransportableWeight_SpawnAltImpactFx_maybe (vt+0x18c): the explosion +0x1b0 at the grip.
void CKHkS08TransportableWeight::Vf18C() { SpawnExplosionAtGrip(this, m_unk1b0); }

// 0x004b5120 CKHkS08TransportableWeight_vf160: the fall's step after the position (+0x80) was integrated (State2).
// On a ground (status 1 or 2): the position follows the contact (a moving ground (class id 0x13) that is not a slide:
// the projection through its world matrix; any other ground but a slide without engine bit 1: the projection), less the
// grip's offset unless on such a slide; landed (vt+0x154); then, unless on such a slide, the velocity bounced on the
// contact normal (vt+0x164): unchanged means it stops (zero, landed +0xbc). Status 3 (nothing under it): when it was not
// drawn this frame, the stored music track asked for again, vt+0x108 and back into the pool. Then, every status but 3
// that returned, the move from the node's modelling position to +0x80 slides along the walls (cylinder +0x7c / +0x78):
// slid (2): the slide added and the velocity bounced on the wall's normal (unchanged: stopped); pushed out (3): the push
// added.
uint8_t CKHkS08TransportableWeight::Vf160(IKTime* /*clock*/) {
    const int32_t status = static_cast<int32_t>(m_GContactInOut.m_eContactStatus);
    if (status >= 1 && status <= 2) {
        const CVector3 normal = m_GContactInOut.m_Normal;  // +0x54 (f30, f31, f29)
        ICollisionMesh* ground = static_cast<ICollisionMesh*>(m_GContactInOut.m_pGround);
        bool projected = false;
        if (ground->GetClassID() == 0x13 && (ground->m_ui16PropertiesFlags & 0x200u) == 0) {  // vt+0x18
            Mat4_TransformPoints(ground->GetWorldMatrix(), &m_vPosition, &m_GContactInOut.m_ProjectionOnGround, 1);  // vt+0x50
            projected = true;
        }
        if (!projected) {
            ground = static_cast<ICollisionMesh*>(m_GContactInOut.m_pGround);
            if ((ground->m_ui16PropertiesFlags & 0x200u) == 0 || ((ground->m_ba16EngineFlags >> 1) & 1u) != 0) {
                m_vPosition.x = m_GContactInOut.m_ProjectionOnGround.x;
                m_vPosition.z = m_GContactInOut.m_ProjectionOnGround.z;
                m_vPosition.y = m_GContactInOut.m_ProjectionOnGround.y;
            }
        }
        ground = static_cast<ICollisionMesh*>(m_GContactInOut.m_pGround);
        const bool deadSlide =
            (ground->m_ui16PropertiesFlags & 0x200u) != 0 && ((ground->m_ba16EngineFlags >> 1) & 1u) == 0;
        if (!deadSlide && Vf118() != nullptr) {  // vt+0x118
            const CSGHotSpot* grip = Vf118();
            m_vPosition.z = m_vPosition.z - grip->m_v3RelativePosition.z;
            m_vPosition.x = m_vPosition.x - grip->m_v3RelativePosition.x;
            m_vPosition.y = m_vPosition.y - grip->m_v3RelativePosition.y;
        }
        Vf154(&m_GContactInOut);  // vt+0x154
        ground = static_cast<ICollisionMesh*>(m_GContactInOut.m_pGround);
        if ((ground->m_ui16PropertiesFlags & 0x200u) == 0 || ((ground->m_ba16EngineFlags >> 1) & 1u) != 0) {
            const CVector3 velocity = m_vVelocity;
            CVector3 out;
            Vf164(&out, &velocity, &normal);  // vt+0x164
            if (m_vVelocity.x == out.x && out.y == m_vVelocity.y && out.z == m_vVelocity.z) {
                m_vVelocity = kWeightZero;  // TOC +0x64c4: 0x00c50d64
                m_bLanded = 1;
            } else {
                m_vVelocity.z = out.z;
                m_vVelocity.x = out.x;
                m_vVelocity.y = out.y;
            }
        }
    } else if (status == 3) {
        if (WeightNode(this)->m_ui16LastRenderedFrame != g_ui16RenderFrameCounter) {  // TOC +0x64d4: 0x00c29694
            static_cast<CKS08GameManager*>(g_pEngine->m_gameManager)->RequestStoredMusicTrack();  // 0x004f6b78
            Vf108();  // vt+0x108
            static_cast<CKGrpTransportableObject*>(m_unk20)->ReleaseObject(this);  // 0x004a7ce0
        }
    }
    const RwV3d& from = WeightNode(this)->m_pRwFrame->modelling.pos;
    CLine line;
    line.m_start = {from.x, from.y, from.z};
    const RwV3d& p = WeightNode(this)->m_pRwFrame->modelling.pos;
    line.m_VectDir.x = m_vPosition.x - p.x;
    line.m_VectDir.y = m_vPosition.y - p.y;
    line.m_VectDir.z = m_vPosition.z - p.z;
    CSlideGroundEdgeDatasOut slide;
    const uint8_t result = static_cast<CKSrvCollision*>(g_pEngine->m_srvCollision)
                               ->ResolveSweptCylinderWalls(&line, m_unk7c, m_unk78, &slide, nullptr, nullptr, 1);  // 0x0019aa68
    if (result == 2) {
        m_vPosition.x = m_vPosition.x + slide.m_v3BouncingVector.x;
        m_vPosition.y = m_vPosition.y + slide.m_v3BouncingVector.y;
        m_vPosition.z = m_vPosition.z + slide.m_v3BouncingVector.z;
        const CVector3 velocity = m_vVelocity;
        const CVector3 normal = slide.m_v3Normal;
        CVector3 out;
        Vf164(&out, &velocity, &normal);  // vt+0x164
        if (m_vVelocity.x == out.x && out.y == m_vVelocity.y && out.z == m_vVelocity.z) {
            m_vVelocity = kWeightZero;
        } else {
            m_vVelocity.z = out.z;
            m_vVelocity.x = out.x;
            m_vVelocity.y = out.y;
        }
    } else if (result == 3) {
        m_vPosition.x = m_vPosition.x + slide.m_v3BouncingVector.x;
        m_vPosition.y = m_vPosition.y + slide.m_v3BouncingVector.y;
        m_vPosition.z = m_vPosition.z + slide.m_v3BouncingVector.z;
    }
    return 0;  // r3 is not set on the way out (State2 ignores it)
}

// 0x004b5860 CKHkS08TransportableWeight_vf188: the carried weight's swing (a damped spring per axis, dt > 0). The hot
// spot's world matrix (carrier vt+0x7c); its velocity from the last position (+0x1b4; unset: none) gives the targets:
// along its right axis * 0.1 clamped to [-1, 1], along its at axis * 0.07 clamped to [lower, 1], lower = -1 or, with a
// CKHkS08Hero carrier (key 0x25c2), -((d - 0.2) * 3.5) when that is below 1 (d the flat distance from the hot spot to the
// hero's hot spot 0x13). Each swing speed takes the acceleration along its axis * 0.2, the pull to the target * 20 and a
// damping of -0.8 (fmadds by dt); the swings advance and are clamped again. The up axis +0x17c = Y + atan(swing right) *
// right - atan(swing at) * at, normalised.
void CKHkS08TransportableWeight::Vf188(float dt) {
    CKS08CarrierHero* carrier = static_cast<CKS08CarrierHero*>(m_pCarrier);
    CMatrix34 m;
    static_cast<CSGHotSpot*>(carrier->Vf7C())->GetWorldMatrix(&m);  // vt+0x7c, 0x000ce970
    if (dt == 0.0f) return;  // TOC +0x64d0; bne: NaN goes on
    const float px = m.m_pos.x;
    const float py = m.m_pos.y;
    const float pz = m.m_pos.z;
    IKSerializable* holder = carrier->Vf64();  // vt+0x64
    float lowerRight = -1.0f;  // f23 (TOC +0x64a8)
    float lowerAt = -1.0f;     // f24
    if (holder->IsKindOfClass(0x25c2) != 0) {  // vt+0x08
        CKHkS08Hero* hero = static_cast<CKHkS08Hero*>(holder);
        hero->GetDragonIndex();  // 0x00361960 (result unused)
        CVector3 v;
        static_cast<CSGHotSpot*>(hero->GetHotSpot(0x13))->GetWorldPosition(&v);  // 0x00361b70, 0x000ce790
        v.x = v.x - px;
        v.y = 0.0f;
        v.z = v.z - pz;
        float d = static_cast<float>(c22spyro::MathSqrtf(ppc::fmadds(v.z, v.z, ppc::fmadds(v.x, v.x, 0.0f))));  // 0x00010690
        if ((d - 0.2f) * 3.5f < 1.0f) {  // TOC +0x64e0 / +0x64e4 / +0x64e8; blt
            d = static_cast<float>(c22spyro::MathSqrtf(ppc::fmadds(v.z, v.z, ppc::fmadds(v.x, v.x, v.y * v.y))));
            lowerAt = -((d - 0.2f) * 3.5f);
        }
    }
    const float inv = 1.0f / dt;
    float vx = 0.0f;
    float vy = 0.0f;
    float vz = 0.0f;
    if (m_vPrevGripPos.x != kUnset) {  // only x is compared
        vx = (m_vPrevGripPos.x - px) * inv;
        vy = (m_vPrevGripPos.y - py) * inv;
        vz = (m_vPrevGripPos.z - pz) * inv;
    }
    const float ax = (m_vPrevGripVel.x - vx) * inv;
    const float ay = (m_vPrevGripVel.y - vy) * inv;
    const float az = (m_vPrevGripVel.z - vz) * inv;
    m_vPrevGripVel.y = vy;
    m_vPrevGripPos.y = py;
    m_vPrevGripVel.x = vx;
    m_vPrevGripPos.x = px;
    m_vPrevGripVel.z = vz;
    m_vPrevGripPos.z = pz;
    const CVector3& r = m.m_right;
    const CVector3& at = m.m_at;
    float targetRight = ppc::fmadds(vz, r.z, ppc::fmadds(vx, r.x, vy * r.y)) * 0.1f;  // TOC +0x64ec
    float targetAt = ppc::fmadds(vz, at.z, ppc::fmadds(vx, at.x, vy * at.y)) * 0.07f;  // TOC +0x64f0
    // The clamps (cror: NaN passes through both).
    auto clamp = [](float value, float lower) {
        if (value <= lower) return lower;
        if (value >= 1.0f) return 1.0f;
        return value;
    };
    targetRight = clamp(targetRight, lowerRight);
    targetAt = clamp(targetAt, lowerAt);
    const float accRight = ppc::fmadds(az, r.z, ppc::fmadds(ax, r.x, ay * r.y)) * 0.2f;  // f26 (TOC +0x64e0)
    const float accAt = ppc::fmadds(az, at.z, ppc::fmadds(ax, at.x, ay * at.y)) * 0.2f;
    float speedRight = ppc::fmadds(dt, accRight, m_fSwingRightSpeed);
    float speedAt = ppc::fmadds(dt, accAt, m_fSwingAtSpeed);
    speedRight = ppc::fmadds(dt, (targetRight - m_fSwingRight) * 20.0f, speedRight);  // TOC +0x64f4
    speedAt = ppc::fmadds(dt, (targetAt - m_fSwingAt) * 20.0f, speedAt);
    speedRight = ppc::fmadds(dt, speedRight * -0.8f, speedRight);  // TOC +0x64f8
    speedAt = ppc::fmadds(dt, speedAt * -0.8f, speedAt);
    const float swingRight = ppc::fmadds(dt, speedRight, m_fSwingRight);
    m_fSwingRightSpeed = speedRight;
    const float swingAt = ppc::fmadds(dt, speedAt, m_fSwingAt);
    m_fSwingAtSpeed = speedAt;
    m_fSwingRight = swingRight;
    m_fSwingAt = swingAt;
    m_fSwingRight = clamp(swingRight, lowerRight);
    m_fSwingAt = clamp(swingAt, lowerAt);
    m_vSwingUp = kWeightAxisY;  // TOC +0x64fc: 0x00c50d40
    const float a = crt::Atanf(m_fSwingRight);  // TocBridge_Math_Atanf_maybe 0x0098f1e0
    m_vSwingUp.z = ppc::fmadds(a, r.z, m_vSwingUp.z);
    m_vSwingUp.x = ppc::fmadds(a, r.x, m_vSwingUp.x);
    m_vSwingUp.y = ppc::fmadds(a, r.y, m_vSwingUp.y);
    const float b = -crt::Atanf(m_fSwingAt);
    m_vSwingUp.y = ppc::fmadds(b, at.y, m_vSwingUp.y);
    m_vSwingUp.x = ppc::fmadds(b, at.x, m_vSwingUp.x);
    m_vSwingUp.z = ppc::fmadds(b, at.z, m_vSwingUp.z);
    const float length = static_cast<float>(c22spyro::MathSqrtf(
        ppc::fmadds(m_vSwingUp.z, m_vSwingUp.z, ppc::fmadds(m_vSwingUp.x, m_vSwingUp.x, m_vSwingUp.y * m_vSwingUp.y))));
    if (length == 0.0f) return;
    const float s = 1.0f / length;
    m_vSwingUp.z = s * m_vSwingUp.z;
    m_vSwingUp.x = s * m_vSwingUp.x;
    m_vSwingUp.y = s * m_vSwingUp.y;
}
