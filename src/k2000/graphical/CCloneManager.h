// CCloneManager.h - the renderer's RpTeam of cloned instances (key 0xcd, vtable 0xb16918, size 0x68; the
// renderer's +0x94). Original unit: CCloneManager.cpp (0x864b8..). XXL2: K/KModules/KGL/Main/
// CCloneManager.h (IRendableObject: m_pRpTeam, m_shadows, m_ui32NbInstanceClones, m_vClones,
// m_aui32SqrLodRanges); the PS3 offsets are the XXL2 members in the same order.
#pragma once
#include <cstdint>

#include "Renderware/rpteam/RpTeam.h"
#include "k2000/core/Layout.h"
#include "k2000/graphical/IRendableObject.h"
#include "k2000/util/TVector.h"

struct RpMaterial;

class CCloneManager : public IRendableObject {
public:
    DOTD_CLASS_KEY(kCategoryGraphical, 3)
    DOTD_DECLARE_FACTORIES(CCloneManager)

    CCloneManager();                                    // 0x000873d0 CCloneManager_Create (inlined)
    ~CCloneManager() override;                          // 0x00087a98 CCloneManager_Destructor
    int32_t IsKindOfClass(uint32_t key) override { return key == 0xcd || key == 0xa8d || key == 0xc; }  // 0x99c288
    void Destroy() override;                            // vt+0x10 0x00086f68 CCloneManager_Destroy
    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x00087440 CCloneManager_Load
    int32_t GetSerializationFlags() override { return 0; }  // vt+0x34 0x99c2c0
    // vt+0x30 0x000872d0 CCloneManager_PostLoad: for the level (type 0) the team elements' geometries get the tangent flag.
    int32_t PostLoad(int32_t type) override;
    // vt+0x58 0x00086cf0 CCloneManager_UpdateAndExtract (Ghidra CCloneManager_EnqueueVisibleClones in the checklist): the players
    // whose CClone was queued this frame (stamp = the render frame counter) are switched on, the others off, the render lists
    // rebuilt; when any is on, the manager joins render stage 6.
    void UpdateAndExtract(float maxDistanceSquared, RenderQueue** stages, IKTime* frameClock, RwCamera* camera,
                          int32_t distanceCull) override;
    // vt+0x5c 0x00086eb8 CCloneManager_Render (CCloneManager_DrawClones): no face culling, then the team's passes 2 | 4 | 8.
    void Render(IKTime* frameClock) override;
    // vt+0x70 0x000872b0 CCloneManager_CanBeUpdated: not while the renderer skips the scene roots' extraction (bit 2 of its flags).
    int32_t CanBeUpdated() override;
    // vt+0x24 0x000871a8 CCloneManager_RecursiveRegistration: type 0 registers the manager, then every clone's own (type 0).
    void RecursiveRegistration(int32_t type) override;
    // vt+0x6c 0x00086548 CCloneManager_GetRenderingProperties: 0, 0xff, 1, blend mode 1.
    void GetRenderingProperties(uint8_t* first, uint8_t* second, uint8_t* third, uint32_t* blendMode) override;
    // 0x00086708 CCloneManager_GetTeamElementFirstMaterial: the first RpMaterial of the geometry of the LOD 0 atomic of
    // dictionary element `index` (the clone materials' CMaterial adopts it in its PostLoad).
    RpMaterial* GetTeamElementFirstMaterial(uint32_t index);
    // 0x00086828 CCloneManager_SetFlag200OnTeamElementsWithMaterialMode10To14: a geometry whose material is a normal-mapped
    // mode (10-14) gets the geometry flag 0x200 (tangents).
    void SetFlag200OnTeamElementsWithMaterialMode10To14();

    RpTeam* m_pRpTeam;                         // +0x18 null when the file holds no clones
    RpTeamShadows m_shadows;                   // +0x1c Load sets number 0, shadowLOD 5
    uint32_t m_ui32NbInstanceClones;           // +0x48
    TVector<IKSerializable*, 10> m_vClones;    // +0x4c CNode* (handles)
    uint32_t m_aui32SqrLodRanges[4];           // +0x58
};
DOTD_ASSERT_SIZE(CCloneManager, 0x68);
DOTD_ASSERT_OFFSET(CCloneManager, m_pRpTeam, 0x18);
DOTD_ASSERT_OFFSET(CCloneManager, m_shadows, 0x1c);
DOTD_ASSERT_OFFSET(CCloneManager, m_ui32NbInstanceClones, 0x48);
DOTD_ASSERT_OFFSET(CCloneManager, m_vClones, 0x4c);
DOTD_ASSERT_OFFSET(CCloneManager, m_aui32SqrLodRanges, 0x58);
