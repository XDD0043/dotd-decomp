// CKHkScrapShower.cpp - reconstructed original translation unit 0x4a40d0-0x4a66d0 (GAME_TOC1, main_toc1), 28 functions, 26 live.
// Primary class: CKHkScrapShower  key 0x1242  category Hook  size 0x12c  vtable 0xb285c8
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [ ] 0x4a40d0  RegisterCKHkScrapShowerClass
//   [ ] 0x4a4148  _GLOBAL__I_4a4148
//   [x] 0x4a4158  CKHkScrapShower_GetInfo
//   [x] 0x4a4240  CKHkScrapShower_PickDropPosition_maybe
//   [x] 0x4a47f8  CKHkScrapShower_Resume  (the actor base's KStub_Nop_3f6e60: inherited)
//   [x] 0x4a4820  CKHkScrapShower_Pause  (the actor base's KStub_Nop_3f6e58: inherited)
//   [x] 0x4a4848  CKHkScrapShower_Stop  (the actor base's Stop: inherited)
//   [x] 0x4a4870  CKHkScrapShower_Start
//   [x] 0x4a49c0  CKHkScrapShower_PostLoad  (header)
//   [ ] 0x4a4a00  CKHkScrapShower_Save
//   [x] 0x4a4a28  CKHkScrapShower_RecursiveRegistration  (the actor base's (IKHook's): inherited)
//   [x] 0x4a4a50  CKHkScrapShower_Destroy
//   [x] 0x4a4ab0  CKHkScrapShower_DeleteArray
//   [x] 0x4a4b50  CKHkScrapShower_Construct  [dead]
//   [x] 0x4a4bd0  CKHkScrapShower_OnActivate
//   [x] 0x4a4ce8  CKHkScrapShower_BaseDestructor  (the header's destructor)
//   [x] 0x4a4d18  CKHkScrapShower_vfC8  (CKHkScrapShower::ApplyStatePreset)
//   [x] 0x4a4d68  CKHkScrapShower_SetDefaultState
//   [x] 0x4a4db0  CKHkScrapShower_DeletingDestructor  (the header's destructor)
//   [x] 0x4a4df8  CKHkScrapShower_Destructor  (the header's destructor)
//   [x] 0x4a4e28  CKHkScrapShower_OnDeactivate
//   [x] 0x4a4f18  CKHkScrapShower_Update
//   [ ] 0x4a5770  CKHkScrapShower_Construct_2  [dead]
//   [x] 0x4a57f0  CKHkScrapShower_MessageProc
//   [x] 0x4a5aa8  CKHkScrapShower_Restart
//   [x] 0x4a5bb8  CKHkScrapShower_CreateArray
//   [x] 0x4a5ce0  CKHkScrapShower_Create
//   [x] 0x4a5d78  CKHkScrapShower_Load
//
//   [ ] 0x9c4e50  CKHkScrapShower_IsKindOfClass  [inline]
//   [ ] 0x9c4ea8  CKHkScrapShower_GetClassType  [inline]
//   [ ] 0x9c4eb0  CKHkScrapShower_GetClassID  [inline]
//   [ ] 0x9c4eb8  CKHkScrapShower_GetTriggerProp9B  [inline]
#include "k2000/hooks/CKHkScrapShower.h"

#include "k2000/math/Math.h"

#include <cmath>

#include "Renderware/rwcore/RwCamera.h"
#include "Spyro2008/groups/IKGrpHero.h"
#include "Spyro2008/hooks/CKHkS08Hero.h"
#include "Spyro2008/logic/CKS08GameManager.h"
#include "crt/ppc_ops.h"
#include "k2000/ai/CKHkDetectorGroup.h"
#include "k2000/components/CKScrapShowerCpnt.h"
#include "k2000/core/IKInfo.h"
#include "k2000/dictionaries/CKSoundDictionaryID.h"
#include "k2000/io/IKFile.h"
#include "k2000/logic/CDefaultGameManager.h"
#include "k2000/logic/ai/CKDetectorBase.h"
#include "k2000/logic/sound/CKSound.h"
#include "k2000/misc/ClassRegistry.h"
#include "k2000/misc/Engine.h"
#include "k2000/scenegraph/CSGMovable.h"
#include "k2000/services/CKSrvCollision.h"
#include "k2000/system/IKTime.h"

// 0x004a5d78 CKHkScrapShower_Load: every multi-byte read is swapped (lwbrx per word), the four single
// bytes are not.
int32_t CKHkScrapShower::Load(IKFile* file, int32_t type) {
    CKHkActorBase::Load(file, type);
    if (type != K_LEVEL_PLATEFORMS) return 1;
    ReadU32LEWords(file, reinterpret_cast<uint32_t*>(&m_unk20), 3);
    ReadF32LE(file, &m_unk2c);
    ReadF32LE(file, &m_unkC0);
    ReadU8(file, &m_ui8NbUnk58);
    m_unk58 = new float[m_ui8NbUnk58];
    m_unk5c = new float[m_ui8NbUnk58];
    for (uint32_t i = 0; i < m_ui8NbUnk58; ++i) {
        ReadF32LE(file, &m_unk58[i]);
        ReadF32LE(file, &m_unk5c[i]);
    }
    for (uint32_t i = 0; i < 9; ++i) ReadF32LE(file, &m_unk60[i]);
    ReadU8(file, &m_unkA0);
    for (uint32_t i = 0; i < 3; ++i) ReadF32LE(file, &m_unkA4[i]);
    IKFile_ReadRef(file, &m_unk30);
    IKFile_ReadRef(file, &m_unk84);
    ReadU32LEWords(file, reinterpret_cast<uint32_t*>(&m_unk88), 3);
    ReadU32LEWords(file, reinterpret_cast<uint32_t*>(m_unk94), 2);
    IKFile_ReadRef(file, &m_unk9c);
    m_unkC4.Load(file, K_LEVEL_PLATEFORMS);
    m_unkCC.Load(file, K_LEVEL_PLATEFORMS);
    IKFile_ReadRef(file, &m_unkD4);
    ReadU8(file, &m_unkD8);
    ReadU8(file, &m_unkD9);
    ReadU8(file, &m_unkBC);
    for (uint32_t i = 0; i < 3; ++i) ReadF32LE(file, &m_unkB0[i]);
    return 1;
}

// ==== C2.8 port-all P18: the rest of the hook ====================================================================

namespace {

IKGrpHero* ScrapHeroGroup() { return static_cast<IKGrpHero*>(g_pEngine->m_gameManager->m_unk04[1]); }  // engine +0x8c -> +0x08

CKScrapShowerCpnt* ScrapCpnt(IKSerializable* cpnt) { return static_cast<CKScrapShowerCpnt*>(cpnt); }

// The draw of the delays (Rand_Int & 0xffff, as a float).
float RandUnit16() { return static_cast<float>(static_cast<double>(static_cast<uint32_t>(Rand_Int()) & 0xffffu)); }

// The block of the hero's hazard query 0xc32 (CKHkS08Hero_6.cpp's HazardHitQuery, the same layout).
struct ScrapHazardQuery {
    IKSerializable* m_hero;   // +0x00
    void* m_volume;           // +0x04
    float m_knock[3];         // +0x08..+0x10
    CVector3 m_point;         // +0x14
    int32_t m_kind;           // +0x20
    uint8_t m_damage;         // +0x24
};

// The falling sound (+0xd4's sound +0x129), stopped when there is one.
void StopFallSound(CKSoundDictionaryID* dict, int8_t sound) {
    if (dict->GetSound(static_cast<uint32_t>(static_cast<int32_t>(sound))) == nullptr) return;  // 0x00112bc0
    Sound_Stop(dict->GetSound(static_cast<uint32_t>(static_cast<int32_t>(sound))), 0);       // 0x001111b0
}

}  // namespace

float CKHkScrapShower::DrawDelay(uint32_t step) const {
    const float a0 = m_unk58[step];
    const float b0 = m_unk5c[step];
    const float u = RandUnit16();
    const float half = (b0 - a0) * 0.5f;                 // TOC +0x61fc
    const float mid = ppc::fmadds(a0 + b0, 0.5f, half);  // b
    const float span = (m_unk5c[step] - m_unk58[step]) * -0.5f;  // TOC +0x6200
    float t = u / 65535.0f;                               // TOC +0x61dc
    t = t + t;
    return ppc::fmadds(t, span, mid);
}

// 0x004a4158 CKHkScrapShower_GetInfo
int32_t CKHkScrapShower::GetInfo(IKInfo* info, int32_t request) {
    const int32_t base = CKHkActorBase::GetInfo(info, request);  // KStub_Return1 0x3f7140
    int32_t own = 1;
    if (request == kGetInfoValueAccessor && info->m_ui32Id == 0x9b) {
        own = AnswerInfo(info, [](IKSerializable* o, uint32_t) {
            return (static_cast<CKHkScrapShower*>(o)->m_bitArray >> 8) & 1u;  // 0x009c4eb8 GetTriggerProp9B
        }, 0);
    }
    if (base == 2) return 2;
    if (own == 0) return 0;
    return base == 0 ? 0 : 1;
}

// 0x004a4240 CKHkScrapShower_PickDropPosition_maybe
uint8_t CKHkScrapShower::PickDropPosition() {
    CKHkS08Hero* hero = static_cast<CKHkS08Hero*>(ScrapHeroGroup()->m_apControlledHeroes[0]);  // 0x002ca0e0
    if (hero == nullptr) return 0;
    CVector3 pos;
    float stepX;
    float stepY;
    float stepZ;
    const float chance = RandUnit16() / 65535.0f * 100.0f;  // TOC +0x61dc, +0x61e0
    if (!(chance >= m_unk60[1])) {  // bge: NaN takes the other branch
        // In front of the hero: his forward axis times his speed times (+0x2c / +0xc0 + +0x60).
        const float* p = hero->GetPositionPtr();  // 0x00361968
        pos = {p[0], p[1], p[2]};
        const float fx = hero->m_unk540;  // 0x00361a50 CKHkS08Hero_GetForwardDirPtr_maybe
        const float fy = hero->m_unk544;
        const float fz = hero->m_unk548;
        const float lead = hero->GetUnk530() * (m_unk2c / m_unkC0 + m_unk60[0]);  // 0x00361c10
        stepZ = fz * lead;
        stepX = fx * lead;
        stepY = fy * lead;
        pos.z = pos.z + stepZ;
        pos.x = pos.x + stepX;
        pos.y = pos.y + stepY;
    } else {
        float spreadX;
        float spreadZ;
        if ((m_bitArray & 8u) == 0) {
            const float* p = hero->GetPositionPtr();
            pos = {p[0], p[1], p[2]};
            spreadX = m_unk60[2];
            spreadZ = m_unk60[2];
        } else {
            pos = m_unk88;
            spreadX = m_unk94[0];
            spreadZ = m_unk94[1];
        }
        const float k = -3.0518044e-05f;  // TOC +0x61e4: -2 / 65535
        stepX = ppc::fmadds(RandUnit16(), k, 1.0f) * spreadX;  // TOC +0x61e8 1.0
        const float u2 = RandUnit16();
        stepY = 0.0f;  // TOC +0x61f0
        pos.y = pos.y + stepY;
        pos.x = pos.x + stepX;
        stepZ = ppc::fmadds(u2, k, 1.0f) * spreadZ;
        pos.z = pos.z + stepZ;
    }
    CKSrvCollision* collision = static_cast<CKSrvCollision*>(g_pEngine->m_srvCollision);
    collision->GroundProbePoints(&m_GContactIn, &m_GContactInOut, &pos.x, 1);  // 0x00196540
    if (m_GContactInOut.m_eContactStatus == 3) {
        // Three more probes, each a quarter step back toward the hero (TOC +0x61ec -0.25).
        stepZ = stepZ * -0.25f;
        stepX = stepX * -0.25f;
        stepY = stepY * -0.25f;
        for (int32_t i = 0; i < 3 && m_GContactInOut.m_eContactStatus == 3; ++i) {
            pos.z = pos.z + stepZ;
            pos.x = pos.x + stepX;
            pos.y = pos.y + stepY;
            collision->GroundProbePoints(&m_GContactIn, &m_GContactInOut, &pos.x, 1);
        }
    }
    if (m_GContactInOut.m_eContactStatus == 3) return 0;
    if ((m_bitArray & 0x10u) == 0) {
        CKS08GameManager* manager = static_cast<CKS08GameManager*>(g_pEngine->m_gameManager);
        if ((manager->GetGroundSurfaceBit(m_GContactInOut.m_pGround) & 0xffu) != 0) return 0;  // vt+0x138 0x004f88f8
    }
    CVector3 point;
    GroundContact_GetWorldPoint(&m_GContactInOut, &point);  // inlined 0x001a70e0 (the moving ground's matrix, class 0x13)
    RwFrame* frame = static_cast<CSGMovable*>(m_pKGLObject)->m_pRwFrame;
    frame->modelling.pos.z = point.z;
    frame->modelling.pos.x = point.x;
    frame->modelling.pos.y = point.y;
    frame->modelling.flags &= 0xfffdffffu;
    RwFrame_MarkDirty(frame);  // 0x00010698
    frame = static_cast<CSGMovable*>(m_pKGLObject)->m_pRwFrame;
    frame->modelling.up.x = m_GContactInOut.m_Normal.x;
    frame->modelling.up.y = m_GContactInOut.m_Normal.y;
    frame->modelling.up.z = m_GContactInOut.m_Normal.z;
    frame->modelling.flags &= 0xfffdfffcu;
    RwFrame_MarkDirty(frame);
    return 1;
}

// 0x004a4870 CKHkScrapShower_Start
void CKHkScrapShower::Start() {
    CKHkActorBase::Start();  // 0x003f6e48
    m_i32ShadowIndex = -1;
    Restart();  // vt+0x54
    m_GContactIn.m_MasksOfGrdForTest[0] = 1;
    m_GContactIn.m_MasksOfGrdForTest[1] = 8;
    m_GContactIn.m_fDeltaMax = 1.0f;  // TOC +0x61e8
    m_GContactIn.m_fObjectHeight = m_unk2c;
    m_GContactInOut.m_pGround = nullptr;
    m_GContactInOut.m_ui8SectorNumber = 0;
    m_GContactInOut.m_i32FaceIndex = -1;
    m_GContactInOut.m_eContactStatus = 3;
    float other = 0.0f;
    const uint8_t roots = static_cast<uint8_t>(Math_SolveQuadratic(4.9f, m_unkC0, -m_unk2c, &m_fFallTime, &other));  // TOC +0x61f4; 0x0098f690 -> 0x582b08
    if (roots == 2) {
        if (m_fFallTime <= 0.0f) m_fFallTime = other;  // cror lt|eq: NaN keeps the first root
    } else if (roots == 0) {
        m_fFallTime = m_unk2c / m_unkC0;
    }
}

// 0x004a4a50 CKHkScrapShower_Destroy
void CKHkScrapShower::Destroy() {
    CKHkActorBase::Destroy();  // 0x003f6e08: vt+0xc0 (empty)
    if (m_unk58 != nullptr) delete[] m_unk58;  // OperatorDeleteArray
    if (m_unk5c != nullptr) delete[] m_unk5c;
}

// 0x004a4bd0 CKHkScrapShower_OnActivate
void CKHkScrapShower::VfA0() {
    CKHkActorBase::VfA0();  // 0x003f7338
    CKSoundDictionaryID* dict = static_cast<CKSoundDictionaryID*>(m_unkD4);
    for (uint32_t i = 0; i < 4; ++i) {
        if (dict->GetSound(i) != nullptr) CKSound_SetLoop(dict->GetSound(i), 1);  // 0x00112bc0, 0x00110fd0
    }
}

// 0x004a4d18 CKHkScrapShower_vfC8
void CKHkScrapShower::ApplyStatePreset(int32_t state) {
    const uint32_t bit = static_cast<uint32_t>(state != 0 ? m_unkD9 : m_unkD8) << 5;  // rlwinm 5,0,26: not masked to bit 5
    m_bitArray = (m_bitArray & 0xffffffdfu) | bit;
}

// 0x004a4d68 CKHkScrapShower_SetDefaultState
void CKHkScrapShower::SetDefaultState(int32_t flag) {
    CKHkActorBase::SetDefaultState(flag);  // KStub_Nop_3f72a0
    m_bitArray = (m_bitArray & 0xffffffdfu) | 0x20u;
}

// 0x004a4e28 CKHkScrapShower_OnDeactivate
void CKHkScrapShower::VfA4() {
    CKHkActorBase::VfA4();  // 0x003f7370
    if (m_i8Sound >= 0) {
        StopFallSound(static_cast<CKSoundDictionaryID*>(m_unkD4), m_i8Sound);
        m_i8Sound = -1;
    }
    if (m_i32ShadowIndex != -1) {
        ScrapCpnt(m_unk30)->UnregisterPieceShadow(static_cast<uint8_t>(m_i32ShadowIndex), m_pKGLObject, &m_shadowGround);
        m_i32ShadowIndex = -1;
        m_bitArray &= 0xffffffbfu;
    }
}

// 0x004a4f18 CKHkScrapShower_Update. Flags (+0x0c): bit 5 enabled, 6 a piece falls, 7 drop at once (message 0x998), 8 a
// hero is detected; bit 3 drops inside the box, bit 4 without shadow and surface test.
void CKHkScrapShower::Update(IKTime* clock) {
    // 0x003f6e68 WorldObjectBase_Update_Nop: the actor base's (empty).
    if ((m_bitArray & 0x20u) == 0 && (m_bitArray & 0x40u) == 0) return;
    // The detection: the detector group (+0x9c, vt+0xc0 0x9ccff0: its +0x4c bit 0) or the detector (+0x84). Entering
    // fires +0xc4, leaving +0xcc.
    bool detected;
    if (m_unk9c == nullptr) {
        CKDetectorBase* detector = static_cast<CKDetectorBase*>(m_unk84);
        detector->Detect();  // vt+0x50
        if (static_cast<uint8_t>(detector->GetDetectionType(0)) != 0) {  // vt+0x54
            QueueTriggerSignals(&m_unkC4);  // 0x00236338
            detected = true;
        } else if (static_cast<uint8_t>(detector->GetDetectionType(2)) != 0) {
            QueueTriggerSignals(&m_unkCC);
            detected = false;
        } else {
            detected = static_cast<uint8_t>(detector->GetDetectionType(1)) != 0;
        }
    } else if ((static_cast<CKHkDetectorGroup*>(m_unk9c)->m_unk4C[0] & 1u) != 0) {
        if ((m_bitArray & 0x100u) == 0) QueueTriggerSignals(&m_unkC4);
        detected = true;
    } else {
        if ((m_bitArray & 0x100u) != 0) QueueTriggerSignals(&m_unkCC);
        detected = false;
    }
    if (detected) {
        m_bitArray = (m_bitArray & 0xfffffeffu) | 0x100u;
    } else {
        m_bitArray &= 0xfffffeffu;
    }
    const uint32_t bits = m_bitArray;
    CKSoundDictionaryID* dict = static_cast<CKSoundDictionaryID*>(m_unkD4);
    CKScrapShowerCpnt* cpnt = ScrapCpnt(m_unk30);
    if ((bits & 0x40u) == 0) {
        // Waiting: the delay runs down, then a drop (at once with bit 7, else with a hero detected and a drop point).
        const float zero = 0.0f;  // TOC +0x61f0
        if (m_fDelay > zero) {  // ble: NaN skips the wait
            const float left = m_fDelay - clock->m_afDeltaTime[0];
            m_fDelay = left;
            if (!(left < zero)) return;  // blt
            m_fDelay = zero;
        }
        if ((bits & 0x80u) == 0) {
            if ((bits & 0x100u) == 0) return;
            if (PickDropPosition() == 0) return;
        }
        const RwFrame* frame = static_cast<CSGMovable*>(m_pKGLObject)->m_pRwFrame;
        m_shadowGround.m_v3Position.z = frame->modelling.pos.z;
        m_shadowGround.m_v3Position.x = frame->modelling.pos.x;
        m_shadowGround.m_v3Position.y = frame->modelling.pos.y;
        frame = static_cast<CSGMovable*>(m_pKGLObject)->m_pRwFrame;
        m_shadowGround.m_v3Normal.x = frame->modelling.up.x;
        m_shadowGround.m_v3Normal.z = frame->modelling.up.z;
        m_shadowGround.m_v3Normal.y = frame->modelling.up.y;
        m_shadowGround.m_fUnk18 = zero;
        if ((m_bitArray & 0x10u) == 0) {
            m_i32ShadowIndex = cpnt->RegisterPieceShadow(m_pKGLObject, &m_shadowGround);  // 0x004a6820
            if (m_i32ShadowIndex == -1) return;
        } else {
            m_i32ShadowIndex = 0;  // r26: bit 6, clear here
        }
        m_bitArray &= 0xffffff7fu;
        m_fDropTime = clock->m_afCurrentTime[0];
        m_bitArray = (m_bitArray & 0xffffffbfu) | 0x40u;
        if ((m_bitArray & 0x10u) == 0) {
            cpnt->SetPieceShadowScale(static_cast<uint8_t>(m_i32ShadowIndex), m_unk60[3]);  // 0x004a67a8 (+0x127)
        }
        if (m_i8Sound >= 0) StopFallSound(dict, m_i8Sound);
        const int32_t drawn = static_cast<int32_t>((static_cast<uint32_t>(Rand_Int()) >> 14) & 3u);
        if (static_cast<int32_t>(m_i8Sound) == drawn) {
            m_i8Sound = static_cast<int8_t>((static_cast<int32_t>(m_i8Sound) + 1) % 4);  // srawi / addze: signed
        } else {
            m_i8Sound = static_cast<int8_t>(drawn);
        }
        CKSound* sound = dict->GetSound(static_cast<uint32_t>(static_cast<int32_t>(m_i8Sound)));
        if (sound == nullptr) return;
        sound->Play(zero);                // 0x00111230
        sound->SetBaseVolume(m_unk60[5]);  // 0x00110ee8
        sound->SetSpeed(m_unk60[7]);       // 0x00110e98
        return;
    }
    // Falling: the shadow, volume and speed follow the fall; after +0x60 the piece is launched, at the fall time the drop
    // ends.
    const float elapsed = clock->m_afCurrentTime[0] - m_fDropTime;
    const float total = m_unk60[0] + m_fFallTime;
    const float dt = clock->m_afDeltaTime[0];
    const float sinceLaunch = elapsed - m_unk60[0];
    if (elapsed < total) {  // bge: NaN skips
        const float f = elapsed / total;
        if ((bits & 0x10u) == 0) {
            cpnt->SetPieceShadowScale(static_cast<uint8_t>(m_i32ShadowIndex), ppc::fmadds(1.0f - f, m_unk60[3], f * m_unk60[4]));
        }
        if (dict->GetSound(static_cast<uint32_t>(static_cast<int32_t>(m_i8Sound))) != nullptr) {
            dict->GetSound(static_cast<uint32_t>(static_cast<int32_t>(m_i8Sound)))
                ->SetBaseVolume(ppc::fmadds(1.0f - f, m_unk60[5], f * m_unk60[6]));
        }
        if (dict->GetSound(static_cast<uint32_t>(static_cast<int32_t>(m_i8Sound))) != nullptr) {
            dict->GetSound(static_cast<uint32_t>(static_cast<int32_t>(m_i8Sound)))
                ->SetSpeed(ppc::fmadds(1.0f - f, m_unk60[7], f * m_unk60[8]));
        }
    }
    if (!(sinceLaunch > 0.0f)) return;  // ble
    if (dt > sinceLaunch) {
        // The launch frame: from +0x2c above the node down to it.
        const RwFrame* frame = static_cast<CSGMovable*>(m_pKGLObject)->m_pRwFrame;
        CVector3 from;
        from.x = frame->modelling.pos.x;
        from.z = frame->modelling.pos.z;
        from.y = frame->modelling.pos.y + m_unk2c;
        frame = static_cast<CSGMovable*>(m_pKGLObject)->m_pRwFrame;
        const CVector3 to = {frame->modelling.pos.x, frame->modelling.pos.y, frame->modelling.pos.z};
        cpnt->LaunchScrapAtPoint(&from, &to, m_unkC0, this);  // 0x004a6c38
    }
    if (!(m_fFallTime <= sinceLaunch)) return;  // cror lt|eq
    if ((m_bitArray & 0x10u) == 0) {
        cpnt->UnregisterPieceShadow(static_cast<uint8_t>(m_i32ShadowIndex), m_pKGLObject, &m_shadowGround);  // 0x004a6cb0
    }
    m_i32ShadowIndex = -1;
    StopFallSound(dict, m_i8Sound);
    m_bitArray &= 0xffffffbfu;
    const uint32_t step = m_ui8Step;
    const float delay = DrawDelay(step);
    m_ui8Step = static_cast<uint8_t>(static_cast<int32_t>(step + 1) % static_cast<int32_t>(m_ui8NbUnk58));  // divw
    m_fDelay = delay;
    const RwFrame* frame = static_cast<CSGMovable*>(m_pKGLObject)->m_pRwFrame;
    const float* hero = static_cast<CKHkS08Hero*>(ScrapHeroGroup()->m_apControlledHeroes[0])->GetPositionPtr();  // 0x00361968
    const float dy = hero[1] - frame->modelling.pos.y;
    const float dx = hero[0] - frame->modelling.pos.x;
    const float dz = hero[2] - frame->modelling.pos.z;
    const float distanceSq = ppc::fmadds(dz, dz, ppc::fmadds(dx, dx, dy * dy));
    const CVector3 at = {frame->modelling.pos.x, frame->modelling.pos.y, frame->modelling.pos.z};
    cpnt->TryCameraShake(distanceSq, &at);  // 0x004a6928 (the frame's position)
}

// 0x004a57f0 CKHkScrapShower_MessageProc
int32_t CKHkScrapShower::MessageProc(uint16_t message, void* data) {
    const int32_t base = CKHkActorBase::MessageProc(message, data);  // 0x003f7148
    int32_t own = 1;
    switch (message) {
    case 0x996:
        m_ui8Step = 0;
        m_fDelay = DrawDelay(0);
        own = 0;
        m_bitArray = (m_bitArray & 0xffffffdfu) | 0x20u;
        break;
    case 0x997:
        own = 0;
        m_bitArray &= 0xffffffdfu;
        break;
    case 0x998:
        own = 0;
        if ((m_bitArray & 0x20u) != 0 && (m_bitArray & 0x40u) == 0) {
            m_fDelay = 0.0f;
            m_bitArray = (m_bitArray & 0xffffff7fu) | 0x80u;
        }
        break;
    case 0xc32: {
        ScrapHazardQuery* query = static_cast<ScrapHazardQuery*>(data);
        query->m_knock[0] = m_unkA4[0];
        query->m_knock[1] = m_unkA4[1];
        query->m_knock[2] = m_unkA4[2];
        const RwFrame* frame = static_cast<CSGMovable*>(m_pKGLObject)->m_pRwFrame;
        query->m_point.x = frame->modelling.pos.x;
        query->m_point.z = frame->modelling.pos.z;
        query->m_point.y = frame->modelling.pos.y;
        own = 0;
        query->m_damage = static_cast<CKHkS08Hero*>(query->m_hero)->IsPlayerControlled() != 0 ? m_unkA0 : 0;  // 0x00362af0
        break;
    }
    default:
        break;
    }
    if (base == 3 || own == 3) return 3;
    if (base == 2 || own == 2) return 2;
    return base == 0 ? 0 : own;
}

// 0x004a5aa8 CKHkScrapShower_Restart
void CKHkScrapShower::Restart() {
    m_ui8Step = 0;
    m_fDelay = 0.0f;
    m_i8Sound = -1;
    m_bitArray &= 0xfffffe3fu;
    if ((m_bitArray & 4u) != 0) return;
    // BUG(original): the sound was set to -1 just above, so this stop never runs.
    if (m_i8Sound >= 0) {
        StopFallSound(static_cast<CKSoundDictionaryID*>(m_unkD4), m_i8Sound);
        m_i8Sound = -1;
    }
    if (m_i32ShadowIndex != -1) {
        ScrapCpnt(m_unk30)->UnregisterPieceShadow(static_cast<uint8_t>(m_i32ShadowIndex), m_pKGLObject, &m_shadowGround);
        m_i32ShadowIndex = -1;
    }
}
