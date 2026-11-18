// CKHkMovingObject.cpp - reconstructed original translation unit 0x5c58e8-0x5c79e0 (GAME_TOC2, main_toc2), 37 functions, 34 live.
// Primary owner: CKHkMovingObject (not a registered class)
// Other owners: RegisterCKHkMovingObjectClass (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x5c58e8  CKHkMovingObject_Destroy
//   [x] 0x5c5938  CKHkMovingObject_Construct  [dead]
//   [x] 0x5c59a0  CKHkMovingObject_vf50
//   [x] 0x5c59a8  CKHkMovingObject_vf68
//   [x] 0x5c59b0  CKHkMovingObject_vf70
//   [x] 0x5c59b8  CKHkMovingObject_vf78
//   [ ] 0x5c59c0  CKHkMovingObject_SyncTrackStateFromMover_maybe  [dead]
//   [x] 0x5c5a10  CKHkMovingObject_IsTrackAtStart_maybe
//   [x] 0x5c5a48  CKHkMovingObject_IsTrackAtEnd_maybe
//   [ ] 0x5c5a88  CKHkMovingObject_Construct_2  [dead]
//   [ ] 0x5c5af0  RegisterCKHkMovingObjectClass
//   [ ] 0x5c5b68  _GLOBAL__I_5c5b68
//   [x] 0x5c5b78  CKHkMovingObject_StopMover_maybe
//   [x] 0x5c5c38  CKHkMovingObject_StartMove_maybe
//   [ ] 0x5c5e00  CKHkMovingObject_Save
//   [x] 0x5c5e28  CKHkMovingObject_LevelReset  (RecursiveRegistration: IKHook's (inherited), then 1)
//   [x] 0x5c5e50  CKHkMovingObject_DestroyArray
//   [x] 0x5c5ef8  CKHkMovingObject_ClearReferences
//   [x] 0x5c5fd8  CKHkMovingObject_IsVisible_maybe
//   [x] 0x5c5ff0  CKHkMovingObject_OnDeactivate
//   [x] 0x5c6190  CKHkMovingObject_vf40
//   [x] 0x5c6278  CKHkMovingObject_RestoreCheckpointState_maybe
//   [x] 0x5c6360  CKHkMovingObject_ResetToInitialState_maybe
//   [x] 0x5c63c8  CKHkMovingObject_IsTrackBetweenEnds_maybe
//   [x] 0x5c6420  CKHkMovingObject_CreateArray
//   [x] 0x5c6508  CKHkMovingObject_Create
//   [x] 0x5c6588  CKHkMovingObject_SetMoveProgress_maybe
//   [x] 0x5c6688  CKHkMovingObject_Update
//   [x] 0x5c6c60  CKHkMovingObject_PostLoad
//   [x] 0x5c6df0  CKHkMovingObject_Destructor  (CKHkMovingObject.h)
//   [x] 0x5c6e58  CKHkMovingObject_Load
//   [x] 0x5c7498  CKHkMovingObject_Destructor_2  (= the destructor 0x5c6df0, CKHkMovingObject.h)
//   [x] 0x5c7500  CKHkMovingObject_DeletingDestructor  (= the destructor 0x5c6df0, then delete)
//   [x] 0x5c7570  CKHkMovingObject_RestoreState_maybe
//   [x] 0x5c7738  CKHkMovingObject_RestoreState_maybe
//   [x] 0x5c7740  CKHkMovingObject_ReinitRuntime
//   [x] 0x5c7758  CKHkMovingObject_HandleMessage
//
//   [ ] 0x9cd508  CKHkMovingObject_IsKindOf  [inline]
//   [ ] 0x9cd550  CKHkMovingObject_GetClassGroup  [inline]
//   [ ] 0x9cd558  CKHkMovingObject_GetClassId  [inline]
#include "k2000/ui/CKHkMovingObject.h"

#include <cstring>

#include "Renderware/rwcore/RwMatrix.h"
#include "k2000/components/CKGroundCpnt.h"
#include "k2000/components/CKMoveCpntUpdater.h"
#include "k2000/dictionaries/CKSoundDictionaryID.h"
#include "k2000/io/IKFile.h"
#include "k2000/logic/CKMoveCpnt.h"
#include "k2000/logic/sound/CKSound.h"
#include "k2000/scenegraph/CSGLeaf.h"
#include "k2000/services/CKSrvTrigger.h"
#include "k2000/system/IKTime.h"
#include "k2000/memory/Mem.h"
#include "k2000/misc/Mat4.h"

// 0x005c6e58 CKHkMovingObject_Load
int32_t CKHkMovingObject::Load(IKFile* file, int32_t type) {
    IKHook::Load(file, type);  // through TocBridge_CKHook_Load
    if (type != K_LEVEL_PLATEFORMS) return 1;
    m_pMatrix = RwMatrixCreate_Thunk();
    CMatrix34_LoadMatrix(m_pMatrix, file);
    IKFile_ReadRef(file, &m_pUnk24);
    ReadU8(file, &m_unk28);
    ReadU8(file, &m_unk29);
    uint32_t count = 0;
    ReadU32LE(file, &count);
    // The vector reserve the Load inlines: capacity = count, then the block; the grow branch after it
    // cannot run (kept as in the original).
    m_vpSteps.m_ui32NbElt = count;
    m_vpSteps.m_pBlock = static_cast<Step**>(Mem_AllocAligned16(count * static_cast<uint32_t>(sizeof(Step*))));
    if (m_vpSteps.m_ui32NbElt < count) {
        uint32_t capacity = count + 1;
        if (capacity == 0) capacity = 1;
        m_vpSteps.m_pBlock = static_cast<Step**>(
            Mem_ReallocAligned16(m_vpSteps.m_pBlock, capacity * static_cast<uint32_t>(sizeof(Step*))));
        m_vpSteps.m_ui32NbElt = capacity;
    }
    m_vpSteps.m_ui32NbUsedElt = count;
    for (uint32_t i = 0; i < count; ++i) {
        Step* step = new Step;  // OperatorNew(0x44), no constructor
        m_vpSteps.m_pBlock[i] = step;
        IKFile_ReadRef(file, &step->m_pUnk4);
        IKFile_ReadRef(file, &step->m_pUnk0);
        ReadU8(file, &step->m_unk8);
        ReadF32LE(file, &step->m_unkC);
        ReadU8(file, &step->m_unk10);
        ReadF32LE(file, &step->m_unk14);
        IKFile_ReadRef(file, &step->m_pUnk18);
        ReadU32LE(file, &step->m_unk1C);
        ReadU32LE(file, &step->m_unk20);
        uint32_t dropped = 0;  // read and swapped into a stack word, never stored
        ReadU32LE(file, &dropped);
        step->m_tsUnk28.Load(file, 0);
        step->m_tsUnk30.Load(file, 0);
        IKFile_ReadRef(file, &step->m_pUnk38);
    }
    return 1;
}

// 0x005c6360 CKHkMovingObject_SetDefaultState (the flag is not used)
void CKHkMovingObject::SetDefaultState(int32_t /*flag*/) {
    m_unk2A = m_unk28;
    for (uint32_t i = 0; i < m_vpSteps.m_ui32NbUsedElt; ++i) {
        Step* step = m_vpSteps.m_pBlock[i];
        step->m_unk3C = step->m_unk8;
        step->m_unk40 = step->m_unkC;
    }
}

// 0x005c6278 CKHkMovingObject_RestoreCheckpointState_maybe
int32_t CKHkMovingObject::RestoreCheckpointState(uint32_t stateIdForLeft) {
    if (stateIdForLeft == 0) {
        m_unk2A = m_unk28;
        for (uint32_t i = 0; i < m_vpSteps.m_ui32NbUsedElt; ++i) {
            Step* step = m_vpSteps.m_pBlock[i];
            step->m_unk3C = step->m_unk8;
            step->m_unk40 = step->m_unkC;
        }
    } else {
        m_unk2A = m_unk29;
        for (uint32_t i = 0; i < m_vpSteps.m_ui32NbUsedElt; ++i) {
            Step* step = m_vpSteps.m_pBlock[i];
            step->m_unk3C = step->m_unk10;
            step->m_unk40 = step->m_unk14;
        }
    }
    return 1;
}

namespace {

CKMoveCpntUpdater* UpdaterOf(const CKHkMovingObject::Step* step) { return reinterpret_cast<CKMoveCpntUpdater*>(step->m_pUnk0); }
CKMoveCpnt* MoveOf(const CKHkMovingObject::Step* step) { return reinterpret_cast<CKMoveCpnt*>(step->m_pUnk4); }
// The step's sound `index` (CKSoundDictionaryID_GetSound_2 0x112bd8: no range check).
CKSound* SoundOf(const CKHkMovingObject::Step* step, uint32_t index) {
    return static_cast<CKSoundDictionaryID*>(step->m_pUnk38)->GetSound2(index);
}
uint32_t StepIndexOf(const void* data) {
    uint32_t index;
    std::memcpy(&index, &static_cast<const CTriggerAction*>(data)->m_mdParam, sizeof index);
    return index;
}

}  // namespace

// 0x005c5c38 CKHkMovingObject_StartMove_maybe
void CKHkMovingObject::StartMove(uint32_t index) {
    Step* step = m_vpSteps.m_pBlock[index];
    UpdaterOf(step)->Start();  // 0x0024dc98
    step->m_unk3C = 1;
    QueueTriggerSignals(&step->m_tsUnk28);  // 0x00236338
    if (step->m_pUnk18 != nullptr) return;
    if (SoundOf(step, 0) != nullptr) SoundOf(step, 0)->Play(0.0f);
    if (SoundOf(step, 1) != nullptr) SoundOf(step, 1)->SetLoop(1);
    if (SoundOf(step, 1) != nullptr) SoundOf(step, 1)->Play(0.0f);
}

// 0x005c5b78 CKHkMovingObject_StopMover_maybe
void CKHkMovingObject::StopMover(uint32_t index) {
    Step* step = m_vpSteps.m_pBlock[index];
    UpdaterOf(step)->Stop();  // 0x0024dc60
    step->m_unk3C = 0;
    if (SoundOf(step, 1) != nullptr) SoundOf(step, 1)->Stop(0);
}

// 0x005c6588 CKHkMovingObject_SetMoveProgress_maybe
void CKHkMovingObject::SetMoveProgress(float progress, uint32_t index) {
    Step* step = m_vpSteps.m_pBlock[index];
    step->m_unk40 = progress;
    CKMoveCpntUpdater* updater = UpdaterOf(step);
    updater->m_fTime = MoveOf(step)->m_unk04 * step->m_unk40;
    updater->m_pMoveCpnt->ResetTrackTime();  // 0x0024d2a8, 0x0024c400
    if (1.0f <= progress && SoundOf(step, 1) != nullptr) SoundOf(step, 1)->Stop(0);
}

// 0x005c7570 CKHkMovingObject_RestoreState_maybe
void CKHkMovingObject::RestoreState() {
    CSGLeaf* node = static_cast<CSGLeaf*>(m_pKGLObject);
    node->SetLocalMatrix(reinterpret_cast<const RwMatrix*>(m_pMatrix));  // 0x000d0be8
    node->m_sgProperties = (node->m_sgProperties & 0xfffffffbu) | (static_cast<uint32_t>(m_unk2A ^ 1u) << 2);
    static_cast<CKGroundCpnt*>(m_pUnk24)->SetActive(m_unk2A);  // 0x001910a8
    for (uint32_t i = 0; i < m_vpSteps.m_ui32NbUsedElt; ++i) {
        Step* step = m_vpSteps.m_pBlock[i];
        if (step->m_unk3C != 0) {
            StartMove(i);
            SetMoveProgress(m_vpSteps.m_pBlock[i]->m_unk40, i);
            continue;
        }
        UpdaterOf(step)->Stop();
        step->m_unk3C = 0;
        if (SoundOf(step, 1) != nullptr) SoundOf(step, 1)->Stop(0);
    }
}

// 0x005c7740 CKHkMovingObject_ReinitRuntime
void CKHkMovingObject::Restart() {
    if ((m_bitArray & 4u) != 0) return;
    RestoreState();
}

// 0x005c7738 (SectorNowValid)
void CKHkMovingObject::VfA0() { RestoreState(); }

// 0x005c5ff0 CKHkMovingObject_OnDeactivate (SectorNowInvalid): the node at its matrix and shown, the sounds stopped.
void CKHkMovingObject::VfA4() {
    CSGLeaf* node = static_cast<CSGLeaf*>(m_pKGLObject);
    node->SetLocalMatrix(reinterpret_cast<const RwMatrix*>(m_pMatrix));
    node->m_sgProperties &= 0xfffffffbu;
    for (uint32_t i = 0; i < m_vpSteps.m_ui32NbUsedElt; ++i) {
        const Step* step = m_vpSteps.m_pBlock[i];
        for (uint32_t k = 0; k < 3; ++k) {
            if (SoundOf(step, k) != nullptr) SoundOf(step, k)->Stop(0);
        }
    }
}

// 0x005c7758 CKHkMovingObject_MessageProc
int32_t CKHkMovingObject::MessageProc(uint16_t message, void* data) {
    switch (message) {
    case 0x496: {
        const uint32_t index = StepIndexOf(data);
        if (UpdaterOf(m_vpSteps.m_pBlock[index])->m_bRunning == 0) StartMove(index);
        return 0;
    }
    case 0x497: {
        Step* step = m_vpSteps.m_pBlock[StepIndexOf(data)];
        UpdaterOf(step)->Stop();  // 0x0024dc60
        step->m_unk3C = 0;
        if (SoundOf(step, 1) != nullptr) SoundOf(step, 1)->Stop(0);
        return 0;
    }
    case 0x498:
        UpdaterOf(m_vpSteps.m_pBlock[StepIndexOf(data)])->Pause();  // 0x0024dc28
        return 0;
    case 0x499:
        UpdaterOf(m_vpSteps.m_pBlock[StepIndexOf(data)])->Resume();  // 0x0024dbf0
        return 0;
    case 0x49a: {
        Step* step = m_vpSteps.m_pBlock[StepIndexOf(data)];
        CKMoveCpntUpdater* updater = UpdaterOf(step);
        updater->m_fTime = MoveOf(step)->m_unk04;
        updater->m_pMoveCpnt->ResetTrackTime();  // 0x0024d2a8, 0x0024c400
        return 0;
    }
    case 0x49b: {
        CSGLeaf* node = static_cast<CSGLeaf*>(m_pKGLObject);
        node->m_sgProperties = (node->m_sgProperties & 0xfffffffbu) | 4u;
        static_cast<CKGroundCpnt*>(m_pUnk24)->SetActive(0);
        m_unk2A = 0;
        return 0;
    }
    case 0x49c: {
        CSGLeaf* node = static_cast<CSGLeaf*>(m_pKGLObject);
        node->m_sgProperties &= 0xfffffffbu;
        static_cast<CKGroundCpnt*>(m_pUnk24)->SetActive(1);
        m_unk2A = 1;
        return 0;
    }
    default:
        return 1;
    }
}

// 0x005c6c60 CKHkMovingObject_PostLoad
int32_t CKHkMovingObject::PostLoad(int32_t type) {
    PostLoadLife(type);  // IKLife_PostLoad 0x19f68
    if (type != K_LEVEL_PLATEFORMS) return 1;
    for (uint32_t i = 0; i < m_vpSteps.m_ui32NbUsedElt; ++i) {
        Step* step = m_vpSteps.m_pBlock[i];
        if (step->m_pUnk18 != nullptr) {
            IKInfo info;
            info.m_ui32Id = step->m_unk20;
            step->m_pUnk18->GetInfo(&info, kGetInfoValueAccessor);  // vt+0x40
            step->m_pfnValue = info.m_pfnAccessor;
            step->m_unk24 = 0;
        }
        step->m_unk3C = 0;
        step->m_unk40 = 0.0f;
    }
    m_unk2A = 1;
    return 1;
}

// 0x005c6190 CKHkMovingObject_vf40 (GetInfo), with 0x5c5a10 IsTrackAtStart, 0x5c5a48 IsTrackAtEnd, 0x5c63c8
// IsTrackBetweenEnds and 0x5c5fd8 IsVisible.
int32_t CKHkMovingObject::GetInfo(IKInfo* info, int32_t request) {
    if (request != kGetInfoValueAccessor) return 1;
    switch (info->m_ui32Id) {
    case 300:
        return AnswerInfo(info, [](IKSerializable* o, uint32_t index) {
            const Step* step = static_cast<CKHkMovingObject*>(o)->m_vpSteps.m_pBlock[index];
            return static_cast<uint32_t>(UpdaterOf(step)->m_fTime == 0.0f);
        }, 0);
    case 0x12d:
        return AnswerInfo(info, [](IKSerializable* o, uint32_t index) {
            const Step* step = static_cast<CKHkMovingObject*>(o)->m_vpSteps.m_pBlock[index];
            return static_cast<uint32_t>(UpdaterOf(step)->m_fTime == MoveOf(step)->m_unk04);
        }, 0);
    case 0x12e:
        return AnswerInfo(info, [](IKSerializable* o, uint32_t index) {
            const Step* step = static_cast<CKHkMovingObject*>(o)->m_vpSteps.m_pBlock[index];
            const float time = UpdaterOf(step)->m_fTime;
            return static_cast<uint32_t>(time != 0.0f && time != MoveOf(step)->m_unk04);
        }, 0);
    case 0x12f:
        return AnswerInfo(info, [](IKSerializable* o, uint32_t) {
            const CSGLeaf* node = static_cast<const CSGLeaf*>(static_cast<CKHkMovingObject*>(o)->m_pKGLObject);
            return ((node->m_sgProperties ^ 4u) >> 2) & 1u;
        }, 0);
    default:
        return 1;
    }
}

// 0x005c6688 CKHkMovingObject_Update
void CKHkMovingObject::Update(IKTime* frameClock) {
    CSGLeaf* node = static_cast<CSGLeaf*>(m_pKGLObject);
    node->SetLocalMatrix(reinterpret_cast<const RwMatrix*>(m_pMatrix));  // 0x000d0be8
    const float dt = frameClock->m_afDeltaTime[0];
    for (uint32_t i = 0; i < m_vpSteps.m_ui32NbUsedElt; ++i) {
        Step* step = m_vpSteps.m_pBlock[i];
        CKMoveCpntUpdater* updater = UpdaterOf(step);
        const float before = updater->m_fTime;
        float sample[10];
        uint32_t ended = 0;
        if (step->m_pUnk18 == nullptr) {
            if (updater->m_bRunning != 0) {
                ended = updater->Evaluate(dt, sample);  // 0x0024db60
                if (MoveOf(step)->m_unk08 != 0) ended = 0;  // a looping movement never ends
                updater->ApplyToNode(sample, node);  // 0x0024d9c0
            }
        } else {
            const uint32_t bits = step->m_pfnValue(step->m_pUnk18, step->m_unk1C);
            float value;
            std::memcpy(&value, &bits, sizeof value);
            double clamped = 0.0;
            if (0.0 < static_cast<double>(value)) clamped = static_cast<double>(value) < 1.0 ? static_cast<double>(value) : 1.0;
            const float time = static_cast<float>(clamped * static_cast<double>(MoveOf(step)->m_unk04));
            ended = updater->SampleMoveCpnt(time, sample);  // 0x0024dad0
            updater->ApplyToNode(sample, node);
            if (before == 0.0f && 0.0f < time && SoundOf(step, 0) != nullptr) SoundOf(step, 0)->Play(0.0f);
            if (before == time) {
                if (SoundOf(step, 1) != nullptr && SoundOf(step, 1)->IsPlaying() != 0 && SoundOf(step, 1) != nullptr) {
                    SoundOf(step, 1)->Stop(0);
                }
            } else if (SoundOf(step, 1) != nullptr && SoundOf(step, 1)->IsPlaying() == 0) {
                if (SoundOf(step, 1) != nullptr) SoundOf(step, 1)->SetLoop(1);
                if (SoundOf(step, 1) != nullptr) SoundOf(step, 1)->Play(0.0f);
            }
        }
        step = m_vpSteps.m_pBlock[i];
        step->m_unk40 = UpdaterOf(step)->m_fTime / MoveOf(step)->m_unk04;
        step->m_unk3C = UpdaterOf(step)->m_bRunning;
        if ((ended & 0xffu) != 0) {
            QueueTriggerSignals(&step->m_tsUnk30);
            if (SoundOf(step, 2) != nullptr) SoundOf(step, 2)->Play(0.0f);
            if (SoundOf(step, 1) != nullptr) SoundOf(step, 1)->Stop(0);
        }
    }
}

// 0x005c5ef8 CKHkMovingObject_Destroy
void CKHkMovingObject::Destroy() {
    if (m_pMatrix != nullptr) {
        RwMatrixDestroy_Thunk(m_pMatrix);
        m_pMatrix = nullptr;
    }
    for (uint32_t i = m_vpSteps.m_ui32NbUsedElt; i != 0; --i) {
        if (m_vpSteps.m_pBlock[i - 1] != nullptr) delete m_vpSteps.m_pBlock[i - 1];  // OperatorDelete
    }
    if (m_vpSteps.m_pBlock != nullptr) Mem_FreeAligned16(m_vpSteps.m_pBlock);
    m_vpSteps.m_ui32NbUsedElt = 0;
    m_vpSteps.m_pBlock = nullptr;
}
