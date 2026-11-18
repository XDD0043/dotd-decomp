// CKSrvDynamic.cpp - reconstructed original translation unit 0x23a9a8-0x23bce0 (GAME_TOC1, main_toc1), 28 functions, 23 live.
// Primary class: CKSrvDynamic  key 0x701  category Service  size 0x30  vtable 0xb20bd0
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x23a9a8  CKSrvDynamic_Delete
//   [ ] 0x23a9f8  CKSrvDynamic_Construct  [dead]
//   [x] 0x23aa48  CKSrvDynamic_DestroyService
//   [x] 0x23aa50  CKSrvDynamic_RecursiveRegistration
//   [x] 0x23aab0  CKSrvDynamic_Start
//   [x] 0x23aac0  CKSrvDynamic_Stop
//   [x] 0x23aac8  CKSrvDynamic_Pause
//   [x] 0x23aad8  CKSrvDynamic_Resume
//   [ ] 0x23aaf0  CKSrvDynamic_CallFrameHooks_maybe  [dead]
//   [ ] 0x23abd0  CKSrvDynamic_CallStepHooks_maybe  [dead]
//   [ ] 0x23acb0  CKSrvDynamic_CallPostStepHooks_maybe  [dead]
//   [x] 0x23ad90  CKSrvDynamic_GetElapsedStepTime_maybe
//   [x] 0x23adb0  CKSrvDynamic_GetSubstepCount_maybe
//   [x] 0x23adb8  CKSrvDynamic_GetFixedStepDt_maybe
//   [ ] 0x23adc8  CKSrvDynamic_Construct_2  [dead]
//   [ ] 0x23ae18  RegisterCKSrvDynamicClass
//   [ ] 0x23ae90  _GLOBAL__I_23ae90
//   [x] 0x23aea0  CKSrvDynamic_InitializeService
//   [x] 0x23aec8  CKSrvDynamic_Destroy
//   [x] 0x23af50  CKSrvDynamic_DeleteArray
//   [x] 0x23aff8  CKSrvDynamic_SetEntryFlag
//   [x] 0x23b168  CKSrvDynamic_UnregisterHook
//   [ ] 0x23b350  CKSrvDynamic_Save
//   [x] 0x23b3c0  CKSrvDynamic_Load
//   [x] 0x23b480  CKSrvDynamic_RegisterHook
//   [x] 0x23b8a8  CKSrvDynamic_CreateArray
//   [x] 0x23b990  CKSrvDynamic_Create
//   [x] 0x23ba10  UpdateCKSrvDynamic
//
//   [ ] 0x9b9bc8  CKSrvDynamic_IsKindOfClass  [inline]
//   [ ] 0x9b9c00  CKSrvDynamic_GetClassType  [inline]
//   [ ] 0x9b9c08  CKSrvDynamic_GetClassID  [inline]
//   [ ] 0x9b9c10  CKSrvDynamic_DeletingDestructor  [inline]
//   [ ] 0x9b9c98  CKSrvDynamic_Destructor  [inline]
#include "k2000/services/CKSrvDynamic.h"

#include <cstring>

#include "k2000/io/IKFile.h"
#include "k2000/memory/Mem.h"
#include "k2000/logic/CKSavingManager.h"
#include "k2000/misc/Engine.h"
#include "k2000/system/IKTime.h"
#include "crt/ppc_ops.h"
#include "platform/log.h"

namespace {
// DOTD: the native dispatchers of the registered objects (SetNativeDispatch). A handful of objects register (the
// heroes, the hero group); objects no longer registered leave the table when another is added.
struct NativeDispatchEntry {
    IKSerializable* m_object;
    CKSrvDynamic::NativeHookDispatch m_dispatch;
};
NativeDispatchEntry g_nativeDispatch[16];
uint32_t g_nativeDispatchCount = 0;

CKSrvDynamic::NativeHookDispatch FindNativeDispatch(IKSerializable* object) {
    for (uint32_t i = 0; i < g_nativeDispatchCount; ++i) {
        if (g_nativeDispatch[i].m_object == object) return g_nativeDispatch[i].m_dispatch;
    }
    return nullptr;
}

// One hook call of UpdateCKSrvDynamic: an entry with a hook at `pair` and its flag byte set calls it with `step`.
void CallEntryHook(CKSrvDynamic::Entry* entry, const uint32_t pair[2], float step) {
    if (pair[0] == 0 || entry->m_ui8Flag == 0) return;
    CKSrvDynamic::NativeHookDispatch dispatch = FindNativeDispatch(entry->m_unk00);
    if (dispatch == nullptr) {
        static bool s_logged = false;
        if (!s_logged) {
            s_logged = true;
            DOTD_LOG("CKSrvDynamic: an entry without a native dispatcher (hook %08x)", pair[0]);
        }
        return;
    }
    dispatch(entry->m_unk00, pair, step);
}
}  // namespace

// DOTD: see the header.
void CKSrvDynamic::SetNativeDispatch(IKSerializable* object, NativeHookDispatch dispatch) {
    uint32_t kept = 0;
    for (uint32_t i = 0; i < g_nativeDispatchCount; ++i) {
        IKSerializable* other = g_nativeDispatch[i].m_object;
        if (other == object) continue;
        bool registered = false;
        for (uint32_t k = 0; k < m_vEntries.m_ui32NbUsedElt; ++k) {
            if (m_vEntries.m_pBlock[k].m_unk00 == other) registered = true;
        }
        if (registered) g_nativeDispatch[kept++] = g_nativeDispatch[i];
    }
    g_nativeDispatchCount = kept;
    if (g_nativeDispatchCount >= sizeof(g_nativeDispatch) / sizeof(g_nativeDispatch[0])) {
        DOTD_LOG("CKSrvDynamic: native dispatch table full");
        return;
    }
    g_nativeDispatch[g_nativeDispatchCount].m_object = object;
    g_nativeDispatch[g_nativeDispatchCount].m_dispatch = dispatch;
    ++g_nativeDispatchCount;
}

// Inlined in 0x0023b990 CKSrvDynamic_Create (0x23a9f8 CKSrvDynamic_Construct is an unreferenced copy).
CKSrvDynamic::CKSrvDynamic() {
    m_vEntries.m_ui32NbElt = 1;
    m_vEntries.m_ui32NbUsedElt = 0;
    m_vEntries.m_pBlock = nullptr;
    m_ui32Priority = 0x79;
}

// 0x0023aea0 CKSrvDynamic_InitializeService: the engine's dynamic service (+0xb8), returns 1.
int32_t CKSrvDynamic::InitializeService() {
    Engine_SetDynamicService(this);
    return 1;
}

// 0x0023aec8 CKSrvDynamic_Destroy: the counters cleared, the entry block freed.
void CKSrvDynamic::Destroy() {
    m_unk0c = 0;
    if (m_vEntries.m_pBlock != nullptr) {
        Mem_FreeAligned16(m_vEntries.m_pBlock);
        m_vEntries.m_pBlock = nullptr;
    }
    m_vEntries.m_ui32NbUsedElt = 0;
    m_vEntries.m_pBlock = nullptr;
    m_i32StepCount = 0;
    m_fStepRemainder = 0.0f;
    m_ui32StepIndex = 0;
}

// 0x0023b3c0 CKSrvDynamic_Load. The counters are cleared for every type; a level also allocates the
// one-entry block (over the constructor's null) and reads one float.
int32_t CKSrvDynamic::Load(IKFile* file, int32_t type) {
    m_i32StepCount = 0;
    m_fStepRemainder = 0.0f;
    m_unk0c = 0;
    m_ui32StepIndex = 0;
    if (type == K_LEVEL_PLATEFORMS) {
        m_vEntries.m_ui32NbElt = 1;
        m_vEntries.m_pBlock = static_cast<Entry*>(Mem_AllocAligned16(static_cast<uint32_t>(sizeof(Entry))));
        ReadF32LE(file, &m_fStepsPerSecond);
    }
    return 1;
}

// 0x0023b480 CKSrvDynamic_RegisterHook: an object already registered is left alone; otherwise its 0x24-byte entry
// (the three member-function pointers the caller passes, the flag byte, the sort key) goes in front of the
// first of the first +0x0c entries whose key is not above `key` (the loop goes on after an insertion, a copy for
// every further entry that qualifies; BUG(original) kept), or at the end.
void CKSrvDynamic::RegisterHook(IKSerializable* object, uint8_t flag, uint32_t key, const SPtmf& hook5,
                                const SPtmf& hook6, const SPtmf& hook7) {
    TVector<Entry, 1>& entries = m_vEntries;
    for (uint32_t i = 0; i < entries.m_ui32NbUsedElt; ++i) {
        if (entries.m_pBlock[i].m_unk00 == object) return;
    }
    // The 0x24 bytes the original builds on its stack: the flag byte is the top byte of the word at +0x04 (the
    // other three bytes are stack leftovers there, not reproduced).
    auto fill = [&](Entry* e) {
        e->m_unk00 = object;
        e->m_ui8Flag = flag;
        e->m_unk08[0] = hook6.m_fn;
        e->m_unk08[1] = hook6.m_adj;
        e->m_unk08[2] = hook5.m_fn;
        e->m_unk08[3] = hook5.m_adj;
        e->m_unk08[4] = hook7.m_fn;
        e->m_unk08[5] = hook7.m_adj;
        e->m_unk20 = key;
    };
    auto grow = [&]() {
        if (entries.m_ui32NbElt != entries.m_ui32NbUsedElt) return;
        uint32_t capacity = entries.m_ui32NbUsedElt + 1;
        if (capacity == 0) capacity = 1;
        entries.m_pBlock = static_cast<Entry*>(
            Mem_ReallocAligned16(entries.m_pBlock, capacity * static_cast<uint32_t>(sizeof(Entry))));
        entries.m_ui32NbElt = capacity;
    };
    uint32_t used = entries.m_ui32NbUsedElt;
    if (m_unk0c != 0) {
        bool inserted = false;
        for (uint32_t i = 0; i < m_unk0c; ++i) {
            if (entries.m_pBlock[i].m_unk20 > key) continue;
            grow();
            used = entries.m_ui32NbUsedElt;
            std::memmove(&entries.m_pBlock[i + 1], &entries.m_pBlock[i], (used - i) * sizeof(Entry));
            fill(&entries.m_pBlock[i]);
            inserted = true;
            used = ++entries.m_ui32NbUsedElt;
        }
        if (inserted) {
            m_unk0c = used;
            return;
        }
    }
    grow();
    used = entries.m_ui32NbUsedElt;
    fill(&entries.m_pBlock[used]);
    used = ++entries.m_ui32NbUsedElt;
    m_unk0c = used;
}

// 0x0023aff8 CKSrvDynamic_SetEntryFlag
void CKSrvDynamic::SetEntryFlag(IKSerializable* object, uint8_t flag) {
    for (uint32_t i = 0; i < m_vEntries.m_ui32NbUsedElt; ++i) {
        if (m_vEntries.m_pBlock[i].m_unk00 == object) {
            m_vEntries.m_pBlock[i].m_ui8Flag = flag;
            return;
        }
    }
}

// 0x0023aab0 CKSrvDynamic_Start
void CKSrvDynamic::Start() { m_ui8Paused = 0; }

// 0x0023aac8 CKSrvDynamic_Pause
void CKSrvDynamic::Pause() { m_ui8Paused = 1; }

// 0x0023aad8 CKSrvDynamic_Resume: the time left over is dropped.
void CKSrvDynamic::Resume() {
    m_fStepRemainder = 0.0f;
    m_ui8Paused = 0;
}

// 0x0023ad90 CKSrvDynamic_GetElapsedStepTime_maybe
float CKSrvDynamic::GetElapsedStepTime() const {
    // lwz + fcfid: the index as an unsigned 32-bit value, rounded to float, then divided.
    const float index = static_cast<float>(static_cast<double>(m_ui32StepIndex));
    return index / m_fStepsPerSecond;
}

// 0x0023adb0 CKSrvDynamic_GetSubstepCount_maybe
int32_t CKSrvDynamic::GetSubstepCount() const { return m_i32StepCount; }

// 0x0023adb8 CKSrvDynamic_GetFixedStepDt_maybe
float CKSrvDynamic::GetFixedStepDt() const { return 1.0f / m_fStepsPerSecond; }  // TOC1 -0x324

// 0x0023ba10 UpdateCKSrvDynamic. The entry count (+0x0c) and the entry block are read again after every call.
void CKSrvDynamic::Update(IKTime* clock) {
    if (m_ui8Paused != 0) return;
    float step = 1.0f / m_fStepsPerSecond;  // TOC1 -0x324
    const float dt = clock->m_afDeltaTime[0];
    const float total = dt + m_fStepRemainder;
    // fdivs + fctidz: the 64-bit truncation of the float quotient; the low word is the count.
    int32_t count = static_cast<int32_t>(static_cast<uint32_t>(ppc::fctidz(total / step)));
    float steps;
    if (count == 0) {
        steps = 1.0f;
        count = 1;
        step = total;
    } else {
        // rldicl + fcfid + frsp: the count's low word as an unsigned value.
        steps = static_cast<float>(static_cast<double>(static_cast<uint32_t>(count)));
    }
    m_i32StepCount = count;
    const float remainder = total - step * steps;
    m_fStepRemainder = remainder;
    uint32_t used = m_unk0c;
    for (uint32_t i = 0; i < used;) {
        Entry* entry = &m_vEntries.m_pBlock[i];
        ++i;
        if (entry->m_unk08[0] != 0 && entry->m_ui8Flag != 0) {
            CallEntryHook(entry, &entry->m_unk08[0], dt);
            used = m_unk0c;
        }
    }
    int32_t index = 0;
    do {
        m_ui32StepIndex = static_cast<uint32_t>(index);
        for (uint32_t i = 0; i < used;) {
            Entry* entry = &m_vEntries.m_pBlock[i];
            ++i;
            if (entry->m_unk08[2] != 0 && entry->m_ui8Flag != 0) {
                CallEntryHook(entry, &entry->m_unk08[2], step);
                used = m_unk0c;
            }
        }
        ++index;
    } while (count != index);
    for (uint32_t i = 0; i < used;) {
        Entry* entry = &m_vEntries.m_pBlock[i];
        ++i;
        if (entry->m_unk08[4] != 0 && entry->m_ui8Flag != 0) {
            CallEntryHook(entry, &entry->m_unk08[4], remainder);
            used = m_unk0c;
        }
    }
}

// 0x0023b168 CKSrvDynamic_UnregisterHook
void CKSrvDynamic::UnregisterHook(IKSerializable* object) {
    const uint32_t count = m_vEntries.m_ui32NbUsedElt;
    if (count == 0) return;
    uint32_t index = 0;
    while (m_vEntries.m_pBlock[index].m_unk00 != object) {
        if (++index == count) return;
    }
    const uint32_t last = count - 1;
    m_vEntries.m_ui32NbUsedElt = last;
    if (last != index) m_vEntries.m_pBlock[index] = m_vEntries.m_pBlock[last];
    m_unk0c = m_vEntries.m_ui32NbUsedElt;
}

// 0x0023aa50 CKSrvDynamic_RecursiveRegistration: type 0: the service registered (CKSavingManager vt+0x24).
void CKSrvDynamic::RecursiveRegistration(int32_t type) {
    if (type == 0) g_pEngine->m_pSavingManager->RegisterSerializableObject(this, nullptr);
}
