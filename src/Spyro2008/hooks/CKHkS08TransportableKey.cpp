// CKHkS08TransportableKey.cpp - reconstructed original translation unit 0x4ac580-0x4b08d8 (GAME_TOC1, main_toc1), 52 functions, 49 live.
// Primary class: CKHkS08TransportableKey  key 0x3082  category Hook  size 0x130  vtable 0xb28c08
// Other owners: Vec3 (1), CKHkS08TransportableWeight (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x4ac580  CKHkS08TransportableKey_vf124
//   [x] 0x4ac5d0  CKHkS08TransportableKey_vf120  (header)
//   [x] 0x4ac610  CKHkS08TransportableKey_vf17C
//   [x] 0x4ac888  CKHkS08TransportableKey_vf180
//   [x] 0x4ac8f0  CKHkS08TransportableKey_vf16C
//   [ ] 0x4ac920  CKHkS08TransportableKey_ProbeGroundAtPoint_maybe  [dead]
//   [ ] 0x4ac9a8  Vec3_YawDifferenceWrapped_4_maybe  [dead]
//   [x] 0x4aca38  CKHkS08TransportableKey_UpdateGroundAttachment_maybe
//   [x] 0x4acdc0  CKHkS08TransportableKey_Resume  (empty / no effect: inherited)
//   [x] 0x4acde8  CKHkS08TransportableKey_Pause  (empty / no effect: inherited)
//   [x] 0x4ace10  CKHkS08TransportableKey_Stop  (header)
//   [ ] 0x4ace38  CKHkS08TransportableKey_Save
//   [x] 0x4ace60  CKHkS08TransportableKey_RecursiveRegistration  (the base's 0x4ac1f0 -> CKHkActorBase's 0x3f6ee8 -> IKHook's: inherited)
//   [x] 0x4ace88  CKHkS08TransportableKey_Destroy
//   [x] 0x4aced0  CKHkS08TransportableKey_Construct
//   [x] 0x4acf40  CKHkS08TransportableKey_DeleteArray
//   [x] 0x4acfe0  CKHkS08TransportableKey_PostLoad
//   [x] 0x4ad0b0  CKHkS08TransportableKey_State0_maybe
//   [x] 0x4ad128  CKHkS08TransportableWeight_ConstructBase_maybe
//   [x] 0x4ad198  CKHkS08TransportableKey_vf178
//   [x] 0x4ad1e0  CKHkS08TransportableKey_vf110  (header)
//   [x] 0x4ad1f8  CKHkS08TransportableKey_vfF4
//   [ ] 0x4ad220  RegisterCKHkS08TransportableKeyClass
//   [ ] 0x4ad2a8  _GLOBAL__D_4ad2a8
//   [ ] 0x4ad2b8  _GLOBAL__I_4ad2b8
//   [x] 0x4ad2c8  CKHkS08TransportableKey_OnActivate
//   [x] 0x4ad3e0  CKHkS08TransportableKey_vf154
//   [x] 0x4ad4b0  CKHkS08TransportableKey_vfFC
//   [x] 0x4ad5b0  CKHkS08TransportableKey_vf170
//   [x] 0x4ad5e0  CKHkS08TransportableKey_vf174
//   [x] 0x4ad610  CKHkS08TransportableKey_BaseDestructor  (header)
//   [x] 0x4ad640  CKHkS08TransportableKey_DeletingDestructor  (header)
//   [x] 0x4ad688  CKHkS08TransportableKey_Destructor  (header)
//   [x] 0x4ad6b8  CKHkS08TransportableKey_State1
//   [x] 0x4ad8f0  CKHkS08TransportableKey_OnDeactivate
//   [x] 0x4ada30  CKHkS08TransportableKey_vf164
//   [x] 0x4adb08  CKHkS08TransportableKey_Restart
//   [x] 0x4adcf0  CKHkS08TransportableKey_vf160
//   [x] 0x4ae250  CKHkS08TransportableKey_PlayImpactFeedback_maybe
//   [x] 0x4ae688  CKHkS08TransportableKey_State2
//   [x] 0x4aebf8  CKHkS08TransportableKey_Create
//   [x] 0x4aec80  CKHkS08TransportableKey_CreateArray
//   [ ] 0x4aed80  CKHkS08TransportableKey_FindGroundPointByRaising_maybe  [dead]
//   [x] 0x4aeee8  CKHkS08TransportableKey_Load
//   [x] 0x4af358  CKHkS08TransportableKey_Start
//   [x] 0x4af510  CKHkS08TransportableKey_vf10C
//   [x] 0x4af670  CKHkS08TransportableKey_vf108
//   [x] 0x4af750  CKHkS08TransportableKey_vf134
//   [x] 0x4af8e8  CKHkS08TransportableKey_ResetStateMachine_maybe
//   [x] 0x4af9a8  CKHkS08TransportableKey_vfF8
//   [x] 0x4afd08  CKHkS08TransportableKey_vfF0
//   [x] 0x4aff00  CKHkS08TransportableKey_Update
//
//   [x] 0x9c52f8  CKHkS08TransportableKey_vf12C  [inline]  (base)
//   [x] 0x9c5300  CKHkS08TransportableKey_vf130  [inline]  (base)
//   [x] 0x9c5308  CKHkS08TransportableKey_vf140  [inline]  (base)
//   [x] 0x9c5350  CKHkS08TransportableKey_vf144  [inline]  (base)
//   [x] 0x9c5358  CKHkS08TransportableKey_vf148  [inline]  (base)
//   [x] 0x9c5360  CKHkS08TransportableKey_vf14C  [inline]
//   [x] 0x9c5368  CKHkS08TransportableKey_vf150  [inline]  (base)
//   [x] 0x9c53b8  CKHkS08TransportableKey_IsKindOfClass  [inline]
//   [x] 0x9c5418  CKHkS08TransportableKey_GetClassType  [inline]
//   [x] 0x9c5420  CKHkS08TransportableKey_GetClassID  [inline]
//   [x] 0x9c5428  CKHkS08TransportableKey_vf114  [inline]  (header)
//   [x] 0x9c5430  CKHkS08TransportableKey_vf118  [inline]  (header)
//   [x] 0x9c5438  CKHkS08TransportableKey_vf138  [inline]  (header)
//   [x] 0x9c5440  CKHkS08TransportableKey_vf13C  [inline]  (header)
//   [x] 0x9c5448  CKHkS08TransportableKey_vf158  [inline]  (header)
//   [x] 0x9c5450  CKHkS08TransportableKey_vf15C  [inline]
//   [x] 0x9c5458  CKHkS08TransportableKey_vf184  [inline]  (header)
//   [x] 0x9c5460  CKHkS08TransportableKey_vf104  [inline]
#include "Spyro2008/hooks/CKHkS08TransportableKey.h"
#include "k2000/core/Ps3MemberFn.h"
#include "Spyro2008/groups/C22SpyroShims.h"

#include "k2000/io/IKFile.h"
#include "k2000/misc/Mat4.h"
#include "k2000/scenegraph/CSGLeaf.h"
#include "k2000/scenegraph/CNode.h"
#include "k2000/geometry/CGeometry.h"
#include "k2000/fx/IKFx.h"
#include "k2000/groups/CKGrpTransportableObject.h"
#include "k2000/logic/CKParticlesEffectFxData.h"
#include "k2000/logic/CSGHotSpot.h"
#include "k2000/logic/CKLevel.h"
#include "k2000/logic/CKSector.h"
#include "k2000/logic/KBase910C.h"
#include "k2000/misc/Engine.h"
#include "k2000/scenegraph/CSGBranch.h"
#include "k2000/services/CKSrvCollision.h"
#include "k2000/services/CKSrvFx.h"
#include "k2000/services/CollisionDatas.h"
#include "k2000/services/ICollisionMesh.h"
#include "k2000/system/IKTime.h"
#include "k2000/dictionaries/CKSoundDictionaryID.h"
#include "Renderware/rwcore/RwCamera.h"
#include "Spyro2008/logic/CKS08CarrierHero.h"
#include "Spyro2008/logic/CKS08GameManager.h"
#include "k2000/logic/sound/CKSound.h"
#include "k2000/render/CRenderer.h"
#include "crt/ppc_ops.h"

#include <cfloat>
#include <cstring>

// 0x004acfe0 CKHkS08TransportableKey_PostLoad: KBase3002_PostLoad; for the level type two RwMatrixCreate_Thunk matrices
// (+0xec, orthonormalised in place, and +0x108), +0x40 = 0 and bit 2 (hidden) of the hook's scene node (+0x1c); for
// the other types only +0x40 = 0.
int32_t CKHkS08TransportableKey::PostLoad(int32_t type) {
    CKHkS08TransportableBase::PostLoad(type);
    if (type != K_LEVEL_PLATEFORMS) {
        m_unk40 = nullptr;
        return 1;
    }
    CMatrix34* matrix = RwMatrixCreate_Thunk();
    m_unkEC = matrix;
    Mat4_OrthoNormalizeInPlace(matrix);
    m_unk108 = RwMatrixCreate_Thunk();
    CSGLeaf* node = static_cast<CSGLeaf*>(m_pKGLObject);
    m_unk40 = nullptr;  // stw of the type (0)
    node->m_sgProperties = (node->m_sgProperties & 0xfffffffbu) | 4u;
    return 1;
}

// 0x004aeee8 CKHkS08TransportableKey_Load
int32_t CKHkS08TransportableKey::Load(IKFile* file, int32_t type) {
    CKHkS08TransportableBase::Load(file, type);
    if (type == K_LEVEL_PLATEFORMS) {
        ReadF32LE(file, &m_unk78);
        ReadF32LE(file, &m_unk7c);
        ReadU32LEWords(file, reinterpret_cast<uint32_t*>(&m_unk98), 3);
        ReadF32LE(file, &m_unkB4);
        ReadF32LE(file, &m_unkB8);
        ReadF32LE(file, &m_unkE8);
        ReadF32LE(file, &m_unkF8);
        ReadF32LE(file, &m_unkF4);
        ReadF32LE(file, &m_unkF0);
        IKFile_ReadRef(file, &m_unk44);
        IKFile_ReadRef(file, &m_unk34);
        IKFile_ReadRef(file, &m_unk3c);
        IKFile_ReadRef(file, &m_unk38);
    }
    return 1;
}

namespace {
// DOTD: the key's state handlers by descriptor (k2000/core/Ps3MemberFn.h; the table Start builds at +0x118).
Ps3MemberFnEntry<CKHkS08TransportableKey::StateFn> g_keyStates[] = {
    {0x00bc7420u, &CKHkS08TransportableKey::State0, "CKHkS08TransportableKey_State0_maybe 0x4ad0b0", false},
    {0x00bc74c0u, &CKHkS08TransportableKey::State1, "CKHkS08TransportableKey_State1 0x4ad6b8", false},
    {0x00bc7578u, &CKHkS08TransportableKey::State2, "CKHkS08TransportableKey_State2 0x4ae688", false},
};

// 0x00c50da0 (StaticInitAndDestruction_11578): FLT_MAX x3, the "no point" vector (TOC +0x6350).
const CVector3 kNoPoint = {FLT_MAX, FLT_MAX, FLT_MAX};
// 0x00c50d64: the zero vector.
const CVector3 kZero = {0.0f, 0.0f, 0.0f};
// 0x00c50d40: the y axis.
const CVector3 kAxisY = {0.0f, 1.0f, 0.0f};

CSGLeaf* KeyNode(CKHkS08TransportableKey* key) { return static_cast<CSGLeaf*>(key->m_pKGLObject); }

// The node's frame modelling position set (the identity flag 0x20000 cleared), the frame marked dirty (0x10698).
void SetNodePosition(CSGLeaf* node, float x, float y, float z) {
    RwFrame* frame = node->m_pRwFrame;
    frame->modelling.pos.x = x;
    frame->modelling.pos.y = y;
    frame->modelling.pos.z = z;
    frame->modelling.flags &= 0xfffdffffu;
    RwFrame_MarkDirty(frame);
}

CMatrix34* AsMatrix(RwMatrix* m) { return reinterpret_cast<CMatrix34*>(m); }
const RwMatrix* AsRw(const CMatrix34* m) { return reinterpret_cast<const RwMatrix*>(m); }

// The ground's sector is active (CKSector +0x06 bit 0).
bool GroundSectorActive(IKSerializable* ground) {
    const uint16_t index = static_cast<ICollisionMesh*>(ground)->GetSectorNumber();  // 0x001a6ba8
    CKSector* sector = static_cast<CKSector*>(g_pEngine->m_level->m_vpSectors.m_pBlock[index]);
    return (sector->m_ba16Properties & 1u) != 0;
}
}  // namespace

uint8_t CKHkS08TransportableKey::CallState(const uint32_t pair[2], IKTime* clock, int32_t phase, uint8_t other) {
    StateFn fn = ResolvePs3MemberFn(g_keyStates, pair, "CKHkS08TransportableKey state handler");
    if (fn == nullptr) return other;
    return (this->*fn)(clock, phase, other);
}

void CKHkS08TransportableKey::SwitchState(uint8_t next, IKTime* clock, uint8_t leaveOther) {
    const uint32_t* table = static_cast<const uint32_t*>(m_pUnk110);
    const uint8_t old = m_unk114;
    if (old != 0xff) CallState(&table[old * 2u], clock, 2, leaveOther);
    m_unk114 = next;
    if (next != 0xff) CallState(&table[next * 2u], clock, 1, old);
}

void CKHkS08TransportableKey::RunStateMachine(IKTime* clock) {
    const uint8_t state = m_unk114;
    if (state == 0xff) return;
    const uint32_t* table = static_cast<const uint32_t*>(m_pUnk110);
    const uint8_t next = CallState(&table[state * 2u], clock, 0, state);
    if (next != m_unk114) SwitchState(next, clock, next);
}

namespace {
// The state machine's exit (the table +0x110, the current state +0x114): the state left with no clock towards 0xff.
void LeaveKeyState(CKHkS08TransportableKey* key) {
    if (key->m_unk114 != 0xff) {
        key->CallState(&static_cast<const uint32_t*>(key->m_pUnk110)[key->m_unk114 * 2u], nullptr, 2, 0xff);
    }
    key->m_unk114 = 0xff;
}
}  // namespace

// 0x004af670 CKHkS08TransportableKey_vf108: during the machine's tick (+0xe0) the pending state +0xdc = 0xff (State2 ends
// with it); otherwise the state machine left.
void CKHkS08TransportableKey::Vf108() {
    if (m_bInStateUpdate != 0) {
        m_i32PendingState = 0xff;
        return;
    }
    LeaveKeyState(this);
}

// 0x004af8e8 CKHkS08TransportableKey_ResetStateMachine_maybe (vt+0x11c): no carrier, the state machine left.
void CKHkS08TransportableKey::ResetStateMachine() {
    m_pCarrier = nullptr;
    LeaveKeyState(this);
}

// 0x004af510 CKHkS08TransportableKey_vf10C: a machine with no state enters state 1 (no clock, from 0xff).
void CKHkS08TransportableKey::Vf10C() {
    if (m_unk114 != 0xff) return;
    m_unk114 = 1;
    CallState(&static_cast<const uint32_t*>(m_pUnk110)[2], nullptr, 1, 0xff);
}

// 0x9c5460 CKHkS08TransportableKey_vf104: the word at 0x00c2bca8 read as a float (0x436f6f72, the bytes "Coor" of the
// string data there: BUG(original) or a shared constant; its value is kept).
float CKHkS08TransportableKey::Vf104() {
    const uint32_t bits = 0x436f6f72u;
    float value;
    std::memcpy(&value, &bits, sizeof(value));
    return value;
}

// 0x004ac580 CKHkS08TransportableKey_vf124: vt+0x180, then +0xc0 cleared.
void CKHkS08TransportableKey::Vf124() {
    Vf180();
    m_pDynamicGround = nullptr;  // +0xc0
}

// 0x004ac888 CKHkS08TransportableKey_vf180: the effect +0x40 released (vt+0x58 with the key as owner).
void CKHkS08TransportableKey::Vf180() {
    if (m_unk40 != nullptr) {
        static_cast<IKFx*>(m_unk40)->StopAndRelease(this);
        m_unk40 = nullptr;
    }
}

// 0x004ac610 CKHkS08TransportableKey_vf17C: no effect yet: the effect data +0x3c attached to the grip (+0x10 node 0, +0x14
// the hot spot +0x34) and its pooled effect acquired with the key as owner (inlined lookup) into +0x40.
void CKHkS08TransportableKey::Vf17C() {
    if (m_unk40 != nullptr) return;
    CKParticlesEffectFxData* data = static_cast<CKParticlesEffectFxData*>(m_unk3c);
    data->m_pAttachOwner = nullptr;
    data->m_pAttachHotSpot = m_unk34;
    m_unk40 = static_cast<CKSrvFx*>(g_pEngine->m_srvFx)->AcquireFx(data, this);
}

// 0x004ac8f0 / 0x004ad5b0 / 0x004ad5e0 CKHkS08TransportableKey_vf16C / vf170 / vf174
CKSound* CKHkS08TransportableKey::Vf16C() { return static_cast<CKSoundDictionaryID*>(m_unk44)->GetSound(0); }
CKSound* CKHkS08TransportableKey::Vf170() { return static_cast<CKSoundDictionaryID*>(m_unk44)->GetSound(1); }
CKSound* CKHkS08TransportableKey::Vf174() { return static_cast<CKSoundDictionaryID*>(m_unk44)->GetSound(2); }

// 0x004ad198 CKHkS08TransportableKey_vf178
void CKHkS08TransportableKey::Vf178() {
    ICollisionMesh* ground = static_cast<ICollisionMesh*>(m_GContactInOut.m_pGround);
    if (ground == nullptr) return;
    if ((ground->m_ui16PropertiesFlags & 0x200u) != 0) return;
    m_vGroundPoint.x = m_GContactInOut.m_ProjectionOnGround.x;
    m_vGroundPoint.z = m_GContactInOut.m_ProjectionOnGround.z;
    m_vGroundPoint.y = m_GContactInOut.m_ProjectionOnGround.y;
}

// 0x004ada30 CKHkS08TransportableKey_vf164
void CKHkS08TransportableKey::Vf164(CVector3* out, const CVector3* velocity, const CVector3* normal) {
    const float vy = velocity->y;
    const float vx = velocity->x;
    const float d = -ppc::fmadds(normal->z, velocity->z, ppc::fmadds(vx, normal->x, normal->y * vy));
    const float nz = normal->z * d;
    const float nx = normal->x * d;
    const float ny = normal->y * d;
    out->z = nz + nz + velocity->z;
    out->x = vx + nx + nx;
    out->y = ny + ny + vy;
    const float bounce = m_unkB4;
    out->y = bounce * out->y;
    out->x = bounce * out->x;
    out->z = bounce * out->z;
    const float minimum = m_unkB8;
    if (minimum * minimum <= ppc::fmadds(out->z, out->z, ppc::fmadds(out->x, out->x, out->y * out->y)) && minimum != 0.0f) {
        return;
    }
    out->x = velocity->x;
    const float y = velocity->y;
    out->z = velocity->z;
    out->y = y;
}

// 0x004ad3e0 CKHkS08TransportableKey_vf154: landed on a ground that is neither a slide (0x200) nor bit 0: the impact
// feedback (vt+0x168); otherwise vt+0x108 and back into the group's pool (ReleaseObject).
void CKHkS08TransportableKey::Vf154(const CGroundContactDatasInOut* contact) {
    const ICollisionMesh* ground = static_cast<const ICollisionMesh*>(contact->m_pGround);
    if (ground != nullptr && (ground->m_ui16PropertiesFlags & 0x200u) == 0 && (ground->m_ui16PropertiesFlags & 1u) == 0) {
        Vf168();
        return;
    }
    Vf108();
    static_cast<CKGrpTransportableObject*>(m_unk20)->ReleaseObject(this);  // 0x004a7ce0
}

// 0x004af9a8 CKHkS08TransportableKey_vfF8 (C2.8 port-rest R10): let go with `velocity`. A hero carrier (0x91cc) next to a
// receiver, no ground, or an enemy carrier (0x958c) only asks the carrier held (+0x48, vt+0x5c); anyone else first needs
// a ground that is not a slide (0x200) and a contact status other than 3. Let go: the velocity kept (+0x8c), the carrier
// told (vt+0x54), no carrier, the machine switched to state 2 (falling; no clock).
uint8_t CKHkS08TransportableKey::VfF8(IKSerializable* carrier, const CVector3* velocity) {
    const bool heroAtReceiver =
        carrier->IsKindOfClass(0x91cc) != 0 && static_cast<CKS08CarrierHero*>(carrier)->HasNearbyReceiver() != 0;
    if (!heroAtReceiver) {
        const ICollisionMesh* ground = static_cast<const ICollisionMesh*>(m_GContactInOut.m_pGround);
        if (ground != nullptr && carrier->IsKindOfClass(0x958c) == 0) {
            if ((ground->m_ui16PropertiesFlags & 0x200u) != 0) return 0;
            if (m_GContactInOut.m_eContactStatus == 3) return 0;
        }
    }
    if (static_cast<KBase910C*>(m_pCarrier)->Vf5C(this) == 0) return 0;  // vt+0x5c
    m_vVelocity.x = velocity->x;
    m_vVelocity.z = velocity->z;
    m_vVelocity.y = velocity->y;
    static_cast<KBase910C*>(m_pCarrier)->StopCarrying(this);  // vt+0x54
    m_pCarrier = nullptr;
    SwitchState(2, nullptr, 2);
    return 1;
}

namespace {
// The surface of the impact effect (0x4ae250's inlined test, three times): none without a ground; engine flag bit 1:
// 3; property 0x800: 0; 0x1000: 1; 0x2000: 2; else 0.
uint32_t KeyImpactSurface(const ICollisionMesh* ground) {
    if (ground == nullptr) return 0;
    if (((ground->m_ba16EngineFlags >> 1) & 1u) != 0) return 3;
    const uint16_t flags = ground->m_ui16PropertiesFlags;
    if ((flags & 0x800u) != 0) return 0;
    if ((flags & 0x1000u) != 0) return 1;
    if ((flags & 0x2000u) != 0) return 2;
    return 0;
}
}  // namespace

// 0x004ae250 CKHkS08TransportableKey_PlayImpactFeedback_maybe (vt+0x168, C2.8 port-rest R10): with a ground, the speed
// of the velocity's part along the contact normal picks the feedback: at least +0xf8 (when +0xf8 > 0) the hard one (sound
// vt+0x174, surface effect kind 2), else at least +0xf4 the medium one (vt+0x170, kind 1), else at least +0xf0 the soft
// one (vt+0x16c, kind 0); the sound at the node's world position (volume 0.0), the effect at the contact point.
void CKHkS08TransportableKey::Vf168() {
    if (m_GContactInOut.m_pGround == nullptr) return;
    CKS08GameManager* manager = static_cast<CKS08GameManager*>(g_pEngine->m_gameManager);
    const CVector3& n = m_GContactInOut.m_Normal;  // +0x54
    const float dot = ppc::fmadds(n.z, m_vVelocity.z, ppc::fmadds(n.x, m_vVelocity.x, n.y * m_vVelocity.y));
    const float pz = n.z * dot;
    const float px = n.x * dot;
    const float py = n.y * dot;
    const float zero = 0.0f;  // TOC +0x6334
    auto speed = [&]() { return std::sqrt(ppc::fmadds(pz, pz, ppc::fmadds(px, px, py * py))); };  // 0x00010690
    CKSound* sound = nullptr;
    uint32_t mode = 0;
    if (m_unkF8 > zero && m_unkF8 <= speed()) {
        sound = Vf174();  // vt+0x174
        mode = 2;
    } else if (m_unkF4 > zero && m_unkF4 <= speed()) {
        sound = Vf170();  // vt+0x170
        mode = 1;
    } else if (m_unkF0 > zero && m_unkF0 <= speed()) {
        sound = Vf16C();  // vt+0x16c
        mode = 0;
    } else {
        return;
    }
    if (sound != nullptr) {
        const RwV3d& p = KeyNode(this)->m_pRwFrame->ltm.pos;  // node +0x4 -> +0x80
        const CVector3 position = {p.x, p.y, p.z};
        sound->SetPosition(&position);  // 0x00110fa0
        sound->Play(zero);              // 0x00111230
    }
    manager->SpawnSurfaceFx(zero, this, KeyImpactSurface(static_cast<const ICollisionMesh*>(m_GContactInOut.m_pGround)),
                            mode, &m_GContactInOut.m_ProjectionOnGround.x);  // 0x004f9628
}

// 0x004adcf0 CKHkS08TransportableKey_vf160 (C2.8 port-rest R10): the fall's step after the position (+0x80) was
// integrated (State2). On a ground (status 1 or 2): the position follows the contact (a moving ground (class id 0x13):
// the projection through its world matrix; any other: the projection) less the grip's offset; landed (vt+0x154); the
// velocity bounced on the contact normal (vt+0x164): unchanged means it stops (zero, landed +0xbc). Status 3 (nothing
// under it): when it was not drawn this frame, vt+0x108 and back into the pool. Then the move from the node's modelling
// position to +0x80 slides along the walls (cylinder +0x7c / +0x78): slid (2): the slide added and the velocity bounced on
// the wall's normal (unchanged: stopped); pushed out (3): the push added. (The Weight's 0x4b5120 adds the slide cases.)
uint8_t CKHkS08TransportableKey::Vf160(IKTime* /*clock*/) {
    static const CVector3 kZero = {0.0f, 0.0f, 0.0f};  // TOC +0x6358: 0x00c50d64
    const int32_t status = static_cast<int32_t>(m_GContactInOut.m_eContactStatus);
    if (status > 0 && status < 3) {
        const CVector3 normal = m_GContactInOut.m_Normal;  // +0x54 (f30, f31, f29)
        ICollisionMesh* ground = static_cast<ICollisionMesh*>(m_GContactInOut.m_pGround);
        if (ground->GetClassID() == 0x13) {  // vt+0x18
            Mat4_TransformPoints(ground->GetWorldMatrix(), &m_vPosition, &m_GContactInOut.m_ProjectionOnGround, 1);  // vt+0x50
        } else {
            m_vPosition.x = m_GContactInOut.m_ProjectionOnGround.x;
            m_vPosition.y = m_GContactInOut.m_ProjectionOnGround.y;
            m_vPosition.z = m_GContactInOut.m_ProjectionOnGround.z;
        }
        if (Vf118() != nullptr) {  // vt+0x118
            const CSGHotSpot* grip = Vf118();
            m_vPosition.z = m_vPosition.z - grip->m_v3RelativePosition.z;
            m_vPosition.x = m_vPosition.x - grip->m_v3RelativePosition.x;
            m_vPosition.y = m_vPosition.y - grip->m_v3RelativePosition.y;
        }
        Vf154(&m_GContactInOut);  // vt+0x154
        const CVector3 velocity = m_vVelocity;
        CVector3 out;
        Vf164(&out, &velocity, &normal);  // vt+0x164
        if (m_vVelocity.x == out.x && out.y == m_vVelocity.y && out.z == m_vVelocity.z) {
            m_vVelocity = kZero;
            m_bLanded = 1;
        } else {
            m_vVelocity.z = out.z;
            m_vVelocity.x = out.x;
            m_vVelocity.y = out.y;
        }
    } else if (status == 3) {
        if (KeyNode(this)->m_ui16LastRenderedFrame != g_ui16RenderFrameCounter) {  // TOC: 0x00c29694
            Vf108();  // vt+0x108
            static_cast<CKGrpTransportableObject*>(m_unk20)->ReleaseObject(this);  // 0x004a7ce0
        }
    }
    const RwV3d& from = KeyNode(this)->m_pRwFrame->modelling.pos;
    CLine line;
    line.m_start = {from.x, from.y, from.z};
    line.m_VectDir.x = m_vPosition.x - from.x;
    line.m_VectDir.y = m_vPosition.y - from.y;
    line.m_VectDir.z = m_vPosition.z - from.z;
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
        if (m_vVelocity.x != out.x || out.y != m_vVelocity.y || out.z != m_vVelocity.z) {
            m_vVelocity.z = out.z;
            m_vVelocity.x = out.x;
            m_vVelocity.y = out.y;
        } else {
            m_vVelocity = kZero;
        }
    } else if (result == 3) {
        m_vPosition.x = m_vPosition.x + slide.m_v3BouncingVector.x;
        m_vPosition.y = m_vPosition.y + slide.m_v3BouncingVector.y;
        m_vPosition.z = m_vPosition.z + slide.m_v3BouncingVector.z;
    }
    return 0;  // void in the original (State2 ignores it)
}

// 0x004ad1f8 CKHkS08TransportableKey_vfF4: not falling (state 2) and not carried.
uint8_t CKHkS08TransportableKey::VfF4(IKSerializable* /*carrier*/) {
    if (m_unk114 == 2) return 0;
    return m_pCarrier == nullptr ? 1 : 0;
}

// 0x004ad4b0 CKHkS08TransportableKey_vfFC: held by `carrier`: a carrier hero (0x91cc) with a receiver nearby
// (CKS08CarrierHero_HasNearbyReceiver_maybe 0x4b0a38), no ground, or a carrier of class 0x958c give 1; otherwise 1 when the
// ground is not a slide (property 0x200). Not held by it: 0.
uint8_t CKHkS08TransportableKey::VfFC(IKSerializable* carrier) {
    if (m_pCarrier != carrier) return 0;
    if ((carrier->IsKindOfClass(0x91cc) == 0 || static_cast<CKS08CarrierHero*>(carrier)->HasNearbyReceiver() == 0) &&
        m_GContactInOut.m_pGround != nullptr && carrier->IsKindOfClass(0x958c) == 0) {
        return static_cast<uint8_t>(((static_cast<ICollisionMesh*>(m_GContactInOut.m_pGround)->m_ui16PropertiesFlags >> 9) & 1u) ^ 1u);
    }
    return 1;
}

// 0x004afd08 CKHkS08TransportableKey_vfF0: a carrier picks it up when it is not falling and the carrier accepts it (the
// carrier's vt+0x58): the carrier kept (+0x48), told (vt+0x50), the machine switched to state 0 (carried; no clock).
uint8_t CKHkS08TransportableKey::VfF0(IKSerializable* carrier) {
    if (m_unk114 == 2) return 0;
    KBase910C* holder = static_cast<KBase910C*>(carrier);
    if (holder->CanPickUp(this) == 0) return 0;  // vt+0x58
    m_pCarrier = carrier;
    holder->StartCarrying(this);  // vt+0x50
    SwitchState(0, nullptr, 0);
    return 1;
}

// 0x004af750 CKHkS08TransportableKey_vf134: put on `receiver` (+0x30): the node's modelling position kept (+0x80), the
// machine switched to state 1 (no clock), +0x2d set, +0xe4 = FLT_MAX (0x00c4ace0).
void CKHkS08TransportableKey::Vf134(IKSerializable* receiver) {
    m_unk30 = receiver;
    const RwV3d& p = KeyNode(this)->m_pRwFrame->modelling.pos;
    m_vPosition.x = p.x;
    m_vPosition.y = p.y;
    m_vPosition.z = p.z;
    SwitchState(1, nullptr, 1);
    m_unk2D = 1;
    m_unkE4 = FLT_MAX;
}

// 0x004ad2c8 CKHkS08TransportableKey_OnActivate: the actor base's; no pending state, not ticking; the marker node (+0x38)
// out of its parent and under the grip hot spot (or the key's node without one).
void CKHkS08TransportableKey::VfA0() {
    CKHkActorBase::VfA0();  // 0x003f7338
    m_i32PendingState = -1;
    m_bInStateUpdate = 0;
    if (m_unk38 == nullptr) return;
    CSGLeaf* marker = static_cast<CSGLeaf*>(m_unk38);
    if (marker->m_pParent != nullptr) marker->m_pParent->RemoveChild(marker);  // vt+0x78
    CSGHotSpot* spot = Vf118();
    if (spot == nullptr) {
        static_cast<CSGBranch*>(m_pKGLObject)->AddChild(marker);  // vt+0x70
        return;
    }
    spot->AttachVolume(marker);  // 0x000ce2b8
}

// 0x004ad8f0 CKHkS08TransportableKey_OnDeactivate: the actor base's; a key that is not carried, not placed and not in
// the pool goes back to the pool (ReleaseObject), its node under sector 0's root; no pending state, not ticking.
void CKHkS08TransportableKey::VfA4() {
    CKHkActorBase::VfA4();  // 0x003f7370
    if (m_pCarrier == nullptr && m_unk24 == 0 && m_unk25 == 0) {
        static_cast<CKGrpTransportableObject*>(m_unk20)->ReleaseObject(this);  // 0x004a7ce0
        ReparentToBaseSectorRoot(KeyNode(this));
    }
    m_bInStateUpdate = 0;
    m_i32PendingState = -1;
}

// 0x004ace88 CKHkS08TransportableKey_Destroy
void CKHkS08TransportableKey::Destroy() {
    CKHkS08TransportableBase::Destroy();  // 0x004ac218
    RwMatrixDestroy_Thunk(m_unkEC);
    RwMatrixDestroy_Thunk(m_unk108);
}

// 0x004adb08 CKHkS08TransportableKey_Restart (vt+0x54): a key that is not held (+0x48), not placed (+0x24) and not in
// its pool (+0x25) goes back to its group's pool (ReleaseObject), its node under sector 0's root, its state machine
// left; then, always, +0xc0 = 0, +0xdc = -1, the bytes +0x2d and +0xe0 and the word +0x30 cleared.
void CKHkS08TransportableKey::Restart() {
    if (m_pCarrier == nullptr && m_unk24 == 0 && m_unk25 == 0) {
        static_cast<CKGrpTransportableObject*>(m_unk20)->ReleaseObject(this);  // 0x004a7ce0
        ReparentToBaseSectorRoot(KeyNode(this));
        LeaveKeyState(this);
    }
    m_pDynamicGround = nullptr;  // +0xc0
    m_i32PendingState = -1;      // +0xdc
    m_unk2D = 0;
    m_bInStateUpdate = 0;        // +0xe0
    m_unk30 = nullptr;
}

// 0x004af358 CKHkS08TransportableKey_Start
void CKHkS08TransportableKey::Start() {
    CKHkS08TransportableBase::Start();  // 0x004ac060: +0x25 = 1, +0x28 = 0, vt+0x144 with 0

    // The state engine: a table of three handlers at +0x118 (the PS3 descriptors of the key's State0 / State1 /
    // State2, TOC +0x63c4 / +0x63c0 / +0x63c8), which +0x110 points to; CallState maps them to the native handlers.
    m_unk118[0] = 0x00bc7420u;
    m_unk118[2] = 0x00bc74c0u;
    m_unk118[4] = 0x00bc7578u;
    m_unk118[3] = 0;
    m_unk118[1] = 0;
    m_unk118[5] = 0;
    m_unk115 = 3;
    m_unk114 = 0xff;
    m_pUnk110 = &m_unk118[0];
    m_pCarrier = nullptr;
    m_GContactInOut.m_eContactStatus = 3;
    m_GContactInOut.m_ui8SectorNumber = 0;
    m_GContactInOut.m_pGround = nullptr;
    m_GContactInOut.m_i32FaceIndex = -1;
    m_unk24 = 0;
    m_bUnkBD = 1;                 // the byte at +0xbd
    m_pDynamicGround = nullptr;   // +0xc0
    m_vProbePoint = kNoPoint;     // +0xc4..+0xcc: the vector 0xc50da0
    m_vUnkD0 = kZero;             // +0xd0..+0xd8: the zero vector 0xc50d64
    m_i32PendingState = -1;       // +0xdc
    m_unkE4 = 0.0f;               // +0xe4
    m_bInStateUpdate = 0;         // the byte at +0xe0
    m_vGroundPoint = kNoPoint;    // +0xfc..+0x104: the vector 0xc50da0
    m_bUnk10C = 0;                // the byte at +0x10c
    m_unk2D = 0;                  // the byte at +0x2d
    m_unk30 = nullptr;
    if (m_unk38 != nullptr) {
        // The node's geometries that are of render kind 2 (bits 8-9 of their properties) get the low six bits 0x2e.
        CNode* node = static_cast<CNode*>(m_unk38);
        for (CGeometry* geometry = static_cast<CGeometry*>(node->m_lGeometryList); geometry != nullptr;
             geometry = geometry->m_pNext) {
            if (((geometry->m_BitProperties >> 8) & 3u) == 2u) {
                geometry->m_BitProperties = (geometry->m_BitProperties & 0xffffffc0u) | 0x2eu;
            }
        }
        node->m_sgProperties = (node->m_sgProperties & 0xfffffffbu) | 4u;
    }
}

// 0x004aca38 CKHkS08TransportableKey_UpdateGroundAttachment_maybe. The ground under `point` (or, with the "no point"
// vector: the grip hot spot's world position (the node updated first), falling: the fall position (+ the grip's offset);
// no grip: the fall position / the node's modelling position), probed down by +0x78 plus this frame's fall when falling
// (masks {1, 0}). A new ground that moves (IsKindOf 0x4cc, CDynamicGround) gets the pose in its space (+0x108: the LTM
// times the ground's inverted world matrix); the ground kept in +0xc0, then vt+0x178.
void CKHkS08TransportableKey::UpdateGroundAttachment(IKTime* clock, const CVector3* point) {
    CGroundContactDatasIn in;
    in.m_fDeltaMax = 0.0f;  // TOC +0x6334
    float height = m_unk78;
    if (m_vVelocity.y < 0.0f) height = height - m_vVelocity.y * clock->m_afDeltaTime[0];
    in.m_fObjectHeight = height;
    in.m_MasksOfGrdForTest[0] = 1;
    in.m_MasksOfGrdForTest[1] = 0;
    CVector3 at;
    if (kNoPoint.x != point->x || point->y != kNoPoint.y || point->z != kNoPoint.z) {
        at = *point;
    } else if (Vf118() != nullptr) {
        if (m_unk114 == 2) {
            at = m_vPosition;
            const CSGHotSpot* spot = Vf118();
            at.x = at.x + spot->m_v3RelativePosition.x;
            at.y = at.y + spot->m_v3RelativePosition.y;
            at.z = at.z + spot->m_v3RelativePosition.z;
        } else {
            KeyNode(this)->ForceWorldMatrixUpdate();  // vt+0x50
            Vf118()->GetWorldPosition(&at);  // 0x000ce790
        }
    } else if (m_unk114 == 2) {
        at = m_vPosition;
    } else {
        const RwV3d& p = KeyNode(this)->m_pRwFrame->modelling.pos;
        at = {p.x, p.y, p.z};
    }
    static_cast<CKSrvCollision*>(g_pEngine->m_srvCollision)->GroundProbePoints(&in, &m_GContactInOut, &at.x, 1);
    IKSerializable* ground = m_GContactInOut.m_pGround;
    if (m_pDynamicGround == nullptr || ground != m_pDynamicGround) {
        if (ground != nullptr && ground->IsKindOfClass(0x4cc) != 0) {
            CMatrix34 inverse;
            Mat4_Invert(&inverse, static_cast<ICollisionMesh*>(ground)->GetWorldMatrix());  // vt+0x50
            Mat4_Multiply(m_unk108, AsMatrix(&KeyNode(this)->m_pRwFrame->ltm), &inverse);
        }
        ground = m_GContactInOut.m_pGround;
    }
    m_pDynamicGround = ground;
    Vf178();
}

// 0x004ad0b0 CKHkS08TransportableKey_State0_maybe (carried): entering clears +0x24 / +0xbc and the velocity; leaving clears
// the velocity.
uint8_t CKHkS08TransportableKey::State0(IKTime* /*clock*/, int32_t phase, uint8_t other) {
    if (phase == 1) {
        m_unk24 = 0;
        m_bLanded = 0;
        m_vVelocity = kZero;
        return other;
    }
    if (phase == 2) m_vVelocity = kZero;
    return other;
}

// 0x004ad6b8 CKHkS08TransportableKey_State1 (at rest). Enter: no velocity; on a moving ground (IsKindOf 0x4cc) the pose in
// its space (+0x108 = the LTM times the ground's inverted world matrix, vt+0x54). Leave: no velocity, +0x2d / +0x30
// cleared, the marker hidden, vt+0x144 with 0. Tick: not placed, with a marker: shown when vt+0x184.
uint8_t CKHkS08TransportableKey::State1(IKTime* /*clock*/, int32_t phase, uint8_t other) {
    if (phase == 1) {
        m_vVelocity = kZero;
        IKSerializable* ground = m_pDynamicGround;
        if (ground != nullptr && ground->IsKindOfClass(0x4cc) != 0) {
            Mat4_Multiply(m_unk108, AsMatrix(&KeyNode(this)->m_pRwFrame->ltm),
                          static_cast<ICollisionMesh*>(m_pDynamicGround)->GetInvertedWorldMatrix());  // vt+0x54
        }
        return other;
    }
    if (phase == 2) {
        m_vVelocity = kZero;
        m_unk2D = 0;
        m_unk30 = nullptr;
        if (m_unk38 != nullptr) {
            CSGLeaf* marker = static_cast<CSGLeaf*>(m_unk38);
            marker->m_sgProperties = (marker->m_sgProperties & 0xfffffffbu) | 4u;
        }
        SetFlag2C(0);  // vt+0x144
        return other;
    }
    if (phase == 0 && m_unk24 == 0 && m_unk38 != nullptr && Vf184() != 0) {
        static_cast<CSGLeaf*>(m_unk38)->m_sgProperties &= 0xfffffffbu;
    }
    return other;
}

// 0x004ae688 CKHkS08TransportableKey_State2 (falling). Enter: +0xe4 / +0xbc cleared, the node turned upright (up y, the
// forward from its LTM's at, at its LTM position) and the fall position taken from the grip (or the LTM). Leave: no velocity. Tick: the
// position advances by the velocity and the velocity by the gravity (fmadds), the ground probed, the fall's step
// (vt+0x160), the node moved there; a pending state (+0xdc >= 0) is returned (and cleared); once landed (+0xbc) on a ground
// that is not a slide the node sits on the ground point (less the grip's offset), on a moving ground the pose in its
// space; landed: state 1.
uint8_t CKHkS08TransportableKey::State2(IKTime* clock, int32_t phase, uint8_t other) {
    if (phase == 1) {
        m_unkE4 = 0.0f;
        m_bLanded = 0;
        KeyNode(this)->ForceWorldMatrixUpdate();  // vt+0x50
        CMatrix34 m;
        m.m_right = {1.0f, 0.0f, 0.0f};
        m.m_ui32Flags = 0x20003u;
        m.m_up = {0.0f, 1.0f, 0.0f};
        m.m_ui32pad1 = 0;
        m.m_at = {0.0f, 0.0f, 1.0f};
        m.m_ui32pad2 = 0;
        m.m_pos = {0.0f, 0.0f, 0.0f};
        m.m_ui32pad3 = 0;
        const RwV3d& at = KeyNode(this)->m_pRwFrame->ltm.at;
        const CVector3 forward = {at.x, at.y, at.z};
        Mat4_BuildFromUpAndForward(&m, &kAxisY, &forward);
        // 0x004ae934..0x004ae95c: the position is the node's LTM position (the upright pose keeps the node where it is).
        const RwV3d& pos = KeyNode(this)->m_pRwFrame->ltm.pos;
        m.m_pos.z = pos.z;
        m.m_pos.x = pos.x;
        m.m_pos.y = pos.y;
        m.m_ui32Flags &= 0xfffdffffu;
        KeyNode(this)->SetLocalMatrix(AsRw(&m));
        if (Vf118() == nullptr) {
            const RwV3d& p = KeyNode(this)->m_pRwFrame->ltm.pos;
            m_vPosition = {p.x, p.y, p.z};
        } else {
            Vf118()->GetWorldPosition(&m_vPosition);
        }
        return other;
    }
    if (phase == 2) {
        m_vVelocity = kZero;
        return other;
    }
    if (phase != 0) return other;
    const float dt = clock->m_afDeltaTime[0];
    const RwV3d& p = KeyNode(this)->m_pRwFrame->modelling.pos;
    const float pz = p.z;
    const float py = p.y;
    m_vPosition.x = ppc::fmadds(dt, m_vVelocity.x, p.x);
    m_vPosition.z = ppc::fmadds(dt, m_vVelocity.z, pz);
    m_vPosition.y = ppc::fmadds(dt, m_vVelocity.y, py);
    const float dt2 = clock->m_afDeltaTime[0];
    m_vVelocity.x = ppc::fmadds(dt2, m_unk98.x, m_vVelocity.x);
    m_vVelocity.z = ppc::fmadds(dt2, m_unk98.z, m_vVelocity.z);
    m_vVelocity.y = ppc::fmadds(dt2, m_unk98.y, m_vVelocity.y);
    UpdateGroundAttachment(clock, &kNoPoint);
    Vf160(clock);  // vt+0x160
    SetNodePosition(KeyNode(this), m_vPosition.x, m_vPosition.y, m_vPosition.z);
    const int32_t pending = m_i32PendingState;
    if (pending >= 0) {
        m_i32PendingState = -1;
        return static_cast<uint8_t>(pending);
    }
    if (m_bLanded == 0) return other;
    ICollisionMesh* ground = static_cast<ICollisionMesh*>(m_pDynamicGround);
    if (m_GContactInOut.m_eContactStatus != 3 && ground != nullptr && (ground->m_ui16PropertiesFlags & 0x200u) == 0) {
        CVector3 point;
        GroundContact_GetWorldPoint(&m_GContactInOut, &point);
        const CSGHotSpot* spot = Vf118();
        SetNodePosition(KeyNode(this), point.x - spot->m_v3RelativePosition.x, point.y - spot->m_v3RelativePosition.y,
                        point.z - spot->m_v3RelativePosition.z);
        if (m_pDynamicGround->IsKindOfClass(0x4cc) != 0) {
            KeyNode(this)->ForceWorldMatrixUpdate();  // vt+0x50
            CMatrix34 inverse;
            Mat4_Invert(&inverse, static_cast<ICollisionMesh*>(m_pDynamicGround)->GetWorldMatrix());  // vt+0x50
            Mat4_Multiply(m_unk108, AsMatrix(&KeyNode(this)->m_pRwFrame->ltm), &inverse);
        }
    }
    return 1;
}

// 0x004aff00 CKHkS08TransportableKey_Update. A ground in a sector that went inactive is forgotten (and nothing else
// happens). Carried: no probe point. At rest (not placed, not on a receiver): the pose is the LTM (on a moving ground:
// +0x108 through the ground's world matrix), slid along the walls from the grip's world position (cylinder +0x7c / +0x78)
// unless marked (+0x2c); the ground probed under the pose's grip; at rest on a ground with the grip more than 0.1 above
// the ground point: the pose applied and the machine switched to falling (2); a power bucket (IsKindOf 0x30c2) at rest on
// a slide or nothing goes back to the pool. Then the machine ticks (+0xe0 set meanwhile); still at rest: the pose applied.
void CKHkS08TransportableKey::Update(IKTime* clock) {
    // 0x004abfc0 CKHkS08TransportableBase_3002_maybe_Update (empty).
    if (m_pDynamicGround != nullptr && !GroundSectorActive(m_pDynamicGround)) {
        m_pDynamicGround = nullptr;
        return;
    }
    if (m_unk114 == 0) m_vProbePoint = kNoPoint;
    bool applyPose = false;
    CMatrix34 pose;
    const uint8_t state = m_unk114;
    if (state != 2 && state != 0xff && m_unk24 == 0 && m_unk30 == nullptr) {
        pose = *AsMatrix(&KeyNode(this)->m_pRwFrame->ltm);
        if (m_unk114 == 1) {
            IKSerializable* ground = m_pDynamicGround;
            if (ground != nullptr && ground->IsKindOfClass(0x4cc) != 0) {
                pose = *m_unk108;
                Mat4_TransformPostConcat(&pose, static_cast<ICollisionMesh*>(m_pDynamicGround)->GetWorldMatrix());  // vt+0x50
            }
            if (m_unk2C == 0) {
                CVector3 grip;
                Vf118()->GetWorldPosition(&grip);  // 0x000ce790
                const CSGHotSpot* spot = Vf118();
                CLine line;
                line.m_start = grip;
                line.m_VectDir.z = (pose.m_pos.z + spot->m_v3RelativePosition.z) - grip.z;
                line.m_VectDir.x = (pose.m_pos.x + spot->m_v3RelativePosition.x) - grip.x;
                line.m_VectDir.y = (pose.m_pos.y + spot->m_v3RelativePosition.y) - grip.y;
                CSlideGroundEdgeDatasOut out;
                const uint8_t result = static_cast<CKSrvCollision*>(g_pEngine->m_srvCollision)
                                           ->ResolveSweptCylinderWalls(&line, m_unk7c, m_unk78, &out, nullptr, nullptr, 1);
                if (static_cast<uint32_t>(result) - 2u <= 1u) {
                    pose.m_pos.x = out.m_v3BouncingVector.x + pose.m_pos.x;
                    pose.m_pos.y = out.m_v3BouncingVector.y + pose.m_pos.y;
                    pose.m_pos.z = out.m_v3BouncingVector.z + pose.m_pos.z;
                    pose.m_ui32Flags &= 0xfffdffffu;
                }
            }
        }
        const CSGHotSpot* spot = Vf118();
        const CVector3 probe = {pose.m_pos.x + spot->m_v3RelativePosition.x, pose.m_pos.y + spot->m_v3RelativePosition.y,
                                pose.m_pos.z + spot->m_v3RelativePosition.z};
        UpdateGroundAttachment(clock, &probe);
        applyPose = true;
        if (m_unk114 == 1 && m_GContactInOut.m_eContactStatus != 3 && m_pDynamicGround != nullptr) {
            CVector3 grip;
            Vf118()->GetWorldPosition(&grip);
            CVector3 point;
            GroundContact_GetWorldPoint(&m_GContactInOut, &point);  // only the heights are compared
            if (!(grip.y <= point.y + 0.1f)) {  // TOC +0x63cc
                KeyNode(this)->SetLocalMatrix(AsRw(&pose));
                SwitchState(2, clock, 2);
                applyPose = false;
            }
        }
        if (IsKindOfClass(0x30c2) != 0 && m_unk114 == 1) {
            const ICollisionMesh* ground = static_cast<const ICollisionMesh*>(m_pDynamicGround);
            if ((ground != nullptr && (ground->m_ui16PropertiesFlags & 0x200u) != 0) ||
                m_GContactInOut.m_eContactStatus == 3) {
                Vf108();
                static_cast<CKGrpTransportableObject*>(m_unk20)->ReleaseObject(this);  // 0x004a7ce0
            }
        }
    }
    m_bInStateUpdate = 1;
    RunStateMachine(clock);
    m_bInStateUpdate = 0;
    if (m_unk114 == 1 && applyPose) KeyNode(this)->SetLocalMatrix(AsRw(&pose));
}
