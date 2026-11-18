// CKHkLinkedBeacon.cpp - reconstructed original translation unit 0x44ae90-0x450480 (GAME_TOC1, main_toc1), 36 functions, 33 live.
// Primary class: CKHkLinkedBeacon  key 0x1002  category Hook  size 0xf4  vtable 0xb26cb8
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [ ] 0x44ae90  RegisterCKHkLinkedBeaconClass
//   [ ] 0x44af08  _GLOBAL__I_44af08
//   [x] 0x44af18  CKHkLinkedBeacon_ShowInputIcon_maybe
//   [x] 0x44b2b0  CKHkLinkedBeacon_GetInfo
//   [x] 0x44b3e0  CKHkLinkedBeacon_BeginLinkStage_maybe
//   [x] 0x44b710  CKHkLinkedBeacon_Resume
//   [x] 0x44b738  CKHkLinkedBeacon_Pause
//   [x] 0x44b760  CKHkLinkedBeacon_Stop
//   [x] 0x44b788  CKHkLinkedBeacon_Start
//   [x] 0x44b810  CKHkLinkedBeacon_PostLoad
//   [x] 0x44b838  CKHkLinkedBeacon_Save
//   [x] 0x44b860  CKHkLinkedBeacon_RecursiveRegistration
//   [x] 0x44b888  CKHkLinkedBeacon_Destroy
//   [x] 0x44b940  CKHkLinkedBeacon_DeleteArray
//   [x] 0x44b9e0  CKHkLinkedBeacon_Construct  [dead]
//   [x] 0x44ba18  CKHkLinkedBeacon_DeletingDestructor  (the deleting form of the implicit destructor)
//   [x] 0x44ba60  CKHkLinkedBeacon_Destructor  (C++ destructor chain: vtable stores only)
//   [x] 0x44ba90  CKHkLinkedBeacon_BaseDestructor  (C++ destructor chain: vtable stores only)
//   [ ] 0x44bac0  CKHkLinkedBeacon_Construct_2  [dead]
//   [x] 0x44baf8  CKHkLinkedBeacon_vfC8
//   [x] 0x44bb58  CKHkLinkedBeacon_SetDefaultState
//   [x] 0x44bbd8  CKHkLinkedBeacon_Create
//   [x] 0x44bc30  CKHkLinkedBeacon_CreateArray
//   [ ] 0x44bce0  CKHkLinkedBeacon_SaveLinkRecord_maybe  [dead]
//   [x] 0x44be70  CKHkLinkedBeacon_OnActivate
//   [x] 0x44bf20  CKHkLinkedBeacon_Restart
//   [x] 0x44c0b8  CKHkLinkedBeacon_LoadLinkRecord_maybe
//   [x] 0x44c240  CKHkLinkedBeacon_Load
//   [x] 0x44cbb8  CKHkLinkedBeacon_SwitchOn_maybe
//   [x] 0x44d518  CKHkLinkedBeacon_SwitchOff_maybe
//   [x] 0x44d838  CKHkLinkedBeacon_OnDeactivate
//   [x] 0x44d908  CKHkLinkedBeacon_ExecuteLinkAction_maybe
//   [x] 0x44dee0  CKHkLinkedBeacon_UpdateConditionalLinks_maybe
//   [x] 0x44e2c8  CKHkLinkedBeacon_MessageProc
//   [x] 0x44eb40  CKHkLinkedBeacon_UpdateCurrentStage_maybe
//   [x] 0x44f620  CKHkLinkedBeacon_Update
//
//   [ ] 0x9c3c18  CKHkLinkedBeacon_IsKindOfClass  [inline]
//   [ ] 0x9c3c70  CKHkLinkedBeacon_GetClassType  [inline]
//   [ ] 0x9c3c78  CKHkLinkedBeacon_GetClassID  [inline]
//   [x] 0x9c3c80  CKHkLinkedBeacon_GetTriggerPropA7  [inline]
//   [x] 0x9c3c90  CKHkLinkedBeacon_GetTriggerPropA6  [inline]
#include "k2000/hooks/CKHkLinkedBeacon.h"

#include <cmath>
#include <cstring>

#include "Spyro2008/groups/IKGrpHero.h"
#include "Spyro2008/hooks/CKHkS08Hero.h"
#include "crt/ppc_ops.h"
#include "crt/xsinf.h"
#include "k2000/ai/CKSrvPathFinding.h"
#include "k2000/cameras/CKSrvCamera.h"
#include "k2000/components/CKSekensLauncherCpnt.h"
#include "k2000/core/IKInfo.h"
#include "k2000/dictionaries/CAnimationDictionary.h"
#include "k2000/io/IKFile.h"
#include "k2000/logic/CDefaultGameManager.h"
#include "k2000/logic/CKKLBCharacterSparx.h"
#include "k2000/logic/IKFxData.h"
#include "k2000/logic/ai/CKDetectorBase.h"
#include "k2000/logic/ai/CKLinkedBeaconSeq.h"
#include "k2000/logic/fx/CKInputIconNodeFx.h"
#include "k2000/math/CMatrix34.h"
#include "k2000/misc/CKGrpMeca.h"
#include "k2000/misc/ClassRegistry.h"
#include "k2000/misc/Engine.h"
#include "k2000/misc/Mat4.h"
#include "k2000/services/CKSrvFx.h"
#include "k2000/core/Stub.h"
#include "k2000/logic/ai/CKKLBCharacterBase.h"
#include "k2000/dictionaries/CKSoundDictionaryID.h"
#include "k2000/logic/sound/CKSound.h"
#include "k2000/system/CTimeManager.h"
#include "k2000/system/IKTime.h"

namespace {
// 0x00c50d40: the shared +y axis (zero in the EBOOT's BSS; a static initialiser fills it).
const CVector3 kAxisY = {0.0f, 1.0f, 0.0f};

// The unit's game TOC floats (TOC +0x538c..+0x53fc).
constexpr float kFullCircleDegrees = 360.0f;          // +0x53e8: no switch-on / release cone
constexpr float kHalf = 0.5f;                         // +0x53ec
constexpr float kRadiansPerDegree = 0x1.1df468p-6f;   // +0x53f0 0.017453291 (0x3c8efa34)
constexpr float kConeMinDistanceSq = 0.0625f;         // +0x53f4: closer than 0.25 counts as inside the cone
constexpr float kPercent = 100.0f;                    // +0x53f8
constexpr float kRandRange = 65535.0f;                // +0x53fc

IKTime* EngineClock() { return g_pEngine->m_timeManager->m_pTime; }  // engine +0x48 -> +0x04

bool SignBit(float x) {
    int32_t bits;
    std::memcpy(&bits, &x, 4);
    return bits < 0;
}

// The cosine as the unit inlines it: the polynomial for a non-negative argument, the library's cosf 0x9a11d8 on the
// negated argument otherwise (the sign bit tested through memory).
float GameCosf(float x) { return SignBit(x) ? crt::LibCosf(-x) : crt::InlineCosf(x); }

// 0x00010690 Math_Sqrtf: fsqrts.
float Sqrtf(float x) { return std::sqrt(x); }

// The unit's inline normalisation: the length sqrt(z z + (x x + y y)) (fused), each component scaled by 1 / length
// unless the length is 0. Returns the length.
float Normalize(CVector3* v) {
    const float length = Sqrtf(ppc::fmadds(v->z, v->z, ppc::fmadds(v->x, v->x, v->y * v->y)));
    if (length != 0.0f) {
        const float inverse = 1.0f / length;
        v->x *= inverse;
        v->y *= inverse;
        v->z *= inverse;
    }
    return length;
}

// The game manager's hero group (+0x08).
IKGrpHero* HeroGroup() { return static_cast<IKGrpHero*>(g_pEngine->m_gameManager->m_unk04[1]); }

// GetControlledHeroArray 0x2ca0e0 [0], CKHkS08Hero_GetPositionPtr 0x361968.
const float* ControlledHeroPosition() {
    return static_cast<CKHkS08Hero*>(HeroGroup()->m_apControlledHeroes[0])->GetPositionPtr();
}

CKSekensLauncherCpnt* Launcher(IKSerializable* sekens) { return static_cast<CKSekensLauncherCpnt*>(sekens); }

// The animation of step `step` of a sequence: word `step` of its dictionary.
uint32_t AnimWord(const CKLinkedBeaconSeq* seq, int32_t step) {
    return static_cast<uint32_t>(static_cast<CAnimationDictionary*>(seq->m_pAnimDictionary)->m_apAnimations[step]);
}

// The marker byte +0x2d of the object +0xb0: bit 1 = on. The object's class is not known: +0xb0 is null in every
// beacon of the files (LVL010..LVL040, the only levels with beacons), so the byte is only reached through its PS3
// offset here.
void SetMarker(IKSerializable* object, bool on) {
    if (object == nullptr) return;
    uint8_t* flags = reinterpret_cast<uint8_t*>(object) + 0x2d;
    *flags = static_cast<uint8_t>((*flags & 0xfdu) | (on ? 2u : 0u));
}

// One 12-byte read, then each word byte-swapped (the PS3's Read(0xc) + three lwbrx).
void ReadVector3Words(IKFile* file, CVector3* v) {
    uint32_t w[3];
    ReadU32LEWords(file, w, 3);
    std::memcpy(v, w, sizeof(w));
}
}  // namespace

// 0x0044c0b8 CKHkLinkedBeacon_LoadLinkRecord_maybe: a reference, then five single bytes (+4, +6, +5, +7, +8).
void CKHkLinkedBeacon::LoadLinkRecord(IKFile* file, LinkRecord* record, int32_t /*unused*/) {
    IKFile_ReadRef(file, &record->m_pTarget);
    ReadU8(file, &record->m_unk4);
    ReadU8(file, &record->m_unk6);
    ReadU8(file, &record->m_unk5);
    ReadU8(file, &record->m_unk7);
    ReadU8(file, &record->m_unk8);
}

// 0x0044c240 CKHkLinkedBeacon_Load
int32_t CKHkLinkedBeacon::Load(IKFile* file, int32_t type) {
    CKHkActorBase::Load(file, type);
    if (type != K_LEVEL_PLATEFORMS) return 1;
    ReadVector3Words(file, &m_unk20);
    ReadVector3Words(file, &m_unk2C);
    ReadF32LE(file, &m_fTimeOut);
    ReadU8(file, &m_unk50);
    IKFile_ReadRef(file, &m_unk54);
    IKFile_ReadRef(file, &m_unk58);
    IKFile_ReadRef(file, &m_unkC8);
    ReadF32LE(file, &m_unk3C);
    ReadF32LE(file, &m_fReleaseNear);
    ReadF32LE(file, &m_fReleaseFar);
    ReadF32LE(file, &m_unk48);
    ReadF32LE(file, &m_unk4C);
    m_unk88.Load(file, K_LEVEL_PLATEFORMS);
    m_unk90.Load(file, K_LEVEL_PLATEFORMS);
    m_unk98.Load(file, K_LEVEL_PLATEFORMS);
    m_unkA0.Load(file, K_LEVEL_PLATEFORMS);
    m_unkA8.Load(file, K_LEVEL_PLATEFORMS);
    IKFile_ReadRef(file, &m_unkB0);
    if ((m_bitArray & 0x10u) == 0) {
        m_unk68 = 0;
        m_unk6C = 0x1.99999ap-1f;  // 0.8f (TOC 0x3f4ccccd)
        m_unk64 = nullptr;
    } else {
        IKFile_ReadRef(file, &m_unk64);
        ReadU8(file, &m_unk68);
        ReadF32LE(file, &m_unk6C);
    }
    ReadS32LE(file, &m_unk5C);
    m_apUnk60 = new IKSerializable*[static_cast<uint32_t>(m_unk5C)];  // OperatorNewArray(count * 4)
    for (int32_t i = 0; i < m_unk5C; ++i) IKFile_ReadRef(file, &m_apUnk60[i]);
    ReadS32LE(file, &m_unkB4);
    m_apLinks = new LinkRecord*[static_cast<uint32_t>(m_unkB4)];  // OperatorNewArray(count * 4)
    for (int32_t i = 0; i < m_unkB4; ++i) {
        LinkRecord* record = new LinkRecord;  // OperatorNew(0xc), +8, +0, +4 = 0
        record->m_pTarget = nullptr;
        std::memset(&record->m_unk4, 0, 8);
        m_apLinks[i] = record;
        LoadLinkRecord(file, m_apLinks[i], 0);
    }
    ReadU8(file, &m_unkBC);
    ReadF32LE(file, &m_unk70);
    ReadU8(file, &m_unk74);
    ReadVector3Words(file, &m_unk78);
    ReadF32LE(file, &m_fArrivalRadius);
    IKFile_ReadRef(file, &m_unkC0);
    IKFile_ReadRef(file, &m_unkC4);
    return 1;
}

// 0x0044b788 CKHkLinkedBeacon_Start: the character's Start (vt+0x50 of m_unkC8), the icon effect forgotten,
// then vt+0x54.
void CKHkLinkedBeacon::Start() {
    CKHkActorBase::Start();
    static_cast<CKKLBCharacterBase*>(m_unkC8)->Vf50();
    m_pInputIconFx = nullptr;
    Restart();
}

// 0x0044bb58 CKHkLinkedBeacon_SetDefaultState: state 0, or a beacon with bit 11, gets bit 18 set.
void CKHkLinkedBeacon::SetDefaultState(int32_t flag) {
    CKHkActorBase::SetDefaultState(flag);
    if (flag == 0 || (m_bitArray & 0x800) != 0) m_bitArray = (m_bitArray & 0xfffbffffu) | 0x40000u;
}

// 0x0044af18 CKHkLinkedBeacon_ShowInputIcon_maybe. The release: the effect's StopAndRelease (vt+0x58) with this hook, the
// word cleared. The show (with the data +0xc0): CKSrvFx_AcquireFx inlined when none is held; a newly acquired one is
// placed by the beacon's own frame (position +0x20, oriented along +0x2c with +y up) unless the icon follows the
// character (bit 16); with bit 16 it is placed by the character's world matrix (vt+0xa0) every call.
void CKHkLinkedBeacon::ShowInputIcon(int32_t on) {
    if (on == 0) {
        if (m_pInputIconFx == nullptr) return;
        m_pInputIconFx->StopAndRelease(this);  // vt+0x58
        m_pInputIconFx = nullptr;
        return;
    }
    if (m_unkC0 == nullptr) return;
    if (m_pInputIconFx == nullptr) {
        IKFx* fx = static_cast<CKSrvFx*>(g_pEngine->m_srvFx)->AcquireFx(static_cast<IKFxData*>(m_unkC0), this);
        m_pInputIconFx = fx;
        if ((m_bitArray & 0x10000u) == 0 && fx != nullptr) {
            CMatrix34 frame;  // BUG(original): an uninitialised stack matrix; only its position and flag bit 17 are set
            std::memset(&frame, 0, sizeof(frame));
            frame.m_pos = m_unk20;
            frame.m_ui32Flags &= 0xfffdffffu;
            Mat4_SetBasisFromAtUp(&frame, &m_unk2C, &kAxisY);  // 0x0023fd30
            static_cast<CKInputIconNodeFx*>(m_pInputIconFx)->UpdateWorldPosition(&frame);  // 0x001c4bd8
        }
    }
    if ((m_bitArray & 0x10000u) == 0 || m_pInputIconFx == nullptr) return;
    const CMatrix34* matrix = static_cast<CKKLBCharacterSparx*>(m_unkC8)->VfA0();  // vt+0xa0
    static_cast<CKInputIconNodeFx*>(m_pInputIconFx)->UpdateWorldPosition(matrix);
}

// 0x0044bf20 CKHkLinkedBeacon_Restart. A beacon that is not finished (bit 2 clear): when it was active (bit 17)
// its marker byte (+0x2d bit 1 of m_unkB0's object), sound and sekens are stopped, the character restarted
// (vt+0x54 of m_unkC8) and the icon hidden; then the active bits become 0x800000 (bit 23 only among the
// cleared mask 0xe345ffff), the sekens and the link-state marker reset and every link record's byte +9
// cleared.
void CKHkLinkedBeacon::Restart() {
    if ((m_bitArray & 4) != 0) return;
    if ((m_bitArray & 0x20000) != 0) {
        if (m_unkB0 != nullptr) {
            // The object is not identified in the structure draft: its byte at +0x2d loses bit 1.
            uint8_t* flags = reinterpret_cast<uint8_t*>(m_unkB0) + 0x2d;
            *flags = static_cast<uint8_t>(*flags & 0xfc | (*flags & 1));
        }
        if (m_unkC4 != nullptr) {
            CKSoundDictionaryID* dictionary = static_cast<CKSoundDictionaryID*>(m_unkC4);
            if (CKSoundDictionaryID_GetSound(dictionary, 0) != nullptr) {
                Sound_Stop(CKSoundDictionaryID_GetSound(dictionary, 0), 0);
            }
        }
        if (m_pSekens != nullptr) {
            static_cast<CKSekensLauncherCpnt*>(m_pSekens)->StopSekens(0, 0);  // 0x001f7a18: sekens 0 cancelled
            m_pSekens = nullptr;
        }
        static_cast<CKKLBCharacterBase*>(m_unkC8)->Vf54();  // vt+0x54
        ShowInputIcon(0);
    }
    m_bitArray = (m_bitArray & 0xe345ffffu) | 0x800000u;
    m_pSekens = nullptr;
    m_unkEC = -1;
    for (int32_t i = 0; i < m_unkB4; ++i) m_apLinks[i]->m_unk9 = 0;
}

// 0x0044b888 CKHkLinkedBeacon_Destroy
void CKHkLinkedBeacon::Destroy() {
    // CKHkActorBase_d82_maybe_ClearReferences 0x3f6e08: the hook's vt+0xc0 (KStub_Nop_9c0bc8 for this class).
    if (m_apUnk60 != nullptr) {
        delete[] m_apUnk60;  // OperatorDeleteArray
        m_apUnk60 = nullptr;
    }
    for (int32_t i = 0; i < m_unkB4; ++i) delete m_apLinks[i];  // OperatorDelete_Bridge 0xa3ce18
    if (m_apLinks != nullptr) {
        delete[] m_apLinks;
        m_apLinks = nullptr;
    }
}

// 0x0044b2b0 CKHkLinkedBeacon_GetInfo (the actor base's KStub_Return1_3f7140 answers 1, so the merge of the two answers
// is the beacon's own).
int32_t CKHkLinkedBeacon::GetInfo(IKInfo* info, int32_t request) {
    if (request != kGetInfoValueAccessor) return 1;
    switch (info->m_ui32Id) {
    case 0xa6:  // 0x009c3c90 CKHkLinkedBeacon_GetTriggerPropA6, an integer
        return AnswerInfo(info, [](IKSerializable* o, uint32_t) {
            return static_cast<uint32_t>(static_cast<CKHkLinkedBeacon*>(o)->GetTriggerPropA6());
        }, 1);
    case 0xa7:  // 0x009c3c80 CKHkLinkedBeacon_GetTriggerPropA7, a byte
        return AnswerInfo(info, [](IKSerializable* o, uint32_t) {
            return static_cast<CKHkLinkedBeacon*>(o)->GetTriggerPropA7();
        }, 0);
    default:
        return 1;
    }
}

// 0x0044baf8 CKHkLinkedBeacon_vfC8
void CKHkLinkedBeacon::ApplyStatePreset(int32_t state) {
    const uint32_t preset = state == 0 ? (m_bitArray & 0x100u) : (m_bitArray & 0x200u);
    if (preset != 0) {
        m_bitArray = (m_bitArray & 0xfffbffffu) | 0x40000u;
        return;
    }
    m_bitArray &= 0xfffbffffu;
}

// 0x0044be70 CKHkLinkedBeacon_OnActivate
void CKHkLinkedBeacon::VfA0() {
    CKHkActorBase::VfA0();
    m_bitArray = (m_bitArray & 0xe345ffffu) | 0x800000u;
    m_pSekens = nullptr;
    m_unkEC = -1;
    for (int32_t i = 0; i < m_unkB4; ++i) m_apLinks[i]->m_unk9 = 0;
}

// 0x0044d838 CKHkLinkedBeacon_OnDeactivate
void CKHkLinkedBeacon::VfA4() {
    CKHkActorBase::VfA4();
    if ((m_bitArray & 0x20000u) == 0) return;
    if (m_pSekens != nullptr) {
        Launcher(m_pSekens)->StopSekens(0, 0);
        m_pSekens = nullptr;
    }
    m_bitArray &= 0xffcfffffu;
    SwitchOff(EngineClock());
}

// 0x0044b3e0 CKHkLinkedBeacon_BeginLinkStage_maybe. A sekens that is neither current nor pending any more is cancelled
// (StopSekens with 0) before the stage's own is taken; a stage whose sekens has not become current yet (and whose
// sequence does not start at once, +0x16) waits for it with bit 28 (UpdateCurrentStage starts the steps then).
void CKHkLinkedBeacon::BeginLinkStage(IKTime* clock) {
    m_bitArray &= 0xcfffffffu;
    m_fStageStartTime = clock->m_afCurrentTime[IKTime::SCALABLE_GAME_TIME];
    if (m_pSekens != nullptr) {
        if (Launcher(m_pSekens)->IsEntryDone(0) != 0) Launcher(m_pSekens)->StopSekens(0, 0);
        m_pSekens = nullptr;
    }
    const CKLinkedBeaconSeq* seq =
        static_cast<const CKLinkedBeaconSeq*>(m_iStage == -1 ? m_unk64 : m_apUnk60[m_iStage]);
    if (seq->m_pLauncherCpnt != nullptr) {
        m_pSekens = seq->m_pLauncherCpnt;
        if (Launcher(m_pSekens)->HasSekens(0) == 0) {
            m_pSekens = nullptr;
        } else {
            Launcher(m_pSekens)->PlaySekens(0);
        }
    }
    if (m_iStage == -1) {
        m_bitArray &= 0xffbfffffu;
        return;
    }
    CKKLBCharacterBase* character = static_cast<CKKLBCharacterBase*>(m_unkC8);
    if (m_pSekens == nullptr || Launcher(m_pSekens)->IsSekensCurrent(0) != 0 || seq->m_unk16 != 0) {
        m_iAnimStep = 0;
        if ((m_bitArray & 0x10u) != 0) {
            if (seq->m_nbEntries > 0) {
                character->Vf88(1);  // vt+0x88
                m_bitArray = (m_bitArray & 0xffbfffffu) | 0x400000u;
                m_fAnimStepTime = clock->m_afCurrentTime[IKTime::SCALABLE_GAME_TIME];
                character->Vf80(AnimWord(seq, m_iAnimStep));  // vt+0x80
                return;
            }
            character->Vf88(0);
        }
        m_bitArray &= 0xffbfffffu;
        return;
    }
    m_bitArray = (m_bitArray & 0xefffffffu) | 0x10000000u;
    if ((m_bitArray & 0x10u) != 0) character->Vf88(0);
    m_bitArray &= 0xffbfffffu;
}

// The arrival (inlined three times: Update 0x0044fe74, SwitchOn 0x0044d200, UpdateCurrentStage 0x0044f488).
void CKHkLinkedBeacon::Arrive() {
    CKKLBCharacterBase* character = static_cast<CKKLBCharacterBase*>(m_unkC8);
    // vt+0x8c: its first word `m_iStage == -1` (nor / srawi / xor / subf / rldicl 33: the low word of |~stage| - 1 is
    // negative); the second, bit 14 of the bit array (rldicl 50), is not read by CKKLBCharacterSparx_vf8C.
    character->Vf8C(m_iStage == -1 ? 1 : 0);
    QueueTriggerSignals(&m_unkA8);  // 0x00236338 (the beacon as its second word, not used)
    m_bitArray = (m_bitArray & 0xfff7ffffu) | 0x80000u;
    ShowInputIcon(1);
    if (m_unkC4 == nullptr) return;
    CKSoundDictionaryID* dictionary = static_cast<CKSoundDictionaryID*>(m_unkC4);
    if (CKSoundDictionaryID_GetSound(dictionary, 0) != nullptr) {  // 0x00112bc0
        CKSound* sound = CKSoundDictionaryID_GetSound(dictionary, 0);
        const CVector3 position = character->Vf5C();  // vt+0x5c
        sound->SetPosition(&position);                // 0x00110fa0
    }
    if (CKSoundDictionaryID_GetSound(dictionary, 0) != nullptr) {
        CKSound_Play(0.0f, CKSoundDictionaryID_GetSound(dictionary, 0));  // 0x00111230, from 0 (TOC +0x53dc)
    }
}

// The placement for the stage (inlined in SwitchOn 0x0044d000 and UpdateCurrentStage 0x0044f2a8).
void CKHkLinkedBeacon::PlaceCharacter() {
    CKKLBCharacterBase* character = static_cast<CKKLBCharacterBase*>(m_unkC8);
    switch (m_unk50) {
    case 3:
        character->Vf68(&m_unk20, m_unk70, 0);  // vt+0x68
        break;
    case 5:
        character->Vf68(&m_unk20, m_unk70, 1);
        break;
    case 4:
        character->Vf70(&m_unk20, &m_unk2C);  // vt+0x70
        break;
    default:
        character->Vf6C(&m_unk20, &m_unk2C, m_unk50);  // vt+0x6c
        break;
    }
}

// 0x0044cbb8 CKHkLinkedBeacon_SwitchOn_maybe. The view test: the sphere (position +0x20, radius 1) against the camera's
// frustum planes down to 5 (CKSrvCamera_TestSphereAgainstFrustum 0x12c830). The priority (+0xbc, nonzero): every active
// beacon of the meca group's active actor list with a nonzero priority; a higher one keeps the character, lower ones
// are switched off. With a sequence (bit 4) the Sparx must accept the beacon as its target (vt+0x90); it then arrives
// at once within the arrival radius (when nonzero), else (bits 10 + 12 and a first animation) it is reset where it is
// (vt+0x98) and turned (+0x74) or placed (PlaceCharacter); the beacon's own sequence (bit 10) starts at its first
// animation (or the second, without a first).
void CKHkLinkedBeacon::SwitchOn(IKTime* clock) {
    if ((m_bitArray & 0x40000u) == 0) return;
    CKKLBCharacterBase* character = static_cast<CKKLBCharacterBase*>(m_unkC8);
    if (static_cast<uint8_t>(character->Vf60()) == 0) return;  // vt+0x60
    if ((m_bitArray & 0x40u) != 0) {
        const float sphere[4] = {m_unk20.x, m_unk20.y, m_unk20.z, 1.0f};  // (and a 1 after it, not read)
        if (static_cast<CKSrvCamera*>(g_pEngine->m_srvCamera)->TestSphereAgainstFrustum(sphere, 5) == 0) return;
    }
    if (m_unkBC != 0) {
        CKGrpMeca* meca = static_cast<CKGrpMeca*>(g_pEngine->m_gameManager->m_unk04[2]);
        if (meca != nullptr) {
            for (IKHook** actor = meca->m_pUnk2c; *actor != nullptr; ++actor) {
                if (static_cast<uint8_t>((*actor)->IsKindOfClass(0x1002)) == 0) continue;  // vt+0x08
                CKHkLinkedBeacon* other = static_cast<CKHkLinkedBeacon*>(*actor);
                if ((other->m_bitArray & 0x20000u) == 0) continue;
                const uint8_t priority = other->m_unkBC;
                if (priority == 0) continue;
                if (priority > m_unkBC) return;
                if (priority < m_unkBC) other->SwitchOff(clock);
            }
        }
    }
    m_fSwitchOnTime = clock->m_afCurrentTime[IKTime::SCALABLE_GAME_TIME];
    if ((m_bitArray & 0x10u) != 0 && character->SetTarget() == 0) return;  // vt+0x90
    m_bitArray &= 0xfbffffffu;
    if ((m_bitArray & 0x10u) == 0) {
        m_bitArray = (m_bitArray & 0xfff7ffffu) | 0x80000u;
        m_iStage = 0;
    } else {
        m_iStage = -1;
        bool arrived = false;
        if (m_fArrivalRadius != 0.0f) {  // bne: a NaN radius tests too
            const CVector3 position = character->Vf5C();
            const float dx = position.x - m_unk20.x;
            const float dz = position.z - m_unk20.z;
            const float distanceSq = ppc::fmadds(dx, dx, dz * dz);
            arrived = !(distanceSq > m_fArrivalRadius * m_fArrivalRadius);  // bgt: a NaN arrives
        }
        if (arrived) {
            Arrive();
        } else {
            m_bitArray &= 0xfef7ffffu;
            const CKLinkedBeaconSeq* own = static_cast<const CKLinkedBeaconSeq*>(m_unk64);
            if ((m_bitArray & 0x400u) != 0 && (m_bitArray & 0x1000u) != 0 && AnimWord(own, 0) != 0) {
                character->Vf98(1);  // vt+0x98
                if (m_unk74 == 2) {
                    // The path from the Sparx to the beacon (both points' sectors looked up first).
                    CKSrvPathFinding* pathFinding = static_cast<CKSrvPathFinding*>(g_pEngine->m_srvPathFinding);
                    CPFPoint seeker;
                    CPFPoint target;
                    seeker.m_unk0c = 0xffff;
                    target.m_unk0c = 0xffff;
                    seeker.m_position = character->Vf5C();
                    target.m_position = m_unk20;
                    pathFinding->FindSectorForPoint(&seeker);  // 0x001e5ca0
                    pathFinding->FindSectorForPoint(&target);
                    CPFCharacter* pfCharacter = character->Vf94();  // vt+0x94
                    m_unkEC = pathFinding->AcquirePathQuery(&seeker, &target, pfCharacter);  // 0x001e5920
                } else if (m_unk74 == 1 || m_unk74 == 3) {
                    // Turned towards the beacon (1) or the point +0x78 (3).
                    CVector3 direction = m_unk74 == 1 ? m_unk20 : m_unk78;
                    const CVector3 position = character->Vf5C();
                    direction.x -= position.x;
                    direction.y -= position.y;
                    direction.z -= position.z;
                    Normalize(&direction);
                    character->Vf64(&direction.x);  // vt+0x64
                }
            } else {
                PlaceCharacter();
            }
            if ((m_bitArray & 0x400u) != 0) {
                bool animate = true;
                if (AnimWord(own, 0) != 0) {
                    m_iAnimStep = 0;
                } else if (AnimWord(own, 1) == 0) {
                    m_iAnimStep = -1;
                    animate = false;
                } else {
                    m_iAnimLoops = 0;
                    m_iAnimStep = 1;
                }
                if (animate) {
                    character->Vf88(1);
                    character->Vf80(AnimWord(own, m_iAnimStep));
                }
            }
        }
    }
    m_iPendingStage = -1;
    SetMarker(m_unkB0, true);
    m_bitArray = (m_bitArray & 0xfffdffffu) | 0x20000u;
    QueueTriggerSignals(&m_unk88);
    m_bitArray &= 0xdd7fffffu;
    BeginLinkStage(clock);
}

// 0x0044d518 CKHkLinkedBeacon_SwitchOff_maybe. The hand-over follows +0x58 (bit 20) or +0x54 (bit 21) to the first armed
// beacon (bit 18), which switches on unless it is finished (bit 2).
void CKHkLinkedBeacon::SwitchOff(IKTime* clock) {
    if ((m_bitArray & 0x20000u) != 0) {
        if (m_pSekens != nullptr && Launcher(m_pSekens)->IsEntryDone(0) == 0 &&
            Launcher(m_pSekens)->IsSekensLineFinished(0) == 0) {
            Launcher(m_pSekens)->StopSekens(0, 0);
            m_bitArray = (m_bitArray & 0xf7ffffffu) | 0x8000000u;
            return;
        }
        m_bitArray &= 0xe3f7ffffu;
        if ((m_bitArray & 0x10u) != 0) static_cast<CKKLBCharacterBase*>(m_unkC8)->Vf54();  // vt+0x54
        if ((m_bitArray & 0x8u) != 0) m_bitArray &= 0xfffbffffu;
        if (m_pSekens != nullptr) {
            Launcher(m_pSekens)->StopSekens(0, 0);
            m_pSekens = nullptr;
        }
        QueueTriggerSignals(&m_unk98);
        SetMarker(m_unkB0, false);
        if (m_unkC4 != nullptr) {
            CKSoundDictionaryID* dictionary = static_cast<CKSoundDictionaryID*>(m_unkC4);
            if (CKSoundDictionaryID_GetSound(dictionary, 0) != nullptr) {
                Sound_Stop(CKSoundDictionaryID_GetSound(dictionary, 0), 0);  // 0x001111b0
            }
        }
        ShowInputIcon(0);
        m_bitArray &= 0xfffdffffu;
    }
    CKHkLinkedBeacon* next;
    if ((m_bitArray & 0x100000u) != 0) {
        m_bitArray &= 0xffefffffu;
        next = static_cast<CKHkLinkedBeacon*>(m_unk58);
        while (next != nullptr && (next->m_bitArray & 0x40000u) == 0) next = static_cast<CKHkLinkedBeacon*>(next->m_unk58);
    } else if ((m_bitArray & 0x200000u) != 0) {
        m_bitArray &= 0xffdfffffu;
        next = static_cast<CKHkLinkedBeacon*>(m_unk54);
        while (next != nullptr && (next->m_bitArray & 0x40000u) == 0) next = static_cast<CKHkLinkedBeacon*>(next->m_unk54);
    } else {
        return;
    }
    if (next == nullptr || (next->m_bitArray & 0x4u) != 0) return;
    next->SwitchOn(clock);
}

namespace {
// The beacons of the chain from `beacon` along +0x54 (previous) or +0x58 (next), `beacon` not included.
CKHkLinkedBeacon* ChainNext(const CKHkLinkedBeacon* beacon, bool forward) {
    return static_cast<CKHkLinkedBeacon*>(forward ? beacon->m_unk58 : beacon->m_unk54);
}

// Switched off when active (trigger +0x90 first) and disarmed (the actions 5 / 6, the messages 0x99b / 0x99c).
void SwitchOffAndDisarm(CKHkLinkedBeacon* beacon, IKTime* clock) {
    if ((beacon->m_bitArray & 0x20000u) != 0) {
        QueueTriggerSignals(&beacon->m_unk90);
        beacon->SwitchOff(clock);
    }
    beacon->m_bitArray &= 0xfffbffffu;
}

void Arm(CKHkLinkedBeacon* beacon) { beacon->m_bitArray = (beacon->m_bitArray & 0xfffbffffu) | 0x40000u; }

// The next stage (the action 3, the message 0x998): past the last one, the first again when the stages loop (bit 5),
// else the hand-over to the next beacon.
void NextStage(CKHkLinkedBeacon* beacon, IKTime* clock) {
    if ((beacon->m_bitArray & 0x20000u) == 0) return;
    const uint32_t flags = beacon->m_bitArray;
    beacon->m_iStage++;
    if (beacon->m_iStage < beacon->m_unk5C) {
        beacon->BeginLinkStage(clock);
        return;
    }
    if ((flags & 0x20u) != 0 && beacon->m_unk5C > 0) {
        beacon->m_iStage = 0;
        beacon->BeginLinkStage(clock);
        return;
    }
    beacon->m_bitArray = (beacon->m_bitArray & 0xffefffffu) | 0x100000u;
    beacon->SwitchOff(clock);
}

// The Sparx taken over (the action 9, the message 0x99f): an inactive armed beacon whose character's current target
// (vt+0x9c) is a beacon of the same class ID switches that one off first (with a pending switch-on bit 26 on itself),
// then switches on.
void TakeOver(CKHkLinkedBeacon* beacon, IKTime* clock) {
    if ((beacon->m_bitArray & 0x20000u) != 0) return;
    if ((beacon->m_bitArray & 0x40000u) == 0) return;
    IKSerializable* target = static_cast<CKKLBCharacterBase*>(beacon->m_unkC8)->Vf9C();
    if (target != nullptr && target->GetClassID() == beacon->GetClassID()) {  // vt+0x18
        beacon->m_bitArray = (beacon->m_bitArray & 0xfbffffffu) | 0x4000000u;
        static_cast<CKHkLinkedBeacon*>(target)->SwitchOff(clock);
    }
    beacon->SwitchOn(clock);
}
}  // namespace

// 0x0044d908 CKHkLinkedBeacon_ExecuteLinkAction_maybe (the jump table 0x0044d954; an action above 10 does nothing).
void CKHkLinkedBeacon::ExecuteLinkAction(uint32_t action, uint32_t param) {
    switch (action) {
    case 0:
        if ((m_bitArray & 0x20000u) != 0) return;
        if (static_cast<uint8_t>(static_cast<CKKLBCharacterBase*>(m_unkC8)->Vf60()) == 0) return;
        SwitchOn(EngineClock());
        return;
    case 1:
        m_bitArray = (m_bitArray & 0xffefffffu) | 0x100000u;
        SwitchOff(EngineClock());
        return;
    case 2:
        m_bitArray = (m_bitArray & 0xffdfffffu) | 0x200000u;
        SwitchOff(EngineClock());
        return;
    case 3:
        NextStage(this, EngineClock());
        return;
    case 4:
        m_bitArray &= 0xfbffffffu;
        if ((m_bitArray & 0x20000u) == 0) return;
        SwitchOff(EngineClock());
        return;
    case 5:
        SwitchOffAndDisarm(this, EngineClock());
        return;
    case 6: {
        SwitchOffAndDisarm(this, EngineClock());
        for (CKHkLinkedBeacon* b = ChainNext(this, false); b != nullptr; b = ChainNext(b, false)) {
            SwitchOffAndDisarm(b, EngineClock());
        }
        for (CKHkLinkedBeacon* b = ChainNext(this, true); b != nullptr; b = ChainNext(b, true)) {
            SwitchOffAndDisarm(b, EngineClock());
        }
        return;
    }
    case 7:
        Arm(this);
        return;
    case 8:
        Arm(this);
        for (CKHkLinkedBeacon* b = ChainNext(this, false); b != nullptr; b = ChainNext(b, false)) Arm(b);
        for (CKHkLinkedBeacon* b = ChainNext(this, true); b != nullptr; b = ChainNext(b, true)) Arm(b);
        return;
    case 9:
        TakeOver(this, EngineClock());
        return;
    case 10: {
        const int32_t stage = static_cast<int32_t>(param & 0xffu) - 1;
        if (m_iStage == stage) return;
        m_iStage = stage;
        BeginLinkStage(EngineClock());
        return;
    }
    default:
        return;
    }
}

// 0x0044dee0 CKHkLinkedBeacon_UpdateConditionalLinks_maybe. A record with a hero (+5 not 0xfe / 0xff) holds only while
// that hero's player control (CKHkS08Hero_IsPlayerControlled 0x362af0) equals +6 (else its +9 is cleared). An active
// beacon skips the actions 0 and 9, an inactive one 1..4 and 10. The detector then runs (vt+0x50) and its states
// (vt+0x54) 0 (entered), 1 (inside), 2 (left) drive +9 and the action by the condition +4.
void CKHkLinkedBeacon::UpdateConditionalLinks() {
    for (int32_t i = 0; i < m_unkB4; ++i) {
        LinkRecord* record = m_apLinks[i];
        const uint8_t hero = record->m_unk5;
        if (static_cast<uint8_t>(hero + 2u) > 1u) {
            CKHkS08Hero* watched = static_cast<CKHkS08Hero*>(HeroGroup()->m_apHeros[hero]);  // GetHeroByDragonIndex 0x2ca080
            if (record->m_unk6 != watched->IsPlayerControlled()) {
                record->m_unk9 = 0;
                continue;
            }
        }
        const uint8_t action = record->m_unk7;
        if ((m_bitArray & 0x20000u) != 0) {
            if (action == 0 || action == 9) continue;
        } else {
            if (static_cast<uint8_t>(action - 1u) <= 3u || action == 10) continue;
        }
        CKDetectorBase* detector = static_cast<CKDetectorBase*>(record->m_pTarget);
        detector->Detect();  // vt+0x50
        bool entered = static_cast<uint8_t>(detector->GetDetectionType(0)) != 0;  // vt+0x54
        if (!entered && static_cast<uint8_t>(detector->GetDetectionType(1)) != 0 && record->m_unk9 == 0) entered = true;
        if (entered) {
            record->m_unk9 = 1;
            if (record->m_unk4 == 0) ExecuteLinkAction(record->m_unk7, record->m_unk8);
            continue;
        }
        if (static_cast<uint8_t>(detector->GetDetectionType(2)) != 0) {
            record->m_unk9 = 0;
            if (record->m_unk4 == 1) ExecuteLinkAction(record->m_unk7, record->m_unk8);
            continue;
        }
        if (static_cast<uint8_t>(detector->GetDetectionType(1)) != 0) {
            record->m_unk9 = 1;
            if (record->m_unk4 == 2) ExecuteLinkAction(record->m_unk7, record->m_unk8);
            continue;
        }
        if (record->m_unk9 == 0) {
            if (record->m_unk4 == 3) ExecuteLinkAction(record->m_unk7, record->m_unk8);
        } else if (record->m_unk4 == 1) {
            ExecuteLinkAction(record->m_unk7, record->m_unk8);
        }
        m_apLinks[i]->m_unk9 = 0;
    }
}

// 0x0044e2c8 CKHkLinkedBeacon_MessageProc (the jump table 0x0044e340 for 0x940..0x9a0). The beacon's messages use the
// engine's clock: 0x940 (the Sparx takes another target, CKHkS08Sparx_SetTarget_maybe) lets it go without a hand-over
// (bits 20 / 21 cleared, the sekens stopped) and, with bit 13, asks to switch on again (bit 26); 0x996 switch on (an
// inactive beacon with a character), 0x997 as the action 4, 0x998 the next stage, 0x999 / 0x99a hand over to the next /
// previous beacon, 0x99b / 0x99c switch off and disarm (0x99c the whole chain), 0x99d / 0x99e arm (0x99e the whole
// chain), 0x99f the Sparx taken over, 0x9a0 (data: a stage number from 1, at most the stage count) that stage, or
// during the beacon's own sequence its pending stage.
int32_t CKHkLinkedBeacon::MessageProc(uint16_t message, void* data) {
    // CKHkActorBase's (0x003f7148): the actor messages 0x908..0x90f on this class's slots, vt+0xcc / vt+0xd4 empty
    // (KStub_Nop_9c0bd8 / 9c0be0) and vt+0xd0 the actor base's SetVisible 0x009c0c18 (the beacon overrides none of them).
    const int32_t base = CKHkActorBase::MessageProc(message, data);
    IKTime* clock = EngineClock();
    int32_t own = 0;
    switch (message) {
    case 0x940:
        m_bitArray &= 0xffcfffffu;
        if (m_pSekens != nullptr) {
            Launcher(m_pSekens)->StopSekens(0, 0);
            m_pSekens = nullptr;
        }
        SwitchOff(clock);
        if ((m_bitArray & 0x2000u) != 0) m_bitArray = (m_bitArray & 0xfbffffffu) | 0x4000000u;
        break;
    case 0x996:
        if ((m_bitArray & 0x20000u) == 0 && static_cast<uint8_t>(static_cast<CKKLBCharacterBase*>(m_unkC8)->Vf60()) != 0) {
            SwitchOn(clock);
        }
        break;
    case 0x997:
        m_bitArray &= 0xfbffffffu;
        if ((m_bitArray & 0x20000u) != 0) SwitchOff(clock);
        break;
    case 0x998:
        NextStage(this, clock);
        break;
    case 0x999:
        m_bitArray = (m_bitArray & 0xffefffffu) | 0x100000u;
        SwitchOff(clock);
        break;
    case 0x99a:
        m_bitArray = (m_bitArray & 0xffdfffffu) | 0x200000u;
        SwitchOff(clock);
        break;
    case 0x99b:
        SwitchOffAndDisarm(this, clock);
        break;
    case 0x99c:
        SwitchOffAndDisarm(this, clock);
        for (CKHkLinkedBeacon* b = ChainNext(this, false); b != nullptr; b = ChainNext(b, false)) SwitchOffAndDisarm(b, clock);
        for (CKHkLinkedBeacon* b = ChainNext(this, true); b != nullptr; b = ChainNext(b, true)) SwitchOffAndDisarm(b, clock);
        break;
    case 0x99d:
        Arm(this);
        break;
    case 0x99e:
        Arm(this);
        for (CKHkLinkedBeacon* b = ChainNext(this, false); b != nullptr; b = ChainNext(b, false)) Arm(b);
        for (CKHkLinkedBeacon* b = ChainNext(this, true); b != nullptr; b = ChainNext(b, true)) Arm(b);
        break;
    case 0x99f:
        TakeOver(this, clock);
        break;
    case 0x9a0: {
        const int32_t stage = *static_cast<const int32_t*>(data);
        if ((m_bitArray & 0x20000u) == 0 || stage <= 0 || m_unk5C < stage) break;
        if (m_iStage == -1) {
            m_iPendingStage = stage - 1;  // BUG(original): Update takes a pending stage only above 0, so 1 is lost
            break;
        }
        m_iStage = stage - 1;
        BeginLinkStage(clock);
        break;
    }
    default:
        own = 1;
        break;
    }
    if (base == 3 || own == 3) return 3;
    if (base == 2 || own == 2) return 2;
    if (base == 0) return 0;
    return own;
}

// 0x0044eb40 CKHkLinkedBeacon_UpdateCurrentStage_maybe. The beacon's own sequence (stage -1) with bit 10: step 0 plays
// until its animation ends (vt+0x7c; meanwhile vt+0x84 advances it), then (with bit 12) the character is placed (and
// arrives for the placement 4) and step 1 starts (or none: vt+0x88 0); step 1 loops +0x68 times (0: endlessly); step 2
// starts once the character is within +0x6c of the beacon. The own sequence is over with bit 24 (set by Update).
uint8_t CKHkLinkedBeacon::UpdateCurrentStage(IKTime* clock) {
    CKKLBCharacterBase* character = static_cast<CKKLBCharacterBase*>(m_unkC8);
    const double dt = clock->m_afDeltaTime[IKTime::SCALABLE_GAME_TIME];
    const CKLinkedBeaconSeq* seq;
    if (m_iStage == -1) {
        seq = static_cast<const CKLinkedBeaconSeq*>(m_unk64);
        if ((m_bitArray & 0x400u) != 0) {
            if (m_iAnimStep == 0) {
                if (character->Vf7C(dt) == 0) {
                    character->Vf84(dt);
                } else {
                    if ((m_bitArray & 0x1000u) != 0) {
                        PlaceCharacter();
                        if (m_unk50 == 4) Arrive();
                    }
                    if (AnimWord(seq, 1) == 0) {
                        m_iAnimStep = -1;
                        character->Vf88(0);
                    } else {
                        m_iAnimStep = 1;
                        m_iAnimLoops = 0;
                        character->Vf80(AnimWord(seq, 1));
                    }
                }
            } else if (m_iAnimStep > 0) {
                if (m_unk68 != 0 && m_iAnimStep == 1 && character->Vf7C(dt) != 0) {
                    m_iAnimLoops++;
                    if (static_cast<int32_t>(m_unk68) <= m_iAnimLoops) {
                        m_iAnimStep = -1;
                        character->Vf88(0);
                    }
                }
                if (m_iAnimStep > 0) character->Vf84(dt);
            }
            if (m_iAnimStep != 2 && AnimWord(seq, 2) != 0) {
                const CVector3 position = character->Vf5C();
                const float dx = position.x - m_unk20.x;
                const float dy = position.y - m_unk20.y;
                const float dz = position.z - m_unk20.z;
                const float distanceSq = ppc::fmadds(dz, dz, ppc::fmadds(dx, dx, dy * dy));
                if (distanceSq <= m_unk6C * m_unk6C) {  // cror lt / eq
                    m_iAnimStep = 2;
                    character->Vf88(1);
                    character->Vf80(AnimWord(seq, m_iAnimStep));
                }
            }
        }
        if ((m_bitArray & 0x1000000u) != 0) return 1;
    } else {
        seq = static_cast<const CKLinkedBeaconSeq*>(m_apUnk60[m_iStage]);
    }
    // The stage's sekens: a looping stage (+0x14) plays it again once it is done, else it is forgotten.
    if (m_pSekens != nullptr && (m_bitArray & 0x10000000u) == 0 && Launcher(m_pSekens)->IsEntryDone(0) != 0) {
        if (seq->m_unk14 != 0) {
            Launcher(m_pSekens)->PlaySekens(0);
        } else {
            m_pSekens = nullptr;
        }
    }
    const float time = clock->m_afCurrentTime[IKTime::SCALABLE_GAME_TIME];
    if (seq->m_unk14 != 0 && seq->m_fTimeOut > 0.0f && time - m_fStageStartTime >= seq->m_fTimeOut) {
        if (m_pSekens != nullptr) {
            Launcher(m_pSekens)->StopSekens(0, 0);
            m_pSekens = nullptr;
        }
        return 1;
    }
    if ((m_bitArray & 0x400000u) == 0) {
        if ((m_bitArray & 0x10000000u) != 0) {
            // Waiting for the stage's sekens to become current.
            if (m_pSekens == nullptr) {
                m_bitArray &= 0xefffffffu;
                return 0;
            }
            Launcher(m_pSekens)->PlaySekens(0);
            if (Launcher(m_pSekens)->IsSekensCurrent(0) == 0) return 0;
            m_bitArray &= 0xefffffffu;
            m_iAnimStep = 0;
            if ((m_bitArray & 0x10u) != 0) {
                if (seq->m_nbEntries > 0) {
                    character->Vf88(1);
                    m_bitArray = (m_bitArray & 0xffbfffffu) | 0x400000u;
                    m_fAnimStepTime = time;
                    character->Vf80(AnimWord(seq, m_iAnimStep));
                    return 0;
                }
                character->Vf88(0);
            }
            m_bitArray &= 0xffbfffffu;
            return 0;
        }
        if (seq->m_unk14 != 0) return 0;
        return m_pSekens == nullptr ? 1 : 0;
    }
    if (seq->m_unk15 != 0) {
        // The steps follow the sekens' current line.
        if (m_pSekens == nullptr) {
            m_bitArray &= 0xffbfffffu;
            return 1;
        }
        if (m_iAnimStep == Launcher(m_pSekens)->GetCurrentLineIndex(0)) {
            character->Vf84(dt);
            return 0;
        }
        m_iAnimStep = Launcher(m_pSekens)->GetCurrentLineIndex(0);
        if (m_iAnimStep < 0) m_iAnimStep = 0;
        m_fAnimStepTime = time;
        character->Vf80(AnimWord(seq, m_iAnimStep));
        return 0;
    }
    // The steps by their end flag / duration.
    const CKLinkedBeaconSeq::Entry* entry = &seq->m_aEntries[m_iAnimStep];
    bool advance;
    if (entry->m_unk0 == 0 && character->Vf7C(dt) != 0) {
        advance = true;
    } else {
        entry = &seq->m_aEntries[m_iAnimStep];
        // A step that waits for its animation's end, or a timed one before its duration (ble / cror gt eq: a NaN
        // duration waits).
        advance = entry->m_unk0 != 0 && entry->m_fDuration > 0.0f && time - m_fAnimStepTime >= entry->m_fDuration;
    }
    if (!advance) {
        character->Vf84(dt);
        return 0;
    }
    m_iAnimStep++;
    if (seq->m_unk14 != 0 && seq->m_nbEntries == m_iAnimStep) m_iAnimStep = 0;
    if (m_iAnimStep < seq->m_nbEntries) {
        m_fAnimStepTime = time;
        character->Vf80(AnimWord(seq, m_iAnimStep));
        return 0;
    }
    m_bitArray &= 0xffbfffffu;
    return 1;
}

// 0x0044f620 CKHkLinkedBeacon_Update (WorldObjectBase_Update_Nop 0x3f6e68 first: empty).
void CKHkLinkedBeacon::Update(IKTime* clock) {
    if ((m_bitArray & 0x40000u) == 0 && (m_bitArray & 0x20000u) == 0) return;
    CKKLBCharacterBase* character = static_cast<CKKLBCharacterBase*>(m_unkC8);
    if (static_cast<uint8_t>(character->Vf58()) == 0) return;  // vt+0x58
    if ((m_bitArray & 0x4000000u) != 0) {
        SwitchOn(clock);
    } else if ((m_bitArray & 0x8000000u) != 0) {
        SwitchOff(clock);
    }
    UpdateConditionalLinks();
    const float time = clock->m_afCurrentTime[IKTime::SCALABLE_GAME_TIME];

    if ((m_bitArray & 0x20000u) == 0) {
        // Inactive: the switch-on test of the character (its range +0x3c, then the cone of +0x48 degrees around +0x2c
        // unless 360, or closer than 0.25). Once the character has been outside it (bit 23), entering it switches the
        // beacon on with the chance +0x4c percent (a draw unless 100); a failed draw waits for the next exit.
        CVector3 delta = character->Vf5C();
        delta.x -= m_unk20.x;
        delta.y -= m_unk20.y;
        delta.z -= m_unk20.z;
        const float distanceSq = ppc::fmadds(delta.z, delta.z, ppc::fmadds(delta.x, delta.x, delta.y * delta.y));
        const float length = Sqrtf(distanceSq);
        if (length != 0.0f) {
            const float inverse = 1.0f / length;
            delta.z *= inverse;
            delta.x *= inverse;
            delta.y *= inverse;
        }
        bool inside = false;
        if (static_cast<uint8_t>(character->Vf60()) != 0 && m_unk3C * m_unk3C >= distanceSq) {  // cror gt / eq
            inside = true;
            if (m_unk48 < kFullCircleDegrees) {  // bge: a NaN angle has no cone
                const float cosine = GameCosf(m_unk48 * kHalf * kRadiansPerDegree);
                const float dot =
                    ppc::fmadds(m_unk2C.z, delta.z, ppc::fmadds(m_unk2C.x, delta.x, delta.y * m_unk2C.y));
                if (!(dot < -cosine) && !(distanceSq < kConeMinDistanceSq)) inside = false;
            }
        }
        if ((m_bitArray & 0x800000u) == 0) {
            if (!inside) m_bitArray = (m_bitArray & 0xff7fffffu) | 0x800000u;
            return;
        }
        if (!inside) return;
        if (m_unk4C != kPercent) {
            const float draw = static_cast<float>(static_cast<uint32_t>(Rand_Int()) & 0xffffu);  // 0x00011500
            if (draw / kRandRange * kPercent > m_unk4C) {  // ble: switched on unless above the chance
                m_bitArray &= 0xff7fffffu;
                return;
            }
        }
        SwitchOn(clock);
        return;
    }

    // Active.
    if ((m_bitArray & 0x8000u) != 0) ShowInputIcon(1);
    if ((m_bitArray & 0x80000u) != 0) {
        if ((m_bitArray & 0x10000u) != 0) ShowInputIcon(1);
    } else if ((m_bitArray & 0x1000u) != 0 && m_iAnimStep == 0) {
        // The path-finding route (+0xec): towards its next waypoint (from the beacon's position when it gives none).
        if (m_unkEC >= 0) {
            CVector3 point = m_unk20;
            uint16_t nextNode;
            const uint32_t state = static_cast<CKSrvPathFinding*>(g_pEngine->m_srvPathFinding)
                                       ->GetNextQueryWaypoint(static_cast<uint8_t>(m_unkEC), &nextNode, &point);  // 0x001e52c8
            if ((state & 2u) != 0) m_unkEC = -1;
            const CVector3 position = character->Vf5C();
            point.y -= position.y;
            point.x -= position.x;
            point.z -= position.z;
            Normalize(&point);
            character->Vf64(&point.x);
        }
    } else {
        // Flying to the beacon: arrived when the flight ends (vt+0x78 for the placements 3 / 5, else vt+0x74) or within
        // the arrival radius (horizontally; cror lt / eq).
        const uint8_t done =
            (m_unk50 == 3 || m_unk50 == 5) ? character->Vf78(clock) : character->MoveTowardTarget(clock);
        bool arrived = done != 0;
        if (!arrived) {
            const CVector3 position = character->Vf5C();
            const float dz = position.z - m_unk20.z;
            const float dx = position.x - m_unk20.x;
            arrived = ppc::fmadds(dx, dx, dz * dz) <= m_fArrivalRadius * m_fArrivalRadius;
        }
        if (arrived) Arrive();
    }

    // The time-out (bit 5, +0x38 above 0): the hand-over to the next beacon.
    if ((m_bitArray & 0x20u) != 0 && m_fTimeOut > 0.0f && time - m_fSwitchOnTime >= m_fTimeOut) {
        m_bitArray = (m_bitArray & 0xffefffffu) | 0x100000u;
        SwitchOff(clock);
        return;
    }
    const uint8_t hasCharacter = static_cast<uint8_t>(character->Vf60());
    if (hasCharacter == 0) {
        QueueTriggerSignals(&m_unk90);
        m_pSekens = nullptr;  // (the word Vf60 answered, 0; the sekens is not stopped)
        SwitchOff(clock);
        return;
    }
    if ((m_bitArray & 0x20000000u) != 0 && (m_bitArray & 0x80000u) != 0) {
        // The stage is over and the character has arrived: the next stage (the pending one first), past the last one
        // the first again when the stages loop, else the hand-over to the next beacon.
        m_bitArray = (m_bitArray & 0xfdffffffu) | 0x2000000u;
        if (m_iPendingStage > 0) {
            m_iStage = m_iPendingStage;
            m_iPendingStage = -1;
        } else {
            m_iStage++;
            const int32_t count = m_unk5C;
            if (m_iStage >= count) {
                if ((m_bitArray & 0x20u) == 0 || count <= 0) {
                    m_bitArray = (m_bitArray & 0xffefffffu) | 0x100000u;
                    SwitchOff(clock);
                    return;
                }
                m_iStage = 0;
            }
        }
        BeginLinkStage(clock);
    } else if (UpdateCurrentStage(clock) == 0) {
        m_bitArray &= 0xfdffffffu;
    } else {
        if (m_iStage != -1) {
            QueueTriggerSignals(&m_unkA0);
        } else if ((m_bitArray & 0x1000000u) == 0) {
            QueueTriggerSignals(&m_unkA0);
            m_bitArray = (m_bitArray & 0xfeffffffu) | 0x1000000u;
        }
        m_bitArray = (m_bitArray & 0xdfffffffu) | 0x20000000u;
    }

    // The arrived character faces the hero (bit 7; the beacon's direction when they meet) or the beacon's direction.
    if ((m_bitArray & 0x80000u) != 0 && (m_bitArray & 0x10u) != 0) {
        CVector3 direction;
        if ((m_bitArray & 0x80u) != 0) {
            const float* hero = ControlledHeroPosition();
            direction.x = hero[0];
            direction.y = hero[1];
            direction.z = hero[2];
            const CVector3 position = character->Vf5C();
            direction.y -= position.y;
            direction.x -= position.x;
            direction.z -= position.z;
            if (Normalize(&direction) == 0.0f) direction = m_unk2C;
        } else {
            direction = m_unk2C;
        }
        character->Vf64(&direction.x);
    }
    if (static_cast<uint8_t>(character->VfA8()) != 0) return;  // vt+0xa8

    // The release by the controlled hero: within +0x40 (the hand-over to the next beacon), or beyond +0x44 inside the
    // cone (to the previous one); both fire trigger +0x90.
    const float* hero = ControlledHeroPosition();
    float dx = hero[0] - m_unk20.x;
    float dy = hero[1] - m_unk20.y;
    float dz = hero[2] - m_unk20.z;
    const float distanceSq = ppc::fmadds(dz, dz, ppc::fmadds(dx, dx, dy * dy));
    const float length = Sqrtf(distanceSq);
    if (length != 0.0f) {
        const float inverse = 1.0f / length;
        dz *= inverse;
        dx *= inverse;
        dy *= inverse;
    }
    bool inCone;
    if (m_unk48 == kFullCircleDegrees || distanceSq < kConeMinDistanceSq) {
        inCone = true;
    } else {
        const float cosine = GameCosf(m_unk48 * kHalf * kRadiansPerDegree);
        const float dot = ppc::fmadds(m_unk2C.z, dz, ppc::fmadds(dx, m_unk2C.x, dy * m_unk2C.y));
        inCone = dot < -cosine;
    }
    if (m_fReleaseNear > 0.0f && m_fReleaseNear * m_fReleaseNear >= distanceSq) {  // cror gt / eq
        m_bitArray = (m_bitArray & 0xffefffffu) | 0x100000u;
    } else {
        if (!(m_fReleaseFar > 0.0f) || !inCone) return;
        if (!(m_fReleaseFar * m_fReleaseFar <= distanceSq)) return;  // cror lt / eq
        m_bitArray = (m_bitArray & 0xffdfffffu) | 0x200000u;
    }
    QueueTriggerSignals(&m_unk90);
    SwitchOff(clock);
}
