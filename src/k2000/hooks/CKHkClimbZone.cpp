// CKHkClimbZone.cpp - reconstructed original translation unit 0x456b78-0x459be0 (GAME_TOC1, main_toc1), 41 functions, 38 live.
// Primary class: CKHkClimbZone  key 0x1602  category Hook  size 0xc4  vtable 0xb27120
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x456b78  CKHkClimbZone_Delete
//   [x] 0x456bc8  CKHkClimbZone_GetLinkedObjectFlagC23_maybe
//   [x] 0x456bf0  CKHkClimbZone_GetGroundByIndex_maybe
//   [ ] 0x456c38  RegisterCKHkClimbZoneClass
//   [ ] 0x456cb0  _GLOBAL__I_456cb0
//   [x] 0x456cc0  CKHkClimbZone_RaycastAttachPoint_maybe
//   [x] 0x457180  CKHkClimbZone_RemoveClimber_maybe
//   [x] 0x457288  CKHkClimbZone_GetInfo  (with 0x9c3f48 CKHkClimbZone_GetTriggerProp96)
//   [x] 0x457368  CKHkClimbZone_Resume
//   [x] 0x457390  CKHkClimbZone_Pause
//   [x] 0x4573b8  CKHkClimbZone_Stop
//   [x] 0x4573e0  CKHkClimbZone_Start
//   [x] 0x457438  CKHkClimbZone_PostLoad
//   [ ] 0x4574a0  CKHkClimbZone_Save
//   [x] 0x4574c8  CKHkClimbZone_RecursiveRegistration  (CKHkActorBase's 0x3f6ee8, then 1: inherited)
//   [x] 0x4574f0  CKHkClimbZone_Destroy
//   [x] 0x457578  CKHkClimbZone_Construct  [dead]
//   [x] 0x4575d8  CKHkClimbZone_DeleteArray
//   [x] 0x457678  CKHkClimbZone_OnDeactivate
//   [x] 0x457740  CKHkClimbZone_IsAboveBottom_maybe
//   [x] 0x457768  CKHkClimbZone_IsBelowTop_maybe
//   [x] 0x457798  CKHkClimbZone_BaseDestructor  (the destructor 0x458548, CKHkClimbZone.h)
//   [x] 0x457808  CKHkClimbZone_SetDefaultState
//   [x] 0x4578b8  CKHkClimbZone_MessageProc
//   [x] 0x4579d0  CKHkClimbZone_vfC8
//   [ ] 0x457a78  CKHkClimbZone_Construct_2  [dead]
//   [x] 0x457ad8  CKHkClimbZone_ClampMoveToExtent_maybe
//   [x] 0x457c50  CKHkClimbZone_SetCollisionEnabled_maybe
//   [x] 0x457d68  CKHkClimbZone_Update
//   [ ] 0x458400  CKHkClimbZone_GetPerpendicularDistance_maybe  [dead]
//   [x] 0x4584d0  CKHkClimbZone_DeletingDestructor  (C++ deleting destructor)
//   [x] 0x458548  CKHkClimbZone_Destructor  (header)
//   [x] 0x4585b8  CKHkClimbZone_CreateArray
//   [x] 0x458698  CKHkClimbZone_Create
//   [x] 0x458708  CKHkClimbZone_ResolveClimberOverlap_maybe
//   [x] 0x458a88  CKHkClimbZone_GetAttachMatrix_maybe
//   [x] 0x458e98  CKHkClimbZone_AddOrUpdateClimber_maybe
//   [x] 0x4591e0  CKHkClimbZone_AttachClimberIfValid_maybe
//   [x] 0x459290  CKHkClimbZone_OnActivate
//   [x] 0x459520  CKHkClimbZone_Restart
//   [x] 0x4595d0  CKHkClimbZone_Load
//
//   [x] 0x9c3ee0  CKHkClimbZone_IsKindOfClass  [inline, in the header]
//   [x] 0x9c3f38  CKHkClimbZone_GetClassType  [inline, DOTD_CLASS_KEY]
//   [x] 0x9c3f40  CKHkClimbZone_GetClassID  [inline, DOTD_CLASS_KEY]
//   [x] 0x9c3f48  CKHkClimbZone_GetTriggerProp96  [inline]  (GetInfo's accessor)
#include <cmath>
#include <cstring>

#include "k2000/hooks/CKHkClimbZone.h"
#include "k2000/hooks/CKHkCrumblyZone.h"

#include "k2000/core/IKInfo.h"
#include "k2000/io/IKFile.h"
#include "k2000/memory/Mem.h"
#include "Renderware/rwcore/RwCamera.h"
#include "crt/ppc_ops.h"
#include "k2000/core/Stub.h"
#include "k2000/misc/Engine.h"
#include "k2000/misc/Mat4.h"
#include "k2000/render/CRenderer.h"
#include "k2000/scenegraph/CSGBranch.h"
#include "k2000/scenegraph/CSGMovable.h"
#include "k2000/scenegraph/IKBoundingBox.h"
#include "k2000/services/CKSrvCollision.h"
#include "k2000/services/CollisionDatas.h"
#include "k2000/services/ICollisionMesh.h"
#include "k2000/system/IKTime.h"

namespace {
// 0x00c50d64 (TOC1 +0x5624): the zero vector.
constexpr CVector3 kZero{0.0f, 0.0f, 0.0f};
// 0x00c50d40 (TOC1 +0x560c): the shared Y axis (the probe axis of kinds 0 / 1 and the at axis of a wall's matrix).
constexpr CVector3 kAxisY{0.0f, 1.0f, 0.0f};

CKSrvCollision* Collision() { return static_cast<CKSrvCollision*>(g_pEngine->m_srvCollision); }
RwFrame* FrameOf(IKSerializable* node) { return static_cast<CSGMovable*>(node)->m_pRwFrame; }
}  // namespace

// DOTD: the original reads the frames' LTM words as the scene's last sync left them; natively the LTM is made current on
// read (RwFrameGetLTM recomputes it from the modelling matrices: the zones' frames do not move).
const CMatrix34& CKHkClimbZone::NodeLtm() const {
    return *reinterpret_cast<const CMatrix34*>(FrameLtm(FrameOf(m_pKGLObject)));
}
const CMatrix34& CKHkClimbZone::NodeModelling() const {
    return *reinterpret_cast<const CMatrix34*>(&FrameOf(m_pKGLObject)->modelling);
}
const CMatrix34& CKHkClimbZone::BoxLtm() const { return *reinterpret_cast<const CMatrix34*>(FrameLtm(FrameOf(m_pUnk20))); }

// PORT: the original's climber key is the hero's 32-bit address; x64 folds the 64-bit address into the record's word.
int32_t CKHkClimbZone::ClimberKey(const void* climber) {
    const uint64_t address = reinterpret_cast<uintptr_t>(climber);
    return static_cast<int32_t>(static_cast<uint32_t>(address) ^ static_cast<uint32_t>(address >> 32));
}

// 0x004595d0 CKHkClimbZone_Load
int32_t CKHkClimbZone::Load(IKFile* file, int32_t type) {
    CKHkActorBase::Load(file, type);
    if (type != K_LEVEL_PLATEFORMS) return 1;
    IKFile_ReadRef(file, &m_pUnk20);
    ReadF32LE(file, &m_fUnk30);
    ReadU8(file, &m_unk34);
    for (float& f : m_afUnk24) ReadF32LE(file, &f);
    IKFile_ReadRef(file, &m_pUnk38);
    IKFile_ReadRef(file, &m_pUnk3C);
    ReadF32LE(file, &m_fUnk40);
    IKFile_ReadRef(file, &m_pUnk44);
    ReadF32LE(file, &m_fUnk48);
    IKFile_ReadRef(file, &m_pUnk4C);
    IKFile_ReadRef(file, &m_pUnk50);
    IKFile_ReadRef(file, &m_pUnk54);
    ReadF32LE(file, &m_fUnk58);
    ReadF32LE(file, &m_fUnk5C);
    ReadU8(file, &m_ui8NbUnk60);
    m_apUnk60 = static_cast<IKSerializable**>(
        Mem_AllocAligned16(m_ui8NbUnk60 * static_cast<uint32_t>(sizeof(IKSerializable*))));
    IKFile_ReadObjectRefArray(file, m_apUnk60, m_ui8NbUnk60);
    m_tsUnk68.Load(file, K_LEVEL_PLATEFORMS);
    m_tsUnk70.Load(file, K_LEVEL_PLATEFORMS);
    return 1;
}

// 0x00457438 CKHkClimbZone_PostLoad: CKHkActorBase's, then (level type) the climber list gets its 16-byte block.
int32_t CKHkClimbZone::PostLoad(int32_t type) {
    CKHkActorBase::PostLoad(type);
    if (type == K_LEVEL_PLATEFORMS) {
        m_vUnkB4.m_ui32NbElt = 1;
        m_vUnkB4.m_pBlock = static_cast<Climber*>(Mem_AllocAligned16(0x10));
    }
    return 1;
}

// 0x004574f0 CKHkClimbZone_Destroy: CKHkActorBase's (vt+0xc0, empty for the zone), the climber block and the +0x60
// array freed.
int32_t CKHkClimbZone::GetInfo(IKInfo* info, int32_t request) {
    const int32_t base = CKHkActorBase::GetInfo(info, request);  // KStub_Return1_3f7140
    int32_t own = 1;
    if (request == kGetInfoValueAccessor && info->m_ui32Id == 0x96) {
        own = AnswerInfo(info, [](IKSerializable* o, uint32_t) {
            return (static_cast<CKHkClimbZone*>(o)->m_bitArray >> 16) & 1u;  // lhz +0x0c (big-endian high half), bit 0
        }, 0);
    }
    if (base == 2 || own == 2) return 2;
    if (base == 0) return 0;
    return own;
}

void CKHkClimbZone::Destroy() {
    if (m_vUnkB4.m_pBlock != nullptr) {
        Mem_FreeAligned16(m_vUnkB4.m_pBlock);
        m_vUnkB4.m_pBlock = nullptr;
    }
    m_vUnkB4.m_ui32NbUsedElt = 0;
    m_vUnkB4.m_pBlock = nullptr;
    if (m_apUnk60 != nullptr) Mem_FreeAligned16(m_apUnk60);
}

// 0x004573e0 CKHkClimbZone_Start: CKHkActorBase_d82_maybe_ResetRuntime (empty), then vt+0x54.
void CKHkClimbZone::Start() {
    CKHkActorBase::Start();
    Restart();
}

// 0x00457808 CKHkClimbZone_SetDefaultState: state 0 always, state 1 only with bit 6. Bit 16 = bit 5, bit 18 =
// not bit 12.
void CKHkClimbZone::SetDefaultState(int32_t flag) {
    CKHkActorBase::SetDefaultState(flag);
    const uint32_t f = m_bitArray;
    if (flag != 0 && (f & 0x40) == 0) return;
    m_bitArray = (f & ~0x50000u) | (((f >> 5) & 1) << 16) | ((((f >> 12) & 1) ^ 1u) << 18);
}

// 0x004578b8 CKHkClimbZone_MessageProc: CKHkActorBase's (KBaseD82: the messages 0x908..0x90f), then 0x996 sets bit 18
// and 0x997 clears it (both answer 0, any other message 1); the answers are merged (3 wins, then 2, then 0 when the
// base answered 0).
int32_t CKHkClimbZone::MessageProc(uint16_t message, void* data) {
    const int32_t base = CKHkActorBase::MessageProc(message, data);  // 0x003f7148
    int32_t own;
    if (message == 0x996) {
        own = 0;
        m_bitArray = (m_bitArray & 0xfffbffffu) | 0x40000u;
    } else {
        own = 1;
        if (message == 0x997) {
            own = 0;
            m_bitArray &= 0xfffbffffu;
        }
    }
    if (base == 3 || own == 3) return 3;
    if (base == 2 || own == 2) return 2;
    if (base != 0) return own;
    return 0;
}

// 0x004579d0 CKHkClimbZone_vfC8: the preset `state` (0 / 1) takes bit 16 from bit 7 / bit 8 and bit 18 from not bit 13
// / not bit 14.
void CKHkClimbZone::ApplyStatePreset(int32_t state) {
    const uint32_t on = state == 0 ? (m_bitArray & 0x80u) : (m_bitArray & 0x100u);
    m_bitArray = on == 0 ? (m_bitArray & 0xfffeffffu) : ((m_bitArray & 0xfffeffffu) | 0x10000u);
    const uint32_t off = state == 0 ? (m_bitArray & 0x2000u) : (m_bitArray & 0x4000u);
    if (off == 0) {
        m_bitArray = (m_bitArray & 0xfffbffffu) | 0x40000u;
        return;
    }
    m_bitArray &= 0xfffbffffu;
}

// 0x00457c50 CKHkClimbZone_SetCollisionEnabled_maybe (vt+0xcc): bit 16 = `enabled`; on, the box joins the collision
// service unless it is in (its infos bit 0) or the zone keeps it out (bit 9); off, it leaves and the climbers are
// forgotten.
void CKHkClimbZone::SetEnabled(int32_t enabled) {
    IKBoundingVolume* box = static_cast<IKBoundingVolume*>(m_pUnk20);
    if (enabled != 0) {
        if ((box->m_ba8Infos & 1) == 0 && (m_bitArray & 0x200u) == 0) Collision()->AddVolume(box);  // 0x00192b80
        m_bitArray = (m_bitArray & 0xfffeffffu) | (static_cast<uint32_t>(enabled) << 16);
        return;
    }
    if ((box->m_ba8Infos & 1) != 0) Collision()->RemoveVolume(box);  // 0x00192bc0
    m_vUnkB4.m_ui32NbUsedElt = 0;
    m_bitArray &= 0xfffeffffu;
}

// 0x00459290 CKHkClimbZone_OnActivate (vt+0xa0, the zone's sector became active): unless bit 9 keeps the box out, the
// box (its half sizes and radius from +0x24) moves under the zone's node and the attach probe of the node's position is
// cached; then the pushes are cleared, bit 17 tells a crumbly zone (+0x54), the zone switches itself to its bit 16
// (vt+0xcc) and starts with no climber active.
void CKHkClimbZone::VfA0() {
    CKHkActorBase::VfA0();  // 0x003f7338 the active actor list
    if ((m_bitArray & 0x200u) == 0) {
        m_bitArray &= 0xffefffffu;
        IKBoundingBox* box = static_cast<IKBoundingBox*>(m_pUnk20);
        if (box->m_pParent != nullptr) box->m_pParent->RemoveChild(box);  // vt+0x78
        box->m_Extent.x = m_afUnk24[0];
        box->m_Extent.z = m_afUnk24[2];
        box->m_Extent.y = m_afUnk24[1];
        const float sum =
            ppc::fmadds(m_afUnk24[2], m_afUnk24[2], ppc::fmadds(m_afUnk24[0], m_afUnk24[0], m_afUnk24[1] * m_afUnk24[1]));
        box->m_fRadius = std::sqrt(sum);  // Math_Sqrtf 0x10690
        static_cast<CSGBranch*>(m_pKGLObject)->AddChild(box);  // vt+0x70
        const CMatrix34& ltm = NodeLtm();
        m_vUnk78 = ltm.m_pos;
        CVector3 point = ltm.m_pos;
        CVector3 hit{};  // BUG(original): the stack words are left as they were without a hit.
        CMatrix34 matrix{};
        RaycastAttachPoint(&hit, &point, &matrix);
        m_vUnk84 = hit;
        m_vUnk90 = matrix.m_up;
    }
    m_vUnk9C = kZero;
    m_vUnkA8 = kZero;
    const uint32_t crumbly = m_pUnk54 != nullptr ? 0x20000u : 0u;
    m_bitArray = (m_bitArray & 0xfffdffffu) | crumbly;
    SetEnabled(static_cast<int32_t>((m_bitArray >> 16) & 1u));  // vt+0xcc, the halfword's bit 0
    m_bitArray &= 0xfff7ffffu;
    AddOrUpdateClimber(0.0f, 0, &kZero, 0);
    m_fUnkC0 = 0.0f;
}

// 0x00457678 CKHkClimbZone_OnDeactivate (vt+0xa4): the box leaves the collision service and the zone's node for the
// engine's dynamic scene root.
void CKHkClimbZone::VfA4() {
    CKHkActorBase::VfA4();  // 0x003f7370
    IKBoundingBox* box = static_cast<IKBoundingBox*>(m_pUnk20);
    Collision()->RemoveVolume(box);  // 0x00192bc0
    if (box->m_pParent != nullptr) box->m_pParent->RemoveChild(box);  // vt+0x78
    static_cast<CSGBranch*>(g_pEngine->m_dynamicSceneRoot)->AddChild(box);  // engine +0x14, vt+0x70
}

// 0x00456bc8 CKHkClimbZone_GetLinkedObjectFlagC23_maybe: bit 23 of +0x38's flags (+0xc), 0 without +0x38.
uint8_t CKHkClimbZone::GetLinkedObjectFlagC23() {
    if (m_pUnk38 == nullptr) return 0;
    // STUB(C2.8): +0x38 is a level mechanism's body (no LVL010 climb zone has one); its class is not identified.
    DOTD_STUB_ONCE("CKHkClimbZone_GetLinkedObjectFlagC23_maybe 0x456bc8: the zone's +0x38 (C2.8)");
    return 0;
}

// 0x00456bf0 CKHkClimbZone_GetGroundByIndex_maybe: +0x38's ground `index` (its +0x24 array of +0x20 entries), or null.
IKSerializable* CKHkClimbZone::GetGroundByIndex(uint8_t /*index*/) {
    if (m_pUnk38 == nullptr) return nullptr;
    // STUB(C2.8): as GetLinkedObjectFlagC23.
    DOTD_STUB_ONCE("CKHkClimbZone_GetGroundByIndex_maybe 0x456bf0: the zone's +0x38 (C2.8)");
    return nullptr;
}

// 0x00456cc0 CKHkClimbZone_RaycastAttachPoint_maybe. Kind 2: the node's at axis (LTM), the walls (RaycastWalls, no
// height, no culling); the matrix's basis from the Y axis (at) and the wall's normal (up). Kinds 0 / 1: the Y axis
// (negated for kind 1), the ground meshes (RaycastMeshes); the matrix's up is the hit face's normal (negated for kind 0)
// and its forward the node's at axis. The ray starts 0.5 back from the point and is 5 long.
CVector3* CKHkClimbZone::RaycastAttachPoint(CVector3* out, CVector3* point, CMatrix34* matrix) {
    CKSrvCollision* collision = Collision();
    if (m_unk34 == 2) {
        const CVector3& at = NodeLtm().m_at;
        const float dz = at.z * 5.0f;  // TOC1 +0x5608
        const float dx = at.x * 5.0f;
        const float dy = at.y * 5.0f;
        point->z = ppc::fmadds(at.z, -0.5f, point->z);  // TOC1 +0x5604
        point->x = ppc::fmadds(at.x, -0.5f, point->x);
        point->y = ppc::fmadds(at.y, -0.5f, point->y);
        CLine line{*point, {dx, dy, dz}};
        CGroundEdgeDatasOut edge{};
        if (collision->RaycastWalls(&line, 0.0f, &edge, 0, nullptr, 1) == 0) return out;  // 0x00198438
        const float t = edge.m_ftLine;
        out->z = ppc::fmadds(dz, t, point->z);
        out->x = ppc::fmadds(dx, t, point->x);
        out->y = ppc::fmadds(dy, t, point->y);
        if (matrix != nullptr) {
            matrix->m_pos = *out;
            matrix->m_ui32Flags &= 0xfffdffffu;
            Mat4_SetBasisFromAtUp(matrix, &kAxisY, &edge.m_EdgeNormal);  // 0x0023fd30
        }
    } else {
        float ax = kAxisY.x, ay = kAxisY.y, az = kAxisY.z;
        if (m_unk34 != 0) {
            ax = -ax;
            ay = -ay;
            az = -az;
        }
        const float dz = az * 5.0f;
        const float dx = ax * 5.0f;
        const float dy = ay * 5.0f;
        point->x = ppc::fmadds(ax, -0.5f, point->x);
        point->z = ppc::fmadds(az, -0.5f, point->z);
        point->y = ppc::fmadds(ay, -0.5f, point->y);
        CLine line{*point, {dx, dy, dz}};
        CLineCollisionDatas hit{};
        hit.m_ftOnLine = 3.40282347e+38f;  // FLT_MAX (0x00c4ace0)
        hit.m_i32FaceIndex = -1;
        hit.m_pCollisionMesh = nullptr;
        hit.m_ui8SectorNumber = 0;
        if (collision->RaycastMeshes(&line, &hit, 1, 0, nullptr) == 0) return out;  // 0x00197af8
        const float t = hit.m_ftOnLine;
        out->z = ppc::fmadds(dz, t, point->z);
        out->x = ppc::fmadds(dx, t, point->x);
        out->y = ppc::fmadds(dy, t, point->y);
        if (matrix != nullptr) {
            const ICollisionMesh* mesh = hit.m_pCollisionMesh;
            if (hit.m_i32FaceIndex == -1 || mesh == nullptr || mesh->m_ui16NbTriangle <= hit.m_i32FaceIndex) {
                // BUG(original): the face is then read from address 0 (and the mesh's vertices from a null mesh).
                DOTD_STUB_ONCE("CKHkClimbZone_RaycastAttachPoint_maybe: a hit without a face (BUG(original): null reads)");
                m_bitArray = (m_bitArray & 0xffefffffu) | 0x100000u;
                return out;
            }
            const ICollisionMesh::CCollisionTriangle& face = mesh->m_aTriangle[hit.m_i32FaceIndex];
            const CVector3& v0 = mesh->m_aVertex[face.m_aui16Index[0]];
            const CVector3& v1 = mesh->m_aVertex[face.m_aui16Index[1]];
            const CVector3& v2 = mesh->m_aVertex[face.m_aui16Index[2]];
            const float e1x = v1.x - v0.x;
            const float e2z = v2.z - v0.z;
            const float e1z = v1.z - v0.z;
            const float e2x = v2.x - v0.x;
            const float e2y = v2.y - v0.y;
            const float e1y = v1.y - v0.y;
            CVector3 normal;
            normal.y = ppc::fmsubs(e1z, e2x, e1x * e2z);
            normal.x = ppc::fmsubs(e1y, e2z, e1z * e2y);
            normal.z = ppc::fmsubs(e1x, e2y, e1y * e2x);
            const float length = std::sqrt(ppc::fmadds(normal.z, normal.z, ppc::fmadds(normal.x, normal.x, normal.y * normal.y)));
            if (length != 0.0f) {
                const float inverse = 1.0f / length;
                normal.z = normal.z * inverse;
                normal.x = normal.x * inverse;
                normal.y = normal.y * inverse;
            }
            if (m_unk34 == 0) {
                normal.x = -normal.x;
                normal.y = -normal.y;
                normal.z = -normal.z;
            }
            matrix->m_pos = *out;
            matrix->m_ui32Flags &= 0xfffdffffu;
            Mat4_BuildFromUpAndForward(matrix, &normal, &NodeLtm().m_at);  // 0x0023ff80
        }
    }
    m_bitArray = (m_bitArray & 0xffefffffu) | 0x100000u;
    return out;
}

// 0x00457180 CKHkClimbZone_RemoveClimber_maybe: the climber's record goes (the last one takes its place); an active
// zone (bit 15) becomes inactive and fires its +0x70 trigger.
void CKHkClimbZone::RemoveClimber(int32_t climberKey) {
    uint32_t count = m_vUnkB4.m_ui32NbUsedElt;
    if (count != 0) {
        Climber* block = m_vUnkB4.m_pBlock;
        uint32_t index = 0;
        bool found = block[0].m_key == climberKey;
        if (!found) {
            for (index = 1; index < count; ++index) {
                if (block[index].m_key == climberKey) {
                    found = true;
                    break;
                }
            }
        }
        if (found) {
            count -= 1;
            m_vUnkB4.m_ui32NbUsedElt = count;
            if (index != count) block[index] = block[count];
        }
    }
    if ((m_bitArray & 0x8000u) != 0) {
        m_bitArray &= 0xffff7fffu;
        QueueTriggerSignals(&m_tsUnk70);  // 0x00236338
    }
}

// 0x00457740 CKHkClimbZone_IsAboveBottom_maybe: the position's y above the node's (LTM).
uint8_t CKHkClimbZone::IsAboveBottom(const CVector3* position) { return NodeLtm().m_pos.y < position->y ? 1 : 0; }

// 0x00457768 CKHkClimbZone_IsBelowTop_maybe: the position's y below the node's plus the extent.
uint8_t CKHkClimbZone::IsBelowTop(const CVector3* position) {
    return position->y < NodeLtm().m_pos.y + m_fUnk30 ? 1 : 0;
}

// 0x00457ad8 CKHkClimbZone_ClampMoveToExtent_maybe. No extent: the zero vector. Kind 2: the move's y kept within
// [position - bottom, bottom + extent - position]... as the original computes it (y only). Otherwise the move's part
// along the node's at axis, clamped the same way.
CVector3 CKHkClimbZone::ClampMoveToExtent(const CVector3* position, const CVector3* move) {
    const float range = m_fUnk30;
    if (range == 0.0f) return kZero;
    const CMatrix34& ltm = NodeLtm();
    const float nx = ltm.m_pos.x, ny = ltm.m_pos.y, nz = ltm.m_pos.z;
    if (m_unk34 == 2) {
        const float my = move->y;
        float y = position->y - ny;
        if (my < 0.0f) {
            if (my > y) y = my;
        } else {
            y = range + y;
            if (!(my > y)) y = my;
        }
        return {kZero.x, y, kZero.z};
    }
    const CVector3& at = ltm.m_at;
    float along = ppc::fmadds(move->z, at.z, ppc::fmadds(move->x, at.x, move->y * at.y));
    const float offset = ppc::fmadds(nz - position->z, at.z, ppc::fmadds(nx - position->x, at.x, (ny - position->y) * at.y));
    if (along < 0.0f) {
        if (!(offset < 0.0f)) return {kZero.x, kZero.y, kZero.z};
        if (!(along > offset)) along = offset;
        return {along * at.x, along * at.y, along * at.z};
    }
    const float top = range + offset;
    if (top <= 0.0f) return {kZero.x, kZero.y, kZero.z};
    const float length = along <= top ? along : top;
    return {length * at.x, length * at.y, length * at.z};
}

// 0x00458708 CKHkClimbZone_ResolveClimberOverlap_maybe: the other climbers' records, last first; each whose range holds
// the position pushes it to the near end of the range (to the bottom side when its distance is at least the
// position's), unless the range touches that end of the zone (0: no place).
uint8_t CKHkClimbZone::ResolveClimberOverlap(const CVector3* position, CVector3* out, int32_t climberKey) {
    *out = *position;
    uint32_t remaining = m_vUnkB4.m_ui32NbUsedElt;
    while (remaining != 0) {
        remaining -= 1;
        const Climber& record = m_vUnkB4.m_pBlock[remaining];
        if (climberKey == 0 || record.m_key == climberKey) continue;
        float d;
        if (m_unk34 == 2) {
            d = position->y - NodeLtm().m_pos.y;
        } else {
            const CMatrix34& ltm = NodeLtm();
            const float dy = position->y - ltm.m_pos.y;
            const float dx = position->x - ltm.m_pos.x;
            const float dz = position->z - ltm.m_pos.z;
            float along = dy * ltm.m_up.y;
            along = ppc::fmadds(dx, ltm.m_up.x, along);
            along = ppc::fmadds(dz, ltm.m_up.z, along);
            const float ey = dy - along * ltm.m_up.y;
            const float ex = dx - along * ltm.m_up.x;
            const float ez = dz - along * ltm.m_up.z;
            d = std::sqrt(ppc::fmadds(ez, ez, ppc::fmadds(ex, ex, ey * ey)));  // Math_Sqrtf
        }
        const float hi = record.m_fHi;
        const bool atTop = hi >= m_fUnk30;
        if (atTop && record.m_fLo <= 0.0f) return 0;
        if (!(d <= hi) || !(d >= record.m_fLo)) {
            *out = *position;
            continue;
        }
        if (record.m_fDist >= d) {
            const float lo = record.m_fLo;
            if (lo <= 0.0f) return 0;
            if (m_unk34 == 2) {
                const float bottom = NodeLtm().m_pos.y;
                out->y = bottom;
                out->y = bottom + lo;
            } else {
                const float push = lo - d;
                const CVector3& axis = NodeModelling().m_at;  // the frame's +0x30 (modelling at)
                out->z = ppc::fmadds(push, axis.z, out->z);
                out->x = ppc::fmadds(push, axis.x, out->x);
                out->y = ppc::fmadds(push, axis.y, out->y);
            }
            continue;
        }
        if (atTop) return 0;
        if (m_unk34 == 2) {
            const float bottom = NodeLtm().m_pos.y;
            out->y = bottom;
            out->y = bottom + hi;
        } else {
            const float push = -(d - hi);
            const CVector3& axis = NodeModelling().m_at;
            out->z = ppc::fmadds(axis.z, push, out->z);
            out->x = ppc::fmadds(axis.x, push, out->x);
            out->y = ppc::fmadds(axis.y, push, out->y);
        }
    }
    return 1;
}

// 0x00458a88 CKHkClimbZone_GetAttachMatrix_maybe. The attach point: kind 2 the box's position 0.5 x extent lower (0.25
// lower again with a ground +0x50), else the node's; with bit 3 the position itself; else, with an extent, the position
// clamped along the climb axis. Unchanged from the cached probe and without a climber, the cached matrix; otherwise
// the probe again (with a climber, after the other climbers pushed the point away).
uint8_t CKHkClimbZone::GetAttachMatrix(const CVector3* position, CMatrix34* matrix, int32_t climberKey) {
    CVector3 p;
    if (m_unk34 == 2) {
        const CMatrix34& box = BoxLtm();
        p.y = ppc::fmadds(m_fUnk30, -0.5f, box.m_pos.y);
        p.z = box.m_pos.z;
        p.x = box.m_pos.x;
        if (m_pUnk50 != nullptr) p.y = p.y - 0.25f;  // TOC1 +0x563c
    } else {
        const CMatrix34& ltm = NodeLtm();
        p = ltm.m_pos;
    }
    if ((m_bitArray & 8u) == 0) {
        const float range = m_fUnk30;
        if (range > 0.0f) {
            if (m_unk34 == 2) {
                const float top = range + p.y;
                const float y = position->y;
                if (!(y <= top)) {
                    p.y = top;
                } else if (y > p.y) {
                    p.y = y;
                }
            } else {
                const CVector3& at = NodeLtm().m_at;
                const float along =
                    ppc::fmadds(position->z - p.z, at.z, ppc::fmadds(position->x - p.x, at.x, (position->y - p.y) * at.y));
                if (range < along) {
                    p.z = ppc::fmadds(range, at.z, p.z);
                    p.x = ppc::fmadds(range, at.x, p.x);
                    p.y = ppc::fmadds(range, at.y, p.y);
                } else if (along > 0.0f) {
                    p.z = ppc::fmadds(along, at.z, p.z);
                    p.x = ppc::fmadds(along, at.x, p.x);
                    p.y = ppc::fmadds(along, at.y, p.y);
                }
            }
        }
    } else {
        p = *position;
    }
    if (m_vUnk78.x == p.x && p.y == m_vUnk78.y && p.z == m_vUnk78.z && climberKey == 0) {
        matrix->m_pos = m_vUnk84;
        matrix->m_ui32Flags &= 0xfffdffffu;
        if (m_unk34 != 2) {
            Mat4_BuildFromUpAndForward(matrix, &m_vUnk90, &NodeModelling().m_at);  // 0x0023ff80 (the frame's +0x30)
        } else {
            Mat4_SetBasisFromAtUp(matrix, &kAxisY, &m_vUnk90);  // 0x0023fd30
        }
        return 1;
    }
    CVector3 hit{};  // BUG(original): the stack words are left as they were without a hit.
    if (climberKey == 0) {
        m_vUnk78 = p;
        CVector3 probe = p;
        RaycastAttachPoint(&hit, &probe, matrix);
    } else {
        CVector3 resolved = p;
        if (ResolveClimberOverlap(&p, &resolved, climberKey) == 0) return 0;
        m_vUnk78 = resolved;
        CVector3 probe = resolved;
        RaycastAttachPoint(&hit, &probe, matrix);
    }
    m_vUnk84 = hit;
    m_vUnk90 = matrix->m_up;
    return 1;
}

// 0x004591e0 CKHkClimbZone_AttachClimberIfValid_maybe
uint8_t CKHkClimbZone::AttachClimberIfValid(float dt, const CVector3* position, CMatrix34* matrix, int32_t climberKey) {
    const CVector3 copy = *position;
    const uint8_t attached = GetAttachMatrix(&copy, matrix, climberKey);
    if (attached != 0) AddOrUpdateClimber(dt, 1, &matrix->m_pos, climberKey);
    return attached;
}

// 0x00457d68 CKHkClimbZone_Update. A crumbly zone (+0x54, bit 17) crumbles or is restored with bit 16. The zone works
// while its node's parent is a sector root (key 0x8b) or was drawn this frame and is not hidden: an on zone re-probes
// its node's position once (bit 20), pushes its body (+0x38) and times its climbers (+0x58: switched off once they
// stayed that long); an off zone waits +0x5c to switch on again. A zone not drawn only does the latter (with bit 19).
void CKHkClimbZone::Update(IKTime* frameClock) {
    // WorldObjectBase_Update_Nop 0x3f6e68.
    if ((m_bitArray & 0x20000u) != 0) {
        CKHkCrumblyZone* zone = static_cast<CKHkCrumblyZone*>(m_pUnk54);
        if ((m_bitArray & 0x10000u) != 0) {
            zone->RestoreIfDestroyed();  // 0x00414808
        } else {
            zone->CrumbleIfIntact();  // 0x00414840
        }
    }
    const float dt = frameClock->m_afDeltaTime[0];
    CSGBranch* parent = static_cast<CSGLeaf*>(m_pKGLObject)->m_pParent;
    bool working = true;
    if (parent != nullptr && parent->IsKindOfClass(0x8b) == 0) {
        if (parent->m_ui16LastRenderedFrame != g_ui16RenderFrameCounter || (parent->m_sgProperties & 4u) != 0) working = false;
    }
    if (!working) {
        if ((m_bitArray & 0x10000u) != 0) return;
        if (!(m_fUnk5C >= 0.0f)) return;
        if ((m_bitArray & 0x80000u) == 0) return;
        m_fUnkC0 = m_fUnkC0 + dt;
        if (!(m_fUnk5C <= m_fUnkC0)) return;
        SetEnabled(1);  // vt+0xcc
        m_fUnkC0 = 0.0f;
        m_bitArray &= 0xfff7ffffu;
        return;
    }
    if ((m_bitArray & 0x10000u) != 0 && (m_bitArray & 0x100000u) == 0) {
        const CMatrix34& ltm = NodeLtm();
        m_vUnk78 = ltm.m_pos;
        CVector3 point = ltm.m_pos;
        CVector3 hit{};  // BUG(original): the stack words are left as they were without a hit.
        CMatrix34 matrix{};
        RaycastAttachPoint(&hit, &point, &matrix);
        m_vUnk84 = hit;
        m_vUnk90 = matrix.m_up;
        if ((m_bitArray & 0x100000u) == 0) m_bitArray = (m_bitArray & 0xffefffffu) | 0x100000u;
    }
    if ((m_bitArray & 0x10000u) != 0 && m_pUnk38 != nullptr) {
        // STUB(C2.8): the pushes into the body +0x38 (its +0x1ac / +0x1b8 force sums and the +0x1c4 count: +0x9c / +0xa8
        // once when they are not zero, the node's at axis x +0x40 x +0x3c's +0x100, x +0x48 x the fog horn +0x44's
        // charge ratio CKHkS08FogHorn_GetChargeRatio 0x49c278): level mechanisms; no LVL010 climb zone has a body.
        DOTD_STUB_ONCE("CKHkClimbZone_Update: the pushes into the zone's body +0x38 (C2.8)");
    }
    if ((m_bitArray & 0x10000u) == 0) {
        if (m_fUnk5C >= 0.0f) {
            m_fUnkC0 = m_fUnkC0 + dt;
            if (m_fUnk5C <= m_fUnkC0) {
                SetEnabled(1);  // vt+0xcc
                m_fUnkC0 = 0.0f;
            }
        }
        return;
    }
    if (!(m_fUnk58 >= 0.0f)) return;
    if (m_vUnkB4.m_ui32NbUsedElt == 0) {
        m_fUnkC0 = 0.0f;
        return;
    }
    if (m_pUnk54 != nullptr) static_cast<CKHkCrumblyZone*>(m_pUnk54)->TryTriggerCollapse();  // 0x00414e00
    m_fUnkC0 = m_fUnkC0 + dt;
    if (!(m_fUnk58 <= m_fUnkC0)) return;
    SetEnabled(0);  // vt+0xcc
    m_fUnkC0 = 0.0f;
    m_bitArray = (m_bitArray & 0xfff7ffffu) | 0x80000u;
}

// 0x00458e98 CKHkClimbZone_AddOrUpdateClimber_maybe (all single precision, fused where the assembly fuses).
void CKHkClimbZone::AddOrUpdateClimber(float dt, uint32_t active, const CVector3* position, int32_t climberKey) {
    if ((m_bitArray & 0x10000) == 0) return;
    const uint32_t active8 = active & 0xff;
    if (active8 != 0 && (m_bitArray & 0x8000) == 0) QueueTriggerSignals(&m_tsUnk68);  // 0x00236338
    m_bitArray = (m_bitArray & 0xffff7fffu) | (active8 << 15);
    if (climberKey == 0) return;
    const RwMatrix* ltm = FrameLtm(FrameOf(m_pKGLObject));
    float x = position->x;
    float y = position->y;
    float z = position->z;
    if (x == 0.0f && y == 0.0f && z == 0.0f) {  // the vector at 0x00c50de4, (0, 0, 0)
        x = ltm->pos.x;
        y = ltm->pos.y;
        z = ltm->pos.z;
    }
    float dist;
    if (m_unk34 == 2) {
        dist = y - ltm->pos.y;
    } else {
        const float dy = y - ltm->pos.y;
        const float dx = x - ltm->pos.x;
        const float dz = z - ltm->pos.z;
        float d = dy * ltm->up.y;
        d = ppc::fmadds(dx, ltm->up.x, d);
        d = ppc::fmadds(dz, ltm->up.z, d);
        const float ey = dy - d * ltm->up.y;
        const float ex = dx - d * ltm->up.x;
        const float ez = dz - d * ltm->up.z;
        float sum = ey * ey;
        sum = ppc::fmadds(ex, ex, sum);
        sum = ppc::fmadds(ez, ez, sum);
        dist = std::sqrt(sum);  // Math_Sqrtf 0x10690 (fsqrts)
    }
    float hi = ppc::fmadds(dt, 0.5f, dist);  // TOC1 +0x5640
    float cur = m_fUnk30;
    if (!(hi > cur)) cur = hi;
    float lo = ppc::fmadds(dt, -0.5f, dist);  // TOC1 +0x5604
    if (lo <= 0.0f) lo = 0.0f;                // TOC1 +0x5618
    Climber* block = m_vUnkB4.m_pBlock;
    for (uint32_t i = 0; i < m_vUnkB4.m_ui32NbUsedElt; ++i) {
        if (block[i].m_key == climberKey) {
            block[i].m_fLo = lo;
            block[i].m_fHi = cur;
            block[i].m_fDist = dist;
            return;
        }
    }
    if (m_vUnkB4.m_ui32NbElt == m_vUnkB4.m_ui32NbUsedElt) {
        uint32_t capacity = m_vUnkB4.m_ui32NbUsedElt + 1;
        uint32_t bytes = capacity << 4;
        if (capacity == 0) {
            capacity = 1;
            bytes = 0x10;
        }
        block = static_cast<Climber*>(Mem_ReallocAligned16(block, bytes));
        m_vUnkB4.m_pBlock = block;
        m_vUnkB4.m_ui32NbElt = capacity;
    }
    Climber& added = block[m_vUnkB4.m_ui32NbUsedElt];
    added.m_key = climberKey;
    added.m_fLo = lo;
    added.m_fHi = cur;
    added.m_fDist = dist;
    m_vUnkB4.m_ui32NbUsedElt += 1;
}

// 0x00459520 CKHkClimbZone_Restart: the two run-time vectors (+0x9c, +0xa8) reset to the zero vector, no climber
// recorded (AddOrUpdateClimber with key 0 only reads the flags), bit 19 cleared.
void CKHkClimbZone::Restart() {
    m_vUnk9C = kZero;
    m_vUnkA8 = kZero;
    AddOrUpdateClimber(0.0f, 0, nullptr, 0);
    m_fUnkC0 = 0.0f;
    m_vUnkB4.m_ui32NbUsedElt = 0;
    m_bitArray &= 0xfff7ffffu;
}
