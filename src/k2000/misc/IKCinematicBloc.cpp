// IKCinematicBloc.cpp - reconstructed original translation unit 0x18e8d8-0x18edd8 (GAME_TOC1, main_toc1), 7 functions, 7 live.
// Primary owner: IKCinematicBloc (not a registered class)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [ ] 0x18e8d8  IKCinematicBloc_LevelReset
//   [x] 0x18e940  IKCinematicBloc_IsOutputOf_maybe
//   [x] 0x18e9e0  IKCinematicBloc_CheckSekensStop
//   [ ] 0x18eac0  IKCinematicBloc_PostLoad
//   [x] 0x18eae8  IKCinematicBloc_Construct
//   [ ] 0x18eb50  IKCinematicBloc_Construct_2
//   [x] 0x18ebb8  IKCinematicBloc_InterruptConflictingBlocs
//
//   [ ] 0x9aa508  IKCinematicBloc_vf8  [inline]
//   [ ] 0x9aa530  IKCinematicBloc_vf14  [inline]
//   [ ] 0x9aa538  IKCinematicBloc_vf18  [inline]
//   [ ] 0x9aa540  IKCinematicBloc_vf5C  [inline]
//   [ ] 0x9aa548  IKCinematicBloc_vf64  [inline]
//   [ ] 0x9aa550  IKCinematicBloc_vf68  [inline]
//   [ ] 0x9aa558  IKCinematicBloc_vf6C  [inline]
//   [ ] 0x9aa560  IKCinematicBloc_vf0  [inline]
//   [ ] 0x9aa580  IKCinematicBloc_DeletingDestructor  [inline]
#include "k2000/misc/IKCinematicBloc.h"

#include "k2000/logic/CKCinematicScene.h"
#include "k2000/logic/CKCinematicSceneData.h"
#include "k2000/hooks/IKHook.h"
#include "k2000/hooks/IKLife.h"
#include "k2000/logic/CKSekens.h"
#include "k2000/scenegraph/CSGMovable.h"
#include "Renderware/rwcore/RwCamera.h"
#include "crt/ppc_ops.h"
#include "k2000/misc/CKSekensElement.h"
#include "k2000/misc/Engine.h"
#include "k2000/services/CKSrvCinematic.h"
#include "k2000/services/CKSrvSekensor.h"

#include <cmath>

namespace {
// 0x00c50d58: three floats StaticInitAndDestruction_11578 sets to 1.0 (0x3f800000) at startup.
constexpr float kCinematicBlocDefaultVector[3] = {1.0f, 1.0f, 1.0f};
}  // namespace

// 0x0018eae8 IKCinematicBloc_Construct
IKCinematicBloc::IKCinematicBloc() {
    m_unk2c[0] = kCinematicBlocDefaultVector[0];
    m_unk2c[2] = kCinematicBlocDefaultVector[2];
    m_unk2c[1] = kCinematicBlocDefaultVector[1];
}

// 0x0018e940 IKCinematicBloc_IsOutputOf_maybe: the outputs (type 1) of `element` searched from the last.
uint8_t IKCinematicBloc::IsOutputOf(IKCinematicElement* element) {
    uint32_t count = 0;
    IKCinematicElement** outputs = m_pRelatedScene->GetNodeOutputs(&count, 1, element);
    while (count != 0) {
        --count;
        if (outputs[count] == this) return 1;
    }
    return 0;
}

// The inlined Complete body of the blocs (see IKCinematicBloc.h).
void IKCinematicBloc::CompleteBloc() {
    uint32_t count = 0;
    if ((m_DataFlags & 1) == 0) return;
    m_pRelatedScene->RemoveActiveNode(this);
    m_DataFlags = (m_DataFlags & 0xfffffffau) | 4;
    m_bSekensReached = 0;
    if ((m_DataFlags & 0x10) == 0) return;
    CKSrvCinematic* service = static_cast<CKSrvCinematic*>(g_pEngine->m_srvCinematic);
    IKCinematicElement** outputs = m_pRelatedScene->GetNodeOutputs(&count, 1, this);
    for (uint32_t i = 0; i < count; ++i) service->ActivateNode(this, outputs[i]);
    count = 0;
    outputs = m_pRelatedScene->GetNodeOutputs(&count, 2, this);
    for (uint32_t i = 0; i < count; ++i) outputs[i]->Stop();  // vt+0x6c
}

// 0x0018e9e0 IKCinematicBloc_CheckSekensStop
uint8_t IKCinematicBloc::CheckSekensStop() {
    if (m_pSekensElement != nullptr) {
        CKSekensElement* element = static_cast<CKSekensElement*>(m_pSekensElement);
        const IKSerializable* current = static_cast<CKSrvSekensor*>(g_pEngine->m_srvSekensor)->GetCurrentSekens();
        uint8_t stop;
        if (current == nullptr) {
            stop = m_bSekensReached;
        } else {
            if (element->m_pSekens != current) return 1;
            m_bSekensReached = 1;
            stop = element->m_unk08;
        }
        if (stop != 0) {
            Stop();  // vt+0x6c
            return 0;
        }
    }
    return 1;
}

// 0x0018ebb8 IKCinematicBloc_InterruptConflictingBlocs. The scene's running elements that are blocs asking for
// an exclusive actor (vt+0x84) and share this bloc's actor (the hook of their CKCinematicSceneData, +0x04) are
// stopped unless this bloc is one of their outputs. CKSrvCinematic bit 1 guards the recursion.
uint8_t IKCinematicBloc::InterruptConflictingBlocs() {
    CKSrvCinematic* service = static_cast<CKSrvCinematic*>(g_pEngine->m_srvCinematic);
    if (IsExclusiveOnActor() == 0) return 1;
    if (((service->m_baData >> 1) & 1) != 0) return 0;
    service->m_baData = static_cast<uint8_t>((service->m_baData & 0xfc) | (service->m_baData & 1) | 2);
    for (IKCinematicElement* other = m_pRelatedScene->m_pActiveNodes; other != nullptr; other = other->m_pNext) {
        if (other == this) continue;
        if (other->IsKindOfClass(0x84c) == 0) continue;
        IKCinematicBloc* bloc = static_cast<IKCinematicBloc*>(other);
        if (bloc->IsExclusiveOnActor() == 0) continue;
        if (other->m_pElementData == nullptr || m_pElementData == nullptr) continue;
        if (static_cast<CKCinematicSceneData*>(other->m_pElementData)->m_pHook !=
            static_cast<CKCinematicSceneData*>(m_pElementData)->m_pHook)
            continue;
        uint32_t count = 0;
        IKCinematicElement** outputs = m_pRelatedScene->GetNodeOutputs(&count, 1, other);
        bool found = false;
        for (uint32_t i = count; i != 0; --i) {
            if (outputs[i - 1] == this) {
                found = true;
                break;
            }
        }
        if (!found) other->Stop();  // vt+0x6c
    }
    service->m_baData = static_cast<uint8_t>((service->m_baData & 0xfc) | (service->m_baData & 1));
    return 1;
}

namespace {
// The length of a matrix row, Math_Sqrtf(x*x + y*y + z*z) with the sum fused as in the original (fmuls, fmadds, fmadds).
float RowLength(const float* v) {
    float sum = v[1] * v[1];
    sum = ppc::fmadds(v[0], v[0], sum);
    sum = ppc::fmadds(v[2], v[2], sum);
    return static_cast<float>(std::sqrt(static_cast<double>(sum)));
}
}  // namespace

// The beginning of every bloc's Start (see the header); the same code as CKPlayVideoCinematicBloc::Start's.
void IKCinematicBloc::StartCommon() {
    CKCinematicSceneData* data = static_cast<CKCinematicSceneData*>(m_pElementData);
    IKHook* hook = data != nullptr ? static_cast<IKHook*>(data->m_pHook) : nullptr;
    CSGMovable* node = hook != nullptr ? static_cast<CSGMovable*>(hook->m_pKGLObject) : nullptr;
    if (node == nullptr) {
        m_unk2c[0] = 1.0f;  // the shared vector 0x00c50d58
        m_unk2c[1] = 1.0f;
        m_unk2c[2] = 1.0f;
    } else {
        const RwFrame* frame = node->m_pRwFrame;
        m_unk2c[0] = RowLength(&frame->modelling.at.x);
        m_unk2c[1] = RowLength(&frame->modelling.right.x);
        m_unk2c[2] = RowLength(&frame->modelling.up.x);
    }
    if (UsesActor() != 0 && hook != nullptr) {  // vt+0x80
        IKLife* object = hook->m_pHookLife != nullptr ? static_cast<IKLife*>(hook->m_pHookLife) : hook;
        if (((object->m_bitArray >> 1) & 1) == 0) Complete();  // vt+0x64
    }
    if (((m_DataFlags & 0x20) == 0 || (m_DataFlags & 4) == 0) && InterruptConflictingBlocs() != 0) {
        m_pRelatedScene->AddActiveNode(this);
        m_DataFlags = (m_DataFlags & 0xfffffff8u) | (m_DataFlags & 2) | 1;
        m_bSekensReached = 0;
    } else {
        Complete();  // vt+0x64
    }
}
