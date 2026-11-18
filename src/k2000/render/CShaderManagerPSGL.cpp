// CShaderManagerPSGL.cpp - reconstructed original translation unit 0xf7f30-0xfdb40 (GAME_TOC1, main_toc1), 47 functions, 38 live.
// Primary owner: CShaderManagerPSGL (not a registered class)
// Other owners: CShaderManager (5), KBase11CD (4), ShaderProgramCache (3), ShaderCache (3), ShaderVariantMap (3), Shader (2), Debug (2)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [ ] 0xf7f30  StaticInitAndDestruction_MeshShaderPassState_maybe  [platform]  (the static mesh pass state 0xc685c0 is CShaderManagerPSGL_2.cpp's g_pass, built per mesh by PreparePSGLAtomicMeshShaders)
//   [ ] 0xf7fb8  _GLOBAL__D_f7fb8
//   [ ] 0xf7fc8  _GLOBAL__I_f7fc8
//   [x] 0xf7fd8  BeginRenderCameraUpdate
//   [ ] 0xf8000  Shader_CopyShdescBinPath_maybe  [dead]
//   [ ] 0xf80b8  Shader_CopyShfctBinPath_maybe  [dead]
//   [x] 0xf8168  ShaderManagerPSGL_TryAssignOverride_maybe
//   [ ] 0xf8200  ShaderProgramCache_FindPixelShader_maybe  [platform]  (the pixel shader cache lookup: replaced by design: platform/gfx/cg_program translates the Cg programs to GLSL per variant)
//   [ ] 0xf8380  ShaderProgramCache_FindVertexShader_maybe  [platform]  (the vertex shader cache lookup: replaced by design: platform/gfx/cg_program translates the Cg programs to GLSL per variant)
//   [ ] 0xf8500  Debug_PrintMatrix4x4_maybe  [dead]
//   [ ] 0xf86c0  Debug_PrintRwMatrix_maybe  [dead]
//   [x] 0xf8828  KStub_Nop_f8828  (empty)
//   [x] 0xf8830  KStub_Return1_f8830  (KBase11CD vt+0x28 Save: 1, IKSerializable's default)
//   [x] 0xf8838  KStub_Return1_f8838  (KBase11CD vt+0x24 RecursiveRegistration: nothing, IKSerializable's default)
//   [ ] 0xf8840  CShaderManagerPSGL_GetShaderModeForKey_maybe  [platform]  (the Cg profile mode of a shader object's compile: replaced by design: platform/gfx/cg_program translates the Cg programs to GLSL per variant)
//   [x] 0xf8888  KBase11CD_vf2C
//   [ ] 0xf89d0  ShaderProgramCache_FindPair_maybe  [platform]  (the program pair lookup: replaced by design: platform/gfx/cg_program translates the Cg programs to GLSL per variant)
//   [ ] 0xf8b88  ShaderCache_ReadVariantKeyLists_maybe  [platform]  (the PS3 shader cache files: replaced by design: platform/gfx/cg_program translates the Cg programs to GLSL per variant)
//   [ ] 0xf8f48  CShaderManagerPSGL_ConstructMembers_2_maybe  [dead: no pointer to its descriptor 0xb55aa8, no call]
//   [ ] 0xf9138  CShaderManagerPSGL_ConstructMembers_maybe  [platform]  (the members: the scalar ones are CShaderManagerPSGL's initializers, the hash tables, variant key, request, matrix cache object and uniform pool the GL backend's (cg_program, ShaderMatrixCache.cpp))
//   [ ] 0xf9328  ShaderCache_WriteEntries_maybe  [platform]  (the PS3 shader cache files: replaced by design: platform/gfx/cg_program translates the Cg programs to GLSL per variant)
//   [ ] 0xf97e0  ShaderCache_SaveToFile_maybe  [dead: no pointer to its descriptor 0xb55ad8, no call]
//   [ ] 0xf9a18  CShaderManager_ClearVertexShaderCache_maybe  [platform]  (the vertex shader object cache: replaced by design: platform/gfx/cg_program translates the Cg programs to GLSL per variant)
//   [ ] 0xf9d40  CShaderManager_ClearPixelShaderCache_maybe  [platform]  (the pixel shader object cache: replaced by design: platform/gfx/cg_program translates the Cg programs to GLSL per variant)
//   [ ] 0xfa068  KBase11CD_vf54  [platform]  (the caches released: CShaderManagerPSGL::ReleaseShaderResources releases the GLSL programs instead)
//   [ ] 0xfa198  ShaderVariantMap_InsertOrUpdate_maybe  [platform]  (the variant map: replaced by design: platform/gfx/cg_program translates the Cg programs to GLSL per variant)
//   [ ] 0xfa4c0  CShaderManagerPSGL_DestructMembers_maybe  [platform]  (the members destroyed: the global cleared in BootStubs.cpp's ~CShaderManagerPSGL, the rest the GL backend's)
//   [ ] 0xfa858  KBase11CD_Destructor  [platform]  (KBase11CD's destructor (the members, as 0xfa4c0): the GL backend's)
//   [ ] 0xfabf0  KBase11CD_DeletingDestructor  [platform]  (KBase11CD's deleting destructor (the members, as 0xfa4c0): the GL backend's)
//   [ ] 0xfaf98  CShaderManagerPSGL_LoadShaderCache_maybe  [platform]  (the PS3 shader cache files: replaced by design: platform/gfx/cg_program translates the Cg programs to GLSL per variant)
//   [ ] 0xfb7d8  CShaderManagerPSGL_LoadShaderCache_maybe  [dead: no pointer to its descriptor 0xb55bb0, no call]
//   [ ] 0xfb7e0  CShaderManagerPSGL_LoadShaderCacheFile_2_maybe  [dead: no pointer to its descriptor 0xb55bb8, no call]
//   [ ] 0xfb958  CShaderManagerPSGL_LoadShaderCacheFile_3_maybe  [dead: no pointer to its descriptor 0xb55bc0, no call]
//   [ ] 0xfbad0  CShaderManagerPSGL_LoadShaderCacheFile_maybe  [platform]  (the PS3 shader cache files: replaced by design: platform/gfx/cg_program translates the Cg programs to GLSL per variant (BootLoadRequest_Execute_maybe's call: BootStubs.cpp))
//   [ ] 0xfbc50  ShaderVariantMap_InsertOrReplace_maybe  [dead]
//   [ ] 0xfbf28  CShaderManager_CacheMissingShaderVariant_maybe  [platform]  (the PS3 shader cache files: replaced by design: platform/gfx/cg_program translates the Cg programs to GLSL per variant)
//   [ ] 0xfc798  CShaderManager_CacheShaderVariantList_maybe  [dead: no pointer to its descriptor 0xb55be0, no call]
//   [ ] 0xfc820  CShaderManager_CacheGeneratedShaderVariants_maybe  [dead]
//   [ ] 0xfc928  CShaderManagerPSGL_WriteCacheAndClearMaps_maybe  [platform]  (the PS3 shader cache files: replaced by design: platform/gfx/cg_program translates the Cg programs to GLSL per variant)
//   [ ] 0xfcc90  CShaderManagerPSGL_LoadShaderDescFiles_maybe  [platform]  (the .shdesc / .shfct description files: replaced by design: platform/gfx/cg_program translates the Cg programs to GLSL per variant)
//   [ ] 0xfd110  CShaderManagerPSGL_LoadShaderFctFile_maybe  [dead]
//   [ ] 0xfd120  ShaderVariantMap_InsertOrReplace_2_maybe  [dead]
//   [ ] 0xfd3f8  CShaderManagerPSGL_FindOrCreatePrograms_maybe  [platform]  (the programs of a variant, found or compiled: ShaderVariant_GetProgram (cg_program))
//   [x] 0xfda80  BindSelectedPSGLShaderPrograms  (SelectProgram in CShaderManagerPSGL_2.cpp)
//   [ ] 0xfdb28  KStub_Return0_fdb28  [dead]
//   [ ] 0xfdb30  PixelShaderObject_SetCgProgram_maybe  [platform]  (a Cg shader object of the PS3 program cache: replaced by design: platform/gfx/cg_program translates the Cg programs to GLSL per variant)
//   [ ] 0xfdb38  KStub_Nop_fdb38  [platform]  (a Cg shader object of the PS3 program cache: replaced by design: platform/gfx/cg_program translates the Cg programs to GLSL per variant)
//
//   [ ] 0x9a5ad0  KBase11CD_vf14  [inline]
//   [ ] 0x9a5ad8  KBase11CD_vf18  [inline]
//   [ ] 0x9a5ae0  KBase11CD_vf58  [inline]
//   [ ] 0x9a5ae8  KBase11CD_vf5C  [inline]
//   [ ] 0x9a5af0  KBase11CD_vf60  [inline]
//   [ ] 0x9a5af8  KStub_Nop_9a5af8  [inline]
//   [ ] 0x9a5b00  ShaderVariantHashTable_HashKey  [inline]
//   [ ] 0x9a5b88  KStub_Nop_9a5b88  [inline]
//   [ ] 0x9a5cd0  KBase11CD_vf8  [inline]
//   [ ] 0x9a5cf0  ShaderVariantHashTable_HashKey_2  [inline]
//   [ ] 0x9a5d78  ShaderVariantHashTable_DeletingDestructor_2  [inline]
//   [ ] 0x9a5eb8  ShaderVariantHashTable_Destructor_2  [inline]
//   [ ] 0x9a5ff0  ShaderVariantHashTable_Destructor  [inline]
//   [ ] 0x9a6118  ShaderVariantHashTable_DeletingDestructor  [inline]
#include "k2000/render/CShaderManagerPSGL.h"

#include "Renderware/rpskin/RpSkin.h"
#include "Renderware/rpworld/RpAtomic.h"
#include "Renderware/rwcore/RwCamera.h"
#include "k2000/io/IKFile.h"
#include "k2000/render/ShaderMatrixCache.h"

// 0x000f7fd8 BeginRenderCameraUpdate (BeginCameraUpdateAndCacheShaderMatrices 0x247ff8 inlined).
RwCamera* BeginRenderCameraUpdate(RwCamera* camera) {
    RwCamera* begun = RwCameraBeginUpdate(camera);
    if (g_pShaderManager != nullptr && g_pShaderManager->m_bShadersEnabled != 0) ShaderMatrixCache_BeginCamera();
    return begun;
}

// 0x000f8168 ShaderManagerPSGL_TryAssignOverride_maybe (from the assembly; RpSkinGeometryGetSkin through its bridge
// 0x98e910). The result is the int the caller masks to a byte.
int32_t CShaderManagerPSGL::TryAssignOverride(RpAtomic* atomic) {
    if (m_bAtomicPipeline == 0 || m_pAtomicPipeline == nullptr) return 0;
    // Host guard: an atomic without a geometry counts as unskinned (RpSkinGeometryGetSkin would read through null).
    if (atomic->geometry != nullptr && RpSkinGeometryGetSkin(atomic->geometry) != nullptr) return 1;
    atomic->pipeline = m_pAtomicPipeline;
    return 1;
}

// 0x000f8888 KBase11CD_vf2C: the base's Load. The level (type 0) gives six words, then two (each block
// is one Read, then swapped word by word).
int32_t CShaderManagerPSGL::LoadBase(IKFile* file, int32_t type) {
    if (type == 0) {
        ReadU32LEWords(file, m_unk64, 6);
        ReadU32LEWords(file, m_unk7c, 2);
    }
    return 1;
}
