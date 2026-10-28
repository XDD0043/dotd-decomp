// CKHkHeroActivator.cpp - reconstructed original translation unit 0x447fc0-0x44ae90 (GAME_TOC1, main_toc1), 37 functions, 33 live.
// Primary class: CKHkHeroActivator  key 0x1a02  category Hook  size 0xb8  vtable 0xb26bc0
// Other owners: CKHkLinkedBeacon (2)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x447fc0  CKHkHeroActivator_Delete
//   [x] 0x448010  CKHkHeroActivator_Restart
//   [ ] 0x448038  CKHkHeroActivator_CallSetEnabled
//   [ ] 0x448078  RegisterCKHkHeroActivatorClass
//   [ ] 0x4480f0  _GLOBAL__I_4480f0
//   [ ] 0x448100  CKHkHeroActivator_SetTransform_maybe
//   [ ] 0x4481c8  CKHkHeroActivator_GetInfo
//   [ ] 0x448218  CKHkHeroActivator_Resume
//   [ ] 0x448240  CKHkHeroActivator_Pause
//   [ ] 0x448268  CKHkHeroActivator_UpdateProximityFx_maybe
//   [ ] 0x448800  CKHkHeroActivator_Stop
//   [x] 0x448828  CKHkHeroActivator_Start
//   [ ] 0x448880  CKHkHeroActivator_PostLoad
//   [ ] 0x448910  CKHkHeroActivator_Save
//   [ ] 0x448938  CKHkHeroActivator_RecursiveRegistration
//   [ ] 0x448960  CKHkHeroActivator_Destroy
//   [x] 0x448988  CKHkHeroActivator_Construct  [dead]
//   [x] 0x4489c0  CKHkHeroActivator_DeleteArray
//   [ ] 0x448a60  CKHkHeroActivator_DeletingDestructor
//   [ ] 0x448aa8  CKHkHeroActivator_Destructor
//   [ ] 0x448ad8  CKHkHeroActivator_BaseDestructor
//   [x] 0x448b08  CKHkHeroActivator_SetDefaultState
//   [ ] 0x448c00  CKHkHeroActivator_Construct_2  [dead]
//   [ ] 0x448c38  CKHkHeroActivator_ApplyStatePreset_maybe
//   [ ] 0x448cc0  CKHkHeroActivator_OnActivate
//   [x] 0x448f00  CKHkHeroActivator_CreateArray
//   [x] 0x448fb0  CKHkHeroActivator_Create
//   [ ] 0x449008  CKHkHeroActivator_IsInActivationCone_maybe
//   [x] 0x4494c0  CKHkHeroActivator_SetMarkerFx_maybe
//   [x] 0x4497d0  CKHkHeroActivator_SetEnabled
//   [ ] 0x449990  CKHkHeroActivator_MessageProc
//   [ ] 0x449bd0  CKHkHeroActivator_Update
//   [ ] 0x44a518  CKHkHeroActivator_OnDeactivate
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
#include "Renderware/rpprtstd/RpPrtStd.h"
#include "Renderware/rwcore/RwCamera.h"
#include "k2000/core/Stub.h"
#include "k2000/scenegraph/CParticlesNodeFx.h"
#include "k2000/scenegraph/CSGLeaf.h"

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
    m_unk98 = 0;
    m_unk9C = 0;
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
    m_unkA4 = 0;
    m_fUnkA0 = static_cast<float>(m_unk88);
}

// 0x004494c0 CKHkHeroActivator_SetMarkerFx_maybe. STUB(C2.2): see the header.
void CKHkHeroActivator::SetMarkerFx(int32_t on) {
    if (on != 0) DOTD_STUB_ONCE("CKHkHeroActivator_SetMarkerFx_maybe: acquire the input-icon effect (C2.2, services)");
    m_unk94 = 0;
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
    m_unk9C = 0;
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
