// CKHkPlatform.cpp - reconstructed original translation unit 0x41e248-0x425b98 (GAME_TOC1, main_toc1), 51 functions, 41 live.
// Primary class: CKHkPlatform  key 0x3a42  category Hook  size 0x1f4  vtable 0xb26000
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x41e248  CKHkPlatform_Delete
//   [ ] 0x41e298  CKHkPlatform_SetFlagBit4_maybe  [dead]
//   [ ] 0x41e2b8  CKHkPlatform_ResetMotionState_maybe  [dead]
//   [ ] 0x41e430  FUN_0041e430  [dead]
//   [ ] 0x41e478  CKHkPlatform_GetFloat34_maybe  [dead]
//   [ ] 0x41e480  CKHkPlatform_SetFloat34_maybe  [dead]
//   [ ] 0x41e488  CKHkPlatform_GetFloat7C_maybe  [dead]
//   [ ] 0x41e490  CKHkPlatform_SetFloat7C_maybe  [dead]
//   [x] 0x41e498  CKHkPlatform_IsAtStartProperty_maybe  (the accessor of id 0x15e in GetInfo)
//   [x] 0x41e4c0  CKHkPlatform_IsAtEndProperty_maybe  (the accessor of id 0x15f in GetInfo)
//   [x] 0x41e4e8  CKHkPlatform_vfF0  (in the header)
//   [ ] 0x41e4f0  RegisterCKHkPlatformClass
//   [ ] 0x41e568  _GLOBAL__I_41e568
//   [x] 0x41e578  CKHkPlatform_SetNavBlocking_maybe
//   [ ] 0x41ea08  CKHkPlatform_StopLoopSound_2_maybe  [dead]  (no pointer to its descriptor 0xbb7750, no call)
//   [ ] 0x41ea98  CKHkPlatform_StopLoopSound_maybe  [dead]  (no pointer to its descriptor 0xbb7758, no call)
//   [x] 0x41eb18  CKHkPlatform_StartMoveSounds_maybe
//   [x] 0x41ec28  CKHkPlatform_EnsureLoopSoundPlaying_maybe
//   [x] 0x41ecd8  CKHkPlatform_PlayWaypointFx_maybe
//   [x] 0x41ef68  CKHkPlatform_Stop  (empty / no effect: inherited, CKHkActorBase_d82_maybe_Stop 0x3f6e50)
//   [x] 0x41ef90  CKHkPlatform_Start  (= the inherited slot: CKHkActorBase_d82_maybe_ResetRuntime (empty))
//   [x] 0x41efb8  CKHkPlatform_RecursiveRegistration
//   [x] 0x41f1d8  CKHkPlatform_DeleteArray
//   [x] 0x41f278  CKHkPlatform_Create
//   [x] 0x41f310  CKHkPlatform_AttachSounds
//   [x] 0x41f3a0  CKHkPlatform_IsMovingForwardProperty_maybe  (the accessor of id 0x161 in GetInfo)
//   [x] 0x41f428  CKHkPlatform_IsMovingProperty_maybe  (the accessor of id 0x160 in GetInfo)
//   [ ] 0x41f468  CKHkPlatform_SetFloat80MaxOne_maybe  [dead]
//   [ ] 0x41f480  CKHkPlatform_SetInitialPathRatio_maybe  [dead]
//   [x] 0x41f498  CKHkPlatform_GetInfo
//   [x] 0x41f650  CKHkPlatform_Destroy
//   [x] 0x41f698  CKHkPlatform_OnActivate
//   [ ] 0x41f8b8  CKHkPlatform_SetFlagBit20_maybe  [dead]
//   [x] 0x41f8d8  CKHkPlatform_IsMovingBackwardProperty_maybe  (the accessor of id 0x162 in GetInfo)
//   [x] 0x41f958  CKHkPlatform_vfD0
//   [x] 0x41fab0  CKHkPlatform_CreateArray
//   [x] 0x41fbd0  CKHkPlatform_PostLoad
//   [x] 0x41fc78  CKHkPlatform_OnDeactivate
//   [x] 0x41fde0  CKHkPlatform_Restart
//   [x] 0x41ffe8  CKHkPlatform_EvaluatePathPosition_maybe
//   [x] 0x420270  CKHkPlatform_OrientAlongDirection_maybe
//   [x] 0x4204a8  CKHkPlatform_SetPathDistance_maybe
//   [x] 0x420630  CKHkPlatform_vfC8
//   [x] 0x4207c0  CKHkPlatform_SimulateSwaySpring_maybe
//   [x] 0x421020  CKHkPlatform_SetDefaultState
//   [x] 0x4212a0  CKHkPlatform_Load
//   [ ] 0x422518  CKHkPlatform_Save
//   [x] 0x423620  CKHkPlatform_UpdateMotion_maybe
//   [x] 0x423f70  CKHkPlatform_AdvanceAlongPath_maybe
//   [x] 0x424690  CKHkPlatform_Update
//   [x] 0x425378  CKHkPlatform_MessageProc
//
//   [ ] 0x9c2ff8  CKHkPlatform_IsKindOfClass  [inline]
//   [ ] 0x9c3050  CKHkPlatform_GetClassType  [inline]
//   [ ] 0x9c3058  CKHkPlatform_GetClassID  [inline]
//   [ ] 0x9c3060  CKHkPlatform_Destructor  [inline]
//   [ ] 0x9c3090  CKHkPlatform_DeletingDestructor  [inline]
#include "k2000/hooks/CKHkPlatform.h"

#include <cmath>
#include <cstring>

#include "Renderware/rwcore/RwCamera.h"
#include "k2000/ai/CKSrvPathFinding.h"
#include "k2000/core/IKInfo.h"
#include "k2000/dictionaries/CKSoundDictionaryID.h"
#include "k2000/io/IKFile.h"
#include "k2000/logic/CKPFGraphNode.h"
#include "k2000/logic/fx/CKExplosionNodeFx.h"
#include "k2000/logic/math/IKPath.h"
#include "k2000/services/CKSrvFx.h"
#include "crt/ppc_ops.h"
#include "crt/xatan.h"
#include "k2000/logic/ai/CKFlaggedPath.h"
#include "k2000/logic/sound/CKSound.h"
#include "k2000/math/Quat.h"
#include "k2000/memory/Mem.h"
#include "k2000/misc/Engine.h"
#include "k2000/scenegraph/CParticlesNodeFx.h"
#include "k2000/scenegraph/CSGLeaf.h"
#include "k2000/scenegraph/CSGMovable.h"
#include "k2000/services/ICollisionMesh.h"
#include "Renderware/rpprtstd/RpPrtStd.h"
#include "Spyro2008/groups/CKGrpS08Hero.h"
#include "Spyro2008/hooks/CKHkS08Hero.h"
#include "k2000/components/CKQuakeCpntUpdater.h"
#include "k2000/logic/CDefaultGameManager.h"
#include "k2000/logic/ai/CKMarkerBeacon.h"
#include "k2000/logic/physics/CDynamicGround.h"
#include "k2000/logic/physics/CGround.h"
#include "k2000/math/CBBox.h"
#include "k2000/misc/ClassRegistry.h"
#include "k2000/misc/Mat4.h"
#include "k2000/services/CKSrvCollision.h"
#include "k2000/system/IKTime.h"

namespace {
// 0x00c50d64 (TOC1 +0x4d18 points at it): the null vector (statically and live (0, 0, 0)).
const CVector3 kVectorZero = {0.0f, 0.0f, 0.0f};

// One read of count words, then each word byte-swapped (the PS3's Read(count * 4) + lwbrx per word).
void ReadFloatWords(IKFile* file, float* dst, uint32_t count) {
    uint32_t w[4];
    ReadU32LEWords(file, w, count);
    std::memcpy(dst, w, count * sizeof(uint32_t));
}

// Mem_AllocAligned16(count * 4) then one contiguous reference read (vt+0x28) of count references.
IKSerializable** AllocAndReadRefs(IKFile* file, uint8_t count) {
    IKSerializable** refs =
        static_cast<IKSerializable**>(Mem_AllocAligned16(static_cast<uint32_t>(count * sizeof(IKSerializable*))));
    IKFile_ReadObjectRefArray(file, refs, count);
    return refs;
}
}  // namespace

// 0x004212a0 CKHkPlatform_Load
int32_t CKHkPlatform::Load(IKFile* file, int32_t type) {
    CKHkActorBase::Load(file, type);
    if (type == K_LEVEL_PLATEFORMS) {
        ReadU8(file, &m_unk20);
        m_apUnk24 = AllocAndReadRefs(file, m_unk20);
        IKFile_ReadRef(file, &m_unk28);
        IKFile_ReadRef(file, &m_unk2C);
        for (float& value : m_unk30) ReadF32LE(file, &value);
        for (float& value : m_unk5C) ReadF32LE(file, &value);
        ReadFloatWords(file, &m_vPositionOffset.x, 3);
        ReadFloatWords(file, &m_vStartPath.x, 3);
        ReadFloatWords(file, &m_vDirPath.x, 3);
        ReadFloatWords(file, m_qBaseOrientation, 4);
        for (float& value : m_unk50) ReadF32LE(file, &value);
        ReadU8(file, &m_unk10D);  // read into a stack byte, then stored
        for (float& value : m_unk110) ReadF32LE(file, &value);
        ReadU8(file, &m_unk134);
        if (m_unk134 == 0) {
            m_apUnk138 = nullptr;
        } else {
            m_apUnk138 = AllocAndReadRefs(file, m_unk134);
        }
        ReadF32LE(file, &m_unk13C);
        ReadF32LE(file, &m_unk140);
        IKFile_ReadRef(file, &m_unkBC);
        m_unkFC.Load(file, K_LEVEL_PLATEFORMS);
        m_unk104.Load(file, K_LEVEL_PLATEFORMS);
        for (IKSerializable*& ref : m_unk144) IKFile_ReadRef(file, &ref);
        for (uint8_t& value : m_unk154) ReadU8(file, &value);
    }

    // Inlined InitVariables (XXL2 CKHkPlatform::InitVariables), for every serialization type.
    m_fTimer = 0.0f;
    m_fPositionOnPath = m_unk30[4] * m_unk5C[4];  // fmuls +0x40 * +0x6c
    m_pfPoint = kVectorZero;
    m_pfPointIndex = 0xffff;
    // m_bitArray: bit 27 cleared, bits 24..26 = bits 10..12, bit 9 = bit 13, bit 28 cleared, then bits 29..30
    // cleared (rlwinm sequence at 0x42136c..0x421490).
    uint32_t bits = m_bitArray & 0xf7ffffffu;
    bits = (bits & 0xf0ffffffu) | ((bits & 0x1c00u) << 14);
    bits = (bits & ~0x200u) | (((bits >> 13) & 1u) << 9);
    bits &= ~0x10000000u;
    m_qLastSlopeRotation[0] = 0.0f;
    m_qLastSlopeRotation[3] = 1.0f;
    m_qLastSlopeRotation[1] = 0.0f;
    m_qLastSlopeRotation[2] = 0.0f;
    m_qLastPathRotation[2] = m_qBaseOrientation[2];
    m_qLastPathRotation[0] = m_qBaseOrientation[0];
    m_qLastPathRotation[1] = m_qBaseOrientation[1];
    m_qLastPathRotation[3] = m_qBaseOrientation[3];
    m_vPosition = kVectorZero;
    m_unk1A8 = 0.0f;
    m_unk1AC = kVectorZero;
    m_unk1B8 = kVectorZero;
    m_unk1C4 = 0;
    m_unk1C8 = kVectorZero;
    m_unk1D4 = kVectorZero;
    m_bitArray = bits & 0x9fffffffu;
    return 1;
}

namespace {
// 0x00019c98 KObject_LevelResetIfNotNull_maybe: the object's RecursiveRegistration when there is one.
void RegisterIfNotNull(IKSerializable* object, int32_t type) {
    if (object != nullptr) object->RecursiveRegistration(type);
}

CKSoundDictionaryID* SoundsOf(IKSerializable* dictionary) { return static_cast<CKSoundDictionaryID*>(dictionary); }

// The particles (+0x150, a CParticlesNodeFx) on: scene bit 10 set, bit 19 cleared, no emission speed adjustment, the
// emitter's flags 0xa.
void ParticlesOn(IKSerializable* object) {
    CParticlesNodeFx* node = static_cast<CParticlesNodeFx*>(object);
    node->m_sgProperties = (node->m_sgProperties | 0x400u) & 0xfff7ffffu;
    node->m_fEmissionSpeedAdjustment = 0.0f;
    node->m_pRpPrtStdEmitter->flag |= 0xau;
}
}  // namespace

// 0x0041fbd0 CKHkPlatform_PostLoad
int32_t CKHkPlatform::PostLoad(int32_t type) {
    CKHkActorBase::PostLoad(type);  // 0x003f6e70
    if (static_cast<uint32_t>(type - 4) > 3u && type == K_LEVEL_PLATEFORMS) {
        m_GrndDataIn.m_fDeltaMax = 1.0f;      // TOC1 +0x4d1c
        m_GrndDataIn.m_fObjectHeight = 0.5f;  // TOC1 +0x4d24
        m_GrndDataIn.m_MasksOfGrdForTest[0] = 1;
        m_GrndDataIn.m_MasksOfGrdForTest[1] = 8;
        m_GrndDataInOut.m_pGround = nullptr;
        m_GrndDataInOut.m_ui8SectorNumber = 0;
        m_GrndDataInOut.m_i32FaceIndex = -1;
        m_GrndDataInOut.m_eContactStatus = 3;
    }
    return 1;
}

// 0x0041f650 CKHkPlatform_Destroy
void CKHkPlatform::Destroy() {
    CKHkActorBase::Destroy();      // 0x003f6e08
    Mem_FreeAligned16(m_apUnk24);  // 0x00052fb8
    Mem_FreeAligned16(m_apUnk138);
}

// 0x0041efb8 CKHkPlatform_RecursiveRegistration (returns 1): the actor base's (IKHook's); outside the memory-card types
// 4..7 the sound dictionary (+0xbc), the grounds (+0x24, from the last; null entries skipped), the +0x138 references,
// the paths (+0x28, +0x2c), the four references +0x144..+0x150, then the trigger starters (nothing).
void CKHkPlatform::RecursiveRegistration(int32_t type) {
    CKHkActorBase::RecursiveRegistration(type);  // 0x003f6ee8
    if (static_cast<uint32_t>(type - 4) < 4u) return;
    RegisterIfNotNull(m_unkBC, type);
    for (uint32_t i = m_unk20; i != 0; --i) RegisterIfNotNull(m_apUnk24[i - 1], type);
    for (uint32_t i = m_unk134; i != 0; --i) RegisterIfNotNull(m_apUnk138[i - 1], type);
    if (m_unk28 != nullptr) RegisterIfNotNull(m_unk28, type);
    if (m_unk2C != nullptr) RegisterIfNotNull(m_unk2C, type);
    for (IKSerializable* object : m_unk144) RegisterIfNotNull(object, type);
}

// 0x0041f498 CKHkPlatform_GetInfo, with its accessors (the path distance +0x15c against 0 and the length +0x6c; the
// motion flags: bit 23 the swing speed +0x1f0 against +-0.1, else bits 24-26 the movement and bit 27 its direction).
int32_t CKHkPlatform::GetInfo(IKInfo* info, int32_t request) {
    const int32_t base = CKHkActorBase::GetInfo(info, request);  // KStub_Return1 0x3f7140
    int32_t own = 1;
    if (request == kGetInfoValueAccessor && info->m_ui32Id - 0x15eu <= 4u) {
        switch (info->m_ui32Id) {
        case 0x15e:  // 0x0041e498 CKHkPlatform_IsAtStartProperty_maybe (fcmpu / cror: not greater than 0)
            own = AnswerInfo(info, [](IKSerializable* o, uint32_t) {
                return static_cast<CKHkPlatform*>(o)->m_fPositionOnPath <= 0.0f ? 1u : 0u;
            }, 0);
            break;
        case 0x15f:  // 0x0041e4c0 CKHkPlatform_IsAtEndProperty_maybe
            own = AnswerInfo(info, [](IKSerializable* o, uint32_t) {
                const CKHkPlatform* p = static_cast<CKHkPlatform*>(o);
                return p->m_fPositionOnPath >= p->m_unk5C[4] ? 1u : 0u;
            }, 0);
            break;
        case 0x160:  // 0x0041f428 CKHkPlatform_IsMovingProperty_maybe
            own = AnswerInfo(info, [](IKSerializable* o, uint32_t) {
                const CKHkPlatform* p = static_cast<CKHkPlatform*>(o);
                if (!(p->m_unk5C[4] > p->m_fPositionOnPath) || !(p->m_fPositionOnPath > 0.0f)) return 0u;
                return ((p->m_bitArray >> 24) & 7u) != 0 ? 1u : 0u;  // the byte +0xc
            }, 0);
            break;
        case 0x161:  // 0x0041f3a0 CKHkPlatform_IsMovingForwardProperty_maybe
            own = AnswerInfo(info, [](IKSerializable* o, uint32_t) {
                const CKHkPlatform* p = static_cast<CKHkPlatform*>(o);
                const uint32_t bits = p->m_bitArray;
                if ((bits & 0x800000u) != 0) return p->m_fUnk1F0 > 0.1f ? 1u : 0u;  // TOC1 +0x4d58
                if (!(p->m_unk5C[4] > p->m_fPositionOnPath) || !(p->m_fPositionOnPath > 0.0f)) return 0u;
                if (((bits >> 24) & 7u) == 0) return 0u;
                return ((bits >> 27) & 1u) ^ 1u;
            }, 0);
            break;
        default:  // 0x162: 0x0041f8d8 CKHkPlatform_IsMovingBackwardProperty_maybe
            own = AnswerInfo(info, [](IKSerializable* o, uint32_t) {
                const CKHkPlatform* p = static_cast<CKHkPlatform*>(o);
                const uint32_t bits = p->m_bitArray;
                if ((bits & 0x800000u) != 0) return p->m_fUnk1F0 < -0.1f ? 1u : 0u;  // TOC1 +0x4d78
                if (!(p->m_unk5C[4] > p->m_fPositionOnPath) || !(p->m_fPositionOnPath > 0.0f)) return 0u;
                if (((bits >> 24) & 7u) == 0) return 0u;
                return (bits >> 27) & 1u;
            }, 0);
            break;
        }
    }
    if (base == 2 || own == 2) return 2;
    return base == 0 ? 0 : own;
}

// 0x0041e578 CKHkPlatform_SetNavBlocking_maybe
void CKHkPlatform::SetNavBlocking(uint8_t blocked) {
    const uint32_t bits = m_bitArray;
    if ((bits & 0x200u) == 0) return;
    if (blocked != 0) {
        if ((bits & 0x10000000u) != 0) return;
    } else if ((bits & 0x10000000u) == 0) {
        return;
    }
    CKSrvPathFinding* pathFinding = static_cast<CKSrvPathFinding*>(g_pEngine->m_srvPathFinding);
    m_pfPoint = m_vPosition;
    // The point +0x184 with its graph node index +0x190 is a CPFPoint (the lookup reads and updates the index).
    CPFPoint point;
    point.m_position = m_pfPoint;
    point.m_unk0c = m_pfPointIndex;
    const uint32_t found = pathFinding->FindSectorForPoint(&point);  // 0x001e5ca0
    m_pfPoint = point.m_position;
    m_pfPointIndex = point.m_unk0c;
    if ((found & 0xffu) != 0) {
        const float a = m_unk5C[5];  // +0x70
        const float b = m_unk5C[6];  // +0x74
        const RwFrame* frame = static_cast<CSGMovable*>(m_pKGLObject)->m_pRwFrame;
        const RwV3d& at = frame->modelling.at;        // frame +0x30
        const RwV3d& right = frame->modelling.right;  // frame +0x10
        const float na = -a;
        const float nb = -b;
        const CVector3 atPos = {at.x * a, at.y * a, at.z * a};
        const CVector3 rightPos = {right.x * b, right.y * b, right.z * b};
        const CVector3 atNeg = {at.x * na, at.y * na, at.z * na};
        const CVector3 rightNeg = {right.x * nb, right.y * nb, right.z * nb};
        const CVector3& p = m_pfPoint;
        const CVector3 c0 = {(p.x + atPos.x) + rightPos.x, (p.y + atPos.y) + rightPos.y, (p.z + atPos.z) + rightPos.z};
        const CVector3 c1 = {(p.x + atNeg.x) + rightNeg.x, (p.y + atNeg.y) + rightNeg.y, (p.z + atNeg.z) + rightNeg.z};
        const CVector3 c2 = {(p.x + atNeg.x) + rightPos.x, (p.y + atNeg.y) + rightPos.y, (p.z + atNeg.z) + rightPos.z};
        const CVector3 c3 = {(p.x + atPos.x) + rightNeg.x, (p.y + atPos.y) + rightNeg.y, (p.z + atPos.z) + rightNeg.z};
        // The box of the four corners in x and z (strict compares: a NaN corner changes nothing), at the first corner's y.
        float minX = c0.x;
        float maxX = c0.x;
        float minZ = c0.z;
        float maxZ = c0.z;
        const CVector3* corners[3] = {&c1, &c2, &c3};
        for (const CVector3* c : corners) {
            if (minX > c->x) minX = c->x;
            if (minZ > c->z) minZ = c->z;
            if (maxX < c->x) maxX = c->x;
            if (maxZ < c->z) maxZ = c->z;
        }
        const CVector3 low = {minX, c0.y, minZ};
        const CVector3 high = {maxX, c0.y, maxZ};
        if ((m_bitArray & 0x20000u) != 0) {
            pathFinding->SetBoxBlocked(point.m_unk0c, &low, &high, blocked);  // 0x001e5f60
        } else if (point.m_unk0c < pathFinding->m_Graph.m_ui32GraphNodesSize) {
            static_cast<CKPFGraphNode*>(pathFinding->m_Graph.m_apGraphNodes[point.m_unk0c])
                ->m_Sector.SetBoxBlocked(&low, &high, blocked);  // 0x001ed3c0
        }
    }
    m_bitArray = (m_bitArray & 0xefffffffu) | (static_cast<uint32_t>(blocked) << 28);
}

// 0x0041f698 CKHkPlatform_OnActivate: the actor base's; the sway (+0x1a0, +0x1a4) cleared; the grounds on (from the
// last); the node at the path orientation (+0x174) and position (+0x194); the path-finding box blocked; the first
// ground's properties bit 1 cleared; the node's LTM at row kept (+0x1e0); with bit 8 the flagged path (+0x2c) set to the
// distance; the particles (+0x150) on; the visibility applied (vt+0xd0 with bit 31); +0x10c = 1, +0x1f0 = 0.
void CKHkPlatform::VfA0() {
    CKHkActorBase::VfA0();  // 0x003f7338
    m_unk1A0[1] = 0;
    m_unk1A0[0] = 0;
    for (uint32_t i = m_unk20; i != 0; --i) {
        static_cast<ICollisionMesh*>(m_apUnk24[(i - 1) & 0xffu])->SetActive(1);  // 0x001a6b70
    }
    CMatrix34 m;
    Quat_ToMatrixNormalizing(m_qLastPathRotation, &m);  // 0x00241d78
    m.m_pos = m_vPosition;
    m.m_ui32Flags &= 0xfffdffffu;
    static_cast<CSGMovable*>(m_pKGLObject)->SetLocalMatrix(reinterpret_cast<const RwMatrix*>(&m));  // 0x000d0be8
    SetNavBlocking(1);  // 0x0041e578
    ICollisionMesh* ground = static_cast<ICollisionMesh*>(m_apUnk24[0]);
    ground->m_ui16PropertiesFlags = static_cast<uint16_t>(ground->m_ui16PropertiesFlags & 0xfffdu);
    const RwV3d& at = static_cast<CSGMovable*>(m_pKGLObject)->m_pRwFrame->ltm.at;  // frame +0x70
    m_unk1E0 = {at.x, at.y, at.z};
    if ((m_bitArray & 0x100u) != 0 && m_unk2C != nullptr) {
        CVector3 point;
        static_cast<CKFlaggedPath*>(m_unk2C)->SetDistanceAndGetPositionUp(m_fPositionOnPath, &point, nullptr, nullptr);  // 0x000c4d88
    }
    if (m_unk144[3] != nullptr) ParticlesOn(m_unk144[3]);  // +0x150
    SetVisible(static_cast<int32_t>(m_bitArray >> 31));  // vt+0xd0
    m_unk10C = 1;
    m_fUnk1F0 = 0.0f;
}

// 0x0041fde0 CKHkPlatform_Restart
void CKHkPlatform::Restart() {
    if ((m_bitArray & 4u) != 0) return;
    CMatrix34 m;
    Quat_ToMatrixNormalizing(m_qLastPathRotation, &m);  // 0x00241d78
    m.m_pos = m_vPosition;
    m.m_ui32Flags &= 0xfffdffffu;
    static_cast<CSGMovable*>(m_pKGLObject)->SetLocalMatrix(reinterpret_cast<const RwMatrix*>(&m));  // 0x000d0be8
    SetNavBlocking(1);  // 0x0041e578
    ICollisionMesh* ground = static_cast<ICollisionMesh*>(m_apUnk24[0]);
    ground->m_ui16PropertiesFlags = static_cast<uint16_t>(ground->m_ui16PropertiesFlags & 0xfffdu);
    if (SoundsOf(m_unkBC)->GetSound2(3) != nullptr) SoundsOf(m_unkBC)->GetSound2(3)->Stop(0);  // 0x00112bd8, 0x001111b0
    CKSound* loop = SoundsOf(m_unkBC)->GetSound2(1);
    if (loop != nullptr && loop->IsPlaying() != 0) loop->Stop(0);  // 0x00111568
    const RwV3d& at = static_cast<CSGMovable*>(m_pKGLObject)->m_pRwFrame->ltm.at;  // frame +0x70
    m_unk1E0 = {at.x, at.y, at.z};
    SetVisible(static_cast<int32_t>(m_bitArray >> 31));  // vt+0xd0
    m_unk10C = 1;
}

// 0x0041fc78 CKHkPlatform_OnDeactivate
void CKHkPlatform::VfA4() {
    CKHkActorBase::VfA4();  // 0x003f7370
    for (uint32_t i = m_unk20; i != 0; --i) {
        static_cast<ICollisionMesh*>(m_apUnk24[(i - 1) & 0xffu])->SetActive(0);  // 0x001a6b70
    }
    if (SoundsOf(m_unkBC)->GetSound2(3) != nullptr) SoundsOf(m_unkBC)->GetSound2(3)->Stop(0);  // 0x00112bd8, 0x001111b0
    CKSound* loop = SoundsOf(m_unkBC)->GetSound2(1);
    if (loop != nullptr && loop->IsPlaying() != 0) loop->Stop(0);  // 0x00111568
    SetNavBlocking(0);  // 0x0041e578
    if (m_unk144[3] != nullptr) {
        CParticlesNodeFx* node = static_cast<CParticlesNodeFx*>(m_unk144[3]);
        node->m_sgProperties &= 0xfff7fbffu;
        node->m_pRpPrtStdEmitter->flag &= 0xfffffff7u;
    }
}

// 0x0041f310 CKHkPlatform_AttachSounds
void CKHkPlatform::KGLObjectAttached(IKSerializable* leaf) {
    for (uint32_t i = 0; i < 10; ++i) {
        if (SoundsOf(m_unkBC)->GetSound2(i) != nullptr) SoundsOf(m_unkBC)->GetSound2(i)->SetAttachObject(leaf);  // 0x00112bd8, 0x00111350
    }
}

// 0x0041f958 CKHkPlatform_vfD0
void CKHkPlatform::SetVisible(int32_t visible) {
    const uint32_t v = static_cast<uint32_t>(visible) & 0xffu;
    m_bitArray = (m_bitArray & 0x7fffffffu) | (v << 31);
    if (m_pKGLObject != nullptr) {
        CSGLeaf* leaf = static_cast<CSGLeaf*>(m_pKGLObject);
        leaf->m_sgProperties = (leaf->m_sgProperties & 0xfffffffbu) | (((v ^ 1u) << 2) & 0x3fcu);
    }
    if (m_unk144[3] != nullptr) {
        CParticlesNodeFx* node = static_cast<CParticlesNodeFx*>(m_unk144[3]);
        node->m_sgProperties = (node->m_sgProperties & 0xfff7fbffu) | (v << 10);
        if (v == 0) {
            node->m_pRpPrtStdEmitter->flag &= 0xfffffff7u;
        } else {
            node->m_fEmissionSpeedAdjustment = 0.0f;
            node->m_pRpPrtStdEmitter->flag |= 0xau;
        }
    }
    for (uint32_t i = m_unk20; i != 0; --i) {
        IKSerializable* ground = m_apUnk24[i - 1];
        if (ground != nullptr) static_cast<ICollisionMesh*>(ground)->SetActive(static_cast<uint16_t>(v));  // 0x001a6b70
    }
}

// ---- C2.8 port-rest R04: the preset, the path distance and the orientation ----

namespace {
// 0x00c50d40 (TOC1 +0x4d88): the shared Y axis (zero in the EBOOT's BSS; a static initialiser fills it).
const CVector3 kAxisY = {0.0f, 1.0f, 0.0f};
// 0x00010690 Math_Sqrtf: the double square root rounded to float.
float MathSqrtf(float x) { return static_cast<float>(std::sqrt(static_cast<double>(x))); }
// The clamp to [-1, 1] before the arc functions (cror lt|eq / gt|eq: NaN passes through).
float ClampUnit(float x) {
    if (x <= -1.0f) return -1.0f;  // TOC1 +0x4d84
    if (x >= 1.0f) return 1.0f;    // TOC1 +0x4d1c
    return x;
}
}  // namespace

// 0x0041ecd8 CKHkPlatform_PlayWaypointFx_maybe
void CKHkPlatform::PlayWaypointFx() {
    IKFx* fx = static_cast<CKSrvFx*>(g_pEngine->m_srvFx)->AcquireFx(static_cast<IKFxData*>(m_unk144[2]), this);  // inlined
    if (fx == nullptr) return;
    static_cast<CKExplosionNodeFx*>(fx)->Trigger(this, &static_cast<CSGMovable*>(m_pKGLObject)->m_pRwFrame->ltm);  // 0x001b82a8
    fx->ReleaseReservation(this);  // vt+0x54
}

// 0x0041ffe8 CKHkPlatform_EvaluatePathPosition_maybe. The line: 0.0 (TOC1 +0x4d20) against the length +0x6c (ble: NaN
// takes the start), t = distance / length (fdivs), start + t * dir (fmadds); the direction normalised with 1.0 / length
// unless 0. The waypoints: index 1 .. count - 2 of the flagged path's beacons; one between the old cursor and the new
// distance (old < w <= new or old > w >= new) plays the effect, each time read again.
void CKHkPlatform::EvaluatePathPosition(float distance, CVector3* position, CVector3* direction) {
    if ((m_bitArray & 0x100u) != 0) {
        if (m_unk28 != nullptr) {
            *position = static_cast<IKPath*>(m_unk28)->GetPointAt(distance, direction);  // vt+0x50
            return;
        }
        if (m_unk2C != nullptr) {
            CKFlaggedPath* path = static_cast<CKFlaggedPath*>(m_unk2C);
            const float old = path->m_fCursorPos;  // +0x0c before the move
            path->SetDistanceAndGetPosition(distance, position, direction, nullptr);  // 0x000c4eb8
            if (m_unk144[2] == nullptr) return;
            path = static_cast<CKFlaggedPath*>(m_unk2C);
            if (path->m_ui32NbOfBeacon <= 2) return;
            if (path->m_ui32NbOfBeacon - 1u <= 1u) return;
            for (uint32_t i = 1; ; ) {
                const float w = path->m_aBeaconList[i];
                ++i;
                bool play = false;
                if (old < w) {
                    play = distance >= w;  // cror gt|eq
                } else if (old > w) {  // ble: equal or NaN skips
                    play = distance <= w;  // cror lt|eq
                }
                if (play) PlayWaypointFx();  // 0x0041ecd8
                path = static_cast<CKFlaggedPath*>(m_unk2C);
                if (path->m_ui32NbOfBeacon - 1u <= i) return;
            }
        }
    }
    const float length = m_unk5C[4];  // +0x6c
    if (!(length > 0.0f)) {
        *position = m_vStartPath;  // +0x94
    } else {
        const float t = distance / length;
        position->z = ppc::fmadds(t, m_vDirPath.z, m_vStartPath.z);
        position->x = ppc::fmadds(t, m_vDirPath.x, m_vStartPath.x);
        position->y = ppc::fmadds(t, m_vDirPath.y, m_vStartPath.y);
    }
    const float y = m_vDirPath.y;
    const float x = m_vDirPath.x;
    direction->x = x;
    const float z = m_vDirPath.z;
    direction->y = y;
    direction->z = z;
    const float len = MathSqrtf(ppc::fmadds(z, z, ppc::fmadds(x, x, y * y)));
    if (len == 0.0f) return;
    const float inv = 1.0f / len;
    direction->z = inv * direction->z;
    direction->x = inv * direction->x;
    direction->y = inv * direction->y;
}

// 0x00420270 CKHkPlatform_OrientAlongDirection_maybe. The angles in degrees (57.29578 TOC1 +0x4d8c, fmuls); acos /
// asin of the clamped components (crt::Acosf / Asinf, the TocBridge targets); the yaw negated for a negative x.
void CKHkPlatform::OrientAlongDirection(const CVector3* direction, float* q) {
    if ((m_bitArray & 0x100000u) == 0) {
        const float x = direction->x;
        float yaw = crt::Acosf(ClampUnit(direction->z));  // 0x0098e1a0
        if (x < 0.0f) yaw = -yaw;
        q[3] = 1.0f;
        q[2] = 0.0f;
        q[0] = 0.0f;
        q[1] = 0.0f;
        Quat_Rotate(q, reinterpret_cast<const RwV3d*>(&kAxisY), yaw * 57.29578f);  // 0x00242130
        return;
    }
    q[0] = 0.0f;
    q[3] = 1.0f;
    q[1] = 0.0f;
    q[2] = 0.0f;
    float x = direction->x;
    float z = direction->z;
    const float len = MathSqrtf(ppc::fmadds(z, z, ppc::fmadds(x, x, 0.0f)));
    if (len != 0.0f) {
        const float inv = 1.0f / len;
        z = z * inv;
        x = x * inv;
    }
    const float pitchSine = -direction->y;
    const CVector3 side = {z, -0.0f, -x};  // TOC1 +0x4d90 -0.0
    Quat_Rotate(q, reinterpret_cast<const RwV3d*>(&side), crt::Asinf(ClampUnit(pitchSine)) * 57.29578f);  // 0x0098f1d0
    float yaw = crt::Acosf(ClampUnit(z));
    if (x < 0.0f) yaw = -yaw;
    Quat_Rotate(q, reinterpret_cast<const RwV3d*>(&kAxisY), yaw * 57.29578f);
}

// 0x004204a8 CKHkPlatform_SetPathDistance_maybe. The flat direction: y 0, length sqrtf(z * z + (x * x + 0.0)) (fmadds), 1.0
// (TOC1 +0x4d1c) / length unless 0.
void CKHkPlatform::SetPathDistance(float distance, int32_t block) {
    if (block != 0) SetNavBlocking(0);  // 0x0041e578
    m_fPositionOnPath = distance;
    CVector3 direction;
    EvaluatePathPosition(distance, &m_vPosition, &direction);  // 0x0041ffe8
    m_vPosition.x = m_vPosition.x + m_vPositionOffset.x;
    m_vPosition.z = m_vPosition.z + m_vPositionOffset.z;
    m_vPosition.y = m_vPosition.y + m_vPositionOffset.y;
    const uint32_t bits = m_bitArray;
    if ((bits & 0x10u) != 0) {
        if ((bits & 0x100000u) == 0) {
            direction.y = 0.0f;  // stw 0
            const float len = MathSqrtf(ppc::fmadds(direction.z, direction.z, ppc::fmadds(direction.x, direction.x, 0.0f)));
            if (len != 0.0f) {
                const float inv = 1.0f / len;
                direction.z = direction.z * inv;
                direction.x = direction.x * inv;
                direction.y = direction.y * inv;
            }
        }
        OrientAlongDirection(&direction, m_qLastPathRotation);  // 0x00420270
    }
    if (block != 0) SetNavBlocking(1);
}

// 0x00420630 CKHkPlatform_vfC8 (the rlwinm sequences of 0x420658.. / 0x42070c..)
void CKHkPlatform::ApplyStatePreset(int32_t state) {
    uint32_t f;
    if (state != 0) {
        f = (m_bitArray & 0xf8ffffffu) | ppc::rlwinm(m_bitArray, 10, 5, 7);
        m_bitArray = f;
        f = (f & 0xfffffdffu) | (((m_bitArray >> 18) & 1u) << 9);
        m_bitArray = f;
        f = (f & 0x7fffffffu) | (static_cast<uint32_t>(m_unk154[1]) << 31);
        m_bitArray = f;
        SetPathDistance(m_unk5C[9] * m_unk5C[4], 0);  // +0x80 * +0x6c
        f = (m_bitArray & 0xdfffffffu) | ppc::rlwinm(m_unk154[3], 29, 0, 2);
        m_bitArray = f;
        f = (f & 0xbfffffffu) | ppc::rlwinm(m_unk154[5], 30, 0, 1);
        m_bitArray = f;
        return;
    }
    f = (m_bitArray & 0xf8ffffffu) | ppc::rlwinm(m_bitArray, 14, 5, 7);
    m_bitArray = f;
    f = (f & 0xfffffdffu) | (((m_bitArray >> 13) & 1u) << 9);
    m_bitArray = f;
    f = (f & 0x7fffffffu) | (static_cast<uint32_t>(m_unk154[0]) << 31);
    m_bitArray = f;
    SetPathDistance(m_unk30[4] * m_unk5C[4], 0);  // +0x40 * +0x6c
    f = (m_bitArray & 0xdfffffffu) | ppc::rlwinm(m_unk154[2], 29, 0, 2);
    m_bitArray = f;
    f = (f & 0xbfffffffu) | ppc::rlwinm(m_unk154[4], 30, 0, 1);
    m_bitArray = f;
}

// 0x00421020 CKHkPlatform_SetDefaultState (the rlwinm sequences of 0x4210c0.. and 0x4211d8..)
void CKHkPlatform::SetDefaultState(int32_t flag) {
    CKHkActorBase::SetDefaultState(flag);  // KStub_Nop_3f72a0
    const uint8_t on = static_cast<uint8_t>(flag);
    if (on != 0 && (m_bitArray & 4u) == 0) SetNavBlocking(0);  // 0x0041e578
    const float start = m_unk30[4] * m_unk5C[4];  // fmuls +0x40 * +0x6c
    m_fTimer = 0.0f;
    m_fPositionOnPath = start;
    m_pfPoint = kVectorZero;
    m_pfPointIndex = 0xffff;
    uint32_t f = m_bitArray;
    m_bitArray = f & 0xf7ffffffu;
    uint32_t g = (f & 0xf0ffffffu) | ppc::rlwinm(m_bitArray, 14, 5, 7);
    m_bitArray = g;
    g = (g & 0xfffffdffu) | (((m_bitArray >> 13) & 1u) << 9);
    m_bitArray = g & 0xefffffffu;
    m_qLastSlopeRotation[0] = 0.0f;
    m_qLastSlopeRotation[3] = 1.0f;
    m_qLastSlopeRotation[1] = 0.0f;
    m_qLastSlopeRotation[2] = 0.0f;
    m_qLastPathRotation[2] = m_qBaseOrientation[2];
    m_qLastPathRotation[0] = m_qBaseOrientation[0];
    m_qLastPathRotation[1] = m_qBaseOrientation[1];
    m_qLastPathRotation[3] = m_qBaseOrientation[3];
    m_vPosition = kVectorZero;
    m_unk1A8 = 0.0f;
    m_unk1AC = kVectorZero;
    m_unk1B8 = kVectorZero;
    m_unk1C4 = 0;
    m_unk1C8 = kVectorZero;
    m_unk1D4 = kVectorZero;
    f = m_bitArray & 0x9fffffffu;
    m_bitArray = f;
    if (on == 0) {
        f = (f & 0xf8ffffffu) | ppc::rlwinm(m_bitArray, 14, 5, 7);
        m_bitArray = f;
        f = (f & 0xfffffdffu) | (((m_bitArray >> 13) & 1u) << 9);
        m_bitArray = f;
        f = (f & 0x7fffffffu) | (static_cast<uint32_t>(m_unk154[0]) << 31);
        m_bitArray = f;
        f = f | ppc::rlwinm(m_unk154[2], 29, 0, 2);
        m_bitArray = f;
        f = (f & 0xbfffffffu) | ppc::rlwinm(m_unk154[4], 30, 0, 1);
        m_bitArray = f;
    }
    SetPathDistance(m_unk30[4] * m_unk5C[4], 0);  // 0x004204a8 (tail call)
}

// 0x0041eb18 CKHkPlatform_StartMoveSounds_maybe (0.0 TOC1 +0x4d20)
void CKHkPlatform::StartMoveSounds() {
    if ((m_bitArray & 4u) != 0) return;
    CKSound* loop = SoundsOf(m_unkBC)->GetSound2(1);  // 0x00112bd8
    if (loop == nullptr || loop->IsPlaying() != 0) return;  // 0x00111568
    CKSound* start = SoundsOf(m_unkBC)->GetSound2(0);
    if (start != nullptr) {
        start->SetSpeed(m_unk5C[10]);  // +0x84, 0x00110e98
        start->Play(0.0f);             // 0x00111230
    }
    loop->SetLoop(1);  // 0x00110fd0
    loop->SetSpeed(m_unk5C[10]);
    loop->Play(0.0f);
}

namespace {
// The movement bits 24..26 (the flags word's first byte on the PS3, lbz +0xc) = `mode`, after StartMoveSounds when none
// was set (the cases 0x99c..0x9a0 of MessageProc); 0x99f also sets bit 27 (backward).
void SetMoveMode(CKHkPlatform* p, uint32_t mode, bool backward) {
    p->m_fTimer = 0.0f;  // stw 0
    uint32_t f = p->m_bitArray & 0xf7ffffffu;
    if (backward) f |= 0x08000000u;
    p->m_bitArray = f;
    if (((p->m_bitArray >> 24) & 7u) == 0) p->StartMoveSounds();  // 0x0041eb18
    p->m_bitArray = (p->m_bitArray & 0xf8ffffffu) | mode;
}
}  // namespace

// 0x00425378 CKHkPlatform_MessageProc (the cases at 0x00425508..0x00425b98)
int32_t CKHkPlatform::MessageProc(uint16_t message, void* data) {
    const int32_t base = CKHkActorBase::MessageProc(message, data);  // 0x003f7148
    int32_t own = 1;
    const uint32_t index = (static_cast<uint32_t>(message) + 0x6au) & 0xffu;
    if (((message >> 8) & 0xffu) == 9 && index <= 0x12) {
        own = 0;
        switch (index) {
        case 0: {  // 0x996 reset: the Load's runtime block, the start distance (box moved), the sounds when moving
            const float start = m_unk30[4] * m_unk5C[4];
            m_fTimer = 0.0f;
            m_fPositionOnPath = start;
            m_pfPoint = kVectorZero;
            m_pfPointIndex = 0xffff;
            uint32_t f = m_bitArray;
            m_bitArray = f & 0xf7ffffffu;
            uint32_t g = (f & 0xf0ffffffu) | ppc::rlwinm(m_bitArray, 14, 5, 7);
            m_bitArray = g;
            g = (g & 0xfffffdffu) | (((m_bitArray >> 13) & 1u) << 9);
            m_bitArray = g & 0xefffffffu;
            m_qLastSlopeRotation[0] = 0.0f;
            m_qLastSlopeRotation[1] = 0.0f;
            m_qLastSlopeRotation[2] = 0.0f;
            m_qLastSlopeRotation[3] = 1.0f;
            m_qLastPathRotation[2] = m_qBaseOrientation[2];
            m_qLastPathRotation[3] = m_qBaseOrientation[3];
            m_qLastPathRotation[0] = m_qBaseOrientation[0];
            m_qLastPathRotation[1] = m_qBaseOrientation[1];
            m_vPosition = kVectorZero;
            m_unk1A8 = 0.0f;
            m_unk1AC = kVectorZero;
            m_unk1B8 = kVectorZero;
            m_unk1C4 = 0;
            m_unk1C8 = kVectorZero;
            m_unk1D4 = kVectorZero;
            m_bitArray &= 0x9fffffffu;
            SetPathDistance(m_unk30[4] * m_unk5C[4], 1);  // 0x004204a8
            if (((m_bitArray >> 10) & 7u) != 0) StartMoveSounds();
            break;
        }
        case 1:  // 0x997 to the start
            SetPathDistance(0.0f, 1);
            m_fTimer = m_unk30[2];  // +0x38
            break;
        case 2:  // 0x998 to the end
            SetPathDistance(m_unk5C[4], 1);
            m_fTimer = m_unk30[2];
            break;
        case 3:  // 0x999 to the preset distance
            SetPathDistance(m_unk30[4] * m_unk5C[4], 1);
            break;
        case 4: {  // 0x99a stop (unanswered while not moving)
            if (((m_bitArray >> 24) & 7u) == 0) {
                own = 1;
                break;
            }
            m_bitArray &= 0xf8ffffffu;
            if ((m_bitArray & 4u) != 0) break;
            CKSound* loop = SoundsOf(m_unkBC)->GetSound2(1);
            if (loop != nullptr && loop->IsPlaying() != 0) loop->Stop(0);  // 0x001111b0
            break;
        }
        case 5: {  // 0x99b the movement back from the preset bits 10..12
            m_fTimer = 0.0f;  // stw 0
            const uint32_t original = m_bitArray;
            m_bitArray = original & 0xf7ffffffu;
            const uint32_t cleared = m_bitArray;
            const bool wasMoving = ((cleared >> 24) & 7u) != 0;
            m_bitArray = (original & 0xf0ffffffu) | ppc::rlwinm(cleared, 14, 5, 7);
            if (!wasMoving) {
                if (((m_bitArray >> 24) & 7u) != 0) StartMoveSounds();
            } else if (((m_bitArray >> 24) & 7u) == 0 && (m_bitArray & 4u) == 0) {
                CKSound* loop = SoundsOf(m_unkBC)->GetSound2(1);
                if (loop != nullptr && loop->IsPlaying() != 0) loop->Stop(0);
            }
            break;
        }
        case 6: SetMoveMode(this, 0x01000000u, false); break;  // 0x99c
        case 7: SetMoveMode(this, 0x02000000u, false); break;  // 0x99d
        case 8: SetMoveMode(this, 0x03000000u, false); break;  // 0x99e
        case 9: SetMoveMode(this, 0x04000000u, true); break;   // 0x99f
        case 10: SetMoveMode(this, 0x05000000u, false); break; // 0x9a0
        case 11:  // 0x9a1 the path-finding box on
            if ((m_bitArray & 0x200u) != 0) break;
            m_bitArray = (m_bitArray & 0xfffffdffu) | 0x200u;
            SetNavBlocking(1);
            break;
        case 12:  // 0x9a2 the path-finding box off
            if ((m_bitArray & 0x200u) == 0) break;
            SetNavBlocking(0);
            m_bitArray &= 0xfffffdffu;
            break;
        case 13:  // 0x9a3 go back from the start or the end (cror: NaN does nothing)
            if (m_fPositionOnPath <= 0.0f) {
                m_fTimer = 0.0f;
                m_bitArray &= 0xf7ffffffu;
                StartMoveSounds();
                m_bitArray = (m_bitArray & 0xf8ffffffu) | 0x03000000u;
            } else if (m_unk5C[4] <= m_fPositionOnPath) {
                m_fTimer = 0.0f;
                m_bitArray = (m_bitArray & 0xf7ffffffu) | 0x08000000u;
                StartMoveSounds();
                m_bitArray = (m_bitArray & 0xf8ffffffu) | 0x04000000u;
            }
            break;
        case 14: m_bitArray &= 0xdfffffffu; break;                              // 0x9a4
        case 15: m_bitArray &= 0xbfffffffu; break;                              // 0x9a5
        case 16: m_bitArray = (m_bitArray & 0xdfffffffu) | 0x20000000u; break;  // 0x9a6
        case 17: m_bitArray = (m_bitArray & 0xbfffffffu) | 0x40000000u; break;  // 0x9a7
        default: {  // 0x9a8 to the distance sent (a float), clamped to [0, +0x6c]
            const float d = *static_cast<const float*>(data);
            float distance = m_unk5C[4];
            if (d <= 0.0f) {
                distance = 0.0f;
            } else if (!(d >= distance)) {
                distance = d;
            }
            SetPathDistance(distance, 1);
            break;
        }
        }
    }
    if (base == 3 || own == 3) return 3;
    if (base == 2 || own == 2) return 2;
    return base == 0 ? 0 : own;
}

// ---- C2.8 port-final F01: the motion (Update, UpdateMotion, AdvanceAlongPath, the sway spring) ----

namespace {
const float kPfZero = 0.0f;              // TOC1 +0x4d20
const float kPfOne = 1.0f;               // TOC1 +0x4d1c
const float kPfHalf = 0.5f;              // TOC1 +0x4d24 0x3f000000
const float kPfMinSpeedShare = 0.1f;     // TOC1 +0x4d58 0x3dcccccd
const float kPfMinusTenth = -0.1f;       // TOC1 +0x4d78 0xbdcccccd
const float kPfSinkShare = 0.95f;        // TOC1 +0x4dc0 0x3f733333
const float kPfQuatEpsilon = 0.001f;     // TOC1 +0x4dc4 0x3a83126f
const float kPfRadToDeg = 57.2957802f;   // TOC1 +0x4d8c 0x42652ee1
const float kPfPushHeat = 3.0f;          // TOC1 +0x4d94 0x40400000
const float kPfPushHeatMax = 10.0f;      // TOC1 +0x4d98 0x41200000
const float kPfSwayStep = 0.01f;         // TOC1 +0x4d9c 0x3c23d70a
// 0x00c50d4c / 0x00c50d34 (TOC1 +0x4db8 / +0x4dbc): the shared Z and X axes.
const CVector3 kAxisZ = {0.0f, 0.0f, 1.0f};
const CVector3 kAxisX = {1.0f, 0.0f, 0.0f};

CSGMovable* PlatformNode(const CKHkPlatform* p) { return static_cast<CSGMovable*>(p->m_pKGLObject); }
ICollisionMesh* PlatformGround(const CKHkPlatform* p, uint32_t i) {
    return static_cast<ICollisionMesh*>(p->m_apUnk24[i & 0xffu]);
}
void GroundsActive(CKHkPlatform* p, uint16_t active) {
    for (uint32_t i = p->m_unk20; i != 0; --i) PlatformGround(p, i - 1)->SetActive(active);  // 0x001a6b70
}
// The loop (sound 1) stopped when the platform is awake (bit 2 clear) and it plays.
void StopLoopIfPlaying(CKHkPlatform* p) {
    if ((p->m_bitArray & 4u) != 0) return;
    CKSound* loop = SoundsOf(p->m_unkBC)->GetSound2(1);  // 0x00112bd8
    if (loop != nullptr && loop->IsPlaying() != 0) loop->Stop(0);  // 0x00111568, 0x001111b0
}
// The end (+0xfc) / start (+0x104) signals once (+0x10c), with sound 2 at the speed +0x84 (UpdateMotion only).
void ReachedEnd(CKHkPlatform* p, CTriggerStarter* signals, bool sound) {
    if (p->m_unk10C != 0) return;
    QueueTriggerSignals(signals);  // 0x00236338
    p->m_unk10C = 1;
    if (!sound) return;
    CKSound* bump = SoundsOf(p->m_unkBC)->GetSound2(2);
    if (bump == nullptr) return;
    bump->SetSpeed(p->m_unk5C[10]);  // 0x00110e98
    bump->Play(kPfZero);             // 0x00111230
}
// The speed share of the ramps (+0x3c at the start, +0x78 before the end, at least 0.1; 1 between).
float RampShare(const CKHkPlatform* p) {
    const float d = p->m_fPositionOnPath;
    float share;
    if (!(d >= p->m_unk30[3])) {  // bge (NaN: the far part)
        share = d / p->m_unk30[3];
        if (share < kPfMinSpeedShare) share = kPfMinSpeedShare;  // blt
        return share;
    }
    if (!(p->m_unk5C[4] - p->m_unk5C[7] < d)) return kPfOne;  // blt / bge (NaN: 1)
    share = (p->m_unk5C[4] - d) / p->m_unk5C[7];
    if (share < kPfMinSpeedShare) share = kPfMinSpeedShare;  // bge keeps (NaN kept)
    return share;
}
// The inlined ground probe of UpdateMotion / AdvanceAlongPath (bit 3): the platform's grounds off, the ground under the
// position (+0x194) found; on a ground that is not 0x4cc (status 0 / 1) the height is the probe's, raised to the ground's
// value (+0x40) when its engine flag bit 1 is set; the grounds on again.
void FollowGround(CKHkPlatform* p) {
    GroundsActive(p, 0);
    static_cast<CKSrvCollision*>(g_pEngine->m_srvCollision)
        ->GroundProbePoints(&p->m_GrndDataIn, &p->m_GrndDataInOut, &p->m_vPosition.x, 1);  // 0x00196540
    const uint32_t status = p->m_GrndDataInOut.m_eContactStatus;
    if ((status == 0 || status == 1) && p->m_GrndDataInOut.m_pGround->IsKindOfClass(0x4cc) == 0) {  // vt+0x08
        CGround* ground = static_cast<CGround*>(p->m_GrndDataInOut.m_pGround);
        const float probe = p->m_GrndDataInOut.m_ProjectionOnGround.y;  // +0xec
        if (((ground->m_ba16EngineFlags >> 1) & 1u) == 0) {
            p->m_vPosition.y = probe;
        } else {
            const float value = ground->m_fPropertieValue;  // +0x40
            p->m_vPosition.y = value > probe ? value : probe;  // bgt / ble (NaN: the probe)
        }
    }
    GroundsActive(p, 1);
}
// The inlined orientation of UpdateMotion / AdvanceAlongPath (bit 4): `dir` flattened without bit 20, normalised
// (1 / length) into `at`, `right` = (at.z, 0, -at.x) (normalised with bit 20), then OrientAlongDirection into `q`.
void OrientToDirection(CKHkPlatform* p, CVector3* dir, float* q, CVector3* at, CVector3* right) {
    if ((p->m_bitArray & 0x100000u) == 0) dir->y = kPfZero;
    const float length = std::sqrt(ppc::fmadds(dir->z, dir->z, ppc::fmadds(dir->x, dir->x, dir->y * dir->y)));  // 0x10690
    if (length != kPfZero) {
        const float inv = kPfOne / length;
        dir->z = dir->z * inv;
        dir->x = dir->x * inv;
        dir->y = dir->y * inv;
    }
    at->z = dir->z;
    at->x = dir->x;
    right->x = at->z;
    const float negX = -at->x;
    at->y = dir->y;
    right->y = kPfZero;
    right->z = negX;
    if ((p->m_bitArray & 0x100000u) != 0) {
        const float len2 = std::sqrt(ppc::fmadds(negX, negX, ppc::fmadds(right->x, right->x, kPfZero)));
        if (len2 != kPfZero) {
            const float inv = kPfOne / len2;
            right->z = inv * right->z;
            right->x = inv * right->x;
            right->y = inv * right->y;
        }
    }
    p->OrientAlongDirection(dir, q);  // 0x00420270
}
// A random sound of the dictionary (GetSound, no range check): first + (rand & 0xffff) * 3 >> 16, played from 0.
void PlayRandomSound(CKHkPlatform* p, uint32_t first) {
    const uint32_t r = static_cast<uint32_t>(Rand_Int()) & 0xffffu;  // 0x00011500
    const uint32_t index = (((r * 3u) >> 16) & 0xffffu) + first;
    if (SoundsOf(p->m_unkBC)->GetSound(index) == nullptr) return;  // 0x00112bc0
    CKSound_Play(kPfZero, SoundsOf(p->m_unkBC)->GetSound(index));
}
// The sign the sway sound compares (crnor: not less than 0, NaN included, is +1).
int32_t SwaySign(float v) { return v < kPfZero ? -1 : 1; }
}  // namespace

// 0x0041ec28 CKHkPlatform_EnsureLoopSoundPlaying_maybe
void CKHkPlatform::EnsureLoopSoundPlaying() {
    CKSound* loop = SoundsOf(m_unkBC)->GetSound2(1);  // 0x00112bd8
    if (loop == nullptr || loop->IsPlaying() != 0) return;  // 0x00111568
    loop->SetLoop(1);              // 0x00110fd0
    loop->SetSpeed(m_unk5C[10]);   // +0x84
    loop->Play(kPfZero);
}

// 0x004207c0 CKHkPlatform_SimulateSwaySpring_maybe
void CKHkPlatform::SimulateSwaySpring(float dt, float* delta, CVector3* axis, float* rot, const CVector3* force) {
    const RwV3d& at0 = PlatformNode(this)->m_pRwFrame->ltm.pos;  // frame +0x80
    const float px = at0.x;
    const float py = at0.y;
    const float pz = at0.z;
    *axis = kAxisY;
    *rot = 0.0f;  // stw 0
    float vx = m_unk1AC.x;
    float vy = m_unk1AC.y;
    float vz = m_unk1AC.z;
    float damping = m_unk110[1];  // +0x114
    bool pushed = false;
    for (uint32_t i = 0; i < m_unk134; ++i) {
        // The pushers: points (CKMarkerBeacon _maybe: a position at +0x04) within +0x13c push by +0x140 x (1 - d / r).
        const CVector3& point = static_cast<CKMarkerBeacon*>(m_apUnk138[i])->m_v3Position;
        const float dy = point.y - py;
        const float dx = point.x - px;
        const float dz = point.z - pz;
        const float d2 = ppc::fmadds(dz, dz, ppc::fmadds(dx, dx, dy * dy));
        if (!(d2 > 0.0f)) continue;                       // ble (NaN: skipped)
        if (!(m_unk13C * m_unk13C > d2)) continue;         // ble
        const float d = std::sqrt(d2);                     // 0x10690
        const float push = ((m_unk13C - d) * m_unk140) / (d * m_unk13C);
        pushed = true;
        vz = ppc::fmadds(dz, push, vz);
        vx = ppc::fmadds(dx, push, vx);
        vy = ppc::fmadds(dy, push, vy);
        if (m_unk1AC.x == 0.0f && m_unk1AC.y == 0.0f && m_unk1AC.z == 0.0f) {  // the null vector 0x00c50d64
            damping = damping + kPfPushHeat / d;
            if (damping > kPfPushHeatMax) damping = kPfPushHeatMax;  // ble keeps (NaN kept)
        }
    }
    if (!pushed) {
        vz = vz + force->z;
        vx = vx + force->x;
        vy = vy + force->y;
    }
    if (dt > kPfZero) {  // ble (NaN: no step)
        const float drag = -damping;
        float left = dt;
        float step = kPfSwayStep;
        do {
            if (step > left) step = left;  // ble keeps
            left = left - step;
            float ax = kVectorZero.x;
            float ay = kVectorZero.y;
            float az = kVectorZero.z;
            if ((m_bitArray & 0x100u) != 0 && (m_unk28 != nullptr || m_unk2C != nullptr)) {
                // On a path: the push along the direction (+0x1e0) and gravity's share of it (+0x110 x dir.y).
                const float gy = -m_unk110[0] * m_unk1E0.y;
                float dot = vy * m_unk1E0.y;
                dot = ppc::fmadds(vx, m_unk1E0.x, dot);
                const float fy = ppc::fmadds(gy, m_unk1E0.y, ay);
                const float fx = ppc::fmadds(gy, m_unk1E0.x, ax);
                const float fz = ppc::fmadds(gy, m_unk1E0.z, az);
                dot = ppc::fmadds(vz, m_unk1E0.z, dot);
                float ny = ppc::fmadds(m_unk1E0.y, dot, fy);
                float nx = ppc::fmadds(m_unk1E0.x, dot, fx);
                float nz = ppc::fmadds(m_unk1E0.z, dot, fz);
                const float oy = m_unk1C8.y;
                const float ox = m_unk1C8.x;
                const float oz = m_unk1C8.z;
                ny = ppc::fmadds(drag, oy, ny);
                nx = ppc::fmadds(drag, ox, nx);
                nz = ppc::fmadds(drag, oz, nz);
                ny = ppc::fmadds(step, ny, oy);
                nx = ppc::fmadds(step, nx, ox);
                nz = ppc::fmadds(step, nz, oz);
                m_unk1C8.y = ny;
                const float sy = ny * m_unk1E0.y;
                m_unk1C8.x = nx;
                m_unk1C8.z = nz;
                float along = ppc::fmadds(nx, m_unk1E0.x, sy);
                along = ppc::fmadds(nz, m_unk1E0.z, along);
                *delta = ppc::fmadds(step, along, *delta);
            } else {
                const uint8_t axes = m_unk10D;
                const RwV3d& up = PlatformNode(this)->m_pRwFrame->ltm.at;  // frame +0x70
                if ((axes & 1u) != 0) {
                    float k = vy * up.y;
                    k = ppc::fmadds(vx, up.x, k);
                    k = ppc::fmadds(vz, up.z, k);
                    az = ppc::fmadds(up.z, k, az);
                    ax = ppc::fmadds(up.x, k, ax);
                    ay = ppc::fmadds(up.y, k, ay);
                }
                if ((axes & 2u) != 0) {  // BUG(original)?: the same axis (frame +0x70) as bit 0
                    float k = vy * up.y;
                    k = ppc::fmadds(vx, up.x, k);
                    k = ppc::fmadds(vz, up.z, k);
                    az = ppc::fmadds(up.z, k, az);
                    ax = ppc::fmadds(up.x, k, ax);
                    ay = ppc::fmadds(up.y, k, ay);
                }
                if ((axes & 4u) != 0) {
                    float k = vy * kAxisY.y;
                    k = ppc::fmadds(vx, kAxisY.x, k);
                    k = ppc::fmadds(vz, kAxisY.z, k);
                    const float ty = ppc::fmadds(kAxisY.y, k, ay);
                    az = ppc::fmadds(kAxisY.z, k, az);
                    ax = ppc::fmadds(kAxisY.x, k, ax);
                    ay = ty - m_unk110[0];
                }
                const float ox = m_unk1C8.x;
                const float oy = m_unk1C8.y;
                const float oz = m_unk1C8.z;
                float nx = ppc::fmadds(drag, ox, ax);
                float ny = ppc::fmadds(drag, oy, ay);
                float nz = ppc::fmadds(drag, oz, az);
                nx = ppc::fmadds(step, nx, ox);
                ny = ppc::fmadds(step, ny, oy);
                nz = ppc::fmadds(step, nz, oz);
                m_unk1C8.x = nx;
                const float qx = ppc::fmadds(step, nx, m_unk1D4.x);
                m_unk1C8.y = ny;
                m_unk1C8.z = nz;
                const float qy = ppc::fmadds(step, ny, m_unk1D4.y);
                const float qz = ppc::fmadds(step, nz, m_unk1D4.z);
                m_unk1D4.x = qx;
                m_unk1D4.y = qy;
                m_unk1D4.z = qz;
            }
        } while (left > kPfZero);  // bgt / ble
    }
    // The heroes' tilt (+0x1c4 of them, their positions summed in +0x1b8, axes bits 3..5 of +0x10d).
    const uint8_t n = m_unk1C4;
    if (n == 0) return;
    const uint8_t axes = m_unk10D;
    if (((axes >> 3) & 1u) == 0 && ((axes >> 4) & 1u) == 0 && ((axes >> 5) & 1u) == 0) return;
    const float inv = kPfOne / static_cast<float>(static_cast<int32_t>(n));  // extsw, fcfid, frsp, fdivs
    m_unk1B8.y = inv * m_unk1B8.y;
    m_unk1B8.z = inv * m_unk1B8.z;
    m_unk1B8.x = inv * m_unk1B8.x;
    const float dy = py - m_unk1B8.y;
    const float dz = pz - m_unk1B8.z;
    const float dx = px - m_unk1B8.x;
    axis->x = ppc::fmsubs(dz, m_unk1AC.y, dy * m_unk1AC.z);
    axis->y = ppc::fmsubs(dx, m_unk1AC.z, dz * m_unk1AC.x);
    axis->z = ppc::fmsubs(dy, m_unk1AC.x, dx * m_unk1AC.y);
    CMatrix34 ltm;
    std::memcpy(&ltm, &PlatformNode(this)->m_pRwFrame->ltm, sizeof(CMatrix34));  // the 16 words
    CMatrix34 inverse;
    Mat4_Invert(&inverse, &ltm);  // 0x0023f878
    CVector3 local;
    Mat4_TransformVectors(&inverse, &local, axis, 1);  // 0x0023f7b0
    const uint8_t limits = m_unk10D;
    // Each local axis kept (bits 3 / 4 / 5) scaled (+0x11c / +0x124 / +0x12c) and clamped to +-(+0x118 / +0x120 /
    // +0x128) (the positive side's ble keeps the limit on a NaN), else 0.
    const float* limit = &m_unk110[2];
    float* values[3] = {&local.x, &local.y, &local.z};
    for (uint32_t k = 0; k < 3; ++k) {
        float& v = *values[k];
        if (((limits >> (3 + k)) & 1u) == 0) {
            v = 0.0f;  // stw 0
            continue;
        }
        const float max = limit[k * 2];
        const float scale = limit[k * 2 + 1];
        if (!(v > kPfZero)) {  // ble
            const float scaled = v * scale;
            v = (-max > scaled) ? -max : scaled;  // bgt / ble
        } else {
            const float scaled = v * scale;
            v = !(max > scaled) ? max : scaled;  // ble (NaN: the limit)
        }
    }
    Mat4_TransformVectors(&ltm, axis, &local, 1);
    const float length = std::sqrt(ppc::fmadds(axis->z, axis->z, ppc::fmadds(axis->x, axis->x, axis->y * axis->y)));
    if (length == kPfZero) {  // bne
        *rot = kPfZero;
        return;
    }
    const float k = kPfOne / length;
    axis->z = k * axis->z;
    axis->x = k * axis->x;
    axis->y = k * axis->y;
    *rot = length;
}

// 0x00423620 CKHkPlatform_UpdateMotion_maybe: the platform moved by its sway spring (the waiting timer +0x160 first;
// the push force the ramp speed share along the direction +0x1e0); the ends reached as AdvanceAlongPath does (the
// signals with sound 2, the velocity's x / z cleared); the position on the path plus the offset and the spring's
// offset (+0x1d4), the ground followed (bit 3), the orientation (bit 4), then the spring's tilt about its axis.
void CKHkPlatform::UpdateMotion(float dt, float* q, CVector3* at, CVector3* right) {
    SetNavBlocking(0);  // 0x0041e578
    float push = kPfZero;
    if (m_fTimer > kPfZero) {  // ble (NaN: no wait)
        m_fTimer = m_fTimer - dt;
        if (m_fTimer <= kPfZero) {  // cror lt|eq
            m_fTimer = kPfZero;
            StartMoveSounds();  // 0x0041eb18
        }
    } else if (((m_bitArray >> 24) & 7u) != 0) {
        const float share = RampShare(this);
        push = (m_bitArray & 0x08000000u) != 0 ? -share * m_unk5C[8] : share * m_unk30[1];  // +0x7c / +0x34
    }
    if (((m_bitArray >> 24) & 7u) == 0) push = kPfZero;
    float deltaPos = 0.0f;  // stw 0
    const float decay = m_unk110[8];  // +0x130
    m_unk1AC.x = decay * m_unk1AC.x;
    m_unk1AC.z = decay * m_unk1AC.z;
    m_unk1AC.y = decay * m_unk1AC.y;
    const CVector3 force = {push * m_unk1E0.x, push * m_unk1E0.y, push * m_unk1E0.z};
    CVector3 axis;
    float rot;
    SimulateSwaySpring(dt, &deltaPos, &axis, &rot, &force);  // 0x004207c0
    float delta = deltaPos;
    const uint32_t bits = m_bitArray;
    if ((bits & 0x40000000u) != 0 && delta < 0.0f) {
        delta = kPfZero;
    } else if ((bits & 0x20000000u) != 0 && !(delta <= kPfZero)) {  // ble (NaN: blocked)
        delta = kPfZero;
    }
    const float d = delta + m_fPositionOnPath;  // fadds
    m_fPositionOnPath = d;
    if (d <= kPfZero) {  // cror lt|eq: the start reached
        m_fPositionOnPath = kPfZero;
        m_fUnk1F0 = kPfZero;
        StopLoopIfPlaying(this);
        ReachedEnd(this, &m_unk104, true);
        const uint32_t mode = (m_bitArray >> 24) & 7u;
        m_unk1C8.x = 0.0f;  // stw 0
        m_unk1C8.z = 0.0f;
        if (mode == 2) {
            m_bitArray &= 0xf7ffffffu;
            m_fTimer = m_unk30[2];  // +0x38
        } else if (mode >= 2 && mode - 4u <= 1u) {
            m_bitArray &= 0xf8ffffffu;
            m_fTimer = 0.0f;  // stw 0
        }
    } else if (m_unk5C[4] <= d) {  // cror lt|eq: the end reached
        m_fUnk1F0 = kPfZero;
        m_fPositionOnPath = m_unk5C[4];
        StopLoopIfPlaying(this);
        ReachedEnd(this, &m_unkFC, true);
        const uint32_t mode = (m_bitArray >> 24) & 7u;
        m_unk1C8.x = 0.0f;
        m_unk1C8.z = 0.0f;
        if (mode == 2 || mode == 5) {
            m_bitArray = (m_bitArray & 0xf7ffffffu) | 0x08000000u;
            m_fTimer = m_unk30[2];
        } else if (mode == 1) {
            SetPathDistance(0.0f, 0);  // 0x004204a8
            m_bitArray &= 0xf7ffffffu;
            m_fTimer = m_unk30[2];
        } else if (mode == 3) {
            m_fTimer = 0.0f;  // stw 0
        }
    } else {
        const float speed = delta / dt;  // fdivs
        m_unk10C = 0;
        if (speed > kPfMinSpeedShare || speed < kPfMinusTenth) {
            EnsureLoopSoundPlaying();  // 0x0041ec28
        } else {
            StopLoopIfPlaying(this);
        }
        m_fUnk1F0 = speed;
    }
    EvaluatePathPosition(m_fPositionOnPath, &m_vPosition, &m_unk1E0);  // 0x0041ffe8
    float x = m_vPosition.x + m_vPositionOffset.x;
    float z = m_vPosition.z + m_vPositionOffset.z;
    float y = m_vPosition.y + m_vPositionOffset.y;
    m_vPosition.x = x;
    m_vPosition.y = y;
    m_vPosition.z = z;
    x = x + m_unk1D4.x;
    z = z + m_unk1D4.z;
    y = y + m_unk1D4.y;
    m_vPosition.x = x;
    m_vPosition.z = z;
    m_vPosition.y = y;
    if ((m_bitArray & 8u) != 0) FollowGround(this);
    if ((m_bitArray & 0x10u) != 0) {
        CVector3 dir = m_unk1E0;
        OrientToDirection(this, &dir, q, at, right);
    }
    if (rot != kPfZero) {  // beq (NaN: tilted)
        CMatrix34 m;
        Quat_ToMatrixNormalizing(q, &m);  // 0x00241d78
        CMatrix34 inverse;
        Mat4_Invert(&inverse, &m);  // 0x0023f878
        CVector3 local;
        Mat4_TransformPoints(&inverse, &local, &axis, 1);  // 0x0023f7e8
        Quat_Rotate(q, reinterpret_cast<const RwV3d*>(&local), rot);  // 0x00242130
    }
}

// 0x00423f70 CKHkPlatform_AdvanceAlongPath_maybe: with a move mode (bits 24..26) the waiting timer (+0x160) runs out
// first (the move sounds then); else the distance (+0x15c) moves by the ramp share x the speed (+0x34 forward, +0x7c
// backward with bit 27 unless bit 30; none with bit 29) and the ends play the signals, stop the loop and switch the
// mode (1: back to 0, 2 / 5: back and forth with a wait, 3: stop, 4 / 5 at the start: stop). Then the position on
// the path plus the offset, the ground (bit 3) and the orientation (bit 4).
void CKHkPlatform::AdvanceAlongPath(float dt, float* q, CVector3* at, CVector3* right) {
    if (((m_bitArray >> 24) & 7u) == 0) return;
    if (m_fTimer > kPfZero) {  // ble (NaN: moving)
        const float t = m_fTimer - dt;
        m_fTimer = t;
        if (t <= kPfZero) {  // cror lt|eq
            m_fTimer = kPfZero;
            StartMoveSounds();  // 0x0041eb18
        }
    } else {
        SetNavBlocking(0);  // 0x0041e578
        const float share = RampShare(this);
        const uint32_t bits = m_bitArray;
        float d = m_fPositionOnPath;
        if ((bits & 0x08000000u) != 0 && (bits & 0x40000000u) == 0) {
            d = d - dt * (share * m_unk5C[8]);  // fmuls, fmuls, fsubs
            m_fPositionOnPath = d;
        } else if ((bits & 0x20000000u) == 0) {
            d = ppc::fmadds(share * m_unk30[1], dt, d);
            m_fPositionOnPath = d;
        }
        if (d <= kPfZero) {  // cror lt|eq: the start
            m_fPositionOnPath = kPfZero;
            StopLoopIfPlaying(this);
            ReachedEnd(this, &m_unk104, false);
            const uint32_t mode = (m_bitArray >> 24) & 7u;
            if (mode == 2) {
                m_bitArray &= 0xf7ffffffu;
                m_fTimer = m_unk30[2];
            } else if (mode >= 2 && mode - 4u <= 1u) {
                m_bitArray &= 0xf8ffffffu;
                m_fTimer = 0.0f;  // stw 0
            }
        } else if (!(m_unk5C[4] <= d)) {  // cror lt|eq, bne (NaN: moving)
            m_unk10C = 0;
            EnsureLoopSoundPlaying();  // 0x0041ec28
        } else {  // the end
            StopLoopIfPlaying(this);
            m_fPositionOnPath = m_unk5C[4];
            ReachedEnd(this, &m_unkFC, false);
            const uint32_t mode = (m_bitArray >> 24) & 7u;
            if (mode == 2 || mode == 5) {
                StopLoopIfPlaying(this);
                m_bitArray = (m_bitArray & 0xf7ffffffu) | 0x08000000u;
                m_fTimer = m_unk30[2];
            } else if (mode == 1) {
                SetPathDistance(kPfZero, 0);  // 0x004204a8
                m_bitArray &= 0xf7ffffffu;
                m_fTimer = m_unk30[2];
            } else if (mode == 3) {
                StopLoopIfPlaying(this);
                m_bitArray &= 0xf8ffffffu;
                m_fTimer = 0.0f;  // stw 0
            }
        }
    }
    CVector3 dir;
    EvaluatePathPosition(m_fPositionOnPath, &m_vPosition, &dir);  // 0x0041ffe8
    m_vPosition.x = m_vPosition.x + m_vPositionOffset.x;
    m_vPosition.z = m_vPosition.z + m_vPositionOffset.z;
    m_vPosition.y = m_vPosition.y + m_vPositionOffset.y;
    if ((m_bitArray & 8u) != 0) FollowGround(this);
    if ((m_bitArray & 0x10u) != 0) OrientToDirection(this, &dir, q, at, right);
}

// 0x00424690 CKHkPlatform_Update
void CKHkPlatform::Update(IKTime* clock) {
    CKHkActorBase::Update(clock);  // 0x003f6e68
    const float dt = clock->m_afDeltaTime[0];
    uint32_t bits = m_bitArray;
    CVector3 at;
    CVector3 right;
    if ((bits & 0x200000u) != 0) {
        const RwFrame* frame = PlatformNode(this)->m_pRwFrame;
        at = {frame->modelling.at.x, frame->modelling.at.y, frame->modelling.at.z};
        right = {frame->modelling.right.x, frame->modelling.right.y, frame->modelling.right.z};
    } else {
        at = kAxisZ;
        right = kAxisX;
    }
    if ((bits & 0x80000000u) == 0) return;
    float qPath[4] = {m_qBaseOrientation[0], m_qBaseOrientation[1], m_qBaseOrientation[2], m_qBaseOrientation[3]};
    if ((bits & 0x800000u) != 0) {
        UpdateMotion(dt, qPath, &at, &right);  // 0x00423620
    } else {
        AdvanceAlongPath(dt, qPath, &at, &right);  // 0x00423f70
    }
    float qSlope[4] = {0.0f, 0.0f, 0.0f, kPfOne};
    CKGrpS08Hero* group = static_cast<CKGrpS08Hero*>(g_pEngine->m_gameManager->m_unk04[1]);  // engine +0x8c -> +0x08
    if (group != nullptr) {
        bits = m_bitArray;
        if ((bits & 0x20u) != 0 || (bits & 0x40u) != 0 || (bits & 0x400000u) != 0) {
            // The heroes on the first ground: their count, the sway they push (their offsets from the node along the
            // at / right axes, weighted 1, or by how deep they stand in a sinking ground (flag 358 bit 8)).
            IKSerializable** heroes = group->m_apHeroesCopy;  // 0x002ca0f0
            uint32_t count = 0;
            if (heroes[0] == nullptr) {
                m_unk1EC = 0;
            } else {
                float swayAt = kPfZero;
                float swayRight = kPfZero;
                for (uint32_t h = 0; heroes[h] != nullptr; ++h) {
                    CKHkS08Hero* hero = static_cast<CKHkS08Hero*>(heroes[h]);
                    if (hero->IsPlayerControlled() == 0 && (m_bitArray & 0x80000u) != 0) continue;  // 0x00362af0
                    if (static_cast<IKSerializable*>(m_apUnk24[0]) != hero->GetGroundObject()) continue;  // 0x00363c40
                    const float* position = hero->GetPositionPtr();  // 0x00361968
                    const RwV3d& origin = PlatformNode(this)->m_pRwFrame->ltm.pos;
                    const float hz = position[2];
                    const float hx = position[0];
                    const float oz = origin.z;
                    const float ox = origin.x;
                    if ((hero->GetFlag35CBit8() & 0xffu) != 0) continue;  // 0x00361ab0
                    const uint32_t sinking = hero->GetFlag358Bit8() & 0xffu;  // 0x00361b50
                    ++count;
                    float weight = kPfOne;
                    if (sinking != 0) {
                        weight = static_cast<CGround*>(m_apUnk24[0])->m_fPropertieValue;  // +0x40
                        weight = weight - hero->GetPositionPtr()[1];
                        weight = weight / hero->GetUnk26C();  // 0x00361b60
                        weight = kPfOne - weight;
                        weight = weight * kPfSinkShare;
                    }
                    const float dx = hx - ox;
                    const float dz = hz - oz;
                    float alongAt = at.y * kPfZero;
                    const float rightY = right.y * kPfZero;
                    alongAt = ppc::fmadds(dx, at.x, alongAt);
                    float alongRight = ppc::fmadds(dx, right.x, rightY);
                    alongAt = ppc::fmadds(dz, at.z, alongAt);
                    alongRight = ppc::fnmadds(dz, right.z, alongRight);
                    swayAt = ppc::fmadds(weight, alongAt, swayAt);
                    swayRight = ppc::fmadds(weight, alongRight, swayRight);
                }
                const uint32_t counted = count & 0xffu;
                if (m_unk1EC < counted) PlayRandomSound(this, 4);  // sounds 4..6
                m_unk1EC = static_cast<uint8_t>(count);
                if (counted != 0) {
                    const float sx = m_unk30[5] * swayAt;     // +0x44
                    const float sz = swayRight * m_unk30[6];  // +0x48
                    const float oldX = m_unk1A0[0];
                    const float oldZ = m_unk1A0[1];
                    m_unk1A0[0] = sx;
                    m_unk1A0[1] = sz;
                    bool knock = false;
                    if (m_unk5C[0] * kPfHalf < std::fabs(sx) && SwaySign(sx) != SwaySign(oldX)) {
                        knock = true;
                    } else if (m_unk5C[1] * kPfHalf < std::fabs(sz) && SwaySign(sz) != SwaySign(oldZ)) {
                        knock = true;
                    }
                    if (knock) PlayRandomSound(this, 7);  // sounds 7..9
                    if ((m_bitArray & 0x20u) != 0) {
                        const float max = m_unk5C[0];
                        const float v = m_unk1A0[0];
                        const float a = max < v ? max : v;
                        const float angle = a < -max ? -max : a;
                        Quat_Rotate(qSlope, reinterpret_cast<const RwV3d*>(&right), angle);  // 0x00242130
                    }
                    if ((m_bitArray & 0x40u) != 0) {
                        const float max = m_unk5C[1];
                        const float v = m_unk1A0[1];
                        const float a = max < v ? max : v;
                        const float angle = a < -max ? -max : a;
                        Quat_Rotate(qSlope, reinterpret_cast<const RwV3d*>(&at), angle);
                    }
                }
            }
            if ((m_bitArray & 0x400000u) != 0) {
                // The sinking (+0x1a8) towards the heroes' count x +0x50, at +0x54 down / +0x58 up a second.
                const float target = static_cast<float>(count & 0xffu) * m_unk50[0];
                const float sink = m_unk1A8;
                if (!(target < sink)) {  // bge (NaN: going down)
                    const float next = ppc::fmadds(m_unk50[1], dt, sink);
                    m_unk1A8 = next;
                    if (target < next) m_unk1A8 = target;  // bge (NaN: kept)
                } else {
                    const float next = sink - m_unk50[2] * dt;  // fmuls, fsubs
                    m_unk1A8 = next;
                    if (target > next) m_unk1A8 = target;  // ble (NaN: kept)
                }
            }
        }
        if ((m_bitArray & 0x80u) != 0) {
            // The companions on the first ground at an end are told to leave it (0xc3b when the controlled hero can be
            // reached), elsewhere 0xc41.
            IKSerializable** companions = group->m_apCompanionHeroes;  // 0x002ca0e8
            CKHkS08Hero* leader = static_cast<CKHkS08Hero*>(group->m_apControlledHeroes[0]);  // 0x002ca0e0
            for (uint32_t c = 0; companions[c] != nullptr; ++c) {
                CKHkS08Hero* hero = static_cast<CKHkS08Hero*>(companions[c]);
                if (static_cast<IKSerializable*>(m_apUnk24[0]) != hero->GetGroundObject()) continue;
                const float d = m_fPositionOnPath;
                if (d <= kPfZero || m_unk5C[4] <= d) {  // cror lt|eq (NaN: 0xc41)
                    CKSrvPathFinding* pf = static_cast<CKSrvPathFinding*>(g_pEngine->m_srvPathFinding);  // engine +0x6c
                    const CPFPoint* from = static_cast<const CPFPoint*>(hero->GetPFDestination());  // 0x00361a40
                    const CPFPoint* to = static_cast<const CPFPoint*>(leader->GetPFDestination());
                    const CPFCharacter* character = hero->GetPFCharacter();  // 0x00361a30
                    if ((pf->HasSectorRoute(from, to, character, nullptr) & 0xffu) == 0) continue;  // 0x001e9198
                    hero->MessageProc(0xc3b, nullptr);  // vt+0x1c
                } else {
                    hero->MessageProc(0xc41, nullptr);
                }
            }
        }
    }
    // The slope (+0x164) and the path orientation (+0x174) eased towards their targets, combined into the node.
    float t = m_unk30[7] * dt;  // +0x4c
    if (t > kPfOne) t = kPfOne;  // ble keeps
    float slope[4];
    Quat_Slerp(t, slope, m_qLastSlopeRotation, qSlope);  // 0x00242728
    Quat_Normalize(slope);  // 0x00242180
    if (std::fabs(slope[3] - m_qLastSlopeRotation[3]) > kPfQuatEpsilon ||
        std::fabs(slope[0] - m_qLastSlopeRotation[0]) > kPfQuatEpsilon ||
        std::fabs(slope[2] - m_qLastSlopeRotation[2]) > kPfQuatEpsilon ||
        std::fabs(slope[1] - m_qLastSlopeRotation[1]) > kPfQuatEpsilon) {
        CKSound* creak = SoundsOf(m_unkBC)->GetSound2(3);  // 0x00112bd8
        if (creak != nullptr && creak->IsPlaying() == 0) {   // 0x00111568
            creak->SetLoop(1);  // 0x00110fd0
            creak->Play(kPfZero);
        }
    } else if (SoundsOf(m_unkBC)->GetSound2(3) != nullptr) {
        SoundsOf(m_unkBC)->GetSound2(3)->Stop(0);  // 0x001111b0
    }
    m_qLastSlopeRotation[3] = slope[3];
    m_qLastSlopeRotation[1] = slope[1];
    m_qLastSlopeRotation[0] = slope[0];
    m_qLastSlopeRotation[2] = slope[2];
    t = m_unk5C[2] * dt;  // +0x64
    if (t > kPfOne) t = kPfOne;
    float path[4];
    Quat_Slerp(t, path, m_qLastPathRotation, qPath);
    Quat_Normalize(path);
    m_qLastPathRotation[0] = path[0];
    m_qLastPathRotation[1] = path[1];
    m_qLastPathRotation[2] = path[2];
    m_qLastPathRotation[3] = path[3];
    float q[4];
    Quat_Multiply(q, slope, path);  // 0x00241cc0
    Quat_Normalize(q);
    CMatrix34 m;
    Quat_ToMatrixNormalizing(q, &m);  // 0x00241d78
    m.m_pos.x = m_vPosition.x;
    m.m_pos.z = m_vPosition.z;
    m.m_pos.y = m_vPosition.y - m_unk1A8;
    m.m_ui32Flags &= 0xfffdffffu;
    CKQuakeCpntUpdater* quake = static_cast<CKQuakeCpntUpdater*>(m_unk144[1]);  // +0x148
    if (quake == nullptr || quake->m_bRunning == 0) {
        PlatformNode(this)->SetLocalMatrix(reinterpret_cast<const RwMatrix*>(&m));  // 0x000d0be8
    } else {
        float sample[15];
        quake->EvaluateScaled(dt, kPfOne, sample);  // 0x0024f5c8
        CMatrix34 shaken;
        ShakeSample_BuildMatrix(quake, sample, &shaken, &m);  // 0x0024ee90
        Mat4_TransformPostConcat(&shaken, &m);                 // 0x0023f760
        PlatformNode(this)->SetLocalMatrix(reinterpret_cast<const RwMatrix*>(&shaken));
    }
    // The first ground slippery (properties bit 1) while the node tilts more than +0x30 degrees.
    const float limit = m_unk30[0];
    const float tilt = std::fabs(crt::Acosf(PlatformNode(this)->m_pRwFrame->ltm.up.y) * kPfRadToDeg);  // frame +0x64
    ICollisionMesh* first = PlatformGround(this, 0);
    if (limit <= tilt) {  // cror lt|eq
        first->m_ui16PropertiesFlags = static_cast<uint16_t>(first->m_ui16PropertiesFlags | 2u);
    } else {
        first->m_ui16PropertiesFlags = static_cast<uint16_t>(first->m_ui16PropertiesFlags & 0xfffdu);
    }
    // The moving grounds refreshed (CKHkBridgeBase's inlined refresh: once per frame, their parent's matrix).
    for (int32_t i = static_cast<int32_t>(m_unk20) - 1; i != -1; --i) {
        CDynamicGround* ground = static_cast<CDynamicGround*>(m_apUnk24[static_cast<uint32_t>(i) & 0xffu]);
        if ((ground->m_ba16EngineFlags & 0x20u) != 0) continue;
        ground->m_ba16EngineFlags = static_cast<uint16_t>(ground->m_ba16EngineFlags | 0x20u);
        if ((ground->m_ba16EngineFlags & 1u) == 0) continue;
        CSGMovable* parent = static_cast<CSGMovable*>(ground->m_pParent);
        parent->ForceWorldMatrixUpdate();  // vt+0x50
        const CMatrix34* ltm = reinterpret_cast<const CMatrix34*>(&static_cast<CSGMovable*>(ground->m_pParent)->m_pRwFrame->ltm);
        Mat4_Invert(ground->m_pInvertedWorldMatrix, ltm);  // 0x0023f878
        const CMatrix34* ltm2 = reinterpret_cast<const CMatrix34*>(&static_cast<CSGMovable*>(ground->m_pParent)->m_pRwFrame->ltm);
        BBox_TransformByMatrix(reinterpret_cast<CBBox*>(ground->m_AABB), reinterpret_cast<const CBBox*>(ground->m_OBB), ltm2);  // 0x0023bce0
    }
    SetNavBlocking(1);  // 0x0041e578
    m_unk1AC = kVectorZero;
    m_unk1B8 = kVectorZero;
    m_unk1C4 = 0;
}
