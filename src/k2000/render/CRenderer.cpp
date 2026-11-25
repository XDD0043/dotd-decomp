// CRenderer.cpp - reconstructed original translation unit 0x9e1a0-0xa2cc0 (GAME_TOC1, main_toc1), 42 functions, 33 live.
// Primary owner: CRenderer (not a registered class)
// Other owners: Apply2DRenderStates (1), FrameDeltaTimeRing (1), PushRenderStates (1), PopRenderStates (1), RegisterCRendererClass (1), ApplySceneRenderStatesAndFog (1), CompareRenderItemsFarToNear (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x9e1a0  Apply2DRenderStates
//   [ ] 0x9e388  CRenderer_Save
//   [ ] 0x9e390  FrameDeltaTimeRing_Push_maybe  [dead]
//   [ ] 0x9e3d8  CRenderer_RunPostRenderingFxVf58_maybe  [dead]
//   [ ] 0x9e4c8  CRenderer_RunPostRenderingFxVf54_maybe  [dead]
//   [x] 0x9e590  PushRenderStates
//   [x] 0x9e858  PopRenderStates
//   [ ] 0x9e960  KStub_Nop_9e960  [dead]
//   [ ] 0x9e968  KStub_Nop_9e968  [dead]
//   [ ] 0x9e970  KStub_Nop_9e970  [dead]
//   [ ] 0x9e978  KStub_Nop_9e978  [dead]
//   [ ] 0x9e980  CRenderer_UnregisterPostRenderingFx_maybe  [dead]
//   [ ] 0x9ea10  RegisterCRendererClass
//   [ ] 0x9ea90  _GLOBAL__I_9ea90
//   [x] 0x9eaa0  CRenderer_RegisterPostRenderingFx_maybe
//   [x] 0x9eb70  CRenderer_ClearReferences
//   [x] 0x9ec10  CRenderer_LevelReset  (CRenderer::RecursiveRegistration)
//   [x] 0x9ed38  ApplySceneRenderStatesAndFog
//   [x] 0x9f0a8  CRenderer_Construct
//   [x] 0x9f208  CRenderer_DestroyArray  (CRenderer::DeleteArray)
//   [x] 0x9f2b0  CRenderer_StageApplySceneStates_maybe
//   [x] 0x9f320  CRenderer_Shutdown_maybe
//   [x] 0x9f588  CompareRenderItemsFarToNear
//   [x] 0x9f5c0  CompareRenderItemsPriorityThenFarToNear  (ComparePriorityThenFarToNear, the queues' sort)
//   [x] 0x9f620  InitializeRendererStages
//   [x] 0x9fd30  ConstructRenderer
//   [x] 0x9fe90  CRenderer_CreateArray  (CRenderer::CreateArray)
//   [x] 0x9ff30  CRenderer_Create
//   [x] 0x9ff70  ExecuteRenderStages4CTo74
//   [x] 0xa04e8  SyncSceneCamerasAndClipPlanes
//   [x] 0xa0a00  SceneRoots_UpdateWorldMatrices_maybe
//   [x] 0xa0ac8  ExecuteRenderStages7CTo90
//   [x] 0xa11b0  RenderFallbackFrame_maybe (the render lwmutex is a PS3 system object: not taken here)
//   [x] 0xa1408  ExecuteRenderStages38To48
//   [x] 0xa1a78  ExecuteRenderStage78
//   [x] 0xa1c08  RenderGameFrame
//   [x] 0xa2180  CRenderer_PostLoad
//   [x] 0xa2330  CRenderer_Load
//   [ ] 0xa26a8  CRenderer_RegisterAllPostRenderingFx_maybe  [dead]
//   [x] 0xa2ab8  CRenderer_DeletingDestructor  (~CRenderer and the delete)
//   [x] 0xa2b70  CRenderer_Destructor
//   [ ] 0xa2c18  CRenderer_Destructor_2_maybe  [dead: no pointer to its descriptor 0xb48bc0, no call]
//
//   [ ] 0x99cd28  CRenderer_GetClassGroup  [inline]
//   [ ] 0x99cd30  CRenderer_GetClassId  [inline]
//   [ ] 0x99cd38  KStub_Nop_99cd38  [inline]
//   [ ] 0x99cd40  KStub_Nop_99cd40  [inline]
//   [x] 0x99cd48  RenderQueueType4_BlendedZWrite_FreeBuffer  [inline]
//   [x] 0x99cda0  RenderQueueType7_TransparentPrio_BeginPass  [inline]
//   [x] 0x99d028  RenderQueueType0_TransparentATestPrio_AllocBuffer  [inline]
//   [x] 0x99d068  RenderQueueType6_TransparentATest_Add  [inline]
//   [ ] 0x99d148  RenderQueueType7_TransparentPrio_IsEmpty  [inline]
//   [x] 0x99d168  RenderQueueType0_TransparentATestPrio_IsEmpty  [inline]
//   [x] 0x99d188  RenderQueueType1_Opaque_IsEmpty  [inline]
//   [ ] 0x99d1a8  RenderQueueType2_OpaqueCutout_IsEmpty  [inline]
//   [ ] 0x99d1c8  RenderQueueType3_Transparent_IsEmpty  [inline]
//   [ ] 0x99d1e8  RenderQueueType4_BlendedZWrite_IsEmpty  [inline]
//   [ ] 0x99d208  RenderQueueType5_TransparentUnsorted_IsEmpty  [inline]
//   [x] 0x99d228  RenderQueueType6_TransparentATest_IsEmpty  [inline]
//   [ ] 0x99d248  RenderQueueType7_TransparentPrio_Clear  [inline]
//   [x] 0x99d258  RenderQueueType0_TransparentATestPrio_Clear  [inline]
//   [x] 0x99d268  RenderQueueType1_Opaque_Clear  [inline]
//   [ ] 0x99d278  RenderQueueType2_OpaqueCutout_Clear  [inline]
//   [ ] 0x99d288  RenderQueueType3_Transparent_Clear  [inline]
//   [ ] 0x99d298  RenderQueueType4_BlendedZWrite_Clear  [inline]
//   [ ] 0x99d2a8  RenderQueueType5_TransparentUnsorted_Clear  [inline]
//   [x] 0x99d2b8  RenderQueueType6_TransparentATest_Clear  [inline]
//   [x] 0x99d2c8  RenderQueueType0_TransparentATestPrio_BeginPass  [inline]
//   [x] 0x99d548  RenderQueueType1_Opaque_BeginPass  [inline]
//   [x] 0x99d7c8  RenderQueueType2_OpaqueCutout_BeginPass  [inline]
//   [x] 0x99da48  RenderQueueType3_Transparent_BeginPass  [inline]
//   [ ] 0x99dcd0  RenderQueueType4_BlendedZWrite_BeginPass  [inline]
//   [x] 0x99df50  RenderQueueType5_TransparentUnsorted_BeginPass  [inline]
//   [x] 0x99e1d8  RenderQueueType6_TransparentATest_BeginPass  [inline]
//   [ ] 0x99e458  CRenderer_IsKindOf  [inline]
//   [ ] 0x99e478  RenderQueueType7_TransparentPrio_Execute  [inline]
//   [ ] 0x99e6e8  RenderQueueType5_TransparentUnsorted_AllocBuffer  [inline]
//   [x] 0x99e728  RenderQueueType6_TransparentATest_AllocBuffer  [inline]
//   [ ] 0x99e768  RenderQueueType7_TransparentPrio_AllocBuffer  [inline]
//   [x] 0x99e7a8  RenderQueueType1_Opaque_AllocBuffer  [inline]
//   [ ] 0x99e7e8  RenderQueueType2_OpaqueCutout_AllocBuffer  [inline]
//   [ ] 0x99e828  RenderQueueType3_Transparent_AllocBuffer  [inline]
//   [ ] 0x99e868  RenderQueueType4_BlendedZWrite_AllocBuffer  [inline]
//   [x] 0x99e8a8  RenderQueueType0_TransparentATestPrio_FreeBuffer  [inline]
//   [x] 0x99e900  RenderQueueType7_TransparentPrio_FreeBuffer  [inline]
//   [x] 0x99e958  RenderQueueType5_TransparentUnsorted_FreeBuffer  [inline]
//   [x] 0x99e9b0  RenderQueueType6_TransparentATest_FreeBuffer  [inline]
//   [x] 0x99ea08  RenderQueueType1_Opaque_FreeBuffer  [inline]
//   [x] 0x99ea60  RenderQueueType2_OpaqueCutout_FreeBuffer  [inline]
//   [x] 0x99eab8  RenderQueueType3_Transparent_FreeBuffer  [inline]
//   [ ] 0x99eb10  RenderQueueType7_TransparentPrio_Add  [inline]
//   [x] 0x99ebf0  RenderQueueType0_TransparentATestPrio_Add  [inline]
//   [x] 0x99ecd0  RenderQueueType1_Opaque_Add  [inline]
//   [x] 0x99edb0  RenderQueueType2_OpaqueCutout_Add  [inline]
//   [ ] 0x99ee90  RenderQueueType3_Transparent_Add  [inline]
//   [ ] 0x99ef70  RenderQueueType4_BlendedZWrite_Add  [inline]
//   [x] 0x99f050  RenderQueueType5_TransparentUnsorted_Add  [inline]
//   [x] 0x99f130  RenderQueueType0_TransparentATestPrio_Execute  [inline]
//   [x] 0x99f510  RenderQueueType1_Opaque_Execute  [inline]
//   [ ] 0x99f690  RenderQueueType2_OpaqueCutout_Execute  [inline]
//   [ ] 0x99f810  RenderQueueType3_Transparent_Execute  [inline]
//   [ ] 0x99fa80  RenderQueueType4_BlendedZWrite_Execute  [inline]
//   [ ] 0x99fe18  RenderQueueType5_TransparentUnsorted_Execute  [inline]
//   [x] 0x9a0068  RenderQueueType6_TransparentATest_Execute  [inline]
#include "k2000/render/CRenderer.h"

#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>

#include "Renderware/rpworld/RpGeometry.h"
#include "Renderware/rpworld/RpWorld.h"
#include "Renderware/rwcore/RwCamera.h"
#include "Renderware/rwcore/RwDevice.h"
#include "Renderware/rwcore/RwIm3D.h"
#include "Renderware/rwcore/RwMatrix.h"
#include "crt/Ps3Qsort.h"
#include "platform/capture_camera.h"
#include "platform/gfx/device.h"
#include "platform/gfx/gpuprof.h"
#include "platform/log.h"
#include "k2000/cameras/CameraContext.h"
#include "k2000/core/Stub.h"
#include "k2000/fx/ParticleUpdateScheduler.h"
#include "k2000/geometry/CGeometry.h"
#include "k2000/graphical/CBackgroundManager.h"
#include "k2000/graphical/CSpawnManager.h"
#include "k2000/graphical/memory/CKPBuffer.h"
#include "k2000/graphical/render/CBackgroundCopyRender.h"
#include "k2000/graphical/render/CPostRenderingFx.h"
#include "k2000/logic/CKCoreManager.h"
#include "k2000/managers/CKGraphic.h"
#include "k2000/render/CShaderManagerPSGL.h"
#include "k2000/graphical/render/CLightManager.h"
#include "k2000/graphical/render/CLightSet.h"
#include "k2000/cameras/CKSrvCamera.h"
#include "k2000/graphical/IRendableObject.h"
#include "k2000/graphical/system/CVideoManager.h"
#include "k2000/misc/CKGameLoop.h"
#include "k2000/graphical/ui/CKFlashManager.h"
#include "k2000/graphical/ui/CManager2d.h"
#include "k2000/logic/CKLevel.h"
#include "k2000/io/IKFile.h"
#include "k2000/misc/ClassRegistry.h"
#include "k2000/misc/CoreSingletons.h"
#include "k2000/misc/Engine.h"
#include "k2000/misc/Mat4.h"
#include "k2000/scenegraph/CSGBranch.h"
#include "k2000/services/CKSrvShadow.h"

CRenderer* g_pRenderStateRenderer = nullptr;  // 0x00c5c90c
uint16_t g_ui16RenderFrameCounter = 0;         // 0x00c29694

const int32_t kBlendTableSrc[4] = {2, 5, 5, 1};   // 0x00c297ec: ONE, SRCALPHA, SRCALPHA, ZERO
const int32_t kBlendTableDest[4] = {1, 6, 2, 4};  // 0x00c297fc: ZERO, INVSRCALPHA, ONE, INVSRCCOLOR

namespace {

void* StateWord(intptr_t value) { return reinterpret_cast<void*>(value); }

// The render-queue state caches (the pass's last blend mode, Z write, alpha test and reference).
uint32_t s_queueBlendMode = 0;   // 0x00c5c870
uint8_t s_queueZWrite = 0;       // 0x00c5c874
uint8_t s_queueAlphaTest = 0;    // 0x00c5c875
float s_queueAlphaRef = 200.0f;  // 0x00c296ac

// 0x0001e178 CKGameLoop_GetGlobalUpdateInhibitByte_maybe (CKGameLoop.cpp): the byte at 0x00ceac59, the XMB open.
uint8_t GetGlobalUpdateInhibitByte() { return CKGameLoop_GetGlobalUpdateInhibitByte(); }

// 0x0009f588 CompareRenderItemsFarToNear: by the sorting coefficient (+0x0c), descending.
int CompareFarToNear(const IRendableObject* a, const IRendableObject* b) {
    const float d = b->m_fSortingCoef - a->m_fSortingCoef;
    if (d == 0.0f) return 0;
    return 0.0f <= d ? 1 : -1;
}

// 0x0009f5c0 CompareRenderItemsPriorityThenFarToNear: the larger priority (+0x08) first, then as above.
int ComparePriorityThenFarToNear(const IRendableObject* a, const IRendableObject* b) {
    if (a->m_pPriorityParent != b->m_pPriorityParent) return a->m_pPriorityParent > b->m_pPriorityParent ? -1 : 1;
    const float d = b->m_fSortingCoef - a->m_fSortingCoef;
    if (d == 0.0f) return 0;
    return d < 0.0f ? -1 : 1;
}

// The comparisons as qsort calls them: on pointers to two array elements (0x00b489b0 / 0x00b489b8).
int FarToNearCompare(const void* a, const void* b) {
    return CompareFarToNear(*static_cast<IRendableObject* const*>(a), *static_cast<IRendableObject* const*>(b));
}
int PriorityThenFarToNearCompare(const void* a, const void* b) {
    return ComparePriorityThenFarToNear(*static_cast<IRendableObject* const*>(a), *static_cast<IRendableObject* const*>(b));
}

// The queues' qsort (TocBridge_qsort -> 0x0095eab0, ported in crt/Ps3Qsort.cpp: equal keys end up in the original's order).
void SortItems(IRendableObject** items, uint32_t count, bool priorityFirst) {
    Ps3Qsort(items, count, sizeof(IRendableObject*), priorityFirst ? PriorityThenFarToNearCompare : FarToNearCompare);
}

}  // namespace

// ==== the render queues (inline in the original: 0x99cd48-0x9a0068) ====================================
// The eight queue classes differ in four things (the vtable slots they fill, 0xb17020-0xb17188): the pass's render
// states (BeginPass), whether the items are sorted and by what (the sorting order given to the item at Add, the qsort
// comparison), and which states each item changes before it is drawn (Execute).

namespace {
struct QueueClass {
    bool zWrite;          // BeginPass: depth write (s_queueZWrite)
    bool blended;         // BeginPass: blend table entry 1 and vertex alpha on (else entry 0 and off)
    bool alphaTest;       // BeginPass: alpha test function 5 (greater) with the reference 200 (else 8 = always)
    int32_t sortOrder;    // Add: ComputeSortingCoef argument (0: the item is not given one)
    bool sorted;          // Execute: qsort (types 0 and 7: priority first)
};
const QueueClass kQueueClasses[8] = {
    /* 0 TransparentATestPrio */ {false, true, true, 1, true},
    /* 1 Opaque               */ {true, false, false, 2, true},
    /* 2 OpaqueCutout         */ {true, false, true, 2, true},
    /* 3 Transparent          */ {false, true, false, 1, true},
    /* 4 BlendedZWrite        */ {true, true, true, 1, true},
    /* 5 TransparentUnsorted  */ {false, true, false, 0, false},
    /* 6 TransparentATest     */ {false, true, true, 1, true},
    /* 7 TransparentPrio      */ {false, true, false, 1, true},
};
}  // namespace

// 0x0099e728 RenderQueueType6_TransparentATest_AllocBuffer (the same in every type)
void RenderQueue::AllocBuffer() {
    m_capacity = 100;
    m_ppItems = static_cast<IRendableObject**>(std::malloc(100 * sizeof(IRendableObject*)));  // Mem_AllocAligned16(400)
}

// 0x0099e9b0 RenderQueueType6_TransparentATest_FreeBuffer (0x0099ea08 Type1, 0x0099e8a8 Type0: the same in every type)
void RenderQueue::FreeBuffer() {
    if (m_ppItems != nullptr) {
        std::free(m_ppItems);  // Mem_FreeAligned16 (AllocBuffer's block)
        m_ppItems = nullptr;
    }
    m_count = 0;
    m_ppItems = nullptr;
}

// 0x0099d068 RenderQueueType6_TransparentATest_Add / 0x0099ecd0 RenderQueueType1_Opaque_Add / 0x0099ebf0 ...Type0 /
// 0x0099edb0 Type2 / 0x0099ee90 Type3 / 0x0099ef70 Type4 / 0x0099f050 Type5 / 0x0099eb10 Type7: appends the item (the
// array grows by 100), then the item's vt+0x74 (ComputeSortingCoef) with the queue's sorting order (opaque types 1, 2: 2;
// types 0, 3, 4, 6, 7: 1; type 5 asks for none).
void RenderQueue::Add(IRendableObject* item) {
    if (m_capacity == m_count) {
        uint32_t capacity = m_count + 100;
        if (capacity == 0) capacity = 100;
        m_ppItems = static_cast<IRendableObject**>(std::realloc(m_ppItems, capacity * sizeof(IRendableObject*)));  // Mem_ReallocAligned16(capacity * 4)
        m_capacity = capacity;
    }
    m_ppItems[m_count] = item;
    ++m_count;
    const int32_t order = kQueueClasses[m_type].sortOrder;
    if (order != 0) item->ComputeSortingCoef(order);
}

// 0x0099e1d8 Type6 / 0x0099d548 Type1 / 0x0099d2c8 Type0 / 0x0099d7c8 Type2 / 0x0099da48 Type3 / 0x0099dcd0 Type4 /
// 0x0099df50 Type5 / 0x0099cda0 Type7 BeginPass: the render states of the pass.
void RenderQueue::BeginPass() {
    const QueueClass& c = kQueueClasses[m_type];
    RwRenderStateSet(rwRENDERSTATEZTESTENABLE, StateWord(m_zTest));
    s_queueZWrite = c.zWrite ? 1 : 0;
    RwRenderStateSet(rwRENDERSTATEZWRITEENABLE, StateWord(s_queueZWrite));
    RwRenderStateSet(rwRENDERSTATESHADEMODE, StateWord(2));
    RwRenderStateSet(rwRENDERSTATECULLMODE, StateWord(2));
    RwRenderStateSet(rwRENDERSTATEVERTEXALPHAENABLE, StateWord(c.blended ? 1 : 0));
    s_queueBlendMode = c.blended ? 1 : 0;
    RwRenderStateSet(rwRENDERSTATESRCBLEND, StateWord(kBlendTableSrc[s_queueBlendMode]));
    RwRenderStateSet(rwRENDERSTATEDESTBLEND, StateWord(kBlendTableDest[s_queueBlendMode]));
    s_queueAlphaRef = 200.0f;  // 0x43480000
    s_queueAlphaTest = c.alphaTest ? 1 : 0;
    RwRenderStateSet(rwRENDERSTATEALPHATESTFUNCTION, StateWord(c.alphaTest ? 5 : 8));
    RwRenderStateSet(rwRENDERSTATEALPHATESTFUNCTIONREF, StateWord(static_cast<intptr_t>(s_queueAlphaRef)));
    // The PSGL driver's GL_ALPHA_TEST enable (0x00cefd40/44) follows s_queueAlphaTest; the device layer
    // applies the alpha test with the render states (rwcore/RwDevice.cpp).
    RwRenderStateSet(rwRENDERSTATEVERTEXALPHAENABLE, StateWord(c.blended ? 1 : 0));
}

// 0x009a0068 Type6 / 0x0099f510 Type1 / 0x0099f130 Type0 / 0x0099f690 Type2 / 0x0099f810 Type3 / 0x0099fa80 Type4 /
// 0x0099fe18 Type5 / 0x0099e478 Type7 Execute: BeginPass, the items sorted, each item's states, its lighting and its
// vt+0x5c.
namespace {
// DEV (platform/gfx/gpuprof.h, not in the original): the renderer's 23 stage queues, so that a queue knows its
// stage number for the GPU measurements and the page's stage switches.
RenderQueue* s_stageQueues[dotd::gfx::gpuprof::kStages] = {};

int StageOf(const RenderQueue* queue) {
    for (int i = 0; i < dotd::gfx::gpuprof::kStages; ++i) {
        if (s_stageQueues[i] == queue) return i;
    }
    return -1;
}

const char* ItemClassName(IRendableObject* item) {
    const KClassInfo* info = FindClassInfo(MakeClassKey(static_cast<uint32_t>(item->GetClassType()),
                                                        static_cast<uint32_t>(item->GetClassID())));
    return info != nullptr ? info->name : "?";
}

}  // namespace

// DEV (gpuprof.h): what identifies an item of a described stage (RenderQueueDebug.cpp).
std::string RenderQueueItemDescription(IRendableObject* item);

void RenderQueue::Execute(IKTime* frameClock) {
    // DEV (gpuprof.h): a stage the page switched off is emptied undrawn; a measured frame marks its start and end.
    const int stage = StageOf(this);
    if (dotd::gfx::gpuprof::StageSkipped(stage)) {
        m_count = 0;
        return;
    }
    dotd::gfx::gpuprof::BeginStage(stage, m_count);
    if (m_type == kOpaque && (dotd::gfx::gpuprof::OpaqueMode() & dotd::gfx::gpuprof::kOpaquePrepass) != 0 && m_count != 0) {
        // DEV (gpuprof.h): the depth pre-pass, the same items with the colour writes off; the pass below then shades
        // only the visible pixels (the device's depth test is GL_LEQUAL).
        const uint32_t count = m_count;
        dotd::gfx::SetColorWrite(false);
        ExecuteItems(frameClock, stage);
        dotd::gfx::SetColorWrite(true);
        m_count = count;
    }
    ExecuteItems(frameClock, stage);
    dotd::gfx::gpuprof::EndStage(stage);
}

void RenderQueue::ExecuteItems(IKTime* frameClock, int stage) {
    const int measuredStage = dotd::gfx::gpuprof::Measuring() ? stage : -1;  // DEV (gpuprof.h)
    const bool describing = dotd::gfx::gpuprof::Describing(stage);
    BeginPass();
    const QueueClass& c = kQueueClasses[m_type];
    if (c.sorted) {
        SortItems(m_ppItems, m_count, m_type == kTransparentATestPrio || m_type == kTransparentPrio);
        // DEV (gpuprof.h): the opaque queue near to far instead (the GPU's depth test then rejects hidden pixels).
        if (m_type == kOpaque && (dotd::gfx::gpuprof::OpaqueMode() & dotd::gfx::gpuprof::kOpaqueReverse) != 0) {
            std::reverse(m_ppItems, m_ppItems + m_count);
        }
    }
    for (uint32_t i = 0; i < m_count; ++i) {
        IRendableObject* item = m_ppItems[i];
        if (m_type != kOpaque && m_type != kOpaqueCutout) {
            uint8_t zWriteWithAlpha = 0, alphaRef = 0, alphaTest = 0;
            uint32_t blendMode = 0;
            item->GetRenderingProperties(&zWriteWithAlpha, &alphaRef, &alphaTest, &blendMode);  // vt+0x6c
            if (s_queueBlendMode != blendMode) {
                s_queueBlendMode = blendMode;
                RwRenderStateSet(rwRENDERSTATESRCBLEND, StateWord(kBlendTableSrc[blendMode]));
                RwRenderStateSet(rwRENDERSTATEDESTBLEND, StateWord(kBlendTableDest[blendMode]));
                // Types 6 and 4: vertex alpha for every mode but 0 (opaque).
                if (m_type == kTransparentATest || m_type == kBlendedZWrite)
                    RwRenderStateSet(rwRENDERSTATEVERTEXALPHAENABLE, StateWord(blendMode != 0 ? 1 : 0));
            }
            if (m_type == kTransparentATestPrio || m_type == kTransparentATest || m_type == kBlendedZWrite) {
                if (alphaTest != s_queueAlphaTest) {
                    RwRenderStateSet(rwRENDERSTATEALPHATESTFUNCTION, StateWord(alphaTest != 0 ? 5 : 8));
                    s_queueAlphaTest = alphaTest;
                }
                if (alphaTest != 0) {
                    // fmuls by 0x3f48c8c9 (0.78431374 = 200 / 255), compared as a double.
                    const float ref = static_cast<float>(alphaRef) * 0x1.91919p-1f;
                    if (ref != s_queueAlphaRef) {
                        RwRenderStateSet(rwRENDERSTATEALPHATESTFUNCTIONREF, StateWord(static_cast<intptr_t>(ref)));
                        s_queueAlphaRef = ref;
                    }
                }
            }
            if (m_type == kTransparentATestPrio || m_type == kTransparentATest) {
                // Z write: off for blend mode 2 (additive); otherwise on, except for an item whose first property
                // byte is set (render flags 0x1a00 or the material's bit 1), which writes depth only while its
                // geometry alpha (the second byte) is below 0xff (0x9a0348 / 0x99f3d8: lbz, nor, clrldi 56, neg,
                // rldicl 1,63 = (~alpha & 0xff) != 0). The port had this test the other way round until
                // live-fixes-4: full-alpha translucent sheets (LVL010's Water_Fall / Water_Waterfall_Wave, the
                // Mec_PFM_Ivy vines) wrote depth, so blended items sorted after them vanished behind the water.
                uint8_t zWrite = 0;
                if (blendMode != 2) zWrite = zWriteWithAlpha != 0 ? static_cast<uint8_t>(alphaRef != 0xff ? 1 : 0) : 1;
                if (zWrite != s_queueZWrite) {
                    s_queueZWrite = zWrite;
                    RwRenderStateSet(rwRENDERSTATEZWRITEENABLE, StateWord(zWrite));
                }
            }
        }
        // ApplyLightingZone 0x994e8 when the item's light set (+0x10) or flag (+0x14 bit 7) differs from the lighting's.
        {
            CLightManager* lighting = g_pLightManager;
            const uint8_t flat = static_cast<uint8_t>((item->m_BitProperties >> 7) & 1);
            if (lighting != nullptr && (lighting->m_pPreviousLightSet != item->m_pLightSet || flat != lighting->m_ui8PreviousFlat)) {
                lighting->ApplyLightingZone(static_cast<const CLightSet*>(item->m_pLightSet), flat);
            }
        }
        // DEV (gpuprof.h): the GPU test's item switches and the measured frames' notes.
        if (dotd::gfx::gpuprof::ItemSkipped(stage, i)) continue;
        if (measuredStage >= 0) dotd::gfx::gpuprof::NoteItem(measuredStage, ItemClassName(item));
        if (describing) dotd::gfx::gpuprof::NoteItemDescription(i, RenderQueueItemDescription(item).c_str());
        item->Render(frameClock);  // vt+0x5c (under the render mutex 0x00cf9c90)
    }
    m_count = 0;
}

// ==== the renderer ======================================================================================

// 0x0009fd30 ConstructRenderer (= 0x9f0a8 CRenderer_Construct): the render-state owner, the 23 empty
// stage slots, the render-state stack (20 x 0x38 bytes), the matrix (+0xd0) and +0xd4 = 99.
CRenderer::CRenderer()
    : m_cameraContext(nullptr),
      m_pRootNode(nullptr),
      m_pSecondaryRootNode(nullptr),
      m_pWorld(nullptr),
      m_cloneManager(nullptr),
      m_manager2d(nullptr),
      m_fFogDistance(0.0f),
      m_bitProperties(0),
      m_backgroundManager(nullptr),
      m_lightManager(nullptr),
      m_flashManager(nullptr),
      m_videoManager(nullptr),
      m_spawnManager(nullptr),
      m_lRenderableObjectList(nullptr),
      m_renderStateDepth(0),
      m_renderStateCapacity(0x14),
      m_pRenderStateStack(nullptr),
      m_fInvFarSquared(0.0f),
      m_pInvCameraMatrix(nullptr),
      m_unkD4(99) {
    g_pRenderStateRenderer = this;
    for (RenderQueue*& stage : m_aStages) stage = nullptr;
    std::memset(m_cFogColor, 0, sizeof(m_cFogColor));
    m_pRenderStateStack = static_cast<uint8_t*>(std::calloc(1, 0x460));  // Mem_AllocAligned16(0x460)
    // 0x0023fa68 RwMatrixCreate_Thunk, then set to the identity (flags 0x20003, the 1.0f of TOC -0x6214).
    CMatrix34* matrix = RwMatrixCreate_Thunk();
    m_pInvCameraMatrix = matrix;
    matrix->m_ui32Flags = 0x20003;
    matrix->m_right.x = 1.0f;
    matrix->m_pos.x = 0.0f;
    matrix->m_at.z = 1.0f;
    matrix->m_up.y = 1.0f;
    matrix->m_up.x = 0.0f;
    matrix->m_right.z = 0.0f;
    matrix->m_right.y = 0.0f;
    matrix->m_at.y = 0.0f;
    matrix->m_at.x = 0.0f;
    matrix->m_up.z = 0.0f;
    matrix->m_pos.z = 0.0f;
    matrix->m_pos.y = 0.0f;
    m_bitProperties |= 0x20;
}

// 0x000a2b70 CRenderer_Destructor: the render-state stack freed, the matrix +0xd0 destroyed (RwMatrixDestroy), the
// renderable list's nodes back to their pool, the lwmutex +0x08 destroyed (a PS3 system object: nothing here).
CRenderer::~CRenderer() {
    std::free(m_pRenderStateStack);  // Mem_FreeAligned16 (the constructor's block)
    RwMatrixDestroy_Thunk(m_pInvCameraMatrix);  // 0x0023f968
    for (RendableNode* node = m_lRenderableObjectList; node != nullptr;) {
        RendableNode* next = node->m_pNext;
        delete node;  // the node pool (TOC -0x6260) takes it back
        node = next;
    }
    m_lRenderableObjectList = nullptr;
}

// 0x0009f320 CRenderer_Shutdown_maybe. The cameras are taken out of the world through the camera context before its null
// check (as in the original; InitializeStages always makes the context).
void CRenderer::Shutdown() {
    for (RenderQueue*& stage : m_aStages) {
        stage->FreeBuffer();  // vt+0x10
        delete stage;         // OperatorDelete_Bridge
        stage = nullptr;
    }
    if (m_manager2d != nullptr) {
        m_manager2d->Shutdown();  // 0x62920
        Engine_SetManager2d(nullptr);
        ClassRegistry_DestroyObject(m_manager2d);
        m_manager2d = nullptr;
    }
    RpWorldRemoveCamera(m_pWorld, m_cameraContext->m_pMainCamera);
    RpWorldRemoveCamera(m_pWorld, m_cameraContext->m_pUICamera);
    RpWorldRemoveCamera(m_pWorld, m_cameraContext->m_pSceneCamera);
    if (m_cameraContext != nullptr) {
        m_cameraContext->DestroyCamerasAndRasters();  // 0xa4350
        delete m_cameraContext;                       // vt+0x04
        m_cameraContext = nullptr;
    }
    if (m_cloneManager != nullptr) {
        ClassRegistry_DestroyObject(m_cloneManager);
        m_cloneManager = nullptr;
    }
    if (m_backgroundManager != nullptr) {
        ClassRegistry_DestroyObject(m_backgroundManager);
        m_backgroundManager = nullptr;
    }
    if (m_flashManager != nullptr) {
        static_cast<CKFlashManager*>(m_flashManager)->DestroyManager();  // 0x6c990 UI2D_DestroyRt2dFreeLists_maybe
        ClassRegistry_DestroyObject(m_flashManager);
        m_flashManager = nullptr;
    }
    if (m_lightManager != nullptr) {
        static_cast<CLightManager*>(m_lightManager)->DestroyRwLights();  // 0x9b3a8
        ClassRegistry_DestroyObject(m_lightManager);
        m_lightManager = nullptr;
    }
    if (m_videoManager != nullptr) {
        m_videoManager->ShutdownVideoSystem();  // 0xa8328 VideoSystem_Shutdown_maybe
        ClassRegistry_DestroyObject(m_videoManager);
        m_videoManager = nullptr;
    }
    if (m_spawnManager != nullptr) {
        static_cast<CSpawnManager*>(m_spawnManager)->Shutdown();  // 0xb9270
        ClassRegistry_DestroyObject(m_spawnManager);
        m_spawnManager = nullptr;
    }
    if (m_pWorld != nullptr) {
        RpWorldDestroy(m_pWorld);
        m_pWorld = nullptr;
    }
}
IKBaseClass* CRenderer::Create() { return new CRenderer(); }  // 0x0009ff30 CRenderer_Create
// C2.8 port-all P18.
// 0x0009fe90 CRenderer_CreateArray (the element size 0xd8 on the PS3)
IKBaseClass* CRenderer::CreateArray(uint32_t count, uint16_t* elementSize) {
    if (elementSize != nullptr) *elementSize = static_cast<uint16_t>(sizeof(CRenderer));
    return new CRenderer[count];
}
// 0x0009f208 CRenderer_DeleteArray: each element's destructor (vt+0x00), last first, then the block.
void CRenderer::DeleteArray(IKBaseClass* first) { delete[] static_cast<CRenderer*>(first); }

// C2.8 port-all P18.
// 0x0009ec10 CRenderer_RecursiveRegistration
void CRenderer::RecursiveRegistration(int32_t type) {
    if (type == 0) {
        m_pRootNode->RecursiveRegistration(0);           // vt+0x24
        m_pSecondaryRootNode->RecursiveRegistration(0);
        m_flashManager->RecursiveRegistration(0);
        // KStub_Return1_a2e10(m_cameraContext, 0): the camera context registers nothing.
    }
    for (RendableNode* node = m_lRenderableObjectList; node != nullptr; node = node->m_pNext) {
        node->m_pObject->RecursiveRegistration(type);
    }
}
void CRenderer::Delete(IKBaseClass* object) { delete object; }

// 0x0009f620 InitializeRendererStages. The stage queue types in slot order (renderer +0x38 + 4 * stage; the vtable of
// each is read from the TOC slots 0x187e..0x1877): 0 0, 1 1, 2 2, 3 3, 4 0, 5 1, 6 2, 7 4, 8 3, 9 0, 10 5, 11 6, 12 0, 13 7,
// 14 7, 15 0, 16 6, 17 6, 18 6, 19 1, 20 6, 21 0, 22 6 (types as in the enum of RenderQueue). Each queue's buffer is
// allocated (vt+0x0c).
int32_t CRenderer::InitializeStages(void* startupContext) {
    dotd::trace::Boot("CRenderer::InitializeStages (camera context, render queues; world: stand-in)");
    m_cameraContext = new CameraContext();  // OperatorNew(0x98) + ConstructRendererCameraContext
    if (m_cameraContext->Init(static_cast<AppConfig*>(startupContext)) != 1) return 0;
    RwDevice_RegisterWorldCameras(m_cameraContext->m_pMainCamera, m_cameraContext->m_pSceneCamera);
    // The renderer's world: empty (the level's geometry hangs in the scene graph), the box +-100000 (TOC -0x61fc sup,
    // -0x6200 inf), with the main, UI and scene cameras.
    RwBBox box;
    box.inf = RwV3d{-100000.0f, -100000.0f, -100000.0f};
    box.sup = RwV3d{100000.0f, 100000.0f, 100000.0f};
    m_pWorld = RpWorldCreate(&box);
    RpWorldAddCamera(m_pWorld, m_cameraContext->m_pMainCamera);
    RpWorldAddCamera(m_pWorld, m_cameraContext->m_pUICamera);
    RpWorldAddCamera(m_pWorld, m_cameraContext->m_pSceneCamera);
    static const RenderQueue::Type kStageTypes[23] = {
        RenderQueue::kTransparentATestPrio, RenderQueue::kOpaque, RenderQueue::kOpaqueCutout,       // 0-2
        RenderQueue::kTransparent, RenderQueue::kTransparentATestPrio, RenderQueue::kOpaque,        // 3-5
        RenderQueue::kOpaqueCutout, RenderQueue::kBlendedZWrite, RenderQueue::kTransparent,         // 6-8
        RenderQueue::kTransparentATestPrio, RenderQueue::kTransparentUnsorted, RenderQueue::kTransparentATest,  // 9-11
        RenderQueue::kTransparentATestPrio, RenderQueue::kTransparentPrio, RenderQueue::kTransparentPrio,       // 12-14
        RenderQueue::kTransparentATestPrio, RenderQueue::kTransparentATest,                                    // 15-16
        RenderQueue::kTransparentATest, RenderQueue::kTransparentATest, RenderQueue::kOpaque,       // 17-19
        RenderQueue::kTransparentATest, RenderQueue::kTransparentATestPrio, RenderQueue::kTransparentATest,     // 20-22
    };
    for (uint32_t i = 0; i < 23; ++i) m_aStages[i] = new RenderQueue(kStageTypes[i]);
    for (uint32_t i = 0; i < 23; ++i) s_stageQueues[i] = m_aStages[i];  // DEV (gpuprof.h)
    for (RenderQueue* stage : m_aStages) stage->AllocBuffer();
    // The stage managers, in the original's order and slots.
    m_cloneManager = static_cast<IKSerializable*>(ClassRegistry_CreateObjectByKey(0xcd));
    m_manager2d = static_cast<CManager2d*>(ClassRegistry_CreateObjectByKey(0x40d));
    Engine_SetManager2d(m_manager2d);
    m_manager2d->Init();  // 0x630e8 CManager2d_Init_maybe
    m_backgroundManager = static_cast<IKSerializable*>(ClassRegistry_CreateObjectByKey(0x68d));
    static_cast<CBackgroundManager*>(m_backgroundManager)->Init();  // 0x93680 CBackgroundManager_Init_maybe
    m_lightManager = static_cast<IKSerializable*>(ClassRegistry_CreateObjectByKey(0x90d));
    static_cast<CLightManager*>(m_lightManager)->CreateWorldLights();  // 0x9a5f0 Renderer_CreateWorldLights_maybe
    m_flashManager = static_cast<IKSerializable*>(ClassRegistry_CreateObjectByKey(0x70d));
    static_cast<CKFlashManager*>(m_flashManager)->InitializeManager();  // 0x6c9b8 Rt2dDevice_Init_maybe
    m_videoManager = static_cast<CVideoManager*>(ClassRegistry_CreateObjectByKey(0x9cd));
    m_videoManager->InitCodec();  // 0xa83d0 CVideoManager_InitCodec_maybe (the engine slot is set by its constructor)
    m_spawnManager = static_cast<IKSerializable*>(ClassRegistry_CreateObjectByKey(0xb8d));
    static_cast<CSpawnManager*>(m_spawnManager)->Init();  // 0xb90e8 CSpawnManager_Init_maybe
    m_bitProperties &= 0xfffffff1u;
    return 1;
}

// 0x0009e1a0 Apply2DRenderStates
void Apply2DRenderStates() {
    RwRenderStateSet(rwRENDERSTATEZTESTENABLE, StateWord(1));
    RwRenderStateSet(rwRENDERSTATEZWRITEENABLE, StateWord(1));
    RwRenderStateSet(rwRENDERSTATETEXTURERASTER, nullptr);
    RwRenderStateSet(rwRENDERSTATESHADEMODE, StateWord(2));
    RwRenderStateSet(rwRENDERSTATECULLMODE, StateWord(2));
    RwRenderStateSet(rwRENDERSTATESRCBLEND, StateWord(kBlendTableSrc[0]));
    RwRenderStateSet(rwRENDERSTATEDESTBLEND, StateWord(kBlendTableDest[0]));
    RwRenderStateSet(rwRENDERSTATEFOGENABLE, StateWord(0));
    RwRenderStateSet(rwRENDERSTATEALPHATESTFUNCTIONREF, StateWord(200));
    RwRenderStateSet(rwRENDERSTATEALPHATESTFUNCTION, StateWord(8));
    RwRenderStateSet(rwRENDERSTATEVERTEXALPHAENABLE, StateWord(0));
}

namespace {
// 0x00a6f550: the states PopRenderStates restores, in PushRenderStates' slot order.
const RwRenderState kPushedStates[14] = {
    rwRENDERSTATEZTESTENABLE, rwRENDERSTATEZWRITEENABLE, rwRENDERSTATESHADEMODE, rwRENDERSTATETEXTUREFILTER,
    rwRENDERSTATESRCBLEND, rwRENDERSTATEDESTBLEND, rwRENDERSTATEVERTEXALPHAENABLE, rwRENDERSTATEBORDERCOLOR,
    rwRENDERSTATEFOGENABLE, rwRENDERSTATEFOGCOLOR, rwRENDERSTATEFOGTYPE, rwRENDERSTATECULLMODE,
    rwRENDERSTATEALPHATESTFUNCTION, rwRENDERSTATEALPHATESTFUNCTIONREF,
};
}  // namespace

// 0x0009e590 PushRenderStates: the 14 states into entry +0xc0 of the stack (0x38 bytes each; the Get of
// the border colour fails and leaves its word as it was). BUG(original): no bound check against the
// capacity (+0xc4, 20).
void PushRenderStates(CRenderer* renderer) {
    int32_t* entry = reinterpret_cast<int32_t*>(renderer->m_pRenderStateStack + renderer->m_renderStateDepth * 0x38);
    if (renderer->m_renderStateDepth >= renderer->m_renderStateCapacity) {
        // The PS3 writes past the 0x460-byte block here (heap corruption); the remake writes a spill entry.
        static int32_t s_spill[14];
        DOTD_STUB_ONCE("PushRenderStates: render-state stack overflow (BUG(original): writes past the block)");
        entry = s_spill;
    }
    for (uint32_t i = 0; i < 14; ++i) RwRenderStateGet(kPushedStates[i], &entry[i]);
    ++renderer->m_renderStateDepth;
}

// 0x0009e858 PopRenderStates: each state whose current value differs from the saved one is set back.
// (The border colour's Get fails: the comparison reads the stack word left from the Get before; its Set
// fails too.)
void PopRenderStates(CRenderer* renderer) {
    --renderer->m_renderStateDepth;
    const int32_t* entry =
        reinterpret_cast<const int32_t*>(renderer->m_pRenderStateStack + renderer->m_renderStateDepth * 0x38);
    int32_t current = 0;
    for (uint32_t i = 0; i < 14; ++i) {
        RwRenderStateGet(kPushedStates[i], &current);
        if (entry[i] != current) RwRenderStateSet(kPushedStates[i], reinterpret_cast<void*>(static_cast<intptr_t>(entry[i])));
    }
}

// ==== the world stages (C2.4 step 5) ===================================================================
// RenderGameFrame's order (render-engine-pipeline.md): the scene roots are traversed into the 23 queues, then the far group
// (stages 0-4, the scene camera at ctx +0x24 with its own near / far planes, then a depth clear), the main group (stages
// 5-15, the main camera), stage 16 (distortion / post) and the 2D group (17-22, in ExecuteRenderStages7CTo90). The far and
// main groups draw into the scene colour raster (a camera texture, ctx +0x1c; the alternative one +0x10 on the depth of
// field path), which the main group then copies into the final colour (DrawFullscreenRasterQuad); stage 16's post
// effects read it again (C2.4 step 8).

namespace {
// The background data of the active sector: max(the current sector, 0), the unloading and the loading sector (as signed
// ints), indexed into the background manager's array; null when there is none (0xfffffffe in the original).
CBackgroundData* ActiveBackground(CRenderer* renderer) {
    CKLevel* level = g_pEngine->m_level;
    const int32_t current = level->m_currentSector;
    int32_t sector = level->m_i32NumUnloadingSector;
    if (level->m_i32NumUnloadingSector < level->m_i32NumLoadingSector) sector = level->m_i32NumLoadingSector;
    const int32_t clamped = current & ~(current >> 31);
    if (sector < clamped) sector = clamped;
    if (static_cast<uint32_t>(sector) == 0xfffffffeu) return nullptr;
    CBackgroundManager* manager = static_cast<CBackgroundManager*>(renderer->m_backgroundManager);
    if (manager->m_apRootNode == nullptr || sector < 0 || sector >= manager->m_ui8NbRootNode) return nullptr;
    return manager->m_apRootNode[sector];
}

// CKCoreManager_GetObjectByClassKey 0x1cdf0 for the far-texture object (key 0x4d0d, the level's CBackgroundCopyRender).
const CBackgroundCopyRender* FarTextureObject(const CRenderer* /*renderer*/) {
    return static_cast<const CBackgroundCopyRender*>(g_pEngine->m_coreManager->GetObjectByClassKey(0x4d0d));
}

const uint8_t kColorWhite[4] = {0xff, 0xff, 0xff, 0xff};  // 0x00c50dfc

// The depth of field path (inlined in RenderGameFrame and the world groups): the post-rendering object (key 0x38d) exists,
// the graphic caps have 0x200, the shader manager runs the RSX profiles (+0x44, +0x40 = 6) and the object's bit 0x400.
bool DepthOfFieldPath() {
    const CPostRenderingFx* postFx = static_cast<const CPostRenderingFx*>(g_pEngine->m_coreManager->GetObjectByClassKey(0x38d));
    return postFx != nullptr && (g_pEngine->m_graphic->m_baHardwareCaps & 0x200) != 0 && g_pShaderManager->m_bShadersEnabled != 0 &&
           g_pShaderManager->m_i32ProfileMode == 6 && (postFx->m_BitProperties & 0x400) != 0;
}

// DEBUG, not in the original (platform/capture_camera.h, C2.4 exit): with DOTD_CAMERA_FROM set, the main camera takes the
// RPCS3 capture's frame LTM, view window, view offset and near / far / fog planes before SyncSceneCamerasAndClipPlanes,
// overriding the game camera (CKSrvCamera_UpdateFrame, step 5), for drawing a frame from exactly the capture's camera.
// After the sync the scene camera's planes are checked against the capture once.
bool ApplyCaptureCamera(CameraContext* context) {
    dotd::platform::capturecam::CameraState state;
    if (!dotd::platform::capturecam::Get(&state, nullptr)) return false;
    RwCamera* main = context->m_pMainCamera;
    RwFrame* frame = RwCameraGetFrame(main);
    if (frame != nullptr) {
        frame->modelling.right = {state.right[0], state.right[1], state.right[2]};
        frame->modelling.up = {state.up[0], state.up[1], state.up[2]};
        frame->modelling.at = {state.at[0], state.at[1], state.at[2]};
        frame->modelling.pos = {state.pos[0], state.pos[1], state.pos[2]};
        frame->modelling.flags = 3;
        RwFrame_MarkDirty(frame);
    }
    const RwV2d window = {state.viewWindow[0], state.viewWindow[1]};
    const RwV2d offset = {state.viewOffset[0], state.viewOffset[1]};
    RwCameraSetViewWindow(main, &window);
    RwCameraSetViewOffset(main, &offset);
    RwCameraSetNearClipPlane(main, state.nearPlane);
    RwCameraSetFarClipPlane(main, state.farPlane);
    main->fogPlane = state.fogPlane;
    return true;
}

void CheckCaptureSceneCamera(const CameraContext* context) {
    static float s_near = -1.0f, s_far = -1.0f;
    static int s_reports = 0;
    dotd::platform::capturecam::CameraState scene;
    if (!dotd::platform::capturecam::Get(nullptr, &scene)) return;
    const RwCamera* camera = context->m_pSceneCamera;
    if (s_reports >= 8 || (camera->nearPlane == s_near && camera->farPlane == s_far)) return;
    s_near = camera->nearPlane;
    s_far = camera->farPlane;
    ++s_reports;
    DOTD_LOG("capturecam: scene camera after SyncSceneCamerasAndClipPlanes: near %.6g far %.6g (capture %.6g / %.6g)\n",
             camera->nearPlane, camera->farPlane, scene.nearPlane, scene.farPlane);
}
}  // namespace

// 0x0009ed38 ApplySceneRenderStatesAndFog: the render states every world group starts from (Z test and write, no raster,
// Gouraud, back culling, the blend table's entry 0, alpha reference 200 with the test off, no vertex alpha) and the
// fog: with the group's flag (m_bitProperties bit 0) the density of the pass (the main camera: FogManager_GetMainDensity,
// the scene camera: GetFarDensity; any other camera: no fog), and the fog state (RW 0xe) on, type 2, the pass's colour when the
// camera's fog plane is not beyond its far plane. The shaders do their own fog from the camera service's fog range and the
// fog texture (ShaderUniform_FillFogParams 0xf6788); the state is what MeshShaderPassState_IsFogEnabled reads.
void CRenderer::ApplySceneRenderStatesAndFog(const uint8_t fogColor[4]) {
    RwRenderStateSet(rwRENDERSTATEZTESTENABLE, StateWord(1));
    RwRenderStateSet(rwRENDERSTATEZWRITEENABLE, StateWord(1));
    RwRenderStateSet(rwRENDERSTATETEXTURERASTER, nullptr);
    RwRenderStateSet(rwRENDERSTATESHADEMODE, StateWord(2));
    RwRenderStateSet(rwRENDERSTATECULLMODE, StateWord(2));
    RwRenderStateSet(rwRENDERSTATESRCBLEND, StateWord(kBlendTableSrc[0]));
    RwRenderStateSet(rwRENDERSTATEDESTBLEND, StateWord(kBlendTableDest[0]));
    RwRenderStateSet(rwRENDERSTATEALPHATESTFUNCTIONREF, StateWord(200));
    RwRenderStateSet(rwRENDERSTATEALPHATESTFUNCTION, StateWord(8));
    RwRenderStateSet(rwRENDERSTATEVERTEXALPHAENABLE, StateWord(0));
    const RwCamera* current = RwDevice_GetCurrentCamera();
    if ((m_bitProperties & 1) == 0) {
        RwRenderStateSet(rwRENDERSTATEFOGENABLE, StateWord(0));
        return;
    }
    const CKSrvCamera* cameras = static_cast<const CKSrvCamera*>(g_pEngine->m_srvCamera);
    float density;
    if (m_cameraContext->m_pMainCamera == current) {
        density = cameras->GetMainFogDensity();
    } else if (m_cameraContext->m_pSceneCamera == current) {
        density = cameras->GetFarFogDensity();
    } else {
        RwRenderStateSet(rwRENDERSTATEFOGENABLE, StateWord(0));
        return;
    }
    RwRenderStateSet(rwRENDERSTATEFOGDENSITY, &density);
    if (current->fogPlane <= current->farPlane) {
        RwRenderStateSet(rwRENDERSTATEFOGENABLE, StateWord(1));
        RwRenderStateSet(rwRENDERSTATEFOGTYPE, StateWord(2));
        RwRenderStateSet(rwRENDERSTATEFOGCOLOR, StateWord(static_cast<intptr_t>(static_cast<uint32_t>(fogColor[0]) << 16 | fogColor[2] | static_cast<uint32_t>(fogColor[1]) << 8 | 0xff000000u)));
    } else {
        RwRenderStateSet(rwRENDERSTATEFOGENABLE, StateWord(0));
    }
}

// 0x000a04e8 SyncSceneCamerasAndClipPlanes: the scene (far) camera takes the main camera's frame, view offset, view
// window and projection; its far plane is the background radius of the level and the active sector and its near plane a
// thousandth of it (0.99 of it, limited to 0.99 of the main far plane, when the background asks for it: bit 3). While the
// far-texture object (class 0x4d0d, CBackgroundCopyRender; its flags +0x20 and +0x21 come from its Load) is active the
// main far plane is reduced by its +0x1c first. Last, the cameras' frame objects are synced (their view matrices).
void CRenderer::SyncSceneCamerasAndClipPlanes() {
    CameraContext* context = m_cameraContext;
    RwCamera* main = context->m_pMainCamera;
    RwFrame* frame = RwCameraGetFrame(main);
    if ((frame->modelling.flags & 3) != 3) {
        RwMatrixOrthoNormalize(&frame->modelling, &frame->modelling);
        RwFrame_MarkDirty(frame);
    }
    RwCamera* scene = context->m_pSceneCamera;
    if (RwCameraGetFrame(scene) != frame) RwCameraSetFrame(scene, frame);
    if (scene->viewOffset.x != main->viewOffset.x || scene->viewOffset.y != main->viewOffset.y) RwCameraSetViewOffset(scene, &main->viewOffset);
    if (scene->viewWindow.x != main->viewWindow.x || scene->viewWindow.y != main->viewWindow.y) RwCameraSetViewWindow(scene, &main->viewWindow);
    if (scene->projectionType != main->projectionType) RwCameraSetProjection(scene, static_cast<RwCameraProjection>(main->projectionType));
    CBackgroundManager* backgrounds = static_cast<CBackgroundManager*>(m_backgroundManager);
    const CBackgroundData* level = backgrounds->m_apRootNode != nullptr ? backgrounds->m_apRootNode[0] : nullptr;
    const CBackgroundData* sector = ActiveBackground(this);
    constexpr float kDefaultRadius = 10000.0f;  // TOC -0x61c8
    float far = 0.001f;                          // TOC -0x61c4
    uint32_t nearMode = 0;
    if (level != nullptr && level->m_fRadiusModel != kDefaultRadius) {
        far = level->m_fRadiusModel;
        nearMode = (level->m_unk18 >> 3) & 1;
    }
    const CBackgroundData* last = nullptr;
    if (sector != nullptr) {
        last = sector;
        if (sector->m_fRadiusModel != kDefaultRadius) {
            if (far <= sector->m_fRadiusModel) far = sector->m_fRadiusModel;
            nearMode = (sector->m_unk18 >> 3) & 1;
        }
    }
    if (last != nullptr && (last->m_unk18 & 1) != 0) far = far + far;
    const CBackgroundCopyRender* farTexture = FarTextureObject(this);
    const bool farTextureActive = farTexture != nullptr && farTexture->m_unk20 != 0 && farTexture->m_unk21 != 0;
    float nearPlane;
    if (nearMode == 0) {
        nearPlane = far * 0.001f;
        if (farTextureActive) {
            const float limit = main->farPlane - farTexture->m_unk1c;
            nearPlane = nearPlane <= limit ? nearPlane : limit;
        }
    } else {
        nearPlane = far * 0.99f;
        if (!farTextureActive) {
            const float limit = main->farPlane * 0.99f;
            if (limit < nearPlane) nearPlane = limit;
        } else {
            const float limit = (main->farPlane - farTexture->m_unk1c) * 0.99f;
            nearPlane = nearPlane <= limit ? nearPlane : limit;
        }
    }
    if (nearPlane < 0.0001f) nearPlane = 0.0001f;  // TOC -0x61bc
    if (scene->farPlane != far) RwCameraSetFarClipPlane(scene, far);
    if (scene->nearPlane != nearPlane) RwCameraSetNearClipPlane(scene, nearPlane);
    if (scene->nearPlane >= scene->farPlane) RwCameraSetFarClipPlane(scene, scene->nearPlane + 0.001f);
    // Per frame (the main camera's, then the UI camera's): its LTM synced (BridgeRwGetFrameLocalToWorldMatrix), the
    // objects of its object list synced through their sync callbacks (+0x10: _rwCameraSync_maybe 0x7471c8, their view
    // matrices and frustums; the main frame holds the scene camera, added last, then the main camera), then the frame's
    // private sync bits cleared (& 0xf0).
    RwFrameGetLTM(frame);
    _rwCameraSync(scene);
    _rwCameraSync(main);
    frame->object.privateFlags = static_cast<RwUInt8>(frame->object.privateFlags & 0xf0);
    RwFrame* uiFrame = RwCameraGetFrame(context->m_pUICamera);
    RwFrameGetLTM(uiFrame);
    _rwCameraSync(context->m_pUICamera);
    uiFrame->object.privateFlags = static_cast<RwUInt8>(uiFrame->object.privateFlags & 0xf0);
}

// 0x000a1408 ExecuteRenderStages38To48 (the far group): stages 0-4 on the scene camera, then a depth-only clear so the
// main group draws over the background, after the background gradient quad of a sector with render type 1
// (DrawBackgroundGradientQuad_maybe 0x93c48, CBackgroundManager.cpp).
void CRenderer::ExecuteRenderStages38To48(IKTime* frameClock) {
    uint8_t farFogColor[4];
    static_cast<CKSrvCamera*>(g_pEngine->m_srvCamera)->GetFarFogColor(farFogColor);
    CBackgroundData* background = ActiveBackground(this);
    const uint32_t farFlag = (background == nullptr || background->m_eRenderType == 1) ? 0u : (background->m_unk18 & 1);
    m_bitProperties = farFlag | (m_bitProperties & 0xfffffffeu);
    CameraContext* context = m_cameraContext;
    context->m_pSceneCamera->zBuffer = context->m_pDepthRaster;
    context->m_pSceneCamera->frameBuffer = DepthOfFieldPath() ? context->m_unk10 : context->m_pSceneColorRaster;
    RwCamera* begun = BeginRenderCameraUpdate(context->m_pSceneCamera);
    if (begun == nullptr || (m_bitProperties & 2) != 0) {
        for (uint32_t stage = 0; stage <= 4; ++stage) m_aStages[stage]->Clear();
    } else {
        ApplySceneRenderStatesAndFog(farFogColor);
        if (g_pLightManager != nullptr) g_pLightManager->ApplyLightingZone(nullptr, 0);
        for (uint32_t stage = 0; stage <= 4; ++stage) {
            if (!m_aStages[stage]->IsEmpty()) m_aStages[stage]->Execute(frameClock);
        }
        const CBackgroundData* active = ActiveBackground(this);
        if (active != nullptr && active->m_eRenderType == 1) {
            static_cast<CBackgroundManager*>(m_backgroundManager)->DrawBackgroundGradientQuad(m_cFogColor);
        }
    }
    RwCameraEndUpdate(context->m_pSceneCamera);
    if ((m_bitProperties & 2) == 0 && (m_bitProperties & 8) == 0) {
        // The depth cleared in the scene colour raster's frame buffer (PSGL_BindRasterRenderTarget_maybe 0x738758), then
        // the display bound again (PSGL_UnbindRenderTarget_maybe).
        RwDevice_BindRasterRenderTarget(DepthOfFieldPath() ? context->m_unk10 : context->m_pSceneColorRaster);
        ClearRendererCamera(context, 1);
        RwDevice_UnbindRenderTarget();
    }
}

// 0x0009ff70 ExecuteRenderStages4CTo74 (the main group): stages 5-15 on the main camera drawing into the scene colour
// raster (the alternative one on the depth of field path), then the scene colour copied into the final colour (ONE / ZERO,
// white, linear, not flipped); on the depth of field path the main camera keeps the scene colour raster.
void CRenderer::ExecuteRenderStages4CTo74(IKTime* frameClock) {
    uint8_t mainFogColor[4];
    static_cast<CKSrvCamera*>(g_pEngine->m_srvCamera)->GetMainFogColor(mainFogColor);
    CBackgroundData* background = ActiveBackground(this);
    uint32_t mainFlag = 0;
    if (background != nullptr && (background->m_unk18 & 2) != 0) mainFlag = ((background->m_unk18 >> 2) & 1) ^ 1;
    m_bitProperties = (m_bitProperties & 0xfffffffeu) | mainFlag;
    const bool depthOfField = DepthOfFieldPath();
    m_cameraContext->m_pMainCamera->frameBuffer = depthOfField ? m_cameraContext->m_unk10 : m_cameraContext->m_pSceneColorRaster;
    RwCamera* begun = BeginRenderCameraUpdate(m_cameraContext->m_pMainCamera);
    if (begun == nullptr || (m_bitProperties & 2) != 0) {
        for (uint32_t stage = 5; stage <= 15; ++stage) m_aStages[stage]->Clear();
    } else {
        ApplySceneRenderStatesAndFog(mainFogColor);
        if (g_pLightManager != nullptr) g_pLightManager->ApplyLightingZone(nullptr, 0);
        for (uint32_t stage = 5; stage <= 15; ++stage) {
            if (!m_aStages[stage]->IsEmpty()) m_aStages[stage]->Execute(frameClock);
        }
    }
    RwCameraEndUpdate(m_cameraContext->m_pMainCamera);
    m_cameraContext->m_pMainCamera->frameBuffer = m_cameraContext->m_pFinalColorRaster;
    if (BeginRenderCameraUpdate(m_cameraContext->m_pMainCamera) != nullptr)
        DrawFullscreenRasterQuad(m_cameraContext->m_pSceneColorRaster, 2, 1, kColorWhite, 1, 0);
    RwCameraEndUpdate(m_cameraContext->m_pMainCamera);
    if (DepthOfFieldPath()) m_cameraContext->m_pMainCamera->frameBuffer = m_cameraContext->m_pSceneColorRaster;
}

// 0x000a1a78 ExecuteRenderStage78: stage 16 (the distortion materials, queued by CGeometry's modes 7 and 8; the post
// effects of CPostRenderingFx are step 8) on the main camera.
void CRenderer::ExecuteRenderStage78(IKTime* frameClock) {
    if ((m_bitProperties & 2) == 0 && !m_aStages[16]->IsEmpty()) {
        if (BeginRenderCameraUpdate(m_cameraContext->m_pMainCamera) != nullptr) {
            if (g_pLightManager != nullptr) g_pLightManager->ApplyLightingZone(nullptr, 0);
            m_aStages[16]->Execute(frameClock);
        } else {
            m_aStages[16]->Clear();
        }
        RwCameraEndUpdate(m_cameraContext->m_pMainCamera);
        return;
    }
    m_aStages[16]->Clear();
}

// 0x000a0ac8 ExecuteRenderStages7CTo90: the 2D group on the UI camera (render context +0x20).
void CRenderer::ExecuteRenderStages7CTo90(IKTime* frameClock) {
    m_manager2d->UpdateScreen();
    const bool fullscreenVideo = m_videoManager->HasFullscreenVideo();  // 0xa8698
    // depthOnly: with the loading video, a full-screen video, the inhibit byte, or bit 2/3 set ... (see below)
    int32_t depthOnly;
    if (m_videoManager->m_pLoadingVideo != nullptr) {
        depthOnly = 1;
    } else {
        if ((m_bitProperties & 4) == 0 && (m_bitProperties & 8) == 0) {
            depthOnly = fullscreenVideo ? 0 : 1;
        } else {
            depthOnly = 0;
        }
        if (GetGlobalUpdateInhibitByte() != 0) depthOnly = 1;
    }
    CameraContext* context = m_cameraContext;
    const uint32_t savedColor = context->m_clearColor;
    // While a full-screen video plays the clear colour is the shared black (0x00c50df8 = 0x000000ff) with
    // alpha 0.
    if (fullscreenVideo) {
        const uint32_t black = 0x000000ffu & 0xffffff00u;
        if (context->m_clearColor != black) context->m_clearColor = black;
    }
    ClearRendererCamera(context, depthOnly);
    if (context->m_clearColor != (savedColor & 0xffffff00u)) context->m_clearColor = savedColor & 0xffffff00u;
    if (RwCameraBeginUpdate(context->m_pUICamera) == nullptr) {
        for (uint32_t stage = 17; stage <= 22; ++stage) m_aStages[stage]->Clear();
        RwCameraEndUpdate(context->m_pUICamera);
        return;
    }
    if ((m_bitProperties & 4) == 0) {
        Apply2DRenderStates();
        if (g_pLightManager != nullptr) g_pLightManager->ApplyLightingZone(nullptr, 0);
        if (!m_aStages[17]->IsEmpty()) m_aStages[17]->Execute(frameClock);
        m_videoManager->Render(frameClock);  // vt+0x5c CVideoManager_Draw 0xa98b0
    } else {
        m_aStages[17]->Clear();
        m_videoManager->Render(frameClock);
    }
    if ((m_bitProperties & 4) != 0) {
        for (uint32_t stage = 18; stage <= 22; ++stage) m_aStages[stage]->Clear();
    } else {
        Apply2DRenderStates();
        for (uint32_t stage = 18; stage <= 22; ++stage) {
            if (!m_aStages[stage]->IsEmpty()) m_aStages[stage]->Execute(frameClock);
        }
    }
    m_manager2d->RenderMsgBox();  // 0x63550 CManager2d_PostRenderPass_maybe
    // KStub_Nop_1058b8(engine +0x18 input, frame context): nothing.
    RwCameraEndUpdate(context->m_pUICamera);
}

// 0x000a1c08 RenderGameFrame: the particle scheduler's updates, the renderables' PreUpdate (vt+0x54), the scene cameras
// and clip planes, the frame counter, the main scene root's traversal into the stage queues (the camera it culls with is
// the main camera), the renderables' UpdateAndExtract (vt+0x58), the secondary root's traversal with the UI camera (the
// menus' particle nodes, queued in the 2D stages), the particle nodes prepared, the scene clear, the far, main and
// post groups (ExecuteRenderStages38To48 / 4CTo74 / 78), the 2D group and the present. STUB(M2): the render targets (one
// target here instead of the scene colour raster), the inverse view matrix (+0xd0, unused so far), UpdateActiveSectorWorld
// 0x1fb9e0 (the shadow service's texture on unit 5: C2.4 step 7).
void CRenderer::RenderGameFrame(IKTime* frameClock) {
    CameraContext* context = m_cameraContext;
    if (context->m_pFinalColorRaster == nullptr || context->m_pDepthRaster == nullptr) return;
    dotd::gfx::gpuprof::FrameStart();  // DEV (platform/gfx/gpuprof.h): a measured frame begins here
    RwIm3DBeginFrame();
    RpAtomicBeginFrame();
    ParticleUpdateScheduler* scheduler = g_pEngine->m_particleScheduler;
    ScheduleParticleNodeUpdates(scheduler, frameClock);
    for (RendableNode* node = m_lRenderableObjectList; node != nullptr; node = node->m_pNext) {
        IRendableObject* object = static_cast<IRendableObject*>(node->m_pObject);
        if (object->CanBeUpdated() != 0) object->PreUpdate(frameClock);
    }
    if (ApplyCaptureCamera(context)) {  // DEBUG (DOTD_CAMERA_FROM), not in the original
        SyncSceneCamerasAndClipPlanes();
        CheckCaptureSceneCamera(context);
    } else {
        SyncSceneCamerasAndClipPlanes();
    }
    // TOC -0x61ac: the frame counter skips 0xffff and 0 (-2 -> 1).
    if (g_ui16RenderFrameCounter == 0xfffe) {
        g_ui16RenderFrameCounter = 1;
    } else {
        ++g_ui16RenderFrameCounter;
    }
    const float farPlane = context->m_pMainCamera->farPlane;
    m_fInvFarSquared = 1.0f / (farPlane * farPlane);  // TOC -0x6214: 1.0f
    if ((m_bitProperties & 2) == 0) {
        // The level's sector changed: the shadow service's sector, and its shadow texture on unit 5 (UpdateActiveSectorWorld).
        const int32_t sector = g_pEngine->m_level->m_currentSector;
        if (static_cast<int32_t>(m_unkD4) != sector) {
            m_unkD4 = static_cast<uint32_t>(sector);
            CKSrvShadow* shadow = static_cast<CKSrvShadow*>(g_pEngine->m_srvShadow);
            shadow->m_unk0c = static_cast<uint32_t>(sector);
            shadow->UpdateActiveSectorWorld();
        }
        if (m_pRootNode != nullptr) static_cast<CSGBranch*>(m_pRootNode)->UpdateAndExtract(0.0f, m_aStages, frameClock, context->m_pMainCamera, 0);
    }
    for (RendableNode* node = m_lRenderableObjectList; node != nullptr; node = node->m_pNext) {
        IRendableObject* object = static_cast<IRendableObject*>(node->m_pObject);
        if (object->CanBeUpdated() != 0) object->UpdateAndExtract(0.0f, m_aStages, frameClock, context->m_pMainCamera, 0);
    }
    if ((m_bitProperties & 4) == 0 && m_pSecondaryRootNode != nullptr) {
        static_cast<CSGBranch*>(m_pSecondaryRootNode)->UpdateAndExtract(0.0f, m_aStages, frameClock, context->m_pUICamera, 0);
    }
    PrepareQueuedParticleNodes(scheduler);
    if ((m_bitProperties & 8) == 0) {
        // The scene colour raster's clear (PSGL_BindRasterRenderTarget_maybe of ctx +0x1c, or +0x10 on the depth of field
        // path; the clear goes to the bound frame buffer), then the display bound again.
        RwDevice_BindRasterRenderTarget(DepthOfFieldPath() ? context->m_unk10 : context->m_pSceneColorRaster);
        ClearRendererCamera(context, 0);
        RwDevice_UnbindRenderTarget();
    }
    ExecuteRenderStages38To48(frameClock);
    ExecuteRenderStages4CTo74(frameClock);
    ExecuteRenderStage78(frameClock);
    if (GetGlobalUpdateInhibitByte() != 0) m_bitProperties = (m_bitProperties & 0xfffffffbu) | 4;
    ExecuteRenderStages7CTo90(frameClock);
    RwCamera* mainCamera = context->m_pMainCamera;
    if (mainCamera->frameBuffer != nullptr && mainCamera->zBuffer != nullptr) RwCameraShowRaster(mainCamera, nullptr, 0);
    m_bitProperties &= 0xfffffff1u;
}

// 0x000a11b0 RenderFallbackFrame_maybe (the loading frame). BUG(original): without a final colour raster
// it returns with the render mutex (0x00cf9c90) still locked.
void CRenderer::RenderFallbackFrame(IKTime* frameClock) {
    CameraContext* context = m_cameraContext;
    if (context->m_pFinalColorRaster == nullptr) return;
    if (context->m_pDepthRaster == nullptr) return;
    RwIm3DBeginFrame();
    RpAtomicBeginFrame();
    if (m_videoManager->CanBeUpdated() != 0) {
        m_videoManager->PreUpdate(frameClock);  // vt+0x54
        m_videoManager->UpdateAndExtract(0.0f, m_aStages, frameClock, context->m_pMainCamera, 0);  // vt+0x58
    }
    // TOC -0x61ac: the frame counter, as RenderGameFrame advances it (-2 -> 1): mode 6 and the other fallback frames
    // count too (the nodes posed before them are not "drawn this frame" afterwards).
    if (g_ui16RenderFrameCounter == 0xfffe) {
        g_ui16RenderFrameCounter = 1;
    } else {
        ++g_ui16RenderFrameCounter;
    }
    const float farPlane = context->m_pMainCamera->farPlane;  // camera +0x84
    m_fInvFarSquared = 1.0f / (farPlane * farPlane);           // TOC -0x6214: 1.0f
    // The main camera's frame LTM (BridgeRwGetFrameLocalToWorldMatrix of the TOC -0x626c camera's frame: RwFrameGetLTM,
    // which syncs a dirty frame). C2.8 chase-g8: in the first frame after a streaming load (G +82419: mode 8 -> 5, still a
    // fallback frame) the camera service has moved the camera and this is what brings its LTM up to date; without it the
    // camera stood on the load's pose for a frame. Its inverse goes into the matrix +0xd0 (0x0023f878 Mat4_Invert_maybe).
    Mat4_Invert(m_pInvCameraMatrix, reinterpret_cast<const CMatrix34*>(RwFrameGetLTM(RwCameraGetFrame(context->m_pMainCamera))));
    ClearRendererCamera(context, 0);
    m_bitProperties = (m_bitProperties & 0xfffffffbu) | 4;
    ExecuteRenderStages7CTo90(frameClock);
    RwCamera* mainCamera = context->m_pMainCamera;
    if (mainCamera->frameBuffer != nullptr && mainCamera->zBuffer != nullptr) RwCameraShowRaster(mainCamera, nullptr, 0);
    m_bitProperties &= 0xfffffff1u;
}

// The insertion inlined in CRenderer_Load (XXL2 CRenderer::AddRendeableObject): an object already in the
// list is not added twice; a new one goes to the head (a node from the FreeListPool at TOC -0x6260 in the
// original).
void CRenderer::AddRendeableObject(IKSerializable* object) {
    for (RendableNode* node = m_lRenderableObjectList; node != nullptr; node = node->m_pNext) {
        if (node->m_pObject == object) return;
    }
    RendableNode* node = new RendableNode();
    node->m_pNext = nullptr;
    node->m_pObject = object;
    node->m_pNext = m_lRenderableObjectList;
    m_lRenderableObjectList = node;
}

// 0x0009eaa0 CRenderer_RegisterPostRenderingFx_maybe: the object at the head of the renderable list unless it is in it.
void CRenderer::RegisterPostRenderingFx(IKSerializable* object) { AddRendeableObject(object); }

// 0x0009eb70 CRenderer_Destroy: the scene roots forgotten and the renderable objects' nodes returned to the
// pool (the level's objects are about to be freed).
void CRenderer::Destroy() {
    m_pRootNode = nullptr;
    Engine_SetMainSceneRoot(nullptr);
    m_pSecondaryRootNode = nullptr;
    Engine_SetSecondarySceneRoot(nullptr);
    for (RendableNode* node = m_lRenderableObjectList; node != nullptr;) {
        RendableNode* next = node->m_pNext;
        delete node;
        node = next;
    }
    m_lRenderableObjectList = nullptr;
}

// 0x000a2180 CRenderer_PostLoad: the first node of the video manager leaves the renderable list (back to the node pool) and, unless
// the manager is in the list a second time, a new node puts it at the head.
int32_t CRenderer::PostLoad(int32_t type) {
    if (type != 0) return 1;
    static_cast<CBackgroundManager*>(m_backgroundManager)->HideAllBackgrounds();  // 0x93690
    RendableNode* previous = nullptr;
    for (RendableNode* node = m_lRenderableObjectList; node != nullptr; previous = node, node = node->m_pNext) {
        if (node->m_pObject != m_videoManager) continue;
        if (previous == nullptr) {
            m_lRenderableObjectList = node->m_pNext;
        } else {
            previous->m_pNext = node->m_pNext;
        }
        delete node;
        break;
    }
    for (RendableNode* node = m_lRenderableObjectList; node != nullptr; node = node->m_pNext) {
        if (node->m_pObject == m_videoManager) return 1;
    }
    RendableNode* node = new RendableNode();
    node->m_pObject = m_videoManager;
    node->m_pNext = m_lRenderableObjectList;
    m_lRenderableObjectList = node;
    return 1;
}

// 0x000a2330 CRenderer_Load (CKGraphic_Load calls it for every type but 1). The level (type 0) gives
// the scene roots, the fog and the renderable objects; every type then hands the roots to the engine.
int32_t CRenderer::Load(IKFile* file, int32_t type) {
    if (type == 0) {
        IKFile_ReadRef(file, &m_pRootNode);
        IKFile_ReadRef(file, &m_pSecondaryRootNode);
        ReadRaw(file, m_cFogColor, 4);
        ReadF32LE(file, &m_fFogDistance);
        ReadU32LE(file, &m_bitProperties);
        uint32_t count = 0;
        ReadU32LE(file, &count);
        for (uint32_t i = 0; i < count; ++i) {
            IKSerializable* object = nullptr;
            IKFile_ReadRef(file, &object);
            AddRendeableObject(object);
        }
        m_bitProperties &= 0xfffffff1u;
    }
    Engine_SetMainSceneRoot(m_pRootNode);
    Engine_SetSecondarySceneRoot(m_pSecondaryRootNode);
    return 1;
}

// 0x000a0a00 SceneRoots_UpdateWorldMatrices_maybe
void CRenderer::UpdateSceneWorldMatrices() {
    SyncSceneCamerasAndClipPlanes();  // 0x000a04e8
    RenderLock_Lock();                // 0x00cf9c90
    static_cast<CSGLeaf*>(m_pRootNode)->UpdateWorldMatrices(0);           // vt+0x68
    static_cast<CSGLeaf*>(m_pSecondaryRootNode)->UpdateWorldMatrices(0);
    RenderLock_Unlock();
    RwFrame* frame = static_cast<CSGLeaf*>(m_pRootNode)->m_pRwFrame;
    frame->object.privateFlags = static_cast<RwUInt8>(frame->object.privateFlags & 0xfdu);
}
