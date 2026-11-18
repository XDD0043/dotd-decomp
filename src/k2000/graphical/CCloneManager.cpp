//
// Reconstructed original translation unit: 0x864b8-0x87b18 (GAME_TOC1, main_toc1), 27 functions, 19 live.
// Primary class: CCloneManager  key 0xcd  category Graphical  size 0x68  vtable 0xb16918
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x864b8  CCloneManager_Delete  (DOTD_DECLARE_FACTORIES)
//   [ ] 0x86508  CCloneManager_Construct  [dead]
//   [x] 0x86548  CCloneManager_GetMaterialRenderInfo  (GetRenderingProperties)
//   [ ] 0x86570  CCloneManager_Construct_2  [dead]
//   [ ] 0x865b0  RegisterCCloneManagerClass
//   [ ] 0x86628  _GLOBAL__I_86628
//   [ ] 0x86638  CCloneManager_HasTeamElementData_maybe  [dead]
//   [x] 0x86708  CCloneManager_GetTeamElementFirstMaterial
//   [ ] 0x86770  CCloneManager_FindTeamElementIndexByFirstMaterial_maybe  [dead]
//   [x] 0x86828  CCloneManager_SetFlag200OnTeamElementsWithMaterialMode10To14
//   [ ] 0x86918  CCloneManager_SetPlayerColorForTexture_maybe  [dead]
//   [ ] 0x86a30  CCloneManager_SetCloneColorForTexture_maybe  [dead]
//   [ ] 0x86b58  CCloneManager_SetAllPlayersColorForTexture_maybe  [dead]
//   [x] 0x86cf0  CCloneManager_EnqueueVisibleClones
//   [x] 0x86eb8  CCloneManager_DrawClones
//   [ ] 0x86f40  CCloneManager_Save
//   [x] 0x86f68  CCloneManager_Destroy
//   [x] 0x87108  CCloneManager_DeleteArray  (DOTD_DECLARE_FACTORIES)
//   [x] 0x871a8  CCloneManager_RecursiveRegistration
//   [x] 0x872b0  CCloneManager_vf70
//   [x] 0x872d0  CCloneManager_PostLoad
//   [x] 0x87300  CCloneManager_CreateArray
//   [x] 0x873d0  CCloneManager_Create
//   [x] 0x87440  CCloneManager_Load
//   [ ] 0x87990  CCloneManager_Destructor_2  [dead]
//   [x] 0x87a10  CCloneManager_DeletingDestructor  (~CCloneManager, the deleting form)
//   [x] 0x87a98  CCloneManager_Destructor
//
//   [x] 0x99c288  CCloneManager_IsKindOfClass  [inline]
//   [x] 0x99c2b0  CCloneManager_GetClassType  [inline]
//   [x] 0x99c2b8  CCloneManager_GetClassID  [inline]
//   [x] 0x99c2c0  CCloneManager_GetSerializationFlags  [inline]
#include "k2000/graphical/CCloneManager.h"

#include "Renderware/rphanim/RpHAnim.h"
#include "Renderware/rpteam/RpTeam.h"
#include "Renderware/rpworld/RpAtomic.h"
#include "Renderware/rpworld/RpGeometry.h"
#include "Renderware/rwcore/RwCamera.h"
#include "Renderware/rwcore/RwFrameList.h"
#include "Renderware/rwcore/RwIm3D.h"
#include "Renderware/rwcore/RwStream.h"
#include "k2000/core/Stub.h"
#include "k2000/graphical/render/CLightManager.h"
#include "k2000/io/IKFile.h"
#include "k2000/logic/render/CMaterial.h"
#include "k2000/managers/CKGraphic.h"
#include "k2000/memory/Mem.h"
#include "k2000/misc/Engine.h"
#include "k2000/logic/CKSavingManager.h"
#include "k2000/render/CRenderer.h"
#include "k2000/scenegraph/CClone.h"

CCloneManager::CCloneManager() {
    m_pNextAccumulatedObject = nullptr;
    m_BitProperties = 0;
    m_pPriorityParent = 0;
    m_pLightSet = nullptr;
    m_vClones.m_ui32NbElt = 10;
    m_vClones.m_ui32NbUsedElt = 0;
    m_vClones.m_pBlock = nullptr;
}

// 0x00087a98 CCloneManager_Destructor: the clone vector's block freed (Destroy has normally done it), its length and
// block cleared. The team is Destroy's.
CCloneManager::~CCloneManager() {
    if (m_vClones.m_pBlock != nullptr) Mem_FreeAligned16(m_vClones.m_pBlock);
    m_vClones.m_ui32NbUsedElt = 0;
    m_vClones.m_pBlock = nullptr;
}

// 0x00086f68 CCloneManager_Destroy (the level unload): IRendableObject's; the team locked, then the dictionary and the team
// destroyed (RpTeamDestroy destroys each player's hierarchy frame); the clone list freed and the counts cleared.
// STUB(C2.8): the original first walks the clones: a node without an RpHAnim hierarchy on its player's frame has the
// intermediate frame CCloneManager_Load inserted destroyed, one with a hierarchy has its first word cleared and the frame given
// back to the player. Not done here (the intermediate frames stay allocated): the level unload path as a whole, with the nodes
// destroyed together with their frames, is C2.8's (item 5, level exit).
void CCloneManager::Destroy() {
    IRendableObject::Destroy();  // 0xa7248
    if (m_pRpTeam != nullptr) {
        RpTeamLock(m_pRpTeam, 0xff);
        RpTeamDictionaryDestroy(RpTeamGetDictionary(m_pRpTeam));
        RpTeamSetDictionary(m_pRpTeam, nullptr);
        RpTeamDestroy(m_pRpTeam);
        m_pRpTeam = nullptr;
    }
    if (m_vClones.m_pBlock != nullptr) {
        Mem_FreeAligned16(m_vClones.m_pBlock);
        m_vClones.m_pBlock = nullptr;
    }
    m_vClones.m_ui32NbUsedElt = 0;
    m_vClones.m_pBlock = nullptr;
    m_ui32NbInstanceClones = 0;
}

// 0x00087440 CCloneManager_Load. No type test of its own: IRendableObject_Load gets the type, the rest
// is read for every type.
int32_t CCloneManager::Load(IKFile* file, int32_t type) {
    IRendableObject::Load(file, type);
    ReadU32LE(file, &m_ui32NbInstanceClones);
    if (m_ui32NbInstanceClones != 0) {
        // The inlined TVector reserve + resize (the grow branch cannot run: the capacity is the count).
        m_vClones.m_ui32NbElt = m_ui32NbInstanceClones;
        m_vClones.m_pBlock =
            static_cast<IKSerializable**>(Mem_AllocAligned16(m_ui32NbInstanceClones * sizeof(IKSerializable*)));
        const uint32_t count = m_ui32NbInstanceClones;
        if (m_vClones.m_ui32NbElt < count) {
            uint32_t capacity = (count / 10) * 10 + 10;
            if (capacity == 0) capacity = 10;
            m_vClones.m_pBlock = static_cast<IKSerializable**>(
                Mem_ReallocAligned16(m_vClones.m_pBlock, capacity * sizeof(IKSerializable*)));
            m_vClones.m_ui32NbElt = capacity;
        }
        m_vClones.m_ui32NbUsedElt = count;
        ReadU32LEWords(file, m_aui32SqrLodRanges, 4);
        IKFile_ReadRef(file, &m_pLightSet);  // the light set again, after IRendableObject's (as XXL2)
        IKFile_ReadObjectRefArray(file, m_vClones.m_pBlock, m_ui32NbInstanceClones);

        RwStream* stream = file->m_pRwStream;
        uint32_t length = 0;
        if (RwStreamFindChunk(stream, 0x22, &length, nullptr) != 0) {
            RpTeamDictionary* dictionary = RpTeamDictionaryStreamRead(stream);
            if (RwStreamFindChunk(stream, 0x1c, &length, nullptr) != 0) {
                m_pRpTeam = RpTeamStreamRead(stream, dictionary);
                if (m_pRpTeam == nullptr) return 1;  // (the original does not test: a stream the readers cannot read)
                for (uint32_t i = 0; i < m_ui32NbInstanceClones; ++i) {
                    RpTeamPlayer* player = RpTeamGetPlayer(m_pRpTeam, i);
                    RpTeamPlayerSetActivity(player, 0);
                    player->unkF4 = 0;
                    ReadU32LEWords(file, reinterpret_cast<uint32_t*>(RpTeamPlayerGetBoundingSphere(player)), 4);
                    RwFrame* hierarchyFrame = RpTeamPlayerGetHierarchyFrame(player);
                    CClone* node = static_cast<CClone*>(m_vClones.m_pBlock[i]);
                    if (RpHAnimFrameGetHierarchy(hierarchyFrame) == nullptr) {
                        // A CClone: the node keeps the sphere (+0x28) and the player (+0x2c), and a new frame goes between its
                        // own and the player's.
                        node->m_pRwPlayerBSphere = RpTeamPlayerGetBoundingSphere(player);
                        node->m_pTeamPlayer = player;
                        RwFrame* intermediate = RwFrameCreate();
                        RwFrameAddChild(intermediate, hierarchyFrame);
                        RwFrameAddChild(node->m_pRwFrame, intermediate);
                    } else {
                        // STUB(C2.9): a CAnimatedClone (key 0x58b: the sphere at +0x68, the player +0x6c, the hierarchy +0x2c, the
                        // bit set of the nodes at +0x4c..+0x58 with bits 0..numNodes-1 set, the player's frame under the node's).
                        // No clump of the game files has an RpHAnim hierarchy and no level has a CAnimatedClone.
                        DOTD_STUB_ONCE("CCloneManager_Load: a player with an RpHAnim hierarchy (CAnimatedClone, C2.9)");
                    }
                }
                // The renderer's light manager (CRenderer +0xac): its first directional light (+0x54, XXL2
                // m_aHardwareDirectionalLights[0]) and its ambient light (+0x50, m_pAmbientLight). The manager may not exist yet
                // while this loads, and nothing reads the team's lights (STUB(C2.9): the persistent-lights pipeline callbacks).
                CLightManager* lights = static_cast<CLightManager*>(g_pEngine->m_graphic->m_renderer->m_lightManager);
                RpTeamSetPersistentLights(m_pRpTeam, lights != nullptr ? lights->m_aHardwareDirectionalLights[0] : nullptr,
                                          lights != nullptr ? lights->m_pAmbientLight : nullptr);
                m_shadows.number = 0;
                m_shadows.shadowLOD = 5;
                RpTeamSetShadows(m_pRpTeam, &m_shadows);
                RpTeamUnlock(m_pRpTeam);
                return 1;
            }
        }
    }
    m_pRpTeam = nullptr;
    return 1;
}

// 0x00086708 CCloneManager_GetTeamElementFirstMaterial
RpMaterial* CCloneManager::GetTeamElementFirstMaterial(uint32_t index) {
    RpTeamDictionary* dictionary = RpTeamGetDictionary(m_pRpTeam);
    RpAtomic* atomic = RpTeamDictionaryGetElement(dictionary, index);
    return atomic->geometry->matList.materials[0];
}

// 0x00086828 CCloneManager_SetFlag200OnTeamElementsWithMaterialMode10To14
void CCloneManager::SetFlag200OnTeamElementsWithMaterialMode10To14() {
    if (m_pRpTeam == nullptr) return;
    RpTeamDictionary* dictionary = RpTeamGetDictionary(m_pRpTeam);
    for (uint32_t i = 0; i < RpTeamDictionaryGetNumberOfElements(dictionary); ++i) {
        RpGeometry* geometry = RpTeamDictionaryGetElement(dictionary, i)->geometry;
        // The CMaterial plugin of the geometry's first material (the clone material's PostLoad linked it), its mode: bits 3-6.
        const uint32_t mode = (geometry->matList.materials[0]->kMaterial->m_baProperties >> 3) & 0xf;
        if (mode - 10u < 5u && (geometry->flags & 0x200) == 0) geometry->flags |= 0x200;  // CMaterial_IsMode10To14_maybe
    }
}

// 0x000872d0 CCloneManager_PostLoad
int32_t CCloneManager::PostLoad(int32_t type) {
    if (type == 0) SetFlag200OnTeamElementsWithMaterialMode10To14();
    return 1;
}

// 0x000872b0 CCloneManager_CanBeUpdated: ((renderer flags ^ 2) >> 1) & 1
int32_t CCloneManager::CanBeUpdated() {
    return static_cast<int32_t>(((g_pEngine->m_graphic->m_renderer->m_bitProperties ^ 2) >> 1) & 1);
}

// 0x00086cf0 CCloneManager_UpdateAndExtract. CClone::UpdateAndExtract (the scene traversal, before this) stamped the player of
// every clone it queued with the frame counter: those are switched on (RpTeamPlayerSetActivity), the others off with their
// stamp cleared; the team's lists are rebuilt when it is unlocked, and the manager joins stage 6 when a player is on.
void CCloneManager::UpdateAndExtract(float /*maxDistanceSquared*/, RenderQueue** stages, IKTime* /*frameClock*/,
                                     RwCamera* /*camera*/, int32_t /*distanceCull*/) {
    if (m_pRpTeam == nullptr) return;
    const uint32_t count = RpTeamGetNumberOfPlayers(m_pRpTeam);
    RpTeamLock(m_pRpTeam, 2);
    if (count == 0) {
        RpTeamUnlock(m_pRpTeam);
        return;
    }
    bool anyDrawn = false;
    for (uint32_t i = 0; i < count; ++i) {
        RpTeamPlayer* player = RpTeamGetPlayer(m_pRpTeam, i);
        if (player->unkF4 == g_ui16RenderFrameCounter) {
            anyDrawn = true;
            if ((player->flags & 1) == 0) RpTeamPlayerSetActivity(player, 1);
        } else if ((player->flags & 1) != 0) {
            RpTeamPlayerSetActivity(player, 0);
            player->unkF4 = 0;
        }
    }
    RpTeamUnlock(m_pRpTeam);
    if (anyDrawn) stages[6]->Add(this);
}

// 0x00086eb8 CCloneManager_Render: RwRenderStateSet(0x14 = rwRENDERSTATECULLMODE, 1 = rwCULLMODECULLNONE) between the
// render-state stack's push and pop, around the team's passes 2 (clip state), 4 (skin matrices), 8 (draw).
void CCloneManager::Render(IKTime* /*frameClock*/) {
    PushRenderStates(g_pRenderStateRenderer);
    RwRenderStateSet(rwRENDERSTATECULLMODE, reinterpret_cast<void*>(1));
    RpTeamRender(m_pRpTeam, 0xe);
    PopRenderStates(g_pRenderStateRenderer);
}

// C2.8 port-all P08.

// 0x00086548 CCloneManager_GetRenderingProperties (Ghidra CCloneManager_GetMaterialRenderInfo in the checklist)
void CCloneManager::GetRenderingProperties(uint8_t* first, uint8_t* second, uint8_t* third, uint32_t* blendMode) {
    *first = 0;
    *second = 0xff;
    *third = 1;
    *blendMode = 1;
}

// 0x000871a8 CCloneManager_RecursiveRegistration
void CCloneManager::RecursiveRegistration(int32_t type) {
    if (type != 0) return;
    g_pEngine->m_pSavingManager->RegisterSerializableObject(this, nullptr);  // vt+0x24
    const uint32_t count = m_vClones.m_ui32NbUsedElt;
    for (uint32_t i = 0; i < count; ++i) {
        IKSerializable* clone = m_vClones.m_pBlock[i];
        if (clone != nullptr) clone->RecursiveRegistration(0);  // vt+0x24
    }
}
