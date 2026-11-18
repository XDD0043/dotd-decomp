// CParticlesNodeFx_2.cpp - reconstructed original translation unit 0xe5fb8-0xe79f8 (GAME_TOC1, main_toc1), 16 functions, 14 live.
// Primary class: CParticlesNodeFx  key 0x4cb  category SceneNode  size 0x68  vtable 0xb18b18
// Other owners: EnqueueParticleNodeRenderWork (1), ParticleFxNode (1), UpdateParticleNodeSimulation (1), PrepareParticleNodeForRendering (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0xe5fb8  CParticlesNodeFx_RecursiveRegistration  (INodeFx's (returns 1, registers nothing): CSGLeaf's)
//   [x] 0xe5fe0  EnqueueParticleNodeRenderWork
//   [x] 0xe6160  CParticlesNodeFx_DeleteArray
//   [x] 0xe6200  CreateCParticlesNodeFx
//   [ ] 0xe6278  CParticlesNodeFx_CopyEmitPointArrays_maybe  [dead]
//   [ ] 0xe6370  FUN_000e6370  [dead]
//   [x] 0xe64b0  CParticlesNodeFx_TransformEmitPointsToWorld_maybe
//   [x] 0xe6598  CParticlesNodeFx_Destroy
//   [x] 0xe65f0  CParticlesNodeFx_PostLoad
//   [x] 0xe6768  CParticlesNodeFx_CreateArray
//   [x] 0xe6868  CParticlesNodeFx_MessageProc
//   [x] 0xe6938  ParticleFxNode_StopEmitting_maybe
//   [x] 0xe6a00  CParticlesNodeFx_Load
//   [x] 0xe6ba8  UpdateParticleNodeSimulation
//   [x] 0xe6c60  PrepareParticleNodeForRendering
//   [ ] 0xe7870  CParticlesNodeFx_Save
//
//   [ ] 0x9a54b0  CParticlesNodeFx_IsKindOfClass  [inline]
//   [x] 0x9a5510  CParticlesNodeFx_GetClassType  [inline]
//   [x] 0x9a5518  CParticlesNodeFx_GetClassID  [inline]
//   [ ] 0x9a5520  CParticlesNodeFx_Destructor  [inline]
//   [ ] 0x9a5560  CParticlesNodeFx_DeletingDestructor  [inline]
#include "k2000/scenegraph/CParticlesNodeFx.h"

#include <cmath>

#include "Renderware/rpprtstd/RpPrtStd.h"
#include "Renderware/rpprtstd/RpPrtStdRuntime.h"
#include "Renderware/rpworld/RpAtomic.h"
#include "Renderware/rwcore/RwCamera.h"
#include "Renderware/rwcore/RwMatrix.h"
#include "crt/ppc_ops.h"
#include "k2000/fx/ParticleUpdateScheduler.h"
#include "k2000/misc/Engine.h"
#include "k2000/render/CRenderer.h"
#include "k2000/system/IKTime.h"
#include "k2000/misc/ClassRegistry.h"
#include "k2000/scenegraph/CAnimatedNode.h"
#include "k2000/geometry/CGeometry.h"
#include "k2000/io/IKFile.h"
#include "k2000/misc/Mat4.h"

// Inlined in 0x000e6200 CreateCParticlesNodeFx (InitializeCNode, the INodeFx vtable, then these).
CParticlesNodeFx::CParticlesNodeFx() {
    m_pAdvEmtPointList = nullptr;
    m_ui32LastUpdateGeneration = 0xffffffff;
    m_bReadyForWorkerUpdate = 0;
}

// 0x000e6a00 CParticlesNodeFx_Load. No type check of its own.
int32_t CParticlesNodeFx::Load(IKFile* file, int32_t type) {
    INodeFx::Load(file, type);
    ReadU8(file, &m_ui8NbActivePoints);
    ReadU8(file, &m_ui8NbEmitParticlesPerPoint);
    ReadF32LE(file, &m_fCompensationCoeff);
    ReadRaw(file, m_ai8BoneExclusion, 4);
    static const CVector3 kNullVector = {0.0f, 0.0f, 0.0f};  // g_nullVector (0x00c50d64, XXL2 name)
    m_oldPosition = kNullVector;
    m_oldSpeed = kNullVector;
    ReadF32LE(file, &m_fBoundingRadius);
    return 1;
}

// 0x000e65f0 CParticlesNodeFx_PostLoad. No type check of its own: the base part, then the first
// geometry's atomic's emitter bound (+0x58) and its point list (+0x54, property 0x1000006): the loaded
// point count into it, or, with scene flag 0x8000, the count cleared and flag 0x2000 set. Without flag
// 0x1000 the atomic's bounding sphere becomes (0, 0, 0) radius 100000 (TOC 0x00c10b28). The emitter's
// flags follow scene flag 0x400 (ACTIVE | EMIT, 0xa), flag 0x2000 is set when there is a point list, and
// the emission speed adjustment is cleared.
int32_t CParticlesNodeFx::PostLoad(int32_t type) {
    // 0x000eca78 CNodeFx_PostLoadBase_maybe (INodeFx, k2000/fx/CNodeFx.cpp): the geometries' render bits 22,
    // 23, 25 from +0x28..+0x2a and their vt+0x80, then CNode_PostLoad 0xcc340 (the atomics on the node's frame).
    INodeFx::PostLoad(type);
    // BUG(original): neither the first geometry nor its atomic's emitter is checked (every particle node's
    // atomic has one).
    RpAtomic* atomic = static_cast<CGeometry*>(m_lGeometryList)->m_pRpAtomic;
    RpPrtStdEmitter* emitter = RpPrtStdAtomicGetEmitter(atomic);
    m_pRpPrtStdEmitter = emitter;
    const int32_t offset =
        RpPrtStdPropTabGetPropOffset(emitter->emtClass->propTab, rpPRTADVPROPERTYCODEEMITTERPOINTLIST);
    if (offset == -1) {
        m_pAdvEmtPointList = nullptr;
    } else {
        m_pAdvEmtPointList = reinterpret_cast<RpPrtAdvEmtPointList*>(reinterpret_cast<uint8_t*>(emitter) + offset);
        if ((m_sgProperties & 0x8000u) == 0) {
            m_pAdvEmtPointList->numPoint = m_ui8NbActivePoints;
        } else {
            m_ui8NbActivePoints = 0;
            m_sgProperties = (m_sgProperties & ~0x2000u) | 0x2000u;
        }
    }
    if ((m_sgProperties & 0x1000u) == 0) {
        atomic->boundingSphere[3] = 100000.0f;
        atomic->boundingSphere[0] = 0.0f;
        atomic->boundingSphere[2] = 0.0f;
        atomic->boundingSphere[1] = 0.0f;
    }
    if ((m_sgProperties & 0x400u) == 0) {
        emitter->flag &= ~(rpPRTSTDEMITTERFLAGACTIVE | rpPRTSTDEMITTERFLAGEMIT);
    } else {
        emitter->flag |= rpPRTSTDEMITTERFLAGACTIVE | rpPRTSTDEMITTERFLAGEMIT;
    }
    if (m_pAdvEmtPointList != nullptr) m_sgProperties = (m_sgProperties & ~0x2000u) | 0x2000u;
    m_fEmissionSpeedAdjustment = 0.0f;  // stw 0
    RpPrtStdShim_NoteBoundNode(emitter, m_pAdvEmtPointList);  // DEV (gfx_c16_test)
    return 1;
}

namespace {

// The node's frame time (inlined in 0xe6ba8 and 0xe6c60): nothing when the clock is stopped (state 3);
// running (state 0) the unscaled time (+0x20) for nodes that ignore the time scale (0x40000) or the pause
// (0x80000), else the scaled time (+0x1c); in any other state only 0x40000 nodes move (the unscaled time).
float NodeFrameTime(uint32_t flags, const IKTime* frameClock) {
    const int32_t state = frameClock->m_eCurrentState;
    if (state == 3) return 0.0f;
    if (state == 0) {
        if ((flags & 0x40000) != 0 || (flags & 0x80000) != 0) return frameClock->m_afDeltaTime[1];
        return frameClock->m_afDeltaTime[0];
    }
    if ((flags & 0x40000) != 0) return frameClock->m_afDeltaTime[1];
    return 0.0f;
}

// The node frame's stored LTM position (RwFrame +0x80, read directly; no hierarchy sync).
const RwV3d* FramePosition(RwFrame* frame) { return &FrameLtm(frame)->pos; }

// 0x0023f878 Mat4_Invert_maybe: RwMatrixInvert through its TOC bridge (0x98e1e0).
void Mat4_Invert(RwMatrix* out, const RwMatrix* in) { RwMatrixInvert(out, in); }
// 0x0023f7b0 Mat4_TransformVectors(matrix, out, in, count): RwV3dTransformVectors(out, in, count, matrix) through its
// TOC bridge (0x98e1f0).
void Mat4_TransformVectors(const RwMatrix* matrix, RwV3d* out, const RwV3d* in, int32_t count) {
    RwV3dTransformVectors(out, in, count, matrix);
}

}  // namespace

// 0x000e5fe0 EnqueueParticleNodeRenderWork. The work array grows by 32 (Mem_ReallocAligned16).
void CParticlesNodeFx::UpdateAndExtract(float /*maxDistanceSquared*/, RenderQueue** stages, IKTime* frameClock,
                                        RwCamera* camera, int32_t /*distanceCull*/) {
    ParticleUpdateScheduler* scheduler = g_pEngine->m_particleScheduler;
    if (scheduler->workCapacity == scheduler->workCount) {
        uint32_t capacity = scheduler->workCapacity + 0x20;
        if (capacity == 0) capacity = 0x20;
        scheduler->workItems = static_cast<ParticleRenderWorkItem*>(
            ParticleScheduler_Realloc(scheduler->workItems, capacity * sizeof(ParticleRenderWorkItem)));
        scheduler->workCapacity = capacity;
    }
    ParticleRenderWorkItem* item = &scheduler->workItems[scheduler->workCount];
    item->node = this;
    item->camera = camera;
    item->frameClock = frameClock;
    item->stages = stages;
    ++scheduler->workCount;
    for (CSGLeaf* child = m_lChildList; child != nullptr; child = child->m_pNext) {
        child->UpdateAndExtract(0.0f, stages, frameClock, camera, 0);  // TOC -0x4ec4: 0.0f
    }
    m_sgProperties &= 0xfff7ffffu;
}

// 0x000e6ba8 UpdateParticleNodeSimulation: not for nodes moved by their emitter (0x800, prepared instead);
// with flag 1 the frame time, then the atomic's particles updated (RW_UpdateParticleAtomic).
void UpdateParticleNodeSimulation(CParticlesNodeFx* node, IKTime* frameClock) {
    const uint32_t flags = node->m_sgProperties;
    if ((flags & 0x800) != 0) return;
    if ((flags & 1) != 0) node->m_fDeltaTime = NodeFrameTime(flags, frameClock);
    CGeometry* geometry = static_cast<CGeometry*>(node->m_lGeometryList);
    RpPrtStdAtomicUpdate(geometry->m_pRpAtomic, &node->m_fDeltaTime);
}

// 0x000e6c60 PrepareParticleNodeForRendering. An active emitter (unless the node is hidden, flag 4) with
// emission on (0x400) or live particles: the frame time (flag 1); the geometry queued (vt+0x84) unless the
// node is unbounded (0x1000) or holds a point list without 0x4000, the first time only stamped (and the
// atomic then updated and emitting once with the emit gap as the time); the emission speed adjustment
// added to the initial speed, or for a node that drags its emitter (0x800) the node's velocity feeding the
// standard property's force and direction (put back afterwards); the point list's points count set (or
// emission stopped when it has none); the particles updated (unless the worker did, generation) and
// emitting, with flag 0x200 once with the frame time as the emission time; the node ready for the worker
// while it has particles. Otherwise a dragging node only tracks its position and velocity.
void PrepareParticleNodeForRendering(CParticlesNodeFx* node, RenderQueue** stages, IKTime* frameClock, RwCamera* camera) {
    node->m_bReadyForWorkerUpdate = 0;
    uint32_t flags = node->m_sgProperties;
    RpPrtStdEmitter* emitter = node->m_pRpPrtStdEmitter;
    if ((flags & 4) == 0 && (emitter->flag & rpPRTSTDEMITTERFLAGACTIVE) != 0 &&
        ((node->m_sgProperties & 0x400) != 0 || emitter->prtActive != 0)) {
        flags = node->m_sgProperties;
        RpAtomic* atomic = static_cast<CGeometry*>(node->m_lGeometryList)->m_pRpAtomic;
        const int32_t stdOffset = emitter->emtClass->propTab->propOffset[1];  // the property at index 1
        if ((flags & 1) != 0) node->m_fDeltaTime = NodeFrameTime(flags, frameClock);
        bool first;
        if ((flags & 0x1000) == 0 && (node->m_pAdvEmtPointList == nullptr || (flags & 0x4000) != 0)) {
            if (node->m_ui16LastRenderedFrame == 0) {
                first = true;
                node->m_ui16LastRenderedFrame = g_ui16RenderFrameCounter;
            } else {
                if (node->CullAndEnqueueGeometry(stages, frameClock, camera) == 0) {
                    node->m_bReadyForWorkerUpdate = 0;
                    return;
                }
                first = false;
                flags = node->m_sgProperties;
                node->m_ui16LastRenderedFrame = g_ui16RenderFrameCounter;
            }
        } else {
            first = false;
        }
        RpPrtStdEmitterStandard* std =
            reinterpret_cast<RpPrtStdEmitterStandard*>(reinterpret_cast<uint8_t*>(emitter) + stdOffset);
        float savedVel = 0.0f;
        RwV3d savedForce = {0.0f, 0.0f, 0.0f};
        RwV3d savedDir = {0.0f, 0.0f, 0.0f};
        if ((flags & 0x800) != 0) {
            const float adjustment = node->m_fEmissionSpeedAdjustment;
            savedVel = std->prtInitVel;
            savedForce = std->force;
            savedDir = std->prtInitDir;
            std->prtInitVel = savedVel + adjustment;
            if (node->m_fDeltaTime != 0.0f) {
                const float inv = 1.0f / node->m_fDeltaTime;
                const RwV3d* pos = FramePosition(node->m_pRwFrame);
                RwV3d v;
                v.x = inv * (pos->x - node->m_oldPosition.x);
                v.y = inv * (pos->y - node->m_oldPosition.y);
                v.z = inv * (pos->z - node->m_oldPosition.z);
                std->prtInitDir = v;
                const float coeff = node->m_fCompensationCoeff;
                const float dx = (v.x - node->m_oldSpeed.x) * coeff;
                const float dy = (v.y - node->m_oldSpeed.y) * coeff;
                const float dz = (v.z - node->m_oldSpeed.z) * coeff;
                std->force.x = ppc::fmadds(inv, dx, std->force.x);
                std->force.y = ppc::fmadds(inv, dy, std->force.y);
                std->force.z = ppc::fmadds(inv, dz, std->force.z);
                pos = FramePosition(node->m_pRwFrame);
                node->m_oldPosition.x = pos->x;
                node->m_oldPosition.y = pos->y;
                node->m_oldPosition.z = pos->z;
                node->m_oldSpeed.x = std->prtInitDir.x;
                node->m_oldSpeed.y = std->prtInitDir.y;
                node->m_oldSpeed.z = std->prtInitDir.z;
                const float scale = node->m_fCompensationCoeff;
                std->prtInitDir.x = scale * std->prtInitDir.x;
                std->prtInitDir.z = scale * std->prtInitDir.z;
                std->prtInitDir.y = scale * std->prtInitDir.y;
                // The direction into the frame's space: the inverse of the frame's stored LTM (+0x50).
                RwMatrix inverse;
                Mat4_Invert(&inverse, FrameLtm(node->m_pRwFrame));
                Mat4_TransformVectors(&inverse, &std->prtInitDir, &std->prtInitDir, 1);
                std->prtInitDir.y = ppc::fmadds(savedDir.y, savedVel, std->prtInitDir.y);
                std->prtInitDir.x = ppc::fmadds(savedDir.x, savedVel, std->prtInitDir.x);
                std->prtInitDir.z = ppc::fmadds(savedDir.z, savedVel, std->prtInitDir.z);
                const float y2 = std->prtInitDir.y * std->prtInitDir.y;
                float length = ppc::fmadds(std->prtInitDir.x, std->prtInitDir.x, y2);
                length = ppc::fmadds(std->prtInitDir.z, std->prtInitDir.z, length);
                length = std::sqrt(length);  // 0x00010690 Math_Sqrtf (fsqrts)
                if (length == 0.0f) {
                    std->prtInitVel = 0.0f;
                } else {
                    const float invLength = 1.0f / length;
                    std->prtInitDir.z = invLength * std->prtInitDir.z;
                    std->prtInitDir.x = invLength * std->prtInitDir.x;
                    std->prtInitDir.y = invLength * std->prtInitDir.y;
                    std->prtInitVel = length;
                }
            }
        } else if (node->m_fEmissionSpeedAdjustment != 0.0f) {
            savedVel = std->prtInitVel;
            std->prtInitVel = node->m_fEmissionSpeedAdjustment + savedVel;
        }
        bool emit;
        RpPrtAdvEmtPointList* list = node->m_pAdvEmtPointList;
        if (list == nullptr) {
            emit = true;
        } else {
            uint32_t count = node->m_ui8NbActivePoints;
            if (node->m_pParent != nullptr && (node->m_sgProperties & 0x10000) != 0) {
                // The points from the (animated) parent's bone positions: at most its subtree's bone count, in
                // order from the last bone down, or at random (0x20000: one rand() draw per point, bone =
                // (rand & 0xffff) * bones >> 16), skipping the four excluded bones (each skip one point less);
                // flag 0x2000 when the count changed. BUG(original): the parent is not checked to be animated.
                const CAnimatedNode* parent = static_cast<const CAnimatedNode*>(static_cast<CSGLeaf*>(node->m_pParent));
                const uint32_t loaded = count;
                uint32_t points = loaded;
                if (!(parent->GetSubtreeBoneCount(0) > loaded)) points = parent->GetSubtreeBoneCount(0);
                const int8_t* excluded = node->m_ai8BoneExclusion;
                float* out = reinterpret_cast<float*>(list->pointList);
                auto isExcluded = [excluded](int8_t bone) {
                    return excluded[0] == bone || excluded[1] == bone || excluded[2] == bone || excluded[3] == bone;
                };
                if ((node->m_sgProperties & 0x20000) == 0) {
                    uint32_t bone = points - 1;
                    for (uint32_t left = points; left != 0;) {
                        --left;
                        if (isExcluded(static_cast<int8_t>(bone))) {
                            --points;
                            --bone;
                            continue;
                        }
                        const RwMatrix* matrix = parent->GetBoneMatrix(left);
                        out[2] = matrix->pos.z;
                        out[0] = matrix->pos.x;
                        out[1] = matrix->pos.y;
                        out += 3;
                        --bone;
                    }
                } else {
                    const uint32_t bones = parent->GetSubtreeBoneCount(0);
                    for (uint32_t left = points; left != 0;) {
                        --left;
                        const uint32_t product = (static_cast<uint32_t>(Rand_Int()) & 0xffffu) * bones;
                        const uint32_t bone = (product >> 16) & 0xffffu;
                        if (isExcluded(static_cast<int8_t>(bone))) {
                            --points;
                            continue;
                        }
                        const RwMatrix* matrix = parent->GetBoneMatrix(bone & 0xffu);
                        out[2] = matrix->pos.z;
                        out[0] = matrix->pos.x;
                        out[1] = matrix->pos.y;
                        out += 3;
                    }
                }
                if (points != loaded) {
                    node->m_sgProperties = (node->m_sgProperties & ~0x2000u) | 0x2000u;
                    count = points;
                }
            }
            if (count == 0) {
                emit = false;
                std->emtPrtEmit = 0;
                list->numPoint = 0;
                node->m_pRpPrtStdEmitter->flag &= ~rpPRTSTDEMITTERFLAGEMIT;
                if (node->m_pRpPrtStdEmitter->prtActive != 0) emit = true;
            } else {
                const uint32_t before = node->m_sgProperties;
                node->m_sgProperties = before & ~0x2000u;
                emit = true;
                if ((before & 0x2000) != 0) {
                    if ((node->m_sgProperties & 0x400) != 0) node->m_pRpPrtStdEmitter->flag |= rpPRTSTDEMITTERFLAGEMIT;
                    list->numPoint = count;
                    if ((node->m_sgProperties & 0x4000) == 0) {
                        std->emtPrtEmit = node->m_ui8NbEmitParticlesPerPoint;
                    } else {
                        std->emtPrtEmit = count * node->m_ui8NbEmitParticlesPerPoint;
                    }
                }
            }
        }
        const uint32_t generation = g_pEngine->m_particleScheduler->generation;
        if (first) {
            RpPrtStdAtomicUpdateAndEmit(atomic, &std->emtEmitGap);
            atomic->boundingSphere[3] = atomic->boundingSphere[3] + node->m_fBoundingRadius;
        }
        if (emit) {
            const uint32_t now = node->m_sgProperties;
            if ((now & 0x200) == 0) {
                if (node->m_ui32LastUpdateGeneration != generation - 1 || (now & 0x800) != 0)
                    RpPrtStdAtomicUpdate(atomic, &node->m_fDeltaTime);
                RpPrtStdAtomicEmit(atomic, &node->m_fDeltaTime);
                atomic->boundingSphere[3] = atomic->boundingSphere[3] + node->m_fBoundingRadius;
            } else {
                // Emit once now: the emission time set to the frame time for this emit (the word copied).
                const float savedEmitTime = std->emtEmitTime;
                std->emtEmitTime = node->m_fDeltaTime;
                if (node->m_ui32LastUpdateGeneration != generation - 1 || (node->m_sgProperties & 0x800) != 0)
                    RpPrtStdAtomicUpdate(atomic, &node->m_fDeltaTime);
                RpPrtStdAtomicEmit(atomic, &node->m_fDeltaTime);
                atomic->boundingSphere[3] = atomic->boundingSphere[3] + node->m_fBoundingRadius;
                std->emtEmitTime = savedEmitTime;
                node->m_sgProperties &= 0xfff7f9ffu;
                node->m_pRpPrtStdEmitter->flag &= ~rpPRTSTDEMITTERFLAGEMIT;
            }
        }
        if (list != nullptr && (node->m_sgProperties & 0x8000) != 0) {
            node->m_ui8NbActivePoints = 0;
            node->m_sgProperties = (node->m_sgProperties & ~0x2000u) | 0x2000u;
        }
        if ((node->m_sgProperties & 0x800) != 0) {
            std->force = savedForce;
            std->prtInitDir = savedDir;
            std->prtInitVel = savedVel;
        } else if (node->m_fEmissionSpeedAdjustment != 0.0f) {
            std->prtInitVel = savedVel;
        }
        if ((node->m_sgProperties & 0x400) == 0 && node->m_pRpPrtStdEmitter->prtActive == 0) {
            node->m_pRpPrtStdEmitter->flag &= ~rpPRTSTDEMITTERFLAGACTIVE;
        }
        if (emit && node->m_pRpPrtStdEmitter->prtActive != 0) {
            if (node->m_ui16LastRenderedFrame != g_ui16RenderFrameCounter &&
                node->CullAndEnqueueGeometry(stages, frameClock, camera) != 0) {
                node->m_ui16LastRenderedFrame = g_ui16RenderFrameCounter;
            }
            node->m_bReadyForWorkerUpdate = 1;
            return;
        }
        node->m_bReadyForWorkerUpdate = 0;
        return;
    }
    flags = node->m_sgProperties;
    if (node->m_pAdvEmtPointList != nullptr && (flags & 0x8000) != 0) {
        node->m_ui8NbActivePoints = 0;
        node->m_sgProperties = (node->m_sgProperties & ~0x2000u) | 0x2000u;
        flags = node->m_sgProperties;
    }
    if ((flags & 0x800) == 0) return;
    const float time = NodeFrameTime(flags, frameClock);
    if (time == 0.0f) {
        node->m_oldSpeed.x = 0.0f;  // g_nullVector (0x00c50d64)
        node->m_oldSpeed.y = 0.0f;
        node->m_oldSpeed.z = 0.0f;
    } else {
        const RwV3d* pos = FramePosition(node->m_pRwFrame);
        node->m_oldSpeed.x = pos->x - node->m_oldPosition.x;
        node->m_oldSpeed.z = pos->z - node->m_oldPosition.z;
        node->m_oldSpeed.y = pos->y - node->m_oldPosition.y;
        // BUG(original): the time is read again; a stopped clock (state 3) cannot reach here, but the
        // division would be by 0.
        const float inv = 1.0f / NodeFrameTime(node->m_sgProperties, frameClock);
        node->m_oldSpeed.z = inv * node->m_oldSpeed.z;
        node->m_oldSpeed.x = inv * node->m_oldSpeed.x;
        node->m_oldSpeed.y = inv * node->m_oldSpeed.y;
    }
    const RwV3d* pos = FramePosition(node->m_pRwFrame);
    node->m_oldPosition.x = pos->x;
    node->m_oldPosition.y = pos->y;
    node->m_oldPosition.z = pos->z;
}

// 0x000e64b0 CParticlesNodeFx_TransformEmitPointsToWorld_maybe
uint32_t CParticlesNodeFx::TransformEmitPointsToWorld(CVector3* points, uint32_t maxPoints, CVector3* dirs,
                                                      uint32_t maxDirs) {
    RpPrtAdvEmtPointList* list = m_pAdvEmtPointList;
    uint32_t count = 0;
    const CMatrix34* ltm = reinterpret_cast<const CMatrix34*>(FrameLtm(m_pRwFrame));  // node +0x04, +0x50
    if (points != nullptr) {
        count = m_ui8NbActivePoints;
        if (count > maxPoints) count = maxPoints;  // cmplw / bgt
        Mat4_TransformPoints(ltm, points, reinterpret_cast<const CVector3*>(list->pointList), static_cast<int32_t>(count));  // 0x0023f7e8
    }
    if (dirs != nullptr) {
        count = m_ui8NbActivePoints;
        if (count > maxDirs) count = maxDirs;
        Mat4_TransformVectors(ltm, dirs, reinterpret_cast<const CVector3*>(list->directionList), static_cast<int32_t>(count));  // 0x0023f7b0
    }
    return count;
}

// 0x000e6938 ParticleFxNode_StopEmitting_maybe
void CParticlesNodeFx::StopEmitting() {
    RpPrtStdEmitter* emitter = m_pRpPrtStdEmitter;
    if (emitter->prtActive == 0) return;
    RpAtomic* atomic = static_cast<CGeometry*>(m_lGeometryList)->m_pRpAtomic;
    const int32_t stdOffset = emitter->emtClass->propTab->propOffset[1];  // the standard property
    const RpPrtStdEmitterStandard* std =
        reinterpret_cast<const RpPrtStdEmitterStandard*>(reinterpret_cast<const uint8_t*>(emitter) + stdOffset);
    float deltaTime = std->prtLife + std->prtLifeBias;
    deltaTime = deltaTime + deltaTime;
    m_sgProperties &= 0xfff7fbffu;
    emitter->flag &= ~rpPRTSTDEMITTERFLAGEMIT;
    RpPrtStdAtomicUpdateAndEmit(atomic, &deltaTime);  // RW_UpdateParticleAtomic_2
    atomic->boundingSphere[3] = atomic->boundingSphere[3] + m_fBoundingRadius;
}

// 0x000e6598 CParticlesNodeFx_Destroy
void CParticlesNodeFx::Destroy() {
    ParticleUpdateScheduler* scheduler = g_pEngine->m_particleScheduler;
    scheduler->workCount = 0;
    scheduler->activeCount = 0;
    CNode::Destroy();
    m_pRpPrtStdEmitter = nullptr;
    m_pAdvEmtPointList = nullptr;
}

// C2.8 port-all P11.

// 0x000e6868 CParticlesNodeFx_MessageProc
int32_t CParticlesNodeFx::MessageProc(uint16_t message, void* data) {
    if (message == 0x1a00) {
        const uint8_t emit = *static_cast<const uint8_t*>(data);
        m_sgProperties = (m_sgProperties & 0xfff7fbffu) | (static_cast<uint32_t>(emit) << 10);
        if (emit == 0) {
            m_pRpPrtStdEmitter->flag &= 0xfffffff7u;  // the emit flag (0x8) off
            return 0;
        }
    } else if (message == 0x1a01) {
        m_sgProperties = (m_sgProperties & 0xfff7f9ffu) | 0x200u | 0x400u;
    } else {
        return 1;
    }
    m_fEmissionSpeedAdjustment = 0.0f;
    m_pRpPrtStdEmitter->flag |= rpPRTSTDEMITTERFLAGACTIVE | rpPRTSTDEMITTERFLAGEMIT;  // 0xa
    return 0;
}
