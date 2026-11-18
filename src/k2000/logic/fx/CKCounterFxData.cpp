// CKCounterFxData.cpp - reconstructed original translation unit 0x5748c0-0x575810 (GAME_TOC2, main_toc2), 26 functions, 22 live.
// Primary class: CKCounterFxData  key 0x58cc  category Logic  size 0x4c  vtable 0xb2df38
// Other owners: CKCounterNodeFx (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x5748c0  CKCounterFxData_Delete  (DOTD_DECLARE_FACTORIES)
//   [x] 0x574910  CKCounterFxData_GetNodeClassKey  (CKCounterFxData.h)
//   [ ] 0x574918  CKCounterFxData_SetValueToMax_maybe  [dead]
//   [x] 0x574928  CKCounterNodeFx_SetValueClamped_maybe  (CKCounterFxData::SetValueClamped; also inlined in MessageProc)
//   [x] 0x574978  CKCounterFxData_AcquireNode_maybe
//   [ ] 0x574bd0  RegisterCKCounterFxDataClass
//   [ ] 0x574c48  _GLOBAL__I_574c48
//   [x] 0x574c58  CKCounterFxData_ResetNode_maybe
//   [ ] 0x574c90  CKCounterFxData_DecrementValue_maybe  [dead]
//   [ ] 0x574ce8  CKCounterFxData_IncrementValue_maybe  [dead]
//   [x] 0x574d48  CKCounterFxData_ReleaseNode_maybe
//   [ ] 0x574d98  CKCounterFxData_Save
//   [x] 0x574dc0  CKCounterFxData_RecursiveRegistration  (IKFxData's, the default)
//   [x] 0x574de8  CKCounterFxData_Construct_2_maybe  (the constructor)
//   [x] 0x574e48  CKCounterFxData_DeleteArray  (DOTD_DECLARE_FACTORIES)
//   [ ] 0x574ee8  FUN_00574ee8  [dead]
//   [x] 0x574f28  CKCounterFxData_GetInfo  (returns 1: the default)
//   [x] 0x574f30  CKCounterFxData_Destroy  (empty: CKCounterFxData.h)
//   [x] 0x574f38  CKCounterFxData_DeletingDestructor  (the destructor; delete)
//   [x] 0x574fb0  CKCounterFxData_Construct_maybe  (the constructor)
//   [x] 0x575010  CKCounterFxData_MessageProc
//   [x] 0x575240  CKCounterFxData_CreateArray  (DOTD_DECLARE_FACTORIES; the constructor)
//   [x] 0x575340  CKCounterFxData_Create  (DOTD_DECLARE_FACTORIES; the constructor)
//   [x] 0x5753c0  CKCounterFxData_Destructor
//   [x] 0x575428  CKCounterFxData_BaseDestructor  (the same as 0x5753c0)
//   [x] 0x575490  CKCounterFxData_Load
//
//   [x] 0x9cae68  CKCounterFxData_IsKindOfClass  [inline]  (CKCounterFxData.h)
//   [x] 0x9caea0  CKCounterFxData_GetClassType  [inline]  (DOTD_CLASS_KEY)
//   [x] 0x9caea8  CKCounterFxData_GetClassID  [inline]  (DOTD_CLASS_KEY)
//
// C2.8 port-final F04: CKCounterFxData (0x58cc) and CKCounterNodeFx (0x590c) are in no level file of the game; ported
// from the disassembly (port-rest R06's analysis).
#include "k2000/logic/fx/CKCounterFxData.h"

#include <cstring>

#include "k2000/fx/IKFx.h"
#include "k2000/io/IKFile.h"
#include "k2000/logic/fx/CKCounterNodeFx.h"
#include "k2000/memory/Mem.h"
#include "k2000/misc/Engine.h"
#include "k2000/services/CKSrvFx.h"

namespace {
constexpr float kZero = 0.0f;  // TOC2 -0x7560
}  // namespace

CKCounterFxData::CKCounterFxData() {
    m_colorKeys.m_pBlock = nullptr;
    m_colorKeys.m_ui32NbElt = 20;
    m_colorKeys.m_ui32NbUsedElt = 0;
    m_colorKeys.m_pBlock = static_cast<CurveKey*>(Mem_AllocAligned16(20 * static_cast<uint32_t>(sizeof(CurveKey))));
}

CKCounterFxData::~CKCounterFxData() {
    if (m_colorKeys.m_pBlock != nullptr) Mem_FreeAligned16(m_colorKeys.m_pBlock);
}

// 0x00575490 CKCounterFxData_Load: IKFxData's; level files: the target reference, the position (one 12-byte read), the
// maximum, the fade times, the height, the colour keys, the scale, the distance range and the flags byte; the value
// starts at the maximum. Any type: no node.
int32_t CKCounterFxData::Load(IKFile* file, int32_t type) {
    IKFxData::Load(file, type);
    if (type == K_LEVEL_PLATEFORMS) {
        IKFile_ReadRef(file, &m_pTarget);
        uint32_t position[3];
        ReadU32LEWords(file, position, 3);
        std::memcpy(&m_vPosition, position, sizeof(position));
        ReadF32LE(file, &m_fMaxValue);
        ReadF32LE(file, &m_fFadeInTime);
        ReadF32LE(file, &m_fFadeOutTime);
        ReadF32LE(file, &m_fHeight);
        CurveKeys_Load(&m_colorKeys, file);  // 0x002469b8
        ReadF32LE(file, &m_fScale);
        ReadF32LE(file, &m_fMinDistance);
        ReadF32LE(file, &m_fMaxDistance);
        ReadU8(file, &m_flags);
        m_fValue = m_fMaxValue;
    }
    m_pNode = nullptr;
    return 1;
}

// 0x00574978 CKCounterFxData_AcquireNode_maybe
void CKCounterFxData::AcquireNode() {
    m_pNode = static_cast<CKCounterNodeFx*>(static_cast<CKSrvFx*>(g_pEngine->m_srvFx)->AcquireFx(this, this));
}

// 0x00574928 CKCounterNodeFx_SetValueClamped_maybe: below 0 counts as 0 for the test; not below the maximum (or NaN):
// the maximum.
void CKCounterFxData::SetValueClamped(float value) {
    const float floored = value < kZero ? kZero : value;
    float result = m_fMaxValue;
    if (floored < m_fMaxValue) result = value < kZero ? floored : value;
    m_fValue = result;
}

// 0x00574c58 CKCounterFxData_ResetNode_maybe
void CKCounterFxData::ResetNode() {
    if (m_pNode != nullptr) m_pNode->ResetDisplay();
}

// 0x00574d48 CKCounterFxData_ReleaseNode_maybe
void CKCounterFxData::ReleaseNode() {
    if (m_pNode == nullptr) return;
    m_pNode->EnterFadeOut(this);
    m_pNode = nullptr;
}

// 0x00575010 CKCounterFxData_MessageProc (jump table at TOC2 -0x752c, 0x575054): 0x1b00 the counter at the sent object's
// +0x04 position (the data a pointer to it), 0x1b01 over the sent object (the target): both restart at the maximum with a
// new node (none without an object); 0x1b02 the value set clamped; 0x1b03 / 0x1b04 (with a node) the value raised to
// at most the maximum / lowered to at least 0, then the pulse restarted; 0x1b05 the node released; 0x1b06 (with a node)
// the value the maximum. These return 0, the rest 1.
int32_t CKCounterFxData::MessageProc(uint16_t message, void* data) {
    const uint32_t index = static_cast<uint16_t>(message - 0x1b00);
    if (index > 6) return 1;
    switch (index) {
    case 0: {
        IKSerializable* object = nullptr;
        std::memcpy(&object, data, sizeof(object));
        m_fValue = m_fMaxValue;
        m_pNode = nullptr;
        if (object == nullptr) return 0;
        // The object's three words at +0x04 (its class is not known; the sender's layout as the PS3 reads it).
        const uint8_t* bytes = reinterpret_cast<const uint8_t*>(object);
        std::memcpy(&m_vPosition, bytes + 0x04, sizeof(m_vPosition));
        AcquireNode();
        return 0;
    }
    case 1: {
        IKSerializable* object = nullptr;
        std::memcpy(&object, data, sizeof(object));
        m_fValue = m_fMaxValue;
        m_pNode = nullptr;
        if (object == nullptr) return 0;
        m_pTarget = object;
        AcquireNode();
        return 0;
    }
    case 2: {
        float value;
        std::memcpy(&value, data, sizeof(value));
        SetValueClamped(value);
        return 0;
    }
    case 3: {
        float add;
        std::memcpy(&add, data, sizeof(add));
        if (m_pNode == nullptr) return 0;
        float value = add + m_fValue;
        m_fValue = value;
        if (!(value < m_fMaxValue)) value = m_fMaxValue;  // blt: a NaN takes the maximum
        m_fValue = value;
        m_pNode->ResetDisplay();
        return 0;
    }
    case 4: {
        float sub;
        std::memcpy(&sub, data, sizeof(sub));
        if (m_pNode == nullptr) return 0;
        float value = m_fValue - sub;
        if (value < kZero) value = kZero;
        m_fValue = value;
        m_pNode->ResetDisplay();
        return 0;
    }
    case 5:
        ReleaseNode();
        return 0;
    default:  // 6
        if (m_pNode == nullptr) return 0;
        m_fValue = m_fMaxValue;
        return 0;
    }
}
