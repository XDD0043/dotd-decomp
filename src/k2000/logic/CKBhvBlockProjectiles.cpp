// CKBhvBlockProjectiles.cpp - reconstructed original translation unit 0x5c3088-0x5c4e50 (GAME_TOC2, main_toc2), 28 functions, 23 live.
// Primary class: CKBhvBlockProjectiles  key 0xa7cc  category Logic  size ?  vtable 0xb2fc60
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x5c3088  CKBhvBlockProjectiles_Delete
//   [ ] 0x5c30d8  CKBhvBlockProjectiles_FindTarget_maybe  [dead]
//   [ ] 0x5c3228  CKBhvBlockProjectiles_IsTargetValid_maybe  [dead]
//   [x] 0x5c32d8  CKBhvBlockProjectiles_LaunchAtTarget_maybe
//   [ ] 0x5c3428  CKBhvBlockProjectiles_IsPlayingSecondAnim_maybe  [dead]
//   [x] 0x5c34b0  CKBhvBlockProjectiles_FireOnAnimMark_maybe
//   [ ] 0x5c3718  CKBhvBlockProjectiles_PlayFirstAnim_maybe  [dead]
//   [ ] 0x5c3820  CKBhvBlockProjectiles_PlaySecondAnim_maybe  [dead]
//   [x] 0x5c3928  CKBhvBlockProjectiles_GetRandomizedInterval_maybe
//   [x] 0x5c3988  CKBhvBlockProjectiles_vf68
//   [ ] 0x5c39f8  CKBhvBlockProjectiles_Save
//   [x] 0x5c3a20  CKBhvBlockProjectiles_RecursiveRegistration  (the base's only: KBase9C8C 0x5c57b8 returns 1)
//   [x] 0x5c3a48  CKBhvBlockProjectiles_Destroy
//   [x] 0x5c3a70  CKBhvBlockProjectiles_Construct_2  (the constructor)
//   [x] 0x5c3aa8  CKBhvBlockProjectiles_Construct
//   [x] 0x5c3ae0  CKBhvBlockProjectiles_DeleteArray
//   [x] 0x5c3b80  CKBhvBlockProjectiles_BaseDestructor
//   [ ] 0x5c3bb0  RegisterCKBhvBlockProjectilesClass
//   [ ] 0x5c3c38  _GLOBAL__D_5c3c38
//   [ ] 0x5c3c48  _GLOBAL__I_5c3c48
//   [x] 0x5c3c58  CKBhvBlockProjectiles_DeletingDestructor
//   [x] 0x5c3ca0  CKBhvBlockProjectiles_Destructor
//   [x] 0x5c3cd0  CKBhvBlockProjectiles_CreateArray
//   [x] 0x5c3d80  CKBhvBlockProjectiles_Create
//   [x] 0x5c3dd8  CKBhvBlockProjectiles_FaceTarget_maybe
//   [x] 0x5c3f88  CKBhvBlockProjectiles_Update_maybe
//   [x] 0x5c4470  CKBhvBlockProjectiles_vf64
//   [x] 0x5c4850  CKBhvBlockProjectiles_Load
//
//   [x] 0x9cd408  CKBhvBlockProjectiles_IsKindOfClass  [inline]
//   [ ] 0x9cd440  CKBhvBlockProjectiles_GetClassType  [inline]
//   [ ] 0x9cd448  CKBhvBlockProjectiles_GetClassID  [inline]
#include "k2000/logic/CKBhvBlockProjectiles.h"

#include <cmath>

#include "Renderware/rwcore/RwCamera.h"
#include "Spyro2008/hooks/IKHkEnemy.h"
#include "crt/ppc_ops.h"
#include "k2000/dictionaries/CAnimationDictionary.h"
#include "k2000/graphical/animation/CAnimationManager.h"
#include "k2000/io/IKFile.h"
#include "k2000/logic/CDefaultGameManager.h"
#include "k2000/logic/CKMarkedFX.h"
#include "k2000/logic/CKProjectileAccessor.h"
#include "k2000/logic/CSGHotSpot.h"
#include "k2000/logic/KBase9CCC.h"
#include "k2000/logic/ai/CKMarkerBeacon.h"
#include "k2000/logic/animation/CKAnimationMarkContainer.h"
#include "k2000/logic/cameras/CKAimCamembert.h"
#include "k2000/logic/sound/CKMarkedSoundDico.h"
#include "k2000/math/CMatrix34.h"
#include "k2000/math/Quat.h"
#include "k2000/misc/ClassRegistry.h"
#include "k2000/misc/Engine.h"
#include "k2000/misc/IKGrpEnemy.h"
#include "k2000/scenegraph/CAnimatedNode.h"
#include "k2000/scenegraph/CSGMovable.h"
#include "k2000/system/IKTime.h"

// 0x005c4850 CKBhvBlockProjectiles_Load: the base's Load, then (level data only) the fields in the file's
// order.
int32_t CKBhvBlockProjectiles::Load(IKFile* file, int32_t type) {
    KBase9C8C::Load(file, type);
    if (type == K_LEVEL_PLATEFORMS) {
        IKFile_ReadRef(file, &m_unk0c);
        IKFile_ReadRef(file, &m_unk2c);
        ReadF32LE(file, &m_unk14);
        ReadF32LE(file, &m_unk10);
        ReadF32LE(file, &m_unk1c);
        ReadF32LE(file, &m_unk20);
        IKFile_ReadRef(file, &m_unk28);
        IKFile_ReadRef(file, &m_unk30);
        ReadU32LEWords(file, reinterpret_cast<uint32_t*>(m_unk38), 3);
        IKFile_ReadRef(file, &m_unk5c);
        IKFile_ReadRef(file, &m_unk44);
        ReadF32LE(file, &m_unk60);
        IKFile_ReadRef(file, &m_unk08);
        IKFile_ReadRef(file, &m_unk04);
        IKFile_ReadRef(file, &m_unk64);
    }
    return 1;
}

namespace {
KBase9CCC* User(IKSerializable* user) { return static_cast<KBase9CCC*>(user); }
CAnimatedNode* UserNode(IKSerializable* user) { return static_cast<CAnimatedNode*>(User(user)->GetAnimatedNode()); }  // vt+0x54
CSGMovable* UserMovable(IKSerializable* user) { return static_cast<CSGMovable*>(User(user)->GetMovable()); }  // vt+0x58
CKAimCamembert* Sector(IKSerializable* sector) { return static_cast<CKAimCamembert*>(sector); }
// The dictionary's words (+0x04): 0 the idle animation, 1 the shooting one.
uint32_t AnimWord(IKSerializable* dictionary, uint32_t index) {
    return static_cast<uint32_t>(static_cast<CAnimationDictionary*>(dictionary)->m_apAnimations[index]);
}
// The LTM position of a hook's node (RwFrame +0x80).
const RwV3d& HookPosition(IKSerializable* hook) {
    return FrameLtm(static_cast<CSGMovable*>(static_cast<IKHook*>(hook)->m_pKGLObject)->m_pRwFrame)->pos;
}
// The game manager's vt+0x254 (0x009c6d10 CKS08GameManager_vf254): the activation marks' channel (0x1a, "MarkI_Activate").
constexpr uint32_t kActivateMarkChannel = 0x1a;
// The animation `word` played on the user's node: cut from 0 (CAnimatedNode_PlayAnim_maybe) when the blend time is
// not above 0 (fcmpu + cror: a NaN blends), else blended from 0 (CAnimatedNode_CrossfadeToAnim_maybe, mode 1).
void PlayOrBlend(IKSerializable* user, float blend, uint32_t word) {
    if (blend <= 0.0f) {  // TOC2 -0x6090 0.0
        UserNode(user)->PlayAnim(0.0, word, 0);  // 0x000c98b8
    } else {
        UserNode(user)->CrossfadeToAnim(blend, 0.0, word, 1);  // 0x000c8eb0
    }
}
}  // namespace

// 0x005c3928 CKBhvBlockProjectiles_GetRandomizedInterval_maybe: the interval +0x1c plus a random part in [-1, 1] times
// +0x20 (rand() & 0xffff over 65535.0, doubled; fmsubs then fadds). Enter and Update inline it.
float CKBhvBlockProjectiles::GetRandomizedInterval() {
    const uint16_t r = static_cast<uint16_t>(Rand_Int());
    const float unit = static_cast<float>(static_cast<double>(r)) / 65535.0f;  // TOC2 -0x608c
    return ppc::fmsubs(unit + unit, m_unk20, m_unk20) + m_unk1c;
}

// 0x005c4470 CKBhvBlockProjectiles_vf64: the block entered (the argument is not used: the block's own user +0x0c). The
// idle animation starts; the shot timer restarts, the next interval is drawn, the target forgotten. With a marker
// (+0x44) the node is placed at it (its quaternion as the rotation, CSGMovable_SetLocalMatrix_maybe) and keeps its
// direction (the matrix's at row), else it keeps its LTM's at row; the LTM made current (vt+0x50) either way. The
// aiming sector takes the node's LTM position and that direction (vt+0x5c). KStub_Nop_5cebf0 (the marked effects and
// the user's vt+0x50) does nothing.
void CKBhvBlockProjectiles::Enter(IKSerializable* /*user*/) {
    const uint32_t idle = AnimWord(m_unk2c, 0);
    if (idle != 0) PlayOrBlend(m_unk0c, m_unk10, idle);
    m_unk18 = 0.0f;
    const float interval = GetRandomizedInterval();
    m_unk34 = nullptr;
    m_unk24 = interval;
    const CKMarkerBeacon* marker = static_cast<const CKMarkerBeacon*>(m_unk44);
    if (marker != nullptr) {
        alignas(16) CMatrix34 matrix;
        float q[4] = {marker->m_qOrientation[0], marker->m_qOrientation[1], marker->m_qOrientation[2],
                      marker->m_qOrientation[3]};
        Quat_ToMatrixNormalizing(q, &matrix);  // 0x00241d78 (on +0x10)
        matrix.m_pos.z = marker->m_v3Position.z;
        matrix.m_pos.x = marker->m_v3Position.x;
        matrix.m_pos.y = marker->m_v3Position.y;
        matrix.m_ui32Flags &= 0xfffdffffu;
        m_unk38[0] = matrix.m_at.x;
        m_unk38[1] = matrix.m_at.y;
        m_unk38[2] = matrix.m_at.z;
        UserMovable(m_unk0c)->SetLocalMatrix(reinterpret_cast<const RwMatrix*>(&matrix));  // 0x000d0be8
        UserMovable(m_unk0c)->ForceWorldMatrixUpdate();                                     // vt+0x50
    } else {
        UserMovable(m_unk0c)->ForceWorldMatrixUpdate();                    // vt+0x50
        const RwV3d& at = FrameLtm(UserMovable(m_unk0c)->m_pRwFrame)->at;  // RwFrame +0x70
        m_unk38[0] = at.x;
        m_unk38[1] = at.y;
        m_unk38[2] = at.z;
    }
    const RwV3d& p = FrameLtm(UserMovable(m_unk0c)->m_pRwFrame)->pos;  // +0x80
    const CVector3 position = {p.x, p.y, p.z};
    const CVector3 direction = {m_unk38[0], m_unk38[1], m_unk38[2]};
    Sector(m_unk30)->SetOriginAndDirection(&position, &direction);  // vt+0x5c
}

// 0x005c3988 CKBhvBlockProjectiles_vf68: the block left: the target forgotten. KStub_Nop_5cebf8 (the marked effects and
// the user's vt+0x50) does nothing.
void CKBhvBlockProjectiles::Leave(IKSerializable* /*user*/) { m_unk34 = nullptr; }

// 0x005c3f88 CKBhvBlockProjectiles_Update_maybe. The node's animation advances by the frame's dt (+0x1c). A target that
// still has a squad (+0x168), is awake (life flag bit 3 clear) and lies in the sector (vt+0x50) is kept; otherwise the
// enemy group's active enemies (+0x58, +0x120) are scored and the best one taken (a score above the best so far, which
// starts at 0: bge, a NaN is not taken). Then the node faces the target (FaceTarget). While the shooting animation plays
// its activation mark fires (FireOnAnimMark), and at its end the idle animation comes back and a new interval is drawn.
// Otherwise the shot timer runs; past the interval (fcmpu + cror: not a NaN) with a target the shooting animation starts
// (when the dictionary has one) and the timer restarts. Then the sound marks (from the node) and the marked effects.
void CKBhvBlockProjectiles::Update(IKTime* clock) {
    const float dt = clock->m_afDeltaTime[0];  // +0x1c
    UserNode(m_unk0c)->AddAnimTime(dt);         // 0x000c9638
    float score;  // the sector's answer (sp+0x70; ScoreTarget always writes it)
    IKHkEnemy* target = static_cast<IKHkEnemy*>(m_unk34);
    bool keep = false;
    if (target != nullptr && target->m_pGroupSquad != nullptr && (target->m_bitArray & 8u) == 0) {
        const RwV3d& p = HookPosition(target);
        keep = Sector(m_unk30)->ScoreTarget(reinterpret_cast<const CVector3*>(&p), &score) != 0;  // vt+0x50
    }
    if (!keep) {
        m_unk34 = nullptr;
        IKGrpEnemy* group = static_cast<IKGrpEnemy*>(g_pEngine->m_gameManager->m_unk04[0]);  // +0x8c -> +0x04
        if (group != nullptr && group->m_ui32NbActiveEnemies != 0) {
            const uint32_t count = group->m_ui32NbActiveEnemies;  // +0x120
            score = 0.0f;
            float best = 0.0f;
            for (uint32_t i = 0; i != count; ++i) {
                IKHkEnemy* enemy = static_cast<IKHkEnemy*>(group->m_apActiveEnemies[i]);  // +0x58
                if (enemy->m_pGroupSquad == nullptr) continue;
                if ((enemy->m_bitArray & 8u) != 0) continue;
                const RwV3d& p = HookPosition(enemy);
                if (Sector(m_unk30)->ScoreTarget(reinterpret_cast<const CVector3*>(&p), &score) == 0) continue;
                if (!(best < score)) continue;  // bge
                best = score;
                m_unk34 = enemy;
            }
        }
    }
    FaceTarget();
    const uint32_t active = UserNode(m_unk0c)->GetActiveAnim();  // 0x000c9720
    if (AnimWord(m_unk2c, 1) == active) {
        FireOnAnimMark();
        if (UserNode(m_unk0c)->IsAnimEndReached(dt)) {  // 0x000ca368
            const uint32_t idle = AnimWord(m_unk2c, 0);
            if (idle != 0) PlayOrBlend(m_unk0c, m_unk10, idle);
            m_unk24 = GetRandomizedInterval();
        }
    } else {
        const float elapsed = m_unk18 + dt;
        m_unk18 = elapsed;
        if (m_unk24 <= elapsed && m_unk34 != nullptr) {
            const uint32_t shoot = AnimWord(m_unk2c, 1);
            if (shoot != 0) PlayOrBlend(m_unk0c, m_unk14, shoot);
            m_unk18 = 0.0f;
        }
    }
    CKMarkedSoundDico* sounds = static_cast<CKMarkedSoundDico*>(m_unk08);
    sounds->SetSourceMode(0);            // 0x005cdf60
    sounds->UpdateFromAnimMarks(clock);  // vt+0x50
    static_cast<CKMarkedFX*>(m_unk04)->UpdateFromAnimMarks(clock);  // 0x005d0640
}

// 0x005c3dd8 CKBhvBlockProjectiles_FaceTarget_maybe: the flat direction to the target (LTM positions, y 0) or the stored
// direction (+0x38, y 0), normalised unless its length (Math_Sqrtf of fmadds) is 0 (1.0 / length times each component),
// becomes the node's at with its modelling up (CSGMovable_SetOrientationFromAtUp, the frame's +0x20).
void CKBhvBlockProjectiles::FaceTarget() {
    CVector3 at;
    if (m_unk34 != nullptr) {
        const RwV3d& t = HookPosition(m_unk34);
        const RwV3d& n = FrameLtm(UserMovable(m_unk0c)->m_pRwFrame)->pos;  // +0x80
        at.x = t.x - n.x;
        at.z = t.z - n.z;
    } else {
        at.x = m_unk38[0];
        at.z = m_unk38[2];
    }
    at.y = 0.0f;
    const float squared = ppc::fmadds(at.z, at.z, ppc::fmadds(at.x, at.x, 0.0f));
    const float length = static_cast<float>(std::sqrt(static_cast<double>(squared)));  // 0x00010690 Math_Sqrtf
    if (length != 0.0f) {
        const float inverse = 1.0f / length;  // TOC2 -0x6094
        at.z = at.z * inverse;
        at.x = at.x * inverse;
        at.y = at.y * inverse;
    }
    CSGMovable* node = UserMovable(m_unk0c);
    const RwV3d& up = UserMovable(m_unk0c)->m_pRwFrame->modelling.up;  // RwFrame +0x20
    const CVector3 upVector = {up.x, up.y, up.z};
    node->SetOrientationFromAtUp(&at, &upVector);  // 0x000d0918
}

// 0x005c34b0 CKBhvBlockProjectiles_FireOnAnimMark_maybe: the node's current animation (or else its active one; neither:
// nothing). The time now is brought into [0, duration) (the bge / blt and cror loops: a NaN stays); the activation mark
// (the game manager's channel, -1 none) crossed between the evaluated time and it launches a projectile.
void CKBhvBlockProjectiles::FireOnAnimMark() {
    RtAnimAnimation* animation = UserNode(m_unk0c)->GetCurrentAnim();  // 0x000c96d8
    if (animation == nullptr) {
        // DOTD: GetActiveAnim answers the dictionary word; the original's +0x5c is the animation itself.
        animation = CAnimationManager_GetAnimation(UserNode(m_unk0c)->GetActiveAnim());  // 0x000c9720
        if (animation == nullptr) return;
    }
    float t = UserNode(m_unk0c)->GetAnimTimeNow();                       // 0x000c95f0
    const float duration = UserNode(m_unk0c)->GetCurrentAnimDuration();  // 0x000c9768
    if (!(t >= 0.0f)) {  // bge
        do {
            t = t + duration;
        } while (t < 0.0f);
    }
    const float end = duration + 0.0f;
    while (end <= t) t = t - duration;
    const float previous = UserNode(m_unk0c)->GetCurrentAnimTime();  // 0x000c95a8
    const uint32_t channel = kActivateMarkChannel;                   // vt+0x254
    if (channel == 0xffffffffu) return;
    AnimMark* mark = Anim_GetMarkById(animation, channel);  // 0x00078830
    if (mark == nullptr) return;
    if (AnimMark_CrossedValueR3(mark, previous, t) == 0) return;  // vt+0x1c
    LaunchAtTarget();
}

// 0x005c32d8 CKBhvBlockProjectiles_LaunchAtTarget_maybe: with a projectile type (+0x5c's +0x04), a hot spot and a target:
// the target is asked for its aim point (message 0x400 with its node's LTM position, index 0, no hot spot, the user as
// the asker) and a projectile leaves the hot spot's world position for that point (the speed +0x60, the damage +0x64,
// the user's owner, vt+0x50).
void CKBhvBlockProjectiles::LaunchAtTarget() {
    CKProjectileAccessor* projectiles = static_cast<CKProjectileAccessor*>(m_unk5c);
    if (projectiles->m_pProjectileType == nullptr || m_unk28 == nullptr || m_unk34 == nullptr) return;
    CVector3 from;
    static_cast<CSGHotSpot*>(m_unk28)->GetWorldPosition(&from);  // 0x000ce790
    struct {
        uint8_t m_ui8Index;          // +0x00
        CVector3 m_point;            // +0x04
        IKSerializable* m_pHotSpot;  // +0x10
        IKSerializable* m_pAsker;    // +0x14
    } query;
    IKSerializable* target = m_unk34;
    const RwV3d& p = HookPosition(target);
    query.m_pAsker = m_unk0c;
    query.m_point = {p.x, p.y, p.z};
    query.m_ui8Index = 0;
    query.m_pHotSpot = nullptr;
    target->MessageProc(0x400, &query);  // vt+0x1c
    projectiles->LaunchAtPointEx(&from, &query.m_point, m_unk60, m_unk64, User(m_unk0c)->GetOwner());  // 0x001f2c50
}
