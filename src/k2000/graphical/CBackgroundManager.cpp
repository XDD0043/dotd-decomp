// CBackgroundManager.cpp - reconstructed original translation unit 0x935d0-0x94bf0 (GAME_TOC1, main_toc1), 31 functions, 19 live.
// Primary class: CBackgroundManager  key 0x68d  category Graphical  size 0x24  vtable 0xb16d90
// Other owners: BackgroundSectorEntry (2), DrawBackgroundGradientQuad (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x935d0  CBackgroundManager_Delete
//   [ ] 0x93620  CBackgroundManager_Construct  [dead]
//   [ ] 0x93648  CBackgroundManager_Construct_2  [dead]
//   [ ] 0x93670  CBackgroundManager_GetEntryArray_maybe  [dead]
//   [x] 0x93680  CBackgroundManager_Init_maybe
//   [x] 0x93690  CBackgroundManager_HideAllBackgrounds_maybe
//   [x] 0x936f8  CBackgroundManager_RecursiveRegistration
//   [ ] 0x93758  BackgroundSectorEntry_Construct_maybe  [dead]
//   [ ] 0x937a8  BackgroundSectorEntry_Construct_2_maybe  [dead]
//   [ ] 0x937f8  KStub_Nop_937f8  [dead]
//   [ ] 0x93800  KStub_Return1_93800  [dead]
//   [ ] 0x93808  CBackgroundManager_SetEntryVisible_maybe  [dead]
//   [ ] 0x93840  RegisterCBackgroundManagerClass
//   [ ] 0x938b8  _GLOBAL__I_938b8
//   [ ] 0x938c8  CBackgroundManager_Save
//   [ ] 0x938f0  CBackgroundManager_Update_2  [dead]
//   [x] 0x939a0  CBackgroundManager_DeleteArray
//   [ ] 0x93a48  KStub_Nop_93a48  [dead]
//   [x] 0x93a50  CBackgroundManager_vf70
//   [x] 0x93a70  CBackgroundManager_PostLoad  (CBackgroundManager.h)
//   [x] 0x93a78  CBackgroundManager_CreateArray
//   [x] 0x93b30  CBackgroundManager_Create
//   [x] 0x93b88  CBackgroundManager_Destroy
//   [x] 0x93c48  DrawBackgroundGradientQuad_maybe
//   [x] 0x944c8  CBackgroundManager_LoadSectorBackground
//   [x] 0x946e0  CBackgroundManager_Update
//   [x] 0x94790  CBackgroundManager_Load
//   [ ] 0x94988  CBackgroundManager_SaveSectorBackground_maybe  [dead]
//   [x] 0x94b68  CBackgroundManager_Destructor
//   [ ] 0x94b88  CBackgroundManager_Destructor_2  [dead]
//   [x] 0x94ba8  CBackgroundManager_DeletingDestructor
//
//   [x] 0x99c860  CBackgroundManager_GetClassType  [inline]
//   [x] 0x99c868  CBackgroundManager_GetClassID  [inline]
//   [x] 0x99c870  CBackgroundManager_GetSerializationFlags  [inline]
//   [ ] 0x99c878  CBackgroundManager_Draw  [inline]
//   [x] 0x99c880  CBackgroundManager_IsKindOfClass  [inline]
#include "k2000/graphical/CBackgroundManager.h"

#include "k2000/io/IKFile.h"
#include "k2000/logic/CKLevel.h"
#include "k2000/logic/CKSector.h"
#include "k2000/managers/CKGraphic.h"
#include "k2000/misc/Engine.h"
#include "k2000/logic/CKSavingManager.h"
#include "k2000/render/CRenderer.h"
#include "k2000/cameras/CameraContext.h"
#include "k2000/scenegraph/CSGMovable.h"
#include "Renderware/rwcore/RwCamera.h"
#include "Renderware/rwcore/RwIm2D.h"
#include "Renderware/rwcore/RwIm3D.h"
#include "crt/ppc_ops.h"
#include <cmath>
#include <cstring>
#include "k2000/scenegraph/CSGLeaf.h"

// 0x00093b30 CBackgroundManager_Create (= CBackgroundManager_Construct 0x93620): the IRendableObject
// part only, in the original's store order.
CBackgroundManager::CBackgroundManager() {
    m_pLightSet = nullptr;
    m_pNextAccumulatedObject = nullptr;
    m_BitProperties = 0;
    m_pPriorityParent = 0;
}

// Inlined in CBackgroundManager_Load (0x948c8..0x94928), in the original's store order. The two floats
// are TOC constants (-0x6464 0.33, -0x6460 10000.0).
CBackgroundData::CBackgroundData() {
    m_unk18 = 0;
    m_fPercentFogFadeBegin = 0x1.51eb86p-2f;  // 0.33 (0x3ea8f5c3)
    m_fRadiusModel = 0x1.388p+13f;            // 10000.0 (0x461c4000)
    m_eRenderType = 0;
    m_fHorizon = 0.0f;
    // Bit fields of the last word: bit 0 = 1, bit 1 = 1, bits 2-3 = 0.
    m_unk18 = (m_unk18 & ~0xfu) | 3u;
}

// 0x000944c8 CBackgroundData::Load (Ghidra CBackgroundManager_LoadSectorBackground)
int32_t CBackgroundData::Load(IKFile* file, int32_t type) {
    if (type != K_LEVEL_PLATEFORMS) return 1;
    IKFile_ReadRef(file, &m_pRootNode);
    ReadU32LE(file, &m_eRenderType);
    ReadF32LE(file, &m_fPercentFogFadeBegin);
    ReadF32LE(file, &m_fHorizon);
    ReadF32LE(file, &m_fRadiusModel);
    ReadU32LE(file, &m_unk18);
    return 1;
}

// 0x00093680 CBackgroundManager_Init_maybe (InitializeRendererStages): no backgrounds.
void CBackgroundManager::Init() {
    m_ui8NbRootNode = 0;
    m_apRootNode = nullptr;
}

// 0x00093b88 CBackgroundManager_Destroy (the level unload): IRendableObject's, then every background
// deleted (operator delete, no destructor call) and the array (operator delete[]). The count is kept.
void CBackgroundManager::Destroy() {
    IRendableObject::Destroy();  // 0xa7248
    CBackgroundData** array = m_apRootNode;
    for (uint32_t i = 0; i < m_ui8NbRootNode; ++i) {
        if (m_apRootNode[i] != nullptr) ::operator delete(m_apRootNode[i]);  // 0xa3ce18 OperatorDelete
    }
    if (array != nullptr) delete[] array;
    m_apRootNode = nullptr;
}

// 0x00094790 CBackgroundManager_Load
int32_t CBackgroundManager::Load(IKFile* file, int32_t type) {
    IRendableObject::Load(file, type);
    if (type != K_LEVEL_PLATEFORMS) return 1;
    ReadU8(file, &m_ui8NbRootNode);
    if (m_ui8NbRootNode == 0) {
        m_apRootNode = nullptr;
        return 1;
    }
    m_apRootNode = new CBackgroundData*[m_ui8NbRootNode];  // OperatorNewArray(count * 4)
    for (uint32_t i = 0; i < m_ui8NbRootNode; ++i) {
        m_apRootNode[i] = new CBackgroundData();  // OperatorNew(0x1c)
        m_apRootNode[i]->Load(file, K_LEVEL_PLATEFORMS);
    }
    return 1;
}

// 0x00093a50 CBackgroundManager_CanBeUpdated
int32_t CBackgroundManager::CanBeUpdated() {
    return static_cast<int32_t>(((g_pEngine->m_graphic->m_renderer->m_bitProperties ^ 2) >> 1) & 1);
}

// 0x000946e0 CBackgroundManager_PreUpdate: the backgrounds start hidden (flag 4 of the root node: CBackgroundManager_HideAllBackgrounds
// 0x93690, the level's load) and the active sectors' are shown here every frame.
void CBackgroundManager::PreUpdate(IKTime* /*frameClock*/) {
    CKLevel* level = g_pEngine->m_level;
    for (CKSector* sector = level->IterateActiveSectors(nullptr); sector != nullptr; sector = level->IterateActiveSectors(sector)) {
        const uint32_t index = sector->m_ui16NumSector & 0xff;
        if (m_apRootNode == nullptr || index >= m_ui8NbRootNode) continue;
        CSGLeaf* root = static_cast<CSGLeaf*>(m_apRootNode[index]->m_pRootNode);
        if (root != nullptr) root->m_sgProperties &= ~4u;
    }
}

// 0x00093690 CBackgroundManager_HideAllBackgrounds_maybe
void CBackgroundManager::HideAllBackgrounds() {
    for (uint32_t i = 0; i < m_ui8NbRootNode; ++i) {
        CSGLeaf* root = static_cast<CSGLeaf*>(m_apRootNode[i]->m_pRootNode);
        if (root != nullptr) root->m_sgProperties |= 4;
    }
}

namespace {
// 0x00010690 Math_Sqrtf: the double square root rounded to float, as a double.
inline double MathSqrtf(double x) { return static_cast<double>(static_cast<float>(std::sqrt(x))); }
}  // namespace

// 0x00093c48 DrawBackgroundGradientQuad_maybe (ExecuteRenderStages38To48, for a background of render type 1; no level
// file has one). A band of the fog colour across the screen below the horizon: the point of the camera's view ray on
// the horizontal plane at height `horizon * 100` (Y axis 0x00c50d40), the two points of that plane's horizontal line
// beside it on the planes through the camera and the view window's left and right edges, projected; from their screen
// heights down, an RwIm2D quad pair of 6 vertices: the fog colour with alpha 0 on the horizon line, the fog alpha one
// fade height (+0x10 times the raster height) lower, and again two fade heights lower (at least the raster's bottom).
// Z test and write off, no culling, blend SRCALPHA / INVSRCALPHA, no fog, vertex alpha; the render states pushed and
// popped around it. BUG(original): the texture raster state is left as it is and the vertices' s, t, r, q are stack
// garbage; here they are 0.
void CBackgroundManager::DrawBackgroundGradientQuad(const uint8_t* fogColor) {
    CKLevel* level = g_pEngine->m_level;
    const int32_t current = level->m_currentSector;
    int32_t sector = level->m_i32NumUnloadingSector;
    if (level->m_i32NumUnloadingSector < level->m_i32NumLoadingSector) sector = level->m_i32NumLoadingSector;
    const int32_t clamped = current & ~(current >> 31);
    if (sector < clamped) sector = clamped;
    const CBackgroundData* background = static_cast<uint32_t>(sector) == 0xfffffffeu ? nullptr : m_apRootNode[sector];
    PushRenderStates(g_pRenderStateRenderer);
    CameraContext* context = g_pEngine->m_graphic->m_renderer->m_cameraContext;
    const float nearZ = RwIm2DGetNearScreenZ();                            // RWEngine +0x18
    const float recipZ = 1.0f / context->m_pMainCamera->nearPlane;          // TOC -0x642c 1.0
    float height = 0.0f;                                                    // TOC -0x6410
    float width = 0.0f;
    if (context->m_pFinalColorRaster != nullptr) {
        height = static_cast<float>(context->m_pFinalColorRaster->height);
        width = static_cast<float>(context->m_pFinalColorRaster->width);
    }
    const RwFrame* frame = static_cast<const CSGMovable*>(context->m_pCamera)->m_pRwFrame;
    const RwV3d& right = frame->modelling.right;
    const RwV3d& up = frame->modelling.up;
    const RwV3d& at = frame->modelling.at;
    const RwV3d& pos = frame->modelling.pos;
    // The view ray (10000 along `at`; its height relative to the plane) and its hit on the horizon plane.
    const float rayX = ppc::fmadds(at.x, 10000.0f, pos.x) - pos.x;          // TOC -0x6460
    const float rayY = ppc::fmsubs(background->m_fHorizon, 100.0f, pos.y);  // TOC -0x6424
    const float rayZ = ppc::fmadds(at.z, 10000.0f, pos.z) - pos.z;
    const float denom = ppc::fmadds(at.z, rayZ, ppc::fmadds(at.x, rayX, at.y * rayY));
    float t = 0.0f;
    if (!(std::fabs(denom) <= 1.0e-6f)) {                                   // TOC -0x6420
        const float a = at.y * (pos.y + at.y);
        const float p = ppc::fmadds(pos.z, at.z, ppc::fmadds(pos.x, at.x, pos.y * at.y));
        const float c = ppc::fmadds(at.x, pos.x + at.x, a);
        t = -(ppc::fnmadds(at.z, pos.z + at.z, c) + p) / denom;
    }
    RwV3d hit;
    hit.x = ppc::fmadds(t, rayX, pos.x);
    hit.y = ppc::fmadds(t, rayY, pos.y);
    hit.z = ppc::fmadds(t, rayZ, pos.z);
    float hitScreen[2];
    ProjectWorldPointToScreen(context, &hit, hitScreen, 1);  // (the result is not used)
    RwV2d viewWindow;
    CameraContext_GetViewWindow(context, &viewWindow);
    // The right and left edge points one unit ahead, and the normals of the planes through the camera and them.
    const float aheadZ = pos.z + at.z;
    const float aheadX = pos.x + at.x;
    const float aheadY = pos.y + at.y;
    const float negWindow = -viewWindow.x;
    const float rightZ = ppc::fmadds(viewWindow.x, right.z, aheadZ);
    const float leftZ = ppc::fmadds(right.z, negWindow, aheadZ);
    const float rightX = ppc::fmadds(viewWindow.x, right.x, aheadX);
    const float leftX = ppc::fmadds(right.x, negWindow, aheadX);
    const float rightY = ppc::fmadds(viewWindow.x, right.y, aheadY);
    const float leftY = ppc::fmadds(right.y, negWindow, aheadY);
    const float ax = rightX - pos.x;
    const float ay = rightY - pos.y;
    const float az = rightZ - pos.z;
    float n1y = ppc::fmsubs(ax, up.z, az * up.x);
    float n1z = ppc::fmsubs(ay, up.x, ax * up.y);
    float n1x = ppc::fmsubs(az, up.y, ay * up.z);
    float length = static_cast<float>(MathSqrtf(ppc::fmadds(n1z, n1z, ppc::fmadds(n1x, n1x, n1y * n1y))));
    if (length != 0.0f) {
        const float inv = 1.0f / length;
        n1z = n1z * inv;
        n1x = n1x * inv;
        n1y = n1y * inv;
    }
    const float bz = leftZ - pos.z;
    const float bx = leftX - pos.x;
    const float by = leftY - pos.y;
    float n2y = ppc::fnmsubs(bx, up.z, bz * up.x);
    float n2z = ppc::fnmsubs(by, up.x, bx * up.y);
    float n2x = ppc::fnmsubs(bz, up.y, by * up.z);
    length = static_cast<float>(MathSqrtf(ppc::fmadds(n2z, n2z, ppc::fmadds(n2x, n2x, n2y * n2y))));
    if (length != 0.0f) {
        const float inv = 1.0f / length;
        n2z = n2z * inv;
        n2x = n2x * inv;
        n2y = n2y * inv;
    }
    // The horizon line's direction (the Y axis crossed with the ray) and its hits on both planes.
    const CVector3 axisY = {0.0f, 1.0f, 0.0f};  // 0x00c50d40 (filled by a static initialiser)
    const float lineY = ppc::fmsubs(rayX, axisY.z, rayZ * axisY.x);
    const float lineX = ppc::fmsubs(rayZ, axisY.y, rayY * axisY.z);
    const float lineZ = ppc::fmsubs(rayY, axisY.x, rayX * axisY.y);
    float t1 = 0.0f;
    float d = ppc::fmadds(n1z, lineZ, ppc::fmadds(n1x, lineX, n1y * lineY));
    if (!(std::fabs(d) <= 1.0e-6f)) {
        const float p = ppc::fmadds(n1z, hit.z, ppc::fmadds(n1x, hit.x, n1y * hit.y));
        t1 = -(ppc::fnmadds(n1z, rightZ, ppc::fmadds(n1x, rightX, n1y * rightY)) + p) / d;
    }
    RwV3d right1;
    right1.z = ppc::fmadds(t1, lineZ, hit.z);
    right1.x = ppc::fmadds(t1, lineX, hit.x);
    right1.y = ppc::fmadds(t1, lineY, hit.y);
    float t2 = 0.0f;
    d = ppc::fmadds(n2z, lineZ, ppc::fmadds(n2x, lineX, n2y * lineY));
    if (!(std::fabs(d) <= 1.0e-6f)) {
        const float p = ppc::fmadds(n2z, hit.z, ppc::fmadds(n2x, hit.x, n2y * hit.y));
        t2 = -(ppc::fnmadds(n2z, leftZ, ppc::fmadds(n2x, leftX, n2y * leftY)) + p) / d;
    }
    RwV3d left1;
    left1.x = ppc::fmadds(t2, lineX, hit.x);
    left1.z = ppc::fmadds(t2, lineZ, hit.z);
    left1.y = ppc::fmadds(t2, lineY, hit.y);
    float screenA[2];
    float screenB[2];
    ProjectWorldPointToScreen(context, &right1, screenA, 1);
    ProjectWorldPointToScreen(context, &left1, screenB, 1);
    RwIm2DVertex vertices[6];
    std::memset(vertices, 0, sizeof(vertices));
    const float fade = background->m_fPercentFogFadeBegin;
    vertices[5].x = 0.0f;
    vertices[5].y = screenA[1];
    vertices[4].x = width;
    vertices[4].y = screenB[1];
    vertices[3].x = 0.0f;
    vertices[3].y = ppc::fmadds(height, fade, screenA[1]);
    vertices[2].x = width;
    vertices[2].y = ppc::fmadds(height, fade, screenB[1]);
    vertices[1].x = 0.0f;
    float bottom = ppc::fmadds(height, fade + fade, screenA[1]);
    vertices[1].y = !(height > bottom) ? bottom : height;
    vertices[0].x = width;
    bottom = ppc::fmadds(height, fade + fade, screenB[1]);
    vertices[0].y = !(height > bottom) ? bottom : height;
    for (uint32_t i = 0; i < 6; ++i) {
        vertices[i].z = nearZ;
        vertices[i].recipZ = recipZ;
        vertices[i].emissiveColor.red = fogColor[0];
        vertices[i].emissiveColor.green = fogColor[1];
        vertices[i].emissiveColor.blue = fogColor[2];
        vertices[i].emissiveColor.alpha = i < 4 ? fogColor[3] : 0;
    }
    RwImVertexIndex indices[12] = {0, 3, 1, 0, 2, 3, 2, 5, 3, 2, 4, 5};  // 0x00a6f3f0
    RwRenderStateSet(rwRENDERSTATEZTESTENABLE, reinterpret_cast<void*>(0));
    RwRenderStateSet(rwRENDERSTATEZWRITEENABLE, reinterpret_cast<void*>(0));
    RwRenderStateSet(rwRENDERSTATECULLMODE, reinterpret_cast<void*>(1));
    RwRenderStateSet(rwRENDERSTATESRCBLEND, reinterpret_cast<void*>(5));   // the blend tables' entry 1 (0xc297ec / 0xc297fc)
    RwRenderStateSet(rwRENDERSTATEDESTBLEND, reinterpret_cast<void*>(6));
    RwRenderStateSet(rwRENDERSTATEFOGENABLE, reinterpret_cast<void*>(0));
    RwRenderStateSet(rwRENDERSTATEVERTEXALPHAENABLE, reinterpret_cast<void*>(1));
    RwIm2DRenderIndexedPrimitive(rwPRIMTYPETRILIST, vertices, 6, indices, 12);
    PopRenderStates(g_pRenderStateRenderer);
}

// C2.8 port-all P08.
// 0x000936f8 CBackgroundManager_RecursiveRegistration
void CBackgroundManager::RecursiveRegistration(int32_t type) {
    if (type == 0) g_pEngine->m_pSavingManager->RegisterSerializableObject(this, nullptr);  // vt+0x24
}
