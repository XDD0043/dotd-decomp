// Ps3Qsort.cpp - see Ps3Qsort.h. Ported from the decompilation (the helper names are Ghidra's):
//   [x] 0x95eab0  qsort
//   [x] 0x95e4b8  Sort_IntroSort
//   [x] 0x95e258  Sort_MedianOfThree
//   [x] 0x95e080  Sort_AdjustHeap_maybe
//   [x] 0x95df30  Sort_SwapElements
//   [x] 0x95dd90  Sort_Rotate3Elements
//   [x] 0x95e3b8  Sort_RotateBlockRight
// The PS3 code works on 32-bit addresses; here pointers into the array are byte pointers.
#include "crt/Ps3Qsort.h"

#include <cstring>

namespace {
typedef int (*Compare)(const void*, const void*);
typedef uint8_t* P;

// 0x95df30: the bytes of two elements exchanged.
void Swap(P a, P b, uint32_t size) {
    uint8_t buffer[0x100];
    while (size != 0) {
        const uint32_t chunk = size < 0x100 ? size : 0x100;
        std::memcpy(buffer, a, chunk);
        std::memcpy(a, b, chunk);
        std::memcpy(b, buffer, chunk);
        a += chunk;
        b += chunk;
        size -= chunk;
    }
}

// 0x95dd90: a <- c, c <- b, b <- a (the old a).
void Rotate3(P a, P b, P c, uint32_t size) {
    uint8_t buffer[0x100];
    while (size != 0) {
        const uint32_t chunk = size < 0x100 ? size : 0x100;
        std::memcpy(buffer, a, chunk);
        std::memcpy(a, c, chunk);
        std::memcpy(c, b, chunk);
        std::memcpy(b, buffer, chunk);
        a += chunk;
        b += chunk;
        c += chunk;
        size -= chunk;
    }
}

// 0x95e3b8: the element at `source` moved to `dest`, the elements from `dest` up to it one place to the right.
void RotateBlockRight(P dest, P source, uint32_t size) {
    uint8_t buffer[0x100];
    uint32_t remaining = size;
    while (remaining != 0) {
        const uint32_t chunk = remaining < 0x100 ? remaining : 0x100;
        remaining -= chunk;
        std::memcpy(buffer, source + (size - chunk), chunk);
        std::memmove(dest + chunk, dest, static_cast<size_t>((source - dest) + size) - chunk);
        std::memcpy(dest, buffer, chunk);
    }
}

// 0x95e258: the median of three ends up in the middle slot, the smallest first, the largest last.
void MedianOfThree(P a, P b, P c, uint32_t size, Compare compare) {
    if (compare(b, a) < 0) {
        Swap(a, b, size);
        if (compare(c, b) < 0) Swap(b, c, size);
    } else if (compare(c, b) < 0) {
        Swap(b, c, size);
    }
    if (compare(b, a) < 0) Swap(a, b, size);
}

// 0x95e080: a heap of `count` elements, the element at `hole` sifted down by exchanging with its larger child, then the
// moved value sifted back up.
void AdjustHeap(P base, uint32_t hole, uint32_t count, uint32_t size, Compare compare) {
    uint32_t k = hole * 2 + 2;  // the right child's index
    if (count < k) return;
    P current = base + static_cast<size_t>(hole) * size;
    for (;;) {
        P right = base + static_cast<size_t>(k) * size;
        P left = right - size;
        P position;
        uint32_t next;
        if (count == k || compare(right, left) < 0) {
            --k;
            Swap(current, left, size);
            next = k * 2 + 2;
            position = left;
        } else {
            Swap(current, right, size);
            next = k * 2 + 2;
            position = right;
        }
        if (count < next) {
            // sift up from `position` (index k)
            if (hole < k) {
                do {
                    k = (k - 1) >> 1;
                    P parent = base + static_cast<size_t>(k) * size;
                    if (compare(position, parent) < 1) return;
                    Swap(parent, position, size);
                    position = parent;
                } while (hole < k);
            }
            return;
        }
        k = next;
        current = position;
    }
}

// 0x95e4b8
void IntroSort(P first, uint32_t count, uint32_t depth, uint32_t size, Compare compare) {
    bool toHeap = depth == 0;
    for (;;) {
        if (toHeap || count <= 0x20) {
            if (toHeap) {
                // 0x95e9dc: the heap sort of a long range whose recursion budget is spent
                if (count > 0x20) {
                    uint32_t half = count >> 1;
                    while (half != 0) {
                        --half;
                        AdjustHeap(first, half, count, size, compare);
                    }
                    P last = first + static_cast<size_t>(size) * count;
                    do {
                        last -= size;
                        --count;
                        Swap(first, last, size);
                        AdjustHeap(first, 0, count, size, compare);
                    } while (count != 1);
                    return;
                }
            }
            // 0x95e8ac: insertion sort
            P next = first;
            if (count > 1) {
                for (;;) {
                    --count;
                    if (count == 0) return;
                    while (true) {
                        next += size;
                        P position = next;
                        if (compare(next, first) < 0) {
                            RotateBlockRight(first, next, size);  // a new minimum: to the front
                            break;
                        }
                        P slot;
                        int result;
                        do {
                            slot = position;
                            result = compare(next, slot - size);
                            position = slot - size;
                        } while (result < 0);
                        if (next == slot) break;
                        --count;
                        RotateBlockRight(slot, next, size);
                        if (count == 0) return;
                    }
                }
            }
            return;
        }
        // 0x95e54c: the three-way partition around the median of three (nine for long ranges)
        P end = first + static_cast<size_t>(size) * count;
        P last = end - size;
        P mid = first + static_cast<size_t>(size) * (count >> 1);
        P upper = mid + size;  // uVar5
        if (static_cast<uint32_t>(size) * 0x28 < static_cast<uint32_t>(last - first)) {
            const uint32_t step = size * ((static_cast<uint32_t>(last - first) / size >> 3) + 1);
            MedianOfThree(first, first + step, first + step * 2, size, compare);
            MedianOfThree(mid - step, mid, mid + step, size, compare);
            MedianOfThree(last - step * 2, last - step, last, size, compare);
            MedianOfThree(first + step, mid, last - step, size, compare);
        } else {
            MedianOfThree(first, mid, last, size, compare);
        }
        // the pivot moves left over equal elements
        while (first < mid) {
            P previous = mid - size;
            if (compare(previous, mid) != 0) break;
            mid = previous;
        }
        // upper: past the elements equal to the pivot that follow it
        while (upper < end) {
            if (compare(upper, mid) != 0) break;
            upper += size;
        }
        P scan = upper;   // uVar6
        P lowerEnd = mid;  // uVar10
        for (;;) {
            // LAB_0095e6c4
            if (scan < end) goto upScan;
            for (;;) {
                // the down scan
                for (;;) {
                    if (first < mid) {
                        P pivot = lowerEnd;  // uVar7
                        do {
                            P candidate = mid - size;
                            const int result = compare(candidate, pivot);
                            if (result >= 0) {
                                if (result != 0) break;
                                pivot = lowerEnd - size;
                                Swap(pivot, candidate, size);
                                lowerEnd = pivot;
                            }
                            mid = candidate;
                        } while (first < mid);
                    }
                    if (first == mid) {
                        if (scan != end) {
                            if (upper == scan) {
                                Swap(upper, lowerEnd, size);
                            } else {
                                Rotate3(scan, lowerEnd, upper, size);
                            }
                            upper += size;
                            mid = first;
                            scan += size;
                            lowerEnd += size;
                            goto nextRound;
                        }
                        // the partition is done: the elements below the pivots, the equal ones in the middle, the larger above
                        const uint32_t leftCount = static_cast<uint32_t>((lowerEnd - first) / size);
                        const uint32_t rightCount = static_cast<uint32_t>((end - upper) / size);
                        depth = (depth >> 1) + (depth >> 2);
                        if (rightCount < leftCount) {
                            IntroSort(upper, rightCount, depth, size, compare);
                            count = leftCount;
                        } else {
                            IntroSort(first, leftCount, depth, size, compare);
                            first = upper;
                            count = rightCount;
                        }
                        toHeap = depth == 0;
                        goto restart;
                    }
                    if (scan == end) {
                        mid -= size;
                        lowerEnd -= size;
                        upper -= size;
                        scan = end;
                        if (mid == lowerEnd) {
                            Swap(lowerEnd, upper, size);
                        } else {
                            Rotate3(mid, upper, lowerEnd, size);
                        }
                        goto nextRound;
                    }
                    mid -= size;
                    {
                        P following = scan + size;
                        Swap(scan, mid, size);
                        scan = following;
                        if (end <= following) continue;  // still at or past the end: the down scan again
                    }
                    break;
                }
            upScan:
                // LAB_0095e770
                {
                    const int result = compare(lowerEnd, scan);
                    if (result < 0) {
                        scan += size;
                        goto nextRound;
                    }
                    if (result != 0) continue;  // larger than the pivot: the down scan
                    Swap(upper, scan, size);
                    upper += size;
                    scan += size;
                    goto nextRound;
                }
            }
        nextRound:;
        }
    restart:;
    }
}
}  // namespace

// 0x0095eab0 qsort -> Sort_IntroSort(base, count, count, size, compare)
void Ps3Qsort(void* base, uint32_t count, uint32_t size, int (*compare)(const void*, const void*)) {
    IntroSort(static_cast<P>(base), count, count, size, compare);
}
