// CKS08GameManager_6.cpp - reconstructed original translation unit 0x5043a8-0x506400 (GAME_TOC1, main_toc1), 9 functions, 6 live.
// Primary class: CKS08GameManager  key 0x784c  category Logic  size 0xf2c  vtable 0xb2af78
// Other owners: CKS08ObjectiveList (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x5043a8  CKS08GameManager_StateInGame_maybe
//   [x] 0x5044e0  CKS08GameManager_State4_maybe
//   [x] 0x504750  CKS08GameManager_State5_maybe
//   [x] 0x504990  CKS08GameManager_StateMenuPause
//   [x] 0x504c88  CKS08GameManager_StateHeroDeath_maybe
//   [x] 0x506348  CKS08ObjectiveList_Delete  (the registry Delete of CKS08ObjectiveList: DOTD_DECLARE_FACTORIES, CKS08ObjectiveList.h)
//   [ ] 0x506398  KStub_Nop_506398  [dead]
//   [ ] 0x5063a0  FUN_005063a0  [dead]
//   [ ] 0x5063f8  KStub_Nop_5063f8  [dead]
#include "Spyro2008/logic/CKS08GameManager.h"

#include "Spyro2008/logic/CKMenuBase114c.h"
#include "k2000/core/Stub.h"
#include "k2000/graphical/system/IKVideo.h"
#include "k2000/graphical/system/CKVideoSegment.h"
#include "k2000/graphical/system/CVideoManager.h"
#include "k2000/graphical/system/PS3_CKVideo.h"
#include "k2000/input/CKInputDico.h"
#include "k2000/managers/CKInput.h"
#include "k2000/misc/CKGameLoop.h"
#include "k2000/misc/Engine.h"
#include "k2000/system/CTimeManager.h"
#include "k2000/system/IKTime.h"
#include "k2000/ui/IKNode2d.h"

#include <cstring>

#include "Renderware/rwcore/RwCamera.h"
#include "Spyro2008/groups/IKGrpHero.h"
#include "Spyro2008/hooks/CKHkS08Hero.h"
#include "crt/ppc_ops.h"
#include "k2000/cameras/CKSrvCamera.h"
#include "k2000/cameras/IKCamera.h"
#include "k2000/dictionaries/CAnimationDictionary.h"
#include "k2000/dictionaries/CKSoundDictionaryID.h"
#include "k2000/fx/IKFx.h"
#include "k2000/geometry/CGeometry.h"
#include "k2000/graphical/fx/CColorizedScreenData.h"
#include "k2000/graphical/fx/CColorizedScreenFx.h"
#include "k2000/logic/CKSekens.h"
#include "k2000/logic/IKFxData.h"
#include "k2000/logic/sound/CKSound.h"
#include "k2000/scenegraph/CNode.h"
#include "k2000/scenegraph/CSGMovable.h"
#include "k2000/services/CKSrvFx.h"
#include "k2000/services/CKSrvMusic.h"
#include "k2000/logic/sound/CKMusicPlayList.h"
#include "k2000/services/CTriggerStarter.h"

// 0x005043a8 CKS08GameManager_StateInGame_maybe: game state 7 stays. While the clock runs: the common state;
// on its tick (phase 0) the interface asks for menu 0x10 when flags +0xafc bit 7 is set (one request on the
// stack, depth 1), else no menu (0x24); on enter (phase 1) bits 2-4 of +0xafc are cleared and bit 4 set.
uint8_t CKS08GameManager::StateInGame(int32_t phase, uint8_t other) {
    if (g_pEngine->m_timeManager->m_pTime->m_eCurrentState == IKTime::RUNNING) {
        const uint8_t state = StateInGameCommon(phase, other);
        if (state != 7) return state;
        if (phase == 0) {
            m_aMenuStack[0] = (m_unkAFC & 0x80) != 0 ? 0x10 : 0x24;
            m_ui32MenuStackDepth = 1;
            return 7;
        }
        if (phase == 1) {
            m_unkAFC = (m_unkAFC & 0xffffffe3u) | 0x10;
            return 7;
        }
    }
    return 7;
}

// 0x005044e0 CKS08GameManager_State4_maybe: the copyrights screen (menu 4). Enter: the interface video
// stopped if it plays; with the menu: flag bit 0 cleared, menu 4; without: flag bit 0 set. Update: once the
// flag is set (the menu's end) or without the menu, no menu and state 0.
uint8_t CKS08GameManager::State4(int32_t phase, uint8_t other) {
    const uint8_t state = StateReturn4(phase, other);
    if (state != 4) return state;
    if (phase == 0) {
        if (Vf344()[4] != nullptr && (m_unkAFC & 1) == 0) return 4;
        m_aMenuStack[0] = 0x24;
        m_ui32MenuStackDepth = 1;
        return 0;
    }
    if (phase != 1) return 4;
    if (GetInterfaceVideo() != nullptr && (GetInterfaceVideo()->m_baData & 1) != 0) GetInterfaceVideo()->Stop();
    if (Vf344()[4] != nullptr) {
        m_unkAFC &= ~1u;
        m_aMenuStack[0] = 4;
        m_ui32MenuStackDepth = 1;
        return 4;
    }
    m_unkAFC = (m_unkAFC & ~1u) | 1;
    return 4;
}

// 0x00504750 CKS08GameManager_State5_maybe: the press-start screen (menu 0x11), as State4. The update leaves
// once the flag is set (KStub_Return1_4ec918: always).
uint8_t CKS08GameManager::State5(int32_t phase, uint8_t other) {
    const uint8_t state = State5Common(phase, other);
    if (state != 5) return state;
    if (phase == 0) {
        if ((m_unkAFC & 1) != 0) return 0;  // and 0x4ec918 KStub_Return1_4ec918 returned 1
        return 5;
    }
    if (phase != 1) return 5;
    if (GetInterfaceVideo() != nullptr && (GetInterfaceVideo()->m_baData & 1) != 0) GetInterfaceVideo()->Stop();
    if (Vf344()[0x11] != nullptr) {
        m_unkAFC &= ~1u;
        m_aMenuStack[0] = 0x11;
        m_ui32MenuStackDepth = 1;
        return 5;
    }
    m_unkAFC = (m_unkAFC & ~1u) | 1;
    return 5;
}

// 0x00504990 CKS08GameManager_StateMenuPause: the common part (StateMenuCommon), then the pause menu: enter shows menu
// 10 (+0xafc bit 6: the "info" pause), 0x15 (bit 9), 0x13 (bit 10) or 0xf (the pause menu); every frame the pause music
// (entry 0 of the dictionary +0xbdc, looping, centred) is kept playing; leave stops it, clears bit 6, makes the save the
// menu asked for (bit 9: vt+0x104 with 0, 0) and asks for no menu (vt+0x338). The menus answer through their own code
// (the interface state machine, KBase730C), which requests the next game state.
uint8_t CKS08GameManager::StateMenuPause(int32_t phase, uint8_t other) {
    const uint8_t state = StateMenuCommon(phase, other);  // 0x4f5128
    if (state != 8) return state;
    if (phase == 1) {
        const uint32_t flags = m_unkAFC;
        uint8_t menu = 0xf;
        if ((flags & 0x40u) != 0) {
            menu = 10;
        } else if ((flags & 0x200u) != 0) {
            menu = 0x15;
        } else if ((flags & 0x400u) != 0) {
            menu = 0x13;
        }
        m_aMenuStack[0] = menu;
        m_ui32MenuStackDepth = 1;
        return 8;
    }
    if (phase == 2) {
        // KStub_Nop_4ec920(this, 0): empty.
        m_unkAFC &= ~0x40u;
        CKSound* music = static_cast<CKSoundDictionaryID*>(m_unkBDC)->GetSound2(0);  // 0x112bd8
        if (music != nullptr && music->IsPlaying() != 0) music->Stop(0);  // 0x111568, 0x1111b0
        if ((m_unkAFC & 0x200u) != 0) {
            RequestSave(0, 0);  // vt+0x104
            m_unkAFC &= ~0x200u;
        }
        m_aMenuStack[0] = NoMenuId();  // vt+0x338
        m_ui32MenuStackDepth = 1;
        return 8;
    }
    if (phase != 0) return 8;
    CKSound* music = static_cast<CKSoundDictionaryID*>(m_unkBDC)->GetSound2(0);
    if (music == nullptr || music->IsPlaying() != 0) return 8;
    music->ResetPan(1);   // 0x111b70
    music->SetLoop(1);    // 0x110fd0
    music->Play(0.0f);    // 0x111230; TOC +0x739c
    return 8;
}

namespace {
CKSrvCamera* CameraService() { return static_cast<CKSrvCamera*>(g_pEngine->m_srvCamera); }

// The inlined camera switch of the death states: `camera` becomes the camera service's next camera unless it is the
// current one; outside a blocked switch (+0x46c bit 4) a cut (no transition, timer 0) with the stack-changed bit.
void SwitchDeathCamera(IKSerializable* camera) {
    CKSrvCamera* service = CameraService();
    if (static_cast<IKSerializable*>(service->m_pCurrentCamera) == camera) return;
    service->m_pNextCamera = static_cast<IKCamera*>(camera);
    if ((service->m_baTemporaryFlags & 0x10u) != 0) return;
    service->m_ui8TransitionMode = 0;
    service->m_fSwitchTimer = 0.0f;
    service->m_baTemporaryFlags = (service->m_baTemporaryFlags & ~0x400000u) | 0x400000u;
}

// The manager put in (if absent) / taken out of the camera service's owners (+0xe14, count +0xe24; no bound check).
void AddDeathCameraOwner(IKSerializable* owner) {
    CKSrvCamera* service = CameraService();
    for (uint32_t i = 0; i < service->m_unke24; ++i) {
        if (service->m_apCinematicOwner[i] == owner) return;
    }
    service->m_apCinematicOwner[service->m_unke24++] = owner;
}
void RemoveDeathCameraOwner(IKSerializable* owner) {
    CKSrvCamera* service = CameraService();
    const uint32_t count = service->m_unke24;
    for (uint32_t i = 0; i < count; ++i) {
        if (service->m_apCinematicOwner[i] != owner) continue;
        service->m_unke24 = count - 1;
        if (i != count - 1) service->m_apCinematicOwner[i] = service->m_apCinematicOwner[count - 1];
        return;
    }
}

// The death camera's frame (modes 1 and 2): its rising speed (+0xdbc) accelerates by `accel` towards the top speed
// (+0xdc4), its position climbs by it, and its vt+0x88 value grows by +0xdc8 per second.
void UpdateDeathCamera(CKS08GameManager* manager, IKCamera* camera, float dt, float accel) {
    const float x = camera->m_WorldPosition.x;
    const float y = camera->m_WorldPosition.y;
    const float z = camera->m_WorldPosition.z;
    float speed = manager->m_fDeathCameraSpeed;
    const float top = manager->m_fDeathCameraMaxSpeed;
    if (top > speed) {  // ble: a NaN keeps the speed
        speed = ppc::fmadds(dt, accel, speed);
        manager->m_fDeathCameraSpeed = speed;
        if (speed > top) speed = top;
        manager->m_fDeathCameraSpeed = speed;
    }
    camera->m_WorldPosition.z = z;
    camera->m_WorldPosition.x = x;
    camera->m_WorldPosition.y = ppc::fmadds(dt, speed, y);
    const float value = camera->Vf84();                                       // vt+0x84
    camera->Vf88(ppc::fmadds(dt, manager->m_fDeathCameraRollSpeed, value));  // vt+0x88
}

// The geometry chain of a node: its render bits set (or cleared) as the death tint needs.
void TintNodeGeometry(IKSerializable* node) {
    for (CGeometry* geometry = static_cast<CGeometry*>(static_cast<CNode*>(node)->m_lGeometryList); geometry != nullptr;
         geometry = geometry->m_pNext)
        geometry->m_BitProperties = (geometry->m_BitProperties & ~0x3fu) | 0x30u;
}
void UntintNodeGeometry(IKSerializable* node) {
    for (CGeometry* geometry = static_cast<CGeometry*>(static_cast<CNode*>(node)->m_lGeometryList); geometry != nullptr;
         geometry = geometry->m_pNext) {
        geometry->m_BitProperties &= ~0x20u;
        geometry->UpdateProperties();  // vt+0x60
    }
}

CKHkS08Hero* HeroOfDragon(CKS08GameManager* manager, uint32_t dragon) {
    return static_cast<CKHkS08Hero*>(static_cast<IKGrpHero*>(manager->m_unk04[1])->m_apHeros[static_cast<uint8_t>(dragon)]);  // 0x2ca080
}
}  // namespace

// 0x00504c88 CKS08GameManager_StateHeroDeath_maybe: game state 9 (StartDeathSequence chose the mode and the dragon).
// Enter: the death trigger signals (+0xb00), the timers cleared, the input mapping 1 on, the dead hero attached to the
// manager (mode 3, its old object told 0x940) and frozen there (locked, its volumes off, invulnerable, the other hero
// too), the death music; mode 1 puts the camera +0xda8 behind the hero, mode 2 the camera +0xddc above it, tints the
// screen and the hero, plays the dragon's death animation; both start the three effects +0xdac..+0xdb4. Update (not
// while paused): mode 1 raises its camera until +0xda4 seconds, mode 2 lets the hero sink (above +0xde8 over the
// ground) and raises its camera until +0xdec seconds; a menu button after +0xd94 seconds ends it early (state 0).
// Leave: the sekens +0xdb8 stopped, the camera owner and the music released; mode 2 removes the tints and puts the
// time scale back to 1.
uint8_t CKS08GameManager::StateHeroDeath(int32_t phase, uint8_t /*other*/) {
    if (phase == 1) {
        QueueTriggerSignals(&m_unkB00);  // 0x236338
        m_fDeathTime = 0.0f;
        m_unkDB8 = nullptr;
        g_pEngine->m_input->SetMappingEnabled(1, 1);  // 0x107618
        CKHkS08Hero* hero = HeroOfDragon(this, m_ui8DeathDragon);
        const int32_t next = static_cast<int32_t>(m_ui8DeathDragon) + 1;
        CKHkS08Hero* other = HeroOfDragon(this, static_cast<uint32_t>(next % 2));
        if (hero->GetAttachedObject() != nullptr) hero->GetAttachedObject()->MessageProc(0x940, hero);  // 0x361d50, vt+0x1c
        if (hero->AttachToObject(this, 3) == 0) {  // 0x362360
            m_apDeathFx[2] = nullptr;
            m_apDeathFx[0] = nullptr;
            m_apDeathFx[1] = nullptr;
            return 9;
        }
        hero->SetExternallyPositionedAndPhysics(1, nullptr, nullptr);  // 0x32a638
        hero->SetAttachedMovementEnabled(1);                           // 0x362050
        hero->SetInvulnerable(1);                                      // 0x361b20
        other->SetInvulnerable(1);
        hero->SetCollisionDisabledWhileAttached(1);  // 0x362150
        hero->SetFlag360Bit8IfAttached(1);           // 0x363f98
        hero->SetFlag360Bit14IfAttached(1);          // 0x363dc8
        hero->SetFlag360Bit15IfAttached(1);          // 0x363df8
        hero->SetFlag35CBit21IfAttached(1);          // 0x363fc8
        if (m_unkD98 != nullptr) {
            CKSrvMusic* music = static_cast<CKSrvMusic*>(g_pEngine->m_srvMusic);
            music->ClearChannelRequests();      // 0x2101a0
            music->RequestTrack(static_cast<CKMusicPlayList*>(m_unkD98), 1);   // 0x210358
        }
        RwFrame* frame = static_cast<CSGMovable*>(hero->m_pKGLObject)->m_pRwFrame;
        if (m_ui8DeathMode == 1) {
            const float* position = hero->GetPositionPtr();  // 0x361968
            const float z = position[2];
            const float x = position[0];
            const float y = position[1];
            (void)hero->GetDragonIndex();
            IKCamera* camera = static_cast<IKCamera*>(m_unkDA8);
            camera->m_WorldPosition.x = x - frame->ltm.at.x;
            camera->m_WorldPosition.y = (y + 2.0f) - frame->ltm.at.y;  // TOC +0x73d0
            camera->m_WorldPosition.z = z - frame->ltm.at.z;
            camera->m_WorldTarget.z = z;
            camera->m_WorldTarget.x = x;
            camera->m_WorldTarget.y = y;
            SwitchDeathCamera(camera);
            AddDeathCameraOwner(this);
            camera->Vf88(0.0f);  // vt+0x88; TOC +0x739c
            m_fDeathCameraSpeed = 0.0f;
        } else if (m_ui8DeathMode == 2) {
            const float* position = hero->GetPositionPtr();
            const float z = position[2];
            const float x = position[0];
            const float y = position[1];
            const uint8_t dragon = hero->GetDragonIndex();
            hero->SetFlag35CBit3IfAttached(1);  // 0x363ee8
            hero->SetObjectControlsAnim(1);     // 0x362010
            IKCamera* camera = static_cast<IKCamera*>(m_unkDDC);
            const float above = y + 3.0f;  // TOC +0x73d4
            camera->m_WorldPosition.x = ppc::fmadds(frame->ltm.at.x, -2.0f, x);  // TOC +0x73d8
            camera->m_WorldPosition.y = ppc::fmadds(frame->ltm.at.y, -2.0f, above);
            camera->m_WorldPosition.z = ppc::fmadds(frame->ltm.at.z, -2.0f, z);
            camera->m_WorldTarget.z = z;
            camera->m_WorldTarget.x = x;
            camera->m_WorldTarget.y = y;
            SwitchDeathCamera(camera);
            AddDeathCameraOwner(this);
            CColorizedScreenFx* tint = static_cast<CColorizedScreenFx*>(m_unkDE0);
            tint->ApplyData(static_cast<CColorizedScreenData*>(m_unkDE4));  // 0xb0b00
            tint->m_BitProperties = (tint->m_BitProperties & ~0x100u) | 0x100u;
            tint->m_BitProperties = (tint->m_BitProperties & ~0x20u) | 0x20u;
            tint->m_BitProperties = (tint->m_BitProperties & ~0x1fu) | 0xfu;
            TintNodeGeometry(hero->m_pKGLObject);
            for (uint32_t i = 13; i != 0xffffffffu; --i) TintNodeGeometry(hero->GetSubNodeB(i));  // 0x329eb8
            CAnimationDictionary* animations = static_cast<CAnimationDictionary*>(m_unkD9C[dragon]);
            hero->PlayAnimResource(0.0f, static_cast<uint32_t>(animations->m_apAnimations[0]));  // vt+0xc0
            const float zero = 0.0f;
            std::memcpy(&m_unkDF4[0], &zero, 4);
            camera->Vf88(0.0f);
            m_fDeathCameraSpeed = 0.0f;
        } else {
            return 9;
        }
        // The three effects (the inlined CKSrvFx_AcquireFx 0x9bdc18) for the manager.
        CKSrvFx* fxService = static_cast<CKSrvFx*>(g_pEngine->m_srvFx);
        m_apDeathFx[0] = fxService->AcquireFx(static_cast<IKFxData*>(m_unkDAC), this);
        m_apDeathFx[1] = fxService->AcquireFx(static_cast<IKFxData*>(m_unkDB0), this);
        m_apDeathFx[2] = fxService->AcquireFx(static_cast<IKFxData*>(m_unkDB4), this);
        return 9;
    }
    if (phase == 2) {
        if (m_unkDB8 != nullptr) {
            static_cast<CKSekens*>(m_unkDB8)->Stop();  // 0x1f56b0
            m_unkDB8 = nullptr;
        }
        RemoveDeathCameraOwner(this);
        if (m_unkD98 != nullptr) static_cast<CKSrvMusic*>(g_pEngine->m_srvMusic)->StopPlayList(static_cast<CKMusicPlayList*>(m_unkD98));  // 0x210bd8
        if (m_ui8DeathMode <= 1) return 0;
        if (m_ui8DeathMode != 2) return 9;
        CColorizedScreenFx* tint = static_cast<CColorizedScreenFx*>(m_unkDE0);
        tint->m_BitProperties &= ~0x20u;
        tint->UpdateProperties();  // vt+0x60
        CKHkS08Hero* hero = HeroOfDragon(this, m_ui8DeathDragon);
        UntintNodeGeometry(hero->m_pKGLObject);
        (void)hero->GetDragonIndex();
        for (uint32_t i = 13; i != 0xffffffffu; --i) UntintNodeGeometry(hero->GetSubNodeB(i));
        g_pEngine->m_timeManager->m_fTimeScale = 1.0f;  // TOC +0x73dc
        return 0;
    }
    if (phase != 0) return 9;
    IKTime* clock = g_pEngine->m_timeManager->m_pTime;
    if (clock->m_eCurrentState == IKTime::PAUSED) return 9;
    CKHkS08Hero* hero = HeroOfDragon(this, m_ui8DeathDragon);
    const float dt = clock->m_afDeltaTime[IKTime::SCALABLE_GAME_TIME];
    m_fDeathTime = dt + m_fDeathTime;
    if (IsAnyMenuButtonPressed() != 0 && m_fDeathTime > m_fDeathSkipDelay) return 0;  // 0x4f89d8
    if (m_ui8DeathMode == 1) {
        if (m_fDeathTime >= m_fDeathDuration1) return 0;  // cror gt|eq
        UpdateDeathCamera(this, static_cast<IKCamera*>(m_unkDA8), dt, m_fDeathCameraAccel);
        return 9;
    }
    if (m_ui8DeathMode < 1) return 0;
    if (m_ui8DeathMode != 2) return 9;
    if (m_fDeathTime >= m_fDeathDuration2) return 0;
    RwFrame* frame = static_cast<CSGMovable*>(hero->m_pKGLObject)->m_pRwFrame;
    const float x = frame->modelling.pos.x;
    const float y = frame->modelling.pos.y;
    const float z = frame->modelling.pos.z;
    if (m_fDeathSinkHeight < hero->GetHeightAboveGround()) {  // 0x32a008
        float speed;
        std::memcpy(&speed, &m_unkDF4[0], 4);
        speed = ppc::fmadds(dt, m_fDeathSinkAccel, speed);
        std::memcpy(&m_unkDF4[0], &speed, 4);
        const float drop = dt * speed;
        frame->modelling.pos.z = z;
        frame->modelling.pos.x = x;
        frame->modelling.pos.y = y - drop;
        frame->modelling.flags &= ~0x20000u;
        RwFrame_MarkDirty(frame);  // 0x10698
    }
    hero->AdvanceObjectAnimTime(dt);  // 0x363410
    UpdateDeathCamera(this, static_cast<IKCamera*>(m_unkDDC), dt, 3.0f);  // TOC +0x73d4
    return 9;
}
