// IKPath.h - the abstract path (key 0x70c, vtable 0xb17c98; XXL2: K/KModules/KGL/Path/IKPath.h, member
// m_pPathOwner). Its constructor is inlined in the paths' Creates (CKSpline4, CKSpline4L, CKLine), whose
// Loads all clear m_pPathOwner first and read their lists with the same TVector code (LoadPathVector).
#pragma once
#include <cstdint>

#include "k2000/core/IKSerializable.h"
#include "k2000/core/Layout.h"
#include "k2000/io/IKFile.h"
#include "k2000/memory/Mem.h"
#include "k2000/util/TVector.h"

struct CVector3;

class IKPath : public IKSerializable {
public:
    IKPath() { m_pPathOwner = nullptr; }
    ~IKPath() override {}

    // vt+0x54 (pure in IKPath; CKSpline4L 0xc7420 GetPointAtDistance_maybe): the point at `distance` along the path, and
    // with `direction` the path's direction there. (r5 is not read.) step 5: the camera path track.
    virtual void GetPointAtDistance(float distance, CVector3* point, CVector3* direction);
    // vt+0x58 (pure in IKPath; CKSpline4L 0xc66a8, CKLine 0xc7a30 GetClosestDistanceAlong_maybe): the distance along the
    // path of the path's point closest to `point`; `squared` 0 measures with |dx| + |dy| + |dz|, else the squared
    // length. step 6: the camera zones' flagged paths (CKCameraConstraint_ComputeLookDirection_maybe).
    virtual float GetClosestDistanceAlong(const CVector3* point, uint8_t squared);
    // vt+0x5c (pure in IKPath; CKSpline4L 0x9a2090 GetLength): the path's length.
    virtual float GetLength();

    void* m_pPathOwner;  // +0x04 XXL2 IKPath::m_pPathOwner (IKPathOwner*)
};
DOTD_ASSERT_SIZE(IKPath, 0x8);

// An empty TVector as the path constructors leave it: null, capacity Grow, 0 used.
template <class T, uint32_t Grow>
inline void InitPathVector(TVector<T, Grow>& v) {
    v.m_pBlock = nullptr;
    v.m_ui32NbElt = Grow;
    v.m_ui32NbUsedElt = 0;
}

// The paths' inlined TVector<T, Grow> load: sized to `count` (1 element when 0), the original's
// never-taken grow step, then one Read of the elements; with swapWords each 32-bit word is swapped.
template <class T, uint32_t Grow>
inline void LoadPathVector(IKFile* file, TVector<T, Grow>& v, uint32_t count, bool swapWords) {
    if (count == 0) {
        v.m_ui32NbElt = 1;
        v.m_pBlock = static_cast<T*>(Mem_AllocAligned16(static_cast<uint32_t>(sizeof(T))));
    } else {
        v.m_ui32NbElt = count;
        v.m_pBlock = static_cast<T*>(Mem_AllocAligned16(count * static_cast<uint32_t>(sizeof(T))));
    }
    if (v.m_ui32NbElt < count) {  // as in the original: cannot happen
        uint32_t capacity = (count & ~(Grow - 1)) + Grow;
        if (capacity == 0) capacity = Grow;
        v.m_pBlock = static_cast<T*>(Mem_ReallocAligned16(v.m_pBlock, capacity * static_cast<uint32_t>(sizeof(T))));
        v.m_ui32NbElt = capacity;
    }
    v.m_ui32NbUsedElt = count;
    const uint32_t bytes = count * static_cast<uint32_t>(sizeof(T));
    if (swapWords) {
        ReadU32LEWords(file, reinterpret_cast<uint32_t*>(v.m_pBlock), bytes / 4);
    } else {
        ReadRaw(file, v.m_pBlock, bytes);
    }
}
