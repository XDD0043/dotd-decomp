// ps3_qsort_test - C2.4 step 5: the ported PS3 libc qsort (crt/Ps3Qsort.cpp) sorts correctly for every size up to 600, with
// many equal keys (the forced sort keys of the world geometries are 0..7), with all-equal and already-sorted input, and
// keeps the elements a permutation of the input. (The order of equal keys is the original's; that is not checkable
// without it, the algorithm is a transcription.)
#include <algorithm>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "crt/Ps3Qsort.h"

namespace {
struct Item {
    float key;
    uint32_t id;
};
int Compare(const void* a, const void* b) {
    const float d = static_cast<const Item*>(b)->key - static_cast<const Item*>(a)->key;  // descending, as the queues
    return d == 0.0f ? 0 : (d < 0.0f ? -1 : 1);
}
}  // namespace

int main() {
    std::srand(12345);
    int failures = 0;
    for (int mode = 0; mode < 5; ++mode) {
        for (uint32_t n = 0; n <= 600; ++n) {
            std::vector<Item> items(n);
            for (uint32_t i = 0; i < n; ++i) {
                switch (mode) {
                    case 0: items[i].key = static_cast<float>(std::rand() % 8); break;      // many equal keys
                    case 1: items[i].key = static_cast<float>(std::rand()); break;          // mostly distinct
                    case 2: items[i].key = 3.0f; break;                                      // all equal
                    case 3: items[i].key = static_cast<float>(n - i); break;                 // already in order (descending)
                    default: items[i].key = static_cast<float>(i); break;                    // the reverse order
                }
                items[i].id = i;
            }
            std::vector<Item> sorted = items;
            Ps3Qsort(sorted.data(), n, sizeof(Item), Compare);
            bool ok = true;
            for (uint32_t i = 1; i < n; ++i) ok = ok && sorted[i - 1].key >= sorted[i].key;
            std::vector<uint32_t> ids;
            for (const Item& item : sorted) ids.push_back(item.id);
            std::sort(ids.begin(), ids.end());
            for (uint32_t i = 0; i < n; ++i) ok = ok && ids[i] == i;
            if (!ok) {
                std::printf("FAIL ps3_qsort: mode %d size %u\n", mode, n);
                ++failures;
            }
        }
    }
    if (failures == 0) std::printf("ps3_qsort: all tests passed\n");
    return failures == 0 ? 0 : 1;
}
