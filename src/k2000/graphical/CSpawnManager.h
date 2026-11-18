// CSpawnManager.h - the spawn pools of instanced geometry (key 0xb8d, vtable 0xb179c0, size 0x44).
// Original unit: CSpawnManager.cpp (0xb8da0..). XXL2: K/KModules/KGL/Main/CSpawnManager.h
// (m_ui32NbPool, m_apSpawnPool, m_vpSpawnPoolParams, read in that order); DotD adds two vectors. A renderer
// stage manager: created by InitializeRendererStages (renderer +0xb8), handed to the loader as the global
// 13:46. Every file has one; only LVL000's has data (four zero counts).
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/math/CMatrix34.h"
#include "k2000/graphical/IRendableObject.h"
#include "k2000/util/TVector.h"

class CSpawnManager : public IRendableObject {
public:
    DOTD_CLASS_KEY(kCategoryGraphical, 0x2e)
    DOTD_DECLARE_FACTORIES(CSpawnManager)

    // An entry of m_vUnk20 (0x1c bytes on the PS3): Load reads only the reference. Name ours.
    struct SEntry {
        IKSerializable* m_pObject;  // +0x00 a scene node (its frame at +4)
        CVector3 m_vPos;            // +0x04 not written by Load; the node's last position (UpdateAndExtract)
        CVector3 m_vDir;            // +0x10 not written by Load; its normalised motion since then
    };

    CSpawnManager();                  // 0x000b9638 CSpawnManager_Create (inlined; = CSpawnManager_Construct 0xb8da0)
    ~CSpawnManager() override;        // 0x000b9e70 / 0x000b96c0 CSpawnManager_Destructor / _DeletingDestructor
    // vt+0x08 0x9a1060
    int32_t IsKindOfClass(uint32_t key) override { return key == 0xb8d || key == 0xa8d || key == 0xc; }
    void Destroy() override;                                // vt+0x10 0x000b92c8 CSpawnManager_Destroy
    int32_t Load(IKFile* file, int32_t type) override;      // vt+0x2c 0x000b9978 CSpawnManager_Load
    // 0x000b9448 CSpawnManager_StopAllShakeCaches_maybe (CKGraphic_Stop): every pool's shake caches stopped.
    void StopAllShakeCaches();
    // 0x000b93c8 CSpawnManager_StartPoolShakeCaches_maybe (CKGraphic_PreSectorLoaded): every pool's slot started.
    void StartPoolShakeCaches(int32_t slot);
    void Init();                                            // 0x000b90e8 CSpawnManager_Init_maybe
    // 0x000b9270 CSpawnManager_Shutdown_maybe (CRenderer_Shutdown_maybe): m_vUnk20's block freed, the vector emptied.
    void Shutdown();
    int32_t GetSerializationFlags() override { return 0; }  // vt+0x34 0x9a1098
    // vt+0x1c 0x000b9528 CSpawnManager_MessageProc: 1.
    int32_t MessageProc(uint16_t /*message*/, void* /*data*/) override { return 1; }
    // vt+0x24 0x000b91a0 CSpawnManager_RecursiveRegistration: IRendableObject's (0xa71e8), then 1.
    void RecursiveRegistration(int32_t type) override { IRendableObject::RecursiveRegistration(type); }
    int32_t PostLoad(int32_t /*type*/) override { return 1; }  // vt+0x30 0x000b9530 CSpawnManager_PostLoad
    // vt+0x70 0x000b8e00 CSpawnManager_CanBeUpdated: the renderer's bit 1 (the scene roots are not extracted) is clear.
    int32_t CanBeUpdated() override;
    // 0x000b8e20 KStub_Nop_b8e20 (CKGraphic_PostSectorUnload calls it on the spawn manager): nothing.
    void PostSectorUnload() {}
    // vt+0x54 0x000b91c8 CSpawnManager_Update: each pool param with its +0x04 bit 0 set gets KStub_Nop_b7b70 (nothing).
    void PreUpdate(IKTime*) override {}
    // vt+0x58 0x000b9780 CSpawnManager_Enqueue: every entry's node position remembered with its motion direction (none
    // on the first frame after a reset: +0x14 bit 8); then bit 8 cleared.
    void UpdateAndExtract(float, RenderQueue**, IKTime*, RwCamera*, int32_t) override;
    void Render(IKTime* /*frameClock*/) override {}                               // vt+0x5c 0x009a10a0 CSpawnManager_Render: a bare blr

    uint32_t m_ui32NbPool;                             // +0x18
    IKSerializable** m_apSpawnPool;                    // +0x1c CKSpawnPool references (Mem_AllocAligned16)
    TVector<SEntry, 2> m_vUnk20;                       // +0x20 read last; capacity 2
    TVector<IKSerializable*, 2> m_vpSpawnPoolParams;   // +0x2c references (XXL2: the vector read after the pools)
    TVector<IKSerializable*, 2> m_vUnk38;              // +0x38 references
};
DOTD_ASSERT_SIZE(CSpawnManager::SEntry, 0x1c);
DOTD_ASSERT_SIZE(CSpawnManager, 0x44);
DOTD_ASSERT_OFFSET(CSpawnManager, m_ui32NbPool, 0x18);
DOTD_ASSERT_OFFSET(CSpawnManager, m_apSpawnPool, 0x1c);
DOTD_ASSERT_OFFSET(CSpawnManager, m_vUnk20, 0x20);
DOTD_ASSERT_OFFSET(CSpawnManager, m_vpSpawnPoolParams, 0x2c);
DOTD_ASSERT_OFFSET(CSpawnManager, m_vUnk38, 0x38);
