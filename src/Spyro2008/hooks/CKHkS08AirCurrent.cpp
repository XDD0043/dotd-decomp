// CKHkS08AirCurrent.cpp - reconstructed original translation unit 0x4740f0-0x478940 (GAME_TOC1, main_toc1), 36 functions, 34 live.
// Primary class: CKHkS08AirCurrent  key 0x2b02  category Hook  size 0x130  vtable 0xb27918
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x4740f0  CKHkS08AirCurrent_Delete
//   [x] 0x474140  CKHkS08AirCurrent_Restart
//   [x] 0x474160  CKHkS08AirCurrent_MessageProc  (header)
//   [x] 0x4741b8  CKHkS08AirCurrent_GetInfo  (GetInfo, vt+0x40)
//   [x] 0x474208  CKHkS08AirCurrent_UpdateAlphaFlicker_maybe
//   [x] 0x474310  CKHkS08AirCurrent_SetFxIntensity_maybe
//   [x] 0x474470  CKHkS08AirCurrent_UpdateFlowFx_maybe
//   [x] 0x4748c0  CKHkS08AirCurrent_OnDeactivate
//   [x] 0x474928  CKHkS08AirCurrent_Resume  (empty / no effect: inherited)
//   [x] 0x474950  CKHkS08AirCurrent_Pause  (empty / no effect: inherited)
//   [x] 0x474978  CKHkS08AirCurrent_Stop  (inherited, empty)
//   [x] 0x4749a0  CKHkS08AirCurrent_Start
//   [x] 0x4749c8  CKHkS08AirCurrent_PostLoad
//   [ ] 0x474a20  CKHkS08AirCurrent_Save
//   [x] 0x474a48  CKHkS08AirCurrent_RecursiveRegistration  (inherited: CKHkActorBase's)
//   [x] 0x474a70  CKHkS08AirCurrent_Destroy
//   [x] 0x474ad0  CKHkS08AirCurrent_DeleteArray
//   [x] 0x474b70  CKHkS08AirCurrent_Construct  [dead]
//   [x] 0x474ba8  CKHkS08AirCurrent_DeletingDestructor  (the deleting form of the destructor)
//   [x] 0x474bf0  CKHkS08AirCurrent_Destructor  (header)
//   [x] 0x474c20  CKHkS08AirCurrent_BaseDestructor  (the destructor)
//   [ ] 0x474c50  RegisterCKHkS08AirCurrentClass
//   [ ] 0x474cd8  _GLOBAL__D_474cd8
//   [ ] 0x474ce8  _GLOBAL__I_474ce8
//   [ ] 0x474cf8  CKHkS08AirCurrent_Construct_2  [dead]
//   [x] 0x474d30  CKHkS08AirCurrent_vfC8
//   [x] 0x474d90  CKHkS08AirCurrent_SetDefaultState
//   [x] 0x474e58  CKHkS08AirCurrent_Create
//   [x] 0x474eb0  CKHkS08AirCurrent_CreateArray
//   [x] 0x474f60  CKHkS08AirCurrent_RemoveRecords_maybe
//   [x] 0x475278  CKHkS08AirCurrent_ClampPositionToTube_maybe  (ClampPositionToTube, wired in CKHkS08Hero_UpdateFlyingMovement_maybe)
//   [x] 0x4754a0  CKHkS08AirCurrent_AddRecords_maybe
//   [x] 0x476400  CKHkS08AirCurrent_vfCC
//   [x] 0x476438  CKHkS08AirCurrent_OnActivate
//   [x] 0x4765c0  CKHkS08AirCurrent_Update
//   [x] 0x4779e0  CKHkS08AirCurrent_Load
//
//   [ ] 0x9c46c8  CKHkS08AirCurrent_IsKindOfClass  [inline]
//   [ ] 0x9c4720  CKHkS08AirCurrent_GetClassType  [inline]
//   [ ] 0x9c4728  CKHkS08AirCurrent_GetClassID  [inline]
#include "Spyro2008/hooks/CKHkS08AirCurrent.h"

#include <cmath>
#include <cstring>

#include "Renderware/rwcore/RwCamera.h"
#include "Spyro2008/groups/IKGrpHero.h"
#include "Spyro2008/hooks/CKHkS08Hero.h"
#include "Spyro2008/logic/CKS08GameManager.h"
#include "crt/ppc_ops.h"
#include "crt/xatan.h"
#include "crt/xsinf.h"
#include "k2000/ai/CKHkDetectorGroup.h"
#include "k2000/cameras/CKSrvCamera.h"
#include "k2000/core/Stub.h"
#include "k2000/dictionaries/CKSoundDictionaryID.h"
#include "k2000/geometry/CGeometry.h"
#include "k2000/io/IKFile.h"
#include "k2000/logic/CMultiGeometryBasic.h"
#include "k2000/logic/cameras/CKCameraConstraint.h"
#include "k2000/logic/fx/CKAnimatedFxCollection.h"
#include "k2000/logic/math/CKSpline4L.h"
#include "k2000/logic/math/IKPath.h"
#include "k2000/logic/render/CMaterial.h"
#include "k2000/logic/sound/CKSound.h"
#include "k2000/math/Math.h"
#include "k2000/math/Vec3.h"
#include "k2000/memory/Mem.h"
#include "k2000/misc/Mat4.h"
#include "k2000/misc/ClassRegistry.h"
#include "k2000/misc/Engine.h"
#include "k2000/scenegraph/CFogBoxNodeFx.h"
#include "k2000/scenegraph/CNode.h"
#include "k2000/services/CTriggerStarter.h"
#include "k2000/system/IKTime.h"

// 0x004779e0 CKHkS08AirCurrent_Load
int32_t CKHkS08AirCurrent::Load(IKFile* file, int32_t type) {
    CKHkActorBase::Load(file, type);
    if (type != K_LEVEL_PLATEFORMS) return 1;
    IKFile_ReadRef(file, &m_pMultiGeometry);
    IKFile_ReadRef(file, &m_pSpline);
    for (float& f : m_vWindDir) ReadF32LE(file, &f);
    ReadF32LE(file, &m_fBaseStrength);
    ReadF32LE(file, &m_fTubeRadius);
    ReadF32LE(file, &m_fGustIntervalMax);
    ReadF32LE(file, &m_fGustIntervalMin);
    ReadF32LE(file, &m_fGustStrengthMin);
    ReadF32LE(file, &m_fGustStrengthMax);
    ReadF32LE(file, &m_fUnk5C);
    ReadF32LE(file, &m_fUnk60);
    for (float& f : m_afUnk68) ReadF32LE(file, &f);
    ReadF32LE(file, &m_fUnkC8);
    ReadF32LE(file, &m_fUnkCC);
    ReadU16LE(file, &m_ui16NbStreamNodes);
    if (m_ui16NbStreamNodes == 0) {
        m_aui8StreamNodeAlpha = nullptr;
        m_apStreamNodes = nullptr;
    } else {
        m_apStreamNodes = static_cast<IKSerializable**>(
            Mem_AllocAligned16(m_ui16NbStreamNodes * static_cast<uint32_t>(sizeof(IKSerializable*))));
        IKFile_ReadObjectRefArray(file, m_apStreamNodes, m_ui16NbStreamNodes);
        m_aui8StreamNodeAlpha = new uint8_t[m_ui16NbStreamNodes];  // OperatorNewArray
        ReadRaw(file, m_aui8StreamNodeAlpha, m_ui16NbStreamNodes);
    }
    IKFile_ReadRef(file, &m_pFlowNode);
    IKFile_ReadRef(file, &m_pFlickerNode);
    IKFile_ReadRef(file, &m_pSteadyNode);
    ReadU16LE(file, &m_unk38);
    IKFile_ReadRef(file, &m_pFogBoxA);
    ReadU16LE(file, &m_unk40);
    IKFile_ReadRef(file, &m_pFogBoxB);
    ReadF32LE(file, &m_fRecordHeightBase);
    ReadF32LE(file, &m_fUnk50);
    ReadF32LE(file, &m_fUnk54);
    ReadF32LE(file, &m_fUnk58);
    IKFile_ReadRef(file, &m_pDetectorGroup);
    ReadF32LE(file, &m_fPushRampTime);
    IKFile_ReadRef(file, &m_pCameraConstraint);
    ReadF32LE(file, &m_fUnkC0);
    ReadF32LE(file, &m_fUnkC4);
    ReadF32LE(file, &m_fUnk64);
    IKFile_ReadRef(file, &m_pMainAnimFx);
    ReadU8(file, &m_ui8NbFlowAnimFx);
    m_apFlowAnimFx = static_cast<IKSerializable**>(
        Mem_AllocAligned16(m_ui8NbFlowAnimFx * static_cast<uint32_t>(sizeof(IKSerializable*))));
    IKFile_ReadObjectRefArray(file, m_apFlowAnimFx, m_ui8NbFlowAnimFx);
    IKFile_ReadRef(file, &m_pSoundDico);
    return 1;
}

// 0x004749a0 CKHkS08AirCurrent_Start: the actor base's (empty) ResetRuntime 0x3f6e48.
void CKHkS08AirCurrent::Start() {}

// 0x00474d90 CKHkS08AirCurrent_SetDefaultState (after the empty base call KStub_Nop_3f72a0): bit 11 of the
// flags takes bit 3, always for flag 0, otherwise only when bit 5 is set.
void CKHkS08AirCurrent::SetDefaultState(int32_t flag) {
    if (flag != 0 && (m_bitArray & 0x20u) == 0) return;
    m_bitArray = (m_bitArray & 0xfffff7ffu) | (((m_bitArray >> 3) & 1u) << 11);
}

namespace {

// Rand_Int's low 16 bits over 65535 (fcfid, frsp, fdivs by TOC1 +0x5a34). A macro, so that the rand log names the caller.
#define AirRand01() (static_cast<float>(static_cast<uint16_t>(Rand_Int())) / 65535.0f)

// TOC1 +0x5ac4 (0xb8000080) and +0x5acc (pi / 180).
const float kRandScale = [] {
    const uint32_t bits = 0xb8000080u;
    float f;
    std::memcpy(&f, &bits, 4);
    return f;
}();
const float kDegToRad = 0x1.1df468p-6f;  // 0x3c8efa34

const CVector3 kAxisY = {0.0f, 1.0f, 0.0f};       // 0x00c50d40
const CVector3 kAxisZ = {0.0f, 0.0f, 1.0f};       // 0x00c50d4c
const CVector3 kVectorZero = {0.0f, 0.0f, 0.0f};  // 0x00c50d64

uint8_t AlphaByte(float alpha) { return static_cast<uint8_t>(ppc::fctiwz(alpha)); }

// 0x002ca0f8 CKGrpS08Hero_GetFocusedHero (local copy; CKGrpS08Hero.cpp, not ported there yet).
CKHkS08Hero* FocusedHeroOf(const IKGrpHero* group) {
    const int8_t index = static_cast<int8_t>(group->m_ui8FocusedDragon);
    if (index == -1) return nullptr;
    return static_cast<CKHkS08Hero*>(group->m_apHeros[index]);
}
// 0x002ca080 GetHeroByDragonIndex (local copy).
CKHkS08Hero* HeroAt(const IKGrpHero* group, uint32_t index) {
    return static_cast<CKHkS08Hero*>(group->m_apHeros[static_cast<uint8_t>(index)]);
}
// 0x00361968 CKHkS08Hero_GetPositionPtr (local copy; the same as CKHkDetectorGroup.cpp's).
const float* HeroPositionOf(CKHkS08Hero* hero) {
    if ((hero->m_bitArray & 2u) == 0 || ((hero->m_ui32StatusFlagsED4 >> 4) & 1u) != 0) return &hero->m_unk54c;
    return &FrameLtm(static_cast<CSGMovable*>(hero->m_pKGLObject)->m_pRwFrame)->pos.x;
}
// 0x00362af0 CKHkS08Hero_IsPlayerControlled: the hero is its own tracked leader.
bool IsPlayerControlled(const CKHkS08Hero* hero) { return hero->m_ui8Hero == hero->m_ui8TrackedLeader; }

// The sound of +0x48 (CKSoundDictionaryID_GetSound(0)), null without one.
CKSound* SoundOf(IKSerializable* dictionary) { return static_cast<CKSoundDictionaryID*>(dictionary)->GetSound(0); }

// The game manager's record of a hero (+0xdf8 + hero * 0x20; CKHkS08Hero_2.cpp's layout): the push (words 0-2), the
// pull (words 3-5), two bytes in word 6 (+0xe10 / +0xe11) and the air current (word 7, +0xe14).
uint32_t* WindRecord(uint32_t hero) {
    CKS08GameManager* manager = static_cast<CKS08GameManager*>(g_pEngine->m_gameManager);
    return &manager->m_unkDF4[1 + (hero & 0xffu) * 8u];
}
void AddToRecord(uint32_t* record, uint32_t word, float x, float y, float z) {
    float v[3];
    std::memcpy(v, &record[word], 12);
    v[0] = x + v[0];
    v[1] = y + v[1];
    v[2] = z + v[2];
    std::memcpy(&record[word], v, 12);
}

// The game's inlined cosf / sinf with the library call for a negative argument (the sign bit tested as an integer).
bool SignBit(float x) {
    int32_t bits;
    std::memcpy(&bits, &x, 4);
    return bits < 0;
}
float GameCos(float x) { return SignBit(x) ? crt::LibCosf(-x) : crt::InlineCosf(x); }
float GameSin(float x) { return SignBit(x) ? -crt::LibSinf(-x) : crt::InlineSinf(x); }

// The box test of a CMultiGeometryBasic shape 0 (+0x04: max x, y, z, min x, y, z), inlined.
bool InBox(const CMultiGeometryBasic* shape, float x, float y, float z) {
    const float* s = shape->m_afShape;
    return s[3] <= x && s[0] >= x && s[5] <= z && s[2] >= z && s[4] <= y && y <= s[1];
}
// 0x002441e8 Vec3_IsWithinRadius_maybe (local copy; k2000/math/Vec3.cpp, not ported there yet): each axis distance at
// most `extent`, then the squared distance (fmuls, fmadds, fmadds) at most `radiusSquared`.
bool IsWithinRadius(float extent, float radiusSquared, const float* center, const float* point) {
    const float dx = std::fabs(center[0] - point[0]);
    if (!(dx <= extent)) return false;
    const float dz = std::fabs(center[2] - point[2]);
    if (!(dz <= extent)) return false;
    const float dy = std::fabs(center[1] - point[1]);
    if (!(dy <= extent)) return false;
    return ppc::fmadds(dz, dz, ppc::fmadds(dx, dx, dy * dy)) <= radiusSquared;
}

}  // namespace

// 0x004749c8 CKHkS08AirCurrent_PostLoad
int32_t CKHkS08AirCurrent::PostLoad(int32_t type) {
    CKHkActorBase::PostLoad(type);  // 0x3f6e70
    if (type == 0) {
        m_fIntensityB = 1.0f;  // TOC1 +0x5a54
        m_fIntensityA = 1.0f;
    }
    return 1;
}

// 0x00474140 CKHkS08AirCurrent_Restart
void CKHkS08AirCurrent::Restart() {
    if ((m_bitArray & 4u) != 0) return;
    m_fTimeInside = 0.0f;
}

// 0x00474d30 CKHkS08AirCurrent_vfC8
void CKHkS08AirCurrent::ApplyStatePreset(int32_t state) {
    const uint32_t on = state == 0 ? (m_bitArray & 8u) : (m_bitArray & 0x10u);
    if (on != 0) {
        m_bitArray = (m_bitArray & 0xfffff7ffu) | 0x800u;
    } else {
        m_bitArray &= 0xfffff7ffu;
    }
}

// 0x00476400 CKHkS08AirCurrent_vfCC
void CKHkS08AirCurrent::SetEnabled(int32_t enabled) {
    m_bitArray = (m_bitArray & 0xfffff7ffu) | (static_cast<uint32_t>(enabled) << 11);
    if (enabled != 0) {
        AddRecords();
    } else {
        RemoveRecords();
    }
}

namespace {

// The record step inlined at each of AddRecords' four sites: the fog box's box with the record id `id` (searched from the
// last active box down) gets its scale (+0x08) back to 1 and keeps its particles; without one, while a box is left, the
// next box becomes the record (its matrix the identity, the id, scale 1, one more active box) and its emitter particles
// are randomised. Either way the box takes the record's matrix (all 0x40 bytes, the pad words included).
void PlaceRecord(CFogBoxNodeFx* fog, uint32_t id, const CMatrix34& m) {
    const uint32_t active = fog->m_unk40;
    int32_t index = static_cast<int32_t>(active) - 1;
    for (; index >= 0; --index) {
        if (fog->m_aBoxes[index].m_unk04 == id) break;
    }
    int32_t isNew = 0;
    if (index >= 0) {
        fog->m_aBoxes[index].m_unk08 = 1.0f;  // TOC1 +0x5a54
    } else {
        if (fog->m_ui32NbBoxes == active) return;
        CMatrix34* box = fog->m_aBoxes[active].m_pMatrix;
        box->m_right = {1.0f, 0.0f, 0.0f};
        box->m_ui32Flags = 0x20003u;
        box->m_up = {0.0f, 1.0f, 0.0f};
        box->m_at = {0.0f, 0.0f, 1.0f};
        box->m_pos = {0.0f, 0.0f, 0.0f};
        fog->m_aBoxes[fog->m_unk40].m_unk04 = id;
        fog->m_aBoxes[fog->m_unk40].m_unk08 = 1.0f;
        fog->m_unk40 = fog->m_unk40 + 1;
        isNew = 1;
        index = static_cast<int32_t>(active);
    }
    std::memcpy(fog->m_aBoxes[index].m_pMatrix, &m, sizeof(CMatrix34));
    fog->RandomizeEmitterParticles(isNew, static_cast<uint32_t>(index));  // 0x000da968
}

// The record removal inlined in RemoveRecords: the box with the id (searched from the last active box down) leaves the
// active ones; the last active box's matrix and id move into its slot (not its scale), and the freed last slot's id is 0.
void RemoveRecord(CFogBoxNodeFx* fog, uint32_t id) {
    const uint32_t active = fog->m_unk40;
    int32_t index = static_cast<int32_t>(active) - 1;
    for (; index >= 0; --index) {
        if (fog->m_aBoxes[index].m_unk04 == id) break;
    }
    if (index < 0) return;
    const uint32_t last = active - 1;
    fog->m_unk40 = last;
    if (static_cast<uint32_t>(index) != last) {
        std::memcpy(fog->m_aBoxes[index].m_pMatrix, fog->m_aBoxes[last].m_pMatrix, sizeof(CMatrix34));
        fog->m_aBoxes[index].m_unk04 = fog->m_aBoxes[last].m_unk04;
    }
    fog->m_aBoxes[fog->m_unk40].m_unk04 = 0;
}

// The grid of one record set in the shape (rows `a` = the count's square root, rounded up when the rows times the
// columns `b` = count / root miss some): 3 rand draws per record, inside its cell, jittered by +0x50 (x, z) and placed at
// +0x4c plus +0x54 times a draw in height.
#define AirRandSigned() ppc::fmadds(static_cast<float>(static_cast<uint16_t>(Rand_Int())), kRandScale, 1.0f)

}  // namespace

// 0x004754a0 CKHkS08AirCurrent_AddRecords_maybe: the fog boxes' records (+0x3c: +0x38 of them, +0x44: +0x40). With a
// spline (+0x98) the records sit at even distances along it, turned to its direction; otherwise in a grid over the shape
// (+0x94), turned to the wind (rand draws).
void CKHkS08AirCurrent::AddRecords() {
    // BUG(original): the record matrix is a stack matrix that is only written when Mat4_SetBasisFromAtUp writes it (its
    // pad words never): a vertical direction leaves the previous record's axes (the first time, stack garbage).
    CMatrix34 m;
    std::memset(&m, 0, sizeof m);
    CVector3 point;      // sp+0x70
    CVector3 direction;  // sp+0x7c
    if (m_pSpline != nullptr) {
        IKPath* spline = static_cast<IKPath*>(m_pSpline);
        const float length = spline->GetLength();  // vt+0x5c
        struct Set {
            uint16_t count;
            IKSerializable* fog;
        };
        const Set sets[2] = {{m_unk38, m_pFogBoxA}, {m_unk40, m_pFogBoxB}};
        for (const Set& set : sets) {
            const uint16_t count = set.count;
            if (count == 0) continue;
            const float step = length / static_cast<float>(static_cast<int32_t>(count));
            for (int32_t i = 0; i < static_cast<int32_t>(count); ++i) {
                spline->GetPointAtDistance(step * static_cast<float>(i), &point, &direction);  // vt+0x54
                m.m_pos = point;
                m.m_ui32Flags &= 0xfffdffffu;
                Mat4_SetBasisFromAtUp(&m, &direction, &kAxisY);  // 0x0023fd30 (TOC1 +0x5a44: 0x00c50d40)
                if (set.fog != nullptr) PlaceRecord(static_cast<CFogBoxNodeFx*>(set.fog), static_cast<uint32_t>(i + 1), m);
            }
        }
        return;
    }
    if (m_pMultiGeometry == nullptr) return;
    direction = {m_afWind[0], m_afWind[1], m_afWind[2]};
    const float windLength = std::sqrt(ppc::fmadds(direction.z, direction.z,
                                                   ppc::fmadds(direction.x, direction.x, direction.y * direction.y)));  // 0x00010690
    if (windLength != 0.0f) {
        const float inverse = 1.0f / windLength;
        direction.z = direction.z * inverse;
        direction.x = direction.x * inverse;
        direction.y = direction.y * inverse;
    }
    const CMultiGeometryBasic* shape = static_cast<const CMultiGeometryBasic*>(m_pMultiGeometry);
    const float* s = shape->m_afShape;
    const float halfX = (s[0] - s[3]) * 0.5f;  // TOC1 +0x5a3c
    const float halfZ = (s[2] - s[5]) * 0.5f;
    const float centerX = (s[0] + s[3]) * 0.5f;
    const float centerY = (s[1] + s[4]) * 0.5f;
    const float centerZ = (s[2] + s[5]) * 0.5f;
    // The first grid's size (computed before the matrix).
    uint32_t rows = 0;
    uint32_t cols = 0;
    uint32_t colsFull = 0;
    auto gridOf = [](uint32_t count, uint32_t* a, uint32_t* b, uint32_t* full) {
        const int32_t root = ppc::fctiwz(std::sqrt(static_cast<float>(static_cast<int32_t>(count))));  // fsqrts
        *a = static_cast<uint32_t>(root) & 0xffu;
        *full = static_cast<uint32_t>(ppc::divw(static_cast<int32_t>(count), static_cast<int32_t>(*a)));
        *b = *full & 0xffu;
        if (static_cast<int32_t>(*a * *b) < static_cast<int32_t>(count)) *a = static_cast<uint32_t>(root + 1) & 0xffu;
    };
    if (m_unk38 != 0) gridOf(m_unk38, &rows, &cols, &colsFull);
    if (static_cast<uint8_t>(Mat4_SetBasisFromAtUp(&m, &direction, &kAxisY)) == 0) {
        Mat4_SetBasisFromAtUp(&m, &direction, &kAxisZ);  // TOC1 +0x5ac0: 0x00c50d4c
    }
    // One record of a grid cell: 3 rand draws.
    auto cell = [&](uint32_t i, uint32_t j, uint32_t a, uint32_t b) {
        const float u1 = AirRandSigned();
        const float x0 = ((halfX * (static_cast<float>(static_cast<int32_t>((i & 0xffu) << 1)) + 1.0f)) /
                          static_cast<float>(static_cast<int32_t>(a))) - halfX;
        float x = ppc::fmadds(u1, m_fUnk50, x0);
        const float u2 = AirRandSigned();
        const float base = m_fRecordHeightBase;
        x = centerX + x;
        const float z0 = (ppc::fmadds(static_cast<float>(static_cast<int32_t>((j << 1) & 0x1feu)), halfZ, halfZ) /
                          static_cast<float>(static_cast<int32_t>(b))) - halfZ;
        float z = ppc::fmadds(u2, m_fUnk50, z0);
        const float u3 = AirRandSigned();
        z = centerZ + z;
        const float y = centerY + ppc::fmadds(u3, m_fUnk54, base);
        m.m_pos.x = x;
        m.m_pos.z = z;
        m.m_pos.y = y;
        m.m_ui32Flags &= 0xfffdffffu;
    };
    for (uint32_t i = 0; rows != 0;) {
        if (cols != 0) {
            for (uint32_t j = 0;;) {
                const uint32_t index = rows * (i & 0xffu) + (j & 0xffu);
                if (static_cast<int32_t>(index) < static_cast<int32_t>(m_unk38)) {
                    cell(i, j, rows, cols);
                    PlaceRecord(static_cast<CFogBoxNodeFx*>(m_pFogBoxA), index + 1, m);
                }
                ++j;
                if (cols == (j & 0xffu)) break;
            }
        }
        ++i;
        if (rows == (i & 0xffu)) break;
    }
    if (m_unk40 == 0) return;
    gridOf(m_unk40, &rows, &cols, &colsFull);
    for (uint32_t i = 0; rows != 0;) {
        if (cols != 0) {
            for (uint32_t j = 0;;) {
                const uint32_t index = (j & 0xffu) + rows * (i & 0xffu);
                if (static_cast<int32_t>(index) < static_cast<int32_t>(m_unk40)) {
                    cell(i, j, rows, cols);
                    PlaceRecord(static_cast<CFogBoxNodeFx*>(m_pFogBoxB), index + 1, m);
                }
                ++j;
                if (((colsFull - 1) & 0xffu) + 1 == j) break;
            }
        }
        ++i;
        if (rows == (i & 0xffu)) break;
    }
}

// 0x00474f60 CKHkS08AirCurrent_RemoveRecords_maybe: the records of both fog boxes removed (no null test on +0x44).
void CKHkS08AirCurrent::RemoveRecords() {
    for (int32_t i = 0; i < static_cast<int32_t>(m_unk38); ++i) {
        if (m_pFogBoxA != nullptr) RemoveRecord(static_cast<CFogBoxNodeFx*>(m_pFogBoxA), static_cast<uint32_t>(i + 1));
    }
    for (int32_t i = 0; i < static_cast<int32_t>(m_unk40); ++i) {
        RemoveRecord(static_cast<CFogBoxNodeFx*>(m_pFogBoxB), static_cast<uint32_t>(i + 1));
    }
}

// 0x00474310 CKHkS08AirCurrent_SetFxIntensity_maybe
void CKHkS08AirCurrent::SetFxIntensity(float a, float b) {
    if (m_pFlickerNode != nullptr) SceneNode_SetAlphaRecursive(m_pFlickerNode, AlphaByte(a * m_fAlpha), 1);
    if (m_pSteadyNode != nullptr) SceneNode_SetAlphaRecursive(m_pSteadyNode, AlphaByte(a * 255.0f), 1);
    for (int32_t i = 0; i < static_cast<int32_t>(m_ui16NbStreamNodes); ++i) {
        SceneNode_SetAlphaRecursive(m_apStreamNodes[i], AlphaByte(b * static_cast<float>(m_aui8StreamNodeAlpha[i])), 1);
    }
    if (m_pFlowNode != nullptr) SceneNode_SetAlphaRecursive(m_pFlowNode, AlphaByte(b * m_fFlowAlpha), 1);
}

// 0x00474208 CKHkS08AirCurrent_UpdateAlphaFlicker_maybe
void CKHkS08AirCurrent::UpdateAlphaFlicker(float dt) {
    if (m_pFlickerNode == nullptr) return;
    float alpha = m_fAlpha;
    float target = m_fAlphaTarget;
    if (alpha == target) {
        target = ppc::fmadds(AirRand01(), m_afUnk68[(0x8c - 0x68) / 4] - m_afUnk68[(0x88 - 0x68) / 4], m_afUnk68[(0x88 - 0x68) / 4]);
        m_fAlphaTarget = target;
        alpha = m_fAlpha;
    }
    const float speed = m_afUnk68[(0x90 - 0x68) / 4];
    if (target < alpha) {
        const float next = alpha - dt * speed;
        m_fAlpha = next;
        if (!(next >= target)) m_fAlpha = target;
    } else {
        const float next = ppc::fmadds(dt, speed, alpha);
        m_fAlpha = next;
        if (next > target) m_fAlpha = target;
    }
    if (m_pFlickerNode != nullptr) SceneNode_SetAlphaRecursive(m_pFlickerNode, AlphaByte(m_fAlpha), 1);
}

// 0x00474470 CKHkS08AirCurrent_UpdateFlowFx_maybe
void CKHkS08AirCurrent::UpdateFlowFx(float dt) {
    IKPath* spline = static_cast<IKPath*>(m_pSpline);
    if (spline == nullptr) return;
    const float timer = m_fFlowTimer - dt;
    m_fFlowTimer = timer;
    CSGMovable* flow = static_cast<CSGMovable*>(m_pFlowNode);
    if (flow != nullptr) {
        const float* r = m_afUnk68;  // +0x68: index (offset - 0x68) / 4
        float distance;
        if (timer <= 0.0f) {
            // A new run: its duration, speed, fade-in and fade-out times, start and angle (6 rand draws).
            m_fFlowTimer = ppc::fmadds(AirRand01(), r[5] - r[4], r[4]);      // +0x7c / +0x78
            m_fFlowSpeed = ppc::fmadds(AirRand01(), r[7] - r[6], r[6]);      // +0x84 / +0x80
            m_fFlowFadeIn = ppc::fmadds(AirRand01(), r[1] - r[0], r[0]);     // +0x6c / +0x68
            m_fFlowFadeOut = ppc::fmadds(AirRand01(), r[3] - r[2], r[2]);    // +0x74 / +0x70
            const float u = AirRand01();
            const float length = spline->GetLength();  // vt+0x5c
            float start = (length - m_fFlowTimer * m_fFlowSpeed) - 0.5f;
            start = u * start;
            m_fFlowDistance = start;
            if (start < 0.0f) m_fFlowDistance = 0.0f;
            m_fFlowFadeInTotal = m_fFlowFadeIn;
            m_fFlowAlpha = 0.0f;
            m_fFlowAngle = AirRand01() * 360.0f;  // TOC1 +0x5a40
            distance = m_fFlowDistance;
        } else {
            distance = ppc::fmadds(dt, m_fFlowSpeed, m_fFlowDistance);
            m_fFlowDistance = distance;
        }
        CVector3 position;
        CVector3 direction;
        spline->GetPointAtDistance(distance, &position, &direction);  // vt+0x54
        RwFrame* frame = flow->m_pRwFrame;
        frame->modelling.pos.z = position.z;
        frame->modelling.pos.x = position.x;
        frame->modelling.pos.y = position.y;
        frame->modelling.flags &= 0xfffdffffu;
        RwFrame_MarkDirty(flow->m_pRwFrame);
        flow->SetBasisFromUpAndForward(&direction, &kAxisY);
        flow->RotateAboutPoint(m_fFlowAngle, &position, &direction);
        const float scale = m_fUnk5C * 1.2f;  // TOC1 +0x5a48
        flow->ScaleXYZ(scale, scale, scale);
        if (!(m_fFlowFadeIn <= 0.0f)) {
            float left = m_fFlowFadeIn - dt;
            m_fFlowFadeIn = left;
            if (left < 0.0f) {
                left = 0.0f;
                m_fFlowFadeIn = 0.0f;
            }
            m_fFlowAlpha = (left * -255.0f) / m_fFlowFadeInTotal + 255.0f;
        } else if (!(m_fFlowTimer >= m_fFlowFadeOut)) {
            m_fFlowAlpha = (m_fFlowTimer * 255.0f) / m_fFlowFadeOut;
        }
        SceneNode_SetAlphaRecursive(flow, AlphaByte(m_fFlowAlpha), 1);
    }
    if (m_ui8NbFlowAnimFx == 0 || m_ui16NbStreamNodes == 0) return;
    for (int32_t i = 0; i < static_cast<int32_t>(m_ui8NbFlowAnimFx); ++i) {
        CKAnimatedFxCollection* collection = static_cast<CKAnimatedFxCollection*>(m_apFlowAnimFx[i]);
        if (collection->m_bPlaying != 0) {
            collection->Update(dt);
        } else {
            const uint32_t index = (static_cast<uint32_t>(static_cast<uint16_t>(Rand_Int())) * m_ui16NbStreamNodes) >> 16;
            collection->PlayWithOwnRigs(static_cast<CSGLeaf*>(m_apStreamNodes[index]), nullptr);
        }
    }
}

// 0x00476438 CKHkS08AirCurrent_OnActivate
void CKHkS08AirCurrent::VfA0() {
    CKHkActorBase::VfA0();  // 0x003f7338 the active actor list
    const float strength = m_fBaseStrength;
    m_fStrength = strength;
    m_afWind[0] = strength * m_vWindDir[0];
    m_afWind[2] = strength * m_vWindDir[2];
    m_afWind[1] = strength * m_vWindDir[1];
    const float u = AirRand01();
    m_fFlowTimer = 0.0f;
    m_fTimeInside = 0.0f;
    m_fAlphaTarget = m_afUnk68[(0x88 - 0x68) / 4];
    m_fAlpha = m_afUnk68[(0x88 - 0x68) / 4];
    m_fGustTimer = ppc::fmadds(u, m_fGustIntervalMax - m_fGustIntervalMin, m_fGustIntervalMin);
    if ((m_bitArray & 0x800u) == 0) {
        m_fIntensityB = 0.0f;
        m_fIntensityA = 0.0f;
        SetFxIntensity(0.0f, 0.0f);
        RemoveRecords();
        return;
    }
    m_fIntensityB = 0.0f;
    m_fIntensityA = 1.0f;
    SetFxIntensity(1.0f, 0.0f);
    AddRecords();
    if (m_pMainAnimFx == nullptr) return;
    IKSerializable* owner = m_pFlickerNode;
    if (owner == nullptr) {
        if (m_ui16NbStreamNodes == 0) return;
        owner = m_apStreamNodes[0];
    }
    static_cast<CKAnimatedFxCollection*>(m_pMainAnimFx)->PlayWithOwnRigs(static_cast<CSGLeaf*>(owner), nullptr);
}

// 0x004748c0 CKHkS08AirCurrent_OnDeactivate
void CKHkS08AirCurrent::VfA4() {
    CKHkActorBase::VfA4();  // 0x003f7370
    if (SoundOf(m_pSoundDico) != nullptr) SoundOf(m_pSoundDico)->Stop(0);
}

// 0x004765c0 CKHkS08AirCurrent_Update
void CKHkS08AirCurrent::Update(IKTime* frameClock) {
    // 0x3f6e68 WorldObjectBase_Update_Nop
    const float dt = frameClock->m_afDeltaTime[0];
    IKGrpHero* group = static_cast<IKGrpHero*>(g_pEngine->m_gameManager->m_unk04[1]);  // the game manager's +0x08
    UpdateFlowFx(dt);
    UpdateAlphaFlicker(dt);  // inlined
    if (m_pMainAnimFx != nullptr) static_cast<CKAnimatedFxCollection*>(m_pMainAnimFx)->Update(frameClock->m_afDeltaTime[0]);
    const int8_t mode = static_cast<int8_t>(FocusedHeroOf(group)->GetMovementMode());  // 0x32a6c0 (the thunk)
    // The sound loops while the current is on, except while a hero inside flies.
    if ((m_bitArray & 0x800u) == 0 || (!(m_fTimeInside <= 0.0f) && mode == 1)) {
        if (SoundOf(m_pSoundDico) != nullptr) SoundOf(m_pSoundDico)->Stop(0);
    } else if (SoundOf(m_pSoundDico) != nullptr && SoundOf(m_pSoundDico)->m_pInstances == nullptr) {
        SoundOf(m_pSoundDico)->SetLoop(1);
        SoundOf(m_pSoundDico)->Play(0.0f);
    }
    // The FX intensities fade in / out (1 per second).
    const float a = m_fIntensityA;
    const float b = m_fIntensityB;
    float nextA;
    float nextB;
    if ((m_bitArray & 0x800u) == 0) {
        nextA = a - dt;
        if (nextA < 0.0f) nextA = 0.0f;
        nextB = b - dt;
        if (nextB < 0.0f) nextB = 0.0f;
    } else {
        nextA = dt + a;
        if (!(nextA <= 1.0f)) nextA = 1.0f;
        if (!(m_fTimeInside <= 0.0f) || (m_bitArray & 0x400u) != 0) {
            nextB = dt + b;
            if (!(nextB <= 1.0f)) nextB = 1.0f;
        } else {
            nextB = b - dt;
            if (!(nextB >= 0.0f)) nextB = 0.0f;
        }
    }
    if (nextA != a || nextB != b) {
        m_fIntensityA = nextA;
        m_fIntensityB = nextB;
        SetFxIntensity(nextA, nextB);
    }
    CKCameraConstraint* constraint = static_cast<CKCameraConstraint*>(m_pCameraConstraint);
    if (constraint != nullptr && (m_bitArray & 0x80u) == 0) constraint->m_unk1c &= 0xfbu;
    if (group == nullptr || (m_bitArray & 0x800u) == 0) {
        if (constraint != nullptr) constraint->m_unk1c &= 0xfbu;
        return;
    }
    if (m_fGustTimer > 0.0f) {
        const float left = m_fGustTimer - dt;
        m_fGustTimer = left;
        if (left <= 0.0f) {
            // A gust: the next one's time, its strength and a direction turned at random around +0x9c (4 rand draws).
            m_fGustTimer = ppc::fmadds(AirRand01(), m_fGustIntervalMax - m_fGustIntervalMin, m_fGustIntervalMin);
            const float gust = ppc::fmadds(AirRand01(), m_fGustStrengthMax - m_fGustStrengthMin, m_fGustStrengthMin);
            const float yaw0 = Vec3_GetYawAngleFromZ(reinterpret_cast<const CVector3*>(m_vWindDir));
            const float pitch0 = crt::Asinf(m_vWindDir[1]);
            const float r1 = static_cast<float>(static_cast<uint16_t>(Rand_Int()));
            const float yaw = ppc::fmadds(ppc::fmadds(r1, kRandScale, 1.0f), m_fUnkC0 * kDegToRad, yaw0);
            const float r2 = static_cast<float>(static_cast<uint16_t>(Rand_Int()));
            const float pitch = ppc::fmadds(ppc::fmadds(r2, kRandScale, 1.0f), m_fUnkC4 * kDegToRad, pitch0);
            const float cosPitch = GameCos(pitch);
            m_afWind[2] = cosPitch * GameCos(yaw);
            m_afWind[1] = GameSin(pitch);
            const float cosPitch2 = GameCos(pitch);
            m_afWind[0] = cosPitch2 * GameSin(yaw);
            m_afWind[0] = gust * m_afWind[0];
            m_afWind[1] = gust * m_afWind[1];
            m_afWind[2] = gust * m_afWind[2];
        }
    }
    bool anyInside = false;
    uint8_t playerInside = 0;
    for (uint32_t i = 0; static_cast<int32_t>(group->GetHeroCount()) > static_cast<int32_t>(i); ++i) {  // vt+0xf4 every pass
        CKHkS08Hero* hero = HeroAt(group, i);
        const float* p = HeroPositionOf(hero);
        const float point[3] = {p[0], p[1], p[2]};
        const CMultiGeometryBasic* shape = static_cast<const CMultiGeometryBasic*>(m_pMultiGeometry);
        IKPath* spline = static_cast<IKPath*>(m_pSpline);
        uint32_t* record = WindRecord(i);
        auto markRecord = [&]() {
            uint8_t* bytes = reinterpret_cast<uint8_t*>(&record[6]);
            bytes[0] = static_cast<uint8_t>((bytes[0] | ((m_bitArray >> 8) & 1u)) != 0 ? 1 : 0);  // +0xe10
            bytes[1] = static_cast<uint8_t>((bytes[1] | ((m_bitArray >> 9) & 1u)) != 0 ? 1 : 0);  // +0xe11
        };
        if (spline != nullptr) {
            const uint32_t type = shape->m_baData & 3u;
            bool inside = false;
            if (type == 0) {
                inside = InBox(shape, point[0], point[1], point[2]);
            } else if (type == 1) {
                inside = IsWithinRadius(shape->m_afShape[3], shape->m_afShape[4], shape->m_afShape, point);
            }
            CVector3 onSpline;
            CVector3 tangent;
            if (inside) {
                const float along = spline->GetClosestDistanceAlong(reinterpret_cast<const CVector3*>(point), 1);  // vt+0x58
                spline->GetPointAtDistance(along, &onSpline, &tangent);  // vt+0x54
                const float dy = onSpline.y - point[1];
                const float dx = onSpline.x - point[0];
                const float dz = onSpline.z - point[2];
                const float distanceSquared = ppc::fmadds(dz, dz, ppc::fmadds(dx, dx, dy * dy));
                if (!(m_fTubeRadius * m_fTubeRadius <= distanceSquared)) {
                    // Inside the tube: pushed along the spline, pulled toward it.
                    if (IsPlayerControlled(HeroAt(group, i))) playerInside = 1;
                    float tx = tangent.x * m_fStrength;
                    float tz = tangent.z * m_fStrength;
                    float ty = tangent.y * m_fStrength;
                    float px = kVectorZero.x;
                    float py = kVectorZero.y;
                    float pz = kVectorZero.z;
                    const float pullFrom = spline->GetLength() - m_fTubeRadius;  // vt+0x5c
                    if (!(pullFrom <= along) && m_fUnkC8 != 0.0f && !(m_fUnkCC * m_fUnkCC >= distanceSquared)) {
                        px = (onSpline.x - point[0]) * m_fUnkC8;
                        py = (onSpline.y - point[1]) * m_fUnkC8;
                        pz = (onSpline.z - point[2]) * m_fUnkC8;
                    }
                    if (!(m_fTimeInside >= m_fPushRampTime)) {
                        const float ramp = m_fTimeInside / m_fPushRampTime;
                        tz = tz * ramp;
                        tx = tx * ramp;
                        ty = ty * ramp;
                    }
                    AddToRecord(record, 0, tx, ty, tz);
                    AddToRecord(record, 3, px, py, pz);
                    markRecord();
                    anyInside = true;
                    if ((m_bitArray & 0x40u) != 0) record[7] = static_cast<uint32_t>(reinterpret_cast<uintptr_t>(this));
                } else if (HeroAt(group, i) == FocusedHeroOf(group) && SoundOf(m_pSoundDico) != nullptr) {
                    SoundOf(m_pSoundDico)->SetPosition(&onSpline);
                }
            } else if (SoundOf(m_pSoundDico) != nullptr && SoundOf(m_pSoundDico)->GetSample() != nullptr &&
                       HeroAt(group, i) == FocusedHeroOf(group)) {
                // The sound follows the focused hero's closest point on the spline.
                const float along = spline->GetClosestDistanceAlong(reinterpret_cast<const CVector3*>(point), 1);
                spline->GetPointAtDistance(along, &onSpline, &tangent);
                SoundOf(m_pSoundDico)->SetPosition(&onSpline);
            }
            // The +0x24 nodes turn about their up axis.
            for (int32_t k = 0; k < static_cast<int32_t>(m_ui16NbStreamNodes); ++k) {
                CSGMovable* node = static_cast<CSGMovable*>(m_apStreamNodes[k]);
                node->RotateInPlace(&node->m_pRwFrame->modelling.up.x, m_fUnk64 * frameClock->m_afDeltaTime[0]);
            }
            continue;
        }
        // No spline: the shape (or the detector group) holds the hero, pushed by the wind vector.
        bool inside = false;
        if (shape == nullptr) {
            CKHkDetectorGroup* detector = static_cast<CKHkDetectorGroup*>(m_pDetectorGroup);
            if (detector == nullptr) {
                inside = true;  // no shape and no detector: every hero
            } else {
                inside = detector->IsTriggered(point) != 0;  // vt+0xc4
            }
        } else {
            const uint32_t type = shape->m_baData & 3u;
            if (type == 0) {
                inside = InBox(shape, point[0], point[1], point[2]);
            } else if (type == 1) {
                inside = IsWithinRadius(shape->m_afShape[3], shape->m_afShape[4], shape->m_afShape, point);
            }
            if (!inside && m_pDetectorGroup != nullptr) inside = static_cast<CKHkDetectorGroup*>(m_pDetectorGroup)->IsTriggered(point) != 0;
        }
        if (!inside) continue;
        bool rampOnlyWhenBelow = false;
        if (IsPlayerControlled(HeroAt(group, i))) {
            playerInside = 1;
        } else if (shape != nullptr || m_pDetectorGroup != nullptr) {
            rampOnlyWhenBelow = true;
        }
        float wx = m_afWind[0];
        float wy = m_afWind[1];
        float wz = m_afWind[2];
        // The ramp: below +0xd4 (an unordered time ramps too, except for a hero not player-controlled in the shape or
        // the detector: blt there, bge elsewhere).
        if (rampOnlyWhenBelow ? (m_fTimeInside < m_fPushRampTime) : !(m_fTimeInside >= m_fPushRampTime)) {
            const float ramp = m_fTimeInside / m_fPushRampTime;
            wz = wz * ramp;
            wx = wx * ramp;
            wy = wy * ramp;
        }
        AddToRecord(record, 0, wx, wy, wz);
        AddToRecord(record, 3, kVectorZero.x, kVectorZero.y, kVectorZero.z);
        markRecord();
        anyInside = true;
    }
    if (anyInside) {
        m_fTimeInside = m_fTimeInside + frameClock->m_afDeltaTime[0];
    } else {
        m_fTimeInside = 0.0f;
    }
    if (constraint == nullptr) return;
    constraint->m_unk1c = static_cast<uint8_t>((constraint->m_unk1c & 0xfbu) | (playerInside << 2));
    if ((m_bitArray & 0x80u) == 0) return;
    // The camera constraint follows the player inside: entered (its +0x28 signals) or left (+0x30).
    CKSrvCamera* camera = static_cast<CKSrvCamera*>(g_pEngine->m_srvCamera);
    CKCameraConstraint* active = camera->m_pActiveConstraint;
    const uint8_t isActive = constraint == active ? 1 : 0;
    if (playerInside == isActive) return;
    if (playerInside == 0) {
        if (isActive == 0) return;
        if (active != nullptr) QueueTriggerSignals(&active->m_tsUnk30);
        camera->m_pActiveConstraint = nullptr;
        QueueTriggerSignals(&constraint->m_tsUnk30);
        return;
    }
    if (active != nullptr) QueueTriggerSignals(&active->m_tsUnk30);
    camera->m_pActiveConstraint = constraint;
    QueueTriggerSignals(&constraint->m_tsUnk28);
    std::memcpy(&constraint->m_unk74, &constraint->m_afUnk44[10], sizeof(uint32_t));  // +0x74 = +0x6c
    constraint->m_unk9c = (constraint->m_unk9c & 0x00ffffffu) | 0xff000000u;           // the byte at +0x9c = 0xff
}

// 0x00474a70 CKHkS08AirCurrent_Destroy
void CKHkS08AirCurrent::Destroy() {
    Mem_FreeAligned16(m_apStreamNodes);
    if (m_aui8StreamNodeAlpha != nullptr) delete[] m_aui8StreamNodeAlpha;
    Mem_FreeAligned16(m_apFlowAnimFx);
}

// ==== P14 ===========================================================================================================
#include <algorithm>
#include <vector>

namespace {
// DOTD (x64): the live air currents, for FromRecordWord.
std::vector<CKHkS08AirCurrent*>& LiveAirCurrents() {
    static std::vector<CKHkS08AirCurrent*> live;
    return live;
}
}  // namespace

// 0x00474b70 CKHkS08AirCurrent_Construct (inlined in 0x00474e58 CKHkS08AirCurrent_Create): the base's only.
CKHkS08AirCurrent::CKHkS08AirCurrent() { LiveAirCurrents().push_back(this); }  // DOTD: the registry

// 0x00474bf0 CKHkS08AirCurrent_Destructor
CKHkS08AirCurrent::~CKHkS08AirCurrent() {
    std::vector<CKHkS08AirCurrent*>& live = LiveAirCurrents();
    live.erase(std::remove(live.begin(), live.end(), this), live.end());  // DOTD: the registry
}

CKHkS08AirCurrent* CKHkS08AirCurrent::FromRecordWord(uint32_t word) {
    if (word == 0) return nullptr;
    for (CKHkS08AirCurrent* current : LiveAirCurrents()) {
        if (static_cast<uint32_t>(reinterpret_cast<uintptr_t>(current)) == word) return current;
    }
    return nullptr;
}

// 0x00475278 CKHkS08AirCurrent_ClampPositionToTube_maybe
CVector3 CKHkS08AirCurrent::ClampPositionToTube(const CVector3* position) {
    IKPath* spline = static_cast<IKPath*>(m_pSpline);
    const float along = spline->GetClosestDistanceAlong(position, 1);  // vt+0x58
    CVector3 out;
    spline->GetPointAtDistance(along, &out, nullptr);  // vt+0x54
    const float length = spline->GetLength();          // vt+0x5c
    float dy = position->y - out.y;
    float dx = position->x - out.x;
    float dz = position->z - out.z;
    float distance = std::sqrt(ppc::fmadds(dz, dz, ppc::fmadds(dx, dx, dy * dy)));  // Math_Sqrtf 0x10690
    const float kZero = 0.0f;  // TOC1 +0x5a50
    if (distance != kZero) {
        const float k = 1.0f / distance;  // TOC1 +0x5a54
        dz = dz * k;
        dx = dx * k;
        dy = dy * k;
    } else {
        distance = kZero;
    }
    const float kMargin = 0.05f;  // TOC1 +0x5a88
    const float radius = m_fTubeRadius - kMargin;
    // ble / bgt / ble: a NaN distance or parameter keeps the position.
    if (distance > radius && (length - kMargin) > along && along > kMargin) {
        CVector3 wall;
        wall.z = ppc::fmadds(dz, radius, out.z);
        wall.x = ppc::fmadds(dx, radius, out.x);
        wall.y = ppc::fmadds(dy, radius, out.y);
        return wall;
    }
    CVector3 kept;
    kept.z = position->z;
    kept.x = position->x;
    kept.y = position->y;
    return kept;
}
