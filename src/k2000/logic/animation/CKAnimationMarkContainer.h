// CKAnimationMarkContainer.h - the animation marks of an animation (key 0x898c, vtable 0xb166f8, size
// 0x10). Original unit: CKAnimationMarkContainer.cpp. Not in XXL2.
//
// The container holds a vector of marks; each mark is one of five small classes, picked by a type word
// in the file (the Load's jump table 0x7d9ec): two constants and three key lists. The marks are not
// IKBaseClass objects: their vtable starts with GetType (slot 0), then Save, Load, ClearKeys, ValueAt,
// MaxInRange, MinInRange, CrossedValue, GetKeyValue. Only the slots the Load uses are declared; the rest
// come with C2.2.
#pragma once
#include <cstdint>
#include <cstring>

#include "crt/ppc_ops.h"

#include "k2000/core/IKSerializable.h"
#include "k2000/core/Layout.h"
#include "k2000/io/IKFile.h"
#include "k2000/memory/Mem.h"

// The mark base (Ghidra AnimMark): the vtable and the channel.
class AnimMark {
public:
    virtual uint32_t GetType() = 0;                // slot 0 (KStub_ReturnN)
    virtual void Save(IKFile* /*file*/) {}         // slot 1  STUB(C2.2)
    virtual void Load(IKFile* file) = 0;           // slot 2

    // 0x0007dcf8 AnimMark_LoadChannel
    void LoadChannel(IKFile* file) { ReadU32LE(file, &m_channel); }

    uint32_t m_channel;  // +0x04 not set by the constructors
};
DOTD_ASSERT_SIZE(AnimMark, 0x8);

// Types 0 and 1: a constant (vtables 0xb16750 and 0xb167b0, 0xc bytes; the constructor sets the vtable
// only).
class AnimMarkConst0 : public AnimMark {
public:
    uint32_t GetType() override { return 0; }  // 0x999960 KStub_Return0_999960
    // 0x0099ad48 AnimMarkConst0_Load
    void Load(IKFile* file) override {
        LoadChannel(file);
        ReadU32LE(file, &m_value);
    }
    uint32_t m_value;  // +0x08
};
DOTD_ASSERT_SIZE(AnimMarkConst0, 0xc);

class AnimMarkConst1 : public AnimMark {
public:
    uint32_t GetType() override { return 1; }  // 0x999930 KStub_Return1_999930
    // 0x0099ae50 AnimMarkConst1_Load
    void Load(IKFile* file) override {
        LoadChannel(file);
        ReadU32LE(file, &m_value);
    }
    uint32_t m_value;  // +0x08
};
DOTD_ASSERT_SIZE(AnimMarkConst1, 0xc);

// One key of a key-list mark: a time and a value (an integer in the LVL010 marks of type 2).
struct AnimMarkKey {
    float m_fTime;     // +0x00
    uint32_t m_value;  // +0x04
};
DOTD_ASSERT_SIZE(AnimMarkKey, 0x8);

// Types 2, 3 and 4: key lists (vtables 0xb16810, 0xb16840, 0xb16870, 0x14 bytes). The three Loads are the
// same code: a TVector of keys (block, capacity, count; the constructor: 0, 1, 0).
class AnimMarkKeys : public AnimMark {
public:
    AnimMarkKeys() {
        m_aKeys = nullptr;
        m_capacity = 1;
        m_count = 0;
    }
    // 0x0099aed8 AnimMarkKeys2_Load, 0x0099b0a8 AnimMarkKeys3_Load, 0x0099b278 AnimMarkKeys4_Load
    void Load(IKFile* file) override {
        LoadChannel(file);
        uint32_t count;
        ReadU32LE(file, &count);
        if (count == 0) {
            m_capacity = 1;
            m_aKeys = static_cast<AnimMarkKey*>(Mem_AllocAligned16(static_cast<uint32_t>(sizeof(AnimMarkKey))));
        } else {
            m_capacity = count;
            m_aKeys = static_cast<AnimMarkKey*>(Mem_AllocAligned16(count * static_cast<uint32_t>(sizeof(AnimMarkKey))));
        }
        if (m_capacity < count) {  // the inlined reserve; never true here
            uint32_t grown = count + 1;
            m_aKeys = static_cast<AnimMarkKey*>(
                Mem_ReallocAligned16(m_aKeys, grown * static_cast<uint32_t>(sizeof(AnimMarkKey))));
            m_capacity = grown;
        }
        m_count = count;
        for (uint32_t i = 0; i < count; ++i) {
            ReadF32LE(file, &m_aKeys[i].m_fTime);
            ReadU32LE(file, &m_aKeys[i].m_value);
        }
    }
    AnimMarkKey* m_aKeys;  // +0x08 Mem_AllocAligned16
    uint32_t m_capacity;   // +0x0c
    uint32_t m_count;      // +0x10
};
DOTD_ASSERT_SIZE(AnimMarkKeys, 0x14);

class AnimMarkKeys2 : public AnimMarkKeys {
public:
    uint32_t GetType() override { return 2; }  // 0x999990 KStub_Return2_999990
};
class AnimMarkKeys3 : public AnimMarkKeys {
public:
    uint32_t GetType() override { return 3; }  // 0x999928 KStub_Return3_999928
};
class AnimMarkKeys4 : public AnimMarkKeys {
public:
    uint32_t GetType() override { return 4; }  // 0x999920 KStub_Return4_999920
};

// ---- The marks' query slots (vt+0x10 ValueAt, vt+0x1c CrossedValue; the [inline] 0x999xxx bodies of this unit), as their
// callers read them. The slots return a float (f1) in the types 0, 3 and 4 and an integer (r3) in the types 1 and 2, and
// the callers read one register whatever the type: the integer register after a float slot holds a pointer (the mark, or
// its key block), never 0. DOTD: dispatched on GetType (slot 0) instead of the vtable slot.

// The key lists' time wrap (the start of 0x999aa0 / 0x999b70 / 0x999c40 / 0x99a1b8 / 0x999e10 / 0x999d38): below 0 (TOC1
// -0x6a20) the last key's time is added until it is not, then taken off while it is not above the time.
inline float AnimMarkKeys_WrapTime(const AnimMarkKeys* keys, float t) {
    const float last = keys->m_aKeys[keys->m_count - 1].m_fTime;
    if (!(t >= 0.0f)) {
        do {
            t = t + last;
        } while (t < 0.0f);
    }
    while (last <= t) t = t - last;
    return t;
}

inline float AnimMark_WordAsFloat(uint32_t word) {
    float value;
    std::memcpy(&value, &word, 4);
    return value;
}

// 0x00999aa0 AnimMarkKeys2_ValueAt: the value of the key before the first key not before the (wrapped) time; 0 with
// one key or past the last.
inline uint32_t AnimMarkKeys2_ValueAt(const AnimMarkKeys* keys, float t) {
    t = AnimMarkKeys_WrapTime(keys, t);
    for (uint32_t i = 1; i < keys->m_count; ++i) {
        if (keys->m_aKeys[i].m_fTime >= t) return keys->m_aKeys[i - 1].m_value;  // cror gt|eq
    }
    return 0;
}

// 0x0099a1b8 AnimMarkKeys2_CrossedValue: over the keys from the first not before `t0` (both times wrapped): the value
// of the key before when that key is at `t0` exactly, the key's own when `t1` reaches it from before `t0`, the largest
// (unsigned) of those and the keys passed on the way; the answer when a key beyond `t1` comes, 0 when none does.
inline uint32_t AnimMarkKeys2_CrossedValue(const AnimMarkKeys* keys, float t0, float t1) {
    t0 = AnimMarkKeys_WrapTime(keys, t0);
    t1 = AnimMarkKeys_WrapTime(keys, t1);
    const uint32_t count = keys->m_count;
    if (count <= 1) return 0;
    float previousTime = keys->m_aKeys[0].m_fTime;
    uint32_t previousValue = keys->m_aKeys[0].m_value;
    uint32_t result = 0;
    for (uint32_t i = 1; i < count; ++i) {
        const float time = keys->m_aKeys[i].m_fTime;
        const uint32_t value = keys->m_aKeys[i].m_value;
        if (t0 <= time) {
            if (previousTime == t0) {
                result = previousValue;
            } else if (previousTime <= t0 && t1 >= time) {
                result = value;
            }
            if (t1 < time) return result;
            if (result < value) result = value;
        }
        previousValue = value;
        previousTime = time;
    }
    return 0;
}

// vt+0x10 as an integer (r3): type 1 its constant (0x999938), type 2 the key value (0x999aa0), else a pointer (1).
inline uint32_t AnimMark_ValueAtR3(AnimMark* mark, float t) {
    const uint32_t type = mark->GetType();
    if (type == 1) return static_cast<AnimMarkConst1*>(mark)->m_value;
    if (type == 2) return AnimMarkKeys2_ValueAt(static_cast<AnimMarkKeys*>(mark), t);
    return 1;
}

// vt+0x1c as an integer (r3): type 1 its constant (0x999950), type 2 the crossed value (0x99a1b8), else a pointer (1).
inline uint32_t AnimMark_CrossedValueR3(AnimMark* mark, float t0, float t1) {
    const uint32_t type = mark->GetType();
    if (type == 1) return static_cast<AnimMarkConst1*>(mark)->m_value;
    if (type == 2) return AnimMarkKeys2_CrossedValue(static_cast<AnimMarkKeys*>(mark), t0, t1);
    return 1;
}

// vt+0x10 as a float (f1): constant 0 its value as a float (0x999968); constant 1 (0x999938) leaves f1, `t`; keys 2
// (0x999aa0) leave the wrapped time; keys 3 (0x999b70) the value of the key before the first key not before the time (a
// step), 0 with one key or past the last; keys 4 (0x999c40) the same, interpolated linearly.
inline float AnimMark_ValueAtF1(AnimMark* mark, float t) {
    const uint32_t type = mark->GetType();
    if (type == 0) return AnimMark_WordAsFloat(static_cast<AnimMarkConst0*>(mark)->m_value);
    if (type == 1) return t;
    const AnimMarkKeys* keys = static_cast<const AnimMarkKeys*>(mark);
    t = AnimMarkKeys_WrapTime(keys, t);
    if (type == 2) return t;
    const uint32_t count = keys->m_count;
    if (count <= 1) return 0.0f;  // TOC1 -0x6a20
    for (uint32_t i = 1; i < count; ++i) {
        const AnimMarkKey& previous = keys->m_aKeys[i - 1];
        const AnimMarkKey& key = keys->m_aKeys[i];
        if (key.m_fTime >= t) {
            if (type == 3) return AnimMark_WordAsFloat(previous.m_value);
            const float v0 = AnimMark_WordAsFloat(previous.m_value);
            const float fraction = (t - previous.m_fTime) / (key.m_fTime - previous.m_fTime);
            return ppc::fmadds(fraction, AnimMark_WordAsFloat(key.m_value) - v0, v0);
        }
    }
    return 0.0f;
}

struct RtAnimAnimation;
// 0x00078830 Anim_GetMarkById (k2000/graphical/animation/CSectorAnimation.cpp): the mark of channel `id` in the
// animation's mark container (the sector entry's handle +0x20, at the end of the custom data), searched from the last;
// null without a container or a match.
AnimMark* Anim_GetMarkById(RtAnimAnimation* animation, uint32_t id);

class CKAnimationMarkContainer : public IKSerializable {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x226)
    DOTD_DECLARE_FACTORIES(CKAnimationMarkContainer)

    CKAnimationMarkContainer();  // 0x0007d6b8 CKAnimationMarkContainer_Create (as the dead _Construct 0x7d3a0)
    ~CKAnimationMarkContainer() override {}

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x0007d868 CKAnimationMarkContainer_Load

    AnimMark** m_ppMarks;  // +0x04 Mem_AllocAligned16; 0 in the constructor
    uint32_t m_capacity;   // +0x08 1 in the constructor
    uint32_t m_count;      // +0x0c
};
DOTD_ASSERT_SIZE(CKAnimationMarkContainer, 0x10);
DOTD_ASSERT_OFFSET(CKAnimationMarkContainer, m_ppMarks, 0x04);
DOTD_ASSERT_OFFSET(CKAnimationMarkContainer, m_capacity, 0x08);
DOTD_ASSERT_OFFSET(CKAnimationMarkContainer, m_count, 0x0c);
