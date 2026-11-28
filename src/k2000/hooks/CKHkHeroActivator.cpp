// CKHkHeroActivator.cpp - reconstructed original translation unit 0x447fc0-0x44ae90 (GAME_TOC1, main_toc1), 37 functions, 33 live.
// Primary class: CKHkHeroActivator  key 0x1a02  category Hook  size 0xb8  vtable 0xb26bc0
// Other owners: CKHkLinkedBeacon (2)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x447fc0  CKHkHeroActivator_Delete
//   [x] 0x448010  CKHkHeroActivator_Restart
//   [x] 0x448038  CKHkHeroActivator_CallSetEnabled
//   [ ] 0x448078  RegisterCKHkHeroActivatorClass
//   [ ] 0x4480f0  _GLOBAL__I_4480f0
//   [x] 0x448100  CKHkHeroActivator_SetTransform_maybe
//   [x] 0x4481c8  CKHkHeroActivator_GetInfo
//   [x] 0x448218  CKHkHeroActivator_Resume  (empty / no effect: inherited)
//   [x] 0x448240  CKHkHeroActivator_Pause  (empty / no effect: inherited)
//   [x] 0x448268  CKHkHeroActivator_UpdateProximityFx_maybe
//   [x] 0x448800  CKHkHeroActivator_Stop  (empty / no effect: inherited, CKHkActorBase_d82_maybe_Stop 0x3f6e50)
//   [x] 0x448828  CKHkHeroActivator_Start
//   [x] 0x448880  CKHkHeroActivator_PostLoad
//   [ ] 0x448910  CKHkHeroActivator_Save
//   [x] 0x448938  CKHkHeroActivator_RecursiveRegistration  (= the inherited slot: CKHkActorBase_d82_maybe_LevelReset 0x3f6ee8, then 1)
//   [x] 0x448960  CKHkHeroActivator_Destroy  (inherited: CKHkActorBase_d82_maybe_ClearReferences 0x3f6e08 calls vt+0xc0, KStub_Nop_9c0bc8)
//   [x] 0x448988  CKHkHeroActivator_Construct  [dead]
//   [x] 0x4489c0  CKHkHeroActivator_DeleteArray
//   [x] 0x448a60  CKHkHeroActivator_DeletingDestructor  (the deleting form of the implicit destructor)
//   [x] 0x448aa8  CKHkHeroActivator_Destructor  (the C++ destructor (CKHkActorBase_d82_maybe_BaseDestructor 0x3f73f0))
//   [x] 0x448ad8  CKHkHeroActivator_BaseDestructor  (C++ destructor chain: vtable stores only)
//   [x] 0x448b08  CKHkHeroActivator_SetDefaultState
//   [ ] 0x448c00  CKHkHeroActivator_Construct_2  [dead]
//   [x] 0x448c38  CKHkHeroActivator_ApplyStatePreset_maybe
//   [x] 0x448cc0  CKHkHeroActivator_OnActivate
//   [x] 0x448f00  CKHkHeroActivator_CreateArray
//   [x] 0x448fb0  CKHkHeroActivator_Create
//   [x] 0x449008  CKHkHeroActivator_IsInActivationCone_maybe
//   [x] 0x4494c0  CKHkHeroActivator_SetMarkerFx_maybe
//   [x] 0x4497d0  CKHkHeroActivator_SetEnabled
//   [x] 0x449990  CKHkHeroActivator_MessageProc
//   [x] 0x449bd0  CKHkHeroActivator_Update
//   [x] 0x44a518  CKHkHeroActivator_OnDeactivate
//   [x] 0x44a5e0  CKHkHeroActivator_Load
//   [x] 0x44ad78  CKHkLinkedBeacon_Delete
//   [ ] 0x44adc8  CKHkLinkedBeacon_ResetLinkStates_maybe  [dead]
//   [ ] 0x44ae48  FUN_0044ae48  [dead]
//
//   [ ] 0x9c3bb0  CKHkHeroActivator_IsKindOfClass  [inline]
//   [ ] 0x9c3c08  CKHkHeroActivator_GetClassType  [inline]
//   [ ] 0x9c3c10  CKHkHeroActivator_GetClassID  [inline]
#include "k2000/hooks/CKHkHeroActivator.h"

#include <cstring>

#include "k2000/io/IKFile.h"
#include "k2000/logic/IKFxData.h"
#include "k2000/logic/fx/CKInputIconNodeFx.h"
#include "k2000/misc/Engine.h"
#include "k2000/services/CKSrvFx.h"
#include "Renderware/rpprtstd/RpPrtStd.h"
#include "Renderware/rwcore/RwCamera.h"
#include "k2000/core/Stub.h"
#include "k2000/scenegraph/CParticlesNodeFx.h"
#include "k2000/scenegraph/CSGLeaf.h"
#include "k2000/math/CMatrix34.h"
#include "k2000/scenegraph/CSGMovable.h"
#include "Spyro2008/groups/C22SpyroShims.h"
#include "Spyro2008/groups/CKGrpS08Hero.h"
#include "Spyro2008/hooks/CKHkS08Hero.h"
#include "Spyro2008/logic/CKS08GameManager.h"
#include "crt/ppc_ops.h"
#include "crt/xsinf.h"
#include "k2000/components/CKLocTextAccessor.h"
#include "k2000/core/IKInfo.h"
#include "k2000/dictionaries/CKSoundDictionaryID.h"
#include "k2000/logic/CKParticlesEffectFxData.h"
#include "k2000/logic/CMultiGeometryBasic.h"
#include "k2000/logic/ai/CKDetectorBase.h"
#include "k2000/logic/fx/CKParticlesEffectNodeFx.h"
#include "k2000/logic/sound/CKSound.h"
#include "k2000/math/Math.h"
#include "k2000/math/Vec3.h"
#include "k2000/misc/Mat4.h"
#include "k2000/services/CTriggerStarter.h"
#include "k2000/system/IKTime.h"

namespace {
// One 12-byte read, then each word byte-swapped (the PS3's Read(0xc) + three lwbrx).
void ReadVector3Words(IKFile* file, CVector3* v) {
    uint32_t w[3];
    ReadU32LEWords(file, w, 3);
    std::memcpy(v, w, sizeof(w));
}
}  // namespace

// 0x0044a5e0 CKHkHeroActivator_Load
int32_t CKHkHeroActivator::Load(IKFile* file, int32_t type) {
    CKHkActorBase::Load(file, type);
    if (type != K_LEVEL_PLATEFORMS) return 1;
    ReadVector3Words(file, &m_unk20);
    ReadVector3Words(file, &m_unk2C);
    IKFile_ReadRef(file, &m_unk70);
    ReadF32LE(file, &m_unk78);
    ReadF32LE(file, &m_unk74);
    ReadF32LE(file, &m_unk7C);
    m_unk48.Load(file, K_LEVEL_PLATEFORMS);
    m_unk38.Load(file, K_LEVEL_PLATEFORMS);
    m_unk40.Load(file, K_LEVEL_PLATEFORMS);
    IKFile_ReadRef(file, &m_unk50);
    ReadU8(file, &m_unk54[0]);
    ReadU8(file, &m_unk54[1]);
    ReadU8(file, &m_unk54[2]);
    ReadU32LE(file, &m_unk58);
    IKFile_ReadRef(file, &m_unk5C);
    IKFile_ReadRef(file, &m_unk60);
    IKFile_ReadRef(file, &m_unk6C);
    IKFile_ReadRef(file, &m_unk84);
    ReadU8(file, &m_unk88);
    ReadU8(file, &m_unk89);
    ReadF32LE(file, &m_unk8C);
    ReadF32LE(file, &m_unk80);
    IKFile_ReadRef(file, &m_unk64);
    ReadF32LE(file, &m_unk68);
    ReadF32LE(file, &m_unkAC);
    ReadF32LE(file, &m_unkB0);
    IKFile_ReadRef(file, &m_unk90);
    return 1;
}

// 0x00448828 CKHkHeroActivator_Start: CKHkActorBase_d82_maybe_ResetRuntime (empty), then vt+0x54.
void CKHkHeroActivator::Start() {
    CKHkActorBase::Start();
    Restart();
}

// 0x00448010 CKHkHeroActivator_Restart: bits 9 and 10 cleared, the two run-time words 0.
void CKHkHeroActivator::Restart() {
    m_bitArray &= 0xfffff9ffu;
    m_pProximityFx = nullptr;
    m_pUser = nullptr;
}

// 0x00448b08 CKHkHeroActivator_SetDefaultState: state 0 always, state 1 only when bit 5 is set. Bit 3 (the
// default "enabled") sets bit 8 and the proximity float to the byte m_unk88, else clears them.
void CKHkHeroActivator::SetDefaultState(int32_t flag) {
    CKHkActorBase::SetDefaultState(flag);
    if (flag != 0 && (m_bitArray & 0x20) == 0) return;
    if ((m_bitArray & 8) == 0) {
        m_bitArray &= 0xfffffeffu;
        m_fUnkA0 = 0.0f;
        return;
    }
    m_bitArray = (m_bitArray & 0xfffffeffu) | 0x100u;
    m_fUnkA4 = 0.0f;  // stw 0
    m_fUnkA0 = static_cast<float>(m_unk88);
}

// 0x00448880 CKHkHeroActivator_PostLoad: CKHkActorBase's part (0x3f6e70 = IKLife_PostLoad 0x19f68, then 1), the three
// trigger lists' PostLoad (TriggerEventList_PostLoad_maybe 0x236330, returns 1) in the order +0x48, +0x38, +0x40, and the
// marker effect cleared (stw 0 at +0x94; no type test). SetMarkerFx tests it, so without this it read the heap
// (found by work/fill_test.py with fills ff / 3f: a crash in CKGrpS08Clamp::Start -> SetEnabled -> SetMarkerFx).
int32_t CKHkHeroActivator::PostLoad(int32_t type) {
    PostLoadLife(type);
    m_unk48.PostLoad(type);
    m_unk38.PostLoad(type);
    m_unk40.PostLoad(type);
    m_pMarkerFx = nullptr;
    return 1;
}

// 0x004494c0 CKHkHeroActivator_SetMarkerFx_maybe. The release: the effect's StopAndRelease (vt+0x58) with this hook, then
// the word cleared (stw of `on`, 0). The acquire: CKSrvFx_AcquireFx inlined on the data +0x5c (a CKInputIconFxData; its
// node is a CKInputIconNodeFx, started through vt+0x64), then placed at m_unk20; an effect already held is only moved.
void CKHkHeroActivator::SetMarkerFx(int32_t on) {
    if (on == 0) {
        if (m_pMarkerFx == nullptr) return;
        m_pMarkerFx->StopAndRelease(this);  // vt+0x58
        m_pMarkerFx = nullptr;
        return;
    }
    if (m_pMarkerFx != nullptr) {
        const CVector3 position = m_unk20;
        static_cast<CKInputIconNodeFx*>(m_pMarkerFx)->SetPosition(&position);  // 0x001c45c8
        return;
    }
    m_pMarkerFx = static_cast<CKSrvFx*>(g_pEngine->m_srvFx)->AcquireFx(static_cast<IKFxData*>(m_unk5C), this);
    if (m_pMarkerFx == nullptr) return;
    const CVector3 position = m_unk20;
    static_cast<CKInputIconNodeFx*>(m_pMarkerFx)->SetPosition(&position);
}

// 0x00448038 CKHkHeroActivator_CallSetEnabled
void CKHkHeroActivator_CallSetEnabled(IKSerializable* activator, int32_t enabled) {
    static_cast<CKHkActorBase*>(activator)->SetEnabled(enabled);  // vt+0xcc
}

// 0x00448100 CKHkHeroActivator_SetTransform_maybe
void CKHkHeroActivator::SetTransform(const CMatrix34* matrix) {
    m_unk20 = matrix->m_pos;
    m_unk2C = matrix->m_at;
    const RwMatrix* local = reinterpret_cast<const RwMatrix*>(matrix);
    if (m_unk60 != nullptr) static_cast<CSGMovable*>(m_unk60)->SetLocalMatrix(local);  // 0x000d0be8
    if (m_pKGLObject != nullptr) static_cast<CSGMovable*>(m_pKGLObject)->SetLocalMatrix(local);
    if (m_unk84 != nullptr) static_cast<CSGMovable*>(m_unk84)->SetLocalMatrix(local);
}

// 0x004497d0 CKHkHeroActivator_SetEnabled. The particle node m_unk60 (the "ring" effect) is hidden and its
// emitter stopped when disabled; enabled, it is placed at m_unk20, oriented along m_unk2C with +y up, its
// emitter started, and its bit 10 follows the argument. The scene node of the hook (+0x1c) has its hidden
// bit (flag 4) set to the opposite.
void CKHkHeroActivator::SetEnabled(int32_t enabled) {
    const uint32_t v = static_cast<uint32_t>(enabled) & 0xff;
    m_bitArray = (m_bitArray & 0xfffffeffu) | (v << 8);
    SetMarkerFx(0);
    m_bitArray &= 0xfffff9ffu;
    m_pUser = nullptr;
    CParticlesNodeFx* node = static_cast<CParticlesNodeFx*>(m_unk60);
    if (node != nullptr) {
        if (v == 0) {
            const uint32_t p = node->m_sgProperties;
            node->m_sgProperties = (p & 0xfff00000u) | (p & 0x7f800u) | (p & 0x3ffu);  // bits 10 and 19 cleared
            node->m_pRpPrtStdEmitter->flag &= ~rpPRTSTDEMITTERFLAGEMIT;
        } else {
            RwFrame* frame = node->m_pRwFrame;
            frame->modelling.pos.x = m_unk20.x;
            frame->modelling.pos.y = m_unk20.y;
            frame->modelling.pos.z = m_unk20.z;
            frame->modelling.flags &= 0xfffdffffu;
            RwFrame_MarkDirty(frame);
            static const CVector3 kUp = {0.0f, 1.0f, 0.0f};  // 0x00c50d40 (TOC1 +0x52e8)
            node->SetOrientationFromAtUp(&m_unk2C, &kUp);
            const uint32_t p = node->m_sgProperties;
            node->m_sgProperties = (p & 0xfff00000u) | (p & 0x7f800u) | (p & 0x3ffu) | (v << 10);
            node->m_fEmissionSpeedAdjustment = 0.0f;  // stw 0
            node->m_pRpPrtStdEmitter->flag |= rpPRTSTDEMITTERFLAGACTIVE | rpPRTSTDEMITTERFLAGEMIT;
        }
    }
    if (m_pKGLObject != nullptr) {
        CSGLeaf* scene = static_cast<CSGLeaf*>(m_pKGLObject);
        scene->m_sgProperties = (scene->m_sgProperties & 0xfffffffbu) | ((((static_cast<uint32_t>(enabled)) ^ 1u) & 0xffu) << 2);
    }
}

// ---- C2.8 meca-hero: the activator's run time ----

namespace {
const float kZero = 0.0f;              // TOC1 +0x52ec
const float kOne = 1.0f;               // TOC1 +0x5304
const float kDegToRad = 0x1.1df468p-6f;  // TOC1 +0x5328 (0x3c8efa34)
const CVector3 kUpAxis = {0.0f, 1.0f, 0.0f};  // 0x00c50d40 (TOC1 +0x52e8)

CKGrpS08Hero* HeroGroup() { return static_cast<CKGrpS08Hero*>(g_pEngine->m_gameManager->m_unk04[1]); }
CKS08GameManager* GameManager() { return static_cast<CKS08GameManager*>(g_pEngine->m_gameManager); }
CKHkS08Hero* HeroAt(CKGrpS08Hero* group, uint32_t index) {  // 0x002ca080 GetHeroByDragonIndex
    return static_cast<CKHkS08Hero*>(group->m_apHeros[index]);
}
CKHkS08Hero* FocusedHero(CKGrpS08Hero* group) {  // 0x002ca0f8 CKGrpS08Hero_GetFocusedHero
    if (group->m_ui8FocusedDragon == 0xff) return nullptr;
    return HeroAt(group, static_cast<uint32_t>(static_cast<int32_t>(static_cast<int8_t>(group->m_ui8FocusedDragon))));
}
// The game's cosine of a float angle: the inlined polynomial for a clear sign bit, the library's cosf of the negation
// otherwise (the original tests the stored word's sign).
float GameCosf(float x) {
    uint32_t bits;
    std::memcpy(&bits, &x, 4);
    return static_cast<int32_t>(bits) < 0 ? crt::LibCosf(-x) : crt::InlineCosf(x);
}
// SceneNode_SetAlphaRecursive with the low byte of fctiwz (stfiwx, lbz +3).
void SetAlpha(IKSerializable* node, float alpha) {
    SceneNode_SetAlphaRecursive(node, static_cast<uint8_t>(ppc::fctiwz(alpha)), 1);  // TocBridge 0x98f570 -> 0x582c60
}
void PlaySound0At(CKSoundDictionaryID* sounds, const CVector3* position) {
    if (sounds->GetSound(0) != nullptr) sounds->GetSound(0)->SetPosition(position);  // 0x00112bc0, 0x00110fa0
    if (sounds->GetSound(0) != nullptr) sounds->GetSound(0)->Play(kZero);            // 0x00111230
}
}  // namespace

// 0x004481c8 CKHkHeroActivator_GetInfo
int32_t CKHkHeroActivator::GetInfo(IKInfo* info, int32_t request) {
    const int32_t base = CKHkActorBase::GetInfo(info, request);  // KStub_Return1 0x3f7140
    if (base == 2) return 2;
    return base == 0 ? 0 : 1;
}

// 0x00448c38 CKHkHeroActivator_ApplyStatePreset_maybe
void CKHkHeroActivator::ApplyStatePreset(int32_t state) {
    const uint32_t bit = state == 0 ? 8u : 0x10u;
    if ((m_bitArray & bit) != 0) {
        m_bitArray = (m_bitArray & 0xfffffeffu) | 0x100u;
        m_fUnkA4 = kZero;  // stw 0
        m_fUnkA0 = static_cast<float>(m_unk88);
    } else {
        m_bitArray &= 0xfffffeffu;
        m_fUnkA0 = kZero;  // stw 0
    }
}

// 0x00449008 CKHkHeroActivator_IsInActivationCone_maybe. The detector's geometry (+0x08): its byte +0x1c & 3 is the
// shape (0 a box: maxima +0x04..+0x0c, minima +0x10..+0x18; 1 a sphere: centre +0x04 with the two floats +0x10 / +0x14
// for Vec3_IsWithinRadius_maybe 0x2441e8); other shapes never hold the point.
uint8_t CKHkHeroActivator::IsInActivationCone(const CVector3* position, const CVector3* direction) const {
    if (m_unk70 != nullptr) {
        const CMultiGeometryBasic* geometry =
            static_cast<const CMultiGeometryBasic*>(static_cast<CKDetectorBase*>(m_unk70)->m_pGeometry);
        const uint32_t shape = geometry->m_baData & 3u;
        const float* g = geometry->m_afShape;  // box: +0x04 max x, y, z, +0x10 min x, y, z
        if (shape == 0) {
            // cror lt|eq tests: a NaN coordinate fails each bound.
            if (!(g[3] <= position->x) || !(g[0] >= position->x)) return 0;
            if (!(g[5] <= position->z) || !(g[2] >= position->z)) return 0;
            if (!(g[4] <= position->y)) return 0;
            return position->y <= g[1] ? 1 : 0;
        }
        if (shape == 1) return static_cast<uint8_t>(Vec3_IsWithinRadius(g[3], g[4], g, &position->x));  // 0x002441e8
        return 0;
    }
    float dx = position->x - m_unk20.x;
    float dy = position->y - m_unk20.y;
    float dz = position->z - m_unk20.z;
    float length = static_cast<float>(c22spyro::MathSqrtf(ppc::fmadds(dz, dz, ppc::fmadds(dx, dx, dy * dy))));  // 0x00010690
    if (length != kZero) {
        const float inverse = kOne / length;
        dz = dz * inverse;
        dx = dx * inverse;
        dy = dy * inverse;
    } else {
        length = kZero;
    }
    if (m_unk78 < length) return 0;  // bge: a NaN length passes
    // The direction from the cone's apex (+0x80 behind the position along +0x2c) to the point.
    const float back = -m_unk80;
    float cy = ppc::fmadds(back, m_unk2C.y, position->y - m_unk20.y);
    float cx = ppc::fmadds(back, m_unk2C.x, position->x - m_unk20.x);
    float cz = ppc::fmadds(back, m_unk2C.z, position->z - m_unk20.z);
    const float apex = static_cast<float>(c22spyro::MathSqrtf(ppc::fmadds(cz, cz, ppc::fmadds(cx, cx, cy * cy))));
    if (apex != kZero) {
        const float inverse = kOne / apex;
        cz = cz * inverse;
        cx = cx * inverse;
        cy = cy * inverse;
    }
    const float coneCos = GameCosf(m_unk74 * kDegToRad);
    const float along = ppc::fmadds(m_unk2C.z, dz, ppc::fmadds(m_unk2C.x, dx, m_unk2C.y * dy));
    if (!(along > coneCos)) return 0;  // ble: a NaN fails
    const float faceCos = GameCosf(m_unk7C * kDegToRad);
    const float facing = -ppc::fmadds(direction->z, cz, ppc::fmadds(direction->x, cx, cy * direction->y));  // fnmadds
    return faceCos < facing ? 1 : 0;
}

// 0x00448268 CKHkHeroActivator_UpdateProximityFx_maybe. The effect is acquired as CKSrvFx_AcquireFx does (inlined in
// the original), after the data's start matrix (+0x24) took the node's world matrix, or a basis from +0x2c and +0x20.
void CKHkHeroActivator::UpdateProximityFx() {
    if (m_unk64 == nullptr) return;
    CKGrpS08Hero* group = HeroGroup();
    const uint8_t count = group->m_ui8ControlledHeroCount;  // 0x002ca288 GetControlledHeroCount
    if (kZero < m_unkB0 && count != 0) {
        uint32_t index = 0;
        uint32_t next = 0;
        do {
            ++next;
            CKHkS08Hero* hero = static_cast<CKHkS08Hero*>(group->m_apControlledHeroes[index]);  // 0x002ca0e0
            index = next & 0xffu;
            const float* p = hero->GetPositionPtr();  // 0x00361968
            const float dy = p[1] - m_unk20.y;
            const float dx = p[0] - m_unk20.x;
            const float dz = p[2] - m_unk20.z;
            const float distance2 = ppc::fmadds(dz, dz, ppc::fmadds(dx, dx, dy * dy));
            if (distance2 < m_unkB0 * m_unkB0) {
                if (m_pProximityFx != nullptr) return;
                CMatrix34 matrix;
                if (m_pKGLObject != nullptr) {
                    std::memcpy(&matrix, FrameLtm(static_cast<CSGMovable*>(m_pKGLObject)->m_pRwFrame), sizeof(matrix));
                } else {
                    matrix.m_pos = m_unk20;
                    Mat4_SetBasisFromAtUp(&matrix, &m_unk2C, &kUpAxis);  // 0x0023fd30
                }
                uint32_t flags;
                std::memcpy(&flags, reinterpret_cast<const uint8_t*>(&matrix) + 0xc, 4);
                flags &= 0xfffdffffu;
                std::memcpy(reinterpret_cast<uint8_t*>(&matrix) + 0xc, &flags, 4);
                CKParticlesEffectFxData* data = static_cast<CKParticlesEffectFxData*>(m_unk64);
                std::memcpy(data->m_pLocalMatrix, &matrix, sizeof(matrix));
                m_pProximityFx = static_cast<CKSrvFx*>(g_pEngine->m_srvFx)->AcquireFx(data, this);
                return;
            }
        } while (count != index);
    }
    if (m_pProximityFx == nullptr) return;
    m_pProximityFx->StopAndRelease(this);  // vt+0x58
    m_pProximityFx = nullptr;
}

// 0x00449990 CKHkHeroActivator_MessageProc
int32_t CKHkHeroActivator::MessageProc(uint16_t message, void* data) {
    const int32_t base = CKHkActorBase::MessageProc(message, data);  // 0x003f7148
    int32_t own = 1;
    if (message == 0x93f) {
        if ((m_bitArray & 0x80u) != 0) {
            m_bitArray &= 0xfffffeffu;
            SetMarkerFx(0);
        }
        QueueTriggerSignals(&m_unk48);
        m_bitArray = (m_bitArray & 0xfffffbffu) | 0x400u;
        PlaySound0At(static_cast<CKSoundDictionaryID*>(m_unk6C), &m_unk20);
        own = 0;
        m_pUser = static_cast<IKSerializable*>(data);
    } else if (message == 0x2666) {
        // The text of the CKLocTextAccessor +0x50: its first text with a text block (+0x04), else its +0x10.
        CKLocTextAccessor* accessor = static_cast<CKLocTextAccessor*>(m_unk50);
        IKSerializable* text = accessor->m_texts.m_pBlock != nullptr ? accessor->m_texts.m_pBlock[0] : accessor->m_pText;
        own = 0;
        *static_cast<IKSerializable**>(data) = text;
    }
    if (base == 3 || own == 3) return 3;
    if (base == 2 || own == 2) return 2;
    if (base != 0) return own;
    return 0;
}

// 0x00448cc0 CKHkHeroActivator_OnActivate
void CKHkHeroActivator::VfA0() {
    CKHkActorBase::VfA0();  // 0x003f7338
    m_pProximityFx = nullptr;
    if ((m_bitArray & 0x100u) != 0) {
        CParticlesNodeFx* ring = static_cast<CParticlesNodeFx*>(m_unk60);
        if (ring != nullptr) {
            RwFrame* frame = ring->m_pRwFrame;
            frame->modelling.pos.z = m_unk20.z;
            frame->modelling.pos.x = m_unk20.x;
            frame->modelling.pos.y = m_unk20.y;
            frame->modelling.flags &= 0xfffdffffu;
            RwFrame_MarkDirty(frame);  // 0x00010698
            ring->SetOrientationFromAtUp(&m_unk2C, &kUpAxis);  // 0x000d0918
            ring->m_sgProperties = (ring->m_sgProperties & ~0x80400u) | 0x400u;
            ring->m_fEmissionSpeedAdjustment = 0.0f;  // stw 0
            ring->m_pRpPrtStdEmitter->flag |= rpPRTSTDEMITTERFLAGACTIVE | rpPRTSTDEMITTERFLAGEMIT;  // ori 0xa
        }
        m_fUnkA8 = m_unk68;
        if (m_unk68 == kZero) UpdateProximityFx();
    }
    if (m_unk84 != nullptr) {
        if (m_pKGLObject != nullptr) {
            static_cast<CSGMovable*>(m_unk84)->SetLocalMatrix(&static_cast<CSGMovable*>(m_pKGLObject)->m_pRwFrame->modelling);
        } else {
            CSGMovable* node = static_cast<CSGMovable*>(m_unk84);
            RwFrame* frame = node->m_pRwFrame;
            frame->modelling.pos.z = m_unk20.z;
            frame->modelling.pos.x = m_unk20.x;
            frame->modelling.pos.y = m_unk20.y;
            frame->modelling.flags &= 0xfffdffffu;
            RwFrame_MarkDirty(frame);
            node->SetOrientationFromAtUp(&m_unk2C, &kUpAxis);
        }
        SetAlpha(m_unk84, m_fUnkA4);
    }
    if (m_pKGLObject != nullptr) SetAlpha(m_pKGLObject, m_fUnkA0);
    m_pMarkerFx = nullptr;
}

// 0x0044a518 CKHkHeroActivator_OnDeactivate
void CKHkHeroActivator::VfA4() {
    CKHkActorBase::VfA4();  // 0x003f7370
    CParticlesNodeFx* ring = static_cast<CParticlesNodeFx*>(m_unk60);
    if (ring != nullptr) {
        ring->m_sgProperties &= 0xfff7fbffu;
        ring->m_pRpPrtStdEmitter->flag &= ~rpPRTSTDEMITTERFLAGEMIT;
    }
    SetMarkerFx(0);
    if (m_pProximityFx == nullptr) return;
    m_pProximityFx->StopAndRelease(this);  // vt+0x58
    m_pProximityFx = nullptr;
}

// 0x00449bd0 CKHkHeroActivator_Update
void CKHkHeroActivator::Update(IKTime* frameClock) {
    // WorldObjectBase_Update_Nop 0x3f6e68 (empty).
    if (m_unk90 != nullptr) {
        const RwMatrix* world = FrameLtm(static_cast<CSGMovable*>(m_unk90)->m_pRwFrame);  // RwFrame +0x50
        m_unk20 = {world->pos.x, world->pos.y, world->pos.z};
        m_unk2C = {world->at.x, world->at.y, world->at.z};
        if (m_unk60 != nullptr) static_cast<CSGMovable*>(m_unk60)->SetLocalMatrix(world);  // 0x000d0be8
        if (m_pKGLObject != nullptr) static_cast<CSGMovable*>(m_pKGLObject)->SetLocalMatrix(world);
        if (m_unk84 != nullptr) static_cast<CSGMovable*>(m_unk84)->SetLocalMatrix(world);
    }
    const float dt = frameClock->m_afDeltaTime[0];  // +0x1c
    if ((m_bitArray & 0x100u) == 0) {
        // Disabled: both alphas fade to 0, the proximity effect released.
        if (m_pKGLObject != nullptr && m_fUnkA0 != kZero) {
            m_fUnkA0 = m_fUnkA0 - dt * m_unk8C;
            if (m_fUnkA0 < kZero) m_fUnkA0 = kZero;
            SetAlpha(m_pKGLObject, m_fUnkA0);
        }
        if (m_unk84 != nullptr && m_fUnkA4 != kZero) {
            m_fUnkA4 = m_fUnkA4 - dt * m_unk8C;
            if (m_fUnkA4 < kZero) m_fUnkA4 = kZero;
            SetAlpha(m_unk84, m_fUnkA4);
        }
        if (m_pProximityFx == nullptr) return;
        m_pProximityFx->StopAndRelease(this);  // vt+0x58
        m_pProximityFx = nullptr;
        return;
    }
    CKGrpS08Hero* group = HeroGroup();
    m_ui32HeroesInCone = 0;
    if (m_pProximityFx != nullptr) {
        CVector3 position;
        if (m_pKGLObject == nullptr) {
            position = m_unk20;
        } else {
            const RwV3d& p = FrameLtm(static_cast<CSGMovable*>(m_pKGLObject)->m_pRwFrame)->pos;
            position = {p.x, p.y, p.z};
        }
        position.y = position.y + m_unkAC;
        SetOwnedParticleEffectPosition(static_cast<CKParticlesEffectNodeFx*>(m_pProximityFx), &position, this);  // 0x001cdce0
    }
    // The heroes of the mask +0x58 that may attach to the activator (vt+0xe0 with 2) and stand in its cone.
    uint32_t inCone = 0;
    uint32_t player = 0;   // one of them is player-controlled
    uint32_t focused = 0;  // ... and the focused hero
    for (uint32_t i = 0;; ++i) {
        const uint32_t bit = ppc::slw(1, i);
        if (static_cast<int32_t>(group->GetHeroCount()) <= static_cast<int32_t>(i)) break;  // 0x002ca038 (vt+0xf4)
        CKHkS08Hero* hero = HeroAt(group, i & 0xffu);
        if ((bit & m_unk58) == 0) continue;
        if (hero->CanAttachTo(this, 2) == 0) continue;  // 0x00361d08 (vt+0xe0)
        const float* p = hero->GetPositionPtr();  // 0x00361968
        const CVector3 position = {p[0], p[1], p[2]};
        const CVector3 forward = {hero->m_unk540, hero->m_unk544, hero->m_unk548};  // 0x00361a50 (+0x540)
        if (IsInActivationCone(&position, &forward) == 0) continue;
        ++inCone;
        m_ui32HeroesInCone |= bit;
        if (hero->IsPlayerControlled() == 0) continue;  // 0x00362af0
        player = 1;
        if (hero == FocusedHero(group)) focused = 1;
    }
    // The activation rule: +0x56 how the count +0x54 compares (0 at least, 1 exactly, 2 at most), +0x55 who must be in
    // the cone (0 a player's hero, 1 no player's hero, 3 the focused hero, else anyone).
    uint32_t active = 0;
    const int8_t compare = static_cast<int8_t>(m_unk54[2]);
    const int32_t needed = m_unk54[0];
    const int32_t found = static_cast<int32_t>(inCone);
    const bool countOk = compare == 1 ? needed == found : compare == 2 ? needed >= found : compare == 0 ? needed <= found : false;
    if (countOk) {
        const int8_t who = static_cast<int8_t>(m_unk54[1]);
        if (who == 3) {
            active = focused;
        } else if (who == 0) {
            active = player;
        } else {
            active = who == 1 ? (player ^ 1u) : 1u;
        }
    }
    if (active != ((m_bitArray >> 9) & 1u)) {
        if (active == 0) {
            QueueTriggerSignals(&m_unk40);  // 0x00236338
        } else {
            QueueTriggerSignals(&m_unk38);
        }
        m_bitArray = (m_bitArray & 0xfffffdffu) | (active << 9);
    }
    float sceneAlpha = static_cast<float>(m_unk88);  // f30
    float extraAlpha = kZero;                         // f31
    bool used = false;
    if ((m_bitArray & 0x200u) == 0) {
        SetMarkerFx(0);
    } else if ((m_bitArray & 0x40u) == 0) {
        // Bit 6 clear: the activator uses itself (as message 0x93f, without a hero).
        if ((m_bitArray & 0x80u) != 0) {
            m_bitArray &= 0xfffffeffu;
            SetMarkerFx(0);
        }
        QueueTriggerSignals(&m_unk48);
        m_bitArray = (m_bitArray & 0xfffffbffu) | 0x400u;
        PlaySound0At(static_cast<CKSoundDictionaryID*>(m_unk6C), &m_unk20);
    } else {
        // The player-controlled heroes in the cone make it their interaction target (the button prompt).
        uint8_t target = 0;
        for (uint32_t i = 0; static_cast<int32_t>(group->GetHeroCount()) > static_cast<int32_t>(i); ++i) {
            CKHkS08Hero* hero = HeroAt(group, i & 0xffu);
            if ((ppc::slw(1, i & 0x3fu) & m_ui32HeroesInCone) == 0) continue;
            if (hero->IsPlayerControlled() == 0) continue;
            const uint8_t index = hero->m_ui8Hero == hero->m_ui8TrackedLeader ? hero->m_ui8Leader : 0xff;  // 0x00362ac8
            if (GameManager()->SetHeroInteractionTarget(this, 2, index) != 0) target = 1;  // 0x004ee770
        }
        SetMarkerFx(target);
        if (target != 0) {
            used = true;
            if (m_unk84 != nullptr) sceneAlpha = kZero;
            const uint8_t shown = m_unk89;
            if (m_pProximityFx != nullptr) {
                m_pProximityFx->StopAndRelease(this);  // vt+0x58
                m_pProximityFx = nullptr;
            }
            extraAlpha = static_cast<float>(shown);
        }
    }
    if (!used && kZero < m_unk68) {
        // The proximity test every +0x68 seconds.
        m_fUnkA8 = m_fUnkA8 - dt;
        if (m_fUnkA8 <= kZero) {
            m_fUnkA8 = m_unk68;
            UpdateProximityFx();
        }
    }
    // Both alphas step towards their targets at +0x8c per second.
    if (m_pKGLObject != nullptr && sceneAlpha != m_fUnkA0) {
        if (sceneAlpha < m_fUnkA0) {
            m_fUnkA0 = m_fUnkA0 - dt * m_unk8C;
            if (sceneAlpha > m_fUnkA0) m_fUnkA0 = sceneAlpha;  // ble: no clamp on a NaN
        } else {
            m_fUnkA0 = ppc::fmadds(dt, m_unk8C, m_fUnkA0);
            if (sceneAlpha < m_fUnkA0) m_fUnkA0 = sceneAlpha;
        }
        SetAlpha(m_pKGLObject, m_fUnkA0);
    }
    if (m_unk84 == nullptr || m_fUnkA4 == extraAlpha) return;
    if (m_fUnkA4 > extraAlpha) {
        m_fUnkA4 = m_fUnkA4 - dt * m_unk8C;
        if (!(m_fUnkA4 >= extraAlpha)) m_fUnkA4 = extraAlpha;  // bge: a NaN is clamped
    } else {
        m_fUnkA4 = ppc::fmadds(dt, m_unk8C, m_fUnkA4);
        if (m_fUnkA4 > extraAlpha) m_fUnkA4 = extraAlpha;
    }
    SetAlpha(m_unk84, m_fUnkA4);
}
