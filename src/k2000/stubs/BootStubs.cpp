// BootStubs.cpp - stand-ins for everything the C1.1 boot path calls that is not ported yet.
//
// Each block names the checkpoint that replaces it. When a unit is ported, delete its stand-ins here:
// duplicate definitions then show up as link errors, so nothing is left behind by accident.
// Constructors of registry-created classes are traced by the class table (ClassTable.cpp); the others
// trace themselves, so the boot trace lists subsystems in creation order.
#include <cstdio>
#include <cstring>

#include "Renderware/rphanim/RpHAnim.h"
#include "Renderware/rt2d/Rt2d.h"
#include "Renderware/rtanim/RtAnim.h"
#include "Spyro2008/logic/CKS08GameManager.h"
#include "k2000/cameras/CameraContext.h"
#include "k2000/core/Stub.h"
#include "k2000/graphical/system/CVideoManager.h"
#include "k2000/graphical/ui/CKFlashManager.h"
#include "k2000/graphical/ui/CManager2d.h"
#include "k2000/io/KFileSystem.h"
#include "k2000/io/KHostFS.h"
#include "k2000/io/LoadRequests.h"
#include "k2000/logic/CDefaultGameManager.h"
#include "k2000/logic/CKCoreManager.h"
#include "k2000/logic/CKLevel.h"
#include "k2000/logic/CKSavingManager.h"
#include "k2000/logic/io/CKLoadingManager.h"
#include "k2000/logic/ui/CLocManager.h"
#include "k2000/managers/CKGraphic.h"
#include "k2000/managers/CKInput.h"
#include "k2000/managers/CKServiceManager.h"
#include "k2000/misc/CKGameLoop.h"
#include "k2000/misc/ClassRegistry.h"
#include "k2000/misc/Engine.h"
#include "k2000/misc/ClassManager.h"
#include "k2000/misc/JobQueue.h"
#include "k2000/managers/CKSoundManager.h"
#include "k2000/render/CRenderer.h"
#include "k2000/render/CShaderManagerPSGL.h"
#include "k2000/render/TextureBank.h"
#include "k2000/graphical/IRendableObject.h"
#include "platform/cell/sysutil.h"

struct ParticleUpdateScheduler;

// ==== C1.4: graphics ============================================================================

IKBaseClass* CKGraphic::Create() { return new CKGraphic(); }
void CKGraphic::Delete(IKBaseClass* object) { delete object; }
void CKGraphic::Start() {}
void CKGraphic::Update(IKTime*) {}
void CKGraphic::PreUpdate(IKTime*) {}
void CKGraphic::PostUpdate(IKTime*) {}

// CKGraphic_InitializeModule: RwEngineInit/Open/Start on the PSGL device, the RW plugins, then the shader
// manager (key 0x124d), the TextureBank and CAnimationManager (key 0x20d).
int32_t CKGraphic::InitializeModule(void*) {
    dotd::trace::Boot("CKGraphic::Init (RenderWare engine + PSGL device: stand-in)");
    g_pShaderManager = static_cast<CShaderManagerPSGL*>(ClassRegistry_CreateObjectByKey(0x124d));
    m_pTextureManager = new TextureBank();  // TextureBank_Construct_maybe
    Engine_SetTextureBank(m_pTextureManager);
    // The RenderWare plugins' opens that matter to animations, in the engine start's order: RtAnim (the scheme table),
    // RpHAnim (scheme 1: _rpHAnimOpen_maybe 0x6e8070) and the compressed scheme 2 (0x71f5c0).
    RtAnimInitialize();
    RpHAnimPluginOpen();
    RtCompressedKeyFrameRegister();
    m_animationManager = static_cast<IKSerializable*>(ClassRegistry_CreateObjectByKey(0x20d));  // CAnimationManager
    Engine_SetAnimationManager(reinterpret_cast<CAnimationManager*>(m_animationManager));
    // The hardware caps (0x5a9f0..0x5aa60, bit by bit in the original's order): 1, 4, 2 set, 0x28 cleared, 0x20, 0x40, 0x80,
    // 0x100 set, 0x410 cleared, 0x400, 0x200 set: 0x7e7 from 0 (the live value in LVL010). 0x400: the post effects
    // (CPostRenderingFx, CKPBuffer); 0x200: 32-bit camera textures and the depth of field path.
    uint32_t caps = m_baHardwareCaps;
    caps = (caps & ~1u) | 1u;
    caps = (caps & ~4u) | 4u;
    caps = (caps & ~2u) | 2u;
    caps &= ~0x28u;
    caps |= 0x20u;
    caps = (caps & ~0x40u) | 0x40u;
    caps = (caps & ~0x80u) | 0x80u;
    caps = (caps & ~0x100u) | 0x100u;
    caps &= ~0x410u;
    caps |= 0x400u;
    caps = (caps & ~0x200u) | 0x200u;
    m_baHardwareCaps = caps;
    return 1;
}

// CKGraphic::CreateRenderer 0x599c0: k2000/managers/CKGraphic.cpp (C2.8 port-all P21).

// CRenderer (constructor, InitializeStages, RenderGameFrame, RenderFallbackFrame): k2000/render/CRenderer.cpp (C1.4).


CShaderManagerPSGL* g_pShaderManager = nullptr;  // 0x00c685e0
// 0x000ffc40 CShaderManagerPSGL_Destructor -> CShaderManagerPSGL_DestructMembers_maybe 0xfa4c0: the global cleared (the
// rest of it, the pipelines +0x04 / +0x60, the request queue +0x8508, the request +0x90 and the caches, are members the
// remake's stand-in class does not have: C1.4).
CShaderManagerPSGL::~CShaderManagerPSGL() {
    if (g_pShaderManager == this) g_pShaderManager = nullptr;  // g_ShaderManagerPSGL = 0
}
IKBaseClass* CShaderManagerPSGL::Create() { return new CShaderManagerPSGL(); }
void CShaderManagerPSGL::Delete(IKBaseClass* object) { delete object; }
void CShaderManagerPSGL::Start() { dotd::trace::Boot("CShaderManagerPSGL::Start (Cg context: stand-in)"); }
// 0x000f39a0 ShaderUniforms_ReleaseBuiltinRecords_maybe: the 0x28 built-in uniform records (g_BuiltinShaderUniformRecords,
// ShaderUniformRecord_Reset_maybe 0xf31b8 each) and their buffers (ShaderUniforms_FreeBuiltinBuffers_maybe 0xf3338)
// released. STUB(C1.4): the records are InitializeBuiltinShaderUniformRecords' (0xf3488, not ported: the remake's uniform
// values are bound per GL program by CShaderManagerPSGL_2.cpp), so there is nothing to release.
void ShaderUniforms_ReleaseBuiltinRecords() {}

// ==== C1.6 / M1: services ========================================================================

CKServiceManager::~CKServiceManager() {}
IKBaseClass* CKServiceManager::Create() { return new CKServiceManager(); }
void CKServiceManager::Delete(IKBaseClass* object) { delete object; }

// ==== C1.2: files, loading, the object database ===================================================

// KFileSystem::SetExecutablePath (0x49770 CopyString4Offset) / SetDataRoot (0x496c8): k2000/memory/KMemBuffer.cpp
// (C2.8 port-all P21).
void KFileSystem::InitSaveDevice() { dotd::trace::Boot("KFileSystem_InitSaveDevice (stand-in)"); }

namespace {
KHostFS* s_pHostFS = nullptr;  // 0x00c5b840
}  // namespace
// KHostFS_Construct 0x50248: KHostFS_ConstructBase_maybe registers the instance; the request queue (+0x20) is the
// member's constructor (CKFileSystemRequestQueue_Construct 0x4f3e8); the rest is the stand-in's (KHostFS.h).
KHostFS::KHostFS() { s_pHostFS = this; }
// KHostFS_Destructor 0x515c0: the request queue's destructor is the member's; the rest is the stand-in's.
KHostFS::~KHostFS() {}
// 0x00051990 KHostFS_GetInstance
KHostFS* KHostFS_GetInstance() { return s_pHostFS; }
void KHostFS::Init() { dotd::trace::Boot("KHostFS::Init (RtFS, ELB:, request thread: stand-in)"); }
void KHostFS::PreopenRwsFiles() {}
void KHostFS::PollDevice() {}
// 0x0004fcb0 KHostFS_vf24: no read request in flight (the request thread is STUB(C1.2): reads are synchronous).
uint8_t KHostFS::IsIdle() { return 1; }
uint8_t KHostFS::IsReadIdle() { return 1; }  // C1.6 gm: as IsIdle (the native reads are synchronous)
KHostFS* KHostFS_Create() {
    dotd::trace::Boot("create KHostFS");
    return new KHostFS();
}

// CKSavingManager: k2000/logic/CKSavingManager.cpp.

IKBaseClass* CKLevel::Create() { return new CKLevel(); }
void CKLevel::Delete(IKBaseClass* object) { delete object; }

// CLocManager's destructor and factories: k2000/logic/ui/CLocManager.cpp.

// The texture registry (FindTextureByName, TextureRef_AddRef/Release): k2000/render/Texture.cpp (C1.4).

void SaveData_InitDirNamePrefix();  // k2000/io/SaveData.cpp
void BootLoadRequest::Execute() {
    dotd::trace::Boot("boot load: pre-open RWS, save data, Shader/ps3/shfct.bin (stand-in)");
    // BootLoad_InitSaveData_maybe 0x14698 (C2.8 port-rest R05, CDefaultGameManager.cpp): the save device's vt+0x00 (the
    // default device's KStub_Return1), then the save folders' prefix.
    BootLoad_InitSaveData();
}

void Uuid_ParseHexString(uint8_t* uuid, const char*) { std::memset(uuid, 0, 16); }

// ==== C1.6: the game manager =====================================================================

CDefaultGameManager::CDefaultGameManager()
    : m_level(nullptr),
      m_playerArray(nullptr),
      m_players(),
      m_playerStride(0),
      m_flags64(0),
      m_gameStructure(nullptr),
      m_pBootingVideo(nullptr),
      m_unk274(0),
      m_currentLevel(-1),
      m_requestedLevel(-1),
      m_requestedSector(-2),
      m_unk288(-1),
      m_unk28c(-1),
      m_i32RequestedLanguage(-1),
      m_bLevelChangePending(0) {
    // The IKGameManager part of CKS08GameManager_ConstructBase_maybe (0x4edee0); the KMemBuffers are
    // built by their constructors. The initialisers above are the stand-in's (InitImpl sets them).
    m_guidSave[0] = 0;
    m_guidSave[3] = 0;
    m_guidSave[1] = 0;
    m_guidSave[2] = 0;
    m_guidPendingSave[3] = 0;
    m_guidPendingSave[0] = 0;
    m_guidPendingSave[1] = 0;
    m_guidPendingSave[2] = 0;
    m_unk151 = 0xff;
    m_unk148 = 0;
    m_unk14c = 0;
    m_unk150 = 0;
    for (uint32_t& word : m_unk154) word = 0;
    m_unk220[3] = 0;
    m_unk220[0] = 0;
    m_unk220[1] = 0;
    m_unk220[2] = 0;
    m_unk230[3] = 0;
    m_unk230[0] = 0;
    m_unk230[1] = 0;
    m_unk230[2] = 0;
    m_unk249 = 1;
    m_unk254[3] = 0;
    m_unk254[0] = 0;
    m_unk254[1] = 0;
    m_unk254[2] = 0;
}
CDefaultGameManager::~CDefaultGameManager() {}

IKBaseClass* CKS08GameManager::Create() { return new CKS08GameManager(); }
void CKS08GameManager::Delete(IKBaseClass* object) { delete object; }

// ==== system message boxes and the job queue (save data) ==========================================


// ==== C1.6 gm: other families' functions the options and the language switch call ===================
// (minimal bodies until their families port them; the merge deletes these)

// 0x00113298 CKSoundManager_SetVolumes_maybe: the free-function form the options call (family audio's port).
void CKSoundManager_SetVolumes(float master, float music, float speech, float sounds, CKSoundManager* manager) {
    manager->SetVolumes(master, music, speech, sounds);
}
// Family audio: 0x001145a8 SoundOutput_GetOutputMode_maybe. The PS3 always has its RWA driver, whose
// KStub_Return6_6eb06c the function's table turns into 5; STUB(audio): the native output has none yet.
int32_t SoundOutput_GetOutputMode(CKSoundOutput* /*output*/) { return 5; }
// Family audio: 0x00114660 SoundOutput_SetOutputMode_maybe (KStub_Nop_6eb040 on the PS3).
void SoundOutput_SetOutputMode(CKSoundOutput* /*output*/, int32_t /*mode*/) {}

// 0x000a4be8 Camera_SetFovAndAspectFromRaster_maybe: ported in k2000/cameras/CameraContext.cpp.


// MessageBox_ClearJobMessageEntries / PushJobMessageEntry / GetJobMessageCount: k2000/misc/MessageBox.cpp.

// CKErrorTable: k2000/misc/CKErrorTable.cpp.

// ==== runtime pieces ===============================================================================

void FreeListPools_InitGlobal() {}
void FreeListPools_FreeAllGlobal() {}
void KThread_InitMainThread() {}
void KThread_ReleaseMainThread() {}
void* KMemoryManager_GetGlobal() { return nullptr; }  // the PS3 build never constructs it
void KStub_Nop_10688() {}
void KStub_Nop_12168() {}
