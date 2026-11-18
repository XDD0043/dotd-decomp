// CKS08EnemyElement.cpp - reconstructed original translation unit 0x26b348-0x26c918 (GAME_TOC1, main_toc1), 18 functions, 18 live.
// Primary class: CKS08EnemyElement  key 0x7a0c  category Logic  size 0x64  vtable 0xb21a80
// Other owners: CKS08Accessory (3), EnemyArmorPart (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x26b348  CKS08EnemyElement_Delete
//   [x] 0x26b398  CKS08EnemyElement_BreakOff_maybe
//   [x] 0x26b738  CKS08EnemyElement_DeleteArray
//   [x] 0x26b7d8  CKS08EnemyElement_Create
//   [ ] 0x26b810  RegisterCKS08EnemyElementClass
//   [ ] 0x26b898  _GLOBAL__D_26b898
//   [ ] 0x26b8a8  _GLOBAL__I_26b8a8
//   [x] 0x26b8b8  CKS08Accessory_AttachToOwner_maybe
//   [x] 0x26b9a8  EnemyArmorPart_ApplyDamage  (CKHkS08Enemy.cpp ApplyArmourPartDamage)
//   [x] 0x26bb58  CKS08Accessory_UpdateMotion_maybe
//   [x] 0x26c158  CKS08EnemyElement_vf50
//   [x] 0x26c258  CKS08EnemyElement_CreateArray
//   [ ] 0x26c2e8  CKS08EnemyElement_Save
//   [x] 0x26c2f0  CKS08EnemyElement_PostLoad
//   [x] 0x26c3f8  CKS08EnemyElement_RecursiveRegistration  (returns 1: the root's empty slot)
//   [x] 0x26c400  CKS08EnemyElement_Destroy  (empty: the root's default)
//   [x] 0x26c408  CKS08Accessory_LaunchFromHit_maybe
//   [x] 0x26c7b8  CKS08EnemyElement_Load
//
//   [ ] 0x9bbce8  CKS08EnemyElement_GetClassType  [inline]
//   [ ] 0x9bbcf0  CKS08EnemyElement_GetClassID  [inline]
//   [ ] 0x9bbcf8  CKS08EnemyElement_vf54  [inline]
//   [ ] 0x9bbd00  CKS08EnemyElement_IsKindOfClass  [inline]
//   [ ] 0x9bbd20  CKS08EnemyElement_DeletingDestructor  [inline]
//   [ ] 0x9bbd60  CKS08EnemyElement_Destructor  [inline]
#include "Spyro2008/logic/CKS08EnemyElement.h"
#include "k2000/components/CKCameraEventCpnt.h"
#include "k2000/scenegraph/CSGMovable.h"
#include "k2000/system/IKTime.h"
#include "k2000/services/CollisionDatas.h"
#include "k2000/services/CKSrvFx.h"
#include "k2000/services/CKSrvCollision.h"
#include "k2000/misc/Mat4.h"
#include "k2000/logic/physics/CGround.h"
#include "k2000/logic/fx/CKExplosionNodeFx.h"
#include "k2000/hooks/GroundContact.h"
#include "k2000/cameras/CKSrvCamera.h"
#include "crt/ppc_ops.h"
#include "Spyro2008/logic/CKS08Damage.h"
#include "Spyro2008/logic/CKS08AccessoryManager.h"
#include "Spyro2008/logic/CKS08AccessoryConfig.h"
#include "Spyro2008/groups/CKGrpS08Enemy.h"
#include "Renderware/rwcore/RwCamera.h"
#include <cstring>
#include <cmath>
#include "k2000/scenegraph/CSGLeaf.h"
#include "k2000/logic/CDefaultGameManager.h"
#include "k2000/misc/Engine.h"
#include "k2000/misc/IKGrpEnemy.h"

#include "Spyro2008/logic/memory/CKS08EnemyElementPool.h"
#include "k2000/core/Stub.h"
#include "k2000/io/IKFile.h"
#include "k2000/scenegraph/CSGBranch.h"

// 0x0026c7b8 CKS08EnemyElement_Load: two references, whatever the type.
int32_t CKS08EnemyElement::Load(IKFile* file, int32_t /*type*/) {
    IKFile_ReadRef(file, &m_pNode);
    IKFile_ReadRef(file, &m_pGlow);
    return 1;
}

// 0x0026c2f0 CKS08EnemyElement_PostLoad: the element free (+0x54); its node moved under the enemy group's first +0x40
// node and hidden (flag 4), as is the glow.
int32_t CKS08EnemyElement::PostLoad(int32_t /*type*/) {
    m_inUse54 = 0;
    CSGLeaf* node = static_cast<CSGLeaf*>(m_pNode);
    if (node != nullptr) {
        if (node->m_pParent != nullptr) node->m_pParent->RemoveChild(node);  // vt+0x78
        const IKGrpEnemy* group = static_cast<const IKGrpEnemy*>(g_pEngine->m_gameManager->m_unk04[0]);  // TOC +0x6c8
        static_cast<CSGBranch*>(group->m_vUnk40.m_pBlock[0])->AddChild(node);  // vt+0x70
        node->m_sgProperties |= 4u;
    }
    if (m_pGlow != nullptr) static_cast<CSGLeaf*>(m_pGlow)->m_sgProperties |= 4u;
    return 1;
}

// 0x0026b8b8 CKS08Accessory_AttachToOwner_maybe
void CKS08EnemyElement::AttachToOwner(IKSerializable* pool) {
    m_pPool58 = pool;
    if (pool != nullptr) m_unk44 = static_cast<CKS08EnemyElementPool*>(pool)->m_unk18;
    m_v10 = CVector3{0.0f, 0.0f, 0.0f};  // the zero vector 0x00c50d64 (TOC +0x6f0)
    CSGLeaf* glow = static_cast<CSGLeaf*>(m_pGlow);
    if (glow == nullptr) return;
    glow->m_sgProperties &= 0xfffffffbu;  // shown (rlwinm 29 / 3)
    CSGBranch* parent = glow->m_pParent;
    if (static_cast<IKSerializable*>(parent) == m_pNode) return;
    parent->RemoveChild(glow);                             // vt+0x78
    static_cast<CSGBranch*>(m_pNode)->AddChild(glow);      // vt+0x70
}

namespace {
// 0x00010690 Math_Sqrtf: the double square root rounded to float.
float SqrtF(float x) { return static_cast<float>(std::sqrt(static_cast<double>(x))); }

CKGrpS08Enemy* EnemyGroupOfElements() {  // 0x00276f58 GetEnemyGroup (TOC +0x6c8: the engine; +0x8c, +0x04)
    return static_cast<CKGrpS08Enemy*>(g_pEngine->m_gameManager->m_unk04[0]);
}

// The scripted camera of the enemy group (+0x264) is the service's active one (+0xe0c) under a current camera (+0x474).
bool GroupCameraActive() {
    const CKSrvCamera* cameras = static_cast<const CKSrvCamera*>(g_pEngine->m_srvCamera);
    return cameras->m_pCurrentCamera != nullptr && cameras->m_pScriptedCameraHandle != nullptr &&
           EnemyGroupOfElements()->m_pUnk264 == cameras->m_pScriptedCameraHandle;
}

// The flight's end: the group's scripted camera released when active (ScriptedCameraHandle_Release_maybe 0x166130), then
// BreakOff.
void EndFlight(CKS08EnemyElement* element) {
    if (GroupCameraActive()) static_cast<CKCameraEventCpnt*>(EnemyGroupOfElements()->m_pUnk264)->Release();
    element->BreakOff();  // 0x0026b398
}
}  // namespace

// 0x0026bb58 CKS08Accessory_UpdateMotion_maybe. In flight (+0x48 clear): gravity (the config's +0x08 x +0x04) and the
// push's share of the frame while it lasts, both over the config's +0x04 (a mass_maybe) into the velocity; the position
// moved, swept against the walls (a 0.3 cylinder: a hit lands it with no time left); the ground under it (the manager's
// probe): touched (status 1 / 2) it bounces (the velocity's y made positive, the velocity and the turn rates scaled by
// the config's +0x18, the position put on the ground) until the config's bounce count or a ground with flag 0x200,
// then it lands; no ground (status 3) ends the flight. The node follows and turns. Landed: the time +0x40 counts down
// to the end. An element part (pool type 0..7) with camera time +0x60 left steers the group's scripted camera
// (STUB(C2.8: camera)).
void CKS08EnemyElement::UpdateMotion(IKTime* clock) {
    if (m_pPool58 == nullptr) return;
    const float dt = clock->m_afDeltaTime[0];
    const CKS08AccessoryConfig* config =
        static_cast<const CKS08AccessoryConfig*>(static_cast<CKS08EnemyElementPool*>(m_pPool58)->m_pConfig);
    if (config != nullptr && dt > 0.0f) {
        if (m_unk48 != 0) {
            if (!(m_unk40 > 0.0f)) {
                EndFlight(this);
                return;
            }
            m_unk40 = m_unk40 - dt;
        } else {
            // The null vector (0x00c50d64, TOC +0x6f0) plus 0 and the gravity.
            float ax = 0.0f + 0.0f;
            float ay = ppc::fmadds(-config->m_unk08, config->m_unk04, 0.0f);
            float az = 0.0f + 0.0f;
            if (m_unk28 > 0.0f) {
                const float share = (dt >= m_unk28 ? m_unk28 : dt) / dt;
                m_unk28 = m_unk28 - dt;
                az = ppc::fmadds(share, m_v1c.z, az);
                ax = ppc::fmadds(share, m_v1c.x, ax);
                ay = ppc::fmadds(share, m_v1c.y, ay);
            }
            const float step = dt / config->m_unk04;
            m_v10.z = ppc::fmadds(az, step, m_v10.z);
            m_v10.x = ppc::fmadds(ax, step, m_v10.x);
            m_v10.y = ppc::fmadds(ay, step, m_v10.y);
            const CVector3 from = m_v04;
            m_v04.x = ppc::fmadds(dt, m_v10.x, from.x);
            m_v04.y = ppc::fmadds(dt, m_v10.y, from.y);
            m_v04.z = ppc::fmadds(dt, m_v10.z, from.z);
            CLine line;
            line.m_start = from;
            line.m_VectDir.x = m_v04.x - from.x;
            line.m_VectDir.y = m_v04.y - from.y;
            line.m_VectDir.z = m_v04.z - from.z;
            CSlideGroundEdgeDatasOut out;
            const uint8_t wall = static_cast<CKSrvCollision*>(g_pEngine->m_srvCollision)
                                     ->ResolveSweptCylinderWalls(&line, 0.3f, 0.3f, &out, nullptr, nullptr, 1);  // 0x0019aa68, TOC +0x6f4
            if (static_cast<uint32_t>(wall) - 1u <= 2u) {
                m_unk40 = 0.0f;
                m_unk48 = 1;
            }
            const CGroundContactDatasInOut* ground =
                static_cast<CKS08AccessoryManager*>(EnemyGroupOfElements()->m_pUnk1ec)->ProbeGround(&m_v04);  // 0x002c7598
            const int32_t status = static_cast<int32_t>(ground->m_eContactStatus);
            const float dh = ground->m_fdH;
            if (status == 1 || status == 2) {
                if (m_unk3c < static_cast<uint32_t>(config->m_unk1c) &&
                    (static_cast<const CGround*>(ground->m_pGround)->m_ui16PropertiesFlags & 0x200u) == 0) {
                    m_v10.y = std::fabs(m_v10.y);
                    const float rebound = config->m_unk18;
                    m_v10.x = rebound * m_v10.x;
                    m_v10.z = rebound * m_v10.z;
                    m_v10.y = rebound * m_v10.y;
                    m_afSpin30[0] = m_afSpin30[0] * rebound;
                    m_afSpin30[1] = m_afSpin30[1] * rebound;
                    m_afSpin30[2] = m_afSpin30[2] * rebound;
                    m_v04.y = dh + m_v04.y;
                    m_unk3c = m_unk3c + 1;
                } else {
                    m_unk48 = 1;
                }
            } else if (status == 3) {
                EndFlight(this);
                return;
            }
            RwFrame* frame = static_cast<CSGMovable*>(m_pNode)->m_pRwFrame;
            frame->modelling.pos.x = m_v04.x;
            frame->modelling.pos.y = m_v04.y;
            frame->modelling.pos.z = m_v04.z;
            frame->modelling.flags &= 0xfffdffffu;
            RwFrame_MarkDirty(frame);  // 0x00010698
            // The turns about the frame's own axes, in degrees (TOC +0x6f8, 57.29578).
            CMatrix34* m = reinterpret_cast<CMatrix34*>(&static_cast<CSGMovable*>(m_pNode)->m_pRwFrame->modelling);
            Mat4_RotateInPlace(m, &m->m_right, dt * m_afSpin30[0] * 57.29578f);  // 0x00240498
            Mat4_RotateInPlace(m, &m->m_up, dt * m_afSpin30[1] * 57.29578f);
            Mat4_RotateInPlace(m, &m->m_at, dt * m_afSpin30[2] * 57.29578f);
        }
        if (m_pPool58 == nullptr) return;
    }
    const int32_t type = static_cast<CKS08EnemyElementPool*>(m_pPool58)->m_unk14;
    if (type < 0 || type == 8) return;
    if (!(m_unk60 > 0.0f) || !GroupCameraActive()) return;
    m_unk60 = m_unk60 - dt;
    // STUB(C2.8: camera): above 0, ScriptedCameraHandle_SetPositionAndTarget_maybe 0x165a78 (the camera's position, the
    // direction to the node, the group's +0x26c); else ScriptedCameraHandle_Release_maybe 0x166130.
    DOTD_STUB_ONCE("CKS08Accessory_UpdateMotion: the scripted camera's follow (C2.8)");
}

// 0x0026c408 CKS08Accessory_LaunchFromHit_maybe
void CKS08EnemyElement::LaunchFromHit(const CKS08Damage* damage, const CVector3* hitPoint, IKSerializable* breakFx) {
    const RwV3d& at = static_cast<CSGMovable*>(m_pNode)->m_pRwFrame->ltm.pos;
    m_v04 = CVector3{at.x, at.y, at.z};
    m_v10 = CVector3{0.0f, 0.0f, 0.0f};  // 0x00c50d64 (TOC +0x6f0)
    const CKS08AccessoryConfig* config =
        m_pPool58 != nullptr
            ? static_cast<const CKS08AccessoryConfig*>(static_cast<CKS08EnemyElementPool*>(m_pPool58)->m_pConfig)
            : nullptr;
    // Away from the hit, flat.
    float x = m_v04.x - hitPoint->x;
    float y = 0.0f;
    float z = m_v04.z - hitPoint->z;
    if (ppc::fmadds(z, z, ppc::fmadds(x, x, y * y)) <= 0.0f) {  // cror lt / eq
        x = 0.0f;  // the Z axis 0x00c50d4c (TOC +0x70c)
        y = 0.0f;
        z = 1.0f;
    }
    float length = SqrtF(ppc::fmadds(z, z, ppc::fmadds(x, x, y * y)));
    if (length != 0.0f) {
        const float inverse = 1.0f / length;
        z = inverse * z;
        x = inverse * x;
        y = inverse * y;
    }
    // A frame looking along it (up: the Y axis 0x00c50d40, TOC +0x710), turned by the damage's angles (x -57.29578,
    // TOC +0x714): about its up by +0x1c, about its right by +0x18 (at least the config's +0x24).
    CMatrix34 frame{};
    frame.m_right = CVector3{-z, 0.0f, x};
    frame.m_ui32Flags = 0;
    frame.m_up = CVector3{0.0f, 1.0f, 0.0f};
    frame.m_at = CVector3{x, y, z};
    Mat4_RotateLocalYDeg(damage->m_unk1c * -57.29578f, &frame);  // 0x002413d0
    float pitch;
    std::memcpy(&pitch, &damage->m_unk18, sizeof(pitch));  // read as a float
    if (config != nullptr && pitch <= config->m_unk24) pitch = config->m_unk24;
    Mat4_RotateLocalXDeg(pitch * -57.29578f, &frame);  // 0x00241118
    x = frame.m_at.x;
    y = frame.m_at.y;
    z = frame.m_at.z;
    length = SqrtF(ppc::fmadds(z, z, ppc::fmadds(x, x, y * y)));
    if (length != 0.0f) {
        const float inverse = 1.0f / length;
        z = inverse * z;
        x = inverse * x;
        y = inverse * y;
    }
    const float speed = damage->m_unk10 >= config->m_unk28 ? damage->m_unk10 : config->m_unk28;
    m_v1c = CVector3{speed * x, speed * y, speed * z};
    m_unk2c = damage->m_unk14;
    if (m_unk2c < config->m_unk2c) m_unk2c = config->m_unk2c;
    m_unk28 = m_unk2c;
    m_unk3c = 0;
    m_unk40 = config->m_unk20;
    m_afSpin30[0] = config->m_unk0c;
    m_afSpin30[1] = config->m_unk10;
    m_afSpin30[2] = config->m_unk14;
    m_unk48 = 0;
    m_pBreakFx50 = breakFx;
    m_unk60 = EnemyGroupOfElements()->m_unk268[0];
}

// 0x0026b398 CKS08EnemyElement_BreakOff_maybe
void CKS08EnemyElement::BreakOff() {
    CSGLeaf* node = static_cast<CSGLeaf*>(m_pNode);
    if (node->m_pParent != nullptr) node->m_pParent->RemoveChild(node);  // vt+0x78
    static_cast<CSGBranch*>(EnemyGroupOfElements()->m_vUnk40.m_pBlock[0])->AddChild(node);  // vt+0x70
    node->m_sgProperties |= 4u;
    IKFxData* data = static_cast<IKFxData*>(m_pBreakFx50);
    m_inUse54 = 0;
    IKFx* effect = static_cast<CKSrvFx*>(g_pEngine->m_srvFx)->AcquireFx(data, this);
    if (effect != nullptr) {
        CKExplosionNodeFx* explosion = static_cast<CKExplosionNodeFx*>(effect);
        explosion->SetTranslation(&m_v04, this);  // 0x001b66e8
        explosion->Trigger(this, 0);              // 0x001b82a8
        explosion->ReleaseReservation(this);      // vt+0x54
    }
    // ScriptedCameraHandle_Release_maybe 0x166130 of the group's active scripted camera.
    if (GroupCameraActive()) static_cast<CKCameraEventCpnt*>(EnemyGroupOfElements()->m_pUnk264)->Release();
}

// 0x0026c158 CKS08EnemyElement_vf50
void CKS08EnemyElement::ReturnToGroup() {
    CSGLeaf* node = static_cast<CSGLeaf*>(m_pNode);
    if (node->m_pParent != nullptr) node->m_pParent->RemoveChild(node);  // vt+0x78
    static_cast<CSGBranch*>(EnemyGroupOfElements()->m_vUnk40.m_pBlock[0])->AddChild(node);  // vt+0x70
    node->m_sgProperties |= 4u;
    m_inUse54 = 0;
    if (m_pGlow != nullptr) static_cast<CSGLeaf*>(m_pGlow)->m_sgProperties |= 4u;
}
