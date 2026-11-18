// CTrailNodeFx.cpp - reconstructed original translation unit 0xea630-0xec920 (GAME_TOC1, main_toc1), 17 functions, 16 live.
// Primary class: CTrailNodeFx  key 0x6cb  category SceneNode  size 0x38  vtable 0xb18c38
// Other owners: TrailStrip (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [ ] 0xea630  RegisterCTrailNodeFxClass
//   [ ] 0xea6a8  _GLOBAL__I_ea6a8
//   [ ] 0xea6b8  CTrailNodeFx_AllocPointBuffers_maybe  [dead]
//   [x] 0xea8c0  CTrailNodeFx_RecursiveRegistration  (INodeFx's (returns 1, registers nothing): CSGLeaf's)
//   [x] 0xea8e8  CTrailNodeFx_DeleteArray
//   [x] 0xea990  CTrailNodeFx_Create
//   [x] 0xea9f0  CTrailNodeFx_Destroy
//   [x] 0xeaad8  CTrailNodeFx_CreateArray
//   [x] 0xeabb0  TrailStrip_ResetPointsBetweenAnchors_maybe
//   [ ] 0xeae78  CTrailNodeFx_UpdateAnchorPoints_maybe  [dead: only its descriptor at 0xb52f70, never referenced;  [dead: no pointer to its descriptor 0xb52f70]
//                SetRibbonActive inlines the same layout for one ribbon]
//   [x] 0xeb2d8  CTrailNodeFx_LoadPart
//   [x] 0xeb5f0  CTrailNodeFx_Load
//   [x] 0xeb7b0  CTrailNodeFx_UpdateTrailGeometry_maybe
//   [x] 0xec240  CTrailNodeFx_Enqueue
//   [ ] 0xec320  CTrailNodeFx_SaveSegment_maybe  [left: save-only: called only by CTrailNodeFx_Save 0xec6d0 (the saves are out of scope)]
//   [ ] 0xec610  CTrailNodeFx_Save
//   [x] 0xec708  CTrailNodeFx_PostLoad
//
//   [ ] 0x9a5628  CTrailNodeFx_IsKindOfClass  [inline]
//   [ ] 0x9a5688  CTrailNodeFx_GetClassType  [inline]
//   [ ] 0x9a5690  CTrailNodeFx_GetClassID  [inline]
//   [ ] 0x9a5698  CTrailNodeFx_DeletingDestructor  [inline]
//   [ ] 0x9a56f0  CTrailNodeFx_Destructor  [inline]
//   [x] 0x9bdfb8  CTrailNodeFx_SetRibbonActive_maybe  [inline]
//   [ ] 0x9be780  KStub_Return12_9be780  [inline]
//   [ ] 0x9be788  KStub_Return674_9be788  [inline]
#include "k2000/scenegraph/CTrailNodeFx.h"

#include <cmath>
#include <cstring>

#include "crt/ppc_ops.h"
#include "k2000/geometry/CGeometry.h"
#include "k2000/io/IKFile.h"
#include "k2000/logic/CSGHotSpot.h"
#include "k2000/math/Vec3.h"
#include "k2000/memory/Mem.h"
#include "k2000/misc/Mat4.h"
#include "k2000/scenegraph/CAnimatedNode.h"
#include "k2000/system/IKTime.h"
#include "Renderware/rpworld/RpAtomic.h"
#include "Renderware/rpworld/RpGeometry.h"
#include "Renderware/rwcore/RwCamera.h"

namespace {

// 0x00c50d64 (TOC1 -0x4df4): the null vector (zero in the EBOOT's BSS; a static initialiser fills it).
const CVector3 kNullVector = {0.0f, 0.0f, 0.0f};
constexpr float kOne = 1.0f;                 // TOC1 -0x4df0
constexpr float kZero = 0.0f;                // TOC1 -0x4dec
constexpr float kSphereRadius = 300000.0f;   // TOC1 -0x4de0 (0x48927c00)

// The scene flags' anchor mode (bits 9-10).
uint32_t AnchorMode(uint32_t flags) { return (flags >> 9) & 3u; }

// 0x00010690 Math_Sqrtf (fsqrts).
float Sqrtf(float x) { return std::sqrt(x); }

// The unsigned word converted as the original does it (fcfid of the zero-extended value, frsp).
float ToFloat(uint32_t value) { return static_cast<float>(static_cast<double>(value)); }

// The control point of strip `strip`, place `place`.
CVector3& Point(STrailNodeData* trail, uint32_t index) { return trail->m_pCtrlPoints[index]; }

// The direction and step from `a` to `b` over the strips: `step` = |b - a| / (strips - 1) along the normalised
// direction (left as it is when the length is 0).
void StripStep(const CVector3& a, const CVector3& b, uint32_t strips, float* sx, float* sy, float* sz) {
    float dy = b.y - a.y;
    float dx = b.x - a.x;
    float dz = b.z - a.z;
    const float length2 = ppc::fmadds(dz, dz, ppc::fmadds(dx, dx, dy * dy));
    const float step = Sqrtf(length2) / ToFloat(strips - 1u);
    const float length = Sqrtf(length2);
    if (length != kZero) {
        const float inverse = kOne / length;
        dz = dz * inverse;
        dx = dx * inverse;
        dy = dy * inverse;
    }
    *sz = dz * step;
    *sx = step * dx;
    *sy = step * dy;
}

}  // namespace

// 0x000eb2d8 CTrailNodeFx_LoadPart
void CTrailNodeFx::LoadTrail(uint32_t /*index*/, STrailNodeData* trail, IKFile* file, int32_t type) {
    if (type == K_LEVEL_PLATEFORMS) {
        ReadRaw(file, &trail->m_ui8Extrem1, 1);
        ReadRaw(file, &trail->m_ui8Extrem2, 1);
        ReadRaw(file, trail->m_cColor, 4);  // not swapped
        IKFile_ReadRef(file, &trail->m_pHotSpot1);
        IKFile_ReadRef(file, &trail->m_pHotSpot2);
        ReadU32LE(file, &trail->m_ui32NbCtrPoints);
        ReadU32LE(file, &trail->m_ui32NbLineVertex);
        ReadF32LE(file, &trail->m_unk44);
        ReadU32LE(file, &trail->m_unk38);
        ReadU32LE(file, &trail->m_unk34);
    }
    trail->m_ui8Visible = 0;
    trail->m_pCtrlPoints = nullptr;
    trail->m_ba8Properties = 0;
}

// 0x000eb5f0 CTrailNodeFx_Load
int32_t CTrailNodeFx::Load(IKFile* file, int32_t type) {
    INodeFx::Load(file, type);  // 0xeccd8
    if (type != K_LEVEL_PLATEFORMS) return 1;
    m_pTrailCtrlPoints = nullptr;
    ReadU32LE(file, &m_ui32NbTrail);
    if (m_ui32NbTrail == 0) {
        m_apTrailData = nullptr;
        return 1;
    }
    m_apTrailData = static_cast<STrailNodeData**>(Mem_AllocAligned16(m_ui32NbTrail * sizeof(STrailNodeData*)));
    // The loop counter is a byte (rlwinm 0xff): more than 255 trails would never end. Each trail block is
    // Mem_AllocAligned16(m_ui32NbTrail * 100), sized by the trail count rather than the 0x64-byte struct
    // (as the original). DOTD: at least the native struct (0x70 bytes on 64-bit hosts).
    uint32_t bytes = m_ui32NbTrail * 100u;
    if (bytes < sizeof(STrailNodeData)) bytes = static_cast<uint32_t>(sizeof(STrailNodeData));
    uint32_t index = 0;
    do {
        STrailNodeData* trail = static_cast<STrailNodeData*>(Mem_AllocAligned16(bytes));
        m_apTrailData[index] = trail;
        LoadTrail(index, trail, file, K_LEVEL_PLATEFORMS);
        index = (index + 1) & 0xff;
    } while (index < m_ui32NbTrail);
    return 1;
}

// 0x000ec708 CTrailNodeFx_PostLoad
int32_t CTrailNodeFx::PostLoad(int32_t type) {
    INodeFx::PostLoad(type);  // 0xeca78
    const uint32_t count = m_ui32NbTrail;
    STrailNodeData** trails = m_apTrailData;
    if (count == 0) {
        m_pTrailCtrlPoints = nullptr;
        return 1;
    }
    uint32_t total = 0;
    for (uint32_t i = 0; i < count; ++i) total += trails[i]->m_unk34 * trails[i]->m_ui32NbCtrPoints;
    m_pTrailCtrlPoints = static_cast<CVector3*>(Mem_AllocAligned16((total * 12u) & 0xfffffffcu));  // 0x00053198
    for (uint32_t i = 0; i < total; ++i) m_pTrailCtrlPoints[i] = kNullVector;
    CVector3* points = m_pTrailCtrlPoints;
    for (uint32_t i = 0; i < count; ++i) {
        STrailNodeData* trail = trails[i];
        trail->m_pCtrlPoints = points;
        trail->m_unk48 = 0.0f;  // an integer 0 store
        trail->m_unk4c = kNullVector;
        trail->m_unk58 = kNullVector;
        points += trail->m_unk34 * trail->m_ui32NbCtrPoints;
        trail->m_v3Extrem1 = kNullVector;
        trail->m_v3Extrem2 = kNullVector;
    }
    return 1;
}

// 0x000ea9f0 CTrailNodeFx_Destroy
void CTrailNodeFx::Destroy() {
    CNode::Destroy();  // 0xcbe10
    for (uint32_t i = 0; i < m_ui32NbTrail; ++i) {
        Mem_FreeAligned16(m_apTrailData[i]);  // 0x00052fb8
        m_apTrailData[i] = nullptr;
    }
    if (m_pTrailCtrlPoints != nullptr) {
        Mem_FreeAligned16(m_pTrailCtrlPoints);
        m_pTrailCtrlPoints = nullptr;
    }
    if (m_apTrailData != nullptr) {
        Mem_FreeAligned16(m_apTrailData);
        m_apTrailData = nullptr;
    }
}

// 0x009bdfb8 CTrailNodeFx_SetRibbonActive_maybe
void CTrailNodeFx::SetRibbonActive(uint32_t ribbon, uint32_t active, int32_t resetGeometry) {
    STrailNodeData* trail = m_apTrailData[ribbon];
    if (active == (trail->m_ba8Properties & 1u)) return;
    trail->m_ba8Properties = static_cast<uint8_t>((trail->m_ba8Properties & 0xfeu) | active);
    trail->m_ui8Visible = static_cast<uint8_t>(trail->m_ui32NbCtrPoints);
    if (active == 0 && resetGeometry == 0) return;
    // The two anchors (mode 0: the parent's bones through its frame's LTM).
    CVector3 a = kNullVector;
    CVector3 b = kNullVector;
    switch (AnchorMode(m_sgProperties)) {
    case 0: {
        CAnimatedNode* parent = static_cast<CAnimatedNode*>(static_cast<CSGLeaf*>(m_pParent));
        const RwMatrix* bone = parent->GetBoneMatrix(trail->m_ui8Extrem1);  // 0x000c8bd8
        a = {bone->pos.x, bone->pos.y, bone->pos.z};
        Mat4_TransformPoints(reinterpret_cast<const CMatrix34*>(&parent->m_pRwFrame->ltm), &a, &a, 1);  // 0x0023f7e8
        bone = parent->GetBoneMatrix(trail->m_ui8Extrem2);
        b = {bone->pos.x, bone->pos.y, bone->pos.z};
        Mat4_TransformPoints(reinterpret_cast<const CMatrix34*>(&parent->m_pRwFrame->ltm), &b, &b, 1);
        break;
    }
    case 1:
        a = trail->m_v3Extrem1;
        b = trail->m_v3Extrem2;
        break;
    case 2:
        trail->m_pHotSpot1->GetWorldPosition(&a);  // 0x000ce790
        trail->m_pHotSpot2->GetWorldPosition(&b);
        break;
    default:
        break;
    }
    const uint32_t places = trail->m_ui32NbCtrPoints;
    if (places != 0) {
        uint32_t place = 0;  // a byte counter
        do {
            Point(trail, place) = a;
            Point(trail, (trail->m_unk34 - 1u) * trail->m_ui32NbCtrPoints + place) = b;
            place = (place + 1u) & 0xffu;
        } while (place < trail->m_ui32NbCtrPoints);
    }
    float sx, sy, sz;
    StripStep(a, b, trail->m_unk34, &sx, &sy, &sz);
    // The strips between: every point one step past the previous strip's first point (byte counters).
    if (trail->m_unk34 - 1u > 1u) {
        uint32_t strip = 1;
        do {
            const uint32_t n = trail->m_ui32NbCtrPoints;
            if (n != 0) {
                uint32_t place = 0;
                do {
                    CVector3& p = Point(trail, strip * trail->m_ui32NbCtrPoints + place);
                    p = Point(trail, (strip - 1u) * trail->m_ui32NbCtrPoints);
                    p.x = sx + p.x;
                    p.y = sy + p.y;
                    p.z = sz + p.z;
                    place = (place + 1u) & 0xffu;
                } while (place < trail->m_ui32NbCtrPoints);
            }
            strip = (strip + 1u) & 0xffu;
        } while (strip < trail->m_unk34 - 1u);
    }
}

// 0x000eabb0 TrailStrip_ResetPointsBetweenAnchors_maybe
void CTrailNodeFx::ResetPointsBetweenAnchors(STrailNodeData* trail) {
    CVector3& first = Point(trail, 0);
    CVector3& last = Point(trail, (trail->m_unk34 - 1u) * trail->m_ui32NbCtrPoints);
    switch (AnchorMode(m_sgProperties)) {
    case 1:
        first = trail->m_v3Extrem1;
        last = trail->m_v3Extrem2;
        break;
    case 2:
        trail->m_pHotSpot1->GetWorldPosition(&first);  // 0x000ce790
        trail->m_pHotSpot2->GetWorldPosition(&last);
        break;
    case 0: {
        CAnimatedNode* parent = static_cast<CAnimatedNode*>(static_cast<CSGLeaf*>(m_pParent));
        const RwMatrix* bone = parent->GetBoneMatrix(trail->m_ui8Extrem1);  // 0x000c8bd8
        first = {bone->pos.x, bone->pos.y, bone->pos.z};
        bone = parent->GetBoneMatrix(trail->m_ui8Extrem2);
        last = {bone->pos.x, bone->pos.y, bone->pos.z};
        break;
    }
    default:
        break;
    }
    float sx, sy, sz;
    StripStep(first, last, trail->m_unk34, &sx, &sy, &sz);
    for (uint32_t strip = 1; trail->m_unk34 - 1u > 1u && strip < trail->m_unk34 - 1u; ++strip) {
        CVector3& p = Point(trail, strip * trail->m_ui32NbCtrPoints);
        p = Point(trail, (strip - 1u) * trail->m_ui32NbCtrPoints);
        p.x = sx + p.x;
        p.y = sy + p.y;
        p.z = sz + p.z;
    }
}

namespace {

// Every strip's points one place back (the last one dropped), the first place left as it was.
void ShiftStrips(STrailNodeData* trail) {
    for (uint32_t strip = 0; strip < trail->m_unk34; ++strip) {
        const uint32_t n = trail->m_ui32NbCtrPoints;
        for (uint32_t i = (strip + 1u) * n - 1u; strip * trail->m_ui32NbCtrPoints < i; --i) {
            trail->m_pCtrlPoints[i] = trail->m_pCtrlPoints[i - 1u];
        }
    }
}

// The last `hidden` points of every strip onto the last visible one.
void CollapseTail(STrailNodeData* trail, uint32_t hidden) {
    for (uint32_t strip = 0; strip < trail->m_unk34; ++strip) {
        const CVector3 p = trail->m_pCtrlPoints[(strip + 1u) * trail->m_ui32NbCtrPoints - hidden - 1u];
        for (uint32_t k = 0; k < hidden; ++k) trail->m_pCtrlPoints[(strip + 1u) * trail->m_ui32NbCtrPoints - k - 1u] = p;
    }
}

}  // namespace

// 0x000eb7b0 CTrailNodeFx_UpdateTrailGeometry_maybe
uint8_t CTrailNodeFx::UpdateTrailGeometry(IKTime* frameClock) {
    const uint32_t count = m_ui32NbTrail;
    STrailNodeData** trails = m_apTrailData;
    CGeometry* geometry = static_cast<CGeometry*>(m_lGeometryList);
    uint8_t colourChanged = 0;
    uint8_t rebuilt = 0;
    if (count != 0) {
        for (uint32_t i = 0; i < count; ++i) {
            STrailNodeData* trail = trails[i];
            const uint8_t properties = trail->m_ba8Properties;
            if ((properties & 2u) != 0) colourChanged = 1;
            if ((properties & 1u) != 0) {
                // On: every period the points move one place back and the newest one is laid out again.
                trail->m_unk48 = trail->m_unk48 + frameClock->m_afDeltaTime[0];
                if (!(trail->m_unk48 >= trail->m_unk44)) {
                    ResetPointsBetweenAnchors(trail);
                } else {
                    do {
                        trail->m_unk48 = trail->m_unk48 - trail->m_unk44;
                        ShiftStrips(trail);
                        ResetPointsBetweenAnchors(trail);
                        trail->m_unk4c = Point(trail, trail->m_ui32NbCtrPoints - 1u);
                        trail->m_unk58 = Point(trail, trail->m_ui32NbCtrPoints * trail->m_unk34 - 1u);
                    } while (trail->m_unk48 >= trail->m_unk44);
                }
                rebuilt = 1;
            } else if (trail->m_ui8Visible != 0) {
                // Off and still visible: one point fewer every period, the hidden ones on the last visible one.
                trail->m_unk48 = trail->m_unk48 + frameClock->m_afDeltaTime[0];
                const uint32_t hiddenAtStart = trail->m_ui32NbCtrPoints - trail->m_ui8Visible;
                if (!(trail->m_unk48 >= trail->m_unk44)) {
                    ResetPointsBetweenAnchors(trail);
                    const uint32_t n = trail->m_ui32NbCtrPoints;
                    if (n > 2u && n - 2u > hiddenAtStart) CollapseTail(trail, n - trail->m_ui8Visible);
                } else {
                    while (trail->m_ui8Visible != 0) {
                        trail->m_unk48 = trail->m_unk48 - trail->m_unk44;
                        ShiftStrips(trail);
                        ResetPointsBetweenAnchors(trail);
                        CollapseTail(trail, trail->m_ui32NbCtrPoints - trail->m_ui8Visible);
                        trail->m_ui8Visible = static_cast<uint8_t>(trail->m_ui8Visible - 1);
                        trail->m_unk4c = Point(trail, trail->m_ui32NbCtrPoints - hiddenAtStart - 1u);
                        trail->m_unk58 = Point(trail, trail->m_ui32NbCtrPoints * trail->m_unk34 - hiddenAtStart - 1u);
                        if (!(trail->m_unk48 >= trail->m_unk44)) break;
                    }
                }
                rebuilt = 1;
            }
        }
        if (rebuilt != 0) {
            RpGeometry* rpGeometry = geometry->m_pRpAtomic->geometry;
            RwRGBA* colours = nullptr;
            if (colourChanged != 0) {
                RpGeometryLock(rpGeometry, 0x1a);  // TocBridge 0x98ec90: vertices, pre-lit colours, texture coordinates
                colours = geometry->m_pRpAtomic->geometry->preLitLum;
            } else {
                RpGeometryLock(rpGeometry, 0x12);  // vertices, texture coordinates
            }
            rpGeometry = geometry->m_pRpAtomic->geometry;
            RwTexCoords* texCoords = rpGeometry->texCoords[0];
            CVector3* vertices = reinterpret_cast<CVector3*>(rpGeometry->morphTarget->verts);
            uint32_t texBase = 0;
            for (uint32_t i = 0; i < count; ++i) {
                STrailNodeData* trail = trails[i];
                if (AnchorMode(m_sgProperties) == 0) {
                    // The bones' points into the world (the first strip's points only: the count is one strip's).
                    Mat4_TransformPoints(reinterpret_cast<const CMatrix34*>(&static_cast<CSGLeaf*>(m_pParent)->m_pRwFrame->ltm),
                                         trail->m_pCtrlPoints, trail->m_pCtrlPoints,
                                         static_cast<int32_t>(trail->m_ui32NbCtrPoints));  // 0x0023f7e8
                }
                if ((trail->m_ba8Properties & 2u) != 0) {
                    for (uint32_t n = 0; n < trail->m_ui32NbLineVertex; ++n) std::memcpy(colours++, trail->m_cColor, 4);
                    trail->m_ba8Properties = static_cast<uint8_t>(trail->m_ba8Properties & 0xfdu);
                }
                if (trail->m_ui8Visible == 0) {
                    // Nothing visible: every vertex of a strip on its first one.
                    for (uint32_t strip = 0; strip < trail->m_unk34; ++strip) {
                        for (uint32_t k = 0; k < trail->m_unk38; ++k) {
                            vertices[strip * trail->m_unk38 + k] = vertices[strip * trail->m_unk38];
                        }
                    }
                } else {
                    for (uint32_t strip = 0; strip < trail->m_unk34; ++strip) {
                        Bezier_SampleCurvePoints(static_cast<int32_t>(trail->m_ui32NbCtrPoints),
                                                 trail->m_pCtrlPoints + strip * trail->m_ui32NbCtrPoints,
                                                 static_cast<int32_t>(trail->m_unk38),
                                                 vertices + strip * trail->m_unk38);  // 0x00010b68
                    }
                }
                if (trail->m_unk38 > 2u) {
                    // u along the strip (the first step scaled by the time since the points moved, the others whole,
                    // at most 1), v across the strips.
                    const uint32_t strips = trail->m_unk34;
                    const float phase = trail->m_unk48 / trail->m_unk44;
                    const float du = kOne / ToFloat(trail->m_unk38 - 1u);
                    const float dv = kOne / static_cast<float>(static_cast<double>(static_cast<int64_t>(strips) - 1));
                    if (strips != 0) {
                        float v = kZero;
                        uint32_t strip = 0;
                        for (;;) {
                            float u = kZero;
                            uint32_t k = 0;
                            while (k < trail->m_unk38) {
                                const uint32_t index = strip * trail->m_unk38 + texBase + k;
                                // PORT: the original also writes past the array (see the BUG below); those writes
                                // are dropped here.
                                if (static_cast<int32_t>(index) < rpGeometry->numVertices) {
                                    RwTexCoords& t = texCoords[index];
                                    t.u = u;
                                    t.v = v;
                                }
                                if (k == 0) {
                                    u = ppc::fmadds(du, phase, u);
                                } else {
                                    u = u + du;
                                    if (u > kOne) u = kOne;  // ble: !(u > 1)
                                }
                                ++k;
                            }
                            if (++strip == strips) break;
                            v = v + dv;
                        }
                    }
                    // BUG(original): the next ribbon's texture coordinates start twice this ribbon's vertices on (the
                    // count is added here and again below), so a node's later ribbons write past their own (LVL010:
                    // 28 of the 81 trail nodes hold 2 to 12 ribbons).
                    texBase += trail->m_ui32NbLineVertex;
                }
                if (i + 1u == count) break;
                texBase += trail->m_ui32NbLineVertex;
                vertices += trail->m_ui32NbLineVertex;
            }
            geometry->UnlockGeometry();  // 0x00088530
        }
        if (geometry != nullptr) {
            // The atomic always drawn: its bounding sphere at the parent, 300000 wide.
            RpAtomic* atomic = geometry->m_pRpAtomic;
            const RwFrame* parentFrame = static_cast<CSGLeaf*>(m_pParent)->m_pRwFrame;
            if ((atomic->flags & 2u) != 0) {
                _rpAtomicResyncInterpolatedSphere(atomic);  // TocBridge 0x98e090
                atomic = geometry->m_pRpAtomic;
            }
            atomic->boundingSphere[0] = parentFrame->ltm.pos.x;
            atomic->boundingSphere[1] = parentFrame->ltm.pos.y;
            atomic->boundingSphere[2] = parentFrame->ltm.pos.z;
            atomic->boundingSphere[3] = kSphereRadius;
            geometry->m_pRpAtomic->flags &= ~2u;
            geometry->m_pRpAtomic->privateFlags = static_cast<uint8_t>(geometry->m_pRpAtomic->privateFlags | 1u);
        }
    }
    // The node's own LTM the identity (the vertices are in the world), its LTM sync bit (4) cleared.
    RwFrame* frame = m_pRwFrame;
    RwMatrix& ltm = frame->ltm;
    ltm.flags = 0x20003u;
    ltm.right.x = kOne;
    ltm.pos.x = 0.0f;
    ltm.at.z = kOne;
    ltm.up.y = kOne;
    ltm.up.x = 0.0f;
    ltm.right.z = 0.0f;
    ltm.right.y = 0.0f;
    ltm.at.y = 0.0f;
    ltm.at.x = 0.0f;
    ltm.up.z = 0.0f;
    ltm.pos.z = 0.0f;
    ltm.pos.y = 0.0f;
    frame->object.privateFlags = static_cast<RwUInt8>(frame->object.privateFlags & 0xfbu);
    frame->dotdLtmOwned = 1;  // DOTD: RW's sync leaves the written LTM alone (see CAnimatedNode.cpp)
    return rebuilt;
}

// 0x000ec240 CTrailNodeFx_Enqueue
void CTrailNodeFx::UpdateAndExtract(float /*maxDistanceSquared*/, RenderQueue** stages, IKTime* frameClock,
                                    RwCamera* camera, int32_t /*distanceCull*/) {
    if ((m_sgProperties & 4u) != 0) return;
    if (frameClock->m_eCurrentState != 0) return;
    if (UpdateTrailGeometry(frameClock) == 0) return;
    CullAndEnqueueGeometry(stages, frameClock, camera);  // vt+0x84 0x000cc460
}
