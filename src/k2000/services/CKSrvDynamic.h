// CKSrvDynamic.h - the dynamic-object service (key 0x701, vtable 0xb20bd0, size 0x30). Original unit:
// CKSrvDynamic.cpp (0x23a9a8-0x23bce0). Not in XXL2; names ours.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/services/IKService.h"
#include "k2000/util/TVector.h"

class CKSrvDynamic : public IKService {
public:
    DOTD_CLASS_KEY(kCategoryService, 0x1c)
    int32_t IsKindOfClass(uint32_t key) override {  // vt+0x08 0x9b9bc8
        return key == 0x701 || key == 0x1 || key == 0x3fe || key == 0xc;
    }
    DOTD_DECLARE_FACTORIES(CKSrvDynamic)

    // One registered object, 0x24 bytes on the PS3 (CKSrvDynamic_RegisterHook 0x23b480 inserts them
    // sorted by +0x20, descending _maybe).
    struct Entry {
        IKSerializable* m_unk00;  // +0x00 the registered object (the search key)
        uint8_t m_ui8Flag;        // +0x04 a flag byte (SetEntryFlag)
        uint8_t m_pad05[3];
        uint32_t m_unk08[6];      // +0x08 the caller's words
        uint32_t m_unk20;         // +0x20 the sort key
    };

    CKSrvDynamic();  // inlined in 0x0023b990 CKSrvDynamic_Create
    ~CKSrvDynamic() override {}
    // vt+0x24 0x0023aa50 CKSrvDynamic_RecursiveRegistration: type 0: the service registered.
    void RecursiveRegistration(int32_t type) override;

    void Destroy() override;  // vt+0x10 0x0023aec8 CKSrvDynamic_Destroy
    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x0023b3c0 CKSrvDynamic_Load
    // 0x0023aff8 CKSrvDynamic_SetEntryFlag: the flag byte of the entry registered for `object`, if any.
    void SetEntryFlag(IKSerializable* object, uint8_t flag);
    // 0x0023b168 CKSrvDynamic_UnregisterHook: the object's entry gets the last entry (unordered removal), the count +0x0c
    // follows the size; an object not registered changes nothing.
    void UnregisterHook(IKSerializable* object);

    // A pointer to a member function as the PS3 passes it: the function descriptor's address and the this-adjust
    // (k2000/core/Ps3MemberFn.h; the entry keeps the words, the owner maps them to its native hooks: the hero's
    // CKHkS08Hero::CallDynamicHook). Each hook takes a time step.
    struct SPtmf {
        uint32_t m_fn;
        uint32_t m_adj;
    };
    // 0x0023b480 CKSrvDynamic_RegisterHook (`key` is the entry's sort key; hook5/6/7 are the PS3's 64-bit arguments 5,
    // 6 and 7). The entry keeps hook6 at +0x08 (called once per frame with the frame's dt), hook5 at +0x10 (called at
    // each fixed sub-step with the step) and hook7 at +0x18 (called last with the time left over): Update below.
    void RegisterHook(IKSerializable* object, uint8_t flag, uint32_t key, const SPtmf& hook5, const SPtmf& hook6,
                      const SPtmf& hook7);
    // DOTD: the native side of an entry: the owner's function that maps a (descriptor, adjust) pair of its hooks to
    // its native member and calls it with the step. The owner sets it next to its RegisterHook; an entry without one
    // logs once and its hooks do nothing.
    using NativeHookDispatch = void (*)(IKSerializable* object, const uint32_t pair[2], float step);
    void SetNativeDispatch(IKSerializable* object, NativeHookDispatch dispatch);
    void Start() override;                              // vt+0x50 0x0023aab0 CKSrvDynamic_Start
    void Stop() override {}                             // vt+0x68 0x0023aac0 CKSrvDynamic_Stop (empty)
    void Pause() override;                              // vt+0x70 0x0023aac8 CKSrvDynamic_Pause
    void Resume() override;                             // vt+0x78 0x0023aad8 CKSrvDynamic_Resume
    // vt+0x7c 0x0023ba10 UpdateCKSrvDynamic: the frame's dt plus the time left over from the last frame cut in fixed
    // steps of 1 / +0x1c (at least one: the whole time when it is shorter than a step); the entries' frame hooks, then
    // the sub-step hooks once per step (+0x24 the step's index, +0x28 the count), then the hooks of the time left
    // (kept in +0x20). Nothing while paused.
    void Update(IKTime* clock) override;
    // 0x0023ad90 CKSrvDynamic_GetElapsedStepTime_maybe: the time of the current sub-step's start (+0x24 / +0x1c).
    float GetElapsedStepTime() const;
    // 0x0023adb0 CKSrvDynamic_GetSubstepCount_maybe
    int32_t GetSubstepCount() const;
    // 0x0023adb8 CKSrvDynamic_GetFixedStepDt_maybe
    float GetFixedStepDt() const;
    int32_t InitializeService() override;               // vt+0x94 0x23aea0 CKSrvDynamic_InitializeService
    void DestroyService() override {}                   // vt+0x98 0x23aa48 (empty)

    uint32_t m_unk0c;              // +0x0c Load: 0 (a count, RegisterHook loops over it _maybe)
    TVector<Entry, 1> m_vEntries;  // +0x10 Load (level): a one-entry block
    float m_fStepsPerSecond;       // +0x1c read (LVL000: 200.0): the fixed step is its inverse
    float m_fStepRemainder;        // +0x20 the time left over by the last Update (Load, Resume: 0)
    uint32_t m_ui32StepIndex;      // +0x24 the current sub-step (Load: 0)
    int32_t m_i32StepCount;        // +0x28 the sub-steps of this frame (Load: 0)
    uint8_t m_ui8Paused;           // +0x2c Pause 1, Start / Resume 0 (not set by the constructor or Load)
    uint8_t m_pad2d[3];
};
DOTD_ASSERT_SIZE(CKSrvDynamic::Entry, 0x24);
DOTD_ASSERT_SIZE(CKSrvDynamic, 0x30);
DOTD_ASSERT_OFFSET(CKSrvDynamic, m_ui32Priority, 0x08);
DOTD_ASSERT_OFFSET(CKSrvDynamic, m_unk0c, 0x0c);
DOTD_ASSERT_OFFSET(CKSrvDynamic, m_vEntries, 0x10);
DOTD_ASSERT_OFFSET(CKSrvDynamic, m_fStepsPerSecond, 0x1c);
DOTD_ASSERT_OFFSET(CKSrvDynamic, m_fStepRemainder, 0x20);
DOTD_ASSERT_OFFSET(CKSrvDynamic, m_ui32StepIndex, 0x24);
DOTD_ASSERT_OFFSET(CKSrvDynamic, m_i32StepCount, 0x28);
DOTD_ASSERT_OFFSET(CKSrvDynamic, m_ui8Paused, 0x2c);
