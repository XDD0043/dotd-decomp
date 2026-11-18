// CLightComponent.cpp - reconstructed original translation unit 0xba598-0xbb3c0 (GAME_TOC1, main_toc1), 21 functions, 16 live.
// Primary class: CLightComponent  key 0xa4c  category Logic  size 0x2c  vtable 0xb17a98
// Other owners: LightColorAnim (3), LightData (1), CMaterial (1), GetMaterialTexture (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0xba598  CLightComponent_Delete
//   [x] 0xba5e8  CLightComponent_RecursiveRegistration
//   [ ] 0xba648  RegisterCLightComponentClass
//   [ ] 0xba6c0  _GLOBAL__I_ba6c0
//   [x] 0xba6d0  CLightComponent_FreeLightList_maybe  (XXL2 FreeBlinkData: the same body as Destroy 0xbb278 (no bl caller))
//   [ ] 0xba740  LightColorAnim_AdvanceAndEvaluate_maybe  [dead]
//   [x] 0xba7f0  CLightComponent_AllocLightList_maybe  (XXL2 AllocateBlinkData: inlined in Load 0xbafe8 (no bl caller))
//   [x] 0xba8b8  CLightComponent_Create
//   [x] 0xba930  CLightComponent_DeleteArray
//   [x] 0xba9d0  CLightComponent_CreateArray
//   [x] 0xbaad0  CLightComponent_PostLoad  (IKSerializable's: returns 1)
//   [ ] 0xbaad8  FUN_000baad8  [dead]
//   [ ] 0xbaba0  LightColorAnim_Load_maybe  [dead]
//   [ ] 0xbac38  LightColorAnim_Save_maybe  [dead]
//   [x] 0xbacd8  LightData_UpdateColorAnimation_maybe
//   [ ] 0xbad70  CLightComponent_Save
//   [x] 0xbafe8  CLightComponent_Load
//   [x] 0xbb278  CLightComponent_Destroy
//   [x] 0xbb2e8  CMaterial_Delete  (the registry factory: DOTD_DECLARE_FACTORIES(CMaterial))
//   [ ] 0xbb338  FUN_000bb338  [dead]
//   [x] 0xbb398  GetMaterialTexture_maybe  (ported in CKSrvShadow.cpp (GetMaterialTexture))
//
//   [x] 0x9a10d8  CLightComponent_GetClassType  [inline]
//   [x] 0x9a10e0  CLightComponent_GetClassID  [inline]
//   [x] 0x9a10e8  CLightComponent_IsKindOfClass  [inline]
//   [x] 0x9a1108  CLightComponent_DeletingDestructor  [inline]
//   [x] 0x9a1148  CLightComponent_Destructor  [inline]
#include "k2000/logic/render/CLightComponent.h"

#include <cstring>

#include "k2000/io/IKFile.h"
#include "k2000/logic/CKSavingManager.h"
#include "k2000/misc/Engine.h"
#include "k2000/math/CurveKeys.h"
#include "k2000/memory/Mem.h"
#include "k2000/system/IKTime.h"

namespace {
// Constants of the math unit's static initialiser (StaticInitAndDestruction_11578, Str.cpp; live values).
// STUB: local copies until that unit exports them.
const uint8_t kColorWhite[4] = {0xff, 0xff, 0xff, 0xff};  // 0x00c50dfc CColor (r, g, b, a)
const CVector3 kVectorAxisZ = {0.0f, 0.0f, 1.0f};         // 0x00c50d4c
}  // namespace

// 0x000ba8b8 CLightComponent_Create, in the original's store order; +0x04 and +0x1c are left as they are.
CLightComponent::CLightComponent() {
    m_baProperties = 0;
    m_pLightFrame = nullptr;
    m_fRadius = 0.0f;
    m_fConeAngle = 0.0f;
    std::memcpy(m_cLightColor, kColorWhite, 4);
    m_v3Dir = kVectorAxisZ;
}

// 0x000bafe8 CLightComponent_Load
int32_t CLightComponent::Load(IKFile* file, int32_t type) {
    if (type != K_LEVEL_PLATEFORMS) return 1;
    ReadU32LE(file, &m_baProperties);
    ReadRaw(file, m_cLightColor, 4);  // not swapped by the original
    ReadF32LE(file, &m_fRadius);
    ReadF32LE(file, &m_fConeAngle);
    uint8_t bytes[0xc];  // one 0xc-byte read, then each word byte-swapped
    file->Read(bytes, 0xc);
    float* dir = reinterpret_cast<float*>(&m_v3Dir);
    for (int i = 0; i < 3; ++i) {
        const uint8_t* b = bytes + 4 * i;
        const uint32_t bits = static_cast<uint32_t>(b[0]) | (static_cast<uint32_t>(b[1]) << 8) |
                              (static_cast<uint32_t>(b[2]) << 16) | (static_cast<uint32_t>(b[3]) << 24);
        std::memcpy(dir + i, &bits, 4);
    }
    m_pBlinkColorData = nullptr;
    if ((m_baProperties & 8) == 0) return 1;
    // XXL2 CLightComponent::AllocateBlinkData, inlined: OperatorNew(0x14), 20 keys reserved (0xa0 bytes).
    CBlinkData* blink = static_cast<CBlinkData*>(::operator new(sizeof(CBlinkData)));
    blink->m_ColorLine.m_pBlock = nullptr;
    blink->m_ColorLine.m_ui32NbUsedElt = 0;
    blink->m_ColorLine.m_ui32NbElt = 20;
    blink->m_ColorLine.m_pBlock =
        static_cast<CurveKey*>(Mem_AllocAligned16(20 * static_cast<uint32_t>(sizeof(CurveKey))));
    m_pBlinkColorData = blink;
    blink->m_fBlinkLength = 1.0f;  // TOC -0x5a74
    m_pBlinkColorData->m_fCurTime = 0.0f;
    ReadF32LE(file, &m_pBlinkColorData->m_fBlinkLength);
    CurveKeys_Load(&m_pBlinkColorData->m_ColorLine, file);
    return 1;
}

// 0x000bacd8 LightData_UpdateColorAnimation_maybe
void CLightComponent::UpdateColorAnimation(const IKTime* frameClock) {
    if ((m_baProperties & 8) == 0) return;
    CBlinkData* blink = m_pBlinkColorData;
    float time = frameClock->m_afDeltaTime[IKTime::SCALABLE_GAME_TIME] + blink->m_fCurTime;
    if (time <= blink->m_fBlinkLength) {
        blink->m_fCurTime = time;
    } else {
        blink->m_fCurTime = 0.0f;
        time = blink->m_fCurTime;
    }
    ColorCurve_Evaluate(time / blink->m_fBlinkLength, m_cLightColor, &blink->m_ColorLine);
}

// 0x000bb278 CLightComponent_Destroy
void CLightComponent::Destroy() {
    CBlinkData* blink = m_pBlinkColorData;
    if (blink == nullptr) return;
    if (blink->m_ColorLine.m_pBlock != nullptr) Mem_FreeAligned16(blink->m_ColorLine.m_pBlock);
    delete blink;  // OperatorDelete
    m_pBlinkColorData = nullptr;
}

// 0x000ba5e8 CLightComponent_RecursiveRegistration
void CLightComponent::RecursiveRegistration(int32_t type) {
    if (type == 0) g_pEngine->m_pSavingManager->RegisterSerializableObject(this, nullptr);  // vt+0x24
}
