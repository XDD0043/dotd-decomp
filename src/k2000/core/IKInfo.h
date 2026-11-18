// IKInfo.h - the value request of IKSerializable::GetInfo (vt+0x40; XXL2 GetInfo(IKInfo*, EGetInfoRequestType)).
// CKComparedData_PostLoad (0x2331f0) builds one on its stack (vtable TOC1 -0x450, no data of its own) with the
// requested value id at +0x10; a class that knows the id answers 0 and writes the accessor (+0x04/+0x08, a PS3
// member-function pointer: the function descriptor and the this-adjustment, 0) and the value's type (+0x0c). The
// trigger comparator then calls the accessor with the operand's argument (CKComparator_CompareOperands 0x9b7658).
#pragma once
#include <cstdint>
#include <cstring>

class IKSerializable;

// The accessor: the value as a raw word (a byte in the low 8 bits, an integer, or a float's bits).
using InfoAccessor = uint32_t (*)(IKSerializable* self, uint32_t arg);

struct IKInfo {
    InfoAccessor m_pfnAccessor = nullptr;  // +0x04 / +0x08 in the original
    int32_t m_eValueType = 0;              // +0x0c 0 a byte, 1 an integer, 2 a float
    uint32_t m_ui32Id = 0;                 // +0x10 the requested value id
};

// GetInfo's request types (XXL2 EGetInfoRequestType): 0 the value accessor; the others are not used by DotD's
// comparator.
enum : int32_t { kGetInfoValueAccessor = 0 };

// Answers one value id: writes the accessor and the type and returns 0 (found); GetInfo returns 1 when no case knows
// the id.
inline int32_t AnswerInfo(IKInfo* info, InfoAccessor accessor, int32_t type) {
    info->m_pfnAccessor = accessor;
    info->m_eValueType = type;
    return 0;
}

inline uint32_t FloatBits(float value) {
    uint32_t bits;
    std::memcpy(&bits, &value, 4);
    return bits;
}
