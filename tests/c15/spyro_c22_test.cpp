// spyro_c22_test - checkpoint C2.2, family spyro: the Start of the Spyro2008 groups and hooks that the original
// runs at level start (CKServiceLife_Start -> CKBundle_InitHooks, not ported yet), called here by hand on the
// objects LVL010 holds when the game loop reaches mode 4. The test boots, requests LVL010 as level_load_test
// does, then calls Start (vt+0x50) on every hook and group of the ported classes below (the lives of the
// level's bundles) and checks the state the live RPCS3 dump
// (outputs/remake/census/objects-lvl010_ingame-20261018-223707) shows for it.
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <set>
#include <string>
#include <vector>

#include "Spyro2008/groups/CKGrpS08Hero.h"
#include "Spyro2008/hooks/CKHkS08Hero.h"
#include "Spyro2008/logic/CKS08GameManager.h"
#include "boot_helper.h"
#include "k2000/groups/IKBaseGroup.h"
#include "k2000/hooks/IKLife.h"
#include "k2000/logic/CKBundle.h"
#include "k2000/logic/CKGameLevel.h"
#include "k2000/logic/CKGameSpawnPoint.h"
#include "k2000/misc/CKGameLoop.h"
#include "k2000/misc/ClassRegistry.h"
#include "k2000/misc/CoreSingletons.h"
#include "k2000/misc/Engine.h"
#include "k2000/misc/IKGameStructure.h"
#include "k2000/managers/CKServiceManager.h"
#include "k2000/services/CKServiceLife.h"
#include "k2000/services/CKSrvDynamic.h"

namespace {

CKS08GameManager* Manager() { return static_cast<CKS08GameManager*>(g_pEngine->m_gameManager); }

CKGameSpawnPoint* FirstSpawnPoint(int level) {
    IKGameStructure* structure = static_cast<IKGameStructure*>(Manager()->m_gameStructure);
    for (uint32_t i = 0; i < structure->m_vpStages.m_ui32NbUsedElt; ++i) {
        CKGameLevel* stage = structure->m_vpStages.m_pBlock[i];
        if (stage == nullptr || stage->m_i32StageIndex != level) continue;
        if (stage->m_vpSpawnPoints.m_ui32NbUsedElt == 0) return nullptr;
        return stage->m_vpSpawnPoints.m_pBlock[0];
    }
    return nullptr;
}

bool LoadLevel(int level) {
    CKS08GameManager* manager = Manager();
    CKGameSpawnPoint* spawnPoint = FirstSpawnPoint(level);
    if (spawnPoint == nullptr) return false;
    static_cast<IKGameStructure*>(manager->m_gameStructure)->m_pCurrentSpawnPoint = spawnPoint;
    manager->RequestSpawnPointLevel();
    for (uint32_t frame = 0; frame < 20000; ++frame) {
        c15::RunFrame();
        if (g_pCKGameLoop->m_mode == CKGameLoop::kModeStartLevel && manager->m_currentLevel == level) return true;
        if (g_pCKGameLoop->m_mode == CKGameLoop::kModeQuit) break;
    }
    return false;
}

// The classes whose Start this checkpoint ports, groups before hooks (the original starts the groups first).
const char* const kStarted[] = {
    "CKGrpS08Enemy", "CKGrpS08Hero",     "CKGrpS08Meca",     "CKGrpS08Clamp",           "CKGrpS08SpawnableMushroom",
    "CKHkS08Enemy",  "CKHkS08Weapon",    "CKHkS08Sparx",     "CKHkS08CrumblyZone",      "CKHkS08CrumblyZoneMultiState",
    "CKHkS08Egg",    "CKHkS08AirCurrent", "CKHkS08FogHorn",  "CKHkS08TransportableKey", "CKHkS08TransportableWeight",
    "CKHkS08SavePoint", "CKHkS08DragonCityGolem", "CKHkS08SpawnableMushroom", "CKHkS08Hero",
};

// Calls Start on every life of the named class among the level's bundles (the lists CKBundle starts in the
// original: the awake and the asleep hooks and groups).
uint32_t StartObjects(const char* className, CKGrpS08Hero** heroGroup) {
    uint32_t started = 0;
    CKServiceLife* life = static_cast<CKServiceLife*>(g_pEngine->m_lifeService);
    std::set<IKLife*> seen;
    for (CKBundle* bundle = static_cast<CKBundle*>(life->m_lBundleList); bundle != nullptr; bundle = bundle->m_pNext) {
        // The bundle's group tree (groups are not in the life lists), then the hooks and groups it holds.
        std::vector<IKBaseGroup*> groups;
        std::vector<IKBaseGroup*> stack;
        if (bundle->m_pGroup != nullptr) stack.push_back(static_cast<IKBaseGroup*>(bundle->m_pGroup));
        while (!stack.empty()) {
            IKBaseGroup* group = stack.back();
            stack.pop_back();
            groups.push_back(group);
            for (IKBaseGroup* child = group->m_lChilds; child != nullptr; child = child->m_pNextGroup) stack.push_back(child);
        }
        std::vector<IKLife*> lives;
        for (IKBaseGroup* group : groups) lives.push_back(group);
        for (IKLife* list : {bundle->m_lAwakeLifeList, bundle->m_lAsleepLifeList}) {
            for (IKLife* object = list; object != nullptr; object = object->m_pNext) lives.push_back(object);
        }
        {
            for (IKLife* object : lives) {
                if (!seen.insert(object).second) continue;
                const KClassInfo* info = FindClassInfo(MakeClassKey(object->GetClassType(), object->GetClassID()));
                if (info == nullptr || std::strcmp(info->name, className) != 0) continue;
                if (std::strcmp(className, "CKGrpS08Hero") == 0) *heroGroup = static_cast<CKGrpS08Hero*>(object);
                // DOTD_SPYRO_DUMP=dir : the heroes' bytes before and after Start (work/spyro_hero_diff.py compares
                // them with the live dump of the same level).
                const bool isHero = std::strcmp(className, "CKHkS08Hero") == 0;
                std::vector<uint8_t> before;
                if (isHero) {
                    before.assign(reinterpret_cast<uint8_t*>(object), reinterpret_cast<uint8_t*>(object) + sizeof(CKHkS08Hero));
                }
                object->Start();
                if (isHero) {
                    if (const char* dir = std::getenv("DOTD_SPYRO_DUMP")) {
                        const CKHkS08Hero* hero = static_cast<CKHkS08Hero*>(object);
                        char path[600];
                        std::snprintf(path, sizeof(path), "%s/hero%u_before.bin", dir, static_cast<unsigned>(hero->m_ui8Hero));
                        if (std::FILE* f = std::fopen(path, "wb")) {
                            std::fwrite(before.data(), 1, before.size(), f);
                            std::fclose(f);
                        }
                        std::snprintf(path, sizeof(path), "%s/hero%u_after.bin", dir, static_cast<unsigned>(hero->m_ui8Hero));
                        if (std::FILE* f = std::fopen(path, "wb")) {
                            std::fwrite(object, 1, sizeof(CKHkS08Hero), f);
                            std::fclose(f);
                        }
                    }
                }
                ++started;
            }
        }
    }
    return started;
}

}  // namespace

int main() {
    std::setvbuf(stdout, nullptr, _IONBF, 0);
    if (!c15::BootToFrontEnd()) {
        std::printf("spyro_c22: no game data configured: skipped\n");
        return 77;
    }
    C15_CHECK(LoadLevel(10));
    if (std::getenv("SPYRO_C22_DEBUG") != nullptr) {
        CKServiceLife* life = static_cast<CKServiceLife*>(g_pEngine->m_lifeService);
        uint32_t bundles = 0, lives = 0;
        for (CKBundle* bundle = static_cast<CKBundle*>(life->m_lBundleList); bundle != nullptr; bundle = bundle->m_pNext) {
            ++bundles;
            for (IKLife* l = bundle->m_lAwakeLifeList; l != nullptr; l = l->m_pNext) ++lives;
            for (IKLife* l = bundle->m_lAsleepLifeList; l != nullptr; l = l->m_pNext) ++lives;
        }
        std::printf("spyro_c22: %u bundles, %u lives\n", bundles, lives);
    }
    // CKSrvDynamic::InitializeService (0x23aea0, STUB(C1.6)) should hand the service to the engine
    // (Engine_SetDynamicService); until the svc family ports it the slot holds garbage, so do it here.
    Engine_SetDynamicService(g_pEngine->m_serviceManager->GetServiceByClassId(CKSrvDynamic::kClassKey >> 6));
    CKGrpS08Hero* heroGroup = nullptr;
    for (const char* name : kStarted) {
        const uint32_t started = StartObjects(name, &heroGroup);
        std::printf("spyro_c22: %-30s %u started\n", name, started);
    }
    // LVL010 holds one hero group with two heroes: one controlled (player 0), one companion (the live dump:
    // bytes +0x50 / +0x51 = 1 / 1), the sound listener following the camera, the arrays ready.
    C15_CHECK(heroGroup != nullptr);
    if (heroGroup != nullptr) {
        C15_CHECK(heroGroup->m_ui8ControlledHeroCount == 1);
        C15_CHECK(heroGroup->m_ui8CompanionHeroCount == 1);
        C15_CHECK(heroGroup->m_apControlledHeroes != nullptr && heroGroup->m_apControlledHeroes[0] != nullptr);
        C15_CHECK(heroGroup->m_apControlledHeroes[1] == nullptr);
        C15_CHECK(heroGroup->m_apCompanionHeroes != nullptr && heroGroup->m_apCompanionHeroes[0] != nullptr);
        C15_CHECK(heroGroup->m_unk60 == -1000.0f && heroGroup->m_unk68 == -1000.0f && heroGroup->m_unk6c == -1000.0f);
        C15_CHECK(heroGroup->m_unk104 == 20.0f);
        C15_CHECK(heroGroup->m_unk100 == heroGroup->m_unk10c && heroGroup->m_unk108 == heroGroup->m_unk10c);
    }
    std::printf("spyro_c22: %s\n", c15::g_failures == 0 ? "all checks passed" : "FAILED");
    c15::Shutdown();
    return c15::g_failures == 0 ? 0 : 1;
}
