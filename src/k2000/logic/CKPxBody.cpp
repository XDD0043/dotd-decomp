// Reconstructed original translation unit: 0x2182d0-0x21ae38 (GAME_TOC1, main_toc1), 22 functions, 22 live.
// Primary class: CKPxBody  key 0x498c  category Logic  size 0x12c  vtable 0xb1fe18
// Other owners: CKPxKinematic (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x2182d0  CKPxBody_Delete  (DOTD_DECLARE_FACTORIES)
//   [ ] 0x218320  RegisterCKPxBodyClass
//   [ ] 0x218398  _GLOBAL__I_218398
//   [ ] 0x2183a8  CKPxBody_Save
//   [x] 0x2183d0  CKPxBody_RecursiveRegistration  (RecursiveRegistration: the header)
//   [x] 0x2183f8  CKPxBody_Destroy
//   [x] 0x218528  CKPxBody_Construct  (the constructor)
//   [x] 0x218598  CKPxBody_DeleteArray  (DOTD_DECLARE_FACTORIES)
//   [x] 0x218638  CKPxKinematic_ConstructBase_maybe  (CKPxBody's constructor: the same stores)
//   [x] 0x2186a8  CKPxBody_vf60  (Translate)
//   [x] 0x218790  CKPxBody_RecordSampleAndUpdateShapes_maybe  (RecordSampleAndUpdateShapes)
//   [x] 0x218b80  CKPxBody_BaseDestructor  (the destructor)
//   [x] 0x218c08  CKPxBody_DeletingDestructor  (the destructor, then delete)
//   [x] 0x218c98  CKPxBody_Destructor  (the destructor)
//   [x] 0x218d20  CKPxBody_CreateArray  (DOTD_DECLARE_FACTORIES)
//   [x] 0x218e20  CKPxBody_Create  (DOTD_DECLARE_FACTORIES: the constructor)
//   [x] 0x218ea8  CKPxBody_Integrate_maybe  (Integrate / IntegrateCommon)
//   [x] 0x2199e8  CKPxBody_ApplyTransform_maybe  (ApplyTransform)
//   [x] 0x219b30  CKPxBody_SyncFromNode_maybe  (SyncFromNode)
//   [x] 0x219c70  CKPxBody_SetWorldMatrix_maybe  (SetWorldMatrix)
//   [x] 0x219e50  CKPxBody_UpdateInertiaTensor_maybe  (UpdateInertiaTensor)
//   [x] 0x21a298  CKPxBody_Load
//
//   [x] 0x9b2b60  CKPxBody_IsKindOfClass  [inline]  (the header)
//   [x] 0x9b2b88  CKPxBody_GetClassType  [inline]  (DOTD_CLASS_KEY)
//   [x] 0x9b2b90  CKPxBody_GetClassID  [inline]  (DOTD_CLASS_KEY)
//   [x] 0x9b2b98  CKPxBody_CreateRuntimeState_maybe  [inline]  (CreateRuntimeState)
//   [x] 0x9b2cb8  CKPxBody_SyncNodeFromBody_maybe  [inline]  (SyncNodeFromBody)
//   [x] 0x9b2d18  CKPxBody_ExportState  [inline]  (ExportState)
//   [x] 0x9b2f78  CKPxBody_vf58  [inline]  (AddVelocity)
//   [x] 0x9b30f0  CKPxBody_InitFromDesc_maybe  [inline]  (InitFromDesc)
//   [x] 0x9b34b0  CKPxBody_Step_maybe  [inline]  (Step)
//
// C2.8 port-final F03: the class (CKPxBody.h), its Load, construction / destruction, the transform slots and the
// description. C2.8 port-last Z7: the solver (Integrate, UpdateInertiaTensor, RecordSampleAndUpdateShapes) and the
// inline slots ExportState / InitFromDesc / vf58 / Step that CKSrvPhysics' body loops call.
#include "k2000/logic/CKPxBody.h"

#include <cmath>
#include <cstring>

#include "Renderware/rwcore/RwCamera.h"
#include "k2000/core/Stub.h"
#include "crt/ppc_ops.h"
#include "k2000/io/IKFile.h"
#include "k2000/logic/CKPxConstraintReport.h"
#include "k2000/logic/CKPxKinematic.h"
#include "k2000/logic/CKPxParameterReport.h"
#include "k2000/logic/memory/CKPxContainer.h"
#include "k2000/memory/Mem.h"
#include "k2000/misc/Engine.h"
#include "k2000/misc/KBase474C.h"
#include "k2000/misc/Mat4.h"
#include "k2000/scenegraph/CSGMovable.h"
#include "k2000/services/CKSrvPhysics.h"

namespace {

const CVector3 kNullVector{0.0f, 0.0f, 0.0f};  // 0x00c50d64 (TOC1 -0xbdc)
constexpr float kOne = 1.0f;                   // TOC1 -0xbe0
constexpr float kDescDefault = 0.01f;          // TOC1 -0xbd8 (0x3c23d70a)

// 0x0022cf40 CKPxShape_UpdateWorldMatrix_maybe (k2000/misc/CKPxShape.cpp): the shape's world matrix from its owner's.
void ShapeUpdateWorldMatrix(KBase474C* shape) { shape->UpdateWorldMatrix(); }

constexpr float kHalf = 0.5f;               // TOC1 -0xb9c (0x3f000000)
constexpr float kRadToDeg = 57.29578f;      // TOC1 -0xb98 (0x42652ee1)
constexpr float kZero = 0.0f;               // TOC1 -0xb94
constexpr float kRestSpeed = 1.0f;          // TOC1 -0xbe0 (the sleep test's threshold)
constexpr float kSleepTime = 2.0f;          // TOC1 -0xb90 (0x40000000)
constexpr float kRestingTime = 0.1f;        // TOC1 -0xb8c (0x3dcccccd)

// The vector's length: Math_Sqrtf 0x10690 of fmadds(z, z, fmadds(x, x, y * y)).
float Length(float x, float y, float z) { return std::sqrt(ppc::fmadds(z, z, ppc::fmadds(x, x, y * y))); }

// |x| as the original takes it: the float stored, its sign bit cleared in memory, reloaded.
float AbsBits(float x) {
    uint32_t bits;
    std::memcpy(&bits, &x, sizeof(bits));
    bits &= 0x7fffffffu;
    std::memcpy(&x, &bits, sizeof(bits));
    return x;
}

}  // namespace

CKPxBodyDesc::CKPxBodyDesc() {
    m_unk10 = 0;
    m_unk04 = 0;
    m_unk08 = 0;
    m_unk0c = 0;
    m_fUnk14 = kOne;
    m_unk18 = kNullVector;
    m_fUnk24 = 0.0f;
    m_fUnk28 = 0.0f;
    m_fUnk2c = kDescDefault;
    m_unk30 = kNullVector;
    m_fUnk3c = 0.0f;
    m_fUnk40 = kDescDefault;
    m_unk44 = kNullVector;
    m_fUnk50 = 0.0f;
    m_unk54 = kNullVector;
    m_pUnk60 = RwMatrixCreate_Thunk();
    m_pUnk64 = RwMatrixCreate_Thunk();
}

CKPxBodyDesc::~CKPxBodyDesc() {
    RwMatrixDestroy_Thunk(m_pUnk60);  // 0x0023f968
    RwMatrixDestroy_Thunk(m_pUnk64);
}

CKPxBody::CKPxBody() {
    m_vUnk104.m_pBlock = nullptr;
    m_vUnk104.m_ui32NbElt = 2;
    m_vUnk104.m_ui32NbUsedElt = 0;
    m_vRecords.m_ui32NbElt = 1;
    m_vRecords.m_ui32NbUsedElt = 0;
    m_vRecords.m_pBlock = nullptr;
    // The rest is what the fresh heap leaves (zero).
    m_unk18 = 0;
    m_unk1c = 0;
    m_ui32Flags = 0;
    m_fUnk24 = 0.0f;
    m_pDesc = nullptr;
    m_fMass = 0.0f;
    m_fInvMass = 0.0f;
    m_pGravity = nullptr;
    m_unk38 = kNullVector;
    m_pUnk44 = nullptr;
    m_pLocalInertia = nullptr;
    m_pWorldInertia = nullptr;
    m_unk50 = kNullVector;
    m_unk5c = kNullVector;
    m_fUnk68 = 0.0f;
    m_unk6c = kNullVector;
    m_unk78 = kNullVector;
    m_unk84 = kNullVector;
    m_fUnk90 = 0.0f;
    m_unk94 = kNullVector;
    m_fUnka0 = 0.0f;
    m_unka4 = kNullVector;
    m_fUnkb0 = 0.0f;
    m_fUnkb4 = 0.0f;
    m_unkb8 = kNullVector;
    m_fUnkc4 = 0.0f;
    m_unkc8 = kNullVector;
    m_fUnkd4 = 0.0f;
    m_unkd8 = kNullVector;
    m_unke4 = kNullVector;
    m_pWorldMatrix = nullptr;
    m_pNode = nullptr;
    m_pUnkf8 = nullptr;
    m_pUnkfc = nullptr;
    m_pContainer = nullptr;
    m_pUnk110 = nullptr;
    m_pUnk114 = nullptr;
    m_pUnk118 = nullptr;
    m_ui16Unk128 = 0;
    m_ui8Unk12a = 0;
    m_ui8Unk12b = 0;
}

CKPxBody::~CKPxBody() {
    if (m_vRecords.m_pBlock != nullptr) Mem_FreeAligned16(m_vRecords.m_pBlock);  // 0x00052fb8
    if (m_vUnk104.m_pBlock != nullptr) Mem_FreeAligned16(m_vUnk104.m_pBlock);
    m_vUnk104.m_ui32NbUsedElt = 0;
    m_vUnk104.m_pBlock = nullptr;
}

void CKPxBody::Destroy() {
    if (m_pDesc != nullptr) {
        delete m_pDesc;  // vt+0x04
        m_pDesc = nullptr;
    }
    RwMatrixDestroy_Thunk(m_pUnk44);  // 0x0023f968
    RwMatrixDestroy_Thunk(m_pLocalInertia);
    RwMatrixDestroy_Thunk(m_pWorldInertia);
    RwMatrixDestroy_Thunk(m_pWorldMatrix);
    RwMatrixDestroy_Thunk(m_pUnkf8);
    RwMatrixDestroy_Thunk(m_pUnkfc);
    if (m_vUnk104.m_pBlock != nullptr) {
        Mem_FreeAligned16(m_vUnk104.m_pBlock);
        m_vUnk104.m_pBlock = nullptr;
    }
    m_vUnk104.m_ui32NbUsedElt = 0;
    m_vUnk104.m_pBlock = nullptr;
    if (m_vRecords.m_pBlock != nullptr) Mem_FreeAligned16(m_vRecords.m_pBlock);
    m_vRecords.m_ui32NbUsedElt = 0;
    m_vRecords.m_pBlock = nullptr;
    KBase468C::Destroy();  // 0x00218070 CKPxObject_ClearReferences_BaseNop_maybe
}

// 0x009b2b98 CKPxBody_CreateRuntimeState_maybe (vt+0x6c, inline)
void CKPxBody::CreateRuntimeState() { m_pDesc = new CKPxBodyDesc; }  // OperatorNew(0x68)

// 0x009b2cb8 CKPxBody_SyncNodeFromBody_maybe (vt+0x68, inline)
void CKPxBody::SyncNodeFromBody() {
    CMatrix34 local;
    Mat4_Multiply(&local, m_pUnkfc, m_pWorldMatrix);  // 0x0023f788
    static_cast<CSGMovable*>(m_pNode)->SetLocalMatrix(reinterpret_cast<const RwMatrix*>(&local));  // 0x000d0d58
}

void CKPxBody::RebuildWorldInertia() {
    const CMatrix34* r = m_pWorldMatrix;
    CMatrix34 transpose;
    transpose.m_ui32Flags = 0;  // BUG(original): the stack word's other bits are not initialised (masked 0xfffdfffc)
    transpose.m_right = {r->m_right.x, r->m_up.x, r->m_at.x};
    transpose.m_up = {r->m_right.y, r->m_up.y, r->m_at.y};
    transpose.m_at = {r->m_right.z, r->m_up.z, r->m_at.z};
    transpose.m_ui32Flags &= 0xfffdfffcu;
    transpose.m_ui32pad1 = 0;
    transpose.m_ui32pad2 = 0;
    transpose.m_ui32pad3 = 0;
    transpose.m_pos = kNullVector;
    Mat4_Multiply(m_pWorldInertia, &transpose, m_pLocalInertia);  // 0x0023f788
    Mat4_TransformPostConcat(m_pWorldInertia, m_pWorldMatrix);  // 0x0023f760
}

void CKPxBody::UpdateShapes() {
    CKPxContainer* container = static_cast<CKPxContainer*>(m_pContainer);
    for (KBase474C* shape = static_cast<KBase474C*>(container->m_unk1c); shape != nullptr;
         shape = static_cast<KBase474C*>(shape->m_unk10)) {
        ShapeUpdateWorldMatrix(shape);  // 0x0022cf40
    }
}

// 0x0021a298 CKPxBody_Load: the base's, then (level data) three words, the byte +0x12a, +0x24 = 0, the description
// (vt+0x6c), the mass (and 1 / it), the gravity pointer, a vector, two matrices read and one made, vectors and floats
// (the zero ones from 0x00c50d64), the world matrix, the node, two matrices, the container, the references (a 16-bit
// count), three references with the record block between them, then the world inertia.
int32_t CKPxBody::Load(IKFile* file, int32_t type) {
    KBase468C::Load(file, type);  // 0x00218078
    if (type != 0) return 1;
    ReadU32LE(file, &m_unk18);
    ReadU32LE(file, &m_unk1c);
    ReadU32LE(file, &m_ui32Flags);
    ReadU8(file, &m_ui8Unk12a);
    m_fUnk24 = 0.0f;
    CreateRuntimeState();  // vt+0x6c
    ReadF32LE(file, &m_fMass);
    m_fInvMass = kOne / m_fMass;
    m_pGravity = &static_cast<CKSrvPhysics*>(g_pEngine->m_srvPhysics)->m_unk24;
    ReadU32LEWords(file, reinterpret_cast<uint32_t*>(&m_unk38), 3);
    m_pUnk44 = RwMatrixCreate_Thunk();
    CMatrix34_LoadMatrix(m_pUnk44, file);
    m_pLocalInertia = RwMatrixCreate_Thunk();
    CMatrix34_LoadMatrix(m_pLocalInertia, file);
    m_pWorldInertia = RwMatrixCreate_Thunk();
    m_unk50 = kNullVector;
    m_unk5c = kNullVector;
    ReadF32LE(file, &m_fUnk68);
    ReadU32LEWords(file, reinterpret_cast<uint32_t*>(&m_unk6c), 3);
    m_unk78 = kNullVector;
    m_unk84 = kNullVector;
    ReadF32LE(file, &m_fUnk90);
    ReadU32LEWords(file, reinterpret_cast<uint32_t*>(&m_unk94), 3);
    ReadF32LE(file, &m_fUnka0);
    ReadU32LEWords(file, reinterpret_cast<uint32_t*>(&m_unka4), 3);
    ReadF32LE(file, &m_fUnkb0);
    ReadF32LE(file, &m_fUnkb4);
    ReadU32LEWords(file, reinterpret_cast<uint32_t*>(&m_unkb8), 3);
    ReadF32LE(file, &m_fUnkc4);
    ReadU32LEWords(file, reinterpret_cast<uint32_t*>(&m_unkc8), 3);
    ReadF32LE(file, &m_fUnkd4);
    m_unkd8 = kNullVector;
    m_unke4 = kNullVector;
    m_pWorldMatrix = RwMatrixCreate_Thunk();
    CMatrix34_LoadMatrix(m_pWorldMatrix, file);
    IKFile_ReadRef(file, &m_pNode);
    m_pUnkf8 = RwMatrixCreate_Thunk();
    CMatrix34_LoadMatrix(m_pUnkf8, file);
    m_pUnkfc = RwMatrixCreate_Thunk();
    CMatrix34_LoadMatrix(m_pUnkfc, file);
    IKFile_ReadRef(file, &m_pContainer);
    uint16_t count = 0;
    ReadU16LE(file, &count);
    if (count == 0) {
        m_vUnk104.m_ui32NbElt = 1;
        m_vUnk104.m_pBlock = static_cast<IKSerializable**>(Mem_AllocAligned16(static_cast<uint32_t>(sizeof(IKSerializable*))));
    } else {
        m_vUnk104.m_ui32NbElt = count;
        m_vUnk104.m_pBlock = static_cast<IKSerializable**>(
            Mem_AllocAligned16(count * static_cast<uint32_t>(sizeof(IKSerializable*))));  // 0x00053198
    }
    if (m_vUnk104.m_ui32NbElt < count) {  // never (the grow-by-two of the template)
        uint32_t capacity = (static_cast<uint32_t>(count) & 0xfffeu) + 2;
        if (capacity == 0) capacity = 2;
        m_vUnk104.m_pBlock = static_cast<IKSerializable**>(
            Mem_ReallocAligned16(m_vUnk104.m_pBlock, capacity * static_cast<uint32_t>(sizeof(IKSerializable*))));
        m_vUnk104.m_ui32NbElt = capacity;
    }
    m_vUnk104.m_ui32NbUsedElt = count;
    IKFile_ReadObjectRefArray(file, m_vUnk104.m_pBlock, count);
    IKFile_ReadRef(file, &m_pUnk110);
    m_vRecords.m_ui32NbElt = 1;
    m_vRecords.m_pBlock = static_cast<Record*>(Mem_AllocAligned16(static_cast<uint32_t>(sizeof(Record))));  // 0x5c
    m_ui16Unk128 = 0;
    IKFile_ReadRef(file, &m_pUnk114);
    IKFile_ReadRef(file, &m_pUnk118);
    RebuildWorldInertia();
    return 1;
}

// 0x00219c70 CKPxBody_SetWorldMatrix_maybe (vt+0x5c)
void CKPxBody::SetWorldMatrix(const CMatrix34* matrix) {
    *m_pWorldMatrix = *matrix;
    RebuildWorldInertia();
    UpdateShapes();
    if (m_pNode != nullptr) SyncNodeFromBody();  // vt+0x68
}

// 0x002186a8 CKPxBody_vf60
void CKPxBody::Translate(const CVector3* offset) {
    CMatrix34* m = m_pWorldMatrix;
    m->m_pos.y = offset->y + m->m_pos.y;
    m->m_pos.z = offset->z + m->m_pos.z;
    m->m_pos.x = offset->x + m->m_pos.x;
    m->m_ui32Flags &= 0xfffdffffu;
    UpdateShapes();
    if (m_pNode != nullptr) SyncNodeFromBody();  // vt+0x68
}

// 0x002199e8 CKPxBody_ApplyTransform_maybe
void CKPxBody::ApplyTransform(const CMatrix34* transform) {
    Mat4_TransformPostConcat(m_pWorldMatrix, transform);  // 0x0023f760
    Mat4_OrthoNormalizeInPlace(m_pWorldMatrix);           // 0x0023f648
    RebuildWorldInertia();
    UpdateShapes();
    if (m_pNode != nullptr) SyncNodeFromBody();  // vt+0x68
}

// 0x00219b30 CKPxBody_SyncFromNode_maybe
void CKPxBody::SyncFromNode() {
    CSGMovable* node = static_cast<CSGMovable*>(m_pNode);
    node->ForceWorldMatrixUpdate();  // vt+0x50
    Mat4_Multiply(m_pWorldMatrix, m_pUnkf8, reinterpret_cast<const CMatrix34*>(&node->m_pRwFrame->ltm));  // frame +0x50
    Mat4_OrthoNormalizeInPlace(m_pWorldMatrix);
    RebuildWorldInertia();
    UpdateShapes();
}

// ---- C2.8 port-last Z7: the solver ----

namespace {

// The constraint report's counters cleared (Stop, the sleep test): the current count, each history slot's count, the
// ring's read and write slots.
void ResetConstraintReport(IKSerializable* object) {
    CKPxConstraintReport* report = static_cast<CKPxConstraintReport*>(object);
    report->m_ui16NbCurrent = 0;
    for (uint32_t i = 0; i < 20; ++i) report->m_history[i].m_ui32NbUsedElt = 0;
    report->m_ui16Read = 0;
    report->m_ui16Write = 0;
}

// The parameter report's averages, weight and ring indices cleared.
void ResetParameterReport(IKSerializable* object) {
    CKPxParameterReport* report = static_cast<CKPxParameterReport*>(object);
    for (uint32_t i = 0; i < 7; ++i) report->m_averages[i] = kNullVector;
    report->m_ui16Oldest = 0;
    report->m_fTotalWeight = 0.0f;  // stw 0
    report->m_ui16Newest = 0;
}

}  // namespace

void CKPxBody::ResetReports(uint32_t flags) {
    if ((flags & 0x400000) != 0) ResetConstraintReport(m_pUnk114);
    if ((m_ui32Flags & 0x800000) != 0) ResetParameterReport(m_pUnk118);
}

// 0x009b2d18 CKPxBody_ExportState (vt+0x50, inline)
void CKPxBody::ExportState(CKPxBodyDesc* desc) {
    desc->m_unk04 = m_unk18;
    desc->m_unk08 = m_unk1c;
    desc->m_unk0c = m_ui32Flags;
    desc->m_unk10 = m_ui8Unk12a;
    desc->m_fUnk14 = m_fMass;
    desc->m_unk18 = m_unk38;
    desc->m_fUnk24 = m_fUnk68;
    desc->m_fUnk28 = m_fUnk90;
    desc->m_fUnk2c = m_fUnka0;
    desc->m_unk30 = m_unka4;
    desc->m_fUnk3c = m_fUnkb0;
    desc->m_fUnk40 = m_fUnkb4;
    desc->m_unk44 = m_unkb8;
    desc->m_fUnk50 = m_fUnkc4;
    desc->m_unk54 = m_unkc8;
    *desc->m_pUnk60 = *m_pWorldMatrix;  // all 16 words
    *desc->m_pUnk64 = *m_pUnkf8;
}

// The parameters InitFromDesc takes back (inlined in both 0x9b30f0 and the kinematic 0x9b3c60), up to the node offset's
// inverse.
void CKPxBody::InitParametersFromDesc(const CKPxBodyDesc* desc) {
    m_unk18 = desc->m_unk04;
    m_unk1c = desc->m_unk08;
    m_ui32Flags = desc->m_unk0c;
    m_fUnk24 = 0.0f;  // stw 0
    m_ui8Unk12a = desc->m_unk10;
    m_fMass = desc->m_fUnk14;
    m_fInvMass = kOne / m_fMass;
    m_unk38 = desc->m_unk18;
    m_fUnk68 = desc->m_fUnk24;
    m_fUnk90 = desc->m_fUnk28;
    m_fUnka0 = desc->m_fUnk2c;
    m_unka4 = desc->m_unk30;
    m_fUnkb0 = desc->m_fUnk3c;
    m_fUnkb4 = desc->m_fUnk40;
    m_unkb8 = desc->m_unk44;
    m_fUnkc4 = desc->m_fUnk50;
    m_unkc8 = desc->m_unk54;
    *m_pUnkf8 = *desc->m_pUnk64;
    Mat4_Invert(m_pUnkfc, m_pUnkf8);  // 0x0023f878
}

// 0x009b30f0 CKPxBody_InitFromDesc_maybe (vt+0x54, inline): the parameters, then SetWorldMatrix's body inlined.
void CKPxBody::InitFromDesc(const CKPxBodyDesc* desc) {
    InitParametersFromDesc(desc);
    *m_pWorldMatrix = *desc->m_pUnk60;
    RebuildWorldInertia();
    UpdateShapes();
    if (m_pNode != nullptr) SyncNodeFromBody();  // vt+0x68
}

// 0x009b2f78 CKPxBody_vf58 (vt+0x58, inline)
void CKPxBody::AddVelocity(CVector3* delta) {
    const float x = m_unka4.x + delta->x;
    const float y = m_unka4.y + delta->y;
    const float z = m_unka4.z + delta->z;
    if ((m_ui32Flags & 0x1000) == 0) {
        m_unka4.z = z;
        m_unka4.x = x;
        m_unka4.y = y;
        return;
    }
    const float speed = Length(x, y, z);
    if (speed > m_fUnkb0) {  // ble: NaN keeps the velocity
        const float scale = m_fUnkb0 / speed;
        const float sz = z * scale;
        const float sx = x * scale;
        const float sy = y * scale;
        delta->z = sz - m_unka4.z;
        delta->x = sx - m_unka4.x;
        delta->y = sy - m_unka4.y;
        m_ui32Flags |= 0x2000;
        m_unka4.z = sz;
        m_unka4.x = sx;
        m_unka4.y = sy;
        return;
    }
    m_ui32Flags &= ~0x2000u;
    m_unka4.z = z;
    m_unka4.x = x;
    m_unka4.y = y;
}

// The sleep test after a step (0x9b34fc..0x9b3800, the tail of Step).
void CKPxBody::UpdateRestState(float dt) {
    if ((m_ui32Flags & 0x20) != 0) return;
    float linear = AbsBits(m_unka4.x) + AbsBits(m_unka4.y);
    linear = linear + AbsBits(m_unka4.z);
    float angular = AbsBits(m_unkb8.x) + AbsBits(m_unkb8.y);
    angular = angular + AbsBits(m_unkb8.z);
    float sum = linear + angular;
    const float half = sum * kHalf;
    sum = sum * half;
    if (!(sum < kRestSpeed)) return;  // bge: NaN returns
    const float rest = dt + m_fUnk24;
    m_fUnk24 = rest;
    if (rest > kSleepTime) {
        const uint32_t flags = m_ui32Flags;
        m_ui16Unk128 = 0;
        m_ui32Flags = flags & ~0x1cu;
        ResetReports(flags);
        m_ui32Flags |= 8;
        m_fUnk24 = 0.0f;  // stw 0
        return;
    }
    if (rest > kRestingTime) m_ui32Flags = (m_ui32Flags & ~0xcu) | 0x10;  // ble: NaN skips
}

// 0x009b34b0 CKPxBody_Step_maybe (vt+0x64, inline)
void CKPxBody::Step(float dt, float dt2, float frequency, float /*halfFrequencySq*/, uint8_t lastStep) {
    Integrate(dt, dt2, frequency, lastStep);  // 0x00218ea8
    RecordSampleAndUpdateShapes(dt, lastStep);  // 0x00218790
    UpdateRestState(dt);
}

// 0x00218790 CKPxBody_RecordSampleAndUpdateShapes_maybe
void CKPxBody::RecordSampleAndUpdateShapes(float dt, uint8_t lastStep) {
    if ((m_ui32Flags & 0x800000) != 0 && lastStep != 0) {
        CKPxParameterReport::SSample sample;
        sample.m_values[0] = m_unk6c;
        sample.m_values[1] = m_unka4;
        Mat4_TransformVectorsInline(m_pWorldMatrix, &sample.m_values[2], &m_unka4, 1);  // 0x00240520
        sample.m_values[3] = m_pWorldMatrix->m_pos;
        sample.m_values[4] = m_unk94;
        sample.m_values[5] = m_unkb8;
        Mat4_TransformVectorsInline(m_pWorldMatrix, &sample.m_values[6], &m_unkb8, 1);
        sample.m_fWeight = dt;
        CKPxParameterReport* report = static_cast<CKPxParameterReport*>(m_pUnk118);
        if (report->m_ui16WindowSize != 0) {
            TVector<CKPxParameterReport::SSample, 1>& samples = report->m_samples;
            const uint16_t newest = report->m_ui16Newest;
            if (newest < samples.m_ui32NbUsedElt) {
                samples.m_pBlock[newest] = sample;
            } else {
                if (samples.m_ui32NbElt == samples.m_ui32NbUsedElt) {
                    uint32_t capacity = samples.m_ui32NbUsedElt + 1;
                    if (capacity == 0) capacity = 1;
                    samples.m_pBlock = static_cast<CKPxParameterReport::SSample*>(Mem_ReallocAligned16(
                        samples.m_pBlock,
                        (capacity * static_cast<uint32_t>(sizeof(CKPxParameterReport::SSample))) & ~7u));  // 0x53190
                    samples.m_ui32NbElt = capacity;
                }
                samples.m_pBlock[samples.m_ui32NbUsedElt] = sample;
                ++samples.m_ui32NbUsedElt;
            }
            const uint16_t next = static_cast<uint16_t>(report->m_ui16Newest + 1);
            uint16_t slot = 0;
            if (report->m_ui16WindowSize > next) slot = next;
            report->AddSampleToSlidingWindow(&slot);  // 0x00232470
        }
    }
    UpdateShapes();
}

// 0x00219e50 CKPxBody_UpdateInertiaTensor_maybe
void CKPxBody::UpdateInertiaTensor() {
    CMatrix34* inertia = m_pUnk44;
    inertia->m_ui32Flags &= 0xfffdfffeu;
    inertia->m_right = kNullVector;
    inertia->m_up = kNullVector;
    inertia->m_at = kNullVector;
    inertia->m_pos = kNullVector;
    if ((m_ui32Flags & 0x80000) == 0) {
        CKPxContainer* container = static_cast<CKPxContainer*>(m_pContainer);
        CMatrix34 transpose{};  // the stack matrices (their other flag bits and pads are not set: zero here)
        CMatrix34 product{};
        CMatrix34 tensor{};
        for (KBase474C* shape = static_cast<KBase474C*>(container->m_unk1c); shape != nullptr;
             shape = static_cast<KBase474C*>(shape->m_unk10)) {
            const CMatrix34* offset = shape->m_pWorldMatrix;  // +0x38: the shape's offset in the body
            transpose.m_ui32Flags &= 0xfffdfffcu;
            transpose.m_pos = kNullVector;
            transpose.m_right = {offset->m_right.x, offset->m_up.x, offset->m_at.x};
            transpose.m_up = {offset->m_right.y, offset->m_up.y, offset->m_at.y};
            transpose.m_at = {offset->m_right.z, offset->m_up.z, offset->m_at.z};
            shape->ComputeInertiaTensor(&tensor);  // vt+0x5c
            Mat4_Multiply(&product, &tensor, shape->m_pWorldMatrix);  // 0x0023f788
            Mat4_TransformPostConcat(&product, &transpose);  // 0x0023f760
            Mat4_Add(m_pUnk44, m_pUnk44, &product);  // 0x002402e8
        }
        CMatrix34* sum = m_pUnk44;
        const float mass = m_fMass;
        sum->m_right = {mass * sum->m_right.x, mass * sum->m_right.y, mass * sum->m_right.z};
        sum->m_up = {mass * sum->m_up.x, mass * sum->m_up.y, mass * sum->m_up.z};
        sum->m_at = {mass * sum->m_at.x, mass * sum->m_at.y, mass * sum->m_at.z};
        sum->m_ui32Flags &= 0xfffdfffeu;
    } else {
        CMatrix34* diagonal = m_pUnk44;
        diagonal->m_right = {m_unk38.x, 0.0f, 0.0f};
        diagonal->m_ui32Flags &= 0xfffdfffcu;
        diagonal->m_up = {0.0f, m_unk38.y, 0.0f};
        diagonal->m_ui32Flags &= 0xfffdfffcu;
        diagonal->m_at = {0.0f, 0.0f, m_unk38.z};
        diagonal->m_ui32Flags &= 0xfffdfffcu;
    }
    Mat4_Invert(m_pLocalInertia, m_pUnk44);  // 0x0023f878
    RebuildWorldInertia();
}

// 0x00218ea8 CKPxBody_Integrate_maybe
void CKPxBody::Integrate(float dt, float dt2, float frequency, uint8_t lastStep) {
    IntegrateCommon(dt, dt2, frequency, lastStep, false);
}

// 0x00218ea8 CKPxBody_Integrate_maybe and 0x0021b9f8 CKPxKinematic_Integrate_maybe: the same code but for the kinematic's
// friction limits (mass / dt and the angular inertia / dt instead of times the frequency) and its axis locks
// (ApplyTranslationAxisConstraint before the move, ApplyRotationAxisConstraint before the turn).
void CKPxBody::IntegrateCommon(float dt, float dt2, float frequency, uint8_t lastStep, bool kinematic) {
    uint32_t flags = m_ui32Flags;
    if ((flags & 0x800) == 0) {
        // The linear friction: the force less min(frequency * mass, +0xa0) times the velocity.
        const float limit = kinematic ? m_fMass / dt : frequency * m_fMass;
        float drag = m_fUnka0;
        if (!(limit > drag)) drag = limit;  // ble: NaN takes the limit
        drag = -drag;
        m_unk50.x = ppc::fmadds(drag, m_unka4.x, m_unk50.x);
        m_unk50.z = ppc::fmadds(drag, m_unka4.z, m_unk50.z);
        m_unk50.y = ppc::fmadds(drag, m_unka4.y, m_unk50.y);
        flags = m_ui32Flags;
    }
    if ((flags & 0x100000) != 0) {
        // The drag across the axis +0xc8 (turned to world space): the velocity's part off the axis.
        const float limit = kinematic ? m_fMass / dt : frequency * m_fMass;
        float drag = m_fUnkd4;
        if (!(limit > drag)) drag = limit;  // ble
        CVector3 axis;
        Mat4_TransformVectors(m_pWorldMatrix, &axis, &m_unkc8, 1);  // 0x0023f7b0
        const float negDrag = -drag;
        const CVector3 v = m_unka4;
        float d = axis.y * v.y;
        d = ppc::fmadds(axis.x, v.x, d);
        d = ppc::fnmadds(axis.z, v.z, d);
        const float pz = ppc::fmadds(axis.z, d, v.z);
        const float px = ppc::fmadds(axis.x, d, v.x);
        const float py = ppc::fmadds(axis.y, d, v.y);
        m_unk50.z = ppc::fmadds(pz, negDrag, m_unk50.z);
        m_unk50.x = ppc::fmadds(px, negDrag, m_unk50.x);
        m_unk50.y = ppc::fmadds(py, negDrag, m_unk50.y);
    }
    // The acceleration from the force and half the pending force (+0x5c, then cleared).
    {
        const CVector3 force = m_unk50;
        const float ax = ppc::fmadds(m_unk5c.x, kHalf, force.x);
        const float ay = ppc::fmadds(m_unk5c.y, kHalf, force.y);
        const float az = ppc::fmadds(m_unk5c.z, kHalf, force.z);
        m_unk5c = kNullVector;
        const float inverseMass = m_fInvMass;
        m_unk6c.x = ax * inverseMass;
        m_unk6c.y = ay * inverseMass;
        m_unk6c.z = az * inverseMass;
    }
    if ((m_ui32Flags & 0x1000) != 0) {
        // 0x219630: the acceleration clamped to +0x68, then the velocity it gives clamped to +0xb0 (the acceleration
        // recomputed from the clamped velocity).
        const float length = Length(m_unk6c.x, m_unk6c.y, m_unk6c.z);
        const float maxAcceleration = m_fUnk68;
        if (length > maxAcceleration) {  // ble
            const float scale = maxAcceleration / length;
            m_unk6c.z = scale * m_unk6c.z;
            m_unk6c.x = scale * m_unk6c.x;
            m_unk6c.y = scale * m_unk6c.y;
            m_ui32Flags |= 0x4000;
        } else {
            m_ui32Flags &= ~0x4000u;
        }
        const float vy = ppc::fmadds(dt, m_unk6c.y, m_unka4.y);
        const float vx = ppc::fmadds(dt, m_unk6c.x, m_unka4.x);
        const float vz = ppc::fmadds(dt, m_unk6c.z, m_unka4.z);
        const float speed = Length(vx, vy, vz);
        const float maxSpeed = m_fUnkb0;
        if (speed > maxSpeed) {  // ble
            const float scale = maxSpeed / speed;
            const float ez = ppc::fmsubs(vz, scale, m_unka4.z);
            const float ex = ppc::fmsubs(vx, scale, m_unka4.x);
            const float ey = ppc::fmsubs(vy, scale, m_unka4.y);
            const float inverseDt = kOne / dt;
            m_unk6c.z = inverseDt * ez;
            m_unk6c.x = inverseDt * ex;
            m_unk6c.y = inverseDt * ey;
            m_ui32Flags |= 0x2000;
        } else {
            m_ui32Flags &= ~0x2000u;
        }
    }
    // 0x219084: the move dt2 * acceleration + dt * velocity.
    {
        const float mx = dt2 * m_unk6c.x;
        const float my = dt2 * m_unk6c.y;
        const float mz = dt2 * m_unk6c.z;
        m_unkd8.x = mx;
        m_unkd8.y = my;
        m_unkd8.z = mz;
        m_unkd8.z = ppc::fmadds(dt, m_unka4.z, mz);
        m_unkd8.x = ppc::fmadds(dt, m_unka4.x, mx);
        m_unkd8.y = ppc::fmadds(dt, m_unka4.y, my);
    }
    // The acceleration from the force alone.
    {
        const float inverseMass = m_fInvMass;
        m_unk6c.x = inverseMass * m_unk50.x;
        m_unk6c.z = inverseMass * m_unk50.z;
        m_unk6c.y = inverseMass * m_unk50.y;
    }
    if ((m_ui32Flags & 0x1000) != 0) {
        const float length = Length(m_unk6c.x, m_unk6c.y, m_unk6c.z);
        const float maxAcceleration = m_fUnk68;
        if (length > maxAcceleration) {  // bgt
            const float scale = maxAcceleration / length;
            m_unk6c.z = scale * m_unk6c.z;
            m_unk6c.x = scale * m_unk6c.x;
            m_unk6c.y = scale * m_unk6c.y;
            m_ui32Flags |= 0x4000;
        } else {
            m_ui32Flags &= ~0x4000u;
        }
    }
    if (kinematic) static_cast<CKPxKinematic*>(this)->ApplyTranslationAxisConstraint();  // 0x0021ae88
    // 0x219108: the position moved, the velocity changed by dt * acceleration (vt+0x58).
    {
        CMatrix34* world = m_pWorldMatrix;
        world->m_pos.y = world->m_pos.y + m_unkd8.y;
        world->m_pos.z = world->m_pos.z + m_unkd8.z;
        world->m_pos.x = world->m_pos.x + m_unkd8.x;
        world->m_ui32Flags &= ~0x20000u;
        CVector3 change{dt * m_unk6c.x, dt * m_unk6c.y, dt * m_unk6c.z};
        AddVelocity(&change);  // vt+0x58
    }
    // The next force: gravity times the mass (none with flag 0x40).
    if ((m_ui32Flags & 0x40) == 0) {
        const CVector3* gravity = m_pGravity;
        const float mass = m_fMass;
        m_unk50.z = mass * gravity->z;
        m_unk50.x = mass * gravity->x;
        m_unk50.y = mass * gravity->y;
    } else {
        m_unk50 = kNullVector;
    }
    if ((m_ui32Flags & 0x8000) == 0) {
        // 0x219520: the angular friction: the torque less min(frequency * (w . I w) / |w|^2, +0xb4) times w (w turned
        // into the body frame for the inertia +0x44).
        const float length = Length(m_unkb8.x, m_unkb8.y, m_unkb8.z);
        float inertiaAlong = kZero;
        if (length > kZero) {  // ble: NaN keeps 0
            CVector3 local;
            Mat4_TransformVectorsInline(m_pWorldMatrix, &local, &m_unkb8, 1);  // 0x00240520
            CVector3 turned;
            Mat4_TransformVectors(m_pUnk44, &turned, &local, 1);  // 0x0023f7b0
            const float inverse = kOne / length;
            turned.y = turned.y * inverse;
            turned.x = turned.x * inverse;
            turned.z = inverse * turned.z;
            const float yy = turned.y * local.y;
            const float xy = ppc::fmadds(turned.x, local.x, yy);
            inertiaAlong = ppc::fmadds(turned.z, local.z, xy) / length;
        }
        const float limit = kinematic ? inertiaAlong / dt : inertiaAlong * frequency;
        float drag = m_fUnkb4;
        if (!(limit > drag)) drag = limit;  // ble
        drag = -drag;
        m_unk78.z = ppc::fmadds(drag, m_unkb8.z, m_unk78.z);
        m_unk78.x = ppc::fmadds(drag, m_unkb8.x, m_unk78.x);
        m_unk78.y = ppc::fmadds(drag, m_unkb8.y, m_unk78.y);
    }
    // 0x2191f8: the angular acceleration from the torque and half the pending torque (+0x84, then cleared).
    {
        CVector3 torque{ppc::fmadds(m_unk84.x, kHalf, m_unk78.x), ppc::fmadds(m_unk84.y, kHalf, m_unk78.y),
                        ppc::fmadds(m_unk84.z, kHalf, m_unk78.z)};
        m_unk84 = kNullVector;
        Mat4_TransformVectors(m_pWorldInertia, &m_unk94, &torque, 1);  // 0x0023f7b0
    }
    if ((m_ui32Flags & 0x10000) != 0) {
        // 0x219790: the angular acceleration clamped to +0x90, the angular velocity it gives clamped to +0xc4.
        const float length = Length(m_unk94.x, m_unk94.y, m_unk94.z);
        const float maxAcceleration = m_fUnk90;
        if (length > maxAcceleration) {  // ble
            const float scale = maxAcceleration / length;
            m_unk94.z = scale * m_unk94.z;
            m_unk94.x = scale * m_unk94.x;
            m_unk94.y = scale * m_unk94.y;
            m_ui32Flags |= 0x40000;
        } else {
            m_ui32Flags &= ~0x40000u;
        }
        const float wy = ppc::fmadds(dt, m_unk94.y, m_unkb8.y);
        const float wx = ppc::fmadds(dt, m_unk94.x, m_unkb8.x);
        const float wz = ppc::fmadds(dt, m_unk94.z, m_unkb8.z);
        const float speed = Length(wx, wy, wz);
        const float maxSpeed = m_fUnkc4;
        if (speed > maxSpeed) {  // ble
            const float scale = maxSpeed / speed;
            const float ez = ppc::fmsubs(wz, scale, m_unkb8.z);
            const float ex = ppc::fmsubs(wx, scale, m_unkb8.x);
            const float ey = ppc::fmsubs(wy, scale, m_unkb8.y);
            const float inverseDt = kOne / dt;
            m_unk94.z = inverseDt * ez;
            m_unk94.x = inverseDt * ex;
            m_unk94.y = inverseDt * ey;
            m_ui32Flags |= 0x20000;
        } else {
            m_ui32Flags &= ~0x20000u;
        }
    }
    // 0x219274: the turn dt2 * angular acceleration + dt * w, then the angular acceleration from the torque alone.
    {
        const float rx = dt2 * m_unk94.x;
        const float ry = dt2 * m_unk94.y;
        const float rz = dt2 * m_unk94.z;
        m_unke4.x = rx;
        m_unke4.y = ry;
        m_unke4.z = rz;
        m_unke4.x = ppc::fmadds(dt, m_unkb8.x, rx);
        m_unke4.y = ppc::fmadds(dt, m_unkb8.y, ry);
        m_unke4.z = ppc::fmadds(dt, m_unkb8.z, rz);
        Mat4_TransformVectors(m_pWorldInertia, &m_unk94, &m_unk78, 1);  // 0x0023f7b0
    }
    if ((m_ui32Flags & 0x10000) != 0) {
        const float length = Length(m_unk94.x, m_unk94.y, m_unk94.z);
        const float maxAcceleration = m_fUnk90;
        if (length > maxAcceleration) {  // bgt
            const float scale = maxAcceleration / length;
            m_unk94.z = scale * m_unk94.z;
            m_unk94.x = scale * m_unk94.x;
            m_unk94.y = scale * m_unk94.y;
            m_ui32Flags |= 0x40000;
        } else {
            m_ui32Flags &= ~0x40000u;
        }
    }
    if (kinematic) static_cast<CKPxKinematic*>(this)->ApplyRotationAxisConstraint();  // 0x0021b1c0
    // 0x2192e8: the turn's axis normalised; a positive angle turns the world matrix (in degrees), which is then
    // orthonormalised, and the world inertia is rebuilt.
    {
        const float angle = Length(m_unke4.x, m_unke4.y, m_unke4.z);
        if (angle != kZero) {
            const float inverse = kOne / angle;
            m_unke4.z = inverse * m_unke4.z;
            m_unke4.x = inverse * m_unke4.x;
            m_unke4.y = inverse * m_unke4.y;
            if (angle > kZero) {  // ble
                Mat4_RotateInPlace(m_pWorldMatrix, &m_unke4, angle * kRadToDeg);  // 0x00240498
                Mat4_OrthoNormalizeInPlace(m_pWorldMatrix);  // 0x0023f648
                RebuildWorldInertia();
            }
        }
    }
    // 0x219408: the angular velocity w + dt * angular acceleration (clamped with flag 0x1000).
    {
        float wz = ppc::fmadds(dt, m_unk94.z, m_unkb8.z);
        float wx = ppc::fmadds(dt, m_unk94.x, m_unkb8.x);
        float wy = ppc::fmadds(dt, m_unk94.y, m_unkb8.y);
        if ((m_ui32Flags & 0x1000) != 0) {
            const float speed = Length(wx, wy, wz);
            const float maxSpeed = m_fUnkb0;  // the original clamps to the linear limit +0xb0 here, not +0xc4
            if (speed > maxSpeed) {  // bgt
                m_ui32Flags |= 0x20000;
                const float scale = maxSpeed / speed;
                wz = wz * scale;
                wx = wx * scale;
                wy = wy * scale;
            } else {
                m_ui32Flags &= ~0x20000u;
            }
        }
        m_unkb8.z = wz;
        m_unkb8.x = wx;
        m_unkb8.y = wy;
        m_unk78 = kNullVector;
    }
    if (lastStep != 0 && m_pNode != nullptr) SyncNodeFromBody();  // vt+0x68
}

// The constraint rows' slot (inlined in every row writer).
CKPxBody::Record* CKPxBody::NextRecord() {
    if (m_ui16Unk128 < m_vRecords.m_ui32NbUsedElt) return &m_vRecords.m_pBlock[m_ui16Unk128];
    if (m_vRecords.m_ui32NbElt == m_vRecords.m_ui32NbUsedElt) {
        uint32_t capacity = m_vRecords.m_ui32NbUsedElt + 1;
        if (capacity == 0) capacity = 1;
        m_vRecords.m_pBlock = static_cast<Record*>(
            Mem_ReallocAligned16(m_vRecords.m_pBlock, (capacity * static_cast<uint32_t>(sizeof(Record))) & ~3u));  // 0x53190
        m_vRecords.m_ui32NbElt = capacity;
    }
    return &m_vRecords.m_pBlock[m_vRecords.m_ui32NbUsedElt++];
}
