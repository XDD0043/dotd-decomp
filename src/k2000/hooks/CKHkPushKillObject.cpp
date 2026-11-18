// Reconstructed original translation unit: 0x42cce0-0x42ffb0 (GAME_TOC1, main_toc1), 36 functions, 33 live.
// Primary class: CKHkPushKillObject  key 0xd42  category Hook  size 0xe4  vtable 0xb262f0
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x42cce0  CKHkPushKillObject_Delete  (DOTD_DECLARE_FACTORIES)
//   [ ] 0x42cd30  CKHkPushKillObject_ResetRuntimeState_maybe  [dead]
//   [x] 0x42cd70  CKHkPushKillObject_vfC8  (CKHkPushKillObject.h ApplyStatePreset)
//   [x] 0x42cd98  CKHkPushKillObject_vfC0
//   [ ] 0x42cde0  RegisterCKHkPushKillObjectClass
//   [ ] 0x42ce58  _GLOBAL__I_42ce58
//   [x] 0x42ce68  CKHkPushKillObject_GetInfo
//   [x] 0x42cf50  CKHkPushKillObject_SetDefaultState  (CKHkPushKillObject.h)
//   [x] 0x42cfa8  CKHkPushKillObject_UpdateSpin_maybe  (UpdateSpin)
//   [x] 0x42d178  CKHkPushKillObject_Resume  (empty / no effect: inherited, KStub_Nop_3f6e60)
//   [x] 0x42d1a0  CKHkPushKillObject_Pause  (empty / no effect: inherited, KStub_Nop_3f6e58)
//   [x] 0x42d1c8  CKHkPushKillObject_Stop  (empty / no effect: inherited, CKHkActorBase_d82_maybe_Stop 0x3f6e50)
//   [x] 0x42d1f0  CKHkPushKillObject_Start  (= the inherited slot: CKHkActorBase_d82_maybe_ResetRuntime (empty))
//   [x] 0x42d218  CKHkPushKillObject_AttachSounds
//   [x] 0x42d2b0  CKHkPushKillObject_PostLoad  (= the inherited slot: CKHkActorBase_d82_maybe_PostLoad, then 1)
//   [ ] 0x42d2d8  CKHkPushKillObject_Save
//   [x] 0x42d300  CKHkPushKillObject_RecursiveRegistration  (= the inherited slot: CKHkActorBase_d82_maybe_RecursiveRegistration, then 1)
//   [x] 0x42d328  CKHkPushKillObject_Destroy  (= the inherited slot: CKHkActorBase_d82_maybe_Destroy (vt+0xc0))
//   [ ] 0x42d350  CKHkPushKillObject_Construct  [dead]
//   [x] 0x42d388  CKHkPushKillObject_DeleteArray  (DOTD_DECLARE_FACTORIES)
//   [x] 0x42d428  CKHkPushKillObject_DeletingDestructor  (the deleting form of the implicit destructor)
//   [x] 0x42d470  CKHkPushKillObject_Destructor  (the C++ destructor (CKHkActorBase_d82_maybe_BaseDestructor))
//   [x] 0x42d4a0  CKHkPushKillObject_BaseDestructor  (C++ destructor chain: vtable stores only)
//   [ ] 0x42d4d0  CKHkPushKillObject_Construct_2  [dead]
//   [x] 0x42d508  CKHkPushKillObject_CreateArray  (DOTD_DECLARE_FACTORIES)
//   [x] 0x42d5b8  CKHkPushKillObject_Create  (DOTD_DECLARE_FACTORIES)
//   [x] 0x42d610  CKHkPushKillObject_UpdateCurveMotion_maybe  (UpdateCurveMotion)
//   [x] 0x42d9a8  CKHkPushKillObject_UpdateAxisPosition_maybe  (UpdateAxisPosition)
//   [x] 0x42dbf0  CKHkPushKillObject_OnActivate  (VfA0)
//   [x] 0x42de58  CKHkPushKillObject_UpdateVolumesAndFx_maybe  (UpdateVolumesAndFx)
//   [x] 0x42e9b0  CKHkPushKillObject_OnDeactivate  (VfA4)
//   [x] 0x42ea68  CKHkPushKillObject_Update
//   [x] 0x42ebf8  CKHkPushKillObject_Restart
//   [x] 0x42ed08  CKHkPushKillObject_Load
//   [x] 0x42f6b0  CKHkPushKillObject_MessageProc
//
//   [x] 0x9c32b8  CKHkPushKillObject_IsKindOfClass  [inline]  (CKHkPushKillObject.h)
//   [x] 0x9c3310  CKHkPushKillObject_GetClassType  [inline]  (DOTD_CLASS_KEY)
//   [x] 0x9c3318  CKHkPushKillObject_GetClassID  [inline]  (DOTD_CLASS_KEY)
//   [x] 0x9c3320  CKHkPushKillObject_GetTriggerProp98  [inline]  (GetInfo)
#include "k2000/hooks/CKHkPushKillObject.h"

#include <cmath>
#include <cstring>

#include "k2000/core/IKInfo.h"
#include "k2000/dictionaries/CKSoundDictionaryID.h"
#include "k2000/io/IKFile.h"
#include "k2000/logic/sound/CKSound.h"
#include "k2000/memory/Mem.h"
#include "Renderware/rwcore/RwCamera.h"
#include "Spyro2008/groups/CKGrpS08Hero.h"
#include "Spyro2008/hooks/CKHkS08Hero.h"
#include "crt/ppc_ops.h"
#include "k2000/cameras/CKSrvCamera.h"
#include "k2000/cameras/IKCamera.h"
#include "k2000/fx/CKSparkFxData.h"
#include "k2000/fx/IKFx.h"
#include "k2000/logic/CDefaultGameManager.h"
#include "k2000/logic/CKParticlesEffectFxData.h"
#include "k2000/logic/CSGHotSpot.h"
#include "k2000/logic/fx/CKParticlesEffectNodeFx.h"
#include "k2000/misc/ClassRegistry.h"
#include "k2000/misc/Engine.h"
#include "k2000/misc/FloatApproach.h"
#include "k2000/misc/Mat4.h"
#include "k2000/scenegraph/CKSparkParam.h"
#include "k2000/scenegraph/CSGBranch.h"
#include "k2000/scenegraph/CSGMovable.h"
#include "k2000/scenegraph/IKBoundingVolume.h"
#include "k2000/services/CKSrvCollision.h"
#include "k2000/services/CKSrvFx.h"
#include "k2000/system/IKTime.h"

// 0x0042ed08 CKHkPushKillObject_Load: +0x98 = 1.3 (TOC1 +0x4f14) for every type, the rest for the level type 0 only.
int32_t CKHkPushKillObject::Load(IKFile* file, int32_t type) {
    CKHkActorBase::Load(file, type);  // 0x003f6e98
    m_unk88[4] = 1.3f;                // +0x98
    if (type != 0) return 1;
    IKFile_ReadRef(file, &m_unkB0);
    m_tsHit.Load(file, 0);  // 0x002361c0
    ReadU32LE(file, &m_ui32KeyCount);
    m_afKeys = static_cast<float*>(Mem_AllocAligned16(m_ui32KeyCount * 8u));
    ReadU32LEWords(file, reinterpret_cast<uint32_t*>(m_afKeys), m_ui32KeyCount * 2u);  // one read, then each word swapped
    IKFile_ReadRef(file, &m_pSounds);
    ReadU8(file, &m_ui8Spins);
    ReadF32LE(file, &m_fSpinMax);
    ReadF32LE(file, &m_fSpinAccel);
    ReadU8(file, &m_ui8Axis);
    ReadU8(file, &m_ui8MoveAxis);
    for (float& value : m_unkA0) ReadF32LE(file, &value);
    ReadU8(file, &m_ui8Presets);
    IKFile_ReadRef(file, &m_pVolume);
    ReadU8(file, &m_ui8Damage);
    for (float& value : m_afKnock) ReadF32LE(file, &value);
    ReadU32LEWords(file, reinterpret_cast<uint32_t*>(&m_unk40), 3);
    ReadU32LEWords(file, reinterpret_cast<uint32_t*>(&m_unk4C), 3);
    IKFile_ReadRef(file, &m_pFxData2C);
    IKFile_ReadRef(file, &m_pFxData30);
    IKFile_ReadRef(file, &m_pFxData38);
    IKFile_ReadRef(file, &m_pFxData34);
    for (float& value : m_unk88) ReadF32LE(file, &value);
    IKFile_ReadRef(file, &m_pKillCamera);
    ReadF32LE(file, &m_fKillCameraTime);
    return 1;
}

// 0x0042cd98 CKHkPushKillObject_vfC0
void CKHkPushKillObject::VfC0() {
    if (m_afKeys == nullptr) return;
    Mem_FreeAligned16(m_afKeys);  // 0x00052fb8
    m_afKeys = nullptr;
}

// 0x0042ce68 CKHkPushKillObject_GetInfo
int32_t CKHkPushKillObject::GetInfo(IKInfo* info, int32_t request) {
    const int32_t base = CKHkActorBase::GetInfo(info, request);  // KStub_Return1 0x3f7140
    bool unknown = true;
    if (request == kGetInfoValueAccessor && info->m_ui32Id == 0x98) {
        AnswerInfo(info, [](IKSerializable* o, uint32_t) {  // 0x009c3320
            return static_cast<uint32_t>(static_cast<CKHkPushKillObject*>(o)->m_ui8Pushed);
        }, 0);
        unknown = false;
    }
    if (base == 2) return 2;
    if (!unknown) return 0;
    return base == 0 ? 0 : 1;
}

// 0x0042d218 CKHkPushKillObject_AttachSounds
void CKHkPushKillObject::KGLObjectAttached(IKSerializable* leaf) {
    CKSoundDictionaryID* sounds = static_cast<CKSoundDictionaryID*>(m_pSounds);
    sounds->GetSound(0)->SetAttachObject(leaf);  // 0x00112bc0, 0x00111350
    sounds->GetSound(1)->SetAttachObject(leaf);
    sounds->GetSound(2)->SetAttachObject(leaf);
}

namespace {

const float kZero = 0.0f;           // TOC1 +0x4ee4 0x00000000
const float kOne = 1.0f;            // TOC1 +0x4eb0 0x3f800000
const float kQuarterTurn = 90.0f;   // TOC1 +0x4edc 0x42b40000
const float kRandMax = 65535.0f;    // TOC1 +0x4f04 0x477fff00
const float kRandScale = -2.0f;     // TOC1 +0x4f08 0xc0000000
const CVector3 kAxisY = {0.0f, 1.0f, 0.0f};    // 0x00c50d40 (TOC1 +0x4ee0, the shared Y axis)
const CVector3 kNullVector = {0.0f, 0.0f, 0.0f};  // 0x00c50d64 (TOC1 +0x4f10)

CSGMovable* Node(const CKHkPushKillObject* o) { return static_cast<CSGMovable*>(o->m_pKGLObject); }
CMatrix34* StartMatrix(const CKHkPushKillObject* o) { return reinterpret_cast<CMatrix34*>(o->m_pStartMatrix); }
CKSound* Sound(const CKHkPushKillObject* o, uint32_t index) {
    return static_cast<CKSoundDictionaryID*>(o->m_pSounds)->GetSound(index);  // 0x00112bc0
}
CKSrvCollision* Collision() { return static_cast<CKSrvCollision*>(g_pEngine->m_srvCollision); }  // engine +0x58
CKSrvFx* FxService() { return static_cast<CKSrvFx*>(g_pEngine->m_srvFx); }                       // engine +0x60
IKBoundingVolume* Volume(const CKHkPushKillObject* o) { return static_cast<IKBoundingVolume*>(o->m_pVolume); }

// The start matrix's axis `axis` (0 right, 1 up, 2 at). BUG(original): another value leaves the three registers the
// caller had (UpdateAxisPosition: y is the frame's dt); zeros here (no level holds the class).
CVector3 StartAxis(const CKHkPushKillObject* o, uint8_t axis) {
    const CMatrix34* m = StartMatrix(o);
    if (axis == 1) return m->m_up;
    if (axis == 0) return m->m_right;
    if (axis == 2) return m->m_at;
    return kNullVector;
}

// The node's modelling position set, its matrix no longer the identity (bit 17), the frame marked dirty.
void PlaceNode(CSGMovable* node, float x, float y, float z) {
    RwFrame* frame = node->m_pRwFrame;
    frame->modelling.pos.z = z;
    frame->modelling.pos.x = x;
    frame->modelling.pos.y = y;
    frame->modelling.flags &= 0xfffdffffu;
    RwFrame_MarkDirty(node->m_pRwFrame);  // 0x00010698
}

// The volume under the node: off its old parent (vt+0x78), onto the node (vt+0x70).
void VolumeUnderNode(CKHkPushKillObject* o) {
    IKBoundingVolume* volume = Volume(o);
    if (volume->m_pParent != nullptr) volume->m_pParent->RemoveChild(volume);  // vt+0x78
    static_cast<CSGBranch*>(o->m_pKGLObject)->AddChild(Volume(o));            // vt+0x70
}

// The hero's hazard query 0xc32 (CKHkCrumblyZone.cpp's ZoneHazardQuery, the same layout).
struct PushKillHazardQuery {
    CKHkS08Hero* m_hero;         // +0x00
    IKBoundingVolume* m_volume;  // +0x04
    float m_knock08;             // +0x08
    float m_knock0C;             // +0x0c
    float m_knock10;             // +0x10
    CVector3 m_point;            // +0x14
    int32_t m_kind;              // +0x20
    uint8_t m_damage;            // +0x24
    uint8_t m_unk25;             // +0x25
};

}  // namespace

// 0x0042cfa8 CKHkPushKillObject_UpdateSpin_maybe
uint8_t CKHkPushKillObject::UpdateSpin(float dt) {
    if (m_ui8Spins == 0) return 1;
    float& angle = m_unkC4[4];  // +0xd4
    float& speed = m_unkC4[5];  // +0xd8
    uint8_t done = 0;
    float current = 0.0f;
    if (m_ui8Pushed != 0 || m_unkC4[0] != kZero) {  // the curve time: fcmpu / bne (NaN: speeding up)
        const float raised = ppc::fmadds(dt, m_fSpinAccel, speed);
        const float max = m_fSpinMax;
        speed = raised;
        if (!(raised > max)) {  // ble (NaN: kept, not done)
            current = raised;
            done = max == raised ? 1 : 0;
        } else {
            speed = max;
            done = 1;
            current = speed;
        }
    } else {
        const float lowered = speed - dt * m_fSpinAccel;  // fmuls, fsubs
        speed = lowered;
        if (!(lowered > kZero)) {  // ble (NaN: stopped)
            current = kZero;
            done = 1;
            speed = kZero;
        } else {
            current = speed;
        }
    }
    const float turned = angle - dt * current;  // fmuls, fsubs
    angle = turned;
    if (current != kZero) {
        const uint32_t quarter = (static_cast<uint32_t>(Rand_Int()) >> 14) & 3u;  // 0x00011500; rldicl 50, 62
        angle = ppc::fmadds(static_cast<float>(quarter), kQuarterTurn, turned);
    }
    Node(this)->SetOrientationFromAtUp(&StartMatrix(this)->m_at, &kAxisY);  // 0x000d0918
    Node(this)->RotateInPlace(reinterpret_cast<const float*>(&Node(this)->m_pRwFrame->modelling.at), angle);  // 0x000d11b0
    return done;
}

// 0x0042d610 CKHkPushKillObject_UpdateCurveMotion_maybe
void CKHkPushKillObject::UpdateCurveMotion(float dt) {
    const uint32_t count = m_ui32KeyCount;
    const float time = dt + m_unkC4[0];  // fadds
    m_unkC4[1] = m_unkC4[2];
    m_unkC4[0] = time;
    if (m_afKeys[(count - 1) * 2] <= time) m_unkC4[0] = 0.0f;  // cror lt|eq; stw 0
    // The last key at or before the time, searched from the end; none: no offset.
    float offset = kZero;
    for (uint32_t i = count; i-- != 0;) {
        const float* key = m_afKeys + i * 2;
        const float keyTime = key[0];
        const float now = m_unkC4[0];
        if (!(keyTime <= now)) continue;  // cror lt|eq, bne (NaN: keeps searching)
        float value = key[1];
        if (i + 1 < count) {  // cmplw / blt
            const float* next = key + 2;
            const float slope = (next[1] - value) / (next[0] - keyTime);
            value = ppc::fmadds(slope, now - keyTime, value);
        }
        offset = value + 0.0f;  // the stored zero word added (fadds)
        break;
    }
    const CVector3 start = StartMatrix(this)->m_pos;
    CVector3 axis = StartAxis(this, m_ui8Axis);
    m_unkC4[2] = offset;
    const float length = std::sqrt(ppc::fmadds(axis.z, axis.z, ppc::fmadds(axis.x, axis.x, axis.y * axis.y)));  // 0x10690
    if (length != kZero) {
        const float scale = offset / length;
        axis.z = axis.z * scale;
        axis.x = axis.x * scale;
        axis.y = axis.y * scale;
    }
    PlaceNode(Node(this), axis.x + start.x, start.y + axis.y, start.z + axis.z);
    // The curve sound's speed and the spark intensity: full (1 - distance / ramp, doubled for the spark) inside the ramp
    // at either end ([0] / [1]), the top speed less (top - lowest) x that share, clamped to [lowest, top].
    const float top = m_unkC4[3];
    const float span = top - m_unk88[3];
    const float ramp = (m_unk88[1] - m_unk88[0]) * m_unk88[2];
    float spark = kZero;
    float target = top;
    if (std::fabs(m_unk88[0] - offset) < ramp) {  // bge (NaN: the other end)
        const float share = kOne - std::fabs(m_unk88[0] - offset) / ((m_unk88[1] - m_unk88[0]) * m_unk88[2]);
        spark = share + share;
        target = m_unkC4[3] - span * share;
    } else {
        const float distance = m_unk88[1] - offset;
        if (!(ramp <= distance)) {  // ble (NaN: full speed)
            const float share = kOne - distance / ramp;
            spark = share + share;
            target = m_unkC4[3] - span * share;
        }
    }
    CKSound* sound = Sound(this, 1);
    float speed;
    if (target <= m_unk88[3]) {  // cror lt|eq
        speed = m_unk88[3];
    } else if (target >= m_unkC4[3]) {  // cror gt|eq (NaN: the computed value)
        speed = m_unkC4[3];
    } else {
        speed = target;
    }
    sound->SetSpeed(speed);  // 0x00110e98 (no null test)
    CKSparkFxData* sparkData = static_cast<CKSparkFxData*>(m_pFxData2C);
    static_cast<CKSparkParam*>(sparkData->m_pSparkParam)->m_afUnk04[27] = spark;  // +0x70
}

// 0x0042d9a8 CKHkPushKillObject_UpdateAxisPosition_maybe
void CKHkPushKillObject::UpdateAxisPosition(float dt) {
    // FloatApproachAccel state {target, top speed, speed, acceleration, current} on the stack.
    float state[5];
    state[0] = 0.0f;
    state[1] = m_unkA0[1];
    state[2] = m_unkC4[7];
    state[3] = m_unkA0[2];
    state[4] = m_unkC4[6];
    bool starting;
    if (m_ui8Pushed == 0) {
        state[0] = m_unkA0[0];
        starting = m_unkC4[6] == kZero;  // fcmpu / beq
    } else {
        starting = m_unkA0[0] == m_unkC4[6];  // bne: not starting
    }
    if (starting) {
        Sound(this, 0)->SetLoop(0);    // 0x00110fd0
        CKSound_Play(kZero, Sound(this, 0));  // 0x00111230
    }
    FloatApproachAccel_Step(dt, state);  // 0x00243800
    m_unkC4[6] = state[4];
    m_unkC4[7] = state[2];
    CVector3 axis;
    if (m_ui8MoveAxis == 1 || m_ui8MoveAxis == 0 || m_ui8MoveAxis == 2) {
        axis = StartAxis(this, m_ui8MoveAxis);
    } else {
        // BUG(original): the registers keep the caller's values (y: dt); this keeps that much.
        axis = {0.0f, dt, 0.0f};
    }
    const float length = std::sqrt(ppc::fmadds(axis.z, axis.z, ppc::fmadds(axis.x, axis.x, axis.y * axis.y)));
    const float position = m_unkC4[6];
    if (length != kZero) {
        const float scale = position / length;
        axis.z = axis.z * scale;
        axis.x = axis.x * scale;
        axis.y = axis.y * scale;
    }
    const CVector3& start = StartMatrix(this)->m_pos;
    PlaceNode(Node(this), start.x + axis.x, start.y + axis.y, start.z + axis.z);
}

// 0x0042de58 CKHkPushKillObject_UpdateVolumesAndFx_maybe
void CKHkPushKillObject::UpdateVolumesAndFx(uint8_t active) {
    CMatrix34 inverse;
    Mat4_Invert(&inverse, reinterpret_cast<const CMatrix34*>(&Node(this)->m_pRwFrame->modelling));  // 0x0023f878
    CMatrix34 spark = *StartMatrix(this);  // the 16 words (flags and pads too)
    // The particle matrix: the identity (flags 0x20003), its pads the stack's (BUG(original): never written; 0 here).
    CMatrix34 particles = {};
    particles.m_ui32Flags = 0x20003u;
    particles.m_at.z = kOne;
    particles.m_right.x = kOne;
    particles.m_up.y = kOne;
    CVector3 origin = kNullVector;
    const RwV3d& at = Node(this)->m_pRwFrame->modelling.pos;
    CVector3 position = {at.x, at.y, at.z};
    // The half size along axis +0x7c, in the start matrix's frame and in the node's (through the inverse).
    CVector3 half = {0.0f, 0.0f, 0.0f};
    const uint8_t axis = m_ui8Axis;
    if (axis == 0 || axis == 1 || axis == 2) {
        const float size = axis == 1 ? m_unk4C.y : (axis == 0 ? m_unk4C.x : m_unk4C.z);  // +0x50 / +0x4c / +0x54
        half = StartAxis(this, axis);
        const float length = std::sqrt(ppc::fmadds(half.z, half.z, ppc::fmadds(half.x, half.x, half.y * half.y)));
        if (length != 0.0f) {
            const float scale = size / length;
            half.x = half.x * scale;
            half.y = half.y * scale;
            half.z = half.z * scale;
        }
    }
    // BUG(original): another axis value transforms the stack's leftovers; the zero vector here.
    CVector3 local;
    Mat4_TransformVectors(&inverse, &local, &half, 1);  // 0x0023f7b0
    if (m_unkC4[2] - m_unkC4[1] > kZero) {  // ble (NaN: the backward end)
        // Moving forward: the leading end, the spark matrix turned round (right and up negated, flags bits 0, 1, 17 off).
        spark.m_ui32Flags &= 0xfffdfffcu;
        origin.x = origin.x + local.x;
        position.x = position.x + half.x;
        position.y = position.y + half.y;
        position.z = position.z + half.z;
        origin.y = origin.y + local.y;
        origin.z = origin.z + local.z;
        spark.m_up.z = -StartMatrix(this)->m_up.z;
        spark.m_up.x = -StartMatrix(this)->m_up.x;
        spark.m_up.y = -StartMatrix(this)->m_up.y;
        spark.m_right.z = -StartMatrix(this)->m_right.z;
        spark.m_right.x = -StartMatrix(this)->m_right.x;
        spark.m_right.y = -StartMatrix(this)->m_right.y;
    } else {
        position.x = position.x - half.x;
        position.y = position.y - half.y;
        position.z = position.z - half.z;
        origin.x = origin.x - local.x;
        origin.y = origin.y - local.y;
        origin.z = origin.z - local.z;
    }
    spark.m_pos = position;
    spark.m_ui32Flags &= 0xfffdffffu;
    particles.m_pos = origin;
    particles.m_ui32Flags &= 0xfffdffffu;
    CKSparkFxData* sparkData = static_cast<CKSparkFxData*>(m_pFxData2C);
    *static_cast<CMatrix34*>(sparkData->m_unk14) = spark;
    CKParticlesEffectFxData* particleData = static_cast<CKParticlesEffectFxData*>(m_pFxData30);
    *reinterpret_cast<CMatrix34*>(particleData->m_unk24) = particles;

    if (active == 0) {
        if (m_pFxB8 != nullptr) {
            static_cast<IKFx*>(m_pFxB8)->StopAndRelease(this);  // vt+0x58
            m_pFxB8 = nullptr;
            Sound_Stop(Sound(this, 1), 0);  // 0x001111b0
        }
        if (m_pFxBC == nullptr) return;
        static_cast<IKFx*>(m_pFxBC)->StopAndRelease(this);
        m_pFxBC = nullptr;
        return;
    }
    if (m_pFxB8 == nullptr) {
        IKFx* fx = FxService()->AcquireFx(sparkData, this);  // the inlined lookup
        m_pFxB8 = fx;
        // (fx != nullptr: 0x001d3f80 KStub_Nop_1d3f80(fx, 1, this), empty.)
        Sound(this, 1)->SetLoop(1);  // 0x00110fd0
        if (Sound(this, 1)->CountInstances() == 0) CKSound_Play(kZero, Sound(this, 1));
    }
    if (m_pFxBC != nullptr) return;
    particleData->m_unk08 = static_cast<uint8_t>(particleData->m_unk08 | 0x10u);
    particleData->m_pAttachHotSpot = nullptr;  // +0x14 (the null +0xbc)
    particleData->m_pAttachOwner = static_cast<CSGLeaf*>(m_pKGLObject);
    IKFx* fx = FxService()->AcquireFx(particleData, this);
    m_pFxBC = fx;
    if (fx == nullptr) return;
    if ((fx->m_baFxData & 2u) == 0) return;
    if (fx->m_pOwner != this) return;
    static_cast<CKParticlesEffectNodeFx*>(fx)->m_bRefreshOrientation = 1;  // +0x2c
}

// 0x0042dbf0 CKHkPushKillObject_OnActivate
void CKHkPushKillObject::VfA0() {
    CKHkActorBase::VfA0();  // 0x003f7338
    m_unkC4[3] = kOne;
    m_pFxBC = nullptr;
    m_pFxB8 = nullptr;
    m_unkC4[6] = m_unkA0[0];
    m_unkC4[0] = kZero;
    m_unkC4[5] = kZero;
    m_unkC4[4] = kZero;
    m_unkC4[7] = kZero;
    m_unkC4[1] = kZero;
    m_unkC4[2] = kZero;
    const float base = m_unk88[4] + Sound(this, 1)->m_fRandomPitch;  // fadds
    const uint32_t draw = static_cast<uint32_t>(Rand_Int()) & 0xffffu;  // 0x00011500
    const float random = static_cast<float>(draw) / kRandMax * kRandScale;  // fcfid, frsp, fdivs, fmuls
    m_unkC4[3] = ppc::fmadds(random, Sound(this, 1)->m_fRandomPitch, base);
    CMatrix34* matrix = RwMatrixCreate_Thunk();  // 0x0023fa68
    m_pStartMatrix = reinterpret_cast<RwMatrix*>(matrix);
    std::memcpy(matrix, &Node(this)->m_pRwFrame->modelling, sizeof(CMatrix34));
    VolumeUnderNode(this);
    Collision()->AddVolume(Volume(this));  // 0x00192b80
    UpdateAxisPosition(kZero);
}

// 0x0042e9b0 CKHkPushKillObject_OnDeactivate
void CKHkPushKillObject::VfA4() {
    CKHkActorBase::VfA4();  // 0x003f7370
    UpdateVolumesAndFx(0);
    Node(this)->SetLocalMatrix(m_pStartMatrix);       // 0x000d0be8
    RwMatrixDestroy_Thunk(StartMatrix(this));         // 0x0023f968
    m_pStartMatrix = nullptr;
    Collision()->RemoveVolume(Volume(this));          // 0x00192bc0
    IKBoundingVolume* volume = Volume(this);
    if (volume->m_pParent != nullptr) volume->m_pParent->RemoveChild(volume);  // vt+0x78
}

// 0x0042ebf8 CKHkPushKillObject_Restart
void CKHkPushKillObject::Restart() {
    if ((m_bitArray & 4u) == 0) {
        UpdateVolumesAndFx(0);
        Node(this)->SetLocalMatrix(m_pStartMatrix);
        VolumeUnderNode(this);
    }
    m_unkC4[6] = m_unkA0[0];
    m_pFxBC = nullptr;
    m_unkC4[2] = 0.0f;  // stw 0
    m_unkC4[3] = kOne;
    m_unkC4[0] = 0.0f;
    m_unkC4[5] = 0.0f;
    m_unkC4[4] = 0.0f;
    m_unkC4[7] = 0.0f;
    m_unkC4[1] = 0.0f;
    m_pFxB8 = nullptr;
}

// 0x0042ea68 CKHkPushKillObject_Update
void CKHkPushKillObject::Update(IKTime* clock) {
    CKHkActorBase::Update(clock);  // 0x003f6e68
    const float dt = clock->m_afDeltaTime[0];
    if (m_ui8Pushed == 0) {
        if (m_unkC4[0] == 0.0f) {  // the stored zero word: fcmpu / beq
            if (UpdateSpin(dt) == 0) return;
            UpdateAxisPosition(dt);
            Collision()->RemoveVolume(Volume(this));
            UpdateVolumesAndFx(0);
            return;
        }
        UpdateSpin(dt);
        UpdateCurveMotion(dt);
        UpdateVolumesAndFx(1);
        return;
    }
    Collision()->AddVolume(Volume(this));
    if (m_unkC4[6] != kZero) {  // bne (NaN: sliding)
        UpdateAxisPosition(dt);
        UpdateVolumesAndFx(0);
        return;
    }
    if (UpdateSpin(dt) == 0) return;
    UpdateCurveMotion(dt);
    UpdateVolumesAndFx(1);
}

// 0x0042f6b0 CKHkPushKillObject_MessageProc
int32_t CKHkPushKillObject::MessageProc(uint16_t message, void* data) {
    const int32_t base = CKHkActorBase::MessageProc(message, data);  // 0x003f7148
    int32_t own = 1;
    if (message == 0x997) {
        own = 0;
        m_ui8Pushed = 0;
    } else if (message == 0x996) {
        own = 0;
        m_ui8Pushed = 1;
    } else if (message == 0xc32) {
        PushKillHazardQuery* query = static_cast<PushKillHazardQuery*>(data);
        query->m_damage = m_ui8Damage;
        query->m_unk25 = 0;
        query->m_knock10 = m_afKnock[0];
        query->m_knock0C = m_afKnock[1];
        query->m_knock08 = m_afKnock[2];
        query->m_kind = 0;
        CKSound_Play(kZero, Sound(this, 2));
        FxService()->StartEffect(static_cast<IKFxData*>(m_pFxData38), this);  // the inlined start (vt+0x50 tested)
        // The hero's hot spot (vt+0x16c of the hero group: the hero's index, part 0).
        CKHkS08Hero* hero = query->m_hero;
        CKGrpS08Hero* group = static_cast<CKGrpS08Hero*>(g_pEngine->m_gameManager->m_unk04[1]);  // engine +0x8c -> +0x08
        const uint8_t index = hero->GetDragonIndex();  // 0x00361960
        const uint8_t spot = static_cast<uint8_t>(group->GetHotSpotIndexSigned(index, 0));  // 0x002ca298
        CVector3 at;
        static_cast<CSGHotSpot*>(hero->GetHotSpot(spot))->GetWorldPosition(&at);  // 0x00361b70, 0x000ce790
        if (m_pKillCamera != nullptr) {
            CKSrvCamera* cameras = static_cast<CKSrvCamera*>(g_pEngine->m_srvCamera);  // engine +0x70
            bool owned = false;
            for (uint32_t i = 0; i < cameras->m_unke24; ++i) {
                if (cameras->m_apCinematicOwner[i] == this) {
                    owned = true;
                    break;
                }
            }
            if (!owned) {
                cameras->m_apCinematicOwner[cameras->m_unke24] = this;
                cameras->m_unke24 = cameras->m_unke24 + 1;
            }
            cameras->m_ui8TransitionMode = 0;
            cameras->m_pNextCamera = static_cast<IKCamera*>(m_pKillCamera);
            cameras->m_fSwitchTimer = m_fKillCameraTime;
            cameras->m_baTemporaryFlags = (cameras->m_baTemporaryFlags | 0x400000u) & ~0x30u;
        }
        CKParticlesEffectFxData* hitData = static_cast<CKParticlesEffectFxData*>(m_pFxData34);
        RwMatrix* matrix = hitData->m_unk24;
        matrix->pos.z = at.z;
        matrix->pos.x = at.x;
        matrix->pos.y = at.y;
        matrix->flags &= 0xfffdffffu;
        FxService()->StartEffect(hitData, this);
        QueueTriggerSignals(&m_tsHit);  // 0x00236338
        own = 0;
    }
    if (base == 3 || own == 3) return 3;
    if (base == 2 || own == 2) return 2;
    if (base == 0) return 0;
    return own;
}
