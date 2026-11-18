// CKHkDoor.cpp - reconstructed original translation unit 0x416710-0x419a18 (GAME_TOC1, main_toc1), 31 functions, 25 live.
// Primary class: CKHkDoor  key 0x1942  category Hook  size 0x80  vtable 0xb25d10
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x416710  CKHkDoor_Delete
//   [ ] 0x416760  FUN_00416760  [dead]
//   [ ] 0x416858  CKHkDoor_ResetStateEntriesToNone_maybe  [dead]
//   [ ] 0x4168e0  CKHkDoor_SetStateTableEntry2Bit_maybe  [dead]
//   [ ] 0x416910  RegisterCKHkDoorClass
//   [ ] 0x416988  _GLOBAL__I_416988
//   [x] 0x416998  CKHkDoor_SetDefaultState
//   [ ] 0x4169f0  CKHkDoor_SetClosedCollisionState_maybe  [dead]
//   [ ] 0x416a70  CKHkDoor_SetOpenCollisionState_maybe  [dead]
//   [x] 0x416af8  CKHkDoor_UpdateStateFromLinkedObjects_maybe
//   [x] 0x4172e0  CKHkDoor_Resume  (empty / no effect: inherited)
//   [x] 0x417308  CKHkDoor_Pause  (empty / no effect: inherited)
//   [x] 0x417330  CKHkDoor_Stop  (empty / no effect: inherited, CKHkActorBase_d82_maybe_Stop 0x3f6e50)
//   [x] 0x417358  CKHkDoor_Start
//   [x] 0x417390  CKHkDoor_PostLoad  (= the inherited slot)
//   [ ] 0x417400  CKHkDoor_Save
//   [x] 0x417428  CKHkDoor_RecursiveRegistration  (= the inherited slot: CKHkActorBase_d82_maybe_LevelReset 0x3f6ee8, then 1)
//   [x] 0x417450  CKHkDoor_DeleteArray
//   [x] 0x4174f0  CKHkDoor_Create
//   [x] 0x417548  CKHkDoor_AttachSounds
//   [x] 0x4175f0  CKHkDoor_Destroy
//   [x] 0x417638  CKHkDoor_GetInfo
//   [x] 0x417768  CKHkDoor_CreateArray
//   [x] 0x417818  CKHkDoor_OnDeactivate
//   [x] 0x4179a8  CKHkDoor_ApplyStatePreset_maybe
//   [x] 0x417b30  CKHkDoor_Update
//   [ ] 0x4186b8  CKHkDoor_SetOpenState_maybe  [dead]
//   [x] 0x418810  CKHkDoor_MessageProc
//   [x] 0x418c60  CKHkDoor_OnActivate
//   [x] 0x419150  CKHkDoor_Load
//   [x] 0x419738  CKHkDoor_Restart
//
//   [ ] 0x9c2e10  CKHkDoor_IsKindOfClass  [inline]
//   [ ] 0x9c2e68  CKHkDoor_GetClassType  [inline]
//   [ ] 0x9c2e70  CKHkDoor_GetClassID  [inline]
//   [ ] 0x9c2e78  CKHkDoor_GetTriggerProp9D  [inline]
//   [ ] 0x9c2e98  CKHkDoor_Destructor  [inline]
//   [ ] 0x9c2ec8  CKHkDoor_GetTriggerProp9C  [inline]
//   [ ] 0x9c2ed8  CKHkDoor_DeletingDestructor  [inline]
#include "k2000/hooks/CKHkDoor.h"
#include "k2000/core/IKInfo.h"
#include <cstring>

#include "Renderware/rwcore/RwCamera.h"
#include "k2000/io/IKFile.h"
#include "k2000/logic/CKPFGraphTransition.h"
#include "k2000/scenegraph/CSGBranch.h"
#include "k2000/scenegraph/CSGMovable.h"
#include "k2000/services/ICollisionMesh.h"
#include "k2000/memory/Mem.h"
#include "crt/ppc_ops.h"
#include "Spyro2008/groups/C22SpyroShims.h"
#include "Spyro2008/groups/CKGrpS08Hero.h"
#include "k2000/logic/CDefaultGameManager.h"
#include "k2000/cameras/CKSrvCamera.h"
#include "k2000/dictionaries/CKSoundDictionaryID.h"
#include "k2000/logic/CKParticlesEffectFxData.h"
#include "k2000/logic/ai/CKDetectorBase.h"
#include "k2000/logic/sound/CKSound.h"
#include "k2000/math/Vec3.h"
#include "k2000/misc/Engine.h"
#include "k2000/scenegraph/CSGLeaf.h"
#include "k2000/services/CKSrvFx.h"
#include "k2000/services/CTriggerStarter.h"
#include "k2000/system/IKTime.h"

// 0x00419150 CKHkDoor_Load: no branch on the serialization type (only the trigger starters get it).
int32_t CKHkDoor::Load(IKFile* file, int32_t type) {
    CKHkActorBase::Load(file, type);
    ReadF32LE(file, &m_unk44);
    ReadF32LE(file, &m_unk48);
    ReadF32LE(file, &m_unk4C);
    ReadU16LE(file, &m_baAutoAction);
    ReadU8(file, &m_ui8NbOfDectector);
    if (m_ui8NbOfDectector == 0) {
        m_apBackDetector = nullptr;
        m_apFrontDetector = nullptr;
    } else {
        const uint32_t bytes = static_cast<uint32_t>(m_ui8NbOfDectector * sizeof(IKSerializable*));
        m_apFrontDetector = static_cast<IKSerializable**>(Mem_AllocAligned16(bytes));
        m_apBackDetector = static_cast<IKSerializable**>(Mem_AllocAligned16(bytes));
        IKFile_ReadObjectRefArray(file, m_apFrontDetector, m_ui8NbOfDectector);
        IKFile_ReadObjectRefArray(file, m_apBackDetector, m_ui8NbOfDectector);
    }
    IKFile_ReadRef(file, &m_unk68);
    IKFile_ReadRef(file, &m_unk54);
    IKFile_ReadRef(file, &m_unk50);
    IKFile_ReadRef(file, &m_unk58);
    IKFile_ReadRef(file, &m_unk5C);
    m_tsOpenStarter.Load(file, type);
    m_tsCloseStarter.Load(file, type);
    IKFile_ReadRef(file, &m_unk6C);
    return 1;
}

// 0x00416998 CKHkDoor_SetDefaultState: KStub_Nop_3f72a0, then the preset 0.
void CKHkDoor::SetDefaultState(int32_t flag) {
    CKHkActorBase::SetDefaultState(flag);
    ApplyStatePreset(0);
}

// 0x00417358 CKHkDoor_Start: CKHkActorBase_d82_maybe_ResetRuntime (empty), then the first runtime word 0.
void CKHkDoor::Start() {
    CKHkActorBase::Start();
    m_unk20 = 0;
}

// 0x004179a8 CKHkDoor_ApplyStatePreset_maybe. Bits 10/11 of the flags take the preset's two bits; when
// bit 11 (the preset's second bit) is set, bits 15 and 16 are set and bit 14 cleared, every detector's
// 3-bit state in the first runtime word becomes 6 (shifts through ppc::slw: the count of detectors can
// exceed what 32 bits hold) and bit 12 is set.
void CKHkDoor::ApplyStatePreset(int32_t state) {
    const uint32_t first = state == 0 ? 6u : 8u;
    uint32_t f = m_bitArray;
    f = (f & ~0xc00u) | (((f >> first) & 1) << 10) | (((f >> (first + 1)) & 1) << 11);
    m_bitArray = f;
    if (((f >> 11) & 1) == 0) return;
    f = (f & ~0x1c000u) | 0x18000u;
    m_bitArray = f;
    uint32_t states = m_unk20;
    for (uint32_t i = m_ui8NbOfDectector; i != 0; --i) {
        const uint32_t shift = (i - 1) * 3;
        states = states & ~ppc::slw(7, shift) | ppc::slw(6, shift);
    }
    if (m_ui8NbOfDectector != 0) m_unk20 = states;
    m_bitArray = (m_bitArray & 0xffffefffu) | 0x1000u;
}

void CKHkDoor::ApplyOpenState() {
    const uint32_t closeTransitions = (m_bitArray & 0x400u) != 0 ? 4u : 0u;
    m_fOpening = closeTransitions != 0 ? m_unk44 : 0.0f;
    CKPFGraphTransition* transitions[2] = {static_cast<CKPFGraphTransition*>(m_unk58),
                                           static_cast<CKPFGraphTransition*>(m_unk5C)};
    for (CKPFGraphTransition* transition : transitions) {
        if (transition != nullptr) transition->m_baFlags = (transition->m_baFlags & 0xfffffffbu) | closeTransitions;
    }
    if (m_unk54 != nullptr) static_cast<ICollisionMesh*>(m_unk54)->SetActive(closeTransitions != 0 ? 0u : 1u);  // 0x001a6b70
    m_bitArray = (m_bitArray & 0xfffdffffu) | 0x20000u;
    m_bitArray &= 0xffffdfffu;
}

void CKHkDoor::PlaceLeaves() {
    RwFrame* frame = static_cast<CSGMovable*>(m_pKGLObject)->m_pRwFrame;
    const float opening = m_fOpening;
    frame->modelling.pos.y = ppc::fmadds(opening, m_vSlideAxis.y, m_vClosedPosition.y);
    frame->modelling.pos.x = ppc::fmadds(opening, m_vSlideAxis.x, m_vClosedPosition.x);
    frame->modelling.pos.z = ppc::fmadds(opening, m_vSlideAxis.z, m_vClosedPosition.z);
    frame->modelling.flags &= 0xfffdffffu;
    RwFrame_MarkDirty(frame);  // 0x00010698
    if (m_unk50 == nullptr) return;
    RwFrame* other = static_cast<CSGMovable*>(m_unk50)->m_pRwFrame;
    const float back = -m_fOpening;  // fneg
    other->modelling.pos.x = ppc::fmadds(back, m_vSlideAxis.x, m_vClosedPosition.x);
    other->modelling.pos.y = ppc::fmadds(back, m_vSlideAxis.y, m_vClosedPosition.y);
    other->modelling.pos.z = ppc::fmadds(back, m_vSlideAxis.z, m_vClosedPosition.z);
    other->modelling.flags &= 0xfffdffffu;
    RwFrame_MarkDirty(other);
}

void CKHkDoor::ResetDetectorStates() {
    m_bitArray = (m_bitArray & 0xfffe3fffu) | 0x18000u;
    uint32_t states = m_unk20;
    for (uint32_t i = m_ui8NbOfDectector; i != 0; --i) {
        const uint32_t shift = (i - 1) * 3;
        states = states & ~ppc::slw(7, shift) | ppc::slw(6, shift);
    }
    if (m_ui8NbOfDectector != 0) m_unk20 = states;
    m_bitArray = (m_bitArray & 0xffffefffu) | 0x1000u;
}

// 0x00418c60 CKHkDoor_OnActivate. The axis (jump table 0x418cc8 on bits 3-5): 0 / 1 the right row, 2 / 3 up, 4 / 5 at,
// the odd ones negated; 6 and 7 leave +0x34 as it is.
void CKHkDoor::VfA0() {
    CKHkActorBase::VfA0();  // 0x003f7338
    CSGLeaf* leaf = static_cast<CSGLeaf*>(m_pKGLObject);
    const uint32_t axis = (m_bitArray >> 3) & 7u;
    if (axis <= 5) {
        const RwMatrix& m = leaf->m_pRwFrame->modelling;
        const RwV3d& row = axis < 2 ? m.right : (axis < 4 ? m.up : m.at);
        if ((axis & 1u) != 0) {
            m_vSlideAxis = {-row.x, -row.y, -row.z};
        } else {
            m_vSlideAxis = {row.x, row.y, row.z};
        }
    }
    ApplyOpenState();
    const RwV3d& position = leaf->m_pRwFrame->modelling.pos;  // RwFrame +0x40
    m_vClosedPosition = {position.x, position.y, position.z};
    if (m_unk50 != nullptr) {
        CSGLeaf* other = static_cast<CSGLeaf*>(m_unk50);
        if (other->m_pParent != nullptr) other->m_pParent->RemoveChild(other);  // vt+0x78
        leaf->m_pParent->AddChild(other);                                         // vt+0x70
        other->SetLocalMatrix(&leaf->m_pRwFrame->modelling);  // 0x000d0be8
    }
    PlaceLeaves();
    leaf->m_sgProperties &= 0xfffffffbu;
    if (m_unk50 != nullptr) static_cast<CSGLeaf*>(m_unk50)->m_sgProperties &= 0xfffffffbu;
    ResetDetectorStates();
}

// 0x00419738 CKHkDoor_Restart (vt+0x54): a door that is not disabled (flag bit 2) takes its preset open or closed state
// again, its leaves placed and the detector states reset (OnActivate's steps without the axis, the kept position and
// the reparenting).
void CKHkDoor::Restart() {
    if ((m_bitArray & 4u) != 0) return;
    ApplyOpenState();
    PlaceLeaves();
    ResetDetectorStates();
}

// 0x00417638 CKHkDoor_GetInfo, with 0x009c2ec8 CKHkDoor_GetTriggerProp9C (+0xc bit 10) and 0x009c2e78 _GetTriggerProp9D
// (the float +0x24 is 0, TOC +0x4bc4). The actor base's answer (KStub_Return1 0x3f7140) is 1: an own id answers 0.
int32_t CKHkDoor::GetInfo(IKInfo* info, int32_t request) {
    if (request != kGetInfoValueAccessor) return 1;
    if (info->m_ui32Id == 0x9c) {
        return AnswerInfo(info, [](IKSerializable* o, uint32_t) { return (static_cast<CKHkDoor*>(o)->m_bitArray >> 10) & 1u; }, 0);
    }
    if (info->m_ui32Id == 0x9d) {
        return AnswerInfo(info, [](IKSerializable* o, uint32_t) {
            float value;
            std::memcpy(&value, &static_cast<CKHkDoor*>(o)->m_fOpening, 4);  // +0x24
            return value == 0.0f ? 1u : 0u;
        }, 0);
    }
    return 1;
}

// ---- C2.8 meca-hero: the door's run time ----

namespace {
// The opening / closing transitions' flag bit 2 (closed while open) and the collision mesh (+0x54, off while open).
void SetPassable(CKHkDoor* door, bool open) {
    CKPFGraphTransition* transitions[2] = {static_cast<CKPFGraphTransition*>(door->m_unk58),
                                           static_cast<CKPFGraphTransition*>(door->m_unk5C)};
    for (CKPFGraphTransition* transition : transitions) {
        if (transition != nullptr) transition->m_baFlags = (transition->m_baFlags & 0xfffffffbu) | (open ? 4u : 0u);
    }
    if (door->m_unk54 != nullptr) static_cast<ICollisionMesh*>(door->m_unk54)->SetActive(open ? 0u : 1u);  // 0x001a6b70
}
// Sound 0 (the move loop) started looped unless it plays (no instance).
void StartMoveLoop(CKSoundDictionaryID* sounds) {
    CKSound* sound = sounds->GetSound(0);  // 0x00112bc0
    if (sound == nullptr || sound->CountInstances() != 0) return;
    sound->SetLoop(1);       // 0x00110fd0
    sound->Play(0.0f);       // 0x00111230
}
}  // namespace

// 0x00416af8 CKHkDoor_UpdateStateFromLinkedObjects_maybe (flag bit 11). Each detector pair (front +0x60 / back +0x64,
// last first) updates (vt+0x50) and gives its 3-bit state in +0x20 from the detection types (vt+0x54: 0 entered, 1
// inside, 2 left): 0 / 1 entered from the front / back, 2 / 4 left the front (4: into the back), 3 / 5 left the back
// (5: into the front); bit 12 asks the inside test instead of the entered one. The combined state (3 all left the back,
// 4 all left on either side but not all the front, 0 entered from the front, 2 all left the front, 5 all left, 1 entered,
// else 6) changes flags bits 14-16; its auto action (+0x42, two bits per state) opens (0) or arms the hero check (1, bit
// 13). Armed, the door closes again (bits 10 and 13 cleared) once the focused hero is no longer within its distance to
// the camera plus 0.5 of the door. Bit 12 is cleared.
void CKHkDoor::UpdateStateFromLinkedObjects() {
    const uint32_t count = m_ui8NbOfDectector;
    if (count == 0) return;
    bool all3 = true, all4 = true, all0 = true, all2 = true, all5 = true, all1 = true;  // r24 r22 r20 r23 r21 r19
    for (int32_t i = static_cast<int32_t>(count) - 1; i != -1; --i) {
        CKDetectorBase* front = static_cast<CKDetectorBase*>(m_apFrontDetector[i]);
        CKDetectorBase* back = static_cast<CKDetectorBase*>(m_apBackDetector[i]);
        int32_t inFront = 0;
        int32_t inBack = 0;
        if ((m_bitArray & 0x1000u) == 0) {
            inFront = front->GetDetectionType(1);  // vt+0x54
            inBack = back->GetDetectionType(1);
        }
        front->Detect();  // vt+0x50
        back->Detect();
        const uint32_t shift = (static_cast<uint32_t>(i) & 0xffffu) * 3;
        auto setState = [&](uint32_t value) { m_unk20 = (m_unk20 & ~ppc::slw(7, shift)) | ppc::slw(value, shift); };
        if (static_cast<uint8_t>(inFront) != 0) {
            if (static_cast<uint8_t>(front->GetDetectionType(2)) != 0) {
                setState(static_cast<uint8_t>(back->GetDetectionType(1)) != 0 ? 4u : 2u);
            }
        } else if (static_cast<uint8_t>(inBack) == 0) {
            if (static_cast<uint8_t>(front->GetDetectionType(0)) != 0) {
                setState(0);
            } else if (static_cast<uint8_t>(back->GetDetectionType(0)) != 0) {
                setState(1);
            } else if ((m_bitArray & 0x1000u) != 0) {
                if (static_cast<uint8_t>(front->GetDetectionType(1)) != 0) {
                    setState(0);
                } else if (static_cast<uint8_t>(back->GetDetectionType(1)) != 0) {
                    setState(1);
                }
            }
        }
        if (static_cast<uint8_t>(inBack) != 0 && static_cast<uint8_t>(back->GetDetectionType(2)) != 0) {
            setState(static_cast<uint8_t>(front->GetDetectionType(1)) != 0 ? 5u : 3u);
        }
        switch ((m_unk20 >> shift) & 7u) {  // the jump table 0x00416c54
        case 0: all3 = all4 = all2 = all5 = all1 = false; break;  // keeps all0
        case 1: all3 = all4 = all0 = all2 = all5 = false; break;  // keeps all1
        case 2: all3 = all4 = all0 = false; break;                 // keeps all2, all5, all1
        case 3: all2 = all5 = all1 = false; break;                 // keeps all3, all4, all0
        case 4: all3 = all2 = all5 = all1 = false; break;          // keeps all4, all0
        case 5: all3 = all4 = all0 = all2 = false; break;          // keeps all5, all1
        default: all3 = all4 = all0 = all2 = all5 = all1 = false; break;
        }
    }
    uint32_t combined;
    if (all3) {
        combined = 3;
    } else if (all4) {
        combined = 4;
    } else if (all0) {
        combined = 0;
    } else if (all2) {
        combined = 2;
    } else if (all5) {
        combined = 5;
    } else {
        combined = all1 ? 1u : 6u;
    }
    if (((m_bitArray >> 14) & 7u) != combined) {
        if (combined != 6) {
            const uint32_t action = (static_cast<uint32_t>(m_baAutoAction) >> (combined * 2)) & 3u;
            if (action == 0) {
                m_bitArray = (m_bitArray | 0x400u) & 0xffffdfffu;
            } else if (action == 1) {
                m_bitArray |= 0x2000u;
            }
        }
        m_bitArray = (m_bitArray & 0xfffe3fffu) | (combined << 14);
    }
    if ((m_bitArray & 0x2000u) != 0) {
        CKGrpS08Hero* group = static_cast<CKGrpS08Hero*>(g_pEngine->m_gameManager->m_unk04[1]);
        CSGMovable* heroNode = static_cast<CSGMovable*>(
            group->m_unk66 == 0xff ? nullptr : group->m_apUnk44[static_cast<int8_t>(group->m_unk66)]);  // 0x002ca128
        const RwV3d& h = FrameLtm(heroNode->m_pRwFrame)->pos;
        const CVector3 hero = {h.x, h.y, h.z};
        const CVector3& camera = static_cast<CKSrvCamera*>(g_pEngine->m_srvCamera)->m_v3RealPos;
        const float dz = hero.z - camera.z;
        const float dx = hero.x - camera.x;
        const float reach = static_cast<float>(c22spyro::MathSqrtf(ppc::fmadds(dx, dx, dz * dz))) + 0.5f;  // TOC +0x4bfc
        const RwV3d& d = FrameLtm(static_cast<CSGMovable*>(m_pKGLObject)->m_pRwFrame)->pos;
        const CVector3 door = {d.x, d.y, d.z};
        if (Vec3_IsWithinXZRadius(reach, &door, &hero) == 0) {  // 0x00244298
            m_bitArray &= 0xffffdbffu;
        }
    }
    m_bitArray &= 0xffffefffu;
}

// 0x00417b30 CKHkDoor_Update: the linked detectors (bit 11); open (bit 10) the opening grows by +0x48 per second to
// +0x44, closed it shrinks to 0, the leaves placed each frame, the move loop sound 0 played meanwhile; at the end the
// +0x70 (opened) / +0x78 (closed) signals, sound 1, the transitions and the collision mesh. Starting to open (bit 17)
// starts the effect +0x6c above the door (+0x4c).
void CKHkDoor::Update(IKTime* frameClock) {
    // WorldObjectBase_Update_Nop 0x3f6e68 (empty).
    uint32_t flags = m_bitArray;
    if ((flags & 0x800u) != 0) {
        UpdateStateFromLinkedObjects();  // 0x00416af8
        flags = m_bitArray;
    }
    CKSoundDictionaryID* sounds = static_cast<CKSoundDictionaryID*>(m_unk68);
    const float dt = frameClock->m_afDeltaTime[0];
    if ((flags & 0x400u) != 0) {
        if (m_fOpening == m_unk44) {
            if ((flags & 0x20000u) != 0) return;
            SetPassable(this, true);
            QueueTriggerSignals(&m_tsOpenStarter);  // 0x00236338
            m_bitArray = (m_bitArray & 0xfffdffffu) | 0x20000u;
            if (sounds->GetSound(1) != nullptr) sounds->GetSound(1)->Play(0.0f);
            if (sounds->GetSound(0) != nullptr) Sound_Stop(sounds->GetSound(0), 0);  // 0x001111b0
            return;
        }
        if ((flags & 0x20000u) != 0) {
            m_bitArray &= 0xfffdffffu;
            CKParticlesEffectFxData* data = static_cast<CKParticlesEffectFxData*>(m_unk6C);
            if (data != nullptr) {
                data->m_unk08 = static_cast<uint8_t>((data->m_unk08 & 0xefu) | 0x10u);
                data->m_pAttachHotSpot = nullptr;
                data->m_pAttachOwner = static_cast<CSGLeaf*>(m_pKGLObject);
                RwMatrix* matrix = data->m_unk24;
                matrix->pos.x = 0.0f;  // the zero vector 0x00c50d64 (TOC +0x4c1c), y raised by +0x4c
                matrix->pos.z = 0.0f;
                matrix->pos.y = 0.0f + m_unk4C;
                matrix->flags &= 0xfffdffffu;
                data->m_unk08 = static_cast<uint8_t>((data->m_unk08 & 0xf7u) | 0x8u);
                static_cast<CKSrvFx*>(g_pEngine->m_srvFx)->StartEffect(data, this);
            }
        }
        StartMoveLoop(sounds);
        m_fOpening = ppc::fmadds(m_unk48, dt, m_fOpening);
        if (m_fOpening >= m_unk44) m_fOpening = m_unk44;  // cror gt|eq
        PlaceLeaves();
        return;
    }
    if (m_fOpening == 0.0f) {  // TOC +0x4bc4
        if ((flags & 0x20000u) != 0) return;
        SetPassable(this, false);
        QueueTriggerSignals(&m_tsCloseStarter);
        m_bitArray = (m_bitArray & 0xfffdffffu) | 0x20000u;
        if (sounds->GetSound(1) != nullptr) sounds->GetSound(1)->Play(0.0f);
        if (sounds->GetSound(0) != nullptr) Sound_Stop(sounds->GetSound(0), 0);
        return;
    }
    if ((flags & 0x20000u) != 0) m_bitArray &= 0xfffdffffu;
    StartMoveLoop(sounds);
    m_fOpening = m_fOpening - m_unk48 * dt;
    if (m_fOpening <= 0.0f) {
        // Closed: both leaves at the closed position (no transition change this frame).
        m_fOpening = 0.0f;
        RwFrame* frame = static_cast<CSGMovable*>(m_pKGLObject)->m_pRwFrame;
        frame->modelling.pos.z = m_vClosedPosition.z;
        frame->modelling.pos.x = m_vClosedPosition.x;
        frame->modelling.pos.y = m_vClosedPosition.y;
        frame->modelling.flags &= 0xfffdffffu;
        RwFrame_MarkDirty(frame);
        if (m_unk50 == nullptr) return;
        RwFrame* other = static_cast<CSGMovable*>(m_unk50)->m_pRwFrame;
        other->modelling.pos.z = m_vClosedPosition.z;
        other->modelling.pos.x = m_vClosedPosition.x;
        other->modelling.pos.y = m_vClosedPosition.y;
        other->modelling.flags &= 0xfffdffffu;
        RwFrame_MarkDirty(other);
        return;
    }
    PlaceLeaves();
    // Closing: the transitions open again (bit 2 cleared) and the collision mesh on.
    SetPassable(this, false);
}

// 0x00418810 CKHkDoor_MessageProc: the actor messages, then 0x996 open, 0x997 close, 0x998 the detectors linked (bit
// 11, their states reset to 6), 0x999 unlinked, 0x99a / 0x99b open / closed at once (the leaves placed).
int32_t CKHkDoor::MessageProc(uint16_t message, void* data) {
    const int32_t base = CKHkActorBase::MessageProc(message, data);  // 0x003f7148
    int32_t own = 1;
    switch (message) {
    case 0x996:
        m_bitArray = (m_bitArray & 0xfffffbffu) | 0x400u;
        own = 0;
        break;
    case 0x997:
        m_bitArray &= 0xfffffbffu;
        own = 0;
        break;
    case 0x998: {
        m_bitArray = (m_bitArray & 0xfffff7ffu) | 0x800u;
        m_bitArray = (m_bitArray & 0xfffe3fffu) | 0x10000u | 0x8000u;
        uint32_t states = m_unk20;
        for (uint32_t i = m_ui8NbOfDectector; i != 0; --i) {
            const uint32_t shift = ((i - 1) & 0xffffu) * 3;
            states = (states & ~ppc::slw(7, shift)) | ppc::slw(6, shift);
        }
        if (m_ui8NbOfDectector != 0) m_unk20 = states;
        m_bitArray = (m_bitArray & 0xffffefffu) | 0x1000u;
        own = 0;
        break;
    }
    case 0x999:
        m_bitArray &= 0xfffff7ffu;
        own = 0;
        break;
    case 0x99a:
    case 0x99b:
        if (message == 0x99a) {
            m_bitArray = (m_bitArray & 0xfffffbffu) | 0x400u;
            m_fOpening = m_unk44;
            SetPassable(this, true);
        } else {
            m_bitArray &= 0xfffffbffu;
            m_fOpening = 0.0f;  // stw 0
            SetPassable(this, false);
        }
        m_bitArray = (m_bitArray & 0xfffdffffu) | 0x20000u;
        PlaceLeaves();
        own = 0;
        break;
    default:
        break;
    }
    if (base == 3 || own == 3) return 3;
    if (base == 2 || own == 2) return 2;
    if (base != 0) return own;
    return 0;
}

// 0x00417818 CKHkDoor_OnDeactivate: the first leaf back at the closed position, the second leaf moved back under the
// first one (its parent's vt+0x78, the leaf's vt+0x70) with an identity matrix and hidden, the collision mesh off, the
// move loop stopped.
void CKHkDoor::VfA4() {
    CKHkActorBase::VfA4();  // 0x003f7370
    RwFrame* frame = static_cast<CSGMovable*>(m_pKGLObject)->m_pRwFrame;
    frame->modelling.pos.z = m_vClosedPosition.z;
    frame->modelling.pos.x = m_vClosedPosition.x;
    frame->modelling.pos.y = m_vClosedPosition.y;
    frame->modelling.flags &= 0xfffdffffu;
    RwFrame_MarkDirty(frame);
    CSGLeaf* other = static_cast<CSGLeaf*>(m_unk50);
    if (other != nullptr) {
        if (other->m_pParent != nullptr) other->m_pParent->RemoveChild(other);  // vt+0x78
        static_cast<CSGBranch*>(m_pKGLObject)->AddChild(other);                    // vt+0x70
        static_cast<CSGMovable*>(other)->SetIdentity();                          // CSGMovable_SetIdentity
    }
    static_cast<ICollisionMesh*>(m_unk54)->SetActive(0);  // 0x001a6b70
    if (other != nullptr) other->m_sgProperties = (other->m_sgProperties & 0xfffffffbu) | 4u;
    CKSoundDictionaryID* sounds = static_cast<CKSoundDictionaryID*>(m_unk68);
    if (sounds->GetSound(0) != nullptr) Sound_Stop(sounds->GetSound(0), 0);
}

// 0x004175f0 CKHkDoor_Destroy: CKHkActorBase_d82_maybe_ClearReferences 0x3f6e08 (the hook's vt+0xc0, KStub_Nop_9c0bc8),
// then the two detector arrays freed.
void CKHkDoor::Destroy() {
    Mem_FreeAligned16(m_apFrontDetector);  // 0x00052fb8
    Mem_FreeAligned16(m_apBackDetector);
}

// 0x00417548 CKHkDoor_AttachSounds
void CKHkDoor::KGLObjectAttached(IKSerializable* /*leaf*/) {
    CKSoundDictionaryID* sounds = static_cast<CKSoundDictionaryID*>(m_unk68);
    if (sounds->GetSound2(0) != nullptr) sounds->GetSound2(0)->SetAttachObject(m_pKGLObject);  // 0x00112bd8, 0x00111350
    if (sounds->GetSound2(1) != nullptr) sounds->GetSound2(1)->SetAttachObject(m_pKGLObject);
}
