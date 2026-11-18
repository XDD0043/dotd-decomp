// SpawnInstance.cpp - reconstructed original translation unit 0xd4b30-0xd62b0 (GAME_TOC1, main_toc1), 9 functions, 7 live.
// Primary owner: SpawnInstance (not a registered class)
// Other owners: SpawnNodeData (3), SpawnNodeInfo (2)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [ ] 0xd4b30  SpawnNodeData_ResetInstanceState_maybe  [dead]
//   [x] 0xd4ba8  SpawnNodeData_ClearReferences_maybe
//   [x] 0xd4bf0  SpawnInstance_EnqueueGeometries_maybe  (ISpawnNode::EnqueueGeometries, port-final F05)
//   [x] 0xd4df0  SpawnInstance_FindActorInBoundsAndStartShake_maybe  (ISpawnNode::FindActorInBoundsAndStartShake, port-final F05)
//   [x] 0xd5198  SpawnNodeInfo_Load
//   [x] 0xd5488  SpawnNodeData_PostLoad_maybe
//   [ ] 0xd55e8  SpawnNodeInfo_Save  [dead]
//   [x] 0xd5a78  SpawnInstance_ApplyTransform_maybe  (ISpawnNode::ApplyTransform, port-final F05)
//   [x] 0xd5e20  SpawnInstance_CullAndUpdate_maybe  (ISpawnNode::CullAndUpdate, port-final F05)
#include "k2000/misc/ISpawnNode.h"

#include <cstring>

#include "Renderware/rwcore/RwCamera.h"
#include "Renderware/rwcore/RwMatrix.h"
#include "k2000/core/IKSerializable.h"
#include "k2000/io/IKFile.h"
#include "k2000/scenegraph/CSGMovable.h"
#include "k2000/misc/Mat4.h"

#include <cmath>

#include "Renderware/rpworld/RpAtomic.h"
#include "Renderware/rpworld/RpGeometry.h"
#include "crt/ppc_ops.h"
#include "crt/xsinf.h"
#include "k2000/cameras/CameraContext.h"
#include "k2000/components/CKQuakeCpntUpdater.h"
#include "k2000/geometry/CGeometry.h"
#include "k2000/graphical/memory/CKSpawnPool.h"
#include "k2000/graphical/memory/CKSpawnPoolParams.h"
#include "k2000/graphical/render/CSpawnPoolRenderParam.h"
#include "k2000/logic/render/CMaterial.h"
#include "k2000/managers/CKGraphic.h"
#include "k2000/math/CMatrix34.h"
#include "k2000/misc/Engine.h"
#include "k2000/render/CRenderer.h"
#include "k2000/scenegraph/CNode.h"


namespace {
// 0x00c50d34 (TOC1 -0x528c): the shared unit X vector the static initialiser 0x11578 builds (1, 0, 0).
const uint32_t kVectorUnitX[3] = {0x3f800000u, 0u, 0u};
}  // namespace

// 0x000d5198 SpawnNodeInfo_Load (XXL2 ISpawnNode::Load)
void ISpawnNode::Load(IKFile* file, int32_t type) {
    if (type != K_LEVEL_PLATEFORMS) return;
    m_pOriginalMatrix = nullptr;
    IKFile_ReadRef(file, &m_pSpawnPool);
    ReadU32LE(file, &m_ui32SectorNum);
    uint32_t words[6];
    ReadU32LEWords(file, words, 3);
    std::memcpy(m_rwBSphereCenter, words, 0xc);
    ReadF32LE(file, &m_rwBSphereRadius);
    ReadU32LEWords(file, words, 3);
    std::memcpy(m_unk04, words, 0xc);
    ReadF32LE(file, &m_unk10);
    ReadU32LEWords(file, m_aUnk38, 6);
}

// 0x000d5488 SpawnNodeData_PostLoad_maybe (called by CSpawnNode_PostLoad with the node's ISpawnNode part and
// the node as its CSGMovable): level data only. A copy of the node's frame matrix becomes the original matrix
// (all 16 words, flags and pads included) and the frame is given it again; the spawn state is reset.
void ISpawnNode::PostLoad(int32_t type, CSGMovable* node) {
    if (type != 0) return;
    RwMatrix* original = RwMatrixCreate();  // RwMatrixCreate_Thunk 0x23fa68
    m_pOriginalMatrix = original;
    std::memcpy(original, &node->m_pRwFrame->modelling, sizeof(RwMatrix));
    m_unk28 = 0xffffffffu;
    node->SetLocalMatrix(static_cast<const RwMatrix*>(m_pOriginalMatrix));  // 0x000d0be8
    m_unk34 = m_unk34 & 0x00ffffffu;  // the byte at +0x34 (type, 0)
    m_unk30 = nullptr;  // stw of `type` (0 here): no actor
    std::memcpy(m_aUnk50, kVectorUnitX, 0xc);
}

// 0x000d4ba8 SpawnNodeData_ClearReferences_maybe
void ISpawnNode::ClearReferences() {
    if (m_pOriginalMatrix != nullptr) {
        RwMatrixDestroy_Thunk(static_cast<CMatrix34*>(m_pOriginalMatrix));
        m_pOriginalMatrix = nullptr;
    }
}

// ---- The spawn render chain (C2.8 port-final F05).
namespace {
// 0x00c50d64 (TOC1 -0x527c): the shared null vector.
const CVector3 kNullVector = {0.0f, 0.0f, 0.0f};
// 0x00c4acb8 + 0x38 (through TOC1 -0x5280): FLT_MIN (0x00800000), the null-vector tolerance.
const float kFltMin = 0x1p-126f;

CKQuakeCpntUpdater* SlotUpdater(CKSpawnPoolParams* params, uint32_t slot) {
    return static_cast<CKQuakeCpntUpdater*>(params->m_vsMatrixData[slot].m_pObject);
}

// The world position of a spawn manager entry's node: its frame's +0x80 as it is (no RwFrameGetLTM sync).
const RwV3d& EntryPosition(const CSpawnManager::SEntry* entry) {
    return static_cast<const CSGMovable*>(entry->m_pObject)->m_pRwFrame->ltm.pos;
}

// The box test of FindActorInBoundsAndStartShake (fcmpu + cror: an unordered compare is outside): x, z, then y,
// minimum <= position <= maximum.
bool InBox(const ISpawnNode* spawn, float minX, const RwV3d& p) {
    return minX <= p.x && spawn->Bound(0) >= p.x && spawn->Bound(5) <= p.z && spawn->Bound(2) >= p.z &&
           spawn->Bound(4) <= p.y && spawn->Bound(1) >= p.y;
}

uint32_t FloatBits(float value) {
    uint32_t bits;
    std::memcpy(&bits, &value, 4);
    return bits;
}
}  // namespace

float ISpawnNode::Bound(uint32_t index) const {
    float value;
    std::memcpy(&value, &m_aUnk38[index], 4);
    return value;
}

// 0x000d4df0 SpawnInstance_FindActorInBoundsAndStartShake_maybe. The latch byte +0x34 follows the slot's running flag.
uint8_t ISpawnNode::FindActorInBoundsAndStartShake(CKSpawnPoolParams* params) {
    const uint32_t slot = m_unk28;
    if (slot == 0xffffffffu) return 1;
    if (SlotUpdater(params, slot)->m_bRunning == 0) SetByte34(0);
    const uint32_t flags = params->m_unk04;
    if ((flags & 1) == 0 || (flags & 2) != 0) return 0;
    const float minX = Bound(3);
    CSpawnManager::SEntry* actor = m_unk30;
    if (actor != nullptr) {
        if (InBox(this, minX, EntryPosition(actor))) {
            if (SlotUpdater(params, slot)->m_bRunning == 0) {
                const CVector3& dir = actor->m_vDir;
                // A direction within FLT_MIN of the null vector (each axis: dir - min <= 0 and min + dir >= 0) does not
                // restart the shake.
                if (!(dir.x - kFltMin <= kNullVector.x && kFltMin + dir.x >= kNullVector.x &&
                      dir.y - kFltMin <= kNullVector.y && kFltMin + dir.y >= kNullVector.y &&
                      dir.z - kFltMin <= kNullVector.z && kFltMin + dir.z >= kNullVector.z)) {
                    m_aUnk50[0] = dir.x;
                    m_aUnk50[2] = dir.z;
                    m_aUnk50[1] = dir.y;
                    params->StartShake(m_unk28);  // 0x000b7d58
                }
            }
            return 1;
        }
        m_unk30 = nullptr;
        SetByte34(SlotUpdater(params, slot)->m_bRunning != 0 ? 1 : 0);
        return 0;
    }
    CSpawnManager* manager = static_cast<CSpawnManager*>(g_pEngine->m_graphic->m_renderer->m_spawnManager);
    const uint32_t count = manager->m_vUnk20.m_ui32NbUsedElt;
    CSpawnManager::SEntry* entry = manager->m_vUnk20.m_pBlock;
    for (uint32_t i = 0; i < count; ++i, ++entry) {
        if (InBox(this, minX, EntryPosition(entry))) {
            m_unk30 = entry;
            if (SlotUpdater(params, slot)->m_bRunning != 0) return 0;
            params->StartShake(slot);  // 0x000b7d58
            const CVector3& dir = m_unk30->m_vDir;
            m_aUnk50[0] = dir.x;
            m_aUnk50[2] = dir.z;
            m_aUnk50[1] = dir.y;
            return 1;
        }
    }
    return 0;
}

// 0x000d5a78 SpawnInstance_ApplyTransform_maybe. The slot is taken on first use (CKSpawnPoolParams_NextIndex_maybe). A
// stopped shake puts the original matrix back. Else the copy of the original is concatenated (pre) with the slot's shake
// matrix: unoriented with flag 2, else oriented along the shake direction brought into the original's local space
// (Mat4_Invert, Mat4_TransformVectors; its length fused as y*y, then x and z fmadds; normalised by 1/length unless 0).
// The up axis is scaled by +0x5c and the identity flags (0x20000, 1) cleared before it becomes the local matrix; the
// node's world matrices (vt+0x68, forced) and the spawn sphere (the local one +0x04 / +0x10 into +0x14 / +0x20) follow.
void ISpawnNode::ApplyTransform(CNode* node, CKSpawnPoolParams* params, IKTime* /*clock*/) {
    if ((params->m_unk04 & 1) == 0) return;
    uint32_t slot = m_unk28;
    if (slot == 0xffffffffu) {
        slot = params->NextIndex();  // 0x000b7b78
        m_unk28 = slot;
    }
    if (SlotUpdater(params, slot)->m_bRunning == 0) {
        node->SetLocalMatrix(static_cast<const RwMatrix*>(m_pOriginalMatrix));  // 0x000d0be8
        return;
    }
    CMatrix34 matrix;
    std::memcpy(&matrix, m_pOriginalMatrix, sizeof(CMatrix34));
    CMatrix34* shake;
    if ((params->m_unk04 & 2) != 0) {
        shake = params->GetShakeMatrix(m_unk28, &kNullVector, 0);  // 0x000b8268
    } else {
        CMatrix34 inverse;
        Mat4_Invert(&inverse, static_cast<const CMatrix34*>(m_pOriginalMatrix));  // 0x0023f878
        CVector3 direction;
        Mat4_TransformVectors(&inverse, &direction, reinterpret_cast<const CVector3*>(m_aUnk50), 1);  // 0x0023f7b0
        const float length = std::sqrt(ppc::fmadds(direction.z, direction.z,
                                                    ppc::fmadds(direction.x, direction.x, direction.y * direction.y)));
        if (length != 0.0f) {  // 0x00010690 Math_Sqrtf; TOC1 -0x5288 0
            const float inverseLength = 1.0f / length;
            direction.z = direction.z * inverseLength;
            direction.x = direction.x * inverseLength;
            direction.y = direction.y * inverseLength;
        }
        shake = params->GetShakeMatrix(m_unk28, &direction, 1);
    }
    Mat4_TransformPreConcat(&matrix, shake);  // 0x0023f738
    const float scale = m_aUnk50[3];
    matrix.m_up.x = scale * matrix.m_up.x;
    matrix.m_up.z = scale * matrix.m_up.z;
    matrix.m_up.y = scale * matrix.m_up.y;
    matrix.m_ui32Flags &= 0xfffdfffeu;
    node->SetLocalMatrix(reinterpret_cast<const RwMatrix*>(&matrix));  // 0x000d0be8
    node->UpdateWorldMatrices(1);                                       // vt+0x68
    TransformNodeBoundingSphereToWorld(m_unk10, node, m_rwBSphereCenter, &m_rwBSphereRadius, m_unk04);  // 0x000cbfc0
}

// 0x000d5e20 SpawnInstance_CullAndUpdate_maybe. The first geometry's render flag 0x40000 (bit 18) keeps the node past the
// far distance and unfaded (the original reads it before any test: the list is never empty). bge / cror lt|eq: an
// unordered distance passes the far test and fades. The fade t = 1 - (d - near) * (1 / (far - near)) (fmuls, fsubs);
// render param flag 2: the grow scale = sin(t * pi/2) (the game's inlined sine, the library sinf for a negative
// product); flag 1: the alpha = the low byte of fctiwz(t * 255); otherwise 0xff. The geometries then take that alpha
// in colour byte 3: 0xff clears their alpha stage bit 0x800 everywhere; another alpha sets it, except for a geometry
// with render flag 0x1000 whose material shader mode (bits 3-6) is 1..6, which keeps 0xff and loses the bit. A bit
// change re-runs the geometry's UpdateProperties (vt+0x60).
uint8_t ISpawnNode::CullAndUpdate(CNode* node, IKTime* clock) {
    CKSpawnPool* pool = static_cast<CKSpawnPool*>(m_pSpawnPool);
    CKSpawnPoolParams* params = static_cast<CKSpawnPoolParams*>(pool->m_apSpawnPoolParams[m_ui32SectorNum]);
    CSpawnPoolRenderParam* render = static_cast<CSpawnPoolRenderParam*>(pool->m_apRenderParams[m_ui32SectorNum]);
    if (params == nullptr || render == nullptr) return 0;
    CGeometry* first = static_cast<CGeometry*>(node->m_lGeometryList);
    const uint32_t keep = first != nullptr ? (first->m_BitProperties >> 18) & 1u : 0u;
    const RwV3d& position = node->m_pRwFrame->ltm.pos;
    const CameraContext* context = static_cast<const CameraContext*>(g_pEngine->m_cameraContext);
    const RwV3d& camera = static_cast<const CSGMovable*>(context->m_pCamera)->m_pRwFrame->modelling.pos;
    const float farDistance = render->m_fFar;
    const float nearDistance = render->m_fNear;
    const float dy = position.y - camera.y;
    const float dx = position.x - camera.x;
    const float dz = position.z - camera.z;
    const float distance = ppc::fmadds(dz, dz, ppc::fmadds(dx, dx, dy * dy));
    if (farDistance < distance && keep == 0) return 0;
    // 0x0098e8d0 with the main camera 0x00c5c9cc (CameraContext.cpp keeps it equal to the context's +0x0c).
    if (RwCameraFrustumTestSphere(context->m_pMainCamera, m_rwBSphereCenter) == 0) return 0;
    m_aUnk50[3] = 1.0f;  // TOC1 -0x5270
    uint8_t alpha = 0xff;
    if (!(distance <= nearDistance) && keep == 0) {
        const float t = 1.0f - (distance - nearDistance) * render->m_fInvRange;
        if ((render->m_unk04 & 2) != 0) {
            const float angle = t * 1.5707963705062866f;  // TOC1 -0x5244 (0x3fc90fdb)
            m_aUnk50[3] = (FloatBits(angle) & 0x80000000u) != 0 ? -crt::LibSinf(-angle) : crt::InlineSinf(angle);
        }
        if ((render->m_unk04 & 1) != 0) {
            alpha = static_cast<uint8_t>(ppc::fctiwz(t * 255.0f));  // TOC1 -0x5240; stfiwx, lbz of the low byte
        }
    }
    if (FindActorInBoundsAndStartShake(params) != 0 || (params->m_unk04 & 2) != 0 || Byte34() != 0) {
        ApplyTransform(node, params, clock);
    }
    CGeometry* geometry = static_cast<CGeometry*>(node->m_lGeometryList);
    if (geometry == nullptr || alpha == geometry->m_cGeometryColor[3]) return 1;
    if (alpha == 0xff) {
        for (; geometry != nullptr; geometry = geometry->m_pNext) {
            geometry->m_cGeometryColor[3] = alpha;
            const uint32_t bits = geometry->m_BitProperties;
            if (((bits >> 11) & 1) != 0) {
                geometry->m_BitProperties = bits & ~0x800u;
                geometry->UpdateProperties();  // vt+0x60
            }
        }
        return 1;
    }
    for (; geometry != nullptr; geometry = geometry->m_pNext) {
        uint32_t stageBit = 1;
        uint8_t value = alpha;
        if ((geometry->m_BitProperties & 0x1000) != 0) {
            const uint32_t mode = (static_cast<CMaterial*>(geometry->m_pMaterial)->m_baProperties >> 3) & 0xf;
            if (mode != 0 && mode <= 6) {
                stageBit = 0;
                value = 0xff;
            }
        }
        geometry->m_cGeometryColor[3] = value;
        const uint32_t bits = geometry->m_BitProperties;
        if (((bits >> 11) & 1) != stageBit) {
            geometry->m_BitProperties = (bits & ~0x800u) | (stageBit << 11);
            geometry->UpdateProperties();  // vt+0x60
        }
    }
    return 1;
}

// 0x000d4bf0 SpawnInstance_EnqueueGeometries_maybe. With a sphere every atomic takes it as its bounding sphere (a
// morphing atomic resynced first: BridgeRwUpdateAtomicMorphBoundingSphere 0x98e090), its dirty-sphere flag cleared and
// its world bound marked dirty, before its world sphere (vt+0x78); without one only vt+0x78. The node's frame loses its
// object-sync mark (privateFlags 0x8), then every geometry is enqueued with distance 0 and no distance cull.
void ISpawnNode::EnqueueGeometries(CNode* node, RenderQueue** stages, IKTime* clock, const float* sphere,
                                   RwCamera* camera) {
    CGeometry* geometry = static_cast<CGeometry*>(node->m_lGeometryList);
    if (sphere == nullptr) {
        for (; geometry != nullptr; geometry = geometry->m_pNext) geometry->GetWorldBoundingSphere(node);  // vt+0x78
    } else {
        for (; geometry != nullptr; geometry = geometry->m_pNext) {
            const float radius = sphere[3];
            RpAtomic* atomic = geometry->m_pRpAtomic;
            if ((atomic->flags & 2) != 0) {
                _rpAtomicResyncInterpolatedSphere(atomic);
                atomic = geometry->m_pRpAtomic;
            }
            atomic->boundingSphere[0] = sphere[0];
            atomic->boundingSphere[1] = sphere[1];
            atomic->boundingSphere[2] = sphere[2];
            atomic->boundingSphere[3] = radius;
            geometry->m_pRpAtomic->flags &= 0xfffffffdu;
            geometry->m_pRpAtomic->privateFlags |= 1;
            geometry->GetWorldBoundingSphere(node);  // vt+0x78
        }
    }
    RwFrame* frame = node->m_pRwFrame;
    frame->object.privateFlags = static_cast<uint8_t>(frame->object.privateFlags & 0xf7);
    for (geometry = static_cast<CGeometry*>(node->m_lGeometryList); geometry != nullptr; geometry = geometry->m_pNext) {
        geometry->EnqueueVisible(0.0f, stages, clock, camera, 0);  // vt+0x58; TOC1 -0x5288 0
    }
}
