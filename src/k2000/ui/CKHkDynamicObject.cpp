// CKHkDynamicObject.cpp - reconstructed original translation unit 0x5a9bc8-0x5acb48 (GAME_TOC2, main_toc2), 32 functions, 26 live.
// Primary owner: CKHkDynamicObject (not a registered class)
// Other owners: RegisterCKHkDynamicObjectClass (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x5a9bc8  CKHkDynamicObject_Destroy
//   [x] 0x5a9c18  CKHkDynamicObject_Construct  [dead]
//   [x] 0x5a9c60  CKHkDynamicObject_vf68  (Stop, empty: IKHook's)
//   [x] 0x5a9c68  CKHkDynamicObject_vf70  (Pause, empty: IKHook's)
//   [x] 0x5a9c70  CKHkDynamicObject_vf78  (Resume, empty: IKHook's)
//   [ ] 0x5a9c78  RegisterCKHkDynamicObjectClass
//   [ ] 0x5a9cf0  _GLOBAL__I_5a9cf0
//   [ ] 0x5a9d00  CKHkDynamicObject_OnCycleComplete_maybe  [dead]
//   [ ] 0x5a9da8  CKHkDynamicObject_GetAxisFromFlagBits9to11_maybe  [dead]
//   [ ] 0x5a9ee8  CKHkDynamicObject_GetAxisFromFlagBits6to8_maybe  [dead]
//   [ ] 0x5a9ff0  CKHkDynamicObject_Save
//   [x] 0x5aa018  CKHkDynamicObject_LevelReset  (RecursiveRegistration: IKHook's (inherited), then 1)
//   [x] 0x5aa040  CKHkDynamicObject_ClearReferences  (Destroy)
//   [x] 0x5aa0c8  CKHkDynamicObject_DestroyArray
//   [x] 0x5aa170  CKHkDynamicObject_SetActive_maybe  (SetActive, vt+0xc0)
//   [x] 0x5aa1c8  CKHkDynamicObject_OnDeactivate  (VfA4)
//   [x] 0x5aa248  CKHkDynamicObject_OnActivate  (VfA0)
//   [ ] 0x5aa2a8  CKHkDynamicObject_Construct_2  [dead]
//   [x] 0x5aa2f0  CKHkDynamicObject_vf40  (GetInfo)
//   [x] 0x5aa348  CKHkDynamicObject_CreateArray
//   [x] 0x5aa418  CKHkDynamicObject_Create
//   [x] 0x5aa480  CKHkDynamicObject_HandleMessage  (MessageProc, vt+0x1c; the jump table's 15 cases to 0x5aab98)
//   [x] 0x5aab98  CKHkDynamicObject_Update  (vt+0x7c)
//   [x] 0x5ab788  CKHkDynamicObject_Destructor  (implicit: the vtables only)
//   [x] 0x5ab7a8  CKHkDynamicObject_Load
//   [ ] 0x5abfd8  CKHkDynamicObject_Destructor_2  [dead]
//   [x] 0x5abff8  CKHkDynamicObject_PostLoad  (PostLoad, vt+0x30)
//   [x] 0x5ac2a0  CKHkDynamicObject_vf3C  (SetGameState, vt+0x3c)
//   [x] 0x5ac608  CKHkDynamicObject_ResetToInitialState_maybe  (SetDefaultState, vt+0x38)
//   [x] 0x5ac818  CKHkDynamicObject_ReinitRuntime  (Restart, vt+0x54)
//   [x] 0x5ac9a0  CKHkDynamicObject_ResetRuntime  (Start, vt+0x50)
//   [x] 0x5acb00  CKHkDynamicObject_DeletingDestructor  (implicit, then delete)
//
//   [ ] 0x9cbe30  CKHkDynamicObject_IsKindOf  [inline]
//   [ ] 0x9cbe78  CKHkDynamicObject_GetClassGroup  [inline]
//   [ ] 0x9cbe80  CKHkDynamicObject_GetClassId  [inline]
//   [x] 0x9cbe88  CKHkDynamicObject_GetTriggerProp10  [inline]  (the GetInfo accessor)
#include "k2000/ui/CKHkDynamicObject.h"

#include "Renderware/rwcore/RwMatrix.h"
#include "crt/xlround.h"
#include "k2000/core/IKInfo.h"
#include "k2000/io/IKFile.h"
#include "k2000/misc/Mat4.h"

// 0x005ab7a8 CKHkDynamicObject_Load
int32_t CKHkDynamicObject::Load(IKFile* file, int32_t type) {
    IKHook::Load(file, type);  // through TocBridge_CKHook_Load
    if (type != K_LEVEL_PLATEFORMS) return 1;
    ReadF32LE(file, &m_unk70);
    ReadF32LE(file, &m_unk6C);
    ReadF32LE(file, &m_unk74);
    // Read into a local, +0x28 = 0, then +0x28 = the swapped word.
    uint32_t value = 0;
    ReadU32LE(file, &value);
    m_unk28 = 0;
    m_unk28 = value;
    IKFile_ReadRef(file, &m_pUnk44);
    ReadU32LEWords(file, reinterpret_cast<uint32_t*>(m_aUnk2C), 3);
    ReadF32LE(file, &m_unk38);
    ReadF32LE(file, &m_unk3C);
    ReadF32LE(file, &m_unk40);
    IKFile_ReadRef(file, &m_pUnk80);
    ReadF32LE(file, &m_unk78);
    ReadF32LE(file, &m_unk7C);
    IKFile_ReadRef(file, &m_pUnk68);
    ReadU32LEWords(file, reinterpret_cast<uint32_t*>(m_aUnk48), 3);
    ReadU32LEWords(file, reinterpret_cast<uint32_t*>(m_aUnk54), 3);
    ReadF32LE(file, &m_unk64);
    ReadF32LE(file, &m_unk60);
    IKFile_ReadRef(file, &m_pUnk84);
    ReadF32LE(file, &m_unk88);
    ReadF32LE(file, &m_unk8C);
    IKFile_ReadRef(file, &m_pUnk94);
    ReadF32LE(file, &m_unk90);
    m_pMatrix20 = RwMatrixCreate_Thunk();
    m_pMatrix24 = RwMatrixCreate_Thunk();
    CMatrix34_LoadMatrix(m_pMatrix20, file);
    CMatrix34_LoadMatrix(m_pMatrix24, file);
    IKFile_ReadRef(file, &m_pUnkF0);
    m_tsUnk98.Load(file, 0);
    m_tsUnkA0.Load(file, 0);
    ReadU8(file, &m_unkA8);
    ReadU8(file, &m_unkA9);
    return 1;
}

// ==== port-all P19 ====================================================================================================

// 0x005aa040 CKHkDynamicObject_Destroy (RwMatrixDestroy through its thunk / TOC bridge)
void CKHkDynamicObject::Destroy() {
    if (m_pMatrix20 != nullptr) {
        RwMatrixDestroy(reinterpret_cast<RwMatrix*>(m_pMatrix20));
        m_pMatrix20 = nullptr;
    }
    if (m_pMatrix24 != nullptr) {
        RwMatrixDestroy(reinterpret_cast<RwMatrix*>(m_pMatrix24));
        m_pMatrix24 = nullptr;
    }
    if (m_pMatrixE4 != nullptr) {
        RwMatrixDestroy(reinterpret_cast<RwMatrix*>(m_pMatrixE4));
        m_pMatrixE4 = nullptr;
    }
}

// 0x005aa2f0 CKHkDynamicObject_vf40 (GetInfo), with 0x009cbe88 CKHkDynamicObject_GetTriggerProp10: the angle in whole
// degrees (fsubs, fmuls by 57.29578f (TOC2 -0x6810), lroundf 0x77ed68, back to a float).
int32_t CKHkDynamicObject::GetInfo(IKInfo* info, int32_t request) {
    if (request != kGetInfoValueAccessor || info->m_ui32Id != 0x10) return 1;
    return AnswerInfo(info, [](IKSerializable* o, uint32_t) {
        const CKHkDynamicObject* hook = static_cast<CKHkDynamicObject*>(o);
        const int32_t degrees = crt::lroundf((hook->m_unkBC - hook->m_unkE8) * 57.2957801818847656f);
        return FloatBits(static_cast<float>(static_cast<double>(static_cast<int64_t>(degrees))));
    }, 2);
}

// ==== port-rest R09 ===================================================================================================
#include "k2000/components/CKGroundCpnt.h"
#include "k2000/scenegraph/CSGLeaf.h"
#include "k2000/math/Vec3.h"
#include "k2000/scenegraph/CSGMovable.h"

namespace {
// The axis the flag bits select (the inlined 0x5a9ee8 _GetAxisFromFlagBits6to8 / 0x5a9da8 _GetAxisFromFlagBits9to11,
// dead out of line; the jump tables of every caller give the same cases): 0 the x axis (0x00c50d34), 2 the z axis
// (0x00c50d4c), 3 (s, s, 0), 4 (0, s, s), 5 (s, 0, s) with s = TOC2 -0x67fc (0x3f3504f3), 6 the diagonal (TOC2 -0x67f8,
// 0x3f13cd3e, each); 1 and 7 the y axis (0x00c50d40).
CVector3 SelectedAxis(uint32_t select) {
    const float s = 0.707106769f;
    const float d = 0.577350497f;
    switch (select) {
    case 0: return CVector3{1.0f, 0.0f, 0.0f};
    case 2: return CVector3{0.0f, 0.0f, 1.0f};
    case 3: return CVector3{s, s, 0.0f};
    case 4: return CVector3{0.0f, s, s};
    case 5: return CVector3{s, 0.0f, s};
    case 6: return CVector3{d, d, d};
    default: return CVector3{0.0f, 1.0f, 0.0f};
    }
}
uint32_t AxisBits6(uint32_t flags) { return (flags >> 6) & 7u; }  // rldicl 0x3a, 0x3d
uint32_t AxisBits9(uint32_t flags) { return (flags >> 9) & 7u; }  // rldicl 0x37, 0x3d
CSGMovable* NodeOf(CKHkDynamicObject* hook) { return static_cast<CSGMovable*>(hook->m_pKGLObject); }
}  // namespace

// The runtime state the resets share: +0xc4 = 1, +0xd4 = 1, +0xc0 / +0xc8 / +0xcc / +0xd0 / +0xd8 = 0 (the callers add
// +0xbc / +0xe0 / +0xe8 as noted), then the bits 6..8 axis through the start matrix into +0xb0.
void CKHkDynamicObject::ResetMotionState() {
    m_unkC4 = 1.0f;  // TOC2 -0x67cc
    m_unkD4 = 1;
    m_unkC0 = 0.0f;
    m_unkC8 = 0.0f;
    m_unkCC = 0.0f;
    m_unkD0 = 0.0f;
    m_unkD8 = 0.0f;
    const CVector3 axis = SelectedAxis(AxisBits6(m_unk28));
    Mat4_TransformVectors(m_pMatrix20, reinterpret_cast<CVector3*>(m_aUnkB0), &axis, 1);  // TocBridge 0x9900c0 -> 0x23f7b0
}

// 0x005aa170 CKHkDynamicObject_SetActive_maybe (vt+0xc0): +0xec = `active`, the node hidden when not active (+0x10 bit 2
// = active ^ 1), the ground component's grounds switched (CollisionMeshArray_SetActive_maybe 0x1910a8 through TocBridge
// 0x990530).
void CKHkDynamicObject::SetActive(uint8_t active) {
    m_unkEC = active;
    CSGLeaf* node = static_cast<CSGLeaf*>(m_pKGLObject);
    node->m_sgProperties = (node->m_sgProperties & 0xfffffffbu) | ((static_cast<uint32_t>(active) ^ 1u) << 2);
    static_cast<CKGroundCpnt*>(m_pUnkF0)->SetActive(active);
}

// 0x005aa1c8 CKHkDynamicObject_OnDeactivate (vt+0xa4): shown and active (vt+0xc0 with 1), the node back to the start
// matrix (CSGMovable_SetLocalMatrix_maybe 0xd0be8 through TocBridge 0x990050), the flags restored from +0xac.
void CKHkDynamicObject::VfA4() {
    SetActive(1);  // vt+0xc0
    NodeOf(this)->SetLocalMatrix(reinterpret_cast<const RwMatrix*>(m_pMatrix20));
    m_unk28 = 0;
    m_unk28 = m_unkAC;
}

// 0x005aa248 CKHkDynamicObject_OnActivate (vt+0xa0): the node takes the running matrix +0xe4, then vt+0xc0 with +0xec.
void CKHkDynamicObject::VfA0() {
    NodeOf(this)->SetLocalMatrix(reinterpret_cast<const RwMatrix*>(m_pMatrixE4));
    SetActive(m_unkEC);  // vt+0xc0
}

// 0x005abff8 CKHkDynamicObject_PostLoad (vt+0x30): IKLife's (0x19f68), the two trigger starters', the running matrix
// created; the bits 6..8 axis through the start matrix into +0xb0; the bits 9..11 axis into +0x54, through the start
// matrix when bit 12 is set, else as is. Returns 1.
int32_t CKHkDynamicObject::PostLoad(int32_t type) {
    PostLoadLife(type);         // TocBridge 0x990200 -> IKLife_PostLoad 0x19f68
    m_tsUnk98.PostLoad(type);   // TocBridge 0x990210 -> 0x236330
    m_tsUnkA0.PostLoad(type);
    m_pMatrixE4 = reinterpret_cast<CMatrix34*>(RwMatrixCreate());  // TocBridge 0x990570 -> RwMatrixCreate_Thunk 0x23fa68
    const CVector3 axis = SelectedAxis(AxisBits6(m_unk28));
    Mat4_TransformVectors(m_pMatrix20, reinterpret_cast<CVector3*>(m_aUnkB0), &axis, 1);  // TocBridge 0x9900c0
    const uint32_t flags = m_unk28;
    const CVector3 second = SelectedAxis(AxisBits9(flags));
    if ((flags & 0x1000u) == 0) {
        m_aUnk54[0] = second.x;
        m_aUnk54[2] = second.z;
        m_aUnk54[1] = second.y;
    } else {
        Mat4_TransformVectors(m_pMatrix20, reinterpret_cast<CVector3*>(m_aUnk54), &second, 1);
    }
    return 1;
}

// 0x005ac608 CKHkDynamicObject_ResetToInitialState_maybe (vt+0x38 SetDefaultState): the shared reset with +0xe8 and
// +0xbc = 0, the running matrix = the start matrix (all 16 words), +0xec = the loaded +0xa8.
void CKHkDynamicObject::SetDefaultState(int32_t /*flag*/) {
    m_unkE8 = 0.0f;
    m_unkBC = 0.0f;
    ResetMotionState();
    *m_pMatrixE4 = *m_pMatrix20;
    m_unkEC = m_unkA8;
}

// 0x005ac2a0 CKHkDynamicObject_vf3C (vt+0x3c SetGameState): game state `on` (the state word not 0) takes +0xa9 as the
// active flag, else +0xa8; the shared reset (not +0xbc); the running matrix = the end matrix +0x24 with +0xe8 = the yaw
// of its at axis less the start matrix's (Vec3_GetYawAngleFromX 0x244638 through TocBridge 0x98feb0), or the start
// matrix with +0xe8 = 0. Returns 1.
int32_t CKHkDynamicObject::SetGameState(const SApplyGameState* state) {
    const bool on = state->m_ui32GameStateId != 0;
    m_unkEC = on ? m_unkA9 : m_unkA8;
    m_unkD8 = 0.0f;
    m_unkC4 = 1.0f;
    m_unkD4 = 1;
    m_unkC0 = 0.0f;
    m_unkC8 = 0.0f;
    m_unkCC = 0.0f;
    m_unkD0 = 0.0f;
    const CVector3 axis = SelectedAxis(AxisBits6(m_unk28));
    Mat4_TransformVectors(m_pMatrix20, reinterpret_cast<CVector3*>(m_aUnkB0), &axis, 1);  // TocBridge 0x9900c0
    if (!on) {
        *m_pMatrixE4 = *m_pMatrix20;
        m_unkE8 = 0.0f;
        return 1;
    }
    *m_pMatrixE4 = *m_pMatrix24;
    const float end = Vec3_GetYawAngleFromX(&m_pMatrix24->m_at);
    const float start = Vec3_GetYawAngleFromX(&m_pMatrix20->m_at);
    m_unkE8 = end - start;
    return 1;
}

// 0x005ac9a0 CKHkDynamicObject_ResetRuntime (vt+0x50 Start): the shared reset with +0xe0 = 0 (not +0xbc), then the
// loaded flags kept in +0xac.
void CKHkDynamicObject::Start() {
    m_unkE0 = 0.0f;
    ResetMotionState();
    m_unkAC = 0;
    m_unkAC = m_unk28;
}

// 0x005ac818 CKHkDynamicObject_ReinitRuntime (vt+0x54 Restart): unless the hook's sector is unloaded (IKLife bit 2),
// the shared reset with +0xe0 and +0xbc = 0, the flags back from +0xac and the node on the running matrix.
void CKHkDynamicObject::Restart() {
    if ((m_bitArray & 4u) != 0) return;
    m_unkE0 = 0.0f;
    m_unkBC = 0.0f;
    ResetMotionState();
    m_unk28 = 0;
    m_unk28 = m_unkAC;
    NodeOf(this)->SetLocalMatrix(reinterpret_cast<const RwMatrix*>(m_pMatrixE4));  // TocBridge 0x990050
}

// ==== port-final F06 ==================================================================================================
#include <cmath>
#include <cstring>

#include "Renderware/rwcore/RwCamera.h"
#include "Spyro2008/groups/CKGrpS08Hero.h"
#include "crt/ppc_ops.h"
#include "crt/xatan.h"
#include "k2000/components/CKCurve2DCpnt.h"
#include "k2000/logic/CDefaultGameManager.h"
#include "k2000/misc/Engine.h"
#include "k2000/system/IKTime.h"

namespace {
const float kDegToRad = 0.0174532905f;    // TOC2 -0x67e4 (0x3c8efa34)
const float kRadToDeg = 57.2957802f;      // TOC2 -0x6810 (0x42652ee1)
const float kPi = 3.14159274f;            // TOC2 -0x67dc (0x40490fdb)
const float kMinusPi = -3.14159274f;      // TOC2 -0x67e0 (0xc0490fdb)
const float kTwoPi = 6.28318548f;         // TOC2 -0x6814 (0x40c90fdb)
const float kHalfPi = 1.57079637f;        // TOC2 -0x67d8 (0x3fc90fdb)
const float kMinusHalfPi = -1.57079637f;  // TOC2 -0x67d4 (0xbfc90fdb)
const CVector3 kYAxis = {0.0f, 1.0f, 0.0f};  // 0x00c50d40 (TOC2 -0x6804 points at it)

RwFrame* FrameOf(IKSerializable* node) { return static_cast<CSGMovable*>(node)->m_pRwFrame; }
CKCurve2DCpnt* Curve(IKSerializable* object) { return static_cast<CKCurve2DCpnt*>(object); }
const CVector3* AsVector(const float* v) { return reinterpret_cast<const CVector3*>(v); }

// 0x00010690 Math_Sqrtf: the double square root rounded to a float.
float SqrtF(float x) { return static_cast<float>(std::sqrt(static_cast<double>(x))); }

// The float's integer part as the code inlines it (rldicl / subfic / sraw / nor / and on the bits): the mantissa bits
// below the binary point cleared; |x| < 1 gives +0, NaN and the infinities stay.
float IntegerPartBits(float x) {
    uint32_t bits;
    std::memcpy(&bits, &x, sizeof bits);
    const int32_t e = 0x7f - static_cast<int32_t>((bits >> 23) & 0xffu);  // subfic
    int32_t fraction = 0;
    if (!(e <= -0x1f)) fraction = ppc::sraw(0x7fffff, static_cast<uint32_t>(-e));
    const int32_t whole = (e - 1) >> 31;  // srawi 31: -1 when the exponent is 127 or more
    bits &= ~(static_cast<uint32_t>(fraction) | ~static_cast<uint32_t>(whole));
    float out;
    std::memcpy(&out, &bits, sizeof out);
    return out;
}

// 0x0023fba8 Mat4_RotateAboutPoint_maybe (through TocBridge 0x990560; not in Mat4.h, CKMeshPopNodeFx.cpp has the same
// local copy): `m` turned by `degrees` about `axis` through `point` (the position moved to the point, the identity flag
// cleared, RwMatrixRotate post-concatenated, the position moved back).
void RotateMatrixAboutPoint(CMatrix34* m, const CVector3* point, const CVector3* axis, float degrees) {
    m->m_pos.x = m->m_pos.x - point->x;
    m->m_pos.y = m->m_pos.y - point->y;
    m->m_pos.z = m->m_pos.z - point->z;
    m->m_ui32Flags = m->m_ui32Flags & 0xfffdffffu;
    RwMatrixRotate(reinterpret_cast<RwMatrix*>(m), reinterpret_cast<const RwV3d*>(axis), degrees, rwCOMBINEPOSTCONCAT);
    m->m_pos.x = m->m_pos.x + point->x;
    m->m_pos.y = m->m_pos.y + point->y;
    m->m_pos.z = m->m_pos.z + point->z;
}

// The angle reached (+0xbc = the target): the trigger starter +0x98's signals, the wait +0xe0 = +0x8c, the angle
// wrapped to its fraction of a turn (fdivs by 2pi, less its integer part, fmuls by 2pi) into +0xd8 and +0xbc. Inlined
// in MessageProc 0x496 and Update.
void ReachAngle(CKHkDynamicObject* hook) {
    QueueTriggerSignals(&hook->m_tsUnk98);  // TocBridge 0x9901b0 -> 0x236338
    const float turns = hook->m_unkBC / kTwoPi;
    hook->m_unkE0 = hook->m_unk8C;
    const float wrapped = (turns - IntegerPartBits(turns)) * kTwoPi;
    hook->m_unkD8 = wrapped;
    hook->m_unkBC = wrapped;
}

// The running matrix +0xe4 takes the node's orientation (the modelling matrix's words 0x00..0x2f and pad3), its own
// position kept, the identity flag cleared (MessageProc 0x49b / 0x49c / 0x49d).
void TakeNodeOrientation(CKHkDynamicObject* hook) {
    CMatrix34* running = hook->m_pMatrixE4;
    const RwMatrix& from = FrameOf(hook->m_pKGLObject)->modelling;
    const CVector3 position = running->m_pos;
    std::memcpy(running, &from, 0x30);
    running->m_ui32pad3 = from.pad3;
    running->m_pos = position;
    running->m_ui32Flags = running->m_ui32Flags & 0xfffdffffu;
}

// The running matrix +0xe4 takes the node's position, the identity flag cleared (MessageProc 0x499 / 0x49a).
void TakeNodePosition(CKHkDynamicObject* hook) {
    CMatrix34* running = hook->m_pMatrixE4;
    const RwV3d& pos = FrameOf(hook->m_pKGLObject)->modelling.pos;
    running->m_pos.z = pos.z;
    running->m_pos.x = pos.x;
    running->m_pos.y = pos.y;
    running->m_ui32Flags = running->m_ui32Flags & 0xfffdffffu;
}

// The node's modelling position written, the identity flag cleared, the frame marked dirty (0x5aafa0 / 0x5aafc8).
void SetNodePosition(IKSerializable* node, float x, float y, float z) {
    RwFrame* frame = FrameOf(node);
    frame->modelling.pos.z = z;
    frame->modelling.pos.x = x;
    frame->modelling.pos.y = y;
    frame->modelling.flags = frame->modelling.flags & 0xfffdffffu;
    RwFrame_MarkDirty(frame);  // TocBridge 0x98fbd0 -> 0x10698
}

// The node put on the running matrix (CSGMovable_SetLocalMatrix_maybe through TocBridge 0x990050), turned in place by
// `degrees` about `axis` (CSGMovable_RotateInPlace through TocBridge 0x98fe50), its position put back to `saved`.
void TurnNode(CKHkDynamicObject* hook, const float* axis, float degrees, const RwV3d& saved) {
    CSGMovable* node = static_cast<CSGMovable*>(hook->m_pKGLObject);
    node->SetLocalMatrix(reinterpret_cast<const RwMatrix*>(hook->m_pMatrixE4));
    node->RotateInPlace(axis, degrees);
    SetNodePosition(node, saved.x, saved.y, saved.z);
}
}  // namespace

// 0x005aa480 CKHkDynamicObject_HandleMessage (vt+0x1c MessageProc; the jump table at 0x5aa4c8). `data` points at a
// float (degrees) for 0x496 / 0x497. Returns 0 for those two, 1 for the others.
int32_t CKHkDynamicObject::MessageProc(uint16_t message, void* data) {
    const uint16_t index = static_cast<uint16_t>(message - 0x496);
    if (index > 0xe) return 1;
    const float* value = static_cast<const float*>(data);
    switch (index) {
    case 0: {  // 0x496: the angle target, degrees from the origin +0xe8, wrapped into [-pi, pi]
        if ((m_unk28 & 0x10u) == 0) return 0;
        m_unkC8 = 0.0f;  // stw 0
        const float target = ppc::fmadds(*value, kDegToRad, m_unkE8);
        m_unkD8 = target;
        if (target < kMinusPi) {  // bge skips (NaN too)
            float up = target;
            do {
                up = up + kTwoPi;
            } while (up < kMinusPi);
            m_unkD8 = up;
        }
        float t = m_unkD8;
        if (t > kPi) {  // ble skips
            float down = t;
            do {
                down = down - kTwoPi;
            } while (down > kPi);
            t = down;
            m_unkD8 = down;
        }
        // The current angle +0xbc brought to the target's side of the half turns.
        float current = m_unkBC;
        if (t < 0.0f) {  // bge -> 0x5aab64
            if (current > kHalfPi) {  // ble -> 0x5aab68
                current = current - kTwoPi;
                m_unkBC = current;
            } else if (t > 0.0f && current < kMinusHalfPi) {  // 0x5aab68 (t < 0 here: never)
                current = current + kTwoPi;
                m_unkBC = current;
            }
        } else if (t > 0.0f && current < kMinusHalfPi) {  // 0x5aab68: ble / bge skip
            current = current + kTwoPi;
            m_unkBC = current;
        }
        m_unkDC = current;
        if (!(t == current)) return 0;  // bne (NaN too)
        ReachAngle(this);
        return 0;
    }
    case 1: {  // 0x497: the angle target in degrees, relative to +0xbc unless bit 18 (then absolute)
        if ((m_unk28 & 0x10u) == 0) return 0;
        m_unkC8 = 0.0f;
        float target = *value * kDegToRad;  // fmuls
        m_unkD8 = target;
        const float current = m_unkBC;
        if ((m_unk28 & 0x40000u) == 0) {
            target = target + current;  // fadds
            m_unkD8 = target;
        }
        const float wait = m_unkE0;
        m_unkDC = current;
        if (wait < 0.0f || wait == 0.0f) {  // cror lt|eq
            QueueTriggerSignals(&m_tsUnkA0);  // TocBridge 0x9901b0
        }
        return 0;
    }
    case 2:  // 0x498: the low six motion bits cleared
        m_unk28 = m_unk28 & 0xffffffc0u;
        return 1;
    case 3:  // 0x499: bit 0 (the translation) set, bits 1 and 5 cleared; the position taken from the node
        if ((m_unk28 & 1u) != 0) return 1;
        m_unk28 = ((m_unk28 & 0xfffffffeu) | 1u) & 0xffffffddu;
        TakeNodePosition(this);
        m_unkC8 = 0.0f;  // stw 0
        m_unkC0 = 0.0f;  // stw 0
        return 1;
    case 4:  // 0x49a: bit 1 (the turn about a point) set, bit 0 cleared; the position taken from the node
        if ((m_unk28 & 2u) != 0) return 1;
        m_unk28 = (m_unk28 & 0xfffffffcu) | 2u;
        TakeNodePosition(this);
        m_unkC8 = 0.0f;
        m_unkC0 = 0.0f;
        return 1;
    case 5:  // 0x49b: bit 2 (the spin) set, bits 3..5 cleared
        if ((m_unk28 & 4u) != 0) return 1;
        m_unk28 = (m_unk28 & 0xffffffc3u) | 4u;
        TakeNodeOrientation(this);
        m_unkD8 = 0.0f;
        m_unkBC = 0.0f;
        m_unkCC = 0.0f;
        return 1;
    case 6:  // 0x49c: bit 4 (the angle target) set, bits 2, 3 and 5 cleared (the zeros stored as words)
        if ((m_unk28 & 0x10u) != 0) return 1;
        m_unk28 = (m_unk28 & 0xffffffc3u) | 0x10u;
        TakeNodeOrientation(this);
        m_unkD8 = 0.0f;
        m_unkBC = 0.0f;
        m_unkCC = 0.0f;
        return 1;
    case 7:  // 0x49d: bit 3 (face the hero) set, bits 2, 4 and 5 cleared
        if ((m_unk28 & 8u) != 0) return 1;
        m_unk28 = (m_unk28 & 0xffffffc3u) | 8u;
        TakeNodeOrientation(this);
        m_unkD8 = 0.0f;
        m_unkBC = 0.0f;
        m_unkCC = 0.0f;
        return 1;
    case 8:  // 0x49e .. 0x4a2: one motion bit cleared (0, 1, 2, 4, 3)
        m_unk28 = m_unk28 & 0xfffffffeu;
        return 1;
    case 9:
        m_unk28 = m_unk28 & 0xfffffffdu;
        return 1;
    case 10:
        m_unk28 = m_unk28 & 0xfffffffbu;
        return 1;
    case 11:
        m_unk28 = m_unk28 & 0xffffffefu;
        return 1;
    case 12:
        m_unk28 = m_unk28 & 0xfffffff7u;
        return 1;
    case 13:  // 0x4a3 / 0x4a4: active / inactive (vt+0xc0)
        SetActive(1);
        return 1;
    default:
        SetActive(0);
        return 1;
    }
}

// 0x005aab98 CKHkDynamicObject_Update (vt+0x7c). The bits of +0x28: 0 the translation (bit 15 along the curve +0x44,
// else +0x38 per second up to +0x3c; bit 14 back to the start at the end, bit 13 back and forth with the direction
// byte +0xd4), 1 the turn about the point +0x48 / axis +0x54 (bit 17 the curve +0x68, else +0x64 per second; bit 5 the
// node also faces the point), 2 the spin about +0xb0 (bit 16 the curve +0x80), 3 face the focused hero (yaw, at most
// +0x6c either side, +0x70 per second, within +0x74), 4 turn to the target angle +0xd8 (+0x88 per second, bit 18 along
// the curve +0x84), the wait +0xe0 before the next. Then the axes scaled by +0x90.
void CKHkDynamicObject::Update(IKTime* clock) {
    const float dt = clock->m_afDeltaTime[0];  // lfs +0x1c
    if (m_unkEC == 0) return;
    uint32_t flags = m_unk28;
    const CVector3* point = AsVector(m_aUnk48);
    const CVector3* axis = AsVector(m_aUnk54);
    if ((flags & 1u) != 0) {
        // The translation (0x5aaf18): the position along +0x2c from the running matrix's.
        const CVector3& origin = m_pMatrixE4->m_pos;
        const int8_t direction = static_cast<int8_t>(m_unkD4);
        float x;
        float y;
        float z;
        if ((flags & 0x8000u) != 0) {
            const float t = ppc::fmadds(dt, static_cast<float>(direction), m_unkC8);  // fcfid / frsp
            m_unkC8 = t;
            if (m_pUnk44 == nullptr) {
                z = origin.z;
                x = origin.x;
                y = origin.y;
            } else {
                bool evaluate = true;
                float at = t;
                if (t < m_unk40 && t > 0.0f) {  // bge / bgt
                    at = t;
                } else if ((flags & 0x4000u) != 0) {
                    m_unkC0 = 0.0f;
                    m_unkC8 = 0.0f;
                    z = origin.z;
                    x = origin.x;
                    y = origin.y;
                    evaluate = false;
                } else if ((flags & 0x2000u) == 0) {
                    at = m_unk40;
                    m_unkC8 = m_unk40;
                } else {
                    if (direction <= 0) {
                        at = 0.0f;
                        m_unkC8 = 0.0f;
                    } else {
                        at = m_unk40;
                        m_unkC8 = m_unk40;
                    }
                    m_unkD4 = static_cast<uint8_t>(-static_cast<int32_t>(m_unkD4));  // neg, stb
                }
                if (evaluate) {
                    const float s = Curve(m_pUnk44)->Evaluate(at);  // TocBridge 0x990550 -> 0x249ea8
                    m_unkC0 = s;
                    z = ppc::fmadds(s, m_aUnk2C[2], origin.z);
                    x = ppc::fmadds(s, m_aUnk2C[0], origin.x);
                    y = ppc::fmadds(s, m_aUnk2C[1], origin.y);
                }
            }
        } else {
            const float end = m_unk3C;
            const float s = ppc::fmadds(dt, static_cast<float>(direction) * m_unk38, m_unkC0);  // fcfid / frsp, fmuls
            if (s < end && s > 0.0f) {  // bge / bgt
                m_unkC0 = s;
                z = ppc::fmadds(s, m_aUnk2C[2], origin.z);
                x = ppc::fmadds(s, m_aUnk2C[0], origin.x);
                y = ppc::fmadds(s, m_aUnk2C[1], origin.y);
            } else {
                if (direction <= 0) {
                    z = origin.z;
                    x = origin.x;
                    y = origin.y;
                } else {
                    x = ppc::fmadds(end, m_aUnk2C[0], origin.x);
                    z = ppc::fmadds(end, m_aUnk2C[2], origin.z);
                    y = ppc::fmadds(end, m_aUnk2C[1], origin.y);
                }
                if ((flags & 0x4000u) != 0) {
                    m_unkC0 = 0.0f;  // stw 0
                    z = origin.z;
                    x = origin.x;
                    y = origin.y;
                } else if ((flags & 0x2000u) != 0) {
                    if (direction <= 0) {
                        m_unkC0 = 0.0f;  // stw 0
                    } else {
                        m_unkC0 = end;
                    }
                    m_unkD4 = static_cast<uint8_t>(-static_cast<int32_t>(m_unkD4));  // neg, stb
                }
            }
        }
        SetNodePosition(m_pKGLObject, x, y, z);
        flags = m_unk28;
    } else if ((flags & 2u) != 0) {
        // The turn about the point +0x48 / axis +0x54 by +0xc0 degrees (0x5aac08).
        if ((flags & 0x20000u) == 0) {
            m_unkC0 = ppc::fmadds(dt, m_unk64, m_unkC0);
        } else {
            float t = dt + m_unkC8;  // fadds
            m_unkC8 = t;
            if (t > m_unk60) {  // bgt
                t = t - m_unk60;
                m_unkC8 = t;
            }
            m_unkC0 = Curve(m_pUnk68)->Evaluate(t);  // TocBridge 0x990550
            flags = m_unk28;
        }
        const CVector3& pos = m_pMatrixE4->m_pos;
        if ((flags & 0x20u) == 0) {
            // 0x5ab26c: the running position turned about the point in an identity matrix.
            alignas(16) CMatrix34 turned{};
            turned.m_ui32Flags = 0x20003u;
            turned.m_pos.x = 0.0f;
            turned.m_at.z = 1.0f;
            turned.m_up.y = 1.0f;
            turned.m_up.x = 0.0f;
            turned.m_right.z = 0.0f;
            turned.m_right.y = 0.0f;
            turned.m_at.y = 0.0f;
            turned.m_at.x = 0.0f;
            turned.m_up.z = 0.0f;
            turned.m_pos.z = 0.0f;
            turned.m_pos.y = 0.0f;
            turned.m_right.x = 1.0f;
            turned.m_pos.x = pos.x;
            turned.m_pos.y = pos.y;
            turned.m_pos.z = pos.z;
            turned.m_ui32Flags = turned.m_ui32Flags & 0xfffdffffu;
            RotateMatrixAboutPoint(&turned, point, axis, m_unkC0);  // TocBridge 0x990560 -> 0x23fba8
            SetNodePosition(m_pKGLObject, turned.m_pos.x, turned.m_pos.y, turned.m_pos.z);
        } else {
            // 0x5aac30: the node faces the point (its offset from the running position, less the part along the axis,
            // normalised), sits at the running position, then turns about the point.
            CVector3 v;
            v.y = point->y - pos.y;
            v.x = point->x - pos.x;
            v.z = point->z - pos.z;
            float d = v.y * axis->y;
            d = ppc::fmadds(v.x, axis->x, d);
            d = ppc::fnmadds(v.z, axis->z, d);
            v.y = ppc::fmadds(d, axis->y, v.y);
            v.x = ppc::fmadds(axis->x, d, v.x);
            v.z = ppc::fmadds(d, axis->z, v.z);
            float square = v.y * v.y;
            square = ppc::fmadds(v.x, v.x, square);
            square = ppc::fmadds(v.z, v.z, square);
            const float length = SqrtF(square);  // TocBridge 0x98fc10 -> 0x10690
            if (!(length == 0.0f)) {  // bne (NaN too)
                const float inverse = 1.0f / length;
                v.z = v.z * inverse;
                v.x = v.x * inverse;
                v.y = v.y * inverse;
            }
            CSGMovable* node = static_cast<CSGMovable*>(m_pKGLObject);
            node->SetOrientationFromAtUp(&v, &m_pMatrixE4->m_up);  // TocBridge 0x98fcf0 -> 0xd0918
            SetNodePosition(node, m_pMatrixE4->m_pos.x, m_pMatrixE4->m_pos.y, m_pMatrixE4->m_pos.z);
            node->RotateAboutPoint(m_unkC0, point, axis);  // TocBridge 0x990540 -> 0xd0f80
        }
        flags = m_unk28;
    }

    // The rotation (0x5aad68): the node's position kept across it.
    const RwV3d saved = FrameOf(m_pKGLObject)->modelling.pos;
    if ((flags & 4u) != 0) {
        // The spin about +0xb0 (0x5aad98): +0xbc degrees.
        if ((flags & 0x10000u) == 0) {
            m_unkBC = ppc::fmadds(dt, m_unk78, m_unkBC);
        } else {
            const float t = dt + m_unkCC;  // fadds
            m_unkCC = t;
            if (m_unk7C < t) m_unkCC = 0.0f;  // bge skips; stw 0
            if (m_pUnk80 == nullptr) {
                m_unkBC = 0.0f;
            } else {
                m_unkBC = Curve(m_pUnk80)->Evaluate(m_unkCC);  // TocBridge 0x990550
            }
        }
        // +0xbc is passed as it is here (lfs, no fmuls): degrees in this mode, where the other turns convert radians.
        TurnNode(this, m_aUnkB0, m_unkBC, saved);
    } else if ((flags & 8u) != 0) {
        // Face the focused hero (0x5aaff0): the yaw to it in the xz plane, clamped to +0x6c either side of the running
        // matrix's at axis, approached at +0x70 per second while the hero is within +0x74.
        CKGrpS08Hero* group = static_cast<CKGrpS08Hero*>(g_pEngine->m_gameManager->m_unk04[1]);
        if (group != nullptr) {
            float dy = 0.0f;  // f29
            // 0x002ca128 CKGrpS08Hero_GetFocusedHeroNode_maybe (TocBridge 0x9902e0)
            IKSerializable* hero =
                group->m_ui8FocusedDragon == 0xff ? nullptr : group->m_apCameraTargets[static_cast<int8_t>(group->m_ui8FocusedDragon)];
            const RwV3d& heroPos = FrameOf(hero)->ltm.pos;
            const RwV3d& ownPos = FrameOf(m_pKGLObject)->modelling.pos;
            float dx = heroPos.x - ownPos.x;
            float dz = heroPos.z - ownPos.z;
            float length = SqrtF(ppc::fmadds(dz, dz, ppc::fmadds(dx, dx, dy)));  // TocBridge 0x98fc10
            if (!(length == 0.0f)) {  // bne
                const float inverse = 1.0f / length;
                dz = dz * inverse;
                dx = dx * inverse;
                dy = inverse * dy;
            } else {
                length = dy;
            }
            if (!(m_unk74 >= length)) {  // cror gt|eq, bne: beyond the reach, the yaw kept
                TurnNode(this, &kYAxis.x, m_unkBC * kRadToDeg, saved);
            } else {
                const CMatrix34* running = m_pMatrixE4;
                float c = ppc::fmadds(dz, running->m_at.z, ppc::fmadds(dx, running->m_at.x, dy * running->m_at.y));
                if (std::fabs(c) > 1.0f) c = c < 0.0f ? -1.0f : 1.0f;  // ble skips; TOC2 -0x67c4 / -0x67cc
                float angle = crt::Acosf(c);  // 0x780c90
                const float side =
                    ppc::fmadds(dz, running->m_right.z, ppc::fmadds(dx, running->m_right.x, dy * running->m_right.y));
                if (side < 0.0f) angle = -angle;
                const float limit = m_unk6C;
                if (angle > limit) angle = limit;
                float target = -limit;
                if (!(angle < target)) target = angle;  // bge
                float current;
                if (target < 0.0f) {  // blt -> 0x5ab4dc
                    current = m_unkBC;
                    if (current > kHalfPi) {  // ble skips
                        current = current - kTwoPi;
                        m_unkBC = current;
                    } else if (target > 0.0f && current < kMinusHalfPi) {  // 0x5ab114 (target < 0: never)
                        current = current + kTwoPi;
                        m_unkBC = current;
                    }
                } else {
                    current = m_unkBC;
                    if (target > 0.0f && current < kMinusHalfPi) {  // ble / bge skip
                        current = current + kTwoPi;
                        m_unkBC = current;
                    }
                }
                if (!(target < current)) {  // bge -> 0x5ab570
                    const float next = ppc::fmadds(dt, m_unk70, current);
                    m_unkBC = next;
                    if (target < next) m_unkBC = target;  // bge skips
                } else {
                    const float next = current - dt * m_unk70;  // fmuls, fsubs
                    m_unkBC = next;
                    if (target > next) m_unkBC = target;  // ble skips
                }
                TurnNode(this, &kYAxis.x, m_unkBC * kRadToDeg, saved);
            }
        }
    } else if ((flags & 0x10u) != 0) {
        // Turn to the target angle (0x5aae00), after the wait +0xe0.
        const float wait = m_unkE0;
        if (wait > 0.0f) {  // ble -> 0x5ab5a8
            const float left = wait - dt;
            m_unkE0 = left;
            if (left < 0.0f || left == 0.0f) {  // cror lt|eq
                m_unkE0 = 0.0f;
                QueueTriggerSignals(&m_tsUnkA0);  // TocBridge 0x9901b0
            }
        } else {
            const float target = m_unkD8;
            const float current = m_unkBC;
            if (!(target == current)) {  // beq -> the scale
                bool reached = false;
                if ((flags & 0x40000u) != 0) {
                    // 0x5ab64c: along the curve +0x84 from +0xdc to the target, until its last point's x.
                    const float t = dt + m_unkC8;  // fadds
                    CKCurve2DCpnt* curve = Curve(m_pUnk84);
                    float last = 0.0f;  // f13 is 0 on this path
                    m_unkC8 = t;
                    const uint32_t count = curve->m_points.m_ui32NbUsedElt;
                    if (count != 0) last = curve->m_points.m_pBlock[count - 1].m_fX;
                    if (last < t) {  // bge -> 0x5ab768
                        m_unkC8 = count != 0 ? curve->m_points.m_pBlock[count - 1].m_fX : 0.0f;  // a word copy
                        reached = true;
                    } else {
                        const float from = m_unkDC;
                        const float span = target - from;
                        m_unkBC = ppc::fmadds(span, curve->Evaluate(t), from);  // TocBridge 0x990550
                    }
                } else if (!(target < current)) {  // bge cr6 -> 0x5ab748
                    const float next = ppc::fmadds(dt, m_unk88, current);
                    m_unkBC = next;
                    if (next > target) reached = true;  // ble skips
                } else {
                    const float next = current - dt * m_unk88;  // fmuls, fsubs
                    m_unkBC = next;
                    if (next < target) reached = true;  // blt
                }
                if (reached) {
                    m_unkBC = target;
                    ReachAngle(this);
                }
                TurnNode(this, m_aUnkB0, m_unkBC * kRadToDeg, saved);
            }
        }
    }

    // The axes scaled by +0x90 (0x5aae28), the identity and normal flags cleared, the frame marked dirty.
    RwFrame* frame = FrameOf(m_pKGLObject);
    RwMatrix& m = frame->modelling;
    const float scale = m_unk90;
    m.right.x = scale * m.right.x;
    m.right.y = scale * m.right.y;
    m.right.z = scale * m.right.z;
    m.up.x = scale * m.up.x;
    m.up.y = scale * m.up.y;
    m.up.z = scale * m.up.z;
    m.at.x = scale * m.at.x;
    m.at.z = scale * m.at.z;
    m.at.y = scale * m.at.y;
    m.flags = m.flags & 0xfffdfffeu;
    RwFrame_MarkDirty(frame);  // TocBridge 0x98fbd0
}
