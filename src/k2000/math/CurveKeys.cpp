// CurveKeys.cpp - reconstructed original translation unit 0x246350-0x246bb8 (GAME_TOC1, main_toc1), 6 functions, 4 live.
// Primary owner: CurveKeys (not a registered class)
// Other owners: ColorCurve (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [ ] 0x246350  CurveKeys_Equals_maybe  [dead]
//   [x] 0x246408  ColorCurve_Evaluate
//   [ ] 0x246670  CurveKeys_CopyFrom_maybe
//   [ ] 0x246778  CurveKeys_NotEquals_maybe  [dead]
//   [ ] 0x246830  CurveKeys_Save_maybe
//   [x] 0x2469b8  CurveKeys_Load_maybe
#include "k2000/math/CurveKeys.h"

#include "k2000/io/IKFile.h"
#include <cstring>

#include "k2000/memory/Mem.h"
#include "crt/ppc_ops.h"

// 0x002469b8 CurveKeys_Load_maybe
void CurveKeys_Load(TVector<CurveKey, 20>* keys, IKFile* file) {
    uint32_t present = 0;
    ReadU32LE(file, &present);
    if (present == 0) return;
    uint32_t count = 0;
    ReadU32LE(file, &count);
    if (keys->m_ui32NbElt < count) {
        uint32_t capacity = (count / 20) * 20 + 20;  // the next multiple of 20 above count
        uint32_t bytes = capacity * static_cast<uint32_t>(sizeof(CurveKey));
        if (capacity == 0) {  // as in the original (cannot happen)
            capacity = 20;
            bytes = 20 * static_cast<uint32_t>(sizeof(CurveKey));
        }
        keys->m_pBlock = static_cast<CurveKey*>(Mem_ReallocAligned16(keys->m_pBlock, bytes));
        keys->m_ui32NbElt = capacity;
    }
    keys->m_ui32NbUsedElt = count;
    for (uint32_t i = 0; i < count; ++i) {
        ReadU32LE(file, &keys->m_pBlock[i].m_key);
        ReadRaw(file, keys->m_pBlock[i].m_valueRaw, 4);  // not swapped by the original
    }
}

// 0x00246408 ColorCurve_Evaluate: the colour (four raw bytes) of the key list at `t`. No key: the shared black (0x00c50df8,
// bytes 0, 0, 0, 0xff); one key: its colour; before the first or after the last key: that key's colour; on a key: its
// colour; between two keys: each byte blended (1 - f) * previous + f * next with f = (t - previous time) / (next time -
// previous time), truncated through fctidz to a byte. A list whose keys are not in ascending order can fall through
// every interval: black.
void ColorCurve_Evaluate(float t, uint8_t out[4], const TVector<CurveKey, 20>* keys) {
    static const uint8_t kBlack[4] = {0x00, 0x00, 0x00, 0xff};
    const uint32_t count = keys->m_ui32NbUsedElt;
    if (count == 0) {
        std::memcpy(out, kBlack, 4);
        return;
    }
    const CurveKey* block = keys->m_pBlock;
    if (count == 1) {
        std::memcpy(out, block[0].m_valueRaw, 4);
        return;
    }
    auto timeOf = [](const CurveKey& key) {
        float time;
        std::memcpy(&time, &key.m_key, 4);
        return time;
    };
    if (timeOf(block[0]) > t) {
        std::memcpy(out, block[0].m_valueRaw, 4);
        return;
    }
    if (t > timeOf(block[count - 1])) {
        std::memcpy(out, block[count - 1].m_valueRaw, 4);
        return;
    }
    if (timeOf(block[0]) == t) {
        std::memcpy(out, block[0].m_valueRaw, 4);
        return;
    }
    for (uint32_t i = 1; i < count; ++i) {
        const CurveKey& previous = block[i - 1];
        const CurveKey& next = block[i];
        const float previousTime = timeOf(previous);
        const float nextTime = timeOf(next);
        if (t == nextTime) {
            std::memcpy(out, next.m_valueRaw, 4);
            return;
        }
        if (previousTime < t && t < nextTime) {
            const float f = (t - previousTime) / (nextTime - previousTime);
            const float g = 1.0f - f;
            for (int k = 0; k < 4; ++k) {
                const float blended = ppc::fmadds(g, static_cast<float>(previous.m_valueRaw[k]), f * static_cast<float>(next.m_valueRaw[k]));
                out[k] = static_cast<uint8_t>(ppc::fctidz(blended));
            }
            return;
        }
    }
    std::memcpy(out, kBlack, 4);
}
