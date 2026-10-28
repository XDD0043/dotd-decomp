// CKComparator.cpp - reconstructed original translation unit 0x234850-0x235030 (GAME_TOC1, main_toc1), 17 functions, 17 live.
// Primary class: CKComparator  key 0x230c  category Logic  size 0x14  vtable 0xb20978
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x234850  CKComparator_Delete
//   [x] 0x2348a0  CKComparator_vf60
//   [x] 0x2348a8  CKComparator_vf68
//   [ ] 0x2348b0  RegisterCKComparatorClass
//   [ ] 0x234928  _GLOBAL__I_234928
//   [x] 0x234938  CKComparator_Load
//   [ ] 0x234a40  CKComparator_Save
//   [ ] 0x234b48  CKComparator_RecursiveRegistration
//   [ ] 0x234c10  CKComparator_Destroy
//   [x] 0x234c38  CKComparator_DeleteArray
//   [x] 0x234ce0  CKComparator_Create
//   [x] 0x234d30  CKComparator_ClearFiredEvents_maybe
//   [x] 0x234db0  CKComparator_ClearEventLatches_maybe
//   [x] 0x234e30  CKComparator_vf64
//   [x] 0x234ec8  CKComparator_CreateArray
//   [x] 0x234f78  CKComparator_vf50
//   [x] 0x234ff8  CKComparator_Evaluate
//
//   [ ] 0x9b75b8  CKComparator_IsKindOfClass  [inline]
//   [ ] 0x9b75e0  CKComparator_GetClassType  [inline]
//   [ ] 0x9b75e8  CKComparator_GetClassID  [inline]
//   [ ] 0x9b75f0  CKComparator_Destructor  [inline]
//   [ ] 0x9b7610  CKComparator_DeletingDestructor  [inline]
//   [x] 0x9b7658  CKComparator_CompareOperands  [inline]
#include "k2000/logic/CKComparator.h"

#include "k2000/io/IKFile.h"
#include <cstring>

#include "k2000/core/Stub.h"
#include "k2000/logic/CKComparedData.h"

// 0x00234938 CKComparator_Load
int32_t CKComparator::Load(IKFile* file, int32_t type) {
    const int32_t result = IKEvaluator::Load(file, type);
    if (type == K_LEVEL_PLATEFORMS) {
        IKFile_ReadObjectRefArray(file, reinterpret_cast<IKSerializable**>(m_aDatas), 2);
    }
    return result;
}

namespace {
bool IsByteOperand(const CKComparedData* data) { return ((data->m_ba32Flags >> 2) & 3) == 2; }
}  // namespace

// 0x00234d30 CKComparator_ClearFiredEvents_maybe
void CKComparator::Start() {
    for (CKComparedData* data : m_aDatas) {
        if (IsByteOperand(data)) data->m_unk08 &= ~(1u << 24);
    }
}

// 0x00234e30 CKComparator_vf64
void CKComparator::Asleep() {
    for (CKComparedData* data : m_aDatas) {
        if (IsByteOperand(data) && ((data->m_unk08 >> 25) & 1) == 0) data->m_unk08 &= ~(1u << 24);
    }
}

// 0x00234f78 CKComparator_vf50 and 0x00234db0 CKComparator_ClearEventLatches_maybe: the same body as Start.
void CKComparator::Vf50() { Start(); }
void CKComparator::Vf5C() { Start(); }

namespace {

// The operand kinds CompareOperands reads: the first operand's flags bits 0-1 pick the type, bits 2-3 where
// the value is (1 and 3 the constant at +4, 2 the event byte at +8, 0 the value of an object, read through
// the accessor CKComparedData_PostLoad stored at +0xc / +0x10).
bool IsConstant(const CKComparedData* data) {
    const uint32_t mode = (data->m_ba32Flags >> 2) & 3;
    return mode == 1 || mode == 3;
}

// STUB(C2.2): the accessor of a mode-0 operand is a PS3 member-function pointer that CKComparedData_PostLoad
// (0x2331f0, through the object's GetInfo vt+0x40) fills; neither is ported, so the compare cannot read the
// value. The caller makes the comparison false, which is what the unevaluated trigger did before this port.
bool ObjectValueUnavailable() {
    DOTD_STUB_ONCE("CKComparator_CompareOperands: mode-0 operand (object value accessor, CKComparedData_PostLoad)");
    return true;
}

// The byte of an operand (type 0): the event byte of a mode-2 operand ANDed with 1, the first byte of the
// big-endian word at +4 of a constant.
bool ByteOperand(const CKComparedData* data, uint32_t* out) {
    if (((data->m_ba32Flags >> 2) & 3) == 2) {
        *out = (data->m_unk08 >> 24) & 1;
        return true;
    }
    if (IsConstant(data)) {
        *out = data->m_ui32Value >> 24;
        return true;
    }
    return !ObjectValueUnavailable();
}

bool IntOperand(const CKComparedData* data, int32_t* out) {
    if (IsConstant(data)) {
        *out = static_cast<int32_t>(data->m_ui32Value);
        return true;
    }
    return !ObjectValueUnavailable();
}

bool FloatOperand(const CKComparedData* data, double* out) {
    if (IsConstant(data)) {
        float value;
        std::memcpy(&value, &data->m_ui32Value, sizeof value);
        *out = static_cast<double>(value);
        return true;
    }
    return !ObjectValueUnavailable();
}

}  // namespace

// 0x00234ff8 CKComparator_Evaluate, with the inline CompareOperands 0x9b7658 (the key is the operator
// (flags bits 1-3) << 16 | the first operand's type). Each operand is read when its side of the compare is
// reached, as in the original (first operand, then the second); the combinations the original does not list
// give false.
bool CKComparator::Vf54() {
    const CKComparedData* a = m_aDatas[0];
    const CKComparedData* b = m_aDatas[1];
    const uint32_t op = (m_ba32Flags >> 1) & 7;
    const uint32_t type = a->m_ba32Flags & 3;
    if (op <= 5 && type == 0) {
        if (op < 4) return false;
        uint32_t x = 0, y = 0;
        if (!ByteOperand(a, &x) || !ByteOperand(b, &y)) return false;
        return op == 4 ? x == y : x != y;
    }
    if (op > 5 || type == 0) return false;
    if (type == 2) {
        double x = 0, y = 0;
        if (!FloatOperand(a, &x) || !FloatOperand(b, &y)) return false;
        switch (op) {
            case 0: return x <= y;
            case 1: return x < y;
            case 2: return y <= x;
            case 3: return y < x;
            case 4: return x == y;
            default: return x != y;
        }
    }
    // types 1 and 3 compare signed integers (type 3 only for == and !=; ops 0-3 list type 1 and 2 alone)
    if (type == 3 && op < 4) return false;
    int32_t x = 0, y = 0;
    if (!IntOperand(a, &x) || !IntOperand(b, &y)) return false;
    switch (op) {
        case 0: return x <= y;
        case 1: return x < y;
        case 2: return y <= x;
        case 3: return y < x;
        case 4: return x == y;
        default: return x != y;
    }
}
