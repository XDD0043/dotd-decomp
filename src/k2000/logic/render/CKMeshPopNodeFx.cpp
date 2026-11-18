// CKMeshPopNodeFx.cpp - reconstructed original translation unit 0x1c9338-0x1cbc50 (GAME_TOC1, main_toc1), 27 functions, 25 live.
// Primary class: CKMeshPopNodeFx  key 0xa24c  category Logic  size 0x38  vtable 0xb1d3c8
// Other owners: CKParticlesEffectFxData (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x1c9338  CKMeshPopNodeFx_Delete
//   [ ] 0x1c9388  CKMeshPopNodeFx_InitMatrices_maybe  [dead]
//   [x] 0x1c9428  CKMeshPopNodeFx_SetMatrixForOwner_maybe
//   [ ] 0x1c94f8  RegisterCKMeshPopNodeFxClass
//   [ ] 0x1c9570  _GLOBAL__I_1c9570
//   [x] 0x1c9580  CKMeshPopNodeFx_ApplyAlphaCurve_maybe
//   [x] 0x1c9728  CKMeshPopNodeFx_ApplyMoveUpdater_maybe
//   [ ] 0x1c97c0  CKMeshPopNodeFx_Save
//   [x] 0x1c97e8  CKMeshPopNodeFx_RecursiveRegistration
//   [x] 0x1c98a8  CKMeshPopNodeFx_Destroy
//   [x] 0x1c9900  CKMeshPopNodeFx_DeleteArray
//   [x] 0x1c99a8  CKMeshPopNodeFx_Create
//   [x] 0x1c9a00  CKMeshPopNodeFx_SetUpDirForOwner_maybe
//   [x] 0x1c9c08  CKMeshPopNodeFx_SetPositionForOwner_maybe
//   [ ] 0x1c9c60  FUN_001c9c60  [dead]
//   [x] 0x1c9c70  CKMeshPopNodeFx_Stop
//   [x] 0x1c9d90  CKMeshPopNodeFx_PlaceWithRandomYaw_maybe
//   [x] 0x1c9f90  CKMeshPopNodeFx_CreateArray
//   [x] 0x1ca048  CKMeshPopNodeFx_Load
//   [x] 0x1ca108  CKMeshPopNodeFx_ScatterElementRandomOffset_maybe
//   [x] 0x1ca730  CKMeshPopNodeFx_Start
//   [x] 0x1ca850  CKMeshPopNodeFx_PostLoad
//   [x] 0x1ca978  CKMeshPopNodeFx_PlaceAtTarget_maybe
//   [x] 0x1caf50  CKMeshPopNodeFx_TriggerPop_maybe
//   [x] 0x1cb568  CKMeshPopNodeFx_SetActive_maybe
//   [x] 0x1cb6e8  CKMeshPopNodeFx_Update
//   [x] 0x1cbc48  CKParticlesEffectFxData_GetNodeClassKey  (CKParticlesEffectFxData's vt+0x54 in CKParticlesEffectFxData.h)
//
//   [x] 0x9acbd0  CKMeshPopNodeFx_IsKindOfClass  [inline]
//   [x] 0x9acc10  CKMeshPopNodeFx_GetClassType  [inline]
//   [x] 0x9acc18  CKMeshPopNodeFx_GetClassID  [inline]
//   [x] 0x9acc20  CKMeshPopNodeFx_GetFxData  [inline]
//   [x] 0x9acc28  CKMeshPopNodeFx_SetFxData  [inline]
//   [ ] 0x9acc30  CKMeshPopNodeFx_Destruct  [inline]
//   [ ] 0x9acc50  CKMeshPopNodeFx_DeletingDestruct  [inline]
#include "k2000/logic/render/CKMeshPopNodeFx.h"

#include <cmath>
#include <cstring>

#include "Renderware/rwcore/RwCamera.h"
#include "Renderware/rwcore/RwMatrix.h"
#include "crt/ppc_ops.h"
#include "crt/xsinf.h"
#include "k2000/components/CKCurve2DCpnt.h"
#include "k2000/components/CKMoveCpntUpdater.h"
#include "k2000/geometry/CGeometry.h"
#include "k2000/io/IKFile.h"
#include "k2000/logic/CKSavingManager.h"
#include "k2000/logic/CSGHotSpot.h"
#include "k2000/logic/render/CKMeshPopFxData.h"
#include "k2000/logic/render/CMaterial.h"
#include "k2000/misc/ClassRegistry.h"
#include "k2000/scenegraph/CSGBranch.h"
#include "k2000/misc/Engine.h"
#include "k2000/misc/Mat4.h"
#include "k2000/scenegraph/CNode.h"
#include "k2000/services/CKSrvFx.h"
#include "k2000/system/IKTime.h"

namespace {

// The game TOC floats (TOC1 -0x1cb0 .. -0x1c18).
constexpr float k65535 = 65535.0f;                       // -0x1c70
constexpr float kMinusTwo = -2.0f;                       // -0x1c28
constexpr float kRandSigned = -3.051804378628731e-05f;   // -0x1c2c (0xb8000080): u x this + 1 lies in -1..1
constexpr float kDegToRad = 0.01745329052209854f;        // -0x1c34
constexpr float kMinusDegToRad = -0.01745329052209854f;  // -0x1c30
constexpr float kTwoPi = 6.2831854820251465f;            // -0x1c1c
constexpr float kHundred = 100.0f;                       // -0x1c18

float RandU16() { return static_cast<float>(static_cast<double>(static_cast<uint32_t>(Rand_Int()) & 0xffffu)); }
// (u / 65535) x -2: fcfid, frsp, fdivs, fmuls.
float RandMinusTwo() { return (RandU16() / k65535) * kMinusTwo; }

bool SignBitSet(float x) {
    int32_t bits;
    std::memcpy(&bits, &x, 4);
    return bits < 0;
}
// The inlined cosf / sinf (as CKCameraConstraint.cpp's): the polynomials for a non-negative argument, the library's
// cosf 0x009a11d8 / sinf 0x009a1390 of the magnitude otherwise (the sine negated).
float GameCosf(float x) { return SignBitSet(x) ? crt::LibCosf(-x) : crt::InlineCosf(x); }
float GameSinf(float x) { return SignBitSet(x) ? -crt::LibSinf(-x) : crt::InlineSinf(x); }

// 0x00c50e14: the identity matrix CKGraphic_InitializeModule creates (RwMatrixCreate_Thunk) and nothing changes.
const CMatrix34& IdentityMatrix() {
    static const CMatrix34 identity = [] {
        CMatrix34 m;
        std::memset(&m, 0, sizeof m);
        m.m_right.x = 1.0f;
        m.m_up.y = 1.0f;
        m.m_at.z = 1.0f;
        m.m_ui32Flags = 0x20003u;
        return m;
    }();
    return identity;
}

// 0x0023fba8 Mat4_RotateAboutPoint_maybe: `m` turned by `angle` degrees about `axis` through `point` (the position
// moved to the point, the identity flag cleared, RwMatrixRotate post-concatenated, the position moved back).
void RotateAboutPoint(float angle, CMatrix34* m, const CVector3* point, const CVector3* axis) {
    m->m_pos.x = m->m_pos.x - point->x;
    m->m_pos.y = m->m_pos.y - point->y;
    m->m_pos.z = m->m_pos.z - point->z;
    m->m_ui32Flags = m->m_ui32Flags & 0xfffdffffu;
    RwMatrixRotate(reinterpret_cast<RwMatrix*>(m), reinterpret_cast<const RwV3d*>(axis), angle, rwCOMBINEPOSTCONCAT);
    m->m_pos.x = m->m_pos.x + point->x;
    m->m_pos.y = m->m_pos.y + point->y;
    m->m_pos.z = m->m_pos.z + point->z;
}

// The placement copy the original writes word by word (16 words).
void CopyMatrix(CMatrix34* to, const CMatrix34* from) { std::memcpy(to, from, sizeof *to); }

// The identity the Start writes into both matrices (the pads are not written).
void SetIdentityKeepPads(CMatrix34* m) {
    m->m_ui32Flags = 0x20003u;
    m->m_at.z = 1.0f;
    m->m_up.y = 1.0f;
    m->m_right.x = 1.0f;
    m->m_up.x = 0.0f;
    m->m_right.z = 0.0f;
    m->m_right.y = 0.0f;
    m->m_at.y = 0.0f;
    m->m_at.x = 0.0f;
    m->m_pos.x = 0.0f;
    m->m_up.z = 0.0f;
    m->m_pos.z = 0.0f;
    m->m_pos.y = 0.0f;
}

}  // namespace

// 0x001ca048 CKMeshPopNodeFx_Load
int32_t CKMeshPopNodeFx::Load(IKFile* file, int32_t type) {
    IKNodeFx::Load(file, type);
    if (type == K_LEVEL_PLATEFORMS) IKFile_ReadRef(file, &m_pMoveUpdater);
    return 1;
}

// The matrix the PostLoad stores: identity with flags 0x20003 (right/up/at diagonal 1.0f, the rest 0; the pads
// +0x1c/+0x2c/+0x3c are not written).
static void SetIdentityMatrixWithFlags(CMatrix34* m) {
    m->m_up.z = 0.0f;  // stw r0: the words of the original's zero stores, in the original's order
    m->m_right.z = 0.0f;
    m->m_right.y = 0.0f;
    m->m_at.y = 0.0f;
    m->m_at.x = 0.0f;
    m->m_up.x = 0.0f;
    m->m_pos.z = 0.0f;
    m->m_pos.y = 0.0f;
    m->m_pos.x = 0.0f;
    m->m_ui32Flags = 0x20003u;
    m->m_at.z = 1.0f;
    m->m_up.y = 1.0f;
    m->m_right.x = 1.0f;
}

// 0x001ca850 CKMeshPopNodeFx_PostLoad: IKNodeFx_PostLoad, the node's flags bit 2 (hidden: cleared, then set), two
// RwMatrixCreate_Thunk matrices for the level load (type 0), then both matrices identity with flags 0x20003 and
// the run-time words (TOC -0x1cb0 = 1.0f, -0x1cac = 3600.0f, -0x1ca8 = -1.0f).
int32_t CKMeshPopNodeFx::PostLoad(int32_t type) {
    IKNodeFx::PostLoad(type);
    if (m_pNode != nullptr) m_pNode->m_sgProperties = (m_pNode->m_sgProperties & 0xfffffffbu) | 4u;
    if (type == K_LEVEL_PLATEFORMS) {
        m_unk24 = RwMatrixCreate_Thunk();
        m_unk20 = RwMatrixCreate_Thunk();
    }
    m_unk1c = 0;
    m_unk2c = 0;
    SetIdentityMatrixWithFlags(m_unk24);
    SetIdentityMatrixWithFlags(m_unk20);
    m_unk34 = -1.0f;
    m_unk28 = 3600.0f;
    m_unk30 = 1.0f;
    return 1;
}

// 0x001ca730 CKMeshPopNodeFx_Start
void CKMeshPopNodeFx::Vf64() {
    m_baFxData = static_cast<uint8_t>((m_baFxData & 0xfcu) | 2u);
    m_unk1c = 0.0f;
    m_unk2c = 0.0f;
    SetIdentityKeepPads(m_unk24);
    SetIdentityKeepPads(m_unk20);
    m_unk28 = 3600.0f;
    m_unk30 = 1.0f;
    m_unk34 = -1.0f;
    if (m_pFxData == nullptr) {
        Stop();  // vt+0x6c
    } else {
        m_baFxData = static_cast<uint8_t>(m_baFxData & 0xf3u);
    }
}

// 0x001c9c70 CKMeshPopNodeFx_Stop
void CKMeshPopNodeFx::Stop() {
    m_baFxData = static_cast<uint8_t>((m_baFxData & 0xfcu) | 1u);
    if ((m_baFxData & 4u) != 0) {
        MoveUpdater()->Stop();                // 0x0024dc60
        MoveUpdater()->SetMoveCpnt(nullptr);  // 0x0024dda8
    }
    CNode* node = m_pNode;
    if (node->m_pParent != nullptr) node->m_pParent->RemoveChild(node);         // vt+0x78
    static_cast<CSGBranch*>(g_pEngine->m_dynamicSceneRoot)->AddChild(m_pNode);  // vt+0x70
    m_pNode->m_sgProperties = (m_pNode->m_sgProperties & 0xfffffffbu) | 4u;
    m_baFxData = static_cast<uint8_t>(m_baFxData & 0xf3u);
}

// 0x001c9428 CKMeshPopNodeFx_SetMatrixForOwner_maybe
void CKMeshPopNodeFx::SetMatrixForOwner(const IKSerializable* owner, const CMatrix34* matrix) {
    if (OwnedBy(owner)) CopyMatrix(m_unk20, matrix);
}

// 0x001c9c08 CKMeshPopNodeFx_SetPositionForOwner_maybe
void CKMeshPopNodeFx::SetPositionForOwner(const IKSerializable* owner, const CVector3* position) {
    if (!OwnedBy(owner)) return;
    m_unk20->m_pos = *position;
    m_unk20->m_ui32Flags = m_unk20->m_ui32Flags & 0xfffdffffu;
}

// 0x001c9d90 CKMeshPopNodeFx_PlaceWithRandomYaw_maybe
void CKMeshPopNodeFx::PlaceWithRandomYaw(const IKSerializable* owner, const CVector3* up, const CVector3* position) {
    if ((m_baFxData & 2u) == 0 || m_pOwner != owner) return;
    CMatrix34 m;
    std::memset(&m, 0, sizeof(m));
    m.m_ui32Flags = 0x20003u;
    m.m_right.x = 1.0f;  // TOC -0x1cb0
    m.m_up.y = 1.0f;
    m.m_at.z = 1.0f;
    m.m_pos = *position;
    m.m_ui32Flags &= 0xfffdffffu;
    static const CVector3 kAxisZ = {0.0f, 0.0f, 1.0f};  // TOC -0x1c74 -> 0x00c50d4c
    Mat4_BuildFromUpAndForward(&m, up, &kAxisZ);  // 0x0023ff80
    const float r = static_cast<float>(static_cast<double>(static_cast<uint32_t>(Rand_Int()) & 0xffffu));  // 0x00011500
    Mat4_RotateLocalYDeg(r / 65535.0f * 360.0f, &m);  // TOC -0x1c70 / -0x1c6c; 0x002413d0
    *m_unk20 = m;
}

// 0x001cb568 CKMeshPopNodeFx_SetActive_maybe
void CKMeshPopNodeFx::SetActive(const IKSerializable* owner, int32_t active) {
    if ((m_baFxData & 2u) == 0 || m_pOwner != owner || m_pNode == nullptr) return;
    if (active == 0) {
        if ((m_baFxData & 8u) == 0) return;
        if ((m_baFxData & 4u) == 0) {
            Stop();  // vt+0x6c
        } else {
            m_baFxData = static_cast<uint8_t>(m_baFxData & 0xf7u);
        }
        return;
    }
    if ((m_baFxData & 8u) != 0 || (m_baFxData & 4u) != 0) return;
    if (FxData()->m_unk18 == 0) {
        TriggerPop(m_pOwner, 0);
    } else {
        TriggerPop(owner, 0);
        m_baFxData = static_cast<uint8_t>((m_baFxData & 0xf7u) | 8u);
    }
    const CKMeshPopFxData* data = FxData();
    const float base = data->m_unk1c + data->m_unk20;
    const float r = RandMinusTwo();
    m_unk2c = ppc::fmadds(r, FxData()->m_unk20, base);
}

// 0x001caf50 CKMeshPopNodeFx_TriggerPop_maybe
void CKMeshPopNodeFx::TriggerPop(const IKSerializable* owner, int32_t child) {
    if ((m_baFxData & 2u) == 0 || m_pOwner != owner || m_pNode == nullptr) return;
    if ((m_baFxData & 8u) != 0 || (m_baFxData & 4u) != 0) return;
    m_baFxData = static_cast<uint8_t>((m_baFxData & 0xfbu) | 4u);
    if (child == 0) {
        const CKMeshPopFxData* data = FxData();
        const uint32_t sum = static_cast<uint32_t>(data->m_unk38) + static_cast<uint32_t>(data->m_unk3c);
        const uint32_t u = static_cast<uint32_t>(Rand_Int()) & 0xffffu;
        const uint32_t span = static_cast<uint32_t>(FxData()->m_unk3c) * 2u + 1u;
        const uint32_t count = sum - ((u * span) >> 16);
        if (count > 1u) {
            if (FxData()->m_unk4c != 0) m_unk34 = 0.0f;
            CKSrvFx* fx = static_cast<CKSrvFx*>(g_pEngine->m_srvFx);
            for (uint32_t i = 1; i != count; ++i) {
                IKFx* pooled = fx->AcquireFx(reinterpret_cast<IKFxData*>(m_pFxData), this);  // the inlined lookup
                if (pooled == nullptr) continue;
                CKMeshPopNodeFx* sibling = static_cast<CKMeshPopNodeFx*>(pooled);
                if (FxData()->m_unk4c != 0 && sibling->OwnedBy(this)) {
                    sibling->m_unk34 = (static_cast<float>(i) / static_cast<float>(count)) * kTwoPi;
                }
                if (sibling->OwnedBy(this)) CopyMatrix(sibling->m_unk20, m_unk20);
                sibling->TriggerPop(this, 1);
                sibling->ReleaseReservation(this);  // vt+0x54
            }
        }
    }
    PlaceAtTarget(owner);
    m_pNode->m_sgProperties = m_pNode->m_sgProperties & 0xfffffffbu;
    MoveUpdater()->SetMoveCpnt(reinterpret_cast<CKMoveCpnt*>(FxData()->m_unk10));  // 0x0024dda8
    MoveUpdater()->Start();                                                        // 0x0024dc98
    const float scaleBase = FxData()->m_unk40 + kHundred;
    const float r0 = RandMinusTwo();
    m_unk1c = 0.0f;
    m_unk30 = ppc::fmadds(r0, FxData()->m_unk40, scaleBase) / kHundred;
    const float lifeBase = FxData()->m_unk2c + FxData()->m_unk30;
    const float r1 = RandMinusTwo();
    m_unk28 = ppc::fmadds(r1, FxData()->m_unk30, lifeBase);
    ApplyAlphaCurve();
}

// 0x001ca978 CKMeshPopNodeFx_PlaceAtTarget_maybe
void CKMeshPopNodeFx::PlaceAtTarget(const IKSerializable* owner) {
    CNode* node = m_pNode;
    if (node->m_pParent != nullptr) node->m_pParent->RemoveChild(node);  // vt+0x78
    const CKMeshPopFxData* data = FxData();
    if (data->m_unk19 != 0) {
        static_cast<CSGBranch*>(g_pEngine->m_dynamicSceneRoot)->AddChild(m_pNode);  // vt+0x70
        if (data->m_unk08 == nullptr) {
            CSGHotSpot* hotSpot = data->m_unk0c;
            if (hotSpot != nullptr) {
                CMatrix34 world;
                hotSpot->GetWorldMatrix(&world);  // 0x000ce970 (its result is not tested)
                if (OwnedBy(owner)) CopyMatrix(m_unk20, &world);
            }
        } else if (OwnedBy(owner)) {
            CopyMatrix(m_unk20, reinterpret_cast<const CMatrix34*>(FrameLtm(data->m_unk08->m_pRwFrame)));  // frame +0x50
        }
    } else {
        if (OwnedBy(owner)) CopyMatrix(m_unk20, &IdentityMatrix());  // 0x00c50e14
        CSGBranch* parent = data->m_unk08;
        if (parent == nullptr) {
            CSGHotSpot* hotSpot = data->m_unk0c;
            if (hotSpot == nullptr) {
                static_cast<CSGBranch*>(g_pEngine->m_dynamicSceneRoot)->AddChild(m_pNode);  // vt+0x70
            } else if (hotSpot->m_pParent == nullptr) {
                Stop();  // vt+0x6c
                return;
            } else {
                hotSpot->AttachVolume(m_pNode);  // 0x000ce2b8
            }
        } else {
            parent->AddChild(m_pNode);  // vt+0x70
        }
    }
    CopyMatrix(m_unk24, m_unk20);
    ScatterElementRandomOffset(m_unk24, 2);
}

// 0x001ca108 CKMeshPopNodeFx_ScatterElementRandomOffset_maybe
void CKMeshPopNodeFx::ScatterElementRandomOffset(CMatrix34* m, int32_t mode) {
    if (mode != 1) {
        if (mode != 0 && mode != 2) return;
        float dirX;
        float dirZ;
        if (m_unk34 >= 0.0f) {
            const float spread = FxData()->m_unk50;
            float angle = ppc::fmadds(spread, kDegToRad, m_unk34);
            const float r = RandU16() / k65535;
            angle = ppc::fmadds(r + r, FxData()->m_unk50 * kMinusDegToRad, angle);
            dirX = GameCosf(angle);
            dirZ = GameSinf(angle);
        } else {
            dirX = ppc::fmadds(RandU16(), kRandSigned, 1.0f);
            dirZ = ppc::fmadds(RandU16(), kRandSigned, 1.0f);
        }
        float dirY = 0.0f;
        const float length = std::sqrt(ppc::fmadds(dirZ, dirZ, ppc::fmadds(dirX, dirX, 0.0f)));  // 0x00010690 Math_Sqrtf
        if (length != 0.0f) {
            const float inv = 1.0f / length;
            dirZ = dirZ * inv;
            dirX = dirX * inv;
            dirY = inv * 0.0f;
        }
        const CKMeshPopFxData* data = FxData();
        const float distanceBase = data->m_unk24 + data->m_unk28;
        const float r = RandMinusTwo();
        const float distance = ppc::fmadds(r, FxData()->m_unk28, distanceBase);
        const float* offset = FxData()->m_unk54;
        const float z = ppc::fmadds(distance, dirZ, m->m_pos.z);
        const float x = ppc::fmadds(distance, dirX, m->m_pos.x);
        const float y = ppc::fmadds(distance, dirY, m->m_pos.y);
        m->m_pos.z = z + offset[2];
        m->m_pos.x = x + offset[0];
        m->m_pos.y = y + offset[1];
        m->m_ui32Flags = m->m_ui32Flags & 0xfffdffffu;
        if (mode == 0) return;
        if (FxData()->m_unk44 != 0) {
            const CVector3 away = {-dirX, -dirY, -dirZ};
            Mat4_SetBasisFromAtUp(m, &away, &m->m_up);  // 0x0023fd30
        }
    }
    const CVector3 point = m->m_pos;
    const float yawRange = FxData()->m_unk48;
    const float r = RandMinusTwo();
    RotateAboutPoint(ppc::fmadds(r, FxData()->m_unk48, yawRange + 0.0f), m, &point, &m->m_up);  // 0x0023fba8
    CVector3 axis;
    axis.y = 0.0f;
    axis.x = ppc::fmadds(RandU16(), kRandSigned, 1.0f);
    const float xx = ppc::fmadds(axis.x, axis.x, axis.y * axis.y);
    axis.z = ppc::fmadds(RandU16(), kRandSigned, 1.0f);
    const float length = std::sqrt(ppc::fmadds(axis.z, axis.z, xx));  // 0x00010690 Math_Sqrtf
    if (length != 0.0f) {
        const float inv = 1.0f / length;
        axis.z = axis.z * inv;
        axis.x = axis.x * inv;
        axis.y = axis.y * inv;
    }
    const float tilt = (RandU16() / k65535) * FxData()->m_unk34;
    RotateAboutPoint(tilt, m, &point, &axis);
}

// 0x001c9580 CKMeshPopNodeFx_ApplyAlphaCurve_maybe
void CKMeshPopNodeFx::ApplyAlphaCurve() {
    const CKMeshPopFxData* data = FxData();
    const float x = (data->m_unk2c / m_unk28) * m_unk1c;
    const float y = static_cast<const CKCurve2DCpnt*>(data->m_unk14)->Evaluate(x);  // 0x00249ea8
    const uint8_t alpha = static_cast<uint8_t>(ppc::fctiwz(y));
    CGeometry* geometry = static_cast<CGeometry*>(m_pNode->m_lGeometryList);
    for (; geometry != nullptr; geometry = geometry->m_pNext) {
        uint8_t value = alpha;
        uint32_t transparent = 1;
        if (alpha == 0xff) {
            transparent = 0;
        } else if ((geometry->m_BitProperties & 0x1000u) != 0) {
            const uint32_t blend = (static_cast<const CMaterial*>(geometry->m_pMaterial)->m_baProperties >> 3) & 0xfu;
            if (blend != 0 && blend <= 6) {
                transparent = 0;
                value = 0xff;
            }
        }
        geometry->m_cGeometryColor[3] = value;
        if (((geometry->m_BitProperties >> 11) & 1u) != transparent) {
            geometry->m_BitProperties = (geometry->m_BitProperties & 0xfffff7ffu) | (transparent << 11);
            geometry->UpdateProperties();  // vt+0x60
        }
    }
}

// 0x001cb6e8 CKMeshPopNodeFx_Update
void CKMeshPopNodeFx::Update(IKTime* frameClock) {
    const float dt = frameClock->m_afDeltaTime[0];
    m_unk1c = m_unk1c + dt;
    if ((m_baFxData & 4u) != 0) {
        if (MoveUpdater()->m_bRunning == 0 || m_unk28 <= m_unk1c) {
            if ((m_baFxData & 8u) == 0) {
                Stop();  // vt+0x6c
            } else {
                MoveUpdater()->Stop();
                MoveUpdater()->SetMoveCpnt(nullptr);
                m_pNode->m_sgProperties = (m_pNode->m_sgProperties & 0xfffffffbu) | 4u;
                m_baFxData = static_cast<uint8_t>(m_baFxData & 0xfbu);
            }
        } else {
            m_pNode->SetLocalMatrix(reinterpret_cast<const RwMatrix*>(m_unk24));  // 0x000d0be8
            float sample[10];
            MoveUpdater()->Evaluate(dt, sample);  // 0x0024db60
            const float scale = m_unk30;
            sample[7] = ppc::fmsubs(sample[7] + 1.0f, scale, 1.0f);
            sample[8] = ppc::fmsubs(sample[8] + 1.0f, scale, 1.0f);
            sample[9] = ppc::fmsubs(sample[9] + 1.0f, scale, 1.0f);
            MoveUpdater()->ApplyToNode(sample, m_pNode);  // 0x0024d9c0
            ApplyAlphaCurve();
        }
    }
    if ((m_baFxData & 8u) == 0) return;
    m_unk2c = m_unk2c - dt;
    if (0.0f < m_unk2c) return;
    CKSrvFx* fx = static_cast<CKSrvFx*>(g_pEngine->m_srvFx);
    IKFx* pooled = fx->AcquireFx(reinterpret_cast<IKFxData*>(m_pFxData), this);  // the inlined lookup
    if (pooled != nullptr) {
        CKMeshPopNodeFx* sibling = static_cast<CKMeshPopNodeFx*>(pooled);
        if (sibling->OwnedBy(this)) CopyMatrix(sibling->m_unk20, m_unk20);
        sibling->TriggerPop(this, 0);
        sibling->ReleaseReservation(this);  // vt+0x54
    }
    const CKMeshPopFxData* data = FxData();
    const float base = data->m_unk1c + data->m_unk20;
    const float r = RandMinusTwo();
    m_unk2c = ppc::fmadds(r, FxData()->m_unk20, base);
}

// 0x001c97e8 CKMeshPopNodeFx_RecursiveRegistration
void CKMeshPopNodeFx::RecursiveRegistration(int32_t type) {
    g_pEngine->m_pSavingManager->RegisterSerializableObject(this, nullptr);  // vt+0x24
    IKNodeFx::RecursiveRegistration(type);  // 0x001d88c0
    if (type == 0) m_pMoveUpdater->RecursiveRegistration(0);  // vt+0x24
}

// 0x001c98a8 CKMeshPopNodeFx_Destroy (RwMatrixDestroy_Thunk twice)
void CKMeshPopNodeFx::Destroy() {
    RwMatrixDestroy_Thunk(m_unk24);  // 0x0023f968
    m_unk24 = nullptr;
    RwMatrixDestroy_Thunk(m_unk20);
    m_unk20 = nullptr;
}

// 0x001c9728 CKMeshPopNodeFx_ApplyMoveUpdater_maybe (fadds, then fmsubs with the pop's scale)
void CKMeshPopNodeFx::ApplyMoveUpdater(IKTime* frameClock) {
    float sample[10];
    MoveUpdater()->Evaluate(frameClock->m_afDeltaTime[0], sample);  // 0x0024db60
    const float scale = m_unk30;
    sample[7] = ppc::fmsubs(sample[7] + 1.0f, scale, 1.0f);
    sample[8] = ppc::fmsubs(sample[8] + 1.0f, scale, 1.0f);
    sample[9] = ppc::fmsubs(sample[9] + 1.0f, scale, 1.0f);
    MoveUpdater()->ApplyToNode(sample, m_pNode);  // 0x0024d9c0
}

// 0x001c9a00 CKMeshPopNodeFx_SetUpDirForOwner_maybe
void CKMeshPopNodeFx::SetUpDirForOwner(const IKSerializable* owner, const CVector3* up) {
    if ((m_baFxData & 2u) == 0 || m_pOwner != owner) return;
    CMatrix34 m;
    std::memset(&m, 0, sizeof(m));
    m.m_ui32Flags = 0x20003u;
    m.m_right.x = 1.0f;  // TOC -0x1cb0
    m.m_up.y = 1.0f;
    m.m_at.z = 1.0f;
    m.m_pos = m_unk24->m_pos;
    m.m_ui32Flags &= 0xfffdffffu;
    static const CVector3 kAxisZ = {0.0f, 0.0f, 1.0f};  // TOC -0x1c74 -> 0x00c50d4c
    Mat4_BuildFromUpAndForward(&m, up, &kAxisZ);  // 0x0023ff80
    const float r = static_cast<float>(static_cast<double>(static_cast<uint32_t>(Rand_Int()) & 0xffffu));  // 0x00011500
    Mat4_RotateLocalYDeg(r / 65535.0f * 360.0f, &m);  // TOC -0x1c70 / -0x1c6c; 0x002413d0
    *m_unk20 = m;
}
