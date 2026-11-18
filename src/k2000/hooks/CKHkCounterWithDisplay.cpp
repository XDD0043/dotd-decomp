// Reconstructed original translation unit: 0x4472f0-0x447fc0 (GAME_TOC1, main_toc1), 31 functions, 27 live.
// Primary class: CKHkCounterWithDisplay  key 0x1f82  category Hook  size 0x34  vtable 0xb26ac8
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x4472f0  CKHkCounterWithDisplay_Delete  (the factory Delete, DOTD_DECLARE_FACTORIES)
//   [x] 0x447340  CKHkCounterWithDisplay_SetDefaultState  (header)
//   [x] 0x447348  CKHkCounterWithDisplay_SetGameState  (header)
//   [ ] 0x447350  RegisterCKHkCounterWithDisplayClass
//   [ ] 0x4473c8  _GLOBAL__I_4473c8
//   [x] 0x4473d8  CKHkCounterWithDisplay_ResetCounter_maybe  (no caller: only its OPD)
//   [ ] 0x447448  CKHkCounterWithDisplay_ResetFxNode_maybe  [dead]
//   [ ] 0x447470  CKHkCounterWithDisplay_SetDisplayVisible_maybe  [dead]
//   [x] 0x447550  CKHkCounterWithDisplay_GetInfo
//   [x] 0x4475a0  CKHkCounterWithDisplay_OnDeactivate  (the actor base's 0x3f7370: inherited)
//   [x] 0x4475c8  CKHkCounterWithDisplay_OnActivate  (the actor base's 0x3f7338: inherited)
//   [x] 0x4475f0  CKHkCounterWithDisplay_Resume  (the actor base's 0x3f6e60: inherited)
//   [x] 0x447618  CKHkCounterWithDisplay_Pause  (the actor base's 0x3f6e58: inherited)
//   [x] 0x447640  CKHkCounterWithDisplay_Stop  (the display call: a STUB until R06's CKCounterFxData lands)
//   [x] 0x447690  CKHkCounterWithDisplay_PostLoad  (the actor base's 0x3f6e70: inherited)
//   [ ] 0x4476b8  CKHkCounterWithDisplay_Save
//   [x] 0x4476e0  CKHkCounterWithDisplay_RecursiveRegistration  (the actor base's 0x3f6ee8: inherited)
//   [x] 0x447708  CKHkCounterWithDisplay_Destroy  (the actor base's 0x3f6e08: inherited)
//   [x] 0x447730  CKHkCounterWithDisplay_DeletingDestructor  (the header's destructor)
//   [x] 0x447778  CKHkCounterWithDisplay_Destructor  (the header's destructor)
//   [x] 0x4477a8  CKHkCounterWithDisplay_BaseDestructor  (the header's destructor)
//   [ ] 0x4477d8  CKHkCounterWithDisplay_Construct  [dead]
//   [ ] 0x447818  CKHkCounterWithDisplay_Construct_2  [dead]
//   [x] 0x447858  CKHkCounterWithDisplay_DeleteArray  (DOTD_DECLARE_FACTORIES)
//   [x] 0x4478f8  CKHkCounterWithDisplay_Update  (the display calls: STUBs until R06's CKCounterFxData lands)
//   [x] 0x4479c8  CKHkCounterWithDisplay_CreateArray  (DOTD_DECLARE_FACTORIES)
//   [x] 0x447a88  CKHkCounterWithDisplay_Create  (the constructor)
//   [x] 0x447ae8  CKHkCounterWithDisplay_Load
//   [x] 0x447ca8  CKHkCounterWithDisplay_Start  (the display's maximum: a STUB until R06's class lands)
//   [x] 0x447db0  CKHkCounterWithDisplay_Restart  (the display call: a STUB until R06's class lands)
//   [x] 0x447e70  CKHkCounterWithDisplay_MessageProc  (the display calls: STUBs until R06's class lands)
//
//   [ ] 0x9c3b48  CKHkCounterWithDisplay_IsKindOfClass  [inline]
//   [ ] 0x9c3ba0  CKHkCounterWithDisplay_GetClassType  [inline]
//   [ ] 0x9c3ba8  CKHkCounterWithDisplay_GetClassID  [inline]
#include "k2000/hooks/CKHkCounterWithDisplay.h"

#include "k2000/core/Stub.h"
#include "k2000/io/IKFile.h"
#include "k2000/logic/CKIntegerCounter.h"
#include "k2000/logic/system/CKTimeCounter.h"

namespace {

CKTimeCounter* TimeCounter(IKSerializable* c) { return static_cast<CKTimeCounter*>(c); }
CKIntegerCounter* IntegerCounter(IKSerializable* c) { return static_cast<CKIntegerCounter*>(c); }

// An integer counter's word as a float: lwz (zero-extended), fcfid, frsp.
float WordAsFloat(int32_t value) { return static_cast<float>(static_cast<double>(static_cast<uint32_t>(value))); }

// ---- the display (+0x24, a CKCounterFxData): R06's class ----
// STUB(port-rest R06): CKCounterFxData.cpp / CKCounterNodeFx.cpp (R06) are not ported; these call sites wait for them.
// The display's node (+0x1c) is there.
bool DisplayHasNode(IKSerializable* /*display*/) {
    DOTD_STUB_ONCE("CKHkCounterWithDisplay: the display's node +0x1c (R06's CKCounterFxData)");
    return false;
}
// 0x0098f5a0 TocBridge_CKCounterFxData_AcquireNode_maybe (0x574978).
void DisplayAcquireNode(IKSerializable* /*display*/) {
    DOTD_STUB_ONCE("CKCounterFxData_AcquireNode_maybe 0x574978 (R06's CKCounterFxData)");
}
// 0x0098f590 TocBridge_CKCounterFxData_ReleaseNode_maybe (0x574d48).
void DisplayReleaseNode(IKSerializable* /*display*/) {
    DOTD_STUB_ONCE("CKCounterFxData_ReleaseNode_maybe 0x574d48 (R06's CKCounterFxData)");
}
// 0x0098f580 TocBridge_CKCounterFxData_ResetNode_maybe (0x574c58).
void DisplayResetNode(IKSerializable* /*display*/) {
    DOTD_STUB_ONCE("CKCounterFxData_ResetNode_maybe 0x574c58 (R06's CKCounterFxData)");
}
// 0x0098f5b0 TocBridge_CKCounterNodeFx_SetValueClamped_maybe (0x574928).
void DisplaySetValue(IKSerializable* /*display*/, float /*value*/) {
    DOTD_STUB_ONCE("CKCounterNodeFx_SetValueClamped_maybe 0x574928 (R06's CKCounterFxData)");
}
// The display's maximum (its float +0x3c; Start stores it).
void DisplaySetMaximum(IKSerializable* /*display*/, float /*maximum*/) {
    DOTD_STUB_ONCE("CKHkCounterWithDisplay_Start 0x447ca8: the display's maximum +0x3c (R06's CKCounterFxData)");
}

}  // namespace

CKHkCounterWithDisplay::CKHkCounterWithDisplay() {
    m_ui32Priority = 0xffffffffu;
    // Not set by Create (the fresh heap's zeros).
    m_pUnk20 = nullptr;
    m_pUnk24 = nullptr;
    m_i32Type = 0;
    m_fUnk2C = 0.0f;
    m_unk30 = 0;
}

// 0x004473d8 CKHkCounterWithDisplay_ResetCounter_maybe
void CKHkCounterWithDisplay::ResetCounter() {
    if (m_i32Type == 0) {
        TimeCounter(m_pUnk20)->Reset();  // 0x00200988
    } else if (m_i32Type == 1) {
        IntegerCounter(m_pUnk20)->Reset();  // 0x001ffcc0
    }
}

// 0x00447550 CKHkCounterWithDisplay_GetInfo
int32_t CKHkCounterWithDisplay::GetInfo(IKInfo* info, int32_t request) {
    const int32_t base = CKHkActorBase::GetInfo(info, request);  // KStub_Return1 0x3f7140
    if (base == 2) return 2;
    return base == 0 ? 0 : 1;
}

// 0x00447640 CKHkCounterWithDisplay_Stop
void CKHkCounterWithDisplay::Stop() {
    CKHkActorBase::Stop();  // 0x003f6e50
    if (DisplayHasNode(m_pUnk24)) DisplayReleaseNode(m_pUnk24);  // 0x0098f590
}

// 0x004478f8 CKHkCounterWithDisplay_Update
void CKHkCounterWithDisplay::Update(IKTime* clock) {
    CKHkActorBase::Update(clock);  // 0x003f6e68 (empty)
    // BUG(original): for a type other than 0 / 1 the value is f31 as the caller left it; 0 here.
    float value = 0.0f;
    if (m_i32Type == 0) {
        value = TimeCounter(m_pUnk20)->m_fCurrentValue;
    } else if (m_i32Type == 1) {
        value = WordAsFloat(IntegerCounter(m_pUnk20)->m_i32CurrentValue);
    }
    DisplaySetValue(m_pUnk24, value);  // 0x0098f5b0
    if (m_fUnk2C == value) return;  // fcmpu / beq: a NaN goes on
    if (m_i32Type != 1) return;
    DisplayResetNode(m_pUnk24);  // 0x0098f580
    m_fUnk2C = value;
}

// 0x00447ae8 CKHkCounterWithDisplay_Load: the actor base's, then for the level type the counter and the display, the
// type (swapped) and the byte +0x30.
int32_t CKHkCounterWithDisplay::Load(IKFile* file, int32_t type) {
    CKHkActorBase::Load(file, type);  // 0x003f6e98
    if (type != K_LEVEL_PLATEFORMS) return 1;
    IKFile_ReadRef(file, &m_pUnk20);
    IKFile_ReadRef(file, &m_pUnk24);
    ReadS32LE(file, &m_i32Type);
    ReadU8(file, &m_unk30);
    return 1;
}

// 0x00447ca8 CKHkCounterWithDisplay_Start
void CKHkCounterWithDisplay::Start() {
    CKHkActorBase::Start();  // 0x003f6e48 (empty)
    // BUG(original): for a type other than 0 / 1 the maximum is f31 as the caller left it; 0 here.
    float maximum = 0.0f;
    if (m_i32Type == 0) {
        m_fUnk2C = TimeCounter(m_pUnk20)->m_fCurrentValue;
        maximum = TimeCounter(m_pUnk20)->m_fMaxValue;
    } else if (m_i32Type == 1) {
        m_fUnk2C = WordAsFloat(IntegerCounter(m_pUnk20)->m_i32CurrentValue);
        maximum = WordAsFloat(IntegerCounter(m_pUnk20)->m_i32MaxValue);
    }
    DisplaySetMaximum(m_pUnk24, maximum);  // the display's +0x3c
    if (m_i32Type == 0) {
        TimeCounter(m_pUnk20)->Reset();  // 0x00200988
    } else if (m_i32Type == 1) {
        IntegerCounter(m_pUnk20)->Reset();  // 0x001ffcc0
    }
}

// 0x00447db0 CKHkCounterWithDisplay_Restart
void CKHkCounterWithDisplay::Restart() {
    if (m_i32Type == 0) {
        m_fUnk2C = TimeCounter(m_pUnk20)->m_fCurrentValue;
    } else if (m_i32Type == 1) {
        m_fUnk2C = WordAsFloat(IntegerCounter(m_pUnk20)->m_i32CurrentValue);
    }
    if (DisplayHasNode(m_pUnk24)) DisplayReleaseNode(m_pUnk24);  // 0x0098f590
    if (m_i32Type == 0) TimeCounter(m_pUnk20)->m_baFlags &= 0xfffffffeu;  // stopped
}

// 0x00447e70 CKHkCounterWithDisplay_MessageProc: the actor messages (asked twice, the first answer dropped), then 0x996
// (the display shown: its node acquired when it has none; a time counter runs, +0x1c bit 0) and 0x997 (its node
// released; a time counter stops). BUG(original)?: the answer is the actor base's only (1 for 0x996 / 0x997).
int32_t CKHkCounterWithDisplay::MessageProc(uint16_t message, void* data) {
    CKHkActorBase::MessageProc(message, data);  // 0x003f7148 (the answer unused)
    const int32_t base = CKHkActorBase::MessageProc(message, data);
    if (message == 0x996) {
        if (!DisplayHasNode(m_pUnk24)) DisplayAcquireNode(m_pUnk24);  // 0x0098f5a0
        if (m_i32Type == 0) TimeCounter(m_pUnk20)->m_baFlags = (TimeCounter(m_pUnk20)->m_baFlags & 0xfffffffeu) | 1u;
    } else if (message == 0x997) {
        if (DisplayHasNode(m_pUnk24)) DisplayReleaseNode(m_pUnk24);  // 0x0098f590
        if (m_i32Type == 0) TimeCounter(m_pUnk20)->m_baFlags &= 0xfffffffeu;
    }
    if (base == 3) return 3;
    if (base == 2) return 2;
    return base == 0 ? 0 : 1;
}
