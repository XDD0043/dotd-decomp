// CKGroupBlocCinematicBloc.h - a group of cinematic elements (key 0x1c8, vtable 0xb1b3b0, size 0x48). Original unit: CKGroupBlocCinematicBloc.cpp.
// XXL2: the same members in the same order.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/misc/IKCinematicBloc.h"

class IKFile;

class CKGroupBlocCinematicBloc : public IKCinematicBloc {
public:
    DOTD_CLASS_KEY(kCategoryCinematic, 0x7)
    DOTD_DECLARE_FACTORIES(CKGroupBlocCinematicBloc)
    DOTD_BLOC_IS_KIND_OF()

    // 0x0017c430 CKGroupBlocCinematicBloc_Create: IKCinematicBloc_Construct, then the vtable.
    CKGroupBlocCinematicBloc() {}
    ~CKGroupBlocCinematicBloc() override {}

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x0017cc38 CKGroupBlocCinematicBloc_Load

    IKSerializable** m_pEltPointer;  // +0x38 IKCinematicElement references (new[]); not set when the count is 0
    uint32_t m_ui32EltNumber;        // +0x3c
    IKSerializable* m_pBegin;        // +0x40 IKCinematicElement
    IKSerializable* m_pEnd;          // +0x44 IKCinematicElement
};
DOTD_ASSERT_SIZE(CKGroupBlocCinematicBloc, 0x48);
DOTD_ASSERT_OFFSET(CKGroupBlocCinematicBloc, m_pEltPointer, +0x38);
DOTD_ASSERT_OFFSET(CKGroupBlocCinematicBloc, m_ui32EltNumber, +0x3c);
DOTD_ASSERT_OFFSET(CKGroupBlocCinematicBloc, m_pBegin, +0x40);
DOTD_ASSERT_OFFSET(CKGroupBlocCinematicBloc, m_pEnd, +0x44);
